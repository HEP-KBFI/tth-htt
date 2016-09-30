from collections import OrderedDict as OD

samples_2016 = OD()

samples_2016["ttHToNonbb_M125_13TeV_powheg_pythia8"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "signal"),
  ("process_name_specific", "ttHToNonbb_M125"),
  ("nof_files",             43),
  ("nof_events",            3187030),
  ("use_it",                True),
  ("xsection",              0.2151), # (1 - BR(ttH -> bb)) * sigma(ttH) = (1 - 0.577) * 0.5085 pb according to https://twiki.cern.ch/twiki/bin/view/LHCPhysics/CrossSections#Higgs_cross_sections_and_decay_b
  ("triggers",              [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/lucia/VHBBHeppyV24bis/ttHToNonbb_M125_13TeV_powheg_pythia8/VHBB_HEPPY_V24bis_ttHToNonbb_M125_13TeV_powheg_Py8__spr16MAv2-puspr16_HLT_80r2as_v14-v1/160911_224147"),
        ("selection", "*"),
        ("blacklist", [5, 13, 16, 18, 24, 28, 35]),
      ]),
    ]
  ),
])
