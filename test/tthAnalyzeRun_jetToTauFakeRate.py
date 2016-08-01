import os, logging, sys, getpass

import tthAnalysis.HiggsToTauTau.tthAnalyzeSamples_jetToTauFakeRate
from tthAnalysis.HiggsToTauTau.analyzeConfig_jetToTauFakeRate import analyzeConfig_jetToTauFakeRate
from tthAnalysis.HiggsToTauTau.jobTools import query_yes_no

LUMI = 2301. # 1/pb

version = "2016Jul29"

if __name__ == '__main__':
  logging.basicConfig(
    stream = sys.stdout,
    level = logging.INFO,
    format = '%(asctime)s - %(levelname)s: %(message)s')

  analysis = analyzeConfig_jetToTauFakeRate(
    outputDir = os.path.join("/home", getpass.getuser(), "ttHAnalysis", version),
    executable_analyze = "analyze_jetToTauFakeRate",
    charge_selections = [ "OS" ],
    jet_minPt = 20.,
    jet_maxPt = 1.e+6,
    jet_minAbsEta = -1.,
    jet_maxAbsEta = 2.3, 
    hadTau_selections = [
      "dR05isoLoose",
      "dR05isoMedium",
      "dR05isoTight",
      "dR03mvaVLoose",
      "dR03mvaLoose",
      "dR03mvaMedium",
      "dR03mvaTight",
      "dR03mvaVTight",
      "dR03mvaVVTight"
    ],
    absEtaBins = [ -1., 1.479, 9.9 ],
    ptBins = [ 20., 25., 30., 35., 40., 45., 50., 60., 70., 80., 100., 200. ],
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
    ],
    max_files_per_job = 30,
    use_lumi = True, lumi = LUMI,
    debug = False,
    running_method = "sbatch",
    num_parallel_jobs = 4,
    executable_comp_jetToTauFakeRate = "comp_jetToTauFakeRate")

  analysis.create()

  run_analysis = query_yes_no("Start jobs ?")
  if run_analysis:
    analysis.run()
  else:
    sys.exit(0)

