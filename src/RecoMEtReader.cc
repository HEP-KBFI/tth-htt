#include "tthAnalysis/HiggsToTauTau/interface/RecoMEtReader.h" // RecoMEtReader

#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // getBranchName_MEt()

#include <FWCore/Utilities/interface/Exception.h>

#include <TString.h> // Form
#include <TTree.h> // TTree

std::map<std::string, int> RecoMEtReader::numInstances_;
std::map<std::string, RecoMEtReader*> RecoMEtReader::instances_;

RecoMEtReader::RecoMEtReader(int era)
  : era_(era)
  , branchName_obj_("MET")
  , met_option_(kMEt_central)
{
  setBranchNames();
}

RecoMEtReader::RecoMEtReader(int era, const std::string& branchName_obj, const std::string& branchName_cov)
  : era_(era)
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
  if ( numInstances_[branchName_obj_] == 0 ) {
    RecoMEtReader* gInstance = instances_[branchName_obj_];
    assert(gInstance);
    instances_[branchName_obj_] = 0;
  }
}

void RecoMEtReader::setBranchNames()
{
  if(numInstances_[branchName_obj_] == 0)
  {
    const std::string branchName_obj_pt  = Form("%s_pt",  branchName_obj_.data());
    const std::string branchName_obj_phi = Form("%s_phi", branchName_obj_.data());
    for(int met_option = kMEt_central; met_option <= kMEt_shifted_UnclusteredEnDown; ++met_option)
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

void RecoMEtReader::setBranchAddresses(TTree* tree)
{
  if(instances_[branchName_obj_] == this)
  {
    for(int met_option = kMEt_central; met_option <= kMEt_shifted_UnclusteredEnDown; ++met_option)
    {
      met_.systematics_[met_option] = {0., 0.};
      tree->SetBranchAddress(branchName_pt_[met_option].data(),  &met_.systematics_[met_option].pt_);
      tree->SetBranchAddress(branchName_phi_[met_option].data(), &met_.systematics_[met_option].phi_);
    }
    if(era_ == kEra_2015)
    { // CV: branch does not exist in VHbb Ntuples v12 produced by Karl for 2015 data
      met_.covXX_ = 400.;       //     assume 20 GeV MET resolution independently in x-direction and in y-direction
      met_.covXY_ =   0.;       //    (cf. Fig. 11 in arXiv:1411.0511)
      met_.covYY_ = 400.;
    }
    else
    {
      tree->SetBranchAddress(branchName_covXX_.data(), &met_.covXX_);
      tree->SetBranchAddress(branchName_covXY_.data(), &met_.covXY_);
      tree->SetBranchAddress(branchName_covYY_.data(), &met_.covYY_);
    }
  }
}

RecoMEt RecoMEtReader::read() const
{
  RecoMEtReader* gInstance = instances_[branchName_obj_];
  assert(gInstance);
  RecoMEt met = met_;
  met.default_ = met.systematics_[met_option_];
  met.update(); // update cov and p4
  return met;
}
