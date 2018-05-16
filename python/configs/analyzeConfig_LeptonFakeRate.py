import logging, jinja2, codecs, os

from tthAnalysis.HiggsToTauTau.configs.analyzeConfig import *
from tthAnalysis.HiggsToTauTau.jobTools import create_if_not_exists, add_chmodX
from tthAnalysis.HiggsToTauTau.analysisTools import initDict, getKey, create_cfg, createFile, generateInputFileList

jinja_template_dir = os.path.join(
  os.getenv('CMSSW_BASE'), 'src', 'tthAnalysis', 'HiggsToTauTau', 'python', 'templates'
)
DKEY_COMBINE_OUTPUT="combine_output"

jinja2.filters.FILTERS['os.path.basename'] = os.path.basename

def getBinName(label, minValue, maxValue):
  binName = ''
  if minValue > 0. and maxValue > 0.:
    binName = '%s%1.1fto%1.1f' % (label, minValue, maxValue)
  elif minValue > 0.:
    binName = '%sGt%1.1f' % (label, minValue)
  elif maxValue > 0.:
    binName = '%sLt%1.1f' % (label, maxValue)
  binName = binName.replace('.', '_')
  return binName

def getEtaBin(minAbsEta, maxAbsEta):
  return getBinName("absEta", minAbsEta, maxAbsEta)

def getPtBin(minPt, maxPt):
  return getBinName("Pt", minPt, maxPt)

fit_param_range_map = {
  'electron' : {
    'tight' : {
      'incl'                            : '0.01,10.0',
      'absEtaLt1_5_Pt15_0to20_0'        : '0.01,10.0',
      'absEtaLt1_5_Pt20_0to30_0'        : '0.01,10.0',
      'absEtaLt1_5_Pt30_0to45_0'        : '0.01,10.0',
      'absEtaLt1_5_Pt45_0to65_0'        : '0.01,10.0',
      'absEtaLt1_5_Pt65_0to100000_0'    : '0.01,10.0',
      'absEta1_5to9_9_Pt15_0to20_0'     : '0.01,10.0',
      'absEta1_5to9_9_Pt20_0to30_0'     : '0.0,10.0',  ## CHANGED TO MAKE FIT CONVERGE
      'absEta1_5to9_9_Pt30_0to45_0'     : '0.01,10.0',
      'absEta1_5to9_9_Pt45_0to65_0'     : '0.01,10.0',
      'absEta1_5to9_9_Pt65_0to100000_0' : '0.01,10.0',
    },
    'fakeable' : {
      'incl'                            : '0.01,10.0',
      'absEtaLt1_5_Pt15_0to20_0'        : '0.01,10.0',
      'absEtaLt1_5_Pt20_0to30_0'        : '0.01,10.0',
      'absEtaLt1_5_Pt30_0to45_0'        : '0.01,10.0',
      'absEtaLt1_5_Pt45_0to65_0'        : '0.01,10.0',
      'absEtaLt1_5_Pt65_0to100000_0'    : '0.01,10.0',
      'absEta1_5to9_9_Pt15_0to20_0'     : '0.01,10.0',
      'absEta1_5to9_9_Pt20_0to30_0'     : '0.01,10.0',
      'absEta1_5to9_9_Pt30_0to45_0'     : '0.01,10.0',
      'absEta1_5to9_9_Pt45_0to65_0'     : '0.01,10.0',
      'absEta1_5to9_9_Pt65_0to100000_0' : '0.01,10.0',
    },
  },
  'muon' : {
    'tight' : {
      'incl'                            : '0.01,10.0',
      'absEtaLt1_5_Pt10_0to15_0'        : '0.01,10.0',
      'absEtaLt1_5_Pt15_0to20_0'        : '0.01,10.0',
      'absEtaLt1_5_Pt20_0to30_0'        : '0.01,10.0',
      'absEtaLt1_5_Pt30_0to45_0'        : '0.01,10.0',
      'absEtaLt1_5_Pt45_0to65_0'        : '0.01,10.0',
      'absEtaLt1_5_Pt65_0to100000_0'    : '0.01,10.0',
      'absEta1_5to9_9_Pt10_0to15_0'     : '0.01,10.0',
      'absEta1_5to9_9_Pt15_0to20_0'     : '0.01,10.0',
      'absEta1_5to9_9_Pt20_0to30_0'     : '0.01,10.0',
      'absEta1_5to9_9_Pt30_0to45_0'     : '0.01,10.0',
      'absEta1_5to9_9_Pt45_0to65_0'     : '0.01,10.0',
      'absEta1_5to9_9_Pt65_0to100000_0' : '0.01,10.0',
    },
    'fakeable' : {
      'incl'                            : '0.01,10.0',
      'absEtaLt1_5_Pt10_0to15_0'        : '0.01,10.0',
      'absEtaLt1_5_Pt15_0to20_0'        : '0.01,10.0',
      'absEtaLt1_5_Pt20_0to30_0'        : '0.01,10.0',
      'absEtaLt1_5_Pt30_0to45_0'        : '0.01,10.0',
      'absEtaLt1_5_Pt45_0to65_0'        : '0.01,10.0',
      'absEtaLt1_5_Pt65_0to100000_0'    : '0.01,10.0',
      'absEta1_5to9_9_Pt10_0to15_0'     : '0.01,10.0',
      'absEta1_5to9_9_Pt15_0to20_0'     : '0.01,10.0',
      'absEta1_5to9_9_Pt20_0to30_0'     : '0.01,10.0',
      'absEta1_5to9_9_Pt30_0to45_0'     : '0.01,10.0',
      'absEta1_5to9_9_Pt45_0to65_0'     : '0.01,10.0',
      'absEta1_5to9_9_Pt65_0to100000_0' : '0.01,10.0',
    }
  }
}

