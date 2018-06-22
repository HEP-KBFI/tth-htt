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
        "ttH_htt",
        "ttH_hzg",
        "ttH_hmm",
    ),

    categories = cms.VPSet(
        cms.PSet(
            input = cms.string("2lss_1tau_SS_Tight/sel/evt"),
            output = cms.string("ttH_2lss_1tau")
        )
    ),
    makeSubDir = cms.bool(False),

    histogramToFit = cms.string("mvaDiscr_2lss"),
    histogramToFit_xMin = cms.double(-1.),
    histogramToFit_xMax = cms.double(-1.),
    histogramToFit_rebin = cms.int32(1),
    histogramToFit_makeBinContentsPositive = cms.bool(True),
    apply_automatic_rebinning = cms.bool(False),
    minEvents_automatic_rebinning = cms.double(0.1),
    quantile_rebinning_in_fakes = cms.bool(False),
    nbin_quantile_rebinning = cms.int32(-1),
    explicit_binning = cms.vdouble(),
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
        "CMS_ttHl_tauESUp",
        "CMS_ttHl_tauESDown",
        "CMS_ttHl_FRjt_normUp",
        "CMS_ttHl_FRjt_normDown",
        "CMS_ttHl_FRjt_shapeUp",
        "CMS_ttHl_FRjt_shapeDown",
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
    ),
)
