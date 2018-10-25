from collections import OrderedDict as OD

# file generated at 2018-07-19 16:13:20 with the following command:
# find_samples.py -V -i ../NanoAOD/test/datasets_mc_2016.txt -m python/samples/metaDict_2016_mc.py -s ../NanoAOD/test/datasets_sum_2016.txt -v 8_0_0

meta_dictionary = OD()


### event sums

sum_events = {
  ("DYJetsToLL_M-10to50_amcatnloFXFX_v1", "DYJetsToLL_M-10to50_amcatnloFXFX_v2", "DYJetsToLL_M-10to50_amcatnloFXFX_v2_ext1"),
  ("DYJetsToLL_M-5to50_HT-100to200", "DYJetsToLL_M-5to50_HT-100to200_ext1"),
  ("DYJetsToLL_M-5to50_HT-200to400", "DYJetsToLL_M-5to50_HT-200to400_ext1"),
  ("DYJetsToLL_M-5to50_HT-400to600", "DYJetsToLL_M-5to50_HT-400to600_ext1"),
  ("DYJetsToLL_M-5to50_HT-600toInf", "DYJetsToLL_M-5to50_HT-600toInf_ext1"),
  ("DYJetsToLL_M-50_ext1", "DYJetsToLL_M-50_ext2"),
  ("DYJetsToLL_M50_HT100to200", "DYJetsToLL_M50_HT100to200_ext1"),
  ("DYJetsToLL_M50_HT200to400", "DYJetsToLL_M50_HT200to400_ext1"),
  ("DYJetsToLL_M50_HT400to600", "DYJetsToLL_M50_HT400to600_ext1"),
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
  ("ttHToNonbb_fastsim_p1", "ttHToNonbb_fastsim_p2", "ttHToNonbb_fastsim_p3"),
  ("TTJets_DiLept", "TTJets_DiLept_ext1"),
  ("TTJets_SingleLeptFromT", "TTJets_SingleLeptFromT_ext1"),
  ("TTJets_SingleLeptFromTbar", "TTJets_SingleLeptFromTbar_ext1"),
  ("TTTo2L2Nu_fastsim_p1", "TTTo2L2Nu_fastsim_p2", "TTTo2L2Nu_fastsim_p3"),
  ("TTToSemilepton_fastsim_p1", "TTToSemilepton_fastsim_p2", "TTToSemilepton_fastsim_p3"),
  ("TTWJetsToLNu_ext1", "TTWJetsToLNu_ext2"),
  ("TTZToLL_M10_ext1", "TTZToLL_M10_ext2", "TTZToLL_M10_ext3"),
  ("WJetsToLNu", "WJetsToLNu_ext2"),
  ("WJetsToLNu_madgraphMLM", "WJetsToLNu_madgraphMLM_ext2"),
  ("W2JetsToLNu", "W2JetsToLNu_ext1"),
  ("W3JetsToLNu", "W3JetsToLNu_ext1"),
  ("W4JetsToLNu", "W4JetsToLNu_ext1", "W4JetsToLNu_ext2"),
  ("WJetsToLNu_HT100To200", "WJetsToLNu_HT100To200_ext1", "WJetsToLNu_HT100To200_ext2"),
  ("WJetsToLNu_HT200To400", "WJetsToLNu_HT200To400_ext1", "WJetsToLNu_HT200To400_ext2"),
  ("WJetsToLNu_HT400To600", "WJetsToLNu_HT400To600_ext1"),
  ("WJetsToLNu_HT600To800", "WJetsToLNu_HT600To800_ext1"),
  ("WJetsToLNu_HT800To1200", "WJetsToLNu_HT800To1200_ext1"),
  ("WJetsToLNu_HT1200To2500", "WJetsToLNu_HT1200To2500_ext1"),
  ("WJetsToLNu_HT2500ToInf", "WJetsToLNu_HT2500ToInf_ext1"),
  ("WGToLNuG_ext1", "WGToLNuG_ext2", "WGToLNuG_ext3"),
  ("ZGTo2LG", "ZGTo2LG_ext1"),
  ("TGJets", "TGJets_ext1"),
  ("TTGJets", "TTGJets_ext1"),
}


meta_dictionary["/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "signal"),
  ("process_name_specific", "ttHJetToNonbb_M125_amcatnlo"),
  ("nof_db_events",         10045633),
  ("nof_db_files",          269),
  ("fsize_db",              526291716675),
  ("xsection",              0.2118),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 526.29GB; nevents: 10.05M; release: 8_0_21; last modified: 2017-01-31 22:15:53"),
])

meta_dictionary["/ttHJetTobb_M125_13TeV_amcatnloFXFX_madspin_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext3-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "signal"),
  ("process_name_specific", "ttHJetTobb_M125_amcatnlo"),
  ("nof_db_events",         9794226),
  ("nof_db_files",          224),
  ("fsize_db",              518904216922),
  ("xsection",              0.2953),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 518.90GB; nevents: 9.79M; release: 8_0_21; last modified: 2017-02-02 09:06:26"),
])

meta_dictionary["/ttHToNonbb_M125_TuneCUETP8M2_ttHtranche3_13TeV-powheg-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "signal"),
  ("process_name_specific", "ttHToNonbb_M125_powheg"),
  ("nof_db_events",         3981250),
  ("nof_db_files",          108),
  ("fsize_db",              209184824730),
  ("xsection",              0.2118),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 209.18GB; nevents: 3.98M; release: 8_0_21; last modified: 2016-12-11 20:21:58"),
])

meta_dictionary["/THQ_Hincl_13TeV-madgraph-pythia8_TuneCUETP8M1/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "tHq"),
  ("process_name_specific", "THQ"),
  ("nof_db_events",         3495799),
  ("nof_db_files",          52),
  ("fsize_db",              159053432604),
  ("xsection",              0.07096),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 159.05GB; nevents: 3.50M; release: 8_0_21; last modified: 2017-01-04 21:44:30"),
])

meta_dictionary["/THW_Hincl_13TeV-madgraph-pythia8_TuneCUETP8M1/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "tHW"),
  ("process_name_specific", "THW"),
  ("nof_db_events",         1499200),
  ("nof_db_files",          22),
  ("fsize_db",              79228993799),
  ("xsection",              0.01561),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 79.23GB; nevents: 1.50M; release: 8_0_21; last modified: 2016-12-24 18:21:43"),
])

meta_dictionary["/GluGluHToZZTo4L_M125_13TeV_powheg2_JHUgenV6_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "additional_signal_overlap"),
  ("process_name_specific", "GluGluHToZZTo4L"),
  ("nof_db_events",         999800),
  ("nof_db_files",          23),
  ("fsize_db",              36259596782),
  ("xsection",              0.01297),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 36.26GB; nevents: 999.80k; release: 8_0_21; last modified: 2016-12-13 01:00:36"),
])

meta_dictionary["/TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "TTZ"),
  ("process_name_specific", "TTZToLL_M10_ext1"),
  ("nof_db_events",         1992438),
  ("nof_db_files",          36),
  ("fsize_db",              97535774960),
  ("xsection",              0.2529),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 97.54GB; nevents: 1.99M; release: 8_0_21; last modified: 2016-11-30 08:13:25"),
])

meta_dictionary["/TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext2-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "TTZ"),
  ("process_name_specific", "TTZToLL_M10_ext2"),
  ("nof_db_events",         5982035),
  ("nof_db_files",          94),
  ("fsize_db",              292336758888),
  ("xsection",              0.2529),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 292.34GB; nevents: 5.98M; release: 8_0_21; last modified: 2017-02-03 09:41:00"),
])

meta_dictionary["/TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext3-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "TTZ"),
  ("process_name_specific", "TTZToLL_M10_ext3"),
  ("nof_db_events",         5934228),
  ("nof_db_files",          149),
  ("fsize_db",              290448333645),
  ("xsection",              0.2529),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 290.45GB; nevents: 5.93M; release: 8_0_21; last modified: 2017-03-11 08:55:14"),
])

meta_dictionary["/TTZToLL_M-1to10_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "TTZ"),
  ("process_name_specific", "TTZToLL_M-1to10"),
  ("nof_db_events",         246792),
  ("nof_db_files",          19),
  ("fsize_db",              12124688063),
  ("xsection",              0.0493),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 12.12GB; nevents: 246.79k; release: 8_0_21; last modified: 2017-01-04 21:28:39"),
])

meta_dictionary["/ttZJets_13TeV_madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "TTZ"),
  ("process_name_specific", "TTZJets_LO"),
  ("nof_db_events",         9874825),
  ("nof_db_files",          208),
  ("fsize_db",              505409280236),
  ("xsection",              0.8393),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 505.41GB; nevents: 9.87M; release: 8_0_21; last modified: 2017-03-01 14:23:06"),
])

