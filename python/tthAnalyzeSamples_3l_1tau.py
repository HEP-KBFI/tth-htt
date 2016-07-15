from collections import OrderedDict as OD

from tthAnalyzeSamples_1l_2tau import samples

for sample_name, sample_info in samples.items():
  sample_info["triggers"] = [ "1e", "2e", "1mu", "2mu", "1e1mu" ]

samples["/DoubleMuon/Run2015C_25ns-16Dec2015-v1/MINIAOD"] = OD([
  ("type", "data"),
  ("sample_category", "data_obs"),
  ("process_name_specific", "DoubleMuon_Run2015C"),
  ("nof_files", 23),
  ("nof_events", 900626),
  ("use_it", True),
  ("triggers", [ "2mu" ]),
  ("local_paths",
    [
      OD([
        ("path", "/hdfs/cms/store/user/kaehatah/DoubleMuon/VHBB_HEPPY_H20_DoubleMuon__Run2015C_25ns-16Dec2015-v1/160419_120720"),
        ("selection", "*"),
      ])
    ]
  )
])
samples["/DoubleMuon/Run2015D-16Dec2015-v1/MINIAOD"] = OD([
  ("type", "data"),
  ("sample_category", "data_obs"),
  ("process_name_specific", "DoubleMuon_Run2015D"),
  ("nof_files", 951),
  ("nof_events", 51342919),
  ("use_it", True),
  ("triggers", [ "2mu" ]),
  ("local_paths",
    [
      OD([
        ("path", "/hdfs/cms/store/user/kaehatah/DoubleMuon/VHBB_HEPPY_H20_DoubleMuon__Run2015D-16Dec2015-v1/160419_140710"),
        ("selection", "*"),
      ]),
      OD([
        ("path", "/hdfs/cms/store/user/kaehatah/DoubleMuon/VHBB_HEPPY_H20_DoubleMuon__Run2015D-16Dec2015-v1/160429_225658"),
        ("selection", "44,63,65,109,141,188,189,215,245,251,257,262,287,290,459,469,472,539,570,593,652,661,712,760,858,864,900,932"),
      ])
    ]
  )
])
samples["/DoubleEG/Run2015C_25ns-16Dec2015-v1/MINIAOD"] = OD([
  ("type", "data"),
  ("sample_category", "data_obs"),
  ("process_name_specific", "DoubleEG_Run2015C"),
  ("nof_files", 52),
  ("nof_events", 2127090),
  ("use_it", True),
  ("triggers", [ "2e" ]),
  ("local_paths",
    [
      OD([
        ("path", "/hdfs/cms/store/user/kaehatah/DoubleEG/VHBB_HEPPY_H20_DoubleEG__Run2015C_25ns-16Dec2015-v1/160419_140830"),
        ("selection", "*"),
      ]),
      OD([
        ("path", "/hdfs/cms/store/user/kaehatah/DoubleEG/VHBB_HEPPY_H20_DoubleEG__Run2015C_25ns-16Dec2015-v1/160429_225812"),
        ("selection", "1,30"),
      ])
    ]
  )
])
samples["/DoubleEG/Run2015D-16Dec2015-v2/MINIAOD"] = OD([
  ("type", "data"),
  ("sample_category", "data_obs"),
  ("process_name_specific", "DoubleEG_Run2015D"),
  ("nof_files", 1652),
  ("nof_events", 93018487),
  ("use_it", True),
  ("triggers", [ "2e" ]),
  ("local_paths",
    [
      OD([
        ("path", "/hdfs/cms/store/user/kaehatah/DoubleEG/VHBB_HEPPY_H20_DoubleEG__Run2015D-16Dec2015-v2/160420_113228"),
        ("selection", "*"),
      ]),
      OD([
        ("path", "/hdfs/cms/store/user/kaehatah/DoubleEG/VHBB_HEPPY_H20_DoubleEG__Run2015D-16Dec2015-v2/160429_225920"),
        ("selection", "15,19,111,130,156,175,191,235,239,309,361,376,395,409,413,422,448,470,483,498,507,532,568,584,597,612,666,670,"
                      "673,690,697,710,722,734,748,762,772,783,814,833,846,860,863,868,878,880,889,913,960,974,991,1019,1088,1091,1106,"
                      "1143,1176,1277,1366,1367,1410,1411,1425,1427,1428,1434,1456,1466,1514,1516,1522,1585,1613"),
      ])
    ]
  )
])
samples["/MuonEG/Run2015C_25ns-16Dec2015-v1/MINIAOD"] = OD([
  ("type", "data"),
  ("sample_category", "data_obs"),
  ("process_name_specific", "MuonEG_Run2015C"),
  ("nof_files", 6),
  ("nof_events", 111545),
  ("use_it", True),
  ("triggers", [ "1e1mu" ]),
  ("local_paths",
    [
      OD([
        ("path", "/hdfs/cms/store/user/kaehatah/MuonEG/VHBB_HEPPY_H20_MuonEG__Run2015C_25ns-16Dec2015-v1/160419_141135"),
        ("selection", "*"),
      ])
    ]
  )
])
samples["/MuonEG/Run2015D-16Dec2015-v1/MINIAOD"] = OD([
  ("type", "data"),
  ("sample_category", "data_obs"),
  ("process_name_specific", "MuonEG_Run2015D"),
  ("nof_files", 286),
  ("nof_events", 13442593),
  ("use_it", True),
  ("triggers", [ "1e1mu" ]),
  ("local_paths",
    [
      OD([
        ("path", "/hdfs/cms/store/user/kaehatah/MuonEG/VHBB_HEPPY_H20_MuonEG__Run2015D-16Dec2015-v1/160419_141314"),
        ("selection", "*"),
      ]),
      OD([
        ("path", "/hdfs/cms/store/user/kaehatah/MuonEG/VHBB_HEPPY_H20_MuonEG__Run2015D-16Dec2015-v1/160429_230034"),
        ("selection", "13,14,18,19,22,26,27,29,34,40,41,45,47,50,51,54,57,63,64,70,74,75,79,81,83,86,88,90,100,102,103,106,"
                      "107,108,110,112,117,119,124,128,129,132,134,135,141,144,145,148,154,157,159,162,163,170,177,180,181,182,"
                      "184,188,189,190,191,192,193,196,197,198,199,201,212,215,222,226,230,233,235,236,237,239,241,243,244,245,"
                      "247,248,252,253,254,259,260,263,265,270,274,275,277,278,281,284"),
      ]),
    ]
  )
])
samples["/SingleMuon/Run2015C_25ns-16Dec2015-v1/MINIAOD"] = OD([
  ("type", "data"),
  ("sample_category", "data_obs"),
  ("process_name_specific", "SingleMuon_Run2015C"),
  ("nof_files", 23),
  ("nof_events", 1341179),
  ("use_it", True),
  ("triggers", [ "1mu" ]),
  ("local_paths",
    [
      OD([
        ("path", "/hdfs/cms/store/user/kaehatah/SingleMuon/VHBB_HEPPY_H20_SingleMuon__Run2015C_25ns-16Dec2015-v1/160419_141430"),
        ("selection", "*"),
      ]),
      OD([
        ("path", "/hdfs/cms/store/user/kaehatah/SingleMuon/VHBB_HEPPY_H20_SingleMuon__Run2015C_25ns-16Dec2015-v1/160429_230148"),
        ("selection", "12"),
      ]),
    ]
  )
])
samples["/SingleMuon/Run2015D-16Dec2015-v1/MINIAOD"] = OD([
  ("type", "data"),
  ("sample_category", "data_obs"),
  ("process_name_specific", "SingleMuon_Run2015D"),
  ("nof_files", 1758),
  ("nof_events", 91999861),
  ("use_it", True),
  ("triggers", [ "1mu" ]),
  ("local_paths",
    [
      OD([
        ("path", "/hdfs/cms/store/user/kaehatah/SingleMuon/VHBB_HEPPY_H20_SingleMuon__Run2015D-16Dec2015-v1/160419_141549"),
        ("selection", "*"),
      ]),
      OD([
        ("path", "/hdfs/cms/store/user/kaehatah/SingleMuon/VHBB_HEPPY_H20_SingleMuon__Run2015D-16Dec2015-v1/160429_230258"),
        ("selection", "2,9,13,21,25,49,57,66,68,81,87,88,91,163,189,193,284,300,329,361,367,400,428,440,464,466,468,485,494,495,531,"
         "532,552,604,617,622,651,652,691,703,722,738,746,766,767,797,802,843,848,850,859,882,888,927,1083,1091,1107,1115,1116,1117,"
         "1129,1145,1165,1166,1174,1182,1188,1200,1203,1216,1222,1225,1262,1368,1386,1411,1421,1435,1459,1490,1523,1569,1594,1615,1642,"
         "1659,1750,1753"),
      ]),
    ]
  )
])
samples["/SingleElectron/Run2015C_25ns-16Dec2015-v1/MINIAOD"] = OD([
  ("type", "data"),
  ("sample_category", "data_obs"),
  ("process_name_specific", "SingleElectron_Run2015C"),
  ("nof_files", 21),
  ("nof_events", 837157),
  ("use_it", True),
  ("triggers", [ "1e" ]),
  ("local_paths",
    [
      OD([
        ("path", "/hdfs/cms/store/user/kaehatah/SingleElectron/VHBB_HEPPY_H20_SingleElectron__Run2015C_25ns-16Dec2015-v1/160419_132242"),
        ("selection", "*"),
      ]),
      OD([
        ("path", "/hdfs/cms/store/user/kaehatah/SingleElectron/VHBB_HEPPY_H20_SingleElectron__Run2015C_25ns-16Dec2015-v1/160429_230407"),
        ("selection", "14"),
      ]),
    ]
  )
])
samples["/SingleElectron/Run2015D-16Dec2015-v1/MINIAOD"] = OD([
  ("type", "data"),
  ("sample_category", "data_obs"),
  ("process_name_specific", "SingleElectron_Run2015D"),
  ("nof_files", 2430),
  ("nof_events", 134140420),
  ("use_it", True),
  ("triggers", [ "1e" ]),
  ("local_paths",
    [
      OD([
        ("path", "/hdfs/cms/store/user/kaehatah/SingleElectron/VHBB_HEPPY_H20_SingleElectron__Run2015D-16Dec2015-v1/160420_113346"),
        ("selection", "*"),
      ]),
      OD([
        ("path", "/hdfs/cms/store/user/kaehatah/SingleElectron/VHBB_HEPPY_H20_SingleElectron__Run2015D-16Dec2015-v1/160429_230512"),
        ("selection", "8,18,24,32,33,34,36,45,54,57,59,72,80,89,91,103,107,119,123,146,154,158,189,194,215,251,260,287,292,296,312,329,335,"
         "653,854,863,906,927,928,959,970,976,987,1005,1008,1016,1027,1066,1116,1130,1131,1144,1154,1160,1170,1171,1178,1191,1194,1236,1241,"
         "1256,1311,1340,1344,1368,1426,1433,1449,1517,1615,1624,1631,1634,1645,1663,1674,1678,1699,1705,1744,1767,1789,1909,1919,1923,1937,"
         "1946,2039,2046,2079,2125,2127,2131,2135,2141,2147,2158,2161,2164,2186,2190,2193,2227,2239,2279,2290,2314,2341,2364,2370,2377,2392,"
         "2395,2396,2406,2430"),
      ]),
    ]
  )
])
       
