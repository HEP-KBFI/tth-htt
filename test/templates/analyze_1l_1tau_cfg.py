import FWCore.ParameterSet.Config as cms
import os

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

process.analyze_1l_1tau = cms.PSet(
    treeName = cms.string('Events'),

    process = cms.string(''),

    histogramDir = cms.string(''),

    era = cms.string(''),

    triggers_1e = cms.vstring(),
    use_triggers_1e = cms.bool(True),
    triggers_1e1tau = cms.vstring(),
    use_triggers_1e1tau = cms.bool(False),
    triggers_1mu = cms.vstring(),
    use_triggers_1mu = cms.bool(True),
    triggers_1mu1tau = cms.vstring(),
    use_triggers_1mu1tau = cms.bool(False),

    apply_offline_e_trigger_cuts_1e = cms.bool(True),
    apply_offline_e_trigger_cuts_1e1tau = cms.bool(True),
    apply_offline_e_trigger_cuts_1mu = cms.bool(True),
    apply_offline_e_trigger_cuts_1mu1tau = cms.bool(True),

    electronSelection = cms.string(''),
    muonSelection = cms.string(''),
    apply_leptonGenMatching = cms.bool(False),

    hadTauSelection = cms.string(''),
    hadTauSelection_veto = cms.string(''),
    hadTauChargeSelection = cms.string(''),
    apply_hadTauGenMatching = cms.bool(False),

    applyFakeRateWeights = cms.string(""),
    leptonFakeRateWeight = cms.PSet(
        inputFileName = cms.string(""),
        histogramName_e = cms.string(""),
        histogramName_mu = cms.string(""),
    ),
    hadTauFakeRateWeight = cms.PSet(
        inputFileName = cms.string(""),
        lead = cms.PSet(
            absEtaBins = cms.vdouble(-1., 1.479, 9.9),
            graphName = cms.string("jetToTauFakeRate/$hadTauSelection/$etaBin/jetToTauFakeRate_mc_hadTaus_pt"),
            applyGraph = cms.bool(True),
            fitFunctionName = cms.string("jetToTauFakeRate/$hadTauSelection/$etaBin/fitFunction_data_div_mc_hadTaus_pt"),
            applyFitFunction = cms.bool(True),
        )
    ),

    isMC = cms.bool(False),
    central_or_shift = cms.string(''),
    evtCategories = cms.vstring(),
    lumiScale = cms.VPSet(),
    apply_genWeight = cms.bool(True),
    apply_DYMCReweighting = cms.bool(False),
    apply_DYMCNormScaleFactors = cms.bool(False),
    apply_topPtReweighting = cms.bool(False),
    apply_hlt_filter = cms.bool(False),
    apply_l1PreFireWeight = cms.bool(True),
    apply_met_filters = cms.bool(True),
    cfgMEtFilter = cms.PSet(),
    apply_hadTauFakeRateSF = cms.bool(False),

    fillGenEvtHistograms = cms.bool(False),
    cfgEvtYieldHistManager = cms.PSet(),

    branchName_electrons = cms.string('Electron'),
    branchName_muons = cms.string('Muon'),
    branchName_hadTaus = cms.string('Tau'),
    branchName_jets = cms.string('Jet'),
    branchName_jetsHTTv2 = cms.string('HTTV2'),
    branchName_subjetsHTTv2 = cms.string('HTTV2Subjets'),
    branchName_jetsAK12 = cms.string('FatJetAK12'),
    branchName_subjetsAK12 = cms.string('SubJetAK12'),
    branchName_jetsAK8 = cms.string('FatJet'),
    branchName_subjetsAK8 = cms.string('SubJet'),
    branchName_met = cms.string('MET'),

    branchName_genLeptons = cms.string('GenLep'),
    branchName_genHadTaus = cms.string('GenVisTau'),
    branchName_genPhotons = cms.string('GenPhoton'),
    branchName_genJets = cms.string('GenJet'),
    branchName_muonGenMatch     = cms.string('MuonGenMatch'),
    branchName_electronGenMatch = cms.string('ElectronGenMatch'),
    branchName_hadTauGenMatch   = cms.string('TauGenMatch'),
    branchName_jetGenMatch      = cms.string('JetGenMatch'),
    redoGenMatching = cms.bool(True),
    genMatchingByIndex = cms.bool(True),
    jetCleaningByIndex = cms.bool(True),

    branchName_genTauLeptons = cms.string('GenTau'),
    branchName_genTopQuarks = cms.string('GenTop'),
    branchName_genBJets = cms.string('GenBQuarkFromTop'),
    branchName_genWBosons = cms.string('GenVbosons'),
    branchName_genWJets = cms.string('GenWZQuark'),
    branchName_genQuarkFromTop = cms.string('GenQuarkFromTop'),

    selEventsFileName_input = cms.string(''),
    selEventsFileName_output = cms.string(''),
    selectBDT = cms.bool(False),

    syncNtuple = cms.PSet(
        output = cms.string(''),
        options = cms.VPSet(
            cms.PSet(
                tree = cms.string(''),
                genMatch = cms.vstring(),
            ),
        ),
    ),
    useNonNominal = cms.bool(False),
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
    hhWeight_cfg = cms.PSet(
        denominator_file = cms.string(''),
        klScan_file      = cms.string('hhAnalysis/multilepton/data/kl_scan.dat'),
        ktScan_file      = cms.string(''),
        coefFile         = cms.string('HHStatAnalysis/AnalyticalModels/data/coefficientsByBin_extended_3M_costHHSim_19-4.txt'),
        histtitle        = cms.string(''),
        isDEBUG          = cms.bool(False),
        do_scan          = cms.bool(True),
        do_ktscan        = cms.bool(False),
        apply_rwgt       = cms.bool(False),
    ),


)
