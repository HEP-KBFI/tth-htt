from collections import OrderedDict as OD

# file generated at 2019-11-21 16:11:21 with the following command:
# find_samples.py -V -i ../NanoAOD/test/datasets/txt/datasets_mc_2017_RunIIFall17MiniAODv2.txt -m python/samples/metaDict_2017_mc.py -s ../NanoAOD/test/datasets/txt/sum_datasets_2017_RunIIFall17MiniAODv2.txt -c python/samples/sampleLocations_2017_nanoAOD.txt

meta_dictionary = OD()


### event sums

sum_events = { 
  ("ttHToNonbb_M125_powheg", "ttHToNonbb_M125_powheg_ext1"),
  ("GluGluHToTauTau", "GluGluHToTauTau_ext1"),
  ("GluGluHToZZTo4L_ext1", "GluGluHToZZTo4L_ext3", "GluGluHToZZTo4L_ext4"),
  ("GluGluHToMuMu_M125", "GluGluHToMuMu_M125_ext1"),
  ("VBF_HToZZTo4L", "VBF_HToZZTo4L_ext1", "VBF_HToZZTo4L_ext2"),
  ("VBFHToGG_M125", "VBFHToGG_M125_PSWeights_ext1"),
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
  ("ZZTo4L", "ZZTo4L_ext1", "ZZTo4L_ext2"),
}


meta_dictionary["/ttHJetToNonbb_M125_TuneCP5_13TeV_amcatnloFXFX_madspin_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Oct22_ttHJetToNonbb_M125_TuneCP5_13TeV_amcatnloFXFX_madspin_pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v"),
  ("sample_category",       "ttH"),
  ("process_name_specific", "ttHJetToNonbb_M125_amcatnlo"),
  ("nof_db_events",         9779592),
  ("nof_db_files",          208),
  ("fsize_db",              625507074411),
  ("xsection",              0.2118),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "94.95%; status: VALID; size: 625.51GB; nevents: 9.78M; release: 9_4_7; last modified: 2018-06-16 07:53:14"),
])

meta_dictionary["/ttHToNonbb_M125_TuneCP5_13TeV-powheg-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Sep28_ttHToNonbb_M125_TuneCP5_13TeV-powheg-pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v1"),
  ("sample_category",       "ttH"),
  ("process_name_specific", "ttHToNonbb_M125_powheg"),
  ("nof_db_events",         7966779),
  ("nof_db_files",          164),
  ("fsize_db",              494872891344),
  ("xsection",              0.2118),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 494.87GB; nevents: 7.97M; release: 9_4_7; last modified: 2018-06-16 16:33:14"),
])

meta_dictionary["/ttHToNonbb_M125_TuneCP5_13TeV-powheg-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14_ext1-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Sep28_ttHToNonbb_M125_TuneCP5_13TeV-powheg-pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14_ext1-v2"),
  ("sample_category",       "ttH"),
  ("process_name_specific", "ttHToNonbb_M125_powheg_ext1"),
  ("nof_db_events",         8241489),
  ("nof_db_files",          355),
  ("fsize_db",              515822367934),
  ("xsection",              0.2118),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 515.82GB; nevents: 8.24M; release: 9_4_6_patch1; last modified: 2019-01-18 18:55:27"),
])

meta_dictionary["/TTH_4f_ctcvcp_TuneCP5_13TeV_madgraph_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Sep28_TTH_4f_ctcvcp_TuneCP5_13TeV_madgraph_pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1"),
  ("sample_category",       "ttH_ctcvcp"),
  ("process_name_specific", "TTH_4f_ctcvcp"),
  ("nof_db_events",         9618000),
  ("nof_db_files",          257),
  ("fsize_db",              604098212165),
  ("xsection",              0.5071),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "94.85%; status: VALID; size: 604.10GB; nevents: 9.62M; release: 9_4_7; last modified: 2019-02-02 22:34:37"),
])

meta_dictionary["/THQ_ctcvcp_4f_Hincl_13TeV_madgraph_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Sep28_THQ_ctcvcp_4f_Hincl_13TeV_madgraph_pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1"),
  ("sample_category",       "tHq"),
  ("process_name_specific", "THQ_ctcvcp"),
  ("nof_db_events",         9918994),
  ("nof_db_files",          258),
  ("fsize_db",              569542482347),
  ("xsection",              0.07096),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 569.54GB; nevents: 9.92M; release: 9_4_7; last modified: 2019-02-02 05:57:19"),
])

meta_dictionary["/THW_ctcvcp_5f_Hincl_13TeV_madgraph_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Sep28_THW_ctcvcp_5f_Hincl_13TeV_madgraph_pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1"),
  ("sample_category",       "tHW"),
  ("process_name_specific", "THW_ctcvcp"),
  ("nof_db_events",         4719999),
  ("nof_db_files",          172),
  ("fsize_db",              308444472684),
  ("xsection",              0.01561),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 308.44GB; nevents: 4.72M; release: 9_4_7; last modified: 2019-02-05 11:33:24"),
])

meta_dictionary["/GluGluHToTauTau_M125_13TeV_powheg_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Sep28_GluGluHToTauTau_M125_13TeV_powheg_pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v2"),
  ("sample_category",       "ggH"),
  ("process_name_specific", "GluGluHToTauTau"),
  ("nof_db_events",         2921180),
  ("nof_db_files",          35),
  ("fsize_db",              121621260930),
  ("xsection",              3.0469),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 121.62GB; nevents: 2.92M; release: 9_4_6_patch1; last modified: 2019-02-02 05:48:45"),
])

meta_dictionary["/GluGluHToTauTau_M125_13TeV_powheg_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14_ext1-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Sep28_GluGluHToTauTau_M125_13TeV_powheg_pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14_ext1-v1"),
  ("sample_category",       "ggH"),
  ("process_name_specific", "GluGluHToTauTau_ext1"),
  ("nof_db_events",         9259000),
  ("nof_db_files",          169),
  ("fsize_db",              387946138466),
  ("xsection",              3.0469),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 387.95GB; nevents: 9.26M; release: 9_4_7; last modified: 2018-10-19 11:01:45"),
])

meta_dictionary["/GluGluHToZZTo4L_M125_13TeV_powheg2_JHUGenV7011_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14_ext1-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Sep28_GluGluHToZZTo4L_M125_13TeV_powheg2_JHUGenV7011_pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14_ext1-v1"),
  ("sample_category",       "ggH"),
  ("process_name_specific", "GluGluHToZZTo4L_ext1"),
  ("nof_db_events",         965198),
  ("nof_db_files",          20),
  ("fsize_db",              44829063769),
  ("xsection",              0.01297),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 44.83GB; nevents: 965.20k; release: 9_4_6_patch1; last modified: 2018-04-20 00:56:39"),
])

meta_dictionary["/GluGluHToZZTo4L_M125_13TeV_powheg2_JHUGenV7011_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14_ext3-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Sep28_GluGluHToZZTo4L_M125_13TeV_powheg2_JHUGenV7011_pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14_ext3-v1"),
  ("sample_category",       "ggH"),
  ("process_name_specific", "GluGluHToZZTo4L_ext3"),
  ("nof_db_events",         988000),
  ("nof_db_files",          50),
  ("fsize_db",              46820541357),
  ("xsection",              0.01297),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 46.82GB; nevents: 988.00k; release: 9_4_7; last modified: 2019-05-03 07:06:07"),
])

meta_dictionary["/GluGluHToZZTo4L_M125_13TeV_powheg2_JHUGenV7011_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14_ext4-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Sep28_GluGluHToZZTo4L_M125_13TeV_powheg2_JHUGenV7011_pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14_ext4-v1"),
  ("sample_category",       "ggH"),
  ("process_name_specific", "GluGluHToZZTo4L_ext4"),
  ("nof_db_events",         988312),
  ("nof_db_files",          45),
  ("fsize_db",              47000353665),
  ("xsection",              0.01297),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 47.00GB; nevents: 988.31k; release: 9_4_7; last modified: 2019-07-31 05:48:10"),
])

meta_dictionary["/GluGluHToZZTo2L2Q_M125_13TeV_powheg2_JHUGenV7011_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Sep28_GluGluHToZZTo2L2Q_M125_13TeV_powheg2_JHUGenV7011_pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2"),
  ("sample_category",       "ggH"),
  ("process_name_specific", "GluGluHToZZTo2L2Q_M125"),
  ("nof_db_events",         992000),
  ("nof_db_files",          48),
  ("fsize_db",              44974281652),
  ("xsection",              0.17963),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 44.97GB; nevents: 992.00k; release: 9_4_7; last modified: 2018-11-09 16:54:33"),
])

meta_dictionary["/GluGluHToWWToLNuQQ_M125_NNPDF31_TuneCP5_PSweights_13TeV_powheg_JHUGen710_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Sep28_GluGluHToWWToLNuQQ_M125_NNPDF31_TuneCP5_PSweights_13TeV_powheg_JHUGen710_pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_real"),
  ("sample_category",       "ggH"),
  ("process_name_specific", "GluGluHToWWToLNuQQ_M125_PSweights"),
  ("nof_db_events",         465000),
  ("nof_db_files",          19),
  ("fsize_db",              19992436481),
  ("xsection",              4.5621),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 19.99GB; nevents: 465.00k; release: 9_4_7; last modified: 2018-10-07 00:04:12"),
])

meta_dictionary["/GluGluHToWWTo2L2Nu_M125_13TeV_powheg2_JHUGenV714_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Sep28_GluGluHToWWTo2L2Nu_M125_13TeV_powheg2_JHUGenV714_pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1"),
  ("sample_category",       "ggH"),
  ("process_name_specific", "GluGluHToWWTo2L2Nu_M125"),
  ("nof_db_events",         953600),
  ("nof_db_files",          58),
  ("fsize_db",              41071656137),
  ("xsection",              1.1033),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 41.07GB; nevents: 953.60k; release: 9_4_7; last modified: 2018-10-14 09:40:46"),
])

meta_dictionary["/GluGluHToMuMu_M-125_TuneCP5_PSweights_13TeV_powheg_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Sep28_GluGluHToMuMu_M-125_TuneCP5_PSweights_13TeV_powheg_pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1"),
  ("sample_category",       "ggH"),
  ("process_name_specific", "GluGluHToMuMu_M125"),
  ("nof_db_events",         494000),
  ("nof_db_files",          16),
  ("fsize_db",              21883331893),
  ("xsection",              0.010571),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 21.88GB; nevents: 494.00k; release: 9_4_7; last modified: 2019-03-12 20:43:43"),
])

meta_dictionary["/GluGluHToMuMu_M-125_TuneCP5_PSweights_13TeV_powheg_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14_ext1-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Sep28_GluGluHToMuMu_M-125_TuneCP5_PSweights_13TeV_powheg_pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14_ext1-v1"),
  ("sample_category",       "ggH"),
  ("process_name_specific", "GluGluHToMuMu_M125_ext1"),
  ("nof_db_events",         1489600),
  ("nof_db_files",          53),
  ("fsize_db",              66238692309),
  ("xsection",              0.010571),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 66.24GB; nevents: 1.49M; release: 9_4_7; last modified: 2019-02-25 18:44:47"),
])

meta_dictionary["/GluGluHToBB_M125_13TeV_amcatnloFXFX_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Sep28_GluGluHToBB_M125_13TeV_amcatnloFXFX_pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2"),
  ("sample_category",       "ggH"),
  ("process_name_specific", "GluGluHToBB_M125"),
  ("nof_db_events",         9358631),
  ("nof_db_files",          200),
  ("fsize_db",              416027040109),
  ("xsection",              28.293),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 416.03GB; nevents: 9.36M; release: 9_4_7; last modified: 2018-09-30 15:41:28"),
])

meta_dictionary["/GluGluHToGG_M125_13TeV_amcatnloFXFX_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Sep28_GluGluHToGG_M125_13TeV_amcatnloFXFX_pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2"),
  ("sample_category",       "ggH"),
  ("process_name_specific", "GluGluHToGG_M125"),
  ("nof_db_events",         1995838),
  ("nof_db_files",          61),
  ("fsize_db",              88338303082),
  ("xsection",              0.11028),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 88.34GB; nevents: 2.00M; release: 9_4_7; last modified: 2018-11-09 01:11:29"),
])

meta_dictionary["/VBFHToTauTau_M125_13TeV_powheg_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Sep28_VBFHToTauTau_M125_13TeV_powheg_pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v1"),
  ("sample_category",       "qqH"),
  ("process_name_specific", "VBFHToTauTau"),
  ("nof_db_events",         2977152),
  ("nof_db_files",          39),
  ("fsize_db",              133660549317),
  ("xsection",              0.2372),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 133.66GB; nevents: 2.98M; release: 9_4_7; last modified: 2019-02-01 22:16:12"),
])

