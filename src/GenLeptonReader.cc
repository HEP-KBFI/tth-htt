#include "tthAnalysis/HiggsToTauTau/interface/GenLeptonReader.h" // GenLeptonReader

#include "FWCore/Utilities/interface/Exception.h"

#include <TString.h> // Form

std::map<std::string, int> GenLeptonReader::numInstances_;
std::map<std::string, GenLeptonReader*> GenLeptonReader::instances_;

GenLeptonReader::GenLeptonReader()
  : max_nLeptons_(32)
  , branchName_num_("nGenLep")
  , branchName_obj_("GenLep")
  , lepton_pt_(0)
  , lepton_eta_(0)
  , lepton_phi_(0)
  , lepton_mass_(0)
  , lepton_pdgId_(0)
{
  setBranchNames();
}

GenLeptonReader::GenLeptonReader(const std::string& branchName_num, const std::string& branchName_obj)
  : max_nLeptons_(32)
  , branchName_num_(branchName_num)
  , branchName_obj_(branchName_obj)
  , lepton_pt_(0)
  , lepton_eta_(0)
  , lepton_phi_(0)
  , lepton_mass_(0)
  , lepton_pdgId_(0)
{
  setBranchNames();
}

GenLeptonReader::~GenLeptonReader()
{
  --numInstances_[branchName_obj_];
  assert(numInstances_[branchName_obj_] >= 0);
  if ( numInstances_[branchName_obj_] == 0 ) {
    GenLeptonReader* gInstance = instances_[branchName_obj_];
    assert(gInstance);
    delete gInstance->lepton_pt_;
    delete gInstance->lepton_eta_;
    delete gInstance->lepton_phi_;
    delete gInstance->lepton_mass_;
    delete gInstance->lepton_pdgId_;
    instances_[branchName_obj_] = 0;
  }
}

void GenLeptonReader::setBranchNames()
{
  if ( numInstances_[branchName_obj_] == 0 ) {
    branchName_pt_ = Form("%s_%s", branchName_obj_.data(), "pt");
    branchName_eta_ = Form("%s_%s", branchName_obj_.data(), "eta");
    branchName_phi_ = Form("%s_%s", branchName_obj_.data(), "phi");
    branchName_mass_ = Form("%s_%s", branchName_obj_.data(), "mass");
    branchName_pdgId_ = Form("%s_%s", branchName_obj_.data(), "pdgId");
    instances_[branchName_obj_] = this;
  } else {
    if ( branchName_num_ != instances_[branchName_obj_]->branchName_num_ ) {
      throw cms::Exception("GenLeptonReader") 
	<< "Association between configuration parameters 'branchName_num' and 'branchName_obj' must be unique:"
	<< " present association 'branchName_num' = " << branchName_num_ << " with 'branchName_obj' = " << branchName_obj_ 
	<< " does not match previous association 'branchName_num' = " << instances_[branchName_obj_]->branchName_num_ << " with 'branchName_obj' = " << instances_[branchName_obj_]->branchName_obj_ << " !!\n";
    }
  }
  ++numInstances_[branchName_obj_];
}

void GenLeptonReader::setBranchAddresses(TTree* tree)
{
  if ( instances_[branchName_obj_] == this ) {
    tree->SetBranchAddress(branchName_num_.data(), &nLeptons_);   
    lepton_pt_ = new Float_t[max_nLeptons_];
    tree->SetBranchAddress(branchName_pt_.data(), lepton_pt_); 
    lepton_eta_ = new Float_t[max_nLeptons_];
    tree->SetBranchAddress(branchName_eta_.data(), lepton_eta_); 
    lepton_phi_ = new Float_t[max_nLeptons_];
    tree->SetBranchAddress(branchName_phi_.data(), lepton_phi_); 
    lepton_mass_ = new Float_t[max_nLeptons_];
    tree->SetBranchAddress(branchName_mass_.data(), lepton_mass_); 
    lepton_pdgId_ = new Int_t[max_nLeptons_];
    tree->SetBranchAddress(branchName_pdgId_.data(), lepton_pdgId_); 
  }
}

std::vector<GenLepton> GenLeptonReader::read() const
{
  GenLeptonReader* gInstance = instances_[branchName_obj_];
  assert(gInstance);
  std::vector<GenLepton> leptons;
  Int_t nLeptons = gInstance->nLeptons_;
  if ( nLeptons > max_nLeptons_ ) {
    throw cms::Exception("GenLeptonReader") 
      << "Number of leptons stored in Ntuple = " << nLeptons << ", exceeds max_nLeptons = " << max_nLeptons_ << " !!\n";
  }
  leptons.reserve(nLeptons);
  for ( Int_t idxLepton = 0; idxLepton < nLeptons; ++idxLepton ) {
    leptons.push_back(GenLepton({ 
      gInstance->lepton_pt_[idxLepton],
      gInstance->lepton_eta_[idxLepton],
      gInstance->lepton_phi_[idxLepton],
      gInstance->lepton_mass_[idxLepton],
      gInstance->lepton_pdgId_[idxLepton] }));
  }
  return leptons;
}
