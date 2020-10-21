#!/usr/bin/env python

from tthAnalysis.HiggsToTauTau.configs.refGenWeightConfig import refGenWeightConfig, validate_refGenWeight
from tthAnalysis.HiggsToTauTau.jobTools import query_yes_no
from tthAnalysis.HiggsToTauTau.runConfig import tthAnalyzeParser, filter_samples
from tthAnalysis.HiggsToTauTau.common import logging, load_samples

import os
import sys
import getpass
import collections
import itertools

# E.g.: ./test/tthRefGenWeight.py -v 2018May09 -e 2017 -m all

mode_choices = [ 'all', 'tth', 'tth_sync', 'hh', 'hh_bbww', 'hh_bbww_sync', 'hh_bbww_ttbar', 'hh_bbww_sync_ttbar' ]
default_output = '{mode}_{era}.txt'

parser = tthAnalyzeParser(default_num_parallel_jobs = 100)
parser.add_modes(mode_choices)
parser.add_use_home()
parser.add_argument('-V', '--validate',
  dest = 'validate', action = 'store_true', default = False,
  help = 'R|Validate the results',
)
parser.add_argument('-o', '--output-file',
  type = str, dest = 'output_file', metavar = 'filename', default = default_output,
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
mode     = args.mode
validate = args.validate
use_home = args.use_home

# Custom arguments
output_file = args.output_file

# Use the arguments
if output_file == default_output:
  output_file = output_file.format(mode = mode, era = era)
version = "%s_%s" % (version, mode)

if mode == 'all':
  samples_tth            = load_samples(era, False)
  samples_hh_multilepton = load_samples(era, False, base = 'hh_multilepton')
  samples_hh_bbww        = load_samples(era, False, base = 'hh_bbww')
  samples_hh_bbww_ttbar  = load_samples(era, False, base = 'hh_bbww', suffix = 'ttbar')
  samples = collections.OrderedDict(itertools.chain(
    samples_tth.items(), samples_hh_multilepton.items(), samples_hh_bbww.items(), samples_hh_bbww_ttbar.items()
  ))
elif mode == 'tth':
  samples = load_samples(era, False)
elif mode == 'tth_sync':
  samples = load_samples(era, False, suffix = 'sync')
elif mode == 'hh':
  samples = load_samples(era, False, base = 'hh_multilepton')
elif mode == 'hh_bbww':
  samples = load_samples(era, False, base = 'hh_bbww')
elif mode == 'hh_bbww_ttbar':
  samples = load_samples(era, False, base = 'hh_bbww', suffix = 'ttbar')
elif mode == 'hh_bbww_sync':
  samples = load_samples(era, False, base = 'hh_bbww', suffix = 'sync')
elif mode == 'hh_bbww_sync_ttbar':
  samples = load_samples(era, False, base = 'hh_bbww', suffix = 'sync_ttbar')
else:
  raise ValueError('Invalid mode: %s' % mode)

for sample_name, sample_entry in samples.items():
  if sample_name == 'sum_events':
    continue
  sample_entry['use_it'] = sample_entry['type'] != 'data'

if __name__ == '__main__':
  if sample_filter:
    samples = filter_samples(samples, sample_filter)
  if 'sum_events' in samples:
    del samples['sum_events']

  configDir = os.path.join("/home",       getpass.getuser(), 'ttHRefGenWeight', era, version)
  outputDir = os.path.join("/hdfs/local", getpass.getuser(), 'ttHRefGenWeight', era, version)

  if validate:
    validation_result = validate_refGenWeight(os.path.join(outputDir, output_file), samples)
    sys.exit(validation_result)

  refGenWeightJobs = refGenWeightConfig(
    configDir          = configDir,
    outputDir          = outputDir,
    output_file        = output_file,
    executable         = "getRefGenWeight.py",
    samples            = samples,
    era                = era,
    check_output_files = check_output_files,
    running_method     = running_method,
    num_parallel_jobs  = num_parallel_jobs,
    dry_run            = dry_run,
    use_home           = use_home,
    submission_cmd     = sys.argv,
  )

  job_statistics = refGenWeightJobs.create()
  for job_type, num_jobs in job_statistics.items():
    logging.info(" #jobs of type '%s' = %i" % (job_type, num_jobs))

  if auto_exec:
    run_refGenWeight = True
  elif no_exec:
    run_refGenWeight = False
  else:
    run_refGenWeight = query_yes_no("Start jobs ?")
  if run_refGenWeight:
    refGenWeightJobs.run()
  else:
    sys.exit(0)
