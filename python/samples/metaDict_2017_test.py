from collections import OrderedDict as OD

meta_dictionary = OD()

### event sums

sum_events = {
  #("", ""),
}

meta_dictionary["/ttHToNonbb_M125_TuneCUETP8M2_13TeV-powheg-pythia8/RunIISummer17MiniAOD-NZSFlatPU28to62_92X_upgrade2017_realistic_v10-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "signal"),
  ("process_name_specific", "ttHToNonbb_M125"),
  ("nof_db_events",         3999999),
  ("xsection",              0.2151),
  ("use_it",                True),
  ("genWeight",             True),
])

meta_dictionary["/TT_TuneCUETP8M2T4_13TeV-powheg-pythia8/RunIISummer17MiniAOD-92X_upgrade2017_realistic_v10_ext1-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "TT"),
  ("process_name_specific", "TT"),
  ("nof_db_events",         33844772),
  ("xsection",              182.18),
  ("use_it",                True),
  ("genWeight",             True),
])