meta_dictionary["/VBF_HToZZTo4L_M125_13TeV_powheg2_JHUGenV7011_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Sep28_VBF_HToZZTo4L_M125_13TeV_powheg2_JHUGenV7011_pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1"),
  ("sample_category",       "qqH"),
  ("process_name_specific", "VBF_HToZZTo4L"),
  ("nof_db_events",         981285),
  ("nof_db_files",          53),
  ("fsize_db",              50160648576),
  ("xsection",              0.0010099),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 50.16GB; nevents: 981.28k; release: 9_4_6_patch1,9_4_7; last modified: 2018-04-21 01:03:45"),
])

meta_dictionary["/VBF_HToZZTo4L_M125_13TeV_powheg2_JHUGenV7011_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14_ext1-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Sep28_VBF_HToZZTo4L_M125_13TeV_powheg2_JHUGenV7011_pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14_ext1-v1"),
  ("sample_category",       "qqH"),
  ("process_name_specific", "VBF_HToZZTo4L_ext1"),
  ("nof_db_events",         986020),
  ("nof_db_files",          19),
  ("fsize_db",              49857117667),
  ("xsection",              0.0010099),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 49.86GB; nevents: 986.02k; release: 9_4_6_patch1; last modified: 2018-04-20 18:50:13"),
])

meta_dictionary["/VBF_HToZZTo4L_M125_13TeV_powheg2_JHUGenV7011_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14_ext2-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Sep28_VBF_HToZZTo4L_M125_13TeV_powheg2_JHUGenV7011_pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14_ext2-v2"),
  ("sample_category",       "qqH"),
  ("process_name_specific", "VBF_HToZZTo4L_ext2"),
  ("nof_db_events",         1000000),
  ("nof_db_files",          29),
  ("fsize_db",              51167133340),
  ("xsection",              0.0010099),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 51.17GB; nevents: 1.00M; release: 9_4_7; last modified: 2019-04-30 13:11:46"),
])

meta_dictionary["/VBFHToWWToLNuQQ_M125_NNPDF31_TuneCP5_PSweights_13TeV_powheg_JHUGen710_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Sep28_VBFHToWWToLNuQQ_M125_NNPDF31_TuneCP5_PSweights_13TeV_powheg_JHUGen710_pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realist"),
  ("sample_category",       "qqH"),
  ("process_name_specific", "VBFHToWWToLNuQQ_M125_PSweights"),
  ("nof_db_events",         483600),
  ("nof_db_files",          30),
  ("fsize_db",              22613864866),
  ("xsection",              0.35517),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 22.61GB; nevents: 483.60k; release: 9_4_7; last modified: 2018-08-12 23:18:00"),
])

meta_dictionary["/VBFHToWWTo2L2Nu_M125_13TeV_powheg2_JHUGenV714_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Sep28_VBFHToWWTo2L2Nu_M125_13TeV_powheg2_JHUGenV714_pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1"),
  ("sample_category",       "qqH"),
  ("process_name_specific", "VBFHToWWTo2L2Nu_M125"),
  ("nof_db_events",         500000),
  ("nof_db_files",          32),
  ("fsize_db",              22373340398),
  ("xsection",              0.085894),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 22.37GB; nevents: 500.00k; release: 9_4_7; last modified: 2018-10-15 04:21:53"),
])

meta_dictionary["/VBFHToMuMu_M-125_TuneCP5_PSweights_13TeV_powheg_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Oct22_VBFHToMuMu_M-125_TuneCP5_PSweights_13TeV_powheg_pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1"),
  ("sample_category",       "qqH"),
  ("process_name_specific", "VBFHToMuMu_M125"),
  ("nof_db_events",         982200),
  ("nof_db_files",          69),
  ("fsize_db",              47471748498),
  ("xsection",              0.00082296),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 47.47GB; nevents: 982.20k; release: 9_4_7; last modified: 2019-02-23 14:50:58"),
])

meta_dictionary["/VBFHToBB_M-125_13TeV_powheg_pythia8_weightfix/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Sep28_VBFHToBB_M-125_13TeV_powheg_pythia8_weightfix__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1"),
  ("sample_category",       "qqH"),
  ("process_name_specific", "VBFHToBB_M125"),
  ("nof_db_events",         5000000),
  ("nof_db_files",          69),
  ("fsize_db",              227405574450),
  ("xsection",              2.2026),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 227.41GB; nevents: 5.00M; release: 9_4_6_patch1; last modified: 2018-04-20 12:28:21"),
])

meta_dictionary["/VBFHToGG_M125_13TeV_amcatnlo_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Sep28_VBFHToGG_M125_13TeV_amcatnlo_pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1"),
  ("sample_category",       "qqH"),
  ("process_name_specific", "VBFHToGG_M125"),
  ("nof_db_events",         1925302),
  ("nof_db_files",          28),
  ("fsize_db",              86362858092),
  ("xsection",              0.0085851),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 86.36GB; nevents: 1.93M; release: 9_4_6_patch1; last modified: 2018-04-20 01:00:09"),
])

meta_dictionary["/VBFHToGG_M125_13TeV_amcatnlo_pythia8_PSWeights/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14_ext1-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Sep28_VBFHToGG_M125_13TeV_amcatnlo_pythia8_PSWeights__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14_ext1-v1"),
  ("sample_category",       "qqH"),
  ("process_name_specific", "VBFHToGG_M125_PSWeights_ext1"),
  ("nof_db_events",         975930),
  ("nof_db_files",          16),
  ("fsize_db",              44420652691),
  ("xsection",              0.0085851),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 44.42GB; nevents: 975.93k; release: 9_4_6_patch1; last modified: 2018-07-11 08:45:43"),
])

meta_dictionary["/TTZToLLNuNu_M-10_TuneCP5_13TeV-amcatnlo-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Sep28_TTZToLLNuNu_M-10_TuneCP5_13TeV-amcatnlo-pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2"),
  ("sample_category",       "TTZ"),
  ("process_name_specific", "TTZToLL_M10"),
  ("nof_db_events",         7932650),
  ("nof_db_files",          150),
  ("fsize_db",              479409585023),
  ("xsection",              0.2072),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 479.41GB; nevents: 7.93M; release: 9_4_7; last modified: 2019-03-07 12:07:09"),
])

meta_dictionary["/TTZToLLNuNu_M-10_TuneCP5_PSweights_13TeV-amcatnlo-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Sep28_TTZToLLNuNu_M-10_TuneCP5_PSweights_13TeV-amcatnlo-pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1"),
  ("sample_category",       "TTZ"),
  ("process_name_specific", "TTZToLL_M10_PSweights"),
  ("nof_db_events",         11092000),
  ("nof_db_files",          300),
  ("fsize_db",              673564862733),
  ("xsection",              0.2072),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 673.56GB; nevents: 11.09M; release: 9_4_6_patch1; last modified: 2019-02-14 05:38:09"),
])

meta_dictionary["/TTZToLL_M-1to10_TuneCP5_13TeV-amcatnlo-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Sep28_TTZToLL_M-1to10_TuneCP5_13TeV-amcatnlo-pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2"),
  ("sample_category",       "TTZ"),
  ("process_name_specific", "TTZToLL_M-1to10"),
  ("nof_db_events",         245978),
  ("nof_db_files",          6),
  ("fsize_db",              14747523608),
  ("xsection",              0.04537),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 14.75GB; nevents: 245.98k; release: 9_4_6_patch1; last modified: 2019-01-22 23:11:36"),
])

meta_dictionary["/ttZJets_TuneCP5_13TeV_madgraphMLM_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Sep28_ttZJets_TuneCP5_13TeV_madgraphMLM_pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1"),
  ("sample_category",       "TTZ"),
  ("process_name_specific", "TTZJets_LO"),
  ("nof_db_events",         9698473),
  ("nof_db_files",          197),
  ("fsize_db",              591860866458),
  ("xsection",              0.8393),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 591.86GB; nevents: 9.70M; release: 9_4_7; last modified: 2018-10-05 15:55:02"),
])

meta_dictionary["/ttZJets_TuneCP5_13TeV_madgraphMLM_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14_ext1-v3/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Sep28_ttZJets_TuneCP5_13TeV_madgraphMLM_pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14_ext1-v3"),
  ("sample_category",       "TTZ"),
  ("process_name_specific", "TTZJets_LO_ext1"),
  ("nof_db_events",         8536618),
  ("nof_db_files",          199),
  ("fsize_db",              522473916483),
  ("xsection",              0.8393),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 522.47GB; nevents: 8.54M; release: 9_4_6_patch1; last modified: 2018-09-05 20:51:50"),
])

meta_dictionary["/TTWJetsToLNu_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Oct22_TTWJetsToLNu_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2"),
  ("sample_category",       "TTW"),
  ("process_name_specific", "TTWJetsToLNu"),
  ("nof_db_events",         4994543),
  ("nof_db_files",          95),
  ("fsize_db",              304322832014),
  ("xsection",              0.196),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "92.16%; status: VALID; size: 304.32GB; nevents: 4.99M; release: 9_4_7; last modified: 2019-02-20 08:25:15"),
])

meta_dictionary["/TTWJetsToLNu_TuneCP5_PSweights_13TeV-amcatnloFXFX-madspin-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Sep28_TTWJetsToLNu_TuneCP5_PSweights_13TeV-amcatnloFXFX-madspin-pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v"),
  ("sample_category",       "TTW"),
  ("process_name_specific", "TTWJetsToLNu_PSweights"),
  ("nof_db_events",         4908905),
  ("nof_db_files",          122),
  ("fsize_db",              301017438722),
  ("xsection",              0.196),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 301.02GB; nevents: 4.91M; release: 9_4_7; last modified: 2018-10-05 06:47:54"),
])

meta_dictionary["/ttWJets_TuneCP5_13TeV_madgraphMLM_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Sep28_ttWJets_TuneCP5_13TeV_madgraphMLM_pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1"),
  ("sample_category",       "TTW"),
  ("process_name_specific", "TTWJets_LO"),
  ("nof_db_events",         6415920),
  ("nof_db_files",          132),
  ("fsize_db",              393195148836),
  ("xsection",              0.6008),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 393.20GB; nevents: 6.42M; release: 9_4_6_patch1; last modified: 2018-09-07 15:59:35"),
])

meta_dictionary["/ttWJets_TuneCP5_13TeV_madgraphMLM_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14_ext1-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Sep28_ttWJets_TuneCP5_13TeV_madgraphMLM_pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14_ext1-v2"),
  ("sample_category",       "TTW"),
  ("process_name_specific", "TTWJets_LO_ext1"),
  ("nof_db_events",         9425384),
  ("nof_db_files",          280),
  ("fsize_db",              577708152029),
  ("xsection",              0.6008),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 577.71GB; nevents: 9.43M; release: 9_4_6_patch1; last modified: 2018-08-02 01:24:11"),
])

meta_dictionary["/TTWW_TuneCP5_13TeV-madgraph-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14_ext1-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Nov24_TTWW_TuneCP5_13TeV-madgraph-pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14_ext1-v1"),
  ("sample_category",       "TTWW"),
  ("process_name_specific", "TTWW_ext1"),
  ("nof_db_events",         200000),
  ("nof_db_files",          5),
  ("fsize_db",              13174218718),
  ("xsection",              0.006981),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 13.17GB; nevents: 200.00k; release: 9_4_7; last modified: 2018-09-19 14:03:03"),
])

meta_dictionary["/ST_s-channel_4f_leptonDecays_TuneCP5_13TeV-amcatnlo-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Sep28_ST_s-channel_4f_leptonDecays_TuneCP5_13TeV-amcatnlo-pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2"),
  ("sample_category",       "TT"),
  ("process_name_specific", "ST_s-channel_4f_leptonDecays"),
  ("nof_db_events",         9883805),
  ("nof_db_files",          143),
  ("fsize_db",              456938749955),
  ("xsection",              3.364),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 456.94GB; nevents: 9.88M; release: 9_4_6_patch1; last modified: 2018-10-04 16:47:09"),
])

meta_dictionary["/ST_s-channel_4f_leptonDecays_TuneCP5_PSweights_13TeV-amcatnlo-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Sep28_ST_s-channel_4f_leptonDecays_TuneCP5_PSweights_13TeV-amcatnlo-pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realist"),
  ("sample_category",       "TT"),
  ("process_name_specific", "ST_s-channel_4f_leptonDecays_PSweights"),
  ("nof_db_events",         9914948),
  ("nof_db_files",          147),
  ("fsize_db",              458781982765),
  ("xsection",              3.364),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 458.78GB; nevents: 9.91M; release: 9_4_7; last modified: 2018-10-14 23:49:33"),
])

meta_dictionary["/ST_t-channel_antitop_4f_inclusiveDecays_TuneCP5_13TeV-powhegV2-madspin-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Sep28_ST_t-channel_antitop_4f_inclusiveDecays_TuneCP5_13TeV-powhegV2-madspin-pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realis"),
  ("sample_category",       "TT"),
  ("process_name_specific", "ST_t-channel_antitop_4f_inclusiveDecays"),
  ("nof_db_events",         3675910),
  ("nof_db_files",          69),
  ("fsize_db",              173657703453),
  ("xsection",              80.95),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 173.66GB; nevents: 3.68M; release: 9_4_6_patch1; last modified: 2018-10-22 06:00:47"),
])

