import FWCore.ParameterSet.Config as cms

import os

process = cms.PSet()

process.fwliteInput = cms.PSet(
    fileNames = cms.vstring(),
    maxEvents = cms.int32(-1),
    outputEvery = cms.uint32(100000)
)

process.fwliteOutput = cms.PSet(
    fileName = cms.string('')
)

process.addBackgroundLeptonFakes = cms.PSet(

    categories = cms.VPSet(
        cms.PSet(
            signal = cms.string(""),
            sideband = cms.string("")
        ),
    ),

    processData = cms.string("data_obs"),
    processLeptonFakes = cms.string("data_fakes"),
    processesToSubtract = cms.vstring(),
    sysShifts = cms.vstring(),
    makeBinContentsPositive_forTailFit = cms.bool(False) ## DISABLE makeBinContentsPositive BY DEFAULT
)
