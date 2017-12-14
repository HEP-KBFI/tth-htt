import logging, jinja2, codecs, os

from tthAnalysis.HiggsToTauTau.analyzeConfig_new import *
from tthAnalysis.HiggsToTauTau.jobTools import create_if_not_exists, add_chmodX
from tthAnalysis.HiggsToTauTau.analysisTools import initDict, getKey, create_cfg, createFile, generateInputFileList

current_dir = os.path.dirname(os.path.realpath(__file__))
DKEY_COMBINE_OUTPUT="combine_output"

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
      'incl'                            : '-10.0,15.0',
      'absEtaLt1_5_Pt15_0to20_0'        : '-10.0,10.0',
      'absEtaLt1_5_Pt20_0to30_0'        : '-10.0,10.0',
      'absEtaLt1_5_Pt30_0to45_0'        : '-10.0,20.0',
      'absEtaLt1_5_Pt45_0to65_0'        : '-10.0,10.0',
      'absEtaLt1_5_Pt65_0to100000_0'    : '-10.0,10.0',
      'absEta1_5to9_9_Pt15_0to20_0'     : '-100.0,100.0',
      'absEta1_5to9_9_Pt20_0to30_0'     : '-5.0,13.0',
      'absEta1_5to9_9_Pt30_0to45_0'     : '-5.0,20.0',
      'absEta1_5to9_9_Pt45_0to65_0'     : '-100.0,100.0',
      'absEta1_5to9_9_Pt65_0to100000_0' : '-100.0,100.0',
    },
    'fakeable' : {
        'incl'                            : '-100.0,100.0',
        'absEtaLt1_5_Pt15_0to20_0'        : '-100.0,100.0',
        'absEtaLt1_5_Pt20_0to30_0'        : '-100.0,100.0',
        'absEtaLt1_5_Pt30_0to45_0'        : '-100.0,100.0',
        'absEtaLt1_5_Pt45_0to65_0'        : '-100.0,100.0',
        'absEtaLt1_5_Pt65_0to100000_0'    : '-100.0,100.0',
        'absEta1_5to9_9_Pt15_0to20_0'     : '-100.0,100.0',
        'absEta1_5to9_9_Pt20_0to30_0'     : '-100.0,100.0',
        'absEta1_5to9_9_Pt30_0to45_0'     : '-100.0,100.0',
        'absEta1_5to9_9_Pt45_0to65_0'     : '-100.0,100.0',
        'absEta1_5to9_9_Pt65_0to100000_0' : '-100.0,100.0',
    },
  },
  'muon' : {
    'tight' : {
        'incl'                            : '-100.0,100.0',
        'absEtaLt1_5_Pt10_0to15_0'        : '-100.0,100.0',
        'absEtaLt1_5_Pt15_0to20_0'        : '-100.0,100.0',
        'absEtaLt1_5_Pt20_0to30_0'        : '-100.0,100.0',
        'absEtaLt1_5_Pt30_0to45_0'        : '-100.0,100.0',
        'absEtaLt1_5_Pt45_0to65_0'        : '-10.0,10.0',
        'absEtaLt1_5_Pt65_0to100000_0'    : '-100.0,100.0',
        'absEta1_5to9_9_Pt10_0to15_0'     : '-5.0,5.0',
        'absEta1_5to9_9_Pt15_0to20_0'     : '-100.0,100.0',
        'absEta1_5to9_9_Pt20_0to30_0'     : '-15.0,15.0',
        'absEta1_5to9_9_Pt30_0to45_0'     : '-50.0,50.0',
        'absEta1_5to9_9_Pt45_0to65_0'     : '-50.0,50.0',
        'absEta1_5to9_9_Pt65_0to100000_0' : '-20.0,20.0',
    },
    'fakeable' : {
      'incl'                            : '-100.0,100.0',
      'absEtaLt1_5_Pt10_0to15_0'        : '-100.0,100.0',
      'absEtaLt1_5_Pt15_0to20_0'        : '-100.0,100.0',
      'absEtaLt1_5_Pt20_0to30_0'        : '-100.0,100.0',
      'absEtaLt1_5_Pt30_0to45_0'        : '-100.0,100.0',
      'absEtaLt1_5_Pt45_0to65_0'        : '-10.0,10.0',
      'absEtaLt1_5_Pt65_0to100000_0'    : '-100.0,100.0',
      'absEta1_5to9_9_Pt10_0to15_0'     : '-5.0,5.0',
      'absEta1_5to9_9_Pt15_0to20_0'     : '-100.0,100.0',
      'absEta1_5to9_9_Pt20_0to30_0'     : '-15.0,15.0',
      'absEta1_5to9_9_Pt30_0to45_0'     : '-50.0,50.0',
      'absEta1_5to9_9_Pt45_0to65_0'     : '-50.0,50.0',
      'absEta1_5to9_9_Pt65_0to100000_0' : '-20.0,20.0',
    },
  },
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
  def __init__(self, configDir, outputDir, cmssw_base_dir_combine,  executable_analyze, samples,
               absEtaBins_e, absPtBins_e, absEtaBins_mu, absPtBins_mu, fillGenEvtHistograms, central_or_shifts,
               max_files_per_job, era, use_lumi, lumi, debug, running_method, num_parallel_jobs, prep_dcard,
               numerator_histogram, denominator_histogram, executable_addBackgrounds_LeptonFakeRate,
               executable_prep_dcard, executable_comp_LeptonFakeRate):
               # charge_selections, jet_minPt, jet_maxPt, jet_minAbsEta, jet_maxAbsEta, hadTau_selections,
               # executable_comp_LeptonFakeRate):
    analyzeConfig.__init__(self, configDir, outputDir, executable_analyze, "LeptonFakeRate", central_or_shifts,
      max_files_per_job, era, use_lumi, lumi, debug, running_method, num_parallel_jobs, prep_dcard,
      [numerator_histogram, denominator_histogram], executable_addBackgrounds_LeptonFakeRate,
      executable_prep_dcard)

    self.cmssw_base_dir_combine = cmssw_base_dir_combine
    if not os.path.isdir(os.path.join(cmssw_base_dir_combine, 'src', 'CombineHarvester')) or \
       not os.path.isdir(os.path.join(cmssw_base_dir_combine, 'src', 'HiggsAnalysis', 'CombinedLimit')):
      raise ValueError('CMSSW path for combine not valid: %s' % self.cmssw_base_dir_combine)

    self.samples = samples
    self.absEtaBins_e = absEtaBins_e
    self.absEtaBins_mu = absEtaBins_mu
    self.absPtBins_e = absPtBins_e
    self.absPtBins_mu = absPtBins_mu
    self.cfgFile_prep_dcard = "prepareDatacards_LeptonFakeRate_cfg.py"
    self.cfgFile_prep_compLeptonFakeRate = "comp_LeptonFakeRate_cfg.py"
    self.prep_dcard = prep_dcard

    self.numerator_histogram = numerator_histogram[0]
    self.denominator_histogram = denominator_histogram[0]
    self.histograms_to_fit = [self.numerator_histogram, self.denominator_histogram]
    self.numerator_plotLabel = numerator_histogram[1]
    self.denominator_plotLabel = denominator_histogram[1]

    self.executable_addBackgrounds_LeptonFakeRate = executable_addBackgrounds_LeptonFakeRate
    self.executable_prep_dcard = executable_prep_dcard
    self.executable_comp_LeptonFakeRate = executable_comp_LeptonFakeRate
    self.fillGenEvtHistograms = fillGenEvtHistograms
    self.cfgFile_analyze = os.path.join(self.template_dir, "analyze_LeptonFakeRate_cfg.py")
    self.cfgFile_addBackgrounds_LeptonFakeRate = os.path.join(self.template_dir, "addBackground_LeptonFakeRate_cfg.py")
    self.prep_dcard_processesToCopy = ["data_obs","TTW","TTZ","TT","Rares","EWK","signal", "TTWW", "tH","ttH_hbb", "fakes_data"]
    self.prep_dcard_signals = ["signal"]

    self.histogramDir_prep_dcard = "LeptonFakeRate"
    self.jobOptions_addBackgrounds_LeptonFakeRate = {}
    self.jobOptions_prep_compLeptonFakeRate = {}
    self.jobOptions_combine = {}

