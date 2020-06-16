from collections import OrderedDict as OD

# file generated at 2020-06-16 21:43:51 with the following command:
# find_samples.py -V -i ../NanoAOD/test/datasets/txt/datasets_mc_2016_RunIISummer16MiniAODv3_private.txt -m python/samples/metaDict_2016_private.py -c python/samples/sampleLocations_2016_nanoAOD.txt

meta_dictionary = OD()


### event sums

sum_events = { 
}


meta_dictionary["/TTWJetsToLNu_EWK_5f_NLO/RunIISummer16MiniAODv3/USER"] =  OD([
  ("crab_string",           "2016v3_2020Jun16_TTWJetsToLNu_EWK_5f_NLO__RunIISummer16MiniAODv3"),
  ("sample_category",       "TTW"),
  ("process_name_specific", "TTWJetsToLNu_EWK_5f_NLO"),
  ("nof_db_events",         12500),
  ("nof_db_files",          25),
  ("fsize_db",              1041055285),
  ("xsection",              0.0162562),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100%; status: VALID; size: 1.04GB; nevents: 12.50k; release: 9_4_0; last modified: 2020-06-16 15:05:55"),
])


# event statistics by sample category:
# TTW: 12.50k

