from collections import OrderedDict as OD

# file generated at 2018-05-17 17:20:36 with the following command:
# create_dictionary.py -v -m python/samples/metaDict_2017.py -p /hdfs/local/karl/ttHNtupleProduction/2017/2018May11_fullProduction_v4_woPresel_nom_all_except_forBDTtraining/ntuples -Z zeroes.txt -z zombies.txt -N samples_2017 -E 2017 -g tthAnalyzeSamples_2017.py -o python/samples -M

samples_2017 = OD()
samples_2017["/SingleElectron/Run2017B-17Nov2017-v1/MINIAOD"] = OD([
  ("type",                            "data"),
  ("sample_category",                 "data_obs"),
  ("process_name_specific",           "SingleElectron_Run2017B_17Nov2017_v1"),
  ("nof_files",                       115),
  ("nof_db_files",                    634),
  ("nof_events",                      56501676),
  ("nof_tree_events",                 56501676),
  ("nof_db_events",                   60537490),
  ("fsize_local",                     18205380110), # 18.21GB, avg file size 158.31MB
  ("fsize_db",                        1839129571740), # 1.84TB, avg file size 2.90GB
  ("use_it",                          True),
  ("triggers",                        ['1e']),
  ("reHLT",                           True),
  ("has_LHE",                         False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018May11_fullProduction_v4_woPresel_nom_all_except_forBDTtraining/ntuples/SingleElectron_Run2017B_17Nov2017_v1"),
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
  ("nof_files",                       259),
  ("nof_db_files",                    1705),
  ("nof_events",                      127361546),
  ("nof_tree_events",                 127361546),
  ("nof_db_events",                   136637888),
  ("fsize_local",                     50246461261), # 50.25GB, avg file size 194.00MB
  ("fsize_db",                        4293152220674), # 4.29TB, avg file size 2.52GB
  ("use_it",                          True),
  ("triggers",                        ['1e']),
  ("reHLT",                           True),
  ("has_LHE",                         False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018May11_fullProduction_v4_woPresel_nom_all_except_forBDTtraining/ntuples/SingleElectron_Run2017C_17Nov2017_v1"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
  ("missing_from_superset",           [
    "HLT_IsoMu24_eta2p1_MediumChargedIsoPFTau40_Trk1_TightID_eta2p1_Reg_CrossL1",
    "HLT_IsoMu24_eta2p1_MediumChargedIsoPFTau40_Trk1_eta2p1_Reg_CrossL1",
    "HLT_IsoMu24_eta2p1_TightChargedIsoPFTau40_Trk1_TightID_eta2p1_Reg_CrossL1",
    "HLT_IsoMu24_eta2p1_TightChargedIsoPFTau40_Trk1_eta2p1_Reg_CrossL1",
    "HLT_L1_CDC_SingleMu_3_er1p2_TOP120_DPHI2p618_3p142",
    "HLT_PFMET120_PFMHT120_IDTight_HFCleaned",
    "HLT_PFMET120_PFMHT120_IDTight_PFHT60_HFCleaned",
    "HLT_PFMETNoMu120_PFMHTNoMu120_IDTight_HFCleaned",
    "HLT_PFMETTypeOne120_PFMHT120_IDTight_HFCleaned",
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
  ("nof_files",                       103),
  ("nof_db_files",                    693),
  ("nof_events",                      50610320),
  ("nof_tree_events",                 50610320),
  ("nof_db_events",                   51526710),
  ("fsize_local",                     19497899482), # 19.50GB, avg file size 189.30MB
  ("fsize_db",                        1584079997402), # 1.58TB, avg file size 2.29GB
  ("use_it",                          True),
  ("triggers",                        ['1e']),
  ("reHLT",                           True),
  ("has_LHE",                         False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018May11_fullProduction_v4_woPresel_nom_all_except_forBDTtraining/ntuples/SingleElectron_Run2017D_17Nov2017_v1"),
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
  ("nof_files",                       203),
  ("nof_db_files",                    1280),
  ("nof_events",                      100205122),
  ("nof_tree_events",                 100205122),
  ("nof_db_events",                   102121689),
  ("fsize_local",                     40491089993), # 40.49GB, avg file size 199.46MB
  ("fsize_db",                        3608372444378), # 3.61TB, avg file size 2.82GB
  ("use_it",                          True),
  ("triggers",                        ['1e']),
  ("reHLT",                           True),
  ("has_LHE",                         False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018May11_fullProduction_v4_woPresel_nom_all_except_forBDTtraining/ntuples/SingleElectron_Run2017E_17Nov2017_v1"),
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
  ("nof_files",                       256),
  ("nof_db_files",                    1583),
  ("nof_events",                      126061224),
  ("nof_tree_events",                 126061224),
  ("nof_db_events",                   128467223),
  ("fsize_local",                     52941674875), # 52.94GB, avg file size 206.80MB
  ("fsize_db",                        4628019555901), # 4.63TB, avg file size 2.92GB
  ("use_it",                          True),
  ("triggers",                        ['1e']),
  ("reHLT",                           True),
  ("has_LHE",                         False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018May11_fullProduction_v4_woPresel_nom_all_except_forBDTtraining/ntuples/SingleElectron_Run2017F_17Nov2017_v1"),
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
  ("nof_files",                       268),
  ("nof_db_files",                    1146),
  ("nof_events",                      128496874),
  ("nof_tree_events",                 128496874),
  ("nof_db_events",                   136300266),
  ("fsize_local",                     37803452502), # 37.80GB, avg file size 141.06MB
  ("fsize_db",                        3681903942053), # 3.68TB, avg file size 3.21GB
  ("use_it",                          True),
  ("triggers",                        ['1mu']),
  ("reHLT",                           True),
  ("has_LHE",                         False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018May11_fullProduction_v4_woPresel_nom_all_except_forBDTtraining/ntuples/SingleMuon_Run2017B_17Nov2017_v1"),
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
  ("nof_files",                       313),
  ("nof_db_files",                    1511),
  ("nof_events",                      154633551),
  ("nof_tree_events",                 154633551),
  ("nof_db_events",                   165652756),
  ("fsize_local",                     52845955055), # 52.85GB, avg file size 168.84MB
  ("fsize_db",                        4719988428330), # 4.72TB, avg file size 3.12GB
  ("use_it",                          True),
  ("triggers",                        ['1mu']),
  ("reHLT",                           True),
  ("has_LHE",                         False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018May11_fullProduction_v4_woPresel_nom_all_except_forBDTtraining/ntuples/SingleMuon_Run2017C_17Nov2017_v1"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
  ("missing_from_superset",           [
    "HLT_IsoMu24_eta2p1_MediumChargedIsoPFTau40_Trk1_TightID_eta2p1_Reg_CrossL1",
    "HLT_IsoMu24_eta2p1_MediumChargedIsoPFTau40_Trk1_eta2p1_Reg_CrossL1",
    "HLT_IsoMu24_eta2p1_TightChargedIsoPFTau40_Trk1_TightID_eta2p1_Reg_CrossL1",
    "HLT_IsoMu24_eta2p1_TightChargedIsoPFTau40_Trk1_eta2p1_Reg_CrossL1",
    "HLT_L1_CDC_SingleMu_3_er1p2_TOP120_DPHI2p618_3p142",
    "HLT_PFMET120_PFMHT120_IDTight_HFCleaned",
    "HLT_PFMET120_PFMHT120_IDTight_PFHT60_HFCleaned",
    "HLT_PFMETNoMu120_PFMHTNoMu120_IDTight_HFCleaned",
    "HLT_PFMETTypeOne120_PFMHT120_IDTight_HFCleaned",
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
  ("nof_files",                       140),
  ("nof_db_files",                    823),
  ("nof_events",                      69031074),
  ("nof_tree_events",                 69031074),
  ("nof_db_events",                   70361660),
  ("fsize_local",                     23592057483), # 23.59GB, avg file size 168.51MB
  ("fsize_db",                        2004044655656), # 2.00TB, avg file size 2.44GB
  ("use_it",                          True),
  ("triggers",                        ['1mu']),
  ("reHLT",                           True),
  ("has_LHE",                         False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018May11_fullProduction_v4_woPresel_nom_all_except_forBDTtraining/ntuples/SingleMuon_Run2017D_17Nov2017_v1"),
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
  ("nof_files",                       310),
  ("nof_db_files",                    1669),
  ("nof_events",                      151713898),
  ("nof_tree_events",                 151713898),
  ("nof_db_events",                   154630534),
  ("fsize_local",                     54260985116), # 54.26GB, avg file size 175.04MB
  ("fsize_db",                        5063603395030), # 5.06TB, avg file size 3.03GB
  ("use_it",                          True),
  ("triggers",                        ['1mu']),
  ("reHLT",                           True),
  ("has_LHE",                         False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018May11_fullProduction_v4_woPresel_nom_all_except_forBDTtraining/ntuples/SingleMuon_Run2017E_17Nov2017_v1"),
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
  ("nof_files",                       492),
  ("nof_db_files",                    2737),
  ("nof_events",                      235945383),
  ("nof_tree_events",                 235945383),
  ("nof_db_events",                   242140980),
  ("fsize_local",                     86591606588), # 86.59GB, avg file size 176.00MB
  ("fsize_db",                        8025096282975), # 8.03TB, avg file size 2.93GB
  ("use_it",                          True),
  ("triggers",                        ['1mu']),
  ("reHLT",                           True),
  ("has_LHE",                         False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018May11_fullProduction_v4_woPresel_nom_all_except_forBDTtraining/ntuples/SingleMuon_Run2017F_17Nov2017_v1"),
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
  ("nof_files",                       110),
  ("nof_db_files",                    759),
  ("nof_events",                      54125900),
  ("nof_tree_events",                 54125900),
  ("nof_db_events",                   58088760),
  ("fsize_local",                     20151556570), # 20.15GB, avg file size 183.20MB
  ("fsize_db",                        2000582502159), # 2.00TB, avg file size 2.64GB
  ("use_it",                          True),
  ("triggers",                        ['2e', '3e']),
  ("reHLT",                           True),
  ("has_LHE",                         False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018May11_fullProduction_v4_woPresel_nom_all_except_forBDTtraining/ntuples/DoubleEG_Run2017B_17Nov2017_v1"),
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
  ("nof_files",                       121),
  ("nof_db_files",                    847),
  ("nof_events",                      60063430),
  ("nof_tree_events",                 60063430),
  ("nof_db_events",                   65181125),
  ("fsize_local",                     23429586217), # 23.43GB, avg file size 193.63MB
  ("fsize_db",                        2252815090346), # 2.25TB, avg file size 2.66GB
  ("use_it",                          True),
  ("triggers",                        ['2e', '3e']),
  ("reHLT",                           True),
  ("has_LHE",                         False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018May11_fullProduction_v4_woPresel_nom_all_except_forBDTtraining/ntuples/DoubleEG_Run2017C_17Nov2017_v1"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
  ("missing_from_superset",           [
    "HLT_IsoMu24_eta2p1_MediumChargedIsoPFTau40_Trk1_TightID_eta2p1_Reg_CrossL1",
    "HLT_IsoMu24_eta2p1_MediumChargedIsoPFTau40_Trk1_eta2p1_Reg_CrossL1",
    "HLT_IsoMu24_eta2p1_TightChargedIsoPFTau40_Trk1_TightID_eta2p1_Reg_CrossL1",
    "HLT_IsoMu24_eta2p1_TightChargedIsoPFTau40_Trk1_eta2p1_Reg_CrossL1",
    "HLT_L1_CDC_SingleMu_3_er1p2_TOP120_DPHI2p618_3p142",
    "HLT_PFMET120_PFMHT120_IDTight_HFCleaned",
    "HLT_PFMET120_PFMHT120_IDTight_PFHT60_HFCleaned",
    "HLT_PFMETNoMu120_PFMHTNoMu120_IDTight_HFCleaned",
    "HLT_PFMETTypeOne120_PFMHT120_IDTight_HFCleaned",
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
  ("nof_files",                       51),
  ("nof_db_files",                    344),
  ("nof_events",                      25209987),
  ("nof_tree_events",                 25209987),
  ("nof_db_events",                   25911432),
  ("fsize_local",                     10047496455), # 10.05GB, avg file size 197.01MB
  ("fsize_db",                        881576196022), # 881.58GB, avg file size 2.56GB
  ("use_it",                          True),
  ("triggers",                        ['2e', '3e']),
  ("reHLT",                           True),
  ("has_LHE",                         False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018May11_fullProduction_v4_woPresel_nom_all_except_forBDTtraining/ntuples/DoubleEG_Run2017D_17Nov2017_v1"),
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
  ("nof_files",                       110),
  ("nof_db_files",                    639),
  ("nof_events",                      54624312),
  ("nof_tree_events",                 54624312),
  ("nof_db_events",                   56235775),
  ("fsize_local",                     23230814780), # 23.23GB, avg file size 211.19MB
  ("fsize_db",                        2140362591723), # 2.14TB, avg file size 3.35GB
  ("use_it",                          True),
  ("triggers",                        ['2e', '3e']),
  ("reHLT",                           True),
  ("has_LHE",                         False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018May11_fullProduction_v4_woPresel_nom_all_except_forBDTtraining/ntuples/DoubleEG_Run2017E_17Nov2017_v1"),
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
  ("nof_files",                       146),
  ("nof_db_files",                    1024),
  ("nof_events",                      72431395),
  ("nof_tree_events",                 72431395),
  ("nof_db_events",                   74344288),
  ("fsize_local",                     31987556398), # 31.99GB, avg file size 219.09MB
  ("fsize_db",                        2879805741948), # 2.88TB, avg file size 2.81GB
  ("use_it",                          True),
  ("triggers",                        ['2e', '3e']),
  ("reHLT",                           True),
  ("has_LHE",                         False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018May11_fullProduction_v4_woPresel_nom_all_except_forBDTtraining/ntuples/DoubleEG_Run2017F_17Nov2017_v1"),
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
  ("nof_files",                       27),
  ("nof_db_files",                    164),
  ("nof_events",                      13572040),
  ("nof_tree_events",                 13572040),
  ("nof_db_events",                   14501767),
  ("fsize_local",                     4724207403), # 4.72GB, avg file size 174.97MB
  ("fsize_db",                        429564397133), # 429.56GB, avg file size 2.62GB
  ("use_it",                          True),
  ("triggers",                        ['2mu', '3mu']),
  ("reHLT",                           True),
  ("has_LHE",                         False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018May11_fullProduction_v4_woPresel_nom_all_except_forBDTtraining/ntuples/DoubleMuon_Run2017B_17Nov2017_v1"),
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
  ("nof_files",                       92),
  ("nof_db_files",                    466),
  ("nof_events",                      46273101),
  ("nof_tree_events",                 46273101),
  ("nof_db_events",                   49636525),
  ("fsize_local",                     17852405898), # 17.85GB, avg file size 194.05MB
  ("fsize_db",                        1506932771681), # 1.51TB, avg file size 3.23GB
  ("use_it",                          True),
  ("triggers",                        ['2mu', '3mu']),
  ("reHLT",                           True),
  ("has_LHE",                         False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018May11_fullProduction_v4_woPresel_nom_all_except_forBDTtraining/ntuples/DoubleMuon_Run2017C_17Nov2017_v1"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
  ("missing_from_superset",           [
    "HLT_IsoMu24_eta2p1_MediumChargedIsoPFTau40_Trk1_TightID_eta2p1_Reg_CrossL1",
    "HLT_IsoMu24_eta2p1_MediumChargedIsoPFTau40_Trk1_eta2p1_Reg_CrossL1",
    "HLT_IsoMu24_eta2p1_TightChargedIsoPFTau40_Trk1_TightID_eta2p1_Reg_CrossL1",
    "HLT_IsoMu24_eta2p1_TightChargedIsoPFTau40_Trk1_eta2p1_Reg_CrossL1",
    "HLT_L1_CDC_SingleMu_3_er1p2_TOP120_DPHI2p618_3p142",
    "HLT_PFMET120_PFMHT120_IDTight_HFCleaned",
    "HLT_PFMET120_PFMHT120_IDTight_PFHT60_HFCleaned",
    "HLT_PFMETNoMu120_PFMHTNoMu120_IDTight_HFCleaned",
    "HLT_PFMETTypeOne120_PFMHT120_IDTight_HFCleaned",
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
  ("nof_files",                       45),
  ("nof_db_files",                    242),
  ("nof_events",                      22646081),
  ("nof_tree_events",                 22646081),
  ("nof_db_events",                   23075733),
  ("fsize_local",                     8766350368), # 8.77GB, avg file size 194.81MB
  ("fsize_db",                        700300808389), # 700.30GB, avg file size 2.89GB
  ("use_it",                          True),
  ("triggers",                        ['2mu', '3mu']),
  ("reHLT",                           True),
  ("has_LHE",                         False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018May11_fullProduction_v4_woPresel_nom_all_except_forBDTtraining/ntuples/DoubleMuon_Run2017D_17Nov2017_v1"),
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
  ("nof_files",                       101),
  ("nof_db_files",                    596),
  ("nof_events",                      50596536),
  ("nof_tree_events",                 50596536),
  ("nof_db_events",                   51589091),
  ("fsize_local",                     20397705416), # 20.40GB, avg file size 201.96MB
  ("fsize_db",                        1822288632364), # 1.82TB, avg file size 3.06GB
  ("use_it",                          True),
  ("triggers",                        ['2mu', '3mu']),
  ("reHLT",                           True),
  ("has_LHE",                         False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018May11_fullProduction_v4_woPresel_nom_all_except_forBDTtraining/ntuples/DoubleMuon_Run2017E_17Nov2017_v1"),
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
  ("nof_files",                       151),
  ("nof_db_files",                    875),
  ("nof_events",                      75301738),
  ("nof_tree_events",                 75301738),
  ("nof_db_events",                   79756560),
  ("fsize_local",                     30746634148), # 30.75GB, avg file size 203.62MB
  ("fsize_db",                        2792396630929), # 2.79TB, avg file size 3.19GB
  ("use_it",                          True),
  ("triggers",                        ['2mu', '3mu']),
  ("reHLT",                           True),
  ("has_LHE",                         False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018May11_fullProduction_v4_woPresel_nom_all_except_forBDTtraining/ntuples/DoubleMuon_Run2017F_17Nov2017_v1"),
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
  ("nof_files",                       9),
  ("nof_db_files",                    70),
  ("nof_events",                      4153318),
  ("nof_tree_events",                 4153318),
  ("nof_db_events",                   4453465),
  ("fsize_local",                     1869874958), # 1.87GB, avg file size 207.76MB
  ("fsize_db",                        151955610304), # 151.96GB, avg file size 2.17GB
  ("use_it",                          True),
  ("triggers",                        ['1e1mu', '2e1mu', '1e2mu']),
  ("reHLT",                           True),
  ("has_LHE",                         False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018May11_fullProduction_v4_woPresel_nom_all_except_forBDTtraining/ntuples/MuonEG_Run2017B_17Nov2017_v1"),
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
  ("nof_files",                       29),
  ("nof_db_files",                    219),
  ("nof_events",                      14579589),
  ("nof_tree_events",                 14579589),
  ("nof_db_events",                   15595214),
  ("fsize_local",                     7390442413), # 7.39GB, avg file size 254.84MB
  ("fsize_db",                        548775705076), # 548.78GB, avg file size 2.51GB
  ("use_it",                          True),
  ("triggers",                        ['1e1mu', '2e1mu', '1e2mu']),
  ("reHLT",                           True),
  ("has_LHE",                         False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018May11_fullProduction_v4_woPresel_nom_all_except_forBDTtraining/ntuples/MuonEG_Run2017C_17Nov2017_v1"),
        ("selection", "*"),
        ("blacklist", []),
      ]),
    ]
  ),
  ("missing_from_superset",           [
    "HLT_IsoMu24_eta2p1_MediumChargedIsoPFTau40_Trk1_TightID_eta2p1_Reg_CrossL1",
    "HLT_IsoMu24_eta2p1_MediumChargedIsoPFTau40_Trk1_eta2p1_Reg_CrossL1",
    "HLT_IsoMu24_eta2p1_TightChargedIsoPFTau40_Trk1_TightID_eta2p1_Reg_CrossL1",
    "HLT_IsoMu24_eta2p1_TightChargedIsoPFTau40_Trk1_eta2p1_Reg_CrossL1",
    "HLT_L1_CDC_SingleMu_3_er1p2_TOP120_DPHI2p618_3p142",
    "HLT_PFMET120_PFMHT120_IDTight_HFCleaned",
    "HLT_PFMET120_PFMHT120_IDTight_PFHT60_HFCleaned",
    "HLT_PFMETNoMu120_PFMHTNoMu120_IDTight_HFCleaned",
    "HLT_PFMETTypeOne120_PFMHT120_IDTight_HFCleaned",
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
    "HLT_ZeroBias_part0",
    "HLT_ZeroBias_part1",
    "HLT_ZeroBias_part2",
    "HLT_ZeroBias_part3",
    "HLT_ZeroBias_part4",
    "HLT_ZeroBias_part5",
    "HLT_ZeroBias_part6",
    "HLT_ZeroBias_part7",
  ]),
  ("missing_hlt_paths",               [

  ]),
])

samples_2017["/MuonEG/Run2017D-17Nov2017-v1/MINIAOD"] = OD([
  ("type",                            "data"),
  ("sample_category",                 "data_obs"),
  ("process_name_specific",           "MuonEG_Run2017D_17Nov2017_v1"),
  ("nof_files",                       18),
  ("nof_db_files",                    126),
  ("nof_events",                      9012928),
  ("nof_tree_events",                 9012928),
  ("nof_db_events",                   9164365),
  ("fsize_local",                     4503506528), # 4.50GB, avg file size 250.19MB
  ("fsize_db",                        321530133689), # 321.53GB, avg file size 2.55GB
  ("use_it",                          True),
  ("triggers",                        ['1e1mu', '2e1mu', '1e2mu']),
  ("reHLT",                           True),
  ("has_LHE",                         False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018May11_fullProduction_v4_woPresel_nom_all_except_forBDTtraining/ntuples/MuonEG_Run2017D_17Nov2017_v1"),
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
  ("nof_files",                       37),
  ("nof_db_files",                    239),
  ("nof_events",                      18703362),
  ("nof_tree_events",                 18703362),
  ("nof_db_events",                   19043421),
  ("fsize_local",                     9696684879), # 9.70GB, avg file size 262.07MB
  ("fsize_db",                        753395415338), # 753.40GB, avg file size 3.15GB
  ("use_it",                          True),
  ("triggers",                        ['1e1mu', '2e1mu', '1e2mu']),
  ("reHLT",                           True),
  ("has_LHE",                         False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018May11_fullProduction_v4_woPresel_nom_all_except_forBDTtraining/ntuples/MuonEG_Run2017E_17Nov2017_v1"),
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
  ("nof_files",                       51),
  ("nof_db_files",                    362),
  ("nof_events",                      25342514),
  ("nof_tree_events",                 25342514),
  ("nof_db_events",                   25776363),
  ("fsize_local",                     13419570989), # 13.42GB, avg file size 263.13MB
  ("fsize_db",                        1031887580033), # 1.03TB, avg file size 2.85GB
  ("use_it",                          True),
  ("triggers",                        ['1e1mu', '2e1mu', '1e2mu']),
  ("reHLT",                           True),
  ("has_LHE",                         False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018May11_fullProduction_v4_woPresel_nom_all_except_forBDTtraining/ntuples/MuonEG_Run2017F_17Nov2017_v1"),
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
  ("nof_files",                       20),
  ("nof_db_files",                    283),
  ("nof_events",                      3322118),
  ("nof_tree_events",                 9650032),
  ("nof_db_events",                   9650032),
  ("fsize_local",                     28734723415), # 28.73GB, avg file size 1.44GB
  ("fsize_db",                        603282930374), # 603.28GB, avg file size 2.13GB
  ("use_it",                          True),
  ("xsection",                        0.2118),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("reHLT",                           True),
  ("has_LHE",                         True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018May11_fullProduction_v4_woPresel_nom_all_except_forBDTtraining/ntuples/ttHJetToNonbb_M125_amcatnlo"),
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
  ("nof_files",                       2),
  ("nof_db_files",                    47),
  ("nof_events",                      924563),
  ("nof_tree_events",                 934244),
  ("nof_db_events",                   934244),
  ("fsize_local",                     1323351850), # 1.32GB, avg file size 661.68MB
  ("fsize_db",                        42622664498), # 42.62GB, avg file size 906.87MB
  ("use_it",                          True),
  ("xsection",                        0.01212),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("reHLT",                           True),
  ("has_LHE",                         True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018May11_fullProduction_v4_woPresel_nom_all_except_forBDTtraining/ntuples/GluGluHToZZTo4L"),
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
  ("nof_files",                       16),
  ("nof_db_files",                    199),
  ("nof_events",                      3570767),
  ("nof_tree_events",                 7563490),
  ("nof_db_events",                   7563490),
  ("fsize_local",                     19770523990), # 19.77GB, avg file size 1.24GB
  ("fsize_db",                        444833969271), # 444.83GB, avg file size 2.24GB
  ("use_it",                          True),
  ("xsection",                        0.2529),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("reHLT",                           True),
  ("has_LHE",                         True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018May11_fullProduction_v4_woPresel_nom_all_except_forBDTtraining/ntuples/TTZToLL_M10"),
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
  ("nof_files",                       1),
  ("nof_db_files",                    17),
  ("nof_events",                      131167),
  ("nof_tree_events",                 250000),
  ("nof_db_events",                   250000),
  ("fsize_local",                     630492713), # 630.49MB, avg file size 630.49MB
  ("fsize_db",                        14727460148), # 14.73GB, avg file size 866.32MB
  ("use_it",                          True),
  ("xsection",                        0.0493),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("reHLT",                           True),
  ("has_LHE",                         True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018May11_fullProduction_v4_woPresel_nom_all_except_forBDTtraining/ntuples/TTZToLL_M-1to10"),
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
  ("nof_files",                       10),
  ("nof_db_files",                    109),
  ("nof_events",                      5353337),
  ("nof_tree_events",                 4925829),
  ("nof_db_events",                   4925829),
  ("fsize_local",                     13176656133), # 13.18GB, avg file size 1.32GB
  ("fsize_db",                        292280765632), # 292.28GB, avg file size 2.68GB
  ("use_it",                          True),
  ("xsection",                        0.2043),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("reHLT",                           True),
  ("has_LHE",                         True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018May11_fullProduction_v4_woPresel_nom_all_except_forBDTtraining/ntuples/TTWJetsToLNu"),
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
  ("nof_files",                       10),
  ("nof_db_files",                    122),
  ("nof_events",                      5353337),
  ("nof_tree_events",                 4889942),
  ("nof_db_events",                   4889942),
  ("fsize_local",                     13061840333), # 13.06GB, avg file size 1.31GB
  ("fsize_db",                        290787551975), # 290.79GB, avg file size 2.38GB
  ("use_it",                          True),
  ("xsection",                        0.2043),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("reHLT",                           True),
  ("has_LHE",                         True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018May11_fullProduction_v4_woPresel_nom_all_except_forBDTtraining/ntuples/TTWJetsToLNu_PSweights"),
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
  ("nof_files",                       1),
  ("nof_db_files",                    11),
  ("nof_events",                      199022),
  ("nof_tree_events",                 200000),
  ("nof_db_events",                   200000),
  ("fsize_local",                     601996097), # 602.00MB, avg file size 602.00MB
  ("fsize_db",                        13111885203), # 13.11GB, avg file size 1.19GB
  ("use_it",                          True),
  ("xsection",                        0.007834),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("reHLT",                           True),
  ("has_LHE",                         True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018May11_fullProduction_v4_woPresel_nom_all_except_forBDTtraining/ntuples/TTWW"),
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
  ("nof_files",                       20),
  ("nof_db_files",                    217),
  ("nof_events",                      5912001),
  ("nof_tree_events",                 9472619),
  ("nof_db_events",                   9472619),
  ("fsize_local",                     15260647441), # 15.26GB, avg file size 763.03MB
  ("fsize_db",                        423862017407), # 423.86GB, avg file size 1.95GB
  ("use_it",                          True),
  ("xsection",                        3.36),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("reHLT",                           True),
  ("has_LHE",                         True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018May11_fullProduction_v4_woPresel_nom_all_except_forBDTtraining/ntuples/ST_s-channel_4f_leptonDecays"),
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
  ("nof_files",                       8),
  ("nof_db_files",                    116),
  ("nof_events",                      3891397),
  ("nof_tree_events",                 3891190),
  ("nof_db_events",                   3891190),
  ("fsize_local",                     6309455144), # 6.31GB, avg file size 788.68MB
  ("fsize_db",                        177784436788), # 177.78GB, avg file size 1.53GB
  ("use_it",                          True),
  ("xsection",                        80.95),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("reHLT",                           True),
  ("has_LHE",                         True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018May11_fullProduction_v4_woPresel_nom_all_except_forBDTtraining/ntuples/ST_t-channel_antitop_4f_inclusiveDecays"),
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
  ("nof_files",                       13),
  ("nof_db_files",                    186),
  ("nof_events",                      5841537),
  ("nof_tree_events",                 5841455),
  ("nof_db_events",                   5841455),
  ("fsize_local",                     9486362616), # 9.49GB, avg file size 729.72MB
  ("fsize_db",                        268058212482), # 268.06GB, avg file size 1.44GB
  ("use_it",                          True),
  ("xsection",                        136.02),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("reHLT",                           True),
  ("has_LHE",                         True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018May11_fullProduction_v4_woPresel_nom_all_except_forBDTtraining/ntuples/ST_t-channel_top_4f_inclusiveDecays"),
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
  ("nof_files",                       16),
  ("nof_db_files",                    155),
  ("nof_events",                      7696889),
  ("nof_tree_events",                 7756300),
  ("nof_db_events",                   7756300),
  ("fsize_local",                     14289757379), # 14.29GB, avg file size 893.11MB
  ("fsize_db",                        386122494678), # 386.12GB, avg file size 2.49GB
  ("use_it",                          True),
  ("xsection",                        35.85),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("reHLT",                           True),
  ("has_LHE",                         True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018May11_fullProduction_v4_woPresel_nom_all_except_forBDTtraining/ntuples/ST_tW_antitop_5f_inclusiveDecays"),
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
  ("nof_files",                       16),
  ("nof_db_files",                    183),
  ("nof_events",                      7499912),
  ("nof_tree_events",                 7558006),
  ("nof_db_events",                   7558006),
  ("fsize_local",                     13920622375), # 13.92GB, avg file size 870.04MB
  ("fsize_db",                        376466493438), # 376.47GB, avg file size 2.06GB
  ("use_it",                          True),
  ("xsection",                        35.85),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("reHLT",                           True),
  ("has_LHE",                         True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018May11_fullProduction_v4_woPresel_nom_all_except_forBDTtraining/ntuples/ST_tW_top_5f_inclusiveDecays"),
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
  ("nof_files",                       18),
  ("nof_db_files",                    164),
  ("nof_events",                      8634689),
  ("nof_tree_events",                 8705576),
  ("nof_db_events",                   8705576),
  ("fsize_local",                     17520166658), # 17.52GB, avg file size 973.34MB
  ("fsize_db",                        451436194017), # 451.44GB, avg file size 2.75GB
  ("use_it",                          True),
  ("xsection",                        88.29),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("reHLT",                           True),
  ("has_LHE",                         True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018May11_fullProduction_v4_woPresel_nom_all_except_forBDTtraining/ntuples/TTTo2L2Nu"),
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
  ("nof_files",                       84),
  ("nof_db_files",                    743),
  ("nof_events",                      40828357),
  ("nof_tree_events",                 41161951),
  ("nof_db_events",                   41161951),
  ("fsize_local",                     87479769894), # 87.48GB, avg file size 1.04GB
  ("fsize_db",                        2166068169129), # 2.17TB, avg file size 2.92GB
  ("use_it",                          True),
  ("xsection",                        365.34),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("reHLT",                           True),
  ("has_LHE",                         True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018May11_fullProduction_v4_woPresel_nom_all_except_forBDTtraining/ntuples/TTToSemiLeptonic"),
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
  ("nof_files",                       86),
  ("nof_db_files",                    765),
  ("nof_events",                      42678039),
  ("nof_tree_events",                 42678688),
  ("nof_db_events",                   42678688),
  ("fsize_local",                     88955111648), # 88.96GB, avg file size 1.03GB
  ("fsize_db",                        2292321642457), # 2.29TB, avg file size 3.00GB
  ("use_it",                          True),
  ("xsection",                        377.96),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("reHLT",                           True),
  ("has_LHE",                         True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018May11_fullProduction_v4_woPresel_nom_all_except_forBDTtraining/ntuples/TTToHadronic"),
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
  ("nof_files",                       79),
  ("nof_db_files",                    508),
  ("nof_events",                      38801086),
  ("nof_tree_events",                 38832197),
  ("nof_db_events",                   38832197),
  ("fsize_local",                     23954732301), # 23.95GB, avg file size 303.22MB
  ("fsize_db",                        1343136870100), # 1.34TB, avg file size 2.64GB
  ("use_it",                          True),
  ("xsection",                        18610.0),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("reHLT",                           True),
  ("has_LHE",                         True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018May11_fullProduction_v4_woPresel_nom_all_except_forBDTtraining/ntuples/DYJetsToLL_M-10to50"),
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
  ("nof_files",                       55),
  ("nof_db_files",                    372),
  ("nof_events",                      144293006),
  ("nof_tree_events",                 26923935),
  ("nof_db_events",                   26923935),
  ("fsize_local",                     26893824124), # 26.89GB, avg file size 488.98MB
  ("fsize_db",                        1065736102325), # 1.07TB, avg file size 2.86GB
  ("use_it",                          True),
  ("xsection",                        5765.4),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("reHLT",                           True),
  ("has_LHE",                         True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018May11_fullProduction_v4_woPresel_nom_all_except_forBDTtraining/ntuples/DYJetsToLL_M-50"),
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
  ("nof_files",                       376),
  ("nof_db_files",                    2752),
  ("nof_events",                      144293006),
  ("nof_tree_events",                 185998625),
  ("nof_db_events",                   185998625),
  ("fsize_local",                     185693553424), # 185.69GB, avg file size 493.87MB
  ("fsize_db",                        7376341087077), # 7.38TB, avg file size 2.68GB
  ("use_it",                          True),
  ("xsection",                        5765.4),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("reHLT",                           True),
  ("has_LHE",                         True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018May11_fullProduction_v4_woPresel_nom_all_except_forBDTtraining/ntuples/DYJetsToLL_M-50_ext1"),
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
  ("nof_files",                       48),
  ("nof_db_files",                    382),
  ("nof_events",                      23221088),
  ("nof_tree_events",                 23240598),
  ("nof_db_events",                   23240598),
  ("fsize_local",                     18308823728), # 18.31GB, avg file size 381.43MB
  ("fsize_db",                        882645881655), # 882.65GB, avg file size 2.31GB
  ("use_it",                          True),
  ("xsection",                        61526.7),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("reHLT",                           True),
  ("has_LHE",                         True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018May11_fullProduction_v4_woPresel_nom_all_except_forBDTtraining/ntuples/WJetsToLNu"),
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
  ("nof_files",                       4),
  ("nof_db_files",                    50),
  ("nof_events",                      1811894),
  ("nof_tree_events",                 1818828),
  ("nof_db_events",                   1818828),
  ("fsize_local",                     2137019698), # 2.14GB, avg file size 534.25MB
  ("fsize_db",                        75643188117), # 75.64GB, avg file size 1.51GB
  ("use_it",                          True),
  ("xsection",                        12.178),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("reHLT",                           True),
  ("has_LHE",                         True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018May11_fullProduction_v4_woPresel_nom_all_except_forBDTtraining/ntuples/WWTo2L2Nu"),
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
  ("nof_files",                       22),
  ("nof_db_files",                    212),
  ("nof_events",                      6738664),
  ("nof_tree_events",                 10751052),
  ("nof_db_events",                   10751052),
  ("fsize_local",                     13251399603), # 13.25GB, avg file size 602.34MB
  ("fsize_db",                        452807583489), # 452.81GB, avg file size 2.14GB
  ("use_it",                          True),
  ("xsection",                        4.42965),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("reHLT",                           True),
  ("has_LHE",                         True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018May11_fullProduction_v4_woPresel_nom_all_except_forBDTtraining/ntuples/WZTo3LNu"),
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
  ("nof_files",                       15),
  ("nof_db_files",                    204),
  ("nof_events",                      101642344),
  ("nof_tree_events",                 6960289),
  ("nof_db_events",                   6960289),
  ("fsize_local",                     7653811233), # 7.65GB, avg file size 510.25MB
  ("fsize_db",                        322020515003), # 322.02GB, avg file size 1.58GB
  ("use_it",                          True),
  ("xsection",                        1.256),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("reHLT",                           True),
  ("has_LHE",                         True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018May11_fullProduction_v4_woPresel_nom_all_except_forBDTtraining/ntuples/ZZTo4L"),
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
  ("nof_files",                       193),
  ("nof_db_files",                    1490),
  ("nof_events",                      101642344),
  ("nof_tree_events",                 95716759),
  ("nof_db_events",                   95716759),
  ("fsize_local",                     105191040929), # 105.19GB, avg file size 545.03MB
  ("fsize_db",                        3881682466950), # 3.88TB, avg file size 2.61GB
  ("use_it",                          True),
  ("xsection",                        1.256),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("reHLT",                           True),
  ("has_LHE",                         True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018May11_fullProduction_v4_woPresel_nom_all_except_forBDTtraining/ntuples/ZZTo4L_ext1"),
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
  ("nof_files",                       10),
  ("nof_db_files",                    138),
  ("nof_events",                      1803859),
  ("nof_tree_events",                 4647278),
  ("nof_db_events",                   4647278),
  ("fsize_local",                     11596850926), # 11.60GB, avg file size 1.16GB
  ("fsize_db",                        269969335093), # 269.97GB, avg file size 1.96GB
  ("use_it",                          True),
  ("xsection",                        3.697),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("reHLT",                           True),
  ("has_LHE",                         True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018May11_fullProduction_v4_woPresel_nom_all_except_forBDTtraining/ntuples/TTGJets"),
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
  ("nof_files",                       3),
  ("nof_db_files",                    29),
  ("nof_events",                      372249),
  ("nof_tree_events",                 993804),
  ("nof_db_events",                   993804),
  ("fsize_local",                     3883052452), # 3.88GB, avg file size 1.29GB
  ("fsize_db",                        77438656415), # 77.44GB, avg file size 2.67GB
  ("use_it",                          True),
  ("xsection",                        0.008213),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("reHLT",                           True),
  ("has_LHE",                         True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018May11_fullProduction_v4_woPresel_nom_all_except_forBDTtraining/ntuples/TTTT"),
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
  ("nof_files",                       27),
  ("nof_db_files",                    292),
  ("nof_events",                      3453358),
  ("nof_tree_events",                 13220024),
  ("nof_db_events",                   13220024),
  ("fsize_local",                     30669150666), # 30.67GB, avg file size 1.14GB
  ("fsize_db",                        723683119488), # 723.68GB, avg file size 2.48GB
  ("use_it",                          True),
  ("xsection",                        0.0758),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("reHLT",                           True),
  ("has_LHE",                         True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018May11_fullProduction_v4_woPresel_nom_all_except_forBDTtraining/ntuples/tZq_ll_4f"),
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
  ("nof_files",                       3),
  ("nof_db_files",                    23),
  ("nof_events",                      999937),
  ("nof_tree_events",                 1000000),
  ("nof_db_events",                   1000000),
  ("fsize_local",                     885607143), # 885.61MB, avg file size 295.20MB
  ("fsize_db",                        42876536279), # 42.88GB, avg file size 1.86GB
  ("use_it",                          True),
  ("xsection",                        0.1743),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("reHLT",                           True),
  ("has_LHE",                         False),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018May11_fullProduction_v4_woPresel_nom_all_except_forBDTtraining/ntuples/WWTo2L2Nu_DoubleScattering"),
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
  ("nof_files",                       1),
  ("nof_db_files",                    21),
  ("nof_events",                      210461),
  ("nof_tree_events",                 240000),
  ("nof_db_events",                   240000),
  ("fsize_local",                     418288632), # 418.29MB, avg file size 418.29MB
  ("fsize_db",                        11711799646), # 11.71GB, avg file size 557.70MB
  ("use_it",                          True),
  ("xsection",                        0.2086),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("reHLT",                           True),
  ("has_LHE",                         True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018May11_fullProduction_v4_woPresel_nom_all_except_forBDTtraining/ntuples/WWW_4F"),
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
  ("nof_files",                       1),
  ("nof_db_files",                    14),
  ("nof_events",                      221593),
  ("nof_tree_events",                 250000),
  ("nof_db_events",                   250000),
  ("fsize_local",                     480304750), # 480.30MB, avg file size 480.30MB
  ("fsize_db",                        13268139304), # 13.27GB, avg file size 947.72MB
  ("use_it",                          True),
  ("xsection",                        0.1651),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("reHLT",                           True),
  ("has_LHE",                         True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018May11_fullProduction_v4_woPresel_nom_all_except_forBDTtraining/ntuples/WWZ_4F"),
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
  ("nof_files",                       1),
  ("nof_db_files",                    18),
  ("nof_events",                      219645),
  ("nof_tree_events",                 250000),
  ("nof_db_events",                   250000),
  ("fsize_local",                     464034468), # 464.03MB, avg file size 464.03MB
  ("fsize_db",                        12226507693), # 12.23GB, avg file size 679.25MB
  ("use_it",                          True),
  ("xsection",                        0.05565),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("reHLT",                           True),
  ("has_LHE",                         True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018May11_fullProduction_v4_woPresel_nom_all_except_forBDTtraining/ntuples/WZZ"),
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
  ("nof_files",                       1),
  ("nof_db_files",                    17),
  ("nof_events",                      213543),
  ("nof_tree_events",                 250000),
  ("nof_db_events",                   250000),
  ("fsize_local",                     416211124), # 416.21MB, avg file size 416.21MB
  ("fsize_db",                        11782250391), # 11.78GB, avg file size 693.07MB
  ("use_it",                          True),
  ("xsection",                        0.01398),
  ("genWeight",                       True),
  ("triggers",                        ['1e', '1mu', '2e', '2mu', '1e1mu', '3e', '3mu', '2e1mu', '1e2mu', '1e1tau', '1mu1tau', '2tau']),
  ("reHLT",                           True),
  ("has_LHE",                         True),
  ("local_paths",
    [
      OD([
        ("path",      "/hdfs/local/karl/ttHNtupleProduction/2017/2018May11_fullProduction_v4_woPresel_nom_all_except_forBDTtraining/ntuples/ZZZ"),
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