meta_dictionary["/TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v3/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "TTW"),
  ("process_name_specific", "TTWJetsToLNu_ext1"),
  ("nof_db_events",         2160168),
  ("nof_db_files",          33),
  ("fsize_db",              106465986443),
  ("xsection",              0.2043),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 106.47GB; nevents: 2.16M; release: 8_0_21; last modified: 2016-12-23 05:50:32"),
])

meta_dictionary["/TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext2-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "TTW"),
  ("process_name_specific", "TTWJetsToLNu_ext2"),
  ("nof_db_events",         3120397),
  ("nof_db_files",          49),
  ("fsize_db",              154498243520),
  ("xsection",              0.2043),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 154.50GB; nevents: 3.12M; release: 8_0_21; last modified: 2016-11-16 01:29:02"),
])

meta_dictionary["/ttWJets_13TeV_madgraphMLM/RunIISummer16MiniAODv2-80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "TTW"),
  ("process_name_specific", "TTWJets_LO"),
  ("nof_db_events",         6972048),
  ("nof_db_files",          203),
  ("fsize_db",              352050210597),
  ("xsection",              0.6008),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 352.05GB; nevents: 6.97M; release: 8_0_21; last modified: 2017-01-05 19:59:10"),
])

meta_dictionary["/TTWW_TuneCUETP8M2T4_13TeV-madgraph-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v3/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "TTWW"),
  ("process_name_specific", "TTWW"),
  ("nof_db_events",         98692),
  ("nof_db_files",          10),
  ("fsize_db",              6355401897),
  ("xsection",              0.007834),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 6.36GB; nevents: 98.69k; release: 8_0_21; last modified: 2017-07-02 10:53:42"),
])

meta_dictionary["/ST_s-channel_4f_leptonDecays_13TeV-amcatnlo-pythia8_TuneCUETP8M1/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "TT"),
  ("process_name_specific", "ST_s-channel_4f_leptonDecays"),
  ("nof_db_events",         1000000),
  ("nof_db_files",          21),
  ("fsize_db",              34846873111),
  ("xsection",              3.36),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 34.85GB; nevents: 1.00M; release: 8_0_21; last modified: 2016-12-07 20:31:18"),
])

meta_dictionary["/ST_t-channel_antitop_4f_inclusiveDecays_13TeV-powhegV2-madspin-pythia8_TuneCUETP8M1/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "TT"),
  ("process_name_specific", "ST_t-channel_antitop_4f_inclusiveDecays"),
  ("nof_db_events",         38811017),
  ("nof_db_files",          406),
  ("fsize_db",              1410982422127),
  ("xsection",              80.95),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 1.41TB; nevents: 38.81M; release: 8_0_21; last modified: 2016-12-09 19:26:59"),
])

meta_dictionary["/ST_t-channel_top_4f_inclusiveDecays_13TeV-powhegV2-madspin-pythia8_TuneCUETP8M1/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "TT"),
  ("process_name_specific", "ST_t-channel_top_4f_inclusiveDecays"),
  ("nof_db_events",         67240808),
  ("nof_db_files",          723),
  ("fsize_db",              2450450426137),
  ("xsection",              136.02),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 2.45TB; nevents: 67.24M; release: 8_0_21; last modified: 2016-12-06 00:02:08"),
])

meta_dictionary["/ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "TT"),
  ("process_name_specific", "ST_tW_antitop_5f_inclusiveDecays"),
  ("nof_db_events",         6933094),
  ("nof_db_files",          144),
  ("fsize_db",              269982644061),
  ("xsection",              35.85),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 269.98GB; nevents: 6.93M; release: 8_0_21; last modified: 2016-12-11 00:44:33"),
])

meta_dictionary["/ST_tW_top_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "TT"),
  ("process_name_specific", "ST_tW_top_5f_inclusiveDecays"),
  ("nof_db_events",         6952830),
  ("nof_db_files",          161),
  ("fsize_db",              270606649204),
  ("xsection",              35.85),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 270.61GB; nevents: 6.95M; release: 8_0_21; last modified: 2016-12-15 22:19:28"),
])

meta_dictionary["/ST_tWll_5f_LO_13TeV_MadGraph_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "TT"),
  ("process_name_specific", "ST_tWll"),
  ("nof_db_events",         916072),
  ("nof_db_files",          44),
  ("fsize_db",              48763204959),
  ("xsection",              0.01103),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 48.76GB; nevents: 916.07k; release: 8_0_21; last modified: 2017-07-16 23:27:47"),
])

meta_dictionary["/TTTo2L2Nu_TuneCUETP8M2_ttHtranche3_13TeV-powheg-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "TT"),
  ("process_name_specific", "TTTo2L2Nu"),
  ("nof_db_events",         79092400),
  ("nof_db_files",          1464),
  ("fsize_db",              3387694712730),
  ("xsection",              88.29),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 3.39TB; nevents: 79.09M; release: 8_0_21; last modified: 2016-12-20 16:06:23"),
])

meta_dictionary["/TTToSemilepton_TuneCUETP8M2_ttHtranche3_13TeV-powheg-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "TT"),
  ("process_name_specific", "TTToSemiLepton"),
  ("nof_db_events",         152720952),
  ("nof_db_files",          2519),
  ("fsize_db",              6724822441375),
  ("xsection",              365.34),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 6.72TB; nevents: 152.72M; release: 8_0_21; last modified: 2017-01-06 06:48:33"),
])

meta_dictionary["/TTJets_DiLept_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "TT"),
  ("process_name_specific", "TTJets_DiLept"),
  ("nof_db_events",         6094476),
  ("nof_db_files",          83),
  ("fsize_db",              262031966527),
  ("xsection",              88.29),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 262.03GB; nevents: 6.09M; release: 8_0_21; last modified: 2016-12-08 12:00:08"),
])

meta_dictionary["/TTJets_DiLept_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "TT"),
  ("process_name_specific", "TTJets_DiLept_ext1"),
  ("nof_db_events",         24350202),
  ("nof_db_files",          342),
  ("fsize_db",              1048856825670),
  ("xsection",              88.29),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 1.05TB; nevents: 24.35M; release: 8_0_21; last modified: 2016-12-15 03:24:44"),
])

meta_dictionary["/TTJets_SingleLeptFromT_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "TT"),
  ("process_name_specific", "TTJets_SingleLeptFromT"),
  ("nof_db_events",         11957043),
  ("nof_db_files",          167),
  ("fsize_db",              529533711423),
  ("xsection",              182.67),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 529.53GB; nevents: 11.96M; release: 8_0_21; last modified: 2016-12-11 17:11:24"),
])

meta_dictionary["/TTJets_SingleLeptFromT_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "TT"),
  ("process_name_specific", "TTJets_SingleLeptFromT_ext1"),
  ("nof_db_events",         50016934),
  ("nof_db_files",          629),
  ("fsize_db",              2213857927517),
  ("xsection",              182.67),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 2.21TB; nevents: 50.02M; release: 8_0_21; last modified: 2016-12-15 03:17:48"),
])

meta_dictionary["/TTJets_SingleLeptFromTbar_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "TT"),
  ("process_name_specific", "TTJets_SingleLeptFromTbar"),
  ("nof_db_events",         11944041),
  ("nof_db_files",          196),
  ("fsize_db",              529634738825),
  ("xsection",              182.67),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 529.63GB; nevents: 11.94M; release: 8_0_21; last modified: 2017-01-10 08:13:09"),
])

meta_dictionary["/TTJets_SingleLeptFromTbar_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "TT"),
  ("process_name_specific", "TTJets_SingleLeptFromTbar_ext1"),
  ("nof_db_events",         48266353),
  ("nof_db_files",          559),
  ("fsize_db",              2132760517090),
  ("xsection",              182.67),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 2.13TB; nevents: 48.27M; release: 8_0_21; last modified: 2016-12-11 07:03:39"),
])

meta_dictionary["/DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DYJetsToLL_M-10to50"),
  ("nof_db_events",         35291566),
  ("nof_db_files",          555),
  ("fsize_db",              871330489678),
  ("xsection",              18610.0),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 871.33GB; nevents: 35.29M; release: 8_0_21; last modified: 2017-01-08 11:58:44"),
])

meta_dictionary["/DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DYJetsToLL_M-10to50_amcatnloFXFX_v1"),
  ("nof_db_events",         30920596),
  ("nof_db_files",          237),
  ("fsize_db",              735149680003),
  ("xsection",              18610.0),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 735.15GB; nevents: 30.92M; release: 8_0_21; last modified: 2017-01-21 02:33:58"),
])

