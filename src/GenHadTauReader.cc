#include "tthAnalysis/HiggsToTauTau/interface/GenHadTauReader.h" // GenHadTauReader

#include "FWCore/Utilities/interface/Exception.h"

#include <TString.h> // Form

std::map<std::string, int> GenHadTauReader::numInstances_;
std::map<std::string, GenHadTauReader*> GenHadTauReader::instances_;

GenHadTauReader::GenHadTauReader()
  : max_nHadTaus_(32)
  , branchName_num_("nGenHadTaus")
  , branchName_obj_("GenHadTaus")
  , hadTau_pt_(0)
  , hadTau_eta_(0)
  , hadTau_phi_(0)
  , hadTau_mass_(0)
  , hadTau_charge_(0)
{
  setBranchNames();
}

GenHadTauReader::GenHadTauReader(const std::string& branchName_num, const std::string& branchName_obj)
  : max_nHadTaus_(32)
  , branchName_num_(branchName_num)
  , branchName_obj_(branchName_obj)
  , hadTau_pt_(0)
  , hadTau_eta_(0)
  , hadTau_phi_(0)
  , hadTau_mass_(0)
  , hadTau_charge_(0)
{
  setBranchNames();
}

GenHadTauReader::~GenHadTauReader()
{
  --numInstances_[branchName_obj_];
  assert(numInstances_[branchName_obj_] >= 0);
  if ( numInstances_[branchName_obj_] == 0 ) {
    GenHadTauReader* gInstance = instances_[branchName_obj_];
    assert(gInstance);
    delete[] gInstance->hadTau_pt_;
    delete[] gInstance->hadTau_eta_;
    delete[] gInstance->hadTau_phi_;
    delete[] gInstance->hadTau_mass_;
    delete[] gInstance->hadTau_charge_;
    instances_[branchName_obj_] = 0;
  }
}

void GenHadTauReader::setBranchNames()
{
  if ( numInstances_[branchName_obj_] == 0 ) {
    branchName_pt_ = Form("%s_%s", branchName_obj_.data(), "pt");
    branchName_eta_ = Form("%s_%s", branchName_obj_.data(), "eta");
    branchName_phi_ = Form("%s_%s", branchName_obj_.data(), "phi");
    branchName_mass_ = Form("%s_%s", branchName_obj_.data(), "mass");
    branchName_charge_ = Form("%s_%s", branchName_obj_.data(), "charge");
    instances_[branchName_obj_] = this;
  } else {
    if ( branchName_num_ != instances_[branchName_obj_]->branchName_num_ ) {
      throw cms::Exception("GenHadTauReader") 
	<< "Association between configuration parameters 'branchName_num' and 'branchName_obj' must be unique:"
	<< " present association 'branchName_num' = " << branchName_num_ << " with 'branchName_obj' = " << branchName_obj_ 
	<< " does not match previous association 'branchName_num' = " << instances_[branchName_obj_]->branchName_num_ << " with 'branchName_obj' = " << instances_[branchName_obj_]->branchName_obj_ << " !!\n";
    }
  }
  ++numInstances_[branchName_obj_];
}

void GenHadTauReader::setBranchAddresses(TTree* tree)
{
  if ( instances_[branchName_obj_] == this ) {
    tree->SetBranchAddress(branchName_num_.data(), &nHadTaus_);   
    hadTau_pt_ = new Float_t[max_nHadTaus_];
    tree->SetBranchAddress(branchName_pt_.data(), hadTau_pt_); 
    hadTau_eta_ = new Float_t[max_nHadTaus_];
    tree->SetBranchAddress(branchName_eta_.data(), hadTau_eta_); 
    hadTau_phi_ = new Float_t[max_nHadTaus_];
    tree->SetBranchAddress(branchName_phi_.data(), hadTau_phi_); 
    hadTau_mass_ = new Float_t[max_nHadTaus_];
    tree->SetBranchAddress(branchName_mass_.data(), hadTau_mass_); 
    hadTau_charge_ = new Float_t[max_nHadTaus_];
    tree->SetBranchAddress(branchName_charge_.data(), hadTau_charge_);
  }
}

std::vector<GenHadTau> GenHadTauReader::read() const
{
  GenHadTauReader* gInstance = instances_[branchName_obj_];
  assert(gInstance);
  std::vector<GenHadTau> hadTaus;
  Int_t nHadTaus = gInstance->nHadTaus_;
  if ( nHadTaus > max_nHadTaus_ ) {
    throw cms::Exception("GenHadTauReader") 
      << "Number of hadronic taus stored in Ntuple = " << nHadTaus << ", exceeds max_nHadTaus = " << max_nHadTaus_ << " !!\n";
  }
  hadTaus.reserve(nHadTaus);
  for ( Int_t idxHadTau = 0; idxHadTau < nHadTaus; ++idxHadTau ) {
    hadTaus.push_back(GenHadTau({ 
      gInstance->hadTau_pt_[idxHadTau],
      gInstance->hadTau_eta_[idxHadTau],
      gInstance->hadTau_phi_[idxHadTau],
      gInstance->hadTau_mass_[idxHadTau],
      gInstance->hadTau_charge_[idxHadTau] }));
  }
  return hadTaus;
}
