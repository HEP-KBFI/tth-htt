#ifndef tthAnalysis_HiggsToTauTau_RecoElectronReader_h
#define tthAnalysis_HiggsToTauTau_RecoElectronReader_h

#include "tthAnalysis/HiggsToTauTau/interface/ReaderBase.h" // ReaderBase
#include "tthAnalysis/HiggsToTauTau/interface/RecoElectron.h" // RecoElectron

#include <map> // std::map<,>

// forward declarations
class TTree;
class RecoLeptonReader;
enum class EGammaID;
enum class EGammaWP;

class RecoElectronReader
  : public ReaderBase
{
public:
  RecoElectronReader(int era,
                     bool readGenMatching = false);
  RecoElectronReader(int era,
                     const std::string & branchName_obj,
                     bool readGenMatching = false);
  ~RecoElectronReader();

  /**
   * @brief Call tree->SetBranchAddress for all lepton branches specific to RecoElectrons
   */
  void
  setBranchAddresses(TTree * tree) override;

  /**
   * @brief Read branches from tree and use information to fill collection of RecoElectron objects
   * @return Collection of RecoElectron objects
   */
  std::vector<RecoElectron>
  read() const;

  void
  readUncorrected(bool flag);

protected:
 /**
   * @brief Initialize names of branches to be read from tree
   */
  void
  setBranchNames();

  int era_;

  std::string branchName_num_;
  std::string branchName_obj_;

  bool readUncorrected_;

  RecoLeptonReader * leptonReader_;

  std::string branchName_eCorr_;
  std::string branchName_sigmaEtaEta_;
  std::string branchName_HoE_;
  std::string branchName_deltaEta_;
  std::string branchName_deltaPhi_;
  std::string branchName_OoEminusOoP_;
  std::string branchName_lostHits_;
  std::string branchName_conversionVeto_;
  std::string branchName_cutbasedID_HLT_;

  std::map<EGammaID, std::string> branchNames_mvaRaw_POG_;
  std::map<EGammaID, std::map<EGammaWP, std::string>> branchNames_mvaID_POG_;

  Float_t * eCorr_;
  Float_t * sigmaEtaEta_;
  Float_t * HoE_;
  Float_t * deltaEta_;
  Float_t * deltaPhi_;
  Float_t * OoEminusOoP_;
  UChar_t * lostHits_;
  Bool_t * conversionVeto_;
  Int_t * cutbasedID_HLT_;

  std::map<EGammaID, Float_t *> rawMVAs_POG_;
  std::map<EGammaID, std::map<EGammaWP, Bool_t *>> mvaIDs_POG_;

  // CV: make sure that only one RecoElectronReader instance exists for a given branchName,
  //     as ROOT cannot handle multiple TTree::SetBranchAddress calls for the same branch.
  static std::map<std::string, int> numInstances_;
  static std::map<std::string, RecoElectronReader *> instances_;
};

#endif // tthAnalysis_HiggsToTauTau_RecoElectronReader_h

