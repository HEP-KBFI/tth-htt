from collections import OrderedDict as OD

meta_dictionary = OD()

### event sums

sum_events = {
  ("TTWJetsToLNu_ext1", "TTWJetsToLNu_ext2"),
  ("TTJets_SingleLeptFromT", "TTJets_SingleLeptFromT_ext1"),
  ("TGJets", "TGJets_ext1"),
  ("ttHToNonbb_fastsim_p1", "ttHToNonbb_fastsim_p2", "ttHToNonbb_fastsim_p3"),
  ("TTTo2L2Nu_fastsim_p1", "TTTo2L2Nu_fastsim_p2", "TTTo2L2Nu_fastsim_p3"),
  ("TTToSemilepton_fastsim_p1", "TTToSemilepton_fastsim_p2", "TTToSemilepton_fastsim_p3"),
  ("TTJets_SingleLeptFromTbar", "TTJets_SingleLeptFromTbar_ext1"),
  ("TTZToLL_M10_ext1", "TTZToLL_M10_ext2"),
  ("DYJetsToLL_M-50_ext1", "DYJetsToLL_M-50_ext2"),
  ("WGToLNuG_ext1", "WGToLNuG_ext2"),
  ("TTJets_DiLept", "TTJets_DiLept_ext1"),
  ("TTGJets", "TTGJets_ext1"),
}

### DATA

meta_dictionary["/DoubleEG/Run2016B-23Sep2016-v3/MINIAOD"] = OD([
  ("crab_string",           "VHBB_HEPPY_V25tthtautau_DoubleEG__Run2016B-23Sep2016-v3_forceResubmit2"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "DoubleEG_Run2016B_v3"),
  ("xsection",              None),
  ("use_it",                True),
])

meta_dictionary["/DoubleEG/Run2016C-23Sep2016-v1/MINIAOD"] = OD([
  ("crab_string",           "VHBB_HEPPY_V25tthtautau_v2_DoubleEG__Run2016C-23Sep2016-v1"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "DoubleEG_Run2016C_v1"),
  ("xsection",              None),
  ("use_it",                True),
])

meta_dictionary["/DoubleEG/Run2016D-23Sep2016-v1/MINIAOD"] = OD([
  ("crab_string",           "VHBB_HEPPY_V25tthtautau_v2_DoubleEG__Run2016D-23Sep2016-v1"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "DoubleEG_Run2016D_v1"),
  ("xsection",              None),
  ("use_it",                True),
])

meta_dictionary["/DoubleEG/Run2016E-23Sep2016-v1/MINIAOD"] = OD([
  ("crab_string",           "VHBB_HEPPY_V25tthtautau_v2_DoubleEG__Run2016E-23Sep2016-v1"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "DoubleEG_Run2016E_v1"),
  ("xsection",              None),
  ("use_it",                True),
])

meta_dictionary["/DoubleEG/Run2016F-23Sep2016-v1/MINIAOD"] = OD([
  ("crab_string",           "VHBB_HEPPY_V25tthtautau_v2_DoubleEG__Run2016F-23Sep2016-v1"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "DoubleEG_Run2016F_v1"),
  ("xsection",              None),
  ("use_it",                True),
])

meta_dictionary["/DoubleEG/Run2016G-23Sep2016-v1/MINIAOD"] = OD([
  ("crab_string",           "VHBB_HEPPY_V25tthtautau_v2_DoubleEG__Run2016G-23Sep2016-v1"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "DoubleEG_Run2016G_v1"),
  ("xsection",              None),
  ("use_it",                True),
])

meta_dictionary["/DoubleEG/Run2016H-PromptReco-v2/MINIAOD"] = OD([
  ("crab_string",           "VHBB_HEPPY_V25tthtautau_DoubleEG__Run2016H-PromptReco-v2"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "DoubleEG_Run2016H_v2_promptReco"),
  ("xsection",              None),
  ("use_it",                True),
])

meta_dictionary["/DoubleEG/Run2016H-PromptReco-v3/MINIAOD"] = OD([
  ("crab_string",           "VHBB_HEPPY_V25tthtautau_v3_DoubleEG__Run2016H-PromptReco-v3"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "DoubleEG_Run2016H_v3_promptReco"),
  ("xsection",              None),
  ("use_it",                True),
])

meta_dictionary["/DoubleMuon/Run2016B-23Sep2016-v3/MINIAOD"] = OD([
  ("crab_string",           "VHBB_HEPPY_V25tthtautau_v2_DoubleMuon__Run2016B-23Sep2016-v3"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "DoubleMuon_Run2016B_v3"),
  ("xsection",              None),
  ("use_it",                True),
])

meta_dictionary["/DoubleMuon/Run2016C-23Sep2016-v1/MINIAOD"] = OD([
  ("crab_string",           "VHBB_HEPPY_V25tthtautau_v2_DoubleMuon__Run2016C-23Sep2016-v1"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "DoubleMuon_Run2016C_v1"),
  ("xsection",              None),
  ("use_it",                True),
])

meta_dictionary["/DoubleMuon/Run2016D-23Sep2016-v1/MINIAOD"] = OD([
  ("crab_string",           "VHBB_HEPPY_V25tthtautau_v2_DoubleMuon__Run2016D-23Sep2016-v1"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "DoubleMuon_Run2016D_v1"),
  ("xsection",              None),
  ("use_it",                True),
])

meta_dictionary["/DoubleMuon/Run2016E-23Sep2016-v1/MINIAOD"] = OD([
  ("crab_string",           "VHBB_HEPPY_V25tthtautau_v2_DoubleMuon__Run2016E-23Sep2016-v1"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "DoubleMuon_Run2016E_v1"),
  ("xsection",              None),
  ("use_it",                True),
])

meta_dictionary["/DoubleMuon/Run2016F-23Sep2016-v1/MINIAOD"] = OD([
  ("crab_string",           "VHBB_HEPPY_V25tthtautau_v2_DoubleMuon__Run2016F-23Sep2016-v1"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "DoubleMuon_Run2016F_v1"),
  ("xsection",              None),
  ("use_it",                True),
])

