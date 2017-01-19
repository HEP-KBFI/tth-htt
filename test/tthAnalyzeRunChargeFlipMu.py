import os, logging, sys, getpass

from tthAnalysis.HiggsToTauTau.analyzeConfig_charge_flip_mu import analyzeConfig_charge_flip_mu
from tthAnalysis.HiggsToTauTau.jobTools import query_yes_no
#from tthAnalysis.HiggsToTauTau.tthAnalyzeSamples_chargeflip_2015 import samples_2015
from tthAnalysis.HiggsToTauTau.tthAnalyzeSamples_chargeflip_mu_2016 import samples_2016

#ERA = "2015"
ERA = "2016"

samples = None
LUMI = None
if ERA == "2015":
  samples = samples_2015
  LUMI = 2260. # 1/pb
elif ERA == "2016":
  samples = samples_2016
  LUMI = 12.9e+3 # 1/pb
else:
  raise ValueError("Invalid Configuration parameter 'ERA' = %s !!" % ERA)

version = "histosCF_mu_1bin"

if __name__ == '__main__':
  logging.basicConfig(
      stream = sys.stdout,
      level = logging.INFO,
      format = '%(asctime)s - %(levelname)s: %(message)s')
  
  analysis = analyzeConfig_charge_flip_mu(
    outputDir = os.path.join("/home", getpass.getuser(), "tth", "histograms", version),
    executable_analyze = "analyze_charge_flip_mu",
    samples = samples_2016,
    lepton_selections = [ "Tight"],
    #hadTau_selection = "dR03mvaTight",
    central_or_shifts = [ 
      "central",
       "CMS_ttHl_muonERUp",
       "CMS_ttHl_muonERDown",
       "CMS_ttHl_muonESBarrel1Up",
       "CMS_ttHl_muonESBarrel1Down",
       "CMS_ttHl_muonESBarrel2Up",
       "CMS_ttHl_muonESBarrel2Down"
       "CMS_ttHl_muonESEndcap1Down",
       "CMS_ttHl_muonESEndcap1Up",
       "CMS_ttHl_muonESEndcap2Down",
       "CMS_ttHl_muonESEndcap2Up"
    ],
    max_files_per_job = 40,
    era = ERA, use_lumi = True, lumi = LUMI,
    debug = False,
    running_method = "sbatch",
    num_parallel_jobs = 4,
    #sel_events_file = '',#os.path.join(os.environ["CMSSW_BASE"] , "src/tthAnalysis/HiggsToTauTau/data/eventlist_diff.txt"),
    histograms_to_fit = [ "mass_ll" ],
    select_rle_output = False
    )

  analysis.create()

  run_analysis = query_yes_no("Start jobs ?")
  if run_analysis:
    analysis.run()
  else:
    sys.exit(0)

