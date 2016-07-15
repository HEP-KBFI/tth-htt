import codecs, getpass, jinja2, logging, os, time

from tthAnalysis.HiggsToTauTau.jobTools import run_cmd

job_template = """#!/bin/bash
echo "current time:"
date
echo "executing 'hostname':"
hostname
echo "initializing CMSSW run-time environment"
source /cvmfs/cms.cern.ch/cmsset_default.sh 
cd {{ working_dir }}
cmsenv
cd -
echo "executing 'pwd'"
pwd
{{ exec_name }} {{ cfg_file }}

"""

class sbatchManager:
  """

  """
  def __init__(self):
    self.workingDir = None
    self.logFileDir = None
    self.queue = "short"
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

  def submitJob(self, executable, cfgFile, logFile=None, skipIfOutputFileExists=False, outputFile=None):
    """Waits for all sbatch jobs submitted by this instance of sbatchManager to finish processing
    """  
    if skipIfOutputFileExists and os.path.exists(outputFile):
      return
    if not self.workingDir:
      raise ValueError("Please call 'setWorkingDir' before calling 'submitJob' !!")
    scriptFile = cfgFile.replace(".py", ".sh")
    scriptFile = scriptFile.replace("_cfg", "")
    script = jinja2.Template(job_template).render(working_dir = self.workingDir, exec_name = executable, cfg_file = cfgFile)
    with codecs.open(scriptFile, "w", "utf-8") as f: f.write(script)
    if not logFile:
      if not self.workingDir:
        raise ValueError("Please call 'setLogFileDir' before calling 'submitJob' !!")
      logFile = os.path.join(self.logFileDir, os.path.basename(scriptFile).replace(".sh", ".log"))
    command = "%s --partition=%s --output=%s %s" % (self.command_submit, self.queue, logFile, scriptFile)
    ##print "<submitJob>: command = %s" % command
    retVal = run_cmd(command).split()[-1]
    jobId = retVal.split()[-1]
    ##print " jobId = %s" % jobId
    self.jobIds.append(jobId)

  def waitForJobs(self):
    """Waits for all sbatch jobs submitted by this instance of sbatchManager to finish processing
    """    
    numJobs = len(self.jobIds)
    print "<waitForJobs>: numJobs = %i" % numJobs
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
          print "idx_poll_group = %i: command = %s" % (idx_poll_group, command)
          poll_result = run_cmd(command, True).rstrip("\n")
          print " poll_result = %s" % poll_result
          numJobs_left = numJobs_left + int(poll_result)
          time.sleep(1)
        print "numJobs_left = %i" % numJobs_left
        if numJobs_left > 0:
          time.sleep(self.poll_interval)
        else:
          break
        logging.info("Waiting for sbatch to finish (%d jobs still left) ..." % numJobs_left)
