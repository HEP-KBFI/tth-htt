#ifndef tthAnalysis_HiggsToTauTau_GenHadTauReader_h
#define tthAnalysis_HiggsToTauTau_GenHadTauReader_h

#include "tthAnalysis/HiggsToTauTau/interface/GenHadTau.h" // GenHadTau

#include <Rtypes.h> // Int_t, Float_t
#include <TTree.h> // TTree

#include <string>
#include <vector>
#include <map>

class GenHadTauReader
{
 public:
  GenHadTauReader();
  GenHadTauReader(const std::string& branchName_num, const std::string& branchName_obj); 
  ~GenHadTauReader();

  /**
   * @brief Call tree->SetBranchAddress for all GenHadTau branches
   */
  void setBranchAddresses(TTree* tree);

  /**
   * @brief Read branches from tree and use information to fill collection of GenHadTau objects
   * @return Collection of GenHadTau objects
   */
  std::vector<GenHadTau> read() const;
  
 protected: 
 /**
   * @brief Initialize names of branches to be read from tree
   */
  void setBranchNames();

  const int max_nHadTaus_;
  std::string branchName_num_;
  std::string branchName_obj_;

  std::string branchName_pt_;
  std::string branchName_eta_;
  std::string branchName_phi_;
  std::string branchName_mass_;
  std::string branchName_charge_;

  Int_t nHadTaus_;
  Float_t* hadTau_pt_;
  Float_t* hadTau_eta_;
  Float_t* hadTau_phi_;
  Float_t* hadTau_mass_;
  Float_t* hadTau_charge_;

  // CV: make sure that only one GenHadTauReader instance exists for a given branchName,
  //     as ROOT cannot handle multiple TTree::SetBranchAddress calls for the same branch.
  static std::map<std::string, int> numInstances_;
  static std::map<std::string, GenHadTauReader*> instances_;
};

#endif // tthAnalysis_HiggsToTauTau_GenHadTauReader_h

