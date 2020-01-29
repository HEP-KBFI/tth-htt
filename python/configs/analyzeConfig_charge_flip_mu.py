from tthAnalysis.HiggsToTauTau.configs.analyzeConfig_charge_flip import *
from tthAnalysis.HiggsToTauTau.analysisTools import create_cfg

class analyzeConfig_charge_flip_mu(analyzeConfig_charge_flip):
  """Configuration metadata needed to run analysis in a single go.

  Sets up a folder structure by defining full path names; no directory creation is delegated here.

  See $CMSSW_BASE/src/tthAnalysis/HiggsToTauTau/python/analyzeConfig.py
  for documentation of further Args.

  """
  def __init__(self,
        configDir,
        outputDir,
        cmssw_base_dir_combine,
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
        dry_run           = False,
        isDebug           = False,
        use_home          = False,
        submission_cmd    = None,
      ):
    analyzeConfig.__init__(self,
      configDir             = configDir,
      outputDir             = outputDir,
      executable_analyze    = executable_analyze,
      channel               = "charge_flip_mu",
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
      triggers              = [ '1mu', '2mu' ],
      verbose               = verbose,
      dry_run               = dry_run,
      isDebug               = isDebug,
      use_home              = use_home,
      submission_cmd        = submission_cmd,
    )

    if not os.path.isdir(os.path.join(cmssw_base_dir_combine, 'src', 'CombineHarvester')) or \
       not os.path.isdir(os.path.join(cmssw_base_dir_combine, 'src', 'HiggsAnalysis', 'CombinedLimit')) or \
       not os.path.isdir(os.path.join(cmssw_base_dir_combine, 'src', 'tthAnalysis', 'ChargeFlipEstimation')):
      raise ValueError('CMSSW path for combine not valid: %s' % cmssw_base_dir_combine)

    self.prep_dcard_processesToCopy = ["data_obs", "DY", "DY_fake", "WJets", "TTbar", "Singletop", "Diboson"]
    self.prep_dcard_signals = [ "DY" ]

    self.lepton_selections = lepton_selections

    self.cfgFile_analyze_original = os.path.join(self.template_dir, "analyze_charge_flip_mu_cfg.py")
    self.cfgFile_prep_dcard_original = os.path.join(self.template_dir, "prepareDatacards_cfg.py")
    self.select_rle_output = select_rle_output

    self.jobOptions_postFit = {
      'signals'                : [ "data_obs", "DY" ],
      'backgrounds'            : [ "DY_fake", "Singletop", "Diboson", "TTbar" ],
      'lepton_type'            : 'muon',
      'era'                    : self.era,
      'cmssw_base_dir_combine' : cmssw_base_dir_combine,
      'target'                 : 'fit_result_data_exclusions.root',
    }
    self.subMake_targets = []

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
      for ptEtaBin in [
          "BB_LL", "BB_ML", "BB_MM", "BB_HL", "BB_HM", "BB_HH",
          "EE_LL", "EE_ML", "EE_MM", "EE_HL", "EE_HM", "EE_HH",
          "BE_LL", "BE_ML", "EB_ML","BE_MM",  "BE_HL", "EB_HL",
          "BE_HM", "EB_HM", "BE_HH", "total",
        ]:
        lines.append("    cms.PSet(")
        lines.append("        input = cms.string('%s/%s')," % (charge, ptEtaBin))
        lines.append("        output = cms.string('ttH_%s_%s_%s')" % (self.channel, charge, ptEtaBin))
        lines.append("    ),")
    lines.append(")")
    lines.append("process.prepareDatacards.histogramToFit = cms.string('%s')" % jobOptions['histogramToFit'])
    lines.append("process.prepareDatacards.sysShifts = cms.vstring(%s)" % systematics.muon_E)
    create_cfg(self.cfgFile_prep_dcard, jobOptions['cfgFile_modified'], lines)

  def create(self):
    return analyzeConfig_charge_flip.create(self)

