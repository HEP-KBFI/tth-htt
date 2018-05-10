#!/usr/bin/env python
import os, logging, sys, getpass

from tthAnalysis.HiggsToTauTau.configs.puHistogramConfig import puHistogramConfig
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

  run_puHistogramProduction = False

  for resubmission_idx in range(resubmission_limit):
    logging.info("Submission attempt #%i" % (resubmission_idx + 1))
    puHistogramProduction = puHistogramConfig(
      configDir = os.path.join("/home",       getpass.getuser(), "ttHPileupProduction", era, version),
      outputDir = os.path.join("/hdfs/local", getpass.getuser(), "ttHPileupProduction", era, version),
      executable            = "puHistogramProducer.sh",
      samples               = samples,
      max_files_per_job     = files_per_job,
      era                   = era,
      check_input_files     = check_input_files,
      running_method        = "sbatch",
      version               = version,
      num_parallel_jobs     = 8,
      verbose               = resubmission_idx > 0,
      dry_run               = dry_run,
    )

    num_jobs = puHistogramProduction.create()

    if num_jobs > 0:
      if resubmission_idx == 0:
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
    else:
      logging.info("All jobs done")
      break
