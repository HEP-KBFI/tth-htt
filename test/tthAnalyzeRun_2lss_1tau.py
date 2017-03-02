import os, logging, sys, getpass

#--------------------------------------------------------------------------------
# NOTE: set mode flag to
#   'VHbb' : to run the analysis directly on the VHbb Ntuples (to e.g. produce the RLE files to run the tthProdNtuple and ttHAddMEM steps)
#   'addMEM' : to run the analysis on the Ntuples with MEM variables added
#   'forBDTtraining' : to run the analysis on the Ntuples with MEM variables added, and with a relaxed event selection, to increase the BDT training statistics
#--------------------------------------------------------------------------------

mode = "VHbb"
#mode = "addMEM"

hadTau_selection = None
changeBranchNames = None
if mode == "VHbb":
  from tthAnalysis.HiggsToTauTau.tthAnalyzeSamples_2lss_1tau_2015 import samples_2015
  from tthAnalysis.HiggsToTauTau.tthAnalyzeSamples_2lss_1tau_2016 import samples_2016
  hadTau_selection = "dR03mvaMedium"
  changeBranchNames = False
elif mode == "addMEM":
  from tthAnalysis.HiggsToTauTau.tthAnalyzeSamples_2016_2lss1tau_addMEM_v2 import samples_2016
  hadTau_selection = "dR03mvaMedium"
  changeBranchNames = True
elif mode == "forBDTtraining":
  from tthAnalysis.HiggsToTauTau.tthAnalyzeSamples_2016_2lss1tau_addMEM_forBDTtraining import samples_2016
  hadTau_selection = "dR03mvaVVLoose"
  changeBranchNames = True
else:
  raise ValueError("Invalid Configuration parameter 'mode' = %s !!" % mode)
from tthAnalysis.HiggsToTauTau.analyzeConfig_2lss_1tau import analyzeConfig_2lss_1tau
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

version = "2017Mar03"

if __name__ == '__main__':
  logging.basicConfig(
    stream = sys.stdout,
    level = logging.INFO,
    format = '%(asctime)s - %(levelname)s: %(message)s')

  analysis = analyzeConfig_2lss_1tau(
    configDir = os.path.join("/home", getpass.getuser(), "ttHAnalysis", ERA, version),
    ##outputDir = os.path.join("/hdfs/local/ttH_2tau", getpass.getuser(), "ttHAnalysis", ERA, version),
    outputDir = os.path.join("/home", getpass.getuser(), "ttHAnalysis", ERA, version),
    executable_analyze = "analyze_2lss_1tau", cfgFile_analyze = "analyze_2lss_1tau_cfg.py",
    samples = samples, changeBranchNames = changeBranchNames,
    lepton_charge_selections = [ "OS", "SS" ],
    hadTau_selection = hadTau_selection,
    # CV: apply "fake" background estimation to leptons only and not to hadronic taus, as discussed on slide 10 of
    #     https://indico.cern.ch/event/597028/contributions/2413742/attachments/1391684/2120220/16.12.22_ttH_Htautau_-_Review_of_systematics.pdf
    ##applyFakeRateWeights = "3L",
    applyFakeRateWeights = "2lepton",
    chargeSumSelections = [ "OS", "SS" ],
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
      #------------------------------------------------------
      # CV: enable the CMS_ttHl_FRe_shape and CMS_ttHl_FRm_shape only
      #     if you plan to run compShapeSyst 1!
##       "CMS_ttHl_FRe_shape_ptUp",
##       "CMS_ttHl_FRe_shape_ptDown",
##       "CMS_ttHl_FRe_shape_etaUp",
##       "CMS_ttHl_FRe_shape_etaDown",
##       "CMS_ttHl_FRe_shape_eta_barrelUp",
##       "CMS_ttHl_FRe_shape_eta_barrelDown",
##       "CMS_ttHl_FRm_shape_ptUp",
##       "CMS_ttHl_FRm_shape_ptDown",
##       "CMS_ttHl_FRm_shape_etaUp",
##       "CMS_ttHl_FRm_shape_etaDown",
      #------------------------------------------------------
##       "CMS_ttHl_tauESUp",
##       "CMS_ttHl_tauESDown",
##       "CMS_ttHl_FRjt_normUp",
##       "CMS_ttHl_FRjt_normDown",
##       "CMS_ttHl_FRjt_shapeUp",
##       "CMS_ttHl_FRjt_shapeDown"
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
    max_files_per_job = 100,
    era = ERA, use_lumi = True, lumi = LUMI,
    debug = False,
    running_method = "sbatch",
    num_parallel_jobs = 8,
    executable_addBackgrounds = "addBackgrounds",
    executable_addFakes = "addBackgroundLeptonFakes",
    executable_addFlips = "addBackgroundLeptonFlips", 
    histograms_to_fit = [ "EventCounter", "numJets", "mvaDiscr_2lss", "mvaDiscr_2lss_1tau", "mTauTauVis", "memOutput_LR" ],
    select_rle_output = True)

  if mode == "forBDTtraining":
    analysis.set_BDT_training()
  analysis.create()

  ##run_analysis = query_yes_no("Start jobs ?")
  run_analysis = True
  if run_analysis:
    analysis.run()
  else:
    sys.exit(0)

