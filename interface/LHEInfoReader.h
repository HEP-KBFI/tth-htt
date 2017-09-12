#ifndef tthAnalysis_HiggsToTauTau_LHEInfoReader_h
#define tthAnalysis_HiggsToTauTau_LHEInfoReader_h

#include "tthAnalysis/HiggsToTauTau/interface/ReaderBase.h" // ReaderBase

#include <Rtypes.h> // Int_t, Double_t
#include <TTree.h> // TTree

#include <string>
#include <vector>
#include <map>

enum { kLHE_scale_central, kLHE_scale_xUp, kLHE_scale_xDown, kLHE_scale_yUp, kLHE_scale_yDown };

class LHEInfoReader
  : public ReaderBase
{
 public:
  LHEInfoReader();
  ~LHEInfoReader();

  /**
   * @brief Call tree->SetBranchAddress for all branches containing LHE (scale and PDF) information
   */
  void setBranchAddresses(TTree* tree) override;

  /**
   * @brief Read branches from tree and return values
   * @return Weights for estimating systematic uncertainties related to scale and PDF variations
   */
  void read() const;

  double getWeight_scale_xUp() const;
  double getWeight_scale_xDown() const;
  double getWeight_scale_yUp() const;
  double getWeight_scale_yDown() const;

  int getNumWeights_pdf() const;
  double getWeight_pdf(int idx) const;

 protected:
 /**
   * @brief Initialize names of branches to be read from tree
   */
  void setBranchNames();

  const int max_scale_nWeights_;
  std::string branchName_scale_nWeights_;
  std::string branchName_scale_weights_;
  std::string branchName_scale_ids_;
  const int max_pdf_nWeights_;
  std::string branchName_pdf_nWeights_;
  std::string branchName_pdf_weights_;

  Int_t scale_nWeights_;
  Float_t* scale_weights_;
  Int_t* scale_ids_;
  Int_t pdf_nWeights_;
  Float_t* pdf_weights_;

  mutable double weight_scale_xUp_;
  mutable double weight_scale_xDown_;
  mutable double weight_scale_yUp_;
  mutable double weight_scale_yDown_;

  // CV: make sure that only one LHEInfoReader instance exists for a given branchName,
  //     as ROOT cannot handle multiple TTree::SetBranchAddress calls for the same branch.
  static std::map<std::string, int> numInstances_;
  static std::map<std::string, LHEInfoReader*> instances_;
};

#endif // tthAnalysis_HiggsToTauTau_GenLeptonReader_h

