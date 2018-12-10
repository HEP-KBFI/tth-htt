import logging
import re

from tthAnalysis.HiggsToTauTau.configs.analyzeConfig import *
from tthAnalysis.HiggsToTauTau.jobTools import create_if_not_exists
from tthAnalysis.HiggsToTauTau.analysisTools import initDict, getKey, create_cfg, createFile, generateInputFileList, is_dymc_reweighting

def get_lepton_and_hadTau_selection_and_frWeight(lepton_and_hadTau_selection, lepton_and_hadTau_frWeight):
  lepton_and_hadTau_selection_and_frWeight = lepton_and_hadTau_selection
  if lepton_and_hadTau_selection.startswith("Fakeable"):
    if lepton_and_hadTau_frWeight == "enabled":
      lepton_and_hadTau_selection_and_frWeight += "_wFakeRateWeights"
    elif lepton_and_hadTau_frWeight == "disabled":
      lepton_and_hadTau_selection_and_frWeight += "_woFakeRateWeights"
  lepton_and_hadTau_selection_and_frWeight = lepton_and_hadTau_selection_and_frWeight.replace("|", "_")
  return lepton_and_hadTau_selection_and_frWeight

def getHistogramDir(category, hadTau_selection, hadTau_frWeight, chargeSumSelection):
  histogramDir = category
  if chargeSumSelection != "disabled":
    histogramDir += "_%s" % chargeSumSelection
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

