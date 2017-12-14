import FWCore.ParameterSet.Config as cms

import os

process = cms.PSet()

process.fwliteInput = cms.PSet(
    fileNames = cms.vstring('/home/veelken/ttHAnalysis/histograms/allHistograms.root'),
    
    ##maxEvents = cms.int32(100000),
    maxEvents = cms.int32(-1),
    
    outputEvery = cms.uint32(100000)
)

process.fwliteOutput = cms.PSet(
    fileName = cms.string('/home/veelken/ttHAnalysis/histograms/addBackgroundLeptonFakes.root')
)

process.addBackgroundLeptonFakes = cms.PSet(

    categories = cms.VPSet(
        cms.PSet(
            signal = cms.string("2lss_1tau_SS_Tight"),
            sideband = cms.string("2lss_1tau_SS_Fakeable")
        ),
        cms.PSet(
            signal = cms.string("2epp_1tau_bloose_SS_Tight"),
            sideband = cms.string("2epp_1tau_bloose_SS_Fakeable")
        ),        
        cms.PSet(
            signal = cms.string("2epp_1tau_btight_SS_Tight"),
            sideband = cms.string("2epp_1tau_btight_SS_Fakeable")
        ),        
        cms.PSet(
            signal = cms.string("2emm_1tau_bloose_SS_Tight"),
            sideband = cms.string("2emm_1tau_bloose_SS_Fakeable")
        ),        
        cms.PSet(
            signal = cms.string("2emm_1tau_btight_SS_Tight"),
            sideband = cms.string("2emm_1tau_btight_SS_Fakeable")
        ),        
        cms.PSet(
            signal = cms.string("1e1mupp_1tau_bloose_SS_Tight"),
            sideband = cms.string("1e1mupp_1tau_bloose_SS_Fakeable")
        ),        
        cms.PSet(
            signal = cms.string("1e1mupp_1tau_btight_SS_Tight"),
            sideband = cms.string("1e1mupp_1tau_btight_SS_Fakeable")
        ),        
        cms.PSet(
            signal = cms.string("1e1mumm_1tau_bloose_SS_Tight"),
            sideband = cms.string("1e1mumm_1tau_bloose_SS_Fakeable")
        ),        
        cms.PSet(
            signal = cms.string("1e1mumm_1tau_btight_SS_Tight"),
            sideband = cms.string("1e1mumm_1tau_btight_SS_Fakeable")
        ),        
	    cms.PSet(
            signal = cms.string("2mupp_1tau_bloose_SS_Tight"),
            sideband = cms.string("2mupp_1tau_bloose_SS_Fakeable")
        ),        
        cms.PSet(
            signal = cms.string("2mupp_1tau_btight_SS_Tight"),
            sideband = cms.string("2mupp_1tau_btight_SS_Fakeable")
        ),        
        cms.PSet(
            signal = cms.string("2mumm_1tau_bloose_SS_Tight"),
            sideband = cms.string("2mumm_1tau_bloose_SS_Fakeable")
        ),        
        cms.PSet(
            signal = cms.string("2mumm_1tau_btight_SS_Tight"),
            sideband = cms.string("2mumm_1tau_btight_SS_Fakeable")
        )
    ),

    processData = cms.string("data_obs"),
    processLeptonFakes = cms.string("fakes_data"),
    processesToSubtract = cms.vstring(
        "TTW",
        "TTZ",
        "WZ",
        "EWK",
        "Rares"
    ),

    sysShifts = cms.vstring()
)
