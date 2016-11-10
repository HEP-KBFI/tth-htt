import codecs, getpass, jinja2, logging, os, time
from datetime import date

from tthAnalysis.HiggsToTauTau.jobTools import create_if_not_exists, run_cmd


# Template for wrapper that is ran on cluster node

current_dir = os.path.dirname(os.path.realpath(__file__))
job_template_file = current_dir + "/sbatch-node.template.sh"
job_template = open(job_template_file, 'r').read()


# Define SbatchManager

command_create_scratchDir = '/scratch/mkscratch'

class sbatchManager:
  """

  """
  def __init__(self):
    self.workingDir = None
    self.logFileDir = None
    ##self.queue = "short" # maximum run-time of job = 2 hours
    self.queue = "main" # maximum run-time of job = 2 days
    if os.environ.get('SBATCH_PRIORITY'):
      self.queue = os.environ.get('SBATCH_PRIORITY')
    self.command_submit = "sbatch"
    self.command_poll = "squeue"
    self.poll_interval = 30
    self.jobIds = []

  def setWorkingDir(self, workingDir):
    """Set path to CMSSW area in which jobs are executed
    """
    self.workingDir = workingDir

  def setLogFileDir(self, logFileDir):
    """Set path to directory in which log files are to be stored (matters only if 'logFile' parameter is not given when calling 'submitJob' method)
    """
    self.logFileDir = logFileDir

  def submitJob(self, inputFiles, executable, cfgFile, outputFilePath, outputFiles, logFile=None, skipIfOutputFileExists=False):
    """Waits for all sbatch jobs submitted by this instance of sbatchManager to finish processing
    """

    # raise if logfile missing
    if not logFile:
      if not self.logFileDir:
        raise ValueError("Please call 'setLogFileDir' before calling 'submitJob' !!")
      logFile = os.path.join(self.logFileDir, os.path.basename(scriptFile).replace(".sh", ".log"))


    # if any of the output files exists, returns (Margus: BUG? Because only that file should be skipped, not all?)
    if skipIfOutputFileExists:
      for outputFile in outputFiles:
        if os.path.exists(os.path.join(outputFilePath, outputFile)):
          print "output file = '%s' exists --> skipping !!" % os.path.join(outputFilePath, outputFile)
          return

    if not self.workingDir:
      raise ValueError("Please call 'setWorkingDir' before calling 'submitJob' !!")

    # create scratch dir
    scratchDir = "/scratch/%s" % getpass.getuser()
    if not os.path.exists(scratchDir):
      print "Directory '%s' does not yet exist, creating it !!" % scratchDir
      run_cmd(command_create_scratchDir)
    scratchDir = os.path.join(scratchDir, "tthAnalysis" + "_" + date.today().isoformat())
    create_if_not_exists(scratchDir)

    # create script for executing jobs
    scriptFile = cfgFile.replace(".py", ".sh")
    scriptFile = scriptFile.replace("_cfg", "")
    command = "%s --partition=%s %s" % (self.command_submit, self.queue, scriptFile)

    script = jinja2.Template(job_template).render(
      working_dir = self.workingDir,
      scratch_dir = scratchDir,
      exec_name = executable,
      cfg_file = cfgFile,
      inputFiles = " ".join(inputFiles),
      outputDir = outputFilePath,
      outputFiles = " ".join(outputFiles),
      wrapperLogFile = logFile.replace('.log', '_wrapper.log'),
      executableLogFile = logFile.replace('.log', '_executable.log'),
      RUNNING_COMMAND = command
      )
    print "writing sbatch script file = '%s'" % scriptFile
    with codecs.open(scriptFile, "w", "utf-8") as f: f.write(script)

    print "<submitJob>: command = %s" % command
    retVal = run_cmd(command).split()[-1]
    jobId = retVal.split()[-1]
    # print " jobId = %s" % jobId
    self.jobIds.append(jobId)

  def waitForJobs(self):
    """Waits for all sbatch jobs submitted by this instance of sbatchManager to finish processing
    """
    numJobs = len(self.jobIds)
    ##print "<waitForJobs>: numJobs = %i" % numJobs
    if numJobs > 0:
      jobIds_per_poll_group = 500
      num_poll_groups = numJobs / jobIds_per_poll_group
      if (numJobs % jobIds_per_poll_group) > 0:
        num_poll_groups = num_poll_groups + 1
      whoami = getpass.getuser()
      while True:
        numJobs_left = 0
        for idx_poll_group in range(num_poll_groups):
          idx_first = idx_poll_group*jobIds_per_poll_group
          idx_last = min((idx_poll_group + 1)*jobIds_per_poll_group, numJobs)
          jobIds_poll_group = self.jobIds[idx_first:idx_last]
          command = "%s -u %s | grep \"%s\" | wc -l" % (self.command_poll, whoami, "\\|".join(jobIds_poll_group))
          ##print "idx_poll_group = %i: command = %s" % (idx_poll_group, command)
          poll_result = run_cmd(command, True).rstrip("\n")
          ##print " poll_result = %s" % poll_result
          numJobs_left = numJobs_left + int(poll_result)
          time.sleep(1)
        ##print "numJobs_left = %i" % numJobs_left
        if numJobs_left > 0:
          time.sleep(self.poll_interval)
        else:
          break
        logging.info("Waiting for sbatch to finish (%d jobs still left) ..." % numJobs_left)
