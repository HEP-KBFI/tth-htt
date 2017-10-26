from collections import OrderedDict as OD

samples_2016 = OD()

# file generated with command:
# check_broken -p /hdfs/local/karl/addMEM/2016/2017Mar17/final_ntuples_recopied/2lss_1tau -o -z -i -P -v

samples_2016["/ST_t-channel_antitop_4f_inclusiveDecays_13TeV-powhegV2-madspin-pythia8_TuneCUETP8M1/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "TT"),
  ("process_name_specific", "ST_t-channel_antitop_4f_inclusiveDecays"),
  ("nof_files",             1),
  ("nof_events",            38795356),
  ("use_it",                True),
  ("xsection",              80.950000),
  ("genWeight",             True),
  ("triggers",              [ "1e", "1mu", "2e", "1e1mu", "2mu", "3e", "2e1mu", "1e2mu", "3mu", "1e1tau", "1mu1tau", "2tau" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/addMEM/2016/2017Mar17/final_ntuples_recopied/2lss_1tau/ST_t-channel_antitop_4f_inclusiveDecays_13TeV-powhegV2-madspin-pythia8_TuneCUETP8M1/VHBB_HEPPY_V25tt_ST_t-channel_antitop_4f_inclusiveDecays_13TeV-powhegV2-madspin-Py8_TuneCUETP8M1__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6-v1/170209_102511"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/DoubleEG/Run2016B-23Sep2016-v3/MINIAOD"] = OD([
  ("type",                  "data"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "DoubleEG_Run2016B_v3"),
  ("nof_files",             1),
  ("nof_events",            143073264),
  ("use_HIP_mitigation_bTag", True),
  ("use_HIP_mitigation_mediumMuonId", True),
  ("use_it",                True),
  ("triggers",              [ "2e", "3e" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/addMEM/2016/2017Mar17/final_ntuples_recopied/2lss_1tau/DoubleEG/VHBB_HEPPY_V25tthtautau_DoubleEG__Run2016B-23Sep2016-v3_forceResubmit2/170219_190454"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/DoubleEG/Run2016H-PromptReco-v2/MINIAOD"] = OD([
  ("type",                  "data"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "DoubleEG_Run2016H_v2_promptReco"),
  ("nof_files",             1),
  ("nof_events",            84344488),
  ("use_HIP_mitigation_bTag", False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                True),
  ("triggers",              [ "2e", "3e" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/addMEM/2016/2017Mar17/final_ntuples_recopied/2lss_1tau/DoubleEG/VHBB_HEPPY_V25tthtautau_DoubleEG__Run2016H-PromptReco-v2/170215_142837"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/DoubleMuon/Run2016H-PromptReco-v2/MINIAOD"] = OD([
  ("type",                  "data"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "DoubleMuon_Run2016H_v2_promptReco"),
  ("nof_files",             1),
  ("nof_events",            48093748),
  ("use_HIP_mitigation_bTag", False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                True),
  ("triggers",              [ "2mu", "3mu" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/addMEM/2016/2017Mar17/final_ntuples_recopied/2lss_1tau/DoubleMuon/VHBB_HEPPY_V25tthtautau_DoubleMuon__Run2016H-PromptReco-v2/170215_142956"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/Tau/Run2016B-23Sep2016-v3/MINIAOD"] = OD([
  ("type",                  "data"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "Tau_Run2016B_v3"),
  ("nof_files",             1),
  ("nof_events",            68727448),
  ("use_HIP_mitigation_bTag", True),
  ("use_HIP_mitigation_mediumMuonId", True),
  ("use_it",                True),
  ("triggers",              [ "1e1tau", "1mu1tau", "2tau" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/addMEM/2016/2017Mar17/final_ntuples_recopied/2lss_1tau/Tau/VHBB_HEPPY_V25tthtautau_HLT_Tau__Run2016B-23Sep2016-v3/170216_184427"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/Tau/Run2016C-23Sep2016-v1/MINIAOD"] = OD([
  ("type",                  "data"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "Tau_Run2016C_v1"),
  ("nof_files",             1),
  ("nof_events",            36931472),
  ("use_HIP_mitigation_bTag", True),
  ("use_HIP_mitigation_mediumMuonId", True),
  ("use_it",                True),
  ("triggers",              [ "1e1tau", "1mu1tau", "2tau" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/addMEM/2016/2017Mar17/final_ntuples_recopied/2lss_1tau/Tau/VHBB_HEPPY_V25tthtautau_HLT_Tau__Run2016C-23Sep2016-v1/170216_182257"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/Tau/Run2016D-23Sep2016-v1/MINIAOD"] = OD([
  ("type",                  "data"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "Tau_Run2016D_v1"),
  ("nof_files",             1),
  ("nof_events",            56827772),
  ("use_HIP_mitigation_bTag", True),
  ("use_HIP_mitigation_mediumMuonId", True),
  ("use_it",                True),
  ("triggers",              [ "1e1tau", "1mu1tau", "2tau" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/addMEM/2016/2017Mar17/final_ntuples_recopied/2lss_1tau/Tau/VHBB_HEPPY_V25tthtautau_HLT_Tau__Run2016D-23Sep2016-v1/170216_182421"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/Tau/Run2016E-23Sep2016-v1/MINIAOD"] = OD([
  ("type",                  "data"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "Tau_Run2016E_v1"),
  ("nof_files",             1),
  ("nof_events",            58348772),
  ("use_HIP_mitigation_bTag", True),
  ("use_HIP_mitigation_mediumMuonId", True),
  ("use_it",                True),
  ("triggers",              [ "1e1tau", "1mu1tau", "2tau" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/addMEM/2016/2017Mar17/final_ntuples_recopied/2lss_1tau/Tau/VHBB_HEPPY_V25tthtautau_HLT_Tau__Run2016E-23Sep2016-v1/170216_182541"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/Tau/Run2016F-23Sep2016-v1/MINIAOD"] = OD([
  ("type",                  "data"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "Tau_Run2016F_v1"),
  ("nof_files",             1),
  ("nof_events",            40549716),
  ("use_HIP_mitigation_bTag", True),
  ("use_HIP_mitigation_mediumMuonId", True),
  ("use_it",                True),
  ("triggers",              [ "1e1tau", "1mu1tau", "2tau" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/addMEM/2016/2017Mar17/final_ntuples_recopied/2lss_1tau/Tau/VHBB_HEPPY_V25tthtautau_HLT_Tau__Run2016F-23Sep2016-v1/170216_182849"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/MuonEG/Run2016D-23Sep2016-v1/MINIAOD"] = OD([
  ("type",                  "data"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "MuonEG_Run2016D_v1"),
  ("nof_files",             1),
  ("nof_events",            23482352),
  ("use_HIP_mitigation_bTag", True),
  ("use_HIP_mitigation_mediumMuonId", True),
  ("use_it",                True),
  ("triggers",              [ "1e1mu", "2e1mu", "1e2mu" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/addMEM/2016/2017Mar17/final_ntuples_recopied/2lss_1tau/MuonEG/VHBB_HEPPY_V25tthtautau_MuonEG__Run2016D-23Sep2016-v1/170207_125438"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/MuonEG/Run2016H-PromptReco-v3/MINIAOD"] = OD([
  ("type",                  "data"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "MuonEG_Run2016H_v3_promptReco"),
  ("nof_files",             1),
  ("nof_events",            770494),
  ("use_HIP_mitigation_bTag", False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                True),
  ("triggers",              [ "1e1mu", "2e1mu", "1e2mu" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/addMEM/2016/2017Mar17/final_ntuples_recopied/2lss_1tau/MuonEG/VHBB_HEPPY_V25tthtautau_MuonEG__Run2016H-PromptReco-v3/170215_143932"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/ST_s-channel_4f_leptonDecays_13TeV-amcatnlo-pythia8_TuneCUETP8M1/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "TT"),
  ("process_name_specific", "ST_s-channel_4f_leptonDecays"),
  ("nof_files",             1),
  ("nof_events",            622689),
  ("use_it",                True),
  ("xsection",              3.680000),
  ("genWeight",             True),
  ("triggers",              [ "1e", "1mu", "2e", "1e1mu", "2mu", "3e", "2e1mu", "1e2mu", "3mu", "1e1tau", "1mu1tau", "2tau" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/addMEM/2016/2017Mar17/final_ntuples_recopied/2lss_1tau/ST_s-channel_4f_leptonDecays_13TeV-amcatnlo-pythia8_TuneCUETP8M1/VHBB_HEPPY_V25tthtautau_ST_s-channel_4f_leptonDecays_13TeV-amcatnlo-Py8_TuneCUETP8M1__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6-v1/170207_123409"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/ST_t-channel_top_4f_inclusiveDecays_13TeV-powhegV2-madspin-pythia8_TuneCUETP8M1/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "TT"),
  ("process_name_specific", "ST_t-channel_top_4f_inclusiveDecays"),
  ("nof_files",             1),
  ("nof_events",            67073424),
  ("use_it",                True),
  ("xsection",              136.020000),
  ("genWeight",             True),
  ("triggers",              [ "1e", "1mu", "2e", "1e1mu", "2mu", "3e", "2e1mu", "1e2mu", "3mu", "1e1tau", "1mu1tau", "2tau" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/addMEM/2016/2017Mar17/final_ntuples_recopied/2lss_1tau/ST_t-channel_top_4f_inclusiveDecays_13TeV-powhegV2-madspin-pythia8_TuneCUETP8M1/VHBB_HEPPY_V25tthtautau_ST_t-channel_top_4f_inclusiveDecays_13TeV-powhegV2-madspin-Py8_TuneCUETP8M1__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6-v1/170208_120156"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "TT"),
  ("process_name_specific", "ST_tW_antitop_5f_inclusiveDecays"),
  ("nof_files",             1),
  ("nof_events",            6884378),
  ("use_it",                True),
  ("xsection",              35.600000),
  ("genWeight",             True),
  ("triggers",              [ "1e", "1mu", "2e", "1e1mu", "2mu", "3e", "2e1mu", "1e2mu", "3mu", "1e1tau", "1mu1tau", "2tau" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/addMEM/2016/2017Mar17/final_ntuples_recopied/2lss_1tau/ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1/VHBB_HEPPY_V25tthtautau_ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-Py8_TuneCUETP8M1__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6_ext1-v1/170207_123614"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/ST_tW_top_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "TT"),
  ("process_name_specific", "ST_tW_top_5f_inclusiveDecays"),
  ("nof_files",             1),
  ("nof_events",            6942672),
  ("use_it",                True),
  ("xsection",              35.600000),
  ("genWeight",             True),
  ("triggers",              [ "1e", "1mu", "2e", "1e1mu", "2mu", "3e", "2e1mu", "1e2mu", "3mu", "1e1tau", "1mu1tau", "2tau" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/addMEM/2016/2017Mar17/final_ntuples_recopied/2lss_1tau/ST_tW_top_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1/VHBB_HEPPY_V25tthtautau_ST_tW_top_5f_inclusiveDecays_13TeV-powheg-Py8_TuneCUETP8M1__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6_ext1-v1/170207_133952"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/SingleElectron/Run2016H-PromptReco-v2/MINIAOD"] = OD([
  ("type",                  "data"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "SingleElectron_Run2016H_v2_promptReco"),
  ("nof_files",             1),
  ("nof_events",            126863480),
  ("use_HIP_mitigation_bTag", False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                True),
  ("triggers",              [ "1e" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/addMEM/2016/2017Mar17/final_ntuples_recopied/2lss_1tau/SingleElectron/VHBB_HEPPY_V25tthtautau_SingleElectron__Run2016H-PromptReco-v2/170215_145016"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/SingleMuon/Run2016H-PromptReco-v2/MINIAOD"] = OD([
  ("type",                  "data"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "SingleMuon_Run2016H_v2_promptReco"),
  ("nof_files",             1),
  ("nof_events",            171134784),
  ("use_HIP_mitigation_bTag", False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                True),
  ("triggers",              [ "1mu" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/addMEM/2016/2017Mar17/final_ntuples_recopied/2lss_1tau/SingleMuon/VHBB_HEPPY_V25tthtautau_SingleMuon__Run2016H-PromptReco-v2/170215_143417"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/SingleMuon/Run2016H-PromptReco-v3/MINIAOD"] = OD([
  ("type",                  "data"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "SingleMuon_Run2016H_v3_promptReco"),
  ("nof_files",             1),
  ("nof_events",            4393222),
  ("use_HIP_mitigation_bTag", False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                True),
  ("triggers",              [ "1mu" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/addMEM/2016/2017Mar17/final_ntuples_recopied/2lss_1tau/SingleMuon/VHBB_HEPPY_V25tthtautau_SingleMuon__Run2016H-PromptReco-v3/170215_144050"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/TGJets_TuneCUETP8M1_13TeV_amcatnlo_madspin_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "Rares"),
  ("process_name_specific", "TGJets"),
  ("nof_files",             1),
  ("nof_events",            364226),
  ("use_it",                True),
  ("xsection",              2.967000),
  ("genWeight",             True),
  ("triggers",              [ "1e", "1mu", "2e", "1e1mu", "2mu", "3e", "2e1mu", "1e2mu", "3mu", "1e1tau", "1mu1tau", "2tau" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/addMEM/2016/2017Mar17/final_ntuples_recopied/2lss_1tau/TGJets_TuneCUETP8M1_13TeV_amcatnlo_madspin_pythia8/VHBB_HEPPY_V25tthtautau_TGJets_TuneCUETP8M1_13TeV_amcatnlo_madspin_Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6-v1/170209_095835"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/TGJets_TuneCUETP8M1_13TeV_amcatnlo_madspin_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "Rares"),
  ("process_name_specific", "TGJets_ext1"),
  ("nof_files",             1),
  ("nof_events",            364226),
  ("use_it",                True),
  ("xsection",              2.967000),
  ("genWeight",             True),
  ("triggers",              [ "1e", "1mu", "2e", "1e1mu", "2mu", "3e", "2e1mu", "1e2mu", "3mu", "1e1tau", "1mu1tau", "2tau" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/addMEM/2016/2017Mar17/final_ntuples_recopied/2lss_1tau/TGJets_TuneCUETP8M1_13TeV_amcatnlo_madspin_pythia8/VHBB_HEPPY_V25tthtautau_TGJets_TuneCUETP8M1_13TeV_amcatnlo_madspin_Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6_ext1-v1/170207_123908"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/TTGJets_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "Rares"),
  ("process_name_specific", "TTGJets"),
  ("nof_files",             1),
  ("nof_events",            4743511),
  ("use_it",                True),
  ("xsection",              3.697000),
  ("genWeight",             True),
  ("triggers",              [ "1e", "1mu", "2e", "1e1mu", "2mu", "3e", "2e1mu", "1e2mu", "3mu", "1e1tau", "1mu1tau", "2tau" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/addMEM/2016/2017Mar17/final_ntuples_recopied/2lss_1tau/TTGJets_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/VHBB_HEPPY_V25tthtautau_TTGJets_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6-v1/170207_124053"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/TTGJets_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "Rares"),
  ("process_name_specific", "TTGJets_ext1"),
  ("nof_files",             1),
  ("nof_events",            4743511),
  ("use_it",                True),
  ("xsection",              3.697000),
  ("genWeight",             True),
  ("triggers",              [ "1e", "1mu", "2e", "1e1mu", "2mu", "3e", "2e1mu", "1e2mu", "3mu", "1e1tau", "1mu1tau", "2tau" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/addMEM/2016/2017Mar17/final_ntuples_recopied/2lss_1tau/TTGJets_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/VHBB_HEPPY_V25tthtautau_TTGJets_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6_ext1-v1/170208_120330"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/TTJets_DiLept_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "TT"),
  ("process_name_specific", "TTJets_DiLept"),
  ("nof_files",             1),
  ("nof_events",            30209063),
  ("use_it",                True),
  ("xsection",              87.300000),
  ("genWeight",             True),
  ("triggers",              [ "1e", "1mu", "2e", "1e1mu", "2mu", "3e", "2e1mu", "1e2mu", "3mu", "1e1tau", "1mu1tau", "2tau" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/addMEM/2016/2017Mar17/final_ntuples_recopied/2lss_1tau/TTJets_DiLept_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/VHBB_HEPPY_V25tthtautau_TTJets_DiLept_TuneCUETP8M1_13TeV-madgraphMLM-Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6-v1/170207_124244"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/TTJets_DiLept_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "TT"),
  ("process_name_specific", "TTJets_DiLept_ext1"),
  ("nof_files",             1),
  ("nof_events",            30209063),
  ("use_it",                True),
  ("xsection",              87.300000),
  ("genWeight",             True),
  ("triggers",              [ "1e", "1mu", "2e", "1e1mu", "2mu", "3e", "2e1mu", "1e2mu", "3mu", "1e1tau", "1mu1tau", "2tau" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/addMEM/2016/2017Mar17/final_ntuples_recopied/2lss_1tau/TTJets_DiLept_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/VHBB_HEPPY_V25tthtautau_TTJets_DiLept_TuneCUETP8M1_13TeV-madgraphMLM-Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6_ext1-v1/170207_124429"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/TTJets_SingleLeptFromT_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "TT"),
  ("process_name_specific", "TTJets_SingleLeptFromT"),
  ("nof_files",             1),
  ("nof_events",            61478697),
  ("use_it",                True),
  ("xsection",              182.180000),
  ("genWeight",             True),
  ("triggers",              [ "1e", "1mu", "2e", "1e1mu", "2mu", "3e", "2e1mu", "1e2mu", "3mu", "1e1tau", "1mu1tau", "2tau" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/addMEM/2016/2017Mar17/final_ntuples_recopied/2lss_1tau/TTJets_SingleLeptFromT_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/VHBB_HEPPY_V25tthtautau_TTJets_SingleLeptFromT_TuneCUETP8M1_13TeV-madgraphMLM-Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6-v1/170208_120534"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/TTJets_SingleLeptFromT_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "TT"),
  ("process_name_specific", "TTJets_SingleLeptFromT_ext1"),
  ("nof_files",             1),
  ("nof_events",            61478697),
  ("use_it",                True),
  ("xsection",              182.180000),
  ("genWeight",             True),
  ("triggers",              [ "1e", "1mu", "2e", "1e1mu", "2mu", "3e", "2e1mu", "1e2mu", "3mu", "1e1tau", "1mu1tau", "2tau" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/addMEM/2016/2017Mar17/final_ntuples_recopied/2lss_1tau/TTJets_SingleLeptFromT_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/VHBB_HEPPY_V25tthtautau_TTJets_SingleLeptFromT_TuneCUETP8M1_13TeV-madgraphMLM-Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6_ext1-v1/170208_120653"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/TTJets_SingleLeptFromTbar_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "TT"),
  ("process_name_specific", "TTJets_SingleLeptFromTbar"),
  ("nof_files",             1),
  ("nof_events",            60195937),
  ("use_it",                True),
  ("xsection",              182.180000),
  ("genWeight",             True),
  ("triggers",              [ "1e", "1mu", "2e", "1e1mu", "2mu", "3e", "2e1mu", "1e2mu", "3mu", "1e1tau", "1mu1tau", "2tau" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/addMEM/2016/2017Mar17/final_ntuples_recopied/2lss_1tau/TTJets_SingleLeptFromTbar_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/VHBB_HEPPY_V25tthtautau_TTJets_SingleLeptFromTbar_TuneCUETP8M1_13TeV-madgraphMLM-Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6-v1/170208_120816"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/TTTT_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "Rares"),
  ("process_name_specific", "TTTT"),
  ("nof_files",             1),
  ("nof_events",            104770),
  ("use_it",                True),
  ("xsection",              0.009103),
  ("genWeight",             True),
  ("triggers",              [ "1e", "1mu", "2e", "1e1mu", "2mu", "3e", "2e1mu", "1e2mu", "3mu", "1e1tau", "1mu1tau", "2tau" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/addMEM/2016/2017Mar17/final_ntuples_recopied/2lss_1tau/TTTT_TuneCUETP8M1_13TeV-amcatnlo-pythia8/VHBB_HEPPY_V25tthtautau_TTTT_TuneCUETP8M1_13TeV-amcatnlo-Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6-v1/170207_123853"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v3/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "TTW"),
  ("process_name_specific", "TTWJetsToLNu_ext1"),
  ("nof_files",             1),
  ("nof_events",            2701216),
  ("use_it",                True),
  ("xsection",              0.204300),
  ("genWeight",             True),
  ("triggers",              [ "1e", "1mu", "2e", "1e1mu", "2mu", "3e", "2e1mu", "1e2mu", "3mu", "1e1tau", "1mu1tau", "2tau" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/addMEM/2016/2017Mar17/final_ntuples_recopied/2lss_1tau/TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/VHBB_HEPPY_V25tthtautau_TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6_ext1-v3/170207_124033"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext2-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "TTW"),
  ("process_name_specific", "TTWJetsToLNu_ext2"),
  ("nof_files",             1),
  ("nof_events",            2701216),
  ("use_it",                True),
  ("xsection",              0.204300),
  ("genWeight",             True),
  ("triggers",              [ "1e", "1mu", "2e", "1e1mu", "2mu", "3e", "2e1mu", "1e2mu", "3mu", "1e1tau", "1mu1tau", "2tau" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/addMEM/2016/2017Mar17/final_ntuples_recopied/2lss_1tau/TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/VHBB_HEPPY_V25tthtautau_TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6_ext2-v1/170207_124213"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "TTZ"),
  ("process_name_specific", "TTZToLL_M10_ext1"),
  ("nof_files",             1),
  ("nof_events",            3686150),
  ("use_it",                True),
  ("xsection",              0.252900),
  ("genWeight",             True),
  ("triggers",              [ "1e", "1mu", "2e", "1e1mu", "2mu", "3e", "2e1mu", "1e2mu", "3mu", "1e1tau", "1mu1tau", "2tau" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/addMEM/2016/2017Mar17/final_ntuples_recopied/2lss_1tau/TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-pythia8/VHBB_HEPPY_V25tthtautau_TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6_ext1-v1/170207_124540"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext2-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "TTZ"),
  ("process_name_specific", "TTZToLL_M10_ext2"),
  ("nof_files",             1),
  ("nof_events",            3686150),
  ("use_it",                True),
  ("xsection",              0.252900),
  ("genWeight",             True),
  ("triggers",              [ "1e", "1mu", "2e", "1e1mu", "2mu", "3e", "2e1mu", "1e2mu", "3mu", "1e1tau", "1mu1tau", "2tau" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/addMEM/2016/2017Mar17/final_ntuples_recopied/2lss_1tau/TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-pythia8/VHBB_HEPPY_V25tthtautau_TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6_ext2-v1/170207_124710"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/TTZToLL_M-1to10_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "TTZ"),
  ("process_name_specific", "TTZToLL_M-1to10"),
  ("nof_files",             1),
  ("nof_events",            246798),
  ("use_it",                True),
  ("xsection",              0.049300),
  ("genWeight",             True),
  ("triggers",              [ "1e", "1mu", "2e", "1e1mu", "2mu", "3e", "2e1mu", "1e2mu", "3mu", "1e1tau", "1mu1tau", "2tau" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/addMEM/2016/2017Mar17/final_ntuples_recopied/2lss_1tau/TTZToLL_M-1to10_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/VHBB_HEPPY_V25tthtautau_TTZToLL_M-1to10_TuneCUETP8M1_13TeV-madgraphMLM-Py8__RunIISummer16MAv2-80r2as_2016_TrancheIV_v6-v1/170207_124356"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/Tau/Run2016H-PromptReco-v3/MINIAOD"] = OD([
  ("type",                  "data"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "Tau_Run2016H_v3_promptReco"),
  ("nof_files",             1),
  ("nof_events",            1898072),
  ("use_HIP_mitigation_bTag", False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                True),
  ("triggers",              [ "1e1tau", "1mu1tau", "2tau" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/addMEM/2016/2017Mar17/final_ntuples_recopied/2lss_1tau/Tau/VHBB_HEPPY_V25tthtautau_Tau__Run2016H-PromptReco-v3/170215_145334"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/WGToLNuG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "Rares"),
  ("process_name_specific", "WGToLNuG_ext1"),
  ("nof_files",             1),
  ("nof_events",            9651890),
  ("use_it",                True),
  ("xsection",              585.800000),
  ("genWeight",             True),
  ("triggers",              [ "1e", "1mu", "2e", "1e1mu", "2mu", "3e", "2e1mu", "1e2mu", "3mu", "1e1tau", "1mu1tau", "2tau" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/addMEM/2016/2017Mar17/final_ntuples_recopied/2lss_1tau/WGToLNuG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/VHBB_HEPPY_V25tthtautau_WGToLNuG_TuneCUETP8M1_13TeV-amcatnloFXFX-Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6_ext1-v1/170208_121122"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/WGToLNuG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext2-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "Rares"),
  ("process_name_specific", "WGToLNuG_ext2"),
  ("nof_files",             1),
  ("nof_events",            9651890),
  ("use_it",                True),
  ("xsection",              585.800000),
  ("genWeight",             True),
  ("triggers",              [ "1e", "1mu", "2e", "1e1mu", "2mu", "3e", "2e1mu", "1e2mu", "3mu", "1e1tau", "1mu1tau", "2tau" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/addMEM/2016/2017Mar17/final_ntuples_recopied/2lss_1tau/WGToLNuG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/VHBB_HEPPY_V25tthtautau_WGToLNuG_TuneCUETP8M1_13TeV-amcatnloFXFX-Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6_ext2-v1/170208_121305"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/WJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "EWK"),
  ("process_name_specific", "WJetsToLNu"),
  ("nof_files",             1),
  ("nof_events",            16484091),
  ("use_it",                True),
  ("xsection",              61526.700000),
  ("genWeight",             True),
  ("triggers",              [ "1e", "1mu", "2e", "1e1mu", "2mu", "3e", "2e1mu", "1e2mu", "3mu", "1e1tau", "1mu1tau", "2tau" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/addMEM/2016/2017Mar17/final_ntuples_recopied/2lss_1tau/WJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/VHBB_HEPPY_V25tthtautau_WJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6-v1/170208_121448"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/WWTo2L2Nu_13TeV-powheg/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "EWK"),
  ("process_name_specific", "WWTo2L2Nu"),
  ("nof_files",             1),
  ("nof_events",            1999193),
  ("use_it",                True),
  ("xsection",              10.481000),
  ("genWeight",             True),
  ("triggers",              [ "1e", "1mu", "2e", "1e1mu", "2mu", "3e", "2e1mu", "1e2mu", "3mu", "1e1tau", "1mu1tau", "2tau" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/addMEM/2016/2017Mar17/final_ntuples_recopied/2lss_1tau/WWTo2L2Nu_13TeV-powheg/VHBB_HEPPY_V25tthtautau_WWTo2L2Nu_13TeV-powheg__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6-v1/170207_134602"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/WWTo2L2Nu_DoubleScattering_13TeV-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "Rares"),
  ("process_name_specific", "WWTo2L2Nu_DoubleScattering"),
  ("nof_files",             1),
  ("nof_events",            999361),
  ("use_it",                True),
  ("xsection",              0.172900),
  ("genWeight",             True),
  ("triggers",              [ "1e", "1mu", "2e", "1e1mu", "2mu", "3e", "2e1mu", "1e2mu", "3mu", "1e1tau", "1mu1tau", "2tau" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/addMEM/2016/2017Mar17/final_ntuples_recopied/2lss_1tau/WWTo2L2Nu_DoubleScattering_13TeV-pythia8/VHBB_HEPPY_V25tthtautau_WWTo2L2Nu_DoubleScattering_13TeV-Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6-v1/170207_134843"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/WWW_4F_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "Rares"),
  ("process_name_specific", "WWW_4F"),
  ("nof_files",             1),
  ("nof_events",            210465),
  ("use_it",                True),
  ("xsection",              0.208600),
  ("genWeight",             True),
  ("triggers",              [ "1e", "1mu", "2e", "1e1mu", "2mu", "3e", "2e1mu", "1e2mu", "3mu", "1e1tau", "1mu1tau", "2tau" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/addMEM/2016/2017Mar17/final_ntuples_recopied/2lss_1tau/WWW_4F_TuneCUETP8M1_13TeV-amcatnlo-pythia8/VHBB_HEPPY_V25tthtautau_WWW_4F_TuneCUETP8M1_13TeV-amcatnlo-Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6-v1/170207_135107"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/WWZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "Rares"),
  ("process_name_specific", "WWZ"),
  ("nof_files",             1),
  ("nof_events",            221511),
  ("use_it",                True),
  ("xsection",              0.165100),
  ("genWeight",             True),
  ("triggers",              [ "1e", "1mu", "2e", "1e1mu", "2mu", "3e", "2e1mu", "1e2mu", "3mu", "1e1tau", "1mu1tau", "2tau" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/addMEM/2016/2017Mar17/final_ntuples_recopied/2lss_1tau/WWZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8/VHBB_HEPPY_V25tthtautau_WWZ_TuneCUETP8M1_13TeV-amcatnlo-Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6-v1/170207_135405"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/WZTo3LNu_TuneCUETP8M1_13TeV-powheg-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "EWK"),
  ("process_name_specific", "WZTo3LNu"),
  ("nof_files",             1),
  ("nof_events",            1993307),
  ("use_it",                True),
  ("xsection",              4.429650),
  ("genWeight",             True),
  ("triggers",              [ "1e", "1mu", "2e", "1e1mu", "2mu", "3e", "2e1mu", "1e2mu", "3mu", "1e1tau", "1mu1tau", "2tau" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/addMEM/2016/2017Mar17/final_ntuples_recopied/2lss_1tau/WZTo3LNu_TuneCUETP8M1_13TeV-powheg-pythia8/VHBB_HEPPY_V25tthtautau_WZTo3LNu_TuneCUETP8M1_13TeV-powheg-Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6-v1/170207_124837"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/WZZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "Rares"),
  ("process_name_specific", "WZZ"),
  ("nof_files",             1),
  ("nof_events",            216296),
  ("use_it",                True),
  ("xsection",              0.055650),
  ("genWeight",             True),
  ("triggers",              [ "1e", "1mu", "2e", "1e1mu", "2mu", "3e", "2e1mu", "1e2mu", "3mu", "1e1tau", "1mu1tau", "2tau" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/addMEM/2016/2017Mar17/final_ntuples_recopied/2lss_1tau/WZZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8/VHBB_HEPPY_V25tthtautau_WZZ_TuneCUETP8M1_13TeV-amcatnlo-Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6-v1/170207_125000"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/WpWpJJ_EWK-QCD_TuneCUETP8M1_13TeV-madgraph-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "Rares"),
  ("process_name_specific", "WpWpJJ_EWK-QCD"),
  ("nof_files",             1),
  ("nof_events",            149601),
  ("use_it",                True),
  ("xsection",              0.037110),
  ("genWeight",             True),
  ("triggers",              [ "1e", "1mu", "2e", "1e1mu", "2mu", "3e", "2e1mu", "1e2mu", "3mu", "1e1tau", "1mu1tau", "2tau" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/addMEM/2016/2017Mar17/final_ntuples_recopied/2lss_1tau/WpWpJJ_EWK-QCD_TuneCUETP8M1_13TeV-madgraph-pythia8/VHBB_HEPPY_V25tthtautau_WpWpJJ_EWK-QCD_TuneCUETP8M1_13TeV-madgraph-Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6-v1/170207_125131"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "Rares"),
  ("process_name_specific", "ZGTo2LG"),
  ("nof_files",             1),
  ("nof_events",            9243007),
  ("use_it",                True),
  ("xsection",              131.300000),
  ("genWeight",             True),
  ("triggers",              [ "1e", "1mu", "2e", "1e1mu", "2mu", "3e", "2e1mu", "1e2mu", "3mu", "1e1tau", "1mu1tau", "2tau" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/addMEM/2016/2017Mar17/final_ntuples_recopied/2lss_1tau/ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/VHBB_HEPPY_V25tthtautau_ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6_ext1-v1/170207_124611"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/ZZTo4L_13TeV_powheg_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "EWK"),
  ("process_name_specific", "ZZTo4L"),
  ("nof_files",             1),
  ("nof_events",            6611208),
  ("use_it",                True),
  ("xsection",              1.256000),
  ("genWeight",             True),
  ("triggers",              [ "1e", "1mu", "2e", "1e1mu", "2mu", "3e", "2e1mu", "1e2mu", "3mu", "1e1tau", "1mu1tau", "2tau" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/addMEM/2016/2017Mar17/final_ntuples_recopied/2lss_1tau/ZZTo4L_13TeV_powheg_pythia8/VHBB_HEPPY_V25tthtautau_ZZTo4L_13TeV_powheg_Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6-v1/170207_125252"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/ZZZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "Rares"),
  ("process_name_specific", "ZZZ"),
  ("nof_files",             1),
  ("nof_events",            213100),
  ("use_it",                True),
  ("xsection",              0.013980),
  ("genWeight",             True),
  ("triggers",              [ "1e", "1mu", "2e", "1e1mu", "2mu", "3e", "2e1mu", "1e2mu", "3mu", "1e1tau", "1mu1tau", "2tau" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/addMEM/2016/2017Mar17/final_ntuples_recopied/2lss_1tau/ZZZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8/VHBB_HEPPY_V25tthtautau_ZZZ_TuneCUETP8M1_13TeV-amcatnlo-Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6-v1/170207_125415"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/tZq_ll_4f_13TeV-amcatnlo-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "Rares"),
  ("process_name_specific", "tZq_ll_4f"),
  ("nof_files",             1),
  ("nof_events",            3806636),
  ("use_it",                True),
  ("xsection",              0.075800),
  ("genWeight",             True),
  ("triggers",              [ "1e", "1mu", "2e", "1e1mu", "2mu", "3e", "2e1mu", "1e2mu", "3mu", "1e1tau", "1mu1tau", "2tau" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/addMEM/2016/2017Mar17/final_ntuples_recopied/2lss_1tau/tZq_ll_4f_13TeV-amcatnlo-pythia8/VHBB_HEPPY_V25tthtautau_tZq_ll_4f_13TeV-amcatnlo-Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6_ext1-v1/170208_121616"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "signal"),
  ("process_name_specific", "ttHJetToNonbb_M125_amcatnlo"),
  ("nof_files",             1),
  ("nof_events",            2970052),
  ("use_it",                True),
  ("xsection",              0.215100),
  ("genWeight",             True),
  ("triggers",              [ "1e", "1mu", "2e", "1e1mu", "2mu", "3e", "2e1mu", "1e2mu", "3mu", "1e1tau", "1mu1tau", "2tau" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/addMEM/2016/2017Mar17/final_ntuples_recopied/2lss_1tau/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/VHBB_HEPPY_V25tthtautau_ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_Py8_mWCutfix__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6_ext1-v1/170207_122849"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/DoubleEG/Run2016C-23Sep2016-v1/MINIAOD"] = OD([
  ("type",                  "data"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "DoubleEG_Run2016C_v1"),
  ("nof_files",             1),
  ("nof_events",            47677856),
  ("use_HIP_mitigation_bTag", True),
  ("use_HIP_mitigation_mediumMuonId", True),
  ("use_it",                True),
  ("triggers",              [ "2e", "3e" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/addMEM/2016/2017Mar17/final_ntuples_recopied/2lss_1tau/DoubleEG/VHBB_HEPPY_V25tthtautau_v2_DoubleEG__Run2016C-23Sep2016-v1/170219_194332"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/DoubleEG/Run2016D-23Sep2016-v1/MINIAOD"] = OD([
  ("type",                  "data"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "DoubleEG_Run2016D_v1"),
  ("nof_files",             1),
  ("nof_events",            53324960),
  ("use_HIP_mitigation_bTag", True),
  ("use_HIP_mitigation_mediumMuonId", True),
  ("use_it",                True),
  ("triggers",              [ "2e", "3e" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/addMEM/2016/2017Mar17/final_ntuples_recopied/2lss_1tau/DoubleEG/VHBB_HEPPY_V25tthtautau_v2_DoubleEG__Run2016D-23Sep2016-v1/170218_171438"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/DoubleEG/Run2016E-23Sep2016-v1/MINIAOD"] = OD([
  ("type",                  "data"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "DoubleEG_Run2016E_v1"),
  ("nof_files",             1),
  ("nof_events",            49877712),
  ("use_HIP_mitigation_bTag", True),
  ("use_HIP_mitigation_mediumMuonId", True),
  ("use_it",                True),
  ("triggers",              [ "2e", "3e" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/addMEM/2016/2017Mar17/final_ntuples_recopied/2lss_1tau/DoubleEG/VHBB_HEPPY_V25tthtautau_v2_DoubleEG__Run2016E-23Sep2016-v1/170218_171718"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/DoubleEG/Run2016F-23Sep2016-v1/MINIAOD"] = OD([
  ("type",                  "data"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "DoubleEG_Run2016F_v1"),
  ("nof_files",             1),
  ("nof_events",            34577624),
  ("use_HIP_mitigation_bTag", True),
  ("use_HIP_mitigation_mediumMuonId", True),
  ("use_it",                True),
  ("triggers",              [ "2e", "3e" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/addMEM/2016/2017Mar17/final_ntuples_recopied/2lss_1tau/DoubleEG/VHBB_HEPPY_V25tthtautau_v2_DoubleEG__Run2016F-23Sep2016-v1/170218_180254"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/DoubleEG/Run2016G-23Sep2016-v1/MINIAOD"] = OD([
  ("type",                  "data"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "DoubleEG_Run2016G_v1"),
  ("nof_files",             1),
  ("nof_events",            78797040),
  ("use_HIP_mitigation_bTag", False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                True),
  ("triggers",              [ "2e", "3e" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/addMEM/2016/2017Mar17/final_ntuples_recopied/2lss_1tau/DoubleEG/VHBB_HEPPY_V25tthtautau_v2_DoubleEG__Run2016G-23Sep2016-v1/170218_172915"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/DoubleMuon/Run2016B-23Sep2016-v3/MINIAOD"] = OD([
  ("type",                  "data"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "DoubleMuon_Run2016B_v3"),
  ("nof_files",             1),
  ("nof_events",            82535520),
  ("use_HIP_mitigation_bTag", True),
  ("use_HIP_mitigation_mediumMuonId", True),
  ("use_it",                True),
  ("triggers",              [ "2mu", "3mu" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/addMEM/2016/2017Mar17/final_ntuples_recopied/2lss_1tau/DoubleMuon/VHBB_HEPPY_V25tthtautau_v2_DoubleMuon__Run2016B-23Sep2016-v3/170218_175649"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/DoubleMuon/Run2016C-23Sep2016-v1/MINIAOD"] = OD([
  ("type",                  "data"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "DoubleMuon_Run2016C_v1"),
  ("nof_files",             1),
  ("nof_events",            27934630),
  ("use_HIP_mitigation_bTag", True),
  ("use_HIP_mitigation_mediumMuonId", True),
  ("use_it",                True),
  ("triggers",              [ "2mu", "3mu" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/addMEM/2016/2017Mar17/final_ntuples_recopied/2lss_1tau/DoubleMuon/VHBB_HEPPY_V25tthtautau_v2_DoubleMuon__Run2016C-23Sep2016-v1/170218_171035"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/DoubleMuon/Run2016D-23Sep2016-v1/MINIAOD"] = OD([
  ("type",                  "data"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "DoubleMuon_Run2016D_v1"),
  ("nof_files",             1),
  ("nof_events",            33861744),
  ("use_HIP_mitigation_bTag", True),
  ("use_HIP_mitigation_mediumMuonId", True),
  ("use_it",                True),
  ("triggers",              [ "2mu", "3mu" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/addMEM/2016/2017Mar17/final_ntuples_recopied/2lss_1tau/DoubleMuon/VHBB_HEPPY_V25tthtautau_v2_DoubleMuon__Run2016D-23Sep2016-v1/170218_171554"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/DoubleMuon/Run2016E-23Sep2016-v1/MINIAOD"] = OD([
  ("type",                  "data"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "DoubleMuon_Run2016E_v1"),
  ("nof_files",             1),
  ("nof_events",            28246946),
  ("use_HIP_mitigation_bTag", True),
  ("use_HIP_mitigation_mediumMuonId", True),
  ("use_it",                True),
  ("triggers",              [ "2mu", "3mu" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/addMEM/2016/2017Mar17/final_ntuples_recopied/2lss_1tau/DoubleMuon/VHBB_HEPPY_V25tthtautau_v2_DoubleMuon__Run2016E-23Sep2016-v1/170218_180126"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/DoubleMuon/Run2016F-23Sep2016-v1/MINIAOD"] = OD([
  ("type",                  "data"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "DoubleMuon_Run2016F_v1"),
  ("nof_files",             1),
  ("nof_events",            20329920),
  ("use_HIP_mitigation_bTag", True),
  ("use_HIP_mitigation_mediumMuonId", True),
  ("use_it",                True),
  ("triggers",              [ "2mu", "3mu" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/addMEM/2016/2017Mar17/final_ntuples_recopied/2lss_1tau/DoubleMuon/VHBB_HEPPY_V25tthtautau_v2_DoubleMuon__Run2016F-23Sep2016-v1/170217_152817"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/DoubleMuon/Run2016G-23Sep2016-v1/MINIAOD"] = OD([
  ("type",                  "data"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "DoubleMuon_Run2016G_v1"),
  ("nof_files",             1),
  ("nof_events",            45235604),
  ("use_HIP_mitigation_bTag", False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                True),
  ("triggers",              [ "2mu", "3mu" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/addMEM/2016/2017Mar17/final_ntuples_recopied/2lss_1tau/DoubleMuon/VHBB_HEPPY_V25tthtautau_v2_DoubleMuon__Run2016G-23Sep2016-v1/170217_151055"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/MuonEG/Run2016B-23Sep2016-v3/MINIAOD"] = OD([
  ("type",                  "data"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "MuonEG_Run2016B_v3"),
  ("nof_files",             1),
  ("nof_events",            32727796),
  ("use_HIP_mitigation_bTag", True),
  ("use_HIP_mitigation_mediumMuonId", True),
  ("use_it",                True),
  ("triggers",              [ "1e1mu", "2e1mu", "1e2mu" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/addMEM/2016/2017Mar17/final_ntuples_recopied/2lss_1tau/MuonEG/VHBB_HEPPY_V25tthtautau_v2_MuonEG__Run2016B-23Sep2016-v3/170218_175920"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/MuonEG/Run2016C-23Sep2016-v1/MINIAOD"] = OD([
  ("type",                  "data"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "MuonEG_Run2016C_v1"),
  ("nof_files",             1),
  ("nof_events",            15405678),
  ("use_HIP_mitigation_bTag", True),
  ("use_HIP_mitigation_mediumMuonId", True),
  ("use_it",                True),
  ("triggers",              [ "1e1mu", "2e1mu", "1e2mu" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/addMEM/2016/2017Mar17/final_ntuples_recopied/2lss_1tau/MuonEG/VHBB_HEPPY_V25tthtautau_v2_MuonEG__Run2016C-23Sep2016-v1/170218_170759"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/MuonEG/Run2016E-23Sep2016-v1/MINIAOD"] = OD([
  ("type",                  "data"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "MuonEG_Run2016E_v1"),
  ("nof_files",             1),
  ("nof_events",            22519304),
  ("use_HIP_mitigation_bTag", True),
  ("use_HIP_mitigation_mediumMuonId", True),
  ("use_it",                True),
  ("triggers",              [ "1e1mu", "2e1mu", "1e2mu" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/addMEM/2016/2017Mar17/final_ntuples_recopied/2lss_1tau/MuonEG/VHBB_HEPPY_V25tthtautau_v2_MuonEG__Run2016E-23Sep2016-v1/170218_172335"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/MuonEG/Run2016F-23Sep2016-v1/MINIAOD"] = OD([
  ("type",                  "data"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "MuonEG_Run2016F_v1"),
  ("nof_files",             1),
  ("nof_events",            16002165),
  ("use_HIP_mitigation_bTag", True),
  ("use_HIP_mitigation_mediumMuonId", True),
  ("use_it",                True),
  ("triggers",              [ "1e1mu", "2e1mu", "1e2mu" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/addMEM/2016/2017Mar17/final_ntuples_recopied/2lss_1tau/MuonEG/VHBB_HEPPY_V25tthtautau_v2_MuonEG__Run2016F-23Sep2016-v1/170218_182854"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/MuonEG/Run2016G-23Sep2016-v1/MINIAOD"] = OD([
  ("type",                  "data"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "MuonEG_Run2016G_v1"),
  ("nof_files",             1),
  ("nof_events",            33854612),
  ("use_HIP_mitigation_bTag", False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                True),
  ("triggers",              [ "1e1mu", "2e1mu", "1e2mu" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/addMEM/2016/2017Mar17/final_ntuples_recopied/2lss_1tau/MuonEG/VHBB_HEPPY_V25tthtautau_v2_MuonEG__Run2016G-23Sep2016-v1/170218_172759"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/SingleElectron/Run2016F-23Sep2016-v1/MINIAOD"] = OD([
  ("type",                  "data"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "SingleElectron_Run2016F_v1"),
  ("nof_files",             1),
  ("nof_events",            70593528),
  ("use_HIP_mitigation_bTag", True),
  ("use_HIP_mitigation_mediumMuonId", True),
  ("use_it",                True),
  ("triggers",              [ "1e" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/addMEM/2016/2017Mar17/final_ntuples_recopied/2lss_1tau/SingleElectron/VHBB_HEPPY_V25tthtautau_v2_SingleElectron__Run2016F-23Sep2016-v1/170218_172629"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/SingleElectron/Run2016G-23Sep2016-v1/MINIAOD"] = OD([
  ("type",                  "data"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "SingleElectron_Run2016G_v1"),
  ("nof_files",             1),
  ("nof_events",            153232800),
  ("use_HIP_mitigation_bTag", False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                True),
  ("triggers",              [ "1e" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/addMEM/2016/2017Mar17/final_ntuples_recopied/2lss_1tau/SingleElectron/VHBB_HEPPY_V25tthtautau_v2_SingleElectron__Run2016G-23Sep2016-v1/170217_150830"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/SingleMuon/Run2016D-23Sep2016-v1/MINIAOD"] = OD([
  ("type",                  "data"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "SingleMuon_Run2016D_v1"),
  ("nof_files",             1),
  ("nof_events",            98017992),
  ("use_HIP_mitigation_bTag", True),
  ("use_HIP_mitigation_mediumMuonId", True),
  ("use_it",                True),
  ("triggers",              [ "1mu" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/addMEM/2016/2017Mar17/final_ntuples_recopied/2lss_1tau/SingleMuon/VHBB_HEPPY_V25tthtautau_v2_SingleMuon__Run2016D-23Sep2016-v1/170218_171316"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/SingleMuon/Run2016F-23Sep2016-v1/MINIAOD"] = OD([
  ("type",                  "data"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "SingleMuon_Run2016F_v1"),
  ("nof_files",             1),
  ("nof_events",            65489556),
  ("use_HIP_mitigation_bTag", True),
  ("use_HIP_mitigation_mediumMuonId", True),
  ("use_it",                True),
  ("triggers",              [ "1mu" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/addMEM/2016/2017Mar17/final_ntuples_recopied/2lss_1tau/SingleMuon/VHBB_HEPPY_V25tthtautau_v2_SingleMuon__Run2016F-23Sep2016-v1/170217_153044"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/SingleMuon/Run2016G-23Sep2016-v1/MINIAOD"] = OD([
  ("type",                  "data"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "SingleMuon_Run2016G_v1"),
  ("nof_files",             1),
  ("nof_events",            149916848),
  ("use_HIP_mitigation_bTag", False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                True),
  ("triggers",              [ "1mu" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/addMEM/2016/2017Mar17/final_ntuples_recopied/2lss_1tau/SingleMuon/VHBB_HEPPY_V25tthtautau_v2_SingleMuon__Run2016G-23Sep2016-v1/170217_151611"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/TTJets_SingleLeptFromTbar_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "TT"),
  ("process_name_specific", "TTJets_SingleLeptFromTbar_ext1"),
  ("nof_files",             1),
  ("nof_events",            60195937),
  ("use_it",                True),
  ("xsection",              182.180000),
  ("genWeight",             True),
  ("triggers",              [ "1e", "1mu", "2e", "1e1mu", "2mu", "3e", "2e1mu", "1e2mu", "3mu", "1e1tau", "1mu1tau", "2tau" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/addMEM/2016/2017Mar17/final_ntuples_recopied/2lss_1tau/TTJets_SingleLeptFromTbar_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/VHBB_HEPPY_V25tthtautau_v2_TTJets_SingleLeptFromTbar_TuneCUETP8M1_13TeV-madgraphMLM-Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6_ext1-v1/170217_230025"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/Tau/Run2016G-23Sep2016-v1/MINIAOD"] = OD([
  ("type",                  "data"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "Tau_Run2016G_v1"),
  ("nof_files",             1),
  ("nof_events",            79578656),
  ("use_HIP_mitigation_bTag", False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                True),
  ("triggers",              [ "1e1tau", "1mu1tau", "2tau" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/addMEM/2016/2017Mar17/final_ntuples_recopied/2lss_1tau/Tau/VHBB_HEPPY_V25tthtautau_v2_Tau__Run2016G-23Sep2016-v1/170218_173036"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/ttHJetTobb_M125_13TeV_amcatnloFXFX_madspin_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext3-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "ttH_hbb"),
  ("process_name_specific", "ttHJetTobb_M125"),
  ("nof_files",             1),
  ("nof_events",            2910427),
  ("use_it",                True),
  ("xsection",              0.293400),
  ("genWeight",             True),
  ("triggers",              [ "1e", "1mu", "2e", "1e1mu", "2mu", "3e", "2e1mu", "1e2mu", "3mu", "1e1tau", "1mu1tau", "2tau" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/addMEM/2016/2017Mar17/final_ntuples_recopied/2lss_1tau/ttHJetTobb_M125_13TeV_amcatnloFXFX_madspin_pythia8/VHBB_HEPPY_V25tthtautau_v2_ttHJetTobb_M125_13TeV_amcatnloFXFX_madspin_Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6_ext3-v1/170217_224718"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DYJetsToLL_M-10to50"),
  ("nof_files",             1),
  ("nof_events",            35253280),
  ("use_it",                True),
  ("xsection",              18610.000000),
  ("genWeight",             True),
  ("triggers",              [ "1e", "1mu", "2e", "1e1mu", "2mu", "3e", "2e1mu", "1e2mu", "3mu", "1e1tau", "1mu1tau", "2tau" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/addMEM/2016/2017Mar17/final_ntuples_recopied/2lss_1tau/DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/VHBB_HEPPY_V25tthtautau_v3_DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-madgraphMLM-Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6-v1/170225_232933"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext2-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DYJetsToLL_M-50"),
  ("nof_files",             1),
  ("nof_events",            94931120),
  ("use_it",                True),
  ("xsection",              6025.200000),
  ("genWeight",             True),
  ("triggers",              [ "1e", "1mu", "2e", "1e1mu", "2mu", "3e", "2e1mu", "1e2mu", "3mu", "1e1tau", "1mu1tau", "2tau" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/addMEM/2016/2017Mar17/final_ntuples_recopied/2lss_1tau/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/VHBB_HEPPY_V25tthtautau_v3_DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6_ext2-v1/170225_232809"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/DoubleEG/Run2016H-PromptReco-v3/MINIAOD"] = OD([
  ("type",                  "data"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "DoubleEG_Run2016H_v3_promptReco"),
  ("nof_files",             1),
  ("nof_events",            2146647),
  ("use_HIP_mitigation_bTag", False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                True),
  ("triggers",              [ "2e", "3e" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/addMEM/2016/2017Mar17/final_ntuples_recopied/2lss_1tau/DoubleEG/VHBB_HEPPY_V25tthtautau_v3_DoubleEG__Run2016H-PromptReco-v3/170221_105758"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/DoubleMuon/Run2016H-PromptReco-v3/MINIAOD"] = OD([
  ("type",                  "data"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "DoubleMuon_Run2016H_v3_promptReco"),
  ("nof_files",             1),
  ("nof_events",            1219733),
  ("use_HIP_mitigation_bTag", False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                True),
  ("triggers",              [ "2mu", "3mu" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/addMEM/2016/2017Mar17/final_ntuples_recopied/2lss_1tau/DoubleMuon/VHBB_HEPPY_V25tthtautau_v3_DoubleMuon__Run2016H-PromptReco-v3/170221_214504"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/MuonEG/Run2016H-PromptReco-v2/MINIAOD"] = OD([
  ("type",                  "data"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "MuonEG_Run2016H_v2_promptReco"),
  ("nof_files",             1),
  ("nof_events",            28705852),
  ("use_HIP_mitigation_bTag", False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                True),
  ("triggers",              [ "1e1mu", "2e1mu", "1e2mu" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/addMEM/2016/2017Mar17/final_ntuples_recopied/2lss_1tau/MuonEG/VHBB_HEPPY_V25tthtautau_v3_MuonEG__Run2016H-PromptReco-v2/170221_150405"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/SingleElectron/Run2016B-23Sep2016-v3/MINIAOD"] = OD([
  ("type",                  "data"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "SingleElectron_Run2016B_v3"),
  ("nof_files",             1),
  ("nof_events",            246440448),
  ("use_HIP_mitigation_bTag", True),
  ("use_HIP_mitigation_mediumMuonId", True),
  ("use_it",                True),
  ("triggers",              [ "1e" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/addMEM/2016/2017Mar17/final_ntuples_recopied/2lss_1tau/SingleElectron/VHBB_HEPPY_V25tthtautau_v3_SingleElectron__Run2016B-23Sep2016-v3/170220_170550"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/SingleElectron/Run2016C-23Sep2016-v1/MINIAOD"] = OD([
  ("type",                  "data"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "SingleElectron_Run2016C_v1"),
  ("nof_files",             1),
  ("nof_events",            97259848),
  ("use_HIP_mitigation_bTag", True),
  ("use_HIP_mitigation_mediumMuonId", True),
  ("use_it",                True),
  ("triggers",              [ "1e" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/addMEM/2016/2017Mar17/final_ntuples_recopied/2lss_1tau/SingleElectron/VHBB_HEPPY_V25tthtautau_v3_SingleElectron__Run2016C-23Sep2016-v1/170220_170950"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/SingleElectron/Run2016D-23Sep2016-v1/MINIAOD"] = OD([
  ("type",                  "data"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "SingleElectron_Run2016D_v1"),
  ("nof_files",             1),
  ("nof_events",            148167728),
  ("use_HIP_mitigation_bTag", True),
  ("use_HIP_mitigation_mediumMuonId", True),
  ("use_it",                True),
  ("triggers",              [ "1e" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/addMEM/2016/2017Mar17/final_ntuples_recopied/2lss_1tau/SingleElectron/VHBB_HEPPY_V25tthtautau_v3_SingleElectron__Run2016D-23Sep2016-v1/170220_171118"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/SingleElectron/Run2016E-23Sep2016-v1/MINIAOD"] = OD([
  ("type",                  "data"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "SingleElectron_Run2016E_v1"),
  ("nof_files",             1),
  ("nof_events",            117321544),
  ("use_HIP_mitigation_bTag", True),
  ("use_HIP_mitigation_mediumMuonId", True),
  ("use_it",                True),
  ("triggers",              [ "1e" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/addMEM/2016/2017Mar17/final_ntuples_recopied/2lss_1tau/SingleElectron/VHBB_HEPPY_V25tthtautau_v3_SingleElectron__Run2016E-23Sep2016-v1/170220_171247"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/SingleElectron/Run2016H-PromptReco-v3/MINIAOD"] = OD([
  ("type",                  "data"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "SingleElectron_Run2016H_v3_promptReco"),
  ("nof_files",             1),
  ("nof_events",            3191585),
  ("use_HIP_mitigation_bTag", False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                True),
  ("triggers",              [ "1e" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/addMEM/2016/2017Mar17/final_ntuples_recopied/2lss_1tau/SingleElectron/VHBB_HEPPY_V25tthtautau_v3_SingleElectron__Run2016H-PromptReco-v3/170222_145637"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/SingleMuon/Run2016B-23Sep2016-v3/MINIAOD"] = OD([
  ("type",                  "data"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "SingleMuon_Run2016B_v3"),
  ("nof_files",             1),
  ("nof_events",            158145728),
  ("use_HIP_mitigation_bTag", True),
  ("use_HIP_mitigation_mediumMuonId", True),
  ("use_it",                True),
  ("triggers",              [ "1mu" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/addMEM/2016/2017Mar17/final_ntuples_recopied/2lss_1tau/SingleMuon/VHBB_HEPPY_V25tthtautau_v3_SingleMuon__Run2016B-23Sep2016-v3/170220_170831"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/SingleMuon/Run2016C-23Sep2016-v1/MINIAOD"] = OD([
  ("type",                  "data"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "SingleMuon_Run2016C_v1"),
  ("nof_files",             1),
  ("nof_events",            67441312),
  ("use_HIP_mitigation_bTag", True),
  ("use_HIP_mitigation_mediumMuonId", True),
  ("use_it",                True),
  ("triggers",              [ "1mu" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/addMEM/2016/2017Mar17/final_ntuples_recopied/2lss_1tau/SingleMuon/VHBB_HEPPY_V25tthtautau_v3_SingleMuon__Run2016C-23Sep2016-v1/170221_173556"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/SingleMuon/Run2016E-23Sep2016-v1/MINIAOD"] = OD([
  ("type",                  "data"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "SingleMuon_Run2016E_v1"),
  ("nof_files",             1),
  ("nof_events",            90984720),
  ("use_HIP_mitigation_bTag", True),
  ("use_HIP_mitigation_mediumMuonId", True),
  ("use_it",                True),
  ("triggers",              [ "1mu" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/addMEM/2016/2017Mar17/final_ntuples_recopied/2lss_1tau/SingleMuon/VHBB_HEPPY_V25tthtautau_v3_SingleMuon__Run2016E-23Sep2016-v1/170220_170712"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/Tau/Run2016H-PromptReco-v2/MINIAOD"] = OD([
  ("type",                  "data"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "Tau_Run2016H_v2_promptReco"),
  ("nof_files",             1),
  ("nof_events",            76504272),
  ("use_HIP_mitigation_bTag", False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                True),
  ("triggers",              [ "1e1tau", "1mu1tau", "2tau" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/addMEM/2016/2017Mar17/final_ntuples_recopied/2lss_1tau/Tau/VHBB_HEPPY_V25tthtautau_v3_Tau__Run2016H-PromptReco-v2/170221_162533"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])

# check_broken -p /hdfs/local/karl/addMEM/2016/2017Mar24/final_ntuples_recopied/2lss_1tau -o -z -i -P -v

samples_2016["/TTTo2L2Nu_TuneCUETP8M2_ttHtranche3_13TeV-powheg-pythia8/matze-faster_v8_ttjets_dl_maod_p1_3a2fa29ab1d54ae0995b28f27b405be9-v1/USER"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "TT"),
  ("process_name_specific", "TTTo2L2Nu_fastsim_p1"),
  ("nof_files",             1),
  ("nof_events",            90528028),
  ("use_it",                False),
  ("xsection",              87.300000),
  ("genWeight",             True),
  ("triggers",              [ "1e", "1mu", "2e", "1e1mu", "2mu", "3e", "2e1mu", "1e2mu", "3mu", "1e1tau", "1mu1tau", "2tau" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/addMEM/2016/2017Mar24/final_ntuples_recopied/2lss_1tau/TTTo2L2Nu_TuneCUETP8M2_ttHtranche3_13TeV-powheg-pythia8/VHBB_HEPPY_V25tthtautau_TTTo2L2Nu_TuneCUETP8M2_ttHtranche3_13TeV-powheg-Py8__matze-faster_v8_ttjets_dl_maod_p1_3a2fa29ab1d54ae0995b28f27b405be9-v1/170207_130407"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/TTTo2L2Nu_TuneCUETP8M2_ttHtranche3_13TeV-powheg-pythia8/matze-faster_v8_ttjets_dl_maod_p2_3a2fa29ab1d54ae0995b28f27b405be9-v1/USER"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "TT"),
  ("process_name_specific", "TTTo2L2Nu_fastsim_p2"),
  ("nof_files",             1),
  ("nof_events",            90528028),
  ("use_it",                False),
  ("xsection",              87.300000),
  ("genWeight",             True),
  ("triggers",              [ "1e", "1mu", "2e", "1e1mu", "2mu", "3e", "2e1mu", "1e2mu", "3mu", "1e1tau", "1mu1tau", "2tau" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/addMEM/2016/2017Mar24/final_ntuples_recopied/2lss_1tau/TTTo2L2Nu_TuneCUETP8M2_ttHtranche3_13TeV-powheg-pythia8/VHBB_HEPPY_V25tthtautau_TTTo2L2Nu_TuneCUETP8M2_ttHtranche3_13TeV-powheg-Py8__matze-faster_v8_ttjets_dl_maod_p2_3a2fa29ab1d54ae0995b28f27b405be9-v1/170208_163923"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/TTTo2L2Nu_TuneCUETP8M2_ttHtranche3_13TeV-powheg-pythia8/matze-faster_v8_ttjets_dl_maod_p3_3a2fa29ab1d54ae0995b28f27b405be9-v1/USER"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "TT"),
  ("process_name_specific", "TTTo2L2Nu_fastsim_p3"),
  ("nof_files",             1),
  ("nof_events",            90528028),
  ("use_it",                False),
  ("xsection",              87.300000),
  ("genWeight",             True),
  ("triggers",              [ "1e", "1mu", "2e", "1e1mu", "2mu", "3e", "2e1mu", "1e2mu", "3mu", "1e1tau", "1mu1tau", "2tau" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/addMEM/2016/2017Mar24/final_ntuples_recopied/2lss_1tau/TTTo2L2Nu_TuneCUETP8M2_ttHtranche3_13TeV-powheg-pythia8/VHBB_HEPPY_V25tthtautau_TTTo2L2Nu_TuneCUETP8M2_ttHtranche3_13TeV-powheg-Py8__matze-faster_v8_ttjets_dl_maod_p3_3a2fa29ab1d54ae0995b28f27b405be9-v1/170208_163840"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/TTToSemilepton_TuneCUETP8M2_ttHtranche3_13TeV-powheg-pythia8/matze-faster_v8_ttjets_sl_maod_p1_3a2fa29ab1d54ae0995b28f27b405be9-v1/USER"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "TT"),
  ("process_name_specific", "TTToSemilepton_fastsim_p1"),
  ("nof_files",             1),
  ("nof_events",            85311658),
  ("use_it",                False),
  ("xsection",              245.000000),
  ("genWeight",             True),
  ("triggers",              [ "1e", "1mu", "2e", "1e1mu", "2mu", "3e", "2e1mu", "1e2mu", "3mu", "1e1tau", "1mu1tau", "2tau" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/addMEM/2016/2017Mar24/final_ntuples_recopied/2lss_1tau/TTToSemilepton_TuneCUETP8M2_ttHtranche3_13TeV-powheg-pythia8/VHBB_HEPPY_V25tthtautau_TTToSemilepton_TuneCUETP8M2_ttHtranche3_13TeV-powheg-Py8__matze-faster_v8_ttjets_sl_maod_p1_3a2fa29ab1d54ae0995b28f27b405be9-v1/170207_153448"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/TTToSemilepton_TuneCUETP8M2_ttHtranche3_13TeV-powheg-pythia8/matze-faster_v8_ttjets_sl_maod_p2_3a2fa29ab1d54ae0995b28f27b405be9-v1/USER"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "TT"),
  ("process_name_specific", "TTToSemilepton_fastsim_p2"),
  ("nof_files",             1),
  ("nof_events",            85311658),
  ("use_it",                False),
  ("xsection",              245.000000),
  ("genWeight",             True),
  ("triggers",              [ "1e", "1mu", "2e", "1e1mu", "2mu", "3e", "2e1mu", "1e2mu", "3mu", "1e1tau", "1mu1tau", "2tau" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/addMEM/2016/2017Mar24/final_ntuples_recopied/2lss_1tau/TTToSemilepton_TuneCUETP8M2_ttHtranche3_13TeV-powheg-pythia8/VHBB_HEPPY_V25tthtautau_TTToSemilepton_TuneCUETP8M2_ttHtranche3_13TeV-powheg-Py8__matze-faster_v8_ttjets_sl_maod_p2_3a2fa29ab1d54ae0995b28f27b405be9-v1/170208_162433"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/TTToSemilepton_TuneCUETP8M2_ttHtranche3_13TeV-powheg-pythia8/matze-faster_v8_ttjets_sl_maod_p3_3a2fa29ab1d54ae0995b28f27b405be9-v1/USER"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "TT"),
  ("process_name_specific", "TTToSemilepton_fastsim_p3"),
  ("nof_files",             1),
  ("nof_events",            85311658),
  ("use_it",                False),
  ("xsection",              245.000000),
  ("genWeight",             True),
  ("triggers",              [ "1e", "1mu", "2e", "1e1mu", "2mu", "3e", "2e1mu", "1e2mu", "3mu", "1e1tau", "1mu1tau", "2tau" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/addMEM/2016/2017Mar24/final_ntuples_recopied/2lss_1tau/TTToSemilepton_TuneCUETP8M2_ttHtranche3_13TeV-powheg-pythia8/VHBB_HEPPY_V25tthtautau_TTToSemilepton_TuneCUETP8M2_ttHtranche3_13TeV-powheg-Py8__matze-faster_v8_ttjets_sl_maod_p3_3a2fa29ab1d54ae0995b28f27b405be9-v1/170209_090617"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/matze-faster_v9_ttW_maod_54aa74f75231422e9f4d3766cb92a64a-v1/USER"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "TTW"),
  ("process_name_specific", "TTWJetsToLNu_fastsim"),
  ("nof_files",             1),
  ("nof_events",            7158310),
  ("use_it",                False),
  ("xsection",              0.204300),
  ("genWeight",             True),
  ("triggers",              [ "1e", "1mu", "2e", "1e1mu", "2mu", "3e", "2e1mu", "1e2mu", "3mu", "1e1tau", "1mu1tau", "2tau" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/addMEM/2016/2017Mar24/final_ntuples_recopied/2lss_1tau/TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/VHBB_HEPPY_V25tthtautau_TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-Py8__matze-faster_v9_ttW_maod_54aa74f75231422e9f4d3766cb92a64a-v1/170208_163631"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-pythia8/matze-faster_v9_ttZ_maod_54aa74f75231422e9f4d3766cb92a64a-v1/USER"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "TTZ"),
  ("process_name_specific", "TTZToLLNuNu_fastsim"),
  ("nof_files",             1),
  ("nof_events",            8826709),
  ("use_it",                False),
  ("xsection",              0.252900),
  ("genWeight",             True),
  ("triggers",              [ "1e", "1mu", "2e", "1e1mu", "2mu", "3e", "2e1mu", "1e2mu", "3mu", "1e1tau", "1mu1tau", "2tau" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/addMEM/2016/2017Mar24/final_ntuples_recopied/2lss_1tau/TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-pythia8/VHBB_HEPPY_V25tthtautau_TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-Py8__matze-faster_v9_ttZ_maod_54aa74f75231422e9f4d3766cb92a64a-v1/170208_172612"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/WZTo3LNu_TuneCUETP8M1_13TeV-powheg-pythia8/matze-faster_v9_WZ_maod_54aa74f75231422e9f4d3766cb92a64a-v1/USER"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "EWK"),
  ("process_name_specific", "WZTo3LNu_fastsim"),
  ("nof_files",             1),
  ("nof_events",            18814814),
  ("use_it",                False),
  ("xsection",              4.102000),
  ("genWeight",             True),
  ("triggers",              [ "1e", "1mu", "2e", "1e1mu", "2mu", "3e", "2e1mu", "1e2mu", "3mu", "1e1tau", "1mu1tau", "2tau" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/addMEM/2016/2017Mar24/final_ntuples_recopied/2lss_1tau/WZTo3LNu_TuneCUETP8M1_13TeV-powheg-pythia8/VHBB_HEPPY_V25tthtautau_WZTo3LNu_TuneCUETP8M1_13TeV-powheg-Py8__matze-faster_v9_WZ_maod_54aa74f75231422e9f4d3766cb92a64a-v1/170209_090741"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/ttHToNonbb_M125_TuneCUETP8M2_ttHtranche3_13TeV-powheg-pythia8/matze-faster_v8_ttH_maod_p1_3a2fa29ab1d54ae0995b28f27b405be9-v1/USER"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "signal"),
  ("process_name_specific", "ttHToNonbb_fastsim_p1"),
  ("nof_files",             1),
  ("nof_events",            16459380),
  ("use_it",                False),
  ("xsection",              0.215100),
  ("genWeight",             True),
  ("triggers",              [ "1e", "1mu", "2e", "1e1mu", "2mu", "3e", "2e1mu", "1e2mu", "3mu", "1e1tau", "1mu1tau", "2tau" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/addMEM/2016/2017Mar24/final_ntuples_recopied/2lss_1tau/ttHToNonbb_M125_TuneCUETP8M2_ttHtranche3_13TeV-powheg-pythia8/VHBB_HEPPY_V25tthtautau_ttHToNonbb_M125_TuneCUETP8M2_ttHtranche3_13TeV-powheg-Py8__matze-faster_v8_ttH_maod_p1_3a2fa29ab1d54ae0995b28f27b405be9-v1/170207_130941"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/ttHToNonbb_M125_TuneCUETP8M2_ttHtranche3_13TeV-powheg-pythia8/matze-faster_v8_ttH_maod_p2_3a2fa29ab1d54ae0995b28f27b405be9-v1/USER"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "signal"),
  ("process_name_specific", "ttHToNonbb_fastsim_p2"),
  ("nof_files",             1),
  ("nof_events",            16459380),
  ("use_it",                False),
  ("xsection",              0.215100),
  ("genWeight",             True),
  ("triggers",              [ "1e", "1mu", "2e", "1e1mu", "2mu", "3e", "2e1mu", "1e2mu", "3mu", "1e1tau", "1mu1tau", "2tau" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/addMEM/2016/2017Mar24/final_ntuples_recopied/2lss_1tau/ttHToNonbb_M125_TuneCUETP8M2_ttHtranche3_13TeV-powheg-pythia8/VHBB_HEPPY_V25tthtautau_ttHToNonbb_M125_TuneCUETP8M2_ttHtranche3_13TeV-powheg-Py8__matze-faster_v8_ttH_maod_p2_3a2fa29ab1d54ae0995b28f27b405be9-v1/170208_162259"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/ttHToNonbb_M125_TuneCUETP8M2_ttHtranche3_13TeV-powheg-pythia8/matze-faster_v8_ttH_maod_p3_3a2fa29ab1d54ae0995b28f27b405be9-v1/USER"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "signal"),
  ("process_name_specific", "ttHToNonbb_fastsim_p3"),
  ("nof_files",             1),
  ("nof_events",            16459380),
  ("use_it",                False),
  ("xsection",              0.215100),
  ("genWeight",             True),
  ("triggers",              [ "1e", "1mu", "2e", "1e1mu", "2mu", "3e", "2e1mu", "1e2mu", "3mu", "1e1tau", "1mu1tau", "2tau" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/addMEM/2016/2017Mar24/final_ntuples_recopied/2lss_1tau/ttHToNonbb_M125_TuneCUETP8M2_ttHtranche3_13TeV-powheg-pythia8/VHBB_HEPPY_V25tthtautau_ttHToNonbb_M125_TuneCUETP8M2_ttHtranche3_13TeV-powheg-Py8__matze-faster_v8_ttH_maod_p3_3a2fa29ab1d54ae0995b28f27b405be9-v1/170208_124342"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
