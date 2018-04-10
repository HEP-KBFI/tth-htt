#ifndef tthAnalysis_HiggsToTauTau_RecoJetReaderAK12_h
#define tthAnalysis_HiggsToTauTau_RecoJetReaderAK12_h

#include "tthAnalysis/HiggsToTauTau/interface/ReaderBase.h" // ReaderBase
#include "tthAnalysis/HiggsToTauTau/interface/RecoJetAK12.h" // RecoJetAK12

#include <map> // std::map<,>

// forward declarations
class TTree;
class RecoSubjetReaderAK12;

class RecoJetReaderAK12
  : public ReaderBase
{
public:
  RecoJetReaderAK12(int era);
  RecoJetReaderAK12(int era,
		    const std::string & branchName_jet, const std::string & branchName_subjet);
  ~RecoJetReaderAK12();

  /**
   * @brief Call tree->SetBranchAddress for all RecoJetAK12 branches
   */
  void
  setBranchAddresses(TTree * tree) override;

  /**
   * @brief Read branches from tree and use information to fill collection of RecoJetAK12 objects
   * @return Collection of RecoJetAK12 objects
   */
  std::vector<RecoJetAK12>
  read() const;

protected:
 /**
   * @brief Initialize names of branches to be read from tree
   */
  void
  setBranchNames();

  int era_;
  const unsigned int max_nJets_;
  std::string branchName_num_;
  std::string branchName_obj_;

  RecoSubjetReaderAK12 * subjetReader_;

  std::string branchName_pt_;
  std::string branchName_eta_;
  std::string branchName_phi_;
  std::string branchName_mass_;
  std::string branchName_jetCharge_;
  std::string branchName_pullEta_;
  std::string branchName_pullPhi_;
  std::string branchName_pullMag_;
  std::string branchName_QjetVolatility_;
  std::string branchName_msoftdrop_;
  std::string branchName_subJetIdx1_;
  std::string branchName_subJetIdx2_;
  std::string branchName_tau1_;
  std::string branchName_tau2_;
  std::string branchName_tau3_;
  std::string branchName_tau4_;

  UInt_t nJets_;
  Float_t * jet_pt_;
  Float_t * jet_eta_;
  Float_t * jet_phi_;
  Float_t * jet_mass_;
  Float_t * jet_charge_;
  Float_t * jet_pullEta_;
  Float_t * jet_pullPhi_;
  Float_t * jet_pullMag_;
  Float_t * jet_QjetVolatility_;
  Float_t * jet_msoftdrop_;
  Int_t * subjet_idx1_;
  Int_t * subjet_idx2_;
  Float_t * jet_tau1_;
  Float_t * jet_tau2_;
  Float_t * jet_tau3_;
  Float_t * jet_tau4_;

  // CV: make sure that only one RecoJetReaderAK12 instance exists for a given branchName,
  //     as ROOT cannot handle multiple TTree::SetBranchAddress calls for the same branch.
  static std::map<std::string, int> numInstances_;
  static std::map<std::string, RecoJetReaderAK12 *> instances_;
};

#endif // tthAnalysis_HiggsToTauTau_RecoJetReaderAK12_h
