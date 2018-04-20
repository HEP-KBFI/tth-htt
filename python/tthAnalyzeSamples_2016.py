from collections import OrderedDict as OD

# file generated with the following command:
# ./scripts/create_dictionary.py -v -m python/metaDict_2016.py -p python/sampleLocations_2016.txt -Z zeroes_2016.txt -z zombies_2016.txt -N samples_2016 -J /home/karl/sandbox/create_dictionary_2016 -F -E 2016

samples_2016 = OD()

samples_2016["/TTJets_DiLept_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "TT"),
  ("process_name_specific",           "TTJets_DiLept_ext1"),
  ("nof_files",                       2448),
  ("nof_events",                      30218948),
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
        ("path",      "/hdfs/cms/store/user/rdewanje/VHBBHeppyV25tthtautau/MC/TTJets_DiLept_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/VHBB_HEPPY_V25tthtautau_TTJets_DiLept_TuneCUETP8M1_13TeV-madgraphMLM-Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6_ext1-v1/170207_124429"),
        ("selection", "*"),
        ("blacklist", [3, 14, 32, 51, 57, 341, 538, 615, 659, 778, 1177, 1432, 1642, 1643, 1648, 1653, 1872, 1885, 1926, 2210, 2220, 2374, 2435]),
      ]),
    ]
  ),
])

samples_2016["/TTJets_DiLept_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "TT"),
  ("process_name_specific",           "TTJets_DiLept"),
  ("nof_files",                       616),
  ("nof_events",                      30218948),
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
        ("path",      "/hdfs/cms/store/user/rdewanje/VHBBHeppyV25tthtautau/MC/TTJets_DiLept_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/VHBB_HEPPY_V25tthtautau_TTJets_DiLept_TuneCUETP8M1_13TeV-madgraphMLM-Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6-v1/170207_124244"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])

samples_2016["/WGToLNuG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "Rares"),
  ("process_name_specific",           "WGToLNuG_ext1"),
  ("nof_files",                       508),
  ("nof_events",                      9651890),
  ("use_HIP_mitigation_bTag",         False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                          True),
  ("xsection",                        585.8),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("reHLT",                           True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/mario/VHBBHeppyV25tthtautau/MC/WGToLNuG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/VHBB_HEPPY_V25tthtautau_WGToLNuG_TuneCUETP8M1_13TeV-amcatnloFXFX-Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6_ext1-v1/170208_121122"),
        ("selection", "*"),
        ("blacklist", [38, 133, 186, 223, 260, 262, 300, 308, 334, 355, 363, 373, 380, 396, 423, 424]),
      ]),
    ]
  ),
])

samples_2016["/WGToLNuG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext2-v1/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "Rares"),
  ("process_name_specific",           "WGToLNuG_ext2"),
  ("nof_files",                       1033),
  ("nof_events",                      9651890),
  ("use_HIP_mitigation_bTag",         False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                          True),
  ("xsection",                        585.8),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("reHLT",                           True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/mario/VHBBHeppyV25tthtautau/MC/WGToLNuG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/VHBB_HEPPY_V25tthtautau_WGToLNuG_TuneCUETP8M1_13TeV-amcatnloFXFX-Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6_ext2-v1/170208_121305"),
        ("selection", "*"),
        ("blacklist", [77, 357, 456, 507, 527, 673, 785]),
      ]),
    ]
  ),
])
samples_2016["/TTToSemilepton_TuneCUETP8M2_ttHtranche3_13TeV-powheg-pythia8/matze-faster_v8_ttjets_sl_maod_p1_3a2fa29ab1d54ae0995b28f27b405be9-v1/USER"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "TT"),
  ("process_name_specific",           "TTToSemilepton_fastsim_p1"),
  ("nof_files",                       1702),
  ("nof_events",                      85311662),
  ("use_HIP_mitigation_bTag",         False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                          False),
  ("xsection",                        245.0),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("reHLT",                           True),
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
  ("type",                            "mc"),
  ("sample_category",                 "TT"),
  ("process_name_specific",           "TTToSemilepton_fastsim_p2"),
  ("nof_files",                       3403),
  ("nof_events",                      85311662),
  ("use_HIP_mitigation_bTag",         False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                          False),
  ("xsection",                        245.0),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("reHLT",                           True),
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
  ("type",                            "mc"),
  ("sample_category",                 "TT"),
  ("process_name_specific",           "TTToSemilepton_fastsim_p3"),
  ("nof_files",                       3404),
  ("nof_events",                      85311662),
  ("use_HIP_mitigation_bTag",         False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                          False),
  ("xsection",                        245.0),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("reHLT",                           True),
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
samples_2016["/TTJets_SingleLeptFromTbar_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "TT"),
  ("process_name_specific",           "TTJets_SingleLeptFromTbar_ext1"),
  ("nof_files",                       4870),
  ("nof_events",                      60195940),
  ("use_HIP_mitigation_bTag",         False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                          True),
  ("xsection",                        182.18),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("reHLT",                           True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v2/MC/TTJets_SingleLeptFromTbar_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/VHBB_HEPPY_V25tthtautau_v2_TTJets_SingleLeptFromTbar_TuneCUETP8M1_13TeV-madgraphMLM-Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6_ext1-v1/170217_230025"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])

samples_2016["/TTJets_SingleLeptFromTbar_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "TT"),
  ("process_name_specific",           "TTJets_SingleLeptFromTbar"),
  ("nof_files",                       1205),
  ("nof_events",                      60195940),
  ("use_HIP_mitigation_bTag",         False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                          True),
  ("xsection",                        182.18),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("reHLT",                           True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/mario/VHBBHeppyV25tthtautau/MC/TTJets_SingleLeptFromTbar_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/VHBB_HEPPY_V25tthtautau_TTJets_SingleLeptFromTbar_TuneCUETP8M1_13TeV-madgraphMLM-Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6-v1/170208_120816"),
        ("selection", "*"),
        ("blacklist", [215, 291]),
      ]),
    ]
  ),
])
samples_2016["/ttHToNonbb_M125_TuneCUETP8M2_ttHtranche3_13TeV-powheg-pythia8/matze-faster_v8_ttH_maod_p1_3a2fa29ab1d54ae0995b28f27b405be9-v1/USER"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "signal"),
  ("process_name_specific",           "ttHToNonbb_fastsim_p1"),
  ("nof_files",                       337),
  ("nof_events",                      16459381),
  ("use_HIP_mitigation_bTag",         False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                          False),
  ("xsection",                        0.2151),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("reHLT",                           True),
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
  ("type",                            "mc"),
  ("sample_category",                 "signal"),
  ("process_name_specific",           "ttHToNonbb_fastsim_p2"),
  ("nof_files",                       674),
  ("nof_events",                      16459381),
  ("use_HIP_mitigation_bTag",         False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                          False),
  ("xsection",                        0.2151),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("reHLT",                           True),
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
  ("type",                            "mc"),
  ("sample_category",                 "signal"),
  ("process_name_specific",           "ttHToNonbb_fastsim_p3"),
  ("nof_files",                       674),
  ("nof_events",                      16459381),
  ("use_HIP_mitigation_bTag",         False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                          False),
  ("xsection",                        0.2151),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("reHLT",                           True),
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
samples_2016["/TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "TTZ"),
  ("process_name_specific",           "TTZToLL_M10_ext1"),
  ("nof_files",                       203),
  ("nof_events",                      3700023),
  ("use_HIP_mitigation_bTag",         False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                          True),
  ("xsection",                        0.273132),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("reHLT",                           True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau/MC/TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-pythia8/VHBB_HEPPY_V25tthtautau_TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6_ext1-v1/170207_124540"),
        ("selection", "*"),
        ("blacklist", [15, 36, 57, 129]),
      ]),
    ]
  ),
])

samples_2016["/TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext2-v1/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "TTZ"),
  ("process_name_specific",           "TTZToLL_M10_ext2"),
  ("nof_files",                       610),
  ("nof_events",                      3700023),
  ("use_HIP_mitigation_bTag",         False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                          True),
  ("xsection",                        0.273132),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("reHLT",                           True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau/MC/TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-pythia8/VHBB_HEPPY_V25tthtautau_TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6_ext2-v1/170207_124710"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/TTJets_SingleLeptFromT_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "TT"),
  ("process_name_specific",           "TTJets_SingleLeptFromT_ext1"),
  ("nof_files",                       5057),
  ("nof_events",                      61478694),
  ("use_HIP_mitigation_bTag",         False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                          True),
  ("xsection",                        182.18),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("reHLT",                           True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/mario/VHBBHeppyV25tthtautau/MC/TTJets_SingleLeptFromT_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/VHBB_HEPPY_V25tthtautau_TTJets_SingleLeptFromT_TuneCUETP8M1_13TeV-madgraphMLM-Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6_ext1-v1/170208_120653"),
        ("selection", "*"),
        ("blacklist", [182, 206, 425, 496, 542, 1101, 1108, 1186, 1426, 1618, 2502, 2509, 2755, 2912, 2924, 3039, 3156, 3165, 3180, 3201, 3204, 3212, 3357, 3390, 3492, 3658, 4040, 4159, 4173, 4275, 4312, 4314, 4398, 4440, 4441, 4672, 4707, 4747, 4752, 4785]),
      ]),
    ]
  ),
])

