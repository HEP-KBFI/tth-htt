import FWCore.ParameterSet.Config as cms

import os

process = cms.PSet()

process.fwliteInput = cms.PSet(
    fileNames = cms.vstring()
)

process.fwliteOutput = cms.PSet(
    fileName = cms.string('prepareDatacards.root')
)

process.prepareDatacards = cms.PSet(

    processesToCopy = cms.vstring(
        "data_obs",
        "TTW",
        "TTZ",
        "WZ",
        "Rares",
        "fakes_data",
        "flips_data"
    ),

    sf_signal = cms.double(1.),
    signals = cms.vstring(
        "ttH_hww",
        "ttH_hzz",
        "ttH_htt"
    ),

    categories = cms.VPSet(
        cms.PSet(
            input = cms.string("2lss_1tau_SS_Tight/sel/evt"),
            output = cms.string("ttH_2lss_1tau")
        )
    ),
    makeSubDir = cms.bool(False),

    histogramToFit = cms.string("mvaDiscr_2lss"),
    histogramToFit_rebin = cms.int32(1),

    setBinsToZeroBelow = cms.double(-1.),

    sysShifts = cms.vstring(
        "CMS_ttHl_btag_HFUp",
        "CMS_ttHl_btag_HFDown",
        "CMS_ttHl_btag_HFStats1Up",
        "CMS_ttHl_btag_HFStats1Down",
        "CMS_ttHl_btag_HFStats2Up",
        "CMS_ttHl_btag_HFStats2Down",
        "CMS_ttHl_btag_LFUp",
        "CMS_ttHl_btag_LFDown",
        "CMS_ttHl_btag_LFStats1Up",
        "CMS_ttHl_btag_LFStats1Down",
        "CMS_ttHl_btag_LFStats2Up",
        "CMS_ttHl_btag_LFStats2Down",
        "CMS_ttHl_btag_cErr1Up",
        "CMS_ttHl_btag_cErr1Down",
        "CMS_ttHl_btag_cErr2Up",
        "CMS_ttHl_btag_cErr2Down",
        "CMS_ttHl_JESUp",
        "CMS_ttHl_JESDown",
        "CMS_ttHl_thu_shape_ttH_x1Up",
        "CMS_ttHl_thu_shape_ttH_x1Down",
        "CMS_ttHl_thu_shape_ttH_y1Up",
        "CMS_ttHl_thu_shape_ttH_y1Down",
        "CMS_ttHl_thu_shape_ttW_x1Up",
        "CMS_ttHl_thu_shape_ttW_x1Down",
        "CMS_ttHl_thu_shape_ttW_y1Up",
        "CMS_ttHl_thu_shape_ttW_y1Down",
        "CMS_ttHl_thu_shape_ttZ_x1Up",
        "CMS_ttHl_thu_shape_ttZ_x1Down",
        "CMS_ttHl_thu_shape_ttZ_y1Up",
        "CMS_ttHl_thu_shape_ttZ_y1Down"
    )
)
