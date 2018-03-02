import FWCore.ParameterSet.Config as cms

import os

from tthAnalysis.HiggsToTauTau.makePlots_mcClosure_cfg import process

process.makePlots_mcClosure.processesBackground = cms.vstring(
    ##"TT",
    "TTW",
    "TTZ",
    "EWK",
    "Rares",
    "fakes_data"
)
process.makePlots_mcClosure.processSignal = cms.string("signal")

process.makePlots_mcClosure.categories = cms.VPSet(
    cms.PSet(
        name = cms.string("4l_OS_Fakeable_mcClosure_wFakeRateWeights"),
        label = cms.string("4l")
    )
)

process.makePlots_mcClosure.distributions.extend([
    cms.PSet(
        histogramName = cms.string("sel/evt/$PROCESS/numJets"),
        xAxisTitle = cms.string("jet Multiplicity"),
        yAxisTitle = cms.string("N")
    )
])


