from collections import OrderedDict as OD

# file generated at 2018-04-20 22:19:24 with the following command:
# find_samples.py -i ../NanoAOD/test/datasets_mc_2017.txt -V -m python/samples/metaDict_2017_mc.py

meta_dictionary = OD()


### event sums

sum_events = { 
  ("TTToHadronic", "TTToHadronic_PSweights"),
  ("TTTo2L2Nu", "TTTo2L2Nu_PSweights"),
  ("DYJetsToLL_M-50", "DYJetsToLL_M-50_ext1"),
  ("TTWJetsToLNu", "TTWJetsToLNu_PSweights"),
  ("ZZTo4L", "ZZTo4L_ext1"),
  ("TTToSemiLeptonic", "TTToSemiLeptonic_PSweights"),
}


meta_dictionary["/ttHJetToNonbb_M125_TuneCP5_13TeV_amcatnloFXFX_madspin_pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "signal"),
  ("process_name_specific", "ttHJetToNonbb_M125_amcatnlo"),
  ("nof_db_events",         9650032),
  ("nof_db_files",          283),
  ("fsize_db",              603282930374),
  ("xsection",              0.2118),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 603.28GB; nevents: 9.65M; release: 9_4_0_patch1; last modified: 2018-02-25 01:47:16"),
])

meta_dictionary["/ttHToNonbb_M125_TuneCP5_13TeV-powheg-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "signal"),
  ("process_name_specific", "ttHToNonbb_M125_powheg"),
  ("nof_db_events",         7669336),
  ("nof_db_files",          219),
  ("fsize_db",              465938496839),
  ("xsection",              0.2118),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 465.94GB; nevents: 7.67M; release: 9_4_0_patch1; last modified: 2018-02-17 14:21:12"),
])

meta_dictionary["/GluGluHToZZTo4L_M125_13TeV_powheg2_JHUGenV7011_pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "additional_signal_overlap"),
  ("process_name_specific", "GluGluHToZZTo4L"),
  ("nof_db_events",         934244),
  ("nof_db_files",          47),
  ("fsize_db",              42622664498),
  ("xsection",              0.01212),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 42.62GB; nevents: 934.24k; release: 9_4_0_patch1; last modified: 2018-02-06 20:27:24"),
])

meta_dictionary["/TTZToLLNuNu_M-10_TuneCP5_13TeV-amcatnlo-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "TTZ"),
  ("process_name_specific", "TTZToLL_M10"),
  ("nof_db_events",         7563490),
  ("nof_db_files",          199),
  ("fsize_db",              444833969271),
  ("xsection",              0.2529),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 444.83GB; nevents: 7.56M; release: 9_4_0_patch1; last modified: 2018-01-23 23:10:22"),
])

meta_dictionary["/TTZToLL_M-1to10_TuneCP5_13TeV-amcatnlo-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "TTZ"),
  ("process_name_specific", "TTZToLL_M-1to10"),
  ("nof_db_events",         250000),
  ("nof_db_files",          17),
  ("fsize_db",              14727460148),
  ("xsection",              0.0493),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 14.73GB; nevents: 250.00k; release: 9_4_0_patch1; last modified: 2017-12-21 15:03:55"),
])

meta_dictionary["/TTWJetsToLNu_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v2/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "TTW"),
  ("process_name_specific", "TTWJetsToLNu"),
  ("nof_db_events",         4925829),
  ("nof_db_files",          109),
  ("fsize_db",              292280765632),
  ("xsection",              0.2043),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 292.28GB; nevents: 4.93M; release: 9_4_0_patch1; last modified: 2018-02-08 17:33:34"),
])

meta_dictionary["/TTWJetsToLNu_TuneCP5_PSweights_13TeV-amcatnloFXFX-madspin-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "TTW"),
  ("process_name_specific", "TTWJetsToLNu_PSweights"),
  ("nof_db_events",         4889942),
  ("nof_db_files",          122),
  ("fsize_db",              290787551975),
  ("xsection",              0.2043),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 290.79GB; nevents: 4.89M; release: 9_4_0_patch1; last modified: 2018-02-17 16:02:45"),
])