meta_dictionary["/DoubleMuon/Run2016G-23Sep2016-v1/MINIAOD"] = OD([
  ("crab_string",           "VHBB_HEPPY_V25tthtautau_v2_DoubleMuon__Run2016G-23Sep2016-v1"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "DoubleMuon_Run2016G_v1"),
  ("xsection",              None),
  ("use_it",                True),
])

meta_dictionary["/DoubleMuon/Run2016H-PromptReco-v2/MINIAOD"] = OD([
  ("crab_string",           "VHBB_HEPPY_V25tthtautau_DoubleMuon__Run2016H-PromptReco-v2"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "DoubleMuon_Run2016H_v2_promptReco"),
  ("xsection",              None),
  ("use_it",                True),
])

meta_dictionary["/DoubleMuon/Run2016H-PromptReco-v3/MINIAOD"] = OD([
  ("crab_string",           "VHBB_HEPPY_V25tthtautau_v3_DoubleMuon__Run2016H-PromptReco-v3"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "DoubleMuon_Run2016H_v3_promptReco"),
  ("xsection",              None),
  ("use_it",                True),
])

meta_dictionary["/MuonEG/Run2016B-23Sep2016-v3/MINIAOD"] = OD([
  ("crab_string",           "VHBB_HEPPY_V25tthtautau_v2_MuonEG__Run2016B-23Sep2016-v3"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "MuonEG_Run2016B_v3"),
  ("xsection",              None),
  ("use_it",                True),
])

meta_dictionary["/MuonEG/Run2016C-23Sep2016-v1/MINIAOD"] = OD([
  ("crab_string",           "VHBB_HEPPY_V25tthtautau_v2_MuonEG__Run2016C-23Sep2016-v1"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "MuonEG_Run2016C_v1"),
  ("xsection",              None),
  ("use_it",                True),
])

meta_dictionary["/MuonEG/Run2016D-23Sep2016-v1/MINIAOD"] = OD([
  ("crab_string",           "VHBB_HEPPY_V25tthtautau_MuonEG__Run2016D-23Sep2016-v1"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "MuonEG_Run2016D_v1"),
  ("xsection",              None),
  ("use_it",                True),
])

meta_dictionary["/MuonEG/Run2016E-23Sep2016-v1/MINIAOD"] = OD([
  ("crab_string",           "VHBB_HEPPY_V25tthtautau_v2_MuonEG__Run2016E-23Sep2016-v1"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "MuonEG_Run2016E_v1"),
  ("xsection",              None),
  ("use_it",                True),
])

meta_dictionary["/MuonEG/Run2016F-23Sep2016-v1/MINIAOD"] = OD([
  ("crab_string",           "VHBB_HEPPY_V25tthtautau_v2_MuonEG__Run2016F-23Sep2016-v1"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "MuonEG_Run2016F_v1"),
  ("xsection",              None),
  ("use_it",                True),
])

meta_dictionary["/MuonEG/Run2016G-23Sep2016-v1/MINIAOD"] = OD([
  ("crab_string",           "VHBB_HEPPY_V25tthtautau_v2_MuonEG__Run2016G-23Sep2016-v1"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "MuonEG_Run2016G_v1"),
  ("xsection",              None),
  ("use_it",                True),
])

meta_dictionary["/MuonEG/Run2016H-PromptReco-v2/MINIAOD"] = OD([
  ("crab_string",           "VHBB_HEPPY_V25tthtautau_v3_MuonEG__Run2016H-PromptReco-v2"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "MuonEG_Run2016H_v2_promptReco"),
  ("xsection",              None),
  ("use_it",                True),
])

meta_dictionary["/MuonEG/Run2016H-PromptReco-v3/MINIAOD"] = OD([
  ("crab_string",           "VHBB_HEPPY_V25tthtautau_MuonEG__Run2016H-PromptReco-v3"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "MuonEG_Run2016H_v3_promptReco"),
  ("xsection",              None),
  ("use_it",                True),
])

meta_dictionary["/SingleElectron/Run2016B-23Sep2016-v3/MINIAOD"] = OD([
  ("crab_string",           "VHBB_HEPPY_V25tthtautau_v3_SingleElectron__Run2016B-23Sep2016-v3"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "SingleElectron_Run2016B_v3"),
  ("xsection",              None),
  ("use_it",                True),
])

meta_dictionary["/SingleElectron/Run2016C-23Sep2016-v1/MINIAOD"] = OD([
  ("crab_string",           "VHBB_HEPPY_V25tthtautau_v3_SingleElectron__Run2016C-23Sep2016-v1"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "SingleElectron_Run2016C_v1"),
  ("xsection",              None),
  ("use_it",                True),
])

meta_dictionary["/SingleElectron/Run2016D-23Sep2016-v1/MINIAOD"] = OD([
  ("crab_string",           "VHBB_HEPPY_V25tthtautau_v3_SingleElectron__Run2016D-23Sep2016-v1"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "SingleElectron_Run2016D_v1"),
  ("xsection",              None),
  ("use_it",                True),
])

meta_dictionary["/SingleElectron/Run2016E-23Sep2016-v1/MINIAOD"] = OD([
  ("crab_string",           "VHBB_HEPPY_V25tthtautau_v3_SingleElectron__Run2016E-23Sep2016-v1"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "SingleElectron_Run2016E_v1"),
  ("xsection",              None),
  ("use_it",                True),
])

meta_dictionary["/SingleElectron/Run2016F-23Sep2016-v1/MINIAOD"] = OD([
  ("crab_string",           "VHBB_HEPPY_V25tthtautau_v2_SingleElectron__Run2016F-23Sep2016-v1"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "SingleElectron_Run2016F_v1"),
  ("xsection",              None),
  ("use_it",                True),
])

