from collections import OrderedDict as OD

# file generated at 2019-05-14 04:11:32 with the following command:
# find_samples.py -V -i ../NanoAOD/test/datasets/txt/datasets_mc_2018_RunIIAutumn18MiniAOD.txt -m python/samples/metaDict_2018_mc.py -s ../NanoAOD/test/datasets/txt/sum_datasets_2018_RunIIAutumn18MiniAOD.txt

meta_dictionary = OD()


### event sums

sum_events = { 
  ("TTWW_ext1", "TTWW_ext2"),
  ("ZH_HToBB_ZToLL", "ZH_HToBB_ZToLL_ext1"),
  ("DYJetsToLL_M-50_amcatnloFXFX", "DYJetsToLL_M-50_amcatnloFXFX_ext2"),
  ("DYJetsToLL_M50_HT400to600_PSweights", "DYJetsToLL_M50_HT400to600_PSweights_ext2"),
  ("WZTo3LNu", "WZTo3LNu_ext1"),
  ("ZZTo4L_ext1", "ZZTo4L_ext2"),
  ("ZZTo2L2Nu_ext1", "ZZTo2L2Nu_ext2"),
  ("QCD_Pt80to120_Mu5", "QCD_Pt80to120_Mu5_ext1"),
  ("QCD_Pt120to170_Mu5", "QCD_Pt120to170_Mu5_ext1"),
  ("QCD_Pt300to470_Mu5", "QCD_Pt300to470_Mu5_ext3"),
  ("QCD_Pt470to600_Mu5", "QCD_Pt470to600_Mu5_ext1"),
}


meta_dictionary["/ttHToNonbb_M125_TuneCP5_13TeV-powheg-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v2/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "signal"),
  ("process_name_specific", "ttHToNonbb_M125_powheg"),
  ("nof_db_events",         7525991),
  ("nof_db_files",          224),
  ("fsize_db",              469867184231),
  ("xsection",              0.2118),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 469.87GB; nevents: 7.53M; release: 10_2_5; last modified: 2018-12-25 21:13:06"),
])

meta_dictionary["/ttHTobb_M125_TuneCP5_13TeV-powheg-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v3/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "signal"),
  ("process_name_specific", "ttHTobb_M125_powheg"),
  ("nof_db_events",         11835999),
  ("nof_db_files",          319),
  ("fsize_db",              747952512985),
  ("xsection",              0.2953),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 747.95GB; nevents: 11.84M; release: 10_2_5; last modified: 2019-01-17 22:53:35"),
])

meta_dictionary["/TTH_4f_ctcvcp_TuneCP5_13TeV_madgraph_pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "signal"),
  ("process_name_specific", "TTH_4f_ctcvcp"),
  ("nof_db_events",         29093000),
  ("nof_db_files",          720),
  ("fsize_db",              1815791395391),
  ("xsection",              0.5071),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 1.82TB; nevents: 29.09M; release: 10_2_5; last modified: 2019-01-14 14:01:02"),
])

meta_dictionary["/ttHTobb_ttToSemiLep_M125_TuneCP5_13TeV-powheg-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "signal"),
  ("process_name_specific", "ttHTobb_ttToSemiLep_M125"),
  ("nof_db_events",         9635500),
  ("nof_db_files",          319),
  ("fsize_db",              604307711571),
  ("xsection",              0.1298),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 604.31GB; nevents: 9.64M; release: 10_2_5; last modified: 2019-03-20 19:48:49"),
])

meta_dictionary["/ttHTobb_ttTo2L2Nu_M125_TuneCP5_13TeV-powheg-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "signal"),
  ("process_name_specific", "ttHTobb_ttTo2L2Nu_M125"),
  ("nof_db_events",         9572600),
  ("nof_db_files",          334),
  ("fsize_db",              595087252743),
  ("xsection",              0.03136),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 595.09GB; nevents: 9.57M; release: 10_2_5; last modified: 2019-03-28 14:35:22"),
])

meta_dictionary["/THQ_ctcvcp_4f_Hincl_13TeV_madgraph_pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "tHq"),
  ("process_name_specific", "THQ_ctcvcp"),
  ("nof_db_events",         29683974),
  ("nof_db_files",          793),
  ("fsize_db",              1681088947501),
  ("xsection",              0.07096),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 1.68TB; nevents: 29.68M; release: 10_2_5; last modified: 2019-02-03 22:41:54"),
])

meta_dictionary["/THW_ctcvcp_5f_Hincl_13TeV_madgraph_pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "tHW"),
  ("process_name_specific", "THW_ctcvcp"),
  ("nof_db_events",         14998988),
  ("nof_db_files",          436),
  ("fsize_db",              958252346048),
  ("xsection",              0.01561),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 958.25GB; nevents: 15.00M; release: 10_2_5; last modified: 2019-01-22 18:31:18"),
])

meta_dictionary["/GluGluHToZZTo4L_M125_13TeV_powheg2_JHUGenV7011_pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v2/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "additional_signal_overlap"),
  ("process_name_specific", "GluGluHToZZTo4L"),
  ("nof_db_events",         958000),
  ("nof_db_files",          30),
  ("fsize_db",              44997251487),
  ("xsection",              0.01297),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 45.00GB; nevents: 958.00k; release: 10_2_5; last modified: 2018-12-03 02:58:46"),
])

meta_dictionary["/TTZToLLNuNu_M-10_TuneCP5_13TeV-amcatnlo-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15_ext1-v2/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "TTZ"),
  ("process_name_specific", "TTZToLL_M10_ext1"),
  ("nof_db_events",         13280000),
  ("nof_db_files",          340),
  ("fsize_db",              798948554766),
  ("xsection",              0.2529),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 798.95GB; nevents: 13.28M; release: 10_2_5; last modified: 2019-01-22 22:30:24"),
])

meta_dictionary["/TTZToLL_M-1to10_TuneCP5_13TeV-amcatnlo-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "TTZ"),
  ("process_name_specific", "TTZToLL_M-1to10"),
  ("nof_db_events",         250000),
  ("nof_db_files",          19),
  ("fsize_db",              15016634796),
  ("xsection",              0.05324),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 15.02GB; nevents: 250.00k; release: 10_2_6; last modified: 2018-12-25 10:32:56"),
])

meta_dictionary["/ttZJets_TuneCP5_13TeV_madgraphMLM_pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15_ext1-v2/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "TTZ"),
  ("process_name_specific", "TTZJets_LO_ext1"),
  ("nof_db_events",         22646257),
  ("nof_db_files",          632),
  ("fsize_db",              1397818296718),
  ("xsection",              0.8393),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 1.40TB; nevents: 22.65M; release: 10_2_5; last modified: 2019-01-22 17:25:45"),
])

meta_dictionary["/TTWJetsToLNu_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15_ext1-v2/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "TTW"),
  ("process_name_specific", "TTWJetsToLNu_ext1"),
  ("nof_db_events",         4911941),
  ("nof_db_files",          149),
  ("fsize_db",              298983454636),
  ("xsection",              0.2043),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 298.98GB; nevents: 4.91M; release: 10_2_5; last modified: 2019-01-12 00:25:10"),
])

meta_dictionary["/ttWJets_TuneCP5_13TeV_madgraphMLM_pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15_ext1-v2/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "TTW"),
  ("process_name_specific", "TTWJets_LO_ext1"),
  ("nof_db_events",         12816567),
  ("nof_db_files",          374),
  ("fsize_db",              780624312046),
  ("xsection",              0.6008),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 780.62GB; nevents: 12.82M; release: 10_2_5; last modified: 2019-01-22 16:51:53"),
])

