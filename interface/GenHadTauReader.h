#ifndef tthAnalysis_HiggsToTauTau_GenHadTauReader_h
#define tthAnalysis_HiggsToTauTau_GenHadTauReader_h

#include "tthAnalysis/HiggsToTauTau/interface/GenHadTau.h" // GenHadTau
#include "tthAnalysis/HiggsToTauTau/interface/ReaderBase.h" // ReaderBase

#include <map> // std::map<,>

// forward declarations
class TTree;

class GenHadTauReader
  : public ReaderBase
{
public:
  GenHadTauReader(unsigned int max_nHadTaus = 36);
  GenHadTauReader(const std::string & branchName_obj,
                  unsigned int max_nHadTaus = 36);
  ~GenHadTauReader();

  /**
   * @brief Call tree->SetBranchAddress for all GenHadTau branches
   */
  void
  setBranchAddresses(TTree * tree) override;

  /**
   * @brief Read branches from tree and use information to fill collection of GenHadTau objects
   * @return Collection of GenHadTau objects
   */
  std::vector<GenHadTau>
  read() const;

protected:
 /**
   * @brief Initialize names of branches to be read from tree
   */
  void
  setBranchNames();

  const unsigned int max_nHadTaus_;
  std::string branchName_num_;
  std::string branchName_obj_;

  std::string branchName_pt_;
  std::string branchName_eta_;
  std::string branchName_phi_;
  std::string branchName_mass_;
  std::string branchName_charge_;

  UInt_t nHadTaus_;
  Float_t * hadTau_pt_;
  Float_t * hadTau_eta_;
  Float_t * hadTau_phi_;
  Float_t * hadTau_mass_;
  Int_t * hadTau_charge_;

  // CV: make sure that only one GenHadTauReader instance exists for a given branchName,
  //     as ROOT cannot handle multiple TTree::SetBranchAddress calls for the same branch.
  static std::map<std::string, int> numInstances_;
  static std::map<std::string, GenHadTauReader*> instances_;
};

#endif // tthAnalysis_HiggsToTauTau_GenHadTauReader_h

