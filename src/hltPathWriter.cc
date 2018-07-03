#include "tthAnalysis/HiggsToTauTau/interface/hltPathWriter.h"

#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h" // cmsException()
#include "tthAnalysis/HiggsToTauTau/interface/BranchAddressInitializer.h" // BranchAddressInitializer, TTree, Form()

hltPathWriter::hltPathWriter(const std::vector<std::string> & hltPath_branchNames)
{
  for(const std::string & branchName: hltPath_branchNames)
  {
    branchEntryType branch;
    branch.branchName_ = branchName;
    branch.value_ = false;
    branch.value_isInitialized_ = false;
    branches_[branchName] = branch;
  }
}

void
hltPathWriter::setBranches(TTree * tree)
{
  BranchAddressInitializer bai(tree);
  for(auto & branch: branches_)
  {
    bai.setBranch(branch.second.value_, branch.second.branchName_);
  }
}

void
hltPathWriter::write(const std::vector<hltPath *> & hltPaths)
{
  for(auto & branch: branches_)
  {
    branch.second.value_isInitialized_ = false;
  }

  for(const hltPath * const hltPath_: hltPaths)
  {
    std::map<std::string, branchEntryType>::iterator branch = branches_.find(hltPath_->getBranchName());
    if(branch != branches_.end())
    {
      branch->second.value_ = hltPath_->getValue();
      branch->second.value_isInitialized_ = true;
    }
    else
    {
      throw cmsException(__func__, __LINE__)
        << " HLT path = '" << hltPath_->getBranchName() << "' has not been declared";
    }
  }

  for(const auto & branch: branches_)
  {
    if(! branch.second.value_isInitialized_)
    {
      throw cmsException(__func__, __LINE__)
        << " HLT path = '" << branch.second.branchName_ << "' has not been initialized";
    }
  }
}