meta_dictionary["/ST_t-channel_antitop_4f_InclusiveDecays_TuneCP5_PSweights_13TeV-powheg-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Sep28_ST_t-channel_antitop_4f_InclusiveDecays_TuneCP5_PSweights_13TeV-powheg-pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realis"),
  ("sample_category",       "TT"),
  ("process_name_specific", "ST_t-channel_antitop_4f_inclusiveDecays_PSweights"),
  ("nof_db_events",         64818800),
  ("nof_db_files",          1288),
  ("fsize_db",              3064755155948),
  ("xsection",              80.95),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 3.06TB; nevents: 64.82M; release: 9_4_7; last modified: 2018-09-26 11:08:14"),
])

meta_dictionary["/ST_t-channel_top_4f_inclusiveDecays_TuneCP5_13TeV-powhegV2-madspin-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Sep28_ST_t-channel_top_4f_inclusiveDecays_TuneCP5_13TeV-powhegV2-madspin-pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_re"),
  ("sample_category",       "TT"),
  ("process_name_specific", "ST_t-channel_top_4f_inclusiveDecays"),
  ("nof_db_events",         5982064),
  ("nof_db_files",          93),
  ("fsize_db",              281605211173),
  ("xsection",              136.02),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 281.61GB; nevents: 5.98M; release: 9_4_7; last modified: 2018-06-11 22:54:09"),
])

meta_dictionary["/ST_t-channel_top_4f_InclusiveDecays_TuneCP5_PSweights_13TeV-powheg-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Sep28_ST_t-channel_top_4f_InclusiveDecays_TuneCP5_PSweights_13TeV-powheg-pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_"),
  ("sample_category",       "TT"),
  ("process_name_specific", "ST_t-channel_top_4f_inclusiveDecays_PSweights"),
  ("nof_db_events",         122688200),
  ("nof_db_files",          2354),
  ("fsize_db",              5815097338121),
  ("xsection",              136.02),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 5.82TB; nevents: 122.69M; release: 9_4_7; last modified: 2018-11-11 14:11:55"),
])

meta_dictionary["/ST_tW_antitop_5f_inclusiveDecays_TuneCP5_13TeV-powheg-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Sep28_ST_tW_antitop_5f_inclusiveDecays_TuneCP5_13TeV-powheg-pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2"),
  ("sample_category",       "TT"),
  ("process_name_specific", "ST_tW_antitop_5f_inclusiveDecays"),
  ("nof_db_events",         7977430),
  ("nof_db_files",          134),
  ("fsize_db",              409038270439),
  ("xsection",              35.85),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 409.04GB; nevents: 7.98M; release: 9_4_7; last modified: 2018-10-06 03:17:43"),
])

meta_dictionary["/ST_tW_antitop_5f_inclusiveDecays_TuneCP5_PSweights_13TeV-powheg-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Sep28_ST_tW_antitop_5f_inclusiveDecays_TuneCP5_PSweights_13TeV-powheg-pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14"),
  ("sample_category",       "TT"),
  ("process_name_specific", "ST_tW_antitop_5f_inclusiveDecays_PSweights"),
  ("nof_db_events",         7745276),
  ("nof_db_files",          150),
  ("fsize_db",              397785712841),
  ("xsection",              35.85),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 397.79GB; nevents: 7.75M; release: 9_4_7; last modified: 2018-09-19 03:46:20"),
])

meta_dictionary["/ST_tW_top_5f_inclusiveDecays_TuneCP5_13TeV-powheg-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Sep28_ST_tW_top_5f_inclusiveDecays_TuneCP5_13TeV-powheg-pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2"),
  ("sample_category",       "TT"),
  ("process_name_specific", "ST_tW_top_5f_inclusiveDecays"),
  ("nof_db_events",         7794186),
  ("nof_db_files",          139),
  ("fsize_db",              399638903127),
  ("xsection",              35.85),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 399.64GB; nevents: 7.79M; release: 9_4_6_patch1; last modified: 2018-09-19 08:25:32"),
])

meta_dictionary["/ST_tW_top_5f_inclusiveDecays_TuneCP5_PSweights_13TeV-powheg-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Sep28_ST_tW_top_5f_inclusiveDecays_TuneCP5_PSweights_13TeV-powheg-pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic"),
  ("sample_category",       "TT"),
  ("process_name_specific", "ST_tW_top_5f_inclusiveDecays_PSweights"),
  ("nof_db_events",         7945242),
  ("nof_db_files",          114),
  ("fsize_db",              407830773310),
  ("xsection",              35.85),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 407.83GB; nevents: 7.95M; release: 9_4_6_patch1; last modified: 2018-10-13 06:08:18"),
])

meta_dictionary["/ST_tWll_5f_LO_TuneCP5_PSweights_13TeV-madgraph-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14_ext1-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Sep28_ST_tWll_5f_LO_TuneCP5_PSweights_13TeV-madgraph-pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14_ext1-v1"),
  ("sample_category",       "TT"),
  ("process_name_specific", "ST_tWll_PSweights_ext1"),
  ("nof_db_events",         986000),
  ("nof_db_files",          42),
  ("fsize_db",              62041007346),
  ("xsection",              0.01096),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 62.04GB; nevents: 986.00k; release: 9_4_7; last modified: 2019-01-03 22:41:21"),
])

meta_dictionary["/TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Sep28_TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v1"),
  ("sample_category",       "TT"),
  ("process_name_specific", "TTTo2L2Nu"),
  ("nof_db_events",         9000000),
  ("nof_db_files",          153),
  ("fsize_db",              482042390765),
  ("xsection",              88.4),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 482.04GB; nevents: 9.00M; release: 9_4_6_patch1; last modified: 2018-09-10 15:51:32"),
])

meta_dictionary["/TTTo2L2Nu_TuneCP5_PSweights_13TeV-powheg-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Sep28_TTTo2L2Nu_TuneCP5_PSweights_13TeV-powheg-pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v2"),
  ("sample_category",       "TT"),
  ("process_name_specific", "TTTo2L2Nu_PSweights"),
  ("nof_db_events",         69155808),
  ("nof_db_files",          1056),
  ("fsize_db",              3693271643807),
  ("xsection",              88.4),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 3.69TB; nevents: 69.16M; release: 9_4_7; last modified: 2018-11-25 13:11:01"),
])

meta_dictionary["/TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Sep28_TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v1"),
  ("sample_category",       "TT"),
  ("process_name_specific", "TTToSemiLeptonic"),
  ("nof_db_events",         43732445),
  ("nof_db_files",          828),
  ("fsize_db",              2384692629872),
  ("xsection",              365.52),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 2.38TB; nevents: 43.73M; release: 9_4_6_patch1; last modified: 2018-09-23 07:13:45"),
])

meta_dictionary["/TTToSemiLeptonic_TuneCP5_PSweights_13TeV-powheg-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Sep28_TTToSemiLeptonic_TuneCP5_PSweights_13TeV-powheg-pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2"),
  ("sample_category",       "TT"),
  ("process_name_specific", "TTToSemiLeptonic_PSweights"),
  ("nof_db_events",         110195128),
  ("nof_db_files",          2178),
  ("fsize_db",              6010271289488),
  ("xsection",              365.52),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 6.01TB; nevents: 110.20M; release: 9_4_6_patch1; last modified: 2018-10-26 11:16:09"),
])

meta_dictionary["/TTToHadronic_TuneCP5_13TeV-powheg-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Sep28_TTToHadronic_TuneCP5_13TeV-powheg-pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v2"),
  ("sample_category",       "TT"),
  ("process_name_specific", "TTToHadronic"),
  ("nof_db_events",         41729120),
  ("nof_db_files",          665),
  ("fsize_db",              2307611725630),
  ("xsection",              377.85),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 2.31TB; nevents: 41.73M; release: 9_4_7; last modified: 2018-10-06 14:41:34"),
])

meta_dictionary["/TTToHadronic_TuneCP5_PSweights_13TeV-powheg-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Sep28_TTToHadronic_TuneCP5_PSweights_13TeV-powheg-pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v1"),
  ("sample_category",       "TT"),
  ("process_name_specific", "TTToHadronic_PSweights"),
  ("nof_db_events",         130262440),
  ("nof_db_files",          2021),
  ("fsize_db",              7191138172968),
  ("xsection",              377.85),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 7.19TB; nevents: 130.26M; release: 9_4_7; last modified: 2018-10-13 06:14:24"),
])

meta_dictionary["/TTJets_DiLept_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Sep28_TTJets_DiLept_TuneCP5_13TeV-madgraphMLM-pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1"),
  ("sample_category",       "TT"),
  ("process_name_specific", "TTJets_DiLept"),
  ("nof_db_events",         28380110),
  ("nof_db_files",          602),
  ("fsize_db",              1574497543250),
  ("xsection",              88.4),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 1.57TB; nevents: 28.38M; release: 9_4_6_patch1; last modified: 2018-09-19 21:13:11"),
])

meta_dictionary["/TTJets_SingleLeptFromT_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Sep28_TTJets_SingleLeptFromT_TuneCP5_13TeV-madgraphMLM-pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1"),
  ("sample_category",       "TT"),
  ("process_name_specific", "TTJets_SingleLeptFromT"),
  ("nof_db_events",         61947630),
  ("nof_db_files",          1056),
  ("fsize_db",              3422466502202),
  ("xsection",              182.76),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 3.42TB; nevents: 61.95M; release: 9_4_6_patch1; last modified: 2018-04-27 06:06:08"),
])

meta_dictionary["/TTJets_SingleLeptFromTbar_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Sep28_TTJets_SingleLeptFromTbar_TuneCP5_13TeV-madgraphMLM-pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1"),
  ("sample_category",       "TT"),
  ("process_name_specific", "TTJets_SingleLeptFromTbar"),
  ("nof_db_events",         56705550),
  ("nof_db_files",          1306),
  ("fsize_db",              3215810423559),
  ("xsection",              182.76),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 3.22TB; nevents: 56.71M; release: 9_4_6_patch1; last modified: 2018-10-07 05:50:45"),
])

meta_dictionary["/TTJets_TuneCP5_13TeV-amcatnloFXFX-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Oct22_TTJets_TuneCP5_13TeV-amcatnloFXFX-pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v1"),
  ("sample_category",       "TT"),
  ("process_name_specific", "TTJets_amcatnloFXFX"),
  ("nof_db_events",         154280331),
  ("nof_db_files",          2540),
  ("fsize_db",              8610252714647),
  ("xsection",              831.76),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "88.05%; status: VALID; size: 8.61TB; nevents: 154.28M; release: 9_4_6_patch1; last modified: 2018-10-07 00:40:18"),
])

meta_dictionary["/TTJets_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Sep28_TTJets_TuneCP5_13TeV-madgraphMLM-pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1"),
  ("sample_category",       "TT"),
  ("process_name_specific", "TTJets_madgraphMLM"),
  ("nof_db_events",         8026103),
  ("nof_db_files",          260),
  ("fsize_db",              448684514040),
  ("xsection",              831.76),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 448.68GB; nevents: 8.03M; release: 9_4_6_patch1; last modified: 2018-11-21 21:35:02"),
])

meta_dictionary["/TTWH_TuneCP5_13TeV-madgraph-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Oct22_TTWH_TuneCP5_13TeV-madgraph-pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v1"),
  ("sample_category",       "TTWH"),
  ("process_name_specific", "TTWH"),
  ("nof_db_events",         200000),
  ("nof_db_files",          5),
  ("fsize_db",              13473888441),
  ("xsection",              0.001582),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 13.47GB; nevents: 200.00k; release: 9_4_7; last modified: 2018-10-07 19:46:31"),
])

meta_dictionary["/TTZH_TuneCP5_13TeV-madgraph-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Sep28_TTZH_TuneCP5_13TeV-madgraph-pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v1"),
  ("sample_category",       "TTZH"),
  ("process_name_specific", "TTZH"),
  ("nof_db_events",         200000),
  ("nof_db_files",          7),
  ("fsize_db",              13762563086),
  ("xsection",              0.001535),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 13.76GB; nevents: 200.00k; release: 9_4_7; last modified: 2018-07-22 15:56:52"),
])

meta_dictionary["/WWW_4F_TuneCP5_13TeV-amcatnlo-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Sep28_WWW_4F_TuneCP5_13TeV-amcatnlo-pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2"),
  ("sample_category",       "Rares"),
  ("process_name_specific", "WWW"),
  ("nof_db_events",         232300),
  ("nof_db_files",          21),
  ("fsize_db",              11979015983),
  ("xsection",              0.2086),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 11.98GB; nevents: 232.30k; release: 9_4_7; last modified: 2018-10-17 15:35:08"),
])

