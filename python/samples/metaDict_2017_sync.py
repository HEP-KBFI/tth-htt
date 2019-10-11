from collections import OrderedDict as OD

# file generated at 2019-10-09 01:26:28 with the following command:
# find_samples.py -V -i ../NanoAOD/test/datasets/txt/datasets_sync_2017_RunIIFall17MiniAODv2.txt -m python/samples/metaDict_2017_sync.py

meta_dictionary = OD()


### event sums

sum_events = { 
}


meta_dictionary["/ttHJetToNonbb_M125_TuneCP5_13TeV_amcatnloFXFX_madspin_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "ttH"),
  ("process_name_specific", "ttHJetToNonbb_M125_amcatnlo"),
  ("nof_db_events",         9779592),
  ("nof_db_files",          208),
  ("fsize_db",              625507074411),
  ("xsection",              0.2118),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 625.51GB; nevents: 9.78M; release: 9_4_7; last modified: 2018-06-16 07:53:14"),
])


# event statistics by sample category:
# ttH: 9.78M

