#!/usr/bin/env python
import os, logging, sys, getpass
from tthAnalysis.HiggsToTauTau.configs.analyzeConfig_3l_1tau import analyzeConfig_3l_1tau
from tthAnalysis.HiggsToTauTau.jobTools import query_yes_no
from tthAnalysis.HiggsToTauTau.analysisSettings import systematics
from tthAnalysis.HiggsToTauTau.runConfig import tthAnalyzeParser, filter_samples

# E.g.: ./tthAnalyzeRun_3l_1tau.py -v 2017Dec13 -m default -e 2017

mode_choices         = [
  'default', 'addMEM', 'forBDTtraining_beforeAddMEM', 'forBDTtraining_afterAddMEM', 'sync', 'sync_noMEM'
]
sys_choices          = [ 'central', 'full', 'extended' ]
systematics.full     = systematics.an_common
systematics.extended = systematics.an_extended

parser = tthAnalyzeParser()
parser.add_modes(mode_choices)
parser.add_sys(sys_choices)
parser.add_preselect()
parser.add_rle_select()
parser.add_nonnominal()
parser.add_tau_id_wp()
parser.add_hlt_filter()
parser.add_files_per_job()
parser.add_use_home()
args = parser.parse_args()

# Common arguments
era                = args.era
version            = args.version
dry_run            = args.dry_run
resubmission_limit = args.resubmission_limit
resubmit           = not args.disable_resubmission
no_exec            = args.no_exec
auto_exec          = args.auto_exec
check_input_files  = args.check_input_files
debug              = args.debug
sample_filter      = args.filter

# Additional arguments
mode              = args.mode
systematics_label = args.systematics
use_preselected   = args.use_preselected
rle_select        = os.path.expanduser(args.rle_select)
use_nonnominal    = args.original_central
hlt_filter        = args.hlt_filter
files_per_job     = args.files_per_job
use_home          = args.use_home

# Use the arguments
max_job_resubmission = resubmission_limit if resubmit else 1
central_or_shift     = getattr(systematics, systematics_label)
do_sync              = mode.startswith('sync')

MEMbranch                      = ''
hadTauFakeRateWeight_inputFile = "tthAnalysis/HiggsToTauTau/data/FR_tau_2016.root" #TODO update
chargeSumSelections            = [ "OS" ] if "forBDTtraining" in mode else [ "OS", "SS" ]

if mode == "default":
  if use_preselected:
    from tthAnalysis.HiggsToTauTau.samples.tthAnalyzeSamples_2017_preselected import samples_2017
  else:
    from tthAnalysis.HiggsToTauTau.samples.tthAnalyzeSamples_2017 import samples_2017
  hadTau_selection     = "dR03mvaLoose"
  applyFakeRateWeights = "3lepton"

  for sample_name, sample_info in samples_2017.items():
    if sample_name in [
        #TODO list of samples collected with tau triggers?
      ]:
      sample_info["use_it"] = False
elif mode == "addMEM":
  from tthAnalysis.HiggsToTauTau.samples.tthAnalyzeSamples_2017_addMEM_3l1tau import samples_2017
  hadTau_selection     = "dR03mvaLoose"
  applyFakeRateWeights = "3lepton"
  MEMbranch            = 'memObjects_3l_1tau_lepFakeable_tauTight_dR03mvaLoose'
elif mode == "forBDTtraining_beforeAddMEM":
  if use_preselected:
    from tthAnalysis.HiggsToTauTau.samples.tthAnalyzeSamples_2017_BDT_preselected import samples_2017
  else:
    from tthAnalysis.HiggsToTauTau.samples.tthAnalyzeSamples_2017_BDT import samples_2017
  applyFakeRateWeights     = "4L"
  hadTau_selection         = "dR03mvaTight"
  hadTau_selection_relaxed = "dR03mvaVVLoose"
elif mode == "forBDTtraining_afterAddMEM":
  from tthAnalysis.HiggsToTauTau.samples.tthAnalyzeSamples_2017_BDT_addMEM_3l1tau import samples_2017
  applyFakeRateWeights     = "4L"
  hadTau_selection         = "dR03mvaTight"
  hadTau_selection_relaxed = "dR03mvaVVLoose"
  MEMbranch                = 'memObjects_3l_1tau_lepLoose_tauTight_dR03mvaVVLoose'
elif mode.startswith("sync"):
  if mode == "sync":
    from tthAnalysis.HiggsToTauTau.samples.tthAnalyzeSamples_2017_addMEM_sync import samples_2017
  elif mode == "sync_noMEM":
    from tthAnalysis.HiggsToTauTau.samples.tthAnalyzeSamples_2017_sync import samples_2017
  else:
    raise ValueError("Internal logic error")
  hadTau_selection     = "dR03mvaLoose"
  applyFakeRateWeights = "3lepton"
else:
  raise ValueError("Internal logic error")

if era == "2017":
  from tthAnalysis.HiggsToTauTau.analysisSettings import lumi_2017 as lumi
  samples = samples_2017
else:
  raise ValueError("Invalid era: %s" % era)