meta_dictionary["/TTWW_TuneCP5_13TeV-madgraph-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15_ext1-v2/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "TTWW"),
  ("process_name_specific", "TTWW_ext1"),
  ("nof_db_events",         185000),
  ("nof_db_files",          13),
  ("fsize_db",              12337520794),
  ("xsection",              0.006983),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 12.34GB; nevents: 185.00k; release: 10_2_5; last modified: 2019-01-11 22:20:59"),
])

meta_dictionary["/TTWW_TuneCP5_13TeV-madgraph-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15_ext2-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "TTWW"),
  ("process_name_specific", "TTWW_ext2"),
  ("nof_db_events",         800000),
  ("nof_db_files",          27),
  ("fsize_db",              52851826665),
  ("xsection",              0.006983),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 52.85GB; nevents: 800.00k; release: 10_2_5; last modified: 2019-02-08 08:52:33"),
])

meta_dictionary["/ST_s-channel_4f_leptonDecays_TuneCP5_13TeV-madgraph-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15_ext1-v4/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "TT"),
  ("process_name_specific", "ST_s-channel_4f_leptonDecays_ext1"),
  ("nof_db_events",         19952000),
  ("nof_db_files",          353),
  ("fsize_db",              914449200019),
  ("xsection",              3.36),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 914.45GB; nevents: 19.95M; release: 10_2_5; last modified: 2019-01-22 19:34:12"),
])

meta_dictionary["/ST_t-channel_antitop_4f_InclusiveDecays_TuneCP5_13TeV-powheg-madspin-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "TT"),
  ("process_name_specific", "ST_t-channel_antitop_4f_inclusiveDecays"),
  ("nof_db_events",         79090800),
  ("nof_db_files",          1319),
  ("fsize_db",              3668166205835),
  ("xsection",              80.95),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 3.67TB; nevents: 79.09M; release: 10_2_6; last modified: 2019-02-16 00:45:33"),
])

meta_dictionary["/ST_t-channel_top_4f_InclusiveDecays_TuneCP5_13TeV-powheg-madspin-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "TT"),
  ("process_name_specific", "ST_t-channel_top_4f_inclusiveDecays"),
  ("nof_db_events",         154307600),
  ("nof_db_files",          2395),
  ("fsize_db",              7123325826717),
  ("xsection",              136.02),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 7.12TB; nevents: 154.31M; release: 10_2_6; last modified: 2019-02-25 23:37:27"),
])

meta_dictionary["/ST_tW_antitop_5f_inclusiveDecays_TuneCP5_13TeV-powheg-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15_ext1-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "TT"),
  ("process_name_specific", "ST_tW_antitop_5f_inclusiveDecays_ext1"),
  ("nof_db_events",         7623000),
  ("nof_db_files",          160),
  ("fsize_db",              387298031075),
  ("xsection",              35.85),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 387.30GB; nevents: 7.62M; release: 10_2_6; last modified: 2019-01-02 22:17:32"),
])

meta_dictionary["/ST_tW_top_5f_inclusiveDecays_TuneCP5_13TeV-powheg-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15_ext1-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "TT"),
  ("process_name_specific", "ST_tW_top_5f_inclusiveDecays_ext1"),
  ("nof_db_events",         9598000),
  ("nof_db_files",          173),
  ("fsize_db",              487035275580),
  ("xsection",              35.85),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 487.04GB; nevents: 9.60M; release: 10_2_6; last modified: 2018-12-31 18:00:25"),
])

meta_dictionary["/ST_tWll_5f_LO_TuneCP5_PSweights_13TeV-madgraph-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15_ext1-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "TT"),
  ("process_name_specific", "ST_tWll_PSweights_ext1"),
  ("nof_db_events",         248600),
  ("nof_db_files",          21),
  ("fsize_db",              15676809884),
  ("xsection",              0.01103),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 15.68GB; nevents: 248.60k; release: 10_2_5; last modified: 2018-12-27 13:35:45"),
])

meta_dictionary["/TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "TT"),
  ("process_name_specific", "TTTo2L2Nu"),
  ("nof_db_events",         64310000),
  ("nof_db_files",          968),
  ("fsize_db",              3413760837047),
  ("xsection",              88.29),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 3.41TB; nevents: 64.31M; release: 10_2_5; last modified: 2018-11-21 18:44:43"),
])

meta_dictionary["/TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "TT"),
  ("process_name_specific", "TTToSemiLeptonic"),
  ("nof_db_events",         101550000),
  ("nof_db_files",          1523),
  ("fsize_db",              5446585250527),
  ("xsection",              365.34),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 5.45TB; nevents: 101.55M; release: 10_2_6; last modified: 2019-01-22 14:22:10"),
])

meta_dictionary["/TTToHadronic_TuneCP5_13TeV-powheg-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "TT"),
  ("process_name_specific", "TTToHadronic"),
  ("nof_db_events",         133808000),
  ("nof_db_files",          3313),
  ("fsize_db",              7273064972485),
  ("xsection",              377.96),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 7.27TB; nevents: 133.81M; release: 10_2_5; last modified: 2018-11-27 22:36:52"),
])

meta_dictionary["/TTJets_DiLept_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "TT"),
  ("process_name_specific", "TTJets_DiLept"),
  ("nof_db_events",         28701360),
  ("nof_db_files",          841),
  ("fsize_db",              1591205272331),
  ("xsection",              88.29),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 1.59TB; nevents: 28.70M; release: 10_2_5; last modified: 2019-03-05 07:07:19"),
])

meta_dictionary["/TTJets_SingleLeptFromT_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "TT"),
  ("process_name_specific", "TTJets_SingleLeptFromT"),
  ("nof_db_events",         61658409),
  ("nof_db_files",          1607),
  ("fsize_db",              3396470873673),
  ("xsection",              182.67),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 3.40TB; nevents: 61.66M; release: 10_2_5; last modified: 2019-03-18 20:03:54"),
])

meta_dictionary["/TTJets_SingleLeptFromTbar_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "TT"),
  ("process_name_specific", "TTJets_SingleLeptFromTbar"),
  ("nof_db_events",         59929205),
  ("nof_db_files",          1540),
  ("fsize_db",              3384871119793),
  ("xsection",              182.67),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 3.38TB; nevents: 59.93M; release: 10_2_5; last modified: 2019-02-13 04:50:04"),
])

meta_dictionary["/TTJets_TuneCP5_13TeV-amcatnloFXFX-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15_ext1-v2/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "TT"),
  ("process_name_specific", "TTJets_amcatnloFXFX_ext1"),
  ("nof_db_events",         142155064),
  ("nof_db_files",          3485),
  ("fsize_db",              7849430055124),
  ("xsection",              831.76),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 7.85TB; nevents: 142.16M; release: 10_2_5; last modified: 2019-03-04 16:58:48"),
])

meta_dictionary["/TTJets_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "TT"),
  ("process_name_specific", "TTJets_madgraphMLM"),
  ("nof_db_events",         10244307),
  ("nof_db_files",          309),
  ("fsize_db",              569352569399),
  ("xsection",              831.76),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 569.35GB; nevents: 10.24M; release: 10_2_5; last modified: 2019-02-15 13:47:42"),
])

meta_dictionary["/WWW_4F_TuneCP5_13TeV-amcatnlo-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15_ext1-v2/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "Rares"),
  ("process_name_specific", "WWW_ext1"),
  ("nof_db_events",         240000),
  ("nof_db_files",          12),
  ("fsize_db",              12122543635),
  ("xsection",              0.2086),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 12.12GB; nevents: 240.00k; release: 10_2_5; last modified: 2019-01-12 02:44:07"),
])

