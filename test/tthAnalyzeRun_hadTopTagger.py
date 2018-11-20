#!/usr/bin/env python
import os, logging, sys, getpass

from tthAnalysis.HiggsToTauTau.configs.analyzeConfig_hadTopTagger import analyzeConfig_hadTopTagger
from tthAnalysis.HiggsToTauTau.jobTools import query_yes_no
from tthAnalysis.HiggsToTauTau.analysisSettings import get_lumi
from tthAnalysis.HiggsToTauTau.runConfig import tthAnalyzeParser, filter_samples

# E.g.: ./tthAnalyzeRun_hadTopTagger.py -v 2017Dec13 -e 2017

parser = tthAnalyzeParser()
parser.add_tau_id_wp('dR03mvaLoose')
parser.add_files_per_job()
parser.add_use_home()
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
files_per_job = 3 #args.files_per_job # HTT files are fat
use_home      = args.use_home

# Use the arguments
hadTau_selection = "Tight|%s" % tau_id_wp
lumi = get_lumi(era)

if era == "2016":
  from tthAnalysis.HiggsToTauTau.samples.tthAnalyzeSamples_2016_sync import samples_2016 as samples
elif era == "2017":
  from tthAnalysis.HiggsToTauTau.samples.tthAnalyzeSamples_2017_BDT import samples_2017 as samples
elif era == "2018":
  from tthAnalysis.HiggsToTauTau.samples.tthAnalyzeSamples_2018_sync import samples_2018 as samples
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

  analysis = analyzeConfig_hadTopTagger(
    configDir          = os.path.join("/home",       getpass.getuser(), "ttHAnalysis", era, version),
    outputDir          = os.path.join("/hdfs/local", getpass.getuser(), "ttHAnalysis", era, version),
    executable_analyze = "analyze_hadTopTagger",
    cfgFile_analyze    = "analyze_hadTopTagger_cfg.py",
    samples            = samples,
    channel            = "hadTopTagger",
    hadTau_selection   = hadTau_selection,
    max_files_per_job  = files_per_job,
    era                = era,
    use_lumi           = True,
    lumi               = lumi,
    check_output_files = check_output_files,
    running_method     = running_method,
    num_parallel_jobs  = num_parallel_jobs,
    verbose            = False,
    dry_run            = dry_run,
    isDebug            = debug,
    use_home           = use_home
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