meta_dictionary["/WWZ_4F_TuneCP5_13TeV-amcatnlo-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Sep28_WWZ_4F_TuneCP5_13TeV-amcatnlo-pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2"),
  ("sample_category",       "Rares"),
  ("process_name_specific", "WWZ"),
  ("nof_db_events",         250000),
  ("nof_db_files",          24),
  ("fsize_db",              13265189749),
  ("xsection",              0.1676),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 13.27GB; nevents: 250.00k; release: 9_4_7; last modified: 2018-10-20 23:53:06"),
])

meta_dictionary["/WZZ_TuneCP5_13TeV-amcatnlo-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Sep28_WZZ_TuneCP5_13TeV-amcatnlo-pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1"),
  ("sample_category",       "Rares"),
  ("process_name_specific", "WZZ"),
  ("nof_db_events",         305200),
  ("nof_db_files",          7),
  ("fsize_db",              15294686519),
  ("xsection",              0.05701),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 15.29GB; nevents: 305.20k; release: 9_4_6_patch1,9_4_7; last modified: 2018-04-20 00:28:06"),
])

meta_dictionary["/ZZZ_TuneCP5_13TeV-amcatnlo-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Sep28_ZZZ_TuneCP5_13TeV-amcatnlo-pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2"),
  ("sample_category",       "Rares"),
  ("process_name_specific", "ZZZ"),
  ("nof_db_events",         250000),
  ("nof_db_files",          22),
  ("fsize_db",              12871064949),
  ("xsection",              0.01473),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 12.87GB; nevents: 250.00k; release: 9_4_7; last modified: 2018-10-24 18:17:57"),
])

meta_dictionary["/WZG_TuneCP5_13TeV-amcatnlo-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Sep28_WZG_TuneCP5_13TeV-amcatnlo-pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1"),
  ("sample_category",       "Rares"),
  ("process_name_specific", "WZG"),
  ("nof_db_events",         1000000),
  ("nof_db_files",          20),
  ("fsize_db",              50788326431),
  ("xsection",              0.04345),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 50.79GB; nevents: 1.00M; release: 9_4_6_patch1; last modified: 2018-04-20 00:23:21"),
])

meta_dictionary["/WGToLNuG_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Sep28_WGToLNuG_TuneCP5_13TeV-madgraphMLM-pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1"),
  ("sample_category",       "Rares"),
  ("process_name_specific", "WGToLNuG"),
  ("nof_db_events",         6283083),
  ("nof_db_files",          134),
  ("fsize_db",              259323657535),
  ("xsection",              464.8),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 259.32GB; nevents: 6.28M; release: 9_4_7; last modified: 2018-10-21 07:04:53"),
])

meta_dictionary["/ZGToLLG_01J_5f_TuneCP5_13TeV-amcatnloFXFX-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v3/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Sep28_ZGToLLG_01J_5f_TuneCP5_13TeV-amcatnloFXFX-pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v3"),
  ("sample_category",       "Rares"),
  ("process_name_specific", "ZGTo2LG_01J"),
  ("nof_db_events",         30490034),
  ("nof_db_files",          526),
  ("fsize_db",              1312540069447),
  ("xsection",              55.59),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 1.31TB; nevents: 30.49M; release: 9_4_7; last modified: 2019-03-10 11:48:36"),
])

meta_dictionary["/TGJets_leptonDecays_TuneCP5_PSweights_13TeV-amcatnlo-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Sep28_TGJets_leptonDecays_TuneCP5_PSweights_13TeV-amcatnlo-pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1"),
  ("sample_category",       "Rares"),
  ("process_name_specific", "TGJets_PSweights"),
  ("nof_db_events",         6649547),
  ("nof_db_files",          110),
  ("fsize_db",              332620767606),
  ("xsection",              1.018),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 332.62GB; nevents: 6.65M; release: 9_4_7; last modified: 2018-07-26 01:58:13"),
])

meta_dictionary["/TTGJets_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Sep28_TTGJets_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v1"),
  ("sample_category",       "Rares"),
  ("process_name_specific", "TTGJets"),
  ("nof_db_events",         12008540),
  ("nof_db_files",          310),
  ("fsize_db",              721586862695),
  ("xsection",              4.215),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 721.59GB; nevents: 12.01M; release: 9_4_7; last modified: 2018-11-22 04:24:05"),
])

meta_dictionary["/TTGJets_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14_ext1-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Sep28_TTGJets_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14_ext1-v2"),
  ("sample_category",       "Rares"),
  ("process_name_specific", "TTGJets_ext1"),
  ("nof_db_events",         8783747),
  ("nof_db_files",          240),
  ("fsize_db",              528701934879),
  ("xsection",              4.215),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 528.70GB; nevents: 8.78M; release: 9_4_7; last modified: 2018-11-11 13:44:37"),
])

meta_dictionary["/tZq_ll_4f_ckm_NLO_TuneCP5_PSweights_13TeV-amcatnlo-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Sep28_tZq_ll_4f_ckm_NLO_TuneCP5_PSweights_13TeV-amcatnlo-pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v2"),
  ("sample_category",       "Rares"),
  ("process_name_specific", "tZq_ll_4f_PSweights"),
  ("nof_db_events",         13276146),
  ("nof_db_files",          211),
  ("fsize_db",              748393512503),
  ("xsection",              0.07358),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 748.39GB; nevents: 13.28M; release: 9_4_6_patch1; last modified: 2018-10-07 10:39:27"),
])

meta_dictionary["/WpWpJJ_EWK-QCD_TuneCP5_13TeV-madgraph-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Sep28_WpWpJJ_EWK-QCD_TuneCP5_13TeV-madgraph-pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1"),
  ("sample_category",       "Rares"),
  ("process_name_specific", "WpWpJJ_EWK_QCD"),
  ("nof_db_events",         149000),
  ("nof_db_files",          21),
  ("fsize_db",              8401827223),
  ("xsection",              0.04926),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 8.40GB; nevents: 149.00k; release: 9_4_6_patch1; last modified: 2018-06-18 11:32:50"),
])

meta_dictionary["/WWTo2L2Nu_DoubleScattering_13TeV-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Sep28_WWTo2L2Nu_DoubleScattering_13TeV-pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2"),
  ("sample_category",       "Rares"),
  ("process_name_specific", "WWTo2L2Nu_DoubleScattering"),
  ("nof_db_events",         968000),
  ("nof_db_files",          31),
  ("fsize_db",              37369750968),
  ("xsection",              0.2232),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 37.37GB; nevents: 968.00k; release: 9_4_6_patch1; last modified: 2018-09-07 15:59:55"),
])

meta_dictionary["/TTTT_TuneCP5_13TeV-amcatnlo-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Nov24_TTTT_TuneCP5_13TeV-amcatnlo-pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2"),
  ("sample_category",       "Rares"),
  ("process_name_specific", "TTTT"),
  ("nof_db_events",         1000000),
  ("nof_db_files",          31),
  ("fsize_db",              78458590319),
  ("xsection",              0.008213),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "42.86%; status: VALID; size: 78.46GB; nevents: 1.00M; release: 9_4_6_patch1; last modified: 2019-04-16 00:28:57"),
])

meta_dictionary["/TTTT_TuneCP5_PSweights_13TeV-amcatnlo-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Nov24_TTTT_TuneCP5_PSweights_13TeV-amcatnlo-pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1"),
  ("sample_category",       "Rares"),
  ("process_name_specific", "TTTT_PSweights"),
  ("nof_db_events",         2273928),
  ("nof_db_files",          71),
  ("fsize_db",              177857452203),
  ("xsection",              0.008213),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "56.52%; status: VALID; size: 177.86GB; nevents: 2.27M; release: 9_4_7; last modified: 2018-07-01 06:33:44"),
])

meta_dictionary["/TTTW_TuneCP5_13TeV-madgraph-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Nov24_TTTW_TuneCP5_13TeV-madgraph-pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v2"),
  ("sample_category",       "Rares"),
  ("process_name_specific", "TTTW"),
  ("nof_db_events",         200000),
  ("nof_db_files",          5),
  ("fsize_db",              14414668661),
  ("xsection",              0.000732),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 14.41GB; nevents: 200.00k; release: 9_4_7; last modified: 2018-08-11 09:49:03"),
])

meta_dictionary["/TTTJ_TuneCP5_13TeV-madgraph-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Nov24_TTTJ_TuneCP5_13TeV-madgraph-pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v2"),
  ("sample_category",       "Rares"),
  ("process_name_specific", "TTTJ"),
  ("nof_db_events",         200000),
  ("nof_db_files",          5),
  ("fsize_db",              13736818051),
  ("xsection",              0.000397),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 13.74GB; nevents: 200.00k; release: 9_4_6_patch1; last modified: 2018-10-07 10:52:06"),
])

meta_dictionary["/TTWZ_TuneCP5_13TeV-madgraph-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Sep28_TTWZ_TuneCP5_13TeV-madgraph-pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v1"),
  ("sample_category",       "Rares"),
  ("process_name_specific", "TTWZ"),
  ("nof_db_events",         200000),
  ("nof_db_files",          5),
  ("fsize_db",              13154770289),
  ("xsection",              0.003884),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 13.15GB; nevents: 200.00k; release: 9_4_6_patch1; last modified: 2018-10-20 20:03:38"),
])

meta_dictionary["/TTZZ_TuneCP5_13TeV-madgraph-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Sep28_TTZZ_TuneCP5_13TeV-madgraph-pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v1"),
  ("sample_category",       "Rares"),
  ("process_name_specific", "TTZZ"),
  ("nof_db_events",         200000),
  ("nof_db_files",          5),
  ("fsize_db",              13301434140),
  ("xsection",              0.001982),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 13.30GB; nevents: 200.00k; release: 9_4_7; last modified: 2018-10-05 16:00:49"),
])

meta_dictionary["/VHToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Sep28_VHToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2"),
  ("sample_category",       "VH"),
  ("process_name_specific", "VHToNonbb_M125"),
  ("nof_db_events",         918508),
  ("nof_db_files",          35),
  ("fsize_db",              44015654097),
  ("xsection",              0.9425),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 44.02GB; nevents: 918.51k; release: 9_4_6_patch1; last modified: 2018-07-07 21:48:41"),
])

meta_dictionary["/ZH_HToBB_ZToLL_M125_13TeV_powheg_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Sep28_ZH_HToBB_ZToLL_M125_13TeV_powheg_pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1"),
  ("sample_category",       "VH"),
  ("process_name_specific", "ZH_HToBB_ZToLL"),
  ("nof_db_events",         4816186),
  ("nof_db_files",          75),
  ("fsize_db",              243231917749),
  ("xsection",              0.05198),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 243.23GB; nevents: 4.82M; release: 9_4_6_patch1; last modified: 2018-04-20 01:16:59"),
])

meta_dictionary["/ZHToTauTau_M125_13TeV_powheg_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Sep28_ZHToTauTau_M125_13TeV_powheg_pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1"),
  ("sample_category",       "VH"),
  ("process_name_specific", "ZHToTauTau"),
  ("nof_db_events",         4940230),
  ("nof_db_files",          75),
  ("fsize_db",              231991011973),
  ("xsection",              0.05544),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 231.99GB; nevents: 4.94M; release: 9_4_6_patch1; last modified: 2018-04-20 00:29:21"),
])

meta_dictionary["/DYJetsToLL_M-10to50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Sep28_DYJetsToLL_M-10to50_TuneCP5_13TeV-madgraphMLM-pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1"),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DYJetsToLL_M-10to50"),
  ("nof_db_events",         39521230),
  ("nof_db_files",          477),
  ("fsize_db",              1379092540630),
  ("xsection",              18610.0),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 1.38TB; nevents: 39.52M; release: 9_4_7; last modified: 2018-10-06 03:25:44"),
])

meta_dictionary["/DYJetsToLL_M-10to50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14_ext1-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Sep28_DYJetsToLL_M-10to50_TuneCP5_13TeV-madgraphMLM-pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14_ext1-v2"),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DYJetsToLL_M-10to50_ext1"),
  ("nof_db_events",         39536839),
  ("nof_db_files",          480),
  ("fsize_db",              1424731750804),
  ("xsection",              18610.0),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 1.42TB; nevents: 39.54M; release: 9_4_7; last modified: 2019-02-06 20:17:22"),
])

meta_dictionary["/DYJetsToLL_M-4to50_HT-100to200_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Sep28_DYJetsToLL_M-4to50_HT-100to200_TuneCP5_13TeV-madgraphMLM-pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v1"),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DYJetsToLL_M-4to50_HT-100to200"),
  ("nof_db_events",         9029117),
  ("nof_db_files",          106),
  ("fsize_db",              401052735767),
  ("xsection",              239.04),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 401.05GB; nevents: 9.03M; release: 9_4_6_patch1; last modified: 2019-02-02 05:51:42"),
])

meta_dictionary["/DYJetsToLL_M-4to50_HT-100to200_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14_ext1-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Sep28_DYJetsToLL_M-4to50_HT-100to200_TuneCP5_13TeV-madgraphMLM-pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14_ext1-v"),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DYJetsToLL_M-4to50_HT-100to200_ext1"),
  ("nof_db_events",         1026278),
  ("nof_db_files",          15),
  ("fsize_db",              44369238206),
  ("xsection",              239.04),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 44.37GB; nevents: 1.03M; release: 9_4_6_patch1; last modified: 2018-04-18 00:09:22"),
])

