from collections import OrderedDict as OD

# file generated at 2020-05-10 12:38:26 with the following command:
# create_dictionary.py -m python/samples/metaDict_2016_sync.py -p /hdfs/local/karl/ttHNtupleProduction/2016/2020May10_wPresel_nonNom_sync/ntuples -N samples_2016 -E 2016 -o python/samples -g tthAnalyzeSamples_2016_preselected_sync.py -M

samples_2016 = OD()
samples_2016["/ttHToNonbb_M125_TuneCUETP8M2_ttHtranche3_13TeV-powheg-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "ttH"),
  ("process_name_specific",           "ttHToNonbb_M125_powheg"),
  ("nof_files",                       1),
  ("nof_db_files",                    35),
  ("nof_events",                      {
    'Count'                                                                          : [        77700, ],
    'CountWeighted'                                                                  : [        76222,        76224,        76201, ],
    'CountWeightedLHEWeightScale'                                                    : [        80750,        79880,        79560,        78178,        76222,        74779,        73739,        71182,        69162, ],
    'CountWeightedLHEEnvelope'                                                       : [        88399,        63494, ],
    'CountWeightedL1PrefireNom'                                                      : [        74520,        74527,        74503, ],
    'CountWeightedL1Prefire'                                                         : [        74520,        74083,        74956, ],
    'CountWeightedLHEWeightScaleL1PrefireNom'                                        : [        78888,        78065,        77776,        76415,        74520,        73137,        72099,        69621,        67664, ],
    'CountWeightedLHEEnvelopeL1PrefireNom'                                           : [        86380,        62114, ],
    'Count_fwd'                                                                      : [         1086, ],
    'CountWeighted_fwd'                                                              : [         1067,         1063,         1070, ],
    'CountWeightedLHEWeightScale_fwd'                                                : [         1083,         1079,         1081,         1095,         1067,         1048,         1059,         1018,          987, ],
    'CountWeightedLHEEnvelope_fwd'                                                   : [         1214,          879, ],
    'CountWeightedL1PrefireNom_fwd'                                                  : [          979,          976,          982, ],
    'CountWeightedL1Prefire_fwd'                                                     : [          979,          958,         1001, ],
    'CountWeightedLHEWeightScaleL1PrefireNom_fwd'                                    : [          993,          989,          992,         1005,          979,          962,          972,          935,          907, ],
    'CountWeightedLHEEnvelopeL1PrefireNom_fwd'                                       : [         1114,          807, ],
    'Count_pt0to60'                                                                  : [        17948, ],
    'CountWeighted_pt0to60'                                                          : [        17692,        17702,        17685, ],
    'CountWeightedLHEWeightScale_pt0to60'                                            : [        18712,        18534,        18509,        18090,        17692,        17425,        17042,        16520,        16117, ],
    'CountWeightedLHEEnvelope_pt0to60'                                               : [        20464,        14868, ],
    'CountWeightedL1PrefireNom_pt0to60'                                              : [        17350,        17361,        17342, ],
    'CountWeightedL1Prefire_pt0to60'                                                 : [        17350,        17260,        17440, ],
    'CountWeightedLHEWeightScaleL1PrefireNom_pt0to60'                                : [        18341,        18170,        18149,        17737,        17350,        17091,        16712,        16205,        15812, ],
    'CountWeightedLHEEnvelopeL1PrefireNom_pt0to60'                                   : [        20057,        14590, ],
    'Count_pt60to120'                                                                : [        27127, ],
    'CountWeighted_pt60to120'                                                        : [        26706,        26714,        26694, ],
    'CountWeightedLHEWeightScale_pt60to120'                                          : [        28261,        28019,        27974,        27324,        26706,        26269,        25729,        24910,        24270, ],
    'CountWeightedLHEEnvelope_pt60to120'                                             : [        30906,        22365, ],
    'CountWeightedL1PrefireNom_pt60to120'                                            : [        26160,        26171,        26149, ],
    'CountWeightedL1Prefire_pt60to120'                                               : [        26160,        26017,        26302, ],
    'CountWeightedLHEWeightScaleL1PrefireNom_pt60to120'                              : [        27664,        27434,        27397,        26759,        26160,        25739,        25205,        24409,        23787, ],
    'CountWeightedLHEEnvelopeL1PrefireNom_pt60to120'                                 : [        30261,        21916, ],
    'Count_pt120to200'                                                               : [        19368, ],
    'CountWeighted_pt120to200'                                                       : [        19031,        19004,        19052, ],
    'CountWeightedLHEWeightScale_pt120to200'                                         : [        20198,        19955,        19840,        19557,        19031,        18642,        18449,        17778,        17245, ],
    'CountWeightedLHEEnvelope_pt120to200'                                            : [        22090,        15826, ],
    'CountWeightedL1PrefireNom_pt120to200'                                           : [        18608,        18580,        18631, ],
    'CountWeightedL1Prefire_pt120to200'                                              : [        18608,        18500,        18716, ],
    'CountWeightedLHEWeightScaleL1PrefireNom_pt120to200'                             : [        19730,        19501,        19395,        19116,        18608,        18233,        18040,        17389,        16873, ],
    'CountWeightedLHEEnvelopeL1PrefireNom_pt120to200'                                : [        21586,        15482, ],
    'Count_pt200to300'                                                               : [         8261, ],
    'CountWeighted_pt200to300'                                                       : [         8032,         8031,         8033, ],
    'CountWeightedLHEWeightScale_pt200to300'                                         : [         8543,         8427,         8355,         8282,         8032,         7837,         7832,         7511,         7250, ],
    'CountWeightedLHEEnvelope_pt200to300'                                            : [         9387,         6577, ],
    'CountWeightedL1PrefireNom_pt200to300'                                           : [         7828,         7829,         7828, ],
    'CountWeightedL1Prefire_pt200to300'                                              : [         7828,         7778,         7879, ],
    'CountWeightedLHEWeightScaleL1PrefireNom_pt200to300'                             : [         8315,         8207,         8141,         8068,         7828,         7641,         7634,         7324,         7072, ],
    'CountWeightedLHEEnvelopeL1PrefireNom_pt200to300'                                : [         9141,         6414, ],
    'Count_ptGt300'                                                                  : [         3910, ],
    'CountWeighted_ptGt300'                                                          : [         3681,         3699,         3663, ],
    'CountWeightedLHEWeightScale_ptGt300'                                            : [         3953,         3868,         3802,         3831,         3681,         3559,         3629,         3445,         3294, ],
    'CountWeightedLHEEnvelope_ptGt300'                                               : [         4337,         2978, ],
    'CountWeightedL1PrefireNom_ptGt300'                                              : [         3587,         3604,         3569, ],
    'CountWeightedL1Prefire_ptGt300'                                                 : [         3587,         3564,         3611, ],
    'CountWeightedLHEWeightScaleL1PrefireNom_ptGt300'                                : [         3844,         3764,         3703,         3730,         3587,         3470,         3536,         3359,         3213, ],
    'CountWeightedLHEEnvelopeL1PrefireNom_ptGt300'                                   : [         4221,         2904, ],
    'Count_pt300to450'                                                               : [         3004, ],
    'CountWeighted_pt300to450'                                                       : [         2868,         2886,         2849, ],
    'CountWeightedLHEWeightScale_pt300to450'                                         : [         3099,         3024,         2969,         2987,         2868,         2772,         2819,         2676,         2560, ],
    'CountWeightedLHEEnvelope_pt300to450'                                            : [         3389,         2323, ],
    'CountWeightedL1PrefireNom_pt300to450'                                           : [         2794,         2812,         2775, ],
    'CountWeightedL1Prefire_pt300to450'                                              : [         2794,         2775,         2812, ],
    'CountWeightedLHEWeightScaleL1PrefireNom_pt300to450'                             : [         3012,         2942,         2891,         2907,         2794,         2702,         2746,         2609,         2497, ],
    'CountWeightedLHEEnvelopeL1PrefireNom_pt300to450'                                : [         3298,         2264, ],
    'Count_ptGt450'                                                                  : [          906, ],
    'CountWeighted_ptGt450'                                                          : [          814,          813,          813, ],
    'CountWeightedLHEWeightScale_ptGt450'                                            : [          854,          843,          833,          844,          814,          787,          810,          769,          734, ],
    'CountWeightedLHEEnvelope_ptGt450'                                               : [          948,          655, ],
    'CountWeightedL1PrefireNom_ptGt450'                                              : [          794,          793,          794, ],
    'CountWeightedL1Prefire_ptGt450'                                                 : [          794,          789,          798, ],
    'CountWeightedLHEWeightScaleL1PrefireNom_ptGt450'                                : [          832,          822,          812,          823,          794,          768,          790,          750,          717, ],
    'CountWeightedLHEEnvelopeL1PrefireNom_ptGt450'                                   : [          923,          640, ],
  }),
  ("nof_tree_events",                 16293),
  ("nof_db_events",                   3981250),
  ("fsize_local",                     98172305), # 98.17MB, avg file size 98.17MB
  ("fsize_db",                        208884155497), # 208.88GB, avg file size 5.97GB
  ("use_it",                          True),
  ("xsection",                        0.2118),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("has_LHE",                         True),
  ("nof_PSweights",                   1),
  ("LHE_set",                         "LHA IDs 260001 - 260100 -> NNPDF30_nlo_as_0118 PDF set, expecting 101 weights (counted 100 weights)"),
  ("nof_reweighting",                 0),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2016/2020May10_wPresel_nonNom_sync/ntuples/ttHToNonbb_M125_powheg"),
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

