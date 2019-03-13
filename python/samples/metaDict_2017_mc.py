from collections import OrderedDict as OD

# file generated at 2019-03-13 16:17:40 with the following command:
# find_samples.py -V -i ../NanoAOD/test/datasets/txt/datasets_mc_2017_RunIIFall17MiniAODv2.txt -m python/samples/metaDict_2017_mc.py -s ../NanoAOD/test/datasets/txt/sum_datasets_2017_RunIIFall17MiniAODv2.txt

meta_dictionary = OD()


### event sums

sum_events = { 
  ("ttHToNonbb_M125_powheg", "ttHToNonbb_M125_powheg_ext1"),
  ("TTZToLL_M10", "TTZToLL_M10_PSweights"),
  ("TTZJets_LO", "TTZJets_LO_ext1"),
  ("TTWJetsToLNu", "TTWJetsToLNu_PSweights"),
  ("TTWJets_LO", "TTWJets_LO_ext1"),
  ("ST_s-channel_4f_leptonDecays", "ST_s-channel_4f_leptonDecays_PSweights"),
  ("ST_t-channel_antitop_4f_inclusiveDecays", "ST_t-channel_antitop_4f_inclusiveDecays_PSweights"),
  ("ST_t-channel_top_4f_inclusiveDecays", "ST_t-channel_top_4f_inclusiveDecays_PSweights"),
  ("ST_tW_antitop_5f_inclusiveDecays", "ST_tW_antitop_5f_inclusiveDecays_PSweights"),
  ("ST_tW_top_5f_inclusiveDecays", "ST_tW_top_5f_inclusiveDecays_PSweights"),
  ("TTTo2L2Nu", "TTTo2L2Nu_PSweights"),
  ("TTToSemiLeptonic", "TTToSemiLeptonic_PSweights"),
  ("TTToHadronic", "TTToHadronic_PSweights"),
  ("TTGJets", "TTGJets_ext1"),
  ("GluGluHToTauTau", "GluGluHToTauTau_ext1"),
  ("TTTT", "TTTT_PSweights"),
  ("DYJetsToLL_M-10to50", "DYJetsToLL_M-10to50_ext1"),
  ("DYJetsToLL_M-4to50_HT-100to200", "DYJetsToLL_M-4to50_HT-100to200_ext1"),
  ("DYJetsToLL_M-4to50_HT-200to400", "DYJetsToLL_M-4to50_HT-200to400_ext1"),
  ("DYJetsToLL_M-4to50_HT-400to600", "DYJetsToLL_M-4to50_HT-400to600_ext1"),
  ("DYJetsToLL_M-4to50_HT-600toInf", "DYJetsToLL_M-4to50_HT-600toInf_ext1"),
  ("DYJetsToLL_M-50", "DYJetsToLL_M-50_ext1"),
  ("DYJetsToLL_M-50_amcatnloFXFX", "DYJetsToLL_M-50_amcatnloFXFX_ext1"),
  ("DY1JetsToLL_M-50_ext1", "DY1JetsToLL_M-50"),
  ("DY2JetsToLL_M-50", "DY2JetsToLL_M-50_ext1"),
  ("DY3JetsToLL_M-50", "DY3JetsToLL_M-50_ext1"),
  ("DYJetsToLL_M50_HT100to200", "DYJetsToLL_M50_HT100to200_ext1"),
  ("DYJetsToLL_M50_HT200to400", "DYJetsToLL_M50_HT200to400_ext1"),
  ("DYJetsToLL_M50_HT400to600", "DYJetsToLL_M50_HT400to600_ext1"),
  ("DYBBJetsToLL_M-50", "DYBBJetsToLL_M-50_ext1"),
  ("WJetsToLNu_madgraphMLM", "WJetsToLNu_madgraphMLM_ext1"),
  ("WWTo2L2Nu", "WWTo2L2Nu_PSweights_ext1"),
  ("WWToLNuQQ", "WWToLNuQQ_ext1", "WWToLNuQQ_PSweights_ext1"),
  ("WWTo4Q", "WWTo4Q_PSweights_ext1"),
  ("ZZTo4L", "ZZTo4L_ext1"),
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

meta_dictionary["/ttHJetTobb_M125_TuneCP5_13TeV_amcatnloFXFX_madspin_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "signal"),
  ("process_name_specific", "ttHJetTobb_M125_amcatnlo"),
  ("nof_db_events",         9911561),
  ("nof_db_files",          209),
  ("fsize_db",              632844520711),
  ("xsection",              0.2953),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 632.84GB; nevents: 9.91M; release: 9_4_6_patch1; last modified: 2018-04-20 18:50:05"),
])

meta_dictionary["/ttHToNonbb_M125_TuneCP5_13TeV-powheg-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "signal"),
  ("process_name_specific", "ttHToNonbb_M125_powheg"),
  ("nof_db_events",         7669336),
  ("nof_db_files",          157),
  ("fsize_db",              470851848333),
  ("xsection",              0.2118),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 470.85GB; nevents: 7.67M; release: 9_4_6_patch1; last modified: 2018-04-20 01:48:34"),
])

meta_dictionary["/ttHToNonbb_M125_TuneCP5_13TeV-powheg-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14_ext1-v2/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "signal"),
  ("process_name_specific", "ttHToNonbb_M125_powheg_ext1"),
  ("nof_db_events",         8241489),
  ("nof_db_files",          355),
  ("fsize_db",              515822367934),
  ("xsection",              0.2118),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 515.82GB; nevents: 8.24M; release: 9_4_6_patch1; last modified: 2019-01-18 18:55:27"),
])

meta_dictionary["/ttHTobb_M125_TuneCP5_13TeV-powheg-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "signal"),
  ("process_name_specific", "ttHTobb_M125_powheg"),
  ("nof_db_events",         8000000),
  ("nof_db_files",          171),
  ("fsize_db",              501807321040),
  ("xsection",              0.2953),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 501.81GB; nevents: 8.00M; release: 9_4_6_patch1; last modified: 2018-04-19 22:52:45"),
])

meta_dictionary["/THQ_4f_Hincl_13TeV_madgraph_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "tHq"),
  ("process_name_specific", "THQ"),
  ("nof_db_events",         3381548),
  ("nof_db_files",          49),
  ("fsize_db",              181831444350),
  ("xsection",              0.07096),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 181.83GB; nevents: 3.38M; release: 9_4_7; last modified: 2018-05-30 20:42:31"),
])

meta_dictionary["/THQ_ctcvcp_4f_Hincl_13TeV_madgraph_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "tHq"),
  ("process_name_specific", "THQ_ctcvcp"),
  ("nof_db_events",         9918994),
  ("nof_db_files",          258),
  ("fsize_db",              569542482347),
  ("xsection",              0.07096),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 569.54GB; nevents: 9.92M; release: 9_4_7; last modified: 2019-02-02 05:57:19"),
])

meta_dictionary["/THW_5f_Hincl_13TeV_madgraph_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "tHW"),
  ("process_name_specific", "THW"),
  ("nof_db_events",         1439996),
  ("nof_db_files",          37),
  ("fsize_db",              93531021287),
  ("xsection",              0.01561),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 93.53GB; nevents: 1.44M; release: 9_4_7; last modified: 2018-08-28 20:29:14"),
])

meta_dictionary["/THW_ctcvcp_5f_Hincl_13TeV_madgraph_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "tHW"),
  ("process_name_specific", "THW_ctcvcp"),
  ("nof_db_events",         4719999),
  ("nof_db_files",          172),
  ("fsize_db",              308444472684),
  ("xsection",              0.01561),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 308.44GB; nevents: 4.72M; release: 9_4_7; last modified: 2019-02-05 11:33:24"),
])

meta_dictionary["/GluGluHToZZTo4L_M125_13TeV_powheg2_JHUGenV7011_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14_ext1-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "additional_signal_overlap"),
  ("process_name_specific", "GluGluHToZZTo4L_ext1"),
  ("nof_db_events",         965198),
  ("nof_db_files",          20),
  ("fsize_db",              44829063769),
  ("xsection",              0.01297),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 44.83GB; nevents: 965.20k; release: 9_4_6_patch1; last modified: 2018-04-20 00:56:39"),
])

meta_dictionary["/TTZToLLNuNu_M-10_TuneCP5_13TeV-amcatnlo-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "TTZ"),
  ("process_name_specific", "TTZToLL_M10"),
  ("nof_db_events",         7932650),
  ("nof_db_files",          150),
  ("fsize_db",              479409585023),
  ("xsection",              0.2529),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 479.41GB; nevents: 7.93M; release: 9_4_7; last modified: 2019-03-07 12:07:09"),
])

meta_dictionary["/TTZToLLNuNu_M-10_TuneCP5_PSweights_13TeV-amcatnlo-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "TTZ"),
  ("process_name_specific", "TTZToLL_M10_PSweights"),
  ("nof_db_events",         11092000),
  ("nof_db_files",          300),
  ("fsize_db",              673564862733),
  ("xsection",              0.2529),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 673.56GB; nevents: 11.09M; release: 9_4_6_patch1; last modified: 2019-02-14 05:38:09"),
])