meta_dictionary["/DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v2/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DYJetsToLL_M-10to50_amcatnloFXFX_v2"),
  ("nof_db_events",         65888233),
  ("nof_db_files",          765),
  ("fsize_db",              1566684913593),
  ("xsection",              18610.0),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 1.57TB; nevents: 65.89M; release: 8_0_21; last modified: 2017-02-15 22:42:56"),
])

meta_dictionary["/DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DYJetsToLL_M-10to50_amcatnloFXFX_v2_ext1"),
  ("nof_db_events",         40381391),
  ("nof_db_files",          467),
  ("fsize_db",              960666755116),
  ("xsection",              18610.0),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 960.67GB; nevents: 40.38M; release: 8_0_21; last modified: 2017-01-16 23:18:36"),
])

meta_dictionary["/DY1JetsToLL_M-10to50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DY1JetsToLL_M-10to50"),
  ("nof_db_events",         39840774),
  ("nof_db_files",          526),
  ("fsize_db",              1132424364458),
  ("xsection",              835.3),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 1.13TB; nevents: 39.84M; release: 8_0_21; last modified: 2017-01-11 17:27:23"),
])

meta_dictionary["/DY2JetsToLL_M-10to50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DY2JetsToLL_M-10to50"),
  ("nof_db_events",         19442927),
  ("nof_db_files",          272),
  ("fsize_db",              575503768149),
  ("xsection",              443.1),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 575.50GB; nevents: 19.44M; release: 8_0_21; last modified: 2017-01-09 23:08:49"),
])

meta_dictionary["/DY3JetsToLL_M-10to50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DY3JetsToLL_M-10to50"),
  ("nof_db_events",         4964197),
  ("nof_db_files",          59),
  ("fsize_db",              158613271317),
  ("xsection",              108.69),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 158.61GB; nevents: 4.96M; release: 8_0_21; last modified: 2016-12-27 04:17:32"),
])

meta_dictionary["/DY4JetsToLL_M-10to50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DY4JetsToLL_M-10to50"),
  ("nof_db_events",         2087849),
  ("nof_db_files",          42),
  ("fsize_db",              74947256710),
  ("xsection",              41.99),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 74.95GB; nevents: 2.09M; release: 8_0_21; last modified: 2017-01-26 18:18:30"),
])

meta_dictionary["/DYJetsToLL_M-5to50_HT-70to100_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DYJetsToLL_M-5to50_HT-70to100"),
  ("nof_db_events",         10000704),
  ("nof_db_files",          121),
  ("fsize_db",              304225723751),
  ("xsection",              344.3),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 304.23GB; nevents: 10.00M; release: 8_0_21; last modified: 2017-02-16 11:50:28"),
])

meta_dictionary["/DYJetsToLL_M-5to50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DYJetsToLL_M-5to50_HT-100to200"),
  ("nof_db_events",         1008250),
  ("nof_db_files",          13),
  ("fsize_db",              32697052450),
  ("xsection",              256.7),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 32.70GB; nevents: 1.01M; release: 8_0_21; last modified: 2017-01-02 23:34:31"),
])

meta_dictionary["/DYJetsToLL_M-5to50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DYJetsToLL_M-5to50_HT-100to200_ext1"),
  ("nof_db_events",         8583596),
  ("nof_db_files",          91),
  ("fsize_db",              281203884837),
  ("xsection",              256.7),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 281.20GB; nevents: 8.58M; release: 8_0_21; last modified: 2016-12-06 11:32:44"),
])

meta_dictionary["/DYJetsToLL_M-5to50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DYJetsToLL_M-5to50_HT-200to400"),
  ("nof_db_events",         1045127),
  ("nof_db_files",          53),
  ("fsize_db",              39379233484),
  ("xsection",              43.32),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 39.38GB; nevents: 1.05M; release: 8_0_21; last modified: 2017-01-09 22:32:41"),
])

meta_dictionary["/DYJetsToLL_M-5to50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DYJetsToLL_M-5to50_HT-200to400_ext1"),
  ("nof_db_events",         2077880),
  ("nof_db_files",          25),
  ("fsize_db",              78297685327),
  ("xsection",              43.32),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 78.30GB; nevents: 2.08M; release: 8_0_21; last modified: 2016-12-09 09:11:50"),
])

meta_dictionary["/DYJetsToLL_M-5to50_HT-400to600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DYJetsToLL_M-5to50_HT-400to600"),
  ("nof_db_events",         1016799),
  ("nof_db_files",          19),
  ("fsize_db",              44433574635),
  ("xsection",              4.15),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 44.43GB; nevents: 1.02M; release: 8_0_21; last modified: 2017-01-06 15:36:20"),
])

meta_dictionary["/DYJetsToLL_M-5to50_HT-400to600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DYJetsToLL_M-5to50_HT-400to600_ext1"),
  ("nof_db_events",         2071405),
  ("nof_db_files",          35),
  ("fsize_db",              90957542216),
  ("xsection",              4.15),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 90.96GB; nevents: 2.07M; release: 8_0_21; last modified: 2016-12-09 15:01:22"),
])

meta_dictionary["/DYJetsToLL_M-5to50_HT-600toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DYJetsToLL_M-5to50_HT-600toInf"),
  ("nof_db_events",         1021077),
  ("nof_db_files",          18),
  ("fsize_db",              50164124141),
  ("xsection",              1.266),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 50.16GB; nevents: 1.02M; release: 8_0_21; last modified: 2016-12-27 02:07:35"),
])

meta_dictionary["/DYJetsToLL_M-5to50_HT-600toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DYJetsToLL_M-5to50_HT-600toInf_ext1"),
  ("nof_db_events",         2006318),
  ("nof_db_files",          48),
  ("fsize_db",              98870323062),
  ("xsection",              1.266),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 98.87GB; nevents: 2.01M; release: 8_0_21; last modified: 2017-01-04 21:05:59"),
])

meta_dictionary["/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v2/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DYJetsToLL_M-50_ext1"),
  ("nof_db_events",         49144274),
  ("nof_db_files",          477),
  ("fsize_db",              1464680608482),
  ("xsection",              5765.4),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 1.46TB; nevents: 49.14M; release: 8_0_21; last modified: 2016-12-25 02:36:25"),
])

meta_dictionary["/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext2-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DYJetsToLL_M-50_ext2"),
  ("nof_db_events",         96658943),
  ("nof_db_files",          837),
  ("fsize_db",              2884497559928),
  ("xsection",              5765.4),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 2.88TB; nevents: 96.66M; release: 8_0_21; last modified: 2017-02-09 12:19:56"),
])

meta_dictionary["/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext2-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DYJetsToLL_M-50_amcatnloFXFX"),
  ("nof_db_events",         122055388),
  ("nof_db_files",          1451),
  ("fsize_db",              3609631059789),
  ("xsection",              5765.4),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 3.61TB; nevents: 122.06M; release: 8_0_21; last modified: 2017-02-16 16:36:08"),
])

meta_dictionary["/DY1JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DY1JetsToLL_M-50"),
  ("nof_db_events",         62627174),
  ("nof_db_files",          986),
  ("fsize_db",              1976077585765),
  ("xsection",              878.0),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 1.98TB; nevents: 62.63M; release: 8_0_21; last modified: 2017-01-05 09:57:18"),
])

meta_dictionary["/DY2JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DY2JetsToLL_M-50"),
  ("nof_db_events",         19970551),
  ("nof_db_files",          291),
  ("fsize_db",              678862189624),
  ("xsection",              307.0),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 678.86GB; nevents: 19.97M; release: 8_0_21; last modified: 2016-12-12 21:41:21"),
])

meta_dictionary["/DY3JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DY3JetsToLL_M-50"),
  ("nof_db_events",         5856110),
  ("nof_db_files",          133),
  ("fsize_db",              214250973292),
  ("xsection",              112.0),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 214.25GB; nevents: 5.86M; release: 8_0_21; last modified: 2017-01-04 08:36:36"),
])

meta_dictionary["/DY4JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DY4JetsToLL_M-50"),
  ("nof_db_events",         4197868),
  ("nof_db_files",          59),
  ("fsize_db",              170191766959),
  ("xsection",              44.2),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 170.19GB; nevents: 4.20M; release: 8_0_21; last modified: 2016-12-24 09:03:05"),
])

meta_dictionary["/DYJetsToLL_M-50_HT-70to100_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DYJetsToLL_M50_HT70to100"),
  ("nof_db_events",         9616188),
  ("nof_db_files",          112),
  ("fsize_db",              327219620062),
  ("xsection",              212.49),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 327.22GB; nevents: 9.62M; release: 8_0_21; last modified: 2016-12-28 09:45:00"),
])

