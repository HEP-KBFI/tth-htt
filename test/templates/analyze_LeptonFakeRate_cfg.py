import FWCore.ParameterSet.Config as cms
import os

from tthAnalysis.HiggsToTauTau.configs.LeptonFakeRate_trigger_cfi import *
from tthAnalysis.HiggsToTauTau.configs.recommendedMEtFilters_cfi import *
from tthAnalysis.HiggsToTauTau.configs.EvtYieldHistManager_cfi import *

process = cms.PSet()

process.fwliteInput = cms.PSet(
    fileNames = cms.vstring(),
    maxEvents = cms.int32(-1),
    outputEvery = cms.uint32(100000)
)

process.fwliteOutput = cms.PSet(
    fileName = cms.string('')
)

process.analyze_LeptonFakeRate = cms.PSet(
    treeName = cms.string('Events'),

    process = cms.string(''),

    era = cms.string(''),

    use_triggers_1e = cms.bool(True),
    use_triggers_2e = cms.bool(True),
    use_triggers_1mu = cms.bool(True),
    use_triggers_2mu = cms.bool(True),

    triggers_1e = cms.vstring(),
    triggers_1mu = cms.vstring(),
    triggers_2e = cms.vstring(),
    triggers_2mu = cms.vstring(),

    triggers_mu_cfg = cms.VPSet(),
    triggers_e_cfg = cms.VPSet(),

    absEtaBins_e = cms.vdouble(0., 1.479, 9.9),
    ptBins_e = cms.vdouble(15., 20., 30., 45., 65., 100000.),
    absEtaBins_mu = cms.vdouble(0., 1.479, 9.9),
    ptBins_mu = cms.vdouble(10., 15., 20., 30., 45., 65., 100000.),

    minConePt_global_e = cms.double(10),
    minRecoPt_global_e = cms.double(7),
    minConePt_global_mu = cms.double(10),
    minRecoPt_global_mu = cms.double(5),

    isMC = cms.bool(True),
    central_or_shift = cms.string(''),
    lumiScale = cms.double(1.),
    apply_genWeight = cms.bool(True),
    apply_met_filters = cms.bool(True),
    cfgMEtFilter = cms.PSet(),
    fillGenEvtHistograms = cms.bool(True),
    cfgEvtYieldHistManager = cms.PSet(),

    branchName_electrons = cms.string('Electron'),
    branchName_muons = cms.string('Muon'),
    branchName_hadTaus = cms.string('Tau'),
    branchName_jets = cms.string('Jet'),
    branchName_met = cms.string('MET'),

    branchName_genLeptons = cms.string('GenLep'),
    branchName_genHadTaus = cms.string('GenVisTau'),
    branchName_genPhotons = cms.string('GenPhoton'),
    branchName_genJets = cms.string('GenJet'),
    redoGenMatching = cms.bool(True),

    selEventsFileName_input = cms.string(''),
    selEventsFileName_output = cms.string(''),
    isDEBUG = cms.bool(False),
    applyMETFilters = cms.bool(True),
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
