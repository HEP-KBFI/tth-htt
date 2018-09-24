#!/usr/bin/env python
import os, logging, sys, getpass

from tthAnalysis.HiggsToTauTau.configs.prodNtupleConfig import prodNtupleConfig
from tthAnalysis.HiggsToTauTau.jobTools import query_yes_no
from tthAnalysis.HiggsToTauTau.runConfig import tthAnalyzeParser, filter_samples

# E.g.: ./tthProdNtuple.py -v 2017Dec13 -m all -e 2017 -p

mode_choices = [ 'all', 'all_except_forBDTtraining', 'forBDTtraining', 'sync', 'leptonFR_sync', 'hh' ]

parser = tthAnalyzeParser()
parser.add_modes(mode_choices)
parser.add_nonnominal()
parser.add_tau_id_wp('dR03mvaVVLoose')
parser.add_files_per_job(10)
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
no_exec            = args.no_exec
auto_exec          = args.auto_exec
check_output_files = not args.not_check_input_files
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
golden_json_2016 = os.path.join(
  os.environ['CMSSW_BASE'], 'src/tthAnalysis/NanoAOD/data',
  'Cert_271036-284044_13TeV_23Sep2016ReReco_Collisions16_JSON.txt'
)
golden_json_2017 = os.path.join(
  os.environ['CMSSW_BASE'], 'src/tthAnalysis/NanoAOD/data',
  'Cert_294927-306462_13TeV_EOY2017ReReco_Collisions17_JSON_v1.txt'
)

# Use the arguments
version = "%s_w%sPresel_%s_%s" % (
  version, ("" if preselection else "o"), "nonNom" if use_nonnominal else "nom", mode
)

if mode == 'sync':
  if preselection:
    if era == "2016":
      from tthAnalysis.HiggsToTauTau.samples.tthAnalyzeSamples_2016_sync import samples_2016 as samples
    elif era == "2017":
      from tthAnalysis.HiggsToTauTau.samples.tthAnalyzeSamples_2017_sync import samples_2017 as samples
    elif era == "2018":
      from tthAnalysis.HiggsToTauTau.samples.tthAnalyzeSamples_2018_sync import samples_2018 as samples
    else:
      raise ValueError("Invalid era: %s" % era)
  else:
    if era == "2016":
      from tthAnalysis.HiggsToTauTau.samples.tthAnalyzeSamples_2016_nanoAOD_sync import samples_2016 as samples
    elif era == "2017":
      from tthAnalysis.HiggsToTauTau.samples.tthAnalyzeSamples_2017_nanoAOD_sync import samples_2017 as samples
    elif era == "2018":
      from tthAnalysis.HiggsToTauTau.samples.tthAnalyzeSamples_2018_nanoAOD_sync import samples_2018 as samples
    else:
      raise ValueError("Invalid era: %s" % era)
elif mode == 'leptonFR_sync':
  if preselection:
    raise ValueError("Does not make sense to apply preselection to Ntuples used in lepton FR sync")
  else:
    if era == "2016":
      from tthAnalysis.HiggsToTauTau.samples.tthAnalyzeSamples_2016_nanoAOD_leptonFR_sync import samples_2016 as samples
    elif era == "2017":
      from tthAnalysis.HiggsToTauTau.samples.tthAnalyzeSamples_2017_nanoAOD_leptonFR_sync import samples_2017 as samples
    elif era == "2018":
      from tthAnalysis.HiggsToTauTau.samples.tthAnalyzeSamples_2018_nanoAOD_leptonFR_sync import samples_2018 as samples
    else:
      raise ValueError("Invalid era: %s" % era)
elif mode == 'hh':
  if preselection:
    if era == "2016":
      from hhAnalysis.multilepton.samples.hhAnalyzeSamples_2016 import samples_2016 as samples
      pileup = os.path.join(
        os.environ['CMSSW_BASE'], 'src/hhAnalysis/multilepton/data/pileup_hh_2016.root'
      )
    elif era == "2017":
      from hhAnalysis.multilepton.samples.hhAnalyzeSamples_2017 import samples_2017 as samples
      pileup = os.path.join(
        os.environ['CMSSW_BASE'], 'src/hhAnalysis/multilepton/data/pileup_hh_2017.root'
      )
    elif era == "2018":
      from hhAnalysis.multilepton.samples.hhAnalyzeSamples_2018 import samples_2018 as samples
      pileup = os.path.join(
        os.environ['CMSSW_BASE'], 'src/hhAnalysis/multilepton/data/pileup_hh_2018.root'
      )
    else:
      raise ValueError("Invalid era: %s" % era)
  else:
    if era == "2016":
      from hhAnalysis.multilepton.samples.hhAnalyzeSamples_2016_nanoAOD import samples_2016 as samples
      pileup = os.path.join(
        os.environ['CMSSW_BASE'], 'src/hhAnalysis/multilepton/data/pileup_hh_2016.root'
      )
    elif era == "2017":
      from hhAnalysis.multilepton.samples.hhAnalyzeSamples_2017_nanoAOD_hh_merged import samples_2017 as samples
      pileup = os.path.join(
        os.environ['CMSSW_BASE'], 'src/hhAnalysis/multilepton/data/pileup_hh_2017.root'
      )
    elif era == "2018":
      from hhAnalysis.multilepton.samples.hhAnalyzeSamples_2018_nanoAOD import samples_2018 as samples
      pileup = os.path.join(
        os.environ['CMSSW_BASE'], 'src/hhAnalysis/multilepton/data/pileup_hh_2018.root'
      )
    else:
      raise ValueError("Invalid era: %s" % era)
