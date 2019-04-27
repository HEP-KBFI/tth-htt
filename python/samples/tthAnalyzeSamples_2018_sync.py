from collections import OrderedDict as OD

# file generated at 2019-04-27 16:25:05 with the following command:
# create_dictionary.py -m python/samples/metaDict_2018_sync.py -p /hdfs/local/karl/ttHNtupleProduction/2018/2019Apr27_woPresel_nonNom_sync/ntuples/ttHToNonbb_M125_powheg -N samples_2018 -E 2018 -o python/samples -g tthAnalyzeSamples_2018_sync.py -M

samples_2018 = OD()
samples_2018["/ttHToNonbb_M125_TuneCP5_13TeV-powheg-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v2/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "signal"),
  ("process_name_specific",           "ttHToNonbb_M125_powheg"),
  ("nof_files",                       1),
  ("nof_db_files",                    224),
  ("nof_events",                      {
    'Count'                                  : [        63000, ],
    'CountFullWeighted'                      : [        33168,        33175,        33166, ],
    'CountWeighted'                          : [        61650,        61660,        61653, ],
    'CountFullWeightedNoPU'                  : [        33211, ],
    'CountWeightedNoPU'                      : [        61692, ],
    'CountWeightedLHEWeightScale'            : [        89698,        87068,        85055,        63175,        61650,        60527,        51746,        50384,        49345, ],
    'CountWeightedLHEWeightScaleNoPU'        : [        89754,        87106,        85075,        63230,        61692,        60555,        51788,        50414,        49367, ],
    'CountFullWeightedLHEWeightScale'        : [        48256,        46841,        45757,        33986,        33168,        32562,        27838,        27105,        26546, ],
    'CountFullWeightedLHEWeightScaleNoPU'    : [        48285,        46861,        45768,        34016,        33211,        32577,        27861,        27122,        26558, ],
  }),
  ("nof_tree_events",                 63000),
  ("nof_db_events",                   7525991),
  ("fsize_local",                     271054977), # 271.05MB, avg file size 271.05MB
  ("fsize_db",                        469867184231), # 469.87GB, avg file size 2.10GB
  ("use_it",                          True),
  ("xsection",                        0.2118),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("has_LHE",                         True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2018/2019Apr27_woPresel_nonNom_sync/ntuples/ttHToNonbb_M125_powheg"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
  ("missing_from_superset",           [
    # not computed
  ]),
  ("missing_hlt_paths",               [
    "HLT_DoubleMediumChargedIsoPFTau40_Trk1_TightID_eta2p1_Reg",
    "HLT_DoubleTightChargedIsoPFTau35_Trk1_TightID_eta2p1_Reg",
    "HLT_DoubleTightChargedIsoPFTau40_Trk1_eta2p1_Reg",
    "HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTau30_eta2p1_CrossL1",
    "HLT_IsoMu20_eta2p1_LooseChargedIsoPFTau27_eta2p1_CrossL1",
  ]),
  ("hlt_paths",               [
    # not computed
  ]),
])

samples_2018["sum_events"] = [
]

