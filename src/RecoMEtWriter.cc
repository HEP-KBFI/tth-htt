#include "tthAnalysis/HiggsToTauTau/interface/RecoMEtWriter.h" // RecoMEtWriter

#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // getBranchName_MEt()
#include "tthAnalysis/HiggsToTauTau/interface/writerAuxFunctions.h" // setBranch()

#include <FWCore/Utilities/interface/Exception.h>

#include <TTree.h> // TTree
#include <TString.h> // Form()

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
  for(int met_option = RecoMEtReader::kMEt_central; met_option <= RecoMEtReader::kMEt_shifted_UnclusteredEnDown; ++met_option)
  {
    const std::string branchName_obj = getBranchName_MEt(era_, branchName_obj_, met_option);
    branchName_pt_[met_option]  = Form("%s_%s", branchName_obj.data(), "pt");
    branchName_phi_[met_option] = Form("%s_%s", branchName_obj.data(), "phi");
  }
  branchName_covXX_ = Form("%s_%s", branchName_obj_.data(), "covXX");
  branchName_covXY_ = Form("%s_%s", branchName_obj_.data(), "covXY");
  branchName_covYY_ = Form("%s_%s", branchName_obj_.data(), "covYY");
}

void RecoMEtWriter::setBranches(TTree* tree)
{
  for(int met_option = RecoMEtReader::kMEt_central; met_option <= RecoMEtReader::kMEt_shifted_UnclusteredEnDown; ++met_option)
  {
    setBranch(tree, &met_.systematics_[met_option].pt_,  branchName_pt_[met_option]);
    setBranch(tree, &met_.systematics_[met_option].phi_, branchName_phi_[met_option]);
  }
  setBranch(tree, &met_.covXX_, branchName_covXX_);
  setBranch(tree, &met_.covXY_, branchName_covXY_);
  setBranch(tree, &met_.covYY_, branchName_covYY_);
}

void RecoMEtWriter::write(const RecoMEt& met)
{
  met_ = met;
}
