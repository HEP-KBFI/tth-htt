#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTauWriter.h" // RecoHadTauWriter

#include "FWCore/Utilities/interface/Exception.h"

#include "tthAnalysis/HiggsToTauTau/interface/LocalFileInPath.h" // LocalFileInPath
#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // kEra_2015, kEra_2016
#include "tthAnalysis/HiggsToTauTau/interface/writerAuxFunctions.h" // setBranchI, setBranchVI, setBranchVF

#include <TString.h> // Form

RecoHadTauWriter::RecoHadTauWriter(int era)
  : era_(era)
  , max_nHadTaus_(32)
  , branchName_num_("nTaus")
  , branchName_obj_("Taus")
  , genLeptonWriter_(0)
  , genHadTauWriter_(0)
  , genJetWriter_(0)
  , hadTau_pt_(0)
  , hadTau_eta_(0)
  , hadTau_phi_(0)
  , hadTau_mass_(0)
  , hadTau_charge_(0)
  , hadTau_dxy_(0)
  , hadTau_dz_(0)
  , hadTau_decayMode_(0)
  , hadTau_idDecayMode_(0)
  , hadTau_idDecayModeNewDMs_(0)
  , hadTau_idMVA_dR03_(0)
  , hadTau_rawMVA_dR03_(0)
  , hadTau_idMVA_dR05_(0)
  , hadTau_rawMVA_dR05_(0)
  , hadTau_idCombIso_dR03_(0)
  , hadTau_rawCombIso_dR03_(0)
  , hadTau_idCombIso_dR05_(0)
  , hadTau_rawCombIso_dR05_(0)    
  , hadTau_idAgainstElec_(0)
  , hadTau_idAgainstMu_(0)
{
  genLeptonWriter_ = new GenParticleWriter(Form("%s_genLepton", branchName_num_.data()), Form("%s_genLepton", branchName_obj_.data()));
  genHadTauWriter_ = new GenParticleWriter(Form("%s_genHadTau", branchName_num_.data()), Form("%s_genHadTau", branchName_obj_.data()));
  genJetWriter_ = new GenParticleWriter(Form("%s_genJet", branchName_num_.data()), Form("%s_genJet", branchName_obj_.data()));
  setBranchNames();
}

RecoHadTauWriter::RecoHadTauWriter(int era, const std::string& branchName_num, const std::string& branchName_obj)
  : era_(era)
  , max_nHadTaus_(32)
  , branchName_num_(branchName_num)
  , branchName_obj_(branchName_obj)
  , genLeptonWriter_(0)
  , genHadTauWriter_(0)
  , genJetWriter_(0)
  , hadTau_pt_(0)
  , hadTau_eta_(0)
  , hadTau_phi_(0)
  , hadTau_mass_(0)
  , hadTau_charge_(0)
  , hadTau_dxy_(0)
  , hadTau_dz_(0)
  , hadTau_decayMode_(0)
  , hadTau_idDecayMode_(0)
  , hadTau_idDecayModeNewDMs_(0)
  , hadTau_idMVA_dR03_(0)
  , hadTau_rawMVA_dR03_(0)
  , hadTau_idMVA_dR05_(0)
  , hadTau_rawMVA_dR05_(0)
  , hadTau_idCombIso_dR03_(0)
  , hadTau_rawCombIso_dR03_(0)
  , hadTau_idCombIso_dR05_(0)
  , hadTau_rawCombIso_dR05_(0)   
  , hadTau_idAgainstElec_(0)
  , hadTau_idAgainstMu_(0)
{
  genLeptonWriter_ = new GenParticleWriter(Form("%s_genLepton", branchName_num_.data()), Form("%s_genLepton", branchName_obj_.data()));
  genHadTauWriter_ = new GenParticleWriter(Form("%s_genHadTau", branchName_num_.data()), Form("%s_genHadTau", branchName_obj_.data()));
  genJetWriter_ = new GenParticleWriter(Form("%s_genJet", branchName_num_.data()), Form("%s_genJet", branchName_obj_.data()));
  setBranchNames();
}

