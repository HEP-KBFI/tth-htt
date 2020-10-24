from collections import OrderedDict as OD

# file generated at 2020-10-24 22:28:37 with the following command:
# create_dictionary.py -m python/samples/metaDict_2016_sync.py -p /hdfs/local/karl/ttHNtupleProduction/2016/2020Oct24_wPresel_nonNom_tth_sync/ntuples -N samples_2016 -E 2016 -o python/samples -g tthAnalyzeSamples_2016_preselected_sync.py -M

samples_2016 = OD()
samples_2016["/ttHToNonbb_M125_TuneCUETP8M2_ttHtranche3_13TeV-powheg-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "ttH"),
  ("process_name_specific",           "ttHToNonbb_M125_powheg"),
  ("nof_files",                       1),
  ("nof_db_files",                    35),
  ("nof_events",                      {
    'Count'                                                                          : [ 77700, ],
    'CountWeighted'                                                                  : [ 7.62215938e+04, 7.62243594e+04, 7.62014922e+04, ],
    'CountWeightedLHEWeightScale'                                                    : [ 8.07497578e+04, 7.98802734e+04, 7.95600234e+04, 7.81780938e+04, 7.62215938e+04, 7.47790703e+04, 7.37387266e+04, 7.11818828e+04, 6.91620547e+04, ],
    'CountWeightedLHEEnvelope'                                                       : [ 8.83985547e+04, 6.34939727e+04, ],
    'CountWeightedFull'                                                              : [ 4.37314258e+04, 4.37351914e+04, 4.37203203e+04, ],
    'CountWeightedFullLHEWeightScale'                                                : [ 4.63339492e+04, 4.58348672e+04, 4.56511797e+04, 4.48582773e+04, 4.37314258e+04, 4.29078906e+04, 4.23106367e+04, 4.08443125e+04, 3.96848945e+04, ],
    'CountWeightedFullLHEEnvelope'                                                   : [ 5.07229062e+04, 3.64326328e+04, ],
    'CountWeightedL1PrefireNom'                                                      : [ 7.45196328e+04, 7.45266875e+04, 7.45034062e+04, ],
    'CountWeightedL1Prefire'                                                         : [ 7.45196328e+04, 7.40834453e+04, 7.49561484e+04, ],
    'CountWeightedLHEWeightScaleL1PrefireNom'                                        : [ 7.88878281e+04, 7.80649688e+04, 7.77760703e+04, 7.64148125e+04, 7.45196328e+04, 7.31370781e+04, 7.20990469e+04, 6.96213281e+04, 6.76637812e+04, ],
    'CountWeightedLHEEnvelopeL1PrefireNom'                                           : [ 8.63799062e+04, 6.21137500e+04, ],
    'CountWeightedFullL1PrefireNom'                                                  : [ 4.27568555e+04, 4.27621289e+04, 4.27474062e+04, ],
    'CountWeightedFullL1Prefire'                                                     : [ 4.27568555e+04, 4.25067734e+04, 4.30074609e+04, ],
    'CountWeightedFullLHEWeightScaleL1PrefireNom'                                    : [ 4.52656641e+04, 4.47936016e+04, 4.46275938e+04, 4.38465664e+04, 4.27568555e+04, 4.19652969e+04, 4.13702617e+04, 3.99483867e+04, 3.88253438e+04, ],
    'CountWeightedFullLHEEnvelopeL1PrefireNom'                                       : [ 4.95646445e+04, 3.56407969e+04, ],
  }),
  ("nof_tree_events",                 16293),
  ("nof_db_events",                   3981250),
  ("fsize_local",                     97192475), # 97.19MB, avg file size 97.19MB
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
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2016/2020Oct24_wPresel_nonNom_tth_sync/ntuples/ttHToNonbb_M125_powheg"),
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

