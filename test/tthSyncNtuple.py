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
# 4) Rebuild (i.e. clean and then build) this project with SYNC_NTUPLE definition enabled:
#
# scram b clean -j8 && scram b -j8 USER_CXXFLAGS="-DSYNC_NTUPLE"
#
# This enables the reading of some branches that otherwise are not enabled (e.g. muon's pT error,
# and electron's and muon's jetPtRel variables) since they're not used in the analysis in any way.
#
# 5) Run
#
# tthProdNtuple.py -m sync -e $ERA -v $VERSION -p
#
# to add missing branches nanoAOD-tools modules and perform basic
# object-level selection.
#
# 6) Update the value of samples_$ERA[sync_key]['local_paths'][0]['path'] in file
# $CMSSW_BASE/src/tthAnalysis/HiggsToTauTau/python/samples/tthAnalyzeSamples_$ERA_sync.py to
# /hdfs/local/$USER/ttHNtupleProduction/$ERA/$VERSION_wNanoPrep_woPresel_sync/ntuples/ttHJetToNonbb_M125_amcatnlo
#
# 7) Now you're ready to run this script
#
# WHAT THIS SCRIPT DOES
#
# The script generates Makefiles for individual analyses with 'sync' mode enabled. The choice of
# analyses which produce the sync Ntuple can be specified from the command line. The path to these
# Makefiles is recorded and their final output files are assumed implicitly. This information is
# then used to build a ,,grand'' Makefile which runs all specified analyses, preferably in parallel.
# The final target of this master Makefile hadd-s the individual outputs of each sync Ntuple job
# together.

import os, logging, sys, getpass

from tthAnalysis.HiggsToTauTau.configs.syncNtupleConfig import syncNtupleConfig
from tthAnalysis.HiggsToTauTau.jobTools import query_yes_no
from tthAnalysis.HiggsToTauTau.runConfig import tthAnalyzeParser
from tthAnalysis.HiggsToTauTau.analysisSettings import systematics

sys_choices     = systematics.an_inclusive_opts
channel_choices = [
  '0l_2tau', '1l_2tau', '2lss', '2lss_1tau', '2los_1tau', '2l_2tau', '3l', '3l_1tau', '4l', 'inclusive',
  'ttWctrl', 'ttZctrl', 'WZctrl','ZZctrl',
]

parser = tthAnalyzeParser()
parser.add_rle_select()
parser.add_nonnominal()
parser.add_hlt_filter()
parser.add_tau_id_wp()
parser.add_use_home()
parser.add_sys(sys_choices)
parser.add_argument('-c', '--channels',
  type = str, nargs = '+', dest = 'channels', metavar = 'channel', choices = channel_choices,
  default = channel_choices, required = False,
  help = 'R|Choice of analyses for which the sync Ntuple is used (choices: %s)' % \
         tthAnalyzeParser.cat(channel_choices),
)
parser.add_argument('-o', '--output',
  type = str, dest = 'output', metavar = 'filename', default = 'sync_Tallinn.root',
  help = 'R|Final output filename',
)
parser.add_argument('-X', '--clean',
  dest = 'clean', action = 'store_true', default = False, help = 'R|Remove all output files',
)
parser.add_argument('-M', '--with-mem',
  dest = 'with_mem', action = 'store_true', default = False, help = 'R|Use Ntuple w/ MEM included',
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
running_method     = args.running_method

# Additional arguments
rle_select        = os.path.expanduser(args.rle_select)
use_nonnominal    = args.original_central
tau_id_wp         = args.tau_id_wp
use_home          = args.use_home
hlt_filter        = args.hlt_filter
systematics_label = args.systematics

# Custom arguments
channels = args.channels
output   = args.output
clean    = args.clean
with_mem = args.with_mem

for systematic_label in systematics_label:
  if systematics_label != 'full':
    if not hasattr(systematics, systematic_label):
      raise ValueError('Invalid option for systematic uncertainty: %s' % systematic_label)

if __name__ == '__main__':
  logging.basicConfig(
    stream = sys.stdout,
    level  = logging.INFO,
    format = '%(asctime)s - %(levelname)s: %(message)s',
  )

  analysis = syncNtupleConfig(
    config_dir = os.path.join("/home",       getpass.getuser(), "ttHAnalysis", args.era, args.version),
    output_dir = os.path.join("/hdfs/local", getpass.getuser(), "ttHAnalysis", args.era, args.version),
    output_filename    = output,
    version            = version,
    era                = era,
    channels           = channels,
    dry_run            = dry_run,
    check_output_files = check_output_files,
    running_method     = running_method,
    isDebug            = debug,
    rle_select         = rle_select,
    with_mem           = with_mem,
    use_nonnominal     = use_nonnominal,
    hlt_filter         = hlt_filter,
    tau_id_wp          = tau_id_wp,
    use_home           = use_home,
    systematics_label  = systematics_label,
  )

  job_statistics = analysis.create()

  if auto_exec:
    run_analysis = True
  elif no_exec:
    run_analysis = False
  else:
    run_analysis = query_yes_no("Start jobs ?")
  if run_analysis:
    analysis.run(clean)
  else:
    sys.exit(0)
