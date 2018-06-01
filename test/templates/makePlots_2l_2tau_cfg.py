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
    "fakes_data"
)
process.makePlots.processSignal = cms.string("signal")

process.makePlots.categories = cms.VPSet(
    cms.PSet(
        name = cms.string("2l_2tau_sumOS_Tight"),
        label = cms.string("2l_2tau")
    )
)

process.makePlots.distributions.extend([
    cms.PSet(
        histogramName = cms.string('sel/evt/$PROCESS/leptonPairCharge'),
        xAxisTitle = cms.string('lepton charge sum'),
        yAxisTitle = cms.string('N')
    ),
    cms.PSet(
        histogramName = cms.string('sel/evt/$PROCESS/hadTauPairCharge'),
        xAxisTitle = cms.string('#tau_{h} charge sum'),
        yAxisTitle = cms.string('N')
    ),
    cms.PSet(
        histogramName = cms.string('sel/evt/$PROCESS/mTauTauVis'),
        xAxisTitle = cms.string('m_{#tau#tau}^{vis} [GeV]'),
        yAxisTitle = cms.string('dN/dm_{#tau#tau}^{vis} [1/GeV]')
    ),
    cms.PSet(
        histogramName = cms.string("sel/evt/$PROCESS/mvaOutput_plainKin_tt"),
        xAxisTitle = cms.string("MVA Discriminant"),
        yAxisTitle = cms.string("dN/dMVA")
    ),
    cms.PSet(
        histogramName = cms.string("sel/evt/$PROCESS/mvaOutput_plainKin_ttV"),
        xAxisTitle = cms.string("MVA Discriminant"),
        yAxisTitle = cms.string("dN/dMVA")
    ),
    cms.PSet(
        histogramName = cms.string("sel/evt/$PROCESS/mvaOutput_plainKin_SUM_VT"),
        xAxisTitle = cms.string("MVA Discriminant"),
        yAxisTitle = cms.string("dN/dMVA"),
        explicitBinning = cms.vdouble([0.0, 0.35, 0.41, 0.47, 1.0]),
    ),
    cms.PSet(
        histogramName = cms.string("sel/evt/$PROCESS/mvaOutput_plainKin_1B_VT"),
        xAxisTitle = cms.string("MVA Discriminant"),
        yAxisTitle = cms.string("dN/dMVA")
    ),
    cms.PSet(
        histogramName = cms.string("sel/evt/$PROCESS/mvaOutput_plainKin_SUM_VT_noRebin"),
        xAxisTitle = cms.string("MVA Discriminant"),
        yAxisTitle = cms.string("dN/dMVA")
    ),
    cms.PSet(
        histogramName = cms.string("sel/evt/$PROCESS/mvaOutput_plainKin_1B_VT_4bins_quantiles"),
        xAxisTitle = cms.string("MVA Discriminant"),
        yAxisTitle = cms.string("dN/dMVA")
    ),
])
