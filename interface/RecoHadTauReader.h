#ifndef tthAnalysis_HiggsToTauTau_RecoHadTauReader_h
#define tthAnalysis_HiggsToTauTau_RecoHadTauReader_h

#include "tthAnalysis/HiggsToTauTau/interface/ReaderBase.h" // ReaderBase
#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTau.h" // RecoHadTau

#include <map> // std::map<,>

// forward declarations
class TFile;
class TGraphAsymmErrors;
class TFormula;
class TTree;
class GenLeptonReader;
class GenHadTauReader;
class GenJetReader;

class RecoHadTauReader
  : public ReaderBase
{
public:
  RecoHadTauReader(int era,
                   bool readGenMatching = false);
  RecoHadTauReader(int era,
                   const std::string & branchName_obj,
                   bool readGenMatching = false);
  ~RecoHadTauReader();

  void
  setHadTauPt_central_or_shift(int hadTauPt_option);

  /**
   * @brief Call tree->SetBranchAddress for all RecoHadTau branches
   */
  void
  setBranchAddresses(TTree * tree) override;

  /**
   * @brief Read branches from tree and use information to fill collection of RecoHadTau objects
   * @return Collection of RecoHadTau objects
   */
  std::vector<RecoHadTau>
  read() const;

protected:
  /**
   * @brief Compute "VVLose" (95% signal efficiency) working point for tau ID MVA trained for dR=0.3 isolation cone,
   *        used to enhance background event statistics for training of event-level MVAs that separate ttH signal from backgrounds
   */
  void
  readDBdR03oldDMwLTEff95();

  TFile * tauIdMVArun2dR03DB_wpFile_;
  TGraphAsymmErrors * DBdR03oldDMwLTEff95_;
  TFormula * mvaOutput_normalization_DBdR03oldDMwLT_;

  /**
   * @brief Initialize names of branches to be read from tree
   */
  void
  setBranchNames();

  int era_;
  const int max_nHadTaus_;
  std::string branchName_num_;
  std::string branchName_obj_;

  /**
   * @brief Read branches containing information on matching of RecoHadTau objects
   *        to generator level electrons, muons, hadronic taus, and jets from tree
   *        and add this information to collection of RecoHadTau objects given as function argument
   */
  void
  readGenMatching(std::vector<RecoHadTau> & hadTaus) const;

  GenLeptonReader * genLeptonReader_;
  GenHadTauReader * genHadTauReader_;
  GenJetReader * genJetReader_;
  bool readGenMatching_;

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
  std::string branchName_idCombIso_dR03_;
  std::string branchName_isoCombIso_dR03_;
  std::string branchName_rawCombIso_dR03_;
  std::string branchName_idCombIso_dR05_;
  std::string branchName_isoCombIso_dR05_;
  std::string branchName_idAgainstElec_;
  std::string branchName_idAgainstMu_;
  std::string branchName_filterBits_;

  int hadTauPt_option_;

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
  Int_t * hadTau_idCombIso_dR03_;
  Float_t * hadTau_rawCombIso_dR03_;
  Int_t * hadTau_idCombIso_dR05_;
  Float_t * hadTau_rawCombIso_dR05_;
  Int_t * hadTau_idAgainstElec_;
  Int_t * hadTau_idAgainstMu_;
  UInt_t * hadTau_filterBits_;

  // CV: make sure that only one RecoHadronicTauReader instance exists for a given branchName,
  //     as ROOT cannot handle multiple TTree::SetBranchAddress calls for the same branch.
  static std::map<std::string, int> numInstances_;
  static std::map<std::string, RecoHadTauReader *> instances_;
};

#endif // tthAnalysis_HiggsToTauTau_RecoHadTauReader_h

