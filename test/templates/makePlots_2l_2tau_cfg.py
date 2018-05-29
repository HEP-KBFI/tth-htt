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
##     cms.PSet(
##         histogramName = cms.string('sel/leadHadTau/$PROCESS/pt'),
##         xMin = cms.double(20.),
##         xMax = cms.double(200.),
##         xAxisTitle = cms.string('leading #tau_{h} p_{T} [GeV]'),
##         yAxisTitle = cms.string('dN/dp_{T} [1/GeV]')
##     ),
##     cms.PSet(
##         histogramName = cms.string('sel/leadHadTau/$PROCESS/eta'),
##         xAxisTitle = cms.string('leading #tau_{h} #eta'),
##         yAxisTitle = cms.string('dN/d#eta')
##     ),
##     cms.PSet(
##         histogramName = cms.string('sel/subleadHadTau/$PROCESS/pt'),
##         xMin = cms.double(20.),
##         xMax = cms.double(200.),
##         xAxisTitle = cms.string('subleading #tau_{h} p_{T} [GeV]'),
##         yAxisTitle = cms.string('dN/dp_{T} [1/GeV]')
##     ),
##     cms.PSet(
##         histogramName = cms.string('sel/subleadHadTau/$PROCESS/eta'),
##         xAxisTitle = cms.string('subleading #tau_{h} #eta'),
##         yAxisTitle = cms.string('dN/d#eta')
##     ),
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
        histogramName = cms.string("sel/evt/$PROCESS/mvaDiscr_2l_2tau"),
        xAxisTitle = cms.string("MVA Discriminant"),
        yAxisTitle = cms.string("N")
    )
])
