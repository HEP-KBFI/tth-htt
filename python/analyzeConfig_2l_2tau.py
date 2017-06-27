import logging

from tthAnalysis.HiggsToTauTau.analyzeConfig import *
from tthAnalysis.HiggsToTauTau.jobTools import create_if_not_exists
from tthAnalysis.HiggsToTauTau.analysisTools import initDict, getKey, create_cfg, createFile, generateInputFileList

def get_hadTau_selection_and_frWeight(hadTau_selection, hadTau_frWeight):
  hadTau_selection_and_frWeight = hadTau_selection
  if hadTau_selection.startswith("Fakeable"):
    if hadTau_frWeight == "enabled":
      hadTau_selection_and_frWeight += "_wFakeRateWeights"
    elif hadTau_frWeight == "disabled":
      hadTau_selection_and_frWeight += "_woFakeRateWeights"
  hadTau_selection_and_frWeight = hadTau_selection_and_frWeight.replace("|", "_")
  return hadTau_selection_and_frWeight

def getHistogramDir(lepton_charge_selection, hadTau_selection, hadTau_frWeight, hadTau_charge_selection):
  hadTau_selection_part1 = hadTau_selection
  if hadTau_selection_part1.find("_") != -1:
    hadTau_selection_part1 = hadTau_selection_part1[:hadTau_selection_part1.find("_")]
  histogramDir = "2l_2tau_lep%s_tau%s_%s" % (lepton_charge_selection, hadTau_charge_selection, hadTau_selection_part1)
  if hadTau_selection_part1.find("Fakeable") != -1:
    if hadTau_frWeight == "enabled":
      histogramDir += "_wFakeRateWeights"
    elif hadTau_frWeight == "disabled":
      histogramDir += "_woFakeRateWeights"
  return histogramDir

