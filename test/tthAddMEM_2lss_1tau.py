#!/usr/bin/env python
import os, logging, sys, getpass

from tthAnalysis.HiggsToTauTau.configs.addMEMConfig_2lss_1tau import addMEMConfig_2lss_1tau
from tthAnalysis.HiggsToTauTau.jobTools import query_yes_no
from tthAnalysis.HiggsToTauTau.analysisSettings import systematics
from tthAnalysis.HiggsToTauTau.runConfig import tthAnalyzeParser

sys_choices               = [ 'central', 'full' ]
max_mem_integrations      = 20000
systematics.full          = systematics.an_addMEM
integration_point_choices = {
  'small' : True,
  'full'  : False,
}
mode_choices = {
  'default' : 'full',
  'bdt'     : 'small',
  'sync'    : 'full',
}

parser = tthAnalyzeParser(isAddMEM = True)
parser.add_modes(mode_choices.keys())
parser.add_sys(sys_choices)
parser.add_argument('-i', '--integration-points',
  type = str, dest = 'integration_points', metavar = 'choice',
  choices = integration_point_choices.keys(), default = None, required = False,
  help = 'R|Number of integration points to use, default depends on mode (choices: %s)' % \
         tthAnalyzeParser(integration_point_choices.keys()),
)
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
resubmit           = not args.disable_resubmission
no_exec            = args.no_exec
auto_exec          = args.auto_exec
check_input_files  = args.check_input_files
debug              = args.debug

# Additional arguments
mode              = args.mode
systematics_label = args.systematics

# Custom arguments
integration_points   = args.integration_points
max_mem_integrations = args.max_mem_integrations

# Use the arguments
central_or_shift     = getattr(systematics, systematics_label)
integration_choice   = integration_point_choices[integration_points] if integration_points \
                       else integration_point_choices[mode_choices[mode]]
max_job_resubmission = resubmission_limit if resubmit else 1
version              = "%s_%s_%s" % (version, mode, 'small' if integration_choice else 'full')

if mode == 'default':
  from tthAnalysis.HiggsToTauTau.samples.tthAnalyzeSamples_2017 import samples_2017

  leptonSelection = "Fakeable"
  hadTauSelection = "Tight|dR03mvaMedium"
elif mode == 'bdt':
  from tthAnalysis.HiggsToTauTau.samples.tthAnalyzeSamples_2017_FastSim import samples_2017

  leptonSelection = "Loose"
  hadTauSelection = "Tight|dR03mvaMedium"
elif mode == 'sync':
  from tthAnalysis.HiggsToTauTau.samples.tthAnalyzeSamples_2017_sync import samples_2017

  leptonSelection = "Fakeable"
  hadTauSelection = "Tight|dR03mvaMedium"
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

  addMEMProduction = addMEMConfig_2lss_1tau(
    treeName                 = 'Events',
    outputDir                = os.path.join("/hdfs/local", getpass.getuser(), "addMEM", era, version),
    cfgDir                   = os.path.join("/home",       getpass.getuser(), "addMEM", era, version),
    executable_addMEM        = "addMEM_2lss_1tau",
    samples                  = samples,
    era                      = era,
    check_input_files        = check_input_files,
    running_method           = "sbatch",
    max_files_per_job        = 1, # so that we'd have 1-1 correspondence b/w input and output files
    mem_integrations_per_job = 50,
    max_mem_integrations     = max_mem_integrations, # use -1 if you don't want to limit the nof MEM integrations
    num_parallel_jobs        = 16,
    leptonSelection          = leptonSelection,
    hadTauSelection          = hadTauSelection,
    lowIntegrationPoints     = integration_choice, # if False, use full integration points
    isDebug                  = debug,
    central_or_shift         = central_or_shift,
    dry_run                  = dry_run,
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
      for resubmission_idx in range(max_job_resubmission):
        logging.info("Submission attempt #%i" % (resubmission_idx + 1))
        addMEMProduction.run()
