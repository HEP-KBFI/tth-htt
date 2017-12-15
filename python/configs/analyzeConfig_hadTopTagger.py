import logging

from tthAnalysis.HiggsToTauTau.configs.analyzeConfig_new import *
from tthAnalysis.HiggsToTauTau.jobTools import create_if_not_exists
from tthAnalysis.HiggsToTauTau.analysisTools import initDict, getKey, create_cfg, createFile, generateInputFileList

class analyzeConfig_hadTopTagger(analyzeConfig):
  """Configuration metadata needed to run analysis in a single go.

  Sets up a folder structure by defining full path names; no directory creation is delegated here.

  See $CMSSW_BASE/src/tthAnalysis/HiggsToTauTau/python/analyzeConfig.py
  for documentation of further Args.

  """
  def __init__(self, configDir, outputDir, executable_analyze, cfgFile_analyze, samples, changeBranchNames,
               hadTau_selection, max_files_per_job, era, use_lumi, lumi, debug, running_method, num_parallel_jobs,
               verbose = False, dry_run = False):
    analyzeConfig.__init__(self, configDir, outputDir, executable_analyze, "hadTopTagger", [ "central" ],
      max_files_per_job, era, use_lumi, lumi, debug, running_method, num_parallel_jobs,
      [], verbose = verbose, dry_run = dry_run)

    self.samples = samples
    self.changeBranchNames = changeBranchNames

    self.hadTau_selection = hadTau_selection

    self.cfgFile_analyze = os.path.join(self.template_dir, cfgFile_analyze)

  def createCfg_analyze(self, jobOptions):
    """Create python configuration file for the analyze_hadTopTagger executable (analysis code)

    Args:
      inputFiles: list of input files (Ntuples)
      outputFile: output file of the job -- a ROOT file containing histogram
    """
    lines = []
    ##lines.append("process.fwliteInput.fileNames = cms.vstring(%s)" % [ os.path.basename(inputFile) for inputFile in jobOptions['ntupleFiles'] ])
    lines.append("process.fwliteInput.fileNames = cms.vstring(%s)" % jobOptions['ntupleFiles'])
    lines.append("process.fwliteOutput.fileName = cms.string('%s')" % os.path.basename(jobOptions['histogramFile']))
    lines.append("process.analyze_hadTopTagger.process = cms.string('%s')" % jobOptions['sample_category'])
    lines.append("process.analyze_hadTopTagger.histogramDir = cms.string('analyze_hadTopTagger')")
    lines.append("process.analyze_hadTopTagger.era = cms.string('%s')" % self.era)
    lines.append("process.analyze_hadTopTagger.hadTauSelection = cms.string('%s')" % jobOptions['hadTau_selection'])
    lines.append("process.analyze_hadTopTagger.use_HIP_mitigation_mediumMuonId = cms.bool(%s)" % jobOptions['use_HIP_mitigation_mediumMuonId'])
    lines.append("process.analyze_hadTopTagger.isMC = cms.bool(%s)" % jobOptions['is_mc'])
    lines.append("process.analyze_hadTopTagger.lumiScale = cms.double(%f)" % jobOptions['lumi_scale'])
    lines.append("process.analyze_hadTopTagger.apply_genWeight = cms.bool(%s)" % jobOptions['apply_genWeight'])
    lines.append("process.analyze_hadTopTagger.selectBDT = cms.bool(%s)" % str(jobOptions['selectBDT']))
    if jobOptions['changeBranchNames']:
      lines.append("process.analyze_hadTopTagger.branchName_electrons = cms.string('Electron')")
      lines.append("process.analyze_hadTopTagger.branchName_muons = cms.string('Muon')")
      lines.append("process.analyze_hadTopTagger.branchName_hadTaus = cms.string('HadTau')")
      lines.append("process.analyze_hadTopTagger.branchName_genLeptons1 = cms.string('GenLep')")
      lines.append("process.analyze_hadTopTagger.branchName_genLeptons2 = cms.string('')")
      lines.append("process.analyze_hadTopTagger.branchName_genHadTaus = cms.string('GenHadTaus')")
      lines.append("process.analyze_hadTopTagger.branchName_genJets = cms.string('GenJet')")
      lines.append("process.analyze_hadTopTagger.redoGenMatching = cms.bool(False)")
    create_cfg(self.cfgFile_analyze, jobOptions['cfgFile_modified'], lines)

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
          self.dirs[key_dir][dir_type] = os.path.join(self.configDir, dir_type, self.channel, process_name)
        else:
          self.dirs[key_dir][dir_type] = os.path.join(self.outputDir, dir_type, self.channel, process_name)
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

    for sample_name, sample_info in self.samples.items():
      if not sample_info["use_it"] or sample_info["sample_category"] in [ "additional_signal_overlap", "background_data_estimate" ]:
        continue
      process_name = sample_info["process_name_specific"]
      logging.info("Creating configuration files to run '%s' for sample %s" % (self.executable_analyze, process_name))

      sample_category = sample_info["sample_category"]
      is_mc = (sample_info["type"] == "mc")

      inputFileList = inputFileLists[sample_name]
      for jobId in inputFileList.keys():
        ##print "processing sample %s: jobId = %i" % (process_name, jobId)

        # build config files for executing analysis code
        key_dir = getKey(process_name)
        key_analyze_job = getKey(process_name, jobId)
        ntupleFiles = inputFileList[jobId]
        if len(ntupleFiles) == 0:
          print "Warning: ntupleFiles['%s'] = %s --> skipping job !!" % (key_file, ntupleFiles)
          continue

        self.jobOptions_analyze[key_analyze_job] = {
          'ntupleFiles' : ntupleFiles,
          'cfgFile_modified' : os.path.join(self.dirs[key_dir][DKEY_CFGS], "analyze_%s_%s_%i_cfg.py" % \
             (self.channel, process_name, jobId)),
          'histogramFile' : os.path.join(self.dirs[key_dir][DKEY_HIST], "%s_%i.root" % \
             (process_name, jobId)),
          'logFile' : os.path.join(self.dirs[key_dir][DKEY_LOGS], "analyze_%s_%s_%i.log" % \
             (self.channel, process_name, jobId)),
          'sample_category' : sample_category,
          'hadTau_selection' : self.hadTau_selection,
          'use_HIP_mitigation_mediumMuonId' : True,
          'is_mc' : is_mc,
          'lumi_scale' : 1. if not (self.use_lumi and is_mc) else sample_info["xsection"] * self.lumi / sample_info["nof_events"],
          'apply_genWeight' : sample_info["genWeight"] if (is_mc and "genWeight" in sample_info) else False,
          'selectBDT' : True,
          'changeBranchNames' : self.changeBranchNames
        }
        self.createCfg_analyze(self.jobOptions_analyze[key_analyze_job])

        # initialize input and output file names for hadd_stage1
        key_hadd_stage1 = getKey(process_name)
        if not key_hadd_stage1 in self.inputFiles_hadd_stage1:
          self.inputFiles_hadd_stage1[key_hadd_stage1] = []
        self.inputFiles_hadd_stage1[key_hadd_stage1].append(self.jobOptions_analyze[key_analyze_job]['histogramFile'])
        self.outputFile_hadd_stage1[key_hadd_stage1] = os.path.join(self.dirs[DKEY_HIST], "histograms_harvested_stage1_%s_%s.root" % \
          (self.channel, process_name))
        self.targets.append(self.outputFile_hadd_stage1[key_hadd_stage1])

    if self.is_sbatch:
      logging.info("Creating script for submitting '%s' jobs to batch system" % self.executable_analyze)
      self.sbatchFile_analyze = os.path.join(self.dirs[DKEY_SCRIPTS], "sbatch_analyze_%s.py" % self.channel)
      self.createScript_sbatch_analyze(self.executable_analyze, self.sbatchFile_analyze, self.jobOptions_analyze)

    logging.info("Creating Makefile")
    lines_makefile = []
    self.addToMakefile_analyze(lines_makefile)
    self.addToMakefile_hadd_stage1(lines_makefile)
    self.createMakefile(lines_makefile)

    logging.info("Done")

    return self.num_jobs
