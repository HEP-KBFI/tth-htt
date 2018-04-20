#ifndef tthAnalysis_HiggsToTauTau_RecoElectronWriter_h
#define tthAnalysis_HiggsToTauTau_RecoElectronWriter_h

#include <Rtypes.h> // *_t

#include <string> // std::string
#include <vector> // std::vector<>

// forward declarations
class TTree;
class RecoElectron;
class RecoLeptonWriter;

class RecoElectronWriter
{
public:
  RecoElectronWriter(int era);
  RecoElectronWriter(int era,
                     const std::string & branchName_obj);
  RecoElectronWriter(int era,
                     const std::string & branchName_num,
                     const std::string & branchName_obj);
  ~RecoElectronWriter();

  /**
   * @brief Call tree->Branch for all lepton branches specific to RecoElectrons
   */
  void
  setBranches(TTree * tree);

  /**
   * @brief Write branches specific to RecoElectrons to tree
   */
  void
  write(const std::vector<const RecoElectron *>& leptons);

  void
  writeUncorrected(bool flag);

protected:
 /**
   * @brief Initialize names of branches to be read from tree
   */
  void
  setBranchNames();

  int era_;

  std::string branchName_num_;
  std::string branchName_obj_;

  bool writeUncorrected_;

  RecoLeptonWriter * leptonWriter_;

  std::string branchName_eCorr_;
  std::string branchName_mvaRaw_POG_;
  std::string branchName_mvaID_POG_;
  std::string branchName_sigmaEtaEta_;
  std::string branchName_HoE_;
  std::string branchName_deltaEta_;
  std::string branchName_deltaPhi_;
  std::string branchName_OoEminusOoP_;
  std::string branchName_lostHits_;
  std::string branchName_conversionVeto_;
  std::string branchName_cutbasedID_HLT_;

  Float_t * eCorr_;
  Float_t * mvaRaw_POG_;
  Bool_t * mvaID_POG_;
  Float_t * sigmaEtaEta_;
  Float_t * HoE_;
  Float_t * deltaEta_;
  Float_t * deltaPhi_;
  Float_t * OoEminusOoP_;
  UChar_t * lostHits_;
  Bool_t * conversionVeto_;
  Int_t * cutbasedID_HLT_;
};

#endif // tthAnalysis_HiggsToTauTau_RecoElectronWriter_h

