#!/usr/bin/env python
import os, logging, sys, getpass

from tthAnalysis.HiggsToTauTau.analyzeConfig_1l_2tau import analyzeConfig_1l_2tau
from tthAnalysis.HiggsToTauTau.jobTools import query_yes_no

use_prod_ntuples = True
mode             = "VHbb"
ERA              = "2016"
version          = "2017Sep30"

samples              = None
LUMI                 = None
hadTau_selection     = None
changeBranchNames    = None
applyFakeRateWeights = None

if mode == "VHbb":
  from tthAnalysis.HiggsToTauTau.tthAnalyzeSamples_2015 import samples_2015
  from tthAnalysis.HiggsToTauTau.tthAnalyzeSamples_2016 import samples_2016
  hadTau_selection     = "dR03mvaVTight"
  changeBranchNames    = False
  applyFakeRateWeights = "3L"
elif mode == "forBDTtraining":
  if ERA == "2015":
    raise ValueError("Wrong combination of era and mode: %s and %s" % (ERA, mode))
  from tthAnalysis.HiggsToTauTau.tthAnalyzeSamples_2016_FastSim import samples_2016
  hadTau_selection     = "dR03mvaLoose"
  changeBranchNames    = False
  applyFakeRateWeights = "3L"
else:
  raise ValueError("Invalid Configuration parameter 'mode' = %s !!" % mode)

if use_prod_ntuples:
    from tthAnalysis.HiggsToTauTau.tthAnalyzeSamples_prodNtuples_2016 import samples_2016
    changeBranchNames = True

if samples_2015:
  for sample_name, sample_info in samples_2015.items():
    if sample_info["type"] == "mc":
      sample_info["triggers"] = ["1e", "1mu"]
    if sample_name in [
      "/DoubleMuon/Run2015C_25ns-16Dec2015-v1/MINIAOD",
      "/DoubleMuon/Run2015D-16Dec2015-v1/MINIAOD",
      "/DoubleEG/Run2015C_25ns-16Dec2015-v1/MINIAOD",
      "/DoubleEG/Run2015D-16Dec2015-v2/MINIAOD",
      "/MuonEG/Run2015C_25ns-16Dec2015-v1/MINIAOD",
      "/MuonEG/Run2015D-16Dec2015-v1/MINIAOD"]:
      sample_info["use_it"] = False

for sample_name, sample_info in samples_2016.items():
  if sample_info["type"] == "mc":
    sample_info["triggers"] = [ "1e", "1mu" ]
  if sample_name in [
      "/DoubleMuon/Run2016B-PromptReco-v2/MINIAOD",
      "/DoubleMuon/Run2016C-PromptReco-v2/MINIAOD",
      "/DoubleMuon/Run2016D-PromptReco-v2/MINIAOD",
      "/DoubleMuon/Run2016E-PromptReco-v2/MINIAOD",
      "/DoubleMuon/Run2016F-PromptReco-v1/MINIAOD",
      "/DoubleMuon/Run2016G-PromptReco-v1/MINIAOD",
      "/DoubleEG/Run2016B-PromptReco-v2/MINIAOD",
      "/DoubleEG/Run2016C-PromptReco-v2/MINIAOD",
      "/DoubleEG/Run2016D-PromptReco-v2/MINIAOD",
      "/DoubleEG/Run2016E-PromptReco-v2/MINIAOD",
      "/DoubleEG/Run2016F-PromptReco-v1/MINIAOD",
      "/DoubleEG/Run2016G-PromptReco-v1/MINIAOD",
      "/MuonEG/Run2016B-PromptReco-v2/MINIAOD",
      "/MuonEG/Run2016C-PromptReco-v2/MINIAOD",
      "/MuonEG/Run2016D-PromptReco-v2/MINIAOD",
      "/MuonEG/Run2016E-PromptReco-v2/MINIAOD",
      "/MuonEG/Run2016F-PromptReco-v1/MINIAOD",
      "/MuonEG/Run2016G-PromptReco-v1/MINIAOD",
      "/Tau/Run2016B-PromptReco-v2/MINIAOD",
      "/Tau/Run2016C-PromptReco-v2/MINIAOD",
      "/Tau/Run2016D-PromptReco-v2/MINIAOD",
      "/Tau/Run2016E-PromptReco-v2/MINIAOD",
      "/Tau/Run2016F-PromptReco-v1/MINIAOD",
      "/Tau/Run2016G-PromptReco-v1/MINIAOD" ]:
    sample_info["use_it"] = False


