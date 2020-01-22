from collections import OrderedDict as OD

# file generated at 2020-01-11 16:52:26 with the following command:
# find_samples.py -V -i ../NanoAOD/test/datasets/txt/datasets_mc_2016_RunIISummer16MiniAODv3.txt -m python/samples/metaDict_2016_mc.py -s ../NanoAOD/test/datasets/txt/sum_datasets_2016_RunIISummer16MiniAODv3.txt -c python/samples/sampleLocations_2016_nanoAOD.txt

meta_dictionary = OD()


### event sums

sum_events = { 
  ("THQ_ctcvcp", "THQ_ctcvcp_CP5"),
  ("THW_ctcvcp", "THW_ctcvcp_CP5"),
  ("GluGluHToBB_M125", "GluGluHToBB_M125_ext1"),
  ("VBFHToBB_M125", "VBFHToBB_M125_ext1"),
  ("VBFHToGG_M125_ext1", "VBFHToGG_M125_ext2"),
  ("TTZToLL_M10_ext2", "TTZToLL_M10_ext3"),
  ("ST_s-channel_4f_leptonDecays", "ST_s-channel_4f_leptonDecays_PSweights"),
  ("ST_t-channel_antitop_4f_inclusiveDecays", "ST_t-channel_antitop_4f_inclusiveDecays_PSweights"),
  ("TTJets_DiLept", "TTJets_DiLept_ext1"),
  ("TTJets_SingleLeptFromT", "TTJets_SingleLeptFromT_ext1"),
  ("TTJets_SingleLeptFromTbar", "TTJets_SingleLeptFromTbar_ext1"),
  ("WGToLNuG_ext1", "WGToLNuG_ext2", "WGToLNuG_ext3"),
  ("TTGJets", "TTGJets_ext1"),
  ("tZq_ll_4f_ext1", "tZq_ll_4f_PSweights"),
  ("DYJetsToLL_M-10to50_amcatnloFXFX", "DYJetsToLL_M-10to50_amcatnloFXFX_ext1"),
  ("DYJetsToLL_M-5to50_HT-100to200", "DYJetsToLL_M-5to50_HT-100to200_ext1"),
  ("DYJetsToLL_M-5to50_HT-200to400", "DYJetsToLL_M-5to50_HT-200to400_ext1"),
  ("DYJetsToLL_M-5to50_HT-400to600", "DYJetsToLL_M-5to50_HT-400to600_ext1"),
  ("DYJetsToLL_M-5to50_HT-600toInf", "DYJetsToLL_M-5to50_HT-600toInf_ext1"),
  ("DYJetsToLL_M-50_ext1", "DYJetsToLL_M-50_ext2"),
  ("DYJetsToLL_M50_HT100to200", "DYJetsToLL_M50_HT100to200_ext1"),
  ("DYJetsToLL_M50_HT200to400", "DYJetsToLL_M50_HT200to400_ext1"),
  ("DYJetsToLL_M50_HT400to600", "DYJetsToLL_M50_HT400to600_ext1"),
  ("WJetsToLNu", "WJetsToLNu_ext2"),
  ("WJetsToLNu_madgraphMLM", "WJetsToLNu_madgraphMLM_ext2"),
  ("W2JetsToLNu", "W2JetsToLNu_ext1"),
  ("W3JetsToLNu", "W3JetsToLNu_ext1"),
  ("W4JetsToLNu", "W4JetsToLNu_ext2"),
  ("WJetsToLNu_HT100To200", "WJetsToLNu_HT100To200_ext1", "WJetsToLNu_HT100To200_ext2"),
  ("WJetsToLNu_HT200To400", "WJetsToLNu_HT200To400_ext1", "WJetsToLNu_HT200To400_ext2"),
  ("WJetsToLNu_HT400To600", "WJetsToLNu_HT400To600_ext1"),
  ("WJetsToLNu_HT600To800", "WJetsToLNu_HT600To800_ext1"),
  ("WJetsToLNu_HT800To1200", "WJetsToLNu_HT800To1200_ext1"),
  ("WJetsToLNu_HT1200To2500", "WJetsToLNu_HT1200To2500_ext1"),
  ("WJetsToLNu_HT2500ToInf", "WJetsToLNu_HT2500ToInf_ext1"),
  ("WWToLNuQQ", "WWToLNuQQ_ext1"),
  ("ZZTo2L2Nu", "ZZTo2L2Nu_ext1"),
  ("QCD_Pt30to50_EMEnriched", "QCD_Pt30to50_EMEnriched_ext1"),
  ("QCD_Pt50to80_EMEnriched", "QCD_Pt50to80_EMEnriched_ext1"),
  ("QCD_Pt80to120_EMEnriched", "QCD_Pt80to120_EMEnriched_ext1"),
  ("QCD_Pt120to170_EMEnriched", "QCD_Pt120to170_EMEnriched_ext1"),
  ("QCD_Pt80to120_Mu5", "QCD_Pt80to120_Mu5_ext1"),
  ("QCD_Pt120to170_Mu5", "QCD_Pt120to170_Mu5_backup"),
  ("QCD_Pt170to300_Mu5", "QCD_Pt170to300_Mu5_ext1", "QCD_Pt170to300_Mu5_backup"),
  ("QCD_Pt300to470_Mu5", "QCD_Pt300to470_Mu5_ext1", "QCD_Pt300to470_Mu5_ext2"),
  ("QCD_Pt470to600_Mu5", "QCD_Pt470to600_Mu5_ext1", "QCD_Pt470to600_Mu5_ext2"),
  ("QCD_Pt600to800_Mu5", "QCD_Pt600to800_Mu5_ext1", "QCD_Pt600to800_Mu5_backup"),
  ("QCD_Pt800to1000_Mu5", "QCD_Pt800to1000_Mu5_ext1", "QCD_Pt800to1000_Mu5_ext2"),
  ("QCD_Pt1000toInf_Mu5", "QCD_Pt1000toInf_Mu5_ext1"),
}


meta_dictionary["/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Nov25_ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v2"),
  ("sample_category",       "ttH"),
  ("process_name_specific", "ttHJetToNonbb_M125_amcatnlo_ext1"),
  ("nof_db_events",         10058345),
  ("nof_db_files",          90),
  ("fsize_db",              528505950470),
  ("xsection",              0.2118),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "92.08%; status: VALID; size: 528.51GB; nevents: 10.06M; release: 9_4_9; last modified: 2019-05-04 15:01:50"),
])

meta_dictionary["/ttHToNonbb_M125_TuneCUETP8M2_ttHtranche3_13TeV-powheg-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Sep30_ttHToNonbb_M125_TuneCUETP8M2_ttHtranche3_13TeV-powheg-pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2"),
  ("sample_category",       "ttH"),
  ("process_name_specific", "ttHToNonbb_M125_powheg"),
  ("nof_db_events",         3981250),
  ("nof_db_files",          35),
  ("fsize_db",              208884155497),
  ("xsection",              0.2118),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 208.88GB; nevents: 3.98M; release: 9_4_9; last modified: 2018-11-22 07:18:07"),
])

meta_dictionary["/ttH_4f_ctcvcp_TuneCP5_13TeV_madgraph_pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Oct23_ttH_4f_ctcvcp_TuneCP5_13TeV_madgraph_pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v1"),
  ("sample_category",       "ttH_ctcvcp"),
  ("process_name_specific", "TTH_4f_ctcvcp"),
  ("nof_db_events",         9566400),
  ("nof_db_files",          149),
  ("fsize_db",              520020669375),
  ("xsection",              0.5071),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 520.02GB; nevents: 9.57M; release: 9_4_9; last modified: 2019-07-29 22:47:43"),
])

meta_dictionary["/THQ_Hincl_13TeV-madgraph-pythia8_TuneCUETP8M1/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Oct23_THQ_Hincl_13TeV-madgraph-pythia8_TuneCUETP8M1__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2"),
  ("sample_category",       "tHq"),
  ("process_name_specific", "THQ"),
  ("nof_db_events",         3495799),
  ("nof_db_files",          25),
  ("fsize_db",              158327042086),
  ("xsection",              0.02313),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "97.14%; status: VALID; size: 158.33GB; nevents: 3.50M; release: 9_4_9; last modified: 2018-11-19 21:35:57"),
])

meta_dictionary["/THQ_ctcvcp_Hincl_13TeV-madgraph-pythia8_TuneCUETP8M1/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Sep30_THQ_ctcvcp_Hincl_13TeV-madgraph-pythia8_TuneCUETP8M1__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2"),
  ("sample_category",       "tHq"),
  ("process_name_specific", "THQ_ctcvcp"),
  ("nof_db_events",         9829911),
  ("nof_db_files",          95),
  ("fsize_db",              440044765353),
  ("xsection",              0.07096),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "98.99%; status: VALID; size: 440.04GB; nevents: 9.83M; release: 9_4_9; last modified: 2019-02-08 13:08:31"),
])

meta_dictionary["/THQ_ctcvcp_HIncl_M125_TuneCP5_13TeV-madgraph-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Oct23_THQ_ctcvcp_HIncl_M125_TuneCP5_13TeV-madgraph-pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v1"),
  ("sample_category",       "tHq"),
  ("process_name_specific", "THQ_ctcvcp_CP5"),
  ("nof_db_events",         9728596),
  ("nof_db_files",          191),
  ("fsize_db",              464344551509),
  ("xsection",              0.07096),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 464.34GB; nevents: 9.73M; release: 9_4_9; last modified: 2019-05-15 20:38:56"),
])

meta_dictionary["/THW_Hincl_13TeV-madgraph-pythia8_TuneCUETP8M1/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Sep30_THW_Hincl_13TeV-madgraph-pythia8_TuneCUETP8M1__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2"),
  ("sample_category",       "tHW"),
  ("process_name_specific", "THW"),
  ("nof_db_events",         1499200),
  ("nof_db_files",          11),
  ("fsize_db",              78915203633),
  ("xsection",              0.005087),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "93.33%; status: VALID; size: 78.92GB; nevents: 1.50M; release: 9_4_9; last modified: 2018-11-24 10:41:39"),
])

meta_dictionary["/THW_ctcvcp_Hincl_13TeV-madgraph-pythia8_TuneCUETP8M1/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Oct23_THW_ctcvcp_Hincl_13TeV-madgraph-pythia8_TuneCUETP8M1__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2"),
  ("sample_category",       "tHW"),
  ("process_name_specific", "THW_ctcvcp"),
  ("nof_db_events",         4983436),
  ("nof_db_files",          46),
  ("fsize_db",              264383773632),
  ("xsection",              0.01561),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "94.0%; status: VALID; size: 264.38GB; nevents: 4.98M; release: 9_4_9; last modified: 2019-03-07 08:55:28"),
])

meta_dictionary["/THW_ctcvcp_HIncl_M125_TuneCP5_13TeV-madgraph-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Oct29_THW_ctcvcp_HIncl_M125_TuneCP5_13TeV-madgraph-pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v1"),
  ("sample_category",       "tHW"),
  ("process_name_specific", "THW_ctcvcp_CP5"),
  ("nof_db_events",         4998296),
  ("nof_db_files",          127),
  ("fsize_db",              278606440203),
  ("xsection",              0.01561),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 278.61GB; nevents: 5.00M; release: 9_4_9; last modified: 2019-05-21 18:07:24"),
])

meta_dictionary["/GluGluHToTauTau_M125_13TeV_powheg_pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v3/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Sep30_GluGluHToTauTau_M125_13TeV_powheg_pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v3"),
  ("sample_category",       "ggH"),
  ("process_name_specific", "GluGluHToTauTau"),
  ("nof_db_events",         9673200),
  ("nof_db_files",          78),
  ("fsize_db",              301793073376),
  ("xsection",              3.0469),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 301.79GB; nevents: 9.67M; release: 9_4_9; last modified: 2019-05-19 11:17:29"),
])

meta_dictionary["/GluGluHToZZTo4L_M125_13TeV_powheg2_JHUgenV6_pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Sep30_GluGluHToZZTo4L_M125_13TeV_powheg2_JHUgenV6_pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v1"),
  ("sample_category",       "ggH"),
  ("process_name_specific", "GluGluHToZZTo4L"),
  ("nof_db_events",         999800),
  ("nof_db_files",          9),
  ("fsize_db",              35576764188),
  ("xsection",              0.01297),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 35.58GB; nevents: 999.80k; release: 9_4_9; last modified: 2019-01-25 22:55:15"),
])

meta_dictionary["/GluGluHToWWToLNuQQ_M125_13TeV_powheg_JHUGenV628_pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Oct23_GluGluHToWWToLNuQQ_M125_13TeV_powheg_JHUGenV628_pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v1"),
  ("sample_category",       "ggH"),
  ("process_name_specific", "GluGluHToWWToLNuQQ_M125_ext1"),
  ("nof_db_events",         198000),
  ("nof_db_files",          22),
  ("fsize_db",              6500162934),
  ("xsection",              4.5621),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 6.50GB; nevents: 198.00k; release: 9_4_9; last modified: 2019-05-11 00:06:58"),
])

meta_dictionary["/GluGluHToWWTo2L2Nu_M125_13TeV_powheg_JHUgen_pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Nov25_GluGluHToWWTo2L2Nu_M125_13TeV_powheg_JHUgen_pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2"),
  ("sample_category",       "ggH"),
  ("process_name_specific", "GluGluHToWWTo2L2Nu_M125"),
  ("nof_db_events",         492200),
  ("nof_db_files",          4),
  ("fsize_db",              15435406262),
  ("xsection",              1.1033),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 15.44GB; nevents: 492.20k; release: 9_4_9; last modified: 2019-04-15 18:17:32"),
])

meta_dictionary["/GluGluHToMuMu_M-125_TuneCP5_PSweights_13TeV_powheg_pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Sep30_GluGluHToMuMu_M-125_TuneCP5_PSweights_13TeV_powheg_pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v1"),
  ("sample_category",       "ggH"),
  ("process_name_specific", "GluGluHToMuMu_M125"),
  ("nof_db_events",         1991200),
  ("nof_db_files",          34),
  ("fsize_db",              63981899559),
  ("xsection",              0.010571),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 63.98GB; nevents: 1.99M; release: 9_4_9; last modified: 2019-02-22 13:53:17"),
])

