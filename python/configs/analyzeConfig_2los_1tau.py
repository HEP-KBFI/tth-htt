import logging

from tthAnalysis.HiggsToTauTau.configs.analyzeConfig import *
from tthAnalysis.HiggsToTauTau.jobTools import create_if_not_exists
from tthAnalysis.HiggsToTauTau.analysisTools import initDict, getKey, create_cfg, createFile, generateInputFileList

def get_lepton_and_hadTau_selection_and_frWeight(lepton_and_hadTau_selection, lepton_and_hadTau_frWeight):
  lepton_and_hadTau_selection_and_frWeight = lepton_and_hadTau_selection
  if lepton_and_hadTau_selection.startswith("Fakeable"):
    if lepton_and_hadTau_frWeight == "enabled":
      lepton_and_hadTau_selection_and_frWeight += "_wFakeRateWeights"
    elif lepton_and_hadTau_frWeight == "disabled":
      lepton_and_hadTau_selection_and_frWeight += "_woFakeRateWeights"
  lepton_and_hadTau_selection_and_frWeight = lepton_and_hadTau_selection_and_frWeight.replace("|", "_")
  return lepton_and_hadTau_selection_and_frWeight

def getHistogramDir(lepton_selection, hadTau_selection, lepton_and_hadTau_frWeight):
  histogramDir = "2los_1tau_%s" % (lepton_selection)
  if lepton_selection.find("Fakeable") != -1 or hadTau_selection.find("Fakeable") != -1:
    if lepton_and_hadTau_frWeight == "enabled":
      histogramDir += "_wFakeRateWeights"
    elif lepton_and_hadTau_frWeight == "disabled":
      histogramDir += "_woFakeRateWeights"
  return histogramDir

