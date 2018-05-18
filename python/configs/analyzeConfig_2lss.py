import logging

from tthAnalysis.HiggsToTauTau.configs.analyzeConfig import *
from tthAnalysis.HiggsToTauTau.jobTools import create_if_not_exists
from tthAnalysis.HiggsToTauTau.analysisTools import initDict, getKey, create_cfg, createFile, generateInputFileList

def get_lepton_selection_and_frWeight(lepton_selection, lepton_frWeight):
  lepton_selection_and_frWeight = lepton_selection
  if lepton_selection.startswith("Fakeable"):
    if lepton_frWeight == "enabled":
      lepton_selection_and_frWeight += "_wFakeRateWeights"
    elif lepton_frWeight == "disabled":
      lepton_selection_and_frWeight += "_woFakeRateWeights"
  lepton_selection_and_frWeight = lepton_selection_and_frWeight.replace("|", "_")
  return lepton_selection_and_frWeight

def getHistogramDir(lepton_selection, lepton_frWeight, lepton_charge_selection):
  histogramDir = "2lss_%s_%s" % (lepton_charge_selection, lepton_selection)
  if lepton_selection.find("Fakeable") != -1:
    if lepton_frWeight == "enabled":
      histogramDir += "_wFakeRateWeights"
    elif lepton_frWeight == "disabled":
      histogramDir += "_woFakeRateWeights"
  return histogramDir

