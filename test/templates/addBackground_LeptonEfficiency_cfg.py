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

process.addBackground_LeptonEfficiency = cms.PSet(
    categories = cms.VPSet(
        cms.PSet(
            numerator = cms.string("LeptonEfficiency/numerator/electrons_tight/"),
            denominator = cms.string("LeptonEfficiency/denominator/electrons_presel_not_tight/"),
            lepton = cms.string("electron")
        ),
        cms.PSet(
            numerator = cms.string("LeptonEfficiency/numerator/muons_tight/"),
            denominator = cms.string("LeptonEfficiency/denominator/muons_presel_not_tight/"),
            lepton = cms.string("muon")
        )
     ),

    processData = cms.string("data_obs"),
    processLeptonFakes = cms.string("data_fakes"),
    processesToSubtract = cms.vstring(
        "DYl",
        "WJetsl",
        "TTbarl",
        "Singletopl",
        "Dibosonl",
    ),
    sysShifts = cms.vstring(
      "central",
      "CMS_ttHl_JESUp",
      "CMS_ttHl_JESDown",
      "CMS_ttHl_JERUp",
      "CMS_ttHl_JERDown",
      "CMS_ttHl_UnclusteredEnUp",
      "CMS_ttHl_UnclusteredEnDown",
      "MET_RespUp",
      "MET_RespDown",
      "MET_ResolUp",
      "MET_ResolDown"        
    )
)
