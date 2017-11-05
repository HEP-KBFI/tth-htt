#ifndef tthAnalysis_HiggsToTauTau_MEMOutputReader_2lss_1tau_h
#define tthAnalysis_HiggsToTauTau_MEMOutputReader_2lss_1tau_h

#include "tthAnalysis/HiggsToTauTau/interface/MEMOutput_2lss_1tau.h" // MEMOutput_2lss_1tau
#include "tthAnalysis/HiggsToTauTau/interface/KeyTypes.h" // RUN_TYPE, LUMI_TYPE, EVT_TYPE
#include "tthAnalysis/HiggsToTauTau/interface/ReaderBase.h" // ReaderBase

#include <Rtypes.h> // Int_t, Double_t
#include <TTree.h> // TTree

#include <string>
#include <vector>
#include <map>

class MEMOutputReader_2lss_1tau
  : public ReaderBase
{
 public:
  MEMOutputReader_2lss_1tau(const std::string& branchName_num,
                            const std::string& branchName_obj);
  ~MEMOutputReader_2lss_1tau();

  /**
   * @brief Call tree->SetBranchAddress for all GenParticle branches
   */
  void setBranchAddresses(TTree* tree) override;

  /**
   * @brief Read branches from tree and use information to fill collection of MEMOutput_2lss_1tau objects
   * @return Collection of MEMOutput_2lss_1tau objects
   */
  std::vector<MEMOutput_2lss_1tau> read() const;

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
  std::string branchName_weight_ttZ_;
  std::string branchName_weight_ttZ_Zll_;
  std::string branchName_weight_tt_;
  std::string branchName_LR_;
  std::string branchName_cpuTime_;
  std::string branchName_realTime_;
  std::string branchName_isValid_;
  std::string branchName_errorFlag_;

  Int_t nMEMOutputs_;
  RUN_TYPE* run_;
  LUMI_TYPE* lumi_;
  EVT_TYPE* evt_;
  Float_t* leadLepton_eta_;
  Float_t* leadLepton_phi_;
  Float_t* subleadLepton_eta_;
  Float_t* subleadLepton_phi_;
  Float_t* hadTau_eta_;
  Float_t* hadTau_phi_;
  Int_t* type_;
  Float_t* weight_ttH_;
  Float_t* weight_ttZ_;
  Float_t* weight_ttZ_Zll_;
  Float_t* weight_tt_;
  Float_t* LR_;
  Float_t* cpuTime_;
  Float_t* realTime_;
  Int_t* isValid_;
  Int_t* errorFlag_;

  // CV: make sure that only one MEMOutputReader_2lss_1tau instance exists for a given branchName,
  //     as ROOT cannot handle multiple TTree::SetBranchAddress calls for the same branch.
  static std::map<std::string, int> numInstances_;
  static std::map<std::string, MEMOutputReader_2lss_1tau*> instances_;
};

#endif // tthAnalysis_HiggsToTauTau_GenParticleReader_h

