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

    looseRegion = cms.string("SS_Fakeable"),
    tightRegion = cms.string("SS_Tight"),

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
    processFakes = cms.string("fakes_data"),

    hadTauEtaBins_lead = cms.vdouble(-1., 1.2, 1.7, 9.9),
    hadTauEtaBins_sublead = cms.vdouble(-1., 1.2, 1.7, 9.9),
    
    histogramsToFit = cms.vstring(
        "hadTauPt_lead",
        "hadTauPt_sublead"
    ),

    fitFunction = cms.string("[0] + [1]*x"),
    xMin = cms.double(0.),
    xMax = cms.double(200.)
)