meta_dictionary["/GluGluHToBB_M125_13TeV_amcatnloFXFX_pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Sep30_GluGluHToBB_M125_13TeV_amcatnloFXFX_pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2"),
  ("sample_category",       "ggH"),
  ("process_name_specific", "GluGluHToBB_M125"),
  ("nof_db_events",         972675),
  ("nof_db_files",          7),
  ("fsize_db",              32270097687),
  ("xsection",              28.293),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 32.27GB; nevents: 972.67k; release: 9_4_9; last modified: 2019-03-01 09:57:04"),
])

meta_dictionary["/GluGluHToBB_M125_13TeV_amcatnloFXFX_pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Nov25_GluGluHToBB_M125_13TeV_amcatnloFXFX_pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v1"),
  ("sample_category",       "ggH"),
  ("process_name_specific", "GluGluHToBB_M125_ext1"),
  ("nof_db_events",         3799373),
  ("nof_db_files",          31),
  ("fsize_db",              126249951405),
  ("xsection",              28.293),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 126.25GB; nevents: 3.80M; release: 9_4_9; last modified: 2019-05-03 23:37:04"),
])

meta_dictionary["/GluGluHToGG_M125_13TeV_amcatnloFXFX_pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext2-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Sep30_GluGluHToGG_M125_13TeV_amcatnloFXFX_pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext2-v2"),
  ("sample_category",       "ggH"),
  ("process_name_specific", "GluGluHToGG_M125_ext2"),
  ("nof_db_events",         812652),
  ("nof_db_files",          7),
  ("fsize_db",              26217726562),
  ("xsection",              0.11028),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 26.22GB; nevents: 812.65k; release: 9_4_9; last modified: 2019-04-22 20:59:06"),
])

meta_dictionary["/VBFHToTauTau_M125_13TeV_powheg_pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Nov25_VBFHToTauTau_M125_13TeV_powheg_pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2"),
  ("sample_category",       "qqH"),
  ("process_name_specific", "VBFHToTauTau"),
  ("nof_db_events",         1499400),
  ("nof_db_files",          15),
  ("fsize_db",              50767229807),
  ("xsection",              0.2372),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 50.77GB; nevents: 1.50M; release: 9_4_9; last modified: 2019-02-10 01:58:13"),
])

meta_dictionary["/VBF_HToZZTo4L_M125_13TeV_powheg2_JHUgenV6_pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Sep30_VBF_HToZZTo4L_M125_13TeV_powheg2_JHUgenV6_pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2"),
  ("sample_category",       "qqH"),
  ("process_name_specific", "VBF_HToZZTo4L"),
  ("nof_db_events",         500000),
  ("nof_db_files",          6),
  ("fsize_db",              19438723963),
  ("xsection",              0.0010099),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 19.44GB; nevents: 500.00k; release: 9_4_9; last modified: 2019-05-01 13:26:40"),
])

meta_dictionary["/VBFHToWWToLNuQQ_M125_13TeV_powheg_JHUGenV628_pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Oct23_VBFHToWWToLNuQQ_M125_13TeV_powheg_JHUGenV628_pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v1"),
  ("sample_category",       "qqH"),
  ("process_name_specific", "VBFHToWWToLNuQQ_M125_ext1"),
  ("nof_db_events",         200000),
  ("nof_db_files",          31),
  ("fsize_db",              7289993844),
  ("xsection",              0.35517),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 7.29GB; nevents: 200.00k; release: 9_4_9; last modified: 2019-05-14 14:09:08"),
])

meta_dictionary["/VBFHToWWTo2L2Nu_M125_13TeV_powheg_JHUgenv628_pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Sep30_VBFHToWWTo2L2Nu_M125_13TeV_powheg_JHUgenv628_pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2"),
  ("sample_category",       "qqH"),
  ("process_name_specific", "VBFHToWWTo2L2Nu_M125"),
  ("nof_db_events",         100000),
  ("nof_db_files",          1),
  ("fsize_db",              3406704278),
  ("xsection",              0.085894),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 3.41GB; nevents: 100.00k; release: 9_4_9; last modified: 2019-02-01 17:22:01"),
])

meta_dictionary["/VBFHToMuMu_M-125_TuneCP5_PSweights_13TeV_powheg_pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Sep30_VBFHToMuMu_M-125_TuneCP5_PSweights_13TeV_powheg_pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v1"),
  ("sample_category",       "qqH"),
  ("process_name_specific", "VBFHToMuMu_M125"),
  ("nof_db_events",         997600),
  ("nof_db_files",          25),
  ("fsize_db",              36458351750),
  ("xsection",              0.00082296),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 36.46GB; nevents: 997.60k; release: 9_4_9; last modified: 2019-02-20 04:32:08"),
])

meta_dictionary["/VBFHToBB_M-125_13TeV_powheg_pythia8_weightfix/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Oct23_VBFHToBB_M-125_13TeV_powheg_pythia8_weightfix__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v1"),
  ("sample_category",       "qqH"),
  ("process_name_specific", "VBFHToBB_M125"),
  ("nof_db_events",         997371),
  ("nof_db_files",          11),
  ("fsize_db",              35502253347),
  ("xsection",              2.2026),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 35.50GB; nevents: 997.37k; release: 9_4_9; last modified: 2019-02-01 17:34:51"),
])

meta_dictionary["/VBFHToBB_M-125_13TeV_powheg_pythia8_weightfix/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Sep30_VBFHToBB_M-125_13TeV_powheg_pythia8_weightfix__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v1"),
  ("sample_category",       "qqH"),
  ("process_name_specific", "VBFHToBB_M125_ext1"),
  ("nof_db_events",         3774811),
  ("nof_db_files",          36),
  ("fsize_db",              134011208892),
  ("xsection",              2.2026),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 134.01GB; nevents: 3.77M; release: 9_4_9; last modified: 2019-05-05 15:06:16"),
])

meta_dictionary["/VBFHToGG_M125_13TeV_amcatnlo_pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Sep30_VBFHToGG_M125_13TeV_amcatnlo_pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v2"),
  ("sample_category",       "qqH"),
  ("process_name_specific", "VBFHToGG_M125_ext1"),
  ("nof_db_events",         1999200),
  ("nof_db_files",          14),
  ("fsize_db",              66554715193),
  ("xsection",              0.0085851),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "95.0%; status: VALID; size: 66.55GB; nevents: 2.00M; release: 9_4_9; last modified: 2019-04-28 19:32:42"),
])

meta_dictionary["/VBFHToGG_M125_13TeV_amcatnlo_pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext2-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Sep30_VBFHToGG_M125_13TeV_amcatnlo_pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext2-v2"),
  ("sample_category",       "qqH"),
  ("process_name_specific", "VBFHToGG_M125_ext2"),
  ("nof_db_events",         1198800),
  ("nof_db_files",          12),
  ("fsize_db",              40048536582),
  ("xsection",              0.0085851),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 40.05GB; nevents: 1.20M; release: 9_4_9; last modified: 2019-05-12 07:19:18"),
])

meta_dictionary["/TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext2-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Nov25_TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext2-v1"),
  ("sample_category",       "TTZ"),
  ("process_name_specific", "TTZToLL_M10_ext2"),
  ("nof_db_events",         5837781),
  ("nof_db_files",          49),
  ("fsize_db",              285619884616),
  ("xsection",              0.2814),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "94.92%; status: VALID; size: 285.62GB; nevents: 5.84M; release: 9_4_9; last modified: 2018-10-17 14:10:02"),
])

meta_dictionary["/TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext3-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Nov25_TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext3-v1"),
  ("sample_category",       "TTZ"),
  ("process_name_specific", "TTZToLL_M10_ext3"),
  ("nof_db_events",         5934228),
  ("nof_db_files",          48),
  ("fsize_db",              290237477462),
  ("xsection",              0.2814),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 290.24GB; nevents: 5.93M; release: 9_4_9; last modified: 2018-09-30 03:36:01"),
])

meta_dictionary["/TTZToLL_M-1to10_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv3-94X_mcRun2_asymptotic_v3-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Sep30_TTZToLL_M-1to10_TuneCUETP8M1_13TeV-madgraphMLM-pythia8__RunIISummer16MiniAODv3-94X_mcRun2_asymptotic_v3-v1"),
  ("sample_category",       "TTZ"),
  ("process_name_specific", "TTZToLL_M-1to10"),
  ("nof_db_events",         246792),
  ("nof_db_files",          5),
  ("fsize_db",              12037865155),
  ("xsection",              0.0822),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 12.04GB; nevents: 246.79k; release: 9_4_9; last modified: 2019-01-25 08:48:31"),
])

meta_dictionary["/ttZJets_13TeV_madgraphMLM-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Oct23_ttZJets_13TeV_madgraphMLM-pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v1"),
  ("sample_category",       "TTZ"),
  ("process_name_specific", "TTZJets_LO"),
  ("nof_db_events",         9883364),
  ("nof_db_files",          80),
  ("fsize_db",              503856469288),
  ("xsection",              0.8854),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 503.86GB; nevents: 9.88M; release: 9_4_9; last modified: 2018-10-18 06:05:21"),
])

meta_dictionary["/TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext2-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Oct23_TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext2-v1"),
  ("sample_category",       "TTW"),
  ("process_name_specific", "TTWJetsToLNu_ext2"),
  ("nof_db_events",         3120397),
  ("nof_db_files",          31),
  ("fsize_db",              153765510942),
  ("xsection",              0.196),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 153.77GB; nevents: 3.12M; release: 9_4_9; last modified: 2018-10-18 10:47:11"),
])

meta_dictionary["/ttWJets_13TeV_madgraphMLM/RunIISummer16MiniAODv3-94X_mcRun2_asymptotic_v3-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Sep30_ttWJets_13TeV_madgraphMLM__RunIISummer16MiniAODv3-94X_mcRun2_asymptotic_v3-v1"),
  ("sample_category",       "TTW"),
  ("process_name_specific", "TTWJets_LO"),
  ("nof_db_events",         6700440),
  ("nof_db_files",          60),
  ("fsize_db",              334741041696),
  ("xsection",              0.6008),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 334.74GB; nevents: 6.70M; release: 9_4_9; last modified: 2019-01-24 21:20:21"),
])

meta_dictionary["/TTWW_TuneCUETP8M2T4_13TeV-madgraph-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Sep30_TTWW_TuneCUETP8M2T4_13TeV-madgraph-pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v1"),
  ("sample_category",       "TTWW"),
  ("process_name_specific", "TTWW_ext1"),
  ("nof_db_events",         98300),
  ("nof_db_files",          22),
  ("fsize_db",              5758278541),
  ("xsection",              0.006981),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 5.76GB; nevents: 98.30k; release: 9_4_9; last modified: 2019-02-18 16:35:57"),
])

meta_dictionary["/ST_s-channel_4f_leptonDecays_13TeV-amcatnlo-pythia8_TuneCUETP8M1/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Sep30_ST_s-channel_4f_leptonDecays_13TeV-amcatnlo-pythia8_TuneCUETP8M1__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v1"),
  ("sample_category",       "TT"),
  ("process_name_specific", "ST_s-channel_4f_leptonDecays"),
  ("nof_db_events",         1000000),
  ("nof_db_files",          8),
  ("fsize_db",              34802245951),
  ("xsection",              3.364),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 34.80GB; nevents: 1.00M; release: 9_4_9; last modified: 2019-01-27 09:05:51"),
])

meta_dictionary["/ST_s-channel_4f_leptonDecays_13TeV_PSweights-amcatnlo-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Oct23_ST_s-channel_4f_leptonDecays_13TeV_PSweights-amcatnlo-pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v1"),
  ("sample_category",       "TT"),
  ("process_name_specific", "ST_s-channel_4f_leptonDecays_PSweights"),
  ("nof_db_events",         9971200),
  ("nof_db_files",          228),
  ("fsize_db",              351816237888),
  ("xsection",              3.364),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 351.82GB; nevents: 9.97M; release: 9_4_9; last modified: 2019-07-12 21:15:10"),
])

meta_dictionary["/ST_t-channel_antitop_4f_inclusiveDecays_13TeV-powhegV2-madspin-pythia8_TuneCUETP8M1/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Sep30_ST_t-channel_antitop_4f_inclusiveDecays_13TeV-powhegV2-madspin-pythia8_TuneCUETP8M1__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asym"),
  ("sample_category",       "TT"),
  ("process_name_specific", "ST_t-channel_antitop_4f_inclusiveDecays"),
  ("nof_db_events",         38811017),
  ("nof_db_files",          298),
  ("fsize_db",              1415890534904),
  ("xsection",              80.95),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 1.42TB; nevents: 38.81M; release: 9_4_9; last modified: 2018-11-09 05:05:25"),
])

meta_dictionary["/ST_t-channel_antitop_4f_inclusiveDecays_13TeV_PSweights-powhegV2-madspin/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Oct23_ST_t-channel_antitop_4f_inclusiveDecays_13TeV_PSweights-powhegV2-madspin__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v"),
  ("sample_category",       "TT"),
  ("process_name_specific", "ST_t-channel_antitop_4f_inclusiveDecays_PSweights"),
  ("nof_db_events",         39675800),
  ("nof_db_files",          532),
  ("fsize_db",              1461111384763),
  ("xsection",              80.95),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 1.46TB; nevents: 39.68M; release: 9_4_9; last modified: 2019-07-14 09:14:11"),
])

meta_dictionary["/ST_t-channel_top_4f_inclusiveDecays_13TeV-powhegV2-madspin-pythia8_TuneCUETP8M1/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Nov25_CHUNK0_ST_t-channel_top_4f_inclusiveDecays_13TeV-powhegV2-madspin-pythia8_TuneCUETP8M1__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptoti"),
  ("sample_category",       "TT"),
  ("process_name_specific", "ST_t-channel_top_4f_inclusiveDecays"),
  ("nof_db_events",         67105876),
  ("nof_db_files",          499),
  ("fsize_db",              2452787667702),
  ("xsection",              136.02),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "100.00%; status: VALID; size: 2.45TB; nevents: 67.11M; release: 9_4_9; last modified: 2018-11-11 13:54:53"),
])

