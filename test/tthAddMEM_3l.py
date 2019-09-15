#!/usr/bin/env python

from tthAnalysis.HiggsToTauTau.configs.addMEMConfig_3l import addMEMConfig_3l
from tthAnalysis.HiggsToTauTau.jobTools import query_yes_no
from tthAnalysis.HiggsToTauTau.analysisSettings import systematics
from tthAnalysis.HiggsToTauTau.runConfig import tthAnalyzeParser, filter_samples
from tthAnalysis.HiggsToTauTau.common import logging, load_samples

import os
import getpass

sys_choices          = [ 'full' ] + systematics.an_addMEM_opts
mode_choices         = [ 'default', 'bdt', 'sync' ]
max_mem_integrations = 100000
systematics.full     = systematics.an_addMEM

parser = tthAnalyzeParser(isAddMEM = True)
parser.add_modes(mode_choices)
parser.add_sys(sys_choices)
parser.add_preselect()
parser.add_nonnominal()
parser.add_use_home(False)
parser.add_jet_cleaning()
parser.add_argument('-n', '--max-mem-integrations',
  type = int, dest = 'max_mem_integrations', metavar = 'integer', default = max_mem_integrations,
  required = False,
  help = 'R|Maximum number of input files per one job (default: %i)' % max_mem_integrations
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

# Custom arguments
max_mem_integrations = args.max_mem_integrations

# Use the arguments
central_or_shifts = []
for systematic_label in systematics_label:
  for central_or_shift in getattr(systematics, systematic_label):
    if central_or_shift not in central_or_shifts:
      central_or_shifts.append(central_or_shift)
version = "%s_%s_%s" % (version, mode, 'nonNom' if use_nonnominal else 'nom')
jet_cleaning_by_index = (jet_cleaning == 'by_index')

if mode == 'default':
  samples = load_samples(era, suffix = "preselected" if use_preselected else "")
  leptonSelection = "Fakeable"
elif mode == 'bdt':
  if use_preselected:
    raise ValueError("Makes no sense to use preselected samples w/ BDT training mode")
  samples = load_samples(era, suffix = "BDT")
  leptonSelection = "Loose"
elif mode == 'sync':
  sample_suffix = "sync" if use_nonnominal else "sync_nom"
  if use_preselected:
    sample_suffix = "preselected_{}".format(sample_suffix)
  samples = load_samples(era, suffix = sample_suffix)
  leptonSelection = "Fakeable"
else:
  raise ValueError("Invalid mode: %s" % mode)

if __name__ == '__main__':
  logging.info(
    "Running the jobs with the following systematic uncertainties enabled: %s" % \
    ', '.join(central_or_shifts)
  )

  if sample_filter:
    samples = filter_samples(samples, sample_filter)

  addMEMProduction = addMEMConfig_3l(
    treeName                 = 'Events',
    outputDir                = os.path.join("/hdfs/local", getpass.getuser(), "addMEM", era, version),
    cfgDir                   = os.path.join("/home",       getpass.getuser(), "addMEM", era, version),
    executable_addMEM        = "addMEM_3l",
    samples                  = samples,
    era                      = era,
    check_output_files       = check_output_files,
    running_method           = running_method,
    max_files_per_job        = 1, # so that we'd have 1-1 correspondence b/w input and output files
    mem_integrations_per_job = 50,
    max_mem_integrations     = max_mem_integrations, # use -1 if you don't want to limit the nof MEM integrations
    num_parallel_jobs        = num_parallel_jobs,
    leptonSelection          = leptonSelection,
    isDebug                  = debug,
    jet_cleaning_by_index    = jet_cleaning_by_index,
    central_or_shift         = central_or_shifts,
    dry_run                  = dry_run,
    use_nonnominal           = use_nonnominal,
    use_home                 = use_home,
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
