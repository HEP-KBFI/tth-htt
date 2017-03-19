import codecs, getpass, jinja2, logging, os, time, subprocess, datetime, uuid, sys

from tthAnalysis.HiggsToTauTau.ClusterHistogramAggregator import ClusterHistogramAggregator
from tthAnalysis.HiggsToTauTau.jobTools import create_if_not_exists, run_cmd

# Template for wrapper that is ran on cluster node

current_dir       = os.path.dirname(os.path.realpath(__file__))
job_template_file = os.path.join(current_dir, 'sbatch-node.template.sh')
job_template      = open(job_template_file, 'r').read()

submit_job_version2_template_file = os.path.join(current_dir, 'sbatch-node.submit_job_version2_template.sh')
submit_job_version2_template      = open(submit_job_version2_template_file, 'r').read()

command_create_scratchDir = '/scratch/mkscratch'

# Define Status

class Status:
  submitted   = 1
  completed   = 2

# Define sbatchManagerError

class sbatchManagerError(Exception):
  pass

# Define sbatchManager

class sbatchManager:
    """Manages SLURM jobs

       About queue priorities:
         low - 2d (maybe 2w) time limit, availability dependent on load
         main - 2d time limit, good availability
         short - 2h time limit, very good availability
         prio - ? (10min?) time limit, available immediately
    """

    def __init__(self, uuid_str = '', verbose = True):
        self.workingDir     = None
        self.logFileDir     = None
        queue_environ = os.environ.get('SBATCH_PRIORITY')
        self.queue          = queue_environ if queue_environ else "low"
        self.poll_interval  = 30
        self.jobIds         = {}
        self.analysisName   = "tthAnalysis"
        self.user           = getpass.getuser()
        self.uuid           = uuid_str if uuid_str else uuid.uuid4()
        if verbose:
          self.unmute()
        else:
          self.mute()

    def setWorkingDir(self, workingDir):
        """Set path to CMSSW area in which jobs are executed
        """
        self.workingDir = workingDir

    def setLogFileDir(self, logFileDir):
        """Set path to directory in which log files are to be stored (matters only if 'logFile'
           parameter is not given when calling 'submitJob' method)
        """
        self.logFileDir = logFileDir

    def mute(self):
      self.setLogLevel(logging.INFO)

    def unmute(self):
      self.setLogLevel(logging.DEBUG)

    def setLogLevel(self, logLevel):
      logging.basicConfig(
        stream = sys.stdout,
        level  = logLevel,
        format = '[%(filename)s:%(funcName)s] %(asctime)s - %(levelname)s: %(message)s',
      )

    def hadd_in_cluster(
        self,
        inputFiles                  = None,
        outputFile                  = None,
        maximum_histograms_in_batch = 20,
        waitForJobs                 = True,
        auxDirName                  = None,
    ):
        cluster_histogram_aggregator = ClusterHistogramAggregator(
            input_histograms            = inputFiles,
            final_output_histogram      = outputFile,
            maximum_histograms_in_batch = maximum_histograms_in_batch,
            waitForJobs                 = waitForJobs,
            sbatch_manager              = self,
            auxDirName                  = auxDirName,
        )

        cluster_histogram_aggregator.create_output_histogram()

    def check_job_completion(self, jobsId_list, default_completion = True):
        completion = { k : default_completion for k in jobsId_list }

        # If the input list is empty, just return here (we don't want to mess up the subprocess commands here)
        if not completion:
          return completion

        # First, let's try with sacct
        sacct_cmd = "sacct -X -P -n -o JobID,ExitCode,DerivedExitCode,Comment | grep {comment}".format(comment = self.uuid)
        sacct_out, sacct_err = run_cmd(sacct_cmd, return_stderr = True)
        if not sacct_err and sacct_out:
            # The output of sacct contains one line per job, each line has pipe-separated fields the order of which
            # is defined in the command that issued the output
            lines = sacct_out.split('\n')
            for line in lines:
                JobID, ExitCode, DerivedExitCode, Comment = line.split('|')
                if JobID in completion:
                    completion[JobID] = (ExitCode == '0:0' and DerivedExitCode == '0:0')
            return completion
        else:
            # Likely returned along the lines of (due to heavy load on the cluster):
            # sacct: error: Problem talking to the database: Connection refused
            logging.info('sacct currently unavailable: %s' % sacct_err)

        #time.sleep(1) # enable for testing only?
        # Let's try with scontrol
        # scontrol doesn't have an option to take a list of Job IDs as an argument; thus, we have to grep the job IDs
        scontrol_cmd = "scontrol show -od job | grep 'Comment={comment}'".format(comment = self.uuid)
        scontrol_out, scontrol_err = run_cmd(scontrol_cmd, return_stderr = True)
        if not scontrol_err and scontrol_out:
            # The output of scontrol contains one entry per line, each line contains a space-delimited key-value pairs,
            # whereas the keys and values are separated by an equation sign
            # Although the keys do not contain any spaces, the values might, so we have to take care of that
            lines = scontrol_out.split('\n')
            for line in lines:
                line_dict = {}
                line_split_eq_spaces = map(lambda x: x.split(), line.split('='))
                for i in range(len(line_split_eq_spaces) - 1):
                    k = line_split_eq_spaces[i]
                    v = line_split_eq_spaces[i + 1]
                    line_dict[k[-1]] = ' '.join(v[:-1] if i != len(line_split_eq_spaces) - 2 else v)
                JobId = line_dict['JobId']
                if JobId in completion:
                    completion[JobId] = (line_dict['ExitCode'] == '0:0' and line_dict['DerivedExitCode'] == '0:0')
            return completion
        else:
            # scontrol probably returned something like:
            # slurm_load_jobs error: Invalid job id specified
            # Probably because too much time has passed since the job completion and checking the exit status here
            logging.info('scontrol has errors: %s' % scontrol_err)

        # None of the SLURM commands work; let's just say that the job completed successfully
        logging.error("Cannot tell if the job has been completed or not!")
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

    def submitJob(self, inputFiles, executable, cfgFile, outputFilePath, outputFiles,
                  logFile = None, skipIfOutputFileExists = False):
        """Waits for all sbatch jobs submitted by this instance of sbatchManager to finish processing
        """
        # raise if logfile missing
        if not logFile:
            if not self.logFileDir:
                raise ValueError("Please call 'setLogFileDir' before calling 'submitJob' !!")
            logFile = os.path.join(self.logFileDir, os.path.basename(script_file).replace(".sh", ".log"))

        # skip only if none of the output files are missing in the file system
        if skipIfOutputFileExists:
            outputFiles_fullpath = map(lambda outputFile: os.path.join(outputFilePath, outputFile), outputFiles)
            outputFiles_missing = [outputFile for outputFile in outputFiles_fullpath if not os.path.exists(outputFile)]
            if not outputFiles_missing:
                logging.debug(
                  "output file(s) = %s exist(s) --> skipping !!" % \
                  '; '.join(map(lambda x: "'%s'" % x, outputFiles_fullpath))
                )
                return

        if not self.workingDir:
            raise ValueError("Please call 'setWorkingDir' before calling 'submitJob' !!")

        scratch_dir = self.get_scratch_dir()

        # create script for executing jobs
        script_file         = cfgFile.replace(".py", ".sh").replace("_cfg", "")
        wrapper_log_file    = logFile.replace('.log', '_wrapper.log')
        executable_log_file = logFile.replace('.log', '_executable.log')

        sbatch_command = "sbatch --partition={partition} --output={output} --comment='{comment}' {cmd}".format(
          partition = self.queue,
          output    = wrapper_log_file,
          comment   = self.uuid,
          cmd       = script_file,
        )

        script = jinja2.Template(job_template).render(
            working_dir         = self.workingDir,
            scratch_dir         = scratch_dir,
            exec_name           = executable,
            cfg_file            = cfgFile,
            inputFiles          = " ".join(inputFiles),
            outputDir           = outputFilePath,
            outputFiles         = " ".join(outputFiles),
            wrapper_log_file    = wrapper_log_file,
            executable_log_file = executable_log_file,
            RUNNING_COMMAND     = sbatch_command,
        )
        logging.debug("writing sbatch script file = '%s'" % script_file)
        with codecs.open(script_file, "w", "utf-8") as f:
            f.write(script)

        self.jobIds[self.submit(sbatch_command)] = Status.submitted

    def submit_job_version2(
        self,
        task_name  = None,
        command    = None,
        output_dir = None
    ):
        '''This method is similar to submitJob, but has less required parameters.
           Supports multiple lines of Bash commands instead of fixed oneliner.
        '''
        logging.debug("task_name=%s, command=%s, output_dir=%s)" % (task_name, command, output_dir))

        if not self.workingDir:
            raise ValueError("Please call 'setWorkingDir' before calling 'submitJob' !!")

        scratch_dir = self.get_scratch_dir()

        # Create script for executing jobs

        cfg_dir = os.path.join(output_dir, 'cfgs')
        log_dir = os.path.join(output_dir, 'logs')
        script_file         = os.path.join(cfg_dir, '%s.sh' % task_name)
        wrapper_log_file    = os.path.join(log_dir, '%s_wrapper.log' % task_name)
        executable_log_file = os.path.join(log_dir, '%s_executable.log' % task_name)
        create_if_not_exists(cfg_dir)
        create_if_not_exists(log_dir)

        sbatch_command = "sbatch --partition={partition} --output={output} --comment='{comment}' {cmd}".format(
            partition = self.queue,
            output    = wrapper_log_file,
            comment   = self.uuid,
            cmd       = script_file,
        )

        script = jinja2.Template(submit_job_version2_template).render(
            command             = command,
            working_dir         = self.workingDir,
            scratch_dir         = scratch_dir,
            wrapper_log_file    = wrapper_log_file,
            executable_log_file = executable_log_file,
            sbatch_command      = sbatch_command,
        )
        logging.debug("writing sbatch script file = '%s'" % script_file)
        with codecs.open(script_file, "w", "utf-8") as f:
            f.write(script)
            f.flush()
            os.fsync(f.fileno())

        self.jobIds[self.submit(sbatch_command)] = Status.submitted

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
        command_template = "squeue -u {{user}} -o '%i %36k' | grep {{uuid}} | awk '{print $1}'"
        command = jinja2.Template(command_template).render(
          user = self.user,
          uuid = self.uuid,
        )

        jobIds_set = set([ k for k in self.jobIds if self.jobIds[k] == Status.submitted])
        nofJobs_left = len(jobIds_set)
        while nofJobs_left > 0:
            poll_result = run_cmd(command, do_not_log = False)
            polled_ids = set(poll_result.split('\n'))
            finished_ids = list(jobIds_set - polled_ids)

            if finished_ids:
                # based on job's exit code what if the job has failed or completed successfully
                completion = self.check_job_completion(finished_ids)
                failed_jobs = [k for k in completion if not completion[k]]
                if failed_jobs:
                    failed_jobs_str = ','.join(failed_jobs)
                    logging.error("Job(s) w/ ID(s) {jobIds} finished with errors".format(jobIds = failed_jobs_str))
                    raise sbatchManagerError("Job w/ IDs %s failed" % failed_jobs_str)
                else:
                    logging.debug("Job(s) w/ ID(s) {jobIds} finished successfully".format(jobIds = ','.join(completion.keys())))
                for completed_id in completion:
                    self.jobIds[completed_id] = Status.completed

            jobIds_set = set([ k for k in self.jobIds if self.jobIds[k] == Status.submitted])
            nofJobs_left = len(jobIds_set)
            if nofJobs_left > 0:
                time.sleep(self.poll_interval)
            else:
                break
            logging.info("Waiting for sbatch to finish (%d job(s) still left) ..." % nofJobs_left)


    def log_ram_and_cpu_usage_information(self, log_file = None):
        info_params = {
          'job_ids' : ",".join(self.jobIds.keys()),
          'log_file': log_file,
        }
        ram_and_cpu_info = run_cmd(
          'sacct --long --jobs=%(job_ids)s > %(log_file)s; cat %(log_file)s;' % info_params
        )
