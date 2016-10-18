#ifndef tthAnalysis_HiggsToTauTau_hltPath_h
#define tthAnalysis_HiggsToTauTau_hltPath_h

#include <Rtypes.h> // Int_t
#include <TTree.h> // TTree

#include <string> // std::string
#include <vector> // std::vector<>

/**
 * @brief Auxiliary data structure for handling trigger information
 */
struct hltPath
{
  hltPath(const std::string& branchName)
    : branchName_(branchName)
  {}
  ~hltPath() {}
  void setBranchAddress(TTree* tree)
  {
    tree->SetBranchAddress(branchName_.data(), &value_);
  } 
  std::string branchName_;
  Int_t value_;
};

std::vector<hltPath*> create_hltPaths(const std::vector<std::string>& branchNames);
void hltPaths_setBranchAddresses(TTree* tree, const std::vector<hltPath*>& hltPaths);
bool hltPaths_isTriggered(const std::vector<hltPath*>& hltPaths);
void hltPaths_delete(const std::vector<hltPath*>& hltPaths);

#endif // tthAnalysis_HiggsToTauTau_hltPath_h
