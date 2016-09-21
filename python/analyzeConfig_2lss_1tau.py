import logging

from tthAnalysis.HiggsToTauTau.analyzeConfig import *
from tthAnalysis.HiggsToTauTau.jobTools import create_if_not_exists

class analyzeConfig_2lss_1tau(analyzeConfig):
  """Configuration metadata needed to run analysis in a single go.
  
  Sets up a folder structure by defining full path names; no directory creation is delegated here.
  
  Args specific to analyzeConfig_2lss_1tau:
    lepton_selections: either `Tight`, `Loose` or `Fakeable`
    hadTau_selection: either `dR05isoLoose/Medium/Tight` or `dR03mvaMedium/Tight/VTight/VVTight`

  See $CMSSW_BASE/src/tthAnalysis/HiggsToTauTau/python/analyzeConfig.py
  for documentation of further Args.
  
  """
  def __init__(self, outputDir, executable_analyze, samples, lepton_selections, lepton_charge_selections, hadTau_selection, central_or_shifts,
               max_files_per_job, era, use_lumi, lumi, debug, running_method, num_parallel_jobs, 
               executable_addFakes, executable_addFlips, histograms_to_fit, executable_prep_dcard="prepareDatacard"):
    analyzeConfig.__init__(self, outputDir, executable_analyze, "2lss_1tau", central_or_shifts,
      max_files_per_job, era, use_lumi, lumi, debug, running_method, num_parallel_jobs, 
      histograms_to_fit)

    self.samples = samples
    self.prep_dcard_processesToCopy = [ "data_obs", "TTW", "TTZ", "WZ", "Rares", "fakes_data", "flips_data" ]

    self.lepton_selections = lepton_selections
    self.lepton_charge_selections = lepton_charge_selections

    self.hadTau_selection = hadTau_selection

    self.executable_addFakes = executable_addFakes
    self.executable_addFlips = executable_addFlips
    
    for sample_name, sample_info in self.samples.items():
      if not sample_info["use_it"] or sample_info["sample_category"] in [ "additional_signal_overlap", "background_data_estimate" ]:
        continue
      process_name = sample_info["process_name_specific"]
      for lepton_selection in self.lepton_selections:
        for lepton_charge_selection in self.lepton_charge_selections:
          
          key_dir = getKey(sample_name, lepton_selection, lepton_charge_selection)  
          for dir_type in [ DKEY_CFGS, DKEY_HIST, DKEY_LOGS ]:
            initDict(self.dirs, [ key_dir, dir_type ])
            self.dirs[key_dir][dir_type] = os.path.join(self.outputDir, dir_type, self.channel,
              "_".join([ lepton_selection, lepton_charge_selection ]), process_name)
    for dir_type in [ DKEY_DCRD, DKEY_PLOT ]:
      initDict(self.dirs, [ dir_type ])
      self.dirs[dir_type] = os.path.join(self.outputDir, dir_type, self.channel)
    ##print "self.dirs = ", self.dirs

    self.cfgFile_analyze_original = os.path.join(self.workingDir, "analyze_2lss_1tau_cfg.py")
    self.histogramFile_addFakes = os.path.join(self.outputDir, DKEY_HIST, "addBackgroundLeptonFakes_%s.root" % self.channel)
    self.cfgFile_addFakes_original = os.path.join(self.workingDir, "addBackgroundLeptonFakes_cfg.py")
    self.cfgFile_addFakes_modified = os.path.join(self.outputDir, DKEY_CFGS, "addBackgroundLeptonFakes_%s_cfg.py" % self.channel)
    self.histogramFile_addFlips = os.path.join(self.outputDir, DKEY_HIST, "addBackgroundLeptonFlips_%s.root" % self.channel)
    self.cfgFile_addFlips_original = os.path.join(self.workingDir, "addBackgroundLeptonFlips_cfg.py")
    self.cfgFile_addFlips_modified = os.path.join(self.outputDir, DKEY_CFGS, "addBackgroundLeptonFlips_%s_cfg.py" % self.channel)
    self.histogramDir_prep_dcard = "2lss_1tau_SS_Tight"
    self.cfgFile_make_plots_original = os.path.join(self.workingDir, "makePlots_2lss_1tau_cfg.py")
    self.make_plots_backgrounds = [ "TTW", "TTZ", "WZ", "Rares", "fakes_data", "flips_data" ]

  def createCfg_analyze(self, inputFiles, outputFile, sample_category, era, triggers,
                        lepton_selection, lepton_charge_selection, hadTau_selection,
                        is_mc, central_or_shift, lumi_scale, apply_trigger_bits, cfgFile_modified):
    """Create python configuration file for the analyze_2lss_1tau executable (analysis code)

    Args:
      inputFiles: list of input files (Ntuples)
      outputFile: output file of the job -- a ROOT file containing histogram
      process: either `TT`, `TTW`, `TTZ`, `EWK`, `Rares`, `data_obs`, `ttH_hww`, `ttH_hzz` or `ttH_htt`
      is_mc: flag indicating whether job runs on MC (True) or data (False)
      lumi_scale: event weight (= xsection * luminosity / number of events)
      central_or_shift: either 'central' or one of the systematic uncertainties defined in $CMSSW_BASE/src/tthAnalysis/HiggsToTauTau/bin/analyze_2lss_1tau.cc
    """  
    lines = []
    lines.append("process.fwliteInput.fileNames = cms.vstring(%s)" % inputFiles)
    lines.append("process.fwliteOutput.fileName = cms.string('%s')" % outputFile)
    lines.append("process.analyze_2lss_1tau.process = cms.string('%s')" % sample_category)
    lines.append("process.analyze_2lss_1tau.era = cms.string('%s')" % era)
    lines.append("process.analyze_2lss_1tau.use_triggers_1e = cms.bool(%s)" % ("1e" in triggers))
    lines.append("process.analyze_2lss_1tau.use_triggers_2e = cms.bool(%s)" % ("2e" in triggers))
    lines.append("process.analyze_2lss_1tau.use_triggers_1mu = cms.bool(%s)" % ("1mu" in triggers))
    lines.append("process.analyze_2lss_1tau.use_triggers_2mu = cms.bool(%s)" % ("2mu" in triggers))
    lines.append("process.analyze_2lss_1tau.use_triggers_1e1mu = cms.bool(%s)" % ("1e1mu" in triggers))
    lines.append("process.analyze_2lss_1tau.leptonSelection = cms.string('%s')" % lepton_selection)
    lines.append("process.analyze_2lss_1tau.leptonChargeSelection = cms.string('%s')" % lepton_charge_selection)
    lines.append("process.analyze_2lss_1tau.hadTauSelection = cms.string('%s')" % hadTau_selection)
    lines.append("process.analyze_2lss_1tau.isMC = cms.bool(%s)" % is_mc)
    lines.append("process.analyze_2lss_1tau.central_or_shift = cms.string('%s')" % central_or_shift)
    lines.append("process.analyze_2lss_1tau.lumiScale = cms.double(%f)" % lumi_scale)
    lines.append("process.analyze_2lss_1tau.apply_trigger_bits = cms.bool(%s)" % apply_trigger_bits)
    create_cfg(self.cfgFile_analyze_original, cfgFile_modified, lines)

  def createCfg_addFakes(self, inputFile, outputFile, cfgFile_modified):
    """Create python configuration file for the addBackgroundLeptonFakes executable (data-driven estimation of 'Fakes' backgrounds)

    Args:
      inputFiles: input file (the ROOT file produced by hadd_stage1)
      outputFile: output file of the job
    """  
    lines = []
    lines.append("process.fwliteInput.fileNames = cms.vstring('%s')" % inputFile)
    lines.append("process.fwliteOutput.fileName = cms.string('%s')" % outputFile)
    create_cfg(self.cfgFile_addFakes_original, cfgFile_modified, lines)

  def createCfg_addFlips(self, inputFile, outputFile, cfgFile_modified):
    """Create python configuration file for the addBackgroundLeptonFlips executable (data-driven estimation of 'Flips' backgrounds)

    Args:
      inputFiles: input file (the ROOT file produced by hadd_stage1)
      outputFile: output file of the job
    """  
    lines = []
    lines.append("process.fwliteInput.fileNames = cms.vstring('%s')" % inputFile)
    lines.append("process.fwliteOutput.fileName = cms.string('%s')" % outputFile)
    create_cfg(self.cfgFile_addFlips_original, cfgFile_modified, lines)

  def addToMakefile_hadd_stage1(self, lines_makefile):
    inputFiles_hadd_stage1 = []
    for sample_name, sample_info in self.samples.items():
      if not sample_name in self.inputFileIds.keys():
        continue
      process_name = sample_info["process_name_specific"]
      inputFiles_sample = []
      for lepton_selection in self.lepton_selections:
        for lepton_charge_selection in self.lepton_charge_selections:
          for central_or_shift in self.central_or_shifts:
            inputFiles_jobIds = []                  
            for jobId in range(len(self.inputFileIds[sample_name])):
              key_file = getKey(sample_name, lepton_selection, lepton_charge_selection, central_or_shift, jobId)
              if key_file in self.histogramFiles.keys():
                inputFiles_jobIds.append(self.histogramFiles[key_file])
            if len(inputFiles_jobIds) > 0:
              haddFile_jobIds = self.histogramFile_hadd_stage1.replace(".root", "_%s_%s_%s_%s.root" % \
                (process_name, lepton_selection, lepton_charge_selection, central_or_shift))
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

  def addToMakefile_addFakes(self, lines_makefile):
    lines_makefile.append("%s: %s" % (self.histogramFile_addFakes, self.histogramFile_hadd_stage1))
    lines_makefile.append("\t%s %s" % (self.executable_addFakes, self.cfgFile_addFakes_modified))
    lines_makefile.append("")
    self.filesToClean.append(self.histogramFile_addFakes)

  def addToMakefile_addFlips(self, lines_makefile):
    lines_makefile.append("%s: %s" % (self.histogramFile_addFlips, self.histogramFile_hadd_stage1))
    lines_makefile.append("\t%s %s" % (self.executable_addFlips, self.cfgFile_addFlips_modified))
    lines_makefile.append("")
    self.filesToClean.append(self.histogramFile_addFlips)

  def addToMakefile_backgrounds_from_data(self, lines_makefile):
    self.addToMakefile_addFakes(lines_makefile)
    self.addToMakefile_addFlips(lines_makefile)

  def addToMakefile_hadd_stage2(self, lines_makefile):
    """Adds the commands to Makefile that are necessary for building the final histogram file.
    """
    lines_makefile.append("%s: %s" % (self.histogramFile_hadd_stage2, " ".join([ self.histogramFile_hadd_stage1, self.histogramFile_addFakes, self.histogramFile_addFlips ])))
    lines_makefile.append("\t%s %s" % ("rm -f", self.histogramFile_hadd_stage2))
    lines_makefile.append("\t%s %s %s" % ("hadd", self.histogramFile_hadd_stage2, " ".join([ self.histogramFile_hadd_stage1, self.histogramFile_addFakes, self.histogramFile_addFlips ])))
    lines_makefile.append("")
    self.filesToClean.append(self.histogramFile_hadd_stage2)

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

      for lepton_selection in self.lepton_selections:
        for lepton_charge_selection in self.lepton_charge_selections:
          for central_or_shift in self.central_or_shifts:
            for jobId in range(len(self.inputFileIds[sample_name])):
              if central_or_shift != "central" and not (lepton_selection == "Tight" and charge_selection == "SS"):
                continue
              if central_or_shift != "central" and not is_mc:
                continue
              if central_or_shift.startswith("CMS_ttHl_thu_shape_ttH") and sample_category != "signal":
                continue
              if central_or_shift.startswith("CMS_ttHl_thu_shape_ttW") and sample_category != "TTW":
                continue
              if central_or_shift.startswith("CMS_ttHl_thu_shape_ttZ") and sample_category != "TTZ":
                continue
  
              key_dir = getKey(sample_name, lepton_selection, lepton_charge_selection)
              key_file = getKey(sample_name, lepton_selection, lepton_charge_selection, central_or_shift, jobId)

              self.ntupleFiles[key_file] = generate_input_list(self.inputFileIds[sample_name][jobId], secondary_files, primary_store, secondary_store, self.debug)
              self.cfgFiles_analyze_modified[key_file] = os.path.join(self.dirs[key_dir][DKEY_CFGS], "analyze_%s_%s_%s_%s_%s_%i_cfg.py" % \
                (self.channel, process_name, lepton_selection, lepton_charge_selection, central_or_shift, jobId))
              self.histogramFiles[key_file] = os.path.join(self.dirs[key_dir][DKEY_HIST], "%s_%s_%s_%s_%i.root" % \
                (process_name, lepton_selection, lepton_charge_selection, central_or_shift, jobId))
              self.logFiles_analyze[key_file] = os.path.join(self.dirs[key_dir][DKEY_LOGS], "analyze_%s_%s_%s_%s_%s_%i.log" % \
                (self.channel, process_name, lepton_selection, lepton_charge_selection, central_or_shift, jobId))
                
              self.createCfg_analyze(self.ntupleFiles[key_file], self.histogramFiles[key_file], sample_category, self.era, triggers,
                lepton_selection, lepton_charge_selection, self.hadTau_selection,
                is_mc, central_or_shift, lumi_scale, apply_trigger_bits, self.cfgFiles_analyze_modified[key_file])
                
    if self.is_sbatch:
      logging.info("Creating script for submitting '%s' jobs to batch system" % self.executable_analyze)
      self.createScript_sbatch()

    logging.info("Creating configuration files for executing 'addBackgroundLeptonFakes'")
    self.createCfg_addFakes(self.histogramFile_hadd_stage1, self.histogramFile_addFakes, self.cfgFile_addFakes_modified)

    logging.info("Creating configuration files for executing 'addBackgroundLeptonFlips'")
    self.createCfg_addFlips(self.histogramFile_hadd_stage1, self.histogramFile_addFlips, self.cfgFile_addFlips_modified)

    logging.info("Creating configuration files for executing 'prepareDatacards'")
    for histogramToFit in self.histograms_to_fit:
      self.createCfg_prep_dcard(histogramToFit)

    logging.info("Creating configuration files for executing 'makePlots'")
    self.createCfg_makePlots()

    logging.info("Creating Makefile")
    lines_makefile = []
    self.addToMakefile_analyze(lines_makefile)
    self.addToMakefile_hadd_stage1(lines_makefile)
    self.addToMakefile_backgrounds_from_data(lines_makefile)
    self.addToMakefile_hadd_stage2(lines_makefile)
    self.addToMakefile_prep_dcard(lines_makefile)
    self.addToMakefile_make_plots(lines_makefile)
    self.addToMakefile_clean(lines_makefile)
    self.createMakefile(lines_makefile)
  
    logging.info("Done")

