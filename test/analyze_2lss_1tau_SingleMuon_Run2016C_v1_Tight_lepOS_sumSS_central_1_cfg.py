import FWCore.ParameterSet.Config as cms

import os
  
process = cms.PSet()
  
process.fwliteInput = cms.PSet(
    fileNames = cms.vstring('/hdfs/local/lucia/VHBBHeppyV24bis/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/VHBB_HEPPY_V24bis_ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_Py8_mWCutfix__spr16MAv2-puspr16_HLT_80r2as_v14_ext1-v1/160911_223711/0000/tree_1.root'),
    maxEvents = cms.int32(-1),
    outputEvery = cms.uint32(100000)
)

process.fwliteOutput = cms.PSet(
    fileName = cms.string('analyze_2lss_1tau.root')
)

process.analyze_2lss_1tau = cms.PSet(
    treeName = cms.string('tree'),

    process = cms.string('ttH'),

    histogramDir = cms.string('2lss_1tau_lepSS_sumOS_Tight'),

    era = cms.string('2016'),

    triggers_1e = cms.vstring('HLT_BIT_HLT_Ele25_WPTight_Gsf_v', 'HLT_BIT_HLT_Ele27_eta2p1_WPLoose_Gsf_v'),
    use_triggers_1e = cms.bool(True),
    triggers_2e = cms.vstring('HLT_BIT_HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v'),
    use_triggers_2e = cms.bool(True),
    triggers_1mu = cms.vstring('HLT_BIT_HLT_IsoMu22_v', 'HLT_BIT_HLT_IsoTkMu22_v'),
    use_triggers_1mu = cms.bool(True),
    triggers_2mu = cms.vstring('HLT_BIT_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v', 'HLT_BIT_HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v'),
    use_triggers_2mu = cms.bool(True),
    triggers_1e1mu = cms.vstring('HLT_BIT_HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v', 'HLT_BIT_HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v'),
    use_triggers_1e1mu = cms.bool(True),
    
    apply_offline_e_trigger_cuts_1e = cms.bool(True),
    apply_offline_e_trigger_cuts_2e = cms.bool(True),
    apply_offline_e_trigger_cuts_1mu = cms.bool(True),
    apply_offline_e_trigger_cuts_2mu = cms.bool(True),
    apply_offline_e_trigger_cuts_1e1mu = cms.bool(True),

    leptonSelection = cms.string('Tight'),
    apply_leptonGenMatching = cms.bool(True),
    apply_leptonGenMatching_ttZ_workaround = cms.bool(False),
    leptonChargeSelection = cms.string('SS'),

    hadTauSelection = cms.string('Tight|dR03mvaMedium'),
    apply_hadTauGenMatching = cms.bool(True),

    chargeSumSelection = cms.string('OS'),

    applyFakeRateWeights = cms.string("disabled"), # either "disabled", "3L" or "2tau"
    leptonFakeRateWeight = cms.PSet(
        inputFileName = cms.string("tthAnalysis/HiggsToTauTau/data/FR_lep_ttH_mva_2016_data.root"),
        histogramName_e = cms.string("FR_mva075_el_data_comb"),
        histogramName_mu = cms.string("FR_mva075_mu_data_comb")
    ),
    hadTauFakeRateWeight = cms.PSet(
        inputFileName = cms.string("tthAnalysis/HiggsToTauTau/data/FR_tau_2016.root"),
        lead = cms.PSet(
            absEtaBins = cms.vdouble(-1., 1.479, 9.9),
            graphName = cms.string("jetToTauFakeRate/$hadTauSelection/$etaBin/jetToTauFakeRate_mc_hadTaus_pt"),
            applyGraph = cms.bool(True),
            fitFunctionName = cms.string("jetToTauFakeRate/$hadTauSelection/$etaBin/fitFunction_data_div_mc_hadTaus_pt"),
            applyFitFunction = cms.bool(True)
        )
    ),
    
    use_HIP_mitigation_bTag = cms.bool(False),
    use_HIP_mitigation_mediumMuonId = cms.bool(False),

    apply_lepton_and_hadTauCharge_cut = cms.bool(True),

    isMC = cms.bool(True),
    central_or_shift = cms.string('central'),
    lumiScale = cms.double(1.),
    apply_genWeight = cms.bool(True),
    apply_trigger_bits = cms.bool(False),
    apply_hadTauFakeRateSF = cms.bool(False),

    fillGenEvtHistograms = cms.bool(False),

    branchName_electrons = cms.string('selLeptons'),
    branchName_muons = cms.string('selLeptons'),
    branchName_hadTaus = cms.string('TauGood'),
    branchName_jets = cms.string('Jet'),
    branchName_met = cms.string('met'),
    ##branchName_memOutput = cms.string('memObjects_2lss_1tau'),
    branchName_memOutput = cms.string(''),

    branchName_genLeptons1 = cms.string('GenLep'),
    branchName_genLeptons2 = cms.string('GenLepFromTau'),
    branchName_genHadTaus = cms.string('GenHadTaus'),
    branchName_genJets = cms.string('GenJet'),
    
    selEventsFileName_input = cms.string(''),
    selEventsFileName_output = cms.string('selEvents_analyze_2lss_1tau.txt'),
    selectBDT = cms.bool(False),
)