meta_dictionary["/TTZToLL_M-1to10_TuneCP5_13TeV-amcatnlo-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "TTZ"),
  ("process_name_specific", "TTZToLL_M-1to10"),
  ("nof_db_events",         245978),
  ("nof_db_files",          6),
  ("fsize_db",              14747523608),
  ("xsection",              0.05324),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 14.75GB; nevents: 245.98k; release: 9_4_6_patch1; last modified: 2019-01-22 23:11:36"),
])

meta_dictionary["/ttZJets_TuneCP5_13TeV_madgraphMLM_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "TTZ"),
  ("process_name_specific", "TTZJets_LO"),
  ("nof_db_events",         9698473),
  ("nof_db_files",          197),
  ("fsize_db",              591860866458),
  ("xsection",              0.8393),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 591.86GB; nevents: 9.70M; release: 9_4_7; last modified: 2018-10-05 15:55:02"),
])

meta_dictionary["/ttZJets_TuneCP5_13TeV_madgraphMLM_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14_ext1-v3/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "TTZ"),
  ("process_name_specific", "TTZJets_LO_ext1"),
  ("nof_db_events",         8536618),
  ("nof_db_files",          199),
  ("fsize_db",              522473916483),
  ("xsection",              0.8393),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 522.47GB; nevents: 8.54M; release: 9_4_6_patch1; last modified: 2018-09-05 20:51:50"),
])

meta_dictionary["/TTWJetsToLNu_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "TTW"),
  ("process_name_specific", "TTWJetsToLNu"),
  ("nof_db_events",         4994543),
  ("nof_db_files",          95),
  ("fsize_db",              304322832014),
  ("xsection",              0.2043),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 304.32GB; nevents: 4.99M; release: 9_4_7; last modified: 2019-02-20 08:25:15"),
])

meta_dictionary["/TTWJetsToLNu_TuneCP5_PSweights_13TeV-amcatnloFXFX-madspin-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "TTW"),
  ("process_name_specific", "TTWJetsToLNu_PSweights"),
  ("nof_db_events",         4919674),
  ("nof_db_files",          91),
  ("fsize_db",              295312929992),
  ("xsection",              0.2043),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 295.31GB; nevents: 4.92M; release: 9_4_6_patch1; last modified: 2018-04-20 18:46:41"),
])

meta_dictionary["/ttWJets_TuneCP5_13TeV_madgraphMLM_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "TTW"),
  ("process_name_specific", "TTWJets_LO"),
  ("nof_db_events",         6415920),
  ("nof_db_files",          132),
  ("fsize_db",              393195148836),
  ("xsection",              0.6008),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 393.20GB; nevents: 6.42M; release: 9_4_6_patch1; last modified: 2018-09-07 15:59:35"),
])

meta_dictionary["/ttWJets_TuneCP5_13TeV_madgraphMLM_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14_ext1-v2/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "TTW"),
  ("process_name_specific", "TTWJets_LO_ext1"),
  ("nof_db_events",         9425384),
  ("nof_db_files",          280),
  ("fsize_db",              577708152029),
  ("xsection",              0.6008),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 577.71GB; nevents: 9.43M; release: 9_4_6_patch1; last modified: 2018-08-02 01:24:11"),
])

meta_dictionary["/TTWW_TuneCP5_13TeV-madgraph-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14_ext1-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "TTWW"),
  ("process_name_specific", "TTWW_ext1"),
  ("nof_db_events",         200000),
  ("nof_db_files",          5),
  ("fsize_db",              13268894893),
  ("xsection",              0.006983),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 13.27GB; nevents: 200.00k; release: 9_4_6_patch1; last modified: 2018-04-20 01:51:36"),
])

meta_dictionary["/ST_s-channel_4f_leptonDecays_TuneCP5_13TeV-amcatnlo-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "TT"),
  ("process_name_specific", "ST_s-channel_4f_leptonDecays"),
  ("nof_db_events",         9883805),
  ("nof_db_files",          143),
  ("fsize_db",              456938749955),
  ("xsection",              3.36),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 456.94GB; nevents: 9.88M; release: 9_4_6_patch1; last modified: 2018-10-04 16:47:09"),
])

meta_dictionary["/ST_s-channel_4f_leptonDecays_TuneCP5_PSweights_13TeV-amcatnlo-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "TT"),
  ("process_name_specific", "ST_s-channel_4f_leptonDecays_PSweights"),
  ("nof_db_events",         9906720),
  ("nof_db_files",          146),
  ("fsize_db",              449348688254),
  ("xsection",              3.36),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 449.35GB; nevents: 9.91M; release: 9_4_6_patch1; last modified: 2018-04-22 04:40:04"),
])

meta_dictionary["/ST_t-channel_antitop_4f_inclusiveDecays_TuneCP5_13TeV-powhegV2-madspin-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "TT"),
  ("process_name_specific", "ST_t-channel_antitop_4f_inclusiveDecays"),
  ("nof_db_events",         3675910),
  ("nof_db_files",          69),
  ("fsize_db",              173657703453),
  ("xsection",              80.95),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 173.66GB; nevents: 3.68M; release: 9_4_6_patch1; last modified: 2018-10-22 06:00:47"),
])

meta_dictionary["/ST_t-channel_antitop_4f_InclusiveDecays_TuneCP5_PSweights_13TeV-powheg-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "TT"),
  ("process_name_specific", "ST_t-channel_antitop_4f_inclusiveDecays_PSweights"),
  ("nof_db_events",         64818800),
  ("nof_db_files",          1288),
  ("fsize_db",              3064755155948),
  ("xsection",              80.95),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 3.06TB; nevents: 64.82M; release: 9_4_7; last modified: 2018-09-26 11:08:14"),
])

meta_dictionary["/ST_t-channel_top_4f_inclusiveDecays_TuneCP5_13TeV-powhegV2-madspin-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "TT"),
  ("process_name_specific", "ST_t-channel_top_4f_inclusiveDecays"),
  ("nof_db_events",         5865875),
  ("nof_db_files",          111),
  ("fsize_db",              271552800774),
  ("xsection",              136.02),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 271.55GB; nevents: 5.87M; release: 9_4_6_patch1; last modified: 2018-04-21 09:45:52"),
])

meta_dictionary["/ST_t-channel_top_4f_InclusiveDecays_TuneCP5_PSweights_13TeV-powheg-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "TT"),
  ("process_name_specific", "ST_t-channel_top_4f_inclusiveDecays_PSweights"),
  ("nof_db_events",         122688200),
  ("nof_db_files",          2354),
  ("fsize_db",              5815097338121),
  ("xsection",              136.02),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 5.82TB; nevents: 122.69M; release: 9_4_7; last modified: 2018-11-11 14:11:55"),
])

meta_dictionary["/ST_tW_antitop_5f_inclusiveDecays_TuneCP5_13TeV-powheg-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "TT"),
  ("process_name_specific", "ST_tW_antitop_5f_inclusiveDecays"),
  ("nof_db_events",         7977430),
  ("nof_db_files",          134),
  ("fsize_db",              409038270439),
  ("xsection",              35.85),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 409.04GB; nevents: 7.98M; release: 9_4_7; last modified: 2018-10-06 03:17:43"),
])

meta_dictionary["/ST_tW_antitop_5f_inclusiveDecays_TuneCP5_PSweights_13TeV-powheg-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "TT"),
  ("process_name_specific", "ST_tW_antitop_5f_inclusiveDecays_PSweights"),
  ("nof_db_events",         7745276),
  ("nof_db_files",          150),
  ("fsize_db",              397785712841),
  ("xsection",              35.85),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 397.79GB; nevents: 7.75M; release: 9_4_7; last modified: 2018-09-19 03:46:20"),
])

meta_dictionary["/ST_tW_top_5f_inclusiveDecays_TuneCP5_13TeV-powheg-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "TT"),
  ("process_name_specific", "ST_tW_top_5f_inclusiveDecays"),
  ("nof_db_events",         7794186),
  ("nof_db_files",          139),
  ("fsize_db",              399638903127),
  ("xsection",              35.85),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 399.64GB; nevents: 7.79M; release: 9_4_6_patch1; last modified: 2018-09-19 08:25:32"),
])

meta_dictionary["/ST_tW_top_5f_inclusiveDecays_TuneCP5_PSweights_13TeV-powheg-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "TT"),
  ("process_name_specific", "ST_tW_top_5f_inclusiveDecays_PSweights"),
  ("nof_db_events",         7660001),
  ("nof_db_files",          130),
  ("fsize_db",              386042521329),
  ("xsection",              35.85),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 386.04GB; nevents: 7.66M; release: 9_4_6_patch1; last modified: 2018-04-21 06:48:45"),
])

meta_dictionary["/ST_tWll_5f_LO_TuneCP5_PSweights_13TeV-madgraph-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14_ext1-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "TT"),
  ("process_name_specific", "ST_tWll_PSweights_ext1"),
  ("nof_db_events",         986000),
  ("nof_db_files",          42),
  ("fsize_db",              62041007346),
  ("xsection",              0.01103),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 62.04GB; nevents: 986.00k; release: 9_4_7; last modified: 2019-01-03 22:41:21"),
])

