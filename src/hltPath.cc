#include "tthAnalysis/HiggsToTauTau/interface/hltPath.h"

#include <TTree.h> // TTree

#include <algorithm> // std::any_of()
#include <cassert> // assert()

hltPath::hltPath(const std::string & branchName,
                 double minPt,
                 double maxPt)
  : branchName_(branchName)
  , value_(-1)
  , minPt_(minPt)
  , maxPt_(maxPt)
{}

std::vector<std::string>
hltPath::setBranchAddress(TTree * tree)
{
  tree->SetBranchAddress(branchName_.data(), &value_);
  return { branchName_ };
}

std::vector<std::string>
hltPath::setBranchAddresses(TTree * tree)
{
  return setBranchAddress(tree);
}

const std::string &
hltPath::getBranchName() const
{
  return branchName_;
}

Int_t
hltPath::getValue() const
{
  assert(value_ == 0 || value_ == 1);
  return value_;
}

double
hltPath::getMinPt() const
{
  return minPt_;
}

double
hltPath::getMaxPt() const
{
  return maxPt_;
}

std::vector<hltPath *>
create_hltPaths(const std::vector<std::string> & branchNames)
{
  std::vector<hltPath *> hltPaths;
  for(const std::string & branchName: branchNames)
  {
    hltPaths.push_back(new hltPath(branchName));
  }
  return hltPaths;
}

void
hltPaths_setBranchAddresses(TTree * tree,
                            const std::vector<hltPath *> & hltPaths)
{
  for(hltPath * const & path: hltPaths)
  {
    path->setBranchAddress(tree);
  }
}

bool
hltPaths_isTriggered(const std::vector<hltPath *> & hltPaths)
{
  return std::any_of(
    hltPaths.cbegin(), hltPaths.cend(),
    [](hltPath * const & path) -> bool
    {
      return path->getValue() >= 1;
    }
  );
}

void
hltPaths_delete(const std::vector<hltPath *> & hltPaths)
{
  for(hltPath * path: hltPaths)
  {
    delete path;
    path = nullptr;
  }
}

std::ostream &
operator<<(std::ostream & stream,
           const hltPath & hltPath_iter)
{
  stream << "hltPath = " << hltPath_iter.getBranchName() << ": "
            "value = "   << hltPath_iter.getValue()
         << " (minPt = " << hltPath_iter.getMinPt() << ", "
              "maxPt = " << hltPath_iter.getMaxPt() << ")\n";
  return stream;
}
