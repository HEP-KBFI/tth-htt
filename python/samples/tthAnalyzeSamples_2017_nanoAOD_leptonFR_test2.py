from collections import OrderedDict as OD

# file generated with the following command:
# ./scripts/create_dictionary.py -v -m python/samples/metaDict_2017_leptonFR_test2.py -p /hdfs/local/karl/nanoAODproduction -Z zeroes.txt -z zombies.txt -N samples_2017 -E 2017

samples_2017 = OD()
samples_2017["/SingleElectron/Run2017E-17Nov2017-v1/MINIAOD"] = OD([
  ("type",                            "data"),
  ("sample_category",                 "data_obs"),
  ("process_name_specific",           "SingleElectron_Run2017E_17Nov2017_v1"),
  ("nof_files",                       20),
  ("nof_events",                      1995560),
  ("nof_tree_events",                 1995560),
  ("nof_db_events",                   154630534),
  ("use_HIP_mitigation_bTag",         False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                          True),
  ("triggers",                        ['1e']),
  ("reHLT",                           True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/nanoAODproduction/SingleElectron_Run2017E_17Nov2017_v1"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])

