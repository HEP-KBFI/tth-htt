#!/usr/bin/env python
from tthAnalysis.HiggsToTauTau.configs.addMEMConfig_2lss_1tau import addMEMConfig_2lss_1tau
from tthAnalysis.HiggsToTauTau.jobTools import query_yes_no
from tthAnalysis.HiggsToTauTau.analysisSettings import systematics
from tthAnalysis.HiggsToTauTau.runConfig import tthAnalyzeParser, filter_samples
from tthAnalysis.HiggsToTauTau.common import logging, load_samples

import os
import getpass
import re

sys_choices               = [ 'full' ] + systematics.an_addMEM_opts
max_mem_integrations      = 20000
systematics.full          = systematics.an_addMEM
integration_point_choices = [ 'low', 'nominal', 'high' ]
mode_choices = {
  'default' : 'nominal',
  'bdt'     : 'nominal',
  'sync'    : 'high',
}

parser = tthAnalyzeParser(isAddMEM = True)
parser.add_modes(mode_choices.keys())
parser.add_sys(sys_choices)
parser.add_preselect()
parser.add_nonnominal()
parser.add_tau_id_wp()
parser.add_tau_id()
parser.add_use_home(False)
parser.add_jet_cleaning()
parser.add_argument('-i', '--integration-points',
  type = str, dest = 'integration_points', metavar = 'choice',
  choices = integration_point_choices, default = '', required = False,
  help = 'R|Number of integration points to use, default depends on mode (choices: %s)' % \
         tthAnalyzeParser(integration_point_choices),
)
parser.add_argument('-n', '--max-mem-integrations',
  type = int, dest = 'max_mem_integrations', metavar = 'integer', default = max_mem_integrations,
  required = False,
  help = 'R|Maximum number of input files per one job (default: %i)' % max_mem_integrations
)
parser.add_argument('-F', '--rle-filter',
  type = lambda s: s.lower() in ['true', 't', 'yes', '1'], dest = 'rle_filter', metavar = 'option', default = True,
  required = False,
  help = 'R|Apply RLE filter',
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
num_parallel_jobs  = args.num_parallel_jobs
running_method     = args.running_method

# Additional arguments
mode              = args.mode
systematics_label = args.systematics
use_preselected   = args.use_preselected
use_nonnominal    = args.original_central
use_home          = args.use_home
jet_cleaning      = args.jet_cleaning
tau_id            = args.tau_id

# Custom arguments
integration_points   = args.integration_points
max_mem_integrations = args.max_mem_integrations
rle_filter           = args.rle_filter

# Use the arguments
central_or_shifts = []
for systematic_label in systematics_label:
  for central_or_shift in getattr(systematics, systematic_label):
    if central_or_shift not in central_or_shifts:
      central_or_shifts.append(central_or_shift)
integration_choice = integration_points if integration_points else mode_choices[mode]
version            = "%s_%s_%s_%s" % (version, mode, 'nonNom' if use_nonnominal else 'nom', integration_choice)
jet_cleaning_by_index = (jet_cleaning == 'by_index')

hadTauSelection = "Tight"
rle_filter_file = ''

if mode == 'default':
  samples = load_samples(era, suffix = "preselected" if use_preselected else "")
  leptonSelection = "Fakeable"
  hadTauWP_map = {
    'dR03mva' : 'Loose',
    'deepVSj' : 'VLoose',
  }
  hadTauWP = tau_id + hadTauWP_map[tau_id]
  if rle_filter:
    rle_filter_file = 'mem_{}_{}.root'.format(era, hadTauWP)
elif mode == 'bdt':
  if use_preselected:
    raise ValueError("Makes no sense to use preselected samples w/ BDT training mode")
  samples = load_samples(era, suffix = "BDT")
  leptonSelection = "Loose"
  hadTauWP_map = {
    'dR03mva' : 'VVLoose',
    'deepVSj' : 'VVVLoose',
  }
  hadTauWP = tau_id + hadTauWP_map[tau_id]
  hadTauSelection = "Fakeable"
  if rle_filter:
    rle_filter_file = 'mem_forBDTtraining_{}_{}.root'.format(era, hadTauWP)
elif mode == 'sync':
  sample_suffix = "sync" if use_nonnominal else "sync_nom"
  if use_preselected:
    sample_suffix = "preselected_{}".format(sample_suffix)
  samples = load_samples(era, suffix = sample_suffix)
  leptonSelection = "Fakeable"
  hadTauWP_map = {
    'dR03mva' : 'Loose',
    'deepVSj' : 'VLoose',
  }
  hadTauWP = tau_id + hadTauWP_map[tau_id]
  if rle_filter:
    rle_filter_file = 'mem_sync_{}_{}.root'.format(era, hadTauWP)
else:
  raise ValueError("Invalid mode: %s" % mode)

if not mode.startswith("sync"):
  for sample_name, sample_info in samples.items():
    if sample_name == 'sum_events':
      continue
    if re.match("(^WZTo3LNu$|^WZTo3LNu_ext(\d)?$)", sample_info["process_name_specific"]):
      sample_info["use_it"] = True

if rle_filter_file:
  rle_filter_file = os.path.join(
    os.environ['CMSSW_BASE'], 'src', 'tthAnalysis', 'HiggsToTauTau', 'data', 'mem', rle_filter_file
  )
  if not os.path.isfile(rle_filter_file):
    raise ValueError("No such file: %s" % rle_filter_file)

if __name__ == '__main__':
  logging.info(
    "Running the jobs with the following systematic uncertainties enabled: %s" % \
    ', '.join(central_or_shifts)
  )

  if sample_filter:
    samples = filter_samples(samples, sample_filter)

  if args.tau_id_wp:
    logging.info("Changing tau ID WP: %s -> %s" % (hadTauWP, args.tau_id_wp))
    hadTauWP = args.tau_id_wp
  hadTauSelectionAndWP = '%s|%s' % (hadTauSelection, hadTauWP)

  addMEMProduction = addMEMConfig_2lss_1tau(
    treeName                 = 'Events',
    outputDir                = os.path.join("/hdfs/local", getpass.getuser(), "addMEM", era, version),
    cfgDir                   = os.path.join("/home",       getpass.getuser(), "addMEM", era, version),
    executable_addMEM        = "addMEM_2lss_1tau",
    samples                  = samples,
    era                      = era,
    check_output_files       = check_output_files,
    running_method           = running_method,
    max_files_per_job        = 1, # so that we'd have 1-1 correspondence b/w input and output files
    mem_integrations_per_job = 50 if mode != 'sync' else 10,
    max_mem_integrations     = max_mem_integrations, # use -1 if you don't want to limit the nof MEM integrations
    num_parallel_jobs        = num_parallel_jobs,
    leptonSelection          = leptonSelection,
    hadTauSelection          = hadTauSelectionAndWP,
    integration_choice       = integration_choice, # if False, use full integration points
    isDebug                  = debug,
    jet_cleaning_by_index    = jet_cleaning_by_index,
    central_or_shift         = central_or_shifts,
    dry_run                  = dry_run,
    use_nonnominal           = use_nonnominal,
    use_home                 = use_home,
    rle_filter_file          = rle_filter_file,
  )

  goodToGo = addMEMProduction.create()

  if goodToGo:
    if auto_exec:
      run_addMEMProduction = True
    elif no_exec:
      run_addMEMProduction = False
    else:
      run_addMEMProduction = query_yes_no("Start jobs ?")
    if run_addMEMProduction:
      addMEMProduction.run()
