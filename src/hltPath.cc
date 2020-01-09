#include "tthAnalysis/HiggsToTauTau/interface/hltPath.h"

#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h" // cmsException()

#include <TTree.h> // TTree

#include <iostream> // std::ostream
#include <algorithm> // std::any_of()
#include <cassert> // assert()

hltPath::hltPath(const std::string & branchName,
                 double minPt,
                 double maxPt,
                 const std::string & label)
  : branchName_(branchName)
  , value_(false)
  , minPt_(minPt)
  , maxPt_(maxPt)
  , label_(label)
{}

const std::string &
hltPath::getBranchName() const
{
  return branchName_;
}

Int_t
hltPath::getValue() const
{
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

const std::string &
hltPath::getLabel() const
{
  return label_;
}

std::vector<hltPath *>
create_hltPaths(const std::vector<std::string> & branchNames,
                const std::string & label)
{
  std::vector<hltPath *> hltPaths;
  for(const std::string & branchName: branchNames)
  {
    hltPaths.push_back(new hltPath(branchName, -1., -1., label));
  }
  return hltPaths;
}

std::vector<hltPath *>
filter_hltPaths(const std::vector<hltPath *> & hltPaths,
                const std::vector<std::string> & branchNames)
{
  std::vector<hltPath *> filteredPaths;
  std::copy_if(
    hltPaths.cbegin(), hltPaths.cend(), std::back_inserter(filteredPaths),
    [&branchNames](const hltPath * const path) -> bool
    {
      return std::find(branchNames.cbegin(), branchNames.cend(), path->getBranchName()) != branchNames.cend();
    }
  );
  return filteredPaths;
}

bool
hltPaths_isTriggered(const std::vector<hltPath *> & hltPaths,
                     bool verbose)
{
  return std::any_of(
    hltPaths.cbegin(), hltPaths.cend(),
    [verbose](const hltPath * const & path) -> bool
    {
      const bool passes = path->getValue();
      if(verbose)
      {
        std::cout << "  " << path->getLabel() << ": " << *path;
      }
      return passes;
    }
  );
}

bool
hltPaths_isTriggered(const std::vector<hltPath *> & hltPaths,
                     const edm::ParameterSet & runRanges,
                     const EventInfo & eventInfo,
                     bool isMC,
                     bool verbose)
{
  if(isMC)
  {
    return hltPaths_isTriggered(hltPaths, verbose);
  }
  bool isTriggered = false;
  for(const hltPath * const path: hltPaths)
  {
    if(path->getValue())
    {
      if(! runRanges.exists(path->getBranchName()))
      {
        throw cmsException(__func__, __LINE__) << "Unable to find run ranges for HLT path: " << path->getBranchName();
      }
      const std::vector<unsigned int> runs = runRanges.getParameter<std::vector<unsigned int>>(path->getBranchName());
      if(std::find(runs.cbegin(), runs.cend(), eventInfo.run) == runs.cend())
      {
        std::cout
          << "  WARNING: path '" << path->getBranchName() << "' is supposedly triggered but it shouldn't exist for run: "
          << eventInfo.run << " => flipping its trigger bit to FALSE\n"
        ;
      }
      else
      {
        if(verbose)
        {
          std::cout << "  " << path->getLabel() << ": " << *path;
        }
        isTriggered = true;
        break;
      }
    }
  }
  return isTriggered;
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