meta_dictionary["/SingleElectron/Run2016G-23Sep2016-v1/MINIAOD"] = OD([
  ("crab_string",           "VHBB_HEPPY_V25tthtautau_v2_SingleElectron__Run2016G-23Sep2016-v1"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "SingleElectron_Run2016G_v1"),
  ("xsection",              None),
  ("use_it",                True),
])

meta_dictionary["/SingleElectron/Run2016H-PromptReco-v2/MINIAOD"] = OD([
  ("crab_string",           "VHBB_HEPPY_V25tthtautau_SingleElectron__Run2016H-PromptReco-v2"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "SingleElectron_Run2016H_v2_promptReco"),
  ("xsection",              None),
  ("use_it",                True),
])

meta_dictionary["/SingleElectron/Run2016H-PromptReco-v3/MINIAOD"] = OD([
  ("crab_string",           "VHBB_HEPPY_V25tthtautau_v3_SingleElectron__Run2016H-PromptReco-v3"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "SingleElectron_Run2016H_v3_promptReco"),
  ("xsection",              None),
  ("use_it",                True),
])

meta_dictionary["/SingleMuon/Run2016B-23Sep2016-v3/MINIAOD"] = OD([
  ("crab_string",           "VHBB_HEPPY_V25tthtautau_v3_SingleMuon__Run2016B-23Sep2016-v3"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "SingleMuon_Run2016B_v3"),
  ("xsection",              None),
  ("use_it",                True),
])

meta_dictionary["/SingleMuon/Run2016C-23Sep2016-v1/MINIAOD"] = OD([
  ("crab_string",           "VHBB_HEPPY_V25tthtautau_v3_SingleMuon__Run2016C-23Sep2016-v1"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "SingleMuon_Run2016C_v1"),
  ("xsection",              None),
  ("use_it",                True),
])

meta_dictionary["/SingleMuon/Run2016D-23Sep2016-v1/MINIAOD"] = OD([
  ("crab_string",           "VHBB_HEPPY_V25tthtautau_v2_SingleMuon__Run2016D-23Sep2016-v1"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "SingleMuon_Run2016D_v1"),
  ("xsection",              None),
  ("use_it",                True),
])

meta_dictionary["/SingleMuon/Run2016E-23Sep2016-v1/MINIAOD"] = OD([
  ("crab_string",           "VHBB_HEPPY_V25tthtautau_v3_SingleMuon__Run2016E-23Sep2016-v1"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "SingleMuon_Run2016E_v1"),
  ("xsection",              None),
  ("use_it",                True),
])

meta_dictionary["/SingleMuon/Run2016F-23Sep2016-v1/MINIAOD"] = OD([
  ("crab_string",           "VHBB_HEPPY_V25tthtautau_v2_SingleMuon__Run2016F-23Sep2016-v1"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "SingleMuon_Run2016F_v1"),
  ("xsection",              None),
  ("use_it",                True),
])

meta_dictionary["/SingleMuon/Run2016G-23Sep2016-v1/MINIAOD"] = OD([
  ("crab_string",           "VHBB_HEPPY_V25tthtautau_v2_SingleMuon__Run2016G-23Sep2016-v1"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "SingleMuon_Run2016G_v1"),
  ("xsection",              None),
  ("use_it",                True),
])

meta_dictionary["/SingleMuon/Run2016H-PromptReco-v2/MINIAOD"] = OD([
  ("crab_string",           "VHBB_HEPPY_V25tthtautau_SingleMuon__Run2016H-PromptReco-v2"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "SingleMuon_Run2016H_v2_promptReco"),
  ("xsection",              None),
  ("use_it",                True),
])

meta_dictionary["/SingleMuon/Run2016H-PromptReco-v3/MINIAOD"] = OD([
  ("crab_string",           "VHBB_HEPPY_V25tthtautau_SingleMuon__Run2016H-PromptReco-v3"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "SingleMuon_Run2016H_v3_promptReco"),
  ("xsection",              None),
  ("use_it",                True),
])

meta_dictionary["/Tau/Run2016B-23Sep2016-v3/MINIAOD"] = OD([
  ("crab_string",           "VHBB_HEPPY_V25tthtautau_HLT_Tau__Run2016B-23Sep2016-v3"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "Tau_Run2016B_v3"),
  ("xsection",              None),
  ("use_it",                True),
])

meta_dictionary["/Tau/Run2016C-23Sep2016-v1/MINIAOD"] = OD([
  ("crab_string",           "VHBB_HEPPY_V25tthtautau_HLT_Tau__Run2016C-23Sep2016-v1"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "Tau_Run2016C_v1"),
  ("xsection",              None),
  ("use_it",                True),
])

meta_dictionary["/Tau/Run2016D-23Sep2016-v1/MINIAOD"] = OD([
  ("crab_string",           "VHBB_HEPPY_V25tthtautau_HLT_Tau__Run2016D-23Sep2016-v1"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "Tau_Run2016D_v1"),
  ("xsection",              None),
  ("use_it",                True),
])

meta_dictionary["/Tau/Run2016E-23Sep2016-v1/MINIAOD"] = OD([
  ("crab_string",           "VHBB_HEPPY_V25tthtautau_HLT_Tau__Run2016E-23Sep2016-v1"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "Tau_Run2016E_v1"),
  ("xsection",              None),
  ("use_it",                True),
])

meta_dictionary["/Tau/Run2016F-23Sep2016-v1/MINIAOD"] = OD([
  ("crab_string",           "VHBB_HEPPY_V25tthtautau_HLT_Tau__Run2016F-23Sep2016-v1"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "Tau_Run2016F_v1"),
  ("xsection",              None),
  ("use_it",                True),
])

meta_dictionary["/Tau/Run2016G-23Sep2016-v1/MINIAOD"] = OD([
  ("crab_string",           "VHBB_HEPPY_V25tthtautau_v2_Tau__Run2016G-23Sep2016-v1"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "Tau_Run2016G_v1"),
  ("xsection",              None),
  ("use_it",                True),
])

