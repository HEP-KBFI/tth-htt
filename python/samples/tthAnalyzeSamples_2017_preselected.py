from collections import OrderedDict as OD

# file generated at 2018-06-08 10:39:27 with the following command:
# create_dictionary.py -m python/samples/metaDict_2017.py -p /hdfs/local/karl/ttHNtupleProduction/2017/2018Jun07_wPresel_nom_all/ntuples -Z zeroes.txt -z zombies.txt -N samples_2017 -E 2017 -g tthAnalyzeSamples_2017_preselected.py -o python/samples -M

samples_2017 = OD()
samples_2017["/SingleElectron/Run2017B-17Nov2017-v1/MINIAOD"] = OD([
  ("type",                            "data"),
  ("sample_category",                 "data_obs"),
  ("process_name_specific",           "SingleElectron_Run2017B_17Nov2017_v1"),
  ("nof_files",                       2),
  ("nof_db_files",                    634),
  ("nof_events",                      56501671),
  ("nof_tree_events",                 12555),
  ("nof_db_events",                   60537490),
  ("fsize_local",                     11372843), # 11.37MB, avg file size 5.69MB
  ("fsize_db",                        1839129571740), # 1.84TB, avg file size 2.90GB
  ("use_it",                          True),
  ("triggers",                        ['1e']),
  ("has_LHE",                         False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018Jun07_wPresel_nom_all/ntuples/SingleElectron_Run2017B_17Nov2017_v1"),
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
    "HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8",
    "HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL",
    "HLT_Mu3_PFJet40",
  ]),
])

