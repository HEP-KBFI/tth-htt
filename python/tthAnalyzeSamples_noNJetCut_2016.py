from collections import OrderedDict as OD

samples_no_njet_cut_2016 = OD()

samples_no_njet_cut_2016["/DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DYJetsToLL_M-10to50"),
  ("nof_files",             1242),
  ("nof_events",            32284243),
  ("use_it",                True),
  ("xsection",              18610.000000),
  ("triggers",              [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyD24_v3/DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/VHBB_HEPPY_D24_DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-amcatnloFXFX-Py8__spr16MAv2-puspr16_80r2as_2016_MAv2_v0-v1/161011_113321"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_no_njet_cut_2016["/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring16MiniAODv2-PUSpring16RAWAODSIM_reHLT_80X_mcRun2_asymptotic_v14_ext1-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DYJetsToLL_M-50"),
  ("nof_files",             9213),
  ("nof_events",            90542966),
  ("use_it",                True),
  ("xsection",              5765.400000),
  ("triggers",              [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyD24_v3/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/VHBB_HEPPY_D24_DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-Py8__spr16MAv2-puspr16_HLT_80r2as_v14_ext1-v1/161011_130620"),
        ("selection", "*"),
        ("blacklist", [1027, 6240, 6241, 6242, 6243, 6244, 6245, 6246, 6247, 6249, 6251, 6252, 6253, 6255, 7813, 7899, 7901, 7902, 7903, 7905, 7906, 8030, 8031, 8033, 8034, 8036, 8037, 8039, 8040, 8041, 8043, 8044, 8223, 8285, 8286, 8289, 8290, 8291, 8292, 8293, 8295, 8296, 8297, 8298, 8360, 8361, 8364, 8366, 8367, 8368, 8369, 8370, 8371, 8372, 8373, 8553, 8555, 8556, 8557, 8558, 8559, 8561, 8563, 8564, 8565, 8566, 8567, 8631, 8896, 8897, 8899, 8901, 8903, 8904, 8906, 8907, 8911, 8912, 8913, 8914, 8915]),
      ]),
    ]
  ),
])

