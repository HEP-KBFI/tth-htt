import FWCore.ParameterSet.Config as cms

# MET filter settings taken from:
# https://twiki.cern.ch/twiki/bin/viewauth/CMS/MissingETOptionalFiltersRun2#Moriond_2018

recommendedMEtFilters = cms.PSet(
    apply_Flag_BadChargedCandidateFilter          = cms.bool(True),
    apply_Flag_BadChargedCandidateSummer16Filter  = cms.bool(False),
    apply_Flag_BadPFMuonFilter                    = cms.bool(True),
    apply_Flag_BadPFMuonSummer16Filter            = cms.bool(False),
    apply_Flag_CSCTightHalo2015Filter             = cms.bool(False),
    apply_Flag_CSCTightHaloFilter                 = cms.bool(False),
    apply_Flag_CSCTightHaloTrkMuUnvetoFilter      = cms.bool(False),
    apply_Flag_EcalDeadCellBoundaryEnergyFilter   = cms.bool(False),
    apply_Flag_EcalDeadCellTriggerPrimitiveFilter = cms.bool(True),
    apply_Flag_HBHENoiseFilter                    = cms.bool(True),
    apply_Flag_HBHENoiseIsoFilter                 = cms.bool(True),
    apply_Flag_HcalStripHaloFilter                = cms.bool(False),
    apply_Flag_METFilters                         = cms.bool(False),
    apply_Flag_chargedHadronTrackResolutionFilter = cms.bool(False),
    apply_Flag_ecalBadCalibFilter                 = cms.bool(True),
    apply_Flag_ecalLaserCorrFilter                = cms.bool(False),
    apply_Flag_eeBadScFilter                      = cms.bool(False), # explicitly not suggested
    apply_Flag_globalSuperTightHalo2016Filter     = cms.bool(False),
    apply_Flag_globalTightHalo2016Filter          = cms.bool(True), # NB! not suggested for FastSim samples
    apply_Flag_goodVertices                       = cms.bool(True),
    apply_Flag_hcalLaserEventFilter               = cms.bool(False),
    apply_Flag_muonBadTrackFilter                 = cms.bool(False),
    apply_Flag_trkPOGFilters                      = cms.bool(False),
    apply_Flag_trkPOG_logErrorTooManyClusters     = cms.bool(False),
    apply_Flag_trkPOG_manystripclus53X            = cms.bool(False),
    apply_Flag_trkPOG_toomanystripclus53X         = cms.bool(False),
)
