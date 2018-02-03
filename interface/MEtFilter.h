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
//  bool getFlag_trackingFailureFilter() const; // Karl: missing in nanoAOD
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
  bool Flag_HBHENoiseIsoFilter_;
  bool Flag_EcalDeadCellTriggerPrimitiveFilter_;
  bool Flag_ecalLaserCorrFilter_;
  bool Flag_hcalLaserEventFilter_;
  bool Flag_muonBadTrackFilter_;
  bool Flag_trkPOGFilters_;
//  bool Flag_trackingFailureFilter_; // Karl: missing in nanoAOD
  bool Flag_CSCTightHaloFilter_;
  bool Flag_HBHENoiseFilter_;
  bool Flag_chargedHadronTrackResolutionFilter_;
  bool Flag_GlobalTightHalo2016Filter_;
  bool Flag_METFilters_;
  bool Flag_CSCTightHalo2015Filter_;
  bool Flag_eeBadScFilter_;
  bool Flag_trkPOG_manystripclus53X_;
  bool Flag_trkPOG_toomanystripclus53X_;
  bool Flag_trkPOG_logErrorTooManyClusters_;
  bool Flag_goodVertices_;
};

#endif // MEtFilter_H
