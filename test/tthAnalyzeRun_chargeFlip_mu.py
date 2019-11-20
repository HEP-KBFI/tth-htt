#!/usr/bin/env python

from tthAnalysis.HiggsToTauTau.configs.analyzeConfig_charge_flip_mu import analyzeConfig_charge_flip_mu
from tthAnalysis.HiggsToTauTau.jobTools import query_yes_no
from tthAnalysis.HiggsToTauTau.analysisSettings import systematics, get_lumi
from tthAnalysis.HiggsToTauTau.runConfig import tthAnalyzeParser, filter_samples
from tthAnalysis.HiggsToTauTau.common import logging, load_samples_aux as load_samples, load_samples_stitched

import os
import sys
import getpass
import re

# E.g.: ./test/tthAnalyzeRun_chargeFlip_mu.py -v 2017Dec13 -e 2017

sys_choices      = [ 'full' ] + systematics.an_chargeFlip_mu_opts
systematics.full = systematics.an_chargeFlip_mu

parser = tthAnalyzeParser()
parser.add_sys(sys_choices, default_choice = 'full')
parser.add_preselect()
parser.add_files_per_job()
parser.add_use_home()
parser.add_jet_cleaning()
parser.add_gen_matching()
parser.add_stitched()
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
use_preselected   = args.use_preselected
files_per_job     = args.files_per_job
use_home          = args.use_home
jet_cleaning      = args.jet_cleaning
gen_matching      = args.gen_matching
use_stitched      = args.use_stitched

# Use the arguments
central_or_shifts = []
for systematic_label in systematics_label:
  for central_or_shift in getattr(systematics, systematic_label):
    if central_or_shift not in central_or_shifts:
      central_or_shifts.append(central_or_shift)
lumi = get_lumi(era)
jet_cleaning_by_index = (jet_cleaning == 'by_index')
gen_matching_by_index = (gen_matching == 'by_index')

samples = load_samples(era, suffix = "preselected" if use_preselected else "")
samples = load_samples_stitched(samples, era, load_dy = 'dy' in use_stitched, load_wjets = 'wjets' in use_stitched)

for sample_name, sample_info in samples.items():
  if sample_name == 'sum_events':
    continue
  if sample_info["use_it"] == False:
    continue
  if sample_info["type"] == "mc":
    sample_info["triggers"] = [ "1mu", "2mu" ]
  if re.match("/DY(\d)?Jets", sample_name):
    sample_info["sample_category"] = "DY"
  elif sample_info["process_name_specific"].startswith(("TTTo", "TTJets")):
    sample_info["sample_category"] = "TTbar"
  elif re.match("/W(\d)?Jets", sample_name):
    sample_info["sample_category"] = "WJets"
  elif sample_info["process_name_specific"].startswith("ST_"):
    sample_info["sample_category"] = "Singletop"
  elif sample_info["process_name_specific"].startswith(("WWTo", "WZTo", "ZZTo")):
    sample_info["sample_category"] = "Diboson"
  elif sample_info["sample_category"] == "data_obs":
      sample_info["use_it"] = "Muon" in sample_name
  else:
    sample_info["use_it"] = False

if __name__ == '__main__':
  logging.info(
    "Running the jobs with the following systematic uncertainties enabled: %s" % \
    ', '.join(central_or_shifts)
  )

  if sample_filter:
    samples = filter_samples(samples, sample_filter)

  analysis = analyzeConfig_charge_flip_mu(
    configDir = os.path.join("/home",       getpass.getuser(), "ttHAnalysis", era, version),
    outputDir = os.path.join("/hdfs/local", getpass.getuser(), "ttHAnalysis", era, version),
    executable_analyze    = "analyze_charge_flip_mu",
    samples               = samples,
    lepton_selections     = [ "Tight" ],
    jet_cleaning_by_index = jet_cleaning_by_index,
    gen_matching_by_index = gen_matching_by_index,
    central_or_shifts     = central_or_shifts,
    max_files_per_job     = files_per_job,
    era                   = era,
    use_lumi              = True,
    lumi                  = lumi,
    check_output_files    = check_output_files,
    running_method        = running_method,
    num_parallel_jobs     = num_parallel_jobs,
    histograms_to_fit     = {
      "mass_ll" : {},
    },
    select_rle_output     = False,
    dry_run               = dry_run,
    isDebug               = debug,
    use_home              = use_home,
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
