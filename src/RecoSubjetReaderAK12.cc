#include "tthAnalysis/HiggsToTauTau/interface/RecoSubjetReaderAK12.h" // RecoSubjetReaderAK12

#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h" // cmsException()
#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // kBtag_*
#include "tthAnalysis/HiggsToTauTau/interface/BranchAddressInitializer.h" // BranchAddressInitializer, TTree, Form()

std::map<std::string, int> RecoSubjetReaderAK12::numInstances_;
std::map<std::string, RecoSubjetReaderAK12 *> RecoSubjetReaderAK12::instances_;

RecoSubjetReaderAK12::RecoSubjetReaderAK12(int era)
  : RecoSubjetReaderAK12(era, "SubJetAK12")
{}

RecoSubjetReaderAK12::RecoSubjetReaderAK12(int era,
					   const std::string & branchName_obj)
  : era_(era)
  , max_nJets_(128)
  , branchName_num_(Form("n%s", branchName_obj.data()))
  , branchName_obj_(branchName_obj)
  , jet_pt_(nullptr)
  , jet_eta_(nullptr)
  , jet_phi_(nullptr)
  , jet_mass_(nullptr)
  , jet_charge_(nullptr)
  , jet_pullEta_(nullptr)
  , jet_pullPhi_(nullptr)
  , jet_pullMag_(nullptr)
{
  setBranchNames();
}

RecoSubjetReaderAK12::~RecoSubjetReaderAK12()
{
  --numInstances_[branchName_obj_];
  assert(numInstances_[branchName_obj_] >= 0);
  if(numInstances_[branchName_obj_] == 0)
  {
    RecoSubjetReaderAK12 * const gInstance = instances_[branchName_obj_];
    assert(gInstance);
    delete[] gInstance->jet_pt_;
    delete[] gInstance->jet_eta_;
    delete[] gInstance->jet_phi_;
    delete[] gInstance->jet_mass_;
    delete[] gInstance->jet_charge_;
    delete[] gInstance->jet_pullEta_;
    delete[] gInstance->jet_pullPhi_;
    delete[] gInstance->jet_pullMag_;
    instances_[branchName_obj_] = nullptr;
  }
}

void
RecoSubjetReaderAK12::setBranchNames()
{
  if(numInstances_[branchName_obj_] == 0)
  {
    branchName_pt_ = Form("%s_%s", branchName_obj_.data(), "pt");
    branchName_eta_ = Form("%s_%s", branchName_obj_.data(), "eta");
    branchName_phi_ = Form("%s_%s", branchName_obj_.data(), "phi");
    branchName_mass_ = Form("%s_%s", branchName_obj_.data(), "mass");
    branchName_jetCharge_ = Form("%s_%s", branchName_obj_.data(), "jetCharge");
    branchName_pullEta_ = Form("%s_%s", branchName_obj_.data(), "pullEta");
    branchName_pullPhi_ = Form("%s_%s", branchName_obj_.data(), "pullPhi");
    branchName_pullMag_ = Form("%s_%s", branchName_obj_.data(), "pullMag");
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
RecoSubjetReaderAK12::setBranchAddresses(TTree * tree)
{
  if(instances_[branchName_obj_] == this)
  {
    BranchAddressInitializer bai(tree, max_nJets_);
    bai.setBranchAddress(nJets_, branchName_num_);
    bai.setBranchAddress(jet_pt_, branchName_pt_);
    bai.setBranchAddress(jet_eta_, branchName_eta_);
    bai.setBranchAddress(jet_phi_, branchName_phi_);
    bai.setBranchAddress(jet_mass_, branchName_mass_);
    bai.setBranchAddress(jet_charge_, branchName_jetCharge_);
    bai.setBranchAddress(jet_pullEta_, branchName_pullEta_);
    bai.setBranchAddress(jet_pullPhi_, branchName_pullPhi_);
    bai.setBranchAddress(jet_pullMag_, branchName_pullMag_);
  }
}

std::vector<RecoSubjetAK12>
RecoSubjetReaderAK12::read() const
{
  const RecoSubjetReaderAK12 * const gInstance = instances_[branchName_obj_];
  assert(gInstance);

  std::vector<RecoSubjetAK12> jets;
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
	gInstance->jet_charge_[idxJet],
	gInstance->jet_pullEta_[idxJet],
	gInstance->jet_pullPhi_[idxJet],
	gInstance->jet_pullMag_[idxJet],
        static_cast<Int_t>(idxJet)
      });
    } // idxJet
  } // nJets > 0
  return jets;
}