meta_dictionary["/Tau/Run2016H-PromptReco-v2/MINIAOD"] = OD([
  ("crab_string",           "VHBB_HEPPY_V25tthtautau_v3_Tau__Run2016H-PromptReco-v2"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "Tau_Run2016H_v2_promptReco"),
  ("xsection",              None),
  ("use_it",                True),
])

meta_dictionary["/Tau/Run2016H-PromptReco-v3/MINIAOD"] = OD([
  ("crab_string",           "VHBB_HEPPY_V25tthtautau_Tau__Run2016H-PromptReco-v3"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "Tau_Run2016H_v3_promptReco"),
  ("xsection",              None),
  ("use_it",                True),
])

### MC

meta_dictionary["/DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] = OD([
  ("crab_string",           "VHBB_HEPPY_V25tthtautau_v3_DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-madgraphMLM-Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6-v1"),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DYJetsToLL_M-10to50"),
  ("xsection",              18610.),
  ("use_it",                True),
  ("genWeight",             True),
])

meta_dictionary["/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v2/MINIAODSIM"] = OD([
  ("crab_string",           "VHBB_HEPPY_V25tthtautau_v3_DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6_ext1-v2"),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DYJetsToLL_M-50_ext1"),
  ("xsection",              6025.2),
  ("use_it",                True),
  ("genWeight",             True),
])

meta_dictionary["/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext2-v1/MINIAODSIM"] = OD([
  ("crab_string",           "VHBB_HEPPY_V25tthtautau_v3_DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6_ext2-v1"),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DYJetsToLL_M-50_ext2"),
  ("xsection",              6025.2),
  ("use_it",                True),
  ("genWeight",             True),
])

meta_dictionary["/GluGluHToZZTo4L_M125_13TeV_powheg2_JHUgenV6_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] = OD([
  ("crab_string",           "VHBB_HEPPY_V25tthtautau_GluGluHToZZTo4L_M125_13TeV_powheg2_JHUgenV6_Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6-v1"),
  ("sample_category",       "additional_signal_overlap"),
  ("process_name_specific", "GluGluHToZZTo4L"),
  ("xsection",              0.0119),
  ("use_it",                True),
  ("genWeight",             True),
])

meta_dictionary["/ST_s-channel_4f_leptonDecays_13TeV-amcatnlo-pythia8_TuneCUETP8M1/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] = OD([
  ("crab_string",           "VHBB_HEPPY_V25tthtautau_ST_s-channel_4f_leptonDecays_13TeV-amcatnlo-Py8_TuneCUETP8M1__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6-v1"),
  ("sample_category",       "TT"),
  ("process_name_specific", "ST_s-channel_4f_leptonDecays"),
  ("xsection",              3.68),
  ("use_it",                True),
  ("genWeight",             True),
])

meta_dictionary["/ST_t-channel_antitop_4f_inclusiveDecays_13TeV-powhegV2-madspin-pythia8_TuneCUETP8M1/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] = OD([
  ("crab_string",           "VHBB_HEPPY_V25tt_ST_t-channel_antitop_4f_inclusiveDecays_13TeV-powhegV2-madspin-Py8_TuneCUETP8M1__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6-v1"),
  ("sample_category",       "TT"),
  ("process_name_specific", "ST_t-channel_antitop_4f_inclusiveDecays"),
  ("xsection",              80.95),
  ("use_it",                True),
  ("genWeight",             True),
])

meta_dictionary["/ST_t-channel_top_4f_inclusiveDecays_13TeV-powhegV2-madspin-pythia8_TuneCUETP8M1/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] = OD([
  ("crab_string",           "VHBB_HEPPY_V25tthtautau_ST_t-channel_top_4f_inclusiveDecays_13TeV-powhegV2-madspin-Py8_TuneCUETP8M1__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6-v1"),
  ("sample_category",       "TT"),
  ("process_name_specific", "ST_t-channel_top_4f_inclusiveDecays"),
  ("xsection",              136.02),
  ("use_it",                True),
  ("genWeight",             True),
])

meta_dictionary["/ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"] = OD([
  ("crab_string",           "VHBB_HEPPY_V25tthtautau_ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-Py8_TuneCUETP8M1__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6_ext1-v1"),
  ("sample_category",       "TT"),
  ("process_name_specific", "ST_tW_antitop_5f_inclusiveDecays"),
  ("xsection",              35.6),
  ("use_it",                True),
  ("genWeight",             True),
])

meta_dictionary["/ST_tW_top_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"] = OD([
  ("crab_string",           "VHBB_HEPPY_V25tthtautau_ST_tW_top_5f_inclusiveDecays_13TeV-powheg-Py8_TuneCUETP8M1__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6_ext1-v1"),
  ("sample_category",       "TT"),
  ("process_name_specific", "ST_tW_top_5f_inclusiveDecays"),
  ("xsection",              35.6),
  ("use_it",                True),
  ("genWeight",             True),
])

meta_dictionary["/TGJets_TuneCUETP8M1_13TeV_amcatnlo_madspin_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"] = OD([
  ("crab_string",           "VHBB_HEPPY_V25tthtautau_TGJets_TuneCUETP8M1_13TeV_amcatnlo_madspin_Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6_ext1-v1"),
  ("sample_category",       "Rares"),
  ("process_name_specific", "TGJets_ext1"),
  ("xsection",              2.967),
  ("use_it",                True),
  ("genWeight",             True),
])

meta_dictionary["/TGJets_TuneCUETP8M1_13TeV_amcatnlo_madspin_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] = OD([
  ("crab_string",           "VHBB_HEPPY_V25tthtautau_TGJets_TuneCUETP8M1_13TeV_amcatnlo_madspin_Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6-v1"),
  ("sample_category",       "Rares"),
  ("process_name_specific", "TGJets"),
  ("xsection",              2.967),
  ("use_it",                True),
  ("genWeight",             True),
])

meta_dictionary["/TTGJets_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"] = OD([
  ("crab_string",           "VHBB_HEPPY_V25tthtautau_TTGJets_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6_ext1-v1"),
  ("sample_category",       "Rares"),
  ("process_name_specific", "TTGJets_ext1"),
  ("xsection",              3.697),
  ("use_it",                True),
  ("genWeight",             True),
])

