import os, logging, uuid

from tthAnalysis.HiggsToTauTau.jobTools import create_if_not_exists, run_cmd, get_log_version
from tthAnalysis.HiggsToTauTau.analysisTools import initDict, getKey, create_cfg, generateInputFileList
from tthAnalysis.HiggsToTauTau.analysisTools import createMakefile as tools_createMakefile
from tthAnalysis.HiggsToTauTau.sbatchManagerTools import createScript_sbatch as tools_createScript_sbatch

DKEY_CFGS       = "cfgs"
DKEY_HISTO      = "histograms"
DKEY_LOGS       = "logs"
MAKEFILE_TARGET = "sbatch_puProfile"

class puHistogramConfig:
    """Configuration metadata needed to run Ntuple production.

    Args:
        configDir:             The root config dir -- all configuration files are stored in its subdirectories
        outputDir:             The root output dir -- all log and output files are stored in its subdirectories
        executable_puProfile: Name of the executable that runs the Ntuple production
        debug:                 if True, checks each input root file (Ntuple) before creating the python configuration files
        running_method:        either `sbatch` (uses SLURM) or `Makefile`
        num_parallel_jobs:     number of jobs that can be run in parallel on local machine
                               (does not limit number of Ntuple production jobs running in parallel on batch system)

    """
    def __init__(self, configDir, outputDir, executable,
                 samples, max_files_per_job, era, check_input_files, running_method,
                 version, num_parallel_jobs, pool_id = '', verbose = False, dry_run = False):

        self.configDir             = configDir
        self.outputDir             = outputDir
        self.executable            = executable
        self.max_num_jobs          = 200000
        self.samples               = samples
        self.max_files_per_job     = max_files_per_job
        self.era                   = era
        self.check_input_files     = check_input_files
        self.verbose               = verbose
        self.dry_run               = dry_run
        if running_method.lower() not in ["sbatch", "makefile"]:
          raise ValueError("Invalid running method: %s" % running_method)

        self.running_method    = running_method
        self.is_sbatch         = self.running_method.lower() == "sbatch"
        self.is_makefile       = not self.is_sbatch
        self.makefile          = os.path.join(self.configDir, "Makefile_puProfile")
        self.num_parallel_jobs = num_parallel_jobs
        self.pool_id           = pool_id if pool_id else uuid.uuid4()

        self.workingDir = os.getcwd()
        logging.info("Working directory is: %s" % self.workingDir)
        self.template_dir = os.path.join(
            os.getenv('CMSSW_BASE'), 'src', 'tthAnalysis', 'HiggsToTauTau', 'test', 'templates'
        )
        logging.info("Templates directory is: %s" % self.template_dir)

        self.version = version
        self.samples = samples

        create_if_not_exists(self.configDir)
        create_if_not_exists(self.outputDir)
        self.stdout_file_path = os.path.join(self.configDir, "stdout_puProfile.log")
        self.stderr_file_path = os.path.join(self.configDir, "stderr_puProfile.log")
        self.stdout_file_path, self.stderr_file_path = get_log_version((
            self.stdout_file_path, self.stderr_file_path,
        ))

        self.sbatchFile_puProfile = os.path.join(self.configDir, "sbatch_puProfile.py")
        self.cfgFiles_puProfile_modified = {}
        self.logFiles_puProfile          = {}

        self.inputFiles   = {}
        self.outputFiles  = {}
        self.filesToClean = []
        self.dirs         = {}
        for sample_name, sample_info in self.samples.items():
            if not sample_info["use_it"]:
                continue
            process_name = sample_info["process_name_specific"]
            key_dir = getKey(sample_name)
            for dir_type in [ DKEY_CFGS, DKEY_HISTO, DKEY_LOGS ]:
                initDict(self.dirs, [ key_dir, dir_type ])
                if dir_type in [ DKEY_CFGS, DKEY_LOGS ]:
                    self.dirs[key_dir][dir_type] = os.path.join(self.configDir, dir_type, process_name)
                else:
                    self.dirs[key_dir][dir_type] = os.path.join(self.outputDir, dir_type, process_name)
        for dir_type in [ DKEY_CFGS, DKEY_LOGS ]:
            initDict(self.dirs, [ dir_type ])
            if dir_type in [ DKEY_CFGS, DKEY_HISTO, DKEY_LOGS ]:
                self.dirs[dir_type] = os.path.join(self.configDir, dir_type)
            else:
                self.dirs[dir_type] = os.path.join(self.outputDir, dir_type)

        self.cvmfs_error_log = {}

    def createCfg_puProfile(self, jobOptions):
        """Create python configuration file for the puProfile.sh script

        Args:
          inputFiles: list of input files (Ntuples)
          outputFile: output file of the job -- a ROOT file containing histogram
        """
        pass

    def createScript_sbatch(self):
        """Creates the python script necessary to submit the Ntuple production jobs to the batch system
        """
        pass

    def addToMakefile_puProfile(self, lines_makefile):
        """Adds the commands to Makefile that are necessary for running the Ntuple production code
        """
        pass

    def createMakefile(self, lines_makefile):
        """Creates Makefile that runs the Ntuple production.
        """
        pass

    def create(self):
        """Creates all necessary config files and runs the Ntuple production -- either locally or on the batch system
        """

        for key in self.dirs.keys():
            if type(self.dirs[key]) == dict:
                for dir_type in self.dirs[key].keys():
                    create_if_not_exists(self.dirs[key][dir_type])
            else:
                create_if_not_exists(self.dirs[key])

        self.inputFileIds = {}
        for sample_name, sample_info in self.samples.items():
            process_name = sample_info["process_name_specific"]
            is_mc = (sample_info["type"] == "mc")

            if not is_mc:
              continue

            logging.info("Creating configuration files to run '%s' for sample %s" % (self.executable, process_name))

            inputFileList = generateInputFileList(sample_info, self.max_files_per_job, self.check_input_files)
            key_dir = getKey(sample_name)
            for jobId in inputFileList.keys():

                key_file = getKey(sample_name, jobId)

                self.inputFiles[key_file] = inputFileList[jobId]
                if len(self.inputFiles[key_file]) == 0:
                    logging.warning(
                        "ntupleFiles['%s'] = %s --> skipping job !!" % (key_file, self.inputFiles[key_file])
                    )
                    continue

                jobOptions = {
                }
                self.createCfg_puProfile(jobOptions)

        return 0

    def run(self):
        """Runs all Ntuple production jobs -- either locally or on the batch system.
        """
        pass
