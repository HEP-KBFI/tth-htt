from collections import OrderedDict as OD

# file generated at 2019-03-19 02:10:52 with the following command:
# find_samples.py -V -i ../NanoAOD/test/datasets/txt/datasets_sync_2017_RunIIFall17MiniAODv2.txt -m python/samples/metaDict_2017_sync.py

meta_dictionary = OD()


### event sums

sum_events = { 
}


meta_dictionary["/ttHJetToNonbb_M125_TuneCP5_13TeV_amcatnloFXFX_madspin_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "signal"),
  ("process_name_specific", "ttHJetToNonbb_M125_amcatnlo"),
  ("nof_db_events",         9659185),
  ("nof_db_files",          204),
  ("fsize_db",              610192796578),
  ("xsection",              0.2118),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 610.19GB; nevents: 9.66M; release: 9_4_6_patch1; last modified: 2018-04-20 01:08:54"),
])


# event statistics by sample category:
# signal: 9.66M

