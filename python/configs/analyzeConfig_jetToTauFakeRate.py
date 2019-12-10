from tthAnalysis.HiggsToTauTau.configs.analyzeConfig import *
from tthAnalysis.HiggsToTauTau.jobTools import create_if_not_exists
from tthAnalysis.HiggsToTauTau.analysisTools import initDict, getKey, create_cfg, generateInputFileList
from tthAnalysis.HiggsToTauTau.common import logging

class analyzeConfig_jetToTauFakeRate(analyzeConfig):
  """
  Configuration metadata needed to run analysis in a single go.

  Sets up a folder structure by defining full path names; no directory creation is delegated here.

  Args specific to analyzeConfig_jetToTauFakeRate:
    charge_selection: either `OS` or `SS` (opposite-sign or same-sign of the electron+muon pair)
    hadTau_selections: list of tau ID discriminators to check

  See $CMSSW_BASE/src/tthAnalysis/HiggsToTauTau/python/analyzeConfig.py
  for documentation of further Args.

  """
  def __init__(self,
        configDir,
        outputDir,
        executable_analyze,
        samples,
        charge_selections,
        jet_minPt,
        jet_maxPt,
        jet_minAbsEta,
        jet_maxAbsEta,
        hadTau_selection_tight,
        hadTau_selection_denominator,
        hadTau_selections_numerator,
        absEtaBins,
        ptBins,
        decayModes,
        jet_cleaning_by_index,
        gen_matching_by_index,
        central_or_shifts,
        max_files_per_job,
        era,
        use_lumi,
        lumi,
        check_output_files,
        running_method,
        num_parallel_jobs,
        executable_comp_jetToTauFakeRate,
        verbose    = False,
        hlt_filter = False,
        dry_run    = False,
        isDebug    = False,
        use_home   = False,
      ):
    analyzeConfig.__init__(self,
      configDir             = configDir,
      outputDir             = outputDir,
      executable_analyze    = executable_analyze,
      channel               = "jetToTauFakeRate",
      samples               = samples,
      jet_cleaning_by_index = jet_cleaning_by_index,
      gen_matching_by_index = gen_matching_by_index,
      central_or_shifts     = central_or_shifts,
      max_files_per_job     = max_files_per_job,
      era                   = era,
      use_lumi              = use_lumi,
      lumi                  = lumi,
      check_output_files    = check_output_files,
      running_method        = running_method,
      num_parallel_jobs     = num_parallel_jobs,
      histograms_to_fit     = [],
      triggers              = [ '1e', '1mu', '1e1mu' ],
      verbose               = verbose,
      dry_run               = dry_run,
      isDebug               = isDebug,
      use_home              = use_home,
    )

    self.charge_selections = charge_selections
    self.hlt_filter = hlt_filter

    self.jet_minPt = jet_minPt
    self.jet_maxPt = jet_maxPt
    self.jet_minAbsEta = jet_minAbsEta
    self.jet_maxAbsEta = jet_maxAbsEta

    self.hadTau_selection_tight = hadTau_selection_tight
    self.hadTau_selection_denominator = hadTau_selection_denominator
    self.hadTau_selections_numerator = hadTau_selections_numerator

    self.absEtaBins = absEtaBins
    self.ptBins = ptBins
    self.decayModes = decayModes

    self.executable_comp_jetToTauFakeRate = executable_comp_jetToTauFakeRate

    self.cfgFile_analyze = os.path.join(self.template_dir, "analyze_jetToTauFakeRate_cfg.py")
    self.cfgFile_comp_jetToTauFakeRate = os.path.join(self.template_dir, "comp_jetToTauFakeRate_cfg.py")
    self.jobOptions_comp_jetToTauFakeRate = {}
    self.cfgFile_make_plots = os.path.join(self.template_dir, "makePlots_jetToTauFakeRate_cfg.py")
    self.cfgFile_make_plots_denominator = os.path.join(self.template_dir, "makePlots_jetToTauFakeRate_denominator_cfg.py")

    self.make_plots_backgrounds = [ "TT", "TTW", "TTWW", "TTZ", "EWK", "Rares" ]
    self.processes_to_comp = self.make_plots_backgrounds + [ "ttH" ]

  def createCfg_analyze(self, jobOptions, sample_info):
    """Create python configuration file for the analyze_jetToTauFakeRate executable (analysis code)

    Args:
      inputFiles: list of input files (Ntuples)
      outputFile: output file of the job -- a ROOT file containing histogram
      process: either `TT`, `TTW`, `TTWW`, `TTZ`, `EWK`, `Rares`, `data_obs`, `ttH_hww`, `ttH_hzz` or `ttH_htt`
      is_mc: flag indicating whether job runs on MC (True) or data (False)
      lumi_scale: event weight (= xsection * luminosity / number of events)
      central_or_shift: either 'central' or one of the systematic uncertainties defined in $CMSSW_BASE/src/tthAnalysis/HiggsToTauTau/bin/analyze_jetToTauFakeRate.cc
    """

    additionalJobOptions = [
      'chargeSelection',
      'jet_minPt',
      'jet_maxPt',
      'jet_minAbsEta',
      'jet_maxAbsEta',
      'hadTau_selection_tight',
      'hadTauSelection_denominator',
      'hadTauSelections_numerator',
      'absEtaBins',
      'decayModes'
    ]

    lines = super(analyzeConfig_jetToTauFakeRate, self).createCfg_analyze(jobOptions, sample_info, additionalJobOptions)
    create_cfg(self.cfgFile_analyze, jobOptions['cfgFile_modified'], lines)

  def createCfg_comp_jetToTauFakeRate(self, jobOptions):
    """Create python configuration file for the comp_jetToTauFakeRate executable

    Args:
      inputFiles: input file (the ROOT file produced by hadd_stage1)
      outputFile: output file of the job
    """
    lines = []
    lines.append("process.fwliteInput.fileNames = cms.vstring('%s')" % jobOptions['inputFile'])
    lines.append("process.fwliteOutput.fileName = cms.string('%s')" % os.path.basename(jobOptions['outputFile']))
    lines.append("process.comp_jetToTauFakeRate.looseRegion = cms.string('%s')" % jobOptions['looseRegion'])
    lines.append("process.comp_jetToTauFakeRate.tightRegion = cms.string('%s')" % jobOptions['tightRegion'])
    lines.append("process.comp_jetToTauFakeRate.processData = cms.string('data_obs')")
    lines.append("process.comp_jetToTauFakeRate.processesToSubtract = cms.vstring(")
    for process in self.processes_to_comp:
      lines.append("    '{process}t', '{process}l',".format(process = process))
    lines.append(")")
    lines.append("process.comp_jetToTauFakeRate.processMC = cms.string('TTj')")
    lines.append("process.comp_jetToTauFakeRate.absEtaBins = cms.vdouble(%s)" % jobOptions['absEtaBins'])
    lines.append("process.comp_jetToTauFakeRate.ptBins = cms.vdouble(%s)" % jobOptions['ptBins'])
    lines.append("process.comp_jetToTauFakeRate.decayModes = cms.vint32(%s)" % jobOptions['decayModes'])
    lines.append("process.comp_jetToTauFakeRate.hadTauSelections = cms.vstring(%s)" % jobOptions['hadTauSelections'])
    lines.append("process.comp_jetToTauFakeRate.outputFileName = cms.string('%s')" % jobOptions['plots_outputFileName'])
    create_cfg(self.cfgFile_comp_jetToTauFakeRate, jobOptions['cfgFile_modified'], lines)

  def addToMakefile_comp_jetToTauFakeRate(self, lines_makefile):
    if self.is_sbatch:
      lines_makefile.append("sbatch_comp_jetToTauFakeRate: %s" % " ".join([ jobOptions['inputFile'] for jobOptions in self.jobOptions_comp_jetToTauFakeRate.values() ]))
      lines_makefile.append("\t%s %s" % ("python", self.sbatchFile_comp_jetToTauFakeRate))
      lines_makefile.append("")
    for jobOptions in self.jobOptions_comp_jetToTauFakeRate.values():
      if self.is_makefile:
        lines_makefile.append("%s: %s" % (jobOptions['outputFile'], jobOptions['inputFile']))
        lines_makefile.append("\t%s %s" % (self.executable_comp_jetToTauFakeRate, jobOptions['cfgFile_modified']))
        lines_makefile.append("")
      elif self.is_sbatch:
        lines_makefile.append("%s: %s" % (jobOptions['outputFile'], "sbatch_comp_jetToTauFakeRate"))
        lines_makefile.append("\t%s" % ":") # CV: null command
        lines_makefile.append("")
      self.filesToClean.append(jobOptions['outputFile'])

  def create(self):
    """Creates all necessary config files and runs the complete analysis workfow -- either locally or on the batch system
    """

    for sample_name, sample_info in self.samples.items():
      if not sample_info["use_it"]:
        continue
      process_name = sample_info["process_name_specific"]
      sample_category = sample_info["sample_category"]
      is_mc = (sample_info["type"] == "mc")

      logging.info("Building dictionaries for sample %s..." % process_name)
      for charge_selection in self.charge_selections:
        central_or_shift_extensions = ["", "hadd", "addBackgrounds"]
        central_or_shifts_extended = central_or_shift_extensions + self.central_or_shifts
        for central_or_shift_or_dummy in central_or_shifts_extended:
          process_name_extended = [ process_name, "hadd" ]
          for process_name_or_dummy in process_name_extended:
            if central_or_shift_or_dummy in [ "hadd" ] and process_name_or_dummy in [ "hadd" ]:
              continue
            if central_or_shift_or_dummy != "central" and central_or_shift_or_dummy not in central_or_shift_extensions:
              if not is_mc:
                continue
              if not self.accept_central_or_shift(central_or_shift_or_dummy, sample_info):
                continue

            key_dir = getKey(process_name_or_dummy, charge_selection, central_or_shift_or_dummy)
            for dir_type in [ DKEY_CFGS, DKEY_HIST, DKEY_LOGS, DKEY_RLES ]:
              initDict(self.dirs, [ key_dir, dir_type ])
              if dir_type in [ DKEY_CFGS, DKEY_LOGS ]:
                self.dirs[key_dir][dir_type] = os.path.join(self.configDir, dir_type, self.channel,
                  "_".join([ charge_selection ]), process_name_or_dummy, central_or_shift_or_dummy)
              else:
                self.dirs[key_dir][dir_type] = os.path.join(self.outputDir, dir_type, self.channel,
                  "_".join([ charge_selection ]), process_name_or_dummy, central_or_shift_or_dummy)
    for subdirectory in [ "comp_jetToTauFakeRate", "makePlots" ]:
      key_dir = getKey(subdirectory)
      for dir_type in [ DKEY_CFGS, DKEY_HIST, DKEY_LOGS, DKEY_ROOT, DKEY_DCRD, DKEY_PLOT ]:
        initDict(self.dirs, [ key_dir, dir_type ])
        if dir_type in [ DKEY_CFGS, DKEY_LOGS, DKEY_DCRD, DKEY_PLOT ]:
          self.dirs[key_dir][dir_type] = os.path.join(self.configDir, dir_type, self.channel, subdirectory)
        else:
          self.dirs[key_dir][dir_type] = os.path.join(self.outputDir, dir_type, self.channel, subdirectory)
    for dir_type in [ DKEY_CFGS, DKEY_SCRIPTS, DKEY_HIST, DKEY_LOGS, DKEY_DCRD, DKEY_PLOT, DKEY_HADD_RT ]:
      initDict(self.dirs, [ dir_type ])
      if dir_type in [ DKEY_CFGS, DKEY_SCRIPTS, DKEY_LOGS, DKEY_DCRD, DKEY_PLOT, DKEY_HADD_RT ]:
        self.dirs[dir_type] = os.path.join(self.configDir, dir_type, self.channel)
      else:
        self.dirs[dir_type] = os.path.join(self.outputDir, dir_type, self.channel)

    numDirectories = 0
    for key in self.dirs.keys():
      if type(self.dirs[key]) == dict:
        numDirectories += len(self.dirs[key])
      else:
        numDirectories += 1
    logging.info("Creating directory structure (numDirectories = %i)" % numDirectories)
    numDirectories_created = 0;
    frac = 1
    for key in self.dirs.keys():
      if type(self.dirs[key]) == dict:
        for dir_type in self.dirs[key].keys():
          create_if_not_exists(self.dirs[key][dir_type])
        numDirectories_created += len(self.dirs[key])
      else:
        create_if_not_exists(self.dirs[key])
        numDirectories_created = numDirectories_created + 1
      while 100*numDirectories_created >= frac*numDirectories:
        logging.info(" %i%% completed" % frac)
        frac = frac + 1
    logging.info("Done.")

    inputFileLists = {}
    for sample_name, sample_info in self.samples.items():
      if not sample_info["use_it"]:
        continue
      logging.info("Checking input files for sample %s" % sample_info["process_name_specific"])
      inputFileLists[sample_name] = generateInputFileList(sample_info, self.max_files_per_job)

    self.inputFileIds = {}
    for sample_name, sample_info in self.samples.items():
      if not sample_info["use_it"]:
        continue

      process_name = sample_info["process_name_specific"]
      inputFileList = inputFileLists[sample_name]

      logging.info("Creating configuration files to run '%s' for sample %s" % (self.executable_analyze, process_name))

      is_mc = (sample_info["type"] == "mc")
      sample_category = sample_info["sample_category"]

      for charge_selection in self.charge_selections:
        for central_or_shift in self.central_or_shifts:
          
          if central_or_shift != "central" and not is_mc:
            continue
          if not self.accept_central_or_shift(central_or_shift, sample_info):
            continue

          # build config files for executing analysis code
          key_analyze_dir = getKey(process_name, charge_selection, central_or_shift)

          for jobId in inputFileList.keys():

            analyze_job_tuple = (process_name, charge_selection, central_or_shift, jobId)
            key_analyze_job = getKey(*analyze_job_tuple)
            ntupleFiles = inputFileList[jobId]
            if len(ntupleFiles) == 0:
              logging.warning("No input ntuples for %s --> skipping job !!" % (key_analyze_job))
              continue

            cfgFile_modified_path = os.path.join(self.dirs[key_analyze_dir][DKEY_CFGS], "analyze_%s_%s_%s_%i_cfg.py" % analyze_job_tuple)
            logFile_path = os.path.join(self.dirs[key_analyze_dir][DKEY_LOGS], "analyze_%s_%s_%s_%i.log" % analyze_job_tuple)
            histogramFile_path = os.path.join(self.dirs[key_analyze_dir][DKEY_HIST], "analyze_%s_%s_%s_%i.root" % analyze_job_tuple)

            self.jobOptions_analyze[key_analyze_job] = {
              'ntupleFiles'                 : ntupleFiles,
              'cfgFile_modified'            : cfgFile_modified_path,
              'histogramFile'               : histogramFile_path,
              'logFile'                     : logFile_path,
              'chargeSelection'             : charge_selection,
              'jet_minPt'                   : self.jet_minPt,
              'jet_maxPt'                   : self.jet_maxPt,
              'jet_minAbsEta'               : self.jet_minAbsEta,
              'jet_maxAbsEta'               : self.jet_maxAbsEta,
              'hadTau_selection_tight'      : self.hadTau_selection_tight,
              'hadTauSelection_denominator' : self.hadTau_selection_denominator,
              'hadTauSelections_numerator'  : self.hadTau_selections_numerator,
              'absEtaBins'                  : self.absEtaBins,
              'decayModes'                  : self.decayModes,
              'central_or_shift'            : central_or_shift,
              'useObjectMultiplicity'       : self.era in [ '2018' ],
              'apply_hlt_filter'            : self.hlt_filter,
            }
            self.createCfg_analyze(self.jobOptions_analyze[key_analyze_job], sample_info)

            # initialize input and output file names for hadd_stage1
            key_hadd_stage1_dir = getKey(process_name, charge_selection)
            hadd_stage1_job_tuple = (process_name, charge_selection)
            key_hadd_stage1_job = getKey(*hadd_stage1_job_tuple)
            if not key_hadd_stage1_job in self.inputFiles_hadd_stage1:
              self.inputFiles_hadd_stage1[key_hadd_stage1_job] = []
            self.inputFiles_hadd_stage1[key_hadd_stage1_job].append(self.jobOptions_analyze[key_analyze_job]['histogramFile'])
            self.outputFile_hadd_stage1[key_hadd_stage1_job] = os.path.join(self.dirs[key_hadd_stage1_dir][DKEY_HIST],
                                                                            "hadd_stage1_%s_%s.root" % hadd_stage1_job_tuple)

        # initialize input and output file names for hadd_stage2
        key_hadd_stage1_job = getKey(process_name, charge_selection)
        key_hadd_stage2_dir = getKey("hadd", charge_selection)
        key_hadd_stage2_job = getKey(charge_selection)
        if not key_hadd_stage2_job in self.inputFiles_hadd_stage2:
          self.inputFiles_hadd_stage2[key_hadd_stage2_job] = []
        self.inputFiles_hadd_stage2[key_hadd_stage2_job].append(self.outputFile_hadd_stage1[key_hadd_stage1_job])
        self.outputFile_hadd_stage2[key_hadd_stage2_job] = os.path.join(self.dirs[key_hadd_stage2_dir][DKEY_HIST],
                                                                        "hadd_stage2_%s.root" % charge_selection)

    logging.info("Creating configuration files for executing 'comp_jetToTauFakeRate'")
    for charge_selection in self.charge_selections:
      key_hadd_stage2_job = getKey(charge_selection)
      key_comp_jetToTauFakeRate_dir = getKey("comp_jetToTauFakeRate")
      key_comp_jetToTauFakeRate_job = getKey(charge_selection)
      self.jobOptions_comp_jetToTauFakeRate[key_comp_jetToTauFakeRate_job] = {
        'inputFile' : self.outputFile_hadd_stage2[key_hadd_stage2_job],
        'cfgFile_modified' : os.path.join(
          self.dirs[DKEY_CFGS], "comp_jetToTauFakeRate_%s_cfg.py" % charge_selection),
        'outputFile' : os.path.join(
          self.dirs[DKEY_HIST], "comp_jetToTauFakeRate_%s.root" % charge_selection),
        'logFile' : os.path.join(
          self.dirs[DKEY_LOGS], "comp_jetToTauFakeRate_%s.log" % charge_selection),
        'looseRegion' : "jetToTauFakeRate_%s/denominator/" % charge_selection,
        'tightRegion' : "jetToTauFakeRate_%s/numerator/" % charge_selection,
        'absEtaBins' : self.absEtaBins,
        'ptBins' : self.ptBins,
        'decayModes' : self.decayModes,
        'hadTauSelections' : self.hadTau_selections_numerator,
        'plots_outputFileName' : os.path.join(self.dirs[key_comp_jetToTauFakeRate_dir][DKEY_PLOT], "comp_jetToTauFakeRate.png")
      }
      self.createCfg_comp_jetToTauFakeRate(self.jobOptions_comp_jetToTauFakeRate[key_comp_jetToTauFakeRate_job])
      self.targets.append(self.jobOptions_comp_jetToTauFakeRate[key_comp_jetToTauFakeRate_job]['outputFile'])

    logging.info("Creating configuration files to run 'makePlots'")
    for charge_selection in self.charge_selections:
      key_hadd_stage2_job = getKey(charge_selection)
      key_makePlots_dir = getKey("makePlots")
      key_makePlots_job = getKey(charge_selection)      
      self.jobOptions_make_plots[key_makePlots_job] = {
        'executable' : self.executable_make_plots,
        'inputFile' : self.outputFile_hadd_stage2[key_hadd_stage2_job],
        'cfgFile_modified' : os.path.join(
          self.dirs[key_makePlots_dir][DKEY_CFGS], "makePlots_%s_cfg.py" % self.channel),
        'outputFile' : os.path.join(
          self.dirs[key_makePlots_dir][DKEY_PLOT], "makePlots_%s.png" % self.channel),
        'histogramDir' : "jetToTauFakeRate_%s" % charge_selection,
        'label' : None,
        'make_plots_backgrounds' : self.make_plots_backgrounds,
      }
      self.createCfg_makePlots(self.jobOptions_make_plots[key_makePlots_job])
      self.cfgFile_make_plots = self.cfgFile_make_plots_denominator
      for absEtaBin in [ "absEtaLt1_5", "absEta1_5to9_9" ]:
        key_hadd_stage2_job = getKey(charge_selection)
        key_makePlots_job = getKey(charge_selection, absEtaBin, "denominator")        
        self.jobOptions_make_plots[key_makePlots_job] = {
          'executable' : self.executable_make_plots,
          'inputFile' : self.outputFile_hadd_stage2[key_hadd_stage2_job],
          'cfgFile_modified' : os.path.join(
            self.dirs[key_makePlots_dir][DKEY_CFGS], "makePlots_%s_%s_denominator_%s_cfg.py" % (self.channel, charge_selection, absEtaBin)),
          'outputFile' : os.path.join(
            self.dirs[key_makePlots_dir][DKEY_PLOT], "makePlots_%s_%s_denominator_%s.png" % (self.channel, charge_selection, absEtaBin)),
          'histogramDir' : "jetToTauFakeRate_%s/denominator/%s" % (charge_selection, absEtaBin),
          'label' : None,
          'make_plots_backgrounds' : self.make_plots_backgrounds,
        }
        self.createCfg_makePlots(self.jobOptions_make_plots[key_makePlots_job])
        for hadTau_selection_numerator in self.hadTau_selections_numerator:
          key_hadd_stage2_job = getKey(charge_selection)
          key_makePlots_job = getKey(charge_selection, absEtaBin, "numerator", hadTau_selection_numerator)
          self.jobOptions_make_plots[key_makePlots_job] = {
            'executable' : self.executable_make_plots,
            'inputFile' : self.outputFile_hadd_stage2[key_hadd_stage2_job],
            'cfgFile_modified' : os.path.join(
              self.dirs[key_makePlots_dir][DKEY_CFGS], "makePlots_%s_%s_numerator_%s_%s_cfg.py" % (self.channel, charge_selection, hadTau_selection_numerator, absEtaBin)),
            'outputFile' : os.path.join(
              self.dirs[key_makePlots_dir][DKEY_PLOT], "makePlots_%s_%s_numerator_%s_%s.png" % (self.channel, charge_selection, hadTau_selection_numerator, absEtaBin)),
            'histogramDir' : "jetToTauFakeRate_%s/numerator/%s/%s" % (charge_selection, hadTau_selection_numerator, absEtaBin),
            'label' : None,
            'make_plots_backgrounds' : self.make_plots_backgrounds,
          }
          self.createCfg_makePlots(self.jobOptions_make_plots[key_makePlots_job])

    if self.is_sbatch:
      logging.info("Creating script for submitting '%s' jobs to batch system" % self.executable_analyze)
      self.sbatchFile_analyze = os.path.join(self.dirs[DKEY_SCRIPTS], "sbatch_analyze_%s.py" % self.channel)
      self.createScript_sbatch_analyze(self.executable_analyze, self.sbatchFile_analyze, self.jobOptions_analyze)
      logging.info("Creating script for submitting '%s' jobs to batch system" % self.executable_comp_jetToTauFakeRate)
      self.sbatchFile_comp_jetToTauFakeRate = os.path.join(self.dirs[DKEY_SCRIPTS], "sbatch_comp_jetToTauFakeRate.py")
      self.createScript_sbatch(self.executable_comp_jetToTauFakeRate, self.sbatchFile_comp_jetToTauFakeRate, self.jobOptions_comp_jetToTauFakeRate)

    lines_makefile = []
    self.addToMakefile_analyze(lines_makefile)
    self.addToMakefile_hadd_stage1(lines_makefile)
    self.addToMakefile_hadd_stage2(lines_makefile, make_dependency = "phony_hadd_stage1")
    self.addToMakefile_comp_jetToTauFakeRate(lines_makefile)
    self.addToMakefile_make_plots(lines_makefile)
    self.createMakefile(lines_makefile)

    logging.info("Done.")

    return self.num_jobs