meta_dictionary["/ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Oct23_ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v1"),
  ("sample_category",       "TT"),
  ("process_name_specific", "ST_tW_antitop_5f_inclusiveDecays_ext1"),
  ("nof_db_events",         6933094),
  ("nof_db_files",          58),
  ("fsize_db",              270415654176),
  ("xsection",              35.85),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 270.42GB; nevents: 6.93M; release: 9_4_9; last modified: 2018-10-01 02:42:01"),
])

meta_dictionary["/ST_tW_top_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Oct23_ST_tW_top_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v1"),
  ("sample_category",       "TT"),
  ("process_name_specific", "ST_tW_top_5f_inclusiveDecays_ext1"),
  ("nof_db_events",         6952830),
  ("nof_db_files",          60),
  ("fsize_db",              271455083001),
  ("xsection",              35.85),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "97.14%; status: VALID; size: 271.46GB; nevents: 6.95M; release: 9_4_9; last modified: 2018-10-04 05:07:18"),
])

meta_dictionary["/ST_tWll_5f_LO_13TeV-MadGraph-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Sep30_ST_tWll_5f_LO_13TeV-MadGraph-pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v1"),
  ("sample_category",       "TT"),
  ("process_name_specific", "ST_tWll"),
  ("nof_db_events",         50000),
  ("nof_db_files",          1),
  ("fsize_db",              2471279251),
  ("xsection",              0.01096),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 2.47GB; nevents: 50.00k; release: 9_4_9; last modified: 2018-10-18 11:01:19"),
])

meta_dictionary["/TTTo2L2Nu_TuneCP5_PSweights_13TeV-powheg-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Nov25_TTTo2L2Nu_TuneCP5_PSweights_13TeV-powheg-pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v1"),
  ("sample_category",       "TT"),
  ("process_name_specific", "TTTo2L2Nu"),
  ("nof_db_events",         67926800),
  ("nof_db_files",          778),
  ("fsize_db",              2988515757147),
  ("xsection",              88.4),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 2.99TB; nevents: 67.93M; release: 9_4_9; last modified: 2019-06-05 16:53:03"),
])

meta_dictionary["/TTToSemiLeptonic_TuneCP5_PSweights_13TeV-powheg-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Nov25_TTToSemiLeptonic_TuneCP5_PSweights_13TeV-powheg-pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v1"),
  ("sample_category",       "TT"),
  ("process_name_specific", "TTToSemiLeptonic"),
  ("nof_db_events",         107604800),
  ("nof_db_files",          1105),
  ("fsize_db",              4847363049070),
  ("xsection",              365.52),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "93.22%; status: VALID; size: 4.85TB; nevents: 107.60M; release: 9_4_9; last modified: 2019-06-12 09:39:20"),
])

meta_dictionary["/TTToHadronic_TuneCP5_PSweights_13TeV-powheg-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Sep30_TTToHadronic_TuneCP5_PSweights_13TeV-powheg-pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v1"),
  ("sample_category",       "TT"),
  ("process_name_specific", "TTToHadronic"),
  ("nof_db_events",         68518800),
  ("nof_db_files",          772),
  ("fsize_db",              3163848156807),
  ("xsection",              377.85),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 3.16TB; nevents: 68.52M; release: 9_4_9; last modified: 2019-06-14 17:19:47"),
])

meta_dictionary["/TTJets_DiLept_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Sep30_TTJets_DiLept_TuneCUETP8M1_13TeV-madgraphMLM-pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2"),
  ("sample_category",       "TT"),
  ("process_name_specific", "TTJets_DiLept"),
  ("nof_db_events",         6068369),
  ("nof_db_files",          48),
  ("fsize_db",              258912481730),
  ("xsection",              88.4),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 258.91GB; nevents: 6.07M; release: 9_4_9; last modified: 2018-11-17 21:59:27"),
])

meta_dictionary["/TTJets_DiLept_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Oct29_TTJets_DiLept_TuneCUETP8M1_13TeV-madgraphMLM-pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v2"),
  ("sample_category",       "TT"),
  ("process_name_specific", "TTJets_DiLept_ext1"),
  ("nof_db_events",         24767666),
  ("nof_db_files",          208),
  ("fsize_db",              1057101408492),
  ("xsection",              88.4),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 1.06TB; nevents: 24.77M; release: 9_4_9; last modified: 2018-11-18 22:41:36"),
])

meta_dictionary["/TTJets_SingleLeptFromT_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Sep30_TTJets_SingleLeptFromT_TuneCUETP8M1_13TeV-madgraphMLM-pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2"),
  ("sample_category",       "TT"),
  ("process_name_specific", "TTJets_SingleLeptFromT"),
  ("nof_db_events",         11957043),
  ("nof_db_files",          97),
  ("fsize_db",              527227071561),
  ("xsection",              182.76),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 527.23GB; nevents: 11.96M; release: 9_4_9; last modified: 2018-11-18 11:36:18"),
])

meta_dictionary["/TTJets_SingleLeptFromT_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Oct23_TTJets_SingleLeptFromT_TuneCUETP8M1_13TeV-madgraphMLM-pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v2"),
  ("sample_category",       "TT"),
  ("process_name_specific", "TTJets_SingleLeptFromT_ext1"),
  ("nof_db_events",         49664175),
  ("nof_db_files",          407),
  ("fsize_db",              2190287845746),
  ("xsection",              182.76),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "99.2%; status: VALID; size: 2.19TB; nevents: 49.66M; release: 9_4_9; last modified: 2018-11-20 10:44:10"),
])

meta_dictionary["/TTJets_SingleLeptFromTbar_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Sep30_TTJets_SingleLeptFromTbar_TuneCUETP8M1_13TeV-madgraphMLM-pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2"),
  ("sample_category",       "TT"),
  ("process_name_specific", "TTJets_SingleLeptFromTbar"),
  ("nof_db_events",         11955887),
  ("nof_db_files",          112),
  ("fsize_db",              529159861432),
  ("xsection",              182.76),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 529.16GB; nevents: 11.96M; release: 9_4_9; last modified: 2018-11-19 08:38:57"),
])

meta_dictionary["/TTJets_SingleLeptFromTbar_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Nov25_CHUNK0_TTJets_SingleLeptFromTbar_TuneCUETP8M1_13TeV-madgraphMLM-pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v2"),
  ("sample_category",       "TT"),
  ("process_name_specific", "TTJets_SingleLeptFromTbar_ext1"),
  ("nof_db_events",         48387865),
  ("nof_db_files",          366),
  ("fsize_db",              2131421738428),
  ("xsection",              182.76),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "98.26%; status: VALID; size: 2.13TB; nevents: 48.39M; release: 9_4_9; last modified: 2018-11-19 16:21:22"),
])

meta_dictionary["/TTJets_TuneCUETP8M2T4_13TeV-amcatnloFXFX-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Nov25_TTJets_TuneCUETP8M2T4_13TeV-amcatnloFXFX-pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2"),
  ("sample_category",       "TT"),
  ("process_name_specific", "TTJets_amcatnloFXFX"),
  ("nof_db_events",         43845135),
  ("nof_db_files",          328),
  ("fsize_db",              1938885377318),
  ("xsection",              831.76),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 1.94TB; nevents: 43.85M; release: 9_4_9; last modified: 2019-01-16 20:36:35"),
])

meta_dictionary["/TTJets_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Oct23_TTJets_TuneCUETP8M1_13TeV-madgraphMLM-pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v1"),
  ("sample_category",       "TT"),
  ("process_name_specific", "TTJets_madgraphMLM"),
  ("nof_db_events",         10199051),
  ("nof_db_files",          81),
  ("fsize_db",              450517597405),
  ("xsection",              831.76),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 450.52GB; nevents: 10.20M; release: 9_4_9; last modified: 2019-01-31 15:59:30"),
])

meta_dictionary["/TTWH_TuneCUETP8M2T4_13TeV-madgraph-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Sep30_TTWH_TuneCUETP8M2T4_13TeV-madgraph-pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v1"),
  ("sample_category",       "TTWH"),
  ("process_name_specific", "TTWH_ext1"),
  ("nof_db_events",         100000),
  ("nof_db_files",          19),
  ("fsize_db",              5876783273),
  ("xsection",              0.001582),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 5.88GB; nevents: 100.00k; release: 9_4_9; last modified: 2019-02-07 10:33:26"),
])

meta_dictionary["/TTZH_TuneCUETP8M2T4_13TeV-madgraph-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Oct23_TTZH_TuneCUETP8M2T4_13TeV-madgraph-pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v1"),
  ("sample_category",       "TTZH"),
  ("process_name_specific", "TTZH_ext1"),
  ("nof_db_events",         97800),
  ("nof_db_files",          25),
  ("fsize_db",              6060088194),
  ("xsection",              0.001535),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 6.06GB; nevents: 97.80k; release: 9_4_9; last modified: 2019-02-19 06:48:01"),
])

meta_dictionary["/WWW_4F_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Sep30_WWW_4F_TuneCUETP8M1_13TeV-amcatnlo-pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2"),
  ("sample_category",       "Rares"),
  ("process_name_specific", "WWW"),
  ("nof_db_events",         240000),
  ("nof_db_files",          2),
  ("fsize_db",              9387450023),
  ("xsection",              0.2086),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 9.39GB; nevents: 240.00k; release: 9_4_9; last modified: 2018-11-25 23:37:57"),
])

meta_dictionary["/WWZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Sep30_WWZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2"),
  ("sample_category",       "Rares"),
  ("process_name_specific", "WWZ"),
  ("nof_db_events",         250000),
  ("nof_db_files",          2),
  ("fsize_db",              10137871549),
  ("xsection",              0.1676),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 10.14GB; nevents: 250.00k; release: 9_4_9; last modified: 2018-11-25 00:18:36"),
])

meta_dictionary["/WZZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Sep30_WZZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2"),
  ("sample_category",       "Rares"),
  ("process_name_specific", "WZZ"),
  ("nof_db_events",         246800),
  ("nof_db_files",          3),
  ("fsize_db",              10093638437),
  ("xsection",              0.05701),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 10.09GB; nevents: 246.80k; release: 9_4_9; last modified: 2018-11-24 04:45:19"),
])

meta_dictionary["/ZZZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Sep30_ZZZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2"),
  ("sample_category",       "Rares"),
  ("process_name_specific", "ZZZ"),
  ("nof_db_events",         249237),
  ("nof_db_files",          4),
  ("fsize_db",              9637763887),
  ("xsection",              0.01473),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 9.64GB; nevents: 249.24k; release: 9_4_9; last modified: 2018-11-27 04:46:28"),
])

meta_dictionary["/WZG_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Sep30_WZG_TuneCUETP8M1_13TeV-amcatnlo-pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v1"),
  ("sample_category",       "Rares"),
  ("process_name_specific", "WZG"),
  ("nof_db_events",         998200),
  ("nof_db_files",          8),
  ("fsize_db",              38928454526),
  ("xsection",              0.04345),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 38.93GB; nevents: 998.20k; release: 9_4_9; last modified: 2019-01-25 17:40:34"),
])

meta_dictionary["/WGToLNuG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Oct23_WGToLNuG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v1"),
  ("sample_category",       "Rares"),
  ("process_name_specific", "WGToLNuG_ext1"),
  ("nof_db_events",         5059865),
  ("nof_db_files",          45),
  ("fsize_db",              148377698646),
  ("xsection",              464.8),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 148.38GB; nevents: 5.06M; release: 9_4_9; last modified: 2018-10-01 02:45:41"),
])

meta_dictionary["/WGToLNuG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext2-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Nov25_WGToLNuG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext2-v1"),
  ("sample_category",       "Rares"),
  ("process_name_specific", "WGToLNuG_ext2"),
  ("nof_db_events",         10231994),
  ("nof_db_files",          73),
  ("fsize_db",              299146793202),
  ("xsection",              464.8),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 299.15GB; nevents: 10.23M; release: 9_4_9; last modified: 2018-10-17 14:08:12"),
])

meta_dictionary["/WGToLNuG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext3-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Nov25_WGToLNuG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext3-v1"),
  ("sample_category",       "Rares"),
  ("process_name_specific", "WGToLNuG_ext3"),
  ("nof_db_events",         12219986),
  ("nof_db_files",          90),
  ("fsize_db",              357306491523),
  ("xsection",              464.8),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 357.31GB; nevents: 12.22M; release: 9_4_9; last modified: 2018-10-07 10:30:18"),
])

meta_dictionary["/WGToLNuG_01J_5f_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2020Jan10_WGToLNuG_01J_5f_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v1"),
  ("sample_category",       "Rares"),
  ("process_name_specific", "WGToLNuG_01J"),
  ("nof_db_events",         26722551),
  ("nof_db_files",          348),
  ("fsize_db",              903161012258),
  ("xsection",              191.6),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 903.16GB; nevents: 26.72M; release: 9_4_9; last modified: 2019-04-10 00:45:58"),
])

meta_dictionary["/ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Oct23_ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v1"),
  ("sample_category",       "Rares"),
  ("process_name_specific", "ZGTo2LG_ext1"),
  ("nof_db_events",         14372682),
  ("nof_db_files",          106),
  ("fsize_db",              462073274633),
  ("xsection",              123.9),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 462.07GB; nevents: 14.37M; release: 9_4_9; last modified: 2018-10-03 03:34:07"),
])

meta_dictionary["/TGJets_leptonDecays_13TeV_amcatnlo_madspin_pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Sep30_TGJets_leptonDecays_13TeV_amcatnlo_madspin_pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2"),
  ("sample_category",       "Rares"),
  ("process_name_specific", "TGJets"),
  ("nof_db_events",         6872721),
  ("nof_db_files",          62),
  ("fsize_db",              271354980749),
  ("xsection",              1.018),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 271.35GB; nevents: 6.87M; release: 9_4_9; last modified: 2019-02-25 16:43:28"),
])

meta_dictionary["/TTGJets_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Sep30_TTGJets_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2"),
  ("sample_category",       "Rares"),
  ("process_name_specific", "TTGJets"),
  ("nof_db_events",         4870911),
  ("nof_db_files",          42),
  ("fsize_db",              235015310414),
  ("xsection",              4.215),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 235.02GB; nevents: 4.87M; release: 9_4_9; last modified: 2018-11-19 16:26:39"),
])

