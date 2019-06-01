from collections import OrderedDict as OD

# file generated at 2019-06-01 15:57:21 with the following command:
# create_dictionary.py -m python/samples/metaDict_2017.py -p /hdfs/local/karl/ttHNtupleProduction/2017/2019Jun01_woPresel_nom/ntuples -N samples_2017 -E 2017 -o python/samples -g tthAnalyzeSamples_2017.py -M

samples_2017 = OD()
samples_2017["/THQ_ctcvcp_4f_Hincl_13TeV_madgraph_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "tHq"),
  ("process_name_specific",           "THQ_ctcvcp"),
  ("nof_files",                       1),
  ("nof_db_files",                    258),
  ("nof_events",                      {
    'Count'                                            : [        51000, ],
    'CountWeighted'                                    : [        50759,        50812,        50686, ],
    'CountWeightedNoPU'                                : [        50754, ],
    'CountFullWeighted'                                : [        50759,        50812,        50686, ],
    'CountFullWeightedNoPU'                            : [        50754, ],
    'CountWeightedLHEWeightScale'                      : [        63589,        58185,        53467,        55486,        50758,        46638,        49280,        45075,        41409, ],
    'CountWeightedLHEWeightScaleNoPU'                  : [        63585,        58175,        53453,        55486,        50754,        46628,        49280,        45071,        41402, ],
    'CountFullWeightedLHEWeightScale'                  : [        63589,        58185,        53467,        55486,        50758,        46638,        49280,        45075,        41409, ],
    'CountFullWeightedLHEWeightScaleNoPU'              : [        63585,        58175,        53453,        55486,        50754,        46628,        49280,        45071,        41402, ],
    'CountWeightedL1PrefireNom'                        : [        48722,        48766,        48658, ],
    'CountWeightedL1Prefire'                           : [        48722,        48230,        49203, ],
    'CountWeightedNoPUL1PrefireNom'                    : [        48707, ],
    'CountFullWeightedL1PrefireNom'                    : [        48722,        48766,        48658, ],
    'CountFullWeightedL1Prefire'                       : [        48722,        48230,        49203, ],
    'CountFullWeightedNoPUL1PrefireNom'                : [        48707, ],
    'CountWeightedLHEWeightScaleL1PrefireNom'          : [        61014,        55868,        51366,        53222,        48721,        44791,        47257,        43255,        39760, ],
    'CountWeightedLHEWeightScaleNoPUL1PrefireNom'      : [        60997,        55847,        51343,        53210,        48707,        44773,        47248,        43242,        39745, ],
    'CountFullWeightedLHEWeightScaleL1PrefireNom'      : [        61014,        55868,        51366,        53222,        48721,        44791,        47257,        43255,        39760, ],
    'CountFullWeightedLHEWeightScaleNoPUL1PrefireNom'  : [        60997,        55847,        51343,        53210,        48707,        44773,        47248,        43242,        39745, ],
  }),
  ("nof_tree_events",                 51000),
  ("nof_db_events",                   9918994),
  ("fsize_local",                     143156990), # 143.16MB, avg file size 143.16MB
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
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2019Jun01_woPresel_nom/ntuples/THQ_ctcvcp"),
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
    'CountWeighted'                                    : [        50289,        50286,        50305, ],
    'CountWeightedNoPU'                                : [        50354, ],
    'CountFullWeighted'                                : [        50289,        50286,        50305, ],
    'CountFullWeightedNoPU'                            : [        50354, ],
    'CountWeightedLHEWeightScale'                      : [        49856,        57208,        60594,        43826,        50289,        53265,        39125,        44896,        47552, ],
    'CountWeightedLHEWeightScaleNoPU'                  : [        49924,        57252,        60665,        43886,        50354,        53327,        39178,        44972,        47608, ],
    'CountFullWeightedLHEWeightScale'                  : [        49856,        57208,        60594,        43826,        50289,        53265,        39125,        44896,        47552, ],
    'CountFullWeightedLHEWeightScaleNoPU'              : [        49924,        57252,        60665,        43886,        50354,        53327,        39178,        44972,        47608, ],
    'CountWeightedL1PrefireNom'                        : [        48440,        48429,        48456, ],
    'CountWeightedL1Prefire'                           : [        48440,        48000,        48872, ],
    'CountWeightedNoPUL1PrefireNom'                    : [        48478, ],
    'CountFullWeightedL1PrefireNom'                    : [        48440,        48429,        48456, ],
    'CountFullWeightedL1Prefire'                       : [        48440,        48000,        48872, ],
    'CountFullWeightedNoPUL1PrefireNom'                : [        48478, ],
    'CountWeightedLHEWeightScaleL1PrefireNom'          : [        47967,        55104,        58418,        42165,        48440,        51352,        37643,        43245,        45844, ],
    'CountWeightedLHEWeightScaleNoPUL1PrefireNom'      : [        48008,        55131,        58460,        42201,        48478,        51388,        37675,        43287,        45877, ],
    'CountFullWeightedLHEWeightScaleL1PrefireNom'      : [        47967,        55104,        58418,        42165,        48440,        51352,        37643,        43245,        45844, ],
    'CountFullWeightedLHEWeightScaleNoPUL1PrefireNom'  : [        48008,        55131,        58460,        42201,        48478,        51388,        37675,        43287,        45877, ],
  }),
  ("nof_tree_events",                 50400),
  ("nof_db_events",                   4719999),
  ("fsize_local",                     165366907), # 165.37MB, avg file size 165.37MB
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
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2019Jun01_woPresel_nom/ntuples/THW_ctcvcp"),
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

