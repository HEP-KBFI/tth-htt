from collections import OrderedDict as OD

# file generated at 2018-05-30 21:09:00 with the following command:
# create_dictionary.py -m python/samples/metaDict_2017.py -p python/samples/sampleLocations_2017_post.txt -Z zeroes.txt -z zombies.txt -N samples_2017 -E 2017 -g tthAnalyzeSamples_2017.py -o python/samples -M

samples_2017 = OD()
samples_2017["/SingleElectron/Run2017B-17Nov2017-v1/MINIAOD"] = OD([
  ("type",                            "data"),
  ("sample_category",                 "data_obs"),
  ("process_name_specific",           "SingleElectron_Run2017B_17Nov2017_v1"),
  ("nof_files",                       58),
  ("nof_db_files",                    634),
  ("nof_events",                      56501676),
  ("nof_tree_events",                 56501676),
  ("nof_db_events",                   60537490),
  ("fsize_local",                     26571379117), # 26.57GB, avg file size 458.13MB
  ("fsize_db",                        1839129571740), # 1.84TB, avg file size 2.90GB
  ("use_it",                          True),
  ("triggers",                        ['1e']),
  ("has_LHE",                         False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018May29_woPresel_nom_all/ntuples/SingleElectron_Run2017B_17Nov2017_v1"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
  ("missing_from_superset",           [

  ]),
  ("missing_hlt_paths",               [
    "HLT_Ele17_CaloIdM_TrackIdM_PFJet30",
    "HLT_Ele23_CaloIdM_TrackIdM_PFJet30",
    "HLT_Ele32_WPTight_Gsf",
    "HLT_Ele8_CaloIdM_TrackIdM_PFJet30",
  ]),
])

samples_2017["/SingleElectron/Run2017C-17Nov2017-v1/MINIAOD"] = OD([
  ("type",                            "data"),
  ("sample_category",                 "data_obs"),
  ("process_name_specific",           "SingleElectron_Run2017C_17Nov2017_v1"),
  ("nof_files",                       130),
  ("nof_db_files",                    1705),
  ("nof_events",                      127361546),
  ("nof_tree_events",                 127361546),
  ("nof_db_events",                   136637888),
  ("fsize_local",                     70217992609), # 70.22GB, avg file size 540.14MB
  ("fsize_db",                        4293152220674), # 4.29TB, avg file size 2.52GB
  ("use_it",                          True),
  ("triggers",                        ['1e']),
  ("has_LHE",                         False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018May29_woPresel_nom_all/ntuples/SingleElectron_Run2017C_17Nov2017_v1"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
  ("missing_from_superset",           [

  ]),
  ("missing_hlt_paths",               [
    "HLT_Ele32_WPTight_Gsf",
  ]),
])

samples_2017["/SingleElectron/Run2017D-17Nov2017-v1/MINIAOD"] = OD([
  ("type",                            "data"),
  ("sample_category",                 "data_obs"),
  ("process_name_specific",           "SingleElectron_Run2017D_17Nov2017_v1"),
  ("nof_files",                       52),
  ("nof_db_files",                    693),
  ("nof_events",                      50610320),
  ("nof_tree_events",                 50610320),
  ("nof_db_events",                   51526710),
  ("fsize_local",                     27007953234), # 27.01GB, avg file size 519.38MB
  ("fsize_db",                        1584079997402), # 1.58TB, avg file size 2.29GB
  ("use_it",                          True),
  ("triggers",                        ['1e']),
  ("has_LHE",                         False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018May29_woPresel_nom_all/ntuples/SingleElectron_Run2017D_17Nov2017_v1"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
  ("missing_from_superset",           [

  ]),
  ("missing_hlt_paths",               [

  ]),
])

samples_2017["/SingleElectron/Run2017E-17Nov2017-v1/MINIAOD"] = OD([
  ("type",                            "data"),
  ("sample_category",                 "data_obs"),
  ("process_name_specific",           "SingleElectron_Run2017E_17Nov2017_v1"),
  ("nof_files",                       102),
  ("nof_db_files",                    1280),
  ("nof_events",                      100205122),
  ("nof_tree_events",                 100205122),
  ("nof_db_events",                   102121689),
  ("fsize_local",                     56176576033), # 56.18GB, avg file size 550.75MB
  ("fsize_db",                        3608372444378), # 3.61TB, avg file size 2.82GB
  ("use_it",                          True),
  ("triggers",                        ['1e']),
  ("has_LHE",                         False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018May29_woPresel_nom_all/ntuples/SingleElectron_Run2017E_17Nov2017_v1"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
  ("missing_from_superset",           [

  ]),
  ("missing_hlt_paths",               [

  ]),
])

samples_2017["/SingleElectron/Run2017F-17Nov2017-v1/MINIAOD"] = OD([
  ("type",                            "data"),
  ("sample_category",                 "data_obs"),
  ("process_name_specific",           "SingleElectron_Run2017F_17Nov2017_v1"),
  ("nof_files",                       128),
  ("nof_db_files",                    1583),
  ("nof_events",                      126059593),
  ("nof_tree_events",                 126059593),
  ("nof_db_events",                   128467223),
  ("fsize_local",                     71676732500), # 71.68GB, avg file size 559.97MB
  ("fsize_db",                        4628019555901), # 4.63TB, avg file size 2.92GB
  ("use_it",                          True),
  ("triggers",                        ['1e']),
  ("has_LHE",                         False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018May29_woPresel_nom_all/ntuples/SingleElectron_Run2017F_17Nov2017_v1"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
  ("missing_from_superset",           [

  ]),
  ("missing_hlt_paths",               [

  ]),
])

samples_2017["/SingleMuon/Run2017B-17Nov2017-v1/MINIAOD"] = OD([
  ("type",                            "data"),
  ("sample_category",                 "data_obs"),
  ("process_name_specific",           "SingleMuon_Run2017B_17Nov2017_v1"),
  ("nof_files",                       134),
  ("nof_db_files",                    1146),
  ("nof_events",                      128496874),
  ("nof_tree_events",                 128496874),
  ("nof_db_events",                   136300266),
  ("fsize_local",                     47030535498), # 47.03GB, avg file size 350.97MB
  ("fsize_db",                        3681903942053), # 3.68TB, avg file size 3.21GB
  ("use_it",                          True),
  ("triggers",                        ['1mu']),
  ("has_LHE",                         False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018May29_woPresel_nom_all/ntuples/SingleMuon_Run2017B_17Nov2017_v1"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
  ("missing_from_superset",           [

  ]),
  ("missing_hlt_paths",               [
    "HLT_Mu3_PFJet40",
  ]),
])

samples_2017["/SingleMuon/Run2017C-17Nov2017-v1/MINIAOD"] = OD([
  ("type",                            "data"),
  ("sample_category",                 "data_obs"),
  ("process_name_specific",           "SingleMuon_Run2017C_17Nov2017_v1"),
  ("nof_files",                       157),
  ("nof_db_files",                    1511),
  ("nof_events",                      154633551),
  ("nof_tree_events",                 154633551),
  ("nof_db_events",                   165652756),
  ("fsize_local",                     67158755671), # 67.16GB, avg file size 427.76MB
  ("fsize_db",                        4719988428330), # 4.72TB, avg file size 3.12GB
  ("use_it",                          True),
  ("triggers",                        ['1mu']),
  ("has_LHE",                         False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018May29_woPresel_nom_all/ntuples/SingleMuon_Run2017C_17Nov2017_v1"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
  ("missing_from_superset",           [

  ]),
  ("missing_hlt_paths",               [

  ]),
])

samples_2017["/SingleMuon/Run2017D-17Nov2017-v1/MINIAOD"] = OD([
  ("type",                            "data"),
  ("sample_category",                 "data_obs"),
  ("process_name_specific",           "SingleMuon_Run2017D_17Nov2017_v1"),
  ("nof_files",                       70),
  ("nof_db_files",                    823),
  ("nof_events",                      69031074),
  ("nof_tree_events",                 69031074),
  ("nof_db_events",                   70361660),
  ("fsize_local",                     30232837534), # 30.23GB, avg file size 431.90MB
  ("fsize_db",                        2004044655656), # 2.00TB, avg file size 2.44GB
  ("use_it",                          True),
  ("triggers",                        ['1mu']),
  ("has_LHE",                         False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018May29_woPresel_nom_all/ntuples/SingleMuon_Run2017D_17Nov2017_v1"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
  ("missing_from_superset",           [

  ]),
  ("missing_hlt_paths",               [

  ]),
])

samples_2017["/SingleMuon/Run2017E-17Nov2017-v1/MINIAOD"] = OD([
  ("type",                            "data"),
  ("sample_category",                 "data_obs"),
  ("process_name_specific",           "SingleMuon_Run2017E_17Nov2017_v1"),
  ("nof_files",                       155),
  ("nof_db_files",                    1669),
  ("nof_events",                      151713898),
  ("nof_tree_events",                 151713898),
  ("nof_db_events",                   154630534),
  ("fsize_local",                     67594439336), # 67.59GB, avg file size 436.09MB
  ("fsize_db",                        5063603395030), # 5.06TB, avg file size 3.03GB
  ("use_it",                          True),
  ("triggers",                        ['1mu']),
  ("has_LHE",                         False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018May29_woPresel_nom_all/ntuples/SingleMuon_Run2017E_17Nov2017_v1"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
  ("missing_from_superset",           [

  ]),
  ("missing_hlt_paths",               [

  ]),
])

samples_2017["/SingleMuon/Run2017F-17Nov2017-v1/MINIAOD"] = OD([
  ("type",                            "data"),
  ("sample_category",                 "data_obs"),
  ("process_name_specific",           "SingleMuon_Run2017F_17Nov2017_v1"),
  ("nof_files",                       246),
  ("nof_db_files",                    2737),
  ("nof_events",                      235942694),
  ("nof_tree_events",                 235942694),
  ("nof_db_events",                   242140980),
  ("fsize_local",                     107082955374), # 107.08GB, avg file size 435.30MB
  ("fsize_db",                        8025096282975), # 8.03TB, avg file size 2.93GB
  ("use_it",                          True),
  ("triggers",                        ['1mu']),
  ("has_LHE",                         False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018May29_woPresel_nom_all/ntuples/SingleMuon_Run2017F_17Nov2017_v1"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
  ("missing_from_superset",           [

  ]),
  ("missing_hlt_paths",               [

  ]),
])

samples_2017["/DoubleEG/Run2017B-17Nov2017-v1/MINIAOD"] = OD([
  ("type",                            "data"),
  ("sample_category",                 "data_obs"),
  ("process_name_specific",           "DoubleEG_Run2017B_17Nov2017_v1"),
  ("nof_files",                       55),
  ("nof_db_files",                    759),
  ("nof_events",                      54125900),
  ("nof_tree_events",                 54125900),
  ("nof_db_events",                   58088760),
  ("fsize_local",                     28370425314), # 28.37GB, avg file size 515.83MB
  ("fsize_db",                        2000582502159), # 2.00TB, avg file size 2.64GB
  ("use_it",                          True),
  ("triggers",                        ['2e', '3e']),
  ("has_LHE",                         False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018May29_woPresel_nom_all/ntuples/DoubleEG_Run2017B_17Nov2017_v1"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
  ("missing_from_superset",           [

  ]),
  ("missing_hlt_paths",               [

  ]),
])

samples_2017["/DoubleEG/Run2017C-17Nov2017-v1/MINIAOD"] = OD([
  ("type",                            "data"),
  ("sample_category",                 "data_obs"),
  ("process_name_specific",           "DoubleEG_Run2017C_17Nov2017_v1"),
  ("nof_files",                       61),
  ("nof_db_files",                    847),
  ("nof_events",                      60063430),
  ("nof_tree_events",                 60063430),
  ("nof_db_events",                   65181125),
  ("fsize_local",                     33309666732), # 33.31GB, avg file size 546.06MB
  ("fsize_db",                        2252815090346), # 2.25TB, avg file size 2.66GB
  ("use_it",                          True),
  ("triggers",                        ['2e', '3e']),
  ("has_LHE",                         False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018May29_woPresel_nom_all/ntuples/DoubleEG_Run2017C_17Nov2017_v1"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
  ("missing_from_superset",           [

  ]),
  ("missing_hlt_paths",               [

  ]),
])

samples_2017["/DoubleEG/Run2017D-17Nov2017-v1/MINIAOD"] = OD([
  ("type",                            "data"),
  ("sample_category",                 "data_obs"),
  ("process_name_specific",           "DoubleEG_Run2017D_17Nov2017_v1"),
  ("nof_files",                       26),
  ("nof_db_files",                    344),
  ("nof_events",                      25209987),
  ("nof_tree_events",                 25209987),
  ("nof_db_events",                   25911432),
  ("fsize_local",                     14074701784), # 14.07GB, avg file size 541.33MB
  ("fsize_db",                        881576196022), # 881.58GB, avg file size 2.56GB
  ("use_it",                          True),
  ("triggers",                        ['2e', '3e']),
  ("has_LHE",                         False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018May29_woPresel_nom_all/ntuples/DoubleEG_Run2017D_17Nov2017_v1"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
  ("missing_from_superset",           [

  ]),
  ("missing_hlt_paths",               [

  ]),
])

samples_2017["/DoubleEG/Run2017E-17Nov2017-v1/MINIAOD"] = OD([
  ("type",                            "data"),
  ("sample_category",                 "data_obs"),
  ("process_name_specific",           "DoubleEG_Run2017E_17Nov2017_v1"),
  ("nof_files",                       55),
  ("nof_db_files",                    639),
  ("nof_events",                      54624312),
  ("nof_tree_events",                 54624312),
  ("nof_db_events",                   56235775),
  ("fsize_local",                     32177164959), # 32.18GB, avg file size 585.04MB
  ("fsize_db",                        2140362591723), # 2.14TB, avg file size 3.35GB
  ("use_it",                          True),
  ("triggers",                        ['2e', '3e']),
  ("has_LHE",                         False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018May29_woPresel_nom_all/ntuples/DoubleEG_Run2017E_17Nov2017_v1"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
  ("missing_from_superset",           [

  ]),
  ("missing_hlt_paths",               [

  ]),
])

samples_2017["/DoubleEG/Run2017F-17Nov2017-v1/MINIAOD"] = OD([
  ("type",                            "data"),
  ("sample_category",                 "data_obs"),
  ("process_name_specific",           "DoubleEG_Run2017F_17Nov2017_v1"),
  ("nof_files",                       73),
  ("nof_db_files",                    1024),
  ("nof_events",                      72430490),
  ("nof_tree_events",                 72430490),
  ("nof_db_events",                   74344288),
  ("fsize_local",                     44440283362), # 44.44GB, avg file size 608.77MB
  ("fsize_db",                        2879805741948), # 2.88TB, avg file size 2.81GB
  ("use_it",                          True),
  ("triggers",                        ['2e', '3e']),
  ("has_LHE",                         False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018May29_woPresel_nom_all/ntuples/DoubleEG_Run2017F_17Nov2017_v1"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
  ("missing_from_superset",           [

  ]),
  ("missing_hlt_paths",               [

  ]),
])

samples_2017["/DoubleMuon/Run2017B-17Nov2017-v1/MINIAOD"] = OD([
  ("type",                            "data"),
  ("sample_category",                 "data_obs"),
  ("process_name_specific",           "DoubleMuon_Run2017B_17Nov2017_v1"),
  ("nof_files",                       14),
  ("nof_db_files",                    164),
  ("nof_events",                      13572040),
  ("nof_tree_events",                 13572040),
  ("nof_db_events",                   14501767),
  ("fsize_local",                     5710616521), # 5.71GB, avg file size 407.90MB
  ("fsize_db",                        429564397133), # 429.56GB, avg file size 2.62GB
  ("use_it",                          True),
  ("triggers",                        ['2mu', '3mu']),
  ("has_LHE",                         False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018May29_woPresel_nom_all/ntuples/DoubleMuon_Run2017B_17Nov2017_v1"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
  ("missing_from_superset",           [

  ]),
  ("missing_hlt_paths",               [
    "HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8",
  ]),
])

samples_2017["/DoubleMuon/Run2017C-17Nov2017-v1/MINIAOD"] = OD([
  ("type",                            "data"),
  ("sample_category",                 "data_obs"),
  ("process_name_specific",           "DoubleMuon_Run2017C_17Nov2017_v1"),
  ("nof_files",                       46),
  ("nof_db_files",                    466),
  ("nof_events",                      46273101),
  ("nof_tree_events",                 46273101),
  ("nof_db_events",                   49636525),
  ("fsize_local",                     21171145260), # 21.17GB, avg file size 460.24MB
  ("fsize_db",                        1506932771681), # 1.51TB, avg file size 3.23GB
  ("use_it",                          True),
  ("triggers",                        ['2mu', '3mu']),
  ("has_LHE",                         False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018May29_woPresel_nom_all/ntuples/DoubleMuon_Run2017C_17Nov2017_v1"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
  ("missing_from_superset",           [

  ]),
  ("missing_hlt_paths",               [

  ]),
])

samples_2017["/DoubleMuon/Run2017D-17Nov2017-v1/MINIAOD"] = OD([
  ("type",                            "data"),
  ("sample_category",                 "data_obs"),
  ("process_name_specific",           "DoubleMuon_Run2017D_17Nov2017_v1"),
  ("nof_files",                       23),
  ("nof_db_files",                    242),
  ("nof_events",                      22646081),
  ("nof_tree_events",                 22646081),
  ("nof_db_events",                   23075733),
  ("fsize_local",                     10309175601), # 10.31GB, avg file size 448.23MB
  ("fsize_db",                        700300808389), # 700.30GB, avg file size 2.89GB
  ("use_it",                          True),
  ("triggers",                        ['2mu', '3mu']),
  ("has_LHE",                         False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018May29_woPresel_nom_all/ntuples/DoubleMuon_Run2017D_17Nov2017_v1"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
  ("missing_from_superset",           [

  ]),
  ("missing_hlt_paths",               [

  ]),
])

samples_2017["/DoubleMuon/Run2017E-17Nov2017-v1/MINIAOD"] = OD([
  ("type",                            "data"),
  ("sample_category",                 "data_obs"),
  ("process_name_specific",           "DoubleMuon_Run2017E_17Nov2017_v1"),
  ("nof_files",                       51),
  ("nof_db_files",                    596),
  ("nof_events",                      50596536),
  ("nof_tree_events",                 50596536),
  ("nof_db_events",                   51589091),
  ("fsize_local",                     24805088136), # 24.81GB, avg file size 486.37MB
  ("fsize_db",                        1822288632364), # 1.82TB, avg file size 3.06GB
  ("use_it",                          True),
  ("triggers",                        ['2mu', '3mu']),
  ("has_LHE",                         False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018May29_woPresel_nom_all/ntuples/DoubleMuon_Run2017E_17Nov2017_v1"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
  ("missing_from_superset",           [

  ]),
  ("missing_hlt_paths",               [

  ]),
])

samples_2017["/DoubleMuon/Run2017F-17Nov2017-v1/MINIAOD"] = OD([
  ("type",                            "data"),
  ("sample_category",                 "data_obs"),
  ("process_name_specific",           "DoubleMuon_Run2017F_17Nov2017_v1"),
  ("nof_files",                       76),
  ("nof_db_files",                    875),
  ("nof_events",                      75300854),
  ("nof_tree_events",                 75300854),
  ("nof_db_events",                   79756560),
  ("fsize_local",                     35537181250), # 35.54GB, avg file size 467.59MB
  ("fsize_db",                        2792396630929), # 2.79TB, avg file size 3.19GB
  ("use_it",                          True),
  ("triggers",                        ['2mu', '3mu']),
  ("has_LHE",                         False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018May29_woPresel_nom_all/ntuples/DoubleMuon_Run2017F_17Nov2017_v1"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
  ("missing_from_superset",           [

  ]),
  ("missing_hlt_paths",               [

  ]),
])

samples_2017["/MuonEG/Run2017B-17Nov2017-v1/MINIAOD"] = OD([
  ("type",                            "data"),
  ("sample_category",                 "data_obs"),
  ("process_name_specific",           "MuonEG_Run2017B_17Nov2017_v1"),
  ("nof_files",                       5),
  ("nof_db_files",                    70),
  ("nof_events",                      4153318),
  ("nof_tree_events",                 4153318),
  ("nof_db_events",                   4453465),
  ("fsize_local",                     2361920536), # 2.36GB, avg file size 472.38MB
  ("fsize_db",                        151955610304), # 151.96GB, avg file size 2.17GB
  ("use_it",                          True),
  ("triggers",                        ['1e1mu', '2e1mu', '1e2mu']),
  ("has_LHE",                         False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018May29_woPresel_nom_all/ntuples/MuonEG_Run2017B_17Nov2017_v1"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
  ("missing_from_superset",           [

  ]),
  ("missing_hlt_paths",               [
    "HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL",
  ]),
])

samples_2017["/MuonEG/Run2017C-17Nov2017-v1/MINIAOD"] = OD([
  ("type",                            "data"),
  ("sample_category",                 "data_obs"),
  ("process_name_specific",           "MuonEG_Run2017C_17Nov2017_v1"),
  ("nof_files",                       15),
  ("nof_db_files",                    219),
  ("nof_events",                      14579589),
  ("nof_tree_events",                 14579589),
  ("nof_db_events",                   15595214),
  ("fsize_local",                     9207425519), # 9.21GB, avg file size 613.83MB
  ("fsize_db",                        548775705076), # 548.78GB, avg file size 2.51GB
  ("use_it",                          True),
  ("triggers",                        ['1e1mu', '2e1mu', '1e2mu']),
  ("has_LHE",                         False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018May29_woPresel_nom_all/ntuples/MuonEG_Run2017C_17Nov2017_v1"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
  ("missing_from_superset",           [

  ]),
  ("missing_hlt_paths",               [

  ]),
])

samples_2017["/MuonEG/Run2017D-17Nov2017-v1/MINIAOD"] = OD([
  ("type",                            "data"),
  ("sample_category",                 "data_obs"),
  ("process_name_specific",           "MuonEG_Run2017D_17Nov2017_v1"),
  ("nof_files",                       9),
  ("nof_db_files",                    126),
  ("nof_events",                      9012928),
  ("nof_tree_events",                 9012928),
  ("nof_db_events",                   9164365),
  ("fsize_local",                     5776270868), # 5.78GB, avg file size 641.81MB
  ("fsize_db",                        321530133689), # 321.53GB, avg file size 2.55GB
  ("use_it",                          True),
  ("triggers",                        ['1e1mu', '2e1mu', '1e2mu']),
  ("has_LHE",                         False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018May29_woPresel_nom_all/ntuples/MuonEG_Run2017D_17Nov2017_v1"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
  ("missing_from_superset",           [

  ]),
  ("missing_hlt_paths",               [

  ]),
])

samples_2017["/MuonEG/Run2017E-17Nov2017-v1/MINIAOD"] = OD([
  ("type",                            "data"),
  ("sample_category",                 "data_obs"),
  ("process_name_specific",           "MuonEG_Run2017E_17Nov2017_v1"),
  ("nof_files",                       19),
  ("nof_db_files",                    239),
  ("nof_events",                      18703362),
  ("nof_tree_events",                 18703362),
  ("nof_db_events",                   19043421),
  ("fsize_local",                     12303148029), # 12.30GB, avg file size 647.53MB
  ("fsize_db",                        753395415338), # 753.40GB, avg file size 3.15GB
  ("use_it",                          True),
  ("triggers",                        ['1e1mu', '2e1mu', '1e2mu']),
  ("has_LHE",                         False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018May29_woPresel_nom_all/ntuples/MuonEG_Run2017E_17Nov2017_v1"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
  ("missing_from_superset",           [

  ]),
  ("missing_hlt_paths",               [

  ]),
])

samples_2017["/MuonEG/Run2017F-17Nov2017-v1/MINIAOD"] = OD([
  ("type",                            "data"),
  ("sample_category",                 "data_obs"),
  ("process_name_specific",           "MuonEG_Run2017F_17Nov2017_v1"),
  ("nof_files",                       26),
  ("nof_db_files",                    362),
  ("nof_events",                      25342217),
  ("nof_tree_events",                 25342217),
  ("nof_db_events",                   25776363),
  ("fsize_local",                     17092450672), # 17.09GB, avg file size 657.40MB
  ("fsize_db",                        1031887580033), # 1.03TB, avg file size 2.85GB
  ("use_it",                          True),
  ("triggers",                        ['1e1mu', '2e1mu', '1e2mu']),
  ("has_LHE",                         False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018May29_woPresel_nom_all/ntuples/MuonEG_Run2017F_17Nov2017_v1"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
  ("missing_from_superset",           [

  ]),
  ("missing_hlt_paths",               [

  ]),
])

samples_2017["/ttHJetToNonbb_M125_TuneCP5_13TeV_amcatnloFXFX_madspin_pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "signal"),
  ("process_name_specific",           "ttHJetToNonbb_M125_amcatnlo"),
  ("nof_files",                       49),
  ("nof_db_files",                    283),
  ("nof_events",                      3321918),
  ("nof_tree_events",                 9650032),
  ("nof_db_events",                   9650032),
  ("fsize_local",                     32075057875), # 32.08GB, avg file size 654.59MB
  ("fsize_db",                        603282930374), # 603.28GB, avg file size 2.13GB
  ("use_it",                          True),
  ("xsection",                        0.2118),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("has_LHE",                         True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018May30_6samples_woPresel_nom_all/ntuples/ttHJetToNonbb_M125_amcatnlo"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
  ("missing_from_superset",           [
    # not computed
  ]),
  ("missing_hlt_paths",               [

  ]),
])

samples_2017["/ttHToNonbb_M125_TuneCP5_13TeV-powheg-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "signal"),
  ("process_name_specific",           "ttHToNonbb_M125_powheg"),
  ("nof_files",                       39),
  ("nof_db_files",                    219),
  ("nof_events",                      7522034),
  ("nof_tree_events",                 7669336),
  ("nof_db_events",                   7669336),
  ("fsize_local",                     25927235525), # 25.93GB, avg file size 664.80MB
  ("fsize_db",                        465938496839), # 465.94GB, avg file size 2.13GB
  ("use_it",                          False),
  ("xsection",                        0.2118),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("has_LHE",                         True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018May30_6samples_woPresel_nom_all/ntuples/ttHToNonbb_M125_powheg"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
  ("missing_from_superset",           [
    # not computed
  ]),
  ("missing_hlt_paths",               [

  ]),
])

samples_2017["/ttHJetTobb_M125_TuneCP5_13TeV_amcatnloFXFX_madspin_pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "signal"),
  ("process_name_specific",           "ttHJetTobb_M125_amcatnlo"),
  ("nof_files",                       50),
  ("nof_db_files",                    259),
  ("nof_events",                      3408993),
  ("nof_tree_events",                 9911561),
  ("nof_db_events",                   9911561),
  ("fsize_local",                     31641801801), # 31.64GB, avg file size 632.84MB
  ("fsize_db",                        626042445493), # 626.04GB, avg file size 2.42GB
  ("use_it",                          False),
  ("xsection",                        0.2953),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("has_LHE",                         True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018May30_6samples_woPresel_nom_all/ntuples/ttHJetTobb_M125_amcatnlo"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
  ("missing_from_superset",           [
    # not computed
  ]),
  ("missing_hlt_paths",               [

  ]),
])

samples_2017["/GluGluHToZZTo4L_M125_13TeV_powheg2_JHUGenV7011_pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "additional_signal_overlap"),
  ("process_name_specific",           "GluGluHToZZTo4L"),
  ("nof_files",                       5),
  ("nof_db_files",                    47),
  ("nof_events",                      924557),
  ("nof_tree_events",                 934244),
  ("nof_db_events",                   934244),
  ("fsize_local",                     1674837907), # 1.67GB, avg file size 334.97MB
  ("fsize_db",                        42622664498), # 42.62GB, avg file size 906.87MB
  ("use_it",                          True),
  ("xsection",                        0.01212),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("has_LHE",                         True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018May30_6samples_woPresel_nom_all/ntuples/GluGluHToZZTo4L"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
  ("missing_from_superset",           [
    # not computed
  ]),
  ("missing_hlt_paths",               [

  ]),
])

samples_2017["/TTZToLLNuNu_M-10_TuneCP5_13TeV-amcatnlo-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "TTZ"),
  ("process_name_specific",           "TTZToLL_M10"),
  ("nof_files",                       8),
  ("nof_db_files",                    199),
  ("nof_events",                      3570880),
  ("nof_tree_events",                 7563490),
  ("nof_db_events",                   7563490),
  ("fsize_local",                     22318896964), # 22.32GB, avg file size 2.79GB
  ("fsize_db",                        444833969271), # 444.83GB, avg file size 2.24GB
  ("use_it",                          True),
  ("xsection",                        0.2529),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("has_LHE",                         True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018May29_woPresel_nom_all/ntuples/TTZToLL_M10"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
  ("missing_from_superset",           [
    # not computed
  ]),
  ("missing_hlt_paths",               [

  ]),
])

samples_2017["/TTZToLL_M-1to10_TuneCP5_13TeV-amcatnlo-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "TTZ"),
  ("process_name_specific",           "TTZToLL_M-1to10"),
  ("nof_files",                       1),
  ("nof_db_files",                    17),
  ("nof_events",                      131171),
  ("nof_tree_events",                 250000),
  ("nof_db_events",                   250000),
  ("fsize_local",                     708595588), # 708.60MB, avg file size 708.60MB
  ("fsize_db",                        14727460148), # 14.73GB, avg file size 866.32MB
  ("use_it",                          True),
  ("xsection",                        0.0493),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("has_LHE",                         True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018May29_woPresel_nom_all/ntuples/TTZToLL_M-1to10"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
  ("missing_from_superset",           [
    # not computed
  ]),
  ("missing_hlt_paths",               [

  ]),
])

samples_2017["/TTWJetsToLNu_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v2/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "TTW"),
  ("process_name_specific",           "TTWJetsToLNu"),
  ("nof_files",                       25),
  ("nof_db_files",                    109),
  ("nof_events",                      5353357),
  ("nof_tree_events",                 4925829),
  ("nof_db_events",                   4925829),
  ("fsize_local",                     14982758596), # 14.98GB, avg file size 599.31MB
  ("fsize_db",                        292280765632), # 292.28GB, avg file size 2.68GB
  ("use_it",                          True),
  ("xsection",                        0.2043),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("has_LHE",                         True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018May30_6samples_woPresel_nom_all/ntuples/TTWJetsToLNu"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
  ("missing_from_superset",           [
    # not computed
  ]),
  ("missing_hlt_paths",               [

  ]),
])

samples_2017["/TTWJetsToLNu_TuneCP5_PSweights_13TeV-amcatnloFXFX-madspin-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "TTW"),
  ("process_name_specific",           "TTWJetsToLNu_PSweights"),
  ("nof_files",                       5),
  ("nof_db_files",                    122),
  ("nof_events",                      5353357),
  ("nof_tree_events",                 4889942),
  ("nof_db_events",                   4889942),
  ("fsize_local",                     14820288326), # 14.82GB, avg file size 2.96GB
  ("fsize_db",                        290787551975), # 290.79GB, avg file size 2.38GB
  ("use_it",                          True),
  ("xsection",                        0.2043),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("has_LHE",                         True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018May29_woPresel_nom_all/ntuples/TTWJetsToLNu_PSweights"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
  ("missing_from_superset",           [
    # not computed
  ]),
  ("missing_hlt_paths",               [

  ]),
])

samples_2017["/TTWW_TuneCP5_13TeV-madgraph-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10_ext1-v2/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "TTWW"),
  ("process_name_specific",           "TTWW"),
  ("nof_files",                       1),
  ("nof_db_files",                    11),
  ("nof_events",                      199017),
  ("nof_tree_events",                 200000),
  ("nof_db_events",                   200000),
  ("fsize_local",                     676921422), # 676.92MB, avg file size 676.92MB
  ("fsize_db",                        13111885203), # 13.11GB, avg file size 1.19GB
  ("use_it",                          True),
  ("xsection",                        0.007834),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("has_LHE",                         True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018May29_woPresel_nom_all/ntuples/TTWW"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
  ("missing_from_superset",           [
    # not computed
  ]),
  ("missing_hlt_paths",               [

  ]),
])

samples_2017["/ST_s-channel_4f_leptonDecays_TuneCP5_13TeV-amcatnlo-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "TT"),
  ("process_name_specific",           "ST_s-channel_4f_leptonDecays"),
  ("nof_files",                       10),
  ("nof_db_files",                    217),
  ("nof_events",                      5912237),
  ("nof_tree_events",                 9472619),
  ("nof_db_events",                   9472619),
  ("fsize_local",                     17207425593), # 17.21GB, avg file size 1.72GB
  ("fsize_db",                        423862017407), # 423.86GB, avg file size 1.95GB
  ("use_it",                          True),
  ("xsection",                        3.36),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("has_LHE",                         True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018May29_woPresel_nom_all/ntuples/ST_s-channel_4f_leptonDecays"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
  ("missing_from_superset",           [
    # not computed
  ]),
  ("missing_hlt_paths",               [

  ]),
])

samples_2017["/ST_t-channel_antitop_4f_inclusiveDecays_TuneCP5_13TeV-powhegV2-madspin-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "TT"),
  ("process_name_specific",           "ST_t-channel_antitop_4f_inclusiveDecays"),
  ("nof_files",                       4),
  ("nof_db_files",                    116),
  ("nof_events",                      3891275),
  ("nof_tree_events",                 3891190),
  ("nof_db_events",                   3891190),
  ("fsize_local",                     6923286441), # 6.92GB, avg file size 1.73GB
  ("fsize_db",                        177784436788), # 177.78GB, avg file size 1.53GB
  ("use_it",                          True),
  ("xsection",                        80.95),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("has_LHE",                         True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018May29_woPresel_nom_all/ntuples/ST_t-channel_antitop_4f_inclusiveDecays"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
  ("missing_from_superset",           [
    # not computed
  ]),
  ("missing_hlt_paths",               [

  ]),
])

samples_2017["/ST_t-channel_top_4f_inclusiveDecays_TuneCP5_13TeV-powhegV2-madspin-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "TT"),
  ("process_name_specific",           "ST_t-channel_top_4f_inclusiveDecays"),
  ("nof_files",                       7),
  ("nof_db_files",                    186),
  ("nof_events",                      5841440),
  ("nof_tree_events",                 5841455),
  ("nof_db_events",                   5841455),
  ("fsize_local",                     10399199943), # 10.40GB, avg file size 1.49GB
  ("fsize_db",                        268058212482), # 268.06GB, avg file size 1.44GB
  ("use_it",                          True),
  ("xsection",                        136.02),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("has_LHE",                         True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018May29_woPresel_nom_all/ntuples/ST_t-channel_top_4f_inclusiveDecays"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
  ("missing_from_superset",           [
    # not computed
  ]),
  ("missing_hlt_paths",               [

  ]),
])

samples_2017["/ST_tW_antitop_5f_inclusiveDecays_TuneCP5_13TeV-powheg-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "TT"),
  ("process_name_specific",           "ST_tW_antitop_5f_inclusiveDecays"),
  ("nof_files",                       8),
  ("nof_db_files",                    155),
  ("nof_events",                      7697295),
  ("nof_tree_events",                 7756300),
  ("nof_db_events",                   7756300),
  ("fsize_local",                     16000370341), # 16.00GB, avg file size 2.00GB
  ("fsize_db",                        386122494678), # 386.12GB, avg file size 2.49GB
  ("use_it",                          True),
  ("xsection",                        35.85),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("has_LHE",                         True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018May29_woPresel_nom_all/ntuples/ST_tW_antitop_5f_inclusiveDecays"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
  ("missing_from_superset",           [
    # not computed
  ]),
  ("missing_hlt_paths",               [

  ]),
])

samples_2017["/ST_tW_top_5f_inclusiveDecays_TuneCP5_13TeV-powheg-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "TT"),
  ("process_name_specific",           "ST_tW_top_5f_inclusiveDecays"),
  ("nof_files",                       8),
  ("nof_db_files",                    183),
  ("nof_events",                      7500242),
  ("nof_tree_events",                 7558006),
  ("nof_db_events",                   7558006),
  ("fsize_local",                     15587456243), # 15.59GB, avg file size 1.95GB
  ("fsize_db",                        376466493438), # 376.47GB, avg file size 2.06GB
  ("use_it",                          True),
  ("xsection",                        35.85),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("has_LHE",                         True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018May29_woPresel_nom_all/ntuples/ST_tW_top_5f_inclusiveDecays"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
  ("missing_from_superset",           [
    # not computed
  ]),
  ("missing_hlt_paths",               [

  ]),
])

samples_2017["/TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v2/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "TT"),
  ("process_name_specific",           "TTTo2L2Nu"),
  ("nof_files",                       9),
  ("nof_db_files",                    164),
  ("nof_events",                      8634689),
  ("nof_tree_events",                 8705576),
  ("nof_db_events",                   8705576),
  ("fsize_local",                     20469148561), # 20.47GB, avg file size 2.27GB
  ("fsize_db",                        451436194017), # 451.44GB, avg file size 2.75GB
  ("use_it",                          True),
  ("xsection",                        88.29),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("has_LHE",                         True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018May29_woPresel_nom_all/ntuples/TTTo2L2Nu"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
  ("missing_from_superset",           [
    # not computed
  ]),
  ("missing_hlt_paths",               [

  ]),
])

samples_2017["/TTTo2L2Nu_TuneCP5_PSweights_13TeV-powheg-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "TT"),
  ("process_name_specific",           "TTTo2L2Nu_PSweights"),
  ("nof_files",                       71),
  ("nof_db_files",                    1230),
  ("nof_events",                      69138136),
  ("nof_tree_events",                 69705626),
  ("nof_db_events",                   69705626),
  ("fsize_local",                     163867825564), # 163.87GB, avg file size 2.31GB
  ("fsize_db",                        3608766343800), # 3.61TB, avg file size 2.93GB
  ("use_it",                          False),
  ("xsection",                        88.29),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("has_LHE",                         True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018May29_woPresel_nom_all/ntuples/TTTo2L2Nu_PSweights"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
  ("missing_from_superset",           [
    # not computed
  ]),
  ("missing_hlt_paths",               [

  ]),
])

samples_2017["/TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "TT"),
  ("process_name_specific",           "TTToSemiLeptonic"),
  ("nof_files",                       42),
  ("nof_db_files",                    743),
  ("nof_events",                      40826968),
  ("nof_tree_events",                 41161951),
  ("nof_db_events",                   41161951),
  ("fsize_local",                     98536482380), # 98.54GB, avg file size 2.35GB
  ("fsize_db",                        2166068169129), # 2.17TB, avg file size 2.92GB
  ("use_it",                          True),
  ("xsection",                        365.34),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("has_LHE",                         True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018May29_woPresel_nom_all/ntuples/TTToSemiLeptonic"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
  ("missing_from_superset",           [
    # not computed
  ]),
  ("missing_hlt_paths",               [

  ]),
])

samples_2017["/TTToSemiLeptonic_TuneCP5_PSweights_13TeV-powheg-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "TT"),
  ("process_name_specific",           "TTToSemiLeptonic_PSweights"),
  ("nof_files",                       113),
  ("nof_db_files",                    2032),
  ("nof_events",                      110483903),
  ("nof_tree_events",                 111381888),
  ("nof_db_events",                   111381888),
  ("fsize_local",                     267061245112), # 267.06GB, avg file size 2.36GB
  ("fsize_db",                        5860979058540), # 5.86TB, avg file size 2.88GB
  ("use_it",                          False),
  ("xsection",                        365.34),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("has_LHE",                         True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018May29_woPresel_nom_all/ntuples/TTToSemiLeptonic_PSweights"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
  ("missing_from_superset",           [
    # not computed
  ]),
  ("missing_hlt_paths",               [

  ]),
])

samples_2017["/TTToHadronic_TuneCP5_13TeV-powheg-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "TT"),
  ("process_name_specific",           "TTToHadronic"),
  ("nof_files",                       43),
  ("nof_db_files",                    765),
  ("nof_events",                      42676682),
  ("nof_tree_events",                 42678688),
  ("nof_db_events",                   42678688),
  ("fsize_local",                     96661811713), # 96.66GB, avg file size 2.25GB
  ("fsize_db",                        2292321642457), # 2.29TB, avg file size 3.00GB
  ("use_it",                          True),
  ("xsection",                        377.96),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("has_LHE",                         True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018May29_woPresel_nom_all/ntuples/TTToHadronic"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
  ("missing_from_superset",           [
    # not computed
  ]),
  ("missing_hlt_paths",               [

  ]),
])

samples_2017["/TTToHadronic_TuneCP5_PSweights_13TeV-powheg-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "TT"),
  ("process_name_specific",           "TTToHadronic_PSweights"),
  ("nof_files",                       131),
  ("nof_db_files",                    2498),
  ("nof_events",                      128928313),
  ("nof_tree_events",                 129985840),
  ("nof_db_events",                   129985840),
  ("fsize_local",                     295094925668), # 295.09GB, avg file size 2.25GB
  ("fsize_db",                        6970450887587), # 6.97TB, avg file size 2.79GB
  ("use_it",                          False),
  ("xsection",                        377.96),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("has_LHE",                         True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018May29_woPresel_nom_all/ntuples/TTToHadronic_PSweights"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
  ("missing_from_superset",           [
    # not computed
  ]),
  ("missing_hlt_paths",               [

  ]),
])

samples_2017["/DYJetsToLL_M-10to50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v2/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "EWK"),
  ("process_name_specific",           "DYJetsToLL_M-10to50"),
  ("nof_files",                       40),
  ("nof_db_files",                    508),
  ("nof_events",                      38800923),
  ("nof_tree_events",                 38832197),
  ("nof_db_events",                   38832197),
  ("fsize_local",                     26779990104), # 26.78GB, avg file size 669.50MB
  ("fsize_db",                        1343136870100), # 1.34TB, avg file size 2.64GB
  ("use_it",                          True),
  ("xsection",                        18610.0),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("has_LHE",                         True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018May29_woPresel_nom_all/ntuples/DYJetsToLL_M-10to50"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
  ("missing_from_superset",           [
    # not computed
  ]),
  ("missing_hlt_paths",               [

  ]),
])

samples_2017["/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "EWK"),
  ("process_name_specific",           "DYJetsToLL_M-50"),
  ("nof_files",                       28),
  ("nof_db_files",                    372),
  ("nof_events",                      144292435),
  ("nof_tree_events",                 26923935),
  ("nof_db_events",                   26923935),
  ("fsize_local",                     35361896058), # 35.36GB, avg file size 1.26GB
  ("fsize_db",                        1065736102325), # 1.07TB, avg file size 2.86GB
  ("use_it",                          True),
  ("xsection",                        5765.4),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("has_LHE",                         True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018May29_woPresel_nom_all/ntuples/DYJetsToLL_M-50"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
  ("missing_from_superset",           [
    # not computed
  ]),
  ("missing_hlt_paths",               [

  ]),
])

samples_2017["/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10_ext1-v1/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "EWK"),
  ("process_name_specific",           "DYJetsToLL_M-50_ext1"),
  ("nof_files",                       188),
  ("nof_db_files",                    2752),
  ("nof_events",                      144292435),
  ("nof_tree_events",                 185998625),
  ("nof_db_events",                   185998625),
  ("fsize_local",                     235865862367), # 235.87GB, avg file size 1.25GB
  ("fsize_db",                        7376341087077), # 7.38TB, avg file size 2.68GB
  ("use_it",                          True),
  ("xsection",                        5765.4),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("has_LHE",                         True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018May29_woPresel_nom_all/ntuples/DYJetsToLL_M-50_ext1"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
  ("missing_from_superset",           [
    # not computed
  ]),
  ("missing_hlt_paths",               [

  ]),
])

samples_2017["/WJetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "EWK"),
  ("process_name_specific",           "WJetsToLNu"),
  ("nof_files",                       24),
  ("nof_db_files",                    382),
  ("nof_events",                      23218208),
  ("nof_tree_events",                 23240598),
  ("nof_db_events",                   23240598),
  ("fsize_local",                     22046235969), # 22.05GB, avg file size 918.59MB
  ("fsize_db",                        882645881655), # 882.65GB, avg file size 2.31GB
  ("use_it",                          True),
  ("xsection",                        61526.7),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("has_LHE",                         True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018May29_woPresel_nom_all/ntuples/WJetsToLNu"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
  ("missing_from_superset",           [
    # not computed
  ]),
  ("missing_hlt_paths",               [

  ]),
])

samples_2017["/WWTo2L2Nu_NNPDF31_TuneCP5_13TeV-powheg-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "EWK"),
  ("process_name_specific",           "WWTo2L2Nu"),
  ("nof_files",                       2),
  ("nof_db_files",                    50),
  ("nof_events",                      1811952),
  ("nof_tree_events",                 1818828),
  ("nof_db_events",                   1818828),
  ("fsize_local",                     2662193550), # 2.66GB, avg file size 1.33GB
  ("fsize_db",                        75643188117), # 75.64GB, avg file size 1.51GB
  ("use_it",                          True),
  ("xsection",                        12.178),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("has_LHE",                         True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018May29_woPresel_nom_all/ntuples/WWTo2L2Nu"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
  ("missing_from_superset",           [
    # not computed
  ]),
  ("missing_hlt_paths",               [

  ]),
])

samples_2017["/WZTo3LNu_TuneCP5_13TeV-amcatnloFXFX-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v2/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "EWK"),
  ("process_name_specific",           "WZTo3LNu"),
  ("nof_files",                       11),
  ("nof_db_files",                    212),
  ("nof_events",                      6739363),
  ("nof_tree_events",                 10751052),
  ("nof_db_events",                   10751052),
  ("fsize_local",                     16161444659), # 16.16GB, avg file size 1.47GB
  ("fsize_db",                        452807583489), # 452.81GB, avg file size 2.14GB
  ("use_it",                          True),
  ("xsection",                        4.42965),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("has_LHE",                         True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018May29_woPresel_nom_all/ntuples/WZTo3LNu"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
  ("missing_from_superset",           [
    # not computed
  ]),
  ("missing_hlt_paths",               [

  ]),
])

samples_2017["/ZZTo4L_13TeV_powheg_pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v2/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "EWK"),
  ("process_name_specific",           "ZZTo4L"),
  ("nof_files",                       8),
  ("nof_db_files",                    204),
  ("nof_events",                      101623232),
  ("nof_tree_events",                 6960289),
  ("nof_db_events",                   6960289),
  ("fsize_local",                     9500540365), # 9.50GB, avg file size 1.19GB
  ("fsize_db",                        322020515003), # 322.02GB, avg file size 1.58GB
  ("use_it",                          True),
  ("xsection",                        1.256),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("has_LHE",                         True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018May29_woPresel_nom_all/ntuples/ZZTo4L"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
  ("missing_from_superset",           [
    # not computed
  ]),
  ("missing_hlt_paths",               [

  ]),
])

samples_2017["/ZZTo4L_13TeV_powheg_pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10_ext1-v1/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "EWK"),
  ("process_name_specific",           "ZZTo4L_ext1"),
  ("nof_files",                       97),
  ("nof_db_files",                    1490),
  ("nof_events",                      101623232),
  ("nof_tree_events",                 95716759),
  ("nof_db_events",                   95716759),
  ("fsize_local",                     130772056235), # 130.77GB, avg file size 1.35GB
  ("fsize_db",                        3881682466950), # 3.88TB, avg file size 2.61GB
  ("use_it",                          True),
  ("xsection",                        1.256),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("has_LHE",                         True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018May29_woPresel_nom_all/ntuples/ZZTo4L_ext1"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
  ("missing_from_superset",           [
    # not computed
  ]),
  ("missing_hlt_paths",               [

  ]),
])

samples_2017["/TTGJets_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "Rares"),
  ("process_name_specific",           "TTGJets"),
  ("nof_files",                       5),
  ("nof_db_files",                    138),
  ("nof_events",                      1803839),
  ("nof_tree_events",                 4647278),
  ("nof_db_events",                   4647278),
  ("fsize_local",                     13152529585), # 13.15GB, avg file size 2.63GB
  ("fsize_db",                        269969335093), # 269.97GB, avg file size 1.96GB
  ("use_it",                          True),
  ("xsection",                        3.697),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("has_LHE",                         True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018May29_woPresel_nom_all/ntuples/TTGJets"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
  ("missing_from_superset",           [
    # not computed
  ]),
  ("missing_hlt_paths",               [

  ]),
])

samples_2017["/TTTT_TuneCP5_13TeV-amcatnlo-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v2/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "Rares"),
  ("process_name_specific",           "TTTT"),
  ("nof_files",                       21),
  ("nof_db_files",                    29),
  ("nof_events",                      372234),
  ("nof_tree_events",                 993804),
  ("nof_db_events",                   993804),
  ("fsize_local",                     4334964059), # 4.33GB, avg file size 206.43MB
  ("fsize_db",                        77438656415), # 77.44GB, avg file size 2.67GB
  ("use_it",                          True),
  ("xsection",                        0.008213),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("has_LHE",                         True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018May30_TTTT_woPresel_nom_all/ntuples/TTTT"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
  ("missing_from_superset",           [
    # not computed
  ]),
  ("missing_hlt_paths",               [

  ]),
])

samples_2017["/tZq_ll_4f_ckm_NLO_TuneCP5_PSweights_13TeV-amcatnlo-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "Rares"),
  ("process_name_specific",           "tZq_ll_4f"),
  ("nof_files",                       14),
  ("nof_db_files",                    292),
  ("nof_events",                      3453341),
  ("nof_tree_events",                 13220024),
  ("nof_db_events",                   13220024),
  ("fsize_local",                     35768882494), # 35.77GB, avg file size 2.55GB
  ("fsize_db",                        723683119488), # 723.68GB, avg file size 2.48GB
  ("use_it",                          True),
  ("xsection",                        0.0758),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("has_LHE",                         True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018May29_woPresel_nom_all/ntuples/tZq_ll_4f"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
  ("missing_from_superset",           [
    # not computed
  ]),
  ("missing_hlt_paths",               [

  ]),
])

samples_2017["/WWTo2L2Nu_DoubleScattering_13TeV-herwigpp/RunIIFall17MiniAOD-94X_mc2017_realistic_v11-v1/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "Rares"),
  ("process_name_specific",           "WWTo2L2Nu_DoubleScattering"),
  ("nof_files",                       2),
  ("nof_db_files",                    23),
  ("nof_events",                      999963),
  ("nof_tree_events",                 1000000),
  ("nof_db_events",                   1000000),
  ("fsize_local",                     1119737871), # 1.12GB, avg file size 559.87MB
  ("fsize_db",                        42876536279), # 42.88GB, avg file size 1.86GB
  ("use_it",                          True),
  ("xsection",                        0.1743),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("has_LHE",                         False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018May29_woPresel_nom_all/ntuples/WWTo2L2Nu_DoubleScattering"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
  ("missing_from_superset",           [
    # not computed
  ]),
  ("missing_hlt_paths",               [

  ]),
])

samples_2017["/WWW_4F_TuneCP5_13TeV-amcatnlo-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v11-v1/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "Rares"),
  ("process_name_specific",           "WWW_4F"),
  ("nof_files",                       1),
  ("nof_db_files",                    21),
  ("nof_events",                      210467),
  ("nof_tree_events",                 240000),
  ("nof_db_events",                   240000),
  ("fsize_local",                     480142139), # 480.14MB, avg file size 480.14MB
  ("fsize_db",                        11711799646), # 11.71GB, avg file size 557.70MB
  ("use_it",                          True),
  ("xsection",                        0.2086),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("has_LHE",                         True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018May29_woPresel_nom_all/ntuples/WWW_4F"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
  ("missing_from_superset",           [
    # not computed
  ]),
  ("missing_hlt_paths",               [

  ]),
])

samples_2017["/WWZ_4F_TuneCP5_13TeV-amcatnlo-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v11-v1/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "Rares"),
  ("process_name_specific",           "WWZ_4F"),
  ("nof_files",                       1),
  ("nof_db_files",                    14),
  ("nof_events",                      221573),
  ("nof_tree_events",                 250000),
  ("nof_db_events",                   250000),
  ("fsize_local",                     544234082), # 544.23MB, avg file size 544.23MB
  ("fsize_db",                        13268139304), # 13.27GB, avg file size 947.72MB
  ("use_it",                          True),
  ("xsection",                        0.1651),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("has_LHE",                         True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018May29_woPresel_nom_all/ntuples/WWZ_4F"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
  ("missing_from_superset",           [
    # not computed
  ]),
  ("missing_hlt_paths",               [

  ]),
])

samples_2017["/WZZ_TuneCP5_13TeV-amcatnlo-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v11-v1/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "Rares"),
  ("process_name_specific",           "WZZ"),
  ("nof_files",                       1),
  ("nof_db_files",                    18),
  ("nof_events",                      219657),
  ("nof_tree_events",                 250000),
  ("nof_db_events",                   250000),
  ("fsize_local",                     522864596), # 522.86MB, avg file size 522.86MB
  ("fsize_db",                        12226507693), # 12.23GB, avg file size 679.25MB
  ("use_it",                          True),
  ("xsection",                        0.05565),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("has_LHE",                         True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018May29_woPresel_nom_all/ntuples/WZZ"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
  ("missing_from_superset",           [
    # not computed
  ]),
  ("missing_hlt_paths",               [

  ]),
])

samples_2017["/ZZZ_TuneCP5_13TeV-amcatnlo-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v11-v1/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "Rares"),
  ("process_name_specific",           "ZZZ"),
  ("nof_files",                       1),
  ("nof_db_files",                    17),
  ("nof_events",                      213550),
  ("nof_tree_events",                 250000),
  ("nof_db_events",                   250000),
  ("fsize_local",                     468116793), # 468.12MB, avg file size 468.12MB
  ("fsize_db",                        11782250391), # 11.78GB, avg file size 693.07MB
  ("use_it",                          True),
  ("xsection",                        0.01398),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("has_LHE",                         True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018May29_woPresel_nom_all/ntuples/ZZZ"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
  ("missing_from_superset",           [
    # not computed
  ]),
  ("missing_hlt_paths",               [

  ]),
])

samples_2017["/THQ_4f_Hincl_13TeV_madgraph_pythia8_Fall17/private/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "tH"),
  ("process_name_specific",           "THQ"),
  ("nof_files",                       1),
  ("nof_db_files",                    9),
  ("nof_events",                      8740),
  ("nof_tree_events",                 124500),
  ("nof_db_events",                   124500),
  ("fsize_local",                     343110292), # 343.11MB, avg file size 343.11MB
  ("fsize_db",                        9518371556), # 9.52GB, avg file size 1.06GB
  ("use_it",                          True),
  ("xsection",                        0.07096),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("has_LHE",                         True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018May29_woPresel_nom_all/ntuples/THQ"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
  ("missing_from_superset",           [
    # not computed
  ]),
  ("missing_hlt_paths",               [

  ]),
])

samples_2017["/THW_5f_Hincl_13TeV_madgraph_pythia8_Fall17/private/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "tH"),
  ("process_name_specific",           "THW"),
  ("nof_files",                       1),
  ("nof_db_files",                    4),
  ("nof_events",                      5417),
  ("nof_tree_events",                 50000),
  ("nof_db_events",                   50000),
  ("fsize_local",                     167196123), # 167.20MB, avg file size 167.20MB
  ("fsize_db",                        4388282654), # 4.39GB, avg file size 1.10GB
  ("use_it",                          True),
  ("xsection",                        0.01561),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("has_LHE",                         True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018May29_woPresel_nom_all/ntuples/THW"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
  ("missing_from_superset",           [
    # not computed
  ]),
  ("missing_hlt_paths",               [

  ]),
])

samples_2017["/ST_tWll_5f_LO_TuneCP5_PSweights_13TeV_madgraph_pythia8_Fall17/private/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "TT"),
  ("process_name_specific",           "ST_tWll"),
  ("nof_files",                       1),
  ("nof_db_files",                    1),
  ("nof_events",                      12493),
  ("nof_tree_events",                 12500),
  ("nof_db_events",                   12500),
  ("fsize_local",                     37087903), # 37.09MB, avg file size 37.09MB
  ("fsize_db",                        1047598022), # 1.05GB, avg file size 1.05GB
  ("use_it",                          True),
  ("xsection",                        0.01103),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("has_LHE",                         True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018May29_woPresel_nom_all/ntuples/ST_tWll"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
  ("missing_from_superset",           [
    # not computed
  ]),
  ("missing_hlt_paths",               [

  ]),
])

samples_2017["/VHToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_Fall17/private/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "VH"),
  ("process_name_specific",           "VHToNonbb_M125"),
  ("nof_files",                       1),
  ("nof_db_files",                    12),
  ("nof_events",                      98371),
  ("nof_tree_events",                 200165),
  ("nof_db_events",                   200165),
  ("fsize_local",                     361566867), # 361.57MB, avg file size 361.57MB
  ("fsize_db",                        12634080628), # 12.63GB, avg file size 1.05GB
  ("use_it",                          True),
  ("xsection",                        0.952),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("has_LHE",                         True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018May29_woPresel_nom_all/ntuples/VHToNonbb_M125"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
  ("missing_from_superset",           [
    # not computed
  ]),
  ("missing_hlt_paths",               [

  ]),
])

samples_2017["/WpWpJJ_EWK_QCD_TuneCP5_13TeV_madgraph_pythia8_Fall17/private/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "Rares"),
  ("process_name_specific",           "WpWpJJ_EWK_QCD"),
  ("nof_files",                       1),
  ("nof_db_files",                    2),
  ("nof_events",                      24610),
  ("nof_tree_events",                 24750),
  ("nof_db_events",                   24750),
  ("fsize_local",                     65939414), # 65.94MB, avg file size 65.94MB
  ("fsize_db",                        1843708097), # 1.84GB, avg file size 921.85MB
  ("use_it",                          True),
  ("xsection",                        0.03711),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("has_LHE",                         True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018May29_woPresel_nom_all/ntuples/WpWpJJ_EWK_QCD"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
  ("missing_from_superset",           [
    # not computed
  ]),
  ("missing_hlt_paths",               [

  ]),
])