meta_dictionary["/DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DYJetsToLL_M50_HT100to200"),
  ("nof_db_events",         2751187),
  ("nof_db_files",          39),
  ("fsize_db",              99055433690),
  ("xsection",              173.988),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 99.06GB; nevents: 2.75M; release: 8_0_21; last modified: 2017-01-02 23:59:04"),
])

meta_dictionary["/DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DYJetsToLL_M50_HT100to200_ext1"),
  ("nof_db_events",         7856020),
  ("nof_db_files",          135),
  ("fsize_db",              285713618902),
  ("xsection",              173.988),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 285.71GB; nevents: 7.86M; release: 8_0_21; last modified: 2017-01-05 09:34:38"),
])

meta_dictionary["/DYJetsToLL_M-50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DYJetsToLL_M50_HT200to400"),
  ("nof_db_events",         962195),
  ("nof_db_files",          40),
  ("fsize_db",              39591734120),
  ("xsection",              53.2656),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 39.59GB; nevents: 962.20k; release: 8_0_21; last modified: 2017-01-06 06:44:06"),
])

meta_dictionary["/DYJetsToLL_M-50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DYJetsToLL_M50_HT200to400_ext1"),
  ("nof_db_events",         8691536),
  ("nof_db_files",          130),
  ("fsize_db",              356304624396),
  ("xsection",              53.2656),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 356.30GB; nevents: 8.69M; release: 8_0_21; last modified: 2017-01-05 09:42:43"),
])

meta_dictionary["/DYJetsToLL_M-50_HT-400to600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DYJetsToLL_M50_HT400to600"),
  ("nof_db_events",         1070454),
  ("nof_db_files",          20),
  ("fsize_db",              50365115465),
  ("xsection",              7.58268),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 50.37GB; nevents: 1.07M; release: 8_0_21; last modified: 2017-01-03 10:51:55"),
])

meta_dictionary["/DYJetsToLL_M-50_HT-400to600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DYJetsToLL_M50_HT400to600_ext1"),
  ("nof_db_events",         8938322),
  ("nof_db_files",          165),
  ("fsize_db",              423173194004),
  ("xsection",              7.58268),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 423.17GB; nevents: 8.94M; release: 8_0_21; last modified: 2016-12-18 01:51:39"),
])

meta_dictionary["/DYJetsToLL_M-50_HT-600to800_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v2/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DYJetsToLL_M50_HT600to800"),
  ("nof_db_events",         8292957),
  ("nof_db_files",          351),
  ("fsize_db",              425360036396),
  ("xsection",              1.88244),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 425.36GB; nevents: 8.29M; release: 8_0_21; last modified: 2016-12-12 18:11:09"),
])

meta_dictionary["/DYJetsToLL_M-50_HT-800to1200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DYJetsToLL_M50_HT800to1200"),
  ("nof_db_events",         2668730),
  ("nof_db_files",          82),
  ("fsize_db",              143044004453),
  ("xsection",              0.872856),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 143.04GB; nevents: 2.67M; release: 8_0_21; last modified: 2016-12-15 03:17:19"),
])

meta_dictionary["/DYJetsToLL_M-50_HT-1200to2500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DYJetsToLL_M50_HT1200to2500"),
  ("nof_db_events",         596079),
  ("nof_db_files",          33),
  ("fsize_db",              34344518074),
  ("xsection",              0.2079),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 34.34GB; nevents: 596.08k; release: 8_0_21; last modified: 2016-12-11 00:39:51"),
])

meta_dictionary["/DYJetsToLL_M-50_HT-2500toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "DYJetsToLL_M50_HT2500toInf"),
  ("nof_db_events",         399492),
  ("nof_db_files",          17),
  ("fsize_db",              24697200292),
  ("xsection",              0.0037649),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 24.70GB; nevents: 399.49k; release: 8_0_21; last modified: 2016-12-14 08:11:22"),
])

meta_dictionary["/WJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "WJetsToLNu"),
  ("nof_db_events",         24120319),
  ("nof_db_files",          300),
  ("fsize_db",              656083366927),
  ("xsection",              61526.7),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 656.08GB; nevents: 24.12M; release: 8_0_21; last modified: 2016-12-13 05:25:49"),
])

meta_dictionary["/WJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext2-v2/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "WJetsToLNu_ext2"),
  ("nof_db_events",         235575850),
  ("nof_db_files",          2672),
  ("fsize_db",              6396591256086),
  ("xsection",              61526.7),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 6.40TB; nevents: 235.58M; release: 8_0_21; last modified: 2017-06-16 13:52:22"),
])

meta_dictionary["/WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "WJetsToLNu_madgraphMLM"),
  ("nof_db_events",         29705748),
  ("nof_db_files",          422),
  ("fsize_db",              812117052261),
  ("xsection",              61526.7),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 812.12GB; nevents: 29.71M; release: 8_0_21; last modified: 2016-12-11 20:21:23"),
])

meta_dictionary["/WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext2-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "WJetsToLNu_madgraphMLM_ext2"),
  ("nof_db_events",         57026058),
  ("nof_db_files",          638),
  ("fsize_db",              1565743727277),
  ("xsection",              61526.7),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 1.57TB; nevents: 57.03M; release: 8_0_21; last modified: 2017-01-11 07:53:46"),
])

meta_dictionary["/W1JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "W1JetsToLNu"),
  ("nof_db_events",         45367044),
  ("nof_db_files",          651),
  ("fsize_db",              1297946863384),
  ("xsection",              9503.91),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 1.30TB; nevents: 45.37M; release: 8_0_21; last modified: 2017-01-06 06:51:52"),
])

meta_dictionary["/W2JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "W2JetsToLNu"),
  ("nof_db_events",         29878415),
  ("nof_db_files",          596),
  ("fsize_db",              922124426257),
  ("xsection",              3258.45),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 922.12GB; nevents: 29.88M; release: 8_0_21; last modified: 2016-12-29 00:43:01"),
])

meta_dictionary["/W2JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "W2JetsToLNu_ext1"),
  ("nof_db_events",         30319351),
  ("nof_db_files",          430),
  ("fsize_db",              926996721477),
  ("xsection",              3258.45),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 927.00GB; nevents: 30.32M; release: 8_0_21; last modified: 2017-01-16 14:37:58"),
])

meta_dictionary["/W3JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "W3JetsToLNu"),
  ("nof_db_events",         19798117),
  ("nof_db_files",          331),
  ("fsize_db",              654899381207),
  ("xsection",              1162.28),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 654.90GB; nevents: 19.80M; release: 8_0_21; last modified: 2016-12-14 08:08:19"),
])

meta_dictionary["/W3JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "W3JetsToLNu_ext1"),
  ("nof_db_events",         39269431),
  ("nof_db_files",          553),
  ("fsize_db",              1298235804794),
  ("xsection",              1162.28),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 1.30TB; nevents: 39.27M; release: 8_0_21; last modified: 2017-01-17 03:32:42"),
])

meta_dictionary["/W4JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "W4JetsToLNu"),
  ("nof_db_events",         9170576),
  ("nof_db_files",          197),
  ("fsize_db",              343116116192),
  ("xsection",              634.61),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 343.12GB; nevents: 9.17M; release: 8_0_21; last modified: 2016-12-24 00:01:37"),
])

meta_dictionary["/W4JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "W4JetsToLNu_ext1"),
  ("nof_db_events",         2073275),
  ("nof_db_files",          23),
  ("fsize_db",              77900051602),
  ("xsection",              634.61),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 77.90GB; nevents: 2.07M; release: 8_0_21; last modified: 2017-01-07 21:38:31"),
])

meta_dictionary["/W4JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext2-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "W4JetsToLNu_ext2"),
  ("nof_db_events",         18751462),
  ("nof_db_files",          343),
  ("fsize_db",              701969438528),
  ("xsection",              634.61),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 701.97GB; nevents: 18.75M; release: 8_0_21; last modified: 2017-01-02 11:12:47"),
])

meta_dictionary["/WJetsToLNu_HT-70To100_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "WJetsToLNu_HT70To100"),
  ("nof_db_events",         10094300),
  ("nof_db_files",          207),
  ("fsize_db",              313384971344),
  ("xsection",              1656.3),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 313.38GB; nevents: 10.09M; release: 8_0_21; last modified: 2017-01-03 11:08:04"),
])

meta_dictionary["/WJetsToLNu_HT-100To200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "WJetsToLNu_HT100To200"),
  ("nof_db_events",         10235198),
  ("nof_db_files",          134),
  ("fsize_db",              339100477514),
  ("xsection",              1647.7),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 339.10GB; nevents: 10.24M; release: 8_0_21; last modified: 2017-01-08 23:06:13"),
])

