#ifndef tthAnalysis_HiggsToTauTau_RecoLeptonReader_h
#define tthAnalysis_HiggsToTauTau_RecoLeptonReader_h

#include "tthAnalysis/HiggsToTauTau/interface/RecoLepton.h" // RecoLepton

#include <Rtypes.h> // Int_t, Float_t
#include <TTree.h> // TTree

#include <string>
#include <vector>
#include <map>

class RecoLeptonReader
{
 public:
  RecoLeptonReader();
  RecoLeptonReader(const std::string& branchName_num, const std::string& branchName_obj);
  ~RecoLeptonReader();

  /**
   * @brief Call tree->SetBranchAddress for all lepton branches common to RecoElectrons and RecoMuons
   */
  void setBranchAddresses(TTree* tree);

  friend class RecoElectronReader;
  friend class RecoMuonReader;

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
  std::string branchName_dxy_;
  std::string branchName_dz_;
  std::string branchName_relIso_;
  std::string branchName_chargedHadRelIso03_;
  std::string branchName_miniIsoCharged_;
  std::string branchName_miniIsoNeutral_;
  std::string branchName_sip3d_;
  std::string branchName_mvaRawTTH_;
  std::string branchName_jetNDauChargedMVASel_;
  std::string branchName_jetPtRel_;
  std::string branchName_jetPtRatio_;
  std::string branchName_jetBtagCSV_;
  std::string branchName_tightCharge_;
  std::string branchName_charge_;

  Int_t nLeptons_;
  Float_t* pt_;
  Float_t* eta_;
  Float_t* phi_;
  Float_t* mass_;
  Int_t* pdgId_;
  Float_t* dxy_;
  Float_t* dz_;
  Float_t* relIso_;
  Float_t* chargedHadRelIso03_;
  Float_t* miniIsoCharged_;
  Float_t* miniIsoNeutral_;
  Float_t* sip3d_;
  Float_t* mvaRawTTH_;
  Float_t* jetNDauChargedMVASel_;
  Float_t* jetPtRel_;
  Float_t* jetPtRatio_;
  Float_t* jetBtagCSV_;
  Int_t* tightCharge_;
  Int_t* charge_;

  // CV: make sure that only one RecoLeptonReader instance exists for a given branchName,
  //     as ROOT cannot handle multiple TTree::SetBranchAddress calls for the same branch.
  static std::map<std::string, int> numInstances_;
  static std::map<std::string, RecoLeptonReader*> instances_;
};

#endif // tthAnalysis_HiggsToTauTau_RecoLeptonReader_h
