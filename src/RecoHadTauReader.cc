#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTauReader.h" // RecoHadTauReader

#include "FWCore/Utilities/interface/Exception.h"

#include <TString.h> // Form

std::map<std::string, int> RecoHadTauReader::numInstances_;
std::map<std::string, RecoHadTauReader*> RecoHadTauReader::instances_;

RecoHadTauReader::RecoHadTauReader()
  : max_nHadTaus_(32)
  , branchName_num_("nTauGood")
  , branchName_obj_("TauGood")
  , hadTau_pt_(0)
  , hadTau_eta_(0)
  , hadTau_phi_(0)
  , hadTau_mass_(0)
  , hadTau_pdgId_(0)
  , hadTau_dz_(0)
  , hadTau_idDecayMode_(0)
  , hadTau_idMVA_dR03_(0)
  , hadTau_idMVA_dR05_(0)
  , hadTau_idCombIso_dR03_(0)
  , hadTau_idCombIso_dR05_(0)
  , hadTau_idAgainstElec_(0)
  , hadTau_idAgainstMu_(0)
{
  setBranchNames();
}

RecoHadTauReader::RecoHadTauReader(const std::string& branchName_num, const std::string& branchName_obj)
  : max_nHadTaus_(32)
  , branchName_num_(branchName_num)
  , branchName_obj_(branchName_obj)
  , hadTau_pt_(0)
  , hadTau_eta_(0)
  , hadTau_phi_(0)
  , hadTau_mass_(0)
  , hadTau_pdgId_(0)
  , hadTau_dz_(0)
  , hadTau_idDecayMode_(0)
  , hadTau_idMVA_dR03_(0)
  , hadTau_idMVA_dR05_(0)
  , hadTau_idCombIso_dR03_(0)
  , hadTau_idCombIso_dR05_(0)
  , hadTau_idAgainstElec_(0)
  , hadTau_idAgainstMu_(0)
{
  setBranchNames();
}

RecoHadTauReader::~RecoHadTauReader()
{
  --numInstances_[branchName_obj_];
  assert(numInstances_[branchName_obj_] >= 0);
  if ( numInstances_[branchName_obj_] == 0 ) {
    RecoHadTauReader* gInstance = instances_[branchName_obj_];
    assert(gInstance);
    delete gInstance->hadTau_pt_;
    delete gInstance->hadTau_eta_;
    delete gInstance->hadTau_phi_;
    delete gInstance->hadTau_mass_;
    delete gInstance->hadTau_dz_;
    delete gInstance->hadTau_idDecayMode_;
    delete gInstance->hadTau_idMVA_dR03_;
    delete gInstance->hadTau_idMVA_dR05_;
    delete gInstance->hadTau_idCombIso_dR03_;
    delete gInstance->hadTau_idCombIso_dR05_;
    delete gInstance->hadTau_idAgainstElec_;
    delete gInstance->hadTau_idAgainstMu_;
    delete gInstance->hadTau_pdgId_;
    instances_[branchName_obj_] = 0;
  }
}

void RecoHadTauReader::setBranchNames()
{
  if ( numInstances_[branchName_obj_] == 0 ) {
    branchName_pt_ = Form("%s_%s", branchName_obj_.data(), "pt");
    branchName_eta_ = Form("%s_%s", branchName_obj_.data(), "eta");
    branchName_phi_ = Form("%s_%s", branchName_obj_.data(), "phi");
    branchName_mass_ = Form("%s_%s", branchName_obj_.data(), "mass");
    branchName_pdgId_ = Form("%s_%s", branchName_obj_.data(), "pdgId");
    branchName_dz_ = Form("%s_%s", branchName_obj_.data(), "dz");
    branchName_idDecayMode_ = Form("%s_%s", branchName_obj_.data(), "idDecayMode");
    branchName_idMVA_dR03_ = Form("%s_%s", branchName_obj_.data(), "idMVArun2dR03");
    branchName_idMVA_dR05_ = Form("%s_%s", branchName_obj_.data(), "idMVArun2");
    branchName_idCombIso_dR03_ = Form("%s_%s", branchName_obj_.data(), "idCI3hit");
    branchName_idCombIso_dR05_ = Form("%s_%s", branchName_obj_.data(), "idCI3hitdR03");
    branchName_idAgainstElec_ = Form("%s_%s", branchName_obj_.data(), "idAntiErun2");
    branchName_idAgainstMu_ = Form("%s_%s", branchName_obj_.data(), "idAntiMu");
    instances_[branchName_obj_] = this;
  } else {
    if ( branchName_num_ != instances_[branchName_obj_]->branchName_num_ ) {
      throw cms::Exception("RecoHadTauReader") 
	<< "Association between configuration parameters 'branchName_num' and 'branchName_obj' must be unique:"
	<< " present association 'branchName_num' = " << branchName_num_ << " with 'branchName_obj' = " << branchName_obj_ 
	<< " does not match previous association 'branchName_num' = " << instances_[branchName_obj_]->branchName_num_ << " with 'branchName_obj' = " << instances_[branchName_obj_]->branchName_obj_ << " !!\n";
    }
  }
  ++numInstances_[branchName_obj_];
}

