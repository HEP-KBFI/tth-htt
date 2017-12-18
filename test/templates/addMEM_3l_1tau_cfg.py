import FWCore.ParameterSet.Config as cms

process = cms.PSet()

process.fwliteInput = cms.PSet(
    fileNames = cms.vstring(''),
    skipEvents = cms.uint32(0),
    maxEvents = cms.int32(-1),
    outputEvery = cms.uint32(1000)
)

process.fwliteOutput = cms.PSet(
    fileName = cms.string('addMEM_3l_1tau.root')
)

process.addMEM_3l_1tau = cms.PSet(
    treeName = cms.string('Events'),

    era = cms.string('2017'),

    leptonSelection = cms.string('Fakeable'),

    hadTauSelection = cms.string('Tight|dR03mvaMedium'),

    isMC = cms.bool(True),

    branchName_electrons = cms.string('Electron'),
    branchName_muons = cms.string('Muon'),
    branchName_hadTaus = cms.string('HadTau'),
    branchName_jets = cms.string('Jet'),
    branchName_met = cms.string('met'),

    copy_all_branches = cms.bool(True),

    copy_histograms = cms.vstring(
        "Count",
        "CountFullWeighted",
        "CountWeighted",
        "CountPosWeight",
        "CountNegWeight",
        "CountWeightedLHEWeightScale",
        "CountWeightedLHEWeightPdf",
    ),

    selEventsFileName_input = cms.string(''),
    isDEBUG = cms.bool(False),
    readGenObjects = cms.bool(True),

    central_or_shift = cms.vstring(
        "central",
    )
)
