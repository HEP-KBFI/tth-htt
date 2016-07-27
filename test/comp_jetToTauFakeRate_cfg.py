import FWCore.ParameterSet.Config as cms

import os

process = cms.PSet()

process.fwliteInput = cms.PSet(
    fileNames = cms.vstring(),
    
    maxEvents = cms.int32(-1),
    
    outputEvery = cms.uint32(100000)
)

process.fwliteOutput = cms.PSet(
    fileName = cms.string('comp_jetToTauFakeRate.root')
)

process.comp_jetToTauFakeRate = cms.PSet(

    looseRegion = cms.string("jetToTauFakeRate_OS/denominator/"),
    tightRegion = cms.string("jetToTauFakeRate_OS/numerator/"),

    processData = cms.string("data_obs"),    
    processesToSubtract = cms.vstring(
        "TT_t",
        "TT_l", 
        "EWK",
        "Rares",
        "TTW",
        "TTZ",
        "signal"
    ),

    hadTauSelections = cms.vstring(
        "dR05isoLoose",
        "dR05isoMedium",
        "dR05isoTight",
        "dR03mvaVLoose",
        "dR03mvaLoose",
        "dR03mvaMedium",
        "dR03mvaTight",
        "dR03mvaVTight",
        "dR03mvaVVTight"
    ),
    hadTauAbsEtaBins = cms.vdouble(-1., 1.2, 1.7, 9.9),

    isMC = cms.bool(False),

    histogramsToFit = cms.vstring("jets/pt"),

    fitFunction = cms.string("[0] + [1]*x"),
    xMin = cms.double(0.),
    xMax = cms.double(200.)
)
