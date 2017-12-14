import FWCore.ParameterSet.Config as cms

import os
  
process = cms.PSet()
  
process.fwliteInput = cms.PSet(
#    fileNames = cms.vstring('/home/karl/VHbbNtuples_7_6_x3/CMSSW_7_6_3/src/VHbbAnalysis/Heppy/test/Loop_1/tree.root'),
#    fileNames = cms.vstring('/home/karl/VHbbNtuples_7_6_x3/CMSSW_7_6_3/src/VHbbAnalysis/Heppy/test/Loop_2/tree.root'),
    fileNames = cms.vstring('/home/andres/tth/sync/ttHJetToNonbb_M125_13TeV_sync_summer_v3.root'),
    maxEvents = cms.int32(-1),
    outputEvery = cms.uint32(10000)
)

process.fwliteOutput = cms.PSet(
#    fileName = cms.string('/home/karl/sandbox/sync_ntuples/ttHJetToTT_M125_13TeV_ntuples_sync_v0.root')
#    fileName = cms.string('/home/karl/sandbox/sync_ntuples/ttJet_13TeV_ntuples_sync_v0.root')
    fileName = cms.string('/home/andres/tth/sync/sync_ntuple_summer_v1_crab.root')
)

process.syncNtuple = cms.PSet(
    treeName = cms.string('tree'),
    outputTreeName = cms.string('syncTree'),
    era = cms.string('2016'),

    # 2016 triggers
    triggers_1e = cms.vstring(['HLT_BIT_HLT_Ele25_WPTight_Gsf_v', 'HLT_BIT_HLT_Ele25_eta2p1_WPTight_Gsf_v', 'HLT_BIT_HLT_Ele27_eta2p1_WPLoose_Gsf_v', 'HLT_BIT_HLT_Ele27_eta2p1_WPTight_Gsf_v']),
    triggers_2e = cms.vstring(['HLT_BIT_HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v']),
    triggers_1mu = cms.vstring(['HLT_BIT_HLT_IsoMu22_v', 'HLT_BIT_HLT_IsoTkMu22_v', 'HLT_BIT_HLT_IsoMu22_eta2p1_v', 'HLT_BIT_HLT_IsoTkMu22_eta2p1_v']),
    triggers_2mu = cms.vstring(['HLT_BIT_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v', 'HLT_BIT_HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v']),
    triggers_1e1mu = cms.vstring(['HLT_BIT_HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v', 'HLT_BIT_HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v']),
  
    use_triggers_1e = cms.bool(True),
    use_triggers_2e = cms.bool(True),
    use_triggers_1mu = cms.bool(True),
    use_triggers_2mu = cms.bool(True),
    use_triggers_1e1mu = cms.bool(True),
  
    triggers_3e = cms.vstring(),
    use_triggers_3e = cms.bool(False),
    triggers_2e1mu = cms.vstring(),
    use_triggers_2e1mu = cms.bool(False),
    triggers_1e2mu = cms.vstring(),
    use_triggers_1e2mu = cms.bool(False),
    triggers_3mu = cms.vstring(),
    use_triggers_3mu = cms.bool(False),

    apply_offline_e_trigger_cuts_1e = cms.bool(True),
    apply_offline_e_trigger_cuts_1mu = cms.bool(True),
    apply_offline_e_trigger_cuts_2e = cms.bool(True),
    apply_offline_e_trigger_cuts_1e1mu = cms.bool(True),
    apply_offline_e_trigger_cuts_2mu = cms.bool(True),
    apply_offline_e_trigger_cuts_3e = cms.bool(True),
    apply_offline_e_trigger_cuts_2e1mu = cms.bool(True),
    apply_offline_e_trigger_cuts_1e2mu = cms.bool(True),
    apply_offline_e_trigger_cuts_3mu = cms.bool(True),

  
    #selEventsFileName_input = cms.string('testEv.txt'),
    selEventsFileName_input = cms.string(''),
    selEventsFileName_output = cms.string(''),

    leptonSelection = cms.string('Fakeable'),

    hadTauSelection = cms.string('Tight|dR03mvaMedium'),
    #hadTauSelection = cms.string('dR03mvaTight'),
    leptonFakeRateWeight = cms.PSet(
        inputFileName = cms.string("tthAnalysis/HiggsToTauTau/data/FR_lep_ttH_mva_2016_data.root"),
        histogramName_e = cms.string("FR_mva075_el_data_comb"),
        histogramName_mu = cms.string("FR_mva075_mu_data_comb")
    ),
    hadTauFakeRateWeight = cms.PSet(
        inputFileName = cms.string("tthAnalysis/HiggsToTauTau/data/FR_tau_2016.root"),
        lead = cms.PSet(
            absEtaBins = cms.vdouble(-1., 1.479, 9.9),
            graphName = cms.string("jetToTauFakeRate/dR03mvaTight/$etaBin/jetToTauFakeRate_mc_hadTaus_pt"),
            applyGraph = cms.bool(True),
            fitFunctionName = cms.string("jetToTauFakeRate/dR03mvaTight/$etaBin/fitFunction_data_div_mc_hadTaus_pt"),
            applyFitFunction = cms.bool(True),
            applyGraph_lead = cms.bool(False),
            applyFitFunction_lead = cms.bool(True),
            applyGraph_sublead = cms.bool(False),
            applyFitFunction_sublead = cms.bool(True)
        )
    ),    
    debug = cms.bool(False), # set it to True if you select only few events
    lumiScale = cms.double(0.002600),
    apply_trigger_bits = cms.bool(True),
    #apply_leptonGenMatching = cms.bool(True)
    #apply_hadTauGenMatching = cms.bool(False),
    apply_hadTauGenMatching = cms.bool(True),
    applyFakeRateWeights = cms.string('disabled'),
    apply_hadTauFakeRateSF = cms.bool(True),
    isMC = cms.bool(True),
    apply_genWeight = cms.bool(True),
    use_HIP_mitigation_mediumMuonId = cms.bool(False),
    
    selectBDT = cms.bool(False)
)
