import os, logging, sys, getpass

from tthAnalysis.HiggsToTauTau.tthAnalyzeSamples_jetToTauFakeRate_2015 import samples_2015
from tthAnalysis.HiggsToTauTau.tthAnalyzeSamples_jetToTauFakeRate_2016 import samples_2016
from tthAnalysis.HiggsToTauTau.analyzeConfig_LeptonFakeRate import analyzeConfig_LeptonFakeRate
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

version = "2017Sep19"

if __name__ == '__main__':
  logging.basicConfig(
    stream = sys.stdout,
    level = logging.INFO,
    format = '%(asctime)s - %(levelname)s: %(message)s')

  analysis = analyzeConfig_LeptonFakeRate(
    configDir = os.path.join("/home", getpass.getuser(), "ttHAnalysis_2017Sep19", ERA, version),
    outputDir = os.path.join("/hdfs/local", getpass.getuser(), "ttHAnalysis_LeptonFakeRate_trial_2017Sep19", ERA, version),
    cmssw_base_dir_combine = "",
    executable_analyze = "analyze_LeptonFakeRate",
    samples = samples,
    absEtaBins_e  = [ -1., 1.479, 9.9 ],
    absEtaBins_mu = [ -1., 1.479, 9.9 ],
    absPtBins_e   = [ 20., 30., 100000.],
    absPtBins_mu  = [ 10., 30., 100000.],
    fillGenEvtHistograms = False,
    central_or_shifts = [ 
      "central",
      "CMS_ttHl_JESUp",
      "CMS_ttHl_JESDown",
      "CMS_ttHl_JERUp",
      "CMS_ttHl_JERDown",
      "CMS_ttHl_UnclusteredEnUp",
      "CMS_ttHl_UnclusteredEnDown"
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
##       "CMS_ttHl_tauESDown",
##       "CMS_ttHl_FRet_shiftUp",
##       "CMS_ttHl_FRet_shiftDown",
##       "CMS_ttHl_FRmt_shiftUp",
##       "CMS_ttHl_FRmt_shiftDown",
##       "CMS_ttHl_thu_shape_ttH_x1Up",  
##       "CMS_ttHl_thu_shape_ttH_x1Down",
##       "CMS_ttHl_thu_shape_ttH_y1Up",   
##       "CMS_ttHl_thu_shape_ttH_y1Down",
##       "CMS_ttHl_thu_shape_ttW_x1Up",
##       "CMS_ttHl_thu_shape_ttW_x1Down",
##       "CMS_ttHl_thu_shape_ttW_y1Up",
##       "CMS_ttHl_thu_shape_ttW_y1Down",
##       "CMS_ttHl_thu_shape_ttZ_x1Up",
##       "CMS_ttHl_thu_shape_ttZ_x1Down",
##       "CMS_ttHl_thu_shape_ttZ_y1Up",
##       "CMS_ttHl_thu_shape_ttZ_y1Down"  
    ],
    histograms_to_fit = [
      "mT_fix_L"
    ],
    prep_dcard = True,
    max_files_per_job = 100,
    era = ERA, 
    use_lumi = True, 
    lumi = LUMI,
    debug = False,
    running_method = "sbatch",
    executable_addBackgrounds_LeptonFakeRate = "addBackground_LeptonFakeRate",
    executable_prep_dcard = "prepareDatacards",
#    charge_selections = [ "OS" ],
#    executable_comp_LeptonFakeRate = "comp_LeptonFakeRate",
    num_parallel_jobs = 8
)


  analysis.create()

  run_analysis = query_yes_no("Start jobs ?")
  if run_analysis:
    analysis.run()
  else:
    sys.exit(0)