class analyzeConfig_2lss(analyzeConfig):
  """Configuration metadata needed to run analysis in a single go.

     Sets up a folder structure by defining full path names; no directory creation is delegated here.

     Args specific to analyzeConfig_2lss:
       lepton_selections: either `Tight`, `Loose` or `Fakeable`
       hadTauVeto_selection: either `dR05iso[Loose|Medium|Tight]` or `dR03mva[Medium|Tight|VTight|VVTight]`

     See $CMSSW_BASE/src/tthAnalysis/HiggsToTauTau/python/analyzeConfig.py
     for documentation of further Args.

  """
  def __init__(self, configDir, outputDir, executable_analyze, cfgFile_analyze, samples,
               MEMbranch, lepton_charge_selections, hadTauVeto_selection, applyFakeRateWeights, central_or_shifts,
               max_files_per_job, era, use_lumi, lumi, check_input_files, running_method, num_parallel_jobs,
               executable_addBackgrounds, executable_addFakes, executable_addFlips, histograms_to_fit,
               select_rle_output = False, executable_prep_dcard = "prepareDatacards",
               executable_add_syst_dcard = "addSystDatacards", do_sync = False, verbose = False,
               dry_run = False, isDebug = False, rle_select = '', use_nonnominal = False, hlt_filter = False,
               use_home = True):
    analyzeConfig.__init__(self, configDir, outputDir, executable_analyze, "2lss", central_or_shifts,
      max_files_per_job, era, use_lumi, lumi, check_input_files, running_method, num_parallel_jobs,
      histograms_to_fit,
      triggers = [ '1e', '1mu', '2e', '2mu', '1e1mu' ],
      executable_prep_dcard = executable_prep_dcard,
      executable_add_syst_dcard = executable_add_syst_dcard,
      do_sync = do_sync,
      verbose = verbose,
      dry_run = dry_run,
      isDebug = isDebug,
      use_home = use_home,
    )

    self.samples = samples
    self.MEMbranch = MEMbranch

    ##self.lepton_selections = [ "Tight", "Fakeable", "Fakeable_mcClosure" ]
    self.lepton_selections = [ "Tight", "Fakeable" ]
    self.lepton_frWeights = [ "enabled", "disabled" ]
    self.lepton_charge_selections = lepton_charge_selections
    self.hadTauVeto_selection_part2 = hadTauVeto_selection
    self.applyFakeRateWeights = applyFakeRateWeights

    self.lepton_genMatches = [ "2l0j", "1l1j", "0l2j" ]

    self.apply_leptonGenMatching = None
    self.lepton_genMatches_nonfakes = []
    self.lepton_genMatches_fakes = []
    if applyFakeRateWeights == "2lepton":
      self.apply_leptonGenMatching = True
      for lepton_genMatch in self.lepton_genMatches:
          if lepton_genMatch.endswith("0j"):
            self.lepton_genMatches_nonfakes.append(lepton_genMatch)
          else:
            self.lepton_genMatches_fakes.append(lepton_genMatch)
    else:
      raise ValueError("Invalid Configuration parameter 'applyFakeRateWeights' = %s !!" % applyFakeRateWeights)

    self.executable_addBackgrounds = executable_addBackgrounds
    self.executable_addFakes = executable_addFakes
    self.executable_addFlips = executable_addFlips

    self.nonfake_backgrounds = [ "TT", "TTW", "TTWW", "TTZ", "EWK", "Rares", "tH" ]

    self.prep_dcard_processesToCopy = [ "data_obs", "TTW", "TTZ", "TTWW", "EWK", "Rares", "tH", "fakes_data", "fakes_mc", "flips_data" ]
    self.make_plots_backgrounds = [ "TTW", "TTWW", "TTZ", "EWK", "Rares", "fakes_data", "flips_data" ]

    self.cfgFile_analyze = os.path.join(self.template_dir, cfgFile_analyze)
    self.inputFiles_hadd_stage1_6 = []
    self.outputFile_hadd_stage1_6 = None
    self.cfgFile_addFlips = os.path.join(self.template_dir, "addBackgroundLeptonFlips_cfg.py")
    self.jobOptions_addFlips = {}
    self.histogramDir_prep_dcard = "2lss_SS_Tight"
    self.histogramDir_prep_dcard_OS = "2lss_OS_Tight"
    self.cfgFile_make_plots = os.path.join(self.template_dir, "makePlots_2lss_cfg.py")
    self.cfgFile_make_plots_mcClosure = os.path.join(self.template_dir, "makePlots_mcClosure_2lss_cfg.py")

    self.select_rle_output = select_rle_output
    self.rle_select = rle_select
    self.use_nonnominal = use_nonnominal
    self.hlt_filter = hlt_filter

    self.isBDTtraining = False

  def set_BDT_training(self):
    """Run analysis with loose selection criteria for leptons,
       for the purpose of preparing event list files for BDT training.
    """
    self.lepton_selections = [ "forBDTtraining" ]
    self.lepton_frWeights  = [ "disabled" ]
    self.isBDTtraining     = True

  def createCfg_analyze(self, jobOptions, sample_info):
    """Create python configuration file for the analyze_2lss executable (analysis code)

       Args:
         inputFiles: list of input files (Ntuples)
         outputFile: output file of the job -- a ROOT file containing histogram
         process: either `TTW`, `TTZ`, `Rares`, `data_obs`, `ttH_hww`, `ttH_hzz` or `ttH_htt`
         is_mc: flag indicating whether job runs on MC (True) or data (False)
         lumi_scale: event weight (= xsection * luminosity / number of events)
         central_or_shift: either 'central' or one of the systematic uncertainties defined in $CMSSW_BASE/src/tthAnalysis/HiggsToTauTau/bin/analyze_2lss.cc
    """
    lepton_frWeight = "disabled" if jobOptions['applyFakeRateWeights'] == "disabled" else "enabled"
    jobOptions['histogramDir'] = getHistogramDir(jobOptions['leptonSelection'], lepton_frWeight, jobOptions['leptonChargeSelection'])
    lines = super(analyzeConfig_2lss, self).createCfg_analyze(jobOptions, sample_info)
    create_cfg(self.cfgFile_analyze, jobOptions['cfgFile_modified'], lines)

  def createCfg_addFlips(self, jobOptions):
    """Create python configuration file for the addBackgroundLeptonFlips executable (data-driven estimation of 'Flips' backgrounds)

       Args:
         inputFiles: input file (the ROOT file produced by hadd_stage1)
         outputFile: output file of the job
    """
    lines = []
    lines.append("process.fwliteInput.fileNames = cms.vstring('%s')" % jobOptions['inputFile'])
    lines.append("process.fwliteOutput.fileName = cms.string('%s')" % os.path.basename(jobOptions['outputFile']))
    lines.append("process.addBackgroundLeptonFlips.categories = cms.VPSet(")
    lines.append("    cms.PSet(")
    lines.append("        signal = cms.string('%s')," % jobOptions['category_signal'])
    lines.append("        sideband = cms.string('%s')" % jobOptions['category_sideband'])
    lines.append("    )")
    lines.append(")")
    processesToSubtract = [ "fakes_data" ]
    processesToSubtract.extend(self.nonfake_backgrounds)
    lines.append("process.addBackgroundLeptonFlips.processesToSubtract = cms.vstring(%s)" % processesToSubtract)
    lines.append("process.addBackgroundLeptonFlips.sysShifts = cms.vstring(%s)" % self.central_or_shifts)
    create_cfg(self.cfgFile_addFlips, jobOptions['cfgFile_modified'], lines)

  def createCfg_makePlots_mcClosure(self, jobOptions):
    """Fills the template of python configuration file for making control plots

       Args:
         histogramFile: name of the input ROOT file
    """
    lines = []
    lines.append("process.fwliteInput.fileNames = cms.vstring('%s')" % jobOptions['inputFile'])
    lines.append("process.makePlots_mcClosure.outputFileName = cms.string('%s')" % jobOptions['outputFile'])
    lines.append("process.makePlots_mcClosure.processesBackground = cms.vstring(%s)" % self.make_plots_backgrounds)
    lines.append("process.makePlots_mcClosure.processSignal = cms.string('%s')" % self.make_plots_signal)
    lines.append("process.makePlots_mcClosure.categories = cms.VPSet(")
    lines.append("  cms.PSet(")
    lines.append("    signal = cms.string('%s')," % jobOptions['histogramDir_signal'])
    lines.append("    sideband = cms.string('%s')," % jobOptions['histogramDir_sideband'])
    lines.append("    label = cms.string('%s')" % self.channel)
    lines.append("  )")
    lines.append(")")
    create_cfg(self.cfgFile_make_plots_mcClosure, jobOptions['cfgFile_modified'], lines)

  def addToMakefile_hadd_stage1_6(self, lines_makefile):
    """Adds the commands to Makefile that are necessary for building the intermediate histogram file
       that is used as input for data-driven background estimation.
    """
    self.addToMakefile_hadd(lines_makefile, { 'all' : self.inputFiles_hadd_stage1_6 }, { 'all' : self.outputFile_hadd_stage1_6 }, "stage1_6")

  def addToMakefile_addFlips(self, lines_makefile):
    if self.is_sbatch:
      lines_makefile.append("sbatch_addFlips: %s" % " ".join([ jobOptions['inputFile'] for jobOptions in self.jobOptions_addFlips.values() ]))
      lines_makefile.append("\t%s %s" % ("python", self.sbatchFile_addFlips))
      lines_makefile.append("")
    for jobOptions in self.jobOptions_addFlips.values():
      if self.is_makefile:
        lines_makefile.append("%s: %s" % (jobOptions['outputFile'], jobOptions['inputFile']))
        lines_makefile.append("\t%s %s &> %s" % (self.executable_addFlips, jobOptions['cfgFile_modified'], jobOptions['logFile']))
        lines_makefile.append("")
      elif self.is_sbatch:
        lines_makefile.append("%s: %s" % (jobOptions['outputFile'], "sbatch_addFlips"))
        lines_makefile.append("\t%s" % ":") # CV: null command
        lines_makefile.append("")
      self.filesToClean.append(jobOptions['outputFile'])

  def addToMakefile_backgrounds_from_data(self, lines_makefile):
    self.addToMakefile_addBackgrounds(lines_makefile, "sbatch_addBackgrounds", self.sbatchFile_addBackgrounds, self.jobOptions_addBackgrounds)
    self.addToMakefile_addBackgrounds(lines_makefile, "sbatch_addBackgrounds_sum", self.sbatchFile_addBackgrounds_sum, self.jobOptions_addBackgrounds_sum)
    self.addToMakefile_hadd_stage1_5(lines_makefile)
    self.addToMakefile_addFakes(lines_makefile)
    self.addToMakefile_hadd_stage1_6(lines_makefile)
    self.addToMakefile_addFlips(lines_makefile)

  def create(self):
    """Creates all necessary config files and runs the complete analysis workfow -- either locally or on the batch system
    """

    for sample_name, sample_info in self.samples.items():
      if not sample_info["use_it"] or sample_info["sample_category"] in [ "additional_signal_overlap", "background_data_estimate" ]:
        continue
      process_name = sample_info["process_name_specific"]
      for lepton_selection in self.lepton_selections:
        for lepton_frWeight in self.lepton_frWeights:
          if lepton_frWeight == "enabled" and not lepton_selection.startswith("Fakeable"):
            continue
          lepton_selection_and_frWeight = get_lepton_selection_and_frWeight(lepton_selection, lepton_frWeight)
          for lepton_charge_selection in self.lepton_charge_selections:
            key_dir = getKey(process_name, lepton_selection_and_frWeight, lepton_charge_selection)
            for dir_type in [ DKEY_CFGS, DKEY_HIST, DKEY_LOGS, DKEY_RLES, DKEY_SYNC ]:
              initDict(self.dirs, [ key_dir, dir_type ])
              if dir_type in [ DKEY_CFGS, DKEY_LOGS ]:
                self.dirs[key_dir][dir_type] = os.path.join(self.configDir, dir_type, self.channel,
                  "_".join([ lepton_selection_and_frWeight, lepton_charge_selection ]), process_name)
              else:
                self.dirs[key_dir][dir_type] = os.path.join(self.outputDir, dir_type, self.channel,
                  "_".join([ lepton_selection_and_frWeight, lepton_charge_selection ]), process_name)
    for dir_type in [ DKEY_CFGS, DKEY_SCRIPTS, DKEY_HIST, DKEY_LOGS, DKEY_DCRD, DKEY_PLOT, DKEY_HADD_RT, DKEY_SYNC ]:
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
      inputFileLists[sample_name] = generateInputFileList(sample_info, self.max_files_per_job, self.check_input_files)

    for lepton_selection in self.lepton_selections:
      hadTauVeto_selection = "Tight"
      hadTauVeto_selection = "|".join([ hadTauVeto_selection, self.hadTauVeto_selection_part2 ])

      if lepton_selection == "forBDTtraining":
        lepton_selection = "Loose" # "Tight" ## "Fakeable" ## Xanda FIX that

      if self.isBDTtraining : lepton_selection = "forBDTtraining" ## Xanda FIX that
      for lepton_frWeight in self.lepton_frWeights:
        if lepton_frWeight == "enabled" and not lepton_selection.startswith("Fakeable"):
          continue
        if lepton_frWeight == "disabled" and not lepton_selection in [ "Tight", "forBDTtraining" ] :
          continue
        lepton_selection_and_frWeight = get_lepton_selection_and_frWeight(lepton_selection, lepton_frWeight)

        for lepton_charge_selection in self.lepton_charge_selections:

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
                if central_or_shift != "central":
                  isFR_shape_shift = False
                  for FR_shape_shift in [
                    "CMS_ttHl_FRe_shape",
                    "CMS_ttHl_FRm_shape",
                    "CMS_ttHl_FRjt_norm",
                    "CMS_ttHl_FRjt_shape" ]:
                    if central_or_shift.find(FR_shape_shift) != -1:
                      isFR_shape_shift = True
                  if not ((lepton_selection == "Fakeable" and lepton_charge_selection == "SS" and isFR_shape_shift) or
                          (lepton_selection == "Tight"    and lepton_charge_selection == "SS")):
                    continue
                  if not is_mc and not isFR_shape_shift:
                    continue
                if central_or_shift.startswith("CMS_ttHl_thu_shape_ttH") and sample_category != "signal":
                  continue
                if central_or_shift.startswith("CMS_ttHl_thu_shape_ttW") and sample_category != "TTW":
                  continue
                if central_or_shift.startswith("CMS_ttHl_thu_shape_ttZ") and sample_category != "TTZ":
                  continue
                ##print "processing sample %s: jobId = %i, central_or_shift = '%s'" % (process_name, jobId, central_or_shift)

                # build config files for executing analysis code
                key_dir = getKey(process_name, lepton_selection_and_frWeight, lepton_charge_selection)
                key_analyze_job = getKey(process_name, lepton_selection_and_frWeight, lepton_charge_selection, central_or_shift, jobId)
                ntupleFiles = inputFileList[jobId]
                if len(ntupleFiles) == 0:
                  logging.warning("No input ntuples for %s --> skipping job !!" % (key_analyze_job))
                  continue

                syncOutput = ''
                syncTree = ''
                syncRequireGenMatching = False
                if self.do_sync:
                  if lepton_selection_and_frWeight == 'Tight':
                    if lepton_charge_selection == 'SS':
                      syncOutput = os.path.join(self.dirs[key_dir][DKEY_SYNC], '%s_SR.root' % self.channel)
                      syncTree   = 'syncTree_%s_SR' % self.channel.replace('_', '').replace('ss', 'SS')
                    elif lepton_charge_selection == 'OS':
                      syncOutput = os.path.join(self.dirs[key_dir][DKEY_SYNC], '%s_Flip.root' % self.channel)
                      syncTree   = 'syncTree_%s_Flip' % self.channel.replace('_', '').replace('ss', 'SS')
                    else:
                      continue
                    syncRequireGenMatching = True
                  elif lepton_selection_and_frWeight == 'Fakeable_wFakeRateWeights' and lepton_charge_selection == 'SS':
                    syncOutput = os.path.join(self.dirs[key_dir][DKEY_SYNC], '%s_Fake.root' % self.channel)
                    syncTree   = 'syncTree_%s_Fake' % self.channel.replace('_', '').replace('ss', 'SS')
                  else:
                    continue
                  self.inputFiles_sync['sync'].append(syncOutput)

                syncRLE = ''
                if self.do_sync and self.rle_select:
                  syncRLE = self.rle_select % syncTree
                  if not os.path.isfile(syncRLE):
                    raise ValueError('Input RLE file for the sync is missing: %s' % syncRLE)

                cfg_key = getKey(self.channel, process_name, lepton_selection_and_frWeight, lepton_charge_selection, central_or_shift, jobId)
                cfgFile_modified_path = os.path.join(self.dirs[key_dir][DKEY_CFGS], "analyze_%s_cfg.py" % cfg_key)
                logFile_path = os.path.join(self.dirs[key_dir][DKEY_LOGS], "analyze_%s.log" % cfg_key)
                rleOutputFile_path = os.path.join(self.dirs[key_dir][DKEY_RLES], "rle_%s.txt" % cfg_key) \
                  if self.select_rle_output else ""
                histogramFile_path = os.path.join(self.dirs[key_dir][DKEY_HIST], "%s.root" % key_analyze_job)
                applyFakeRateWeights = self.applyFakeRateWeights if not lepton_selection == "Tight" else "disabled"
                branchName_memOutput = '%s_%s' % (self.MEMbranch, self.get_addMEM_systematics(central_or_shift)) \
                                       if self.MEMbranch else ''

                self.jobOptions_analyze[key_analyze_job] = {
                  'ntupleFiles'              : ntupleFiles,
                  'cfgFile_modified'         : cfgFile_modified_path,
                  'histogramFile'            : histogramFile_path,
                  'logFile'                  : logFile_path,
                  'selEventsFileName_output' : rleOutputFile_path,
                  'leptonSelection'          : lepton_selection,
                  'apply_leptonGenMatching'  : self.apply_leptonGenMatching,
                  'leptonChargeSelection'    : lepton_charge_selection,
                  'hadTauSelection'          : hadTauVeto_selection,
                  'applyFakeRateWeights'     : applyFakeRateWeights,
                  'central_or_shift'         : central_or_shift,
                  'selectBDT'                : self.isBDTtraining,
                  'branchName_memOutput'     : branchName_memOutput,
                  'syncOutput'               : syncOutput,
                  'syncTree'                 : syncTree,
                  'syncRLE'                  : syncRLE,
                  'syncRequireGenMatching'   : syncRequireGenMatching,
                  'apply_hlt_filter'         : self.hlt_filter,
                  'useNonNominal'            : self.use_nonnominal,
                  'fillGenEvtHistograms'     : True,
                }
                self.createCfg_analyze(self.jobOptions_analyze[key_analyze_job], sample_info)

                # initialize input and output file names for hadd_stage1
                key_hadd_stage1 = getKey(process_name, lepton_selection_and_frWeight, lepton_charge_selection)
                if not key_hadd_stage1 in self.inputFiles_hadd_stage1:
                  self.inputFiles_hadd_stage1[key_hadd_stage1] = []
                self.inputFiles_hadd_stage1[key_hadd_stage1].append(self.jobOptions_analyze[key_analyze_job]['histogramFile'])
                self.outputFile_hadd_stage1[key_hadd_stage1] = os.path.join(self.dirs[DKEY_HIST], "histograms_harvested_stage1_%s_%s_%s_%s.root" % \
                   (self.channel, process_name, lepton_selection_and_frWeight, lepton_charge_selection))

              if self.isBDTtraining or self.do_sync:
                continue

              if is_mc:
                logging.info("Creating configuration files to run 'addBackgrounds' for sample %s" % process_name)

                sample_categories = [ sample_category ]
                if is_signal:
                  sample_categories = [ "signal", "ttH", "ttH_htt", "ttH_hww", "ttH_hzz" ]
                for sample_category in sample_categories:
                  # sum non-fake and fake contributions for each MC sample separately
                  genMatch_categories = [ "nonfake", "fake" ]
                  for genMatch_category in genMatch_categories:
                    key_hadd_stage1 = getKey(process_name, lepton_selection_and_frWeight, lepton_charge_selection)
                    key_addBackgrounds_job = None
                    processes_input = None
                    process_output = None
                    cfgFile_modified = None
                    outputFile = None
                    if genMatch_category == "nonfake":
                      # sum non-fake contributions for each MC sample separately
                      # input processes: TT2l,...
                      # output processes: TT; ...
                      if sample_category in [ "signal" ]:
                        lepton_genMatches = []
                        lepton_genMatches.extend(self.lepton_genMatches_nonfakes)
                        lepton_genMatches.extend(self.lepton_genMatches_fakes)
                        processes_input = [ "%s%s" % (sample_category, genMatch) for genMatch in lepton_genMatches ]
                      elif sample_category in [ "ttH" ]:
                        processes_input = []
                        processes_input.extend([ "%s%s" % ("ttH_htt", genMatch) for genMatch in self.lepton_genMatches_nonfakes ])
                        processes_input.extend([ "%s%s" % ("ttH_hww", genMatch) for genMatch in self.lepton_genMatches_nonfakes ])
                        processes_input.extend([ "%s%s" % ("ttH_hzz", genMatch) for genMatch in self.lepton_genMatches_nonfakes ])
                      else:
                        processes_input = [ "%s%s" % (sample_category, genMatch) for genMatch in self.lepton_genMatches_nonfakes ]
                      process_output = sample_category
                      key_addBackgrounds_job = getKey(process_name, sample_category, lepton_selection_and_frWeight, lepton_charge_selection)
                      cfgFile_modified = os.path.join(self.dirs[DKEY_CFGS], "addBackgrounds_%s_%s_%s_%s_%s_cfg.py" % \
                        (self.channel, process_name, sample_category, lepton_selection_and_frWeight, lepton_charge_selection))
                      outputFile = os.path.join(self.dirs[DKEY_HIST], "addBackgrounds_%s_%s_%s_%s_%s.root" % \
                        (self.channel, process_name, sample_category, lepton_selection_and_frWeight, lepton_charge_selection))
                    elif genMatch_category == "fake":
                      # sum fake contributions for each MC sample separately
                      # input processes: TT1l1j,TT0l2j,...
                      # output processes: TT_fake; ...
                      if sample_category in [ "signal" ]:
                        processes_input = [ "%s%s" % (sample_category, genMatch) for genMatch in self.lepton_genMatches_fakes ]
                      elif sample_category in [ "ttH" ]:
                        processes_input = []
                        processes_input.extend([ "%s%s" % ("ttH_htt", genMatch) for genMatch in self.lepton_genMatches_fakes ])
                        processes_input.extend([ "%s%s" % ("ttH_hww", genMatch) for genMatch in self.lepton_genMatches_fakes ])
                        processes_input.extend([ "%s%s" % ("ttH_hzz", genMatch) for genMatch in self.lepton_genMatches_fakes ])
                      else:
                        processes_input = [ "%s%s" % (sample_category, genMatch) for genMatch in self.lepton_genMatches_fakes ]
                      process_output = "%s_fake" % sample_category
                      key_addBackgrounds_job = getKey(process_name, "%s_fake" % sample_category, lepton_selection_and_frWeight, lepton_charge_selection)
                      cfgFile_modified = os.path.join(self.dirs[DKEY_CFGS], "addBackgrounds_%s_fakes_%s_%s_%s_%s_cfg.py" % \
                        (self.channel, process_name, sample_category, lepton_selection_and_frWeight, lepton_charge_selection))
                      outputFile = os.path.join(self.dirs[DKEY_HIST], "addBackgrounds_%s_fakes_%s_%s_%s_%s.root" % \
                        (self.channel, process_name, sample_category, lepton_selection_and_frWeight, lepton_charge_selection))
                    if processes_input:
                      logging.info(" ...for genMatch option = '%s'" % genMatch_category)
                      self.jobOptions_addBackgrounds[key_addBackgrounds_job] = {
                        'inputFile' : self.outputFile_hadd_stage1[key_hadd_stage1],
                        'cfgFile_modified' : cfgFile_modified,
                        'outputFile' : outputFile,
                        'logFile' : os.path.join(self.dirs[DKEY_LOGS], os.path.basename(cfgFile_modified).replace("_cfg.py", ".log")),
                        'categories' : [ getHistogramDir(lepton_selection, lepton_frWeight, lepton_charge_selection) ],
                        'processes_input' : processes_input,
                        'process_output' : process_output
                      }
                      self.createCfg_addBackgrounds(self.jobOptions_addBackgrounds[key_addBackgrounds_job])

                      # initialize input and output file names for hadd_stage1_5
                      key_hadd_stage1_5 = getKey(lepton_selection_and_frWeight, lepton_charge_selection)
                      if not key_hadd_stage1_5 in self.inputFiles_hadd_stage1_5:
                        self.inputFiles_hadd_stage1_5[key_hadd_stage1_5] = []
                      self.inputFiles_hadd_stage1_5[key_hadd_stage1_5].append(self.jobOptions_addBackgrounds[key_addBackgrounds_job]['outputFile'])
                      self.outputFile_hadd_stage1_5[key_hadd_stage1_5] = os.path.join(self.dirs[DKEY_HIST], "histograms_harvested_stage1_5_%s_%s_%s.root" % \
                        (self.channel, lepton_selection_and_frWeight, lepton_charge_selection))

              if self.isBDTtraining or self.do_sync:
                continue

              # add output files of hadd_stage1 for data to list of input files for hadd_stage1_5
              if not is_mc:
                key_hadd_stage1 = getKey(process_name, lepton_selection_and_frWeight, lepton_charge_selection)
                key_hadd_stage1_5 = getKey(lepton_selection_and_frWeight, lepton_charge_selection)
                if not key_hadd_stage1_5 in self.inputFiles_hadd_stage1_5:
                  self.inputFiles_hadd_stage1_5[key_hadd_stage1_5] = []
                self.inputFiles_hadd_stage1_5[key_hadd_stage1_5].append(self.outputFile_hadd_stage1[key_hadd_stage1])

          if self.isBDTtraining or self.do_sync:
            continue

          # sum fake contributions for the total of all MC samples
          # input processes: TT1l1j,TT0l2j,...
          # output process: fakes_mc
          key_addBackgrounds_job = getKey(lepton_selection_and_frWeight, lepton_charge_selection)
          sample_categories = []
          sample_categories.extend(self.nonfake_backgrounds)
          sample_categories.extend([ "signal" ])
          processes_input = []
          for sample_category in sample_categories:
            processes_input.append("%s_fake" % sample_category)
          self.jobOptions_addBackgrounds_sum[key_addBackgrounds_job] = {
            'inputFile' : self.outputFile_hadd_stage1_5[key_hadd_stage1_5],
            'cfgFile_modified' : os.path.join(self.dirs[DKEY_CFGS], "addBackgrounds_%s_fakes_mc_%s_%s_cfg.py" % \
              (self.channel, lepton_selection_and_frWeight, lepton_charge_selection)),
            'outputFile' : os.path.join(self.dirs[DKEY_HIST], "addBackgrounds_%s_fakes_mc_%s_%s.root" % \
              (self.channel, lepton_selection_and_frWeight, lepton_charge_selection)),
            'logFile' : os.path.join(self.dirs[DKEY_LOGS], "addBackgrounds_%s_fakes_mc_%s_%s.log" % \
              (self.channel, lepton_selection_and_frWeight, lepton_charge_selection)),
            'categories' : [ getHistogramDir(lepton_selection, lepton_frWeight, lepton_charge_selection) ],
            'processes_input' : processes_input,
            'process_output' : "fakes_mc"
          }
          self.createCfg_addBackgrounds(self.jobOptions_addBackgrounds_sum[key_addBackgrounds_job])

          # initialize input and output file names for hadd_stage2
          key_hadd_stage2 = getKey(lepton_selection_and_frWeight, lepton_charge_selection)
          if not key_hadd_stage2 in self.inputFiles_hadd_stage2:
            self.inputFiles_hadd_stage2[key_hadd_stage2] = []
          if lepton_selection == "Tight":
            self.inputFiles_hadd_stage2[key_hadd_stage2].append(self.jobOptions_addBackgrounds_sum[key_addBackgrounds_job]['outputFile'])
          key_hadd_stage1_5 = getKey(lepton_selection_and_frWeight, lepton_charge_selection)
          self.inputFiles_hadd_stage2[key_hadd_stage2].append(self.outputFile_hadd_stage1_5[key_hadd_stage1_5])
          self.outputFile_hadd_stage2[key_hadd_stage2] = os.path.join(self.dirs[DKEY_HIST], "histograms_harvested_stage2_%s_%s_%s.root" % \
              (self.channel, lepton_selection_and_frWeight, lepton_charge_selection))

    if self.isBDTtraining or self.do_sync:
      if self.is_sbatch:
        logging.info("Creating script for submitting '%s' jobs to batch system" % self.executable_analyze)
        self.sbatchFile_analyze = os.path.join(self.dirs[DKEY_SCRIPTS], "sbatch_analyze_%s.py" % self.channel)
        if self.isBDTtraining:
          self.createScript_sbatch_analyze(self.executable_analyze, self.sbatchFile_analyze, self.jobOptions_analyze)
        elif self.do_sync:
          self.createScript_sbatch_syncNtuple(self.executable_analyze, self.sbatchFile_analyze, self.jobOptions_analyze)
      logging.info("Creating Makefile")
      lines_makefile = []
      if self.isBDTtraining:
        self.addToMakefile_analyze(lines_makefile)
        self.addToMakefile_hadd_stage1(lines_makefile)
      elif self.do_sync:
        self.addToMakefile_syncNtuple(lines_makefile)
        outputFile_sync_path = os.path.join(self.outputDir, DKEY_SYNC, '%s.root' % self.channel)
        self.outputFile_sync['sync'] = outputFile_sync_path
        self.targets.append(outputFile_sync_path)
        self.addToMakefile_hadd_sync(lines_makefile)
      else:
        raise ValueError("Internal logic error")
      self.createMakefile(lines_makefile)
      logging.info("Done")
      return self.num_jobs

    logging.info("Creating configuration files to run 'addBackgroundFakes'")
    for lepton_charge_selection in self.lepton_charge_selections:
      key_addFakes_job = getKey("fakes_data", lepton_charge_selection)
      key_hadd_stage1_5 = getKey(get_lepton_selection_and_frWeight("Fakeable", "enabled"), lepton_charge_selection)
      category_sideband = None
      if self.applyFakeRateWeights == "2lepton":
        category_sideband = "2lss_%s_Fakeable_wFakeRateWeights" % lepton_charge_selection
      else:
        raise ValueError("Invalid Configuration parameter 'applyFakeRateWeights' = %s !!" % applyFakeRateWeights)
      self.jobOptions_addFakes[key_addFakes_job] = {
        'inputFile' : self.outputFile_hadd_stage1_5[key_hadd_stage1_5],
        'cfgFile_modified' : os.path.join(self.dirs[DKEY_CFGS], "addBackgroundLeptonFakes_%s_%s_cfg.py" % \
          (self.channel, lepton_charge_selection)),
        'outputFile' : os.path.join(self.dirs[DKEY_HIST], "addBackgroundLeptonFakes_%s_%s.root" % \
          (self.channel, lepton_charge_selection)),
        'logFile' : os.path.join(self.dirs[DKEY_LOGS], "addBackgroundLeptonFakes_%s_%s.log" % \
          (self.channel, lepton_charge_selection)),
        'category_signal' : "2lss_%s_Tight" % lepton_charge_selection,
        'category_sideband' : category_sideband
      }
      self.createCfg_addFakes(self.jobOptions_addFakes[key_addFakes_job])
      key_hadd_stage2 = getKey(get_lepton_selection_and_frWeight("Tight", "disabled"), lepton_charge_selection)
      self.inputFiles_hadd_stage2[key_hadd_stage2].append(self.jobOptions_addFakes[key_addFakes_job]['outputFile'])

    #--------------------------------------------------------------------------
    # CV: add histograms in OS and SS regions,
    #     so that "fakes_data" background can be subtracted from OS control region used to estimate charge flip background
    key_addFakes_job = getKey("fakes_data", "OS")
    self.inputFiles_hadd_stage1_6.append(self.jobOptions_addFakes[key_addFakes_job]['outputFile'])
    key_hadd_stage1_5 = getKey(get_lepton_selection_and_frWeight("Tight", "disabled"), "OS")
    self.inputFiles_hadd_stage1_6.append(self.outputFile_hadd_stage1_5[key_hadd_stage1_5])
    self.outputFile_hadd_stage1_6 = os.path.join(self.dirs[DKEY_HIST], "histograms_harvested_stage1_6_%s_Tight_SS.root" % self.channel)
    #--------------------------------------------------------------------------

    logging.info("Creating configuration files to run 'addBackgroundFlips'")
    key_addFlips_job = getKey("flips_data")
    self.inputFiles_hadd_stage1_6.append(self.jobOptions_addFakes[key_addFakes_job]['outputFile'])
    self.jobOptions_addFlips[key_addFlips_job] = {
      'inputFile' : self.outputFile_hadd_stage1_6,
      'cfgFile_modified' : os.path.join(self.dirs[DKEY_CFGS], "addBackgroundLeptonFlips_%s_cfg.py" % self.channel),
      'outputFile' : os.path.join(self.dirs[DKEY_HIST], "addBackgroundLeptonFlips_%s.root" % self.channel),
      'logFile' : os.path.join(self.dirs[DKEY_LOGS], "addBackgroundLeptonFlips_%s.log" % self.channel),
      'category_signal' : "2lss_SS_Tight",
      'category_sideband' : "2lss_OS_Tight"
    }
    self.createCfg_addFlips(self.jobOptions_addFlips[key_addFlips_job])
    key_hadd_stage2 = getKey(get_lepton_selection_and_frWeight("Tight", "disabled"), "SS")
    self.inputFiles_hadd_stage2[key_hadd_stage2].append(self.jobOptions_addFlips[key_addFlips_job]['outputFile'])

    logging.info("Creating configuration files to run 'prepareDatacards'")
    for histogramToFit in self.histograms_to_fit:
      key_prep_dcard_job = getKey(histogramToFit)
      key_hadd_stage2 = getKey(get_lepton_selection_and_frWeight("Tight", "disabled"), "SS")
      self.jobOptions_prep_dcard[key_prep_dcard_job] = {
        'inputFile' : self.outputFile_hadd_stage2[key_hadd_stage2],
        'cfgFile_modified' : os.path.join(self.dirs[DKEY_CFGS], "prepareDatacards_%s_%s_cfg.py" % (self.channel, histogramToFit)),
        'datacardFile' : os.path.join(self.dirs[DKEY_DCRD], "prepareDatacards_%s_%s.root" % (self.channel, histogramToFit)),
        'histogramDir' : self.histogramDir_prep_dcard,
        'histogramToFit' : histogramToFit,
        'label' : None
      }
      self.createCfg_prep_dcard(self.jobOptions_prep_dcard[key_prep_dcard_job])

      # add shape templates for the following systematic uncertainties:
      #  - 'CMS_ttHl_Clos_e'
      #  - 'CMS_ttHl_Clos_m'
      #  - 'CMS_ttHl_FRe_shape_2lss_anticorr1', 'CMS_ttHl_FRe_shape_2lss_corr1'
      #  - 'CMS_ttHl_FRm_shape_2lss_anticorr1', 'CMS_ttHl_FRm_shape_2lss_corr1'
      key_add_syst_dcard_job = getKey(histogramToFit)
      self.jobOptions_add_syst_dcard[key_add_syst_dcard_job] = {
        'inputFile' : self.jobOptions_prep_dcard[key_prep_dcard_job]['datacardFile'],
        'cfgFile_modified' : os.path.join(self.dirs[DKEY_CFGS], "addSystDatacards_%s_%s_cfg.py" % (self.channel, histogramToFit)),
        'outputFile' : os.path.join(self.dirs[DKEY_DCRD], "addSystDatacards_%s_%s.root" % (self.channel, histogramToFit)),
        'category' : self.channel,
        'histogramToFit' : histogramToFit
      }
      self.createCfg_add_syst_dcard(self.jobOptions_add_syst_dcard[key_add_syst_dcard_job])

      logging.info("Creating configuration files to run 'makePlots'")
      key_makePlots_job = getKey("SS")
      key_hadd_stage2 = getKey(get_lepton_selection_and_frWeight("Tight", "disabled"), "SS")
      self.jobOptions_make_plots[key_makePlots_job] = {
        'executable' : self.executable_make_plots,
        'inputFile' : self.outputFile_hadd_stage2[key_hadd_stage2],
        'cfgFile_modified' : os.path.join(self.dirs[DKEY_CFGS], "makePlots_%s_cfg.py" % self.channel),
        'outputFile' : os.path.join(self.dirs[DKEY_PLOT], "makePlots_%s.png" % self.channel),
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
        key_hadd_stage2 = getKey(get_lepton_selection_and_frWeight("Tight", "disabled"), "OS")
        self.jobOptions_make_plots[key_makePlots_job] = {
          'executable' : self.executable_make_plots,
          'inputFile' : self.outputFile_hadd_stage2[key_hadd_stage2],
          'cfgFile_modified' : os.path.join(self.dirs[DKEY_CFGS], "makePlots_%s_OS_cfg.py" % self.channel),
          'outputFile' : os.path.join(self.dirs[DKEY_PLOT], "makePlots_%s_OS.png" % self.channel),
          'histogramDir' : self.histogramDir_prep_dcard_OS,
          'label' : "OS",
          'make_plots_backgrounds' : make_plots_backgrounds
        }
        self.createCfg_makePlots(self.jobOptions_make_plots[key_makePlots_job])
      if "Fakeable_mcClosure" in self.lepton_selections:
        key_makePlots_job = getKey("SS")
        key_hadd_stage2 = getKey(get_lepton_selection_and_frWeight("Tight", "disabled"), "SS")
        self.jobOptions_make_plots[key_makePlots_job] = {
          'executable' : self.executable_make_plots_mcClosure,
          'inputFile' : self.outputFile_hadd_stage2[key_hadd_stage2],
          'cfgFile_modified' : os.path.join(self.dirs[DKEY_CFGS], "makePlots_mcClosure_%s_cfg.py" % self.channel),
          'outputFile' : os.path.join(self.dirs[DKEY_PLOT], "makePlots_mcClosure_%s.png" % self.channel),
          'histogramDir_signal' : self.histogramDir_prep_dcard,
          'histogramDir_sideband' : (self.histogramDir_prep_dcard.replace("Tight", "Fakeable_mcClosure_wFakeRateWeights"))
        }
        self.createCfg_makePlots_mcClosure(self.jobOptions_make_plots[key_makePlots_job])

    if self.is_sbatch:
      logging.info("Creating script for submitting '%s' jobs to batch system" % self.executable_analyze)
      self.sbatchFile_analyze = os.path.join(self.dirs[DKEY_SCRIPTS], "sbatch_analyze_%s.py" % self.channel)
      self.createScript_sbatch_analyze(self.executable_analyze, self.sbatchFile_analyze, self.jobOptions_analyze)
      logging.info("Creating script for submitting '%s' jobs to batch system" % self.executable_addBackgrounds)
      self.sbatchFile_addBackgrounds = os.path.join(self.dirs[DKEY_SCRIPTS], "sbatch_addBackgrounds_%s.py" % self.channel)
      self.createScript_sbatch(self.executable_addBackgrounds, self.sbatchFile_addBackgrounds, self.jobOptions_addBackgrounds)
      self.sbatchFile_addBackgrounds_sum = os.path.join(self.dirs[DKEY_SCRIPTS], "sbatch_addBackgrounds_%s.py" % self.channel)
      self.createScript_sbatch(self.executable_addBackgrounds, self.sbatchFile_addBackgrounds_sum, self.jobOptions_addBackgrounds_sum)
      logging.info("Creating script for submitting '%s' jobs to batch system" % self.executable_addFakes)
      self.sbatchFile_addFakes = os.path.join(self.dirs[DKEY_SCRIPTS], "sbatch_addFakes_%s.py" % self.channel)
      self.createScript_sbatch(self.executable_addFakes, self.sbatchFile_addFakes, self.jobOptions_addFakes)
      logging.info("Creating script for submitting '%s' jobs to batch system" % self.executable_addFlips)
      self.sbatchFile_addFlips = os.path.join(self.dirs[DKEY_SCRIPTS], "sbatch_addFlips_%s.py" % self.channel)
      self.createScript_sbatch(self.executable_addFlips, self.sbatchFile_addFlips, self.jobOptions_addFlips)

    logging.info("Creating Makefile")
    lines_makefile = []
    self.addToMakefile_analyze(lines_makefile)
    self.addToMakefile_hadd_stage1(lines_makefile)
    self.addToMakefile_backgrounds_from_data(lines_makefile)
    self.addToMakefile_hadd_stage2(lines_makefile)
    self.addToMakefile_prep_dcard(lines_makefile)
    self.addToMakefile_add_syst_dcard(lines_makefile)
    self.addToMakefile_make_plots(lines_makefile)
    self.createMakefile(lines_makefile)

    logging.info("Done")

    return self.num_jobs