process.fwliteInput.fileNames = cms.vstring(['/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v3/SingleMuon/VHBB_HEPPY_V25tthtautau_v3_SingleMuon__Run2016C-23Sep2016-v1/170221_173556/0000/tree_1.root', '/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v3/SingleMuon/VHBB_HEPPY_V25tthtautau_v3_SingleMuon__Run2016C-23Sep2016-v1/170221_173556/0000/tree_2.root', '/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v3/SingleMuon/VHBB_HEPPY_V25tthtautau_v3_SingleMuon__Run2016C-23Sep2016-v1/170221_173556/0000/tree_3.root', '/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v3/SingleMuon/VHBB_HEPPY_V25tthtautau_v3_SingleMuon__Run2016C-23Sep2016-v1/170221_173556/0000/tree_4.root', '/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v3/SingleMuon/VHBB_HEPPY_V25tthtautau_v3_SingleMuon__Run2016C-23Sep2016-v1/170221_173556/0000/tree_5.root', '/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v3/SingleMuon/VHBB_HEPPY_V25tthtautau_v3_SingleMuon__Run2016C-23Sep2016-v1/170221_173556/0000/tree_6.root', '/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v3/SingleMuon/VHBB_HEPPY_V25tthtautau_v3_SingleMuon__Run2016C-23Sep2016-v1/170221_173556/0000/tree_7.root', '/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v3/SingleMuon/VHBB_HEPPY_V25tthtautau_v3_SingleMuon__Run2016C-23Sep2016-v1/170221_173556/0000/tree_8.root', '/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v3/SingleMuon/VHBB_HEPPY_V25tthtautau_v3_SingleMuon__Run2016C-23Sep2016-v1/170221_173556/0000/tree_9.root', '/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v3/SingleMuon/VHBB_HEPPY_V25tthtautau_v3_SingleMuon__Run2016C-23Sep2016-v1/170221_173556/0000/tree_10.root', '/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v3/SingleMuon/VHBB_HEPPY_V25tthtautau_v3_SingleMuon__Run2016C-23Sep2016-v1/170221_173556/0000/tree_11.root', '/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v3/SingleMuon/VHBB_HEPPY_V25tthtautau_v3_SingleMuon__Run2016C-23Sep2016-v1/170221_173556/0000/tree_12.root', '/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v3/SingleMuon/VHBB_HEPPY_V25tthtautau_v3_SingleMuon__Run2016C-23Sep2016-v1/170221_173556/0000/tree_13.root', '/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v3/SingleMuon/VHBB_HEPPY_V25tthtautau_v3_SingleMuon__Run2016C-23Sep2016-v1/170221_173556/0000/tree_14.root', '/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v3/SingleMuon/VHBB_HEPPY_V25tthtautau_v3_SingleMuon__Run2016C-23Sep2016-v1/170221_173556/0000/tree_15.root', '/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v3/SingleMuon/VHBB_HEPPY_V25tthtautau_v3_SingleMuon__Run2016C-23Sep2016-v1/170221_173556/0000/tree_16.root', '/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v3/SingleMuon/VHBB_HEPPY_V25tthtautau_v3_SingleMuon__Run2016C-23Sep2016-v1/170221_173556/0000/tree_17.root', '/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v3/SingleMuon/VHBB_HEPPY_V25tthtautau_v3_SingleMuon__Run2016C-23Sep2016-v1/170221_173556/0000/tree_18.root', '/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v3/SingleMuon/VHBB_HEPPY_V25tthtautau_v3_SingleMuon__Run2016C-23Sep2016-v1/170221_173556/0000/tree_19.root', '/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v3/SingleMuon/VHBB_HEPPY_V25tthtautau_v3_SingleMuon__Run2016C-23Sep2016-v1/170221_173556/0000/tree_20.root', '/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v3/SingleMuon/VHBB_HEPPY_V25tthtautau_v3_SingleMuon__Run2016C-23Sep2016-v1/170221_173556/0000/tree_21.root', '/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v3/SingleMuon/VHBB_HEPPY_V25tthtautau_v3_SingleMuon__Run2016C-23Sep2016-v1/170221_173556/0000/tree_22.root', '/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v3/SingleMuon/VHBB_HEPPY_V25tthtautau_v3_SingleMuon__Run2016C-23Sep2016-v1/170221_173556/0000/tree_23.root', '/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v3/SingleMuon/VHBB_HEPPY_V25tthtautau_v3_SingleMuon__Run2016C-23Sep2016-v1/170221_173556/0000/tree_24.root', '/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v3/SingleMuon/VHBB_HEPPY_V25tthtautau_v3_SingleMuon__Run2016C-23Sep2016-v1/170221_173556/0000/tree_25.root', '/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v3/SingleMuon/VHBB_HEPPY_V25tthtautau_v3_SingleMuon__Run2016C-23Sep2016-v1/170221_173556/0000/tree_26.root', '/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v3/SingleMuon/VHBB_HEPPY_V25tthtautau_v3_SingleMuon__Run2016C-23Sep2016-v1/170221_173556/0000/tree_27.root', '/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v3/SingleMuon/VHBB_HEPPY_V25tthtautau_v3_SingleMuon__Run2016C-23Sep2016-v1/170221_173556/0000/tree_28.root', '/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v3/SingleMuon/VHBB_HEPPY_V25tthtautau_v3_SingleMuon__Run2016C-23Sep2016-v1/170221_173556/0000/tree_29.root', '/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v3/SingleMuon/VHBB_HEPPY_V25tthtautau_v3_SingleMuon__Run2016C-23Sep2016-v1/170221_173556/0000/tree_30.root', '/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v3/SingleMuon/VHBB_HEPPY_V25tthtautau_v3_SingleMuon__Run2016C-23Sep2016-v1/170221_173556/0000/tree_31.root', '/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v3/SingleMuon/VHBB_HEPPY_V25tthtautau_v3_SingleMuon__Run2016C-23Sep2016-v1/170221_173556/0000/tree_32.root', '/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v3/SingleMuon/VHBB_HEPPY_V25tthtautau_v3_SingleMuon__Run2016C-23Sep2016-v1/170221_173556/0000/tree_33.root', '/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v3/SingleMuon/VHBB_HEPPY_V25tthtautau_v3_SingleMuon__Run2016C-23Sep2016-v1/170221_173556/0000/tree_34.root', '/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v3/SingleMuon/VHBB_HEPPY_V25tthtautau_v3_SingleMuon__Run2016C-23Sep2016-v1/170221_173556/0000/tree_35.root', '/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v3/SingleMuon/VHBB_HEPPY_V25tthtautau_v3_SingleMuon__Run2016C-23Sep2016-v1/170221_173556/0000/tree_36.root', '/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v3/SingleMuon/VHBB_HEPPY_V25tthtautau_v3_SingleMuon__Run2016C-23Sep2016-v1/170221_173556/0000/tree_37.root', '/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v3/SingleMuon/VHBB_HEPPY_V25tthtautau_v3_SingleMuon__Run2016C-23Sep2016-v1/170221_173556/0000/tree_38.root', '/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v3/SingleMuon/VHBB_HEPPY_V25tthtautau_v3_SingleMuon__Run2016C-23Sep2016-v1/170221_173556/0000/tree_39.root', '/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v3/SingleMuon/VHBB_HEPPY_V25tthtautau_v3_SingleMuon__Run2016C-23Sep2016-v1/170221_173556/0000/tree_40.root', '/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v3/SingleMuon/VHBB_HEPPY_V25tthtautau_v3_SingleMuon__Run2016C-23Sep2016-v1/170221_173556/0000/tree_41.root', '/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v3/SingleMuon/VHBB_HEPPY_V25tthtautau_v3_SingleMuon__Run2016C-23Sep2016-v1/170221_173556/0000/tree_42.root', '/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v3/SingleMuon/VHBB_HEPPY_V25tthtautau_v3_SingleMuon__Run2016C-23Sep2016-v1/170221_173556/0000/tree_43.root', '/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v3/SingleMuon/VHBB_HEPPY_V25tthtautau_v3_SingleMuon__Run2016C-23Sep2016-v1/170221_173556/0000/tree_44.root', '/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v3/SingleMuon/VHBB_HEPPY_V25tthtautau_v3_SingleMuon__Run2016C-23Sep2016-v1/170221_173556/0000/tree_45.root', '/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v3/SingleMuon/VHBB_HEPPY_V25tthtautau_v3_SingleMuon__Run2016C-23Sep2016-v1/170221_173556/0000/tree_46.root', '/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v3/SingleMuon/VHBB_HEPPY_V25tthtautau_v3_SingleMuon__Run2016C-23Sep2016-v1/170221_173556/0000/tree_47.root', '/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v3/SingleMuon/VHBB_HEPPY_V25tthtautau_v3_SingleMuon__Run2016C-23Sep2016-v1/170221_173556/0000/tree_48.root', '/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v3/SingleMuon/VHBB_HEPPY_V25tthtautau_v3_SingleMuon__Run2016C-23Sep2016-v1/170221_173556/0000/tree_49.root', '/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v3/SingleMuon/VHBB_HEPPY_V25tthtautau_v3_SingleMuon__Run2016C-23Sep2016-v1/170221_173556/0000/tree_50.root', '/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v3/SingleMuon/VHBB_HEPPY_V25tthtautau_v3_SingleMuon__Run2016C-23Sep2016-v1/170221_173556/0000/tree_51.root', '/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v3/SingleMuon/VHBB_HEPPY_V25tthtautau_v3_SingleMuon__Run2016C-23Sep2016-v1/170221_173556/0000/tree_52.root', '/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v3/SingleMuon/VHBB_HEPPY_V25tthtautau_v3_SingleMuon__Run2016C-23Sep2016-v1/170221_173556/0000/tree_53.root', '/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v3/SingleMuon/VHBB_HEPPY_V25tthtautau_v3_SingleMuon__Run2016C-23Sep2016-v1/170221_173556/0000/tree_54.root', '/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v3/SingleMuon/VHBB_HEPPY_V25tthtautau_v3_SingleMuon__Run2016C-23Sep2016-v1/170221_173556/0000/tree_55.root', '/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v3/SingleMuon/VHBB_HEPPY_V25tthtautau_v3_SingleMuon__Run2016C-23Sep2016-v1/170221_173556/0000/tree_56.root', '/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v3/SingleMuon/VHBB_HEPPY_V25tthtautau_v3_SingleMuon__Run2016C-23Sep2016-v1/170221_173556/0000/tree_57.root', '/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v3/SingleMuon/VHBB_HEPPY_V25tthtautau_v3_SingleMuon__Run2016C-23Sep2016-v1/170221_173556/0000/tree_58.root', '/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v3/SingleMuon/VHBB_HEPPY_V25tthtautau_v3_SingleMuon__Run2016C-23Sep2016-v1/170221_173556/0000/tree_59.root', '/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v3/SingleMuon/VHBB_HEPPY_V25tthtautau_v3_SingleMuon__Run2016C-23Sep2016-v1/170221_173556/0000/tree_60.root', '/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v3/SingleMuon/VHBB_HEPPY_V25tthtautau_v3_SingleMuon__Run2016C-23Sep2016-v1/170221_173556/0000/tree_61.root', '/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v3/SingleMuon/VHBB_HEPPY_V25tthtautau_v3_SingleMuon__Run2016C-23Sep2016-v1/170221_173556/0000/tree_62.root', '/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v3/SingleMuon/VHBB_HEPPY_V25tthtautau_v3_SingleMuon__Run2016C-23Sep2016-v1/170221_173556/0000/tree_63.root', '/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v3/SingleMuon/VHBB_HEPPY_V25tthtautau_v3_SingleMuon__Run2016C-23Sep2016-v1/170221_173556/0000/tree_64.root', '/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v3/SingleMuon/VHBB_HEPPY_V25tthtautau_v3_SingleMuon__Run2016C-23Sep2016-v1/170221_173556/0000/tree_65.root', '/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v3/SingleMuon/VHBB_HEPPY_V25tthtautau_v3_SingleMuon__Run2016C-23Sep2016-v1/170221_173556/0000/tree_66.root', '/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v3/SingleMuon/VHBB_HEPPY_V25tthtautau_v3_SingleMuon__Run2016C-23Sep2016-v1/170221_173556/0000/tree_67.root', '/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v3/SingleMuon/VHBB_HEPPY_V25tthtautau_v3_SingleMuon__Run2016C-23Sep2016-v1/170221_173556/0000/tree_68.root', '/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v3/SingleMuon/VHBB_HEPPY_V25tthtautau_v3_SingleMuon__Run2016C-23Sep2016-v1/170221_173556/0000/tree_69.root', '/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v3/SingleMuon/VHBB_HEPPY_V25tthtautau_v3_SingleMuon__Run2016C-23Sep2016-v1/170221_173556/0000/tree_70.root', '/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v3/SingleMuon/VHBB_HEPPY_V25tthtautau_v3_SingleMuon__Run2016C-23Sep2016-v1/170221_173556/0000/tree_71.root', '/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v3/SingleMuon/VHBB_HEPPY_V25tthtautau_v3_SingleMuon__Run2016C-23Sep2016-v1/170221_173556/0000/tree_72.root', '/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v3/SingleMuon/VHBB_HEPPY_V25tthtautau_v3_SingleMuon__Run2016C-23Sep2016-v1/170221_173556/0000/tree_73.root', '/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v3/SingleMuon/VHBB_HEPPY_V25tthtautau_v3_SingleMuon__Run2016C-23Sep2016-v1/170221_173556/0000/tree_74.root', '/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v3/SingleMuon/VHBB_HEPPY_V25tthtautau_v3_SingleMuon__Run2016C-23Sep2016-v1/170221_173556/0000/tree_75.root', '/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v3/SingleMuon/VHBB_HEPPY_V25tthtautau_v3_SingleMuon__Run2016C-23Sep2016-v1/170221_173556/0000/tree_76.root', '/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v3/SingleMuon/VHBB_HEPPY_V25tthtautau_v3_SingleMuon__Run2016C-23Sep2016-v1/170221_173556/0000/tree_77.root', '/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v3/SingleMuon/VHBB_HEPPY_V25tthtautau_v3_SingleMuon__Run2016C-23Sep2016-v1/170221_173556/0000/tree_78.root', '/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v3/SingleMuon/VHBB_HEPPY_V25tthtautau_v3_SingleMuon__Run2016C-23Sep2016-v1/170221_173556/0000/tree_79.root', '/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v3/SingleMuon/VHBB_HEPPY_V25tthtautau_v3_SingleMuon__Run2016C-23Sep2016-v1/170221_173556/0000/tree_80.root', '/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v3/SingleMuon/VHBB_HEPPY_V25tthtautau_v3_SingleMuon__Run2016C-23Sep2016-v1/170221_173556/0000/tree_81.root', '/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v3/SingleMuon/VHBB_HEPPY_V25tthtautau_v3_SingleMuon__Run2016C-23Sep2016-v1/170221_173556/0000/tree_82.root', '/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v3/SingleMuon/VHBB_HEPPY_V25tthtautau_v3_SingleMuon__Run2016C-23Sep2016-v1/170221_173556/0000/tree_83.root', '/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v3/SingleMuon/VHBB_HEPPY_V25tthtautau_v3_SingleMuon__Run2016C-23Sep2016-v1/170221_173556/0000/tree_84.root', '/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v3/SingleMuon/VHBB_HEPPY_V25tthtautau_v3_SingleMuon__Run2016C-23Sep2016-v1/170221_173556/0000/tree_85.root', '/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v3/SingleMuon/VHBB_HEPPY_V25tthtautau_v3_SingleMuon__Run2016C-23Sep2016-v1/170221_173556/0000/tree_86.root', '/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v3/SingleMuon/VHBB_HEPPY_V25tthtautau_v3_SingleMuon__Run2016C-23Sep2016-v1/170221_173556/0000/tree_87.root', '/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v3/SingleMuon/VHBB_HEPPY_V25tthtautau_v3_SingleMuon__Run2016C-23Sep2016-v1/170221_173556/0000/tree_88.root', '/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v3/SingleMuon/VHBB_HEPPY_V25tthtautau_v3_SingleMuon__Run2016C-23Sep2016-v1/170221_173556/0000/tree_89.root', '/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v3/SingleMuon/VHBB_HEPPY_V25tthtautau_v3_SingleMuon__Run2016C-23Sep2016-v1/170221_173556/0000/tree_90.root', '/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v3/SingleMuon/VHBB_HEPPY_V25tthtautau_v3_SingleMuon__Run2016C-23Sep2016-v1/170221_173556/0000/tree_91.root', '/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v3/SingleMuon/VHBB_HEPPY_V25tthtautau_v3_SingleMuon__Run2016C-23Sep2016-v1/170221_173556/0000/tree_92.root', '/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v3/SingleMuon/VHBB_HEPPY_V25tthtautau_v3_SingleMuon__Run2016C-23Sep2016-v1/170221_173556/0000/tree_93.root', '/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v3/SingleMuon/VHBB_HEPPY_V25tthtautau_v3_SingleMuon__Run2016C-23Sep2016-v1/170221_173556/0000/tree_94.root', '/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v3/SingleMuon/VHBB_HEPPY_V25tthtautau_v3_SingleMuon__Run2016C-23Sep2016-v1/170221_173556/0000/tree_95.root', '/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v3/SingleMuon/VHBB_HEPPY_V25tthtautau_v3_SingleMuon__Run2016C-23Sep2016-v1/170221_173556/0000/tree_96.root', '/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v3/SingleMuon/VHBB_HEPPY_V25tthtautau_v3_SingleMuon__Run2016C-23Sep2016-v1/170221_173556/0000/tree_97.root', '/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v3/SingleMuon/VHBB_HEPPY_V25tthtautau_v3_SingleMuon__Run2016C-23Sep2016-v1/170221_173556/0000/tree_98.root', '/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v3/SingleMuon/VHBB_HEPPY_V25tthtautau_v3_SingleMuon__Run2016C-23Sep2016-v1/170221_173556/0000/tree_99.root', '/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau_v3/SingleMuon/VHBB_HEPPY_V25tthtautau_v3_SingleMuon__Run2016C-23Sep2016-v1/170221_173556/0000/tree_100.root'])
process.fwliteOutput.fileName = cms.string('SingleMuon_Run2016C_v1_Tight_lepOS_sumSS_central_1.root')
process.analyze_2lss_1tau.process = cms.string('data_obs')
process.analyze_2lss_1tau.histogramDir = cms.string('2lss_1tau_lepOS_sumSS_Tight')
process.analyze_2lss_1tau.era = cms.string('2016')
process.analyze_2lss_1tau.triggers_1e = cms.vstring(['HLT_BIT_HLT_Ele25_WPTight_Gsf_v', 'HLT_BIT_HLT_Ele27_WPTight_Gsf_v', 'HLT_BIT_HLT_Ele25_eta2p1_WPTight_Gsf_v', 'HLT_BIT_HLT_Ele27_eta2p1_WPLoose_Gsf_v'])
process.analyze_2lss_1tau.use_triggers_1e = cms.bool(False)
process.analyze_2lss_1tau.triggers_2e = cms.vstring(['HLT_BIT_HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v'])
process.analyze_2lss_1tau.use_triggers_2e = cms.bool(False)
process.analyze_2lss_1tau.triggers_1mu = cms.vstring(['HLT_BIT_HLT_IsoMu22_v', 'HLT_BIT_HLT_IsoTkMu22_v', 'HLT_BIT_HLT_IsoMu22_eta2p1_v', 'HLT_BIT_HLT_IsoTkMu22_eta2p1_v', 'HLT_BIT_HLT_IsoMu24_v', 'HLT_BIT_HLT_IsoTkMu24_v'])
process.analyze_2lss_1tau.use_triggers_1mu = cms.bool(True)
process.analyze_2lss_1tau.triggers_2mu = cms.vstring(['HLT_BIT_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v', 'HLT_BIT_HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v'])
process.analyze_2lss_1tau.use_triggers_2mu = cms.bool(False)
process.analyze_2lss_1tau.triggers_1e1mu = cms.vstring(['HLT_BIT_HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v', 'HLT_BIT_HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v'])
process.analyze_2lss_1tau.use_triggers_1e1mu = cms.bool(False)
process.analyze_2lss_1tau.leptonSelection = cms.string('Tight')
process.analyze_2lss_1tau.apply_leptonGenMatching = cms.bool(False)
process.analyze_2lss_1tau.apply_leptonGenMatching_ttZ_workaround = cms.bool(False)
process.analyze_2lss_1tau.leptonChargeSelection = cms.string('OS')
process.analyze_2lss_1tau.hadTauSelection = cms.string('Tight|dR03mvaMedium')
process.analyze_2lss_1tau.apply_hadTauGenMatching = cms.bool(False)
process.analyze_2lss_1tau.applyFakeRateWeights = cms.string('disabled')
process.analyze_2lss_1tau.hadTauFakeRateWeight.inputFileName = cms.string('tthAnalysis/HiggsToTauTau/data/FR_tau_2016.root')
process.analyze_2lss_1tau.hadTauFakeRateWeight.lead.fitFunctionName = cms.string('jetToTauFakeRate/dR03mvaMedium/$etaBin/fitFunction_data_div_mc_hadTaus_pt')
process.analyze_2lss_1tau.hadTauFakeRateWeight.applyGraph_lead = cms.bool(False)
process.analyze_2lss_1tau.hadTauFakeRateWeight.applyFitFunction_lead = cms.bool(True)
process.analyze_2lss_1tau.hadTauFakeRateWeight.applyGraph_sublead = cms.bool(False)
process.analyze_2lss_1tau.hadTauFakeRateWeight.applyFitFunction_sublead = cms.bool(True)
process.analyze_2lss_1tau.apply_hadTauFakeRateSF = cms.bool(True)
process.analyze_2lss_1tau.chargeSumSelection = cms.string('SS')
process.analyze_2lss_1tau.use_HIP_mitigation_bTag = cms.bool(True)
process.analyze_2lss_1tau.use_HIP_mitigation_mediumMuonId = cms.bool(True)
process.analyze_2lss_1tau.isMC = cms.bool(False)
process.analyze_2lss_1tau.central_or_shift = cms.string('central')
process.analyze_2lss_1tau.lumiScale = cms.double(1.000000)
process.analyze_2lss_1tau.apply_genWeight = cms.bool(False)
process.analyze_2lss_1tau.apply_trigger_bits = cms.bool(True)
process.analyze_2lss_1tau.selEventsFileName_output = cms.string('/home/ram/ttHAnalysis/2016/2017Mar17/output_rle/2lss_1tau/Tight_OS_SS/SingleMuon_Run2016C_v1/rle_2lss_1tau_SingleMuon_Run2016C_v1_Tight_lepOS_sumSS_central_1.txt')
process.analyze_2lss_1tau.selectBDT = cms.bool(False)

