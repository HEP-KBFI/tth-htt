from collections import OrderedDict as OD

# file generated at 2020-10-24 22:37:09 with the following command:
# create_dictionary.py -m python/samples/metaDict_2018_sync.py -p /hdfs/local/karl/ttHNtupleProduction/2018/2020Oct24_wPresel_nonNom_tth_sync/ntuples -N samples_2018 -E 2018 -o python/samples -g tthAnalyzeSamples_2018_preselected_sync.py -M

samples_2018 = OD()
samples_2018["/ttHToNonbb_M125_TuneCP5_13TeV-powheg-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v2/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "ttH"),
  ("process_name_specific",           "ttHToNonbb_M125_powheg"),
  ("nof_files",                       1),
  ("nof_db_files",                    224),
  ("nof_events",                      {
    'Count'                                                                          : [ 63000, ],
    'CountWeighted'                                                                  : [ 6.16550039e+04, 6.16721719e+04, 6.16409766e+04, ],
    'CountWeightedLHEWeightScale'                                                    : [ 8.97077031e+04, 8.70789844e+04, 8.50663203e+04, 6.31800820e+04, 6.16550039e+04, 6.05346953e+04, 5.17520078e+04, 5.03899219e+04, 4.93522227e+04, ],
    'CountWeightedLHEEnvelope'                                                       : [ 9.08448594e+04, 4.86382617e+04, ],
    'CountWeightedFull'                                                              : [ 3.31697422e+04, 3.31749844e+04, 3.31615977e+04, ],
    'CountWeightedFullLHEWeightScale'                                                : [ 4.82600938e+04, 4.68459531e+04, 4.57633672e+04, 3.39892109e+04, 3.31697422e+04, 3.25661992e+04, 2.78409805e+04, 2.71084766e+04, 2.65502188e+04, ],
    'CountWeightedFullLHEEnvelope'                                                   : [ 4.88720156e+04, 2.61659805e+04, ],
  }),
  ("nof_tree_events",                 13723),
  ("nof_db_events",                   7525991),
  ("fsize_local",                     79233577), # 79.23MB, avg file size 79.23MB
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
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2018/2020Oct24_wPresel_nonNom_tth_sync/ntuples/ttHToNonbb_M125_powheg"),
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

