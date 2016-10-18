#include "tthAnalysis/HiggsToTauTau/interface/hltPath.h"

std::vector<hltPath*> create_hltPaths(const std::vector<std::string>& branchNames)
{
  std::vector<hltPath*> hltPaths;
  for ( std::vector<std::string>::const_iterator branchName = branchNames.begin();
	branchName != branchNames.end(); ++branchName ) {
    hltPaths.push_back(new hltPath(*branchName));
  }
  return hltPaths;
}

void hltPaths_setBranchAddresses(TTree* tree, const std::vector<hltPath*>& hltPaths)
{
  for ( std::vector<hltPath*>::const_iterator hltPath_iter = hltPaths.begin();
	hltPath_iter != hltPaths.end(); ++hltPath_iter ) {
    (*hltPath_iter)->setBranchAddress(tree);
  }
}

bool hltPaths_isTriggered(const std::vector<hltPath*>& hltPaths)
{
  bool retVal = false;
  for ( std::vector<hltPath*>::const_iterator hltPath_iter = hltPaths.begin();
	hltPath_iter != hltPaths.end(); ++hltPath_iter ) {
    if ( (*hltPath_iter)->value_ >= 1 ) {
      retVal = true;
      break;
    }
  }
  return retVal;
}

void hltPaths_delete(const std::vector<hltPath*>& hltPaths)
{
  for ( std::vector<hltPath*>::const_iterator hltPath_iter = hltPaths.begin();
	hltPath_iter != hltPaths.end(); ++hltPath_iter ) {
    delete (*hltPath_iter);
  }
}
