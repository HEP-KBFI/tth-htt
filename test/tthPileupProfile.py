#!/usr/bin/env python
import os, logging, sys, getpass

from tthAnalysis.HiggsToTauTau.configs.puHistogramConfig import puHistogramConfig, validate_pu
from tthAnalysis.HiggsToTauTau.jobTools import query_yes_no
from tthAnalysis.HiggsToTauTau.runConfig import tthAnalyzeParser, filter_samples

#--------------------------------------------------------------------------------
# NOTE: set mode flag to
#   'all'                   : to produce the Ntuples from all samples
#   'forBDTtraining_only'   : to produce the Ntuples only from the FastSim samples
#   'forBDTtraining_except' : to produce the Ntuples from all but the FastSim samples
#--------------------------------------------------------------------------------

# E.g.: ./tthPileupProfile.py -v 2018May09 -e 2017

mode_choices = [ 'all', 'sync' ]

parser = tthAnalyzeParser()
parser.add_modes(mode_choices)
parser.add_files_per_job(100)
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
resubmit           = not args.disable_resubmission
no_exec            = args.no_exec
auto_exec          = args.auto_exec
check_input_files  = args.check_input_files
sample_filter      = args.filter

# Additional arguments
mode          = args.mode
files_per_job = args.files_per_job
validate      = args.validate

# Use the arguments
max_job_resubmission = resubmission_limit if resubmit else 1

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

  for idx_job_resubmission in range(max_job_resubmission):
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
      running_method    = "sbatch",
      version           = version,
      num_parallel_jobs = 8,
      verbose           = idx_job_resubmission > 0,
      dry_run           = dry_run,
    )

    job_statistics = puHistogramProduction.create()
    for job_type, num_jobs in job_statistics.items():
      logging.info(" #jobs of type '%s' = %i" % (job_type, num_jobs))
    job_statistics_summary[idx_job_resubmission] = job_statistics

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
      sys.exit(0)

  for idx_job_resubmission in job_statistics_summary.keys():
    logging.info("Job submission #%i:" % (idx_job_resubmission + 1))
    for job_type, num_jobs in job_statistics_summary[idx_job_resubmission].items():
      logging.info(" #jobs of type '%s' = %i" % (job_type, num_jobs))
