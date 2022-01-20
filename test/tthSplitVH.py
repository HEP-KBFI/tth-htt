#!/usr/bin/env python

from tthAnalysis.HiggsToTauTau.configs.vhSplitConfig import vhSplitConfig
from tthAnalysis.HiggsToTauTau.jobTools import query_yes_no
from tthAnalysis.HiggsToTauTau.runConfig import tthAnalyzeParser
from tthAnalysis.HiggsToTauTau.common import logging, load_samples

import os
import sys
import getpass

# E.g.: ./test/tthSplitVH.py -v 2017Dec13 -e 2017

parser = tthAnalyzeParser()
parser.add_use_home(False)
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
use_home       = args.use_home

samples = load_samples(era, False, base = 'tth')
del samples['sum_events']
for sample_name, sample_info in samples.items():
  sample_info["use_it"] = sample_name.startswith("/VH")

if __name__ == '__main__':

  vhSplitter = vhSplitConfig(
    configDir = os.path.join("/scratch-persistent", getpass.getuser(), 'ttHVHSplitter', era, version),
    localDir  = os.path.join("/home",               getpass.getuser(), "ttHVHSplitter", era, version),
    outputDir = os.path.join("/hdfs/local",         getpass.getuser(), "ttHVHSplitter", era, version),
    samples               = samples,
    era                   = era,
    check_output_files    = check_output_files,
    running_method        = running_method,
    version               = version,
    num_parallel_jobs     = num_parallel_jobs,
    dry_run               = dry_run,
    isDebug               = debug,
    use_home              = use_home,
    submission_cmd        = sys.argv,
  )

  num_jobs = vhSplitter.create()

  if num_jobs > 0:
    if auto_exec:
      run_vhSplitter = True
    elif no_exec:
      run_vhSplitter = False
    else:
      run_vhSplitter = query_yes_no("Start jobs ?")
    if run_vhSplitter:
      vhSplitter.run()
    else:
      sys.exit(0)
  else:
    logging.info("All jobs done")