meta_dictionary["/TTGJets_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] = OD([
  ("crab_string",           "VHBB_HEPPY_V25tthtautau_TTGJets_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6-v1"),
  ("sample_category",       "Rares"),
  ("process_name_specific", "TTGJets"),
  ("xsection",              3.697),
  ("use_it",                True),
  ("genWeight",             True),
])

meta_dictionary["/ttHJetTobb_M125_13TeV_amcatnloFXFX_madspin_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext3-v1/MINIAODSIM"] = OD([
  ("crab_string",           "VHBB_HEPPY_V25tthtautau_v2_ttHJetTobb_M125_13TeV_amcatnloFXFX_madspin_Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6_ext3-v1"),
  ("sample_category",       "ttH_hbb"),
  ("process_name_specific", "ttHJetTobb_M125"),
  ("xsection",              0.2934),
  ("use_it",                True),
  ("genWeight",             True),
])

meta_dictionary["/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"] = OD([
  ("crab_string",           "VHBB_HEPPY_V25tthtautau_ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_Py8_mWCutfix__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6_ext1-v1"),
  ("sample_category",       "signal"),
  ("process_name_specific", "ttHJetToNonbb_M125_amcatnlo"),
  ("xsection",              0.2151),
  ("use_it",                True),
  ("genWeight",             True),
])

meta_dictionary["/ttHToNonbb_M125_TuneCUETP8M2_ttHtranche3_13TeV-powheg-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] = OD([
  ("crab_string",           "VHBB_HEPPY_V25tthtautau_ttHToNonbb_M125_TuneCUETP8M2_ttHtranche3_13TeV-powheg-Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6-v1"),
  ("sample_category",       "signal"),
  ("process_name_specific", "ttHToNonbb_M125_powheg"),
  ("xsection",              0.2151),
  ("use_it",                False),
  ("genWeight",             True),
])

meta_dictionary["/TTJets_DiLept_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"] = OD([
  ("crab_string",           "VHBB_HEPPY_V25tthtautau_TTJets_DiLept_TuneCUETP8M1_13TeV-madgraphMLM-Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6_ext1-v1"),
  ("sample_category",       "TT"),
  ("process_name_specific", "TTJets_DiLept_ext1"),
  ("xsection",              87.3),
  ("use_it",                True),
  ("genWeight",             True),
])

meta_dictionary["/TTJets_DiLept_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] = OD([
  ("crab_string",           "VHBB_HEPPY_V25tthtautau_TTJets_DiLept_TuneCUETP8M1_13TeV-madgraphMLM-Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6-v1"),
  ("sample_category",       "TT"),
  ("process_name_specific", "TTJets_DiLept"),
  ("xsection",              87.3),
  ("use_it",                True),
  ("genWeight",             True),
])

meta_dictionary["/TTJets_SingleLeptFromTbar_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"] = OD([
  ("crab_string",           "VHBB_HEPPY_V25tthtautau_v2_TTJets_SingleLeptFromTbar_TuneCUETP8M1_13TeV-madgraphMLM-Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6_ext1-v1"),
  ("sample_category",       "TT"),
  ("process_name_specific", "TTJets_SingleLeptFromTbar_ext1"),
  ("xsection",              182.18),
  ("use_it",                True),
  ("genWeight",             True),
])

meta_dictionary["/TTJets_SingleLeptFromTbar_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] = OD([
  ("crab_string",           "VHBB_HEPPY_V25tthtautau_TTJets_SingleLeptFromTbar_TuneCUETP8M1_13TeV-madgraphMLM-Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6-v1"),
  ("sample_category",       "TT"),
  ("process_name_specific", "TTJets_SingleLeptFromTbar"),
  ("xsection",              182.18),
  ("use_it",                True),
  ("genWeight",             True),
])

meta_dictionary["/TTJets_SingleLeptFromT_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"] = OD([
  ("crab_string",           "VHBB_HEPPY_V25tthtautau_TTJets_SingleLeptFromT_TuneCUETP8M1_13TeV-madgraphMLM-Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6_ext1-v1"),
  ("sample_category",       "TT"),
  ("process_name_specific", "TTJets_SingleLeptFromT_ext1"),
  ("xsection",              182.18),
  ("use_it",                True),
  ("genWeight",             True),
])

meta_dictionary["/TTJets_SingleLeptFromT_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] = OD([
  ("crab_string",           "VHBB_HEPPY_V25tthtautau_TTJets_SingleLeptFromT_TuneCUETP8M1_13TeV-madgraphMLM-Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6-v1"),
  ("sample_category",       "TT"),
  ("process_name_specific", "TTJets_SingleLeptFromT"),
  ("xsection",              182.18),
  ("use_it",                True),
  ("genWeight",             True),
])

meta_dictionary["/TTTT_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] = OD([
  ("crab_string",           "VHBB_HEPPY_V25tthtautau_TTTT_TuneCUETP8M1_13TeV-amcatnlo-Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6-v1"),
  ("sample_category",       "Rares"),
  ("process_name_specific", "TTTT"),
  ("xsection",              0.009103),
  ("use_it",                True),
  ("genWeight",             True),
])

meta_dictionary["/TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v3/MINIAODSIM"] = OD([
  ("crab_string",           "VHBB_HEPPY_V25tthtautau_TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6_ext1-v3"),
  ("sample_category",       "TTW"),
  ("process_name_specific", "TTWJetsToLNu_ext1"),
  ("xsection",              0.2043),
  ("use_it",                True),
  ("genWeight",             True),
])

meta_dictionary["/TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext2-v1/MINIAODSIM"] = OD([
  ("crab_string",           "VHBB_HEPPY_V25tthtautau_TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6_ext2-v1"),
  ("sample_category",       "TTW"),
  ("process_name_specific", "TTWJetsToLNu_ext2"),
  ("xsection",              0.2043),
  ("use_it",                True),
  ("genWeight",             True),
])

