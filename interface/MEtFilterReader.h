#ifndef tthAnalysis_HiggsToTauTau_MEtFilterReader_h
#define tthAnalysis_HiggsToTauTau_MEtFilterReader_h

#include "tthAnalysis/HiggsToTauTau/interface/ReaderBase.h" // ReaderBase
#include "tthAnalysis/HiggsToTauTau/interface/MEtFilter.h" // To be made NEW !



#include <Rtypes.h> // Int_t, Double_t
#include <TTree.h> // TTree

#include <string>
#include <vector>
#include <map>

class MEtFilterReader
  : public ReaderBase
{
 public:
  MEtFilterReader(MEtFilter* metFilter); // NEW!
  ~MEtFilterReader();

  /**
   * @brief Call tree->SetBranchAddress for all branches containing "Flag" and "Filter" in their names
   */
  void setBranchAddresses(TTree* tree) override;

  /**
   * @brief Read branches from tree and return values
   * @return Weights for estimating systematic uncertainties related to scale and PDF variations
   */

  void read() const;

  /*
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
  */

 protected:
 /**
   * @brief Initialize names of branches to be read from tree
   */
  void setBranchNames();

  std::string branchNameFlag_HBHENoiseIsoFilter_;
  std::string branchNameFlag_EcalDeadCellTriggerPrimitiveFilter_;
  std::string branchNameFlag_ecalLaserCorrFilter_;
  std::string branchNameFlag_hcalLaserEventFilter_;
  std::string branchNameFlag_muonBadTrackFilter_;
  std::string branchNameFlag_trkPOGFilters_;
  std::string branchNameFlag_trackingFailureFilter_;
  std::string branchNameFlag_CSCTightHaloFilter_;
  std::string branchNameFlag_HBHENoiseFilter_;
  std::string branchNameFlag_chargedHadronTrackResolutionFilter_;
  std::string branchNameFlag_GlobalTightHalo2016Filter_;
  std::string branchNameFlag_METFilters_;
  std::string branchNameFlag_CSCTightHalo2015Filter_;
  std::string branchNameFlag_eeBadScFilter_;
  std::string branchNameFlag_trkPOG_manystripclus53X_;
  std::string branchNameFlag_trkPOG_toomanystripclus53X_;
  std::string branchNameFlag_trkPOG_logErrorTooManyClusters_;
  std::string branchNameFlag_goodVertices_;

//----  NEW ! -----
  /* 
  mutable int Flag_HBHENoiseIsoFilter_;
  mutable int Flag_EcalDeadCellTriggerPrimitiveFilter_;
  mutable int Flag_ecalLaserCorrFilter_;
  mutable int Flag_hcalLaserEventFilter_;
  mutable int Flag_muonBadTrackFilter_;
  mutable int Flag_trkPOGFilters_;
  mutable int Flag_trackingFailureFilter_;
  mutable int Flag_CSCTightHaloFilter_;
  mutable int Flag_HBHENoiseFilter_;
  mutable int Flag_chargedHadronTrackResolutionFilter_;
  mutable int Flag_GlobalTightHalo2016Filter_;
  mutable int Flag_METFilters_;
  mutable int Flag_CSCTightHalo2015Filter_;
  mutable int Flag_eeBadScFilter_;
  mutable int Flag_trkPOG_manystripclus53X_;
  mutable int Flag_trkPOG_toomanystripclus53X_;
  mutable int Flag_trkPOG_logErrorTooManyClusters_;
  mutable int Flag_goodVertices_;
  */
  // ----------

  // CV: make sure that only one MEtFilterReader instance exists,
  static int numInstances_;
  static MEtFilterReader* instance_;

  MEtFilter* metFilter_; // NEW !

};

#endif

