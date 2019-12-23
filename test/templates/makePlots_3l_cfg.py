import FWCore.ParameterSet.Config as cms

from tthAnalysis.HiggsToTauTau.configs.makePlots_cfi import process

process.makePlots.distributions.extend([
    cms.PSet(
        histogramName = cms.string("sel/evt/$PROCESS/mvaOutput_3l_ttV"),
        xAxisTitle = cms.string("MVA Discriminant (3l ttV)"),
        yAxisTitle = cms.string("dN/dMVA")
    ),
    cms.PSet(
        histogramName = cms.string("sel/evt/$PROCESS/mvaOutput_3l_ttbar"),
        xAxisTitle = cms.string("MVA Discriminant (3l tt)"),
        yAxisTitle = cms.string("dN/dMVA")
    ),
])
