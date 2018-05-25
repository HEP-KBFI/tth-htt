from collections import OrderedDict as OD

# file generated at 2018-05-24 15:06:18 with the following command:
# create_dictionary.py -v -m python/samples/metaDict_2017.py -p python/samples/sampleLocations_2017.txt -Z zeroes.txt -z zombies.txt -N samples_2017 -E 2017 -o python/samples -g tthAnalyzeSamples_2017_nanoAOD.py -M

samples_2017 = OD()
samples_2017["/SingleElectron/Run2017B-17Nov2017-v1/MINIAOD"] = OD([
  ("type",                            "data"),
  ("sample_category",                 "data_obs"),
  ("process_name_specific",           "SingleElectron_Run2017B_17Nov2017_v1"),
  ("nof_files",                       1150),
  ("nof_db_files",                    634),
  ("nof_events",                      56501676),
  ("nof_tree_events",                 56501676),
  ("nof_db_events",                   60537490),
  ("fsize_local",                     36421699370), # 36.42GB, avg file size 31.67MB
  ("fsize_db",                        1839129571740), # 1.84TB, avg file size 2.90GB
  ("use_it",                          True),
  ("triggers",                        ['1e']),
  ("has_LHE",                         False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/kaehatah/NanoProduction_v2_2018Apr26/SingleElectron/NanoProduction_v2_2018Apr26_SingleElectron__Run2017B-17Nov2017-v1/180425_232221"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
  ("missing_from_superset",           [
    "HLT_HcalIsolatedbunch",
    "HLT_L1FatEvents",
  ]),
  ("missing_hlt_paths",               [
    "HLT_Ele17_CaloIdM_TrackIdM_PFJet30",
    "HLT_Ele23_CaloIdM_TrackIdM_PFJet30",
    "HLT_Ele32_WPTight_Gsf",
    "HLT_Ele8_CaloIdM_TrackIdM_PFJet30",
  ]),
])

samples_2017["/SingleElectron/Run2017C-17Nov2017-v1/MINIAOD"] = OD([
  ("type",                            "data"),
  ("sample_category",                 "data_obs"),
  ("process_name_specific",           "SingleElectron_Run2017C_17Nov2017_v1"),
  ("nof_files",                       2586),
  ("nof_db_files",                    1705),
  ("nof_events",                      127361546),
  ("nof_tree_events",                 127361546),
  ("nof_db_events",                   136637888),
  ("fsize_local",                     92652744376), # 92.65GB, avg file size 35.83MB
  ("fsize_db",                        4293152220674), # 4.29TB, avg file size 2.52GB
  ("use_it",                          True),
  ("triggers",                        ['1e']),
  ("has_LHE",                         False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/kaehatah/NanoProduction_v2_2018Apr26/SingleElectron/NanoProduction_v2_2018Apr26_SingleElectron__Run2017C-17Nov2017-v1/180425_232459"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
  ("missing_from_superset",           [
    "HLT_DiPFJetAve100_HFJEC",
    "HLT_DiPFJetAve140",
    "HLT_DiPFJetAve160_HFJEC",
    "HLT_DiPFJetAve200",
    "HLT_DiPFJetAve220_HFJEC",
    "HLT_DiPFJetAve260",
    "HLT_DiPFJetAve300_HFJEC",
    "HLT_DiPFJetAve320",
    "HLT_DiPFJetAve40",
    "HLT_DiPFJetAve400",
    "HLT_DiPFJetAve500",
    "HLT_DiPFJetAve60",
    "HLT_DiPFJetAve60_HFJEC",
    "HLT_DiPFJetAve80",
    "HLT_DiPFJetAve80_HFJEC",
    "HLT_Dimuon18_PsiPrime_noCorrL1",
    "HLT_Dimuon24_Phi_noCorrL1",
    "HLT_Dimuon24_Upsilon_noCorrL1",
    "HLT_Dimuon25_Jpsi_noCorrL1",
    "HLT_DoubleEle25_CaloIdL_MW",
    "HLT_DoubleEle27_CaloIdL_MW",
    "HLT_Ele27_Ele37_CaloIdL_MW",
    "HLT_Ele32_WPTight_Gsf",
    "HLT_Ele35_WPTight_Gsf_L1EGMT",
    "HLT_IsoMu24_eta2p1_MediumChargedIsoPFTau40_Trk1_TightID_eta2p1_Reg_CrossL1",
    "HLT_IsoMu24_eta2p1_MediumChargedIsoPFTau40_Trk1_eta2p1_Reg_CrossL1",
    "HLT_IsoMu24_eta2p1_TightChargedIsoPFTau40_Trk1_TightID_eta2p1_Reg_CrossL1",
    "HLT_IsoMu24_eta2p1_TightChargedIsoPFTau40_Trk1_eta2p1_Reg_CrossL1",
    "HLT_IsoMu30",
    "HLT_L1_CDC_SingleMu_3_er1p2_TOP120_DPHI2p618_3p142",
    "HLT_MediumChargedIsoPFTau50_Trk30_eta2p1_1pr_MET110",
    "HLT_MediumChargedIsoPFTau50_Trk30_eta2p1_1pr_MET120",
    "HLT_MediumChargedIsoPFTau50_Trk30_eta2p1_1pr_MET130",
    "HLT_Mu12_DoublePhoton20",
    "HLT_Mu17_Photon30_IsoCaloId",
    "HLT_Mu19",
    "HLT_Mu19_TrkIsoVVL",
    "HLT_Mu19_TrkIsoVVL_Mu9_TrkIsoVVL",
    "HLT_Mu19_TrkIsoVVL_Mu9_TrkIsoVVL_DZ",
    "HLT_Mu19_TrkIsoVVL_Mu9_TrkIsoVVL_DZ_Mass3p8",
    "HLT_Mu19_TrkIsoVVL_Mu9_TrkIsoVVL_DZ_Mass8",
    "HLT_Mu27_Ele37_CaloIdL_MW",
    "HLT_Mu37_Ele27_CaloIdL_MW",
    "HLT_Mu37_TkMu27",
    "HLT_Mu55",
    "HLT_PFHT380_SixPFJet32_DoublePFBTagDeepCSV_2p2",
    "HLT_PFMET120_PFMHT120_IDTight_HFCleaned",
    "HLT_PFMET120_PFMHT120_IDTight_PFHT60_HFCleaned",
    "HLT_PFMETNoMu120_PFMHTNoMu120_IDTight_HFCleaned",
    "HLT_PFMETTypeOne120_PFMHT120_IDTight_HFCleaned",
    "HLT_Photon25",
    "HLT_Physics_part0",
    "HLT_Physics_part1",
    "HLT_Physics_part2",
    "HLT_Physics_part3",
    "HLT_Physics_part4",
    "HLT_Physics_part5",
    "HLT_Physics_part6",
    "HLT_Physics_part7",
    "HLT_Tau3Mu_Mu5_Mu1_TkMu1_IsoTau10",
    "HLT_Tau3Mu_Mu5_Mu1_TkMu1_IsoTau10_Charge1",
    "HLT_Tau3Mu_Mu5_Mu1_TkMu1_Tau10",
    "HLT_Tau3Mu_Mu5_Mu1_TkMu1_Tau10_Charge1",
    "HLT_Tau3Mu_Mu7_Mu1_TkMu1_IsoTau15",
    "HLT_Tau3Mu_Mu7_Mu1_TkMu1_IsoTau15_Charge1",
    "HLT_Tau3Mu_Mu7_Mu1_TkMu1_Tau15",
    "HLT_Tau3Mu_Mu7_Mu1_TkMu1_Tau15_Charge1",
    "HLT_TriplePhoton_20_20_20_CaloIdLV2",
    "HLT_TriplePhoton_20_20_20_CaloIdLV2_R9IdVL",
    "HLT_TriplePhoton_30_30_10_CaloIdLV2",
    "HLT_TriplePhoton_30_30_10_CaloIdLV2_R9IdVL",
    "HLT_TriplePhoton_35_35_5_CaloIdLV2_R9IdVL",
    "HLT_VBF_DoubleLooseChargedIsoPFTau20_Trk1_eta2p1_Reg",
    "HLT_VBF_DoubleMediumChargedIsoPFTau20_Trk1_eta2p1_Reg",
    "HLT_VBF_DoubleTightChargedIsoPFTau20_Trk1_eta2p1_Reg",
    "HLT_ZeroBias_part0",
    "HLT_ZeroBias_part1",
    "HLT_ZeroBias_part2",
    "HLT_ZeroBias_part3",
    "HLT_ZeroBias_part4",
    "HLT_ZeroBias_part5",
    "HLT_ZeroBias_part6",
    "HLT_ZeroBias_part7",
    "HLT_ZeroBias_part8",
    "HLT_ZeroBias_part9",
  ]),
  ("missing_hlt_paths",               [
    "HLT_Ele32_WPTight_Gsf",
  ]),
])

samples_2017["/SingleElectron/Run2017D-17Nov2017-v1/MINIAOD"] = OD([
  ("type",                            "data"),
  ("sample_category",                 "data_obs"),
  ("process_name_specific",           "SingleElectron_Run2017D_17Nov2017_v1"),
  ("nof_files",                       1021),
  ("nof_db_files",                    693),
  ("nof_events",                      50610320),
  ("nof_tree_events",                 50610320),
  ("nof_db_events",                   51526710),
  ("fsize_local",                     36259618542), # 36.26GB, avg file size 35.51MB
  ("fsize_db",                        1584079997402), # 1.58TB, avg file size 2.29GB
  ("use_it",                          True),
  ("triggers",                        ['1e']),
  ("has_LHE",                         False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/kaehatah/NanoProduction_v2_2018Apr26/SingleElectron/NanoProduction_v2_2018Apr26_SingleElectron__Run2017D-17Nov2017-v1/180425_232758"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
  ("missing_from_superset",           [
    "HLT_TripleMu_5_3_3_Mass3p8to60_DZ",
  ]),
  ("missing_hlt_paths",               [

  ]),
])

samples_2017["/SingleElectron/Run2017E-17Nov2017-v1/MINIAOD"] = OD([
  ("type",                            "data"),
  ("sample_category",                 "data_obs"),
  ("process_name_specific",           "SingleElectron_Run2017E_17Nov2017_v1"),
  ("nof_files",                       2026),
  ("nof_db_files",                    1280),
  ("nof_events",                      100205122),
  ("nof_tree_events",                 100205122),
  ("nof_db_events",                   102121689),
  ("fsize_local",                     76242887443), # 76.24GB, avg file size 37.63MB
  ("fsize_db",                        3608372444378), # 3.61TB, avg file size 2.82GB
  ("use_it",                          True),
  ("triggers",                        ['1e']),
  ("has_LHE",                         False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/kaehatah/NanoProduction_v2_2018Apr26/SingleElectron/NanoProduction_v2_2018Apr26_SingleElectron__Run2017E-17Nov2017-v1/180425_233027"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
  ("missing_from_superset",           [

  ]),
  ("missing_hlt_paths",               [

  ]),
])

samples_2017["/SingleElectron/Run2017F-17Nov2017-v1/MINIAOD"] = OD([
  ("type",                            "data"),
  ("sample_category",                 "data_obs"),
  ("process_name_specific",           "SingleElectron_Run2017F_17Nov2017_v1"),
  ("nof_files",                       2552),
  ("nof_db_files",                    1583),
  ("nof_events",                      126061224),
  ("nof_tree_events",                 126061224),
  ("nof_db_events",                   128467223),
  ("fsize_local",                     100317379754), # 100.32GB, avg file size 39.31MB
  ("fsize_db",                        4628019555901), # 4.63TB, avg file size 2.92GB
  ("use_it",                          True),
  ("triggers",                        ['1e']),
  ("has_LHE",                         False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/kaehatah/NanoProduction_v2_2018Apr26/SingleElectron/NanoProduction_v2_2018Apr26_SingleElectron__Run2017F-17Nov2017-v1/180425_233318"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
  ("missing_from_superset",           [
    "HLT_AK8PFJet330_PFAK8BTagCSV_p1",
    "HLT_AK8PFJet330_PFAK8BTagCSV_p17",
    "HLT_Diphoton30_18_PVrealAND_R9Id_AND_IsoCaloId_AND_HE_R9Id_NoPixelVeto_Mass55",
    "HLT_Diphoton30_18_PVrealAND_R9Id_AND_IsoCaloId_AND_HE_R9Id_PixelVeto_Mass55",
    "HLT_DoubleMu2_Jpsi_DoubleTkMu0_Phi",
    "HLT_DoubleMu2_Jpsi_DoubleTrk1_Phi",
    "HLT_DoubleMu3_DCA_PFMET50_PFMHT60",
    "HLT_DoubleMu3_DoubleEle7p5_CaloIdL_TrackIdL_Upsilon",
    "HLT_DoubleMu3_TkMu_DsTau3Mu",
    "HLT_DoubleMu5_Upsilon_DoubleEle3_CaloIdL_TrackIdL",
    "HLT_Ele15_CaloIdL_TrackIdL_IsoVL_PFJet30",
    "HLT_Ele15_Ele8_CaloIdL_TrackIdL_IsoVL",
    "HLT_Ele15_WPLoose_Gsf",
    "HLT_Ele17_WPLoose_Gsf",
    "HLT_IsoMu27_LooseChargedIsoPFTau20_SingleL1",
    "HLT_IsoMu27_MediumChargedIsoPFTau20_SingleL1",
    "HLT_IsoMu27_TightChargedIsoPFTau20_SingleL1",
    "HLT_L1_DoubleJet30_Mass_Min400_Mu10",
    "HLT_Mu12",
    "HLT_Mu15",
    "HLT_Mu18_Mu9",
    "HLT_Mu18_Mu9_DZ",
    "HLT_Mu18_Mu9_SameSign",
    "HLT_Mu18_Mu9_SameSign_DZ",
    "HLT_Mu20_Mu10",
    "HLT_Mu20_Mu10_DZ",
    "HLT_Mu20_Mu10_SameSign",
    "HLT_Mu20_Mu10_SameSign_DZ",
    "HLT_Mu23_Mu12",
    "HLT_Mu23_Mu12_DZ",
    "HLT_Mu23_Mu12_SameSign",
    "HLT_Mu23_Mu12_SameSign_DZ",
    "HLT_PFMET100_PFMHT100_IDTight_PFHT60",
    "HLT_PFMETNoMu100_PFMHTNoMu100_IDTight_PFHT60",
    "HLT_PFMETTypeOne100_PFMHT100_IDTight_PFHT60",
    "HLT_Photon20",
    "HLT_Photon50_R9Id90_HE10_IsoM_EBOnly_PFJetsMJJ300DEta3_PFMET50",
    "HLT_Photon75_R9Id90_HE10_IsoM_EBOnly_PFJetsMJJ300DEta3",
    "HLT_Photon75_R9Id90_HE10_IsoM_EBOnly_PFJetsMJJ600DEta3",
    "HLT_QuadPFJet103_88_75_15",
    "HLT_QuadPFJet103_88_75_15_BTagCSV_p013_VBF2",
    "HLT_QuadPFJet103_88_75_15_DoubleBTagCSV_p013_p08_VBF1",
    "HLT_QuadPFJet105_88_76_15",
    "HLT_QuadPFJet105_88_76_15_BTagCSV_p013_VBF2",
    "HLT_QuadPFJet105_90_76_15_DoubleBTagCSV_p013_p08_VBF1",
    "HLT_QuadPFJet111_90_80_15",
    "HLT_QuadPFJet111_90_80_15_BTagCSV_p013_VBF2",
    "HLT_QuadPFJet111_90_80_15_DoubleBTagCSV_p013_p08_VBF1",
    "HLT_QuadPFJet98_83_71_15",
    "HLT_QuadPFJet98_83_71_15_BTagCSV_p013_VBF2",
    "HLT_QuadPFJet98_83_71_15_DoubleBTagCSV_p013_p08_VBF1",
    "HLT_TrimuonOpen_5_3p5_2_Upsilon_Muon",
    "HLT_TripleMu_5_3_3_Mass3p8to60_DCA",
    "HLT_ZeroBias_Beamspot",
  ]),
  ("missing_hlt_paths",               [

  ]),
])

samples_2017["/SingleMuon/Run2017B-17Nov2017-v1/MINIAOD"] = OD([
  ("type",                            "data"),
  ("sample_category",                 "data_obs"),
  ("process_name_specific",           "SingleMuon_Run2017B_17Nov2017_v1"),
  ("nof_files",                       2679),
  ("nof_db_files",                    1146),
  ("nof_events",                      128496874),
  ("nof_tree_events",                 128496874),
  ("nof_db_events",                   136300266),
  ("fsize_local",                     75582613196), # 75.58GB, avg file size 28.21MB
  ("fsize_db",                        3681903942053), # 3.68TB, avg file size 3.21GB
  ("use_it",                          True),
  ("triggers",                        ['1mu']),
  ("has_LHE",                         False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/kaehatah/NanoProduction_v2_2018Apr26/SingleMuon/NanoProduction_v2_2018Apr26_SingleMuon__Run2017B-17Nov2017-v1/180425_233553"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
  ("missing_from_superset",           [
    "HLT_HcalIsolatedbunch",
    "HLT_L1FatEvents",
  ]),
  ("missing_hlt_paths",               [
    "HLT_Mu3_PFJet40",
  ]),
])

samples_2017["/SingleMuon/Run2017C-17Nov2017-v1/MINIAOD"] = OD([
  ("type",                            "data"),
  ("sample_category",                 "data_obs"),
  ("process_name_specific",           "SingleMuon_Run2017C_17Nov2017_v1"),
  ("nof_files",                       3125),
  ("nof_db_files",                    1511),
  ("nof_events",                      154633551),
  ("nof_tree_events",                 154633551),
  ("nof_db_events",                   165652756),
  ("fsize_local",                     97849742049), # 97.85GB, avg file size 31.31MB
  ("fsize_db",                        4719988428330), # 4.72TB, avg file size 3.12GB
  ("use_it",                          True),
  ("triggers",                        ['1mu']),
  ("has_LHE",                         False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/kaehatah/NanoProduction_v2_2018Apr26/SingleMuon/NanoProduction_v2_2018Apr26_SingleMuon__Run2017C-17Nov2017-v1/180425_233828"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
  ("missing_from_superset",           [
    "HLT_DiPFJetAve100_HFJEC",
    "HLT_DiPFJetAve140",
    "HLT_DiPFJetAve160_HFJEC",
    "HLT_DiPFJetAve200",
    "HLT_DiPFJetAve220_HFJEC",
    "HLT_DiPFJetAve260",
    "HLT_DiPFJetAve300_HFJEC",
    "HLT_DiPFJetAve320",
    "HLT_DiPFJetAve40",
    "HLT_DiPFJetAve400",
    "HLT_DiPFJetAve500",
    "HLT_DiPFJetAve60",
    "HLT_DiPFJetAve60_HFJEC",
    "HLT_DiPFJetAve80",
    "HLT_DiPFJetAve80_HFJEC",
    "HLT_Dimuon18_PsiPrime_noCorrL1",
    "HLT_Dimuon24_Phi_noCorrL1",
    "HLT_Dimuon24_Upsilon_noCorrL1",
    "HLT_Dimuon25_Jpsi_noCorrL1",
    "HLT_DoubleEle25_CaloIdL_MW",
    "HLT_DoubleEle27_CaloIdL_MW",
    "HLT_Ele27_Ele37_CaloIdL_MW",
    "HLT_Ele32_WPTight_Gsf",
    "HLT_Ele35_WPTight_Gsf_L1EGMT",
    "HLT_IsoMu24_eta2p1_MediumChargedIsoPFTau40_Trk1_TightID_eta2p1_Reg_CrossL1",
    "HLT_IsoMu24_eta2p1_MediumChargedIsoPFTau40_Trk1_eta2p1_Reg_CrossL1",
    "HLT_IsoMu24_eta2p1_TightChargedIsoPFTau40_Trk1_TightID_eta2p1_Reg_CrossL1",
    "HLT_IsoMu24_eta2p1_TightChargedIsoPFTau40_Trk1_eta2p1_Reg_CrossL1",
    "HLT_IsoMu30",
    "HLT_L1_CDC_SingleMu_3_er1p2_TOP120_DPHI2p618_3p142",
    "HLT_MediumChargedIsoPFTau50_Trk30_eta2p1_1pr_MET110",
    "HLT_MediumChargedIsoPFTau50_Trk30_eta2p1_1pr_MET120",
    "HLT_MediumChargedIsoPFTau50_Trk30_eta2p1_1pr_MET130",
    "HLT_Mu12_DoublePhoton20",
    "HLT_Mu17_Photon30_IsoCaloId",
    "HLT_Mu19",
    "HLT_Mu19_TrkIsoVVL",
    "HLT_Mu19_TrkIsoVVL_Mu9_TrkIsoVVL",
    "HLT_Mu19_TrkIsoVVL_Mu9_TrkIsoVVL_DZ",
    "HLT_Mu19_TrkIsoVVL_Mu9_TrkIsoVVL_DZ_Mass3p8",
    "HLT_Mu19_TrkIsoVVL_Mu9_TrkIsoVVL_DZ_Mass8",
    "HLT_Mu27_Ele37_CaloIdL_MW",
    "HLT_Mu37_Ele27_CaloIdL_MW",
    "HLT_Mu37_TkMu27",
    "HLT_Mu55",
    "HLT_PFHT380_SixPFJet32_DoublePFBTagDeepCSV_2p2",
    "HLT_PFMET120_PFMHT120_IDTight_HFCleaned",
    "HLT_PFMET120_PFMHT120_IDTight_PFHT60_HFCleaned",
    "HLT_PFMETNoMu120_PFMHTNoMu120_IDTight_HFCleaned",
    "HLT_PFMETTypeOne120_PFMHT120_IDTight_HFCleaned",
    "HLT_Photon25",
    "HLT_Physics_part0",
    "HLT_Physics_part1",
    "HLT_Physics_part2",
    "HLT_Physics_part3",
    "HLT_Physics_part4",
    "HLT_Physics_part5",
    "HLT_Physics_part6",
    "HLT_Physics_part7",
    "HLT_Tau3Mu_Mu5_Mu1_TkMu1_IsoTau10",
    "HLT_Tau3Mu_Mu5_Mu1_TkMu1_IsoTau10_Charge1",
    "HLT_Tau3Mu_Mu5_Mu1_TkMu1_Tau10",
    "HLT_Tau3Mu_Mu5_Mu1_TkMu1_Tau10_Charge1",
    "HLT_Tau3Mu_Mu7_Mu1_TkMu1_IsoTau15",
    "HLT_Tau3Mu_Mu7_Mu1_TkMu1_IsoTau15_Charge1",
    "HLT_Tau3Mu_Mu7_Mu1_TkMu1_Tau15",
    "HLT_Tau3Mu_Mu7_Mu1_TkMu1_Tau15_Charge1",
    "HLT_TriplePhoton_20_20_20_CaloIdLV2",
    "HLT_TriplePhoton_20_20_20_CaloIdLV2_R9IdVL",
    "HLT_TriplePhoton_30_30_10_CaloIdLV2",
    "HLT_TriplePhoton_30_30_10_CaloIdLV2_R9IdVL",
    "HLT_TriplePhoton_35_35_5_CaloIdLV2_R9IdVL",
    "HLT_VBF_DoubleLooseChargedIsoPFTau20_Trk1_eta2p1_Reg",
    "HLT_VBF_DoubleMediumChargedIsoPFTau20_Trk1_eta2p1_Reg",
    "HLT_VBF_DoubleTightChargedIsoPFTau20_Trk1_eta2p1_Reg",
    "HLT_ZeroBias_part0",
    "HLT_ZeroBias_part1",
    "HLT_ZeroBias_part2",
    "HLT_ZeroBias_part3",
    "HLT_ZeroBias_part4",
    "HLT_ZeroBias_part5",
    "HLT_ZeroBias_part6",
    "HLT_ZeroBias_part7",
    "HLT_ZeroBias_part8",
    "HLT_ZeroBias_part9",
  ]),
  ("missing_hlt_paths",               [

  ]),
])

samples_2017["/SingleMuon/Run2017D-17Nov2017-v1/MINIAOD"] = OD([
  ("type",                            "data"),
  ("sample_category",                 "data_obs"),
  ("process_name_specific",           "SingleMuon_Run2017D_17Nov2017_v1"),
  ("nof_files",                       1398),
  ("nof_db_files",                    823),
  ("nof_events",                      69031074),
  ("nof_tree_events",                 69031074),
  ("nof_db_events",                   70361660),
  ("fsize_local",                     43815901476), # 43.82GB, avg file size 31.34MB
  ("fsize_db",                        2004044655656), # 2.00TB, avg file size 2.44GB
  ("use_it",                          True),
  ("triggers",                        ['1mu']),
  ("has_LHE",                         False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/kaehatah/NanoProduction_v2_2018Apr26/SingleMuon/NanoProduction_v2_2018Apr26_SingleMuon__Run2017D-17Nov2017-v1/180425_234103"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
  ("missing_from_superset",           [
    "HLT_TripleMu_5_3_3_Mass3p8to60_DZ",
  ]),
  ("missing_hlt_paths",               [

  ]),
])

samples_2017["/SingleMuon/Run2017E-17Nov2017-v1/MINIAOD"] = OD([
  ("type",                            "data"),
  ("sample_category",                 "data_obs"),
  ("process_name_specific",           "SingleMuon_Run2017E_17Nov2017_v1"),
  ("nof_files",                       3100),
  ("nof_db_files",                    1669),
  ("nof_events",                      151713898),
  ("nof_tree_events",                 151713898),
  ("nof_db_events",                   154630534),
  ("fsize_local",                     103041240461), # 103.04GB, avg file size 33.24MB
  ("fsize_db",                        5063603395030), # 5.06TB, avg file size 3.03GB
  ("use_it",                          True),
  ("triggers",                        ['1mu']),
  ("has_LHE",                         False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/kaehatah/NanoProduction_v2_2018Apr26/SingleMuon/NanoProduction_v2_2018Apr26_SingleMuon__Run2017E-17Nov2017-v1/180425_234304"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
  ("missing_from_superset",           [

  ]),
  ("missing_hlt_paths",               [

  ]),
])

samples_2017["/SingleMuon/Run2017F-17Nov2017-v1/MINIAOD"] = OD([
  ("type",                            "data"),
  ("sample_category",                 "data_obs"),
  ("process_name_specific",           "SingleMuon_Run2017F_17Nov2017_v1"),
  ("nof_files",                       4913),
  ("nof_db_files",                    2737),
  ("nof_events",                      235945383),
  ("nof_tree_events",                 235945383),
  ("nof_db_events",                   242140980),
  ("fsize_local",                     167333079573), # 167.33GB, avg file size 34.06MB
  ("fsize_db",                        8025096282975), # 8.03TB, avg file size 2.93GB
  ("use_it",                          True),
  ("triggers",                        ['1mu']),
  ("has_LHE",                         False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/kaehatah/NanoProduction_v2_2018Apr26/SingleMuon/NanoProduction_v2_2018Apr26_SingleMuon__Run2017F-17Nov2017-v1/180425_234621"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
  ("missing_from_superset",           [
    "HLT_AK8PFJet330_PFAK8BTagCSV_p1",
    "HLT_AK8PFJet330_PFAK8BTagCSV_p17",
    "HLT_Diphoton30_18_PVrealAND_R9Id_AND_IsoCaloId_AND_HE_R9Id_NoPixelVeto_Mass55",
    "HLT_Diphoton30_18_PVrealAND_R9Id_AND_IsoCaloId_AND_HE_R9Id_PixelVeto_Mass55",
    "HLT_DoubleMu2_Jpsi_DoubleTkMu0_Phi",
    "HLT_DoubleMu2_Jpsi_DoubleTrk1_Phi",
    "HLT_DoubleMu3_DCA_PFMET50_PFMHT60",
    "HLT_DoubleMu3_DoubleEle7p5_CaloIdL_TrackIdL_Upsilon",
    "HLT_DoubleMu3_TkMu_DsTau3Mu",
    "HLT_DoubleMu5_Upsilon_DoubleEle3_CaloIdL_TrackIdL",
    "HLT_Ele15_CaloIdL_TrackIdL_IsoVL_PFJet30",
    "HLT_Ele15_Ele8_CaloIdL_TrackIdL_IsoVL",
    "HLT_Ele15_WPLoose_Gsf",
    "HLT_Ele17_WPLoose_Gsf",
    "HLT_IsoMu27_LooseChargedIsoPFTau20_SingleL1",
    "HLT_IsoMu27_MediumChargedIsoPFTau20_SingleL1",
    "HLT_IsoMu27_TightChargedIsoPFTau20_SingleL1",
    "HLT_L1_DoubleJet30_Mass_Min400_Mu10",
    "HLT_Mu12",
    "HLT_Mu15",
    "HLT_Mu18_Mu9",
    "HLT_Mu18_Mu9_DZ",
    "HLT_Mu18_Mu9_SameSign",
    "HLT_Mu18_Mu9_SameSign_DZ",
    "HLT_Mu20_Mu10",
    "HLT_Mu20_Mu10_DZ",
    "HLT_Mu20_Mu10_SameSign",
    "HLT_Mu20_Mu10_SameSign_DZ",
    "HLT_Mu23_Mu12",
    "HLT_Mu23_Mu12_DZ",
    "HLT_Mu23_Mu12_SameSign",
    "HLT_Mu23_Mu12_SameSign_DZ",
    "HLT_PFMET100_PFMHT100_IDTight_PFHT60",
    "HLT_PFMETNoMu100_PFMHTNoMu100_IDTight_PFHT60",
    "HLT_PFMETTypeOne100_PFMHT100_IDTight_PFHT60",
    "HLT_Photon20",
    "HLT_Photon50_R9Id90_HE10_IsoM_EBOnly_PFJetsMJJ300DEta3_PFMET50",
    "HLT_Photon75_R9Id90_HE10_IsoM_EBOnly_PFJetsMJJ300DEta3",
    "HLT_Photon75_R9Id90_HE10_IsoM_EBOnly_PFJetsMJJ600DEta3",
    "HLT_QuadPFJet103_88_75_15",
    "HLT_QuadPFJet103_88_75_15_BTagCSV_p013_VBF2",
    "HLT_QuadPFJet103_88_75_15_DoubleBTagCSV_p013_p08_VBF1",
    "HLT_QuadPFJet105_88_76_15",
    "HLT_QuadPFJet105_88_76_15_BTagCSV_p013_VBF2",
    "HLT_QuadPFJet105_90_76_15_DoubleBTagCSV_p013_p08_VBF1",
    "HLT_QuadPFJet111_90_80_15",
    "HLT_QuadPFJet111_90_80_15_BTagCSV_p013_VBF2",
    "HLT_QuadPFJet111_90_80_15_DoubleBTagCSV_p013_p08_VBF1",
    "HLT_QuadPFJet98_83_71_15",
    "HLT_QuadPFJet98_83_71_15_BTagCSV_p013_VBF2",
    "HLT_QuadPFJet98_83_71_15_DoubleBTagCSV_p013_p08_VBF1",
    "HLT_TrimuonOpen_5_3p5_2_Upsilon_Muon",
    "HLT_TripleMu_5_3_3_Mass3p8to60_DCA",
    "HLT_ZeroBias_Beamspot",
  ]),
  ("missing_hlt_paths",               [

  ]),
])

samples_2017["/DoubleEG/Run2017B-17Nov2017-v1/MINIAOD"] = OD([
  ("type",                            "data"),
  ("sample_category",                 "data_obs"),
  ("process_name_specific",           "DoubleEG_Run2017B_17Nov2017_v1"),
  ("nof_files",                       1098),
  ("nof_db_files",                    759),
  ("nof_events",                      54125900),
  ("nof_tree_events",                 54125900),
  ("nof_db_events",                   58088760),
  ("fsize_local",                     42263853306), # 42.26GB, avg file size 38.49MB
  ("fsize_db",                        2000582502159), # 2.00TB, avg file size 2.64GB
  ("use_it",                          True),
  ("triggers",                        ['2e', '3e']),
  ("has_LHE",                         False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/kaehatah/NanoProduction_v2_2018Apr26/DoubleEG/NanoProduction_v2_2018Apr26_DoubleEG__Run2017B-17Nov2017-v1/180425_235551"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
  ("missing_from_superset",           [
    "HLT_HcalIsolatedbunch",
    "HLT_L1FatEvents",
  ]),
  ("missing_hlt_paths",               [

  ]),
])

samples_2017["/DoubleEG/Run2017C-17Nov2017-v1/MINIAOD"] = OD([
  ("type",                            "data"),
  ("sample_category",                 "data_obs"),
  ("process_name_specific",           "DoubleEG_Run2017C_17Nov2017_v1"),
  ("nof_files",                       1201),
  ("nof_db_files",                    847),
  ("nof_events",                      60063430),
  ("nof_tree_events",                 60063430),
  ("nof_db_events",                   65181125),
  ("fsize_local",                     48601880964), # 48.60GB, avg file size 40.47MB
  ("fsize_db",                        2252815090346), # 2.25TB, avg file size 2.66GB
  ("use_it",                          True),
  ("triggers",                        ['2e', '3e']),
  ("has_LHE",                         False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/kaehatah/NanoProduction_v2_2018Apr26/DoubleEG/NanoProduction_v2_2018Apr26_DoubleEG__Run2017C-17Nov2017-v1/180425_235958"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
  ("missing_from_superset",           [
    "HLT_DiPFJetAve100_HFJEC",
    "HLT_DiPFJetAve140",
    "HLT_DiPFJetAve160_HFJEC",
    "HLT_DiPFJetAve200",
    "HLT_DiPFJetAve220_HFJEC",
    "HLT_DiPFJetAve260",
    "HLT_DiPFJetAve300_HFJEC",
    "HLT_DiPFJetAve320",
    "HLT_DiPFJetAve40",
    "HLT_DiPFJetAve400",
    "HLT_DiPFJetAve500",
    "HLT_DiPFJetAve60",
    "HLT_DiPFJetAve60_HFJEC",
    "HLT_DiPFJetAve80",
    "HLT_DiPFJetAve80_HFJEC",
    "HLT_Dimuon18_PsiPrime_noCorrL1",
    "HLT_Dimuon24_Phi_noCorrL1",
    "HLT_Dimuon24_Upsilon_noCorrL1",
    "HLT_Dimuon25_Jpsi_noCorrL1",
    "HLT_DoubleEle25_CaloIdL_MW",
    "HLT_DoubleEle27_CaloIdL_MW",
    "HLT_Ele27_Ele37_CaloIdL_MW",
    "HLT_Ele32_WPTight_Gsf",
    "HLT_Ele35_WPTight_Gsf_L1EGMT",
    "HLT_IsoMu24_eta2p1_MediumChargedIsoPFTau40_Trk1_TightID_eta2p1_Reg_CrossL1",
    "HLT_IsoMu24_eta2p1_MediumChargedIsoPFTau40_Trk1_eta2p1_Reg_CrossL1",
    "HLT_IsoMu24_eta2p1_TightChargedIsoPFTau40_Trk1_TightID_eta2p1_Reg_CrossL1",
    "HLT_IsoMu24_eta2p1_TightChargedIsoPFTau40_Trk1_eta2p1_Reg_CrossL1",
    "HLT_IsoMu30",
    "HLT_L1_CDC_SingleMu_3_er1p2_TOP120_DPHI2p618_3p142",
    "HLT_MediumChargedIsoPFTau50_Trk30_eta2p1_1pr_MET110",
    "HLT_MediumChargedIsoPFTau50_Trk30_eta2p1_1pr_MET120",
    "HLT_MediumChargedIsoPFTau50_Trk30_eta2p1_1pr_MET130",
    "HLT_Mu12_DoublePhoton20",
    "HLT_Mu17_Photon30_IsoCaloId",
    "HLT_Mu19",
    "HLT_Mu19_TrkIsoVVL",
    "HLT_Mu19_TrkIsoVVL_Mu9_TrkIsoVVL",
    "HLT_Mu19_TrkIsoVVL_Mu9_TrkIsoVVL_DZ",
    "HLT_Mu19_TrkIsoVVL_Mu9_TrkIsoVVL_DZ_Mass3p8",
    "HLT_Mu19_TrkIsoVVL_Mu9_TrkIsoVVL_DZ_Mass8",
    "HLT_Mu27_Ele37_CaloIdL_MW",
    "HLT_Mu37_Ele27_CaloIdL_MW",
    "HLT_Mu37_TkMu27",
    "HLT_Mu55",
    "HLT_PFHT380_SixPFJet32_DoublePFBTagDeepCSV_2p2",
    "HLT_PFMET120_PFMHT120_IDTight_HFCleaned",
    "HLT_PFMET120_PFMHT120_IDTight_PFHT60_HFCleaned",
    "HLT_PFMETNoMu120_PFMHTNoMu120_IDTight_HFCleaned",
    "HLT_PFMETTypeOne120_PFMHT120_IDTight_HFCleaned",
    "HLT_Photon25",
    "HLT_Physics_part0",
    "HLT_Physics_part1",
    "HLT_Physics_part2",
    "HLT_Physics_part3",
    "HLT_Physics_part4",
    "HLT_Physics_part5",
    "HLT_Physics_part6",
    "HLT_Physics_part7",
    "HLT_Tau3Mu_Mu5_Mu1_TkMu1_IsoTau10",
    "HLT_Tau3Mu_Mu5_Mu1_TkMu1_IsoTau10_Charge1",
    "HLT_Tau3Mu_Mu5_Mu1_TkMu1_Tau10",
    "HLT_Tau3Mu_Mu5_Mu1_TkMu1_Tau10_Charge1",
    "HLT_Tau3Mu_Mu7_Mu1_TkMu1_IsoTau15",
    "HLT_Tau3Mu_Mu7_Mu1_TkMu1_IsoTau15_Charge1",
    "HLT_Tau3Mu_Mu7_Mu1_TkMu1_Tau15",
    "HLT_Tau3Mu_Mu7_Mu1_TkMu1_Tau15_Charge1",
    "HLT_TriplePhoton_20_20_20_CaloIdLV2",
    "HLT_TriplePhoton_20_20_20_CaloIdLV2_R9IdVL",
    "HLT_TriplePhoton_30_30_10_CaloIdLV2",
    "HLT_TriplePhoton_30_30_10_CaloIdLV2_R9IdVL",
    "HLT_TriplePhoton_35_35_5_CaloIdLV2_R9IdVL",
    "HLT_VBF_DoubleLooseChargedIsoPFTau20_Trk1_eta2p1_Reg",
    "HLT_VBF_DoubleMediumChargedIsoPFTau20_Trk1_eta2p1_Reg",
    "HLT_VBF_DoubleTightChargedIsoPFTau20_Trk1_eta2p1_Reg",
    "HLT_ZeroBias_part0",
    "HLT_ZeroBias_part1",
    "HLT_ZeroBias_part2",
    "HLT_ZeroBias_part3",
    "HLT_ZeroBias_part4",
    "HLT_ZeroBias_part5",
    "HLT_ZeroBias_part6",
    "HLT_ZeroBias_part7",
    "HLT_ZeroBias_part8",
    "HLT_ZeroBias_part9",
  ]),
  ("missing_hlt_paths",               [

  ]),
])

samples_2017["/DoubleEG/Run2017D-17Nov2017-v1/MINIAOD"] = OD([
  ("type",                            "data"),
  ("sample_category",                 "data_obs"),
  ("process_name_specific",           "DoubleEG_Run2017D_17Nov2017_v1"),
  ("nof_files",                       507),
  ("nof_db_files",                    344),
  ("nof_events",                      25209987),
  ("nof_tree_events",                 25209987),
  ("nof_db_events",                   25911432),
  ("fsize_local",                     20579874491), # 20.58GB, avg file size 40.59MB
  ("fsize_db",                        881576196022), # 881.58GB, avg file size 2.56GB
  ("use_it",                          True),
  ("triggers",                        ['2e', '3e']),
  ("has_LHE",                         False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/kaehatah/NanoProduction_v2_2018Apr26/DoubleEG/NanoProduction_v2_2018Apr26_DoubleEG__Run2017D-17Nov2017-v1/180426_000229"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
  ("missing_from_superset",           [
    "HLT_TripleMu_5_3_3_Mass3p8to60_DZ",
  ]),
  ("missing_hlt_paths",               [

  ]),
])

samples_2017["/DoubleEG/Run2017E-17Nov2017-v1/MINIAOD"] = OD([
  ("type",                            "data"),
  ("sample_category",                 "data_obs"),
  ("process_name_specific",           "DoubleEG_Run2017E_17Nov2017_v1"),
  ("nof_files",                       1096),
  ("nof_db_files",                    639),
  ("nof_events",                      54624312),
  ("nof_tree_events",                 54624312),
  ("nof_db_events",                   56235775),
  ("fsize_local",                     47658132283), # 47.66GB, avg file size 43.48MB
  ("fsize_db",                        2140362591723), # 2.14TB, avg file size 3.35GB
  ("use_it",                          True),
  ("triggers",                        ['2e', '3e']),
  ("has_LHE",                         False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/kaehatah/NanoProduction_v2_2018Apr26/DoubleEG/NanoProduction_v2_2018Apr26_DoubleEG__Run2017E-17Nov2017-v1/180426_000436"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
  ("missing_from_superset",           [

  ]),
  ("missing_hlt_paths",               [

  ]),
])

samples_2017["/DoubleEG/Run2017F-17Nov2017-v1/MINIAOD"] = OD([
  ("type",                            "data"),
  ("sample_category",                 "data_obs"),
  ("process_name_specific",           "DoubleEG_Run2017F_17Nov2017_v1"),
  ("nof_files",                       1460),
  ("nof_db_files",                    1024),
  ("nof_events",                      72431395),
  ("nof_tree_events",                 72431395),
  ("nof_db_events",                   74344288),
  ("fsize_local",                     65458121724), # 65.46GB, avg file size 44.83MB
  ("fsize_db",                        2879805741948), # 2.88TB, avg file size 2.81GB
  ("use_it",                          True),
  ("triggers",                        ['2e', '3e']),
  ("has_LHE",                         False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/kaehatah/NanoProduction_v2_2018Apr26/DoubleEG/NanoProduction_v2_2018Apr26_DoubleEG__Run2017F-17Nov2017-v1/180426_000644"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
  ("missing_from_superset",           [
    "HLT_AK8PFJet330_PFAK8BTagCSV_p1",
    "HLT_AK8PFJet330_PFAK8BTagCSV_p17",
    "HLT_Diphoton30_18_PVrealAND_R9Id_AND_IsoCaloId_AND_HE_R9Id_NoPixelVeto_Mass55",
    "HLT_Diphoton30_18_PVrealAND_R9Id_AND_IsoCaloId_AND_HE_R9Id_PixelVeto_Mass55",
    "HLT_DoubleMu2_Jpsi_DoubleTkMu0_Phi",
    "HLT_DoubleMu2_Jpsi_DoubleTrk1_Phi",
    "HLT_DoubleMu3_DCA_PFMET50_PFMHT60",
    "HLT_DoubleMu3_DoubleEle7p5_CaloIdL_TrackIdL_Upsilon",
    "HLT_DoubleMu3_TkMu_DsTau3Mu",
    "HLT_DoubleMu5_Upsilon_DoubleEle3_CaloIdL_TrackIdL",
    "HLT_Ele15_CaloIdL_TrackIdL_IsoVL_PFJet30",
    "HLT_Ele15_Ele8_CaloIdL_TrackIdL_IsoVL",
    "HLT_Ele15_WPLoose_Gsf",
    "HLT_Ele17_WPLoose_Gsf",
    "HLT_IsoMu27_LooseChargedIsoPFTau20_SingleL1",
    "HLT_IsoMu27_MediumChargedIsoPFTau20_SingleL1",
    "HLT_IsoMu27_TightChargedIsoPFTau20_SingleL1",
    "HLT_L1_DoubleJet30_Mass_Min400_Mu10",
    "HLT_Mu12",
    "HLT_Mu15",
    "HLT_Mu18_Mu9",
    "HLT_Mu18_Mu9_DZ",
    "HLT_Mu18_Mu9_SameSign",
    "HLT_Mu18_Mu9_SameSign_DZ",
    "HLT_Mu20_Mu10",
    "HLT_Mu20_Mu10_DZ",
    "HLT_Mu20_Mu10_SameSign",
    "HLT_Mu20_Mu10_SameSign_DZ",
    "HLT_Mu23_Mu12",
    "HLT_Mu23_Mu12_DZ",
    "HLT_Mu23_Mu12_SameSign",
    "HLT_Mu23_Mu12_SameSign_DZ",
    "HLT_PFMET100_PFMHT100_IDTight_PFHT60",
    "HLT_PFMETNoMu100_PFMHTNoMu100_IDTight_PFHT60",
    "HLT_PFMETTypeOne100_PFMHT100_IDTight_PFHT60",
    "HLT_Photon20",
    "HLT_Photon50_R9Id90_HE10_IsoM_EBOnly_PFJetsMJJ300DEta3_PFMET50",
    "HLT_Photon75_R9Id90_HE10_IsoM_EBOnly_PFJetsMJJ300DEta3",
    "HLT_Photon75_R9Id90_HE10_IsoM_EBOnly_PFJetsMJJ600DEta3",
    "HLT_QuadPFJet103_88_75_15",
    "HLT_QuadPFJet103_88_75_15_BTagCSV_p013_VBF2",
    "HLT_QuadPFJet103_88_75_15_DoubleBTagCSV_p013_p08_VBF1",
    "HLT_QuadPFJet105_88_76_15",
    "HLT_QuadPFJet105_88_76_15_BTagCSV_p013_VBF2",
    "HLT_QuadPFJet105_90_76_15_DoubleBTagCSV_p013_p08_VBF1",
    "HLT_QuadPFJet111_90_80_15",
    "HLT_QuadPFJet111_90_80_15_BTagCSV_p013_VBF2",
    "HLT_QuadPFJet111_90_80_15_DoubleBTagCSV_p013_p08_VBF1",
    "HLT_QuadPFJet98_83_71_15",
    "HLT_QuadPFJet98_83_71_15_BTagCSV_p013_VBF2",
    "HLT_QuadPFJet98_83_71_15_DoubleBTagCSV_p013_p08_VBF1",
    "HLT_TrimuonOpen_5_3p5_2_Upsilon_Muon",
    "HLT_TripleMu_5_3_3_Mass3p8to60_DCA",
    "HLT_ZeroBias_Beamspot",
  ]),
  ("missing_hlt_paths",               [

  ]),
])

samples_2017["/DoubleMuon/Run2017B-17Nov2017-v1/MINIAOD"] = OD([
  ("type",                            "data"),
  ("sample_category",                 "data_obs"),
  ("process_name_specific",           "DoubleMuon_Run2017B_17Nov2017_v1"),
  ("nof_files",                       266),
  ("nof_db_files",                    164),
  ("nof_events",                      13572040),
  ("nof_tree_events",                 13572040),
  ("nof_db_events",                   14501767),
  ("fsize_local",                     9377250709), # 9.38GB, avg file size 35.25MB
  ("fsize_db",                        429564397133), # 429.56GB, avg file size 2.62GB
  ("use_it",                          True),
  ("triggers",                        ['2mu', '3mu']),
  ("has_LHE",                         False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/kaehatah/NanoProduction_v2_2018Apr26/DoubleMuon/NanoProduction_v2_2018Apr26_DoubleMuon__Run2017B-17Nov2017-v1/180426_000856"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
  ("missing_from_superset",           [
    "HLT_HcalIsolatedbunch",
    "HLT_L1FatEvents",
  ]),
  ("missing_hlt_paths",               [
    "HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8",
  ]),
])

samples_2017["/DoubleMuon/Run2017C-17Nov2017-v1/MINIAOD"] = OD([
  ("type",                            "data"),
  ("sample_category",                 "data_obs"),
  ("process_name_specific",           "DoubleMuon_Run2017C_17Nov2017_v1"),
  ("nof_files",                       915),
  ("nof_db_files",                    466),
  ("nof_events",                      46273101),
  ("nof_tree_events",                 46273101),
  ("nof_db_events",                   49636525),
  ("fsize_local",                     35579400710), # 35.58GB, avg file size 38.88MB
  ("fsize_db",                        1506932771681), # 1.51TB, avg file size 3.23GB
  ("use_it",                          True),
  ("triggers",                        ['2mu', '3mu']),
  ("has_LHE",                         False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/kaehatah/NanoProduction_v2_2018Apr26/DoubleMuon/NanoProduction_v2_2018Apr26_DoubleMuon__Run2017C-17Nov2017-v1/180426_001058"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
  ("missing_from_superset",           [
    "HLT_DiPFJetAve100_HFJEC",
    "HLT_DiPFJetAve140",
    "HLT_DiPFJetAve160_HFJEC",
    "HLT_DiPFJetAve200",
    "HLT_DiPFJetAve220_HFJEC",
    "HLT_DiPFJetAve260",
    "HLT_DiPFJetAve300_HFJEC",
    "HLT_DiPFJetAve320",
    "HLT_DiPFJetAve40",
    "HLT_DiPFJetAve400",
    "HLT_DiPFJetAve500",
    "HLT_DiPFJetAve60",
    "HLT_DiPFJetAve60_HFJEC",
    "HLT_DiPFJetAve80",
    "HLT_DiPFJetAve80_HFJEC",
    "HLT_Dimuon18_PsiPrime_noCorrL1",
    "HLT_Dimuon24_Phi_noCorrL1",
    "HLT_Dimuon24_Upsilon_noCorrL1",
    "HLT_Dimuon25_Jpsi_noCorrL1",
    "HLT_DoubleEle25_CaloIdL_MW",
    "HLT_DoubleEle27_CaloIdL_MW",
    "HLT_Ele27_Ele37_CaloIdL_MW",
    "HLT_Ele32_WPTight_Gsf",
    "HLT_Ele35_WPTight_Gsf_L1EGMT",
    "HLT_IsoMu24_eta2p1_MediumChargedIsoPFTau40_Trk1_TightID_eta2p1_Reg_CrossL1",
    "HLT_IsoMu24_eta2p1_MediumChargedIsoPFTau40_Trk1_eta2p1_Reg_CrossL1",
    "HLT_IsoMu24_eta2p1_TightChargedIsoPFTau40_Trk1_TightID_eta2p1_Reg_CrossL1",
    "HLT_IsoMu24_eta2p1_TightChargedIsoPFTau40_Trk1_eta2p1_Reg_CrossL1",
    "HLT_IsoMu30",
    "HLT_L1_CDC_SingleMu_3_er1p2_TOP120_DPHI2p618_3p142",
    "HLT_MediumChargedIsoPFTau50_Trk30_eta2p1_1pr_MET110",
    "HLT_MediumChargedIsoPFTau50_Trk30_eta2p1_1pr_MET120",
    "HLT_MediumChargedIsoPFTau50_Trk30_eta2p1_1pr_MET130",
    "HLT_Mu12_DoublePhoton20",
    "HLT_Mu17_Photon30_IsoCaloId",
    "HLT_Mu19",
    "HLT_Mu19_TrkIsoVVL",
    "HLT_Mu19_TrkIsoVVL_Mu9_TrkIsoVVL",
    "HLT_Mu19_TrkIsoVVL_Mu9_TrkIsoVVL_DZ",
    "HLT_Mu19_TrkIsoVVL_Mu9_TrkIsoVVL_DZ_Mass3p8",
    "HLT_Mu19_TrkIsoVVL_Mu9_TrkIsoVVL_DZ_Mass8",
    "HLT_Mu27_Ele37_CaloIdL_MW",
    "HLT_Mu37_Ele27_CaloIdL_MW",
    "HLT_Mu37_TkMu27",
    "HLT_Mu55",
    "HLT_PFHT380_SixPFJet32_DoublePFBTagDeepCSV_2p2",
    "HLT_PFMET120_PFMHT120_IDTight_HFCleaned",
    "HLT_PFMET120_PFMHT120_IDTight_PFHT60_HFCleaned",
    "HLT_PFMETNoMu120_PFMHTNoMu120_IDTight_HFCleaned",
    "HLT_PFMETTypeOne120_PFMHT120_IDTight_HFCleaned",
    "HLT_Photon25",
    "HLT_Physics_part0",
    "HLT_Physics_part1",
    "HLT_Physics_part2",
    "HLT_Physics_part3",
    "HLT_Physics_part4",
    "HLT_Physics_part5",
    "HLT_Physics_part6",
    "HLT_Physics_part7",
    "HLT_Tau3Mu_Mu5_Mu1_TkMu1_IsoTau10",
    "HLT_Tau3Mu_Mu5_Mu1_TkMu1_IsoTau10_Charge1",
    "HLT_Tau3Mu_Mu5_Mu1_TkMu1_Tau10",
    "HLT_Tau3Mu_Mu5_Mu1_TkMu1_Tau10_Charge1",
    "HLT_Tau3Mu_Mu7_Mu1_TkMu1_IsoTau15",
    "HLT_Tau3Mu_Mu7_Mu1_TkMu1_IsoTau15_Charge1",
    "HLT_Tau3Mu_Mu7_Mu1_TkMu1_Tau15",
    "HLT_Tau3Mu_Mu7_Mu1_TkMu1_Tau15_Charge1",
    "HLT_TriplePhoton_20_20_20_CaloIdLV2",
    "HLT_TriplePhoton_20_20_20_CaloIdLV2_R9IdVL",
    "HLT_TriplePhoton_30_30_10_CaloIdLV2",
    "HLT_TriplePhoton_30_30_10_CaloIdLV2_R9IdVL",
    "HLT_TriplePhoton_35_35_5_CaloIdLV2_R9IdVL",
    "HLT_VBF_DoubleLooseChargedIsoPFTau20_Trk1_eta2p1_Reg",
    "HLT_VBF_DoubleMediumChargedIsoPFTau20_Trk1_eta2p1_Reg",
    "HLT_VBF_DoubleTightChargedIsoPFTau20_Trk1_eta2p1_Reg",
    "HLT_ZeroBias_part0",
    "HLT_ZeroBias_part1",
    "HLT_ZeroBias_part2",
    "HLT_ZeroBias_part3",
    "HLT_ZeroBias_part4",
    "HLT_ZeroBias_part5",
    "HLT_ZeroBias_part6",
    "HLT_ZeroBias_part7",
    "HLT_ZeroBias_part8",
    "HLT_ZeroBias_part9",
  ]),
  ("missing_hlt_paths",               [

  ]),
])

samples_2017["/DoubleMuon/Run2017D-17Nov2017-v1/MINIAOD"] = OD([
  ("type",                            "data"),
  ("sample_category",                 "data_obs"),
  ("process_name_specific",           "DoubleMuon_Run2017D_17Nov2017_v1"),
  ("nof_files",                       449),
  ("nof_db_files",                    242),
  ("nof_events",                      22646081),
  ("nof_tree_events",                 22646081),
  ("nof_db_events",                   23075733),
  ("fsize_local",                     17532999507), # 17.53GB, avg file size 39.05MB
  ("fsize_db",                        700300808389), # 700.30GB, avg file size 2.89GB
  ("use_it",                          True),
  ("triggers",                        ['2mu', '3mu']),
  ("has_LHE",                         False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/kaehatah/NanoProduction_v2_2018Apr26/DoubleMuon/NanoProduction_v2_2018Apr26_DoubleMuon__Run2017D-17Nov2017-v1/180426_001619"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
  ("missing_from_superset",           [
    "HLT_TripleMu_5_3_3_Mass3p8to60_DZ",
  ]),
  ("missing_hlt_paths",               [

  ]),
])

samples_2017["/DoubleMuon/Run2017E-17Nov2017-v1/MINIAOD"] = OD([
  ("type",                            "data"),
  ("sample_category",                 "data_obs"),
  ("process_name_specific",           "DoubleMuon_Run2017E_17Nov2017_v1"),
  ("nof_files",                       1003),
  ("nof_db_files",                    596),
  ("nof_events",                      50596536),
  ("nof_tree_events",                 50596536),
  ("nof_db_events",                   51589091),
  ("fsize_local",                     41824963942), # 41.82GB, avg file size 41.70MB
  ("fsize_db",                        1822288632364), # 1.82TB, avg file size 3.06GB
  ("use_it",                          True),
  ("triggers",                        ['2mu', '3mu']),
  ("has_LHE",                         False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/kaehatah/NanoProduction_v2_2018Apr26/DoubleMuon/NanoProduction_v2_2018Apr26_DoubleMuon__Run2017E-17Nov2017-v1/180426_002241"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
  ("missing_from_superset",           [

  ]),
  ("missing_hlt_paths",               [

  ]),
])

samples_2017["/DoubleMuon/Run2017F-17Nov2017-v1/MINIAOD"] = OD([
  ("type",                            "data"),
  ("sample_category",                 "data_obs"),
  ("process_name_specific",           "DoubleMuon_Run2017F_17Nov2017_v1"),
  ("nof_files",                       1506),
  ("nof_db_files",                    875),
  ("nof_events",                      75301738),
  ("nof_tree_events",                 75301738),
  ("nof_db_events",                   79756560),
  ("fsize_local",                     64336647182), # 64.34GB, avg file size 42.72MB
  ("fsize_db",                        2792396630929), # 2.79TB, avg file size 3.19GB
  ("use_it",                          True),
  ("triggers",                        ['2mu', '3mu']),
  ("has_LHE",                         False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/kaehatah/NanoProduction_v2_2018Apr26/DoubleMuon/NanoProduction_v2_2018Apr26_DoubleMuon__Run2017F-17Nov2017-v1/180426_002512"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
  ("missing_from_superset",           [
    "HLT_AK8PFJet330_PFAK8BTagCSV_p1",
    "HLT_AK8PFJet330_PFAK8BTagCSV_p17",
    "HLT_Diphoton30_18_PVrealAND_R9Id_AND_IsoCaloId_AND_HE_R9Id_NoPixelVeto_Mass55",
    "HLT_Diphoton30_18_PVrealAND_R9Id_AND_IsoCaloId_AND_HE_R9Id_PixelVeto_Mass55",
    "HLT_DoubleMu2_Jpsi_DoubleTkMu0_Phi",
    "HLT_DoubleMu2_Jpsi_DoubleTrk1_Phi",
    "HLT_DoubleMu3_DCA_PFMET50_PFMHT60",
    "HLT_DoubleMu3_DoubleEle7p5_CaloIdL_TrackIdL_Upsilon",
    "HLT_DoubleMu3_TkMu_DsTau3Mu",
    "HLT_DoubleMu5_Upsilon_DoubleEle3_CaloIdL_TrackIdL",
    "HLT_Ele15_CaloIdL_TrackIdL_IsoVL_PFJet30",
    "HLT_Ele15_Ele8_CaloIdL_TrackIdL_IsoVL",
    "HLT_Ele15_WPLoose_Gsf",
    "HLT_Ele17_WPLoose_Gsf",
    "HLT_IsoMu27_LooseChargedIsoPFTau20_SingleL1",
    "HLT_IsoMu27_MediumChargedIsoPFTau20_SingleL1",
    "HLT_IsoMu27_TightChargedIsoPFTau20_SingleL1",
    "HLT_L1_DoubleJet30_Mass_Min400_Mu10",
    "HLT_Mu12",
    "HLT_Mu15",
    "HLT_Mu18_Mu9",
    "HLT_Mu18_Mu9_DZ",
    "HLT_Mu18_Mu9_SameSign",
    "HLT_Mu18_Mu9_SameSign_DZ",
    "HLT_Mu20_Mu10",
    "HLT_Mu20_Mu10_DZ",
    "HLT_Mu20_Mu10_SameSign",
    "HLT_Mu20_Mu10_SameSign_DZ",
    "HLT_Mu23_Mu12",
    "HLT_Mu23_Mu12_DZ",
    "HLT_Mu23_Mu12_SameSign",
    "HLT_Mu23_Mu12_SameSign_DZ",
    "HLT_PFMET100_PFMHT100_IDTight_PFHT60",
    "HLT_PFMETNoMu100_PFMHTNoMu100_IDTight_PFHT60",
    "HLT_PFMETTypeOne100_PFMHT100_IDTight_PFHT60",
    "HLT_Photon20",
    "HLT_Photon50_R9Id90_HE10_IsoM_EBOnly_PFJetsMJJ300DEta3_PFMET50",
    "HLT_Photon75_R9Id90_HE10_IsoM_EBOnly_PFJetsMJJ300DEta3",
    "HLT_Photon75_R9Id90_HE10_IsoM_EBOnly_PFJetsMJJ600DEta3",
    "HLT_QuadPFJet103_88_75_15",
    "HLT_QuadPFJet103_88_75_15_BTagCSV_p013_VBF2",
    "HLT_QuadPFJet103_88_75_15_DoubleBTagCSV_p013_p08_VBF1",
    "HLT_QuadPFJet105_88_76_15",
    "HLT_QuadPFJet105_88_76_15_BTagCSV_p013_VBF2",
    "HLT_QuadPFJet105_90_76_15_DoubleBTagCSV_p013_p08_VBF1",
    "HLT_QuadPFJet111_90_80_15",
    "HLT_QuadPFJet111_90_80_15_BTagCSV_p013_VBF2",
    "HLT_QuadPFJet111_90_80_15_DoubleBTagCSV_p013_p08_VBF1",
    "HLT_QuadPFJet98_83_71_15",
    "HLT_QuadPFJet98_83_71_15_BTagCSV_p013_VBF2",
    "HLT_QuadPFJet98_83_71_15_DoubleBTagCSV_p013_p08_VBF1",
    "HLT_TrimuonOpen_5_3p5_2_Upsilon_Muon",
    "HLT_TripleMu_5_3_3_Mass3p8to60_DCA",
    "HLT_ZeroBias_Beamspot",
  ]),
  ("missing_hlt_paths",               [

  ]),
])

samples_2017["/MuonEG/Run2017B-17Nov2017-v1/MINIAOD"] = OD([
  ("type",                            "data"),
  ("sample_category",                 "data_obs"),
  ("process_name_specific",           "MuonEG_Run2017B_17Nov2017_v1"),
  ("nof_files",                       81),
  ("nof_db_files",                    70),
  ("nof_events",                      4153318),
  ("nof_tree_events",                 4153318),
  ("nof_db_events",                   4453465),
  ("fsize_local",                     3665798402), # 3.67GB, avg file size 45.26MB
  ("fsize_db",                        151955610304), # 151.96GB, avg file size 2.17GB
  ("use_it",                          True),
  ("triggers",                        ['1e1mu', '2e1mu', '1e2mu']),
  ("has_LHE",                         False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/kaehatah/NanoProduction_v2_2018Apr26/MuonEG/NanoProduction_v2_2018Apr26_MuonEG__Run2017B-17Nov2017-v1/180426_002749"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
  ("missing_from_superset",           [
    "HLT_HcalIsolatedbunch",
    "HLT_L1FatEvents",
  ]),
  ("missing_hlt_paths",               [
    "HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL",
  ]),
])

samples_2017["/MuonEG/Run2017C-17Nov2017-v1/MINIAOD"] = OD([
  ("type",                            "data"),
  ("sample_category",                 "data_obs"),
  ("process_name_specific",           "MuonEG_Run2017C_17Nov2017_v1"),
  ("nof_files",                       285),
  ("nof_db_files",                    219),
  ("nof_events",                      14579589),
  ("nof_tree_events",                 14579589),
  ("nof_db_events",                   15595214),
  ("fsize_local",                     14043158866), # 14.04GB, avg file size 49.27MB
  ("fsize_db",                        548775705076), # 548.78GB, avg file size 2.51GB
  ("use_it",                          True),
  ("triggers",                        ['1e1mu', '2e1mu', '1e2mu']),
  ("has_LHE",                         False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/kaehatah/NanoProduction_v2_2018Apr26/MuonEG/NanoProduction_v2_2018Apr26_MuonEG__Run2017C-17Nov2017-v1/180426_002954"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
  ("missing_from_superset",           [
    "HLT_DiPFJetAve100_HFJEC",
    "HLT_DiPFJetAve140",
    "HLT_DiPFJetAve160_HFJEC",
    "HLT_DiPFJetAve200",
    "HLT_DiPFJetAve220_HFJEC",
    "HLT_DiPFJetAve260",
    "HLT_DiPFJetAve300_HFJEC",
    "HLT_DiPFJetAve320",
    "HLT_DiPFJetAve40",
    "HLT_DiPFJetAve400",
    "HLT_DiPFJetAve500",
    "HLT_DiPFJetAve60",
    "HLT_DiPFJetAve60_HFJEC",
    "HLT_DiPFJetAve80",
    "HLT_DiPFJetAve80_HFJEC",
    "HLT_Dimuon18_PsiPrime_noCorrL1",
    "HLT_Dimuon24_Phi_noCorrL1",
    "HLT_Dimuon24_Upsilon_noCorrL1",
    "HLT_Dimuon25_Jpsi_noCorrL1",
    "HLT_DoubleEle25_CaloIdL_MW",
    "HLT_DoubleEle27_CaloIdL_MW",
    "HLT_Ele27_Ele37_CaloIdL_MW",
    "HLT_Ele32_WPTight_Gsf",
    "HLT_Ele35_WPTight_Gsf_L1EGMT",
    "HLT_IsoMu24_eta2p1_MediumChargedIsoPFTau40_Trk1_TightID_eta2p1_Reg_CrossL1",
    "HLT_IsoMu24_eta2p1_MediumChargedIsoPFTau40_Trk1_eta2p1_Reg_CrossL1",
    "HLT_IsoMu24_eta2p1_TightChargedIsoPFTau40_Trk1_TightID_eta2p1_Reg_CrossL1",
    "HLT_IsoMu24_eta2p1_TightChargedIsoPFTau40_Trk1_eta2p1_Reg_CrossL1",
    "HLT_IsoMu30",
    "HLT_L1_CDC_SingleMu_3_er1p2_TOP120_DPHI2p618_3p142",
    "HLT_MediumChargedIsoPFTau50_Trk30_eta2p1_1pr_MET110",
    "HLT_MediumChargedIsoPFTau50_Trk30_eta2p1_1pr_MET120",
    "HLT_MediumChargedIsoPFTau50_Trk30_eta2p1_1pr_MET130",
    "HLT_Mu12_DoublePhoton20",
    "HLT_Mu17_Photon30_IsoCaloId",
    "HLT_Mu19",
    "HLT_Mu19_TrkIsoVVL",
    "HLT_Mu19_TrkIsoVVL_Mu9_TrkIsoVVL",
    "HLT_Mu19_TrkIsoVVL_Mu9_TrkIsoVVL_DZ",
    "HLT_Mu19_TrkIsoVVL_Mu9_TrkIsoVVL_DZ_Mass3p8",
    "HLT_Mu19_TrkIsoVVL_Mu9_TrkIsoVVL_DZ_Mass8",
    "HLT_Mu27_Ele37_CaloIdL_MW",
    "HLT_Mu37_Ele27_CaloIdL_MW",
    "HLT_Mu37_TkMu27",
    "HLT_Mu55",
    "HLT_PFHT380_SixPFJet32_DoublePFBTagDeepCSV_2p2",
    "HLT_PFMET120_PFMHT120_IDTight_HFCleaned",
    "HLT_PFMET120_PFMHT120_IDTight_PFHT60_HFCleaned",
    "HLT_PFMETNoMu120_PFMHTNoMu120_IDTight_HFCleaned",
    "HLT_PFMETTypeOne120_PFMHT120_IDTight_HFCleaned",
    "HLT_Photon25",
    "HLT_Physics_part0",
    "HLT_Physics_part1",
    "HLT_Physics_part2",
    "HLT_Physics_part3",
    "HLT_Physics_part4",
    "HLT_Physics_part5",
    "HLT_Physics_part6",
    "HLT_Physics_part7",
    "HLT_Tau3Mu_Mu5_Mu1_TkMu1_IsoTau10",
    "HLT_Tau3Mu_Mu5_Mu1_TkMu1_IsoTau10_Charge1",
    "HLT_Tau3Mu_Mu5_Mu1_TkMu1_Tau10",
    "HLT_Tau3Mu_Mu5_Mu1_TkMu1_Tau10_Charge1",
    "HLT_Tau3Mu_Mu7_Mu1_TkMu1_IsoTau15",
    "HLT_Tau3Mu_Mu7_Mu1_TkMu1_IsoTau15_Charge1",
    "HLT_Tau3Mu_Mu7_Mu1_TkMu1_Tau15",
    "HLT_Tau3Mu_Mu7_Mu1_TkMu1_Tau15_Charge1",
    "HLT_TriplePhoton_20_20_20_CaloIdLV2",
    "HLT_TriplePhoton_20_20_20_CaloIdLV2_R9IdVL",
    "HLT_TriplePhoton_30_30_10_CaloIdLV2",
    "HLT_TriplePhoton_30_30_10_CaloIdLV2_R9IdVL",
    "HLT_TriplePhoton_35_35_5_CaloIdLV2_R9IdVL",
    "HLT_VBF_DoubleLooseChargedIsoPFTau20_Trk1_eta2p1_Reg",
    "HLT_VBF_DoubleMediumChargedIsoPFTau20_Trk1_eta2p1_Reg",
    "HLT_VBF_DoubleTightChargedIsoPFTau20_Trk1_eta2p1_Reg",
    "HLT_ZeroBias_part0",
    "HLT_ZeroBias_part1",
    "HLT_ZeroBias_part2",
    "HLT_ZeroBias_part3",
    "HLT_ZeroBias_part4",
    "HLT_ZeroBias_part5",
    "HLT_ZeroBias_part6",
    "HLT_ZeroBias_part7",
    "HLT_ZeroBias_part8",
    "HLT_ZeroBias_part9",
  ]),
  ("missing_hlt_paths",               [

  ]),
])

samples_2017["/MuonEG/Run2017D-17Nov2017-v1/MINIAOD"] = OD([
  ("type",                            "data"),
  ("sample_category",                 "data_obs"),
  ("process_name_specific",           "MuonEG_Run2017D_17Nov2017_v1"),
  ("nof_files",                       178),
  ("nof_db_files",                    126),
  ("nof_events",                      9012928),
  ("nof_tree_events",                 9012928),
  ("nof_db_events",                   9164365),
  ("fsize_local",                     8713270522), # 8.71GB, avg file size 48.95MB
  ("fsize_db",                        321530133689), # 321.53GB, avg file size 2.55GB
  ("use_it",                          True),
  ("triggers",                        ['1e1mu', '2e1mu', '1e2mu']),
  ("has_LHE",                         False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/kaehatah/NanoProduction_v2_2018Apr26/MuonEG/NanoProduction_v2_2018Apr26_MuonEG__Run2017D-17Nov2017-v1/180426_003159"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
  ("missing_from_superset",           [
    "HLT_TripleMu_5_3_3_Mass3p8to60_DZ",
  ]),
  ("missing_hlt_paths",               [

  ]),
])

samples_2017["/MuonEG/Run2017E-17Nov2017-v1/MINIAOD"] = OD([
  ("type",                            "data"),
  ("sample_category",                 "data_obs"),
  ("process_name_specific",           "MuonEG_Run2017E_17Nov2017_v1"),
  ("nof_files",                       369),
  ("nof_db_files",                    239),
  ("nof_events",                      18703362),
  ("nof_tree_events",                 18703362),
  ("nof_db_events",                   19043421),
  ("fsize_local",                     18850203527), # 18.85GB, avg file size 51.08MB
  ("fsize_db",                        753395415338), # 753.40GB, avg file size 3.15GB
  ("use_it",                          True),
  ("triggers",                        ['1e1mu', '2e1mu', '1e2mu']),
  ("has_LHE",                         False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/kaehatah/NanoProduction_v2_2018Apr26/MuonEG/NanoProduction_v2_2018Apr26_MuonEG__Run2017E-17Nov2017-v1/180426_003408"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
  ("missing_from_superset",           [

  ]),
  ("missing_hlt_paths",               [

  ]),
])

samples_2017["/MuonEG/Run2017F-17Nov2017-v1/MINIAOD"] = OD([
  ("type",                            "data"),
  ("sample_category",                 "data_obs"),
  ("process_name_specific",           "MuonEG_Run2017F_17Nov2017_v1"),
  ("nof_files",                       501),
  ("nof_db_files",                    362),
  ("nof_events",                      25342514),
  ("nof_tree_events",                 25342514),
  ("nof_db_events",                   25776363),
  ("fsize_local",                     26064857734), # 26.06GB, avg file size 52.03MB
  ("fsize_db",                        1031887580033), # 1.03TB, avg file size 2.85GB
  ("use_it",                          True),
  ("triggers",                        ['1e1mu', '2e1mu', '1e2mu']),
  ("has_LHE",                         False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/kaehatah/NanoProduction_v2_2018Apr26/MuonEG/NanoProduction_v2_2018Apr26_MuonEG__Run2017F-17Nov2017-v1/180426_003615"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
  ("missing_from_superset",           [
    "HLT_AK8PFJet330_PFAK8BTagCSV_p1",
    "HLT_AK8PFJet330_PFAK8BTagCSV_p17",
    "HLT_Diphoton30_18_PVrealAND_R9Id_AND_IsoCaloId_AND_HE_R9Id_NoPixelVeto_Mass55",
    "HLT_Diphoton30_18_PVrealAND_R9Id_AND_IsoCaloId_AND_HE_R9Id_PixelVeto_Mass55",
    "HLT_DoubleMu2_Jpsi_DoubleTkMu0_Phi",
    "HLT_DoubleMu2_Jpsi_DoubleTrk1_Phi",
    "HLT_DoubleMu3_DCA_PFMET50_PFMHT60",
    "HLT_DoubleMu3_DoubleEle7p5_CaloIdL_TrackIdL_Upsilon",
    "HLT_DoubleMu3_TkMu_DsTau3Mu",
    "HLT_DoubleMu5_Upsilon_DoubleEle3_CaloIdL_TrackIdL",
    "HLT_Ele15_CaloIdL_TrackIdL_IsoVL_PFJet30",
    "HLT_Ele15_Ele8_CaloIdL_TrackIdL_IsoVL",
    "HLT_Ele15_WPLoose_Gsf",
    "HLT_Ele17_WPLoose_Gsf",
    "HLT_IsoMu27_LooseChargedIsoPFTau20_SingleL1",
    "HLT_IsoMu27_MediumChargedIsoPFTau20_SingleL1",
    "HLT_IsoMu27_TightChargedIsoPFTau20_SingleL1",
    "HLT_L1_DoubleJet30_Mass_Min400_Mu10",
    "HLT_Mu12",
    "HLT_Mu15",
    "HLT_Mu18_Mu9",
    "HLT_Mu18_Mu9_DZ",
    "HLT_Mu18_Mu9_SameSign",
    "HLT_Mu18_Mu9_SameSign_DZ",
    "HLT_Mu20_Mu10",
    "HLT_Mu20_Mu10_DZ",
    "HLT_Mu20_Mu10_SameSign",
    "HLT_Mu20_Mu10_SameSign_DZ",
    "HLT_Mu23_Mu12",
    "HLT_Mu23_Mu12_DZ",
    "HLT_Mu23_Mu12_SameSign",
    "HLT_Mu23_Mu12_SameSign_DZ",
    "HLT_PFMET100_PFMHT100_IDTight_PFHT60",
    "HLT_PFMETNoMu100_PFMHTNoMu100_IDTight_PFHT60",
    "HLT_PFMETTypeOne100_PFMHT100_IDTight_PFHT60",
    "HLT_Photon20",
    "HLT_Photon50_R9Id90_HE10_IsoM_EBOnly_PFJetsMJJ300DEta3_PFMET50",
    "HLT_Photon75_R9Id90_HE10_IsoM_EBOnly_PFJetsMJJ300DEta3",
    "HLT_Photon75_R9Id90_HE10_IsoM_EBOnly_PFJetsMJJ600DEta3",
    "HLT_QuadPFJet103_88_75_15",
    "HLT_QuadPFJet103_88_75_15_BTagCSV_p013_VBF2",
    "HLT_QuadPFJet103_88_75_15_DoubleBTagCSV_p013_p08_VBF1",
    "HLT_QuadPFJet105_88_76_15",
    "HLT_QuadPFJet105_88_76_15_BTagCSV_p013_VBF2",
    "HLT_QuadPFJet105_90_76_15_DoubleBTagCSV_p013_p08_VBF1",
    "HLT_QuadPFJet111_90_80_15",
    "HLT_QuadPFJet111_90_80_15_BTagCSV_p013_VBF2",
    "HLT_QuadPFJet111_90_80_15_DoubleBTagCSV_p013_p08_VBF1",
    "HLT_QuadPFJet98_83_71_15",
    "HLT_QuadPFJet98_83_71_15_BTagCSV_p013_VBF2",
    "HLT_QuadPFJet98_83_71_15_DoubleBTagCSV_p013_p08_VBF1",
    "HLT_TrimuonOpen_5_3p5_2_Upsilon_Muon",
    "HLT_TripleMu_5_3_3_Mass3p8to60_DCA",
    "HLT_ZeroBias_Beamspot",
  ]),
  ("missing_hlt_paths",               [

  ]),
])

samples_2017["/ttHJetToNonbb_M125_TuneCP5_13TeV_amcatnloFXFX_madspin_pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "signal"),
  ("process_name_specific",           "ttHJetToNonbb_M125_amcatnlo"),
  ("nof_files",                       195),
  ("nof_db_files",                    283),
  ("nof_events",                      0),
  ("nof_tree_events",                 9650032),
  ("nof_db_events",                   9650032),
  ("fsize_local",                     25720305081), # 25.72GB, avg file size 131.90MB
  ("fsize_db",                        603282930374), # 603.28GB, avg file size 2.13GB
  ("use_it",                          True),
  ("xsection",                        0.2118),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("has_LHE",                         True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/kaehatah/NanoProduction_v2_2018Apr26/ttHJetToNonbb_M125_TuneCP5_13TeV_amcatnloFXFX_madspin_pythia8/NanoProduction_v2_2018Apr26_ttHJetToNonbb_M125_TuneCP5_13TeV_amcatnloFXFX_madspin_pythia8__RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/180426_004206"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
  ("missing_from_superset",           [
    # not computed
  ]),
  ("missing_hlt_paths",               [

  ]),
])

samples_2017["/ttHToNonbb_M125_TuneCP5_13TeV-powheg-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "signal"),
  ("process_name_specific",           "ttHToNonbb_M125_powheg"),
  ("nof_files",                       155),
  ("nof_db_files",                    219),
  ("nof_events",                      0),
  ("nof_tree_events",                 7669336),
  ("nof_db_events",                   7669336),
  ("fsize_local",                     20741906758), # 20.74GB, avg file size 133.82MB
  ("fsize_db",                        465938496839), # 465.94GB, avg file size 2.13GB
  ("use_it",                          False),
  ("xsection",                        0.2118),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("has_LHE",                         True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/kaehatah/NanoProduction_v2_2018Apr26/ttHToNonbb_M125_TuneCP5_13TeV-powheg-pythia8/NanoProduction_v2_2018Apr26_ttHToNonbb_M125_TuneCP5_13TeV-powheg-pythia8__RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/180426_004436"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
  ("missing_from_superset",           [
    # not computed
  ]),
  ("missing_hlt_paths",               [

  ]),
])

samples_2017["/ttHJetTobb_M125_TuneCP5_13TeV_amcatnloFXFX_madspin_pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "signal"),
  ("process_name_specific",           "ttHJetTobb_M125_amcatnlo"),
  ("nof_files",                       200),
  ("nof_db_files",                    259),
  ("nof_events",                      0),
  ("nof_tree_events",                 9911561),
  ("nof_db_events",                   9911561),
  ("fsize_local",                     26583424399), # 26.58GB, avg file size 132.92MB
  ("fsize_db",                        626042445493), # 626.04GB, avg file size 2.42GB
  ("use_it",                          False),
  ("xsection",                        0.2953),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("has_LHE",                         True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/kaehatah/NanoProduction_v2_2018Apr26/ttHJetTobb_M125_TuneCP5_13TeV_amcatnloFXFX_madspin_pythia8/NanoProduction_v2_2018Apr26_ttHJetTobb_M125_TuneCP5_13TeV_amcatnloFXFX_madspin_pythia8__RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/180502_004852"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
  ("missing_from_superset",           [
    # not computed
  ]),
  ("missing_hlt_paths",               [

  ]),
])

samples_2017["/GluGluHToZZTo4L_M125_13TeV_powheg2_JHUGenV7011_pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "additional_signal_overlap"),
  ("process_name_specific",           "GluGluHToZZTo4L"),
  ("nof_files",                       19),
  ("nof_db_files",                    47),
  ("nof_events",                      0),
  ("nof_tree_events",                 934244),
  ("nof_db_events",                   934244),
  ("fsize_local",                     1345840068), # 1.35GB, avg file size 70.83MB
  ("fsize_db",                        42622664498), # 42.62GB, avg file size 906.87MB
  ("use_it",                          True),
  ("xsection",                        0.01212),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("has_LHE",                         True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/kaehatah/NanoProduction_v2_2018Apr26/GluGluHToZZTo4L_M125_13TeV_powheg2_JHUGenV7011_pythia8/NanoProduction_v2_2018Apr26_GluGluHToZZTo4L_M125_13TeV_powheg2_JHUGenV7011_pythia8__RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/180426_004715"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
  ("missing_from_superset",           [
    # not computed
  ]),
  ("missing_hlt_paths",               [

  ]),
])

samples_2017["/TTZToLLNuNu_M-10_TuneCP5_13TeV-amcatnlo-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "TTZ"),
  ("process_name_specific",           "TTZToLL_M10"),
  ("nof_files",                       153),
  ("nof_db_files",                    199),
  ("nof_events",                      0),
  ("nof_tree_events",                 7563490),
  ("nof_db_events",                   7563490),
  ("fsize_local",                     18067482735), # 18.07GB, avg file size 118.09MB
  ("fsize_db",                        444833969271), # 444.83GB, avg file size 2.24GB
  ("use_it",                          True),
  ("xsection",                        0.2529),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("has_LHE",                         True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/kaehatah/NanoProduction_v2_2018Apr26/TTZToLLNuNu_M-10_TuneCP5_13TeV-amcatnlo-pythia8/NanoProduction_v2_2018Apr26_TTZToLLNuNu_M-10_TuneCP5_13TeV-amcatnlo-pythia8__RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/180426_004956"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
  ("missing_from_superset",           [
    # not computed
  ]),
  ("missing_hlt_paths",               [

  ]),
])

samples_2017["/TTZToLL_M-1to10_TuneCP5_13TeV-amcatnlo-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "TTZ"),
  ("process_name_specific",           "TTZToLL_M-1to10"),
  ("nof_files",                       6),
  ("nof_db_files",                    17),
  ("nof_events",                      0),
  ("nof_tree_events",                 250000),
  ("nof_db_events",                   250000),
  ("fsize_local",                     573189887), # 573.19MB, avg file size 95.53MB
  ("fsize_db",                        14727460148), # 14.73GB, avg file size 866.32MB
  ("use_it",                          True),
  ("xsection",                        0.0493),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("has_LHE",                         True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/kaehatah/NanoProduction_v2_2018Apr26/TTZToLL_M-1to10_TuneCP5_13TeV-amcatnlo-pythia8/NanoProduction_v2_2018Apr26_TTZToLL_M-1to10_TuneCP5_13TeV-amcatnlo-pythia8__RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/180426_005228"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
  ("missing_from_superset",           [
    # not computed
  ]),
  ("missing_hlt_paths",               [

  ]),
])

samples_2017["/TTWJetsToLNu_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v2/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "TTW"),
  ("process_name_specific",           "TTWJetsToLNu"),
  ("nof_files",                       100),
  ("nof_db_files",                    109),
  ("nof_events",                      0),
  ("nof_tree_events",                 4925829),
  ("nof_db_events",                   4925829),
  ("fsize_local",                     12004291899), # 12.00GB, avg file size 120.04MB
  ("fsize_db",                        292280765632), # 292.28GB, avg file size 2.68GB
  ("use_it",                          True),
  ("xsection",                        0.2043),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("has_LHE",                         True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/kaehatah/NanoProduction_v2_2018Apr26/TTWJetsToLNu_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8/NanoProduction_v2_2018Apr26_TTWJetsToLNu_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8__RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v2/180426_005445"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
  ("missing_from_superset",           [
    # not computed
  ]),
  ("missing_hlt_paths",               [

  ]),
])

samples_2017["/TTWJetsToLNu_TuneCP5_PSweights_13TeV-amcatnloFXFX-madspin-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "TTW"),
  ("process_name_specific",           "TTWJetsToLNu_PSweights"),
  ("nof_files",                       99),
  ("nof_db_files",                    122),
  ("nof_events",                      0),
  ("nof_tree_events",                 4889942),
  ("nof_db_events",                   4889942),
  ("fsize_local",                     11898223875), # 11.90GB, avg file size 120.18MB
  ("fsize_db",                        290787551975), # 290.79GB, avg file size 2.38GB
  ("use_it",                          True),
  ("xsection",                        0.2043),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("has_LHE",                         True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/kaehatah/NanoProduction_v2_2018Apr26/TTWJetsToLNu_TuneCP5_PSweights_13TeV-amcatnloFXFX-madspin-pythia8/NanoProduction_v2_2018Apr26_TTWJetsToLNu_TuneCP5_PSweights_13TeV-amcatnloFXFX-madspin-pythia8__RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/180426_005652"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
  ("missing_from_superset",           [
    # not computed
  ]),
  ("missing_hlt_paths",               [

  ]),
])

samples_2017["/TTWW_TuneCP5_13TeV-madgraph-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10_ext1-v2/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "TTWW"),
  ("process_name_specific",           "TTWW"),
  ("nof_files",                       5),
  ("nof_db_files",                    11),
  ("nof_events",                      0),
  ("nof_tree_events",                 200000),
  ("nof_db_events",                   200000),
  ("fsize_local",                     545394676), # 545.39MB, avg file size 109.08MB
  ("fsize_db",                        13111885203), # 13.11GB, avg file size 1.19GB
  ("use_it",                          True),
  ("xsection",                        0.007834),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("has_LHE",                         True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/kaehatah/NanoProduction_v2_2018Apr26/TTWW_TuneCP5_13TeV-madgraph-pythia8/NanoProduction_v2_2018Apr26_TTWW_TuneCP5_13TeV-madgraph-pythia8__RunIIFall17MiniAOD-94X_mc2017_realistic_v10_ext1-v2/180426_005923"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
  ("missing_from_superset",           [
    # not computed
  ]),
  ("missing_hlt_paths",               [

  ]),
])

samples_2017["/ST_s-channel_4f_leptonDecays_TuneCP5_13TeV-amcatnlo-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "TT"),
  ("process_name_specific",           "ST_s-channel_4f_leptonDecays"),
  ("nof_files",                       192),
  ("nof_db_files",                    217),
  ("nof_events",                      0),
  ("nof_tree_events",                 9472619),
  ("nof_db_events",                   9472619),
  ("fsize_local",                     13877180831), # 13.88GB, avg file size 72.28MB
  ("fsize_db",                        423862017407), # 423.86GB, avg file size 1.95GB
  ("use_it",                          True),
  ("xsection",                        3.36),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("has_LHE",                         True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/kaehatah/NanoProduction_v2_2018Apr26/ST_s-channel_4f_leptonDecays_TuneCP5_13TeV-amcatnlo-pythia8/NanoProduction_v2_2018Apr26_ST_s-channel_4f_leptonDecays_TuneCP5_13TeV-amcatnlo-pythia8__RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/180426_010153"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
  ("missing_from_superset",           [
    # not computed
  ]),
  ("missing_hlt_paths",               [

  ]),
])

samples_2017["/ST_t-channel_antitop_4f_inclusiveDecays_TuneCP5_13TeV-powhegV2-madspin-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "TT"),
  ("process_name_specific",           "ST_t-channel_antitop_4f_inclusiveDecays"),
  ("nof_files",                       79),
  ("nof_db_files",                    116),
  ("nof_events",                      0),
  ("nof_tree_events",                 3891190),
  ("nof_db_events",                   3891190),
  ("fsize_local",                     5928072226), # 5.93GB, avg file size 75.04MB
  ("fsize_db",                        177784436788), # 177.78GB, avg file size 1.53GB
  ("use_it",                          True),
  ("xsection",                        80.95),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("has_LHE",                         True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/kaehatah/NanoProduction_v2_2018Apr26/ST_t-channel_antitop_4f_inclusiveDecays_TuneCP5_13TeV-powhegV2-madspin-pythia8/NanoProduction_v2_2018Apr26_ST_t-channel_antitop_4f_inclusiveDecays_TuneCP5_13TeV-powhegV2-madspin-pythia8__RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/180426_010401"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
  ("missing_from_superset",           [
    # not computed
  ]),
  ("missing_hlt_paths",               [

  ]),
])

samples_2017["/ST_t-channel_top_4f_inclusiveDecays_TuneCP5_13TeV-powhegV2-madspin-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "TT"),
  ("process_name_specific",           "ST_t-channel_top_4f_inclusiveDecays"),
  ("nof_files",                       130),
  ("nof_db_files",                    186),
  ("nof_events",                      0),
  ("nof_tree_events",                 5841455),
  ("nof_db_events",                   5841455),
  ("fsize_local",                     8963984476), # 8.96GB, avg file size 68.95MB
  ("fsize_db",                        268058212482), # 268.06GB, avg file size 1.44GB
  ("use_it",                          True),
  ("xsection",                        136.02),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("has_LHE",                         True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/kaehatah/NanoProduction_v2_2018Apr26/ST_t-channel_top_4f_inclusiveDecays_TuneCP5_13TeV-powhegV2-madspin-pythia8/NanoProduction_v2_2018Apr26_ST_t-channel_top_4f_inclusiveDecays_TuneCP5_13TeV-powhegV2-madspin-pythia8__RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/180426_010639"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
  ("missing_from_superset",           [
    # not computed
  ]),
  ("missing_hlt_paths",               [

  ]),
])

samples_2017["/ST_tW_antitop_5f_inclusiveDecays_TuneCP5_13TeV-powheg-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "TT"),
  ("process_name_specific",           "ST_tW_antitop_5f_inclusiveDecays"),
  ("nof_files",                       157),
  ("nof_db_files",                    155),
  ("nof_events",                      0),
  ("nof_tree_events",                 7756300),
  ("nof_db_events",                   7756300),
  ("fsize_local",                     13412794950), # 13.41GB, avg file size 85.43MB
  ("fsize_db",                        386122494678), # 386.12GB, avg file size 2.49GB
  ("use_it",                          True),
  ("xsection",                        35.85),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("has_LHE",                         True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/kaehatah/NanoProduction_v2_2018Apr26/ST_tW_antitop_5f_inclusiveDecays_TuneCP5_13TeV-powheg-pythia8/NanoProduction_v2_2018Apr26_ST_tW_antitop_5f_inclusiveDecays_TuneCP5_13TeV-powheg-pythia8__RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/180426_010915"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
  ("missing_from_superset",           [
    # not computed
  ]),
  ("missing_hlt_paths",               [

  ]),
])

samples_2017["/ST_tW_top_5f_inclusiveDecays_TuneCP5_13TeV-powheg-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "TT"),
  ("process_name_specific",           "ST_tW_top_5f_inclusiveDecays"),
  ("nof_files",                       153),
  ("nof_db_files",                    183),
  ("nof_events",                      0),
  ("nof_tree_events",                 7558006),
  ("nof_db_events",                   7558006),
  ("fsize_local",                     13070339562), # 13.07GB, avg file size 85.43MB
  ("fsize_db",                        376466493438), # 376.47GB, avg file size 2.06GB
  ("use_it",                          True),
  ("xsection",                        35.85),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("has_LHE",                         True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/kaehatah/NanoProduction_v2_2018Apr26/ST_tW_top_5f_inclusiveDecays_TuneCP5_13TeV-powheg-pythia8/NanoProduction_v2_2018Apr26_ST_tW_top_5f_inclusiveDecays_TuneCP5_13TeV-powheg-pythia8__RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/180426_011117"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
  ("missing_from_superset",           [
    # not computed
  ]),
  ("missing_hlt_paths",               [

  ]),
])

samples_2017["/TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v2/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "TT"),
  ("process_name_specific",           "TTTo2L2Nu"),
  ("nof_files",                       177),
  ("nof_db_files",                    164),
  ("nof_events",                      0),
  ("nof_tree_events",                 8705576),
  ("nof_db_events",                   8705576),
  ("fsize_local",                     16194715196), # 16.19GB, avg file size 91.50MB
  ("fsize_db",                        451436194017), # 451.44GB, avg file size 2.75GB
  ("use_it",                          True),
  ("xsection",                        88.29),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("has_LHE",                         True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/kaehatah/NanoProduction_v2_2018Apr26/TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8/NanoProduction_v2_2018Apr26_TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8__RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v2/180426_011318"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
  ("missing_from_superset",           [
    # not computed
  ]),
  ("missing_hlt_paths",               [

  ]),
])

samples_2017["/TTTo2L2Nu_TuneCP5_PSweights_13TeV-powheg-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "TT"),
  ("process_name_specific",           "TTTo2L2Nu_PSweights"),
  ("nof_files",                       1411),
  ("nof_db_files",                    1230),
  ("nof_events",                      0),
  ("nof_tree_events",                 69705626),
  ("nof_db_events",                   69705626),
  ("fsize_local",                     129582511235), # 129.58GB, avg file size 91.84MB
  ("fsize_db",                        3608766343800), # 3.61TB, avg file size 2.93GB
  ("use_it",                          False),
  ("xsection",                        88.29),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("has_LHE",                         True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/kaehatah/NanoProduction_v2_2018Apr26/TTTo2L2Nu_TuneCP5_PSweights_13TeV-powheg-pythia8/NanoProduction_v2_2018Apr26_TTTo2L2Nu_TuneCP5_PSweights_13TeV-powheg-pythia8__RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/180502_005044"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
  ("missing_from_superset",           [
    # not computed
  ]),
  ("missing_hlt_paths",               [

  ]),
])

samples_2017["/TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "TT"),
  ("process_name_specific",           "TTToSemiLeptonic"),
  ("nof_files",                       831),
  ("nof_db_files",                    743),
  ("nof_events",                      0),
  ("nof_tree_events",                 41161951),
  ("nof_db_events",                   41161951),
  ("fsize_local",                     79145829697), # 79.15GB, avg file size 95.24MB
  ("fsize_db",                        2166068169129), # 2.17TB, avg file size 2.92GB
  ("use_it",                          True),
  ("xsection",                        365.34),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("has_LHE",                         True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/kaehatah/NanoProduction_v2_2018Apr26/TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8/NanoProduction_v2_2018Apr26_TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8__RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/180426_011520"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
  ("missing_from_superset",           [
    # not computed
  ]),
  ("missing_hlt_paths",               [

  ]),
])

samples_2017["/TTToSemiLeptonic_TuneCP5_PSweights_13TeV-powheg-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "TT"),
  ("process_name_specific",           "TTToSemiLeptonic_PSweights"),
  ("nof_files",                       2247),
  ("nof_db_files",                    2032),
  ("nof_events",                      0),
  ("nof_tree_events",                 111381888),
  ("nof_db_events",                   111381888),
  ("fsize_local",                     214190811519), # 214.19GB, avg file size 95.32MB
  ("fsize_db",                        5860979058540), # 5.86TB, avg file size 2.88GB
  ("use_it",                          False),
  ("xsection",                        365.34),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("has_LHE",                         True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/kaehatah/NanoProduction_v2_2018Apr26/TTToSemiLeptonic_TuneCP5_PSweights_13TeV-powheg-pythia8/NanoProduction_v2_2018Apr26_TTToSemiLeptonic_TuneCP5_PSweights_13TeV-powheg-pythia8__RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/180502_005310"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
  ("missing_from_superset",           [
    # not computed
  ]),
  ("missing_hlt_paths",               [

  ]),
])

samples_2017["/TTToHadronic_TuneCP5_13TeV-powheg-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "TT"),
  ("process_name_specific",           "TTToHadronic"),
  ("nof_files",                       860),
  ("nof_db_files",                    765),
  ("nof_events",                      0),
  ("nof_tree_events",                 42678688),
  ("nof_db_events",                   42678688),
  ("fsize_local",                     83077815921), # 83.08GB, avg file size 96.60MB
  ("fsize_db",                        2292321642457), # 2.29TB, avg file size 3.00GB
  ("use_it",                          True),
  ("xsection",                        377.96),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("has_LHE",                         True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/kaehatah/NanoProduction_v2_2018Apr26/TTToHadronic_TuneCP5_13TeV-powheg-pythia8/NanoProduction_v2_2018Apr26_TTToHadronic_TuneCP5_13TeV-powheg-pythia8__RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/180426_011722"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
  ("missing_from_superset",           [
    # not computed
  ]),
  ("missing_hlt_paths",               [

  ]),
])

samples_2017["/TTToHadronic_TuneCP5_PSweights_13TeV-powheg-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "TT"),
  ("process_name_specific",           "TTToHadronic_PSweights"),
  ("nof_files",                       2618),
  ("nof_db_files",                    2498),
  ("nof_events",                      0),
  ("nof_tree_events",                 129985840),
  ("nof_db_events",                   129985840),
  ("fsize_local",                     253037895099), # 253.04GB, avg file size 96.65MB
  ("fsize_db",                        6970450887587), # 6.97TB, avg file size 2.79GB
  ("use_it",                          False),
  ("xsection",                        377.96),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("has_LHE",                         True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/kaehatah/NanoProduction_v2_2018Apr26/TTToHadronic_TuneCP5_PSweights_13TeV-powheg-pythia8/NanoProduction_v2_2018Apr26_TTToHadronic_TuneCP5_PSweights_13TeV-powheg-pythia8__RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/180502_005536"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
  ("missing_from_superset",           [
    # not computed
  ]),
  ("missing_hlt_paths",               [

  ]),
])

samples_2017["/DYJetsToLL_M-10to50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v2/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "EWK"),
  ("process_name_specific",           "DYJetsToLL_M-10to50"),
  ("nof_files",                       783),
  ("nof_db_files",                    508),
  ("nof_events",                      0),
  ("nof_tree_events",                 38832197),
  ("nof_db_events",                   38832197),
  ("fsize_local",                     25124735447), # 25.12GB, avg file size 32.09MB
  ("fsize_db",                        1343136870100), # 1.34TB, avg file size 2.64GB
  ("use_it",                          True),
  ("xsection",                        18610.0),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("has_LHE",                         True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/kaehatah/NanoProduction_v2_2018Apr26/DYJetsToLL_M-10to50_TuneCP5_13TeV-madgraphMLM-pythia8/NanoProduction_v2_2018Apr26_DYJetsToLL_M-10to50_TuneCP5_13TeV-madgraphMLM-pythia8__RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v2/180426_011926"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
  ("missing_from_superset",           [
    # not computed
  ]),
  ("missing_hlt_paths",               [

  ]),
])

samples_2017["/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "EWK"),
  ("process_name_specific",           "DYJetsToLL_M-50"),
  ("nof_files",                       542),
  ("nof_db_files",                    372),
  ("nof_events",                      0),
  ("nof_tree_events",                 26923935),
  ("nof_db_events",                   26923935),
  ("fsize_local",                     28709057318), # 28.71GB, avg file size 52.97MB
  ("fsize_db",                        1065736102325), # 1.07TB, avg file size 2.86GB
  ("use_it",                          True),
  ("xsection",                        5765.4),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("has_LHE",                         True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/kaehatah/NanoProduction_v2_2018Apr26/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/NanoProduction_v2_2018Apr26_DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8__RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/180426_012230"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
  ("missing_from_superset",           [
    # not computed
  ]),
  ("missing_hlt_paths",               [

  ]),
])

samples_2017["/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10_ext1-v1/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "EWK"),
  ("process_name_specific",           "DYJetsToLL_M-50_ext1"),
  ("nof_files",                       3752),
  ("nof_db_files",                    2752),
  ("nof_events",                      0),
  ("nof_tree_events",                 185998625),
  ("nof_db_events",                   185998625),
  ("fsize_local",                     198263559520), # 198.26GB, avg file size 52.84MB
  ("fsize_db",                        7376341087077), # 7.38TB, avg file size 2.68GB
  ("use_it",                          True),
  ("xsection",                        5765.4),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("has_LHE",                         True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/kaehatah/NanoProduction_v2_2018Apr26/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/NanoProduction_v2_2018Apr26_DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8__RunIIFall17MiniAOD-94X_mc2017_realistic_v10_ext1-v1/180502_100405"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
  ("missing_from_superset",           [
    # not computed
  ]),
  ("missing_hlt_paths",               [

  ]),
])

samples_2017["/WJetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "EWK"),
  ("process_name_specific",           "WJetsToLNu"),
  ("nof_files",                       479),
  ("nof_db_files",                    382),
  ("nof_events",                      0),
  ("nof_tree_events",                 23240598),
  ("nof_db_events",                   23240598),
  ("fsize_local",                     19087293127), # 19.09GB, avg file size 39.85MB
  ("fsize_db",                        882645881655), # 882.65GB, avg file size 2.31GB
  ("use_it",                          True),
  ("xsection",                        61526.7),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("has_LHE",                         True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/kaehatah/NanoProduction_v2_2018Apr26/WJetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/NanoProduction_v2_2018Apr26_WJetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8__RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/180426_012507"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
  ("missing_from_superset",           [
    # not computed
  ]),
  ("missing_hlt_paths",               [

  ]),
])

samples_2017["/WWTo2L2Nu_NNPDF31_TuneCP5_13TeV-powheg-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "EWK"),
  ("process_name_specific",           "WWTo2L2Nu"),
  ("nof_files",                       37),
  ("nof_db_files",                    50),
  ("nof_events",                      0),
  ("nof_tree_events",                 1818828),
  ("nof_db_events",                   1818828),
  ("fsize_local",                     2206374126), # 2.21GB, avg file size 59.63MB
  ("fsize_db",                        75643188117), # 75.64GB, avg file size 1.51GB
  ("use_it",                          True),
  ("xsection",                        12.178),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("has_LHE",                         True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/kaehatah/NanoProduction_v2_2018Apr26/WWTo2L2Nu_NNPDF31_TuneCP5_13TeV-powheg-pythia8/NanoProduction_v2_2018Apr26_WWTo2L2Nu_NNPDF31_TuneCP5_13TeV-powheg-pythia8__RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/180426_012710"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
  ("missing_from_superset",           [
    # not computed
  ]),
  ("missing_hlt_paths",               [

  ]),
])

samples_2017["/WZTo3LNu_TuneCP5_13TeV-amcatnloFXFX-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v2/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "EWK"),
  ("process_name_specific",           "WZTo3LNu"),
  ("nof_files",                       217),
  ("nof_db_files",                    212),
  ("nof_events",                      0),
  ("nof_tree_events",                 10751052),
  ("nof_db_events",                   10751052),
  ("fsize_local",                     13469758957), # 13.47GB, avg file size 62.07MB
  ("fsize_db",                        452807583489), # 452.81GB, avg file size 2.14GB
  ("use_it",                          True),
  ("xsection",                        4.42965),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("has_LHE",                         True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/kaehatah/NanoProduction_v2_2018Apr26/WZTo3LNu_TuneCP5_13TeV-amcatnloFXFX-pythia8/NanoProduction_v2_2018Apr26_WZTo3LNu_TuneCP5_13TeV-amcatnloFXFX-pythia8__RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v2/180426_012904"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
  ("missing_from_superset",           [
    # not computed
  ]),
  ("missing_hlt_paths",               [

  ]),
])

samples_2017["/ZZTo4L_13TeV_powheg_pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v2/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "EWK"),
  ("process_name_specific",           "ZZTo4L"),
  ("nof_files",                       142),
  ("nof_db_files",                    204),
  ("nof_events",                      0),
  ("nof_tree_events",                 6960289),
  ("nof_db_events",                   6960289),
  ("fsize_local",                     8016169937), # 8.02GB, avg file size 56.45MB
  ("fsize_db",                        322020515003), # 322.02GB, avg file size 1.58GB
  ("use_it",                          True),
  ("xsection",                        1.256),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("has_LHE",                         True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/kaehatah/NanoProduction_v2_2018Apr26/ZZTo4L_13TeV_powheg_pythia8/NanoProduction_v2_2018Apr26_ZZTo4L_13TeV_powheg_pythia8__RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v2/180426_013103"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
  ("missing_from_superset",           [
    # not computed
  ]),
  ("missing_hlt_paths",               [

  ]),
])

samples_2017["/ZZTo4L_13TeV_powheg_pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10_ext1-v1/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "EWK"),
  ("process_name_specific",           "ZZTo4L_ext1"),
  ("nof_files",                       1929),
  ("nof_db_files",                    1490),
  ("nof_events",                      0),
  ("nof_tree_events",                 95716759),
  ("nof_db_events",                   95716759),
  ("fsize_local",                     110095041935), # 110.10GB, avg file size 57.07MB
  ("fsize_db",                        3881682466950), # 3.88TB, avg file size 2.61GB
  ("use_it",                          True),
  ("xsection",                        1.256),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("has_LHE",                         True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/kaehatah/NanoProduction_v2_2018Apr26/ZZTo4L_13TeV_powheg_pythia8/NanoProduction_v2_2018Apr26_ZZTo4L_13TeV_powheg_pythia8__RunIIFall17MiniAOD-94X_mc2017_realistic_v10_ext1-v1/180426_013334"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
  ("missing_from_superset",           [
    # not computed
  ]),
  ("missing_hlt_paths",               [

  ]),
])

samples_2017["/TTGJets_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "Rares"),
  ("process_name_specific",           "TTGJets"),
  ("nof_files",                       94),
  ("nof_db_files",                    138),
  ("nof_events",                      0),
  ("nof_tree_events",                 4647278),
  ("nof_db_events",                   4647278),
  ("fsize_local",                     10647577280), # 10.65GB, avg file size 113.27MB
  ("fsize_db",                        269969335093), # 269.97GB, avg file size 1.96GB
  ("use_it",                          True),
  ("xsection",                        3.697),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("has_LHE",                         True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/kaehatah/NanoProduction_v2_2018Apr26/TTGJets_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8/NanoProduction_v2_2018Apr26_TTGJets_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8__RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/180426_013609"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
  ("missing_from_superset",           [
    # not computed
  ]),
  ("missing_hlt_paths",               [

  ]),
])

samples_2017["/TTTT_TuneCP5_13TeV-amcatnlo-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v2/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "Rares"),
  ("process_name_specific",           "TTTT"),
  ("nof_files",                       21),
  ("nof_db_files",                    29),
  ("nof_events",                      0),
  ("nof_tree_events",                 993804),
  ("nof_db_events",                   993804),
  ("fsize_local",                     3522818144), # 3.52GB, avg file size 167.75MB
  ("fsize_db",                        77438656415), # 77.44GB, avg file size 2.67GB
  ("use_it",                          True),
  ("xsection",                        0.008213),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("has_LHE",                         True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/kaehatah/NanoProduction_v2_2018Apr26/TTTT_TuneCP5_13TeV-amcatnlo-pythia8/NanoProduction_v2_2018Apr26_TTTT_TuneCP5_13TeV-amcatnlo-pythia8__RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v2/180426_013810"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
  ("missing_from_superset",           [
    # not computed
  ]),
  ("missing_hlt_paths",               [

  ]),
])

samples_2017["/tZq_ll_4f_ckm_NLO_TuneCP5_PSweights_13TeV-amcatnlo-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "Rares"),
  ("process_name_specific",           "tZq_ll_4f"),
  ("nof_files",                       267),
  ("nof_db_files",                    292),
  ("nof_events",                      0),
  ("nof_tree_events",                 13220024),
  ("nof_db_events",                   13220024),
  ("fsize_local",                     29116153331), # 29.12GB, avg file size 109.05MB
  ("fsize_db",                        723683119488), # 723.68GB, avg file size 2.48GB
  ("use_it",                          True),
  ("xsection",                        0.0758),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("has_LHE",                         True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/kaehatah/NanoProduction_v2_2018Apr26/tZq_ll_4f_ckm_NLO_TuneCP5_PSweights_13TeV-amcatnlo-pythia8/NanoProduction_v2_2018Apr26_tZq_ll_4f_ckm_NLO_TuneCP5_PSweights_13TeV-amcatnlo-pythia8__RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/180426_013940"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
  ("missing_from_superset",           [
    # not computed
  ]),
  ("missing_hlt_paths",               [

  ]),
])

samples_2017["/WWTo2L2Nu_DoubleScattering_13TeV-herwigpp/RunIIFall17MiniAOD-94X_mc2017_realistic_v11-v1/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "Rares"),
  ("process_name_specific",           "WWTo2L2Nu_DoubleScattering"),
  ("nof_files",                       21),
  ("nof_db_files",                    23),
  ("nof_events",                      0),
  ("nof_tree_events",                 1000000),
  ("nof_db_events",                   1000000),
  ("fsize_local",                     926014783), # 926.01MB, avg file size 44.10MB
  ("fsize_db",                        42876536279), # 42.88GB, avg file size 1.86GB
  ("use_it",                          True),
  ("xsection",                        0.1743),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("has_LHE",                         False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/kaehatah/NanoProduction_v2_2018Apr26/WWTo2L2Nu_DoubleScattering_13TeV-herwigpp/NanoProduction_v2_2018Apr26_WWTo2L2Nu_DoubleScattering_13TeV-herwigpp__RunIIFall17MiniAOD-94X_mc2017_realistic_v11-v1/180426_014217"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
  ("missing_from_superset",           [
    # not computed
  ]),
  ("missing_hlt_paths",               [

  ]),
])

samples_2017["/WWW_4F_TuneCP5_13TeV-amcatnlo-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v11-v1/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "Rares"),
  ("process_name_specific",           "WWW_4F"),
  ("nof_files",                       5),
  ("nof_db_files",                    21),
  ("nof_events",                      0),
  ("nof_tree_events",                 240000),
  ("nof_db_events",                   240000),
  ("fsize_local",                     403952166), # 403.95MB, avg file size 80.79MB
  ("fsize_db",                        11711799646), # 11.71GB, avg file size 557.70MB
  ("use_it",                          True),
  ("xsection",                        0.2086),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("has_LHE",                         True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/kaehatah/NanoProduction_v2_2018Apr26/WWW_4F_TuneCP5_13TeV-amcatnlo-pythia8/NanoProduction_v2_2018Apr26_WWW_4F_TuneCP5_13TeV-amcatnlo-pythia8__RunIIFall17MiniAOD-94X_mc2017_realistic_v11-v1/180426_014419"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
  ("missing_from_superset",           [
    # not computed
  ]),
  ("missing_hlt_paths",               [

  ]),
])

samples_2017["/WWZ_4F_TuneCP5_13TeV-amcatnlo-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v11-v1/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "Rares"),
  ("process_name_specific",           "WWZ_4F"),
  ("nof_files",                       6),
  ("nof_db_files",                    14),
  ("nof_events",                      0),
  ("nof_tree_events",                 250000),
  ("nof_db_events",                   250000),
  ("fsize_local",                     462598196), # 462.60MB, avg file size 77.10MB
  ("fsize_db",                        13268139304), # 13.27GB, avg file size 947.72MB
  ("use_it",                          True),
  ("xsection",                        0.1651),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("has_LHE",                         True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/kaehatah/NanoProduction_v2_2018Apr26/WWZ_4F_TuneCP5_13TeV-amcatnlo-pythia8/NanoProduction_v2_2018Apr26_WWZ_4F_TuneCP5_13TeV-amcatnlo-pythia8__RunIIFall17MiniAOD-94X_mc2017_realistic_v11-v1/180503_104449"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
  ("missing_from_superset",           [
    # not computed
  ]),
  ("missing_hlt_paths",               [

  ]),
])

samples_2017["/WZZ_TuneCP5_13TeV-amcatnlo-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v11-v1/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "Rares"),
  ("process_name_specific",           "WZZ"),
  ("nof_files",                       6),
  ("nof_db_files",                    18),
  ("nof_events",                      0),
  ("nof_tree_events",                 250000),
  ("nof_db_events",                   250000),
  ("fsize_local",                     453244807), # 453.24MB, avg file size 75.54MB
  ("fsize_db",                        12226507693), # 12.23GB, avg file size 679.25MB
  ("use_it",                          True),
  ("xsection",                        0.05565),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("has_LHE",                         True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/kaehatah/NanoProduction_v2_2018Apr26/WZZ_TuneCP5_13TeV-amcatnlo-pythia8/NanoProduction_v2_2018Apr26_WZZ_TuneCP5_13TeV-amcatnlo-pythia8__RunIIFall17MiniAOD-94X_mc2017_realistic_v11-v1/180426_014619"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
  ("missing_from_superset",           [
    # not computed
  ]),
  ("missing_hlt_paths",               [

  ]),
])

samples_2017["/ZZZ_TuneCP5_13TeV-amcatnlo-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v11-v1/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "Rares"),
  ("process_name_specific",           "ZZZ"),
  ("nof_files",                       6),
  ("nof_db_files",                    17),
  ("nof_events",                      0),
  ("nof_tree_events",                 250000),
  ("nof_db_events",                   250000),
  ("fsize_local",                     414329487), # 414.33MB, avg file size 69.05MB
  ("fsize_db",                        11782250391), # 11.78GB, avg file size 693.07MB
  ("use_it",                          True),
  ("xsection",                        0.01398),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("has_LHE",                         True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/kaehatah/NanoProduction_v2_2018Apr26/ZZZ_TuneCP5_13TeV-amcatnlo-pythia8/NanoProduction_v2_2018Apr26_ZZZ_TuneCP5_13TeV-amcatnlo-pythia8__RunIIFall17MiniAOD-94X_mc2017_realistic_v11-v1/180426_014816"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
  ("missing_from_superset",           [
    # not computed
  ]),
  ("missing_hlt_paths",               [

  ]),
])

samples_2017["/THQ_4f_Hincl_13TeV_madgraph_pythia8_Fall17/private/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "tH"),
  ("process_name_specific",           "THQ"),
  ("nof_files",                       9),
  ("nof_db_files",                    9),
  ("nof_events",                      0),
  ("nof_tree_events",                 124500),
  ("nof_db_events",                   124500),
  ("fsize_local",                     307832172), # 307.83MB, avg file size 34.20MB
  ("fsize_db",                        9518371556), # 9.52GB, avg file size 1.06GB
  ("use_it",                          True),
  ("xsection",                        0.07096),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("has_LHE",                         True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/kaehatah/NanoProduction_v2_2018May23/THQ_4f_Hincl_13TeV_madgraph_pythia8_Fall17/NanoProduction_v2_2018May23_THQ_4f_Hincl_13TeV_madgraph_pythia8_Fall17__private/180523_135212"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
  ("missing_from_superset",           [
    # not computed
  ]),
  ("missing_hlt_paths",               [

  ]),
])

samples_2017["/THW_5f_Hincl_13TeV_madgraph_pythia8_Fall17/private/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "tH"),
  ("process_name_specific",           "THW"),
  ("nof_files",                       4),
  ("nof_db_files",                    4),
  ("nof_events",                      0),
  ("nof_tree_events",                 50000),
  ("nof_db_events",                   50000),
  ("fsize_local",                     147053622), # 147.05MB, avg file size 36.76MB
  ("fsize_db",                        4388282654), # 4.39GB, avg file size 1.10GB
  ("use_it",                          True),
  ("xsection",                        0.01561),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("has_LHE",                         True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/kaehatah/NanoProduction_v2_2018May23/THW_5f_Hincl_13TeV_madgraph_pythia8_Fall17/NanoProduction_v2_2018May23_THW_5f_Hincl_13TeV_madgraph_pythia8_Fall17__private/180523_135457"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
  ("missing_from_superset",           [
    # not computed
  ]),
  ("missing_hlt_paths",               [

  ]),
])

samples_2017["/ST_tWll_5f_LO_TuneCP5_PSweights_13TeV_madgraph_pythia8_Fall17/private/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "TT"),
  ("process_name_specific",           "ST_tWll"),
  ("nof_files",                       1),
  ("nof_db_files",                    1),
  ("nof_events",                      0),
  ("nof_tree_events",                 12500),
  ("nof_db_events",                   12500),
  ("fsize_local",                     31286649), # 31.29MB, avg file size 31.29MB
  ("fsize_db",                        1047598022), # 1.05GB, avg file size 1.05GB
  ("use_it",                          True),
  ("xsection",                        0.01103),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("has_LHE",                         True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/kaehatah/NanoProduction_v2_2018May23/ST_tWll_5f_LO_TuneCP5_PSweights_13TeV_madgraph_pythia8_Fall17/NanoProduction_v2_2018May23_ST_tWll_5f_LO_TuneCP5_PSweights_13TeV_madgraph_pythia8_Fall17__private/180523_131901"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
  ("missing_from_superset",           [
    # not computed
  ]),
  ("missing_hlt_paths",               [

  ]),
])

samples_2017["/VHToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_Fall17/private/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "VH"),
  ("process_name_specific",           "VHToNonbb_M125"),
  ("nof_files",                       12),
  ("nof_db_files",                    12),
  ("nof_events",                      0),
  ("nof_tree_events",                 200165),
  ("nof_db_events",                   200165),
  ("fsize_local",                     330997443), # 331.00MB, avg file size 27.58MB
  ("fsize_db",                        12634080628), # 12.63GB, avg file size 1.05GB
  ("use_it",                          True),
  ("xsection",                        0.952),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("has_LHE",                         True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/kaehatah/NanoProduction_v2_2018May23/VHToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_Fall17/NanoProduction_v2_2018May23_VHToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_Fall17__private/180523_132230"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
  ("missing_from_superset",           [
    # not computed
  ]),
  ("missing_hlt_paths",               [

  ]),
])

samples_2017["/WpWpJJ_EWK_QCD_TuneCP5_13TeV_madgraph_pythia8_Fall17/private/MINIAODSIM"] = OD([
  ("type",                            "mc"),
  ("sample_category",                 "Rares"),
  ("process_name_specific",           "WpWpJJ_EWK_QCD"),
  ("nof_files",                       2),
  ("nof_db_files",                    2),
  ("nof_events",                      0),
  ("nof_tree_events",                 24750),
  ("nof_db_events",                   24750),
  ("fsize_local",                     51721617), # 51.72MB, avg file size 25.86MB
  ("fsize_db",                        1843708097), # 1.84GB, avg file size 921.85MB
  ("use_it",                          True),
  ("xsection",                        0.03711),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("has_LHE",                         True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/cms/store/user/kaehatah/NanoProduction_v2_2018May23/WpWpJJ_EWK_QCD_TuneCP5_13TeV_madgraph_pythia8_Fall17/NanoProduction_v2_2018May23_WpWpJJ_EWK_QCD_TuneCP5_13TeV_madgraph_pythia8_Fall17__private/180523_132538"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
  ("missing_from_superset",           [
    # not computed
  ]),
  ("missing_hlt_paths",               [

  ]),
])

