from collections import OrderedDict as OD

samples_2016 = OD()

# file generated with command:
# check_broken -p /hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau/MC/ /hdfs/cms/store/user/mario/VHBBHeppyV25tthtautau/MC/ /hdfs/cms/store/user/rdewanje/VHBBHeppyV25tthtautau/MC/ /hdfs/cms/store/user/veelken/VHBBHeppyV25tthtautau/MC/ /hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v2/MC --histo CountWeighted --output=. -P -z -v

# file generated with command:
# check_broken -p /hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau/MC_fastsim/ /hdfs/cms/store/user/mario/VHBBHeppyV25tthtautau/MC_fastsim/ /hdfs/cms/store/user/rdewanje/VHBBHeppyV25tthtautau/MC_fastsim/ /hdfs/cms/store/user/veelken/VHBBHeppyV25tthtautau/MC_fastsim/ --histo CountWeighted --output=. -P -z -v

#############
# Data
#############

# file generated with command:
# check_broken -p /hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau/ /hdfs/cms/store/user/mario/VHBBHeppyV25tthtautau/ /hdfs/cms/store/user/rdewanje/VHBBHeppyV25tthtautau/ /hdfs/cms/store/user/veelken/VHBBHeppyV25tthtautau/ /hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_HLT /hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v2 --histo CountWeighted --output=. -P -z -v -d

