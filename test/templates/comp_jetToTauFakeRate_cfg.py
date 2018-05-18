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
        "TTt",
        "TTl", 
        "EWK",
        "Rares",
        "TTW",
        "TTZ",
        "signal"
    ),

    processMC = cms.string("TTj"),
    
    hadTauSelections = cms.vstring(
        #"dR03mvaVLoose", # CV: VLoose discriminator applied in denominator; so cannot be used in numerator
        "dR03mvaLoose", # CV: Loose discriminator applied in denominator, so cannot be used in numerator
        "dR03mvaMedium",
        "dR03mvaTight",
        "dR03mvaVTight",
        "dR03mvaVVTight"
    ),
    
    absEtaBins = cms.vdouble(-1., 1.479, 9.9),
    ptBins = cms.vdouble(20., 25., 30., 35., 40., 45., 50., 60., 70., 80., 100., 200.),

    isMC = cms.bool(False),

    histogramsToFit = cms.vstring("hadTaus/pt"),

    fitFunction = cms.string("[0] + [1]*x"),
    xMin = cms.double(0.),
    xMax = cms.double(200.),

    outputFileName = cms.string("plots/comp_jetToTauFakeRate.png")
)
