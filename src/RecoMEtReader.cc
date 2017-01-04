#include "tthAnalysis/HiggsToTauTau/interface/RecoMEtReader.h" // RecoMEtReader

#include "FWCore/Utilities/interface/Exception.h"

#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // kEra_2015, kEra_2016

#include <TString.h> // Form

std::map<std::string, int> RecoMEtReader::numInstances_;
std::map<std::string, RecoMEtReader*> RecoMEtReader::instances_;

RecoMEtReader::RecoMEtReader(int era)
  : era_(era)
  , branchName_obj_("met")
{
  setBranchNames();
}

RecoMEtReader::RecoMEtReader(int era, const std::string& branchName_obj)
  : era_(era)
  , branchName_obj_(branchName_obj)
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
  if ( numInstances_[branchName_obj_] == 0 ) {
    branchName_pt_ = Form("%s_%s", branchName_obj_.data(), "pt");
    branchName_phi_ = Form("%s_%s", branchName_obj_.data(), "phi");
    branchName_covXX_ = Form("%s_%s", branchName_obj_.data(), "covXX");
    branchName_covXY_ = Form("%s_%s", branchName_obj_.data(), "covXY");
    branchName_covYY_ = Form("%s_%s", branchName_obj_.data(), "covYY");
    instances_[branchName_obj_] = this;
  }
  ++numInstances_[branchName_obj_];
}

void RecoMEtReader::setBranchAddresses(TTree* tree)
{
  if ( instances_[branchName_obj_] == this ) {
    tree->SetBranchAddress(branchName_pt_.data(), &met_pt_); 
    tree->SetBranchAddress(branchName_phi_.data(), &met_phi_); 
    if ( era_ == kEra_2015 ) { // CV: branch does not exist in VHbb Ntuples v12 produced by Karl for 2015 data
      met_covXX_ = 400.;       //     assume 20 GeV MET resolution independently in x-direction and in y-direction
      met_covXY_ =   0.;       //    (cf. Fig. 11 in arXiv:1411.0511)
      met_covYY_ = 400.;
    } else {
      tree->SetBranchAddress(branchName_covXX_.data(), &met_covXX_); 
      tree->SetBranchAddress(branchName_covXY_.data(), &met_covXY_); 
      tree->SetBranchAddress(branchName_covYY_.data(), &met_covYY_); 
    }
  }
}

RecoMEt RecoMEtReader::read() const
{
  RecoMEtReader* gInstance = instances_[branchName_obj_];
  assert(gInstance);
  RecoMEt met(
    gInstance->met_pt_,
    gInstance->met_phi_,
    gInstance->met_covXX_,
    gInstance->met_covXY_,
    gInstance->met_covYY_);
  return met;
}
