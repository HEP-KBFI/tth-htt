#include "tthAnalysis/HiggsToTauTau/interface/GenLeptonReader.h" // GenLeptonReader

#include "FWCore/Utilities/interface/Exception.h"

#include <TString.h> // Form

std::map<std::string, int> GenLeptonReader::numInstances_;
std::map<std::string, GenLeptonReader*> GenLeptonReader::instances_;

GenLeptonReader::GenLeptonReader()
  : max_nPromptLeptons_(32)
  , branchName_nPromptLeptons_("nGenLep")
  , branchName_promptLeptons_("GenLep")
  , max_nLeptonsFromTau_(32)
  , branchName_nLeptonsFromTau_("nGenLepFromTau")
  , branchName_leptonsFromTau_("GenLepFromTau")
  , promptLepton_pt_(0)
  , promptLepton_eta_(0)
  , promptLepton_phi_(0)
  , promptLepton_mass_(0)
  , promptLepton_pdgId_(0)
  , leptonFromTau_pt_(0)
  , leptonFromTau_eta_(0)
  , leptonFromTau_phi_(0)
  , leptonFromTau_mass_(0)
  , leptonFromTau_pdgId_(0)
{
  setBranchNames();
}

GenLeptonReader::GenLeptonReader(const std::string& branchName_nPromptLeptons, const std::string& branchName_promptLeptons,
				 const std::string& branchName_nLeptonsFromTau, const std::string& branchName_leptonsFromTau)
  : max_nPromptLeptons_(32)
  , branchName_nPromptLeptons_(branchName_nPromptLeptons)
  , branchName_promptLeptons_(branchName_promptLeptons)
  , max_nLeptonsFromTau_(32)
  , branchName_nLeptonsFromTau_(branchName_nLeptonsFromTau)
  , branchName_leptonsFromTau_(branchName_leptonsFromTau)			 
  , promptLepton_pt_(0)
  , promptLepton_eta_(0)
  , promptLepton_phi_(0)
  , promptLepton_mass_(0)
  , promptLepton_pdgId_(0)
  , leptonFromTau_pt_(0)
  , leptonFromTau_eta_(0)
  , leptonFromTau_phi_(0)
  , leptonFromTau_mass_(0)
  , leptonFromTau_pdgId_(0)
{
  setBranchNames();
}

GenLeptonReader::~GenLeptonReader()
{
  --numInstances_[branchName_promptLeptons_];
  assert(numInstances_[branchName_promptLeptons_] >= 0);
  if ( numInstances_[branchName_promptLeptons_] == 0 ) {
    GenLeptonReader* gInstance = instances_[branchName_promptLeptons_];
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
    instances_[branchName_promptLeptons_] = 0;
  }
}

void GenLeptonReader::setBranchNames()
{
  if ( numInstances_[branchName_promptLeptons_] == 0 ) {
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
  } else {
    GenLeptonReader* gInstance = instances_[branchName_promptLeptons_];
    assert(gInstance);
    if ( branchName_nPromptLeptons_  != gInstance->branchName_nPromptLeptons_  ||
	 branchName_nLeptonsFromTau_ != gInstance->branchName_nLeptonsFromTau_ ||
	 branchName_leptonsFromTau_  != gInstance->branchName_leptonsFromTau_  ) {
      throw cms::Exception("GenLeptonReader") 
	<< "Association between configuration parameters 'branchName_nPromptLeptons', 'branchName_nLeptonsFromTau', 'branchName_leptonsFromTau' and 'branchName_promptLeptons' must be unique:"
	<< " present association 'branchName_nPromptLeptons' = " << branchName_nPromptLeptons_ << "," 
	<< " 'branchName_nLeptonsFromTau' = " << branchName_nLeptonsFromTau_ << "," 
	<< " 'branchName_leptonsFromTau' = " << branchName_leptonsFromTau_ 
	<< " with 'branchName_promptLeptons' = " << branchName_promptLeptons_ 
	<< " does not match previous association 'branchName_nPromptLeptons' = " << gInstance->branchName_nPromptLeptons_ << "," 
	<< " 'branchName_nLeptonsFromTau' = " << gInstance->branchName_nLeptonsFromTau_ << "," 
	<< " 'branchName_leptonsFromTau' = " << gInstance->branchName_leptonsFromTau_ 
	<< " with 'branchName_promptLeptons' = " << gInstance->branchName_promptLeptons_ << " !!\n";
    }
  }
  ++numInstances_[branchName_promptLeptons_];
}

