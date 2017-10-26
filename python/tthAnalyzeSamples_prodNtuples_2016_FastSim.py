from collections import OrderedDict as OD

# file generated with the following command:
# ./scripts/create_dictionary.py -v -m python/metaDict_2016.py -p /hdfs/local/karl/ttHNtupleProduction/2016/2017Oct17_woPreselection_forBDTtraining_only/ntuples -Z zeroes.txt -z zombies.txt -N samples_2016 -F -E 2016 -g python/tthAnalyzeSamples_prodNtuples_2016_FastSim_test.py

samples_2016 = OD()
samples_2016["/ttHToNonbb_M125_TuneCUETP8M2_ttHtranche3_13TeV-powheg-pythia8/matze-faster_v8_ttH_maod_p1_3a2fa29ab1d54ae0995b28f27b405be9-v1/USER"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "signal"),
  ("process_name_specific",           "ttHToNonbb_fastsim_p1"),
  ("nof_files",                       17),
  ("nof_events",                      16459381),
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
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2016/2017Oct17_woPreselection_forBDTtraining_only/ntuples/ttHToNonbb_fastsim_p1"),
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
  ("nof_files",                       34),
  ("nof_events",                      16459381),
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
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2016/2017Oct17_woPreselection_forBDTtraining_only/ntuples/ttHToNonbb_fastsim_p2"),
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
  ("nof_files",                       34),
  ("nof_events",                      16459381),
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
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2016/2017Oct17_woPreselection_forBDTtraining_only/ntuples/ttHToNonbb_fastsim_p3"),
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

samples_2016["/TTToSemilepton_TuneCUETP8M2_ttHtranche3_13TeV-powheg-pythia8/matze-faster_v8_ttjets_sl_maod_p1_3a2fa29ab1d54ae0995b28f27b405be9-v1/USER"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "TT"),
  ("process_name_specific",           "TTToSemilepton_fastsim_p1"),
  ("nof_files",                       85),
  ("nof_events",                      85311662),
  ("use_HIP_mitigation_bTag",         False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                          True),
  ("xsection",                        245.0),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("reHLT",                           True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2016/2017Oct17_woPreselection_forBDTtraining_only/ntuples/TTToSemilepton_fastsim_p1"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])

samples_2016["/TTToSemilepton_TuneCUETP8M2_ttHtranche3_13TeV-powheg-pythia8/matze-faster_v8_ttjets_sl_maod_p2_3a2fa29ab1d54ae0995b28f27b405be9-v1/USER"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "TT"),
  ("process_name_specific",           "TTToSemilepton_fastsim_p2"),
  ("nof_files",                       171),
  ("nof_events",                      85311662),
  ("use_HIP_mitigation_bTag",         False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                          True),
  ("xsection",                        245.0),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("reHLT",                           True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2016/2017Oct17_woPreselection_forBDTtraining_only/ntuples/TTToSemilepton_fastsim_p2"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])

samples_2016["/TTToSemilepton_TuneCUETP8M2_ttHtranche3_13TeV-powheg-pythia8/matze-faster_v8_ttjets_sl_maod_p3_3a2fa29ab1d54ae0995b28f27b405be9-v1/USER"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "TT"),
  ("process_name_specific",           "TTToSemilepton_fastsim_p3"),
  ("nof_files",                       171),
  ("nof_events",                      85311662),
  ("use_HIP_mitigation_bTag",         False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                          True),
  ("xsection",                        245.0),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("reHLT",                           True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2016/2017Oct17_woPreselection_forBDTtraining_only/ntuples/TTToSemilepton_fastsim_p3"),
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
  ("nof_files",                       71),
  ("nof_events",                      7158309),
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
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2016/2017Oct17_woPreselection_forBDTtraining_only/ntuples/TTWJetsToLNu_fastsim"),
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
  ("nof_files",                       98),
  ("nof_events",                      8826709),
  ("use_HIP_mitigation_bTag",         False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                          True),
  ("xsection",                        0.2529),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("reHLT",                           True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2016/2017Oct17_woPreselection_forBDTtraining_only/ntuples/TTZToLLNuNu_fastsim"),
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
  ("nof_files",                       94),
  ("nof_events",                      18814815),
  ("use_HIP_mitigation_bTag",         False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                          True),
  ("xsection",                        4.102),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("reHLT",                           True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2016/2017Oct17_woPreselection_forBDTtraining_only/ntuples/WZTo3LNu_fastsim"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])

