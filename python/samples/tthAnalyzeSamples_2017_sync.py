from collections import OrderedDict as OD

# file generated at 2019-04-27 16:24:50 with the following command:
# create_dictionary.py -m python/samples/metaDict_2017_sync.py -p /hdfs/local/karl/ttHNtupleProduction/2017/2019Apr27_woPresel_nonNom_sync/ntuples/ttHJetToNonbb_M125_amcatnlo -N samples_2017 -E 2017 -o python/samples -g tthAnalyzeSamples_2017_sync.py -M

samples_2017 = OD()
samples_2017["/ttHJetToNonbb_M125_TuneCP5_13TeV_amcatnloFXFX_madspin_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v1/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "signal"),
  ("process_name_specific",           "ttHJetToNonbb_M125_amcatnlo"),
  ("nof_files",                       1),
  ("nof_db_files",                    208),
  ("nof_events",                      {
    'Count'                                  : [        65452, ],
    'CountFullWeighted'                      : [        64533,        64495,        64583, ],
    'CountWeighted'                          : [        22455,        22443,        22473, ],
    'CountFullWeightedNoPU'                  : [        64469, ],
    'CountWeightedNoPU'                      : [        22430, ],
    'CountWeightedLHEWeightScale'            : [        22906,        23311,        23703,        22808,        22455,        22179,        21395,        20690,        20108, ],
    'CountWeightedLHEWeightScaleNoPU'        : [        22893,        23302,        23696,        22779,        22430,        22157,        21361,        20658,        20079, ],
    'CountFullWeightedLHEWeightScale'        : [        65828,        66993,        68119,        65547,        64532,        63740,        61486,        59460,        57787, ],
    'CountFullWeightedLHEWeightScaleNoPU'    : [        65792,        66967,        68098,        65464,        64469,        63675,        61388,        59369,        57705, ],
  }),
  ("nof_tree_events",                 65452),
  ("nof_db_events",                   9779592),
  ("fsize_local",                     316345972), # 316.35MB, avg file size 316.35MB
  ("fsize_db",                        625507074411), # 625.51GB, avg file size 3.01GB
  ("use_it",                          True),
  ("xsection",                        0.2118),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("has_LHE",                         True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2019Apr27_woPresel_nonNom_sync/ntuples/ttHJetToNonbb_M125_amcatnlo"),
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

samples_2017["sum_events"] = [
]

