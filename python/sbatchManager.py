import codecs, getpass, jinja2, logging, os, time, datetime, sys, random, uuid

from tthAnalysis.HiggsToTauTau.jobTools import create_if_not_exists, run_cmd, get_log_version
from tthAnalysis.HiggsToTauTau.sbatchManagerTools import is_file_ok

# Template for wrapper that is ran on cluster node

jinja_template_dir = os.path.join(
  os.getenv('CMSSW_BASE'), 'src', 'tthAnalysis', 'HiggsToTauTau', 'python', 'templates'
)

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

class sbatchManagerIOError(sbatchManagerError):
    pass

class sbatchManagerMissingFileError(sbatchManagerError):
    pass

class sbatchManagerCopyError(sbatchManagerError):
    pass

class sbatchManagerValidationError(sbatchManagerError):
    pass

# Define Status

class Status:
  submitted   = 1
  completed   = 2
  running     = 3

  memory_exceeded  = 11
  timeout          = 12
  syntax_error     = 13
  runtime_error    = 14
  other_error      = 15
  io_error         = 16
  missing_file     = 17
  cp_error         = 18
  validation_error = 19

  @staticmethod
  def classify_error(ExitCode, DerivedExitCode, State):
      if State in ['COMPLETING', 'RUNNING', 'PENDING']:
          return Status.running
      if (ExitCode in ['0:0', '0:1'] and DerivedExitCode in ['0:0', '0:1'] and State == 'COMPLETED'):
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
      if (ExitCode == '2:0' and DerivedExitCode == '0:0' and State == 'FAILED'):
          return Status.runtime_error
      if (ExitCode == '3:0' and DerivedExitCode == '0:0' and State == 'FAILED'):
          return Status.io_error
      if (ExitCode == '4:0' and DerivedExitCode == '0:0' and State == 'FAILED'):
          return Status.missing_file
      if (ExitCode == '5:0' and DerivedExitCode == '0:0' and State == 'FAILED'):
          return Status.cp_error
      if (ExitCode == '6:0' and DerivedExitCode == '0:0' and State == 'FAILED'):
          return Status.validation_error
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
      if status_type == Status.io_error:
          return 'io_error'
      if status_type == Status.missing_file:
          return 'missing_file'
      if status_type == Status.cp_error:
          return 'cp_error'
      if status_type == Status.validation_error:
          return 'validation_error'
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
      if status_type == Status.io_error:
          return sbatchManagerRuntimeError
      if status_type == Status.missing_file:
          return sbatchManagerMissingFileError
      if status_type == Status.cp_error:
          return sbatchManagerCopyError
      if status_type == Status.validation_error:
          return sbatchManagerValidationError
      return sbatchManagerError

# Define JobCompletion class to hold information about finished jobs

class JobCompletion:
  def __init__(self, status, exit_code = '-1:-1', derived_exit_code = '-1:-1', state = 'N/A'):
      self.status            = status
      self.exit_code         = exit_code
      self.derived_exit_code = derived_exit_code
      self.state             = state

# Define sbatchManager