meta_dictionary["/TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "TT"),
  ("process_name_specific", "TTTo2L2Nu"),
  ("nof_db_events",         960752),
  ("nof_db_files",          18),
  ("fsize_db",              50669657999),
  ("xsection",              88.29),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 50.67GB; nevents: 960.75k; release: 9_4_6_patch1; last modified: 2019-02-02 05:52:59"),
])

meta_dictionary["/TTTo2L2Nu_TuneCP5_PSweights_13TeV-powheg-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "TT"),
  ("process_name_specific", "TTTo2L2Nu_PSweights"),
  ("nof_db_events",         66979742),
  ("nof_db_files",          1112),
  ("fsize_db",              3505481082135),
  ("xsection",              88.29),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 3.51TB; nevents: 66.98M; release: 9_4_6_patch1; last modified: 2018-04-20 12:02:36"),
])

meta_dictionary["/TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "TT"),
  ("process_name_specific", "TTToSemiLeptonic"),
  ("nof_db_events",         41221873),
  ("nof_db_files",          615),
  ("fsize_db",              2193839328615),
  ("xsection",              365.34),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 2.19TB; nevents: 41.22M; release: 9_4_7; last modified: 2018-05-18 01:50:34"),
])

meta_dictionary["/TTToSemiLeptonic_TuneCP5_PSweights_13TeV-powheg-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "TT"),
  ("process_name_specific", "TTToSemiLeptonic_PSweights"),
  ("nof_db_events",         110014744),
  ("nof_db_files",          2175),
  ("fsize_db",              6000464284883),
  ("xsection",              365.34),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 6.00TB; nevents: 110.01M; release: 9_4_6_patch1; last modified: 2018-10-26 11:16:09"),
])

meta_dictionary["/TTToHadronic_TuneCP5_13TeV-powheg-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "TT"),
  ("process_name_specific", "TTToHadronic"),
  ("nof_db_events",         42357944),
  ("nof_db_files",          712),
  ("fsize_db",              2299793008508),
  ("xsection",              377.96),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 2.30TB; nevents: 42.36M; release: 9_4_6_patch1; last modified: 2018-04-20 18:47:36"),
])

meta_dictionary["/TTToHadronic_TuneCP5_PSweights_13TeV-powheg-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "TT"),
  ("process_name_specific", "TTToHadronic_PSweights"),
  ("nof_db_events",         130725364),
  ("nof_db_files",          2045),
  ("fsize_db",              7081129653973),
  ("xsection",              377.96),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 7.08TB; nevents: 130.73M; release: 9_4_6_patch1; last modified: 2018-04-21 15:42:18"),
])

meta_dictionary["/TTJets_DiLept_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "TT"),
  ("process_name_specific", "TTJets_DiLept"),
  ("nof_db_events",         28380110),
  ("nof_db_files",          602),
  ("fsize_db",              1574497543250),
  ("xsection",              88.29),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 1.57TB; nevents: 28.38M; release: 9_4_6_patch1; last modified: 2018-09-19 21:13:11"),
])

meta_dictionary["/TTJets_SingleLeptFromT_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "TT"),
  ("process_name_specific", "TTJets_SingleLeptFromT"),
  ("nof_db_events",         61761347),
  ("nof_db_files",          1052),
  ("fsize_db",              3412059272229),
  ("xsection",              182.67),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 3.41TB; nevents: 61.76M; release: 9_4_6_patch1; last modified: 2018-04-27 06:06:08"),
])

meta_dictionary["/TTJets_SingleLeptFromTbar_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "TT"),
  ("process_name_specific", "TTJets_SingleLeptFromTbar"),
  ("nof_db_events",         56705550),
  ("nof_db_files",          1306),
  ("fsize_db",              3215810423559),
  ("xsection",              182.67),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 3.22TB; nevents: 56.71M; release: 9_4_6_patch1; last modified: 2018-10-07 05:50:45"),
])

meta_dictionary["/TTJets_TuneCP5_13TeV-amcatnloFXFX-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "TT"),
  ("process_name_specific", "TTJets_amcatnloFXFX"),
  ("nof_db_events",         153531390),
  ("nof_db_files",          2304),
  ("fsize_db",              8431652119393),
  ("xsection",              831.76),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 8.43TB; nevents: 153.53M; release: 9_4_6_patch1; last modified: 2018-04-20 01:23:03"),
])

meta_dictionary["/TTJets_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "TT"),
  ("process_name_specific", "TTJets_madgraphMLM"),
  ("nof_db_events",         8026103),
  ("nof_db_files",          260),
  ("fsize_db",              448684514040),
  ("xsection",              831.76),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 448.68GB; nevents: 8.03M; release: 9_4_6_patch1; last modified: 2018-11-21 21:35:02"),
])

meta_dictionary["/WWW_4F_TuneCP5_13TeV-amcatnlo-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "Rares"),
  ("process_name_specific", "WWW"),
  ("nof_db_events",         232300),
  ("nof_db_files",          21),
  ("fsize_db",              11979015983),
  ("xsection",              0.2086),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 11.98GB; nevents: 232.30k; release: 9_4_7; last modified: 2018-10-17 15:35:08"),
])

meta_dictionary["/WWZ_4F_TuneCP5_13TeV-amcatnlo-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "Rares"),
  ("process_name_specific", "WWZ"),
  ("nof_db_events",         250000),
  ("nof_db_files",          24),
  ("fsize_db",              13265189749),
  ("xsection",              0.1651),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 13.27GB; nevents: 250.00k; release: 9_4_7; last modified: 2018-10-20 23:53:06"),
])

meta_dictionary["/WZZ_TuneCP5_13TeV-amcatnlo-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "Rares"),
  ("process_name_specific", "WZZ"),
  ("nof_db_events",         250000),
  ("nof_db_files",          5),
  ("fsize_db",              12371966638),
  ("xsection",              0.05565),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 12.37GB; nevents: 250.00k; release: 9_4_6_patch1; last modified: 2018-04-20 00:28:06"),
])

meta_dictionary["/ZZZ_TuneCP5_13TeV-amcatnlo-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "Rares"),
  ("process_name_specific", "ZZZ"),
  ("nof_db_events",         250000),
  ("nof_db_files",          22),
  ("fsize_db",              12871064949),
  ("xsection",              0.01398),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 12.87GB; nevents: 250.00k; release: 9_4_7; last modified: 2018-10-24 18:17:57"),
])

meta_dictionary["/WZG_TuneCP5_13TeV-amcatnlo-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "Rares"),
  ("process_name_specific", "WZG"),
  ("nof_db_events",         1000000),
  ("nof_db_files",          20),
  ("fsize_db",              50788326431),
  ("xsection",              0.04123),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 50.79GB; nevents: 1.00M; release: 9_4_6_patch1; last modified: 2018-04-20 00:23:21"),
])

meta_dictionary["/WGToLNuG_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "Rares"),
  ("process_name_specific", "WGToLNuG"),
  ("nof_db_events",         6283083),
  ("nof_db_files",          134),
  ("fsize_db",              259323657535),
  ("xsection",              405.271),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 259.32GB; nevents: 6.28M; release: 9_4_7; last modified: 2018-10-21 07:04:53"),
])

meta_dictionary["/ZGToLLG_01J_5f_TuneCP5_13TeV-amcatnloFXFX-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v3/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "Rares"),
  ("process_name_specific", "ZGTo2LG"),
  ("nof_db_events",         30490034),
  ("nof_db_files",          526),
  ("fsize_db",              1312540069447),
  ("xsection",              117.864),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 1.31TB; nevents: 30.49M; release: 9_4_7; last modified: 2019-03-10 11:48:36"),
])

meta_dictionary["/TGJets_TuneCP5_13TeV_amcatnlo_madspin_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "Rares"),
  ("process_name_specific", "TGJets"),
  ("nof_db_events",         1909000),
  ("nof_db_files",          60),
  ("fsize_db",              96871538662),
  ("xsection",              2.967),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 96.87GB; nevents: 1.91M; release: 9_4_6_patch1; last modified: 2018-06-20 03:31:34"),
])

meta_dictionary["/TTGJets_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "Rares"),
  ("process_name_specific", "TTGJets"),
  ("nof_db_events",         4858971),
  ("nof_db_files",          78),
  ("fsize_db",              289825882220),
  ("xsection",              3.697),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 289.83GB; nevents: 4.86M; release: 9_4_7; last modified: 2019-01-23 02:12:01"),
])

meta_dictionary["/TTGJets_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14_ext1-v2/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "Rares"),
  ("process_name_specific", "TTGJets_ext1"),
  ("nof_db_events",         8729288),
  ("nof_db_files",          239),
  ("fsize_db",              525415577270),
  ("xsection",              3.697),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 525.42GB; nevents: 8.73M; release: 9_4_7; last modified: 2018-11-11 13:44:37"),
])

meta_dictionary["/GluGluHToTauTau_M125_13TeV_powheg_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "Rares"),
  ("process_name_specific", "GluGluHToTauTau"),
  ("nof_db_events",         2892030),
  ("nof_db_files",          38),
  ("fsize_db",              117011687965),
  ("xsection",              3.0469),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 117.01GB; nevents: 2.89M; release: 9_4_6_patch1; last modified: 2018-04-19 22:34:43"),
])

