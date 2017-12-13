from collections import OrderedDict as OD

# file generated with the following command:
# ./scripts/create_dictionary.py -v -m python/metaDict_2017_test.py -p /hdfs/local/karl/nanoAOD_postprocessed -Z zeroes.txt -z zombies.txt -N samples_2017 -E 2017

samples_2017 = OD()
samples_2017["/ttHToNonbb_M125_TuneCUETP8M2_13TeV-powheg-pythia8/RunIISummer17MiniAOD-NZSFlatPU28to62_92X_upgrade2017_realistic_v10-v1/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "signal"),
  ("process_name_specific",           "ttHToNonbb_M125"),
  ("nof_files",                       1),
  ("nof_events",                      2539),
  ("nof_tree_events",                 8096),
  ("nof_db_events",                   3999999),
  ("use_HIP_mitigation_bTag",         False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                          True),
  ("xsection",                        0.2151),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("reHLT",                           True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/nanoAOD_postprocessed/92X_upgrade2017_realistic_v10_ext1-v1/ttHToNonbb_M125"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])

