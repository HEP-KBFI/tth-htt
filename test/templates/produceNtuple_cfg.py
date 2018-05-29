import FWCore.ParameterSet.Config as cms

process = cms.PSet()

process.fwliteInput = cms.PSet(
    fileNames   = cms.vstring(''),
    maxEvents   = cms.int32(-1),
    outputEvery = cms.uint32(100000)
)

process.fwliteOutput = cms.PSet(
    fileName = cms.string('produceNtuple.root')
)

process.produceNtuple = cms.PSet(
    treeName = cms.string('Events'),

    era = cms.string('2017'),

    leptonSelection = cms.string('Fakeable'),
    hadTauSelection = cms.string('Fakeable|dR03mvaMedium'),

    minNumLeptons             = cms.int32(1),
    minNumHadTaus             = cms.int32(1),
    minNumLeptons_and_HadTaus = cms.int32(2),
    minNumJets                = cms.int32(2),
    minNumBJets_loose         = cms.int32(2),
    minNumBJets_medium        = cms.int32(1),

    branchName_electrons  = cms.string('Electron'),
    branchName_muons      = cms.string('Muon'),
    branchName_hadTaus    = cms.string('Tau'),
    branchName_jets       = cms.string('Jet'),
    branchName_met        = cms.string('MET'),
    branchName_genLeptons = cms.string('GenLep'),
    branchName_genPhotons = cms.string('GenPhoton'),
    branchName_genHadTaus = cms.string('GenVisTau'),
    branchName_genJets    = cms.string('GenJet'),

    isMC = cms.bool(True),

    selEventsFileName_input = cms.string(''),

    drop_branches = cms.vstring(),
    copy_histograms = cms.vstring(
        "Count",
        "CountFullWeighted",
        "CountWeighted",
        "CountPosWeight",
        "CountNegWeight",
        "CountWeightedLHEWeightScale",
        "CountWeightedLHEWeightPdf",
    ),

    random_seed = cms.uint32(4357),
    useNonNominal = cms.bool(False),
    isDEBUG = cms.bool(False),
)
