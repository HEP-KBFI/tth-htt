import FWCore.ParameterSet.Config as cms

import os
  
process = cms.PSet()
  
process.fwliteInput = cms.PSet(
    ##fileNames = cms.vstring('/afs/cern.ch/user/v/veelken/scratch0/VHbbNtuples_7_6_x/CMSSW_7_6_3/src/VHbbAnalysis/Heppy/test/latest_Loop/tree.root'),
    fileNames = cms.vstring('/hdfs/cms/store/user/atiko/VHBBHeppyV25tthtautau/MC/ZZTo4L_13TeV_powheg_pythia8/VHBB_HEPPY_V25tthtautau_ZZTo4L_13TeV_powheg_Py8__RunIISummer16MAv2-PUMoriond17_80r2as_2016_TrancheIV_v6-v1/170207_125252/0000/tree_1.root'),
    maxEvents = cms.int32(-1),
    outputEvery = cms.uint32(100000)
)

process.fwliteOutput = cms.PSet(
    fileName = cms.string('analyze_LeptonFakeRate.root')
)

process.analyze_LeptonFakeRate = cms.PSet(
    treeName = cms.string('tree'),

    process = cms.string('ttH'),

    era = cms.string('2016'),
    ## ned to split up triggers by pt range later !!!
    triggers_1e = cms.vstring("HLT_BIT_HLT_Ele12_CaloIdM_TrackIdM_PFJet30_v","HLT_BIT_HLT_Ele17_CaloIdM_TrackIdM_PFJet30_v","HLT_BIT_HLT_Ele23_CaloIdM_TrackIdM_PFJet30_v"),
    use_triggers_1e = cms.bool(True),
    triggers_1mu = cms.vstring("HLT_BIT_HLT_Mu3_PFJet40_v", "HLT_BIT_HLT_Mu8_v", "HLT_BIT_HLT_Mu17_v", "HLT_BIT_HLT_Mu27_v" ),
    use_triggers_1mu = cms.bool(True),
#    triggers_1e1mu = cms.vstring("HLT_BIT_HLT_Mu17_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v", "HLT_BIT_HLT_Mu8_TrkIsoVVL_Ele17_CaloIdL_TrackIdL_IsoVL_v"),
#    use_triggers_1e1mu = cms.bool(False),
    apply_offline_e_trigger_cuts_1e = cms.bool(True),
    apply_offline_e_trigger_cuts_1mu = cms.bool(True),
#    apply_offline_e_trigger_cuts_1e1mu = cms.bool(True),
    
    chargeSelection = cms.string('OS'),

    jet_minPt = cms.double(20.),
    jet_maxPt = cms.double(1.e+6),
    jet_minAbsEta = cms.double(-1.),
    jet_maxAbsEta = cms.double(2.3),
    
    hadTauSelections = cms.vstring(
        'dR05isoLoose',
        'dR05isoMedium',
        'dR05isoTight',
        'dR03mvaVLoose',
        'dR03mvaLoose',
        'dR03mvaMedium',
        'dR03mvaTight',
        'dR03mvaVTight',
        'dR03mvaVVTight'
    ),
    
    absEtaBins = cms.vdouble(-1., 1.479, 9.9),

    use_HIP_mitigation_bTag = cms.bool(False),
    use_HIP_mitigation_mediumMuonId = cms.bool(False),
                                      
    isMC = cms.bool(True),
    central_or_shift = cms.string('central'),
    lumiScale = cms.double(1.),
    apply_trigger_bits = cms.bool(True),
    apply_genWeight = cms.bool(True),
    fillGenEvtHistograms = cms.bool(True),
    
    selEventsFileName_input = cms.string(''),
    selEventsFileName_output = cms.string('')
)
