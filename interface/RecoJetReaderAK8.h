#ifndef tthAnalysis_HiggsToTauTau_RecoJetReaderAK8_h
#define tthAnalysis_HiggsToTauTau_RecoJetReaderAK8_h

#include "tthAnalysis/HiggsToTauTau/interface/ReaderBase.h" // ReaderBase
#include "tthAnalysis/HiggsToTauTau/interface/RecoJetAK8.h" // RecoJetAK8

#include <map> // std::map<,>

// forward declarations
class TTree;
class RecoSubjetReaderAK8;

class RecoJetReaderAK8
  : public ReaderBase
{
public:
  RecoJetReaderAK8(int era,
                   bool isMC);
  RecoJetReaderAK8(int era,
                   bool isMC,
                   const std::string & branchName_jet,
                   const std::string & branchName_subjet);
  ~RecoJetReaderAK8();

  void
  set_central_or_shift(int central_or_shift);

  void
  read_sys(bool flag);

  /**
   * @brief Call tree->SetBranchAddress for all RecoJetAK8 branches
   */
  void
  setBranchAddresses(TTree * tree) override;

  /**
   * @brief Read branches from tree and use information to fill collection of RecoJetAK8 objects
   * @return Collection of RecoJetAK8 objects
   */
  std::vector<RecoJetAK8>
  read() const;

protected:
 /**
   * @brief Initialize names of branches to be read from tree
   */
  void
  setBranchNames();

  int era_;
  bool isMC_;
  const unsigned int max_nJets_;
  std::string branchName_num_;
  std::string branchName_obj_;

  RecoSubjetReaderAK8 * subjetReader_;

  int sysOption_central_;
  int sysOption_;
  bool readSys_;

  std::string branchName_eta_;
  std::string branchName_phi_;
  std::string branchName_subJetIdx1_;
  std::string branchName_subJetIdx2_;
  std::string branchName_tau1_;
  std::string branchName_tau2_;
  std::string branchName_tau3_;
  std::string branchName_tau4_;
  std::string branchName_jetId_;

  std::map<int, std::string> branchNames_pt_systematics_;
  std::map<int, std::string> branchNames_mass_systematics_;
  std::map<int, std::string> branchNames_msoftdrop_systematics_;

  const std::string pt_str_;
  const std::string mass_str_;
  const std::string msoftdrop_str_;

  UInt_t nJets_;
  Float_t * jet_eta_;
  Float_t * jet_phi_;
  Int_t * subjet_idx1_;
  Int_t * subjet_idx2_;
  Float_t * jet_tau1_;
  Float_t * jet_tau2_;
  Float_t * jet_tau3_;
  Float_t * jet_tau4_;
  Int_t * jet_jetId_;

  std::map<int, Float_t *> jet_pt_systematics_;
  std::map<int, Float_t *> jet_mass_systematics_;
  std::map<int, Float_t *> jet_msoftdrop_systematics_;

  // CV: make sure that only one RecoJetReaderAK8 instance exists for a given branchName,
  //     as ROOT cannot handle multiple TTree::SetBranchAddress calls for the same branch.
  static std::map<std::string, int> numInstances_;
  static std::map<std::string, RecoJetReaderAK8 *> instances_;
};

#endif // tthAnalysis_HiggsToTauTau_RecoJetReaderAK8_h