samples_no_njet_cut_2016["/DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DYJetsToLL_M-10to50"),
  ("nof_files",             5260),
  ("nof_events",            30904155),
  ("use_it",                True),
  ("xsection",              18610.000000),
  ("triggers",              [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyD24_v4/DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/VHBB_HEPPY_D24_DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-amcatnloFXFX-Py8__spr16MAv2-puspr16_80r2as_2016_MAv2_v0-v1/161012_122919"),
        ("selection", "*"),
        ("blacklist", [786, 1490]),
      ]),
    ]
  ),
])
samples_no_njet_cut_2016["/DoubleEG/Run2016B-PromptReco-v2/MINIAOD"] = OD([
  ("type",                  "data"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "DoubleEG_Run2016B_v2"),
  ("nof_files",             8588),
  ("nof_events",            246269289),
  ("use_it",                True),
  ("triggers",              [ "2e" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyD24_v4/DoubleEG/VHBB_HEPPY_D24_DoubleEG__Run2016B-PromptReco-v2/161012_152804"),
        ("selection", "*"),
        ("blacklist", [2066, 2347]),
      ]),
    ]
  ),
])
samples_no_njet_cut_2016["/DoubleEG/Run2016C-PromptReco-v2/MINIAOD"] = OD([
  ("type",                  "data"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "DoubleEG_Run2016C"),
  ("nof_files",             5652),
  ("nof_events",            246269289),
  ("use_it",                True),
  ("triggers",              [ "2e" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyD24_v4/DoubleEG/VHBB_HEPPY_D24_DoubleEG__Run2016C-PromptReco-v2/161012_151255"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_no_njet_cut_2016["/DoubleEG/Run2016D-PromptReco-v2/MINIAOD"] = OD([
  ("type",                  "data"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "DoubleEG_Run2016D"),
  ("nof_files",             5950),
  ("nof_events",            246269289),
  ("use_it",                True),
  ("triggers",              [ "2e" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyD24_v4/DoubleEG/VHBB_HEPPY_D24_DoubleEG__Run2016D-PromptReco-v2/161012_151542"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_no_njet_cut_2016["/ST_s-channel_4f_leptonDecays_13TeV-amcatnlo-pythia8_TuneCUETP8M1/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "TT"),
  ("process_name_specific", "ST_s-channel_4f_leptonDecays"),
  ("nof_files",             167),
  ("nof_events",            1000000),
  ("use_it",                True),
  ("xsection",              3.750000),
  ("triggers",              [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyD24_v4/ST_s-channel_4f_leptonDecays_13TeV-amcatnlo-pythia8_TuneCUETP8M1/VHBB_HEPPY_D24_ST_s-channel_4f_leptonDecays_13TeV-amcatnlo-Py8_TuneCUETP8M1__spr16MAv2-puspr16_80r2as_2016_MAv2_v0-v1/161012_120846"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_no_njet_cut_2016["/ST_t-channel_antitop_4f_inclusiveDecays_13TeV-powhegV2-madspin-pythia8_TuneCUETP8M1/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "TT"),
  ("process_name_specific", "ST_t-channel_antitop_4f_inclusiveDecays"),
  ("nof_files",             3356),
  ("nof_events",            19825855),
  ("use_it",                True),
  ("xsection",              70.690000),
  ("triggers",              [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyD24_v4/ST_t-channel_antitop_4f_inclusiveDecays_13TeV-powhegV2-madspin-pythia8_TuneCUETP8M1/VHBB_HEPPY_D24_ST_t-channel_antitop_4f_inclusiveDecays_13TeV-powhegV2-madspin-Py8_TuneCUETP8M1__spr16MAv2-puspr16_80r2as_2016_MAv2_v0-v1/161012_121015"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_no_njet_cut_2016["/ST_t-channel_top_4f_inclusiveDecays_13TeV-powhegV2-madspin-pythia8_TuneCUETP8M1/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "TT"),
  ("process_name_specific", "ST_t-channel_top_4f_inclusiveDecays"),
  ("nof_files",             5556),
  ("nof_events",            32808300),
  ("use_it",                True),
  ("xsection",              70.690000),
  ("triggers",              [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyD24_v4/ST_t-channel_top_4f_inclusiveDecays_13TeV-powhegV2-madspin-pythia8_TuneCUETP8M1/VHBB_HEPPY_D24_ST_t-channel_top_4f_inclusiveDecays_13TeV-powhegV2-madspin-Py8_TuneCUETP8M1__spr16MAv2-puspr16_80r2as_2016_MAv2_v0-v1/161012_121135"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_no_njet_cut_2016["/ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "TT"),
  ("process_name_specific", "ST_tW_antitop_5f_inclusiveDecays"),
  ("nof_files",             165),
  ("nof_events",            985000),
  ("use_it",                True),
  ("xsection",              35.600000),
  ("triggers",              [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyD24_v4/ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1/VHBB_HEPPY_D24_ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-Py8_TuneCUETP8M1__spr16MAv2-puspr16_80r2as_2016_MAv2_v0-v1/161012_121258"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_no_njet_cut_2016["/ST_tW_top_5f_NoFullyHadronicDecays_13TeV-powheg_TuneCUETP8M1/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "TT"),
  ("process_name_specific", "ST_tW_top_5f_NoFullyHadronicDecays"),
  ("nof_files",             906),
  ("nof_events",            5405726),
  ("use_it",                True),
  ("xsection",              35.600000),
  ("triggers",              [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyD24_v4/ST_tW_top_5f_NoFullyHadronicDecays_13TeV-powheg_TuneCUETP8M1/VHBB_HEPPY_D24_ST_tW_top_5f_NoFullyHadronicDecays_13TeV-powheg_TuneCUETP8M1__spr16MAv2-puspr16_80r2as_2016_MAv2_v0-v1/161012_121422"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_no_njet_cut_2016["/SingleElectron/Run2016B-PromptReco-v2/MINIAOD"] = OD([
  ("type",                  "data"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "SingleElectron_Run2016B_v2"),
  ("nof_files",             9638),
  ("nof_events",            246175191),
  ("use_it",                True),
  ("triggers",              [ "1e" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyD24_v4/SingleElectron/VHBB_HEPPY_D24_SingleElectron__Run2016B-PromptReco-v2/161012_154325"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_no_njet_cut_2016["/SingleElectron/Run2016C-PromptReco-v2/MINIAOD"] = OD([
  ("type",                  "data"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "SingleElectron_Run2016C"),
  ("nof_files",             6581),
  ("nof_events",            97292079),
  ("use_it",                True),
  ("triggers",              [ "1e" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyD24_v4/SingleElectron/VHBB_HEPPY_D24_SingleElectron__Run2016C-PromptReco-v2/161012_153119"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_no_njet_cut_2016["/SingleElectron/Run2016D-PromptReco-v2/MINIAOD"] = OD([
  ("type",                  "data"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "SingleElectron_Run2016D"),
  ("nof_files",             9715),
  ("nof_events",            148167727),
  ("use_it",                True),
  ("triggers",              [ "1e" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyD24_v4/SingleElectron/VHBB_HEPPY_D24_SingleElectron__Run2016D-PromptReco-v2/161012_153251"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])

samples_no_njet_cut_2016["/TTJets_DiLept_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v4/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "TT"),
  ("process_name_specific", "TTJets_DiLept"),
  ("nof_files",             1028),
  ("nof_events",            30682233),
  ("use_it",                True),
  ("xsection",              87.300000),
  ("triggers",              [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyD24_v4/TTJets_DiLept_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/VHBB_HEPPY_D24_TTJets_DiLept_TuneCUETP8M1_13TeV-madgraphMLM-Py8__spr16MAv2-puspr16_80r2as_2016_MAv2_v0-v4/161012_120503"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_no_njet_cut_2016["/TTJets_DiLept_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0_ext1-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "TT"),
  ("process_name_specific", "TTJets_DiLept_ext1"),
  ("nof_files",             4198),
  ("nof_events",            30682233),
  ("use_it",                True),
  ("xsection",              87.300000),
  ("triggers",              [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyD24_v4/TTJets_DiLept_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/VHBB_HEPPY_D24_TTJets_DiLept_TuneCUETP8M1_13TeV-madgraphMLM-Py8__spr16MAv2-puspr16_80r2as_2016_MAv2_v0_ext1-v1/161012_120218"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_no_njet_cut_2016["/TTJets_SingleLeptFromT_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "TT"),
  ("process_name_specific", "TTJets_SingleLeptFromT"),
  ("nof_files",             1604),
  ("nof_events",            53057043),
  ("use_it",                True),
  ("xsection",              182.000000),
  ("triggers",              [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyD24_v4/TTJets_SingleLeptFromT_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/VHBB_HEPPY_D24_TTJets_SingleLeptFromT_TuneCUETP8M1_13TeV-madgraphMLM-Py8__spr16MAv2-puspr16_80r2as_2016_MAv2_v0-v1/161012_120407"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_no_njet_cut_2016["/TTJets_SingleLeptFromT_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0_ext1-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "TT"),
  ("process_name_specific", "TTJets_SingleLeptFromT_ext1"),
  ("nof_files",             7369),
  ("nof_events",            53057043),
  ("use_it",                True),
  ("xsection",              182.000000),
  ("triggers",              [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyD24_v4/TTJets_SingleLeptFromT_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/VHBB_HEPPY_D24_TTJets_SingleLeptFromT_TuneCUETP8M1_13TeV-madgraphMLM-Py8__spr16MAv2-puspr16_80r2as_2016_MAv2_v0_ext1-v1/161012_120114"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_no_njet_cut_2016["/TTJets_SingleLeptFromTbar_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "TT"),
  ("process_name_specific", "TTJets_SingleLeptFromTbar"),
  ("nof_files",             2022),
  ("nof_events",            60494823),
  ("use_it",                True),
  ("xsection",              182.000000),
  ("triggers",              [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyD24_v4/TTJets_SingleLeptFromTbar_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/VHBB_HEPPY_D24_TTJets_SingleLeptFromTbar_TuneCUETP8M1_13TeV-madgraphMLM-Py8__spr16MAv2-puspr16_80r2as_2016_MAv2_v0-v1/161012_120312"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_no_njet_cut_2016["/TTJets_SingleLeptFromTbar_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0_ext1-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "TT"),
  ("process_name_specific", "TTJets_SingleLeptFromTbar_ext1"),
  ("nof_files",             8254),
  ("nof_events",            60494823),
  ("use_it",                True),
  ("xsection",              182.000000),
  ("triggers",              [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyD24_v4/TTJets_SingleLeptFromTbar_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/VHBB_HEPPY_D24_TTJets_SingleLeptFromTbar_TuneCUETP8M1_13TeV-madgraphMLM-Py8__spr16MAv2-puspr16_80r2as_2016_MAv2_v0_ext1-v1/161012_120022"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])

samples_no_njet_cut_2016["/WJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISpring16MiniAODv2-PUSpring16RAWAODSIM_reHLT_80X_mcRun2_asymptotic_v14_ext1-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "EWK"),
  ("process_name_specific", "WJetsToLNu"),
  ("nof_files",             8172),
  ("nof_events",            47502020),
  ("use_it",                True),
  ("xsection",              61526.700000),
  ("triggers",              [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyD24_v4/WJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/VHBB_HEPPY_D24_WJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-Py8__spr16MAv2-puspr16_HLT_80r2as_v14_ext1-v1/161012_120717"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_no_njet_cut_2016["/WWTo2L2Nu_13TeV-powheg/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "EWK"),
  ("process_name_specific", "WWTo2L2Nu"),
  ("nof_files",             336),
  ("nof_events",            1996600),
  ("use_it",                True),
  ("xsection",              10.481000),
  ("triggers",              [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyD24_v4/WWTo2L2Nu_13TeV-powheg/VHBB_HEPPY_D24_WWTo2L2Nu_13TeV-powheg__spr16MAv2-puspr16_80r2as_2016_MAv2_v0-v1/161012_121546"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_no_njet_cut_2016["/WZTo3LNu_TuneCUETP8M1_13TeV-powheg-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "EWK"),
  ("process_name_specific", "WZTo3LNu"),
  ("nof_files",             334),
  ("nof_events",            2000000),
  ("use_it",                True),
  ("xsection",              4.102000),
  ("triggers",              [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyD24_v4/WZTo3LNu_TuneCUETP8M1_13TeV-powheg-pythia8/VHBB_HEPPY_D24_WZTo3LNu_TuneCUETP8M1_13TeV-powheg-Py8__spr16MAv2-puspr16_80r2as_2016_MAv2_v0-v1/161012_121711"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_no_njet_cut_2016["/ZZTo4L_13TeV-amcatnloFXFX-pythia8/RunIISpring16MiniAODv2-PUSpring16RAWAODSIM_reHLT_80X_mcRun2_asymptotic_v14-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "EWK"),
  ("process_name_specific", "ZZTo4L"),
  ("nof_files",             1760),
  ("nof_events",            10348531),
  ("use_it",                True),
  ("xsection",              1.256000),
  ("triggers",              [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyD24_v4/ZZTo4L_13TeV-amcatnloFXFX-pythia8/VHBB_HEPPY_D24_ZZTo4L_13TeV-amcatnloFXFX-Py8__spr16MAv2-puspr16_HLT_80r2as_v14-v1/161012_121839"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_no_njet_cut_2016["/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/RunIISpring16MiniAODv2-PUSpring16RAWAODSIM_reHLT_80X_mcRun2_asymptotic_v14_ext1-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "signal"),
  ("process_name_specific", "ttHJetToNonbb_M125"),
  ("nof_files",             1692),
  ("nof_events",            9992683),
  ("use_it",                True),
  ("xsection",              0.215100),
  ("triggers",              [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyD24_v4/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/VHBB_HEPPY_D24_ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_Py8_mWCutfix__spr16MAv2-puspr16_HLT_80r2as_v14_ext1-v1/161012_122004"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_no_njet_cut_2016["/ttHToNonbb_M125_13TeV_powheg_pythia8/RunIISpring16MiniAODv2-PUSpring16RAWAODSIM_reHLT_80X_mcRun2_asymptotic_v14-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "signal"),
  ("process_name_specific", "ttHToNonbb_M125"),
  ("nof_files",             648),
  ("nof_events",            3860872),
  ("use_it",                True),
  ("xsection",              0.215100),
  ("triggers",              [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyD24_v4/ttHToNonbb_M125_13TeV_powheg_pythia8/VHBB_HEPPY_D24_ttHToNonbb_M125_13TeV_powheg_Py8__spr16MAv2-puspr16_HLT_80r2as_v14-v1/161012_122128"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])

samples_no_njet_cut_2016["/SingleMuon/Run2016B-PromptReco-v2/MINIAOD"] = OD([
  ("type",                  "data"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "SingleMuon_Run2016B_v2"),
  ("nof_files",             9724),
  ("nof_events",            324823071),
  ("use_it",                True),
  ("triggers",              [ "1mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyD24_v4/SingleMuon/VHBB_HEPPY_D24_SingleMuon__Run2016B-PromptReco-v2/161028_144131"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_no_njet_cut_2016["/SingleMuon/Run2016C-PromptReco-v2/MINIAOD"] = OD([
  ("type",                  "data"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "SingleMuon_Run2016C"),
  ("nof_files",             8497),
  ("nof_events",            324823071),
  ("use_it",                True),
  ("triggers",              [ "1mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyD24_v4/SingleMuon/VHBB_HEPPY_D24_SingleMuon__Run2016C-PromptReco-v2/161028_142953"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_no_njet_cut_2016["/SingleMuon/Run2016D-PromptReco-v2/MINIAOD"] = OD([
  ("type",                  "data"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "SingleMuon_Run2016D"),
  ("nof_files",             9248),
  ("nof_events",            324823071),
  ("use_it",                True),
  ("triggers",              [ "1mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyD24_v4/SingleMuon/VHBB_HEPPY_D24_SingleMuon__Run2016D-PromptReco-v2/161028_143637"),
        ("selection", "*"),
        ("blacklist", [971, 1367, 7322]),
      ]),
    ]
  ),
])


samples_no_njet_cut_2016["/TTW/spring16DR80v6aMiniAODv1/FASTSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "TTW"),
  ("process_name_specific", "TTW_Fastsim"),
  ("nof_files",             162),
  ("nof_events",            8362991),
  ("use_it",                False),
  ("xsection",              0.204300),
  ("triggers",              [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/andres/tth/TTW_FastSim"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])

