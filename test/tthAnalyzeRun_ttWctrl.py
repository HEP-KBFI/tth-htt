#!/usr/bin/env python
import os, logging, sys, getpass

from tthAnalysis.HiggsToTauTau.configs.analyzeConfig_ttWctrl import analyzeConfig_ttWctrl
from tthAnalysis.HiggsToTauTau.jobTools import query_yes_no
from tthAnalysis.HiggsToTauTau.analysisSettings import systematics, get_lumi
from tthAnalysis.HiggsToTauTau.runConfig import tthAnalyzeParser, filter_samples

# E.g.: ./tthAnalyzeRun_ttWctrl.py -v 2017Dec13 -e 2017

mode_choices     = [ 'default', 'sync', 'sync_wMEM' ]
sys_choices      = [ 'full' ] + systematics.an_common_opts
systematics.full = systematics.an_common

parser = tthAnalyzeParser()
parser.add_modes(mode_choices)
parser.add_sys(sys_choices)
parser.add_rle_select()
parser.add_nonnominal()
parser.add_files_per_job()
parser.add_use_home()
parser.add_hlt_filter()
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
files_per_job     = args.files_per_job
use_home          = args.use_home
rle_select        = os.path.expanduser(args.rle_select)
use_nonnominal    = args.original_central
hlt_filter        = args.hlt_filter

# Use the arguments
central_or_shifts = []
for systematic_label in systematics_label:
  for central_or_shift in getattr(systematics, systematic_label):
    if central_or_shift not in central_or_shifts:
      central_or_shifts.append(central_or_shift)
do_sync = mode.startswith('sync')
lumi = get_lumi(era)

if mode == 'default':
  if era == "2016":
    from tthAnalysis.HiggsToTauTau.samples.tthAnalyzeSamples_2016 import samples_2016 as samples
  elif era == "2017":
    from tthAnalysis.HiggsToTauTau.samples.tthAnalyzeSamples_2017 import samples_2017 as samples
  elif era == "2018":
    from tthAnalysis.HiggsToTauTau.samples.tthAnalyzeSamples_2018 import samples_2018 as samples
  else:
    raise ValueError("Invalid era: %s" % era)
elif mode == 'sync_wMEM':
  if era == "2016":
    from tthAnalysis.HiggsToTauTau.samples.tthAnalyzeSamples_2016_addMEM_sync import samples_2016 as samples
  elif era == "2017":
    from tthAnalysis.HiggsToTauTau.samples.tthAnalyzeSamples_2017_addMEM_sync import samples_2017 as samples
  elif era == "2018":
    from tthAnalysis.HiggsToTauTau.samples.tthAnalyzeSamples_2018_addMEM_sync import samples_2018 as samples
  else:
    raise ValueError("Invalid era: %s" % era)
elif mode == 'sync':
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
else:
  raise ValueError("Invalid mode: %s" % mode)

if era == "2016":
  hadTauVeto_selection = "dR03mvaMedium"
elif era == "2017":
  hadTauVeto_selection = "dR03mvaLoose"
elif era == "2018":
  pass
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

  analysis = analyzeConfig_ttWctrl(
    configDir = os.path.join("/home",       getpass.getuser(), "ttHAnalysis", era, version),
    outputDir = os.path.join("/hdfs/local", getpass.getuser(), "ttHAnalysis", era, version),
    executable_analyze        = "analyze_ttWctrl",
    cfgFile_analyze           = "analyze_ttWctrl_cfg.py",
    samples                   = samples,
    lepton_charge_selections  = [ "OS", "SS" ],
    hadTauVeto_selection      = hadTauVeto_selection,
    applyFakeRateWeights      = "2lepton",
    central_or_shifts         = central_or_shifts,
    max_files_per_job         = files_per_job,
    era                       = era,
    use_lumi                  = True,
    lumi                      = lumi,
    check_output_files        = check_output_files,
    running_method            = running_method,
    num_parallel_jobs         = num_parallel_jobs,
    executable_addBackgrounds = "addBackgrounds",
    executable_addFakes       = "addBackgroundLeptonFakes",
    executable_addFlips       = "addBackgroundLeptonFlips",
    histograms_to_fit         = {
      "EventCounter"  : {},
      "numJets"       : {},
      "mvaDiscr_2lss" : {},
    },
    select_rle_output         = True,
    hlt_filter                = hlt_filter,
    dry_run                   = dry_run,
    isDebug                   = debug,
    use_home                  = use_home,
    do_sync                   = do_sync,
    use_nonnominal            = use_nonnominal,
    rle_select                = rle_select,
  )

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
