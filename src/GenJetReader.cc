#include "tthAnalysis/HiggsToTauTau/interface/GenJetReader.h" // GenJetReader

#include "FWCore/Utilities/interface/Exception.h"

#include <TString.h> // Form

std::map<std::string, int> GenJetReader::numInstances_;
std::map<std::string, GenJetReader*> GenJetReader::instances_;

GenJetReader::GenJetReader()
  : max_nJets_(32)
  , branchName_num_("nGenJet")
  , branchName_obj_("GenJet")
  , jet_pt_(0)
  , jet_eta_(0)
  , jet_phi_(0)
  , jet_mass_(0)
{
  setBranchNames();
}

GenJetReader::GenJetReader(const std::string& branchName_num, const std::string& branchName_obj)
  : max_nJets_(32)
  , branchName_num_(branchName_num)
  , branchName_obj_(branchName_obj)
  , jet_pt_(0)
  , jet_eta_(0)
  , jet_phi_(0)
  , jet_mass_(0)
{
  setBranchNames();
}

GenJetReader::~GenJetReader()
{
  --numInstances_[branchName_obj_];
  assert(numInstances_[branchName_obj_] >= 0);
  if ( numInstances_[branchName_obj_] == 0 ) {
    GenJetReader* gInstance = instances_[branchName_obj_];
    assert(gInstance);
    delete gInstance->jet_pt_;
    delete gInstance->jet_eta_;
    delete gInstance->jet_phi_;
    delete gInstance->jet_mass_;
    instances_[branchName_obj_] = 0;
  }
}

void GenJetReader::setBranchNames()
{
  if ( numInstances_[branchName_obj_] == 0 ) {
    branchName_pt_ = Form("%s_%s", branchName_obj_.data(), "pt");
    branchName_eta_ = Form("%s_%s", branchName_obj_.data(), "eta");
    branchName_phi_ = Form("%s_%s", branchName_obj_.data(), "phi");
    branchName_mass_ = Form("%s_%s", branchName_obj_.data(), "mass");
    instances_[branchName_obj_] = this;
  } else {
    if ( branchName_num_ != instances_[branchName_obj_]->branchName_num_ ) {
      throw cms::Exception("GenJetReader") 
	<< "Association between configuration parameters 'branchName_num' and 'branchName_obj' must be unique:"
	<< " present association 'branchName_num' = " << branchName_num_ << " with 'branchName_obj' = " << branchName_obj_ 
	<< " does not match previous association 'branchName_num' = " << instances_[branchName_obj_]->branchName_num_ << " with 'branchName_obj' = " << instances_[branchName_obj_]->branchName_obj_ << " !!\n";
    }
  }
  ++numInstances_[branchName_obj_];
}

void GenJetReader::setBranchAddresses(TTree* tree)
{
  if ( instances_[branchName_obj_] == this ) {
    tree->SetBranchAddress(branchName_num_.data(), &nJets_);   
    jet_pt_ = new Float_t[max_nJets_];
    tree->SetBranchAddress(branchName_pt_.data(), jet_pt_); 
    jet_eta_ = new Float_t[max_nJets_];
    tree->SetBranchAddress(branchName_eta_.data(), jet_eta_); 
    jet_phi_ = new Float_t[max_nJets_];
    tree->SetBranchAddress(branchName_phi_.data(), jet_phi_); 
    jet_mass_ = new Float_t[max_nJets_];
    tree->SetBranchAddress(branchName_mass_.data(), jet_mass_); 
  }
}

std::vector<GenJet> GenJetReader::read() const
{
  GenJetReader* gInstance = instances_[branchName_obj_];
  assert(gInstance);
  std::vector<GenJet> jets;
  Int_t nJets = gInstance->nJets_;
  if ( nJets > max_nJets_ ) {
    throw cms::Exception("GenJetReader") 
      << "Number of jets stored in Ntuple = " << nJets << ", exceeds max_nJets = " << max_nJets_ << " !!\n";
  }
  jets.reserve(nJets);
  for ( Int_t idxJet = 0; idxJet < nJets; ++idxJet ) {
    jets.push_back(GenJet({ 
      gInstance->jet_pt_[idxJet],
      gInstance->jet_eta_[idxJet],
      gInstance->jet_phi_[idxJet],
      gInstance->jet_mass_[idxJet]}));
  }
  return jets;
}
