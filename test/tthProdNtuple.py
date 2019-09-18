#!/usr/bin/env python

from tthAnalysis.HiggsToTauTau.configs.prodNtupleConfig import prodNtupleConfig
from tthAnalysis.HiggsToTauTau.jobTools import query_yes_no
from tthAnalysis.HiggsToTauTau.runConfig import tthAnalyzeParser, filter_samples
from tthAnalysis.HiggsToTauTau.common import logging, load_samples

import os
import sys
import getpass

# E.g.: ./test/tthProdNtuple.py -v 2017Dec13 -m all -e 2017 -p

mode_choices = [
  'all', 'all_except_forBDTtraining', 'forBDTtraining', 'sync', 'leptonFR_sync', 'hh', 'hh_bbww', 'hh_bkg', 'hh_wjets',
  'hh_bbww_sync',
]

parser = tthAnalyzeParser()
parser.add_modes(mode_choices)
parser.add_nonnominal()
parser.add_tau_id_wp('dR03mvaVVLoose&dR05mvaVVLoose&deepVSjVVVLoose')
parser.add_files_per_job(5)
parser.add_use_home(False)
parser.add_gen_matching()
parser.add_argument('-p', '--enable-preselection',
  dest = 'enable_preselection', action = 'store_true', default = False,
  help = 'R|Enable preselection (read this script for the list of cuts)',
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
gen_matching       = args.gen_matching

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
golden_json_2016 = os.path.join(
  os.environ['CMSSW_BASE'], 'src/tthAnalysis/NanoAOD/data',
  'Cert_271036-284044_13TeV_23Sep2016ReReco_Collisions16_JSON.txt'
)
golden_json_2017 = os.path.join(
  os.environ['CMSSW_BASE'], 'src/tthAnalysis/NanoAOD/data',
  'Cert_294927-306462_13TeV_EOY2017ReReco_Collisions17_JSON_v1.txt'
)
golden_json_2018 = os.path.join(
  os.environ['CMSSW_BASE'], 'src/tthAnalysis/NanoAOD/data',
  'Cert_314472-325175_13TeV_17SeptEarlyReReco2018ABC_PromptEraD_Collisions18_JSON.txt'
)

# Use the arguments
version = "%s_w%sPresel_%s_%s" % (
  version, ("" if preselection else "o"), "nonNom" if use_nonnominal else "nom", mode
)
gen_matching_by_index = (gen_matching == 'by_index')

if mode == 'sync':
  samples = load_samples(era, preselection, suffix = 'sync')
  pileup = os.path.join(
    os.environ['CMSSW_BASE'], 'src/tthAnalysis/HiggsToTauTau/data/pileup_%s_sync.root' % era
  )
elif mode == 'leptonFR_sync':
  if preselection:
    raise ValueError("Does not make sense to apply preselection to Ntuples used in lepton FR sync")

  samples = load_samples(era, False, suffix = 'leptonFR_sync')
elif mode == 'hh_bbww_sync':
  if preselection:
    raise ValueError("Preselection not possible in mode: %s" % mode)

  samples = load_samples(era, False, base = 'hh_bbww', suffix = 'sync')
  pileup = os.path.join(
    os.environ['CMSSW_BASE'], 'src/hhAnalysis/bbww/data/pileup_hh_{}.root'.format(era)
  )
elif mode == 'hh':
  if preselection:
    raise ValueError("Preselection not possible for %s mode" % mode)

  samples = load_samples(era, False, base = 'hh_multilepton')
  pileup = os.path.join(
    os.environ['CMSSW_BASE'], 'src/hhAnalysis/multilepton/data/pileup_hh_{}.root'.format(era)
  )
elif mode == 'hh_bbww':
  if preselection:
    raise ValueError("Preselection not possible for %s mode" % mode)

  samples = load_samples(era, False, base = 'hh_bbww')
  pileup = os.path.join(
    os.environ['CMSSW_BASE'], 'src/hhAnalysis/bbww/data/pileup_hh_{}.root'.format(era)
  )
elif mode == 'hh_wjets':
  if preselection:
    raise ValueError("Preselection not possible for %s mode" % mode)

  samples = load_samples(era, False, base = 'hh_multilepton', suffix = 'wjets')
  pileup = os.path.join(
    os.environ['CMSSW_BASE'], 'src/hhAnalysis/multilepton/data/pileup_wjets_{}.root'.format(era)
  )
else:
  samples = load_samples(era, preselection, suffix = 'base' if preselection else '')

if era == "2016":
  golden_json = golden_json_2016
elif era == "2017":
  golden_json = golden_json_2017
elif era == "2018":
  golden_json = golden_json_2018
else:
  raise ValueError("Invalid era: %s" % era)

if 'sum_events' in samples:
  del samples['sum_events']
for sample_name, sample_entry in samples.items():
  if mode == 'all' or mode == 'hh_bkg' or mode == 'hh_wjets':
    sample_entry['use_it'] = True
  elif mode == 'forBDTtraining':
    sample_entry['use_it'] = not sample_entry['use_it']
  elif mode.startswith('hh'):
    sample_entry['use_it'] = sample_entry['process_name_specific'].startswith('signal') and \
                             'hh' in sample_entry['process_name_specific']
  elif 'sync' in mode or mode == 'all_except_forBDTtraining':
    pass
  else:
    raise ValueError("Invalid mode: %s" % mode)

if preselection:
  preselection_cuts = {
    'minNumLeptons'              : -1,
    'minNumHadTaus'              : -1,
    'minNumLeptons_and_HadTaus'  :  2,
    'minNumJets'                 : -1,
    'minNumBJets_loose'          : -1,
    'minNumBJets_medium'         : -1,
    'maxNumBJets_loose'          : -1,
    'maxNumBJets_medium'         : -1,
    'applyJetEtaCut'             : False,
    'applyHLTcut'                : True,
  }
  leptonSelection = 'Fakeable'
  hadTauWP = 'dR03mvaVLoose&deepVSjVLoose' # override user preference
else:
  preselection_cuts = {
    'minNumLeptons'             : -1,
    'minNumHadTaus'             : -1,
    'minNumLeptons_and_HadTaus' : -1,
    'minNumJets'                : -1,
    'minNumBJets_loose'         : -1,
    'minNumBJets_medium'        : -1,
    'maxNumBJets_loose'         : -1,
    'maxNumBJets_medium'        : -1,
    'applyJetEtaCut'            : False,
    'applyHLTcut'               : False,
  }
  leptonSelection = 'Loose'
  hadTauWP = args.tau_id_wp

if __name__ == '__main__':
  logging.info("Preselection: %s" % ("enabled" if preselection else "disabled"))

  if sample_filter:
    samples = filter_samples(samples, sample_filter)

  ntupleProduction = prodNtupleConfig(
    configDir = os.path.join("/home",       getpass.getuser(), "ttHNtupleProduction", era, version),
    outputDir = os.path.join("/hdfs/local", getpass.getuser(), "ttHNtupleProduction", era, version),
    cfgFile_prodNtuple    = "produceNtuple_cfg.py",
    samples               = samples,
    max_files_per_job     = files_per_job,
    era                   = era,
    preselection_cuts     = preselection_cuts,
    leptonSelection       = leptonSelection,
    hadTauWP              = hadTauWP,
    check_output_files    = check_output_files,
    running_method        = running_method,
    version               = version,
    num_parallel_jobs     = num_parallel_jobs,
    pileup                = pileup,
    golden_json           = golden_json,
    dry_run               = dry_run,
    isDebug               = debug,
    gen_matching_by_index = gen_matching_by_index,
    use_nonnominal        = use_nonnominal,
    use_home              = use_home,
    skip_tools_step       = preselection,
  )

  num_jobs = ntupleProduction.create()

  if num_jobs > 0:
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
