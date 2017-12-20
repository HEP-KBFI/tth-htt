from collections import OrderedDict as OD

meta_dictionary = OD()

### event sums

sum_events = {
  ("DYJetsToLL_M-50_v1", "DYJetsToLL_M-50_v2"),
}

### DATA

meta_dictionary["/SingleMuon/Run2017B-17Nov2017-v1/MINIAOD"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "SingleMuon_Run2017B_17Nov2017_v1"),
  ("nof_db_events",         136300266),
  ("xsection",              None),
  ("use_it",                True),
  ("genWeight",             False),
])

meta_dictionary["/SingleMuon/Run2017C-17Nov2017-v1/MINIAOD"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "SingleMuon_Run2017C_17Nov2017_v1"),
  ("nof_db_events",         165652756),
  ("xsection",              None),
  ("use_it",                True),
  ("genWeight",             False),
])

meta_dictionary["/DoubleEG/Run2017B-17Nov2017-v1/MINIAOD"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "DoubleEG_Run2017B_17Nov2017_v1"),
  ("nof_db_events",         58088760),
  ("xsection",              None),
  ("use_it",                True),
  ("genWeight",             False),
])

meta_dictionary["/DoubleEG/Run2017D-17Nov2017-v1/MINIAOD"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "DoubleEG_Run2017D_17Nov2017_v1"),
  ("nof_db_events",         25911432),
  ("xsection",              None),
  ("use_it",                True),
  ("genWeight",             False),
])

meta_dictionary["/DoubleEG/Run2017E-17Nov2017-v1/MINIAOD"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "DoubleEG_Run2017E_17Nov2017_v1"),
  ("nof_db_events",         56235775),
  ("xsection",              None),
  ("use_it",                True),
  ("genWeight",             False),
])

meta_dictionary["/DoubleMuon/Run2017B-17Nov2017-v1/MINIAOD"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "DoubleMuon_Run2017B_17Nov2017_v1"),
  ("nof_db_events",         14501767),
  ("xsection",              None),
  ("use_it",                True),
  ("genWeight",             False),
])

meta_dictionary["/DoubleMuon/Run2017C-17Nov2017-v1/MINIAOD"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "DoubleMuon_Run2017C_17Nov2017_v1"),
  ("nof_db_events",         49636525),
  ("xsection",              None),
  ("use_it",                True),
  ("genWeight",             False),
])

meta_dictionary["/DoubleMuon/Run2017D-17Nov2017-v1/MINIAOD"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "DoubleMuon_Run2017D_17Nov2017_v1"),
  ("nof_db_events",         23075733),
  ("xsection",              None),
  ("use_it",                True),
  ("genWeight",             False),
])

meta_dictionary["/DoubleMuon/Run2017E-17Nov2017-v1/MINIAOD"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "DoubleMuon_Run2017E_17Nov2017_v1"),
  ("nof_db_events",         51589091),
  ("xsection",              None),
  ("use_it",                True),
  ("genWeight",             False),
])

meta_dictionary["/DoubleMuon/Run2017F-17Nov2017-v1/MINIAOD"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "DoubleMuon_Run2017F_17Nov2017_v1"),
  ("nof_db_events",         79756560),
  ("xsection",              None),
  ("use_it",                True),
  ("genWeight",             False),
])

meta_dictionary["/Tau/Run2017B-17Nov2017-v1/MINIAOD"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "data_obs"),
  ("process_name_specific", "Tau_Run2017B_17Nov2017_v1"),
  ("nof_db_events",         38158216),
  ("xsection",              None),
  ("use_it",                True),
  ("genWeight",             False),
])

### MC

meta_dictionary["/DY1JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DYJetsToLL_M-50_v1"),
  ("nof_db_events",         32553254),
  ("xsection",              6025.2),
  ("use_it",                True),
  ("genWeight",             True),
])

meta_dictionary["/DY2JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DYJetsToLL_M-50_v2"),
  ("nof_db_events",         11623646),
  ("xsection",              6025.2),
  ("use_it",                True),
  ("genWeight",             True),
])

meta_dictionary["/ZZTo4L_13TeV_powheg_pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v2/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "ZZTo4L"),
  ("nof_db_events",         6960289),
  ("xsection",              1.256),
  ("use_it",                True),
  ("genWeight",             True),
])