meta_dictionary["/WWZ_TuneCP5_13TeV-amcatnlo-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15_ext1-v2/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "Rares"),
  ("process_name_specific", "WWZ_ext1"),
  ("nof_db_events",         250000),
  ("nof_db_files",          15),
  ("fsize_db",              12987521478),
  ("xsection",              0.1651),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 12.99GB; nevents: 250.00k; release: 10_2_5; last modified: 2018-12-10 16:42:04"),
])

meta_dictionary["/WZZ_TuneCP5_13TeV-amcatnlo-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15_ext1-v2/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "Rares"),
  ("process_name_specific", "WZZ_ext1"),
  ("nof_db_events",         250000),
  ("nof_db_files",          14),
  ("fsize_db",              13168809687),
  ("xsection",              0.05565),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 13.17GB; nevents: 250.00k; release: 10_2_5; last modified: 2018-12-10 23:51:20"),
])

meta_dictionary["/ZZZ_TuneCP5_13TeV-amcatnlo-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15_ext1-v2/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "Rares"),
  ("process_name_specific", "ZZZ_ext1"),
  ("nof_db_events",         250000),
  ("nof_db_files",          14),
  ("fsize_db",              12595171655),
  ("xsection",              0.01398),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 12.60GB; nevents: 250.00k; release: 10_2_5; last modified: 2018-12-09 06:06:47"),
])

meta_dictionary["/WZG_TuneCP5_13TeV-amcatnlo-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "Rares"),
  ("process_name_specific", "WZG"),
  ("nof_db_events",         1960000),
  ("nof_db_files",          47),
  ("fsize_db",              99260714863),
  ("xsection",              0.04123),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 99.26GB; nevents: 1.96M; release: 10_2_6; last modified: 2018-12-25 18:59:54"),
])

meta_dictionary["/WGToLNuG_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "Rares"),
  ("process_name_specific", "WGToLNuG"),
  ("nof_db_events",         6108186),
  ("nof_db_files",          117),
  ("fsize_db",              247084202479),
  ("xsection",              405.271),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 247.08GB; nevents: 6.11M; release: 10_2_6; last modified: 2019-02-02 00:09:50"),
])

meta_dictionary["/ZGToLLG_01J_5f_TuneCP5_13TeV-amcatnloFXFX-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15_ext1-v2/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "Rares"),
  ("process_name_specific", "ZGTo2LG_ext1"),
  ("nof_db_events",         13946364),
  ("nof_db_files",          266),
  ("fsize_db",              596900709674),
  ("xsection",              117.864),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 596.90GB; nevents: 13.95M; release: 10_2_5; last modified: 2018-12-22 09:26:10"),
])

meta_dictionary["/TGJets_TuneCP5_13TeV_amcatnlo_madspin_pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v3/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "Rares"),
  ("process_name_specific", "TGJets"),
  ("nof_db_events",         2000000),
  ("nof_db_files",          64),
  ("fsize_db",              100429060186),
  ("xsection",              2.967),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: PRODUCTION; size: 100.43GB; nevents: 2.00M; release: 10_2_5; last modified: 2019-03-03 05:06:50"),
])

meta_dictionary["/TTGJets_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "Rares"),
  ("process_name_specific", "TTGJets"),
  ("nof_db_events",         4691915),
  ("nof_db_files",          133),
  ("fsize_db",              279233368180),
  ("xsection",              3.697),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 279.23GB; nevents: 4.69M; release: 10_2_5; last modified: 2019-02-02 00:24:03"),
])

meta_dictionary["/GluGluHToTauTau_M125_13TeV_powheg_pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v2/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "Rares"),
  ("process_name_specific", "GluGluHToTauTau"),
  ("nof_db_events",         12575000),
  ("nof_db_files",          188),
  ("fsize_db",              515475856207),
  ("xsection",              3.0469),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 515.48GB; nevents: 12.57M; release: 10_2_5; last modified: 2018-11-24 09:41:05"),
])

meta_dictionary["/VBFHToTauTau_M125_13TeV_powheg_pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15_ext1-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "Rares"),
  ("process_name_specific", "VBFHToTauTau_ext1"),
  ("nof_db_events",         3000000),
  ("nof_db_files",          72),
  ("fsize_db",              133643341940),
  ("xsection",              0.2372),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 133.64GB; nevents: 3.00M; release: 10_2_6; last modified: 2018-11-27 14:00:45"),
])

meta_dictionary["/tZq_ll_4f_ckm_NLO_TuneCP5_13TeV-madgraph-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15_ext1-v2/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "Rares"),
  ("process_name_specific", "tZq_ll_4f_ext1"),
  ("nof_db_events",         13736000),
  ("nof_db_files",          382),
  ("fsize_db",              775261524542),
  ("xsection",              0.0758),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 775.26GB; nevents: 13.74M; release: 10_2_5; last modified: 2019-01-14 16:46:51"),
])

meta_dictionary["/WpWpJJ_EWK-QCD_TuneCP5_13TeV-madgraph-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "Rares"),
  ("process_name_specific", "WpWpJJ_EWK_QCD"),
  ("nof_db_events",         150000),
  ("nof_db_files",          10),
  ("fsize_db",              8416160335),
  ("xsection",              0.04932),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 8.42GB; nevents: 150.00k; release: 10_2_6; last modified: 2018-12-30 23:28:28"),
])

meta_dictionary["/WWTo2L2Nu_DoubleScattering_13TeV-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "Rares"),
  ("process_name_specific", "WWTo2L2Nu_DoubleScattering"),
  ("nof_db_events",         871500),
  ("nof_db_files",          49),
  ("fsize_db",              35977937003),
  ("xsection",              0.1743),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 35.98GB; nevents: 871.50k; release: 10_2_6; last modified: 2019-01-29 02:52:02"),
])

meta_dictionary["/TTTT_TuneCP5_13TeV-amcatnlo-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15_ext1-v2/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "Rares"),
  ("process_name_specific", "TTTT_ext1"),
  ("nof_db_events",         2359420),
  ("nof_db_files",          98),
  ("fsize_db",              184341115381),
  ("xsection",              0.008213),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 184.34GB; nevents: 2.36M; release: 10_2_5; last modified: 2019-02-05 03:54:38"),
])

meta_dictionary["/TTWH_TuneCP5_13TeV-madgraph-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15_ext1-v2/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "Rares"),
  ("process_name_specific", "TTWH_ext1"),
  ("nof_db_events",         200000),
  ("nof_db_files",          13),
  ("fsize_db",              13560607150),
  ("xsection",              0.001141),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 13.56GB; nevents: 200.00k; release: 10_2_5; last modified: 2019-01-12 03:51:39"),
])

meta_dictionary["/TTZH_TuneCP5_13TeV-madgraph-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15_ext1-v2/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "Rares"),
  ("process_name_specific", "TTZH_ext1"),
  ("nof_db_events",         200000),
  ("nof_db_files",          15),
  ("fsize_db",              13899288356),
  ("xsection",              0.001131),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 13.90GB; nevents: 200.00k; release: 10_2_5; last modified: 2019-02-10 05:34:11"),
])

meta_dictionary["/TTTW_TuneCP5_13TeV-madgraph-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15_ext1-v2/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "Rares"),
  ("process_name_specific", "TTTW_ext1"),
  ("nof_db_events",         200000),
  ("nof_db_files",          14),
  ("fsize_db",              14488761312),
  ("xsection",              0.0007317),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 14.49GB; nevents: 200.00k; release: 10_2_5; last modified: 2019-01-12 03:26:25"),
])

