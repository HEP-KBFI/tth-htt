import FWCore.ParameterSet.Config as cms

import os
  
process = cms.PSet()
  
process.fwliteInput = cms.PSet(
    #fileNames = cms.vstring('/afs/cern.ch/user/v/veelken/scratch0/VHbbNtuples_7_6_x/CMSSW_7_6_3/src/VHbbAnalysis/Heppy/test/latest_Loop/tree.root'),
    ##fileNames = cms.vstring('/afs/cern.ch/user/k/kaehatah/public/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/VHBB_HEPPY_V12_ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_Py8_mWCutfix__fall15MAv2-pu25ns15v1_76r2as_v12-v1/160330_172426/0000/tree_1.root'),
    fileNames = cms.vstring('/hdfs/cms/store/user/kaehatah/ttHToNonbb_M125_13TeV_powheg_pythia8/VHBB_HEPPY_V12_ttHToNonbb_M125_13TeV_powheg_Py8__fall15MAv2-pu25ns15v1_76r2as_v12-v1/160330_172641/0000/tree_10.root'),
    maxEvents = cms.int32(-1),
    outputEvery = cms.uint32(100000)
)

process.fwliteOutput = cms.PSet(
    fileName = cms.string('tthMVATrainingNtuple_2lss_1tau.root')
)

process.produceTTHMVATrainingNtuple_2lss_1tau = cms.PSet(
    treeName = cms.string('tree'),

    process = cms.string('ttH'),

    era = cms.string('2015'),
    
    triggers_1e = cms.vstring("HLT_BIT_HLT_Ele23_WPLoose_Gsf_v"),
    use_triggers_1e = cms.bool(True),
    triggers_2e = cms.vstring("HLT_BIT_HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v"),
    use_triggers_2e = cms.bool(True),
    triggers_1mu = cms.vstring("HLT_BIT_HLT_IsoMu20_v", "HLT_BIT_HLT_IsoTkMu20_v"),
    use_triggers_1mu = cms.bool(True),
    triggers_2mu = cms.vstring("HLT_BIT_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v", "HLT_BIT_HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v"),
    use_triggers_2mu = cms.bool(True),
    triggers_1e1mu = cms.vstring("HLT_BIT_HLT_Mu17_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v", "HLT_BIT_HLT_Mu8_TrkIsoVVL_Ele17_CaloIdL_TrackIdL_IsoVL_v"),
    use_triggers_1e1mu = cms.bool(True),

    apply_offline_e_trigger_cuts_1e = cms.bool(True),
    apply_offline_e_trigger_cuts_2e = cms.bool(False),
    apply_offline_e_trigger_cuts_1mu = cms.bool(False),
    apply_offline_e_trigger_cuts_2mu = cms.bool(False),
    apply_offline_e_trigger_cuts_1e1mu = cms.bool(False),
    
    leptonSelection = cms.string('Loose'),
    leptonChargeSelection = cms.string('SS'),

    hadTauSelection = cms.string('dR03mvaVVLoose'),
    
    leptonFakeRateLooseToTightWeight = cms.PSet(
        inputFileName = cms.string("tthAnalysis/HiggsToTauTau/data/FR_data_ttH_mva.root"),
        histogramName_e = cms.string("FR_mva075_el_data_comb"),
        histogramName_mu = cms.string("FR_mva075_mu_data_comb")
    ),
    
    isMC = cms.bool(False),
    central_or_shift = cms.string('central'),
    lumiScale = cms.double(1.),
    apply_trigger_bits = cms.bool(True),
    
    fillGenEvtHistograms = cms.bool(True),
    
    selEventsFileName_input = cms.string(''),
    selEventsFileName_output = cms.string('')
)
