from collections import OrderedDict as OD

samples = OD()

samples["/DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DYJetsToLL_M-10to50"),
  ("nof_files",             369),
  ("nof_events",            30915886),
  ("use_it",                True),
  ("xsection",              18610.000000),
  ("triggers",              [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/lucia/VHBBHeppyV24bis/DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/VHBB_HEPPY_V24bis_DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-amcatnloFXFX-Py8__spr16MAv2-puspr16_80r2as_2016_MAv2_v0-v1/160911_223234"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples["/GluGluHToZZTo4L_M125_13TeV_powheg2_JHUgenV6_pythia8/RunIISpring16MiniAODv2-PUSpring16RAWAODSIM_reHLT_80X_mcRun2_asymptotic_v14-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "additional_signal_overlap"),
  ("process_name_specific", "GluGluHToZZTo4L"),
  ("nof_files",             15),
  ("nof_events",            969200),
  ("use_it",                True),
  ("xsection",              0.011900),
  ("triggers",              [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/lucia/VHBBHeppyV24bis/GluGluHToZZTo4L_M125_13TeV_powheg2_JHUgenV6_pythia8/VHBB_HEPPY_V24bis_GluGluHToZZTo4L_M125_13TeV_powheg2_JHUgenV6_Py8__spr16MAv2-puspr16_HLT_80r2as_v14-v1/160911_224902"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples["/ST_tW_top_5f_NoFullyHadronicDecays_13TeV-powheg_TuneCUETP8M1/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "TT"),
  ("process_name_specific", "ST_tW_top_5f_NoFullyHadronicDecays"),
  ("nof_files",             66),
  ("nof_events",            5405726),
  ("use_it",                True),
  ("xsection",              35.600000),
  ("triggers",              [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/lucia/VHBBHeppyV24bis/ST_tW_top_5f_NoFullyHadronicDecays_13TeV-powheg_TuneCUETP8M1/VHBB_HEPPY_V24bis_ST_tW_top_5f_NoFullyHadronicDecays_13TeV-powheg_TuneCUETP8M1__spr16MAv2-puspr16_80r2as_2016_MAv2_v0-v1/160911_223856"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples["/TGJets_TuneCUETP8M1_13TeV_amcatnlo_madspin_pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0_ext1-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "Rares"),
  ("process_name_specific", "TGJets_ext1"),
  ("nof_files",             19),
  ("nof_events",            1535543),
  ("use_it",                True),
  ("xsection",              2.967000),
  ("triggers",              [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/lucia/VHBBHeppyV24bis/TGJets_TuneCUETP8M1_13TeV_amcatnlo_madspin_pythia8/VHBB_HEPPY_V24bis_TGJets_TuneCUETP8M1_13TeV_amcatnlo_madspin_Py8__spr16MAv2-puspr16_80r2as_2016_MAv2_v0_ext1-v1/160911_224639"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples["/THW_Hincl_13TeV-madgraph-pythia8_TuneCUETP8M1/RunIISpring16MiniAODv2-PUSpring16RAWAODSIM_reHLT_80X_mcRun2_asymptotic_v14-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "additional_signal_overlap"),
  ("process_name_specific", "THW_Hincl"),
  ("nof_files",             17),
  ("nof_events",            1401800),
  ("use_it",                True),
  ("xsection",              0.015610),
  ("triggers",              [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/lucia/VHBBHeppyV24bis/THW_Hincl_13TeV-madgraph-pythia8_TuneCUETP8M1/VHBB_HEPPY_V24bis_THW_Hincl_13TeV-madgraph-Py8_TuneCUETP8M1__spr16MAv2-puspr16_HLT_80r2as_v14-v1/160911_224716"),
        ("selection", "*"),
        ("blacklist", [15]),
      ]),
    ]
  ),
])
samples["/TTGJets_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "Rares"),
  ("process_name_specific", "TTGJets"),
  ("nof_files",             56),
  ("nof_events",            4301632),
  ("use_it",                True),
  ("xsection",              3.697000),
  ("triggers",              [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/lucia/VHBBHeppyV24bis/TTGJets_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/VHBB_HEPPY_V24bis_TTGJets_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-Py8__spr16MAv2-puspr16_80r2as_2016_MAv2_v0-v1/160911_223929"),
        ("selection", "*"),
        ("blacklist", [1, 6, 14, 25, 39, 52]),
      ]),
    ]
  ),
])
samples["/TTJets_SingleLeptFromTbar_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "TT"),
  ("process_name_specific", "TTJets_SingleLeptFromTbar"),
  ("nof_files",             137),
  ("nof_events",            60309864),
  ("use_it",                True),
  ("xsection",              182.000000),
  ("triggers",              [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/lucia/VHBBHeppyV24bis/TTJets_SingleLeptFromTbar_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/VHBB_HEPPY_V24bis_TTJets_SingleLeptFromTbar_TuneCUETP8M1_13TeV-madgraphMLM-Py8__spr16MAv2-puspr16_80r2as_2016_MAv2_v0-v1/160911_223528"),
        ("selection", "*"),
        ("blacklist", [49, 54]),
      ]),
    ]
  ),
])
samples["/TTJets_SingleLeptFromTbar_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0_ext1-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "TT"),
  ("process_name_specific", "TTJets_SingleLeptFromTbar_ext1"),
  ("nof_files",             529),
  ("nof_events",            60309864),
  ("use_it",                True),
  ("xsection",              182.000000),
  ("triggers",              [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/lucia/VHBBHeppyV24bis/TTJets_SingleLeptFromTbar_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/VHBB_HEPPY_V24bis_TTJets_SingleLeptFromTbar_TuneCUETP8M1_13TeV-madgraphMLM-Py8__spr16MAv2-puspr16_80r2as_2016_MAv2_v0_ext1-v1/160911_223125"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples["/TTTT_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0_ext1-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "Rares"),
  ("process_name_specific", "TTTT"),
  ("nof_files",             11),
  ("nof_events",            989025),
  ("use_it",                True),
  ("xsection",              0.009103),
  ("triggers",              [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/lucia/VHBBHeppyV24bis/TTTT_TuneCUETP8M1_13TeV-amcatnlo-pythia8/VHBB_HEPPY_V24bis_TTTT_TuneCUETP8M1_13TeV-amcatnlo-Py8__spr16MAv2-puspr16_80r2as_2016_MAv2_v0_ext1-v1/160911_224827"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples["/TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "TTW"),
  ("process_name_specific", "TTWJetsToLNu"),
  ("nof_files",             4),
  ("nof_events",            252673),
  ("use_it",                True),
  ("xsection",              0.204300),
  ("triggers",              [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/lucia/VHBBHeppyV24bis/TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/VHBB_HEPPY_V24bis_TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-Py8__spr16MAv2-puspr16_80r2as_2016_MAv2_v0-v1/160911_225800"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples["/TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISpring16MiniAODv2-premix_withHLT_80X_mcRun2_asymptotic_v14_ext1-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "TTZ"),
  ("process_name_specific", "TTZToLLNuNu_M-10_ext1"),
  ("nof_files",             24),
  ("nof_events",            2256848),
  ("use_it",                True),
  ("xsection",              0.252900),
  ("triggers",              [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/lucia/VHBBHeppyV24bis/TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-pythia8/VHBB_HEPPY_V24bis_TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-Py8__spr16MAv2-premix_withHLT_80r2as_v14_ext1-v1/160911_224606"),
        ("selection", "*"),
        ("blacklist", [16]),
      ]),
    ]
  ),
])
samples["/TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "TTZ"),
  ("process_name_specific", "TTZToLLNuNu_M-10"),
  ("nof_files",             6),
  ("nof_events",            2256848),
  ("use_it",                True),
  ("xsection",              0.252900),
  ("triggers",              [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/lucia/VHBBHeppyV24bis/TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-pythia8/VHBB_HEPPY_V24bis_TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-Py8__spr16MAv2-puspr16_80r2as_2016_MAv2_v0-v1/160911_225425"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples["/WGToLNuG_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "Rares"),
  ("process_name_specific", "WGToLNuG"),
  ("nof_files",             75),
  ("nof_events",            5916785),
  ("use_it",                True),
  ("xsection",              585.800000),
  ("triggers",              [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/lucia/VHBBHeppyV24bis/WGToLNuG_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/VHBB_HEPPY_V24bis_WGToLNuG_TuneCUETP8M1_13TeV-madgraphMLM-Py8__spr16MAv2-puspr16_80r2as_2016_MAv2_v0-v1/160911_223823"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples["/WWTo2L2Nu_13TeV-powheg/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "EWK"),
  ("process_name_specific", "WWTo2L2Nu"),
  ("nof_files",             26),
  ("nof_events",            1996600),
  ("use_it",                True),
  ("xsection",              10.481000),
  ("triggers",              [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/lucia/VHBBHeppyV24bis/WWTo2L2Nu_13TeV-powheg/VHBB_HEPPY_V24bis_WWTo2L2Nu_13TeV-powheg__spr16MAv2-puspr16_80r2as_2016_MAv2_v0-v1/160911_224455"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples["/WW_DoubleScattering_13TeV-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "Rares"),
  ("process_name_specific", "WW_DoubleScattering"),
  ("nof_files",             12),
  ("nof_events",            844954),
  ("use_it",                True),
  ("xsection",              1.640000),
  ("triggers",              [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/lucia/VHBBHeppyV24bis/WW_DoubleScattering_13TeV-pythia8/VHBB_HEPPY_V24bis_WW_DoubleScattering_13TeV-Py8__spr16MAv2-puspr16_80r2as_2016_MAv2_v0-v1/160911_225013"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples["/WZTo3LNu_TuneCUETP8M1_13TeV-powheg-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "EWK"),
  ("process_name_specific", "WZTo3LNu"),
  ("nof_files",             26),
  ("nof_events",            2000000),
  ("use_it",                True),
  ("xsection",              4.102000),
  ("triggers",              [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/lucia/VHBBHeppyV24bis/WZTo3LNu_TuneCUETP8M1_13TeV-powheg-pythia8/VHBB_HEPPY_V24bis_WZTo3LNu_TuneCUETP8M1_13TeV-powheg-Py8__spr16MAv2-puspr16_80r2as_2016_MAv2_v0-v1/160911_224418"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples["/WZZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "Rares"),
  ("process_name_specific", "WZZ"),
  ("nof_files",             3),
  ("nof_events",            249800),
  ("use_it",                True),
  ("xsection",              0.055650),
  ("triggers",              [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/lucia/VHBBHeppyV24bis/WZZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8/VHBB_HEPPY_V24bis_WZZ_TuneCUETP8M1_13TeV-amcatnlo-Py8__spr16MAv2-puspr16_80r2as_2016_MAv2_v0-v1/160911_225836"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples["/WpWpJJ_EWK-QCD_TuneCUETP8M1_13TeV-madgraph-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v2/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "Rares"),
  ("process_name_specific", "WpWpJJ_EWK-QCD"),
  ("nof_files",             8),
  ("nof_events",            138235),
  ("use_it",                True),
  ("xsection",              0.037110),
  ("triggers",              [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/lucia/VHBBHeppyV24bis/WpWpJJ_EWK-QCD_TuneCUETP8M1_13TeV-madgraph-pythia8/VHBB_HEPPY_V24bis_WpWpJJ_EWK-QCD_TuneCUETP8M1_13TeV-madgraph-Py8__spr16MAv2-puspr16_80r2as_2016_MAv2_v0-v2/160911_225910"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples["/ZZTo4L_13TeV-amcatnloFXFX-pythia8/RunIISpring16MiniAODv2-PUSpring16RAWAODSIM_reHLT_80X_mcRun2_asymptotic_v14-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "EWK"),
  ("process_name_specific", "ZZTo4L"),
  ("nof_files",             50),
  ("nof_events",            7878358),
  ("use_it",                True),
  ("xsection",              1.256000),
  ("triggers",              [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/lucia/VHBBHeppyV24bis/ZZTo4L_13TeV-amcatnloFXFX-pythia8/VHBB_HEPPY_V24bis_ZZTo4L_13TeV-amcatnloFXFX-Py8__spr16MAv2-puspr16_HLT_80r2as_v14-v1/160911_223636"),
        ("selection", "*"),
        ("blacklist", [11, 12, 14, 16, 24, 25, 29, 31, 35]),
      ]),
    ]
  ),
])
samples["/tZq_ll_4f_13TeV-amcatnlo-pythia8_TuneCUETP8M1/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "Rares"),
  ("process_name_specific", "tZq_ll_4f"),
  ("nof_files",             35),
  ("nof_events",            2973639),
  ("use_it",                True),
  ("xsection",              0.075800),
  ("triggers",              [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/lucia/VHBBHeppyV24bis/tZq_ll_4f_13TeV-amcatnlo-pythia8_TuneCUETP8M1/VHBB_HEPPY_V24bis_tZq_ll_4f_13TeV-amcatnlo-Py8_TuneCUETP8M1__spr16MAv2-puspr16_80r2as_2016_MAv2_v0-v1/160911_224340"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples["/ttHToNonbb_M125_13TeV_powheg_pythia8/RunIISpring16MiniAODv2-PUSpring16RAWAODSIM_reHLT_80X_mcRun2_asymptotic_v14-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "signal"),
  ("process_name_specific", "ttHToNonbb_M125"),
  ("nof_files",             43),
  ("nof_events",            3199629),
  ("use_it",                True),
  ("xsection",              0.215100),
  ("triggers",              [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/lucia/VHBBHeppyV24bis/ttHToNonbb_M125_13TeV_powheg_pythia8/VHBB_HEPPY_V24bis_ttHToNonbb_M125_13TeV_powheg_Py8__spr16MAv2-puspr16_HLT_80r2as_v14-v1/160911_224147"),
        ("selection", "*"),
        ("blacklist", [5, 13, 16, 18, 24, 28, 35]),
      ]),
    ]
  ),
])
