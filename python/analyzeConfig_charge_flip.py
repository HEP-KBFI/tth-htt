import logging

from tthAnalysis.HiggsToTauTau.analyzeConfig_new import *
import tthAnalyzeSamples_chargeflip_2016
from tthAnalysis.HiggsToTauTau.jobTools import create_if_not_exists
from tthAnalysis.HiggsToTauTau.analysisTools import initDict, getKey, create_cfg, createFile, generateInputFileList

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

  def createCfg_analyze(self, jobOptions):
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
    lines.append("process.fwliteInput.fileNames = cms.vstring(%s)" % jobOptions["ntupleFiles"])
    lines.append("process.fwliteOutput.fileName = cms.string('%s')" % os.path.basename(jobOptions["histogramFile"]))
    lines.append("process.analyze_charge_flip.process = cms.string('%s')" % jobOptions["sample_category"])
    lines.append("process.analyze_charge_flip.era = cms.string('%s')" % self.era)
    lines.append("process.analyze_charge_flip.triggers_1e = cms.vstring(%s)" % self.triggers_1e)
    lines.append("process.analyze_charge_flip.use_triggers_1e = cms.bool(%s)" % ("1e" in jobOptions["triggers"]))
    lines.append("process.analyze_charge_flip.triggers_2e = cms.vstring(%s)" % self.triggers_2e)
    lines.append("process.analyze_charge_flip.use_triggers_2e = cms.bool(%s)" % ("2e" in jobOptions["triggers"]))
    lines.append("process.analyze_charge_flip.triggers_1mu = cms.vstring(%s)" % self.triggers_1mu)
    lines.append("process.analyze_charge_flip.use_triggers_1mu = cms.bool(%s)" % ("1mu" in jobOptions["triggers"]))
    lines.append("process.analyze_charge_flip.triggers_2mu = cms.vstring(%s)" % self.triggers_2mu)
    lines.append("process.analyze_charge_flip.use_triggers_2mu = cms.bool(%s)" % ("2mu" in jobOptions["triggers"]))
    lines.append("process.analyze_charge_flip.leptonSelection = cms.string('%s')" % jobOptions["lepton_selection"])
    lines.append("process.analyze_charge_flip.isMC = cms.bool(%s)" % jobOptions["is_mc"])
    lines.append("process.analyze_charge_flip.central_or_shift = cms.string('%s')" % jobOptions["central_or_shift"])
    lines.append("process.analyze_charge_flip.lumiScale = cms.double(%f)" % jobOptions["lumi_scale"])
    lines.append("process.analyze_charge_flip.apply_trigger_bits = cms.bool(%s)" % jobOptions["apply_trigger_bits"])
    lines.append("process.analyze_charge_flip.selEventsFileName_output = cms.string('%s')" % jobOptions["rleOutputFile"])
    create_cfg(self.cfgFile_analyze_original, jobOptions["cfgFile_modified"], lines)
    

  """def addToMakefile_hadd_stage1(self, lines_makefile):
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
  """
  
  def createCfg_prep_dcard(self, jobOptions):
      """Fills the template of python configuration file for datacard preparation
         Args:
           histogramToFit: name of the histogram used for signal extraction
      """
      category_output = self.channel
      if jobOptions['label']:
          category_output += "_%s" % jobOptions['label']
      lines = []
      lines.append("process.fwliteInput.fileNames = cms.vstring('%s')" % jobOptions['inputFile'])
      lines.append("process.fwliteOutput.fileName = cms.string('%s')" % jobOptions['datacardFile'])
      lines.append("process.prepareDatacards.processesToCopy = cms.vstring(%s)" % self.prep_dcard_processesToCopy)
      lines.append("process.prepareDatacards.signals = cms.vstring(%s)" % self.prep_dcard_signals)
      lines.append("process.prepareDatacards.makeSubDir = cms.bool(True)")
      lines.append("process.prepareDatacards.categories = cms.VPSet(")
      for charge in ["OS", "SS"]:
        for ptEtaBin in ["BB_LL", "BB_ML", "BB_MM", "BB_HL", "BB_HM", "BB_HH", "EE_LL", "EE_ML", "EE_MM", "EE_HL", "EE_HM", "EE_HH", "BE_LL", "BE_ML", "EB_ML","BE_MM",  "BE_HL", "EB_HL", "BE_HM", "EB_HM", "BE_HH", "total"]:
          lines.append("    cms.PSet(")
          lines.append("        input = cms.string('%s/%s')," % (charge, ptEtaBin))
          lines.append("        output = cms.string('ttH_%s_%s_%s')" % (self.channel, charge, ptEtaBin))
          lines.append("    ),")
      lines.append(")")
      lines.append("process.prepareDatacards.histogramToFit = cms.string('%s')" % jobOptions['histogramToFit'])
      lines.append("""process.prepareDatacards.sysShifts = cms.vstring(
          "CMS_ttHl_electronESBarrelUp",
      	"CMS_ttHl_electronESBarrelDown",
      	"CMS_ttHl_electronESEndcapUp",
        "CMS_ttHl_electronESEndcapDown",
        "CMS_ttHl_electronERUp",
        "CMS_ttHl_electronERDown") """
      )
      create_cfg(self.cfgFile_prep_dcard, jobOptions['cfgFile_modified'], lines)
  
  
  def create(self):
    """Creates all necessary config files and runs the complete analysis workfow -- either locally or on the batch system
    """
  
    for sample_name, sample_info in self.samples.items():
      if not sample_info["use_it"] or sample_info["sample_category"] in [ "additional_signal_overlap", "background_data_estimate" ]:
        continue
      process_name = sample_info["process_name_specific"]
      for lepton_selection in self.lepton_selections:
        #lepton_and_hadTau_selection_and_frWeight = get_lepton_and_hadTau_selection_and_frWeight(lepton_and_hadTau_selection, lepton_and_hadTau_frWeight)
        key_dir = getKey(process_name, lepton_selection)
        for dir_type in [ DKEY_CFGS, DKEY_HIST, DKEY_LOGS, DKEY_RLES ]:
          initDict(self.dirs, [ key_dir, dir_type ])
          self.dirs[key_dir][dir_type] = os.path.join(self.outputDir, dir_type, self.channel,
            "_".join([ lepton_selection ]), process_name)
    for dir_type in [ DKEY_SCRIPTS, DKEY_DCRD, DKEY_PLOT ]:
      initDict(self.dirs, [ dir_type ])
      self.dirs[dir_type] = os.path.join(self.outputDir, dir_type, self.channel)
    ##print "self.dirs = ", self.dirs

    for key in self.dirs.keys():
      if type(self.dirs[key]) == dict:
        for dir_type in self.dirs[key].keys():
          create_if_not_exists(self.dirs[key][dir_type])
      else:
        create_if_not_exists(self.dirs[key])

    for lepton_selection in self.lepton_selections:
        for sample_name, sample_info in self.samples.items():
          if not sample_info["use_it"] or sample_info["sample_category"] in [ "additional_signal_overlap", "background_data_estimate" ]:
            continue
          process_name = sample_info["process_name_specific"]
          logging.info("Creating configuration files to run '%s' for sample %s" % (self.executable_analyze, process_name))  
          
          sample_category = sample_info["sample_category"]
          is_mc = (sample_info["type"] == "mc")
          is_signal = (sample_category == "signal")

          for central_or_shift in self.central_or_shifts:

            inputFileList = generateInputFileList(sample_name, sample_info, self.max_files_per_job, self.debug)
            for jobId in inputFileList.keys():
              #if central_or_shift != "central" and not (lepton_and_hadTau_selection.startswith("Tight") and lepton_charge_selection == "SS"):
              #  continue
              if central_or_shift != "central" and not is_mc:
                continue                

              # build config files for executing analysis code
              key_dir = getKey(process_name, lepton_selection)
              key_analyze_job = getKey(process_name, lepton_selection, central_or_shift, jobId)
              ntupleFiles = inputFileList[jobId]
              if len(ntupleFiles) == 0:
                print "Warning: ntupleFiles['%s'] = %s --> skipping job !!" % (key_job, ntupleFiles)
                continue
              self.jobOptions_analyze[key_analyze_job] = {
                'ntupleFiles' : ntupleFiles,
                'cfgFile_modified' : os.path.join(self.dirs[key_dir][DKEY_CFGS], "analyze_%s_%s_%s_%s_%i_cfg.py" % \
                  (self.channel, process_name, lepton_selection, central_or_shift, jobId)),
                'histogramFile' : os.path.join(self.dirs[key_dir][DKEY_HIST], "%s_%s_%s_%i.root" % \
                  (process_name, lepton_selection, central_or_shift, jobId)),
                'logFile' : os.path.join(self.dirs[key_dir][DKEY_LOGS], "analyze_%s_%s_%s_%s_%i.log" % \
                  (self.channel, process_name, lepton_selection, central_or_shift, jobId)),
                'rleOutputFile' : os.path.join(self.dirs[key_dir][DKEY_RLES], "rle_%s_%s_%s_%s_%i.txt" % \
                  (self.channel, process_name, lepton_selection, central_or_shift, jobId)) if self.select_rle_output else "",
                'sample_category' : sample_category,
                'triggers' : sample_info["triggers"],
                'lepton_selection' : lepton_selection,
                #'apply_leptonGenMatching' : self.apply_leptonGenMatching,
                #'apply_hadTauGenMatching' : self.apply_hadTauGenMatching,
                #'applyFakeRateWeights' : self.applyFakeRateWeights if not (lepton_selection == "Tight" and hadTau_selection.find("Tight") != -1) else "disabled",
                'is_mc' : is_mc,
                'central_or_shift' : central_or_shift,
                'lumi_scale' : 1. if not (self.use_lumi and is_mc) else sample_info["xsection"] * self.lumi / sample_info["nof_events"],
                'apply_genWeight' : sample_info["genWeight"] if (is_mc and "genWeight" in sample_info.keys()) else False,
                'apply_trigger_bits' : (is_mc and (self.era == "2015" or (self.era == "2016" and sample_info["reHLT"]))) or not is_mc
              }

              #applyFakeRateWeights = self.applyFakeRateWeights
              #if lepton_and_hadTau_frWeight == "disabled":
              #  applyFakeRateWeights = "disabled"
              self.createCfg_analyze(self.jobOptions_analyze[key_analyze_job])

              # initialize input and output file names for hadd_stage1
              key_hadd_stage1 = getKey(process_name, lepton_selection)
              if not key_hadd_stage1 in self.inputFiles_hadd_stage1.keys():
                self.inputFiles_hadd_stage1[key_hadd_stage1] = []
              self.inputFiles_hadd_stage1[key_hadd_stage1].append(self.jobOptions_analyze[key_analyze_job]['histogramFile'])
              self.outputFile_hadd_stage1[key_hadd_stage1] = os.path.join(self.outputDir, DKEY_HIST, "histograms_harvested_stage1_%s_%s_%s.root" % \
                  (self.channel, process_name, lepton_selection))

          #key_hadd_stage1 = getKey(process_name, lepton_selection)
          #key_hadd_stage1_5 = getKey(lepton_selection)
          #print self.inputFiles_hadd_stage1_5 
          #self.inputFiles_hadd_stage1_5[key_hadd_stage1_5].append(self.outputFile_hadd_stage1[key_hadd_stage1])

        key_addBackgrounds_job = getKey(lepton_selection)
        sample_categories = []
        sample_categories.extend([ "signal" ])
        processes_input = []


        # initialize input and output file names for hadd_stage2
        key_hadd_stage2 = getKey(lepton_selection)
        if not key_hadd_stage2 in self.inputFiles_hadd_stage2.keys():
          self.inputFiles_hadd_stage2[key_hadd_stage2] = []
        #if lepton_selection == "Tight":
        #  self.inputFiles_hadd_stage2[key_hadd_stage2].append(self.jobOptions_addBackgrounds[key_addBackgrounds_job]['outputFile'])
        #key_hadd_stage1_5 = getKey(lepton_and_hadTau_selection_and_frWeight)
        self.inputFiles_hadd_stage2[key_hadd_stage2].append(self.outputFile_hadd_stage1[key_hadd_stage1])
        self.outputFile_hadd_stage2[key_hadd_stage2] = os.path.join(self.outputDir, DKEY_HIST, "histograms_harvested_stage2_%s_%s.root" % \
          (self.channel, lepton_selection))

    """if self.isBDTtraining:
      if self.is_sbatch:
        logging.info("Creating script for submitting '%s' jobs to batch system" % self.executable_analyze)
        self.sbatchFile_analyze = os.path.join(self.dirs[DKEY_SCRIPTS], "sbatch_analyze_%s.py" % self.channel)
        self.createScript_sbatch()        
      logging.info("Creating Makefile")
      lines_makefile = []
      self.addToMakefile_analyze(lines_makefile)
      self.createMakefile(lines_makefile)    
      logging.info("Done")      
      return"""
    
    """logging.info("Creating configuration files to run 'addBackgroundFakes'")
    for lepton_charge_selection in self.lepton_charge_selections:
      key_addFakes_job = getKey("fakes_data", lepton_charge_selection)
      key_hadd_stage1_5 = getKey(get_lepton_and_hadTau_selection_and_frWeight("Fakeable", "enabled"), lepton_charge_selection)
      category_sideband = None
      if self.applyFakeRateWeights == "2lepton":
        category_sideband = "2lss_1tau_%s_Fakeable_wFakeRateWeights" % lepton_charge_selection
      elif self.applyFakeRateWeights == "3L":
        category_sideband = "2lss_1tau_%s_Fakeable_wFakeRateWeights" % lepton_charge_selection
      elif self.applyFakeRateWeights == "1tau":
        category_sideband = "2lss_1tau_%s_Fakeable_wFakeRateWeights" % lepton_charge_selection
      else:
        raise ValueError("Invalid Configuration parameter 'applyFakeRateWeights' = %s !!" % applyFakeRateWeights)
      self.jobOptions_addFakes[key_addFakes_job] = {
        'inputFile' : self.outputFile_hadd_stage1_5[key_hadd_stage1_5],
        'cfgFile_modified' : os.path.join(self.outputDir, DKEY_CFGS, "addBackgroundLeptonFakes_%s_%s_cfg.py" % \
          (self.channel, lepton_charge_selection)),
        'outputFile' : os.path.join(self.outputDir, DKEY_HIST, "addBackgroundLeptonFakes_%s_%s.root" % \
          (self.channel, lepton_charge_selection)),
        'category_signal' : "2lss_1tau_%s_Tight" % lepton_charge_selection,
        'category_sideband' : category_sideband
      }
      self.createCfg_addFakes(self.jobOptions_addFakes[key_addFakes_job])
      key_hadd_stage2 = getKey(get_lepton_and_hadTau_selection_and_frWeight("Tight", "disabled"), lepton_charge_selection)
      self.inputFiles_hadd_stage2[key_hadd_stage2].append(self.jobOptions_addFakes[key_addFakes_job]['outputFile'])
    """
    
    """
    #--------------------------------------------------------------------------
    # CV: add histograms in OS and SS regions,
    #     so that "fakes_data" background can be subtracted from OS control region used to estimate charge flip background
    key_addFakes_job = getKey("fakes_data", "OS")
    self.inputFiles_hadd_stage1_6.append(self.jobOptions_addFakes[key_addFakes_job]['outputFile'])
    key_hadd_stage1_5 = getKey(get_lepton_and_hadTau_selection_and_frWeight("Tight", "disabled"), "OS")
    self.inputFiles_hadd_stage1_6.append(self.outputFile_hadd_stage1_5[key_hadd_stage1_5])
    self.outputFile_hadd_stage1_6 = os.path.join(self.outputDir, DKEY_HIST, "histograms_harvested_stage1_6_%s_Tight_OS.root" % \
      (self.channel))
    #--------------------------------------------------------------------------

    logging.info("Creating configuration files to run 'addBackgroundFlips'")
    key_addFlips_job = getKey("flips_data")
    self.jobOptions_addFlips[key_addFlips_job] = {
      'inputFile' : self.outputFile_hadd_stage1_6,
      'cfgFile_modified' : os.path.join(self.outputDir, DKEY_CFGS, "addBackgroundLeptonFlips_%s_cfg.py" % \
        self.channel),
      'outputFile' : os.path.join(self.outputDir, DKEY_HIST, "addBackgroundLeptonFlips_%s.root" % \
        self.channel)
    }
    self.createCfg_addFlips(self.jobOptions_addFlips[key_addFlips_job])
    """
    key_hadd_stage2 = getKey(lepton_selection)
    #self.inputFiles_hadd_stage2[key_hadd_stage2].append(self.jobOptions_addFlips[key_addFlips_job]['outputFile'])

    logging.info("Creating configuration files to run 'prepareDatacards'")
    processesToCopy = []
    for process in self.prep_dcard_processesToCopy:
      processesToCopy.append(process)
    self.prep_dcard_processesToCopy = processesToCopy
    processesToCopy = []
    for process in self.prep_dcard_signals:
      processesToCopy.append(process)
    self.prep_dcard_signals = processesToCopy
    for histogramToFit in self.histograms_to_fit:
      key_prep_dcard_job = getKey(histogramToFit)
      key_hadd_stage2 = getKey(lepton_selection)
      self.jobOptions_prep_dcard[key_prep_dcard_job] = {
        'inputFile' : self.outputFile_hadd_stage2[key_hadd_stage2],
        'cfgFile_modified' : os.path.join(self.outputDir, DKEY_CFGS, "prepareDatacards_%s_%s_cfg.py" % (self.channel, histogramToFit)),
        'datacardFile' : os.path.join(self.outputDir, DKEY_DCRD, "prepareDatacards_%s_%s.root" % (self.channel, histogramToFit)),
        'histogramDir' : self.histogramDir_prep_dcard,
        'histogramToFit' : histogramToFit,
        'label' : None
      }                            
      self.createCfg_prep_dcard(self.jobOptions_prep_dcard[key_prep_dcard_job])


      # add shape templates for 'CMS_ttHl_Clos_e' and 'CMS_ttHl_Clos_m' systematic uncertainties
      """if histogramToFit in [ "mvaDiscr_2lss" ]:
        key_add_syst_dcard_job = getKey(histogramToFit)
        self.jobOptions_add_syst_dcard[key_add_syst_dcard_job] = {
          'inputFile' : self.jobOptions_prep_dcard[key_prep_dcard_job]['datacardFile'],
          'cfgFile_modified' : os.path.join(self.outputDir, DKEY_CFGS, "addSystDatacards_%s_%s_cfg.py" % (self.channel, histogramToFit)),
          'outputFile' : os.path.join(self.outputDir, DKEY_DCRD, "addSystDatacards_%s_%s.root" % (self.channel, histogramToFit)),
          'category' : self.channel,
          'histogramToFit' : histogramToFit
        }
        self.createCfg_add_syst_dcard(self.jobOptions_add_syst_dcard[key_add_syst_dcard_job])
        """
  
    """logging.info("Creating configuration files to run 'makePlots'")
    key_makePlots_job = getKey("SS")
    key_hadd_stage2 = getKey(get_lepton_and_hadTau_selection_and_frWeight("Tight", "disabled"), "SS")                            
    self.jobOptions_make_plots[key_makePlots_job] = {
      'executable' : self.executable_make_plots,
      'inputFile' : self.outputFile_hadd_stage2[key_hadd_stage2],
      'cfgFile_modified' : os.path.join(self.outputDir, DKEY_CFGS, "makePlots_%s_cfg.py" % self.channel),
      'outputFile' : os.path.join(self.outputDir, DKEY_PLOT, self.channel, "makePlots_%s.png" % self.channel),
      'histogramDir' : self.histogramDir_prep_dcard,
      'label' : None,
      'make_plots_backgrounds' : self.make_plots_backgrounds
    }
    self.createCfg_makePlots(self.jobOptions_make_plots[key_makePlots_job])
    if "OS" in self.lepton_charge_selections:
      make_plots_backgrounds = self.make_plots_backgrounds
      if "flips_data" in make_plots_backgrounds:
        make_plots_backgrounds.remove("flips_data")
      key_makePlots_job = getKey("OS")
      key_hadd_stage2 = getKey(get_lepton_and_hadTau_selection_and_frWeight("Tight", "disabled"), "OS")                        
      self.jobOptions_make_plots[key_makePlots_job] = {
        'executable' : self.executable_make_plots,
        'inputFile' : self.outputFile_hadd_stage2[key_hadd_stage2],
        'cfgFile_modified' : os.path.join(self.outputDir, DKEY_CFGS, "makePlots_%s_OS_cfg.py" % self.channel),
        'outputFile' : os.path.join(self.outputDir, DKEY_PLOT, self.channel, "makePlots_%s_OS.png" % self.channel),                       
        'histogramDir' : self.histogramDir_prep_dcard_OS,
        'label' : "OS",
        'make_plots_backgrounds' : make_plots_backgrounds
      }
      self.createCfg_makePlots(self.jobOptions_make_plots[key_makePlots_job])
    if "Fakeable_mcClosure" in self.lepton_and_hadTau_selections:
      key_makePlots_job = getKey("SS")
      key_hadd_stage2 = getKey(get_lepton_and_hadTau_selection_and_frWeight("Tight", "disabled"), "SS")
      self.jobOptions_make_plots[key_makePlots_job] = {
        'executable' : self.executable_make_plots_mcClosure,
        'inputFile' : self.outputFile_hadd_stage2[key_hadd_stage2],
        'cfgFile_modified' : os.path.join(self.outputDir, DKEY_CFGS, "makePlots_mcClosure_%s_cfg.py" % self.channel),
        'outputFile' : os.path.join(self.outputDir, DKEY_PLOT, self.channel, "makePlots_mcClosure_%s.png" % self.channel)                       
      }
      self.createCfg_makePlots_mcClosure(self.jobOptions_make_plots[key_makePlots_job])
    """            
    if self.is_sbatch:
      logging.info("Creating script for submitting '%s' jobs to batch system" % self.executable_analyze)
      self.sbatchFile_analyze = os.path.join(self.dirs[DKEY_SCRIPTS], "sbatch_analyze_%s.py" % self.channel)
      self.createScript_sbatch()

    logging.info("Creating Makefile")
    lines_makefile = []
    self.addToMakefile_analyze(lines_makefile)
    self.addToMakefile_hadd_stage1(lines_makefile)
    #self.addToMakefile_backgrounds_from_data(lines_makefile)
    self.addToMakefile_hadd_stage2(lines_makefile)
    self.addToMakefile_prep_dcard(lines_makefile)
    #self.addToMakefile_add_syst_dcard(lines_makefile)
    #self.addToMakefile_make_plots(lines_makefile)
    self.createMakefile(lines_makefile)
  
    logging.info("Done")

  


#  def create(self):
"""Creates all necessary config files and runs the complete analysis workfow -- either locally or on the batch system
    """
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

      is_mc = (sample_info["type"] == "mc")
      lumi_scale = 1. if not (self.use_lumi and is_mc) else sample_info["xsection"] * self.lumi / sample_info["nof_events"]
      sample_category = sample_info["sample_category"]
      triggers = sample_info["triggers"]
      apply_trigger_bits = (is_mc and (self.era == "2015" or (self.era == "2016" and sample_info["reHLT"]))) or not is_mc

      for lepton_selection in self.lepton_selections:
        for central_or_shift in self.central_or_shifts:

          inputFileList = generateInputFileList(sample_name, sample_info, self.max_files_per_job, self.debug)
          for jobId in inputFileList.keys():
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

            self.ntupleFiles[key_file] = inputFileList[jobId]
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
    self.createMakefile(lines_makefile)
  
    logging.info("Done")
    """

