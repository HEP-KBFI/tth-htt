#ifndef tthAnalysis_HiggsToTauTau_MEMOutputWriter_2lss_1tau_h
#define tthAnalysis_HiggsToTauTau_MEMOutputWriter_2lss_1tau_h

#include "tthAnalysis/HiggsToTauTau/interface/MEMOutput_2lss_1tau.h" // MEMOutput_2lss_1tau

#include <vector> // std::vector<>

// forward declaration
class TTree;

class MEMOutputWriter_2lss_1tau
{
public:
  MEMOutputWriter_2lss_1tau(const std::string & branchName_num,
                            const std::string & branchName_obj);
  ~MEMOutputWriter_2lss_1tau();

  /**
   * @brief Call tree->Branch for all MEMOutputWriter_2lss_1tau branches
   */
  void setBranches(TTree * tree);

  /**
   * @brief Write collection of MEMOutputWriter_2lss_1tau objects to tree
   */
  void write(const std::vector<MEMOutput_2lss_1tau> & memOutputs);
  
protected:
 /**
   * @brief Initialize names of branches to be read from tree
   */
  void setBranchNames();

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
  std::string branchName_hadTau_eta_;
  std::string branchName_hadTau_phi_;
  std::string branchName_type_;
  std::string branchName_weight_ttH_;
  std::string branchName_weight_ttH_error_;
  std::string branchName_weight_ttZ_;
  std::string branchName_weight_ttZ_error_;
  std::string branchName_weight_ttZ_Zll_;
  std::string branchName_weight_ttZ_Zll_error_;
  std::string branchName_weight_tt_;
  std::string branchName_weight_tt_error_;
  std::string branchName_LR_;
  std::string branchName_LR_up_;
  std::string branchName_LR_down_;
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
  Float_t * hadTau_eta_;
  Float_t * hadTau_phi_;
  Int_t * type_;
  Float_t * weight_ttH_;
  Float_t * weight_ttH_error_;
  Float_t * weight_ttZ_;
  Float_t * weight_ttZ_error_;
  Float_t * weight_ttZ_Zll_;
  Float_t * weight_ttZ_Zll_error_;
  Float_t * weight_tt_;
  Float_t * weight_tt_error_;
  Float_t * LR_;
  Float_t * LR_up_;
  Float_t * LR_down_;
  Float_t * cpuTime_;
  Float_t * realTime_;
  Int_t * isValid_;
  Int_t * errorFlag_;
};

#endif // tthAnalysis_HiggsToTauTau_MEMOutputWriter_2lss_1tau_h

