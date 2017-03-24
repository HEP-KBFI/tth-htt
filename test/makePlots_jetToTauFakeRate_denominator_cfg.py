import FWCore.ParameterSet.Config as cms

import os

from tthAnalysis.HiggsToTauTau.makePlots_cfi import process

process.makePlots.processesBackground = cms.vstring(
    "TT",
    "TTW",
    "TTZ",
    "EWK",
    "Rares",
)
process.makePlots.processSignal = cms.string("signal")

process.makePlots.categories = cms.VPSet(
    cms.PSet(
        name = cms.string("jetToTauFakeRate_OS"),
        label = cms.string("jet #rightarrow #tau_{h} CR")
    )
)

process.makePlots.distributions = cms.VPSet(
    cms.PSet(
        histogramName = cms.string("evt/$PROCESS/numHadTaus"),
        xAxisTitle = cms.string("#tau_{h} Multiplicity"),
        yAxisTitle = cms.string("N")
    ),
    cms.PSet(
        histogramName = cms.string("hadTaus/$PROCESS/pt"),
        xMin = cms.double(20.),
        xMax = cms.double(200.),
        xAxisTitle = cms.string("#tau_{h} p_{T} [GeV]"),
        yAxisTitle = cms.string("dN/dp_{T} [1/GeV]")
    ),
    cms.PSet(
        histogramName = cms.string("hadTaus/$PROCESS/eta"),
        xAxisTitle = cms.string("#tau_{h} #eta"),
        yAxisTitle = cms.string("dN/d#eta")
    ),
    cms.PSet(
        histogramName = cms.string("hadTaus/$PROCESS/phi"),
        xAxisTitle = cms.string("#tau_{h} #phi"),
        yAxisTitle = cms.string("dN/d#phi")
    )
)

process.makePlots.nuisanceParameters.normalization = cms.PSet(
    signal = cms.string("1.0 +/- 0.20"),
    TT = cms.string("1.0 +/- 0.20"),
    TTW = cms.string("1.0 +/- 0.20"),
    TTZ = cms.string("1.0 +/- 0.20"),
    EWK = cms.string("1.0 +/- 0.20"),
    Rares = cms.string("1.0 +/- 0.20")
)