void RecoHadTauReader::setBranchAddresses(TTree* tree)
{
  if ( instances_[branchName_obj_] == this ) {
    tree->SetBranchAddress(branchName_num_.data(), &nHadTaus_);   
    hadTau_pt_ = new Double_t[max_nHadTaus_];
    tree->SetBranchAddress(branchName_pt_.data(), hadTau_pt_); 
    hadTau_eta_ = new Double_t[max_nHadTaus_];
    tree->SetBranchAddress(branchName_eta_.data(), hadTau_eta_); 
    hadTau_phi_ = new Double_t[max_nHadTaus_];
    tree->SetBranchAddress(branchName_phi_.data(), hadTau_phi_); 
    hadTau_mass_ = new Double_t[max_nHadTaus_];
    tree->SetBranchAddress(branchName_mass_.data(), hadTau_mass_); 
    hadTau_pdgId_ = new Int_t[max_nHadTaus_];
    tree->SetBranchAddress(branchName_pdgId_.data(), hadTau_pdgId_); 
    hadTau_dz_ = new Double_t[max_nHadTaus_];
    tree->SetBranchAddress(branchName_dz_.data(), hadTau_dz_); 
    hadTau_idDecayMode_ = new Int_t[max_nHadTaus_];
    tree->SetBranchAddress(branchName_idDecayMode_.data(), hadTau_idDecayMode_); 
    hadTau_idMVA_dR03_ = new Int_t[max_nHadTaus_];
    tree->SetBranchAddress(branchName_idMVA_dR03_.data(), hadTau_idMVA_dR03_); 
    hadTau_idMVA_dR05_ = new Int_t[max_nHadTaus_];
    tree->SetBranchAddress(branchName_idMVA_dR05_.data(), hadTau_idMVA_dR05_); 
    hadTau_idCombIso_dR03_ = new Int_t[max_nHadTaus_];
    tree->SetBranchAddress(branchName_idCombIso_dR03_.data(), hadTau_idCombIso_dR03_); 
    hadTau_idCombIso_dR05_ = new Int_t[max_nHadTaus_];
    tree->SetBranchAddress(branchName_idCombIso_dR05_.data(), hadTau_idCombIso_dR05_); 
    hadTau_idAgainstElec_ = new Int_t[max_nHadTaus_];
    tree->SetBranchAddress(branchName_idAgainstElec_.data(), hadTau_idAgainstElec_); 
    hadTau_idAgainstMu_ = new Int_t[max_nHadTaus_];
    tree->SetBranchAddress(branchName_idAgainstMu_.data(), hadTau_idAgainstMu_);
  }
}

std::vector<RecoHadTau> RecoHadTauReader::read() const
{
  RecoHadTauReader* gInstance = instances_[branchName_obj_];
  assert(gInstance);
  std::vector<RecoHadTau> hadTaus;
  Int_t nHadTaus = gInstance->nHadTaus_;
  if ( nHadTaus > max_nHadTaus_ ) {
    throw cms::Exception("RecoHadTauReader") 
      << "Number of hadronic taus stored in Ntuple = " << nHadTaus << ", exceeds max_nHadTaus = " << max_nHadTaus_ << " !!\n";
  }
  hadTaus.reserve(nHadTaus);
  for ( Int_t idxHadTau = 0; idxHadTau < nHadTaus; ++idxHadTau ) {
    hadTaus.push_back(RecoHadTau({ 
      gInstance->hadTau_pt_[idxHadTau],
      gInstance->hadTau_eta_[idxHadTau],
      gInstance->hadTau_phi_[idxHadTau],
      gInstance->hadTau_mass_[idxHadTau],
      gInstance->hadTau_pdgId_[idxHadTau],
      gInstance->hadTau_dz_[idxHadTau],
      gInstance->hadTau_idDecayMode_[idxHadTau],
      gInstance->hadTau_idMVA_dR03_[idxHadTau],
      gInstance->hadTau_idMVA_dR05_[idxHadTau],
      gInstance->hadTau_idCombIso_dR03_[idxHadTau],
      gInstance->hadTau_idCombIso_dR05_[idxHadTau],
      gInstance->hadTau_idAgainstElec_[idxHadTau],
      gInstance->hadTau_idAgainstMu_[idxHadTau] }));
  }
  return hadTaus;
}
