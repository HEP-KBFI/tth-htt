#ifndef tthAnalysis_HiggsToTauTau_RecoSubjetReaderAK12_h
#define tthAnalysis_HiggsToTauTau_RecoSubjetReaderAK12_h

#include "tthAnalysis/HiggsToTauTau/interface/ReaderBase.h" // ReaderBase
#include "tthAnalysis/HiggsToTauTau/interface/RecoSubjetAK12.h" // RecoSubjetAK12

#include <map> // std::map<,>

// forward declarations
class TTree;

class RecoSubjetReaderAK12
  : public ReaderBase
{
public:
  RecoSubjetReaderAK12(int era);
  RecoSubjetReaderAK12(int era,
		       const std::string & branchName_obj);
  ~RecoSubjetReaderAK12();

  /**
   * @brief Call tree->SetBranchAddress for all RecoSubjetHTTv2 branches
   */
  void
  setBranchAddresses(TTree * tree) override;

  /**
   * @brief Read branches from tree and use information to fill collection of RecoSubjetAK12 objects
   * @return Collection of RecoSubjetAK12 objects
   */
  std::vector<RecoSubjetAK12>
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
 
  std::string branchName_pt_;
  std::string branchName_eta_;
  std::string branchName_phi_;
  std::string branchName_mass_;

  UInt_t nJets_;
  Float_t * jet_pt_;
  Float_t * jet_eta_;
  Float_t * jet_phi_;
  Float_t * jet_mass_;

  // CV: make sure that only one RecoSubjetReaderAK12 instance exists for a given branchName,
  //     as ROOT cannot handle multiple TTree::SetBranchAddress calls for the same branch.
  static std::map<std::string, int> numInstances_;
  static std::map<std::string, RecoSubjetReaderAK12 *> instances_;
};

#endif // tthAnalysis_HiggsToTauTau_RecoSubjetReaderAK12_h