class analyzeConfig_2los_1tau(analyzeConfig):
  """Configuration metadata needed to run analysis in a single go.

     Sets up a folder structure by defining full path names; no directory creation is delegated here.

     Args specific to analyzeConfig_2los_1tau:
       lepton_selections: either `Tight`, `Loose` or `Fakeable`
       hadTau_selection: either `dR05iso[Loose|Medium|Tight]` or `dR03mva[Medium|Tight|VTight|VVTight]`

     See $CMSSW_BASE/src/tthAnalysis/HiggsToTauTau/python/analyzeConfig.py
     for documentation of further Args.

  """
  def __init__(self,
        configDir,
        outputDir,
        executable_analyze,
        cfgFile_analyze,
        samples,
        lep_mva_wp,
        hadTau_selection,
        applyFakeRateWeights,
        central_or_shifts,
        max_files_per_job,
        era,
        use_lumi,
        lumi,
        check_output_files,
        running_method,
        num_parallel_jobs,
        executable_addBackgrounds,
        executable_addFakes,
        histograms_to_fit,
        select_rle_output         = False,
        executable_prep_dcard     = "prepareDatacards",
        executable_add_syst_dcard = "addSystDatacards",
        verbose                   = False,
        dry_run                   = False,
        isDebug                   = False,
        hlt_filter                = False,
        use_home                  = True,
      ):
    analyzeConfig.__init__(self,
      configDir                 = configDir,
      outputDir                 = outputDir,
      executable_analyze        = executable_analyze,
      channel                   = "2los_1tau",
      samples                   = samples,
      lep_mva_wp                = lep_mva_wp,
      central_or_shifts         = central_or_shifts,
      max_files_per_job         = max_files_per_job,
      era                       = era,
      use_lumi                  = use_lumi,
      lumi                      = lumi,
      check_output_files        = check_output_files,
      running_method            = running_method,
      num_parallel_jobs         = num_parallel_jobs,
      histograms_to_fit         = histograms_to_fit,
      triggers                  = [ '1e', '1mu', '2e', '2mu', '1e1mu' ],
      executable_prep_dcard     = executable_prep_dcard,
      executable_add_syst_dcard = executable_add_syst_dcard,
      verbose                   = verbose,
      dry_run                   = dry_run,
      isDebug                   = isDebug,
      use_home                  = use_home,
    )

    self.lepton_and_hadTau_selections = [ "Tight", "Fakeable" ]
    self.lepton_and_hadTau_frWeights = [ "enabled", "disabled" ]
    self.hadTau_selection_part2 = hadTau_selection
    self.applyFakeRateWeights = applyFakeRateWeights
    run_mcClosure = 'central' not in self.central_or_shifts or len(central_or_shifts) > 1 or self.do_sync
    if self.era != '2017':
      logging.warning('mcClosure for lepton FR not possible for era %s' % self.era)
      run_mcClosure = False
    if run_mcClosure:
      # Run MC closure jobs only if the analysis is run w/ (at least some) systematic uncertainties
      #self.lepton_and_hadTau_selections.extend([ "Fakeable_mcClosure_all" ]) #TODO
      pass

    self.lepton_genMatches = [ "2l0g0j", "1l1g0j", "1l0g1j", "0l2g0j", "0l1g1j", "0l0g2j" ]
    self.hadTau_genMatches = [ "1t0e0m0j", "0t1e0m0j", "0t0e1m0j", "0t0e0m1j" ]

    self.apply_leptonGenMatching = None
    self.apply_hadTauGenMatching = None
    self.lepton_and_hadTau_genMatches_nonfakes = []
    self.lepton_and_hadTau_genMatches_conversions = []
    self.lepton_and_hadTau_genMatches_fakes = []
    self.lepton_and_hadTau_genMatches_gentau = []
    self.lepton_and_hadTau_genMatches_faketau = []
    if self.applyFakeRateWeights == "3L":
      self.apply_leptonGenMatching = True
      self.apply_hadTauGenMatching = True
      for lepton_genMatch in self.lepton_genMatches:
        for hadTau_genMatch in self.hadTau_genMatches:
          lepton_and_hadTau_genMatch = "&".join([ lepton_genMatch, hadTau_genMatch ])
          if lepton_genMatch.endswith("0g0j") and hadTau_genMatch.endswith("0j"):
            self.lepton_and_hadTau_genMatches_nonfakes.append(lepton_and_hadTau_genMatch)
          elif lepton_genMatch.endswith("0j") and hadTau_genMatch.endswith("0j"):
            self.lepton_and_hadTau_genMatches_conversions.append(lepton_and_hadTau_genMatch)
          else:
            self.lepton_and_hadTau_genMatches_fakes.append(lepton_and_hadTau_genMatch)
      if run_mcClosure:
        self.lepton_and_hadTau_selections.extend([ "Fakeable_mcClosure_e", "Fakeable_mcClosure_m", "Fakeable_mcClosure_t" ])
    elif applyFakeRateWeights == "2lepton":
      self.apply_leptonGenMatching = True
      self.apply_hadTauGenMatching = True
      for lepton_genMatch in self.lepton_genMatches:
        for hadTau_genMatch in self.hadTau_genMatches:
          lepton_and_hadTau_genMatch = "&".join([ lepton_genMatch, hadTau_genMatch ])
          if lepton_genMatch.endswith("0g0j"):
            self.lepton_and_hadTau_genMatches_nonfakes.append(lepton_and_hadTau_genMatch)
            if hadTau_genMatch.endswith("0j"):
              self.lepton_and_hadTau_genMatches_gentau.append(lepton_and_hadTau_genMatch)
            else:
              self.lepton_and_hadTau_genMatches_faketau.append(lepton_and_hadTau_genMatch)
          elif lepton_genMatch.endswith("0j"):
            self.lepton_and_hadTau_genMatches_conversions.append(lepton_and_hadTau_genMatch)
          else:
            self.lepton_and_hadTau_genMatches_fakes.append(lepton_and_hadTau_genMatch)
      if run_mcClosure:
        self.lepton_and_hadTau_selections.extend([ "Fakeable_mcClosure_e", "Fakeable_mcClosure_m" ])
    elif applyFakeRateWeights == "1tau":
      self.apply_leptonGenMatching = True
      self.apply_hadTauGenMatching = True
      for lepton_genMatch in self.lepton_genMatches:
        for hadTau_genMatch in self.hadTau_genMatches:
          if lepton_genMatch.find("0g") != -1 and hadTau_genMatch.endswith("0j"):
            self.lepton_and_hadTau_genMatches_nonfakes.append(hadTau_genMatch)
          elif hadTau_genMatch.endswith("0j"):
            self.lepton_and_hadTau_genMatches_conversions.append(hadTau_genMatch)
          else:
            self.lepton_and_hadTau_genMatches_fakes.append(hadTau_genMatch)
      if run_mcClosure:
        self.lepton_and_hadTau_selections.extend([ "Fakeable_mcClosure_t" ])
    else:
      raise ValueError("Invalid Configuration parameter 'applyFakeRateWeights' = %s !!" % applyFakeRateWeights)

    self.executable_addBackgrounds = executable_addBackgrounds
    self.executable_addFakes = executable_addFakes

    self.nonfake_backgrounds = [ "TT", "TTW", "TTZ", "TTWW", "EWK", "Rares", "tHq", "tHW", "VH" ]

    self.prep_dcard_processesToCopy = [ "data_obs" ] + self.nonfake_backgrounds + [ "conversions", "fakes_data", "fakes_mc" ]
    self.make_plots_backgrounds = [ "TTW", "TTZ", "TTWW", "EWK", "Rares", "tHq", "tHW" ] + [ "conversions", "fakes_data" ]

    self.cfgFile_analyze = os.path.join(self.template_dir, cfgFile_analyze)
    self.inputFiles_hadd_stage1_6 = []
    self.outputFile_hadd_stage1_6 = None
    self.histogramDir_prep_dcard = "2los_1tau_Tight"
    self.cfgFile_make_plots = os.path.join(self.template_dir, "makePlots_2los_1tau_cfg.py")
    self.cfgFile_make_plots_mcClosure = os.path.join(self.template_dir, "makePlots_mcClosure_2los_1tau_cfg.py") #TODO

    self.select_rle_output = select_rle_output
    self.hlt_filter = hlt_filter

  def set_BDT_training(self, hadTau_selection_relaxed):
    """Run analysis with loose selection criteria for leptons and hadronic taus,
       for the purpose of preparing event list files for BDT training.
    """
    self.lepton_and_hadTau_selections = [ "forBDTtraining" ]
    self.lepton_and_hadTau_frWeights  = [ "disabled" ]
    super(analyzeConfig_2los_1tau, self).set_BDT_training(hadTau_selection_relaxed)

  def createCfg_analyze(self, jobOptions, sample_info, lepton_and_hadTau_selection):
    """Create python configuration file for the analyze_2los_1tau executable (analysis code)

       Args:
         inputFiles: list of input files (Ntuples)
         outputFile: output file of the job -- a ROOT file containing histogram
         process: either `TTW`, `TTZ`, `Rares`, `data_obs`, `ttH_hww`, 'ttH_hzg', 'ttH_hmm', `ttH_hzz` or `ttH_htt`
         is_mc: flag indicating whether job runs on MC (True) or data (False)
         lumi_scale: event weight (= xsection * luminosity / number of events)
         central_or_shift: either 'central' or one of the systematic uncertainties defined in $CMSSW_BASE/src/tthAnalysis/HiggsToTauTau/bin/analyze_2los_1tau.cc
    """
    lepton_and_hadTau_frWeight = "disabled" if jobOptions['applyFakeRateWeights'] == "disabled" else "enabled"
    histogramDir = getHistogramDir(
      lepton_and_hadTau_selection, jobOptions['hadTauSelection'], lepton_and_hadTau_frWeight
    )
    jobOptions['histogramDir'] = histogramDir
    if 'mcClosure' in lepton_and_hadTau_selection:
      self.mcClosure_dir[lepton_and_hadTau_selection] = histogramDir

    self.set_leptonFakeRateWeightHistogramNames(jobOptions['central_or_shift'], lepton_and_hadTau_selection)
    jobOptions['leptonFakeRateWeight.inputFileName'] = self.leptonFakeRateWeight_inputFile
    jobOptions['leptonFakeRateWeight.histogramName_e'] = self.leptonFakeRateWeight_histogramName_e
    jobOptions['leptonFakeRateWeight.histogramName_mu'] = self.leptonFakeRateWeight_histogramName_mu

    jobOptions['hadTauFakeRateWeight.inputFileName'] = self.hadTauFakeRateWeight_inputFile
    jobOptions['hadTauFakeRateWeight.lead.graphName'] = 'jetToTauFakeRate/%s/$etaBin/jetToTauFakeRate_mc_hadTaus_pt' % self.hadTau_selection_part2
    jobOptions['hadTauFakeRateWeight.lead.fitFunctionName'] = 'jetToTauFakeRate/%s/$etaBin/fitFunction_data_div_mc_hadTaus_pt' % self.hadTau_selection_part2
    if "mcClosure" in lepton_and_hadTau_selection:
      jobOptions['hadTauFakeRateWeight.applyGraph_lead'] = True
      jobOptions['hadTauFakeRateWeight.applyGraph_sublead'] = True
      jobOptions['hadTauFakeRateWeight.applyFitFunction_lead'] = False
      jobOptions['hadTauFakeRateWeight.applyFitFunction_sublead'] = False
      if self.applyFakeRateWeights not in [ "3L", "1tau" ] and not self.isBDTtraining:
        # We want to preserve the same logic as running in SR and applying the FF method only to leptons [*]
        jobOptions['hadTauFakeRateWeight.applyFitFunction_lead'] = True
        jobOptions['hadTauFakeRateWeight.applyFitFunction_sublead'] = True
    if jobOptions['hadTauSelection'].find("Tight") != -1 and self.applyFakeRateWeights not in [ "3L", "1tau" ] and not self.isBDTtraining:
      # [*] SR and applying the FF method only to leptons
      jobOptions['hadTauFakeRateWeight.applyGraph_lead'] = False # FR in MC for the leading tau
      jobOptions['hadTauFakeRateWeight.applyGraph_sublead'] = False # data-to-MC SF for the leading tau
      jobOptions['hadTauFakeRateWeight.applyFitFunction_lead'] = True
      jobOptions['hadTauFakeRateWeight.applyFitFunction_sublead'] = True
      jobOptions['apply_hadTauFakeRateSF'] = True

    lines = super(analyzeConfig_2los_1tau, self).createCfg_analyze(jobOptions, sample_info)
    create_cfg(self.cfgFile_analyze, jobOptions['cfgFile_modified'], lines)

  def createCfg_makePlots_mcClosure(self, jobOptions): #TODO
    """Fills the template of python configuration file for making control plots

       Args:
         histogramFile: name of the input ROOT file
    """
    lines = []
    lines.append("process.fwliteInput.fileNames = cms.vstring('%s')" % jobOptions['inputFile'])
    lines.append("process.makePlots.outputFileName = cms.string('%s')" % jobOptions['outputFile'])
    lines.append("process.makePlots.processesBackground = cms.vstring(%s)" % self.make_plots_backgrounds)
    lines.append("process.makePlots.processSignal = cms.string('%s')" % self.make_plots_signal)
    lines.append("process.makePlots.categories = cms.VPSet(")
    lines.append("  cms.PSet(")
    lines.append("    signal = cms.string('%s')," % jobOptions['histogramDir_signal'])
    lines.append("    sideband = cms.string('%s')," % jobOptions['histogramDir_sideband'])
    lines.append("    label = cms.string('%s')" % self.channel)
    lines.append("  )")
    lines.append(")")
    lines.append("process.makePlots.intLumiData = cms.double(%.1f)" % self.lumi)
    create_cfg(self.cfgFile_make_plots_mcClosure, jobOptions['cfgFile_modified'], lines)

  def addToMakefile_backgrounds_from_data(self, lines_makefile):
    self.addToMakefile_addBackgrounds(lines_makefile, "sbatch_addBackgrounds", self.sbatchFile_addBackgrounds, self.jobOptions_addBackgrounds)
    self.addToMakefile_addBackgrounds(lines_makefile, "sbatch_addBackgrounds_sum", self.sbatchFile_addBackgrounds_sum, self.jobOptions_addBackgrounds_sum)
    self.addToMakefile_hadd_stage1_5(lines_makefile)
    self.addToMakefile_addFakes(lines_makefile)

  def create(self):
    """Creates all necessary config files and runs the complete analysis workfow -- either locally or on the batch system
    """

    for sample_name, sample_info in self.samples.items():
      if not sample_info["use_it"] or sample_info["sample_category"] in [ "additional_signal_overlap", "background_data_estimate" ]:
        continue
      process_name = sample_info["process_name_specific"]
      for lepton_and_hadTau_selection in self.lepton_and_hadTau_selections:
        for lepton_and_hadTau_frWeight in self.lepton_and_hadTau_frWeights:
          if lepton_and_hadTau_frWeight == "enabled" and not lepton_and_hadTau_selection.startswith("Fakeable"):
            continue
          lepton_and_hadTau_selection_and_frWeight = get_lepton_and_hadTau_selection_and_frWeight(lepton_and_hadTau_selection, lepton_and_hadTau_frWeight)
          key_dir = getKey(process_name, lepton_and_hadTau_selection_and_frWeight)
          for dir_type in [ DKEY_CFGS, DKEY_HIST, DKEY_LOGS, DKEY_RLES ]:
            initDict(self.dirs, [ key_dir, dir_type ])
            if dir_type in [ DKEY_CFGS, DKEY_LOGS ]:
              self.dirs[key_dir][dir_type] = os.path.join(self.configDir, dir_type, self.channel,
                "_".join([ lepton_and_hadTau_selection_and_frWeight ]), process_name)
            else:
              self.dirs[key_dir][dir_type] = os.path.join(self.outputDir, dir_type, self.channel,
                "_".join([ lepton_and_hadTau_selection_and_frWeight ]), process_name)
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
      inputFileLists[sample_name] = generateInputFileList(sample_info, self.max_files_per_job)

    for lepton_and_hadTau_selection in self.lepton_and_hadTau_selections:
      lepton_selection = lepton_and_hadTau_selection
      hadTau_selection = lepton_and_hadTau_selection
      electron_selection = lepton_selection
      muon_selection = lepton_selection

      if self.applyFakeRateWeights == "2lepton":
        hadTau_selection = "Tight"
      hadTau_selection = "|".join([ hadTau_selection, self.hadTau_selection_part2 ])

      if lepton_and_hadTau_selection == "forBDTtraining":
        electron_selection = "Loose"
        muon_selection = "Loose"
        hadTau_selection = "Tight|%s" % self.hadTau_selection_relaxed
      elif lepton_and_hadTau_selection == "Fakeable_mcClosure_e":
        electron_selection = "Fakeable"
        muon_selection = "Tight"
        hadTau_selection = "Tight"
        hadTau_selection = "|".join([ hadTau_selection, self.hadTau_selection_part2 ])
      elif lepton_and_hadTau_selection == "Fakeable_mcClosure_m":
        electron_selection = "Tight"
        muon_selection = "Fakeable"
        hadTau_selection = "Tight"
        hadTau_selection = "|".join([ hadTau_selection, self.hadTau_selection_part2 ])
      elif lepton_and_hadTau_selection == "Fakeable_mcClosure_t":
        electron_selection = "Tight"
        muon_selection = "Tight"
        hadTau_selection = "Fakeable"
        hadTau_selection = "|".join([ hadTau_selection, self.hadTau_selection_part2 ])

      for lepton_and_hadTau_frWeight in self.lepton_and_hadTau_frWeights:
        if lepton_and_hadTau_frWeight == "enabled" and not lepton_and_hadTau_selection.startswith("Fakeable"):
          continue
        if lepton_and_hadTau_frWeight == "disabled" and not lepton_and_hadTau_selection in [ "Tight", "forBDTtraining" ]:
          continue
        lepton_and_hadTau_selection_and_frWeight = get_lepton_and_hadTau_selection_and_frWeight(lepton_and_hadTau_selection, lepton_and_hadTau_frWeight)

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
              if central_or_shift != "central":
                isFR_shape_shift = (central_or_shift in systematics.FR_all)
                if not ((lepton_and_hadTau_selection == "Fakeable" and isFR_shape_shift) or lepton_and_hadTau_selection == "Tight"):
                  continue
                if not is_mc and not isFR_shape_shift:
                  continue

              if central_or_shift in systematics.LHE().ttH and sample_category != "signal":
                continue
              if central_or_shift in systematics.LHE().ttW and sample_category != "TTW":
                continue
              if central_or_shift in systematics.LHE().ttZ and sample_category != "TTZ":
                continue

              logging.info(" ... for '%s' and systematic uncertainty option '%s'" % (lepton_and_hadTau_selection_and_frWeight, central_or_shift))

              # build config files for executing analysis code
              key_dir = getKey(process_name, lepton_and_hadTau_selection_and_frWeight)
              key_analyze_job = getKey(process_name, lepton_and_hadTau_selection_and_frWeight, central_or_shift, jobId)
              ntupleFiles = inputFileList[jobId]
              if len(ntupleFiles) == 0:
                logging.warning("No input ntuples for %s --> skipping job !!" % (key_analyze_job))
                continue

              cfg_key = getKey(self.channel, process_name, lepton_and_hadTau_selection_and_frWeight, central_or_shift, jobId)
              cfgFile_modified_path = os.path.join(self.dirs[key_dir][DKEY_CFGS], "analyze_%s_cfg.py" % cfg_key)
              histogramFile_path = os.path.join(self.dirs[key_dir][DKEY_HIST], "%s.root" % key_analyze_job)
              logFile_path = os.path.join(self.dirs[key_dir][DKEY_LOGS], "analyze_%s.log" % cfg_key)
              rleOutputFile_path = os.path.join(self.dirs[key_dir][DKEY_RLES], "rle_%s.txt" % cfg_key) \
                                   if self.select_rle_output else ""
              applyFakeRateWeights = self.applyFakeRateWeights \
                if self.isBDTtraining or not (lepton_selection == "Tight" and hadTau_selection.find("Tight") != -1) \
                else "disabled"

              self.jobOptions_analyze[key_analyze_job] = {
                'ntupleFiles'              : ntupleFiles,
                'cfgFile_modified'         : cfgFile_modified_path,
                'histogramFile'            : histogramFile_path,
                'logFile'                  : logFile_path,
                'selEventsFileName_output' : rleOutputFile_path,
                'electronSelection'        : electron_selection,
                'muonSelection'            : muon_selection,
                'lep_mva_cut'              : self.lep_mva_cut,
                'apply_leptonGenMatching'  : self.apply_leptonGenMatching,
                'hadTauSelection'          :  hadTau_selection,
                'apply_hadTauGenMatching'  : self.apply_hadTauGenMatching,
                'applyFakeRateWeights'     : applyFakeRateWeights,
                'central_or_shift'         : central_or_shift,
                'selectBDT'                : self.isBDTtraining,
                'apply_hlt_filter'         : self.hlt_filter,
                'fillGenEvtHistograms'     : True,
              }
              self.createCfg_analyze(self.jobOptions_analyze[key_analyze_job], sample_info, lepton_and_hadTau_selection)

              # initialize input and output file names for hadd_stage1
              key_hadd_stage1 = getKey(process_name, lepton_and_hadTau_selection_and_frWeight)
              if not key_hadd_stage1 in self.inputFiles_hadd_stage1:
                self.inputFiles_hadd_stage1[key_hadd_stage1] = []
              self.inputFiles_hadd_stage1[key_hadd_stage1].append(self.jobOptions_analyze[key_analyze_job]['histogramFile'])
              self.outputFile_hadd_stage1[key_hadd_stage1] = os.path.join(self.dirs[DKEY_HIST], "histograms_harvested_stage1_%s_%s_%s.root" % \
                (self.channel, process_name, lepton_and_hadTau_selection_and_frWeight))

          if self.isBDTtraining:
            continue

          if is_mc:
            logging.info("Creating configuration files to run 'addBackgrounds' for sample %s" % process_name)

            sample_categories = [ sample_category ]
            if is_signal:
              sample_categories = [ "signal", "ttH", "ttH_htt", "ttH_hww", "ttH_hzz", "ttH_hmm", "ttH_hzg" ]
            for sample_category in sample_categories:
              # sum non-fake and fake contributions for each MC sample separately
              genMatch_categories = [ "nonfake", "conversions", "fake" ]

              # in case fake background method is applied to leptons only,
              # split events with genuine leptons (taken from MC) into "gentau" and "faketau" parts,
              # so that different systematic uncertainties can be applied to both parts
              if self.applyFakeRateWeights == "2lepton":
                genMatch_categories.extend([ "gentau", "faketau" ])

              for genMatch_category in genMatch_categories:
                key_hadd_stage1 = getKey(process_name, lepton_and_hadTau_selection_and_frWeight)
                key_addBackgrounds_job = None
                processes_input = None
                process_output = None
                cfgFile_modified = None
                outputFile = None
                if genMatch_category == "nonfake":
                  # sum non-fake contributions for each MC sample separately
                  # input processes: TT2l0g0j; ...
                  # output processes: TT; ...
                  if sample_category in [ "signal" ]:
                    lepton_and_hadTau_genMatches = []
                    lepton_and_hadTau_genMatches.extend(self.lepton_and_hadTau_genMatches_nonfakes)
                    lepton_and_hadTau_genMatches.extend(self.lepton_and_hadTau_genMatches_conversions)
                    lepton_and_hadTau_genMatches.extend(self.lepton_and_hadTau_genMatches_fakes)
                    processes_input = [ "%s%s" % (sample_category, genMatch) for genMatch in lepton_and_hadTau_genMatches ]
                  elif sample_category in [ "ttH" ]:
                    lepton_and_hadTau_genMatches = []
                    lepton_and_hadTau_genMatches.extend(self.lepton_and_hadTau_genMatches_nonfakes)
                    lepton_and_hadTau_genMatches.extend(self.lepton_and_hadTau_genMatches_conversions)
                    processes_input = []
                    processes_input.extend([ "%s%s" % ("ttH_htt", genMatch) for genMatch in lepton_and_hadTau_genMatches ])
                    processes_input.extend([ "%s%s" % ("ttH_hww", genMatch) for genMatch in lepton_and_hadTau_genMatches ])
                    processes_input.extend([ "%s%s" % ("ttH_hzz", genMatch) for genMatch in lepton_and_hadTau_genMatches ])
                    processes_input.extend([ "%s%s" % ("ttH_hzg", genMatch) for genMatch in lepton_and_hadTau_genMatches ])
                    processes_input.extend([ "%s%s" % ("ttH_hmm", genMatch) for genMatch in lepton_and_hadTau_genMatches ])
                  else:
                    processes_input = [ "%s%s" % (sample_category, genMatch) for genMatch in self.lepton_and_hadTau_genMatches_nonfakes ]
                  process_output = sample_category
                  key_addBackgrounds_job = getKey(process_name, sample_category, lepton_and_hadTau_selection_and_frWeight)
                  cfgFile_modified = os.path.join(self.dirs[DKEY_CFGS], "addBackgrounds_%s_%s_%s_%s_cfg.py" % \
                    (self.channel, process_name, sample_category, lepton_and_hadTau_selection_and_frWeight))
                  outputFile = os.path.join(self.dirs[DKEY_HIST], "addBackgrounds_%s_%s_%s_%s.root" % \
                    (self.channel, process_name, sample_category, lepton_and_hadTau_selection_and_frWeight))
                elif genMatch_category == "conversions":
                  # sum conversion contributions for each MC sample separately
                  # input processes: TT1l1g0j, TT0l2g0j; ...
                  # output processes: TT_fake; ...
                  if sample_category in [ "signal" ]:
                    processes_input = [ "%s%s" % (sample_category, genMatch) for genMatch in self.lepton_and_hadTau_genMatches_conversions ]
                  elif sample_category in [ "ttH" ]:
                    processes_input = []
                    processes_input.extend([ "%s%s" % ("ttH_htt", genMatch) for genMatch in self.lepton_and_hadTau_genMatches_conversions ])
                    processes_input.extend([ "%s%s" % ("ttH_hww", genMatch) for genMatch in self.lepton_and_hadTau_genMatches_conversions ])
                    processes_input.extend([ "%s%s" % ("ttH_hzz", genMatch) for genMatch in self.lepton_and_hadTau_genMatches_conversions ])
                    processes_input.extend([ "%s%s" % ("ttH_hzg", genMatch) for genMatch in self.lepton_and_hadTau_genMatches_conversions ])
                    processes_input.extend([ "%s%s" % ("ttH_hmm", genMatch) for genMatch in self.lepton_and_hadTau_genMatches_conversions ])
                  else:
                    processes_input = [ "%s%s" % (sample_category, genMatch) for genMatch in self.lepton_and_hadTau_genMatches_conversions ]
                  process_output = "%s_conversion" % sample_category
                  key_addBackgrounds_job = getKey(process_name, "%s_conversion" % sample_category, lepton_and_hadTau_selection_and_frWeight)
                  cfgFile_modified = os.path.join(self.dirs[DKEY_CFGS], "addBackgrounds_%s_conversions_%s_%s_%s_cfg.py" % \
                    (self.channel, process_name, sample_category, lepton_and_hadTau_selection_and_frWeight))
                  outputFile = os.path.join(self.dirs[DKEY_HIST], "addBackgrounds_%s_conversions_%s_%s_%s.root" % \
                    (self.channel, process_name, sample_category, lepton_and_hadTau_selection_and_frWeight))
                elif genMatch_category == "fake":
                  # sum fake background contributions for each MC sample separately
                  # input processes: TT1l0g1j, TT0l1g1j, TT0l0g2j; ...
                  # output processes: TT_fake; ...
                  if sample_category in [ "signal" ]:
                    processes_input = [ "%s%s" % (sample_category, genMatch) for genMatch in self.lepton_and_hadTau_genMatches_fakes ]
                  elif sample_category in [ "ttH" ]:
                    processes_input = []
                    processes_input.extend([ "%s%s" % ("ttH_htt", genMatch) for genMatch in self.lepton_and_hadTau_genMatches_fakes ])
                    processes_input.extend([ "%s%s" % ("ttH_hww", genMatch) for genMatch in self.lepton_and_hadTau_genMatches_fakes ])
                    processes_input.extend([ "%s%s" % ("ttH_hzz", genMatch) for genMatch in self.lepton_and_hadTau_genMatches_fakes ])
                    processes_input.extend([ "%s%s" % ("ttH_hzg", genMatch) for genMatch in self.lepton_and_hadTau_genMatches_fakes ])
                    processes_input.extend([ "%s%s" % ("ttH_hmm", genMatch) for genMatch in self.lepton_and_hadTau_genMatches_fakes ])
                  else:
                    processes_input = [ "%s%s" % (sample_category, genMatch) for genMatch in self.lepton_and_hadTau_genMatches_fakes ]
                  process_output = "%s_fake" % sample_category
                  key_addBackgrounds_job = getKey(process_name, "%s_fake" % sample_category, lepton_and_hadTau_selection_and_frWeight)
                  cfgFile_modified = os.path.join(self.dirs[DKEY_CFGS], "addBackgrounds_%s_fakes_%s_%s_%s_cfg.py" % \
                    (self.channel, process_name, sample_category, lepton_and_hadTau_selection_and_frWeight))
                  outputFile = os.path.join(self.dirs[DKEY_HIST], "addBackgrounds_%s_fakes_%s_%s_%s.root" % \
                    (self.channel, process_name, sample_category, lepton_and_hadTau_selection_and_frWeight))
                elif genMatch_category == "gentau":
                  # sum contributions with genuine leptons and genuine taus
                  # input processes: TT2l0g0j1t0e0m0j, TT2l0j0t1e0m0j, TT2l0j0t0e1m0j; ...
                  # output processes: TT_gentau; ...
                  if sample_category in [ "signal" ]:
                    processes_input = [ "%s%s" % (sample_category, genMatch) for genMatch in self.lepton_and_hadTau_genMatches_gentau ]
                  elif sample_category in [ "ttH" ]:
                    processes_input = []
                    processes_input.extend([ "%s%s" % ("ttH_htt", genMatch) for genMatch in self.lepton_and_hadTau_genMatches_gentau ])
                    processes_input.extend([ "%s%s" % ("ttH_hww", genMatch) for genMatch in self.lepton_and_hadTau_genMatches_gentau ])
                    processes_input.extend([ "%s%s" % ("ttH_hzz", genMatch) for genMatch in self.lepton_and_hadTau_genMatches_gentau ])
                    processes_input.extend([ "%s%s" % ("ttH_hzg", genMatch) for genMatch in self.lepton_and_hadTau_genMatches_gentau ])
                    processes_input.extend([ "%s%s" % ("ttH_hmm", genMatch) for genMatch in self.lepton_and_hadTau_genMatches_gentau ])
                  else:
                    processes_input = [ "%s%s" % (sample_category, genMatch) for genMatch in self.lepton_and_hadTau_genMatches_gentau ]
                  process_output = "%s_gentau" % sample_category
                  key_addBackgrounds_job = getKey(process_name, "%s_gentau" % sample_category, lepton_and_hadTau_selection_and_frWeight)
                  cfgFile_modified = os.path.join(self.dirs[DKEY_CFGS], "addBackgrounds_%s_gentau_%s_%s_%s_cfg.py" % \
                    (self.channel, process_name, sample_category, lepton_and_hadTau_selection_and_frWeight))
                  outputFile = os.path.join(self.dirs[DKEY_HIST], "addBackgrounds_%s_gentau_%s_%s_%s.root" % \
                    (self.channel, process_name, sample_category, lepton_and_hadTau_selection_and_frWeight))
                elif genMatch_category == "faketau":
                  # sum contributions with genuine leptons and fake taus
                  # input processes: TT2l0g0j0t0e0m1j; ...
                  # output processes: TT_faketau; ...
                  if sample_category in [ "signal" ]:
                    processes_input = [ "%s%s" % (sample_category, genMatch) for genMatch in self.lepton_and_hadTau_genMatches_faketau ]
                  elif sample_category in [ "ttH" ]:
                    processes_input = []
                    processes_input.extend([ "%s%s" % ("ttH_htt", genMatch) for genMatch in self.lepton_and_hadTau_genMatches_faketau ])
                    processes_input.extend([ "%s%s" % ("ttH_hww", genMatch) for genMatch in self.lepton_and_hadTau_genMatches_faketau ])
                    processes_input.extend([ "%s%s" % ("ttH_hzz", genMatch) for genMatch in self.lepton_and_hadTau_genMatches_faketau ])
                    processes_input.extend([ "%s%s" % ("ttH_hzg", genMatch) for genMatch in self.lepton_and_hadTau_genMatches_faketau ])
                    processes_input.extend([ "%s%s" % ("ttH_hmm", genMatch) for genMatch in self.lepton_and_hadTau_genMatches_faketau ])
                  else:
                    processes_input = [ "%s%s" % (sample_category, genMatch) for genMatch in self.lepton_and_hadTau_genMatches_faketau ]
                  process_output = "%s_faketau" % sample_category
                  key_addBackgrounds_job = getKey(process_name, "%s_faketau" % sample_category, lepton_and_hadTau_selection_and_frWeight)
                  cfgFile_modified = os.path.join(self.dirs[DKEY_CFGS], "addBackgrounds_%s_faketau_%s_%s_%s_cfg.py" % \
                    (self.channel, process_name, sample_category, lepton_and_hadTau_selection_and_frWeight))
                  outputFile = os.path.join(self.dirs[DKEY_HIST], "addBackgrounds_%s_faketau_%s_%s_%s.root" % \
                    (self.channel, process_name, sample_category, lepton_and_hadTau_selection_and_frWeight))
                if processes_input:
                  logging.info(" ...for genMatch option = '%s'" % genMatch_category)
                  self.jobOptions_addBackgrounds[key_addBackgrounds_job] = {
                    'inputFile' : self.outputFile_hadd_stage1[key_hadd_stage1],
                    'cfgFile_modified' : cfgFile_modified,
                    'outputFile' : outputFile,
                    'logFile' : os.path.join(self.dirs[DKEY_LOGS], os.path.basename(cfgFile_modified).replace("_cfg.py", ".log")),
                    'categories' : [ getHistogramDir(lepton_selection, hadTau_selection, lepton_and_hadTau_frWeight) ],
                    'processes_input' : processes_input,
                    'process_output' : process_output
                  }
                  self.createCfg_addBackgrounds(self.jobOptions_addBackgrounds[key_addBackgrounds_job])

                  # initialize input and output file names for hadd_stage1_5
                  key_hadd_stage1_5 = getKey(lepton_and_hadTau_selection_and_frWeight)
                  if not key_hadd_stage1_5 in self.inputFiles_hadd_stage1_5:
                    self.inputFiles_hadd_stage1_5[key_hadd_stage1_5] = []
                  self.inputFiles_hadd_stage1_5[key_hadd_stage1_5].append(self.jobOptions_addBackgrounds[key_addBackgrounds_job]['outputFile'])
                  self.outputFile_hadd_stage1_5[key_hadd_stage1_5] = os.path.join(self.dirs[DKEY_HIST], "histograms_harvested_stage1_5_%s_%s.root" % \
                    (self.channel, lepton_and_hadTau_selection_and_frWeight))

          if self.isBDTtraining:
            continue

          # add output files of hadd_stage1 for data to list of input files for hadd_stage1_5
          if not is_mc:
            key_hadd_stage1 = getKey(process_name, lepton_and_hadTau_selection_and_frWeight)
            key_hadd_stage1_5 = getKey(lepton_and_hadTau_selection_and_frWeight)
            if not key_hadd_stage1_5 in self.inputFiles_hadd_stage1_5:
              self.inputFiles_hadd_stage1_5[key_hadd_stage1_5] = []
            self.inputFiles_hadd_stage1_5[key_hadd_stage1_5].append(self.outputFile_hadd_stage1[key_hadd_stage1])

        if self.isBDTtraining:
          continue

        # sum fake background contributions for the total of all MC samples
        # input processes: TT1l0g1j, TT0l1g1j, TT0l0g2j; ...
        # output process: fakes_mc
        key_addBackgrounds_job_fakes = getKey(lepton_and_hadTau_selection_and_frWeight, "fakes")
        key_hadd_stage1_5 = getKey(lepton_and_hadTau_selection_and_frWeight)
        sample_categories = []
        sample_categories.extend(self.nonfake_backgrounds)
        sample_categories.extend([ "signal" ])
        processes_input = []
        for sample_category in sample_categories:
          processes_input.append("%s_fake" % sample_category)
        self.jobOptions_addBackgrounds_sum[key_addBackgrounds_job_fakes] = {
          'inputFile' : self.outputFile_hadd_stage1_5[key_hadd_stage1_5],
          'cfgFile_modified' : os.path.join(self.dirs[DKEY_CFGS], "addBackgrounds_%s_fakes_mc_%s_cfg.py" % \
            (self.channel, lepton_and_hadTau_selection_and_frWeight)),
          'outputFile' : os.path.join(self.dirs[DKEY_HIST], "addBackgrounds_%s_fakes_mc_%s.root" % \
            (self.channel, lepton_and_hadTau_selection_and_frWeight)),
          'logFile' : os.path.join(self.dirs[DKEY_LOGS], "addBackgrounds_%s_fakes_mc_%s.log" % \
            (self.channel, lepton_and_hadTau_selection_and_frWeight)),
          'categories' : [ getHistogramDir(lepton_selection, hadTau_selection, lepton_and_hadTau_frWeight) ],
          'processes_input' : processes_input,
          'process_output' : "fakes_mc"
        }
        self.createCfg_addBackgrounds(self.jobOptions_addBackgrounds_sum[key_addBackgrounds_job_fakes])

        # sum conversion background contributions for the total of all MC sample
        # input processes: TT1l1g0j, TT0l2g0j; ...
        # output process: conversions
        key_addBackgrounds_job_conversions = getKey(lepton_and_hadTau_selection_and_frWeight, "conversions")
        sample_categories = []
        sample_categories.extend(self.nonfake_backgrounds)
        sample_categories.extend([ "signal" ])
        processes_input = []
        for sample_category in sample_categories:
          processes_input.append("%s_conversion" % sample_category)
        self.jobOptions_addBackgrounds_sum[key_addBackgrounds_job_conversions] = {
          'inputFile' : self.outputFile_hadd_stage1_5[key_hadd_stage1_5],
          'cfgFile_modified' : os.path.join(self.dirs[DKEY_CFGS], "addBackgrounds_%s_conversions_%s_cfg.py" % \
            (self.channel, lepton_and_hadTau_selection_and_frWeight)),
          'outputFile' : os.path.join(self.dirs[DKEY_HIST], "addBackgrounds_%s_conversions_%s.root" % \
            (self.channel, lepton_and_hadTau_selection_and_frWeight)),
          'logFile' : os.path.join(self.dirs[DKEY_LOGS], "addBackgrounds_%s_conversions_%s.log" % \
            (self.channel, lepton_and_hadTau_selection_and_frWeight)),
          'categories' : [ getHistogramDir(lepton_selection, hadTau_selection, lepton_and_hadTau_frWeight) ],
          'processes_input' : processes_input,
          'process_output' : "conversions"
        }
        self.createCfg_addBackgrounds(self.jobOptions_addBackgrounds_sum[key_addBackgrounds_job_conversions])

        # initialize input and output file names for hadd_stage2
        key_hadd_stage2 = getKey(lepton_and_hadTau_selection_and_frWeight)
        if not key_hadd_stage2 in self.inputFiles_hadd_stage2:
          self.inputFiles_hadd_stage2[key_hadd_stage2] = []
        if lepton_and_hadTau_selection == "Tight":
          self.inputFiles_hadd_stage2[key_hadd_stage2].append(self.jobOptions_addBackgrounds_sum[key_addBackgrounds_job_fakes]['outputFile'])
          self.inputFiles_hadd_stage2[key_hadd_stage2].append(self.jobOptions_addBackgrounds_sum[key_addBackgrounds_job_conversions]['outputFile'])
        key_hadd_stage1_5 = getKey(lepton_and_hadTau_selection_and_frWeight)
        self.inputFiles_hadd_stage2[key_hadd_stage2].append(self.outputFile_hadd_stage1_5[key_hadd_stage1_5])
        self.outputFile_hadd_stage2[key_hadd_stage2] = os.path.join(self.dirs[DKEY_HIST], "histograms_harvested_stage2_%s_%s.root" % \
          (self.channel, lepton_and_hadTau_selection_and_frWeight))

    if self.isBDTtraining:
      if self.is_sbatch:
        logging.info("Creating script for submitting '%s' jobs to batch system" % self.executable_analyze)
        self.sbatchFile_analyze = os.path.join(self.dirs[DKEY_SCRIPTS], "sbatch_analyze_%s.py" % self.channel)
        self.createScript_sbatch_analyze(self.executable_analyze, self.sbatchFile_analyze, self.jobOptions_analyze)
      logging.info("Creating Makefile")
      lines_makefile = []
      self.addToMakefile_analyze(lines_makefile)
      self.addToMakefile_hadd_stage1(lines_makefile)
      self.createMakefile(lines_makefile)
      logging.info("Done")
      return self.num_jobs

    logging.info("Creating configuration files to run 'addBackgroundFakes'")
    key_addFakes_job = getKey("fakes_data")
    key_hadd_stage1_5 = getKey(get_lepton_and_hadTau_selection_and_frWeight("Fakeable", "enabled"))
    category_sideband = None
    if self.applyFakeRateWeights == "2lepton":
      category_sideband = "2los_1tau_Fakeable_wFakeRateWeights"
    elif self.applyFakeRateWeights == "3L":
      category_sideband = "2los_1tau_Fakeable_wFakeRateWeights"
    elif self.applyFakeRateWeights == "1tau":
      category_sideband = "2los_1tau_Fakeable_wFakeRateWeights"
    else:
      raise ValueError("Invalid Configuration parameter 'applyFakeRateWeights' = %s !!" % self.applyFakeRateWeights)
    self.jobOptions_addFakes[key_addFakes_job] = {
      'inputFile' : self.outputFile_hadd_stage1_5[key_hadd_stage1_5],
      'cfgFile_modified' : os.path.join(self.dirs[DKEY_CFGS], "addBackgroundLeptonFakes_%s_cfg.py" % self.channel),
      'outputFile' : os.path.join(self.dirs[DKEY_HIST], "addBackgroundLeptonFakes_%s.root" % self.channel),
      'logFile' : os.path.join(self.dirs[DKEY_LOGS], "addBackgroundLeptonFakes_%s.log" % self.channel),
      'category_signal' : "2los_1tau_Tight",
      'category_sideband' : category_sideband
    }
    self.createCfg_addFakes(self.jobOptions_addFakes[key_addFakes_job])
    key_hadd_stage2 = getKey(get_lepton_and_hadTau_selection_and_frWeight("Tight", "disabled"))
    self.inputFiles_hadd_stage2[key_hadd_stage2].append(self.jobOptions_addFakes[key_addFakes_job]['outputFile'])

    logging.info("Creating configuration files to run 'prepareDatacards'")
    if self.applyFakeRateWeights == "2lepton":
      processesToCopy = []
      for process in self.prep_dcard_processesToCopy:
        processesToCopy.append(process)
        if not (process.find("data") != -1 or process.find("fakes") != -1 or process.find("conversions") != -1):
          processesToCopy.append("%s_gentau" % process)
          processesToCopy.append("%s_faketau" % process)
      self.prep_dcard_processesToCopy = processesToCopy
      processesToCopy = []
      for process in self.prep_dcard_signals:
        processesToCopy.append(process)
        processesToCopy.append("%s_gentau" % process)
        processesToCopy.append("%s_faketau" % process)
      self.prep_dcard_signals = processesToCopy
    for histogramToFit in self.histograms_to_fit:
      key_prep_dcard_job = getKey(histogramToFit)
      key_hadd_stage2 = getKey(get_lepton_and_hadTau_selection_and_frWeight("Tight", "disabled"))
      self.jobOptions_prep_dcard[key_prep_dcard_job] = {
        'inputFile' : self.outputFile_hadd_stage2[key_hadd_stage2],
        'cfgFile_modified' : os.path.join(self.dirs[DKEY_CFGS], "prepareDatacards_%s_%s_cfg.py" % (self.channel, histogramToFit)),
        'datacardFile' : os.path.join(self.dirs[DKEY_DCRD], "prepareDatacards_%s_%s.root" % (self.channel, histogramToFit)),
        'histogramDir' : self.histogramDir_prep_dcard,
        'histogramToFit' : histogramToFit,
        'label' : None
      }
      self.createCfg_prep_dcard(self.jobOptions_prep_dcard[key_prep_dcard_job])

      # add shape templates for the following systematic uncertainties:
      #  - 'CMS_ttHl_Clos_norm_e'
      #  - 'CMS_ttHl_Clos_shape_e'
      #  - 'CMS_ttHl_Clos_norm_m'
      #  - 'CMS_ttHl_Clos_shape_m'
      #  - 'CMS_ttHl_Clos_norm_t'
      #  - 'CMS_ttHl_Clos_shape_t'
      key_prep_dcard_job = getKey(histogramToFit)
      key_add_syst_fakerate_job = getKey(histogramToFit)
      key_hadd_stage2 = getKey(get_lepton_and_hadTau_selection_and_frWeight("Tight", "disabled"))
      self.jobOptions_add_syst_fakerate[key_add_syst_fakerate_job] = {
        'inputFile' : self.jobOptions_prep_dcard[key_prep_dcard_job]['datacardFile'],
        'cfgFile_modified' : os.path.join(self.dirs[DKEY_CFGS], "addSystFakeRates_%s_%s_cfg.py" % (self.channel, histogramToFit)),
        'outputFile' : os.path.join(self.dirs[DKEY_DCRD], "addSystFakeRates_%s_%s.root" % (self.channel, histogramToFit)),
        'category' : self.channel,
        'histogramToFit' : histogramToFit,
        'plots_outputFileName' : os.path.join(self.dirs[DKEY_PLOT], "addSystFakeRates.png")
      }
      histogramDir_nominal = self.histogramDir_prep_dcard
      for lepton_and_hadTau_type in [ 'e', 'm', 't' ]:
        lepton_and_hadTau_mcClosure = "Fakeable_mcClosure_%s" % lepton_and_hadTau_type
        if lepton_and_hadTau_mcClosure not in self.lepton_and_hadTau_selections:
          continue
        lepton_and_hadTau_selection_and_frWeight = get_lepton_and_hadTau_selection_and_frWeight(lepton_and_hadTau_mcClosure, "enabled")
        key_addBackgrounds_job_fakes = getKey(lepton_and_hadTau_selection_and_frWeight, "fakes")
        histogramDir_mcClosure = self.mcClosure_dir[lepton_and_hadTau_mcClosure]
        self.jobOptions_add_syst_fakerate[key_add_syst_fakerate_job].update({
          'add_Clos_%s' % lepton_and_hadTau_type : ("Fakeable_mcClosure_%s" % lepton_and_hadTau_type) in self.lepton_and_hadTau_selections,
          'inputFile_nominal_%s' % lepton_and_hadTau_type : self.outputFile_hadd_stage2[key_hadd_stage2],
          'histogramName_nominal_%s' % lepton_and_hadTau_type : "%s/sel/evt/fakes_mc/%s" % (histogramDir_nominal, histogramToFit),
          'inputFile_mcClosure_%s' % lepton_and_hadTau_type : self.jobOptions_addBackgrounds_sum[key_addBackgrounds_job_fakes]['outputFile'],
          'histogramName_mcClosure_%s' % lepton_and_hadTau_type : "%s/sel/evt/fakes_mc/%s" % (histogramDir_mcClosure, histogramToFit)
        })
      self.createCfg_add_syst_fakerate(self.jobOptions_add_syst_fakerate[key_add_syst_fakerate_job])

      logging.info("Creating configuration files to run 'makePlots'")
      key_makePlots_job = getKey("OS")
      key_hadd_stage2 = getKey(get_lepton_and_hadTau_selection_and_frWeight("Tight", "disabled"))
      self.jobOptions_make_plots[key_makePlots_job] = {
        'executable' : self.executable_make_plots,
        'inputFile' : self.outputFile_hadd_stage2[key_hadd_stage2],
        'cfgFile_modified' : os.path.join(self.dirs[DKEY_CFGS], "makePlots_%s_cfg.py" % self.channel),
        'outputFile' : os.path.join(self.dirs[DKEY_PLOT], "makePlots_%s.png" % self.channel),
        'histogramDir' : self.histogramDir_prep_dcard,
        'label' : "2lOS+2#tau_{h}",
        'make_plots_backgrounds' : self.make_plots_backgrounds
      }
      self.createCfg_makePlots(self.jobOptions_make_plots[key_makePlots_job])
      if "Fakeable_mcClosure" in self.lepton_and_hadTau_selections: #TODO
        key_makePlots_job = getKey("OS")
        key_hadd_stage2 = getKey(get_lepton_and_hadTau_selection_and_frWeight("Tight", "disabled"))
        self.jobOptions_make_plots[key_makePlots_job] = {
          'executable' : self.executable_make_plots_mcClosure,
          'inputFile' : self.outputFile_hadd_stage2[key_hadd_stage2],
          'cfgFile_modified' : os.path.join(self.dirs[DKEY_CFGS], "makePlots_mcClosure_%s_sum%s_cfg.py" % self.channel),
          'outputFile' : os.path.join(self.dirs[DKEY_PLOT], "makePlots_mcClosure_%s_sum%s.png" % self.channel),
          'histogramDir_signal' : self.histogramDir_prep_dcard,
          'histogramDir_sideband' : self.histogramDir_prep_dcard.replace("Tight", "Fakeable_mcClosure_wFakeRateWeights")
        }
        self.createCfg_makePlots_mcClosure(self.jobOptions_make_plots[key_makePlots_job])

    if self.is_sbatch:
      logging.info("Creating script for submitting '%s' jobs to batch system" % self.executable_analyze)
      self.sbatchFile_analyze = os.path.join(self.dirs[DKEY_SCRIPTS], "sbatch_analyze_%s.py" % self.channel)
      self.createScript_sbatch_analyze(self.executable_analyze, self.sbatchFile_analyze, self.jobOptions_analyze)
      logging.info("Creating script for submitting '%s' jobs to batch system" % self.executable_addBackgrounds)
      self.sbatchFile_addBackgrounds = os.path.join(self.dirs[DKEY_SCRIPTS], "sbatch_addBackgrounds_%s.py" % self.channel)
      self.createScript_sbatch(self.executable_addBackgrounds, self.sbatchFile_addBackgrounds, self.jobOptions_addBackgrounds)
      self.sbatchFile_addBackgrounds_sum = os.path.join(self.dirs[DKEY_SCRIPTS], "sbatch_addBackgrounds_sum_%s.py" % self.channel)
      self.createScript_sbatch(self.executable_addBackgrounds, self.sbatchFile_addBackgrounds_sum, self.jobOptions_addBackgrounds_sum)
      logging.info("Creating script for submitting '%s' jobs to batch system" % self.executable_addFakes)
      self.sbatchFile_addFakes = os.path.join(self.dirs[DKEY_SCRIPTS], "sbatch_addFakes_%s.py" % self.channel)
      self.createScript_sbatch(self.executable_addFakes, self.sbatchFile_addFakes, self.jobOptions_addFakes)

    logging.info("Creating Makefile")
    lines_makefile = []
    self.addToMakefile_analyze(lines_makefile)
    self.addToMakefile_hadd_stage1(lines_makefile)
    self.addToMakefile_backgrounds_from_data(lines_makefile)
    self.addToMakefile_hadd_stage2(lines_makefile)
    self.addToMakefile_prep_dcard(lines_makefile)
    self.addToMakefile_add_syst_fakerate(lines_makefile)
    self.addToMakefile_make_plots(lines_makefile)
    self.createMakefile(lines_makefile)

    logging.info("Done")

    return self.num_jobs