samples_2017["/SingleElectron/Run2017C-17Nov2017-v1/MINIAOD"] = OD([
  ("type",                            "data"),
  ("sample_category",                 "data_obs"),
  ("process_name_specific",           "SingleElectron_Run2017C_17Nov2017_v1"),
  ("nof_files",                       3),
  ("nof_db_files",                    1705),
  ("nof_events",                      127361536),
  ("nof_tree_events",                 30936),
  ("nof_db_events",                   136637888),
  ("fsize_local",                     28564628), # 28.56MB, avg file size 9.52MB
  ("fsize_db",                        4293152220674), # 4.29TB, avg file size 2.52GB
  ("use_it",                          True),
  ("triggers",                        ['1e']),
  ("has_LHE",                         False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018Jun07_wPresel_nom_all/ntuples/SingleElectron_Run2017C_17Nov2017_v1"),
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
  ("nof_files",                       2),
  ("nof_db_files",                    693),
  ("nof_events",                      50610322),
  ("nof_tree_events",                 14484),
  ("nof_db_events",                   51526710),
  ("fsize_local",                     13581299), # 13.58MB, avg file size 6.79MB
  ("fsize_db",                        1584079997402), # 1.58TB, avg file size 2.29GB
  ("use_it",                          True),
  ("triggers",                        ['1e']),
  ("has_LHE",                         False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018Jun07_wPresel_nom_all/ntuples/SingleElectron_Run2017D_17Nov2017_v1"),
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
  ("nof_files",                       3),
  ("nof_db_files",                    1280),
  ("nof_events",                      100205123),
  ("nof_tree_events",                 30882),
  ("nof_db_events",                   102121689),
  ("fsize_local",                     29411863), # 29.41MB, avg file size 9.80MB
  ("fsize_db",                        3608372444378), # 3.61TB, avg file size 2.82GB
  ("use_it",                          True),
  ("triggers",                        ['1e']),
  ("has_LHE",                         False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018Jun07_wPresel_nom_all/ntuples/SingleElectron_Run2017E_17Nov2017_v1"),
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
  ("nof_files",                       3),
  ("nof_db_files",                    1583),
  ("nof_events",                      126059586),
  ("nof_tree_events",                 38808),
  ("nof_db_events",                   128467223),
  ("fsize_local",                     37596175), # 37.60MB, avg file size 12.53MB
  ("fsize_db",                        4628019555901), # 4.63TB, avg file size 2.92GB
  ("use_it",                          True),
  ("triggers",                        ['1e']),
  ("has_LHE",                         False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018Jun07_wPresel_nom_all/ntuples/SingleElectron_Run2017F_17Nov2017_v1"),
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
  ("nof_files",                       3),
  ("nof_db_files",                    1146),
  ("nof_events",                      128496866),
  ("nof_tree_events",                 22872),
  ("nof_db_events",                   136300266),
  ("fsize_local",                     19285802), # 19.29MB, avg file size 6.43MB
  ("fsize_db",                        3681903942053), # 3.68TB, avg file size 3.21GB
  ("use_it",                          True),
  ("triggers",                        ['1mu']),
  ("has_LHE",                         False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018Jun07_wPresel_nom_all/ntuples/SingleMuon_Run2017B_17Nov2017_v1"),
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
    "HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8",
    "HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL",
    "HLT_Mu3_PFJet40",
  ]),
])

samples_2017["/SingleMuon/Run2017C-17Nov2017-v1/MINIAOD"] = OD([
  ("type",                            "data"),
  ("sample_category",                 "data_obs"),
  ("process_name_specific",           "SingleMuon_Run2017C_17Nov2017_v1"),
  ("nof_files",                       4),
  ("nof_db_files",                    1511),
  ("nof_events",                      154633543),
  ("nof_tree_events",                 45076),
  ("nof_db_events",                   165652756),
  ("fsize_local",                     39101096), # 39.10MB, avg file size 9.78MB
  ("fsize_db",                        4719988428330), # 4.72TB, avg file size 3.12GB
  ("use_it",                          True),
  ("triggers",                        ['1mu']),
  ("has_LHE",                         False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018Jun07_wPresel_nom_all/ntuples/SingleMuon_Run2017C_17Nov2017_v1"),
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

samples_2017["/SingleMuon/Run2017D-17Nov2017-v1/MINIAOD"] = OD([
  ("type",                            "data"),
  ("sample_category",                 "data_obs"),
  ("process_name_specific",           "SingleMuon_Run2017D_17Nov2017_v1"),
  ("nof_files",                       2),
  ("nof_db_files",                    823),
  ("nof_events",                      69031076),
  ("nof_tree_events",                 20864),
  ("nof_db_events",                   70361660),
  ("fsize_local",                     18196035), # 18.20MB, avg file size 9.10MB
  ("fsize_db",                        2004044655656), # 2.00TB, avg file size 2.44GB
  ("use_it",                          True),
  ("triggers",                        ['1mu']),
  ("has_LHE",                         False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018Jun07_wPresel_nom_all/ntuples/SingleMuon_Run2017D_17Nov2017_v1"),
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
  ("nof_files",                       4),
  ("nof_db_files",                    1669),
  ("nof_events",                      151713908),
  ("nof_tree_events",                 47284),
  ("nof_db_events",                   154630534),
  ("fsize_local",                     42883764), # 42.88MB, avg file size 10.72MB
  ("fsize_db",                        5063603395030), # 5.06TB, avg file size 3.03GB
  ("use_it",                          True),
  ("triggers",                        ['1mu']),
  ("has_LHE",                         False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018Jun07_wPresel_nom_all/ntuples/SingleMuon_Run2017E_17Nov2017_v1"),
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
  ("nof_files",                       5),
  ("nof_db_files",                    2737),
  ("nof_events",                      235942680),
  ("nof_tree_events",                 67527),
  ("nof_db_events",                   242140980),
  ("fsize_local",                     60671427), # 60.67MB, avg file size 12.13MB
  ("fsize_db",                        8025096282975), # 8.03TB, avg file size 2.93GB
  ("use_it",                          True),
  ("triggers",                        ['1mu']),
  ("has_LHE",                         False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018Jun07_wPresel_nom_all/ntuples/SingleMuon_Run2017F_17Nov2017_v1"),
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
  ("nof_files",                       2),
  ("nof_db_files",                    759),
  ("nof_events",                      54125899),
  ("nof_tree_events",                 6924),
  ("nof_db_events",                   58088760),
  ("fsize_local",                     6228080), # 6.23MB, avg file size 3.11MB
  ("fsize_db",                        2000582502159), # 2.00TB, avg file size 2.64GB
  ("use_it",                          True),
  ("triggers",                        ['2e', '3e']),
  ("has_LHE",                         False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018Jun07_wPresel_nom_all/ntuples/DoubleEG_Run2017B_17Nov2017_v1"),
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
    "HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8",
    "HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL",
    "HLT_Mu3_PFJet40",
  ]),
])

samples_2017["/DoubleEG/Run2017C-17Nov2017-v1/MINIAOD"] = OD([
  ("type",                            "data"),
  ("sample_category",                 "data_obs"),
  ("process_name_specific",           "DoubleEG_Run2017C_17Nov2017_v1"),
  ("nof_files",                       2),
  ("nof_db_files",                    847),
  ("nof_events",                      60063438),
  ("nof_tree_events",                 15040),
  ("nof_db_events",                   65181125),
  ("fsize_local",                     13385868), # 13.39MB, avg file size 6.69MB
  ("fsize_db",                        2252815090346), # 2.25TB, avg file size 2.66GB
  ("use_it",                          True),
  ("triggers",                        ['2e', '3e']),
  ("has_LHE",                         False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018Jun07_wPresel_nom_all/ntuples/DoubleEG_Run2017C_17Nov2017_v1"),
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

samples_2017["/DoubleEG/Run2017D-17Nov2017-v1/MINIAOD"] = OD([
  ("type",                            "data"),
  ("sample_category",                 "data_obs"),
  ("process_name_specific",           "DoubleEG_Run2017D_17Nov2017_v1"),
  ("nof_files",                       1),
  ("nof_db_files",                    344),
  ("nof_events",                      25209986),
  ("nof_tree_events",                 7108),
  ("nof_db_events",                   25911432),
  ("fsize_local",                     6402319), # 6.40MB, avg file size 6.40MB
  ("fsize_db",                        881576196022), # 881.58GB, avg file size 2.56GB
  ("use_it",                          True),
  ("triggers",                        ['2e', '3e']),
  ("has_LHE",                         False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018Jun07_wPresel_nom_all/ntuples/DoubleEG_Run2017D_17Nov2017_v1"),
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
  ("nof_files",                       2),
  ("nof_db_files",                    639),
  ("nof_events",                      54624312),
  ("nof_tree_events",                 15192),
  ("nof_db_events",                   56235775),
  ("fsize_local",                     13960478), # 13.96MB, avg file size 6.98MB
  ("fsize_db",                        2140362591723), # 2.14TB, avg file size 3.35GB
  ("use_it",                          True),
  ("triggers",                        ['2e', '3e']),
  ("has_LHE",                         False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018Jun07_wPresel_nom_all/ntuples/DoubleEG_Run2017E_17Nov2017_v1"),
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
  ("nof_files",                       2),
  ("nof_db_files",                    1024),
  ("nof_events",                      72430492),
  ("nof_tree_events",                 18877),
  ("nof_db_events",                   74344288),
  ("fsize_local",                     17643652), # 17.64MB, avg file size 8.82MB
  ("fsize_db",                        2879805741948), # 2.88TB, avg file size 2.81GB
  ("use_it",                          True),
  ("triggers",                        ['2e', '3e']),
  ("has_LHE",                         False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018Jun07_wPresel_nom_all/ntuples/DoubleEG_Run2017F_17Nov2017_v1"),
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
  ("nof_files",                       1),
  ("nof_db_files",                    164),
  ("nof_events",                      13572040),
  ("nof_tree_events",                 10845),
  ("nof_db_events",                   14501767),
  ("fsize_local",                     8420904), # 8.42MB, avg file size 8.42MB
  ("fsize_db",                        429564397133), # 429.56GB, avg file size 2.62GB
  ("use_it",                          True),
  ("triggers",                        ['2mu', '3mu']),
  ("has_LHE",                         False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018Jun07_wPresel_nom_all/ntuples/DoubleMuon_Run2017B_17Nov2017_v1"),
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
    "HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8",
    "HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL",
    "HLT_Mu3_PFJet40",
  ]),
])

samples_2017["/DoubleMuon/Run2017C-17Nov2017-v1/MINIAOD"] = OD([
  ("type",                            "data"),
  ("sample_category",                 "data_obs"),
  ("process_name_specific",           "DoubleMuon_Run2017C_17Nov2017_v1"),
  ("nof_files",                       1),
  ("nof_db_files",                    466),
  ("nof_events",                      46273112),
  ("nof_tree_events",                 25901),
  ("nof_db_events",                   49636525),
  ("fsize_local",                     21317245), # 21.32MB, avg file size 21.32MB
  ("fsize_db",                        1506932771681), # 1.51TB, avg file size 3.23GB
  ("use_it",                          True),
  ("triggers",                        ['2mu', '3mu']),
  ("has_LHE",                         False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018Jun07_wPresel_nom_all/ntuples/DoubleMuon_Run2017C_17Nov2017_v1"),
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

samples_2017["/DoubleMuon/Run2017D-17Nov2017-v1/MINIAOD"] = OD([
  ("type",                            "data"),
  ("sample_category",                 "data_obs"),
  ("process_name_specific",           "DoubleMuon_Run2017D_17Nov2017_v1"),
  ("nof_files",                       1),
  ("nof_db_files",                    242),
  ("nof_events",                      22646080),
  ("nof_tree_events",                 12413),
  ("nof_db_events",                   23075733),
  ("fsize_local",                     10326270), # 10.33MB, avg file size 10.33MB
  ("fsize_db",                        700300808389), # 700.30GB, avg file size 2.89GB
  ("use_it",                          True),
  ("triggers",                        ['2mu', '3mu']),
  ("has_LHE",                         False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018Jun07_wPresel_nom_all/ntuples/DoubleMuon_Run2017D_17Nov2017_v1"),
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
  ("nof_files",                       2),
  ("nof_db_files",                    596),
  ("nof_events",                      50596542),
  ("nof_tree_events",                 28292),
  ("nof_db_events",                   51589091),
  ("fsize_local",                     23896518), # 23.90MB, avg file size 11.95MB
  ("fsize_db",                        1822288632364), # 1.82TB, avg file size 3.06GB
  ("use_it",                          True),
  ("triggers",                        ['2mu', '3mu']),
  ("has_LHE",                         False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018Jun07_wPresel_nom_all/ntuples/DoubleMuon_Run2017E_17Nov2017_v1"),
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
  ("nof_files",                       2),
  ("nof_db_files",                    875),
  ("nof_events",                      75300870),
  ("nof_tree_events",                 38381),
  ("nof_db_events",                   79756560),
  ("fsize_local",                     33019615), # 33.02MB, avg file size 16.51MB
  ("fsize_db",                        2792396630929), # 2.79TB, avg file size 3.19GB
  ("use_it",                          True),
  ("triggers",                        ['2mu', '3mu']),
  ("has_LHE",                         False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018Jun07_wPresel_nom_all/ntuples/DoubleMuon_Run2017F_17Nov2017_v1"),
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
  ("nof_files",                       1),
  ("nof_db_files",                    70),
  ("nof_events",                      4153318),
  ("nof_tree_events",                 6891),
  ("nof_db_events",                   4453465),
  ("fsize_local",                     6475001), # 6.48MB, avg file size 6.48MB
  ("fsize_db",                        151955610304), # 151.96GB, avg file size 2.17GB
  ("use_it",                          True),
  ("triggers",                        ['1e1mu', '2e1mu', '1e2mu']),
  ("has_LHE",                         False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018Jun07_wPresel_nom_all/ntuples/MuonEG_Run2017B_17Nov2017_v1"),
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
    "HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8",
    "HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL",
    "HLT_Mu3_PFJet40",
  ]),
])

samples_2017["/MuonEG/Run2017C-17Nov2017-v1/MINIAOD"] = OD([
  ("type",                            "data"),
  ("sample_category",                 "data_obs"),
  ("process_name_specific",           "MuonEG_Run2017C_17Nov2017_v1"),
  ("nof_files",                       1),
  ("nof_db_files",                    219),
  ("nof_events",                      14579589),
  ("nof_tree_events",                 17764),
  ("nof_db_events",                   15595214),
  ("fsize_local",                     17097879), # 17.10MB, avg file size 17.10MB
  ("fsize_db",                        548775705076), # 548.78GB, avg file size 2.51GB
  ("use_it",                          True),
  ("triggers",                        ['1e1mu', '2e1mu', '1e2mu']),
  ("has_LHE",                         False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018Jun07_wPresel_nom_all/ntuples/MuonEG_Run2017C_17Nov2017_v1"),
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

samples_2017["/MuonEG/Run2017D-17Nov2017-v1/MINIAOD"] = OD([
  ("type",                            "data"),
  ("sample_category",                 "data_obs"),
  ("process_name_specific",           "MuonEG_Run2017D_17Nov2017_v1"),
  ("nof_files",                       1),
  ("nof_db_files",                    126),
  ("nof_events",                      9012928),
  ("nof_tree_events",                 9048),
  ("nof_db_events",                   9164365),
  ("fsize_local",                     8838281), # 8.84MB, avg file size 8.84MB
  ("fsize_db",                        321530133689), # 321.53GB, avg file size 2.55GB
  ("use_it",                          True),
  ("triggers",                        ['1e1mu', '2e1mu', '1e2mu']),
  ("has_LHE",                         False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018Jun07_wPresel_nom_all/ntuples/MuonEG_Run2017D_17Nov2017_v1"),
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
  ("nof_files",                       1),
  ("nof_db_files",                    239),
  ("nof_events",                      18703364),
  ("nof_tree_events",                 18928),
  ("nof_db_events",                   19043421),
  ("fsize_local",                     18687246), # 18.69MB, avg file size 18.69MB
  ("fsize_db",                        753395415338), # 753.40GB, avg file size 3.15GB
  ("use_it",                          True),
  ("triggers",                        ['1e1mu', '2e1mu', '1e2mu']),
  ("has_LHE",                         False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018Jun07_wPresel_nom_all/ntuples/MuonEG_Run2017E_17Nov2017_v1"),
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
  ("nof_files",                       1),
  ("nof_db_files",                    362),
  ("nof_events",                      25342216),
  ("nof_tree_events",                 24632),
  ("nof_db_events",                   25776363),
  ("fsize_local",                     24753463), # 24.75MB, avg file size 24.75MB
  ("fsize_db",                        1031887580033), # 1.03TB, avg file size 2.85GB
  ("use_it",                          True),
  ("triggers",                        ['1e1mu', '2e1mu', '1e2mu']),
  ("has_LHE",                         False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018Jun07_wPresel_nom_all/ntuples/MuonEG_Run2017F_17Nov2017_v1"),
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
  ("nof_files",                       1),
  ("nof_db_files",                    283),
  ("nof_events",                      3321918),
  ("nof_tree_events",                 412835),
  ("nof_db_events",                   9650032),
  ("fsize_local",                     1430056113), # 1.43GB, avg file size 1.43GB
  ("fsize_db",                        603282930374), # 603.28GB, avg file size 2.13GB
  ("use_it",                          True),
  ("xsection",                        0.2118),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("has_LHE",                         True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018Jun07_wPresel_nom_all/ntuples/ttHJetToNonbb_M125_amcatnlo"),
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
  ("nof_files",                       1),
  ("nof_db_files",                    219),
  ("nof_events",                      7522034),
  ("nof_tree_events",                 321137),
  ("nof_db_events",                   7669336),
  ("fsize_local",                     1135511779), # 1.14GB, avg file size 1.14GB
  ("fsize_db",                        465938496839), # 465.94GB, avg file size 2.13GB
  ("use_it",                          False),
  ("xsection",                        0.2118),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("has_LHE",                         True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018Jun07_wPresel_nom_all/ntuples/ttHToNonbb_M125_powheg"),
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
  ("nof_files",                       1),
  ("nof_db_files",                    259),
  ("nof_events",                      3408993),
  ("nof_tree_events",                 134822),
  ("nof_db_events",                   9911561),
  ("fsize_local",                     441088979), # 441.09MB, avg file size 441.09MB
  ("fsize_db",                        626042445493), # 626.04GB, avg file size 2.42GB
  ("use_it",                          False),
  ("xsection",                        0.2953),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("has_LHE",                         True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018Jun07_wPresel_nom_all/ntuples/ttHJetTobb_M125_amcatnlo"),
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
  ("nof_files",                       1),
  ("nof_db_files",                    47),
  ("nof_events",                      924557),
  ("nof_tree_events",                 5791),
  ("nof_db_events",                   934244),
  ("fsize_local",                     14136593), # 14.14MB, avg file size 14.14MB
  ("fsize_db",                        42622664498), # 42.62GB, avg file size 906.87MB
  ("use_it",                          True),
  ("xsection",                        0.01212),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("has_LHE",                         True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018Jun07_wPresel_nom_all/ntuples/GluGluHToZZTo4L"),
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
  ("nof_files",                       1),
  ("nof_db_files",                    199),
  ("nof_events",                      3570881),
  ("nof_tree_events",                 424572),
  ("nof_db_events",                   7563490),
  ("fsize_local",                     1428912125), # 1.43GB, avg file size 1.43GB
  ("fsize_db",                        444833969271), # 444.83GB, avg file size 2.24GB
  ("use_it",                          True),
  ("xsection",                        0.2529),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("has_LHE",                         True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018Jun07_wPresel_nom_all/ntuples/TTZToLL_M10"),
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
  ("nof_tree_events",                 5715),
  ("nof_db_events",                   250000),
  ("fsize_local",                     18399689), # 18.40MB, avg file size 18.40MB
  ("fsize_db",                        14727460148), # 14.73GB, avg file size 866.32MB
  ("use_it",                          True),
  ("xsection",                        0.0493),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("has_LHE",                         True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018Jun07_wPresel_nom_all/ntuples/TTZToLL_M-1to10"),
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
  ("nof_files",                       1),
  ("nof_db_files",                    109),
  ("nof_events",                      5353357),
  ("nof_tree_events",                 218321),
  ("nof_db_events",                   4925829),
  ("fsize_local",                     689259008), # 689.26MB, avg file size 689.26MB
  ("fsize_db",                        292280765632), # 292.28GB, avg file size 2.68GB
  ("use_it",                          True),
  ("xsection",                        0.2043),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("has_LHE",                         True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018Jun07_wPresel_nom_all/ntuples/TTWJetsToLNu"),
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
  ("nof_files",                       1),
  ("nof_db_files",                    122),
  ("nof_events",                      5353357),
  ("nof_tree_events",                 212309),
  ("nof_db_events",                   4889942),
  ("fsize_local",                     668039598), # 668.04MB, avg file size 668.04MB
  ("fsize_db",                        290787551975), # 290.79GB, avg file size 2.38GB
  ("use_it",                          True),
  ("xsection",                        0.2043),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("has_LHE",                         True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018Jun07_wPresel_nom_all/ntuples/TTWJetsToLNu_PSweights"),
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
  ("nof_tree_events",                 10631),
  ("nof_db_events",                   200000),
  ("fsize_local",                     38081361), # 38.08MB, avg file size 38.08MB
  ("fsize_db",                        13111885203), # 13.11GB, avg file size 1.19GB
  ("use_it",                          True),
  ("xsection",                        0.007834),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("has_LHE",                         True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018Jun07_wPresel_nom_all/ntuples/TTWW"),
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
  ("nof_files",                       1),
  ("nof_db_files",                    217),
  ("nof_events",                      5912237),
  ("nof_tree_events",                 12037),
  ("nof_db_events",                   9472619),
  ("fsize_local",                     26982129), # 26.98MB, avg file size 26.98MB
  ("fsize_db",                        423862017407), # 423.86GB, avg file size 1.95GB
  ("use_it",                          True),
  ("xsection",                        3.36),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("has_LHE",                         True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018Jun07_wPresel_nom_all/ntuples/ST_s-channel_4f_leptonDecays"),
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
  ("nof_files",                       1),
  ("nof_db_files",                    116),
  ("nof_events",                      3891275),
  ("nof_tree_events",                 1725),
  ("nof_db_events",                   3891190),
  ("fsize_local",                     4133589), # 4.13MB, avg file size 4.13MB
  ("fsize_db",                        177784436788), # 177.78GB, avg file size 1.53GB
  ("use_it",                          True),
  ("xsection",                        80.95),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("has_LHE",                         True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018Jun07_wPresel_nom_all/ntuples/ST_t-channel_antitop_4f_inclusiveDecays"),
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
  ("nof_files",                       1),
  ("nof_db_files",                    186),
  ("nof_events",                      5841441),
  ("nof_tree_events",                 2228),
  ("nof_db_events",                   5841455),
  ("fsize_local",                     5312690), # 5.31MB, avg file size 5.31MB
  ("fsize_db",                        268058212482), # 268.06GB, avg file size 1.44GB
  ("use_it",                          True),
  ("xsection",                        136.02),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("has_LHE",                         True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018Jun07_wPresel_nom_all/ntuples/ST_t-channel_top_4f_inclusiveDecays"),
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
  ("nof_files",                       1),
  ("nof_db_files",                    155),
  ("nof_events",                      7697295),
  ("nof_tree_events",                 33717),
  ("nof_db_events",                   7756300),
  ("fsize_local",                     79419113), # 79.42MB, avg file size 79.42MB
  ("fsize_db",                        386122494678), # 386.12GB, avg file size 2.49GB
  ("use_it",                          True),
  ("xsection",                        35.85),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("has_LHE",                         True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018Jun07_wPresel_nom_all/ntuples/ST_tW_antitop_5f_inclusiveDecays"),
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
  ("nof_files",                       1),
  ("nof_db_files",                    183),
  ("nof_events",                      7500243),
  ("nof_tree_events",                 32727),
  ("nof_db_events",                   7558006),
  ("fsize_local",                     77005299), # 77.01MB, avg file size 77.01MB
  ("fsize_db",                        376466493438), # 376.47GB, avg file size 2.06GB
  ("use_it",                          True),
  ("xsection",                        35.85),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("has_LHE",                         True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018Jun07_wPresel_nom_all/ntuples/ST_tW_top_5f_inclusiveDecays"),
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
  ("nof_files",                       1),
  ("nof_db_files",                    164),
  ("nof_events",                      77772824),
  ("nof_tree_events",                 303381),
  ("nof_db_events",                   8705576),
  ("fsize_local",                     760023823), # 760.02MB, avg file size 760.02MB
  ("fsize_db",                        451436194017), # 451.44GB, avg file size 2.75GB
  ("use_it",                          True),
  ("xsection",                        88.29),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("has_LHE",                         True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018Jun07_wPresel_nom_all/ntuples/TTTo2L2Nu"),
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
  ("nof_files",                       2),
  ("nof_db_files",                    1230),
  ("nof_events",                      77772824),
  ("nof_tree_events",                 2428111),
  ("nof_db_events",                   69705626),
  ("fsize_local",                     6070006627), # 6.07GB, avg file size 3.04GB
  ("fsize_db",                        3608766343800), # 3.61TB, avg file size 2.93GB
  ("use_it",                          True),
  ("xsection",                        88.29),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("has_LHE",                         True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018Jun07_wPresel_nom_all/ntuples/TTTo2L2Nu_PSweights"),
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
  ("nof_files",                       1),
  ("nof_db_files",                    743),
  ("nof_events",                      151310872),
  ("nof_tree_events",                 305372),
  ("nof_db_events",                   41161951),
  ("fsize_local",                     783500219), # 783.50MB, avg file size 783.50MB
  ("fsize_db",                        2166068169129), # 2.17TB, avg file size 2.92GB
  ("use_it",                          True),
  ("xsection",                        365.34),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("has_LHE",                         True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018Jun07_wPresel_nom_all/ntuples/TTToSemiLeptonic"),
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
  ("nof_files",                       3),
  ("nof_db_files",                    2032),
  ("nof_events",                      151310872),
  ("nof_tree_events",                 826900),
  ("nof_db_events",                   111381888),
  ("fsize_local",                     2121664595), # 2.12GB, avg file size 707.22MB
  ("fsize_db",                        5860979058540), # 5.86TB, avg file size 2.88GB
  ("use_it",                          True),
  ("xsection",                        365.34),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("has_LHE",                         True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018Jun07_wPresel_nom_all/ntuples/TTToSemiLeptonic_PSweights"),
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
  ("nof_files",                       1),
  ("nof_db_files",                    765),
  ("nof_events",                      171604996),
  ("nof_tree_events",                 2288),
  ("nof_db_events",                   42678688),
  ("fsize_local",                     6343702), # 6.34MB, avg file size 6.34MB
  ("fsize_db",                        2292321642457), # 2.29TB, avg file size 3.00GB
  ("use_it",                          True),
  ("xsection",                        377.96),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("has_LHE",                         True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018Jun07_wPresel_nom_all/ntuples/TTToHadronic"),
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
  ("nof_files",                       3),
  ("nof_db_files",                    2498),
  ("nof_events",                      171604996),
  ("nof_tree_events",                 7068),
  ("nof_db_events",                   129985840),
  ("fsize_local",                     19595541), # 19.60MB, avg file size 6.53MB
  ("fsize_db",                        6970450887587), # 6.97TB, avg file size 2.79GB
  ("use_it",                          True),
  ("xsection",                        377.96),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("has_LHE",                         True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018Jun07_wPresel_nom_all/ntuples/TTToHadronic_PSweights"),
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
  ("nof_files",                       1),
  ("nof_db_files",                    508),
  ("nof_events",                      38800916),
  ("nof_tree_events",                 504),
  ("nof_db_events",                   38832197),
  ("fsize_local",                     1185890), # 1.19MB, avg file size 1.19MB
  ("fsize_db",                        1343136870100), # 1.34TB, avg file size 2.64GB
  ("use_it",                          True),
  ("xsection",                        18610.0),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("has_LHE",                         True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018Jun07_wPresel_nom_all/ntuples/DYJetsToLL_M-10to50"),
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
  ("nof_files",                       1),
  ("nof_db_files",                    372),
  ("nof_events",                      144292430),
  ("nof_tree_events",                 22669),
  ("nof_db_events",                   26923935),
  ("fsize_local",                     44624408), # 44.62MB, avg file size 44.62MB
  ("fsize_db",                        1065736102325), # 1.07TB, avg file size 2.86GB
  ("use_it",                          True),
  ("xsection",                        5765.4),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("has_LHE",                         True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018Jun07_wPresel_nom_all/ntuples/DYJetsToLL_M-50"),
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
  ("nof_files",                       4),
  ("nof_db_files",                    2752),
  ("nof_events",                      144292430),
  ("nof_tree_events",                 154217),
  ("nof_db_events",                   185998625),
  ("fsize_local",                     298455608), # 298.46MB, avg file size 74.61MB
  ("fsize_db",                        7376341087077), # 7.38TB, avg file size 2.68GB
  ("use_it",                          True),
  ("xsection",                        5765.4),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("has_LHE",                         True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018Jun07_wPresel_nom_all/ntuples/DYJetsToLL_M-50_ext1"),
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
  ("nof_files",                       1),
  ("nof_db_files",                    382),
  ("nof_events",                      23218208),
  ("nof_tree_events",                 194),
  ("nof_db_events",                   23240598),
  ("fsize_local",                     674791), # 674.79kB, avg file size 674.79kB
  ("fsize_db",                        882645881655), # 882.65GB, avg file size 2.31GB
  ("use_it",                          True),
  ("xsection",                        61526.7),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("has_LHE",                         True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018Jun07_wPresel_nom_all/ntuples/WJetsToLNu"),
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
  ("nof_files",                       1),
  ("nof_db_files",                    50),
  ("nof_events",                      1811952),
  ("nof_tree_events",                 1058),
  ("nof_db_events",                   1818828),
  ("fsize_local",                     2679960), # 2.68MB, avg file size 2.68MB
  ("fsize_db",                        75643188117), # 75.64GB, avg file size 1.51GB
  ("use_it",                          True),
  ("xsection",                        12.178),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("has_LHE",                         True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018Jun07_wPresel_nom_all/ntuples/WWTo2L2Nu"),
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
  ("nof_files",                       1),
  ("nof_db_files",                    212),
  ("nof_events",                      6739363),
  ("nof_tree_events",                 45073),
  ("nof_db_events",                   10751052),
  ("fsize_local",                     107723868), # 107.72MB, avg file size 107.72MB
  ("fsize_db",                        452807583489), # 452.81GB, avg file size 2.14GB
  ("use_it",                          True),
  ("xsection",                        4.42965),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("has_LHE",                         True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018Jun07_wPresel_nom_all/ntuples/WZTo3LNu"),
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
  ("nof_files",                       1),
  ("nof_db_files",                    204),
  ("nof_events",                      101623238),
  ("nof_tree_events",                 25915),
  ("nof_db_events",                   6960289),
  ("fsize_local",                     59530621), # 59.53MB, avg file size 59.53MB
  ("fsize_db",                        322020515003), # 322.02GB, avg file size 1.58GB
  ("use_it",                          True),
  ("xsection",                        1.256),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("has_LHE",                         True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018Jun07_wPresel_nom_all/ntuples/ZZTo4L"),
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
  ("nof_files",                       2),
  ("nof_db_files",                    1490),
  ("nof_events",                      101623238),
  ("nof_tree_events",                 359500),
  ("nof_db_events",                   95716759),
  ("fsize_local",                     808916701), # 808.92MB, avg file size 404.46MB
  ("fsize_db",                        3881682466950), # 3.88TB, avg file size 2.61GB
  ("use_it",                          True),
  ("xsection",                        1.256),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("has_LHE",                         True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018Jun07_wPresel_nom_all/ntuples/ZZTo4L_ext1"),
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
  ("nof_files",                       1),
  ("nof_db_files",                    138),
  ("nof_events",                      1803839),
  ("nof_tree_events",                 41827),
  ("nof_db_events",                   4647278),
  ("fsize_local",                     124650492), # 124.65MB, avg file size 124.65MB
  ("fsize_db",                        269969335093), # 269.97GB, avg file size 1.96GB
  ("use_it",                          True),
  ("xsection",                        3.697),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("has_LHE",                         True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018Jun07_wPresel_nom_all/ntuples/TTGJets"),
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
  ("nof_files",                       1),
  ("nof_db_files",                    29),
  ("nof_events",                      372234),
  ("nof_tree_events",                 68942),
  ("nof_db_events",                   993804),
  ("fsize_local",                     300582841), # 300.58MB, avg file size 300.58MB
  ("fsize_db",                        77438656415), # 77.44GB, avg file size 2.67GB
  ("use_it",                          True),
  ("xsection",                        0.008213),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("has_LHE",                         True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018Jun07_wPresel_nom_all/ntuples/TTTT"),
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
  ("nof_files",                       1),
  ("nof_db_files",                    292),
  ("nof_events",                      3453342),
  ("nof_tree_events",                 851434),
  ("nof_db_events",                   13220024),
  ("fsize_local",                     2445206911), # 2.45GB, avg file size 2.45GB
  ("fsize_db",                        723683119488), # 723.68GB, avg file size 2.48GB
  ("use_it",                          True),
  ("xsection",                        0.0758),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("has_LHE",                         True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018Jun07_wPresel_nom_all/ntuples/tZq_ll_4f"),
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
  ("nof_files",                       1),
  ("nof_db_files",                    23),
  ("nof_events",                      999963),
  ("nof_tree_events",                 346),
  ("nof_db_events",                   1000000),
  ("fsize_local",                     883937), # 883.94kB, avg file size 883.94kB
  ("fsize_db",                        42876536279), # 42.88GB, avg file size 1.86GB
  ("use_it",                          True),
  ("xsection",                        0.1743),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("has_LHE",                         False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018Jun07_wPresel_nom_all/ntuples/WWTo2L2Nu_DoubleScattering"),
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
  ("nof_tree_events",                 701),
  ("nof_db_events",                   240000),
  ("fsize_local",                     2043809), # 2.04MB, avg file size 2.04MB
  ("fsize_db",                        11711799646), # 11.71GB, avg file size 557.70MB
  ("use_it",                          True),
  ("xsection",                        0.2086),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("has_LHE",                         True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018Jun07_wPresel_nom_all/ntuples/WWW_4F"),
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
  ("nof_tree_events",                 1160),
  ("nof_db_events",                   250000),
  ("fsize_local",                     3537646), # 3.54MB, avg file size 3.54MB
  ("fsize_db",                        13268139304), # 13.27GB, avg file size 947.72MB
  ("use_it",                          True),
  ("xsection",                        0.1651),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("has_LHE",                         True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018Jun07_wPresel_nom_all/ntuples/WWZ_4F"),
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
  ("nof_tree_events",                 1567),
  ("nof_db_events",                   250000),
  ("fsize_local",                     4646422), # 4.65MB, avg file size 4.65MB
  ("fsize_db",                        12226507693), # 12.23GB, avg file size 679.25MB
  ("use_it",                          True),
  ("xsection",                        0.05565),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("has_LHE",                         True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018Jun07_wPresel_nom_all/ntuples/WZZ"),
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
  ("nof_tree_events",                 2097),
  ("nof_db_events",                   250000),
  ("fsize_local",                     5641955), # 5.64MB, avg file size 5.64MB
  ("fsize_db",                        11782250391), # 11.78GB, avg file size 693.07MB
  ("use_it",                          True),
  ("xsection",                        0.01398),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("has_LHE",                         True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018Jun07_wPresel_nom_all/ntuples/ZZZ"),
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
  ("nof_tree_events",                 1021),
  ("nof_db_events",                   124500),
  ("fsize_local",                     3531770), # 3.53MB, avg file size 3.53MB
  ("fsize_db",                        9518371556), # 9.52GB, avg file size 1.06GB
  ("use_it",                          True),
  ("xsection",                        0.07096),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("has_LHE",                         True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018Jun07_wPresel_nom_all/ntuples/THQ"),
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
  ("nof_tree_events",                 1226),
  ("nof_db_events",                   50000),
  ("fsize_local",                     4608389), # 4.61MB, avg file size 4.61MB
  ("fsize_db",                        4388282654), # 4.39GB, avg file size 1.10GB
  ("use_it",                          True),
  ("xsection",                        0.01561),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("has_LHE",                         True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018Jun07_wPresel_nom_all/ntuples/THW"),
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
  ("nof_tree_events",                 1506),
  ("nof_db_events",                   12500),
  ("fsize_local",                     4737471), # 4.74MB, avg file size 4.74MB
  ("fsize_db",                        1047598022), # 1.05GB, avg file size 1.05GB
  ("use_it",                          True),
  ("xsection",                        0.01103),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("has_LHE",                         True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018Jun07_wPresel_nom_all/ntuples/ST_tWll"),
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
  ("nof_tree_events",                 555),
  ("nof_db_events",                   200165),
  ("fsize_local",                     1658059), # 1.66MB, avg file size 1.66MB
  ("fsize_db",                        12634080628), # 12.63GB, avg file size 1.05GB
  ("use_it",                          True),
  ("xsection",                        0.952),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("has_LHE",                         True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018Jun07_wPresel_nom_all/ntuples/VHToNonbb_M125"),
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
  ("nof_tree_events",                 115),
  ("nof_db_events",                   24750),
  ("fsize_local",                     594527), # 594.53kB, avg file size 594.53kB
  ("fsize_db",                        1843708097), # 1.84GB, avg file size 921.85MB
  ("use_it",                          True),
  ("xsection",                        0.03711),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("has_LHE",                         True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018Jun07_wPresel_nom_all/ntuples/WpWpJJ_EWK_QCD"),
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

