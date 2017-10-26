#ifndef tthAnalysis_HiggsToTauTau_RecoMEtReader_h
#define tthAnalysis_HiggsToTauTau_RecoMEtReader_h

#include "tthAnalysis/HiggsToTauTau/interface/RecoMEt.h" // RecoMEt
#include "tthAnalysis/HiggsToTauTau/interface/ReaderBase.h" // ReaderBase

#include <Rtypes.h> // Int_t, Double_t
#include <TTree.h> // TTree

#include <string>
#include <vector>
#include <map>

class RecoMEtReader
  : public ReaderBase
{
 public:
  RecoMEtReader(int era);
  RecoMEtReader(int era, const std::string& branchName_obj, const std::string& branchName_cov = "met");
  ~RecoMEtReader();

  /**
   * @brief Call tree->SetBranchAddress for all RecoMEt branches
   */
  void setBranchAddresses(TTree* tree) override;

  /**
   * @brief Read branches from tree and use information to fill RecoMEt object
   * @return RecoMEt object
   */
  RecoMEt read() const;

 protected:
 /**
   * @brief Initialize names of branches to be read from tree
   */
  void setBranchNames();

  int era_;
  std::string branchName_obj_;
  std::string branchName_cov_;

  std::string branchName_pt_;
  std::string branchName_phi_;
  std::string branchName_covXX_;
  std::string branchName_covXY_;
  std::string branchName_covYY_;

  Float_t met_pt_;
  Float_t met_phi_;
  Float_t met_covXX_;
  Float_t met_covXY_;
  Float_t met_covYY_;

  // CV: make sure that only one RecoMEtReader instance exists for a given branchName,
  //     as ROOT cannot handle multiple TTree::SetBranchAddress calls for the same branch.
  static std::map<std::string, int> numInstances_;
  static std::map<std::string, RecoMEtReader*> instances_;
};

#endif // tthAnalysis_HiggsToTauTau_RecoMEtReader_h

