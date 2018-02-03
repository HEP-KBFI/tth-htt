#include "tthAnalysis/HiggsToTauTau/interface/GenLeptonReader.h" // GenLeptonReader

#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h" // cmsException()
#include "tthAnalysis/HiggsToTauTau/interface/BranchAddressInitializer.h" // BranchAddressInitializer, TTree, Form()

std::map<std::string, int> GenLeptonReader::numInstances_;
std::map<std::string, GenLeptonReader *> GenLeptonReader::instances_;

GenLeptonReader::GenLeptonReader()
  : GenLeptonReader("nGenLep", "GenLep")
{}

GenLeptonReader::GenLeptonReader(const std::string & branchName_nPromptLeptons,
                                 const std::string & branchName_promptLeptons,
                                 const std::string & branchName_nLeptonsFromTau,
                                 const std::string & branchName_leptonsFromTau)
  : max_nPromptLeptons_(32)
  , branchName_nPromptLeptons_(branchName_nPromptLeptons)
  , branchName_promptLeptons_(branchName_promptLeptons)
  , max_nLeptonsFromTau_(32)
  , branchName_nLeptonsFromTau_(branchName_nLeptonsFromTau)
  , branchName_leptonsFromTau_(branchName_leptonsFromTau)
  , promptLepton_pt_(nullptr)
  , promptLepton_eta_(nullptr)
  , promptLepton_phi_(nullptr)
  , promptLepton_mass_(nullptr)
  , promptLepton_pdgId_(nullptr)
  , leptonFromTau_pt_(nullptr)
  , leptonFromTau_eta_(nullptr)
  , leptonFromTau_phi_(nullptr)
  , leptonFromTau_mass_(nullptr)
  , leptonFromTau_pdgId_(nullptr)
{
  read_promptLeptons_  = branchName_nPromptLeptons  != "" && branchName_promptLeptons  != "";
  read_leptonsFromTau_ = branchName_nLeptonsFromTau != "" && branchName_leptonsFromTau != "";
  assert(read_promptLeptons_ || read_leptonsFromTau_);
  setBranchNames();
}

GenLeptonReader::~GenLeptonReader()
{
  --numInstances_[branchName_promptLeptons_];
  assert(numInstances_[branchName_promptLeptons_] >= 0);
  if(numInstances_[branchName_promptLeptons_] == 0)
  {
    GenLeptonReader * const gInstance = instances_[branchName_promptLeptons_];
    assert(gInstance);
    delete[] gInstance->promptLepton_pt_;
    delete[] gInstance->promptLepton_eta_;
    delete[] gInstance->promptLepton_phi_;
    delete[] gInstance->promptLepton_mass_;
    delete[] gInstance->promptLepton_pdgId_;
    delete[] gInstance->leptonFromTau_pt_;
    delete[] gInstance->leptonFromTau_eta_;
    delete[] gInstance->leptonFromTau_phi_;
    delete[] gInstance->leptonFromTau_mass_;
    delete[] gInstance->leptonFromTau_pdgId_;
    instances_[branchName_promptLeptons_] = nullptr;
  }
}

void
GenLeptonReader::setBranchNames()
{
  if(numInstances_[branchName_promptLeptons_] == 0)
  {
    branchName_promptLepton_pt_ = Form("%s_%s", branchName_promptLeptons_.data(), "pt");
    branchName_promptLepton_eta_ = Form("%s_%s", branchName_promptLeptons_.data(), "eta");
    branchName_promptLepton_phi_ = Form("%s_%s", branchName_promptLeptons_.data(), "phi");
    branchName_promptLepton_mass_ = Form("%s_%s", branchName_promptLeptons_.data(), "mass");
    branchName_promptLepton_pdgId_ = Form("%s_%s", branchName_promptLeptons_.data(), "pdgId");
    branchName_leptonFromTau_pt_ = Form("%s_%s", branchName_leptonsFromTau_.data(), "pt");
    branchName_leptonFromTau_eta_ = Form("%s_%s", branchName_leptonsFromTau_.data(), "eta");
    branchName_leptonFromTau_phi_ = Form("%s_%s", branchName_leptonsFromTau_.data(), "phi");
    branchName_leptonFromTau_mass_ = Form("%s_%s", branchName_leptonsFromTau_.data(), "mass");
    branchName_leptonFromTau_pdgId_ = Form("%s_%s", branchName_leptonsFromTau_.data(), "pdgId");
    instances_[branchName_promptLeptons_] = this;
  }
  else
  {
    const GenLeptonReader * const gInstance = instances_[branchName_promptLeptons_];
    assert(gInstance);
    if(branchName_nPromptLeptons_  != gInstance->branchName_nPromptLeptons_  ||
       branchName_nLeptonsFromTau_ != gInstance->branchName_nLeptonsFromTau_ ||
       branchName_leptonsFromTau_  != gInstance->branchName_leptonsFromTau_   )
    {
      throw cmsException(this)
        << "Association between configuration parameters 'branchName_nPromptLeptons', 'branchName_nLeptonsFromTau', "
           "'branchName_leptonsFromTau' and 'branchName_promptLeptons' must be unique:"
           " present association 'branchName_nPromptLeptons' = " << branchName_nPromptLeptons_ << ","
           " 'branchName_nLeptonsFromTau' = " << branchName_nLeptonsFromTau_ << ","
           " 'branchName_leptonsFromTau' = " << branchName_leptonsFromTau_
        << " with 'branchName_promptLeptons' = " << branchName_promptLeptons_
        << " does not match previous association 'branchName_nPromptLeptons' = " << gInstance->branchName_nPromptLeptons_ << ","
           " 'branchName_nLeptonsFromTau' = " << gInstance->branchName_nLeptonsFromTau_ << ","
           " 'branchName_leptonsFromTau' = " << gInstance->branchName_leptonsFromTau_
        << " with 'branchName_promptLeptons' = " << gInstance->branchName_promptLeptons_ << " !!\n";
    }
  }
  ++numInstances_[branchName_promptLeptons_];
}