RecoHadTauWriter::~RecoHadTauWriter()
{
  delete genLeptonWriter_;
  delete genHadTauWriter_;
  delete genJetWriter_;
  delete[] hadTau_pt_;
  delete[] hadTau_eta_;
  delete[] hadTau_phi_;
  delete[] hadTau_mass_;
  delete[] hadTau_dxy_;
  delete[] hadTau_dz_;
  delete[] hadTau_decayMode_;
  delete[] hadTau_idDecayMode_;
  delete[] hadTau_idDecayModeNewDMs_;
  delete[] hadTau_idMVA_dR03_;
  delete[] hadTau_rawMVA_dR03_;
  delete[] hadTau_idMVA_dR05_;
  delete[] hadTau_rawMVA_dR05_;
  delete[] hadTau_idCombIso_dR03_;
  delete[] hadTau_rawCombIso_dR03_;
  delete[] hadTau_idCombIso_dR05_;
  delete[] hadTau_rawCombIso_dR05_;
  delete[] hadTau_idAgainstElec_;
  delete[] hadTau_idAgainstMu_;
  delete[] hadTau_charge_;
}

void RecoHadTauWriter::setBranchNames()
{
  branchName_pt_ = Form("%s_%s", branchName_obj_.data(), "pt");
  branchName_eta_ = Form("%s_%s", branchName_obj_.data(), "eta");
  branchName_phi_ = Form("%s_%s", branchName_obj_.data(), "phi");
  branchName_mass_ = Form("%s_%s", branchName_obj_.data(), "mass");
  branchName_charge_ = Form("%s_%s", branchName_obj_.data(), "charge");
  branchName_dxy_ = Form("%s_%s", branchName_obj_.data(), "dxy");
  branchName_dz_ = Form("%s_%s", branchName_obj_.data(), "dz");
  branchName_decayMode_ = Form("%s_%s", branchName_obj_.data(), "decayMode");
  branchName_idDecayMode_ = Form("%s_%s", branchName_obj_.data(), "idDecayMode");
  branchName_idDecayModeNewDMs_ = Form("%s_%s", branchName_obj_.data(), "idDecayModeNewDMs");
  branchName_idMVA_dR03_ = Form("%s_%s", branchName_obj_.data(), "idMVAoldDMdR03");
  branchName_rawMVA_dR03_ = Form("%s_%s", branchName_obj_.data(), "rawMVAoldDMdR03");
  branchName_idMVA_dR05_ = Form("%s_%s", branchName_obj_.data(), "idMVAoldDM");
  branchName_rawMVA_dR05_ = Form("%s_%s", branchName_obj_.data(), "rawMVAoldDM");
  branchName_idCombIso_dR03_ = Form("%s_%s", branchName_obj_.data(), "idCI3hitdR03");
  branchName_rawCombIso_dR03_ = Form("%s_%s", branchName_obj_.data(), "isoCI3hitdR03");
  branchName_idCombIso_dR05_ = Form("%s_%s", branchName_obj_.data(), "idCI3hit");
  branchName_rawCombIso_dR05_ = Form("%s_%s", branchName_obj_.data(), "isoCI3hit"); 
  branchName_idAgainstElec_ = Form("%s_%s", branchName_obj_.data(), "idAntiEle");
  branchName_idAgainstMu_ = Form("%s_%s", branchName_obj_.data(), "idAntiMu");
}

