import os, collections

"""Python configuration file containing necessary information about each sample.
   Needed by: RunCuts.py, FormatResults.py, Diff.py
"""

PREFIX = "/hdfs/cms/store/user/kaehatah"
RESULTS_DIR = "results"
LUMI = 10000

Samples = collections.OrderedDict()

Samples["ttH"] = {
    "path" : os.path.join(PREFIX,
                          "TTbarH_M-125_13TeV_amcatnlo-pythia8-tauola",
                          "VHBB_HEPPY_V11_TTbarH_M-125_13TeV_amcatnlo-pythia8-tauola__Phys14DR-PU40bx25_PHYS14_25_V1-v1",
                          "151007_183021",
                          "0000"),
    "token" : "TTbarH_M-125_13TeV_amcatnlo-pythia8-tauola",
    "subtoken" : "PU40bx25_PHYS14_25_V1-v1",
    "isMC" : True,
    "nof_events" : 199500,
    "x_section" : 0.5085,
    "nof_files" : 7,
  }
Samples["ttH_Htt"] = {
    "path" : os.path.join(PREFIX,
                          "TTbarH_HToTauTau_M-125_13TeV_amcatnlo-pythia8-tauola",
                          "VHBB_HEPPY_V11_TTbarH_HToTauTau_M-125_13TeV_amcatnlo-pythia8-tauola__Phys14DR-AVE30BX50_tsg_PHYS14_ST_V1-v1",
                          "160204_130912",
                          "0000"),
    "token" : "TTbarH_HToTauTau_M-125_13TeV_amcatnlo-pythia8-tauola",
    "subtoken" : "PU40bx25_PHYS14_25_V1-v1",
    "isMC" : True,
    "nof_events" : 187400,
    "x_section" : 0.5085, # ?
    "nof_files" : 5,
  }
Samples["tt_j"] = {
    "path" : os.path.join(PREFIX,
                          "TTJets_MSDecaysCKM_central_Tune4C_13TeV-madgraph-tauola",
                          "VHBB_HEPPY_V11_TTJets_MSDecaysCKM_central_Tune4C_13TeV-madgraph-tauola__Phys14DR-PU20bx25_PHYS14_25_V1-v1",
                          "151016_143340",
                          "0000"),
    "token" : "TTJets_MSDecaysCKM_central_Tune4C_13TeV-madgraph-tauola",
    "subtoken" : "PU20bx25_PHYS14_25_V1-v1",
    "isMC" : True,
    "nof_events" : 25446993, # 116 missing
    "x_section" : 831.76,
    "nof_files" : 552,
  }
Samples["Z_j"] = {
    "path" : os.path.join(PREFIX,
                          "DYJetsToLL_M-50_13TeV-madgraph-pythia8",
                          "VHBB_HEPPY_V11_DYJetsToLL_M-50_13TeV-madgraph-pythia8__Phys14DR-PU20bx25_PHYS14_25_V1-v1",
                          "151012_182949",
                          "0000"),
    "token" : "DYJetsToLL_M-50_13TeV-madgraph-pythia8",
    "subtoken" : "PU20bx25_PHYS14_25_V1-v1",
    "isMC" : True,
    "nof_events" : 2829164, # 8 missing
    "x_section" : 6025.2,
    "nof_files" : 59,
  }
Samples["W_j"] = {
    "path" : os.path.join(PREFIX,
                          "WJetsToLNu_13TeV-madgraph-pythia8-tauola",
                          "VHBB_HEPPY_V11_WJetsToLNu_13TeV-madgraph-pythia8-tauola__Phys14DR-PU20bx25_PHYS14_25_V1-v1",
                          "151016_143511",
                          "0000"),
    "token" : "WJetsToLNu_13TeV-madgraph-pythia8-tauola",
    "subtoken" : "PU20bx25_PHYS14_25_V1-v1",
    "isMC" : True,
    "nof_events" : 10017462, # 31 missing
    "x_section" : 61526.7,
    "nof_files" : 222,
  }
Samples["tt_W"] = {
    "path" : os.path.join(PREFIX,
                          "TTWJets_Tune4C_13TeV-madgraph-tauola",
                          "VHBB_HEPPY_V11_TTWJets_Tune4C_13TeV-madgraph-tauola__Phys14DR-PU20bx25_PHYS14_25_V1-v1",
                          "151013_121036",
                          "0000"),
    "token" : "TTWJets_Tune4C_13TeV-madgraph-tauola",
    "subtoken" : "PU20bx25_PHYS14_25_V1-v1",
    "isMC" : True,
    "nof_events" : 246521,
    "x_section" : 0.665,
    "nof_files" : 9,
  }
Samples["tt_Z"] = {
    "path" : os.path.join(PREFIX,
                          "TTZJets_Tune4C_13TeV-madgraph-tauola",
                          "VHBB_HEPPY_V11_TTZJets_Tune4C_13TeV-madgraph-tauola__Phys14DR-PU20bx25_PHYS14_25_V1-v1",
                          "151016_143600",
                          "0000"),
    "token" : "TTZJets_Tune4C_13TeV-madgraph-tauola",
    "subtoken" : "PU20bx25_PHYS14_25_V1-v1",
    "isMC" : True,
    "nof_events" : 249275,
    "x_section" : 0.857,
    "nof_files" : 11,
  }
Samples["WZ"] = {
    "path" : os.path.join(PREFIX,
                          "WZJetsTo3LNu_Tune4C_13TeV-madgraph-tauola",
                          "VHBB_HEPPY_V11_WZJetsTo3LNu_Tune4C_13TeV-madgraph-tauola__Phys14DR-PU20bx25_PHYS14_25_V1-v1",
                          "151012_183257",
                          "0000"),
    "token" : "WZJetsTo3LNu_Tune4C_13TeV-madgraph-tauola",
    "subtoken" : "PU20bx25_PHYS14_25_V1-v1",
    "isMC" : True,
    "nof_events" : 237484, # 3 missing
    "x_section" : 2.1132,
    "nof_files" : 7,
  }
Samples["ZZ"] = {
    "path" : os.path.join(PREFIX,
                          "ZZTo4L_Tune4C_13TeV-powheg-pythia8",
                          "VHBB_HEPPY_V11_ZZTo4L_Tune4C_13TeV-powheg-pythia8__Phys14DR-PU20bx25_PHYS14_25_V1-v1",
                          "151012_183342",
                          "0000"),
    "token" : "ZZTo4L_Tune4C_13TeV-powheg-pythia8",
    "subtoken" : "PU20bx25_PHYS14_25_V1-v1",
    "isMC" : True,
    "nof_events" : 1958600, # 6 missing
    "x_section" : 0.08415,
    "nof_files" : 41,
  }