meta_dictionary["/DYJetsToLL_M-4to50_HT-200to400_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Sep28_DYJetsToLL_M-4to50_HT-200to400_TuneCP5_13TeV-madgraphMLM-pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v1"),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DYJetsToLL_M-4to50_HT-200to400"),
  ("nof_db_events",         1065941),
  ("nof_db_files",          56),
  ("fsize_db",              52509999108),
  ("xsection",              63.72),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 52.51GB; nevents: 1.07M; release: 9_4_7; last modified: 2018-10-25 01:18:19"),
])

meta_dictionary["/DYJetsToLL_M-4to50_HT-200to400_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14_ext1-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Sep28_DYJetsToLL_M-4to50_HT-200to400_TuneCP5_13TeV-madgraphMLM-pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14_ext1-v"),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DYJetsToLL_M-4to50_HT-200to400_ext1"),
  ("nof_db_events",         1021757),
  ("nof_db_files",          19),
  ("fsize_db",              48889722830),
  ("xsection",              63.72),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 48.89GB; nevents: 1.02M; release: 9_4_7; last modified: 2018-05-18 04:51:48"),
])

meta_dictionary["/DYJetsToLL_M-4to50_HT-400to600_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Sep28_DYJetsToLL_M-4to50_HT-400to600_TuneCP5_13TeV-madgraphMLM-pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1"),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DYJetsToLL_M-4to50_HT-400to600"),
  ("nof_db_events",         2067660),
  ("nof_db_files",          32),
  ("fsize_db",              111643815539),
  ("xsection",              6.729),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 111.64GB; nevents: 2.07M; release: 9_4_7; last modified: 2018-10-14 06:43:37"),
])

meta_dictionary["/DYJetsToLL_M-4to50_HT-400to600_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14_ext1-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Sep28_DYJetsToLL_M-4to50_HT-400to600_TuneCP5_13TeV-madgraphMLM-pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14_ext1-v"),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DYJetsToLL_M-4to50_HT-400to600_ext1"),
  ("nof_db_events",         994584),
  ("nof_db_files",          19),
  ("fsize_db",              53407812926),
  ("xsection",              6.729),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 53.41GB; nevents: 994.58k; release: 9_4_6_patch1; last modified: 2018-04-19 18:21:21"),
])

meta_dictionary["/DYJetsToLL_M-4to50_HT-600toInf_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Sep28_DYJetsToLL_M-4to50_HT-600toInf_TuneCP5_13TeV-madgraphMLM-pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1"),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DYJetsToLL_M-4to50_HT-600toInf"),
  ("nof_db_events",         1988861),
  ("nof_db_files",          34),
  ("fsize_db",              116733344895),
  ("xsection",              2.1692),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "90.0%; status: VALID; size: 116.73GB; nevents: 1.99M; release: 9_4_6_patch1; last modified: 2018-05-18 15:32:44"),
])

meta_dictionary["/DYJetsToLL_M-4to50_HT-600toInf_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14_ext1-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Oct22_DYJetsToLL_M-4to50_HT-600toInf_TuneCP5_13TeV-madgraphMLM-pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14_ext1-v"),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DYJetsToLL_M-4to50_HT-600toInf_ext1"),
  ("nof_db_events",         942875),
  ("nof_db_files",          48),
  ("fsize_db",              56015594969),
  ("xsection",              2.1692),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 56.02GB; nevents: 942.88k; release: 9_4_6_patch1; last modified: 2018-09-06 04:12:00"),
])

meta_dictionary["/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017RECOSIMstep_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Sep28_DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8__RunIIFall17MiniAODv2-PU2017RECOSIMstep_12Apr2018_94X_mc2017_realistic_v14-v1"),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DYJetsToLL_M-50"),
  ("nof_db_events",         48675378),
  ("nof_db_files",          553),
  ("fsize_db",              1989278749780),
  ("xsection",              6077.22),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 1.99TB; nevents: 48.68M; release: 9_4_6_patch1; last modified: 2018-04-26 12:18:24"),
])

meta_dictionary["/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017RECOSIMstep_12Apr2018_94X_mc2017_realistic_v14_ext1-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Sep28_DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8__RunIIFall17MiniAODv2-PU2017RECOSIMstep_12Apr2018_94X_mc2017_realistic_v14_ext1-v1"),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DYJetsToLL_M-50_ext1"),
  ("nof_db_events",         49125561),
  ("nof_db_files",          591),
  ("fsize_db",              2002707381991),
  ("xsection",              6077.22),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 2.00TB; nevents: 49.13M; release: 9_4_6_patch1; last modified: 2018-04-23 22:46:40"),
])

meta_dictionary["/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Sep28_DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v1"),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DYJetsToLL_M-50_amcatnloFXFX"),
  ("nof_db_events",         27529915),
  ("nof_db_files",          324),
  ("fsize_db",              1129729744374),
  ("xsection",              6077.22),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 1.13TB; nevents: 27.53M; release: 9_4_7; last modified: 2019-03-15 16:44:40"),
])

meta_dictionary["/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14_ext1-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Sep28_DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14_ext1-v1"),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DYJetsToLL_M-50_amcatnloFXFX_ext1"),
  ("nof_db_events",         182217609),
  ("nof_db_files",          2005),
  ("fsize_db",              7474232515523),
  ("xsection",              6077.22),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 7.47TB; nevents: 182.22M; release: 9_4_7; last modified: 2018-12-02 07:40:50"),
])

meta_dictionary["/DY1JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14_ext1-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Sep28_DY1JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14_ext1-v1"),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DY1JetsToLL_M-50_ext1"),
  ("nof_db_events",         34859434),
  ("nof_db_files",          417),
  ("fsize_db",              1462619517307),
  ("xsection",              998.61),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 1.46TB; nevents: 34.86M; release: 9_4_6_patch1; last modified: 2018-04-20 01:40:36"),
])

meta_dictionary["/DY1JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Sep28_DY1JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v1"),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DY1JetsToLL_M-50"),
  ("nof_db_events",         42331295),
  ("nof_db_files",          492),
  ("fsize_db",              1818087283471),
  ("xsection",              998.61),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 1.82TB; nevents: 42.33M; release: 9_4_7; last modified: 2018-05-28 20:31:22"),
])

meta_dictionary["/DY2JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Sep28_DY2JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1"),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DY2JetsToLL_M-50"),
  ("nof_db_events",         88895),
  ("nof_db_files",          2),
  ("fsize_db",              4131753194),
  ("xsection",              349.25),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 4.13GB; nevents: 88.89k; release: 9_4_6_patch1; last modified: 2018-06-03 02:31:14"),
])

meta_dictionary["/DY2JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14_ext1-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Sep28_DY2JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14_ext1-v2"),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DY2JetsToLL_M-50_ext1"),
  ("nof_db_events",         10037851),
  ("nof_db_files",          163),
  ("fsize_db",              464730818230),
  ("xsection",              349.25),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 464.73GB; nevents: 10.04M; release: 9_4_7; last modified: 2019-02-05 04:01:05"),
])

meta_dictionary["/DY3JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Sep28_DY3JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1"),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DY3JetsToLL_M-50"),
  ("nof_db_events",         5748466),
  ("nof_db_files",          84),
  ("fsize_db",              276614009421),
  ("xsection",              127.52),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 276.61GB; nevents: 5.75M; release: 9_4_6_patch1; last modified: 2018-08-01 04:29:16"),
])

meta_dictionary["/DY3JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14_ext1-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Sep28_DY3JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14_ext1-v2"),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DY3JetsToLL_M-50_ext1"),
  ("nof_db_events",         1149467),
  ("nof_db_files",          34),
  ("fsize_db",              55739563882),
  ("xsection",              127.52),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 55.74GB; nevents: 1.15M; release: 9_4_6_patch1; last modified: 2019-05-01 09:28:29"),
])

meta_dictionary["/DY4JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_v2_94X_mc2017_realistic_v14-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Sep28_DY4JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_v2_94X_mc2017_realistic_v14-v2"),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DY4JetsToLL_M-50"),
  ("nof_db_events",         4328648),
  ("nof_db_files",          75),
  ("fsize_db",              229309195986),
  ("xsection",              50.039),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 229.31GB; nevents: 4.33M; release: 9_4_6_patch1; last modified: 2018-10-07 10:25:43"),
])

meta_dictionary["/DYJetsToLL_M-50_HT-70to100_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Sep28_DYJetsToLL_M-50_HT-70to100_TuneCP5_13TeV-madgraphMLM-pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1"),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DYJetsToLL_M50_HT70to100"),
  ("nof_db_events",         9344037),
  ("nof_db_files",          207),
  ("fsize_db",              429654206472),
  ("xsection",              167.33),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 429.65GB; nevents: 9.34M; release: 9_4_6_patch1; last modified: 2018-09-07 17:40:18"),
])

meta_dictionary["/DYJetsToLL_M-50_HT-100to200_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Sep28_DYJetsToLL_M-50_HT-100to200_TuneCP5_13TeV-madgraphMLM-pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v"),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DYJetsToLL_M50_HT100to200"),
  ("nof_db_events",         11197488),
  ("nof_db_files",          172),
  ("fsize_db",              547433166562),
  ("xsection",              183.53),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 547.43GB; nevents: 11.20M; release: 9_4_7; last modified: 2018-09-06 02:28:37"),
])

meta_dictionary["/DYJetsToLL_M-50_HT-100to200_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14_ext1-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Sep28_DYJetsToLL_M-50_HT-100to200_TuneCP5_13TeV-madgraphMLM-pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14_ext1-v1"),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DYJetsToLL_M50_HT100to200_ext1"),
  ("nof_db_events",         3950339),
  ("nof_db_files",          61),
  ("fsize_db",              186406431655),
  ("xsection",              183.53),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 186.41GB; nevents: 3.95M; release: 9_4_6_patch1; last modified: 2018-04-20 12:32:47"),
])

meta_dictionary["/DYJetsToLL_M-50_HT-200to400_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Sep28_DYJetsToLL_M-50_HT-200to400_TuneCP5_13TeV-madgraphMLM-pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2"),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DYJetsToLL_M50_HT200to400"),
  ("nof_db_events",         10728447),
  ("nof_db_files",          159),
  ("fsize_db",              576131281371),
  ("xsection",              55.411),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 576.13GB; nevents: 10.73M; release: 9_4_6_patch1; last modified: 2018-10-05 06:39:30"),
])

meta_dictionary["/DYJetsToLL_M-50_HT-200to400_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14_ext1-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Sep28_DYJetsToLL_M-50_HT-200to400_TuneCP5_13TeV-madgraphMLM-pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14_ext1-v1"),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DYJetsToLL_M50_HT200to400_ext1"),
  ("nof_db_events",         1200863),
  ("nof_db_files",          22),
  ("fsize_db",              63472314509),
  ("xsection",              55.411),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 63.47GB; nevents: 1.20M; release: 9_4_6_patch1; last modified: 2018-04-20 01:49:19"),
])

meta_dictionary["/DYJetsToLL_M-50_HT-400to600_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Sep28_DYJetsToLL_M-50_HT-400to600_TuneCP5_13TeV-madgraphMLM-pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v"),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DYJetsToLL_M50_HT400to600"),
  ("nof_db_events",         10219524),
  ("nof_db_files",          193),
  ("fsize_db",              605120374708),
  ("xsection",              7.9592),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 605.12GB; nevents: 10.22M; release: 9_4_6_patch1; last modified: 2018-10-04 16:55:21"),
])

meta_dictionary["/DYJetsToLL_M-50_HT-400to600_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14_ext1-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Sep28_DYJetsToLL_M-50_HT-400to600_TuneCP5_13TeV-madgraphMLM-pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14_ext1-v1"),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DYJetsToLL_M50_HT400to600_ext1"),
  ("nof_db_events",         1124294),
  ("nof_db_files",          23),
  ("fsize_db",              65482538135),
  ("xsection",              7.9592),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 65.48GB; nevents: 1.12M; release: 9_4_6_patch1; last modified: 2018-04-20 00:54:12"),
])

meta_dictionary["/DYJetsToLL_M-50_HT-600to800_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Oct22_DYJetsToLL_M-50_HT-600to800_TuneCP5_13TeV-madgraphMLM-pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v"),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DYJetsToLL_M50_HT600to800"),
  ("nof_db_events",         8743640),
  ("nof_db_files",          183),
  ("fsize_db",              535469359588),
  ("xsection",              2.0041),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 535.47GB; nevents: 8.74M; release: 9_4_7; last modified: 2018-09-26 06:53:39"),
])