void RecoHadTauWriter::setBranches(TTree* tree)
{
  genLeptonWriter_->setBranches(tree);
  genHadTauWriter_->setBranches(tree);
  genJetWriter_->setBranches(tree);
  setBranch(tree, &nHadTaus_, branchName_num_);
  hadTau_pt_ = new Float_t[max_nHadTaus_];
  setBranchVF(tree, branchName_pt_, branchName_num_, hadTau_pt_);
  hadTau_eta_ = new Float_t[max_nHadTaus_];
  setBranchVF(tree, branchName_eta_, branchName_num_, hadTau_eta_);
  hadTau_phi_ = new Float_t[max_nHadTaus_];
  setBranchVF(tree, branchName_phi_, branchName_num_, hadTau_phi_);
  hadTau_mass_ = new Float_t[max_nHadTaus_];
  setBranchVF(tree, branchName_mass_, branchName_num_, hadTau_mass_);
  hadTau_charge_ = new Int_t[max_nHadTaus_];
  setBranchVI(tree, branchName_charge_, branchName_num_, hadTau_charge_);
  hadTau_dxy_ = new Float_t[max_nHadTaus_];
  setBranchVF(tree, branchName_dxy_, branchName_num_, hadTau_dxy_);
  hadTau_dz_ = new Float_t[max_nHadTaus_];
  setBranchVF(tree, branchName_dz_, branchName_num_, hadTau_dz_);
  hadTau_decayMode_ = new Int_t[max_nHadTaus_];
  setBranchVI(tree, branchName_decayMode_, branchName_num_, hadTau_decayMode_);
  hadTau_idDecayMode_ = new Bool_t[max_nHadTaus_];
  setBranch(tree, hadTau_idDecayMode_, branchName_idDecayMode_, branchName_num_);
  hadTau_idDecayModeNewDMs_ = new Bool_t[max_nHadTaus_];
  setBranch(tree, hadTau_idDecayModeNewDMs_, branchName_idDecayModeNewDMs_, branchName_num_);
  hadTau_idMVA_dR03_ = new UChar_t[max_nHadTaus_];
  setBranch(tree, hadTau_idMVA_dR03_, branchName_idMVA_dR03_, branchName_num_);
  hadTau_rawMVA_dR03_ = new Float_t[max_nHadTaus_];
  setBranchVF(tree, branchName_rawMVA_dR03_, branchName_num_, hadTau_rawMVA_dR03_);
  hadTau_idMVA_dR05_ = new UChar_t[max_nHadTaus_];
  setBranch(tree, hadTau_idMVA_dR05_, branchName_idMVA_dR05_, branchName_num_);
  hadTau_rawMVA_dR05_ = new Float_t[max_nHadTaus_];
  setBranchVF(tree, branchName_rawMVA_dR05_, branchName_num_, hadTau_rawMVA_dR05_);
  hadTau_idCombIso_dR03_ = new Int_t[max_nHadTaus_];
  setBranchVI(tree, branchName_idCombIso_dR03_, branchName_num_, hadTau_idCombIso_dR03_);
  hadTau_rawCombIso_dR03_ = new Float_t[max_nHadTaus_];
  setBranchVF(tree, branchName_rawCombIso_dR03_, branchName_num_, hadTau_rawCombIso_dR03_);
  hadTau_idCombIso_dR05_ = new Int_t[max_nHadTaus_];
  setBranchVI(tree, branchName_idCombIso_dR05_, branchName_num_, hadTau_idCombIso_dR05_);
  hadTau_rawCombIso_dR05_ = new Float_t[max_nHadTaus_];
  setBranchVF(tree, branchName_rawCombIso_dR05_, branchName_num_, hadTau_rawCombIso_dR05_);
  hadTau_idAgainstElec_ = new UChar_t[max_nHadTaus_];
  setBranch(tree, hadTau_idAgainstElec_, branchName_idAgainstElec_, branchName_num_);
  hadTau_idAgainstMu_ = new UChar_t[max_nHadTaus_];
  setBranch(tree, hadTau_idAgainstMu_, branchName_idAgainstMu_, branchName_num_);
}

