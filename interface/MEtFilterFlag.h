#ifndef METFILTERFLAG_H
#define METFILTERFLAG_H

enum MEtFilterFlag
{
  BadChargedCandidateFilter = 0,
  BadChargedCandidateSummer16Filter,
  BadPFMuonFilter,
  BadPFMuonSummer16Filter,
  chargedHadronTrackResolutionFilter,
  CSCTightHalo2015Filter,
  CSCTightHaloFilter,
  CSCTightHaloTrkMuUnvetoFilter,
  ecalBadCalibFilter,
  ecalBadCalibFilterV2,
  EcalDeadCellBoundaryEnergyFilter,
  EcalDeadCellTriggerPrimitiveFilter,
  ecalLaserCorrFilter,
  eeBadScFilter,
  globalSuperTightHalo2016Filter,
  globalTightHalo2016Filter,
  goodVertices,
  HBHENoiseFilter,
  HBHENoiseIsoFilter,
  hcalLaserEventFilter,
  HcalStripHaloFilter,
  METFilters,
  muonBadTrackFilter,
  trkPOGFilters,
  trkPOG_logErrorTooManyClusters,
  trkPOG_manystripclus53X,
  trkPOG_toomanystripclus53X,
//--- DO NOT ADD BEYOND LAST
  LAST
};

const char *
getMEtFilterFlagString(MEtFilterFlag flag);

#endif // METFILTERFLAG_H
