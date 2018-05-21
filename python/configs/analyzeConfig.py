import os, logging, uuid, inspect

from tthAnalysis.HiggsToTauTau.jobTools import create_if_not_exists, run_cmd, generate_file_ids, get_log_version
from tthAnalysis.HiggsToTauTau.analysisTools import initDict, getKey, create_cfg, createFile
from tthAnalysis.HiggsToTauTau.analysisTools import createMakefile as tools_createMakefile
from tthAnalysis.HiggsToTauTau.sbatchManagerTools import createScript_sbatch as tools_createScript_sbatch
from tthAnalysis.HiggsToTauTau.sbatchManagerTools import createScript_sbatch_hadd as tools_createScript_sbatch_hadd
from tthAnalysis.HiggsToTauTau.analysisSettings import Triggers

# dir for python configuration and batch script files for each analysis job
DKEY_CFGS = "cfgs"
# dir for ROOT files containing histograms = output of the anaysis jobs
DKEY_HIST = "histograms"
DKEY_PLOT = "plots"       # dir for control plots (prefit)
DKEY_SCRIPTS = "scripts"  # dir for sbatchManagers scripts that submit analysis and hadd jobs to batch system
DKEY_LOGS = "logs"        # dir for log files (stdout/stderr of jobs)
DKEY_DCRD = "datacards"   # dir for the datacard
DKEY_RLES = "output_rle"  # dir for the selected run:lumi:event numbers
DKEY_ROOT = "output_root" # dir for the selected events dumped into a root file
DKEY_HADD_RT = "hadd_cfg_rt" # dir for hadd cfg files generated during the runtime
DKEY_SYNC = 'sync_ntuple' # dir for storing sync Ntuples

executable_rm = 'rm'

DIRLIST = [ DKEY_CFGS, DKEY_DCRD, DKEY_HIST, DKEY_PLOT, DKEY_SCRIPTS, DKEY_LOGS, DKEY_RLES, DKEY_ROOT, DKEY_HADD_RT, DKEY_SYNC ]

