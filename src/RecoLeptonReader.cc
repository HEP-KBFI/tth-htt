#include "tthAnalysis/HiggsToTauTau/interface/RecoLeptonReader.h" // RecoLeptonReader

#include "FWCore/Utilities/interface/Exception.h"

#include <TString.h> // Form

std::map<std::string, int> RecoLeptonReader::numInstances_;
std::map<std::string, RecoLeptonReader*> RecoLeptonReader::instances_;

RecoLeptonReader::RecoLeptonReader()
  : max_nLeptons_(32)
  , branchName_num_("nselLeptons")
  , branchName_obj_("selLeptons")
  , pt_(0)
  , eta_(0)
  , phi_(0)
  , mass_(0)
  , pdgId_(0)  
  , dxy_(0)
  , dz_(0)
  , relIso_(0)
  , miniIsoCharged_(0)
  , miniIsoNeutral_(0)
  , sip3d_(0)
  , mvaRawTTH_(0)
  , jetNDauChargedMVASel_(0)
  , jetPtRel_(0)
  , jetPtRatio_(0)
  , jetBtagCSV_(0)  
  , tightCharge_(0)
  , charge_(0)
{
  setBranchNames();
}

RecoLeptonReader::RecoLeptonReader(const std::string& branchName_num, const std::string& branchName_obj)
  : max_nLeptons_(32)
  , branchName_num_(branchName_num)
  , branchName_obj_(branchName_obj)
  , pt_(0)
  , eta_(0)
  , phi_(0)
  , mass_(0)
  , pdgId_(0)  
  , dxy_(0)
  , dz_(0)
  , relIso_(0)
  , miniIsoCharged_(0)
  , miniIsoNeutral_(0)
  , sip3d_(0)
  , mvaRawTTH_(0)
  , jetNDauChargedMVASel_(0)
  , jetPtRel_(0)
  , jetPtRatio_(0)
  , jetBtagCSV_(0)
  , tightCharge_(0)
  , charge_(0)
{
  setBranchNames();
}

RecoLeptonReader::~RecoLeptonReader()
{
  --numInstances_[branchName_obj_];
  assert(numInstances_[branchName_obj_] >= 0);
  if ( numInstances_[branchName_obj_] == 0 ) {
    RecoLeptonReader* gInstance = instances_[branchName_obj_];
    assert(gInstance);
    delete gInstance->pt_;
    delete gInstance->eta_;
    delete gInstance->phi_;
    delete gInstance->mass_;
    delete gInstance->pdgId_;
    delete gInstance->dxy_;
    delete gInstance->dz_;
    delete gInstance->relIso_;
    delete gInstance->miniIsoCharged_;
    delete gInstance->miniIsoNeutral_;
    delete gInstance->sip3d_;
    delete gInstance->mvaRawTTH_;
    delete gInstance->jetNDauChargedMVASel_;
    delete gInstance->jetPtRel_;
    delete gInstance->jetPtRatio_;
    delete gInstance->jetBtagCSV_;
    delete gInstance->tightCharge_;
    delete gInstance->charge_;
    instances_[branchName_obj_] = 0;
  }
}

void RecoLeptonReader::setBranchNames()
{
  if ( numInstances_[branchName_obj_] == 0 ) {
    branchName_pt_ = Form("%s_%s", branchName_obj_.data(), "pt");
    branchName_eta_ = Form("%s_%s", branchName_obj_.data(), "eta");
    branchName_phi_ = Form("%s_%s", branchName_obj_.data(), "phi");
    branchName_mass_ = Form("%s_%s", branchName_obj_.data(), "mass");
    branchName_pdgId_ = Form("%s_%s", branchName_obj_.data(), "pdgId");
    branchName_dxy_ = Form("%s_%s", branchName_obj_.data(), "dxy");
    branchName_dz_ = Form("%s_%s", branchName_obj_.data(), "dz");
    branchName_relIso_ = Form("%s_%s", branchName_obj_.data(), "miniRelIso");
    branchName_miniIsoCharged_ = Form("%s_%s", branchName_obj_.data(), "miniIsoCharged");
    branchName_miniIsoNeutral_ = Form("%s_%s", branchName_obj_.data(), "miniIsoNeutral");
    branchName_sip3d_ = Form("%s_%s", branchName_obj_.data(), "sip3d");
    branchName_mvaRawTTH_ = Form("%s_%s", branchName_obj_.data(), "mvaTTH");
    branchName_jetNDauChargedMVASel_ = Form("%s_%s", branchName_obj_.data(), "mvaTTHjetNDauChargedMVASel");
    branchName_jetPtRel_ = Form("%s_%s", branchName_obj_.data(), "mvaTTHjetPtRel");
    branchName_jetPtRatio_ = Form("%s_%s", branchName_obj_.data(), "jetPtRatio");
    branchName_jetBtagCSV_ = Form("%s_%s", branchName_obj_.data(), "jetBTagCSV");
    branchName_tightCharge_ = Form("%s_%s", branchName_obj_.data(), "tightCharge");
    branchName_charge_ = Form("%s_%s", branchName_obj_.data(), "charge");
    instances_[branchName_obj_] = this;
  } else {
    if ( branchName_num_ != instances_[branchName_obj_]->branchName_num_ ) {
      throw cms::Exception("RecoLeptonReader") 
	<< "Association between configuration parameters 'branchName_num' and 'branchName_obj' must be unique:"
	<< " present association 'branchName_num' = " << branchName_num_ << " with 'branchName_obj' = " << branchName_obj_ 
	<< " does not match previous association 'branchName_num' = " << instances_[branchName_obj_]->branchName_num_ << " with 'branchName_obj' = " << instances_[branchName_obj_]->branchName_obj_ << " !!\n";
    }
  }
  ++numInstances_[branchName_obj_];
}

