#include "tthAnalysis/HiggsToTauTau/interface/GenParticleWriter.h" // GenParticleWriter

#include "tthAnalysis/HiggsToTauTau/interface/BranchAddressInitializer.h" // BranchAddressInitializer, TTree, Form()

GenParticleWriter::GenParticleWriter(const std::string & branchName_obj,
                                     unsigned int max_nParticles)
  : GenParticleWriter(Form("n%s", branchName_obj.data()), branchName_obj, max_nParticles)
{}

GenParticleWriter::GenParticleWriter(const std::string & branchName_num,
                                     const std::string & branchName_obj,
                                     unsigned int max_nParticles)
  : max_nParticles_(max_nParticles)
  , branchName_num_(branchName_num)
  , branchName_obj_(branchName_obj)
  , nParticles_(0)
  , particle_pt_(nullptr)
  , particle_eta_(nullptr)
  , particle_phi_(nullptr)
  , particle_mass_(nullptr)
  , particle_pdgId_(nullptr)
  , particle_charge_(nullptr)
  , particle_status_(nullptr)
  , particle_statusFlags_(nullptr)
  , particle_genPartFlav_(nullptr)
{
  setBranchNames();
}

GenParticleWriter::~GenParticleWriter()
{
  delete[] particle_pt_;
  delete[] particle_eta_;
  delete[] particle_phi_;
  delete[] particle_mass_;
  delete[] particle_pdgId_;
  delete[] particle_charge_;
  delete[] particle_status_;
  delete[] particle_statusFlags_;
  delete[] particle_genPartFlav_;
}

void GenParticleWriter::setBranchNames()
{
  branchName_pt_ = Form("%s_%s", branchName_obj_.data(), "pt");
  branchName_eta_ = Form("%s_%s", branchName_obj_.data(), "eta");
  branchName_phi_ = Form("%s_%s", branchName_obj_.data(), "phi");
  branchName_mass_ = Form("%s_%s", branchName_obj_.data(), "mass");
  branchName_pdgId_ = Form("%s_%s", branchName_obj_.data(), "pdgId");
  branchName_charge_ = Form("%s_%s", branchName_obj_.data(), "charge");
  branchName_status_ = Form("%s_%s", branchName_obj_.data(), "status");
  branchName_statusFlags_ = Form("%s_%s", branchName_obj_.data(), "statusFlags");
  branchName_genPartFlav_ = Form("%s_%s", branchName_obj_.data(), "genPartFlav");
}

void GenParticleWriter::setBranches(TTree * tree)
{
  BranchAddressInitializer bai(tree, max_nParticles_, branchName_num_);
  bai.setBranch(nParticles_, branchName_num_);
  bai.setBranch(particle_pt_, branchName_pt_);
  bai.setBranch(particle_eta_, branchName_eta_);
  bai.setBranch(particle_phi_, branchName_phi_);
  bai.setBranch(particle_mass_, branchName_mass_);
  bai.setBranch(particle_pdgId_, branchName_pdgId_);
  bai.setBranch(particle_charge_, branchName_charge_);
  bai.setBranch(particle_status_, branchName_status_);
  bai.setBranch(particle_statusFlags_, branchName_statusFlags_);
  bai.setBranch(particle_genPartFlav_, branchName_genPartFlav_);
}

void GenParticleWriter::write(const std::vector<GenParticle> & particles)
{
  nParticles_ = particles.size();
  for(UInt_t idxParticle = 0; idxParticle < nParticles_; ++idxParticle)
  {
    const GenParticle & particle = particles[idxParticle];
    particle_pt_[idxParticle] = particle.pt();
    particle_eta_[idxParticle] = particle.eta();
    particle_phi_[idxParticle] = particle.phi();
    particle_mass_[idxParticle] = particle.mass();
    particle_pdgId_[idxParticle] = particle.pdgId();
    particle_charge_[idxParticle] = particle.charge();
    particle_status_[idxParticle] = particle.status();
    particle_statusFlags_[idxParticle] = particle.statusFlags();
    particle_genPartFlav_[idxParticle] = particle.genPartFlav();
  }
}