samples_2016["/TTJets_SingleLeptFromT_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "TT"),
  ("process_name_specific",           "TTJets_SingleLeptFromT"),
  ("nof_files",                       1207),
  ("nof_events",                      61478694),
  ("use_HIP_mitigation_bTag",         False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                          True),
  ("xsection",                        182.18),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("reHLT",                           True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/mario/VHBBHeppyV25tthtautau/MC/TTJets_SingleLeptFromT_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/VHBB_HEPPY_V25tthtautau_TTJets_SingleLeptFromT_TuneCUETP8M1_13TeV-madgraphMLM-Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6-v1/170208_120534"),
        ("selection", "*"),
        ("blacklist", [64, 134, 135, 236, 293, 328, 486, 541, 587, 834]),
      ]),
    ]
  ),
])
samples_2016["/TTGJets_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "Rares"),
  ("process_name_specific",           "TTGJets_ext1"),
  ("nof_files",                       997),
  ("nof_events",                      4743511),
  ("use_HIP_mitigation_bTag",         False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                          True),
  ("xsection",                        3.697),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("reHLT",                           True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/mario/VHBBHeppyV25tthtautau/MC/TTGJets_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/VHBB_HEPPY_V25tthtautau_TTGJets_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6_ext1-v1/170208_120330"),
        ("selection", "*"),
        ("blacklist", [315, 331, 344, 479, 839, 845, 848, 871, 876, 889]),
      ]),
    ]
  ),
])

samples_2016["/TTGJets_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "Rares"),
  ("process_name_specific",           "TTGJets"),
  ("nof_files",                       489),
  ("nof_events",                      4743511),
  ("use_HIP_mitigation_bTag",         False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                          True),
  ("xsection",                        3.697),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("reHLT",                           True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/rdewanje/VHBBHeppyV25tthtautau/MC/TTGJets_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/VHBB_HEPPY_V25tthtautau_TTGJets_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6-v1/170207_124053"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v3/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "TTW"),
  ("process_name_specific",           "TTWJetsToLNu_ext1"),
  ("nof_files",                       218),
  ("nof_events",                      2701217),
  ("use_HIP_mitigation_bTag",         False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                          True),
  ("xsection",                        0.2043),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("reHLT",                           True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau/MC/TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/VHBB_HEPPY_V25tthtautau_TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6_ext1-v3/170207_124033"),
        ("selection", "*"),
        ("blacklist", [83, 167, 179]),
      ]),
    ]
  ),
])

samples_2016["/TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext2-v1/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "TTW"),
  ("process_name_specific",           "TTWJetsToLNu_ext2"),
  ("nof_files",                       314),
  ("nof_events",                      2701217),
  ("use_HIP_mitigation_bTag",         False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                          True),
  ("xsection",                        0.2043),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("reHLT",                           True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau/MC/TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/VHBB_HEPPY_V25tthtautau_TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6_ext2-v1/170207_124213"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v2/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "EWK"),
  ("process_name_specific",           "DYJetsToLL_M-50_ext1"),
  ("nof_files",                       2461),
  ("nof_events",                      145528414),
  ("use_HIP_mitigation_bTag",         False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                          True),
  ("xsection",                        5765.4),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("reHLT",                           True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v3/MC/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/VHBB_HEPPY_V25tthtautau_v3_DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6_ext1-v2/170225_232649"),
        ("selection", "*"),
        ("blacklist", [2012]),
      ]),
    ]
  ),
])

samples_2016["/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext2-v1/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "EWK"),
  ("process_name_specific",           "DYJetsToLL_M-50_ext2"),
  ("nof_files",                       4851),
  ("nof_events",                      145528414),
  ("use_HIP_mitigation_bTag",         False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                          True),
  ("xsection",                        5765.4),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("reHLT",                           True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v3/MC/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/VHBB_HEPPY_V25tthtautau_v3_DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6_ext2-v1/170225_232809"),
        ("selection", "*"),
        ("blacklist", [63, 252, 412, 1134, 1148, 1670, 1743, 2014, 2234, 3223, 3448, 3514, 4628] + [3259]), # explicitly added 3259, corrupted but not zombie
      ]),
    ]
  ),
])
samples_2016["/TTTo2L2Nu_TuneCUETP8M2_ttHtranche3_13TeV-powheg-pythia8/matze-faster_v8_ttjets_dl_maod_p1_3a2fa29ab1d54ae0995b28f27b405be9-v1/USER"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "TT"),
  ("process_name_specific",           "TTTo2L2Nu_fastsim_p1"),
  ("nof_files",                       1822),
  ("nof_events",                      90528028),
  ("use_HIP_mitigation_bTag",         False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                          False),
  ("xsection",                        87.3),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("reHLT",                           True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau/MC_fastsim/TTTo2L2Nu_TuneCUETP8M2_ttHtranche3_13TeV-powheg-pythia8/VHBB_HEPPY_V25tthtautau_TTTo2L2Nu_TuneCUETP8M2_ttHtranche3_13TeV-powheg-Py8__matze-faster_v8_ttjets_dl_maod_p1_3a2fa29ab1d54ae0995b28f27b405be9-v1/170207_130407"),
        ("selection", "*"),
        ("blacklist", [267]),
      ]),
    ]
  ),
])

samples_2016["/TTTo2L2Nu_TuneCUETP8M2_ttHtranche3_13TeV-powheg-pythia8/matze-faster_v8_ttjets_dl_maod_p2_3a2fa29ab1d54ae0995b28f27b405be9-v1/USER"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "TT"),
  ("process_name_specific",           "TTTo2L2Nu_fastsim_p2"),
  ("nof_files",                       3646),
  ("nof_events",                      90528028),
  ("use_HIP_mitigation_bTag",         False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                          False),
  ("xsection",                        87.3),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("reHLT",                           True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/veelken/VHBBHeppyV25tthtautau/MC_fastsim/TTTo2L2Nu_TuneCUETP8M2_ttHtranche3_13TeV-powheg-pythia8/VHBB_HEPPY_V25tthtautau_TTTo2L2Nu_TuneCUETP8M2_ttHtranche3_13TeV-powheg-Py8__matze-faster_v8_ttjets_dl_maod_p2_3a2fa29ab1d54ae0995b28f27b405be9-v1/170208_163923"),
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
  ("nof_files",                       3642),
  ("nof_events",                      90528028),
  ("use_HIP_mitigation_bTag",         False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                          False),
  ("xsection",                        87.3),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("reHLT",                           True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau/MC_fastsim/TTTo2L2Nu_TuneCUETP8M2_ttHtranche3_13TeV-powheg-pythia8/VHBB_HEPPY_V25tthtautau_TTTo2L2Nu_TuneCUETP8M2_ttHtranche3_13TeV-powheg-Py8__matze-faster_v8_ttjets_dl_maod_p3_3a2fa29ab1d54ae0995b28f27b405be9-v1/170208_163840"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/TGJets_TuneCUETP8M1_13TeV_amcatnlo_madspin_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "Rares"),
  ("process_name_specific",           "TGJets_ext1"),
  ("nof_files",                       157),
  ("nof_events",                      364227),
  ("use_HIP_mitigation_bTag",         False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                          True),
  ("xsection",                        2.967),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("reHLT",                           True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/rdewanje/VHBBHeppyV25tthtautau/MC/TGJets_TuneCUETP8M1_13TeV_amcatnlo_madspin_pythia8/VHBB_HEPPY_V25tthtautau_TGJets_TuneCUETP8M1_13TeV_amcatnlo_madspin_Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6_ext1-v1/170207_123908"),
        ("selection", "*"),
        ("blacklist", [91, 141]),
      ]),
    ]
  ),
])

