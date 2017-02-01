import FWCore.ParameterSet.Config as cms

import os
  
process = cms.PSet()
  
process.fwliteInput = cms.PSet(
#    fileNames = cms.vstring('/home/karl/VHbbNtuples_7_6_x3/CMSSW_7_6_3/src/VHbbAnalysis/Heppy/test/Loop_1/tree.root'),
#    fileNames = cms.vstring('/home/karl/VHbbNtuples_7_6_x3/CMSSW_7_6_3/src/VHbbAnalysis/Heppy/test/Loop_2/tree.root'),
    fileNames = cms.vstring('/home/andres/tth/sync/ttHJetToNonbb_M125_13TeV_sync_summer_v0.root'),
    maxEvents = cms.int32(-1),
    outputEvery = cms.uint32(10000)
)

process.fwliteOutput = cms.PSet(
#    fileName = cms.string('/home/karl/sandbox/sync_ntuples/ttHJetToTT_M125_13TeV_ntuples_sync_v0.root')
#    fileName = cms.string('/home/karl/sandbox/sync_ntuples/ttJet_13TeV_ntuples_sync_v0.root')
    fileName = cms.string('/home/andres/tth/sync/sync_ntuple_summer_v0.root')
)

process.syncNtuple = cms.PSet(
    treeName = cms.string('tree'),
    outputTreeName = cms.string('syncTree'),
#    era = cms.string('2015'),
    era = cms.string('2016'),

    # 2015 triggers
    #triggers_1e = cms.vstring('HLT_BIT_HLT_Ele23_WPLoose_Gsf_v'),
    #triggers_2e = cms.vstring('HLT_BIT_HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v'),
    #triggers_1mu = cms.vstring('HLT_BIT_HLT_IsoMu20_v', 'HLT_BIT_HLT_IsoTkMu20_v'),
    #triggers_2mu = cms.vstring('HLT_BIT_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v', 'HLT_BIT_HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v'),
    #triggers_1e1mu = cms.vstring('HLT_BIT_HLT_Mu17_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v', 'HLT_BIT_HLT_Mu8_TrkIsoVVL_Ele17_CaloIdL_TrackIdL_IsoVL_v'),

    # 2016 triggers
    triggers_1e = cms.vstring('HLT_BIT_HLT_Ele25_WPTight_Gsf_v'),
    triggers_2e = cms.vstring('HLT_BIT_HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v'),
    triggers_1mu = cms.vstring('HLT_BIT_HLT_IsoMu22_v', 'HLT_BIT_HLT_IsoTkMu22_v'),
    triggers_2mu = cms.vstring('HLT_BIT_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v', 'HLT_BIT_HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v'),
    triggers_1e1mu = cms.vstring('HLT_BIT_HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v', 'HLT_BIT_HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v'),

    selEventsFileName_input = cms.string(''),
    selEventsFileName_output = cms.string(''),

    leptonSelection = cms.string('Fakeable'),

    hadTauSelection = cms.string('dR03mvaTight'),
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
            applyFitFunction = cms.bool(True)
        )
    ),    
    debug = cms.bool(False), # set it to True if you select only few events
    lumiScale = cms.double(0.000446),
    apply_trigger_bits = cms.bool(False),
    apply_hadTauGenMatching = cms.bool(False),
    #applyFakeRateWeights = cms.string('disabled')
    isMC = cms.bool(True),
    #apply_genWeight = cms.bool(True)
    use_HIP_mitigation_bTag = cms.bool(True),
    use_HIP_mitigation_mediumMuonId = cms.bool(False)
    

)
