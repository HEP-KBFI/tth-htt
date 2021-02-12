#include "tthAnalysis/HiggsToTauTau/interface/LHEParticleReader.h" // LHEParticleReader

#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h" // cmsException()
#include "tthAnalysis/HiggsToTauTau/interface/BranchAddressInitializer.h" // BranchAddressInitializer, TTree, Form()

std::map<std::string, int> LHEParticleReader::numInstances_;
std::map<std::string, LHEParticleReader *> LHEParticleReader::instances_;

LHEParticleReader::LHEParticleReader()
  : LHEParticleReader("LHEPart")
{}

LHEParticleReader::LHEParticleReader(const std::string & branchName_particles)
  : max_nParticles_(32)
  , branchName_nParticles_(Form("n%s", branchName_particles.data()))
  , branchName_particles_(branchName_particles)
  , particle_pt_(nullptr)
  , particle_eta_(nullptr)
  , particle_phi_(nullptr)
  , particle_mass_(nullptr)
  , particle_pdgId_(nullptr)
  , particle_status_(nullptr)
{
  setBranchNames();
}

LHEParticleReader::~LHEParticleReader()
{
  --numInstances_[branchName_particles_];
  assert(numInstances_[branchName_particles_] >= 0);

  if(numInstances_[branchName_particles_] == 0)
  {
    LHEParticleReader * const gInstance = instances_[branchName_particles_];
    assert(gInstance);
    delete[] gInstance->particle_pt_;
    delete[] gInstance->particle_eta_;
    delete[] gInstance->particle_phi_;
    delete[] gInstance->particle_mass_;
    delete[] gInstance->particle_pdgId_;
    delete[] gInstance->particle_status_;
    instances_[branchName_particles_] = nullptr;
  }
}

void
LHEParticleReader::setBranchNames()
{
  if(numInstances_[branchName_particles_] == 0)
  {
    branchName_particle_pt_ = Form("%s_%s", branchName_particles_.data(), "pt");
    branchName_particle_eta_ = Form("%s_%s", branchName_particles_.data(), "eta");
    branchName_particle_phi_ = Form("%s_%s", branchName_particles_.data(), "phi");
    branchName_particle_mass_ = Form("%s_%s", branchName_particles_.data(), "mass");
    branchName_particle_pdgId_ = Form("%s_%s", branchName_particles_.data(), "pdgId");
    branchName_particle_status_ = Form("%s_%s", branchName_particles_.data(), "status");
    instances_[branchName_particles_] = this;
  }
  else
  {
    const LHEParticleReader * const gInstance = instances_[branchName_particles_];
    assert(gInstance);
    if(branchName_nParticles_ != gInstance->branchName_nParticles_)
    {
      throw cmsException(this)
        << "Association between configuration parameters 'branchName_nParticles' and 'branchName_particles' must be unique:"
        << " present association 'branchName_nParticles' = " << branchName_nParticles_ << ","
        << " with 'branchName_particles' = " << branchName_particles_
        << " does not match previous association 'branchName_nParticles' = " << gInstance->branchName_nParticles_ << ","
        << " with 'branchName_particles' = " << gInstance->branchName_particles_ << " !!\n";
    }
  }
  ++numInstances_[branchName_particles_];
}

std::vector<std::string>
LHEParticleReader::setBranchAddresses(TTree * tree)
{
  if(instances_[branchName_particles_] == this)
  {
    BranchAddressInitializer bai(tree, max_nParticles_);
    bai.setBranchAddress(nParticles_, branchName_nParticles_);
    bai.setBranchAddress(particle_pt_, branchName_particle_pt_);
    bai.setBranchAddress(particle_eta_, branchName_particle_eta_);
    bai.setBranchAddress(particle_phi_, branchName_particle_phi_);
    bai.setBranchAddress(particle_mass_, branchName_particle_mass_);
    bai.setBranchAddress(particle_pdgId_, branchName_particle_pdgId_);
    bai.ignoreErrors(true);
    bai.setBranchAddress(particle_status_, branchName_particle_status_);
    bai.ignoreErrors(false);
    return bai.getBoundBranchNames();
  }
  return {};
}

std::vector<LHEParticle>
LHEParticleReader::read() const
{
  const LHEParticleReader * const gInstance = instances_[branchName_particles_];
  assert(gInstance);

  const UInt_t nParticles = gInstance->nParticles_;
  if ( nParticles > max_nParticles_ ) {
    throw cmsException(this)
      << "Number of particles stored in Ntuple = " << nParticles << "," 
         " exceeds max_nParticles = " << max_nParticles_ << " !!\n";
  }

  std::vector<LHEParticle> particles;
  if(nParticles > 0)
  {
    particles.reserve(nParticles);
    for(UInt_t idxParticle = 0; idxParticle < nParticles; ++idxParticle)
    {
      particles.push_back({
        gInstance->particle_pt_[idxParticle],
        gInstance->particle_eta_[idxParticle],
        gInstance->particle_phi_[idxParticle],
        gInstance->particle_mass_[idxParticle],
        gInstance->particle_pdgId_[idxParticle],
        gInstance->particle_status_[idxParticle]
      });
    }
  } 
  return particles;
}
