import logging

from tthAnalysis.HiggsToTauTau.configs.analyzeConfig import *
from tthAnalysis.HiggsToTauTau.jobTools import create_if_not_exists
from tthAnalysis.HiggsToTauTau.analysisTools import initDict, getKey, create_cfg, createFile, generateInputFileList

class analyzeConfig_inclusive(analyzeConfig):
  def __init__(self, configDir, outputDir, executable_analyze, cfgFile_analyze, samples, era,
               output_tree, check_input_files, running_method, verbose, dry_run, isDebug,
               rle_select, hadTauSelection_tauIdWP, use_nonnominal = False, use_home = True):
    analyzeConfig.__init__(self, configDir, outputDir, executable_analyze,
      channel = "inclusive",
      central_or_shifts = [ ],
      max_files_per_job = 1,
      era = era,
      use_lumi = False,
      lumi = -1.,
      check_input_files = False,
      running_method = running_method,
      num_parallel_jobs = 1,
      histograms_to_fit = [],
      triggers = [
        '1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu',
        '1e2mu', '2e1mu', '1e1tau', '1mu1tau', '2tau',
      ],
      verbose = verbose,
      dry_run = dry_run,
      isDebug = isDebug,
      do_sync = True,
      use_home = use_home,
    )
    self.cfgFile_analyze = cfgFile_analyze
    self.samples = samples
    self.output_tree = output_tree
    self.check_input_files = check_input_files
    self.rle_select = rle_select
    self.hadTauSelection_tauIdWP = hadTauSelection_tauIdWP
    self.use_nonnominal = use_nonnominal

    if self.rle_select and not os.path.isfile(self.rle_select):
      raise ValueError('Input RLE file for the sync is missing: %s' % self.rle_select)

    self.cfgFile_analyze = os.path.join(self.template_dir, cfgFile_analyze)

  def createCfg_analyze(self, jobOptions, sample_info):
    additionalJobOptions = [
      'hadTauSelection_tauIdWP',
    ]

    lines = super(analyzeConfig_inclusive, self).createCfg_analyze(jobOptions, sample_info, additionalJobOptions)
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

        cfg_key = getKey(self.channel, process_name, jobId)
        cfgFile_modified_path = os.path.join(self.dirs[key_dir][DKEY_CFGS], "analyze_%s_cfg.py" % cfg_key)
        logFile_path = os.path.join(self.dirs[key_dir][DKEY_LOGS], "analyze_%s.log" % cfg_key)

        self.jobOptions_analyze[key_analyze_job] = {
          'ntupleFiles'             : ntupleFiles,
          'cfgFile_modified'        : cfgFile_modified_path,
          'histogramFile'           : '',
          'logFile'                 : logFile_path,
          'syncTree'                : self.output_tree,
          'syncOutput'              : syncOutput,
          'syncRLE'                 : self.rle_select if self.rle_select and '%s' not in self.rle_select else '',
          'hadTauSelection_tauIdWP' : self.hadTauSelection_tauIdWP,
          'useNonNominal'           : self.use_nonnominal,
        }
        self.createCfg_analyze(self.jobOptions_analyze[key_analyze_job], sample_info)

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
