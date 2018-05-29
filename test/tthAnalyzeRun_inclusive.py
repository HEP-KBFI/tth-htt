#!/usr/bin/env python
import os, logging, sys, getpass
from tthAnalysis.HiggsToTauTau.configs.analyzeConfig_inclusive import analyzeConfig_inclusive
from tthAnalysis.HiggsToTauTau.jobTools import query_yes_no
from tthAnalysis.HiggsToTauTau.runConfig import tthAnalyzeParser, filter_samples

# E.g. to run: ./tthAnalyzeRun_inclusive.py -v 2017Dec13 -e 2017 -o syncTree

parser = tthAnalyzeParser()
parser.add_rle_select()
parser.add_nonnominal()
parser.add_tau_id_wp('dR03mvaLoose')
parser.add_use_home()
parser.add_argument('-o', '--output-tree',
  type = str, dest = 'output_tree', metavar = 'name', default = 'syncTree', required = False,
  help = 'R|Output TTree name',
)
parser.add_argument('-M', '--with-mem',
  dest = 'with_mem', action = 'store_true', default = False, help = 'R|Use Ntuple w/ MEM included',
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
debug              = args.debug
sample_filter      = args.filter
running_method     = args.running_method

# Additional arguments
rle_select     = os.path.expanduser(args.rle_select)
use_nonnominal = args.original_central
tau_id_wp      = args.tau_id_wp
use_home       = args.use_home

# Custom arguments
output_tree = args.output_tree
with_mem    = args.with_mem

if era == "2017":
  if with_mem:
    from tthAnalysis.HiggsToTauTau.samples.tthAnalyzeSamples_2017_addMEM_sync import samples_2017 as samples
  else:
    from tthAnalysis.HiggsToTauTau.samples.tthAnalyzeSamples_2017_sync import samples_2017 as samples
else:
  raise ValueError("Invalid era: %s" % era)

if __name__ == '__main__':
  logging.basicConfig(
    stream = sys.stdout,
    level  = logging.INFO,
    format = '%(asctime)s - %(levelname)s: %(message)s',
  )

  if sample_filter:
    samples = filter_samples(samples, sample_filter)

  configDir = os.path.join("/home",       getpass.getuser(), "ttHAnalysis", era, version)
  outputDir = os.path.join("/hdfs/local", getpass.getuser(), "ttHAnalysis", era, version)

  job_statistics_summary = {}
  run_analysis           = False
  is_last_resubmission   = False

  for idx_job_resubmission in range(resubmission_limit):
    if is_last_resubmission:
      continue
    logging.info("Job submission #%i:" % (idx_job_resubmission + 1))

    analysis = analyzeConfig_inclusive(
      configDir               = configDir,
      outputDir               = outputDir,
      executable_analyze      = "analyze_inclusive",
      cfgFile_analyze         = "analyze_inclusive_cfg.py",
      samples                 = samples,
      era                     = era,
      output_tree             = output_tree,
      check_input_files       = check_input_files,
      running_method          = running_method,
      verbose                 = idx_job_resubmission > 0,
      dry_run                 = dry_run,
      isDebug                 = debug,
      rle_select              = rle_select,
      hadTauSelection_tauIdWP = tau_id_wp,
      use_nonnominal          = use_nonnominal,
      use_home                = use_home,
    )

    job_statistics = analysis.create()
    for job_type, num_jobs in job_statistics.items():
      logging.info(" #jobs of type '%s' = %i" % (job_type, num_jobs))
    job_statistics_summary[idx_job_resubmission] = job_statistics

    if idx_job_resubmission == 0:
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

    if job_statistics['analyze'] == 0:
      is_last_resubmission = True

  for idx_job_resubmission in job_statistics_summary.keys():
    logging.info("Job submission #%i:" % (idx_job_resubmission + 1))
    for job_type, num_jobs in job_statistics_summary[idx_job_resubmission].items():
      logging.info(" #jobs of type '%s' = %i" % (job_type, num_jobs))
