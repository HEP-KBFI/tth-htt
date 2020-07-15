#!/usr/bin/env python

from tthAnalysis.HiggsToTauTau.configs.projectionConfig import projectionConfig, validate_pu
from tthAnalysis.HiggsToTauTau.jobTools import query_yes_no
from tthAnalysis.HiggsToTauTau.runConfig import tthAnalyzeParser, filter_samples
from tthAnalysis.HiggsToTauTau.common import logging, load_samples

import os
import sys
import getpass
import collections
import itertools

# E.g.: ./test/tthProjection.py -v 2018May09 -e 2017 -m all -p pileup
#       ./test/tthProjection.py -v 2018May09 -e 2017 -m all -p btagSF -j 4

mode_choices = [ 'all', 'sync', 'hh', 'hh_bbww', 'hh_bbww_sync', 'hh_bbww_ttbar', 'hh_bbww_sync_ttbar' ]
projections = [ 'pileup', 'btagSF' ]
default_output = '{projection}_{era}.root'

parser = tthAnalyzeParser(default_num_parallel_jobs = 100)
parser.add_modes(mode_choices)
parser.add_files_per_job(100)
parser.add_use_home()
parser.add_argument('-p', '--project',
  type = str, dest = 'project', metavar = 'choice', choices = projections, required = True,
  help = 'R|Type of job',
)
parser.add_argument('-P', '--plot',
  dest = 'plot', action = 'store_true', default = False,
  help = 'R|Make plots (not supported for btagSF projection)',
)
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
mode          = args.mode
projection    = args.project
files_per_job = args.files_per_job
plot          = args.plot
validate      = args.validate
use_home      = args.use_home

# Custom arguments
output_file = args.output_file

# Use the arguments
if output_file == default_output:
  output_file = output_file.format(projection = projection, era = era)
version = "%s_%s" % (version, mode)

if projection == 'pileup':
  projection_module = "puHist"

  if mode == 'all':
    samples = load_samples(era, False)
  elif mode == 'sync':
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
elif projection == 'btagSF':
  projection_module = "btagSFRatio"

  if mode == 'all':
    samples_tth         = load_samples(era, True,                          suffix = 'base')
    samples_ttbar       = load_samples(era, True, base = 'hh_bbww',        suffix = 'ttbar')
    samples_multilepton = load_samples(era, True, base = 'hh_multilepton', suffix = 'hh')
    samples_bbww        = load_samples(era, True, base = 'hh_bbww',        suffix = 'hh')
    del samples_tth['sum_events']
    del samples_ttbar['sum_events']
    del samples_multilepton['sum_events']
    del samples_bbww['sum_events']
    samples = collections.OrderedDict(itertools.chain(
      samples_tth.items(), samples_ttbar.items(), samples_multilepton.items(), samples_bbww.items(),
    ))
  elif mode == 'sync':
    samples = load_samples(era, True, suffix = 'sync')
  elif mode == 'hh_bbww_sync':
    samples = load_samples(era, True, base = 'hh_bbww', suffix = 'sync')
  elif mode == 'hh_bbww_sync_ttbar':
    samples = load_samples(era, True, base = 'hh_bbww', suffix = 'sync_ttbar')
  else:
    raise ValueError('Invalid mode: %s' % mode)
else:
  raise ValueError('Invalid projection: %s' % projection)

for sample_name, sample_entry in samples.items():
  if sample_name == 'sum_events':
    continue
  sample_entry['use_it'] = sample_entry['type'] != 'data'

if __name__ == '__main__':
  if sample_filter:
    samples = filter_samples(samples, sample_filter)
  if 'sum_events' in samples:
    del samples['sum_events']

  projection_dir = 'ttH{}Projection'.format(projection.capitalize())
  configDir = os.path.join("/home",       getpass.getuser(), projection_dir, era, version)
  outputDir = os.path.join("/hdfs/local", getpass.getuser(), projection_dir, era, version)

  if validate and projection == 'pileup':
    validation_result = validate_pu(os.path.join(outputDir, output_file), samples)
    sys.exit(validation_result)

  projectionJobs = projectionConfig(
    configDir          = configDir,
    outputDir          = outputDir,
    output_file        = output_file,
    executable         = "projectHistogram.sh",
    projection_module  = projection_module,
    samples            = samples,
    max_files_per_job  = files_per_job,
    era                = era,
    plot               = plot,
    check_output_files = check_output_files,
    running_method     = running_method,
    num_parallel_jobs  = num_parallel_jobs,
    dry_run            = dry_run,
    use_home           = use_home,
    submission_cmd     = sys.argv,
  )

  job_statistics = projectionJobs.create()
  for job_type, num_jobs in job_statistics.items():
    logging.info(" #jobs of type '%s' = %i" % (job_type, num_jobs))

  if auto_exec:
    run_projection = True
  elif no_exec:
    run_projection = False
  else:
    run_projection = query_yes_no("Start jobs ?")
  if run_projection:
    projectionJobs.run()
  else:
    sys.exit(0)
