import FWCore.ParameterSet.Config as cms

import os

process = cms.PSet()

process.fwliteInput = cms.PSet(
    fileNames = cms.vstring()
)

process.fwliteOutput = cms.PSet(
    fileName = cms.string('addBackgrounds.root')
)

process.addBackgrounds = cms.PSet(

    categories = cms.vstring(),
    
    processes_input = cms.vstring(),
    process_output = cms.string(""),
    
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
        "CMS_ttHl_FRt_normUp",
        "CMS_ttHl_FRt_normDown",
        "CMS_ttHl_FRt_shapeUp",
        "CMS_ttHl_FRt_shapeDown"
    )
)