class analyzeConfig_2l_2tau(analyzeConfig):
  """Configuration metadata needed to run analysis in a single go.
  
  Sets up a folder structure by defining full path names; no directory creation is delegated here.
  
  Args specific to analyzeConfig_2l_2tau:
    hadTau_selection: either `Tight`, `Loose` or `Fakeable`
    hadTau_charge_selection: either `OS` or `SS` (opposite-sign or same-sign)

  See $CMSSW_BASE/src/tthAnalysis/HiggsToTauTau/python/analyzeConfig.py
  for documentation of further Args.
  
  """
  def __init__(self, configDir, outputDir, executable_analyze, cfgFile_analyze, samples, changeBranchNames, lepton_charge_selections,
               hadTau_selections, hadTau_charge_selections, applyFakeRateWeights, central_or_shifts,
               max_files_per_job, era, use_lumi, lumi, debug, running_method, num_parallel_jobs, 
               executable_addBackgrounds, executable_addBackgroundJetToTauFakes, histograms_to_fit, select_rle_output = False,
               executable_prep_dcard="prepareDatacards", executable_add_syst_dcard = "addSystDatacards",
               select_root_output = False):
    analyzeConfig.__init__(self, configDir, outputDir, executable_analyze, "2l_2tau", central_or_shifts,
      max_files_per_job, era, use_lumi, lumi, debug, running_method, num_parallel_jobs, 
      histograms_to_fit,
      executable_prep_dcard = executable_prep_dcard,
      executable_add_syst_dcard = executable_add_syst_dcard)

    self.samples = samples
    self.changeBranchNames = changeBranchNames

    self.lepton_charge_selections = lepton_charge_selections

    self.hadTau_selections = hadTau_selections
    self.hadTau_charge_selections = hadTau_charge_selections
    self.hadTau_frWeights = [ "enabled", "disabled" ]
    self.hadTau_genMatches = [ "all", "2t0e0m0j", "1t1e0m0j", "1t0e1m0j", "1t0e0m1j", "0t2e0m0j", "0t1e1m0j", "0t1e0m1j", "0t0e2m0j", "0t0e1m1j", "0t0e0m2j" ]
    ##self.hadTau_genMatches = [ "all" ]
    self.hadTau_genMatches_nonfakes = []
    self.hadTau_genMatches_fakes = []
    for  hadTau_genMatch in self.hadTau_genMatches:
      if hadTau_genMatch == "all" and len(self.hadTau_genMatches) > 1:
        continue
      if hadTau_genMatch.endswith("0j"):
        self.hadTau_genMatches_nonfakes.append(hadTau_genMatch)
      else:
        self.hadTau_genMatches_fakes.append(hadTau_genMatch)    
    self.apply_hadTauGenMatching = True

    self.executable_addBackgrounds = executable_addBackgrounds
    self.executable_addFakes = executable_addBackgroundJetToTauFakes
    
    for sample_name, sample_info in self.samples.items():
      if not sample_info["use_it"] or sample_info["sample_category"] in [ "additional_signal_overlap", "background_data_estimate" ]:
        continue
      process_name = sample_info["process_name_specific"]
      for lepton_charge_selection in self.lepton_charge_selections:
        for hadTau_selection in self.hadTau_selections:
          for hadTau_frWeight in self.hadTau_frWeights:
            if hadTau_frWeight == "enabled" and not hadTau_selection.startswith("Fakeable"):
              continue
            hadTau_selection_and_frWeight = get_hadTau_selection_and_frWeight(hadTau_selection, hadTau_frWeight)
            for hadTau_charge_selection in self.hadTau_charge_selections:
              key_dir = getKey(sample_name, lepton_charge_selection, hadTau_selection, hadTau_frWeight, hadTau_charge_selection)  
              for dir_type in [ DKEY_CFGS, DKEY_HIST, DKEY_LOGS ]:
                initDict(self.dirs, [ key_dir, dir_type ])
                self.dirs[key_dir][dir_type] = os.path.join(self.outputDir, dir_type, self.channel,
                  "_".join([ "lep" + lepton_charge_selection, hadTau_selection_and_frWeight, "tau" + hadTau_charge_selection ]), process_name)
    for dir_type in [ DKEY_DCRD, DKEY_PLOT ]:
      initDict(self.dirs, [ dir_type ])
      self.dirs[dir_type] = os.path.join(self.outputDir, dir_type, self.channel)
    ##print "self.dirs = ", self.dirs

    self.nonfake_backgrounds = [ "TT", "TTW", "TTZ", "EWK", "Rares" ]
    
    self.cfgFile_analyze_original = os.path.join(self.workingDir, "analyze_2l_2tau_cfg.py")
    self.cfgFile_addBackgrounds_original = os.path.join(self.workingDir, "addBackgrounds_cfg.py")
    self.cfgFile_addBackgrounds_modified = {}
    self.histogramFile_addBackgrounds = {}
    self.histogramDir_addBackgrounds = {}    
    self.process_output_addBackgrounds = {}            
    self.histogramFile_hadd_stage1_5 = os.path.join(self.outputDir, DKEY_HIST, "histograms_harvested_stage1_5_%s.root" % self.channel)
    self.cfgFile_addFakes_original = os.path.join(self.workingDir, "addBackgroundJetToTauFakes_cfg.py")
    self.cfgFile_addFakes_modified = {}
    self.histogramFile_addFakes = {}
    self.prep_dcard_processesToCopy = [ "data_obs" ] + self.nonfake_backgrounds + [ "fakes_data" ]
    self.histogramDir_prep_dcard = "2l_2tau_lepOS_tauOS_Tight"
    self.histogramDir_prep_dcard_SS = "2l_2tau_lepOS_tauSS_Tight"
    self.make_plots_backgrounds = self.nonfake_backgrounds + [ "fakes_data" ]
    self.cfgFile_make_plots_mcClosure_original = os.path.join(self.workingDir, "makePlots_mcClosure_cfg.py")
    self.cfgFiles_make_plots_mcClosure_modified = []    
    
  def createCfg_analyze(self, inputFiles, outputFile, sample_category, era, triggers,
                        lepton_charge_selection, hadTau_selection, hadTau_genMatch, apply_hadTauGenMatching, hadTau_frWeight, hadTau_charge_selection,
                        is_mc, central_or_shift, lumi_scale, apply_trigger_bits, cfgFile_modified):
    """Create python configuration file for the analyze_2l_2tau executable (analysis code)

    Args:
      inputFiles: list of input files (Ntuples)
      outputFile: output file of the job -- a ROOT file containing histogram
      process: either `TT`, `TTW`, `TTZ`, `EWK`, `Rares`, `data_obs`, `ttH_hww`, `ttH_hzz` or `ttH_htt`
      is_mc: flag indicating whether job runs on MC (True) or data (False)
      lumi_scale: event weight (= xsection * luminosity / number of events)
      central_or_shift: either 'central' or one of the systematic uncertainties defined in $CMSSW_BASE/src/tthAnalysis/HiggsToTauTau/bin/analyze_2l_2tau.cc
    """  
    lines = []
    ##lines.append("process.fwliteInput.fileNames = cms.vstring(%s)" % [ os.path.basename(inputFile) for inputFile in inputFiles ])
    lines.append("process.fwliteInput.fileNames = cms.vstring(%s)" % inputFiles)
    lines.append("process.fwliteOutput.fileName = cms.string('%s')" % os.path.basename(outputFile))
    lines.append("process.analyze_2l_2tau.process = cms.string('%s')" % sample_category)
    histogramDir = getHistogramDir(lepton_charge_selection, hadTau_selection, hadTau_frWeight, hadTau_charge_selection)
    lines.append("process.analyze_2l_2tau.histogramDir = cms.string('%s')" % histogramDir)
    lines.append("process.analyze_2l_2tau.era = cms.string('%s')" % era)
    lines.append("process.analyze_2l_2tau.triggers_1e = cms.vstring(%s)" % self.triggers_1e)
    lines.append("process.analyze_2l_2tau.use_triggers_1e = cms.bool(%s)" % ("1e" in triggers))
    lines.append("process.analyze_2l_2tau.triggers_2e = cms.vstring(%s)" % self.triggers_2e)
    lines.append("process.analyze_2l_2tau.use_triggers_2e = cms.bool(%s)" % ("2e" in triggers))
    lines.append("process.analyze_2l_2tau.triggers_1mu = cms.vstring(%s)" % self.triggers_1mu)
    lines.append("process.analyze_2l_2tau.use_triggers_1mu = cms.bool(%s)" % ("1mu" in triggers))
    lines.append("process.analyze_2l_2tau.triggers_2mu = cms.vstring(%s)" % self.triggers_2mu)
    lines.append("process.analyze_2l_2tau.use_triggers_2mu = cms.bool(%s)" % ("2mu" in triggers))
    lines.append("process.analyze_2l_2tau.triggers_1e1mu = cms.vstring(%s)" % self.triggers_1e1mu)
    lines.append("process.analyze_2l_2tau.use_triggers_1e1mu = cms.bool(%s)" % ("1e1mu" in triggers))
    lines.append("process.analyze_2l_2tau.leptonChargeSelection = cms.string('%s')" % lepton_charge_selection)
    lines.append("process.analyze_2l_2tau.hadTauChargeSelection = cms.string('%s')" % hadTau_charge_selection)
    lines.append("process.analyze_2l_2tau.hadTauSelection = cms.string('%s')" % hadTau_selection)
    lines.append("process.analyze_2l_2tau.hadTauGenMatch = cms.string('%s')" % hadTau_genMatch)
    lines.append("process.analyze_2l_2tau.apply_hadTauGenMatching = cms.bool(%s)" % apply_hadTauGenMatching)
    if hadTau_frWeight == "enabled":
      lines.append("process.analyze_2l_2tau.applyJetToTauFakeRateWeight = cms.bool(True)")
      if era == "2015":
        lines.append("process.analyze_2l_2tau.jetToTauFakeRateWeight.inputFileName = cms.string('tthAnalysis/HiggsToTauTau/data/FR_tau_2015.root')")
        # CV: use data/MC corrections determined for dR03mvaLoose discriminator,
        #     as the event statistics in 2015 data is too low to determine data/MC corrections for tighter working-points
        graphName = "jetToTauFakeRate/dR03mvaLoose/$etaBin/jetToTauFakeRate_mc_hadTaus_pt"
        fitFunctionName = "jetToTauFakeRate/dR03mvaLoose/$etaBin/fitFunction_data_div_mc_hadTaus_pt"
        lines.append("process.analyze_2l_2tau.jetToTauFakeRateWeight.lead.graphName = cms.string('%s')" % graphName)
        lines.append("process.analyze_2l_2tau.jetToTauFakeRateWeight.lead.fitFunctionName = cms.string('%s')" % fitFunctionName)
        lines.append("process.analyze_2l_2tau.jetToTauFakeRateWeight.sublead.graphName = cms.string('%s')" % graphName)
        lines.append("process.analyze_2l_2tau.jetToTauFakeRateWeight.sublead.fitFunctionName = cms.string('%s')" % fitFunctionName)
      elif era == "2016":
        lines.append("process.analyze_2l_2tau.jetToTauFakeRateWeight.inputFileName = cms.string('tthAnalysis/HiggsToTauTau/data/FR_tau_2016.root')")
      else:
        raise ValueError("Invalid parameter 'era' = %s !!" % era)
    elif hadTau_frWeight == "disabled":
      lines.append("process.analyze_2l_2tau.applyJetToTauFakeRateWeight = cms.bool(False)")
    else:
      raise ValueError("Invalid parameter 'hadTau_frWeight' = %s !!" % hadTau_frWeight)
    if hadTau_selection.find("mcClosure") != -1:
      lines.append("process.analyze_2l_2tau.jetToTauFakeRateWeight.applyFitFunction_lead = cms.bool(False)")
      lines.append("process.analyze_2l_2tau.jetToTauFakeRateWeight.applyFitFunction_sublead = cms.bool(False)")
    lines.append("process.analyze_2l_2tau.isMC = cms.bool(%s)" % is_mc)
    lines.append("process.analyze_2l_2tau.central_or_shift = cms.string('%s')" % central_or_shift)
    lines.append("process.analyze_2l_2tau.lumiScale = cms.double(%f)" % lumi_scale)
    lines.append("process.analyze_2l_2tau.apply_trigger_bits = cms.bool(%s)" % apply_trigger_bits)
    create_cfg(self.cfgFile_analyze_original, cfgFile_modified, lines)

  def createCfg_addBackgrounds(self, inputFile, outputFile, cfgFile_modified, categories, processes_input, process_output):
    """Create python configuration file for the addBackgroundLeptonFakes executable (data-driven estimation of 'Fakes' backgrounds)

    Args:
      inputFiles: input file (the ROOT file produced by hadd_stage1)
      outputFile: output file of the job
    """  
    lines = []
    lines.append("process.fwliteInput.fileNames = cms.vstring('%s')" % inputFile)
    lines.append("process.fwliteOutput.fileName = cms.string('%s')" % outputFile)
    lines.append("process.addBackgrounds.categories = cms.vstring(%s)" % categories)
    lines.append("process.addBackgrounds.processes_input = cms.vstring(%s)" % processes_input)
    lines.append("process.addBackgrounds.process_output = cms.string('%s')" % process_output)
    create_cfg(self.cfgFile_addBackgrounds_original, cfgFile_modified, lines)
    
  def createCfg_addFakes(self, inputFile, outputFile, cfgFile_modified, category_signal, category_sideband):
    """Create python configuration file for the addBackgroundLeptonFakes executable (data-driven estimation of 'Fakes' backgrounds)

    Args:
      inputFiles: input file (the ROOT file produced by hadd_stage1)
      outputFile: output file of the job
    """  
    lines = []
    lines.append("process.fwliteInput.fileNames = cms.vstring('%s')" % inputFile)
    lines.append("process.fwliteOutput.fileName = cms.string('%s')" % outputFile)
    lines.append("process.addBackgroundLeptonFakes.categories = cms.VPSet(")
    lines.append("    cms.PSet(")
    lines.append("        signal = cms.string('%s')," % category_signal) 
    lines.append("        sideband = cms.string('%s')" % category_sideband)
    lines.append("    )")
    lines.append(")")
    lines.append("process.addBackgroundLeptonFakes.processesToSubtract = cms.vstring(%s)" % self.nonfake_backgrounds)
    create_cfg(self.cfgFile_addFakes_original, cfgFile_modified, lines)

  def createCfg_makePlots_mcClosure(self):
    """Fills the template of python configuration file for making control plots

    Args:
      histogramFile: name of the input ROOT file 
    """
    lines = []
    lines.append("process.fwliteInput.fileNames = cms.vstring('%s')" % self.histogramFile_hadd_stage2)
    lines.append("process.makePlots_mcClosure.outputFileName = cms.string('%s')" % os.path.join(self.outputDir, DKEY_PLOT, self.channel, "makePlots_mcClosure_%s.png" % self.channel))
    lines.append("process.makePlots_mcClosure.processesBackground = cms.vstring(%s)" % self.make_plots_backgrounds)
    lines.append("process.makePlots_mcClosure.processSignal = cms.string('%s')" % self.make_plots_signal)
    lines.append("process.makePlots_mcClosure.categories = cms.VPSet(")
    lines.append("  cms.PSet(")
    lines.append("    signal = cms.string('%s')," % self.histogramDir_prep_dcard)
    lines.append("    sideband = cms.string('%s')," % self.histogramDir_prep_dcard.replace("Tight", "Fakeable_wFakeRateWeights"))
    lines.append("    label = cms.string('%s')" % self.channel)
    lines.append("  )")
    lines.append(")")
    lines.append("process.makePlots_mcClosure.distributions = cms.VPSet(")
    lines.append("  cms.PSet(")
    lines.append("    histogramName = cms.string('sel/evt/$PROCESS/numJets'),")
    lines.append("    xAxisTitle = cms.string('jet Multiplicity'),")
    lines.append("    yAxisTitle = cms.string('N')")
    lines.append("  ),")
    lines.append("  cms.PSet(")
    lines.append("    histogramName = cms.string('sel/evt/$PROCESS/mTauTauVis'),")
    lines.append("    xAxisTitle = cms.string('m_{#tau#tau}^{vis} [GeV]'),")
    lines.append("    yAxisTitle = cms.string('dN/dm_{#tau#tau}^{vis} [1/GeV]')")
    lines.append("  )")
    lines.append(")")
    cfgFile_modified = os.path.join(self.outputDir, DKEY_CFGS, "makePlots_mcClosure_%s_cfg.py" % self.channel)
    create_cfg(self.cfgFile_make_plots_original, cfgFile_modified, lines)
    self.cfgFiles_make_plots_mcClosure_modified.append(cfgFile_modified)
    
  def addToMakefile_hadd_stage1(self, lines_makefile):
    inputFiles_hadd_stage1 = []
    for sample_name, sample_info in self.samples.items():
      if not sample_name in self.inputFileIds.keys():
        continue
      process_name = sample_info["process_name_specific"]
      inputFiles_sample = []
      for lepton_charge_selection in self.lepton_charge_selections:
        for hadTau_selection in self.hadTau_selections:
          for hadTau_frWeight in [ "enabled", "disabled" ]:
            hadTau_selection_and_frWeight = get_hadTau_selection_and_frWeight(hadTau_selection, hadTau_frWeight)
            for hadTau_genMatch in self.hadTau_genMatches:
              for hadTau_charge_selection in self.hadTau_charge_selections:
                for central_or_shift in self.central_or_shifts:
                  inputFiles_jobIds = []                  
                  for jobId in range(len(self.inputFileIds[sample_name])):
                    key_file = getKey(sample_name, lepton_charge_selection, hadTau_selection, hadTau_frWeight, hadTau_genMatch, hadTau_charge_selection, central_or_shift, jobId)
                    if key_file in self.histogramFiles.keys():
                      inputFiles_jobIds.append(self.histogramFiles[key_file])
                  if len(inputFiles_jobIds) > 0:
                    haddFile_jobIds = self.histogramFile_hadd_stage1.replace(".root", "_%s_%s_%s_%s_%s_%s.root" % \
                      (process_name, lepton_charge_selection, hadTau_selection_and_frWeight, hadTau_genMatch, hadTau_charge_selection, central_or_shift))
                    lines_makefile.append("%s: %s" % (haddFile_jobIds, " ".join(inputFiles_jobIds)))
                    lines_makefile.append("\t%s %s" % ("rm -f", haddFile_jobIds))
                    lines_makefile.append("\t%s %s %s" % ("hadd", haddFile_jobIds, " ".join(inputFiles_jobIds)))
                    lines_makefile.append("")
                    inputFiles_sample.append(haddFile_jobIds)
                    self.filesToClean.append(haddFile_jobIds)
      if len(inputFiles_sample) > 0:
        haddFile_sample = self.histogramFile_hadd_stage1.replace(".root", "_%s.root" % process_name)
        lines_makefile.append("%s: %s" % (haddFile_sample, " ".join(inputFiles_sample)))
        lines_makefile.append("\t%s %s" % ("rm -f", haddFile_sample))
        lines_makefile.append("\t%s %s %s" % ("hadd", haddFile_sample, " ".join(inputFiles_sample)))
        lines_makefile.append("")
        inputFiles_hadd_stage1.append(haddFile_sample)
        self.filesToClean.append(haddFile_sample)
    lines_makefile.append("%s: %s" % (self.histogramFile_hadd_stage1, " ".join(inputFiles_hadd_stage1)))
    lines_makefile.append("\t%s %s" % ("rm -f", self.histogramFile_hadd_stage1))
    lines_makefile.append("\t%s %s %s" % ("hadd", self.histogramFile_hadd_stage1, " ".join(inputFiles_hadd_stage1)))
    lines_makefile.append("")
    self.filesToClean.append(self.histogramFile_hadd_stage1)

  def addToMakefile_addBackgrounds(self, lines_makefile):
    for key in self.histogramFile_addBackgrounds.keys():
      lines_makefile.append("%s: %s" % (self.histogramFile_addBackgrounds[key], self.histogramFile_hadd_stage1))
      lines_makefile.append("\t%s %s" % (self.executable_addBackgrounds, self.cfgFile_addBackgrounds_modified[key]))
      lines_makefile.append("")
      self.filesToClean.append(self.histogramFile_addBackgrounds[key])

  def addToMakefile_hadd_stage1_5(self, lines_makefile):
    """Adds the commands to Makefile that are necessary for building the final histogram file.
       Default implementation is a dummy and assumes that 'addToMakefile_backgrounds_from_data' method does not actually add any histograms,
       so that the hadd stage2 file is simply a copy of the hadd stage1 file.
    """
    inputFiles_hadd_stage1_5 = [ self.histogramFile_hadd_stage1 ]
    for key in self.histogramFile_addBackgrounds.keys():
      inputFiles_hadd_stage1_5.append(self.histogramFile_addBackgrounds[key])
    lines_makefile.append("%s: %s" % (self.histogramFile_hadd_stage1_5, " ".join(inputFiles_hadd_stage1_5)))
    lines_makefile.append("\t%s %s" % ("rm -f", self.histogramFile_hadd_stage1_5))
    lines_makefile.append("\t%s %s %s" % ("hadd", self.histogramFile_hadd_stage1_5, " ".join(inputFiles_hadd_stage1_5)))
    lines_makefile.append("")
    
  def addToMakefile_addFakes(self, lines_makefile):
    for key in self.histogramFile_addFakes.keys():
      lines_makefile.append("%s: %s" % (self.histogramFile_addFakes[key], self.histogramFile_hadd_stage1_5))
      lines_makefile.append("\t%s %s" % (self.executable_addFakes, self.cfgFile_addFakes_modified[key]))
      lines_makefile.append("")
      self.filesToClean.append(self.histogramFile_addFakes[key])

  def addToMakefile_backgrounds_from_data(self, lines_makefile):
    self.addToMakefile_addBackgrounds(lines_makefile)
    self.addToMakefile_hadd_stage1_5(lines_makefile)
    self.addToMakefile_addFakes(lines_makefile)

  def addToMakefile_hadd_stage2(self, lines_makefile):
    """Adds the commands to Makefile that are necessary for building the final histogram file.
    """
    lines_makefile.append("%s: %s" % (self.histogramFile_hadd_stage2, " ".join([ self.histogramFile_hadd_stage1_5 ] + self.histogramFile_addFakes.values())))
    lines_makefile.append("\t%s %s" % ("rm -f", self.histogramFile_hadd_stage2))
    lines_makefile.append("\t%s %s %s" % ("hadd", self.histogramFile_hadd_stage2, " ".join([ self.histogramFile_hadd_stage1_5 ] + self.histogramFile_addFakes.values())))
    lines_makefile.append("")
    self.filesToClean.append(self.histogramFile_hadd_stage2)

  def addToMakefile_make_plots_mcClosure(self, lines_makefile):
    """Adds the commands to Makefile that are necessary for making control plots of the jet->tau fake background estimation procedure.
    """
    for idxJob, cfgFile_modified in enumerate(self.cfgFiles_make_plots_mcClosure_modified):
      lines_makefile.append("makePlots_mcClosure%i: %s" % (idxJob, self.histogramFile_hadd_stage2))
      lines_makefile.append("\t%s %s" % (self.executable_make_plots, cfgFile_modified))
      lines_makefile.append("")
    
  def create(self):
    """Creates all necessary config files and runs the complete analysis workfow -- either locally or on the batch system
    """

    for key in self.dirs.keys():
      if type(self.dirs[key]) == dict:
        for dir_type in self.dirs[key].keys():
          create_if_not_exists(self.dirs[key][dir_type])
      else:
        create_if_not_exists(self.dirs[key])
  
    self.inputFileIds = {}
    for sample_name, sample_info in self.samples.items():
      if not sample_info["use_it"] or sample_info["sample_category"] in [ "additional_signal_overlap", "background_data_estimate" ]:
        continue

      process_name = sample_info["process_name_specific"]

      logging.info("Creating configuration files to run '%s' for sample %s" % (self.executable_analyze, process_name))  

      ( secondary_files, primary_store, secondary_store ) = self.initializeInputFileIds(sample_name, sample_info)

      is_mc = (sample_info["type"] == "mc")
      lumi_scale = 1. if not (self.use_lumi and is_mc) else sample_info["xsection"] * self.lumi / sample_info["nof_events"]
      sample_category = sample_info["sample_category"]
      triggers = sample_info["triggers"]
      apply_trigger_bits = (is_mc and (self.era == "2015" or (self.era == "2016" and sample_info["reHLT"]))) or not is_mc

      for lepton_charge_selection in self.lepton_charge_selections:
        for hadTau_selection in self.hadTau_selections:
          for hadTau_frWeight in [ "enabled", "disabled" ]:
            if hadTau_frWeight == "enabled" and not hadTau_selection.startswith("Fakeable"):
              continue
            hadTau_selection_and_frWeight = get_hadTau_selection_and_frWeight(hadTau_selection, hadTau_frWeight)
            for hadTau_genMatch in self.hadTau_genMatches:
              for hadTau_charge_selection in self.hadTau_charge_selections:
                for central_or_shift in self.central_or_shifts:
                  for jobId in range(len(self.inputFileIds[sample_name])):
                    if hadTau_genMatch != "all" and not is_mc:
                      continue
                    if hadTau_genMatch == "all" and is_mc:
                      continue
                    if central_or_shift != "central" and not (hadTau_selection.startswith("Tight") and hadTau_charge_selection == "OS"):
                      continue
                    if central_or_shift != "central" and not is_mc:
                      continue
                    if hadTau_selection == "Fakeable_mcClosure" and not hadTau_frWeight == "enabled":
                      continue
                    if central_or_shift.startswith("CMS_ttHl_thu_shape_ttH") and sample_category != "signal":
                      continue
                    if central_or_shift.startswith("CMS_ttHl_thu_shape_ttW") and sample_category != "TTW":
                      continue
                    if central_or_shift.startswith("CMS_ttHl_thu_shape_ttZ") and sample_category != "TTZ":
                      continue
                    sample_category_and_genMatch = sample_category + hadTau_genMatch

                    key_dir = getKey(sample_name, lepton_charge_selection, hadTau_selection, hadTau_frWeight, hadTau_charge_selection)
                    key_file = getKey(sample_name, lepton_charge_selection, hadTau_selection, hadTau_frWeight, hadTau_genMatch, hadTau_charge_selection, central_or_shift, jobId)

                    self.ntupleFiles[key_file] = generate_input_list(self.inputFileIds[sample_name][jobId], secondary_files, primary_store, secondary_store, self.debug)
                    self.cfgFiles_analyze_modified[key_file] = os.path.join(self.dirs[key_dir][DKEY_CFGS], "analyze_%s_%s_%s_%s_%s_%s_%s_%i_cfg.py" % \
                      (self.channel, process_name, lepton_charge_selection, hadTau_selection_and_frWeight, hadTau_genMatch, hadTau_charge_selection, central_or_shift, jobId))
                    self.histogramFiles[key_file] = os.path.join(self.dirs[key_dir][DKEY_HIST], "%s_%s_%s_%s_%s_%s_%i.root" % \
                      (process_name, lepton_charge_selection, hadTau_selection_and_frWeight, hadTau_genMatch, hadTau_charge_selection, central_or_shift, jobId))
                    self.logFiles_analyze[key_file] = os.path.join(self.dirs[key_dir][DKEY_LOGS], "analyze_%s_%s_%s_%s_%s_%s_%s_%i.log" % \
                      (self.channel, process_name, lepton_charge_selection, hadTau_selection_and_frWeight, hadTau_genMatch, hadTau_charge_selection, central_or_shift, jobId))

                    self.createCfg_analyze(self.ntupleFiles[key_file], self.histogramFiles[key_file], sample_category, self.era, triggers,
                      lepton_charge_selection, hadTau_selection, hadTau_genMatch, self.apply_hadTauGenMatching, hadTau_frWeight, hadTau_charge_selection,
                      is_mc, central_or_shift, lumi_scale, apply_trigger_bits, self.cfgFiles_analyze_modified[key_file])
                
    if self.is_sbatch:
      logging.info("Creating script for submitting '%s' jobs to batch system" % self.executable_analyze)
      self.createScript_sbatch()

    logging.info("Creating configuration files for executing 'addBackgrounds'")  
    process_names = []
    process_names.extend(self.nonfake_backgrounds)
    process_names.extend([ "signal", "ttH_htt", "ttH_hww", "ttH_hzz" ])
    # sum non-fake contributions for each MC sample separately
    # input processes: TT2t0e0m0j, TT1t1e0m0j, TT1t0e1m0j", TT0t2e0m0j, TT0t1e1m0j, TT0t0e2m0j; TTW2t0e0m0j,...
    # output processes: TT; ...
    for process_name in process_names:
      for lepton_charge_selection in self.lepton_charge_selections:
        for hadTau_selection in self.hadTau_selections:
          for hadTau_frWeight in self.hadTau_frWeights:
            if hadTau_frWeight == "enabled" and not hadTau_selection.startswith("Fakeable"):
              continue
            hadTau_selection_and_frWeight = get_hadTau_selection_and_frWeight(hadTau_selection, hadTau_frWeight)
            for hadTau_charge_selection in self.hadTau_charge_selections:
              key = getKey(process_name, hadTau_selection, hadTau_frWeight, hadTau_charge_selection)
              self.histogramFile_addBackgrounds[key] = os.path.join(self.outputDir, DKEY_HIST, "addBackgrounds_%s_%s_%s_%s_%s.root" % \
                (self.channel, process_name, lepton_charge_selection, hadTau_selection_and_frWeight, hadTau_charge_selection))        
              self.cfgFile_addBackgrounds_modified[key] = os.path.join(self.outputDir, DKEY_CFGS, "addBackgrounds_%s_%s_%s_%s_%s_cfg.py" % \
                (self.channel, process_name, lepton_charge_selection, hadTau_selection_and_frWeight, hadTau_charge_selection))
              histogramDir = getHistogramDir(lepton_charge_selection, hadTau_selection, hadTau_frWeight, hadTau_charge_selection)
              processes_input = [ "%s%s" % (process_name, genMatch) for genMatch in self.hadTau_genMatches_nonfakes ]
              self.process_output_addBackgrounds[key] = process_name
              self.createCfg_addBackgrounds(self.histogramFile_hadd_stage1, self.histogramFile_addBackgrounds[key], self.cfgFile_addBackgrounds_modified[key],
              [ histogramDir ], processes_input, self.process_output_addBackgrounds[key])
    # sum fake contributions for the total of all MC sample
    # input processes: TT1t0e0m1j, TT0t1e0m1j, TT0t0e1m1j, TT0t0e0m2j; TTW1t0e0m1j,...
    # output process: fakes_mc
    for lepton_charge_selection in self.lepton_charge_selections:
      for hadTau_selection in self.hadTau_selections:
        for hadTau_frWeight in self.hadTau_frWeights:
          if hadTau_frWeight == "enabled" and not hadTau_selection.startswith("Fakeable"):
            continue
          hadTau_selection_and_frWeight = get_hadTau_selection_and_frWeight(hadTau_selection, hadTau_frWeight)
          for hadTau_charge_selection in self.hadTau_charge_selections:
            key = getKey(lepton_charge_selection, hadTau_selection, hadTau_frWeight, hadTau_charge_selection)
            self.histogramFile_addBackgrounds[key] = os.path.join(self.outputDir, DKEY_HIST, "addBackgrounds_%s_fakes_mc_%s_%s_%s.root" % \
              (self.channel, lepton_charge_selection, hadTau_selection_and_frWeight, hadTau_charge_selection))
            self.cfgFile_addBackgrounds_modified[key] = os.path.join(self.outputDir, DKEY_CFGS, "addBackgrounds_%s_fakes_mc_%s_%s_%s_cfg.py" % \
              (self.channel, lepton_charge_selection, hadTau_selection_and_frWeight, hadTau_charge_selection))
            histogramDir = getHistogramDir(lepton_charge_selection, hadTau_selection, hadTau_frWeight, hadTau_charge_selection)
            processes_input = []
            for process_name in self.nonfake_backgrounds:
              for genMatch in self.hadTau_genMatches_fakes:
                processes_input.append("%s%s" % (process_name, genMatch))
            self.process_output_addBackgrounds[key] = "fakes_mc"
            self.createCfg_addBackgrounds(self.histogramFile_hadd_stage1, self.histogramFile_addBackgrounds[key], self.cfgFile_addBackgrounds_modified[key],
              [ histogramDir ], processes_input, self.process_output_addBackgrounds[key])    
        
    logging.info("Creating configuration files for executing 'addBackgroundFakes'")
    for hadTau_charge_selection in self.hadTau_charge_selections:
      key = getKey("fakes_data", hadTau_charge_selection) 
      self.histogramFile_addFakes[key] = os.path.join(self.outputDir, DKEY_HIST, "addBackgroundJetToTauFakes_%s_%s.root" % \
        (self.channel, hadTau_charge_selection))
      self.cfgFile_addFakes_modified[key] = os.path.join(self.outputDir, DKEY_CFGS, "addBackgroundJetToTauFakes_%s_%s_cfg.py" % \
        (self.channel, hadTau_charge_selection))
      category_signal = "2l_2tau_lepOS_tau%s_Tight" % hadTau_charge_selection
      category_sideband = "2l_2tau_lepOS_tau%s_Fakeable_wFakeRateWeights" % hadTau_charge_selection
      self.createCfg_addFakes(self.histogramFile_hadd_stage1_5, self.histogramFile_addFakes[key], self.cfgFile_addFakes_modified[key],
        category_signal, category_sideband)  
      
    logging.info("Creating configuration files for executing 'prepareDatacards'")
    for histogramToFit in self.histograms_to_fit:
      self.createCfg_prep_dcard(histogramToFit)
      if "SS" in self.hadTau_charge_selections:
        self.createCfg_prep_dcard(histogramToFit, self.histogramDir_prep_dcard_SS, "SS")

    logging.info("Creating configuration files for executing 'makePlots'")
    self.createCfg_makePlots()
    if "SS" in self.hadTau_charge_selections:
      self.createCfg_makePlots(self.histogramDir_prep_dcard_SS, "SS")
    if "Fakeable_mcClosure" in self.hadTau_selections:
      self.createCfg_makePlots_mcClosure() 

    logging.info("Creating Makefile")
    lines_makefile = []
    self.addToMakefile_analyze(lines_makefile)
    self.addToMakefile_hadd_stage1(lines_makefile)
    self.addToMakefile_backgrounds_from_data(lines_makefile)
    self.addToMakefile_hadd_stage2(lines_makefile)
    self.addToMakefile_prep_dcard(lines_makefile)
    self.addToMakefile_make_plots(lines_makefile)
    self.addToMakefile_make_plots_mcClosure(lines_makefile) 
    self.addToMakefile_clean(lines_makefile)
    self.createMakefile(lines_makefile)
  
    logging.info("Done")

