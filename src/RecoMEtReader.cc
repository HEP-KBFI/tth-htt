#include "tthAnalysis/HiggsToTauTau/interface/RecoMEtReader.h" // RecoMEtReader

#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // getBranchName_MEt()
#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h" // cmsException()
#include "tthAnalysis/HiggsToTauTau/interface/BranchAddressInitializer.h" // BranchAddressInitializer, TTree, Form()
#include "tthAnalysis/HiggsToTauTau/interface/sysUncertOptions.h" // kJetMET_*

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
  , ptPhiOption_(isMC_ ? kJetMET_central : kJetMET_central_nonNominal)
  , read_ptPhi_systematics_(false)
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
RecoMEtReader::setMEt_central_or_shift(int central_or_shift)
{
  if(! isMC_ && central_or_shift != kJetMET_central_nonNominal)
  {
    throw cmsException(this, __func__, __LINE__) << "Nominal MET available only in MC";
  }
  if(! isValidJESsource(era_, central_or_shift))
  {
    throw cmsException(this, __func__, __LINE__) << "Invalid option for the era = " << era_ << ": " << central_or_shift;
  }
  ptPhiOption_ = central_or_shift;
}

void
RecoMEtReader::read_ptPhi_systematics(bool flag)
{
  if(! isMC_ && flag)
  {
    throw cmsException(this, __func__, __LINE__)
      << "Cannot read MET systematics from data"
    ;
  }
  read_ptPhi_systematics_ = flag;
}

void
RecoMEtReader::setBranchNames()
{
  if(numInstances_[branchName_obj_] == 0)
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
    bai.setBranchAddress(met_.systematics_[ptPhiOption_].pt_,  branchName_pt_[ptPhiOption_]);
    bai.setBranchAddress(met_.systematics_[ptPhiOption_].phi_, branchName_phi_[ptPhiOption_]);
    if(read_ptPhi_systematics_)
    {
      for(int met_option = kJetMET_central_nonNominal; met_option <= kJetMET_UnclusteredEnDown; ++met_option)
      {
        if(! isValidJESsource(era_, met_option))
        {
          continue;
        }
        if(met_option == ptPhiOption_)
        {
          continue; // do not bind the same branch twice
        }
        met_.systematics_[met_option] = {0., 0.};
        bai.setBranchAddress(met_.systematics_[met_option].pt_,  branchName_pt_[met_option]);
        bai.setBranchAddress(met_.systematics_[met_option].phi_, branchName_phi_[met_option]);
      }
    }
    bai.setBranchAddress(met_.sumEt_, branchName_sumEt_);
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
  met.default_ = met.systematics_[ptPhiOption_];
  met.update(); // update cov and p4
  return met;
}
