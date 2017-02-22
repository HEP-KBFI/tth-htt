from collections import OrderedDict as OD

samples_2016 = OD()

# file generated with command:
# check_broken -p /hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau/MC/ /hdfs/cms/store/user/mario/VHBBHeppyV25tthtautau/MC/ /hdfs/cms/store/user/rdewanje/VHBBHeppyV25tthtautau/MC/ /hdfs/cms/store/user/veelken/VHBBHeppyV25tthtautau/MC/ /hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v2/MC --histo CountWeighted --output=. -P -z -v

# file generated with command:
# check_broken -p /hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau/MC_fastsim/ /hdfs/cms/store/user/mario/VHBBHeppyV25tthtautau/MC_fastsim/ /hdfs/cms/store/user/rdewanje/VHBBHeppyV25tthtautau/MC_fastsim/ /hdfs/cms/store/user/veelken/VHBBHeppyV25tthtautau/MC_fastsim/ --histo CountWeighted --output=. -P -z -v

#############
# DoubleEG
#############

# file generated with command:
# check_broken -p /hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau/ /hdfs/cms/store/user/mario/VHBBHeppyV25tthtautau/ /hdfs/cms/store/user/rdewanje/VHBBHeppyV25tthtautau/ /hdfs/cms/store/user/veelken/VHBBHeppyV25tthtautau/ /hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v2 --histo CountWeighted --output=samples/DoubleEG/ -P -z -v -d -f DoubleEG

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
  ("nof_files",             2682),
  ("nof_events",            47642368),
  ("use_HIP_mitigation_bTag", True),
  ("use_HIP_mitigation_mediumMuonId", True),
  ("use_it",                True),
  ("triggers",              [ "2e", "3e" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/veelken/VHBBHeppyV25tthtautau/DoubleEG/VHBB_HEPPY_V25tthtautau_DoubleEG__Run2016C-23Sep2016-v1/170207_141622"),
        ("selection", "*"),
        ("blacklist", [846, 2110]),
      ]),
    ]
  ),
])
samples_2016["/DoubleEG/Run2016E-23Sep2016-v1/MINIAOD"] = OD([
  ("type",                  "data"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "DoubleEG_Run2016E_v1"),
  ("nof_files",             3879),
  ("nof_events",            49584823),
  ("use_HIP_mitigation_bTag", True),
  ("use_HIP_mitigation_mediumMuonId", True),
  ("use_it",                True),
  ("triggers",              [ "2e", "3e" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/mario/VHBBHeppyV25tthtautau/DoubleEG/VHBB_HEPPY_V25tthtautau_DoubleEG__Run2016E-23Sep2016-v1/170208_123006"),
        ("selection", "*"),
        ("blacklist", [39, 140, 301, 381, 520, 721, 726, 732, 752, 774, 823, 848, 935, 1317, 2630, 2751, 2788, 2875, 3141, 3361, 3461, 3772, 3841]),
      ]),
    ]
  ),
])
samples_2016["/DoubleEG/Run2016G-23Sep2016-v1/MINIAOD"] = OD([
  ("type",                  "data"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "DoubleEG_Run2016G_v1"),
  ("nof_files",             6617),
  ("nof_events",            78507187),
  ("use_HIP_mitigation_bTag", False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                True),
  ("triggers",              [ "2e", "3e" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/rdewanje/VHBBHeppyV25tthtautau/DoubleEG/VHBB_HEPPY_V25tthtautau_DoubleEG__Run2016G-23Sep2016-v1/170207_125027"),
        ("selection", "*"),
        ("blacklist", [91, 1260, 1365, 1654, 1841, 1938, 1941, 2446, 2751, 2809, 3635, 3825, 3857, 4752, 5469, 5540, 5582, 5590, 5625, 5632, 5668, 5702, 5980, 6017]),
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
  ("nof_files",             194),
  ("nof_events",            2071593),
  ("use_HIP_mitigation_bTag", False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                True),
  ("triggers",              [ "2e", "3e" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau/DoubleEG/VHBB_HEPPY_V25tthtautau_DoubleEG__Run2016H-PromptReco-v3/170215_143652"),
        ("selection", "*"),
        ("blacklist", [9, 177, 179, 180, 182, 183, 184, 185, 186, 187, 188, 190, 191]),
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
# check_broken -p /hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau/ /hdfs/cms/store/user/mario/VHBBHeppyV25tthtautau/ /hdfs/cms/store/user/rdewanje/VHBBHeppyV25tthtautau/ /hdfs/cms/store/user/veelken/VHBBHeppyV25tthtautau/ /hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v2 --histo CountWeighted --output=samples/DoubleMuon/ -P -z -v -d -f DoubleMuon

samples_2016["/DoubleMuon/Run2016B-23Sep2016-v3/MINIAOD"] = OD([
  ("type",                  "data"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "DoubleMuon_Run2016B_v3"),
  ("nof_files",             1966),
  ("nof_events",            82482018),
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
        ("blacklist", [1754]),
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
# check_broken -p /hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau/ /hdfs/cms/store/user/mario/VHBBHeppyV25tthtautau/ /hdfs/cms/store/user/rdewanje/VHBBHeppyV25tthtautau/ /hdfs/cms/store/user/veelken/VHBBHeppyV25tthtautau/ /hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v2 --histo CountWeighted --output=samples/MuonEG/ -P -z -v -d -f MuonEG

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
  ("nof_files",             8180),
  ("nof_events",            27973219),
  ("use_HIP_mitigation_bTag", False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                True),
  ("triggers",              [ "1e1mu", "2e1mu", "1e2mu" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau/MuonEG/VHBB_HEPPY_V25tthtautau_MuonEG__Run2016H-PromptReco-v2/170215_143258"),
        ("selection", "*"),
        ("blacklist", [937, 1020, 1021, 1022, 1031, 1033, 1034, 1037, 1039, 1040, 1044, 1045, 1047, 1048, 1049, 1052, 1054, 1057, 1058, 1059, 1060, 1061, 1062, 1065, 1066, 1073, 1077, 1079, 1080, 1081, 1118, 1120, 1122, 1123, 1127, 1128, 1135, 1136, 1138, 1141, 1142, 1151, 1152, 1156, 1160, 1164, 1167, 1174, 1178, 1185, 1187, 1188, 1191, 1193, 1197, 1202, 1205, 1207, 1209, 1210, 1217, 1219, 1222, 1223, 1226, 1227, 1228, 1230, 1232, 1238, 1242, 1245, 1249, 1253, 1254, 1255, 1260, 1262, 1263, 1264, 1267, 1268, 1269, 1270, 1271, 1272, 1273, 1274, 1276, 1278, 1279, 1280, 1281, 1282, 1283, 1284, 1289, 1299, 1300, 1301, 1305, 1306, 1307, 1308, 1316, 1321, 1322, 1324, 1325, 1326, 1329, 1330, 1331, 1338, 1339, 1340, 1342, 1344, 1346, 1347, 1348, 1349, 1350, 1352, 1353, 1354, 1355, 1356, 1357, 1358, 1360, 1362, 1363, 1364, 1365, 1367, 1369, 1370, 1375, 1377, 1384, 1385, 1386, 1387, 1388, 1389, 1390, 1391, 1392, 1393, 1394, 1396, 1398, 1399, 1400, 1401, 1404, 1406, 1407, 1409, 1411, 1412, 1414, 1415, 1419, 1425, 1426, 1428, 2222, 2818, 3430, 3949, 4005, 4157, 4306, 5912, 6093, 6154, 6675, 6810, 7375, 7631, 7791]),
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
# check_broken -p /hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau/ /hdfs/cms/store/user/mario/VHBBHeppyV25tthtautau/ /hdfs/cms/store/user/rdewanje/VHBBHeppyV25tthtautau/ /hdfs/cms/store/user/veelken/VHBBHeppyV25tthtautau/ /hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v2 --histo CountWeighted --output=samples/SingleElectron/ -P -z -v -d -f SingleElectron

samples_2016["/SingleElectron/Run2016B-23Sep2016-v3/MINIAOD"] = OD([
  ("type",                  "data"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "SingleElectron_Run2016B_v3"),
  ("nof_files",             8546),
  ("nof_events",            245263644),
  ("use_HIP_mitigation_bTag", True),
  ("use_HIP_mitigation_mediumMuonId", True),
  ("use_it",                True),
  ("triggers",              [ "1e" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau/SingleElectron/VHBB_HEPPY_V25tthtautau_SingleElectron__Run2016B-23Sep2016-v3/170207_125603"),
        ("selection", "*"),
        ("blacklist", [2230, 2533, 2590, 3150, 3382, 3388, 3916, 4341, 4375, 4442, 4715, 4856, 5236, 5494, 5557, 5605, 5710, 5725, 5731, 5736, 5737, 5753, 5774, 5781, 5795, 5810, 5822, 5902, 5939, 5947, 5960, 5972, 6012, 6029, 6058]),
      ]),
    ]
  ),
])
samples_2016["/SingleElectron/Run2016C-23Sep2016-v1/MINIAOD"] = OD([
  ("type",                  "data"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "SingleElectron_Run2016C_v1"),
  ("nof_files",             2682),
  ("nof_events",            97227128),
  ("use_HIP_mitigation_bTag", True),
  ("use_HIP_mitigation_mediumMuonId", True),
  ("use_it",                True),
  ("triggers",              [ "1e" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/veelken/VHBBHeppyV25tthtautau/SingleElectron/VHBB_HEPPY_V25tthtautau_SingleElectron__Run2016C-23Sep2016-v1/170207_135748"),
        ("selection", "*"),
        ("blacklist", [1992]),
      ]),
    ]
  ),
])
samples_2016["/SingleElectron/Run2016D-23Sep2016-v1/MINIAOD"] = OD([
  ("type",                  "data"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "SingleElectron_Run2016D_v1"),
  ("nof_files",             4320),
  ("nof_events",            147620964),
  ("use_HIP_mitigation_bTag", True),
  ("use_HIP_mitigation_mediumMuonId", True),
  ("use_it",                True),
  ("triggers",              [ "1e" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/rdewanje/VHBBHeppyV25tthtautau/SingleElectron/VHBB_HEPPY_V25tthtautau_SingleElectron__Run2016D-23Sep2016-v1/170207_125742"),
        ("selection", "*"),
        ("blacklist", [158, 502, 515, 636, 704, 735, 900, 935, 1175, 1461, 1535, 2692, 3004, 3075, 4240]),
      ]),
    ]
  ),
])
samples_2016["/SingleElectron/Run2016E-23Sep2016-v1/MINIAOD"] = OD([
  ("type",                  "data"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "SingleElectron_Run2016E_v1"),
  ("nof_files",             3879),
  ("nof_events",            116250164),
  ("use_HIP_mitigation_bTag", True),
  ("use_HIP_mitigation_mediumMuonId", True),
  ("use_it",                True),
  ("triggers",              [ "1e" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/mario/VHBBHeppyV25tthtautau/SingleElectron/VHBB_HEPPY_V25tthtautau_SingleElectron__Run2016E-23Sep2016-v1/170208_123632"),
        ("selection", "*"),
        ("blacklist", [42, 104, 136, 142, 183, 215, 253, 263, 366, 370, 401, 416, 1084, 1287, 1317, 1430, 1576, 1641, 1707, 1836, 1905, 2259, 2265, 2633, 2634, 2698, 2990, 3102, 3234, 3361, 3395, 3504, 3691, 3705, 3877]),
      ]),
    ]
  ),
])
samples_2016["/SingleElectron/Run2016F-23Sep2016-v1/MINIAOD"] = OD([
  ("type",                  "data"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "SingleElectron_Run2016F_v1"),
  ("nof_files",             2778),
  ("nof_events",            70319143),
  ("use_HIP_mitigation_bTag", True),
  ("use_HIP_mitigation_mediumMuonId", True),
  ("use_it",                True),
  ("triggers",              [ "1e" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/rdewanje/VHBBHeppyV25tthtautau/SingleElectron/VHBB_HEPPY_V25tthtautau_SingleElectron__Run2016F-23Sep2016-v1/170207_125920"),
        ("selection", "*"),
        ("blacklist", [566, 959, 1484, 1980, 2038, 2118, 2179, 2204, 2340, 2473]),
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
  ("nof_files",             194),
  ("nof_events",            3184905),
  ("use_HIP_mitigation_bTag", False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                True),
  ("triggers",              [ "1e" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau/SingleElectron/VHBB_HEPPY_V25tthtautau_SingleElectron__Run2016H-PromptReco-v3/170215_143535"),
        ("selection", "*"),
        ("blacklist", [143]),
      ]),
    ]
  ),
])
samples_2016["/SingleElectron/Run2016G-23Sep2016-v1/MINIAOD"] = OD([
  ("type",                  "data"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "SingleElectron_Run2016G_v1"),
  ("nof_files",             1544),
  ("nof_events",            152508182),
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
        ("blacklist", [351, 451, 1120, 1312, 1322, 1404, 1434]),
      ]),
    ]
  ),
])

