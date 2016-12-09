#include "tthAnalysis/HiggsToTauTau/interface/RecoMEtWriter.h" // RecoMEtWriter

#include "FWCore/Utilities/interface/Exception.h"

#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // kEra_2015, kEra_2016
#include "tthAnalysis/HiggsToTauTau/interface/writerAuxFunctions.h" // setBranchF

#include <TString.h> // Form

RecoMEtWriter::RecoMEtWriter(int era)
  : era_(era)
  , branchName_obj_("met")
{
  setBranchNames();
}

RecoMEtWriter::RecoMEtWriter(int era, const std::string& branchName_obj)
  : era_(era)
  , branchName_obj_(branchName_obj)
{
  setBranchNames();
}

RecoMEtWriter::~RecoMEtWriter()
{}

void RecoMEtWriter::setBranchNames()
{
  branchName_pt_ = Form("%s_%s", branchName_obj_.data(), "pt");
  branchName_phi_ = Form("%s_%s", branchName_obj_.data(), "phi");
  branchName_covXX_ = Form("%s_%s", branchName_obj_.data(), "covXX");
  branchName_covXY_ = Form("%s_%s", branchName_obj_.data(), "covXY");
  branchName_covYY_ = Form("%s_%s", branchName_obj_.data(), "covYY");
}

void RecoMEtWriter::setBranches(TTree* tree)
{
  setBranchF(tree, branchName_pt_, &met_pt_);
  setBranchF(tree, branchName_phi_, &met_phi_);
  setBranchF(tree, branchName_covXX_, &met_covXX_);
  setBranchF(tree, branchName_covXY_, &met_covXY_);
  setBranchF(tree, branchName_covYY_, &met_covYY_);
}

void RecoMEtWriter::write(const RecoMEt& met) 
{
  met_pt_ = met.pt_;
  met_phi_ = met.phi_;
  met_covXX_ = met.covXX_;
  met_covXY_ = met.covXY_;
  met_covYY_ = met.covYY_;
}
