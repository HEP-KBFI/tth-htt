import logging

from tthAnalysis.HiggsToTauTau.configs.analyzeConfig_new import *
from tthAnalysis.HiggsToTauTau.jobTools import create_if_not_exists
from tthAnalysis.HiggsToTauTau.analysisTools import initDict, getKey, create_cfg, createFile, generateInputFileList

class analyzeConfig_Zctrl(analyzeConfig):
  """Configuration metadata needed to run analysis in a single go.

  Sets up a folder structure by defining full path names; no directory creation is delegated here.

  See $CMSSW_BASE/src/tthAnalysis/HiggsToTauTau/python/analyzeConfig.py
  for documentation of Args.

  """
  def __init__(self, configDir, outputDir, executable_analyze, cfgFile_analyze, samples, hadTau_selection,
               central_or_shifts, max_files_per_job, era, use_lumi, lumi, debug, running_method, num_parallel_jobs,
               histograms_to_fit, select_rle_output = False, executable_prep_dcard="prepareDatacard",
               verbose = False, dry_run = False):
    analyzeConfig.__init__(self, configDir, outputDir, executable_analyze, "Zctrl", central_or_shifts,
      max_files_per_job, era, use_lumi, lumi, debug, running_method, num_parallel_jobs,
      histograms_to_fit, verbose = verbose, dry_run = dry_run)

    self.samples = samples
    self.hadTau_selection_part2 = hadTau_selection

    for sample_name, sample_info in self.samples.items():
      if not sample_info["use_it"] or sample_info["sample_category"] in [ "additional_signal_overlap", "background_data_estimate" ]:
        continue
      process_name = sample_info["process_name_specific"]
      key_dir = getKey(sample_name)
      for dir_type in [ DKEY_CFGS, DKEY_HIST, DKEY_LOGS, DKEY_DCRD ]:
        initDict(self.dirs, [ key_dir, dir_type ])
        self.dirs[key_dir][dir_type] = os.path.join(self.outputDir, dir_type, self.channel,
          process_name)
    ##print "self.dirs = ", self.dirs

    self.cfgFile_analyze = os.path.join(self.template_dir, cfgFile_analyze)
    self.histogramDir_prep_dcard = "Zctrl"
    self.prep_dcard_processesToCopy = [ "data_obs", "TT", "TTW", "EWK", "Rares", "ttH_hww", "ttH_hzz", "ttH_htt" ]
    self.prep_dcard_signals = [ "DYJets" ]
    self.make_plots_backgrounds = [ "TTZ", "TTW", "EWK", "Rares", "TT" ]
    self.make_plots_signal = "signal"
    self.select_rle_output = select_rle_output
    self.evtSelections = [ "2lepton", "3lepton", "2lepton_1tau" ]
    raise ValueError("Fix me first before running!")

  def createCfg_analyze(self, jobOptions):
    """Create python configuration file for the analyze_ttZctrl executable (analysis code)
    """
    lines = []
    lines.append("process.fwliteInput.fileNames = cms.vstring(%s)" % jobOptions['ntupleFiles'])
    lines.append("process.fwliteOutput.fileName = cms.string('%s')" % os.path.basename(jobOptions['histogramFile']))
    lines.append("process.analyze_Zctrl.process = cms.string('%s')" % jobOptions['sample_category'])
    lines.append("process.analyze_Zctrl.era = cms.string('%s')" % self.era)
    lines.append("process.analyze_Zctrl.triggers_1e = cms.vstring(%s)" % self.triggers_1e)
    lines.append("process.analyze_Zctrl.use_triggers_1e = cms.bool(%s)" % ("1e" in jobOptions['triggers']))
    lines.append("process.analyze_Zctrl.triggers_2e = cms.vstring(%s)" % self.triggers_2e)
    lines.append("process.analyze_Zctrl.use_triggers_2e = cms.bool(%s)" % ("2e" in jobOptions['triggers']))
    lines.append("process.analyze_Zctrl.triggers_1mu = cms.vstring(%s)" % self.triggers_1mu)
    lines.append("process.analyze_Zctrl.use_triggers_1mu = cms.bool(%s)" % ("1mu" in jobOptions['triggers']))
    lines.append("process.analyze_Zctrl.triggers_2mu = cms.vstring(%s)" % self.triggers_2mu)
    lines.append("process.analyze_Zctrl.use_triggers_2mu = cms.bool(%s)" % ("2mu" in jobOptions['triggers']))
    lines.append("process.analyze_Zctrl.triggers_1e1mu = cms.vstring(%s)" % self.triggers_1e1mu)
    lines.append("process.analyze_Zctrl.use_triggers_1e1mu = cms.bool(%s)" % ("1e1mu" in jobOptions['triggers']))
    lines.append("process.analyze_WZctrl.hadTauSelection = cms.string('Tight|%s')" % jobOptions['hadTau_selection'])
    lines.append("process.analyze_Zctrl.isMC = cms.bool(%s)" % jobOptions['is_mc'])
    lines.append("process.analyze_Zctrl.central_or_shift = cms.string('%s')" % jobOptions['central_or_shift'])
    lines.append("process.analyze_Zctrl.lumiScale = cms.double(%f)" % jobOptions['lumi_scale'])
    lines.append("process.analyze_Zctrl.apply_trigger_bits = cms.bool(%s)" % jobOptions['apply_trigger_bits'])
    lines.append("process.analyze_Zctrl.selEventsFileName_output = cms.string('%s')" % jobOptions['rleOutputFile'])
    create_cfg(self.cfgFile_analyze, jobOptions['cfgFile_modified'], lines)

  def createCfg_makePlots(self, jobOptions):
    """Fills the template of python configuration file for making control plots

    Args:
      histogramFile: name of the input ROOT file
    """
    category_label = self.channel
    if jobOptions['label']:
      category_label += " (%s)" % jobOptions['label']
    lines = []
    lines.append("process.fwliteInput.fileNames = cms.vstring('%s')" % jobOptions['inputFile'])
    lines.append("process.makePlots.outputFileName = cms.string('%s')" % jobOptions['outputFile'])
    lines.append("process.makePlots.processesBackground = cms.vstring(%s)" % jobOptions['make_plots_backgrounds'])
    lines.append("process.makePlots.processSignal = cms.string('%s')" % self.make_plots_signal)
    lines.append("process.makePlots.categories = cms.VPSet(")
    lines.append("  cms.PSet(")
    lines.append("    name = cms.string('%s')," % jobOptions['histogramDir'])
    lines.append("    label = cms.string('%s')" % category_label)
    lines.append("  )")
    lines.append(")")
    lines.append("process.makePlots.distributions.append(cms.PSet(")
    lines.append("  histogramName = cms.string('sel/evt/$PROCESS/mLL'),")
    lines.append("  xAxisTitle = cms.string('m_{ll} [GeV]'),")
    lines.append("  yAxisTitle = cms.string('dN/dm_{ll} [1/GeV]')")
    lines.append("))")
    create_cfg(self.cfgFile_make_plots, jobOptions['cfgFile_modified'], lines)

  def create(self):
    """Creates all necessary config files and runs the complete analysis workfow -- either locally or on the batch system
    """

    for sample_name, sample_info in self.samples.items():
      if not sample_info["use_it"] or sample_info["sample_category"] in [ "additional_signal_overlap", "background_data_estimate" ]:
        continue
      process_name = sample_info["process_name_specific"]
      key_dir = getKey(process_name)
      for dir_type in [ DKEY_CFGS, DKEY_HIST, DKEY_LOGS, DKEY_RLES ]:
        initDict(self.dirs, [ key_dir, dir_type ])
        if dir_type in [ DKEY_CFGS, DKEY_LOGS ]:
          self.dirs[key_dir][dir_type] = os.path.join(self.configDir, dir_type, self.channel, "", process_name)
        else:
          self.dirs[key_dir][dir_type] = os.path.join(self.outputDir, dir_type, self.channel, "", process_name)
    for dir_type in [ DKEY_CFGS, DKEY_SCRIPTS, DKEY_HIST, DKEY_LOGS, DKEY_DCRD, DKEY_PLOT, DKEY_HADD_RT ]:
      initDict(self.dirs, [ dir_type ])
      if dir_type in [ DKEY_CFGS, DKEY_SCRIPTS, DKEY_LOGS, DKEY_HADD_RT ]:
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
          if central_or_shift != "central" and not is_mc:
            continue
          if central_or_shift.startswith("CMS_ttHl_thu_shape_ttH") and sample_category != "signal":
            continue
          if central_or_shift.startswith("CMS_ttHl_thu_shape_ttW") and sample_category != "TTW":
            continue
          if central_or_shift.startswith("CMS_ttHl_thu_shape_ttZ") and sample_category != "TTZ":
            continue

          key_dir = getKey(process_name)
          key_analyze_job = getKey(process_name, central_or_shift, jobId)
          ntupleFiles = inputFileList[jobId]
          if len(ntupleFiles) == 0:
            print "Warning: ntupleFiles['%s'] = %s --> skipping job !!" % (key_job, ntupleFiles)
            continue

          self.jobOptions_analyze[key_analyze_job] = {
            'ntupleFiles' : ntupleFiles,
            'cfgFile_modified' : os.path.join(self.dirs[key_dir][DKEY_CFGS], "analyze_%s_%s_%s_%i_cfg.py" % \
              (self.channel, process_name, central_or_shift, jobId)),
            'histogramFile' : os.path.join(self.dirs[key_dir][DKEY_HIST], "%s_%s_%i.root" % \
              (process_name, central_or_shift, jobId)),
            'logFile' : os.path.join(self.dirs[key_dir][DKEY_LOGS], "analyze_%s_%s_%s_%i.log" % \
              (self.channel, process_name, central_or_shift, jobId)),
            'rleOutputFile' : os.path.join(self.dirs[key_dir][DKEY_RLES], "rle_%s_%s_%s_%i.txt" % \
              (self.channel, process_name, central_or_shift, jobId)) if self.select_rle_output else "",
            'sample_category' : sample_category,
            'triggers' : sample_info["triggers"],
            'hadTau_selection' : self.hadTau_selection_part2,
            'use_HIP_mitigation_mediumMuonId' : True,
            'is_mc' : is_mc,
            'central_or_shift' : central_or_shift,
            'lumi_scale' : 1. if not (self.use_lumi and is_mc) else sample_info["xsection"] * self.lumi / sample_info["nof_events"],
            'apply_genWeight' : sample_info["genWeight"] if (is_mc and "genWeight" in sample_info.keys()) else False,
            'apply_trigger_bits' : (is_mc and (self.era == "2015" or (self.era == "2016" and sample_info["reHLT"]))) or not is_mc
          }

          self.createCfg_analyze(self.jobOptions_analyze[key_analyze_job])

          # initialize input and output file names for hadd_stage1
          key_hadd_stage1 = getKey(process_name)
          if not key_hadd_stage1 in self.inputFiles_hadd_stage1.keys():
            self.inputFiles_hadd_stage1[key_hadd_stage1] = []
          self.inputFiles_hadd_stage1[key_hadd_stage1].append(self.jobOptions_analyze[key_analyze_job]['histogramFile'])
          self.outputFile_hadd_stage1[key_hadd_stage1] = os.path.join(self.dirs[DKEY_HIST], "histograms_harvested_stage1_%s_%s.root" % \
            (self.channel, process_name))

      # initialize input and output file names for hadd_stage2
      key_hadd_stage1 = getKey(process_name)
      key_hadd_stage2 = getKey("all")
      if not key_hadd_stage2 in self.inputFiles_hadd_stage2.keys():
        self.inputFiles_hadd_stage2[key_hadd_stage2] = []
      self.inputFiles_hadd_stage2[key_hadd_stage2].append(self.outputFile_hadd_stage1[key_hadd_stage1])
      self.outputFile_hadd_stage2[key_hadd_stage2] = os.path.join(self.dirs[DKEY_HIST], "histograms_harvested_stage2_%s.root" % \
        (self.channel))

    logging.info("Creating configuration files to run 'prepareDatacards'")
    for evtSelection in self.evtSelections:
      for histogramToFit in self.histograms_to_fit:
        key_prep_dcard_job = getKey(evtSelection, histogramToFit)
        key_hadd_stage2 = getKey("all")
        self.jobOptions_prep_dcard[key_prep_dcard_job] = {
          'inputFile' : self.outputFile_hadd_stage2[key_hadd_stage2],
          'cfgFile_modified' : os.path.join(self.dirs[DKEY_CFGS], "prepareDatacards_%s_%s_%s_cfg.py" % (self.channel, evtSelection, histogramToFit)),
          'datacardFile' : os.path.join(self.dirs[DKEY_DCRD], "prepareDatacards_%s_%s_%s.root" % (self.channel, evtSelection, histogramToFit)),
          'histogramDir' : "_".join([ self.histogramDir_prep_dcard, evtSelection ]),
          'histogramToFit' : histogramToFit,
          'label' : None
        }
        self.createCfg_prep_dcard(self.jobOptions_prep_dcard[key_prep_dcard_job])

    logging.info("Creating configuration files to run 'makePlots'")
    for evtSelection in self.evtSelections:
      key_makePlots_job = getKey(evtSelection)
      key_hadd_stage2 = getKey("all")
      self.jobOptions_make_plots[key_makePlots_job] = {
        'executable' : self.executable_make_plots,
        'inputFile' : self.outputFile_hadd_stage2[key_hadd_stage2],
        'cfgFile_modified' : os.path.join(self.dirs[DKEY_CFGS], "makePlots_%s_%s_cfg.py" % (self.channel, evtSelection)),
        'outputFile' : os.path.join(self.dirs[DKEY_PLOT], "makePlots_%s_%s.png" % (self.channel, evtSelection)),
        'histogramDir' : "_".join([ self.histogramDir_prep_dcard, evtSelection ]),
        'label' : evtSelection,
        'make_plots_backgrounds' : self.make_plots_backgrounds
      }
      self.createCfg_makePlots(self.jobOptions_make_plots[key_makePlots_job])

    if self.is_sbatch:
      logging.info("Creating script for submitting '%s' jobs to batch system" % self.executable_analyze)
      self.sbatchFile_analyze = os.path.join(self.dirs[DKEY_SCRIPTS], "sbatch_analyze_%s.py" % self.channel)
      self.createScript_sbatch_analyze(
        executable = self.executable_analyze,
        sbatchFile = self.sbatchFile_analyze,
        jobOptions = self.jobOptions_analyze,
      )

    logging.info("Creating Makefile")
    lines_makefile = []
    self.addToMakefile_analyze(lines_makefile)
    self.addToMakefile_hadd_stage1(lines_makefile)
    #self.addToMakefile_backgrounds_from_data(lines_makefile)
    self.addToMakefile_hadd_stage2(lines_makefile)
    self.addToMakefile_outRoot(lines_makefile)
    self.addToMakefile_prep_dcard(lines_makefile)
    self.addToMakefile_make_plots(lines_makefile)
    self.createMakefile(lines_makefile)

    logging.info("Done")

    return self.num_jobs