class sbatchManager:
    """Manages SLURM jobs

       About queue priorities:
         low - 2d (maybe 2w) time limit, availability dependent on load
         main - 2d time limit, good availability
         short - 2h time limit, very good availability
         prio - ? (10min?) time limit, available immediately
    """

    def __init__(self,
            pool_id = '',
            verbose = False,
            dry_run = False,
            use_home = True,
            max_resubmissions = 6,
            min_file_size = 20000,
          ):
        self.max_pool_id_length = 256
        if not pool_id:
            raise ValueError("Parameter 'pool_id' not specified!")
        if len(pool_id) > self.max_pool_id_length:
            raise ValueError(
                "Parameter 'pool_id' exceeds maximum length of %i characters!" % self.max_pool_id_length
            )

        self.cmssw_base_dir = None
        self.workingDir     = None
        self.logFileDir     = None
        queue_environ = os.environ.get('SBATCH_PRIORITY')
        verbose_environ = os.environ.get('SBATCH_VERBOSE')
        self.queue             = queue_environ if queue_environ else "small"
        self.poll_interval     = 30
        self.jobIds            = {}
        self.analysisName      = "tthAnalysis"
        self.user              = getpass.getuser()
        self.pool_id           = pool_id
        self.log_completion    = verbose_environ
        self.max_nof_greps     = 1000
        self.sbatchArgs        = ''
        self.datetime          = datetime.datetime.now().strftime('%m/%d/%y-%H:%M:%S')
        self.dry_run           = dry_run
        self.max_mem           = '1800M'
        self.use_home          = use_home
        self.max_resubmissions = max_resubmissions
        self.min_file_size     = min_file_size

        verbose = bool(verbose_environ) if verbose_environ else verbose
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
        completion = { k : JobCompletion(status = default_completion) for k in jobsId_list }

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
                  completion[JobID] = JobCompletion(
                      status            = Status.classify_error(ExitCode, DerivedExitCode, State),
                      exit_code         = ExitCode,
                      derived_exit_code = DerivedExitCode,
                      state             = State,
                  )
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
                if not 'JobId' in line_dict.keys():
                    print("Skipping line = '%s'" % line)
                    continue
                JobId = line_dict['JobId']
                if JobId in completion:
                    completion[JobId] = JobCompletion(
                        status = Status.classify_error(
                          line_dict['ExitCode'],
                          line_dict['DerivedExitCode'],
                          line_dict['JobState'],
                        ),
                        exit_code         = line_dict['ExitCode'],
                        derived_exit_code = line_dict['DerivedExitCode'],
                        state             = line_dict['JobState']
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
        nof_max_retries = 10
        current_retry   = 0
        while current_retry < nof_max_retries:
          # Run command
          cmd_outerr = run_cmd(cmd_str, return_stderr = True)
          try:
            job_id = cmd_outerr[0].split()[-1]
            break
          except IndexError:
            # Fails if stdout returned by the last line is empty
            logging.warning("Caught an error: '%s'; resubmitting %i-th time" % (cmd_outerr[1], current_retry))
            current_retry += 1
            time.sleep(60) # Let's wait for 60 seconds until the next resubmission

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
                  scriptFile, logFile = None, skipIfOutputFileExists = False,
                  job_template_file = 'sbatch-node.sh.template', nof_submissions = 0):
        """Waits for all sbatch jobs submitted by this instance of sbatchManager to finish processing
        """

        logging.debug("<sbatchManager::submitJob>: job_template_file = '%s'" % job_template_file)

        job_template_file = os.path.join(jinja_template_dir, job_template_file)
        job_template = open(job_template_file, 'r').read()

        # raise if logfile missing
        if not logFile:
            if not self.logFileDir:
                raise ValueError("Please call 'setLogFileDir' before calling 'submitJob' !!")
            logFile = os.path.join(self.logFileDir, os.path.basename(scriptFile).replace(".sh", ".log"))

        # skip only if none of the output files are missing in the file system
        outputFiles_fullpath = map(lambda outputFile: os.path.join(outputFilePath, outputFile), outputFiles)
        if skipIfOutputFileExists:
            outputFiles_missing = [
                outputFile for outputFile in outputFiles_fullpath \
                if not is_file_ok(outputFile, validate_outputs = True, min_file_size = self.min_file_size)
            ]
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

        job_dir = self.get_job_dir()

        # create script for executing jobs
        wrapper_log_file    = logFile.replace('.log', '_wrapper.log')
        executable_log_file = logFile.replace('.log', '_executable.log')
        wrapper_log_file, executable_log_file = get_log_version((wrapper_log_file, executable_log_file))

        sbatch_command = "sbatch --partition={partition} --output={output} --comment='{comment}' " \
                         "--mem={max_mem} {args} {cmd}".format(
          partition = self.queue,
          output    = wrapper_log_file,
          comment   = self.pool_id,
          args      = self.sbatchArgs,
          cmd       = scriptFile,
          max_mem   = self.max_mem,
        )

        two_pow_sixteen = 65536
        random.seed((abs(hash(command_line_parameter))) % two_pow_sixteen)
        max_delay = 300
        random_delay = random.randint(0, max_delay)

        script = jinja2.Template(job_template).render(
            working_dir            = self.workingDir,
            cmssw_base_dir         = self.cmssw_base_dir,
            job_dir                = job_dir,
            job_template_file      = job_template_file,
            exec_name              = executable,
            command_line_parameter = command_line_parameter,
            inputFiles             = " ".join(inputFiles),
            outputDir              = outputFilePath,
            outputFiles            = " ".join(outputFiles),
            wrapper_log_file       = wrapper_log_file,
            executable_log_file    = executable_log_file,
            script_file            = scriptFile,
            RUNNING_COMMAND        = sbatch_command,
            random_sleep           = random_delay
        )
        logging.debug("writing sbatch script file = '%s'" % scriptFile)
        with codecs.open(scriptFile, "w", "utf-8") as f:
            f.write(script)
            f.flush()
            os.fsync(f.fileno())

        if self.dry_run:
            return

        nof_submissions += 1
        self.jobIds[self.submit(sbatch_command)] = {
            'status'          : Status.submitted,
            'log_wrap'        : wrapper_log_file,
            'log_exec'        : executable_log_file,
            'args'            : (
                inputFiles, executable, command_line_parameter, outputFilePath, outputFiles,
                scriptFile, logFile, skipIfOutputFileExists, job_template_file, nof_submissions,
            ),
            'nof_submissions' : nof_submissions,
            'outputFiles'     : outputFiles_fullpath,
        }

    def get_job_dir(self):
        if self.use_home:
            prefix = os.path.join('/home', getpass.getuser(), 'jobs')
        else:
            prefix = os.path.join('/scratch', getpass.getuser())
            if not os.path.isdir(prefix):
                run_cmd('/scratch/mkscratch')
        job_dir = os.path.join(
            prefix, "%s_%s" % (self.analysisName, datetime.date.today().isoformat()),
        )
        return job_dir

    def waitForJobs(self):
        """Waits for all sbatch jobs submitted by this instance of sbatchManager to finish processing
        """
        text_line = '-' * 120

        # Set a delimiter, which distinguishes entries b/w different jobs
        delimiter = ','
        # Explanation (the maximum pool ID length = 256 is configurable via self.max_pool_id_length):
        # 1) squeue -h -u {{user}} -o '%i %256k'
        #      Collects the list of running jobs
        #        a) -h omits header
        #        b) -u {{user}} looks only for jobs submitted by {{user}}
        #        c) -o '%i %256k' specifies the output format
        #           i)  %i -- job ID (1st column)
        #           ii) %256k -- comment with width of 256 characters (2nd column)
        #               If the job has no comments, the entry simply reads (null)
        # 2) grep {{comment}}
        #       Filter the jobs by the comment which must be unique per sbatchManager instance at all times
        # 3) awk '{print $1}'
        #       Filter only the jobs IDs out
        # 4) sed ':a;N;$!ba;s/\\n/{{delimiter}}/g'
        #       Place all job IDs to one line, delimited by {{delimiter}} (otherwise the logs are hard to read)
        command_template = "squeue -h -u {{user}} -o '%i %{{ pool_id_length }}k' | grep {{comment}} | awk '{print $1}' | " \
                           "sed ':a;N;$!ba;s/\\n/{{delimiter}}/g'"
        command = jinja2.Template(command_template).render(
          user           = self.user,
          pool_id_length = self.max_pool_id_length,
          comment        = self.pool_id,
          delimiter      = delimiter
        )

        # Initially, all jobs are marked as submitted so we have to go through all jobs and check their exit codes
        # even if some of them have already finished
        jobIds_set = set([ id_ for id_ in self.jobIds if self.jobIds[id_]['status'] == Status.submitted])
        nofJobs_left = len(jobIds_set)
        while nofJobs_left > 0:
            # Get the list of running jobs and convert them to a set
            poll_result, poll_result_err = '', ''
            while True:
                poll_result, poll_result_err = run_cmd(command, do_not_log = False, return_stderr = True)
                if not poll_result and poll_result_err:
                    logging.warning('squeue caught an error: {squeue_error}'.format(squeue_error = poll_result_err))
                else:
                    break
                # sleep a minute and then try again
                # in principle we could limit the number of retries, but hopefully that's not necessary
                time.sleep(60)
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
                    for id_, details in completion.iteritems():
                      if details.status == Status.completed:
                        completed_jobs.append(id_)
                      elif details.status == Status.running:
                        running_jobs.append(id_)
                      else:
                        failed_jobs.append(id_)
                    # If there are any failed jobs, throw
                    if failed_jobs:

                        failed_jobs_str = ','.join(failed_jobs)
                        errors          = [completion[id_].status for id_ in failed_jobs]
                        logging.error("Job(s) w/ ID(s) {jobIds} finished with errors: {reasons}".format(
                            jobIds  = failed_jobs_str,
                            reasons = ', '.join(map(Status.toString, errors)),
                        ))

                        # Let's print a table where the first column corresponds to the job ID
                        # and the second column lists the exit code, the derived exit code, the status
                        # and the classification of the failed job
                        logging.error("Error table:")
                        for id_ in failed_jobs:
                            sys.stderr.write("{jobId} {exitCode} {derivedExitCode} {state} {status}\n".format(
                                jobId           = id_,
                                exitCode        = completion[id_].exit_code,
                                derivedExitCode = completion[id_].derived_exit_code,
                                state           = completion[id_].state,
                                status          = Status.toString(completion[id_].status),
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
                                  )
                                )

                            if self.jobIds[failed_job]['nof_submissions'] < self.max_resubmissions and \
                               completion[failed_job].status == Status.io_error:
                                # The job is eligible for resubmission if the job hasn't been resubmitted more
                                # than a preset limit of resubmissions AND if the job failed due to I/O errors
                                logging.warning(
                                    "Job w/ ID {id} and arguments {args} FAILED because: {reason} "
                                    "-> resubmission attempt #{attempt}".format(
                                        id      = failed_job,
                                        args    = self.jobIds[failed_job]['args'],
                                        reason  = Status.toString(completion[failed_job].status),
                                        attempt = self.jobIds[failed_job]['nof_submissions'],
                                    )
                                )
                                self.submitJob(*self.jobIds[failed_job]['args'])
                                # The old ID must be deleted, b/c otherwise it would be used to compare against
                                # squeue output and we would resubmit the failed job ad infinitum
                                del self.jobIds[failed_job]
                            else:
                                # We've exceeded the maximum number of resubmissions -> fail the workflow
                                raise Status.raiseError(completion[failed_job].status)
                    else:
                        logging.debug("Job(s) w/ ID(s) {completedIds} finished successfully {runningInfo}".format(
                          completedIds = ','.join(completed_jobs),
                          runningInfo  = '(%s still running)' % ','.join(running_jobs) if running_jobs else '',
                        ))
                    # Mark successfully finished jobs as completed so that won't request their status code again
                    # Otherwise they will be still at ,,submitted'' state
                    for id_ in completed_jobs:
                        if not all(map(
                            lambda outputFile: is_file_ok(
                                outputFile, validate_outputs = True, min_file_size = self.min_file_size
                            ),
                            self.jobIds[id_]['outputFiles']
                          )):
                            if self.jobIds[id_]['nof_submissions'] < self.max_resubmissions:
                                logging.warning(
                                    "Job w/ ID {id} and arguments {args} FAILED to produce a valid output file "
                                    "-> resubmission attempt #{attempt}".format(
                                        id      = id_,
                                        args    = self.jobIds[id_]['args'],
                                        attempt = self.jobIds[id_]['nof_submissions'],
                                    )
                                )
                                self.submitJob(*self.jobIds[id_]['args'])
                                del self.jobIds[id_]
                            else:
                                raise ValueError(
                                    "Job w/ ID {id} FAILED because it repeatedly produces bogus output "
                                    "file {output} yet the job still exits w/o any errors".format(
                                        id     = id_,
                                        output = ', '.join(self.jobIds[id_]['outputFiles']),
                                    )
                                )
                        else:
                            # Job completed just fine
                            self.jobIds[id_]['status'] = Status.completed

            jobIds_set = set([ id_ for id_ in self.jobIds if self.jobIds[id_]['status'] == Status.submitted])
            nofJobs_left = len(jobIds_set)
            if nofJobs_left > 0:
                two_pow_sixteen = 65536
                random.seed((abs(hash(uuid.uuid4()))) % two_pow_sixteen)
                max_delay = 300
                random_delay = random.randint(0, max_delay)
                time.sleep(self.poll_interval + random_delay)
            else:
                break
            logging.info("Waiting for sbatch to finish (%d job(s) still left) ..." % nofJobs_left)
