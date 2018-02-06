#ifndef MEtFilter_H
#define MEtFilter_H

class MEtFilter
{
public:
  MEtFilter() = default;

  bool getFlag_goodVertices() const;
  bool getFlag_globalSuperTightHalo2016Filter() const;
  bool getFlag_HBHENoiseFilter() const;
  bool getFlag_HBHENoiseIsoFilter() const;
  bool getFlag_EcalDeadCellTriggerPrimitiveFilter() const;
  bool getFlag_eeBadScFilter() const;
  bool getFlag_BadPFMuonFilter() const;  
  bool getFlag_BadChargedCandidateFilter() const; 
  bool getFlag_hcalLaserEventFilter() const;
  bool getFlag_trkPOGFilters() const;
  bool getFlag_CSCTightHaloFilter() const;
  bool getFlag_trkPOG_manystripclus53X() const;
  bool getFlag_trkPOG_toomanystripclus53X() const;
  bool getFlag_trkPOG_logErrorTooManyClusters() const;
  bool getFlag_CSCTightHalo2015Filter() const;    
  bool getFlag_BadChargedCandidateSummer16Filter() const; 
  bool getFlag_BadPFMuonSummer16Filter() const;           
  bool getFlag_CSCTightHaloTrkMuUnvetoFilter() const;     
  bool getFlag_EcalDeadCellBoundaryEnergyFilter() const;  
  bool getFlag_HcalStripHaloFilter() const;               
  bool getFlag_METFilters() const;                        
  bool getFlag_chargedHadronTrackResolutionFilter() const; 
  bool getFlag_ecalBadCalibFilter() const;                 
  bool getFlag_ecalLaserCorrFilter() const;                
  bool getFlag_muonBadTrackFilter() const;         

  friend class MEtFilterReader;
  
protected:
  bool Flag_goodVertices_;
  bool Flag_globalSuperTightHalo2016Filter_;
  bool Flag_HBHENoiseFilter_;
  bool Flag_HBHENoiseIsoFilter_;
  bool Flag_EcalDeadCellTriggerPrimitiveFilter_;
  bool Flag_eeBadScFilter_;
  bool Flag_BadPFMuonFilter_;  
  bool Flag_BadChargedCandidateFilter_; 
  bool Flag_hcalLaserEventFilter_;
  bool Flag_trkPOGFilters_;
  bool Flag_CSCTightHaloFilter_;
  bool Flag_trkPOG_manystripclus53X_;
  bool Flag_trkPOG_toomanystripclus53X_;
  bool Flag_trkPOG_logErrorTooManyClusters_;
  bool Flag_CSCTightHalo2015Filter_;    
  bool Flag_BadChargedCandidateSummer16Filter_; 
  bool Flag_BadPFMuonSummer16Filter_;           
  bool Flag_CSCTightHaloTrkMuUnvetoFilter_;     
  bool Flag_EcalDeadCellBoundaryEnergyFilter_;  
  bool Flag_HcalStripHaloFilter_;               
  bool Flag_METFilters_;                        
  bool Flag_chargedHadronTrackResolutionFilter_; 
  bool Flag_ecalBadCalibFilter_;                 
  bool Flag_ecalLaserCorrFilter_;                
  bool Flag_muonBadTrackFilter_;         

};

#endif // MEtFilter_H
