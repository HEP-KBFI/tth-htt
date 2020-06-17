from collections import OrderedDict as OD

# file generated at 2020-06-17 00:45:25 with the following command:
# find_samples.py -V -i ../NanoAOD/test/datasets/txt/datasets_mc_2018_RunIIAutumn18MiniAOD_private.txt -m python/samples/metaDict_2018_private.py -c python/samples/sampleLocations_2018_nanoAOD.txt

meta_dictionary = OD()


### event sums

sum_events = { 
}


meta_dictionary["/TTWJetsToLNu_EWK_5f_NLO/RunIIAutumn18MiniAOD/USER"] =  OD([
  ("crab_string",           "2018_2020Jun16_TTWJetsToLNu_EWK_5f_NLO__RunIIAutumn18MiniAOD"),
  ("sample_category",       "TTW"),
  ("process_name_specific", "TTWJetsToLNu_EWK_5f_NLO"),
  ("nof_db_events",         49000),
  ("nof_db_files",          54),
  ("fsize_db",              4386666225),
  ("xsection",              0.0162562),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "0%; status: VALID; size: 4.39GB; nevents: 49.00k; release: 9_4_0; last modified: 2020-06-16 21:22:45"),
])


# event statistics by sample category:
# TTW: 49.00k

