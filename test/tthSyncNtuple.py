#!/usr/bin/env python

# INSTRUCTIONS ON HOW TO RUN SYNC NTUPLE PRODUCTION:
#
# 1) Copy the MINIAODSIM via xrootd (requires VOMS proxy to be open):
#
# xrdcp root://cms-xrd-global.cern.ch/$LFN /hdfs/local/$USER/$LFN
#
# where $LFN is the full logical file name that the analysis groups have agreed upon. In the first
# (source) path of the above command you must keep the leading slash whereas in the second
# (destination) path you can drop the slash. $USER refers to your UNIX user name.
#
# 2) generate the ,,bare'' nanoAOD Ntuple by running:
# $CMSSW_BASE/src/tthAnalysis/NanoAOD/test/runLocally.py       \
# -i /hdfs/local/$USER/$LFN                                    \
# -o /hdfs/local/$USER/sync_ntuples/nanoAODproduction/$VERSION \
# -n ttHJetToNonbb_M125_amcatnlo                               \
# -t mc                                                        \
# -s /home/$USER/sync_ntuples/nanoAODproduction/$VERSION       \
# -v
#
# make -f /home/$USER/sync_ntuples/nanoAODproduction/$VERSION/Makefile_nanoAOD \
# 2>/home/$USER/sync_ntuples/nanoAODproduction/$VERSION/stderr.log             \
# 1>/home/$USER/sync_ntuples/nanoAODproduction/$VERSION/stdout.log
#
# Here $VERSION is helpful to keep track of the output files.
#
# 3) Update the value of samples_$ERA[sync_key]['local_paths'][0]['path'] in file
# $CMSSW_BASE/src/tthAnalysis/HiggsToTauTau/python/samples/tthAnalyzeSamples_$ERA_nanoAOD_sync.py
# to /hdfs/local/$USER/sync_ntuples/nanoAODproduction/$VERSION/ttHJetToNonbb_M125_amcatnlo
#
# 4) Run
#
# tthProdNtuple.py -m sync -e $ERA -v $VERSION -p
#
# to add missing branches nanoAOD-tools modules and perform basic
# object-level selection.
#
# 5) Update the value of samples_$ERA[sync_key]['local_paths'][0]['path'] in file
# $CMSSW_BASE/src/tthAnalysis/HiggsToTauTau/python/samples/tthAnalyzeSamples_$ERA_sync.py to
# /hdfs/local/$USER/ttHNtupleProduction/$ERA/$VERSION_wNanoPrep_woPresel_sync/ntuples/ttHJetToNonbb_M125_amcatnlo
#
# 6) Now you're ready to run this script
#
# WHAT THIS SCRIPT DOES
#
# The script generates Makefiles for individual analyses with 'sync' mode enabled. The choice of
# analyses which produce the sync Ntuple can be specified from the command line. The path to these
# Makefiles is recorded and their final output files are assumed implicitly. This information is
# then used to build a ,,grand'' Makefile which runs all specified analyses, preferably in parallel.
# The final target of this master Makefile hadd-s the individual outputs of each sync Ntuple job
# together.

from tthAnalysis.HiggsToTauTau.configs.syncNtupleConfig import syncNtupleConfig
from tthAnalysis.HiggsToTauTau.jobTools import query_yes_no
import argparse, datetime, logging, sys, getpass, os.path

era_choices                = ['2017']
channel_choices            = ['1l_2tau', '2lss_1tau', '3l_1tau']
default_resubmission_limit = 4

class SmartFormatter(argparse.HelpFormatter):
  def _split_lines(self, text, width):
    if text.startswith('R|'):
      return text[2:].splitlines()
    return argparse.HelpFormatter._split_lines(self, text, width)

parser = argparse.ArgumentParser(
  formatter_class = lambda prog: SmartFormatter(prog, max_help_position = 45)
)
run_parser = parser.add_mutually_exclusive_group()
parser.add_argument('-v', '--version',
  type = str, dest = 'version', metavar = 'version', default = None, required = True,
  help = 'R|Analysis version (e.g. %s)' % datetime.date.today().strftime('%Y%b%d'),
)
parser.add_argument('-e', '--era',
  type = str, dest = 'era', metavar = 'era', choices = era_choices, default = None, required = True,
  help = 'R|Era of data/MC (choices: %s)' % ', '.join(map(lambda choice: "'%s'" % choice, era_choices)),
)
parser.add_argument('-c', '--channels',
  type = str, nargs = '+', dest = 'channels', metavar = 'channel', choices = channel_choices,
  default = channel_choices, required = False,
  help = 'R|Choice of analyses for which the sync Ntuple is used (choices: %s)' % \
          ', '.join(map(lambda choice: "'%s'" % choice, channel_choices))
)
parser.add_argument('-o', '--output',
  type = str, dest = 'output', metavar = 'file', default = 'sync_Tallinn.root',
)
parser.add_argument('-C', '--clean',
  dest = 'clean', action = 'store_true', default = False,
  help = 'R|Remove all output files'
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
run_parser.add_argument('-E', '--no-exec',
  dest = 'no_exec', action = 'store_true', default = False,
  help = 'R|Do not submit the jobs (ignore prompt)',
)
run_parser.add_argument('-A', '--auto-exec',
  dest = 'auto_exec', action = 'store_true', default = False,
  help = 'R|Automatically submit the jobs (ignore prompt)',
)
parser.add_argument('-V', '--verbose',
  dest = 'verbose', action = 'store_true', default = False,
  help = 'R|Increase verbosity level in sbatchManager'
)
args = parser.parse_args()

no_exec   = args.no_exec
auto_exec = args.auto_exec

if __name__ == '__main__':
  logging.basicConfig(
    stream = sys.stdout,
    level  = logging.INFO,
    format = '%(asctime)s - %(levelname)s: %(message)s',
  )

  analysis = syncNtupleConfig(
    config_dir = os.path.join("/home",       getpass.getuser(), "ttHAnalysis", args.era, args.version),
    output_dir = os.path.join("/hdfs/local", getpass.getuser(), "ttHAnalysis", args.era, args.version),
    output_filename      = args.output,
    version              = args.version,
    era                  = args.era,
    channels             = args.channels,
    dry_run              = args.dry_run,
    resubmission_limit   = args.resubmission_limit,
    disable_resubmission = args.disable_resubmission,
    verbose              = args.verbose,
  )

  job_statistics = analysis.create()

  if auto_exec:
    run_analysis = True
  elif no_exec:
    run_analysis = False
  else:
    run_analysis = query_yes_no("Start jobs ?")
  if run_analysis:
    analysis.run(args.clean)
  else:
    sys.exit(0)
