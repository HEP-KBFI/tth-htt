#ifndef tthAnalysis_HiggsToTauTau_RecoJetReaderHTTv2_h
#define tthAnalysis_HiggsToTauTau_RecoJetReaderHTTv2_h

#include "tthAnalysis/HiggsToTauTau/interface/ReaderBase.h" // ReaderBase
#include "tthAnalysis/HiggsToTauTau/interface/RecoJetHTTv2.h" // RecoJetHTTv2

#include <map> // std::map<,>

// forward declarations
class TTree;
class RecoSubjetReaderHTTv2;

class RecoJetReaderHTTv2
  : public ReaderBase
{
public:
  RecoJetReaderHTTv2(int era);
  RecoJetReaderHTTv2(int era,
                     const std::string & branchName_jet,
                     const std::string & branchName_subjet);
  ~RecoJetReaderHTTv2();

  /**
   * @brief Call tree->SetBranchAddress for all RecoJetHTTv2 branches
   */
  void
  setBranchAddresses(TTree * tree) override;

  /**
   * @brief Read branches from tree and use information to fill collection of RecoJetHTTv2 objects
   * @return Collection of RecoJetHTTv2 objects
   */
  std::vector<RecoJetHTTv2>
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

  RecoSubjetReaderHTTv2 * subjetReader_;
 
  std::string branchName_pt_;
  std::string branchName_eta_;
  std::string branchName_phi_;
  std::string branchName_mass_;
  std::string branchName_area_;
  std::string branchName_subjetIdx1_;
  std::string branchName_subjetIdx2_;
  std::string branchName_subjetIdx3_;
  std::string branchName_fRec_;
  std::string branchName_Ropt_;
  std::string branchName_RoptCalc_;
  std::string branchName_ptForRoptCalc_;
  std::string branchName_tau1_;
  std::string branchName_tau2_;
  std::string branchName_tau3_;

  UInt_t nJets_;
  Float_t * jet_pt_;
  Float_t * jet_eta_;
  Float_t * jet_phi_;
  Float_t * jet_mass_;
  Float_t * jet_area_;
  Int_t * subjet_idx1_;
  Int_t * subjet_idx2_;
  Int_t * subjet_idx3_;
  Float_t * jet_fRec_;
  Float_t * jet_Ropt_;
  Float_t * jet_RoptCalc_;
  Float_t * jet_ptForRoptCalc_;
  Float_t * jet_tau1_;
  Float_t * jet_tau2_;
  Float_t * jet_tau3_;

  // CV: make sure that only one RecoJetReaderHTTv2 instance exists for a given branchName,
  //     as ROOT cannot handle multiple TTree::SetBranchAddress calls for the same branch.
  static std::map<std::string, int> numInstances_;
  static std::map<std::string, RecoJetReaderHTTv2 *> instances_;
};

#endif // tthAnalysis_HiggsToTauTau_RecoJetReaderHTTv2_h