samples_2016["/TGJets_TuneCUETP8M1_13TeV_amcatnlo_madspin_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "Rares"),
  ("process_name_specific",           "TGJets"),
  ("nof_files",                       30),
  ("nof_events",                      364227),
  ("use_HIP_mitigation_bTag",         False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                          True),
  ("xsection",                        2.967),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("reHLT",                           True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/rdewanje/VHBBHeppyV25tthtautau/MC/TGJets_TuneCUETP8M1_13TeV_amcatnlo_madspin_pythia8/VHBB_HEPPY_V25tthtautau_TGJets_TuneCUETP8M1_13TeV_amcatnlo_madspin_Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6-v1/170209_095835"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/WJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "EWK"),
  ("process_name_specific",           "WJetsToLNu"),
  ("nof_files",                       2417),
  ("nof_events",                      16484092),
  ("use_HIP_mitigation_bTag",         False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                          True),
  ("xsection",                        61526.7),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("reHLT",                           True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/mario/VHBBHeppyV25tthtautau/MC/WJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/VHBB_HEPPY_V25tthtautau_WJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6-v1/170208_121448"),
        ("selection", "*"),
        ("blacklist", [511, 540]),
      ]),
    ]
  ),
])
samples_2016["/tZq_ll_4f_13TeV-amcatnlo-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "Rares"),
  ("process_name_specific",           "tZq_ll_4f"),
  ("nof_files",                       1464),
  ("nof_events",                      3806635),
  ("use_HIP_mitigation_bTag",         False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                          True),
  ("xsection",                        0.0758),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("reHLT",                           True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/mario/VHBBHeppyV25tthtautau/MC/tZq_ll_4f_13TeV-amcatnlo-pythia8/VHBB_HEPPY_V25tthtautau_tZq_ll_4f_13TeV-amcatnlo-Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6_ext1-v1/170208_121616"),
        ("selection", "*"),
        ("blacklist", [76, 213, 344, 424, 970, 1009, 1173, 1249, 1255, 1308, 1333, 1380, 1388, 1389, 1444]),
      ]),
    ]
  ),
])
samples_2016["/MuonEG/Run2016D-23Sep2016-v1/MINIAOD"] = OD([
  ("type",                            "data"),
  ("sample_category",                 "data_obs"),
  ("process_name_specific",           "MuonEG_Run2016D_v1"),
  ("nof_files",                       4296),
  ("nof_events",                      23482352),
  ("use_HIP_mitigation_bTag",         True),
  ("use_HIP_mitigation_mediumMuonId", True),
  ("use_it",                          True),
  ("triggers",                        ['1e1mu', '2e1mu', '1e2mu']),
  ("reHLT",                           True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/rdewanje/VHBBHeppyV25tthtautau/MuonEG/VHBB_HEPPY_V25tthtautau_MuonEG__Run2016D-23Sep2016-v1/170207_125438"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/DoubleMuon/Run2016G-23Sep2016-v1/MINIAOD"] = OD([
  ("type",                            "data"),
  ("sample_category",                 "data_obs"),
  ("process_name_specific",           "DoubleMuon_Run2016G_v1"),
  ("nof_files",                       1527),
  ("nof_events",                      45235604),
  ("use_HIP_mitigation_bTag",         False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                          True),
  ("triggers",                        ['2mu', '3mu']),
  ("reHLT",                           True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v2/DoubleMuon/VHBB_HEPPY_V25tthtautau_v2_DoubleMuon__Run2016G-23Sep2016-v1/170217_151055"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/SingleMuon/Run2016H-PromptReco-v2/MINIAOD"] = OD([
  ("type",                            "data"),
  ("sample_category",                 "data_obs"),
  ("process_name_specific",           "SingleMuon_Run2016H_v2_promptReco"),
  ("nof_files",                       8180),
  ("nof_events",                      171134793),
  ("use_HIP_mitigation_bTag",         False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                          True),
  ("triggers",                        ['1mu']),
  ("reHLT",                           True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau/SingleMuon/VHBB_HEPPY_V25tthtautau_SingleMuon__Run2016H-PromptReco-v2/170215_143417"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/SingleMuon/Run2016F-23Sep2016-v1/MINIAOD"] = OD([
  ("type",                            "data"),
  ("sample_category",                 "data_obs"),
  ("process_name_specific",           "SingleMuon_Run2016F_v1"),
  ("nof_files",                       641),
  ("nof_events",                      65489554),
  ("use_HIP_mitigation_bTag",         True),
  ("use_HIP_mitigation_mediumMuonId", True),
  ("use_it",                          True),
  ("triggers",                        ['1mu']),
  ("reHLT",                           True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v2/SingleMuon/VHBB_HEPPY_V25tthtautau_v2_SingleMuon__Run2016F-23Sep2016-v1/170217_153044"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/Tau/Run2016F-23Sep2016-v1/MINIAOD"] = OD([
  ("type",                            "data"),
  ("sample_category",                 "data_obs"),
  ("process_name_specific",           "Tau_Run2016F_v1"),
  ("nof_files",                       2798),
  ("nof_events",                      40549716),
  ("use_HIP_mitigation_bTag",         True),
  ("use_HIP_mitigation_mediumMuonId", True),
  ("use_it",                          True),
  ("triggers",                        ['1e1tau', '1mu1tau', '2tau']),
  ("reHLT",                           True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_HLT/Tau/VHBB_HEPPY_V25tthtautau_HLT_Tau__Run2016F-23Sep2016-v1/170216_182849"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/THW_Hincl_13TeV-madgraph-pythia8_TuneCUETP8M1/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "tH"),
  ("process_name_specific",           "THW"),
  ("nof_files",                       75),
  ("nof_events",                      1499036),
  ("use_HIP_mitigation_bTag",         False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                          True),
  ("xsection",                        0.057051),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("reHLT",                           True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_tHq_tHW/MC/THW_Hincl_13TeV-madgraph-pythia8_TuneCUETP8M1/VHBB_HEPPY_V25tthtautau_tHq_tHW_THW_Hincl_13TeV-madgraph-Py8_TuneCUETP8M1__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6-v1/170502_162842"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "signal"),
  ("process_name_specific",           "ttHJetToNonbb_M125_amcatnlo"),
  ("nof_files",                       1018),
  ("nof_events",                      2970051),
  ("use_HIP_mitigation_bTag",         False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                          True),
  ("xsection",                        0.2151),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("reHLT",                           True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau/MC/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/VHBB_HEPPY_V25tthtautau_ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_Py8_mWCutfix__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6_ext1-v1/170207_122849"),
        ("selection", "*"),
        ("blacklist", [645, 835, 909, 986]),
      ]),
    ]
  ),
])
samples_2016["/DoubleEG/Run2016G-23Sep2016-v1/MINIAOD"] = OD([
  ("type",                            "data"),
  ("sample_category",                 "data_obs"),
  ("process_name_specific",           "DoubleEG_Run2016G_v1"),
  ("nof_files",                       1544),
  ("nof_events",                      78797031),
  ("use_HIP_mitigation_bTag",         False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                          True),
  ("triggers",                        ['2e', '3e']),
  ("reHLT",                           True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v2/DoubleEG/VHBB_HEPPY_V25tthtautau_v2_DoubleEG__Run2016G-23Sep2016-v1/170218_172915"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/TTZToLL_M-1to10_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "TTZ"),
  ("process_name_specific",           "TTZToLL_M-1to10"),
  ("nof_files",                       25),
  ("nof_events",                      246798),
  ("use_HIP_mitigation_bTag",         False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                          True),
  ("xsection",                        0.0493),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("reHLT",                           True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau/MC/TTZToLL_M-1to10_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/VHBB_HEPPY_V25tthtautau_TTZToLL_M-1to10_TuneCUETP8M1_13TeV-madgraphMLM-Py8__RunIISummer16MAv2-80r2as_2016_TrancheIV_v6-v1/170207_124356"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/WWTo2L2Nu_13TeV-powheg/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "EWK"),
  ("process_name_specific",           "WWTo2L2Nu"),
  ("nof_files",                       202),
  ("nof_events",                      1999193),
  ("use_HIP_mitigation_bTag",         False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                          True),
  ("xsection",                        10.481),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("reHLT",                           True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/veelken/VHBBHeppyV25tthtautau/MC/WWTo2L2Nu_13TeV-powheg/VHBB_HEPPY_V25tthtautau_WWTo2L2Nu_13TeV-powheg__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6-v1/170207_134602"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/SingleElectron/Run2016B-23Sep2016-v3/MINIAOD"] = OD([
  ("type",                            "data"),
  ("sample_category",                 "data_obs"),
  ("process_name_specific",           "SingleElectron_Run2016B_v3"),
  ("nof_files",                       5982),
  ("nof_events",                      246440440),
  ("use_HIP_mitigation_bTag",         True),
  ("use_HIP_mitigation_mediumMuonId", True),
  ("use_it",                          True),
  ("triggers",                        ['1e']),
  ("reHLT",                           True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v3/SingleElectron/VHBB_HEPPY_V25tthtautau_v3_SingleElectron__Run2016B-23Sep2016-v3/170220_170550"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/GluGluHToZZTo4L_M125_13TeV_powheg2_JHUgenV6_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "additional_signal_overlap"),
  ("process_name_specific",           "GluGluHToZZTo4L"),
  ("nof_files",                       101),
  ("nof_events",                      999912),
  ("use_HIP_mitigation_bTag",         False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                          True),
  ("xsection",                        0.0119),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("reHLT",                           True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/veelken/VHBBHeppyV25tthtautau/MC/GluGluHToZZTo4L_M125_13TeV_powheg2_JHUgenV6_pythia8/VHBB_HEPPY_V25tthtautau_GluGluHToZZTo4L_M125_13TeV_powheg2_JHUgenV6_Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6-v1/170207_133635"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/DoubleMuon/Run2016D-23Sep2016-v1/MINIAOD"] = OD([
  ("type",                            "data"),
  ("sample_category",                 "data_obs"),
  ("process_name_specific",           "DoubleMuon_Run2016D_v1"),
  ("nof_files",                       1003),
  ("nof_events",                      33861745),
  ("use_HIP_mitigation_bTag",         True),
  ("use_HIP_mitigation_mediumMuonId", True),
  ("use_it",                          True),
  ("triggers",                        ['2mu', '3mu']),
  ("reHLT",                           True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v2/DoubleMuon/VHBB_HEPPY_V25tthtautau_v2_DoubleMuon__Run2016D-23Sep2016-v1/170218_171554"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/DoubleMuon/Run2016B-23Sep2016-v3/MINIAOD"] = OD([
  ("type",                            "data"),
  ("sample_category",                 "data_obs"),
  ("process_name_specific",           "DoubleMuon_Run2016B_v3"),
  ("nof_files",                       1966),
  ("nof_events",                      82535526),
  ("use_HIP_mitigation_bTag",         True),
  ("use_HIP_mitigation_mediumMuonId", True),
  ("use_it",                          True),
  ("triggers",                        ['2mu', '3mu']),
  ("reHLT",                           True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v2/DoubleMuon/VHBB_HEPPY_V25tthtautau_v2_DoubleMuon__Run2016B-23Sep2016-v3/170218_175649"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/DoubleMuon/Run2016H-PromptReco-v3/MINIAOD"] = OD([
  ("type",                            "data"),
  ("sample_category",                 "data_obs"),
  ("process_name_specific",           "DoubleMuon_Run2016H_v3_promptReco"),
  ("nof_files",                       133),
  ("nof_events",                      1219733),
  ("use_HIP_mitigation_bTag",         False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                          True),
  ("triggers",                        ['2mu', '3mu']),
  ("reHLT",                           True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v3/DoubleMuon/VHBB_HEPPY_V25tthtautau_v3_DoubleMuon__Run2016H-PromptReco-v3/170221_214504"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/matze-faster_v9_ttW_maod_54aa74f75231422e9f4d3766cb92a64a-v1/USER"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "TTW"),
  ("process_name_specific",           "TTWJetsToLNu_fastsim"),
  ("nof_files",                       1408),
  ("nof_events",                      7158309),
  ("use_HIP_mitigation_bTag",         False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                          False),
  ("xsection",                        0.2043),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("reHLT",                           True),
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
samples_2016["/SingleElectron/Run2016H-PromptReco-v3/MINIAOD"] = OD([
  ("type",                            "data"),
  ("sample_category",                 "data_obs"),
  ("process_name_specific",           "SingleElectron_Run2016H_v3_promptReco"),
  ("nof_files",                       136),
  ("nof_events",                      3191585),
  ("use_HIP_mitigation_bTag",         False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                          True),
  ("triggers",                        ['1e']),
  ("reHLT",                           True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v3/SingleElectron/VHBB_HEPPY_V25tthtautau_v3_SingleElectron__Run2016H-PromptReco-v3/170222_145637"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/DoubleEG/Run2016D-23Sep2016-v1/MINIAOD"] = OD([
  ("type",                            "data"),
  ("sample_category",                 "data_obs"),
  ("process_name_specific",           "DoubleEG_Run2016D_v1"),
  ("nof_files",                       1008),
  ("nof_events",                      53324960),
  ("use_HIP_mitigation_bTag",         True),
  ("use_HIP_mitigation_mediumMuonId", True),
  ("use_it",                          True),
  ("triggers",                        ['2e', '3e']),
  ("reHLT",                           True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v2/DoubleEG/VHBB_HEPPY_V25tthtautau_v2_DoubleEG__Run2016D-23Sep2016-v1/170218_171438"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/MuonEG/Run2016C-23Sep2016-v1/MINIAOD"] = OD([
  ("type",                            "data"),
  ("sample_category",                 "data_obs"),
  ("process_name_specific",           "MuonEG_Run2016C_v1"),
  ("nof_files",                       621),
  ("nof_events",                      15405678),
  ("use_HIP_mitigation_bTag",         True),
  ("use_HIP_mitigation_mediumMuonId", True),
  ("use_it",                          True),
  ("triggers",                        ['1e1mu', '2e1mu', '1e2mu']),
  ("reHLT",                           True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v2/MuonEG/VHBB_HEPPY_V25tthtautau_v2_MuonEG__Run2016C-23Sep2016-v1/170218_170759"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "Rares"),
  ("process_name_specific",           "ZGTo2LG"),
  ("nof_files",                       1447),
  ("nof_events",                      9758652),
  ("use_HIP_mitigation_bTag",         False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                          True),
  ("xsection",                        131.3),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("reHLT",                           True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/rdewanje/VHBBHeppyV25tthtautau/MC/ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/VHBB_HEPPY_V25tthtautau_ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6_ext1-v1/170207_124611"),
        ("selection", "*"),
        ("blacklist", [52, 77, 92, 105, 239, 248, 296, 310, 354, 747, 911]),
      ]),
    ]
  ),
])
samples_2016["/WpWpJJ_EWK-QCD_TuneCUETP8M1_13TeV-madgraph-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "Rares"),
  ("process_name_specific",           "WpWpJJ_EWK-QCD"),
  ("nof_files",                       16),
  ("nof_events",                      149601),
  ("use_HIP_mitigation_bTag",         False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                          True),
  ("xsection",                        0.03711),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("reHLT",                           True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau/MC/WpWpJJ_EWK-QCD_TuneCUETP8M1_13TeV-madgraph-pythia8/VHBB_HEPPY_V25tthtautau_WpWpJJ_EWK-QCD_TuneCUETP8M1_13TeV-madgraph-Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6-v1/170207_125131"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "EWK"),
  ("process_name_specific",           "DYJetsToLL_M-10to50"),
  ("nof_files",                       1782),
  ("nof_events",                      35273261),
  ("use_HIP_mitigation_bTag",         False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                          True),
  ("xsection",                        18610.0),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("reHLT",                           True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v3/MC/DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/VHBB_HEPPY_V25tthtautau_v3_DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-madgraphMLM-Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6-v1/170225_232933"),
        ("selection", "*"),
        ("blacklist", [1237] + [800]), # explicitly added 800, corrupted but not zombie
      ]),
    ]
  ),
])
samples_2016["/SingleElectron/Run2016H-PromptReco-v2/MINIAOD"] = OD([
  ("type",                            "data"),
  ("sample_category",                 "data_obs"),
  ("process_name_specific",           "SingleElectron_Run2016H_v2_promptReco"),
  ("nof_files",                       7576),
  ("nof_events",                      126863489),
  ("use_HIP_mitigation_bTag",         False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                          True),
  ("triggers",                        ['1e']),
  ("reHLT",                           True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau/SingleElectron/VHBB_HEPPY_V25tthtautau_SingleElectron__Run2016H-PromptReco-v2/170215_145016"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/DoubleMuon/Run2016H-PromptReco-v2/MINIAOD"] = OD([
  ("type",                            "data"),
  ("sample_category",                 "data_obs"),
  ("process_name_specific",           "DoubleMuon_Run2016H_v2_promptReco"),
  ("nof_files",                       8180),
  ("nof_events",                      48093751),
  ("use_HIP_mitigation_bTag",         False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                          True),
  ("triggers",                        ['2mu', '3mu']),
  ("reHLT",                           True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau/DoubleMuon/VHBB_HEPPY_V25tthtautau_DoubleMuon__Run2016H-PromptReco-v2/170215_142956"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/SingleMuon/Run2016D-23Sep2016-v1/MINIAOD"] = OD([
  ("type",                            "data"),
  ("sample_category",                 "data_obs"),
  ("process_name_specific",           "SingleMuon_Run2016D_v1"),
  ("nof_files",                       1003),
  ("nof_events",                      98017996),
  ("use_HIP_mitigation_bTag",         True),
  ("use_HIP_mitigation_mediumMuonId", True),
  ("use_it",                          True),
  ("triggers",                        ['1mu']),
  ("reHLT",                           True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v2/SingleMuon/VHBB_HEPPY_V25tthtautau_v2_SingleMuon__Run2016D-23Sep2016-v1/170218_171316"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "TT"),
  ("process_name_specific",           "ST_tW_antitop_5f_inclusiveDecays"),
  ("nof_files",                       699),
  ("nof_events",                      6884378),
  ("use_HIP_mitigation_bTag",         False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                          True),
  ("xsection",                        35.6),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("reHLT",                           True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau/MC/ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1/VHBB_HEPPY_V25tthtautau_ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-Py8_TuneCUETP8M1__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6_ext1-v1/170207_123614"),
        ("selection", "*"),
        ("blacklist", [38, 98, 251, 530, 604]),
      ]),
    ]
  ),
])
samples_2016["/ST_t-channel_top_4f_inclusiveDecays_13TeV-powhegV2-madspin-pythia8_TuneCUETP8M1/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "TT"),
  ("process_name_specific",           "ST_t-channel_top_4f_inclusiveDecays"),
  ("nof_files",                       6784),
  ("nof_events",                      67073431),
  ("use_HIP_mitigation_bTag",         False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                          True),
  ("xsection",                        136.02),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("reHLT",                           True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/mario/VHBBHeppyV25tthtautau/MC/ST_t-channel_top_4f_inclusiveDecays_13TeV-powhegV2-madspin-pythia8_TuneCUETP8M1/VHBB_HEPPY_V25tthtautau_ST_t-channel_top_4f_inclusiveDecays_13TeV-powhegV2-madspin-Py8_TuneCUETP8M1__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6-v1/170208_120156"),
        ("selection", "*"),
        ("blacklist", [511, 533, 573, 703, 729, 741, 839, 843, 1007, 1024, 1501, 2776, 2959, 3223, 3491, 4701, 4914]),
      ]),
    ]
  ),
])
samples_2016["/SingleMuon/Run2016G-23Sep2016-v1/MINIAOD"] = OD([
  ("type",                            "data"),
  ("sample_category",                 "data_obs"),
  ("process_name_specific",           "SingleMuon_Run2016G_v1"),
  ("nof_files",                       1527),
  ("nof_events",                      149916849),
  ("use_HIP_mitigation_bTag",         False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                          True),
  ("triggers",                        ['1mu']),
  ("reHLT",                           True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v2/SingleMuon/VHBB_HEPPY_V25tthtautau_v2_SingleMuon__Run2016G-23Sep2016-v1/170217_151611"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/DoubleEG/Run2016H-PromptReco-v3/MINIAOD"] = OD([
  ("type",                            "data"),
  ("sample_category",                 "data_obs"),
  ("process_name_specific",           "DoubleEG_Run2016H_v3_promptReco"),
  ("nof_files",                       136),
  ("nof_events",                      2295554),
  ("use_HIP_mitigation_bTag",         False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                          True),
  ("triggers",                        ['2e', '3e']),
  ("reHLT",                           True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v3/DoubleEG/VHBB_HEPPY_V25tthtautau_v3_DoubleEG__Run2016H-PromptReco-v3/170221_105758"),
        ("selection", "*"),
        ("blacklist", [128, 130, 133]),
      ]),
    ]
  ),
])
samples_2016["/WWZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "Rares"),
  ("process_name_specific",           "WWZ"),
  ("nof_files",                       26),
  ("nof_events",                      221511),
  ("use_HIP_mitigation_bTag",         False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                          True),
  ("xsection",                        0.1651),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("reHLT",                           True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/veelken/VHBBHeppyV25tthtautau/MC/WWZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8/VHBB_HEPPY_V25tthtautau_WWZ_TuneCUETP8M1_13TeV-amcatnlo-Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6-v1/170207_135405"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/MuonEG/Run2016G-23Sep2016-v1/MINIAOD"] = OD([
  ("type",                            "data"),
  ("sample_category",                 "data_obs"),
  ("process_name_specific",           "MuonEG_Run2016G_v1"),
  ("nof_files",                       1527),
  ("nof_events",                      33854612),
  ("use_HIP_mitigation_bTag",         False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                          True),
  ("triggers",                        ['1e1mu', '2e1mu', '1e2mu']),
  ("reHLT",                           True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v2/MuonEG/VHBB_HEPPY_V25tthtautau_v2_MuonEG__Run2016G-23Sep2016-v1/170218_172759"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/ST_t-channel_antitop_4f_inclusiveDecays_13TeV-powhegV2-madspin-pythia8_TuneCUETP8M1/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "TT"),
  ("process_name_specific",           "ST_t-channel_antitop_4f_inclusiveDecays"),
  ("nof_files",                       3916),
  ("nof_events",                      38795360),
  ("use_HIP_mitigation_bTag",         False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                          True),
  ("xsection",                        80.95),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("reHLT",                           True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau/MC/ST_t-channel_antitop_4f_inclusiveDecays_13TeV-powhegV2-madspin-pythia8_TuneCUETP8M1/VHBB_HEPPY_V25tt_ST_t-channel_antitop_4f_inclusiveDecays_13TeV-powhegV2-madspin-Py8_TuneCUETP8M1__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6-v1/170209_102511"),
        ("selection", "*"),
        ("blacklist", [859, 1664]),
      ]),
    ]
  ),
])
samples_2016["/DoubleEG/Run2016E-23Sep2016-v1/MINIAOD"] = OD([
  ("type",                            "data"),
  ("sample_category",                 "data_obs"),
  ("process_name_specific",           "DoubleEG_Run2016E_v1"),
  ("nof_files",                       906),
  ("nof_events",                      49877710),
  ("use_HIP_mitigation_bTag",         True),
  ("use_HIP_mitigation_mediumMuonId", True),
  ("use_it",                          True),
  ("triggers",                        ['2e', '3e']),
  ("reHLT",                           True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v2/DoubleEG/VHBB_HEPPY_V25tthtautau_v2_DoubleEG__Run2016E-23Sep2016-v1/170218_171718"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/ST_s-channel_4f_leptonDecays_13TeV-amcatnlo-pythia8_TuneCUETP8M1/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "TT"),
  ("process_name_specific",           "ST_s-channel_4f_leptonDecays"),
  ("nof_files",                       100),
  ("nof_events",                      622688),
  ("use_HIP_mitigation_bTag",         False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                          True),
  ("xsection",                        3.68),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("reHLT",                           True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/rdewanje/VHBBHeppyV25tthtautau/MC/ST_s-channel_4f_leptonDecays_13TeV-amcatnlo-pythia8_TuneCUETP8M1/VHBB_HEPPY_V25tthtautau_ST_s-channel_4f_leptonDecays_13TeV-amcatnlo-Py8_TuneCUETP8M1__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6-v1/170207_123409"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/ST_tW_top_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "TT"),
  ("process_name_specific",           "ST_tW_top_5f_inclusiveDecays"),
  ("nof_files",                       702),
  ("nof_events",                      6942671),
  ("use_HIP_mitigation_bTag",         False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                          True),
  ("xsection",                        35.6),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("reHLT",                           True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/veelken/VHBBHeppyV25tthtautau/MC/ST_tW_top_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1/VHBB_HEPPY_V25tthtautau_ST_tW_top_5f_inclusiveDecays_13TeV-powheg-Py8_TuneCUETP8M1__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6_ext1-v1/170207_133952"),
        ("selection", "*"),
        ("blacklist", [215]),
      ]),
    ]
  ),
])
samples_2016["/SingleElectron/Run2016D-23Sep2016-v1/MINIAOD"] = OD([
  ("type",                            "data"),
  ("sample_category",                 "data_obs"),
  ("process_name_specific",           "SingleElectron_Run2016D_v1"),
  ("nof_files",                       3024),
  ("nof_events",                      148167727),
  ("use_HIP_mitigation_bTag",         True),
  ("use_HIP_mitigation_mediumMuonId", True),
  ("use_it",                          True),
  ("triggers",                        ['1e']),
  ("reHLT",                           True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v3/SingleElectron/VHBB_HEPPY_V25tthtautau_v3_SingleElectron__Run2016D-23Sep2016-v1/170220_171118"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/ZZZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "Rares"),
  ("process_name_specific",           "ZZZ"),
  ("nof_files",                       25),
  ("nof_events",                      213100),
  ("use_HIP_mitigation_bTag",         False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                          True),
  ("xsection",                        0.01398),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("reHLT",                           True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau/MC/ZZZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8/VHBB_HEPPY_V25tthtautau_ZZZ_TuneCUETP8M1_13TeV-amcatnlo-Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6-v1/170207_125415"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/SingleMuon/Run2016C-23Sep2016-v1/MINIAOD"] = OD([
  ("type",                            "data"),
  ("sample_category",                 "data_obs"),
  ("process_name_specific",           "SingleMuon_Run2016C_v1"),
  ("nof_files",                       1862),
  ("nof_events",                      67441308),
  ("use_HIP_mitigation_bTag",         True),
  ("use_HIP_mitigation_mediumMuonId", True),
  ("use_it",                          True),
  ("triggers",                        ['1mu']),
  ("reHLT",                           True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v3/SingleMuon/VHBB_HEPPY_V25tthtautau_v3_SingleMuon__Run2016C-23Sep2016-v1/170221_173556"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/WZTo3LNu_TuneCUETP8M1_13TeV-powheg-pythia8/matze-faster_v9_WZ_maod_54aa74f75231422e9f4d3766cb92a64a-v1/USER"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "EWK"),
  ("process_name_specific",           "WZTo3LNu_fastsim"),
  ("nof_files",                       1876),
  ("nof_events",                      18814814),
  ("use_HIP_mitigation_bTag",         False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                          False),
  ("xsection",                        4.102),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("reHLT",                           True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/rdewanje/VHBBHeppyV25tthtautau/MC_fastsim/WZTo3LNu_TuneCUETP8M1_13TeV-powheg-pythia8/VHBB_HEPPY_V25tthtautau_WZTo3LNu_TuneCUETP8M1_13TeV-powheg-Py8__matze-faster_v9_WZ_maod_54aa74f75231422e9f4d3766cb92a64a-v1/170209_090741"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/DoubleMuon/Run2016E-23Sep2016-v1/MINIAOD"] = OD([
  ("type",                            "data"),
  ("sample_category",                 "data_obs"),
  ("process_name_specific",           "DoubleMuon_Run2016E_v1"),
  ("nof_files",                       896),
  ("nof_events",                      28246946),
  ("use_HIP_mitigation_bTag",         True),
  ("use_HIP_mitigation_mediumMuonId", True),
  ("use_it",                          True),
  ("triggers",                        ['2mu', '3mu']),
  ("reHLT",                           True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v2/DoubleMuon/VHBB_HEPPY_V25tthtautau_v2_DoubleMuon__Run2016E-23Sep2016-v1/170218_180126"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/SingleElectron/Run2016E-23Sep2016-v1/MINIAOD"] = OD([
  ("type",                            "data"),
  ("sample_category",                 "data_obs"),
  ("process_name_specific",           "SingleElectron_Run2016E_v1"),
  ("nof_files",                       2716),
  ("nof_events",                      117321545),
  ("use_HIP_mitigation_bTag",         True),
  ("use_HIP_mitigation_mediumMuonId", True),
  ("use_it",                          True),
  ("triggers",                        ['1e']),
  ("reHLT",                           True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v3/SingleElectron/VHBB_HEPPY_V25tthtautau_v3_SingleElectron__Run2016E-23Sep2016-v1/170220_171247"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/SingleMuon/Run2016H-PromptReco-v3/MINIAOD"] = OD([
  ("type",                            "data"),
  ("sample_category",                 "data_obs"),
  ("process_name_specific",           "SingleMuon_Run2016H_v3_promptReco"),
  ("nof_files",                       190),
  ("nof_events",                      4393222),
  ("use_HIP_mitigation_bTag",         False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                          True),
  ("triggers",                        ['1mu']),
  ("reHLT",                           True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau/SingleMuon/VHBB_HEPPY_V25tthtautau_SingleMuon__Run2016H-PromptReco-v3/170215_144050"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/WWW_4F_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "Rares"),
  ("process_name_specific",           "WWW_4F"),
  ("nof_files",                       24),
  ("nof_events",                      210465),
  ("use_HIP_mitigation_bTag",         False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                          True),
  ("xsection",                        0.2086),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("reHLT",                           True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/veelken/VHBBHeppyV25tthtautau/MC/WWW_4F_TuneCUETP8M1_13TeV-amcatnlo-pythia8/VHBB_HEPPY_V25tthtautau_WWW_4F_TuneCUETP8M1_13TeV-amcatnlo-Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6-v1/170207_135107"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/MuonEG/Run2016E-23Sep2016-v1/MINIAOD"] = OD([
  ("type",                            "data"),
  ("sample_category",                 "data_obs"),
  ("process_name_specific",           "MuonEG_Run2016E_v1"),
  ("nof_files",                       896),
  ("nof_events",                      22519303),
  ("use_HIP_mitigation_bTag",         True),
  ("use_HIP_mitigation_mediumMuonId", True),
  ("use_it",                          True),
  ("triggers",                        ['1e1mu', '2e1mu', '1e2mu']),
  ("reHLT",                           True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v2/MuonEG/VHBB_HEPPY_V25tthtautau_v2_MuonEG__Run2016E-23Sep2016-v1/170218_172335"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/DoubleEG/Run2016B-23Sep2016-v3/MINIAOD"] = OD([
  ("type",                            "data"),
  ("sample_category",                 "data_obs"),
  ("process_name_specific",           "DoubleEG_Run2016B_v3"),
  ("nof_files",                       8546),
  ("nof_events",                      143073268),
  ("use_HIP_mitigation_bTag",         True),
  ("use_HIP_mitigation_mediumMuonId", True),
  ("use_it",                          True),
  ("triggers",                        ['2e', '3e']),
  ("reHLT",                           True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau/DoubleEG/VHBB_HEPPY_V25tthtautau_DoubleEG__Run2016B-23Sep2016-v3_forceResubmit2/170219_190454"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/DoubleEG/Run2016H-PromptReco-v2/MINIAOD"] = OD([
  ("type",                            "data"),
  ("sample_category",                 "data_obs"),
  ("process_name_specific",           "DoubleEG_Run2016H_v2_promptReco"),
  ("nof_files",                       7577),
  ("nof_events",                      84344490),
  ("use_HIP_mitigation_bTag",         False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                          True),
  ("triggers",                        ['2e', '3e']),
  ("reHLT",                           True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau/DoubleEG/VHBB_HEPPY_V25tthtautau_DoubleEG__Run2016H-PromptReco-v2/170215_142837"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/WZZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "Rares"),
  ("process_name_specific",           "WZZ"),
  ("nof_files",                       25),
  ("nof_events",                      216296),
  ("use_HIP_mitigation_bTag",         False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                          True),
  ("xsection",                        0.05565),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("reHLT",                           True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau/MC/WZZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8/VHBB_HEPPY_V25tthtautau_WZZ_TuneCUETP8M1_13TeV-amcatnlo-Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6-v1/170207_125000"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/Tau/Run2016E-23Sep2016-v1/MINIAOD"] = OD([
  ("type",                            "data"),
  ("sample_category",                 "data_obs"),
  ("process_name_specific",           "Tau_Run2016E_v1"),
  ("nof_files",                       3886),
  ("nof_events",                      58348773),
  ("use_HIP_mitigation_bTag",         True),
  ("use_HIP_mitigation_mediumMuonId", True),
  ("use_it",                          True),
  ("triggers",                        ['1e1tau', '1mu1tau', '2tau']),
  ("reHLT",                           True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_HLT/Tau/VHBB_HEPPY_V25tthtautau_HLT_Tau__Run2016E-23Sep2016-v1/170216_182541"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/TTTT_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "Rares"),
  ("process_name_specific",           "TTTT"),
  ("nof_files",                       26),
  ("nof_events",                      104770),
  ("use_HIP_mitigation_bTag",         False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                          True),
  ("xsection",                        0.009103),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("reHLT",                           True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau/MC/TTTT_TuneCUETP8M1_13TeV-amcatnlo-pythia8/VHBB_HEPPY_V25tthtautau_TTTT_TuneCUETP8M1_13TeV-amcatnlo-Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6-v1/170207_123853"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/DoubleMuon/Run2016C-23Sep2016-v1/MINIAOD"] = OD([
  ("type",                            "data"),
  ("sample_category",                 "data_obs"),
  ("process_name_specific",           "DoubleMuon_Run2016C_v1"),
  ("nof_files",                       621),
  ("nof_events",                      27934629),
  ("use_HIP_mitigation_bTag",         True),
  ("use_HIP_mitigation_mediumMuonId", True),
  ("use_it",                          True),
  ("triggers",                        ['2mu', '3mu']),
  ("reHLT",                           True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v2/DoubleMuon/VHBB_HEPPY_V25tthtautau_v2_DoubleMuon__Run2016C-23Sep2016-v1/170218_171035"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/WZTo3LNu_TuneCUETP8M1_13TeV-powheg-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "EWK"),
  ("process_name_specific",           "WZTo3LNu"),
  ("nof_files",                       200),
  ("nof_events",                      1993307),
  ("use_HIP_mitigation_bTag",         False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                          True),
  ("xsection",                        4.42965),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("reHLT",                           True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau/MC/WZTo3LNu_TuneCUETP8M1_13TeV-powheg-pythia8/VHBB_HEPPY_V25tthtautau_WZTo3LNu_TuneCUETP8M1_13TeV-powheg-Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6-v1/170207_124837"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/SingleMuon/Run2016E-23Sep2016-v1/MINIAOD"] = OD([
  ("type",                            "data"),
  ("sample_category",                 "data_obs"),
  ("process_name_specific",           "SingleMuon_Run2016E_v1"),
  ("nof_files",                       2688),
  ("nof_events",                      90984718),
  ("use_HIP_mitigation_bTag",         True),
  ("use_HIP_mitigation_mediumMuonId", True),
  ("use_it",                          True),
  ("triggers",                        ['1mu']),
  ("reHLT",                           True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v3/SingleMuon/VHBB_HEPPY_V25tthtautau_v3_SingleMuon__Run2016E-23Sep2016-v1/170220_170712"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/MuonEG/Run2016H-PromptReco-v3/MINIAOD"] = OD([
  ("type",                            "data"),
  ("sample_category",                 "data_obs"),
  ("process_name_specific",           "MuonEG_Run2016H_v3_promptReco"),
  ("nof_files",                       190),
  ("nof_events",                      770494),
  ("use_HIP_mitigation_bTag",         False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                          True),
  ("triggers",                        ['1e1mu', '2e1mu', '1e2mu']),
  ("reHLT",                           True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau/MuonEG/VHBB_HEPPY_V25tthtautau_MuonEG__Run2016H-PromptReco-v3/170215_143932"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/Tau/Run2016C-23Sep2016-v1/MINIAOD"] = OD([
  ("type",                            "data"),
  ("sample_category",                 "data_obs"),
  ("process_name_specific",           "Tau_Run2016C_v1"),
  ("nof_files",                       2688),
  ("nof_events",                      36931473),
  ("use_HIP_mitigation_bTag",         True),
  ("use_HIP_mitigation_mediumMuonId", True),
  ("use_it",                          True),
  ("triggers",                        ['1e1tau', '1mu1tau', '2tau']),
  ("reHLT",                           True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_HLT/Tau/VHBB_HEPPY_V25tthtautau_HLT_Tau__Run2016C-23Sep2016-v1/170216_182257"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/ttHToNonbb_M125_TuneCUETP8M2_ttHtranche3_13TeV-powheg-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "signal"),
  ("process_name_specific",           "ttHToNonbb_M125_powheg"),
  ("nof_files",                       402),
  ("nof_events",                      3858848),
  ("use_HIP_mitigation_bTag",         False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                          False),
  ("xsection",                        0.2151),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("reHLT",                           True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/rdewanje/VHBBHeppyV25tthtautau/MC/ttHToNonbb_M125_TuneCUETP8M2_ttHtranche3_13TeV-powheg-pythia8/VHBB_HEPPY_V25tthtautau_ttHToNonbb_M125_TuneCUETP8M2_ttHtranche3_13TeV-powheg-Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6-v1/170207_122923"),
        ("selection", "*"),
        ("blacklist", [137, 281, 304, 335, 397]),
      ]),
    ]
  ),
])
samples_2016["/ZZTo4L_13TeV_powheg_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "EWK"),
  ("process_name_specific",           "ZZTo4L"),
  ("nof_files",                       673),
  ("nof_events",                      6611207),
  ("use_HIP_mitigation_bTag",         False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                          True),
  ("xsection",                        1.256),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("reHLT",                           True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau/MC/ZZTo4L_13TeV_powheg_pythia8/VHBB_HEPPY_V25tthtautau_ZZTo4L_13TeV_powheg_Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6-v1/170207_125252"),
        ("selection", "*"),
        ("blacklist", [169, 298, 436, 454, 551, 653]),
      ]),
    ]
  ),
])
samples_2016["/ttWW_lo/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "TTWW"),
  ("process_name_specific",           "TTWW"),
  ("nof_files",                       10),
  ("nof_events",                      9994),
  ("use_HIP_mitigation_bTag",         False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                          True),
  ("xsection",                        0.002302),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("reHLT",                           True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_ttWW/MC/TTWW_gpetrucc/VHBB_HEPPY_V25tthtautau_ttWW_TTWW_gpetrucc/170504_085619"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/MuonEG/Run2016F-23Sep2016-v1/MINIAOD"] = OD([
  ("type",                            "data"),
  ("sample_category",                 "data_obs"),
  ("process_name_specific",           "MuonEG_Run2016F_v1"),
  ("nof_files",                       641),
  ("nof_events",                      16002165),
  ("use_HIP_mitigation_bTag",         True),
  ("use_HIP_mitigation_mediumMuonId", True),
  ("use_it",                          True),
  ("triggers",                        ['1e1mu', '2e1mu', '1e2mu']),
  ("reHLT",                           True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v2/MuonEG/VHBB_HEPPY_V25tthtautau_v2_MuonEG__Run2016F-23Sep2016-v1/170218_182854"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/Tau/Run2016D-23Sep2016-v1/MINIAOD"] = OD([
  ("type",                            "data"),
  ("sample_category",                 "data_obs"),
  ("process_name_specific",           "Tau_Run2016D_v1"),
  ("nof_files",                       4328),
  ("nof_events",                      56827771),
  ("use_HIP_mitigation_bTag",         True),
  ("use_HIP_mitigation_mediumMuonId", True),
  ("use_it",                          True),
  ("triggers",                        ['1e1tau', '1mu1tau', '2tau']),
  ("reHLT",                           True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_HLT/Tau/VHBB_HEPPY_V25tthtautau_HLT_Tau__Run2016D-23Sep2016-v1/170216_182421"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/WWTo2L2Nu_DoubleScattering_13TeV-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "Rares"),
  ("process_name_specific",           "WWTo2L2Nu_DoubleScattering"),
  ("nof_files",                       101),
  ("nof_events",                      999361),
  ("use_HIP_mitigation_bTag",         False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                          True),
  ("xsection",                        0.1729),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("reHLT",                           True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/veelken/VHBBHeppyV25tthtautau/MC/WWTo2L2Nu_DoubleScattering_13TeV-pythia8/VHBB_HEPPY_V25tthtautau_WWTo2L2Nu_DoubleScattering_13TeV-Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6-v1/170207_134843"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/Tau/Run2016H-PromptReco-v3/MINIAOD"] = OD([
  ("type",                            "data"),
  ("sample_category",                 "data_obs"),
  ("process_name_specific",           "Tau_Run2016H_v3_promptReco"),
  ("nof_files",                       197),
  ("nof_events",                      1898072),
  ("use_HIP_mitigation_bTag",         False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                          True),
  ("triggers",                        ['1e1tau', '1mu1tau', '2tau']),
  ("reHLT",                           True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau/Tau/VHBB_HEPPY_V25tthtautau_Tau__Run2016H-PromptReco-v3/170215_145334"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/Tau/Run2016H-PromptReco-v2/MINIAOD"] = OD([
  ("type",                            "data"),
  ("sample_category",                 "data_obs"),
  ("process_name_specific",           "Tau_Run2016H_v2_promptReco"),
  ("nof_files",                       6052),
  ("nof_events",                      76504267),
  ("use_HIP_mitigation_bTag",         False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                          True),
  ("triggers",                        ['1e1tau', '1mu1tau', '2tau']),
  ("reHLT",                           True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v3/Tau/VHBB_HEPPY_V25tthtautau_v3_Tau__Run2016H-PromptReco-v2/170221_162533"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/SingleMuon/Run2016B-23Sep2016-v3/MINIAOD"] = OD([
  ("type",                            "data"),
  ("sample_category",                 "data_obs"),
  ("process_name_specific",           "SingleMuon_Run2016B_v3"),
  ("nof_files",                       5897),
  ("nof_events",                      158145722),
  ("use_HIP_mitigation_bTag",         True),
  ("use_HIP_mitigation_mediumMuonId", True),
  ("use_it",                          True),
  ("triggers",                        ['1mu']),
  ("reHLT",                           True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v3/SingleMuon/VHBB_HEPPY_V25tthtautau_v3_SingleMuon__Run2016B-23Sep2016-v3/170220_170831"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/SingleElectron/Run2016F-23Sep2016-v1/MINIAOD"] = OD([
  ("type",                            "data"),
  ("sample_category",                 "data_obs"),
  ("process_name_specific",           "SingleElectron_Run2016F_v1"),
  ("nof_files",                       649),
  ("nof_events",                      70593532),
  ("use_HIP_mitigation_bTag",         True),
  ("use_HIP_mitigation_mediumMuonId", True),
  ("use_it",                          True),
  ("triggers",                        ['1e']),
  ("reHLT",                           True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v2/SingleElectron/VHBB_HEPPY_V25tthtautau_v2_SingleElectron__Run2016F-23Sep2016-v1/170218_172629"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/DoubleMuon/Run2016F-23Sep2016-v1/MINIAOD"] = OD([
  ("type",                            "data"),
  ("sample_category",                 "data_obs"),
  ("process_name_specific",           "DoubleMuon_Run2016F_v1"),
  ("nof_files",                       641),
  ("nof_events",                      20329921),
  ("use_HIP_mitigation_bTag",         True),
  ("use_HIP_mitigation_mediumMuonId", True),
  ("use_it",                          True),
  ("triggers",                        ['2mu', '3mu']),
  ("reHLT",                           True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v2/DoubleMuon/VHBB_HEPPY_V25tthtautau_v2_DoubleMuon__Run2016F-23Sep2016-v1/170217_152817"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/Tau/Run2016G-23Sep2016-v1/MINIAOD"] = OD([
  ("type",                            "data"),
  ("sample_category",                 "data_obs"),
  ("process_name_specific",           "Tau_Run2016G_v1"),
  ("nof_files",                       1552),
  ("nof_events",                      79578661),
  ("use_HIP_mitigation_bTag",         False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                          True),
  ("triggers",                        ['1e1tau', '1mu1tau', '2tau']),
  ("reHLT",                           True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v2/Tau/VHBB_HEPPY_V25tthtautau_v2_Tau__Run2016G-23Sep2016-v1/170218_173036"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/DoubleEG/Run2016C-23Sep2016-v1/MINIAOD"] = OD([
  ("type",                            "data"),
  ("sample_category",                 "data_obs"),
  ("process_name_specific",           "DoubleEG_Run2016C_v1"),
  ("nof_files",                       626),
  ("nof_events",                      47677856),
  ("use_HIP_mitigation_bTag",         True),
  ("use_HIP_mitigation_mediumMuonId", True),
  ("use_it",                          True),
  ("triggers",                        ['2e', '3e']),
  ("reHLT",                           True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v2/DoubleEG/VHBB_HEPPY_V25tthtautau_v2_DoubleEG__Run2016C-23Sep2016-v1/170219_194332"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-pythia8/matze-faster_v9_ttZ_maod_54aa74f75231422e9f4d3766cb92a64a-v1/USER"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "TTZ"),
  ("process_name_specific",           "TTZToLLNuNu_fastsim"),
  ("nof_files",                       1945),
  ("nof_events",                      8826709),
  ("use_HIP_mitigation_bTag",         False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                          False),
  ("xsection",                        0.2529),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("reHLT",                           True),
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
samples_2016["/THQ_Hincl_13TeV-madgraph-pythia8_TuneCUETP8M1/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "tH"),
  ("process_name_specific",           "THQ"),
  ("nof_files",                       175),
  ("nof_events",                      3476259),
  ("use_HIP_mitigation_bTag",         False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                          True),
  ("xsection",                        0.032597),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("reHLT",                           True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_tHq_tHW/MC/THQ_Hincl_13TeV-madgraph-pythia8_TuneCUETP8M1/VHBB_HEPPY_V25tthtautau_tHq_tHW_THQ_Hincl_13TeV-madgraph-Py8_TuneCUETP8M1__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6-v1/170502_162701"),
        ("selection", "*"),
        ("blacklist", [75]),
      ]),
    ]
  ),
])
samples_2016["/DoubleEG/Run2016F-23Sep2016-v1/MINIAOD"] = OD([
  ("type",                            "data"),
  ("sample_category",                 "data_obs"),
  ("process_name_specific",           "DoubleEG_Run2016F_v1"),
  ("nof_files",                       649),
  ("nof_events",                      34577629),
  ("use_HIP_mitigation_bTag",         True),
  ("use_HIP_mitigation_mediumMuonId", True),
  ("use_it",                          True),
  ("triggers",                        ['2e', '3e']),
  ("reHLT",                           True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v2/DoubleEG/VHBB_HEPPY_V25tthtautau_v2_DoubleEG__Run2016F-23Sep2016-v1/170218_180254"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/Tau/Run2016B-23Sep2016-v3/MINIAOD"] = OD([
  ("type",                            "data"),
  ("sample_category",                 "data_obs"),
  ("process_name_specific",           "Tau_Run2016B_v3"),
  ("nof_files",                       8521),
  ("nof_events",                      68727458),
  ("use_HIP_mitigation_bTag",         True),
  ("use_HIP_mitigation_mediumMuonId", True),
  ("use_it",                          True),
  ("triggers",                        ['1e1tau', '1mu1tau', '2tau']),
  ("reHLT",                           True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_HLT/Tau/VHBB_HEPPY_V25tthtautau_HLT_Tau__Run2016B-23Sep2016-v3/170216_184427"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/ttHJetTobb_M125_13TeV_amcatnloFXFX_madspin_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext3-v1/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "ttH_hbb"),
  ("process_name_specific",           "ttHJetTobb_M125"),
  ("nof_files",                       988),
  ("nof_events",                      2910427),
  ("use_HIP_mitigation_bTag",         False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                          True),
  ("xsection",                        0.2934),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("reHLT",                           True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v2/MC/ttHJetTobb_M125_13TeV_amcatnloFXFX_madspin_pythia8/VHBB_HEPPY_V25tthtautau_v2_ttHJetTobb_M125_13TeV_amcatnloFXFX_madspin_Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6_ext3-v1/170217_224718"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/MuonEG/Run2016H-PromptReco-v2/MINIAOD"] = OD([
  ("type",                            "data"),
  ("sample_category",                 "data_obs"),
  ("process_name_specific",           "MuonEG_Run2016H_v2_promptReco"),
  ("nof_files",                       5726),
  ("nof_events",                      28705853),
  ("use_HIP_mitigation_bTag",         False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                          True),
  ("triggers",                        ['1e1mu', '2e1mu', '1e2mu']),
  ("reHLT",                           True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v3/MuonEG/VHBB_HEPPY_V25tthtautau_v3_MuonEG__Run2016H-PromptReco-v2/170221_150405"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/MuonEG/Run2016B-23Sep2016-v3/MINIAOD"] = OD([
  ("type",                            "data"),
  ("sample_category",                 "data_obs"),
  ("process_name_specific",           "MuonEG_Run2016B_v3"),
  ("nof_files",                       1966),
  ("nof_events",                      32727796),
  ("use_HIP_mitigation_bTag",         True),
  ("use_HIP_mitigation_mediumMuonId", True),
  ("use_it",                          True),
  ("triggers",                        ['1e1mu', '2e1mu', '1e2mu']),
  ("reHLT",                           True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v2/MuonEG/VHBB_HEPPY_V25tthtautau_v2_MuonEG__Run2016B-23Sep2016-v3/170218_175920"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/SingleElectron/Run2016C-23Sep2016-v1/MINIAOD"] = OD([
  ("type",                            "data"),
  ("sample_category",                 "data_obs"),
  ("process_name_specific",           "SingleElectron_Run2016C_v1"),
  ("nof_files",                       1878),
  ("nof_events",                      97259854),
  ("use_HIP_mitigation_bTag",         True),
  ("use_HIP_mitigation_mediumMuonId", True),
  ("use_it",                          True),
  ("triggers",                        ['1e']),
  ("reHLT",                           True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v3/SingleElectron/VHBB_HEPPY_V25tthtautau_v3_SingleElectron__Run2016C-23Sep2016-v1/170220_170950"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016["/SingleElectron/Run2016G-23Sep2016-v1/MINIAOD"] = OD([
  ("type",                            "data"),
  ("sample_category",                 "data_obs"),
  ("process_name_specific",           "SingleElectron_Run2016G_v1"),
  ("nof_files",                       1544),
  ("nof_events",                      153363109),
  ("use_HIP_mitigation_bTag",         False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                          True),
  ("triggers",                        ['1e']),
  ("reHLT",                           True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v2/SingleElectron/VHBB_HEPPY_V25tthtautau_v2_SingleElectron__Run2016G-23Sep2016-v1/170217_150830"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
