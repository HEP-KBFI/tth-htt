#include "tthAnalysis/HiggsToTauTau/interface/MEtFilterReader.h" // MEtFilterReader

#include "tthAnalysis/HiggsToTauTau/interface/MEtFilter.h" // MEtFilter
#include "tthAnalysis/HiggsToTauTau/interface/BranchAddressInitializer.h" // BranchAddressInitializer, TTree, Form()

#include <cassert> // assert()

int MEtFilterReader::numInstances_ = 0;
MEtFilterReader * MEtFilterReader::instance_ = nullptr;

MEtFilterReader::MEtFilterReader(MEtFilter * metFilter)
  :  metFilter_(metFilter)
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

void
MEtFilterReader::setBranchAddresses(TTree * tree)
{
  if(instance_ == this)
  {
    BranchAddressInitializer bai(tree);
    for(int flag = 0; flag < MEtFilterFlag::LAST; ++flag)
    {
      const MEtFilterFlag flag_enum = static_cast<MEtFilterFlag>(flag);
      bai.setBranchAddress(metFilter_->getFlagRef(flag_enum), getMEtFilterFlagString(flag_enum));
    }
  }
}
