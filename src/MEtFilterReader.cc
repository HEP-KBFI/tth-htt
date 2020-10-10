#include "tthAnalysis/HiggsToTauTau/interface/MEtFilterReader.h" // MEtFilterReader

#include "tthAnalysis/HiggsToTauTau/interface/MEtFilter.h"                // MEtFilter
#include "tthAnalysis/HiggsToTauTau/interface/BranchAddressInitializer.h" // BranchAddressInitializer, TTree, Form()
#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h"     // Era::k*

#include <cassert> // assert()

int MEtFilterReader::numInstances_ = 0;
MEtFilterReader * MEtFilterReader::instance_ = nullptr;

MEtFilterReader::MEtFilterReader(MEtFilter * metFilter,
                                 Era era)
  : metFilter_(metFilter)
  , era_(era)
{
  setBranchNames();
}

MEtFilterReader::~MEtFilterReader()
{
  --numInstances_;
  assert(numInstances_ >= 0);
  if(numInstances_ == 0)
  {
    instance_ = nullptr;
  }
}

void
MEtFilterReader::setBranchNames()
{
  if(numInstances_ == 0)
  {
    for(int flag = 0; flag < MEtFilterFlag::LAST; ++flag)
    {
      branchNames_[flag] = getMEtFilterFlagString(static_cast<MEtFilterFlag>(flag));
    }
    instance_ = this;
  }
  ++numInstances_;
}

std::vector<std::string>
MEtFilterReader::setBranchAddresses(TTree * tree)
{
  if(instance_ == this)
  {
    BranchAddressInitializer bai(tree);
    for(int flag = 0; flag < MEtFilterFlag::LAST; ++flag)
    {
      const MEtFilterFlag flag_enum = static_cast<MEtFilterFlag>(flag);
      std::string metFilterFlagString = getMEtFilterFlagString(flag_enum);
      if(flag == MEtFilterFlag::ecalBadCalibFilterV2)
      {
        if(era_ == Era::k2016)
        {
          // not present in 2016
          continue;
        }
        else
        {
          // this may or may not be an issue
          //metFilterFlagString += "_bool";
        }
      }
      bai.setBranchAddress(metFilter_->getFlagRef(flag_enum), metFilterFlagString);
    }
    return bai.getBoundBranchNames();
  }
  return {};
}
