from tthAnalysis.HiggsToTauTau.configs.analyzeConfig import *
from tthAnalysis.HiggsToTauTau.jobTools import create_if_not_exists
from tthAnalysis.HiggsToTauTau.analysisTools import initDict, getKey, create_cfg, generateInputFileList
from tthAnalysis.HiggsToTauTau.common import logging

class testGenPhotonFilterConfig(analyzeConfig):
  def __init__(self,
        configDir,
        localDir,
        outputDir,
        executable_analyze,
        cfgFile_analyze,
        samples,
        max_files_per_job,
        era,
        use_lumi,
        lumi,
        check_output_files,
        running_method,
        num_parallel_jobs,
        dry_run,
        isDebug,
        use_home,
        submission_cmd,
      ):
    analyzeConfig.__init__(self,
      configDir             = configDir,
      localDir              = localDir,
      outputDir             = outputDir,
      executable_analyze    = executable_analyze,
      channel               = "testGenPhotonFilter",
      samples               = samples,
      jet_cleaning_by_index = False, # doesn't matter
      gen_matching_by_index = False, # doesn't matter
      central_or_shifts     = [ 'central' ],
      max_files_per_job     = max_files_per_job,
      era                   = era,
      use_lumi              = use_lumi,
      lumi                  = lumi,
      check_output_files    = check_output_files,
      running_method        = running_method,
      num_parallel_jobs     = num_parallel_jobs,
      histograms_to_fit     = [],
      triggers              = [],
      dry_run               = dry_run,
      isDebug               = isDebug,
      use_home              = use_home,
      submission_cmd        = submission_cmd,
    )

    self.cfgFile_analyze = cfgFile_analyze
    self.check_output_files = check_output_files
    self.cfgFile_analyze = os.path.join(self.template_dir, self.cfgFile_analyze)
    self.plot_executable = 'plot_genPhotonFilter.py'

  def createCfg_analyze(self, jobOptions, sample_info):
    lines = super(testGenPhotonFilterConfig, self).createCfg_analyze(jobOptions, sample_info)
    create_cfg(self.cfgFile_analyze, jobOptions['cfgFile_modified'], lines)

  def addToMakefile_plot(self, lines_makefile, inputFileName):
    plotFileName = os.path.join(self.dirs[DKEY_PLOT], 'testGenPhotonFilter.pdf')
    lines_makefile.extend([
      "{}: phony_hadd".format(inputFileName),
      ""
      "{}: {}".format(plotFileName, inputFileName),
      "\t{} {} {}".format(self.plot_executable, inputFileName, plotFileName),
      "",
    ])
    self.targets.append(inputFileName)
    self.targets.append(plotFileName)

  def create(self):
    for sample_name, sample_info in self.samples.items():
      if not sample_info["use_it"]:
        continue
      process_name = sample_info["process_name_specific"]

      key_dir = getKey(process_name)
      for dir_type in [ DKEY_CFGS, DKEY_LOGS, DKEY_RLES, DKEY_HIST, DKEY_HADD_RT ]:
        initDict(self.dirs, [ key_dir, dir_type ])
        if dir_type in [ DKEY_CFGS, DKEY_LOGS, DKEY_HADD_RT ]:
          self.dirs[key_dir][dir_type] = os.path.join(self.get_dir_type(dir_type), dir_type, self.channel, process_name)
        else:
          self.dirs[key_dir][dir_type] = os.path.join(self.outputDir, dir_type, self.channel, process_name)

    for dir_type in [ DKEY_CFGS, DKEY_SCRIPTS, DKEY_LOGS, DKEY_HIST, DKEY_HADD_RT, DKEY_PLOT ]:
      initDict(self.dirs, [ dir_type ])
      if dir_type in [ DKEY_CFGS, DKEY_SCRIPTS, DKEY_LOGS, DKEY_HADD_RT, DKEY_PLOT ]:
        self.dirs[dir_type] = os.path.join(self.get_dir_type(dir_type), dir_type, self.channel)
      else:
        self.dirs[dir_type] = os.path.join(self.outputDir, dir_type, self.channel)

    numDirectories = 0
    for key in self.dirs.keys():
      if type(self.dirs[key]) == dict:
        numDirectories += len(self.dirs[key])
      else:
        numDirectories += 1
    logging.info("Creating directory structure (numDirectories = %i)" % numDirectories)
    numDirectories_created = 0;
    frac = 1
    for key in self.dirs.keys():
      if type(self.dirs[key]) == dict:
        for dir_type in self.dirs[key].keys():
          create_if_not_exists(self.dirs[key][dir_type])
        numDirectories_created += len(self.dirs[key])
      else:
        create_if_not_exists(self.dirs[key])
        numDirectories_created = numDirectories_created + 1
      while 100*numDirectories_created >= frac*numDirectories:
        logging.info(" %i%% completed" % frac)
        frac = frac + 1
    logging.info("Done.")

    inputFileLists = {}
    for sample_name, sample_info in self.samples.items():
      if not sample_info["use_it"]:
        continue
      logging.info("Checking input files for sample %s" % sample_info["process_name_specific"])
      inputFileLists[sample_name] = generateInputFileList(sample_info, self.max_files_per_job)

    outputFiles = { 'hadd' : [] }
    for sample_name, sample_info in self.samples.items():
      if not sample_info["use_it"]:
        continue
      process_name = sample_info["process_name_specific"]
      logging.info(
        "Creating configuration files to run '%s' for sample %s" % (self.executable_analyze, process_name)
      )
      inputFileList = inputFileLists[sample_name]

      for jobId in inputFileList.keys():
        key_analyze_dir = getKey(process_name)
        analyze_job_tuple = (process_name, jobId)
        key_analyze_job = getKey(*analyze_job_tuple)
        ntupleFiles = inputFileList[jobId]
        if len(ntupleFiles) == 0:
          print("Warning: no ntupleFiles --> skipping job !!")
          continue

        cfgFile_modified_path = os.path.join(self.dirs[key_analyze_dir][DKEY_CFGS], "analyze_%s_%i_cfg.py" % analyze_job_tuple)
        logFile_path = os.path.join(self.dirs[key_analyze_dir][DKEY_LOGS], "analyze_%s_%i.log" % analyze_job_tuple)
        histogramFile_path = os.path.join(self.dirs[key_analyze_dir][DKEY_HIST], "analyze_%s_%i.root" % analyze_job_tuple)

        self.jobOptions_analyze[key_analyze_job] = {
          'ntupleFiles'      : ntupleFiles,
          'cfgFile_modified' : cfgFile_modified_path,
          'histogramFile'    : histogramFile_path,
          'logFile'          : logFile_path,
        }
        self.createCfg_analyze(self.jobOptions_analyze[key_analyze_job], sample_info)
        outputFiles['hadd'].append(histogramFile_path)

    logging.info("Creating script for submitting '%s' jobs to batch system" % self.executable_analyze)
    self.sbatchFile_analyze = os.path.join(self.dirs[DKEY_SCRIPTS], "sbatch_analyze_%s.py" % self.channel)
    self.createScript_sbatch_analyze(self.executable_analyze, self.sbatchFile_analyze, self.jobOptions_analyze)
    outputFile = { 'hadd' : os.path.join(self.dirs[DKEY_HIST], "result.root") }
    logging.info("Creating Makefile")
    lines_makefile = []
    self.addToMakefile_analyze(lines_makefile)
    self.addToMakefile_hadd(lines_makefile, 'phony_hadd', 'phony_analyze', outputFiles, outputFile)
    self.addToMakefile_plot(lines_makefile, outputFile['hadd'])
    self.targets.extend(self.phoniesToAdd)
    self.createMakefile(lines_makefile)
    logging.info("Done.")
    return self.num_jobs