else:
  if preselection:
    if era == "2016":
      from tthAnalysis.HiggsToTauTau.samples.tthAnalyzeSamples_2016 import samples_2016 as samples
    elif era == "2017":
      from tthAnalysis.HiggsToTauTau.samples.tthAnalyzeSamples_2017 import samples_2017 as samples
    elif era == "2018":
      from tthAnalysis.HiggsToTauTau.samples.tthAnalyzeSamples_2018 import samples_2018 as samples
    else:
      raise ValueError("Invalid era: %s" % era)
  else:
    if era == "2016":
      from tthAnalysis.HiggsToTauTau.samples.tthAnalyzeSamples_2016_nanoAOD import samples_2016 as samples
    elif era == "2017":
      from tthAnalysis.HiggsToTauTau.samples.tthAnalyzeSamples_2017_nanoAOD import samples_2017 as samples
    elif era == "2018":
      from tthAnalysis.HiggsToTauTau.samples.tthAnalyzeSamples_2018_nanoAOD import samples_2018 as samples
    else:
      raise ValueError("Invalid era: %s" % era)

if era == "2016":
  golden_json = golden_json_2016
elif era == "2017":
  golden_json = golden_json_2017
elif era == "2018":
  raise ValueError("Implement me!")
else:
  raise ValueError("Invalid era: %s" % era)

if 'sum_events' in samples:
  del samples['sum_events']
for sample_name, sample_entry in samples.items():
  if mode == "all":
    sample_entry['use_it'] = True
  elif mode == 'forBDTtraining':
    sample_entry['use_it'] = not sample_entry['use_it']
  elif mode == 'hh':
    sample_entry['use_it'] = sample_entry['process_name_specific'].startswith('signal') and \
                             'hh' in sample_entry['process_name_specific']
  elif 'sync' in mode or mode == 'all_except_forBDTtraining':
    pass
  else:
    raise ValueError("Invalid mode: %s" % mode)

if preselection:
  if mode == 'hh':
    # valid only for HH->4tau analysis; for HH->4W->2lss/3l channel the cuts do not apply
    preselection_cuts = {
      'minNumLeptons'             : -1,
      'minNumHadTaus'             : -1,
      'minNumLeptons_and_HadTaus' : 4,
      'minNumJets'                : -1,
      'minNumBJets_loose'         : -1,
      'minNumBJets_medium'        : -1,
      'maxNumBJets_loose'         : 1,
      'maxNumBJets_medium'        : 0,
      'applyJetEtaCut'            : True,
    }
  else:
    preselection_cuts = {
      'minNumLeptons'              : 1,
      'minNumHadTaus'              : 1,
      'minNumLeptons_and_HadTaus'  : 3,
      'minNumJets'                 : -1,
      'minNumBJets_loose'          : 2,
      'minNumBJets_medium'         : 1,
      'maxNumBJets_loose'          : -1,
      'maxNumBJets_medium'         : -1,
      'applyJetEtaCut'             : True,
    }
  leptonSelection = 'Fakeable'
  hadTauSelection = 'Fakeable'
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
    'applyJetEtaCut'            : True, # disable the cut for VBF HH->2b2W analysis
  }
  leptonSelection = 'Loose'
  hadTauSelection = 'Loose'

hadTauSelectionAndWP = '%s|%s' % (hadTauSelection, args.tau_id_wp)

if __name__ == '__main__':
  logging.basicConfig(
    stream = sys.stdout,
    level  = logging.INFO,
    format = '%(asctime)s - %(levelname)s: %(message)s'
  )

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
    hadTauSelection       = hadTauSelectionAndWP,
    check_output_files    = check_output_files,
    running_method        = running_method,
    version               = version,
    num_parallel_jobs     = num_parallel_jobs,
    pileup                = pileup,
    golden_json           = golden_json,
    dry_run               = dry_run,
    isDebug               = debug,
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
