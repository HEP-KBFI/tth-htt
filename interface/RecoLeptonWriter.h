#ifndef tthAnalysis_HiggsToTauTau_RecoLeptonWriter_h
#define tthAnalysis_HiggsToTauTau_RecoLeptonWriter_h

#include "tthAnalysis/HiggsToTauTau/interface/RecoLepton.h" // RecoLepton
#include "tthAnalysis/HiggsToTauTau/interface/GenParticleWriter.h" // GenParticleWriter
#include "tthAnalysis/HiggsToTauTau/interface/GenLepton.h" // GenLepton
#include "tthAnalysis/HiggsToTauTau/interface/GenHadTau.h" // GenHadTau
#include "tthAnalysis/HiggsToTauTau/interface/GenJet.h" // GenJet

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
    writeGenMatching(leptons);
  }

  /**
   * @brief Write branches containing information on matching of RecoElectrons and RecoMuons 
   *        to generator level electrons, muons, hadronic taus, and jets to tree
   */
  template<typename T>
  void writeGenMatching(const std::vector<const T*>& leptons)
  {
    std::vector<GenParticle> matched_genLeptons;
    std::vector<GenParticle> matched_genHadTaus;
    std::vector<GenParticle> matched_genJets;
    assert(nLeptons_ == (int)leptons.size());
    for ( Int_t idxLepton = 0; idxLepton < nLeptons_; ++idxLepton ) {
      const T* lepton = leptons[idxLepton];
      assert(lepton);
      const GenLepton* matched_genLepton = lepton->genLepton();
      if ( matched_genLepton ) matched_genLeptons.push_back(static_cast<GenParticle>(*matched_genLepton));
      else matched_genLeptons.push_back(dummyGenParticle_);
      const GenHadTau* matched_genHadTau = lepton->genHadTau();
      if ( matched_genHadTau ) matched_genHadTaus.push_back(static_cast<GenParticle>(*matched_genHadTau));
      else matched_genHadTaus.push_back(dummyGenParticle_);
      const GenJet* matched_genJet = lepton->genJet();
      if ( matched_genJet ) matched_genJets.push_back(static_cast<GenParticle>(*matched_genJet));
      else matched_genJets.push_back(dummyGenParticle_);
    }
    genLeptonWriter_->write(matched_genLeptons);
    genHadTauWriter_->write(matched_genHadTaus);
    genJetWriter_->write(matched_genJets);
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

  GenParticleWriter* genLeptonWriter_;
  GenParticleWriter* genHadTauWriter_;
  GenParticleWriter* genJetWriter_;
  GenParticle dummyGenParticle_;

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
