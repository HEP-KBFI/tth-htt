#include "tthAnalysis/HiggsToTauTau/interface/RecoLeptonWriter.h" // RecoLeptonWriter

#include "FWCore/Utilities/interface/Exception.h"

#include "tthAnalysis/HiggsToTauTau/interface/writerAuxFunctions.h" // setBranchI, setBranchVI, setBranchVF

#include <TString.h> // Form

RecoLeptonWriter::RecoLeptonWriter(const std::string& branchName_num, const std::string& branchName_obj)
  : max_nLeptons_(32)
  , branchName_num_(branchName_num)
  , branchName_obj_(branchName_obj)
  , genLeptonWriter_(0)
  , genHadTauWriter_(0)
  , genJetWriter_(0)
  , pt_(0)
  , eta_(0)
  , phi_(0)
  , mass_(0)
  , pdgId_(0)
  , dxy_(0)
  , dz_(0)
  , relIso_(0)
  , chargedHadRelIso03_(0)
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
  genLeptonWriter_ = new GenParticleWriter(Form("%s_genLepton", branchName_num_.data()), Form("%s_genLepton", branchName_obj_.data()));
  genHadTauWriter_ = new GenParticleWriter(Form("%s_genHadTau", branchName_num_.data()), Form("%s_genHadTau", branchName_obj_.data()));
  genJetWriter_ = new GenParticleWriter(Form("%s_genJet", branchName_num_.data()), Form("%s_genJet", branchName_obj_.data()));
  setBranchNames();
}

RecoLeptonWriter::~RecoLeptonWriter()
{
  delete genLeptonWriter_;
  delete genHadTauWriter_;
  delete genJetWriter_;
  delete pt_;
  delete eta_;
  delete phi_;
  delete mass_;
  delete pdgId_;
  delete dxy_;
  delete dz_;
  delete relIso_;
  delete chargedHadRelIso03_;
  delete miniIsoCharged_;
  delete miniIsoNeutral_;
  delete sip3d_;
  delete mvaRawTTH_;
  delete jetNDauChargedMVASel_;
  delete jetPtRel_;
  delete jetPtRatio_;
  delete jetBtagCSV_;
  delete tightCharge_;
  delete charge_;
}

void RecoLeptonWriter::setBranchNames()
{
  branchName_pt_ = Form("%s_%s", branchName_obj_.data(), "pt");
  branchName_eta_ = Form("%s_%s", branchName_obj_.data(), "eta");
  branchName_phi_ = Form("%s_%s", branchName_obj_.data(), "phi");
  branchName_mass_ = Form("%s_%s", branchName_obj_.data(), "mass");
  branchName_pdgId_ = Form("%s_%s", branchName_obj_.data(), "pdgId");
  branchName_dxy_ = Form("%s_%s", branchName_obj_.data(), "dxy");
  branchName_dz_ = Form("%s_%s", branchName_obj_.data(), "dz");
  branchName_relIso_ = Form("%s_%s", branchName_obj_.data(), "miniRelIso");
  branchName_chargedHadRelIso03_ = Form("%s_%s", branchName_obj_.data(), "chargedHadRelIso03");
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
}

void RecoLeptonWriter::setBranches(TTree *tree)
{
  genLeptonWriter_->setBranches(tree);
  genHadTauWriter_->setBranches(tree);
  genJetWriter_->setBranches(tree);
  setBranchI(tree, branchName_num_, &nLeptons_);
  pt_ = new Float_t[max_nLeptons_];
  setBranchVF(tree, branchName_pt_, branchName_num_, pt_);
  eta_ = new Float_t[max_nLeptons_];
  setBranchVF(tree, branchName_eta_, branchName_num_, eta_);
  phi_ = new Float_t[max_nLeptons_];
  setBranchVF(tree, branchName_phi_, branchName_num_, phi_);
  mass_ = new Float_t[max_nLeptons_];
  setBranchVF(tree, branchName_mass_, branchName_num_, mass_);
  pdgId_ = new Int_t[max_nLeptons_];
  setBranchVI(tree, branchName_pdgId_, branchName_num_, pdgId_);
  dxy_ = new Float_t[max_nLeptons_];
  setBranchVF(tree, branchName_dxy_, branchName_num_, dxy_);
  dz_ = new Float_t[max_nLeptons_];
  setBranchVF(tree, branchName_dz_, branchName_num_, dz_);
  relIso_ = new Float_t[max_nLeptons_];
  setBranchVF(tree, branchName_relIso_, branchName_num_, relIso_);
  chargedHadRelIso03_ = new Float_t[max_nLeptons_];
  setBranchVF(tree, branchName_chargedHadRelIso03_, branchName_num_, chargedHadRelIso03_);
  miniIsoCharged_ = new Float_t[max_nLeptons_];
  setBranchVF(tree, branchName_miniIsoCharged_, branchName_num_, miniIsoCharged_);
  miniIsoNeutral_ = new Float_t[max_nLeptons_];
  setBranchVF(tree, branchName_miniIsoNeutral_, branchName_num_, miniIsoNeutral_);
  sip3d_ = new Float_t[max_nLeptons_];
  setBranchVF(tree, branchName_sip3d_, branchName_num_, sip3d_);
  mvaRawTTH_ = new Float_t[max_nLeptons_];
  setBranchVF(tree, branchName_mvaRawTTH_, branchName_num_, mvaRawTTH_);
  jetNDauChargedMVASel_ = new Float_t[max_nLeptons_];
  setBranchVF(tree, branchName_jetNDauChargedMVASel_, branchName_num_, jetNDauChargedMVASel_);
  jetPtRel_ = new Float_t[max_nLeptons_];
  setBranchVF(tree, branchName_jetPtRel_, branchName_num_, jetPtRel_);
  jetPtRatio_ = new Float_t[max_nLeptons_];
  setBranchVF(tree, branchName_jetPtRatio_, branchName_num_, jetPtRatio_);
  jetBtagCSV_ = new Float_t[max_nLeptons_];
  setBranchVF(tree, branchName_jetBtagCSV_, branchName_num_, jetBtagCSV_);
  tightCharge_ = new Int_t[max_nLeptons_];
  setBranchVI(tree, branchName_tightCharge_, branchName_num_, tightCharge_);
  charge_ = new Int_t[max_nLeptons_];
  setBranchVI(tree, branchName_charge_, branchName_num_, charge_);
}

