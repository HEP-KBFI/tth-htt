from collections import OrderedDict as OD

samples_2016 = OD()
'''
samples already copied from Luca Perrozzi
   "ST_tW_top_5f_NoFullyHadronicDecays_13TeV-powheg_TuneCUETP8M1",
   "TTJets_SingleLeptFromTbar_TuneCUETP8M1_13TeV-madgraphMLM-pythia8",
   "THW_Hincl_13TeV-madgraph-pythia8_TuneCUETP8M1",
   "TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8",
   "TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-pythia8",
   "WZZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8",
   "ttHToNonbb_M125_13TeV_powheg_pythia8",
   "DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8",
   "WZTo3LNu_TuneCUETP8M1_13TeV-powheg-pythia8",
   "WWTo2L2Nu_13TeV-powheg",
   "ZZTo4L_13TeV-amcatnloFXFX-pythia8",
   "WGToLNuG_TuneCUETP8M1_13TeV-madgraphMLM-pythia8",
   "TGJets_TuneCUETP8M1_13TeV_amcatnlo_madspin_pythia8",
   "TTGJets_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8",
   "WpWpJJ_EWK-QCD_TuneCUETP8M1_13TeV-madgraph-pythia8",
   "WW_DoubleScattering_13TeV-pythia8",
   "tZq_ll_4f_13TeV-amcatnlo-pythia8_TuneCUETP8M1",
   "TTTT_TuneCUETP8M1_13TeV-amcatnlo-pythia8"

samples not yet ready to be copied
"/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring16MiniAODv2-PUSpring16RAWAODSIM_reHLT_80X_mcRun2_asymptotic_v14_ext1-v1/MINIAODSIM"
/ST_t-channel_antitop_4f_inclusiveDecays_13TeV-powhegV2-madspin-pythia8_TuneCUETP8M1/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM
/ST_t-channel_top_4f_inclusiveDecays_13TeV-powhegV2-madspin-pythia8_TuneCUETP8M1/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM
/ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM
/TTJets_DiLept_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v4/MINIAODSIM
/TTJets_DiLept_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0_ext1-v1/MINIAODSIM
/TTJets_SingleLeptFromT_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0_ext1-v1/MINIAODSIM
/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/RunIISpring16MiniAODv2-PUSpring16RAWAODSIM_reHLT_80X_mcRun2_asymptotic_v14_ext1-v1/MINIAODSIM
/GluGluHToZZTo4L_M125_13TeV_powheg2_JHUgenV6_pythia8/RunIISpring16MiniAODv2-PUSpring16RAWAODSIM_reHLT_80X_mcRun2_asymptotic_v14-v1/MINIAODSIM
/ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM
/ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0_ext1-v1/MINIAODSIM
/TTJets_SingleLeptFromT_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0_ext1-v1/MINIAODSIM
/TT_TuneCUETP8M1_13TeV-powheg-pythia8/RunIISpring16MiniAODv1-PUSpring16_80X_mcRun2_asymptotic_2016_v3_ext3-v1/MINIAODSIM

'''
samples_2016["/ttHToNonbb_M125_13TeV_powheg_pythia8/RunIISpring16MiniAODv2-PUSpring16RAWAODSIM_reHLT_80X_mcRun2_asymptotic_v14-v1/MINIAODSIM"] = OD([
  ("type", "mc"),
  ("sample_category", "signal"),
  ("process_name_specific", "ttHToNonbb_M125"),
  ("nof_files", 43),
  ("nof_events", 3187030), #DBS: 3860872
  ("use_it", False),
  ("xsection", 0.2151), # (1 - BR(ttH -> bb)) * sigma(ttH) = (1 - 0.577) * 0.5085 pb according to https://twiki.cern.ch/twiki/bin/view/LHCPhysics/CrossSections#Higgs_cross_sections_and_decay_b
  ("triggers", [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("local_paths",
    [
      OD([
        ("path", "/hdfs/local/lucia/VHBBHeppyV24bis/ttHToNonbb_M125_13TeV_powheg_pythia8/VHBB_HEPPY_V24bis_ttHToNonbb_M125_13TeV_powheg_Py8__spr16MAv2-puspr16_HLT_80r2as_v14-v1/160911_224147/0000/"),
        ("selection", "*"),
        ("blacklist", [5, 13, 16, 18, 24, 28, 35])
      ])
    ]
  )
])

samples_2016["/THW_Hincl_13TeV-madgraph-pythia8_TuneCUETP8M1/RunIISpring16MiniAODv2-PUSpring16RAWAODSIM_reHLT_80X_mcRun2_asymptotic_v14-v1/MINIAODSIM"] = OD([
  ("type", "mc"),    
  ("sample_category", "additional_signal_overlap"),
  ("process_name_specific", "THW_Hincl"),
  ("nof_files", 17),
  ("nof_events", 1397108), #DBS: 1499200
  ("use_it", True),
  ("xsection", 0.01561),
  ("triggers", [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("local_paths",
    [
      OD([
        ("path", "/hdfs/local/lucia/VHBBHeppyV24bis/THW_Hincl_13TeV-madgraph-pythia8_TuneCUETP8M1/VHBB_HEPPY_V24bis_THW_Hincl_13TeV-madgraph-Py8_TuneCUETP8M1__spr16MAv2-puspr16_HLT_80r2as_v14-v1/160911_224716/0000/"),
        ("selection", "*"),
        ("blacklist", [15])
      ]),
    ]
  )
])
samples_2016["/GluGluHToZZTo4L_M125_13TeV_powheg2_JHUgenV6_pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"] = OD([
  ("type", "mc"),
  ("sample_category", "additional_signal_overlap"),
  ("process_name_specific", "GluGluHToZZTo4L"),
  ("nof_files", 15),
  ("nof_events", 347052), #DBS: 969200
  ("use_it", True),
  ("xsection", 0.0119),
  ("triggers", [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),	
  ("local_paths",
    [
      OD([
        ("path", "/hdfs/local/lucia/VHBBHeppyV24bis/GluGluHToZZTo4L_M125_13TeV_powheg2_JHUgenV6_pythia8/VHBB_HEPPY_V24bis_GluGluHToZZTo4L_M125_13TeV_powheg2_JHUgenV6_Py8__spr16MAv2-puspr16_HLT_80r2as_v14-v1/160911_224902/0000/"),
        ("selection", "*")
      ]),
    ]
  )
])
samples_2016["/TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"] = OD([
  ("type", "mc"),
  ("sample_category", "TTZ"),
  ("process_name_specific", "TTZToLLNuNu"),
  ("nof_files", 6),
  # CV: The two DBS samples:
  #     /TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM
  #     /TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISpring16MiniAODv2-premix_withHLT_80X_mcRun2_asymptotic_v14_ext1-v1/MINIAODSIM
  #     cover the same process and phase-space. The nof_events are added accordingly. 
  ("nof_events", 2235200), #DBS: 398600+1981476
  ("use_it", True),
  ("xsection", 0.2529),
  ("triggers", [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("local_paths",
    [
      OD([
        ("path", "/hdfs/local/lucia/VHBBHeppyV24bis/TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-pythia8/VHBB_HEPPY_V24bis_TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-Py8__spr16MAv2-puspr16_80r2as_2016_MAv2_v0-v1/160911_225425/0000/"),
        ("selection", "*"),
      ])
    ]
  )
])
samples_2016["/TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISpring16MiniAODv2-premix_withHLT_80X_mcRun2_asymptotic_v14_ext1-v1/MINIAODSIM"] = OD([
  ("type", "mc"),
  ("sample_category", "TTZ"),
  ("process_name_specific", "TTZToLLNuNu_ext1"),
  ("nof_files", 24),
  # CV: The two DBS samples:
  #     /TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM
  #     /TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISpring16MiniAODv2-premix_withHLT_80X_mcRun2_asymptotic_v14_ext1-v1/MINIAODSIM
  #     cover the same process and phase-space. The nof_events are added accordingly. 
  ("nof_events", 2235200), #DBS: 398600+1981476
  ("use_it", True),
  ("xsection", 0.2529),
  ("triggers", [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("local_paths",
    [
      OD([
        ("path", "/hdfs/local/lucia/VHBBHeppyV24bis/TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-pythia8/VHBB_HEPPY_V24bis_TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-Py8__spr16MAv2-premix_withHLT_80r2as_v14_ext1-v1/160911_224606/0000/"),
        ("selection", "*"),
        ("blacklist", [16])
      ])
    ]
  )
])

samples_2016["/TTJets_SingleLeptFromTbar_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"] = OD([
  ("type", "mc"),
  ("sample_category", "TT"),
  ("process_name_specific", "TTJets_SingleLeptFromTbar"),
  ("nof_files", 137),
  # CV: The two DBS samples:
  #      /TTJets_SingleLeptFromTbar_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM 
  #      /TTJets_SingleLeptFromTbar_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0_ext1-v1/MINIAODSIM
  #     cover the same process and phase-space. The nof_events are added accordingly. 
  ("nof_events", 58638526), #DBS: 11947951+48546872
  ("use_it", True),
  ("xsection", 182.),
  ("triggers", [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("local_paths",
    [
      OD([
        ("path", "/hdfs/local/lucia/VHBBHeppyV24bis/TTJets_SingleLeptFromTbar_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/VHBB_HEPPY_V24bis_TTJets_SingleLeptFromTbar_TuneCUETP8M1_13TeV-madgraphMLM-Py8__spr16MAv2-puspr16_80r2as_2016_MAv2_v0-v1/160911_223528/0000/"),
        ("selection", "*"),
        ("blacklist", [49,54])
      ]),
    ]
  )
])
samples_2016["/TTJets_SingleLeptFromTbar_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0_ext1-v1/MINIAODSIM"] = OD([
  ("type", "mc"),
  ("sample_category", "TT"),
  ("process_name_specific", "TTJets_SingleLeptFromTbar_ext1"),
  ("nof_files", 529),
  # CV: The two DBS samples:
  #      /TTJets_SingleLeptFromTbar_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM 
  #      /TTJets_SingleLeptFromTbar_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0_ext1-v1/MINIAODSIM
  #     cover the same process and phase-space. The nof_events are added accordingly. 
  ("nof_events", 58638526), #DBS: 11947951+48546872
  ("use_it", True),
  ("xsection", 182.),
  ("triggers", [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("local_paths",
    [
      OD([
        ("path", "/hdfs/local/lucia/VHBBHeppyV24bis/TTJets_SingleLeptFromTbar_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/VHBB_HEPPY_V24bis_TTJets_SingleLeptFromTbar_TuneCUETP8M1_13TeV-madgraphMLM-Py8__spr16MAv2-puspr16_80r2as_2016_MAv2_v0-v1/160911_223528/0000/"),
        ("selection", "*"),
        ("blacklist", [])
      ]),
    ]
  )
])

samples_2016["/ST_tW_top_5f_NoFullyHadronicDecays_13TeV-powheg_TuneCUETP8M1/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"] = OD([
  ("type", "mc"),
  ("sample_category", "TT"),
  ("process_name_specific", "ST_tW_top_5f_NoFullyHadronicDecays"),
  ("nof_files", 66),
  ("nof_events", 4649953), #DBS:5405726
  ("use_it", True),
  ("xsection", 35.6),
  ("triggers", [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("local_paths",
    [
      OD([
        ("path", "/hdfs/local/lucia/VHBBHeppyV24bis/ST_tW_top_5f_NoFullyHadronicDecays_13TeV-powheg_TuneCUETP8M1/VHBB_HEPPY_V24bis_ST_tW_top_5f_NoFullyHadronicDecays_13TeV-powheg_TuneCUETP8M1__spr16MAv2-puspr16_80r2as_2016_MAv2_v0-v1/160911_223856/0000/"),
        ("selection", "*"),
        ("blacklist", [])
      ])
    ]
  )
])
samples_2016["/DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"] = OD([
  ("type", "mc"),
  ("sample_category", "EWK"),
  ("process_name_specific", "DYJetsToLL_M-10to50"),
  ("nof_files", 369),
  ("nof_events", 608980), #DBS:30915886
  ("use_it", True),
  ("xsection", 18610.),
  ("triggers", [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("local_paths",
    [
      OD([
        ("path", "/hdfs/local/lucia/VHBBHeppyV24bis/DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/VHBB_HEPPY_V24bis_DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-amcatnloFXFX-Py8__spr16MAv2-puspr16_80r2as_2016_MAv2_v0-v1/160911_223234/0000/"),
        ("selection", "*")
      ])
    ]
  )
])
samples_2016["/WWTo2L2Nu_13TeV-powheg/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"] = OD([
  ("type", "mc"),
  ("sample_category", "EWK"),
  ("process_name_specific", "WWTo2L2Nu"),
  ("nof_files", 26),
  ("nof_events", 615915), #DBS:1996600
  ("use_it", True),
  ("xsection", 10.481),
  ("triggers", [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("local_paths",
    [
      OD([
        ("path", "/hdfs/local/lucia/VHBBHeppyV24bis/WWTo2L2Nu_13TeV-powheg/VHBB_HEPPY_V24bis_WWTo2L2Nu_13TeV-powheg__spr16MAv2-puspr16_80r2as_2016_MAv2_v0-v1/160911_224455/0000"),
        ("selection", "*"),
      ])
    ]
  )
])
samples_2016["/WZTo3LNu_TuneCUETP8M1_13TeV-powheg-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"] = OD([
  ("type", "mc"),
  ("sample_category", "EWK"),
  ("process_name_specific", "WZTo3LNu"),
  ("nof_files", 26),
  ("nof_events", 459972), #DBS:2000000
  ("use_it", True),
  ("xsection", 4.102),
  ("triggers", [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("local_paths",
    [
      OD([
        ("path", "/hdfs/local/lucia/VHBBHeppyV24bis/WZTo3LNu_TuneCUETP8M1_13TeV-powheg-pythia8/VHBB_HEPPY_V24bis_WZTo3LNu_TuneCUETP8M1_13TeV-powheg-Py8__spr16MAv2-puspr16_80r2as_2016_MAv2_v0-v1/160911_224418/0000/"),
        ("selection", "*")
      ])
    ]
  )
])
samples_2016["/ZZTo4L_13TeV-amcatnloFXFX-pythia8/RunIISpring16MiniAODv2-PUSpring16RAWAODSIM_reHLT_80X_mcRun2_asymptotic_v14-v1/MINIAODSIM"] = OD([
  ("type", "mc"),
  ("sample_category", "EWK"),
  ("process_name_specific", "ZZTo4L"),
  ("nof_files", 50),
  ("nof_events", 1826626), #DBS:10348531
  ("use_it", True),
  ("xsection", 1.256),
  ("triggers", [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("local_paths",
    [
      OD([
        ("path", "/hdfs/local/lucia/VHBBHeppyV24bis/ZZTo4L_13TeV-amcatnloFXFX-pythia8/VHBB_HEPPY_V24bis_ZZTo4L_13TeV-amcatnloFXFX-Py8__spr16MAv2-puspr16_HLT_80r2as_v14-v1/160911_223636/0000/"),
        ("selection", "*"),
        ("blacklist", [11, 12, 14, 16, 24, 25, 29, 31, 35])
      ])
    ]
  )
])
samples_2016["/WZZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"] = OD([
  ("type", "mc"),
  ("sample_category", "Rares"),
  ("process_name_specific", "WZZ"),
  ("nof_files", 3),
  ("nof_events", 225809), #DBS:249800 
  ("use_it", True),
  ("xsection", 0.05565),
  ("triggers", [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("local_paths",
    [
      OD([
        ("path", "/hdfs/local/lucia/VHBBHeppyV24bis/WZZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8/VHBB_HEPPY_V24bis_WZZ_TuneCUETP8M1_13TeV-amcatnlo-Py8__spr16MAv2-puspr16_80r2as_2016_MAv2_v0-v1/160911_225836/0000/"),
        ("selection", "*")
      ])
    ]
  )
])
samples_2016["/WW_DoubleScattering_13TeV-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"] = OD([
  ("type", "mc"),
  ("sample_category", "Rares"),
  ("process_name_specific", "WW_DoubleScattering"),
  ("nof_files", 12),
  ("nof_events", 215438), #DBS:844954
  ("use_it", True),
  ("xsection", 1.64),
  ("triggers", [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("local_paths",
    [
      OD([
        ("path", "/hdfs/local/lucia/VHBBHeppyV24bis/WW_DoubleScattering_13TeV-pythia8/VHBB_HEPPY_V24bis_WW_DoubleScattering_13TeV-Py8__spr16MAv2-puspr16_80r2as_2016_MAv2_v0-v1/160911_225013/0000/"),
        ("selection", "*")
      ])
    ]
  )
])
samples_2016["/WpWpJJ_EWK-QCD_TuneCUETP8M1_13TeV-madgraph-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v2/MINIAODSIM"] = OD([
  ("type", "mc"),
  ("sample_category", "Rares"), # previously: background_samples_yieldshapes
  ("process_name_specific", "WpWpJJ_EWK-QCD"),
  ("nof_files", 8),
  ("nof_events", 131125), #DBS:138235
  ("use_it", True),
  ("xsection", 0.03711),
  ("triggers", [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("local_paths",
    [
      OD([
        ("path", "/hdfs/local/lucia/VHBBHeppyV24bis/WpWpJJ_EWK-QCD_TuneCUETP8M1_13TeV-madgraph-pythia8/VHBB_HEPPY_V24bis_WpWpJJ_EWK-QCD_TuneCUETP8M1_13TeV-madgraph-Py8__spr16MAv2-puspr16_80r2as_2016_MAv2_v0-v2/160911_225910/0000/"),
        ("selection", "*"),
      ])
    ]
  )
])
samples_2016["/WGToLNuG_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"] = OD([
  ("type", "mc"),
  ("sample_category", "Rares"), # previously: background_samples_yieldshapes
  ("process_name_specific", "WGToLNuG"),
  ("nof_files", 75),
  ("nof_events", 886752), #DBS:5916785
  ("use_it", True),
  ("xsection", 585.8),
  ("triggers", [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("local_paths",
    [
      OD([
        ("path", "/hdfs/local/lucia/VHBBHeppyV24bis/WGToLNuG_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/VHBB_HEPPY_V24bis_WGToLNuG_TuneCUETP8M1_13TeV-madgraphMLM-Py8__spr16MAv2-puspr16_80r2as_2016_MAv2_v0-v1/160911_223823/0000/"),
        ("selection", "*")
      ])
    ]
  )
])
samples_2016["/TGJets_TuneCUETP8M1_13TeV_amcatnlo_madspin_pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0_ext1-v1/MINIAODSIM"] = OD([
  ("type", "mc"),
  ("sample_category", "Rares"), # previously: background_samples_yieldshapes
  ("process_name_specific", "TGJets"),
  ("nof_files", 19),
  ("nof_events", 1308207), #DBS:1535543
  ("use_it", True),
  ("xsection", 2.967),
  ("triggers", [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("local_paths",
    [
      OD([
        ("path", "/hdfs/local/lucia/VHBBHeppyV24bis/TGJets_TuneCUETP8M1_13TeV_amcatnlo_madspin_pythia8/VHBB_HEPPY_V24bis_TGJets_TuneCUETP8M1_13TeV_amcatnlo_madspin_Py8__spr16MAv2-puspr16_80r2as_2016_MAv2_v0_ext1-v1/160911_224639/0000/"),
        ("selection", "*")
      ])
    ]
  )
])
samples_2016["/TTGJets_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"] = OD([
  ("type", "mc"),
  ("sample_category", "Rares"), # previously: background_samples_yieldshapes
  ("process_name_specific", "TTGJets"),
  ("nof_files", 56),
  ("nof_events", 4267915), #DBS:4874091
  ("use_it", True),
  ("xsection", 3.697),
  ("triggers", [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("local_paths",
    [
      OD([
        ("path", "/hdfs/local/lucia/VHBBHeppyV24bis/TTGJets_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/VHBB_HEPPY_V24bis_TTGJets_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-Py8__spr16MAv2-puspr16_80r2as_2016_MAv2_v0-v1/160911_223929/0000/"),
        ("selection", "*"),
        ("blacklist", [1, 6, 14, 25, 39, 52])
      ])
    ]
  )
])
samples_2016["/TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"] = OD([
  ("type", "mc"),
  ("sample_category", "TTW"),
  ("process_name_specific", "TTWJetsToLNu"),
  ("nof_files", 4),
  ("nof_events", 249518), #DBS:249518
  ("use_it", True),
  ("xsection", 0.2043),
  ("triggers", [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("local_paths",
    [
      OD([
        ("path", "/hdfs/local/lucia/VHBBHeppyV24bis/TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/VHBB_HEPPY_V24bis_TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-Py8__spr16MAv2-puspr16_80r2as_2016_MAv2_v0-v1/160911_225800/0000/"),
        ("selection", "*")
      ])
    ]
  )
])
samples_2016["/tZq_ll_4f_13TeV-amcatnlo-pythia8_TuneCUETP8M1/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"] = OD([
  ("type", "mc"),
  ("sample_category", "Rares"),
  ("process_name_specific", "tZq_ll_4f"),
  ("nof_files", 35),
  ("nof_events", 2852789), #DBS:2973639
  ("use_it", True),
  ("xsection", 0.0758),
  ("triggers", [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("local_paths",
    [
      OD([
        ("path", "/hdfs/local/lucia/VHBBHeppyV24bis/tZq_ll_4f_13TeV-amcatnlo-pythia8_TuneCUETP8M1/VHBB_HEPPY_V24bis_tZq_ll_4f_13TeV-amcatnlo-Py8_TuneCUETP8M1__spr16MAv2-puspr16_80r2as_2016_MAv2_v0-v1/160911_224340/0000/"),
        ("selection", "*")
      ])
    ]
  )
])
samples_2016["/TTTT_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0_ext1-v1/MINIAODSIM"] = OD([
  ("type", "mc"),
  ("sample_category", "Rares"),
  ("process_name_specific", "TTTT"),
  ("nof_files", 11),
  ("nof_events", 988975), #DBS:989025
  ("use_it", True),
  ("xsection", 0.009103),
  ("triggers", [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("local_paths",
    [
      OD([
        ("path", "/hdfs/local/lucia/VHBBHeppyV24bis/TTTT_TuneCUETP8M1_13TeV-amcatnlo-pythia8/VHBB_HEPPY_V24bis_TTTT_TuneCUETP8M1_13TeV-amcatnlo-Py8__spr16MAv2-puspr16_80r2as_2016_MAv2_v0_ext1-v1/160911_224827/0000/"),
        ("selection", "*")
      ])
    ]
  )
])



'''
samples_2016["/TTJets_SingleLeptFromT_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"] = OD([
  ("type", "mc"),
  ("sample_category", "TT"),
  ("process_name_specific", "TTJets_SingleLeptFromT"),
  ("nof_files", 290),
  ("nof_events", 11953980),
  ("use_it", True),
  ("xsection", 182.),
  ("triggers", [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("local_paths",
    [
      OD([
        ("path", "/hdfs/cms/store/user/kaehatah/TTJets_SingleLeptFromT_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/VHBB_HEPPY_V12_TTJets_SingleLeptFromT_TuneCUETP8M1_13TeV-madgraphMLM-Py8__fall15MAv2-pu25ns15v1_76r2as_v12-v1/160331_075445"),
        ("selection", "*"),
      ]),
    ]
  )
])
samples_2016["/TTJets_DiLept_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"] = OD([
  ("type", "mc"),
  ("sample_category", "TT"),
  ("process_name_specific", "TTJets_DiLept"),
  ("nof_files", 149),
  ("nof_events", 6102376),
  ("use_it", True),
  ("xsection", 87.3),
  ("triggers", [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("local_paths",
    [
      OD([
        ("path", "/hdfs/cms/store/user/kaehatah/TTJets_DiLept_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/VHBB_HEPPY_V12_TTJets_DiLept_TuneCUETP8M1_13TeV-madgraphMLM-Py8__fall15MAv2-pu25ns15v1_76r2as_v12-v1/160331_075552"),
        ("selection", "*"),
      ]),
    ]
  )
])
  ("type", "mc"),
  ("sample_category", "EWK"),
  ("process_name_specific", "DYJetsToLL_M-50"),
  ("nof_files", 226),
  ("nof_events", 9004328),
  ("use_it", True),
  ("xsection", 6025.2),
  ("triggers", [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("local_paths",
    [
      OD([
        ("path", "/hdfs/cms/store/user/kaehatah/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/VHBB_HEPPY_V12_DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-Py8__fall15MAv2-pu25ns15v1_76r2as_v12-v1/160331_075827"),
        ("selection", "*"),
      ])
    ]
  )
])
samples_2016["/WJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"] = OD([
  ("type", "mc"),
  ("sample_category", "EWK"),
  ("process_name_specific", "WJetsToLNu"),
  ("nof_files", 595),
  ("nof_events", 24156124),
  ("use_it", True),
  ("xsection", 61526.7),
  ("triggers", [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("local_paths",
    [
      OD([
        ("path", "/hdfs/cms/store/user/kaehatah/WJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/VHBB_HEPPY_V12_WJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-Py8__fall15MAv2-pu25ns15v1_76r2as_v12-v1/160331_075944"),
        ("selection", "*"),
      ])
    ]
  )
])
samples_2016["/ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"] = OD([
  ("type", "mc"),
  ("sample_category", "TT"),
  ("process_name_specific", "ST_tW_antitop_5f_inclusiveDecays"),
  ("nof_files", 27),
  ("nof_events", 999400),
  ("use_it", True),
  ("xsection", 35.6),
  ("triggers", [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("local_paths",
    [
      OD([
        ("path", "/hdfs/cms/store/user/kaehatah/ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1/VHBB_HEPPY_V12_ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-Py8_TuneCUETP8M1__fall15MAv2-pu25ns15v1_76r2as_v12-v1/160331_080206"),
        ("selection", "*"),
      ])
    ]
  )
])
samples_2016["/ST_t-channel_4f_leptonDecays_13TeV-amcatnlo-pythia8_TuneCUETP8M1/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"] = OD([
  ("type", "mc"),
  ("sample_category", "TT"),
  ("process_name_specific", "ST_t-channel_4f_leptonDecays"),
  # CV: The two DBS samples:
  #       /ST_t-channel_4f_leptonDecays_13TeV-amcatnlo-pythia8_TuneCUETP8M1/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM
  #       /ST_t-channel_4f_leptonDecays_13TeV-amcatnlo-pythia8_TuneCUETP8M1/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12_ext1-v1/MINIAODSIM
  #     cover the same process and phase-space. The nof_events are added accordingly.
  ("nof_files", 478),
  ("nof_events", 19938230+29206391),
  ("use_it", True),
  ("xsection", 70.69),
  ("triggers", [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
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
samples_2016["/ST_t-channel_4f_leptonDecays_13TeV-amcatnlo-pythia8_TuneCUETP8M1/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12_ext1-v1/MINIAODSIM"] = OD([
  ("type", "mc"),
  ("sample_category", "TT"),
  ("process_name_specific", "ST_t-channel_4f_leptonDecays_ext1"),
  # CV: The two DBS samples:
  #       /ST_t-channel_4f_leptonDecays_13TeV-amcatnlo-pythia8_TuneCUETP8M1/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM
  #       /ST_t-channel_4f_leptonDecays_13TeV-amcatnlo-pythia8_TuneCUETP8M1/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12_ext1-v1/MINIAODSIM
  #     cover the same process and phase-space. The nof_events are added accordingly. 
  ("nof_files", 690),
  ("nof_events", 19938230+29206391),
  ("use_it", True),
  ("xsection", 70.69),
  ("triggers", [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
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
samples_2016["/ST_s-channel_4f_leptonDecays_13TeV-amcatnlo-pythia8_TuneCUETP8M1/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v2/MINIAODSIM"] = OD([
  ("type", "mc"),
  ("sample_category", "TT"),
  ("process_name_specific", "ST_s-channel_4f_leptonDecays"),
  ("nof_files", 24),
  ("nof_events", 998400),
  ("use_it", True),
  ("xsection", 3.75),
  ("triggers", [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("local_paths",
    [
      OD([
        ("path", "/hdfs/cms/store/user/kaehatah/ST_s-channel_4f_leptonDecays_13TeV-amcatnlo-pythia8_TuneCUETP8M1/VHBB_HEPPY_V12_ST_s-channel_4f_leptonDecays_13TeV-amcatnlo-Py8_TuneCUETP8M1__fall15MAv2-pu25ns15v1_76r2as_v12-v2/160331_080546"),
        ("selection", "*"),
      ])
    ]
  )
])
samples_2016["/ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"] = OD([
  ("type", "mc"),
  ("sample_category", "Rares"), # previously: background_samples_yieldshapes
  ("process_name_specific", "ZGTo2LG"),
  ("nof_files", 103),
  ("nof_events", 4424816),
  ("use_it", True),
  ("xsection", 131.3),
  ("triggers", [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("local_paths",
    [
      OD([
        ("path", "/hdfs/cms/store/user/kaehatah/ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/VHBB_HEPPY_V12_ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-Py8__fall15MAv2-pu25ns15v1_76r2as_v12-v1/160331_083018"),
        ("selection", "*"),
      ])
    ]
  )
])
samples_2016["/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"] = OD([
  ("type", "mc"),
  ("sample_category", "signal"),
  ("process_name_specific", "ttHJetToNonbb_M125"),
  ("nof_files", 186),
  ("nof_events", 8139275),
  ("use_it", True),
  ("xsection", 0.2151), # (1 - BR(ttH -> bb)) * sigma(ttH) = (1 - 0.577) * 0.5085 pb according to https://twiki.cern.ch/twiki/bin/view/LHCPhysics/CrossSections#Higgs_cross_sections_and_decay_b 
  ("triggers", [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("local_paths",
    [
      OD([
        ("path", "/hdfs/cms/store/user/kaehatah/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/VHBB_HEPPY_V12_ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_Py8_mWCutfix__fall15MAv2-pu25ns15v1_76r2as_v12-v1/160330_172426"),
        ("selection", "*"),
      ])
    ]
  )
])
samples_2016["/ttHJetToNonbb_M130_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"] = OD([
  ("type", "mc"),
  ("sample_category", "signal"),
  ("process_name_specific", "ttHJetToNonbb_M130"),
  ("nof_files", 11),
  ("nof_events", 379065),
  ("use_it", False), # xsection missing
  ("xsection", 0.),
  ("triggers", [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("local_paths",
    [
      OD([
        ("path", "/hdfs/cms/store/user/kaehatah/ttHJetToNonbb_M130_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/VHBB_HEPPY_V12_ttHJetToNonbb_M130_13TeV_amcatnloFXFX_madspin_Py8_mWCutfix__fall15MAv2-pu25ns15v1_76r2as_v12-v1/160330_172533"),
        ("selection", "*"),
      ])
    ]
  )
])
samples_2016["/DoubleMuon/Run2015C_25ns-16Dec2015-v1/MINIAOD"] = OD([
  ("type", "data"),
  ("sample_category", "data_obs"),
  ("process_name_specific", "DoubleMuon_Run2015C"),
  ("nof_files", 23),
  ("nof_events", 900626),
  ("use_it", True),
  ("triggers", [ "2mu" ]),
  ("local_paths",
    [
      OD([
        ("path", "/hdfs/cms/store/user/kaehatah/DoubleMuon/VHBB_HEPPY_H20_DoubleMuon__Run2015C_25ns-16Dec2015-v1/160419_120720"),
        ("selection", "*"),
      ])
    ]
  )
])
samples_2016["/DoubleMuon/Run2015D-16Dec2015-v1/MINIAOD"] = OD([
  ("type", "data"),
  ("sample_category", "data_obs"),
  ("process_name_specific", "DoubleMuon_Run2015D"),
  ("nof_files", 951),
  ("nof_events", 51342919),
  ("use_it", True),
  ("triggers", [ "2mu" ]),
  ("local_paths",
    [
      OD([
        ("path", "/hdfs/cms/store/user/kaehatah/DoubleMuon/VHBB_HEPPY_H20_DoubleMuon__Run2015D-16Dec2015-v1/160419_140710"),
        ("selection", "*"),
      ]),
      OD([
        ("path", "/hdfs/cms/store/user/kaehatah/DoubleMuon/VHBB_HEPPY_H20_DoubleMuon__Run2015D-16Dec2015-v1/160429_225658"),
        ("selection", "44,63,65,109,141,188,189,215,245,251,257,262,287,290,459,469,472,539,570,593,652,661,712,760,858,864,900,932"),
      ])
    ]
  )
])
samples_2016["/DoubleEG/Run2015C_25ns-16Dec2015-v1/MINIAOD"] = OD([
  ("type", "data"),
  ("sample_category", "data_obs"),
  ("process_name_specific", "DoubleEG_Run2015C"),
  ("nof_files", 52),
  ("nof_events", 2127090),
  ("use_it", True),
  ("triggers", [ "2e" ]),
  ("local_paths",
    [
      OD([
        ("path", "/hdfs/cms/store/user/kaehatah/DoubleEG/VHBB_HEPPY_H20_DoubleEG__Run2015C_25ns-16Dec2015-v1/160419_140830"),
        ("selection", "*"),
      ]),
      OD([
        ("path", "/hdfs/cms/store/user/kaehatah/DoubleEG/VHBB_HEPPY_H20_DoubleEG__Run2015C_25ns-16Dec2015-v1/160429_225812"),
        ("selection", "1,30"),
      ])
    ]
  )
])
samples_2016["/DoubleEG/Run2015D-16Dec2015-v2/MINIAOD"] = OD([
  ("type", "data"),
  ("sample_category", "data_obs"),
  ("process_name_specific", "DoubleEG_Run2015D"),
  ("nof_files", 1652),
  ("nof_events", 93018487),
  ("use_it", True),
  ("triggers", [ "2e" ]),
  ("local_paths",
    [
      OD([
        ("path", "/hdfs/cms/store/user/kaehatah/DoubleEG/VHBB_HEPPY_H20_DoubleEG__Run2015D-16Dec2015-v2/160420_113228"),
        ("selection", "*"),
      ]),
      OD([
        ("path", "/hdfs/cms/store/user/kaehatah/DoubleEG/VHBB_HEPPY_H20_DoubleEG__Run2015D-16Dec2015-v2/160429_225920"),
        ("selection", "15,19,111,130,156,175,191,235,239,309,361,376,395,409,413,422,448,470,483,498,507,532,568,584,597,612,666,670,"
                      "673,690,697,710,722,734,748,762,772,783,814,833,846,860,863,868,878,880,889,913,960,974,991,1019,1088,1091,1106,"
                      "1143,1176,1277,1366,1367,1410,1411,1425,1427,1428,1434,1456,1466,1514,1516,1522,1585,1613"),
      ])
    ]
  )
])
samples_2016["/MuonEG/Run2015C_25ns-16Dec2015-v1/MINIAOD"] = OD([
  ("type", "data"),
  ("sample_category", "data_obs"),
  ("process_name_specific", "MuonEG_Run2015C"),
  ("nof_files", 6),
  ("nof_events", 111545),
  ("use_it", True),
  ("triggers", [ "1e1mu" ]),
  ("local_paths",
    [
      OD([
        ("path", "/hdfs/cms/store/user/kaehatah/MuonEG/VHBB_HEPPY_H20_MuonEG__Run2015C_25ns-16Dec2015-v1/160419_141135"),
        ("selection", "*"),
      ])
    ]
  )
])
samples_2016["/MuonEG/Run2015D-16Dec2015-v1/MINIAOD"] = OD([
  ("type", "data"),
  ("sample_category", "data_obs"),
  ("process_name_specific", "MuonEG_Run2015D"),
  ("nof_files", 286),
  ("nof_events", 13442593),
  ("use_it", True),
  ("triggers", [ "1e1mu" ]),
  ("local_paths",
    [
      OD([
        ("path", "/hdfs/cms/store/user/kaehatah/MuonEG/VHBB_HEPPY_H20_MuonEG__Run2015D-16Dec2015-v1/160419_141314"),
        ("selection", "*"),
      ]),
      OD([
        ("path", "/hdfs/cms/store/user/kaehatah/MuonEG/VHBB_HEPPY_H20_MuonEG__Run2015D-16Dec2015-v1/160429_230034"),
        ("selection", "13,14,18,19,22,26,27,29,34,40,41,45,47,50,51,54,57,63,64,70,74,75,79,81,83,86,88,90,100,102,103,106,"
                      "107,108,110,112,117,119,124,128,129,132,134,135,141,144,145,148,154,157,159,162,163,170,177,180,181,182,"
                      "184,188,189,190,191,192,193,196,197,198,199,201,212,215,222,226,230,233,235,236,237,239,241,243,244,245,"
                      "247,248,252,253,254,259,260,263,265,270,274,275,277,278,281,284"),
      ]),
    ]
  )
])
samples_2016["/SingleMuon/Run2015C_25ns-16Dec2015-v1/MINIAOD"] = OD([
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
samples_2016["/SingleMuon/Run2015D-16Dec2015-v1/MINIAOD"] = OD([
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
samples_2016["/SingleElectron/Run2015C_25ns-16Dec2015-v1/MINIAOD"] = OD([
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
samples_2016["/SingleElectron/Run2015D-16Dec2015-v1/MINIAOD"] = OD([
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
'''