meta_dictionary["/TTGJets_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Nov25_CHUNK0_TTGJets_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v2"),
  ("sample_category",       "Rares"),
  ("process_name_specific", "TTGJets_ext1"),
  ("nof_db_events",         9877942),
  ("nof_db_files",          83),
  ("fsize_db",              476687878413),
  ("xsection",              4.215),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "100.00%; status: VALID; size: 476.69GB; nevents: 9.88M; release: 9_4_9; last modified: 2018-11-19 08:49:21"),
])

meta_dictionary["/tZq_ll_4f_13TeV-amcatnlo-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Nov25_tZq_ll_4f_13TeV-amcatnlo-pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v1"),
  ("sample_category",       "Rares"),
  ("process_name_specific", "tZq_ll_4f_ext1"),
  ("nof_db_events",         13656784),
  ("nof_db_files",          117),
  ("fsize_db",              609340347890),
  ("xsection",              0.07358),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 609.34GB; nevents: 13.66M; release: 9_4_9; last modified: 2018-10-24 14:02:18"),
])

meta_dictionary["/tZq_ll_4f_PSweights_13TeV-amcatnlo-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Nov25_tZq_ll_4f_PSweights_13TeV-amcatnlo-pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v1"),
  ("sample_category",       "Rares"),
  ("process_name_specific", "tZq_ll_4f_PSweights"),
  ("nof_db_events",         10780000),
  ("nof_db_files",          268),
  ("fsize_db",              484895614604),
  ("xsection",              0.07358),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 484.90GB; nevents: 10.78M; release: 9_4_9; last modified: 2019-07-05 20:56:31"),
])

meta_dictionary["/WpWpJJ_EWK-QCD_TuneCUETP8M1_13TeV-madgraph-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Sep30_WpWpJJ_EWK-QCD_TuneCUETP8M1_13TeV-madgraph-pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v1"),
  ("sample_category",       "Rares"),
  ("process_name_specific", "WpWpJJ_EWK_QCD"),
  ("nof_db_events",         149681),
  ("nof_db_files",          2),
  ("fsize_db",              6297855563),
  ("xsection",              0.04926),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 6.30GB; nevents: 149.68k; release: 9_4_9; last modified: 2018-09-30 15:36:49"),
])

meta_dictionary["/WWTo2L2Nu_DoubleScattering_13TeV-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Sep30_WWTo2L2Nu_DoubleScattering_13TeV-pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2"),
  ("sample_category",       "Rares"),
  ("process_name_specific", "WWTo2L2Nu_DoubleScattering"),
  ("nof_db_events",         999367),
  ("nof_db_files",          8),
  ("fsize_db",              28740400603),
  ("xsection",              0.2232),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 28.74GB; nevents: 999.37k; release: 9_4_9; last modified: 2018-11-17 21:00:12"),
])

meta_dictionary["/TTTT_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Dec01_TTTT_TuneCUETP8M1_13TeV-amcatnlo-pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2"),
  ("sample_category",       "Rares"),
  ("process_name_specific", "TTTT"),
  ("nof_db_events",         250000),
  ("nof_db_files",          6),
  ("fsize_db",              17011686942),
  ("xsection",              0.008213),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 17.01GB; nevents: 250.00k; release: 9_4_9; last modified: 2018-11-29 14:09:00"),
])

meta_dictionary["/TTTW_TuneCUETP8M2T4_13TeV-madgraph-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Nov25_TTTW_TuneCUETP8M2T4_13TeV-madgraph-pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v1"),
  ("sample_category",       "Rares"),
  ("process_name_specific", "TTTW_ext1"),
  ("nof_db_events",         97200),
  ("nof_db_files",          21),
  ("fsize_db",              6214628717),
  ("xsection",              0.000732),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 6.21GB; nevents: 97.20k; release: 9_4_9; last modified: 2019-02-18 16:38:14"),
])

meta_dictionary["/TTTJ_TuneCUETP8M2T4_13TeV-madgraph-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Sep30_TTTJ_TuneCUETP8M2T4_13TeV-madgraph-pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v1"),
  ("sample_category",       "Rares"),
  ("process_name_specific", "TTTJ_ext1"),
  ("nof_db_events",         100000),
  ("nof_db_files",          15),
  ("fsize_db",              6002230700),
  ("xsection",              0.000397),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 6.00GB; nevents: 100.00k; release: 9_4_9; last modified: 2019-02-17 02:58:36"),
])

meta_dictionary["/TTWZ_TuneCUETP8M2T4_13TeV-madgraph-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Sep30_TTWZ_TuneCUETP8M2T4_13TeV-madgraph-pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v1"),
  ("sample_category",       "Rares"),
  ("process_name_specific", "TTWZ_ext1"),
  ("nof_db_events",         100000),
  ("nof_db_files",          20),
  ("fsize_db",              5738630560),
  ("xsection",              0.003884),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 5.74GB; nevents: 100.00k; release: 9_4_9; last modified: 2019-02-18 23:48:14"),
])

meta_dictionary["/TTZZ_TuneCUETP8M2T4_13TeV-madgraph-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Sep30_TTZZ_TuneCUETP8M2T4_13TeV-madgraph-pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v1"),
  ("sample_category",       "Rares"),
  ("process_name_specific", "TTZZ_ext1"),
  ("nof_db_events",         98400),
  ("nof_db_files",          22),
  ("fsize_db",              5745057480),
  ("xsection",              0.001982),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 5.75GB; nevents: 98.40k; release: 9_4_9; last modified: 2019-02-20 12:57:08"),
])

meta_dictionary["/VHToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Sep30_VHToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2"),
  ("sample_category",       "VH"),
  ("process_name_specific", "VHToNonbb_M125"),
  ("nof_db_events",         1007898),
  ("nof_db_files",          10),
  ("fsize_db",              36259986064),
  ("xsection",              0.9425),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 36.26GB; nevents: 1.01M; release: 9_4_9; last modified: 2018-11-26 07:06:05"),
])

meta_dictionary["/ZH_HToBB_ZToLL_M125_13TeV_powheg_pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Sep30_ZH_HToBB_ZToLL_M125_13TeV_powheg_pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v1"),
  ("sample_category",       "VH"),
  ("process_name_specific", "ZH_HToBB_ZToLL_ext1"),
  ("nof_db_events",         2972920),
  ("nof_db_files",          28),
  ("fsize_db",              117275606767),
  ("xsection",              0.05198),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 117.28GB; nevents: 2.97M; release: 9_4_9; last modified: 2019-02-01 17:35:55"),
])

meta_dictionary["/ZHToTauTau_M125_13TeV_powheg_pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Sep30_ZHToTauTau_M125_13TeV_powheg_pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2"),
  ("sample_category",       "VH"),
  ("process_name_specific", "ZHToTauTau"),
  ("nof_db_events",         599803),
  ("nof_db_files",          7),
  ("fsize_db",              21471114314),
  ("xsection",              0.05544),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 21.47GB; nevents: 599.80k; release: 9_4_9; last modified: 2018-11-16 10:57:14"),
])

meta_dictionary["/DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Sep30_DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2"),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DYJetsToLL_M-10to50"),
  ("nof_db_events",         35114961),
  ("nof_db_files",          264),
  ("fsize_db",              852575436868),
  ("xsection",              18610.0),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 852.58GB; nevents: 35.11M; release: 9_4_9; last modified: 2018-12-30 05:39:25"),
])

meta_dictionary["/DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Sep30_DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2"),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DYJetsToLL_M-10to50_amcatnloFXFX"),
  ("nof_db_events",         67981236),
  ("nof_db_files",          483),
  ("fsize_db",              1594691281733),
  ("xsection",              18610.0),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "99.85%; status: VALID; size: 1.59TB; nevents: 67.98M; release: 9_4_9; last modified: 2018-12-05 03:27:45"),
])

meta_dictionary["/DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Oct29_CHUNK0_DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v2"),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DYJetsToLL_M-10to50_amcatnloFXFX_ext1"),
  ("nof_db_events",         40364234),
  ("nof_db_files",          287),
  ("fsize_db",              946826425333),
  ("xsection",              18610.0),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "99.65%; status: VALID; size: 946.83GB; nevents: 40.36M; release: 9_4_9; last modified: 2018-11-20 13:49:54"),
])

meta_dictionary["/DY1JetsToLL_M-10to50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Nov25_DY1JetsToLL_M-10to50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2"),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DY1JetsToLL_M-10to50"),
  ("nof_db_events",         39958449),
  ("nof_db_files",          296),
  ("fsize_db",              1114603185048),
  ("xsection",              859.68),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 1.11TB; nevents: 39.96M; release: 9_4_9; last modified: 2019-02-25 20:32:31"),
])

meta_dictionary["/DY2JetsToLL_M-10to50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Nov25_CHUNK0_DY2JetsToLL_M-10to50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2"),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DY2JetsToLL_M-10to50"),
  ("nof_db_events",         19461065),
  ("nof_db_files",          144),
  ("fsize_db",              571063486084),
  ("xsection",              455.25),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.00%; status: VALID; size: 571.06GB; nevents: 19.46M; release: 9_4_9; last modified: 2019-02-10 17:45:04"),
])

meta_dictionary["/DY3JetsToLL_M-10to50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Sep30_DY3JetsToLL_M-10to50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2"),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DY3JetsToLL_M-10to50"),
  ("nof_db_events",         4964197),
  ("nof_db_files",          36),
  ("fsize_db",              157220526981),
  ("xsection",              111.81),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 157.22GB; nevents: 4.96M; release: 9_4_9; last modified: 2019-03-02 20:47:03"),
])

meta_dictionary["/DY4JetsToLL_M-10to50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Oct23_DY4JetsToLL_M-10to50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2"),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DY4JetsToLL_M-10to50"),
  ("nof_db_events",         2087849),
  ("nof_db_files",          18),
  ("fsize_db",              74436479210),
  ("xsection",              43.12),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 74.44GB; nevents: 2.09M; release: 9_4_9; last modified: 2019-03-14 15:38:31"),
])

meta_dictionary["/DYJetsToLL_M-5to50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Nov25_DYJetsToLL_M-5to50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2"),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DYJetsToLL_M-5to50_HT-100to200"),
  ("nof_db_events",         1008250),
  ("nof_db_files",          7),
  ("fsize_db",              32622487452),
  ("xsection",              262.89),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 32.62GB; nevents: 1.01M; release: 9_4_9; last modified: 2018-11-18 14:33:25"),
])

meta_dictionary["/DYJetsToLL_M-5to50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Oct23_DYJetsToLL_M-5to50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1"),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DYJetsToLL_M-5to50_HT-100to200_ext1"),
  ("nof_db_events",         8583596),
  ("nof_db_files",          70),
  ("fsize_db",              278893599730),
  ("xsection",              262.89),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "96.51%; status: VALID; size: 278.89GB; nevents: 8.58M; release: 9_4_9; last modified: 2018-11-29 01:18:45"),
])

meta_dictionary["/DYJetsToLL_M-5to50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Oct23_DYJetsToLL_M-5to50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2"),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DYJetsToLL_M-5to50_HT-200to400"),
  ("nof_db_events",         1045127),
  ("nof_db_files",          9),
  ("fsize_db",              39497917957),
  ("xsection",              44.52),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 39.50GB; nevents: 1.05M; release: 9_4_9; last modified: 2018-11-18 08:33:24"),
])

meta_dictionary["/DYJetsToLL_M-5to50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Oct23_DYJetsToLL_M-5to50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1"),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DYJetsToLL_M-5to50_HT-200to400_ext1"),
  ("nof_db_events",         2077880),
  ("nof_db_files",          21),
  ("fsize_db",              78367782998),
  ("xsection",              44.52),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "95.24%; status: VALID; size: 78.37GB; nevents: 2.08M; release: 9_4_9; last modified: 2018-11-25 08:27:47"),
])

meta_dictionary["/DYJetsToLL_M-5to50_HT-400to600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Sep30_DYJetsToLL_M-5to50_HT-400to600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2"),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DYJetsToLL_M-5to50_HT-400to600"),
  ("nof_db_events",         1016799),
  ("nof_db_files",          8),
  ("fsize_db",              44119485779),
  ("xsection",              4.284),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 44.12GB; nevents: 1.02M; release: 9_4_9; last modified: 2018-11-18 16:22:22"),
])

meta_dictionary["/DYJetsToLL_M-5to50_HT-400to600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Nov25_DYJetsToLL_M-5to50_HT-400to600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1"),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DYJetsToLL_M-5to50_HT-400to600_ext1"),
  ("nof_db_events",         2071405),
  ("nof_db_files",          18),
  ("fsize_db",              90110016244),
  ("xsection",              4.284),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "52.38%; status: VALID; size: 90.11GB; nevents: 2.07M; release: 9_4_9; last modified: 2018-11-27 18:44:17"),
])

meta_dictionary["/DYJetsToLL_M-5to50_HT-600toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Sep30_DYJetsToLL_M-5to50_HT-600toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2"),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DYJetsToLL_M-5to50_HT-600toInf"),
  ("nof_db_events",         1021077),
  ("nof_db_files",          8),
  ("fsize_db",              49930642077),
  ("xsection",              1.293),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 49.93GB; nevents: 1.02M; release: 9_4_9; last modified: 2018-11-17 22:08:22"),
])

meta_dictionary["/DYJetsToLL_M-5to50_HT-600toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Oct23_DYJetsToLL_M-5to50_HT-600toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1"),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DYJetsToLL_M-5to50_HT-600toInf_ext1"),
  ("nof_db_events",         2017380),
  ("nof_db_files",          15),
  ("fsize_db",              98595971175),
  ("xsection",              1.293),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 98.60GB; nevents: 2.02M; release: 9_4_9; last modified: 2019-03-02 00:44:22"),
])

meta_dictionary["/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Oct29_CHUNK0_DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v2"),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DYJetsToLL_M-50_ext1"),
  ("nof_db_events",         49748967),
  ("nof_db_files",          360),
  ("fsize_db",              1453769168837),
  ("xsection",              6077.22),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.00%; status: VALID; size: 1.45TB; nevents: 49.75M; release: 9_4_9; last modified: 2018-11-05 09:13:14"),
])

