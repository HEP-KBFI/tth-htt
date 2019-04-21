from collections import OrderedDict as OD

# file generated at 2019-04-21 14:37:48 with the following command:
# create_dictionary.py -m python/samples/metaDict_2016_sync.py -p /hdfs/local/karl/ttHNtupleProduction/2016/2019Apr21_woPresel_nonNom_sync/ntuples/ttHToNonbb_M125_powheg -N samples_2016 -E 2016 -o python/samples -g tthAnalyzeSamples_2016_sync.py -M

samples_2016 = OD()
samples_2016["/ttHToNonbb_M125_TuneCUETP8M2_ttHtranche3_13TeV-powheg-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "signal"),
  ("process_name_specific",           "ttHToNonbb_M125_powheg"),
  ("nof_files",                       1),
  ("nof_db_files",                    35),
  ("nof_events",                      {
    'Count'                                  : [        77700, ],
    'CountFullWeighted'                      : [        43715,        43720,        43702, ],
    'CountWeighted'                          : [        76196,        76217,        76179, ],
    'CountFullWeightedNoPU'                  : [        43753, ],
    'CountWeightedNoPU'                      : [        76208, ],
    'CountWeightedLHEWeightScale'            : [        80732,        79863,        79541,        78161,        76196,        74761,        73722,        71166,        69145, ],
    'CountWeightedLHEWeightScaleNoPU'        : [        80742,        79880,        79567,        78172,        76208,        74784,        73736,        71184,        69166, ],
    'CountFullWeightedLHEWeightScale'        : [        46325,        45825,        45640,        44849,        43715,        42897,        42302,        40834,        39675, ],
    'CountFullWeightedLHEWeightScaleNoPU'    : [        46330,        45835,        45655,        44855,        43753,        42911,        42309,        40845,        39687, ],
  }),
  ("nof_tree_events",                 77700),
  ("nof_db_events",                   3981250),
  ("fsize_local",                     373145797), # 373.15MB, avg file size 373.15MB
  ("fsize_db",                        208884155497), # 208.88GB, avg file size 5.97GB
  ("use_it",                          True),
  ("xsection",                        0.2118),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("has_LHE",                         True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2016/2019Apr21_woPresel_nonNom_sync/ntuples/ttHToNonbb_M125_powheg"),
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
  ("hlt_paths",               [
    # not computed
  ]),
])

samples_2016["sum_events"] = [
]

