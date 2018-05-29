#!/usr/bin/env python
import os, logging, sys, getpass

from tthAnalysis.HiggsToTauTau.configs.analyzeConfig_charge_flip import analyzeConfig_charge_flip
from tthAnalysis.HiggsToTauTau.jobTools import query_yes_no
from tthAnalysis.HiggsToTauTau.analysisSettings import systematics
from tthAnalysis.HiggsToTauTau.runConfig import tthAnalyzeParser, filter_samples

# E.g.: ./tthAnalyzeRun_chargeFlip.py -v 2017Dec13 -e 2017

era_choices      = ['2017']
sys_choices      = [ 'central', 'full' ]
systematics.full = systematics.an_chargeFlip_e

parser = tthAnalyzeParser()
parser.add_sys(sys_choices, default_choice = 'full')
parser.add_files_per_job()
parser.add_use_home()
args = parser.parse_args()

# Common arguments
era                = args.era
version            = args.version
dry_run            = args.dry_run
resubmission_limit = args.resubmission_limit
no_exec            = args.no_exec
auto_exec          = args.auto_exec
check_input_files  = args.check_input_files
debug              = args.debug
sample_filter      = args.filter
num_parallel_jobs  = args.num_parallel_jobs
running_method     = args.running_method

# Additional arguments
systematics_label = args.systematics
files_per_job     = args.files_per_job
use_home          = args.use_home

# Use the arguments
central_or_shift = getattr(systematics, systematics_label)

if era == "2017":
  from tthAnalysis.HiggsToTauTau.samples.tthAnalyzeSamples_2017 import samples_2017 as samples
  from tthAnalysis.HiggsToTauTau.analysisSettings import lumi_2017 as lumi
else:
  raise ValueError("Invalid era: %s" % era)

for sample_name, sample_info in samples.items():
  if sample_info["use_it"] == False: continue
  if sample_info["type"] == "mc":
    sample_info["triggers"] = [ "1e", "2e" ]
  if sample_info["process_name_specific"].startswith("DYJetsToLL"):
    sample_info["sample_category"] = "DY"
  elif sample_info["process_name_specific"].startswith("TTTo") and sample_info["sample_category"] == "TT":
    sample_info["sample_category"] = "TTbar"
  elif sample_info["process_name_specific"] == "WJetsToLNu":
    sample_info["sample_category"] = "WJets"
  elif sample_info["process_name_specific"].startswith("ST_") and sample_info["sample_category"] == "TT":
    sample_info["sample_category"] = "Singletop"
  elif sample_info["process_name_specific"] in ["WWTo2L2Nu", "WZTo3LNu", "ZZTo4L"]:
    sample_info["sample_category"] = "Diboson"
  elif "Muon" in sample_name or "Tau" in sample_name:
      sample_info["use_it"] = False
  elif sample_info["sample_category"] == "data_obs":
    sample_info["use_it"] = True
  else:
    sample_info["use_it"] = False

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

  for idx_job_resubmission in range(resubmission_limit):
    if is_last_resubmission:
      continue

    analysis = analyzeConfig_charge_flip(
      configDir = os.path.join("/home",       getpass.getuser(), "ttHAnalysis", era, version),
      outputDir = os.path.join("/hdfs/local", getpass.getuser(), "ttHAnalysis", era, version),
      executable_analyze = "analyze_charge_flip",
      samples            = samples,
      lepton_selections  = [ "Tight" ],
      central_or_shifts  = central_or_shift,
      max_files_per_job  = files_per_job,
      era                = era,
      use_lumi           = True,
      lumi               = lumi,
      check_input_files  = check_input_files,
      running_method     = running_method,
      num_parallel_jobs  = num_parallel_jobs,
      histograms_to_fit  = [ "mass_ll" ],
      select_rle_output  = False,
      verbose            = idx_job_resubmission > 0,
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
    logging.info("Job (re)submission #%i:" % (idx_job_resubmission + 1))
    for job_type, num_jobs in job_statistics_summary[idx_job_resubmission].items():
      logging.info(" #jobs of type '%s' = %i" % (job_type, num_jobs))
