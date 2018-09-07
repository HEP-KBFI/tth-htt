import FWCore.ParameterSet.Config as cms

import os

process = cms.PSet()

process.fwliteInput = cms.PSet(
    fileNames = cms.vstring(),
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

    triggers_1e = cms.vstring(),
    triggers_2e = cms.vstring(),
    triggers_1mu = cms.vstring(),
    triggers_2mu = cms.vstring(),
    triggers_1e1mu = cms.vstring(),
    triggers_3e = cms.vstring(),
    triggers_2e1mu = cms.vstring(),
    triggers_1e2mu = cms.vstring(),
    triggers_3mu = cms.vstring(),
    triggers_1mu1tau = cms.vstring(),
    triggers_1e1tau = cms.vstring(),
    triggers_2tau = cms.vstring(),

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

    cfgMEtFilter = cms.PSet(),
    cfgEvtYieldHistManager = cms.PSet(),

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
        requireGenMatching = cms.bool(False),
    ),
    hasLHE = cms.bool(True),

    evtWeight = cms.PSet(
        apply = cms.bool(False),
        histogramFile = cms.string(''),
        histogramName = cms.string(''),
        branchNameXaxis = cms.string(''),
        branchNameYaxis = cms.string(''),
        branchTypeXaxis = cms.string(''),
        branchTypeYaxis = cms.string(''),
    ),
)