meta_dictionary["/DYJetsToLL_M-50_HT-800to1200_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Sep28_DYJetsToLL_M-50_HT-800to1200_TuneCP5_13TeV-madgraphMLM-pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-"),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DYJetsToLL_M50_HT800to1200"),
  ("nof_db_events",         3114980),
  ("nof_db_files",          66),
  ("fsize_db",              196397396234),
  ("xsection",              0.92367),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 196.40GB; nevents: 3.11M; release: 9_4_7; last modified: 2018-10-17 14:23:53"),
])

meta_dictionary["/DYJetsToLL_M-50_HT-1200to2500_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Nov24_DYJetsToLL_M-50_HT-1200to2500_TuneCP5_13TeV-madgraphMLM-pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1"),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DYJetsToLL_M50_HT1200to2500"),
  ("nof_db_events",         625517),
  ("nof_db_files",          15),
  ("fsize_db",              41980141603),
  ("xsection",              0.22025),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 41.98GB; nevents: 625.52k; release: 9_4_6_patch1; last modified: 2018-04-20 00:43:19"),
])

meta_dictionary["/DYJetsToLL_M-50_HT-2500toInf_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Nov24_DYJetsToLL_M-50_HT-2500toInf_TuneCP5_13TeV-madgraphMLM-pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-"),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DYJetsToLL_M50_HT2500toInf"),
  ("nof_db_events",         419308),
  ("nof_db_files",          10),
  ("fsize_db",              30462850223),
  ("xsection",              0.004007),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 30.46GB; nevents: 419.31k; release: 9_4_6_patch1; last modified: 2018-10-06 02:51:56"),
])

meta_dictionary["/DYBBJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Sep28_DYBBJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1"),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DYBBJetsToLL_M-50"),
  ("nof_db_events",         2725626),
  ("nof_db_files",          46),
  ("fsize_db",              133741432740),
  ("xsection",              14.6),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 133.74GB; nevents: 2.73M; release: 9_4_6_patch1; last modified: 2018-04-19 22:53:50"),
])

meta_dictionary["/DYBBJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14_ext1-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Sep28_DYBBJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14_ext1-v1"),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DYBBJetsToLL_M-50_ext1"),
  ("nof_db_events",         2375576),
  ("nof_db_files",          121),
  ("fsize_db",              118040727435),
  ("xsection",              14.6),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 118.04GB; nevents: 2.38M; release: 9_4_7; last modified: 2018-11-23 11:37:26"),
])

meta_dictionary["/WJetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v3/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Sep28_WJetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v3"),
  ("sample_category",       "EWK"),
  ("process_name_specific", "WJetsToLNu_madgraphMLM"),
  ("nof_db_events",         30008250),
  ("nof_db_files",          490),
  ("fsize_db",              1182942851062),
  ("xsection",              61526.7),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 1.18TB; nevents: 30.01M; release: 9_4_6_patch1; last modified: 2019-07-30 06:07:09"),
])

meta_dictionary["/WJetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14_ext1-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Sep28_WJetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14_ext1-v2"),
  ("sample_category",       "EWK"),
  ("process_name_specific", "WJetsToLNu_madgraphMLM_ext1"),
  ("nof_db_events",         44881137),
  ("nof_db_files",          746),
  ("fsize_db",              1766214547805),
  ("xsection",              61526.7),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 1.77TB; nevents: 44.88M; release: 9_4_6_patch1; last modified: 2018-07-26 02:31:57"),
])

meta_dictionary["/W1JetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v3/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Sep28_W1JetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v3"),
  ("sample_category",       "EWK"),
  ("process_name_specific", "W1JetsToLNu"),
  ("nof_db_events",         54147812),
  ("nof_db_files",          801),
  ("fsize_db",              2175397601720),
  ("xsection",              9442.49),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 2.18TB; nevents: 54.15M; release: 9_4_6_patch1; last modified: 2018-08-24 10:17:33"),
])

meta_dictionary["/W2JetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v5/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Sep28_W2JetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v5"),
  ("sample_category",       "EWK"),
  ("process_name_specific", "W2JetsToLNu"),
  ("nof_db_events",         32368249),
  ("nof_db_files",          522),
  ("fsize_db",              1391019305711),
  ("xsection",              3252.49),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 1.39TB; nevents: 32.37M; release: 9_4_6_patch1; last modified: 2019-04-18 00:31:35"),
])

meta_dictionary["/W3JetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Sep28_W3JetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1"),
  ("sample_category",       "EWK"),
  ("process_name_specific", "W3JetsToLNu"),
  ("nof_db_events",         19700377),
  ("nof_db_files",          250),
  ("fsize_db",              868954430671),
  ("xsection",              1153.42),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 868.95GB; nevents: 19.70M; release: 9_4_6_patch1; last modified: 2018-04-20 18:55:18"),
])

meta_dictionary["/W4JetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Sep28_W4JetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v2"),
  ("sample_category",       "EWK"),
  ("process_name_specific", "W4JetsToLNu"),
  ("nof_db_events",         11103685),
  ("nof_db_files",          185),
  ("fsize_db",              544022661408),
  ("xsection",              634.05),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 544.02GB; nevents: 11.10M; release: 9_4_7; last modified: 2018-11-19 21:42:04"),
])

meta_dictionary["/WJetsToLNu_HT-70To100_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Sep28_WJetsToLNu_HT-70To100_TuneCP5_13TeV-madgraphMLM-pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1"),
  ("sample_category",       "EWK"),
  ("process_name_specific", "WJetsToLNu_HT70To100"),
  ("nof_db_events",         22255124),
  ("nof_db_files",          403),
  ("fsize_db",              957900452414),
  ("xsection",              1504.92),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 957.90GB; nevents: 22.26M; release: 9_4_7; last modified: 2019-01-13 04:33:38"),
])

meta_dictionary["/WJetsToLNu_HT-100To200_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Sep28_WJetsToLNu_HT-100To200_TuneCP5_13TeV-madgraphMLM-pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2"),
  ("sample_category",       "EWK"),
  ("process_name_specific", "WJetsToLNu_HT100To200"),
  ("nof_db_events",         35862893),
  ("nof_db_files",          735),
  ("fsize_db",              1632440553612),
  ("xsection",              1625.08),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 1.63TB; nevents: 35.86M; release: 9_4_6_patch1; last modified: 2018-07-16 22:47:23"),
])

meta_dictionary["/WJetsToLNu_HT-200To400_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Sep28_WJetsToLNu_HT-200To400_TuneCP5_13TeV-madgraphMLM-pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1"),
  ("sample_category",       "EWK"),
  ("process_name_specific", "WJetsToLNu_HT200To400"),
  ("nof_db_events",         21250517),
  ("nof_db_files",          400),
  ("fsize_db",              1058111782457),
  ("xsection",              477.96),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 1.06TB; nevents: 21.25M; release: 9_4_6_patch1; last modified: 2018-06-11 22:53:32"),
])

meta_dictionary["/WJetsToLNu_HT-400To600_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Sep28_WJetsToLNu_HT-400To600_TuneCP5_13TeV-madgraphMLM-pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1"),
  ("sample_category",       "EWK"),
  ("process_name_specific", "WJetsToLNu_HT400To600"),
  ("nof_db_events",         14313274),
  ("nof_db_files",          314),
  ("fsize_db",              780224610750),
  ("xsection",              67.441),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 780.22GB; nevents: 14.31M; release: 9_4_6_patch1; last modified: 2018-05-28 05:52:21"),
])

meta_dictionary["/WJetsToLNu_HT-600To800_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Sep28_WJetsToLNu_HT-600To800_TuneCP5_13TeV-madgraphMLM-pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1"),
  ("sample_category",       "EWK"),
  ("process_name_specific", "WJetsToLNu_HT600To800"),
  ("nof_db_events",         21709087),
  ("nof_db_files",          488),
  ("fsize_db",              1256446599197),
  ("xsection",              15.096),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 1.26TB; nevents: 21.71M; release: 9_4_6_patch1; last modified: 2018-06-17 00:32:54"),
])

meta_dictionary["/WJetsToLNu_HT-800To1200_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Sep28_WJetsToLNu_HT-800To1200_TuneCP5_13TeV-madgraphMLM-pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1"),
  ("sample_category",       "EWK"),
  ("process_name_specific", "WJetsToLNu_HT800To1200"),
  ("nof_db_events",         20466692),
  ("nof_db_files",          488),
  ("fsize_db",              1227636244434),
  ("xsection",              6.3626),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 1.23TB; nevents: 20.47M; release: 9_4_6_patch1; last modified: 2018-06-26 12:59:36"),
])

meta_dictionary["/WJetsToLNu_HT-1200To2500_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Sep28_WJetsToLNu_HT-1200To2500_TuneCP5_13TeV-madgraphMLM-pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1"),
  ("sample_category",       "EWK"),
  ("process_name_specific", "WJetsToLNu_HT1200To2500"),
  ("nof_db_events",         20258624),
  ("nof_db_files",          551),
  ("fsize_db",              1289100671636),
  ("xsection",              1.2658),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 1.29TB; nevents: 20.26M; release: 9_4_6_patch1; last modified: 2018-06-25 05:52:24"),
])

meta_dictionary["/WJetsToLNu_HT-2500ToInf_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v3/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Oct22_WJetsToLNu_HT-2500ToInf_TuneCP5_13TeV-madgraphMLM-pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v3"),
  ("sample_category",       "EWK"),
  ("process_name_specific", "WJetsToLNu_HT2500ToInf"),
  ("nof_db_events",         21495421),
  ("nof_db_files",          616),
  ("fsize_db",              1489610697179),
  ("xsection",              0.009405),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "98.61%; status: VALID; size: 1.49TB; nevents: 21.50M; release: 9_4_6_patch1; last modified: 2018-07-06 12:31:23"),
])

meta_dictionary["/WWTo2L2Nu_NNPDF31_TuneCP5_13TeV-powheg-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Sep28_WWTo2L2Nu_NNPDF31_TuneCP5_13TeV-powheg-pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1"),
  ("sample_category",       "WW"),
  ("process_name_specific", "WWTo2L2Nu"),
  ("nof_db_events",         2000000),
  ("nof_db_files",          25),
  ("fsize_db",              85721560743),
  ("xsection",              12.2),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 85.72GB; nevents: 2.00M; release: 9_4_7; last modified: 2018-10-12 07:57:13"),
])

meta_dictionary["/WWTo2L2Nu_NNPDF31_TuneCP5_PSweights_13TeV-powheg-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14_ext1-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Sep28_WWTo2L2Nu_NNPDF31_TuneCP5_PSweights_13TeV-powheg-pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14_ext1-v1"),
  ("sample_category",       "WW"),
  ("process_name_specific", "WWTo2L2Nu_PSweights_ext1"),
  ("nof_db_events",         2000000),
  ("nof_db_files",          25),
  ("fsize_db",              85800202496),
  ("xsection",              12.2),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 85.80GB; nevents: 2.00M; release: 9_4_6_patch1; last modified: 2018-04-20 00:58:14"),
])

meta_dictionary["/WWToLNuQQ_NNPDF31_TuneCP5_13TeV-powheg-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Sep28_WWToLNuQQ_NNPDF31_TuneCP5_13TeV-powheg-pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v1"),
  ("sample_category",       "WW"),
  ("process_name_specific", "WWToLNuQQ"),
  ("nof_db_events",         8782525),
  ("nof_db_files",          122),
  ("fsize_db",              386260476875),
  ("xsection",              50.45),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 386.26GB; nevents: 8.78M; release: 9_4_7; last modified: 2018-10-06 23:56:04"),
])

meta_dictionary["/WWToLNuQQ_NNPDF31_TuneCP5_13TeV-powheg-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14_ext1-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Sep28_WWToLNuQQ_NNPDF31_TuneCP5_13TeV-powheg-pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14_ext1-v1"),
  ("sample_category",       "WW"),
  ("process_name_specific", "WWToLNuQQ_ext1"),
  ("nof_db_events",         9994191),
  ("nof_db_files",          127),
  ("fsize_db",              429884785891),
  ("xsection",              50.45),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 429.88GB; nevents: 9.99M; release: 9_4_6_patch1; last modified: 2018-04-21 09:47:36"),
])

meta_dictionary["/WWToLNuQQ_NNPDF31_TuneCP5_PSweights_13TeV-powheg-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14_ext1-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Sep28_WWToLNuQQ_NNPDF31_TuneCP5_PSweights_13TeV-powheg-pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14_ext1-v1"),
  ("sample_category",       "WW"),
  ("process_name_specific", "WWToLNuQQ_PSweights_ext1"),
  ("nof_db_events",         8785360),
  ("nof_db_files",          100),
  ("fsize_db",              386842370187),
  ("xsection",              50.45),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 386.84GB; nevents: 8.79M; release: 9_4_6_patch1; last modified: 2018-07-18 14:24:34"),
])

meta_dictionary["/WWTo1L1Nu2Q_13TeV_amcatnloFXFX_madspin_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Sep28_WWTo1L1Nu2Q_13TeV_amcatnloFXFX_madspin_pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1"),
  ("sample_category",       "WW"),
  ("process_name_specific", "WWTo1L1Nu2Q"),
  ("nof_db_events",         5054286),
  ("nof_db_files",          62),
  ("fsize_db",              215173204051),
  ("xsection",              50.45),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 215.17GB; nevents: 5.05M; release: 9_4_6_patch1; last modified: 2018-04-20 18:49:57"),
])

