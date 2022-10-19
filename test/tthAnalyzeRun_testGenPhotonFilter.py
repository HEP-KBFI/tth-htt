#!/usr/bin/env python

from tthAnalysis.HiggsToTauTau.configs.testGenPhotonFilterConfig import testGenPhotonFilterConfig
from tthAnalysis.HiggsToTauTau.jobTools import query_yes_no
from tthAnalysis.HiggsToTauTau.analysisSettings import get_lumi
from tthAnalysis.HiggsToTauTau.runConfig import tthAnalyzeParser, filter_samples
from tthAnalysis.HiggsToTauTau.common import logging, load_samples, load_samples_stitched

import os
import sys
import getpass

# E.g. to run: ./test/tthAnalyzeRun_testGenPhotonFilter.py -v 2017Dec13 -e 2017

parser = tthAnalyzeParser()
parser.add_files_per_job(files_per_job = 100)
parser.add_use_home()
parser.add_stitched([ 'dy_nlo_incl', 'wjets' ])
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
keep_logs          = args.keep_logs

# Additional arguments
files_per_job = args.files_per_job
use_home      = args.use_home
use_stitched  = args.use_stitched

# Load samples
samples = load_samples(era)
samples = load_samples_stitched(samples, era, use_stitched)

if sample_filter:
  samples = filter_samples(samples, sample_filter)

for sample_name, sample_info in samples.items():
  if sample_name == 'sum_events':
    continue
  if not sample_name.startswith((
    '/TGJets', '/TTGJets', '/WGTo', '/ZGTo', '/DY', '/WJetsToLNu', '/W1', '/W2', '/W3', '/W4', '/TTTo', '/TTJets', '/ST',
  )):
    sample_info["use_it"] = False
    continue
  if sample_info["use_it"]:
    if sample_info["sample_category"] == "XGamma":
      if sample_name.startswith('/TGJets'):
        sample_info["sample_category"] = "TGamma"
      elif sample_name.startswith('/TTGJets'):
        sample_info["sample_category"] = "TTGamma"
      elif sample_name.startswith('/WGTo'):
        sample_info["sample_category"] = "WGamma"
      elif sample_name.startswith('/ZGTo'):
        sample_info["sample_category"] = "ZGamma"
      else:
        assert(False)
    else:
      if sample_name.startswith(('/WJetsToLNu', '/W1', '/W2', '/W3', '/W4')):
        sample_info["sample_category"] = "WJets"
      elif sample_name.startswith(('/TTTo', '/TTJets')):
        if sample_name.startswith(('/TTTo2L2Nu', '/TTJets_DiLept')):
          sample_info["sample_category"] = "TTJets_DiLept"
        elif sample_name.startswith(('/TTToSemiLeptonic', '/TTJets_SingleLeptFromT')):
          sample_info["sample_category"] = "TTJets_SemiLept"
        elif sample_name.startswith('/TTToHadronic'):
          sample_info["sample_category"] = "TTJets_Hadronic"
        else:
          sample_info["sample_category"] = "TTJets"
      elif sample_name.startswith('/ST'):
        if sample_name.startswith('/ST_s-channel'):
          sample_info["sample_category"] = "TJets_sChannel"
        elif sample_name.startswith('/ST_t-channel'):
          sample_info["sample_category"] = "TJets_tChannel"
        elif sample_name.startswith('/ST_tWll'):
          sample_info["sample_category"] = "TJets_tWllChannel"
        elif sample_name.startswith('/ST_tW'):
          sample_info["sample_category"] = "TJets_tWChannel"
        else:
          assert(False)
      elif sample_name.startswith('/DY'):
        sample_info["sample_category"] = "ZJets"
      else:
        assert(False)


if __name__ == '__main__':

  configDir = os.path.join("/scratch-persistent", getpass.getuser(), "testGenPhotonFilter", era, version),
  localDir  = os.path.join("/home",               getpass.getuser(), "testGenPhotonFilter", era, version)
  outputDir = os.path.join("/local",         getpass.getuser(), "testGenPhotonFilter", era, version)

  analysis = testGenPhotonFilterConfig(
    configDir               = configDir,
    localDir                = localDir,
    outputDir               = outputDir,
    executable_analyze      = "testGenPhotonFilter",
    cfgFile_analyze         = "testGenPhotonFilter_cfg.py",
    samples                 = samples,
    max_files_per_job       = files_per_job,
    era                     = era,
    use_lumi                = True,
    lumi                    = get_lumi(era),
    check_output_files      = check_output_files,
    running_method          = running_method,
    num_parallel_jobs       = num_parallel_jobs,
    dry_run                 = dry_run,
    isDebug                 = debug,
    use_home                = use_home,
    keep_logs               = keep_logs,
    submission_cmd          = sys.argv,
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
