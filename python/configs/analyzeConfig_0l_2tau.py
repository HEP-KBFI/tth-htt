from tthAnalysis.HiggsToTauTau.configs.analyzeConfig import *
from tthAnalysis.HiggsToTauTau.jobTools import create_if_not_exists
from tthAnalysis.HiggsToTauTau.analysisTools import initDict, getKey, create_cfg, createFile, generateInputFileList
from tthAnalysis.HiggsToTauTau.common import logging

import os.path

def get_hadTau_selection_and_frWeight(hadTau_selection, hadTau_frWeight):
  hadTau_selection_and_frWeight = hadTau_selection
  if hadTau_selection.startswith("Fakeable"):
    if hadTau_frWeight == "enabled":
      hadTau_selection_and_frWeight += "_wFakeRateWeights"
    elif hadTau_frWeight == "disabled":
      hadTau_selection_and_frWeight += "_woFakeRateWeights"
  hadTau_selection_and_frWeight = hadTau_selection_and_frWeight.replace("|", "_")
  return hadTau_selection_and_frWeight

def getHistogramDir(category, hadTau_selection, hadTau_frWeight, hadTau_charge_selection):
  histogramDir = category
  histogramDir += "_%s" % hadTau_charge_selection
  hadTau_selection_part1 = hadTau_selection
  for separator in [ "|" ]:
    if hadTau_selection_part1.find(separator) != -1:
      hadTau_selection_part1 = hadTau_selection_part1[:hadTau_selection_part1.find(separator)]
  histogramDir += "_%s" % hadTau_selection_part1
  if hadTau_selection_part1.find("Fakeable") != -1:
    if hadTau_frWeight == "enabled":
      histogramDir += "_wFakeRateWeights"
    elif hadTau_frWeight == "disabled":
      histogramDir += "_woFakeRateWeights"
  return histogramDir

