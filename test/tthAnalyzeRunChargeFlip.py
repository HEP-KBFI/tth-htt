import os, logging, sys, getpass

import tthAnalysis.HiggsToTauTau.tthAnalyzeSamples_chargeflip
from tthAnalysis.HiggsToTauTau.analyzeConfig_charge_flip import analyzeConfig_charge_flip
from tthAnalysis.HiggsToTauTau.jobTools import query_yes_no


#LUMI = 2301. # 1/pb
LUMI = 2260. #?
version = "histosCF_pseudodata_eleESER2"


if __name__ == '__main__':
  logging.basicConfig(
      stream = sys.stdout,
      level = logging.INFO,
      format = '%(asctime)s - %(levelname)s: %(message)s')

  analysis = analyzeConfig_charge_flip(
    outputDir = os.path.join("/home", getpass.getuser(), "tth", version),
    executable_analyze = "analyze_charge_flip",
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
       "CMS_ttHl_electronERUp",
       "CMS_ttHl_electronERDown",
       "CMS_ttHl_electronESEndcapUp",
       "CMS_ttHl_electronESEndcapDown",
       "CMS_ttHl_electronESBarrelUp",
       "CMS_ttHl_electronESBarrelDown"
    ],
    max_files_per_job = 40,
    use_lumi = True, lumi = LUMI,
    use_data = False,
    debug = False,
    running_method = "sbatch",
    num_parallel_jobs = 4,
    #sel_events_file = '',#os.path.join(os.environ["CMSSW_BASE"] , "src/tthAnalysis/HiggsToTauTau/data/eventlist_diff.txt"),
    histograms_to_fit = [ "mass_ll" ]
    )

  analysis.create()

  run_analysis = query_yes_no("Start jobs ?")
  if run_analysis:
    analysis.run()
  else:
    sys.exit(0)