meta_dictionary["/TTTJ_TuneCP5_13TeV-madgraph-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15_ext1-v2/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "Rares"),
  ("process_name_specific", "TTTJ_ext1"),
  ("nof_db_events",         184000),
  ("nof_db_files",          13),
  ("fsize_db",              12835341800),
  ("xsection",              0.0003973),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 12.84GB; nevents: 184.00k; release: 10_2_5; last modified: 2019-01-12 04:30:58"),
])

meta_dictionary["/TTWZ_TuneCP5_13TeV-madgraph-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15_ext1-v2/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "Rares"),
  ("process_name_specific", "TTWZ_ext1"),
  ("nof_db_events",         200000),
  ("nof_db_files",          10),
  ("fsize_db",              13169455329),
  ("xsection",              0.002441),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 13.17GB; nevents: 200.00k; release: 10_2_5; last modified: 2018-12-10 23:57:59"),
])

meta_dictionary["/TTZZ_TuneCP5_13TeV-madgraph-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15_ext1-v2/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "Rares"),
  ("process_name_specific", "TTZZ_ext1"),
  ("nof_db_events",         200000),
  ("nof_db_files",          13),
  ("fsize_db",              13292793715),
  ("xsection",              0.001386),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 13.29GB; nevents: 200.00k; release: 10_2_5; last modified: 2018-12-18 15:55:40"),
])

meta_dictionary["/VHToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v2/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "VH"),
  ("process_name_specific", "VHToNonbb_M125"),
  ("nof_db_events",         1102578),
  ("nof_db_files",          30),
  ("fsize_db",              51922787567),
  ("xsection",              0.9425),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 51.92GB; nevents: 1.10M; release: 10_2_6; last modified: 2018-12-17 02:27:28"),
])

meta_dictionary["/ZH_HToBB_ZToLL_M125_13TeV_powheg_pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v2/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "VH"),
  ("process_name_specific", "ZH_HToBB_ZToLL"),
  ("nof_db_events",         4814600),
  ("nof_db_files",          171),
  ("fsize_db",              246564660597),
  ("xsection",              0.05198),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 246.56GB; nevents: 4.81M; release: 10_2_5; last modified: 2018-12-14 08:20:58"),
])

meta_dictionary["/ZH_HToBB_ZToLL_M125_13TeV_powheg_pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15_ext1-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "VH"),
  ("process_name_specific", "ZH_HToBB_ZToLL_ext1"),
  ("nof_db_events",         2222100),
  ("nof_db_files",          108),
  ("fsize_db",              114249380345),
  ("xsection",              0.05198),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 114.25GB; nevents: 2.22M; release: 10_2_5; last modified: 2019-02-28 20:56:01"),
])

meta_dictionary["/ZHToTauTau_M125_13TeV_powheg_pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v2/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "VH"),
  ("process_name_specific", "ZHToTauTau"),
  ("nof_db_events",         4761815),
  ("nof_db_files",          163),
  ("fsize_db",              222037043876),
  ("xsection",              0.05544),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 222.04GB; nevents: 4.76M; release: 10_2_5; last modified: 2018-12-29 13:46:09"),
])

meta_dictionary["/DYJetsToLL_M-10to50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v2/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DYJetsToLL_M-10to50"),
  ("nof_db_events",         39392062),
  ("nof_db_files",          569),
  ("fsize_db",              1384328487602),
  ("xsection",              18610.0),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 1.38TB; nevents: 39.39M; release: 10_2_5; last modified: 2018-12-20 18:51:21"),
])

meta_dictionary["/DYJetsToLL_M-4to50_HT-70to100_TuneCP5_PSweights_13TeV-madgraphMLM-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DYJetsToLL_M-4to50_HT-70to100_PSweights"),
  ("nof_db_events",         9048204),
  ("nof_db_files",          254),
  ("fsize_db",              413835231519),
  ("xsection",              145.5),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 413.84GB; nevents: 9.05M; release: 10_2_5; last modified: 2019-04-21 19:40:05"),
])

meta_dictionary["/DYJetsToLL_M-4to50_HT-100to200_TuneCP5_PSweights_13TeV-madgraphMLM-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DYJetsToLL_M-4to50_HT-100to200_PSweights"),
  ("nof_db_events",         9018837),
  ("nof_db_files",          258),
  ("fsize_db",              396566011694),
  ("xsection",              239.63),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 396.57GB; nevents: 9.02M; release: 10_2_5; last modified: 2019-04-15 18:15:29"),
])

meta_dictionary["/DYJetsToLL_M-4to50_HT-200to400_TuneCP5_PSweights_13TeV-madgraphMLM-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DYJetsToLL_M-4to50_HT-200to400_PSweights"),
  ("nof_db_events",         1939010),
  ("nof_db_files",          76),
  ("fsize_db",              93803281281),
  ("xsection",              63.79),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 93.80GB; nevents: 1.94M; release: 10_2_5; last modified: 2019-03-20 23:53:58"),
])

meta_dictionary["/DYJetsToLL_M-4to50_HT-400to600_TuneCP5_PSweights_13TeV-madgraphMLM-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DYJetsToLL_M-4to50_HT-400to600_PSweights"),
  ("nof_db_events",         2008779),
  ("nof_db_files",          95),
  ("fsize_db",              109073531454),
  ("xsection",              6.726),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 109.07GB; nevents: 2.01M; release: 10_2_5; last modified: 2019-03-17 20:41:20"),
])

meta_dictionary["/DYJetsToLL_M-4to50_HT-600toInf_TuneCP5_PSWeights_13TeV-madgraphMLM-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DYJetsToLL_M-4to50_HT-600toInf_PSWeights"),
  ("nof_db_events",         1975490),
  ("nof_db_files",          102),
  ("fsize_db",              117216307528),
  ("xsection",              2.172),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 117.22GB; nevents: 1.98M; release: 10_2_5; last modified: 2019-03-16 18:41:58"),
])

meta_dictionary["/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DYJetsToLL_M-50"),
  ("nof_db_events",         100194597),
  ("nof_db_files",          1254),
  ("fsize_db",              4107561163369),
  ("xsection",              5765.4),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 4.11TB; nevents: 100.19M; release: 10_2_5; last modified: 2018-12-09 11:55:28"),
])

meta_dictionary["/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DYJetsToLL_M-50_amcatnloFXFX"),
  ("nof_db_events",         997561),
  ("nof_db_files",          15),
  ("fsize_db",              40601589470),
  ("xsection",              5765.4),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 40.60GB; nevents: 997.56k; release: 10_2_5; last modified: 2018-12-02 12:42:42"),
])

meta_dictionary["/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15_ext2-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DYJetsToLL_M-50_amcatnloFXFX_ext2"),
  ("nof_db_events",         138995244),
  ("nof_db_files",          1810),
  ("fsize_db",              5647403099996),
  ("xsection",              5765.4),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "status: PRODUCTION; size: 5.65TB; nevents: 139.00M; release: 10_2_5; last modified: 2019-04-24 12:49:19"),
])

meta_dictionary["/DY1JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v2/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DY1JetsToLL_M-50"),
  ("nof_db_events",         68898175),
  ("nof_db_files",          977),
  ("fsize_db",              2932072952401),
  ("xsection",              945.24),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 2.93TB; nevents: 68.90M; release: 10_2_5; last modified: 2018-12-04 22:48:52"),
])

meta_dictionary["/DY2JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v2/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DY2JetsToLL_M-50"),
  ("nof_db_events",         20456037),
  ("nof_db_files",          326),
  ("fsize_db",              941788605215),
  ("xsection",              330.99),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 941.79GB; nevents: 20.46M; release: 10_2_5; last modified: 2018-11-20 20:54:51"),
])

