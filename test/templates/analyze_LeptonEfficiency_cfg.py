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
    process = cms.string(''), ## Given at the bottom for TTTo2L2Nu sample  
    era = cms.string('2016'),
    isMC = cms.bool(True),
    hasLHE = cms.bool(True),
    useObjectMultiplicity = cms.bool(True),

    lepton_type = cms.string('e'), ## 2 options: e/mu
    triggers_1e = cms.vstring(), ## Given at the bottom for TTTo2L2Nu sample 
    use_triggers_1e = cms.bool(True), ## Given at the bottom for TTTo2L2Nu sample 
    triggers_1mu = cms.vstring(), ## Given at the bottom for TTTo2L2Nu sample
    use_triggers_1mu = cms.bool(False), ## Given at the bottom for TTTo2L2Nu sample
    apply_offline_e_trigger_cuts_1e = cms.bool(True),  ## Given at the bottom for TTTo2L2Nu sample

    leptonSelection = cms.string('Tight'),
    lep_useTightChargeCut  = cms.bool(False), ## NEWLY ADDED
    central_or_shift = cms.string('central'),
    lumiScale = cms.VPSet(), ## Given at the bottom for TTTo2L2Nu sample

    ref_genWeight = cms.double(0.),
    apply_genWeight = cms.bool(True),
    apply_topPtReweighting = cms.string(''), ## Given at the bottom for TTTo2L2Nu sample
    apply_DYMCReweighting = cms.bool(False),
    apply_DYMCNormScaleFactors = cms.bool(False),
    apply_l1PreFireWeight = cms.bool(True),
    applyBtagSFRatio      = cms.bool(True),
    fillGenEvtHistograms  = cms.bool(False),
    jetCleaningByIndex    = cms.bool(True),
    redoGenMatching       = cms.bool(False),
    genMatchingByIndex    = cms.bool(False),
    isDEBUG = cms.bool(False),

    hadTauSelection = cms.string('Tight|deepVSjMedium'), ## NEW LINE
    #apply_hadTauGenMatching = cms.bool(False), ## NOT NEEDED

    ## ---------- NEW LINES ----------
    absEtaBins_e = cms.vdouble(0., 0.9, 1.2, 2.1, 2.5),
    ptBins_e = cms.vdouble(10., 15., 20., 25., 30., 35., 40., 45., 60., 80., 120.),
    absEtaBins_mu = cms.vdouble(0., 0.9, 1.2, 2.1, 2.5),
    ptBins_mu = cms.vdouble(10., 15., 20., 25., 30., 35., 40., 45., 60., 80., 120.),
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





process.fwliteInput.fileNames = cms.vstring(['/hdfs/local/karl/ttHNtupleProduction/2016/2021Feb17_woPresel_nom_all_hh_multilepton/ntuples/DYJetsToLL_M-50_ext1/0000/tree_1.root']) ## Karls' latest ntuples DYJETS

#process.analyze_LeptonEfficiency.hasPS      = cms.bool(False) ## TO BE IMPLEMENTED
#process.analyze_LeptonEfficiency.useAssocJetBtag          = cms.bool(False) ## TO BE IMPLEMENTED

process.analyze_LeptonEfficiency.process  = cms.string('EWK')
process.analyze_LeptonEfficiency.isMC       = cms.bool(True)
process.analyze_LeptonEfficiency.hasLHE     = cms.bool(True)
process.analyze_LeptonEfficiency.lumiScale  = cms.VPSet([cms.PSet(
    central_or_shift = cms.string('central'),
    lumi = cms.double(1.50848250831)
)])
process.analyze_LeptonEfficiency.apply_topPtReweighting = cms.string('')
process.analyze_LeptonEfficiency.ref_genWeight            = cms.double(1.0)
process.analyze_LeptonEfficiency.apply_genWeight            = cms.bool(True)
process.analyze_LeptonEfficiency.apply_DYMCReweighting = cms.bool(True)
process.analyze_LeptonEfficiency.apply_DYMCNormScaleFactors = cms.bool(False)
process.analyze_LeptonEfficiency.apply_l1PreFireWeight    = cms.bool(True)
process.analyze_LeptonEfficiency.jetCleaningByIndex       = cms.bool(True)
process.analyze_LeptonEfficiency.genMatchingByIndex       = cms.bool(True)

process.analyze_LeptonEfficiency.evtWeight.apply          = cms.bool(True)
process.analyze_LeptonEfficiency.evtWeight.histogramFile    = cms.string('tthAnalysis/HiggsToTauTau/data/stitched_weights_2016.root')
process.analyze_LeptonEfficiency.evtWeight.branchNameXaxis  = cms.string('LHE_Njets')
process.analyze_LeptonEfficiency.evtWeight.branchNameYaxis  = cms.string('LHE_HT')
process.analyze_LeptonEfficiency.evtWeight.branchTypeXaxis  = cms.string('UChar_t')
process.analyze_LeptonEfficiency.evtWeight.branchTypeYaxis  = cms.string('Float_t')
process.analyze_LeptonEfficiency.evtWeight.histograms     = cms.VPSet([
  cms.PSet(
    central_or_shift = cms.string('central'),
    histogramName = cms.string('DYJetsToLL_M-50_ext1/LHE_Njets_v_LHE_HT/CountWeightedFullL1PrefireNom_0'),
  ),
]
)


process.analyze_LeptonEfficiency.applyBtagSFRatio       = cms.bool(True)
process.analyze_LeptonEfficiency.btagSFRatio            = cms.PSet(
    central = cms.vdouble(1.0, 0.998505369724, 0.995340655142, 0.997527969636, 0.995310226638, 0.99267178384, 0.988262059925, 0.983708303555, 0.977140001767, 0.982957887322),
)


process.analyze_LeptonEfficiency.cfgEvtYieldHistManager = EvtYieldHistManager_2016
process.analyze_LeptonEfficiency.cfgMEtFilter           = recommendedMEtFilters_2016

## ----FOR ELECTRONS
process.analyze_LeptonEfficiency.lepton_type = cms.string('e')
process.analyze_LeptonEfficiency.triggers_1e      = cms.vstring(['HLT_Ele25_eta2p1_WPTight_Gsf', 'HLT_Ele27_WPTight_Gsf', 'HLT_Ele27_eta2p1_WPLoose_Gsf'])
process.analyze_LeptonEfficiency.use_triggers_1e  = cms.bool(True)
process.analyze_LeptonEfficiency.apply_offline_e_trigger_cuts_1e = cms.bool(True)

## ----FOR MUONS
#process.analyze_LeptonEfficiency.lepton_type = cms.string('mu')
#process.analyze_LeptonEfficiency.triggers_1mu     = cms.vstring(['HLT_IsoMu22_eta2p1', 'HLT_IsoMu22', 'HLT_IsoMu24', 'HLT_IsoTkMu22_eta2p1', 'HLT_IsoTkMu24', 'HLT_IsoTkMu22'])
#process.analyze_LeptonEfficiency.use_triggers_1mu = cms.bool(True)


process.fwliteOutput.fileName = cms.string('analyze_DYJetsToLL_M-50_ext1_central_1.root')



