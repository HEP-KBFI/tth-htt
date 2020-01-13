#!/usr/bin/env python

from tthAnalysis.HiggsToTauTau.configs.analyzeConfig_jetToTauFakeRate import analyzeConfig_jetToTauFakeRate
from tthAnalysis.HiggsToTauTau.jobTools import query_yes_no
from tthAnalysis.HiggsToTauTau.analysisSettings import systematics, get_lumi
from tthAnalysis.HiggsToTauTau.runConfig import tthAnalyzeParser, filter_samples
from tthAnalysis.HiggsToTauTau.common import logging, load_samples_aux as load_samples

import os
import sys
import getpass

# E.g.: ./test/tthAnalyzeRun_jetToTauFakeRate.py -v 2017Dec13 -e 2017

sys_choices      = [ 'full' ] + systematics.an_jetToTauFR_opts
systematics.full = systematics.an_jetToTauFR

parser = tthAnalyzeParser()
parser.add_sys(sys_choices)
parser.add_tau_id_wp(required = True, choices = [ 'dR03mvaVVLoose', 'dR03mvaVLoose', 'deepVSjVVVLoose', 'deepVSjVVLoose' ])
parser.add_files_per_job()
parser.add_use_home()
parser.add_jet_cleaning()
parser.add_gen_matching()
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
jet_cleaning      = args.jet_cleaning
gen_matching      = args.gen_matching

# Use the arguments
central_or_shifts = []
for systematic_label in systematics_label:
  for central_or_shift in getattr(systematics, systematic_label):
    if central_or_shift not in central_or_shifts:
      central_or_shifts.append(central_or_shift)
lumi = get_lumi(era)
jet_cleaning_by_index = (jet_cleaning == 'by_index')
gen_matching_by_index = (gen_matching == 'by_index')

tau_id = tau_id_wp[:7]
hadTau_selection_tight_map = {
  'dR03mva' : 'Loose',
  'deepVSj' : 'Loose',
}
hadTau_selection_tight = tau_id + hadTau_selection_tight_map[tau_id]

hadTau_WP_range = [ 'VVVLoose', 'VVLoose', 'VLoose', 'Loose', 'Medium', 'Tight', 'VTight', 'VVTight' ]
hadTau_denominator_wp = tau_id_wp[7:]
hadTau_numerators = [
  tau_id + hadTau_WP_range[idx] for idx in range(hadTau_WP_range.index(hadTau_denominator_wp) + 1, len(hadTau_WP_range))
]
assert(tau_id_wp not in hadTau_numerators)
logging.info(
  'Using {} for the denomintor and the following tau ID WPs for the numerator: {}'.format(
    tau_id_wp,
    ', '.join(hadTau_numerators)),
)

samples = load_samples(era)
for sample_name, sample_info in samples.items():
  if sample_name == 'sum_events':
    continue
  if sample_info["type"] == "mc":
    sample_info["triggers"] = [ "1e", "1mu", "1e1mu" ]
  if sample_name.startswith(("/DoubleMuon/", "/DoubleEG/", "/Tau/")) and sample_name.find("PromptReco") == -1:
      sample_info["use_it"] = False

if __name__ == '__main__':
  logging.info(
    "Running the jobs with the following systematic uncertainties enabled: %s" % \
    ', '.join(central_or_shifts)
  )

  if sample_filter:
    samples = filter_samples(samples, sample_filter)

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
    hadTau_selection_tight           = hadTau_selection_tight,
    hadTau_selection_denominator     = tau_id_wp,
    hadTau_selections_numerator      = hadTau_numerators,
    absEtaBins                       = [ -1., 1.479, 9.9 ],
    ptBins                           = [ 20., 25., 30., 35., 40., 45., 50., 60., 70., 80., 100., 200. ],
    decayModes                       = [ -1, 0, 1, 2, 5, 6, 10, 11 ],
    jet_cleaning_by_index            = jet_cleaning_by_index,
    gen_matching_by_index            = gen_matching_by_index,
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
    select_rle_output                = True,
    dry_run                          = dry_run,
    isDebug                          = debug,
    use_home                         = use_home,
    submission_cmd                   = sys.argv,
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
