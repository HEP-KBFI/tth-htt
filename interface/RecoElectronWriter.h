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
                     const std::string & branchName_num,
                     const std::string & branchName_obj);
  ~RecoElectronWriter();

  /**
   * @brief Call tree->Branch for all lepton branches specific to RecoElectrons
   */
  void setBranches(TTree * tree);

  /**
   * @brief Write branches specific to RecoElectrons to tree
   */
  void write(const std::vector<const RecoElectron *>& leptons);
  
 protected: 
 /**
   * @brief Initialize names of branches to be read from tree
   */
  void setBranchNames();

  std::string branchName_num_;
  std::string branchName_obj_;

  RecoLeptonWriter * leptonWriter_;

  std::string branchName_mvaRawPOG_GP_; 
  std::string branchName_mvaRawPOG_HZZ_; 
  std::string branchName_sigmaEtaEta_;
  std::string branchName_HoE_;
  std::string branchName_deltaEta_;
  std::string branchName_deltaPhi_;
  std::string branchName_OoEminusOoP_;
  std::string branchName_lostHits_;
  std::string branchName_conversionVeto_;

  Float_t * mvaRawPOG_GP_;
  Float_t * mvaRawPOG_HZZ_;
  Float_t * sigmaEtaEta_;
  Float_t * HoE_;
  Float_t * deltaEta_;
  Float_t * deltaPhi_;
  Float_t * OoEminusOoP_;
  UChar_t * lostHits_;
  Bool_t * conversionVeto_;
};

#endif // tthAnalysis_HiggsToTauTau_RecoElectronWriter_h

