import FWCore.ParameterSet.Config as cms

import os

process = cms.PSet()

process.fwliteInput = cms.PSet(
    fileNames = cms.vstring()
)

process.fwliteOutput = cms.PSet(
    fileName = cms.string('')
)

process.addSystFakeRates = cms.PSet(

    process = cms.string("data_fakes"),

    category = cms.string(''),
    histogramToFit = cms.string(""),
    xAxisTitle = cms.string(""),
    yAxisTitle = cms.string(""),

    addSyst = cms.VPSet(
        cms.PSet(
            name = cms.string(""),
            fakes_mc = cms.PSet(
                inputFileName = cms.vstring(),
                histogramName = cms.string(""),
            ),
            mcClosure = cms.PSet(
                inputFileName = cms.vstring(),
                histogramName = cms.string(""),
            )
        ),
    ),

    outputFileName = cms.string("")
)
