#ifndef tthAnalysis_HiggsToTauTau_RecoJetWriter_h
#define tthAnalysis_HiggsToTauTau_RecoJetWriter_h

#include "tthAnalysis/HiggsToTauTau/interface/RecoJet.h" // RecoJet

#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // kEra_2015, kEra_2016

#include <Rtypes.h> // Int_t, Float_t
#include <TTree.h> // TTree

#include <string>
#include <vector>
#include <map>

class RecoJetWriter
{
 public:
  RecoJetWriter(int era);
  RecoJetWriter(int era, const std::string& branchName_num, const std::string& branchName_obj); 
  ~RecoJetWriter();

  /**
   * @brief Call tree->Branch for all RecoJet branches
   */
  void setBranches(TTree* tree);

  /**
   * @brief Write collection of RecoJet objects to tree
   */
  void write(const std::vector<const RecoJet*>& jets);
  
 protected: 
 /**
   * @brief Initialize names of branches to be read from tree
   */
  void setBranchNames();

  int era_;
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
  std::string branchName_BtagCSVwHipMitigation_;
  std::string branchName_BtagCSVwoHipMitigation_;
  std::string branchName_BtagWeight_;
  std::map<int, std::string> branchNames_BtagWeight_systematics_;

  Int_t nJets_;
  Float_t* jet_pt_;
  Float_t* jet_eta_;
  Float_t* jet_phi_;
  Float_t* jet_mass_;
  Float_t* jet_corr_;
  Float_t* jet_corr_JECUp_;
  Float_t* jet_corr_JECDown_;
  Float_t* jet_BtagCSVwHipMitigation_;
  Float_t* jet_BtagCSVwoHipMitigation_;
  Float_t* jet_BtagWeight_;
  std::map<int, Float_t*> jet_BtagWeights_systematics_; 
};

#endif // tthAnalysis_HiggsToTauTau_RecoJetWriter_h

