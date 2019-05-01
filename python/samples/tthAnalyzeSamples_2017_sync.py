from collections import OrderedDict as OD

# file generated at 2019-05-01 19:35:10 with the following command:
# create_dictionary.py -m python/samples/metaDict_2017_sync.py -p /hdfs/local/karl/ttHNtupleProduction/2017/2019May01_woPresel_nonNom_sync/ntuples/ttHJetToNonbb_M125_amcatnlo -N samples_2017 -E 2017 -o python/samples -g tthAnalyzeSamples_2017_sync.py -M

samples_2017 = OD()
samples_2017["/ttHJetToNonbb_M125_TuneCP5_13TeV_amcatnloFXFX_madspin_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v1/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "signal"),
  ("process_name_specific",           "ttHJetToNonbb_M125_amcatnlo"),
  ("nof_files",                       1),
  ("nof_db_files",                    208),
  ("nof_events",                      {
    'Count'                                            : [        65452, ],
    'CountWeighted'                                    : [        22455,        22443,        22473, ],
    'CountWeightedNoPU'                                : [        22430, ],
    'CountFullWeighted'                                : [        64533,        64495,        64583, ],
    'CountFullWeightedNoPU'                            : [        64469, ],
    'CountWeightedLHEWeightScale'                      : [        22906,        23311,        23703,        22808,        22455,        22179,        21395,        20690,        20108, ],
    'CountWeightedLHEWeightScaleNoPU'                  : [        22893,        23302,        23696,        22780,        22430,        22157,        21361,        20658,        20080, ],
    'CountFullWeightedLHEWeightScale'                  : [        65828,        66993,        68119,        65547,        64532,        63740,        61486,        59460,        57787, ],
    'CountFullWeightedLHEWeightScaleNoPU'              : [        65792,        66967,        68098,        65464,        64469,        63675,        61388,        59369,        57705, ],
    'CountWeightedL1PrefireNom'                        : [        21660,        21648,        21670, ],
    'CountWeightedL1Prefire'                           : [        21660,        21467,        21848, ],
    'CountWeightedNoPUL1PrefireNom'                    : [        21629, ],
    'CountFullWeightedL1PrefireNom'                    : [        62247,        62210,        62276, ],
    'CountFullWeightedL1Prefire'                       : [        62247,        61693,        62787, ],
    'CountFullWeightedNoPUL1PrefireNom'                : [        62164, ],
    'CountWeightedLHEWeightScaleL1PrefireNom'          : [        22052,        22464,        22862,        21981,        21659,        21409,        20633,        19969,        19421, ],
    'CountWeightedLHEWeightScaleNoPUL1PrefireNom'      : [        22035,        22449,        22848,        21948,        21629,        21381,        20595,        19933,        19388, ],
    'CountFullWeightedLHEWeightScaleL1PrefireNom'      : [        63375,        64559,        65703,        63170,        62246,        61527,        59295,        57387,        55813, ],
    'CountFullWeightedLHEWeightScaleNoPUL1PrefireNom'  : [        63326,        64515,        65661,        63076,        62163,        61446,        59187,        57284,        55717, ],
  }),
  ("nof_tree_events",                 65452),
  ("nof_db_events",                   9779592),
  ("fsize_local",                     303286668), # 303.29MB, avg file size 303.29MB
  ("fsize_db",                        625507074411), # 625.51GB, avg file size 3.01GB
  ("use_it",                          True),
  ("xsection",                        0.2118),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("has_LHE",                         True),
  ("LHE_set",                         "LHA IDs 91400 - 91432 -> PDF4LHC15_nnlo_30_pdfas PDF set, expecting 33 weights (counted 33 weights)"),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2019May01_woPresel_nonNom_sync/ntuples/ttHJetToNonbb_M125_amcatnlo"),
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

