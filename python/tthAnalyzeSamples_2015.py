from collections import OrderedDict as OD

# file generated with the following command:
# ./scripts/create_dictionary.py -v -m python/metaDict_2015.py -p /hdfs/cms/store/user/kaehatah -Z zeroes.txt -z zombies.txt -N samples_2015 -J /home/karl/sandbox/create_dictionary -F -x -g dict_2015.py -E 2015

samples_2015 = OD()
samples_2015["/ST_t-channel_4f_leptonDecays_13TeV-amcatnlo-pythia8_TuneCUETP8M1/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "TT"),
  ("process_name_specific",           "ST_t-channel_4f_leptonDecays"),
  ("nof_files",                       478),
  ("nof_events",                      10556897),
  ("use_HIP_mitigation_bTag",         False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                          True),
  ("xsection",                        70.69),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1e1mu', '1mu', '2e', '2mu']),
  ("reHLT",                           True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/kaehatah/ST_t-channel_4f_leptonDecays_13TeV-amcatnlo-pythia8_TuneCUETP8M1/VHBB_HEPPY_V12_ST_t-channel_4f_leptonDecays_13TeV-amcatnlo-Py8_TuneCUETP8M1__fall15MAv2-pu25ns15v1_76r2as_v12-v1/160419_140037"),
        ("selection", "*"),
        ("blacklist", [100, 191, 226, 264, 311, 329, 456]),
      ]),
      OD([
        ("path",      "/hdfs/cms/store/user/kaehatah/ST_t-channel_4f_leptonDecays_13TeV-amcatnlo-pythia8_TuneCUETP8M1/VHBB_HEPPY_V12_ST_t-channel_4f_leptonDecays_13TeV-amcatnlo-Py8_TuneCUETP8M1__fall15MAv2-pu25ns15v1_76r2as_v12-v1/160331_080329"),
        ("selection", "100,191,226,264,329,456"),
        ("blacklist", []),
      ]),
    ]
  ),
])

