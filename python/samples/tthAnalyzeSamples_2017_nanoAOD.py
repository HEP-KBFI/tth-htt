from collections import OrderedDict as OD

# file generated at 2019-06-01 16:02:12 with the following command:
# create_dictionary.py -m python/samples/metaDict_2017.py -p /hdfs/local/karl/ntuples/2017/nanoAODproduction/2019Jun01 -N samples_2017 -E 2017 -o python/samples -g tthAnalyzeSamples_2017_nanoAOD.py -M

samples_2017 = OD()
samples_2017["/THQ_ctcvcp_4f_Hincl_13TeV_madgraph_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "tHq"),
  ("process_name_specific",           "THQ_ctcvcp"),
  ("nof_files",                       1),
  ("nof_db_files",                    258),
  ("nof_events",                      {
  }),
  ("nof_tree_events",                 51000),
  ("nof_db_events",                   9918994),
  ("fsize_local",                     132471393), # 132.47MB, avg file size 132.47MB
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
        ("path",      "/hdfs/local/karl/ntuples/2017/nanoAODproduction/2019Jun01/THQ_ctcvcp"),
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
  }),
  ("nof_tree_events",                 50400),
  ("nof_db_events",                   4719999),
  ("fsize_local",                     155855399), # 155.86MB, avg file size 155.86MB
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
        ("path",      "/hdfs/local/karl/ntuples/2017/nanoAODproduction/2019Jun01/THW_ctcvcp"),
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

