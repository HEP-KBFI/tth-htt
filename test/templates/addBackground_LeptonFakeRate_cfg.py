import FWCore.ParameterSet.Config as cms

import os

process = cms.PSet()

process.fwliteInput = cms.PSet(
#    fileNames = cms.vstring('/hdfs/local/ram/ttHAnalysis_LeptonFakeRate_trial_2017Nov4/2016/2017Nov4/histograms/LeptonFakeRate/OLD_FILES_PREV_ITER/histograms_harvested_stage2.root'),
    fileNames = cms.vstring('/hdfs/local/ram/ttHAnalysis_LeptonFakeRate_trial_2017Nov4/2016/2017Nov4/histograms/LeptonFakeRate/histograms_harvested_stage1_5.root'),
#    fileNames = cms.vstring('/hdfs/local/ram/ttHAnalysis_LeptonFakeRate_trial_2017Sep19/2016/2017Sep19/histograms/LeptonFakeRate/histograms_harvested_stage2_LeptonFakeRate.root'),
#    fileNames = cms.vstring('/hdfs/local/ram/ttHAnalysis_LeptonFakeRate_trial_2017Oct27/2016/2017Oct27/histograms/LeptonFakeRate/histograms_harvested_stage1_5.root'),
    maxEvents = cms.int32(-1),
    outputEvery = cms.uint32(100000)
)

process.fwliteOutput = cms.PSet(
    fileName = cms.string('addBackgroundLeptonFakeRate2.root')
)

process.addBackground_LeptonFakeRate = cms.PSet(
    categories = cms.VPSet(
        cms.PSet(
            numerator = cms.string("LeptonFakeRate/numerator/electrons_tight/"),
            denominator = cms.string("LeptonFakeRate/denominator/electrons_fakeable/"),
            lepton = cms.string("electron")
        ),
        cms.PSet(
            numerator = cms.string("LeptonFakeRate/numerator/muons_tight/"),
            denominator = cms.string("LeptonFakeRate/denominator/muons_fakeable/"),
            lepton = cms.string("muon")
        )
#,
#        cms.PSet(
#            numerator = cms.string("LeptonFakeRate/numerator/"),
#            denominator = cms.string("LeptonFakeRate/denominator/"),
#            lepton = cms.string("")
#        )       
     ),

    processData = cms.string("data_obs"),
    processLeptonFakes = cms.string("fakes_data"),
    processesToSubtract = cms.vstring(
        "TTWl_plus_t",
        "TTZl_plus_t",
        "TTl_plus_t",
        "Raresl_plus_t",
        "EWKl_plus_t",
        "TTWWl_plus_t",
        "tHl_plus_t",
        "ttH_hbbl_plus_t",
        "signall_plus_t"
    ),
    sysShifts = cms.vstring(
      "central",
      "CMS_ttHl_JESUp",
      "CMS_ttHl_JESDown",
      "CMS_ttHl_JERUp",
      "CMS_ttHl_JERDown",
      "CMS_ttHl_UnclusteredEnUp",
      "CMS_ttHl_UnclusteredEnDown"
    )
)




