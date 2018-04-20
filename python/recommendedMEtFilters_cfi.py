import FWCore.ParameterSet.Config as cms

recommendedMEtFilters = cms.PSet(
     apply_Flag_goodVertices = cms.bool(True),
     apply_Flag_HBHENoiseIsoFilter = cms.bool(True),
     apply_Flag_EcalDeadCellTriggerPrimitiveFilter = cms.bool(True),
     apply_Flag_ecalLaserCorrFilter = cms.bool(True),
     apply_Flag_muonBadTrackFilter = cms.bool(True),
     apply_Flag_HBHENoiseFilter = cms.bool(True),
     apply_Flag_chargedHadronTrackResolutionFilter = cms.bool(True),
     apply_Flag_GlobalTightHalo2016Filter = cms.bool(True),
     apply_Flag_eeBadScFilter = cms.bool(True),

     ## Flags not recommended in Moriond 2017 recipe but present in VHBB ntuples ##
     apply_Flag_hcalLaserEventFilter = cms.bool(False),
     apply_Flag_trkPOGFilters  = cms.bool(False),
     apply_Flag_trackingFailureFilter = cms.bool(False),
     apply_Flag_CSCTightHaloFilter = cms.bool(False),
     apply_Flag_METFilters = cms.bool(False),
     apply_Flag_CSCTightHalo2015Filter = cms.bool(False),
     apply_Flag_trkPOG_manystripclus53X = cms.bool(False),
     apply_Flag_trkPOG_toomanystripclus53X = cms.bool(False),
     apply_Flag_trkPOG_logErrorTooManyClusters = cms.bool(False),
)
