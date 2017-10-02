import codecs, getpass, jinja2, logging, os, time, datetime, sys, random

from tthAnalysis.HiggsToTauTau.ClusterHistogramAggregator import ClusterHistogramAggregator
from tthAnalysis.HiggsToTauTau.jobTools import create_if_not_exists, run_cmd

# Template for wrapper that is ran on cluster node

current_dir = os.path.dirname(os.path.realpath(__file__))

command_create_scratchDir = '/scratch/mkscratch'

# Define error classes

class sbatchManagerError(Exception):
    pass

class sbatchManagerMemoryError(sbatchManagerError):
    pass

class sbatchManagerTimeoutError(sbatchManagerError):
    pass

class sbatchManagerSyntaxError(sbatchManagerError):
    pass

class sbatchManagerRuntimeError(sbatchManagerError):
    pass

# Define Status

class Status:
  submitted   = 1
  completed   = 2
  running     = 3

  memory_exceeded = 11
  timeout         = 12
  syntax_error    = 13
  runtime_error   = 14
  other_error     = 15

  @staticmethod
  def classify_error(ExitCode, DerivedExitCode, State):
      if (ExitCode == '0:0' and DerivedExitCode == '0:0' and State == 'COMPLETED'):
          return Status.completed
      if (ExitCode == '0:0' and DerivedExitCode == '0:0' and (State == 'CANCELLED' or
                                                              State == 'CANCELLED by 0')) or \
         (ExitCode == '7:0'                              and State == 'FAILED'):
          # The last condition found at: https://wiki.hpc.uconn.edu/index.php/Job_FAILED_due_to_lack_of_memory
          return Status.memory_exceeded
      if (ExitCode == '0:1' and DerivedExitCode == '0:0' and State == 'TIMEOUT'):
          return Status.timeout
      if (ExitCode == '2:0' and DerivedExitCode == '0:0' and State == 'FAILED'):
          return Status.syntax_error
      if (ExitCode == '1:0' and DerivedExitCode == '0:0' and State == 'FAILED'):
          return Status.runtime_error
      return Status.other_error

  @staticmethod
  def toString(status_type):
      if status_type == Status.submitted:
          return 'submitted'
      if status_type == Status.completed:
          return 'completed'
      if status_type == Status.memory_exceeded:
          return 'memory_exceeded_error'
      if status_type == Status.timeout:
          return 'timeout_error'
      if status_type == Status.syntax_error:
          return 'syntax_error'
      if status_type == Status.runtime_error:
          return 'runtime_error'
      if status_type == Status.other_error:
          return 'other_error'
      return 'unknown_error'

  @staticmethod
  def raiseError(status_type):
      if status_type == Status.memory_exceeded:
          return sbatchManagerMemoryError
      if status_type == Status.timeout:
          return sbatchManagerTimeoutError
      if status_type == Status.syntax_error:
          return sbatchManagerSyntaxError
      if status_type == Status.runtime_error:
          return sbatchManagerRuntimeError
      return sbatchManagerError

# Define sbatchManager

