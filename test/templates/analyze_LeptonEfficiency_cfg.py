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

process.analyze_LeptonEfficiency = cms.PSet(
    treeName = cms.string('Events'),
    process = cms.string(''), ## overwritten at the bottom 
    era = cms.string('2016'), ## overwritten at the bottom 
    isMC = cms.bool(True),    ## overwritten at the bottom 
    hasLHE = cms.bool(True),  ## overwritten at the bottom 
    useObjectMultiplicity = cms.bool(False), ## overwritten at the bottom

    lepton_type = cms.string('e'), ## 2 options: e/mu (will be overwritten at the bottom)

    triggers_1e = cms.vstring(), ## overwritten at the bottom
    use_triggers_1e = cms.bool(False), ## overwritten at the bottom 
    apply_offline_e_trigger_cuts_1e = cms.bool(True),  ## will be overwritten at the bottom

    triggers_1mu = cms.vstring(), ## should be overwritten at the bottom
    use_triggers_1mu = cms.bool(False), ## should be overwritten at the bottom


    leptonSelection = cms.string('Tight'), ## will be overwritten at the bottom
    lep_useTightChargeCut  = cms.bool(False), ## overwritten at the bottom 
    central_or_shift = cms.string('central'), ## overwritten at the bottom 
    lumiScale = cms.VPSet(), ## overwritten at the bottom

    ref_genWeight = cms.double(0.), ## overwritten at the bottom
    apply_genWeight = cms.bool(True), ## overwritten at the bottom
    apply_topPtReweighting = cms.string(''), ## overwritten at the bottom (I WAS HERE !!)
    apply_DYMCReweighting = cms.bool(False), ## overwritten at the bottom
    apply_DYMCNormScaleFactors = cms.bool(False), ## overwritten at the bottom
    apply_l1PreFireWeight = cms.bool(True), ## overwritten at the bottom
    applyBtagSFRatio      = cms.bool(True), ## overwritten at the bottom
    fillGenEvtHistograms  = cms.bool(False), ## overwritten at the bottom
    jetCleaningByIndex    = cms.bool(True), ## overwritten at the bottom
    redoGenMatching       = cms.bool(True), # WAS FALSE BEFORE (= !genMatchingByIndex inside analyzeConfig.py)
    genMatchingByIndex    = cms.bool(False), ## overwritten at the bottom
    isDEBUG = cms.bool(False),
    useBothLeptonsInGenMatching = cms.bool(False), ## Set this to True to use the gen-match status of both Tag and Probe leptons

    hadTauSelection = cms.string('Tight|deepVSjMedium'), ## NEW LINE
    #apply_hadTauGenMatching = cms.bool(False), ## NOT NEEDED

    ## ---------- NEW LINES ----------
    absEtaBins_e = cms.vdouble(0., 0.9, 1.2, 2.1, 2.5),
    ptBins_e = cms.vdouble(10., 15., 20., 25., 30., 35., 40., 45., 60., 80., 120.),
    absEtaBins_mu = cms.vdouble(0., 0.9, 1.2, 2.1, 2.5),
    ptBins_mu = cms.vdouble(10., 15., 20., 25., 30., 35., 40., 45., 60., 80., 120.),
    ZmassWindow = cms.vdouble(60., 120.), 
    useNonNominal = cms.bool(False), ## Added from HH 3l channel 
    # METScaleSyst   = cms.double(0.10), ## MET Syst set to 10% (NOT USED SINCE RUNING ON DI-LEPTON EVENTS WITH 0 MET)  
    ## -------------------------------
    cfgMEtFilter = cms.PSet(),   ## NEEDED TO FILTER OUT ANOMALOUS MET EVENTS FROM THE DATA  (Added at the bottom for TTbar_DiLepton)
    cfgEvtYieldHistManager = cms.PSet(), ## Added by the code at the bottom (NOT NEEDED IN THE .CC FILE)
    triggerWhiteList = cms.PSet(), ## NEEDED FOR DATA IN BOTH CHARGE FLIP AND LEPTON FAKE RATE CODE

    lep_mva_wp       = cms.string('hh_multilepton'),
    lep_mva_cut_mu   = cms.double(0.5), ## THESE ARE SET TO HH MULTI-LEPTON ANALYSIS
    lep_mva_cut_e    = cms.double(0.3), ## THESE ARE SET TO HH MULTI-LEPTON ANALYSIS

    evtWeight = cms.PSet(
        apply = cms.bool(False),
        histogramFile = cms.string(''),
        histogramName = cms.string(''),
        branchNameXaxis = cms.string(''),
        branchNameYaxis = cms.string(''),
        branchTypeXaxis = cms.string(''),
        branchTypeYaxis = cms.string(''),
    ),

    applyFakeRateWeights = cms.string('disabled'),
    leptonFakeRateWeight = cms.PSet(   ## THIS PSET WAS NOT SET IN EVEN IN SIDDESH'S CHARGE FLIP E CODE
        inputFileName = cms.string(""),
        histogramName_e = cms.string(""),
        histogramName_mu = cms.string(""),
        era = cms.string(""),
        applyNonClosureCorrection = cms.bool(True),
    ),


    branchName_electrons = cms.string('Electron'),
    branchName_muons = cms.string('Muon'),
    branchName_jets = cms.string('Jet'),
    branchName_hadTaus = cms.string('Tau'), ## NEW LINE
    branchName_met = cms.string('MET'),
    branchName_vertex = cms.string('PV'),

    branchName_genmet = cms.string('GenMET'),
    branchName_genTauLeptons = cms.string('GenTau'),
    branchName_genHadTaus = cms.string('GenVisTau'),
    branchName_genLeptons = cms.string('GenLep'),

    branchName_genPhotons = cms.string('GenPhoton'),
    branchName_genJets = cms.string('GenJet'),
    branchName_muonGenMatch     = cms.string('MuonGenMatch'),
    branchName_electronGenMatch = cms.string('ElectronGenMatch'),
    branchName_hadTauGenMatch   = cms.string('TauGenMatch'), ## NEW LINE
    branchName_jetGenMatch      = cms.string('JetGenMatch'), ## NEW LINE

    tHweights = cms.VPSet(),

    selEventsFileName_input = cms.string(''),
    selEventsFileName_output = cms.string('out_dyjets.txt'),
)



