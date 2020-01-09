import FWCore.ParameterSet.Config as cms
import os

from tthAnalysis.HiggsToTauTau.configs.recommendedMEtFilters_cfi import *
from tthAnalysis.HiggsToTauTau.configs.EvtYieldHistManager_cfi import *
from tthAnalysis.HiggsToTauTau.analysisSettings import *

process = cms.PSet()

process.fwliteInput = cms.PSet(
    fileNames = cms.vstring(),
    maxEvents = cms.int32(-1),
    outputEvery = cms.uint32(100000)
)

process.fwliteOutput = cms.PSet(
    fileName = cms.string('')
)

process.analyze_charge_flip_mu = cms.PSet(
    treeName = cms.string('Events'),

    process = cms.string(''),

    era = cms.string(''),

    triggers_1e = cms.vstring(),
    use_triggers_1e = cms.bool(False),
    triggers_2e = cms.vstring(),
    use_triggers_2e = cms.bool(False),
    triggers_1mu = cms.vstring(),
    use_triggers_1mu = cms.bool(True),
    triggers_2mu = cms.vstring(),
    use_triggers_2mu = cms.bool(True),
    triggers_1e1mu = cms.vstring(),
    use_triggers_1e1mu = cms.bool(False),

    apply_offline_e_trigger_cuts_1e = cms.bool(False),
    apply_offline_e_trigger_cuts_2e = cms.bool(False),
    apply_offline_e_trigger_cuts_1mu = cms.bool(True),
    apply_offline_e_trigger_cuts_2mu = cms.bool(True),
    apply_offline_e_trigger_cuts_1e1mu = cms.bool(False),

    leptonSelection = cms.string(''),

    hadTauSelection = cms.string(''),

    leptonFakeRateLooseToTightWeight = cms.PSet(
        inputFileName = cms.string(""),
        histogramName_e = cms.string(""),
        histogramName_mu = cms.string("")
    ),

    isMC = cms.bool(False),
    central_or_shift = cms.string(''),
    lumiScale = cms.VPSet(),
    apply_l1PreFireWeight = cms.bool(True),
    apply_genWeight = cms.bool(True),
    apply_DYMCReweighting = cms.bool(False),
    apply_DYMCNormScaleFactors = cms.bool(False),

    cfgMEtFilter = cms.PSet(),
    cfgEvtYieldHistManager = cms.PSet(),
    triggerWhiteList = cms.PSet(),

    branchName_electrons = cms.string('Electron'),
    branchName_muons = cms.string('Muon'),
    branchName_jets = cms.string('Jet'),

    branchName_genTauLeptons = cms.string('GenTau'),
    branchName_genLeptons = cms.string('GenLep'),
    branchName_genHadTaus = cms.string('GenVisTau'),
    branchName_genPhotons = cms.string('GenPhoton'),
    branchName_genJets = cms.string('GenJet'),
    branchName_muonGenMatch     = cms.string('MuonGenMatch'),
    branchName_electronGenMatch = cms.string('ElectronGenMatch'),
    branchName_jetGenMatch      = cms.string('JetGenMatch'),
    redoGenMatching = cms.bool(True),
    genMatchingByIndex = cms.bool(True),
    jetCleaningByIndex = cms.bool(True),

    fillGenEvtHistograms = cms.bool(False),

    selEventsFileName_input = cms.string(''),
    selEventsFileName_output = cms.string(''),
    isDEBUG = cms.bool(False),
    hasLHE = cms.bool(True),
    useObjectMultiplicity = cms.bool(False),

    evtWeight = cms.PSet(
        apply = cms.bool(False),
        histogramFile = cms.string(''),
        histogramName = cms.string(''),
        branchNameXaxis = cms.string(''),
        branchNameYaxis = cms.string(''),
        branchTypeXaxis = cms.string(''),
        branchTypeYaxis = cms.string(''),
    ),
    tHweights = cms.VPSet(),
)