samples_2015["/ST_t-channel_4f_leptonDecays_13TeV-amcatnlo-pythia8_TuneCUETP8M1/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12_ext1-v1/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "TT"),
  ("process_name_specific",           "ST_t-channel_4f_leptonDecays_ext1"),
  ("nof_files",                       690),
  ("nof_events",                      10556897),
  ("use_HIP_mitigation_bTag",         False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                          True),
  ("xsection",                        70.69),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1e1mu', '1mu', '2e', '2mu']),
  ("reHLT",                           True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/kaehatah/ST_t-channel_4f_leptonDecays_13TeV-amcatnlo-pythia8_TuneCUETP8M1/VHBB_HEPPY_V12_ST_t-channel_4f_leptonDecays_13TeV-amcatnlo-Py8_TuneCUETP8M1__fall15MAv2-pu25ns15v1_76r2as_v12_ext1-v1/160331_080437"),
        ("selection", "*"),
        ("blacklist", [196, 244, 267, 306, 310, 358, 376, 379, 390, 406, 409, 449, 452, 454, 471, 516, 534, 546, 560, 564, 576, 584, 585, 601, 621, 625, 633, 641, 646, 689]),
      ]),
      OD([
        ("path",      "/hdfs/cms/store/user/kaehatah/ST_t-channel_4f_leptonDecays_13TeV-amcatnlo-pythia8_TuneCUETP8M1/VHBB_HEPPY_V12_ST_t-channel_4f_leptonDecays_13TeV-amcatnlo-Py8_TuneCUETP8M1__fall15MAv2-pu25ns15v1_76r2as_v12_ext1-v1/160415_124417"),
        ("selection", "196,267,306,310,358,376,379,390,406,409,449,452,454,471,516,534,546,560,564,584,601,621,625,633,641,646,689"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2015["/TTTT_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "Rares"),
  ("process_name_specific",           "TTTT"),
  ("nof_files",                       7),
  ("nof_events",                      505215),
  ("use_HIP_mitigation_bTag",         False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                          True),
  ("xsection",                        0.009103),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1e1mu', '1mu', '2e', '2mu']),
  ("reHLT",                           True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/kaehatah/TTTT_TuneCUETP8M1_13TeV-amcatnlo-pythia8/VHBB_HEPPY_V12_TTTT_TuneCUETP8M1_13TeV-amcatnlo-Py8__fall15MAv2-pu25ns15v1_76r2as_v12-v1/160331_084059"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])

samples_2015["/TTTT_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12_ext1-v1/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "Rares"),
  ("process_name_specific",           "TTTT_ext1"),
  ("nof_files",                       24),
  ("nof_events",                      505215),
  ("use_HIP_mitigation_bTag",         False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                          True),
  ("xsection",                        0.009103),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1e1mu', '1mu', '2e', '2mu']),
  ("reHLT",                           True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/kaehatah/TTTT_TuneCUETP8M1_13TeV-amcatnlo-pythia8/VHBB_HEPPY_V12_TTTT_TuneCUETP8M1_13TeV-amcatnlo-Py8__fall15MAv2-pu25ns15v1_76r2as_v12_ext1-v1/160513_121601"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2015["/WpWpJJ_EWK-QCD_TuneCUETP8M1_13TeV-madgraph-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "Rares"),
  ("process_name_specific",           "WpWpJJ_EWK-QCD"),
  ("nof_files",                       5),
  ("nof_events",                      118359),
  ("use_HIP_mitigation_bTag",         False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                          True),
  ("xsection",                        0.03711),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1e1mu', '1mu', '2e', '2mu']),
  ("reHLT",                           True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/kaehatah/WpWpJJ_EWK-QCD_TuneCUETP8M1_13TeV-madgraph-pythia8/VHBB_HEPPY_V12_WpWpJJ_EWK-QCD_TuneCUETP8M1_13TeV-madgraph-Py8__fall15MAv2-pu25ns15v1_76r2as_v12-v1/160331_083346"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2015["/TTJets_SingleLeptFromTbar_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v2/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "TT"),
  ("process_name_specific",           "TTJets_SingleLeptFromTbar"),
  ("nof_files",                       275),
  ("nof_events",                      11956553),
  ("use_HIP_mitigation_bTag",         False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                          True),
  ("xsection",                        182.0),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1e1mu', '1mu', '2e', '2mu']),
  ("reHLT",                           True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/kaehatah/TTJets_SingleLeptFromTbar_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/VHBB_HEPPY_V12_TTJets_SingleLeptFromTbar_TuneCUETP8M1_13TeV-madgraphMLM-Py8__fall15MAv2-pu25ns15v1_76r2as_v12-v2/160419_134531"),
        ("selection", "*"),
        ("blacklist", [166, 223, 269]),
      ]),
      OD([
        ("path",      "/hdfs/cms/store/user/kaehatah/TTJets_SingleLeptFromTbar_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/VHBB_HEPPY_V12_TTJets_SingleLeptFromTbar_TuneCUETP8M1_13TeV-madgraphMLM-Py8__fall15MAv2-pu25ns15v1_76r2as_v12-v2/160501_160405"),
        ("selection", "166,223,269"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2015["/WJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "EWK"),
  ("process_name_specific",           "WJetsToLNu"),
  ("nof_files",                       595),
  ("nof_events",                      16519503),
  ("use_HIP_mitigation_bTag",         False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                          True),
  ("xsection",                        61526.7),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1e1mu', '1mu', '2e', '2mu']),
  ("reHLT",                           True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/kaehatah/WJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/VHBB_HEPPY_V12_WJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-Py8__fall15MAv2-pu25ns15v1_76r2as_v12-v1/160331_075944"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2015["/ST_s-channel_4f_leptonDecays_13TeV-amcatnlo-pythia8_TuneCUETP8M1/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v2/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "TT"),
  ("process_name_specific",           "ST_s-channel_4f_leptonDecays"),
  ("nof_files",                       24),
  ("nof_events",                      621783),
  ("use_HIP_mitigation_bTag",         False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                          True),
  ("xsection",                        3.75),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1e1mu', '1mu', '2e', '2mu']),
  ("reHLT",                           True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/kaehatah/ST_s-channel_4f_leptonDecays_13TeV-amcatnlo-pythia8_TuneCUETP8M1/VHBB_HEPPY_V12_ST_s-channel_4f_leptonDecays_13TeV-amcatnlo-Py8_TuneCUETP8M1__fall15MAv2-pu25ns15v1_76r2as_v12-v2/160331_080546"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2015["/ttHJetToNonbb_M130_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "signal"),
  ("process_name_specific",           "ttHJetToNonbb_M130"),
  ("nof_files",                       11),
  ("nof_events",                      112949),
  ("use_HIP_mitigation_bTag",         False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                          False),
  ("xsection",                        0.0),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1e1mu', '1mu', '2e', '2mu']),
  ("reHLT",                           True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/kaehatah/ttHJetToNonbb_M130_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/VHBB_HEPPY_V12_ttHJetToNonbb_M130_13TeV_amcatnloFXFX_madspin_Py8_mWCutfix__fall15MAv2-pu25ns15v1_76r2as_v12-v1/160330_172533"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2015["/ST_tW_top_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "TT"),
  ("process_name_specific",           "ST_tW_top_5f_inclusiveDecays"),
  ("nof_files",                       23),
  ("nof_events",                      1000378),
  ("use_HIP_mitigation_bTag",         False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                          True),
  ("xsection",                        35.6),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1e1mu', '1mu', '2e', '2mu']),
  ("reHLT",                           True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/kaehatah/ST_tW_top_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1/VHBB_HEPPY_V12_ST_tW_top_5f_inclusiveDecays_13TeV-powheg-Py8_TuneCUETP8M1__fall15MAv2-pu25ns15v1_76r2as_v12-v1/160331_080051"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2015["/tZq_ll_4f_13TeV-amcatnlo-pythia8_TuneCUETP8M1/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "Rares"),
  ("process_name_specific",           "tZq_ll_4f"),
  ("nof_files",                       75),
  ("nof_events",                      795815),
  ("use_HIP_mitigation_bTag",         False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                          True),
  ("xsection",                        0.0758),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1e1mu', '1mu', '2e', '2mu']),
  ("reHLT",                           True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/kaehatah/tZq_ll_4f_13TeV-amcatnlo-pythia8_TuneCUETP8M1/VHBB_HEPPY_V12_tZq_ll_4f_13TeV-amcatnlo-Py8_TuneCUETP8M1__fall15MAv2-pu25ns15v1_76r2as_v12-v1/160331_083947"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2015["/ZZTo4L_13TeV_powheg_pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "EWK"),
  ("process_name_specific",           "ZZTo4L"),
  ("nof_files",                       154),
  ("nof_events",                      6669043),
  ("use_HIP_mitigation_bTag",         False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                          True),
  ("xsection",                        1.256),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1e1mu', '1mu', '2e', '2mu']),
  ("reHLT",                           True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/kaehatah/ZZTo4L_13TeV_powheg_pythia8/VHBB_HEPPY_V12_ZZTo4L_13TeV_powheg_Py8__fall15MAv2-pu25ns15v1_76r2as_v12-v1/160331_080924"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2015["/WW_DoubleScattering_13TeV-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "Rares"),
  ("process_name_specific",           "WW_DoubleScattering"),
  ("nof_files",                       21),
  ("nof_events",                      844367),
  ("use_HIP_mitigation_bTag",         False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                          True),
  ("xsection",                        1.64),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1e1mu', '1mu', '2e', '2mu']),
  ("reHLT",                           True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/kaehatah/WW_DoubleScattering_13TeV-pythia8/VHBB_HEPPY_V12_WW_DoubleScattering_13TeV-Py8__fall15MAv2-pu25ns15v1_76r2as_v12-v1/160331_083838"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2015["/WGToLNuG_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "Rares"),
  ("process_name_specific",           "WGToLNuG"),
  ("nof_files",                       146),
  ("nof_events",                      6103400),
  ("use_HIP_mitigation_bTag",         False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                          True),
  ("xsection",                        585.8),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1e1mu', '1mu', '2e', '2mu']),
  ("reHLT",                           True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/kaehatah/WGToLNuG_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/VHBB_HEPPY_V12_WGToLNuG_TuneCUETP8M1_13TeV-madgraphMLM-Py8__fall15MAv2-pu25ns15v1_76r2as_v12-v1/160331_082909"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2015["/TTJets_DiLept_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "TT"),
  ("process_name_specific",           "TTJets_DiLept"),
  ("nof_files",                       149),
  ("nof_events",                      6103374),
  ("use_HIP_mitigation_bTag",         False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                          True),
  ("xsection",                        87.3),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1e1mu', '1mu', '2e', '2mu']),
  ("reHLT",                           True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/kaehatah/TTJets_DiLept_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/VHBB_HEPPY_V12_TTJets_DiLept_TuneCUETP8M1_13TeV-madgraphMLM-Py8__fall15MAv2-pu25ns15v1_76r2as_v12-v1/160331_075552"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2015["/TTGJets_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "Rares"),
  ("process_name_specific",           "TTGJets"),
  ("nof_files",                       118),
  ("nof_events",                      1578462),
  ("use_HIP_mitigation_bTag",         False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                          True),
  ("xsection",                        3.697),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1e1mu', '1mu', '2e', '2mu']),
  ("reHLT",                           True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/kaehatah/TTGJets_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/VHBB_HEPPY_V12_TTGJets_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-Py8__fall15MAv2-pu25ns15v1_76r2as_v12-v1/160331_083238"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2015["/DoubleEG/Run2015C_25ns-16Dec2015-v1/MINIAOD"] = OD([
  ("type",                            "data"),
  ("sample_category",                 "data_obs"),
  ("process_name_specific",           "DoubleEG_Run2015C"),
  ("nof_files",                       52),
  ("nof_events",                      1854782),
  ("use_HIP_mitigation_bTag",         False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                          True),
  ("triggers",                        ['2e']),
  ("reHLT",                           True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/kaehatah/DoubleEG/VHBB_HEPPY_H20_DoubleEG__Run2015C_25ns-16Dec2015-v1/160419_140830"),
        ("selection", "*"),
        ("blacklist", [1, 30]),
      ]),
      OD([
        ("path",      "/hdfs/cms/store/user/kaehatah/DoubleEG/VHBB_HEPPY_H20_DoubleEG__Run2015C_25ns-16Dec2015-v1/160429_225812"),
        ("selection", "1,30"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2015["/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "EWK"),
  ("process_name_specific",           "DYJetsToLL_M-50"),
  ("nof_files",                       226),
  ("nof_events",                      9006284),
  ("use_HIP_mitigation_bTag",         False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                          True),
  ("xsection",                        6025.2),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1e1mu', '1mu', '2e', '2mu']),
  ("reHLT",                           True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/kaehatah/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/VHBB_HEPPY_V12_DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-Py8__fall15MAv2-pu25ns15v1_76r2as_v12-v1/160331_075827"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2015["/TGJets_TuneCUETP8M1_13TeV_amcatnlo_madspin_pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "Rares"),
  ("process_name_specific",           "TGJets"),
  ("nof_files",                       9),
  ("nof_events",                      55800),
  ("use_HIP_mitigation_bTag",         False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                          True),
  ("xsection",                        2.967),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1e1mu', '1mu', '2e', '2mu']),
  ("reHLT",                           True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/kaehatah/TGJets_TuneCUETP8M1_13TeV_amcatnlo_madspin_pythia8/VHBB_HEPPY_V12_TGJets_TuneCUETP8M1_13TeV_amcatnlo_madspin_Py8__fall15MAv2-pu25ns15v1_76r2as_v12-v1/160331_083126"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2015["/DoubleEG/Run2015D-16Dec2015-v2/MINIAOD"] = OD([
  ("type",                            "data"),
  ("sample_category",                 "data_obs"),
  ("process_name_specific",           "DoubleEG_Run2015D"),
  ("nof_files",                       1652),
  ("nof_events",                      72103053),
  ("use_HIP_mitigation_bTag",         False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                          True),
  ("triggers",                        ['2e']),
  ("reHLT",                           True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/kaehatah/DoubleEG/VHBB_HEPPY_H20_DoubleEG__Run2015D-16Dec2015-v2/160420_113228"),
        ("selection", "*"),
        ("blacklist", [15, 19, 111, 130, 156, 175, 191, 235, 239, 309, 361, 376, 395, 409, 413, 422, 448, 470, 483, 498, 507, 532, 568, 584, 597, 612, 666, 670, 673, 690, 697, 710, 722, 734, 748, 762, 772, 783, 814, 833, 846, 860, 863, 868, 878, 880, 889, 913, 960, 974, 991, 1019, 1088, 1091, 1106, 1143, 1176, 1277, 1366, 1367, 1410, 1411, 1425, 1427, 1428, 1434, 1456, 1466, 1514, 1516, 1522, 1585, 1613]),
      ]),
      OD([
        ("path",      "/hdfs/cms/store/user/kaehatah/DoubleEG/VHBB_HEPPY_H20_DoubleEG__Run2015D-16Dec2015-v2/160429_225920"),
        ("selection", "15,19,111,130,156,175,191,235,239,309,361,376,395,409,413,422,448,470,483,498,507,532,568,584,597,612,666,670,673,690,697,710,722,734,748,762,772,783,814,833,846,860,863,868,878,880,889,913,960,974,991,1019,1088,1091,1106,1143,1176,1277,1366,1367,1410,1411,1425,1427,1428,1434,1456,1466,1514,1516,1522,1585,1613"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2015["/DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "EWK"),
  ("process_name_specific",           "DYJetsToLL_M-10to50"),
  ("nof_files",                       753),
  ("nof_events",                      22483696),
  ("use_HIP_mitigation_bTag",         False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                          True),
  ("xsection",                        18610.0),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1e1mu', '1mu', '2e', '2mu']),
  ("reHLT",                           True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/kaehatah/DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/VHBB_HEPPY_V12_DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-amcatnloFXFX-Py8__fall15MAv2-pu25ns15v1_76r2as_v12-v1/160331_075706"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2015["/SingleElectron/Run2015C_25ns-16Dec2015-v1/MINIAOD"] = OD([
  ("type",                            "data"),
  ("sample_category",                 "data_obs"),
  ("process_name_specific",           "SingleElectron_Run2015C"),
  ("nof_files",                       21),
  ("nof_events",                      789291),
  ("use_HIP_mitigation_bTag",         False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                          True),
  ("triggers",                        ['1e']),
  ("reHLT",                           True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/kaehatah/SingleElectron/VHBB_HEPPY_H20_SingleElectron__Run2015C_25ns-16Dec2015-v1/160419_132242"),
        ("selection", "*"),
        ("blacklist", [14]),
      ]),
      OD([
        ("path",      "/hdfs/cms/store/user/kaehatah/SingleElectron/VHBB_HEPPY_H20_SingleElectron__Run2015C_25ns-16Dec2015-v1/160429_230407"),
        ("selection", "14"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2015["/DoubleMuon/Run2015D-16Dec2015-v1/MINIAOD"] = OD([
  ("type",                            "data"),
  ("sample_category",                 "data_obs"),
  ("process_name_specific",           "DoubleMuon_Run2015D"),
  ("nof_files",                       951),
  ("nof_events",                      40415329),
  ("use_HIP_mitigation_bTag",         False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                          True),
  ("triggers",                        ['2mu']),
  ("reHLT",                           True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/kaehatah/DoubleMuon/VHBB_HEPPY_H20_DoubleMuon__Run2015D-16Dec2015-v1/160419_140710"),
        ("selection", "*"),
        ("blacklist", [44, 63, 65, 109, 141, 188, 189, 215, 245, 251, 257, 262, 287, 290, 459, 469, 472, 539, 570, 593, 652, 661, 712, 760, 858, 864, 900, 932]),
      ]),
      OD([
        ("path",      "/hdfs/cms/store/user/kaehatah/DoubleMuon/VHBB_HEPPY_H20_DoubleMuon__Run2015D-16Dec2015-v1/160429_225658"),
        ("selection", "44,63,65,109,141,188,189,215,245,251,257,262,287,290,459,469,472,539,570,593,652,661,712,760,858,864,900,932"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2015["/DoubleMuon/Run2015C_25ns-16Dec2015-v1/MINIAOD"] = OD([
  ("type",                            "data"),
  ("sample_category",                 "data_obs"),
  ("process_name_specific",           "DoubleMuon_Run2015C"),
  ("nof_files",                       23),
  ("nof_events",                      709232),
  ("use_HIP_mitigation_bTag",         False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                          True),
  ("triggers",                        ['2mu']),
  ("reHLT",                           True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/kaehatah/DoubleMuon/VHBB_HEPPY_H20_DoubleMuon__Run2015C_25ns-16Dec2015-v1/160419_120720"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2015["/TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "TTZ"),
  ("process_name_specific",           "TTZToLLNuNu"),
  ("nof_files",                       10),
  ("nof_events",                      183096),
  ("use_HIP_mitigation_bTag",         False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                          True),
  ("xsection",                        0.2529),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1e1mu', '1mu', '2e', '2mu']),
  ("reHLT",                           True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/kaehatah/TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-pythia8/VHBB_HEPPY_V12_TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-Py8__fall15MAv2-pu25ns15v1_76r2as_v12-v1/160513_120014"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2015["/SingleElectron/Run2015D-16Dec2015-v1/MINIAOD"] = OD([
  ("type",                            "data"),
  ("sample_category",                 "data_obs"),
  ("process_name_specific",           "SingleElectron_Run2015D"),
  ("nof_files",                       2430),
  ("nof_events",                      106997220),
  ("use_HIP_mitigation_bTag",         False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                          True),
  ("triggers",                        ['1e']),
  ("reHLT",                           True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/kaehatah/SingleElectron/VHBB_HEPPY_H20_SingleElectron__Run2015D-16Dec2015-v1/160420_113346"),
        ("selection", "*"),
        ("blacklist", [8, 18, 24, 32, 33, 34, 36, 45, 54, 57, 59, 72, 80, 89, 91, 103, 107, 119, 123, 146, 154, 158, 189, 194, 215, 251, 260, 287, 292, 296, 312, 329, 335, 653, 854, 863, 906, 927, 928, 959, 970, 976, 987, 1005, 1008, 1016, 1027, 1066, 1116, 1130, 1131, 1144, 1154, 1160, 1170, 1171, 1178, 1191, 1194, 1236, 1241, 1256, 1311, 1340, 1344, 1368, 1426, 1433, 1449, 1517, 1615, 1624, 1631, 1634, 1645, 1663, 1674, 1678, 1699, 1705, 1744, 1767, 1789, 1909, 1919, 1923, 1937, 1946, 2039, 2046, 2079, 2125, 2127, 2131, 2135, 2141, 2147, 2158, 2161, 2164, 2186, 2190, 2193, 2227, 2239, 2279, 2290, 2314, 2341, 2364, 2370, 2377, 2392, 2395, 2396, 2406, 2430]),
      ]),
      OD([
        ("path",      "/hdfs/cms/store/user/kaehatah/SingleElectron/VHBB_HEPPY_H20_SingleElectron__Run2015D-16Dec2015-v1/160429_230512"),
        ("selection", "8,18,24,32,33,34,36,45,54,57,59,72,80,89,91,103,107,119,123,146,154,158,189,194,215,251,260,287,292,296,312,329,335,653,854,863,906,927,928,959,970,976,987,1005,1008,1016,1027,1066,1116,1130,1131,1144,1154,1160,1170,1171,1178,1191,1194,1236,1241,1256,1311,1340,1344,1368,1426,1433,1449,1517,1615,1624,1631,1634,1645,1663,1674,1678,1699,1705,1744,1767,1789,1909,1919,1923,1937,1946,2039,2046,2079,2125,2127,2131,2135,2141,2147,2158,2161,2164,2186,2190,2193,2227,2239,2279,2290,2314,2341,2364,2370,2377,2392,2395,2396,2406"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2015["/TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "TTW"),
  ("process_name_specific",           "TTWJetsToLNu"),
  ("nof_files",                       8),
  ("nof_events",                      128781),
  ("use_HIP_mitigation_bTag",         False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                          True),
  ("xsection",                        0.2043),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1e1mu', '1mu', '2e', '2mu']),
  ("reHLT",                           True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/kaehatah/TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/VHBB_HEPPY_V12_TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-Py8__fall15MAv2-pu25ns15v1_76r2as_v12-v1/160331_082745"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2015["/WZZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "Rares"),
  ("process_name_specific",           "WZZ"),
  ("nof_files",                       6),
  ("nof_events",                      219232),
  ("use_HIP_mitigation_bTag",         False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                          True),
  ("xsection",                        0.05565),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1e1mu', '1mu', '2e', '2mu']),
  ("reHLT",                           True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/kaehatah/WZZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8/VHBB_HEPPY_V12_WZZ_TuneCUETP8M1_13TeV-amcatnlo-Py8__fall15MAv2-pu25ns15v1_76r2as_v12-v1/160331_083728"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2015["/ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "TT"),
  ("process_name_specific",           "ST_tW_antitop_5f_inclusiveDecays"),
  ("nof_files",                       27),
  ("nof_events",                      999345),
  ("use_HIP_mitigation_bTag",         False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                          True),
  ("xsection",                        35.6),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1e1mu', '1mu', '2e', '2mu']),
  ("reHLT",                           True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/kaehatah/ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1/VHBB_HEPPY_V12_ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-Py8_TuneCUETP8M1__fall15MAv2-pu25ns15v1_76r2as_v12-v1/160331_080206"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2015["/SingleMuon/Run2015C_25ns-16Dec2015-v1/MINIAOD"] = OD([
  ("type",                            "data"),
  ("sample_category",                 "data_obs"),
  ("process_name_specific",           "SingleMuon_Run2015C"),
  ("nof_files",                       23),
  ("nof_events",                      767121),
  ("use_HIP_mitigation_bTag",         False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                          True),
  ("triggers",                        ['1mu']),
  ("reHLT",                           True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/kaehatah/SingleMuon/VHBB_HEPPY_H20_SingleMuon__Run2015C_25ns-16Dec2015-v1/160419_141430"),
        ("selection", "*"),
        ("blacklist", [12]),
      ]),
      OD([
        ("path",      "/hdfs/cms/store/user/kaehatah/SingleMuon/VHBB_HEPPY_H20_SingleMuon__Run2015C_25ns-16Dec2015-v1/160429_230148"),
        ("selection", "12"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2015["/SingleMuon/Run2015D-16Dec2015-v1/MINIAOD"] = OD([
  ("type",                            "data"),
  ("sample_category",                 "data_obs"),
  ("process_name_specific",           "SingleMuon_Run2015D"),
  ("nof_files",                       1758),
  ("nof_events",                      74024153),
  ("use_HIP_mitigation_bTag",         False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                          True),
  ("triggers",                        ['1mu']),
  ("reHLT",                           True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/kaehatah/SingleMuon/VHBB_HEPPY_H20_SingleMuon__Run2015D-16Dec2015-v1/160419_141549"),
        ("selection", "*"),
        ("blacklist", [2, 9, 13, 21, 25, 49, 57, 66, 68, 81, 87, 88, 91, 163, 189, 193, 284, 300, 329, 361, 367, 400, 428, 440, 464, 466, 468, 485, 494, 495, 531, 532, 552, 604, 617, 622, 651, 652, 691, 703, 722, 738, 746, 766, 767, 797, 802, 843, 848, 850, 859, 882, 888, 927, 1083, 1091, 1107, 1115, 1116, 1117, 1129, 1145, 1165, 1166, 1174, 1182, 1188, 1200, 1203, 1216, 1222, 1225, 1262, 1368, 1386, 1411, 1421, 1435, 1459, 1490, 1523, 1569, 1594, 1615, 1642, 1659, 1750, 1753]),
      ]),
      OD([
        ("path",      "/hdfs/cms/store/user/kaehatah/SingleMuon/VHBB_HEPPY_H20_SingleMuon__Run2015D-16Dec2015-v1/160429_230258"),
        ("selection", "2,9,13,21,25,49,57,66,68,81,87,88,91,163,189,193,284,300,329,361,367,400,428,440,464,466,468,485,494,495,531,532,552,604,617,622,651,652,691,703,722,738,746,766,767,797,802,843,848,850,859,882,888,927,1083,1091,1107,1115,1116,1117,1129,1145,1165,1166,1174,1182,1188,1200,1203,1216,1222,1225,1262,1368,1386,1411,1421,1435,1459,1490,1523,1569,1594,1615,1642,1659,1750,1753"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2015["/WZTo3LNu_TuneCUETP8M1_13TeV-powheg-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "EWK"),
  ("process_name_specific",           "WZTo3LNu"),
  ("nof_files",                       46),
  ("nof_events",                      2000944),
  ("use_HIP_mitigation_bTag",         False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                          True),
  ("xsection",                        4.102),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1e1mu', '1mu', '2e', '2mu']),
  ("reHLT",                           True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/kaehatah/WZTo3LNu_TuneCUETP8M1_13TeV-powheg-pythia8/VHBB_HEPPY_V12_WZTo3LNu_TuneCUETP8M1_13TeV-powheg-Py8__fall15MAv2-pu25ns15v1_76r2as_v12-v1/160331_080653"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2015["/WWTo2L2Nu_13TeV-powheg/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "EWK"),
  ("process_name_specific",           "WWTo2L2Nu"),
  ("nof_files",                       51),
  ("nof_events",                      1980756),
  ("use_HIP_mitigation_bTag",         False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                          True),
  ("xsection",                        10.481),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1e1mu', '1mu', '2e', '2mu']),
  ("reHLT",                           True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/kaehatah/WWTo2L2Nu_13TeV-powheg/VHBB_HEPPY_V12_WWTo2L2Nu_13TeV-powheg__fall15MAv2-pu25ns15v1_76r2as_v12-v1/160331_080804"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2015["/ttHToNonbb_M125_13TeV_powheg_pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "signal"),
  ("process_name_specific",           "ttHToNonbb_M125"),
  ("nof_files",                       91),
  ("nof_events",                      3944819),
  ("use_HIP_mitigation_bTag",         False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                          False),
  ("xsection",                        0.2151),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1e1mu', '1mu', '2e', '2mu']),
  ("reHLT",                           True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/kaehatah/ttHToNonbb_M125_13TeV_powheg_pythia8/VHBB_HEPPY_V12_ttHToNonbb_M125_13TeV_powheg_Py8__fall15MAv2-pu25ns15v1_76r2as_v12-v1/160330_172641"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2015["/TTJets_SingleLeptFromT_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "TT"),
  ("process_name_specific",           "TTJets_SingleLeptFromT"),
  ("nof_files",                       290),
  ("nof_events",                      11907528),
  ("use_HIP_mitigation_bTag",         False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                          True),
  ("xsection",                        182.0),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1e1mu', '1mu', '2e', '2mu']),
  ("reHLT",                           True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/kaehatah/TTJets_SingleLeptFromT_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/VHBB_HEPPY_V12_TTJets_SingleLeptFromT_TuneCUETP8M1_13TeV-madgraphMLM-Py8__fall15MAv2-pu25ns15v1_76r2as_v12-v1/160331_075445"),
        ("selection", "*"),
        ("blacklist", [203]),
      ]),
    ]
  ),
])
samples_2015["/GluGluHToZZTo4L_M125_13TeV_powheg2_JHUgenV6_pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "additional_signal_overlap"),
  ("process_name_specific",           "GluGluHToZZTo4L"),
  ("nof_files",                       25),
  ("nof_events",                      999315),
  ("use_HIP_mitigation_bTag",         False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                          True),
  ("xsection",                        0.0119),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1e1mu', '1mu', '2e', '2mu']),
  ("reHLT",                           True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/kaehatah/GluGluHToZZTo4L_M125_13TeV_powheg2_JHUgenV6_pythia8/VHBB_HEPPY_V12_GluGluHToZZTo4L_M125_13TeV_powheg2_JHUgenV6_Py8__fall15MAv2-pu25ns15v1_76r2as_v12-v1/160406_221911"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2015["/THW_Hincl_13TeV-madgraph-pythia8_TuneCUETP8M1/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "additional_signal_overlap"),
  ("process_name_specific",           "THW_Hincl"),
  ("nof_files",                       34),
  ("nof_events",                      1496575),
  ("use_HIP_mitigation_bTag",         False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                          True),
  ("xsection",                        0.01561),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1e1mu', '1mu', '2e', '2mu']),
  ("reHLT",                           True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/kaehatah/THW_Hincl_13TeV-madgraph-pythia8_TuneCUETP8M1/VHBB_HEPPY_V12_THW_Hincl_13TeV-madgraph-Py8_TuneCUETP8M1__fall15MAv2-pu25ns15v1_76r2as_v12-v1/160405_112509"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2015["/ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "Rares"),
  ("process_name_specific",           "ZGTo2LG"),
  ("nof_files",                       103),
  ("nof_events",                      3027737),
  ("use_HIP_mitigation_bTag",         False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                          True),
  ("xsection",                        131.3),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1e1mu', '1mu', '2e', '2mu']),
  ("reHLT",                           True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/kaehatah/ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/VHBB_HEPPY_V12_ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-Py8__fall15MAv2-pu25ns15v1_76r2as_v12-v1/160331_083018"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2015["/MuonEG/Run2015D-16Dec2015-v1/MINIAOD"] = OD([
  ("type",                            "data"),
  ("sample_category",                 "data_obs"),
  ("process_name_specific",           "MuonEG_Run2015D"),
  ("nof_files",                       286),
  ("nof_events",                      10749214),
  ("use_HIP_mitigation_bTag",         False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                          True),
  ("triggers",                        ['1e1mu']),
  ("reHLT",                           True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/kaehatah/MuonEG/VHBB_HEPPY_H20_MuonEG__Run2015D-16Dec2015-v1/160429_230034"),
        ("selection", "*"),
        ("blacklist", [10, 15, 16, 17, 20, 21, 23, 24, 30, 32, 33, 36, 42, 46, 56, 58, 59, 60, 66, 69, 85, 91, 92, 94, 95, 96, 97, 98, 105, 111, 113, 114, 121, 122, 123, 125, 126, 130, 133, 137, 142, 147, 149, 150, 151, 156, 158, 160, 161, 164, 166, 168, 169, 172, 174, 176, 178, 186, 187, 200, 203, 207, 216, 219, 225, 228, 231, 238, 246, 249, 251, 255, 256, 261, 264, 266, 268, 269, 271, 272, 273, 283]),
      ]),
      OD([
        ("path",      "/hdfs/cms/store/user/kaehatah/MuonEG/VHBB_HEPPY_H20_MuonEG__Run2015D-16Dec2015-v1/160419_141314"),
        ("selection", "10,15,16,17,20,21,23,24,30,32,33,36,42,46,56,58,59,60,66,69,85,91,92,94,95,96,97,98,105,111,113,114,121,122,123,125,126,130,133,137,142,147,149,150,151,156,158,160,161,164,166,168,169,172,174,176,178,186,187,200,203,207,216,219,225,228,231,238,246,249,251,255,256,261,264,266,268,269,271,272,273,283"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2015["/MuonEG/Run2015C_25ns-16Dec2015-v1/MINIAOD"] = OD([
  ("type",                            "data"),
  ("sample_category",                 "data_obs"),
  ("process_name_specific",           "MuonEG_Run2015C"),
  ("nof_files",                       6),
  ("nof_events",                      97740),
  ("use_HIP_mitigation_bTag",         False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                          True),
  ("triggers",                        ['1e1mu']),
  ("reHLT",                           True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/kaehatah/MuonEG/VHBB_HEPPY_H20_MuonEG__Run2015C_25ns-16Dec2015-v1/160419_141135"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2015["/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "signal"),
  ("process_name_specific",           "ttHJetToNonbb_M125"),
  ("nof_files",                       186),
  ("nof_events",                      2420010),
  ("use_HIP_mitigation_bTag",         False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                          True),
  ("xsection",                        0.2151),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1e1mu', '1mu', '2e', '2mu']),
  ("reHLT",                           True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/kaehatah/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/VHBB_HEPPY_V12_ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_Py8_mWCutfix__fall15MAv2-pu25ns15v1_76r2as_v12-v1/160330_172426"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2015["/ttHJetToNonbb_M120_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v2/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "signal"),
  ("process_name_specific",           "ttHJetToNonbb_M120"),
  ("nof_files",                       13),
  ("nof_events",                      119707),
  ("use_HIP_mitigation_bTag",         False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                          False),
  ("xsection",                        0.0),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1e1mu', '1mu', '2e', '2mu']),
  ("reHLT",                           True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/kaehatah/ttHJetToNonbb_M120_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/VHBB_HEPPY_V12_ttHJetToNonbb_M120_13TeV_amcatnloFXFX_madspin_Py8_mWCutfix__fall15MAv2-pu25ns15v1_76r2as_v12-v2/160330_172315"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
