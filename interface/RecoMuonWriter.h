#ifndef tthAnalysis_HiggsToTauTau_RecoMuonWriter_h
#define tthAnalysis_HiggsToTauTau_RecoMuonWriter_h

#include "tthAnalysis/HiggsToTauTau/interface/RecoMuon.h" // RecoMuon
#include "tthAnalysis/HiggsToTauTau/interface/RecoLeptonWriter.h" // RecoLeptonWriter

#include <Rtypes.h> // Int_t
#include <TTree.h> // TTree

#include <string>
#include <vector>

class RecoMuonWriter
{
 public:
  RecoMuonWriter(int era);
  RecoMuonWriter(int era, const std::string& branchName_num, const std::string& branchName_obj); 
  ~RecoMuonWriter();

  /**
   * @brief Call tree->Branch for all lepton branches specific to RecoMuons
   */
  void setBranches(TTree* tree);

  /**
   * @brief Write branches specific to RecoMuons to tree
   */
  void write(const std::vector<const RecoMuon*>& leptons);
  
 protected: 
 /**
   * @brief Initialize names of branches to be read from tree
   */
  void setBranchNames();

  int era_;
  std::string branchName_num_;
  std::string branchName_obj_;

  RecoLeptonWriter* leptonWriter_;

  std::string branchName_looseIdPOG_; 
  std::string branchName_mediumIdPOG_;
  std::string branchName_segmentCompatibility_;

  Bool_t* looseIdPOG_;
  Bool_t* mediumIdPOG_;
  Float_t* segmentCompatibility_;
};

#endif // tthAnalysis_HiggsToTauTau_RecoMuonWriter_h

