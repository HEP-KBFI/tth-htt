#!/usr/bin/env python
import os, logging, sys, getpass

from tthAnalysis.HiggsToTauTau.configs.puHistogramConfig import puHistogramConfig, validate_pu
from tthAnalysis.HiggsToTauTau.jobTools import query_yes_no
from tthAnalysis.HiggsToTauTau.runConfig import tthAnalyzeParser, filter_samples

# E.g.: ./tthPileupProfile.py -v 2018May09 -e 2017 -m all

mode_choices = [ 'all', 'sync' ]

parser = tthAnalyzeParser(default_num_parallel_jobs = 40)
parser.add_modes(mode_choices)
parser.add_files_per_job(100)
parser.add_use_home()
parser.add_argument('-V', '--validate',
  dest = 'validate', action = 'store_true', default = False,
  help = 'R|Validate the results',
)
args = parser.parse_args()

# Common arguments
era                = args.era
version            = args.version
dry_run            = args.dry_run
resubmission_limit = args.resubmission_limit
no_exec            = args.no_exec
auto_exec          = args.auto_exec
check_input_files  = args.check_input_files
sample_filter      = args.filter
num_parallel_jobs  = args.num_parallel_jobs
running_method     = args.running_method

# Additional arguments
mode          = args.mode
files_per_job = args.files_per_job
validate      = args.validate
use_home      = args.use_home

# Use the arguments

if mode == 'sync':
  from tthAnalysis.HiggsToTauTau.samples.tthAnalyzeSamples_2017_nanoAOD_sync import samples_2017
elif mode == 'all':
  from tthAnalysis.HiggsToTauTau.samples.tthAnalyzeSamples_2017_nanoAOD import samples_2017
else:
  raise ValueError('Unexpected mode: %s' % mode)

if era == "2017":
  samples = samples_2017
else:
  raise ValueError("Invalid era: %s" % era)

if __name__ == '__main__':
  logging.basicConfig(
    stream = sys.stdout,
    level  = logging.INFO,
    format = '%(asctime)s - %(levelname)s: %(message)s'
  )

  if sample_filter:
    samples = filter_samples(samples, sample_filter)

  configDir = os.path.join("/home",       getpass.getuser(), "ttHPileupProduction", era, version)
  outputDir = os.path.join("/hdfs/local", getpass.getuser(), "ttHPileupProduction", era, version)

  if validate:
    validation_result = validate_pu(outputDir, samples)
    sys.exit(validation_result)

  job_statistics_summary    = {}
  run_puHistogramProduction = False
  is_last_resubmission      = False

  for idx_job_resubmission in range(resubmission_limit):
    if is_last_resubmission:
      continue
    logging.info("Job submission #%i:" % (idx_job_resubmission + 1))

    puHistogramProduction = puHistogramConfig(
      configDir         = configDir,
      outputDir         = outputDir,
      executable        = "puHistogramProducer.sh",
      samples           = samples,
      max_files_per_job = files_per_job,
      era               = era,
      check_input_files = check_input_files,
      running_method    = running_method,
      version           = version,
      num_parallel_jobs = num_parallel_jobs,
      verbose           = idx_job_resubmission > 0,
      dry_run           = dry_run,
      use_home          = use_home,
    )

    job_statistics = puHistogramProduction.create()
    for job_type, num_jobs in job_statistics.items():
      logging.info(" #jobs of type '%s' = %i" % (job_type, num_jobs))
    job_statistics_summary[idx_job_resubmission] = job_statistics

    if job_statistics['plot'] == 0:
      is_last_resubmission = True
      break

    if idx_job_resubmission == 0:
      if auto_exec:
        run_puHistogramProduction = True
      elif no_exec:
        run_puHistogramProduction = False
      else:
        run_puHistogramProduction = query_yes_no("Start jobs ?")
    if run_puHistogramProduction:
      puHistogramProduction.run()
    else:
      break

  for idx_job_resubmission in job_statistics_summary.keys():
    logging.info("Job submission #%i:" % (idx_job_resubmission + 1))
    for job_type, num_jobs in job_statistics_summary[idx_job_resubmission].items():
      logging.info(" #jobs of type '%s' = %i" % (job_type, num_jobs))
