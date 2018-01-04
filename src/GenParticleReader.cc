#include "tthAnalysis/HiggsToTauTau/interface/GenParticleReader.h" // GenParticleReader

#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h" // cmsException()

#include <TString.h> // Form()
#include <TTree.h> // TTree

std::map<std::string, int> GenParticleReader::numInstances_;
std::map<std::string, GenParticleReader *> GenParticleReader::instances_;

GenParticleReader::GenParticleReader()
  : GenParticleReader("nGenPart", "GenPart")
{}

GenParticleReader::GenParticleReader(const std::string & branchName_nParticles,
                                     const std::string & branchName_particles)
  : max_nParticles_(32)
  , branchName_nParticles_(branchName_nParticles)
  , branchName_particles_(branchName_particles)
  , particle_pt_(nullptr)
  , particle_eta_(nullptr)
  , particle_phi_(nullptr)
  , particle_mass_(nullptr)
  , particle_pdgId_(nullptr)
  , particle_charge_(nullptr)
{
  setBranchNames();
}

GenParticleReader::~GenParticleReader()
{
  --numInstances_[branchName_particles_];
  assert(numInstances_[branchName_particles_] >= 0);

  if(numInstances_[branchName_particles_] == 0)
  {
    GenParticleReader * const gInstance = instances_[branchName_particles_];
    assert(gInstance);
    delete[] gInstance->particle_pt_;
    delete[] gInstance->particle_eta_;
    delete[] gInstance->particle_phi_;
    delete[] gInstance->particle_mass_;
    delete[] gInstance->particle_pdgId_;
    delete[] gInstance->particle_charge_;
    instances_[branchName_particles_] = nullptr;
  }
}

void GenParticleReader::setBranchNames()
{
  if(numInstances_[branchName_particles_] == 0)
  {
    branchName_particle_pt_ = Form("%s_%s", branchName_particles_.data(), "pt");
    branchName_particle_eta_ = Form("%s_%s", branchName_particles_.data(), "eta");
    branchName_particle_phi_ = Form("%s_%s", branchName_particles_.data(), "phi");
    branchName_particle_mass_ = Form("%s_%s", branchName_particles_.data(), "mass");
    branchName_particle_pdgId_ = Form("%s_%s", branchName_particles_.data(), "pdgId");
    branchName_particle_charge_ = Form("%s_%s", branchName_particles_.data(), "charge");
    instances_[branchName_particles_] = this;
  }
  else
  {
    const GenParticleReader * const gInstance = instances_[branchName_particles_];
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

void
GenParticleReader::setBranchAddresses(TTree * tree)
{
  if(instances_[branchName_particles_] == this)
  {
    tree->SetBranchAddress(branchName_nParticles_.data(), &nParticles_);   
    particle_pt_ = new Float_t[max_nParticles_];
    tree->SetBranchAddress(branchName_particle_pt_.data(), particle_pt_); 
    particle_eta_ = new Float_t[max_nParticles_];
    tree->SetBranchAddress(branchName_particle_eta_.data(), particle_eta_); 
    particle_phi_ = new Float_t[max_nParticles_];
    tree->SetBranchAddress(branchName_particle_phi_.data(), particle_phi_); 
    particle_mass_ = new Float_t[max_nParticles_];
    tree->SetBranchAddress(branchName_particle_mass_.data(), particle_mass_); 
    particle_pdgId_ = new Int_t[max_nParticles_];
    tree->SetBranchAddress(branchName_particle_pdgId_.data(), particle_pdgId_); 
    particle_charge_ = new Int_t[max_nParticles_];
    tree->SetBranchAddress(branchName_particle_charge_.data(), particle_charge_); 
  }
}

std::vector<GenParticle>
GenParticleReader::read() const
{
  const GenParticleReader * const gInstance = instances_[branchName_particles_];
  assert(gInstance);

  const UInt_t nParticles = gInstance->nParticles_;
  if ( nParticles > max_nParticles_ ) {
    throw cmsException(this)
      << "Number of particles stored in Ntuple = " << nParticles << "," 
      << " exceeds max_nParticles = " << max_nParticles_ << " !!\n";
  }

  std::vector<GenParticle> particles;
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
        gInstance->particle_charge_[idxParticle]
      });
    }
  } 
  return particles;
}
