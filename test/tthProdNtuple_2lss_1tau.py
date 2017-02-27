import os, logging, sys, getpass

from tthAnalysis.HiggsToTauTau.tthAnalyzeSamples_2lss_1tau_2015 import samples_2015
from tthAnalysis.HiggsToTauTau.tthAnalyzeSamples_2lss_1tau_2016 import samples_2016
from tthAnalysis.HiggsToTauTau.prodNtupleConfig_2lss_1tau import prodNtupleConfig_2lss_1tau
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
  LUMI = 35.9e+3 # 1/pb
else:
  raise ValueError("Invalid Configuration parameter 'ERA' = %s !!" % ERA)

version = "2017Feb22" # must be the same version as in test/tthAnalyzeRun_2lss_1tau.py !

#--------------------------------------------------------------------------------
# NOTE: you need to run
#         'python scripts/cat_rle.py -e 2016 -c 2lss_1tau -v VERSION -u veelken -V'
#       prior to executing 'python tthProdNtuple_2lss_1tau.py' !!
#      (otherwise you will get error messages of the kind "Found 0 RLE numbers")
#--------------------------------------------------------------------------------

if __name__ == '__main__':
  logging.basicConfig(
    stream = sys.stdout,
    level = logging.INFO,
    format = '%(asctime)s - %(levelname)s: %(message)s')

  ntupleProduction = prodNtupleConfig_2lss_1tau(
    configDir = os.path.join("/home", getpass.getuser(), "ttHNtupleProduction", ERA, version),
    outputDir = os.path.join("/hdfs/local/ttH_2tau", getpass.getuser(), "ttHNtupleProduction", ERA, version),
    ##outputDir = os.path.join("/home", getpass.getuser(), "ttHNtupleProduction", ERA, version),
    executable_prodNtuple = "produceNtuple_2lss_1tau",
    cfgFile_prodNtuple = "produceNtuple_2lss_1tau_cfg.py",
    samples = samples,
    era = ERA,
    debug = False,
    running_method = "sbatch",
    rle_directory = 'default', # [*]
    version = version,
    num_parallel_jobs = 4)
  # [*] if rle_directory is set to 'default', then it looks files in /home/$USER/ttHAnalysis/era/version/rles/channel
  #     set it to '', if no RLE selection is needed

  ntupleProduction.create()

  ##run_ntupleProduction = query_yes_no("Start jobs ?")
  run_ntupleProduction = True
  if run_ntupleProduction:
    ntupleProduction.run()
  else:
    sys.exit(0)

