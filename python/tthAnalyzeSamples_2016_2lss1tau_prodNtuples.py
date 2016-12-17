from collections import OrderedDict as OD

samples_2016 = OD()

# file generated with command:
# check_broken -p /hdfs/local/karl/ttHNtupleProduction/2016/2016Dec16/ntuples/2lss_1tau -P -v -o

samples_2016["/DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DYJetsToLL_M-10to50"),
  ("nof_files",             369),
  ("nof_events",            30915886),
  ("use_it",                False),
  ("xsection",              18610.000000),
  ("genWeight",             False),
  ("triggers",              [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2016/2016Dec16/ntuples/2lss_1tau/DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/VHBB_HEPPY_V24bis_DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-amcatnloFXFX-Py8__spr16MAv2-puspr16_80r2as_2016_MAv2_v0-v1/160911_223234"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring16MiniAODv2-PUSpring16RAWAODSIM_reHLT_80X_mcRun2_asymptotic_v14_ext1-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DYJetsToLL_M-50"),
  ("nof_files",             657),
  ("nof_events",            91350867),
  ("use_it",                False),
  ("xsection",              5765.400000),
  ("genWeight",             False),
  ("triggers",              [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2016/2016Dec16/ntuples/2lss_1tau/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/VHBB_HEPPY_V24_DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-Py8__spr16MAv2-puspr16_HLT_80r2as_v14_ext1-v1/160909_070517"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/DoubleEG/Run2016B-PromptReco-v2/MINIAOD"] = OD([
  ("type",                  "data"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "DoubleEG_Run2016B_v2"),
  ("nof_files",             2614),
  ("nof_events",            233614277),
  ("use_it",                False),
  ("triggers",              [ "2e" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2016/2016Dec16/ntuples/2lss_1tau/DoubleEG/VHBB_HEPPY_D24_DoubleEG__Run2016B-PromptReco-v2/161006_213052"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/DoubleEG/Run2016C-PromptReco-v2/MINIAOD"] = OD([
  ("type",                  "data"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "DoubleEG_Run2016C"),
  ("nof_files",             869),
  ("nof_events",            233614277),
  ("use_it",                False),
  ("triggers",              [ "2e" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2016/2016Dec16/ntuples/2lss_1tau/DoubleEG/VHBB_HEPPY_D24_DoubleEG__Run2016C-PromptReco-v2/161006_213126"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/DoubleEG/Run2016D-PromptReco-v2/MINIAOD"] = OD([
  ("type",                  "data"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "DoubleEG_Run2016D"),
  ("nof_files",             1458),
  ("nof_events",            233614277),
  ("use_it",                False),
  ("triggers",              [ "2e" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2016/2016Dec16/ntuples/2lss_1tau/DoubleEG/VHBB_HEPPY_D24_DoubleEG__Run2016D-PromptReco-v2/161006_213202"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/DoubleMuon/Run2016B-PromptReco-v2/MINIAOD"] = OD([
  ("type",                  "data"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "DoubleMuon_Run2016B_v2"),
  ("nof_files",             2606),
  ("nof_events",            137988419),
  ("use_it",                False),
  ("triggers",              [ "2mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2016/2016Dec16/ntuples/2lss_1tau/DoubleMuon/VHBB_HEPPY_V24_DoubleMuon__Run2016B-PromptReco-v2/161006_213429"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/DoubleMuon/Run2016C-PromptReco-v2/MINIAOD"] = OD([
  ("type",                  "data"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "DoubleMuon_Run2016C"),
  ("nof_files",             869),
  ("nof_events",            137988419),
  ("use_it",                False),
  ("triggers",              [ "2mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2016/2016Dec16/ntuples/2lss_1tau/DoubleMuon/VHBB_HEPPY_V24_DoubleMuon__Run2016C-PromptReco-v2/161011_101655"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/DoubleMuon/Run2016D-PromptReco-v2/MINIAOD"] = OD([
  ("type",                  "data"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "DoubleMuon_Run2016D"),
  ("nof_files",             1458),
  ("nof_events",            137988419),
  ("use_it",                False),
  ("triggers",              [ "2mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2016/2016Dec16/ntuples/2lss_1tau/DoubleMuon/VHBB_HEPPY_V24_DoubleMuon__Run2016D-PromptReco-v2/161006_213542"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/MuonEG/Run2016B-PromptReco-v2/MINIAOD"] = OD([
  ("type",                  "data"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "MuonEG_Run2016B_v2"),
  ("nof_files",             2014),
  ("nof_events",            71270509),
  ("use_it",                False),
  ("triggers",              [ "1e1mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2016/2016Dec16/ntuples/2lss_1tau/MuonEG/VHBB_HEPPY_V24_MuonEG__Run2016B-PromptReco-v2/160920_122430"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/MuonEG/Run2016C-PromptReco-v2/MINIAOD"] = OD([
  ("type",                  "data"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "MuonEG_Run2016C"),
  ("nof_files",             696),
  ("nof_events",            71270509),
  ("use_it",                False),
  ("triggers",              [ "1e1mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2016/2016Dec16/ntuples/2lss_1tau/MuonEG/VHBB_HEPPY_V24_MuonEG__Run2016C-PromptReco-v2/160920_122508"),
        ("selection", "*"),
        ("blacklist", [556]),
      ]),
    ]
  ),
])
samples_2016["/MuonEG/Run2016D-PromptReco-v2/MINIAOD"] = OD([
  ("type",                  "data"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "MuonEG_Run2016D"),
  ("nof_files",             1024),
  ("nof_events",            71270509),
  ("use_it",                False),
  ("triggers",              [ "1e1mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2016/2016Dec16/ntuples/2lss_1tau/MuonEG/VHBB_HEPPY_V24_MuonEG__Run2016D-PromptReco-v2/160920_122552"),
        ("selection", "*"),
        ("blacklist", [16, 17, 18, 22, 423, 628, 789, 927]),
      ]),
    ]
  ),
])
samples_2016["/ST_s-channel_4f_leptonDecays_13TeV-amcatnlo-pythia8_TuneCUETP8M1/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "TT"),
  ("process_name_specific", "ST_s-channel_4f_leptonDecays"),
  ("nof_files",             24),
  ("nof_events",            1000000),
  ("use_it",                False),
  ("xsection",              3.750000),
  ("genWeight",             False),
  ("triggers",              [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2016/2016Dec16/ntuples/2lss_1tau/ST_s-channel_4f_leptonDecays_13TeV-amcatnlo-pythia8_TuneCUETP8M1/VHBB_HEPPY_V24_ST_s-channel_4f_leptonDecays_13TeV-amcatnlo-Py8_TuneCUETP8M1__spr16MAv2-puspr16_80r2as_2016_MAv2_v0-v1/160909_063446"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/ST_t-channel_antitop_4f_inclusiveDecays_13TeV-powhegV2-madspin-pythia8_TuneCUETP8M1/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "TT"),
  ("process_name_specific", "ST_t-channel_antitop_4f_inclusiveDecays"),
  ("nof_files",             520),
  ("nof_events",            19825855),
  ("use_it",                False),
  ("xsection",              70.690000),
  ("genWeight",             False),
  ("triggers",              [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2016/2016Dec16/ntuples/2lss_1tau/ST_t-channel_antitop_4f_inclusiveDecays_13TeV-powhegV2-madspin-pythia8_TuneCUETP8M1/VHBB_HEPPY_V24_ST_t-channel_antitop_4f_inclusiveDecays_13TeV-powhegV2-madspin-Py8_TuneCUETP8M1__spr16MAv2-puspr16_80r2as_2016_MAv2_v0-v1/160909_063650"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/ST_t-channel_top_4f_inclusiveDecays_13TeV-powhegV2-madspin-pythia8_TuneCUETP8M1/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "TT"),
  ("process_name_specific", "ST_t-channel_top_4f_inclusiveDecays"),
  ("nof_files",             324),
  ("nof_events",            32532748),
  ("use_it",                False),
  ("xsection",              70.690000),
  ("genWeight",             False),
  ("triggers",              [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2016/2016Dec16/ntuples/2lss_1tau/ST_t-channel_top_4f_inclusiveDecays_13TeV-powhegV2-madspin-pythia8_TuneCUETP8M1/VHBB_HEPPY_V24_ST_t-channel_top_4f_inclusiveDecays_13TeV-powhegV2-madspin-Py8_TuneCUETP8M1__spr16MAv2-puspr16_80r2as_2016_MAv2_v0-v1/160909_070435"),
        ("selection", "*"),
        ("blacklist", [159, 246]),
      ]),
    ]
  ),
])
samples_2016["/ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "TT"),
  ("process_name_specific", "ST_tW_antitop_5f_inclusiveDecays"),
  ("nof_files",             26),
  ("nof_events",            985000),
  ("use_it",                False),
  ("xsection",              35.600000),
  ("genWeight",             False),
  ("triggers",              [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2016/2016Dec16/ntuples/2lss_1tau/ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1/VHBB_HEPPY_V24_ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-Py8_TuneCUETP8M1__spr16MAv2-puspr16_80r2as_2016_MAv2_v0-v1/160909_063328"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/ST_tW_top_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v2/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "TT"),
  ("process_name_specific", "ST_tW_top_5f_inclusiveDecays"),
  ("nof_files",             25),
  ("nof_events",            998400),
  ("use_it",                False),
  ("xsection",              35.600000),
  ("genWeight",             False),
  ("triggers",              [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2016/2016Dec16/ntuples/2lss_1tau/ST_tW_top_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1/VHBB_HEPPY_V24_ST_tW_top_5f_inclusiveDecays_13TeV-powheg-Py8_TuneCUETP8M1__spr16MAv2-puspr16_80r2as_2016_MAv2_v0-v2/160909_063526"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/SingleElectron/Run2016B-PromptReco-v2/MINIAOD"] = OD([
  ("type",                  "data"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "SingleElectron_Run2016B_v2"),
  ("nof_files",             3209),
  ("nof_events",            491602510),
  ("use_it",                False),
  ("triggers",              [ "1e" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2016/2016Dec16/ntuples/2lss_1tau/SingleElectron/VHBB_HEPPY_V24_SingleElectron__Run2016B-PromptReco-v2/160910_204523"),
        ("selection", "*"),
        ("blacklist", [819]),
      ]),
    ]
  ),
])
samples_2016["/SingleElectron/Run2016C-PromptReco-v2/MINIAOD"] = OD([
  ("type",                  "data"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "SingleElectron_Run2016C"),
  ("nof_files",             1029),
  ("nof_events",            491602510),
  ("use_it",                False),
  ("triggers",              [ "1e" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2016/2016Dec16/ntuples/2lss_1tau/SingleElectron/VHBB_HEPPY_V24_SingleElectron__Run2016C-PromptReco-v2/160910_204634"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/SingleElectron/Run2016D-PromptReco-v2/MINIAOD"] = OD([
  ("type",                  "data"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "SingleElectron_Run2016D"),
  ("nof_files",             1545),
  ("nof_events",            491602510),
  ("use_it",                False),
  ("triggers",              [ "1e" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2016/2016Dec16/ntuples/2lss_1tau/SingleElectron/VHBB_HEPPY_V24_SingleElectron__Run2016D-PromptReco-v2/160910_204714"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/SingleMuon/Run2016B-PromptReco-v2/MINIAOD"] = OD([
  ("type",                  "data"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "SingleMuon_Run2016B_v2"),
  ("nof_files",             3023),
  ("nof_events",            324808459),
  ("use_it",                False),
  ("triggers",              [ "1mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2016/2016Dec16/ntuples/2lss_1tau/SingleMuon/VHBB_HEPPY_V24_SingleMuon__Run2016B-PromptReco-v2/160910_205020"),
        ("selection", "*"),
        ("blacklist", [2173]),
      ]),
    ]
  ),
])
samples_2016["/SingleMuon/Run2016C-PromptReco-v2/MINIAOD"] = OD([
  ("type",                  "data"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "SingleMuon_Run2016C"),
  ("nof_files",             1044),
  ("nof_events",            324808459),
  ("use_it",                False),
  ("triggers",              [ "1mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2016/2016Dec16/ntuples/2lss_1tau/SingleMuon/VHBB_HEPPY_V24_SingleMuon__Run2016C-PromptReco-v2/160910_205128"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/SingleMuon/Run2016D-PromptReco-v2/MINIAOD"] = OD([
  ("type",                  "data"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "SingleMuon_Run2016D"),
  ("nof_files",             1535),
  ("nof_events",            324808459),
  ("use_it",                False),
  ("triggers",              [ "1mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2016/2016Dec16/ntuples/2lss_1tau/SingleMuon/VHBB_HEPPY_V24_SingleMuon__Run2016D-PromptReco-v2/160910_205212"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/TGJets_TuneCUETP8M1_13TeV_amcatnlo_madspin_pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0_ext1-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "Rares"),
  ("process_name_specific", "TGJets_ext1"),
  ("nof_files",             19),
  ("nof_events",            1535543),
  ("use_it",                False),
  ("xsection",              2.967000),
  ("genWeight",             False),
  ("triggers",              [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2016/2016Dec16/ntuples/2lss_1tau/TGJets_TuneCUETP8M1_13TeV_amcatnlo_madspin_pythia8/VHBB_HEPPY_V24bis_TGJets_TuneCUETP8M1_13TeV_amcatnlo_madspin_Py8__spr16MAv2-puspr16_80r2as_2016_MAv2_v0_ext1-v1/160911_224639"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/TTGJets_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "Rares"),
  ("process_name_specific", "TTGJets"),
  ("nof_files",             56),
  ("nof_events",            4301632),
  ("use_it",                False),
  ("xsection",              3.697000),
  ("genWeight",             False),
  ("triggers",              [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2016/2016Dec16/ntuples/2lss_1tau/TTGJets_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/VHBB_HEPPY_V24bis_TTGJets_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-Py8__spr16MAv2-puspr16_80r2as_2016_MAv2_v0-v1/160911_223929"),
        ("selection", "*"),
        ("blacklist", [1, 6, 14, 25, 39, 52]),
      ]),
    ]
  ),
])
samples_2016["/TTJets_DiLept_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v4/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "TT"),
  ("process_name_specific", "TTJets_DiLept"),
  ("nof_files",             70),
  ("nof_events",            30487742),
  ("use_it",                False),
  ("xsection",              87.300000),
  ("genWeight",             False),
  ("triggers",              [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2016/2016Dec16/ntuples/2lss_1tau/TTJets_DiLept_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/VHBB_HEPPY_V24bis_TTJets_DiLept_TuneCUETP8M1_13TeV-madgraphMLM-Py8__spr16MAv2-puspr16_80r2as_2016_MAv2_v0-v4/160911_223748"),
        ("selection", "*"),
        ("blacklist", [47, 59]),
      ]),
    ]
  ),
])
samples_2016["/TTJets_DiLept_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0_ext1-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "TT"),
  ("process_name_specific", "TTJets_DiLept_ext1"),
  ("nof_files",             278),
  ("nof_events",            30487742),
  ("use_it",                False),
  ("xsection",              87.300000),
  ("genWeight",             False),
  ("triggers",              [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2016/2016Dec16/ntuples/2lss_1tau/TTJets_DiLept_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/VHBB_HEPPY_V24bis_TTJets_DiLept_TuneCUETP8M1_13TeV-madgraphMLM-Py8__spr16MAv2-puspr16_80r2as_2016_MAv2_v0_ext1-v1/160911_223310"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/TTJets_SingleLeptFromT_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "TT"),
  ("process_name_specific", "TTJets_SingleLeptFromT"),
  ("nof_files",             111),
  ("nof_events",            18165634),
  ("use_it",                False),
  ("xsection",              182.000000),
  ("genWeight",             False),
  ("triggers",              [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2016/2016Dec16/ntuples/2lss_1tau/TTJets_SingleLeptFromT_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/VHBB_HEPPY_V24bis_TTJets_SingleLeptFromT_TuneCUETP8M1_13TeV-madgraphMLM-Py8__spr16MAv2-puspr16_80r2as_2016_MAv2_v0-v1/160911_223601"),
        ("selection", "*"),
        ("blacklist", [33]),
      ]),
    ]
  ),
])
samples_2016["/TTJets_SingleLeptFromT_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0_ext1-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "TT"),
  ("process_name_specific", "TTJets_SingleLeptFromT_ext1"),
  ("nof_files",             229),
  ("nof_events",            18165634),
  ("use_it",                False),
  ("xsection",              182.000000),
  ("genWeight",             False),
  ("triggers",              [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2016/2016Dec16/ntuples/2lss_1tau/TTJets_SingleLeptFromT_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/VHBB_HEPPY_V24bis_TTJets_SingleLeptFromT_TuneCUETP8M1_13TeV-madgraphMLM-Py8__spr16MAv2-puspr16_80r2as_2016_MAv2_v0_ext1-v1/160911_223200"),
        ("selection", "*"),
        ("blacklist", [1, 3, 5, 6, 7, 8, 11, 13, 14, 15, 16, 17, 18, 19, 20, 22, 23, 24, 25, 26, 28, 29, 30, 31, 32, 33, 34, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 57, 58, 59, 61, 62, 64, 65, 66, 67, 68, 70, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 90, 92, 93, 94, 95, 96, 97, 98, 99, 101, 102, 106, 107, 108, 109, 110, 112, 113, 114, 116, 117, 118, 119, 121, 123, 124, 125, 126, 127, 128, 129, 130, 132, 136, 137, 138, 139, 140, 141, 142, 143, 145, 146, 147, 148, 149, 150, 152, 153, 154, 156, 157, 158, 159, 160, 161, 162, 164, 167, 168, 169, 170, 172, 173, 176, 177, 178, 179, 180, 182, 183, 188, 189, 190, 191, 192, 194, 196, 197, 199, 200, 201, 202, 204, 205, 206, 207, 208, 212, 213, 215, 217, 218, 219, 220, 221, 222, 223, 227]),
      ]),
    ]
  ),
])
samples_2016["/TTJets_SingleLeptFromTbar_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "TT"),
  ("process_name_specific", "TTJets_SingleLeptFromTbar"),
  ("nof_files",             137),
  ("nof_events",            60309864),
  ("use_it",                False),
  ("xsection",              182.000000),
  ("genWeight",             False),
  ("triggers",              [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2016/2016Dec16/ntuples/2lss_1tau/TTJets_SingleLeptFromTbar_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/VHBB_HEPPY_V24bis_TTJets_SingleLeptFromTbar_TuneCUETP8M1_13TeV-madgraphMLM-Py8__spr16MAv2-puspr16_80r2as_2016_MAv2_v0-v1/160911_223528"),
        ("selection", "*"),
        ("blacklist", [49, 54]),
      ]),
    ]
  ),
])
samples_2016["/TTJets_SingleLeptFromTbar_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0_ext1-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "TT"),
  ("process_name_specific", "TTJets_SingleLeptFromTbar_ext1"),
  ("nof_files",             529),
  ("nof_events",            60309864),
  ("use_it",                False),
  ("xsection",              182.000000),
  ("genWeight",             False),
  ("triggers",              [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2016/2016Dec16/ntuples/2lss_1tau/TTJets_SingleLeptFromTbar_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/VHBB_HEPPY_V24bis_TTJets_SingleLeptFromTbar_TuneCUETP8M1_13TeV-madgraphMLM-Py8__spr16MAv2-puspr16_80r2as_2016_MAv2_v0_ext1-v1/160911_223125"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/TTTT_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0_ext1-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "Rares"),
  ("process_name_specific", "TTTT"),
  ("nof_files",             11),
  ("nof_events",            989025),
  ("use_it",                False),
  ("xsection",              0.009103),
  ("genWeight",             False),
  ("triggers",              [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2016/2016Dec16/ntuples/2lss_1tau/TTTT_TuneCUETP8M1_13TeV-amcatnlo-pythia8/VHBB_HEPPY_V24bis_TTTT_TuneCUETP8M1_13TeV-amcatnlo-Py8__spr16MAv2-puspr16_80r2as_2016_MAv2_v0_ext1-v1/160911_224827"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/RunIISpring16MiniAODv2-premix_withHLT_80X_mcRun2_asymptotic_v14-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "TTW"),
  ("process_name_specific", "TTWJetsToLNu_v14-v1"),
  ("nof_files",             6),
  ("nof_events",            2657194),
  ("use_it",                False),
  ("xsection",              0.204300),
  ("genWeight",             False),
  ("triggers",              [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2016/2016Dec16/ntuples/2lss_1tau/TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/VHBB_HEPPY_V24bis_TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-Py8__spr16MAv2-premix_withHLT_80r2as_v14-v1/161005_140021"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/RunIISpring16MiniAODv2-premix_withHLT_80X_mcRun2_asymptotic_v14_ext1-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "TTW"),
  ("process_name_specific", "TTWJetsToLNu_v14_ext1-v1"),
  ("nof_files",             46),
  ("nof_events",            2657194),
  ("use_it",                False),
  ("xsection",              0.204300),
  ("genWeight",             False),
  ("triggers",              [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2016/2016Dec16/ntuples/2lss_1tau/TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/VHBB_HEPPY_V24bis_TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-Py8__spr16MAv2-premix_withHLT_80r2as_v14_ext1-v1/161005_140103"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "TTW"),
  ("process_name_specific", "TTWJetsToLNu_v0-v1"),
  ("nof_files",             4),
  ("nof_events",            2657194),
  ("use_it",                False),
  ("xsection",              0.204300),
  ("genWeight",             False),
  ("triggers",              [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2016/2016Dec16/ntuples/2lss_1tau/TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/VHBB_HEPPY_V24bis_TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-Py8__spr16MAv2-puspr16_80r2as_2016_MAv2_v0-v1/160911_225800"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/TTW/spring16DR80v6aMiniAODv1/FASTSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "TTW"),
  ("process_name_specific", "TTW_Fastsim"),
  ("nof_files",             162),
  ("nof_events",            8362991),
  ("use_it",                False),
  ("xsection",              0.204300),
  ("genWeight",             False),
  ("triggers",              [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2016/2016Dec16/ntuples/2lss_1tau/TTW_FastSim"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISpring16MiniAODv2-premix_withHLT_80X_mcRun2_asymptotic_v14_ext1-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "TTZ"),
  ("process_name_specific", "TTZToLLNuNu_M-10_ext1"),
  ("nof_files",             24),
  ("nof_events",            2256848),
  ("use_it",                False),
  ("xsection",              0.252900),
  ("genWeight",             False),
  ("triggers",              [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2016/2016Dec16/ntuples/2lss_1tau/TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-pythia8/VHBB_HEPPY_V24bis_TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-Py8__spr16MAv2-premix_withHLT_80r2as_v14_ext1-v1/160911_224606"),
        ("selection", "*"),
        ("blacklist", [16]),
      ]),
    ]
  ),
])
samples_2016["/TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "TTZ"),
  ("process_name_specific", "TTZToLLNuNu_M-10"),
  ("nof_files",             6),
  ("nof_events",            2256848),
  ("use_it",                False),
  ("xsection",              0.252900),
  ("genWeight",             False),
  ("triggers",              [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2016/2016Dec16/ntuples/2lss_1tau/TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-pythia8/VHBB_HEPPY_V24bis_TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-Py8__spr16MAv2-puspr16_80r2as_2016_MAv2_v0-v1/160911_225425"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/TT_TuneCUETP8M1_13TeV-powheg-pythia8/RunIISpring16MiniAODv1-PUSpring16_80X_mcRun2_asymptotic_2016_v3_ext4-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "TT"),
  ("process_name_specific", "TT_ext4"),
  ("nof_files",             9602),
  ("nof_events",            275307526),
  ("use_it",                False),
  ("xsection",              831.760000),
  ("genWeight",             False),
  ("triggers",              [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2016/2016Dec16/ntuples/2lss_1tau/TT_TuneCUETP8M1_13TeV-powheg-pythia8/VHBB_HEPPY_D24_TT_TuneCUETP8M1_13TeV-powheg-Py8__spr16MiniAODv1-puspr16_80r2as_2016_v3_ext4-v1/161107_100027"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/TT_TuneCUETP8M1_13TeV-powheg-pythia8/RunIISpring16MiniAODv1-PUSpring16_80X_mcRun2_asymptotic_2016_v3_ext3-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "TT"),
  ("process_name_specific", "TT_ext3"),
  ("nof_files",             2124),
  ("nof_events",            275307526),
  ("use_it",                False),
  ("xsection",              831.760000),
  ("genWeight",             False),
  ("triggers",              [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2016/2016Dec16/ntuples/2lss_1tau/TT_TuneCUETP8M1_13TeV-powheg-pythia8/VHBB_HEPPY_V24_TT_TuneCUETP8M1_13TeV-powheg-Py8__spr16MAv2-puspr16_HLT_80r2as_v14_ext3-v1/160909_063406"),
        ("selection", "*"),
        ("blacklist", [600]),
      ]),
    ]
  ),
])
samples_2016["/WGToLNuG_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "Rares"),
  ("process_name_specific", "WGToLNuG"),
  ("nof_files",             75),
  ("nof_events",            5916785),
  ("use_it",                False),
  ("xsection",              585.800000),
  ("genWeight",             False),
  ("triggers",              [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2016/2016Dec16/ntuples/2lss_1tau/WGToLNuG_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/VHBB_HEPPY_V24bis_WGToLNuG_TuneCUETP8M1_13TeV-madgraphMLM-Py8__spr16MAv2-puspr16_80r2as_2016_MAv2_v0-v1/160911_223823"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/WJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISpring16MiniAODv2-PUSpring16RAWAODSIM_reHLT_80X_mcRun2_asymptotic_v14_ext1-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "EWK"),
  ("process_name_specific", "WJetsToLNu"),
  ("nof_files",             306),
  ("nof_events",            47502020),
  ("use_it",                False),
  ("xsection",              61526.700000),
  ("genWeight",             False),
  ("triggers",              [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2016/2016Dec16/ntuples/2lss_1tau/WJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/VHBB_HEPPY_V24_WJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-Py8__spr16MAv2-puspr16_HLT_80r2as_v14_ext1-v1/160909_070745"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/WWTo2L2Nu_13TeV-powheg/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "EWK"),
  ("process_name_specific", "WWTo2L2Nu"),
  ("nof_files",             26),
  ("nof_events",            1996600),
  ("use_it",                False),
  ("xsection",              10.481000),
  ("genWeight",             False),
  ("triggers",              [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2016/2016Dec16/ntuples/2lss_1tau/WWTo2L2Nu_13TeV-powheg/VHBB_HEPPY_V24bis_WWTo2L2Nu_13TeV-powheg__spr16MAv2-puspr16_80r2as_2016_MAv2_v0-v1/160911_224455"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/WW_DoubleScattering_13TeV-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "Rares"),
  ("process_name_specific", "WW_DoubleScattering"),
  ("nof_files",             12),
  ("nof_events",            844954),
  ("use_it",                False),
  ("xsection",              1.640000),
  ("genWeight",             False),
  ("triggers",              [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2016/2016Dec16/ntuples/2lss_1tau/WW_DoubleScattering_13TeV-pythia8/VHBB_HEPPY_V24bis_WW_DoubleScattering_13TeV-Py8__spr16MAv2-puspr16_80r2as_2016_MAv2_v0-v1/160911_225013"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/WZTo3LNu_TuneCUETP8M1_13TeV-powheg-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "EWK"),
  ("process_name_specific", "WZTo3LNu"),
  ("nof_files",             26),
  ("nof_events",            2000000),
  ("use_it",                False),
  ("xsection",              4.102000),
  ("genWeight",             False),
  ("triggers",              [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2016/2016Dec16/ntuples/2lss_1tau/WZTo3LNu_TuneCUETP8M1_13TeV-powheg-pythia8/VHBB_HEPPY_V24bis_WZTo3LNu_TuneCUETP8M1_13TeV-powheg-Py8__spr16MAv2-puspr16_80r2as_2016_MAv2_v0-v1/160911_224418"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/WZZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "Rares"),
  ("process_name_specific", "WZZ"),
  ("nof_files",             3),
  ("nof_events",            249800),
  ("use_it",                False),
  ("xsection",              0.055650),
  ("genWeight",             False),
  ("triggers",              [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2016/2016Dec16/ntuples/2lss_1tau/WZZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8/VHBB_HEPPY_V24bis_WZZ_TuneCUETP8M1_13TeV-amcatnlo-Py8__spr16MAv2-puspr16_80r2as_2016_MAv2_v0-v1/160911_225836"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/WpWpJJ_EWK-QCD_TuneCUETP8M1_13TeV-madgraph-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v2/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "Rares"),
  ("process_name_specific", "WpWpJJ_EWK-QCD"),
  ("nof_files",             8),
  ("nof_events",            138235),
  ("use_it",                False),
  ("xsection",              0.037110),
  ("genWeight",             False),
  ("triggers",              [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2016/2016Dec16/ntuples/2lss_1tau/WpWpJJ_EWK-QCD_TuneCUETP8M1_13TeV-madgraph-pythia8/VHBB_HEPPY_V24bis_WpWpJJ_EWK-QCD_TuneCUETP8M1_13TeV-madgraph-Py8__spr16MAv2-puspr16_80r2as_2016_MAv2_v0-v2/160911_225910"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "Rares"),
  ("process_name_specific", "ZGTo2LG"),
  ("nof_files",             55),
  ("nof_events",            14616963),
  ("use_it",                False),
  ("xsection",              131.300000),
  ("genWeight",             False),
  ("triggers",              [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2016/2016Dec16/ntuples/2lss_1tau/ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/VHBB_HEPPY_V24bis_ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-Py8__spr16MAv2-puspr16_80r2as_2016_MAv2_v0-v1/160911_224112"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0_ext1-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "Rares"),
  ("process_name_specific", "ZGTo2LG_ext1"),
  ("nof_files",             96),
  ("nof_events",            14616963),
  ("use_it",                False),
  ("xsection",              131.300000),
  ("genWeight",             False),
  ("triggers",              [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2016/2016Dec16/ntuples/2lss_1tau/ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/VHBB_HEPPY_V24bis_ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-Py8__spr16MAv2-puspr16_80r2as_2016_MAv2_v0_ext1-v1/160911_223418"),
        ("selection", "*"),
        ("blacklist", [25, 27, 28, 47, 48, 55, 56, 63, 64, 74, 75, 77, 78, 79, 80]),
      ]),
    ]
  ),
])
samples_2016["/ZZTo4L_13TeV-amcatnloFXFX-pythia8/RunIISpring16MiniAODv2-PUSpring16RAWAODSIM_reHLT_80X_mcRun2_asymptotic_v14-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "EWK"),
  ("process_name_specific", "ZZTo4L"),
  ("nof_files",             50),
  ("nof_events",            7878358),
  ("use_it",                False),
  ("xsection",              1.256000),
  ("genWeight",             False),
  ("triggers",              [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2016/2016Dec16/ntuples/2lss_1tau/ZZTo4L_13TeV-amcatnloFXFX-pythia8/VHBB_HEPPY_V24bis_ZZTo4L_13TeV-amcatnloFXFX-Py8__spr16MAv2-puspr16_HLT_80r2as_v14-v1/160911_223636"),
        ("selection", "*"),
        ("blacklist", [11, 12, 14, 16, 24, 25, 29, 31, 35]),
      ]),
    ]
  ),
])
samples_2016["/tZq_ll_4f_13TeV-amcatnlo-pythia8_TuneCUETP8M1/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "Rares"),
  ("process_name_specific", "tZq_ll_4f"),
  ("nof_files",             35),
  ("nof_events",            2973639),
  ("use_it",                False),
  ("xsection",              0.075800),
  ("genWeight",             False),
  ("triggers",              [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2016/2016Dec16/ntuples/2lss_1tau/tZq_ll_4f_13TeV-amcatnlo-pythia8_TuneCUETP8M1/VHBB_HEPPY_V24bis_tZq_ll_4f_13TeV-amcatnlo-Py8_TuneCUETP8M1__spr16MAv2-puspr16_80r2as_2016_MAv2_v0-v1/160911_224340"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/RunIISpring16MiniAODv2-PUSpring16RAWAODSIM_reHLT_80X_mcRun2_asymptotic_v14_ext1-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "signal"),
  ("process_name_specific", "ttHJetToNonbb_M125"),
  ("nof_files",             109),
  ("nof_events",            6228310),
  ("use_it",                True),
  ("xsection",              0.215100),
  ("genWeight",             True),
  ("triggers",              [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2016/2016Dec16/ntuples/2lss_1tau/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/VHBB_HEPPY_V24bis_ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_Py8_mWCutfix__spr16MAv2-puspr16_HLT_80r2as_v14_ext1-v1/160911_223711"),
        ("selection", "*"),
        ("blacklist", [10, 11, 14, 16, 20, 22, 23, 26, 29, 30, 31, 33, 34, 38, 39, 43, 44, 45, 51, 54, 57, 62, 63, 64, 66, 67, 68, 70, 71, 72, 73, 75, 76, 77, 79, 80, 81, 89, 98, 99]),
      ]),
    ]
  ),
])
