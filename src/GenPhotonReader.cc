#include "tthAnalysis/HiggsToTauTau/interface/GenPhotonReader.h" // GenPhotonReader

#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h" // cmsException()
#include "tthAnalysis/HiggsToTauTau/interface/BranchAddressInitializer.h" // BranchAddressInitializer, TTree, Form()

std::map<std::string, int> GenPhotonReader::numInstances_;
std::map<std::string, GenPhotonReader *> GenPhotonReader::instances_;

GenPhotonReader::GenPhotonReader()
  : GenPhotonReader("GenPhoton")
{}

GenPhotonReader::GenPhotonReader(const std::string & branchName_obj)
  : max_nPhotons_(32)
  , branchName_num_(Form("n%s", branchName_obj.data()))
  , branchName_obj_(branchName_obj)
  , photon_pt_(nullptr)
  , photon_eta_(nullptr)
  , photon_phi_(nullptr)
  , photon_mass_(nullptr)
  , photon_pdgId_(nullptr)
{
  setBranchNames();
}

GenPhotonReader::~GenPhotonReader()
{
  --numInstances_[branchName_obj_];
  assert(numInstances_[branchName_obj_] >= 0);
  if(numInstances_[branchName_obj_] == 0)
  {
    GenPhotonReader * const gInstance = instances_[branchName_obj_];
    assert(gInstance);
    delete[] gInstance->photon_pt_;
    delete[] gInstance->photon_eta_;
    delete[] gInstance->photon_phi_;
    delete[] gInstance->photon_mass_;
    delete[] gInstance->photon_pdgId_;
    instances_[branchName_obj_] = nullptr;
  }
}

void
GenPhotonReader::setBranchNames()
{
  if(numInstances_[branchName_obj_] == 0)
  {
    branchName_pt_ = Form("%s_%s", branchName_obj_.data(), "pt");
    branchName_eta_ = Form("%s_%s", branchName_obj_.data(), "eta");
    branchName_phi_ = Form("%s_%s", branchName_obj_.data(), "phi");
    branchName_mass_ = Form("%s_%s", branchName_obj_.data(), "mass");
    branchName_pdgId_ = Form("%s_%s", branchName_obj_.data(), "pdgId");
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
GenPhotonReader::setBranchAddresses(TTree * tree)
{
  if(instances_[branchName_obj_] == this)
  {
    BranchAddressInitializer bai(tree, max_nPhotons_);
    bai.setBranchAddress(nPhotons_, branchName_num_);
    bai.setBranchAddress(photon_pt_, branchName_pt_);
    bai.setBranchAddress(photon_eta_, branchName_eta_);
    bai.setBranchAddress(photon_phi_, branchName_phi_);
    bai.setBranchAddress(photon_mass_, branchName_mass_);
    bai.setBranchAddress(photon_pdgId_, branchName_pdgId_);
  }
}

std::vector<GenPhoton>
GenPhotonReader::read() const
{
  const GenPhotonReader * const gInstance = instances_[branchName_obj_];
  assert(gInstance);

  const UInt_t nPhotons = gInstance->nPhotons_;
  if(nPhotons > max_nPhotons_)
  {
    throw cmsException(this)
      << "Number of photons stored in Ntuple = " << nPhotons << ", "
         "exceeds max_nPhotons = " << max_nPhotons_ << " !!\n"
    ;
  }

  std::vector<GenPhoton> photons;
  if(nPhotons > 0)
  {
    photons.reserve(nPhotons);
    for(UInt_t idxPhoton = 0; idxPhoton < nPhotons; ++idxPhoton)
    {
      photons.push_back({
        gInstance->photon_pt_[idxPhoton],
        gInstance->photon_eta_[idxPhoton],
        gInstance->photon_phi_[idxPhoton],
        gInstance->photon_mass_[idxPhoton],
        gInstance->photon_pdgId_[idxPhoton],
      });
    }
  }
  return photons;
}
