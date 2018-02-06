#ifndef METFILTERFLAG_H
#define METFILTERFLAG_H

enum MEtFilterFlag
{
  BadChargedCandidateFilter = 0,
  BadChargedCandidateSummer16Filter,
  BadPFMuonFilter,
  BadPFMuonSummer16Filter,
  CSCTightHalo2015Filter,
  CSCTightHaloFilter,
  CSCTightHaloTrkMuUnvetoFilter,
  EcalDeadCellBoundaryEnergyFilter,
  EcalDeadCellTriggerPrimitiveFilter,
  HBHENoiseFilter,
  HBHENoiseIsoFilter,
  HcalStripHaloFilter,
  METFilters,
  chargedHadronTrackResolutionFilter,
  ecalBadCalibFilter,
  ecalLaserCorrFilter,
  eeBadScFilter,
  globalSuperTightHalo2016Filter,
  globalTightHalo2016Filter,
  goodVertices,
  hcalLaserEventFilter,
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
