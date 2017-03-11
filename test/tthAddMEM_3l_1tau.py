import os, logging, sys, getpass

from tthAnalysis.HiggsToTauTau.addMEMConfig_3l_1tau import addMEMConfig_3l_1tau
from tthAnalysis.HiggsToTauTau.jobTools import query_yes_no

isForBDTtraining = False

#--------------------------------------------------------------------------------
# CV: run Ntuple production jobs also for high statistics background samples
#     not used in the analysis, but used for BDT training by Arun
#TODO: update the disabled sample list for 2016 dataset
if isForBDTtraining:
  from tthAnalysis.HiggsToTauTau.tthAnalyzeSamples_2016_3l1tau_prodNtuples_forBDTtraining import samples_2016 as samples

  for sample_name, sample_info in samples.items():
    if sample_name in [
        "/TT_TuneCUETP8M1_13TeV-powheg-pythia8/RunIISpring16MiniAODv1-PUSpring16_80X_mcRun2_asymptotic_2016_v3_ext3-v1/MINIAODSIM",
        "/TT_TuneCUETP8M1_13TeV-powheg-pythia8/RunIISpring16MiniAODv1-PUSpring16_80X_mcRun2_asymptotic_2016_v3_ext4-v1/MINIAODSIM",
        "/TTW/spring16DR80v6aMiniAODv1/FASTSIM"
    ]:
      sample_info["use_it"] = True
else:
  from tthAnalysis.HiggsToTauTau.tthAnalyzeSamples_2016_3l1tau_prodNtuples import samples_2016 as samples
#--------------------------------------------------------------------------------

version = "2017Jan26_dR03mvaVVLoose"
ERA     = "2016"

if __name__ == '__main__':
  logging.basicConfig(
    stream = sys.stdout,
    level  = logging.DEBUG,
    format = '%(asctime)s - %(levelname)s: %(message)s')

  addMEMProduction = addMEMConfig_3l_1tau(
    treeName                 = 'tree',
    outputDir                = os.path.join("/hdfs", getpass.getuser(), "addMEM", ERA, version),
    cfgDir                   = os.path.join("/home", getpass.getuser(), "addMEM", ERA, version),
    executable_addMEM        = "addMEM_3l_1tau",
    samples                  = samples,
    era                      = ERA,
    debug                    = False,
    running_method           = "sbatch",
    max_files_per_job        = 1, # so that we'd have 1-1 correspondence b/w input and output files
    mem_integrations_per_job = 50,
    max_mem_integrations     = 20000, # use -1 if you don't want to limit the nof MEM integrations
    num_parallel_jobs        = 8,
    leptonSelection          = "Loose",
    hadTauSelection          = "Tight|dR03mvaVVLoose",
    isForBDTtraining         = isForBDTtraining,
  )

  goodToGo = addMEMProduction.create()

  if goodToGo:
    run_addMEMProduction = query_yes_no("Start jobs ?")
    if run_addMEMProduction:
      addMEMProduction.run()
