#ifndef tthAnalysis_HiggsToTauTau_MEtFilterReader_h
#define tthAnalysis_HiggsToTauTau_MEtFilterReader_h

#include "tthAnalysis/HiggsToTauTau/interface/ReaderBase.h" // ReaderBase
#include "tthAnalysis/HiggsToTauTau/interface/MEtFilter.h" 



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

  // CV: make sure that only one MEtFilterReader instance exists,
  static int numInstances_;
  static MEtFilterReader* instance_;

  MEtFilter* metFilter_; // NEW !

};

#endif

