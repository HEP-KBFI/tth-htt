#ifndef tthAnalysis_HiggsToTauTau_RecoSubjetReaderHTTv2_h
#define tthAnalysis_HiggsToTauTau_RecoSubjetReaderHTTv2_h

#include "tthAnalysis/HiggsToTauTau/interface/ReaderBase.h"           // ReaderBase
#include "tthAnalysis/HiggsToTauTau/interface/RecoSubjetHTTv2.h"      // RecoSubjetHTTv2
#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // Era

#include <map> // std::map<,>

// forward declarations
class TTree;

class RecoSubjetReaderHTTv2
  : public ReaderBase
{
public:
  RecoSubjetReaderHTTv2(Era era);
  RecoSubjetReaderHTTv2(Era era,
                        const std::string & branchName_obj);
  ~RecoSubjetReaderHTTv2();

  /**
   * @brief Call tree->SetBranchAddress for all RecoSubjetHTTv2 branches
   */
  void
  setBranchAddresses(TTree * tree) override;

  /**
   * @brief Read branches from tree and use information to fill collection of RecoSubjetHTTv2 objects
   * @return Collection of RecoSubjetHTTv2 objects
   */
  std::vector<RecoSubjetHTTv2>
  read() const;

protected:
 /**
   * @brief Initialize names of branches to be read from tree
   */
  void
  setBranchNames();

  Era era_;
  const unsigned int max_nJets_;
  std::string branchName_num_;
  std::string branchName_obj_;

  std::string branchName_pt_;
  std::string branchName_eta_;
  std::string branchName_phi_;
  std::string branchName_mass_;
  std::string branchName_IDPassed_;
  std::string branchName_btagDeepB_;
  std::string branchName_area_;

  UInt_t nJets_;
  Float_t * jet_pt_;
  Float_t * jet_eta_;
  Float_t * jet_phi_;
  Float_t * jet_mass_;
  Float_t * jet_IDPassed_;
  Float_t * jet_btagDeepB_;
  Float_t * jet_area_;

  // CV: make sure that only one RecoSubjetReaderHTTv2 instance exists for a given branchName,
  //     as ROOT cannot handle multiple TTree::SetBranchAddress calls for the same branch.
  static std::map<std::string, int> numInstances_;
  static std::map<std::string, RecoSubjetReaderHTTv2 *> instances_;
};

#endif // tthAnalysis_HiggsToTauTau_RecoSubjetReaderHTTv2_h
