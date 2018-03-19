import logging

from tthAnalysis.HiggsToTauTau.configs.analyzeConfig import *
from tthAnalysis.HiggsToTauTau.jobTools import create_if_not_exists
from tthAnalysis.HiggsToTauTau.analysisTools import initDict, getKey, create_cfg, createFile, generateInputFileList

class analyzeConfig_inclusive(analyzeConfig):
  def __init__(self, configDir, outputDir, executable_analyze, cfgFile_analyze, samples, era,
               output_tree, check_input_files, running_method, verbose, dry_run, isDebug,
               rle_select, hadTauSelection_tauIdWP):
    analyzeConfig.__init__(self, configDir, outputDir, executable_analyze, "inclusive", [ ],
                           1, era, False, -1., False, running_method, 1, [], verbose = verbose,
                           dry_run = dry_run, isDebug = isDebug, do_sync = True)
    self.cfgFile_analyze = cfgFile_analyze
    self.samples = samples
    self.output_tree = output_tree
    self.check_input_files = check_input_files
    self.rle_select = rle_select
    self.hadTauSelection_tauIdWP = hadTauSelection_tauIdWP

    if self.rle_select and not os.path.isfile(self.rle_select):
      raise ValueError('Input RLE file for the sync is missing: %s' % self.rle_select)

    self.cfgFile_analyze = os.path.join(self.template_dir, cfgFile_analyze)

  def createCfg_analyze(self, jobOptions):
    lines = [
      "process.fwliteInput.fileNames = cms.vstring(%s)" % jobOptions['ntupleFiles'],
      "process.analyze_inclusive.era = cms.string('%s')" % self.era,
      "process.analyze_inclusive.isMC = cms.bool(%s)" % jobOptions['is_mc'],
      "process.analyze_inclusive.process = cms.string('%s')" % jobOptions['sample_category'],
      "process.analyze_inclusive.hadTauSelection_tauIdWP = cms.string('%s')" % self.hadTauSelection_tauIdWP,
      "process.analyze_inclusive.triggers_1e = cms.vstring(%s)" % self.triggers_1e,
      "process.analyze_inclusive.triggers_1mu = cms.vstring(%s)" % self.triggers_1mu,
      "process.analyze_inclusive.triggers_2e = cms.vstring(%s)" % self.triggers_2e,
      "process.analyze_inclusive.triggers_2mu = cms.vstring(%s)" % self.triggers_2mu,
      "process.analyze_inclusive.triggers_1e1mu = cms.vstring(%s)" % self.triggers_1e1mu,
      "process.analyze_inclusive.triggers_1e2mu = cms.vstring(%s)" % self.triggers_1e2mu,
      "process.analyze_inclusive.triggers_2e1mu = cms.vstring(%s)" % self.triggers_2e1mu,
      "process.analyze_inclusive.triggers_3e = cms.vstring(%s)" % self.triggers_3e,
      "process.analyze_inclusive.triggers_1e1tau = cms.vstring(%s)" % self.triggers_1e1tau,
      "process.analyze_inclusive.triggers_1mu1tau = cms.vstring(%s)" % self.triggers_1mu1tau,
      "process.analyze_inclusive.triggers_2tau = cms.vstring(%s)" % self.triggers_2tau,
      "process.analyze_inclusive.triggers_3mu = cms.vstring(%s)" % self.triggers_3mu,
      "process.analyze_inclusive.use_triggers_1e = cms.bool(%s)" % ("1e" in jobOptions['triggers']),
      "process.analyze_inclusive.use_triggers_1mu = cms.bool(%s)" % ("1mu" in jobOptions['triggers']),
      "process.analyze_inclusive.use_triggers_2e = cms.bool(%s)" % ("2e" in jobOptions['triggers']),
      "process.analyze_inclusive.use_triggers_2mu = cms.bool(%s)" % ("2mu" in jobOptions['triggers']),
      "process.analyze_inclusive.use_triggers_1e1mu = cms.bool(%s)" % ("1e1mu" in jobOptions['triggers']),
      "process.analyze_inclusive.use_triggers_1e2mu = cms.bool(%s)" % ("1e2mu" in jobOptions['triggers']),
      "process.analyze_inclusive.use_triggers_2e1mu = cms.bool(%s)" % ("2e1mu" in jobOptions['triggers']),
      "process.analyze_inclusive.use_triggers_3e = cms.bool(%s)" % ("3e" in jobOptions['triggers']),
      "process.analyze_inclusive.use_triggers_1e1tau = cms.bool(%s)" % ("1e1tau" in jobOptions['triggers']),
      "process.analyze_inclusive.use_triggers_1mu1tau = cms.bool(%s)" % ("1mu1tau" in jobOptions['triggers']),
      "process.analyze_inclusive.use_triggers_2tau = cms.bool(%s)" % ("2tau" in jobOptions['triggers']),
      "process.analyze_inclusive.use_triggers_3mu = cms.bool(%s)" % ("3mu" in jobOptions['triggers']),
      "process.analyze_inclusive.syncNtuple.tree   = cms.string('%s')" % jobOptions['syncTree'],
      "process.analyze_inclusive.syncNtuple.output = cms.string('%s')" % os.path.basename(jobOptions['syncOutput']),
      "process.analyze_inclusive.isDEBUG = cms.bool(%s)" % self.isDebug,
    ]
    create_cfg(self.cfgFile_analyze, jobOptions['cfgFile_modified'], lines)

  def create(self):
    for sample_name, sample_info in self.samples.items():
      if not sample_info["use_it"] or sample_info["sample_category"] in [ "additional_signal_overlap", "background_data_estimate" ]:
        continue
      process_name = sample_info["process_name_specific"]
      key_dir = getKey(process_name)
      for dir_type in [ DKEY_CFGS, DKEY_LOGS, DKEY_RLES, DKEY_SYNC ]:
        initDict(self.dirs, [ key_dir, dir_type ])
        if dir_type in [ DKEY_CFGS, DKEY_LOGS ]:
          self.dirs[key_dir][dir_type] = os.path.join(self.configDir, dir_type, self.channel, process_name)
        else:
          self.dirs[key_dir][dir_type] = os.path.join(self.outputDir, dir_type, self.channel, process_name)
    for dir_type in [ DKEY_CFGS, DKEY_SCRIPTS, DKEY_LOGS, DKEY_SYNC, DKEY_HADD_RT ]:
      initDict(self.dirs, [ dir_type ])
      if dir_type in [ DKEY_CFGS, DKEY_SCRIPTS, DKEY_LOGS, DKEY_HADD_RT ]:
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
      inputFileLists[sample_name] = generateInputFileList(sample_info, self.max_files_per_job, self.check_input_files)

    for sample_name, sample_info in self.samples.items():
      if not sample_info["use_it"] or sample_info["sample_category"] in [ "additional_signal_overlap", "background_data_estimate" ]:
        continue
      process_name = sample_info["process_name_specific"]
      logging.info("Creating configuration files to run '%s' for sample %s" % (self.executable_analyze, process_name))

      sample_category = sample_info["sample_category"]
      is_mc = (sample_info["type"] == "mc")
      inputFileList = inputFileLists[sample_name]

      for jobId in inputFileList.keys():

        key_dir = getKey(process_name)
        key_analyze_job = getKey(process_name, jobId)
        ntupleFiles = inputFileList[jobId]
        if len(ntupleFiles) == 0:
          print("Warning: no ntupleFiles --> skipping job !!")
          continue

        syncOutput = os.path.join(self.dirs[key_dir][DKEY_SYNC], '%s.root' % self.channel)
        self.inputFiles_sync['sync'].append(syncOutput)

        self.jobOptions_analyze[key_analyze_job] = {
          'ntupleFiles' : ntupleFiles,
          'cfgFile_modified' : os.path.join(self.dirs[key_dir][DKEY_CFGS], "analyze_%s_%s_%i_cfg.py" % \
            (self.channel, process_name, jobId)),
          'logFile' : os.path.join(self.dirs[key_dir][DKEY_LOGS], "analyze_%s_%s_%i.log" % \
                  (self.channel, process_name, jobId)),
          'sample_category': sample_category,
          'process_name_specific': sample_info["process_name_specific"],
          'triggers': sample_info["triggers"],
          'is_mc': is_mc,
          'syncTree' : self.output_tree,
          'syncOutput' : syncOutput,
        }
        self.createCfg_analyze(self.jobOptions_analyze[key_analyze_job])

    logging.info("Creating script for submitting '%s' jobs to batch system" % self.executable_analyze)
    self.sbatchFile_analyze = os.path.join(self.dirs[DKEY_SCRIPTS], "sbatch_analyze_%s.py" % self.channel)
    self.createScript_sbatch_syncNtuple(self.executable_analyze, self.sbatchFile_analyze, self.jobOptions_analyze)
    logging.info("Creating Makefile")
    lines_makefile = []
    self.addToMakefile_syncNtuple(lines_makefile)
    outputFile_sync_path = os.path.join(self.outputDir, DKEY_SYNC, '%s.root' % self.channel)
    self.outputFile_sync['sync'] = outputFile_sync_path
    self.targets.append(outputFile_sync_path)
    self.addToMakefile_hadd_sync(lines_makefile)
    self.createMakefile(lines_makefile)
    logging.info("Done")
    return self.num_jobs
