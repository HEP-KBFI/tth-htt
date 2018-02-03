#ifndef tthAnalysis_HiggsToTauTau_MEtFilterReader_h
#define tthAnalysis_HiggsToTauTau_MEtFilterReader_h

#include "tthAnalysis/HiggsToTauTau/interface/ReaderBase.h" // ReaderBase

// forward declarations
class MEtFilter;

class MEtFilterReader
  : public ReaderBase
{
public:
  MEtFilterReader(MEtFilter * metFilter);
  ~MEtFilterReader();

  void
  setBranchAddresses(TTree * tree) override;

protected:
 /**
   * @brief Initialize names of branches to be read from tree
   */
  void
  setBranchNames();

  std::string branchNameFlag_HBHENoiseIsoFilter_;
  std::string branchNameFlag_EcalDeadCellTriggerPrimitiveFilter_;
  std::string branchNameFlag_ecalLaserCorrFilter_;
  std::string branchNameFlag_hcalLaserEventFilter_;
  std::string branchNameFlag_muonBadTrackFilter_;
  std::string branchNameFlag_trkPOGFilters_;
//  std::string branchNameFlag_trackingFailureFilter_; // Karl: missing in nanoAOD
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
  static MEtFilterReader * instance_;

  MEtFilter * metFilter_;
};

#endif

