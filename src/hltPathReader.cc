#include "tthAnalysis/HiggsToTauTau/interface/hltPathReader.h"

#include "tthAnalysis/HiggsToTauTau/interface/hltPath.h" // hltPath

#include "tthAnalysis/HiggsToTauTau/interface/BranchAddressInitializer.h" // BranchAddressInitializer, TTree, Form()

#include <iostream> // std::cout

hltPathReader::hltPathReader(const std::vector<hltPath*> & hltPaths)
  : hltPaths_(hltPaths)
{}

hltPathReader::hltPathReader(const std::vector<std::vector<hltPath *>> & hltPaths)
{
  for(auto it1 = hltPaths.begin(); it1 != hltPaths.end(); ++it1)
  {
    for(auto it2 = it1->begin(); it2 != it1->end(); ++it2)
    {
      hltPaths_.push_back(*it2);
    }
  }
}

std::vector<std::string>
hltPathReader::setBranchAddresses(TTree * tree) 
{
  const std::vector<std::string> available_branches = this->get_available_branches(tree);
  BranchAddressInitializer bai(tree);
  for(hltPath * hltPath_: hltPaths_)
  {
    if(std::find(available_branches.cbegin(), available_branches.cend(), hltPath_->branchName_) != available_branches.cend())
    {
      bai.setBranchAddress(hltPath_->value_, hltPath_->branchName_);
    }
    else
    {
      std::cout << "Branch '" << hltPath_->branchName_ << "' not available, defaulting to false\n";
      hltPath_->value_ = false;
    }
  }
  return bai.getBoundBranchNames();
}

std::vector<std::string>
hltPathReader::get_available_branches(TTree * tree) const
{
  TObjArray * arr = tree->GetListOfBranches();
  TIter it(arr);
  TObject * obj = nullptr;
  std::vector<std::string> available_branches;
  while((obj = it.Next()))
  {
    available_branches.push_back(obj->GetName());
  }
  delete obj;
  return available_branches;
}