void RecoHadTauWriter::write(const std::vector<const RecoHadTau*>& hadTaus) 
{
  nHadTaus_ = hadTaus.size();
  for ( UInt_t idxHadTau = 0; idxHadTau < nHadTaus_; ++idxHadTau ) {
    const RecoHadTau* hadTau = hadTaus[idxHadTau];
    assert(hadTau);
    hadTau_pt_[idxHadTau] = hadTau->pt();
    hadTau_eta_[idxHadTau] = hadTau->eta();
    hadTau_phi_[idxHadTau] = hadTau->phi();
    hadTau_mass_[idxHadTau] = hadTau->mass();
    hadTau_charge_[idxHadTau] = hadTau->charge();
    hadTau_dxy_[idxHadTau] = hadTau->dxy();
    hadTau_dz_[idxHadTau] = hadTau->dz();
    hadTau_decayMode_[idxHadTau] = hadTau->decayMode();
    hadTau_idDecayMode_[idxHadTau] = hadTau->decayModeFinding();
    hadTau_idDecayModeNewDMs_[idxHadTau] = hadTau->decayModeFindingNew();
    // "undo" insertion of "VVLose" (95% signal efficiency) working point for tau ID MVA trained for dR=0->3 isolation cone
    // and store discriminator information in the same format as in the VHbb Ntuples v24 produced by Andrea for 2016 data
    hadTau_idMVA_dR03_[idxHadTau] = ( hadTau->id_mva_dR03() >= 1 ) ? hadTau->id_mva_dR03() >> 1 : 0;
    hadTau_rawMVA_dR03_[idxHadTau] = hadTau->raw_mva_dR03();
    hadTau_idMVA_dR05_[idxHadTau] = hadTau->id_mva_dR05();
    hadTau_rawMVA_dR05_[idxHadTau] = hadTau->raw_mva_dR05();
    hadTau_idCombIso_dR03_[idxHadTau] = hadTau->id_cut_dR03();
    hadTau_rawCombIso_dR03_[idxHadTau] = hadTau->raw_cut_dR03();
    hadTau_idCombIso_dR05_[idxHadTau] = hadTau->id_cut_dR05();
    hadTau_rawCombIso_dR05_[idxHadTau] = hadTau->raw_cut_dR05();
    hadTau_idAgainstElec_[idxHadTau] = hadTau->antiElectron();
    hadTau_idAgainstMu_[idxHadTau] = hadTau->antiMuon();
  }
  writeGenMatching(hadTaus);
}

void RecoHadTauWriter::writeGenMatching(const std::vector<const RecoHadTau*>& hadTaus)
{
  std::vector<GenParticle> matched_genLeptons;
  std::vector<GenParticle> matched_genHadTaus;
  std::vector<GenParticle> matched_genJets;
  assert(nHadTaus_ == hadTaus.size());
  for ( UInt_t idxHadTau = 0; idxHadTau < nHadTaus_; ++idxHadTau ) {
    const RecoHadTau* hadTau = hadTaus[idxHadTau];
    assert(hadTau);
    const GenLepton* matched_genLepton = hadTau->genLepton();
    if ( matched_genLepton ) matched_genLeptons.push_back(static_cast<GenParticle>(*matched_genLepton));
    else matched_genLeptons.push_back(dummyGenParticle_);
    const GenHadTau* matched_genHadTau = hadTau->genHadTau();
    if ( matched_genHadTau ) matched_genHadTaus.push_back(static_cast<GenParticle>(*matched_genHadTau));
    else matched_genHadTaus.push_back(dummyGenParticle_);
    const GenJet* matched_genJet = hadTau->genJet();
    if ( matched_genJet ) matched_genJets.push_back(static_cast<GenParticle>(*matched_genJet));
    else matched_genJets.push_back(dummyGenParticle_);
  }
  genLeptonWriter_->write(matched_genLeptons);
  genHadTauWriter_->write(matched_genHadTaus);
  genJetWriter_->write(matched_genJets);
}