meta_dictionary["/WJetsToLNu_HT-100To200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "WJetsToLNu_HT100To200_ext1"),
  ("nof_db_events",         29503700),
  ("nof_db_files",          302),
  ("fsize_db",              978141035508),
  ("xsection",              1647.7),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 978.14GB; nevents: 29.50M; release: 8_0_21; last modified: 2017-01-05 09:48:29"),
])

meta_dictionary["/WJetsToLNu_HT-100To200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext2-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "WJetsToLNu_HT100To200_ext2"),
  ("nof_db_events",         39617787),
  ("nof_db_files",          525),
  ("fsize_db",              1316608905354),
  ("xsection",              1647.7),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 1.32TB; nevents: 39.62M; release: 8_0_21; last modified: 2017-01-09 11:52:15"),
])

meta_dictionary["/WJetsToLNu_HT-200To400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "WJetsToLNu_HT200To400"),
  ("nof_db_events",         4950373),
  ("nof_db_files",          89),
  ("fsize_db",              188736454964),
  ("xsection",              440.82),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 188.74GB; nevents: 4.95M; release: 8_0_21; last modified: 2017-01-10 08:21:54"),
])

meta_dictionary["/WJetsToLNu_HT-200To400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "WJetsToLNu_HT200To400_ext1"),
  ("nof_db_events",         14815928),
  ("nof_db_files",          186),
  ("fsize_db",              565495250325),
  ("xsection",              440.82),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 565.50GB; nevents: 14.82M; release: 8_0_21; last modified: 2016-12-15 15:21:50"),
])

meta_dictionary["/WJetsToLNu_HT-200To400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext2-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "WJetsToLNu_HT200To400_ext2"),
  ("nof_db_events",         19914590),
  ("nof_db_files",          351),
  ("fsize_db",              751932488500),
  ("xsection",              440.82),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 751.93GB; nevents: 19.91M; release: 8_0_21; last modified: 2017-01-01 01:13:54"),
])

meta_dictionary["/WJetsToLNu_HT-400To600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "WJetsToLNu_HT400To600"),
  ("nof_db_events",         1963464),
  ("nof_db_files",          28),
  ("fsize_db",              85815607832),
  ("xsection",              59.74),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 85.82GB; nevents: 1.96M; release: 8_0_21; last modified: 2016-11-30 07:49:40"),
])

meta_dictionary["/WJetsToLNu_HT-400To600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "WJetsToLNu_HT400To600_ext1"),
  ("nof_db_events",         5796237),
  ("nof_db_files",          79),
  ("fsize_db",              251334202611),
  ("xsection",              59.74),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 251.33GB; nevents: 5.80M; release: 8_0_21; last modified: 2016-12-11 01:12:02"),
])

meta_dictionary["/WJetsToLNu_HT-600To800_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "WJetsToLNu_HT600To800"),
  ("nof_db_events",         3779141),
  ("nof_db_files",          49),
  ("fsize_db",              177568766315),
  ("xsection",              14.78),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 177.57GB; nevents: 3.78M; release: 8_0_21; last modified: 2016-12-20 08:57:35"),
])

meta_dictionary["/WJetsToLNu_HT-600To800_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "WJetsToLNu_HT600To800_ext1"),
  ("nof_db_events",         14908339),
  ("nof_db_files",          193),
  ("fsize_db",              700877788125),
  ("xsection",              14.78),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 700.88GB; nevents: 14.91M; release: 8_0_21; last modified: 2016-12-12 21:37:30"),
])

meta_dictionary["/WJetsToLNu_HT-800To1200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "WJetsToLNu_HT800To1200"),
  ("nof_db_events",         1544513),
  ("nof_db_files",          28),
  ("fsize_db",              76665083613),
  ("xsection",              6.729),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 76.67GB; nevents: 1.54M; release: 8_0_21; last modified: 2017-01-12 14:06:04"),
])

meta_dictionary["/WJetsToLNu_HT-800To1200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "WJetsToLNu_HT800To1200_ext1"),
  ("nof_db_events",         6200954),
  ("nof_db_files",          115),
  ("fsize_db",              308439745729),
  ("xsection",              6.729),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 308.44GB; nevents: 6.20M; release: 8_0_21; last modified: 2016-12-11 14:06:39"),
])

meta_dictionary["/WJetsToLNu_HT-1200To2500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "WJetsToLNu_HT1200To2500"),
  ("nof_db_events",         244532),
  ("nof_db_files",          7),
  ("fsize_db",              13084880820),
  ("xsection",              1.627),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 13.08GB; nevents: 244.53k; release: 8_0_21; last modified: 2016-12-05 23:44:03"),
])

meta_dictionary["/WJetsToLNu_HT-1200To2500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "WJetsToLNu_HT1200To2500_ext1"),
  ("nof_db_events",         6627909),
  ("nof_db_files",          116),
  ("fsize_db",              356350841731),
  ("xsection",              1.627),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 356.35GB; nevents: 6.63M; release: 8_0_21; last modified: 2017-01-08 11:25:02"),
])

meta_dictionary["/WJetsToLNu_HT-2500ToInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "WJetsToLNu_HT2500ToInf"),
  ("nof_db_events",         253561),
  ("nof_db_files",          7),
  ("fsize_db",              14857461452),
  ("xsection",              0.03928),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 14.86GB; nevents: 253.56k; release: 8_0_21; last modified: 2016-12-18 11:17:08"),
])

meta_dictionary["/WJetsToLNu_HT-2500ToInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "WJetsToLNu_HT2500ToInf_ext1"),
  ("nof_db_events",         2384260),
  ("nof_db_files",          46),
  ("fsize_db",              139067831894),
  ("xsection",              0.03928),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 139.07GB; nevents: 2.38M; release: 8_0_21; last modified: 2016-12-09 14:59:42"),
])

meta_dictionary["/WWTo2L2Nu_13TeV-powheg/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "WWTo2L2Nu"),
  ("nof_db_events",         1999000),
  ("nof_db_files",          24),
  ("fsize_db",              64631538418),
  ("xsection",              12.178),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 64.63GB; nevents: 2.00M; release: 8_0_21; last modified: 2016-12-04 03:04:29"),
])

meta_dictionary["/WZTo3LNu_TuneCUETP8M1_13TeV-powheg-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "WZTo3LNu"),
  ("nof_db_events",         1993200),
  ("nof_db_files",          39),
  ("fsize_db",              63802464673),
  ("xsection",              4.42965),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 63.80GB; nevents: 1.99M; release: 8_0_21; last modified: 2016-12-17 12:27:24"),
])

meta_dictionary["/WZTo3LNu_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "WZTo3LNu_amcatnloFXFX"),
  ("nof_db_events",         11887464),
  ("nof_db_files",          183),
  ("fsize_db",              378287333460),
  ("xsection",              4.42965),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 378.29GB; nevents: 11.89M; release: 8_0_21; last modified: 2016-12-09 15:07:19"),
])

meta_dictionary["/ZZTo4L_13TeV_powheg_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "ZZTo4L"),
  ("nof_db_events",         6669988),
  ("nof_db_files",          96),
  ("fsize_db",              210136229489),
  ("xsection",              1.256),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 210.14GB; nevents: 6.67M; release: 8_0_21; last modified: 2016-12-31 14:22:09"),
])

meta_dictionary["/ZZTo4L_13TeV-amcatnloFXFX-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "EWK"),
  ("process_name_specific", "ZZTo4L_amcatnloFXFX"),
  ("nof_db_events",         10709784),
  ("nof_db_files",          161),
  ("fsize_db",              333693832316),
  ("xsection",              1.256),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 333.69GB; nevents: 10.71M; release: 8_0_21; last modified: 2017-01-16 14:41:03"),
])

meta_dictionary["/QCD_Pt_15to20_bcToE_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "QCD"),
  ("process_name_specific", "QCD_Pt15to20_bcToE"),
  ("nof_db_events",         2685602),
  ("nof_db_files",          50),
  ("fsize_db",              74351225060),
  ("xsection",              187000.0),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 74.35GB; nevents: 2.69M; release: 8_0_21; last modified: 2017-02-01 01:56:08"),
])

meta_dictionary["/QCD_Pt_20to30_bcToE_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "QCD"),
  ("process_name_specific", "QCD_Pt20to30_bcToE"),
  ("nof_db_events",         10987947),
  ("nof_db_files",          163),
  ("fsize_db",              311325565099),
  ("xsection",              313500.0),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 311.33GB; nevents: 10.99M; release: 8_0_21; last modified: 2017-01-11 22:38:34"),
])

meta_dictionary["/QCD_Pt_30to80_bcToE_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "QCD"),
  ("process_name_specific", "QCD_Pt30to80_bcToE"),
  ("nof_db_events",         15328096),
  ("nof_db_files",          157),
  ("fsize_db",              466695066116),
  ("xsection",              361500.0),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 466.70GB; nevents: 15.33M; release: 8_0_21; last modified: 2017-01-04 08:27:43"),
])

