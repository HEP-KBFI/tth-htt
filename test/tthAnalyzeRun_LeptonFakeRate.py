#!/usr/bin/env python
import os, logging, sys, getpass

from tthAnalysis.HiggsToTauTau.configs.analyzeConfig_LeptonFakeRate import analyzeConfig_LeptonFakeRate
from tthAnalysis.HiggsToTauTau.jobTools import query_yes_no
from tthAnalysis.HiggsToTauTau.analysisSettings import systematics, get_lumi
from tthAnalysis.HiggsToTauTau.runConfig import tthAnalyzeParser, filter_samples

# E.g.: ./tthAnalyzeRun_LeptonFakeRate.py -v 2017Dec13 -e 2017

cmssw_base_dir_combine = os.path.expanduser('~/CMSSW_8_1_0') # immediate parent dir to src folder

qcd_inclusive = True # set to True if you want to process inclusive muon-enriched sample

mode_choices           = [ 'default', 'sync' ]
sys_choices            = [ 'full' ] + systematics.an_leptonFR_opts
systematics.full       = systematics.an_leptonFR

parser = tthAnalyzeParser()
parser.add_modes(mode_choices)
parser.add_sys(sys_choices)
parser.add_lep_mva_wp()
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
mode              = args.mode
systematics_label = args.systematics
lep_mva_wp        = args.lep_mva_wp
files_per_job     = args.files_per_job
use_home          = args.use_home

# Use the arguments
central_or_shifts = []
for systematic_label in systematics_label:
  for central_or_shift in getattr(systematics, systematic_label):
    if central_or_shift not in central_or_shifts:
      central_or_shifts.append(central_or_shift)
lumi = get_lumi(era)

if mode == 'default':
  if era == "2016":
    from tthAnalysis.HiggsToTauTau.samples.tthAnalyzeSamples_2016 import samples_2016 as samples
  elif era == "2017":
    from tthAnalysis.HiggsToTauTau.samples.tthAnalyzeSamples_2017 import samples_2017 as samples
  elif era == "2018":
    from tthAnalysis.HiggsToTauTau.samples.tthAnalyzeSamples_2018 import samples_2018 as samples
  else:
    raise ValueError("Invalid era: %s" % era)
elif mode == 'sync':
  if era == "2016":
    from tthAnalysis.HiggsToTauTau.samples.tthAnalyzeSamples_2017_leptonFR_sync import samples_2017 as samples
  elif era == "2017":
    from tthAnalysis.HiggsToTauTau.samples.tthAnalyzeSamples_2017_leptonFR_sync import samples_2017 as samples
  elif era == "2018":
    from tthAnalysis.HiggsToTauTau.samples.tthAnalyzeSamples_2017_leptonFR_sync import samples_2017 as samples
  else:
    raise ValueError("Invalid era: %s" % era)
else:
  raise ValueError('Invalid mode: %s' % mode)

for sample_name, sample_info in samples.items():
  if sample_name == 'sum_events': continue
  if sample_info["type"] == "mc":
    sample_info["triggers"] = [ "1e", "1mu", "2e", "2mu" ]
  if sample_name.startswith(('/MuonEG/Run', '/Tau/Run')):
      sample_info["use_it"] = False
  if sample_info["sample_category"] == "QCD":
    sample_info["use_it"] = True
    if sample_info["process_name_specific"].endswith("_Mu5"):
      sample_info["use_it"] = not qcd_inclusive
    elif sample_info["process_name_specific"] == "QCD_Mu15":
      sample_info["use_it"] = qcd_inclusive
  if era == "2017":
    if sample_name.startswith(('/DoubleEG/Run', '/SingleElectron/Run2017B')):
      # '/SingleElectron/Run2017B' excluded since no useful triggers present in that dataset
      sample_info["use_it"] = False

if __name__ == '__main__':
  logging.basicConfig(
    stream = sys.stdout,
    level  = logging.INFO,
    format = '%(asctime)s - %(levelname)s: %(message)s'
  )

  logging.info(
    "Running the jobs with the following systematic uncertainties enabled: %s" % \
    ', '.join(central_or_shifts)
  )

  if sample_filter:
    samples = filter_samples(samples, sample_filter)

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
    lep_mva_wp                               = lep_mva_wp,
    fillGenEvtHistograms                     = False,
    central_or_shifts                        = central_or_shifts,
    numerator_histogram                      = ("mT_fix_L_num",     "m_{T}^{fix,num}"), # or ("pt", "p_{T}"),
    denominator_histogram                    = ("mT_fix_L_den",     "m_{T}^{fix,den}"), # or ("EventCounter", "Number of events"),
    prep_dcard                               = True,
    max_files_per_job                        = files_per_job,
    era                                      = era,
    use_lumi                                 = True,
    lumi                                     = lumi,
    check_output_files                       = check_output_files,
    running_method                           = running_method,
    executable_addBackgrounds                = "addBackgrounds",
    executable_addBackgrounds_recursively    = "addBackgrounds_recursively",
    executable_addBackgrounds_LeptonFakeRate = "addBackground_LeptonFakeRate",
    executable_prep_dcard                    = "prepareDatacards",
    executable_comp_LeptonFakeRate           = "comp_LeptonFakeRate",
    use_QCD_fromMC                           = False,
    num_parallel_jobs                        = num_parallel_jobs,
    select_rle_output                        = True,
    dry_run                                  = dry_run,
    isDebug                                  = debug,
    use_home                                 = use_home,
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