void RecoLeptonReader::setBranchAddresses(TTree* tree)
{
  if ( instances_[branchName_obj_] == this ) {
    //std::cout << "<RecoLeptonReader::setBranchAddresses>:" << std::endl;
    //std::cout << " branchName_num = " << branchName_num_ << std::endl;
    //std::cout << " branchName_obj = " << branchName_obj_ << std::endl;
    tree->SetBranchAddress(branchName_num_.data(), &nLeptons_);   
    pt_ = new Float_t[max_nLeptons_];
    tree->SetBranchAddress(branchName_pt_.data(), pt_); 
    eta_ = new Float_t[max_nLeptons_];
    tree->SetBranchAddress(branchName_eta_.data(), eta_); 
    phi_ = new Float_t[max_nLeptons_];
    tree->SetBranchAddress(branchName_phi_.data(), phi_); 
    mass_ = new Float_t[max_nLeptons_];
    tree->SetBranchAddress(branchName_mass_.data(), mass_); 
    pdgId_ = new Int_t[max_nLeptons_];
    tree->SetBranchAddress(branchName_pdgId_.data(), pdgId_); 
    dxy_ = new Float_t[max_nLeptons_];
    tree->SetBranchAddress(branchName_dxy_.data(), dxy_); 
    dz_ = new Float_t[max_nLeptons_];
    tree->SetBranchAddress(branchName_dz_.data(), dz_); 
    relIso_ = new Float_t[max_nLeptons_];
    tree->SetBranchAddress(branchName_relIso_.data(), relIso_);
    miniIsoCharged_ = new Float_t[max_nLeptons_];
    tree->SetBranchAddress(branchName_miniIsoCharged_.data(), miniIsoCharged_);
    miniIsoNeutral_ = new Float_t[max_nLeptons_];
    tree->SetBranchAddress(branchName_miniIsoNeutral_.data(), miniIsoNeutral_);
    sip3d_ = new Float_t[max_nLeptons_];
    tree->SetBranchAddress(branchName_sip3d_.data(), sip3d_); 
    mvaRawTTH_ = new Float_t[max_nLeptons_];
    tree->SetBranchAddress(branchName_mvaRawTTH_.data(), mvaRawTTH_); 
    jetNDauChargedMVASel_ = new Float_t[max_nLeptons_];
    tree->SetBranchAddress(branchName_jetNDauChargedMVASel_.data(), jetNDauChargedMVASel_);
    jetPtRel_ = new Float_t[max_nLeptons_];
    tree->SetBranchAddress(branchName_jetPtRel_.data(), jetPtRel_);
    jetPtRatio_ = new Float_t[max_nLeptons_];
    tree->SetBranchAddress(branchName_jetPtRatio_.data(), jetPtRatio_);
    jetBtagCSV_ = new Float_t[max_nLeptons_];
    tree->SetBranchAddress(branchName_jetBtagCSV_.data(), jetBtagCSV_);
    tightCharge_ = new Int_t[max_nLeptons_];
    tree->SetBranchAddress(branchName_tightCharge_.data(), tightCharge_);
    charge_ = new Int_t[max_nLeptons_];
    tree->SetBranchAddress(branchName_charge_.data(), charge_);
  }
}
