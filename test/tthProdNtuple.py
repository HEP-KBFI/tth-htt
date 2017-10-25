#!/usr/bin/env python
import os, logging, sys, getpass

from tthAnalysis.HiggsToTauTau.tthAnalyzeSamples_2016 import samples_2016
from tthAnalysis.HiggsToTauTau.prodNtupleConfig import prodNtupleConfig
from tthAnalysis.HiggsToTauTau.jobTools import query_yes_no

#--------------------------------------------------------------------------------
# NOTE: set mode flag to
#   'all'                   : to produce the Ntuples from all samples
#   'forBDTtraining_only'   : to produce the Ntuples only from the FastSim samples
#   'forBDTtraining_except' : to produce the Ntuples from all but the FastSim samples
#--------------------------------------------------------------------------------

ERA          = "2016"
mode         = "all"
preselection = True
version      = "2017Oct20_w%sPreselection_%s" % ("" if preselection else "o", mode)

samples         = None
LUMI            = None
leptonSelection = None
hadTauSelection = None

for sample_key, sample_entry in samples_2016.items():
  if mode == "all":
    sample_entry['use_it'] = True
  elif mode in ["forBDTtraining_only", "forBDTtraining_except"]:
    if sample_key in [
      "/TTTo2L2Nu_TuneCUETP8M2_ttHtranche3_13TeV-powheg-pythia8/matze-faster_v8_ttjets_dl_maod_p1_3a2fa29ab1d54ae0995b28f27b405be9-v1/USER",
      "/TTTo2L2Nu_TuneCUETP8M2_ttHtranche3_13TeV-powheg-pythia8/matze-faster_v8_ttjets_dl_maod_p2_3a2fa29ab1d54ae0995b28f27b405be9-v1/USER",
      "/TTTo2L2Nu_TuneCUETP8M2_ttHtranche3_13TeV-powheg-pythia8/matze-faster_v8_ttjets_dl_maod_p3_3a2fa29ab1d54ae0995b28f27b405be9-v1/USER",
      "/TTToSemilepton_TuneCUETP8M2_ttHtranche3_13TeV-powheg-pythia8/matze-faster_v8_ttjets_sl_maod_p1_3a2fa29ab1d54ae0995b28f27b405be9-v1/USER",
      "/TTToSemilepton_TuneCUETP8M2_ttHtranche3_13TeV-powheg-pythia8/matze-faster_v8_ttjets_sl_maod_p2_3a2fa29ab1d54ae0995b28f27b405be9-v1/USER",
      "/TTToSemilepton_TuneCUETP8M2_ttHtranche3_13TeV-powheg-pythia8/matze-faster_v8_ttjets_sl_maod_p3_3a2fa29ab1d54ae0995b28f27b405be9-v1/USER",
      "/TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/matze-faster_v9_ttW_maod_54aa74f75231422e9f4d3766cb92a64a-v1/USER",
      "/TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-pythia8/matze-faster_v9_ttZ_maod_54aa74f75231422e9f4d3766cb92a64a-v1/USER",
      "/WZTo3LNu_TuneCUETP8M1_13TeV-powheg-pythia8/matze-faster_v9_WZ_maod_54aa74f75231422e9f4d3766cb92a64a-v1/USER",
      "/ttHToNonbb_M125_TuneCUETP8M2_ttHtranche3_13TeV-powheg-pythia8/matze-faster_v8_ttH_maod_p1_3a2fa29ab1d54ae0995b28f27b405be9-v1/USER",
      "/ttHToNonbb_M125_TuneCUETP8M2_ttHtranche3_13TeV-powheg-pythia8/matze-faster_v8_ttH_maod_p2_3a2fa29ab1d54ae0995b28f27b405be9-v1/USER",
      "/ttHToNonbb_M125_TuneCUETP8M2_ttHtranche3_13TeV-powheg-pythia8/matze-faster_v8_ttH_maod_p3_3a2fa29ab1d54ae0995b28f27b405be9-v1/USER" ]:
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

if ERA == "2016":
  samples = samples_2016
  LUMI    = 35.9e+3 # 1/pb
else:
  raise ValueError("Invalid Configuration parameter 'ERA' = %s !!" % ERA)

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

  ntupleProduction = prodNtupleConfig(
    configDir = os.path.join("/home",       getpass.getuser(), "ttHNtupleProduction", ERA, version),
    outputDir = os.path.join("/hdfs/local", getpass.getuser(), "ttHNtupleProduction", ERA, version),
    executable_prodNtuple = "produceNtuple",
    cfgFile_prodNtuple    = "produceNtuple_cfg.py",
    samples               = samples,
    max_files_per_job     = max_files_per_job,
    era                   = ERA,
    preselection_cuts     = preselection_cuts,
    leptonSelection       = leptonSelection,
    hadTauSelection       = hadTauSelection,
    debug                 = False,
    running_method        = "sbatch",
    version               = version,
    num_parallel_jobs     = 8,
  )

  ntupleProduction.create()

  run_ntupleProduction = query_yes_no("Start jobs ?")
  if run_ntupleProduction:
    ntupleProduction.run()
  else:
    sys.exit(0)
