import os, logging, sys, getpass

#from tthAnalysis.HiggsToTauTau.tthAnalyzeSamples_chargeflip_2015 import samples_2015
from tthAnalysis.HiggsToTauTau.tthAnalyzeSamples_chargeflip_2016 import samples_2016
from tthAnalysis.HiggsToTauTau.configs.analyzeConfig_charge_flip import analyzeConfig_charge_flip
from tthAnalysis.HiggsToTauTau.jobTools import query_yes_no

#ERA = "2015"
ERA = "2016"

samples = None
LUMI = None
if ERA == "2015":
  samples = samples_2015
  LUMI = 2260. # 1/pb
elif ERA == "2016":
  samples = samples_2016
  LUMI = 35.9e+3 # 1/pb
else:
  raise ValueError("Invalid Configuration parameter 'ERA' = %s !!" % ERA)

version = "histosCF_summer_June6_test"

if __name__ == '__main__':
  logging.basicConfig(
      stream = sys.stdout,
      level = logging.INFO,
      format = '%(asctime)s - %(levelname)s: %(message)s')

  analysis = analyzeConfig_charge_flip(
    configDir = os.path.join("/home", getpass.getuser(), "ttHAnalysis", ERA, version),
    outputDir = os.path.join("/hdfs/local/ttH_2tau", getpass.getuser(), "ttHAnalysis", ERA, version),
    #outputDir = os.path.join("/home", getpass.getuser(), "ttHAnalysis", ERA, version),
    executable_analyze = "analyze_charge_flip",
    samples = samples,
    lepton_selections = [ "Tight"],
    #hadTau_selection = "dR03mvaTight",
    central_or_shifts = [
      "central",
       #"CMS_ttHl_btag_HFUp",
       #"CMS_ttHl_btag_HFDown",
       #"CMS_ttHl_btag_HFStats1Up",
       #"CMS_ttHl_btag_HFStats1Down",
       #"CMS_ttHl_btag_HFStats2Up",
       #"CMS_ttHl_btag_HFStats2Down",
       #"CMS_ttHl_btag_LFUp",
       #"CMS_ttHl_btag_LFDown",
       #"CMS_ttHl_btag_LFStats1Up",
       #"CMS_ttHl_btag_LFStats1Down",
       #"CMS_ttHl_btag_LFStats2Up",
       #"CMS_ttHl_btag_LFStats2Down",
       #"CMS_ttHl_btag_cErr1Up",
       #"CMS_ttHl_btag_cErr1Down",
       #"CMS_ttHl_btag_cErr2Up",
       #"CMS_ttHl_btag_cErr2Down",
       #"CMS_ttHl_JESUp",
       #"CMS_ttHl_JESDown",
       #"CMS_ttHl_tauESUp",
       #"CMS_ttHl_tauESDown",
       #"CMS_ttHl_electronESUp",
       #"CMS_ttHl_electronESDown",
       #"CMS_ttHl_electronERUp", ###
       #"CMS_ttHl_electronERDown",
       #"CMS_ttHl_electronESEndcapUp",
       #"CMS_ttHl_electronESEndcapDown",
       #"CMS_ttHl_electronESBarrelUp",
       #"CMS_ttHl_electronESBarrelDown"
    ],
    max_files_per_job = 100,
    era = ERA, use_lumi = True, lumi = LUMI,
    debug = False,
    running_method = "sbatch",
    num_parallel_jobs = 4,
    #sel_events_file = '',#os.path.join(os.environ["CMSSW_BASE"] , "src/tthAnalysis/HiggsToTauTau/data/eventlist_diff.txt"),
    histograms_to_fit = [ "mass_ll" ],
    select_rle_output = False
    )

  analysis.create()

  '''
  run_analysis = query_yes_no("Start jobs ?")
  if run_analysis:
    analysis.run()
  else:
    sys.exit(0)  
  '''

  #'''
  logging.info("Run jobs now..")
  analysis.run()
  logging.info("Running jobs are done. \n\nBye...\n")
  #'''
  #logging.info("Jobs will not run.. Terminating..")


