#ifndef tthAnalysis_HiggsToTauTau_RecoMEtReader_h
#define tthAnalysis_HiggsToTauTau_RecoMEtReader_h

#include "tthAnalysis/HiggsToTauTau/interface/ReaderBase.h"           // ReaderBase
#include "tthAnalysis/HiggsToTauTau/interface/RecoMEt.h"              // RecoMEt
#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // Era

#include <map> // std::map<,>

// forward declarations
class TTree;

class RecoMEtReader
  : public ReaderBase
{
public:
  RecoMEtReader(Era era,
                bool isMC);
  RecoMEtReader(Era era,
                bool isMC,
                const std::string & branchName_obj,
                const std::string & branchName_cov = "");
  ~RecoMEtReader();

  void
  setMEt_central_or_shift(int met_option);

  void
  read_ptPhi_systematics(bool flag);

  /**
   * @brief Call tree->SetBranchAddress for all RecoMEt branches
   */
  std::vector<std::string>
  setBranchAddresses(TTree * tree) override;

  /**
   * @brief Read branches from tree and use information to fill RecoMEt object
   * @return RecoMEt object
   */
  RecoMEt
  read() const;

protected:
 /**
   * @brief Initialize names of branches to be read from tree
   */
  void
  setBranchNames();

  Era era_;
  bool isMC_;
  std::string branchName_obj_;
  std::string branchName_cov_;

  std::map<int, std::string> branchName_pt_;
  std::map<int, std::string> branchName_phi_;
  std::string branchName_sumEt_;
  std::string branchName_covXX_;
  std::string branchName_covXY_;
  std::string branchName_covYY_;

  RecoMEt met_;

  int ptPhiOption_;
  bool read_ptPhi_systematics_;

  // CV: make sure that only one RecoMEtReader instance exists for a given branchName,
  //     as ROOT cannot handle multiple TTree::SetBranchAddress calls for the same branch.
  static std::map<std::string, int> numInstances_;
  static std::map<std::string, RecoMEtReader *> instances_;
};

#endif // tthAnalysis_HiggsToTauTau_RecoMEtReader_h
