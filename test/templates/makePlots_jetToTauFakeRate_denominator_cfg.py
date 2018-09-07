import FWCore.ParameterSet.Config as cms

from tthAnalysis.HiggsToTauTau.configs.makePlots_cfi import process

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