meta_dictionary["/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext2-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Nov25_CHUNK0_DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext2-v2"),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DYJetsToLL_M-50_ext2"),
  ("nof_db_events",         96531428),
  ("nof_db_files",          701),
  ("fsize_db",              2831155987616),
  ("xsection",              6077.22),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.00%; status: VALID; size: 2.83TB; nevents: 96.53M; release: 9_4_9; last modified: 2018-11-17 18:08:34"),
])

meta_dictionary["/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext2-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Oct29_CHUNK0_DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext2-v1"),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DYJetsToLL_M-50_amcatnloFXFX_ext2"),
  ("nof_db_events",         120777245),
  ("nof_db_files",          871),
  ("fsize_db",              3525213031335),
  ("xsection",              6077.22),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "100.00%; status: VALID; size: 3.53TB; nevents: 120.78M; release: 9_4_9; last modified: 2018-10-07 00:37:00"),
])

meta_dictionary["/DY1JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Sep30_CHUNK0_DY1JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v1"),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DY1JetsToLL_M-50"),
  ("nof_db_events",         63730337),
  ("nof_db_files",          475),
  ("fsize_db",              1975229807254),
  ("xsection",              998.61),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "98.47%; status: VALID; size: 1.98TB; nevents: 63.73M; release: 9_4_9; last modified: 2018-12-23 20:07:59"),
])

meta_dictionary["/DY2JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Nov25_DY2JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2"),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DY2JetsToLL_M-50"),
  ("nof_db_events",         19879279),
  ("nof_db_files",          144),
  ("fsize_db",              665323381795),
  ("xsection",              349.25),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 665.32GB; nevents: 19.88M; release: 9_4_9; last modified: 2018-12-30 05:41:12"),
])

meta_dictionary["/DY3JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Oct29_DY3JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2"),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DY3JetsToLL_M-50"),
  ("nof_db_events",         5857441),
  ("nof_db_files",          48),
  ("fsize_db",              212438796731),
  ("xsection",              127.52),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 212.44GB; nevents: 5.86M; release: 9_4_9; last modified: 2019-01-04 11:00:12"),
])

meta_dictionary["/DY4JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Oct23_DY4JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2"),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DY4JetsToLL_M-50"),
  ("nof_db_events",         4197868),
  ("nof_db_files",          30),
  ("fsize_db",              169839944436),
  ("xsection",              50.039),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 169.84GB; nevents: 4.20M; release: 9_4_9; last modified: 2018-12-26 10:08:24"),
])

meta_dictionary["/DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Nov25_DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2"),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DYJetsToLL_M50_HT100to200"),
  ("nof_db_events",         2751187),
  ("nof_db_files",          20),
  ("fsize_db",              99023772526),
  ("xsection",              183.53),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "75.0%; status: VALID; size: 99.02GB; nevents: 2.75M; release: 9_4_9; last modified: 2018-12-06 16:50:41"),
])

meta_dictionary["/DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Oct29_DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v2"),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DYJetsToLL_M50_HT100to200_ext1"),
  ("nof_db_events",         8265899),
  ("nof_db_files",          73),
  ("fsize_db",              299870117814),
  ("xsection",              183.53),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "93.98%; status: VALID; size: 299.87GB; nevents: 8.27M; release: 9_4_9; last modified: 2018-11-19 06:21:52"),
])

meta_dictionary["/DYJetsToLL_M-50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Sep30_DYJetsToLL_M-50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2"),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DYJetsToLL_M50_HT200to400"),
  ("nof_db_events",         962195),
  ("nof_db_files",          12),
  ("fsize_db",              39589451138),
  ("xsection",              55.411),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 39.59GB; nevents: 962.20k; release: 9_4_9; last modified: 2018-11-18 16:23:27"),
])

meta_dictionary["/DYJetsToLL_M-50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Oct29_DYJetsToLL_M-50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v2"),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DYJetsToLL_M50_HT200to400_ext1"),
  ("nof_db_events",         8646942),
  ("nof_db_files",          68),
  ("fsize_db",              353330107045),
  ("xsection",              55.411),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 353.33GB; nevents: 8.65M; release: 9_4_9; last modified: 2018-11-18 19:01:33"),
])

meta_dictionary["/DYJetsToLL_M-50_HT-400to600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Nov25_DYJetsToLL_M-50_HT-400to600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2"),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DYJetsToLL_M50_HT400to600"),
  ("nof_db_events",         1070454),
  ("nof_db_files",          9),
  ("fsize_db",              49969495510),
  ("xsection",              7.9592),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 49.97GB; nevents: 1.07M; release: 9_4_9; last modified: 2018-11-18 20:36:59"),
])

meta_dictionary["/DYJetsToLL_M-50_HT-400to600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Nov25_DYJetsToLL_M-50_HT-400to600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v2"),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DYJetsToLL_M50_HT400to600_ext1"),
  ("nof_db_events",         8655207),
  ("nof_db_files",          76),
  ("fsize_db",              405134119563),
  ("xsection",              7.9592),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "58.62%; status: VALID; size: 405.13GB; nevents: 8.66M; release: 9_4_9; last modified: 2018-11-19 14:40:27"),
])

meta_dictionary["/DYJetsToLL_M-50_HT-600to800_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Nov25_DYJetsToLL_M-50_HT-600to800_TuneCUETP8M1_13TeV-madgraphMLM-pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2"),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DYJetsToLL_M50_HT600to800"),
  ("nof_db_events",         8292957),
  ("nof_db_files",          103),
  ("fsize_db",              422117016594),
  ("xsection",              2.0041),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 422.12GB; nevents: 8.29M; release: 9_4_9; last modified: 2018-11-21 08:55:56"),
])

meta_dictionary["/DYJetsToLL_M-50_HT-800to1200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Oct23_DYJetsToLL_M-50_HT-800to1200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v1"),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DYJetsToLL_M50_HT800to1200"),
  ("nof_db_events",         2673066),
  ("nof_db_files",          28),
  ("fsize_db",              142376357906),
  ("xsection",              0.92367),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "96.3%; status: VALID; size: 142.38GB; nevents: 2.67M; release: 9_4_9; last modified: 2018-11-19 13:17:12"),
])

meta_dictionary["/DYJetsToLL_M-50_HT-1200to2500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Nov25_DYJetsToLL_M-50_HT-1200to2500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v1"),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DYJetsToLL_M50_HT1200to2500"),
  ("nof_db_events",         596079),
  ("nof_db_files",          8),
  ("fsize_db",              34502618926),
  ("xsection",              0.22025),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 34.50GB; nevents: 596.08k; release: 9_4_9; last modified: 2018-11-19 05:19:31"),
])

meta_dictionary["/DYJetsToLL_M-50_HT-2500toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Oct23_DYJetsToLL_M-50_HT-2500toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v1"),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DYJetsToLL_M50_HT2500toInf"),
  ("nof_db_events",         399492),
  ("nof_db_files",          4),
  ("fsize_db",              24982088640),
  ("xsection",              0.004007),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 24.98GB; nevents: 399.49k; release: 9_4_9; last modified: 2018-11-19 17:42:15"),
])

meta_dictionary["/DYBBJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Sep30_DYBBJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2"),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DYBBJetsToLL_M-50"),
  ("nof_db_events",         2554303),
  ("nof_db_files",          18),
  ("fsize_db",              95636695840),
  ("xsection",              14.6),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 95.64GB; nevents: 2.55M; release: 9_4_9; last modified: 2019-03-02 05:13:50"),
])

meta_dictionary["/WJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Oct23_WJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v1"),
  ("sample_category",       "EWK"),
  ("process_name_specific", "WJetsToLNu"),
  ("nof_db_events",         24120319),
  ("nof_db_files",          174),
  ("fsize_db",              645881993756),
  ("xsection",              61526.7),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "99.17%; status: VALID; size: 645.88GB; nevents: 24.12M; release: 9_4_9; last modified: 2019-01-26 03:32:36"),
])

meta_dictionary["/WJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext2-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Oct23_CHUNK0_WJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext2-v1"),
  ("sample_category",       "EWK"),
  ("process_name_specific", "WJetsToLNu_ext2"),
  ("nof_db_events",         237263153),
  ("nof_db_files",          1690),
  ("fsize_db",              6349228046663),
  ("xsection",              61526.7),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "89.89%; status: VALID; size: 6.35TB; nevents: 237.26M; release: 9_4_9; last modified: 2019-01-27 10:45:03"),
])

meta_dictionary["/WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Sep30_WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2"),
  ("sample_category",       "EWK"),
  ("process_name_specific", "WJetsToLNu_madgraphMLM"),
  ("nof_db_events",         29514020),
  ("nof_db_files",          215),
  ("fsize_db",              793704629539),
  ("xsection",              61526.7),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 793.70GB; nevents: 29.51M; release: 9_4_9; last modified: 2018-11-29 19:31:11"),
])

meta_dictionary["/WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext2-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Oct29_CHUNK0_WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext2-v2"),
  ("sample_category",       "EWK"),
  ("process_name_specific", "WJetsToLNu_madgraphMLM_ext2"),
  ("nof_db_events",         57402435),
  ("nof_db_files",          410),
  ("fsize_db",              1550134936304),
  ("xsection",              61526.7),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "100.00%; status: VALID; size: 1.55TB; nevents: 57.40M; release: 9_4_9; last modified: 2018-11-14 08:57:15"),
])

meta_dictionary["/W1JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Oct23_W1JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v1"),
  ("sample_category",       "EWK"),
  ("process_name_specific", "W1JetsToLNu"),
  ("nof_db_events",         45283121),
  ("nof_db_files",          332),
  ("fsize_db",              1272250366716),
  ("xsection",              9442.49),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 1.27TB; nevents: 45.28M; release: 9_4_9; last modified: 2018-11-12 07:44:46"),
])

meta_dictionary["/W2JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Oct23_W2JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2"),
  ("sample_category",       "EWK"),
  ("process_name_specific", "W2JetsToLNu"),
  ("nof_db_events",         30064264),
  ("nof_db_files",          236),
  ("fsize_db",              915792344848),
  ("xsection",              3252.49),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "99.67%; status: VALID; size: 915.79GB; nevents: 30.06M; release: 9_4_9; last modified: 2019-05-10 23:05:33"),
])

meta_dictionary["/W2JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Oct23_CHUNK0_W2JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v2"),
  ("sample_category",       "EWK"),
  ("process_name_specific", "W2JetsToLNu_ext1"),
  ("nof_db_events",         30374504),
  ("nof_db_files",          225),
  ("fsize_db",              922766000017),
  ("xsection",              3252.49),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.00%; status: VALID; size: 922.77GB; nevents: 30.37M; release: 9_4_9; last modified: 2018-11-11 02:53:12"),
])

meta_dictionary["/W3JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Nov25_W3JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2"),
  ("sample_category",       "EWK"),
  ("process_name_specific", "W3JetsToLNu"),
  ("nof_db_events",         19798117),
  ("nof_db_files",          153),
  ("fsize_db",              651868160870),
  ("xsection",              1153.42),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "98.49%; status: VALID; size: 651.87GB; nevents: 19.80M; release: 9_4_9; last modified: 2019-05-14 04:40:41"),
])

meta_dictionary["/W3JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Oct23_CHUNK0_W3JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v2"),
  ("sample_category",       "EWK"),
  ("process_name_specific", "W3JetsToLNu_ext1"),
  ("nof_db_events",         39501912),
  ("nof_db_files",          291),
  ("fsize_db",              1299953115847),
  ("xsection",              1153.42),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "95.12%; status: VALID; size: 1.30TB; nevents: 39.50M; release: 9_4_9; last modified: 2018-12-08 01:52:14"),
])

meta_dictionary["/W4JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Oct23_W4JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2"),
  ("sample_category",       "EWK"),
  ("process_name_specific", "W4JetsToLNu"),
  ("nof_db_events",         9116657),
  ("nof_db_files",          81),
  ("fsize_db",              340719143876),
  ("xsection",              634.05),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 340.72GB; nevents: 9.12M; release: 9_4_9; last modified: 2019-05-03 07:08:35"),
])

meta_dictionary["/W4JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext2-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Nov25_W4JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext2-v1"),
  ("sample_category",       "EWK"),
  ("process_name_specific", "W4JetsToLNu_ext2"),
  ("nof_db_events",         18751462),
  ("nof_db_files",          143),
  ("fsize_db",              700950462106),
  ("xsection",              634.05),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 700.95GB; nevents: 18.75M; release: 9_4_9; last modified: 2018-10-09 00:57:41"),
])

meta_dictionary["/WJetsToLNu_HT-70To100_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Nov25_WJetsToLNu_HT-70To100_TuneCUETP8M1_13TeV-madgraphMLM-pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2"),
  ("sample_category",       "EWK"),
  ("process_name_specific", "WJetsToLNu_HT70To100"),
  ("nof_db_events",         10020533),
  ("nof_db_files",          81),
  ("fsize_db",              309269762266),
  ("xsection",              1504.92),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 309.27GB; nevents: 10.02M; release: 9_4_9; last modified: 2018-11-29 11:50:32"),
])

meta_dictionary["/WJetsToLNu_HT-100To200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Sep30_WJetsToLNu_HT-100To200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2"),
  ("sample_category",       "EWK"),
  ("process_name_specific", "WJetsToLNu_HT100To200"),
  ("nof_db_events",         9945478),
  ("nof_db_files",          72),
  ("fsize_db",              328826822871),
  ("xsection",              1625.08),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 328.83GB; nevents: 9.95M; release: 9_4_9; last modified: 2018-11-19 21:44:19"),
])

meta_dictionary["/WJetsToLNu_HT-100To200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Sep30_WJetsToLNu_HT-100To200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v2"),
  ("sample_category",       "EWK"),
  ("process_name_specific", "WJetsToLNu_HT100To200_ext1"),
  ("nof_db_events",         29503700),
  ("nof_db_files",          226),
  ("fsize_db",              976194222117),
  ("xsection",              1625.08),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "92.23%; status: VALID; size: 976.19GB; nevents: 29.50M; release: 9_4_9; last modified: 2019-01-18 17:29:35"),
])

meta_dictionary["/WJetsToLNu_HT-100To200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext2-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Nov25_CHUNK0_WJetsToLNu_HT-100To200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext2-v2"),
  ("sample_category",       "EWK"),
  ("process_name_specific", "WJetsToLNu_HT100To200_ext2"),
  ("nof_db_events",         38593839),
  ("nof_db_files",          283),
  ("fsize_db",              1278081592124),
  ("xsection",              1625.08),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.00%; status: VALID; size: 1.28TB; nevents: 38.59M; release: 9_4_9; last modified: 2019-03-29 23:30:12"),
])

