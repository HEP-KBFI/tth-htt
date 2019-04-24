#include "tthAnalysis/HiggsToTauTau/interface/L1PreFiringWeightReader.h" // L1PreFiringWeightReader

#include "tthAnalysis/HiggsToTauTau/interface/BranchAddressInitializer.h" // BranchAddressInitializer, TTree, Form()
#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // kEra_2018
#include "tthAnalysis/HiggsToTauTau/interface/sysUncertOptions.h" // L1PreFiringWeightSys

#include <cassert> // assert()

std::map<std::string, int> L1PreFiringWeightReader::numInstances_;
std::map<std::string, L1PreFiringWeightReader*> L1PreFiringWeightReader::instances_;

L1PreFiringWeightReader::L1PreFiringWeightReader(int era,
                                                 L1PreFiringWeightSys option)
  : era_(era)
  , option_(option)
  , branchName_l1PreFiringWeight_("L1PreFiringWeight")
  , l1PreFiringWeight_(1.)
{
  setBranchNames();
}

L1PreFiringWeightReader::~L1PreFiringWeightReader()
{
  --numInstances_[branchName_l1PreFiringWeight_];
  assert(numInstances_[branchName_l1PreFiringWeight_] >= 0);

  if(numInstances_[branchName_l1PreFiringWeight_] == 0)
  {
    L1PreFiringWeightReader * const gInstance = instances_[branchName_l1PreFiringWeight_];
    assert(gInstance);
    instances_[branchName_l1PreFiringWeight_] = nullptr;
  }
}

void
L1PreFiringWeightReader::setBranchNames()
{
  if(numInstances_[branchName_l1PreFiringWeight_] == 0)
  {
    instances_[branchName_l1PreFiringWeight_] = this;
  }
  ++numInstances_[branchName_l1PreFiringWeight_];
}

void
L1PreFiringWeightReader::setBranchAddresses(TTree * tree)
{
  if(era_ != kEra_2018)
  {
    const std::string branchName = [this]() -> std::string
    {
      switch(option_)
      {
        case L1PreFiringWeightSys::nominal: return Form("%s_Nom", branchName_l1PreFiringWeight_.data());
        case L1PreFiringWeightSys::up:      return Form("%s_Up",  branchName_l1PreFiringWeight_.data());
        case L1PreFiringWeightSys::down:    return Form("%s_Dn",  branchName_l1PreFiringWeight_.data());
      }
      assert(0);
    }();

    BranchAddressInitializer bai(tree);
    bai.setBranchAddress(l1PreFiringWeight_, branchName, 1.);
  }
}

double
L1PreFiringWeightReader::getWeight() const
{
  return l1PreFiringWeight_;
}
