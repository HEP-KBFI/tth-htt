from collections import OrderedDict as OD

from tthAnalyzeSamples_2016 import samples_2016

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
    
