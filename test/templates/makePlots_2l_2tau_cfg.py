import FWCore.ParameterSet.Config as cms

from tthAnalysis.HiggsToTauTau.configs.makePlots_cfi import process

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
        explicitBinning = cms.vdouble([ 0.0, 0.25, 0.50, 0.75, 1.0 ]),
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
        histogramName = cms.string("sel/evt/$PROCESS/mvaOutput_final"),
        xAxisTitle = cms.string("MVA Discriminant"),
        yAxisTitle = cms.string("dN/dMVA")
    ),
])
