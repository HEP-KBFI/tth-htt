import os, logging, sys, getpass

from tthAnalysis.HiggsToTauTau.tthAnalyzeSamples_3l_1tau_2015 import samples_2015
from tthAnalysis.HiggsToTauTau.tthAnalyzeSamples_3l_1tau_2016 import samples_2016
from tthAnalysis.HiggsToTauTau.prodNtupleConfig_3l_1tau import prodNtupleConfig_3l_1tau
from tthAnalysis.HiggsToTauTau.jobTools import query_yes_no

#ERA = "2015"
ERA = "2016"

samples = None
LUMI = None
if ERA == "2015":
  samples = samples_2015
  LUMI =  2.3e+3 # 1/pb
elif ERA == "2016":
  samples = samples_2016
  LUMI = 12.9e+3 # 1/pb
else:
  raise ValueError("Invalid Configuration parameter 'ERA' = %s !!" % ERA)

version = "2016Dec16"

#--------------------------------------------------------------------------------   
# CV: run Ntuple production jobs also for high statistics background samples
#     not used in the analysis, but used for BDT training by Arun
for sample_name, sample_info in samples_2016.items():
  if sample_name in [
      "/TT_TuneCUETP8M1_13TeV-powheg-pythia8/RunIISpring16MiniAODv1-PUSpring16_80X_mcRun2_asymptotic_2016_v3_ext3-v1/MINIAODSIM",
      "/TT_TuneCUETP8M1_13TeV-powheg-pythia8/RunIISpring16MiniAODv1-PUSpring16_80X_mcRun2_asymptotic_2016_v3_ext4-v1/MINIAODSIM",
      "/TTW/spring16DR80v6aMiniAODv1/FASTSIM" ]:
    sample_info["use_it"] = True
#--------------------------------------------------------------------------------    

if __name__ == '__main__':
  logging.basicConfig(
    stream = sys.stdout,
    level = logging.INFO,
    format = '%(asctime)s - %(levelname)s: %(message)s')

  ntupleProduction = prodNtupleConfig_3l_1tau(
    outputDir = os.path.join("/home", getpass.getuser(), "ttHNtupleProduction", ERA, version),
    executable_prodNtuple = "produceNtuple_3l_1tau",
    samples = samples,
    era = ERA,
    debug = False,
    running_method = "sbatch",
    num_parallel_jobs = 4)

  ntupleProduction.create()

  run_ntupleProduction = query_yes_no("Start jobs ?")
  if run_ntupleProduction:
    ntupleProduction.run()
  else:
    sys.exit(0)

