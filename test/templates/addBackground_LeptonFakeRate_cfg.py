import FWCore.ParameterSet.Config as cms

import os

process = cms.PSet()

process.fwliteInput = cms.PSet(
    fileNames = cms.vstring(),
    maxEvents = cms.int32(-1),
    outputEvery = cms.uint32(100000)
)

process.fwliteOutput = cms.PSet(
    fileName = cms.string('')
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
     ),

    processData = cms.string("data_obs"),
    processLeptonFakes = cms.string("fakes_data"),
    processesToSubtract = cms.vstring(
        "TTl_plus_t",
        "Raresl_plus_t",
        "EWKl_plus_t",
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