meta_dictionary["/QCD_Pt_80to170_bcToE_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv2-PUMoriond17_backup_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "QCD"),
  ("process_name_specific", "QCD_Pt80to170_bcToE"),
  ("nof_db_events",         14976689),
  ("nof_db_files",          322),
  ("fsize_db",              531878500985),
  ("xsection",              33770.0),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 531.88GB; nevents: 14.98M; release: 8_0_21; last modified: 2016-12-15 03:32:28"),
])

meta_dictionary["/QCD_Pt_170to250_bcToE_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "QCD"),
  ("process_name_specific", "QCD_Pt170to250_bcToE"),
  ("nof_db_events",         9720760),
  ("nof_db_files",          134),
  ("fsize_db",              391866598074),
  ("xsection",              2126.0),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 391.87GB; nevents: 9.72M; release: 8_0_21; last modified: 2017-01-09 10:51:30"),
])

meta_dictionary["/QCD_Pt_250toInf_bcToE_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "QCD"),
  ("process_name_specific", "QCD_Pt250toInf_bcToE"),
  ("nof_db_events",         9773617),
  ("nof_db_files",          156),
  ("fsize_db",              428844795222),
  ("xsection",              563.1),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 428.84GB; nevents: 9.77M; release: 8_0_21; last modified: 2017-01-04 21:05:00"),
])

meta_dictionary["/QCD_Pt-20to30_EMEnriched_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "QCD"),
  ("process_name_specific", "QCD_Pt20to30_EMEnriched"),
  ("nof_db_events",         9218954),
  ("nof_db_files",          223),
  ("fsize_db",              253381689559),
  ("xsection",              4928000.0),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 253.38GB; nevents: 9.22M; release: 8_0_21; last modified: 2016-12-09 09:32:21"),
])

meta_dictionary["/QCD_Pt-30to50_EMEnriched_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "QCD"),
  ("process_name_specific", "QCD_Pt30to50_EMEnriched"),
  ("nof_db_events",         4730195),
  ("nof_db_files",          68),
  ("fsize_db",              134997775548),
  ("xsection",              6410000.0),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 135.00GB; nevents: 4.73M; release: 8_0_21; last modified: 2016-12-08 20:24:26"),
])

meta_dictionary["/QCD_Pt-30to50_EMEnriched_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "QCD"),
  ("process_name_specific", "QCD_Pt30to50_EMEnriched_ext1"),
  ("nof_db_events",         6768384),
  ("nof_db_files",          116),
  ("fsize_db",              193132431939),
  ("xsection",              6410000.0),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 193.13GB; nevents: 6.77M; release: 8_0_21; last modified: 2016-12-05 22:54:53"),
])

meta_dictionary["/QCD_Pt-50to80_EMEnriched_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "QCD"),
  ("process_name_specific", "QCD_Pt50to80_EMEnriched"),
  ("nof_db_events",         22337070),
  ("nof_db_files",          372),
  ("fsize_db",              680585721368),
  ("xsection",              1986000.0),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 680.59GB; nevents: 22.34M; release: 8_0_21; last modified: 2017-02-01 17:27:12"),
])

meta_dictionary["/QCD_Pt-50to80_EMEnriched_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "QCD"),
  ("process_name_specific", "QCD_Pt50to80_EMEnriched_ext1"),
  ("nof_db_events",         23474171),
  ("nof_db_files",          295),
  ("fsize_db",              714075893422),
  ("xsection",              1986000.0),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 714.08GB; nevents: 23.47M; release: 8_0_21; last modified: 2017-01-06 15:37:32"),
])

meta_dictionary["/QCD_Pt-80to120_EMEnriched_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "QCD"),
  ("process_name_specific", "QCD_Pt80to120_EMEnriched"),
  ("nof_db_events",         35841783),
  ("nof_db_files",          542),
  ("fsize_db",              1176700255925),
  ("xsection",              370900.0),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 1.18TB; nevents: 35.84M; release: 8_0_21; last modified: 2017-01-11 22:36:31"),
])

meta_dictionary["/QCD_Pt-80to120_EMEnriched_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "QCD"),
  ("process_name_specific", "QCD_Pt80to120_EMEnriched_ext1"),
  ("nof_db_events",         41853504),
  ("nof_db_files",          557),
  ("fsize_db",              1372324318634),
  ("xsection",              370900.0),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 1.37TB; nevents: 41.85M; release: 8_0_21; last modified: 2017-01-09 23:02:04"),
])

meta_dictionary["/QCD_Pt-120to170_EMEnriched_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "QCD"),
  ("process_name_specific", "QCD_Pt120to170_EMEnriched"),
  ("nof_db_events",         35817281),
  ("nof_db_files",          632),
  ("fsize_db",              1270682061291),
  ("xsection",              66760.0),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 1.27TB; nevents: 35.82M; release: 8_0_21; last modified: 2017-01-28 19:51:59"),
])

meta_dictionary["/QCD_Pt-120to170_EMEnriched_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "QCD"),
  ("process_name_specific", "QCD_Pt120to170_EMEnriched_ext1"),
  ("nof_db_events",         41954035),
  ("nof_db_files",          611),
  ("fsize_db",              1485357770084),
  ("xsection",              66760.0),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 1.49TB; nevents: 41.95M; release: 8_0_21; last modified: 2017-01-29 17:43:56"),
])

meta_dictionary["/QCD_Pt-170to300_EMEnriched_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "QCD"),
  ("process_name_specific", "QCD_Pt170to300_EMEnriched"),
  ("nof_db_events",         11540163),
  ("nof_db_files",          232),
  ("fsize_db",              445459835546),
  ("xsection",              16430.0),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 445.46GB; nevents: 11.54M; release: 8_0_21; last modified: 2016-12-08 11:53:32"),
])

meta_dictionary["/QCD_Pt-300toInf_EMEnriched_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "QCD"),
  ("process_name_specific", "QCD_Pt300toInf_EMEnriched"),
  ("nof_db_events",         7373633),
  ("nof_db_files",          186),
  ("fsize_db",              317392483405),
  ("xsection",              1101.0),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 317.39GB; nevents: 7.37M; release: 8_0_21; last modified: 2016-12-09 01:58:37"),
])

meta_dictionary["/QCD_Pt-20toInf_MuEnrichedPt15_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "QCD"),
  ("process_name_specific", "QCD_Mu15"),
  ("nof_db_events",         22094081),
  ("nof_db_files",          201),
  ("fsize_db",              692603013839),
  ("xsection",              237800.0),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 692.60GB; nevents: 22.09M; release: 8_0_21; last modified: 2016-11-29 11:52:19"),
])

meta_dictionary["/QCD_Pt-15to20_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "QCD"),
  ("process_name_specific", "QCD_Pt15to20_Mu5"),
  ("nof_db_events",         4141251),
  ("nof_db_files",          44),
  ("fsize_db",              114798652074),
  ("xsection",              2785000.0),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 114.80GB; nevents: 4.14M; release: 8_0_21; last modified: 2016-12-08 13:23:56"),
])

meta_dictionary["/QCD_Pt-20to30_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "QCD"),
  ("process_name_specific", "QCD_Pt20to30_Mu5"),
  ("nof_db_events",         31475157),
  ("nof_db_files",          303),
  ("fsize_db",              896514544269),
  ("xsection",              2490000.0),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 896.51GB; nevents: 31.48M; release: 8_0_21; last modified: 2016-11-30 07:50:37"),
])

meta_dictionary["/QCD_Pt-30to50_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "QCD"),
  ("process_name_specific", "QCD_Pt30to50_Mu5"),
  ("nof_db_events",         29954815),
  ("nof_db_files",          302),
  ("fsize_db",              901959914983),
  ("xsection",              1364000.0),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 901.96GB; nevents: 29.95M; release: 8_0_21; last modified: 2016-12-07 20:08:06"),
])

meta_dictionary["/QCD_Pt-50to80_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "QCD"),
  ("process_name_specific", "QCD_Pt50to80_Mu5"),
  ("nof_db_events",         19806915),
  ("nof_db_files",          192),
  ("fsize_db",              646502244303),
  ("xsection",              377400.0),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 646.50GB; nevents: 19.81M; release: 8_0_21; last modified: 2016-11-27 00:23:39"),
])

meta_dictionary["/QCD_Pt-80to120_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "QCD"),
  ("process_name_specific", "QCD_Pt80to120_Mu5"),
  ("nof_db_events",         13786971),
  ("nof_db_files",          146),
  ("fsize_db",              492478276477),
  ("xsection",              88350.0),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 492.48GB; nevents: 13.79M; release: 8_0_21; last modified: 2016-11-27 02:17:39"),
])

