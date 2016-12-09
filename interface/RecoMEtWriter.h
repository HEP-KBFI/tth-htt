#ifndef tthAnalysis_HiggsToTauTau_RecoMEtWriter_h
#define tthAnalysis_HiggsToTauTau_RecoMEtWriter_h

#include "tthAnalysis/HiggsToTauTau/interface/RecoMEt.h" // RecoMEt

#include <Rtypes.h> // Int_t, Double_t
#include <TTree.h> // TTree

#include <string>
#include <vector>
#include <map>

class RecoMEtWriter
{
 public:
  RecoMEtWriter(int era);
  RecoMEtWriter(int era, const std::string& branchName_obj); 
  ~RecoMEtWriter();

  /**
   * @brief Call tree->Branch for all RecoMEt branches
   */
  void setBranches(TTree* tree);

  /**
   * @brief Write RecoMEt object to tree
   */
  void write(const RecoMEt& met);
  
 protected: 
 /**
   * @brief Initialize names of branches to be read from tree
   */
  void setBranchNames();

  int era_;
  std::string branchName_obj_;

  std::string branchName_pt_;
  std::string branchName_phi_;
  std::string branchName_covXX_;
  std::string branchName_covXY_;
  std::string branchName_covYY_;

  Float_t met_pt_;
  Float_t met_phi_;
  Float_t met_covXX_;
  Float_t met_covXY_;
  Float_t met_covYY_;
};

#endif // tthAnalysis_HiggsToTauTau_RecoMEtWriter_h

