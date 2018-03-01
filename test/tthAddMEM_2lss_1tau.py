#!/usr/bin/env python
import os, logging, sys, getpass, argparse, datetime

from tthAnalysis.HiggsToTauTau.configs.addMEMConfig_2lss_1tau import addMEMConfig_2lss_1tau
from tthAnalysis.HiggsToTauTau.jobTools import query_yes_no
from tthAnalysis.HiggsToTauTau.analysisSettings import systematics

era_choices                = ['2017']
sys_choices                = [ 'central', 'full' ]
default_resubmission_limit = 4
max_mem_integrations       = 20000
systematics.full           = systematics.an_addMEM
mode_choices               = ['default', 'bdt', 'sync']

class SmartFormatter(argparse.HelpFormatter):
  def _split_lines(self, text, width):
    if text.startswith('R|'):
      return text[2:].splitlines()
    return argparse.HelpFormatter._split_lines(self, text, width)

parser = argparse.ArgumentParser(
  formatter_class = lambda prog: SmartFormatter(prog, max_help_position = 50)
)
run_parser = parser.add_mutually_exclusive_group()
parser.add_argument('-v', '--version',
  type = str, dest = 'version', metavar = 'version', default = None, required = True,
  help = 'R|Analysis version (e.g. %s)' % datetime.date.today().strftime('%Y%b%d'),
)
parser.add_argument('-m', '--mode',
  type = str, dest = 'mode', metavar = 'mode', default = None, required = True,
  choices = mode_choices,
  help = 'R|Analysis type (choices: %s)' % ', '.join(map(lambda choice: "'%s'" % choice, mode_choices)),
)
parser.add_argument('-e', '--era',
  type = str, dest = 'era', metavar = 'era', choices = era_choices, default = None, required = True,
  help = 'R|Era of data/MC (choices: %s)' % ', '.join(map(lambda choice: "'%s'" % choice, era_choices)),
)
parser.add_argument('-s', '--systematics',
  type = str, dest = 'systematics', metavar = 'mode', choices = sys_choices,
  default = 'central', required = False,
  help = 'R|Systematic uncertainties (choices: %s)' % ', '.join(map(lambda choice: "'%s'" % choice, sys_choices)),
)
parser.add_argument('-n', '--max-mem-integrations',
  type = int, dest = 'max_mem_integrations', metavar = 'integer', default = max_mem_integrations, required = False,
  help = 'R|Maximum number of input files per one job (default: %i)' % max_mem_integrations
)
parser.add_argument('-r', '--resubmission-limit',
  type = int, dest = 'resubmission_limit', metavar = 'number', default = default_resubmission_limit,
  required = False,
  help = 'R|Maximum number of resubmissions (default: %i)' % default_resubmission_limit
)
parser.add_argument('-R', '--disable-resubmission',
  dest = 'disable_resubmission', action = 'store_false', default = True,
  help = 'R|Disable resubmission (overwrites option -r/--resubmission-limit)'
)
run_parser.add_argument('-E', '--no-exec',
  dest = 'no_exec', action = 'store_true', default = False,
  help = 'R|Do not submit the jobs (ignore prompt)',
)
run_parser.add_argument('-A', '--auto-exec',
  dest = 'auto_exec', action = 'store_true', default = False,
  help = 'R|Automatically submit the jobs (ignore prompt)',
)
args = parser.parse_args()

era                  = args.era
version              = args.version
resubmit             = args.disable_resubmission
max_job_resubmission = args.resubmission_limit if resubmit else 1
no_exec              = args.no_exec
auto_exec            = args.auto_exec
max_mem_integrations = args.max_mem_integrations
central_or_shift     = getattr(systematics, args.systematics)
mode                 = args.mode

if mode == 'default':
  from tthAnalysis.HiggsToTauTau.samples.tthAnalyzeSamples_2017 import samples_2017 as samples

  leptonSelection = "Fakeable"
  hadTauSelection = "Tight|dR03mvaMedium"
elif mode == 'bdt':
  from tthAnalysis.HiggsToTauTau.samples.tthAnalyzeSamples_2017_FastSim import samples_2017 as samples

  leptonSelection = "Loose"
  hadTauSelection = "Tight|dR03mvaMedium"
elif mode == 'sync':
  from tthAnalysis.HiggsToTauTau.samples.tthAnalyzeSamples_2017_sync import samples_2017 as samples

  leptonSelection = "Fakeable"
  hadTauSelection = "Tight|dR03mvaMedium"
else:
  raise ValueError("Internal logic error")

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
    debug                    = False,
    running_method           = "sbatch",
    max_files_per_job        = 1, # so that we'd have 1-1 correspondence b/w input and output files
    mem_integrations_per_job = 50,
    max_mem_integrations     = max_mem_integrations, # use -1 if you don't want to limit the nof MEM integrations
    num_parallel_jobs        = 16,
    leptonSelection          = leptonSelection,
    hadTauSelection          = hadTauSelection,
    isForBDTtraining         = mode == 'bdt', # if False, use full integration points
    isDebug                  = True,
    central_or_shift         = central_or_shift,
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