meta_dictionary["/TTWW_TuneCP5_13TeV-madgraph-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10_ext1-v2/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "TTWW"),
  ("process_name_specific", "TTWW"),
  ("nof_db_events",         200000),
  ("nof_db_files",          11),
  ("fsize_db",              13111885203),
  ("xsection",              0.007834),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 13.11GB; nevents: 200.00k; release: 9_4_0_patch1; last modified: 2018-03-03 05:02:52"),
])

meta_dictionary["/ST_s-channel_4f_leptonDecays_TuneCP5_13TeV-amcatnlo-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "TT"),
  ("process_name_specific", "ST_s-channel_4f_leptonDecays"),
  ("nof_db_events",         9472619),
  ("nof_db_files",          217),
  ("fsize_db",              423862017407),
  ("xsection",              3.36),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 423.86GB; nevents: 9.47M; release: 9_4_0_patch1; last modified: 2018-01-20 12:40:35"),
])

meta_dictionary["/ST_t-channel_antitop_4f_inclusiveDecays_TuneCP5_13TeV-powhegV2-madspin-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "TT"),
  ("process_name_specific", "ST_t-channel_antitop_4f_inclusiveDecays"),
  ("nof_db_events",         3891190),
  ("nof_db_files",          116),
  ("fsize_db",              177784436788),
  ("xsection",              80.95),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 177.78GB; nevents: 3.89M; release: 9_4_0_patch1; last modified: 2018-01-14 03:54:35"),
])

meta_dictionary["/ST_t-channel_top_4f_inclusiveDecays_TuneCP5_13TeV-powhegV2-madspin-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "TT"),
  ("process_name_specific", "ST_t-channel_top_4f_inclusiveDecays"),
  ("nof_db_events",         5841455),
  ("nof_db_files",          186),
  ("fsize_db",              268058212482),
  ("xsection",              136.02),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 268.06GB; nevents: 5.84M; release: 9_4_0_patch1; last modified: 2018-01-16 00:24:51"),
])

meta_dictionary["/ST_tW_antitop_5f_inclusiveDecays_TuneCP5_13TeV-powheg-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "TT"),
  ("process_name_specific", "ST_tW_antitop_5f_inclusiveDecays"),
  ("nof_db_events",         7756300),
  ("nof_db_files",          155),
  ("fsize_db",              386122494678),
  ("xsection",              35.85),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 386.12GB; nevents: 7.76M; release: 9_4_0_patch1; last modified: 2018-01-23 00:51:57"),
])

meta_dictionary["/ST_tW_top_5f_inclusiveDecays_TuneCP5_13TeV-powheg-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "TT"),
  ("process_name_specific", "ST_tW_top_5f_inclusiveDecays"),
  ("nof_db_events",         7558006),
  ("nof_db_files",          183),
  ("fsize_db",              376466493438),
  ("xsection",              35.85),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 376.47GB; nevents: 7.56M; release: 9_4_0_patch1; last modified: 2018-01-15 00:03:54"),
])

meta_dictionary["/TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v2/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "TT"),
  ("process_name_specific", "TTTo2L2Nu"),
  ("nof_db_events",         8705576),
  ("nof_db_files",          164),
  ("fsize_db",              451436194017),
  ("xsection",              88.29),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 451.44GB; nevents: 8.71M; release: 9_4_0_patch1; last modified: 2018-01-09 22:02:38"),
])

meta_dictionary["/TTTo2L2Nu_TuneCP5_PSweights_13TeV-powheg-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "TT"),
  ("process_name_specific", "TTTo2L2Nu_PSweights"),
  ("nof_db_events",         69705626),
  ("nof_db_files",          1230),
  ("fsize_db",              3608766343800),
  ("xsection",              88.29),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 3.61TB; nevents: 69.71M; release: 9_4_0_patch1; last modified: 2018-01-11 15:10:21"),
])

meta_dictionary["/TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "TT"),
  ("process_name_specific", "TTToSemiLeptonic"),
  ("nof_db_events",         41161951),
  ("nof_db_files",          743),
  ("fsize_db",              2166068169129),
  ("xsection",              365.34),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 2.17TB; nevents: 41.16M; release: 9_4_0_patch1; last modified: 2018-02-01 21:28:40"),
])

