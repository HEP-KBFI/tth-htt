import logging

from tthAnalysis.HiggsToTauTau.analyzeConfig import *
import tthAnalyzeSamples_chargeflip
from tthAnalysis.HiggsToTauTau.jobTools import create_if_not_exists

class analyzeConfig_charge_flip(analyzeConfig):
  """Configuration metadata needed to run analysis in a single go.
  
  Sets up a folder structure by defining full path names; no directory creation is delegated here.
  
  See $CMSSW_BASE/src/tthAnalysis/HiggsToTauTau/python/analyzeConfig.py
  for documentation of further Args.
  
  """
  def __init__(self, outputDir, executable_analyze, samples, lepton_selections, central_or_shifts,
               max_files_per_job, era, use_lumi, lumi, debug, running_method, num_parallel_jobs, 
               histograms_to_fit = [], select_rle_output = False, executable_prep_dcard="prepareDatacard"):
    analyzeConfig.__init__(self, outputDir, executable_analyze, "charge_flip", central_or_shifts,
      max_files_per_job, era, use_lumi, lumi, debug, running_method, num_parallel_jobs, 
      histograms_to_fit)

    self.samples = samples
    
    self.prep_dcard_processesToCopy = ["data_obs", "DY", "DY_fake", "WJets", "TTbar", "Singletop", "Diboson"]
    self.prep_dcard_signals = [ "DY" ]
    
    self.lepton_selections = lepton_selections
    
    #self.hadTau_selection = hadTau_selection

    for sample_name, sample_info in self.samples.items():
      if not sample_info["use_it"] or sample_info["sample_category"] in [ "additional_signal_overlap", "background_data_estimate" ]:
        continue
      process_name = sample_info["process_name_specific"]
      for lepton_selection in self.lepton_selections:
          key_dir = getKey(sample_name, lepton_selection)  
          for dir_type in [ DKEY_CFGS, DKEY_HIST, DKEY_LOGS, DKEY_DCRD, DKEY_RLES  ]:
            initDict(self.dirs, [ key_dir, dir_type ])
            self.dirs[key_dir][dir_type] = os.path.join(self.outputDir, dir_type, self.channel,
              "_".join([ lepton_selection ]), process_name)
    ##print "self.dirs = ", self.dirs

    self.cfgFile_analyze_original = os.path.join(self.workingDir, "analyze_charge_flip_cfg.py")
    self.cfgFile_prep_dcard_original = os.path.join(self.workingDir, "prepareDatacards_cfg.py")
    #self.histogramDir_prep_dcard = "charge_flip_SS_Tight"
    self.select_rle_output = select_rle_output

  def createCfg_analyze(self, inputFiles, outputFile, sample_category, era, triggers, lepton_selection, 
                        is_mc, central_or_shift, lumi_scale, apply_trigger_bits, cfgFile_modified, rle_output_file):
    """Create python configuration file for the analyze_charge_flip executable (analysis code)

    Args:
      inputFiles: list of input files (Ntuples)
      outputFile: output file of the job -- a ROOT file containing histogram
      process: 
      is_mc: flag indicating whether job runs on MC (True) or data (False)
      lumi_scale: event weight (= xsection * luminosity / number of events)
      central_or_shift: either 'central' or one of the systematic uncertainties defined in $CMSSW_BASE/src/tthAnalysis/HiggsToTauTau/bin/analyze_charge_flip.cc
    """  
    lines = []
    ##lines.append("process.fwliteInput.fileNames = cms.vstring(%s)" % [ os.path.basename(inputFile) for inputFile in inputFiles ])
    lines.append("process.fwliteInput.fileNames = cms.vstring(%s)" % inputFiles)
    lines.append("process.fwliteOutput.fileName = cms.string('%s')" % os.path.basename(outputFile))
    lines.append("process.analyze_charge_flip.process = cms.string('%s')" % sample_category)
    lines.append("process.analyze_charge_flip.era = cms.string('%s')" % era)
    lines.append("process.analyze_charge_flip.triggers_1e = cms.vstring(%s)" % self.triggers_1e)
    lines.append("process.analyze_charge_flip.use_triggers_1e = cms.bool(%s)" % ("1e" in triggers))
    lines.append("process.analyze_charge_flip.triggers_2e = cms.vstring(%s)" % self.triggers_2e)
    lines.append("process.analyze_charge_flip.use_triggers_2e = cms.bool(%s)" % ("2e" in triggers))
    lines.append("process.analyze_charge_flip.leptonSelection = cms.string('%s')" % lepton_selection)
    lines.append("process.analyze_charge_flip.isMC = cms.bool(%s)" % is_mc)
    lines.append("process.analyze_charge_flip.central_or_shift = cms.string('%s')" % central_or_shift)
    lines.append("process.analyze_charge_flip.lumiScale = cms.double(%f)" % lumi_scale)
    lines.append("process.analyze_charge_flip.apply_trigger_bits = cms.bool(%s)" % apply_trigger_bits)
    lines.append("process.analyze_charge_flip.selEventsFileName_output = cms.string('%s')" % rle_output_file)
    create_cfg(self.cfgFile_analyze_original, cfgFile_modified, lines)

  def addToMakefile_hadd_stage1(self, lines_makefile):
    inputFiles_hadd_stage1 = []
    for sample_name, sample_info in self.samples.items():
      if not sample_name in self.inputFileIds.keys():
        continue
      process_name = sample_info["process_name_specific"]
      inputFiles_sample = []
      for lepton_selection in self.lepton_selections:
        for central_or_shift in self.central_or_shifts:
          #Electron ER only for DY
          if (not "DY" in process_name) and "CMS_ttHl_electronER" in central_or_shift: continue
          inputFiles_jobIds = []                  
          for jobId in range(len(self.inputFileIds[sample_name])):
            key_file = getKey(sample_name, lepton_selection, central_or_shift, jobId)
            if key_file in self.histogramFiles.keys():
              inputFiles_jobIds.append(self.histogramFiles[key_file])
          if len(inputFiles_jobIds) > 0:
            haddFile_jobIds = self.histogramFile_hadd_stage1.replace(".root", "_%s_%s_%s.root" % \
              (process_name, lepton_selection, central_or_shift))
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

  def addToMakefile_hadd_stage2(self, lines_makefile):
    """Adds the commands to Makefile that are necessary for building the final histogram file.
    """
    lines_makefile.append("%s: %s" % (self.histogramFile_hadd_stage2, " ".join([ self.histogramFile_hadd_stage1])))
    lines_makefile.append("\t%s %s" % ("rm -f", self.histogramFile_hadd_stage2))
    lines_makefile.append("\t%s %s %s" % ("hadd", self.histogramFile_hadd_stage2, " ".join([ self.histogramFile_hadd_stage1])))
    lines_makefile.append("")
    self.filesToClean.append(self.histogramFile_hadd_stage2)

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


  """def createMakefile(self, lines_makefile):
    Creates Makefile that runs the complete analysis workfow.
    
    targets = []
    targets.extend(self.datacardFiles.values())
    if self.rootOutputAux:
      targets.append("selEventTree_hadd")
    for idxJob in range(len(self.cfgFiles_make_plots_modified)):
      targets.append("makePlots%i" % idxJob)
    lines_makefile_with_header = []
    lines_makefile_with_header.append(".DEFAULT_GOAL := all")
    lines_makefile_with_header.append("SHELL := /bin/bash")
    lines_makefile_with_header.append("")
    lines_makefile_with_header.append("all: %s" % " ".join(targets))
    lines_makefile_with_header.append("")
    lines_makefile_with_header.extend(lines_makefile)
    createFile(self.makefile, lines_makefile_with_header)
    """
    
  def createCfg_prep_dcard(self, histogramToFit, histogramDir = None, label = None):
    """Fills the template of python configuration file for datacard preparation

    Args:
      histogramToFit: name of the histogram used for signal extraction
    """
    datacardFile = os.path.join(self.outputDir, DKEY_DCRD, "prepareDatacards_%s_%s.root" % (self.channel, histogramToFit))
    category_output = self.channel
    cfgFile_modified = os.path.join(self.outputDir, DKEY_CFGS, "prepareDatacards_%s_%s_cfg.py" % (self.channel, histogramToFit))
    key = histogramToFit
    if not histogramDir:
        histogramDir = self.histogramDir_prep_dcard
        if label:
            datacardFile = datacardFile.replace(channel, "%s_%s" % (channel, label))
            category_output += "_%s" % label
            cfgFile_modified = cfgFile_modified.replace("_cfg.py", "_%s_cfg.py" % label)
            key = getKey(histogramToFit, label)
    lines = []
    lines.append("process.fwliteInput.fileNames = cms.vstring('%s')" % self.histogramFile_hadd_stage2)
    lines.append("process.fwliteOutput.fileName = cms.string('%s')" % datacardFile)
    lines.append("process.prepareDatacards.processesToCopy = cms.vstring(%s)" % self.prep_dcard_processesToCopy)
    lines.append("process.prepareDatacards.signals = cms.vstring(%s)" % self.prep_dcard_signals)
    lines.append("process.prepareDatacards.makeSubDir = cms.bool(True)")
    lines.append("process.prepareDatacards.categories = cms.VPSet(")
    for charge in ["OS", "SS"]:
	for ptEtaBin in ["BB_LL", "BB_ML", "BB_MM", "BB_HL", "BB_HM", "BB_HH", "EE_LL", "EE_ML", "EE_MM", "EE_HL", "EE_HM", "EE_HH", "BE_LL", "BE_ML", "EB_ML", "BE_MM", "BE_HL", "EB_HL", "BE_HM", "EB_HM", "BE_HH", "total"]:
	    lines.append("    cms.PSet(")
	    lines.append("        input = cms.string('%s/%s')," % (charge, ptEtaBin))
	    lines.append("        output = cms.string('ttH_%s_%s_%s')" % (self.channel, charge, ptEtaBin))
	    lines.append("    ),")
    lines.append(")")
    lines.append("process.prepareDatacards.histogramToFit = cms.string('%s')" % histogramToFit)
    lines.append("""process.prepareDatacards.sysShifts = cms.vstring(
            "CMS_ttHl_electronESBarrelUp",
        	"CMS_ttHl_electronESBarrelDown",
        	"CMS_ttHl_electronESEndcapUp",
	        "CMS_ttHl_electronESEndcapDown",
	        "CMS_ttHl_electronERUp",
	        "CMS_ttHl_electronERDown") """
    )
    create_cfg(self.cfgFile_prep_dcard_original, cfgFile_modified, lines)
    self.datacardFiles[key] = datacardFile
    self.cfgFile_prep_dcard_modified[key] = cfgFile_modified

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

      for lepton_selection in self.lepton_selections:
        for central_or_shift in self.central_or_shifts:
          for jobId in range(len(self.inputFileIds[sample_name])):
            if central_or_shift != "central" and not (lepton_selection == "Tight"):
              continue
            if central_or_shift != "central" and not is_mc:
              continue
            if central_or_shift.startswith("CMS_ttHl_thu_shape_ttH") and sample_category != "signal":
              continue
            if central_or_shift.startswith("CMS_ttHl_thu_shape_ttW") and sample_category != "TTW":
              continue
            if central_or_shift.startswith("CMS_ttHl_thu_shape_ttZ") and sample_category != "TTZ":
              continue

            key_dir = getKey(sample_name, lepton_selection)
            key_file = getKey(sample_name, lepton_selection, central_or_shift, jobId)

            self.ntupleFiles[key_file] = generate_input_list(self.inputFileIds[sample_name][jobId], secondary_files, primary_store, secondary_store, self.debug)
            self.cfgFiles_analyze_modified[key_file] = os.path.join(self.dirs[key_dir][DKEY_CFGS], "analyze_%s_%s_%s_%s_%i_cfg.py" % \
              (self.channel, process_name, lepton_selection, central_or_shift, jobId))
            self.histogramFiles[key_file] = os.path.join(self.dirs[key_dir][DKEY_HIST], "%s_%s_%s_%i.root" % \
              (process_name, lepton_selection, central_or_shift, jobId))
            self.logFiles_analyze[key_file] = os.path.join(self.dirs[key_dir][DKEY_LOGS], "analyze_%s_%s_%s_%s_%i.log" % \
              (self.channel, process_name, lepton_selection, central_or_shift, jobId))
            self.rleOutputFiles[key_file] = os.path.join(self.dirs[key_dir][DKEY_RLES], "rle_%s_%s_%s_%s_%i.txt" % \
              (self.channel, process_name, lepton_selection, central_or_shift, jobId)) if self.select_rle_output else ""  
            self.createCfg_analyze(self.ntupleFiles[key_file], self.histogramFiles[key_file], sample_category, self.era, triggers,
              lepton_selection, 
              is_mc, central_or_shift, lumi_scale, apply_trigger_bits, self.cfgFiles_analyze_modified[key_file], self.rleOutputFiles[key_file])
                
    if self.is_sbatch:
      logging.info("Creating script for submitting '%s' jobs to batch system" % self.executable_analyze)
      self.createScript_sbatch()
      print self.sbatchFile_analyze
    #logging.info("Creating configuration files for executing 'addBackgroundLeptonFakes'")
    #self.createCfg_addFakes(self.histogramFile_hadd_stage1, self.histogramFile_addFakes, self.cfgFile_addFakes_modified)

    #logging.info("Creating configuration files for executing 'addBackgroundLeptonFlips'")
    #self.createCfg_addFlips(self.histogramFile_hadd_stage1, self.histogramFile_addFlips, self.cfgFile_addFlips_modified)

    logging.info("Creating configuration files for executing 'prepareDatacards'")
    for histogramToFit in self.histograms_to_fit:
      self.createCfg_prep_dcard(histogramToFit)

    lines_makefile = []
    self.addToMakefile_analyze(lines_makefile)
    self.addToMakefile_hadd_stage1(lines_makefile)
    self.addToMakefile_backgrounds_from_data(lines_makefile)
    self.addToMakefile_hadd_stage2(lines_makefile)
    self.addToMakefile_prep_dcard(lines_makefile)
    self.addToMakefile_clean(lines_makefile)
    self.createMakefile(lines_makefile)
  
    logging.info("Done")

