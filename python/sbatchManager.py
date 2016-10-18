import codecs, getpass, jinja2, logging, os, time
from datetime import date

from tthAnalysis.HiggsToTauTau.jobTools import create_if_not_exists, run_cmd

job_template = """#!/bin/bash
echo "job start time:"
date
echo "hostname:"
hostname
echo "current directory:"
pwd
SCRATCH_DIR="{{ scratch_dir }}/${SLURM_JOBID}"
echo "creating scratch directory = '${SCRATCH_DIR}'"
mkdir -p ${SCRATCH_DIR}
echo "it is now:"
date
##echo "copying Ntuple input files"
##INPUT_FILES="{{ inputFiles }}"
##for INPUT_FILE in $INPUT_FILES
##do
##  cp $INPUT_FILE ${SCRATCH_DIR}
##  if [ ! -f ${SCRATCH_DIR}/${INPUT_FILE##*/} ];
##  then
##    echo "Failed to copy ${INPUT_FILE} to scratch directory !!"
##    exit 1
##  fi
##done
##echo "it is now:"
##date
echo "initializing CMSSW run-time environment"
source /cvmfs/cms.cern.ch/cmsset_default.sh 
cd {{ working_dir }}
cmsenv
cd ${SCRATCH_DIR}
echo "it is now:"
date
echo "copying content of 'tthAnalysis/HiggsToTauTau/data' directory"
mkdir -p tthAnalysis/HiggsToTauTau/data
cp -rL $CMSSW_BASE/src/tthAnalysis/HiggsToTauTau/data/* ${SCRATCH_DIR}/tthAnalysis/HiggsToTauTau/data
echo "it is now:"
date
echo "executing '{{ exec_name }}'"
CMSSW_SEARCH_PATH=${SCRATCH_DIR}
{{ exec_name }} {{ cfg_file }}
echo "it is now:"
date
echo "copying output files"
OUTPUT_FILES="{{ outputFiles }}"
EXIT_CODE=0
for OUTPUT_FILE in $OUTPUT_FILES
do
  OUTPUT_FILE_SIZE=$(stat -c '%s' $OUTPUT_FILE)
  if [ $OUTPUT_FILE_SIZE -ge 1000 ]; then
    cp $OUTPUT_FILE {{ outputDir }}
  else
    rm $OUTPUT_FILE
    EXIT_CODE=1
  fi
done
echo "it is now:"
date
echo "deleting scratch directory"
rm -r ${SCRATCH_DIR}
echo "job end time:"
date
exit ${EXIT_CODE}
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
    if skipIfOutputFileExists:
      for outputFile in outputFiles:
        if os.path.exists(os.path.join(outputFilePath, outputFile)):
          print "output file = '%s' exists --> skipping !!" % os.path.join(outputFilePath, outputFile)
          return
    if not self.workingDir:
      raise ValueError("Please call 'setWorkingDir' before calling 'submitJob' !!")
    scratchDir = "/scratch/%s" % getpass.getuser()
    if not os.path.exists(scratchDir):
      print "Directory '%s' does not yet exist, creating it !!" % scratchDir
      run_cmd(command_create_scratchDir)
    scratchDir = os.path.join(scratchDir, "tthAnalysis" + "_" + date.today().isoformat())  
    create_if_not_exists(scratchDir)
    scriptFile = cfgFile.replace(".py", ".sh")
    scriptFile = scriptFile.replace("_cfg", "")
    script = jinja2.Template(job_template).render(
      working_dir = self.workingDir,
      scratch_dir = scratchDir,
      exec_name = executable, cfg_file = cfgFile,
      inputFiles = " ".join(inputFiles), outputDir = outputFilePath, outputFiles = " ".join(outputFiles))
    print "writing sbatch script file = '%s'" % scriptFile
    with codecs.open(scriptFile, "w", "utf-8") as f: f.write(script)
    if not logFile:
      if not self.logFileDir:
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
