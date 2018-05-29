#!/usr/bin/env python
import os, logging, sys, getpass

from tthAnalysis.HiggsToTauTau.configs.addMEMConfig_3l_1tau import addMEMConfig_3l_1tau
from tthAnalysis.HiggsToTauTau.jobTools import query_yes_no
from tthAnalysis.HiggsToTauTau.analysisSettings import systematics
from tthAnalysis.HiggsToTauTau.runConfig import tthAnalyzeParser, filter_samples

sys_choices          = [ 'central', 'full' ]
mode_choices         = [ 'default', 'bdt' ]
max_mem_integrations = 20000
systematics.full     = systematics.an_addMEM

parser = tthAnalyzeParser(isAddMEM = True)
parser.add_modes(mode_choices)
parser.add_sys(sys_choices)
parser.add_nonnominal()
parser.add_tau_id_wp()
parser.add_use_home(False)
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
use_nonnominal    = args.original_central
use_home          = args.use_home

# Custom arguments
integration_points   = args.integration_points
max_mem_integrations = args.max_mem_integrations

# Use the arguments
central_or_shift = getattr(systematics, systematics_label)
version          = "%s_%s_%s" % (version, mode, 'nonNom' if use_nonnominal else 'nom')

if mode == 'default':
  from tthAnalysis.HiggsToTauTau.samples.tthAnalyzeSamples_2017_prodNtuples import samples_2017

  leptonSelection = "Fakeable"
  hadTauSelection = "Tight"
  hadTauWP        = "dR03mvaLoose"
elif mode == 'bdt':
  from tthAnalysis.HiggsToTauTau.samples.tthAnalyzeSamples_2017_BDT import samples_2017

  leptonSelection = "Loose"
  hadTauSelection = "Tight"
  hadTauWP        = "dR03mvaVVLoose"
else:
  raise ValueError("Internal logic error")

if era == "2017":
  samples = samples_2017
else:
  raise ValueError("Invalid era: %s" % era)


if __name__ == '__main__':
  logging.basicConfig(
    stream = sys.stdout,
    level  = logging.DEBUG,
    format = '%(asctime)s - %(levelname)s: %(message)s'
  )

  logging.info(
    "Running the jobs with the following systematic uncertainties enabled: %s" % \
    ', '.join(central_or_shift)
  )

  if sample_filter:
    samples = filter_samples(samples, sample_filter)

  if args.tau_id_wp:
    logging.info("Changing tau ID WP: %s -> %s" % (hadTauWP, args.tau_id_wp))
    hadTauWP = args.tau_id_wp
  hadTauSelectionAndWP = '%s|%s' % (hadTauSelection, hadTauWP)

  addMEMProduction = addMEMConfig_3l_1tau(
    treeName                 = 'Events',
    outputDir                = os.path.join("/hdfs/local", getpass.getuser(), "addMEM", era, version),
    cfgDir                   = os.path.join("/home",       getpass.getuser(), "addMEM", era, version),
    executable_addMEM        = "addMEM_3l_1tau",
    samples                  = samples,
    era                      = era,
    check_input_files        = check_input_files,
    running_method           = running_method,
    max_files_per_job        = 1, # so that we'd have 1-1 correspondence b/w input and output files
    mem_integrations_per_job = 50,
    max_mem_integrations     = max_mem_integrations, # use -1 if you don't want to limit the nof MEM integrations
    num_parallel_jobs        = num_parallel_jobs,
    leptonSelection          = leptonSelection,
    hadTauSelection          = hadTauSelectionAndWP,
    lowIntegrationPoints     = False, # has no effect in 3l1tau MEM, the nof integration points fixed
    isDebug                  = debug,
    central_or_shift         = central_or_shift,
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
      for resubmission_idx in range(resubmission_limit):
        logging.info("Submission attempt #%i" % (resubmission_idx + 1))
        addMEMProduction.run()