meta_dictionary["/WJetsToLNu_HT-200To400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Sep30_WJetsToLNu_HT-200To400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2"),
  ("sample_category",       "EWK"),
  ("process_name_specific", "WJetsToLNu_HT200To400"),
  ("nof_db_events",         4963240),
  ("nof_db_files",          42),
  ("fsize_db",              188183889815),
  ("xsection",              477.96),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "98.0%; status: VALID; size: 188.18GB; nevents: 4.96M; release: 9_4_9; last modified: 2018-11-19 22:49:53"),
])

meta_dictionary["/WJetsToLNu_HT-200To400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Dec01_WJetsToLNu_HT-200To400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v2"),
  ("sample_category",       "EWK"),
  ("process_name_specific", "WJetsToLNu_HT200To400_ext1"),
  ("nof_db_events",         14106492),
  ("nof_db_files",          111),
  ("fsize_db",              533651324579),
  ("xsection",              477.96),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 533.65GB; nevents: 14.11M; release: 9_4_9; last modified: 2018-11-20 00:38:22"),
])

meta_dictionary["/WJetsToLNu_HT-200To400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext2-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Nov25_CHUNK0_WJetsToLNu_HT-200To400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext2-v2"),
  ("sample_category",       "EWK"),
  ("process_name_specific", "WJetsToLNu_HT200To400_ext2"),
  ("nof_db_events",         19914590),
  ("nof_db_files",          155),
  ("fsize_db",              749970418257),
  ("xsection",              477.96),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.00%; status: VALID; size: 749.97GB; nevents: 19.91M; release: 9_4_9; last modified: 2018-11-21 14:53:13"),
])

meta_dictionary["/WJetsToLNu_HT-400To600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Sep30_WJetsToLNu_HT-400To600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2"),
  ("sample_category",       "EWK"),
  ("process_name_specific", "WJetsToLNu_HT400To600"),
  ("nof_db_events",         1963464),
  ("nof_db_files",          19),
  ("fsize_db",              85028221355),
  ("xsection",              67.441),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "90.0%; status: VALID; size: 85.03GB; nevents: 1.96M; release: 9_4_9; last modified: 2018-11-19 05:21:27"),
])

meta_dictionary["/WJetsToLNu_HT-400To600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Oct23_WJetsToLNu_HT-400To600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v2"),
  ("sample_category",       "EWK"),
  ("process_name_specific", "WJetsToLNu_HT400To600_ext1"),
  ("nof_db_events",         5796237),
  ("nof_db_files",          51),
  ("fsize_db",              248677347048),
  ("xsection",              67.441),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "94.92%; status: VALID; size: 248.68GB; nevents: 5.80M; release: 9_4_9; last modified: 2018-11-19 05:20:48"),
])

meta_dictionary["/WJetsToLNu_HT-600To800_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Sep30_WJetsToLNu_HT-600To800_TuneCUETP8M1_13TeV-madgraphMLM-pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2"),
  ("sample_category",       "EWK"),
  ("process_name_specific", "WJetsToLNu_HT600To800"),
  ("nof_db_events",         3779141),
  ("nof_db_files",          33),
  ("fsize_db",              176087256349),
  ("xsection",              15.096),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 176.09GB; nevents: 3.78M; release: 9_4_9; last modified: 2018-11-18 01:01:07"),
])

meta_dictionary["/WJetsToLNu_HT-600To800_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Sep30_WJetsToLNu_HT-600To800_TuneCUETP8M1_13TeV-madgraphMLM-pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v2"),
  ("sample_category",       "EWK"),
  ("process_name_specific", "WJetsToLNu_HT600To800_ext1"),
  ("nof_db_events",         14908339),
  ("nof_db_files",          124),
  ("fsize_db",              694236154129),
  ("xsection",              15.096),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "94.67%; status: VALID; size: 694.24GB; nevents: 14.91M; release: 9_4_9; last modified: 2018-11-18 13:33:38"),
])

meta_dictionary["/WJetsToLNu_HT-800To1200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Nov25_WJetsToLNu_HT-800To1200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2"),
  ("sample_category",       "EWK"),
  ("process_name_specific", "WJetsToLNu_HT800To1200"),
  ("nof_db_events",         1544513),
  ("nof_db_files",          16),
  ("fsize_db",              76241472857),
  ("xsection",              6.3626),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 76.24GB; nevents: 1.54M; release: 9_4_9; last modified: 2018-11-18 14:36:29"),
])

meta_dictionary["/WJetsToLNu_HT-800To1200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Sep30_WJetsToLNu_HT-800To1200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v2"),
  ("sample_category",       "EWK"),
  ("process_name_specific", "WJetsToLNu_HT800To1200_ext1"),
  ("nof_db_events",         6286023),
  ("nof_db_files",          60),
  ("fsize_db",              310009927010),
  ("xsection",              6.3626),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "92.06%; status: VALID; size: 310.01GB; nevents: 6.29M; release: 9_4_9; last modified: 2018-11-19 21:41:23"),
])

meta_dictionary["/WJetsToLNu_HT-1200To2500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Sep30_WJetsToLNu_HT-1200To2500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2"),
  ("sample_category",       "EWK"),
  ("process_name_specific", "WJetsToLNu_HT1200To2500"),
  ("nof_db_events",         244532),
  ("nof_db_files",          3),
  ("fsize_db",              13089950528),
  ("xsection",              1.2658),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 13.09GB; nevents: 244.53k; release: 9_4_9; last modified: 2018-11-18 11:31:27"),
])

meta_dictionary["/WJetsToLNu_HT-1200To2500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Nov25_WJetsToLNu_HT-1200To2500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v2"),
  ("sample_category",       "EWK"),
  ("process_name_specific", "WJetsToLNu_HT1200To2500_ext1"),
  ("nof_db_events",         6627909),
  ("nof_db_files",          68),
  ("fsize_db",              356245076053),
  ("xsection",              1.2658),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "95.52%; status: VALID; size: 356.25GB; nevents: 6.63M; release: 9_4_9; last modified: 2018-11-20 10:44:58"),
])

meta_dictionary["/WJetsToLNu_HT-2500ToInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Sep30_WJetsToLNu_HT-2500ToInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2"),
  ("sample_category",       "EWK"),
  ("process_name_specific", "WJetsToLNu_HT2500ToInf"),
  ("nof_db_events",         253561),
  ("nof_db_files",          5),
  ("fsize_db",              15307944970),
  ("xsection",              0.009405),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 15.31GB; nevents: 253.56k; release: 9_4_9; last modified: 2018-11-19 10:21:21"),
])

meta_dictionary["/WJetsToLNu_HT-2500ToInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Sep30_WJetsToLNu_HT-2500ToInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v2"),
  ("sample_category",       "EWK"),
  ("process_name_specific", "WJetsToLNu_HT2500ToInf_ext1"),
  ("nof_db_events",         2384260),
  ("nof_db_files",          25),
  ("fsize_db",              140626699613),
  ("xsection",              0.009405),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 140.63GB; nevents: 2.38M; release: 9_4_9; last modified: 2018-11-18 23:28:28"),
])

meta_dictionary["/WWTo2L2Nu_13TeV-powheg/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Sep30_WWTo2L2Nu_13TeV-powheg__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2"),
  ("sample_category",       "WW"),
  ("process_name_specific", "WWTo2L2Nu"),
  ("nof_db_events",         1999000),
  ("nof_db_files",          16),
  ("fsize_db",              63758487635),
  ("xsection",              12.2),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 63.76GB; nevents: 2.00M; release: 9_4_9; last modified: 2019-01-22 22:58:50"),
])

meta_dictionary["/WWToLNuQQ_13TeV-powheg/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Sep30_WWToLNuQQ_13TeV-powheg__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2"),
  ("sample_category",       "WW"),
  ("process_name_specific", "WWToLNuQQ"),
  ("nof_db_events",         1999200),
  ("nof_db_files",          18),
  ("fsize_db",              65976939838),
  ("xsection",              50.45),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 65.98GB; nevents: 2.00M; release: 9_4_9; last modified: 2018-12-24 00:52:07"),
])

meta_dictionary["/WWToLNuQQ_13TeV-powheg/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Oct23_WWToLNuQQ_13TeV-powheg__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v2"),
  ("sample_category",       "WW"),
  ("process_name_specific", "WWToLNuQQ_ext1"),
  ("nof_db_events",         6655400),
  ("nof_db_files",          79),
  ("fsize_db",              223926394138),
  ("xsection",              50.45),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 223.93GB; nevents: 6.66M; release: 9_4_9; last modified: 2019-02-23 09:19:58"),
])

meta_dictionary["/WWTo1L1Nu2Q_13TeV_amcatnloFXFX_madspin_pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Oct23_WWTo1L1Nu2Q_13TeV_amcatnloFXFX_madspin_pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2"),
  ("sample_category",       "WW"),
  ("process_name_specific", "WWTo1L1Nu2Q"),
  ("nof_db_events",         5246469),
  ("nof_db_files",          38),
  ("fsize_db",              172027673160),
  ("xsection",              50.45),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 172.03GB; nevents: 5.25M; release: 9_4_9; last modified: 2018-11-26 11:31:19"),
])

meta_dictionary["/WWTo4Q_13TeV-powheg/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Nov25_WWTo4Q_13TeV-powheg__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2"),
  ("sample_category",       "WW"),
  ("process_name_specific", "WWTo4Q"),
  ("nof_db_events",         1998400),
  ("nof_db_files",          14),
  ("fsize_db",              67489035622),
  ("xsection",              52.15),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 67.49GB; nevents: 2.00M; release: 9_4_9; last modified: 2019-01-14 14:16:17"),
])

meta_dictionary["/WZTo3LNu_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Sep30_WZTo3LNu_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2"),
  ("sample_category",       "WZ"),
  ("process_name_specific", "WZTo3LNu"),
  ("nof_db_events",         11928707),
  ("nof_db_files",          91),
  ("fsize_db",              374708263805),
  ("xsection",              4.43),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 374.71GB; nevents: 11.93M; release: 9_4_9; last modified: 2018-11-18 05:11:22"),
])

meta_dictionary["/WZTo3LNu_TuneCUETP8M1_13TeV-powheg-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Sep30_WZTo3LNu_TuneCUETP8M1_13TeV-powheg-pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v1"),
  ("sample_category",       "WZ"),
  ("process_name_specific", "WZTo3LNu_powheg_ext1"),
  ("nof_db_events",         18000000),
  ("nof_db_files",          130),
  ("fsize_db",              565443889573),
  ("xsection",              4.43),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "97.79%; status: VALID; size: 565.44GB; nevents: 18.00M; release: 9_4_9; last modified: 2018-10-22 18:56:41"),
])

meta_dictionary["/WZTo3LNu_0Jets_MLL-4To50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Sep30_WZTo3LNu_0Jets_MLL-4To50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v1"),
  ("sample_category",       "WZ"),
  ("process_name_specific", "WZTo3LNu_0Jets_MLL-4to50"),
  ("nof_db_events",         518917),
  ("nof_db_files",          5),
  ("fsize_db",              14858474111),
  ("xsection",              2.3986),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 14.86GB; nevents: 518.92k; release: 9_4_9; last modified: 2018-10-19 01:10:42"),
])

meta_dictionary["/WZTo3LNu_0Jets_MLL-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Sep30_WZTo3LNu_0Jets_MLL-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v1"),
  ("sample_category",       "WZ"),
  ("process_name_specific", "WZTo3LNu_0Jets_MLL-50"),
  ("nof_db_events",         496684),
  ("nof_db_files",          5),
  ("fsize_db",              16240886055),
  ("xsection",              0.6067),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 16.24GB; nevents: 496.68k; release: 9_4_9; last modified: 2018-10-14 13:42:13"),
])

meta_dictionary["/WZTo3LNu_1Jets_MLL-4To50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Sep30_WZTo3LNu_1Jets_MLL-4To50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2"),
  ("sample_category",       "WZ"),
  ("process_name_specific", "WZTo3LNu_1Jets_MLL-4to50"),
  ("nof_db_events",         469574),
  ("nof_db_files",          5),
  ("fsize_db",              15275534008),
  ("xsection",              0.46107),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 15.28GB; nevents: 469.57k; release: 9_4_9; last modified: 2019-02-22 13:52:46"),
])

meta_dictionary["/WZTo3LNu_1Jets_MLL-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Oct23_WZTo3LNu_1Jets_MLL-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v1"),
  ("sample_category",       "WZ"),
  ("process_name_specific", "WZTo3LNu_1Jets_MLL-50"),
  ("nof_db_events",         463539),
  ("nof_db_files",          4),
  ("fsize_db",              17028271215),
  ("xsection",              0.3226),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 17.03GB; nevents: 463.54k; release: 9_4_9; last modified: 2018-09-29 16:02:45"),
])

meta_dictionary["/WZTo3LNu_2Jets_MLL-4To50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Sep30_WZTo3LNu_2Jets_MLL-4To50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v1"),
  ("sample_category",       "WZ"),
  ("process_name_specific", "WZTo3LNu_2Jets_MLL-4to50"),
  ("nof_db_events",         2435926),
  ("nof_db_files",          19),
  ("fsize_db",              89887588430),
  ("xsection",              0.15607),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "96.0%; status: VALID; size: 89.89GB; nevents: 2.44M; release: 9_4_9; last modified: 2018-10-09 15:02:27"),
])

meta_dictionary["/WZTo3LNu_2Jets_MLL-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Oct23_WZTo3LNu_2Jets_MLL-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v1"),
  ("sample_category",       "WZ"),
  ("process_name_specific", "WZTo3LNu_2Jets_MLL-50"),
  ("nof_db_events",         2280179),
  ("nof_db_files",          17),
  ("fsize_db",              95514909835),
  ("xsection",              0.06314),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 95.51GB; nevents: 2.28M; release: 9_4_9; last modified: 2018-09-30 03:36:15"),
])

