from collections import OrderedDict as OD

# file generated with the following command:
# /home/karl/CMSSW_9_4_4/bin/slc6_amd64_gcc630/create_dictionary.py -v -m python/samples/metaDict_2017_leptonFR_test.py -p /hdfs/local/karl/ttHNtupleProduction/2017/2018Feb05_wNanoPrep_woPresel_all/ntuples -Z zeroes.txt -z zombies.txt -N samples_2017 -E 2017

samples_2017 = OD()
samples_2017["/SingleMuon/Run2017E-17Nov2017-v1/MINIAOD"] = OD([
  ("type",                            "data"),
  ("sample_category",                 "data_obs"),
  ("process_name_specific",           "SingleMuon_Run2017E_17Nov2017_v1"),
  ("nof_files",                       63),
  ("nof_events",                      151622764),
  ("nof_tree_events",                 151166473),
  ("nof_db_events",                   154630534),
  ("use_HIP_mitigation_bTag",         False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                          True),
  ("triggers",                        ['1mu']),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018Feb05_wNanoPrep_woPresel_all/ntuples/SingleMuon_Run2017E_17Nov2017_v1"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])

