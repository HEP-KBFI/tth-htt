from collections import OrderedDict as OD

# file generated at 2019-05-20 04:07:36 with the following command:
# create_dictionary.py -m python/samples/metaDict_2016_sync.py -p /home/karl/ttHNtupleProduction/2016/2019May20_woPresel_nonNom_sync/ntuples -N samples_2016 -E 2016 -o python/samples -g tthAnalyzeSamples_2016_sync.py -M

samples_2016 = OD()
samples_2016["/ttHToNonbb_M125_TuneCUETP8M2_ttHtranche3_13TeV-powheg-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "signal"),
  ("process_name_specific",           "ttHToNonbb_M125_powheg"),
  ("nof_files",                       1),
  ("nof_db_files",                    35),
  ("nof_events",                      {
    'Count'                                            : [        77700, ],
    'CountWeighted'                                    : [        76196,        76217,        76179, ],
    'CountWeightedNoPU'                                : [        76208, ],
    'CountFullWeighted'                                : [        43715,        43720,        43702, ],
    'CountFullWeightedNoPU'                            : [        43753, ],
    'CountWeightedLHEWeightScale'                      : [        80732,        79863,        79541,        78161,        76196,        74761,        73722,        71166,        69145, ],
    'CountWeightedLHEWeightScaleNoPU'                  : [        80742,        79880,        79567,        78172,        76208,        74784,        73736,        71184,        69166, ],
    'CountFullWeightedLHEWeightScale'                  : [        46325,        45825,        45640,        44849,        43715,        42897,        42302,        40834,        39675, ],
    'CountFullWeightedLHEWeightScaleNoPU'              : [        46330,        45835,        45655,        44855,        43753,        42911,        42309,        40845,        39687, ],
    'CountWeightedL1PrefireNom'                        : [        74500,        74519,        74477, ],
    'CountWeightedL1Prefire'                           : [        74500,        74063,        74935, ],
    'CountWeightedNoPUL1PrefireNom'                    : [        74515, ],
    'CountFullWeightedL1PrefireNom'                    : [        42744,        42752,        42730, ],
    'CountFullWeightedL1Prefire'                       : [        42744,        42493,        42994, ],
    'CountFullWeightedNoPUL1PrefireNom'                : [        42770, ],
    'CountWeightedLHEWeightScaleL1PrefireNom'          : [        78871,        78049,        77758,        76398,        74500,        73120,        72084,        69606,        67647, ],
    'CountWeightedLHEWeightScaleNoPUL1PrefireNom'      : [        78882,        78066,        77784,        76411,        74515,        73143,        72099,        69624,        67669, ],
    'CountFullWeightedLHEWeightScaleL1PrefireNom'      : [        45257,        44784,        44618,        43838,        42744,        41955,        41361,        39939,        38816, ],
    'CountFullWeightedLHEWeightScaleNoPUL1PrefireNom'  : [        45262,        44794,        44632,        43845,        42770,        41969,        41370,        39950,        38828, ],
  }),
  ("nof_tree_events",                 77700),
  ("nof_db_events",                   3981250),
  ("fsize_local",                     358446577), # 358.45MB, avg file size 358.45MB
  ("fsize_db",                        208884155497), # 208.88GB, avg file size 5.97GB
  ("use_it",                          True),
  ("xsection",                        0.2118),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("has_LHE",                         True),
  ("LHE_set",                         "LHA IDs 260001 - 260100 -> NNPDF30_nlo_as_0118 PDF set, expecting 101 weights (counted 100 weights)"),
  ("local_paths",
    [
      OD([
        ("path",      "/home/karl/ttHNtupleProduction/2016/2019May20_woPresel_nonNom_sync/ntuples/ttHToNonbb_M125_powheg"),
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

