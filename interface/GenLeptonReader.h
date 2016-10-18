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
  GenLeptonReader(const std::string& branchName_nPromptLeptons, const std::string& branchName_promptLeptons,
		  const std::string& branchName_nLeptonsFromTau, const std::string& branchName_leptonsFromTau); 
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

  // electrons and muons from W and Z boson decays
  const int max_nPromptLeptons_;
  std::string branchName_nPromptLeptons_; 
  std::string branchName_promptLeptons_;
  
  // electrons and muons from tau decays
  const int max_nLeptonsFromTau_;
  std::string branchName_nLeptonsFromTau_;
  std::string branchName_leptonsFromTau_;

  std::string branchName_promptLepton_pt_;
  std::string branchName_promptLepton_eta_;
  std::string branchName_promptLepton_phi_;
  std::string branchName_promptLepton_mass_;
  std::string branchName_promptLepton_pdgId_;

  Int_t nPromptLeptons_;
  Float_t* promptLepton_pt_;
  Float_t* promptLepton_eta_;
  Float_t* promptLepton_phi_;
  Float_t* promptLepton_mass_;
  Int_t* promptLepton_pdgId_;

  std::string branchName_leptonFromTau_pt_;
  std::string branchName_leptonFromTau_eta_;
  std::string branchName_leptonFromTau_phi_;
  std::string branchName_leptonFromTau_mass_;
  std::string branchName_leptonFromTau_pdgId_;

  Int_t nLeptonsFromTau_;
  Float_t* leptonFromTau_pt_;
  Float_t* leptonFromTau_eta_;
  Float_t* leptonFromTau_phi_;
  Float_t* leptonFromTau_mass_;
  Int_t* leptonFromTau_pdgId_;

  // CV: make sure that only one GenLeptonReader instance exists for a given branchName,
  //     as ROOT cannot handle multiple TTree::SetBranchAddress calls for the same branch.
  static std::map<std::string, int> numInstances_;
  static std::map<std::string, GenLeptonReader*> instances_;
};

#endif // tthAnalysis_HiggsToTauTau_GenLeptonReader_h

