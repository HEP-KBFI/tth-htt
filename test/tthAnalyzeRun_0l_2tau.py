#!/usr/bin/env python
import os, logging, sys, getpass
from tthAnalysis.HiggsToTauTau.configs.analyzeConfig_0l_2tau import analyzeConfig_0l_2tau
from tthAnalysis.HiggsToTauTau.jobTools import query_yes_no
from tthAnalysis.HiggsToTauTau.analysisSettings import systematics, get_lumi
from tthAnalysis.HiggsToTauTau.runConfig import tthAnalyzeParser, filter_samples

# E.g.: ./tthAnalyzeRun_0l_2tau.py -v 2017Dec13 -m default -e 2017

mode_choices     = [ 'default', 'forBDTtraining', 'sync' ]
sys_choices      = [ 'full' ] + systematics.an_common_opts
systematics.full = systematics.an_common

parser = tthAnalyzeParser()
parser.add_modes(mode_choices)
parser.add_sys(sys_choices)
parser.add_rle_select()
parser.add_nonnominal()
parser.add_tau_id_wp()
parser.add_hlt_filter()
parser.add_files_per_job()
parser.add_use_home()
parser.add_lep_mva_wp()
args = parser.parse_args()

# Common arguments
era                = args.era
version            = args.version
dry_run            = args.dry_run
no_exec            = args.no_exec
auto_exec          = args.auto_exec
check_output_files = not args.not_check_input_files
debug              = args.debug
sample_filter      = args.filter
num_parallel_jobs  = args.num_parallel_jobs
running_method     = args.running_method

# Additional arguments
mode              = args.mode
systematics_label = args.systematics
rle_select        = os.path.expanduser(args.rle_select)
use_nonnominal    = args.original_central
hlt_filter        = args.hlt_filter
files_per_job     = args.files_per_job
use_home          = args.use_home
lep_mva_wp        = args.lep_mva_wp

# Use the arguments
central_or_shifts = []
for systematic_label in systematics_label:
  for central_or_shift in getattr(systematics, systematic_label):
    if central_or_shift not in central_or_shifts:
      central_or_shifts.append(central_or_shift)
do_sync = mode.startswith('sync')
lumi = get_lumi(era)

hadTau_charge_selections = [ "OS", "SS" ]

if mode == "default":
  if era == "2016":
    from tthAnalysis.HiggsToTauTau.samples.tthAnalyzeSamples_2016 import samples_2016 as samples
    hadTau_selection = "dR03mvaVTight"
  elif era == "2017":
    from tthAnalysis.HiggsToTauTau.samples.tthAnalyzeSamples_2017 import samples_2017 as samples
    for sample_name, sample_info in samples.items():
      if sample_name == 'sum_events': continue
      if sample_info["process_name_specific"] in [
            "TTTo2L2Nu_PSweights", "TTToSemiLeptonic_PSweights", "TTToHadronic_PSweights",
          ]:
        # Use non-PSweights samples for the analysis to estimate the irreducible ttbar background
        sample_info["use_it"] = False

    hadTau_selection = "dR03mvaMedium"
  elif era == "2018":
    from tthAnalysis.HiggsToTauTau.samples.tthAnalyzeSamples_2018 import samples_2018 as samples
  else:
    raise ValueError("Invalid era: %s" % era)

elif mode == "forBDTtraining":
  if era == "2016":
    from tthAnalysis.HiggsToTauTau.samples.tthAnalyzeSamples_2016_BDT import samples_2016 as samples

    hadTau_selection         = "dR03mvaMedium"
    hadTau_selection_relaxed = "dR03mvaLoose"
  elif era == "2017":
    from tthAnalysis.HiggsToTauTau.samples.tthAnalyzeSamples_2017_BDT import samples_2017 as samples
    for sample_name, sample_info in samples.items():
      if sample_name == 'sum_events': continue
      if sample_info["process_name_specific"] in [
            "TTTo2L2Nu", "TTToSemiLeptonic", "TTToHadronic",
          ]:
        # Use PSweights samples only for BDT training
        sample_info["use_it"] = False

    hadTau_selection         = "dR03mvaLoose"
    hadTau_selection_relaxed = "dR03mvaVLoose"
  elif era == "2018":
    from tthAnalysis.HiggsToTauTau.samples.tthAnalyzeSamples_2018_BDT import samples_2018 as samples
  else:
    raise ValueError("Invalid era: %s" % era)

  hadTau_charge_selections = [ "OS" ]