#############
# SingleMuon
#############

# file generated with command:
# check_broken -p /hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau/ /hdfs/cms/store/user/mario/VHBBHeppyV25tthtautau/ /hdfs/cms/store/user/rdewanje/VHBBHeppyV25tthtautau/ /hdfs/cms/store/user/veelken/VHBBHeppyV25tthtautau/ /hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v2 --histo CountWeighted --output=samples/SingleMuon/ -P -z -v -d -f SingleMuon

samples_2016["/SingleMuon/Run2016B-23Sep2016-v3/MINIAOD"] = OD([
  ("type",                  "data"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "SingleMuon_Run2016B_v3"),
  ("nof_files",             8424),
  ("nof_events",            157059503),
  ("use_HIP_mitigation_bTag", True),
  ("use_HIP_mitigation_mediumMuonId", True),
  ("use_it",                True),
  ("triggers",              [ "1mu" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau/SingleMuon/VHBB_HEPPY_V25tthtautau_SingleMuon__Run2016B-23Sep2016-v3/170207_130211"),
        ("selection", "*"),
        ("blacklist", [609, 810, 828, 881, 908, 957, 963, 1522, 1565, 1651, 1727, 1930, 1993, 2203, 2366, 3356, 4158, 4429, 4476, 4828, 4829, 4907, 4926, 4956, 5005, 5160, 5257, 5293, 5360, 5400, 5484, 5632, 5751, 5898, 5928, 5970, 6215, 6356, 6357, 6363, 6391, 6489, 6493, 6615, 6746, 6815, 6969, 6973, 7191, 7202, 7231, 7263, 7409, 8034, 8324]),
      ]),
    ]
  ),
])
samples_2016["/SingleMuon/Run2016C-23Sep2016-v1/MINIAOD"] = OD([
  ("type",                  "data"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "SingleMuon_Run2016C_v1"),
  ("nof_files",             2659),
  ("nof_events",            66803613),
  ("use_HIP_mitigation_bTag", True),
  ("use_HIP_mitigation_mediumMuonId", True),
  ("use_it",                True),
  ("triggers",              [ "1mu" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/veelken/VHBBHeppyV25tthtautau/SingleMuon/VHBB_HEPPY_V25tthtautau_SingleMuon__Run2016C-23Sep2016-v1/170207_140442"),
        ("selection", "*"),
        ("blacklist", [64, 470, 755, 811, 1006, 1322, 1429, 1498, 1613, 1714, 1912, 1943, 1967, 1986, 2032, 2056, 2114, 2129, 2211, 2243, 2343, 2372, 2374, 2394, 2601]),
      ]),
    ]
  ),
])
samples_2016["/SingleMuon/Run2016D-23Sep2016-v1/MINIAOD"] = OD([
  ("type",                  "data"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "SingleMuon_Run2016D_v1"),
  ("nof_files",             1003),
  ("nof_events",            97891172),
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
        ("blacklist", [908]),
      ]),
    ]
  ),
])
samples_2016["/SingleMuon/Run2016E-23Sep2016-v1/MINIAOD"] = OD([
  ("type",                  "data"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "SingleMuon_Run2016E_v1"),
  ("nof_files",             3839),
  ("nof_events",            90393704),
  ("use_HIP_mitigation_bTag", True),
  ("use_HIP_mitigation_mediumMuonId", True),
  ("use_it",                True),
  ("triggers",              [ "1mu" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/mario/VHBBHeppyV25tthtautau/SingleMuon/VHBB_HEPPY_V25tthtautau_SingleMuon__Run2016E-23Sep2016-v1/170208_123822"),
        ("selection", "*"),
        ("blacklist", [514, 688, 1072, 1127, 1144, 1151, 1185, 1251, 1297, 1337, 1499, 1676, 1831, 2065, 2247, 2270, 2312, 2595, 2756, 2822, 2898, 3161, 3173, 3660, 3669, 3703]),
      ]),
    ]
  ),
])
samples_2016["/SingleMuon/Run2016F-23Sep2016-v1/MINIAOD"] = OD([
  ("type",                  "data"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "SingleMuon_Run2016F_v1"),
  ("nof_files",             2744),
  ("nof_events",            65456131),
  ("use_HIP_mitigation_bTag", True),
  ("use_HIP_mitigation_mediumMuonId", True),
  ("use_it",                True),
  ("triggers",              [ "1mu" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/rdewanje/VHBBHeppyV25tthtautau/SingleMuon/VHBB_HEPPY_V25tthtautau_SingleMuon__Run2016F-23Sep2016-v1/170207_130226"),
        ("selection", "*"),
        ("blacklist", [118, 584]),
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
  ("nof_files",             6649),
  ("nof_events",            79091354),
  ("use_HIP_mitigation_bTag", False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                True),
  ("triggers",              [ "1e1tau", "1mu1tau", "2tau" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/veelken/VHBBHeppyV25tthtautau/Tau/VHBB_HEPPY_V25tthtautau_Tau__Run2016G-23Sep2016-v1/170207_141423"),
        ("selection", "*"),
        ("blacklist", [799, 921, 1098, 1432, 1814, 1965, 2005, 2055, 2577, 2616, 2782, 2884, 2897, 2939, 2992, 3082, 3248, 3286, 3317, 3331, 3450, 3490, 3495, 3535, 3762, 3827, 4024, 4093, 4184, 4295, 4750, 5087, 5451, 5632, 5899, 6009, 6364, 6393, 6465]),
      ]),
    ]
  ),
])
samples_2016["/Tau/Run2016H-PromptReco-v2/MINIAOD"] = OD([
  ("type",                  "data"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "Tau_Run2016H_v2_promptReco"),
  ("nof_files",             8646),
  ("nof_events",            76425753),
  ("use_HIP_mitigation_bTag", False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                True),
  ("triggers",              [ "1e1tau", "1mu1tau", "2tau" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau/Tau/VHBB_HEPPY_V25tthtautau_Tau__Run2016H-PromptReco-v2/170215_145153"),
        ("selection", "*"),
        ("blacklist", [6, 10, 11, 17, 23, 25, 31, 34, 35, 36, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 49, 65, 68, 69, 71, 72, 73, 75, 77, 78, 79, 81, 82, 86, 88, 92, 95, 97, 99, 102, 103, 106, 108, 110, 116, 118, 119, 120, 121, 841, 2440, 3374, 5337, 5422, 5975, 6633, 6742, 7359]),
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
  ("nof_events",            79440120),
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
        ("blacklist", [971, 1487]),
      ]),
    ]
  ),
])
samples_2016["/Tau/Run2016H-PromptReco-v2/MINIAOD"] = OD([
  ("type",                  "data"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "Tau_Run2016H_v2_promptReco"),
  ("nof_files",             8646),
  ("nof_events",            76425753),
  ("use_HIP_mitigation_bTag", False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                True),
  ("triggers",              [ "1e1tau", "1mu1tau", "2tau" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau/Tau/VHBB_HEPPY_V25tthtautau_Tau__Run2016H-PromptReco-v2/170215_145153"),
        ("selection", "*"),
        ("blacklist", [6, 10, 11, 17, 23, 25, 31, 34, 35, 36, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 49, 65, 68, 69, 71, 72, 73, 75, 77, 78, 79, 81, 82, 86, 88, 92, 95, 97, 99, 102, 103, 106, 108, 110, 116, 118, 119, 120, 121, 841, 2440, 3374, 5337, 5422, 5975, 6633, 6742, 7359]),
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
samples_2016["/DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DYJetsToLL_M-10to50"),
  ("nof_files",             4086),
  ("nof_events",            29366360),
  ("use_it",                True),
  ("xsection",              18610.000000),
  ("genWeight",             True),
  ("triggers",              [ "1e", "1mu", "2e", "1e1mu", "2mu", "3e", "2e1mu", "1e2mu", "3mu", "1e1tau", "1mu1tau", "2tau" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau/MC/DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/VHBB_HEPPY_V25tthtautau_DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-amcatnloFXFX-Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6_ext1-v1/170207_123124"),
        ("selection", "*"),
        ("blacklist", [279, 2741, 3131]),
      ]),
    ]
  ),
])
samples_2016["/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISummer16MiniAODv2-PUMoriond17_HCALDebug_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DYJetsToLL_M-50"),
  ("nof_files",             2902),
  ("nof_events",            19223920),
  ("use_it",                True),
  ("xsection",              6025.200000),
  ("genWeight",             True),
  ("triggers",              [ "1e", "1mu", "2e", "1e1mu", "2mu", "3e", "2e1mu", "1e2mu", "3mu", "1e1tau", "1mu1tau", "2tau" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau/MC/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/VHBB_HEPPY_V25tthtautau_DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-Py8__RunIISummer16MAv2-PUMoriond17_HCALDebug_80r2as_2016_TrancheIV_v6-v1/170207_123354"),
        ("selection", "*"),
        ("blacklist", [251, 292, 384, 969, 1010, 1106, 1122, 1139, 1293, 1405, 1608, 1629, 1826, 1861, 1883, 1899, 1973, 2192, 2299, 2362, 2484, 2534, 2624, 2627, 2736, 2822, 2832]),
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
        ("blacklist", [3, 14, 32, 57, 109, 341, 538, 615, 778, 1177, 1432, 1642, 1643, 1648, 1653, 1872, 1885, 1926, 2210, 2220, 2374, 2435]),
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
        ("blacklist", [215]),
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
  ("xsection",              0.252900),
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
  ("xsection",              0.252900),
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
        ("blacklist", [38, 133, 186, 223, 260, 300, 308, 334, 355, 363, 373]),
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
## samples_2016["/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/RunIISpring16MiniAODv2-PUSpring16RAWAODSIM_reHLT_80X_mcRun2_asymptotic_v14_ext1-v1/MINIAODSIM"] = OD([
##   ("type",                  "mc"),
##   ("sample_category",       "signal"),
##   ("process_name_specific", "ttHJetToNonbb_M125"),
##   ("nof_files",             109),
##   ("nof_events",            1779218),
##   ("use_it",                True),
##   ("xsection",              0.215100),
##   ("genWeight",             True),
##   ("triggers",              [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
##   ("reHLT",                 True),
##   ("local_paths",
##     [
##       OD([
##         ("path",      "/hdfs/local/lucia/VHBBHeppyV24bis/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/VHBB_HEPPY_V24bis_ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_Py8_mWCutfix__spr16MAv2-puspr16_HLT_80r2as_v14_ext1-v1/160911_223711"),
##         ("selection", "*"),
##         ("blacklist", [10, 11, 14, 16, 20, 22, 23, 26, 29, 30, 31, 33, 34, 38, 39, 43, 44, 45, 51, 54, 57, 62, 63, 64, 66, 67, 68, 70, 71, 72, 73, 75, 76, 77, 79, 80, 81, 89, 98, 99]),
##       ]),
##     ]
##   ),
## ])
#     FOR TESTING ONLY !!!
#--------------------------------------------------------------------------------