def construct_lepton_params(lepton, lepton_short, selection, absEtaPtBinString, error_msg):
  if absEtaPtBinString not in fit_param_range_map[lepton][selection]:
    raise ValueError(error_msg)
  lepton_id = '%ss_%s_%s' % (lepton, selection, absEtaPtBinString)
  lepton_id_short = lepton_id.replace('%ss_' % lepton, '%s_' % lepton_short)
  lepton_range = fit_param_range_map[lepton][selection][absEtaPtBinString]
  return (lepton_id_short, lepton_range, lepton_id)

category_template = """{% for input, output in categories %}
  cms.PSet(
    input = cms.string("{{ input }}"),
    output = cms.string("{{ output }}"),
  ),{% endfor %}
"""

class analyzeConfig_LeptonFakeRate(analyzeConfig):
  """Configuration metadata needed to run analysis in a single go.

  Sets up a folder structure by defining full path names; no directory creation is delegated here.

  Args specific to analyzeConfig_LeptonFakeRate:
    charge_selection: either `OS` or `SS` (opposite-sign or same-sign of the electron+muon pair)
    hadTau_selections: list of tau ID discriminators to check

  See $CMSSW_BASE/src/tthAnalysis/HiggsToTauTau/python/analyzeConfig.py
  for documentation of further Args.

  """
  def __init__(self, configDir, outputDir, cmssw_base_dir_combine, executable_analyze, samples,
               absEtaBins_e, absEtaBins_mu, ptBins_e, ptBins_mu, fillGenEvtHistograms, central_or_shifts,
               numerator_histogram, denominator_histogram, prep_dcard,
               max_files_per_job, era, use_lumi, lumi, check_input_files, running_method, num_parallel_jobs,
               executable_addBackgrounds, executable_addBackgrounds_recursively, executable_addBackgrounds_LeptonFakeRate,
               executable_prep_dcard, executable_comp_LeptonFakeRate, select_rle_output = False,
               verbose = False, dry_run = False, isDebug = False, use_home = True):
    analyzeConfig.__init__(self, configDir, outputDir, executable_analyze, "LeptonFakeRate", central_or_shifts,
      max_files_per_job, era, use_lumi, lumi, check_input_files, running_method, num_parallel_jobs,
      [ numerator_histogram, denominator_histogram ],
      executable_prep_dcard = executable_prep_dcard, triggers = [ '1e', '1mu', '2e', '2mu' ],
      verbose = verbose, dry_run = dry_run, isDebug = isDebug, use_home = use_home)

    self.cmssw_base_dir_combine = cmssw_base_dir_combine
    if not os.path.isdir(os.path.join(cmssw_base_dir_combine, 'src', 'CombineHarvester')) or \
       not os.path.isdir(os.path.join(cmssw_base_dir_combine, 'src', 'HiggsAnalysis', 'CombinedLimit')):
      raise ValueError('CMSSW path for combine not valid: %s' % self.cmssw_base_dir_combine)

    self.samples = samples

    self.absEtaBins_e = absEtaBins_e
    self.ptBins_e = ptBins_e
    self.absEtaBins_mu = absEtaBins_mu
    self.ptBins_mu = ptBins_mu

    self.cfgFile_analyze = os.path.join(self.template_dir, "analyze_LeptonFakeRate_cfg.py")
    self.fillGenEvtHistograms = fillGenEvtHistograms

    self.executable_addBackgrounds = executable_addBackgrounds
    self.executable_addBackgrounds_recursively = executable_addBackgrounds_recursively
    self.executable_addBackgrounds_LeptonFakeRate = executable_addBackgrounds_LeptonFakeRate
    self.cfgFile_addBackgrounds_LeptonFakeRate = os.path.join(self.template_dir, "addBackground_LeptonFakeRate_cfg.py")
    self.jobOptions_addBackgrounds_LeptonFakeRate = {}

    self.executable_prep_dcard = executable_prep_dcard
    self.cfgFile_prep_dcard = os.path.join(self.template_dir, "prepareDatacards_LeptonFakeRate_cfg.py")
    self.executable_comp_LeptonFakeRate = executable_comp_LeptonFakeRate
    self.cfgFile_comp_LeptonFakeRate = os.path.join(self.template_dir, "comp_LeptonFakeRate_cfg.py")
    self.jobOptions_comp_LeptonFakeRate = {}

    self.nonfake_backgrounds = [ "TT", "TTW", "TTZ", "TTWW", "EWK", "Rares", "tH" ]
    self.prep_dcard_processesToCopy = [ "data_obs", "TTW", "TTZ", "TT", "Rares", "EWK", "signal", "TTWW", "tH", "ttH_hbb", "fakes_data" ]
    self.histogramDir_prep_dcard = "LeptonFakeRate"
    self.prep_dcard = prep_dcard

    self.numerator_histogram = numerator_histogram[0]
    self.denominator_histogram = denominator_histogram[0]
    self.histograms_to_fit = [ self.numerator_histogram, self.denominator_histogram ]
    self.numerator_plotLabel = numerator_histogram[1]
    self.denominator_plotLabel = denominator_histogram[1]

    self.select_rle_output = select_rle_output

    self.jobOptions_combine = {}

  def createCfg_analyze(self, jobOptions, sample_info):
    """Create python configuration file for the analyze_LeptonFakeRate executable (analysis code)

    Args:
      inputFiles: list of input files (Ntuples)
      outputFile: output file of the job -- a ROOT file containing histogram
      process: either `TT`, `TTW`, `TTZ`, `EWK`, `Rares`, `data_obs`, `ttH_hww`, `ttH_hzz` or `ttH_htt`
      is_mc: flag indicating whether job runs on MC (True) or data (False)
      lumi_scale: event weight (= xsection * luminosity / number of events)
      central_or_shift: either 'central' or one of the systematic uncertainties defined in $CMSSW_BASE/src/tthAnalysis/HiggsToTauTau/bin/analyze_LeptonFakeRate.cc
    """
    additionalJobOptions = [
      'absEtaBins_e',
      'ptBins_e',
      'absEtaBins_mu',
      'ptBins_mu',
    ]
    lines = super(analyzeConfig_LeptonFakeRate, self).createCfg_analyze(
      jobOptions, sample_info, additionalJobOptions, isLeptonFR = True
    )
    create_cfg(self.cfgFile_analyze, jobOptions['cfgFile_modified'], lines)

  def createCfg_addBackgrounds_LeptonFakeRate(self, jobOptions):
    """Create python configuration file for the addBackgrounds executable (sum either all "fake" or all "non-fake" contributions)
    Args:
      inputFiles: input file (the ROOT file produced by hadd_stage1)
      outputFile: output file of the job
    """
    lines = []
    lines.append("process.fwliteInput.fileNames = cms.vstring('%s')" % jobOptions['inputFile'])
    lines.append("process.fwliteOutput.fileName = cms.string('%s')" % os.path.basename(jobOptions['outputFile']))
    # lines.append("process.addBackgrounds.categories = cms.vstring(%s)" % jobOptions['categories'])
    # lines.append("process.addBackgrounds.processes_input = cms.vstring(%s)" % jobOptions['processes_input'])
    # lines.append("process.addBackgrounds.process_output = cms.string('%s')" % jobOptions['process_output'])
    logging.info("self.cfgFile_addBackgrounds_LeptonFakeRate => %s" % self.cfgFile_addBackgrounds_LeptonFakeRate)
    logging.info("jobOptions['cfgFile_modified'] => %s" % jobOptions['cfgFile_modified'])
    create_cfg(self.cfgFile_addBackgrounds_LeptonFakeRate, jobOptions['cfgFile_modified'], lines)

  def createCfg_comp_LeptonFakeRate(self, jobOptions):
    """Create python configuration file for the comp_LeptonFakeRate executable

    Args:
      inputFiles: input file (the ROOT file produced by hadd_stage1)
      outputFile: output file of the job
    """
    lines = []
    lines.append("process.fwliteInput.fileNames = cms.vstring(%s)" % jobOptions['inputFile'])
    lines.append("process.fwliteOutput.fileName = cms.string('%s')" % jobOptions['outputFile'])
    lines.append("process.comp_LeptonFakeRate.absEtaBins_e = cms.vdouble(%s)" % jobOptions['absEtaBins_e'])
    lines.append("process.comp_LeptonFakeRate.ptBins_e = cms.vdouble(%s)" % jobOptions['ptBins_e'])
    lines.append("process.comp_LeptonFakeRate.absEtaBins_mu = cms.vdouble(%s)" % jobOptions['absEtaBins_mu'])
    lines.append("process.comp_LeptonFakeRate.ptBins_mu = cms.vdouble(%s)" % jobOptions['ptBins_mu'])
    lines.append("process.comp_LeptonFakeRate.outputFileName = cms.string('%s')" % jobOptions['plots_outputFileName'])
    create_cfg(self.cfgFile_comp_LeptonFakeRate, jobOptions['cfgFile_modified'], lines)

  def createCfg_prep_dcard_LeptonFakeRate(self, jobOptions):
    """
    Fills the template of python configuration file for datacard preparation
    Args:
      histogramToFit: name of the histogram used for signal extraction
      """
    category_output = self.channel
    if jobOptions['label']:
      category_output += "_%s" % jobOptions['label']
    lines = []
    lines.append("process.fwliteInput.fileNames = cms.vstring('%s')" % jobOptions['inputFile'])
    lines.append("process.fwliteOutput.fileName = cms.string('%s')" % jobOptions['datacardFile'])
    lines.append("process.prepareDatacards.histogramToFit = cms.string('%s')" % jobOptions['histogramToFit'])
    if jobOptions['histogramToFit'] in [ "mT_fix_L" ]:
      lines.append("process.prepareDatacards.histogramToFit_xMin = cms.double(0.)")
      lines.append("process.prepareDatacards.histogramToFit_xMax = cms.double(150.)")
      lines.append("process.prepareDatacards.minEvents_automatic_rebinning = cms.double(10.)")
    category_entries = jinja2.Template(category_template).render(categories = jobOptions['categories'])
    lines.append(
      "process.prepareDatacards.categories = cms.VPSet(%s\n)" % category_entries
    )
    lines.append(
      "process.prepareDatacards.sysShifts = cms.vstring(\n  %s,\n)" % \
      ',\n  '.join(map(lambda central_or_shift: "'%s'" % central_or_shift, self.central_or_shifts))
    )
    create_cfg(self.cfgFile_prep_dcard, jobOptions['cfgFile_modified'], lines)

  def addToMakefile_backgrounds_from_data(self, lines_makefile):
    self.addToMakefile_hadd_stage1_5(lines_makefile)
    self.addToMakefile_addBackgrounds(lines_makefile, "sbatch_addBackgrounds_sum", self.sbatchFile_addBackgrounds_sum, self.jobOptions_addBackgrounds_sum)
    self.addToMakefile_addBackgrounds(lines_makefile, "sbatch_addBackgrounds_LeptonFakeRate", self.sbatchFile_addBackgrounds_LeptonFakeRate, self.jobOptions_addBackgrounds_LeptonFakeRate)

  def addToMakefile_combine(self, lines_makefile):
    jobOptions = self.jobOptions_combine
    lines_makefile.append("%s: %s" % (jobOptions['outputFile'], jobOptions['inputFile']))
    lines_makefile.append("\tmake -f %s clean" % jobOptions['makefile_path'])
    lines_makefile.append("\tmake -f %s -j16 &> %s" % (jobOptions['makefile_path'], jobOptions['logFile']))
    lines_makefile.append("")
    self.filesToClean.append(jobOptions['outputFile'])

  def addToMakefile_comp_LeptonFakeRate(self, lines_makefile):
    if self.is_sbatch:
      lines_makefile.append("sbatch_comp_LeptonFakeRate: %s" % " ".join([ " ".join(jobOptions['inputFile']) for jobOptions in self.jobOptions_comp_LeptonFakeRate.values() ]))
      lines_makefile.append("\t%s %s" % ("python", self.sbatchFile_comp_LeptonFakeRate))
      lines_makefile.append("")
    for jobOptions in self.jobOptions_comp_LeptonFakeRate.values():
      if self.is_makefile:
        lines_makefile.append("%s: %s" % (jobOptions['outputFile'], " ".join(jobOptions['inputFile'])))
        lines_makefile.append("\t%s %s" % (self.executable_comp_LeptonFakeRate, jobOptions['cfgFile_modified']))
        lines_makefile.append("")
      elif self.is_sbatch:
        lines_makefile.append("%s: %s" % (jobOptions['outputFile'], "sbatch_comp_LeptonFakeRate"))
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
      key_dir = getKey(process_name)
      for dir_type in [ DKEY_CFGS, DKEY_HIST, DKEY_LOGS, DKEY_RLES ]:
        initDict(self.dirs, [ key_dir, dir_type ])
        if dir_type in [ DKEY_CFGS, DKEY_LOGS ]:
          self.dirs[key_dir][dir_type] = os.path.join(self.configDir, dir_type, self.channel, process_name)
        else:
          self.dirs[key_dir][dir_type] = os.path.join(self.outputDir, dir_type, self.channel, process_name)
    for dir_type in [ DKEY_CFGS, DKEY_SCRIPTS, DKEY_LOGS, DKEY_HIST, DKEY_DCRD, DKEY_PLOT, DKEY_HADD_RT, DKEY_COMBINE_OUTPUT ]:
      initDict(self.dirs, [ dir_type ])
      if dir_type in [ DKEY_CFGS, DKEY_SCRIPTS, DKEY_LOGS, DKEY_DCRD, DKEY_HADD_RT, DKEY_PLOT, DKEY_COMBINE_OUTPUT ]:
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
            logging.warning("ntupleFiles['%s'] = %s --> skipping job !!" % (key_job, ntupleFiles))
            continue

          rleOutputFile = os.path.join(
            self.dirs[key_dir][DKEY_RLES],
          "rle_{channel}_{process_name}_{central_or_shift}_{jobId}_%s_%s.txt".format(
            channel          = self.channel,
            process_name     = process_name,
            central_or_shift = central_or_shift,
            jobId            = jobId,
          )) if self.select_rle_output else ""

          cfg_key = getKey(self.channel, process_name, central_or_shift, jobId)
          histo_key = getKey(process_name,  central_or_shift, jobId)
          cfgFile_modified_path = os.path.join(self.dirs[key_dir][DKEY_CFGS], "analyze_%s_cfg.py" % cfg_key)
          logFile_path          = os.path.join(self.dirs[key_dir][DKEY_LOGS], "analyze_%s.log" % cfg_key)
          histogramFile_path    = os.path.join(self.dirs[key_dir][DKEY_HIST], "%s.root" % histo_key)

          self.jobOptions_analyze[key_analyze_job] = {
            'ntupleFiles'              : ntupleFiles,
            'cfgFile_modified'         : cfgFile_modified_path,
            'histogramFile'            : histogramFile_path,
            'selEventsFileName_output' : rleOutputFile,
            'logFile'                  : logFile_path,
            'absEtaBins_e'             : self.absEtaBins_e,
            'ptBins_e'                 : self.ptBins_e,
            'absEtaBins_mu'            : self.absEtaBins_mu,
            'ptBins_mu'                : self.ptBins_mu,
            'central_or_shift'         : central_or_shift,
            'fillGenEvtHistograms'     : self.fillGenEvtHistograms,
          }
          self.createCfg_analyze(self.jobOptions_analyze[key_analyze_job], sample_info)

          # initialize input and output file names for hadd_stage1
          key_hadd_stage1 = getKey(process_name)
          if not key_hadd_stage1 in self.inputFiles_hadd_stage1:
            self.inputFiles_hadd_stage1[key_hadd_stage1] = []
          self.inputFiles_hadd_stage1[key_hadd_stage1].append(self.jobOptions_analyze[key_analyze_job]['histogramFile'])
          self.outputFile_hadd_stage1[key_hadd_stage1] = os.path.join(self.dirs[DKEY_HIST], "histograms_harvested_stage1_%s_%s.root" % \
            (self.channel, process_name))

    # initialize input and output file names for hadd_stage1_5
    key_hadd_stage1_5 = getKey('')
    if not key_hadd_stage1_5 in self.inputFiles_hadd_stage1_5:
      self.inputFiles_hadd_stage1_5[key_hadd_stage1_5] = []
    for key_hadd_stage1 in self.outputFile_hadd_stage1.keys():
      self.inputFiles_hadd_stage1_5[key_hadd_stage1_5].append(self.outputFile_hadd_stage1[key_hadd_stage1])
    self.outputFile_hadd_stage1_5[key_hadd_stage1_5] = os.path.join(self.dirs[DKEY_HIST], "histograms_harvested_stage1_5.root" )

    # sum fake contributions for the total of all MC samples
    # input processes: TTj,...
    # output process: fakes_mc
    key_addBackgrounds_job = getKey('')
    sample_categories = []
    sample_categories.extend(self.nonfake_backgrounds)
    sample_categories.extend([ "signal" ])
    processes_input = []
    for sample_category in sample_categories:
      processes_input.append("%sj" % sample_category)
      self.jobOptions_addBackgrounds_sum[key_addBackgrounds_job] = {
        'inputFile' : self.outputFile_hadd_stage1_5[key_hadd_stage1_5],
        'cfgFile_modified' : os.path.join(self.dirs[DKEY_CFGS], "addBackgrounds_fakes_mc_cfg.py"),
        'outputFile' : os.path.join(self.dirs[DKEY_HIST], "addBackgrounds_fakes_mc.root"),
        'logFile' : os.path.join(self.dirs[DKEY_LOGS], "addBackgrounds_fakes_mc.log"),
        'categories' : [
          "LeptonFakeRate/numerator/electrons_tight",
          "LeptonFakeRate/denominator/electrons_fakeable",
          "LeptonFakeRate/numerator/muons_tight",
          "LeptonFakeRate/denominator/muons_fakeable"
        ],
        'processes_input' : processes_input,
        'process_output' : "fakes_mc",
        'histogramsToCopy' : self.histograms_to_fit,
        'sysShifts' : []
      }
      self.createCfg_addBackgrounds(self.jobOptions_addBackgrounds_sum[key_addBackgrounds_job])

    # create configuration files to run 'addBackgrounds_LeptonFakeRate'
    key_addBackgrounds_job = getKey('')
    self.jobOptions_addBackgrounds_LeptonFakeRate[key_addBackgrounds_job] = {
      'inputFile' : self.outputFile_hadd_stage1_5[key_hadd_stage1_5],
      'cfgFile_modified' : os.path.join(self.dirs[DKEY_CFGS], os.path.basename(self.cfgFile_addBackgrounds_LeptonFakeRate)),
      'outputFile' : os.path.join(self.dirs[DKEY_HIST], "addBackground_LeptonFakeRate.root"),
      'logFile' : os.path.join(self.dirs[DKEY_LOGS], os.path.basename(self.cfgFile_addBackgrounds_LeptonFakeRate.replace("_cfg.py", ".log")) ),
    }
    self.createCfg_addBackgrounds_LeptonFakeRate(self.jobOptions_addBackgrounds_LeptonFakeRate[key_addBackgrounds_job])

    # initialize input and output file names for hadd_stage2
    key_hadd_stage2 = getKey('')
    if not key_hadd_stage2 in self.inputFiles_hadd_stage2:
      self.inputFiles_hadd_stage2[key_hadd_stage2] = []
    # CV: hadd_stage_1_5 output file does not need to be added as input for hadd_stage_2,
    #     as addBackgrounds_LeptonFakeRate output file contains all histograms except fakes_mc
    ##for key_hadd_stage1_5 in self.outputFile_hadd_stage1_5.keys():
    ##  self.inputFiles_hadd_stage2[key_hadd_stage2].append(self.outputFile_hadd_stage1_5[key_hadd_stage1_5])
    self.inputFiles_hadd_stage2[key_hadd_stage2].append(self.jobOptions_addBackgrounds_sum[key_addBackgrounds_job]['outputFile'])
    self.inputFiles_hadd_stage2[key_hadd_stage2].append(self.jobOptions_addBackgrounds_LeptonFakeRate[key_addBackgrounds_job]['outputFile'])
    self.outputFile_hadd_stage2[key_hadd_stage2] = os.path.join(self.dirs[DKEY_HIST], "histograms_harvested_stage2.root")

    # We need to generate the eta and pt bins for electrons and muons
    lepton_bins = {}
    categories = []
    for lepton in ['electron', 'muon']:
      if lepton not in lepton_bins:
        lepton_bins[lepton] = {}

      absEtaBins = None
      ptBins = None
      lepton_short = None
      if lepton == 'electron':
        absEtaBins = self.absEtaBins_e
        ptBins = self.ptBins_e
        lepton_short = 'e'
      elif lepton == 'muon':
        absEtaBins = self.absEtaBins_mu
        ptBins = self.ptBins_mu
        lepton_short = 'mu'
      else:
        raise ValueError('Invalid lepton type: %s' % lepton)
      for selection in ['tight', 'fakeable']:
        if selection not in lepton_bins[lepton]:
          lepton_bins[lepton][selection] = []
        num_or_den = None
        if selection == 'tight':
          num_or_den = 'numerator'
        elif selection == 'fakeable':
          num_or_den = 'denominator'
        else:
          raise ValueError('Invalid lepton selection: %s' % selection)
        for absEtaBin_idx in range(0, len(absEtaBins) - 1):
          absEtaBinLowerEdge = absEtaBins[absEtaBin_idx]
          absEtaBinUpperEdge = absEtaBins[absEtaBin_idx + 1]
          absEtaBinString = getEtaBin(absEtaBinLowerEdge, absEtaBinUpperEdge)
          for ptBin_idx in range(0, len(ptBins) - 1):
            ptBinsLowerEdge = ptBins[ptBin_idx]
            ptBinsUpperEdge = ptBins[ptBin_idx + 1]
            ptBinString = getPtBin(ptBinsLowerEdge, ptBinsUpperEdge)
            absEta_and_ptBinString = '%s_%s' % (absEtaBinString, ptBinString)

            lepton_bins[lepton][selection].append(
              construct_lepton_params(
                lepton, lepton_short, selection, absEta_and_ptBinString,
                error_msg = "No fit parameter range specified for abs(eta) range = (%.3f, %.3f) and "
                            "pT range = (%.3f, %.3f) for lepton type '%s' !!" % \
                            (absEtaBinLowerEdge, absEtaBinUpperEdge, ptBinsLowerEdge, ptBinsUpperEdge, lepton)
              ) + (absEtaBinLowerEdge, absEtaBinUpperEdge, ptBinsLowerEdge, ptBinsUpperEdge, 0)
            )

            categories.append(
              (
                "LeptonFakeRate/%s/%ss_%s/%s/%s" % (num_or_den, lepton, selection, absEtaBinString, ptBinString),
                "%ss_%s_%s_shapes" % (lepton, selection, absEta_and_ptBinString),
              )
            )

        # Let's also add inclusive category
        lepton_bins[lepton][selection].append(
          construct_lepton_params(
            lepton, lepton_short, selection, 'incl',
            error_msg = "No fit parameter range specified for lepton type %s" % lepton
          ) + (-1., -1., -1., -1., 1)
        )
        categories.append(
          (
            "LeptonFakeRate/%s/%ss_%s/incl" % (num_or_den, lepton, selection),
            "%ss_%s_incl_shapes" % (lepton, selection),
          )
        )
    lepton_bins_merged = []
    for lepton_type in lepton_bins:
      for lepton_selection in lepton_bins[lepton_type]:
        lepton_bins_merged.extend(lepton_bins[lepton_type][lepton_selection])

    if self.prep_dcard:
      processesToCopy = []
      signals = []
      logging.info("Creating configuration files to run 'prepareDatacards_LeptonFakeRate'")

      for process in self.prep_dcard_signals:
        signals.append(process)
      self.prep_dcard_signals = signals
      for process in self.prep_dcard_processesToCopy:
        processesToCopy.append(process)
      self.prep_dcard_processesToCopy = processesToCopy
      datacards = []
      for histogramToFit in self.histograms_to_fit:
        key_prep_dcard_job = getKey(histogramToFit)
        datacard = os.path.join(self.dirs[DKEY_DCRD], "prepareDatacards_%s.root" % (histogramToFit))
        self.jobOptions_prep_dcard[key_prep_dcard_job] = {
          'inputFile' : self.outputFile_hadd_stage2[key_hadd_stage2],
          ##'inputFile' : self.jobOptions_addBackgrounds_LeptonFakeRate[key_addBackgrounds_job]['outputFile'],
          'cfgFile_modified' : os.path.join(self.dirs[DKEY_CFGS], "prepareDatacards_LeptonFakeRate_%s_cfg.py" % (histogramToFit)),
          'datacardFile' : datacard,
          'histogramDir' : (self.histogramDir_prep_dcard),
          'histogramToFit' : histogramToFit,
          'label' : None,
          'categories' : categories,
        }
        datacards.append(datacard)
        self.createCfg_prep_dcard_LeptonFakeRate(self.jobOptions_prep_dcard[key_prep_dcard_job])

      # Create setupDatacards_LeptonFakeRate.py script from the template
      systematics = []
      for systematic in self.central_or_shifts:
        if systematic == 'central':
          continue
        systematic_name = systematic.replace('Up', '').replace('Down', '')
        if systematic_name not in systematics:
          systematics.append(systematic_name)
      setup_dcards_template_file = os.path.join(jinja_template_dir, 'setupDatacards_LeptonFakeRate.py.template')
      setup_dcards_template = open(setup_dcards_template_file, 'r').read()
      setup_dcards_script = jinja2.Template(setup_dcards_template).render(
        leptons           = lepton_bins_merged,
        central_or_shifts = systematics,
      )
      setup_dcards_script_path = os.path.join(self.dirs[DKEY_SCRIPTS], 'setupDatacards_LeptonFakeRate.py')
      logging.debug("writing setupDatacards_LeptonFakeRate script file = '%s'" % setup_dcards_script_path)
      with codecs.open(setup_dcards_script_path, "w", "utf-8") as setup_dcards_script_file:
        setup_dcards_script_file.write(setup_dcards_script)
        setup_dcards_script_file.flush()
        os.fsync(setup_dcards_script_file.fileno())
      add_chmodX(setup_dcards_script_path)

      postfit_plot_script_path = os.path.join(os.environ['CMSSW_BASE'], 'src/tthAnalysis/HiggsToTauTau/data/leptonFR/scripts/postFitPlot.py')
      yieldtable_script_path   = os.path.join(os.environ['CMSSW_BASE'], 'src/tthAnalysis/HiggsToTauTau/data/leptonFR/scripts/yieldTable.py')

      # Create run_postFit.sh script from the template
      combine_output_dir = os.path.join(self.dirs[DKEY_COMBINE_OUTPUT], 'output')

      postfit_template_file = os.path.join(jinja_template_dir, 'run_postFit.sh.template')
      postfit_template = open(postfit_template_file, 'r').read()
      for lepton in ['electron', 'muon']:
        for selection in ['fakeable', 'tight']:
          is_num = selection == 'tight'
          for params in lepton_bins[lepton][selection]:
            l_array, l_range, l_sub_dir, l_eta_low, l_eta_high, l_pt_low, l_pt_high, l_is_inclusive = params
            postfit_script = jinja2.Template(postfit_template).render(
              new_cmssw_base         = self.cmssw_base_dir_combine,
              setup_dcards_script    = setup_dcards_script_path,
              postfit_plot_script    = postfit_plot_script_path,
              yieldtable_script      = yieldtable_script_path,
              output_dir             = combine_output_dir,
              numerator_plotLabel    = self.numerator_plotLabel,
              denominator_plotLabel  = self.denominator_plotLabel,
              l_array                = l_array,
              l_range                = l_range,
              l_sub_dir              = l_sub_dir,
              l_eta_low              = l_eta_low,
              l_eta_high             = l_eta_high,
              l_pt_low               = l_pt_low,
              l_pt_high              = l_pt_high,
              l_is_inclusive         = l_is_inclusive,
              is_num                 = is_num,
              numerator_output_dir   = os.path.join(combine_output_dir, 'mlfit_LeptonFakeRate_%s' % self.numerator_histogram),
              denominator_output_dir = os.path.join(combine_output_dir, 'mlfit_LeptonFakeRate_%s' % self.denominator_histogram),
              selection              = selection,
              lepton_letter          = 'e' if lepton == 'electron' else 'mu',
            )
            postfit_script_path = os.path.join(
              self.dirs[DKEY_SCRIPTS],
              'mlfit_%s_%s.sh' % (self.numerator_histogram if is_num else self.denominator_histogram, l_array)
            )
            logging.debug("Writing run_postFit script file = '%s'" % postfit_script_path)
            with codecs.open(postfit_script_path, "w", "utf-8") as postfit_script_file:
              postfit_script_file.write(postfit_script)
              postfit_script_file.flush()
              os.fsync(postfit_script_file.fileno())
            add_chmodX(postfit_script_path)

      fit_value_file = os.path.join(combine_output_dir, 'fit_values.txt')
      makefile_template_file = os.path.join(jinja_template_dir, 'Makefile_postFit.template')
      makefile_template = open(makefile_template_file, 'r').read()
      makefile_templatized = jinja2.Template(makefile_template).render(
        new_cmssw_base = self.cmssw_base_dir_combine,
        setup_dcards_script = setup_dcards_script_path,
        numerator_histogram = self.numerator_histogram,
        denominator_histogram = self.denominator_histogram,
        scripts_dir = self.dirs[DKEY_SCRIPTS],
        numerator_datacard = os.path.join(self.dirs[DKEY_DCRD], "prepareDatacards_%s.root" % self.numerator_histogram),
        denominator_datacard = os.path.join(self.dirs[DKEY_DCRD], "prepareDatacards_%s.root" % self.denominator_histogram),
        output_dir = combine_output_dir,
        numerator_output_dir = os.path.join(combine_output_dir, 'mlfit_LeptonFakeRate_%s' % self.numerator_histogram),
        denominator_output_dir = os.path.join(combine_output_dir, 'mlfit_LeptonFakeRate_%s' % self.denominator_histogram),
        lepton_bins = lepton_bins,
        fit_values = fit_value_file,
      )
      makefile_path = os.path.join(self.dirs[DKEY_SCRIPTS], 'Makefile_postFit')
      logging.debug("Writing run_postFit script file = '%s'" % makefile_path)
      with codecs.open(makefile_path, "w", "utf-8") as makefile_path_file:
        makefile_path_file.write(makefile_templatized)
        makefile_path_file.flush()
        os.fsync(makefile_path_file.fileno())

      self.jobOptions_combine = {
        'inputFile'       : ' '.join(datacards),
        'outputFile'      : fit_value_file,
        'makefile_path'   : makefile_path,
        'logFile'         : os.path.join(self.dirs[DKEY_LOGS], 'postFit.log'),
      }

      key_comp_LeptonFakeRate = getKey('')
      leptonFR_final_output = os.path.join(combine_output_dir, 'leptonFakeRates.root')
      self.jobOptions_comp_LeptonFakeRate[key_comp_LeptonFakeRate] = {
        'inputFile'            : [ fit_value_file, self.outputFile_hadd_stage2[key_hadd_stage2] ],
        ##'inputFile'            : [ fit_value_file, self.jobOptions_addBackgrounds_LeptonFakeRate[key_addBackgrounds_job]['outputFile'] ],
        'outputFile'           : leptonFR_final_output,
        'absEtaBins_e'         : self.absEtaBins_e,
        'ptBins_e'             : self.ptBins_e,
        'absEtaBins_mu'        : self.absEtaBins_mu,
        'ptBins_mu'            : self.ptBins_mu,
        'logFile'              : os.path.join(self.dirs[DKEY_LOGS], os.path.basename(self.cfgFile_comp_LeptonFakeRate).replace('_cfg.py', '.log')),
        'cfgFile_modified'     : os.path.join(self.dirs[DKEY_CFGS], os.path.basename(self.cfgFile_comp_LeptonFakeRate)),
        'plots_outputFileName' : os.path.join(self.dirs[DKEY_PLOT], "comp_LeptonFakeRate.png")
      }
      self.createCfg_comp_LeptonFakeRate(self.jobOptions_comp_LeptonFakeRate[key_comp_LeptonFakeRate])
      self.targets.append(self.jobOptions_comp_LeptonFakeRate[key_comp_LeptonFakeRate]['outputFile'])

    if self.is_sbatch:
      logging.info("Creating script for submitting '%s' jobs to batch system" % self.executable_analyze)
      self.sbatchFile_analyze = os.path.join(self.dirs[DKEY_SCRIPTS], "sbatch_analyze_LeptonFakeRate.py")
      self.createScript_sbatch_analyze(self.executable_analyze, self.sbatchFile_analyze, self.jobOptions_analyze)
      self.sbatchFile_addBackgrounds_sum = os.path.join(self.dirs[DKEY_SCRIPTS], "sbatch_addBackgrounds_sum_LeptonFakeRate.py")
      self.createScript_sbatch(self.executable_addBackgrounds_recursively, self.sbatchFile_addBackgrounds_sum, self.jobOptions_addBackgrounds_sum)
      self.sbatchFile_addBackgrounds_LeptonFakeRate = os.path.join(self.dirs[DKEY_SCRIPTS], "sbatch_addBackgrounds_LeptonFakeRate.py")
      self.createScript_sbatch(self.executable_addBackgrounds_LeptonFakeRate, self.sbatchFile_addBackgrounds_LeptonFakeRate, self.jobOptions_addBackgrounds_LeptonFakeRate)
      logging.info("Creating script for submitting '%s' jobs to batch system" % self.executable_comp_LeptonFakeRate)
      self.sbatchFile_comp_LeptonFakeRate = os.path.join(self.dirs[DKEY_SCRIPTS], "sbatch_comp_LeptonFakeRate.py")
      self.createScript_sbatch(self.executable_comp_LeptonFakeRate, self.sbatchFile_comp_LeptonFakeRate, self.jobOptions_comp_LeptonFakeRate)

    lines_makefile = []
    self.addToMakefile_analyze(lines_makefile)
    self.addToMakefile_hadd_stage1(lines_makefile)
    self.addToMakefile_backgrounds_from_data(lines_makefile)
    self.addToMakefile_hadd_stage2(lines_makefile)
    self.addToMakefile_prep_dcard(lines_makefile)
    self.addToMakefile_combine(lines_makefile)
    self.addToMakefile_comp_LeptonFakeRate(lines_makefile)
    self.createMakefile(lines_makefile)

    logging.info("Done")

    return self.num_jobs

