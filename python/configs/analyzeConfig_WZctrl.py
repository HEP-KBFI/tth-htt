import logging

from tthAnalysis.HiggsToTauTau.configs.analyzeConfig import *
from tthAnalysis.HiggsToTauTau.jobTools import create_if_not_exists
from tthAnalysis.HiggsToTauTau.analysisTools import initDict, getKey, create_cfg, createFile, generateInputFileList

class analyzeConfig_WZctrl(analyzeConfig):
  """Configuration metadata needed to run analysis in a single go.

  Sets up a folder structure by defining full path names; no directory creation is delegated here.

  See $CMSSW_BASE/src/tthAnalysis/HiggsToTauTau/python/analyzeConfig.py
  for documentation of Args.

  """
  def __init__(self, configDir, outputDir, executable_analyze, cfgFile_analyze, samples, hadTau_selection, central_or_shifts,
               max_files_per_job, era, use_lumi, lumi, check_input_files, running_method, num_parallel_jobs,
               histograms_to_fit, select_rle_output = False, executable_prep_dcard="prepareDatacards",
               verbose = False, hlt_filter = False, dry_run = False, isDebug = False, use_home = True):
    analyzeConfig.__init__(self, configDir, outputDir, executable_analyze, "WZctrl", central_or_shifts,
      max_files_per_job, era, use_lumi, lumi, check_input_files, running_method, num_parallel_jobs,
      histograms_to_fit, executable_prep_dcard = executable_prep_dcard, verbose = verbose,
      dry_run = dry_run, isDebug = isDebug, use_home = use_home,
      triggers = [ '1e', '1mu', '2e', '2mu', '1e1mu', '1e2mu', '2e1mu', '3e', '3mu' ],
    )

    self.samples = samples

    self.hadTau_selection_part2 = hadTau_selection

    self.prep_dcard_processesToCopy = [ "data_obs", "TT", "TTW", "TTWW", "TTZ", "WZ", "EWK", "Rares" ]
    self.make_plots_backgrounds = [ "TT", "TTW", "TTWW", "TTZ", "signal", "EWK", "Rares" ]
    self.make_plots_signal = "WZ"

    self.cfgFile_analyze = os.path.join(self.template_dir, cfgFile_analyze)
    self.histogramDir_prep_dcard = "WZctrl"
    self.evtSelections = [ "2lepton", "3lepton", "2lepton_1tau" ]
    self.cfgFile_make_plots = os.path.join(self.template_dir, "makePlots_WZctrl_cfg.py")

    self.select_rle_output = select_rle_output
    self.hlt_filter = hlt_filter

  def createCfg_analyze(self, jobOptions, sample_info):
    """Create python configuration file for the analyze_WZctrl executable (analysis code)

    Args:
      inputFiles: list of input files (Ntuples)
      outputFile: output file of the job -- a ROOT file containing histogram
      process: either `TT`, `TTW`, `TTZ`, `WZ`, `EWK`, `Rares`, `data_obs`, `ttH_hww`, `ttH_hzz` or `ttH_htt`
      is_mc: flag indicating whether job runs on MC (True) or data (False)
      lumi_scale: event weight (= xsection * luminosity / number of events)
      central_or_shift: either 'central' or one of the systematic uncertainties defined in $CMSSW_BASE/src/tthAnalysis/HiggsToTauTau/bin/analyze_WZctrl.cc
    """
    lines = super(analyzeConfig_WZctrl, self).createCfg_analyze(jobOptions, sample_info)
    create_cfg(self.cfgFile_analyze, jobOptions['cfgFile_modified'], lines)

  def create(self):
    """Creates all necessary config files and runs the complete analysis workfow -- either locally or on the batch system
    """

    for sample_name, sample_info in self.samples.items():
      if not sample_info["use_it"] or sample_info["sample_category"] in [ "additional_signal_overlap", "background_data_estimate" ]:
        continue
      process_name = sample_info["process_name_specific"]
      key_dir = getKey(process_name)
      for dir_type in [ DKEY_CFGS, DKEY_HIST, DKEY_LOGS, DKEY_RLES ]:
        initDict(self.dirs, [ key_dir, dir_type ])
        if dir_type in [ DKEY_CFGS, DKEY_LOGS ]:
          self.dirs[key_dir][dir_type] = os.path.join(self.configDir, dir_type, self.channel, "", process_name)
        else:
          self.dirs[key_dir][dir_type] = os.path.join(self.outputDir, dir_type, self.channel, "", process_name)
    for dir_type in [ DKEY_CFGS, DKEY_SCRIPTS, DKEY_HIST, DKEY_LOGS, DKEY_DCRD, DKEY_PLOT, DKEY_HADD_RT ]:
      initDict(self.dirs, [ dir_type ])
      if dir_type in [ DKEY_CFGS, DKEY_SCRIPTS, DKEY_LOGS, DKEY_DCRD, DKEY_PLOT, DKEY_HADD_RT ]:
        self.dirs[dir_type] = os.path.join(self.configDir, dir_type, self.channel)
      else:
        self.dirs[dir_type] = os.path.join(self.outputDir, dir_type, self.channel)
    ##print "self.dirs = ", self.dirs

    for key in self.dirs.keys():
      if type(self.dirs[key]) == dict:
        for dir_type in self.dirs[key].keys():
          create_if_not_exists(self.dirs[key][dir_type])
      else:
        create_if_not_exists(self.dirs[key])

    inputFileLists = {}
    for sample_name, sample_info in self.samples.items():
      if not sample_info["use_it"] or sample_info["sample_category"] in [ "additional_signal_overlap", "background_data_estimate" ]:
        continue
      logging.info("Checking input files for sample %s" % sample_info["process_name_specific"])
      inputFileLists[sample_name] = generateInputFileList(sample_info, self.max_files_per_job, self.check_input_files)

    for sample_name, sample_info in self.samples.items():
      if not sample_info["use_it"] or sample_info["sample_category"] in [ "additional_signal_overlap", "background_data_estimate" ]:
        continue
      process_name = sample_info["process_name_specific"]
      logging.info("Creating configuration files to run '%s' for sample %s" % (self.executable_analyze, process_name))

      sample_category = sample_info["sample_category"]
      is_mc = (sample_info["type"] == "mc")
      is_signal = (sample_category == "signal")

      for central_or_shift in self.central_or_shifts:

        inputFileList = inputFileLists[sample_name]
        for jobId in inputFileList.keys():
          if central_or_shift != "central" and not is_mc:
            continue
          if central_or_shift.startswith("CMS_ttHl_thu_shape_ttH") and sample_category != "signal":
            continue
          if central_or_shift.startswith("CMS_ttHl_thu_shape_ttW") and sample_category != "TTW":
            continue
          if central_or_shift.startswith("CMS_ttHl_thu_shape_ttZ") and sample_category != "TTZ":
            continue

          # build config files for executing analysis code
          key_dir = getKey(process_name)
          key_analyze_job = getKey(process_name, central_or_shift, jobId)
          ntupleFiles = inputFileList[jobId]
          if len(ntupleFiles) == 0:
            print "Warning: ntupleFiles['%s'] = %s --> skipping job !!" % (key_job, ntupleFiles)
            continue

          cfg_key = getKey(self.channel, process_name, central_or_shift, jobId)
          cfgFile_modified_path = os.path.join(self.dirs[key_dir][DKEY_CFGS], "analyze_%s_cfg.py" % cfg_key)
          histogramFile_path    = os.path.join(self.dirs[key_dir][DKEY_HIST], "%s.root" % key_analyze_job)
          logFile_path          = os.path.join(self.dirs[key_dir][DKEY_LOGS], "analyze_%s.log" % cfg_key)
          rleOutputFile_path    = os.path.join(self.dirs[key_dir][DKEY_RLES], "rle_%s.txt" % cfg_key) if self.select_rle_output else ""

          self.jobOptions_analyze[key_analyze_job] = {
            'ntupleFiles'              : ntupleFiles,
            'cfgFile_modified'         : cfgFile_modified_path,
            'histogramFile'            : histogramFile_path,
            'logFile'                  : logFile_path,
            'selEventsFileName_output' : rleOutputFile_path,
            'sample_category'          : sample_category,
            'hadTauSelection'          : self.hadTau_selection_part2,
            'central_or_shift'         : central_or_shift,
            'apply_hlt_filter'         : self.hlt_filter,
          }
          self.createCfg_analyze(self.jobOptions_analyze[key_analyze_job], sample_info)

          # initialize input and output file names for hadd_stage1
          key_hadd_stage1 = getKey(process_name)
          if not key_hadd_stage1 in self.inputFiles_hadd_stage1.keys():
            self.inputFiles_hadd_stage1[key_hadd_stage1] = []
          self.inputFiles_hadd_stage1[key_hadd_stage1].append(self.jobOptions_analyze[key_analyze_job]['histogramFile'])
          self.outputFile_hadd_stage1[key_hadd_stage1] = os.path.join(self.dirs[DKEY_HIST], "histograms_harvested_stage1_%s_%s.root" % \
            (self.channel, process_name))

      # initialize input and output file names for hadd_stage2
      key_hadd_stage1 = getKey(process_name)
      key_hadd_stage2 = getKey("all")
      if not key_hadd_stage2 in self.inputFiles_hadd_stage2.keys():
        self.inputFiles_hadd_stage2[key_hadd_stage2] = []
      self.inputFiles_hadd_stage2[key_hadd_stage2].append(self.outputFile_hadd_stage1[key_hadd_stage1])
      self.outputFile_hadd_stage2[key_hadd_stage2] = os.path.join(self.dirs[DKEY_HIST], "histograms_harvested_stage2_%s.root" % \
        (self.channel))

    logging.info("Creating configuration files to run 'prepareDatacards'")
    for evtSelection in self.evtSelections:
      for histogramToFit in self.histograms_to_fit:
        key_prep_dcard_job = getKey(evtSelection, histogramToFit)
        key_hadd_stage2 = getKey("all")
        self.jobOptions_prep_dcard[key_prep_dcard_job] = {
          'inputFile' : self.outputFile_hadd_stage2[key_hadd_stage2],
          'cfgFile_modified' : os.path.join(self.dirs[DKEY_CFGS], "prepareDatacards_%s_%s_%s_cfg.py" % (self.channel, evtSelection, histogramToFit)),
          'datacardFile' : os.path.join(self.dirs[DKEY_DCRD], "prepareDatacards_%s_%s_%s.root" % (self.channel, evtSelection, histogramToFit)),
          'histogramDir' : "_".join([ self.histogramDir_prep_dcard, evtSelection ]),
          'histogramToFit' : histogramToFit,
          'label' : None
        }
        self.createCfg_prep_dcard(self.jobOptions_prep_dcard[key_prep_dcard_job])

    logging.info("Creating configuration files to run 'makePlots'")
    for evtSelection in self.evtSelections:
      key_makePlots_job = getKey(evtSelection)
      key_hadd_stage2 = getKey("all")
      self.jobOptions_make_plots[key_makePlots_job] = {
        'executable' : self.executable_make_plots,
        'inputFile' : self.outputFile_hadd_stage2[key_hadd_stage2],
        'cfgFile_modified' : os.path.join(self.dirs[DKEY_CFGS], "makePlots_%s_%s_cfg.py" % (self.channel, evtSelection)),
        'outputFile' : os.path.join(self.dirs[DKEY_PLOT], "makePlots_%s_%s.png" % (self.channel, evtSelection)),
        'histogramDir' : "_".join([ self.histogramDir_prep_dcard, evtSelection ]),
        'label' : evtSelection,
        'make_plots_backgrounds' : self.make_plots_backgrounds
      }
      self.createCfg_makePlots(self.jobOptions_make_plots[key_makePlots_job])

    if self.is_sbatch:
      logging.info("Creating script for submitting '%s' jobs to batch system" % self.executable_analyze)
      self.sbatchFile_analyze = os.path.join(self.dirs[DKEY_SCRIPTS], "sbatch_analyze_%s.py" % self.channel)
      self.createScript_sbatch_analyze(
        executable      = self.executable_analyze,
        sbatchFile      = self.sbatchFile_analyze,
        jobOptions      = self.jobOptions_analyze,
        key_input_file  = 'ntupleFiles',
        key_output_file = 'histogramFile',
      )

    logging.info("Creating Makefile")
    lines_makefile = []
    self.addToMakefile_analyze(lines_makefile)
    self.addToMakefile_hadd_stage1(lines_makefile)
    self.addToMakefile_hadd_stage2(lines_makefile)
    self.addToMakefile_prep_dcard(lines_makefile)
    self.addToMakefile_make_plots(lines_makefile)
    self.createMakefile(lines_makefile)

    logging.info("Done")

    return self.num_jobs
