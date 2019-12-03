from tthAnalysis.HiggsToTauTau.configs.analyzeConfig import *
from tthAnalysis.HiggsToTauTau.jobTools import create_if_not_exists
from tthAnalysis.HiggsToTauTau.analysisTools import initDict, getKey, create_cfg, generateInputFileList
from tthAnalysis.HiggsToTauTau.common import logging

class analyzeConfig_charge_flip(analyzeConfig):
  """Configuration metadata needed to run analysis in a single go.

  Sets up a folder structure by defining full path names; no directory creation is delegated here.

  See $CMSSW_BASE/src/tthAnalysis/HiggsToTauTau/python/analyzeConfig.py
  for documentation of further Args.

  """
  def __init__(self,
               configDir,
               outputDir,
               executable_analyze,
               samples,
               lepton_selections,
               jet_cleaning_by_index,
               gen_matching_by_index,
               central_or_shifts,
               max_files_per_job,
               era,
               use_lumi,
               lumi,
               check_output_files,
               running_method,
               num_parallel_jobs,
               histograms_to_fit,
               select_rle_output = False,
               verbose           = False,
               dry_run           = True,
               isDebug           = False,
               use_home          = False,
            ):
    analyzeConfig.__init__(self,
      configDir             = configDir,
      outputDir             = outputDir,
      executable_analyze    = executable_analyze,
      channel               = "charge_flip",
      samples               = samples,
      jet_cleaning_by_index = jet_cleaning_by_index,
      gen_matching_by_index = gen_matching_by_index,
      central_or_shifts     = central_or_shifts,
      max_files_per_job     = max_files_per_job,
      era                   = era,
      use_lumi              = use_lumi,
      lumi                  = lumi,
      check_output_files    = check_output_files,
      running_method        = running_method,
      num_parallel_jobs     = num_parallel_jobs,
      histograms_to_fit     = histograms_to_fit,
      triggers              = [ '1e', '2e' ],
      verbose               = verbose,
      dry_run               = dry_run,
      isDebug               = isDebug,
      use_home              = use_home,
    )

    self.prep_dcard_processesToCopy = ["data_obs", "DY", "DY_fake", "WJets", "TTbar", "Singletop", "Diboson"]
    self.prep_dcard_signals = [ "DY" ]

    self.lepton_selections = lepton_selections

    self.cfgFile_analyze_original = os.path.join(self.template_dir, "analyze_charge_flip_cfg.py")
    self.cfgFile_prep_dcard_original = os.path.join(self.template_dir, "prepareDatacards_cfg.py")
    #self.histogramDir_prep_dcard = "charge_flip_SS_Tight"
    self.select_rle_output = select_rle_output

  def createCfg_analyze(self, jobOptions, sample_info):
    """Create python configuration file for the analyze_charge_flip executable (analysis code)

    Args:
      inputFiles: list of input files (Ntuples)
      outputFile: output file of the job -- a ROOT file containing histogram
      process:
      is_mc: flag indicating whether job runs on MC (True) or data (False)
      lumi_scale: event weight (= xsection * luminosity / number of events)
      central_or_shift: either 'central' or one of the systematic uncertainties defined in $CMSSW_BASE/src/tthAnalysis/HiggsToTauTau/bin/analyze_charge_flip.cc
    """
    lines = super(analyzeConfig_charge_flip, self).createCfg_analyze(jobOptions, sample_info)
    create_cfg(self.cfgFile_analyze_original, jobOptions["cfgFile_modified"], lines)


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
        for ptEtaBin in ["BB_LL", "BB_ML", "BB_MM", "BB_HL", "BB_HM", "BB_HH", "EE_LL", "EE_ML", "EE_MM", "EE_HL", "EE_HM",
                         "EE_HH", "BE_LL", "BE_ML", "EB_ML","BE_MM",  "BE_HL", "EB_HL", "BE_HM", "EB_HM", "BE_HH", "total"]:
          lines.append("    cms.PSet(")
          lines.append("        input = cms.string('%s/%s')," % (charge, ptEtaBin))
          lines.append("        output = cms.string('ttH_%s_%s_%s')" % (self.channel, charge, ptEtaBin))
          lines.append("    ),")
      lines.append(")")
      lines.append("process.prepareDatacards.histogramToFit = cms.string('%s')" % jobOptions['histogramToFit'])
      lines.append("process.prepareDatacards.apply_automatic_rebinning = cms.bool(True)")
      lines.append("process.prepareDatacards.minEvents_automatic_rebinning = cms.double(1.0)")
      lines.append("process.prepareDatacards.sysShifts = cms.vstring(%s)" % systematics.electron_E)
      create_cfg(self.cfgFile_prep_dcard, jobOptions['cfgFile_modified'], lines)

  def create(self):
    """Creates all necessary config files and runs the complete analysis workfow -- either locally or on the batch system
    """

    for sample_name, sample_info in self.samples.items():
      if not sample_info["use_it"]:
        continue

      process_name = sample_info["process_name_specific"]
      sample_category = sample_info["sample_category"]
      is_mc = (sample_info["type"] == "mc")

      logging.info("Building dictionaries for sample %s..." % process_name)
      for lepton_selection in self.lepton_selections:
        central_or_shift_extensions = ["", "hadd", "addBackgrounds"]
        central_or_shifts_extended = central_or_shift_extensions + self.central_or_shifts
        for central_or_shift_or_dummy in central_or_shifts_extended:
          process_name_extended = [ process_name, "hadd" ]
          for process_name_or_dummy in process_name_extended:
            if central_or_shift_or_dummy in [ "hadd", "addBackgrounds" ] and process_name_or_dummy in [ "hadd" ]:
              continue
            if central_or_shift_or_dummy != "central" and central_or_shift_or_dummy not in central_or_shift_extensions:
              if not is_mc:
                continue
              if not self.accept_central_or_shift(central_or_shift_or_dummy, sample_info):
                continue

            key_dir = getKey(process_name_or_dummy, lepton_selection, central_or_shift_or_dummy)
            for dir_type in [ DKEY_CFGS, DKEY_HIST, DKEY_LOGS, DKEY_RLES ]:
              initDict(self.dirs, [ key_dir, dir_type ])
              if dir_type in [ DKEY_CFGS, DKEY_LOGS ]:
                self.dirs[key_dir][dir_type] = os.path.join(self.configDir, dir_type, self.channel,
                  "_".join([ lepton_selection ]), process_name_or_dummy, central_or_shift_or_dummy)
              else:
                self.dirs[key_dir][dir_type] = os.path.join(self.outputDir, dir_type, self.channel,
                  "_".join([ lepton_selection ]), process_name_or_dummy, central_or_shift_or_dummy)
    for subdirectory in [ "prepareDatacards" ]:
      key_dir = getKey(subdirectory)
      for dir_type in [ DKEY_CFGS, DKEY_HIST, DKEY_LOGS, DKEY_ROOT, DKEY_DCRD, DKEY_PLOT ]:
        initDict(self.dirs, [ key_dir, dir_type ])
        if dir_type in [ DKEY_CFGS, DKEY_LOGS, DKEY_DCRD, DKEY_PLOT ]:
          self.dirs[key_dir][dir_type] = os.path.join(self.configDir, dir_type, self.channel, subdirectory)
        else:
          self.dirs[key_dir][dir_type] = os.path.join(self.outputDir, dir_type, self.channel, subdirectory)
    for dir_type in [ DKEY_CFGS, DKEY_SCRIPTS, DKEY_HIST, DKEY_LOGS, DKEY_DCRD, DKEY_PLOT, DKEY_HADD_RT ]:
      initDict(self.dirs, [ dir_type ])
      if dir_type in [ DKEY_CFGS, DKEY_SCRIPTS, DKEY_LOGS, DKEY_DCRD, DKEY_PLOT, DKEY_HADD_RT ]:
        self.dirs[dir_type] = os.path.join(self.configDir, dir_type, self.channel)
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

    for lepton_selection in self.lepton_selections:
      for sample_name, sample_info in self.samples.items():
        if not sample_info["use_it"]:
          continue
        process_name = sample_info["process_name_specific"]
        
        logging.info("Creating configuration files to run '%s' for sample %s" % (self.executable_analyze, process_name))
        is_mc = (sample_info["type"] == "mc")
        inputFileList = inputFileLists[sample_name]
        for central_or_shift in self.central_or_shifts:
          if central_or_shift != "central" and not is_mc:
            continue

          # build config files for executing analysis code
          key_analyze_dir = getKey(process_name, lepton_selection, central_or_shift)

          for jobId in inputFileList.keys():
            analyze_job_tuple = (process_name, lepton_selection, central_or_shift, jobId)
            key_analyze_job = getKey(*analyze_job_tuple)
            ntupleFiles = inputFileList[jobId]
            if len(ntupleFiles) == 0:
              logging.warning("No input ntuples for %s --> skipping job !!" % (key_analyze_job))
              continue

            cfgFile_modified_path = os.path.join(self.dirs[key_analyze_dir][DKEY_CFGS], "analyze_%s_%s_%s_%i_cfg.py" % analyze_job_tuple)
            logFile_path = os.path.join(self.dirs[key_analyze_dir][DKEY_LOGS], "analyze_%s_%s_%s_%i.log" % analyze_job_tuple)
            rleOutputFile_path = os.path.join(self.dirs[key_analyze_dir][DKEY_RLES], "rle_%s_%s_%s_%i.txt" % analyze_job_tuple) \
                                 if self.select_rle_output else ""
            histogramFile_path = os.path.join(self.dirs[key_analyze_dir][DKEY_HIST], "analyze_%s_%s_%s_%i.root" % analyze_job_tuple)

            self.jobOptions_analyze[key_analyze_job] = {
              'ntupleFiles'              : ntupleFiles,
              'cfgFile_modified'         : cfgFile_modified_path,
              'histogramFile'            : histogramFile_path,
              'logFile'                  : logFile_path,
              'selEventsFileName_output' : rleOutputFile_path,
              'leptonSelection'          : lepton_selection,
              'applyFakeRateWeights'     : "disabled",
              'central_or_shift'         : central_or_shift,
              'useObjectMultiplicity'    : True,
            }
            self.createCfg_analyze(self.jobOptions_analyze[key_analyze_job], sample_info)

            # initialize input and output file names for hadd_stage1
            key_hadd_stage1_dir = getKey(process_name, lepton_selection)
            hadd_stage1_job_tuple = (process_name, lepton_selection)
            key_hadd_stage1_job = getKey(*hadd_stage1_job_tuple)
            if not key_hadd_stage1_job in self.inputFiles_hadd_stage1.keys():
              self.inputFiles_hadd_stage1[key_hadd_stage1_job] = []
            self.inputFiles_hadd_stage1[key_hadd_stage1_job].append(self.jobOptions_analyze[key_analyze_job]['histogramFile'])
            self.outputFile_hadd_stage1[key_hadd_stage1_job] = os.path.join(self.dirs[key_hadd_stage1_dir][DKEY_HIST],
                                                                            "hadd_stage1_%s_%s.root" % hadd_stage1_job_tuple)

        # initialize input and output file names for hadd_stage2
        key_hadd_stage1_job = getKey(process_name, lepton_selection)
        key_hadd_stage2_dir = getKey("hadd", lepton_selection)
        key_hadd_stage2_job = getKey(lepton_selection)
        if not key_hadd_stage2_job in self.inputFiles_hadd_stage2.keys():
          self.inputFiles_hadd_stage2[key_hadd_stage2_job] = []
        self.inputFiles_hadd_stage2[key_hadd_stage2_job].append(self.outputFile_hadd_stage1[key_hadd_stage1_job])
        self.outputFile_hadd_stage2[key_hadd_stage2_job] = os.path.join(self.dirs[key_hadd_stage2_dir][DKEY_HIST],
                                                                        "hadd_stage2_%s.root" % lepton_selection)

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
      key_hadd_stage2_job = getKey("Tight")
      key_prep_dcard_dir = getKey("prepareDatacards")
      prep_dcard_job_tuple = (self.channel, histogramToFit)
      key_prep_dcard_job = getKey(histogramToFit)
      self.jobOptions_prep_dcard[key_prep_dcard_job] = {
        'inputFile' : self.outputFile_hadd_stage2[key_hadd_stage2_job],
        'cfgFile_modified' : os.path.join(self.dirs[key_prep_dcard_dir][DKEY_CFGS], "prepareDatacards_%s_%s_cfg.py" % prep_dcard_job_tuple),
        'datacardFile' : os.path.join(self.dirs[key_prep_dcard_dir][DKEY_DCRD], "prepareDatacards_%s_%s.root" % prep_dcard_job_tuple),
        'histogramDir' : self.histogramDir_prep_dcard,
        'histogramToFit' : histogramToFit,
        'label' : None
      }
      self.createCfg_prep_dcard(self.jobOptions_prep_dcard[key_prep_dcard_job])

    if self.is_sbatch:
      logging.info("Creating script for submitting '%s' jobs to batch system" % self.executable_analyze)
      self.sbatchFile_analyze = os.path.join(self.dirs[DKEY_SCRIPTS], "sbatch_analyze_%s.py" % self.channel)
      self.createScript_sbatch_analyze(self.executable_analyze, self.sbatchFile_analyze, self.jobOptions_analyze)

    logging.info("Creating Makefile")
    lines_makefile = []
    self.addToMakefile_analyze(lines_makefile)
    self.addToMakefile_hadd_stage1(lines_makefile)
    self.addToMakefile_hadd_stage2(lines_makefile, make_dependency = "phony_hadd_stage1")
    self.addToMakefile_prep_dcard(lines_makefile)
    self.createMakefile(lines_makefile)

    logging.info("Done.")

    return self.num_jobs
