import FWCore.ParameterSet.Config as cms

import os

process = cms.PSet()

process.fwliteInput = cms.PSet(
    fileNames = cms.vstring()
)

process.fwliteOutput = cms.PSet(
    fileName = cms.string('')
)

process.copyHistograms = cms.PSet(
    categories = cms.vstring(),
)
