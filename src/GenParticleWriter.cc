#include "tthAnalysis/HiggsToTauTau/interface/GenParticleWriter.h" // GenParticleWriter

#include "FWCore/Utilities/interface/Exception.h"

#include "tthAnalysis/HiggsToTauTau/interface/writerAuxFunctions.h" // setBranchI, setBranchVI, setBranchVF

#include <TString.h> // Form

GenParticleWriter::GenParticleWriter(const std::string& branchName_num, const std::string& branchName_obj)
  : max_nParticles_(32)
  , branchName_num_(branchName_num)
  , branchName_obj_(branchName_obj)
  , particle_pt_(0)
  , particle_eta_(0)
  , particle_phi_(0)
  , particle_mass_(0)
  , particle_charge_(0)
  , particle_pdgId_(0)
{
  setBranchNames();
}

GenParticleWriter::~GenParticleWriter()
{
  delete[] particle_pt_;
  delete[] particle_eta_;
  delete[] particle_phi_;
  delete[] particle_mass_;
  delete[] particle_charge_;
  delete[] particle_pdgId_;
}

void GenParticleWriter::setBranchNames()
{
  branchName_pt_ = Form("%s_%s", branchName_obj_.data(), "pt");
  branchName_eta_ = Form("%s_%s", branchName_obj_.data(), "eta");
  branchName_phi_ = Form("%s_%s", branchName_obj_.data(), "phi");
  branchName_mass_ = Form("%s_%s", branchName_obj_.data(), "mass");
  branchName_charge_ = Form("%s_%s", branchName_obj_.data(), "charge");
  branchName_pdgId_ = Form("%s_%s", branchName_obj_.data(), "pdgId");
}

void GenParticleWriter::setBranches(TTree* tree)
{
  setBranchI(tree, branchName_num_, &nParticles_);
  particle_pt_ = new Float_t[max_nParticles_];
  setBranchVF(tree, branchName_pt_, branchName_num_, particle_pt_);
  particle_eta_ = new Float_t[max_nParticles_];
  setBranchVF(tree, branchName_eta_, branchName_num_, particle_eta_); 
  particle_phi_ = new Float_t[max_nParticles_];
  setBranchVF(tree, branchName_phi_, branchName_num_, particle_phi_); 
  particle_mass_ = new Float_t[max_nParticles_];
  setBranchVF(tree, branchName_mass_, branchName_num_, particle_mass_); 
  particle_charge_ = new Float_t[max_nParticles_];
  setBranchVF(tree, branchName_charge_, branchName_num_, particle_charge_);
  particle_pdgId_ = new Int_t[max_nParticles_];
  setBranchVI(tree, branchName_pdgId_, branchName_num_, particle_pdgId_); 
}

void GenParticleWriter::write(const std::vector<GenParticle>& particles)
{
  nParticles_ = particles.size();
  for ( Int_t idxParticle = 0; idxParticle < nParticles_; ++idxParticle ) {
    const GenParticle& particle = particles[idxParticle];
    particle_pt_[idxParticle] = particle.pt();
    particle_eta_[idxParticle] = particle.eta();
    particle_phi_[idxParticle] = particle.phi();
    particle_mass_[idxParticle] = particle.mass();
    particle_charge_[idxParticle] = particle.charge();
    particle_pdgId_[idxParticle] = particle.pdgId();
  }
}
