#ifndef tthAnalysis_HiggsToTauTau_MEMOutputReader_3l_h
#define tthAnalysis_HiggsToTauTau_MEMOutputReader_3l_h

#include "tthAnalysis/HiggsToTauTau/interface/ReaderBase.h" // ReaderBase
#include "tthAnalysis/HiggsToTauTau/interface/MEMOutput_3l.h" // MEMOutput_3l

// forward declarations
class TTree;

class MEMOutputReader_3l
  : public ReaderBase
{
public:
  MEMOutputReader_3l(const std::string & branchName_num,
                     const std::string & branchName_obj);
  ~MEMOutputReader_3l();

  /**
   * @brief Call tree->SetBranchAddress for all MEMOutput_3l branches
   */
  void
  setBranchAddresses(TTree * tree) override;

  /**
   * @brief Read branches from tree and use information to fill collection of MEMOutput_3l objects
   * @return Collection of MEMOutput_3l objects
   */
  std::vector<MEMOutput_3l>
  read() const;

protected:
 /**
   * @brief Initialize names of branches to be read from tree
   */
  void
  setBranchNames();

  const int max_nMEMOutputs_;
  std::string branchName_num_;
  std::string branchName_obj_;

  std::string branchName_run_;
  std::string branchName_lumi_;
  std::string branchName_evt_;
  std::string branchName_leadLepton_eta_;
  std::string branchName_leadLepton_phi_;
  std::string branchName_subleadLepton_eta_;
  std::string branchName_subleadLepton_phi_;
  std::string branchName_thirdLepton_eta_;
  std::string branchName_thirdLepton_phi_;
  std::string branchName_weight_ttH_;
  std::string branchName_kinfitscore_ttH_;
  std::string branchName_weight_tt_;
  std::string branchName_kinfitscore_tt_;
  std::string branchName_LR_;
  std::string branchName_cpuTime_;
  std::string branchName_realTime_;
  std::string branchName_isValid_;
  std::string branchName_errorFlag_;

  Int_t nMEMOutputs_;
  UInt_t * run_;
  UInt_t * lumi_;
  ULong64_t * evt_;
  Float_t * leadLepton_eta_;
  Float_t * leadLepton_phi_;
  Float_t * subleadLepton_eta_;
  Float_t * subleadLepton_phi_;
  Float_t * thirdLepton_eta_;
  Float_t * thirdLepton_phi_;
  Float_t * weight_ttH_;
  Float_t * kinfitscore_ttH_;
  Float_t * weight_tt_;
  Float_t * kinfitscore_tt_;
  Float_t * LR_;
  Float_t * cpuTime_;
  Float_t * realTime_;
  Int_t * isValid_;
  Int_t * errorFlag_;

  // CV: make sure that only one MEMOutputReader_3l instance exists for a given branchName,
  //     as ROOT cannot handle multiple TTree::SetBranchAddress calls for the same branch.
  static std::map<std::string, int> numInstances_;
  static std::map<std::string, MEMOutputReader_3l *> instances_;
};

#endif // tthAnalysis_HiggsToTauTau_MEMOutputReader_3l_h

