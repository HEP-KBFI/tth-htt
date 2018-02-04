#include "tthAnalysis/HiggsToTauTau/interface/RecoMEtReader.h" // RecoMEtReader

#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // getBranchName_MEt()
#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h" // cmsException()
#include "tthAnalysis/HiggsToTauTau/interface/BranchAddressInitializer.h" // BranchAddressInitializer, TTree, Form()

std::map<std::string, int> RecoMEtReader::numInstances_;
std::map<std::string, RecoMEtReader *> RecoMEtReader::instances_;

RecoMEtReader::RecoMEtReader(int era,
                             bool isMC)
  : RecoMEtReader(era, isMC, "MET")
{}

RecoMEtReader::RecoMEtReader(int era,
                             bool isMC,
                             const std::string & branchName_obj,
                             const std::string & branchName_cov)
  : era_(era)
  , isMC_(isMC)
  , branchName_obj_(branchName_obj)
  , branchName_cov_(branchName_cov.empty() ? branchName_obj_ : branchName_cov)
  , met_option_(kMEt_central)
{
  setBranchNames();
}

RecoMEtReader::~RecoMEtReader()
{
  --numInstances_[branchName_obj_];
  assert(numInstances_[branchName_obj_] >= 0);
  if(numInstances_[branchName_obj_] == 0)
  {
    RecoMEtReader * const gInstance = instances_[branchName_obj_];
    assert(gInstance);
    instances_[branchName_obj_] = nullptr;
  }
}

void
RecoMEtReader::setMEt_central_or_shift(int met_option)
{
  if(! isMC_ && met_option != kMEt_central)
  {
    throw cmsException(this, __func__) << "Invalid met systematics for data: " << met_option;
  }
  met_option_ = met_option;
}

void
RecoMEtReader::setBranchNames()
{
  if(numInstances_[branchName_obj_] == 0)
  {
    const std::string branchName_obj_pt  = Form("%s_pt",  branchName_obj_.data());
    const std::string branchName_obj_phi = Form("%s_phi", branchName_obj_.data());
    const int met_option_limit = isMC_ ? kMEt_shifted_UnclusteredEnDown : kMEt_central;
    for(int met_option = kMEt_central; met_option <= met_option_limit; ++met_option)
    {
      branchName_pt_[met_option]  = getBranchName_MEt(era_, branchName_obj_pt,  met_option);
      branchName_phi_[met_option] = getBranchName_MEt(era_, branchName_obj_phi, met_option);
    }
    branchName_covXX_ = Form("%s_%s", branchName_cov_.data(), "covXX");
    branchName_covXY_ = Form("%s_%s", branchName_cov_.data(), "covXY");
    branchName_covYY_ = Form("%s_%s", branchName_cov_.data(), "covYY");
    instances_[branchName_obj_] = this;
  }
  ++numInstances_[branchName_obj_];
}

void
RecoMEtReader::setBranchAddresses(TTree * tree)
{
  if(instances_[branchName_obj_] == this)
  {
    BranchAddressInitializer bai(tree);
    const int met_option_limit = isMC_ ? kMEt_shifted_UnclusteredEnDown : kMEt_central;
    for(int met_option = kMEt_central; met_option <= met_option_limit; ++met_option)
    {
      met_.systematics_[met_option] = {0., 0.};
      bai.setBranchAddress(met_.systematics_[met_option].pt_, branchName_pt_[met_option]);
      bai.setBranchAddress(met_.systematics_[met_option].phi_, branchName_phi_[met_option]);
    }
    bai.setBranchAddress(met_.covXX_, branchName_covXX_);
    bai.setBranchAddress(met_.covXY_, branchName_covXY_);
    bai.setBranchAddress(met_.covYY_, branchName_covYY_);
  }
}

RecoMEt
RecoMEtReader::read() const
{
  const RecoMEtReader * const gInstance = instances_[branchName_obj_];
  assert(gInstance);
  RecoMEt met = met_;
  met.default_ = met.systematics_[met_option_];
  met.update(); // update cov and p4
  return met;
}
