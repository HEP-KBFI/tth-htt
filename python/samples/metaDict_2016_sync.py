from collections import OrderedDict as OD

# file generated at 2019-10-09 01:26:18 with the following command:
# find_samples.py -V -i ../NanoAOD/test/datasets/txt/datasets_sync_2016_RunIISummer16MiniAODv3.txt -m python/samples/metaDict_2016_sync.py

meta_dictionary = OD()


### event sums

sum_events = { 
}


meta_dictionary["/ttHToNonbb_M125_TuneCUETP8M2_ttHtranche3_13TeV-powheg-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "ttH"),
  ("process_name_specific", "ttHToNonbb_M125_powheg"),
  ("nof_db_events",         3981250),
  ("nof_db_files",          35),
  ("fsize_db",              208884155497),
  ("xsection",              0.2118),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 208.88GB; nevents: 3.98M; release: 9_4_9; last modified: 2018-11-22 07:18:07"),
])


# event statistics by sample category:
# ttH: 3.98M

