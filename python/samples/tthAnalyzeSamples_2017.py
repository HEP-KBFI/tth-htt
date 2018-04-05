from collections import OrderedDict as OD

# file generated at 2018-04-04 13:05:12 with the following command:
# create_dictionary.py -v -m python/samples/metaDict_2017.py -p /hdfs/local/karl/ttHNtupleProduction/2017/2018Apr04_woPresel_nom_all/ntuples -Z zeroes.txt -z zombies.txt -N samples_2017 -E 2017 -g tthAnalyzeSamples_2017.py -o python/samples -f ttHJetToNonbb_M125_amcatnlo

samples_2017 = OD()
samples_2017["/ttHJetToNonbb_M125_TuneCP5_13TeV_amcatnloFXFX_madspin_pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "signal"),
  ("process_name_specific",           "ttHJetToNonbb_M125_amcatnlo"),
  ("nof_files",                       195),
  ("nof_db_files",                    283),
  ("nof_events",                      2240805),
  ("nof_tree_events",                 9551123),
  ("nof_db_events",                   9650032),
  ("fsize_local",                     26032516446), # 26.03GB, avg file size 133.50MB
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
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018Apr04_woPresel_nom_all/ntuples/ttHJetToNonbb_M125_amcatnlo"),
        ("selection", "*"),
        ("blacklist", [111, 162]),
      ]),
    ]
  ),
])