class analyzeConfig(object):
    """Configuration metadata needed to run analysis in a single go.

       Sets up a folder structure by defining full path names; no directory creation is delegated here.

       Args:
         configDir: The root config dir -- all configuration files are stored in its subdirectories
         outputDir: The root output dir -- all log and output files are stored in its subdirectories
         executable_analyze: Name of the executable that runs the analysis; possible values are `analyze_2lss_1tau`, `analyze_2los_1tau`, `analyze_1l_2tau`,...
         max_files_per_job: maximum number of input ROOT files (Ntuples) are allowed to chain together per job
         use_lumi: if True, use lumiSection aka event weight ( = xsection * luminosity / nof events), otherwise uses plain event count
         debug: if True, checks each input root file (Ntuple) before creating the python configuration files
         running_method: either `sbatch` (uses SLURM) or `Makefile`
         num_parallel_jobs: number of jobs that can be run in parallel on local machine (does not limit number of analysis jobs running in parallel on batch system)
         poll_interval: the interval of checking whether all sbatch jobs are completed (matters only if `running_method` is set to `sbatch`)
         histograms_to_fit: what histograms are filtered in datacard preparation
         executable_prep_dcard: executable name for preparing the datacards

       Other:
         is_sbatch: boolean that is True if the `running_method` is set to `sbatch`; False otherwise
         is_makefile: boolean that is True if the `running_method` is set to `Makefile`; False otherwise
         channel: name of the channel in the datacard
         workindgDir: path to 'tthAnalysis/HiggsToTauTau/test' directory in CMSSW area
         dirs: list of subdirectories under `subdir` -- jobs, cfgs, histograms, logs, datacards
         makefile: full path to the Makefile
         histogram_files: the histogram files produced by 'analyze_1l_2tau' jobs
         histogram_files_exists: flags indicating if histogram files already exist from a previous execution of 'tthAnalyzeRun_1l_2tau.py', so that 'analyze_1l_2tau' jobs do not have to be submitted again
         histogramFile_hadd_stage1: the histogram file obtained by hadding the output of all jobs
         histogramFile_hadd_stage2: the final histogram file with data-driven background estimates added
         datacardFile: the datacard -- final output file of this execution flow
         cfg_file_prep_dcard: python configuration file for datacard preparation executable
         histogramDir_prep_dcard: directory in final histogram file that is used for building datacard
    """

    def __init__(self, configDir, outputDir, executable_analyze, channel, central_or_shifts,
                 max_files_per_job, era, use_lumi, lumi, check_input_files, running_method,
                 num_parallel_jobs, histograms_to_fit, triggers,
                 executable_prep_dcard = "prepareDatacards",
                 executable_add_syst_dcard = "addSystDatacards",
                 executable_make_plots = "makePlots",
                 executable_make_plots_mcClosure = "makePlots_mcClosure",
                 do_sync = False,
                 verbose = False,
                 dry_run = False,
                 use_home = True,
                 isDebug = False,
                 template_dir = None):

        self.configDir = configDir
        self.outputDir = outputDir
        self.executable_analyze = executable_analyze
        self.channel = channel
        self.central_or_shifts = central_or_shifts
        self.max_files_per_job = max_files_per_job
        self.max_num_jobs = 100000
        self.era = era
        self.use_lumi = use_lumi
        self.lumi = lumi
        self.check_input_files = check_input_files
        assert(running_method.lower() in [ "sbatch", "makefile" ]), "Invalid running method: %s" % running_method
        self.running_method = running_method
        self.is_sbatch = False
        self.is_makefile = False
        if self.running_method.lower() == "sbatch":
            self.is_sbatch = True
        else:
            self.is_makefile = True
        self.makefile = os.path.join(
            self.configDir, "Makefile_%s" % self.channel)
        self.run_hadd_master_on_batch = False
        self.num_parallel_jobs = num_parallel_jobs
        self.histograms_to_fit = histograms_to_fit
        self.executable_prep_dcard = executable_prep_dcard
        self.prep_dcard_processesToCopy = [ "data_obs", "TT", "TTW", "TTZ", "EWK", "Rares" ]
        self.prep_dcard_signals = [ "signal", "ttH", "ttH_hww", "ttH_hzz", "ttH_htt", "ttH_fake" ]
        self.executable_add_syst_dcard = executable_add_syst_dcard
        self.executable_make_plots = executable_make_plots
        self.executable_make_plots_mcClosure = executable_make_plots_mcClosure
        self.verbose = verbose
        self.dry_run = dry_run
        self.use_home = use_home
        self.isDebug = isDebug
        self.triggers = triggers
        self.triggerTable = Triggers(self.era)

        self.workingDir = os.getcwd()
        logging.info("Working directory is: %s" % self.workingDir)
        if template_dir:
            self.template_dir = template_dir
        else:
            self.template_dir = os.path.join(
                os.getenv('CMSSW_BASE'), 'src', 'tthAnalysis', 'HiggsToTauTau', 'test', 'templates'
            )
        logging.info("Templates directory is: %s" % self.template_dir)

        create_if_not_exists(self.configDir)
        create_if_not_exists(self.outputDir)

        self.stdout_file_path = os.path.join(self.configDir, "stdout_%s.log" % self.channel)
        self.stderr_file_path = os.path.join(self.configDir, "stderr_%s.log" % self.channel)
        self.stdout_file_path, self.stderr_file_path = get_log_version((
            self.stdout_file_path, self.stderr_file_path,
        ))

        self.dirs = {}
        self.samples = {}

        self.jobOptions_analyze = {}
        self.inputFiles_hadd_stage1 = {}
        self.outputFile_hadd_stage1 = {}
        self.cfgFile_addBackgrounds = os.path.join(self.template_dir, "addBackgrounds_cfg.py")
        self.jobOptions_addBackgrounds = {}
        self.jobOptions_addBackgrounds_sum = {}
        self.inputFiles_hadd_stage1_5 = {}
        self.outputFile_hadd_stage1_5 = {}
        self.cfgFile_addFakes = os.path.join(self.template_dir, "addBackgroundLeptonFakes_cfg.py")
        self.jobOptions_addFakes = {}
        self.inputFiles_hadd_stage2 = {}
        self.outputFile_hadd_stage2 = {}
        self.cfgFile_prep_dcard = os.path.join(self.template_dir, "prepareDatacards_cfg.py")
        self.jobOptions_prep_dcard = {}
        self.histogramDir_prep_dcard = None
        self.cfgFile_add_syst_dcard = os.path.join(self.template_dir, "addSystDatacards_cfg.py")
        self.jobOptions_add_syst_dcard = {}
        self.make_plots_backgrounds = [ "TT", "TTW", "TTZ", "EWK", "Rares" ]
        self.make_plots_signal = "signal"
        self.cfgFile_make_plots = os.path.join(self.template_dir, "makePlots_cfg.py")
        self.jobOptions_make_plots = {}
        self.filesToClean = []
        self.phoniesToAdd = []
        self.rleOutputFiles = {}
        self.rootOutputFiles = {}
        self.rootOutputAux = {}

        self.do_sync = do_sync
        self.inputFiles_sync = {}
        self.outputFile_sync = {}
        if self.do_sync:
            self.inputFiles_sync['sync'] = []

        self.targets = []
        self.cvmfs_error_log = {}

        self.num_jobs = {}
        self.num_jobs['analyze'] = 0
        self.num_jobs['hadd'] = 0
        self.num_jobs['addBackgrounds'] = 0
        self.num_jobs['addFakes'] = 0

    def __del__(self):
        for hostname, times in self.cvmfs_error_log.items():
            logging.error("Problem with cvmfs access: host = %s (%i jobs)" % (hostname, len(times)))
            for time in times:
                logging.error(str(time))

    def get_addMEM_systematics(self, central_or_shift):
        if central_or_shift in [
            "central",
            "CMS_ttHl_JESUp",
            "CMS_ttHl_JESDown",
            "CMS_ttHl_tauESUp",
            "CMS_ttHl_tauESDown",
            "CMS_ttHl_JERUp",
            "CMS_ttHl_JERDown",
            "CMS_ttHl_UnclusteredEnUp",
            "CMS_ttHl_UnclusteredEnDown",
        ]:
            return central_or_shift
        return "central"

    def createCfg_analyze(self, jobOptions, sample_info, additionalJobOptions = [], isLeptonFR = False):
        process_string = 'process.analyze_%s' % self.channel
        current_function_name = inspect.stack()[0][3]

        is_mc = (sample_info["type"] == "mc")
        if 'process' not in jobOptions:
          jobOptions['process'] = sample_info["sample_category"]
        if 'isMC' not in jobOptions:
          jobOptions['isMC'] = is_mc
        if 'apply_genWeight' not in jobOptions:
          jobOptions['apply_genWeight'] = sample_info["genWeight"] if is_mc else False
        if 'apply_trigger_bits' not in jobOptions:
          jobOptions['apply_trigger_bits'] = (is_mc and sample_info["reHLT"]) or not is_mc
        if 'lumiScale' not in jobOptions:
          jobOptions['lumiScale'] = sample_info["xsection"] * self.lumi / sample_info["nof_events"] \
                                    if (self.use_lumi and is_mc) else 1.
        if 'hasLHE' not in jobOptions:
            jobOptions['hasLHE'] = sample_info['has_LHE']

        jobOptions_local = [
            'process',
            'isMC',
            'hasLHE',
            'central_or_shift',
            'leptonSelection',
            'chargeSumSelection',
            'histogramDir',
            'lumiScale',
            'leptonChargeSelection',
            'hadTauChargeSelection',
            'hadTauSelection',
            'hadTauSelection_veto',
            'apply_leptonGenMatching',
            'apply_hadTauGenMatching',
            'applyFakeRateWeights',
            'apply_genWeight',
            'apply_trigger_bits',
            'selEventsFileName_output',
            'fillGenEvtHistograms',
            'selectBDT',
            'selEventsTFileName',
            'useNonNominal',
            'apply_hlt_filter',
            'branchName_memOutput',
            'hadTauFakeRateWeight.inputFileName',
            'hadTauFakeRateWeight.lead.fitFunctionName',
            'hadTauFakeRateWeight.sublead.fitFunctionName',
            'hadTauFakeRateWeight.third.fitFunctionName',
            'hadTauFakeRateWeight.applyFitFunction_lead',
            'hadTauFakeRateWeight.applyFitFunction_sublead',
            'hadTauFakeRateWeight.applyFitFunction_third',
            'hadTauFakeRateWeight.applyGraph_lead',
            'hadTauFakeRateWeight.applyGraph_sublead',
            'hadTauFakeRateWeight.lead.graphName',
            'hadTauFakeRateWeight.sublead.graphName',
            'apply_hadTauFakeRateSF',
        ]
        jobOptions_keys = jobOptions_local + additionalJobOptions
        max_option_len = max(map(len, [ key for key in jobOptions_keys if key in jobOptions ]))

        lines = [
            "# Filled in %s" % current_function_name,
            "process.fwliteInput.fileNames = cms.vstring(%s)"  % jobOptions['ntupleFiles'],
            "process.fwliteOutput.fileName = cms.string('%s')" % os.path.basename(jobOptions['histogramFile']),
            "{}.{:<{len}} = cms.string('{}')".format(process_string, 'era',             self.era,     len = max_option_len),
            "{}.{:<{len}} = cms.bool({})".format    (process_string, 'redoGenMatching', 'False',      len = max_option_len),
            "{}.{:<{len}} = cms.bool({})".format    (process_string, 'isDEBUG',         self.isDebug, len = max_option_len),
        ]
        for jobOptions_key in jobOptions_keys:
            if jobOptions_key not in jobOptions: continue # temporary?
            jobOptions_val = jobOptions[jobOptions_key]
            jobOptions_expr = ""
            if type(jobOptions_val) == bool:
                jobOptions_expr = "cms.bool(%s)"
            elif type(jobOptions_val) == float:
                jobOptions_expr = "cms.double(%s)"
            elif type(jobOptions_val) == str:
                jobOptions_expr = "cms.string('%s')"
            elif type(jobOptions_val) == list:
                if all(map(lambda x: type(x) == float, jobOptions_val)):
                    jobOptions_expr = "cms.vdouble(%s)"
                elif all(map(lambda x: type(x) == str, jobOptions_val)):
                    jobOptions_expr = "cms.vstring(%s)"
                else:
                    raise ValueError(
                        "Cannot find correct cms vector type for value %s: %s" % \
                        (jobOptions_key, str(jobOptions_val))
                    )
            else:
                raise ValueError(
                    "Cannot find correct cms type for value %s: %s" % \
                    (jobOptions_key, str(jobOptions_val))
                )
            assert(jobOptions_expr)
            if jobOptions_key.startswith('apply_') and jobOptions_key.endswith('GenMatching'):
                jobOptions_val = jobOptions_val and is_mc
            jobOptions_val = jobOptions_expr % str(jobOptions_val)
            lines.append("{}.{:<{len}} = {}".format(process_string, jobOptions_key, jobOptions_val, len = max_option_len))

        for trigger in self.triggers:
            trigger_string     = '%s.triggers_%s'     % (process_string, trigger)
            trigger_use_string = '%s.use_triggers_%s' % (process_string, trigger)
            if isLeptonFR:
                available_triggers = self.triggerTable.get_leptonFR(trigger, sample_info['process_name_specific'])
            else:
                available_triggers = self.triggerTable.get(trigger, sample_info['process_name_specific'])
            use_trigger = bool(trigger in sample_info['triggers'])
            lines.extend([
                "{:<{len}} = cms.vstring({})".format(trigger_string,     available_triggers, len = max_option_len + len(process_string) + 1),
                "{:<{len}} = cms.bool({})".format   (trigger_use_string, use_trigger,        len = max_option_len + len(process_string) + 1),
            ])

        if self.do_sync:
            lines.extend([
                "{}.{:<{len}} = cms.string('{}')".format(process_string, 'syncNtuple.tree', jobOptions['syncTree'], len = max_option_len),
                "{}.{:<{len}} = cms.string('{}')".format(process_string, 'syncNtuple.output', os.path.basename(jobOptions['syncOutput']), len = max_option_len),
                "{}.{:<{len}} = cms.string('{}')".format(process_string, 'selEventsFileName_input', jobOptions['syncRLE'], len = max_option_len),
            ])
            if 'syncRequireGenMatching' in jobOptions:
                lines.append(
                    "{}.{:<{len}} = cms.bool({})".format(process_string, 'syncNtuple.requireGenMatching', jobOptions['syncRequireGenMatching'], len = max_option_len),
                )

        return lines

    def createCfg_addBackgrounds(self, jobOptions):
        """Create python configuration file for the addBackgrounds executable (sum either all "fake" or all "non-fake" contributions)

           Args:
             inputFiles: input file (the ROOT file produced by hadd_stage1)
             outputFile: output file of the job
        """
        lines = []
        lines.append("process.fwliteInput.fileNames = cms.vstring('%s')" % jobOptions['inputFile'])
        lines.append("process.fwliteOutput.fileName = cms.string('%s')" % os.path.basename(jobOptions['outputFile']))
        lines.append("process.addBackgrounds.categories = cms.vstring(%s)" % jobOptions['categories'])
        lines.append("process.addBackgrounds.processes_input = cms.vstring(%s)" % jobOptions['processes_input'])
        lines.append("process.addBackgrounds.process_output = cms.string('%s')" % jobOptions['process_output'])
        if 'histogramsToCopy' in jobOptions.keys():
            lines.append("process.addBackgrounds.histogramsToCopy = cms.vstring(%s)" % jobOptions['histogramsToCopy'])
        if 'sysShifts' in jobOptions.keys():
            lines.append("process.addBackgrounds.sysShifts = cms.vstring(%s)" % jobOptions['sysShifts'])
        create_cfg(self.cfgFile_addBackgrounds, jobOptions['cfgFile_modified'], lines)

    def createCfg_addFakes(self, jobOptions):
        """Create python configuration file for the addBackgroundLeptonFakes executable (data-driven estimation of 'Fakes' backgrounds)

           Args:
             inputFiles: input file (the ROOT file produced by hadd_stage1)
             outputFile: output file of the job
        """
        lines = []
        lines.append("process.fwliteInput.fileNames = cms.vstring('%s')" % jobOptions['inputFile'])
        lines.append("process.fwliteOutput.fileName = cms.string('%s')" % os.path.basename(jobOptions['outputFile']))
        lines.append("process.addBackgroundLeptonFakes.categories = cms.VPSet(")
        lines.append("    cms.PSet(")
        lines.append("        signal = cms.string('%s')," % jobOptions['category_signal'])
        lines.append("        sideband = cms.string('%s')" % jobOptions['category_sideband'])
        lines.append("    )")
        lines.append(")")
        lines.append("process.addBackgroundLeptonFakes.processesToSubtract = cms.vstring(%s)" % self.nonfake_backgrounds)
        lines.append("process.addBackgroundLeptonFakes.sysShifts = cms.vstring(%s)" % self.central_or_shifts)
        create_cfg(self.cfgFile_addFakes, jobOptions['cfgFile_modified'], lines)

    def createCfg_prep_dcard(self, jobOptions):
        """Fills the template of python configuration file for datacard preparation

           Args:
             histogramToFit: name of the histogram used for signal extraction
        """
        category_output = self.channel
        if jobOptions['label']:
            category_output += "_%s" % jobOptions['label']
        histogramToFit = jobOptions['histogramToFit']
        lines = []
        lines.append("process.fwliteInput.fileNames = cms.vstring('%s')" % jobOptions['inputFile'])
        lines.append("process.fwliteOutput.fileName = cms.string('%s')" % jobOptions['datacardFile'])
        lines.append("process.prepareDatacards.processesToCopy = cms.vstring(%s)" % self.prep_dcard_processesToCopy)
        lines.append("process.prepareDatacards.signals = cms.vstring(%s)" % self.prep_dcard_signals)
        lines.append("process.prepareDatacards.makeSubDir = cms.bool(False)")
        lines.append("process.prepareDatacards.categories = cms.VPSet(")
        lines.append("    cms.PSet(")
        lines.append("        input = cms.string('%s/sel/evt')," % jobOptions['histogramDir'])
        lines.append("        output = cms.string('ttH_%s')" % category_output)
        lines.append("    )")
        lines.append(")")
        lines.append("process.prepareDatacards.histogramToFit = cms.string('%s')" % histogramToFit)

        # If the user has specified the binning options for a particular histogram, we expect to see
        # a dictionary instead of a list of histogram names that's been passed to this class as histograms_to_fit
        if type(self.histograms_to_fit) == dict:
            if histogramToFit in self.histograms_to_fit:
                histogramToFit_options = self.histograms_to_fit[histogramToFit]
                # Check the binning options
                if not histogramToFit_options:
                    # Use whatever the default setting are in the original prepareDatacards template
                    pass
                else:
                    # Expected syntax:
                    # {
                    #   "EventCounter"    : { 'auto_rebin' : True, 'min_auto_rebin' = 0.05 }, # no quantile
                    #   "numJets"         : { 'quantile_rebin' : 5 }, # also enables quantile rebinning, no auto
                    #   "mTauTauVis1_sel" : {}, # default settings (no auto or quantile rebinning)
                    # }
                    if 'auto_rebin' in histogramToFit_options:
                        lines.append("process.prepareDatacards.apply_automatic_rebinning = cms.bool(%s)" % \
                                     histogramToFit_options['auto_rebin'])
                    if 'min_auto_rebin' in histogramToFit_options:
                        lines.append("process.prepareDatacards.minEvents_automatic_rebinning = cms.double(%.3f)" % \
                                     histogramToFit_options['min_auto_rebin'])
                    if 'quantile_rebin' in histogramToFit_options:
                        lines.append("process.prepareDatacards.nbin_quantile_rebinning = cms.int32(%d)" % \
                                     histogramToFit_options['quantile_rebin'])
                        if 'quantile_in_fakes' in histogramToFit_options:
                            lines.append("process.prepareDatacards.quantile_rebinning_in_fakes = cms.bool(%d)" % \
                                         histogramToFit_options['quantile_in_fakes'])
                    if 'explicit_binning' in histogramToFit_options:
                        explicit_binning = histogramToFit_options['explicit_binning']
                        assert(type(explicit_binning) == list and sorted(explicit_binning) == explicit_binning)
                        lines.append("process.prepareDatacards.explicit_binning = cms.vdouble(%s)" % explicit_binning)
        # If self.histograms_to_fit is not a dictionary but a list, do not modify anything but
        # use the default settings specified in the original prepareDatacards template

        create_cfg(self.cfgFile_prep_dcard, jobOptions['cfgFile_modified'], lines)

    def createCfg_add_syst_dcard(self, jobOptions):
        """Fills the template of python configuration file for adding specific shape systematics to the datacard,
           e.g. CMS_ttHl_Clos_e_shapeUp/Down, CMS_ttHl_Clos_m_shapeUp/Down

           Args:
             histogramToFit: name of the histogram used for signal extraction
        """
        lines = []
        lines.append("process.fwliteInput.fileNames = cms.vstring('%s')" % jobOptions['inputFile'])
        lines.append("process.fwliteOutput.fileName = cms.string('%s')" % jobOptions['outputFile'])
        lines.append("process.addSystDatacards.category = cms.string('%s')" % jobOptions['category'])
        lines.append("process.addSystDatacards.histogramToFit = cms.string('%s')" % jobOptions['histogramToFit'])
        create_cfg(self.cfgFile_add_syst_dcard, jobOptions['cfgFile_modified'], lines)

    def createCfg_makePlots(self, jobOptions):
        """Fills the template of python configuration file for making control plots

           Args:
             histogram_file: name of the input ROOT file
        """
        category_label = self.channel
        if jobOptions['label']:
            category_label += " (%s)" % jobOptions['label']
        lines = []
        lines.append("process.fwliteInput.fileNames = cms.vstring('%s')" % jobOptions['inputFile'])
        lines.append("process.makePlots.outputFileName = cms.string('%s')" % jobOptions['outputFile'])
        lines.append("process.makePlots.processesBackground = cms.vstring(%s)" % jobOptions['make_plots_backgrounds'])
        lines.append("process.makePlots.processSignal = cms.string('%s')" % self.make_plots_signal)
        lines.append("process.makePlots.categories = cms.VPSet(")
        lines.append("  cms.PSet(")
        lines.append("    name = cms.string('%s')," % jobOptions['histogramDir'])
        lines.append("    label = cms.string('%s')" % category_label)
        lines.append("  )")
        lines.append(")")
        create_cfg(self.cfgFile_make_plots, jobOptions['cfgFile_modified'], lines)

    def createScript_sbatch(self, executable, sbatchFile, jobOptions,
                            key_cfg_file = 'cfgFile_modified', key_input_file = 'inputFile',
                            key_output_file = 'outputFile', key_log_file = 'logFile',
                            skipFileSizeCheck = False):
        """Creates the python script necessary to submit 'generic' (addBackgrounds, addBackgroundFakes/addBackgroundFlips) jobs to the batch system
        """
        num_jobs = tools_createScript_sbatch(
            sbatch_script_file_name = sbatchFile,
            executable = executable,
            command_line_parameters = { key: value[key_cfg_file] for key, value in jobOptions.items() },
            input_file_names = { key: value[key_input_file] for key, value in jobOptions.items() },
            output_file_names = { key: value[key_output_file] for key, value in jobOptions.items() },
            script_file_names = { key: value[key_cfg_file].replace(".py", ".sh").replace("_cfg", "") for key, value in jobOptions.items() },
            log_file_names = { key: value[key_log_file] for key, value in jobOptions.items() },
            working_dir = self.workingDir,
            max_num_jobs = self.max_num_jobs,
            cvmfs_error_log = self.cvmfs_error_log,
            pool_id = uuid.uuid4(),
            verbose = self.verbose,
            dry_run = self.dry_run,
            skipFileSizeCheck = skipFileSizeCheck,
            use_home = self.use_home,
        )
        return num_jobs

    def createScript_sbatch_syncNtuple(self, executable, sbatchFile, jobOptions):
        """Creates the python script necessary to submit the analysis jobs to the batch system
        """
        self.num_jobs['analyze'] += self.createScript_sbatch(
            executable, sbatchFile, jobOptions, 'cfgFile_modified', 'ntupleFiles', 'syncOutput',
            'logFile', skipFileSizeCheck = True,
        )


    def createScript_sbatch_analyze(self, executable, sbatchFile, jobOptions):
        """Creates the python script necessary to submit the analysis jobs to the batch system
        """
        self.num_jobs['analyze'] += self.createScript_sbatch(executable, sbatchFile, jobOptions,
                                                             'cfgFile_modified', 'ntupleFiles', 'histogramFile', 'logFile')

    def createScript_sbatch_addBackgrounds(self, executable, sbatchFile, jobOptions):
        """Creates the python script necessary to submit the analysis jobs to the batch system
        """
        self.num_jobs['addBackgrounds'] += self.createScript_sbatch(executable, sbatchFile, jobOptions)

    def createScript_sbatch_addFakes(self, executable, sbatchFile, jobOptions):
        """Creates the python script necessary to submit the analysis jobs to the batch system
        """
        self.num_jobs['addFakes'] += self.createScript_sbatch(executable, sbatchFile, jobOptions)

    def create_hadd_python_file(self, inputFiles, outputFile, hadd_stage_name):
        sbatch_hadd_file = os.path.join(self.dirs[DKEY_SCRIPTS], "sbatch_hadd_%s_%s.py" % (self.channel, hadd_stage_name))
        sbatch_hadd_file = sbatch_hadd_file.replace(".root", "")
        scriptFile = os.path.join(self.dirs[DKEY_SCRIPTS], os.path.basename(sbatch_hadd_file).replace(".py", ".sh"))
        logFile = os.path.join(self.dirs[DKEY_LOGS], os.path.basename(sbatch_hadd_file).replace(".py", ".log"))
        sbatch_hadd_dir = os.path.join(self.dirs[DKEY_HADD_RT], self.channel, hadd_stage_name) if self.dirs[DKEY_HADD_RT] else ''
        self.num_jobs['hadd'] += tools_createScript_sbatch_hadd(
            sbatch_hadd_file, inputFiles, outputFile, scriptFile, logFile, self.workingDir, auxDirName = sbatch_hadd_dir,
            pool_id = uuid.uuid4(), verbose = self.verbose, dry_run = self.dry_run, use_home = self.use_home,
        )
        return sbatch_hadd_file

    def addToMakefile_analyze(self, lines_makefile):
        """Adds the commands to Makefile that are necessary for running the analysis code on the Ntuple and filling the histograms
        """
        if self.is_sbatch:
            lines_makefile.append("sbatch_analyze:")
            lines_makefile.append("\t%s %s" % ("python", self.sbatchFile_analyze))
            lines_makefile.append("")
        for jobOptions in self.jobOptions_analyze.values():
            if self.is_makefile:
                lines_makefile.append("%s:" % jobOptions['histogramFile'])
                lines_makefile.append("\t%s %s &> %s" % (self.executable_analyze, jobOptions['cfgFile_modified'], jobOptions['logFile']))
                lines_makefile.append("")
            elif self.is_sbatch:
                lines_makefile.append("%s: %s" % (jobOptions['histogramFile'], "sbatch_analyze"))
                lines_makefile.append("\t%s" % ":") # CV: null command
                lines_makefile.append("")
            self.filesToClean.append(jobOptions['histogramFile'])

    def addToMakefile_syncNtuple(self, lines_makefile):
        """Adds the commands to Makefile that are necessary for running the analysis code on the Ntuple and filling the histograms
        """
        if self.is_sbatch:
            lines_makefile.append("sbatch_analyze:")
            lines_makefile.append("\t%s %s" % ("python", self.sbatchFile_analyze))
            lines_makefile.append("")
        for jobOptions in self.jobOptions_analyze.values():
            if self.is_makefile:
                lines_makefile.append("%s:" % jobOptions['syncOutput'])
                lines_makefile.append("\t%s %s &> %s" % (self.executable_analyze, jobOptions['cfgFile_modified'], jobOptions['logFile']))
                lines_makefile.append("")
            elif self.is_sbatch:
                lines_makefile.append("%s: %s" % (jobOptions['syncOutput'], "sbatch_analyze"))
                lines_makefile.append("\t%s" % ":") # CV: null command
                lines_makefile.append("")
            self.filesToClean.append(jobOptions['syncOutput'])

    def addToMakefile_hadd(self, lines_makefile, inputFiles, outputFiles, label):
        scriptFiles = {}
        jobOptions = {}
        for key in outputFiles.keys():
            scriptFiles[key] = self.create_hadd_python_file(inputFiles[key], outputFiles[key], "_".join([ label, key, "ClusterHistogramAggregator" ]))
            jobOptions[key] = {
                'inputFile' : inputFiles[key],
                'cfgFile_modified' : scriptFiles[key],
                'outputFile' : None, # CV: output file written to /hdfs by ClusterHistogramAggregator directly and does not need to be copied
                'logFile' : os.path.join(self.dirs[DKEY_LOGS], os.path.basename(outputFiles[key]).replace(".root", ".log"))
            }
        sbatchTarget = None
        if self.is_sbatch and self.run_hadd_master_on_batch:
            sbatchTarget = "sbatch_hadd_%s" % label
            self.phoniesToAdd.append(sbatchTarget)
            lines_makefile.append("%s: %s" % (sbatchTarget, " ".join([ " ".join(inputFiles[key]) for key in inputFiles.keys()])))
            for outputFile in outputFiles.values():
                lines_makefile.append("\t%s %s" % ("rm -f", outputFile))
            sbatchFile = os.path.join(self.dirs[DKEY_SCRIPTS], "sbatch_hadd_%s_%s.py" % (self.channel, label))
            self.createScript_sbatch('python', sbatchFile, jobOptions)
            lines_makefile.append("\t%s %s" % ("python", sbatchFile))
            lines_makefile.append("")
        for key in outputFiles.keys():
            if self.is_sbatch and self.run_hadd_master_on_batch:
                lines_makefile.append("%s: %s" % (outputFiles[key], sbatchTarget))
                lines_makefile.append("\t%s" % ":") # CV: null command
                lines_makefile.append("")
            else:
                lines_makefile.append("%s: %s" % (outputFiles[key], " ".join(inputFiles[key])))
                lines_makefile.append("\t%s %s" % ("rm -f", outputFiles[key]))
                lines_makefile.append("\t%s %s" % ("python", scriptFiles[key]))
                lines_makefile.append("")
            self.filesToClean.append(outputFiles[key])

    def addToMakefile_hadd_stage1(self, lines_makefile):
        self.addToMakefile_hadd(lines_makefile, self.inputFiles_hadd_stage1, self.outputFile_hadd_stage1, "stage1")

    def addToMakefile_hadd_sync(self, lines_makefile):
        self.addToMakefile_hadd(lines_makefile, self.inputFiles_sync, self.outputFile_sync, "sync")

    def addToMakefile_addBackgrounds(self, lines_makefile, sbatchTarget, sbatchFile, jobOptions):
        if self.is_sbatch:
            lines_makefile.append("%s: %s" % (sbatchTarget, " ".join([ value['inputFile'] for value in jobOptions.values() ])))
            lines_makefile.append("\t%s %s" % ("python", sbatchFile))
            lines_makefile.append("")
        for value in jobOptions.values():
            if self.is_makefile:
                lines_makefile.append("%s: %s" % (value['outputFile'], value['inputFile']))
                lines_makefile.append("\t%s %s &> %s" % (self.executable_addBackgrounds, value['cfgFile_modified'], value['logFile']))
                lines_makefile.append("")
            elif self.is_sbatch:
                lines_makefile.append("%s: %s" % (value['outputFile'], sbatchTarget))
                lines_makefile.append("\t%s" % ":") # CV: null command
                lines_makefile.append("")
            self.filesToClean.append(value['outputFile'])

    def addToMakefile_hadd_stage1_5(self, lines_makefile):
        """Adds the commands to Makefile that are necessary for building the intermediate histogram file
           that is used as input for data-driven background estimation.
        """
        self.addToMakefile_hadd(lines_makefile, self.inputFiles_hadd_stage1_5, self.outputFile_hadd_stage1_5, "stage1_5")

    def addToMakefile_addFakes(self, lines_makefile):
        if self.is_sbatch:
            lines_makefile.append("sbatch_addFakes: %s" % " ".join([ jobOptions['inputFile'] for jobOptions in self.jobOptions_addFakes.values() ]))
            lines_makefile.append("\t%s %s" % ("python", self.sbatchFile_addFakes))
            lines_makefile.append("")
        for jobOptions in self.jobOptions_addFakes.values():
            if self.is_makefile:
                lines_makefile.append("%s: %s" % (jobOptions['outputFile'], jobOptions['inputFile']))
                lines_makefile.append("\t%s %s &> %s" % (self.executable_addFakes, jobOptions['cfgFile_modified'], jobOptions['logFile']))
                lines_makefile.append("")
            elif self.is_sbatch:
                lines_makefile.append("%s: %s" % (jobOptions['outputFile'], "sbatch_addFakes"))
                lines_makefile.append("\t%s" % ":") # CV: null command
                lines_makefile.append("")
            self.filesToClean.append(jobOptions['outputFile'])

    def addToMakefile_backgrounds_from_data(self, lines_makefile):
        self.addToMakefile_addBackgrounds(lines_makefile, "sbatch_addBackgrounds", self.sbatchFile_addBackgrounds, self.jobOptions_addBackgrounds)
        self.addToMakefile_addBackgrounds(lines_makefile, "sbatch_addBackgrounds_sum", self.sbatchFile_addBackgrounds_sum, self.jobOptions_addBackgrounds_sum)
        self.addToMakefile_hadd_stage1_5(lines_makefile)
        self.addToMakefile_addFakes(lines_makefile)

    def addToMakefile_hadd_stage2(self, lines_makefile):
        """Adds the commands to Makefile that are necessary for building the final histogram file.
        """
        self.addToMakefile_hadd(lines_makefile, self.inputFiles_hadd_stage2, self.outputFile_hadd_stage2, "stage2")

    def addToMakefile_prep_dcard(self, lines_makefile):
        """Adds the commands to Makefile that are necessary for building the datacards.
        """
        for jobOptions in self.jobOptions_prep_dcard.values():
            lines_makefile.append("%s: %s" % (jobOptions['datacardFile'], jobOptions['inputFile']))
            lines_makefile.append("\t%s %s" % (self.executable_prep_dcard, jobOptions['cfgFile_modified']))
            self.filesToClean.append(jobOptions['datacardFile'])
            lines_makefile.append("")

    def addToMakefile_add_syst_dcard(self, lines_makefile):
        """Adds the commands to Makefile that are necessary for building the datacards.
        """
        for jobOptions in self.jobOptions_add_syst_dcard.values():
            lines_makefile.append("%s: %s" % (jobOptions['outputFile'], jobOptions['inputFile']))
            lines_makefile.append("\t%s %s" % (self.executable_add_syst_dcard, jobOptions['cfgFile_modified']))
            self.filesToClean.append(jobOptions['outputFile'])
            lines_makefile.append("")

    def addToMakefile_make_plots(self, lines_makefile):
        """Adds the commands to Makefile that are necessary for making control plots of the jet->tau fake background estimation procedure.
        """
        for idxJob, jobOptions in enumerate(self.jobOptions_make_plots.values()):
            lines_makefile.append("makePlots%i: %s" % (idxJob, jobOptions['inputFile']))
            lines_makefile.append("\t%s %s" % (jobOptions['executable'], jobOptions['cfgFile_modified']))
            lines_makefile.append("")

    def addToMakefile_outRoot(self, lines_makefile):
        """Adds the commands to Makefile that are necessary for building the final condensed *.root output file
           containing a TTree of all selected event variables specific to a given channel.
        """
        if not self.rootOutputAux:
            return
        lines_makefile.append("selEventTree_hadd: %s\n" % ' '.join(
            map(lambda x: x[0], self.rootOutputAux.values())))
        for rootOutput in self.rootOutputAux.values():
            lines_makefile.append("%s: %s" % (rootOutput[0], rootOutput[2]))
            lines_makefile.append(
                "\thadd -f %s $(shell for f in `ls %s`; do echo -ne $$f\" \"; done)\n" % (rootOutput[0], rootOutput[1]))
        lines_makefile.append("")

    def createMakefile(self, lines_makefile):
        """Creates Makefile that runs the complete analysis workfow.
        """
        self.targets.extend([ jobOptions['datacardFile'] for jobOptions in self.jobOptions_prep_dcard.values() ])
        self.targets.extend([ jobOptions['outputFile'] for jobOptions in self.jobOptions_add_syst_dcard.values() ])
        if self.rootOutputAux:
            self.targets.append("selEventTree_hadd")
        for idxJob, jobOptions in enumerate(self.jobOptions_make_plots.values()):
            self.targets.append("makePlots%i" % idxJob)
        for rootOutput in self.rootOutputAux.values():
            self.filesToClean.append(rootOutput[0])
        if len(self.targets) == 0:
            self.targets.append("sbatch_analyze")
        tools_createMakefile(self.makefile, self.targets, lines_makefile, self.filesToClean, self.is_sbatch, self.phoniesToAdd)
        logging.info("Run it with:\tmake -f %s -j %i " % (self.makefile, self.num_parallel_jobs))

    def initializeInputFileIds(self, sample_name, sample_info):
        """Retrieves the number of input ROOT files (Ntuples) corresponding to a given sample
           and fills the number into the dictionary 'self.inputFileIds', with the name of the sample as key

           TODO: add blacklist to the secondary storage as well
        """
        logging.warning("Function <initializeInputFileIds> is deprecated and should not be used anymore !!")
        logging.warning("Please have a look at 'analyzeConfig_2lss_1tau.py' to see " \
                        "how to migrate your python scripts to the new syntax.")
        nof_inputFiles = sample_info["nof_files"]
        store_dirs = sample_info["local_paths"]
        assert(len(store_dirs) <= 2), "There is more than one secondary dir!"
        primary_store, secondary_store = "", ""
        secondary_files, blacklist = [], []
        for store_dir in store_dirs:
            if store_dir["selection"] == "*":
                primary_store = store_dir["path"]
                if "blacklist" in store_dir:
                    blacklist = store_dir["blacklist"]
            else:
                secondary_store = store_dir["path"]
                secondary_files = map(lambda x: int(x), store_dir[
                                      "selection"].split(","))
        self.inputFileIds[sample_name] = generate_file_ids(
            nof_inputFiles, self.max_files_per_job, blacklist)
        return (secondary_files, primary_store, secondary_store)

    def create(self):
        """Creates all config files necessary for runing the complete analysis workfow.
        """
        raise ValueError("Method 'create' not implemented in derrived class !!")

    def run(self):
        """Runs the complete analysis workfow -- either locally or on the batch system.
        """
        run_cmd(
            "make -f %s -j %i 2>%s 1>%s" % \
            (self.makefile, self.num_parallel_jobs, self.stderr_file_path, self.stdout_file_path),
            False
        )
