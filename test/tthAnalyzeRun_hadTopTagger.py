#!/usr/bin/env python

from tthAnalysis.HiggsToTauTau.configs.analyzeConfig_hadTopTagger import analyzeConfig_hadTopTagger
from tthAnalysis.HiggsToTauTau.jobTools import query_yes_no
from tthAnalysis.HiggsToTauTau.analysisSettings import get_lumi
from tthAnalysis.HiggsToTauTau.runConfig import tthAnalyzeParser, filter_samples
from tthAnalysis.HiggsToTauTau.common import logging, load_samples

import os
import sys
import getpass

# E.g.: ./test/tthAnalyzeRun_hadTopTagger.py -v 2017Dec13 -e 2017

parser = tthAnalyzeParser()
parser.add_tau_id_wp()
parser.add_tau_id()
parser.add_files_per_job(files_per_job = 3)
parser.add_use_home()
parser.add_jet_cleaning()
parser.add_gen_matching()
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
tau_id_wp     = args.tau_id_wp
files_per_job = args.files_per_job
use_home      = args.use_home
jet_cleaning  = args.jet_cleaning
gen_matching  = args.gen_matching
tau_id        = args.tau_id

hadTau_WP_map = {
  'dR03mva' : 'Loose',
  'deepVSj' : 'Loose',
}
hadTau_WP = tau_id + hadTau_WP_map[tau_id]
if tau_id_wp:
  hadTau_WP = tau_id_wp

# Use the arguments
hadTau_selection = "Tight|%s" % hadTau_WP
lumi = get_lumi(era)
jet_cleaning_by_index = (jet_cleaning == 'by_index')
gen_matching_by_index = (gen_matching == 'by_index')

samples = load_samples(era, suffix = "BDT")

if __name__ == '__main__':
  if sample_filter:
    samples = filter_samples(samples, sample_filter)

  analysis = analyzeConfig_hadTopTagger(
    configDir             = os.path.join("/home",       getpass.getuser(), "ttHAnalysis", era, version),
    outputDir             = os.path.join("/hdfs/local", getpass.getuser(), "ttHAnalysis", era, version),
    executable_analyze    = "analyze_hadTopTagger",
    cfgFile_analyze       = "analyze_hadTopTagger_cfg.py",
    samples               = samples,
    jet_cleaning_by_index = jet_cleaning_by_index,
    gen_matching_by_index = gen_matching_by_index,
    channel               = "hadTopTagger",
    hadTau_selection      = hadTau_selection,
    max_files_per_job     = files_per_job,
    era                   = era,
    use_lumi              = True,
    lumi                  = lumi,
    check_output_files    = check_output_files,
    running_method        = running_method,
    num_parallel_jobs     = num_parallel_jobs,
    verbose               = False,
    dry_run               = dry_run,
    isDebug               = debug,
    use_home              = use_home
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
