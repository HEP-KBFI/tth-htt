#!/usr/bin/env python
import os, logging, sys, getpass

from tthAnalysis.HiggsToTauTau.analyzeConfig_1l_1tau import analyzeConfig_1l_1tau
from tthAnalysis.HiggsToTauTau.jobTools import query_yes_no

use_prod_ntuples = True
ERA              = "2016"
version          = "2017Oct04"

samples           = None
LUMI              = None
changeBranchNames = None

if use_prod_ntuples:
  if ERA == "2015":
    raise ValueError("No production Ntuples for 2015 data & MC")
  from tthAnalysis.HiggsToTauTau.tthAnalyzeSamples_prodNtuples_2016 import samples_2016
  changeBranchNames = True
else:
  from tthAnalysis.HiggsToTauTau.tthAnalyzeSamples_2015 import samples_2015
  from tthAnalysis.HiggsToTauTau.tthAnalyzeSamples_2016 import samples_2016
  changeBranchNames = False

if ERA == "2015":
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
    sample_info["triggers"] = [ "1e", "1mu", "1e1tau", "1mu1tau" ]
  if sample_name in [
      "/DoubleEG/Run2016B-23Sep2016-v3/MINIAOD",
      "/DoubleEG/Run2016C-23Sep2016-v1/MINIAOD",
      "/DoubleEG/Run2016E-23Sep2016-v1/MINIAOD",
      "/DoubleEG/Run2016G-23Sep2016-v1/MINIAOD",
      "/DoubleEG/Run2016H-PromptReco-v2/MINIAOD",
      "/DoubleEG/Run2016H-PromptReco-v3/MINIAOD",
      "/DoubleEG/Run2016D-23Sep2016-v1/MINIAOD",
      "/DoubleEG/Run2016F-23Sep2016-v1/MINIAOD",
      "/DoubleMuon/Run2016B-23Sep2016-v3/MINIAOD",
      "/DoubleMuon/Run2016E-23Sep2016-v1/MINIAOD",
      "/DoubleMuon/Run2016F-23Sep2016-v1/MINIAOD",
      "/DoubleMuon/Run2016H-PromptReco-v2/MINIAOD",
      "/DoubleMuon/Run2016H-PromptReco-v3/MINIAOD",
      "/DoubleMuon/Run2016C-23Sep2016-v1/MINIAOD",
      "/DoubleMuon/Run2016D-23Sep2016-v1/MINIAOD",
      "/DoubleMuon/Run2016G-23Sep2016-v1/MINIAOD",
      "/MuonEG/Run2016D-23Sep2016-v1/MINIAOD",
      "/MuonEG/Run2016H-PromptReco-v2/MINIAOD",
      "/MuonEG/Run2016H-PromptReco-v3/MINIAOD",
      "/MuonEG/Run2016B-23Sep2016-v3/MINIAOD",
      "/MuonEG/Run2016C-23Sep2016-v1/MINIAOD",
      "/MuonEG/Run2016E-23Sep2016-v1/MINIAOD",
      "/MuonEG/Run2016F-23Sep2016-v1/MINIAOD",
      "/MuonEG/Run2016G-23Sep2016-v1/MINIAOD" ]:
    sample_info["use_it"] = False

if ERA == "2015":
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
    format = '%(asctime)s - %(levelname)s: %(message)s',
  )

  analysis = analyzeConfig_1l_1tau(
    configDir          = os.path.join("/home", getpass.getuser(), "ttHAnalysis", ERA, version),
    outputDir          = os.path.join("/hdfs/local", getpass.getuser(), "ttHAnalysis", ERA, version),
    executable_analyze   = "analyze_1l_1tau",
    cfgFile_analyze      = "analyze_1l_1tau_cfg.py",
    samples              = samples,
    changeBranchNames    = changeBranchNames,
    hadTau_selection     = "dR03mvaVTight",
    applyFakeRateWeights = "2L",
    chargeSumSelections  = [ "OS", "SS" ],
    central_or_shifts    = [
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
    num_parallel_jobs                     = 100, # Karl: speed up the hadd steps
    executable_addBackgrounds             = "addBackgrounds",
    executable_addBackgroundJetToTauFakes = "addBackgroundLeptonFakes", # CV: use common executable for estimating jet->lepton and jet->tau_h fake background
    histograms_to_fit                     = [
      "EventCounter",
      "numJets",
      "mvaOutput_1l_1tau_ttbar",
      "mTauTauVis",
      "mTauTau",
    ],
    select_rle_output                     = True,
  )

  analysis.create()

  run_analysis = query_yes_no("Start jobs ?")
  if run_analysis:
    analysis.run()
  else:
    sys.exit(0)
