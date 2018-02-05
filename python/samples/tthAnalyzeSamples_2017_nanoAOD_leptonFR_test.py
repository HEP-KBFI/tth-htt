from collections import OrderedDict as OD

# file generated with the following command:
# ./scripts/create_dictionary.py -v -m python/samples/metaDict_2017_leptonFR_test.py -p /hdfs/cms/store/user/kaehatah/NanoAOD_2017 -Z zeroes.txt -z zombies.txt -N samples_2017 -E 2017

samples_2017 = OD()
samples_2017["/SingleMuon/Run2017E-17Nov2017-v1/MINIAOD"] = OD([
  ("type",                            "data"),
  ("sample_category",                 "data_obs"),
  ("process_name_specific",           "SingleMuon_Run2017E_17Nov2017_v1"),
  ("nof_files",                       3113),
  ("nof_events",                      143253628),
  ("nof_tree_events",                 143253628),
  ("nof_db_events",                   154630534),
  ("use_HIP_mitigation_bTag",         False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                          True),
  ("triggers",                        ['1mu']),
  ("reHLT",                           True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/kaehatah/NanoAOD_2017/SingleMuon/NanoAOD_2017_v5_SingleMuon__Run2017E-17Nov2017-v1/180130_140806"),
        ("selection", "*"),
        ("blacklist", [276,3104]),
      ]),
    ]
  ),
])

