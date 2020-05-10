from collections import OrderedDict as OD

# file generated at 2020-05-10 12:39:44 with the following command:
# create_dictionary.py -m python/samples/metaDict_2018_sync.py -p /hdfs/local/karl/ttHNtupleProduction/2018/2020May10_wPresel_nonNom_sync/ntuples -N samples_2018 -E 2018 -o python/samples -g tthAnalyzeSamples_2018_preselected_sync.py -M

samples_2018 = OD()
samples_2018["/ttHToNonbb_M125_TuneCP5_13TeV-powheg-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v2/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "ttH"),
  ("process_name_specific",           "ttHToNonbb_M125_powheg"),
  ("nof_files",                       1),
  ("nof_db_files",                    224),
  ("nof_events",                      {
    'Count'                                                                          : [        63000, ],
    'CountWeighted'                                                                  : [        61655,        61672,        61641, ],
    'CountWeightedLHEWeightScale'                                                    : [        89708,        87079,        85066,        63180,        61655,        60535,        51752,        50390,        49352, ],
    'CountWeightedLHEEnvelope'                                                       : [        90845,        48638, ],
    'Count_fwd'                                                                      : [          952, ],
    'CountWeighted_fwd'                                                              : [          939,          934,          944, ],
    'CountWeightedLHEWeightScale_fwd'                                                : [         1339,         1289,         1251,          971,          939,          914,          797,          769,          747, ],
    'CountWeightedLHEEnvelope_fwd'                                                   : [         1348,          742, ],
    'Count_pt0to60'                                                                  : [        14788, ],
    'CountWeighted_pt0to60'                                                          : [        14540,        14553,        14524, ],
    'CountWeightedLHEWeightScale_pt0to60'                                            : [        21202,        20642,        20229,        14863,        14540,        14314,        12190,        11897,        11682, ],
    'CountWeightedLHEEnvelope_pt0to60'                                               : [        21510,        11508, ],
    'Count_pt60to120'                                                                : [        22285, ],
    'CountWeighted_pt60to120'                                                        : [        21956,        21945,        21968, ],
    'CountWeightedLHEWeightScale_pt60to120'                                          : [        31936,        31054,        30390,        22467,        21956,        21590,        18411,        17953,        17610, ],
    'CountWeightedLHEEnvelope_pt60to120'                                             : [        32370,        17354, ],
    'Count_pt120to200'                                                               : [        15608, ],
    'CountWeighted_pt120to200'                                                       : [        15263,        15277,        15245, ],
    'CountWeightedLHEWeightScale_pt120to200'                                         : [        22202,        21538,        21021,        15643,        15263,        14979,        12814,        12473,        12212, ],
    'CountWeightedLHEEnvelope_pt120to200'                                            : [        22462,        12036, ],
    'Count_pt200to300'                                                               : [         6386, ],
    'CountWeighted_pt200to300'                                                       : [         6235,         6217,         6255, ],
    'CountWeightedLHEWeightScale_pt200to300'                                         : [         9061,         8735,         8475,         6430,         6235,         6081,         5257,         5086,         4950, ],
    'CountWeightedLHEEnvelope_pt200to300'                                            : [         9151,         4882, ],
    'Count_ptGt300'                                                                  : [         2981, ],
    'CountWeighted_ptGt300'                                                          : [         2725,         2737,         2712, ],
    'CountWeightedLHEWeightScale_ptGt300'                                            : [         3968,         3822,         3700,         2807,         2725,         2656,         2283,         2211,         2150, ],
    'CountWeightedLHEEnvelope_ptGt300'                                               : [         4004,         2117, ],
    'Count_pt300to450'                                                               : [         2266, ],
    'CountWeighted_pt300to450'                                                       : [         2104,         2114,         2094, ],
    'CountWeightedLHEWeightScale_pt300to450'                                         : [         3056,         2945,         2853,         2168,         2104,         2052,         1766,         1711,         1664, ],
    'CountWeightedLHEEnvelope_pt300to450'                                            : [         3083,         1641, ],
    'Count_ptGt450'                                                                  : [          715, ],
    'CountWeighted_ptGt450'                                                          : [          621,          623,          618, ],
    'CountWeightedLHEWeightScale_ptGt450'                                            : [          912,          877,          847,          639,          621,          604,          516,          501,          486, ],
    'CountWeightedLHEEnvelope_ptGt450'                                               : [          921,          476, ],
  }),
  ("nof_tree_events",                 13723),
  ("nof_db_events",                   7525991),
  ("fsize_local",                     79564924), # 79.56MB, avg file size 79.56MB
  ("fsize_db",                        469867184231), # 469.87GB, avg file size 2.10GB
  ("use_it",                          True),
  ("xsection",                        0.2118),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("has_LHE",                         True),
  ("nof_PSweights",                   1),
  ("LHE_set",                         "LHA IDs 91400 - 91432 -> PDF4LHC15_nnlo_30_pdfas PDF set, expecting 33 weights (counted 33 weights)"),
  ("nof_reweighting",                 0),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2018/2020May10_wPresel_nonNom_sync/ntuples/ttHToNonbb_M125_powheg"),
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

samples_2018["sum_events"] = [
]

