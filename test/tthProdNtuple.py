#!/usr/bin/env python
import os, logging, sys, getpass

from tthAnalysis.HiggsToTauTau.configs.prodNtupleConfig import prodNtupleConfig
from tthAnalysis.HiggsToTauTau.jobTools import query_yes_no
from tthAnalysis.HiggsToTauTau.runConfig import tthAnalyzeParser, filter_samples

# E.g.: ./tthProdNtuple.py -v 2017Dec13 -m all -e 2017 -p

mode_choices = [ 'all', 'all_except_forBDTtraining', 'forBDTtraining', 'sync', 'leptonFR_sync' ]

parser = tthAnalyzeParser()
parser.add_modes(mode_choices)
parser.add_nonnominal()
parser.add_tau_id_wp('dR03mvaVVLoose')
parser.add_files_per_job(20)
parser.add_use_home(False)
parser.add_argument('-p', '--enable-preselection',
  dest = 'enable_preselection', action = 'store_true', default = False,
  help = 'R|Enable preselection (read this script for the list of cuts)',
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
mode           = args.mode
use_nonnominal = args.original_central
files_per_job  = args.files_per_job
use_home       = args.use_home

# Custom arguments
preselection = args.enable_preselection
pileup       = os.path.join(
  os.environ['CMSSW_BASE'], 'src/tthAnalysis/HiggsToTauTau/data/pileup_%s.root' % era
)
golden_json_2017  = os.path.join(
  os.environ['CMSSW_BASE'], 'src/tthAnalysis/NanoAOD/data',
  'Cert_294927-306462_13TeV_EOY2017ReReco_Collisions17_JSON_v1.txt'
)

# Use the arguments
version              = "%s_w%sPresel_%s_%s" % (
  version, ("" if preselection else "o"), "nonNom" if use_nonnominal else "nom", mode
)

if mode == 'sync':
  from tthAnalysis.HiggsToTauTau.samples.tthAnalyzeSamples_2017_nanoAOD_sync import samples_2017
elif mode == 'leptonFR_sync':
  from tthAnalysis.HiggsToTauTau.samples.tthAnalyzeSamples_2017_nanoAOD_leptonFR_sync import samples_2017
else:
  from tthAnalysis.HiggsToTauTau.samples.tthAnalyzeSamples_2017_nanoAOD import samples_2017

if era == "2017":
  samples = samples_2017
  golden_json = golden_json_2017
else:
  raise ValueError("Invalid era: %s" % era)

for sample_key, sample_entry in samples.items():
  if mode == "all":
    sample_entry['use_it'] = True
  elif mode == 'forBDTtraining':
    sample_entry['use_it'] = not sample_entry['use_it']
  elif 'sync' in mode or mode == 'all_except_forBDTtraining':
    pass
  else:
    raise ValueError("Internal logic error")

leptonSelection      = 'Loose'
hadTauSelection      = 'Loose'
hadTauSelectionAndWP = '%s|%s' % (hadTauSelection, args.tau_id_wp)

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
    level  = logging.INFO,
    format = '%(asctime)s - %(levelname)s: %(message)s'
  )

  logging.info("Preselection: %s" % ("enabled" if preselection else "disabled"))

  if sample_filter:
    samples = filter_samples(samples, sample_filter)

  run_ntupleProduction = False

  for resubmission_idx in range(resubmission_limit):
    logging.info("Submission attempt #%i" % (resubmission_idx + 1))
    ntupleProduction = prodNtupleConfig(
      configDir = os.path.join("/home",       getpass.getuser(), "ttHNtupleProduction", era, version),
      outputDir = os.path.join("/hdfs/local", getpass.getuser(), "ttHNtupleProduction", era, version),
      executable_nanoAOD    = "produceNtuple.sh",
      executable_prodNtuple = "produceNtuple",
      cfgFile_prodNtuple    = "produceNtuple_cfg.py",
      samples               = samples,
      max_files_per_job     = files_per_job,
      era                   = era,
      preselection_cuts     = preselection_cuts,
      leptonSelection       = leptonSelection,
      hadTauSelection       = hadTauSelectionAndWP,
      check_input_files     = check_input_files,
      running_method        = running_method,
      version               = version,
      num_parallel_jobs     = num_parallel_jobs,
      pileup                = pileup,
      golden_json           = golden_json,
      verbose               = resubmission_idx > 0,
      dry_run               = dry_run,
      isDebug               = debug,
      use_nonnominal        = use_nonnominal,
      use_home              = use_home,
    )

    num_jobs = ntupleProduction.create()

    if num_jobs > 0:
      if resubmission_idx == 0:
        if auto_exec:
          run_ntupleProduction = True
        elif no_exec:
          run_ntupleProduction = False
        else:
          run_ntupleProduction = query_yes_no("Start jobs ?")
      if run_ntupleProduction:
        ntupleProduction.run()
      else:
        sys.exit(0)
    else:
      logging.info("All jobs done")
      break
