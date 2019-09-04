#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTauWriter.h" // RecoHadTauWriter

#include "tthAnalysis/HiggsToTauTau/interface/GenParticleWriter.h" // GenParticleWriter
#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTau.h" // RecoHadTau, GenLepton, GenHadTau, GenJet
#include "tthAnalysis/HiggsToTauTau/interface/BranchAddressInitializer.h" // BranchAddressInitializer, TTree, Form()
#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // kEra_*

RecoHadTauWriter::RecoHadTauWriter(int era,
                                   bool isMC)
  : RecoHadTauWriter(era, isMC, "Tau")
{}

RecoHadTauWriter::RecoHadTauWriter(int era,
                                   bool isMC,
                                   const std::string & branchName_obj)
  : RecoHadTauWriter(era, isMC, Form("n%s", branchName_obj.data()), branchName_obj)
{}

RecoHadTauWriter::RecoHadTauWriter(int era,
                                   bool isMC,
                                   const std::string & branchName_num,
                                   const std::string & branchName_obj)
  : era_(era)
  , isMC_(isMC)
  , max_nHadTaus_(36)
  , branchName_num_(branchName_num)
  , branchName_obj_(branchName_obj)
  , genLeptonWriter_(nullptr)
  , genHadTauWriter_(nullptr)
  , genJetWriter_(nullptr)
  , hadTau_pt_(nullptr)
  , hadTau_eta_(nullptr)
  , hadTau_phi_(nullptr)
  , hadTau_mass_(nullptr)
  , hadTau_charge_(nullptr)
  , hadTau_dxy_(nullptr)
  , hadTau_dz_(nullptr)
  , hadTau_decayMode_(nullptr)
  , hadTau_idDecayMode_(nullptr)
  , hadTau_idAgainstElec_(nullptr)
  , hadTau_idAgainstMu_(nullptr)
  , hadTau_filterBits_(nullptr)
  , hadTau_jetIdx_(nullptr)
  , hadTau_genPartFlav_(nullptr)
  , hadTau_genMatchIdx_(nullptr)
{
  if(isMC_)
  {
    genLeptonWriter_ = new GenParticleWriter(Form("%s_genLepton", branchName_obj_.data()), max_nHadTaus_);
    genHadTauWriter_ = new GenParticleWriter(Form("%s_genTau",    branchName_obj_.data()), max_nHadTaus_);
    genJetWriter_    = new GenParticleWriter(Form("%s_genJet",    branchName_obj_.data()), max_nHadTaus_);
  }
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
  delete[] hadTau_idAgainstElec_;
  delete[] hadTau_idAgainstMu_;
  delete[] hadTau_charge_;
  delete[] hadTau_filterBits_;
  delete[] hadTau_jetIdx_;
  delete[] hadTau_genPartFlav_;
  delete[] hadTau_genMatchIdx_;

  for(auto & kv: hadTau_idMVAs_)
  {
    delete[] kv.second;
  }
  for(auto & kv: hadTau_rawMVAs_)
  {
    delete[] kv.second;
  }
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
  for(const auto & kv: TauID_levels)
  {
    const std::string & mvaString = TauID_names.at(kv.first);
    branchNames_idMVA_[kv.first]  = Form("%s_%s", branchName_obj_.data(), Form("id%s_log", mvaString.data()));
    branchNames_rawMVA_[kv.first] = Form("%s_%s", branchName_obj_.data(), Form("raw%s", mvaString.data()));
  }
  branchName_idAgainstElec_ = Form("%s_%s", branchName_obj_.data(), "idAntiEle_log");
  branchName_idAgainstMu_ = Form("%s_%s", branchName_obj_.data(), "idAntiMu_log");
  branchName_filterBits_ = Form("%s_%s", branchName_obj_.data(), "filterBits");
  branchName_jetIdx_ = Form("%s_%s", branchName_obj_.data(), "jetIdx");
  branchName_genPartFlav_ = Form("%s_%s", branchName_obj_.data(), "genPartFlav");
  branchName_genMatchIdx_ = Form("%s_%s", branchName_obj_.data(), "genMatchIdx");
}

