import FWCore.ParameterSet.Config as cms

from tthAnalysis.HiggsToTauTau.configs.makePlots_cfi import process

process.makePlots.distributions.extend([
    cms.PSet(
        histogramName = cms.string("sel/evt/$PROCESS/m4lep"),
        xAxisTitle = cms.string("m_{4#ell} [GeV]"),
        yAxisTitle = cms.string("dN/dm_{4#ell}")
    ),
])
