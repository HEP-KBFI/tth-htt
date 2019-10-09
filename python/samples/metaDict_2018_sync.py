from collections import OrderedDict as OD

# file generated at 2019-10-09 01:26:34 with the following command:
# find_samples.py -V -i ../NanoAOD/test/datasets/txt/datasets_sync_2018_RunIIAutumn18MiniAOD.txt -m python/samples/metaDict_2018_sync.py

meta_dictionary = OD()


### event sums

sum_events = { 
}


meta_dictionary["/ttHToNonbb_M125_TuneCP5_13TeV-powheg-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v2/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "ttH"),
  ("process_name_specific", "ttHToNonbb_M125_powheg"),
  ("nof_db_events",         7525991),
  ("nof_db_files",          224),
  ("fsize_db",              469867184231),
  ("xsection",              0.2118),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 469.87GB; nevents: 7.53M; release: 10_2_5; last modified: 2018-12-25 21:13:06"),
])


# event statistics by sample category:
# ttH: 7.53M

