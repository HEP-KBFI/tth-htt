#include "tthAnalysis/HiggsToTauTau/interface/RecoMEtWriter.h"

#include "tthAnalysis/HiggsToTauTau/interface/RecoMEtReader.h"            // RecoMEtReader::kJetMET_*
#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h"     // getBranchName_MEt()
#include "tthAnalysis/HiggsToTauTau/interface/BranchAddressInitializer.h" // BranchAddressInitializer, TTree, Form()
#include "tthAnalysis/HiggsToTauTau/interface/sysUncertOptions.h"         // kJetMET_*

RecoMEtWriter::RecoMEtWriter(Era era,
                             bool isMC)
  : RecoMEtWriter(era, isMC, "MET")
{}

RecoMEtWriter::RecoMEtWriter(Era era,
                             bool isMC,
                             const std::string & branchName_obj)
  : era_(era)
  , isMC_(isMC)
  , ptPhiOption_(isMC_ ? kJetMET_central : kJetMET_central_nonNominal)
  , write_ptPhi_systematics_(false)
  , branchName_obj_(branchName_obj)
{
  setBranchNames();
}

RecoMEtWriter::~RecoMEtWriter()
{}

void
RecoMEtWriter::setBranchNames()
{
  for(int met_option = kJetMET_central_nonNominal; met_option <= kJetMET_UnclusteredEnDown; ++met_option)
  {
    if(! isValidJESsource(era_, met_option))
    {
      continue;
    }
    branchName_pt_[met_option]  = getBranchName_jetMET(branchName_obj_, era_, met_option, true);
    branchName_phi_[met_option] = getBranchName_jetMET(branchName_obj_, era_, met_option, false);
  }
  branchName_sumEt_ = Form("%s_%s", branchName_obj_.data(), "sumEt");
  branchName_covXX_ = Form("%s_%s", branchName_obj_.data(), "covXX");
  branchName_covXY_ = Form("%s_%s", branchName_obj_.data(), "covXY");
  branchName_covYY_ = Form("%s_%s", branchName_obj_.data(), "covYY");
}

void
RecoMEtWriter::setPtPhi_central_or_shift(int central_or_shift)
{
  if(! isMC_ && central_or_shift != kJetMET_central_nonNominal)
  {
    throw cmsException(this, __func__, __LINE__) << "Data has only non-nominal pt and phi";
  }
  if(! isValidJESsource(era_, central_or_shift))
  {
    throw cmsException(this, __func__, __LINE__) << "Invalid option for the era = " << static_cast<int>(era_) << ": " << central_or_shift;
  }
  if(central_or_shift <= kJetMET_UnclusteredEnDown)
  {
    ptPhiOption_ = central_or_shift;
  }
  else
  {
    std::cout
        << get_human_line(this, __func__, __LINE__)
        << "Not setting the systematics option to " << central_or_shift
        << " but keeping it at " << ptPhiOption_
    ;
  }
}

void
RecoMEtWriter::write_ptPhi_systematics(bool flag)
{
  if(! isMC_ && flag)
  {
    throw cmsException(this, __func__, __LINE__)
      << "Cannot write MET systematics in data"
    ;
  }
  write_ptPhi_systematics_ = flag;
}

void
RecoMEtWriter::setBranches(TTree * tree)
{
  BranchAddressInitializer bai(tree);

  bai.setBranch(met_.systematics_[ptPhiOption_].pt_,  branchName_pt_[ptPhiOption_]);
  bai.setBranch(met_.systematics_[ptPhiOption_].phi_, branchName_phi_[ptPhiOption_]);
  if(write_ptPhi_systematics_)
  {
    for(int met_option = kJetMET_central_nonNominal; met_option <= kJetMET_UnclusteredEnDown; ++met_option)
    {
      if(! isValidJESsource(era_, met_option))
      {
        continue;
      }
      if(met_option == ptPhiOption_)
      {
        continue; // do not overwrite the choice of branch
      }
      bai.setBranch(met_.systematics_[met_option].pt_, branchName_pt_[met_option]);
      bai.setBranch(met_.systematics_[met_option].phi_, branchName_phi_[met_option]);
    }
  }
  bai.setBranch(met_.sumEt_, branchName_sumEt_);
  bai.setBranch(met_.covXX_, branchName_covXX_);
  bai.setBranch(met_.covXY_, branchName_covXY_);
  bai.setBranch(met_.covYY_, branchName_covYY_);
}

void RecoMEtWriter::write(const RecoMEt & met)
{
  met_ = met;
}
