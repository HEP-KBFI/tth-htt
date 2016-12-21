#ifndef tthAnalysis_HiggsToTauTau_RecoLeptonWriter_h
#define tthAnalysis_HiggsToTauTau_RecoLeptonWriter_h

#include "tthAnalysis/HiggsToTauTau/interface/RecoLepton.h" // RecoLepton

#include <Rtypes.h> // Int_t, Float_t
#include <TTree.h> // TTree

#include <string>
#include <vector>

class RecoLeptonWriter
{
 public:
  RecoLeptonWriter(const std::string& branchName_num, const std::string& branchName_obj);
  ~RecoLeptonWriter();

  /**
   * @brief Call tree->Branch for all lepton branches common to RecoElectrons and RecoMuons
   */
  void setBranches(TTree* tree);

  /**
   * @brief Write branches common to RecoElectrons and RecoMuons to tree
   */
  template<typename T>
  void write(const std::vector<const T*>& leptons)
  {
    nLeptons_ = leptons.size();
    for ( Int_t idxLepton = 0; idxLepton < nLeptons_; ++idxLepton ) {
      const T* lepton = leptons[idxLepton];
      assert(lepton);
      pt_[idxLepton] = lepton->lepton_pt();
      eta_[idxLepton] = lepton->eta();
      phi_[idxLepton] = lepton->phi();
      mass_[idxLepton] = lepton->mass();
      pdgId_[idxLepton] = lepton->pdgId();
      dxy_[idxLepton] = lepton->dxy();
      dz_[idxLepton] = lepton->dz();
      relIso_[idxLepton] = lepton->relIso();
      chargedHadRelIso03_[idxLepton] = lepton->chargedHadRelIso03();
      miniIsoCharged_[idxLepton] = lepton->miniIsoCharged();
      miniIsoNeutral_[idxLepton] = lepton->miniIsoNeutral();
      sip3d_[idxLepton] = lepton->sip3d();
      mvaRawTTH_[idxLepton] = lepton->mvaRawTTH();
      jetNDauChargedMVASel_[idxLepton] = lepton->jetNDauChargedMVASel();
      jetPtRel_[idxLepton] = lepton->jetPtRel();
      jetPtRatio_[idxLepton] = lepton->jetPtRatio();
      jetBtagCSV_[idxLepton] = lepton->jetBtagCSV();
      tightCharge_[idxLepton] = lepton->tightCharge();
      charge_[idxLepton] = lepton->charge();
    }
  }

  friend class RecoElectronWriter;
  friend class RecoMuonWriter;

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
};

#endif // tthAnalysis_HiggsToTauTau_RecoLeptonWriter_h