meta_dictionary["/GluGluHToTauTau_M125_13TeV_powheg_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14_ext1-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "Rares"),
  ("process_name_specific", "GluGluHToTauTau_ext1"),
  ("nof_db_events",         9259000),
  ("nof_db_files",          169),
  ("fsize_db",              387946138466),
  ("xsection",              3.0469),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 387.95GB; nevents: 9.26M; release: 9_4_7; last modified: 2018-10-19 11:01:45"),
])

meta_dictionary["/VBFHToTauTau_M125_13TeV_powheg_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "Rares"),
  ("process_name_specific", "VBFHToTauTau"),
  ("nof_db_events",         2975404),
  ("nof_db_files",          43),
  ("fsize_db",              131499935937),
  ("xsection",              0.2372),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 131.50GB; nevents: 2.98M; release: 9_4_6_patch1; last modified: 2018-04-20 10:31:11"),
])

meta_dictionary["/tZq_ll_4f_ckm_NLO_TuneCP5_PSweights_13TeV-amcatnlo-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "Rares"),
  ("process_name_specific", "tZq_ll_4f_PSweights"),
  ("nof_db_events",         13308207),
  ("nof_db_files",          230),
  ("fsize_db",              734846668347),
  ("xsection",              0.0758),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 734.85GB; nevents: 13.31M; release: 9_4_6_patch1; last modified: 2018-04-20 18:54:49"),
])

meta_dictionary["/WpWpJJ_EWK-QCD_TuneCP5_13TeV-madgraph-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "Rares"),
  ("process_name_specific", "WpWpJJ_EWK_QCD"),
  ("nof_db_events",         149000),
  ("nof_db_files",          21),
  ("fsize_db",              8401827223),
  ("xsection",              0.04932),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 8.40GB; nevents: 149.00k; release: 9_4_6_patch1; last modified: 2018-06-18 11:32:50"),
])

meta_dictionary["/WWTo2L2Nu_DoubleScattering_13TeV-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "Rares"),
  ("process_name_specific", "WWTo2L2Nu_DoubleScattering"),
  ("nof_db_events",         968000),
  ("nof_db_files",          31),
  ("fsize_db",              37369750968),
  ("xsection",              0.1743),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 37.37GB; nevents: 968.00k; release: 9_4_6_patch1; last modified: 2018-09-07 15:59:55"),
])

meta_dictionary["/TTTT_TuneCP5_13TeV-amcatnlo-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "Rares"),
  ("process_name_specific", "TTTT"),
  ("nof_db_events",         1000000),
  ("nof_db_files",          23),
  ("fsize_db",              77916434192),
  ("xsection",              0.008213),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 77.92GB; nevents: 1.00M; release: 9_4_7; last modified: 2018-10-04 16:57:04"),
])

meta_dictionary["/TTTT_TuneCP5_PSweights_13TeV-amcatnlo-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "Rares"),
  ("process_name_specific", "TTTT_PSweights"),
  ("nof_db_events",         2273928),
  ("nof_db_files",          71),
  ("fsize_db",              177857452203),
  ("xsection",              0.008213),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 177.86GB; nevents: 2.27M; release: 9_4_7; last modified: 2018-07-01 06:33:44"),
])

meta_dictionary["/TTWH_TuneCP5_13TeV-madgraph-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "Rares"),
  ("process_name_specific", "TTWH"),
  ("nof_db_events",         200000),
  ("nof_db_files",          5),
  ("fsize_db",              13394175434),
  ("xsection",              0.001141),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 13.39GB; nevents: 200.00k; release: 9_4_6_patch1; last modified: 2018-04-25 19:03:40"),
])

meta_dictionary["/TTZH_TuneCP5_13TeV-madgraph-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "Rares"),
  ("process_name_specific", "TTZH"),
  ("nof_db_events",         200000),
  ("nof_db_files",          5),
  ("fsize_db",              13801667296),
  ("xsection",              0.001131),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 13.80GB; nevents: 200.00k; release: 9_4_6_patch1; last modified: 2018-04-19 22:57:09"),
])

meta_dictionary["/TTTW_TuneCP5_13TeV-madgraph-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "Rares"),
  ("process_name_specific", "TTTW"),
  ("nof_db_events",         200000),
  ("nof_db_files",          6),
  ("fsize_db",              14473792275),
  ("xsection",              0.0007317),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 14.47GB; nevents: 200.00k; release: 9_4_6_patch1; last modified: 2018-04-20 01:16:38"),
])

meta_dictionary["/TTTJ_TuneCP5_13TeV-madgraph-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "Rares"),
  ("process_name_specific", "TTTJ"),
  ("nof_db_events",         200000),
  ("nof_db_files",          5),
  ("fsize_db",              13746788371),
  ("xsection",              0.0003973),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 13.75GB; nevents: 200.00k; release: 9_4_6_patch1; last modified: 2018-04-20 01:21:50"),
])

meta_dictionary["/VHToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "VH"),
  ("process_name_specific", "VHToNonbb_M125"),
  ("nof_db_events",         918508),
  ("nof_db_files",          35),
  ("fsize_db",              44015654097),
  ("xsection",              0.9425),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 44.02GB; nevents: 918.51k; release: 9_4_6_patch1; last modified: 2018-07-07 21:48:41"),
])

meta_dictionary["/ZH_HToBB_ZToLL_M125_13TeV_powheg_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "VH"),
  ("process_name_specific", "ZH_HToBB_ZToLL"),
  ("nof_db_events",         4816186),
  ("nof_db_files",          75),
  ("fsize_db",              243231917749),
  ("xsection",              0.05198),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 243.23GB; nevents: 4.82M; release: 9_4_6_patch1; last modified: 2018-04-20 01:16:59"),
])

meta_dictionary["/ZHToTauTau_M125_13TeV_powheg_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "VH"),
  ("process_name_specific", "ZHToTauTau"),
  ("nof_db_events",         4940230),
  ("nof_db_files",          75),
  ("fsize_db",              231991011973),
  ("xsection",              0.05544),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 231.99GB; nevents: 4.94M; release: 9_4_6_patch1; last modified: 2018-04-20 00:29:21"),
])

meta_dictionary["/DYJetsToLL_M-10to50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DYJetsToLL_M-10to50"),
  ("nof_db_events",         39521230),
  ("nof_db_files",          477),
  ("fsize_db",              1379092540630),
  ("xsection",              18610.0),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 1.38TB; nevents: 39.52M; release: 9_4_7; last modified: 2018-10-06 03:25:44"),
])

meta_dictionary["/DYJetsToLL_M-10to50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14_ext1-v2/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DYJetsToLL_M-10to50_ext1"),
  ("nof_db_events",         39536839),
  ("nof_db_files",          480),
  ("fsize_db",              1424731750804),
  ("xsection",              18610.0),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 1.42TB; nevents: 39.54M; release: 9_4_7; last modified: 2019-02-06 20:17:22"),
])

meta_dictionary["/DYJetsToLL_M-4to50_HT-100to200_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DYJetsToLL_M-4to50_HT-100to200"),
  ("nof_db_events",         8857742),
  ("nof_db_files",          114),
  ("fsize_db",              385869907454),
  ("xsection",              239.63),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 385.87GB; nevents: 8.86M; release: 9_4_6_patch1; last modified: 2018-04-20 11:32:46"),
])

meta_dictionary["/DYJetsToLL_M-4to50_HT-100to200_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14_ext1-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DYJetsToLL_M-4to50_HT-100to200_ext1"),
  ("nof_db_events",         1026278),
  ("nof_db_files",          15),
  ("fsize_db",              44369238206),
  ("xsection",              239.63),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 44.37GB; nevents: 1.03M; release: 9_4_6_patch1; last modified: 2018-04-18 00:09:22"),
])

meta_dictionary["/DYJetsToLL_M-4to50_HT-200to400_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DYJetsToLL_M-4to50_HT-200to400"),
  ("nof_db_events",         1929923),
  ("nof_db_files",          45),
  ("fsize_db",              94218730985),
  ("xsection",              63.79),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 94.22GB; nevents: 1.93M; release: 9_4_6_patch1; last modified: 2018-09-08 05:00:46"),
])

meta_dictionary["/DYJetsToLL_M-4to50_HT-200to400_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14_ext1-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DYJetsToLL_M-4to50_HT-200to400_ext1"),
  ("nof_db_events",         1021757),
  ("nof_db_files",          19),
  ("fsize_db",              48889722830),
  ("xsection",              63.79),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 48.89GB; nevents: 1.02M; release: 9_4_7; last modified: 2018-05-18 04:51:48"),
])

meta_dictionary["/DYJetsToLL_M-4to50_HT-400to600_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DYJetsToLL_M-4to50_HT-400to600"),
  ("nof_db_events",         2067660),
  ("nof_db_files",          32),
  ("fsize_db",              111643815539),
  ("xsection",              6.726),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 111.64GB; nevents: 2.07M; release: 9_4_7; last modified: 2018-10-14 06:43:37"),
])

meta_dictionary["/DYJetsToLL_M-4to50_HT-400to600_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14_ext1-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DYJetsToLL_M-4to50_HT-400to600_ext1"),
  ("nof_db_events",         994584),
  ("nof_db_files",          19),
  ("fsize_db",              53407812926),
  ("xsection",              6.726),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 53.41GB; nevents: 994.58k; release: 9_4_6_patch1; last modified: 2018-04-19 18:21:21"),
])

