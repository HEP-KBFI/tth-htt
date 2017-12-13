import codecs, os, logging, uuid

from tthAnalysis.HiggsToTauTau.jobTools import create_if_not_exists, run_cmd, get_log_version
from tthAnalysis.HiggsToTauTau.analysisTools import initDict, getKey, create_cfg, generateInputFileList
from tthAnalysis.HiggsToTauTau.analysisTools import createMakefile as tools_createMakefile
from tthAnalysis.HiggsToTauTau.sbatchManagerTools import createScript_sbatch as tools_createScript_sbatch

DKEY_CFGS       = "cfgs"
DKEY_NTUPLES    = "ntuples"
DKEY_LOGS       = "logs"
MAKEFILE_TARGET = "sbatch_prodNtuple"

class prodNtupleConfig:
    """Configuration metadata needed to run Ntuple production.

    Args:
        configDir:             The root config dir -- all configuration files are stored in its subdirectories
        outputDir:             The root output dir -- all log and output files are stored in its subdirectories
        executable_prodNtuple: Name of the executable that runs the Ntuple production
        debug:                 if True, checks each input root file (Ntuple) before creating the python configuration files
        running_method:        either `sbatch` (uses SLURM) or `Makefile`
        num_parallel_jobs:     number of jobs that can be run in parallel on local machine
                               (does not limit number of Ntuple production jobs running in parallel on batch system)

    """
    def __init__(self, configDir, outputDir, executable_prodNtuple, executable_nanoAOD,
                 cfgFile_prodNtuple, samples, max_files_per_job, era, preselection_cuts,
                 leptonSelection, hadTauSelection, nanoaod_prep, debug, running_method, version,
                 num_parallel_jobs, pool_id = '', verbose = False, dry_run = False):

        self.configDir             = configDir
        self.outputDir             = outputDir
        self.executable_prodNtuple = executable_prodNtuple
        self.executable_nanoAOD    = executable_nanoAOD
        self.max_num_jobs          = 200000
        self.samples               = samples
        self.max_files_per_job     = max_files_per_job
        self.era                   = era
        self.preselection_cuts     = preselection_cuts
        self.leptonSelection       = leptonSelection
        self.hadTauSelection       = hadTauSelection
        self.nanoaod_prep          = nanoaod_prep
        self.debug                 = debug
        self.verbose               = verbose
        self.dry_run               = dry_run
        if running_method.lower() not in ["sbatch", "makefile"]:
          raise ValueError("Invalid running method: %s" % running_method)

        if self.nanoaod_prep:
            self.executable = self.executable_nanoAOD
        else:
            self.executable = self.executable_prodNtuple

        self.running_method    = running_method
        self.is_sbatch         = self.running_method.lower() == "sbatch"
        self.is_makefile       = not self.is_sbatch
        self.makefile          = os.path.join(self.configDir, "Makefile_prodNtuple")
        self.num_parallel_jobs = num_parallel_jobs
        self.pool_id           = pool_id if pool_id else uuid.uuid4()

        self.workingDir = os.getcwd()
        logging.info("Working directory is: %s" % self.workingDir)

        self.version = version
        self.samples = samples

        create_if_not_exists(self.configDir)
        create_if_not_exists(self.outputDir)
        stdout_file_path = os.path.join(self.configDir, "stdout_prodNtuple.log")
        stderr_file_path = os.path.join(self.configDir, "stderr_prodNtuple.log")
        stdout_file_path, stderr_file_path = get_log_version((stdout_file_path, stderr_file_path))
        self.stdout_file = codecs.open(stdout_file_path, 'w', 'utf-8')
        self.stderr_file = codecs.open(stderr_file_path, 'w', 'utf-8')

        self.cfgFile_prodNtuple_original = os.path.join(self.workingDir, cfgFile_prodNtuple)
        self.sbatchFile_prodNtuple       = os.path.join(self.configDir, "sbatch_prodNtuple.py")
        self.cfgFiles_prodNtuple_modified = {}
        self.logFiles_prodNtuple          = {}

        self.inputFiles   = {}
        self.outputFiles  = {}
        self.filesToClean = []
        self.dirs         = {}
        for sample_name, sample_info in self.samples.items():
            if not sample_info["use_it"]:
                continue
            process_name = sample_info["process_name_specific"]
            key_dir = getKey(sample_name)
            for dir_type in [ DKEY_CFGS, DKEY_NTUPLES, DKEY_LOGS ]:
                initDict(self.dirs, [ key_dir, dir_type ])
                if dir_type in [ DKEY_CFGS, DKEY_LOGS ]:
                    self.dirs[key_dir][dir_type] = os.path.join(self.configDir, dir_type, process_name)
                else:
                    self.dirs[key_dir][dir_type] = os.path.join(self.outputDir, dir_type, process_name)
        for dir_type in [ DKEY_CFGS, DKEY_LOGS ]:
            initDict(self.dirs, [ dir_type ])
            if dir_type in [ DKEY_CFGS, DKEY_NTUPLES, DKEY_LOGS ]:
                self.dirs[dir_type] = os.path.join(self.configDir, dir_type)
            else:
                self.dirs[dir_type] = os.path.join(self.outputDir, dir_type)

        self.cvmfs_error_log = {}

    def createCfg_prodNtuple(self, jobOptions):
        """Create python configuration file for the prodNtuple executable (Ntuple production code)

        Args:
          inputFiles: list of input files (Ntuples)
          outputFile: output file of the job -- a ROOT file containing histogram
        """
        lines = [
            "process.fwliteOutput.fileName                         = cms.string('%s')" % os.path.basename(jobOptions['outputFile']),
            "process.produceNtuple.era                             = cms.string('%s')" % self.era,
            "process.produceNtuple.use_HIP_mitigation_mediumMuonId = cms.bool(%s)"     % jobOptions['use_HIP_mitigation_mediumMuonId'],
            "process.produceNtuple.minNumLeptons                   = cms.int32(%i)"    % self.preselection_cuts['minNumLeptons'],
            "process.produceNtuple.minNumHadTaus                   = cms.int32(%i)"    % self.preselection_cuts['minNumHadTaus'],
            "process.produceNtuple.minNumLeptons_and_HadTaus       = cms.int32(%i)"    % self.preselection_cuts['minNumLeptons_and_HadTaus'],
            "process.produceNtuple.minNumJets                      = cms.int32(%i)"    % self.preselection_cuts['minNumJets'],
            "process.produceNtuple.minNumBJets_loose               = cms.int32(%i)"    % self.preselection_cuts['minNumBJets_loose'],
            "process.produceNtuple.minNumBJets_medium              = cms.int32(%i)"    % self.preselection_cuts['minNumBJets_medium'],
            "process.produceNtuple.isMC                            = cms.bool(%s)"     % jobOptions['is_mc'],
            "process.produceNtuple.leptonSelection                 = cms.string('%s')" % self.leptonSelection,
            "process.produceNtuple.hadTauSelection                 = cms.string('%s')" % self.hadTauSelection,
            "process.produceNtuple.random_seed                     = cms.uint32(%i)"   % jobOptions['random_seed'],
            "process.produceNtuple.branchName_electrons            = cms.string('Electron')",
            "process.produceNtuple.branchName_muons                = cms.string('Muon')",
            "process.produceNtuple.branchName_hadTaus              = cms.string('Tau')",
            "process.produceNtuple.branchName_jets                 = cms.string('Jet')",
            "process.produceNtuple.branchName_met                  = cms.string('MET')",
            "process.produceNtuple.branchName_genLeptons1          = cms.string('GenLep')",
            "process.produceNtuple.branchName_genLeptons2          = cms.string('')",
            "process.produceNtuple.branchName_genHadTaus           = cms.string('GenVisTau')",
            "process.produceNtuple.branchName_genJets              = cms.string('GenJet')",
        ]
        if self.nanoaod_prep:
            inputFiles_prepended = map(lambda path: os.path.basename('%s_ii%s' % os.path.splitext(path)), jobOptions['inputFiles'])
            if len(inputFiles_prepended) != len(set(inputFiles_prepended)):
                raise ValueError("Not all input files have a unique base name: %s" % ', '.join(jobOptions['inputFiles']))
            lines.extend([
                "process.fwliteInput.fileNames                         = cms.vstring(%s)"  % inputFiles_prepended,
                "inputFiles = %s"   % jobOptions['inputFiles'],
                "executable = '%s'" % self.executable_prodNtuple,
            ])
        else:
            lines.extend([
                "process.fwliteInput.fileNames                         = cms.vstring(%s)" % jobOptions['inputFiles'],
            ])
        create_cfg(self.cfgFile_prodNtuple_original, jobOptions['cfgFile_modified'], lines)

    def createScript_sbatch(self):
        """Creates the python script necessary to submit the Ntuple production jobs to the batch system
        """
        num_jobs = tools_createScript_sbatch(
            sbatch_script_file_name = self.sbatchFile_prodNtuple,
            executable              = self.executable,
            command_line_parameters = self.cfgFiles_prodNtuple_modified,
            input_file_names        = self.inputFiles,
            output_file_names       = self.outputFiles,
            script_file_names       = {
                key : value.replace(".py", ".sh").replace("_cfg", "") for key, value in self.cfgFiles_prodNtuple_modified.items()
            },
            log_file_names          = self.logFiles_prodNtuple,
            working_dir             = self.workingDir,
            max_num_jobs            = self.max_num_jobs,
            cvmfs_error_log         = self.cvmfs_error_log,
            pool_id                 = self.pool_id,
            verbose                 = self.verbose,
            job_template_file       = 'sbatch-node.template.produce.sh',
            dry_run                 = self.dry_run,
        )
        return num_jobs

    def addToMakefile_prodNtuple(self, lines_makefile):
        """Adds the commands to Makefile that are necessary for running the Ntuple production code
        """
        if self.is_sbatch:
            lines_makefile.extend([
                "%s:" % MAKEFILE_TARGET,
                "\t%s %s" % ("python", self.sbatchFile_prodNtuple),
                "",
            ])
        for key_file, output_file in self.outputFiles.items():
            cfg_file_prodNtuple_modified = self.cfgFiles_prodNtuple_modified[key_file]
            if self.is_makefile:
                cfg_file = cfg_file_prodNtuple_modified
                log_file = self.logFiles_prodNtuple[key_file]
                lines_makefile.extend([
                    "%s:" % output_file,
                    "\t%s %s &> %s" % (self.executable, cfg_file, log_file),
                    "",
                ])
            elif self.is_sbatch:
                lines_makefile.extend([
                    "%s: %s" % (output_file, MAKEFILE_TARGET),
                    "\t%s" % ":",
                    "",
                ])
            self.filesToClean.append(output_file)

    def createMakefile(self, lines_makefile):
        """Creates Makefile that runs the Ntuple production.
        """
        targets = None
        if self.is_sbatch:
            targets = [ MAKEFILE_TARGET ]
        else:
            targets = self.outputFiles.values()
        tools_createMakefile(self.makefile, targets, lines_makefile, self.filesToClean)
        logging.info("Run it with:\tmake -f %s -j %i " % (self.makefile, self.num_parallel_jobs))

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
            if not sample_info["use_it"]:
                continue

            process_name = sample_info["process_name_specific"]
            is_mc = (sample_info["type"] == "mc")

            logging.info("Creating configuration files to run '%s' for sample %s" % (self.executable, process_name))

            inputFileList = generateInputFileList(sample_name, sample_info, self.max_files_per_job, self.debug)
            key_dir = getKey(sample_name)
            subDirs = list(map(
                lambda y: os.path.join(self.dirs[key_dir][DKEY_NTUPLES], '%04d' % y),
                set(map(lambda x: x // 1000, inputFileList.keys()))
            ))
            for subDir in subDirs:
                create_if_not_exists(subDir)
            for jobId in inputFileList.keys():

                key_file = getKey(sample_name, jobId)

                self.inputFiles[key_file] = inputFileList[jobId]
                if len(self.inputFiles[key_file]) == 0:
                    logging.warning(
                        "ntupleFiles['%s'] = %s --> skipping job !!" % (key_file, self.inputFiles[key_file])
                    )
                    continue
                self.cfgFiles_prodNtuple_modified[key_file] = os.path.join(
                    self.dirs[key_dir][DKEY_CFGS], "produceNtuple_%s_%i_cfg.py" % (process_name, jobId)
                )
                self.outputFiles[key_file] = os.path.join(
                    self.dirs[key_dir][DKEY_NTUPLES], "%04d" % (jobId // 1000), "tree_%i.root" % jobId
                )
                self.logFiles_prodNtuple[key_file] = os.path.join(
                    self.dirs[key_dir][DKEY_LOGS], "produceNtuple_%s_%i.log" % (process_name, jobId)
                )
                jobOptions = {
                    'inputFiles'                      : self.inputFiles[key_file],
                    'cfgFile_modified'                : self.cfgFiles_prodNtuple_modified[key_file],
                    'outputFile'                      : self.outputFiles[key_file],
                    'use_HIP_mitigation_mediumMuonId' : True,
                    'is_mc'                           : is_mc,
                    'random_seed'                     : jobId,
                }
                self.createCfg_prodNtuple(jobOptions)

        if self.is_sbatch:
            logging.info("Creating script for submitting '%s' jobs to batch system" % self.executable)
            num_jobs = self.createScript_sbatch()
            logging.info("Generated %i job(s)" % num_jobs)

        logging.info("Creating Makefile")
        lines_makefile = []
        self.addToMakefile_prodNtuple(lines_makefile)
        self.createMakefile(lines_makefile)

        logging.info("Done")

    def run(self):
        """Runs all Ntuple production jobs -- either locally or on the batch system.
        """
        run_cmd(
            "make -f %s -j %i " % (self.makefile, self.num_parallel_jobs),
            False, self.stdout_file, self.stderr_file,
        )
