#include "tthAnalysis/HiggsToTauTau/interface/RecoMEtWriter.h" // RecoMEtWriter

#include "tthAnalysis/HiggsToTauTau/interface/RecoMEtReader.h" // RecoMEtReader::kMEt_*
#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // getBranchName_MEt()
#include "tthAnalysis/HiggsToTauTau/interface/BranchAddressInitializer.h" // BranchAddressInitializer, TTree, Form()

RecoMEtWriter::RecoMEtWriter(int era,
                             bool isMC)
  : RecoMEtWriter(era, isMC, "MET")
{}

RecoMEtWriter::RecoMEtWriter(int era,
                             bool isMC,
                             const std::string & branchName_obj)
  : era_(era)
  , isMC_(isMC)
  , branchName_obj_(branchName_obj)
{
  setBranchNames();
}

RecoMEtWriter::~RecoMEtWriter()
{}

void RecoMEtWriter::setBranchNames()
{
  const std::string branchName_obj_pt  = Form("%s_pt",  branchName_obj_.data());
  const std::string branchName_obj_phi = Form("%s_phi", branchName_obj_.data());
  const int met_option_limit = isMC_ ? RecoMEtReader::kMEt_shifted_UnclusteredEnDown : RecoMEtReader::kMEt_central;
  for(int met_option = RecoMEtReader::kMEt_central; met_option <= met_option_limit; ++met_option)
  {
    branchName_pt_[met_option]  = getBranchName_MEt(era_, branchName_obj_pt,  met_option);
    branchName_phi_[met_option] = getBranchName_MEt(era_, branchName_obj_phi, met_option);
  }
  branchName_covXX_ = Form("%s_%s", branchName_obj_.data(), "covXX");
  branchName_covXY_ = Form("%s_%s", branchName_obj_.data(), "covXY");
  branchName_covYY_ = Form("%s_%s", branchName_obj_.data(), "covYY");
}

void RecoMEtWriter::setBranches(TTree * tree)
{
  BranchAddressInitializer bai(tree);
  const int met_option_limit = isMC_ ? RecoMEtReader::kMEt_shifted_UnclusteredEnDown : RecoMEtReader::kMEt_central;
  for(int met_option = RecoMEtReader::kMEt_central; met_option <= met_option_limit; ++met_option)
  {
    bai.setBranch(met_.systematics_[met_option].pt_,  branchName_pt_[met_option]);
    bai.setBranch(met_.systematics_[met_option].phi_, branchName_phi_[met_option]);
  }
  bai.setBranch(met_.covXX_, branchName_covXX_);
  bai.setBranch(met_.covXY_, branchName_covXY_);
  bai.setBranch(met_.covYY_, branchName_covYY_);
}

void RecoMEtWriter::write(const RecoMEt & met)
{
  met_ = met;
}
