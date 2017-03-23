#ifndef tthAnalysis_HiggsToTauTau_hltPath_h
#define tthAnalysis_HiggsToTauTau_hltPath_h

#include <Rtypes.h> // Int_t
#include <TTree.h> // TTree

#include <string> // std::string
#include <vector> // std::vector<>
#include <assert.h> // assert

/**
 * @brief Auxiliary data structure for handling trigger information
 */
class hltPath
{
 public:
  hltPath(const std::string& branchName)
    : branchName_(branchName),
      value_(-1)
  {}
  ~hltPath() {}
  void setBranchAddress(TTree* tree)
  {
    tree->SetBranchAddress(branchName_.data(), &value_);
  } 
  const std::string& getBranchName() const 
  { 
    return branchName_; 
  }
  Int_t getValue() const 
  {
    assert(value_ == 0 || value_ == 1); 
    return value_; 
  }
 private:
  std::string branchName_;
  Int_t value_;
};

std::vector<hltPath*> create_hltPaths(const std::vector<std::string>& branchNames);
void hltPaths_setBranchAddresses(TTree* tree, const std::vector<hltPath*>& hltPaths);
bool hltPaths_isTriggered(const std::vector<hltPath*>& hltPaths);
void hltPaths_delete(const std::vector<hltPath*>& hltPaths);

#endif // tthAnalysis_HiggsToTauTau_hltPath_h
