import FWCore.ParameterSet.Config as cms

import os

from tthAnalysis.HiggsToTauTau.makePlots_LeptonFakeRate_cfi import process

process.fwliteInput = cms.PSet(
    fileNames = cms.vstring("/hdfs/local/ram/ttHAnalysis_LeptonFakeRate_trial_2017Sep19/2016/2017Sep19/histograms/LeptonFakeRate/histograms_harvested_stage2_LeptonFakeRate.root")
)






process.makePlots.processesBackground = cms.vstring(
    "TTWl_plus_t",
    "TTZl_plus_t",
    "TTl_plus_t",
    "Raresl_plus_t",
    "EWKl_plus_t"
)

process.makePlots.processSignal = cms.string("signall_plus_t")

process.makePlots.categories = cms.VPSet(
    cms.PSet(
        name = cms.string("LeptonFakeRate"),
        label = cms.string("Control_plot")
    )
)

process.makePlots.distributions.extend([
#    cms.PSet(
#        histogramName = cms.string("sel/evt/$PROCESS/mvaDiscr_2lss_1tau"),
#        xAxisTitle = cms.string("MVA Discriminant"),
#        yAxisTitle = cms.string("N")
#    ),
#    cms.PSet(
#        histogramName = cms.string("sel/evt/$PROCESS/mTauTauVis"),
#        xAxisTitle = cms.string("m_{#tau#tau}^{vis} [GeV]"),
#        yAxisTitle = cms.string("dN/dm_{#tau#tau}^{vis} [1/GeV]")
#    ),
    cms.PSet(
        histogramName = cms.string("numerator/muons_tight/incl/$PROCESS/mT_fix_L"),
        xAxisTitle = cms.string("m_{T}^{fix} (GeV)"),
        yAxisTitle = cms.string("N")
    )
])

process.makePlots.nuisanceParameters.normalization = cms.PSet(
    signall_plus_t = cms.string("1.0 +/- 0.20"),
    TTl_plus_t = cms.string("1.0 +/- 0.20"),
    TTWl_plus_t = cms.string("1.0 +/- 0.20"),
    TTZl_plus_t = cms.string("1.0 +/- 0.20"),
    EWKl_plus_t = cms.string("1.0 +/- 0.20"),
    Raresl_plus_t = cms.string("1.0 +/- 0.20")
#    fakes_data = cms.string("1.0 +/- 0.20"),
#    flips_data = cms.string("1.0 +/- 0.20")
)


