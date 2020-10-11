#ifndef tthAnalysis_HiggsToTauTau_TrigObjReader_h
#define tthAnalysis_HiggsToTauTau_TrigObjReader_h

#include "tthAnalysis/HiggsToTauTau/interface/ReaderBase.h" // ReaderBase
#include "tthAnalysis/HiggsToTauTau/interface/TrigObj.h" // TrigObj

#include <map> // std::map<,>

class TTree;

class TrigObjReader
  : public ReaderBase
{
public:
  TrigObjReader();
  TrigObjReader(const std::string & branchName_obj);
  ~TrigObjReader();

  /**
   * @brief Call tree->SetBranchAddress for all TrigObj branches
   */
  std::vector<std::string>
  setBranchAddresses(TTree * tree) override;

  /**
   * @brief Read branches from tree and use information to fill collection of TrigObj objects
   * @return Collection of TrigObj objects
   */
  std::vector<TrigObj>
  read() const;

protected:
 /**
   * @brief Initialize names of branches to be read from tree
   */
  void
  setBranchNames();

  const unsigned int max_nTrigObjs_;
  std::string branchName_num_;
  std::string branchName_obj_;

  std::string branchName_pt_;     
  std::string branchName_eta_;  
  std::string branchName_phi_;
  std::string branchName_filterBits_; 
  std::string branchName_id_; 
  std::string branchName_l1pt_; 
  std::string branchName_l1pt_2_;  
  std::string branchName_l1iso_;   

  UInt_t nTrigObjs_;
  Float_t * trigObj_pt_;     
  Float_t * trigObj_eta_;  
  Float_t * trigObj_phi_;
  Int_t   * trigObj_filterBits_; 
  Int_t   * trigObj_id_; 
  Float_t * trigObj_l1pt_; 
  Float_t * trigObj_l1pt_2_;  
  Int_t   * trigObj_l1iso_;  

  // CV: make sure that only one TrigObjReader instance exists for a given branchName,
  //     as ROOT cannot handle multiple TTree::SetBranchAddress calls for the same branch.
  static std::map<std::string, int> numInstances_;
  static std::map<std::string, TrigObjReader *> instances_;
};

#endif // tthAnalysis_HiggsToTauTau_TrigObjReader_h