meta_dictionary["/QCD_Pt-80to120_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v3/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "QCD"),
  ("process_name_specific", "QCD_Pt80to120_Mu5_ext1"),
  ("nof_db_events",         9797244),
  ("nof_db_files",          226),
  ("fsize_db",              350535214552),
  ("xsection",              88350.0),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 350.54GB; nevents: 9.80M; release: 8_0_21; last modified: 2016-12-11 14:07:44"),
])

meta_dictionary["/QCD_Pt-120to170_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "QCD"),
  ("process_name_specific", "QCD_Pt120to170_Mu5"),
  ("nof_db_events",         8042721),
  ("nof_db_files",          89),
  ("fsize_db",              313222341348),
  ("xsection",              21250.0),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 313.22GB; nevents: 8.04M; release: 8_0_21; last modified: 2016-11-27 00:56:30"),
])

meta_dictionary["/QCD_Pt-120to170_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv2-PUMoriond17_backup_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "QCD"),
  ("process_name_specific", "QCD_Pt120to170_Mu5_backup"),
  ("nof_db_events",         11938140),
  ("nof_db_files",          273),
  ("fsize_db",              465038799594),
  ("xsection",              21250.0),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 465.04GB; nevents: 11.94M; release: 8_0_21; last modified: 2016-12-01 14:32:35"),
])

meta_dictionary["/QCD_Pt-170to300_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "QCD"),
  ("process_name_specific", "QCD_Pt170to300_Mu5"),
  ("nof_db_events",         7947159),
  ("nof_db_files",          106),
  ("fsize_db",              339781972733),
  ("xsection",              6969.0),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 339.78GB; nevents: 7.95M; release: 8_0_21; last modified: 2016-11-21 18:31:39"),
])

meta_dictionary["/QCD_Pt-170to300_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "QCD"),
  ("process_name_specific", "QCD_Pt170to300_Mu5_ext1"),
  ("nof_db_events",         9403072),
  ("nof_db_files",          116),
  ("fsize_db",              401692718678),
  ("xsection",              6969.0),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 401.69GB; nevents: 9.40M; release: 8_0_21; last modified: 2016-11-27 01:07:07"),
])

meta_dictionary["/QCD_Pt-170to300_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv2-PUMoriond17_backup_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "QCD"),
  ("process_name_specific", "QCD_Pt170to300_Mu5_backup"),
  ("nof_db_events",         19607777),
  ("nof_db_files",          383),
  ("fsize_db",              836784769945),
  ("xsection",              6969.0),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 836.78GB; nevents: 19.61M; release: 8_0_21; last modified: 2016-12-01 14:34:16"),
])

meta_dictionary["/QCD_Pt-300to470_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "QCD"),
  ("process_name_specific", "QCD_Pt300to470_Mu5"),
  ("nof_db_events",         7937590),
  ("nof_db_files",          133),
  ("fsize_db",              376294747731),
  ("xsection",              619.5),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 376.29GB; nevents: 7.94M; release: 8_0_21; last modified: 2016-12-07 20:37:50"),
])

meta_dictionary["/QCD_Pt-300to470_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "QCD"),
  ("process_name_specific", "QCD_Pt300to470_Mu5_ext1"),
  ("nof_db_events",         16452588),
  ("nof_db_files",          256),
  ("fsize_db",              779118198739),
  ("xsection",              619.5),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 779.12GB; nevents: 16.45M; release: 8_0_21; last modified: 2016-12-02 07:55:16"),
])

meta_dictionary["/QCD_Pt-300to470_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext2-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "QCD"),
  ("process_name_specific", "QCD_Pt300to470_Mu5_ext2"),
  ("nof_db_events",         24605508),
  ("nof_db_files",          337),
  ("fsize_db",              1167038684478),
  ("xsection",              619.5),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 1.17TB; nevents: 24.61M; release: 8_0_21; last modified: 2016-11-27 01:23:49"),
])

meta_dictionary["/QCD_Pt-470to600_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "QCD"),
  ("process_name_specific", "QCD_Pt470to600_Mu5"),
  ("nof_db_events",         3851524),
  ("nof_db_files",          64),
  ("fsize_db",              194707159282),
  ("xsection",              58.9),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 194.71GB; nevents: 3.85M; release: 8_0_21; last modified: 2016-11-30 07:58:57"),
])

meta_dictionary["/QCD_Pt-470to600_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "QCD"),
  ("process_name_specific", "QCD_Pt470to600_Mu5_ext1"),
  ("nof_db_events",         5663755),
  ("nof_db_files",          89),
  ("fsize_db",              286563933683),
  ("xsection",              58.9),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 286.56GB; nevents: 5.66M; release: 8_0_21; last modified: 2016-11-14 13:14:30"),
])

meta_dictionary["/QCD_Pt-470to600_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext2-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "QCD"),
  ("process_name_specific", "QCD_Pt470to600_Mu5_ext2"),
  ("nof_db_events",         9847664),
  ("nof_db_files",          151),
  ("fsize_db",              498289319134),
  ("xsection",              58.9),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 498.29GB; nevents: 9.85M; release: 8_0_21; last modified: 2016-12-06 21:47:18"),
])

meta_dictionary["/QCD_Pt-600to800_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "QCD"),
  ("process_name_specific", "QCD_Pt600to800_Mu5"),
  ("nof_db_events",         4010136),
  ("nof_db_files",          63),
  ("fsize_db",              210356845888),
  ("xsection",              18.36),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 210.36GB; nevents: 4.01M; release: 8_0_21; last modified: 2016-11-25 00:07:16"),
])

meta_dictionary["/QCD_Pt-600to800_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "QCD"),
  ("process_name_specific", "QCD_Pt600to800_Mu5_ext1"),
  ("nof_db_events",         5971175),
  ("nof_db_files",          99),
  ("fsize_db",              313098594514),
  ("xsection",              18.36),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 313.10GB; nevents: 5.97M; release: 8_0_21; last modified: 2016-11-30 07:46:27"),
])

meta_dictionary["/QCD_Pt-600to800_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv2-PUMoriond17_backup_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "QCD"),
  ("process_name_specific", "QCD_Pt600to800_Mu5_backup"),
  ("nof_db_events",         9756853),
  ("nof_db_files",          378),
  ("fsize_db",              512978605422),
  ("xsection",              18.36),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 512.98GB; nevents: 9.76M; release: 8_0_21; last modified: 2016-12-01 14:35:20"),
])

meta_dictionary["/QCD_Pt-800to1000_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "QCD"),
  ("process_name_specific", "QCD_Pt800to1000_Mu5"),
  ("nof_db_events",         3962749),
  ("nof_db_files",          70),
  ("fsize_db",              215365278478),
  ("xsection",              3.253),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 215.37GB; nevents: 3.96M; release: 8_0_21; last modified: 2016-11-25 00:16:07"),
])

meta_dictionary["/QCD_Pt-800to1000_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "QCD"),
  ("process_name_specific", "QCD_Pt800to1000_Mu5_ext1"),
  ("nof_db_events",         5838541),
  ("nof_db_files",          99),
  ("fsize_db",              316787561597),
  ("xsection",              3.253),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 316.79GB; nevents: 5.84M; release: 8_0_21; last modified: 2016-11-30 07:35:48"),
])

meta_dictionary["/QCD_Pt-800to1000_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext2-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "QCD"),
  ("process_name_specific", "QCD_Pt800to1000_Mu5_ext2"),
  ("nof_db_events",         9966149),
  ("nof_db_files",          151),
  ("fsize_db",              542172220887),
  ("xsection",              3.253),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 542.17GB; nevents: 9.97M; release: 8_0_21; last modified: 2016-11-26 01:26:58"),
])

meta_dictionary["/QCD_Pt-1000toInf_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "QCD"),
  ("process_name_specific", "QCD_Pt1000toInf_Mu5"),
  ("nof_db_events",         3990117),
  ("nof_db_files",          67),
  ("fsize_db",              224105142415),
  ("xsection",              1.075),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 224.11GB; nevents: 3.99M; release: 8_0_21; last modified: 2016-11-27 00:26:19"),
])

meta_dictionary["/QCD_Pt-1000toInf_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v3/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "QCD"),
  ("process_name_specific", "QCD_Pt1000toInf_Mu5_ext1"),
  ("nof_db_events",         9609821),
  ("nof_db_files",          331),
  ("fsize_db",              540966670881),
  ("xsection",              1.075),
  ("use_it",                False),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 540.97GB; nevents: 9.61M; release: 8_0_21; last modified: 2016-12-08 11:48:48"),
])

