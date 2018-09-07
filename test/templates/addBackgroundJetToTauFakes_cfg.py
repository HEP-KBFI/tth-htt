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
            signal = cms.string("1l_2tau_OS_Tight"),
            sideband = cms.string("1l_2tau_OS_Fakeable_wFakeRateWeights")
        )
    ),
    processData = cms.string("data_obs"),
    processLeptonFakes = cms.string("fakes_data"),
    processesToSubtract = cms.vstring(
        "TT",
        "TTW",
        "TTZ",
        "EWK",
        "Rares"
    ),
    sysShifts = cms.vstring()
)