class sbatchManager:
    """Manages SLURM jobs

       About queue priorities:
         low - 2d (maybe 2w) time limit, availability dependent on load
         main - 2d time limit, good availability
         short - 2h time limit, very good availability
         prio - ? (10min?) time limit, available immediately
    """

    def __init__(self, pool_id = '', verbose = False):
        if not pool_id:
            raise ValueError("pool_id not specified!")

        self.cmssw_base_dir = None
        self.workingDir     = None
        self.logFileDir     = None
        queue_environ = os.environ.get('SBATCH_PRIORITY')
        self.queue          = queue_environ if queue_environ else "small"
        self.poll_interval  = 30
        self.jobIds         = {}
        self.analysisName   = "tthAnalysis"
        self.user           = getpass.getuser()
        self.pool_id        = pool_id
        self.log_completion = False
        self.max_nof_greps  = 1000
        self.sbatchArgs     = ''
        self.datetime       = datetime.datetime.now().strftime('%m/%d/%y-%H:%M:%S')

        logging.basicConfig(
            stream = sys.stdout,
            level  = logging.DEBUG if verbose else logging.INFO,
            format = '[%(filename)s:%(funcName)s] %(asctime)s - %(levelname)s: %(message)s',
        )

    def setWorkingDir(self, workingDir):
        """Set path to CMSSW area in which jobs are executed
        """
        self.workingDir = workingDir

    def setcmssw_base_dir(self, cmssw_base_dir):
        """Set path to cmssw_base_dir area in which jobs are executed
        """
        self.cmssw_base_dir = cmssw_base_dir

    def setLogFileDir(self, logFileDir):
        """Set path to directory in which log files are to be stored (matters only if 'logFile'
           parameter is not given when calling 'submitJob' method)
        """
        self.logFileDir = logFileDir

    def mute(self):
        logging.getLogger().setLevel(logging.INFO)

    def unmute(self):
        logging.getLogger().setLevel(logging.DEBUG)

    def check_job_completion(self, jobsId_list, default_completion = Status.completed):
        completion = { k : default_completion for k in jobsId_list }

        # If the input list is empty, just return here (we don't want to mess up the subprocess commands here)
        if not completion:
          return completion

        # Set a delimiter, which distinguishes entries b/w different jobs
        delimiter = ','

        # First, let's try with sacct; explanation:
        # 1) sacct -X -P -n -o JobID,ExitCode,DerivedExitCode,State
        #      Shows job IDs, exit codes and comments of all submitted, running and finished jobs, one line per job
        #        a) -X -- shows cumulative statistics of each job (has no effect here, though)
        #        b) -P -- output will be '|' delimited without a '|' at the end
        #        c) -n -- omit header
        #        d) -o JobID,ExitCode,DerivedExitCode -- output format
        #        e) -S {datetime} -- look only for jobs submitted after {datetime}
        #        f) -j {jobs} -- filter out only the relevant jobs by their job ID (comma-separated list)
        # 2) sed ':a;N;$!ba;s/\\n/{delimiter}/g'
        #      Place all entries to one line, delimited by {{delimiter}} (otherwise the logs are hard to read)
        sacct_cmd = "sacct -X -P -n -o JobID,ExitCode,DerivedExitCode,State -S {datetime} -j {jobs} | " \
                    "sed ':a;N;$!ba;s/\\n/{delimiter}/g'".format(
          datetime  = self.datetime,
          jobs      = ','.join(jobsId_list),
          delimiter = delimiter,
        )
        sacct_out, sacct_err = run_cmd(sacct_cmd, do_not_log = not self.log_completion, return_stderr = True)
        if not sacct_err and sacct_out:
            # The output of sacct contains one line per job, each line has pipe-separated fields the order of which
            # is defined in the command that issued the output
            lines = sacct_out.split(delimiter)
            for line in lines:
                JobID, ExitCode, DerivedExitCode, State = line.split('|')
                if JobID in completion:
                    if State in ['RUNNING', 'COMPLETING']:
                      completion[JobID] = Status.running
                    else:
                      completion[JobID] = Status.classify_error(ExitCode, DerivedExitCode, State)
            return completion
        else:
            # Likely returned along the lines of (due to heavy load on the cluster since SQL DB is overloaded):
            # sacct: error: Problem talking to the database: Connection refused
            logging.info('sacct currently unavailable: %s' % sacct_err)

        # Let's try with scontrol if the sacct commands failed
        # scontrol doesn't have an option to take a list of Job IDs as an argument; thus, we have to grep the job IDs
        # Explanation:
        # 1) scontrol show -od job
        #      Prints out everything about running or recently finished jobs
        #        a) -o -- prints information one line per record
        #        b) -d -- includes more detailed information about the job
        #        c) job -- prints all jobs (it's possible to get information about other units like nodes and clusters)
        # 2) grep '{jobs}'
        #      Filter out jobs by their job ID (by concatenating the list with escaped regex OR operator '|')
        # 3) sed ':a;N;$!ba;s/\\n/{delimiter}/g'
        #      Put all the result on one line, where each record is delimited by {delimiter}
        scontrol_cmd = "scontrol show -od job | grep '{jobs}' | sed ':a;N;$!ba;s/\\n/{delimiter}/g'".format(
          jobs      = '\\|'.join(jobsId_list),
          delimiter = delimiter,
        )
        scontrol_out, scontrol_err = run_cmd(scontrol_cmd, do_not_log = not self.log_completion, return_stderr = True)
        if not scontrol_err and scontrol_out:
            # The output of scontrol contains one entry per line, each line contains a space-delimited key-value pairs,
            # whereas the keys and values are separated by an equation sign
            # Although the keys do not contain any spaces, the values might, so we have to take care of that
            lines = scontrol_out.split(delimiter)
            for line in lines:
                line_dict = {}
                line_split_eq_spaces = map(lambda x: x.split(), line.split('='))
                for i in range(len(line_split_eq_spaces) - 1):
                    k = line_split_eq_spaces[i]
                    v = line_split_eq_spaces[i + 1]
                    line_dict[k[-1]] = ' '.join(v[:-1] if i != len(line_split_eq_spaces) - 2 else v)
                JobId = line_dict['JobId']
                if JobId in completion:
                    completion[JobId] = Status.classify_error(
                      line_dict['ExitCode'],
                      line_dict['DerivedExitCode'],
                      line_dict['JobState'],
                    )
            return completion
        else:
            # scontrol probably returned something like:
            # slurm_load_jobs error: Invalid job id specified
            # Probably because too much time has passed since the job completion and checking the exit status here
            logging.info('scontrol has errors: %s' % scontrol_err)

        # scontrol still might fail if too much time has passed since the jobs completion (the metadata about each
        # job is cached for a certain period of time, the length of which I don't know at the moment)
        # None of the SLURM commands work; let's just say that the job completed successfully
        logging.error("Cannot tell if the job has completed successfully or not!")
        return completion

    def submit(self, cmd_str):
        # Run command
        cmd_outerr = run_cmd(cmd_str, return_stderr = True)
        # Fails if stdout returned by the last line is empty
        try:
          job_id = cmd_outerr[0].split()[-1]
        except IndexError:
          raise IndexError("Caught an error: '%s'" % cmd_outerr[1])
        # The job ID must be a number, so.. we have to check if it really is one
        try:
          int(job_id)
        except ValueError:
          raise ValueError("job_id = '%s' NaN; sbatch stdout = '%s'; sbatch stderr = '%s'" % \
                            (job_id, cmd_outerr[0], cmd_outerr[1]))
        if job_id in self.jobIds:
            raise RuntimeError("Same job ID: %s" % job_id)
        # Is a valid job ID
        return job_id

    def submitJob(self, inputFiles, executable, command_line_parameter, outputFilePath, outputFiles,
                  scriptFile, logFile = None, skipIfOutputFileExists = False, job_template_file = 'sbatch-node.template.sh'):
        """Waits for all sbatch jobs submitted by this instance of sbatchManager to finish processing
        """

        logging.debug("<sbatchManager::submitJob>: job_template_file = '%s'" % job_template_file)

        job_template_file = os.path.join(current_dir, job_template_file)
        job_template = open(job_template_file, 'r').read()
        
        # raise if logfile missing
        if not logFile:
            if not self.logFileDir:
                raise ValueError("Please call 'setLogFileDir' before calling 'submitJob' !!")
            logFile = os.path.join(self.logFileDir, os.path.basename(scriptFile).replace(".sh", ".log"))

        # skip only if none of the output files are missing in the file system
        if skipIfOutputFileExists:
            outputFiles_fullpath = map(lambda outputFile: os.path.join(outputFilePath, outputFile), outputFiles)
            outputFiles_missing = [ outputFile for outputFile in outputFiles_fullpath if not os.path.exists(outputFile) ]
            if not outputFiles_missing:
                logging.debug(
                  "output file(s) = %s exist(s) --> skipping !!" % \
                  '; '.join(map(lambda x: "'%s'" % x, outputFiles_fullpath))
                )
                return

        if not self.workingDir:
            raise ValueError("Please call 'setWorkingDir' before calling 'submitJob' !!")

        if not self.cmssw_base_dir:
            print("cmssw_base_dir not set, setting it to '%s'" % os.environ.get('CMSSW_BASE'))
            self.cmssw_base_dir = os.environ.get('CMSSW_BASE')

        scratch_dir = self.get_scratch_dir()

        # create script for executing jobs
        wrapper_log_file    = logFile.replace('.log', '_wrapper.log')
        executable_log_file = logFile.replace('.log', '_executable.log')

        sbatch_command = "sbatch --partition={partition} --output={output} --comment='{comment}' {args} {cmd}".format(
          partition = self.queue,
          output    = wrapper_log_file,
          comment   = self.pool_id,
          args      = self.sbatchArgs,
          cmd       = scriptFile,
        )

        two_pow_sixteen = 65536
        random.seed((abs(hash(command_line_parameter))) % two_pow_sixteen)
        max_delay = 300
        delay = random.randint(0, max_delay)
        
        script = jinja2.Template(job_template).render(
            working_dir            = self.workingDir,
            cmssw_base_dir         = self.cmssw_base_dir,
            scratch_dir            = scratch_dir,
            exec_name              = executable,
            command_line_parameter = command_line_parameter,
            inputFiles             = " ".join(inputFiles),
            outputDir              = outputFilePath,
            outputFiles            = " ".join(outputFiles),
            wrapper_log_file       = wrapper_log_file,
            executable_log_file    = executable_log_file,
            RUNNING_COMMAND        = sbatch_command,
            random_sleep           = delay
        )
        logging.debug("writing sbatch script file = '%s'" % scriptFile)
        with codecs.open(scriptFile, "w", "utf-8") as f:
            f.write(script)
            f.flush()
            os.fsync(f.fileno())

        self.jobIds[self.submit(sbatch_command)] = {
            'status'   : Status.submitted,
            'log_wrap' : wrapper_log_file,
            'log_exec' : executable_log_file,
        }

    def get_scratch_dir(self):
        scratch_dir = "/scratch/%s" % getpass.getuser()
        if not os.path.exists(scratch_dir):
            logging.info("Directory '%s' does not yet exist, creating it !!" % scratch_dir)
            run_cmd(command_create_scratchDir)
        scratch_dir = os.path.join(
            scratch_dir,
            "%s_%s" % (self.analysisName, datetime.date.today().isoformat()),
        )
        create_if_not_exists(scratch_dir)
        return scratch_dir

    def waitForJobs(self):
        """Waits for all sbatch jobs submitted by this instance of sbatchManager to finish processing
        """
        text_line = '-' * 120

        # Set a delimiter, which distinguishes entries b/w different jobs
        delimiter = ','
        # Explanation:
        # 1) squeue -h -u {{user}} -o '%i %36k'
        #      Collects the list of running jobs
        #        a) -h omits header
        #        b) -u {{user}} looks only for jobs submitted by {{user}}
        #        c) -o '%i %36k' specifies the output format
        #           i)  %i -- job ID (1st column)
        #           ii) %36k -- comment with width of 36 characters (2nd column)
        #               If the job has no comments, the entry simply reads (null)
        # 2) grep {{comment}}
        #       Filter the jobs by the comment which must be unique per sbatchManager instance at all times
        # 3) awk '{print $1}'
        #       Filter only the jobs IDs out
        # 4) sed ':a;N;$!ba;s/\\n/{{delimiter}}/g'
        #       Place all job IDs to one line, delimited by {{delimiter}} (otherwise the logs are hard to read)
        command_template = "squeue -h -u {{user}} -o '%i %36k' | grep {{comment}} | awk '{print $1}' | " \
                           "sed ':a;N;$!ba;s/\\n/{{delimiter}}/g'"
        command = jinja2.Template(command_template).render(
          user      = self.user,
          comment   = self.pool_id,
          delimiter = delimiter,
        )

        # Initially, all jobs are marked as submitted so we have to go through all jobs and check their exit codes
        # even if some of them have already finished
        jobIds_set = set([ id_ for id_ in self.jobIds if self.jobIds[id_]['status'] == Status.submitted])
        nofJobs_left = len(jobIds_set)
        while nofJobs_left > 0:
            # Get the list of running jobs and convert them to a set
            poll_result = run_cmd(command, do_not_log = False)
            polled_ids = set(poll_result.split(delimiter))
            # Subtract the list of running jobs from the list of all submitted jobs -- the result is a list of
            # jobs that have finished already
            finished_ids = list(jobIds_set - polled_ids)

            # Do not poll anything if currently there are no finished jobs
            if finished_ids:
                # Based on job's exit code what if the job has failed or completed successfully
                # However, the sacct/scontrol commands yield too much output if too many jobs have been submitted here
                # Therefore, we want to restrict the output by grepping specific job IDs
                # There's another problem with that: the length of a bash command is limited by ARG_MAX kernel variable,
                # which is of order 2e6
                # This means that we have to split the job IDs into chunks each of which we have to check separately
                finished_ids_chunks = [
                  finished_ids[i : i + self.max_nof_greps] for i in range(0, len(finished_ids), self.max_nof_greps)
                ]
                for finished_ids_chunk in finished_ids_chunks:
                    completion = self.check_job_completion(finished_ids_chunk)
                    completed_jobs, running_jobs, failed_jobs = [], [], []
                    for id_, state in completion.iteritems():
                      if state == Status.completed:
                        completed_jobs.append(id_)
                      elif state == Status.running:
                        running_jobs.append(id_)
                      else:
                        failed_jobs.append(id_)
                    # If there are any failed jobs, throw
                    if failed_jobs:
                        failed_jobs_str = ','.join(failed_jobs)
                        errors          = [completion[id_] for id_ in failed_jobs]
                        logging.error("Job(s) w/ ID(s) {jobIds} finished with errors: {reasons}".format(
                            jobIds  = failed_jobs_str,
                            reasons = ', '.join(map(Status.toString, errors)),
                        ))
                        sys.stderr.write('%s\n' % text_line)
                        for failed_job in failed_jobs:
                            for log in zip(['wrapper', 'executable'], ['log_wrap', 'log_exec']):
                                logfile = self.jobIds[failed_job][log[1]]
                                if os.path.isfile(logfile):
                                    logfile_contents = open(logfile, 'r').read()
                                else:
                                    logfile_contents = '<file is missing>'
                                sys.stderr.write('Job ID {id} {description} log ({path}):\n{line}\n{log}\n{line}\n'.format(
                                    id          = failed_job,
                                    description = log[0],
                                    path        = logfile,
                                    log         = logfile_contents,
                                    line        = text_line,
                                ))
                        # Raise the first error at hand
                        raise Status.raiseError(errors[0])
                    else:
                        logging.debug("Job(s) w/ ID(s) {completedIds} finished successfully {runningInfo}".format(
                          completedIds = ','.join(completed_jobs),
                          runningInfo  = '(%s still running)' % ','.join(running_jobs) if running_jobs else '',
                        ))
                    # Mark successfully finished jobs as completed so that won't request their status code again
                    # Otherwise they will be still at ,,submitted'' state
                    for id_ in completed_jobs:
                        self.jobIds[id_]['status'] = Status.completed

            jobIds_set = set([ id_ for id_ in self.jobIds if self.jobIds[id_]['status'] == Status.submitted])
            nofJobs_left = len(jobIds_set)
            if nofJobs_left > 0:
                time.sleep(self.poll_interval)
            else:
                break
            logging.info("Waiting for sbatch to finish (%d job(s) still left) ..." % nofJobs_left)