void
GenLeptonReader::setBranchAddresses(TTree * tree)
{
  if(instances_[branchName_promptLeptons_] == this)
  {
    if(read_promptLeptons_)
    {
      std::cout << "setting branch addresses for PromptLeptons: " << branchName_promptLeptons_ << '\n';
      BranchAddressInitializer bai(tree, max_nPromptLeptons_);
      bai.setBranchAddress(nPromptLeptons_, branchName_nPromptLeptons_);
      bai.setBranchAddress(promptLepton_pt_, branchName_promptLepton_pt_);
      bai.setBranchAddress(promptLepton_eta_, branchName_promptLepton_eta_);
      bai.setBranchAddress(promptLepton_phi_, branchName_promptLepton_phi_);
      bai.setBranchAddress(promptLepton_mass_, branchName_promptLepton_mass_);
      bai.setBranchAddress(promptLepton_pdgId_, branchName_promptLepton_pdgId_);
    }

    if(read_leptonsFromTau_)
    {
      std::cout << "setting branch addresses for LeptonsFromTau\n";
      BranchAddressInitializer bai(tree, max_nLeptonsFromTau_);
      bai.setBranchAddress(nLeptonsFromTau_, branchName_nLeptonsFromTau_);
      bai.setBranchAddress(leptonFromTau_pt_, branchName_leptonFromTau_pt_);
      bai.setBranchAddress(leptonFromTau_eta_, branchName_leptonFromTau_eta_);
      bai.setBranchAddress(leptonFromTau_phi_, branchName_leptonFromTau_phi_);
      bai.setBranchAddress(leptonFromTau_mass_, branchName_leptonFromTau_mass_);
      bai.setBranchAddress(leptonFromTau_pdgId_, branchName_leptonFromTau_pdgId_);
    }
  }
}

std::vector<GenLepton>
GenLeptonReader::read() const
{
  const GenLeptonReader * const gInstance = instances_[branchName_promptLeptons_];
  assert(gInstance);

  UInt_t nPromptLeptons = 0;
  if(read_promptLeptons_)
  {
    nPromptLeptons = gInstance->nPromptLeptons_;
    if(nPromptLeptons > max_nPromptLeptons_)
    {
      throw cmsException(this)
        << "Number of prompt leptons stored in Ntuple = " << nPromptLeptons << ","
           " exceeds max_nPromptLeptons = " << max_nPromptLeptons_ << " !!\n";
    }
  }

  UInt_t nLeptonsFromTau = 0;
  if(read_leptonsFromTau_)
  {
    nLeptonsFromTau = gInstance->nLeptonsFromTau_;
    if(nLeptonsFromTau > max_nLeptonsFromTau_)
    {
      throw cmsException(this)
        << "Number of leptons from tau decays stored in Ntuple = " << nLeptonsFromTau << ","
           " exceeds max_nLeptonsFromTau = " << max_nLeptonsFromTau_ << " !!\n";
    }
  }

  std::vector<GenLepton> leptons;
  if((nPromptLeptons + nLeptonsFromTau) > 0)
  {
    leptons.reserve(nPromptLeptons + nLeptonsFromTau);
    for(UInt_t idxLepton = 0; idxLepton < nPromptLeptons; ++idxLepton)
    {
      leptons.push_back({
        gInstance->promptLepton_pt_[idxLepton],
        gInstance->promptLepton_eta_[idxLepton],
        gInstance->promptLepton_phi_[idxLepton],
        gInstance->promptLepton_mass_[idxLepton],
        gInstance->promptLepton_pdgId_[idxLepton]
      });
    }
    for(UInt_t idxLepton = 0; idxLepton < nLeptonsFromTau; ++idxLepton)
    {
      leptons.push_back({
        gInstance->leptonFromTau_pt_[idxLepton],
        gInstance->leptonFromTau_eta_[idxLepton],
        gInstance->leptonFromTau_phi_[idxLepton],
        gInstance->leptonFromTau_mass_[idxLepton],
        gInstance->leptonFromTau_pdgId_[idxLepton]
      });
    }
  }
  return leptons;
}