meta_dictionary["/DYJetsToLL_M-4to50_HT-600toInf_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DYJetsToLL_M-4to50_HT-600toInf"),
  ("nof_db_events",         1988861),
  ("nof_db_files",          34),
  ("fsize_db",              116733344895),
  ("xsection",              2.172),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 116.73GB; nevents: 1.99M; release: 9_4_6_patch1; last modified: 2018-05-18 15:32:44"),
])

meta_dictionary["/DYJetsToLL_M-4to50_HT-600toInf_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14_ext1-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DYJetsToLL_M-4to50_HT-600toInf_ext1"),
  ("nof_db_events",         942875),
  ("nof_db_files",          48),
  ("fsize_db",              56015594969),
  ("xsection",              2.172),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 56.02GB; nevents: 942.88k; release: 9_4_6_patch1; last modified: 2018-09-06 04:12:00"),
])

meta_dictionary["/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017RECOSIMstep_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DYJetsToLL_M-50"),
  ("nof_db_events",         48675378),
  ("nof_db_files",          553),
  ("fsize_db",              1989278749780),
  ("xsection",              5765.4),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 1.99TB; nevents: 48.68M; release: 9_4_6_patch1; last modified: 2018-04-26 12:18:24"),
])

meta_dictionary["/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017RECOSIMstep_12Apr2018_94X_mc2017_realistic_v14_ext1-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DYJetsToLL_M-50_ext1"),
  ("nof_db_events",         49125561),
  ("nof_db_files",          591),
  ("fsize_db",              2002707381991),
  ("xsection",              5765.4),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 2.00TB; nevents: 49.13M; release: 9_4_6_patch1; last modified: 2018-04-23 22:46:40"),
])

meta_dictionary["/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DYJetsToLL_M-50_amcatnloFXFX"),
  ("nof_db_events",         27413121),
  ("nof_db_files",          305),
  ("fsize_db",              1097663136414),
  ("xsection",              5765.4),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 1.10TB; nevents: 27.41M; release: 9_4_6_patch1; last modified: 2018-04-19 18:08:15"),
])

meta_dictionary["/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14_ext1-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DYJetsToLL_M-50_amcatnloFXFX_ext1"),
  ("nof_db_events",         182359906),
  ("nof_db_files",          2126),
  ("fsize_db",              7297684290732),
  ("xsection",              5765.4),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 7.30TB; nevents: 182.36M; release: 9_4_6_patch1; last modified: 2018-04-21 17:01:16"),
])

meta_dictionary["/DY1JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14_ext1-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DY1JetsToLL_M-50_ext1"),
  ("nof_db_events",         34859434),
  ("nof_db_files",          417),
  ("fsize_db",              1462619517307),
  ("xsection",              945.24),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 1.46TB; nevents: 34.86M; release: 9_4_6_patch1; last modified: 2018-04-20 01:40:36"),
])

meta_dictionary["/DY1JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DY1JetsToLL_M-50"),
  ("nof_db_events",         42331295),
  ("nof_db_files",          492),
  ("fsize_db",              1818087283471),
  ("xsection",              945.24),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 1.82TB; nevents: 42.33M; release: 9_4_7; last modified: 2018-05-28 20:31:22"),
])

meta_dictionary["/DY2JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DY2JetsToLL_M-50"),
  ("nof_db_events",         88895),
  ("nof_db_files",          2),
  ("fsize_db",              4131753194),
  ("xsection",              330.99),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 4.13GB; nevents: 88.89k; release: 9_4_6_patch1; last modified: 2018-06-03 02:31:14"),
])

meta_dictionary["/DY2JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14_ext1-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DY2JetsToLL_M-50_ext1"),
  ("nof_db_events",         9701595),
  ("nof_db_files",          143),
  ("fsize_db",              440374419055),
  ("xsection",              330.99),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 440.37GB; nevents: 9.70M; release: 9_4_6_patch1; last modified: 2018-04-20 10:47:55"),
])

meta_dictionary["/DY3JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DY3JetsToLL_M-50"),
  ("nof_db_events",         5748466),
  ("nof_db_files",          84),
  ("fsize_db",              276614009421),
  ("xsection",              120.72),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 276.61GB; nevents: 5.75M; release: 9_4_6_patch1; last modified: 2018-08-01 04:29:16"),
])

meta_dictionary["/DY3JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14_ext1-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DY3JetsToLL_M-50_ext1"),
  ("nof_db_events",         1149467),
  ("nof_db_files",          22),
  ("fsize_db",              54184261688),
  ("xsection",              120.72),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 54.18GB; nevents: 1.15M; release: 9_4_6_patch1; last modified: 2018-04-21 04:45:06"),
])

meta_dictionary["/DY4JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_v2_94X_mc2017_realistic_v14-v2/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DY4JetsToLL_M-50"),
  ("nof_db_events",         4328648),
  ("nof_db_files",          75),
  ("fsize_db",              229309195986),
  ("xsection",              47.47),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 229.31GB; nevents: 4.33M; release: 9_4_6_patch1; last modified: 2018-10-07 10:25:43"),
])

meta_dictionary["/DYJetsToLL_M-50_HT-70to100_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DYJetsToLL_M50_HT70to100"),
  ("nof_db_events",         9344037),
  ("nof_db_files",          207),
  ("fsize_db",              429654206472),
  ("xsection",              158.49),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 429.65GB; nevents: 9.34M; release: 9_4_6_patch1; last modified: 2018-09-07 17:40:18"),
])

meta_dictionary["/DYJetsToLL_M-50_HT-100to200_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DYJetsToLL_M50_HT100to200"),
  ("nof_db_events",         10235418),
  ("nof_db_files",          153),
  ("fsize_db",              489764327787),
  ("xsection",              173.53),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 489.76GB; nevents: 10.24M; release: 9_4_6_patch1; last modified: 2018-04-20 00:33:17"),
])

meta_dictionary["/DYJetsToLL_M-50_HT-100to200_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14_ext1-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DYJetsToLL_M50_HT100to200_ext1"),
  ("nof_db_events",         3950339),
  ("nof_db_files",          61),
  ("fsize_db",              186406431655),
  ("xsection",              173.53),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 186.41GB; nevents: 3.95M; release: 9_4_6_patch1; last modified: 2018-04-20 12:32:47"),
])

meta_dictionary["/DYJetsToLL_M-50_HT-200to400_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DYJetsToLL_M50_HT200to400"),
  ("nof_db_events",         10728447),
  ("nof_db_files",          159),
  ("fsize_db",              576131281371),
  ("xsection",              53.0),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 576.13GB; nevents: 10.73M; release: 9_4_6_patch1; last modified: 2018-10-05 06:39:30"),
])

meta_dictionary["/DYJetsToLL_M-50_HT-200to400_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14_ext1-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DYJetsToLL_M50_HT200to400_ext1"),
  ("nof_db_events",         1200863),
  ("nof_db_files",          22),
  ("fsize_db",              63472314509),
  ("xsection",              53.0),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 63.47GB; nevents: 1.20M; release: 9_4_6_patch1; last modified: 2018-04-20 01:49:19"),
])

meta_dictionary["/DYJetsToLL_M-50_HT-400to600_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DYJetsToLL_M50_HT400to600"),
  ("nof_db_events",         9533635),
  ("nof_db_files",          147),
  ("fsize_db",              557123236526),
  ("xsection",              7.539),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 557.12GB; nevents: 9.53M; release: 9_4_6_patch1; last modified: 2018-04-19 18:14:19"),
])

meta_dictionary["/DYJetsToLL_M-50_HT-400to600_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14_ext1-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DYJetsToLL_M50_HT400to600_ext1"),
  ("nof_db_events",         1124294),
  ("nof_db_files",          23),
  ("fsize_db",              65482538135),
  ("xsection",              7.539),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 65.48GB; nevents: 1.12M; release: 9_4_6_patch1; last modified: 2018-04-20 00:54:12"),
])

meta_dictionary["/DYJetsToLL_M-50_HT-600to800_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DYJetsToLL_M50_HT600to800"),
  ("nof_db_events",         8153358),
  ("nof_db_files",          158),
  ("fsize_db",              492605869792),
  ("xsection",              1.8815),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 492.61GB; nevents: 8.15M; release: 9_4_6_patch1; last modified: 2018-04-19 21:24:43"),
])

meta_dictionary["/DYJetsToLL_M-50_HT-800to1200_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DYJetsToLL_M50_HT800to1200"),
  ("nof_db_events",         3089861),
  ("nof_db_files",          66),
  ("fsize_db",              192099374312),
  ("xsection",              0.8684),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 192.10GB; nevents: 3.09M; release: 9_4_6_patch1; last modified: 2018-04-20 11:40:18"),
])

meta_dictionary["/DYJetsToLL_M-50_HT-1200to2500_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DYJetsToLL_M50_HT1200to2500"),
  ("nof_db_events",         625517),
  ("nof_db_files",          15),
  ("fsize_db",              41980141603),
  ("xsection",              0.2079),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 41.98GB; nevents: 625.52k; release: 9_4_6_patch1; last modified: 2018-04-20 00:43:19"),
])

