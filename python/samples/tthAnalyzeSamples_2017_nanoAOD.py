from collections import OrderedDict as OD

# file generated at 2018-04-04 10:09:51 with the following command:
# create_dictionary.py -v -m python/samples/metaDict_2017.py -p python/samples/sampleLocations_2017.txt -Z zeroes.txt -z zombies.txt -N samples_2017 -E 2017 -o python/samples -g tthAnalyzeSamples_2017_nanoAOD.py

samples_2017 = OD()
samples_2017["/ttHJetToNonbb_M125_TuneCP5_13TeV_amcatnloFXFX_madspin_pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "signal"),
  ("process_name_specific",           "ttHJetToNonbb_M125_amcatnlo"),
  ("nof_files",                       195),
  ("nof_db_files",                    283),
  ("nof_events",                      0),
  ("nof_tree_events",                 9551123),
  ("nof_db_events",                   9650032),
  ("fsize_local",                     25360848528), # 25.36GB, avg file size 130.06MB
  ("fsize_db",                        603282930374), # 603.28GB, avg file size 2.13GB
  ("use_HIP_mitigation_bTag",         False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                          True),
  ("xsection",                        0.2118),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("reHLT",                           True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/kaehatah/NanoAOD_2017_v2/ttHJetToNonbb_M125_TuneCP5_13TeV_amcatnloFXFX_madspin_pythia8/NanoAOD_v2_ttHJetToNonbb_M125_TuneCP5_13TeV_amcatnloFXFX_madspin_pythia8__RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/180331_002330"),
        ("selection", "*"),
        ("blacklist", [111, 162]),
      ]),
    ]
  ),
])

samples_2017["/TTZToLLNuNu_M-10_TuneCP5_13TeV-amcatnlo-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "TTZ"),
  ("process_name_specific",           "TTZToLL_M10"),
  ("nof_files",                       153),
  ("nof_db_files",                    199),
  ("nof_events",                      0),
  ("nof_tree_events",                 7563490),
  ("nof_db_events",                   7563490),
  ("fsize_local",                     22717034288), # 22.72GB, avg file size 148.48MB
  ("fsize_db",                        444833969271), # 444.83GB, avg file size 2.24GB
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
        ("path",      "/hdfs/cms/store/user/kaehatah/NanoAOD_2017_v2/TTZToLLNuNu_M-10_TuneCP5_13TeV-amcatnlo-pythia8/NanoAOD_v1_TTZToLLNuNu_M-10_TuneCP5_13TeV-amcatnlo-pythia8__RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/180304_133414"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])

samples_2017["/TTWJetsToLNu_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v2/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "TTW"),
  ("process_name_specific",           "TTWJetsToLNu"),
  ("nof_files",                       100),
  ("nof_db_files",                    109),
  ("nof_events",                      0),
  ("nof_tree_events",                 4925829),
  ("nof_db_events",                   4925829),
  ("fsize_local",                     15159970782), # 15.16GB, avg file size 151.60MB
  ("fsize_db",                        292280765632), # 292.28GB, avg file size 2.68GB
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
        ("path",      "/hdfs/cms/store/user/kaehatah/NanoAOD_2017_v2/TTWJetsToLNu_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8/NanoAOD_v1_TTWJetsToLNu_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8__RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v2/180302_125338"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])

