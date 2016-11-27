from collections import OrderedDict as OD

samples_2016_fastsim = OD()

samples_2016_fastsim["/TTTo2L2Nu_TuneCUETP8M2_ttHtranche3_13TeV-powheg-pythia8/matze-fast_ttjets_dl_MiniAOD_6b57d231e28e4ebd8065fc7621fa1f5b-v1/USER"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "TT_dilept"),
  ("process_name_specific", "TT_dilept_fastsim_validation"),
  ("nof_files",             17),
  ("nof_events",            1000000),
  ("use_it",                True),
  ("xsection",              87.300000),
  ("triggers",              [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/andres/tth/validation/fastsim/TTTo2L2Nu"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016_fastsim["/TTToSemilepton_TuneCUETP8M2_ttHtranche3_13TeV-powheg-pythia8/matze-fast_ttjets_sl_MiniAOD_6b57d231e28e4ebd8065fc7621fa1f5b-v1/USER"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "TT_semilept"),
  ("process_name_specific", "TT_semilept_fastsim_validation"),
  ("nof_files",             18),
  ("nof_events",            1000000),
  ("use_it",                True),
  ("xsection",              364.310880),
  ("triggers",              [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/andres/tth/validation/fastsim/TTToSemiLepton"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
samples_2016_fastsim["/ttHToNonbb_M125_TuneCUETP8M2_ttHtranche3_13TeV-powheg-pythia8/matze-fast_ttH_MiniAOD_6b57d231e28e4ebd8065fc7621fa1f5b-v1/USER"] = OD([
  ("type",                  "mc"),
  ("sample_category",       "signal"),
  ("process_name_specific", "ttHToNonbb_fastsim_validation"),
  ("nof_files",             21),
  ("nof_events",            994998),
  ("use_it",                True),
  ("xsection",              0.215100),
  ("triggers",              [ "1e", "2e", "1mu", "2mu", "1e1mu" ]),
  ("reHLT",                 False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/andres/tth/validation/fastsim/ttHToNonbb"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
])
