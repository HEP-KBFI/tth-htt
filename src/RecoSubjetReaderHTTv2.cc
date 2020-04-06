#include "tthAnalysis/HiggsToTauTau/interface/RecoSubjetReaderHTTv2.h"

#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h"             // cmsException()
#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h"     // kBtag_*
#include "tthAnalysis/HiggsToTauTau/interface/BranchAddressInitializer.h" // BranchAddressInitializer, TTree, Form()

std::map<std::string, int> RecoSubjetReaderHTTv2::numInstances_;
std::map<std::string, RecoSubjetReaderHTTv2 *> RecoSubjetReaderHTTv2::instances_;

RecoSubjetReaderHTTv2::RecoSubjetReaderHTTv2(Era era)
  : RecoSubjetReaderHTTv2(era, "HTTV2Subjets")
{}

RecoSubjetReaderHTTv2::RecoSubjetReaderHTTv2(Era era,
                                             const std::string & branchName_obj)
  : era_(era)
  , max_nJets_(128)
  , branchName_num_(Form("n%s", branchName_obj.data()))
  , branchName_obj_(branchName_obj)
  , jet_pt_(nullptr)
  , jet_eta_(nullptr)
  , jet_phi_(nullptr)
  , jet_mass_(nullptr)
  , jet_IDPassed_(nullptr)
  , jet_btagDeepB_(nullptr)
  , jet_area_(nullptr)
{
  setBranchNames();
}

RecoSubjetReaderHTTv2::~RecoSubjetReaderHTTv2()
{
  --numInstances_[branchName_obj_];
  assert(numInstances_[branchName_obj_] >= 0);
  if(numInstances_[branchName_obj_] == 0)
  {
    RecoSubjetReaderHTTv2 * const gInstance = instances_[branchName_obj_];
    assert(gInstance);
    delete[] gInstance->jet_pt_;
    delete[] gInstance->jet_eta_;
    delete[] gInstance->jet_phi_;
    delete[] gInstance->jet_mass_;
    delete[] gInstance->jet_IDPassed_;
    delete[] gInstance->jet_btagDeepB_;
    delete[] gInstance->jet_area_;
    instances_[branchName_obj_] = nullptr;
  }
}

void
RecoSubjetReaderHTTv2::setBranchNames()
{
  if(numInstances_[branchName_obj_] == 0)
  {
    branchName_pt_ = Form("%s_%s", branchName_obj_.data(), "pt");
    branchName_eta_ = Form("%s_%s", branchName_obj_.data(), "eta");
    branchName_phi_ = Form("%s_%s", branchName_obj_.data(), "phi");
    branchName_mass_ = Form("%s_%s", branchName_obj_.data(), "mass");
    branchName_IDPassed_ = Form("%s_%s", branchName_obj_.data(), "IDPassed");
    branchName_btagDeepB_ = Form("%s_%s", branchName_obj_.data(), "btag");
    branchName_area_ = Form("%s_%s", branchName_obj_.data(), "area");
    instances_[branchName_obj_] = this;
  }
  else
  {
    if(branchName_num_ != instances_[branchName_obj_]->branchName_num_)
    {
      throw cmsException(this)
        << "Association between configuration parameters 'branchName_num' and 'branchName_obj' must be unique:"
        << " present association 'branchName_num' = " << branchName_num_ << " with 'branchName_obj' = " << branchName_obj_
        << " does not match previous association 'branchName_num' = " << instances_[branchName_obj_]->branchName_num_
        << " with 'branchName_obj' = " << instances_[branchName_obj_]->branchName_obj_ << " !!\n";
    }
  }
  ++numInstances_[branchName_obj_];
}

void
RecoSubjetReaderHTTv2::setBranchAddresses(TTree * tree)
{
  if(instances_[branchName_obj_] == this)
  {
    BranchAddressInitializer bai(tree, max_nJets_);
    bai.setBranchAddress(nJets_, branchName_num_);
    bai.setBranchAddress(jet_pt_, branchName_pt_);
    bai.setBranchAddress(jet_eta_, branchName_eta_);
    bai.setBranchAddress(jet_phi_, branchName_phi_);
    bai.setBranchAddress(jet_mass_, branchName_mass_);
    bai.setBranchAddress(jet_IDPassed_, branchName_IDPassed_);
    bai.setBranchAddress(jet_btagDeepB_, branchName_btagDeepB_);
    bai.setBranchAddress(jet_area_, branchName_area_);
  }
}

std::vector<RecoSubjetHTTv2>
RecoSubjetReaderHTTv2::read() const
{
  const RecoSubjetReaderHTTv2 * const gInstance = instances_[branchName_obj_];
  assert(gInstance);

  std::vector<RecoSubjetHTTv2> jets;
  const UInt_t nJets = gInstance->nJets_;
  if(nJets > max_nJets_)
  {
    throw cmsException(this)
      << "Number of jets stored in Ntuple = " << nJets << ", exceeds max_nJets = " << max_nJets_ << " !!\n";
  }

  if(nJets > 0)
  {
    jets.reserve(nJets);
    for(UInt_t idxJet = 0; idxJet < nJets; ++idxJet)
    {
      jets.push_back({
        {
          gInstance->jet_pt_[idxJet],
          gInstance->jet_eta_[idxJet],
          gInstance->jet_phi_[idxJet],
          gInstance->jet_mass_[idxJet]
        },
        ( gInstance->jet_IDPassed_[idxJet] > 0.5 ) ? true : false ,
        gInstance->jet_btagDeepB_[idxJet],
        gInstance->jet_area_[idxJet],
        static_cast<Int_t>(idxJet)
      });
    } // idxJet
  } // nJets > 0
  return jets;
}
