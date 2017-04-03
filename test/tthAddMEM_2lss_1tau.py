#!/usr/bin/env python
import os, logging, sys, getpass

from tthAnalysis.HiggsToTauTau.addMEMConfig_2lss_1tau import addMEMConfig_2lss_1tau
from tthAnalysis.HiggsToTauTau.jobTools import query_yes_no

isForBDTtraining = False

from tthAnalysis.HiggsToTauTau.tthAnalyzeSamples_2016_2lss1tau_prodNtuples_v3 import samples_2016 as samples

#--------------------------------------------------------------------------------
# CV: run Ntuple production jobs also for high statistics background samples
#     not used in the analysis, but used for BDT training by Arun
if isForBDTtraining:
  for sample_name, sample_info in samples.items():
    if sample_info['process_name_specific'] in [
      'TTTo2L2Nu_fastsim_p1',
      'TTTo2L2Nu_fastsim_p2',
      'TTTo2L2Nu_fastsim_p3',
      'TTToSemilepton_fastsim_p1',
      'TTToSemilepton_fastsim_p2',
      'TTToSemilepton_fastsim_p3',
      'TTWJetsToLNu_fastsim',
      'TTZToLLNuNu_fastsim',
      'WZTo3LNu_fastsim',
      'ttHToNonbb_fastsim_p1',
      'ttHToNonbb_fastsim_p2',
      'ttHToNonbb_fastsim_p3',
    ]:
      sample_info["use_it"] = True
    else:
      sample_info["use_it"] = False
  leptonSelection = "Loose"
  hadTauSelection = "Tight|dR03mvaLoose"
else:
  leptonSelection = "Fakeable"
  hadTauSelection = "Tight|dR03mvaMedium"

#--------------------------------------------------------------------------------

version = "2017Mar24"
ERA     = "2016"

if __name__ == '__main__':
  logging.basicConfig(
    stream = sys.stdout,
    level  = logging.DEBUG,
    format = '%(asctime)s - %(levelname)s: %(message)s')

  addMEMProduction = addMEMConfig_2lss_1tau(
    treeName                 = 'tree',
    outputDir                = os.path.join("/hdfs/local", getpass.getuser(), "addMEM", ERA, version),
    cfgDir                   = os.path.join("/home",       getpass.getuser(), "addMEM", ERA, version),
    executable_addMEM        = "addMEM_2lss_1tau",
    samples                  = samples,
    era                      = ERA,
    debug                    = False,
    running_method           = "sbatch",
    max_files_per_job        = 1, # so that we'd have 1-1 correspondence b/w input and output files
    mem_integrations_per_job = 50,
    max_mem_integrations     = 20000, # use -1 if you don't want to limit the nof MEM integrations
    num_parallel_jobs        = 16,
    leptonSelection          = leptonSelection,
    hadTauSelection          = hadTauSelection,
    isForBDTtraining         = False, # still use full integration points
  )

  goodToGo = addMEMProduction.create()

  if goodToGo:
    run_addMEMProduction = query_yes_no("Start jobs ?")
    if run_addMEMProduction:
      addMEMProduction.run()
