#!/usr/bin/env python
import os, logging, sys, getpass

from tthAnalysis.HiggsToTauTau.configs.analyzeConfig_LeptonFakeRate import analyzeConfig_LeptonFakeRate
from tthAnalysis.HiggsToTauTau.jobTools import query_yes_no
from tthAnalysis.HiggsToTauTau.analysisSettings import systematics
from tthAnalysis.HiggsToTauTau.runConfig import tthAnalyzeParser, filter_samples

# E.g.: ./tthAnalyzeRun_LeptonFakeRate.py -v 2017Dec13 -e 2017

cmssw_base_dir_combine = os.path.expanduser('~/CMSSW_8_1_0') # immediate parent dir to src folder



mode_choices           = [ 'default', 'sync' ]
sys_choices            = [ 'central', 'full' ]
systematics.full       = systematics.an_leptonFR

parser = tthAnalyzeParser()
parser.add_modes(mode_choices)
parser.add_sys(sys_choices)
parser.add_files_per_job()
parser.add_use_home()
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
num_parallel_jobs  = args.num_parallel_jobs
running_method     = args.running_method

# Additional arguments
mode              = args.mode
systematics_label = args.systematics
files_per_job     = args.files_per_job
use_home          = args.use_home

# Use the arguments
central_or_shift = getattr(systematics, systematics_label)

if era == "2017":
  if mode == 'default':
    from tthAnalysis.HiggsToTauTau.samples.tthAnalyzeSamples_2017 import samples_2017 as samples
  elif mode == 'sync':
    from tthAnalysis.HiggsToTauTau.samples.tthAnalyzeSamples_2017_leptonFR_test3 import samples_2017 as samples
  else:
    raise ValueError('Invalid mode: %s' % mode)
  from tthAnalysis.HiggsToTauTau.analysisSettings import lumi_2017 as lumi
else:
  raise ValueError("Invalid era: %s" % era)

for sample_name, sample_info in samples.items():
  if sample_info["type"] == "mc":
    sample_info["triggers"] = [ "1e", "1mu", "2e", "2mu" ]
  if sample_name.startswith(('/MuonEG/Run', '/Tau/Run', '/DoubleEG/Run', '/SingleElectron/Run2017B')): # '/SingleElectron/Run2017B' added since no useful triggers present in that dataset
      sample_info["use_it"] = False

if __name__ == '__main__':
  logging.basicConfig(
    stream = sys.stdout,
    level  = logging.INFO,
    format = '%(asctime)s - %(levelname)s: %(message)s'
  )

  logging.info(
    "Running the jobs with the following systematic uncertainties enabled: %s" % \
    ', '.join(central_or_shift)
  )

  if sample_filter:
    samples = filter_samples(samples, sample_filter)

  job_statistics_summary = {}
  run_analysis           = False
  is_last_resubmission   = False

  for idx_job_resubmission in range(resubmission_limit):
    if is_last_resubmission:
      continue

    analysis = analyzeConfig_LeptonFakeRate(
      configDir = os.path.join("/home",       getpass.getuser(), "ttHAnalysis", era, version),
      outputDir = os.path.join("/hdfs/local", getpass.getuser(), "ttHAnalysis", era, version),
      cmssw_base_dir_combine                   = cmssw_base_dir_combine,
      executable_analyze                       = "analyze_LeptonFakeRate",
      samples                                  = samples,
      absEtaBins_e                             = [ 0., 1.479, 2.5 ],                     ## CERN binning scheme
      absEtaBins_mu                            = [ 0., 1.2, 2.4 ],                       ## CERN binning scheme
      ptBins_e                                 = [ 15., 25., 35., 45., 65., 100. ],      ## CERN binning scheme
      ptBins_mu                                = [ 10., 15., 20., 32., 45., 65., 100. ], ## CERN binning scheme
      fillGenEvtHistograms                     = False,
      central_or_shifts                        = central_or_shift,
      numerator_histogram                      = ("mT_fix_L",     "m_{T}^{fix}"), # or ("pt", "p_{T}"),
      denominator_histogram                    = ("EventCounter", "Number of events"),
      prep_dcard                               = True,
      max_files_per_job                        = files_per_job,
      era                                      = era,
      use_lumi                                 = True,
      lumi                                     = lumi,
      check_input_files                        = check_input_files,
      running_method                           = running_method,
      executable_addBackgrounds                = "addBackgrounds",
      executable_addBackgrounds_recursively    = "addBackgrounds_recursively",
      executable_addBackgrounds_LeptonFakeRate = "addBackground_LeptonFakeRate",
      executable_prep_dcard                    = "prepareDatacards",
      executable_comp_LeptonFakeRate           = "comp_LeptonFakeRate",
      num_parallel_jobs                        = num_parallel_jobs,
      select_rle_output                        = True,
      verbose                                  = idx_job_resubmission > 0,
      dry_run                                  = dry_run,
      isDebug                                  = debug,
      use_home                                 = use_home,
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
    logging.info("Job (re)submission #%i:" % (idx_job_resubmission + 1))
    for job_type, num_jobs in job_statistics_summary[idx_job_resubmission].items():
      logging.info(" #jobs of type '%s' = %i" % (job_type, num_jobs))