void RecoHadTauWriter::setBranches(TTree * tree)
{
  if(isMC_)
  {
    genLeptonWriter_->setBranches(tree);
    genHadTauWriter_->setBranches(tree);
    genJetWriter_->setBranches(tree);
  }
  BranchAddressInitializer bai(tree, max_nHadTaus_, branchName_num_);
  bai.setBranch(nHadTaus_, branchName_num_);
  bai.setBranch(hadTau_pt_, branchName_pt_);
  bai.setBranch(hadTau_eta_, branchName_eta_);
  bai.setBranch(hadTau_phi_, branchName_phi_);
  bai.setBranch(hadTau_mass_, branchName_mass_);
  bai.setBranch(hadTau_charge_, branchName_charge_);
  bai.setBranch(hadTau_dxy_, branchName_dxy_);
  bai.setBranch(hadTau_dz_, branchName_dz_);
  bai.setBranch(hadTau_decayMode_, branchName_decayMode_);
  bai.setBranch(hadTau_idDecayMode_, branchName_idDecayMode_);
  for(const auto & kv: TauID_levels)
  {
    bai.setBranch(hadTau_idMVAs_[kv.first], branchNames_idMVA_[kv.first]);
    bai.setBranch(hadTau_rawMVAs_[kv.first], branchNames_rawMVA_[kv.first]);
  }
  bai.setBranch(hadTau_idAgainstElec_, branchName_idAgainstElec_);
  bai.setBranch(hadTau_idAgainstMu_, branchName_idAgainstMu_);
  bai.setBranch(hadTau_filterBits_, branchName_filterBits_);
  bai.setBranch(hadTau_jetIdx_, branchName_jetIdx_);
  if(isMC_)
  {
    bai.setBranch(hadTau_genPartFlav_, branchName_genPartFlav_);
    bai.setBranch(hadTau_genMatchIdx_, branchName_genMatchIdx_);
  }
}

void RecoHadTauWriter::write(const std::vector<const RecoHadTau *> & hadTaus)
{
  nHadTaus_ = hadTaus.size();
  for(UInt_t idxHadTau = 0; idxHadTau < nHadTaus_; ++idxHadTau)
  {
    const RecoHadTau * hadTau = hadTaus[idxHadTau];
    assert(hadTau);
    const double corrFactor = hadTau->corrFactor();
    const Double_t hadTau_pt = hadTau->pt() / corrFactor;
    const Double_t hadTau_mass = hadTau->mass() / corrFactor;
    hadTau_pt_[idxHadTau] = hadTau_pt;
    hadTau_eta_[idxHadTau] = hadTau->eta();
    hadTau_phi_[idxHadTau] = hadTau->phi();
    hadTau_mass_[idxHadTau] = hadTau_mass;
    hadTau_charge_[idxHadTau] = hadTau->charge();
    hadTau_dxy_[idxHadTau] = hadTau->dxy();
    hadTau_dz_[idxHadTau] = hadTau->dz();
    hadTau_decayMode_[idxHadTau] = hadTau->decayMode();
    hadTau_idDecayMode_[idxHadTau] = hadTau->idDecayMode();
    for(const auto & kv: branchNames_idMVA_)
    {
      hadTau_idMVAs_[kv.first][idxHadTau] = hadTau->id_mva(kv.first);
    }
    for(const auto & kv: branchNames_rawMVA_)
    {
      hadTau_rawMVAs_[kv.first][idxHadTau] = hadTau->raw_mva(kv.first);
    }
    hadTau_idAgainstElec_[idxHadTau] = hadTau->antiElectron();
    hadTau_idAgainstMu_[idxHadTau] = hadTau->antiMuon();
    hadTau_filterBits_[idxHadTau] = hadTau->filterBits();
    hadTau_jetIdx_[idxHadTau] = hadTau->jetIdx();
    if(isMC_)
    {
      hadTau_genPartFlav_[idxHadTau] = hadTau->genPartFlav();
      hadTau_genMatchIdx_[idxHadTau] = hadTau->genMatchIdx();
    }
  }
  if(isMC_)
  {
    writeGenMatching(hadTaus);
  }
}

void RecoHadTauWriter::writeGenMatching(const std::vector<const RecoHadTau *> & hadTaus)
{
  assert(isMC_);
  std::vector<GenParticle> matched_genLeptons;
  std::vector<GenParticle> matched_genHadTaus;
  std::vector<GenParticle> matched_genJets;
  assert(nHadTaus_ == hadTaus.size());
  for(const RecoHadTau * hadTau: hadTaus)
  {
    assert(hadTau);

    const GenLepton * matched_genLepton = hadTau->genLepton();
    if(matched_genLepton) matched_genLeptons.push_back(*reinterpret_cast<const GenParticle *>(matched_genLepton));
    else                  matched_genLeptons.push_back(dummyGenParticle_);

    const GenHadTau * matched_genHadTau = hadTau->genHadTau();
    if(matched_genHadTau) matched_genHadTaus.push_back(*reinterpret_cast<const GenParticle *>(matched_genHadTau));
    else                  matched_genHadTaus.push_back(dummyGenParticle_);

    const GenJet * matched_genJet = hadTau->genJet();
    if(matched_genJet) matched_genJets.push_back(*reinterpret_cast<const GenParticle *>(matched_genJet));
    else               matched_genJets.push_back(dummyGenParticle_);
  }
  genLeptonWriter_->write(matched_genLeptons);
  genHadTauWriter_->write(matched_genHadTaus);
  genJetWriter_->write(matched_genJets);
}
