#ifndef tthAnalysis_HiggsToTauTau_GenJetReader_h
#define tthAnalysis_HiggsToTauTau_GenJetReader_h

#include "tthAnalysis/HiggsToTauTau/interface/ReaderBase.h" // ReaderBase
#include "tthAnalysis/HiggsToTauTau/interface/GenJet.h" // GenJet

#include <map> // std::map<,>

// forward declarations
class TTree;

class GenJetReader
  : public ReaderBase
{
public:
  explicit GenJetReader(const std::string & branchName_obj,
                        unsigned int max_nJets = 36);
  ~GenJetReader();

  /**
   * @brief Call tree->SetBranchAddress for all GenJet branches
   */
  void
  setBranchAddresses(TTree * tree) override;

  /**
   * @brief Read branches from tree and use information to fill collection of GenJet objects
   * @return Collection of GenJet objects
   */
  std::vector<GenJet>
  read() const;

  void
  read_partonFlavour();

protected:
 /**
   * @brief Initialize names of branches to be read from tree
   */
  void
  setBranchNames();

  bool read_partonFlavour_;

  const unsigned int max_nJets_;
  std::string branchName_num_;
  std::string branchName_obj_;

  std::string branchName_pt_;
  std::string branchName_eta_;
  std::string branchName_phi_;
  std::string branchName_mass_;
  std::string branchName_pdgId_;

  UInt_t nJets_;
  Float_t * jet_pt_;
  Float_t * jet_eta_;
  Float_t * jet_phi_;
  Float_t * jet_mass_;
  Int_t * jet_pdgId_;

  // CV: make sure that only one RecoJetReader instance exists for a given branchName,
  //     as ROOT cannot handle multiple TTree::SetBranchAddress calls for the same branch.
  static std::map<std::string, int> numInstances_;
  static std::map<std::string, GenJetReader *> instances_;
};

#endif // tthAnalysis_HiggsToTauTau_GenJetReader_h

