import FWCore.ParameterSet.Config as cms

import os

process = cms.PSet()

process.fwliteInput = cms.PSet(
    fileNames = cms.vstring("/hdfs/local/ram/ttHAnalysis_LeptonFakeRate_trial_2017Sep19/2016/2017Sep19/histograms/LeptonFakeRate/histograms_harvested_stage2.root")
)

process.fwliteOutput = cms.PSet(
    fileName = cms.string('datacard_LeptonFakeRate.root')
)

process.prepareDatacards = cms.PSet(
    processesToCopy = cms.vstring(
        "data_obs",
        "TTW",
        "TTZ",
        "TT",
        "Rares",
        "fakes_data",
        "EWK",
        "tH",
        "TTWW",
        "ttH_hbb"
    ),

    sf_signal = cms.double(1.),
    signals = cms.vstring(
        "signal"
    ),

## electrons and muons inclusive
    categories = cms.VPSet(
        cms.PSet(
            input = cms.string("LeptonFakeRate/denominator/muons_fakeable/incl"),
            output = cms.string("muons_fakeable_incl_shapes")
        ),
        cms.PSet(
            input = cms.string("LeptonFakeRate/denominator/electrons_fakeable/incl"),
            output = cms.string("electrons_fakeable_incl_shapes")
        ),
## electrons inclusive
        cms.PSet(
            input = cms.string("LeptonFakeRate/numerator/muons_tight/incl"),
            output = cms.string("muons_tight_incl_shapes")
        ),
        cms.PSet(
            input = cms.string("LeptonFakeRate/numerator/electrons_tight/incl"),
            output = cms.string("electrons_tight_incl_shapes")
        ),
### Electrons pT and eta bins
        cms.PSet(
            input = cms.string("LeptonFakeRate/denominator/electrons_fakeable/absEta1_0to1_5/Pt20_0to30_0"),
            output = cms.string("electrons_fakeable_absEta1_0to1_5_Pt20_0to30_0_shapes")
        ),
        cms.PSet(
            input = cms.string("LeptonFakeRate/denominator/electrons_fakeable/absEta1_0to1_5/Pt30_0to100000_0"),
            output = cms.string("electrons_fakeable_absEta1_0to1_5_Pt30_0to100000_0_shapes")
        ),
        cms.PSet(
            input = cms.string("LeptonFakeRate/denominator/electrons_fakeable/absEta1_5to9_9/Pt20_0to30_0"),
            output = cms.string("electrons_fakeable_absEta1_5to9_9_Pt20_0to30_0_shapes")
        ),
        cms.PSet(
            input = cms.string("LeptonFakeRate/denominator/electrons_fakeable/absEta1_5to9_9/Pt30_0to100000_0"),
            output = cms.string("electrons_fakeable_absEta1_5to9_9_Pt30_0to100000_0_shapes")
        ),
        cms.PSet(
            input = cms.string("LeptonFakeRate/numerator/electrons_tight/absEta1_0to1_5/Pt20_0to30_0"),
            output = cms.string("electrons_tight_absEta1_0to1_5_Pt20_0to30_0_shapes")
        ),
        cms.PSet(
            input = cms.string("LeptonFakeRate/numerator/electrons_tight/absEta1_0to1_5/Pt30_0to100000_0"),
            output = cms.string("electrons_tight_absEta1_0to1_5_Pt30_0to100000_0_shapes")
        ),
        cms.PSet(
            input = cms.string("LeptonFakeRate/numerator/electrons_tight/absEta1_5to9_9/Pt20_0to30_0"),
            output = cms.string("electrons_tight_absEta1_5to9_9_Pt20_0to30_0_shapes")
        ),
        cms.PSet(
            input = cms.string("LeptonFakeRate/numerator/electrons_tight/absEta1_5to9_9/Pt30_0to100000_0"),
            output = cms.string("electrons_tight_absEta1_5to9_9_Pt30_0to100000_0_shapes")
        ),
### Muons pT and eta bins
        cms.PSet(
            input = cms.string("LeptonFakeRate/denominator/muons_fakeable/absEta1_0to1_5/Pt10_0to30_0"),
            output = cms.string("muons_fakeable_absEta1_0to1_5_Pt10_0to30_0_shapes")
        ),
        cms.PSet(
            input = cms.string("LeptonFakeRate/denominator/muons_fakeable/absEta1_0to1_5/Pt30_0to100000_0"),
            output = cms.string("muons_fakeable_absEta1_0to1_5_Pt30_0to100000_0_shapes")
        ),
        cms.PSet(
            input = cms.string("LeptonFakeRate/denominator/muons_fakeable/absEta1_5to9_9/Pt10_0to30_0"),
            output = cms.string("muons_fakeable_absEta1_5to9_9_Pt10_0to30_0_shapes")
        ),
        cms.PSet(
            input = cms.string("LeptonFakeRate/denominator/muons_fakeable/absEta1_5to9_9/Pt30_0to100000_0"),
            output = cms.string("muons_fakeable_absEta1_5to9_9_Pt30_0to100000_0_shapes")
        ),
        cms.PSet(
            input = cms.string("LeptonFakeRate/numerator/muons_tight/absEta1_0to1_5/Pt10_0to30_0"),
            output = cms.string("muons_tight_absEta1_0to1_5_Pt10_0to30_0_shapes")
        ),
        cms.PSet(
            input = cms.string("LeptonFakeRate/numerator/muons_tight/absEta1_0to1_5/Pt30_0to100000_0"),
            output = cms.string("muons_tight_absEta1_0to1_5_Pt30_0to100000_0_shapes")
        ),
        cms.PSet(
            input = cms.string("LeptonFakeRate/numerator/muons_tight/absEta1_5to9_9/Pt10_0to30_0"),
            output = cms.string("muons_tight_absEta1_5to9_9_Pt10_0to30_0_shapes")
        ),
        cms.PSet(
            input = cms.string("LeptonFakeRate/numerator/muons_tight/absEta1_5to9_9/Pt30_0to100000_0"),
            output = cms.string("muons_tight_absEta1_5to9_9_Pt30_0to100000_0_shapes")
        )
    ),
    makeSubDir = cms.bool(True),

    histogramToFit = cms.string("mT_fix_L"),
    histogramToFit_rebin = cms.int32(1),

    setBinsToZeroBelow = cms.double(-1.),

    sysShifts = cms.vstring(
      "central",
      "CMS_ttHl_JESUp",
      "CMS_ttHl_JESDown",
      "CMS_ttHl_JERUp",
      "CMS_ttHl_JERDown",
      "CMS_ttHl_UnclusteredEnUp",
      "CMS_ttHl_UnclusteredEnDown"
#        "CMS_ttHl_btag_HFUp",
#        "CMS_ttHl_btag_HFDown",
#        "CMS_ttHl_btag_HFStats1Up",
#        "CMS_ttHl_btag_HFStats1Down",
#        "CMS_ttHl_btag_HFStats2Up",
#        "CMS_ttHl_btag_HFStats2Down",
#        "CMS_ttHl_btag_LFUp",
#        "CMS_ttHl_btag_LFDown",
#        "CMS_ttHl_btag_LFStats1Up",
#        "CMS_ttHl_btag_LFStats1Down",
#        "CMS_ttHl_btag_LFStats2Up",
#        "CMS_ttHl_btag_LFStats2Down",
#        "CMS_ttHl_btag_cErr1Up",
#        "CMS_ttHl_btag_cErr1Down",
#        "CMS_ttHl_btag_cErr2Up",
#        "CMS_ttHl_btag_cErr2Down",
#        "CMS_ttHl_JESUp",
#        "CMS_ttHl_JESDown",
#        "CMS_ttHl_tauESUp",
#        "CMS_ttHl_tauESDown",
#        "CMS_ttHl_FRjt_normUp",
#        "CMS_ttHl_FRjt_normDown",
#        "CMS_ttHl_FRjt_shapeUp",
#        "CMS_ttHl_FRjt_shapeDown",
#        "CMS_ttHl_thu_shape_ttH_x1Up",
#        "CMS_ttHl_thu_shape_ttH_x1Down",
#        "CMS_ttHl_thu_shape_ttH_y1Up",
#        "CMS_ttHl_thu_shape_ttH_y1Down",
#        "CMS_ttHl_thu_shape_ttW_x1Up",
#        "CMS_ttHl_thu_shape_ttW_x1Down",
#        "CMS_ttHl_thu_shape_ttW_y1Up",
#        "CMS_ttHl_thu_shape_ttW_y1Down",
#        "CMS_ttHl_thu_shape_ttZ_x1Up",
#        "CMS_ttHl_thu_shape_ttZ_x1Down",
#        "CMS_ttHl_thu_shape_ttZ_y1Up",
#        "CMS_ttHl_thu_shape_ttZ_y1Down"
    )

## ----- NEW LINES --- ###    
#    absEtaBins_e  = cms.vdouble(-1., 1.479, 9.9),
#    absEtaBins_mu = cms.vdouble(-1., 1.479, 9.9),
#    absPtBins_e   = cms.vdouble(20., 30., 100000.),
#    absPtBins_mu  = cms.vdouble(10.,30.,100000.),
### ------------------- ###


)