meta_dictionary["/TTZToLL_M-1to10_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] = OD([
  ("crab_string",           "VHBB_HEPPY_V25tthtautau_TTZToLL_M-1to10_TuneCUETP8M1_13TeV-madgraphMLM-Py8__RunIISummer16MAv2-80r2as_2016_TrancheIV_v6-v1"),
  ("sample_category",       "TTZ"),
  ("process_name_specific", "TTZToLL_M-1to10"),
  ("xsection",              0.0493),
  ("use_it",                True),
  ("genWeight",             True),
])

meta_dictionary["/TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"] = OD([
  ("crab_string",           "VHBB_HEPPY_V25tthtautau_TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6_ext1-v1"),
  ("sample_category",       "TTZ"),
  ("process_name_specific", "TTZToLL_M10_ext1"),
  ("xsection",              0.2529*1.08), # CV: scale by factor 1.08 (https://hypernews.cern.ch/HyperNews/CMS/get/HIG-17-004/19/1.html)
  ("use_it",                True),
  ("genWeight",             True),
])

meta_dictionary["/TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext2-v1/MINIAODSIM"] = OD([
  ("crab_string",           "VHBB_HEPPY_V25tthtautau_TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6_ext2-v1"),
  ("sample_category",       "TTZ"),
  ("process_name_specific", "TTZToLL_M10_ext2"),
  ("xsection",              0.2529*1.08), # CV: scale by factor 1.08 (https://hypernews.cern.ch/HyperNews/CMS/get/HIG-17-004/19/1.html)
  ("use_it",                True),
  ("genWeight",             True),
])

meta_dictionary["/tZq_ll_4f_13TeV-amcatnlo-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"] = OD([
  ("crab_string",           "VHBB_HEPPY_V25tthtautau_tZq_ll_4f_13TeV-amcatnlo-Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6_ext1-v1"),
  ("sample_category",       "Rares"),
  ("process_name_specific", "tZq_ll_4f"),
  ("xsection",              0.0758),
  ("use_it",                True),
  ("genWeight",             True),
])

meta_dictionary["/WGToLNuG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"] = OD([
  ("crab_string",           "VHBB_HEPPY_V25tthtautau_WGToLNuG_TuneCUETP8M1_13TeV-amcatnloFXFX-Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6_ext1-v1"),
  ("sample_category",       "Rares"),
  ("process_name_specific", "WGToLNuG_ext1"),
  ("xsection",              585.8),
  ("use_it",                True),
  ("genWeight",             True),
])

meta_dictionary["/WGToLNuG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext2-v1/MINIAODSIM"] = OD([
  ("crab_string",           "VHBB_HEPPY_V25tthtautau_WGToLNuG_TuneCUETP8M1_13TeV-amcatnloFXFX-Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6_ext2-v1"),
  ("sample_category",       "Rares"),
  ("process_name_specific", "WGToLNuG_ext2"),
  ("xsection",              585.8),
  ("use_it",                True),
  ("genWeight",             True),
])

meta_dictionary["/WJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] = OD([
  ("crab_string",           "VHBB_HEPPY_V25tthtautau_WJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6-v1"),
  ("sample_category",       "EWK"),
  ("process_name_specific", "WJetsToLNu"),
  ("xsection",              61526.7),
  ("use_it",                True),
  ("genWeight",             True),
])

meta_dictionary["/WpWpJJ_EWK-QCD_TuneCUETP8M1_13TeV-madgraph-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] = OD([
  ("crab_string",           "VHBB_HEPPY_V25tthtautau_WpWpJJ_EWK-QCD_TuneCUETP8M1_13TeV-madgraph-Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6-v1"),
  ("sample_category",       "Rares"),
  ("process_name_specific", "WpWpJJ_EWK-QCD"),
  ("xsection",              0.03711),
  ("use_it",                True),
  ("genWeight",             True),
])

meta_dictionary["/WWTo2L2Nu_13TeV-powheg/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] = OD([
  ("crab_string",           "VHBB_HEPPY_V25tthtautau_WWTo2L2Nu_13TeV-powheg__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6-v1"),
  ("sample_category",       "EWK"),
  ("process_name_specific", "WWTo2L2Nu"),
  ("xsection",              10.481),
  ("use_it",                True),
  ("genWeight",             True),
])

meta_dictionary["/WWTo2L2Nu_DoubleScattering_13TeV-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] = OD([
  ("crab_string",           "VHBB_HEPPY_V25tthtautau_WWTo2L2Nu_DoubleScattering_13TeV-Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6-v1"),
  ("sample_category",       "Rares"),
  ("process_name_specific", "WWTo2L2Nu_DoubleScattering"),
  ("xsection",              0.1729),
  ("use_it",                True),
  ("genWeight",             True),
])

meta_dictionary["/WWW_4F_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] = OD([
  ("crab_string",           "VHBB_HEPPY_V25tthtautau_WWW_4F_TuneCUETP8M1_13TeV-amcatnlo-Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6-v1"),
  ("sample_category",       "Rares"),
  ("process_name_specific", "WWW_4F"),
  ("xsection",              0.2086),
  ("use_it",                True),
  ("genWeight",             True),
])

meta_dictionary["/WWZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] = OD([
  ("crab_string",           "VHBB_HEPPY_V25tthtautau_WWZ_TuneCUETP8M1_13TeV-amcatnlo-Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6-v1"),
  ("sample_category",       "Rares"),
  ("process_name_specific", "WWZ"),
  ("xsection",              0.1651),
  ("use_it",                True),
  ("genWeight",             True),
])

meta_dictionary["/WZTo3LNu_TuneCUETP8M1_13TeV-powheg-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] = OD([
  ("crab_string",           "VHBB_HEPPY_V25tthtautau_WZTo3LNu_TuneCUETP8M1_13TeV-powheg-Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6-v1"),
  ("sample_category",       "EWK"),
  ("process_name_specific", "WZTo3LNu"),
  ("xsection",              4.42965),
  ("use_it",                True),
  ("genWeight",             True),
])