if ERA == "2015":
  if mode != "VHbb":
    raise ValueError("Invalid mode for era 2015: %s" % mode)
  samples = samples_2015
  LUMI    = 2.3e+3 # 1/pb
elif ERA == "2016":
  samples = samples_2016
  LUMI    = 35.9e+3 # 1/pb
else:
  raise ValueError("Invalid Configuration parameter 'ERA' = %s !!" % ERA)

if __name__ == '__main__':
  logging.basicConfig(
    stream = sys.stdout,
    level  = logging.INFO,
    format = '%(asctime)s - %(levelname)s: %(message)s'
  )

  analysis = analyzeConfig_1l_2tau(
    configDir          = os.path.join("/home",       getpass.getuser(), "ttHAnalysis", ERA, version),
    outputDir          = os.path.join("/hdfs/local", getpass.getuser(), "ttHAnalysis", ERA, version),
    executable_analyze       = "analyze_1l_2tau",
    cfgFile_analyze          = "analyze_1l_2tau_cfg.py",
    samples                  = samples,
    changeBranchNames        = changeBranchNames,
    hadTau_selection         = hadTau_selection,
    hadTau_charge_selections = [ "OS", "SS" ],
    applyFakeRateWeights     = applyFakeRateWeights,
    central_or_shifts = [
      "central",
##      "CMS_ttHl_btag_HFUp",
##      "CMS_ttHl_btag_HFDown",
##      "CMS_ttHl_btag_HFStats1Up",
##      "CMS_ttHl_btag_HFStats1Down",
##      "CMS_ttHl_btag_HFStats2Up",
##      "CMS_ttHl_btag_HFStats2Down",
##      "CMS_ttHl_btag_LFUp",
##      "CMS_ttHl_btag_LFDown",
##      "CMS_ttHl_btag_LFStats1Up",
##      "CMS_ttHl_btag_LFStats1Down",
##      "CMS_ttHl_btag_LFStats2Up",
##      "CMS_ttHl_btag_LFStats2Down",
##      "CMS_ttHl_btag_cErr1Up",
##      "CMS_ttHl_btag_cErr1Down",
##      "CMS_ttHl_btag_cErr2Up",
##      "CMS_ttHl_btag_cErr2Down",
##      "CMS_ttHl_JESUp",
##      "CMS_ttHl_JESDown",
##      "CMS_ttHl_tauESUp",
##      "CMS_ttHl_tauESDown",
##      "CMS_ttHl_FRjt_normUp",
##      "CMS_ttHl_FRjt_normDown",
##      "CMS_ttHl_FRjt_shapeUp",
##      "CMS_ttHl_FRjt_shapeDown",
##      "CMS_ttHl_FRet_shiftUp",
##      "CMS_ttHl_FRet_shiftDown",
##      "CMS_ttHl_FRmt_shiftUp",
##      "CMS_ttHl_FRmt_shiftDown",
##      "CMS_ttHl_thu_shape_ttH_x1Up",
##      "CMS_ttHl_thu_shape_ttH_x1Down",
##      "CMS_ttHl_thu_shape_ttH_y1Up",
##      "CMS_ttHl_thu_shape_ttH_y1Down",
##      "CMS_ttHl_thu_shape_ttW_x1Up",
##      "CMS_ttHl_thu_shape_ttW_x1Down",
##      "CMS_ttHl_thu_shape_ttW_y1Up",
##      "CMS_ttHl_thu_shape_ttW_y1Down",
##      "CMS_ttHl_thu_shape_ttZ_x1Up",
##      "CMS_ttHl_thu_shape_ttZ_x1Down",
##      "CMS_ttHl_thu_shape_ttZ_y1Up",
##      "CMS_ttHl_thu_shape_ttZ_y1Down",
    ],
    max_files_per_job                     = 10,
    era                                   = ERA,
    use_lumi                              = True,
    lumi                                  = LUMI,
    debug                                 = False,
    running_method                        = "sbatch",
    num_parallel_jobs                     = 52,
    executable_addBackgrounds             = "addBackgrounds",
    executable_addBackgroundJetToTauFakes = "addBackgroundLeptonFakes", # CV: use common executable for estimating jet->lepton and jet->tau_h fake background
    histograms_to_fit                     = [
      "EventCounter",
      "numJets",
      "mvaOutput_1l_2tau_ttbar",
      "mvaDiscr_1l_2tau",
      "mTauTauVis",
    ],
    select_rle_output                     = True,
  )

  if mode.find("forBDTtraining") != -1:
      analysis.set_BDT_training()

  analysis.create()

  run_analysis = query_yes_no("Start jobs ?")
  if run_analysis:
    analysis.run()
  else:
    sys.exit(0)