meta_dictionary["/DY3JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v2/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DY3JetsToLL_M-50"),
  ("nof_db_events",         5652357),
  ("nof_db_files",          113),
  ("fsize_db",              270141096577),
  ("xsection",              120.72),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 270.14GB; nevents: 5.65M; release: 10_2_5; last modified: 2018-11-30 01:48:40"),
])

meta_dictionary["/DY4JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DY4JetsToLL_M-50"),
  ("nof_db_events",         2817812),
  ("nof_db_files",          184),
  ("fsize_db",              150363439120),
  ("xsection",              47.47),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 150.36GB; nevents: 2.82M; release: 10_2_5; last modified: 2019-02-02 00:08:46"),
])

meta_dictionary["/DYJetsToLL_M-50_HT-70to100_TuneCP5_PSweights_13TeV-madgraphMLM-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DYJetsToLL_M50_HT70to100_PSweights"),
  ("nof_db_events",         10019684),
  ("nof_db_files",          237),
  ("fsize_db",              458054839968),
  ("xsection",              158.49),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 458.05GB; nevents: 10.02M; release: 10_2_5; last modified: 2019-02-10 16:38:23"),
])

meta_dictionary["/DYJetsToLL_M-50_HT-100to200_TuneCP5_PSweights_13TeV-madgraphMLM-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v2/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DYJetsToLL_M50_HT100to200_PSweights"),
  ("nof_db_events",         11530510),
  ("nof_db_files",          232),
  ("fsize_db",              555247647975),
  ("xsection",              173.53),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 555.25GB; nevents: 11.53M; release: 10_2_5; last modified: 2019-01-13 04:55:05"),
])

meta_dictionary["/DYJetsToLL_M-50_HT-200to400_TuneCP5_PSweights_13TeV-madgraphMLM-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v2/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DYJetsToLL_M50_HT200to400_PSweights"),
  ("nof_db_events",         11225887),
  ("nof_db_files",          311),
  ("fsize_db",              602756696070),
  ("xsection",              53.0),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 602.76GB; nevents: 11.23M; release: 10_2_5; last modified: 2019-01-22 17:31:09"),
])

meta_dictionary["/DYJetsToLL_M-50_HT-400to600_TuneCP5_PSweights_13TeV-madgraphMLM-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v7/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DYJetsToLL_M50_HT400to600_PSweights"),
  ("nof_db_events",         9697098),
  ("nof_db_files",          249),
  ("fsize_db",              564664803510),
  ("xsection",              7.539),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 564.66GB; nevents: 9.70M; release: 10_2_5; last modified: 2019-02-14 23:55:34"),
])

meta_dictionary["/DYJetsToLL_M-50_HT-400to600_TuneCP5_PSweights_13TeV-madgraphMLM-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15_ext2-v3/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DYJetsToLL_M50_HT400to600_PSweights_ext2"),
  ("nof_db_events",         9358053),
  ("nof_db_files",          253),
  ("fsize_db",              546455118878),
  ("xsection",              7.539),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 546.46GB; nevents: 9.36M; release: 10_2_5; last modified: 2019-04-02 17:46:45"),
])

meta_dictionary["/DYJetsToLL_M-50_HT-600to800_TuneCP5_PSweights_13TeV-madgraphMLM-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v2/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DYJetsToLL_M50_HT600to800_PSweights"),
  ("nof_db_events",         8862104),
  ("nof_db_files",          264),
  ("fsize_db",              542689599939),
  ("xsection",              1.8815),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 542.69GB; nevents: 8.86M; release: 10_2_5; last modified: 2019-02-03 01:31:55"),
])

meta_dictionary["/DYJetsToLL_M-50_HT-800to1200_TuneCP5_PSweights_13TeV-madgraphMLM-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v2/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DYJetsToLL_M50_HT800to1200_PSweights"),
  ("nof_db_events",         3138129),
  ("nof_db_files",          109),
  ("fsize_db",              201483591965),
  ("xsection",              0.8684),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 201.48GB; nevents: 3.14M; release: 10_2_5; last modified: 2019-01-20 16:23:19"),
])

meta_dictionary["/DYJetsToLL_M-50_HT-1200to2500_TuneCP5_PSweights_13TeV-madgraphMLM-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v2/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DYJetsToLL_M50_HT1200to2500_PSweights"),
  ("nof_db_events",         536416),
  ("nof_db_files",          23),
  ("fsize_db",              36172277071),
  ("xsection",              0.2079),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 36.17GB; nevents: 536.42k; release: 10_2_5; last modified: 2019-04-17 17:30:59"),
])

meta_dictionary["/DYJetsToLL_M-50_HT-2500toInf_TuneCP5_PSweights_13TeV-madgraphMLM-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v2/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DYJetsToLL_M50_HT2500toInf_PSweights"),
  ("nof_db_events",         427051),
  ("nof_db_files",          23),
  ("fsize_db",              31050128812),
  ("xsection",              0.003749),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 31.05GB; nevents: 427.05k; release: 10_2_5; last modified: 2019-02-22 03:36:04"),
])

meta_dictionary["/DYBBJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DYBBJetsToLL_M-50"),
  ("nof_db_events",         5158752),
  ("nof_db_files",          159),
  ("fsize_db",              256525597601),
  ("xsection",              14.59),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 256.53GB; nevents: 5.16M; release: 10_2_5; last modified: 2019-03-17 15:51:17"),
])

meta_dictionary["/WJetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v2/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "WJetsToLNu_madgraphMLM"),
  ("nof_db_events",         71072199),
  ("nof_db_files",          991),
  ("fsize_db",              2702061580245),
  ("xsection",              61526.7),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 2.70TB; nevents: 71.07M; release: 10_2_5; last modified: 2019-03-29 04:44:33"),
])

meta_dictionary["/W1JetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v2/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "W1JetsToLNu"),
  ("nof_db_events",         51082776),
  ("nof_db_files",          743),
  ("fsize_db",              2020854019765),
  ("xsection",              9418.44),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 2.02TB; nevents: 51.08M; release: 10_2_5; last modified: 2019-01-17 23:06:16"),
])

meta_dictionary["/W2JetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v2/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "W2JetsToLNu"),
  ("nof_db_events",         23290710),
  ("nof_db_files",          335),
  ("fsize_db",              984065647389),
  ("xsection",              3244.85),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 984.07GB; nevents: 23.29M; release: 10_2_5; last modified: 2018-11-20 01:32:33"),
])

meta_dictionary["/W3JetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v2/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "W3JetsToLNu"),
  ("nof_db_events",         14508481),
  ("nof_db_files",          300),
  ("fsize_db",              644377549776),
  ("xsection",              1153.02),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 644.38GB; nevents: 14.51M; release: 10_2_5; last modified: 2019-01-02 11:19:40"),
])

meta_dictionary["/W4JetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v2/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "W4JetsToLNu"),
  ("nof_db_events",         10082747),
  ("nof_db_files",          205),
  ("fsize_db",              488503593741),
  ("xsection",              633.05),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 488.50GB; nevents: 10.08M; release: 10_2_5; last modified: 2018-12-15 03:01:37"),
])

meta_dictionary["/WJetsToLNu_HT-70To100_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "WJetsToLNu_HT70To100"),
  ("nof_db_events",         28084244),
  ("nof_db_files",          514),
  ("fsize_db",              1190218725712),
  ("xsection",              1502.72),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 1.19TB; nevents: 28.08M; release: 10_2_5; last modified: 2019-02-10 21:29:02"),
])

meta_dictionary["/WJetsToLNu_HT-100To200_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "WJetsToLNu_HT100To200"),
  ("nof_db_events",         29611903),
  ("nof_db_files",          563),
  ("fsize_db",              1320629640223),
  ("xsection",              1625.94),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 1.32TB; nevents: 29.61M; release: 10_2_5; last modified: 2019-02-13 04:48:10"),
])