meta_dictionary["/WWTo4Q_NNPDF31_TuneCP5_13TeV-powheg-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Sep28_WWTo4Q_NNPDF31_TuneCP5_13TeV-powheg-pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v1"),
  ("sample_category",       "WW"),
  ("process_name_specific", "WWTo4Q"),
  ("nof_db_events",         2000000),
  ("nof_db_files",          24),
  ("fsize_db",              89197790862),
  ("xsection",              52.15),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 89.20GB; nevents: 2.00M; release: 9_4_7; last modified: 2018-10-14 03:37:55"),
])

meta_dictionary["/WWTo4Q_NNPDF31_TuneCP5_PSweights_13TeV-powheg-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14_ext1-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Sep28_WWTo4Q_NNPDF31_TuneCP5_PSweights_13TeV-powheg-pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14_ext1-v1"),
  ("sample_category",       "WW"),
  ("process_name_specific", "WWTo4Q_PSweights_ext1"),
  ("nof_db_events",         1976360),
  ("nof_db_files",          26),
  ("fsize_db",              88368465560),
  ("xsection",              52.15),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 88.37GB; nevents: 1.98M; release: 9_4_6_patch1; last modified: 2018-04-20 01:33:15"),
])

meta_dictionary["/WZTo3LNu_TuneCP5_13TeV-amcatnloFXFX-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Sep28_WZTo3LNu_TuneCP5_13TeV-amcatnloFXFX-pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v1"),
  ("sample_category",       "WZ"),
  ("process_name_specific", "WZTo3LNu"),
  ("nof_db_events",         10987679),
  ("nof_db_files",          131),
  ("fsize_db",              478392232798),
  ("xsection",              4.43),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 478.39GB; nevents: 10.99M; release: 9_4_6_patch1; last modified: 2018-10-12 09:40:47"),
])

meta_dictionary["/WZTo3LNu_13TeV-powheg-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Sep28_WZTo3LNu_13TeV-powheg-pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2"),
  ("sample_category",       "WZ"),
  ("process_name_specific", "WZTo3LNu_powheg"),
  ("nof_db_events",         976400),
  ("nof_db_files",          41),
  ("fsize_db",              42009768335),
  ("xsection",              4.43),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 42.01GB; nevents: 976.40k; release: 9_4_6_patch1; last modified: 2018-10-12 07:53:19"),
])

meta_dictionary["/WZTo3LNu_0Jets_MLL-4to50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Sep28_WZTo3LNu_0Jets_MLL-4to50_TuneCP5_13TeV-madgraphMLM-pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1"),
  ("sample_category",       "WZ"),
  ("process_name_specific", "WZTo3LNu_0Jets_MLL-4to50"),
  ("nof_db_events",         488461),
  ("nof_db_files",          24),
  ("fsize_db",              21565472983),
  ("xsection",              2.3986),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 21.57GB; nevents: 488.46k; release: 9_4_7; last modified: 2018-09-26 11:09:41"),
])

meta_dictionary["/WZTo3LNu_0Jets_MLL-50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v3/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Sep28_WZTo3LNu_0Jets_MLL-50_TuneCP5_13TeV-madgraphMLM-pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v3"),
  ("sample_category",       "WZ"),
  ("process_name_specific", "WZTo3LNu_0Jets_MLL-50"),
  ("nof_db_events",         473818),
  ("nof_db_files",          24),
  ("fsize_db",              23217296859),
  ("xsection",              0.6067),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 23.22GB; nevents: 473.82k; release: 9_4_6_patch1; last modified: 2018-05-19 01:52:12"),
])

meta_dictionary["/WZTo3LNu_1Jets_MLL-4to50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Sep28_WZTo3LNu_1Jets_MLL-4to50_TuneCP5_13TeV-madgraphMLM-pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1"),
  ("sample_category",       "WZ"),
  ("process_name_specific", "WZTo3LNu_1Jets_MLL-4to50"),
  ("nof_db_events",         506673),
  ("nof_db_files",          22),
  ("fsize_db",              24141156011),
  ("xsection",              0.46107),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 24.14GB; nevents: 506.67k; release: 9_4_7; last modified: 2018-09-19 01:57:44"),
])

meta_dictionary["/WZTo3LNu_1Jets_MLL-50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Sep28_WZTo3LNu_1Jets_MLL-50_TuneCP5_13TeV-madgraphMLM-pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2"),
  ("sample_category",       "WZ"),
  ("process_name_specific", "WZTo3LNu_1Jets_MLL-50"),
  ("nof_db_events",         486727),
  ("nof_db_files",          26),
  ("fsize_db",              25784953540),
  ("xsection",              0.3226),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 25.78GB; nevents: 486.73k; release: 9_4_6_patch1; last modified: 2018-06-29 18:33:36"),
])

meta_dictionary["/WZTo3LNu_2Jets_MLL-4to50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Sep28_WZTo3LNu_2Jets_MLL-4to50_TuneCP5_13TeV-madgraphMLM-pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1"),
  ("sample_category",       "WZ"),
  ("process_name_specific", "WZTo3LNu_2Jets_MLL-4to50"),
  ("nof_db_events",         1433913),
  ("nof_db_files",          75),
  ("fsize_db",              73675561875),
  ("xsection",              0.15607),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 73.68GB; nevents: 1.43M; release: 9_4_7; last modified: 2018-10-04 12:15:15"),
])

meta_dictionary["/WZTo3LNu_2Jets_MLL-50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Sep28_WZTo3LNu_2Jets_MLL-50_TuneCP5_13TeV-madgraphMLM-pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2"),
  ("sample_category",       "WZ"),
  ("process_name_specific", "WZTo3LNu_2Jets_MLL-50"),
  ("nof_db_events",         1835965),
  ("nof_db_files",          80),
  ("fsize_db",              107485243900),
  ("xsection",              0.06314),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 107.49GB; nevents: 1.84M; release: 9_4_6_patch1; last modified: 2018-07-24 01:27:08"),
])

meta_dictionary["/WZTo3LNu_3Jets_MLL-4to50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Sep28_WZTo3LNu_3Jets_MLL-4to50_TuneCP5_13TeV-madgraphMLM-pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1"),
  ("sample_category",       "WZ"),
  ("process_name_specific", "WZTo3LNu_3Jets_MLL-4to50"),
  ("nof_db_events",         2069899),
  ("nof_db_files",          110),
  ("fsize_db",              117165529475),
  ("xsection",              0.06769),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 117.17GB; nevents: 2.07M; release: 9_4_7; last modified: 2018-09-19 01:59:12"),
])

meta_dictionary["/WZTo3LNu_3Jets_MLL-50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Oct22_WZTo3LNu_3Jets_MLL-50_TuneCP5_13TeV-madgraphMLM-pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2"),
  ("sample_category",       "WZ"),
  ("process_name_specific", "WZTo3LNu_3Jets_MLL-50"),
  ("nof_db_events",         1832414),
  ("nof_db_files",          98),
  ("fsize_db",              115010601689),
  ("xsection",              0.090512),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 115.01GB; nevents: 1.83M; release: 9_4_6_patch1; last modified: 2018-07-02 06:51:45"),
])

meta_dictionary["/WZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Sep28_WZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1"),
  ("sample_category",       "WZ"),
  ("process_name_specific", "WZTo2L2Q"),
  ("nof_db_events",         27582164),
  ("nof_db_files",          406),
  ("fsize_db",              1286368112175),
  ("xsection",              5.6),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 1.29TB; nevents: 27.58M; release: 9_4_7; last modified: 2018-05-22 02:51:17"),
])

meta_dictionary["/WZTo1L1Nu2Q_13TeV_amcatnloFXFX_madspin_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Sep28_WZTo1L1Nu2Q_13TeV_amcatnloFXFX_madspin_pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2"),
  ("sample_category",       "WZ"),
  ("process_name_specific", "WZTo1L1Nu2Q"),
  ("nof_db_events",         19086373),
  ("nof_db_files",          309),
  ("fsize_db",              888745631538),
  ("xsection",              10.71),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 888.75GB; nevents: 19.09M; release: 9_4_6_patch1; last modified: 2018-06-28 07:36:24"),
])

meta_dictionary["/ZZTo4L_13TeV_powheg_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Sep28_ZZTo4L_13TeV_powheg_pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v1"),
  ("sample_category",       "ZZ"),
  ("process_name_specific", "ZZTo4L"),
  ("nof_db_events",         6964071),
  ("nof_db_files",          80),
  ("fsize_db",              292257995604),
  ("xsection",              1.256),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 292.26GB; nevents: 6.96M; release: 9_4_7; last modified: 2018-10-12 16:42:30"),
])

meta_dictionary["/ZZTo4L_13TeV_powheg_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14_ext1-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Sep28_ZZTo4L_13TeV_powheg_pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14_ext1-v1"),
  ("sample_category",       "ZZ"),
  ("process_name_specific", "ZZTo4L_ext1"),
  ("nof_db_events",         98091559),
  ("nof_db_files",          1128),
  ("fsize_db",              4014158215850),
  ("xsection",              1.256),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 4.01TB; nevents: 98.09M; release: 9_4_6_patch1; last modified: 2018-04-20 10:25:00"),
])

meta_dictionary["/ZZTo4L_13TeV_powheg_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14_ext2-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Sep28_ZZTo4L_13TeV_powheg_pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14_ext2-v1"),
  ("sample_category",       "ZZ"),
  ("process_name_specific", "ZZTo4L_ext2"),
  ("nof_db_events",         86763486),
  ("nof_db_files",          1623),
  ("fsize_db",              3665584889110),
  ("xsection",              1.256),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 3.67TB; nevents: 86.76M; release: 9_4_7; last modified: 2019-07-23 18:38:31"),
])

meta_dictionary["/ZZTo2L2Nu_13TeV_powheg_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Sep28_ZZTo2L2Nu_13TeV_powheg_pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1"),
  ("sample_category",       "ZZ"),
  ("process_name_specific", "ZZTo2L2Nu"),
  ("nof_db_events",         8744768),
  ("nof_db_files",          112),
  ("fsize_db",              380491063113),
  ("xsection",              0.564),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 380.49GB; nevents: 8.74M; release: 9_4_7; last modified: 2018-10-07 10:37:59"),
])

meta_dictionary["/ZZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Sep28_ZZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1"),
  ("sample_category",       "ZZ"),
  ("process_name_specific", "ZZTo2L2Q"),
  ("nof_db_events",         27840918),
  ("nof_db_files",          409),
  ("fsize_db",              1296656277482),
  ("xsection",              5.52),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 1.30TB; nevents: 27.84M; release: 9_4_7; last modified: 2018-05-15 00:42:20"),
])

meta_dictionary["/QCD_Pt_20to30_bcToE_TuneCP5_13TeV_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Sep28_QCD_Pt_20to30_bcToE_TuneCP5_13TeV_pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v1"),
  ("sample_category",       "QCD"),
  ("process_name_specific", "QCD_Pt20to30_bcToE"),
  ("nof_db_events",         14429805),
  ("nof_db_files",          414),
  ("fsize_db",              557297169649),
  ("xsection",              305400.0),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 557.30GB; nevents: 14.43M; release: 9_4_7; last modified: 2018-11-01 10:07:28"),
])

meta_dictionary["/QCD_Pt_30to80_bcToE_TuneCP5_13TeV_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Sep28_QCD_Pt_30to80_bcToE_TuneCP5_13TeV_pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1"),
  ("sample_category",       "QCD"),
  ("process_name_specific", "QCD_Pt30to80_bcToE"),
  ("nof_db_events",         16073047),
  ("nof_db_files",          186),
  ("fsize_db",              633331988305),
  ("xsection",              361100.0),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 633.33GB; nevents: 16.07M; release: 9_4_6_patch1; last modified: 2018-04-20 00:35:07"),
])

meta_dictionary["/QCD_Pt_80to170_bcToE_TuneCP5_13TeV_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Sep28_QCD_Pt_80to170_bcToE_TuneCP5_13TeV_pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1"),
  ("sample_category",       "QCD"),
  ("process_name_specific", "QCD_Pt80to170_bcToE"),
  ("nof_db_events",         15999466),
  ("nof_db_files",          189),
  ("fsize_db",              711041578903),
  ("xsection",              33820.0),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 711.04GB; nevents: 16.00M; release: 9_4_6_patch1; last modified: 2018-04-20 01:05:40"),
])

meta_dictionary["/QCD_Pt_170to250_bcToE_TuneCP5_13TeV_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Sep28_QCD_Pt_170to250_bcToE_TuneCP5_13TeV_pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1"),
  ("sample_category",       "QCD"),
  ("process_name_specific", "QCD_Pt170to250_bcToE"),
  ("nof_db_events",         9847660),
  ("nof_db_files",          176),
  ("fsize_db",              477892307613),
  ("xsection",              2130.0),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 477.89GB; nevents: 9.85M; release: 9_4_6_patch1; last modified: 2018-04-21 09:48:08"),
])