elif mode == "sync":
  if use_nonnominal:
    if era == "2016":
      from tthAnalysis.HiggsToTauTau.samples.tthAnalyzeSamples_2016_sync import samples_2016 as samples
    elif era == "2017":
      from tthAnalysis.HiggsToTauTau.samples.tthAnalyzeSamples_2017_sync import samples_2017 as samples
    elif era == "2018":
      from tthAnalysis.HiggsToTauTau.samples.tthAnalyzeSamples_2018_sync import samples_2018 as samples
    else:
      raise ValueError("Invalid era: %s" % era)
  else:
    if era == "2016":
      from tthAnalysis.HiggsToTauTau.samples.tthAnalyzeSamples_2016_sync_nom import samples_2016 as samples
    elif era == "2017":
      from tthAnalysis.HiggsToTauTau.samples.tthAnalyzeSamples_2017_sync_nom import samples_2017 as samples
    elif era == "2018":
      from tthAnalysis.HiggsToTauTau.samples.tthAnalyzeSamples_2018_sync_nom import samples_2018 as samples
    else:
      raise ValueError("Invalid era: %s" % era)

  if era == "2016":
    hadTau_selection = "dR03mvaVTight"
  elif era == "2017":
    hadTau_selection = "dR03mvaMedium"
  elif era == "2018":
    raise ValueError("Implement me!")
  else:
    raise ValueError("Invalid era: %s" % era)
else:
  raise ValueError("Invalid mode: %s" % mode)

for sample_name, sample_info in samples.items():
  if sample_name == 'sum_events': continue
  if sample_info["type"] == "mc":
    sample_info["triggers"] = [ "2tau" ]
  if sample_info["type"] == "data":
    if era == "2016":
      if not sample_name.startswith("/Tau/"):
        sample_info["use_it"] = False
    elif era == "2017":
      if not sample_name.startswith(("/SingleElectron/", "/SingleMuon/")):
        sample_info["use_it"] = False
    elif era == "2018":
      raise ValueError("Implement me!")
    else:
      raise ValueError("Invalid era: %s" % era)

if __name__ == '__main__':
  logging.basicConfig(
    stream = sys.stdout,
    level  = logging.INFO,
    format = '%(asctime)s - %(levelname)s: %(message)s'
  )

  logging.info(
    "Running the jobs with the following systematic uncertainties enabled: %s" % \
    ', '.join(central_or_shifts)
  )

  if sample_filter:
    samples = filter_samples(samples, sample_filter)

  if args.tau_id_wp:
    logging.info("Changing tau ID working point: %s -> %s" % (hadTau_selection, args.tau_id_wp))
    hadTau_selection = args.tau_id_wp

  analysis = analyzeConfig_0l_2tau(
    configDir = os.path.join("/home",       getpass.getuser(), "ttHAnalysis", era, version),
    outputDir = os.path.join("/hdfs/local", getpass.getuser(), "ttHAnalysis", era, version),
    executable_analyze                    = "analyze_0l_2tau",
    cfgFile_analyze                       = "analyze_0l_2tau_cfg.py",
    samples                               = samples,
    lep_mva_wp                            = lep_mva_wp,
    hadTau_selection                      = hadTau_selection,
    hadTau_charge_selections              = hadTau_charge_selections,
    applyFakeRateWeights                  = "2tau",
    central_or_shifts                     = central_or_shifts,
    max_files_per_job                     = files_per_job,
    era                                   = era,
    use_lumi                              = True,
    lumi                                  = lumi,
    check_output_files                    = check_output_files,
    running_method                        = running_method,
    num_parallel_jobs                     = num_parallel_jobs,
    executable_addBackgrounds             = "addBackgrounds",
    # CV: use common executable for estimating jet->lepton and jet->tau_h fake background
    executable_addBackgroundJetToTauFakes = "addBackgroundLeptonFakes",
    histograms_to_fit                     = {
      "EventCounter"            : {},
      "numJets"                 : {},
      "mvaOutput_0l_2tau_ttbar" : {},
      "mTauTauVis"              : {},
      "mTauTau"                 : {},
    },
    select_rle_output                     = True,
    dry_run                               = dry_run,
    do_sync                               = do_sync,
    isDebug                               = debug,
    rle_select                            = rle_select,
    use_nonnominal                        = use_nonnominal,
    hlt_filter                            = hlt_filter,
    use_home                              = use_home,
  )

  if mode == "forBDTtraining" :
    analysis.set_BDT_training(hadTau_selection_relaxed)

  job_statistics = analysis.create()
  for job_type, num_jobs in job_statistics.items():
    logging.info(" #jobs of type '%s' = %i" % (job_type, num_jobs))

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
