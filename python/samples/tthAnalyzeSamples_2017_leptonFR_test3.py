from collections import OrderedDict as OD

# file generated at 2018-03-19 17:15:02 with the following command:
# create_dictionary.py -v -m python/samples/metaDict_2017.py -p /hdfs/local/ram/ttHNtupleProduction/2017/2018Mar19_wNanoPrep_wPresel_all/ntuples/SingleMuon_Run2017E_17Nov2017_v1 -f .*SingleMuon.* -Z zeroes.txt -z zombies.txt -N samples_2017 -E 2017 -o python/samples -g tthAnalyzeSamples_2017_nanoAOD_leptonFR_test3.py

samples_2017 = OD()
samples_2017["/SingleMuon/Run2017E-17Nov2017-v1/MINIAOD"] = OD([
  ("type",                            "data"),
  ("sample_category",                 "data_obs"),
  ("process_name_specific",           "SingleMuon_Run2017E_17Nov2017_v1"),
  ("nof_files",                       5),
  ("nof_db_files",                    1669),
  ("nof_events",                      529684),
  ("nof_tree_events",                 923),
  ("nof_db_events",                   154630534),
  ("fsize_local",                     1356726), # 1.36MB, avg file size 271.35kB
  ("fsize_db",                        5063603395030), # 5.06TB, avg file size 3.03GB
  ("use_HIP_mitigation_bTag",         False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                          True),
  ("triggers",                        ['1mu']),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/ram/ttHNtupleProduction/2017/2018Mar19_wNanoPrep_wPresel_all/ntuples/SingleMuon_Run2017E_17Nov2017_v1"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])

