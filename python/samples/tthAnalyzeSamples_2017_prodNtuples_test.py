from collections import OrderedDict as OD

# file generated with the following command:
# /home/karl/CMSSW_9_4_0/bin/slc6_amd64_gcc630/create_dictionary.py -v -m python/samples/metaDict_2017_test.py -p /hdfs/local/karl/ttHNtupleProduction/2017/2017Dec20_wNanoPrep_woPresel_all/ntuples -Z zeroes.txt -z zombies.txt -N samples_2017 -E 2017

samples_2017 = OD()
samples_2017["/ttHToNonbb_M125_TuneCUETP8M2_13TeV-powheg-pythia8/RunIISummer17MiniAOD-NZSFlatPU28to62_92X_upgrade2017_realistic_v10-v1/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "signal"),
  ("process_name_specific",           "ttHToNonbb_M125"),
  ("nof_files",                       1),
  ("nof_events",                      13385),
  ("nof_tree_events",                 7657),
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
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2017Dec20_wNanoPrep_woPresel_all/ntuples/ttHToNonbb_M125"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])

samples_2017["/TT_TuneCUETP8M2T4_13TeV-powheg-pythia8/RunIISummer17MiniAOD-92X_upgrade2017_realistic_v10_ext1-v1/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "TT"),
  ("process_name_specific",           "TT"),
  ("nof_files",                       1),
  ("nof_events",                      14069),
  ("nof_tree_events",                 9569),
  ("nof_db_events",                   33844772),
  ("use_HIP_mitigation_bTag",         False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                          True),
  ("xsection",                        182.18),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("reHLT",                           True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2017Dec20_wNanoPrep_woPresel_all/ntuples/TT"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])