meta_dictionary["/TTToSemiLeptonic_TuneCP5_PSweights_13TeV-powheg-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "TT"),
  ("process_name_specific", "TTToSemiLeptonic_PSweights"),
  ("nof_db_events",         111381888),
  ("nof_db_files",          2032),
  ("fsize_db",              5860979058540),
  ("xsection",              365.34),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 5.86TB; nevents: 111.38M; release: 9_4_0_patch1; last modified: 2018-01-11 00:38:22"),
])

meta_dictionary["/TTToHadronic_TuneCP5_13TeV-powheg-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "TT"),
  ("process_name_specific", "TTToHadronic"),
  ("nof_db_events",         42678688),
  ("nof_db_files",          765),
  ("fsize_db",              2292321642457),
  ("xsection",              377.96),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 2.29TB; nevents: 42.68M; release: 9_4_0_patch1; last modified: 2018-02-24 05:06:16"),
])

meta_dictionary["/TTToHadronic_TuneCP5_PSweights_13TeV-powheg-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "TT"),
  ("process_name_specific", "TTToHadronic_PSweights"),
  ("nof_db_events",         129985840),
  ("nof_db_files",          2498),
  ("fsize_db",              6970450887587),
  ("xsection",              377.96),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 6.97TB; nevents: 129.99M; release: 9_4_0_patch1; last modified: 2018-01-24 23:15:56"),
])

meta_dictionary["/DYJetsToLL_M-10to50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v2/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DYJetsToLL_M-10to50"),
  ("nof_db_events",         38832197),
  ("nof_db_files",          508),
  ("fsize_db",              1343136870100),
  ("xsection",              18610.0),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 1.34TB; nevents: 38.83M; release: 9_4_0_patch1; last modified: 2018-02-26 22:05:21"),
])

meta_dictionary["/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DYJetsToLL_M-50"),
  ("nof_db_events",         26923935),
  ("nof_db_files",          372),
  ("fsize_db",              1065736102325),
  ("xsection",              5765.4),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 1.07TB; nevents: 26.92M; release: 9_4_0_patch1; last modified: 2018-01-11 00:33:57"),
])

meta_dictionary["/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10_ext1-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DYJetsToLL_M-50_ext1"),
  ("nof_db_events",         185998625),
  ("nof_db_files",          2752),
  ("fsize_db",              7376341087077),
  ("xsection",              5765.4),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 7.38TB; nevents: 186.00M; release: 9_4_0_patch1; last modified: 2018-02-19 14:25:32"),
])

meta_dictionary["/WJetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "WJetsToLNu"),
  ("nof_db_events",         23240598),
  ("nof_db_files",          382),
  ("fsize_db",              882645881655),
  ("xsection",              61526.7),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: PRODUCTION; size: 882.65GB; nevents: 23.24M; release: 9_4_0_patch1; last modified: 2018-01-22 15:06:50"),
])

meta_dictionary["/WWTo2L2Nu_NNPDF31_TuneCP5_13TeV-powheg-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "WWTo2L2Nu"),
  ("nof_db_events",         1818828),
  ("nof_db_files",          50),
  ("fsize_db",              75643188117),
  ("xsection",              12.178),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 75.64GB; nevents: 1.82M; release: 9_4_0_patch1; last modified: 2018-02-09 10:06:57"),
])

meta_dictionary["/WZTo3LNu_TuneCP5_13TeV-amcatnloFXFX-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v2/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "WZTo3LNu"),
  ("nof_db_events",         10751052),
  ("nof_db_files",          212),
  ("fsize_db",              452807583489),
  ("xsection",              4.42965),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 452.81GB; nevents: 10.75M; release: 9_4_0_patch1; last modified: 2018-02-06 20:33:20"),
])

