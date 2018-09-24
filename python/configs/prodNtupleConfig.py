from tthAnalysis.HiggsToTauTau.jobTools import create_if_not_exists, run_cmd, get_log_version, record_software_state
from tthAnalysis.HiggsToTauTau.analysisTools import initDict, getKey, create_cfg, generateInputFileList
from tthAnalysis.HiggsToTauTau.analysisTools import createMakefile as tools_createMakefile
from tthAnalysis.HiggsToTauTau.sbatchManagerTools import createScript_sbatch as tools_createScript_sbatch

import os
import logging
import uuid
import ROOT

DKEY_CFGS       = "cfgs"
DKEY_NTUPLES    = "ntuples"
DKEY_LOGS       = "logs"
MAKEFILE_TARGET = "sbatch_prodNtuple"

DEPENDENCIES = [
    "", # CMSSW_BASE/src
    "tthAnalysis/HiggsToTauTau",
    "PhysicsTools/NanoAODTools",
    "tthAnalysis/NanoAODTools",
    "tthAnalysis/NanoAOD",
]

def get_pileup_histograms(pileup_filename):
    pileup_file = ROOT.TFile.Open(pileup_filename, 'read')
    keys = pileup_file.GetListOfKeys()
    histogram_names = [ key.GetName() for key in keys if key.GetClassName().startswith('TH1') ]
    pileup_file.Close()
    return histogram_names

