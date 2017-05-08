import logging

from tthAnalysis.HiggsToTauTau.analyzeConfig_new import *
from tthAnalysis.HiggsToTauTau.jobTools import create_if_not_exists
from tthAnalysis.HiggsToTauTau.analysisTools import initDict, getKey, create_cfg, createFile, generateInputFileList

class analyzeConfig_jetToTauFakeRate(analyzeConfig):
  """Configuration metadata needed to run analysis in a single go.
  
  Sets up a folder structure by defining full path names; no directory creation is delegated here.
  
  Args specific to analyzeConfig_jetToTauFakeRate:
    charge_selection: either `OS` or `SS` (opposite-sign or same-sign of the electron+muon pair)
    hadTau_selections: list of tau ID discriminators to check

  See $CMSSW_BASE/src/tthAnalysis/HiggsToTauTau/python/analyzeConfig.py
  for documentation of further Args.
  
  """
  def __init__(self, configDir, outputDir, executable_analyze, samples, charge_selections,
               jet_minPt, jet_maxPt, jet_minAbsEta, jet_maxAbsEta, hadTau_selection_denominator, hadTau_selections_numerator, absEtaBins, ptBins, central_or_shifts,
               max_files_per_job, era, use_lumi, lumi, debug, running_method, num_parallel_jobs,
               executable_comp_jetToTauFakeRate):
    analyzeConfig.__init__(self, configDir, outputDir, executable_analyze, "jetToTauFakeRate", central_or_shifts,
      max_files_per_job, era, use_lumi, lumi, debug, running_method, num_parallel_jobs, 
      [])

    self.samples = samples

    self.charge_selections = charge_selections

    self.jet_minPt = jet_minPt
    self.jet_maxPt = jet_maxPt
    self.jet_minAbsEta = jet_minAbsEta
    self.jet_maxAbsEta = jet_maxAbsEta

    self.hadTau_selection_denominator = hadTau_selection_denominator
    self.hadTau_selections_numerator = hadTau_selections_numerator
        
    self.absEtaBins = absEtaBins
    self.ptBins = ptBins

    self.executable_comp_jetToTauFakeRate = executable_comp_jetToTauFakeRate
    
    self.cfgFile_analyze = os.path.join(self.workingDir, "analyze_jetToTauFakeRate_cfg.py")
    self.cfgFile_comp_jetToTauFakeRate = os.path.join(self.workingDir, "comp_jetToTauFakeRate_cfg.py")
    self.jobOptions_comp_jetToTauFakeRate = {}
    self.cfgFile_make_plots = os.path.join(self.workingDir, "makePlots_jetToTauFakeRate_cfg.py")
    self.cfgFile_make_plots_denominator = os.path.join(self.workingDir, "makePlots_jetToTauFakeRate_denominator_cfg.py")
    
  def createCfg_analyze(self, jobOptions):
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
    lines.append("process.fwliteInput.fileNames = cms.vstring(%s)" % jobOptions['ntupleFiles'])
    lines.append("process.fwliteOutput.fileName = cms.string('%s')" % os.path.basename(jobOptions['histogramFile']))
    lines.append("process.analyze_jetToTauFakeRate.process = cms.string('%s')" % jobOptions['sample_category'])
    lines.append("process.analyze_jetToTauFakeRate.era = cms.string('%s')" % self.era)
    lines.append("process.analyze_jetToTauFakeRate.triggers_1e = cms.vstring(%s)" % self.triggers_1e)
    lines.append("process.analyze_jetToTauFakeRate.use_triggers_1e = cms.bool(%s)" % ("1e" in jobOptions['triggers']))
    lines.append("process.analyze_jetToTauFakeRate.triggers_1mu = cms.vstring(%s)" % self.triggers_1mu)
    lines.append("process.analyze_jetToTauFakeRate.use_triggers_1mu = cms.bool(%s)" % ("1mu" in jobOptions['triggers']))
    lines.append("process.analyze_jetToTauFakeRate.triggers_1e1mu = cms.vstring(%s)" % self.triggers_1e1mu)
    lines.append("process.analyze_jetToTauFakeRate.use_triggers_1e1mu = cms.bool(%s)" % ("1e1mu" in jobOptions['triggers']))
    lines.append("process.analyze_jetToTauFakeRate.chargeSelection = cms.string('%s')" % jobOptions['charge_selection'])
    lines.append("process.analyze_jetToTauFakeRate.jet_minPt = cms.double('%f')" % jobOptions['jet_minPt'])
    lines.append("process.analyze_jetToTauFakeRate.jet_maxPt = cms.double('%f')" % jobOptions['jet_maxPt'])
    lines.append("process.analyze_jetToTauFakeRate.jet_minAbsEta = cms.double('%f')" % jobOptions['jet_minAbsEta'])
    lines.append("process.analyze_jetToTauFakeRate.jet_maxAbsEta = cms.double('%f')" % jobOptions['jet_maxAbsEta'])
    lines.append("process.analyze_jetToTauFakeRate.hadTauSelection_denominator = cms.string('%s')" % jobOptions['hadTau_selection_denominator'])
    lines.append("process.analyze_jetToTauFakeRate.hadTauSelections_numerator = cms.vstring(")
    for hadTau_selection in jobOptions['hadTau_selections_numerator']:
      lines.append("    '%s'," % hadTau_selection)
    lines.append(")")
    lines.append("process.analyze_jetToTauFakeRate.absEtaBins = cms.vdouble(%s)" % jobOptions['absEtaBins'])
    lines.append("process.analyze_jetToTauFakeRate.use_HIP_mitigation_bTag = cms.bool(%s)" % jobOptions['use_HIP_mitigation_bTag'])
    lines.append("process.analyze_jetToTauFakeRate.use_HIP_mitigation_mediumMuonId = cms.bool(%s)" % jobOptions['use_HIP_mitigation_mediumMuonId'])
    lines.append("process.analyze_jetToTauFakeRate.isMC = cms.bool(%s)" % jobOptions['is_mc'])
    lines.append("process.analyze_jetToTauFakeRate.central_or_shift = cms.string('%s')" % jobOptions['central_or_shift'])
    lines.append("process.analyze_jetToTauFakeRate.lumiScale = cms.double(%f)" % jobOptions['lumi_scale'])
    lines.append("process.analyze_jetToTauFakeRate.apply_genWeight = cms.bool(%s)" % jobOptions['apply_genWeight'])
    lines.append("process.analyze_jetToTauFakeRate.apply_trigger_bits = cms.bool(%s)" % jobOptions['apply_trigger_bits'])
    create_cfg(self.cfgFile_analyze, jobOptions['cfgFile_modified'], lines)

  def createCfg_comp_jetToTauFakeRate(self, jobOptions):
    """Create python configuration file for the comp_jetToTauFakeRate executable

    Args:
      inputFiles: input file (the ROOT file produced by hadd_stage1)
      outputFile: output file of the job
    """
    for charge_selection in self.charge_selections:
      lines = []
      lines.append("process.fwliteInput.fileNames = cms.vstring('%s')" % jobOptions['inputFile'])
      lines.append("process.fwliteOutput.fileName = cms.string('%s')" % os.path.basename(jobOptions['outputFile']))
      lines.append("process.comp_jetToTauFakeRate.looseRegion = cms.string('%s')" % jobOptions['looseRegion'])
      lines.append("process.comp_jetToTauFakeRate.tightRegion = cms.string('%s')" % jobOptions['tightRegion'])
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
      lines.append("process.comp_jetToTauFakeRate.absEtaBins = cms.vdouble(%s)" % jobOptions['absEtaBins'])
      lines.append("process.comp_jetToTauFakeRate.ptBins = cms.vdouble(%s)" % jobOptions['ptBins'])
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
      if not sample_info["use_it"] or sample_info["sample_category"] in [ "additional_signal_overlap", "background_data_estimate" ]:
        continue
      process_name = sample_info["process_name_specific"]
      for charge_selection in self.charge_selections:
        key_dir = getKey(process_name, charge_selection)
        for dir_type in [ DKEY_CFGS, DKEY_HIST, DKEY_LOGS, DKEY_RLES ]:
          initDict(self.dirs, [ key_dir, dir_type ])
          if dir_type in [ DKEY_CFGS, DKEY_LOGS ]:
            self.dirs[key_dir][dir_type] = os.path.join(self.configDir, dir_type, self.channel,
              "_".join([ charge_selection ]), process_name)
          else:
            self.dirs[key_dir][dir_type] = os.path.join(self.outputDir, dir_type, self.channel,
              "_".join([ charge_selection ]), process_name)
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
      inputFileLists[sample_name] = generateInputFileList(sample_name, sample_info, self.max_files_per_job, self.debug)
  
    self.inputFileIds = {}
    for sample_name, sample_info in self.samples.items():
      if not sample_info["use_it"] or sample_info["sample_category"] in [ "additional_signal_overlap", "background_data_estimate" ]:
        continue

      process_name = sample_info["process_name_specific"]

      logging.info("Creating configuration files to run '%s' for sample %s" % (self.executable_analyze, process_name))  

      is_mc = (sample_info["type"] == "mc")
      lumi_scale = 1. if not (self.use_lumi and is_mc) else sample_info["xsection"] * self.lumi / sample_info["nof_events"]
      apply_genWeight = sample_info["apply_genWeight"] if (is_mc and "apply_genWeight" in sample_info.keys()) else False
      sample_category = sample_info["sample_category"]
      triggers = sample_info["triggers"]
      apply_trigger_bits = (is_mc and (self.era == "2015" or (self.era == "2016" and sample_info["reHLT"]))) or not is_mc

      for charge_selection in self.charge_selections:
        for central_or_shift in self.central_or_shifts:

          inputFileList = inputFileLists[sample_name]
          for jobId in inputFileList.keys():
            if central_or_shift != "central" and not is_mc:
              continue
            if central_or_shift.startswith("CMS_ttHl_thu_shape_ttH") and sample_category != "signal":
              continue
            if central_or_shift.startswith("CMS_ttHl_thu_shape_ttW") and sample_category != "TTW":
              continue
            if central_or_shift.startswith("CMS_ttHl_thu_shape_ttZ") and sample_category != "TTZ":
              continue

            # build config files for executing analysis code
            key_dir = getKey(process_name, charge_selection)
            key_analyze_job = getKey(process_name, charge_selection, central_or_shift, jobId)

            ntupleFiles = inputFileList[jobId]
            if len(ntupleFiles) == 0:
              print "Warning: ntupleFiles['%s'] = %s --> skipping job !!" % (key_job, ntupleFiles)
              continue
            self.jobOptions_analyze[key_analyze_job] = {
              'ntupleFiles' : ntupleFiles,
              'cfgFile_modified' : os.path.join(self.dirs[key_dir][DKEY_CFGS], "analyze_%s_%s_%s_%s_%i_cfg.py" % \
                (self.channel, process_name, charge_selection, central_or_shift, jobId)),
              'histogramFile' : os.path.join(self.dirs[key_dir][DKEY_HIST], "%s_%s_%s_%i.root" % \
                (process_name, charge_selection, central_or_shift, jobId)),
              'logFile' : os.path.join(self.dirs[key_dir][DKEY_LOGS], "analyze_%s_%s_%s_%s_%i.log" % \
                (self.channel, process_name, charge_selection, central_or_shift, jobId)),
              'sample_category' : sample_category,
              'triggers' : sample_info["triggers"],
              'charge_selection' : charge_selection,
              'jet_minPt' : self.jet_minPt,
              'jet_maxPt' : self.jet_maxPt,
              'jet_minAbsEta' : self.jet_minAbsEta,
              'jet_maxAbsEta' : self.jet_maxAbsEta,
              'hadTau_selection_denominator' : self.hadTau_selection_denominator,
              'hadTau_selections_numerator' : self.hadTau_selections_numerator,
              'absEtaBins' : self.absEtaBins,
              ##'use_HIP_mitigation_bTag' : sample_info["use_HIP_mitigation_bTag"],
              ##'use_HIP_mitigation_mediumMuonId' : sample_info["use_HIP_mitigation_mediumMuonId"],
              'use_HIP_mitigation_bTag' : True,
              'use_HIP_mitigation_mediumMuonId' : True,
              'is_mc' : is_mc,
              'central_or_shift' : central_or_shift,
              'lumi_scale' : 1. if not (self.use_lumi and is_mc) else sample_info["xsection"] * self.lumi / sample_info["nof_events"],
              'apply_genWeight' : sample_info["genWeight"] if (is_mc and "genWeight" in sample_info.keys()) else False,
              'apply_trigger_bits' : (is_mc and (self.era == "2015" or (self.era == "2016" and sample_info["reHLT"]))) or not is_mc,
            }
            self.createCfg_analyze(self.jobOptions_analyze[key_analyze_job])

            # initialize input and output file names for hadd_stage1
            key_hadd_stage1 = getKey(process_name, charge_selection)
            if not key_hadd_stage1 in self.inputFiles_hadd_stage1:
              self.inputFiles_hadd_stage1[key_hadd_stage1] = []
            self.inputFiles_hadd_stage1[key_hadd_stage1].append(self.jobOptions_analyze[key_analyze_job]['histogramFile'])
            self.outputFile_hadd_stage1[key_hadd_stage1] = os.path.join(self.dirs[DKEY_HIST], "histograms_harvested_stage1_%s_%s_%s.root" % \
              (self.channel, process_name, charge_selection))

        # initialize input and output file names for hadd_stage2
        key_hadd_stage1 = getKey(process_name, charge_selection)
        key_hadd_stage2 = getKey(charge_selection)
        if not key_hadd_stage2 in self.inputFiles_hadd_stage2:
          self.inputFiles_hadd_stage2[key_hadd_stage2] = []
        self.inputFiles_hadd_stage2[key_hadd_stage2].append(self.outputFile_hadd_stage1[key_hadd_stage1])
        self.outputFile_hadd_stage2[key_hadd_stage2] = os.path.join(self.dirs[DKEY_HIST], "histograms_harvested_stage2_%s_%s.root" % \
          (self.channel, charge_selection))

    logging.info("Creating configuration files for executing 'comp_jetToTauFakeRate'")
    for charge_selection in self.charge_selections:
      key_comp_jetToTauFakeRate_job = getKey(charge_selection)
      key_hadd_stage2 = getKey(charge_selection)
      self.jobOptions_comp_jetToTauFakeRate[key_comp_jetToTauFakeRate_job] = {
        'inputFile' : self.outputFile_hadd_stage2[key_hadd_stage2],
        'cfgFile_modified' : os.path.join(
          self.dirs[DKEY_CFGS], "comp_jetToTauFakeRate_%s_cfg.py" % charge_selection),
        'outputFile' : os.path.join(
          self.dirs[DKEY_HIST], "comp_jetToTauFakeRate_%s.root" % charge_selection),
        'logFile' : os.path.join(
          self.dirs[DKEY_LOGS], "comp_jetToTauFakeRate_%s.log" % charge_selection),
        'looseRegion' : "jetToTauFakeRate_%s/denominator/" % charge_selection,
        'tightRegion' : "jetToTauFakeRate_%s/numerator/" % charge_selection,
        'absEtaBins' : self.absEtaBins,
        'ptBins' : self.ptBins
      }
      self.createCfg_comp_jetToTauFakeRate(self.jobOptions_comp_jetToTauFakeRate[key_comp_jetToTauFakeRate_job])
      self.targets.append(self.jobOptions_comp_jetToTauFakeRate[key_comp_jetToTauFakeRate_job]['outputFile'])

    logging.info("Creating configuration files to run 'makePlots'")
    for charge_selection in self.charge_selections:
      key_makePlots_job = getKey(charge_selection)
      key_hadd_stage2 = getKey(charge_selection)
      self.jobOptions_make_plots[key_makePlots_job] = {
        'executable' : self.executable_make_plots,
        'inputFile' : self.outputFile_hadd_stage2[key_hadd_stage2],
        'cfgFile_modified' : os.path.join(
          self.dirs[DKEY_CFGS], "makePlots_%s_cfg.py" % self.channel),
        'outputFile' : os.path.join(
          self.dirs[DKEY_PLOT], "makePlots_%s.png" % self.channel),
        'histogramDir' : "jetToTauFakeRate_%s" % charge_selection,
        'label' : None,
        'make_plots_backgrounds' : [ "TT", "TTW", "TTZ", "EWK", "Rares" ],
      }
      self.createCfg_makePlots(self.jobOptions_make_plots[key_makePlots_job])
      self.cfgFile_make_plots = self.cfgFile_make_plots_denominator
      for absEtaBin in [ "absEtaLt1_5", "absEta1_5to9_9" ]:
        key_makePlots_job = getKey(charge_selection, absEtaBin, "denominator")
        key_hadd_stage2 = getKey(charge_selection)
        self.jobOptions_make_plots[key_makePlots_job] = {
          'executable' : self.executable_make_plots,
          'inputFile' : self.outputFile_hadd_stage2[key_hadd_stage2],
          'cfgFile_modified' : os.path.join(
            self.dirs[DKEY_CFGS], "makePlots_%s_%s_denominator_%s_cfg.py" % (self.channel, charge_selection, absEtaBin)),
          'outputFile' : os.path.join(
            self.dirs[DKEY_PLOT], "makePlots_%s_%s_denominator_%s.png" % (self.channel, charge_selection, absEtaBin)),
          'histogramDir' : "jetToTauFakeRate_%s/denominator/%s" % (charge_selection, absEtaBin),
          'label' : None,
          'make_plots_backgrounds' : [ "TT", "TTW", "TTZ", "EWK", "Rares" ],
        }
        self.createCfg_makePlots(self.jobOptions_make_plots[key_makePlots_job])
        for hadTau_selection_numerator in self.hadTau_selections_numerator:
          key_makePlots_job = getKey(charge_selection, absEtaBin, "numerator", hadTau_selection_numerator)
          key_hadd_stage2 = getKey(charge_selection)
          self.jobOptions_make_plots[key_makePlots_job] = {
            'executable' : self.executable_make_plots,
            'inputFile' : self.outputFile_hadd_stage2[key_hadd_stage2],
            'cfgFile_modified' : os.path.join(
              self.dirs[DKEY_CFGS], "makePlots_%s_%s_numerator_%s_%s_cfg.py" % (self.channel, charge_selection, hadTau_selection_numerator, absEtaBin)),
            'outputFile' : os.path.join(
              self.dirs[DKEY_PLOT], "makePlots_%s_%s_numerator_%s_%s.png" % (self.channel, charge_selection, hadTau_selection_numerator, absEtaBin)),
            'histogramDir' : "jetToTauFakeRate_%s/numerator/%s/%s" % (charge_selection, hadTau_selection_numerator, absEtaBin),
            'label' : None,
            'make_plots_backgrounds' : [ "TT", "TTW", "TTZ", "EWK", "Rares" ],
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
    self.addToMakefile_hadd_stage2(lines_makefile)
    self.addToMakefile_comp_jetToTauFakeRate(lines_makefile)
    self.addToMakefile_make_plots(lines_makefile)
    self.createMakefile(lines_makefile)
  
    logging.info("Done")