meta_dictionary["/DYJetsToLL_M-50_HT-2500toInf_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DYJetsToLL_M50_HT2500toInf"),
  ("nof_db_events",         404986),
  ("nof_db_files",          10),
  ("fsize_db",              29515940094),
  ("xsection",              0.003749),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 29.52GB; nevents: 404.99k; release: 9_4_6_patch1; last modified: 2018-04-20 01:25:42"),
])

meta_dictionary["/DYBBJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DYBBJetsToLL_M-50"),
  ("nof_db_events",         2725626),
  ("nof_db_files",          46),
  ("fsize_db",              133741432740),
  ("xsection",              14.59),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 133.74GB; nevents: 2.73M; release: 9_4_6_patch1; last modified: 2018-04-19 22:53:50"),
])

meta_dictionary["/DYBBJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14_ext1-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DYBBJetsToLL_M-50_ext1"),
  ("nof_db_events",         2375576),
  ("nof_db_files",          121),
  ("fsize_db",              118040727435),
  ("xsection",              14.59),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 118.04GB; nevents: 2.38M; release: 9_4_7; last modified: 2018-11-23 11:37:26"),
])

meta_dictionary["/WJetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "WJetsToLNu_madgraphMLM"),
  ("nof_db_events",         33073306),
  ("nof_db_files",          514),
  ("fsize_db",              1301026785288),
  ("xsection",              61526.7),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 1.30TB; nevents: 33.07M; release: 9_4_6_patch1; last modified: 2018-08-17 01:17:04"),
])

meta_dictionary["/WJetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14_ext1-v2/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "WJetsToLNu_madgraphMLM_ext1"),
  ("nof_db_events",         44627200),
  ("nof_db_files",          738),
  ("fsize_db",              1756207826672),
  ("xsection",              61526.7),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 1.76TB; nevents: 44.63M; release: 9_4_6_patch1; last modified: 2018-07-26 02:31:57"),
])

meta_dictionary["/W1JetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v3/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "W1JetsToLNu"),
  ("nof_db_events",         54147812),
  ("nof_db_files",          801),
  ("fsize_db",              2175397601720),
  ("xsection",              9418.44),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 2.18TB; nevents: 54.15M; release: 9_4_6_patch1; last modified: 2018-08-24 10:17:33"),
])

meta_dictionary["/W2JetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v4/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "W2JetsToLNu"),
  ("nof_db_events",         6577492),
  ("nof_db_files",          157),
  ("fsize_db",              283312015249),
  ("xsection",              3244.85),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 283.31GB; nevents: 6.58M; release: 9_4_6_patch1; last modified: 2018-08-05 18:44:31"),
])

meta_dictionary["/W3JetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "W3JetsToLNu"),
  ("nof_db_events",         19700377),
  ("nof_db_files",          250),
  ("fsize_db",              868954430671),
  ("xsection",              1153.02),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 868.95GB; nevents: 19.70M; release: 9_4_6_patch1; last modified: 2018-04-20 18:55:18"),
])

meta_dictionary["/W4JetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "W4JetsToLNu"),
  ("nof_db_events",         11333705),
  ("nof_db_files",          186),
  ("fsize_db",              544171543197),
  ("xsection",              633.05),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 544.17GB; nevents: 11.33M; release: 9_4_6_patch1; last modified: 2018-04-21 04:46:56"),
])

meta_dictionary["/WJetsToLNu_HT-70To100_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "WJetsToLNu_HT70To100"),
  ("nof_db_events",         22255124),
  ("nof_db_files",          403),
  ("fsize_db",              957900452414),
  ("xsection",              1502.72),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 957.90GB; nevents: 22.26M; release: 9_4_7; last modified: 2019-01-13 04:33:38"),
])

meta_dictionary["/WJetsToLNu_HT-100To200_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "WJetsToLNu_HT100To200"),
  ("nof_db_events",         35862893),
  ("nof_db_files",          735),
  ("fsize_db",              1632440553612),
  ("xsection",              1625.94),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 1.63TB; nevents: 35.86M; release: 9_4_6_patch1; last modified: 2018-07-16 22:47:23"),
])

meta_dictionary["/WJetsToLNu_HT-200To400_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "WJetsToLNu_HT200To400"),
  ("nof_db_events",         21250517),
  ("nof_db_files",          400),
  ("fsize_db",              1058111782457),
  ("xsection",              477.52),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 1.06TB; nevents: 21.25M; release: 9_4_6_patch1; last modified: 2018-06-11 22:53:32"),
])

meta_dictionary["/WJetsToLNu_HT-400To600_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "WJetsToLNu_HT400To600"),
  ("nof_db_events",         14313274),
  ("nof_db_files",          314),
  ("fsize_db",              780224610750),
  ("xsection",              67.51),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 780.22GB; nevents: 14.31M; release: 9_4_6_patch1; last modified: 2018-05-28 05:52:21"),
])

meta_dictionary["/WJetsToLNu_HT-600To800_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "WJetsToLNu_HT600To800"),
  ("nof_db_events",         21709087),
  ("nof_db_files",          488),
  ("fsize_db",              1256446599197),
  ("xsection",              15.09),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 1.26TB; nevents: 21.71M; release: 9_4_6_patch1; last modified: 2018-06-17 00:32:54"),
])

meta_dictionary["/WJetsToLNu_HT-800To1200_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "WJetsToLNu_HT800To1200"),
  ("nof_db_events",         20432728),
  ("nof_db_files",          487),
  ("fsize_db",              1225597665572),
  ("xsection",              6.297),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 1.23TB; nevents: 20.43M; release: 9_4_6_patch1; last modified: 2018-06-26 12:59:36"),
])

meta_dictionary["/WJetsToLNu_HT-1200To2500_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "WJetsToLNu_HT1200To2500"),
  ("nof_db_events",         20258624),
  ("nof_db_files",          551),
  ("fsize_db",              1289100671636),
  ("xsection",              1.262),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 1.29TB; nevents: 20.26M; release: 9_4_6_patch1; last modified: 2018-06-25 05:52:24"),
])

meta_dictionary["/WJetsToLNu_HT-2500ToInf_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v3/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "WJetsToLNu_HT2500ToInf"),
  ("nof_db_events",         21495421),
  ("nof_db_files",          616),
  ("fsize_db",              1489610697179),
  ("xsection",              0.009446),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 1.49TB; nevents: 21.50M; release: 9_4_6_patch1; last modified: 2018-07-06 12:31:23"),
])

meta_dictionary["/WWTo2L2Nu_NNPDF31_TuneCP5_13TeV-powheg-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "WWTo2L2Nu"),
  ("nof_db_events",         2000000),
  ("nof_db_files",          25),
  ("fsize_db",              85721560743),
  ("xsection",              12.178),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 85.72GB; nevents: 2.00M; release: 9_4_7; last modified: 2018-10-12 07:57:13"),
])

meta_dictionary["/WWTo2L2Nu_NNPDF31_TuneCP5_PSweights_13TeV-powheg-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14_ext1-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "WWTo2L2Nu_PSweights_ext1"),
  ("nof_db_events",         2000000),
  ("nof_db_files",          25),
  ("fsize_db",              85800202496),
  ("xsection",              12.178),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 85.80GB; nevents: 2.00M; release: 9_4_6_patch1; last modified: 2018-04-20 00:58:14"),
])

meta_dictionary["/WWToLNuQQ_NNPDF31_TuneCP5_13TeV-powheg-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "WWToLNuQQ"),
  ("nof_db_events",         8680425),
  ("nof_db_files",          100),
  ("fsize_db",              373194620065),
  ("xsection",              49.997),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 373.19GB; nevents: 8.68M; release: 9_4_6_patch1; last modified: 2018-04-19 18:18:30"),
])

meta_dictionary["/WWToLNuQQ_NNPDF31_TuneCP5_13TeV-powheg-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14_ext1-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "WWToLNuQQ_ext1"),
  ("nof_db_events",         9994191),
  ("nof_db_files",          127),
  ("fsize_db",              429884785891),
  ("xsection",              49.997),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 429.88GB; nevents: 9.99M; release: 9_4_6_patch1; last modified: 2018-04-21 09:47:36"),
])

meta_dictionary["/WWToLNuQQ_NNPDF31_TuneCP5_PSweights_13TeV-powheg-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14_ext1-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "WWToLNuQQ_PSweights_ext1"),
  ("nof_db_events",         8785360),
  ("nof_db_files",          100),
  ("fsize_db",              386842370187),
  ("xsection",              49.997),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 386.84GB; nevents: 8.79M; release: 9_4_6_patch1; last modified: 2018-07-18 14:24:34"),
])

meta_dictionary["/WWTo1L1Nu2Q_13TeV_amcatnloFXFX_madspin_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "WWTo1L1Nu2Q"),
  ("nof_db_events",         5054286),
  ("nof_db_files",          62),
  ("fsize_db",              215173204051),
  ("xsection",              49.997),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 215.17GB; nevents: 5.05M; release: 9_4_6_patch1; last modified: 2018-04-20 18:49:57"),
])