meta_dictionary["/WZZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] = OD([
  ("crab_string",           "VHBB_HEPPY_V25tthtautau_WZZ_TuneCUETP8M1_13TeV-amcatnlo-Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6-v1"),
  ("sample_category",       "Rares"),
  ("process_name_specific", "WZZ"),
  ("xsection",              0.05565),
  ("use_it",                True),
  ("genWeight",             True),
])

meta_dictionary["/ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"] = OD([
  ("crab_string",           "VHBB_HEPPY_V25tthtautau_ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6_ext1-v1"),
  ("sample_category",       "Rares"),
  ("process_name_specific", "ZGTo2LG"),
  ("xsection",              131.3),
  ("use_it",                True),
  ("genWeight",             True),
])

meta_dictionary["/ZZTo4L_13TeV_powheg_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] = OD([
  ("crab_string",           "VHBB_HEPPY_V25tthtautau_ZZTo4L_13TeV_powheg_Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6-v1"),
  ("sample_category",       "EWK"),
  ("process_name_specific", "ZZTo4L"),
  ("xsection",              1.256),
  ("use_it",                True),
  ("genWeight",             True),
])

meta_dictionary["/ZZZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] = OD([
  ("crab_string",           "VHBB_HEPPY_V25tthtautau_ZZZ_TuneCUETP8M1_13TeV-amcatnlo-Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6-v1"),
  ("sample_category",       "Rares"),
  ("process_name_specific", "ZZZ"),
  ("xsection",              0.01398),
  ("use_it",                True),
  ("genWeight",             True),
])

meta_dictionary["/THQ_Hincl_13TeV-madgraph-pythia8_TuneCUETP8M1/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] = OD([
  ("crab_string",           "VHBB_HEPPY_V25tthtautau_tHq_tHW_THQ_Hincl_13TeV-madgraph-Py8_TuneCUETP8M1__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6-v1"),
  ("sample_category",       "tH"),
  ("process_name_specific", "THQ"),
  ("xsection",              0.07096*0.324/0.705305),
  ("use_it",                True),
  ("genWeight",             True),
])

meta_dictionary["/THW_Hincl_13TeV-madgraph-pythia8_TuneCUETP8M1/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] = OD([
  ("crab_string",           "VHBB_HEPPY_V25tthtautau_tHq_tHW_THW_Hincl_13TeV-madgraph-Py8_TuneCUETP8M1__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6-v1"),
  ("sample_category",       "tH"),
  ("process_name_specific", "THW"),
  ("xsection",              0.01561/0.273617),
  ("use_it",                True),
  ("genWeight",             True),
])

meta_dictionary["/ttWW_lo/MINIAODSIM"] = OD([
  ("crab_string",           "VHBB_HEPPY_V25tthtautau_ttWW_TTWW_gpetrucc"),
  ("sample_category",       "TTWW"),
  ("process_name_specific", "TTWW"),
  ("xsection",              0.011500*0.2002),
  ("use_it",                True),
  ("genWeight",             True),
])

### Fastsim

meta_dictionary["/ttHToNonbb_M125_TuneCUETP8M2_ttHtranche3_13TeV-powheg-pythia8/matze-faster_v8_ttH_maod_p1_3a2fa29ab1d54ae0995b28f27b405be9-v1/USER"] = OD([
  ("crab_string",           "VHBB_HEPPY_V25tthtautau_ttHToNonbb_M125_TuneCUETP8M2_ttHtranche3_13TeV-powheg-Py8__matze-faster_v8_ttH_maod_p1_3a2fa29ab1d54ae0995b28f27b405be9-v1"),
  ("sample_category",       "signal"),
  ("process_name_specific", "ttHToNonbb_fastsim_p1"),
  ("xsection",              0.2151),
  ("use_it",                False),
  ("genWeight",             True),
])

meta_dictionary["/ttHToNonbb_M125_TuneCUETP8M2_ttHtranche3_13TeV-powheg-pythia8/matze-faster_v8_ttH_maod_p2_3a2fa29ab1d54ae0995b28f27b405be9-v1/USER"] = OD([
  ("crab_string",           "VHBB_HEPPY_V25tthtautau_ttHToNonbb_M125_TuneCUETP8M2_ttHtranche3_13TeV-powheg-Py8__matze-faster_v8_ttH_maod_p2_3a2fa29ab1d54ae0995b28f27b405be9-v1"),
  ("sample_category",       "signal"),
  ("process_name_specific", "ttHToNonbb_fastsim_p2"),
  ("xsection",              0.2151),
  ("use_it",                False),
  ("genWeight",             True),
])

meta_dictionary["/ttHToNonbb_M125_TuneCUETP8M2_ttHtranche3_13TeV-powheg-pythia8/matze-faster_v8_ttH_maod_p3_3a2fa29ab1d54ae0995b28f27b405be9-v1/USER"] = OD([
  ("crab_string",           "VHBB_HEPPY_V25tthtautau_ttHToNonbb_M125_TuneCUETP8M2_ttHtranche3_13TeV-powheg-Py8__matze-faster_v8_ttH_maod_p3_3a2fa29ab1d54ae0995b28f27b405be9-v1"),
  ("sample_category",       "signal"),
  ("process_name_specific", "ttHToNonbb_fastsim_p3"),
  ("xsection",              0.2151),
  ("use_it",                False),
  ("genWeight",             True),
])

meta_dictionary["/TTTo2L2Nu_TuneCUETP8M2_ttHtranche3_13TeV-powheg-pythia8/matze-faster_v8_ttjets_dl_maod_p1_3a2fa29ab1d54ae0995b28f27b405be9-v1/USER"] = OD([
  ("crab_string",           "VHBB_HEPPY_V25tthtautau_TTTo2L2Nu_TuneCUETP8M2_ttHtranche3_13TeV-powheg-Py8__matze-faster_v8_ttjets_dl_maod_p1_3a2fa29ab1d54ae0995b28f27b405be9-v1"),
  ("sample_category",       "TT"),
  ("process_name_specific", "TTTo2L2Nu_fastsim_p1"),
  ("xsection",              87.3),
  ("use_it",                False),
  ("genWeight",             True),
])

