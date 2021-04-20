import FWCore.ParameterSet.Config as cms

from tthAnalysis.HiggsToTauTau.configs.recommendedMEtFilters_cfi import * # needed for automatic template filling
from tthAnalysis.HiggsToTauTau.configs.EvtYieldHistManager_cfi import * # needed for automatic template filling

process = cms.PSet()

process.fwliteInput = cms.PSet(
    fileNames = cms.vstring(),
    maxEvents = cms.int32(-1),
    outputEvery = cms.uint32(10000)
)

process.fwliteOutput = cms.PSet(
    fileName = cms.string('')
)

process.analyze_testGenPhotonFilter = cms.PSet(
    treeName = cms.string('Events'),

    process = cms.string(''),
    era = cms.string(''),
    isMC = cms.bool(True),

    central_or_shift = cms.string(''),
    lumiScale = cms.VPSet(),
    ref_genWeight = cms.double(0.),
    apply_genWeight = cms.bool(True),

    branchName_genLeptons = cms.string('GenLep'),
    branchName_genPhotons = cms.string('GenPhoton'),
    branchName_genProxyPhotons = cms.string('GenPhotonCandidate'),
    branchName_genFromHardProcess = cms.string('GenIsHardProcess'),

    selEventsFileName_input = cms.string(''),
    isDEBUG = cms.bool(False),

    leptonFakeRateWeight = cms.PSet(), # needed for automatic template filling
)
