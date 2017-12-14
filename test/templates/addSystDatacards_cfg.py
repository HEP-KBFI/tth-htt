import FWCore.ParameterSet.Config as cms

import os

process = cms.PSet()

process.fwliteInput = cms.PSet(
    ##fileNames = cms.vstring('prepareDatacards.root')
    fileNames = cms.vstring('/home/veelken/ttHAnalysis/2016/2017Jan13/datacards/prepareDatacards_2lss_1tau_mvaDiscr_2lss.root')
)

process.fwliteOutput = cms.PSet(
    fileName = cms.string('addSystDatacards.root')
)

process.addSystDatacards = cms.PSet(

    category = cms.string("2lss_1tau"),

    histogramToFit = cms.string("mvaDiscr_2lss"),

    addSyst = cms.VPSet(
        cms.PSet(
            name = cms.string("CMS_ttHl_Clos_e_shape"),
            categories = cms.vstring("2lss_1tau"),
            processes = cms.vstring("fakes_data"),
            histogramsToFit = cms.vstring("mvaDiscr_2lss"),
            inputFileName = cms.string("tthAnalysis/HiggsToTauTau/data/addSystDatacards/Closure_FR_lepton_syst_2lSS1tau_nofaketau_MVA_2lSS_12.9fb.root"),
            histogramName = cms.string("x_TT_DL_FR_TT_MC_minus_FR_QCD_MC_ele"),
        ),
        cms.PSet(
            name = cms.string("CMS_ttHl_Clos_m_shape"),
            categories = cms.vstring("2lss_1tau"),
            processes = cms.vstring("fakes_data"),
            histogramsToFit = cms.vstring("mvaDiscr_2lss"),
            inputFileName = cms.string("tthAnalysis/HiggsToTauTau/data/addSystDatacards/Closure_FR_lepton_syst_2lSS1tau_nofaketau_MVA_2lSS_12.9fb.root"),
            histogramName = cms.string("x_TT_DL_FR_TT_MC_minus_FR_QCD_MC_mu"),
        ),
        cms.PSet(
            name = cms.string("CMS_ttHl_FRe_shape_2lss_anticorr1"),
            categories = cms.vstring("2lss_1tau"),
            processes = cms.vstring("fakes_data"),
            histogramsToFit = cms.vstring("mvaDiscr_2lss"),
            inputFileName = cms.string("tthAnalysis/HiggsToTauTau/data/addSystDatacards/CMS_ttHl_FRl_shape_2lss_1tau_12.9fb.root"),
            histogramName = cms.string("CMS_ttHl_FRe_shape_2lss_anticorr1Up"),
        ),
        cms.PSet(
            name = cms.string("CMS_ttHl_FRe_shape_2lss_corr1"),
            categories = cms.vstring("2lss_1tau"),
            processes = cms.vstring("fakes_data"),
            histogramsToFit = cms.vstring("mvaDiscr_2lss"),
            inputFileName = cms.string("tthAnalysis/HiggsToTauTau/data/addSystDatacards/CMS_ttHl_FRl_shape_2lss_1tau_12.9fb.root"),
            histogramName = cms.string("CMS_ttHl_FRe_shape_2lss_corr1Up"),
        ),
        cms.PSet(
            name = cms.string("CMS_ttHl_FRm_shape_2lss_anticorr1"),
            categories = cms.vstring("2lss_1tau"),
            processes = cms.vstring("fakes_data"),
            histogramsToFit = cms.vstring("mvaDiscr_2lss"),
            inputFileName = cms.string("tthAnalysis/HiggsToTauTau/data/addSystDatacards/CMS_ttHl_FRl_shape_2lss_1tau_12.9fb.root"),
            histogramName = cms.string("CMS_ttHl_FRm_shape_2lss_anticorr1Up"),
        ),
        cms.PSet(
            name = cms.string("CMS_ttHl_FRm_shape_2lss_corr1"),
            categories = cms.vstring("2lss_1tau"),
            processes = cms.vstring("fakes_data"),
            histogramsToFit = cms.vstring("mvaDiscr_2lss"),
            inputFileName = cms.string("tthAnalysis/HiggsToTauTau/data/addSystDatacards/CMS_ttHl_FRl_shape_2lss_1tau_12.9fb.root"),
            histogramName = cms.string("CMS_ttHl_FRm_shape_2lss_corr1Up"),
        ),        
        cms.PSet(
            name = cms.string("CMS_ttHl_Clos_e_shape"),
            categories = cms.vstring("3l_1tau"),
            processes = cms.vstring("fakes_data"),
            histogramsToFit = cms.vstring("mvaDiscr_3l"),
            inputFileName = cms.string("tthAnalysis/HiggsToTauTau/data/addSystDatacards/Closure_FR_lepton_syst_3l1tau_nofaketau_MVA_3l_12.9fb.root"),
            histogramName = cms.string("x_TT_DL_FR_TT_MC_minus_FR_QCD_MC_ele"),
        ),
        cms.PSet(
            name = cms.string("CMS_ttHl_Clos_m_shape"),
            categories = cms.vstring("3l_1tau"),
            processes = cms.vstring("fakes_data"),
            histogramsToFit = cms.vstring("mvaDiscr_3l"),
            inputFileName = cms.string("tthAnalysis/HiggsToTauTau/data/addSystDatacards/Closure_FR_lepton_syst_3l1tau_nofaketau_MVA_3l_12.9fb.root"),
            histogramName = cms.string("x_TT_DL_FR_TT_MC_minus_FR_QCD_MC_mu"),
        )
    )
)
