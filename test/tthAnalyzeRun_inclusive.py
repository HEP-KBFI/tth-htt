#!/usr/bin/env python

from tthAnalysis.HiggsToTauTau.configs.analyzeConfig_inclusive import analyzeConfig_inclusive
from tthAnalysis.HiggsToTauTau.jobTools import query_yes_no
from tthAnalysis.HiggsToTauTau.analysisSettings import systematics
from tthAnalysis.HiggsToTauTau.runConfig import tthAnalyzeParser, filter_samples
from tthAnalysis.HiggsToTauTau.common import logging, load_samples

import os
import sys
import getpass

# E.g. to run: ./test/tthAnalyzeRun_inclusive.py -v 2017Dec13 -e 2017 -o syncTree

sys_choices      = [ "full" ] + systematics.an_inclusive_opts
systematics.full = systematics.an_inclusive

parser = tthAnalyzeParser()
parser.add_sys(sys_choices)
parser.add_rle_select()
parser.add_nonnominal()
parser.add_tau_id_wp()
parser.add_tau_id()
parser.add_use_home()
parser.add_jet_cleaning()
parser.add_gen_matching()
parser.add_argument('-o', '--output-tree',
  type = str, dest = 'output_tree', metavar = 'name', default = 'syncTree', required = False,
  help = 'R|Output TTree name',
)
parser.add_argument('-T', '--tau-wp-ak8',
  type = str, dest = 'tau_wp_ak8', metavar = 'wp', default = '', required = False,
  help = 'R|Tau ID WP of the taus that are used in the cleaning of AK8 jets',
)
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
running_method     = args.running_method

# Additional arguments
rle_select        = os.path.expanduser(args.rle_select)
systematics_label = args.systematics
use_nonnominal    = args.original_central
tau_id_wp         = args.tau_id_wp
use_home          = args.use_home
jet_cleaning      = args.jet_cleaning
gen_matching      = args.gen_matching
tau_id            = args.tau_id

# Custom arguments
output_tree = args.output_tree
tau_wp_ak8  = args.tau_wp_ak8

# Use the arguments
central_or_shifts = []
for systematic_label in systematics_label:
  for central_or_shift in getattr(systematics, systematic_label):
    if central_or_shift not in central_or_shifts:
      central_or_shifts.append(central_or_shift)
jet_cleaning_by_index = (jet_cleaning == 'by_index')
gen_matching_by_index = (gen_matching == 'by_index')

hadTau_WP_map = {
  'dR03mva' : 'VLoose',
  'deepVSj' : 'VLoose',
}
hadTau_WP = tau_id + hadTau_WP_map[tau_id]
if tau_id_wp:
  hadTau_WP = tau_id_wp

hadTau_WP_ak8_map = {
  'dR03mva' : 'Medium',
  'deepVSj' : 'Medium',
}
hadTau_WP_ak8 = tau_id + hadTau_WP_ak8_map[tau_id]
if tau_wp_ak8:
  hadTau_WP_ak8 = tau_wp_ak8

samples = load_samples(era, suffix = "sync" if use_nonnominal else "sync_nom")

if __name__ == '__main__':
  if sample_filter:
    samples = filter_samples(samples, sample_filter)

  logging.info(
    "Running the jobs with the following systematic uncertainties enabled: %s" % \
    ', '.join(central_or_shifts)
  )

  configDir = os.path.join("/home",       getpass.getuser(), "ttHAnalysis", era, version)
  outputDir = os.path.join("/hdfs/local", getpass.getuser(), "ttHAnalysis", era, version)

  analysis = analyzeConfig_inclusive(
    configDir               = configDir,
    outputDir               = outputDir,
    executable_analyze      = "analyze_inclusive",
    cfgFile_analyze         = "analyze_inclusive_cfg.py",
    samples                 = samples,
    era                     = era,
    output_tree             = output_tree,
    check_output_files      = check_output_files,
    running_method          = running_method,
    dry_run                 = dry_run,
    isDebug                 = debug,
    rle_select              = rle_select,
    hadTauSelection_tauIdWP = hadTau_WP,
    hadTauAk8Clean_tauIdWP  = hadTau_WP_ak8,
    jet_cleaning_by_index   = jet_cleaning_by_index,
    gen_matching_by_index   = gen_matching_by_index,
    central_or_shifts       = central_or_shifts,
    use_nonnominal          = use_nonnominal,
    use_home                = use_home,
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