meta_dictionary["/ZZTo4L_13TeV_powheg_pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v2/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "ZZTo4L"),
  ("nof_db_events",         6960289),
  ("nof_db_files",          204),
  ("fsize_db",              322020515003),
  ("xsection",              1.256),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 322.02GB; nevents: 6.96M; release: 9_4_0_patch1; last modified: 2017-12-09 15:05:32"),
])

meta_dictionary["/ZZTo4L_13TeV_powheg_pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10_ext1-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "ZZTo4L_ext1"),
  ("nof_db_events",         95716759),
  ("nof_db_files",          1490),
  ("fsize_db",              3881682466950),
  ("xsection",              1.256),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 3.88TB; nevents: 95.72M; release: 9_4_0_patch1; last modified: 2018-02-09 16:08:21"),
])

meta_dictionary["/TTGJets_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "Rares"),
  ("process_name_specific", "TTGJets"),
  ("nof_db_events",         4647278),
  ("nof_db_files",          138),
  ("fsize_db",              269969335093),
  ("xsection",              3.697),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 269.97GB; nevents: 4.65M; release: 9_4_0_patch1; last modified: 2018-01-23 11:13:18"),
])

meta_dictionary["/TTTT_TuneCP5_13TeV-amcatnlo-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v2/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "Rares"),
  ("process_name_specific", "TTTT"),
  ("nof_db_events",         993804),
  ("nof_db_files",          29),
  ("fsize_db",              77438656415),
  ("xsection",              0.008213),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 77.44GB; nevents: 993.80k; release: 9_4_0_patch1; last modified: 2018-02-23 15:30:59"),
])

meta_dictionary["/tZq_ll_4f_ckm_NLO_TuneCP5_PSweights_13TeV-amcatnlo-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "Rares"),
  ("process_name_specific", "tZq_ll_4f"),
  ("nof_db_events",         13220024),
  ("nof_db_files",          292),
  ("fsize_db",              723683119488),
  ("xsection",              0.0758),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 723.68GB; nevents: 13.22M; release: 9_4_0_patch1; last modified: 2018-02-17 15:41:39"),
])

meta_dictionary["/WWTo2L2Nu_DoubleScattering_13TeV-herwigpp/RunIIFall17MiniAOD-94X_mc2017_realistic_v11-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "Rares"),
  ("process_name_specific", "WWTo2L2Nu_DoubleScattering"),
  ("nof_db_events",         1000000),
  ("nof_db_files",          23),
  ("fsize_db",              42876536279),
  ("xsection",              0.1743),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 42.88GB; nevents: 1.00M; release: 9_4_0_patch1; last modified: 2018-03-26 17:51:09"),
])

meta_dictionary["/WWW_4F_TuneCP5_13TeV-amcatnlo-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v11-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "Rares"),
  ("process_name_specific", "WWW_4F"),
  ("nof_db_events",         240000),
  ("nof_db_files",          21),
  ("fsize_db",              11711799646),
  ("xsection",              0.2086),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 11.71GB; nevents: 240.00k; release: 9_4_0_patch1; last modified: 2018-03-01 06:04:33"),
])

meta_dictionary["/WZZ_TuneCP5_13TeV-amcatnlo-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v11-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "Rares"),
  ("process_name_specific", "WZZ"),
  ("nof_db_events",         250000),
  ("nof_db_files",          18),
  ("fsize_db",              12226507693),
  ("xsection",              0.05565),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 12.23GB; nevents: 250.00k; release: 9_4_0_patch1; last modified: 2018-03-05 12:43:46"),
])

meta_dictionary["/ZZZ_TuneCP5_13TeV-amcatnlo-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v11-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "Rares"),
  ("process_name_specific", "ZZZ"),
  ("nof_db_events",         250000),
  ("nof_db_files",          17),
  ("fsize_db",              11782250391),
  ("xsection",              0.01398),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 11.78GB; nevents: 250.00k; release: 9_4_0_patch1; last modified: 2018-03-14 05:49:59"),
])


# event statistics by sample category:
# signal:                    17.32M
# additional_signal_overlap: 934.24k
# TTZ:                       7.81M
# TTW:                       9.82M
# TTWW:                      200.00k
# TT:                        438.14M
# EWK:                       390.24M
# Rares:                     20.60M

