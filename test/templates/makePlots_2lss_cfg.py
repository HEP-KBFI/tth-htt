import FWCore.ParameterSet.Config as cms

import os

from tthAnalysis.HiggsToTauTau.configs.makePlots_cfi import process

process.makePlots.processesBackground = cms.vstring(
    ##"TT",
    "TTW",
    "TTZ",
    "EWK",
    "Rares",
    "conversions",
    "fakes_data",
    "flips_data"
)
process.makePlots.processSignal = cms.string("signal")

process.makePlots.categories = cms.VPSet(
    cms.PSet(
        name = cms.string("2lss_SS_Tight"),
        label = cms.string("2lss")
    )
)

process.makePlots.distributions.extend([
    cms.PSet(
        histogramName = cms.string("sel/evt/$PROCESS/mvaDiscr_2lss"),
        xAxisTitle = cms.string("MVA Discriminant"),
        yAxisTitle = cms.string("N")
    )
])

process.makePlots.nuisanceParameters.normalization = cms.PSet(
    signal = cms.string("1.0 +/- 0.20"),
    TT = cms.string("1.0 +/- 0.20"),
    TTW = cms.string("1.0 +/- 0.20"),
    TTWW = cms.string("1.0 +/- 0.20"),
    TTZ = cms.string("1.0 +/- 0.20"),
    EWK = cms.string("1.0 +/- 0.20"),
    Rares = cms.string("1.0 +/- 0.20"),
    conversions = cms.string("1.0 +/- 0.20"),
    fakes_data = cms.string("1.0 +/- 0.20"),
    flips_data = cms.string("1.0 +/- 0.20")
)
