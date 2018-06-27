#include "tthAnalysis/HiggsToTauTau/interface/hltPathWriter.h"

#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h" // cmsException()
#include "tthAnalysis/HiggsToTauTau/interface/BranchAddressInitializer.h" // BranchAddressInitializer, TTree, Form()

hltPathWriter::hltPathWriter(const std::vector<std::string>& hltPath_branchNames)
{
  for ( std::vector<std::string>::const_iterator branchName = hltPath_branchNames.begin();
	branchName != hltPath_branchNames.end(); ++branchName ) {
    branchEntryType branch;
    branch.branchName_ = *branchName;
    branch.value_ = 0;
    branch.value_isInitialized_ = false;
    branches_[*branchName] = branch;
  }
}

void
hltPathWriter::setBranches(TTree * tree)
{
  BranchAddressInitializer bai(tree);

  for ( std::map<std::string, branchEntryType>::iterator branch = branches_.begin(); 
	branch != branches_.end(); ++branch ) {
    bai.setBranch(branch->second.value_, branch->second.branchName_);
  }
}

void
hltPathWriter::write(const std::vector<hltPath*> & hltPaths)
{
  for ( std::map<std::string, branchEntryType>::iterator branch = branches_.begin(); 
	branch != branches_.end(); ++branch ) {
    branch->second.value_isInitialized_ = false;
  }
  for ( std::vector<hltPath*>::const_iterator hltPath = hltPaths.begin();
	hltPath != hltPaths.end(); ++hltPath ) {
    std::map<std::string, branchEntryType>::iterator branch = branches_.find((*hltPath)->getBranchName());
    if ( branch != branches_.end() ) {
      branch->second.value_ = (*hltPath)->getValue();
      branch->second.value_isInitialized_ = true;
    } else {
      throw cmsException(__func__, __LINE__)
	<< " HLT path = '" << (*hltPath)->getBranchName() << "' has not been declared !!\n";
    }
  }
  for ( std::map<std::string, branchEntryType>::iterator branch = branches_.begin(); 
	branch != branches_.end(); ++branch ) {
    if ( !branch->second.value_isInitialized_ ) {
      throw cmsException(__func__, __LINE__)
	<< " HLT path = '" << branch->second.branchName_ << "' has not been initialized !!\n";
    }
  }
}
