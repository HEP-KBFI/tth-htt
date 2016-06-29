from collections import OrderedDict as OD

samples = OD()

samples["/THW_Hincl_13TeV-madgraph-pythia8_TuneCUETP8M1/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"] = OD([
  ("type", "mc"),
  ("sample_category", "additional_signal_overlap"),
  ("process_name_specific", "THW_Hincl"),
  ("nof_files", 34),
  ("nof_events", 1496000),
  ("use_it", True),
  ("xsection", 0.01561),
  ("triggers", [ "1e", "1mu" ]),
  ("local_paths",
    [
      OD([
        ("path", "/hdfs/cms/store/user/kaehatah/THW_Hincl_13TeV-madgraph-pythia8_TuneCUETP8M1/VHBB_HEPPY_V12_THW_Hincl_13TeV-madgraph-Py8_TuneCUETP8M1__fall15MAv2-pu25ns15v1_76r2as_v12-v1/160405_112509"),
        ("selection", "*"),
      ]),
    ]
  )
])
samples["/GluGluHToZZTo4L_M125_13TeV_powheg2_JHUgenV6_pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"] = OD([
  ("type", "mc"),
  ("sample_category", "additional_signal_overlap"),
  ("process_name_specific", "GluGluHToZZTo4L"),
  ("nof_files", 25),
  ("nof_events", 999000),
  ("use_it", True),
  ("xsection", 0.0119),
  ("triggers", [ "1e", "1mu" ]),	
  ("local_paths",
    [
      OD([
        ("path", "/hdfs/cms/store/user/kaehatah/GluGluHToZZTo4L_M125_13TeV_powheg2_JHUgenV6_pythia8/VHBB_HEPPY_V12_GluGluHToZZTo4L_M125_13TeV_powheg2_JHUgenV6_Py8__fall15MAv2-pu25ns15v1_76r2as_v12-v1/160406_221911"),
        ("selection", "*"),
      ]),
    ]
  )
])
samples["/TTJets_SingleLeptFromTbar_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v2/MINIAODSIM"] = OD([
  ("type", "mc"),
  ("sample_category", "TT"),
  ("process_name_specific", "TTJets_SingleLeptFromTbar"),
  ("nof_files", 275),
  ("nof_events", 11957090),
  ("use_it", True),
  ("xsection", 182.),
  ("triggers", [ "1e", "1mu" ]),
  ("local_paths",
    [
      OD([
        ("path", "/hdfs/cms/store/user/kaehatah/TTJets_SingleLeptFromTbar_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/VHBB_HEPPY_V12_TTJets_SingleLeptFromTbar_TuneCUETP8M1_13TeV-madgraphMLM-Py8__fall15MAv2-pu25ns15v1_76r2as_v12-v2/160419_134531"),
        ("selection", "*"),
      ]),
      OD([
        ("path", "/hdfs/cms/store/user/kaehatah/TTJets_SingleLeptFromTbar_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/VHBB_HEPPY_V12_TTJets_SingleLeptFromTbar_TuneCUETP8M1_13TeV-madgraphMLM-Py8__fall15MAv2-pu25ns15v1_76r2as_v12-v2/160501_160405"),
        ("selection", "166,223,269"),
      ]),
    ]
  )
])
samples["/TTJets_SingleLeptFromT_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"] = OD([
  ("type", "mc"),
  ("sample_category", "TT"),
  ("process_name_specific", "TTJets_SingleLeptFromT"),
  ("nof_files", 290),
  ("nof_events", 11953980),
  ("use_it", True),
  ("xsection", 182.),
  ("triggers", [ "1e", "1mu" ]),
  ("local_paths",
    [
      OD([
        ("path", "/hdfs/cms/store/user/kaehatah/TTJets_SingleLeptFromT_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/VHBB_HEPPY_V12_TTJets_SingleLeptFromT_TuneCUETP8M1_13TeV-madgraphMLM-Py8__fall15MAv2-pu25ns15v1_76r2as_v12-v1/160331_075445"),
        ("selection", "*"),
      ]),
    ]
  )
])
samples["/TTJets_DiLept_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"] = OD([
  ("type", "mc"),
  ("sample_category", "TT"),
  ("process_name_specific", "TTJets_DiLept"),
  ("nof_files", 149),
  ("nof_events", 6102376),
  ("use_it", True),
  ("xsection", 87.3),
  ("triggers", [ "1e", "1mu" ]),
  ("local_paths",
    [
      OD([
        ("path", "/hdfs/cms/store/user/kaehatah/TTJets_DiLept_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/VHBB_HEPPY_V12_TTJets_DiLept_TuneCUETP8M1_13TeV-madgraphMLM-Py8__fall15MAv2-pu25ns15v1_76r2as_v12-v1/160331_075552"),
        ("selection", "*"),
      ]),
    ]
  )
])
samples["/DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"] = OD([
  ("type", "mc"),
  ("sample_category", "EWK"),
  ("process_name_specific", "DYJetsToLL_M-10to50"),
  ("nof_files", 753),
  ("nof_events", 30899063),
  ("use_it", True),
  ("xsection", 18610.),
  ("triggers", [ "1e", "1mu" ]),
  ("local_paths",
    [
      OD([
        ("path", "/hdfs/cms/store/user/kaehatah/DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/VHBB_HEPPY_V12_DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-amcatnloFXFX-Py8__fall15MAv2-pu25ns15v1_76r2as_v12-v1/160331_075706"),
        ("selection", "*"),
      ])
    ]
  )
])
samples["/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"] = OD([
  ("type", "mc"),
  ("sample_category", "EWK"),
  ("process_name_specific", "DYJetsToLL_M-50"),
  ("nof_files", 226),
  ("nof_events", 9004328),
  ("use_it", True),
  ("xsection", 6025.2),
  ("triggers", [ "1e", "1mu" ]),
  ("local_paths",
    [
      OD([
        ("path", "/hdfs/cms/store/user/kaehatah/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/VHBB_HEPPY_V12_DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-Py8__fall15MAv2-pu25ns15v1_76r2as_v12-v1/160331_075827"),
        ("selection", "*"),
      ])
    ]
  )
])
samples["/WJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"] = OD([
  ("type", "mc"),
  ("sample_category", "EWK"),
  ("process_name_specific", "WJetsToLNu"),
  ("nof_files", 595),
  ("nof_events", 24156124),
  ("use_it", True),
  ("xsection", 61526.7),
  ("triggers", [ "1e", "1mu" ]),
  ("local_paths",
    [
      OD([
        ("path", "/hdfs/cms/store/user/kaehatah/WJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/VHBB_HEPPY_V12_WJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-Py8__fall15MAv2-pu25ns15v1_76r2as_v12-v1/160331_075944"),
        ("selection", "*"),
      ])
    ]
  )
])
samples["/ST_tW_top_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"] = OD([
  ("type", "mc"),
  ("sample_category", "TT"),
  ("process_name_specific", "ST_tW_top_5f_inclusiveDecays"),
  ("nof_files", 23),
  ("nof_events", 1000000),
  ("use_it", True),
  ("xsection", 35.6),
  ("triggers", [ "1e", "1mu" ]),
  ("local_paths",
    [
      OD([
        ("path", "/hdfs/cms/store/user/kaehatah/ST_tW_top_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1/VHBB_HEPPY_V12_ST_tW_top_5f_inclusiveDecays_13TeV-powheg-Py8_TuneCUETP8M1__fall15MAv2-pu25ns15v1_76r2as_v12-v1/160331_080051"),
        ("selection", "*"),
      ])
    ]
  )
])
samples["/ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"] = OD([
  ("type", "mc"),
  ("sample_category", "TT"),
  ("process_name_specific", "ST_tW_antitop_5f_inclusiveDecays"),
  ("nof_files", 27),
  ("nof_events", 999400),
  ("use_it", True),
  ("xsection", 35.6),
  ("triggers", [ "1e", "1mu" ]),
  ("local_paths",
    [
      OD([
        ("path", "/hdfs/cms/store/user/kaehatah/ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1/VHBB_HEPPY_V12_ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-Py8_TuneCUETP8M1__fall15MAv2-pu25ns15v1_76r2as_v12-v1/160331_080206"),
        ("selection", "*"),
      ])
    ]
  )
])
samples["/ST_t-channel_4f_leptonDecays_13TeV-amcatnlo-pythia8_TuneCUETP8M1/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"] = OD([
  ("type", "mc"),
  ("sample_category", "TT"),
  ("process_name_specific", "ST_t-channel_4f_leptonDecays"),
  ("nof_files", 478),
  ("nof_events", 19938230),
  ("use_it", True),
  ("xsection", 70.69),
  ("triggers", [ "1e", "1mu" ]),
  ("local_paths",
    [
      OD([
        ("path", "/hdfs/cms/store/user/kaehatah/ST_t-channel_4f_leptonDecays_13TeV-amcatnlo-pythia8_TuneCUETP8M1/VHBB_HEPPY_V12_ST_t-channel_4f_leptonDecays_13TeV-amcatnlo-Py8_TuneCUETP8M1__fall15MAv2-pu25ns15v1_76r2as_v12-v1/160419_140037"),
        ("selection", "*"),
      ]),
      OD([
        ("path", "/hdfs/cms/store/user/kaehatah/ST_t-channel_4f_leptonDecays_13TeV-amcatnlo-pythia8_TuneCUETP8M1/VHBB_HEPPY_V12_ST_t-channel_4f_leptonDecays_13TeV-amcatnlo-Py8_TuneCUETP8M1__fall15MAv2-pu25ns15v1_76r2as_v12-v1/160501_160520"),
        ("selection", "100,191,226,264,311,329,456"),
      ])
    ]
  )
])
samples["/ST_t-channel_4f_leptonDecays_13TeV-amcatnlo-pythia8_TuneCUETP8M1/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12_ext1-v1/MINIAODSIM"] = OD([
  ("type", "mc"),
  ("sample_category", "TT"),
  ("process_name_specific", "ST_t-channel_4f_leptonDecays_ext1"),
  ("nof_files", 690),
  ("nof_events", 29206391),
  ("use_it", True),
  ("xsection", 70.69),
  ("triggers", [ "1e", "1mu" ]),
  ("local_paths",
    [
      OD([
        ("path", "/hdfs/cms/store/user/kaehatah/ST_t-channel_4f_leptonDecays_13TeV-amcatnlo-pythia8_TuneCUETP8M1/VHBB_HEPPY_V12_ST_t-channel_4f_leptonDecays_13TeV-amcatnlo-Py8_TuneCUETP8M1__fall15MAv2-pu25ns15v1_76r2as_v12_ext1-v1/160331_080437"),
        ("selection", "*"),
      ]),
      OD([
        ("path", "/hdfs/cms/store/user/kaehatah/ST_t-channel_4f_leptonDecays_13TeV-amcatnlo-pythia8_TuneCUETP8M1/VHBB_HEPPY_V12_ST_t-channel_4f_leptonDecays_13TeV-amcatnlo-Py8_TuneCUETP8M1__fall15MAv2-pu25ns15v1_76r2as_v12_ext1-v1/160501_160636"),
        ("selection", "196,244,267,306,310,358,376,379,390,406,409,449,452,454,471,516,534,546,560,564,576,584,585,601,621,625,633,641,646,689"),
      ])
    ]
  )
])
samples["/ST_s-channel_4f_leptonDecays_13TeV-amcatnlo-pythia8_TuneCUETP8M1/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v2/MINIAODSIM"] = OD([
  ("type", "mc"),
  ("sample_category", "TT"),
  ("process_name_specific", "ST_s-channel_4f_leptonDecays"),
  ("nof_files", 24),
  ("nof_events", 998400),
  ("use_it", True),
  ("xsection", 3.75),
  ("triggers", [ "1e", "1mu" ]),
  ("local_paths",
    [
      OD([
        ("path", "/hdfs/cms/store/user/kaehatah/ST_s-channel_4f_leptonDecays_13TeV-amcatnlo-pythia8_TuneCUETP8M1/VHBB_HEPPY_V12_ST_s-channel_4f_leptonDecays_13TeV-amcatnlo-Py8_TuneCUETP8M1__fall15MAv2-pu25ns15v1_76r2as_v12-v2/160331_080546"),
        ("selection", "*"),
      ])
    ]
  )
])
samples["/WZTo3LNu_TuneCUETP8M1_13TeV-powheg-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"] = OD([
  ("type", "mc"),
  ("sample_category", "EWK"),
  ("process_name_specific", "WZTo3LNu"),
  ("nof_files", 46),
  ("nof_events", 2000000),
  ("use_it", True),
  ("xsection", 4.102),
  ("triggers", [ "1e", "1mu" ]),
  ("local_paths",
    [
      OD([
        ("path", "/hdfs/cms/store/user/kaehatah/WZTo3LNu_TuneCUETP8M1_13TeV-powheg-pythia8/VHBB_HEPPY_V12_WZTo3LNu_TuneCUETP8M1_13TeV-powheg-Py8__fall15MAv2-pu25ns15v1_76r2as_v12-v1/160331_080653"),
        ("selection", "*"),
      ])
    ]
  )
])
samples["/WWTo2L2Nu_13TeV-powheg/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"] = OD([
  ("type", "mc"),
  ("sample_category", "EWK"),
  ("process_name_specific", "WWTo2L2Nu"),
  ("nof_files", 51),
  ("nof_events", 1979988),
  ("use_it", True),
  ("xsection", 10.481),
  ("triggers", [ "1e", "1mu" ]),
  ("local_paths",
    [
      OD([
        ("path", "/hdfs/cms/store/user/kaehatah/WWTo2L2Nu_13TeV-powheg/VHBB_HEPPY_V12_WWTo2L2Nu_13TeV-powheg__fall15MAv2-pu25ns15v1_76r2as_v12-v1/160331_080804"),
        ("selection", "*"),
      ])
    ]
  )
])
samples["/ZZTo4L_13TeV_powheg_pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"] = OD([
  ("type", "mc"),
  ("sample_category", "EWK"),
  ("process_name_specific", "ZZTo4L"),
  ("nof_files", 154),
  ("nof_events", 6669188),
  ("use_it", True),
  ("xsection", 1.256),
  ("triggers", [ "1e", "1mu" ]),
  ("local_paths",
    [
      OD([
        ("path", "/hdfs/cms/store/user/kaehatah/ZZTo4L_13TeV_powheg_pythia8/VHBB_HEPPY_V12_ZZTo4L_13TeV_powheg_Py8__fall15MAv2-pu25ns15v1_76r2as_v12-v1/160331_080924"),
        ("selection", "*"),
      ])
    ]
  )
])
samples["/TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"] = OD([
  ("type", "mc"),
  ("sample_category", "TTW"),
  ("process_name_specific", "TTWJetsToLNu"),
  ("nof_files", 8),
  ("nof_events", 250307),
  ("use_it", True),
  ("xsection", 0.2043),
  ("triggers", [ "1e", "1mu" ]),
  ("local_paths",
    [
      OD([
        ("path", "/hdfs/cms/store/user/kaehatah/TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/VHBB_HEPPY_V12_TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-Py8__fall15MAv2-pu25ns15v1_76r2as_v12-v1/160331_082745"),
        ("selection", "*"),
      ])
    ]
  )
])
samples["/WGToLNuG_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"] = OD([
  ("type", "mc"),
  ("sample_category", "Rares"), # previously: background_samples_yieldshapes
  ("process_name_specific", "WGToLNuG"),
  ("nof_files", 146),
  ("nof_events", 6102260),
  ("use_it", True),
  ("xsection", 585.8),
  ("triggers", [ "1e", "1mu" ]),
  ("local_paths",
    [
      OD([
        ("path", "/hdfs/cms/store/user/kaehatah/WGToLNuG_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/VHBB_HEPPY_V12_WGToLNuG_TuneCUETP8M1_13TeV-madgraphMLM-Py8__fall15MAv2-pu25ns15v1_76r2as_v12-v1/160331_082909"),
        ("selection", "*"),
      ])
    ]
  )
])
samples["/ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"] = OD([
  ("type", "mc"),
  ("sample_category", "Rares"), # previously: background_samples_yieldshapes
  ("process_name_specific", "ZGTo2LG"),
  ("nof_files", 103),
  ("nof_events", 4424816),
  ("use_it", True),
  ("xsection", 131.3),
  ("triggers", [ "1e", "1mu" ]),
  ("local_paths",
    [
      OD([
        ("path", "/hdfs/cms/store/user/kaehatah/ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/VHBB_HEPPY_V12_ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-Py8__fall15MAv2-pu25ns15v1_76r2as_v12-v1/160331_083018"),
        ("selection", "*"),
      ])
    ]
  )
])
samples["/TGJets_TuneCUETP8M1_13TeV_amcatnlo_madspin_pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"] = OD([
  ("type", "mc"),
  ("sample_category", "Rares"), # previously: background_samples_yieldshapes
  ("process_name_specific", "TGJets"),
  ("nof_files", 9),
  ("nof_events", 280100),
  ("use_it", True),
  ("xsection", 2.967),
  ("triggers", [ "1e", "1mu" ]),
  ("local_paths",
    [
      OD([
        ("path", "/hdfs/cms/store/user/kaehatah/TGJets_TuneCUETP8M1_13TeV_amcatnlo_madspin_pythia8/VHBB_HEPPY_V12_TGJets_TuneCUETP8M1_13TeV_amcatnlo_madspin_Py8__fall15MAv2-pu25ns15v1_76r2as_v12-v1/160331_083126"),
        ("selection", "*"),
      ])
    ]
  )
])
samples["/TTGJets_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"] = OD([
  ("type", "mc"),
  ("sample_category", "Rares"), # previously: background_samples_yieldshapes
  ("process_name_specific", "TTGJets"),
  ("nof_files", 118),
  ("nof_events", 4874116),
  ("use_it", True),
  ("xsection", 3.697),
  ("triggers", [ "1e", "1mu" ]),
  ("local_paths",
    [
      OD([
        ("path", "/hdfs/cms/store/user/kaehatah/TTGJets_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/VHBB_HEPPY_V12_TTGJets_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-Py8__fall15MAv2-pu25ns15v1_76r2as_v12-v1/160331_083238"),
        ("selection", "*"),
      ])
    ]
  )
])
samples["/WpWpJJ_EWK-QCD_TuneCUETP8M1_13TeV-madgraph-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"] = OD([
  ("type", "mc"),
  ("sample_category", "Rares"), # previously: background_samples_yieldshapes
  ("process_name_specific", "WpWpJJ_EWK-QCD"),
  ("nof_files", 5),
  ("nof_events", 118350),
  ("use_it", True),
  ("xsection", 0.03711),
  ("triggers", [ "1e", "1mu" ]),
  ("local_paths",
    [
      OD([
        ("path", "/hdfs/cms/store/user/kaehatah/WpWpJJ_EWK-QCD_TuneCUETP8M1_13TeV-madgraph-pythia8/VHBB_HEPPY_V12_WpWpJJ_EWK-QCD_TuneCUETP8M1_13TeV-madgraph-Py8__fall15MAv2-pu25ns15v1_76r2as_v12-v1/160331_083346"),
        ("selection", "*"),
      ])
    ]
  )
])
samples["/WZZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"] = OD([
  ("type", "mc"),
  ("sample_category", "Rares"),
  ("process_name_specific", "WZZ"),
  ("nof_files", 6),
  ("nof_events", 249800),
  ("use_it", True),
  ("xsection", 0.05565),
  ("triggers", [ "1e", "1mu" ]),
  ("local_paths",
    [
      OD([
        ("path", "/hdfs/cms/store/user/kaehatah/WZZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8/VHBB_HEPPY_V12_WZZ_TuneCUETP8M1_13TeV-amcatnlo-Py8__fall15MAv2-pu25ns15v1_76r2as_v12-v1/160331_083728"),
        ("selection", "*"),
      ])
    ]
  )
])
samples["/WW_DoubleScattering_13TeV-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"] = OD([
  ("type", "mc"),
  ("sample_category", "Rares"),
  ("process_name_specific", "WW_DoubleScattering"),
  ("nof_files", 21),
  ("nof_events", 844954),
  ("use_it", True),
  ("xsection", 1.64),
  ("triggers", [ "1e", "1mu" ]),
  ("local_paths",
    [
      OD([
        ("path", "/hdfs/cms/store/user/kaehatah/WW_DoubleScattering_13TeV-pythia8/VHBB_HEPPY_V12_WW_DoubleScattering_13TeV-Py8__fall15MAv2-pu25ns15v1_76r2as_v12-v1/160331_083838"),
        ("selection", "*"),
      ])
    ]
  )
])
samples["/tZq_ll_4f_13TeV-amcatnlo-pythia8_TuneCUETP8M1/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"] = OD([
  ("type", "mc"),
  ("sample_category", "Rares"),
  ("process_name_specific", "tZq_ll_4f"),
  ("nof_files", 75),
  ("nof_events", 2996000),
  ("use_it", True),
  ("xsection", 0.0758),
  ("triggers", [ "1e", "1mu" ]),
  ("local_paths",
    [
      OD([
        ("path", "/hdfs/cms/store/user/kaehatah/tZq_ll_4f_13TeV-amcatnlo-pythia8_TuneCUETP8M1/VHBB_HEPPY_V12_tZq_ll_4f_13TeV-amcatnlo-Py8_TuneCUETP8M1__fall15MAv2-pu25ns15v1_76r2as_v12-v1/160331_083947"),
        ("selection", "*"),
      ])
    ]
  )
])
samples["/TTTT_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"] = OD([
  ("type", "mc"),
  ("sample_category", "Rares"),
  ("process_name_specific", "TTTT"),
  ("nof_files", 7),
  ("nof_events", 250000),
  ("use_it", True),
  ("xsection", 0.009103),
  ("triggers", [ "1e", "1mu" ]),
  ("local_paths",
    [
      OD([
        ("path", "/hdfs/cms/store/user/kaehatah/TTTT_TuneCUETP8M1_13TeV-amcatnlo-pythia8/VHBB_HEPPY_V12_TTTT_TuneCUETP8M1_13TeV-amcatnlo-Py8__fall15MAv2-pu25ns15v1_76r2as_v12-v1/160331_084059"),
        ("selection", "*"),
      ])
    ]
  )
])
samples["/TTTT_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12_ext1-v1/MINIAODSIM"] = OD([
  ("type", "mc"),
  ("sample_category", "Rares"),
  ("process_name_specific", "TTTT_ext1"),
  ("nof_files", 24),
  ("nof_events", 960521),
  ("use_it", True),
  ("xsection", 0.009103),
  ("triggers", [ "1e", "1mu" ]),
  ("local_paths",
    [
      OD([
        ("path", "/hdfs/cms/store/user/kaehatah/TTTT_TuneCUETP8M1_13TeV-amcatnlo-pythia8/VHBB_HEPPY_V12_TTTT_TuneCUETP8M1_13TeV-amcatnlo-Py8__fall15MAv2-pu25ns15v1_76r2as_v12_ext1-v1/160513_121601"),
        ("selection", "*")
      ])
    ]
  )
])
samples["/TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"] = OD([
  ("type", "mc"),
  ("sample_category", "TTZ"),
  ("process_name_specific", "TTZToLLNuNu"),
  ("nof_files", 10),
  ("nof_events", 394200),
  ("use_it", True),
  ("xsection", 0.2529),
  ("triggers", [ "1e", "1mu" ]),
  ("local_paths",
    [
      OD([
        ("path", "/hdfs/cms/store/user/kaehatah/TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-pythia8/VHBB_HEPPY_V12_TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-Py8__fall15MAv2-pu25ns15v1_76r2as_v12-v1/160513_120014"),
        ("selection", "*")
      ])
    ]
  )
])
samples["/ttHJetToNonbb_M120_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v2/MINIAODSIM"] = OD([
  ("type", "mc"),
  ("sample_category", "signal"),
  ("process_name_specific", "ttHJetToNonbb_M120"),
  ("nof_files", 13),
  ("nof_events", 398492),
  ("use_it", False), # xsection missing
  ("xsection", 0.),
  ("triggers", [ "1e", "1mu" ]),
  ("local_paths",
    [
      OD([
        ("path", "/hdfs/cms/store/user/kaehatah/ttHJetToNonbb_M120_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/VHBB_HEPPY_V12_ttHJetToNonbb_M120_13TeV_amcatnloFXFX_madspin_Py8_mWCutfix__fall15MAv2-pu25ns15v1_76r2as_v12-v2/160330_172315"),
        ("selection", "*"),
      ])
    ]
  )
])
samples["/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"] = OD([
  ("type", "mc"),
  ("sample_category", "signal"),
  ("process_name_specific", "ttHJetToNonbb_M125"),
  ("nof_files", 186),
  ("nof_events", 8139275),
  ("use_it", True),
  ("xsection", 0.2151), # (1 - BR(ttH -> bb)) * sigma(ttH) = (1 - 0.577) * 0.5085 pb according to https://twiki.cern.ch/twiki/bin/view/LHCPhysics/CrossSections#Higgs_cross_sections_and_decay_b 
  ("triggers", [ "1e", "1mu" ]),
  ("local_paths",
    [
      OD([
        ("path", "/hdfs/cms/store/user/kaehatah/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/VHBB_HEPPY_V12_ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_Py8_mWCutfix__fall15MAv2-pu25ns15v1_76r2as_v12-v1/160330_172426"),
        ("selection", "*"),
      ])
    ]
  )
])
samples["/ttHJetToNonbb_M130_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"] = OD([
  ("type", "mc"),
  ("sample_category", "signal"),
  ("process_name_specific", "ttHJetToNonbb_M130"),
  ("nof_files", 11),
  ("nof_events", 379065),
  ("use_it", False), # xsection missing
  ("xsection", 0.),
  ("triggers", [ "1e", "1mu" ]),
  ("local_paths",
    [
      OD([
        ("path", "/hdfs/cms/store/user/kaehatah/ttHJetToNonbb_M130_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/VHBB_HEPPY_V12_ttHJetToNonbb_M130_13TeV_amcatnloFXFX_madspin_Py8_mWCutfix__fall15MAv2-pu25ns15v1_76r2as_v12-v1/160330_172533"),
        ("selection", "*"),
      ])
    ]
  )
])
samples["/ttHToNonbb_M125_13TeV_powheg_pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"] = OD([
  ("type", "mc"),
  ("sample_category", "signal"),
  ("process_name_specific", "ttHToNonbb_M125"),
  ("nof_files", 91),
  ("nof_events", 3945824),
  ("use_it", False),
  ("xsection", 0.2151), # (1 - BR(ttH -> bb)) * sigma(ttH) = (1 - 0.577) * 0.5085 pb according to https://twiki.cern.ch/twiki/bin/view/LHCPhysics/CrossSections#Higgs_cross_sections_and_decay_b
  ("triggers", [ "1e", "1mu" ]),
  ("local_paths",
    [
      OD([
        ("path", "/hdfs/cms/store/user/kaehatah/ttHToNonbb_M125_13TeV_powheg_pythia8/VHBB_HEPPY_V12_ttHToNonbb_M125_13TeV_powheg_Py8__fall15MAv2-pu25ns15v1_76r2as_v12-v1/160330_172641"),
        ("selection", "*"),
      ])
    ]
  )
])
samples["/SingleMuon/Run2015C_25ns-16Dec2015-v1/MINIAOD"] = OD([
  ("type", "data"),
  ("sample_category", "data_obs"),
  ("process_name_specific", "SingleMuon_Run2015C"),
  ("nof_files", 23),
  ("nof_events", 1341179),
  ("use_it", True),
  ("triggers", [ "1mu" ]),
  ("local_paths",
    [
      OD([
        ("path", "/hdfs/cms/store/user/kaehatah/SingleMuon/VHBB_HEPPY_H20_SingleMuon__Run2015C_25ns-16Dec2015-v1/160419_141430"),
        ("selection", "*"),
      ]),
      OD([
        ("path", "/hdfs/cms/store/user/kaehatah/SingleMuon/VHBB_HEPPY_H20_SingleMuon__Run2015C_25ns-16Dec2015-v1/160429_230148"),
        ("selection", "12"),
      ]),
    ]
  )
])
samples["/SingleMuon/Run2015D-16Dec2015-v1/MINIAOD"] = OD([
  ("type", "data"),
  ("sample_category", "data_obs"),
  ("process_name_specific", "SingleMuon_Run2015D"),
  ("nof_files", 1758),
  ("nof_events", 91999861),
  ("use_it", True),
  ("triggers", [ "1mu" ]),
  ("local_paths",
    [
      OD([
        ("path", "/hdfs/cms/store/user/kaehatah/SingleMuon/VHBB_HEPPY_H20_SingleMuon__Run2015D-16Dec2015-v1/160419_141549"),
        ("selection", "*"),
      ]),
      OD([
        ("path", "/hdfs/cms/store/user/kaehatah/SingleMuon/VHBB_HEPPY_H20_SingleMuon__Run2015D-16Dec2015-v1/160429_230258"),
        ("selection", "2,9,13,21,25,49,57,66,68,81,87,88,91,163,189,193,284,300,329,361,367,400,428,440,464,466,468,485,494,495,531,"
         "532,552,604,617,622,651,652,691,703,722,738,746,766,767,797,802,843,848,850,859,882,888,927,1083,1091,1107,1115,1116,1117,"
         "1129,1145,1165,1166,1174,1182,1188,1200,1203,1216,1222,1225,1262,1368,1386,1411,1421,1435,1459,1490,1523,1569,1594,1615,1642,"
         "1659,1750,1753"),
      ]),
    ]
  )
])
samples["/SingleElectron/Run2015C_25ns-16Dec2015-v1/MINIAOD"] = OD([
  ("type", "data"),
  ("sample_category", "data_obs"),
  ("process_name_specific", "SingleElectron_Run2015C"),
  ("nof_files", 21),
  ("nof_events", 837157),
  ("use_it", True),
  ("triggers", [ "1e" ]),
  ("local_paths",
    [
      OD([
        ("path", "/hdfs/cms/store/user/kaehatah/SingleElectron/VHBB_HEPPY_H20_SingleElectron__Run2015C_25ns-16Dec2015-v1/160419_132242"),
        ("selection", "*"),
      ]),
      OD([
        ("path", "/hdfs/cms/store/user/kaehatah/SingleElectron/VHBB_HEPPY_H20_SingleElectron__Run2015C_25ns-16Dec2015-v1/160429_230407"),
        ("selection", "14"),
      ]),
    ]
  )
])
samples["/SingleElectron/Run2015D-16Dec2015-v1/MINIAOD"] = OD([
  ("type", "data"),
  ("sample_category", "data_obs"),
  ("process_name_specific", "SingleElectron_Run2015D"),
  ("nof_files", 2430),
  ("nof_events", 134140420),
  ("use_it", True),
  ("triggers", [ "1e" ]),
  ("local_paths",
    [
      OD([
        ("path", "/hdfs/cms/store/user/kaehatah/SingleElectron/VHBB_HEPPY_H20_SingleElectron__Run2015D-16Dec2015-v1/160420_113346"),
        ("selection", "*"),
      ]),
      OD([
        ("path", "/hdfs/cms/store/user/kaehatah/SingleElectron/VHBB_HEPPY_H20_SingleElectron__Run2015D-16Dec2015-v1/160429_230512"),
        ("selection", "8,18,24,32,33,34,36,45,54,57,59,72,80,89,91,103,107,119,123,146,154,158,189,194,215,251,260,287,292,296,312,329,335,"
         "653,854,863,906,927,928,959,970,976,987,1005,1008,1016,1027,1066,1116,1130,1131,1144,1154,1160,1170,1171,1178,1191,1194,1236,1241,"
         "1256,1311,1340,1344,1368,1426,1433,1449,1517,1615,1624,1631,1634,1645,1663,1674,1678,1699,1705,1744,1767,1789,1909,1919,1923,1937,"
         "1946,2039,2046,2079,2125,2127,2131,2135,2141,2147,2158,2161,2164,2186,2190,2193,2227,2239,2279,2290,2314,2341,2364,2370,2377,2392,"
         "2395,2396,2406,2430"),
      ]),
    ]
  )
])
