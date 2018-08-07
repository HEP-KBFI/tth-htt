import FWCore.ParameterSet.Config as cms

import numpy as np

from tthAnalysis.HiggsToTauTau.configs.makePlots_cfi import process

process.makePlots.distributions.extend([
    cms.PSet(
        histogramName = cms.string('sel/leadHadTau/$PROCESS/pt'),
        xMin = cms.double(20.),
        xMax = cms.double(200.),
        xAxisTitle = cms.string('leading #tau_{h} p_{T} [GeV]'),
        yAxisTitle = cms.string('dN/dp_{T} [1/GeV]')
    ),
    cms.PSet(
        histogramName = cms.string('sel/leadHadTau/$PROCESS/eta'),
        xAxisTitle = cms.string('leading #tau_{h} #eta'),
        yAxisTitle = cms.string('dN/d#eta')
    ),
    cms.PSet(
        histogramName = cms.string('sel/subleadHadTau/$PROCESS/pt'),
        xMin = cms.double(20.),
        xMax = cms.double(200.),
        xAxisTitle = cms.string('subleading #tau_{h} p_{T} [GeV]'),
        yAxisTitle = cms.string('dN/dp_{T} [1/GeV]')
    ),
    cms.PSet(
        histogramName = cms.string('sel/subleadHadTau/$PROCESS/eta'),
        xAxisTitle = cms.string('subleading #tau_{h} #eta'),
        yAxisTitle = cms.string('dN/d#eta')
    ),
    cms.PSet(
        histogramName = cms.string('sel/evt/$PROCESS/mvaOutput_plainKin_ttV'),
        xAxisTitle = cms.string('MVA'),
        yAxisTitle = cms.string('dN/dMVA')
    ),
    cms.PSet(
        histogramName = cms.string('sel/evt/$PROCESS/mvaOutput_plainKin_tt'),
        xAxisTitle = cms.string('MVA'),
        yAxisTitle = cms.string('dN/dMVA'),
        explicitBinning = cms.vdouble(list(np.linspace(0., 1., 6 + 1))),
    ),
    cms.PSet(
        histogramName = cms.string('sel/evt/$PROCESS/mvaOutput_plainKin_1B_VT'),
        xAxisTitle = cms.string('MVA'),
        yAxisTitle = cms.string('dN/dMVA')
    ),
    cms.PSet(
        histogramName = cms.string('sel/evt/$PROCESS/mvaOutput_HTT_SUM_VT'),
        xAxisTitle = cms.string('MVA'),
        yAxisTitle = cms.string('dN/dMVA'),
        explicitBinning = cms.vdouble(list(np.linspace(0., 1., 7 + 1))),
    ),
    cms.PSet(
        histogramName = cms.string('sel/evt/$PROCESS/mvaOutput_HTT_SUM_VT_noRebin'),
        xAxisTitle = cms.string('MVA'),
        yAxisTitle = cms.string('dN/dMVA')
    ),
    cms.PSet(
        histogramName = cms.string('sel/evt/$PROCESS/mvaOutput_plainKin_SUM_VT'),
        xAxisTitle = cms.string('MVA'),
        yAxisTitle = cms.string('dN/dMVA'),
        explicitBinning = cms.vdouble(list(np.linspace(0., 1., 5 + 1))),
    ),
    cms.PSet(
        histogramName = cms.string('sel/evt/$PROCESS/mvaOutput_plainKin_SUM_VT_noRebin'),
        xAxisTitle = cms.string('MVA'),
        yAxisTitle = cms.string('dN/dMVA')
    ),
    cms.PSet(
        histogramName = cms.string('sel/evt/$PROCESS/mvaOutput_final'),
        xAxisTitle = cms.string('MVA'),
        yAxisTitle = cms.string('dN/dMVA')
    ),
    cms.PSet(
        histogramName = cms.string('sel/evt/$PROCESS/mTauTauVis'),
        xAxisTitle = cms.string('m_{#tau#tau}^{vis} [GeV]'),
        yAxisTitle = cms.string('dN/dm_{#tau#tau}^{vis} [1/GeV]')
    )
])
