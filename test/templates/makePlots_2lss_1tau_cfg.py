import FWCore.ParameterSet.Config as cms

from tthAnalysis.HiggsToTauTau.configs.makePlots_cfi import process

process.makePlots.distributions.extend([
    cms.PSet(
        histogramName = cms.string("sel/evt/$PROCESS/mvaOutput_2lss_ttV"),
        xAxisTitle = cms.string("MVA Discriminant (2lss ttV)"),
        yAxisTitle = cms.string("dN/dMVA")
    ),
    cms.PSet(
        histogramName = cms.string("sel/evt/$PROCESS/mvaOutput_2lss_tt"),
        xAxisTitle = cms.string("MVA Discriminant (2lss tt)"),
        yAxisTitle = cms.string("dN/dMVA")
    ),
    cms.PSet(
        histogramName = cms.string("sel/evt/$PROCESS/mvaOutput_2lss_1tau_plainKin_tt"),
        xAxisTitle = cms.string("MVA Discriminant (2lss tt)"),
        yAxisTitle = cms.string("dN/dMVA")
    ),
    cms.PSet(
        histogramName = cms.string("sel/evt/$PROCESS/mvaOutput_2lss_1tau_plainKin_ttV"),
        xAxisTitle = cms.string("MVA Discriminant (2lss tt)"),
        yAxisTitle = cms.string("dN/dMVA")
    ),
    cms.PSet(
        histogramName = cms.string("sel/evt/$PROCESS/mvaOutput_2lss_1tau_plainKin_1B_M"),
        xAxisTitle = cms.string("MVA Discriminant (2lss tt)"),
        yAxisTitle = cms.string("dN/dMVA")
    ),
    cms.PSet(
        histogramName = cms.string("sel/evt/$PROCESS/mvaOutput_2lss_1tau_plainKin_SUM_M"),
        xAxisTitle = cms.string("MVA Discriminant (2lss tt)"),
        yAxisTitle = cms.string("dN/dMVA")
    ),
    cms.PSet(
        histogramName = cms.string("sel/evt/$PROCESS/mvaOutput_2lss_1tau_plainKin_SUM_M_noRebin"),
        xAxisTitle = cms.string("MVA Discriminant (2lss tt)"),
        yAxisTitle = cms.string("dN/dMVA")
    ),
    cms.PSet(
        histogramName = cms.string("sel/evt/$PROCESS/mvaOutput_2lss_1tau_HTT_SUM_M"),
        xAxisTitle = cms.string("MVA Discriminant (2lss tt)"),
        yAxisTitle = cms.string("dN/dMVA")
    ),
    cms.PSet(
        histogramName = cms.string("sel/evt/$PROCESS/mvaOutput_2lss_1tau_HTT_SUM_M_noRebin"),
        xAxisTitle = cms.string("MVA Discriminant (2lss tt)"),
        yAxisTitle = cms.string("dN/dMVA")
    ),
    cms.PSet(
        histogramName = cms.string("sel/evt/$PROCESS/mvaOutput_2lss_1tau_HTTMEM_SUM_M"),
        xAxisTitle = cms.string("MVA Discriminant (2lss tt)"),
        yAxisTitle = cms.string("dN/dMVA")
    ),
    cms.PSet(
        histogramName = cms.string("sel/evt/$PROCESS/mvaOutput_2lss_1tau_HTTMEM_SUM_M"),
        xAxisTitle = cms.string("MVA Discriminant (2lss tt)"),
        yAxisTitle = cms.string("dN/dMVA")
    ),
    cms.PSet(
        histogramName = cms.string("sel/evt/$PROCESS/mvaOutput_2lss_1tau_HTTMEM_SUM_M_noRebin"),
        xAxisTitle = cms.string("MVA Discriminant (2lss tt)"),
        yAxisTitle = cms.string("dN/dMVA")
    ),
    cms.PSet(
        histogramName = cms.string("sel/evt/$PROCESS/mvaOutput_final"),
        xAxisTitle = cms.string("MVA Discriminant (2lss tt)"),
        yAxisTitle = cms.string("dN/dMVA")
    ),
    cms.PSet(
        histogramName = cms.string("sel/evt/$PROCESS/mTauTauVis1"),
        xAxisTitle = cms.string("m_{#tau#tau}^{vis} [GeV]"),
        yAxisTitle = cms.string("dN/dm_{#tau#tau}^{vis} [1/GeV]")
    ),
    cms.PSet(
        histogramName = cms.string("sel/evt/$PROCESS/mTauTauVis2"),
        xAxisTitle = cms.string("m_{#tau#tau}^{vis} [GeV]"),
        yAxisTitle = cms.string("dN/dm_{#tau#tau}^{vis} [1/GeV]")
    ),
    cms.PSet(
        histogramName = cms.string("sel/evt/$PROCESS/mTauTauVis"),
        xAxisTitle = cms.string("m_{#tau#tau}^{vis} [GeV]"),
        yAxisTitle = cms.string("dN/dm_{#tau#tau}^{vis} [1/GeV]")
    ),
])
