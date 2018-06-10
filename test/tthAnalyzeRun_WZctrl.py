#!/usr/bin/env python
import os, logging, sys, getpass

from tthAnalysis.HiggsToTauTau.configs.analyzeConfig_WZctrl import analyzeConfig_WZctrl
from tthAnalysis.HiggsToTauTau.jobTools import query_yes_no
from tthAnalysis.HiggsToTauTau.analysisSettings import systematics
from tthAnalysis.HiggsToTauTau.runConfig import tthAnalyzeParser, filter_samples

# E.g.: ./tthAnalyzeRun_WZctrl.py -v 2017Dec13 -e 2017

sys_choices      = [ 'full' ] + systematics.an_common_opts
systematics.full = systematics.an_common

parser = tthAnalyzeParser()
parser.add_sys(sys_choices)
parser.add_tau_id_wp("dR03mvaLoose")
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
systematics_label = args.systematics
if type(systematics_label) is str:
  systematics_label = [ systematics_label ]
tau_id_wp         = args.tau_id_wp
files_per_job     = args.files_per_job
use_home          = args.use_home
hlt_filter        = args.hlt_filter

# Use the arguments
central_or_shifts = []
for systematic_label in systematics_label:
  for central_or_shift in getattr(systematics, systematic_label):
    if central_or_shift not in central_or_shifts:
      central_or_shifts.append(central_or_shift)

if era == "2017":
  from tthAnalysis.HiggsToTauTau.samples.tthAnalyzeSamples_2017 import samples_2017 as samples
  from tthAnalysis.HiggsToTauTau.analysisSettings import lumi_2017 as lumi
else:
  raise ValueError("Invalid era: %s" % era)

for sample_name, sample_info in samples.items():
  if sample_info["process_name_specific"] == "WZTo3LNu":
    sample_info["sample_category"] = "WZ"

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

  analysis = analyzeConfig_WZctrl(
    configDir = os.path.join("/home",       getpass.getuser(), "ttHAnalysis", era, version),
    outputDir = os.path.join("/hdfs/local", getpass.getuser(), "ttHAnalysis", era, version),
    executable_analyze = "analyze_WZctrl",
    cfgFile_analyze    = "analyze_WZctrl_cfg.py",
    samples            = samples,
    hadTau_selection   = tau_id_wp,
    central_or_shifts  = central_or_shifts,
    max_files_per_job  = files_per_job,
    era                = era,
    use_lumi           = True,
    lumi               = lumi,
    check_output_files = check_output_files,
    running_method     = running_method,
    num_parallel_jobs  = num_parallel_jobs,
    histograms_to_fit  = [
      "EventCounter",
      "numJets",
      "mLL",
      "mT",
    ],
    select_rle_output  = True,
    hlt_filter         = hlt_filter,
    dry_run            = dry_run,
    isDebug            = debug,
    use_home           = use_home,
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
