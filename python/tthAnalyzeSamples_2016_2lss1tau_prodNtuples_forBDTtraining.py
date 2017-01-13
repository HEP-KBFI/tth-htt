from collections import OrderedDict as OD

samples_2016 = OD()

# file generated with command:
# check_broken -p /hdfs/local/karl/ttHNtupleProduction/2016/2017Jan12_forBDTtraining/ntuples/2lss_1tau -o -z -i -P -v

samples_2016["/TTW/spring16DR80v6aMiniAODv1/FASTSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "TTW"),
  ("process_name_specific", "TTW_Fastsim"),
  ("nof_files",             162),
  ("nof_events",            8017615),
  ("use_it",                True),
  ("xsection",              0.204300),
  ("genWeight",             False),
  ("triggers",              [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2016/2017Jan12_forBDTtraining/ntuples/2lss_1tau/TTW_FastSim"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016[""] = OD([
  ("type",                  "mc"),
  ("sample_category",       ""),
  ("process_name_specific", ""),
  ("nof_files",             24),
  ("nof_events",            832218),
  ("use_it",                True),
  ("xsection",              0.000000),
  ("genWeight",             False),
  ("triggers",              [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2016/2017Jan12_forBDTtraining/ntuples/2lss_1tau/TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-pythia8/VHBB_HEPPY_V24bis_TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-Py8__spr16MAv2-premix_withHLT_80r2as_v14_ext1-v1/160911_224606"),
        ("selection", "*"),
        ("blacklist", [16]),
      ]),
    ]
  ),
])
samples_2016["/TT_TuneCUETP8M1_13TeV-powheg-pythia8/RunIISpring16MiniAODv1-PUSpring16_80X_mcRun2_asymptotic_2016_v3_ext4-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "TT"),
  ("process_name_specific", "TT_ext4"),
  ("nof_files",             9602),
  ("nof_events",            264566715),
  ("use_it",                True),
  ("xsection",              831.760000),
  ("genWeight",             False),
  ("triggers",              [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2016/2017Jan12_forBDTtraining/ntuples/2lss_1tau/TT_TuneCUETP8M1_13TeV-powheg-pythia8/VHBB_HEPPY_D24_TT_TuneCUETP8M1_13TeV-powheg-Py8__spr16MiniAODv1-puspr16_80r2as_2016_v3_ext4-v1/161107_100027"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/TT_TuneCUETP8M1_13TeV-powheg-pythia8/RunIISpring16MiniAODv1-PUSpring16_80X_mcRun2_asymptotic_2016_v3_ext3-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "TT"),
  ("process_name_specific", "TT_ext3"),
  ("nof_files",             2124),
  ("nof_events",            264566715),
  ("use_it",                True),
  ("xsection",              831.760000),
  ("genWeight",             False),
  ("triggers",              [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2016/2017Jan12_forBDTtraining/ntuples/2lss_1tau/TT_TuneCUETP8M1_13TeV-powheg-pythia8/VHBB_HEPPY_V24_TT_TuneCUETP8M1_13TeV-powheg-Py8__spr16MAv2-puspr16_HLT_80r2as_v14_ext3-v1/160909_063406"),
        ("selection", "*"),
        ("blacklist", [600]),
      ]),
    ]
  ),
])
samples_2016["/WZTo3LNu_TuneCUETP8M1_13TeV-powheg-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "EWK"),
  ("process_name_specific", "WZTo3LNu"),
  ("nof_files",             26),
  ("nof_events",            1921938),
  ("use_it",                True),
  ("xsection",              4.102000),
  ("genWeight",             False),
  ("triggers",              [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2016/2017Jan12_forBDTtraining/ntuples/2lss_1tau/WZTo3LNu_TuneCUETP8M1_13TeV-powheg-pythia8/VHBB_HEPPY_V24bis_WZTo3LNu_TuneCUETP8M1_13TeV-powheg-Py8__spr16MAv2-puspr16_80r2as_2016_MAv2_v0-v1/160911_224418"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/ttHToNonbb_M125_13TeV_powheg_pythia8/RunIISpring16MiniAODv2-PUSpring16RAWAODSIM_reHLT_80X_mcRun2_asymptotic_v14-v1/MINIAODSIM"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "signal"),
  ("process_name_specific", "ttHToNonbb_M125"),
  ("nof_files",             43),
  ("nof_events",            3075610),
  ("use_it",                False),
  ("xsection",              0.215100),
  ("genWeight",             False),
  ("triggers",              [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2016/2017Jan12_forBDTtraining/ntuples/2lss_1tau/ttHToNonbb_M125_13TeV_powheg_pythia8/VHBB_HEPPY_V24bis_ttHToNonbb_M125_13TeV_powheg_Py8__spr16MAv2-puspr16_HLT_80r2as_v14-v1/160911_224147"),
        ("selection", "*"),
        ("blacklist", [5, 13, 16, 18, 24, 28, 35]),
      ]),
    ]
  ),
])
