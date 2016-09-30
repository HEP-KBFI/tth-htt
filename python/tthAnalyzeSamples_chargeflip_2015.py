from collections import OrderedDict as OD

from tthAnalyzeSamples_2015 import samples_2015

samples_2015["/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"]["use_it"] = False
samples_2015["/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12_ext1-v1/MINIAODSIM"] = OD([
  ("type", "mc"),
  ("sample_category", "DY"),
  ("process_name_specific", "DYJetsToLL_M-50_ext1"),
  ("nof_files", 5875),
  ("nof_events", 247512446),
  ("use_it", True),
  ("xsection", 6025.2),
  ("triggers", [ "1e", "2e" ]),
  ("local_paths",
    [
      OD([
        ("path", "/hdfs/cms/store/user/kaehatah/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/VHBB_HEPPY_V12_DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-Py8__fall15MAv2-pu25ns15v1_76r2as_v12_ext1-v1/160721_154639"),
        ("selection", "*"),
        ("blacklist", [355,437,438,561,648,788,821,834,870,1147,1186,1302,1461,1515,1574,1598,1635,1802,1809,1954,1961,1979,2008,2033,2105,\
                      2108,2137,2236,2259,2260,2275,2311,2358,2386,2395,2409,2412,2431,2461,2504,2525,2567,2608,2629,2672,2712,2752,2758,2764,\
                      2980,3186,3471,3504,3735,3756,3919,5288,5471,5538,5775])
      ])
    ]
  )
])

samples_2015["/ST_t-channel_4f_leptonDecays_13TeV-amcatnlo-pythia8_TuneCUETP8M1/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"]["sample_category"] = \
  "background_data_estimate"
samples_2015["/ST_t-channel_4f_leptonDecays_13TeV-amcatnlo-pythia8_TuneCUETP8M1/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12_ext1-v1/MINIAODSIM"]["sample_category"] = \
  "background_data_estimate"

for sample_name, sample_info in samples_2015.items():
  if sample_info["type"] == "mc":
    sample_info["triggers"] = [ "1e", "2e" ]
  if sample_name in [
      "/DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM",
      "/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12_ext1-v1/MINIAODSIM" ]:
    sample_info["sample_category"] = "DY"
  if sample_name in [
      "/TTJets_SingleLeptFromTbar_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v2/MINIAODSIM",
      "/TTJets_SingleLeptFromT_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM",
      "/TTJets_DiLept_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM" ]:
    sample_info["sample_category"] = "TTbar"
  if sample_name in [
      "/WJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM" ]:
    sample_info["sample_category"] = "WJets"
  if sample_name in [
      "/ST_tW_top_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM",
      "/ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM",
      "/ST_s-channel_4f_leptonDecays_13TeV-amcatnlo-pythia8_TuneCUETP8M1/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v2/MINIAODSIM",
      "/ST_t-channel_4f_leptonDecays_13TeV-amcatnlo-pythia8_TuneCUETP8M1/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM",
      "/ST_t-channel_4f_leptonDecays_13TeV-amcatnlo-pythia8_TuneCUETP8M1/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12_ext1-v1/MINIAODSIM" ]:
    sample_info["sample_category"] = "Singletop"
  if sample_name in [
      "/WZTo3LNu_TuneCUETP8M1_13TeV-powheg-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM",
      "/WWTo2L2Nu_13TeV-powheg/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM",
      "/ZZTo4L_13TeV_powheg_pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"]:
    sample_info["sample_category"] = "Diboson"
  if sample_name in [
      "/DoubleMuon/Run2015C_25ns-16Dec2015-v1/MINIAOD",
      "/DoubleMuon/Run2015D-16Dec2015-v1/MINIAOD",
      "/DoubleEG/Run2015C_25ns-16Dec2015-v1/MINIAOD",
      "/DoubleEG/Run2015D-16Dec2015-v2/MINIAOD",
      "/MuonEG/Run2015C_25ns-16Dec2015-v1/MINIAOD", 
      "/MuonEG/Run2015D-16Dec2015-v1/MINIAOD" ]:
    sample_info["use_it"] = False

