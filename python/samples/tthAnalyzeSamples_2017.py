from collections import OrderedDict as OD

# file generated at 2019-05-28 09:52:12 with the following command:
# create_dictionary.py -m python/samples/metaDict_2017.py -p /hdfs/local/karl/ttHNtupleProduction/2017/2019May28_woPresel_nonNom/ntuples -N samples_2017 -E 2017 -o python/samples -g tthAnalyzeSamples_2017.py -M

samples_2017 = OD()
samples_2017["/THQ_ctcvcp_4f_Hincl_13TeV_madgraph_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "tHq"),
  ("process_name_specific",           "THQ_ctcvcp"),
  ("nof_files",                       1),
  ("nof_db_files",                    258),
  ("nof_events",                      {
    'Count'                                            : [        51000, ],
    'CountWeighted'                                    : [         3692,         3690,         3696, ],
    'CountWeightedNoPU'                                : [         3683, ],
    'CountFullWeighted'                                : [         3692,         3690,         3696, ],
    'CountFullWeightedNoPU'                            : [         3683, ],
    'CountWeightedLHEWeightScale'                      : [         4672,         4227,         3845,         4082,         3692,         3359,         3629,         3282,         2986, ],
    'CountWeightedLHEWeightScaleNoPU'                  : [         4661,         4216,         3835,         4072,         3683,         3350,         3620,         3274,         2978, ],
    'CountFullWeightedLHEWeightScale'                  : [         4672,         4227,         3845,         4082,         3692,         3359,         3629,         3282,         2986, ],
    'CountFullWeightedLHEWeightScaleNoPU'              : [         4661,         4216,         3835,         4072,         3683,         3350,         3620,         3274,         2978, ],
    'CountWeightedL1PrefireNom'                        : [         3493,         3490,         3498, ],
    'CountWeightedL1Prefire'                           : [         3493,         3446,         3540, ],
    'CountWeightedNoPUL1PrefireNom'                    : [         3484, ],
    'CountFullWeightedL1PrefireNom'                    : [         3493,         3490,         3498, ],
    'CountFullWeightedL1Prefire'                       : [         3493,         3446,         3540, ],
    'CountFullWeightedNoPUL1PrefireNom'                : [         3484, ],
    'CountWeightedLHEWeightScaleL1PrefireNom'          : [         4418,         4000,         3642,         3859,         3493,         3180,         3430,         3105,         2826, ],
    'CountWeightedLHEWeightScaleNoPUL1PrefireNom'      : [         4408,         3990,         3632,         3849,         3484,         3172,         3421,         3097,         2819, ],
    'CountFullWeightedLHEWeightScaleL1PrefireNom'      : [         4418,         4000,         3642,         3859,         3493,         3180,         3430,         3105,         2826, ],
    'CountFullWeightedLHEWeightScaleNoPUL1PrefireNom'  : [         4408,         3990,         3632,         3849,         3484,         3172,         3421,         3097,         2819, ],
  }),
  ("nof_tree_events",                 51000),
  ("nof_db_events",                   9918994),
  ("fsize_local",                     200537556), # 200.54MB, avg file size 200.54MB
  ("fsize_db",                        569542482347), # 569.54GB, avg file size 2.21GB
  ("use_it",                          True),
  ("xsection",                        0.07096),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("has_LHE",                         True),
  ("LHE_set",                         "LHA IDs 306000 - 306102 -> NNPDF31_nnlo_hessian_pdfas PDF set, expecting 103 weights (counted 103 weights)"),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2019May28_woPresel_nonNom/ntuples/THQ_ctcvcp"),
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

samples_2017["/THW_ctcvcp_5f_Hincl_13TeV_madgraph_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "tHW"),
  ("process_name_specific",           "THW_ctcvcp"),
  ("nof_files",                       1),
  ("nof_db_files",                    172),
  ("nof_events",                      {
    'Count'                                            : [        50400, ],
    'CountWeighted'                                    : [         5791,         5809,         5765, ],
    'CountWeightedNoPU'                                : [         5791, ],
    'CountFullWeighted'                                : [         5791,         5809,         5765, ],
    'CountFullWeightedNoPU'                            : [         5791, ],
    'CountWeightedLHEWeightScale'                      : [         5553,         6588,         7166,         4881,         5791,         6299,         4358,         5170,         5624, ],
    'CountWeightedLHEWeightScaleNoPU'                  : [         5554,         6588,         7166,         4882,         5791,         6299,         4358,         5170,         5623, ],
    'CountFullWeightedLHEWeightScale'                  : [         5553,         6588,         7166,         4881,         5791,         6299,         4358,         5170,         5624, ],
    'CountFullWeightedLHEWeightScaleNoPU'              : [         5554,         6588,         7166,         4882,         5791,         6299,         4358,         5170,         5623, ],
    'CountWeightedL1PrefireNom'                        : [         5614,         5631,         5588, ],
    'CountWeightedL1Prefire'                           : [         5614,         5571,         5656, ],
    'CountWeightedNoPUL1PrefireNom'                    : [         5614, ],
    'CountFullWeightedL1PrefireNom'                    : [         5614,         5631,         5588, ],
    'CountFullWeightedL1Prefire'                       : [         5614,         5571,         5656, ],
    'CountFullWeightedNoPUL1PrefireNom'                : [         5614, ],
    'CountWeightedLHEWeightScaleL1PrefireNom'          : [         5377,         6386,         6952,         4727,         5614,         6111,         4220,         5011,         5456, ],
    'CountWeightedLHEWeightScaleNoPUL1PrefireNom'      : [         5377,         6386,         6951,         4727,         5614,         6111,         4220,         5011,         5455, ],
    'CountFullWeightedLHEWeightScaleL1PrefireNom'      : [         5377,         6386,         6952,         4727,         5614,         6111,         4220,         5011,         5456, ],
    'CountFullWeightedLHEWeightScaleNoPUL1PrefireNom'  : [         5377,         6386,         6951,         4727,         5614,         6111,         4220,         5011,         5455, ],
  }),
  ("nof_tree_events",                 50400),
  ("nof_db_events",                   4719999),
  ("fsize_local",                     240078630), # 240.08MB, avg file size 240.08MB
  ("fsize_db",                        308444472684), # 308.44GB, avg file size 1.79GB
  ("use_it",                          True),
  ("xsection",                        0.01561),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("has_LHE",                         True),
  ("LHE_set",                         "LHA IDs 91400 - 91432 -> PDF4LHC15_nnlo_30_pdfas PDF set, expecting 33 weights (counted 33 weights)"),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2019May28_woPresel_nonNom/ntuples/THW_ctcvcp"),
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
    'CountWeightedLHEWeightScaleNoPU'                  : [        22893,        23302,        23696,        22780,        22430,        22157,        21361,        20658,        20079, ],
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
  ("fsize_local",                     303049525), # 303.05MB, avg file size 303.05MB
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
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2019May28_woPresel_nonNom_sync/ntuples/ttHJetToNonbb_M125_amcatnlo"),
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

samples_2017["/VHToNonbb_M125_v14-v2/RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v1/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "VH"),
  ("process_name_specific",           "VHToNonbb_M125_v14-v2"),
  ("nof_files",                       1),
  ("nof_db_files",                    208),
  ("nof_events",                      {
    'Count'                                            : [        65452, ],
    'CountWeighted'                                    : [        22455,        22443,        22473, ],
    'CountWeightedNoPU'                                : [        22430, ],
    'CountFullWeighted'                                : [        64533,        64495,        64583, ],
    'CountFullWeightedNoPU'                            : [        64469, ],
    'CountWeightedLHEWeightScale'                      : [        22906,        23311,        23703,        22808,        22455,        22179,        21395,        20690,        20108, ],
    'CountWeightedLHEWeightScaleNoPU'                  : [        22893,        23302,        23696,        22780,        22430,        22157,        21361,        20658,        20079, ],
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
  ("fsize_local",                     303049525), # 303.05MB, avg file size 303.05MB
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
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2019May28_woPresel_nonNom_sync/ntuples/ttHJetToNonbb_M125_amcatnlo"),
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

samples_2017["/tW1JetsToLNu/RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v1/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "EWK"),
  ("process_name_specific",           "W1JetsToLNu"),
  ("nof_files",                       1),
  ("nof_db_files",                    208),
  ("nof_events",                      {
    'Count'                                            : [        65452, ],
    'CountWeighted'                                    : [        22455,        22443,        22473, ],
    'CountWeightedNoPU'                                : [        22430, ],
    'CountFullWeighted'                                : [        64533,        64495,        64583, ],
    'CountFullWeightedNoPU'                            : [        64469, ],
    'CountWeightedLHEWeightScale'                      : [        22906,        23311,        23703,        22808,        22455,        22179,        21395,        20690,        20108, ],
    'CountWeightedLHEWeightScaleNoPU'                  : [        22893,        23302,        23696,        22780,        22430,        22157,        21361,        20658,        20079, ],
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
  ("fsize_local",                     303049525), # 303.05MB, avg file size 303.05MB
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
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2019May28_woPresel_nonNom_sync/ntuples/ttHJetToNonbb_M125_amcatnlo"),
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

samples_2017["/TTTT/RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v1/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "Rares"),
  ("process_name_specific",           "TTTT"),
  ("nof_files",                       1),
  ("nof_db_files",                    208),
  ("nof_events",                      {
    'Count'                                            : [        65452, ],
    'CountWeighted'                                    : [        22455,        22443,        22473, ],
    'CountWeightedNoPU'                                : [        22430, ],
    'CountFullWeighted'                                : [        64533,        64495,        64583, ],
    'CountFullWeightedNoPU'                            : [        64469, ],
    'CountWeightedLHEWeightScale'                      : [        22906,        23311,        23703,        22808,        22455,        22179,        21395,        20690,        20108, ],
    'CountWeightedLHEWeightScaleNoPU'                  : [        22893,        23302,        23696,        22780,        22430,        22157,        21361,        20658,        20079, ],
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
  ("fsize_local",                     303049525), # 303.05MB, avg file size 303.05MB
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
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2019May28_woPresel_nonNom_sync/ntuples/ttHJetToNonbb_M125_amcatnlo"),
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

samples_2017["/TTTo2L2Nu/RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v1/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "TT"),
  ("process_name_specific",           "TTTo2L2Nu"),
  ("nof_files",                       1),
  ("nof_db_files",                    208),
  ("nof_events",                      {
    'Count'                                            : [        65452, ],
    'CountWeighted'                                    : [        22455,        22443,        22473, ],
    'CountWeightedNoPU'                                : [        22430, ],
    'CountFullWeighted'                                : [        64533,        64495,        64583, ],
    'CountFullWeightedNoPU'                            : [        64469, ],
    'CountWeightedLHEWeightScale'                      : [        22906,        23311,        23703,        22808,        22455,        22179,        21395,        20690,        20108, ],
    'CountWeightedLHEWeightScaleNoPU'                  : [        22893,        23302,        23696,        22780,        22430,        22157,        21361,        20658,        20079, ],
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
  ("fsize_local",                     303049525), # 303.05MB, avg file size 303.05MB
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
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2019May28_woPresel_nonNom_sync/ntuples/ttHJetToNonbb_M125_amcatnlo"),
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

samples_2017["/TTWJetsToLNu/RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v1/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "TTW"),
  ("process_name_specific",           "TTWJetsToLNu"),
  ("nof_files",                       1),
  ("nof_db_files",                    208),
  ("nof_events",                      {
    'Count'                                            : [        65452, ],
    'CountWeighted'                                    : [        22455,        22443,        22473, ],
    'CountWeightedNoPU'                                : [        22430, ],
    'CountFullWeighted'                                : [        64533,        64495,        64583, ],
    'CountFullWeightedNoPU'                            : [        64469, ],
    'CountWeightedLHEWeightScale'                      : [        22906,        23311,        23703,        22808,        22455,        22179,        21395,        20690,        20108, ],
    'CountWeightedLHEWeightScaleNoPU'                  : [        22893,        23302,        23696,        22780,        22430,        22157,        21361,        20658,        20079, ],
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
  ("fsize_local",                     303049525), # 303.05MB, avg file size 303.05MB
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
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2019May28_woPresel_nonNom_sync/ntuples/ttHJetToNonbb_M125_amcatnlo"),
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

samples_2017["/TTWW/RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v1/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "TTWW"),
  ("process_name_specific",           "TTWW"),
  ("nof_files",                       1),
  ("nof_db_files",                    208),
  ("nof_events",                      {
    'Count'                                            : [        65452, ],
    'CountWeighted'                                    : [        22455,        22443,        22473, ],
    'CountWeightedNoPU'                                : [        22430, ],
    'CountFullWeighted'                                : [        64533,        64495,        64583, ],
    'CountFullWeightedNoPU'                            : [        64469, ],
    'CountWeightedLHEWeightScale'                      : [        22906,        23311,        23703,        22808,        22455,        22179,        21395,        20690,        20108, ],
    'CountWeightedLHEWeightScaleNoPU'                  : [        22893,        23302,        23696,        22780,        22430,        22157,        21361,        20658,        20079, ],
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
  ("fsize_local",                     303049525), # 303.05MB, avg file size 303.05MB
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
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2019May28_woPresel_nonNom_sync/ntuples/ttHJetToNonbb_M125_amcatnlo"),
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

samples_2017["/TTZToLL_M10/RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v1/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "TTZ"),
  ("process_name_specific",           "TTZToLL_M10"),
  ("nof_files",                       1),
  ("nof_db_files",                    208),
  ("nof_events",                      {
    'Count'                                            : [        65452, ],
    'CountWeighted'                                    : [        22455,        22443,        22473, ],
    'CountWeightedNoPU'                                : [        22430, ],
    'CountFullWeighted'                                : [        64533,        64495,        64583, ],
    'CountFullWeightedNoPU'                            : [        64469, ],
    'CountWeightedLHEWeightScale'                      : [        22906,        23311,        23703,        22808,        22455,        22179,        21395,        20690,        20108, ],
    'CountWeightedLHEWeightScaleNoPU'                  : [        22893,        23302,        23696,        22780,        22430,        22157,        21361,        20658,        20079, ],
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
  ("fsize_local",                     303049525), # 303.05MB, avg file size 303.05MB
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
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2019May28_woPresel_nonNom_sync/ntuples/ttHJetToNonbb_M125_amcatnlo"),
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
  [ 'ST_s-channel_4f_leptonDecays',                    'ST_s-channel_4f_leptonDecays_PSweights',           ],
  [ 'DYJetsToLL_M-4to50_HT-200to400',                  'DYJetsToLL_M-4to50_HT-200to400_ext1',              ],
  [ 'DYJetsToLL_M50_HT100to200',                       'DYJetsToLL_M50_HT100to200_ext1',                   ],
  [ 'TTTT',                                            'TTTT_PSweights',                                   ],
  [ 'DY3JetsToLL_M-50',                                'DY3JetsToLL_M-50_ext1',                            ],
  [ 'ST_t-channel_top_4f_inclusiveDecays',             'ST_t-channel_top_4f_inclusiveDecays_PSweights',    ],
  [ 'DYJetsToLL_M-4to50_HT-400to600',                  'DYJetsToLL_M-4to50_HT-400to600_ext1',              ],
  [ 'WWToLNuQQ',                                       'WWToLNuQQ_ext1',                                  'WWToLNuQQ_PSweights_ext1',                         ],
  [ 'TTWJetsToLNu',                                    'TTWJetsToLNu_PSweights',                           ],
  [ 'TTToHadronic',                                    'TTToHadronic_PSweights',                           ],
  [ 'TTTo2L2Nu',                                       'TTTo2L2Nu_PSweights',                              ],
  [ 'DYJetsToLL_M-10to50',                             'DYJetsToLL_M-10to50_ext1',                         ],
  [ 'ST_t-channel_antitop_4f_inclusiveDecays',         'ST_t-channel_antitop_4f_inclusiveDecays_PSweights',  ],
  [ 'DY1JetsToLL_M-50_ext1',                           'DY1JetsToLL_M-50',                                 ],
  [ 'WWTo2L2Nu',                                       'WWTo2L2Nu_PSweights_ext1',                         ],
  [ 'DYJetsToLL_M50_HT200to400',                       'DYJetsToLL_M50_HT200to400_ext1',                   ],
  [ 'DYJetsToLL_M-4to50_HT-600toInf',                  'DYJetsToLL_M-4to50_HT-600toInf_ext1',              ],
  [ 'WWTo4Q',                                          'WWTo4Q_PSweights_ext1',                            ],
  [ 'DY2JetsToLL_M-50',                                'DY2JetsToLL_M-50_ext1',                            ],
  [ 'TTZToLL_M10',                                     'TTZToLL_M10_PSweights',                            ],
  [ 'TTGJets',                                         'TTGJets_ext1',                                     ],
  [ 'ST_tW_top_5f_inclusiveDecays',                    'ST_tW_top_5f_inclusiveDecays_PSweights',           ],
  [ 'ZZTo4L',                                          'ZZTo4L_ext1',                                     'ZZTo4L_ext2',                                      ],
  [ 'WJetsToLNu_madgraphMLM',                          'WJetsToLNu_madgraphMLM_ext1',                      ],
  [ 'TTToSemiLeptonic',                                'TTToSemiLeptonic_PSweights',                       ],
  [ 'TTWJets_LO',                                      'TTWJets_LO_ext1',                                  ],
  [ 'TTZJets_LO',                                      'TTZJets_LO_ext1',                                  ],
  [ 'ttHToNonbb_M125_powheg',                          'ttHToNonbb_M125_powheg_ext1',                      ],
  [ 'DYBBJetsToLL_M-50',                               'DYBBJetsToLL_M-50_ext1',                           ],
  [ 'ST_tW_antitop_5f_inclusiveDecays',                'ST_tW_antitop_5f_inclusiveDecays_PSweights',       ],
  [ 'GluGluHToTauTau',                                 'GluGluHToTauTau_ext1',                             ],
  [ 'DYJetsToLL_M50_HT400to600',                       'DYJetsToLL_M50_HT400to600_ext1',                   ],
  [ 'DYJetsToLL_M-50',                                 'DYJetsToLL_M-50_ext1',                             ],
  [ 'DYJetsToLL_M-50_amcatnloFXFX',                    'DYJetsToLL_M-50_amcatnloFXFX_ext1',                ],
  [ 'DYJetsToLL_M-4to50_HT-100to200',                  'DYJetsToLL_M-4to50_HT-100to200_ext1',              ],
]
