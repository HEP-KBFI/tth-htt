import FWCore.ParameterSet.Config as cms

import os

process = cms.PSet()

process.fwliteInput = cms.PSet(
    fileNames = cms.vstring()
)

process.fwliteOutput = cms.PSet(
    fileName = cms.string('')
)

process.prepareDatacards = cms.PSet(

    processesToCopy = cms.vstring(),
    sf_signal = cms.double(1.),
    signals = cms.vstring(),

    categories = cms.VPSet(),
    makeSubDir = cms.bool(False),

    histogramToFit = cms.string(""),
    histogramToFit_xMin = cms.double(-1.),
    histogramToFit_xMax = cms.double(-1.),
    histogramToFit_rebin = cms.int32(1),
    histogramToFit_makeBinContentsPositive = cms.bool(True),
    apply_automatic_rebinning = cms.bool(False),
    minEvents_automatic_rebinning = cms.double(0.1),
    quantile_rebinning_in_fakes = cms.bool(False),
    nbin_quantile_rebinning = cms.int32(-1),
    explicit_binning = cms.vdouble(),
    sysShifts = cms.vstring(),
)