meta_dictionary["/WZTo3LNu_3Jets_MLL-4To50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Oct23_WZTo3LNu_3Jets_MLL-4To50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v1"),
  ("sample_category",       "WZ"),
  ("process_name_specific", "WZTo3LNu_3Jets_MLL-4to50"),
  ("nof_db_events",         2424269),
  ("nof_db_files",          25),
  ("fsize_db",              102029703019),
  ("xsection",              0.06769),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 102.03GB; nevents: 2.42M; release: 9_4_9; last modified: 2018-10-18 23:58:08"),
])

meta_dictionary["/WZTo3LNu_3Jets_MLL-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Oct29_CHUNK0_WZTo3LNu_3Jets_MLL-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v1"),
  ("sample_category",       "WZ"),
  ("process_name_specific", "WZTo3LNu_3Jets_MLL-50"),
  ("nof_db_events",         2410585),
  ("nof_db_files",          18),
  ("fsize_db",              113650549747),
  ("xsection",              0.090512),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "97.14%; status: VALID; size: 113.65GB; nevents: 2.41M; release: 9_4_9; last modified: 2018-10-03 03:38:29"),
])

meta_dictionary["/WZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Nov25_CHUNK0_WZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2"),
  ("sample_category",       "WZ"),
  ("process_name_specific", "WZTo2L2Q"),
  ("nof_db_events",         26517272),
  ("nof_db_files",          197),
  ("fsize_db",              919865006859),
  ("xsection",              5.6),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.00%; status: VALID; size: 919.87GB; nevents: 26.52M; release: 9_4_9; last modified: 2018-11-11 04:01:12"),
])

meta_dictionary["/WZTo1L1Nu2Q_13TeV_amcatnloFXFX_madspin_pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Sep30_WZTo1L1Nu2Q_13TeV_amcatnloFXFX_madspin_pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2"),
  ("sample_category",       "WZ"),
  ("process_name_specific", "WZTo1L1Nu2Q"),
  ("nof_db_events",         24311445),
  ("nof_db_files",          188),
  ("fsize_db",              833536776680),
  ("xsection",              10.71),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 833.54GB; nevents: 24.31M; release: 9_4_9; last modified: 2018-11-11 15:16:15"),
])

meta_dictionary["/ZZTo4L_13TeV_powheg_pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Sep30_ZZTo4L_13TeV_powheg_pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v1"),
  ("sample_category",       "ZZ"),
  ("process_name_specific", "ZZTo4L"),
  ("nof_db_events",         6669988),
  ("nof_db_files",          50),
  ("fsize_db",              206407053220),
  ("xsection",              1.256),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 206.41GB; nevents: 6.67M; release: 9_4_9; last modified: 2018-10-04 05:09:35"),
])

meta_dictionary["/ZZTo4L_13TeV-amcatnloFXFX-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Sep30_ZZTo4L_13TeV-amcatnloFXFX-pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v2"),
  ("sample_category",       "ZZ"),
  ("process_name_specific", "ZZTo4L_amcatnloFXFX_ext1"),
  ("nof_db_events",         10711278),
  ("nof_db_files",          76),
  ("fsize_db",              328957846220),
  ("xsection",              1.256),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "99.07%; status: VALID; size: 328.96GB; nevents: 10.71M; release: 9_4_9; last modified: 2019-01-20 21:32:14"),
])

meta_dictionary["/ZZTo2L2Nu_13TeV_powheg_pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Oct23_ZZTo2L2Nu_13TeV_powheg_pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2"),
  ("sample_category",       "ZZ"),
  ("process_name_specific", "ZZTo2L2Nu"),
  ("nof_db_events",         8931750),
  ("nof_db_files",          74),
  ("fsize_db",              286633172052),
  ("xsection",              0.564),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "94.44%; status: VALID; size: 286.63GB; nevents: 8.93M; release: 9_4_9; last modified: 2019-02-02 00:00:11"),
])

meta_dictionary["/ZZTo2L2Nu_13TeV_powheg_pythia8_ext1/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Oct23_ZZTo2L2Nu_13TeV_powheg_pythia8_ext1__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2"),
  ("sample_category",       "ZZ"),
  ("process_name_specific", "ZZTo2L2Nu_ext1"),
  ("nof_db_events",         48655100),
  ("nof_db_files",          362),
  ("fsize_db",              1556906583517),
  ("xsection",              0.564),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "98.77%; status: VALID; size: 1.56TB; nevents: 48.66M; release: 9_4_9; last modified: 2018-11-29 14:10:51"),
])

meta_dictionary["/ZZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Oct23_ZZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v1"),
  ("sample_category",       "ZZ"),
  ("process_name_specific", "ZZTo2L2Q"),
  ("nof_db_events",         15462693),
  ("nof_db_files",          128),
  ("fsize_db",              536411748052),
  ("xsection",              5.52),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "92.26%; status: VALID; size: 536.41GB; nevents: 15.46M; release: 9_4_9; last modified: 2019-02-02 00:27:00"),
])

meta_dictionary["/QCD_Pt_15to20_bcToE_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Sep30_QCD_Pt_15to20_bcToE_TuneCUETP8M1_13TeV_pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2"),
  ("sample_category",       "QCD"),
  ("process_name_specific", "QCD_Pt15to20_bcToE"),
  ("nof_db_events",         2685602),
  ("nof_db_files",          21),
  ("fsize_db",              74364210723),
  ("xsection",              186900.0),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 74.36GB; nevents: 2.69M; release: 9_4_9; last modified: 2018-11-10 07:01:50"),
])

meta_dictionary["/QCD_Pt_20to30_bcToE_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Oct29_QCD_Pt_20to30_bcToE_TuneCUETP8M1_13TeV_pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2"),
  ("sample_category",       "QCD"),
  ("process_name_specific", "QCD_Pt20to30_bcToE"),
  ("nof_db_events",         10987947),
  ("nof_db_files",          82),
  ("fsize_db",              312373360334),
  ("xsection",              305400.0),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 312.37GB; nevents: 10.99M; release: 9_4_9; last modified: 2018-11-10 20:10:50"),
])

meta_dictionary["/QCD_Pt_30to80_bcToE_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Sep30_QCD_Pt_30to80_bcToE_TuneCUETP8M1_13TeV_pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2"),
  ("sample_category",       "QCD"),
  ("process_name_specific", "QCD_Pt30to80_bcToE"),
  ("nof_db_events",         15342783),
  ("nof_db_files",          119),
  ("fsize_db",              470284909238),
  ("xsection",              361100.0),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 470.28GB; nevents: 15.34M; release: 9_4_9; last modified: 2018-11-15 17:58:47"),
])

meta_dictionary["/QCD_Pt_80to170_bcToE_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv3-PUMoriond17_backup_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Sep30_QCD_Pt_80to170_bcToE_TuneCUETP8M1_13TeV_pythia8__RunIISummer16MiniAODv3-PUMoriond17_backup_94X_mcRun2_asymptotic_v3-v2"),
  ("sample_category",       "QCD"),
  ("process_name_specific", "QCD_Pt80to170_bcToE_backup"),
  ("nof_db_events",         14851987),
  ("nof_db_files",          115),
  ("fsize_db",              533420873496),
  ("xsection",              33820.0),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 533.42GB; nevents: 14.85M; release: 9_4_9; last modified: 2018-11-11 14:54:31"),
])

meta_dictionary["/QCD_Pt_170to250_bcToE_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Sep30_QCD_Pt_170to250_bcToE_TuneCUETP8M1_13TeV_pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2"),
  ("sample_category",       "QCD"),
  ("process_name_specific", "QCD_Pt170to250_bcToE"),
  ("nof_db_events",         9862070),
  ("nof_db_files",          87),
  ("fsize_db",              399943710216),
  ("xsection",              2130.0),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 399.94GB; nevents: 9.86M; release: 9_4_9; last modified: 2018-11-11 01:50:52"),
])

meta_dictionary["/QCD_Pt_250toInf_bcToE_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Nov25_QCD_Pt_250toInf_bcToE_TuneCUETP8M1_13TeV_pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2"),
  ("sample_category",       "QCD"),
  ("process_name_specific", "QCD_Pt250toInf_bcToE"),
  ("nof_db_events",         9861593),
  ("nof_db_files",          97),
  ("fsize_db",              435506733560),
  ("xsection",              563.0),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "96.97%; status: VALID; size: 435.51GB; nevents: 9.86M; release: 9_4_9; last modified: 2018-11-10 23:53:50"),
])

meta_dictionary["/QCD_Pt-20to30_EMEnriched_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Oct23_QCD_Pt-20to30_EMEnriched_TuneCUETP8M1_13TeV_pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2"),
  ("sample_category",       "QCD"),
  ("process_name_specific", "QCD_Pt20to30_EMEnriched"),
  ("nof_db_events",         9241500),
  ("nof_db_files",          74),
  ("fsize_db",              252735055673),
  ("xsection",              4912000.0),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 252.74GB; nevents: 9.24M; release: 9_4_9; last modified: 2018-11-27 05:46:56"),
])

meta_dictionary["/QCD_Pt-30to50_EMEnriched_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Sep30_QCD_Pt-30to50_EMEnriched_TuneCUETP8M1_13TeV_pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2"),
  ("sample_category",       "QCD"),
  ("process_name_specific", "QCD_Pt30to50_EMEnriched"),
  ("nof_db_events",         4736443),
  ("nof_db_files",          34),
  ("fsize_db",              134869337617),
  ("xsection",              6420000.0),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 134.87GB; nevents: 4.74M; release: 9_4_9; last modified: 2018-11-09 01:56:21"),
])

meta_dictionary["/QCD_Pt-30to50_EMEnriched_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Oct23_QCD_Pt-30to50_EMEnriched_TuneCUETP8M1_13TeV_pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v2"),
  ("sample_category",       "QCD"),
  ("process_name_specific", "QCD_Pt30to50_EMEnriched_ext1"),
  ("nof_db_events",         6772399),
  ("nof_db_files",          50),
  ("fsize_db",              192959364085),
  ("xsection",              6420000.0),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 192.96GB; nevents: 6.77M; release: 9_4_9; last modified: 2018-11-16 06:10:25"),
])

meta_dictionary["/QCD_Pt-50to80_EMEnriched_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Sep30_QCD_Pt-50to80_EMEnriched_TuneCUETP8M1_13TeV_pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2"),
  ("sample_category",       "QCD"),
  ("process_name_specific", "QCD_Pt50to80_EMEnriched"),
  ("nof_db_events",         22455794),
  ("nof_db_files",          171),
  ("fsize_db",              687785839317),
  ("xsection",              1988000.0),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 687.79GB; nevents: 22.46M; release: 9_4_9; last modified: 2018-11-15 23:43:57"),
])

meta_dictionary["/QCD_Pt-50to80_EMEnriched_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Oct23_QCD_Pt-50to80_EMEnriched_TuneCUETP8M1_13TeV_pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v2"),
  ("sample_category",       "QCD"),
  ("process_name_specific", "QCD_Pt50to80_EMEnriched_ext1"),
  ("nof_db_events",         23333265),
  ("nof_db_files",          171),
  ("fsize_db",              713692515456),
  ("xsection",              1988000.0),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "97.01%; status: VALID; size: 713.69GB; nevents: 23.33M; release: 9_4_9; last modified: 2018-11-15 19:53:41"),
])

meta_dictionary["/QCD_Pt-80to120_EMEnriched_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Nov25_QCD_Pt-80to120_EMEnriched_TuneCUETP8M1_13TeV_pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2"),
  ("sample_category",       "QCD"),
  ("process_name_specific", "QCD_Pt80to120_EMEnriched"),
  ("nof_db_events",         35926841),
  ("nof_db_files",          268),
  ("fsize_db",              1194513636207),
  ("xsection",              366500.0),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 1.19TB; nevents: 35.93M; release: 9_4_9; last modified: 2018-11-13 09:54:26"),
])

meta_dictionary["/QCD_Pt-80to120_EMEnriched_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Sep30_QCD_Pt-80to120_EMEnriched_TuneCUETP8M1_13TeV_pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v2"),
  ("sample_category",       "QCD"),
  ("process_name_specific", "QCD_Pt80to120_EMEnriched_ext1"),
  ("nof_db_events",         41873363),
  ("nof_db_files",          309),
  ("fsize_db",              1391077094116),
  ("xsection",              366500.0),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 1.39TB; nevents: 41.87M; release: 9_4_9; last modified: 2018-11-12 20:59:12"),
])

meta_dictionary["/QCD_Pt-120to170_EMEnriched_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Oct29_QCD_Pt-120to170_EMEnriched_TuneCUETP8M1_13TeV_pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2"),
  ("sample_category",       "QCD"),
  ("process_name_specific", "QCD_Pt120to170_EMEnriched"),
  ("nof_db_events",         36015016),
  ("nof_db_files",          281),
  ("fsize_db",              1288337214275),
  ("xsection",              66510.0),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 1.29TB; nevents: 36.02M; release: 9_4_9; last modified: 2018-11-20 20:55:23"),
])

meta_dictionary["/QCD_Pt-120to170_EMEnriched_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Sep30_QCD_Pt-120to170_EMEnriched_TuneCUETP8M1_13TeV_pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v2"),
  ("sample_category",       "QCD"),
  ("process_name_specific", "QCD_Pt120to170_EMEnriched_ext1"),
  ("nof_db_events",         42563399),
  ("nof_db_files",          314),
  ("fsize_db",              1520724785350),
  ("xsection",              66510.0),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 1.52TB; nevents: 42.56M; release: 9_4_9; last modified: 2018-12-21 05:32:23"),
])

meta_dictionary["/QCD_Pt-170to300_EMEnriched_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Oct23_QCD_Pt-170to300_EMEnriched_TuneCUETP8M1_13TeV_pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2"),
  ("sample_category",       "QCD"),
  ("process_name_specific", "QCD_Pt170to300_EMEnriched"),
  ("nof_db_events",         11540163),
  ("nof_db_files",          95),
  ("fsize_db",              446095551951),
  ("xsection",              16560.0),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 446.10GB; nevents: 11.54M; release: 9_4_9; last modified: 2018-11-14 22:55:30"),
])

