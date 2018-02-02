#ifndef MEtFilter_H
#define MEtFilter_H

class MEtFilter
{
public:
  MEtFilter() = default;

  bool getFlag_HBHENoiseIsoFilter() const;
  bool getFlag_EcalDeadCellTriggerPrimitiveFilter() const;
  bool getFlag_ecalLaserCorrFilter() const;
  bool getFlag_hcalLaserEventFilter() const;
  bool getFlag_muonBadTrackFilter() const;
  bool getFlag_trkPOGFilters() const;
  bool getFlag_trackingFailureFilter() const;
  bool getFlag_CSCTightHaloFilter() const;
  bool getFlag_HBHENoiseFilter() const;
  bool getFlag_chargedHadronTrackResolutionFilter() const;
  bool getFlag_GlobalTightHalo2016Filter() const;
  bool getFlag_METFilters() const;
  bool getFlag_CSCTightHalo2015Filter() const;
  bool getFlag_eeBadScFilter() const;
  bool getFlag_trkPOG_manystripclus53X() const;
  bool getFlag_trkPOG_toomanystripclus53X() const;
  bool getFlag_trkPOG_logErrorTooManyClusters() const;
  bool getFlag_goodVertices() const;

  friend class MEtFilterReader;

protected:
  int Flag_HBHENoiseIsoFilter_;
  int Flag_EcalDeadCellTriggerPrimitiveFilter_;
  int Flag_ecalLaserCorrFilter_;
  int Flag_hcalLaserEventFilter_;
  int Flag_muonBadTrackFilter_;
  int Flag_trkPOGFilters_;
  int Flag_trackingFailureFilter_;
  int Flag_CSCTightHaloFilter_;
  int Flag_HBHENoiseFilter_;
  int Flag_chargedHadronTrackResolutionFilter_;
  int Flag_GlobalTightHalo2016Filter_;
  int Flag_METFilters_;
  int Flag_CSCTightHalo2015Filter_;
  int Flag_eeBadScFilter_;
  int Flag_trkPOG_manystripclus53X_;
  int Flag_trkPOG_toomanystripclus53X_;
  int Flag_trkPOG_logErrorTooManyClusters_;
  int Flag_goodVertices_;
};

#endif // MEtFilter_H