meta_dictionary["/WJetsToLNu_HT-200To400_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "WJetsToLNu_HT200To400"),
  ("nof_db_events",         25468933),
  ("nof_db_files",          522),
  ("fsize_db",              1257184919296),
  ("xsection",              477.52),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 1.26TB; nevents: 25.47M; release: 10_2_5; last modified: 2019-02-12 17:53:40"),
])

meta_dictionary["/WJetsToLNu_HT-400To600_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "WJetsToLNu_HT400To600"),
  ("nof_db_events",         5932701),
  ("nof_db_files",          239),
  ("fsize_db",              321067288953),
  ("xsection",              67.51),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 321.07GB; nevents: 5.93M; release: 10_2_5; last modified: 2019-01-29 02:01:26"),
])

meta_dictionary["/WJetsToLNu_HT-600To800_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "WJetsToLNu_HT600To800"),
  ("nof_db_events",         19771294),
  ("nof_db_files",          595),
  ("fsize_db",              1134386104465),
  ("xsection",              15.09),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 1.13TB; nevents: 19.77M; release: 10_2_5; last modified: 2019-02-18 15:16:42"),
])

meta_dictionary["/WJetsToLNu_HT-800To1200_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "WJetsToLNu_HT800To1200"),
  ("nof_db_events",         8402687),
  ("nof_db_files",          327),
  ("fsize_db",              504255756512),
  ("xsection",              6.297),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 504.26GB; nevents: 8.40M; release: 10_2_5; last modified: 2019-02-12 17:54:55"),
])

meta_dictionary["/WJetsToLNu_HT-1200To2500_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "WJetsToLNu_HT1200To2500"),
  ("nof_db_events",         7633949),
  ("nof_db_files",          299),
  ("fsize_db",              483917567475),
  ("xsection",              1.262),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 483.92GB; nevents: 7.63M; release: 10_2_5; last modified: 2019-02-25 18:42:07"),
])

meta_dictionary["/WJetsToLNu_HT-2500ToInf_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "WJetsToLNu_HT2500ToInf"),
  ("nof_db_events",         3273980),
  ("nof_db_files",          132),
  ("fsize_db",              225211195235),
  ("xsection",              0.009446),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 225.21GB; nevents: 3.27M; release: 10_2_5; last modified: 2019-02-01 23:47:28"),
])

meta_dictionary["/WWTo2L2Nu_NNPDF31_TuneCP5_13TeV-powheg-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "WWTo2L2Nu"),
  ("nof_db_events",         7758900),
  ("nof_db_files",          176),
  ("fsize_db",              329888556817),
  ("xsection",              12.178),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 329.89GB; nevents: 7.76M; release: 10_2_5; last modified: 2019-03-16 07:58:27"),
])

meta_dictionary["/WWToLNuQQ_NNPDF31_TuneCP5_13TeV-powheg-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "WWToLNuQQ"),
  ("nof_db_events",         19199100),
  ("nof_db_files",          368),
  ("fsize_db",              833728084007),
  ("xsection",              49.997),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 833.73GB; nevents: 19.20M; release: 10_2_5; last modified: 2019-03-20 00:42:50"),
])

meta_dictionary["/WWTo1L1Nu2Q_13TeV_amcatnloFXFX_madspin_pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "WWTo1L1Nu2Q"),
  ("nof_db_events",         4683136),
  ("nof_db_files",          97),
  ("fsize_db",              202725181402),
  ("xsection",              49.997),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 202.73GB; nevents: 4.68M; release: 10_2_5; last modified: 2019-03-20 10:14:33"),
])

meta_dictionary["/WWTo4Q_NNPDF31_TuneCP5_13TeV-powheg-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "WWTo4Q"),
  ("nof_db_events",         3808800),
  ("nof_db_files",          110),
  ("fsize_db",              167149037630),
  ("xsection",              53.923),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 167.15GB; nevents: 3.81M; release: 10_2_5; last modified: 2019-03-16 15:54:15"),
])

meta_dictionary["/WZTo3LNu_TuneCP5_13TeV-amcatnloFXFX-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "WZTo3LNu"),
  ("nof_db_events",         10749269),
  ("nof_db_files",          280),
  ("fsize_db",              465840197517),
  ("xsection",              4.42965),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 465.84GB; nevents: 10.75M; release: 10_2_6; last modified: 2019-03-07 19:57:50"),
])

meta_dictionary["/WZTo3LNu_TuneCP5_13TeV-amcatnloFXFX-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15_ext1-v2/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "WZTo3LNu_ext1"),
  ("nof_db_events",         11248318),
  ("nof_db_files",          206),
  ("fsize_db",              486637376419),
  ("xsection",              4.42965),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 486.64GB; nevents: 11.25M; release: 10_2_5; last modified: 2019-01-11 20:43:05"),
])

meta_dictionary["/WZTo3LNu_TuneCP5_13TeV-powheg-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15_ext1-v2/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "WZTo3LNu_powheg_ext1"),
  ("nof_db_events",         1976600),
  ("nof_db_files",          63),
  ("fsize_db",              83819106118),
  ("xsection",              4.42965),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 83.82GB; nevents: 1.98M; release: 10_2_5; last modified: 2019-01-16 17:19:13"),
])

meta_dictionary["/WZTo3LNu_0Jets_MLL-4to50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v2/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "WZTo3LNu_0Jets_MLL-4to50"),
  ("nof_db_events",         549864),
  ("nof_db_files",          21),
  ("fsize_db",              23763774844),
  ("xsection",              2.508),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 23.76GB; nevents: 549.86k; release: 10_2_5; last modified: 2019-01-14 18:19:42"),
])

meta_dictionary["/WZTo3LNu_0Jets_MLL-50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v2/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "WZTo3LNu_0Jets_MLL-50"),
  ("nof_db_events",         496707),
  ("nof_db_files",          33),
  ("fsize_db",              24329724502),
  ("xsection",              0.638),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 24.33GB; nevents: 496.71k; release: 10_2_5; last modified: 2019-01-14 19:04:52"),
])

meta_dictionary["/WZTo3LNu_1Jets_MLL-4to50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v2/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "WZTo3LNu_1Jets_MLL-4to50"),
  ("nof_db_events",         565620),
  ("nof_db_files",          41),
  ("fsize_db",              26462658315),
  ("xsection",              0.4868),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 26.46GB; nevents: 565.62k; release: 10_2_5; last modified: 2019-02-02 00:02:28"),
])

meta_dictionary["/WZTo3LNu_1Jets_MLL-50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v2/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "WZTo3LNu_1Jets_MLL-50"),
  ("nof_db_events",         497831),
  ("nof_db_files",          28),
  ("fsize_db",              26295965016),
  ("xsection",              0.3389),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 26.30GB; nevents: 497.83k; release: 10_2_5; last modified: 2019-02-02 05:34:10"),
])

meta_dictionary["/WZTo3LNu_2Jets_MLL-4to50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v2/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "WZTo3LNu_2Jets_MLL-4to50"),
  ("nof_db_events",         1409762),
  ("nof_db_files",          62),
  ("fsize_db",              71473530181),
  ("xsection",              0.164),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 71.47GB; nevents: 1.41M; release: 10_2_5; last modified: 2019-03-10 23:02:07"),
])

meta_dictionary["/WZTo3LNu_2Jets_MLL-50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v2/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "WZTo3LNu_2Jets_MLL-50"),
  ("nof_db_events",         1855668),
  ("nof_db_files",          96),
  ("fsize_db",              108440817033),
  ("xsection",              0.06645),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 108.44GB; nevents: 1.86M; release: 10_2_5; last modified: 2019-02-10 16:38:26"),
])

