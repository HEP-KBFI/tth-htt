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

    looseRegion = cms.string(""),
    tightRegion = cms.string(""),

    processData = cms.string("data_obs"),
    processesToSubtract = cms.vstring(),

    processMC = cms.string("TTj"),

    hadTauSelections = cms.vstring(
        "dR03mvaLoose",
        "dR03mvaMedium",
        "dR03mvaTight",
        "dR03mvaVTight",
        "dR03mvaVVTight"
    ),

    absEtaBins = cms.vdouble(),
    ptBins = cms.vdouble(),

    isMC = cms.bool(False),

    histogramsToFit = cms.vstring("hadTaus/pt"),

    fitFunction = cms.string("[0] + [1]*x"),
    xMin = cms.double(0.),
    xMax = cms.double(200.),

    outputFileName = cms.string("")
)
