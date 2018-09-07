import FWCore.ParameterSet.Config as cms

import os

process = cms.PSet()

process.fwliteInput = cms.PSet(
    fileNames = cms.vstring()
)

process.fwliteOutput = cms.PSet(
    fileName = cms.string('')
)

process.compShapeSyst = cms.PSet(
    category = cms.string(""),

    histogramsToFit = cms.vstring(),

    compSyst = cms.VPSet(
        cms.PSet(
            categories = cms.vstring(),
            processes = cms.vstring(),
            shifts = cms.vstring(),
            histogramDir = cms.string(""),
            histogramsToFit = cms.vstring(""),
            outputHistogramName1 = cms.string(""),
            outputHistogramName2 = cms.string("")
        ),
    )
)