if __name__ == '__main__':
  logging.basicConfig(
    stream = sys.stdout,
    level  = logging.INFO,
    format = '%(asctime)s - %(levelname)s: %(message)s',
  )

  logging.info(
    "Running the jobs with the following systematic uncertainties enabled: %s" % \
    ', '.join(central_or_shift)
  )

  if sample_filter:
    samples = filter_samples(samples, sample_filter)

  if args.tau_id_wp:
    logging.info("Changing tau ID working point: %s -> %s" % (hadTau_selection, args.tau_id_wp))
    hadTau_selection = args.tau_id_wp

  job_statistics_summary = {}
  run_analysis           = False
  is_last_resubmission   = False

  for idx_job_resubmission in range(max_job_resubmission):
    if is_last_resubmission:
      continue
    logging.info("Job submission #%i:" % (idx_job_resubmission + 1))

    analysis = analyzeConfig_3l_1tau(
      configDir = os.path.join("/home",       getpass.getuser(), "ttHAnalysis", era, version),
      outputDir = os.path.join("/hdfs/local", getpass.getuser(), "ttHAnalysis", era, version),
      executable_analyze                    = "analyze_3l_1tau",
      cfgFile_analyze                       = "analyze_3l_1tau_cfg.py",
      samples                               = samples,
      MEMbranch                             = MEMbranch,
      hadTau_selection                      = hadTau_selection,
      # CV: apply "fake" background estimation to leptons only and not to hadronic taus, as discussed on slide 10 of
      #     https://indico.cern.ch/event/597028/contributions/2413742/attachments/1391684/2120220/16.12.22_ttH_Htautau_-_Review_of_systematics.pdf
      applyFakeRateWeights                  = applyFakeRateWeights,
      chargeSumSelections                   = chargeSumSelections,
      central_or_shifts                     = central_or_shift,
      max_files_per_job                     = files_per_job,
      era                                   = era,
      use_lumi                              = True,
      lumi                                  = lumi,
      check_input_files                     = check_input_files,
      running_method                        = "sbatch",
      num_parallel_jobs                     = 100, # KE: run up to 100 'hadd' jobs in parallel on batch system
      executable_addBackgrounds             = "addBackgrounds",
      # CV: use common executable for estimating jet->lepton and jet->tau_h fake background
      executable_addBackgroundJetToTauFakes = "addBackgroundLeptonFakes",
      histograms_to_fit                     = {
        "EventCounter"             : {},
        "numJets"                  : {},
        "mvaDiscr_3l"              : {},
        "mTauTauVis"               : {},
        "mvaOutput_plainKin_tt"    : { 'quantile_rebin' : 6, 'quantile_in_fakes' : False }, # BDT2; quantile in all bkg
        "mvaOutput_plainKin_ttV"   : { 'quantile_rebin' : 6, 'quantile_in_fakes' : False }, # BDT1; quantile in all bkg
        "mvaOutput_plainKin_SUM_M" : { 'quantile_rebin' : 6, 'quantile_in_fakes' : False }, # BDT3; quantile in all bkg
        "mvaOutput_plainKin_1B_M"  : {},
      },
      select_rle_output                     = True,
      select_root_output                    = False,
      verbose                               = idx_job_resubmission > 0,
      dry_run                               = dry_run,
      do_sync                               = do_sync,
      isDebug                               = debug,
      rle_select                            = rle_select,
      use_nonnominal                        = use_nonnominal,
      hlt_filter                            = hlt_filter,
      use_home                              = use_home,
    )

    if mode.find("forBDTtraining") != -1:
      if era == "2016":
        if hadTau_selection_relaxed == "dR03mvaVVLoose":
          hadTauFakeRateWeight_inputFileName = "FR_tau_2016_vvLoosePresel.root"
        elif hadTau_selection_relaxed == "dR03mvaVLoose":
          hadTauFakeRateWeight_inputFileName = "FR_tau_2016_vLoosePresel.root"
        else:
          hadTauFakeRateWeight_inputFileName = "FR_tau_2016.root"
        hadTauFakeRateWeight_inputFile = os.path.join(
          "tthAnalysis/HiggsToTauTau/data", hadTauFakeRateWeight_inputFileName
        )
      analysis.set_BDT_training(hadTau_selection_relaxed, hadTauFakeRateWeight_inputFile)

    job_statistics = analysis.create()
    for job_type, num_jobs in job_statistics.items():
      logging.info(" #jobs of type '%s' = %i" % (job_type, num_jobs))
    job_statistics_summary[idx_job_resubmission] = job_statistics

    if idx_job_resubmission == 0:
      if auto_exec:
        run_analysis = True
      elif no_exec:
        run_analysis = False
      else:
        run_analysis = query_yes_no("Start jobs ?")
    if run_analysis:
      analysis.run()
    else:
      sys.exit(0)

    if job_statistics['analyze'] == 0:
      is_last_resubmission = True

  for idx_job_resubmission in job_statistics_summary.keys():
    logging.info("Job (re)submission #%i:" % (idx_job_resubmission + 1))
    for job_type, num_jobs in job_statistics_summary[idx_job_resubmission].items():
      logging.info(" #jobs of type '%s' = %i" % (job_type, num_jobs))
