import FWCore.ParameterSet.Config as cms

from tthAnalysis.HiggsToTauTau.configs.makePlots_cfi import process

process.makePlots.pluginType = cms.string("Plotter_ttH")
process.makePlots.applyRebinning = cms.bool(False)
process.makePlots.apply_automatic_rebinning = cms.bool(False)
process.makePlots.applyAutoBlinding = cms.bool(False)

process.makePlots.distributions.extend([
    cms.PSet(
        histogramName = cms.string("sel/evt/$PROCESS/numHadTaus"),
        xAxisTitle = cms.string("#tau_{h} Multiplicity"),
        yAxisTitle = cms.string("N"),
    ),
    cms.PSet(
        histogramName = cms.string("sel/evt/$PROCESS/numLeptons"),
        xAxisTitle = cms.string("lepton Multiplicity"),
        yAxisTitle = cms.string("N"),
    ),
    cms.PSet(
        histogramName = cms.string("sel/evt/$PROCESS/sumLeptonCharge"),
        xAxisTitle = cms.string("sum of lepton charges"),
        yAxisTitle = cms.string("N"),
    ),
    cms.PSet(
        histogramName = cms.string("sel/evt/$PROCESS/mvaOutput_2lss_ttV"),
        xAxisTitle = cms.string("MVA Discriminant (2lss ttV)"),
        yAxisTitle = cms.string("dN/dMVA"),
    ),
    cms.PSet(
        histogramName = cms.string("sel/evt/$PROCESS/mvaOutput_2lss_ttbar"),
        xAxisTitle = cms.string("MVA Discriminant (2lss tt)"),
        yAxisTitle = cms.string("dN/dMVA"),
    ),
    cms.PSet(
        histogramName = cms.string("sel/evt/$PROCESS/mvaDiscr_2lss"),
        xAxisTitle = cms.string("MVA"),
        yAxisTitle = cms.string("dN/dMVA"),
    ),
    cms.PSet(
        histogramName = cms.string("sel/evt/$PROCESS/mvaDiscr_3l"),
        xAxisTitle = cms.string("MVA Discriminant"),
        yAxisTitle = cms.string("dN/dMVA"),
    ),
    cms.PSet(
        histogramName = cms.string("sel/evt/$PROCESS/mvaOutput_3l_ttV"),
        xAxisTitle = cms.string("MVA Discriminant (3l ttV)"),
        yAxisTitle = cms.string("dN/dMVA"),
    ),
    cms.PSet(
        histogramName = cms.string("sel/evt/$PROCESS/mvaOutput_3l_ttbar"),
        xAxisTitle = cms.string("MVA Discriminant (3l tt)"),
        yAxisTitle = cms.string("dN/dMVA"),
    ),
    cms.PSet(
        histogramName = cms.string("sel/evt/$PROCESS/mLL"),
        xAxisTitle = cms.string("m_{ll} [GeV]"),
        yAxisTitle = cms.string("dN/dm_{ll} [1/GeV]"),
    ),
    cms.PSet(
        histogramName = cms.string("sel/evt/$PROCESS/mT"),
        xAxisTitle = cms.string("m_{T} [GeV]"),
        yAxisTitle = cms.string("dN/dm_{T} [1/GeV]"),
    )
])

