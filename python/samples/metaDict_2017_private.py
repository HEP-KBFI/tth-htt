from collections import OrderedDict as OD

# file generated at 2020-06-16 21:44:20 with the following command:
# find_samples.py -V -i ../NanoAOD/test/datasets/txt/datasets_mc_2017_RunIIFall17MiniAODv2_private.txt -m python/samples/metaDict_2017_private.py -c python/samples/sampleLocations_2017_nanoAOD.txt

meta_dictionary = OD()


### event sums

sum_events = { 
}


meta_dictionary["/TTWJetsToLNu_EWK_5f_NLO/RunIIFall17MiniAODv2/USER"] =  OD([
  ("crab_string",           "2017v2_2020Jun16_TTWJetsToLNu_EWK_5f_NLO__RunIIFall17MiniAODv2"),
  ("sample_category",       "TTW"),
  ("process_name_specific", "TTWJetsToLNu_EWK_5f_NLO"),
  ("nof_db_events",         24503),
  ("nof_db_files",          30),
  ("fsize_db",              2203739653),
  ("xsection",              0.0162562),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100%; status: VALID; size: 2.20GB; nevents: 24.50k; release: 9_4_0; last modified: 2020-06-16 15:04:13"),
])


# event statistics by sample category:
# TTW: 24.50k

