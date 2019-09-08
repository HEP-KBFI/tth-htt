import FWCore.ParameterSet.Config as cms
import os

from tthAnalysis.HiggsToTauTau.configs.recommendedMEtFilters_cfi import *
from tthAnalysis.HiggsToTauTau.configs.EvtYieldHistManager_cfi import *

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

    hadTauSelection_tauIdWP = cms.string(''),
    hadTauAk8Clean_tauIdWP =  cms.string(''),

    isMC = cms.bool(True),
    central_or_shift = cms.string('central'),

    branchName_electrons  = cms.string('Electron'),
    branchName_muons      = cms.string('Muon'),
    branchName_hadTaus    = cms.string('Tau'),
    branchName_jets       = cms.string('Jet'),
    branchName_met        = cms.string('MET'),
    branchName_genLeptons = cms.string('GenLep'),
    branchName_genPhotons = cms.string('GenPhoton'),
    branchName_genHadTaus = cms.string('GenVisTau'),
    branchName_genJets    = cms.string('GenJet'),

    branchName_muonGenMatch     = cms.string('MuonGenMatch'),
    branchName_electronGenMatch = cms.string('ElectronGenMatch'),
    branchName_hadTauGenMatch   = cms.string('TauGenMatch'),
    branchName_jetGenMatch      = cms.string('JetGenMatch'),

    branchName_jetsHTTv2    = cms.string('HTTV2'),
    branchName_subjetsHTTv2 = cms.string('HTTV2Subjets'),
    branchName_jetsAK8      = cms.string('FatJet'),
    branchName_subjetsAK8   = cms.string('SubJet'),

    redoGenMatching    = cms.bool(False),
    genMatchingByIndex = cms.bool(True),
    jetCleaningByIndex = cms.bool(True),

    selEventsFileName_input = cms.string(''),
    isDEBUG = cms.bool(False),
    useNonNominal = cms.bool(False),

    syncNtuple = cms.PSet(
        tree = cms.string('syncTree'),
        output = cms.string('inclusive.root'),
        genMatch = cms.vstring(),
    ),
)
