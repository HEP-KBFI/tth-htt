import FWCore.ParameterSet.Config as cms

import os

process = cms.PSet()

process.fwliteInput = cms.PSet(
    ##fileNames = cms.vstring('/home/veelken/ttHAnalysis/2016/2017Jan16/histograms/addBackgroundLeptonFakes_2lss_1tau_SS.root')
    fileNames = cms.vstring('/home/veelken/ttHAnalysis/2016/2017Jan16/histograms/addBackgroundLeptonFakes_3l_1tau_OS.root')
)

process.fwliteOutput = cms.PSet(
    ##fileName = cms.string('CMS_ttHl_FRl_shape_2lss_1tau_12.9fb.root')
    fileName = cms.string('CMS_ttHl_FRl_shape_3l_1tau_12.9fb.root')
)

process.compShapeSyst = cms.PSet(

    ##category = cms.string("2lss_1tau"),
    category = cms.string("3l_1tau"),

    ##histogramsToFit = cms.vstring("mvaDiscr_2lss"),
    histogramsToFit = cms.vstring("mvaDiscr_3l"),

    compSyst = cms.VPSet(
        cms.PSet(
            categories = cms.vstring("2lss_1tau"),
            processes = cms.vstring("fakes_data"),
            shifts = cms.vstring(
                "CMS_ttHl_FRe_shape_ptUp",
                "CMS_ttHl_FRe_shape_ptDown",
                "CMS_ttHl_FRe_shape_etaUp",
                "CMS_ttHl_FRe_shape_etaDown",
                "CMS_ttHl_FRe_shape_eta_barrelUp",
                "CMS_ttHl_FRe_shape_eta_barrelDown"
            ),
            histogramDir = cms.string("2lss_1tau_SS_Tight/sel/evt"),
            histogramsToFit = cms.vstring("mvaDiscr_2lss"),
            outputHistogramName1 = cms.string("CMS_ttHl_FRe_shape_2lss_anticorr1"),
            outputHistogramName2 = cms.string("CMS_ttHl_FRe_shape_2lss_corr1")
        ),
        cms.PSet(
            categories = cms.vstring("2lss_1tau"),
            processes = cms.vstring("fakes_data"),
            shifts = cms.vstring(
                "CMS_ttHl_FRm_shape_ptUp",
                "CMS_ttHl_FRm_shape_ptDown",
                "CMS_ttHl_FRm_shape_etaUp",
                "CMS_ttHl_FRm_shape_etaDown"
            ),
            histogramDir = cms.string("2lss_1tau_SS_Tight/sel/evt"),
            histogramsToFit = cms.vstring("mvaDiscr_2lss"),
            outputHistogramName1 = cms.string("CMS_ttHl_FRm_shape_2lss_anticorr1"),
            outputHistogramName2 = cms.string("CMS_ttHl_FRm_shape_2lss_corr1")
        ),
        cms.PSet(
            categories = cms.vstring("3l_1tau"),
            processes = cms.vstring("fakes_data"),
            shifts = cms.vstring(
                "CMS_ttHl_FRe_shape_ptUp",
                "CMS_ttHl_FRe_shape_ptDown",
                "CMS_ttHl_FRe_shape_etaUp",
                "CMS_ttHl_FRe_shape_etaDown",
                "CMS_ttHl_FRe_shape_eta_barrelUp",
                "CMS_ttHl_FRe_shape_eta_barrelDown"
            ),
            histogramDir = cms.string("3l_1tau_OS_lepTight_tauTight/sel/evt"),
            histogramsToFit = cms.vstring("mvaDiscr_3l"),
            outputHistogramName1 = cms.string("CMS_ttHl_FRe_shape_3l_anticorr1"),
            outputHistogramName2 = cms.string("CMS_ttHl_FRe_shape_3l_corr1")
        ),
        cms.PSet(
            categories = cms.vstring("3l_1tau"),
            processes = cms.vstring("fakes_data"),
            shifts = cms.vstring(
                "CMS_ttHl_FRm_shape_ptUp",
                "CMS_ttHl_FRm_shape_ptDown",
                "CMS_ttHl_FRm_shape_etaUp",
                "CMS_ttHl_FRm_shape_etaDown"
            ),
            histogramDir = cms.string("3l_1tau_OS_lepTight_tauTight/sel/evt"),
            histogramsToFit = cms.vstring("mvaDiscr_3l"),
            outputHistogramName1 = cms.string("CMS_ttHl_FRm_shape_3l_anticorr1"),
            outputHistogramName2 = cms.string("CMS_ttHl_FRm_shape_3l_corr1")
        )
    )
)
