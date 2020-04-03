#include "tthAnalysis/HiggsToTauTau/interface/RecoLeptonWriter.h" // RecoLeptonWriter

#include "tthAnalysis/HiggsToTauTau/interface/BranchAddressInitializer.h" // BranchAddressInitializer, TTree, Form()
#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // Btag

RecoLeptonWriter::RecoLeptonWriter(bool isMC,
                                   const std::string & branchName_obj)
  : RecoLeptonWriter(isMC, Form("n%s", branchName_obj.data()), branchName_obj)
{}

RecoLeptonWriter::RecoLeptonWriter(bool isMC,
                                   const std::string & branchName_num,
                                   const std::string & branchName_obj)
  : max_nLeptons_(64)
  , branchName_num_(branchName_num)
  , branchName_obj_(branchName_obj)
  , isMC_(isMC)
  , genLeptonWriter_(nullptr)
  , genHadTauWriter_(nullptr)
  , genPhotonWriter_(nullptr)
  , genJetWriter_(nullptr)
  , nLeptons_(0)
  , pt_(nullptr)
  , eta_(nullptr)
  , phi_(nullptr)
  , mass_(nullptr)
  , pdgId_(nullptr)
  , dxy_(nullptr)
  , dz_(nullptr)
  , relIso_all_(nullptr)
  , pfRelIso04_all_(nullptr)
  , relIso_chg_(nullptr)
  , relIso_neu_(nullptr)
  , sip3d_(nullptr)
  , mvaRawTTH_(nullptr)
  , jetPtRatio_(nullptr)
  , jetPtRel_(nullptr)
  , jetNDauChargedMVASel_(nullptr)
  , tightCharge_(nullptr)
  , charge_(nullptr)
  , filterBits_(nullptr)
  , jetIdx_(nullptr)
  , genPartFlav_(nullptr)
  , genMatchIdx_(nullptr)
{
  if(isMC_)
  {
    genLeptonWriter_ = new GenParticleWriter(Form("%s_genLepton", branchName_obj_.data()), max_nLeptons_);
    genHadTauWriter_ = new GenParticleWriter(Form("%s_genTau",    branchName_obj_.data()), max_nLeptons_);
    genPhotonWriter_ = new GenParticleWriter(Form("%s_genPhoton", branchName_obj_.data()), max_nLeptons_);
    genJetWriter_    = new GenParticleWriter(Form("%s_genJet",    branchName_obj_.data()), max_nLeptons_);
  }
  setBranchNames();
}

