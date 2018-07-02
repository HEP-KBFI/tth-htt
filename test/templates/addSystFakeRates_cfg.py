import FWCore.ParameterSet.Config as cms

import os

process = cms.PSet()

process.fwliteInput = cms.PSet(
    ##fileNames = cms.vstring('prepareDatacards.root')
    fileNames = cms.vstring('/home/karl/ttHAnalysis/2017/2018Jun08_2lss1tau/datacards/2lss_1tau/prepareDatacards_2lss_1tau_sumOS_mvaOutput_final.root')
)

process.fwliteOutput = cms.PSet(
    fileName = cms.string('addSystFakeRates.root')
)

process.addSystFakeRates = cms.PSet(

    process = cms.string("fakes_data"),

    histogramToFit = cms.string("mvaOutput_final"),
    xAxisTitle = cms.string("MVA Discriminant"),
    yAxisTitle = cms.string("dN/dMVA"),

    addSyst = cms.VPSet(
        cms.PSet(
            name = cms.string("CMS_ttHl_Clos_e"),
            fakes_mc = cms.PSet(
                inputFileName = cms.string("/hdfs/local/karl/ttHAnalysis/2017/2018Jun08_2lss1tau/histograms/2lss_1tau/histograms_harvested_stage2_2lss_1tau_Tight_lepSS_sumOS.root"),
                histogramName = cms.string("2lss_1tau_lepSS_sumOS_Tight/sel/evt/fakes_mc/mvaOutput_final"),
            ),
            mcClosure = cms.PSet(
                inputFileName = cms.string("/hdfs/local/karl/ttHAnalysis/2017/2018Jun08_2lss1tau/histograms/2lss_1tau/addBackgrounds_2lss_1tau_fakes_mc_Fakeable_wFakeRateWeights_lepSS_sumOS.root"),
                histogramName = cms.string("2lss_1tau_lepSS_sumOS_Fakeable_wFakeRateWeight/sel/evt/fakes_mc/mvaOutput_final"),
            )
        ),
        cms.PSet(
            name = cms.string("CMS_ttHl_Clos_m"),
            fakes_mc = cms.PSet(
                inputFileName = cms.string("/hdfs/local/karl/ttHAnalysis/2017/2018Jun08_2lss1tau/histograms/2lss_1tau/histograms_harvested_stage2_2lss_1tau_Tight_lepSS_sumOS.root"),
                histogramName = cms.string("2lss_1tau_lepSS_sumOS_Tight/sel/evt/fakes_mc/mvaOutput_final"),
            ),
            mcClosure = cms.PSet(
                inputFileName = cms.string("/hdfs/local/karl/ttHAnalysis/2017/2018Jun08_2lss1tau/histograms/2lss_1tau/addBackgrounds_2lss_1tau_fakes_mc_Fakeable_wFakeRateWeights_lepSS_sumOS.root"),
                histogramName = cms.string("2lss_1tau_lepSS_sumOS_Fakeable_wFakeRateWeight/sel/evt/fakes_mc/mvaOutput_final"),
            )
        ),
        cms.PSet(
            name = cms.string("CMS_ttHl_Clos_t"),
            fakes_mc = cms.PSet(
                inputFileName = cms.string("/hdfs/local/karl/ttHAnalysis/2017/2018Jun08_2lss1tau/histograms/2lss_1tau/histograms_harvested_stage2_2lss_1tau_Tight_lepSS_sumOS.root"),
                histogramName = cms.string("2lss_1tau_lepSS_sumOS_Tight/sel/evt/fakes_mc/mvaOutput_final"),
            ),
            mcClosure = cms.PSet(
                inputFileName = cms.string("/hdfs/local/karl/ttHAnalysis/2017/2018Jun08_2lss1tau/histograms/2lss_1tau/addBackgrounds_2lss_1tau_fakes_mc_Fakeable_wFakeRateWeights_lepSS_sumOS.root"),
                histogramName = cms.string("2lss_1tau_lepSS_sumOS_Fakeable_wFakeRateWeight/sel/evt/fakes_mc/mvaOutput_final"),
            )
        )
    ),

    outputFileName = cms.string("plots/addSystFakeRates.png")
)
