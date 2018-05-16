import FWCore.ParameterSet.Config as cms

import os

process = cms.PSet()

process.fwliteInput = cms.PSet(
    fileNames = cms.vstring(''),
    maxEvents = cms.int32(-1),
    outputEvery = cms.uint32(1000)
)

process.fwliteOutput = cms.PSet(
    fileName = cms.string('')
)

process.analyze_inclusive = cms.PSet(
    treeName = cms.string('Events'),
    process = cms.string('signal'),
    era = cms.string('2017'),

    triggers_1e = cms.vstring('HLT_Ele32_WPTight_Gsf', 'HLT_Ele35_WPTight_Gsf'),
    triggers_2e = cms.vstring('HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ'),
    triggers_1mu = cms.vstring('HLT_IsoMu24', 'HLT_IsoMu27'),
    triggers_2mu = cms.vstring('HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL', 'HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ'),
    triggers_1e1mu = cms.vstring(
        'HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL',
        'HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ',
        'HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ',
    ),
    triggers_3e = cms.vstring('HLT_Ele16_Ele12_Ele8_CaloIdL_TrackIdL'),
    triggers_2e1mu = cms.vstring('HLT_Mu8_DiEle12_CaloIdL_TrackIdL'),
    triggers_1e2mu = cms.vstring('HLT_DiMu9_Ele9_CaloIdL_TrackIdL', 'HLT_DiMu9_Ele9_CaloIdL_TrackIdL_DZ'),
    triggers_3mu = cms.vstring('HLT_TripleMu_12_10_5'),
    triggers_1mu1tau = cms.vstring('HLT_IsoMu20_eta2p1_LooseChargedIsoPFTau27_eta2p1_CrossL1'),
    triggers_1e1tau = cms.vstring('HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTau30_eta2p1_CrossL1'),
    triggers_2tau = cms.vstring(
        'HLT_DoubleMediumChargedIsoPFTau35_Trk1_eta2p1_Reg',
        'HLT_DoubleTightChargedIsoPFTau35_Trk1_TightID_eta2p1_Reg',
        'HLT_DoubleMediumChargedIsoPFTau40_Trk1_TightID_eta2p1_Reg',
        'HLT_DoubleTightChargedIsoPFTau40_Trk1_eta2p1_Reg',
    ),

    use_triggers_1e = cms.bool(True),
    use_triggers_2e = cms.bool(True),
    use_triggers_1mu = cms.bool(True),
    use_triggers_2mu = cms.bool(True),
    use_triggers_1e1mu = cms.bool(True),
    use_triggers_3e = cms.bool(True),
    use_triggers_2e1mu = cms.bool(True),
    use_triggers_1e2mu = cms.bool(True),
    use_triggers_3mu = cms.bool(True),
    use_triggers_1mu1tau = cms.bool(True),
    use_triggers_1e1tau = cms.bool(True),
    use_triggers_2tau = cms.bool(True),

    apply_offline_e_trigger_cuts_1e = cms.bool(True),
    apply_offline_e_trigger_cuts_2e = cms.bool(True),
    apply_offline_e_trigger_cuts_1mu = cms.bool(True),
    apply_offline_e_trigger_cuts_2mu = cms.bool(True),
    apply_offline_e_trigger_cuts_1e1mu = cms.bool(True),
    apply_offline_e_trigger_cuts_3e = cms.bool(True),
    apply_offline_e_trigger_cuts_2e1mu = cms.bool(True),
    apply_offline_e_trigger_cuts_1e2mu = cms.bool(True),
    apply_offline_e_trigger_cuts_3mu = cms.bool(True),
    apply_offline_e_trigger_cuts_1mu1tau = cms.bool(True),
    apply_offline_e_trigger_cuts_1e1tau = cms.bool(True),

    hadTauSelection_tauIdWP = cms.string('dR03mvaMedium'),

    isMC = cms.bool(True),
    central_or_shift = cms.string('central'),
    apply_trigger_bits = cms.bool(True),

    branchName_electrons = cms.string('Electron'),
    branchName_muons = cms.string('Muon'),
    branchName_hadTaus = cms.string('Tau'),
    branchName_jets = cms.string('Jet'),
    branchName_met = cms.string('MET'),

    selEventsFileName_input = cms.string(''),
    isDEBUG = cms.bool(False),
    useNonNominal = cms.bool(False),

    syncNtuple = cms.PSet(
        tree = cms.string('syncTree'),
        output = cms.string('inclusive.root'),
    ),
    hasLHE = cms.bool(True),
)
