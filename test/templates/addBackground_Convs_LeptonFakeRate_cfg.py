import FWCore.ParameterSet.Config as cms

import os

process = cms.PSet()

process.fwliteInput = cms.PSet(
    fileNames = cms.vstring('/hdfs/local/ram/ttHAnalysis_LeptonFakeRate_trial_2017Nov4/2016/2017Nov4/histograms/LeptonFakeRate/histograms_harvested_stage1_5.root'),
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

    processData = cms.string("ttH"),
    processLeptonFakes = cms.string("ttH_NC"),
    processesToSubtract = cms.vstring(
        "ttHg",
#        "signall_plus_t"
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

process.fwliteInput.fileNames = cms.vstring('analyze_LeptonFakeRate.root')


