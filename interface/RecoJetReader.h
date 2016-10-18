#ifndef tthAnalysis_HiggsToTauTau_RecoJetReader_h
#define tthAnalysis_HiggsToTauTau_RecoJetReader_h

#include "tthAnalysis/HiggsToTauTau/interface/RecoJet.h" // RecoJet

#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // kEra_2015, kEra_2016

#include <Rtypes.h> // Int_t, Float_t
#include <TTree.h> // TTree

#include <string>
#include <vector>
#include <map>

class RecoJetReader
{
 public:
  RecoJetReader(int era);
  RecoJetReader(int era, const std::string& branchName_num, const std::string& branchName_obj); 
  ~RecoJetReader();

  enum { kJetPt_central, kJetPt_jecUp, kJetPt_jecDown };
  void setJetPt_central_or_shift(int jetPt_option) { jetPt_option_ = jetPt_option; }

  void enable_HIP_mitigation() { 
    std::cout << "<RecoJetReader::enable_HIP_mitigation>:" << std::endl; 
    if ( era_ == kEra_2016 ) {
      branchName_BtagCSV_ = Form("%s_%s", branchName_obj_.data(), "btagCSV"); // CV: CSV algorithm with HIP mitigation
    }
    use_HIP_mitigation_ = true; 
  }
  void disable_HIP_mitigation() { 
    std::cout << "<RecoJetReader::disable_HIP_mitigation>:" << std::endl; 
    if ( era_ == kEra_2016 ) {
      branchName_BtagCSV_ = Form("%s_%s", branchName_obj_.data(), "btagNoHipMitigation"); // CV: CSV algorithm without HIP mitigation
    }
    use_HIP_mitigation_ = false; 
  }

  void setBranchName_BtagWeight(const std::string& branchName_BtagWeight) { branchName_BtagWeight_ = branchName_BtagWeight; }

  /**
   * @brief Call tree->SetBranchAddress for all RecoJet branches
   */
  void setBranchAddresses(TTree* tree);

  /**
   * @brief Read branches from tree and use information to fill collection of RecoJet objects
   * @return Collection of RecoJet objects
   */
  std::vector<RecoJet> read() const;
  
 protected: 
 /**
   * @brief Initialize names of branches to be read from tree
   */
  void setBranchNames();

  int era_;
  bool use_HIP_mitigation_;
  const int max_nJets_;
  std::string branchName_num_;
  std::string branchName_obj_;

  std::string branchName_pt_;  
  std::string branchName_eta_;
  std::string branchName_phi_;
  std::string branchName_mass_;
  std::string branchName_corr_;
  std::string branchName_corr_JECUp_;
  std::string branchName_corr_JECDown_;
  std::string branchName_BtagCSV_;
  std::string branchName_BtagWeight_;

  int jetPt_option_;

  Int_t nJets_;
  Float_t* jet_pt_;
  Float_t* jet_eta_;
  Float_t* jet_phi_;
  Float_t* jet_mass_;
  Float_t* jet_corr_;
  Float_t* jet_corr_JECUp_;
  Float_t* jet_corr_JECDown_;
  Float_t* jet_BtagCSV_;
  Float_t* jet_BtagWeight_;

  // CV: make sure that only one RecoJetReader instance exists for a given branchName,
  //     as ROOT cannot handle multiple TTree::SetBranchAddress calls for the same branch.
  static std::map<std::string, int> numInstances_;
  static std::map<std::string, RecoJetReader*> instances_;
};

#endif // tthAnalysis_HiggsToTauTau_RecoJetReader_h

