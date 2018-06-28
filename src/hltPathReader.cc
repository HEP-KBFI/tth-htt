#include "tthAnalysis/HiggsToTauTau/interface/hltPathReader.h"

#include <TTree.h> // TTree

#include <iostream> // std::cout
#include <algorithm> // std::find

hltPathReader::hltPathReader(const std::vector<hltPath*> & hltPaths)
  : hltPaths_(hltPaths)
{}

hltPathReader::hltPathReader(const std::vector<std::vector<hltPath*>> & hltPaths)
{
  for ( std::vector<std::vector<hltPath*>>::const_iterator it1 = hltPaths.begin();
	it1 != hltPaths.end(); ++it1 ) {
    for ( std::vector<hltPath*>::const_iterator it2 = it1->begin();
	  it2 != it1->end(); ++it2 ) {
      hltPaths_.push_back(*it2);
    }
  }
}

void
hltPathReader::setBranchAddresses(TTree * tree) 
{
  const std::vector<std::string> available_branches = this->get_available_branches(tree);
  for ( std::vector<hltPath*>::iterator hltPath = hltPaths_.begin();
	hltPath != hltPaths_.end(); ++hltPath ) {
    if ( std::find(available_branches.cbegin(), available_branches.cend(), (*hltPath)->branchName_) != available_branches.cend() ) {
      tree->SetBranchAddress((*hltPath)->branchName_.data(), &(*hltPath)->value_);
    } else {
      std::cout << "Branch '" << (*hltPath)->branchName_ << "' not available, defaulting to false\n";
      (*hltPath)->value_ = false;
    }
  }
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
