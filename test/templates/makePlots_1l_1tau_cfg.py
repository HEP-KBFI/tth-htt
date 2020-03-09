import FWCore.ParameterSet.Config as cms

from tthAnalysis.HiggsToTauTau.configs.makePlots_cfi import process

process.makePlots.distributions.extend([
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
    cms.PSet(
        histogramName = cms.string('sel/evt/$PROCESS/mvaOutput_Legacy_6'),
        xAxisTitle = cms.string('MVA'),
        yAxisTitle = cms.string('dN/dMVA')
    ),
])

process.makePlots.distributions = cms.VPSet(
    distribution for distribution in process.makePlots.distributions \
    if distribution.histogramName.configValue().strip("'").startswith('sel/evt/')
)