class prodNtupleConfig:
    """Configuration metadata needed to run Ntuple production.

    Args:
        configDir:             The root config dir -- all configuration files are stored in its subdirectories
        outputDir:             The root output dir -- all log and output files are stored in its subdirectories
        debug:                 if True, checks each input root file (Ntuple) before creating the python configuration files
        running_method:        either `sbatch` (uses SLURM) or `Makefile`
        num_parallel_jobs:     number of jobs that can be run in parallel on local machine
                               (does not limit number of Ntuple production jobs running in parallel on batch system)

    """
    def __init__(self,
             configDir,
             outputDir,
             cfgFile_prodNtuple,
             samples,
             max_files_per_job,
             era,
             preselection_cuts,
             leptonSelection,
             hadTauSelection,
             check_output_files,
             running_method,
             version,
             num_parallel_jobs,
             pileup,
             golden_json,
             dry_run,
             isDebug,
             use_nonnominal,
             use_home,
             skip_tools_step,
             verbose = False,
             pool_id        = '',
          ):

        self.configDir             = configDir
        self.outputDir             = outputDir
        self.max_num_jobs          = 200000
        self.samples               = samples
        self.max_files_per_job     = max_files_per_job
        self.era                   = era
        self.preselection_cuts     = preselection_cuts
        self.leptonSelection       = leptonSelection
        self.hadTauSelection       = hadTauSelection
        self.check_output_files    = check_output_files
        self.verbose               = verbose
        self.dry_run               = dry_run
        self.isDebug               = isDebug
        self.use_nonnominal        = use_nonnominal
        self.use_home              = use_home
        self.pileup                = pileup
        self.golden_json           = golden_json
        if running_method.lower() not in ["sbatch", "makefile"]:
          raise ValueError("Invalid running method: %s" % running_method)

        if not os.path.isfile(self.pileup):
            raise ValueError('No such file: %s' % self.pileup)
        self.pileup_histograms = get_pileup_histograms(self.pileup)

        if not os.path.isfile(self.golden_json):
            raise ValueError('No such file: %s' % self.golden_json)

        self.running_method    = running_method
        self.is_sbatch         = self.running_method.lower() == "sbatch"
        self.is_makefile       = not self.is_sbatch
        self.makefile          = os.path.join(self.configDir, "Makefile_prodNtuple")
        self.num_parallel_jobs = num_parallel_jobs
        self.skip_tools_step   = skip_tools_step
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
        self.stdout_file_path = os.path.join(self.configDir, "stdout_prodNtuple.log")
        self.stderr_file_path = os.path.join(self.configDir, "stderr_prodNtuple.log")
        self.sw_ver_file_cfg  = os.path.join(self.configDir, "VERSION_prodNtuple.log")
        self.sw_ver_file_out  = os.path.join(self.outputDir, "VERSION_prodNtuple.log")
        self.stdout_file_path, self.stderr_file_path, self.sw_ver_file_cfg, self.sw_ver_file_out = get_log_version((
            self.stdout_file_path, self.stderr_file_path, self.sw_ver_file_cfg, self.sw_ver_file_out
        ))

        self.cfgFile_prodNtuple_original = os.path.join(self.template_dir, cfgFile_prodNtuple)
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
            if dir_type in [ DKEY_CFGS, DKEY_LOGS ]:
                self.dirs[dir_type] = os.path.join(self.configDir, dir_type)
            else:
                self.dirs[dir_type] = os.path.join(self.outputDir, dir_type)

        self.cvmfs_error_log = {}
        self.executable = "produceNtuple.sh"

    def createCfg_prodNtuple(self, jobOptions):
        """Create python configuration file for the prodNtuple executable (Ntuple production code)

        Args:
          inputFiles: list of input files (Ntuples)
          outputFile: output file of the job -- a ROOT file containing histogram
        """
        if self.skip_tools_step:
            inputFiles_prepended = jobOptions['inputFiles']
        else:
            inputFiles_prepended = map(lambda path: os.path.basename('%s_ii%s' % os.path.splitext(path)), jobOptions['inputFiles'])
        if len(inputFiles_prepended) != len(set(inputFiles_prepended)):
            raise ValueError("Not all input files have a unique base name: %s" % ', '.join(jobOptions['inputFiles']))

        lines = [
            "process.fwliteOutput.fileName                   = cms.string('%s')" % os.path.basename(jobOptions['outputFile']),
            "process.produceNtuple.era                       = cms.string('%s')" % self.era,
            "process.produceNtuple.minNumLeptons             = cms.int32(%i)"    % self.preselection_cuts['minNumLeptons'],
            "process.produceNtuple.minNumHadTaus             = cms.int32(%i)"    % self.preselection_cuts['minNumHadTaus'],
            "process.produceNtuple.minNumLeptons_and_HadTaus = cms.int32(%i)"    % self.preselection_cuts['minNumLeptons_and_HadTaus'],
            "process.produceNtuple.minNumJets                = cms.int32(%i)"    % self.preselection_cuts['minNumJets'],
            "process.produceNtuple.minNumBJets_loose         = cms.int32(%i)"    % self.preselection_cuts['minNumBJets_loose'],
            "process.produceNtuple.minNumBJets_medium        = cms.int32(%i)"    % self.preselection_cuts['minNumBJets_medium'],
            "process.produceNtuple.maxNumBJets_loose         = cms.int32(%i)"    % self.preselection_cuts['maxNumBJets_loose'],
            "process.produceNtuple.maxNumBJets_medium        = cms.int32(%i)"    % self.preselection_cuts['maxNumBJets_medium'],
            "process.produceNtuple.applyJetEtaCut            = cms.bool(%s)"     % self.preselection_cuts['applyJetEtaCut'],
            "process.produceNtuple.isMC                      = cms.bool(%s)"     % jobOptions['is_mc'],
            "process.produceNtuple.redoGenMatching           = cms.bool(%s)"     % (not self.skip_tools_step),
            "process.produceNtuple.leptonSelection           = cms.string('%s')" % self.leptonSelection,
            "process.produceNtuple.hadTauSelection           = cms.string('%s')" % self.hadTauSelection,
            "process.produceNtuple.random_seed               = cms.uint32(%i)"   % jobOptions['random_seed'],
            "process.produceNtuple.branchName_electrons      = cms.string('Electron')",
            "process.produceNtuple.branchName_muons          = cms.string('Muon')",
            "process.produceNtuple.branchName_hadTaus        = cms.string('Tau')",
            "process.produceNtuple.branchName_jets           = cms.string('Jet')",
            "process.produceNtuple.branchName_met            = cms.string('MET')",
            "process.produceNtuple.branchName_genLeptons     = cms.string('GenLep')",
            "process.produceNtuple.branchName_genHadTaus     = cms.string('GenVisTau')",
            "process.produceNtuple.branchName_genJets        = cms.string('GenJet')",
            "process.produceNtuple.isDEBUG                   = cms.bool(%s)"     % self.isDebug,
            "process.produceNtuple.useNonNominal             = cms.bool(%s)"     % self.use_nonnominal,
            "process.produceNtuple.branchNames_triggers      = cms.vstring(%s)"  % jobOptions['triggers'],
            "process.fwliteInput.fileNames                   = cms.vstring(%s)"  % inputFiles_prepended,
            "executable      = 'produceNtuple'",
            "inputFiles      = %s" % jobOptions['inputFiles'],
            "isMC            = %s" % str(jobOptions['is_mc']),
            "era             = %s" % str(self.era),
            "pileup          = '%s'" % self.pileup,
            "golden_json     = '%s'" % self.golden_json,
            "process_name    = '%s'" % jobOptions['process_name'],
            "skip_tools_step = %s" % self.skip_tools_step,
        ]
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
            job_template_file       = 'sbatch-node.produce.sh.template',
            dry_run                 = self.dry_run,
            use_home                = self.use_home,
            validate_outputs        = self.check_output_files,
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

            if is_mc and process_name not in self.pileup_histograms:
                raise ValueError("Missing PU distribution for %s in file %s" % (process_name, self.pileup))

            logging.info("Creating configuration files to run '%s' for sample %s" % (self.executable, process_name))

            inputFileList = generateInputFileList(sample_info, self.max_files_per_job)
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
                hlt_paths = sample_info["hlt_paths"] if not is_mc else []
                jobOptions = {
                    'inputFiles'       : self.inputFiles[key_file],
                    'cfgFile_modified' : self.cfgFiles_prodNtuple_modified[key_file],
                    'outputFile'       : self.outputFiles[key_file],
                    'is_mc'            : is_mc,
                    'random_seed'      : jobId,
                    'process_name'     : process_name,
                    'triggers'         : hlt_paths,
                }
                self.createCfg_prodNtuple(jobOptions)

        num_jobs = 0
        if self.is_sbatch:
            logging.info("Creating script for submitting '%s' jobs to batch system" % self.executable)
            num_jobs = self.createScript_sbatch()
            logging.info("Generated %i job(s)" % num_jobs)

        logging.info("Creating Makefile")
        lines_makefile = []
        self.addToMakefile_prodNtuple(lines_makefile)
        self.createMakefile(lines_makefile)

        logging.info("Done")
        return num_jobs

    def run(self):
        """Runs all Ntuple production jobs -- either locally or on the batch system.
        """
        record_software_state(self.sw_ver_file_cfg, self.sw_ver_file_out, DEPENDENCIES)
        run_cmd(
            "make -f %s -j %i 2>%s 1>%s" % \
            (self.makefile, self.num_parallel_jobs, self.stderr_file_path, self.stdout_file_path),
            False
        )