meta_dictionary["/WWW_4F_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "Rares"),
  ("process_name_specific", "WWW_4F"),
  ("nof_db_events",         240000),
  ("nof_db_files",          4),
  ("fsize_db",              9412480242),
  ("xsection",              0.2086),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 9.41GB; nevents: 240.00k; release: 8_0_21; last modified: 2016-12-12 21:41:47"),
])

meta_dictionary["/WWZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "Rares"),
  ("process_name_specific", "WWZ_4F"),
  ("nof_db_events",         250000),
  ("nof_db_files",          4),
  ("fsize_db",              10172600107),
  ("xsection",              0.1651),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 10.17GB; nevents: 250.00k; release: 8_0_21; last modified: 2016-12-02 07:47:54"),
])

meta_dictionary["/WZZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "Rares"),
  ("process_name_specific", "WZZ"),
  ("nof_db_events",         246800),
  ("nof_db_files",          5),
  ("fsize_db",              10090863809),
  ("xsection",              0.05565),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 10.09GB; nevents: 246.80k; release: 8_0_21; last modified: 2016-12-10 14:51:37"),
])

meta_dictionary["/ZZZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "Rares"),
  ("process_name_specific", "ZZZ"),
  ("nof_db_events",         249237),
  ("nof_db_files",          4),
  ("fsize_db",              9630643168),
  ("xsection",              0.01398),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 9.63GB; nevents: 249.24k; release: 8_0_21; last modified: 2016-12-12 18:13:11"),
])

meta_dictionary["/WZG_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "Rares"),
  ("process_name_specific", "WZG"),
  ("nof_db_events",         998200),
  ("nof_db_files",          18),
  ("fsize_db",              39750384681),
  ("xsection",              0.04123),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 39.75GB; nevents: 998.20k; release: 8_0_21; last modified: 2017-01-04 08:46:42"),
])

meta_dictionary["/WGToLNuG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "Rares"),
  ("process_name_specific", "WGToLNuG_ext1"),
  ("nof_db_events",         5048470),
  ("nof_db_files",          145),
  ("fsize_db",              151327578433),
  ("xsection",              405.271),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 151.33GB; nevents: 5.05M; release: 8_0_21; last modified: 2016-12-08 13:29:06"),
])

meta_dictionary["/WGToLNuG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext2-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "Rares"),
  ("process_name_specific", "WGToLNuG_ext2"),
  ("nof_db_events",         10231994),
  ("nof_db_files",          124),
  ("fsize_db",              305397640166),
  ("xsection",              405.271),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 305.40GB; nevents: 10.23M; release: 8_0_21; last modified: 2017-01-26 11:43:01"),
])

meta_dictionary["/WGToLNuG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext3-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "Rares"),
  ("process_name_specific", "WGToLNuG_ext3"),
  ("nof_db_events",         12146754),
  ("nof_db_files",          185),
  ("fsize_db",              362875791564),
  ("xsection",              405.271),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 362.88GB; nevents: 12.15M; release: 8_0_21; last modified: 2017-04-22 06:22:41"),
])

meta_dictionary["/ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "Rares"),
  ("process_name_specific", "ZGTo2LG"),
  ("nof_db_events",         2307158),
  ("nof_db_files",          37),
  ("fsize_db",              75836236087),
  ("xsection",              117.864),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 75.84GB; nevents: 2.31M; release: 8_0_21; last modified: 2017-07-06 06:01:06"),
])

meta_dictionary["/ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "Rares"),
  ("process_name_specific", "ZGTo2LG_ext1"),
  ("nof_db_events",         14372682),
  ("nof_db_files",          210),
  ("fsize_db",              472846799759),
  ("xsection",              117.864),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 472.85GB; nevents: 14.37M; release: 8_0_21; last modified: 2017-01-08 22:40:59"),
])

meta_dictionary["/TGJets_TuneCUETP8M1_13TeV_amcatnlo_madspin_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "Rares"),
  ("process_name_specific", "TGJets"),
  ("nof_db_events",         292508),
  ("nof_db_files",          19),
  ("fsize_db",              11570306685),
  ("xsection",              2.967),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 11.57GB; nevents: 292.51k; release: 8_0_21; last modified: 2016-12-19 00:44:01"),
])

meta_dictionary["/TGJets_TuneCUETP8M1_13TeV_amcatnlo_madspin_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "Rares"),
  ("process_name_specific", "TGJets_ext1"),
  ("nof_db_events",         1556996),
  ("nof_db_files",          37),
  ("fsize_db",              61150465610),
  ("xsection",              2.967),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 61.15GB; nevents: 1.56M; release: 8_0_21; last modified: 2016-12-25 12:19:47"),
])

meta_dictionary["/TTGJets_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "Rares"),
  ("process_name_specific", "TTGJets"),
  ("nof_db_events",         4870911),
  ("nof_db_files",          80),
  ("fsize_db",              237119297466),
  ("xsection",              3.697),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 237.12GB; nevents: 4.87M; release: 8_0_21; last modified: 2016-12-11 20:18:13"),
])

meta_dictionary["/TTGJets_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "Rares"),
  ("process_name_specific", "TTGJets_ext1"),
  ("nof_db_events",         9885348),
  ("nof_db_files",          239),
  ("fsize_db",              482404560252),
  ("xsection",              3.697),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 482.40GB; nevents: 9.89M; release: 8_0_21; last modified: 2017-01-05 19:48:06"),
])

meta_dictionary["/TTTT_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "Rares"),
  ("process_name_specific", "TTTT"),
  ("nof_db_events",         250000),
  ("nof_db_files",          18),
  ("fsize_db",              16809583948),
  ("xsection",              0.008213),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 16.81GB; nevents: 250.00k; release: 8_0_21; last modified: 2017-01-06 15:40:11"),
])

meta_dictionary["/TTWH_TuneCUETP8M2T4_13TeV-madgraph-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v3/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "Rares"),
  ("process_name_specific", "TTWH"),
  ("nof_db_events",         100000),
  ("nof_db_files",          16),
  ("fsize_db",              6326872783),
  ("xsection",              0.00114),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 6.33GB; nevents: 100.00k; release: 8_0_21; last modified: 2017-07-07 05:48:17"),
])

meta_dictionary["/TTTW_TuneCUETP8M2T4_13TeV-madgraph-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v2/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "Rares"),
  ("process_name_specific", "TTTW"),
  ("nof_db_events",         97232),
  ("nof_db_files",          21),
  ("fsize_db",              7048906300),
  ("xsection",              0.0007273),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 7.05GB; nevents: 97.23k; release: 8_0_21; last modified: 2017-06-14 20:54:08"),
])

meta_dictionary["/VHToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "VH"),
  ("process_name_specific", "VHToNonbb_M125"),
  ("nof_db_events",         1007898),
  ("nof_db_files",          29),
  ("fsize_db",              36367011319),
  ("xsection",              0.9425),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 36.37GB; nevents: 1.01M; release: 8_0_21; last modified: 2017-01-05 09:17:24"),
])

meta_dictionary["/tZq_ll_4f_13TeV-amcatnlo-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "Rares"),
  ("process_name_specific", "tZq_ll_4f"),
  ("nof_db_events",         14509520),
  ("nof_db_files",          303),
  ("fsize_db",              646779357138),
  ("xsection",              0.0758),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 646.78GB; nevents: 14.51M; release: 8_0_21; last modified: 2016-12-15 03:10:37"),
])

meta_dictionary["/WpWpJJ_EWK-QCD_TuneCUETP8M1_13TeV-madgraph-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "Rares"),
  ("process_name_specific", "WpWpJJ_EWK_QCD_v14-v1"),
  ("nof_db_events",         149681),
  ("nof_db_files",          4),
  ("fsize_db",              6389586443),
  ("xsection",              0.03711),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 6.39GB; nevents: 149.68k; release: 8_0_21; last modified: 2016-12-29 18:29:34"),
])

meta_dictionary["/WWTo2L2Nu_DoubleScattering_13TeV-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"] =  OD([
  ("crab_string",           ""),
  ("sample_category",       "Rares"),
  ("process_name_specific", "WWTo2L2Nu_DoubleScattering"),
  ("nof_db_events",         999367),
  ("nof_db_files",          13),
  ("fsize_db",              29281784971),
  ("xsection",              0.1743),
  ("use_it",                True),
  ("genWeight",             True),
  ("comment",               "status: VALID; size: 29.28GB; nevents: 999.37k; release: 8_0_21; last modified: 2016-12-30 15:42:40"),
])


# event statistics by sample category:
# signal:                    23.82M
# tHq:                       3.50M
# tHW:                       1.50M
# additional_signal_overlap: 999.80k
# TTZ:                       24.03M
# TTW:                       12.25M
# TTWW:                      98.69k
# TT:                        506.30M
# EWK:                       1.43G
# QCD:                       613.84M
# Rares:                     78.80M
# VH:                        1.01M

