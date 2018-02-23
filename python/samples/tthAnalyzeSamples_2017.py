from collections import OrderedDict as OD

# file generated with the following command:
# /home/karl/CMSSW_9_4_4/bin/slc6_amd64_gcc630/create_dictionary.py -v -m python/samples/metaDict_2017.py -p /hdfs/local/karl/ttHNtupleProduction/2017/2018Feb20_1to1_wNanoPrep_woPresel_all/ntuples -Z zeroes.txt -z zombies.txt -N samples_2017 -E 2017

samples_2017 = OD()
samples_2017["/ttHJetToNonbb_M125_TuneCP5_13TeV_amcatnloFXFX_madspin_pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "signal"),
  ("process_name_specific",           "ttHJetToNonbb_M125_amcatnlo"),
  ("nof_files",                       168),
  ("nof_events",                      4387640),
  ("nof_tree_events",                 7714849),
  ("nof_db_events",                   7714849),
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
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018Feb20_1to1_wNanoPrep_woPresel_all/ntuples/ttHJetToNonbb_M125_amcatnlo"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])