#    self.executable_comp_LeptonFakeRate = executable_comp_LeptonFakeRate                           ## TO BE INCLUDED LATER
#    self.cfgFile_comp_LeptonFakeRate = os.path.join(self.template_dir, "comp_LeptonFakeRate_cfg.py") ## TO BE INCLUDED LATER
#    self.jobOptions_comp_LeptonFakeRate = {}
#    self.cfgFile_make_plots = os.path.join(self.template_dir, "makePlots_LeptonFakeRate_cfg.py")                         ## TO BE INCLUDED LATER
#    self.cfgFile_make_plots_denominator = os.path.join(self.template_dir, "makePlots_LeptonFakeRate_denominator_cfg.py") ## TO BE INCLUDED LATER

#    self.charge_selections = charge_selections
#    self.jet_minPt = jet_minPt
#    self.jet_maxPt = jet_maxPt
#    self.jet_minAbsEta = jet_minAbsEta
#    self.jet_maxAbsEta = jet_maxAbsEta
#    self.hadTau_selections = hadTau_selections



  def createCfg_analyze(self, jobOptions):
    """Create python configuration file for the analyze_LeptonFakeRate executable (analysis code)

    Args:
      inputFiles: list of input files (Ntuples)
      outputFile: output file of the job -- a ROOT file containing histogram
      process: either `TT`, `TTW`, `TTZ`, `EWK`, `Rares`, `data_obs`, `ttH_hww`, `ttH_hzz` or `ttH_htt`
      is_mc: flag indicating whether job runs on MC (True) or data (False)
      lumi_scale: event weight (= xsection * luminosity / number of events)
      central_or_shift: either 'central' or one of the systematic uncertainties defined in $CMSSW_BASE/src/tthAnalysis/HiggsToTauTau/bin/analyze_LeptonFakeRate.cc
    """
    lines = []
    ##lines.append("process.fwliteInput.fileNames = cms.vstring(%s)" % [ os.path.basename(inputFile) for inputFile in inputFiles ])
    lines.append("process.fwliteInput.fileNames = cms.vstring(%s)" % jobOptions['ntupleFiles'])
    lines.append("process.fwliteOutput.fileName = cms.string('%s')" % os.path.basename(jobOptions['histogramFile']))
    lines.append("process.analyze_LeptonFakeRate.process = cms.string('%s')" % jobOptions['sample_category'])
    lines.append("process.analyze_LeptonFakeRate.era = cms.string('%s')" % self.era)
    lines.append("process.analyze_LeptonFakeRate.use_triggers_1e = cms.bool(%s)" % ("1e" in jobOptions['triggers']))
    lines.append("process.analyze_LeptonFakeRate.use_triggers_2e = cms.bool(%s)" % ("2e" in jobOptions['triggers']))
    lines.append("process.analyze_LeptonFakeRate.use_triggers_1mu = cms.bool(%s)" % ("1mu" in jobOptions['triggers']))
    lines.append("process.analyze_LeptonFakeRate.use_triggers_2mu = cms.bool(%s)" % ("2mu" in jobOptions['triggers']))
    lines.append("process.analyze_LeptonFakeRate.absEtaBins_e = cms.vdouble(%s)" % self.absEtaBins_e)
    lines.append("process.analyze_LeptonFakeRate.absEtaBins_mu = cms.vdouble(%s)" % self.absEtaBins_mu)
    lines.append("process.analyze_LeptonFakeRate.absPtBins_e = cms.vdouble(%s)" % self.absPtBins_e)
    lines.append("process.analyze_LeptonFakeRate.absPtBins_mu = cms.vdouble(%s)" % self.absPtBins_mu)
    lines.append("process.analyze_LeptonFakeRate.use_HIP_mitigation_mediumMuonId = cms.bool(%s)" % jobOptions['use_HIP_mitigation_mediumMuonId'])
    lines.append("process.analyze_LeptonFakeRate.isMC = cms.bool(%s)" % jobOptions['is_mc'])
    lines.append("process.analyze_LeptonFakeRate.central_or_shift = cms.string('%s')" % jobOptions['central_or_shift'])
    lines.append("process.analyze_LeptonFakeRate.lumiScale = cms.double(%f)" % jobOptions['lumi_scale'])
