#ifndef tthAnalysis_HiggsToTauTau_RecoMEtReader_h
#define tthAnalysis_HiggsToTauTau_RecoMEtReader_h

#include "tthAnalysis/HiggsToTauTau/interface/ReaderBase.h" // ReaderBase
#include "tthAnalysis/HiggsToTauTau/interface/RecoMEt.h" // RecoMEt

#include <map> // std::map<,>

// forward declarations
class TTree;

class RecoMEtReader
  : public ReaderBase
{
 public:
  RecoMEtReader(int era);
  RecoMEtReader(int era,
                const std::string & branchName_obj,
                const std::string & branchName_cov = "");
  ~RecoMEtReader();

  enum {
    kMEt_central,
    kMEt_shifted_JetEnUp, kMEt_shifted_JetEnDown,
    kMEt_shifted_JetResUp, kMEt_shifted_JetResDown,
    kMEt_shifted_UnclusteredEnUp, kMEt_shifted_UnclusteredEnDown
  };
  void setMEt_central_or_shift(int met_option);

  /**
   * @brief Call tree->SetBranchAddress for all RecoMEt branches
   */
  void setBranchAddresses(TTree * tree) override;

  /**
   * @brief Read branches from tree and use information to fill RecoMEt object
   * @return RecoMEt object
   */
  RecoMEt read() const;

 protected:
 /**
   * @brief Initialize names of branches to be read from tree
   */
  void setBranchNames();

  int era_;
  std::string branchName_obj_;
  std::string branchName_cov_;

  std::map<int, std::string> branchName_pt_;
  std::map<int, std::string> branchName_phi_;
  std::string branchName_covXX_;
  std::string branchName_covXY_;
  std::string branchName_covYY_;

  RecoMEt met_;

  int met_option_;

  // CV: make sure that only one RecoMEtReader instance exists for a given branchName,
  //     as ROOT cannot handle multiple TTree::SetBranchAddress calls for the same branch.
  static std::map<std::string, int> numInstances_;
  static std::map<std::string, RecoMEtReader *> instances_;
};

#endif // tthAnalysis_HiggsToTauTau_RecoMEtReader_h
