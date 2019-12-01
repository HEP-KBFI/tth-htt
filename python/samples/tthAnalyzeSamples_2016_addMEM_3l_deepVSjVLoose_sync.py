from collections import OrderedDict as OD

# file generated at 2019-12-01 10:07:36 with the following command:
# create_dictionary.py -m python/samples/metaDict_2016_sync.py -p /hdfs/local/karl/addMEM/2016/2019Nov30_sync_nonNom/final_ntuples/3l -N samples_2016 -E 2016 -o python/samples -g tthAnalyzeSamples_2016_addMEM_3l_deepVSjVLoose_sync.py -M

samples_2016 = OD()
samples_2016["/ttHToNonbb_M125_TuneCUETP8M2_ttHtranche3_13TeV-powheg-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "ttH"),
  ("process_name_specific",           "ttHToNonbb_M125_powheg"),
  ("nof_files",                       1),
  ("nof_db_files",                    35),
  ("nof_events",                      {
    'Count'                                                      : [        77700, ],
    'CountWeighted'                                              : [        76196,        76217,        76179, ],
    'CountWeightedLHEWeightScale'                                : [        80732,        79863,        79541,        78161,        76196,        74761,        73722,        71166,        69145, ],
    'CountWeightedL1PrefireNom'                                  : [        74500,        74519,        74477, ],
    'CountWeightedL1Prefire'                                     : [        74500,        74063,        74935, ],
    'CountWeightedLHEWeightScaleL1PrefireNom'                    : [        78871,        78049,        77758,        76398,        74500,        73120,        72084,        69606,        67647, ],
  }),
  ("nof_tree_events",                 16264),
  ("nof_db_events",                   3981250),
  ("fsize_local",                     179740064), # 179.74MB, avg file size 179.74MB
  ("fsize_db",                        208884155497), # 208.88GB, avg file size 5.97GB
  ("use_it",                          True),
  ("xsection",                        0.2118),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("has_LHE",                         True),
  ("LHE_set",                         "LHA IDs 260001 - 260100 -> NNPDF30_nlo_as_0118 PDF set, expecting 101 weights (counted 100 weights)"),
  ("nof_reweighting",                 0),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/addMEM/2016/2019Nov30_sync_nonNom/final_ntuples/3l/ttHToNonbb_M125_powheg"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
  ("missing_completely",           [
    # not computed
  ]),
  ("missing_from_superset",        [
    # not computed
  ]),
  ("missing_hlt_paths",            [

  ]),
  ("hlt_paths",                    [
    # not computed
  ]),
])

samples_2016["sum_events"] = [
]