meta_dictionary["/TTTo2L2Nu_TuneCUETP8M2_ttHtranche3_13TeV-powheg-pythia8/matze-faster_v8_ttjets_dl_maod_p2_3a2fa29ab1d54ae0995b28f27b405be9-v1/USER"] = OD([
  ("crab_string",           "VHBB_HEPPY_V25tthtautau_TTTo2L2Nu_TuneCUETP8M2_ttHtranche3_13TeV-powheg-Py8__matze-faster_v8_ttjets_dl_maod_p2_3a2fa29ab1d54ae0995b28f27b405be9-v1"),
  ("sample_category",       "TT"),
  ("process_name_specific", "TTTo2L2Nu_fastsim_p2"),
  ("xsection",              87.3),
  ("use_it",                False),
  ("genWeight",             True),
])

meta_dictionary["/TTTo2L2Nu_TuneCUETP8M2_ttHtranche3_13TeV-powheg-pythia8/matze-faster_v8_ttjets_dl_maod_p3_3a2fa29ab1d54ae0995b28f27b405be9-v1/USER"] = OD([
  ("crab_string",           "VHBB_HEPPY_V25tthtautau_TTTo2L2Nu_TuneCUETP8M2_ttHtranche3_13TeV-powheg-Py8__matze-faster_v8_ttjets_dl_maod_p3_3a2fa29ab1d54ae0995b28f27b405be9-v1"),
  ("sample_category",       "TT"),
  ("process_name_specific", "TTTo2L2Nu_fastsim_p3"),
  ("xsection",              87.3),
  ("use_it",                False),
  ("genWeight",             True),
])

meta_dictionary["/TTToSemilepton_TuneCUETP8M2_ttHtranche3_13TeV-powheg-pythia8/matze-faster_v8_ttjets_sl_maod_p1_3a2fa29ab1d54ae0995b28f27b405be9-v1/USER"] = OD([
  ("crab_string",           "VHBB_HEPPY_V25tthtautau_TTToSemilepton_TuneCUETP8M2_ttHtranche3_13TeV-powheg-Py8__matze-faster_v8_ttjets_sl_maod_p1_3a2fa29ab1d54ae0995b28f27b405be9-v1"),
  ("sample_category",       "TT"),
  ("process_name_specific", "TTToSemilepton_fastsim_p1"),
  ("xsection",              245),
  ("use_it",                False),
  ("genWeight",             True),
])

meta_dictionary["/TTToSemilepton_TuneCUETP8M2_ttHtranche3_13TeV-powheg-pythia8/matze-faster_v8_ttjets_sl_maod_p2_3a2fa29ab1d54ae0995b28f27b405be9-v1/USER"] = OD([
  ("crab_string",           "VHBB_HEPPY_V25tthtautau_TTToSemilepton_TuneCUETP8M2_ttHtranche3_13TeV-powheg-Py8__matze-faster_v8_ttjets_sl_maod_p2_3a2fa29ab1d54ae0995b28f27b405be9-v1"),
  ("sample_category",       "TT"),
  ("process_name_specific", "TTToSemilepton_fastsim_p2"),
  ("xsection",              245),
  ("use_it",                False),
  ("genWeight",             True),
])

meta_dictionary["/TTToSemilepton_TuneCUETP8M2_ttHtranche3_13TeV-powheg-pythia8/matze-faster_v8_ttjets_sl_maod_p3_3a2fa29ab1d54ae0995b28f27b405be9-v1/USER"] = OD([
  ("crab_string",           "VHBB_HEPPY_V25tthtautau_TTToSemilepton_TuneCUETP8M2_ttHtranche3_13TeV-powheg-Py8__matze-faster_v8_ttjets_sl_maod_p3_3a2fa29ab1d54ae0995b28f27b405be9-v1"),
  ("sample_category",       "TT"),
  ("process_name_specific", "TTToSemilepton_fastsim_p3"),
  ("xsection",              245),
  ("use_it",                False),
  ("genWeight",             True),
])

meta_dictionary["/TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/matze-faster_v9_ttW_maod_54aa74f75231422e9f4d3766cb92a64a-v1/USER"] = OD([
  ("crab_string",           "VHBB_HEPPY_V25tthtautau_TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-Py8__matze-faster_v9_ttW_maod_54aa74f75231422e9f4d3766cb92a64a-v1"),
  ("sample_category",       "TTW"),
  ("process_name_specific", "TTWJetsToLNu_fastsim"),
  ("xsection",              0.2043),
  ("use_it",                False),
  ("genWeight",             True),
])

meta_dictionary["/TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-pythia8/matze-faster_v9_ttZ_maod_54aa74f75231422e9f4d3766cb92a64a-v1/USER"] = OD([
  ("crab_string",           "VHBB_HEPPY_V25tthtautau_TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-Py8__matze-faster_v9_ttZ_maod_54aa74f75231422e9f4d3766cb92a64a-v1"),
  ("sample_category",       "TTZ"),
  ("process_name_specific", "TTZToLLNuNu_fastsim"),
  ("xsection",              0.2529),
  ("use_it",                False),
  ("genWeight",             True),
])

meta_dictionary["/WZTo3LNu_TuneCUETP8M1_13TeV-powheg-pythia8/matze-faster_v9_WZ_maod_54aa74f75231422e9f4d3766cb92a64a-v1/USER"] = OD([
  ("crab_string",           "VHBB_HEPPY_V25tthtautau_WZTo3LNu_TuneCUETP8M1_13TeV-powheg-Py8__matze-faster_v9_WZ_maod_54aa74f75231422e9f4d3766cb92a64a-v1"),
  ("sample_category",       "EWK"),
  ("process_name_specific", "WZTo3LNu_fastsim"),
  ("xsection",              4.102),
  ("use_it",                False),
  ("genWeight",             True),
])
