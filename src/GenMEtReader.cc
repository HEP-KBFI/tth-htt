#include "tthAnalysis/HiggsToTauTau/interface/GenMEtReader.h" // GenMEtReader

#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h" // cmsException()
#include "tthAnalysis/HiggsToTauTau/interface/BranchAddressInitializer.h" // BranchAddressInitializer, TTree, Form()

std::map<std::string, int> GenMEtReader::numInstances_;
std::map<std::string, GenMEtReader *> GenMEtReader::instances_;

GenMEtReader::GenMEtReader(Era era,
                           bool isMC)
  : GenMEtReader(era, isMC, "GenMET")
{}

GenMEtReader::GenMEtReader(Era era,
                           bool isMC,
                           const std::string & branchName_obj)
  : era_(era)
  , isMC_(isMC)
  , branchName_obj_(branchName_obj)
{
  setBranchNames();
}

GenMEtReader::~GenMEtReader()
{
  --numInstances_[branchName_obj_];
  assert(numInstances_[branchName_obj_] >= 0);
  if(numInstances_[branchName_obj_] == 0)
    {
      GenMEtReader * const gInstance = instances_[branchName_obj_];
      assert(gInstance);
      instances_[branchName_obj_] = nullptr;
    }
}

void
GenMEtReader::setBranchNames()
{
  if(numInstances_[branchName_obj_] == 0)
    {
      branchName_pt_ = Form("%s_%s", branchName_obj_.data(), "pt");
      branchName_phi_ = Form("%s_%s", branchName_obj_.data(), "phi");
      instances_[branchName_obj_] = this;
    }
  ++numInstances_[branchName_obj_];
}

void
GenMEtReader::setBranchAddresses(TTree * tree)
{
  if(instances_[branchName_obj_] == this)
    {
      BranchAddressInitializer bai(tree);
      bai.setBranchAddress(met_.pt_,  branchName_pt_);
      bai.setBranchAddress(met_.phi_, branchName_phi_);
    }
}

GenMEt
GenMEtReader::read() const
{
  const GenMEtReader * const gInstance = instances_[branchName_obj_];
  assert(gInstance);
  GenMEt met = met_;
  met.update(); // update p4
  return met;
}
