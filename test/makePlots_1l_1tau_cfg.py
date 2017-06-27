import FWCore.ParameterSet.Config as cms

import os

from tthAnalysis.HiggsToTauTau.makePlots_cfi import process

process.makePlots.processesBackground = cms.vstring(
    ##"TT",
    "TTW",
    "TTZ",
    "EWK",
    "Rares",
    "fakes_data"
)
process.makePlots.processSignal = cms.string("signal")

process.makePlots.categories = cms.VPSet(
    cms.PSet(
        name = cms.string("1l_1tau_OS_Tight"),
        label = cms.string("1l_1tau")
    )
)

process.makePlots.distributions.extend([
    cms.PSet(
        histogramName = cms.string('sel/evt/$PROCESS/mvaOutput_1l_1tau_ttbar'),
        xAxisTitle = cms.string('MVA'),
        yAxisTitle = cms.string('dN/dMVA')
    ),
    cms.PSet(
        histogramName = cms.string('sel/evt/$PROCESS/mTauTauVis'),
        xAxisTitle = cms.string('m_{#tau#tau}^{vis} [GeV]'),
        yAxisTitle = cms.string('dN/dm_{#tau#tau}^{vis} [1/GeV]')
    ),
    cms.PSet(
        histogramName = cms.string('sel/evt/$PROCESS/mTauTau'),
        xAxisTitle = cms.string('m_{#tau#tau} [GeV]'),
        yAxisTitle = cms.string('dN/dm_{#tau#tau} [1/GeV]')
    ),
])
