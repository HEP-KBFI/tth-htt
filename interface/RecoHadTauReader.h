#ifndef tthAnalysis_HiggsToTauTau_RecoHadTauReader_h
#define tthAnalysis_HiggsToTauTau_RecoHadTauReader_h

#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTau.h" // RecoHadTau

#include <Rtypes.h> // Int_t, Double_t
#include <TTree.h> // TTree

#include <string>
#include <vector>
#include <map>

class RecoHadTauReader
{
 public:
  RecoHadTauReader();
  RecoHadTauReader(const std::string& branchName_num, const std::string& branchName_obj); 
  ~RecoHadTauReader();

  /**
   * @brief Call tree->SetBranchAddress for all RecoHadTau branches
   */
  void setBranchAddresses(TTree* tree);

  /**
   * @brief Read branches from tree and use information to fill collection of RecoHadTau objects
   * @return Collection of RecoHadTau objects
   */
  std::vector<RecoHadTau> read() const;
  
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
  std::string branchName_pdgId_;
  std::string branchName_dz_;
  std::string branchName_idDecayMode_;
  std::string branchName_idMVA_dR03_;
  std::string branchName_idMVA_dR05_;
  std::string branchName_idCombIso_dR03_;
  std::string branchName_idCombIso_dR05_;
  std::string branchName_idAgainstElec_;
  std::string branchName_idAgainstMu_;
  
  Int_t nHadTaus_;
  Double_t* hadTau_pt_;
  Double_t* hadTau_eta_;
  Double_t* hadTau_phi_;
  Double_t* hadTau_mass_;
  Int_t* hadTau_pdgId_;
  Double_t* hadTau_dz_;
  Int_t* hadTau_idDecayMode_;
  Int_t* hadTau_idMVA_dR03_;
  Int_t* hadTau_idMVA_dR05_;
  Int_t* hadTau_idCombIso_dR03_;
  Int_t* hadTau_idCombIso_dR05_;
  Int_t* hadTau_idAgainstElec_;
  Int_t* hadTau_idAgainstMu_;

  // CV: make sure that only one RecoHadronicTauReader instance exists for a given branchName,
  //     as ROOT cannot handle multiple TTree::SetBranchAddress calls for the same branch.
  static std::map<std::string, int> numInstances_;
  static std::map<std::string, RecoHadTauReader*> instances_;
};

#endif // tthAnalysis_HiggsToTauTau_RecoHadTauReader_h

