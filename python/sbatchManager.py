import codecs, getpass, jinja2, logging, os, time
from datetime import date

from tthAnalysis.HiggsToTauTau.jobTools import create_if_not_exists, run_cmd


# Assumes that project dir is available on cluster node (example /home is shared)

CURRENT_FILE = os.path.abspath(__file__)
PROJECT_DIRECTORY = os.path.abspath(os.path.join(CURRENT_FILE, os.pardir))
FAILURE_WRAPPER = '/home/margusp/VHbbNtuples_7_6_x/CMSSW_7_6_3/src/tthAnalysis/HiggsToTauTau/scripts' # PROJECT_DIRECTORY + '/scripts/failure-wrapper.sh'


# Template for wrapper that is ran on cluster node

job_template = """#!/bin/bash

main() {
    run_wrapped_executable > {{ wrapperLogFile }} 2>&1
}

run_wrapped_executable() {
    export SCRATCH_DIR="{{ scratch_dir }}/$SLURM_JOBID"
    EXECUTABLE_LOG_FILE="{{ executableLogFile }}"
    EXECUTABLE_LOG_DIR="`dirname $EXECUTABLE_LOG_FILE`"
    EXECUTABLE_LOG_FILE_NAME="`basename $EXECUTABLE_LOG_FILE`"
    TEMPORARY_EXECUTABLE_LOG_DIR="$SCRATCH_DIR/$EXECUTABLE_LOG_DIR/"
    TEMPORARY_EXECUTABLE_LOG_FILE="$TEMPORARY_EXECUTABLE_LOG_DIR/$EXECUTABLE_LOG_FILE_NAME"

    echo "Time is: `date`"
    echo "Hostname: `hostname`"
    echo "Current directory: `pwd`"

    echo "Create scratch directory: mkdir -p $SCRATCH_DIR"
    mkdir -p $SCRATCH_DIR

    echo "Create temporary log directory: mkdir -p $TEMPORARY_EXECUTABLE_LOG_DIR"
    mkdir -p $TEMPORARY_EXECUTABLE_LOG_DIR

    echo "Create final log directory: mkdir -p $EXECUTABLE_LOG_DIR"
    mkdir -p $EXECUTABLE_LOG_DIR

    echo "Initialize CMSSW run-time environment: source /cvmfs/cms.cern.ch/cmsset_default.sh"
    source /cvmfs/cms.cern.ch/cmsset_default.sh
    cd {{ working_dir }}
    cmsenv
    cd $SCRATCH_DIR

    echo "Time is: `date`"

    echo "Copying contents of 'tthAnalysis/HiggsToTauTau/data' directory to Scratch: cp -rL $CMSSW_BASE/src/tthAnalysis/HiggsToTauTau/data/* $SCRATCH_DIR/tthAnalysis/HiggsToTauTau/data"
    mkdir -p tthAnalysis/HiggsToTauTau/data
    cp -rL $CMSSW_BASE/src/tthAnalysis/HiggsToTauTau/data/* $SCRATCH_DIR/tthAnalysis/HiggsToTauTau/data

    echo "Time is: `date`"

    CMSSW_SEARCH_PATH=$SCRATCH_DIR
    echo "Execute command: {{ FAILURE_WRAPPER }} \"{{ exec_name }} {{ cfg_file }} > $TEMPORARY_EXECUTABLE_LOG_FILE\""
    {{ FAILURE_WRAPPER }} "{{ exec_name }} {{ cfg_file }} > $TEMPORARY_EXECUTABLE_LOG_FILE"

    echo "Time is: `date`"

    OUTPUT_FILES="{{ outputFiles }}"
    echo "Copying output files: {{ outputFiles }}"
    EXIT_CODE=0
    for OUTPUT_FILE in $OUTPUT_FILES
    do
      OUTPUT_FILE_SIZE=$(stat -c '%s' $OUTPUT_FILE)
      if [ $OUTPUT_FILE_SIZE -ge 1000 ]; then
        echo "cp $OUTPUT_FILE {{ outputDir }}"
        cp $OUTPUT_FILE {{ outputDir }}
      else
        rm $OUTPUT_FILE
        EXIT_CODE=1
      fi
    done

    echo "Time is: `date`"

    echo "Contents of temporary log dir:"
    ls -laR $TEMPORARY_EXECUTABLE_LOG_DIR

    echo "Copy from temporary output dir to output dir: cp -a $TEMPORARY_EXECUTABLE_LOG_DIR/* $EXECUTABLE_LOG_DIR/"
    cp -a $TEMPORARY_EXECUTABLE_LOG_DIR/* $EXECUTABLE_LOG_DIR/

    echo "Delete Scratch directory: rm -r $SCRATCH_DIR"
    rm -r $SCRATCH_DIR

    echo "End time is: `date`"

    return $EXIT_CODE
}

main

"""

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
      FAILURE_WRAPPER = FAILURE_WRAPPER
      )
    print "writing sbatch script file = '%s'" % scriptFile
    with codecs.open(scriptFile, "w", "utf-8") as f: f.write(script)

    # start command and register it's ID, so it is possible to get status later
    # command = "%s --partition=%s --output=%s %s" % (self.command_submit, self.queue, logFile, scriptFile)
    command = "%s --partition=%s %s" % (self.command_submit, self.queue, scriptFile)
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
