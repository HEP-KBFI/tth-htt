import FWCore.ParameterSet.Config as cms

import os

process = cms.PSet()

process.fwliteInput = cms.PSet(
    fileNames = cms.vstring()
)

process.fwliteOutput = cms.PSet(
    fileName = cms.string('')
)

process.addSystDatacards = cms.PSet(
    category = cms.string(""),
    histogramToFit = cms.string(""),

    addSyst = cms.VPSet(
        cms.PSet(
            name = cms.string(""),
            categories = cms.vstring(""),
            processes = cms.vstring(""),
            histogramsToFit = cms.vstring(""),
            inputFileName = cms.string(""),
            histogramName = cms.string(""),
        ),
    )
)
