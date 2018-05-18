#!/usr/bin/env python
import os, logging, sys, getpass

from tthAnalysis.HiggsToTauTau.configs.analyzeConfig_WZctrl import analyzeConfig_WZctrl
from tthAnalysis.HiggsToTauTau.jobTools import query_yes_no
from tthAnalysis.HiggsToTauTau.analysisSettings import systematics
from tthAnalysis.HiggsToTauTau.runConfig import tthAnalyzeParser, filter_samples

# E.g.: ./tthAnalyzeRun_WZctrl.py -v 2017Dec13 -e 2017

sys_choices      = [ 'central', 'full' ]
systematics.full = systematics.an_ctrl

parser = tthAnalyzeParser()
parser.add_sys(sys_choices)
parser.add_tau_id_wp("dR03mvaVLoose")
parser.add_files_per_job()
parser.add_use_home()
parser.add_hlt_filter()
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
systematics_label = args.systematics
tau_id_wp         = args.tau_id_wp
files_per_job     = args.files_per_job
use_home          = args.use_home
hlt_filter        = args.hlt_filter

# Use the arguments
max_job_resubmission = resubmission_limit if resubmit else 1
central_or_shift     = getattr(systematics, systematics_label)

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
    ', '.join(central_or_shift)
  )

  if sample_filter:
    samples = filter_samples(samples, sample_filter)

  job_statistics_summary = {}
  run_analysis           = False
  is_last_resubmission   = False

  for idx_job_resubmission in range(max_job_resubmission):
    if is_last_resubmission:
      continue
    logging.info("Job submission #%i:" % (idx_job_resubmission + 1))

    analysis = analyzeConfig_WZctrl(
      configDir = os.path.join("/home",       getpass.getuser(), "ttHAnalysis", era, version),
      outputDir = os.path.join("/hdfs/local", getpass.getuser(), "ttHAnalysis", era, version),
      executable_analyze = "analyze_WZctrl",
      cfgFile_analyze    = "analyze_WZctrl_cfg.py",
      samples            = samples,
      hadTau_selection   = tau_id_wp,
      central_or_shifts  = central_or_shift,
      max_files_per_job  = files_per_job,
      era                = era,
      use_lumi           = True,
      lumi               = lumi,
      check_input_files  = check_input_files,
      running_method     = "sbatch",
      num_parallel_jobs  = 8,
      histograms_to_fit  = [
        "EventCounter",
        "numJets",
        "mLL",
        "mT",
      ],
      select_rle_output  = True,
      verbose            = idx_job_resubmission > 0,
      hlt_filter         = hlt_filter,
      dry_run            = dry_run,
      isDebug            = debug,
      use_home           = use_home,
    )

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
    logging.info("Job submission #%i:" % (idx_job_resubmission + 1))
    for job_type, num_jobs in job_statistics_summary[idx_job_resubmission].items():
      logging.info(" #jobs of type '%s' = %i" % (job_type, num_jobs))