#    lines.append("process.analyze_LeptonFakeRate.apply_trigger_bits = cms.bool(%s)" % jobOptions['apply_trigger_bits']) ## REMOVED
    lines.append("process.analyze_LeptonFakeRate.apply_genWeight = cms.bool(%s)" % jobOptions['apply_genWeight'])
    lines.append("process.analyze_LeptonFakeRate.fillGenEvtHistograms = cms.bool(%s)" % self.fillGenEvtHistograms)
    create_cfg(self.cfgFile_analyze, jobOptions['cfgFile_modified'], lines)
#    lines.append("process.analyze_LeptonFakeRate.triggers_1e = cms.vstring(%s)" % self.triggers_1e)
#    lines.append("process.analyze_LeptonFakeRate.triggers_1mu = cms.vstring(%s)" % self.triggers_1mu)
#    lines.append("process.analyze_LeptonFakeRate.triggers_1e1mu = cms.vstring(%s)" % self.triggers_1e1mu)
#    lines.append("process.analyze_LeptonFakeRate.use_triggers_1e1mu = cms.bool(%s)" % ("1e1mu" in jobOptions['triggers']))
#    lines.append("process.analyze_LeptonFakeRate.chargeSelection = cms.string('%s')" % jobOptions['charge_selection'])
#    lines.append("process.analyze_LeptonFakeRate.jet_minPt = cms.double('%f')" % jobOptions['jet_minPt'])
#    lines.append("process.analyze_LeptonFakeRate.jet_maxPt = cms.double('%f')" % jobOptions['jet_maxPt'])
#    lines.append("process.analyze_LeptonFakeRate.jet_minAbsEta = cms.double('%f')" % jobOptions['jet_minAbsEta'])
#    lines.append("process.analyze_LeptonFakeRate.jet_maxAbsEta = cms.double('%f')" % jobOptions['jet_maxAbsEta'])
#    lines.append("process.analyze_LeptonFakeRate.hadTauSelections = cms.vstring(")
#    for hadTau_selection in jobOptions['hadTau_selections']:
#      lines.append("    '%s'," % hadTau_selection)
#    lines.append(")")


  def createCfg_addBackgrounds_LeptonFakeRate(self, jobOptions):
        """
          Create python configuration file for the addBackgrounds executable (sum either all "fake" or all "non-fake" contributions)
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


  def createCfg_comp_jetToTauFakeRate(self, jobOptions):
    """Create python configuration file for the comp_jetToTauFakeRate executable

    Args:
      inputFiles: input file (the ROOT file produced by hadd_stage1)
      outputFile: output file of the job
    """
    for charge_selection in self.charge_selections:
      lines = []
      lines.append("process.fwliteInput.fileNames = cms.vstring('%s')" % jobOptions['inputFile'])
      lines.append("process.fwliteOutput.fileName = cms.string('%s')" % jobOptions['outputFile'])
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

  def addToMakefile_addBackgrounds_LeptonFakeRate(self, lines_makefile):
        if self.is_sbatch:
            lines_makefile.append("sbatch_addBackgrounds_LeptonFakeRate: %s" % " ".join([ jobOptions['inputFile'] for jobOptions in self.jobOptions_addBackgrounds_LeptonFakeRate.values() ]))
            lines_makefile.append("\t%s %s" % ("python", self.sbatchFile_addBackgrounds_LeptonFakeRate))
            lines_makefile.append("")
        for jobOptions in self.jobOptions_addBackgrounds_LeptonFakeRate.values():
            if self.is_makefile:
                lines_makefile.append("%s: %s" % (jobOptions['outputFile'], jobOptions['inputFile']))
                lines_makefile.append("\t%s %s &> %s" % (self.executable_addBackgrounds_LeptonFakeRate, jobOptions['cfgFile_modified'], jobOptions['logFile']))
                lines_makefile.append("")
            elif self.is_sbatch:
                lines_makefile.append("%s: %s" % (jobOptions['outputFile'], "sbatch_addBackgrounds_LeptonFakeRate"))
                lines_makefile.append("\t%s" % ":") # CV: null command
                lines_makefile.append("")
            self.filesToClean.append(jobOptions['outputFile'])


  def addToMakefile_backgrounds_from_data(self, lines_makefile):
    self.addToMakefile_hadd_stage1_5(lines_makefile)
    self.addToMakefile_addBackgrounds_LeptonFakeRate(lines_makefile)

  def addToMakefile_combine(self, lines_makefile):
    jobOptions = self.jobOptions_combine
    lines_makefile.append("%s: %s" % (jobOptions['outputFile'], jobOptions['inputFile']))
    lines_makefile.append("\trm -rf %s" % jobOptions['combineOutputDir'])
    lines_makefile.append("\t%s &> %s" % (jobOptions['postFitScript'], jobOptions['logFile']))
    lines_makefile.append("")
    self.filesToClean.append(jobOptions['outputFile'])

  def addToMakefile_comp_leptonFakeRate(self, lines_makefile):
    jobOptions = self.jobOptions_prep_compLeptonFakeRate
    lines_makefile.append("%s: %s" % (jobOptions['outputFile'], jobOptions['inputFile']))
    lines_makefile.append("\trm -f %s" % jobOptions['outputFile'])
    lines_makefile.append("\t%s %s &> %s" % (self.executable_comp_LeptonFakeRate, jobOptions['cfgFile_modified'], jobOptions['logFile']))
    lines_makefile.append("")
    self.filesToClean.append(jobOptions['outputFile'])


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
        lines.append("process.fwliteOutput.fileName = cms.string('%s')" % jobOptions['datacardFile'])  ## DEF LINE
        category_entries = jinja2.Template(category_template).render(categories = jobOptions['categories'])
        lines.append(
          "process.prepareDatacards.sysShifts = cms.vstring(\n  %s,\n)" % \
          ',\n  '.join(map(lambda central_or_shift: "'%s'" % central_or_shift, self.central_or_shifts))
        )
        lines.append(
          "process.prepareDatacards.categories = cms.VPSet(%s\n)" % category_entries
        )
        lines.append("process.prepareDatacards.histogramToFit = cms.string('%s')" % jobOptions['histogramToFit'])
        create_cfg(self.cfgFile_prep_dcard, jobOptions['cfgFile_modified'], lines)

  def createCfg_prep_compLeptonFakeRate(self, jobOptions):
    lines = [
        "process.fwliteInput.fileNames = cms.vstring('%s')" % jobOptions['inputFile'],
        "process.fwliteOutput.fileName = cms.string('%s')"  % jobOptions['outputFile'],
    ]
    create_cfg(self.cfgFile_prep_compLeptonFakeRate, jobOptions['cfgFile_modified'], lines)


  def create(self):
    """Creates all necessary config files and runs the complete analysis workfow -- either locally or on the batch system
    """

    for sample_name, sample_info in self.samples.items():
      if not sample_info["use_it"] or sample_info["sample_category"] in [ "additional_signal_overlap", "background_data_estimate" ]:
        continue
      process_name = sample_info["process_name_specific"]
#      for charge_selection in self.charge_selections:                                                          ## NO CHARGE SELECTION NEEDED HERE
#        key_dir = getKey(process_name, charge_selection)                                                       ## NO CHARGE SELECTION NEEDED HERE
      key_dir = getKey(process_name)
      for dir_type in [ DKEY_CFGS, DKEY_HIST, DKEY_LOGS, DKEY_RLES ]:
        initDict(self.dirs, [ key_dir, dir_type ])
        if dir_type in [ DKEY_CFGS, DKEY_LOGS ]:
#            self.dirs[key_dir][dir_type] = os.path.join(self.configDir, dir_type, self.channel,
#              "_".join([ charge_selection ]), process_name)                                                    ## NO CHARGE SELECTION NEEDED HERE
          self.dirs[key_dir][dir_type] = os.path.join(self.configDir, dir_type, self.channel, process_name)
        else:
#            self.dirs[key_dir][dir_type] = os.path.join(self.outputDir, dir_type, self.channel,
#              "_".join([ charge_selection ]), process_name)                                                    ## NO CHARGE SELECTION NEEDED HERE
          self.dirs[key_dir][dir_type] = os.path.join(self.outputDir, dir_type, self.channel, process_name)
    for dir_type in [ DKEY_CFGS, DKEY_SCRIPTS, DKEY_LOGS, DKEY_HIST, DKEY_DCRD, DKEY_PLOT, DKEY_HADD_RT, DKEY_COMBINE_OUTPUT ]:
      initDict(self.dirs, [ dir_type ])
      if dir_type in [ DKEY_CFGS, DKEY_SCRIPTS, DKEY_LOGS, DKEY_DCRD, DKEY_HADD_RT, DKEY_COMBINE_OUTPUT ]:  ## DKEY_PLOT TO BE ADDED LATER
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

#      for charge_selection in self.charge_selections:                                        ## NO CHARGE SELECTION NEEDED HERE
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
#            key_dir = getKey(process_name, charge_selection)                                  ## NO CHARGE SELECTION NEEDED HERE
            key_dir = getKey(process_name)
#            key_analyze_job = getKey(process_name, charge_selection, central_or_shift, jobId) ## NO CHARGE SELECTION NEEDED HERE
            key_analyze_job = getKey(process_name, central_or_shift, jobId)

            ntupleFiles = inputFileList[jobId]
            if len(ntupleFiles) == 0:
              logging.warning("ntupleFiles['%s'] = %s --> skipping job !!" % (key_job, ntupleFiles))
              continue
            self.jobOptions_analyze[key_analyze_job] = {
              'ntupleFiles' : ntupleFiles,
#              'cfgFile_modified' : os.path.join(self.dirs[key_dir][DKEY_CFGS], "analyze_%s_%s_%s_%s_%i_cfg.py" % \
#                (self.channel, process_name, charge_selection, central_or_shift, jobId)),                          ## NO CHARGE SELECTION NEEDED HERE
#              'histogramFile' : os.path.join(self.dirs[key_dir][DKEY_HIST], "%s_%s_%s_%i.root" % \
#                (process_name, charge_selection, central_or_shift, jobId)),                                        ## NO CHARGE SELECTION NEEDED HERE
#              'logFile' : os.path.join(self.dirs[key_dir][DKEY_LOGS], "analyze_%s_%s_%s_%s_%i.log" % \
#                (self.channel, process_name, charge_selection, central_or_shift, jobId)),                          ## NO CHARGE SELECTION NEEDED HERE
              'cfgFile_modified' : os.path.join(self.dirs[key_dir][DKEY_CFGS], "analyze_%s_%s_%s_%i_cfg.py" % \
                (self.channel, process_name, central_or_shift, jobId)),
              'histogramFile' : os.path.join(self.dirs[key_dir][DKEY_HIST], "%s_%s_%i.root" % \
                (process_name,  central_or_shift, jobId)),
              'logFile' : os.path.join(self.dirs[key_dir][DKEY_LOGS], "analyze_%s_%s_%s_%i.log" % \
                (self.channel, process_name, central_or_shift, jobId)),
              'sample_category' : sample_category,
              'triggers' : sample_info["triggers"],
#              'charge_selection' : charge_selection,                                         ## NO CHARGE SELECTION NEEDED HERE
#              'jet_minPt' : self.jet_minPt,
#              'jet_maxPt' : self.jet_maxPt,
#              'jet_minAbsEta' : self.jet_minAbsEta,
#              'jet_maxAbsEta' : self.jet_maxAbsEta,
#              'hadTau_selections' : self.hadTau_selections,
              'absEtaBins_e' : self.absEtaBins_e,
              'absEtaBins_mu' : self.absEtaBins_mu,
              'absPtBins_e' : self.absPtBins_e,
              'absPtBins_mu' : self.absPtBins_mu,
              ##'use_HIP_mitigation_mediumMuonId' : sample_info["use_HIP_mitigation_mediumMuonId"],
              'use_HIP_mitigation_mediumMuonId' : True,
              'is_mc' : is_mc,
              'central_or_shift' : central_or_shift,
              'lumi_scale' : 1. if not (self.use_lumi and is_mc) else sample_info["xsection"] * self.lumi / sample_info["nof_events"],
              'apply_genWeight' : sample_info["genWeight"] if (is_mc and "genWeight" in sample_info.keys()) else False,
              'apply_trigger_bits' : (is_mc and (self.era == "2015" or (self.era == "2016" and sample_info["reHLT"]))) or not is_mc,
            }
            self.createCfg_analyze(self.jobOptions_analyze[key_analyze_job])

            # initialize input and output file names for hadd_stage1
#            key_hadd_stage1 = getKey(process_name, charge_selection)
            key_hadd_stage1 = getKey(process_name)                                                                                             ## NO CHARGE SELECTION NEEDED HERE
            if not key_hadd_stage1 in self.inputFiles_hadd_stage1:
              self.inputFiles_hadd_stage1[key_hadd_stage1] = []
            self.inputFiles_hadd_stage1[key_hadd_stage1].append(self.jobOptions_analyze[key_analyze_job]['histogramFile'])
#            self.outputFile_hadd_stage1[key_hadd_stage1] = os.path.join(self.dirs[DKEY_HIST], "histograms_harvested_stage1_%s_%s_%s.root" % \
#              (self.channel, process_name, charge_selection))                                                                                 ## NO CHARGE SELECTION NEEDED HERE
            self.outputFile_hadd_stage1[key_hadd_stage1] = os.path.join(self.dirs[DKEY_HIST], "histograms_harvested_stage1_%s_%s.root" % \
              (self.channel, process_name))

    # initialize input and output file names for hadd_stage1_5
    key_hadd_stage1_5 = getKey('')
    if not key_hadd_stage1_5 in self.inputFiles_hadd_stage1_5:
      self.inputFiles_hadd_stage1_5[key_hadd_stage1_5] = []
    for key_hadd_stage1 in self.outputFile_hadd_stage1.keys():
      self.inputFiles_hadd_stage1_5[key_hadd_stage1_5].append(self.outputFile_hadd_stage1[key_hadd_stage1])
    self.outputFile_hadd_stage1_5[key_hadd_stage1_5] = os.path.join(self.dirs[DKEY_HIST], "histograms_harvested_stage1_5.root" )

    ## Creating configuration files to run 'addBackgrounds_LeptonFakeRate' [stage 1.5]
    key_addBackgrounds_job = getKey('')
    self.jobOptions_addBackgrounds_LeptonFakeRate[key_addBackgrounds_job] = {
      'inputFile' : self.outputFile_hadd_stage1_5[key_hadd_stage1_5],
      'cfgFile_modified' : os.path.join(self.dirs[DKEY_CFGS], os.path.basename(self.cfgFile_addBackgrounds_LeptonFakeRate)),
      'outputFile' : os.path.join(self.dirs[DKEY_HIST], "addBackground_LeptonFakeRate.root"),
      'logFile' : os.path.join(self.dirs[DKEY_LOGS], os.path.basename(self.cfgFile_addBackgrounds_LeptonFakeRate.replace("_cfg.py", ".log")) ),
    }
    self.createCfg_addBackgrounds_LeptonFakeRate(self.jobOptions_addBackgrounds_LeptonFakeRate[key_addBackgrounds_job])

# initialize input and output file names for hadd_stage2
#        key_hadd_stage2 = getKey(charge_selection)                                                                                            ## NO CHARGE SELECTION NEEDED HERE
#        if not key_hadd_stage2 in self.inputFiles_hadd_stage2:                                                                                ## NO CHARGE SELECTION NEEDED HERE
#          self.inputFiles_hadd_stage2[key_hadd_stage2] = []                                                                                   ## NO CHARGE SELECTION NEEDED HERE
#        self.inputFiles_hadd_stage2[key_hadd_stage2].append(self.outputFile_hadd_stage1[key_hadd_stage1])                                     ## NO CHARGE SELECTION NEEDED HERE
#        self.outputFile_hadd_stage2[key_hadd_stage2] = os.path.join(self.dirs[DKEY_HIST], "histograms_harvested_stage2_%s_%s.root" % \        ## NO CHARGE SELECTION NEEDED HERE
#          (self.channel, charge_selection))                                                                                                   ## NO CHARGE SELECTION NEEDED HERE
    key_hadd_stage2 = getKey('')
    if not key_hadd_stage2 in self.inputFiles_hadd_stage2:
      self.inputFiles_hadd_stage2[key_hadd_stage2] = []
    for key_hadd_stage1_5 in self.outputFile_hadd_stage1_5.keys():
      self.inputFiles_hadd_stage2[key_hadd_stage2].append(self.outputFile_hadd_stage1_5[key_hadd_stage1_5])
    self.inputFiles_hadd_stage2[key_hadd_stage2].append(self.jobOptions_addBackgrounds_LeptonFakeRate[key_addBackgrounds_job]['outputFile'])
    self.outputFile_hadd_stage2[key_hadd_stage2] = os.path.join(self.dirs[DKEY_HIST], "histograms_harvested_stage2.root")

    # We need to generate the eta and pt bins for electrons and muons
    lepton_bins = {}
    categories = []
    for lepton in ['electron', 'muon']:
      if lepton not in lepton_bins:
        lepton_bins[lepton] = {}

      absEtaBins = None
      absPtBins = None
      lepton_short = None
      if lepton == 'electron':
        absEtaBins = self.absEtaBins_e
        absPtBins = self.absPtBins_e  # Karl: why has this variable ,,abs'' in front of it?!
        lepton_short = 'e'
      elif lepton == 'muon':
        absEtaBins = self.absEtaBins_mu
        absPtBins = self.absPtBins_mu
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
          for absPtBin_idx in range(0, len(absPtBins) - 1):
            absPtBinsLowerEdge = absPtBins[absPtBin_idx]
            absPtBinsUpperEdge = absPtBins[absPtBin_idx + 1]
            absPtBinString = getPtBin(absPtBinsLowerEdge, absPtBinsUpperEdge)
            absEtaPtBinString = '%s_%s' % (absEtaBinString, absPtBinString)

            lepton_bins[lepton][selection].append(
              construct_lepton_params(
                lepton, lepton_short, selection, absEtaPtBinString,
                error_msg = "No fit parameter range specified for abs eta range = (%.3f, %.3f) and "
                            "pT range = (%.3f, %3f) for lepton type %s" % \
                            (absEtaBinLowerEdge, absEtaBinUpperEdge, absPtBinsLowerEdge,
                             absPtBinsUpperEdge, lepton)
              ) + (absEtaBinLowerEdge, absEtaBinUpperEdge, absPtBinsLowerEdge, absPtBinsUpperEdge, 0)
            )

            categories.append(
              (
                "LeptonFakeRate/%s/%ss_%s/%s/%s" % (num_or_den, lepton, selection, absEtaBinString, absPtBinString),
                "%ss_%s_%s_shapes" % (lepton, selection, absEtaPtBinString),
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
      setup_dcards_template_file = os.path.join(current_dir, 'setupDatacards_LeptonFakeRate.py.template')
      setup_dcards_template = open(setup_dcards_template_file, 'r').read()
      setup_dcards_script = jinja2.Template(setup_dcards_template).render(leptons = lepton_bins_merged)
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
      fit_value_file     = os.path.join(combine_output_dir, 'fit_values.txt')
      postfit_template_file = os.path.join(current_dir, 'run_postFit.sh.template')
      postfit_template = open(postfit_template_file, 'r').read()
      postfit_script = jinja2.Template(postfit_template).render(
        new_cmssw_base         = self.cmssw_base_dir_combine,
        setup_dcards_script    = setup_dcards_script_path,
        postfit_plot_script    = postfit_plot_script_path,
        yieldtable_script      = yieldtable_script_path,
        numerator_datacard     = os.path.join(self.dirs[DKEY_DCRD], "prepareDatacards_%s.root" % self.numerator_histogram),
        denominator_datacard   = os.path.join(self.dirs[DKEY_DCRD], "prepareDatacards_%s.root" % self.denominator_histogram),
        output_dir             = combine_output_dir,
        numerator_output_dir   = os.path.join(combine_output_dir, 'mlfit_LeptonFakeRate_%s' % self.numerator_histogram),
        denominator_output_dir = os.path.join(combine_output_dir, 'mlfit_LeptonFakeRate_%s' % self.denominator_histogram),
        numerator_plotLabel    = self.numerator_plotLabel,
        denominator_plotLabel  = self.denominator_plotLabel,
        etights                = lepton_bins['electron']['tight'],
        efakes                 = lepton_bins['electron']['fakeable'],
        mtights                = lepton_bins['muon']['tight'],
        mfakes                 = lepton_bins['muon']['fakeable'],
        fit_value_file         = fit_value_file,
      )
      postfit_script_path = os.path.join(self.dirs[DKEY_SCRIPTS], 'run_postFit.sh')
      logging.debug("Writing run_postFit script file = '%s'" % postfit_script_path)
      with codecs.open(postfit_script_path, "w", "utf-8") as postfit_script_file:
        postfit_script_file.write(postfit_script)
        postfit_script_file.flush()
        os.fsync(postfit_script_file.fileno())
      add_chmodX(postfit_script_path)

      self.jobOptions_combine = {
        'inputFile'       : ' '.join(datacards),
        'outputFile'      : fit_value_file,
        'combineOutputDir': combine_output_dir,
        'postFitScript'   : postfit_script_path,
        'logFile'         : os.path.join(self.dirs[DKEY_LOGS], os.path.basename(postfit_script_path).replace('.sh', '.log')),
      }

      leptonFR_final_output = os.path.join(combine_output_dir, 'leptonFakeRates.root')
      self.jobOptions_prep_compLeptonFakeRate = {
        'inputFile'        : fit_value_file,
        'outputFile'       : leptonFR_final_output,
        'logFile'          : os.path.join(self.dirs[DKEY_LOGS], os.path.basename(self.cfgFile_prep_compLeptonFakeRate).replace('_cfg.py', '.log')),
        'cfgFile_modified' : os.path.join(self.dirs[DKEY_CFGS], os.path.basename(self.cfgFile_prep_compLeptonFakeRate)),
      }
      self.createCfg_prep_compLeptonFakeRate(self.jobOptions_prep_compLeptonFakeRate)

    if self.is_sbatch:
      logging.info("Creating script for submitting '%s' jobs to batch system" % self.executable_analyze)
      self.sbatchFile_analyze = os.path.join(self.dirs[DKEY_SCRIPTS], "sbatch_analyze_%s.py" % self.channel)
#      self.createScript_sbatch()

      self.createScript_sbatch_analyze(self.executable_analyze, self.sbatchFile_analyze, self.jobOptions_analyze)
      self.sbatchFile_addBackgrounds_LeptonFakeRate = os.path.join(self.dirs[DKEY_SCRIPTS], "sbatch_addBackgrounds_LeptonFakeRate_%s.py" % self.channel)
      self.createScript_sbatch(self.executable_addBackgrounds_LeptonFakeRate, self.sbatchFile_addBackgrounds_LeptonFakeRate, self.jobOptions_addBackgrounds_LeptonFakeRate)

#      logging.info("Creating script for submitting '%s' jobs to batch system" % self.executable_comp_jetToTauFakeRate)
#      self.sbatchFile_comp_jetToTauFakeRate = os.path.join(self.dirs[DKEY_SCRIPTS], "sbatch_comp_jetToTauFakeRate.py")
#      self.createScript_sbatch(self.executable_comp_jetToTauFakeRate, self.sbatchFile_comp_jetToTauFakeRate, self.jobOptions_comp_jetToTauFakeRate)





#### FAKE RATE COMP BLOCK COMMENTED OUT ########################

#    logging.info("Creating configuration files for executing 'comp_jetToTauFakeRate'")
#    for charge_selection in self.charge_selections:
#      key_comp_jetToTauFakeRate_job = getKey(charge_selection)
#      key_hadd_stage2 = getKey(charge_selection)
#      self.jobOptions_comp_jetToTauFakeRate[key_comp_jetToTauFakeRate_job] = {
#        'inputFile' : self.outputFile_hadd_stage2[key_hadd_stage2],
#        'cfgFile_modified' : os.path.join(
#          self.dirs[DKEY_CFGS], "comp_jetToTauFakeRate_%s_cfg.py" % charge_selection),
#        'outputFile' : os.path.join(
#          self.dirs[DKEY_HIST], "comp_jetToTauFakeRate_%s.root" % charge_selection),
#        'looseRegion' : "jetToTauFakeRate_%s/denominator/" % charge_selection,
#        'tightRegion' : "jetToTauFakeRate_%s/numerator/" % charge_selection,
#        'absEtaBins' : self.absEtaBins,
#        'ptBins' : self.ptBins
#      }
#      self.createCfg_comp_jetToTauFakeRate(self.jobOptions_comp_jetToTauFakeRate[key_comp_jetToTauFakeRate_job])
#      self.targets.append(self.jobOptions_comp_jetToTauFakeRate[key_comp_jetToTauFakeRate_job]['outputFile'])

#    logging.info("Creating configuration files to run 'makePlots'")
#    for charge_selection in self.charge_selections:
#      key_makePlots_job = getKey(charge_selection)
#      key_hadd_stage2 = getKey(charge_selection)
#      self.jobOptions_make_plots[key_makePlots_job] = {
#        'executable' : self.executable_make_plots,
#        'inputFile' : self.outputFile_hadd_stage2[key_hadd_stage2],
#        'cfgFile_modified' : os.path.join(
#          self.dirs[DKEY_CFGS], "makePlots_%s_cfg.py" % self.channel),
#        'outputFile' : os.path.join(
#          self.dirs[DKEY_PLOT], "makePlots_%s.png" % self.channel),
#        'histogramDir' : "jetToTauFakeRate_%s" % charge_selection,
#        'label' : None,
#        'make_plots_backgrounds' : [ "TT", "TTW", "TTZ", "EWK", "Rares" ],
#      }
#      self.createCfg_makePlots(self.jobOptions_make_plots[key_makePlots_job])
#      self.cfgFile_make_plots = self.cfgFile_make_plots_denominator
#      for absEtaBin in [ "absEtaLt1_5", "absEta1_5to9_9" ]:
#        key_makePlots_job = getKey(charge_selection, absEtaBin, "denominator")
#        key_hadd_stage2 = getKey(charge_selection)
#        self.jobOptions_make_plots[key_makePlots_job] = {
#          'executable' : self.executable_make_plots,
#          'inputFile' : self.outputFile_hadd_stage2[key_hadd_stage2],
#          'cfgFile_modified' : os.path.join(
#            self.dirs[DKEY_CFGS], "makePlots_%s_%s_denominator_%s_cfg.py" % (self.channel, charge_selection, absEtaBin)),
#          'outputFile' : os.path.join(
#            self.dirs[DKEY_PLOT], "makePlots_%s_%s_denominator_%s.png" % (self.channel, charge_selection, absEtaBin)),
#          'histogramDir' : "jetToTauFakeRate_%s/denominator/%s" % (charge_selection, absEtaBin),
#          'label' : None,
#          'make_plots_backgrounds' : [ "TT", "TTW", "TTZ", "EWK", "Rares" ],
#        }
#        self.createCfg_makePlots(self.jobOptions_make_plots[key_makePlots_job])
#        for hadTau_selection in self.hadTau_selections:
#          key_makePlots_job = getKey(charge_selection, absEtaBin, "numerator", hadTau_selection)
#          key_hadd_stage2 = getKey(charge_selection)
#          self.jobOptions_make_plots[key_makePlots_job] = {
#            'executable' : self.executable_make_plots,
#            'inputFile' : self.outputFile_hadd_stage2[key_hadd_stage2],
#            'cfgFile_modified' : os.path.join(
#              self.dirs[DKEY_CFGS], "makePlots_%s_%s_numerator_%s_%s_cfg.py" % (self.channel, charge_selection, hadTau_selection, absEtaBin)),
#            'outputFile' : os.path.join(
#              self.dirs[DKEY_PLOT], "makePlots_%s_%s_numerator_%s_%s.png" % (self.channel, charge_selection, hadTau_selection, absEtaBin)),
#            'histogramDir' : "jetToTauFakeRate_%s/numerator/%s/%s" % (charge_selection, hadTau_selection, absEtaBin),
#            'label' : None,
#            'make_plots_backgrounds' : [ "TT", "TTW", "TTZ", "EWK", "Rares" ],
#          }
#          self.createCfg_makePlots(self.jobOptions_make_plots[key_makePlots_job])
#########################################################

    lines_makefile = []
    self.addToMakefile_analyze(lines_makefile)
    self.addToMakefile_hadd_stage1(lines_makefile)
#    self.addToMakefile_hadd_stage1_5(lines_makefile)
    self.addToMakefile_backgrounds_from_data(lines_makefile)
    self.addToMakefile_hadd_stage2(lines_makefile)
    self.addToMakefile_prep_dcard(lines_makefile)
    self.addToMakefile_combine(lines_makefile)
    self.addToMakefile_comp_leptonFakeRate(lines_makefile)
    self.targets = [ self.jobOptions_prep_compLeptonFakeRate['outputFile'] ]
    self.createMakefile(lines_makefile)

    logging.info("Done")

