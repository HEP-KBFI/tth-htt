import FWCore.ParameterSet.Config as cms

import os

process = cms.PSet()

process.fwliteInput = cms.PSet(
    fileNames = cms.vstring()
)

process.fwliteOutput = cms.PSet(
    fileName = cms.string('')
)

process.addBackgrounds = cms.PSet(
    categories = cms.vstring(),
    processes_input = cms.vstring(),
    process_output = cms.string(''),
    sysShifts = cms.vstring(
    ),
)
