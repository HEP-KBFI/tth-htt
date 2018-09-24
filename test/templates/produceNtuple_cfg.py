import FWCore.ParameterSet.Config as cms

process = cms.PSet()

process.fwliteInput = cms.PSet(
    fileNames   = cms.vstring(),
    maxEvents   = cms.int32(-1),
    outputEvery = cms.uint32(100000)
)

process.fwliteOutput = cms.PSet(
    fileName = cms.string('')
)

process.produceNtuple = cms.PSet(
    treeName = cms.string('Events'),

    era = cms.string(''),

    leptonSelection = cms.string(''),
    hadTauSelection = cms.string(''),

    minNumLeptons             = cms.int32(-1),
    minNumHadTaus             = cms.int32(-1),
    minNumLeptons_and_HadTaus = cms.int32(-1),
    minNumJets                = cms.int32(-1),
    minNumBJets_loose         = cms.int32(-1),
    minNumBJets_medium        = cms.int32(-1),
    maxNumBJets_loose         = cms.int32(-1),
    maxNumBJets_medium        = cms.int32(-1),
    applyJetEtaCut            = cms.bool(True),

    branchName_electrons  = cms.string('Electron'),
    branchName_muons      = cms.string('Muon'),
    branchName_hadTaus    = cms.string('Tau'),
    branchName_jets       = cms.string('Jet'),
    branchName_met        = cms.string('MET'),
    branchName_genLeptons = cms.string('GenLep'),
    branchName_genPhotons = cms.string('GenPhoton'),
    branchName_genHadTaus = cms.string('GenVisTau'),
    branchName_genJets    = cms.string('GenJet'),

    # Define trigger branches that are always written to the output file, even if they do not exist in the input file.
    # This logic simplifies the configuration of analysis jobs to handle the case
    # that some triggers appear/disappear in the middle of a data-taking period, e.g. 2017RunB
    # (in this case the trigger decision is set to false for all events in each input file where the trigger branch is missing)
    branchNames_triggers = cms.vstring(),

    isMC = cms.bool(True),
    readGenMatching = cms.bool(False),

    selEventsFileName_input = cms.string(''),

    drop_branches = cms.vstring(),
    copy_histograms = cms.vstring(
        "Count",
        "CountPosWeight",
        "CountNegWeight",
        "CountWeighted",
        "CountWeightedNoPU",
        "CountFullWeighted",
        "CountFullWeightedNoPU",
        "CountWeightedLHEWeightScale",
        "CountWeightedLHEWeightScaleNoPU",
        "CountFullWeightedLHEWeightScale",
        "CountFullWeightedLHEWeightScaleNoPU",
        "CountWeightedLHEWeightPdf",
        "CountWeightedLHEWeightPdfNoPU",
        "CountFullWeightedLHEWeightPdf",
        "CountFullWeightedLHEWeightPdfNoPU",
    ),

    random_seed = cms.uint32(4357),
    useNonNominal = cms.bool(False),
    isDEBUG = cms.bool(False),
)