RecoLeptonWriter::~RecoLeptonWriter()
{
  delete genLeptonWriter_;
  delete genHadTauWriter_;
  delete genPhotonWriter_;
  delete genJetWriter_;
  delete[] pt_;
  delete[] eta_;
  delete[] phi_;
  delete[] mass_;
  delete[] pdgId_;
  delete[] dxy_;
  delete[] dz_;
  delete[] relIso_all_;
  delete[] pfRelIso04_all_;
  delete[] relIso_chg_;
  delete[] relIso_neu_;
  delete[] sip3d_;
  delete[] mvaRawTTH_;
  delete[] jetPtRatio_;
  delete[] jetPtRel_;
  delete[] jetNDauChargedMVASel_;
  delete[] tightCharge_;
  delete[] charge_;
  delete[] filterBits_;
  delete[] jetIdx_;
  delete[] genPartFlav_;
  delete[] genMatchIdx_;

  for(auto & kv: jetBtagCSVs_)
  {
    delete[] kv.second;
  }
  for(auto & kv: assocJetBtagCSVs_)
  {
    delete[] kv.second;
  }
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
  branchName_relIso_all_ = Form("%s_%s", branchName_obj_.data(), "miniPFRelIso_all");
  branchName_pfRelIso04_all_ = Form("%s_%s", branchName_obj_.data(), "pfRelIso04_all");
  branchName_relIso_chg_ = Form("%s_%s", branchName_obj_.data(), "miniPFRelIso_chg");
  branchName_relIso_neu_ = Form("%s_%s", branchName_obj_.data(), "miniPFRelIso_neu");
  branchName_sip3d_ = Form("%s_%s", branchName_obj_.data(), "sip3d");
  branchName_mvaRawTTH_ = Form("%s_%s", branchName_obj_.data(), "mvaTTH");
  branchName_jetPtRatio_ = Form("%s_%s", branchName_obj_.data(), "jetPtRatio");
  branchName_jetPtRel_ = Form("%s_%s", branchName_obj_.data(), "jetPtRelv2");
  for(Btag btag: { Btag::kCSVv2, Btag::kDeepCSV, Btag::kDeepJet })
  {
    std::string btag_str = "";
    switch(btag)
    {
      case Btag::kCSVv2:   btag_str = "CSV"; break;
      case Btag::kDeepCSV: btag_str = "DeepCSV"; break;
      case Btag::kDeepJet: btag_str = "DeepJet"; break;
    }
    branchNames_jetBtagCSV_[btag] = Form("%s_jetBTag%s", branchName_obj_.data(), btag_str.data());
    branchNames_assocJetBtagCSV_[btag] = Form("%s_assocJetBtag_%s", branchName_obj_.data(), btag_str.data());
  }
  branchName_jetNDauChargedMVASel_ = Form("%s_%s", branchName_obj_.data(), "jetNDauChargedMVASel");
  branchName_tightCharge_ = Form("%s_%s", branchName_obj_.data(), "tightCharge");
  branchName_charge_ = Form("%s_%s", branchName_obj_.data(), "charge");
  branchName_filterBits_ = Form("%s_%s", branchName_obj_.data(), "filterBits");
  branchName_jetIdx_ = Form("%s_%s", branchName_obj_.data(), "jetIdx");
  branchName_genPartFlav_ = Form("%s_%s", branchName_obj_.data(), "genPartFlav");
  branchName_genMatchIdx_ = Form("%s_%s", branchName_obj_.data(), "genMatchIdx");
}

void RecoLeptonWriter::setBranches(TTree * tree)
{
  if(isMC_)
  {
    genLeptonWriter_->setBranches(tree);
    genHadTauWriter_->setBranches(tree);
    genPhotonWriter_->setBranches(tree);
    genJetWriter_->setBranches(tree);
  }
  BranchAddressInitializer bai(tree, max_nLeptons_, branchName_num_);
  bai.setBranch(nLeptons_, branchName_num_);
  bai.setBranch(pt_, branchName_pt_);
  bai.setBranch(eta_, branchName_eta_);
  bai.setBranch(phi_, branchName_phi_);
  bai.setBranch(mass_, branchName_mass_);
  bai.setBranch(pdgId_, branchName_pdgId_);
  bai.setBranch(dxy_, branchName_dxy_);
  bai.setBranch(dz_, branchName_dz_);
  bai.setBranch(relIso_all_, branchName_relIso_all_);
  bai.setBranch(pfRelIso04_all_, branchName_pfRelIso04_all_);
  bai.setBranch(relIso_chg_, branchName_relIso_chg_);
  bai.setBranch(relIso_neu_, branchName_relIso_neu_);
  bai.setBranch(sip3d_, branchName_sip3d_);
  bai.setBranch(mvaRawTTH_, branchName_mvaRawTTH_);
  bai.setBranch(jetPtRatio_, branchName_jetPtRatio_);
  bai.setBranch(jetPtRel_, branchName_jetPtRel_);
  for(const auto & kv: branchNames_jetBtagCSV_)
  {
    bai.setBranch(jetBtagCSVs_[kv.first], kv.second);
  }
  for(const auto & kv: branchNames_assocJetBtagCSV_)
  {
    bai.setBranch(assocJetBtagCSVs_[kv.first], kv.second);
  }
  bai.setBranch(jetNDauChargedMVASel_, branchName_jetNDauChargedMVASel_);
  bai.setBranch(tightCharge_, branchName_tightCharge_);
  bai.setBranch(charge_, branchName_charge_);
  bai.setBranch(filterBits_, branchName_filterBits_);
  bai.setBranch(jetIdx_, branchName_jetIdx_);
  if(isMC_)
  {
    bai.setBranch(genPartFlav_, branchName_genPartFlav_);
    bai.setBranch(genMatchIdx_, branchName_genMatchIdx_);
  }
}