void GenLeptonReader::setBranchAddresses(TTree* tree)
{
  if ( instances_[branchName_promptLeptons_] == this ) {
    tree->SetBranchAddress(branchName_nPromptLeptons_.data(), &nPromptLeptons_);   
    promptLepton_pt_ = new Float_t[max_nPromptLeptons_];
    tree->SetBranchAddress(branchName_promptLepton_pt_.data(), promptLepton_pt_); 
    promptLepton_eta_ = new Float_t[max_nPromptLeptons_];
    tree->SetBranchAddress(branchName_promptLepton_eta_.data(), promptLepton_eta_); 
    promptLepton_phi_ = new Float_t[max_nPromptLeptons_];
    tree->SetBranchAddress(branchName_promptLepton_phi_.data(), promptLepton_phi_); 
    promptLepton_mass_ = new Float_t[max_nPromptLeptons_];
    tree->SetBranchAddress(branchName_promptLepton_mass_.data(), promptLepton_mass_); 
    promptLepton_pdgId_ = new Int_t[max_nPromptLeptons_];
    tree->SetBranchAddress(branchName_promptLepton_pdgId_.data(), promptLepton_pdgId_); 
    tree->SetBranchAddress(branchName_nLeptonsFromTau_.data(), &nLeptonsFromTau_);   
    leptonFromTau_pt_ = new Float_t[max_nLeptonsFromTau_];
    tree->SetBranchAddress(branchName_leptonFromTau_pt_.data(), leptonFromTau_pt_); 
    leptonFromTau_eta_ = new Float_t[max_nLeptonsFromTau_];
    tree->SetBranchAddress(branchName_leptonFromTau_eta_.data(), leptonFromTau_eta_); 
    leptonFromTau_phi_ = new Float_t[max_nLeptonsFromTau_];
    tree->SetBranchAddress(branchName_leptonFromTau_phi_.data(), leptonFromTau_phi_); 
    leptonFromTau_mass_ = new Float_t[max_nLeptonsFromTau_];
    tree->SetBranchAddress(branchName_leptonFromTau_mass_.data(), leptonFromTau_mass_); 
    leptonFromTau_pdgId_ = new Int_t[max_nLeptonsFromTau_];
    tree->SetBranchAddress(branchName_leptonFromTau_pdgId_.data(), leptonFromTau_pdgId_); 
  }
}

std::vector<GenLepton> GenLeptonReader::read() const
{
  GenLeptonReader* gInstance = instances_[branchName_promptLeptons_];
  assert(gInstance);
  Int_t nPromptLeptons = gInstance->nPromptLeptons_;
  if ( nPromptLeptons > max_nPromptLeptons_ ) {
    throw cms::Exception("GenLeptonReader") 
      << "Number of prompt leptons stored in Ntuple = " << nPromptLeptons << "," 
      << " exceeds max_nPromptLeptons = " << max_nPromptLeptons_ << " !!\n";
  }
  Int_t nLeptonsFromTau = gInstance->nLeptonsFromTau_;
  if ( nLeptonsFromTau > max_nLeptonsFromTau_ ) {
    throw cms::Exception("GenLeptonReader") 
      << "Number of leptons from tau decays stored in Ntuple = " << nLeptonsFromTau << "," 
      << " exceeds max_nLeptonsFromTau = " << max_nLeptonsFromTau_ << " !!\n";
  }
  std::vector<GenLepton> leptons;
  leptons.reserve(nPromptLeptons + nLeptonsFromTau);
  for ( Int_t idxLepton = 0; idxLepton < nPromptLeptons; ++idxLepton ) {
    leptons.push_back(GenLepton({ 
      gInstance->promptLepton_pt_[idxLepton],
      gInstance->promptLepton_eta_[idxLepton],
      gInstance->promptLepton_phi_[idxLepton],
      gInstance->promptLepton_mass_[idxLepton],
      gInstance->promptLepton_pdgId_[idxLepton] }));
  }
  for ( Int_t idxLepton = 0; idxLepton < nLeptonsFromTau; ++idxLepton ) {
    leptons.push_back(GenLepton({ 
      gInstance->leptonFromTau_pt_[idxLepton],
      gInstance->leptonFromTau_eta_[idxLepton],
      gInstance->leptonFromTau_phi_[idxLepton],
      gInstance->leptonFromTau_mass_[idxLepton],
      gInstance->leptonFromTau_pdgId_[idxLepton] }));
  }  
  return leptons;
}