meta_dictionary["/WWTo4Q_NNPDF31_TuneCP5_13TeV-powheg-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "WWTo4Q"),
  ("nof_db_events",         1976644),
  ("nof_db_files",          25),
  ("fsize_db",              86393032016),
  ("xsection",              53.923),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 86.39GB; nevents: 1.98M; release: 9_4_6_patch1; last modified: 2018-04-19 22:38:31"),
])

meta_dictionary["/WWTo4Q_NNPDF31_TuneCP5_PSweights_13TeV-powheg-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14_ext1-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "WWTo4Q_PSweights_ext1"),
  ("nof_db_events",         1976360),
  ("nof_db_files",          26),
  ("fsize_db",              88368465560),
  ("xsection",              53.923),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 88.37GB; nevents: 1.98M; release: 9_4_6_patch1; last modified: 2018-04-20 01:33:15"),
])

meta_dictionary["/WZTo3LNu_TuneCP5_13TeV-amcatnloFXFX-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "WZTo3LNu"),
  ("nof_db_events",         10881896),
  ("nof_db_files",          125),
  ("fsize_db",              462299974031),
  ("xsection",              4.42965),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 462.30GB; nevents: 10.88M; release: 9_4_7; last modified: 2018-05-15 00:41:50"),
])

meta_dictionary["/WZTo3LNu_TuneCUETP8M1_13TeV-powheg-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "WZTo3LNu_powheg"),
  ("nof_db_events",         1993200),
  ("nof_db_files",          39),
  ("fsize_db",              63802464673),
  ("xsection",              4.42965),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 63.80GB; nevents: 1.99M; release: 8_0_21; last modified: 2016-12-17 12:27:24"),
])

meta_dictionary["/WZTo3LNu_0Jets_MLL-4to50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "WZTo3LNu_0Jets_MLL-4to50"),
  ("nof_db_events",         488461),
  ("nof_db_files",          24),
  ("fsize_db",              21565472983),
  ("xsection",              2.508),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 21.57GB; nevents: 488.46k; release: 9_4_7; last modified: 2018-09-26 11:09:41"),
])

meta_dictionary["/WZTo3LNu_0Jets_MLL-50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v3/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "WZTo3LNu_0Jets_MLL-50"),
  ("nof_db_events",         473818),
  ("nof_db_files",          24),
  ("fsize_db",              23217296859),
  ("xsection",              0.638),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 23.22GB; nevents: 473.82k; release: 9_4_6_patch1; last modified: 2018-05-19 01:52:12"),
])

meta_dictionary["/WZTo3LNu_1Jets_MLL-4to50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "WZTo3LNu_1Jets_MLL-4to50"),
  ("nof_db_events",         506673),
  ("nof_db_files",          22),
  ("fsize_db",              24141156011),
  ("xsection",              0.4868),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 24.14GB; nevents: 506.67k; release: 9_4_7; last modified: 2018-09-19 01:57:44"),
])

meta_dictionary["/WZTo3LNu_1Jets_MLL-50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "WZTo3LNu_1Jets_MLL-50"),
  ("nof_db_events",         486727),
  ("nof_db_files",          26),
  ("fsize_db",              25784953540),
  ("xsection",              0.3389),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 25.78GB; nevents: 486.73k; release: 9_4_6_patch1; last modified: 2018-06-29 18:33:36"),
])

meta_dictionary["/WZTo3LNu_2Jets_MLL-4to50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "WZTo3LNu_2Jets_MLL-4to50"),
  ("nof_db_events",         1433913),
  ("nof_db_files",          75),
  ("fsize_db",              73675561875),
  ("xsection",              0.164),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 73.68GB; nevents: 1.43M; release: 9_4_7; last modified: 2018-10-04 12:15:15"),
])

meta_dictionary["/WZTo3LNu_2Jets_MLL-50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "WZTo3LNu_2Jets_MLL-50"),
  ("nof_db_events",         1835965),
  ("nof_db_files",          80),
  ("fsize_db",              107485243900),
  ("xsection",              0.06645),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 107.49GB; nevents: 1.84M; release: 9_4_6_patch1; last modified: 2018-07-24 01:27:08"),
])

meta_dictionary["/WZTo3LNu_3Jets_MLL-4to50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "WZTo3LNu_3Jets_MLL-4to50"),
  ("nof_db_events",         2069899),
  ("nof_db_files",          110),
  ("fsize_db",              117165529475),
  ("xsection",              0.07121),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 117.17GB; nevents: 2.07M; release: 9_4_7; last modified: 2018-09-19 01:59:12"),
])

meta_dictionary["/WZTo3LNu_3Jets_MLL-50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "WZTo3LNu_3Jets_MLL-50"),
  ("nof_db_events",         1832414),
  ("nof_db_files",          98),
  ("fsize_db",              115010601689),
  ("xsection",              0.09521),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 115.01GB; nevents: 1.83M; release: 9_4_6_patch1; last modified: 2018-07-02 06:51:45"),
])

meta_dictionary["/WZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "WZTo2L2Q"),
  ("nof_db_events",         27582164),
  ("nof_db_files",          406),
  ("fsize_db",              1286368112175),
  ("xsection",              5.595),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 1.29TB; nevents: 27.58M; release: 9_4_7; last modified: 2018-05-22 02:51:17"),
])

meta_dictionary["/WZTo1L1Nu2Q_13TeV_amcatnloFXFX_madspin_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "WZTo1L1Nu2Q"),
  ("nof_db_events",         19086373),
  ("nof_db_files",          309),
  ("fsize_db",              888745631538),
  ("xsection",              10.71),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 888.75GB; nevents: 19.09M; release: 9_4_6_patch1; last modified: 2018-06-28 07:36:24"),
])

meta_dictionary["/ZZTo4L_13TeV_powheg_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "ZZTo4L"),
  ("nof_db_events",         16075000),
  ("nof_db_files",          362),
  ("fsize_db",              679700693766),
  ("xsection",              1.256),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 679.70GB; nevents: 16.07M; release: 9_4_7; last modified: 2018-11-24 04:42:20"),
])

meta_dictionary["/ZZTo4L_13TeV_powheg_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14_ext1-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "ZZTo4L_ext1"),
  ("nof_db_events",         98091559),
  ("nof_db_files",          1128),
  ("fsize_db",              4014158215850),
  ("xsection",              1.256),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 4.01TB; nevents: 98.09M; release: 9_4_6_patch1; last modified: 2018-04-20 10:25:00"),
])

meta_dictionary["/ZZTo2L2Nu_13TeV_powheg_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "ZZTo2L2Nu"),
  ("nof_db_events",         8744768),
  ("nof_db_files",          112),
  ("fsize_db",              380491063113),
  ("xsection",              0.564),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 380.49GB; nevents: 8.74M; release: 9_4_7; last modified: 2018-10-07 10:37:59"),
])

meta_dictionary["/ZZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "ZZTo2L2Q"),
  ("nof_db_events",         27840918),
  ("nof_db_files",          409),
  ("fsize_db",              1296656277482),
  ("xsection",              3.22),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 1.30TB; nevents: 27.84M; release: 9_4_7; last modified: 2018-05-15 00:42:20"),
])

meta_dictionary["/QCD_Pt_20to30_bcToE_TuneCP5_13TeV_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "QCD"),
  ("process_name_specific", "QCD_Pt20to30_bcToE"),
  ("nof_db_events",         10270639),
  ("nof_db_files",          113),
  ("fsize_db",              385896332086),
  ("xsection",              305500.0),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 385.90GB; nevents: 10.27M; release: 9_4_7; last modified: 2018-05-18 04:53:33"),
])

meta_dictionary["/QCD_Pt_30to80_bcToE_TuneCP5_13TeV_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "QCD"),
  ("process_name_specific", "QCD_Pt30to80_bcToE"),
  ("nof_db_events",         16073047),
  ("nof_db_files",          186),
  ("fsize_db",              633331988305),
  ("xsection",              361100.0),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 633.33GB; nevents: 16.07M; release: 9_4_6_patch1; last modified: 2018-04-20 00:35:07"),
])

meta_dictionary["/QCD_Pt_80to170_bcToE_TuneCP5_13TeV_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "QCD"),
  ("process_name_specific", "QCD_Pt80to170_bcToE"),
  ("nof_db_events",         15999466),
  ("nof_db_files",          189),
  ("fsize_db",              711041578903),
  ("xsection",              33830.0),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 711.04GB; nevents: 16.00M; release: 9_4_6_patch1; last modified: 2018-04-20 01:05:40"),
])

meta_dictionary["/QCD_Pt_170to250_bcToE_TuneCP5_13TeV_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "QCD"),
  ("process_name_specific", "QCD_Pt170to250_bcToE"),
  ("nof_db_events",         9847660),
  ("nof_db_files",          176),
  ("fsize_db",              477892307613),
  ("xsection",              2129.0),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 477.89GB; nevents: 9.85M; release: 9_4_6_patch1; last modified: 2018-04-21 09:48:08"),
])

meta_dictionary["/QCD_Pt_250toInf_bcToE_TuneCP5_13TeV_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "QCD"),
  ("process_name_specific", "QCD_Pt250toInf_bcToE"),
  ("nof_db_events",         9996886),
  ("nof_db_files",          187),
  ("fsize_db",              513285807270),
  ("xsection",              562.8),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 513.29GB; nevents: 10.00M; release: 9_4_6_patch1; last modified: 2018-04-20 00:39:27"),
])

