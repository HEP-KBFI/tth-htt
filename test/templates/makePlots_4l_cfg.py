import FWCore.ParameterSet.Config as cms

from tthAnalysis.HiggsToTauTau.configs.makePlots_cfi import process

process.makePlots.distributions.extend([
    cms.PSet(
        histogramName = cms.string("sel/evt/$PROCESS/mva_4l"),
        xAxisTitle = cms.string("MVA Discriminant (4l)"),
        yAxisTitle = cms.string("dN/dMVA")
    ),
    cms.PSet(
        histogramName = cms.string('sel/evt/$PROCESS/massL'),
        xAxisTitle = cms.string('m_{#ell} [GeV]'),
        yAxisTitle = cms.string('dN/dm_{#ell} [1/GeV]')
    ),
])
