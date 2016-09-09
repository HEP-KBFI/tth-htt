import os, logging, sys, getpass

import tthAnalysis.HiggsToTauTau.tthAnalyzeSamples_2l_2tau
from tthAnalysis.HiggsToTauTau.analyzeConfig_2l_2tau import analyzeConfig_2l_2tau
from tthAnalysis.HiggsToTauTau.jobTools import query_yes_no

LUMI = 2301. # 1/pb

version = "2016Sep07_dR03mvaTight"

if __name__ == '__main__':
  logging.basicConfig(
    stream = sys.stdout,
    level = logging.INFO,
    format = '%(asctime)s - %(levelname)s: %(message)s')

  analysis = analyzeConfig_2l_2tau(
    outputDir = os.path.join("/home", getpass.getuser(), "ttHAnalysis", version),
    executable_analyze = "analyze_2l_2tau",
    lepton_charge_selections = [ "OS" ],
    hadTau_selections = [ "Tight|dR03mvaTight", "Fakeable", "Fakeable_mcClosure" ],
    ##hadTau_selections = [ "Tight|dR03mvaTight" ],
    hadTau_charge_selections = [ "OS", "SS" ],
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
       "CMS_ttHl_FRjt_normUp",
       "CMS_ttHl_FRjt_normDown",
       "CMS_ttHl_FRjt_shapeUp",
       "CMS_ttHl_FRjt_shapeDown"
       "CMS_ttHl_FRet_shiftUp",
       "CMS_ttHl_FRet_shiftDown",
       "CMS_ttHl_FRmt_shiftUp",
       "CMS_ttHl_FRmt_shiftDown"
    ],
    max_files_per_job = 30,
    use_lumi = True, lumi = LUMI,
    debug = False,
    running_method = "sbatch",
    num_parallel_jobs = 4,
    executable_addBackgrounds = "addBackgrounds",
    executable_addBackgroundJetToTauFakes = "addBackgroundLeptonFakes", # CV: use common executable for estimating jet->lepton and jet->tau_h fake background
    histograms_to_fit = [ "EventCounter", "numJets", "mTauTauVis" ])

  analysis.create()

  run_analysis = query_yes_no("Start jobs ?")
  if run_analysis:
    analysis.run()
  else:
    sys.exit(0)

