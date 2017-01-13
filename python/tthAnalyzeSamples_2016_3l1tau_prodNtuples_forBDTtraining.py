from collections import OrderedDict as OD

samples_2016 = OD()

# file generated with command:
# check_broken -p /hdfs/local/karl/ttHNtupleProduction/2016/2017Jan12_forBDTtraining/ntuples/3l_1tau -o -z -i -P -v

samples_2016["/TTW/spring16DR80v6aMiniAODv1/FASTSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "TTW"),
  ("process_name_specific", "TTW_Fastsim"),
  ("nof_files",             162),
  ("nof_events",            7218795),
  ("use_it",                True),
  ("xsection",              0.204300),
  ("genWeight",             False),
  ("triggers",              [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2016/2017Jan12_forBDTtraining/ntuples/3l_1tau/TTW_FastSim"),
        ("selection", "*"),
        ("blacklist", [20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 150, 151, 153, 154, 156, 157, 158, 159]),
      ]),
    ]
  ),
])
samples_2016[""] = OD([
  ("type",                  "mc"),
  ("sample_category",       ""),
  ("process_name_specific", ""),
  ("nof_files",             24),
  ("nof_events",            832218),
  ("use_it",                True),
  ("xsection",              0.000000),
  ("genWeight",             False),
  ("triggers",              [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2016/2017Jan12_forBDTtraining/ntuples/3l_1tau/TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-pythia8/VHBB_HEPPY_V24bis_TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-Py8__spr16MAv2-premix_withHLT_80r2as_v14_ext1-v1/160911_224606"),
        ("selection", "*"),
        ("blacklist", [16]),
      ]),
    ]
  ),
])
samples_2016["/TT_TuneCUETP8M1_13TeV-powheg-pythia8/RunIISpring16MiniAODv1-PUSpring16_80X_mcRun2_asymptotic_2016_v3_ext4-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "TT"),
  ("process_name_specific", "TT_ext4"),
  ("nof_files",             9602),
  ("nof_events",            249751606),
  ("use_it",                True),
  ("xsection",              831.760000),
  ("genWeight",             False),
  ("triggers",              [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2016/2017Jan12_forBDTtraining/ntuples/3l_1tau/TT_TuneCUETP8M1_13TeV-powheg-pythia8/VHBB_HEPPY_D24_TT_TuneCUETP8M1_13TeV-powheg-Py8__spr16MiniAODv1-puspr16_80r2as_2016_v3_ext4-v1/161107_100027"),
        ("selection", "*"),
        ("blacklist", [212, 213, 218, 219, 230, 231, 232, 233, 234, 235, 236, 237, 299, 314, 348, 380, 383, 523, 561, 578, 579, 612, 682, 683, 684, 685, 686, 687, 689, 740, 741, 742, 743, 746, 748, 749, 760, 761, 762, 763, 766, 767, 970, 971, 972, 973, 974, 975, 976, 977, 978, 979, 1017, 1018, 1019, 1030, 1031, 1032, 1033, 1034, 1035, 1036, 1037, 1038, 1039, 1191, 1194, 1197, 1252, 1253, 1254, 1256, 1257, 1378, 1379, 1434, 1435, 1437, 1438, 1439, 1545, 1548, 1549, 1623, 1630, 1631, 1632, 1633, 1636, 1637, 1770, 1772, 1773, 1774, 1775, 1776, 1777, 1778, 1779, 1802, 2152, 2300, 2302, 2303, 2304, 2305, 2306, 2307, 2360, 2361, 2362, 2363, 2364, 2365, 2366, 2367, 2368, 2369, 2457, 2550, 2551, 2552, 2553, 2554, 2555, 2556, 2557, 2558, 2559, 2891, 2892, 2893, 2894, 2895, 2896, 2897, 2898, 2899, 2922, 2970, 2971, 2972, 2973, 2974, 2975, 2976, 2977, 2978, 2979, 3089, 3090, 3091, 3092, 3093, 3094, 3095, 3096, 3097, 3098, 3099, 3156, 3245, 3249, 3314, 3315, 3360, 3361, 3362, 3363, 3365, 3367, 3368, 3400, 3429, 3444, 3464, 3492, 3496, 3540, 3541, 3542, 3543, 3544, 3546, 3547, 3548, 3549, 4018, 4019, 4092, 4093, 4094, 4095, 4097, 4098, 4099, 4125, 4142, 4220, 4221, 4222, 4223, 4224, 4225, 4226, 4227, 4228, 4229, 4249, 4356, 4540, 4546, 4547, 4650, 4651, 4652, 4653, 4654, 4655, 4656, 4657, 4658, 4659, 4790, 4792, 4794, 4796, 4797, 4798, 4799, 4821, 4822, 4823, 4824, 4825, 4826, 4827, 4828, 4829, 4912, 4918, 5010, 5012, 5013, 5016, 5017, 5069, 5081, 5085, 5117, 5200, 5201, 5203, 5205, 5206, 5207, 5209, 5239, 5260, 5261, 5262, 5263, 5264, 5265, 5266, 5267, 5268, 5269, 5466, 5650, 5651, 5652, 5653, 5654, 5655, 5656, 5657, 5658, 5659, 5682, 5688, 5790, 5791, 5792, 5793, 5794, 5796, 5797, 5798, 5799, 5840, 5843, 5844, 5845, 5846, 5847, 5848, 5849, 5860, 5861, 5862, 5863, 5864, 5865, 5866, 5867, 5868, 5869, 6049, 6090, 6098, 6099, 6100, 6101, 6102, 6103, 6104, 6105, 6110, 6111, 6112, 6114, 6115, 6116, 6117, 6118, 6119, 6157, 6195, 6196, 6233, 6242, 6243, 6244, 6245, 6248, 6289, 6300, 6301, 6302, 6303, 6304, 6305, 6306, 6307, 6308, 6309, 6372, 6374, 6375, 6376, 6377, 6378, 6379, 6408, 6409, 6412, 6413, 6414, 6415, 6440, 6443, 6560, 6606, 6688, 6689, 6850, 6851, 6853, 6854, 6855, 6856, 6867, 6879, 6881, 6884, 6890, 6893, 7108, 7270, 7271, 7276, 7277, 7300, 7301, 7302, 7303, 7304, 7305, 7306, 7307, 7308, 7309, 7312, 7314, 7315, 7317, 7320, 7321, 7322, 7323, 7324, 7325, 7326, 7327, 7328, 7329, 7444, 7447, 7456, 7457, 7713, 7771, 7778, 7779, 7781, 7786, 7801, 7807, 7820, 7826, 7827, 7911, 7917, 7938, 7939, 8020, 8023, 8028, 8029, 8040, 8041, 8042, 8044, 8046, 8047, 8048, 8049, 8052, 8053, 8063, 8111, 8160, 8161, 8162, 8163, 8164, 8165, 8167, 8169, 8211, 8322, 8323, 8340, 8341, 8342, 8343, 8347, 8349, 8361, 8365, 8366, 8402, 8403, 8422, 8423, 8441, 8448, 8495, 8496, 8502, 8503, 8504, 8505, 8507, 8522, 8523, 8524, 8534, 8568, 8569, 8581, 8582, 8584, 8586, 8587, 8588, 8601, 8605, 8607, 8790, 8793, 8794, 8795, 8796, 8798, 8799, 8810, 8818, 8819, 8831, 8833, 8834, 8835, 8836, 8837, 8838, 8839, 8840, 8844, 8851, 8853, 8918, 8919, 8971, 8972, 8973, 8975, 8976, 8977, 8978, 8979, 8997, 9099, 9163, 9212, 9213, 9214, 9216, 9256, 9310, 9317, 9318, 9340, 9341, 9342, 9343, 9344, 9345, 9349, 9438, 9439, 9542]),
      ]),
    ]
  ),
])
samples_2016["/TT_TuneCUETP8M1_13TeV-powheg-pythia8/RunIISpring16MiniAODv1-PUSpring16_80X_mcRun2_asymptotic_2016_v3_ext3-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "TT"),
  ("process_name_specific", "TT_ext3"),
  ("nof_files",             2124),
  ("nof_events",            249751606),
  ("use_it",                True),
  ("xsection",              831.760000),
  ("genWeight",             False),
  ("triggers",              [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2016/2017Jan12_forBDTtraining/ntuples/3l_1tau/TT_TuneCUETP8M1_13TeV-powheg-pythia8/VHBB_HEPPY_V24_TT_TuneCUETP8M1_13TeV-powheg-Py8__spr16MAv2-puspr16_HLT_80r2as_v14_ext3-v1/160909_063406"),
        ("selection", "*"),
        ("blacklist", [20, 21, 23, 24, 25, 28, 29, 110, 111, 112, 114, 118, 119, 130, 133, 134, 200, 201, 202, 203, 205, 231, 232, 233, 235, 236, 237, 252, 258, 259, 380, 381, 382, 383, 384, 385, 386, 387, 389, 430, 431, 432, 433, 434, 435, 436, 437, 438, 439, 600, 705, 708, 709, 780, 781, 782, 783, 784, 785, 786, 787, 788, 789, 920, 921, 922, 923, 926, 927, 1155, 1219, 1260, 1261, 1264, 1265, 1266, 1267, 1268, 1269, 1482, 1540, 1541, 1542, 1543, 1544, 1545, 1546, 1547, 1548, 1549, 1710, 1711, 1712, 1713, 1714, 1715, 1716, 1717, 1718, 1719, 1804, 1815, 1816, 1843, 1844, 1848, 1849, 1920, 1921, 1922, 1923, 1924, 1925, 1926, 1927, 1928, 1929]),
      ]),
    ]
  ),
])
samples_2016["/WZTo3LNu_TuneCUETP8M1_13TeV-powheg-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "EWK"),
  ("process_name_specific", "WZTo3LNu"),
  ("nof_files",             26),
  ("nof_events",            1921938),
  ("use_it",                True),
  ("xsection",              4.102000),
  ("genWeight",             False),
  ("triggers",              [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2016/2017Jan12_forBDTtraining/ntuples/3l_1tau/WZTo3LNu_TuneCUETP8M1_13TeV-powheg-pythia8/VHBB_HEPPY_V24bis_WZTo3LNu_TuneCUETP8M1_13TeV-powheg-Py8__spr16MAv2-puspr16_80r2as_2016_MAv2_v0-v1/160911_224418"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/ttHToNonbb_M125_13TeV_powheg_pythia8/RunIISpring16MiniAODv2-PUSpring16RAWAODSIM_reHLT_80X_mcRun2_asymptotic_v14-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "signal"),
  ("process_name_specific", "ttHToNonbb_M125"),
  ("nof_files",             43),
  ("nof_events",            3075610),
  ("use_it",                True),
  ("xsection",              0.215100),
  ("genWeight",             False),
  ("triggers",              [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2016/2017Jan12_forBDTtraining/ntuples/3l_1tau/ttHToNonbb_M125_13TeV_powheg_pythia8/VHBB_HEPPY_V24bis_ttHToNonbb_M125_13TeV_powheg_Py8__spr16MAv2-puspr16_HLT_80r2as_v14-v1/160911_224147"),
        ("selection", "*"),
        ("blacklist", [5, 13, 16, 18, 24, 28, 35]),
      ]),
    ]
  ),
])