meta_dictionary["/WZTo3LNu_3Jets_MLL-4to50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v2/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "WZTo3LNu_3Jets_MLL-4to50"),
  ("nof_db_events",         2160519),
  ("nof_db_files",          93),
  ("fsize_db",              121018445179),
  ("xsection",              0.07121),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 121.02GB; nevents: 2.16M; release: 10_2_5; last modified: 2019-02-02 05:45:01"),
])

meta_dictionary["/WZTo3LNu_3Jets_MLL-50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v2/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "WZTo3LNu_3Jets_MLL-50"),
  ("nof_db_events",         1788755),
  ("nof_db_files",          77),
  ("fsize_db",              111719583774),
  ("xsection",              0.09521),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 111.72GB; nevents: 1.79M; release: 10_2_5; last modified: 2019-02-02 05:39:27"),
])

meta_dictionary["/WZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "WZTo2L2Q"),
  ("nof_db_events",         28193648),
  ("nof_db_files",          501),
  ("fsize_db",              1304463189799),
  ("xsection",              5.595),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 1.30TB; nevents: 28.19M; release: 10_2_5; last modified: 2019-03-10 11:49:08"),
])

meta_dictionary["/ZZTo4L_TuneCP5_13TeV_powheg_pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15_ext1-v2/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "ZZTo4L_ext1"),
  ("nof_db_events",         6689900),
  ("nof_db_files",          138),
  ("fsize_db",              278854571525),
  ("xsection",              1.256),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 278.85GB; nevents: 6.69M; release: 10_2_5; last modified: 2019-01-12 05:32:01"),
])

meta_dictionary["/ZZTo4L_TuneCP5_13TeV_powheg_pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15_ext2-v2/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "ZZTo4L_ext2"),
  ("nof_db_events",         99009000),
  ("nof_db_files",          1473),
  ("fsize_db",              4120965640479),
  ("xsection",              1.256),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 4.12TB; nevents: 99.01M; release: 10_2_5; last modified: 2019-03-13 09:29:50"),
])

meta_dictionary["/ZZTo2L2Nu_TuneCP5_13TeV_powheg_pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15_ext1-v2/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "ZZTo2L2Nu_ext1"),
  ("nof_db_events",         8382600),
  ("nof_db_files",          171),
  ("fsize_db",              362146384399),
  ("xsection",              0.564),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 362.15GB; nevents: 8.38M; release: 10_2_5; last modified: 2019-01-12 02:21:00"),
])

meta_dictionary["/ZZTo2L2Nu_TuneCP5_13TeV_powheg_pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15_ext2-v2/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "ZZTo2L2Nu_ext2"),
  ("nof_db_events",         48046000),
  ("nof_db_files",          842),
  ("fsize_db",              2074512868169),
  ("xsection",              0.564),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 2.07TB; nevents: 48.05M; release: 10_2_5; last modified: 2019-03-29 15:55:06"),
])

meta_dictionary["/ZZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "ZZTo2L2Q"),
  ("nof_db_events",         27900469),
  ("nof_db_files",          457),
  ("fsize_db",              1289685740970),
  ("xsection",              3.22),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 1.29TB; nevents: 27.90M; release: 10_2_5; last modified: 2019-02-25 18:47:59"),
])

meta_dictionary["/QCD_Pt-15to20_EMEnriched_TuneCP5_13TeV_pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15_ext1-v2/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "QCD"),
  ("process_name_specific", "QCD_Pt15to20_EMEnriched_ext1"),
  ("nof_db_events",         14578212),
  ("nof_db_files",          237),
  ("fsize_db",              515168303338),
  ("xsection",              1324000.0),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 515.17GB; nevents: 14.58M; release: 10_2_5; last modified: 2018-12-08 21:57:35"),
])

meta_dictionary["/QCD_Pt-20to30_EMEnriched_TuneCP5_13TeV_pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "QCD"),
  ("process_name_specific", "QCD_Pt20to30_EMEnriched"),
  ("nof_db_events",         14255377),
  ("nof_db_files",          183),
  ("fsize_db",              514672737083),
  ("xsection",              4910000.0),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 514.67GB; nevents: 14.26M; release: 10_2_5; last modified: 2018-11-13 03:42:55"),
])

meta_dictionary["/QCD_Pt-30to50_EMEnriched_TuneCP5_13TeV_pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15_ext1-v2/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "QCD"),
  ("process_name_specific", "QCD_Pt30to50_EMEnriched_ext1"),
  ("nof_db_events",         15086084),
  ("nof_db_files",          207),
  ("fsize_db",              562100061688),
  ("xsection",              6415000.0),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 562.10GB; nevents: 15.09M; release: 10_2_5; last modified: 2018-11-18 04:04:42"),
])

meta_dictionary["/QCD_Pt-50to80_EMEnriched_TuneCP5_13TeV_pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "QCD"),
  ("process_name_specific", "QCD_Pt50to80_EMEnriched"),
  ("nof_db_events",         10798233),
  ("nof_db_files",          160),
  ("fsize_db",              427325958129),
  ("xsection",              1986000.0),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 427.33GB; nevents: 10.80M; release: 10_2_5; last modified: 2018-11-24 21:18:47"),
])

meta_dictionary["/QCD_Pt-80to120_EMEnriched_TuneCP5_13TeV_pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "QCD"),
  ("process_name_specific", "QCD_Pt80to120_EMEnriched"),
  ("nof_db_events",         9648791),
  ("nof_db_files",          172),
  ("fsize_db",              407590592957),
  ("xsection",              366500.0),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 407.59GB; nevents: 9.65M; release: 10_2_5; last modified: 2018-11-23 06:37:04"),
])

meta_dictionary["/QCD_Pt-120to170_EMEnriched_TuneCP5_13TeV_pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "QCD"),
  ("process_name_specific", "QCD_Pt120to170_EMEnriched"),
  ("nof_db_events",         9964143),
  ("nof_db_files",          138),
  ("fsize_db",              442430942022),
  ("xsection",              66510.0),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 442.43GB; nevents: 9.96M; release: 10_2_5; last modified: 2018-11-17 01:37:54"),
])

meta_dictionary["/QCD_Pt-170to300_EMEnriched_TuneCP5_13TeV_pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "QCD"),
  ("process_name_specific", "QCD_Pt170to300_EMEnriched"),
  ("nof_db_events",         3712174),
  ("nof_db_files",          74),
  ("fsize_db",              175645304054),
  ("xsection",              16430.0),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 175.65GB; nevents: 3.71M; release: 10_2_5; last modified: 2018-11-12 14:53:19"),
])

meta_dictionary["/QCD_Pt-300toInf_EMEnriched_TuneCP5_13TeV_pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "QCD"),
  ("process_name_specific", "QCD_Pt300toInf_EMEnriched"),
  ("nof_db_events",         2901355),
  ("nof_db_files",          51),
  ("fsize_db",              148206889913),
  ("xsection",              1099.0),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 148.21GB; nevents: 2.90M; release: 10_2_5; last modified: 2018-11-17 22:02:22"),
])

meta_dictionary["/QCD_Pt-15to20_MuEnrichedPt5_TuneCP5_13TeV_pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v3/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "QCD"),
  ("process_name_specific", "QCD_Pt15to20_Mu5"),
  ("nof_db_events",         4576065),
  ("nof_db_files",          129),
  ("fsize_db",              169695109341),
  ("xsection",              2808000.0),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 169.70GB; nevents: 4.58M; release: 10_2_5; last modified: 2019-03-11 03:38:32"),
])

