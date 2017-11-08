from collections import OrderedDict as OD

samples_2016 = OD()

# generated from file:
# /hdfs/local/karl/store/mc/RunIISummer17MiniAOD/TT_TuneCUETP8M2T4_13TeV-powheg-pythia8/MINIAODSIM/92X_upgrade2017_realistic_v10_ext1-v1/110000/187F7EDA-0986-E711-ABB3-02163E014C21.root

samples_2016["/TT_TuneCUETP8M2T4_13TeV-powheg-pythia8/RunIISummer17MiniAOD-92X_upgrade2017_realistic_v10_ext1-v1/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "TT"),
  ("process_name_specific",           "TT"),
  ("nof_files",                       1),
  ("nof_events",                      10000),
  ("use_HIP_mitigation_bTag",         False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                          True),
  ("triggers",                        [ "1e", "1mu", "2e", "1e1mu", "2mu", "3e", "2e1mu", "1e2mu", "3mu", "1e1tau", "1mu1tau", "2tau" ]),
  ("reHLT",                           True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/nanoAOD/92X_upgrade2017_realistic_v10_ext1-v1/TT"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])

# generated from file:
# /hdfs/local/karl/store/mc/RunIISummer17MiniAOD/ttHToNonbb_M125_TuneCUETP8M2_13TeV-powheg-pythia8/MINIAODSIM/NZSFlatPU28to62_92X_upgrade2017_realistic_v10-v1/150000/563AD7C5-25AF-E711-B84F-FA163EBF5DEF.root

samples_2016["/ttHToNonbb_M125_TuneCUETP8M2_13TeV-powheg-pythia8/RunIISummer17MiniAOD-NZSFlatPU28to62_92X_upgrade2017_realistic_v10-v1/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "signal"),
  ("process_name_specific",           "ttHToNonbb_M125"),
  ("nof_files",                       1),
  ("nof_events",                      8096),
  ("use_HIP_mitigation_bTag",         False),
  ("use_HIP_mitigation_mediumMuonId", False),
  ("use_it",                          True),
  ("triggers",                        [ "1e", "1mu", "2e", "1e1mu", "2mu", "3e", "2e1mu", "1e2mu", "3mu", "1e1tau", "1mu1tau", "2tau" ]),
  ("reHLT",                           True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/nanoAOD/92X_upgrade2017_realistic_v10_ext1-v1/ttHToNonbb_M125"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