class analyzeConfig_1l_1tau(analyzeConfig):
  """Configuration metadata needed to run analysis in a single go.

  Sets up a folder structure by defining full path names; no directory creation is delegated here.

  Args specific to analyzeConfig_1l_1tau:
    hadTau_selection: either `Tight`, `Loose` or `Fakeable`
    chargeSumSelections: either `OS` or `SS` or `disabled` (`disabled` will run opposite-sign and same-sign lepton+tau charge selections as separate categories)

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
        hadTau_selection_veto,
        chargeSumSelections,
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
        executable_addFlips,
        histograms_to_fit,
        select_rle_output = False,
        do_sync           = False,
        verbose           = False,
        dry_run           = False,
        isDebug           = False,
        rle_select        = '',
        use_nonnominal    = False,
        hlt_filter        = False,
        use_home          = True,
      ):
    analyzeConfig.__init__(self,
      configDir          = configDir,
      outputDir          = outputDir,
      executable_analyze = executable_analyze,
      channel            = "1l_1tau",
      samples            = samples,
      lep_mva_wp         = lep_mva_wp,
      central_or_shifts  = central_or_shifts,
      max_files_per_job  = max_files_per_job,
      era                = era,
      use_lumi           = use_lumi,
      lumi               = lumi,
      check_output_files = check_output_files,
      running_method     = running_method,
      num_parallel_jobs  = num_parallel_jobs,
      histograms_to_fit  = histograms_to_fit,
      triggers           = [ '1e', '1e1tau', '1mu', '1mu1tau' ],
      do_sync            = do_sync,
      verbose            = verbose,
      dry_run            = dry_run,
      isDebug            = isDebug,
      use_home           = use_home,
    )

    self.lepton_and_hadTau_selections = [ "Tight", "Fakeable" ]
    self.lepton_and_hadTau_frWeights = [ "enabled", "disabled" ]
    self.hadTau_selection_part2 = hadTau_selection
    self.hadTau_selection_veto = hadTau_selection_veto
    self.chargeSumSelections = chargeSumSelections
    self.applyFakeRateWeights = applyFakeRateWeights
    run_mcClosure = 'central' not in self.central_or_shifts or len(central_or_shifts) > 1 or self.do_sync
    if self.era != '2017':
      logging.warning('mcClosure for lepton FR not possible for era %s' % self.era)
      run_mcClosure = False
    if run_mcClosure:
      # Run MC closure jobs only if the analysis is run w/ (at least some) systematic uncertainties
      #self.lepton_and_hadTau_selections.extend([ "Fakeable_mcClosure_all" ]) #TODO
      pass

    self.lepton_genMatches = [ "1l0f0g0j", "1l1f0g0j", "0l0f1g0j", "0l0f0g1j" ]
    self.hadTau_genMatches = [ "1t0e0m0f0j", "1t0e0m1f0j", "0t1e0m0f0j", "0t1e0m1f0j", "0t0e1m0f0j", "0t0e1m1f0j", "0t0e0m0f1j" ]

    self.apply_leptonGenMatching = None
    self.apply_hadTauGenMatching = None
    self.lepton_and_hadTau_genMatches_nonfakes = []
    self.lepton_and_hadTau_genMatches_conversions = []
    self.lepton_and_hadTau_genMatches_flips = []
    self.lepton_and_hadTau_genMatches_fakes = []
    if self.applyFakeRateWeights == "2L":
      self.apply_leptonGenMatching = True
      self.apply_hadTauGenMatching = True
      for lepton_genMatch in self.lepton_genMatches:
        for hadTau_genMatch in self.hadTau_genMatches:
          lepton_and_hadTau_genMatch = "&".join([ lepton_genMatch, hadTau_genMatch ])
          if lepton_genMatch.endswith("0f0g0j") and hadTau_genMatch.endswith("0f0j"):
            self.lepton_and_hadTau_genMatches_nonfakes.append(lepton_and_hadTau_genMatch)
          elif lepton_genMatch.endswith("0g0j") and hadTau_genMatch.endswith("0j"):
            self.lepton_and_hadTau_genMatches_flips.append(lepton_and_hadTau_genMatch)
          elif lepton_genMatch.endswith("0j") and hadTau_genMatch.endswith("0j"):
            self.lepton_and_hadTau_genMatches_conversions.append(lepton_and_hadTau_genMatch)
          else:
            self.lepton_and_hadTau_genMatches_fakes.append(lepton_and_hadTau_genMatch)
      if run_mcClosure:
        self.lepton_and_hadTau_selections.extend([ "Fakeable_mcClosure_e", "Fakeable_mcClosure_m", "Fakeable_mcClosure_t" ])
    elif applyFakeRateWeights == "1tau":
      self.apply_leptonGenMatching = True
      self.apply_hadTauGenMatching = True
      for lepton_genMatch in self.lepton_genMatches:
        for hadTau_genMatch in self.hadTau_genMatches:
          if lepton_genMatch.find("0f0g") != -1 and hadTau_genMatch.endswith("0f0j"):
            self.lepton_and_hadTau_genMatches_nonfakes.append(hadTau_genMatch)
          elif lepton_genMatch.find("0g") != -1 and hadTau_genMatch.endswith("0j"):
            self.lepton_and_hadTau_genMatches_flips.append(hadTau_genMatch)
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
    self.executable_addFlips = executable_addFlips

    self.nonfake_backgrounds = [ "TT", "TTW", "TTZ", "TTWW", "EWK", "Rares", "tHq", "tHW", "VH" ]

    self.prep_dcard_processesToCopy = [ "data_obs" ] + self.nonfake_backgrounds + [ "conversions", "fakes_data", "fakes_mc", "flips_data", "flips_mc" ]
    self.make_plots_backgrounds_SS = [ "TT", "TTW", "TTZ", "TTWW", "EWK", "Rares", "tHq", "tHW" ] + [ "conversions", "fakes_data", "flips_data" ]
    self.make_plots_backgrounds_OS = [ "TT", "TTW", "TTZ", "TTWW", "EWK", "Rares", "tHq", "tHW" ] + [ "conversions", "fakes_data" ]

    self.cfgFile_analyze = os.path.join(self.template_dir, cfgFile_analyze)
    self.inputFiles_hadd_stage1_6 = {}
    self.outputFile_hadd_stage1_6 = {}
    self.cfgFile_addFlips = os.path.join(self.template_dir, "addBackgroundLeptonFlips_cfg.py")
    self.jobOptions_addFlips = {}
    self.cfgFile_make_plots = os.path.join(self.template_dir, "makePlots_1l_1tau_cfg.py")
    self.cfgFile_make_plots_mcClosure = os.path.join(self.template_dir, "makePlots_mcClosure_1l_1tau_cfg.py") #TODO

    self.select_rle_output = select_rle_output
    self.rle_select = rle_select
    self.use_nonnominal = use_nonnominal
    self.hlt_filter = hlt_filter

    self.categories = [
      "1l_1tau",  "1l_1tau_SS",  "1l_1tau_OS",  "1l_1tau_OS_wChargeFlipWeights",
      "1e_1tau",  "1e_1tau_SS",  "1e_1tau_OS",  "1e_1tau_OS_wChargeFlipWeights",
      "1mu_1tau", "1mu_1tau_SS", "1mu_1tau_OS", "1mu_1tau_OS_wChargeFlipWeights" ]
    self.category_inclusive = "1l_1tau"
    if not self.category_inclusive in self.categories:
      self.categories.append(self.category_inclusive)

  def set_BDT_training(self, hadTau_selection_relaxed):
    """Run analysis with loose selection criteria for leptons and hadronic taus,
       for the purpose of preparing event list files for BDT training.
    """
    self.lepton_and_hadTau_selections = [ "forBDTtraining" ]
    self.lepton_and_hadTau_frWeights  = [ "disabled" ]
    super(analyzeConfig_1l_1tau, self).set_BDT_training(hadTau_selection_relaxed)

  def createCfg_analyze(self, jobOptions, sample_info, lepton_and_hadTau_selection):
    """Create python configuration file for the analyze_1l_2tau executable (analysis code)

    Args:
      inputFiles: list of input files (Ntuples)
      outputFile: output file of the job -- a ROOT file containing histogram
      process: either `TT`, `TTW`, `TTZ`, `EWK`, `Rares`, `data_obs`, `ttH_hww`, 'ttH_hzg', 'ttH_hmm', `ttH_hzz` or `ttH_htt`
      is_mc: flag indicating whether job runs on MC (True) or data (False)
      lumi_scale: event weight (= xsection * luminosity / number of events)
      central_or_shift: either 'central' or one of the systematic uncertainties defined in $CMSSW_BASE/src/tthAnalysis/HiggsToTauTau/bin/analyze_1l_2tau.cc
    """
    lepton_and_hadTau_frWeight = "disabled" if jobOptions['applyFakeRateWeights'] == "disabled" else "enabled"
    jobOptions['histogramDir'] = getHistogramDir(
      self.category_inclusive, lepton_and_hadTau_selection, lepton_and_hadTau_frWeight, jobOptions['chargeSumSelection']
    )
    if 'mcClosure' in lepton_and_hadTau_selection:
      self.mcClosure_dir['%s_%s' % (lepton_and_hadTau_selection, jobOptions['chargeSumSelection'])] = jobOptions['histogramDir']

    self.set_leptonFakeRateWeightHistogramNames(jobOptions['central_or_shift'], lepton_and_hadTau_selection)
    jobOptions['leptonFakeRateWeight.inputFileName'] = self.leptonFakeRateWeight_inputFile
    jobOptions['leptonFakeRateWeight.histogramName_e'] = self.leptonFakeRateWeight_histogramName_e
    jobOptions['leptonFakeRateWeight.histogramName_mu'] = self.leptonFakeRateWeight_histogramName_mu

    jobOptions['hadTauFakeRateWeight.inputFileName'] = self.hadTauFakeRateWeight_inputFile
    graphName = 'jetToTauFakeRate/%s/$etaBin/jetToTauFakeRate_mc_hadTaus_pt' % self.hadTau_selection_part2
    jobOptions['hadTauFakeRateWeight.lead.graphName'] = graphName
    fitFunctionName = 'jetToTauFakeRate/%s/$etaBin/fitFunction_data_div_mc_hadTaus_pt' % self.hadTau_selection_part2
    jobOptions['hadTauFakeRateWeight.lead.fitFunctionName'] = fitFunctionName
    if "mcClosure" in lepton_and_hadTau_selection:
      jobOptions['hadTauFakeRateWeight.applyGraph_lead'] = True
      jobOptions['hadTauFakeRateWeight.applyFitFunction_lead'] = False
      if self.applyFakeRateWeights not in [ "2L", "1tau" ] and not self.isBDTtraining:
        # We want to preserve the same logic as running in SR and applying the FF method only to leptons [*]
        jobOptions['hadTauFakeRateWeight.applyFitFunction_lead'] = True
    if jobOptions['hadTauSelection'].find("Tight") != -1 and self.applyFakeRateWeights not in [ "2L", "1tau" ] and not self.isBDTtraining:
      # [*] SR and applying the FF method only to leptons
      jobOptions['hadTauFakeRateWeight.applyGraph_lead'] = False # FR in MC for the leading tau
      jobOptions['hadTauFakeRateWeight.applyFitFunction_lead'] = True # data-to-MC SF for the leading tau
      jobOptions['apply_hadTauFakeRateSF'] = True

    lines = super(analyzeConfig_1l_1tau, self).createCfg_analyze(jobOptions, sample_info)
    create_cfg(self.cfgFile_analyze, jobOptions['cfgFile_modified'], lines)

  def createCfg_addFlips(self, jobOptions):
    """Create python configuration file for the addBackgroundLeptonFlips executable (data-driven estimation of 'Flips' backgrounds)

       Args:
         inputFiles: input file (the ROOT file produced by hadd_stage1)
         outputFile: output file of the job
    """
    lines = []
    lines.append("process.fwliteInput.fileNames = cms.vstring('%s')" % jobOptions['inputFile'])
    lines.append("process.fwliteOutput.fileName = cms.string('%s')" % os.path.basename(jobOptions['outputFile']))
    lines.append("process.addBackgroundLeptonFlips.categories = cms.VPSet(")
    lines.append("    cms.PSet(")
    lines.append("        signal = cms.string('%s')," % jobOptions['category_signal'])
    lines.append("        sideband = cms.string('%s')" % jobOptions['category_sideband'])
    lines.append("    )")
    lines.append(")")
    processesToSubtract = [ "fakes_data" ]
    processesToSubtract.extend([ "%s_conversion" % nonfake_background for nonfake_background in self.nonfake_backgrounds ])
    lines.append("process.addBackgroundLeptonFlips.processesToSubtract = cms.vstring(%s)" % processesToSubtract)
    lines.append("process.addBackgroundLeptonFlips.sysShifts = cms.vstring(%s)" % self.central_or_shifts)
    create_cfg(self.cfgFile_addFlips, jobOptions['cfgFile_modified'], lines)

  def addToMakefile_hadd_stage1_6(self, lines_makefile):
    """Adds the commands to Makefile that are necessary for building the intermediate histogram file
       that is used as input for data-driven background estimation.
    """
    for chargeSumSelection in self.chargeSumSelections:
      key_hadd_stage1_6 = getKey(get_lepton_and_hadTau_selection_and_frWeight("Tight", "disabled"), chargeSumSelection)
      self.addToMakefile_hadd(lines_makefile, { key_hadd_stage1_6 : self.inputFiles_hadd_stage1_6[key_hadd_stage1_6] },
                                              { key_hadd_stage1_6 : self.outputFile_hadd_stage1_6[key_hadd_stage1_6] }, "stage1_6")

  def addToMakefile_addFlips(self, lines_makefile):
    if self.is_sbatch:
      lines_makefile.append("sbatch_addFlips: %s" % " ".join([ jobOptions['inputFile'] for jobOptions in self.jobOptions_addFlips.values() ]))
      lines_makefile.append("\t%s %s" % ("python", self.sbatchFile_addFlips))
      lines_makefile.append("")
    for jobOptions in self.jobOptions_addFlips.values():
      if self.is_makefile:
        lines_makefile.append("%s: %s" % (jobOptions['outputFile'], jobOptions['inputFile']))
        lines_makefile.append("\t%s %s &> %s" % (self.executable_addFlips, jobOptions['cfgFile_modified'], jobOptions['logFile']))
        lines_makefile.append("")
      elif self.is_sbatch:
        lines_makefile.append("%s: %s" % (jobOptions['outputFile'], "sbatch_addFlips"))
        lines_makefile.append("\t%s" % ":") # CV: null command
        lines_makefile.append("")
      self.filesToClean.append(jobOptions['outputFile'])

  def addToMakefile_backgrounds_from_data(self, lines_makefile):
    self.addToMakefile_addBackgrounds(lines_makefile, "sbatch_addBackgrounds", self.sbatchFile_addBackgrounds, self.jobOptions_addBackgrounds)
    self.addToMakefile_addBackgrounds(lines_makefile, "sbatch_addBackgrounds_sum", self.sbatchFile_addBackgrounds_sum, self.jobOptions_addBackgrounds_sum)
    self.addToMakefile_hadd_stage1_5(lines_makefile)
    self.addToMakefile_addFakes(lines_makefile)
    self.addToMakefile_hadd_stage1_6(lines_makefile)
    self.addToMakefile_addFlips(lines_makefile)

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
          for chargeSumSelection in self.chargeSumSelections:
            key_dir = getKey(process_name, lepton_and_hadTau_selection_and_frWeight, chargeSumSelection)
            for dir_type in [ DKEY_CFGS, DKEY_HIST, DKEY_LOGS, DKEY_RLES, DKEY_SYNC ]:
              initDict(self.dirs, [ key_dir, dir_type ])
              if dir_type in [ DKEY_CFGS, DKEY_LOGS ]:
                self.dirs[key_dir][dir_type] = os.path.join(self.configDir, dir_type, self.channel,
                  "_".join([ lepton_and_hadTau_selection_and_frWeight, chargeSumSelection ]), process_name)
              else:
                self.dirs[key_dir][dir_type] = os.path.join(self.outputDir, dir_type, self.channel,
                  "_".join([ lepton_and_hadTau_selection_and_frWeight, chargeSumSelection ]), process_name)
    for dir_type in [ DKEY_CFGS, DKEY_SCRIPTS, DKEY_HIST, DKEY_LOGS, DKEY_DCRD, DKEY_PLOT, DKEY_HADD_RT, DKEY_SYNC ]:
      initDict(self.dirs, [ dir_type ])
      if dir_type in [ DKEY_CFGS, DKEY_SCRIPTS, DKEY_LOGS, DKEY_DCRD, DKEY_PLOT, DKEY_HADD_RT ]:
        self.dirs[dir_type] = os.path.join(self.configDir, dir_type, self.channel)
      else:
        self.dirs[dir_type] = os.path.join(self.outputDir, dir_type, self.channel)

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

    mcClosure_regex = re.compile('Fakeable_mcClosure_(?P<type>m|e|t)_wFakeRateWeights')
    for chargeSumSelection in self.chargeSumSelections:
      for lepton_and_hadTau_selection in self.lepton_and_hadTau_selections:
        lepton_selection = lepton_and_hadTau_selection
        hadTau_selection = lepton_and_hadTau_selection
        electron_selection = lepton_selection
        muon_selection = lepton_selection

        if self.applyFakeRateWeights == "1tau":
          lepton_selection = "Tight"
        hadTau_selection = "|".join([ hadTau_selection, self.hadTau_selection_part2 ])

        if lepton_and_hadTau_selection == "forBDTtraining":
          electron_selection = "Tight"
          muon_selection = "Tight"
          hadTau_selection = "Tight|%s" % self.hadTau_selection_relaxed
        elif lepton_and_hadTau_selection == "Fakeable_mcClosure_e":
          electron_selection = "Fakeable"
          muon_selection = "Tight"
          hadTau_selection = "Tight"
          hadTau_selection = "|".join([hadTau_selection, self.hadTau_selection_part2])
        elif lepton_and_hadTau_selection == "Fakeable_mcClosure_m":
          electron_selection = "Tight"
          muon_selection = "Fakeable"
          hadTau_selection = "Tight"
          hadTau_selection = "|".join([hadTau_selection, self.hadTau_selection_part2])
        elif lepton_and_hadTau_selection == "Fakeable_mcClosure_t":
          electron_selection = "Tight"
          muon_selection = "Tight"
          hadTau_selection = "Fakeable"
          hadTau_selection = "|".join([hadTau_selection, self.hadTau_selection_part2])

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
                  if not (lepton_and_hadTau_selection == "Fakeable" and isFR_shape_shift) or lepton_and_hadTau_selection == "Tight":
                    continue
                  if not is_mc and not isFR_shape_shift:
                    continue

                if central_or_shift in systematics.LHE().ttH and sample_category != "signal":
                  continue
                if central_or_shift in systematics.LHE().ttW and sample_category != "TTW":
                  continue
                if central_or_shift in systematics.LHE().ttZ and sample_category != "TTZ":
                  continue
                if central_or_shift in systematics.DYMCReweighting and not is_dymc_reweighting(sample_name):
                  continue

                logging.info(" ... for '%s' and systematic uncertainty option '%s'" % (lepton_and_hadTau_selection_and_frWeight, central_or_shift))

                # build config files for executing analysis code
                key_dir = getKey(process_name, lepton_and_hadTau_selection_and_frWeight, chargeSumSelection)
                key_analyze_job = getKey(process_name, lepton_and_hadTau_selection_and_frWeight, chargeSumSelection, central_or_shift, jobId)
                ntupleFiles = inputFileList[jobId]
                if len(ntupleFiles) == 0:
                  logging.warning("No input ntuples for %s --> skipping job !!" % (key_analyze_job))
                  continue

                syncOutput = ''
                syncTree = ''
                syncRequireGenMatching = True
                mcClosure_match = mcClosure_regex.match(lepton_and_hadTau_selection_and_frWeight)
                if self.do_sync:
                  if lepton_and_hadTau_selection_and_frWeight == 'Tight':
                    syncOutput = os.path.join(self.dirs[key_dir][DKEY_SYNC], '%s_%s_SR.root' % (self.channel, central_or_shift))
                    syncTree   = 'syncTree_%s_SR' % self.channel.replace('_', '')
                    syncRequireGenMatching = True
                  elif lepton_and_hadTau_selection_and_frWeight == 'Fakeable_wFakeRateWeights':
                    syncOutput = os.path.join(self.dirs[key_dir][DKEY_SYNC], '%s_%s_Fake.root' % (self.channel, central_or_shift))
                    syncTree   = 'syncTree_%s_Fake' % self.channel.replace('_', '')
                  elif mcClosure_match:
                    mcClosure_type = mcClosure_match.group('type')
                    syncOutput = os.path.join(self.dirs[key_dir][DKEY_SYNC], '%s_%s_mcClosure_%s.root' % (self.channel, central_or_shift, mcClosure_type))
                    syncTree = 'syncTree_%s_mcClosure_%s' % (self.channel.replace('_', ''), mcClosure_type)
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

                cfg_key = getKey(
                  self.channel, process_name, lepton_and_hadTau_selection_and_frWeight,
                  chargeSumSelection, central_or_shift, jobId
                )
                cfgFile_modified_path = os.path.join(self.dirs[key_dir][DKEY_CFGS], "analyze_%s_cfg.py" % cfg_key)
                logFile_path = os.path.join(self.dirs[key_dir][DKEY_LOGS], "analyze_%s.log" % cfg_key)
                rleOutputFile_path = os.path.join(self.dirs[key_dir][DKEY_RLES], "rle_%s.txt" % cfg_key) \
                                     if self.select_rle_output else ""
                histogramFile_path = os.path.join(self.dirs[key_dir][DKEY_HIST], "%s.root" % key_analyze_job)
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
                  'hadTauSelection'          : hadTau_selection,
                  'hadTauSelection_veto'     : self.hadTau_selection_veto,
                  'apply_hadTauGenMatching'  : self.apply_hadTauGenMatching,
                  'chargeSumSelection'       : chargeSumSelection,
                  'applyFakeRateWeights'     : applyFakeRateWeights,
                  'central_or_shift'         : central_or_shift,
                  'selectBDT'                : self.isBDTtraining,
                  'syncOutput'               : syncOutput,
                  'syncTree'                 : syncTree,
                  'syncRLE'                  : syncRLE,
                  'syncRequireGenMatching'   : syncRequireGenMatching,
                  'apply_hlt_filter'         : self.hlt_filter,
                  'useNonNominal'            : self.use_nonnominal,
                  'fillGenEvtHistograms'     : True,
                }
                self.createCfg_analyze(self.jobOptions_analyze[key_analyze_job], sample_info, lepton_and_hadTau_selection)

                # initialize input and output file names for hadd_stage1
                key_hadd_stage1 = getKey(process_name, lepton_and_hadTau_selection_and_frWeight, chargeSumSelection)
                if not key_hadd_stage1 in self.inputFiles_hadd_stage1:
                  self.inputFiles_hadd_stage1[key_hadd_stage1] = []
                self.inputFiles_hadd_stage1[key_hadd_stage1].append(self.jobOptions_analyze[key_analyze_job]['histogramFile'])
                self.outputFile_hadd_stage1[key_hadd_stage1] = os.path.join(self.dirs[DKEY_HIST], "histograms_harvested_stage1_%s_%s_%s_%s.root" % \
                  (self.channel, process_name, lepton_and_hadTau_selection_and_frWeight, chargeSumSelection))

                if self.isBDTtraining:
                  self.targets.append(self.outputFile_hadd_stage1[key_hadd_stage1])

            if self.isBDTtraining or self.do_sync:
              continue

            if is_mc:
              logging.info("Creating configuration files to run 'addBackgrounds' for sample %s" % process_name)

              sample_categories = [ sample_category ]
              if is_signal:
                sample_categories = [ "signal", "ttH", "ttH_htt", "ttH_hww", "ttH_hzz", "ttH_hmm", "ttH_hzg" ]
              for sample_category in sample_categories:
                # sum non-fake and fake contributions for each MC sample separately
                genMatch_categories = [ "nonfake", "flips", "conversions", "fake" ]

                for genMatch_category in genMatch_categories:
                  key_hadd_stage1 = getKey(process_name, lepton_and_hadTau_selection_and_frWeight, chargeSumSelection)
                  key_addBackgrounds_job = None
                  processes_input = None
                  process_output = None
                  cfgFile_modified = None
                  outputFile = None
                  if genMatch_category == "nonfake":
                    # sum non-fake contributions for each MC sample separately
                    # input processes: TT1l0f0g0j&2t0e0m0j, TT1l0f0g0j&1t1e0m0f0j, TT1l0f0g0j&1t0e1m0f0j, TT1l0f0g0j&0t2e0m0f0j, TT1l0f0g0j&0t1e1m0f0j, TT1l0f0g0j&0t0e2m0f0j; ...
                    # output processes: TT; ...
                    if sample_category in [ "signal" ]:
                      lepton_and_hadTau_genMatches = []
                      lepton_and_hadTau_genMatches.extend(self.lepton_and_hadTau_genMatches_nonfakes)
                      lepton_and_hadTau_genMatches.extend(self.lepton_and_hadTau_genMatches_flips)
                      lepton_and_hadTau_genMatches.extend(self.lepton_and_hadTau_genMatches_conversions)
                      lepton_and_hadTau_genMatches.extend(self.lepton_and_hadTau_genMatches_fakes)
                      processes_input = [ "%s%s" % (sample_category, genMatch) for genMatch in lepton_and_hadTau_genMatches ]
                    elif sample_category in [ "ttH" ]:
                      lepton_and_hadTau_genMatches = []
                      lepton_and_hadTau_genMatches.extend(self.lepton_and_hadTau_genMatches_nonfakes)
                      lepton_and_hadTau_genMatches.extend(self.lepton_and_hadTau_genMatches_flips)
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
                    key_addBackgrounds_job = getKey(process_name, sample_category, lepton_and_hadTau_selection_and_frWeight, chargeSumSelection)
                    cfgFile_modified = os.path.join(self.dirs[DKEY_CFGS], "addBackgrounds_%s_%s_%s_%s_%s_cfg.py" % \
                      (self.channel, process_name, sample_category, lepton_and_hadTau_selection_and_frWeight, chargeSumSelection))
                    outputFile = os.path.join(self.dirs[DKEY_HIST], "addBackgrounds_%s_%s_%s_%s_%s.root" % \
                      (self.channel, process_name, sample_category, lepton_and_hadTau_selection_and_frWeight, chargeSumSelection))
                  elif genMatch_category == "flips":
                    # sum charge-flip background contributions for each MC sample separately
                    # input processes: TT1l1f0g0j,...
                    # output processes: TT_flips; ...
                    if sample_category in [ "signal" ]:
                      processes_input = [ "%s%s" % (sample_category, genMatch) for genMatch in self.lepton_and_hadTau_genMatches_flips ]
                    elif sample_category in [ "ttH" ]:
                      processes_input = []
                      processes_input.extend([ "%s%s" % ("ttH_htt", genMatch) for genMatch in self.lepton_and_hadTau_genMatches_flips ])
                      processes_input.extend([ "%s%s" % ("ttH_hww", genMatch) for genMatch in self.lepton_and_hadTau_genMatches_flips ])
                      processes_input.extend([ "%s%s" % ("ttH_hzz", genMatch) for genMatch in self.lepton_and_hadTau_genMatches_flips ])
                      processes_input.extend([ "%s%s" % ("ttH_hzg", genMatch) for genMatch in self.lepton_and_hadTau_genMatches_flips ])
                      processes_input.extend([ "%s%s" % ("ttH_hmm", genMatch) for genMatch in self.lepton_and_hadTau_genMatches_flips ])
                    else:
                      processes_input = [ "%s%s" % (sample_category, genMatch) for genMatch in self.lepton_and_hadTau_genMatches_flips ]
                    process_output = "%s_flips" % sample_category
                    key_addBackgrounds_job = getKey(process_name, "%s_flips" % sample_category, lepton_and_hadTau_selection_and_frWeight, chargeSumSelection)
                    cfgFile_modified = os.path.join(self.dirs[DKEY_CFGS], "addBackgrounds_%s_%s_flips_%s_%s_%s_cfg.py" % \
                      (self.channel, process_name, sample_category, lepton_and_hadTau_selection_and_frWeight, chargeSumSelection))
                    outputFile = os.path.join(self.dirs[DKEY_HIST], "addBackgrounds_%s_%s_flips_%s_%s_%s.root" % \
                      (self.channel, process_name, sample_category, lepton_and_hadTau_selection_and_frWeight, chargeSumSelection))
                  elif genMatch_category == "conversions":
                    # sum conversion background contributions for each MC sample separately
                    # input processes: TT0l0f1g0j,...
                    # output processes: TT_conversions; ...
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
                    key_addBackgrounds_job = getKey(process_name, "%s_conversion" % sample_category, lepton_and_hadTau_selection_and_frWeight, chargeSumSelection)
                    cfgFile_modified = os.path.join(self.dirs[DKEY_CFGS], "addBackgrounds_%s_%s_conversions_%s_%s_%s_cfg.py" % \
                      (self.channel, process_name, sample_category, lepton_and_hadTau_selection_and_frWeight, chargeSumSelection))
                    outputFile = os.path.join(self.dirs[DKEY_HIST], "addBackgrounds_%s_%s_conversions_%s_%s_%s.root" % \
                      (self.channel, process_name, sample_category, lepton_and_hadTau_selection_and_frWeight, chargeSumSelection))
                  elif genMatch_category == "fake":
                    # sum fake background contributions for each MC sample separately
                    # input processes: TT1l0f0g1j&0t0f0e0m1j, TT1l1f0g1j&0t0f0e0m1j, TT0l0f0g1j&1t0e0m0f0j, TT0l0f0g1j&1t0e0m1f0j, ...
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
                    key_addBackgrounds_job = getKey(process_name, "%s_fake" % sample_category, lepton_and_hadTau_selection_and_frWeight, chargeSumSelection)
                    cfgFile_modified = os.path.join(self.dirs[DKEY_CFGS], "addBackgrounds_%s_%s_fakes_%s_%s_%s_cfg.py" % \
                      (self.channel, process_name, sample_category, lepton_and_hadTau_selection_and_frWeight, chargeSumSelection))
                    outputFile = os.path.join(self.dirs[DKEY_HIST], "addBackgrounds_%s_%s_fakes_%s_%s_%s.root" % \
                      (self.channel, process_name, sample_category, lepton_and_hadTau_selection_and_frWeight, chargeSumSelection))
                  if processes_input:
                    logging.info(" ...for genMatch option = '%s'" % genMatch_category)
                    self.jobOptions_addBackgrounds[key_addBackgrounds_job] = {
                      'inputFile' : self.outputFile_hadd_stage1[key_hadd_stage1],
                      'cfgFile_modified' : cfgFile_modified,
                      'outputFile' : outputFile,
                      'logFile' : os.path.join(self.dirs[DKEY_LOGS], os.path.basename(cfgFile_modified).replace("_cfg.py", ".log")),
                      'categories' : [ getHistogramDir(category, lepton_and_hadTau_selection, lepton_and_hadTau_frWeight, chargeSumSelection) for category in self.categories ],
                      'processes_input' : processes_input,
                      'process_output' : process_output
                    }
                    self.createCfg_addBackgrounds(self.jobOptions_addBackgrounds[key_addBackgrounds_job])

                    # initialize input and output file names for hadd_stage1_5
                    key_hadd_stage1_5 = getKey(lepton_and_hadTau_selection_and_frWeight, chargeSumSelection)
                    if not key_hadd_stage1_5 in self.inputFiles_hadd_stage1_5:
                      self.inputFiles_hadd_stage1_5[key_hadd_stage1_5] = []
                    self.inputFiles_hadd_stage1_5[key_hadd_stage1_5].append(self.jobOptions_addBackgrounds[key_addBackgrounds_job]['outputFile'])
                    self.outputFile_hadd_stage1_5[key_hadd_stage1_5] = os.path.join(self.dirs[DKEY_HIST], "histograms_harvested_stage1_5_%s_%s_%s.root" % \
                     (self.channel, lepton_and_hadTau_selection_and_frWeight, chargeSumSelection))

            if self.isBDTtraining or self.do_sync:
              continue

            # add output files of hadd_stage1 for data to list of input files for hadd_stage1_5
            if not is_mc:
              key_hadd_stage1 = getKey(process_name, lepton_and_hadTau_selection_and_frWeight, chargeSumSelection)
              key_hadd_stage1_5 = getKey(lepton_and_hadTau_selection_and_frWeight, chargeSumSelection)
              if not key_hadd_stage1_5 in self.inputFiles_hadd_stage1_5:
                self.inputFiles_hadd_stage1_5[key_hadd_stage1_5] = []
              self.inputFiles_hadd_stage1_5[key_hadd_stage1_5].append(self.outputFile_hadd_stage1[key_hadd_stage1])

          if self.isBDTtraining or self.do_sync:
            continue

          # sum fake background contributions for the total of all MC sample
          # input processes: TT1l0f0g1j&0t0f0e0m1j, TT1l1f0g1j&0t0f0e0m1j, TT0l0f0g1j&1t0e0m0f0j, TT0l0f0g1j&1t0e0m1f0j, ...
          # output process: fakes_mc
          key_addBackgrounds_job_fakes = getKey(lepton_and_hadTau_selection_and_frWeight, chargeSumSelection, "fakes")
          key_hadd_stage1_5 = getKey(lepton_and_hadTau_selection_and_frWeight, chargeSumSelection)
          sample_categories = []
          sample_categories.extend(self.nonfake_backgrounds)
          sample_categories.extend([ "signal" ])
          processes_input = []
          for sample_category in sample_categories:
            processes_input.append("%s_fake" % sample_category)
          self.jobOptions_addBackgrounds_sum[key_addBackgrounds_job_fakes] = {
            'inputFile' : self.outputFile_hadd_stage1_5[key_hadd_stage1_5],
            'cfgFile_modified' : os.path.join(self.dirs[DKEY_CFGS], "addBackgrounds_%s_fakes_mc_%s_%s_cfg.py" % \
              (self.channel, lepton_and_hadTau_selection_and_frWeight, chargeSumSelection)),
            'outputFile' : os.path.join(self.dirs[DKEY_HIST], "addBackgrounds_%s_fakes_mc_%s_%s.root" % \
              (self.channel, lepton_and_hadTau_selection_and_frWeight, chargeSumSelection)),
            'logFile' : os.path.join(self.dirs[DKEY_LOGS], "addBackgrounds_%s_fakes_mc_%s_%s.log" % \
              (self.channel, lepton_and_hadTau_selection_and_frWeight, chargeSumSelection)),
            'categories' : [ getHistogramDir(category, lepton_and_hadTau_selection, lepton_and_hadTau_frWeight, chargeSumSelection) for category in self.categories ],
            'processes_input' : processes_input,
            'process_output' : "fakes_mc"
          }
          self.createCfg_addBackgrounds(self.jobOptions_addBackgrounds_sum[key_addBackgrounds_job_fakes])

          # sum charge-flip background contributions for the total of all MC sample
          # input processes: TT1l1f0g0j,...
          # output process: flips_mc
          key_addBackgrounds_job_flips = getKey(lepton_and_hadTau_selection_and_frWeight, chargeSumSelection, "flips")
          sample_categories = []
          sample_categories.extend(self.nonfake_backgrounds)
          sample_categories.extend([ "signal" ])
          processes_input = []
          for sample_category in sample_categories:
            processes_input.append("%s_flips" % sample_category)
          self.jobOptions_addBackgrounds_sum[key_addBackgrounds_job_flips] = {
            'inputFile' : self.outputFile_hadd_stage1_5[key_hadd_stage1_5],
            'cfgFile_modified' : os.path.join(self.dirs[DKEY_CFGS], "addBackgrounds_%s_flips_%s_%s_cfg.py" % \
              (self.channel, lepton_and_hadTau_selection_and_frWeight, chargeSumSelection)),
            'outputFile' : os.path.join(self.dirs[DKEY_HIST], "addBackgrounds_%s_flips_%s_%s.root" % \
              (self.channel, lepton_and_hadTau_selection_and_frWeight, chargeSumSelection)),
            'logFile' : os.path.join(self.dirs[DKEY_LOGS], "addBackgrounds_%s_flips_%s_%s.log" % \
              (self.channel, lepton_and_hadTau_selection_and_frWeight, chargeSumSelection)),
            'categories' : [ getHistogramDir(category, lepton_and_hadTau_selection, lepton_and_hadTau_frWeight, chargeSumSelection) for category in self.categories ],
            'processes_input' : processes_input,
            'process_output' : "flips_mc"
          }
          self.createCfg_addBackgrounds(self.jobOptions_addBackgrounds_sum[key_addBackgrounds_job_flips])

          # sum conversion background contributions for the total of all MC sample
          # input processes: TT0l0f1g0j,...
          # output process: conversions
          key_addBackgrounds_job_conversions = getKey(lepton_and_hadTau_selection_and_frWeight, chargeSumSelection, "conversions")
          sample_categories = []
          sample_categories.extend(self.nonfake_backgrounds)
          sample_categories.extend([ "signal" ])
          processes_input = []
          for sample_category in sample_categories:
            processes_input.append("%s_conversion" % sample_category)
          self.jobOptions_addBackgrounds_sum[key_addBackgrounds_job_conversions] = {
            'inputFile' : self.outputFile_hadd_stage1_5[key_hadd_stage1_5],
            'cfgFile_modified' : os.path.join(self.dirs[DKEY_CFGS], "addBackgrounds_%s_conversions_%s_%s_cfg.py" % \
              (self.channel, lepton_and_hadTau_selection_and_frWeight, chargeSumSelection)),
            'outputFile' : os.path.join(self.dirs[DKEY_HIST], "addBackgrounds_%s_conversions_%s_%s.root" % \
              (self.channel, lepton_and_hadTau_selection_and_frWeight, chargeSumSelection)),
            'logFile' : os.path.join(self.dirs[DKEY_LOGS], "addBackgrounds_%s_conversions_%s_%s.log" % \
              (self.channel, lepton_and_hadTau_selection_and_frWeight, chargeSumSelection)),
            'categories' : [ getHistogramDir(category, lepton_and_hadTau_selection, lepton_and_hadTau_frWeight, chargeSumSelection) for category in self.categories ],
            'processes_input' : processes_input,
            'process_output' : "conversions"
          }
          self.createCfg_addBackgrounds(self.jobOptions_addBackgrounds_sum[key_addBackgrounds_job_conversions])

          # initialize input and output file names for hadd_stage2
          key_hadd_stage2 = getKey(lepton_and_hadTau_selection_and_frWeight, chargeSumSelection)
          if not key_hadd_stage2 in self.inputFiles_hadd_stage2:
            self.inputFiles_hadd_stage2[key_hadd_stage2] = []
          if lepton_and_hadTau_selection == "Tight":
            self.inputFiles_hadd_stage2[key_hadd_stage2].append(self.jobOptions_addBackgrounds_sum[key_addBackgrounds_job_fakes]['outputFile'])
            self.inputFiles_hadd_stage2[key_hadd_stage2].append(self.jobOptions_addBackgrounds_sum[key_addBackgrounds_job_flips]['outputFile'])
            self.inputFiles_hadd_stage2[key_hadd_stage2].append(self.jobOptions_addBackgrounds_sum[key_addBackgrounds_job_conversions]['outputFile'])
          key_hadd_stage1_5 = getKey(lepton_and_hadTau_selection_and_frWeight, chargeSumSelection)
          self.inputFiles_hadd_stage2[key_hadd_stage2].append(self.outputFile_hadd_stage1_5[key_hadd_stage1_5])
          self.outputFile_hadd_stage2[key_hadd_stage2] = os.path.join(self.dirs[DKEY_HIST], "histograms_harvested_stage2_%s_%s_%s.root" % \
            (self.channel, lepton_and_hadTau_selection_and_frWeight, chargeSumSelection))

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
        self.targets.append(outputFile_sync_path)
        self.addToMakefile_hadd_sync(lines_makefile)
      else:
        raise ValueError("Internal logic error")
      self.createMakefile(lines_makefile)
      logging.info("Done")
      return self.num_jobs

    logging.info("Creating configuration files to run 'addBackgroundFakes'")
    for chargeSumSelection in self.chargeSumSelections:
      for category in self.categories:
        key_addFakes_job = getKey(category, "fakes_data", chargeSumSelection)
        key_hadd_stage1_5 = getKey(get_lepton_and_hadTau_selection_and_frWeight("Fakeable", "enabled"), chargeSumSelection)
        self.jobOptions_addFakes[key_addFakes_job] = {
          'inputFile' : self.outputFile_hadd_stage1_5[key_hadd_stage1_5],
          'cfgFile_modified' : os.path.join(self.dirs[DKEY_CFGS], "addBackgroundLeptonFakes_%s_%s_%s_cfg.py" % \
            (self.channel, category, chargeSumSelection)),
          'outputFile' : os.path.join(self.dirs[DKEY_HIST], "addBackgroundLeptonFakes_%s_%s_%s.root" % \
            (self.channel, category, chargeSumSelection)),
          'logFile' : os.path.join(self.dirs[DKEY_LOGS], "addBackgroundLeptonFakes_%s_%s_%s.log" % \
            (self.channel, category, chargeSumSelection)),
          'category_signal' : "%s_Tight" % category,
          'category_sideband' : "%s_Fakeable_wFakeRateWeights" % category
        }
        self.createCfg_addFakes(self.jobOptions_addFakes[key_addFakes_job])
        key_hadd_stage2 = getKey(get_lepton_and_hadTau_selection_and_frWeight("Tight", "disabled"), chargeSumSelection)
        self.inputFiles_hadd_stage2[key_hadd_stage2].append(self.jobOptions_addFakes[key_addFakes_job]['outputFile'])

    #--------------------------------------------------------------------------
    # CV: add histograms in OS and SS regions,
    #     so that "fakes_data" background can be subtracted from OS control region used to estimate charge flip background
    for chargeSumSelection in self.chargeSumSelections:
      key_hadd_stage1_6 = getKey(get_lepton_and_hadTau_selection_and_frWeight("Tight", "disabled"), chargeSumSelection)
      if key_hadd_stage1_6 not in self.inputFiles_hadd_stage1_6:
        self.inputFiles_hadd_stage1_6[key_hadd_stage1_6] = []
      for category in self.categories:
        key_addFakes_job = getKey(category, "fakes_data", chargeSumSelection)
        self.inputFiles_hadd_stage1_6[key_hadd_stage1_6].append(self.jobOptions_addFakes[key_addFakes_job]['outputFile'])
      key_hadd_stage1_5 = getKey(get_lepton_and_hadTau_selection_and_frWeight("Tight", "disabled"), chargeSumSelection)
      self.inputFiles_hadd_stage1_6[key_hadd_stage1_6].append(self.outputFile_hadd_stage1_5[key_hadd_stage1_5])
      self.outputFile_hadd_stage1_6[key_hadd_stage1_6] = os.path.join(self.dirs[DKEY_HIST], "histograms_harvested_stage1_6_%s_Tight_%s.root" % \
        (self.channel, chargeSumSelection))
    #--------------------------------------------------------------------------

    logging.info("Creating configuration files to run 'addBackgroundFlips'")
    for chargeSumSelection in self.chargeSumSelections:
      if not chargeSumSelection in [ "SS", "disabled" ]:
        continue
      for category_signal in self.categories:
        if not category_signal.find("_SS") != -1:
          continue
        key_addFlips_job = getKey(category_signal, "flips_data", chargeSumSelection)
        key_hadd_stage1_6 = getKey(get_lepton_and_hadTau_selection_and_frWeight("Tight", "disabled"), chargeSumSelection)
        self.jobOptions_addFlips[key_addFlips_job] = {
          'inputFile' : self.outputFile_hadd_stage1_6[key_hadd_stage1_6],
          'cfgFile_modified' : os.path.join(self.dirs[DKEY_CFGS], "addBackgroundLeptonFlips_%s_%s_%s_cfg.py" % \
            (self.channel, category_signal, chargeSumSelection)),
          'outputFile' : os.path.join(self.dirs[DKEY_HIST], "addBackgroundLeptonFlips_%s_%s_%s.root" % \
            (self.channel, category_signal, chargeSumSelection)),
          'logFile' : os.path.join(self.dirs[DKEY_LOGS], "addBackgroundLeptonFlips_%s_%s_%s.log" % \
            (self.channel, category_signal, chargeSumSelection)),
          'category_signal' : "%s_Tight" % category_signal,
          'category_sideband' : "%s_Tight" % category_signal.replace("_SS", "_OS_wChargeFlipWeights")
        }
        self.createCfg_addFlips(self.jobOptions_addFlips[key_addFlips_job])
        key_hadd_stage2 = getKey(get_lepton_and_hadTau_selection_and_frWeight("Tight", "disabled"), chargeSumSelection)
        self.inputFiles_hadd_stage2[key_hadd_stage2].append(self.jobOptions_addFlips[key_addFlips_job]['outputFile'])

    logging.info("Creating configuration files to run 'prepareDatacards'")
    for chargeSumSelection in self.chargeSumSelections:
      for category in self.categories:
        for histogramToFit in self.histograms_to_fit:
          key_prep_dcard_job = getKey(category, histogramToFit, chargeSumSelection)
          key_hadd_stage2 = getKey(get_lepton_and_hadTau_selection_and_frWeight("Tight", "disabled"), chargeSumSelection)
          self.jobOptions_prep_dcard[key_prep_dcard_job] = {
            'inputFile' : self.outputFile_hadd_stage2[key_hadd_stage2],
            'cfgFile_modified' : os.path.join(self.dirs[DKEY_CFGS], "prepareDatacards_%s_%s_%s_%s_cfg.py" % (self.channel, category, chargeSumSelection, histogramToFit)),
            'datacardFile' : os.path.join(self.dirs[DKEY_DCRD], "prepareDatacards_%s_%s_%s_%s.root" % (self.channel, category, chargeSumSelection, histogramToFit)),
            'histogramDir' : getHistogramDir(category, "Tight", "disabled", chargeSumSelection),
            'histogramToFit' : histogramToFit,
            'label' : category
          }
          self.createCfg_prep_dcard(self.jobOptions_prep_dcard[key_prep_dcard_job])

          # add shape templates for the following systematic uncertainties:
          #  - 'CMS_ttHl_Clos_norm_e'
          #  - 'CMS_ttHl_Clos_shape_e'
          #  - 'CMS_ttHl_Clos_norm_m'
          #  - 'CMS_ttHl_Clos_shape_m'
          #  - 'CMS_ttHl_Clos_norm_t'
          #  - 'CMS_ttHl_Clos_shape_t'
          key_prep_dcard_job = getKey(category, histogramToFit, chargeSumSelection)
          key_hadd_stage2 = getKey(get_lepton_and_hadTau_selection_and_frWeight("Tight", "disabled"), chargeSumSelection)
          key_add_syst_fakerate_job = getKey(category, histogramToFit, chargeSumSelection)
          self.jobOptions_add_syst_fakerate[key_add_syst_fakerate_job] = {
            'inputFile' : self.jobOptions_prep_dcard[key_prep_dcard_job]['datacardFile'],
            'cfgFile_modified' : os.path.join(self.dirs[DKEY_CFGS], "addSystFakeRates_%s_%s_%s_%s_cfg.py" % (self.channel, category, chargeSumSelection, histogramToFit)),
            'outputFile' : os.path.join(self.dirs[DKEY_DCRD], "addSystFakeRates_%s_%s_%s_%s.root" % (self.channel, category, chargeSumSelection, histogramToFit)),
            'category' : category,
            'histogramToFit' : histogramToFit,
            'plots_outputFileName' : os.path.join(self.dirs[DKEY_PLOT], "addSystFakeRates.png")
          }
          histogramDir_nominal = getHistogramDir(category, "Tight", "disabled", chargeSumSelection)
          for lepton_and_hadTau_type in [ 'e', 'm', 't' ]:
            lepton_and_hadTau_mcClosure = "Fakeable_mcClosure_%s" % lepton_and_hadTau_type
            if lepton_and_hadTau_mcClosure not in self.lepton_and_hadTau_selections:
              continue
            lepton_and_hadTau_selection_and_frWeight = get_lepton_and_hadTau_selection_and_frWeight(lepton_and_hadTau_mcClosure, "enabled")
            key_addBackgrounds_job_fakes = getKey(lepton_and_hadTau_selection_and_frWeight, chargeSumSelection, "fakes")
            histogramDir_mcClosure = self.mcClosure_dir['%s_%s' % (lepton_and_hadTau_mcClosure, chargeSumSelection)]
            self.jobOptions_add_syst_fakerate[key_add_syst_fakerate_job].update({
              'add_Clos_%s' % lepton_and_hadTau_type : ("Fakeable_mcClosure_%s" % lepton_and_hadTau_type) in self.lepton_and_hadTau_selections,
              'inputFile_nominal_%s' % lepton_and_hadTau_type : self.outputFile_hadd_stage2[key_hadd_stage2],
              'histogramName_nominal_%s' % lepton_and_hadTau_type : "%s/sel/evt/fakes_mc/%s" % (histogramDir_nominal, histogramToFit),
              'inputFile_mcClosure_%s' % lepton_and_hadTau_type : self.jobOptions_addBackgrounds_sum[key_addBackgrounds_job_fakes]['outputFile'],
              'histogramName_mcClosure_%s' % lepton_and_hadTau_type : "%s/sel/evt/fakes_mc/%s" % (histogramDir_mcClosure, histogramToFit)
            })
          self.createCfg_add_syst_fakerate(self.jobOptions_add_syst_fakerate[key_add_syst_fakerate_job])

    logging.info("Creating configuration files to run 'makePlots'")
    for chargeSumSelection in self.chargeSumSelections:
      if chargeSumSelection != "disabled":
        raise ValueError("Invalid Configuration parameter 'chargeSumSelection' = %s !!" % chargeSumSelection)
      for category in self.categories:
        histogramDir = None
        label = None
        make_plots_backgrounds = None
        if category == "1l_1tau_SS":
          histogramDir = getHistogramDir(self.category_inclusive, "Tight", "disabled", "SS")
          label = "1l+1#tau_{h} SS"
          make_plots_backgrounds = self.make_plots_backgrounds_SS
        elif category == "1l_1tau_OS":
          histogramDir = getHistogramDir(self.category_inclusive, "Tight", "disabled", "OS")
          label = "1l+1#tau_{h} OS"
          make_plots_backgrounds = self.make_plots_backgrounds_OS
        else:
          continue
        key_makePlots_job = getKey(category, chargeSumSelection)
        key_hadd_stage2 = getKey(get_lepton_and_hadTau_selection_and_frWeight("Tight", "disabled"), chargeSumSelection)
        self.jobOptions_make_plots[key_makePlots_job] = {
          'executable' : self.executable_make_plots,
          'inputFile' : self.outputFile_hadd_stage2[key_hadd_stage2],
          'cfgFile_modified' : os.path.join(self.dirs[DKEY_CFGS], "makePlots_%s_%s_cfg.py" % (self.channel, category)),
          'outputFile' : os.path.join(self.dirs[DKEY_PLOT], "makePlots_%s_%s.png" % (self.channel, category)),
          'histogramDir' : histogramDir,
          'label' : label,
          'make_plots_backgrounds' : make_plots_backgrounds
        }
        self.createCfg_makePlots(self.jobOptions_make_plots[key_makePlots_job])
        if "Fakeable_mcClosure" in self.lepton_and_hadTau_selections: #TODO
          key_makePlots_job = getKey(category, "Fakeable_mcClosure", chargeSumSelection)
          key_hadd_stage2 = getKey(get_lepton_and_hadTau_selection_and_frWeight("Tight", "disabled"), chargeSumSelection)
          self.jobOptions_make_plots[key_makePlots_job] = {
            'executable' : self.executable_make_plots_mcClosure,
            'inputFile' : self.outputFile_hadd_stage2[key_hadd_stage2],
            'cfgFile_modified' : os.path.join(self.dirs[DKEY_CFGS], "makePlots_mcClosure_%s_%s_cfg.py" % (self.channel, category)),
            'outputFile' : os.path.join(self.dirs[DKEY_PLOT], "makePlots_mcClosure_%s_%s.png" % (self.channel, category))
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
      logging.info("Creating script for submitting '%s' jobs to batch system" % self.executable_addFlips)
      self.sbatchFile_addFlips = os.path.join(self.dirs[DKEY_SCRIPTS], "sbatch_addFlips_%s.py" % self.channel)
      self.createScript_sbatch(self.executable_addFlips, self.sbatchFile_addFlips, self.jobOptions_addFlips)

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