meta_dictionary["/QCD_Pt-300toInf_EMEnriched_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Oct29_QCD_Pt-300toInf_EMEnriched_TuneCUETP8M1_13TeV_pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2"),
  ("sample_category",       "QCD"),
  ("process_name_specific", "QCD_Pt300toInf_EMEnriched"),
  ("nof_db_events",         7380341),
  ("nof_db_files",          63),
  ("fsize_db",              318661638327),
  ("xsection",              1100.0),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 318.66GB; nevents: 7.38M; release: 9_4_9; last modified: 2018-12-09 14:55:30"),
])

meta_dictionary["/QCD_Pt-15to20_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Sep30_QCD_Pt-15to20_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2"),
  ("sample_category",       "QCD"),
  ("process_name_specific", "QCD_Pt15to20_Mu5"),
  ("nof_db_events",         4141251),
  ("nof_db_files",          31),
  ("fsize_db",              114361119790),
  ("xsection",              2811000.0),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 114.36GB; nevents: 4.14M; release: 9_4_9; last modified: 2018-11-09 01:17:57"),
])

meta_dictionary["/QCD_Pt-20to30_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Oct23_CHUNK0_QCD_Pt-20to30_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2"),
  ("sample_category",       "QCD"),
  ("process_name_specific", "QCD_Pt20to30_Mu5"),
  ("nof_db_events",         31878740),
  ("nof_db_files",          233),
  ("fsize_db",              904037890950),
  ("xsection",              2531000.0),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "84.79%; status: VALID; size: 904.04GB; nevents: 31.88M; release: 9_4_9; last modified: 2018-11-12 07:45:18"),
])

meta_dictionary["/QCD_Pt-30to50_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Nov25_CHUNK0_QCD_Pt-30to50_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2"),
  ("sample_category",       "QCD"),
  ("process_name_specific", "QCD_Pt30to50_Mu5"),
  ("nof_db_events",         29954815),
  ("nof_db_files",          220),
  ("fsize_db",              897435138629),
  ("xsection",              1367000.0),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "99.76%; status: VALID; size: 897.44GB; nevents: 29.95M; release: 9_4_9; last modified: 2018-11-19 08:44:22"),
])

meta_dictionary["/QCD_Pt-50to80_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Nov25_QCD_Pt-50to80_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2"),
  ("sample_category",       "QCD"),
  ("process_name_specific", "QCD_Pt50to80_Mu5"),
  ("nof_db_events",         19662175),
  ("nof_db_files",          145),
  ("fsize_db",              641727930379),
  ("xsection",              377900.0),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 641.73GB; nevents: 19.66M; release: 9_4_9; last modified: 2018-11-11 02:52:41"),
])

meta_dictionary["/QCD_Pt-80to120_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Oct23_QCD_Pt-80to120_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2"),
  ("sample_category",       "QCD"),
  ("process_name_specific", "QCD_Pt80to120_Mu5"),
  ("nof_db_events",         13895437),
  ("nof_db_files",          103),
  ("fsize_db",              497967273393),
  ("xsection",              88620.0),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "99.29%; status: VALID; size: 497.97GB; nevents: 13.90M; release: 9_4_9; last modified: 2018-12-04 11:59:35"),
])

meta_dictionary["/QCD_Pt-80to120_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Oct23_QCD_Pt-80to120_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v2"),
  ("sample_category",       "QCD"),
  ("process_name_specific", "QCD_Pt80to120_Mu5_ext1"),
  ("nof_db_events",         9809949),
  ("nof_db_files",          80),
  ("fsize_db",              351978029896),
  ("xsection",              88620.0),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 351.98GB; nevents: 9.81M; release: 9_4_9; last modified: 2018-11-09 16:55:55"),
])

meta_dictionary["/QCD_Pt-120to170_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Oct23_QCD_Pt-120to170_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2"),
  ("sample_category",       "QCD"),
  ("process_name_specific", "QCD_Pt120to170_Mu5"),
  ("nof_db_events",         7897731),
  ("nof_db_files",          59),
  ("fsize_db",              307470051834),
  ("xsection",              21190.0),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 307.47GB; nevents: 7.90M; release: 9_4_9; last modified: 2018-11-11 02:54:16"),
])

meta_dictionary["/QCD_Pt-120to170_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv3-PUMoriond17_backup_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Nov25_QCD_Pt-120to170_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8__RunIISummer16MiniAODv3-PUMoriond17_backup_94X_mcRun2_asymptotic_v3-v2"),
  ("sample_category",       "QCD"),
  ("process_name_specific", "QCD_Pt120to170_Mu5_backup"),
  ("nof_db_events",         11912231),
  ("nof_db_files",          102),
  ("fsize_db",              464564032830),
  ("xsection",              21190.0),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 464.56GB; nevents: 11.91M; release: 9_4_9; last modified: 2018-11-13 01:54:26"),
])

meta_dictionary["/QCD_Pt-170to300_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Oct29_QCD_Pt-170to300_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v1"),
  ("sample_category",       "QCD"),
  ("process_name_specific", "QCD_Pt170to300_Mu5"),
  ("nof_db_events",         7947159),
  ("nof_db_files",          62),
  ("fsize_db",              337373205537),
  ("xsection",              7020.0),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 337.37GB; nevents: 7.95M; release: 9_4_9; last modified: 2018-10-12 02:34:07"),
])

meta_dictionary["/QCD_Pt-170to300_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Oct29_QCD_Pt-170to300_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v2"),
  ("sample_category",       "QCD"),
  ("process_name_specific", "QCD_Pt170to300_Mu5_ext1"),
  ("nof_db_events",         9403072),
  ("nof_db_files",          71),
  ("fsize_db",              399116745624),
  ("xsection",              7020.0),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "97.89%; status: VALID; size: 399.12GB; nevents: 9.40M; release: 9_4_9; last modified: 2018-11-25 16:48:49"),
])

meta_dictionary["/QCD_Pt-170to300_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv3-PUMoriond17_backup_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Oct23_QCD_Pt-170to300_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8__RunIISummer16MiniAODv3-PUMoriond17_backup_94X_mcRun2_asymptotic_v3-v2"),
  ("sample_category",       "QCD"),
  ("process_name_specific", "QCD_Pt170to300_Mu5_backup"),
  ("nof_db_events",         19789673),
  ("nof_db_files",          157),
  ("fsize_db",              840579326313),
  ("xsection",              7020.0),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "97.49%; status: VALID; size: 840.58GB; nevents: 19.79M; release: 9_4_9; last modified: 2018-11-13 13:58:56"),
])

meta_dictionary["/QCD_Pt-300to470_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Oct23_QCD_Pt-300to470_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2"),
  ("sample_category",       "QCD"),
  ("process_name_specific", "QCD_Pt300to470_Mu5"),
  ("nof_db_events",         7937590),
  ("nof_db_files",          71),
  ("fsize_db",              375174129111),
  ("xsection",              620.2),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 375.17GB; nevents: 7.94M; release: 9_4_9; last modified: 2018-11-16 02:02:23"),
])

meta_dictionary["/QCD_Pt-300to470_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v1/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Nov25_QCD_Pt-300to470_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v1"),
  ("sample_category",       "QCD"),
  ("process_name_specific", "QCD_Pt300to470_Mu5_ext1"),
  ("nof_db_events",         16462878),
  ("nof_db_files",          126),
  ("fsize_db",              777723059467),
  ("xsection",              620.2),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 777.72GB; nevents: 16.46M; release: 9_4_9; last modified: 2018-10-04 16:51:50"),
])

meta_dictionary["/QCD_Pt-300to470_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext2-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Nov25_CHUNK0_QCD_Pt-300to470_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext2-v2"),
  ("sample_category",       "QCD"),
  ("process_name_specific", "QCD_Pt300to470_Mu5_ext2"),
  ("nof_db_events",         24605508),
  ("nof_db_files",          184),
  ("fsize_db",              1162027704606),
  ("xsection",              620.2),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "89.95%; status: VALID; size: 1.16TB; nevents: 24.61M; release: 9_4_9; last modified: 2018-11-13 09:51:10"),
])

meta_dictionary["/QCD_Pt-470to600_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Nov25_QCD_Pt-470to600_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2"),
  ("sample_category",       "QCD"),
  ("process_name_specific", "QCD_Pt470to600_Mu5"),
  ("nof_db_events",         3972819),
  ("nof_db_files",          41),
  ("fsize_db",              201761244068),
  ("xsection",              59.06),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 201.76GB; nevents: 3.97M; release: 9_4_9; last modified: 2018-11-10 15:54:24"),
])

meta_dictionary["/QCD_Pt-470to600_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Oct23_QCD_Pt-470to600_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v2"),
  ("sample_category",       "QCD"),
  ("process_name_specific", "QCD_Pt470to600_Mu5_ext1"),
  ("nof_db_events",         5668793),
  ("nof_db_files",          43),
  ("fsize_db",              287008158384),
  ("xsection",              59.06),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "94.74%; status: VALID; size: 287.01GB; nevents: 5.67M; release: 9_4_9; last modified: 2018-11-14 05:54:01"),
])

meta_dictionary["/QCD_Pt-470to600_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext2-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Nov25_QCD_Pt-470to600_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext2-v2"),
  ("sample_category",       "QCD"),
  ("process_name_specific", "QCD_Pt470to600_Mu5_ext2"),
  ("nof_db_events",         9847664),
  ("nof_db_files",          76),
  ("fsize_db",              498631831955),
  ("xsection",              59.06),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 498.63GB; nevents: 9.85M; release: 9_4_9; last modified: 2018-11-08 19:56:14"),
])

meta_dictionary["/QCD_Pt-600to800_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Oct23_QCD_Pt-600to800_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2"),
  ("sample_category",       "QCD"),
  ("process_name_specific", "QCD_Pt600to800_Mu5"),
  ("nof_db_events",         4010136),
  ("nof_db_files",          33),
  ("fsize_db",              211608983257),
  ("xsection",              18.2),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "97.56%; status: VALID; size: 211.61GB; nevents: 4.01M; release: 9_4_9; last modified: 2018-11-10 18:00:36"),
])

meta_dictionary["/QCD_Pt-600to800_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Nov25_QCD_Pt-600to800_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v2"),
  ("sample_category",       "QCD"),
  ("process_name_specific", "QCD_Pt600to800_Mu5_ext1"),
  ("nof_db_events",         5971175),
  ("nof_db_files",          50),
  ("fsize_db",              315127671581),
  ("xsection",              18.2),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 315.13GB; nevents: 5.97M; release: 9_4_9; last modified: 2018-11-11 12:04:35"),
])

meta_dictionary["/QCD_Pt-600to800_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv3-PUMoriond17_backup_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Nov25_QCD_Pt-600to800_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8__RunIISummer16MiniAODv3-PUMoriond17_backup_94X_mcRun2_asymptotic_v3-v2"),
  ("sample_category",       "QCD"),
  ("process_name_specific", "QCD_Pt600to800_Mu5_backup"),
  ("nof_db_events",         9928218),
  ("nof_db_files",          106),
  ("fsize_db",              525881357149),
  ("xsection",              18.2),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 525.88GB; nevents: 9.93M; release: 9_4_9; last modified: 2018-11-29 15:32:48"),
])

meta_dictionary["/QCD_Pt-800to1000_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Nov25_QCD_Pt-800to1000_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2"),
  ("sample_category",       "QCD"),
  ("process_name_specific", "QCD_Pt800to1000_Mu5"),
  ("nof_db_events",         3962749),
  ("nof_db_files",          41),
  ("fsize_db",              218078166039),
  ("xsection",              3.276),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 218.08GB; nevents: 3.96M; release: 9_4_9; last modified: 2018-11-10 23:54:38"),
])

meta_dictionary["/QCD_Pt-800to1000_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Sep30_QCD_Pt-800to1000_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v2"),
  ("sample_category",       "QCD"),
  ("process_name_specific", "QCD_Pt800to1000_Mu5_ext1"),
  ("nof_db_events",         6011849),
  ("nof_db_files",          47),
  ("fsize_db",              330161425748),
  ("xsection",              3.276),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "96.72%; status: VALID; size: 330.16GB; nevents: 6.01M; release: 9_4_9; last modified: 2018-11-26 08:48:03"),
])

meta_dictionary["/QCD_Pt-800to1000_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext2-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Oct29_QCD_Pt-800to1000_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext2-v2"),
  ("sample_category",       "QCD"),
  ("process_name_specific", "QCD_Pt800to1000_Mu5_ext2"),
  ("nof_db_events",         9966149),
  ("nof_db_files",          87),
  ("fsize_db",              549916645891),
  ("xsection",              3.276),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 549.92GB; nevents: 9.97M; release: 9_4_9; last modified: 2018-11-10 13:59:18"),
])

meta_dictionary["/QCD_Pt-1000toInf_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Sep30_QCD_Pt-1000toInf_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2"),
  ("sample_category",       "QCD"),
  ("process_name_specific", "QCD_Pt1000toInf_Mu5"),
  ("nof_db_events",         3990117),
  ("nof_db_files",          32),
  ("fsize_db",              227926254486),
  ("xsection",              1.079),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "97.5%; status: VALID; size: 227.93GB; nevents: 3.99M; release: 9_4_9; last modified: 2018-11-13 14:50:46"),
])

meta_dictionary["/QCD_Pt-1000toInf_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v2/MINIAODSIM"] =  OD([
  ("crab_string",           "2016v3_2019Sep30_QCD_Pt-1000toInf_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v2"),
  ("sample_category",       "QCD"),
  ("process_name_specific", "QCD_Pt1000toInf_Mu5_ext1"),
  ("nof_db_events",         9638102),
  ("nof_db_files",          101),
  ("fsize_db",              551501199580),
  ("xsection",              1.079),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "100.0%; status: VALID; size: 551.50GB; nevents: 9.64M; release: 9_4_9; last modified: 2018-11-11 15:39:44"),
])


# event statistics by sample category:
# ttH:        14.04M
# ttH_ctcvcp: 9.57M
# tHq:        23.05M
# tHW:        11.48M
# ggH:        18.94M
# qqH:        11.27M
# TTZ:        21.90M
# TTW:        9.82M
# TTWW:       98.30k
# TT:         621.40M
# TTWH:       100.00k
# TTZH:       97.80k
# Rares:      118.44M
# VH:         4.58M
# EWK:        1.35G
# WW:         17.90M
# WZ:         92.26M
# ZZ:         90.43M
# QCD:        593.70M