meta_dictionary["/QCD_Pt_250toInf_bcToE_TuneCP5_13TeV_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Sep28_QCD_Pt_250toInf_bcToE_TuneCP5_13TeV_pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1"),
  ("sample_category",       "QCD"),
  ("process_name_specific", "QCD_Pt250toInf_bcToE"),
  ("nof_db_events",         9996886),
  ("nof_db_files",          187),
  ("fsize_db",              513285807270),
  ("xsection",              563.0),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 513.29GB; nevents: 10.00M; release: 9_4_6_patch1; last modified: 2018-04-20 00:39:27"),
])

meta_dictionary["/QCD_Pt-15to20_EMEnriched_TuneCP5_13TeV_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Sep28_QCD_Pt-15to20_EMEnriched_TuneCP5_13TeV_pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1"),
  ("sample_category",       "QCD"),
  ("process_name_specific", "QCD_Pt15to20_EMEnriched"),
  ("nof_db_events",         11215220),
  ("nof_db_files",          134),
  ("fsize_db",              397192727584),
  ("xsection",              1324000.0),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 397.19GB; nevents: 11.22M; release: 9_4_6_patch1; last modified: 2018-04-20 01:13:01"),
])

meta_dictionary["/QCD_Pt-20to30_EMEnriched_TuneCP5_13TeV_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Sep28_QCD_Pt-20to30_EMEnriched_TuneCP5_13TeV_pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1"),
  ("sample_category",       "QCD"),
  ("process_name_specific", "QCD_Pt20to30_EMEnriched"),
  ("nof_db_events",         11212810),
  ("nof_db_files",          125),
  ("fsize_db",              406252937750),
  ("xsection",              4912000.0),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 406.25GB; nevents: 11.21M; release: 9_4_6_patch1; last modified: 2018-04-20 00:59:51"),
])

meta_dictionary["/QCD_Pt-30to50_EMEnriched_TuneCP5_13TeV_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Sep28_QCD_Pt-30to50_EMEnriched_TuneCP5_13TeV_pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1"),
  ("sample_category",       "QCD"),
  ("process_name_specific", "QCD_Pt30to50_EMEnriched"),
  ("nof_db_events",         14766010),
  ("nof_db_files",          176),
  ("fsize_db",              553990333710),
  ("xsection",              6420000.0),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 553.99GB; nevents: 14.77M; release: 9_4_6_patch1; last modified: 2018-04-26 12:19:20"),
])

meta_dictionary["/QCD_Pt-50to80_EMEnriched_TuneCP5_13TeV_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Sep28_QCD_Pt-50to80_EMEnriched_TuneCP5_13TeV_pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1"),
  ("sample_category",       "QCD"),
  ("process_name_specific", "QCD_Pt50to80_EMEnriched"),
  ("nof_db_events",         10477146),
  ("nof_db_files",          128),
  ("fsize_db",              412202461390),
  ("xsection",              1988000.0),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 412.20GB; nevents: 10.48M; release: 9_4_6_patch1; last modified: 2018-04-20 12:20:18"),
])

meta_dictionary["/QCD_Pt-80to120_EMEnriched_TuneCP5_13TeV_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Sep28_QCD_Pt-80to120_EMEnriched_TuneCP5_13TeV_pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1"),
  ("sample_category",       "QCD"),
  ("process_name_specific", "QCD_Pt80to120_EMEnriched"),
  ("nof_db_events",         9104852),
  ("nof_db_files",          108),
  ("fsize_db",              389362639707),
  ("xsection",              366500.0),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 389.36GB; nevents: 9.10M; release: 9_4_7; last modified: 2018-10-17 12:17:36"),
])

meta_dictionary["/QCD_Pt-120to170_EMEnriched_TuneCP5_13TeV_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Sep28_QCD_Pt-120to170_EMEnriched_TuneCP5_13TeV_pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2"),
  ("sample_category",       "QCD"),
  ("process_name_specific", "QCD_Pt120to170_EMEnriched"),
  ("nof_db_events",         8515107),
  ("nof_db_files",          163),
  ("fsize_db",              385000236556),
  ("xsection",              66510.0),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 385.00GB; nevents: 8.52M; release: 9_4_7; last modified: 2018-09-07 16:00:14"),
])

meta_dictionary["/QCD_Pt-300toInf_EMEnriched_TuneCP5_13TeV_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Sep28_QCD_Pt-300toInf_EMEnriched_TuneCP5_13TeV_pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1"),
  ("sample_category",       "QCD"),
  ("process_name_specific", "QCD_Pt300toInf_EMEnriched"),
  ("nof_db_events",         2874295),
  ("nof_db_files",          49),
  ("fsize_db",              144869144781),
  ("xsection",              1100.0),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 144.87GB; nevents: 2.87M; release: 9_4_6_patch1; last modified: 2018-04-21 10:04:42"),
])

meta_dictionary["/QCD_Pt-15to20_MuEnrichedPt5_TuneCP5_13TeV_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Sep28_QCD_Pt-15to20_MuEnrichedPt5_TuneCP5_13TeV_pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1"),
  ("sample_category",       "QCD"),
  ("process_name_specific", "QCD_Pt15to20_Mu5"),
  ("nof_db_events",         5859904),
  ("nof_db_files",          63),
  ("fsize_db",              216516638901),
  ("xsection",              2811000.0),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 216.52GB; nevents: 5.86M; release: 9_4_6_patch1; last modified: 2018-04-19 22:42:17"),
])

meta_dictionary["/QCD_Pt-20to30_MuEnrichedPt5_TuneCP5_13TeV_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Sep28_QCD_Pt-20to30_MuEnrichedPt5_TuneCP5_13TeV_pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1"),
  ("sample_category",       "QCD"),
  ("process_name_specific", "QCD_Pt20to30_Mu5"),
  ("nof_db_events",         28213684),
  ("nof_db_files",          319),
  ("fsize_db",              1058418704070),
  ("xsection",              2531000.0),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 1.06TB; nevents: 28.21M; release: 9_4_6_patch1; last modified: 2018-04-19 18:10:49"),
])

meta_dictionary["/QCD_Pt-30to50_MuEnrichedPt5_TuneCP5_13TeV_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Sep28_QCD_Pt-30to50_MuEnrichedPt5_TuneCP5_13TeV_pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1"),
  ("sample_category",       "QCD"),
  ("process_name_specific", "QCD_Pt30to50_Mu5"),
  ("nof_db_events",         29030324),
  ("nof_db_files",          325),
  ("fsize_db",              1131094971096),
  ("xsection",              1367000.0),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 1.13TB; nevents: 29.03M; release: 9_4_6_patch1; last modified: 2018-04-20 00:37:37"),
])

meta_dictionary["/QCD_Pt-50to80_MuEnrichedPt5_TuneCP5_13TeV_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Sep28_QCD_Pt-50to80_MuEnrichedPt5_TuneCP5_13TeV_pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1"),
  ("sample_category",       "QCD"),
  ("process_name_specific", "QCD_Pt50to80_Mu5"),
  ("nof_db_events",         24068613),
  ("nof_db_files",          288),
  ("fsize_db",              1004660826025),
  ("xsection",              377900.0),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 1.00TB; nevents: 24.07M; release: 9_4_6_patch1; last modified: 2018-04-20 18:57:38"),
])

meta_dictionary["/QCD_Pt-80to120_MuEnrichedPt5_TuneCP5_13TeV_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Sep28_QCD_Pt-80to120_MuEnrichedPt5_TuneCP5_13TeV_pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1"),
  ("sample_category",       "QCD"),
  ("process_name_specific", "QCD_Pt80to120_Mu5"),
  ("nof_db_events",         23248995),
  ("nof_db_files",          289),
  ("fsize_db",              1035795578059),
  ("xsection",              88620.0),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 1.04TB; nevents: 23.25M; release: 9_4_6_patch1; last modified: 2018-04-20 10:20:52"),
])

meta_dictionary["/QCD_Pt-120to170_MuEnrichedPt5_TuneCP5_13TeV_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Oct22_QCD_Pt-120to170_MuEnrichedPt5_TuneCP5_13TeV_pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1"),
  ("sample_category",       "QCD"),
  ("process_name_specific", "QCD_Pt120to170_Mu5"),
  ("nof_db_events",         20774848),
  ("nof_db_files",          342),
  ("fsize_db",              984472671147),
  ("xsection",              21190.0),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "99.52%; status: VALID; size: 984.47GB; nevents: 20.77M; release: 9_4_6_patch1; last modified: 2018-04-20 00:46:29"),
])

meta_dictionary["/QCD_Pt-170to300_MuEnrichedPt5_TuneCP5_13TeV_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Oct22_QCD_Pt-170to300_MuEnrichedPt5_TuneCP5_13TeV_pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1"),
  ("sample_category",       "QCD"),
  ("process_name_specific", "QCD_Pt170to300_Mu5"),
  ("nof_db_events",         46170668),
  ("nof_db_files",          721),
  ("fsize_db",              2330576867261),
  ("xsection",              7020.0),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 2.33TB; nevents: 46.17M; release: 9_4_6_patch1; last modified: 2018-04-20 01:20:32"),
])

meta_dictionary["/QCD_Pt-300to470_MuEnrichedPt5_TuneCP5_13TeV_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Oct22_QCD_Pt-300to470_MuEnrichedPt5_TuneCP5_13TeV_pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1"),
  ("sample_category",       "QCD"),
  ("process_name_specific", "QCD_Pt300to470_Mu5"),
  ("nof_db_events",         17744779),
  ("nof_db_files",          374),
  ("fsize_db",              989950950093),
  ("xsection",              620.2),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 989.95GB; nevents: 17.74M; release: 9_4_7; last modified: 2018-10-19 01:57:32"),
])

meta_dictionary["/QCD_Pt-470to600_MuEnrichedPt5_TuneCP5_13TeV_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Sep28_QCD_Pt-470to600_MuEnrichedPt5_TuneCP5_13TeV_pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1"),
  ("sample_category",       "QCD"),
  ("process_name_specific", "QCD_Pt470to600_Mu5"),
  ("nof_db_events",         24243589),
  ("nof_db_files",          388),
  ("fsize_db",              1390197744079),
  ("xsection",              59.06),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 1.39TB; nevents: 24.24M; release: 9_4_6_patch1; last modified: 2018-04-20 11:34:40"),
])

meta_dictionary["/QCD_Pt-600to800_MuEnrichedPt5_TuneCP5_13TeV_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Sep28_QCD_Pt-600to800_MuEnrichedPt5_TuneCP5_13TeV_pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1"),
  ("sample_category",       "QCD"),
  ("process_name_specific", "QCD_Pt600to800_Mu5"),
  ("nof_db_events",         17263676),
  ("nof_db_files",          391),
  ("fsize_db",              1040033606810),
  ("xsection",              18.2),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 1.04TB; nevents: 17.26M; release: 9_4_7; last modified: 2019-04-25 18:29:02"),
])

meta_dictionary["/QCD_Pt-800to1000_MuEnrichedPt5_TuneCP5_13TeV_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Sep28_QCD_Pt-800to1000_MuEnrichedPt5_TuneCP5_13TeV_pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1"),
  ("sample_category",       "QCD"),
  ("process_name_specific", "QCD_Pt800to1000_Mu5"),
  ("nof_db_events",         17114527),
  ("nof_db_files",          389),
  ("fsize_db",              1061424382303),
  ("xsection",              3.276),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "92.44%; status: VALID; size: 1.06TB; nevents: 17.11M; release: 9_4_7; last modified: 2019-02-05 03:57:20"),
])

meta_dictionary["/QCD_Pt-1000toInf_MuEnrichedPt5_TuneCP5_13TeV_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2017v2_2019Sep28_QCD_Pt-1000toInf_MuEnrichedPt5_TuneCP5_13TeV_pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1"),
  ("sample_category",       "QCD"),
  ("process_name_specific", "QCD_Pt1000toInf_Mu5"),
  ("nof_db_events",         11596693),
  ("nof_db_files",          257),
  ("fsize_db",              741261028289),
  ("xsection",              1.079),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "85.47%; status: VALID; size: 741.26GB; nevents: 11.60M; release: 9_4_7; last modified: 2018-12-08 11:11:25"),
])


# event statistics by sample category:
# ttH:        25.99M
# ttH_ctcvcp: 9.62M
# tHq:        9.92M
# tHW:        4.72M
# ggH:        30.87M
# qqH:        15.81M
# TTZ:        37.51M
# TTW:        25.74M
# TTWW:       200.00k
# TT:         962.83M
# TTWH:       200.00k
# TTZH:       200.00k
# Rares:      84.72M
# VH:         10.67M
# EWK:        938.88M
# WW:         40.59M
# WZ:         67.76M
# ZZ:         228.40M
# QCD:        399.84M

