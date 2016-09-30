from collections import OrderedDict as OD

samples = OD()

samples["/DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DYJetsToLL_M-10to50"),
  ("nof_files",             369),
  ("nof_events",            30915886),
  ("use_it",                True),
  ("xsection",              18610.000000),
  ("triggers",              [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/lucia/VHBBHeppyV24bis/DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/VHBB_HEPPY_V24bis_DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-amcatnloFXFX-Py8__spr16MAv2-puspr16_80r2as_2016_MAv2_v0-v1/160911_223234"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples["/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring16MiniAODv2-PUSpring16RAWAODSIM_reHLT_80X_mcRun2_asymptotic_v14_ext1-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DYJetsToLL_M-50"),
  ("nof_files",             657),
  ("nof_events",            91350867),
  ("use_it",                True),
  ("xsection",              6025.200000),
  ("triggers",              [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/lucia/VHBBHeppyV24bis/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/VHBB_HEPPY_V24_DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-Py8__spr16MAv2-puspr16_HLT_80r2as_v14_ext1-v1/160909_070517"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples["/GluGluHToZZTo4L_M125_13TeV_powheg2_JHUgenV6_pythia8/RunIISpring16MiniAODv2-PUSpring16RAWAODSIM_reHLT_80X_mcRun2_asymptotic_v14-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "additional_signal_overlap"),
  ("process_name_specific", "GluGluHToZZTo4L"),
  ("nof_files",             15),
  ("nof_events",            969200),
  ("use_it",                True),
  ("xsection",              0.011900),
  ("triggers",              [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/lucia/VHBBHeppyV24bis/GluGluHToZZTo4L_M125_13TeV_powheg2_JHUgenV6_pythia8/VHBB_HEPPY_V24bis_GluGluHToZZTo4L_M125_13TeV_powheg2_JHUgenV6_Py8__spr16MAv2-puspr16_HLT_80r2as_v14-v1/160911_224902"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples["/MuonEG/Run2016B-PromptReco-v2/MINIAOD"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "MuonEG_Run2016B_v2"),
  ("nof_files",             2014),
  ("nof_events",            139552456),
  ("use_it",                True),
  ("xsection",              1.000000),
  ("triggers",              [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/lucia/VHBBHeppyV24bis/MuonEG/VHBB_HEPPY_V24_MuonEG__Run2016B-PromptReco-v2/160920_122430"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples["/MuonEG/Run2016C-PromptReco-v2/MINIAOD"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "MuonEG_Run2016C"),
  ("nof_files",             696),
  ("nof_events",            139552456),
  ("use_it",                True),
  ("xsection",              1.000000),
  ("triggers",              [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/lucia/VHBBHeppyV24bis/MuonEG/VHBB_HEPPY_V24_MuonEG__Run2016C-PromptReco-v2/160920_122508"),
        ("selection", "*"),
        ("blacklist", [556]),
      ]),
    ]
  ),
])
samples["/MuonEG/Run2016D-PromptReco-v2/MINIAOD"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "MuonEG_Run2016D"),
  ("nof_files",             1024),
  ("nof_events",            139552456),
  ("use_it",                True),
  ("xsection",              1.000000),
  ("triggers",              [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/lucia/VHBBHeppyV24bis/MuonEG/VHBB_HEPPY_V24_MuonEG__Run2016D-PromptReco-v2/160920_122552"),
        ("selection", "*"),
        ("blacklist", [16, 17, 18, 22, 423, 628, 789, 927]),
      ]),
    ]
  ),
])
samples["/MuonEG/Run2016E-PromptReco-v2/MINIAOD"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "MuonEG_Run2016E"),
  ("nof_files",             909),
  ("nof_events",            139552456),
  ("use_it",                True),
  ("xsection",              1.000000),
  ("triggers",              [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/lucia/VHBBHeppyV24bis/MuonEG/VHBB_HEPPY_V24_MuonEG__Run2016E-PromptReco-v2/160920_122633"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples["/MuonEG/Run2016F-PromptReco-v1/MINIAOD"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "MuonEG_Run2016F"),
  ("nof_files",             966),
  ("nof_events",            139552456),
  ("use_it",                True),
  ("xsection",              1.000000),
  ("triggers",              [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/lucia/VHBBHeppyV24bis/MuonEG/VHBB_HEPPY_V24_MuonEG__Run2016F-PromptReco-v1/160910_105743"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples["/MuonEG/Run2016G-PromptReco-v1/MINIAOD"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "MuonEG_Run2016G"),
  ("nof_files",             2137),
  ("nof_events",            139552456),
  ("use_it",                True),
  ("xsection",              1.000000),
  ("triggers",              [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/lucia/VHBBHeppyV24bis/MuonEG/VHBB_HEPPY_V24_MuonEG__Run2016G-PromptReco-v1/160910_105850"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples["/ST_s-channel_4f_leptonDecays_13TeV-amcatnlo-pythia8_TuneCUETP8M1/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "TT"),
  ("process_name_specific", "ST_s-channel_4f_leptonDecays"),
  ("nof_files",             24),
  ("nof_events",            1000000),
  ("use_it",                True),
  ("xsection",              3.750000),
  ("triggers",              [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/lucia/VHBBHeppyV24bis/ST_s-channel_4f_leptonDecays_13TeV-amcatnlo-pythia8_TuneCUETP8M1/VHBB_HEPPY_V24_ST_s-channel_4f_leptonDecays_13TeV-amcatnlo-Py8_TuneCUETP8M1__spr16MAv2-puspr16_80r2as_2016_MAv2_v0-v1/160909_063446"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples["/ST_t-channel_antitop_4f_inclusiveDecays_13TeV-powhegV2-madspin-pythia8_TuneCUETP8M1/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "TT"),
  ("process_name_specific", "ST_t-channel_antitop_4f_inclusiveDecays"),
  ("nof_files",             520),
  ("nof_events",            19825855),
  ("use_it",                True),
  ("xsection",              70.690000),
  ("triggers",              [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/lucia/VHBBHeppyV24bis/ST_t-channel_antitop_4f_inclusiveDecays_13TeV-powhegV2-madspin-pythia8_TuneCUETP8M1/VHBB_HEPPY_V24_ST_t-channel_antitop_4f_inclusiveDecays_13TeV-powhegV2-madspin-Py8_TuneCUETP8M1__spr16MAv2-puspr16_80r2as_2016_MAv2_v0-v1/160909_063650"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples["/ST_t-channel_top_4f_inclusiveDecays_13TeV-powhegV2-madspin-pythia8_TuneCUETP8M1/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "TT"),
  ("process_name_specific", "ST_t-channel_top_4f_inclusiveDecays"),
  ("nof_files",             324),
  ("nof_events",            32532748),
  ("use_it",                True),
  ("xsection",              70.690000),
  ("triggers",              [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/lucia/VHBBHeppyV24bis/ST_t-channel_top_4f_inclusiveDecays_13TeV-powhegV2-madspin-pythia8_TuneCUETP8M1/VHBB_HEPPY_V24_ST_t-channel_top_4f_inclusiveDecays_13TeV-powhegV2-madspin-Py8_TuneCUETP8M1__spr16MAv2-puspr16_80r2as_2016_MAv2_v0-v1/160909_070435"),
        ("selection", "*"),
        ("blacklist", [159, 246]),
      ]),
    ]
  ),
])
samples["/ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "TT"),
  ("process_name_specific", "ST_tW_antitop_5f_inclusiveDecays"),
  ("nof_files",             26),
  ("nof_events",            985000),
  ("use_it",                True),
  ("xsection",              35.600000),
  ("triggers",              [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/lucia/VHBBHeppyV24bis/ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1/VHBB_HEPPY_V24_ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-Py8_TuneCUETP8M1__spr16MAv2-puspr16_80r2as_2016_MAv2_v0-v1/160909_063328"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples["/ST_tW_top_5f_NoFullyHadronicDecays_13TeV-powheg_TuneCUETP8M1/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "TT"),
  ("process_name_specific", "ST_tW_top_5f_NoFullyHadronicDecays"),
  ("nof_files",             66),
  ("nof_events",            5405726),
  ("use_it",                True),
  ("xsection",              35.600000),
  ("triggers",              [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/lucia/VHBBHeppyV24bis/ST_tW_top_5f_NoFullyHadronicDecays_13TeV-powheg_TuneCUETP8M1/VHBB_HEPPY_V24bis_ST_tW_top_5f_NoFullyHadronicDecays_13TeV-powheg_TuneCUETP8M1__spr16MAv2-puspr16_80r2as_2016_MAv2_v0-v1/160911_223856"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples["/SingleElectron/Run2016B-PromptReco-v2/MINIAOD"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "SingleElectron_Run2016B_v2"),
  ("nof_files",             3209),
  ("nof_events",            814959742),
  ("use_it",                True),
  ("xsection",              1.000000),
  ("triggers",              [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/lucia/VHBBHeppyV24bis/SingleElectron/VHBB_HEPPY_V24_SingleElectron__Run2016B-PromptReco-v2/160910_204523"),
        ("selection", "*"),
        ("blacklist", [819]),
      ]),
    ]
  ),
])
samples["/SingleElectron/Run2016C-PromptReco-v2/MINIAOD"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "SingleElectron_Run2016C"),
  ("nof_files",             1029),
  ("nof_events",            814959742),
  ("use_it",                True),
  ("xsection",              1.000000),
  ("triggers",              [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/lucia/VHBBHeppyV24bis/SingleElectron/VHBB_HEPPY_V24_SingleElectron__Run2016C-PromptReco-v2/160910_204634"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples["/SingleElectron/Run2016D-PromptReco-v2/MINIAOD"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "SingleElectron_Run2016D"),
  ("nof_files",             1545),
  ("nof_events",            814959742),
  ("use_it",                True),
  ("xsection",              1.000000),
  ("triggers",              [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/lucia/VHBBHeppyV24bis/SingleElectron/VHBB_HEPPY_V24_SingleElectron__Run2016D-PromptReco-v2/160910_204714"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples["/SingleElectron/Run2016E-PromptReco-v2/MINIAOD"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "SingleElectron_Run2016E"),
  ("nof_files",             1372),
  ("nof_events",            814959742),
  ("use_it",                True),
  ("xsection",              1.000000),
  ("triggers",              [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/lucia/VHBBHeppyV24bis/SingleElectron/VHBB_HEPPY_V24_SingleElectron__Run2016E-PromptReco-v2/160910_204822"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples["/SingleElectron/Run2016F-PromptReco-v1/MINIAOD"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "SingleElectron_Run2016F"),
  ("nof_files",             984),
  ("nof_events",            814959742),
  ("use_it",                True),
  ("xsection",              1.000000),
  ("triggers",              [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/lucia/VHBBHeppyV24bis/SingleElectron/VHBB_HEPPY_V24_SingleElectron__Run2016F-PromptReco-v1/160910_204902"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples["/SingleElectron/Run2016G-PromptReco-v1/MINIAOD"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "SingleElectron_Run2016G"),
  ("nof_files",             2076),
  ("nof_events",            814959742),
  ("use_it",                True),
  ("xsection",              1.000000),
  ("triggers",              [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/lucia/VHBBHeppyV24bis/SingleElectron/VHBB_HEPPY_V24_SingleElectron__Run2016G-PromptReco-v1/160910_204938"),
        ("selection", "*"),
        ("blacklist", [1261]),
      ]),
    ]
  ),
])
samples["/SingleMuon/Run2016B-PromptReco-v2/MINIAOD"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "SingleMuon_Run2016B_v2"),
  ("nof_files",             3023),
  ("nof_events",            618050946),
  ("use_it",                True),
  ("xsection",              1.000000),
  ("triggers",              [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/lucia/VHBBHeppyV24bis/SingleMuon/VHBB_HEPPY_V24_SingleMuon__Run2016B-PromptReco-v2/160910_205020"),
        ("selection", "*"),
        ("blacklist", [2173]),
      ]),
    ]
  ),
])
samples["/SingleMuon/Run2016C-PromptReco-v2/MINIAOD"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "SingleMuon_Run2016C"),
  ("nof_files",             1044),
  ("nof_events",            618050946),
  ("use_it",                True),
  ("xsection",              1.000000),
  ("triggers",              [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/lucia/VHBBHeppyV24bis/SingleMuon/VHBB_HEPPY_V24_SingleMuon__Run2016C-PromptReco-v2/160910_205128"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples["/SingleMuon/Run2016D-PromptReco-v2/MINIAOD"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "SingleMuon_Run2016D"),
  ("nof_files",             1535),
  ("nof_events",            618050946),
  ("use_it",                True),
  ("xsection",              1.000000),
  ("triggers",              [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/lucia/VHBBHeppyV24bis/SingleMuon/VHBB_HEPPY_V24_SingleMuon__Run2016D-PromptReco-v2/160910_205212"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples["/SingleMuon/Run2016E-PromptReco-v2/MINIAOD"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "SingleMuon_Run2016E"),
  ("nof_files",             1363),
  ("nof_events",            618050946),
  ("use_it",                True),
  ("xsection",              1.000000),
  ("triggers",              [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/lucia/VHBBHeppyV24bis/SingleMuon/VHBB_HEPPY_V24_SingleMuon__Run2016E-PromptReco-v2/160910_205250"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples["/SingleMuon/Run2016F-PromptReco-v1/MINIAOD"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "SingleMuon_Run2016F"),
  ("nof_files",             966),
  ("nof_events",            618050946),
  ("use_it",                True),
  ("xsection",              1.000000),
  ("triggers",              [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/lucia/VHBBHeppyV24bis/SingleMuon/VHBB_HEPPY_V24_SingleMuon__Run2016F-PromptReco-v1/160910_205402"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples["/SingleMuon/Run2016G-PromptReco-v1/MINIAOD"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "SingleMuon_Run2016G"),
  ("nof_files",             2159),
  ("nof_events",            618050946),
  ("use_it",                True),
  ("xsection",              1.000000),
  ("triggers",              [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/lucia/VHBBHeppyV24bis/SingleMuon/VHBB_HEPPY_V24_SingleMuon__Run2016G-PromptReco-v1/160910_205443"),
        ("selection", "*"),
        ("blacklist", [78]),
      ]),
    ]
  ),
])
samples["/TGJets_TuneCUETP8M1_13TeV_amcatnlo_madspin_pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0_ext1-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "Rares"),
  ("process_name_specific", "TGJets_ext1"),
  ("nof_files",             19),
  ("nof_events",            1535543),
  ("use_it",                True),
  ("xsection",              2.967000),
  ("triggers",              [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/lucia/VHBBHeppyV24bis/TGJets_TuneCUETP8M1_13TeV_amcatnlo_madspin_pythia8/VHBB_HEPPY_V24bis_TGJets_TuneCUETP8M1_13TeV_amcatnlo_madspin_Py8__spr16MAv2-puspr16_80r2as_2016_MAv2_v0_ext1-v1/160911_224639"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples["/THW_Hincl_13TeV-madgraph-pythia8_TuneCUETP8M1/RunIISpring16MiniAODv2-PUSpring16RAWAODSIM_reHLT_80X_mcRun2_asymptotic_v14-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "additional_signal_overlap"),
  ("process_name_specific", "THW_Hincl"),
  ("nof_files",             17),
  ("nof_events",            1401800),
  ("use_it",                True),
  ("xsection",              0.015610),
  ("triggers",              [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/lucia/VHBBHeppyV24bis/THW_Hincl_13TeV-madgraph-pythia8_TuneCUETP8M1/VHBB_HEPPY_V24bis_THW_Hincl_13TeV-madgraph-Py8_TuneCUETP8M1__spr16MAv2-puspr16_HLT_80r2as_v14-v1/160911_224716"),
        ("selection", "*"),
        ("blacklist", [15]),
      ]),
    ]
  ),
])
samples["/TTGJets_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "Rares"),
  ("process_name_specific", "TTGJets"),
  ("nof_files",             56),
  ("nof_events",            4301632),
  ("use_it",                True),
  ("xsection",              3.697000),
  ("triggers",              [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/lucia/VHBBHeppyV24bis/TTGJets_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/VHBB_HEPPY_V24bis_TTGJets_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-Py8__spr16MAv2-puspr16_80r2as_2016_MAv2_v0-v1/160911_223929"),
        ("selection", "*"),
        ("blacklist", [1, 6, 14, 25, 39, 52]),
      ]),
    ]
  ),
])
samples["/TTJets_DiLept_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v4/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "TT"),
  ("process_name_specific", "TTJets_DiLept"),
  ("nof_files",             70),
  ("nof_events",            30487742),
  ("use_it",                True),
  ("xsection",              87.300000),
  ("triggers",              [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/lucia/VHBBHeppyV24bis/TTJets_DiLept_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/VHBB_HEPPY_V24bis_TTJets_DiLept_TuneCUETP8M1_13TeV-madgraphMLM-Py8__spr16MAv2-puspr16_80r2as_2016_MAv2_v0-v4/160911_223748"),
        ("selection", "*"),
        ("blacklist", [47, 59]),
      ]),
    ]
  ),
])
samples["/TTJets_DiLept_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0_ext1-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "TT"),
  ("process_name_specific", "TTJets_DiLept_ext1"),
  ("nof_files",             278),
  ("nof_events",            30487742),
  ("use_it",                True),
  ("xsection",              87.300000),
  ("triggers",              [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/lucia/VHBBHeppyV24bis/TTJets_DiLept_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/VHBB_HEPPY_V24bis_TTJets_DiLept_TuneCUETP8M1_13TeV-madgraphMLM-Py8__spr16MAv2-puspr16_80r2as_2016_MAv2_v0_ext1-v1/160911_223310"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples["/TTJets_SingleLeptFromT_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "TT"),
  ("process_name_specific", "TTJets_SingleLeptFromT"),
  ("nof_files",             111),
  ("nof_events",            18165634),
  ("use_it",                True),
  ("xsection",              182.000000),
  ("triggers",              [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/lucia/VHBBHeppyV24bis/TTJets_SingleLeptFromT_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/VHBB_HEPPY_V24bis_TTJets_SingleLeptFromT_TuneCUETP8M1_13TeV-madgraphMLM-Py8__spr16MAv2-puspr16_80r2as_2016_MAv2_v0-v1/160911_223601"),
        ("selection", "*"),
        ("blacklist", [33]),
      ]),
    ]
  ),
])
samples["/TTJets_SingleLeptFromT_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0_ext1-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "TT"),
  ("process_name_specific", "TTJets_SingleLeptFromT_ext1"),
  ("nof_files",             229),
  ("nof_events",            18165634),
  ("use_it",                True),
  ("xsection",              182.000000),
  ("triggers",              [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/lucia/VHBBHeppyV24bis/TTJets_SingleLeptFromT_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/VHBB_HEPPY_V24bis_TTJets_SingleLeptFromT_TuneCUETP8M1_13TeV-madgraphMLM-Py8__spr16MAv2-puspr16_80r2as_2016_MAv2_v0_ext1-v1/160911_223200"),
        ("selection", "*"),
        ("blacklist", [1, 3, 5, 6, 7, 8, 11, 13, 14, 15, 16, 17, 18, 19, 20, 22, 23, 24, 25, 26, 28, 29, 30, 31, 32, 33, 34, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 57, 58, 59, 61, 62, 64, 65, 66, 67, 68, 70, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 90, 92, 93, 94, 95, 96, 97, 98, 99, 101, 102, 106, 107, 108, 109, 110, 112, 113, 114, 116, 117, 118, 119, 121, 123, 124, 125, 126, 127, 128, 129, 130, 132, 136, 137, 138, 139, 140, 141, 142, 143, 145, 146, 147, 148, 149, 150, 152, 153, 154, 156, 157, 158, 159, 160, 161, 162, 164, 167, 168, 169, 170, 172, 173, 176, 177, 178, 179, 180, 182, 183, 188, 189, 190, 191, 192, 194, 196, 197, 199, 200, 201, 202, 204, 205, 206, 207, 208, 212, 213, 215, 217, 218, 219, 220, 221, 222, 223, 227]),
      ]),
    ]
  ),
])
samples["/TTJets_SingleLeptFromTbar_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "TT"),
  ("process_name_specific", "TTJets_SingleLeptFromTbar"),
  ("nof_files",             137),
  ("nof_events",            60309864),
  ("use_it",                True),
  ("xsection",              182.000000),
  ("triggers",              [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/lucia/VHBBHeppyV24bis/TTJets_SingleLeptFromTbar_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/VHBB_HEPPY_V24bis_TTJets_SingleLeptFromTbar_TuneCUETP8M1_13TeV-madgraphMLM-Py8__spr16MAv2-puspr16_80r2as_2016_MAv2_v0-v1/160911_223528"),
        ("selection", "*"),
        ("blacklist", [49, 54]),
      ]),
    ]
  ),
])
samples["/TTJets_SingleLeptFromTbar_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0_ext1-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "TT"),
  ("process_name_specific", "TTJets_SingleLeptFromTbar_ext1"),
  ("nof_files",             529),
  ("nof_events",            60309864),
  ("use_it",                True),
  ("xsection",              182.000000),
  ("triggers",              [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/lucia/VHBBHeppyV24bis/TTJets_SingleLeptFromTbar_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/VHBB_HEPPY_V24bis_TTJets_SingleLeptFromTbar_TuneCUETP8M1_13TeV-madgraphMLM-Py8__spr16MAv2-puspr16_80r2as_2016_MAv2_v0_ext1-v1/160911_223125"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples["/TTTT_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0_ext1-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "Rares"),
  ("process_name_specific", "TTTT"),
  ("nof_files",             11),
  ("nof_events",            989025),
  ("use_it",                True),
  ("xsection",              0.009103),
  ("triggers",              [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/lucia/VHBBHeppyV24bis/TTTT_TuneCUETP8M1_13TeV-amcatnlo-pythia8/VHBB_HEPPY_V24bis_TTTT_TuneCUETP8M1_13TeV-amcatnlo-Py8__spr16MAv2-puspr16_80r2as_2016_MAv2_v0_ext1-v1/160911_224827"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples["/TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "TTW"),
  ("process_name_specific", "TTWJetsToLNu"),
  ("nof_files",             4),
  ("nof_events",            252673),
  ("use_it",                True),
  ("xsection",              0.204300),
  ("triggers",              [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/lucia/VHBBHeppyV24bis/TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/VHBB_HEPPY_V24bis_TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-Py8__spr16MAv2-puspr16_80r2as_2016_MAv2_v0-v1/160911_225800"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples["/TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISpring16MiniAODv2-premix_withHLT_80X_mcRun2_asymptotic_v14_ext1-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "TTZ"),
  ("process_name_specific", "TTZToLLNuNu_M-10_ext1"),
  ("nof_files",             24),
  ("nof_events",            2256848),
  ("use_it",                True),
  ("xsection",              0.252900),
  ("triggers",              [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/lucia/VHBBHeppyV24bis/TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-pythia8/VHBB_HEPPY_V24bis_TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-Py8__spr16MAv2-premix_withHLT_80r2as_v14_ext1-v1/160911_224606"),
        ("selection", "*"),
        ("blacklist", [16]),
      ]),
    ]
  ),
])
samples["/TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "TTZ"),
  ("process_name_specific", "TTZToLLNuNu_M-10"),
  ("nof_files",             6),
  ("nof_events",            2256848),
  ("use_it",                True),
  ("xsection",              0.252900),
  ("triggers",              [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/lucia/VHBBHeppyV24bis/TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-pythia8/VHBB_HEPPY_V24bis_TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-Py8__spr16MAv2-puspr16_80r2as_2016_MAv2_v0-v1/160911_225425"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples["/TT_TuneCUETP8M1_13TeV-powheg-pythia8/RunIISpring16MiniAODv1-PUSpring16_80X_mcRun2_asymptotic_2016_v3_ext3-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "TT"),
  ("process_name_specific", "TT_ext3"),
  ("nof_files",             2124),
  ("nof_events",            92882726),
  ("use_it",                True),
  ("xsection",              831.76),
  ("triggers",              [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/lucia/VHBBHeppyV24bis/TT_TuneCUETP8M1_13TeV-powheg-pythia8/VHBB_HEPPY_V24_TT_TuneCUETP8M1_13TeV-powheg-Py8__spr16MAv2-puspr16_HLT_80r2as_v14_ext3-v1/160909_063406"),
        ("selection", "*"),
        ("blacklist", [600]),
      ]),
    ]
  ),
])
samples["/Tau/Run2016B-PromptReco-v2/MINIAOD"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "Tau_Run2016B_v2"),
  ("nof_files",             3203),
  ("nof_events",            130731886),
  ("use_it",                True),
  ("xsection",              1.000000),
  ("triggers",              [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/lucia/VHBBHeppyV24bis/Tau/VHBB_HEPPY_V24_Tau__Run2016B-PromptReco-v2/160912_065507"),
        ("selection", "*"),
        ("blacklist", [2796, 2798, 2800, 2801, 2802, 2803]),
      ]),
    ]
  ),
])
samples["/Tau/Run2016D-PromptReco-v2/MINIAOD"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "Tau_Run2016D"),
  ("nof_files",             1552),
  ("nof_events",            130731886),
  ("use_it",                True),
  ("xsection",              1.000000),
  ("triggers",              [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/lucia/VHBBHeppyV24bis/Tau/VHBB_HEPPY_V24_Tau__Run2016D-PromptReco-v2/160912_070129"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples["/WGToLNuG_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "Rares"),
  ("process_name_specific", "WGToLNuG"),
  ("nof_files",             75),
  ("nof_events",            5916785),
  ("use_it",                True),
  ("xsection",              585.800000),
  ("triggers",              [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/lucia/VHBBHeppyV24bis/WGToLNuG_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/VHBB_HEPPY_V24bis_WGToLNuG_TuneCUETP8M1_13TeV-madgraphMLM-Py8__spr16MAv2-puspr16_80r2as_2016_MAv2_v0-v1/160911_223823"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples["/WWTo2L2Nu_13TeV-powheg/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "EWK"),
  ("process_name_specific", "WWTo2L2Nu"),
  ("nof_files",             26),
  ("nof_events",            1996600),
  ("use_it",                True),
  ("xsection",              10.481000),
  ("triggers",              [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/lucia/VHBBHeppyV24bis/WWTo2L2Nu_13TeV-powheg/VHBB_HEPPY_V24bis_WWTo2L2Nu_13TeV-powheg__spr16MAv2-puspr16_80r2as_2016_MAv2_v0-v1/160911_224455"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples["/WW_DoubleScattering_13TeV-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "Rares"),
  ("process_name_specific", "WW_DoubleScattering"),
  ("nof_files",             12),
  ("nof_events",            844954),
  ("use_it",                True),
  ("xsection",              1.640000),
  ("triggers",              [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/lucia/VHBBHeppyV24bis/WW_DoubleScattering_13TeV-pythia8/VHBB_HEPPY_V24bis_WW_DoubleScattering_13TeV-Py8__spr16MAv2-puspr16_80r2as_2016_MAv2_v0-v1/160911_225013"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples["/WZTo3LNu_TuneCUETP8M1_13TeV-powheg-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "EWK"),
  ("process_name_specific", "WZTo3LNu"),
  ("nof_files",             26),
  ("nof_events",            2000000),
  ("use_it",                True),
  ("xsection",              4.102000),
  ("triggers",              [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/lucia/VHBBHeppyV24bis/WZTo3LNu_TuneCUETP8M1_13TeV-powheg-pythia8/VHBB_HEPPY_V24bis_WZTo3LNu_TuneCUETP8M1_13TeV-powheg-Py8__spr16MAv2-puspr16_80r2as_2016_MAv2_v0-v1/160911_224418"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples["/WZZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "Rares"),
  ("process_name_specific", "WZZ"),
  ("nof_files",             3),
  ("nof_events",            249800),
  ("use_it",                True),
  ("xsection",              0.055650),
  ("triggers",              [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/lucia/VHBBHeppyV24bis/WZZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8/VHBB_HEPPY_V24bis_WZZ_TuneCUETP8M1_13TeV-amcatnlo-Py8__spr16MAv2-puspr16_80r2as_2016_MAv2_v0-v1/160911_225836"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples["/WpWpJJ_EWK-QCD_TuneCUETP8M1_13TeV-madgraph-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v2/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "Rares"),
  ("process_name_specific", "WpWpJJ_EWK-QCD"),
  ("nof_files",             8),
  ("nof_events",            138235),
  ("use_it",                True),
  ("xsection",              0.037110),
  ("triggers",              [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/lucia/VHBBHeppyV24bis/WpWpJJ_EWK-QCD_TuneCUETP8M1_13TeV-madgraph-pythia8/VHBB_HEPPY_V24bis_WpWpJJ_EWK-QCD_TuneCUETP8M1_13TeV-madgraph-Py8__spr16MAv2-puspr16_80r2as_2016_MAv2_v0-v2/160911_225910"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples["/ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "Rares"),
  ("process_name_specific", "ZGTo2LG"),
  ("nof_files",             55),
  ("nof_events",            14616963),
  ("use_it",                True),
  ("xsection",              131.300000),
  ("triggers",              [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/lucia/VHBBHeppyV24bis/ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/VHBB_HEPPY_V24bis_ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-Py8__spr16MAv2-puspr16_80r2as_2016_MAv2_v0-v1/160911_224112"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples["/ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0_ext1-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "Rares"),
  ("process_name_specific", "ZGTo2LG_ext1"),
  ("nof_files",             96),
  ("nof_events",            14616963),
  ("use_it",                True),
  ("xsection",              131.300000),
  ("triggers",              [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/lucia/VHBBHeppyV24bis/ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/VHBB_HEPPY_V24bis_ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-Py8__spr16MAv2-puspr16_80r2as_2016_MAv2_v0_ext1-v1/160911_223418"),
        ("selection", "*"),
        ("blacklist", [25, 27, 28, 47, 48, 55, 56, 63, 64, 74, 75, 77, 78, 79, 80]),
      ]),
    ]
  ),
])
samples["/ZZTo4L_13TeV-amcatnloFXFX-pythia8/RunIISpring16MiniAODv2-PUSpring16RAWAODSIM_reHLT_80X_mcRun2_asymptotic_v14-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "EWK"),
  ("process_name_specific", "ZZTo4L"),
  ("nof_files",             50),
  ("nof_events",            7878358),
  ("use_it",                True),
  ("xsection",              1.256000),
  ("triggers",              [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/lucia/VHBBHeppyV24bis/ZZTo4L_13TeV-amcatnloFXFX-pythia8/VHBB_HEPPY_V24bis_ZZTo4L_13TeV-amcatnloFXFX-Py8__spr16MAv2-puspr16_HLT_80r2as_v14-v1/160911_223636"),
        ("selection", "*"),
        ("blacklist", [11, 12, 14, 16, 24, 25, 29, 31, 35]),
      ]),
    ]
  ),
])
samples["/tZq_ll_4f_13TeV-amcatnlo-pythia8_TuneCUETP8M1/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "Rares"),
  ("process_name_specific", "tZq_ll_4f"),
  ("nof_files",             35),
  ("nof_events",            2973639),
  ("use_it",                True),
  ("xsection",              0.075800),
  ("triggers",              [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/lucia/VHBBHeppyV24bis/tZq_ll_4f_13TeV-amcatnlo-pythia8_TuneCUETP8M1/VHBB_HEPPY_V24bis_tZq_ll_4f_13TeV-amcatnlo-Py8_TuneCUETP8M1__spr16MAv2-puspr16_80r2as_2016_MAv2_v0-v1/160911_224340"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples["/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/RunIISpring16MiniAODv2-PUSpring16RAWAODSIM_reHLT_80X_mcRun2_asymptotic_v14_ext1-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "signal"),
  ("process_name_specific", "ttHJetToNonbb_M125"),
  ("nof_files",             109),
  ("nof_events",            6228310),
  ("use_it",                True),
  ("xsection",              0.215100),
  ("triggers",              [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/lucia/VHBBHeppyV24bis/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/VHBB_HEPPY_V24bis_ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_Py8_mWCutfix__spr16MAv2-puspr16_HLT_80r2as_v14_ext1-v1/160911_223711"),
        ("selection", "*"),
        ("blacklist", [10, 11, 14, 16, 20, 22, 23, 26, 29, 30, 31, 33, 34, 38, 39, 43, 44, 45, 51, 54, 57, 62, 63, 64, 66, 67, 68, 70, 71, 72, 73, 75, 76, 77, 79, 80, 81, 89, 98, 99]),
      ]),
    ]
  ),
])
samples["/ttHToNonbb_M125_13TeV_powheg_pythia8/RunIISpring16MiniAODv2-PUSpring16RAWAODSIM_reHLT_80X_mcRun2_asymptotic_v14-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "signal"),
  ("process_name_specific", "ttHToNonbb_M125"),
  ("nof_files",             43),
  ("nof_events",            3199629),
  ("use_it",                True),
  ("xsection",              0.215100),
  ("triggers",              [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/lucia/VHBBHeppyV24bis/ttHToNonbb_M125_13TeV_powheg_pythia8/VHBB_HEPPY_V24bis_ttHToNonbb_M125_13TeV_powheg_Py8__spr16MAv2-puspr16_HLT_80r2as_v14-v1/160911_224147"),
        ("selection", "*"),
        ("blacklist", [5, 13, 16, 18, 24, 28, 35]),
      ]),
    ]
  ),
])
