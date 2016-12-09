#include "tthAnalysis/HiggsToTauTau/interface/GenParticleReader.h" // GenParticleReader

#include "FWCore/Utilities/interface/Exception.h"

#include <TString.h> // Form

std::map<std::string, int> GenParticleReader::numInstances_;
std::map<std::string, GenParticleReader*> GenParticleReader::instances_;

GenParticleReader::GenParticleReader(const std::string& branchName_num, const std::string& branchName_obj)
  : max_nParticles_(32)
  , branchName_num_(branchName_num)
  , branchName_obj_(branchName_obj)
  , particle_pt_(0)
  , particle_eta_(0)
  , particle_phi_(0)
  , particle_mass_(0)
  , particle_pdgId_(0)
{
  setBranchNames();
}

GenParticleReader::~GenParticleReader()
{
  --numInstances_[branchName_obj_];
  assert(numInstances_[branchName_obj_] >= 0);
  if ( numInstances_[branchName_obj_] == 0 ) {
    GenParticleReader* gInstance = instances_[branchName_obj_];
    assert(gInstance);
    delete[] gInstance->particle_pt_;
    delete[] gInstance->particle_eta_;
    delete[] gInstance->particle_phi_;
    delete[] gInstance->particle_mass_;
    delete[] gInstance->particle_pdgId_;
    instances_[branchName_obj_] = 0;
  }
}

void GenParticleReader::setBranchNames()
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
      throw cms::Exception("GenParticleReader") 
	<< "Association between configuration parameters 'branchName_num' and 'branchName_obj' must be unique:"
	<< " present association 'branchName_num' = " << branchName_num_ << " with 'branchName_obj' = " << branchName_obj_ 
	<< " does not match previous association 'branchName_num' = " << instances_[branchName_obj_]->branchName_num_ << " with 'branchName_obj' = " << instances_[branchName_obj_]->branchName_obj_ << " !!\n";
    }
  }
  ++numInstances_[branchName_obj_];
}

void GenParticleReader::setBranchAddresses(TTree* tree)
{
  if ( instances_[branchName_obj_] == this ) {
    tree->SetBranchAddress(branchName_num_.data(), &nParticles_);   
    particle_pt_ = new Float_t[max_nParticles_];
    tree->SetBranchAddress(branchName_pt_.data(), particle_pt_); 
    particle_eta_ = new Float_t[max_nParticles_];
    tree->SetBranchAddress(branchName_eta_.data(), particle_eta_); 
    particle_phi_ = new Float_t[max_nParticles_];
    tree->SetBranchAddress(branchName_phi_.data(), particle_phi_); 
    particle_mass_ = new Float_t[max_nParticles_];
    tree->SetBranchAddress(branchName_mass_.data(), particle_mass_); 
    particle_pdgId_ = new Int_t[max_nParticles_];
    tree->SetBranchAddress(branchName_pdgId_.data(), particle_pdgId_); 
  }
}

std::vector<GenLepton> GenParticleReader::read() const
{
  GenParticleReader* gInstance = instances_[branchName_obj_];
  assert(gInstance);
  std::vector<GenLepton> particles;
  Int_t nParticles = gInstance->nParticles_;
  if ( nParticles > max_nParticles_ ) {
    throw cms::Exception("GenParticleReader") 
      << "Number of particles stored in Ntuple = " << nParticles << ", exceeds max_nParticles = " << max_nParticles_ << " !!\n";
  }
  particles.reserve(nParticles);
  for ( Int_t idxParticle = 0; idxParticle < nParticles; ++idxParticle ) {
    particles.push_back(GenLepton({ 
      gInstance->particle_pt_[idxParticle],
      gInstance->particle_eta_[idxParticle],
      gInstance->particle_phi_[idxParticle],
      gInstance->particle_mass_[idxParticle],
      gInstance->particle_pdgId_[idxParticle] }));
  }
  return particles;
}
