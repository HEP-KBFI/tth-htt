from collections import OrderedDict as OD

# file generated at 2019-06-05 23:13:35 with the following command:
# create_dictionary.py -m python/samples/metaDict_2018_sync.py -p /hdfs/local/karl/sync_ntuples/2018/nanoAODproduction/2019Jun01 -N samples_2018 -E 2018 -o python/samples -g tthAnalyzeSamples_2018_nanoAOD_sync.py -M

samples_2018 = OD()
samples_2018["/ttHToNonbb_M125_TuneCP5_13TeV-powheg-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v2/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "signal"),
  ("process_name_specific",           "ttHToNonbb_M125_powheg"),
  ("nof_files",                       1),
  ("nof_db_files",                    224),
  ("nof_events",                      {
  }),
  ("nof_tree_events",                 63000),
  ("nof_db_events",                   7525991),
  ("fsize_local",                     182619789), # 182.62MB, avg file size 182.62MB
  ("fsize_db",                        469867184231), # 469.87GB, avg file size 2.10GB
  ("use_it",                          True),
  ("xsection",                        0.2118),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("has_LHE",                         True),
  ("LHE_set",                         "LHA IDs 91400 - 91432 -> PDF4LHC15_nnlo_30_pdfas PDF set, expecting 33 weights (counted 33 weights)"),
  ("nof_reweighting",                 0),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/sync_ntuples/2018/nanoAODproduction/2019Jun01/ttHToNonbb_M125_powheg"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
  ("missing_from_superset",           [
    # not computed
  ]),
  ("missing_hlt_paths",               [
    "HLT_DoubleMediumChargedIsoPFTau40_Trk1_TightID_eta2p1_Reg",
    "HLT_DoubleTightChargedIsoPFTau35_Trk1_TightID_eta2p1_Reg",
    "HLT_DoubleTightChargedIsoPFTau40_Trk1_eta2p1_Reg",
    "HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTau30_eta2p1_CrossL1",
    "HLT_IsoMu20_eta2p1_LooseChargedIsoPFTau27_eta2p1_CrossL1",
  ]),
  ("hlt_paths",               [
    # not computed
  ]),
])

samples_2018["sum_events"] = [
]

