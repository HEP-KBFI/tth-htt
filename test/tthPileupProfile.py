#!/usr/bin/env python
import os, logging, sys, getpass

from tthAnalysis.HiggsToTauTau.configs.puHistogramConfig import puHistogramConfig, validate_pu
from tthAnalysis.HiggsToTauTau.jobTools import query_yes_no
from tthAnalysis.HiggsToTauTau.runConfig import tthAnalyzeParser, filter_samples

# E.g.: ./tthPileupProfile.py -v 2018May09 -e 2017 -m all

mode_choices = [ 'all', 'sync', 'hh' ]

parser = tthAnalyzeParser(default_num_parallel_jobs = 40)
parser.add_modes(mode_choices)
parser.add_files_per_job(100)
parser.add_use_home()
parser.add_argument('-V', '--validate',
  dest = 'validate', action = 'store_true', default = False,
  help = 'R|Validate the results',
)
parser.add_argument('-o', '--output-file',
  type = str, dest = 'output_file', metavar = 'filename', default = 'pileup_{era}.root',
  required = False,
  help = 'R|File name of the output file',
)
args = parser.parse_args()

# Common arguments
era                = args.era
version            = args.version
dry_run            = args.dry_run
no_exec            = args.no_exec
auto_exec          = args.auto_exec
check_output_files = not args.not_check_input_files
sample_filter      = args.filter
num_parallel_jobs  = args.num_parallel_jobs
running_method     = args.running_method

# Additional arguments
mode          = args.mode
files_per_job = args.files_per_job
validate      = args.validate
use_home      = args.use_home

# Custom arguments
output_file = args.output_file

# Use the arguments
if '{era}' in output_file:
  output_file = output_file.format(era = era)

if mode == 'sync':
  if era == "2016":
    from tthAnalysis.HiggsToTauTau.samples.tthAnalyzeSamples_2016_nanoAOD_sync import samples_2016 as samples
  elif era == "2017":
    from tthAnalysis.HiggsToTauTau.samples.tthAnalyzeSamples_2017_nanoAOD_sync import samples_2017 as samples
  elif era == "2018":
    from tthAnalysis.HiggsToTauTau.samples.tthAnalyzeSamples_2018_nanoAOD_sync import samples_2018 as samples
  else:
    raise ValueError("Invalid era: %s" % era)
elif mode == 'all':
  if era == "2016":
    from tthAnalysis.HiggsToTauTau.samples.tthAnalyzeSamples_2016_nanoAOD import samples_2016 as samples
  elif era == "2017":
    from tthAnalysis.HiggsToTauTau.samples.tthAnalyzeSamples_2017_nanoAOD import samples_2017 as samples
  elif era == "2018":
    from tthAnalysis.HiggsToTauTau.samples.tthAnalyzeSamples_2018_nanoAOD import samples_2018 as samples
  else:
    raise ValueError("Invalid era: %s" % era)

  for sample_name, sample_entry in samples.items():
    if sample_name == 'sum_events': continue
    sample_entry['use_it'] = True
elif mode == 'hh':
  if era == "2016":
    from hhAnalysis.multilepton.samples.hhAnalyzeSamples_2016_nanoAOD import samples_2016 as samples
  elif era == "2017":
    from hhAnalysis.multilepton.samples.hhAnalyzeSamples_2017_nanoAOD_hh_merged import samples_2017 as samples
  elif era == "2018":
    from hhAnalysis.multilepton.samples.hhAnalyzeSamples_2018_nanoAOD import samples_2018 as samples
  else:
    raise ValueError("Invalid era: %s" % era)
else:
  raise ValueError('Invalid mode: %s' % mode)

if __name__ == '__main__':
  logging.basicConfig(
    stream = sys.stdout,
    level  = logging.INFO,
    format = '%(asctime)s - %(levelname)s: %(message)s'
  )

  if sample_filter:
    samples = filter_samples(samples, sample_filter)
  if 'sum_events' in samples:
    del samples['sum_events']

  configDir = os.path.join("/home",       getpass.getuser(), "ttHPileupProduction", era, version)
  outputDir = os.path.join("/hdfs/local", getpass.getuser(), "ttHPileupProduction", era, version)

  if validate:
    validation_result = validate_pu(os.path.join(outputDir, output_file), samples)
    sys.exit(validation_result)

  puHistogramProduction = puHistogramConfig(
    configDir          = configDir,
    outputDir          = outputDir,
    output_file        = output_file,
    executable         = "puHistogramProducer.sh",
    samples            = samples,
    max_files_per_job  = files_per_job,
    era                = era,
    check_output_files = check_output_files,
    running_method     = running_method,
    num_parallel_jobs  = num_parallel_jobs,
    dry_run            = dry_run,
    use_home           = use_home,
  )

  job_statistics = puHistogramProduction.create()
  for job_type, num_jobs in job_statistics.items():
    logging.info(" #jobs of type '%s' = %i" % (job_type, num_jobs))

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