meta_dictionary["/QCD_Pt-20to30_MuEnrichedPt5_TuneCP5_13TeV_pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v4/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "QCD"),
  ("process_name_specific", "QCD_Pt20to30_Mu5"),
  ("nof_db_events",         30612338),
  ("nof_db_files",          454),
  ("fsize_db",              1152472355100),
  ("xsection",              2530000.0),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 1.15TB; nevents: 30.61M; release: 10_2_5; last modified: 2018-12-10 17:57:31"),
])

meta_dictionary["/QCD_Pt-30to50_MuEnrichedPt5_TuneCP5_13TeV_pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v3/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "QCD"),
  ("process_name_specific", "QCD_Pt30to50_Mu5"),
  ("nof_db_events",         29884616),
  ("nof_db_files",          509),
  ("fsize_db",              1170514564416),
  ("xsection",              1368000.0),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 1.17TB; nevents: 29.88M; release: 10_2_5; last modified: 2019-01-14 13:30:50"),
])

meta_dictionary["/QCD_Pt-50to80_MuEnrichedPt5_TuneCP5_13TeV_pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v3/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "QCD"),
  ("process_name_specific", "QCD_Pt50to80_Mu5"),
  ("nof_db_events",         20268872),
  ("nof_db_files",          338),
  ("fsize_db",              846172738073),
  ("xsection",              378000.0),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 846.17GB; nevents: 20.27M; release: 10_2_5; last modified: 2018-12-29 02:52:58"),
])

meta_dictionary["/QCD_Pt-80to120_MuEnrichedPt5_TuneCP5_13TeV_pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "QCD"),
  ("process_name_specific", "QCD_Pt80to120_Mu5"),
  ("nof_db_events",         612919),
  ("nof_db_files",          12),
  ("fsize_db",              27505251400),
  ("xsection",              88580.0),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 27.51GB; nevents: 612.92k; release: 10_2_5; last modified: 2018-11-23 06:33:41"),
])

meta_dictionary["/QCD_Pt-80to120_MuEnrichedPt5_TuneCP5_13TeV_pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15_ext1-v2/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "QCD"),
  ("process_name_specific", "QCD_Pt80to120_Mu5_ext1"),
  ("nof_db_events",         25039361),
  ("nof_db_files",          471),
  ("fsize_db",              1122940596867),
  ("xsection",              88580.0),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 1.12TB; nevents: 25.04M; release: 10_2_5; last modified: 2018-12-18 04:53:10"),
])

meta_dictionary["/QCD_Pt-120to170_MuEnrichedPt5_TuneCP5_13TeV_pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "QCD"),
  ("process_name_specific", "QCD_Pt120to170_Mu5"),
  ("nof_db_events",         633668),
  ("nof_db_files",          18),
  ("fsize_db",              30289310736),
  ("xsection",              21170.0),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 30.29GB; nevents: 633.67k; release: 10_2_5; last modified: 2018-12-13 16:19:42"),
])

meta_dictionary["/QCD_Pt-120to170_MuEnrichedPt5_TuneCP5_13TeV_pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15_ext1-v2/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "QCD"),
  ("process_name_specific", "QCD_Pt120to170_Mu5_ext1"),
  ("nof_db_events",         20682254),
  ("nof_db_files",          387),
  ("fsize_db",              986868206088),
  ("xsection",              21170.0),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 986.87GB; nevents: 20.68M; release: 10_2_5; last modified: 2018-12-15 10:48:08"),
])

meta_dictionary["/QCD_Pt-170to300_MuEnrichedPt5_TuneCP5_13TeV_pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v3/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "QCD"),
  ("process_name_specific", "QCD_Pt170to300_Mu5"),
  ("nof_db_events",         35978539),
  ("nof_db_files",          647),
  ("fsize_db",              1839028645751),
  ("xsection",              7025.0),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 1.84TB; nevents: 35.98M; release: 10_2_5; last modified: 2018-12-21 02:57:56"),
])

meta_dictionary["/QCD_Pt-300to470_MuEnrichedPt5_TuneCP5_13TeV_pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v3/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "QCD"),
  ("process_name_specific", "QCD_Pt300to470_Mu5"),
  ("nof_db_events",         492418),
  ("nof_db_files",          27),
  ("fsize_db",              27486086727),
  ("xsection",              620.5),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 27.49GB; nevents: 492.42k; release: 10_2_5; last modified: 2018-12-07 18:45:02"),
])

meta_dictionary["/QCD_Pt-300to470_MuEnrichedPt5_TuneCP5_13TeV_pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15_ext3-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "QCD"),
  ("process_name_specific", "QCD_Pt300to470_Mu5_ext3"),
  ("nof_db_events",         28996145),
  ("nof_db_files",          734),
  ("fsize_db",              1604985239434),
  ("xsection",              620.5),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 1.60TB; nevents: 29.00M; release: 10_2_6; last modified: 2019-02-02 00:36:54"),
])

meta_dictionary["/QCD_Pt-470to600_MuEnrichedPt5_TuneCP5_13TeV_pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "QCD"),
  ("process_name_specific", "QCD_Pt470to600_Mu5"),
  ("nof_db_events",         492716),
  ("nof_db_files",          19),
  ("fsize_db",              28705682413),
  ("xsection",              59.11),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 28.71GB; nevents: 492.72k; release: 10_2_5; last modified: 2018-11-27 11:53:02"),
])

meta_dictionary["/QCD_Pt-470to600_MuEnrichedPt5_TuneCP5_13TeV_pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15_ext1-v2/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "QCD"),
  ("process_name_specific", "QCD_Pt470to600_Mu5_ext1"),
  ("nof_db_events",         20003034),
  ("nof_db_files",          544),
  ("fsize_db",              1163063442101),
  ("xsection",              59.11),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 1.16TB; nevents: 20.00M; release: 10_2_5; last modified: 2018-12-24 11:07:24"),
])

meta_dictionary["/QCD_Pt-600to800_MuEnrichedPt5_TuneCP5_13TeV_pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "QCD"),
  ("process_name_specific", "QCD_Pt600to800_Mu5"),
  ("nof_db_events",         16618977),
  ("nof_db_files",          419),
  ("fsize_db",              993851362870),
  ("xsection",              18.36),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 993.85GB; nevents: 16.62M; release: 10_2_6; last modified: 2018-12-01 16:43:58"),
])

meta_dictionary["/QCD_Pt-800to1000_MuEnrichedPt5_TuneCP5_13TeV_pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15_ext3-v2/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "QCD"),
  ("process_name_specific", "QCD_Pt800to1000_Mu5_ext3"),
  ("nof_db_events",         16749914),
  ("nof_db_files",          466),
  ("fsize_db",              1035961577415),
  ("xsection",              3.275),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 1.04TB; nevents: 16.75M; release: 10_2_5; last modified: 2019-02-26 16:11:56"),
])

meta_dictionary["/QCD_Pt-1000toInf_MuEnrichedPt5_TuneCP5_13TeV_pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "QCD"),
  ("process_name_specific", "QCD_Pt1000toInf_Mu5"),
  ("nof_db_events",         10719790),
  ("nof_db_files",          279),
  ("fsize_db",              683812448772),
  ("xsection",              1.079),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 683.81GB; nevents: 10.72M; release: 10_2_6; last modified: 2019-01-15 03:55:05"),
])


# event statistics by sample category:
# signal:                    67.66M
# tHq:                       29.68M
# tHW:                       15.00M
# additional_signal_overlap: 958.00k
# TTZ:                       36.18M
# TTW:                       17.73M
# TTWW:                      985.00k
# TT:                        873.18M
# Rares:                     63.57M
# VH:                        12.90M
# EWK:                       1.06G
# QCD:                       343.31M

