#!/usr/bin/env python
import os, logging, sys, getpass

from tthAnalysis.HiggsToTauTau.tthAnalyzeSamples_2016 import samples_2016
from tthAnalysis.HiggsToTauTau.prodNtupleConfig import prodNtupleConfig
from tthAnalysis.HiggsToTauTau.jobTools import query_yes_no

for sample_key, sample_entry in samples_2016.items():
  if sample_entry['process_name_specific'] != 'ttHJetToNonbb_M125_amcatnlo':
    sample_entry['use_it'] = False
  else:
    sample_entry['use_it'] = True

#ERA = "2015"
ERA = "2016"

samples = None
LUMI    = None
if ERA == "2016":
  samples = samples_2016
  LUMI    = 35.9e+3 # 1/pb
else:
  raise ValueError("Invalid Configuration parameter 'ERA' = %s !!" % ERA)

preselection      = True
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

version = "2017Sep13_wPreselection"

if __name__ == '__main__':
  logging.basicConfig(
    stream = sys.stdout,
    level = logging.INFO,
    format = '%(asctime)s - %(levelname)s: %(message)s')

  ntupleProduction = prodNtupleConfig(
    configDir = os.path.join("/home",       getpass.getuser(), "ttHNtupleProduction", ERA, version),
    outputDir = os.path.join("/hdfs/local", getpass.getuser(), "ttHNtupleProduction", ERA, version),
    executable_prodNtuple = "produceNtuple",
    cfgFile_prodNtuple    = "produceNtuple_cfg.py",
    samples               = samples,
    max_files_per_job     = 40,
    era                   = ERA,
    preselection_cuts     = preselection_cuts,
    debug                 = False,
    running_method        = "sbatch",
    version               = version,
    num_parallel_jobs     = 8
  )

  ntupleProduction.create()

  run_ntupleProduction = query_yes_no("Start jobs ?")
  if run_ntupleProduction:
    ntupleProduction.run()
  else:
    sys.exit(0)