class analyzeConfig_0l_2tau(analyzeConfig):
  """Configuration metadata needed to run analysis in a single go.

  Sets up a folder structure by defining full path names; no directory creation is delegated here.

  Args specific to analyzeConfig_0l_2tau:
    hadTau_selection: either `Tight`, `Loose` or `Fakeable`
    hadTau_charge_selection: either `OS` or `SS` (opposite-sign or same-sign)

  See $CMSSW_BASE/src/tthAnalysis/HiggsToTauTau/python/analyzeConfig.py
  for documentation of further Args.

  """
  def __init__(self,
        configDir,
        outputDir,
        executable_analyze,
        cfgFile_analyze,
        samples,
        hadTau_selection,
        hadTau_charge_selections,
        applyFakeRateWeights,
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
        executable_addBackgrounds,
        executable_addBackgroundJetToTauFakes,
        histograms_to_fit,
        do_sync           = False,
        select_rle_output = False,
        verbose           = False,
        dry_run           = False,
        isDebug           = False,
        rle_select        = '',
        use_nonnominal    = False,
        hlt_filter        = False,
        use_home          = True,
      ):
    analyzeConfig.__init__(self,
      configDir             = configDir,
      outputDir             = outputDir,
      executable_analyze    = executable_analyze,
      channel               = "0l_2tau",
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
      histograms_to_fit     = histograms_to_fit,
      triggers              = [ '2tau', ],
      do_sync               = do_sync,
      verbose               = verbose,
      dry_run               = dry_run,
      isDebug               = isDebug,
      use_home              = use_home,
    )

    self.hadTau_selections = [ "Tight", "Fakeable" ]
    self.hadTau_frWeights = [ "enabled", "disabled" ]
    self.hadTau_selection_part2 = hadTau_selection
    self.hadTau_charge_selections = hadTau_charge_selections
    self.applyFakeRateWeights = applyFakeRateWeights
    run_mcClosure = 'central' not in self.central_or_shifts or len(central_or_shifts) > 1 or self.do_sync

    self.hadTau_genMatches = [ "2t0e0m0j", "1t1e0m0j", "1t0e1m0j", "1t0e0m1j", "0t2e0m0j", "0t1e1m0j", "0t1e0m1j", "0t0e2m0j", "0t0e1m1j", "0t0e0m2j" ]

    self.apply_hadTauGenMatching = None
    self.hadTau_genMatches_nonfakes = []
    self.hadTau_genMatches_fakes = []
    if applyFakeRateWeights == "2tau":
      self.apply_leptonGenMatching = False
      self.apply_hadTauGenMatching = True
      for hadTau_genMatch in self.hadTau_genMatches:
        if hadTau_genMatch.endswith("0j"):
          self.hadTau_genMatches_nonfakes.append(hadTau_genMatch)
        else:
          self.hadTau_genMatches_fakes.append(hadTau_genMatch)
      if run_mcClosure:
        self.hadTau_selections.extend([ "Fakeable_mcClosure_t" ])
      self.central_or_shifts_fr = systematics.FR_t
    else:
      raise ValueError("Invalid Configuration parameter 'applyFakeRateWeights' = %s !!" % applyFakeRateWeights)
    self.pruneSystematics()

    self.executable_addBackgrounds = executable_addBackgrounds
    self.executable_addFakes = executable_addBackgroundJetToTauFakes

    self.nonfake_backgrounds = [ "TT", "TTW", "TTWW", "TTZ", "EWK", "WZ", "ZZ", "Rares", "DY",  "tHq", "tHW", "VH", "HH", "ggH", "qqH", "TTWH", "TTZH" ]
    samples_categories_MC = []
    for sample_category in self.nonfake_backgrounds + self.ttHProcs:
      if sample_category == "signal" :  sample_category = "ttH"
      if sample_category == "signal_ctcvcp" :  sample_category = "ttH_ctcvcp"
      decays = [""]
      if sample_category in self.procsWithDecayModes : decays += self.decayModes
      couplings = [""]
      if sample_category in ["tHq", "tHW"] : couplings += self.thcouplings
      for decayMode in decays :
        for coupling in couplings :
            if sample_category not in self.ttHProcs and decayMode in ["hmm", "hzg"] : continue
            if sample_category in ["tHq", "tHW"] and not coupling == "" and decayMode == "" : continue
            if coupling == "" and decayMode == "" :
              samples_categories_MC.append("%s" % sample_category)
            elif coupling == "" :
              samples_categories_MC.append("%s_%s" % (sample_category, decayMode))
            else:
              samples_categories_MC.append("%s_%s_%s" % (sample_category, coupling, decayMode))
    self.prep_dcard_processesToCopy = [ "data_obs" ] + samples_categories_MC + [ "data_fakes", "fakes_mc" ]
    self.make_plots_backgrounds = self.nonfake_backgrounds + [ "data_fakes" ]

    self.cfgFile_analyze = os.path.join(self.template_dir, cfgFile_analyze)
    self.histogramDir_prep_dcard = "0l_2tau_OS_Tight"
    self.histogramDir_prep_dcard_SS = "0l_2tau_SS_Tight"
    self.cfgFile_make_plots = os.path.join(self.template_dir, "makePlots_0l_2tau_cfg.py")
    self.cfgFile_make_plots_mcClosure = os.path.join(self.template_dir, "makePlots_mcClosure_0l_2tau_cfg.py")

    self.rle_select = rle_select
    self.use_nonnominal = use_nonnominal
    self.select_rle_output = select_rle_output
    self.hlt_filter = hlt_filter

    self.categories = [
      "0l_2tau",
      #"0l_2tau_0bM_0j", "0l_2tau_1bM_0j", "0l_2tau_2bM_0j",
      #"0l_2tau_0bM_1j", "0l_2tau_1bM_1j", "0l_2tau_2bM_1j",
      #"0l_2tau_0bM_2j", "0l_2tau_1bM_2j", "0l_2tau_2bM_2j"
      ]  ## N.B.: Inclusive category in a member of this list
    self.category_inclusive = "0l_2tau"

  def set_BDT_training(self, hadTau_selection_relaxed):
    """Run analysis with loose selection criteria for hadronic taus,
       for the purpose of preparing event list files for BDT training.
    """
    self.hadTau_selections = [ "forBDTtraining" ]
    self.hadTau_frWeights  = [ "disabled" ]
    super(analyzeConfig_0l_2tau, self).set_BDT_training(hadTau_selection_relaxed)

  def createCfg_analyze(self, jobOptions, sample_info, hadTau_selection):
    """Create python configuration file for the analyze_0l_2tau executable (analysis code)

    Args:
      inputFiles: list of input files (Ntuples)
      outputFile: output file of the job -- a ROOT file containing histogram
      process: either `TT`, `TTW`, `TTZ`, `EWK`, `Rares`, `data_obs`, `ttH_hww`, 'ttH_hzg', 'ttH_hmm', `ttH_hzz` or `ttH_htt`
      is_mc: flag indicating whether job runs on MC (True) or data (False)
      lumi_scale: event weight (= xsection * luminosity / number of events)
      central_or_shift: either 'central' or one of the systematic uncertainties defined in $CMSSW_BASE/src/tthAnalysis/HiggsToTauTau/bin/analyze_0l_2tau.cc
    """
    hadTau_frWeight = "disabled" if jobOptions['applyFakeRateWeights'] == "disabled" else "enabled"
    jobOptions['histogramDir'] = getHistogramDir(self.category_inclusive,
      hadTau_selection, hadTau_frWeight, jobOptions['hadTauChargeSelection']
    )
    if 'mcClosure' in hadTau_selection:
      self.mcClosure_dir['%s_%s' % (hadTau_selection, jobOptions['hadTauChargeSelection'])] = jobOptions['histogramDir']

    jobOptions['hadTauFakeRateWeight.inputFileName'] = self.hadTauFakeRateWeight_inputFile
    graphName = 'jetToTauFakeRate/%s/$etaBin/jetToTauFakeRate_mc_hadTaus_pt' % self.hadTau_selection_part2
    jobOptions['hadTauFakeRateWeight.lead.graphName'] = graphName
    jobOptions['hadTauFakeRateWeight.sublead.graphName'] = graphName
    fitFunctionName = 'jetToTauFakeRate/%s/$etaBin/fitFunction_data_div_mc_hadTaus_pt' % self.hadTau_selection_part2
    jobOptions['hadTauFakeRateWeight.lead.fitFunctionName'] = fitFunctionName
    jobOptions['hadTauFakeRateWeight.sublead.fitFunctionName'] = fitFunctionName
    if "mcClosure" in hadTau_selection:
      jobOptions['hadTauFakeRateWeight.applyGraph_lead'] = True
      jobOptions['hadTauFakeRateWeight.applyGraph_sublead'] = True
      jobOptions['hadTauFakeRateWeight.applyFitFunction_lead'] = False
      jobOptions['hadTauFakeRateWeight.applyFitFunction_sublead'] = False
      if self.applyFakeRateWeights not in [ "2tau" ] and not self.isBDTtraining:
        # We want to preserve the same logic as running in SR [*]
        jobOptions['hadTauFakeRateWeight.applyFitFunction_lead'] = True
        jobOptions['hadTauFakeRateWeight.applyFitFunction_sublead'] = True
    if jobOptions['hadTauSelection'].find("Tight") != -1 and self.applyFakeRateWeights not in [ "2tau" ] and not self.isBDTtraining:
      # [*] SR and applying the FF method to both taus
      jobOptions['hadTauFakeRateWeight.applyGraph_lead'] = False # FR in MC for the leading tau
      jobOptions['hadTauFakeRateWeight.applyGraph_sublead'] = False
      jobOptions['hadTauFakeRateWeight.applyFitFunction_lead'] = True # data-to-MC SF for the leading tau
      jobOptions['hadTauFakeRateWeight.applyFitFunction_sublead'] = True
      jobOptions['apply_hadTauFakeRateSF'] = True

    lines = super(analyzeConfig_0l_2tau, self).createCfg_analyze(jobOptions, sample_info)
    create_cfg(self.cfgFile_analyze, jobOptions['cfgFile_modified'], lines)

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
      for hadTau_selection in self.hadTau_selections:
        for hadTau_frWeight in self.hadTau_frWeights:
          if hadTau_frWeight == "enabled" and not hadTau_selection.startswith("Fakeable"):
            continue
          if hadTau_frWeight == "disabled" and not hadTau_selection in [ "Tight", "forBDTtraining" ]:
            continue

          hadTau_selection_and_frWeight = get_hadTau_selection_and_frWeight(hadTau_selection, hadTau_frWeight)
          for hadTau_charge_selection in self.hadTau_charge_selections:
            central_or_shift_extensions = ["", "hadd", "addBackgrounds"]
            central_or_shifts_extended = central_or_shift_extensions + self.central_or_shifts
            for central_or_shift_or_dummy in central_or_shifts_extended:
              process_name_extended = [ process_name, "hadd" ]
              for process_name_or_dummy in process_name_extended:
                if central_or_shift_or_dummy in [ "hadd", "addBackgrounds" ] and process_name_or_dummy in [ "hadd" ]:
                  continue
                if central_or_shift_or_dummy != "central" and central_or_shift_or_dummy not in central_or_shift_extensions:
                  isFR_shape_shift = (central_or_shift_or_dummy in self.central_or_shifts_fr)
                  if not ((hadTau_selection == "Fakeable" and hadTau_charge_selection == "OS" and isFR_shape_shift) or
                          (hadTau_selection == "Tight"    and hadTau_charge_selection == "OS")):
                    continue
                  if isFR_shape_shift and hadTau_selection == "Tight":
                    continue
                  if not is_mc and not isFR_shape_shift:
                    continue

                if not self.accept_central_or_shift(central_or_shift_or_dummy, sample_category, sample_name):
                  continue

                key_dir = getKey(process_name_or_dummy, hadTau_selection_and_frWeight, hadTau_charge_selection, central_or_shift_or_dummy)
                for dir_type in [ DKEY_CFGS, DKEY_HIST, DKEY_LOGS, DKEY_RLES, DKEY_SYNC ]:
                  initDict(self.dirs, [ key_dir, dir_type ])
                  if dir_type in [ DKEY_CFGS, DKEY_LOGS ]:
                    self.dirs[key_dir][dir_type] = os.path.join(self.configDir, dir_type, self.channel,
                      "_".join([ hadTau_selection_and_frWeight, hadTau_charge_selection ]), process_name_or_dummy, central_or_shift_or_dummy)
                  else:
                    self.dirs[key_dir][dir_type] = os.path.join(self.outputDir, dir_type, self.channel,
                      "_".join([ hadTau_selection_and_frWeight, hadTau_charge_selection ]), process_name_or_dummy, central_or_shift_or_dummy)
    for subdirectory in [ "addBackgrounds", "addBackgroundLeptonFakes", "prepareDatacards", "addSystFakeRates", "makePlots" ]:
      key_dir = getKey(subdirectory)
      for dir_type in [ DKEY_CFGS, DKEY_HIST, DKEY_LOGS, DKEY_ROOT, DKEY_DCRD, DKEY_PLOT ]:
        initDict(self.dirs, [ key_dir, dir_type ])
        if dir_type in [ DKEY_CFGS, DKEY_LOGS, DKEY_DCRD, DKEY_PLOT ]:
          self.dirs[key_dir][dir_type] = os.path.join(self.configDir, dir_type, self.channel, subdirectory)
        else:
          self.dirs[key_dir][dir_type] = os.path.join(self.outputDir, dir_type, self.channel, subdirectory)
    for dir_type in [ DKEY_CFGS, DKEY_SCRIPTS, DKEY_HIST, DKEY_LOGS, DKEY_DCRD, DKEY_PLOT, DKEY_HADD_RT, DKEY_SYNC ]:
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

    for hadTau_selection in self.hadTau_selections:

      hadTauSelection = None
      if hadTau_selection == "forBDTtraining":
        hadTauSelection = "Tight|%s" % self.hadTau_selection_relaxed
      elif hadTau_selection == "Fakeable_mcClosure_t":
        hadTauSelection = "Fakeable|%s" % self.hadTau_selection_part2
      else:
        hadTauSelection = "|".join([ hadTau_selection, self.hadTau_selection_part2 ])

      for hadTau_frWeight in self.hadTau_frWeights:
        if hadTau_frWeight == "enabled" and not hadTau_selection.startswith("Fakeable"):
          continue
        if hadTau_frWeight == "disabled" and not hadTau_selection in [ "Tight", "forBDTtraining" ]:
          continue
        hadTau_selection_and_frWeight = get_hadTau_selection_and_frWeight(hadTau_selection, hadTau_frWeight)

        for hadTau_charge_selection in self.hadTau_charge_selections:

          for sample_name, sample_info in self.samples.items():
            if not sample_info["use_it"]:
              continue
            process_name = sample_info["process_name_specific"]
            logging.info("Creating configuration files to run '%s' for sample %s" % (self.executable_analyze, process_name))
            inputFileList = inputFileLists[sample_name]

            sample_category = sample_info["sample_category"]
            is_mc = (sample_info["type"] == "mc")

            for central_or_shift in self.central_or_shifts:

              if central_or_shift != "central":
                isFR_shape_shift = (central_or_shift in self.central_or_shifts_fr)
                if not ((hadTau_selection == "Fakeable" and hadTau_charge_selection == "OS" and isFR_shape_shift) or
                        (hadTau_selection == "Tight"    and hadTau_charge_selection == "OS")):
                  continue
                if isFR_shape_shift and hadTau_selection == "Tight":
                  continue
                if not is_mc and not isFR_shape_shift:
                  continue

              if not self.accept_central_or_shift(central_or_shift, sample_category, sample_name):
                continue

              logging.info(" ... for '%s' and systematic uncertainty option '%s'" % (hadTau_selection_and_frWeight, central_or_shift))

              # build config files for executing analysis code
              key_analyze_dir = getKey(process_name, hadTau_selection_and_frWeight, hadTau_charge_selection, central_or_shift)

              for jobId in inputFileList.keys():

                analyze_job_tuple = (process_name, hadTau_selection_and_frWeight, hadTau_charge_selection, central_or_shift, jobId)
                key_analyze_job = getKey(*analyze_job_tuple)
                ntupleFiles = inputFileList[jobId]
                if len(ntupleFiles) == 0:
                  logging.warning("No input ntuples for %s --> skipping job !!" % (key_analyze_job))
                  continue

                syncOutput = ''
                syncTree = ''
                syncGenMatch = self.hadTau_genMatches_nonfakes
                if self.do_sync:
                  if hadTau_charge_selection != 'OS':
                    continue
                  if hadTau_selection_and_frWeight == 'Tight':
                    syncOutput = os.path.join(self.dirs[key_analyze_dir][DKEY_SYNC], '%s_%s_SR.root' % (self.channel, central_or_shift))
                    syncTree   = 'syncTree_%s_SR' % self.channel.replace('_', '')
                  elif hadTau_selection_and_frWeight == 'Fakeable_wFakeRateWeights':
                    syncOutput = os.path.join(self.dirs[key_analyze_dir][DKEY_SYNC], '%s_%s_Fake.root' % (self.channel, central_or_shift))
                    syncTree   = 'syncTree_%s_Fake' % self.channel.replace('_', '')
                  elif hadTau_selection_and_frWeight == "Fakeable_mcClosure_t_wFakeRateWeights":
                    syncOutput = os.path.join(self.dirs[key_analyze_dir][DKEY_SYNC], '%s_%s_mcClosure_t.root' % (self.channel, central_or_shift))
                    syncTree = 'syncTree_%s_mcClosure_t' % self.channel.replace('_', '')
                  else:
                    continue
                if syncTree and central_or_shift != "central":
                  syncTree = os.path.join(central_or_shift, syncTree)
                syncRLE = ''
                if self.do_sync and self.rle_select:
                  syncRLE = self.rle_select % syncTree
                  if not os.path.isfile(syncRLE):
                    logging.warning("Input RLE file for the sync is missing: %s; skipping the job" % syncRLE)
                    continue
                if syncOutput:
                  self.inputFiles_sync['sync'].append(syncOutput)

                cfgFile_modified_path = os.path.join(self.dirs[key_analyze_dir][DKEY_CFGS], "analyze_%s_%s_%s_%s_%i_cfg.py" % analyze_job_tuple)
                logFile_path = os.path.join(self.dirs[key_analyze_dir][DKEY_LOGS], "analyze_%s_%s_%s_%s_%i.log" % analyze_job_tuple)
                rleOutputFile_path = os.path.join(self.dirs[key_analyze_dir][DKEY_RLES], "rle_%s_%s_%s_%s_%i.txt" % analyze_job_tuple) \
                                     if self.select_rle_output else ""
                histogramFile_path = os.path.join(self.dirs[key_analyze_dir][DKEY_HIST], "analyze_%s_%s_%s_%s_%i.root" % analyze_job_tuple)
                applyFakeRateWeights = self.applyFakeRateWeights \
                  if self.isBDTtraining or hadTau_selection.find("Tight") == -1 \
                  else "disabled"

                self.jobOptions_analyze[key_analyze_job] = {
                  'ntupleFiles'              : ntupleFiles,
                  'cfgFile_modified'         : cfgFile_modified_path,
                  'histogramFile'            : histogramFile_path,
                  'logFile'                  : logFile_path,
                  'selEventsFileName_output' : rleOutputFile_path,
                  'hadTauSelection'          : hadTauSelection,
                  'apply_hadTauGenMatching'  : self.apply_hadTauGenMatching,
                  'hadTauChargeSelection'    : hadTau_charge_selection,
                  'applyFakeRateWeights'     : applyFakeRateWeights,
                  'central_or_shift'         : central_or_shift,
                  'selectBDT'                : self.isBDTtraining,
                  'syncOutput'               : syncOutput,
                  'syncTree'                 : syncTree,
                  'syncRLE'                  : syncRLE,
                  'apply_hlt_filter'         : self.hlt_filter,
                  'useNonNominal'            : self.use_nonnominal,
                  'fillGenEvtHistograms'     : True,
                  'syncGenMatch'             : syncGenMatch,
                  'useObjectMultiplicity'    : self.era in ['2018'],
                }
                self.createCfg_analyze(self.jobOptions_analyze[key_analyze_job], sample_info, hadTau_selection)

                # initialize input and output file names for hadd_stage1
                key_hadd_stage1_dir = getKey(process_name, hadTau_selection_and_frWeight, hadTau_charge_selection)
                hadd_stage1_job_tuple = (process_name, hadTau_selection_and_frWeight, hadTau_charge_selection)
                key_hadd_stage1_job = getKey(*hadd_stage1_job_tuple)
                if not key_hadd_stage1_job in self.inputFiles_hadd_stage1:
                  self.inputFiles_hadd_stage1[key_hadd_stage1_job] = []
                self.inputFiles_hadd_stage1[key_hadd_stage1_job].append(self.jobOptions_analyze[key_analyze_job]['histogramFile'])
                self.outputFile_hadd_stage1[key_hadd_stage1_job] = os.path.join(self.dirs[key_hadd_stage1_dir][DKEY_HIST],
                                                                                "hadd_stage1_%s_%s_%s.root" % hadd_stage1_job_tuple)

            if self.isBDTtraining or self.do_sync:
              continue

            if is_mc:
              logging.info("Creating configuration files to run 'addBackgrounds' for sample %s" % process_name)
              sample_categories = [ sample_category ]
              for sample_category in sample_categories:
                if sample_category == "signal" :  sample_category = "ttH"
                if sample_category == "signal_ctcvcp" :  sample_category = "ttH_ctcvcp"
                decays = [""]
                if sample_category in self.procsWithDecayModes : decays += self.decayModes
                couplings = [""]
                if sample_category in ["tHq", "tHW"] : couplings += self.thcouplings
                # sum non-fake and fake contributions for each MC sample separately
                genMatch_categories = [ "nonfake", "fake"]
                for decayMode in decays :
                  for coupling in couplings :
                    if sample_category not in self.ttHProcs and decayMode in ["hmm", "hzg"] : continue
                    if sample_category in ["tHq", "tHW"] and not coupling == "" and decayMode == "" : continue
                    for genMatch_category in genMatch_categories:
                      key_hadd_stage1_job = getKey(process_name, hadTau_selection_and_frWeight, hadTau_charge_selection)
                      key_addBackgrounds_dir = getKey(process_name, hadTau_selection_and_frWeight, hadTau_charge_selection, "addBackgrounds")
                      addBackgrounds_job_tuple = None
                      processes_input = None
                      process_output = None
                      if genMatch_category == "nonfake":
                        # sum non-fake contributions for each MC sample separately
                        # input processes: TT4l0g0j; ...
                        # output processes: TT; ...
                        lepton_genMatches = []
                        lepton_genMatches.extend(self.hadTau_genMatches_nonfakes)
                        copy_genMatches = lepton_genMatches
                      elif genMatch_category == "fake":
                        copy_genMatches = self.hadTau_genMatches_fakes
                      processes_input = []
                      ## the SM tH's does not have the couplings
                      if coupling == "" :
                        if decayMode == "" :
                          processes_input = [ "%s%s" % (sample_category, genMatch) for genMatch in copy_genMatches ]
                          process_output = sample_category
                        else :
                          processes_input.extend([ "%s_%s%s" % (sample_category, decayMode, genMatch) for genMatch in copy_genMatches ])
                          process_output = "%s_%s" % (sample_category, decayMode)
                      else :
                        # If there is coupling, there is decayMode
                        processes_input.extend([ "%s_%s_%s%s" % (sample_category, coupling, decayMode, genMatch) for genMatch in copy_genMatches ])
                        process_output = "%s_%s_%s" % (sample_category, coupling, decayMode)
                      if genMatch_category in ["fake"] : process_output += "_" + genMatch_category
                      addBackgrounds_job_tuple = (process_name, process_output, hadTau_selection_and_frWeight, hadTau_charge_selection)
                      if processes_input:
                        logging.info(" ...for genMatch option = '%s'" % genMatch_category)
                        key_addBackgrounds_job = getKey(*addBackgrounds_job_tuple)
                        cfgFile_modified = os.path.join(self.dirs[key_addBackgrounds_dir][DKEY_CFGS], "addBackgrounds_%s_%s_%s_%s_cfg.py" % addBackgrounds_job_tuple)
                        outputFile = os.path.join(self.dirs[key_addBackgrounds_dir][DKEY_HIST], "addBackgrounds_%s_%s_%s_%s.root" % addBackgrounds_job_tuple)
                        self.jobOptions_addBackgrounds[key_addBackgrounds_job] = {
                          'inputFile' : self.outputFile_hadd_stage1[key_hadd_stage1_job],
                          'cfgFile_modified' : cfgFile_modified,
                          'outputFile' : outputFile,
                          'logFile' : os.path.join(self.dirs[key_addBackgrounds_dir][DKEY_LOGS], os.path.basename(cfgFile_modified).replace("_cfg.py", ".log")),
                          'categories' : [ getHistogramDir(category, hadTau_selection, hadTau_frWeight, hadTau_charge_selection) for category in self.categories],
                          'processes_input' : processes_input,
                          'process_output' : process_output
                        }
                        self.createCfg_addBackgrounds(self.jobOptions_addBackgrounds[key_addBackgrounds_job])

                        # initialize input and output file names for hadd_stage1_5
                        key_hadd_stage1_5_dir = getKey("hadd", hadTau_selection_and_frWeight, hadTau_charge_selection)
                        hadd_stage1_5_job_tuple = (hadTau_selection_and_frWeight, hadTau_charge_selection)
                        key_hadd_stage1_5_job = getKey(*hadd_stage1_5_job_tuple)
                        if not key_hadd_stage1_5_job in self.inputFiles_hadd_stage1_5:
                          self.inputFiles_hadd_stage1_5[key_hadd_stage1_5_job] = []
                        self.inputFiles_hadd_stage1_5[key_hadd_stage1_5_job].append(self.jobOptions_addBackgrounds[key_addBackgrounds_job]['outputFile'])
                        self.outputFile_hadd_stage1_5[key_hadd_stage1_5_job] = os.path.join(self.dirs[key_hadd_stage1_5_dir][DKEY_HIST],
                                                                                        "hadd_stage1_5_%s_%s.root" % hadd_stage1_5_job_tuple)

            if self.isBDTtraining or self.do_sync:
              continue

            # add output files of hadd_stage1 for data to list of input files for hadd_stage1_5
            if not is_mc:
              key_hadd_stage1_job = getKey(process_name, hadTau_selection_and_frWeight, hadTau_charge_selection)
              key_hadd_stage1_5_job = getKey(hadTau_selection_and_frWeight, hadTau_charge_selection)
              if not key_hadd_stage1_5_job in self.inputFiles_hadd_stage1_5:
                self.inputFiles_hadd_stage1_5[key_hadd_stage1_5_job] = []
              self.inputFiles_hadd_stage1_5[key_hadd_stage1_5_job].append(self.outputFile_hadd_stage1[key_hadd_stage1_job])

          if self.isBDTtraining or self.do_sync:
            continue

          ## doing list of processes to make the hadd in _Convs and _fake
          ## we could remove the tH ones with althernative couplings
          processes_input_base = []
          sample_categories = []
          sample_categories.extend(self.nonfake_backgrounds)
          sample_categories.extend(self.ttHProcs)
          for sample_category in sample_categories:
            if sample_category == "signal" :  sample_category = "ttH"
            if sample_category == "signal_ctcvcp" :  sample_category = "ttH_ctcvcp"
            decays = [""]
            if sample_category in self.procsWithDecayModes : decays += self.decayModes
            couplings = [""]
            for decayMode in decays :
              for coupling in couplings :
                if sample_category not in self.ttHProcs and decayMode in ["hmm", "hzg"] : continue
                if sample_category in ["tHq", "tHW"] and not coupling == "" and decayMode == "" : continue
                if coupling == "" and decayMode == "" :
                  processes_input_base.append("%s" % sample_category)
                elif coupling == "" :
                  processes_input_base.append("%s_%s" % (sample_category, decayMode))
                else:
                  processes_input_base.append("%s_%s_%s" % (sample_category, coupling, decayMode))

          # sum fake contributions for the total of all MC sample
          # input processes: TT1t0e0m1j, TT0t1e0m1j, TT0t0e1m1j, TT0t0e0m2j; TTW1t0e0m1j,...
          # output process: fakes_mc
          key_hadd_stage1_5_job = getKey(hadTau_selection_and_frWeight, hadTau_charge_selection)
          key_addBackgrounds_dir = getKey("addBackgrounds")
          addBackgrounds_job_fakes_tuple = ("fakes_mc", hadTau_selection_and_frWeight, hadTau_charge_selection)
          key_addBackgrounds_job_fakes = getKey(*addBackgrounds_job_fakes_tuple)
          sample_categories = []
          sample_categories.extend(self.nonfake_backgrounds)
          sample_categories.extend(self.signalProcs)
          processes_input = []
          for process_input_base in processes_input_base:
            processes_input.append("%s_fake" % process_input_base)
          self.jobOptions_addBackgrounds_sum[key_addBackgrounds_job_fakes] = {
            'inputFile' : self.outputFile_hadd_stage1_5[key_hadd_stage1_5_job],
            'cfgFile_modified' : os.path.join(self.dirs[key_addBackgrounds_dir][DKEY_CFGS], "addBackgrounds_%s_%s_%s_cfg.py" % addBackgrounds_job_fakes_tuple),
            'outputFile' : os.path.join(self.dirs[key_addBackgrounds_dir][DKEY_HIST], "addBackgrounds_%s_%s_%s.root" % addBackgrounds_job_fakes_tuple),
            'logFile' : os.path.join(self.dirs[key_addBackgrounds_dir][DKEY_LOGS], "addBackgrounds_%s_%s_%s.log" % addBackgrounds_job_fakes_tuple),
            'categories' : [ getHistogramDir(category, hadTau_selection, hadTau_frWeight, hadTau_charge_selection) for category in self.categories ],
            'processes_input' : processes_input,
            'process_output' : "fakes_mc"
          }
          self.createCfg_addBackgrounds(self.jobOptions_addBackgrounds_sum[key_addBackgrounds_job_fakes])

          # initialize input and output file names for hadd_stage2
          key_hadd_stage1_5_job = getKey(hadTau_selection_and_frWeight, hadTau_charge_selection)
          key_hadd_stage2_dir = getKey("hadd", hadTau_selection_and_frWeight, hadTau_charge_selection)
          hadd_stage2_job_tuple = (hadTau_selection_and_frWeight, hadTau_charge_selection)
          key_hadd_stage2_job = getKey(*hadd_stage2_job_tuple)
          if not key_hadd_stage2_job in self.inputFiles_hadd_stage2:
            self.inputFiles_hadd_stage2[key_hadd_stage2_job] = []
          if hadTau_selection == "Tight":
            self.inputFiles_hadd_stage2[key_hadd_stage2_job].append(self.jobOptions_addBackgrounds_sum[key_addBackgrounds_job_fakes]['outputFile'])
          self.inputFiles_hadd_stage2[key_hadd_stage2_job].append(self.outputFile_hadd_stage1_5[key_hadd_stage1_5_job])
          self.outputFile_hadd_stage2[key_hadd_stage2_job] = os.path.join(self.dirs[key_hadd_stage2_dir][DKEY_HIST], "hadd_stage2_%s_%s.root" % hadd_stage2_job_tuple)

    if self.isBDTtraining or self.do_sync:
      if self.is_sbatch:
        logging.info("Creating script for submitting '%s' jobs to batch system" % self.executable_analyze)
        self.sbatchFile_analyze = os.path.join(self.dirs[DKEY_SCRIPTS], "sbatch_analyze_%s.py" % self.channel)
        if self.isBDTtraining:
          self.createScript_sbatch_analyze(self.executable_analyze, self.sbatchFile_analyze, self.jobOptions_analyze)
        elif self.do_sync:
          self.createScript_sbatch_syncNtuple(self.executable_analyze, self.sbatchFile_analyze, self.jobOptions_analyze)
      logging.info("Creating Makefile")
      lines_makefile = []
      if self.isBDTtraining:
        self.addToMakefile_analyze(lines_makefile)
        self.addToMakefile_hadd_stage1(lines_makefile)
      elif self.do_sync:
        self.addToMakefile_syncNtuple(lines_makefile)
        outputFile_sync_path = os.path.join(self.outputDir, DKEY_SYNC, '%s.root' % self.channel)
        self.outputFile_sync['sync'] = outputFile_sync_path
        self.addToMakefile_hadd_sync(lines_makefile)
      else:
        raise ValueError("Internal logic error")
      self.targets.extend(self.phoniesToAdd)
      self.createMakefile(lines_makefile)
      logging.info("Done.")
      return self.num_jobs

    logging.info("Creating configuration files to run 'addBackgroundFakes'")
    for category in self.categories:
      for hadTau_charge_selection in self.hadTau_charge_selections:
        key_hadd_stage1_5_job = getKey(get_hadTau_selection_and_frWeight("Fakeable", "enabled"), hadTau_charge_selection)
        key_addFakes_dir = getKey("addBackgroundLeptonFakes")
        addFakes_job_tuple = (category, hadTau_charge_selection)
        key_addFakes_job = getKey("data_fakes", *addFakes_job_tuple)
        category_sideband = None
        if self.applyFakeRateWeights == "2tau":
          category_sideband = getHistogramDir(category, "Fakeable", "enabled", hadTau_charge_selection)
        else:
          raise ValueError("Invalid Configuration parameter 'applyFakeRateWeights' = %s !!" % self.applyFakeRateWeights)
        self.jobOptions_addFakes[key_addFakes_job] = {
          'inputFile' : self.outputFile_hadd_stage1_5[key_hadd_stage1_5_job],
          'cfgFile_modified' : os.path.join(self.dirs[key_addFakes_dir][DKEY_CFGS], "addBackgroundLeptonFakes_%s_%s_cfg.py" % addFakes_job_tuple),
          'outputFile' : os.path.join(self.dirs[key_addFakes_dir][DKEY_HIST], "addBackgroundLeptonFakes_%s_%s.root" % addFakes_job_tuple),
          'logFile' : os.path.join(self.dirs[key_addFakes_dir][DKEY_LOGS], "addBackgroundLeptonFakes_%s_%s.log" % addFakes_job_tuple),
          'category_signal' : getHistogramDir(category, "Tight", "disabled", hadTau_charge_selection),
          'category_sideband' : category_sideband
          }
        self.createCfg_addFakes(self.jobOptions_addFakes[key_addFakes_job])
        key_hadd_stage2_job = getKey(get_hadTau_selection_and_frWeight("Tight", "disabled"), hadTau_charge_selection)
        self.inputFiles_hadd_stage2[key_hadd_stage2_job].append(self.jobOptions_addFakes[key_addFakes_job]['outputFile'])

    logging.info("Creating configuration files to run 'prepareDatacards'")
    for category in self.categories:
      for histogramToFit in self.histograms_to_fit:
        key_prep_dcard_dir = getKey("prepareDatacards")
        if "OS" in self.hadTau_charge_selections:
          key_hadd_stage2_job = getKey(get_hadTau_selection_and_frWeight("Tight", "disabled"), "OS")
          prep_dcard_job_tuple = (self.channel, category, histogramToFit)
          key_prep_dcard_job = getKey(category, histogramToFit, "OS")
          self.jobOptions_prep_dcard[key_prep_dcard_job] = {
            'inputFile' : self.outputFile_hadd_stage2[key_hadd_stage2_job],
            'cfgFile_modified' : os.path.join(self.dirs[key_prep_dcard_dir][DKEY_CFGS], "prepareDatacards_%s_%s_%s_cfg.py" % prep_dcard_job_tuple),
            'datacardFile' : os.path.join(self.dirs[key_prep_dcard_dir][DKEY_DCRD], "prepareDatacards_%s_%s_%s.root" % prep_dcard_job_tuple),
            'histogramDir' : getHistogramDir(category, "Tight", "disabled", "OS"),
            'histogramToFit' : histogramToFit,
            'label' : None
          }
          self.createCfg_prep_dcard(self.jobOptions_prep_dcard[key_prep_dcard_job])

        if "SS" in self.hadTau_charge_selections:
          key_hadd_stage2_job = getKey(get_hadTau_selection_and_frWeight("Tight", "disabled"), "SS")
          prep_dcard_job_tuple = (self.channel, category, histogramToFit)
          key_prep_dcard_job = getKey(category, histogramToFit, "SS")
          self.jobOptions_prep_dcard[key_prep_dcard_job] = {
            'inputFile' : self.outputFile_hadd_stage2[key_hadd_stage2_job],
            'cfgFile_modified' : os.path.join(self.dirs[key_prep_dcard_dir][DKEY_CFGS], "prepareDatacards_%s_%s_SS_%s_cfg.py" % prep_dcard_job_tuple),
            'datacardFile' : os.path.join(self.dirs[key_prep_dcard_dir][DKEY_DCRD], "prepareDatacards_%s_%s_SS_%s.root" % prep_dcard_job_tuple),
            'histogramDir' : getHistogramDir(category, "Tight", "disabled", "SS"),
            'histogramToFit' : histogramToFit,
            'label' : 'SS'
          }
          self.createCfg_prep_dcard(self.jobOptions_prep_dcard[key_prep_dcard_job])

        # add shape templates for the following systematic uncertainties:
        #  - 'CMS_ttHl_Clos_norm_t'
        #  - 'CMS_ttHl_Clos_shape_t'
        for hadTau_charge_selection in self.hadTau_charge_selections:
          key_prep_dcard_job = getKey(category, histogramToFit, hadTau_charge_selection)
          key_hadd_stage2_job = getKey(get_hadTau_selection_and_frWeight("Tight", "disabled"), hadTau_charge_selection)
          key_add_syst_fakerate_dir = getKey("addSystFakeRates")
          add_syst_fakerate_job_tuple = (self.channel, category, histogramToFit, hadTau_charge_selection)
          key_add_syst_fakerate_job = getKey(category, histogramToFit, hadTau_charge_selection)
          self.jobOptions_add_syst_fakerate[key_add_syst_fakerate_job] = {
            'inputFile' : self.jobOptions_prep_dcard[key_prep_dcard_job]['datacardFile'],
            'cfgFile_modified' : os.path.join(self.dirs[key_add_syst_fakerate_dir][DKEY_CFGS], "addSystFakeRates_%s_%s_%s_%s_cfg.py" % add_syst_fakerate_job_tuple),
            'outputFile' : os.path.join(self.dirs[key_add_syst_fakerate_dir][DKEY_DCRD], "addSystFakeRates_%s_%s_%s_%s.root" % add_syst_fakerate_job_tuple),
            'category' : self.channel,
            'histogramToFit' : histogramToFit,
            'plots_outputFileName' : os.path.join(self.dirs[key_add_syst_fakerate_dir][DKEY_PLOT], "addSystFakeRates.png")
          }
          histogramDir_nominal = None
          if hadTau_charge_selection == "OS":
            histogramDir_nominal = self.histogramDir_prep_dcard
          elif hadTau_charge_selection == "SS":
            histogramDir_nominal = self.histogramDir_prep_dcard_SS
          else:
            raise ValueError("Invalid parameter 'hadTau_charge_selection' = %s !!" % hadTau_charge_selection)
          for hadTau_type in [ 't', ]:
            hadTau_mcClosure = "Fakeable_mcClosure_%s" % hadTau_type
            if hadTau_mcClosure not in self.hadTau_selections:
              continue
            hadTau_selection_and_frWeight = get_hadTau_selection_and_frWeight(hadTau_mcClosure, "enabled")
            key_addBackgrounds_job_fakes = getKey("fakes_mc", hadTau_selection_and_frWeight, hadTau_charge_selection)
            histogramDir_mcClosure = self.mcClosure_dir['%s_%s' % (hadTau_mcClosure, hadTau_charge_selection)]
            self.jobOptions_add_syst_fakerate[key_add_syst_fakerate_job].update({
                'add_Clos_%s' % hadTau_type : ("Fakeable_mcClosure_%s" % hadTau_type) in self.hadTau_selections,
                'inputFile_nominal_%s' % hadTau_type : self.outputFile_hadd_stage2[key_hadd_stage2_job],
                'histogramName_nominal_%s' % hadTau_type : "%s/sel/evt/fakes_mc/%s" % (histogramDir_nominal, histogramToFit),
                'inputFile_mcClosure_%s' % hadTau_type : self.jobOptions_addBackgrounds_sum[key_addBackgrounds_job_fakes]['outputFile'],
                'histogramName_mcClosure_%s' % hadTau_type : "%s/sel/evt/fakes_mc/%s" % (histogramDir_mcClosure, histogramToFit)
            })
            self.createCfg_add_syst_fakerate(self.jobOptions_add_syst_fakerate[key_add_syst_fakerate_job])

    logging.info("Creating configuration files to run 'makePlots'")
    key_makePlots_dir = getKey("makePlots")
    if "OS" in self.hadTau_charge_selections:
      key_hadd_stage2_job = getKey(get_hadTau_selection_and_frWeight("Tight", "disabled"), "OS")
      key_makePlots_job = getKey("OS")
      self.jobOptions_make_plots[key_makePlots_job] = {
        'executable' : self.executable_make_plots,
        'inputFile' : self.outputFile_hadd_stage2[key_hadd_stage2_job],
        'cfgFile_modified' : os.path.join(self.dirs[key_makePlots_dir][DKEY_CFGS], "makePlots_%s_cfg.py" % self.channel),
        'outputFile' : os.path.join(self.dirs[key_makePlots_dir][DKEY_PLOT], "makePlots_%s.png" % self.channel),
        'histogramDir' : getHistogramDir(self.category_inclusive, "Tight", "disabled", "OS"),
        'label' : "0l+2#tau_{h}",
        'make_plots_backgrounds' : self.make_plots_backgrounds
      }
      self.createCfg_makePlots(self.jobOptions_make_plots[key_makePlots_job])
    if "SS" in self.hadTau_charge_selections:
      key_hadd_stage2_job = getKey(get_hadTau_selection_and_frWeight("Tight", "disabled"), "SS")
      key_makePlots_job = getKey("SS")
      self.jobOptions_make_plots[key_makePlots_job] = {
        'executable' : self.executable_make_plots,
        'inputFile' : self.outputFile_hadd_stage2[key_hadd_stage2_job],
        'cfgFile_modified' : os.path.join(self.dirs[key_makePlots_dir][DKEY_CFGS], "makePlots_%s_SS_cfg.py" % self.channel),
        'outputFile' : os.path.join(self.dirs[key_makePlots_dir][DKEY_PLOT], "makePlots_%s_SS.png" % self.channel),
        'histogramDir' : getHistogramDir(self.category_inclusive, "Tight", "disabled", "SS"),
        'label' : "0l+2#tau_{h} SS",
        'make_plots_backgrounds' : self.make_plots_backgrounds
      }
      self.createCfg_makePlots(self.jobOptions_make_plots[key_makePlots_job])
    if "Fakeable_mcClosure" in self.hadTau_selections: #TODO
      key_hadd_stage2_job = getKey(get_hadTau_selection_and_frWeight("Tight", "disabled"), "OS")
      key_makePlots_job = getKey("OS")
      self.jobOptions_make_plots[key_makePlots_job] = {
        'executable' : self.executable_make_plots_mcClosure,
        'inputFile' : self.outputFile_hadd_stage2[key_hadd_stage2_job],
        'cfgFile_modified' : os.path.join(self.dirs[key_makePlots_dir][DKEY_CFGS], "makePlots_mcClosure_%s_cfg.py" % self.channel),
        'outputFile' : os.path.join(self.dirs[key_makePlots_dir][DKEY_PLOT], "makePlots_mcClosure_%s.png" % self.channel)
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

    logging.info("Done.")

    return self.num_jobs