meta_dictionary["/QCD_Pt-15to20_EMEnriched_TuneCP5_13TeV_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "QCD"),
  ("process_name_specific", "QCD_Pt15to20_EMEnriched"),
  ("nof_db_events",         11215220),
  ("nof_db_files",          134),
  ("fsize_db",              397192727584),
  ("xsection",              1324000.0),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 397.19GB; nevents: 11.22M; release: 9_4_6_patch1; last modified: 2018-04-20 01:13:01"),
])

meta_dictionary["/QCD_Pt-20to30_EMEnriched_TuneCP5_13TeV_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "QCD"),
  ("process_name_specific", "QCD_Pt20to30_EMEnriched"),
  ("nof_db_events",         11212810),
  ("nof_db_files",          125),
  ("fsize_db",              406252937750),
  ("xsection",              4910000.0),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 406.25GB; nevents: 11.21M; release: 9_4_6_patch1; last modified: 2018-04-20 00:59:51"),
])

meta_dictionary["/QCD_Pt-30to50_EMEnriched_TuneCP5_13TeV_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "QCD"),
  ("process_name_specific", "QCD_Pt30to50_EMEnriched"),
  ("nof_db_events",         14766010),
  ("nof_db_files",          176),
  ("fsize_db",              553990333710),
  ("xsection",              6415000.0),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 553.99GB; nevents: 14.77M; release: 9_4_6_patch1; last modified: 2018-04-26 12:19:20"),
])

meta_dictionary["/QCD_Pt-50to80_EMEnriched_TuneCP5_13TeV_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "QCD"),
  ("process_name_specific", "QCD_Pt50to80_EMEnriched"),
  ("nof_db_events",         10477146),
  ("nof_db_files",          128),
  ("fsize_db",              412202461390),
  ("xsection",              1986000.0),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 412.20GB; nevents: 10.48M; release: 9_4_6_patch1; last modified: 2018-04-20 12:20:18"),
])

meta_dictionary["/QCD_Pt-80to120_EMEnriched_TuneCP5_13TeV_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "QCD"),
  ("process_name_specific", "QCD_Pt80to120_EMEnriched"),
  ("nof_db_events",         9104852),
  ("nof_db_files",          108),
  ("fsize_db",              389362639707),
  ("xsection",              366500.0),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 389.36GB; nevents: 9.10M; release: 9_4_7; last modified: 2018-10-17 12:17:36"),
])

meta_dictionary["/QCD_Pt-120to170_EMEnriched_TuneCP5_13TeV_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "QCD"),
  ("process_name_specific", "QCD_Pt120to170_EMEnriched"),
  ("nof_db_events",         8515107),
  ("nof_db_files",          163),
  ("fsize_db",              385000236556),
  ("xsection",              66510.0),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 385.00GB; nevents: 8.52M; release: 9_4_7; last modified: 2018-09-07 16:00:14"),
])

meta_dictionary["/QCD_Pt-300toInf_EMEnriched_TuneCP5_13TeV_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "QCD"),
  ("process_name_specific", "QCD_Pt300toInf_EMEnriched"),
  ("nof_db_events",         2874295),
  ("nof_db_files",          49),
  ("fsize_db",              144869144781),
  ("xsection",              1099.0),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 144.87GB; nevents: 2.87M; release: 9_4_6_patch1; last modified: 2018-04-21 10:04:42"),
])

meta_dictionary["/QCD_Pt-15to20_MuEnrichedPt5_TuneCP5_13TeV_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "QCD"),
  ("process_name_specific", "QCD_Pt15to20_Mu5"),
  ("nof_db_events",         5859904),
  ("nof_db_files",          63),
  ("fsize_db",              216516638901),
  ("xsection",              2808000.0),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 216.52GB; nevents: 5.86M; release: 9_4_6_patch1; last modified: 2018-04-19 22:42:17"),
])

meta_dictionary["/QCD_Pt-20to30_MuEnrichedPt5_TuneCP5_13TeV_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "QCD"),
  ("process_name_specific", "QCD_Pt20to30_Mu5"),
  ("nof_db_events",         28213684),
  ("nof_db_files",          319),
  ("fsize_db",              1058418704070),
  ("xsection",              2530000.0),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 1.06TB; nevents: 28.21M; release: 9_4_6_patch1; last modified: 2018-04-19 18:10:49"),
])

meta_dictionary["/QCD_Pt-30to50_MuEnrichedPt5_TuneCP5_13TeV_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "QCD"),
  ("process_name_specific", "QCD_Pt30to50_Mu5"),
  ("nof_db_events",         29030324),
  ("nof_db_files",          325),
  ("fsize_db",              1131094971096),
  ("xsection",              1368000.0),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 1.13TB; nevents: 29.03M; release: 9_4_6_patch1; last modified: 2018-04-20 00:37:37"),
])

meta_dictionary["/QCD_Pt-50to80_MuEnrichedPt5_TuneCP5_13TeV_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "QCD"),
  ("process_name_specific", "QCD_Pt50to80_Mu5"),
  ("nof_db_events",         24068613),
  ("nof_db_files",          288),
  ("fsize_db",              1004660826025),
  ("xsection",              378000.0),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 1.00TB; nevents: 24.07M; release: 9_4_6_patch1; last modified: 2018-04-20 18:57:38"),
])

meta_dictionary["/QCD_Pt-80to120_MuEnrichedPt5_TuneCP5_13TeV_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "QCD"),
  ("process_name_specific", "QCD_Pt80to120_Mu5"),
  ("nof_db_events",         23248995),
  ("nof_db_files",          289),
  ("fsize_db",              1035795578059),
  ("xsection",              88580.0),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 1.04TB; nevents: 23.25M; release: 9_4_6_patch1; last modified: 2018-04-20 10:20:52"),
])

meta_dictionary["/QCD_Pt-120to170_MuEnrichedPt5_TuneCP5_13TeV_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "QCD"),
  ("process_name_specific", "QCD_Pt120to170_Mu5"),
  ("nof_db_events",         20774848),
  ("nof_db_files",          342),
  ("fsize_db",              984472671147),
  ("xsection",              21170.0),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 984.47GB; nevents: 20.77M; release: 9_4_6_patch1; last modified: 2018-04-20 00:46:29"),
])

meta_dictionary["/QCD_Pt-170to300_MuEnrichedPt5_TuneCP5_13TeV_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "QCD"),
  ("process_name_specific", "QCD_Pt170to300_Mu5"),
  ("nof_db_events",         46170668),
  ("nof_db_files",          721),
  ("fsize_db",              2330576867261),
  ("xsection",              7025.0),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 2.33TB; nevents: 46.17M; release: 9_4_6_patch1; last modified: 2018-04-20 01:20:32"),
])

meta_dictionary["/QCD_Pt-300to470_MuEnrichedPt5_TuneCP5_13TeV_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "QCD"),
  ("process_name_specific", "QCD_Pt300to470_Mu5"),
  ("nof_db_events",         17744779),
  ("nof_db_files",          374),
  ("fsize_db",              989950950093),
  ("xsection",              620.5),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 989.95GB; nevents: 17.74M; release: 9_4_7; last modified: 2018-10-19 01:57:32"),
])

meta_dictionary["/QCD_Pt-470to600_MuEnrichedPt5_TuneCP5_13TeV_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "QCD"),
  ("process_name_specific", "QCD_Pt470to600_Mu5"),
  ("nof_db_events",         24243589),
  ("nof_db_files",          388),
  ("fsize_db",              1390197744079),
  ("xsection",              59.11),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 1.39TB; nevents: 24.24M; release: 9_4_6_patch1; last modified: 2018-04-20 11:34:40"),
])

meta_dictionary["/QCD_Pt-800to1000_MuEnrichedPt5_TuneCP5_13TeV_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "QCD"),
  ("process_name_specific", "QCD_Pt800to1000_Mu5"),
  ("nof_db_events",         17114527),
  ("nof_db_files",          389),
  ("fsize_db",              1061424382303),
  ("xsection",              3.275),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 1.06TB; nevents: 17.11M; release: 9_4_7; last modified: 2019-02-05 03:57:20"),
])

meta_dictionary["/QCD_Pt-1000toInf_MuEnrichedPt5_TuneCP5_13TeV_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "QCD"),
  ("process_name_specific", "QCD_Pt1000toInf_Mu5"),
  ("nof_db_events",         11596693),
  ("nof_db_files",          257),
  ("fsize_db",              741261028289),
  ("xsection",              1.079),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 741.26GB; nevents: 11.60M; release: 9_4_7; last modified: 2018-12-08 11:11:25"),
])


# event statistics by sample category:
# signal:                    43.48M
# tHq:                       13.30M
# tHW:                       6.16M
# additional_signal_overlap: 965.20k
# TTZ:                       37.51M
# TTW:                       25.76M
# TTWW:                      200.00k
# TT:                        949.67M
# Rares:                     87.88M
# VH:                        10.67M
# EWK:                       1.17G
# QCD:                       378.42M

