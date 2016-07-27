import FWCore.ParameterSet.Config as cms

import os
  
process = cms.PSet()
  
process.fwliteInput = cms.PSet(
    ##fileNames = cms.vstring('/afs/cern.ch/user/v/veelken/scratch0/VHbbNtuples_7_6_x/CMSSW_7_6_3/src/VHbbAnalysis/Heppy/test/latest_Loop/tree.root'),
    fileNames = cms.vstring('/afs/cern.ch/user/k/kaehatah/public/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix/VHBB_HEPPY_V12_ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_Py8_mWCutfix__fall15MAv2-pu25ns15v1_76r2as_v12-v1/160330_172426/0000/tree_1.root'),
    maxEvents = cms.int32(-1),
    outputEvery = cms.uint32(100000)
)

process.fwliteOutput = cms.PSet(
    fileName = cms.string('analyze_jetToTauFakeRate.root')
)

process.analyze_jetToTauFakeRate = cms.PSet(
    treeName = cms.string('tree'),

    process = cms.string('ttH'),

    triggers_1e = cms.vstring("HLT_BIT_HLT_Ele23_WPLoose_Gsf_v"),
    use_triggers_1e = cms.bool(True),
    triggers_1mu = cms.vstring("HLT_BIT_HLT_IsoMu20_v", "HLT_BIT_HLT_IsoTkMu20_v"),
    use_triggers_1mu = cms.bool(True),
    triggers_1e1mu = cms.vstring("HLT_BIT_HLT_Mu17_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v", "HLT_BIT_HLT_Mu8_TrkIsoVVL_Ele17_CaloIdL_TrackIdL_IsoVL_v"),
    use_triggers_1e1mu = cms.bool(True),

    apply_offline_e_trigger_cuts_1e = cms.bool(True),
    apply_offline_e_trigger_cuts_1mu = cms.bool(False),
    apply_offline_e_trigger_cuts_1e1mu = cms.bool(False),
    
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
    hadTauAbsEtaBins = cms.vdouble(-1., 1.2, 1.7, 9.9),
                                      
    isMC = cms.bool(False),
    central_or_shift = cms.string('central'),
    lumiScale = cms.double(1.),
    
    selEventsFileName_input = cms.string(''),
    selEventsFileName_output = cms.string('')
)
