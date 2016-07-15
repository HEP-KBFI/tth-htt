import logging

from tthAnalysis.HiggsToTauTau.analyzeConfig import *
import tthAnalyzeSamples_1l_2tau
from tthAnalysis.HiggsToTauTau.jobTools import create_if_not_exists

def get_hadTau_selection_and_frWeight(hadTau_selection, hadTau_frWeight):
  hadTau_selection_and_frWeight = hadTau_selection
  if hadTau_selection == "Fakeable":
    if hadTau_frWeight == "enabled":
      hadTau_selection_and_frWeight += "_wFakeRateWeights"
    elif hadTau_frWeight == "disabled":
      hadTau_selection_and_frWeight += "_woFakeRateWeights"
  return hadTau_selection_and_frWeight

class analyzeConfig_1l_2tau(analyzeConfig):
  """Configuration metadata needed to run analysis in a single go.
  
  Sets up a folder structure by defining full path names; no directory creation is delegated here.
  
  Args specific to analyzeConfig_1l_2tau:
    hadTau_selection: either `Tight`, `Loose` or `Fakeable`
    hadTau_charge_selection: either `OS` or `SS` (opposite-sign or same-sign)

  See $CMSSW_BASE/src/tthAnalysis/HiggsToTauTau/python/analyzeConfig.py
  for documentation of further Args.
  
  """
  def __init__(self, outputDir, executable_analyze, hadTau_selections, hadTau_charge_selections, central_or_shifts,
               max_files_per_job, use_lumi, lumi, debug, running_method, num_parallel_jobs, 
               histograms_to_fit, executable_prep_dcard="prepareDatacard"):
    analyzeConfig.__init__(self, outputDir, executable_analyze, "1l_2tau", central_or_shifts,
      max_files_per_job, use_lumi, lumi, debug, running_method, num_parallel_jobs, 
      histograms_to_fit)

    self.samples = tthAnalyzeSamples_1l_2tau.samples

    self.hadTau_selections = hadTau_selections
    self.hadTau_charge_selections = hadTau_charge_selections
    self.hadTau_frWeights = [ "enabled", "disabled" ]
    self.hadTau_genMatches = [ "lepton", "hadTau", "jet", "all" ]
    self.hadTau_genMatches = [ "all" ]

    for sample_name, sample_info in self.samples.items():
      if not sample_info["use_it"] or sample_info["sample_category"] in [ "additional_signal_overlap", "background_data_estimate" ]:
        continue
      process_name = sample_info["process_name_specific"]
      for hadTau_selection in self.hadTau_selections:
        for hadTau_frWeight in self.hadTau_frWeights:
          if hadTau_frWeight == "enabled" and hadTau_selection != "Fakeable":
            continue
          hadTau_selection_and_frWeight = get_hadTau_selection_and_frWeight(hadTau_selection, hadTau_frWeight)
          for hadTau_charge_selection in self.hadTau_charge_selections:
            key_dir = getKey(sample_name, hadTau_selection, hadTau_frWeight, hadTau_charge_selection)  
            for dir_type in [ DKEY_CFGS, DKEY_HIST, DKEY_LOGS, DKEY_DCRD ]:
              initDict(self.dirs, [ key_dir, dir_type ])
              self.dirs[key_dir][dir_type] = os.path.join(self.outputDir, dir_type, self.channel, "_".join([ hadTau_selection_and_frWeight, hadTau_charge_selection ]), process_name)
    print "self.dirs = ", self.dirs

    self.cfgFile_analyze_original = os.path.join(self.workingDir, "analyze_1l_2tau_cfg.py")
    self.histogramDir_prep_dcard = "1l_2tau_OS_Tight"

  def createCfg_analyze(self, inputFiles, outputFile, sample_category, triggers, hadTau_selection, hadTau_genMatch, hadTau_frWeight, hadTau_charge_selection,
                        is_mc, central_or_shift, lumi_scale, cfgFile_modified):
    """Create python configuration file for the analyze_1l_2tau exectuable (analysis code)

    Args:
      inputFiles: list of input files (Ntuples)
      outputFile: output file of the job -- a ROOT file containing histogram
      process: either `TT`, `TTW`, `TTZ`, `EWK`, `Rares`, `data_obs`, `ttH_hww`, `ttH_hzz` or `ttH_htt`
      is_mc: flag indicating whether job runs on MC (True) or data (False)
      lumi_scale: event weight (= xsection * luminosity / number of events)
      central_or_shift: either 'central' or one of the systematic uncertainties defined in $CMSSW_BASE/src/tthAnalysis/HiggsToTauTau/bin/analyze_1l_2tau.cc
    """  
    lines = []
    lines.append("process.fwliteInput.fileNames = cms.vstring(%s)" % inputFiles)
    lines.append("process.fwliteOutput.fileName = cms.string('%s')" % outputFile)
    lines.append("process.analyze_1l_2tau.process = cms.string('%s')" % sample_category)
    use_triggers_1e = "1e" in triggers
    lines.append("process.analyze_1l_2tau.use_triggers_1e = cms.bool(%s)" % use_triggers_1e)
    use_triggers_1mu = "1mu" in triggers
    lines.append("process.analyze_1l_2tau.use_triggers_1mu = cms.bool(%s)" % use_triggers_1mu)
    lines.append("process.analyze_1l_2tau.hadTauChargeSelection = cms.string('%s')" % hadTau_charge_selection)
    lines.append("process.analyze_1l_2tau.hadTauSelection = cms.string('%s')" % hadTau_selection)
    lines.append("process.analyze_1l_2tau.hadTauGenMatch = cms.string('%s')" % hadTau_genMatch)
    if hadTau_frWeight == "enabled":
      lines.append("process.analyze_1l_2tau.applyJetToTauFakeRateWeight = cms.bool(True)")
    elif hadTau_frWeight != "disabled":
      raise ValueError("Invalid parameter 'hadTau_frWeight' = %s !!" % hadTau_frWeight) 
    lines.append("process.analyze_1l_2tau.isMC = cms.bool(%s)" % is_mc)
    lines.append("process.analyze_1l_2tau.central_or_shift = cms.string('%s')" % central_or_shift)
    lines.append("process.analyze_1l_2tau.lumiScale = cms.double(%f)" % lumi_scale)
    create_cfg(self.cfgFile_analyze_original, cfgFile_modified, lines)

  def addToMakefile_hadd_stage1(self, lines_makefile):
    inputFiles_hadd_stage1 = []
    for sample_name, sample_info in self.samples.items():    
      process_name = sample_info["process_name_specific"]
      inputFiles_sample = []
      for hadTau_selection in self.hadTau_selections:
        for hadTau_frWeight in [ "enabled", "disabled" ]:
          hadTau_selection_and_frWeight = get_hadTau_selection_and_frWeight(hadTau_selection, hadTau_frWeight)
          for hadTau_genMatch in self.hadTau_genMatches:
            for hadTau_charge_selection in self.hadTau_charge_selections:
              for central_or_shift in self.central_or_shifts:
                inputFiles_jobIds = []
                for jobId in range(len(self.inputFileIds[sample_name])):
                  key_file = getKey(sample_name, hadTau_selection, hadTau_frWeight, hadTau_genMatch, hadTau_charge_selection, central_or_shift, jobId)
                  if key_file in self.histogramFiles.keys():
                    inputFiles_jobIds.append(self.histogramFiles[key_file])
                if len(inputFiles_jobIds) > 0:
                  haddFile_jobIds = self.histogramFile_hadd_stage1.replace(".root", "_%s_%s_%s_%s_%s.root" % \
                    (process_name, hadTau_selection, hadTau_genMatch, hadTau_charge_selection, central_or_shift))
                  lines_makefile.append("%s: %s" % (haddFile_jobIds, " ".join(inputFiles_jobIds)))
                  lines_makefile.append("\t%s %s %s" % ("hadd", haddFile_jobIds, " ".join(inputFiles_jobIds)))
                  lines_makefile.append("")
                  inputFiles_sample.append(haddFile_jobIds)
      if len(inputFiles_sample) > 0:
        haddFile_sample = self.histogramFile_hadd_stage1.replace(".root", "_%s.root" % process_name)
        lines_makefile.append("%s: %s" % (haddFile_sample, " ".join(inputFiles_sample)))
        lines_makefile.append("\t%s %s %s" % ("hadd", haddFile_sample, " ".join(inputFiles_sample)))
        lines_makefile.append("")
        inputFiles_hadd_stage1.append(haddFile_sample)
    lines_makefile.append("%s: %s" % (self.histogramFile_hadd_stage1, " ".join(inputFiles_hadd_stage1)))
    lines_makefile.append("\t%s %s %s" % ("hadd", self.histogramFile_hadd_stage1, " ".join(inputFiles_sample)))
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

      for hadTau_selection in self.hadTau_selections:
        for hadTau_frWeight in [ "enabled", "disabled" ]:
          if hadTau_frWeight == "enabled" and hadTau_selection != "Fakeable":
            continue
          hadTau_selection_and_frWeight = get_hadTau_selection_and_frWeight(hadTau_selection, hadTau_frWeight)
          for hadTau_genMatch in self.hadTau_genMatches:
            for hadTau_charge_selection in self.hadTau_charge_selections:
	      for central_or_shift in self.central_or_shifts:
                for jobId in range(len(self.inputFileIds[sample_name])):
                  if sample_category not in [ "TT", "EWK" ] and hadTau_genMatch != "all":
                    continue
                  sample_category_and_genMatch = sample_category
                  if hadTau_genMatch == "lepton":
                    sample_category_and_genMatch += "l"  
                  elif hadTau_genMatch == "hadTau":
                    sample_category_and_genMatch += "t"
                  elif hadTau_genMatch == "jet":
                    sample_category_and_genMatch += "j"
	          if central_or_shift != "central" and not (hadTau_selection == "Tight" and hadTau_charge_selection == "OS"):
	            continue
                  if central_or_shift != "central" and not is_mc:
	            continue

                  inputFiles = generate_input_list(self.inputFileIds[sample_name][jobId], secondary_files, primary_store, secondary_store, self.debug)

                  key_dir = getKey(sample_name, hadTau_selection, hadTau_frWeight, hadTau_charge_selection)
                  key_file = getKey(sample_name, hadTau_selection, hadTau_frWeight, hadTau_genMatch, hadTau_charge_selection, central_or_shift, jobId)

                  self.cfgFiles_analyze_modified[key_file] = os.path.join(self.dirs[key_dir][DKEY_CFGS], "analyze_%s_%s_%s_%s_%s_%s_%i_cfg.py" % \
                    (self.channel, process_name, hadTau_selection_and_frWeight, hadTau_genMatch, hadTau_charge_selection, central_or_shift, jobId))
                  self.histogramFiles[key_file] = os.path.join(self.dirs[key_dir][DKEY_HIST], "%s_%s_%s_%s_%s_%i.root" % \
                    (process_name, hadTau_selection_and_frWeight, hadTau_genMatch, hadTau_charge_selection, central_or_shift, jobId))
                  self.logFiles_analyze[key_file] = os.path.join(self.dirs[key_dir][DKEY_LOGS], "analyze_%s_%s_%s_%s_%s_%s_%i.log" % \
                    (self.channel, process_name, hadTau_selection_and_frWeight, hadTau_genMatch, hadTau_charge_selection, central_or_shift, jobId))
                
                  self.createCfg_analyze(inputFiles, self.histogramFiles[key_file], sample_category, triggers, hadTau_selection, hadTau_genMatch, hadTau_frWeight, hadTau_charge_selection,
                    is_mc, central_or_shift, lumi_scale, self.cfgFiles_analyze_modified[key_file])
                
    if self.is_sbatch:
      logging.info("Creating script for submitting '%s' jobs to batch system" % self.executable_analyze)
      self.createScript_sbatch()

    logging.info("Creating configuration files for executing 'prepareDatacards'")
    for histogramToFit in self.histograms_to_fit:
      self.createCfg_prep_dcard(histogramToFit)

    lines_makefile = []
    self.addToMakefile_analyze(lines_makefile)
    lines_makefile.append("")
    self.addToMakefile_hadd_stage1(lines_makefile)
    lines_makefile.append("")
    self.addToMakefile_backgrounds_from_data(lines_makefile)
    lines_makefile.append("")
    self.addToMakefile_hadd_stage2(lines_makefile)
    lines_makefile.append("")
    self.addToMakefile_prep_dcard(lines_makefile)
    self.createMakefile(lines_makefile)
  
    logging.info("Done")

