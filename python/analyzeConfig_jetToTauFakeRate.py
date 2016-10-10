import logging

from tthAnalysis.HiggsToTauTau.analyzeConfig import *
from tthAnalysis.HiggsToTauTau.jobTools import create_if_not_exists

class analyzeConfig_jetToTauFakeRate(analyzeConfig):
  """Configuration metadata needed to run analysis in a single go.
  
  Sets up a folder structure by defining full path names; no directory creation is delegated here.
  
  Args specific to analyzeConfig_jetToTauFakeRate:
    charge_selection: either `OS` or `SS` (opposite-sign or same-sign of the electron+muon pair)
    hadTau_selections: list of tau ID discriminators to check

  See $CMSSW_BASE/src/tthAnalysis/HiggsToTauTau/python/analyzeConfig.py
  for documentation of further Args.
  
  """
  def __init__(self, outputDir, executable_analyze, samples, charge_selections,
               jet_minPt, jet_maxPt, jet_minAbsEta, jet_maxAbsEta, hadTau_selections, absEtaBins, ptBins, central_or_shifts,
               max_files_per_job, era, use_lumi, lumi, debug, running_method, num_parallel_jobs,
               executable_comp_jetToTauFakeRate):
    analyzeConfig.__init__(self, outputDir, executable_analyze, "jetToTauFakeRate", central_or_shifts,
      max_files_per_job, era, use_lumi, lumi, debug, running_method, num_parallel_jobs,
      [])

    self.samples = samples

    self.charge_selections = charge_selections

    self.jet_minPt = jet_minPt
    self.jet_maxPt = jet_maxPt
    self.jet_minAbsEta = jet_minAbsEta
    self.jet_maxAbsEta = jet_maxAbsEta

    self.hadTau_selections = hadTau_selections
    
    self.absEtaBins = absEtaBins
    self.ptBins = ptBins

    self.executable_comp_jetToTauFakeRate = executable_comp_jetToTauFakeRate
    
    for sample_name, sample_info in self.samples.items():
      if not sample_info["use_it"] or sample_info["sample_category"] in [ "additional_signal_overlap", "background_data_estimate" ]:
        continue
      process_name = sample_info["process_name_specific"]
      for charge_selection in self.charge_selections:
        key_dir = getKey(sample_name, charge_selection)  
        for dir_type in [ DKEY_CFGS, DKEY_HIST, DKEY_LOGS, DKEY_DCRD ]:
          initDict(self.dirs, [ key_dir, dir_type ])
          self.dirs[key_dir][dir_type] = os.path.join(self.outputDir, dir_type, self.channel,
            "_".join([ charge_selection ]), process_name)
    ##print "self.dirs = ", self.dirs

    self.cfgFile_analyze_original = os.path.join(self.workingDir, "analyze_jetToTauFakeRate_cfg.py")
    self.histogramFile_comp_jetToTauFakeRate = {}
    self.cfgFile_comp_jetToTauFakeRate_original = os.path.join(self.workingDir, "comp_jetToTauFakeRate_cfg.py")
    self.cfgFile_comp_jetToTauFakeRate_modified = {}    
    self.histogramDir_numerator = {}
    self.histogramDir_denominator = {}
    
  def createCfg_analyze(self, inputFiles, outputFile, sample_category, era, triggers, charge_selection,
                        jet_minPt, jet_maxPt, jet_minAbsEta, jet_maxAbsEta, hadTau_selections, absEtaBins,
                        is_mc, central_or_shift, lumi_scale, apply_trigger_bits, cfgFile_modified):
    """Create python configuration file for the analyze_jetToTauFakeRate executable (analysis code)

    Args:
      inputFiles: list of input files (Ntuples)
      outputFile: output file of the job -- a ROOT file containing histogram
      process: either `TT`, `TTW`, `TTZ`, `EWK`, `Rares`, `data_obs`, `ttH_hww`, `ttH_hzz` or `ttH_htt`
      is_mc: flag indicating whether job runs on MC (True) or data (False)
      lumi_scale: event weight (= xsection * luminosity / number of events)
      central_or_shift: either 'central' or one of the systematic uncertainties defined in $CMSSW_BASE/src/tthAnalysis/HiggsToTauTau/bin/analyze_jetToTauFakeRate.cc
    """  
    lines = []
    ##lines.append("process.fwliteInput.fileNames = cms.vstring(%s)" % [ os.path.basename(inputFile) for inputFile in inputFiles ])
    lines.append("process.fwliteInput.fileNames = cms.vstring(%s)" % inputFiles)
    lines.append("process.fwliteOutput.fileName = cms.string('%s')" % os.path.basename(outputFile))
    lines.append("process.analyze_jetToTauFakeRate.process = cms.string('%s')" % sample_category)
    lines.append("process.analyze_jetToTauFakeRate.era = cms.string('%s')" % era)
    lines.append("process.analyze_jetToTauFakeRate.triggers_1e = cms.vstring(%s)" % self.triggers_1e)
    lines.append("process.analyze_jetToTauFakeRate.use_triggers_1e = cms.bool(%s)" % ("1e" in triggers))
    lines.append("process.analyze_jetToTauFakeRate.triggers_1mu = cms.vstring(%s)" % self.triggers_1mu)
    lines.append("process.analyze_jetToTauFakeRate.use_triggers_1mu = cms.bool(%s)" % ("1mu" in triggers))
    lines.append("process.analyze_jetToTauFakeRate.triggers_1e1mu = cms.vstring(%s)" % self.triggers_1e1mu)
    lines.append("process.analyze_jetToTauFakeRate.use_triggers_1e1mu = cms.bool(%s)" % ("1e1mu" in triggers))
    lines.append("process.analyze_jetToTauFakeRate.chargeSelection = cms.string('%s')" % charge_selection)
    lines.append("process.analyze_jetToTauFakeRate.jet_minPt = cms.double('%f')" % jet_minPt)
    lines.append("process.analyze_jetToTauFakeRate.jet_maxPt = cms.double('%f')" % jet_maxPt)
    lines.append("process.analyze_jetToTauFakeRate.jet_minAbsEta = cms.double('%f')" % jet_minAbsEta)
    lines.append("process.analyze_jetToTauFakeRate.jet_maxAbsEta = cms.double('%f')" % jet_maxAbsEta)
    lines.append("process.analyze_jetToTauFakeRate.hadTauSelections = cms.vstring(")
    for hadTau_selection in hadTau_selections:
      lines.append("    '%s'," % hadTau_selection)
    lines.append(")")
    lines.append("process.analyze_jetToTauFakeRate.absEtaBins = cms.vdouble(%s)" % absEtaBins)
    lines.append("process.analyze_jetToTauFakeRate.isMC = cms.bool(%s)" % is_mc)
    lines.append("process.analyze_jetToTauFakeRate.central_or_shift = cms.string('%s')" % central_or_shift)
    lines.append("process.analyze_jetToTauFakeRate.lumiScale = cms.double(%f)" % lumi_scale)
    lines.append("process.analyze_jetToTauFakeRate.apply_trigger_bits = cms.bool(%s)" % apply_trigger_bits)
    create_cfg(self.cfgFile_analyze_original, cfgFile_modified, lines)

  def createCfg_comp_jetToTauFakeRate(self, inputFile, outputFile, looseRegion, tightRegion, absEtaBins, ptBins, cfgFile_modified):
    """Create python configuration file for the comp_jetToTauFakeRate executable

    Args:
      inputFiles: input file (the ROOT file produced by hadd_stage1)
      outputFile: output file of the job
    """
    for charge_selection in self.charge_selections:
      lines = []
      lines.append("process.fwliteInput.fileNames = cms.vstring('%s')" % inputFile)
      lines.append("process.fwliteOutput.fileName = cms.string('%s')" % outputFile)
      lines.append("process.comp_jetToTauFakeRate.looseRegion = cms.string('%s')" % looseRegion)
      lines.append("process.comp_jetToTauFakeRate.tightRegion = cms.string('%s')" % tightRegion)
      lines.append("process.comp_jetToTauFakeRate.processData = cms.string('data_obs')")
      lines.append("process.comp_jetToTauFakeRate.processesToSubtract = cms.vstring(")
      lines.append("    'TTt', 'TTl',")
      lines.append("    'EWKt', 'EWKl',")
      lines.append("    'Rarest', 'Raresl',")      
      lines.append("    'TTWt', 'TTWl', ")
      lines.append("    'TTZt', 'TTZl', ")
      lines.append("    'signalt', 'signall'")
      lines.append(")")
      lines.append("process.comp_jetToTauFakeRate.processMC = cms.string('TTj')")
      lines.append("process.comp_jetToTauFakeRate.absEtaBins = cms.vdouble(%s)" % absEtaBins)
      lines.append("process.comp_jetToTauFakeRate.ptBins = cms.vdouble(%s)" % ptBins)
      create_cfg(self.cfgFile_comp_jetToTauFakeRate_original, cfgFile_modified, lines)

  def addToMakefile_hadd_stage1(self, lines_makefile):
    inputFiles_hadd_stage1 = []
    for sample_name, sample_info in self.samples.items():
      if not sample_name in self.inputFileIds.keys():
        continue
      process_name = sample_info["process_name_specific"]
      inputFiles_sample = []
      for charge_selection in self.charge_selections:
        for central_or_shift in self.central_or_shifts:
          inputFiles_jobIds = []                  
          for jobId in range(len(self.inputFileIds[sample_name])):
            key_file = getKey(sample_name, charge_selection, central_or_shift, jobId)
            if key_file in self.histogramFiles.keys():
              inputFiles_jobIds.append(self.histogramFiles[key_file])
          if len(inputFiles_jobIds) > 0:
            haddFile_jobIds = self.histogramFile_hadd_stage1.replace(".root", "_%s_%s_%s.root" % \
              (process_name, charge_selection, central_or_shift))
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

  def addToMakefile_comp_jetToTauFakeRate(self, lines_makefile):
    for charge_selection in self.charge_selections:
      lines_makefile.append("%s: %s" % (self.histogramFile_comp_jetToTauFakeRate[charge_selection], self.histogramFile_hadd_stage1))
      lines_makefile.append("\t%s %s" % (self.executable_comp_jetToTauFakeRate, self.cfgFile_comp_jetToTauFakeRate_modified[charge_selection]))
      lines_makefile.append("")
      self.filesToClean.append(self.histogramFile_comp_jetToTauFakeRate[charge_selection])

  def addToMakefile_hadd_stage2(self, lines_makefile):
    """Adds the commands to Makefile that are necessary for building the final ROOT file with all histograms and fake-rate graphs.
    """
    inputFiles_hadd_stage2 = [ self.histogramFile_hadd_stage1 ]
    for charge_selection in self.charge_selections:
      inputFiles_hadd_stage2.append(self.histogramFile_comp_jetToTauFakeRate[charge_selection])
    print "inputFiles_hadd_stage2 = ", inputFiles_hadd_stage2
    lines_makefile.append("%s: %s" % (self.histogramFile_hadd_stage2, " ".join(inputFiles_hadd_stage2)))
    lines_makefile.append("\t%s %s" % ("rm -f", self.histogramFile_hadd_stage2))
    lines_makefile.append("\t%s %s %s" % ("hadd", self.histogramFile_hadd_stage2, " ".join(inputFiles_hadd_stage2)))
    lines_makefile.append("")
    self.filesToClean.append(self.histogramFile_hadd_stage2)
    lines_makefile.append("")
    lines_makefile.append("all: %s" % self.histogramFile_hadd_stage2)
    lines_makefile.append("")

  def create(self):
    """Creates all necessary config files and runs the complete analysis workfow -- either locally or on the batch system
    """

    for key in self.dirs.keys():
      for dir_type in self.dirs[key].keys():
        create_if_not_exists(self.dirs[key][dir_type])
  
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

      for charge_selection in self.charge_selections:
        for central_or_shift in self.central_or_shifts:
          for jobId in range(len(self.inputFileIds[sample_name])):
            if central_or_shift != "central" and not is_mc:
              continue
            if central_or_shift.startswith("CMS_ttHl_thu_shape_ttH") and sample_category != "signal":
              continue
            if central_or_shift.startswith("CMS_ttHl_thu_shape_ttW") and sample_category != "TTW":
              continue
            if central_or_shift.startswith("CMS_ttHl_thu_shape_ttZ") and sample_category != "TTZ":
              continue

            key_dir = getKey(sample_name, charge_selection)
            key_file = getKey(sample_name, charge_selection, central_or_shift, jobId)

            self.ntupleFiles[key_file] = generate_input_list(self.inputFileIds[sample_name][jobId], secondary_files, primary_store, secondary_store, self.debug)
            self.cfgFiles_analyze_modified[key_file] = os.path.join(self.dirs[key_dir][DKEY_CFGS], "analyze_%s_%s_%s_%s_%i_cfg.py" % \
              (self.channel, process_name, charge_selection, central_or_shift, jobId))
            self.histogramFiles[key_file] = os.path.join(self.dirs[key_dir][DKEY_HIST], "%s_%s_%s_%i.root" % \
              (process_name, charge_selection, central_or_shift, jobId))
            self.logFiles_analyze[key_file] = os.path.join(self.dirs[key_dir][DKEY_LOGS], "analyze_%s_%s_%s_%s_%i.log" % \
              (self.channel, process_name, charge_selection, central_or_shift, jobId))
                
            self.createCfg_analyze(self.ntupleFiles[key_file], self.histogramFiles[key_file], sample_category, self.era, triggers,
              charge_selection, self.jet_minPt, self.jet_maxPt, self.jet_minAbsEta, self.jet_maxAbsEta, self.hadTau_selections, self.absEtaBins,
              is_mc, central_or_shift, lumi_scale, apply_trigger_bits, self.cfgFiles_analyze_modified[key_file])
                
    if self.is_sbatch:
      logging.info("Creating script for submitting '%s' jobs to batch system" % self.executable_analyze)
      self.createScript_sbatch()

    logging.info("Creating configuration files for executing 'comp_jetToTauFakeRate'")
    for charge_selection in self.charge_selections:
      self.histogramFile_comp_jetToTauFakeRate[charge_selection] = os.path.join(
        self.outputDir, DKEY_HIST, "comp_jetToTauFakeRate_%s.root" % charge_selection)
      self.histogramDir_numerator[charge_selection] = "jetToTauFakeRate_%s/numerator/" % charge_selection
      self.histogramDir_denominator[charge_selection] = "jetToTauFakeRate_%s/denominator/" % charge_selection
      self.cfgFile_comp_jetToTauFakeRate_modified[charge_selection] = os.path.join(
        self.outputDir, DKEY_CFGS, "comp_jetToTauFakeRate_%s_cfg.py" % charge_selection)
      self.createCfg_comp_jetToTauFakeRate(self.histogramFile_hadd_stage1, self.histogramFile_comp_jetToTauFakeRate[charge_selection],
        self.histogramDir_denominator[charge_selection], self.histogramDir_numerator[charge_selection], self.absEtaBins, self.ptBins,
        self.cfgFile_comp_jetToTauFakeRate_modified[charge_selection])

    lines_makefile = []
    self.addToMakefile_analyze(lines_makefile)
    self.addToMakefile_hadd_stage1(lines_makefile)
    self.addToMakefile_comp_jetToTauFakeRate(lines_makefile)
    self.addToMakefile_hadd_stage2(lines_makefile)
    self.addToMakefile_clean(lines_makefile)
    self.createMakefile(lines_makefile)
  
    logging.info("Done")

