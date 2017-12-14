#!/usr/bin/env python
import os, logging, sys, getpass, argparse, datetime

from tthAnalysis.HiggsToTauTau.samples.tthAnalyzeSamples_2017_test import samples_2017
from tthAnalysis.HiggsToTauTau.configs.prodNtupleConfig import prodNtupleConfig
from tthAnalysis.HiggsToTauTau.jobTools import query_yes_no

#--------------------------------------------------------------------------------
# NOTE: set mode flag to
#   'all'                   : to produce the Ntuples from all samples
#   'forBDTtraining_only'   : to produce the Ntuples only from the FastSim samples
#   'forBDTtraining_except' : to produce the Ntuples from all but the FastSim samples
#--------------------------------------------------------------------------------

# E.g.: ./tthProdNtuple.py -v 2017Dec13 -m all -e 2017 -V -r 2

mode_choices               = ['all', 'forBDTtraining_only', 'forBDTtraining_except']
era_choices                = ['2017']
default_resubmission_limit = 4

class SmartFormatter(argparse.HelpFormatter):
  def _split_lines(self, text, width):
    if text.startswith('R|'):
      return text[2:].splitlines()
    return argparse.HelpFormatter._split_lines(self, text, width)

parser = argparse.ArgumentParser(
  formatter_class = lambda prog: SmartFormatter(prog, max_help_position = 45)
)
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
parser.add_argument('-p', '--disable-preselection',
  dest = 'disable_preselection', action = 'store_false', default = True,
  help = 'R|Disable preselection (read this script for the list of cuts)',
)
parser.add_argument('-n', '--disable-nanoaod-preprocess',
  dest = 'disable_nanoaod_preprocess', action = 'store_false', default = True,
  help = 'R|Disable nanoAOD preprocessing step',
)
parser.add_argument('-d', '--dry-run',
  dest = 'dry_run', action = 'store_true', default = False,
  help = 'R|Do not submit the jobs, just generate the necessary shell scripts'
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
parser.add_argument('-V', '--verbose',
  dest = 'verbose', action = 'store_true', default = False,
  help = 'R|Increase verbosity level in sbatchManager'
)
args = parser.parse_args()

era                = args.era
mode               = args.mode
preselection       = args.disable_preselection
nanoaod_prep       = args.disable_nanoaod_preprocess
resubmit           = args.disable_resubmission
resubmission_limit = args.resubmission_limit if resubmit else 1 # submit only once
version            = "%s_w%sPreselection_%s" % (args.version, ("" if preselection else "o"), mode)
verbose            = args.verbose
dry_run            = args.dry_run

samples         = None
leptonSelection = None
hadTauSelection = None

for sample_key, sample_entry in samples_2017.items():
  if mode == "all":
    sample_entry['use_it'] = True
  elif mode in ["forBDTtraining_only", "forBDTtraining_except"]:
    if sample_key in [
      # list of FastSim samples
    ]:
      sample_entry["use_it"] = mode == "forBDTtraining_only"
    else:
      sample_entry["use_it"] = mode != "forBDTtraining_only"
  else:
    raise ValueError("Invalid mode: %s" % mode)

if mode in ["all", "forBDTtraining_except"]:
  leptonSelection   = 'Fakeable'
  hadTauSelection   = 'Fakeable|dR03mvaMedium'
  max_files_per_job = 200
else:
  leptonSelection   = 'Loose'
  hadTauSelection   = 'Loose|dR03mvaVVLoose'
  max_files_per_job = 50

if era == "2017":
  samples = samples_2017
else:
  raise ValueError("Invalid Configuration parameter 'era' = %s !!" % era)

preselection_cuts = None
if preselection:
  preselection_cuts = {
    'minNumLeptons'              : 1,
    'minNumHadTaus'              : 1,
    'minNumLeptons_and_HadTaus'  : 2,
    'minNumJets'                 : 1,
    'minNumBJets_loose'          : 2,
    'minNumBJets_medium'         : 1,
  }
else:
  preselection_cuts = {
    'minNumLeptons'             : -1,
    'minNumHadTaus'             : -1,
    'minNumLeptons_and_HadTaus' : -1,
    'minNumJets'                : -1,
    'minNumBJets_loose'         : -1,
    'minNumBJets_medium'        : -1,
  }

if __name__ == '__main__':
  logging.basicConfig(
    stream = sys.stdout,
    level = logging.INFO,
    format = '%(asctime)s - %(levelname)s: %(message)s')

  for resubmission_idx in range(resubmission_limit):
    logging.info("Submission attempt #%i" % (resubmission_idx + 1))
    ntupleProduction = prodNtupleConfig(
      configDir = os.path.join("/home",       getpass.getuser(), "ttHNtupleProduction", era, version),
      outputDir = os.path.join("/hdfs/local", getpass.getuser(), "ttHNtupleProduction", era, version),
      executable_nanoAOD    = "produceNtuple.sh",
      executable_prodNtuple = "produceNtuple",
      cfgFile_prodNtuple    = "produceNtuple_cfg.py",
      samples               = samples,
      max_files_per_job     = max_files_per_job,
      era                   = era,
      preselection_cuts     = preselection_cuts,
      leptonSelection       = leptonSelection,
      hadTauSelection       = hadTauSelection,
      nanoaod_prep          = nanoaod_prep,
      debug                 = False,
      running_method        = "sbatch",
      version               = version,
      num_parallel_jobs     = 8,
      verbose               = verbose,
      dry_run               = dry_run,
    )

    num_jobs = ntupleProduction.create()

    if num_jobs > 0:
      run_ntupleProduction = query_yes_no("Start jobs ?") if resubmission_idx == 0 else True
      if run_ntupleProduction:
        ntupleProduction.run()
      else:
        sys.exit(0)
    else:
      logging.info("All jobs done")
