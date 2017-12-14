import codecs, os, logging, uuid

from tthAnalysis.HiggsToTauTau.jobTools import create_if_not_exists, run_cmd, generate_file_ids
from tthAnalysis.HiggsToTauTau.analysisTools import initDict, getKey, create_cfg, createFile
from tthAnalysis.HiggsToTauTau.analysisTools import createMakefile as tools_createMakefile
from tthAnalysis.HiggsToTauTau.sbatchManagerTools import createScript_sbatch as tools_createScript_sbatch
from tthAnalysis.HiggsToTauTau.sbatchManagerTools import createScript_sbatch_hadd as tools_createScript_sbatch_hadd

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

executable_rm = 'rm'

DIRLIST = [ DKEY_CFGS, DKEY_DCRD, DKEY_HIST, DKEY_PLOT, DKEY_SCRIPTS, DKEY_LOGS, DKEY_RLES, DKEY_ROOT ]

class analyzeConfig:
    """Configuration metadata needed to run analysis in a single go.

    Sets up a folder structure by defining full path names; no directory creation is delegated here.

    Args:
      outputDir: The root output dir -- all configuration, log and output files are stored in its subdirectories
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

    def __init__(self, outputDir, executable_analyze, channel, central_or_shifts,
                 max_files_per_job, era, use_lumi, lumi, debug, running_method, num_parallel_jobs,
                 histograms_to_fit, executable_prep_dcard="prepareDatacards", executable_make_plots="makePlots",
                 pool_id = ''):

        self.outputDir = outputDir
        self.executable_analyze = executable_analyze
        self.channel = channel
        self.central_or_shifts = central_or_shifts
        self.max_files_per_job = max_files_per_job
        self.max_num_jobs = 20000
        self.era = era
        self.use_lumi = use_lumi
        self.lumi = lumi
        self.debug = debug
        assert(running_method.lower() in [
               "sbatch", "makefile"]), "Invalid running method: %s" % running_method
        self.running_method = running_method
        self.is_sbatch = False
        self.is_makefile = False
        if self.running_method.lower() == "sbatch":
            self.is_sbatch = True
        else:
            self.is_makefile = True
        self.makefile = os.path.join(
            self.outputDir, "Makefile_%s" % self.channel)
        self.num_parallel_jobs = num_parallel_jobs
        self.histograms_to_fit = histograms_to_fit
        self.executable_prep_dcard = executable_prep_dcard
        self.prep_dcard_processesToCopy = [
            "data_obs", "TT", "TTW", "TTZ", "EWK", "Rares"]
        self.prep_dcard_signals = ["ttH_hww", "ttH_hzz", "ttH_htt"]
        self.executable_make_plots = executable_make_plots
        self.pool_id = pool_id if pool_id else uuid.uuid4()

        self.workingDir = os.getcwd()
        logging.info("Working directory is: %s" % self.workingDir)
        self.template_dir = os.path.join(
            os.getenv('CMSSW_BASE'), 'src', 'tthAnalysis', 'HiggsToTauTau', 'test', 'templates'
        )
        logging.info("Templates directory is: %s" % self.template_dir)

        create_if_not_exists(self.outputDir)
        self.stdout_file = codecs.open(os.path.join(
            self.outputDir, "stdout_%s.log" % self.channel), 'w', 'utf-8')
        self.stderr_file = codecs.open(os.path.join(
            self.outputDir, "stderr_%s.log" % self.channel), 'w', 'utf-8')
        self.dirs = {}
        self.samples = {}
        self.cfgFiles_analyze_modified = {}
        self.logFiles_analyze = {}
        self.sbatchFile_analyze = os.path.join(self.outputDir, "sbatch_analyze_%s.py" % self.channel)
        self.ntupleFiles = {}
        self.histogramFiles = {}
        self.inputFiles_hadd_stage1 = []
        self.histogramFile_hadd_stage1 = os.path.join(
            self.outputDir, DKEY_HIST, "histograms_harvested_stage1_%s.root" % self.channel)
        self.inputFiles_hadd_stage1_5 = []
        self.histogramFile_hadd_stage1_5 = os.path.join(
            self.outputDir, DKEY_HIST, "histograms_harvested_stage1_5_%s.root" % self.channel)
        self.inputFiles_hadd_stage2 = []
        self.histogramFile_hadd_stage2 = os.path.join(
            self.outputDir, DKEY_HIST, "histograms_harvested_stage2_%s.root" % self.channel)
        self.datacardFiles = {}
        self.cfgFile_prep_dcard_original = os.path.join(
            self.template_dir, "prepareDatacards_cfg.py")
        self.cfgFile_prep_dcard_modified = {}
        self.histogramDir_prep_dcard = None
        self.make_plots_backgrounds = ["TT", "TTW", "TTZ", "EWK", "Rares"]
        self.make_plots_signal = "signal"
        self.cfgFile_make_plots_original = os.path.join(
            self.template_dir, "makePlots_cfg.py")
        self.cfgFiles_make_plots_modified = []
        self.filesToClean = []
        self.rleOutputFiles = {}
        self.rootOutputFiles = {}
        self.rootOutputAux = {}

        if era == '2015':
            self.triggers_1e = ['HLT_BIT_HLT_Ele23_WPLoose_Gsf_v']
            self.triggers_2e = [
                'HLT_BIT_HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v']
            self.triggers_1mu = [
                'HLT_BIT_HLT_IsoMu20_v', 'HLT_BIT_HLT_IsoTkMu20_v']
            self.triggers_2mu = ['HLT_BIT_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v',
                                 'HLT_BIT_HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v']
            self.triggers_1e1mu = ['HLT_BIT_HLT_Mu17_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v',
                                   'HLT_BIT_HLT_Mu8_TrkIsoVVL_Ele17_CaloIdL_TrackIdL_IsoVL_v']
        elif era == '2016':
            # CV: HLT_Ele25_WPTight_Gsf_v* was prescaled during part of 2016
            # Runs B-D, so use HLT_Ele27_eta2p1_WPLoose_Gsf_v in addition
            self.triggers_1e = ['HLT_BIT_HLT_Ele25_WPTight_Gsf_v',
                                'HLT_BIT_HLT_Ele27_eta2p1_WPLoose_Gsf_v']
            self.triggers_2e = [
                'HLT_BIT_HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v']
            self.triggers_1mu = [
                'HLT_BIT_HLT_IsoMu22_v', 'HLT_BIT_HLT_IsoTkMu22_v']
            self.triggers_2mu = ['HLT_BIT_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v',
                                 'HLT_BIT_HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v']
            self.triggers_1e1mu = ['HLT_BIT_HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v',
                                   'HLT_BIT_HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v']
            self.triggers_2tau = [
                'HLT_BIT_HLT_DoubleMediumIsoPFTau35_Trk1_eta2p1_Reg_v*']
        else:
            raise ValueError(
                "Invalid Configuration parameter 'era' = %s !!" % era)

        self.cvmfs_error_log = {}

    def __del__(self):
        for hostname, times in self.cvmfs_error_log.items():
            print "Problem with cvmfs access: host = %s (%i jobs)" % (hostname, len(times))
            for time in times:
                print time

    def createCfg_analyze(self, *args):
        raise ValueError(
            "Function 'createCfg_analyze' not implemented in derrived class !!")

    def createCfg_prep_dcard(self, histogramToFit, histogramDir=None, label=None):
        """Fills the template of python configuration file for datacard preparation

        Args:
          histogramToFit: name of the histogram used for signal extraction
        """
        datacardFile = os.path.join(
            self.outputDir, DKEY_DCRD, "prepareDatacards_%s_%s.root" % (self.channel, histogramToFit))
        category_output = self.channel
        cfg_file_modified = os.path.join(
            self.outputDir, DKEY_CFGS, "prepareDatacards_%s_%s_cfg.py" % (self.channel, histogramToFit))
        key = histogramToFit
        if not histogramDir:
            histogramDir = self.histogramDir_prep_dcard
            if label:
                datacardFile = datacardFile.replace(
                    channel, "%s_%s" % (channel, label))
                category_output += "_%s" % label
                cfg_file_modified = cfg_file_modified.replace(
                    "_cfg.py", "_%s_cfg.py" % label)
                key = getKey(histogramToFit, label)
        lines = []
        lines.append("process.fwliteInput.fileNames = cms.vstring('%s')" %
                     self.histogramFile_hadd_stage2)
        lines.append(
            "process.fwliteOutput.fileName = cms.string('%s')" % datacardFile)
        lines.append("process.prepareDatacards.processesToCopy = cms.vstring(%s)" %
                     self.prep_dcard_processesToCopy)
        lines.append("process.prepareDatacards.signals = cms.vstring(%s)" %
                     self.prep_dcard_signals)
        lines.append("process.prepareDatacards.makeSubDir = cms.bool(False)")
        lines.append("process.prepareDatacards.categories = cms.VPSet(")
        lines.append("    cms.PSet(")
        lines.append("        input = cms.string('%s/sel/evt')," %
                     self.histogramDir_prep_dcard)
        lines.append("        output = cms.string('ttH_%s')" % category_output)
        lines.append("    )")
        lines.append(")")
        lines.append(
            "process.prepareDatacards.histogramToFit = cms.string('%s')" % histogramToFit)
        create_cfg(self.cfgFile_prep_dcard_original, cfg_file_modified, lines)
        self.datacardFiles[key] = datacardFile
        self.cfgFile_prep_dcard_modified[key] = cfg_file_modified

    def createCfg_makePlots(self, histogramDir=None, label=None, make_plots_backgrounds=None):
        """Fills the template of python configuration file for making control plots

        Args:
          histogram_file: name of the input ROOT file
        """
        outputFileName = os.path.join(
            self.outputDir, DKEY_PLOT, self.channel, "makePlots_%s.png" % self.channel)
        category_label = self.channel
        cfg_file_modified = os.path.join(
            self.outputDir, DKEY_CFGS, "makePlots_%s_cfg.py" % self.channel)
        if not histogramDir:
            histogramDir = self.histogramDir_prep_dcard
        if label:
            outputFileName = outputFileName.replace(".png", "_%s.png" % label)
            category_label += " (%s)" % label
            cfg_file_modified = cfg_file_modified.replace(
                "_cfg.py", "_%s_cfg.py" % label)
        lines = []
        lines.append("process.fwliteInput.fileNames = cms.vstring('%s')" %
                     self.histogramFile_hadd_stage2)
        lines.append(
            "process.makePlots.outputFileName = cms.string('%s')" % outputFileName)
        if not make_plots_backgrounds:
            make_plots_backgrounds = self.make_plots_backgrounds
        lines.append(
            "process.makePlots.processesBackground = cms.vstring(%s)" % make_plots_backgrounds)
        lines.append("process.makePlots.processSignal = cms.string('%s')" %
                     self.make_plots_signal)
        lines.append("process.makePlots.categories = cms.VPSet(")
        lines.append("  cms.PSet(")
        lines.append("    name = cms.string('%s')," % histogramDir)
        lines.append("    label = cms.string('%s')" % category_label)
        lines.append("  )")
        lines.append(")")
        create_cfg(self.cfgFile_make_plots_original, cfg_file_modified, lines)
        self.cfgFiles_make_plots_modified.append(cfg_file_modified)

    def initializeInputFileIds(self, sample_name, sample_info):
        """Retrieves the number of input ROOT files (Ntuples) corresponding to a given sample
           and fills the number into the dictionary 'self.inputFileIds', with the name of the sample as key

           TODO: add blacklist to the secondary storage as well
        """
        print "Warning: Function <initializeInputFileIds> is deprecated and should not be used anymore !!"
        print " Please have a look at 'analyzeConfig_2lss_1tau.py' to see how to migrate your python scripts to the new syntax."
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

    def createScript_sbatch(self):
        """Creates the python script necessary to submit the analysis jobs to the batch system
        """
        tools_createScript_sbatch(
            sbatch_script_file_name = self.sbatchFile_analyze,
            executable = self.executable_analyze,
            cfg_file_names = self.cfgFiles_analyze_modified,
            input_file_names = self.ntupleFiles,
            output_file_names = self.histogramFiles,
            log_file_names = self.logFiles_analyze,
            working_dir = self.workingDir,
            max_num_jobs = self.max_num_jobs,
            cvmfs_error_log = self.cvmfs_error_log,
            pool_id = self.pool_id,
        )

    def create_hadd_python_file(self, inputFiles, outputFile, hadd_stage_name):
        sbatch_hadd_file = os.path.join(self.outputDir, "sbatch_hadd_%s_%s.py" % (self.channel, hadd_stage_name))
        tools_createScript_sbatch_hadd(
            sbatch_hadd_file, inputFiles, outputFile, hadd_stage_name, self.workingDir, pool_id = self.pool_id
        )
        return sbatch_hadd_file

    def addToMakefile_analyze(self, lines_makefile):
        """Adds the commands to Makefile that are necessary for running the analysis code on the Ntuple and filling the histograms
        """
        if self.is_sbatch:
            lines_makefile.append("sbatch:")
            lines_makefile.append("\t%s %s" % (
                "python", self.sbatchFile_analyze))
            lines_makefile.append("")
        for key_file, histogram_file in self.histogramFiles.items():
            cfg_file_analyze_modified = self.cfgFiles_analyze_modified[
                key_file]
            if self.is_makefile:
                lines_makefile.append("%s:" % histogram_file)
                cfg_file = self.cfgFiles[key_file]
                log_file = self.logFiles[key_file]
                lines_makefile.append("\t%s %s &> %s" % (
                    self.executable_analyze, cfg_file, log_file))
                lines_makefile.append("")
            elif self.is_sbatch:
                lines_makefile.append("%s: %s" % (histogram_file, "sbatch"))
                lines_makefile.append("\t%s" % ":")  # CV: null command
                lines_makefile.append("")
            self.filesToClean.append(histogram_file)

    def addToMakefile_hadd_stage1(self, lines_makefile):
        script_hadd_stage1 = self.create_hadd_python_file(self.inputFiles_hadd_stage1, self.histogramFile_hadd_stage1, "stage1")
        lines_makefile.append("%s: %s" % (self.histogramFile_hadd_stage1, " ".join(self.inputFiles_hadd_stage1)))
        lines_makefile.append("\t%s %s" % ("rm -f", self.histogramFile_hadd_stage1))
        lines_makefile.append("\t%s %s" % ("python", script_hadd_stage1))
        lines_makefile.append("")
        self.filesToClean.append(self.histogramFile_hadd_stage1)

    def addToMakefile_addBackgrounds(self, lines_makefile):
        for key in self.histogramFile_addBackgrounds.keys():
            lines_makefile.append("%s: %s" % (self.histogramFile_addBackgrounds[key], self.histogramFile_hadd_stage1))
            lines_makefile.append("\t%s %s" % (self.executable_addBackgrounds, self.cfgFile_addBackgrounds_modified[key]))
            lines_makefile.append("")
            self.filesToClean.append(self.histogramFile_addBackgrounds[key])

    def addToMakefile_hadd_stage1_5(self, lines_makefile):
        """Adds the commands to Makefile that are necessary for building the intermediate histogram file
           that is used as input for data-driven background estimation.
        """
        script_hadd_stage1_5 = self.create_hadd_python_file(self.inputFiles_hadd_stage1_5, self.histogramFile_hadd_stage1_5, "stage1_5")
        lines_makefile.append("%s: %s" % (self.histogramFile_hadd_stage1_5, " ".join(self.inputFiles_hadd_stage1_5)))
        lines_makefile.append("\t%s %s" % ("rm -f", self.histogramFile_hadd_stage1_5))
        lines_makefile.append("\t%s %s" % ("python", script_hadd_stage1_5))
        lines_makefile.append("")
        self.filesToClean.append(self.histogramFile_hadd_stage1_5)

    def addToMakefile_backgrounds_from_data(self, lines_makefile):
        """Adds the commands to Makefile that are necessary for adding the data-driven background estimates.
           Default implementation is a dummy and does not actually add any histograms.
        """
        return

    def addToMakefile_hadd_stage2(self, lines_makefile):
        """Adds the commands to Makefile that are necessary for building the final histogram file.
        """
        script_hadd_stage2 = self.create_hadd_python_file(self.inputFiles_hadd_stage2, self.histogramFile_hadd_stage2, "stage2")
        lines_makefile.append("%s: %s" % (self.histogramFile_hadd_stage2, " ".join(self.inputFiles_hadd_stage2)))
        lines_makefile.append("\t%s %s" % ("rm -f", self.histogramFile_hadd_stage2))
        lines_makefile.append("\t%s %s" % ("python", script_hadd_stage2))
        lines_makefile.append("")
        self.filesToClean.append(self.histogramFile_hadd_stage2)

    def addToMakefile_outRoot(self, lines_makefile):
        """Adds the commands to Makefile that are necessary for building the final condensed *.root output file
           containing a TTree of all selected event variables specific to a given channel.
        """
        if not self.rootOutputAux:
            return
        lines_makefile.append("selEventTree_hadd: %s\n" % ' '.join(
            map(lambda x: x[0], self.rootOutputAux.values())))
        for rootOutput in self.rootOutputAux.values():
            lines_makefile.append("%s: %s" % (rootOutput[0], self.histogramFile_hadd_stage1))
            lines_makefile.append(
                "\thadd -f %s $(shell for f in `ls %s`; do echo -ne $$f\" \"; done)\n" % (rootOutput[0], rootOutput[1]))
        lines_makefile.append("")

    def addToMakefile_prep_dcard(self, lines_makefile):
        """Adds the commands to Makefile that are necessary for building the datacards.
        """
        for key in self.datacardFiles.keys():
            lines_makefile.append("%s: %s" % (
                self.datacardFiles[key], self.histogramFile_hadd_stage2))
            lines_makefile.append("\t%s %s" % (
                self.executable_prep_dcard, self.cfgFile_prep_dcard_modified[key]))
            self.filesToClean.append(self.datacardFiles[key])
        lines_makefile.append("")

    def addToMakefile_make_plots(self, lines_makefile):
        """Adds the commands to Makefile that are necessary for building the datacards.
        """
        for idxJob, cfg_file_modified in enumerate(self.cfgFiles_make_plots_modified):
            lines_makefile.append("makePlots%i: %s" % (
                idxJob, self.histogramFile_hadd_stage2))
            lines_makefile.append("\t%s %s" % (
                self.executable_make_plots, cfg_file_modified))
            lines_makefile.append("")

    def createMakefile(self, lines_makefile):
        """Creates Makefile that runs the complete analysis workfow.
        """
        targets = []
        targets.extend(self.datacardFiles.values())
        if self.rootOutputAux:
            targets.append("selEventTree_hadd")
        for idxJob in range(len(self.cfgFiles_make_plots_modified)):
            targets.append("makePlots%i" % idxJob)
        for rootOutput in self.rootOutputAux.values():
            self.filesToClean.append(rootOutput[0])
        tools_createMakefile(self.makefile, targets, lines_makefile, self.filesToClean, self.is_sbatch)
        logging.info("Run it with:\tmake -f %s -j %i " %
            (self.makefile, self.num_parallel_jobs))

    def create(self):
        """Creates all config files necessary for runing the complete analysis workfow.
        """
        raise ValueError(
            "Method 'create' not implemented in derrived class !!")

    def run(self):
        """Runs the complete analysis workfow -- either locally or on the batch system.
        """
        run_cmd("make -f %s -j %i " % (self.makefile, self.num_parallel_jobs),
            False, self.stdout_file, self.stderr_file)
