#ifndef tthAnalysis_HiggsToTauTau_GenLeptonReader_h
#define tthAnalysis_HiggsToTauTau_GenLeptonReader_h

#include "tthAnalysis/HiggsToTauTau/interface/GenLepton.h" // GenLepton

#include <Rtypes.h> // Int_t, Double_t
#include <TTree.h> // TTree

#include <string>
#include <vector>
#include <map>

class GenLeptonReader
{
 public:
  GenLeptonReader();
  GenLeptonReader(const std::string& branchName_num, const std::string& branchName_obj); 
  ~GenLeptonReader();

  /**
   * @brief Call tree->SetBranchAddress for all GenLepton branches
   */
  void setBranchAddresses(TTree* tree);

  /**
   * @brief Read branches from tree and use information to fill collection of GenLepton objects
   * @return Collection of GenLepton objects
   */
  std::vector<GenLepton> read() const;
  
 protected: 
 /**
   * @brief Initialize names of branches to be read from tree
   */
  void setBranchNames();

  const int max_nLeptons_;
  std::string branchName_num_;
  std::string branchName_obj_;

  std::string branchName_pt_;
  std::string branchName_eta_;
  std::string branchName_phi_;
  std::string branchName_mass_;
  std::string branchName_pdgId_;

  Int_t nLeptons_;
  Double_t* lepton_pt_;
  Double_t* lepton_eta_;
  Double_t* lepton_phi_;
  Double_t* lepton_mass_;
  Int_t* lepton_pdgId_;

  // CV: make sure that only one GenLeptonReader instance exists for a given branchName,
  //     as ROOT cannot handle multiple TTree::SetBranchAddress calls for the same branch.
  static std::map<std::string, int> numInstances_;
  static std::map<std::string, GenLeptonReader*> instances_;
};

#endif // tthAnalysis_HiggsToTauTau_GenLeptonReader_h

