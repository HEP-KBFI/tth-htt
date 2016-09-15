import os, logging, sys, getpass

from tthAnalysis.HiggsToTauTau.tthAnalyzeSamples_2los_1tau_2015 import samples_2015
#from tthAnalysis.HiggsToTauTau.tthAnalyzeSamples_2los_1tau_2016 import samples_2016
from tthAnalysis.HiggsToTauTau.analyzeConfig_2los_1tau import analyzeConfig_2los_1tau
from tthAnalysis.HiggsToTauTau.jobTools import query_yes_no

ERA = "2015"
#ERA = "2016"

samples = None
LUMI = None
if ERA == "2015":
  samples = samples_2015
  LUMI = 2301. # 1/pb
elif ERA == "2016":
  samples = samples_2016
  LUMI = "XXXXX" # 1/pb
else:
  raise ValueError("Invalid Configuration parameter 'ERA' = %s !!" % ERA)

version = "2016Sep14_dR03mvaTight"

if __name__ == '__main__':
  logging.basicConfig(
    stream = sys.stdout,
    level = logging.INFO,
    format = '%(asctime)s - %(levelname)s: %(message)s')

  analysis = analyzeConfig_2los_1tau(
    outputDir = os.path.join("/home", getpass.getuser(), "ttHAnalysis", version),
    executable_analyze = "analyze_2los_1tau",
    samples = samples,
    hadTau_selections = [ "Tight|dR03mvaTight", "Fakeable|dR03mvaTight", "Fakeable_mcClosure|dR03mvaTight" ],
    ##hadTau_selections = [ "Tight|dR03mvaTight" ],
    central_or_shifts = [ 
      "central",
##       "CMS_ttHl_btag_HFUp", 
##       "CMS_ttHl_btag_HFDown",	
##       "CMS_ttHl_btag_HFStats1Up", 
##       "CMS_ttHl_btag_HFStats1Down",
##       "CMS_ttHl_btag_HFStats2Up", 
##       "CMS_ttHl_btag_HFStats2Down",
##       "CMS_ttHl_btag_LFUp", 
##       "CMS_ttHl_btag_LFDown",	
##       "CMS_ttHl_btag_LFStats1Up", 
##       "CMS_ttHl_btag_LFStats1Down",
##       "CMS_ttHl_btag_LFStats2Up", 
##       "CMS_ttHl_btag_LFStats2Down",
##       "CMS_ttHl_btag_cErr1Up",
##       "CMS_ttHl_btag_cErr1Down",
##       "CMS_ttHl_btag_cErr2Up",
##       "CMS_ttHl_btag_cErr2Down",
##       "CMS_ttHl_JESUp",
##       "CMS_ttHl_JESDown",
##       "CMS_ttHl_tauESUp",
##       "CMS_ttHl_tauESDown"
##       "CMS_ttHl_FRjt_normUp",
##       "CMS_ttHl_FRjt_normDown",
##       "CMS_ttHl_FRjt_shapeUp",
##       "CMS_ttHl_FRjt_shapeDown"
##       "CMS_ttHl_FRet_shiftUp",
##       "CMS_ttHl_FRet_shiftDown",
##       "CMS_ttHl_FRmt_shiftUp",
##       "CMS_ttHl_FRmt_shiftDown"
    ],
    max_files_per_job = 30,
    era = ERA, use_lumi = True, lumi = LUMI,
    debug = False,
    running_method = "sbatch",
    num_parallel_jobs = 4,
    executable_addBackgrounds = "addBackgrounds",
    executable_addBackgroundJetToTauFakes = "addBackgroundLeptonFakes", # CV: use common executable for estimating jet->lepton and jet->tau_h fake background
    histograms_to_fit = [ "EventCounter", "numJets", "mvaDiscr_2lss", "mvaOutput_2los_1tau_ttbar", "mTauTauVis" ])

  analysis.create()

  run_analysis = query_yes_no("Start jobs ?")
  if run_analysis:
    analysis.run()
  else:
    sys.exit(0)

