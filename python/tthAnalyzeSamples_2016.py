from collections import OrderedDict as OD

samples_2016 = OD()

# file generated with command:
# check_broken -p /hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau/MC_fastsim/ /hdfs/cms/store/user/mario/VHBBHeppyV25tthtautau/MC_fastsim/ /hdfs/cms/store/user/rdewanje/VHBBHeppyV25tthtautau/MC_fastsim/ /hdfs/cms/store/user/veelken/VHBBHeppyV25tthtautau/MC_fastsim/ --histo CountWeighted --output=. -P -z -v

#############
# DoubleEG
#############

# file generated with command:
# check_broken -p /hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau/ /hdfs/cms/store/user/mario/VHBBHeppyV25tthtautau/ /hdfs/cms/store/user/rdewanje/VHBBHeppyV25tthtautau/ /hdfs/cms/store/user/veelken/VHBBHeppyV25tthtautau/ /hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v2 /hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v3 --histo CountWeighted --output=samples/DoubleEG/ -P -z -v -d -f DoubleEG

samples_2016["/DoubleEG/Run2016B-23Sep2016-v3/MINIAOD"] = OD([
  ("type",                  "data"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "DoubleEG_Run2016B_v3"),
  ("nof_files",             8546),
  ("nof_events",            143073268),
  ("use_HIP_mitigation_bTag", True),
  ("use_HIP_mitigation_mediumMuonId", True),
  ("use_it",                True),
  ("triggers",              [ "2e", "3e" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau/DoubleEG/VHBB_HEPPY_V25tthtautau_DoubleEG__Run2016B-23Sep2016-v3_forceResubmit2/170219_190454"),
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
  ("nof_files",             626),
  ("nof_events",            47677856),
  ("use_HIP_mitigation_bTag", True),
  ("use_HIP_mitigation_mediumMuonId", True),
  ("use_it",                True),
  ("triggers",              [ "2e", "3e" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v2/DoubleEG/VHBB_HEPPY_V25tthtautau_v2_DoubleEG__Run2016C-23Sep2016-v1/170219_194332"),
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
  ("nof_files",             906),
  ("nof_events",            49877710),
  ("use_HIP_mitigation_bTag", True),
  ("use_HIP_mitigation_mediumMuonId", True),
  ("use_it",                True),
  ("triggers",              [ "2e", "3e" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v2/DoubleEG/VHBB_HEPPY_V25tthtautau_v2_DoubleEG__Run2016E-23Sep2016-v1/170218_171718"),
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
  ("nof_files",             1544),
  ("nof_events",            78797031),
  ("use_HIP_mitigation_bTag", False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                True),
  ("triggers",              [ "2e", "3e" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v2/DoubleEG/VHBB_HEPPY_V25tthtautau_v2_DoubleEG__Run2016G-23Sep2016-v1/170218_172915"),
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
  ("nof_files",             7577),
  ("nof_events",            84344490),
  ("use_HIP_mitigation_bTag", False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                True),
  ("triggers",              [ "2e", "3e" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau/DoubleEG/VHBB_HEPPY_V25tthtautau_DoubleEG__Run2016H-PromptReco-v2/170215_142837"),
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
  ("nof_files",             136),
  ("nof_events",            2146647),
  ("use_HIP_mitigation_bTag", False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                True),
  ("triggers",              [ "2e", "3e" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v3/DoubleEG/VHBB_HEPPY_V25tthtautau_v3_DoubleEG__Run2016H-PromptReco-v3/170221_105758"),
        ("selection", "*"),
        ("blacklist", [124, 128, 130, 131, 132, 133, 134]),
      ]),
    ]
  ),
])
samples_2016["/DoubleEG/Run2016D-23Sep2016-v1/MINIAOD"] = OD([
  ("type",                  "data"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "DoubleEG_Run2016D_v1"),
  ("nof_files",             1008),
  ("nof_events",            53324960),
  ("use_HIP_mitigation_bTag", True),
  ("use_HIP_mitigation_mediumMuonId", True),
  ("use_it",                True),
  ("triggers",              [ "2e", "3e" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v2/DoubleEG/VHBB_HEPPY_V25tthtautau_v2_DoubleEG__Run2016D-23Sep2016-v1/170218_171438"),
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
  ("nof_files",             649),
  ("nof_events",            34577629),
  ("use_HIP_mitigation_bTag", True),
  ("use_HIP_mitigation_mediumMuonId", True),
  ("use_it",                True),
  ("triggers",              [ "2e", "3e" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v2/DoubleEG/VHBB_HEPPY_V25tthtautau_v2_DoubleEG__Run2016F-23Sep2016-v1/170218_180254"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])

#############
# DoubleMuon
#############

# file generated with command:
# check_broken -p /hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau/ /hdfs/cms/store/user/mario/VHBBHeppyV25tthtautau/ /hdfs/cms/store/user/rdewanje/VHBBHeppyV25tthtautau/ /hdfs/cms/store/user/veelken/VHBBHeppyV25tthtautau/ /hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v2 /hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v3 --histo CountWeighted --output=samples/DoubleMuon/ -P -z -v -d -f DoubleMuon

samples_2016["/DoubleMuon/Run2016B-23Sep2016-v3/MINIAOD"] = OD([
  ("type",                  "data"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "DoubleMuon_Run2016B_v3"),
  ("nof_files",             1966),
  ("nof_events",            82535526),
  ("use_HIP_mitigation_bTag", True),
  ("use_HIP_mitigation_mediumMuonId", True),
  ("use_it",                True),
  ("triggers",              [ "2mu", "3mu" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v2/DoubleMuon/VHBB_HEPPY_V25tthtautau_v2_DoubleMuon__Run2016B-23Sep2016-v3/170218_175649"),
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
  ("nof_files",             896),
  ("nof_events",            28246946),
  ("use_HIP_mitigation_bTag", True),
  ("use_HIP_mitigation_mediumMuonId", True),
  ("use_it",                True),
  ("triggers",              [ "2mu", "3mu" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v2/DoubleMuon/VHBB_HEPPY_V25tthtautau_v2_DoubleMuon__Run2016E-23Sep2016-v1/170218_180126"),
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
  ("nof_files",             641),
  ("nof_events",            20329921),
  ("use_HIP_mitigation_bTag", True),
  ("use_HIP_mitigation_mediumMuonId", True),
  ("use_it",                True),
  ("triggers",              [ "2mu", "3mu" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v2/DoubleMuon/VHBB_HEPPY_V25tthtautau_v2_DoubleMuon__Run2016F-23Sep2016-v1/170217_152817"),
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
  ("nof_files",             8180),
  ("nof_events",            48093751),
  ("use_HIP_mitigation_bTag", False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                True),
  ("triggers",              [ "2mu", "3mu" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau/DoubleMuon/VHBB_HEPPY_V25tthtautau_DoubleMuon__Run2016H-PromptReco-v2/170215_142956"),
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
  ("nof_files",             133),
  ("nof_events",            1219733),
  ("use_HIP_mitigation_bTag", False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                True),
  ("triggers",              [ "2mu", "3mu" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v3/DoubleMuon/VHBB_HEPPY_V25tthtautau_v3_DoubleMuon__Run2016H-PromptReco-v3/170221_214504"),
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
  ("nof_files",             621),
  ("nof_events",            27934629),
  ("use_HIP_mitigation_bTag", True),
  ("use_HIP_mitigation_mediumMuonId", True),
  ("use_it",                True),
  ("triggers",              [ "2mu", "3mu" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v2/DoubleMuon/VHBB_HEPPY_V25tthtautau_v2_DoubleMuon__Run2016C-23Sep2016-v1/170218_171035"),
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
  ("nof_files",             1003),
  ("nof_events",            33861745),
  ("use_HIP_mitigation_bTag", True),
  ("use_HIP_mitigation_mediumMuonId", True),
  ("use_it",                True),
  ("triggers",              [ "2mu", "3mu" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v2/DoubleMuon/VHBB_HEPPY_V25tthtautau_v2_DoubleMuon__Run2016D-23Sep2016-v1/170218_171554"),
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
  ("nof_files",             1527),
  ("nof_events",            45235604),
  ("use_HIP_mitigation_bTag", False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                True),
  ("triggers",              [ "2mu", "3mu" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v2/DoubleMuon/VHBB_HEPPY_V25tthtautau_v2_DoubleMuon__Run2016G-23Sep2016-v1/170217_151055"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])

#############
# MuonEG
#############

# file generated with command:
# check_broken -p /hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau/ /hdfs/cms/store/user/mario/VHBBHeppyV25tthtautau/ /hdfs/cms/store/user/rdewanje/VHBBHeppyV25tthtautau/ /hdfs/cms/store/user/veelken/VHBBHeppyV25tthtautau/ /hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v2 /hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v3 --histo CountWeighted --output=samples/MuonEG/ -P -z -v -d -f MuonEG

samples_2016["/MuonEG/Run2016D-23Sep2016-v1/MINIAOD"] = OD([
  ("type",                  "data"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "MuonEG_Run2016D_v1"),
  ("nof_files",             4296),
  ("nof_events",            23482352),
  ("use_HIP_mitigation_bTag", True),
  ("use_HIP_mitigation_mediumMuonId", True),
  ("use_it",                True),
  ("triggers",              [ "1e1mu", "2e1mu", "1e2mu" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/rdewanje/VHBBHeppyV25tthtautau/MuonEG/VHBB_HEPPY_V25tthtautau_MuonEG__Run2016D-23Sep2016-v1/170207_125438"),
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
  ("nof_files",             5726),
  ("nof_events",            28705853),
  ("use_HIP_mitigation_bTag", False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                True),
  ("triggers",              [ "1e1mu", "2e1mu", "1e2mu" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v3/MuonEG/VHBB_HEPPY_V25tthtautau_v3_MuonEG__Run2016H-PromptReco-v2/170221_150405"),
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
  ("nof_files",             190),
  ("nof_events",            770494),
  ("use_HIP_mitigation_bTag", False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                True),
  ("triggers",              [ "1e1mu", "2e1mu", "1e2mu" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau/MuonEG/VHBB_HEPPY_V25tthtautau_MuonEG__Run2016H-PromptReco-v3/170215_143932"),
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
  ("nof_files",             1966),
  ("nof_events",            32727796),
  ("use_HIP_mitigation_bTag", True),
  ("use_HIP_mitigation_mediumMuonId", True),
  ("use_it",                True),
  ("triggers",              [ "1e1mu", "2e1mu", "1e2mu" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v2/MuonEG/VHBB_HEPPY_V25tthtautau_v2_MuonEG__Run2016B-23Sep2016-v3/170218_175920"),
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
  ("nof_files",             621),
  ("nof_events",            15405678),
  ("use_HIP_mitigation_bTag", True),
  ("use_HIP_mitigation_mediumMuonId", True),
  ("use_it",                True),
  ("triggers",              [ "1e1mu", "2e1mu", "1e2mu" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v2/MuonEG/VHBB_HEPPY_V25tthtautau_v2_MuonEG__Run2016C-23Sep2016-v1/170218_170759"),
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
  ("nof_files",             896),
  ("nof_events",            22519303),
  ("use_HIP_mitigation_bTag", True),
  ("use_HIP_mitigation_mediumMuonId", True),
  ("use_it",                True),
  ("triggers",              [ "1e1mu", "2e1mu", "1e2mu" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v2/MuonEG/VHBB_HEPPY_V25tthtautau_v2_MuonEG__Run2016E-23Sep2016-v1/170218_172335"),
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
  ("nof_files",             641),
  ("nof_events",            16002165),
  ("use_HIP_mitigation_bTag", True),
  ("use_HIP_mitigation_mediumMuonId", True),
  ("use_it",                True),
  ("triggers",              [ "1e1mu", "2e1mu", "1e2mu" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v2/MuonEG/VHBB_HEPPY_V25tthtautau_v2_MuonEG__Run2016F-23Sep2016-v1/170218_182854"),
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
  ("nof_files",             1527),
  ("nof_events",            33854612),
  ("use_HIP_mitigation_bTag", False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                True),
  ("triggers",              [ "1e1mu", "2e1mu", "1e2mu" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v2/MuonEG/VHBB_HEPPY_V25tthtautau_v2_MuonEG__Run2016G-23Sep2016-v1/170218_172759"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])

#############
# SingleElectron
#############

# file generated with command:
# check_broken -p /hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau/ /hdfs/cms/store/user/mario/VHBBHeppyV25tthtautau/ /hdfs/cms/store/user/rdewanje/VHBBHeppyV25tthtautau/ /hdfs/cms/store/user/veelken/VHBBHeppyV25tthtautau/ /hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v2 /hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v3 --histo CountWeighted --output=samples/SingleElectron/ -P -z -v -d -f SingleElectron

samples_2016["/SingleElectron/Run2016B-23Sep2016-v3/MINIAOD"] = OD([
  ("type",                  "data"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "SingleElectron_Run2016B_v3"),
  ("nof_files",             5982),
  ("nof_events",            246440440),
  ("use_HIP_mitigation_bTag", True),
  ("use_HIP_mitigation_mediumMuonId", True),
  ("use_it",                True),
  ("triggers",              [ "1e" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v3/SingleElectron/VHBB_HEPPY_V25tthtautau_v3_SingleElectron__Run2016B-23Sep2016-v3/170220_170550"),
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
  ("nof_files",             1878),
  ("nof_events",            97259854),
  ("use_HIP_mitigation_bTag", True),
  ("use_HIP_mitigation_mediumMuonId", True),
  ("use_it",                True),
  ("triggers",              [ "1e" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v3/SingleElectron/VHBB_HEPPY_V25tthtautau_v3_SingleElectron__Run2016C-23Sep2016-v1/170220_170950"),
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
  ("nof_files",             3024),
  ("nof_events",            148167727),
  ("use_HIP_mitigation_bTag", True),
  ("use_HIP_mitigation_mediumMuonId", True),
  ("use_it",                True),
  ("triggers",              [ "1e" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v3/SingleElectron/VHBB_HEPPY_V25tthtautau_v3_SingleElectron__Run2016D-23Sep2016-v1/170220_171118"),
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
  ("nof_files",             2716),
  ("nof_events",            117321545),
  ("use_HIP_mitigation_bTag", True),
  ("use_HIP_mitigation_mediumMuonId", True),
  ("use_it",                True),
  ("triggers",              [ "1e" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v3/SingleElectron/VHBB_HEPPY_V25tthtautau_v3_SingleElectron__Run2016E-23Sep2016-v1/170220_171247"),
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
  ("nof_files",             649),
  ("nof_events",            70593532),
  ("use_HIP_mitigation_bTag", True),
  ("use_HIP_mitigation_mediumMuonId", True),
  ("use_it",                True),
  ("triggers",              [ "1e" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v2/SingleElectron/VHBB_HEPPY_V25tthtautau_v2_SingleElectron__Run2016F-23Sep2016-v1/170218_172629"),
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
  ("nof_files",             7576),
  ("nof_events",            126863489),
  ("use_HIP_mitigation_bTag", False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                True),
  ("triggers",              [ "1e" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau/SingleElectron/VHBB_HEPPY_V25tthtautau_SingleElectron__Run2016H-PromptReco-v2/170215_145016"),
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
  ("nof_files",             136),
  ("nof_events",            3191585),
  ("use_HIP_mitigation_bTag", False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                True),
  ("triggers",              [ "1e" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v3/SingleElectron/VHBB_HEPPY_V25tthtautau_v3_SingleElectron__Run2016H-PromptReco-v3/170222_145637"),
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
  ("nof_files",             1544),
  ("nof_events",            153232788),
  ("use_HIP_mitigation_bTag", False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                True),
  ("triggers",              [ "1e" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v2/SingleElectron/VHBB_HEPPY_V25tthtautau_v2_SingleElectron__Run2016G-23Sep2016-v1/170217_150830"),
        ("selection", "*"),
        ("blacklist", [1312]),
      ]),
    ]
  ),
])

#############
# SingleMuon
#############

# file generated with command:
# check_broken -p /hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau/ /hdfs/cms/store/user/mario/VHBBHeppyV25tthtautau/ /hdfs/cms/store/user/rdewanje/VHBBHeppyV25tthtautau/ /hdfs/cms/store/user/veelken/VHBBHeppyV25tthtautau/ /hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v2 /hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v3 --histo CountWeighted --output=samples/SingleMuon/ -P -z -v -d -f SingleMuon

samples_2016["/SingleMuon/Run2016B-23Sep2016-v3/MINIAOD"] = OD([
  ("type",                  "data"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "SingleMuon_Run2016B_v3"),
  ("nof_files",             5897),
  ("nof_events",            158145722),
  ("use_HIP_mitigation_bTag", True),
  ("use_HIP_mitigation_mediumMuonId", True),
  ("use_it",                True),
  ("triggers",              [ "1mu" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v3/SingleMuon/VHBB_HEPPY_V25tthtautau_v3_SingleMuon__Run2016B-23Sep2016-v3/170220_170831"),
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
  ("nof_files",             1862),
  ("nof_events",            67441308),
  ("use_HIP_mitigation_bTag", True),
  ("use_HIP_mitigation_mediumMuonId", True),
  ("use_it",                True),
  ("triggers",              [ "1mu" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v3/SingleMuon/VHBB_HEPPY_V25tthtautau_v3_SingleMuon__Run2016C-23Sep2016-v1/170221_173556"),
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
  ("nof_files",             1003),
  ("nof_events",            98017996),
  ("use_HIP_mitigation_bTag", True),
  ("use_HIP_mitigation_mediumMuonId", True),
  ("use_it",                True),
  ("triggers",              [ "1mu" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v2/SingleMuon/VHBB_HEPPY_V25tthtautau_v2_SingleMuon__Run2016D-23Sep2016-v1/170218_171316"),
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
  ("nof_files",             2688),
  ("nof_events",            90984718),
  ("use_HIP_mitigation_bTag", True),
  ("use_HIP_mitigation_mediumMuonId", True),
  ("use_it",                True),
  ("triggers",              [ "1mu" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v3/SingleMuon/VHBB_HEPPY_V25tthtautau_v3_SingleMuon__Run2016E-23Sep2016-v1/170220_170712"),
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
  ("nof_files",             641),
  ("nof_events",            65489554),
  ("use_HIP_mitigation_bTag", True),
  ("use_HIP_mitigation_mediumMuonId", True),
  ("use_it",                True),
  ("triggers",              [ "1mu" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v2/SingleMuon/VHBB_HEPPY_V25tthtautau_v2_SingleMuon__Run2016F-23Sep2016-v1/170217_153044"),
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
  ("nof_files",             8180),
  ("nof_events",            171134793),
  ("use_HIP_mitigation_bTag", False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                True),
  ("triggers",              [ "1mu" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau/SingleMuon/VHBB_HEPPY_V25tthtautau_SingleMuon__Run2016H-PromptReco-v2/170215_143417"),
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
  ("nof_files",             190),
  ("nof_events",            4393222),
  ("use_HIP_mitigation_bTag", False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                True),
  ("triggers",              [ "1mu" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau/SingleMuon/VHBB_HEPPY_V25tthtautau_SingleMuon__Run2016H-PromptReco-v3/170215_144050"),
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
  ("nof_files",             1527),
  ("nof_events",            149916849),
  ("use_HIP_mitigation_bTag", False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                True),
  ("triggers",              [ "1mu" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v2/SingleMuon/VHBB_HEPPY_V25tthtautau_v2_SingleMuon__Run2016G-23Sep2016-v1/170217_151611"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])

#############
# Tau
#############

# file generated with command:
# check_broken -p /hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau/ /hdfs/cms/store/user/mario/VHBBHeppyV25tthtautau/ /hdfs/cms/store/user/rdewanje/VHBBHeppyV25tthtautau/ /hdfs/cms/store/user/veelken/VHBBHeppyV25tthtautau/ /hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau /hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_HLT /hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v2 /hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v3 --histo CountWeighted --output=samples/Tau/ -P -z -v -d -f Tau

samples_2016["/Tau/Run2016B-23Sep2016-v3/MINIAOD"] = OD([
  ("type",                  "data"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "Tau_Run2016B_v3"),
  ("nof_files",             8521),
  ("nof_events",            68727458),
  ("use_HIP_mitigation_bTag", True),
  ("use_HIP_mitigation_mediumMuonId", True),
  ("use_it",                True),
  ("triggers",              [ "1e1tau", "1mu1tau", "2tau" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_HLT/Tau/VHBB_HEPPY_V25tthtautau_HLT_Tau__Run2016B-23Sep2016-v3/170216_184427"),
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
  ("nof_files",             2688),
  ("nof_events",            36931473),
  ("use_HIP_mitigation_bTag", True),
  ("use_HIP_mitigation_mediumMuonId", True),
  ("use_it",                True),
  ("triggers",              [ "1e1tau", "1mu1tau", "2tau" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_HLT/Tau/VHBB_HEPPY_V25tthtautau_HLT_Tau__Run2016C-23Sep2016-v1/170216_182257"),
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
  ("nof_files",             4328),
  ("nof_events",            56827771),
  ("use_HIP_mitigation_bTag", True),
  ("use_HIP_mitigation_mediumMuonId", True),
  ("use_it",                True),
  ("triggers",              [ "1e1tau", "1mu1tau", "2tau" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_HLT/Tau/VHBB_HEPPY_V25tthtautau_HLT_Tau__Run2016D-23Sep2016-v1/170216_182421"),
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
  ("nof_files",             3886),
  ("nof_events",            58348773),
  ("use_HIP_mitigation_bTag", True),
  ("use_HIP_mitigation_mediumMuonId", True),
  ("use_it",                True),
  ("triggers",              [ "1e1tau", "1mu1tau", "2tau" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_HLT/Tau/VHBB_HEPPY_V25tthtautau_HLT_Tau__Run2016E-23Sep2016-v1/170216_182541"),
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
  ("nof_files",             2798),
  ("nof_events",            40549716),
  ("use_HIP_mitigation_bTag", True),
  ("use_HIP_mitigation_mediumMuonId", True),
  ("use_it",                True),
  ("triggers",              [ "1e1tau", "1mu1tau", "2tau" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_HLT/Tau/VHBB_HEPPY_V25tthtautau_HLT_Tau__Run2016F-23Sep2016-v1/170216_182849"),
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
  ("nof_files",             1552),
  ("nof_events",            79578661),
  ("use_HIP_mitigation_bTag", False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                True),
  ("triggers",              [ "1e1tau", "1mu1tau", "2tau" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v2/Tau/VHBB_HEPPY_V25tthtautau_v2_Tau__Run2016G-23Sep2016-v1/170218_173036"),
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
  ("nof_files",             6052),
  ("nof_events",            76504267),
  ("use_HIP_mitigation_bTag", False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                True),
  ("triggers",              [ "1e1tau", "1mu1tau", "2tau" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v3/Tau/VHBB_HEPPY_V25tthtautau_v3_Tau__Run2016H-PromptReco-v2/170221_162533"),
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
  ("nof_files",             197),
  ("nof_events",            1898072),
  ("use_HIP_mitigation_bTag", False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                True),
  ("triggers",              [ "1e1tau", "1mu1tau", "2tau" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau/Tau/VHBB_HEPPY_V25tthtautau_Tau__Run2016H-PromptReco-v3/170215_145334"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])


#############
# MC
#############

# file generated with command:
# check_broken -p /hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau/MC/ /hdfs/cms/store/user/mario/VHBBHeppyV25tthtautau/MC/ /hdfs/cms/store/user/rdewanje/VHBBHeppyV25tthtautau/MC/ /hdfs/cms/store/user/veelken/VHBBHeppyV25tthtautau/MC/ /hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v2/MC /hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v3/MC --histo CountWeighted --output=. -P -z -v

samples_2016["/ST_t-channel_antitop_4f_inclusiveDecays_13TeV-powhegV2-madspin-pythia8_TuneCUETP8M1/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "TT"),
  ("process_name_specific", "ST_t-channel_antitop_4f_inclusiveDecays"),
  ("nof_files",             3916),
  ("nof_events",            38793427),
  ("use_it",                True),
  ("xsection",              80.950000),
  ("genWeight",             True),
  ("triggers",              [ "1e", "1mu", "2e", "1e1mu", "2mu", "3e", "2e1mu", "1e2mu", "3mu", "1e1tau", "1mu1tau", "2tau" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau/MC/ST_t-channel_antitop_4f_inclusiveDecays_13TeV-powhegV2-madspin-pythia8_TuneCUETP8M1/VHBB_HEPPY_V25tt_ST_t-channel_antitop_4f_inclusiveDecays_13TeV-powhegV2-madspin-Py8_TuneCUETP8M1__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6-v1/170209_102511"),
        ("selection", "*"),
        ("blacklist", [859, 1664]),
      ]),
    ]
  ),
])
samples_2016["/DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DYJetsToLL_M-10to50"),
  ("nof_files",             1782),
  ("nof_events",            35252387),
  ("use_it",                True),
  ("xsection",              18610.000000),
  ("genWeight",             True),
  ("triggers",              [ "1e", "1mu", "2e", "1e1mu", "2mu", "3e", "2e1mu", "1e2mu", "3mu", "1e1tau", "1mu1tau", "2tau" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v3/MC/DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/VHBB_HEPPY_V25tthtautau_v3_DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-madgraphMLM-Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6-v1/170225_232933"),
        ("selection", "*"),
        ("blacklist", [784, 1237]),
      ]),
    ]
  ),
])
samples_2016["/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v2/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DYJetsToLL_M-50_ext1"),
  ("nof_files",             2461),
  ("nof_events",            143970947),
  ("use_it",                True),
  ("xsection",              6025.200000),
  ("genWeight",             True),
  ("triggers",              [ "1e", "1mu", "2e", "1e1mu", "2mu", "3e", "2e1mu", "1e2mu", "3mu", "1e1tau", "1mu1tau", "2tau" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v3/MC/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/VHBB_HEPPY_V25tthtautau_v3_DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6_ext1-v2/170225_232649"),
        ("selection", "*"),
        ("blacklist", [474, 1871, 2012, 2305, 2320, 2321, 2323]),
      ]),
    ]
  ),
])
samples_2016["/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext2-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DYJetsToLL_M-50_ext2"),
  ("nof_files",             4851),
  ("nof_events",            143970947),
  ("use_it",                True),
  ("xsection",              6025.200000),
  ("genWeight",             True),
  ("triggers",              [ "1e", "1mu", "2e", "1e1mu", "2mu", "3e", "2e1mu", "1e2mu", "3mu", "1e1tau", "1mu1tau", "2tau" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v3/MC/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/VHBB_HEPPY_V25tthtautau_v3_DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6_ext2-v1/170225_232809"),
        ("selection", "*"),
        ("blacklist", [19, 31, 32, 63, 240, 252, 307, 393, 398, 412, 454, 532, 611, 715, 734, 736, 948, 1061, 1062, 1075, 1100, 1114, 1132, 1134, 1148, 1151, 1221, 1314, 1407, 1616, 1624, 1670, 1675, 1704, 1743, 1888, 1904, 1930, 1991, 2014, 2111, 2136, 2179, 2228, 2229, 2233, 2234, 2275, 2409, 2468, 2514, 2555, 2557, 2686, 2847, 2974, 3014, 3103, 3169, 3223, 3417, 3424, 3427, 3448, 3514, 3516, 3656, 3703, 3854, 3906, 4069, 4148, 4303, 4377, 4380, 4431, 4440, 4525, 4530, 4612, 4628, 4633, 4656, 4666, 4671, 4750, 4785]),
      ]),
    ]
  ),
])
samples_2016["/GluGluHToZZTo4L_M125_13TeV_powheg2_JHUgenV6_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "additional_signal_overlap"),
  ("process_name_specific", "GluGluHToZZTo4L"),
  ("nof_files",             101),
  ("nof_events",            999863),
  ("use_it",                True),
  ("xsection",              0.011900),
  ("genWeight",             True),
  ("triggers",              [ "1e", "1mu", "2e", "1e1mu", "2mu", "3e", "2e1mu", "1e2mu", "3mu", "1e1tau", "1mu1tau", "2tau" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/veelken/VHBBHeppyV25tthtautau/MC/GluGluHToZZTo4L_M125_13TeV_powheg2_JHUgenV6_pythia8/VHBB_HEPPY_V25tthtautau_GluGluHToZZTo4L_M125_13TeV_powheg2_JHUgenV6_Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6-v1/170207_133635"),
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
  ("nof_files",             100),
  ("nof_events",            622641),
  ("use_it",                True),
  ("xsection",              3.680000),
  ("genWeight",             True),
  ("triggers",              [ "1e", "1mu", "2e", "1e1mu", "2mu", "3e", "2e1mu", "1e2mu", "3mu", "1e1tau", "1mu1tau", "2tau" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/rdewanje/VHBBHeppyV25tthtautau/MC/ST_s-channel_4f_leptonDecays_13TeV-amcatnlo-pythia8_TuneCUETP8M1/VHBB_HEPPY_V25tthtautau_ST_s-channel_4f_leptonDecays_13TeV-amcatnlo-Py8_TuneCUETP8M1__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6-v1/170207_123409"),
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
  ("nof_files",             6784),
  ("nof_events",            67070045),
  ("use_it",                True),
  ("xsection",              136.020000),
  ("genWeight",             True),
  ("triggers",              [ "1e", "1mu", "2e", "1e1mu", "2mu", "3e", "2e1mu", "1e2mu", "3mu", "1e1tau", "1mu1tau", "2tau" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/mario/VHBBHeppyV25tthtautau/MC/ST_t-channel_top_4f_inclusiveDecays_13TeV-powhegV2-madspin-pythia8_TuneCUETP8M1/VHBB_HEPPY_V25tthtautau_ST_t-channel_top_4f_inclusiveDecays_13TeV-powhegV2-madspin-Py8_TuneCUETP8M1__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6-v1/170208_120156"),
        ("selection", "*"),
        ("blacklist", [511, 533, 573, 703, 729, 741, 839, 843, 1007, 1024, 1501, 2776, 2959, 3223, 3491, 4701, 4914]),
      ]),
    ]
  ),
])
samples_2016["/ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "TT"),
  ("process_name_specific", "ST_tW_antitop_5f_inclusiveDecays"),
  ("nof_files",             699),
  ("nof_events",            6884041),
  ("use_it",                True),
  ("xsection",              35.600000),
  ("genWeight",             True),
  ("triggers",              [ "1e", "1mu", "2e", "1e1mu", "2mu", "3e", "2e1mu", "1e2mu", "3mu", "1e1tau", "1mu1tau", "2tau" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau/MC/ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1/VHBB_HEPPY_V25tthtautau_ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-Py8_TuneCUETP8M1__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6_ext1-v1/170207_123614"),
        ("selection", "*"),
        ("blacklist", [38, 98, 251, 530, 604]),
      ]),
    ]
  ),
])
samples_2016["/ST_tW_top_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "TT"),
  ("process_name_specific", "ST_tW_top_5f_inclusiveDecays"),
  ("nof_files",             702),
  ("nof_events",            6942327),
  ("use_it",                True),
  ("xsection",              35.600000),
  ("genWeight",             True),
  ("triggers",              [ "1e", "1mu", "2e", "1e1mu", "2mu", "3e", "2e1mu", "1e2mu", "3mu", "1e1tau", "1mu1tau", "2tau" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/veelken/VHBBHeppyV25tthtautau/MC/ST_tW_top_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1/VHBB_HEPPY_V25tthtautau_ST_tW_top_5f_inclusiveDecays_13TeV-powheg-Py8_TuneCUETP8M1__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6_ext1-v1/170207_133952"),
        ("selection", "*"),
        ("blacklist", [215]),
      ]),
    ]
  ),
])
samples_2016["/TGJets_TuneCUETP8M1_13TeV_amcatnlo_madspin_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "Rares"),
  ("process_name_specific", "TGJets"),
  ("nof_files",             30),
  ("nof_events",            364136),
  ("use_it",                True),
  ("xsection",              2.967000),
  ("genWeight",             True),
  ("triggers",              [ "1e", "1mu", "2e", "1e1mu", "2mu", "3e", "2e1mu", "1e2mu", "3mu", "1e1tau", "1mu1tau", "2tau" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/rdewanje/VHBBHeppyV25tthtautau/MC/TGJets_TuneCUETP8M1_13TeV_amcatnlo_madspin_pythia8/VHBB_HEPPY_V25tthtautau_TGJets_TuneCUETP8M1_13TeV_amcatnlo_madspin_Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6-v1/170209_095835"),
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
  ("nof_files",             157),
  ("nof_events",            364136),
  ("use_it",                True),
  ("xsection",              2.967000),
  ("genWeight",             True),
  ("triggers",              [ "1e", "1mu", "2e", "1e1mu", "2mu", "3e", "2e1mu", "1e2mu", "3mu", "1e1tau", "1mu1tau", "2tau" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/rdewanje/VHBBHeppyV25tthtautau/MC/TGJets_TuneCUETP8M1_13TeV_amcatnlo_madspin_pythia8/VHBB_HEPPY_V25tthtautau_TGJets_TuneCUETP8M1_13TeV_amcatnlo_madspin_Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6_ext1-v1/170207_123908"),
        ("selection", "*"),
        ("blacklist", [91, 141]),
      ]),
    ]
  ),
])
samples_2016["/THW_Hincl_13TeV-madgraph-pythia8_TuneCUETP8M1/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "additional_signal_overlap"),
  ("process_name_specific", "THW_Hincl"),
  ("nof_files",             150),
  ("nof_events",            1498975),
  ("use_it",                True),
  ("xsection",              0.015610),
  ("genWeight",             True),
  ("triggers",              [ "1e", "1mu", "2e", "1e1mu", "2mu", "3e", "2e1mu", "1e2mu", "3mu", "1e1tau", "1mu1tau", "2tau" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/veelken/VHBBHeppyV25tthtautau/MC/THW_Hincl_13TeV-madgraph-pythia8_TuneCUETP8M1/VHBB_HEPPY_V25tthtautau_THW_Hincl_13TeV-madgraph-Py8_TuneCUETP8M1__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6-v1/170207_134333"),
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
  ("nof_files",             489),
  ("nof_events",            4742775),
  ("use_it",                True),
  ("xsection",              3.697000),
  ("genWeight",             True),
  ("triggers",              [ "1e", "1mu", "2e", "1e1mu", "2mu", "3e", "2e1mu", "1e2mu", "3mu", "1e1tau", "1mu1tau", "2tau" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/rdewanje/VHBBHeppyV25tthtautau/MC/TTGJets_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/VHBB_HEPPY_V25tthtautau_TTGJets_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6-v1/170207_124053"),
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
  ("nof_files",             997),
  ("nof_events",            4742775),
  ("use_it",                True),
  ("xsection",              3.697000),
  ("genWeight",             True),
  ("triggers",              [ "1e", "1mu", "2e", "1e1mu", "2mu", "3e", "2e1mu", "1e2mu", "3mu", "1e1tau", "1mu1tau", "2tau" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/mario/VHBBHeppyV25tthtautau/MC/TTGJets_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/VHBB_HEPPY_V25tthtautau_TTGJets_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6_ext1-v1/170208_120330"),
        ("selection", "*"),
        ("blacklist", [315, 331, 344, 479, 839, 845, 848, 871, 876, 889]),
      ]),
    ]
  ),
])
samples_2016["/TTJets_DiLept_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "TT"),
  ("process_name_specific", "TTJets_DiLept"),
  ("nof_files",             616),
  ("nof_events",            30227418),
  ("use_it",                True),
  ("xsection",              87.300000),
  ("genWeight",             True),
  ("triggers",              [ "1e", "1mu", "2e", "1e1mu", "2mu", "3e", "2e1mu", "1e2mu", "3mu", "1e1tau", "1mu1tau", "2tau" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/rdewanje/VHBBHeppyV25tthtautau/MC/TTJets_DiLept_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/VHBB_HEPPY_V25tthtautau_TTJets_DiLept_TuneCUETP8M1_13TeV-madgraphMLM-Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6-v1/170207_124244"),
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
  ("nof_files",             2448),
  ("nof_events",            30227418),
  ("use_it",                True),
  ("xsection",              87.300000),
  ("genWeight",             True),
  ("triggers",              [ "1e", "1mu", "2e", "1e1mu", "2mu", "3e", "2e1mu", "1e2mu", "3mu", "1e1tau", "1mu1tau", "2tau" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/rdewanje/VHBBHeppyV25tthtautau/MC/TTJets_DiLept_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/VHBB_HEPPY_V25tthtautau_TTJets_DiLept_TuneCUETP8M1_13TeV-madgraphMLM-Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6_ext1-v1/170207_124429"),
        ("selection", "*"),
        ("blacklist", [3, 14, 32, 51, 57, 109, 341, 538, 615, 659, 778, 1177, 1432, 1642, 1643, 1648, 1653, 1872, 1885, 1926, 2210, 2220, 2374, 2435]),
      ]),
    ]
  ),
])
samples_2016["/TTJets_SingleLeptFromT_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "TT"),
  ("process_name_specific", "TTJets_SingleLeptFromT"),
  ("nof_files",             1207),
  ("nof_events",            61475579),
  ("use_it",                True),
  ("xsection",              182.180000),
  ("genWeight",             True),
  ("triggers",              [ "1e", "1mu", "2e", "1e1mu", "2mu", "3e", "2e1mu", "1e2mu", "3mu", "1e1tau", "1mu1tau", "2tau" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/mario/VHBBHeppyV25tthtautau/MC/TTJets_SingleLeptFromT_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/VHBB_HEPPY_V25tthtautau_TTJets_SingleLeptFromT_TuneCUETP8M1_13TeV-madgraphMLM-Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6-v1/170208_120534"),
        ("selection", "*"),
        ("blacklist", [64, 134, 135, 236, 293, 328, 486, 541, 587, 834]),
      ]),
    ]
  ),
])
samples_2016["/TTJets_SingleLeptFromT_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "TT"),
  ("process_name_specific", "TTJets_SingleLeptFromT_ext1"),
  ("nof_files",             5057),
  ("nof_events",            61475579),
  ("use_it",                True),
  ("xsection",              182.180000),
  ("genWeight",             True),
  ("triggers",              [ "1e", "1mu", "2e", "1e1mu", "2mu", "3e", "2e1mu", "1e2mu", "3mu", "1e1tau", "1mu1tau", "2tau" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/mario/VHBBHeppyV25tthtautau/MC/TTJets_SingleLeptFromT_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/VHBB_HEPPY_V25tthtautau_TTJets_SingleLeptFromT_TuneCUETP8M1_13TeV-madgraphMLM-Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6_ext1-v1/170208_120653"),
        ("selection", "*"),
        ("blacklist", [182, 206, 425, 496, 542, 1101, 1108, 1186, 1426, 1618, 2502, 2509, 2755, 2912, 2924, 3039, 3156, 3165, 3180, 3201, 3204, 3212, 3357, 3390, 3492, 3658, 4040, 4159, 4173, 4275, 4312, 4314, 4398, 4440, 4441, 4672, 4707, 4747, 4752, 4785]),
      ]),
    ]
  ),
])
samples_2016["/TTJets_SingleLeptFromTbar_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "TT"),
  ("process_name_specific", "TTJets_SingleLeptFromTbar"),
  ("nof_files",             1205),
  ("nof_events",            60202982),
  ("use_it",                True),
  ("xsection",              182.180000),
  ("genWeight",             True),
  ("triggers",              [ "1e", "1mu", "2e", "1e1mu", "2mu", "3e", "2e1mu", "1e2mu", "3mu", "1e1tau", "1mu1tau", "2tau" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/mario/VHBBHeppyV25tthtautau/MC/TTJets_SingleLeptFromTbar_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/VHBB_HEPPY_V25tthtautau_TTJets_SingleLeptFromTbar_TuneCUETP8M1_13TeV-madgraphMLM-Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6-v1/170208_120816"),
        ("selection", "*"),
        ("blacklist", [215, 291]),
      ]),
    ]
  ),
])
samples_2016["/TTTT_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "Rares"),
  ("process_name_specific", "TTTT"),
  ("nof_files",             26),
  ("nof_events",            104758),
  ("use_it",                True),
  ("xsection",              0.009103),
  ("genWeight",             True),
  ("triggers",              [ "1e", "1mu", "2e", "1e1mu", "2mu", "3e", "2e1mu", "1e2mu", "3mu", "1e1tau", "1mu1tau", "2tau" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau/MC/TTTT_TuneCUETP8M1_13TeV-amcatnlo-pythia8/VHBB_HEPPY_V25tthtautau_TTTT_TuneCUETP8M1_13TeV-amcatnlo-Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6-v1/170207_123853"),
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
  ("nof_files",             218),
  ("nof_events",            2700951),
  ("use_it",                True),
  ("xsection",              0.204300),
  ("genWeight",             True),
  ("triggers",              [ "1e", "1mu", "2e", "1e1mu", "2mu", "3e", "2e1mu", "1e2mu", "3mu", "1e1tau", "1mu1tau", "2tau" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau/MC/TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/VHBB_HEPPY_V25tthtautau_TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6_ext1-v3/170207_124033"),
        ("selection", "*"),
        ("blacklist", [83, 167, 179]),
      ]),
    ]
  ),
])
samples_2016["/TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext2-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "TTW"),
  ("process_name_specific", "TTWJetsToLNu_ext2"),
  ("nof_files",             314),
  ("nof_events",            2700951),
  ("use_it",                True),
  ("xsection",              0.204300),
  ("genWeight",             True),
  ("triggers",              [ "1e", "1mu", "2e", "1e1mu", "2mu", "3e", "2e1mu", "1e2mu", "3mu", "1e1tau", "1mu1tau", "2tau" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau/MC/TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/VHBB_HEPPY_V25tthtautau_TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6_ext2-v1/170207_124213"),
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
  ("nof_files",             203),
  ("nof_events",            3685750),
  ("use_it",                True),
  ("xsection",              0.252900*1.08), # CV: scale by factor 1.08 (https://hypernews.cern.ch/HyperNews/CMS/get/HIG-17-004/19/1.html)
  ("genWeight",             True),
  ("triggers",              [ "1e", "1mu", "2e", "1e1mu", "2mu", "3e", "2e1mu", "1e2mu", "3mu", "1e1tau", "1mu1tau", "2tau" ]),
  ("reHLT",                 True),   
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau/MC/TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-pythia8/VHBB_HEPPY_V25tthtautau_TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6_ext1-v1/170207_124540"),
        ("selection", "*"),
        ("blacklist", [15, 36, 57, 129]),
      ]),
    ]
  ),
])
samples_2016["/TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext2-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "TTZ"),
  ("process_name_specific", "TTZToLL_M10_ext2"),
  ("nof_files",             610),
  ("nof_events",            3685750),
  ("use_it",                True),
  ("xsection",              0.252900*1.08), # CV: scale by factor 1.08 (https://hypernews.cern.ch/HyperNews/CMS/get/HIG-17-004/19/1.html)
  ("genWeight",             True),
  ("triggers",              [ "1e", "1mu", "2e", "1e1mu", "2mu", "3e", "2e1mu", "1e2mu", "3mu", "1e1tau", "1mu1tau", "2tau" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau/MC/TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-pythia8/VHBB_HEPPY_V25tthtautau_TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6_ext2-v1/170207_124710"),
        ("selection", "*"),
        ("blacklist", [389, 499, 550]),
      ]),
    ]
  ),
])
samples_2016["/TTZToLL_M-1to10_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "TTZ"),
  ("process_name_specific", "TTZToLL_M-1to10"),
  ("nof_files",             25),
  ("nof_events",            246788),
  ("use_it",                True),
  ("xsection",              0.049300),
  ("genWeight",             True),
  ("triggers",              [ "1e", "1mu", "2e", "1e1mu", "2mu", "3e", "2e1mu", "1e2mu", "3mu", "1e1tau", "1mu1tau", "2tau" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau/MC/TTZToLL_M-1to10_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/VHBB_HEPPY_V25tthtautau_TTZToLL_M-1to10_TuneCUETP8M1_13TeV-madgraphMLM-Py8__RunIISummer16MAv2-80r2as_2016_TrancheIV_v6-v1/170207_124356"),
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
  ("nof_files",             508),
  ("nof_events",            9683019),
  ("use_it",                True),
  ("xsection",              585.800000),
  ("genWeight",             True),
  ("triggers",              [ "1e", "1mu", "2e", "1e1mu", "2mu", "3e", "2e1mu", "1e2mu", "3mu", "1e1tau", "1mu1tau", "2tau" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/mario/VHBBHeppyV25tthtautau/MC/WGToLNuG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/VHBB_HEPPY_V25tthtautau_WGToLNuG_TuneCUETP8M1_13TeV-amcatnloFXFX-Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6_ext1-v1/170208_121122"),
        ("selection", "*"),
        ("blacklist", [38, 133, 186, 223, 260, 262, 300, 308, 334, 355, 363, 373, 380, 396, 423, 424]),
      ]),
    ]
  ),
])
samples_2016["/WGToLNuG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext2-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "Rares"),
  ("process_name_specific", "WGToLNuG_ext2"),
  ("nof_files",             1033),
  ("nof_events",            9683019),
  ("use_it",                True),
  ("xsection",              585.800000),
  ("genWeight",             True),
  ("triggers",              [ "1e", "1mu", "2e", "1e1mu", "2mu", "3e", "2e1mu", "1e2mu", "3mu", "1e1tau", "1mu1tau", "2tau" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/mario/VHBBHeppyV25tthtautau/MC/WGToLNuG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/VHBB_HEPPY_V25tthtautau_WGToLNuG_TuneCUETP8M1_13TeV-amcatnloFXFX-Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6_ext2-v1/170208_121305"),
        ("selection", "*"),
        ("blacklist", [77, 357, 456, 507, 527, 673, 785]),
      ]),
    ]
  ),
])
samples_2016["/WJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "EWK"),
  ("process_name_specific", "WJetsToLNu"),
  ("nof_files",             2417),
  ("nof_events",            16482922),
  ("use_it",                True),
  ("xsection",              61526.700000),
  ("genWeight",             True),
  ("triggers",              [ "1e", "1mu", "2e", "1e1mu", "2mu", "3e", "2e1mu", "1e2mu", "3mu", "1e1tau", "1mu1tau", "2tau" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/mario/VHBBHeppyV25tthtautau/MC/WJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/VHBB_HEPPY_V25tthtautau_WJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6-v1/170208_121448"),
        ("selection", "*"),
        ("blacklist", [511, 540]),
      ]),
    ]
  ),
])
samples_2016["/WWTo2L2Nu_13TeV-powheg/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "EWK"),
  ("process_name_specific", "WWTo2L2Nu"),
  ("nof_files",             202),
  ("nof_events",            1999091),
  ("use_it",                True),
  ("xsection",              10.481000),
  ("genWeight",             True),
  ("triggers",              [ "1e", "1mu", "2e", "1e1mu", "2mu", "3e", "2e1mu", "1e2mu", "3mu", "1e1tau", "1mu1tau", "2tau" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/veelken/VHBBHeppyV25tthtautau/MC/WWTo2L2Nu_13TeV-powheg/VHBB_HEPPY_V25tthtautau_WWTo2L2Nu_13TeV-powheg__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6-v1/170207_134602"),
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
  ("nof_files",             101),
  ("nof_events",            999310),
  ("use_it",                True),
  ("xsection",              0.172900),
  ("genWeight",             True),
  ("triggers",              [ "1e", "1mu", "2e", "1e1mu", "2mu", "3e", "2e1mu", "1e2mu", "3mu", "1e1tau", "1mu1tau", "2tau" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/veelken/VHBBHeppyV25tthtautau/MC/WWTo2L2Nu_DoubleScattering_13TeV-pythia8/VHBB_HEPPY_V25tthtautau_WWTo2L2Nu_DoubleScattering_13TeV-Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6-v1/170207_134843"),
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
  ("nof_files",             24),
  ("nof_events",            210451),
  ("use_it",                True),
  ("xsection",              0.208600),
  ("genWeight",             True),
  ("triggers",              [ "1e", "1mu", "2e", "1e1mu", "2mu", "3e", "2e1mu", "1e2mu", "3mu", "1e1tau", "1mu1tau", "2tau" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/veelken/VHBBHeppyV25tthtautau/MC/WWW_4F_TuneCUETP8M1_13TeV-amcatnlo-pythia8/VHBB_HEPPY_V25tthtautau_WWW_4F_TuneCUETP8M1_13TeV-amcatnlo-Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6-v1/170207_135107"),
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
  ("nof_files",             26),
  ("nof_events",            221500),
  ("use_it",                True),
  ("xsection",              0.165100),
  ("genWeight",             True),
  ("triggers",              [ "1e", "1mu", "2e", "1e1mu", "2mu", "3e", "2e1mu", "1e2mu", "3mu", "1e1tau", "1mu1tau", "2tau" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/veelken/VHBBHeppyV25tthtautau/MC/WWZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8/VHBB_HEPPY_V25tthtautau_WWZ_TuneCUETP8M1_13TeV-amcatnlo-Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6-v1/170207_135405"),
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
  ("nof_files",             200),
  ("nof_events",            1993205),
  ("use_it",                True),
  ("xsection",              4.429650),
  ("genWeight",             True),
  ("triggers",              [ "1e", "1mu", "2e", "1e1mu", "2mu", "3e", "2e1mu", "1e2mu", "3mu", "1e1tau", "1mu1tau", "2tau" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau/MC/WZTo3LNu_TuneCUETP8M1_13TeV-powheg-pythia8/VHBB_HEPPY_V25tthtautau_WZTo3LNu_TuneCUETP8M1_13TeV-powheg-Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6-v1/170207_124837"),
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
  ("nof_files",             25),
  ("nof_events",            216284),
  ("use_it",                True),
  ("xsection",              0.055650),
  ("genWeight",             True),
  ("triggers",              [ "1e", "1mu", "2e", "1e1mu", "2mu", "3e", "2e1mu", "1e2mu", "3mu", "1e1tau", "1mu1tau", "2tau" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau/MC/WZZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8/VHBB_HEPPY_V25tthtautau_WZZ_TuneCUETP8M1_13TeV-amcatnlo-Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6-v1/170207_125000"),
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
  ("nof_files",             16),
  ("nof_events",            149594),
  ("use_it",                True),
  ("xsection",              0.037110),
  ("genWeight",             True),
  ("triggers",              [ "1e", "1mu", "2e", "1e1mu", "2mu", "3e", "2e1mu", "1e2mu", "3mu", "1e1tau", "1mu1tau", "2tau" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau/MC/WpWpJJ_EWK-QCD_TuneCUETP8M1_13TeV-madgraph-pythia8/VHBB_HEPPY_V25tthtautau_WpWpJJ_EWK-QCD_TuneCUETP8M1_13TeV-madgraph-Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6-v1/170207_125131"),
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
  ("nof_files",             1447),
  ("nof_events",            9242330),
  ("use_it",                True),
  ("xsection",              131.300000),
  ("genWeight",             True),
  ("triggers",              [ "1e", "1mu", "2e", "1e1mu", "2mu", "3e", "2e1mu", "1e2mu", "3mu", "1e1tau", "1mu1tau", "2tau" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/rdewanje/VHBBHeppyV25tthtautau/MC/ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/VHBB_HEPPY_V25tthtautau_ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6_ext1-v1/170207_124611"),
        ("selection", "*"),
        ("blacklist", [52, 77, 92, 105, 239, 248, 296, 306, 307, 310, 336, 347, 354, 368, 372, 383, 394, 403, 408, 420, 470, 472, 480, 488, 506, 521, 551, 553, 570, 595, 614, 650, 675, 678, 716, 747, 755, 775, 779, 790, 791, 820, 827, 840, 847, 885, 899, 901, 909, 911, 915, 919, 929, 932, 942, 945, 947, 949, 950, 1001, 1007, 1013, 1017, 1018, 1028, 1029, 1030, 1031, 1038, 1041, 1129, 1130, 1139, 1144, 1152, 1157, 1163, 1165, 1177, 1279, 1283, 1307, 1308, 1339, 1345, 1349, 1351]),
      ]),
    ]
  ),
])
samples_2016["/ZZTo4L_13TeV_powheg_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "EWK"),
  ("process_name_specific", "ZZTo4L"),
  ("nof_files",             673),
  ("nof_events",            6610878),
  ("use_it",                True),
  ("xsection",              1.256000),
  ("genWeight",             True),
  ("triggers",              [ "1e", "1mu", "2e", "1e1mu", "2mu", "3e", "2e1mu", "1e2mu", "3mu", "1e1tau", "1mu1tau", "2tau" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau/MC/ZZTo4L_13TeV_powheg_pythia8/VHBB_HEPPY_V25tthtautau_ZZTo4L_13TeV_powheg_Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6-v1/170207_125252"),
        ("selection", "*"),
        ("blacklist", [169, 298, 436, 454, 551, 653]),
      ]),
    ]
  ),
])
samples_2016["/ZZZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "Rares"),
  ("process_name_specific", "ZZZ"),
  ("nof_files",             25),
  ("nof_events",            213086),
  ("use_it",                True),
  ("xsection",              0.013980),
  ("genWeight",             True),
  ("triggers",              [ "1e", "1mu", "2e", "1e1mu", "2mu", "3e", "2e1mu", "1e2mu", "3mu", "1e1tau", "1mu1tau", "2tau" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau/MC/ZZZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8/VHBB_HEPPY_V25tthtautau_ZZZ_TuneCUETP8M1_13TeV-amcatnlo-Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6-v1/170207_125415"),
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
  ("nof_files",             1464),
  ("nof_events",            3805895),
  ("use_it",                True),
  ("xsection",              0.075800),
  ("genWeight",             True),
  ("triggers",              [ "1e", "1mu", "2e", "1e1mu", "2mu", "3e", "2e1mu", "1e2mu", "3mu", "1e1tau", "1mu1tau", "2tau" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/mario/VHBBHeppyV25tthtautau/MC/tZq_ll_4f_13TeV-amcatnlo-pythia8/VHBB_HEPPY_V25tthtautau_tZq_ll_4f_13TeV-amcatnlo-Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6_ext1-v1/170208_121616"),
        ("selection", "*"),
        ("blacklist", [76, 213, 344, 424, 970, 1009, 1173, 1249, 1255, 1308, 1333, 1380, 1388, 1389, 1444]),
      ]),
    ]
  ),
])
samples_2016["/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "signal"),
  ("process_name_specific", "ttHJetToNonbb_M125_amcatnlo"),
  ("nof_files",             1018),
  ("nof_events",            2969555),
  ("use_it",                True),
  ("xsection",              0.215100),
  ("genWeight",             True),
  ("triggers",              [ "1e", "1mu", "2e", "1e1mu", "2mu", "3e", "2e1mu", "1e2mu", "3mu", "1e1tau", "1mu1tau", "2tau" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau/MC/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/VHBB_HEPPY_V25tthtautau_ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_Py8_mWCutfix__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6_ext1-v1/170207_122849"),
        ("selection", "*"),
        ("blacklist", [645, 835, 909, 986]),
      ]),
    ]
  ),
])
samples_2016["/ttHToNonbb_M125_TuneCUETP8M2_ttHtranche3_13TeV-powheg-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "signal"),
  ("process_name_specific", "ttHToNonbb_M125_powheg"),
  ("nof_files",             402),
  ("nof_events",            3819298),
  ("use_it",                False),
  ("xsection",              0.215100),
  ("genWeight",             True),
  ("triggers",              [ "1e", "1mu", "2e", "1e1mu", "2mu", "3e", "2e1mu", "1e2mu", "3mu", "1e1tau", "1mu1tau", "2tau" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/rdewanje/VHBBHeppyV25tthtautau/MC/ttHToNonbb_M125_TuneCUETP8M2_ttHtranche3_13TeV-powheg-pythia8/VHBB_HEPPY_V25tthtautau_ttHToNonbb_M125_TuneCUETP8M2_ttHtranche3_13TeV-powheg-Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6-v1/170207_122923"),
        ("selection", "*"),
        ("blacklist", [11, 39, 137, 225, 281, 304, 312, 335, 397]),
      ]),
    ]
  ),
])
samples_2016["/TTJets_SingleLeptFromTbar_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "TT"),
  ("process_name_specific", "TTJets_SingleLeptFromTbar_ext1"),
  ("nof_files",             4870),
  ("nof_events",            60202982),
  ("use_it",                True),
  ("xsection",              182.180000),
  ("genWeight",             True),
  ("triggers",              [ "1e", "1mu", "2e", "1e1mu", "2mu", "3e", "2e1mu", "1e2mu", "3mu", "1e1tau", "1mu1tau", "2tau" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v2/MC/TTJets_SingleLeptFromTbar_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/VHBB_HEPPY_V25tthtautau_v2_TTJets_SingleLeptFromTbar_TuneCUETP8M1_13TeV-madgraphMLM-Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6_ext1-v1/170217_230025"),
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
  ("nof_files",             988),
  ("nof_events",            2909941),
  ("use_it",                True),
  ("xsection",              0.293400),
  ("genWeight",             True),
  ("triggers",              [ "1e", "1mu", "2e", "1e1mu", "2mu", "3e", "2e1mu", "1e2mu", "3mu", "1e1tau", "1mu1tau", "2tau" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v2/MC/ttHJetTobb_M125_13TeV_amcatnloFXFX_madspin_pythia8/VHBB_HEPPY_V25tthtautau_v2_ttHJetTobb_M125_13TeV_amcatnloFXFX_madspin_Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6_ext3-v1/170217_224718"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])

#Fastsim
samples_2016["/TTTo2L2Nu_TuneCUETP8M2_ttHtranche3_13TeV-powheg-pythia8/matze-faster_v8_ttjets_dl_maod_p1_3a2fa29ab1d54ae0995b28f27b405be9-v1/USER"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "TT"),
  ("process_name_specific", "TTTo2L2Nu_fastsim_p1"),
  ("nof_files",             1822),
  ("nof_events",            90523463),
  ("use_it",                False),
  ("xsection",              87.300000),
  ("genWeight",             True),
  ("triggers",              [ "1e", "1mu", "2e", "1e1mu", "2mu", "3e", "2e1mu", "1e2mu", "3mu", "1e1tau", "1mu1tau", "2tau" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau/MC_fastsim/TTTo2L2Nu_TuneCUETP8M2_ttHtranche3_13TeV-powheg-pythia8/VHBB_HEPPY_V25tthtautau_TTTo2L2Nu_TuneCUETP8M2_ttHtranche3_13TeV-powheg-Py8__matze-faster_v8_ttjets_dl_maod_p1_3a2fa29ab1d54ae0995b28f27b405be9-v1/170207_130407"),
        ("selection", "*"),
        ("blacklist", [267]),
      ]),
    ]
  ),
])
samples_2016["/TTTo2L2Nu_TuneCUETP8M2_ttHtranche3_13TeV-powheg-pythia8/matze-faster_v8_ttjets_dl_maod_p2_3a2fa29ab1d54ae0995b28f27b405be9-v1/USER"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "TT"),
  ("process_name_specific", "TTTo2L2Nu_fastsim_p2"),
  ("nof_files",             3646),
  ("nof_events",            90523463),
  ("use_it",                False),
  ("xsection",              87.300000),
  ("genWeight",             True),
  ("triggers",              [ "1e", "1mu", "2e", "1e1mu", "2mu", "3e", "2e1mu", "1e2mu", "3mu", "1e1tau", "1mu1tau", "2tau" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/veelken/VHBBHeppyV25tthtautau/MC_fastsim/TTTo2L2Nu_TuneCUETP8M2_ttHtranche3_13TeV-powheg-pythia8/VHBB_HEPPY_V25tthtautau_TTTo2L2Nu_TuneCUETP8M2_ttHtranche3_13TeV-powheg-Py8__matze-faster_v8_ttjets_dl_maod_p2_3a2fa29ab1d54ae0995b28f27b405be9-v1/170208_163923"),
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
  ("nof_files",             3642),
  ("nof_events",            90523463),
  ("use_it",                False),
  ("xsection",              87.300000),
  ("genWeight",             True),
  ("triggers",              [ "1e", "1mu", "2e", "1e1mu", "2mu", "3e", "2e1mu", "1e2mu", "3mu", "1e1tau", "1mu1tau", "2tau" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau/MC_fastsim/TTTo2L2Nu_TuneCUETP8M2_ttHtranche3_13TeV-powheg-pythia8/VHBB_HEPPY_V25tthtautau_TTTo2L2Nu_TuneCUETP8M2_ttHtranche3_13TeV-powheg-Py8__matze-faster_v8_ttjets_dl_maod_p3_3a2fa29ab1d54ae0995b28f27b405be9-v1/170208_163840"),
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
  ("nof_files",             1702),
  ("nof_events",            85307397),
  ("use_it",                False),
  ("xsection",              245.000000),
  ("genWeight",             True),
  ("triggers",              [ "1e", "1mu", "2e", "1e1mu", "2mu", "3e", "2e1mu", "1e2mu", "3mu", "1e1tau", "1mu1tau", "2tau" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/veelken/VHBBHeppyV25tthtautau/MC_fastsim/TTToSemilepton_TuneCUETP8M2_ttHtranche3_13TeV-powheg-pythia8/VHBB_HEPPY_V25tthtautau_TTToSemilepton_TuneCUETP8M2_ttHtranche3_13TeV-powheg-Py8__matze-faster_v8_ttjets_sl_maod_p1_3a2fa29ab1d54ae0995b28f27b405be9-v1/170207_153448"),
        ("selection", "*"),
        ("blacklist", [940, 1042]),
      ]),
    ]
  ),
])
samples_2016["/TTToSemilepton_TuneCUETP8M2_ttHtranche3_13TeV-powheg-pythia8/matze-faster_v8_ttjets_sl_maod_p2_3a2fa29ab1d54ae0995b28f27b405be9-v1/USER"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "TT"),
  ("process_name_specific", "TTToSemilepton_fastsim_p2"),
  ("nof_files",             3403),
  ("nof_events",            85307397),
  ("use_it",                False),
  ("xsection",              245.000000),
  ("genWeight",             True),
  ("triggers",              [ "1e", "1mu", "2e", "1e1mu", "2mu", "3e", "2e1mu", "1e2mu", "3mu", "1e1tau", "1mu1tau", "2tau" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau/MC_fastsim/TTToSemilepton_TuneCUETP8M2_ttHtranche3_13TeV-powheg-pythia8/VHBB_HEPPY_V25tthtautau_TTToSemilepton_TuneCUETP8M2_ttHtranche3_13TeV-powheg-Py8__matze-faster_v8_ttjets_sl_maod_p2_3a2fa29ab1d54ae0995b28f27b405be9-v1/170208_162433"),
        ("selection", "*"),
        ("blacklist", [1891]),
      ]),
    ]
  ),
])
samples_2016["/TTToSemilepton_TuneCUETP8M2_ttHtranche3_13TeV-powheg-pythia8/matze-faster_v8_ttjets_sl_maod_p3_3a2fa29ab1d54ae0995b28f27b405be9-v1/USER"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "TT"),
  ("process_name_specific", "TTToSemilepton_fastsim_p3"),
  ("nof_files",             3404),
  ("nof_events",            85307397),
  ("use_it",                False),
  ("xsection",              245.000000),
  ("genWeight",             True),
  ("triggers",              [ "1e", "1mu", "2e", "1e1mu", "2mu", "3e", "2e1mu", "1e2mu", "3mu", "1e1tau", "1mu1tau", "2tau" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/rdewanje/VHBBHeppyV25tthtautau/MC_fastsim/TTToSemilepton_TuneCUETP8M2_ttHtranche3_13TeV-powheg-pythia8/VHBB_HEPPY_V25tthtautau_TTToSemilepton_TuneCUETP8M2_ttHtranche3_13TeV-powheg-Py8__matze-faster_v8_ttjets_sl_maod_p3_3a2fa29ab1d54ae0995b28f27b405be9-v1/170209_090617"),
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
  ("nof_files",             1408),
  ("nof_events",            7157601),
  ("use_it",                False),
  ("xsection",              0.204300),
  ("genWeight",             True),
  ("triggers",              [ "1e", "1mu", "2e", "1e1mu", "2mu", "3e", "2e1mu", "1e2mu", "3mu", "1e1tau", "1mu1tau", "2tau" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/veelken/VHBBHeppyV25tthtautau/MC_fastsim/TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/VHBB_HEPPY_V25tthtautau_TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-Py8__matze-faster_v9_ttW_maod_54aa74f75231422e9f4d3766cb92a64a-v1/170208_163631"),
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
  ("nof_files",             1945),
  ("nof_events",            8825723),
  ("use_it",                False),
  ("xsection",              0.252900),
  ("genWeight",             True),
  ("triggers",              [ "1e", "1mu", "2e", "1e1mu", "2mu", "3e", "2e1mu", "1e2mu", "3mu", "1e1tau", "1mu1tau", "2tau" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/mario/VHBBHeppyV25tthtautau/MC_fastsim/TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-pythia8/VHBB_HEPPY_V25tthtautau_TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-Py8__matze-faster_v9_ttZ_maod_54aa74f75231422e9f4d3766cb92a64a-v1/170208_172612"),
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
  ("nof_files",             1876),
  ("nof_events",            18813875),
  ("use_it",                False),
  ("xsection",              4.102000),
  ("genWeight",             True),
  ("triggers",              [ "1e", "1mu", "2e", "1e1mu", "2mu", "3e", "2e1mu", "1e2mu", "3mu", "1e1tau", "1mu1tau", "2tau" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/rdewanje/VHBBHeppyV25tthtautau/MC_fastsim/WZTo3LNu_TuneCUETP8M1_13TeV-powheg-pythia8/VHBB_HEPPY_V25tthtautau_WZTo3LNu_TuneCUETP8M1_13TeV-powheg-Py8__matze-faster_v9_WZ_maod_54aa74f75231422e9f4d3766cb92a64a-v1/170209_090741"),
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
  ("nof_files",             337),
  ("nof_events",            16458549),
  ("use_it",                False),
  ("xsection",              0.215100),
  ("genWeight",             True),
  ("triggers",              [ "1e", "1mu", "2e", "1e1mu", "2mu", "3e", "2e1mu", "1e2mu", "3mu", "1e1tau", "1mu1tau", "2tau" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/rdewanje/VHBBHeppyV25tthtautau/MC_fastsim/ttHToNonbb_M125_TuneCUETP8M2_ttHtranche3_13TeV-powheg-pythia8/VHBB_HEPPY_V25tthtautau_ttHToNonbb_M125_TuneCUETP8M2_ttHtranche3_13TeV-powheg-Py8__matze-faster_v8_ttH_maod_p1_3a2fa29ab1d54ae0995b28f27b405be9-v1/170207_130941"),
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
  ("nof_files",             674),
  ("nof_events",            16458549),
  ("use_it",                False),
  ("xsection",              0.215100),
  ("genWeight",             True),
  ("triggers",              [ "1e", "1mu", "2e", "1e1mu", "2mu", "3e", "2e1mu", "1e2mu", "3mu", "1e1tau", "1mu1tau", "2tau" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau/MC_fastsim/ttHToNonbb_M125_TuneCUETP8M2_ttHtranche3_13TeV-powheg-pythia8/VHBB_HEPPY_V25tthtautau_ttHToNonbb_M125_TuneCUETP8M2_ttHtranche3_13TeV-powheg-Py8__matze-faster_v8_ttH_maod_p2_3a2fa29ab1d54ae0995b28f27b405be9-v1/170208_162259"),
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
  ("nof_files",             674),
  ("nof_events",            16458549),
  ("use_it",                False),
  ("xsection",              0.215100),
  ("genWeight",             True),
  ("triggers",              [ "1e", "1mu", "2e", "1e1mu", "2mu", "3e", "2e1mu", "1e2mu", "3mu", "1e1tau", "1mu1tau", "2tau" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/mario/VHBBHeppyV25tthtautau/MC_fastsim/ttHToNonbb_M125_TuneCUETP8M2_ttHtranche3_13TeV-powheg-pythia8/VHBB_HEPPY_V25tthtautau_ttHToNonbb_M125_TuneCUETP8M2_ttHtranche3_13TeV-powheg-Py8__matze-faster_v8_ttH_maod_p3_3a2fa29ab1d54ae0995b28f27b405be9-v1/170208_124342"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])


#--------------------------------------------------------------------------------
# !!! ONLY FOR TESTING
## samples_2016 = OD()
## samples_2016["/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"] = OD([
##   ("type",                  "mc"),
##   ("sample_category",       "signal"),
##   ("process_name_specific", "ttHJetToNonbb_M125_amcatnlo"),
##   ("nof_files",             1018),
##   ("nof_events",            2969555),
##   ("use_it",                True),
##   ("xsection",              0.215100),
##   ("genWeight",             True),
##   ("triggers",              [ "1e", "1mu", "2e", "1e1mu", "2mu", "3e", "2e1mu", "1e2mu", "3mu", "1e1tau", "1mu1tau", "2tau" ]),
##   ("reHLT",                 True),
##   ("local_paths",
##     [
##       OD([
##         ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau/MC/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/VHBB_HEPPY_V25tthtautau_ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_Py8_mWCutfix__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6_ext1-v1/170207_122849"),
##         ("selection", "*"),
##         ("blacklist", [645, 835, 909, 986]),
##       ]),
##     ]
##   ),
## ])
#     FOR TESTING ONLY !!!
#--------------------------------------------------------------------------------
