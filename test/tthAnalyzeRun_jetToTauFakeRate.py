#!/usr/bin/env python
import os, logging, sys, getpass

from tthAnalysis.HiggsToTauTau.configs.analyzeConfig_jetToTauFakeRate import analyzeConfig_jetToTauFakeRate
from tthAnalysis.HiggsToTauTau.jobTools import query_yes_no
from tthAnalysis.HiggsToTauTau.analysisSettings import systematics, get_lumi
from tthAnalysis.HiggsToTauTau.runConfig import tthAnalyzeParser, filter_samples

# E.g.: ./tthAnalyzeRun_jetToTauFakeRate.py -v 2017Dec13 -e 2017

sys_choices      = [ 'full' ] + systematics.an_jetToTauFR_opts
systematics.full = systematics.an_jetToTauFR

parser = tthAnalyzeParser()
parser.add_sys(sys_choices)
parser.add_tau_id_wp()
parser.add_files_per_job()
parser.add_use_home()
parser.add_hlt_filter()
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
systematics_label = args.systematics
tau_id_wp         = args.tau_id_wp
files_per_job     = args.files_per_job
use_home          = args.use_home
hlt_filter        = args.hlt_filter

# Use the arguments
central_or_shifts = []
for systematic_label in systematics_label:
  for central_or_shift in getattr(systematics, systematic_label):
    if central_or_shift not in central_or_shifts:
      central_or_shifts.append(central_or_shift)
lumi = get_lumi(era)

if era == "2016":
  from tthAnalysis.HiggsToTauTau.samples.tthAnalyzeSamples_2016 import samples_2016 as samples
elif era == "2017":
  from tthAnalysis.HiggsToTauTau.samples.tthAnalyzeSamples_2017 import samples_2017 as samples
elif era == "2018":
  from tthAnalysis.HiggsToTauTau.samples.tthAnalyzeSamples_2018 import samples_2018 as samples
else:
  raise ValueError("Invalid era: %s" % era)

if era == "2016":
  hadTau_selection_denominator = "dR03mvaLoose"
elif era == "2017":
  hadTau_selection_denominator = "dR03mvaVLoose"
elif era == "2018":
  raise ValueError("Implement me!")
else:
  raise ValueError("Invalid era: %s" % era)

for sample_name, sample_info in samples.items():
  if sample_name == 'sum_events': continue
  if sample_info["type"] == "mc":
    sample_info["triggers"] = [ "1e", "1mu", "1e1mu" ]
  if era == "2016" and sample_name.startswith(("/DoubleMuon/", "/DoubleEG/", "/Tau/")) and \
     sample_name.find("PromptReco-v3") == -1:
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

  if tau_id_wp:
    logging.warning(
      "Changing hadTau_selection_denominator from {} to {}".format(
        hadTau_selection_denominator, tau_id_wp
      )
    )
    hadTau_selection_denominator = tau_id_wp

  analysis = analyzeConfig_jetToTauFakeRate(
    configDir = os.path.join("/home",       getpass.getuser(), "ttHAnalysis", era, version),
    outputDir = os.path.join("/hdfs/local", getpass.getuser(), "ttHAnalysis", era, version),
    executable_analyze               = "analyze_jetToTauFakeRate",
    samples                          = samples,
    charge_selections                = [ "OS" ],
    jet_minPt                        = 20.,
    jet_maxPt                        = 1.e+6,
    jet_minAbsEta                    = -1.,
    jet_maxAbsEta                    = 2.3,
    hadTau_selection_denominator     = hadTau_selection_denominator,
    hadTau_selections_numerator      = [
      "dR03mvaVLoose",
      "dR03mvaLoose",
      "dR03mvaMedium",
      "dR03mvaTight",
      "dR03mvaVTight",
      "dR03mvaVVTight",
    ],
    absEtaBins                       = [ -1., 1.479, 9.9 ],
    ptBins                           = [ 20., 25., 30., 35., 40., 45., 50., 60., 70., 80., 100., 200. ],
    central_or_shifts                = central_or_shifts,
    max_files_per_job                = files_per_job,
    era                              = era,
    use_lumi                         = True,
    lumi                             = lumi,
    check_output_files               = check_output_files,
    running_method                   = running_method,
    num_parallel_jobs                = num_parallel_jobs,
    executable_comp_jetToTauFakeRate = "comp_jetToTauFakeRate",
    hlt_filter                       = hlt_filter,
    dry_run                          = dry_run,
    isDebug                          = debug,
    use_home                         = use_home,
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
