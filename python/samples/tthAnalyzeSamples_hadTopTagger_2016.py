from collections import OrderedDict as OD

samples_2016 = OD()

# file generated with command:
# check_broken -p /hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau/MC_fastsim/ /hdfs/cms/store/user/mario/VHBBHeppyV25tthtautau/MC_fastsim/ /hdfs/cms/store/user/rdewanje/VHBBHeppyV25tthtautau/MC_fastsim/ /hdfs/cms/store/user/veelken/VHBBHeppyV25tthtautau/MC_fastsim/ --histo CountWeighted --output=. -P -z -v

#Fastsim
samples_2016["/TTToSemilepton_TuneCUETP8M2_ttHtranche3_13TeV-powheg-pythia8/matze-faster_v8_ttjets_sl_maod_p1_3a2fa29ab1d54ae0995b28f27b405be9-v1/USER"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "TT"),
  ("process_name_specific", "TTToSemilepton_fastsim_p1"),
  ("nof_files",             1702),
  ("nof_events",            85307397),
  ("use_it",                True),
  ("xsection",              245.000000),
  ("genWeight",             True),
  ("triggers",              [ "1e", "1mu", "2e", "1e1mu", "2mu", "3e", "2e1mu", "1e2mu", "3mu", "1e1tau", "1mu1tau", "2tau" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/veelken/VHBBHeppyV25tthtautau/MC_fastsim/TTToSemilepton_TuneCUETP8M2_ttHtranche3_13TeV-powheg-pythia8/VHBB_HEPPY_V25tthtautau_TTToSemilepton_TuneCUETP8M2_ttHtranche3_13TeV-powheg-Py8__matze-faster_v8_ttjets_sl_maod_p1_3a2fa29ab1d54ae0995b28f27b405be9-v1/170207_153448"),
        ("selection", "*"),
        ("blacklist", [940, 1042]),
      ]),
    ]
  ),
])
samples_2016["/TTToSemilepton_TuneCUETP8M2_ttHtranche3_13TeV-powheg-pythia8/matze-faster_v8_ttjets_sl_maod_p2_3a2fa29ab1d54ae0995b28f27b405be9-v1/USER"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "TT"),
  ("process_name_specific", "TTToSemilepton_fastsim_p2"),
  ("nof_files",             3403),
  ("nof_events",            85307397),
  ("use_it",                True),
  ("xsection",              245.000000),
  ("genWeight",             True),
  ("triggers",              [ "1e", "1mu", "2e", "1e1mu", "2mu", "3e", "2e1mu", "1e2mu", "3mu", "1e1tau", "1mu1tau", "2tau" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau/MC_fastsim/TTToSemilepton_TuneCUETP8M2_ttHtranche3_13TeV-powheg-pythia8/VHBB_HEPPY_V25tthtautau_TTToSemilepton_TuneCUETP8M2_ttHtranche3_13TeV-powheg-Py8__matze-faster_v8_ttjets_sl_maod_p2_3a2fa29ab1d54ae0995b28f27b405be9-v1/170208_162433"),
        ("selection", "*"),
        ("blacklist", [1891]),
      ]),
    ]
  ),
])
samples_2016["/TTToSemilepton_TuneCUETP8M2_ttHtranche3_13TeV-powheg-pythia8/matze-faster_v8_ttjets_sl_maod_p3_3a2fa29ab1d54ae0995b28f27b405be9-v1/USER"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "TT"),
  ("process_name_specific", "TTToSemilepton_fastsim_p3"),
  ("nof_files",             3404),
  ("nof_events",            85307397),
  ("use_it",                True),
  ("xsection",              245.000000),
  ("genWeight",             True),
  ("triggers",              [ "1e", "1mu", "2e", "1e1mu", "2mu", "3e", "2e1mu", "1e2mu", "3mu", "1e1tau", "1mu1tau", "2tau" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/rdewanje/VHBBHeppyV25tthtautau/MC_fastsim/TTToSemilepton_TuneCUETP8M2_ttHtranche3_13TeV-powheg-pythia8/VHBB_HEPPY_V25tthtautau_TTToSemilepton_TuneCUETP8M2_ttHtranche3_13TeV-powheg-Py8__matze-faster_v8_ttjets_sl_maod_p3_3a2fa29ab1d54ae0995b28f27b405be9-v1/170209_090617"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/matze-faster_v9_ttW_maod_54aa74f75231422e9f4d3766cb92a64a-v1/USER"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "TTW"),
  ("process_name_specific", "TTWJetsToLNu_fastsim"),
  ("nof_files",             1408),
  ("nof_events",            7158309),
  ("use_it",                True),
  ("xsection",              0.204300),
  ("genWeight",             True),
  ("triggers",              [ "1e", "1mu", "2e", "1e1mu", "2mu", "3e", "2e1mu", "1e2mu", "3mu", "1e1tau", "1mu1tau", "2tau" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/veelken/VHBBHeppyV25tthtautau/MC_fastsim/TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/VHBB_HEPPY_V25tthtautau_TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-Py8__matze-faster_v9_ttW_maod_54aa74f75231422e9f4d3766cb92a64a-v1/170208_163631"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-pythia8/matze-faster_v9_ttZ_maod_54aa74f75231422e9f4d3766cb92a64a-v1/USER"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "TTZ"),
  ("process_name_specific", "TTZToLLNuNu_fastsim"),
  ("nof_files",             1945),
  ("nof_events",            8825723),
  ("use_it",                True),
  ("xsection",              0.252900),
  ("genWeight",             True),
  ("triggers",              [ "1e", "1mu", "2e", "1e1mu", "2mu", "3e", "2e1mu", "1e2mu", "3mu", "1e1tau", "1mu1tau", "2tau" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/mario/VHBBHeppyV25tthtautau/MC_fastsim/TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-pythia8/VHBB_HEPPY_V25tthtautau_TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-Py8__matze-faster_v9_ttZ_maod_54aa74f75231422e9f4d3766cb92a64a-v1/170208_172612"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/ttHToNonbb_M125_TuneCUETP8M2_ttHtranche3_13TeV-powheg-pythia8/matze-faster_v8_ttH_maod_p1_3a2fa29ab1d54ae0995b28f27b405be9-v1/USER"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "signal"),
  ("process_name_specific", "ttHToNonbb_fastsim_p1"),
  ("nof_files",             337),
  ("nof_events",            16458549),
  ("use_it",                True),
  ("xsection",              0.215100),
  ("genWeight",             True),
  ("triggers",              [ "1e", "1mu", "2e", "1e1mu", "2mu", "3e", "2e1mu", "1e2mu", "3mu", "1e1tau", "1mu1tau", "2tau" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/rdewanje/VHBBHeppyV25tthtautau/MC_fastsim/ttHToNonbb_M125_TuneCUETP8M2_ttHtranche3_13TeV-powheg-pythia8/VHBB_HEPPY_V25tthtautau_ttHToNonbb_M125_TuneCUETP8M2_ttHtranche3_13TeV-powheg-Py8__matze-faster_v8_ttH_maod_p1_3a2fa29ab1d54ae0995b28f27b405be9-v1/170207_130941"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/ttHToNonbb_M125_TuneCUETP8M2_ttHtranche3_13TeV-powheg-pythia8/matze-faster_v8_ttH_maod_p2_3a2fa29ab1d54ae0995b28f27b405be9-v1/USER"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "signal"),
  ("process_name_specific", "ttHToNonbb_fastsim_p2"),
  ("nof_files",             674),
  ("nof_events",            16458549),
  ("use_it",                True),
  ("xsection",              0.215100),
  ("genWeight",             True),
  ("triggers",              [ "1e", "1mu", "2e", "1e1mu", "2mu", "3e", "2e1mu", "1e2mu", "3mu", "1e1tau", "1mu1tau", "2tau" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau/MC_fastsim/ttHToNonbb_M125_TuneCUETP8M2_ttHtranche3_13TeV-powheg-pythia8/VHBB_HEPPY_V25tthtautau_ttHToNonbb_M125_TuneCUETP8M2_ttHtranche3_13TeV-powheg-Py8__matze-faster_v8_ttH_maod_p2_3a2fa29ab1d54ae0995b28f27b405be9-v1/170208_162259"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/ttHToNonbb_M125_TuneCUETP8M2_ttHtranche3_13TeV-powheg-pythia8/matze-faster_v8_ttH_maod_p3_3a2fa29ab1d54ae0995b28f27b405be9-v1/USER"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "signal"),
  ("process_name_specific", "ttHToNonbb_fastsim_p3"),
  ("nof_files",             674),
  ("nof_events",            16458549),
  ("use_it",                True),
  ("xsection",              0.215100),
  ("genWeight",             True),
  ("triggers",              [ "1e", "1mu", "2e", "1e1mu", "2mu", "3e", "2e1mu", "1e2mu", "3mu", "1e1tau", "1mu1tau", "2tau" ]),
  ("reHLT",                 True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/mario/VHBBHeppyV25tthtautau/MC_fastsim/ttHToNonbb_M125_TuneCUETP8M2_ttHtranche3_13TeV-powheg-pythia8/VHBB_HEPPY_V25tthtautau_ttHToNonbb_M125_TuneCUETP8M2_ttHtranche3_13TeV-powheg-Py8__matze-faster_v8_ttH_maod_p3_3a2fa29ab1d54ae0995b28f27b405be9-v1/170208_124342"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/TTTo2L2Nu_TuneCUETP8M2_ttHtranche3_13TeV-powheg-pythia8/matze-faster_v8_ttjets_dl_maod_p1_3a2fa29ab1d54ae0995b28f27b405be9-v1/USER"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "TT"),
  ("process_name_specific",           "TTTo2L2Nu_fastsim_p1"),
  ("nof_files",                       92),
  ("nof_events",                      90528028),
  ("use_HIP_mitigation_bTag",         False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                          True),
  ("xsection",                        87.3),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("reHLT",                           True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2016/2017Oct17_woPreselection_forBDTtraining_only/ntuples/TTTo2L2Nu_fastsim_p1"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])

samples_2016["/TTTo2L2Nu_TuneCUETP8M2_ttHtranche3_13TeV-powheg-pythia8/matze-faster_v8_ttjets_dl_maod_p2_3a2fa29ab1d54ae0995b28f27b405be9-v1/USER"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "TT"),
  ("process_name_specific",           "TTTo2L2Nu_fastsim_p2"),
  ("nof_files",                       183),
  ("nof_events",                      90528028),
  ("use_HIP_mitigation_bTag",         False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                          True),
  ("xsection",                        87.3),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("reHLT",                           True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2016/2017Oct17_woPreselection_forBDTtraining_only/ntuples/TTTo2L2Nu_fastsim_p2"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])

samples_2016["/TTTo2L2Nu_TuneCUETP8M2_ttHtranche3_13TeV-powheg-pythia8/matze-faster_v8_ttjets_dl_maod_p3_3a2fa29ab1d54ae0995b28f27b405be9-v1/USER"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "TT"),
  ("process_name_specific",           "TTTo2L2Nu_fastsim_p3"),
  ("nof_files",                       183),
  ("nof_events",                      90528028),
  ("use_HIP_mitigation_bTag",         False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                          True),
  ("xsection",                        87.3),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("reHLT",                           True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2016/2017Oct17_woPreselection_forBDTtraining_only/ntuples/TTTo2L2Nu_fastsim_p3"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])

