#!/usr/bin/env python
import os, logging, sys, getpass

from tthAnalysis.HiggsToTauTau.configs.analyzeConfig_charge_flip import analyzeConfig_charge_flip
from tthAnalysis.HiggsToTauTau.jobTools import query_yes_no
from tthAnalysis.HiggsToTauTau.analysisSettings import systematics, get_lumi
from tthAnalysis.HiggsToTauTau.runConfig import tthAnalyzeParser, filter_samples

# E.g.: ./tthAnalyzeRun_chargeFlip.py -v 2017Dec13 -e 2017

era_choices      = ['2017']
sys_choices      = [ 'full' ] + systematics.an_chargeFlip_e_opts
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
no_exec            = args.no_exec
auto_exec          = args.auto_exec
check_output_files = not args.not_check_input_files
debug              = args.debug
sample_filter      = args.filter
num_parallel_jobs  = args.num_parallel_jobs
running_method     = args.running_method

# Additional arguments
systematics_label = args.systematics
files_per_job     = args.files_per_job
use_home          = args.use_home

# Use the arguments
central_or_shifts = []
for systematic_label in systematics_label:
  for central_or_shift in getattr(systematics, systematic_label):
    if central_or_shift not in central_or_shifts:
      central_or_shifts.append(central_or_shift)
lumi = get_lumi(era)

if era == "2016":
  from tthAnalysis.HiggsToTauTau.samples.tthAnalyzeSamples_2016 import samples_2016 as samples
elif era == "2017":
  from tthAnalysis.HiggsToTauTau.samples.tthAnalyzeSamples_2017 import samples_2017 as samples
elif era == "2018":
  from tthAnalysis.HiggsToTauTau.samples.tthAnalyzeSamples_2018 import samples_2018 as samples
else:
  raise ValueError("Invalid era: %s" % era)

for sample_name, sample_info in samples.items():
  if sample_name == 'sum_events': continue
  if sample_info["use_it"] == False: continue
  if sample_info["type"] == "mc":
    sample_info["triggers"] = [ "1e", "2e" ]
  if sample_info["process_name_specific"].startswith("DYJetsToLL"):
    sample_info["sample_category"] = "DY"
  elif sample_info["process_name_specific"].startswith(("TTTo", "TTJets")) and sample_info["sample_category"] == "TT":
    sample_info["sample_category"] = "TTbar"
  elif sample_info["process_name_specific"].startswith(("WJetsToLNu", "W1JetsToLNu", "W2JetsToLNu", "W3JetsToLNu", "W4JetsToLNu")):
    sample_info["sample_category"] = "WJets"
  elif sample_info["process_name_specific"].startswith("ST_") and sample_info["sample_category"] == "TT":
    sample_info["sample_category"] = "Singletop"
  elif sample_info["process_name_specific"].startswith(("WWTo2L2Nu", "WZTo3LNu", "ZZTo4L")):
    sample_info["sample_category"] = "Diboson"
  elif sample_info["sample_category"] == "data_obs":
    sample_info["use_it"] = not ("Muon" in sample_name or "Tau" in sample_name)
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
    ', '.join(central_or_shifts)
  )

  if sample_filter:
    samples = filter_samples(samples, sample_filter)

  analysis = analyzeConfig_charge_flip(
    configDir = os.path.join("/home",       getpass.getuser(), "ttHAnalysis", era, version),
    outputDir = os.path.join("/hdfs/local", getpass.getuser(), "ttHAnalysis", era, version),
    executable_analyze = "analyze_charge_flip",
    samples            = samples,
    lepton_selections  = [ "Tight" ],
    central_or_shifts  = central_or_shifts,
    max_files_per_job  = files_per_job,
    era                = era,
    use_lumi           = True,
    lumi               = lumi,
    check_output_files = check_output_files,
    running_method     = running_method,
    num_parallel_jobs  = num_parallel_jobs,
    histograms_to_fit  = {
      "mass_ll" : {},
    },
    select_rle_output  = False,
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