samples_2016["/DoubleMuon/Run2016H-PromptReco-v2/MINIAOD"] = OD([
  ("type",                  "data"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "DoubleMuon_Run2016H_v2_promptReco"),
  ("nof_files",             8180),
  ("nof_events",            0),
  ("use_HIP_mitigation_bTag", False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                True),
  ("triggers",              [ "2mu", "3mu" ]),
  ("reHLT",                 False),
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
  ("nof_files",             190),
  ("nof_events",            0),
  ("use_HIP_mitigation_bTag", False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                True),
  ("triggers",              [ "2mu", "3mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau/DoubleMuon/VHBB_HEPPY_V25tthtautau_DoubleMuon__Run2016H-PromptReco-v3/170215_143813"),
        ("selection", "*"),
        ("blacklist", [46, 52, 55, 72, 83, 97, 103, 110, 117, 118, 135, 137, 178, 188]),
      ]),
    ]
  ),
])
samples_2016["/Tau/Run2016B-23Sep2016-v3/MINIAOD"] = OD([
  ("type",                  "data"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "Tau_Run2016B_v3"),
  ("nof_files",             8521),
  ("nof_events",            0),
  ("use_HIP_mitigation_bTag", True),
  ("use_HIP_mitigation_mediumMuonId", True),
  ("use_it",                True),
  ("triggers",              [ "1e1tau", "1mu1tau", "2tau" ]),
  ("reHLT",                 False),
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
  ("nof_events",            0),
  ("use_HIP_mitigation_bTag", True),
  ("use_HIP_mitigation_mediumMuonId", True),
  ("use_it",                True),
  ("triggers",              [ "1e1tau", "1mu1tau", "2tau" ]),
  ("reHLT",                 False),
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
  ("nof_events",            0),
  ("use_HIP_mitigation_bTag", True),
  ("use_HIP_mitigation_mediumMuonId", True),
  ("use_it",                True),
  ("triggers",              [ "1e1tau", "1mu1tau", "2tau" ]),
  ("reHLT",                 False),
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
  ("nof_events",            0),
  ("use_HIP_mitigation_bTag", True),
  ("use_HIP_mitigation_mediumMuonId", True),
  ("use_it",                True),
  ("triggers",              [ "1e1tau", "1mu1tau", "2tau" ]),
  ("reHLT",                 False),
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
  ("nof_events",            0),
  ("use_HIP_mitigation_bTag", True),
  ("use_HIP_mitigation_mediumMuonId", True),
  ("use_it",                True),
  ("triggers",              [ "1e1tau", "1mu1tau", "2tau" ]),
  ("reHLT",                 False),
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
samples_2016["/MuonEG/Run2016D-23Sep2016-v1/MINIAOD"] = OD([
  ("type",                  "data"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "MuonEG_Run2016D_v1"),
  ("nof_files",             4296),
  ("nof_events",            0),
  ("use_HIP_mitigation_bTag", True),
  ("use_HIP_mitigation_mediumMuonId", True),
  ("use_it",                True),
  ("triggers",              [ "1e1mu", "2e1mu", "1e2mu" ]),
  ("reHLT",                 False),
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
  ("nof_events",            0),
  ("use_HIP_mitigation_bTag", False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                True),
  ("triggers",              [ "1e1mu", "2e1mu", "1e2mu" ]),
  ("reHLT",                 False),
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
  ("nof_events",            0),
  ("use_HIP_mitigation_bTag", False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                True),
  ("triggers",              [ "1e1mu", "2e1mu", "1e2mu" ]),
  ("reHLT",                 False),
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
samples_2016["/SingleElectron/Run2016H-PromptReco-v2/MINIAOD"] = OD([
  ("type",                  "data"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "SingleElectron_Run2016H_v2_promptReco"),
  ("nof_files",             7576),
  ("nof_events",            0),
  ("use_HIP_mitigation_bTag", False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                True),
  ("triggers",              [ "1e" ]),
  ("reHLT",                 False),
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
  ("nof_events",            0),
  ("use_HIP_mitigation_bTag", False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                True),
  ("triggers",              [ "1e" ]),
  ("reHLT",                 False),
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
samples_2016["/SingleMuon/Run2016F-23Sep2016-v1/MINIAOD"] = OD([
  ("type",                  "data"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "SingleMuon_Run2016F_v1"),
  ("nof_files",             2744),
  ("nof_events",            0),
  ("use_HIP_mitigation_bTag", True),
  ("use_HIP_mitigation_mediumMuonId", True),
  ("use_it",                True),
  ("triggers",              [ "1mu" ]),
  ("reHLT",                 False),
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
  ("nof_events",            0),
  ("use_HIP_mitigation_bTag", False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                True),
  ("triggers",              [ "1mu" ]),
  ("reHLT",                 False),
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
  ("nof_events",            0),
  ("use_HIP_mitigation_bTag", False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                True),
  ("triggers",              [ "1mu" ]),
  ("reHLT",                 False),
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
samples_2016["/Tau/Run2016H-PromptReco-v2/MINIAOD"] = OD([
  ("type",                  "data"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "Tau_Run2016H_v2_promptReco"),
  ("nof_files",             8646),
  ("nof_events",            0),
  ("use_HIP_mitigation_bTag", False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                True),
  ("triggers",              [ "1e1tau", "1mu1tau", "2tau" ]),
  ("reHLT",                 False),
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
  ("nof_events",            0),
  ("use_HIP_mitigation_bTag", False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                True),
  ("triggers",              [ "1e1tau", "1mu1tau", "2tau" ]),
  ("reHLT",                 False),
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
samples_2016["/DoubleEG/Run2016B-23Sep2016-v3/MINIAOD"] = OD([
  ("type",                  "data"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "DoubleEG_Run2016B_v3"),
  ("nof_files",             1995),
  ("nof_events",            0),
  ("use_HIP_mitigation_bTag", True),
  ("use_HIP_mitigation_mediumMuonId", True),
  ("use_it",                True),
  ("triggers",              [ "2e", "3e" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v2/DoubleEG/VHBB_HEPPY_V25tthtautau_v2_DoubleEG__Run2016B-23Sep2016-v3/170218_175533"),
        ("selection", "*"),
        ("blacklist", [854, 909, 1093, 1180, 1181, 1183, 1184, 1190, 1191, 1193, 1195, 1197, 1198, 1200, 1204, 1208, 1209, 1210, 1212, 1214, 1217, 1218, 1222, 1224, 1227, 1241, 1245, 1246, 1250, 1252, 1254, 1256, 1257, 1258, 1265, 1266, 1271, 1276, 1279, 1284, 1287, 1289, 1294, 1296, 1300, 1303, 1304, 1305, 1309, 1310, 1311, 1312, 1314, 1316, 1318, 1323, 1325, 1326, 1328, 1337, 1339, 1341, 1344, 1349, 1350, 1351, 1352, 1357, 1360, 1364, 1508, 1523, 1610, 1677, 1706, 1806, 1940]),
      ]),
    ]
  ),
])
samples_2016["/DoubleEG/Run2016C-23Sep2016-v1/MINIAOD"] = OD([
  ("type",                  "data"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "DoubleEG_Run2016C_v1"),
  ("nof_files",             626),
  ("nof_events",            0),
  ("use_HIP_mitigation_bTag", True),
  ("use_HIP_mitigation_mediumMuonId", True),
  ("use_it",                True),
  ("triggers",              [ "2e", "3e" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v2/DoubleEG/VHBB_HEPPY_V25tthtautau_v2_DoubleEG__Run2016C-23Sep2016-v1/170219_194332"),
        ("selection", "*"),
        ("blacklist", [5, 7, 16, 17, 21, 25, 27, 30, 35, 44, 46, 47, 48, 49, 50, 55, 56, 76, 86, 100, 104, 115, 119, 121, 122, 125, 126, 127, 128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 152, 154, 155, 156, 158, 159, 161, 164, 170, 175, 178, 179, 180, 186, 187, 193, 194, 195, 207, 210, 211, 215, 224, 233, 253, 278, 313, 315, 320, 323, 345, 359, 365, 368, 369, 371, 372, 373, 374, 375, 377, 379, 380, 392, 421, 436, 437, 479, 499, 513, 521, 550, 559, 560, 561, 562, 570, 606, 608, 609, 610, 611, 612, 614, 615, 623, 625]),
      ]),
    ]
  ),
])
samples_2016["/DoubleEG/Run2016D-23Sep2016-v1/MINIAOD"] = OD([
  ("type",                  "data"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "DoubleEG_Run2016D_v1"),
  ("nof_files",             1008),
  ("nof_events",            0),
  ("use_HIP_mitigation_bTag", True),
  ("use_HIP_mitigation_mediumMuonId", True),
  ("use_it",                True),
  ("triggers",              [ "2e", "3e" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v2/DoubleEG/VHBB_HEPPY_V25tthtautau_v2_DoubleEG__Run2016D-23Sep2016-v1/170218_171438"),
        ("selection", "*"),
        ("blacklist", [280, 670, 680, 688, 692, 728, 729, 733, 752, 756, 772, 775, 787, 794, 800, 893, 898, 944, 946, 950, 951, 971, 989]),
      ]),
    ]
  ),
])
samples_2016["/DoubleEG/Run2016E-23Sep2016-v1/MINIAOD"] = OD([
  ("type",                  "data"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "DoubleEG_Run2016E_v1"),
  ("nof_files",             906),
  ("nof_events",            0),
  ("use_HIP_mitigation_bTag", True),
  ("use_HIP_mitigation_mediumMuonId", True),
  ("use_it",                True),
  ("triggers",              [ "2e", "3e" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v2/DoubleEG/VHBB_HEPPY_V25tthtautau_v2_DoubleEG__Run2016E-23Sep2016-v1/170218_171718"),
        ("selection", "*"),
        ("blacklist", [21, 269, 347, 387, 415, 457, 461, 468, 471, 485, 486, 488, 492, 493, 499, 500, 502, 504, 508, 509, 513, 515, 519, 524, 525, 526, 530, 546, 549, 553, 663, 666, 670, 826, 836, 864, 866, 877, 884, 886, 905]),
      ]),
    ]
  ),
])
samples_2016["/DoubleEG/Run2016F-23Sep2016-v1/MINIAOD"] = OD([
  ("type",                  "data"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "DoubleEG_Run2016F_v1"),
  ("nof_files",             649),
  ("nof_events",            0),
  ("use_HIP_mitigation_bTag", True),
  ("use_HIP_mitigation_mediumMuonId", True),
  ("use_it",                True),
  ("triggers",              [ "2e", "3e" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v2/DoubleEG/VHBB_HEPPY_V25tthtautau_v2_DoubleEG__Run2016F-23Sep2016-v1/170218_180254"),
        ("selection", "*"),
        ("blacklist", [5, 338, 474, 475, 476, 477, 482, 485, 490, 494, 497, 508, 532, 555, 563, 575, 579, 584, 585, 592, 594, 596, 597, 599, 601, 604, 619, 628, 629, 636, 647]),
      ]),
    ]
  ),
])
samples_2016["/DoubleEG/Run2016G-23Sep2016-v1/MINIAOD"] = OD([
  ("type",                  "data"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "DoubleEG_Run2016G_v1"),
  ("nof_files",             1544),
  ("nof_events",            0),
  ("use_HIP_mitigation_bTag", False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                True),
  ("triggers",              [ "2e", "3e" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v2/DoubleEG/VHBB_HEPPY_V25tthtautau_v2_DoubleEG__Run2016G-23Sep2016-v1/170218_172915"),
        ("selection", "*"),
        ("blacklist", [242, 243, 285, 286, 760, 761, 762, 764, 767, 768, 770, 772, 775, 776, 793, 794, 800, 811, 812, 813, 817, 823, 830, 831, 838, 860, 880, 883, 884, 885, 886, 887, 895, 896, 912, 914, 923, 930, 933, 938, 942, 945, 951, 954, 959, 965, 970, 971, 1002, 1004, 1008, 1011, 1027, 1053, 1054, 1058, 1063, 1066, 1124, 1155, 1156, 1177, 1230, 1246, 1247, 1250, 1252, 1256, 1260, 1266, 1278, 1280, 1281, 1282, 1285, 1286, 1292, 1299, 1302, 1303, 1310, 1314, 1343, 1344, 1345, 1346, 1347, 1348, 1349, 1351, 1352, 1355, 1357, 1364, 1367, 1371, 1378, 1380, 1382, 1393, 1398, 1401, 1402, 1404, 1406, 1407, 1408, 1409, 1418, 1422, 1433, 1456, 1459, 1461, 1464, 1465, 1510]),
      ]),
    ]
  ),
])
samples_2016["/DoubleMuon/Run2016B-23Sep2016-v3/MINIAOD"] = OD([
  ("type",                  "data"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "DoubleMuon_Run2016B_v3"),
  ("nof_files",             1966),
  ("nof_events",            0),
  ("use_HIP_mitigation_bTag", True),
  ("use_HIP_mitigation_mediumMuonId", True),
  ("use_it",                True),
  ("triggers",              [ "2mu", "3mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v2/DoubleMuon/VHBB_HEPPY_V25tthtautau_v2_DoubleMuon__Run2016B-23Sep2016-v3/170218_175649"),
        ("selection", "*"),
        ("blacklist", [1594, 1693, 1715]),
      ]),
    ]
  ),
])
samples_2016["/DoubleMuon/Run2016C-23Sep2016-v1/MINIAOD"] = OD([
  ("type",                  "data"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "DoubleMuon_Run2016C_v1"),
  ("nof_files",             621),
  ("nof_events",            0),
  ("use_HIP_mitigation_bTag", True),
  ("use_HIP_mitigation_mediumMuonId", True),
  ("use_it",                True),
  ("triggers",              [ "2mu", "3mu" ]),
  ("reHLT",                 False),
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
  ("nof_events",            0),
  ("use_HIP_mitigation_bTag", True),
  ("use_HIP_mitigation_mediumMuonId", True),
  ("use_it",                True),
  ("triggers",              [ "2mu", "3mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v2/DoubleMuon/VHBB_HEPPY_V25tthtautau_v2_DoubleMuon__Run2016D-23Sep2016-v1/170218_171554"),
        ("selection", "*"),
        ("blacklist", [629, 657]),
      ]),
    ]
  ),
])
samples_2016["/DoubleMuon/Run2016E-23Sep2016-v1/MINIAOD"] = OD([
  ("type",                  "data"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "DoubleMuon_Run2016E_v1"),
  ("nof_files",             896),
  ("nof_events",            0),
  ("use_HIP_mitigation_bTag", True),
  ("use_HIP_mitigation_mediumMuonId", True),
  ("use_it",                True),
  ("triggers",              [ "2mu", "3mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v2/DoubleMuon/VHBB_HEPPY_V25tthtautau_v2_DoubleMuon__Run2016E-23Sep2016-v1/170218_180126"),
        ("selection", "*"),
        ("blacklist", [374, 446, 454, 510, 556, 608, 661, 675, 698, 790, 793, 809, 865, 878, 880]),
      ]),
    ]
  ),
])
samples_2016["/DoubleMuon/Run2016F-23Sep2016-v1/MINIAOD"] = OD([
  ("type",                  "data"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "DoubleMuon_Run2016F_v1"),
  ("nof_files",             641),
  ("nof_events",            0),
  ("use_HIP_mitigation_bTag", True),
  ("use_HIP_mitigation_mediumMuonId", True),
  ("use_it",                True),
  ("triggers",              [ "2mu", "3mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v2/DoubleMuon/VHBB_HEPPY_V25tthtautau_v2_DoubleMuon__Run2016F-23Sep2016-v1/170217_152817"),
        ("selection", "*"),
        ("blacklist", [329]),
      ]),
    ]
  ),
])
samples_2016["/DoubleMuon/Run2016G-23Sep2016-v1/MINIAOD"] = OD([
  ("type",                  "data"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "DoubleMuon_Run2016G_v1"),
  ("nof_files",             1527),
  ("nof_events",            0),
  ("use_HIP_mitigation_bTag", False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                True),
  ("triggers",              [ "2mu", "3mu" ]),
  ("reHLT",                 False),
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
samples_2016["/MuonEG/Run2016B-23Sep2016-v3/MINIAOD"] = OD([
  ("type",                  "data"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "MuonEG_Run2016B_v3"),
  ("nof_files",             1966),
  ("nof_events",            0),
  ("use_HIP_mitigation_bTag", True),
  ("use_HIP_mitigation_mediumMuonId", True),
  ("use_it",                True),
  ("triggers",              [ "1e1mu", "2e1mu", "1e2mu" ]),
  ("reHLT",                 False),
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
  ("nof_events",            0),
  ("use_HIP_mitigation_bTag", True),
  ("use_HIP_mitigation_mediumMuonId", True),
  ("use_it",                True),
  ("triggers",              [ "1e1mu", "2e1mu", "1e2mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v2/MuonEG/VHBB_HEPPY_V25tthtautau_v2_MuonEG__Run2016C-23Sep2016-v1/170218_170759"),
        ("selection", "*"),
        ("blacklist", [40, 59]),
      ]),
    ]
  ),
])
samples_2016["/MuonEG/Run2016E-23Sep2016-v1/MINIAOD"] = OD([
  ("type",                  "data"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "MuonEG_Run2016E_v1"),
  ("nof_files",             896),
  ("nof_events",            0),
  ("use_HIP_mitigation_bTag", True),
  ("use_HIP_mitigation_mediumMuonId", True),
  ("use_it",                True),
  ("triggers",              [ "1e1mu", "2e1mu", "1e2mu" ]),
  ("reHLT",                 False),
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
  ("nof_events",            0),
  ("use_HIP_mitigation_bTag", True),
  ("use_HIP_mitigation_mediumMuonId", True),
  ("use_it",                True),
  ("triggers",              [ "1e1mu", "2e1mu", "1e2mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v2/MuonEG/VHBB_HEPPY_V25tthtautau_v2_MuonEG__Run2016F-23Sep2016-v1/170217_153318"),
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
  ("nof_events",            0),
  ("use_HIP_mitigation_bTag", False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                True),
  ("triggers",              [ "1e1mu", "2e1mu", "1e2mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v2/MuonEG/VHBB_HEPPY_V25tthtautau_v2_MuonEG__Run2016G-23Sep2016-v1/170218_172759"),
        ("selection", "*"),
        ("blacklist", [864, 1356]),
      ]),
    ]
  ),
])
samples_2016["/SingleElectron/Run2016B-23Sep2016-v3/MINIAOD"] = OD([
  ("type",                  "data"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "SingleElectron_Run2016B_v3"),
  ("nof_files",             1994),
  ("nof_events",            0),
  ("use_HIP_mitigation_bTag", True),
  ("use_HIP_mitigation_mediumMuonId", True),
  ("use_it",                True),
  ("triggers",              [ "1e" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v2/SingleElectron/VHBB_HEPPY_V25tthtautau_v2_SingleElectron__Run2016B-23Sep2016-v3/170218_175416"),
        ("selection", "*"),
        ("blacklist", [67, 85, 90, 110, 130, 140, 152, 156, 173, 177, 186, 189, 194, 195, 198, 206, 211, 244, 253, 297, 306, 310, 325, 351, 473, 487, 567, 618, 688, 706, 718, 747, 751, 763, 782, 785, 803, 816, 818, 825, 834, 835, 837, 839, 845, 851, 863, 875, 877, 900, 901, 903, 912, 982, 997, 1005, 1010, 1044, 1049, 1084, 1085, 1086, 1088, 1090, 1091, 1093, 1099, 1100, 1105, 1106, 1107, 1113, 1115, 1124, 1126, 1135, 1136, 1140, 1161, 1163, 1166, 1179, 1181, 1182, 1195, 1196, 1198, 1202, 1203, 1206, 1216, 1220, 1221, 1225, 1230, 1231, 1232, 1233, 1240, 1255, 1260, 1261, 1262, 1263, 1264, 1265, 1267, 1268, 1269, 1271, 1272, 1273, 1275, 1276, 1278, 1280, 1281, 1284, 1287, 1295, 1297, 1301, 1302, 1303, 1306, 1309, 1310, 1311, 1313, 1314, 1315, 1318, 1320, 1327, 1328, 1330, 1332, 1333, 1335, 1336, 1337, 1338, 1340, 1343, 1344, 1345, 1346, 1349, 1351, 1353, 1354, 1355, 1358, 1362, 1364, 1366, 1367, 1368, 1369, 1371, 1373, 1374, 1375, 1376, 1379, 1380, 1381, 1382, 1384, 1396, 1399, 1409, 1410, 1420, 1430, 1433, 1436, 1437, 1439, 1441, 1447, 1448, 1449, 1450, 1456, 1457, 1458, 1460, 1470, 1471, 1472, 1473, 1475, 1477, 1478, 1481, 1483, 1491, 1493, 1496, 1498, 1500, 1508, 1509, 1510, 1511, 1512, 1514, 1516, 1517, 1518, 1520, 1525, 1526, 1527, 1528, 1529, 1530, 1532, 1533, 1535, 1536, 1537, 1538, 1539, 1540, 1541, 1542, 1543, 1545, 1546, 1547, 1548, 1549, 1550, 1554, 1555, 1556, 1557, 1558, 1561, 1563, 1564, 1565, 1566, 1567, 1568, 1569, 1570, 1572, 1574, 1577, 1578, 1579, 1580, 1581, 1583, 1584, 1585, 1586, 1587, 1589, 1590, 1591, 1593, 1596, 1597, 1598, 1601, 1603, 1604, 1606, 1618, 1619, 1623, 1624, 1627, 1628, 1630, 1637, 1640, 1641, 1644, 1645, 1646, 1650, 1653, 1655, 1656, 1661, 1665, 1666, 1669, 1673, 1675, 1677, 1678, 1679, 1684, 1687, 1695, 1698, 1699, 1702, 1703, 1705, 1706, 1707, 1708, 1710, 1711, 1712, 1715, 1716, 1722, 1723, 1724, 1725, 1727, 1729, 1730, 1731, 1743, 1745, 1747, 1750, 1752, 1753, 1754, 1756, 1757, 1758, 1759, 1760, 1761, 1762, 1763, 1764, 1765, 1772, 1773, 1774, 1775, 1776, 1779, 1780, 1781, 1782, 1783, 1784, 1785, 1786, 1787, 1790, 1791, 1792, 1793, 1794, 1795, 1796, 1797, 1798, 1800, 1801, 1802, 1803, 1807, 1812, 1813, 1814, 1815, 1816, 1818, 1820, 1822, 1823, 1824, 1825, 1826, 1827, 1828, 1829, 1830, 1831, 1832, 1833, 1834, 1835, 1836, 1837, 1841, 1842, 1843, 1846, 1847, 1848, 1849, 1852, 1853, 1854, 1857, 1859, 1861, 1863, 1865, 1868, 1869, 1870, 1872, 1873, 1874, 1875, 1876, 1877, 1878, 1879, 1880, 1881, 1882, 1883, 1884, 1885, 1886, 1889, 1890, 1895, 1906, 1909, 1955, 1967, 1977, 1982, 1983, 1984, 1985, 1993]),
      ]),
    ]
  ),
])
samples_2016["/SingleElectron/Run2016C-23Sep2016-v1/MINIAOD"] = OD([
  ("type",                  "data"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "SingleElectron_Run2016C_v1"),
  ("nof_files",             627),
  ("nof_events",            0),
  ("use_HIP_mitigation_bTag", True),
  ("use_HIP_mitigation_mediumMuonId", True),
  ("use_it",                True),
  ("triggers",              [ "1e" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v2/SingleElectron/VHBB_HEPPY_V25tthtautau_v2_SingleElectron__Run2016C-23Sep2016-v1/170218_170914"),
        ("selection", "*"),
        ("blacklist", [8, 9, 11, 12, 17, 20, 22, 33, 37, 42, 43, 44, 47, 48, 49, 51, 52, 53, 54, 55, 58, 59, 60, 61, 62, 63, 65, 66, 67, 69, 73, 74, 75, 76, 77, 78, 79, 81, 83, 84, 86, 87, 90, 92, 93, 94, 95, 96, 98, 105, 106, 108, 110, 112, 114, 118, 124, 125, 126, 127, 128, 129, 130, 131, 132, 133, 135, 136, 137, 138, 140, 141, 143, 145, 149, 154, 155, 161, 162, 163, 165, 166, 169, 171, 172, 173, 174, 175, 176, 177, 178, 179, 183, 185, 188, 189, 190, 192, 193, 196, 198, 199, 200, 201, 202, 204, 205, 207, 208, 209, 210, 213, 215, 218, 220, 221, 224, 225, 227, 229, 231, 234, 236, 237, 239, 240, 243, 244, 247, 248, 249, 250, 253, 255, 262, 263, 264, 265, 277, 278, 282, 283, 288, 298, 299, 300, 302, 303, 304, 305, 308, 309, 312, 313, 314, 316, 318, 320, 321, 322, 323, 324, 329, 330, 331, 334, 336, 339, 340, 345, 346, 348, 349, 351, 353, 382, 385, 386, 387, 388, 390, 391, 394, 396, 397, 398, 400, 402, 403, 404, 405, 406, 407, 409, 410, 411, 412, 416, 417, 418, 419, 420, 421, 422, 423, 424, 425, 427, 428, 429, 433, 434, 435, 436, 437, 439, 440, 441, 443, 446, 448, 453, 454, 459, 463, 464, 465, 477, 479, 483, 487, 488, 489, 492, 498, 519, 523, 527, 528, 531, 532, 547, 560, 561, 563, 564, 565, 568, 569, 570, 571, 572, 583, 585, 586, 599, 601, 602, 603, 607, 608, 609, 611, 615]),
      ]),
    ]
  ),
])
samples_2016["/SingleElectron/Run2016D-23Sep2016-v1/MINIAOD"] = OD([
  ("type",                  "data"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "SingleElectron_Run2016D_v1"),
  ("nof_files",             1008),
  ("nof_events",            0),
  ("use_HIP_mitigation_bTag", True),
  ("use_HIP_mitigation_mediumMuonId", True),
  ("use_it",                True),
  ("triggers",              [ "1e" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v2/SingleElectron/VHBB_HEPPY_V25tthtautau_v2_SingleElectron__Run2016D-23Sep2016-v1/170218_120808"),
        ("selection", "*"),
        ("blacklist", [5, 6, 11, 14, 15, 16, 17, 24, 26, 30, 36, 39, 40, 46, 47, 49, 51, 54, 56, 58, 66, 67, 68, 69, 71, 74, 76, 79, 85, 86, 90, 92, 93, 97, 98, 99, 100, 102, 105, 106, 107, 108, 111, 114, 117, 119, 120, 122, 131, 143, 144, 146, 163, 169, 174, 176, 177, 183, 185, 186, 192, 209, 236, 241, 250, 252, 268, 273, 279, 280, 281, 283, 288, 292, 294, 295, 301, 302, 306, 311, 313, 317, 318, 319, 320, 323, 332, 333, 334, 335, 337, 343, 351, 356, 357, 360, 371, 374, 375, 391, 400, 408, 438, 455, 460, 461, 463, 469, 479, 482, 483, 488, 490, 491, 504, 517, 530, 566, 574, 575, 579, 580, 583, 587, 588, 591, 594, 595, 596, 599, 600, 603, 604, 606, 607, 608, 609, 624, 627, 628, 630, 635, 636, 638, 641, 643, 644, 652, 667, 668, 670, 671, 674, 677, 684, 692, 705, 739, 742, 750, 752, 754, 755, 756, 766, 773, 774, 779, 780, 781, 782, 786, 788, 789, 790, 791, 796, 798, 799, 802, 804, 805, 807, 809, 810, 812, 815, 821, 822, 823, 848, 867, 878, 879, 881, 883, 884, 888, 889, 896, 898, 904, 905, 909, 915, 929, 933, 947, 948, 949, 950, 957, 958, 959, 968, 975, 982, 987, 988, 989, 992, 993, 994, 1004, 1005, 1006]),
      ]),
    ]
  ),
])
samples_2016["/SingleElectron/Run2016E-23Sep2016-v1/MINIAOD"] = OD([
  ("type",                  "data"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "SingleElectron_Run2016E_v1"),
  ("nof_files",             906),
  ("nof_events",            0),
  ("use_HIP_mitigation_bTag", True),
  ("use_HIP_mitigation_mediumMuonId", True),
  ("use_it",                True),
  ("triggers",              [ "1e" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v2/SingleElectron/VHBB_HEPPY_V25tthtautau_v2_SingleElectron__Run2016E-23Sep2016-v1/170218_120651"),
        ("selection", "*"),
        ("blacklist", [5, 6, 10, 11, 12, 13, 14, 15, 20, 21, 28, 30, 34, 35, 37, 43, 48, 53, 61, 62, 63, 69, 70, 71, 72, 80, 85, 87, 91, 92, 113, 127, 135, 156, 170, 171, 172, 174, 197, 198, 202, 203, 209, 210, 215, 222, 226, 233, 237, 242, 244, 246, 262, 270, 277, 296, 300, 303, 304, 308, 311, 319, 325, 346, 385, 394, 416, 424, 425, 435, 438, 440, 442, 445, 450, 451, 463, 475, 480, 483, 487, 493, 494, 495, 499, 509, 516, 522, 527, 528, 533, 535, 547, 548, 560, 591, 628, 633, 638, 639, 640, 641, 642, 644, 645, 647, 648, 649, 650, 651, 653, 656, 659, 660, 661, 663, 665, 669, 670, 671, 672, 674, 675, 676, 677, 678, 679, 680, 681, 682, 683, 684, 685, 687, 699, 701, 703, 705, 707, 712, 720, 725, 751, 764, 765, 766, 767, 771, 774, 775, 777, 779, 780, 781, 834, 836, 837, 838, 839, 840, 841, 842, 843, 845, 847, 849, 851, 865, 869, 870, 872, 873, 874, 876, 877, 878, 879, 880, 882, 883, 884, 885, 886, 887, 888, 891, 892, 893, 896, 898, 900, 903, 904, 905]),
      ]),
    ]
  ),
])
samples_2016["/SingleElectron/Run2016F-23Sep2016-v1/MINIAOD"] = OD([
  ("type",                  "data"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "SingleElectron_Run2016F_v1"),
  ("nof_files",             649),
  ("nof_events",            0),
  ("use_HIP_mitigation_bTag", True),
  ("use_HIP_mitigation_mediumMuonId", True),
  ("use_it",                True),
  ("triggers",              [ "1e" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v2/SingleElectron/VHBB_HEPPY_V25tthtautau_v2_SingleElectron__Run2016F-23Sep2016-v1/170218_172629"),
        ("selection", "*"),
        ("blacklist", [73, 77, 91, 95, 100, 101, 139, 179, 193, 195, 227, 228, 252, 277, 289, 295, 325, 327, 328, 329, 330, 334, 335, 337, 340, 346, 347, 348, 349, 350, 351, 384, 386, 394, 404, 419, 427, 432, 434, 445, 509, 513, 521, 526, 534, 537, 561, 564, 568, 573, 586, 587, 589, 590, 594, 600, 604, 605, 612, 613, 619, 620, 625, 628, 631]),
      ]),
    ]
  ),
])
samples_2016["/SingleElectron/Run2016G-23Sep2016-v1/MINIAOD"] = OD([
  ("type",                  "data"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "SingleElectron_Run2016G_v1"),
  ("nof_files",             1544),
  ("nof_events",            0),
  ("use_HIP_mitigation_bTag", False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                True),
  ("triggers",              [ "1e" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v2/SingleElectron/VHBB_HEPPY_V25tthtautau_v2_SingleElectron__Run2016G-23Sep2016-v1/170217_150830"),
        ("selection", "*"),
        ("blacklist", [105, 351, 451, 480, 1072, 1120, 1312, 1322, 1404, 1434]),
      ]),
    ]
  ),
])
samples_2016["/SingleMuon/Run2016B-23Sep2016-v3/MINIAOD"] = OD([
  ("type",                  "data"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "SingleMuon_Run2016B_v3"),
  ("nof_files",             1966),
  ("nof_events",            0),
  ("use_HIP_mitigation_bTag", True),
  ("use_HIP_mitigation_mediumMuonId", True),
  ("use_it",                True),
  ("triggers",              [ "1mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v2/SingleMuon/VHBB_HEPPY_V25tthtautau_v2_SingleMuon__Run2016B-23Sep2016-v3/170218_175805"),
        ("selection", "*"),
        ("blacklist", [190, 350, 421, 486, 555, 779, 886, 904, 960, 962, 996, 1079, 1092, 1157, 1169, 1204, 1249, 1272, 1283, 1290, 1293, 1327, 1345, 1362, 1396, 1402, 1407, 1408, 1438, 1441, 1442, 1448, 1479, 1483, 1488, 1502, 1534, 1538, 1540, 1541, 1547, 1549, 1556, 1570, 1574, 1575, 1588, 1595, 1597, 1599, 1600, 1602, 1608, 1610, 1612, 1617, 1627, 1634, 1639, 1705, 1716, 1719, 1722, 1730, 1732, 1742, 1743, 1744, 1751, 1758, 1764, 1766, 1779, 1790, 1801, 1811, 1821, 1822, 1845, 1852, 1853, 1856, 1878, 1888, 1890, 1898, 1902, 1906, 1945]),
      ]),
    ]
  ),
])
samples_2016["/SingleMuon/Run2016C-23Sep2016-v1/MINIAOD"] = OD([
  ("type",                  "data"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "SingleMuon_Run2016C_v1"),
  ("nof_files",             621),
  ("nof_events",            0),
  ("use_HIP_mitigation_bTag", True),
  ("use_HIP_mitigation_mediumMuonId", True),
  ("use_it",                True),
  ("triggers",              [ "1mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v2/SingleMuon/VHBB_HEPPY_V25tthtautau_v2_SingleMuon__Run2016C-23Sep2016-v1/170218_171159"),
        ("selection", "*"),
        ("blacklist", [23, 34, 35, 40, 43, 58, 90, 102, 154, 165, 167, 172, 180, 184, 187, 188, 189, 194, 206, 208, 211, 215, 217, 219, 224, 226, 231, 232, 235, 254, 260, 261, 263, 289, 318, 321, 350, 362, 363, 364, 375, 378, 383, 384, 386, 392, 393, 400, 403, 410, 411, 412, 414, 426, 428, 436, 438, 440, 445, 450, 451, 453, 454, 464, 471, 497, 507, 510, 512, 514, 515, 518, 520, 526, 529, 530, 539, 548, 555, 556, 562, 563, 564, 565, 572, 581, 586, 606, 610, 611, 612, 613, 617]),
      ]),
    ]
  ),
])
samples_2016["/SingleMuon/Run2016D-23Sep2016-v1/MINIAOD"] = OD([
  ("type",                  "data"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "SingleMuon_Run2016D_v1"),
  ("nof_files",             1003),
  ("nof_events",            0),
  ("use_HIP_mitigation_bTag", True),
  ("use_HIP_mitigation_mediumMuonId", True),
  ("use_it",                True),
  ("triggers",              [ "1mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v2/SingleMuon/VHBB_HEPPY_V25tthtautau_v2_SingleMuon__Run2016D-23Sep2016-v1/170218_171316"),
        ("selection", "*"),
        ("blacklist", [17, 22, 23, 28, 83, 92, 370, 399, 566, 574, 578, 728, 736, 827, 854, 901, 908, 945, 946, 952, 971]),
      ]),
    ]
  ),
])
samples_2016["/SingleMuon/Run2016E-23Sep2016-v1/MINIAOD"] = OD([
  ("type",                  "data"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "SingleMuon_Run2016E_v1"),
  ("nof_files",             896),
  ("nof_events",            0),
  ("use_HIP_mitigation_bTag", True),
  ("use_HIP_mitigation_mediumMuonId", True),
  ("use_it",                True),
  ("triggers",              [ "1mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v2/SingleMuon/VHBB_HEPPY_V25tthtautau_v2_SingleMuon__Run2016E-23Sep2016-v1/170218_172212"),
        ("selection", "*"),
        ("blacklist", [24, 28, 74, 111, 142, 143, 146, 150, 152, 156, 162, 167, 171, 186, 192, 195, 198, 199, 202, 205, 208, 209, 213, 214, 215, 217, 218, 219, 221, 222, 223, 225, 229, 232, 234, 238, 242, 250, 254, 262, 268, 281, 288, 291, 294, 297, 302, 306, 311, 312, 318, 322, 331, 337, 339, 350, 351, 352, 353, 354, 356, 362, 366, 368, 374, 375, 390, 448, 467, 476, 487, 497, 525, 528, 533, 535, 536, 539, 544, 545, 546, 551, 557, 560, 561, 565, 570, 577, 578, 579, 580, 583, 593, 596, 601, 602, 605, 607, 608, 610, 612, 625, 628, 629, 632, 642, 653, 654, 657, 663, 664, 665, 667, 669, 673, 674, 675, 679, 680, 681, 684, 689, 692, 694, 698, 700, 705, 706, 719, 721, 728, 743, 748, 749, 769, 772, 773, 775, 776, 796, 797, 832, 833, 840, 847, 879, 880, 882, 893]),
      ]),
    ]
  ),
])
samples_2016["/SingleMuon/Run2016G-23Sep2016-v1/MINIAOD"] = OD([
  ("type",                  "data"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "SingleMuon_Run2016G_v1"),
  ("nof_files",             1527),
  ("nof_events",            0),
  ("use_HIP_mitigation_bTag", False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                True),
  ("triggers",              [ "1mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v2/SingleMuon/VHBB_HEPPY_V25tthtautau_v2_SingleMuon__Run2016G-23Sep2016-v1/170217_151611"),
        ("selection", "*"),
        ("blacklist", [662, 896]),
      ]),
    ]
  ),
])
samples_2016["/Tau/Run2016G-23Sep2016-v1/MINIAOD"] = OD([
  ("type",                  "data"),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "Tau_Run2016G_v1"),
  ("nof_files",             1552),
  ("nof_events",            0),
  ("use_HIP_mitigation_bTag", False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                True),
  ("triggers",              [ "1e1tau", "1mu1tau", "2tau" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v2/Tau/VHBB_HEPPY_V25tthtautau_v2_Tau__Run2016G-23Sep2016-v1/170218_173036"),
        ("selection", "*"),
        ("blacklist", [5, 39, 40, 45, 50, 51, 52, 86, 92, 106, 128, 137, 144, 146, 162, 164, 172, 173, 177, 185, 187, 189, 197, 204, 207, 215, 228, 237, 239, 241, 242, 244, 262, 278, 348, 350, 369, 372, 375, 441, 450, 469, 470, 481, 486, 488, 493, 499, 506, 511, 513, 514, 517, 526, 535, 537, 541, 549, 551, 557, 575, 584, 603, 604, 616, 618, 620, 666, 668, 674, 676, 693, 697, 701, 709, 710, 712, 717, 721, 723, 724, 728, 731, 732, 735, 740, 749, 752, 754, 757, 758, 760, 763, 766, 778, 780, 784, 785, 786, 793, 796, 798, 799, 810, 817, 846, 856, 864, 865, 866, 877, 880, 884, 887, 888, 894, 896, 897, 899, 922, 927, 928, 931, 935, 941, 942, 943, 947, 952, 953, 955, 956, 957, 959, 960, 961, 964, 965, 967, 971, 972, 975, 976, 977, 979, 981, 982, 989, 992, 1000, 1002, 1005, 1017, 1021, 1022, 1025, 1029, 1033, 1034, 1044, 1047, 1054, 1055, 1061, 1062, 1063, 1067, 1070, 1074, 1087, 1089, 1091, 1095, 1101, 1108, 1109, 1110, 1113, 1115, 1118, 1119, 1126, 1129, 1144, 1152, 1153, 1155, 1164, 1165, 1173, 1176, 1181, 1183, 1184, 1186, 1194, 1200, 1201, 1203, 1204, 1205, 1214, 1219, 1222, 1233, 1256, 1262, 1263, 1267, 1276, 1279, 1280, 1286, 1287, 1292, 1293, 1295, 1303, 1307, 1315, 1325, 1326, 1328, 1330, 1350, 1361, 1362, 1363, 1364, 1368, 1369, 1374, 1388, 1390, 1391, 1396, 1398, 1402, 1405, 1406, 1409, 1411, 1414, 1415, 1418, 1419, 1422, 1431, 1432, 1434, 1437, 1454, 1458, 1480, 1484, 1487, 1490, 1492, 1499, 1504, 1507, 1538]),
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
  ("xsection",              1.640000),
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
