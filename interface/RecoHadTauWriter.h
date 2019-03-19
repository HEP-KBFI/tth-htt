#ifndef tthAnalysis_HiggsToTauTau_RecoHadTauWriter_h
#define tthAnalysis_HiggsToTauTau_RecoHadTauWriter_h

#include "tthAnalysis/HiggsToTauTau/interface/GenParticle.h" // GenParticle, *_t

#include <string> // std::string
#include <vector> // std::vector<>

// forward declarations
class TTree;
class RecoHadTau;
class GenParticleWriter;

class RecoHadTauWriter
{
public:
  RecoHadTauWriter(int era);
  RecoHadTauWriter(int era,
                   const std::string & branchName_obj);
  RecoHadTauWriter(int era,
                   const std::string & branchName_num,
                   const std::string & branchName_obj);
  ~RecoHadTauWriter();

  /**
   * @brief Call tree->SetBranchAddress for all RecoHadTau branches
   */
  void setBranches(TTree * tree);

  /**
   * @brief Write collection of RecoHadTau objects to tree
   */
  void write(const std::vector<const RecoHadTau *> & hadTaus);
  
  /**
   * @brief Write branches containing information on matching of RecoHadTau objects
   *        to generator level electrons, muons, hadronic taus, and jets to tree
   */
  void writeGenMatching(const std::vector<const RecoHadTau *> & hadTaus);

protected:
 /**
   * @brief Initialize names of branches to be written to tree
   */
  void setBranchNames();

  int era_;
  const int max_nHadTaus_;
  std::string branchName_num_;
  std::string branchName_obj_;

  GenParticleWriter * genLeptonWriter_;
  GenParticleWriter * genHadTauWriter_;
  GenParticleWriter * genJetWriter_;
  GenParticle dummyGenParticle_;

  std::string branchName_pt_;
  std::string branchName_eta_;
  std::string branchName_phi_;
  std::string branchName_mass_;
  std::string branchName_charge_;
  std::string branchName_dxy_;
  std::string branchName_dz_;
  std::string branchName_decayMode_;
  std::string branchName_idDecayMode_;
  std::string branchName_idDecayModeNewDMs_;
  std::string branchName_idMVA_dR03_;
  std::string branchName_rawMVA_dR03_;
  std::string branchName_idMVA_dR05_;
  std::string branchName_rawMVA_dR05_;
  std::string branchName_idAgainstElec_;
  std::string branchName_idAgainstMu_;
  std::string branchName_filterBits_;

  UInt_t nHadTaus_;
  Float_t * hadTau_pt_;
  Float_t * hadTau_eta_;
  Float_t * hadTau_phi_;
  Float_t * hadTau_mass_;
  Int_t * hadTau_charge_;
  Float_t * hadTau_dxy_;
  Float_t * hadTau_dz_;
  Int_t * hadTau_decayMode_;
  Bool_t * hadTau_idDecayMode_;
  Bool_t * hadTau_idDecayModeNewDMs_;
  Int_t * hadTau_idMVA_dR03_;
  Float_t * hadTau_rawMVA_dR03_;
  Int_t * hadTau_idMVA_dR05_;
  Float_t * hadTau_rawMVA_dR05_;
  Int_t * hadTau_idAgainstElec_;
  Int_t * hadTau_idAgainstMu_;
  UInt_t * hadTau_filterBits_;
};

#endif // tthAnalysis_HiggsToTauTau_RecoHadTauWriter_h

