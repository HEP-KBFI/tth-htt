#!/usr/bin/env python
import os, logging, sys, getpass
from tthAnalysis.HiggsToTauTau.analyzeConfig_2los_1tau import analyzeConfig_2los_1tau
from tthAnalysis.HiggsToTauTau.jobTools import query_yes_no

#--------------------------------------------------------------------------------
# NOTE: set mode flag to
#   'VHbb'           : to run the analysis on the VHbb Ntuples, with the nominal event selection
#   'forBDTtraining' : to run the analysis on the VHbb Ntuples, with a relaxed event selection, to increase the BDT training statistics
#--------------------------------------------------------------------------------

#mode = "VHbb"
mode = "VHbb"
#mode = "forBDTtraining_beforeAddMEM"
#mode = "forBDTtraining_afterAddMEM"

if mode == "VHbb":
  from tthAnalysis.HiggsToTauTau.tthAnalyzeSamples_2los_1tau_2015 import samples_2015
  from tthAnalysis.HiggsToTauTau.tthAnalyzeSamples_2los_1tau_2016 import samples_2016
  hadTau_selection = "dR03mvaMedium"
  changeBranchNames = False
  applyFakeRateWeights  = "3L"
elif mode == "forBDTtraining":
  from tthAnalysis.HiggsToTauTau.tthAnalyzeSamples_2016_FastSim import samples_2016
  hadTau_selection = "dR03mvaLoose"
  changeBranchNames = False
  applyFakeRateWeights = "3L"
else:
  raise ValueError("Invalid Configuration parameter 'mode' = %s !!" % mode)

#ERA = "2015"
ERA = "2016"

samples = None
LUMI = None
if ERA == "2015":
  try:
    samples = samples_2015
  except NameError:
    raise ValueError("Mode {mode} not available for era {era}".format(mode = mode, era = ERA))
  LUMI =  2.3e+3 # 1/pb
elif ERA == "2016":
  samples = samples_2016
  LUMI = 35.9e+3 # 1/pb
else:
  raise ValueError("Invalid Configuration parameter 'ERA' = %s !!" % ERA)

version = "2017Jul07"

if __name__ == '__main__':
  logging.basicConfig(
    stream = sys.stdout,
    level  = logging.INFO,
    format = '%(asctime)s - %(levelname)s: %(message)s',
  )

  configDir = os.path.join("/home",       getpass.getuser(), "ttHAnalysis", ERA, version)
  outputDir = os.path.join("/hdfs/local", getpass.getuser(), "ttHAnalysis", ERA, version)

  analysis = analyzeConfig_2los_1tau(
    configDir                 = configDir,
    outputDir                 = outputDir,
    executable_analyze        = "analyze_2los_1tau",
    cfgFile_analyze           = "analyze_2los_1tau_cfg.py",
    samples                   = samples,
    changeBranchNames         = changeBranchNames,
    hadTau_selection          = hadTau_selection,
    applyFakeRateWeights      = applyFakeRateWeights,
    central_or_shifts         = [
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
##       "CMS_ttHl_thu_shape_ttZ_y1Down",
    ],
    max_files_per_job         = 100,
    era                       = ERA,
    use_lumi                  = True,
    lumi                      = LUMI,
    debug                     = False,
    running_method            = "sbatch",
    num_parallel_jobs         = 8,
    executable_addBackgrounds = "addBackgrounds",
    executable_addFakes       = "addBackgroundLeptonFakes",
    histograms_to_fit         = [
      "EventCounter",
      "numJets",
      "mvaDiscr_2lss",
      "mvaOutput_2los_1tau_ttbar",
      "mTauTauVis"
    ],
    select_rle_output         = True,
  )

  if mode.find("forBDTtraining") != -1:
    analysis.set_BDT_training()

  analysis.create()

  run_analysis = query_yes_no("Start jobs ?")
  ##run_analysis = True
  if run_analysis:
    analysis.run()
  else:
    sys.exit(0)
