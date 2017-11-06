#!/usr/bin/env python
import os, logging, sys, getpass

from tthAnalysis.HiggsToTauTau.addMEMConfig_2lss_1tau import addMEMConfig_2lss_1tau
from tthAnalysis.HiggsToTauTau.jobTools import query_yes_no

version          = "2017Nov05"
ERA              = "2016"
isForBDTtraining = False
central_or_shift = [
  "central",
  # "CMS_ttHl_JESUp",
  # "CMS_ttHl_JESDown",
  # "CMS_ttHl_tauESUp",
  # "CMS_ttHl_tauESDown",
  # "CMS_ttHl_JERUp",
  # "CMS_ttHl_JERDown",
  # "CMS_ttHl_UnclusteredEnUp",
  # "CMS_ttHl_UnclusteredEnDown",
]

#--------------------------------------------------------------------------------
# CV: run Ntuple production jobs also for high statistics background samples
#     not used in the analysis, but used for BDT training by Arun
if isForBDTtraining:
  from tthAnalysis.HiggsToTauTau.tthAnalyzeSamples_prodNtuples_2016_FastSim import samples_2016 as samples
  leptonSelection = "Loose"
  hadTauSelection = "Tight|dR03mvaLoose"
else:
  from tthAnalysis.HiggsToTauTau.tthAnalyzeSamples_prodNtuples_2016 import samples_2016 as samples
  leptonSelection = "Fakeable"
  hadTauSelection = "Tight|dR03mvaMedium"

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
    isForBDTtraining         = False, # if False, use full integration points
    isDebug                  = True,
    central_or_shift         = central_or_shift,
  )

  goodToGo = addMEMProduction.create()

  if goodToGo:
    run_addMEMProduction = query_yes_no("Start jobs ?")
    if run_addMEMProduction:
      addMEMProduction.run()
