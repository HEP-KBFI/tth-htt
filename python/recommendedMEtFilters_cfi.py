import FWCore.ParameterSet.Config as cms

# MET filter settings taken from:
# https://twiki.cern.ch/twiki/bin/view/CMS/MissingETOptionalFiltersRun2?rev=115#Moriond_2018

recommendedMEtFilters = cms.PSet(
    apply_Flag_BadChargedCandidateFilter          = cms.PSet(forMC = cms.bool(True),  forData = cms.bool(True)),
    apply_Flag_BadChargedCandidateSummer16Filter  = cms.PSet(forMC = cms.bool(False), forData = cms.bool(False)),
    apply_Flag_BadPFMuonFilter                    = cms.PSet(forMC = cms.bool(True),  forData = cms.bool(True)),
    apply_Flag_BadPFMuonSummer16Filter            = cms.PSet(forMC = cms.bool(False), forData = cms.bool(False)),
    apply_Flag_CSCTightHalo2015Filter             = cms.PSet(forMC = cms.bool(False), forData = cms.bool(False)),
    apply_Flag_CSCTightHaloFilter                 = cms.PSet(forMC = cms.bool(False), forData = cms.bool(False)),
    apply_Flag_CSCTightHaloTrkMuUnvetoFilter      = cms.PSet(forMC = cms.bool(False), forData = cms.bool(False)),
    apply_Flag_EcalDeadCellBoundaryEnergyFilter   = cms.PSet(forMC = cms.bool(False), forData = cms.bool(False)),
    apply_Flag_EcalDeadCellTriggerPrimitiveFilter = cms.PSet(forMC = cms.bool(True),  forData = cms.bool(True)),
    apply_Flag_HBHENoiseFilter                    = cms.PSet(forMC = cms.bool(True),  forData = cms.bool(True)),
    apply_Flag_HBHENoiseIsoFilter                 = cms.PSet(forMC = cms.bool(True),  forData = cms.bool(True)),
    apply_Flag_HcalStripHaloFilter                = cms.PSet(forMC = cms.bool(False), forData = cms.bool(False)),
    apply_Flag_METFilters                         = cms.PSet(forMC = cms.bool(False), forData = cms.bool(False)),
    apply_Flag_chargedHadronTrackResolutionFilter = cms.PSet(forMC = cms.bool(False), forData = cms.bool(False)),
    apply_Flag_ecalBadCalibFilter                 = cms.PSet(forMC = cms.bool(True),  forData = cms.bool(True)),
    apply_Flag_ecalLaserCorrFilter                = cms.PSet(forMC = cms.bool(False), forData = cms.bool(False)),
    apply_Flag_eeBadScFilter                      = cms.PSet(forMC = cms.bool(False), forData = cms.bool(True)), # [*]
    apply_Flag_globalSuperTightHalo2016Filter     = cms.PSet(forMC = cms.bool(False), forData = cms.bool(False)),
    apply_Flag_globalTightHalo2016Filter          = cms.PSet(forMC = cms.bool(True),  forData = cms.bool(True)), # NB! not suggested for FastSim samples
    apply_Flag_goodVertices                       = cms.PSet(forMC = cms.bool(True),  forData = cms.bool(True)),
    apply_Flag_hcalLaserEventFilter               = cms.PSet(forMC = cms.bool(False), forData = cms.bool(False)),
    apply_Flag_muonBadTrackFilter                 = cms.PSet(forMC = cms.bool(False), forData = cms.bool(False)),
    apply_Flag_trkPOGFilters                      = cms.PSet(forMC = cms.bool(False), forData = cms.bool(False)),
    apply_Flag_trkPOG_logErrorTooManyClusters     = cms.PSet(forMC = cms.bool(False), forData = cms.bool(False)),
    apply_Flag_trkPOG_manystripclus53X            = cms.PSet(forMC = cms.bool(False), forData = cms.bool(False)),
    apply_Flag_trkPOG_toomanystripclus53X         = cms.PSet(forMC = cms.bool(False), forData = cms.bool(False)),
)

# is set to true for data only as per gitlab page
# https://gitlab.cern.ch/ttH_leptons/doc/blob/master/2017/event_selection.md#4-event-selection
