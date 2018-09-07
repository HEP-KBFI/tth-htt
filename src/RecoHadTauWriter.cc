#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTauWriter.h" // RecoHadTauWriter

#include "tthAnalysis/HiggsToTauTau/interface/GenParticleWriter.h" // GenParticleWriter
#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTau.h" // RecoHadTau, GenLepton, GenHadTau, GenJet
#include "tthAnalysis/HiggsToTauTau/interface/BranchAddressInitializer.h" // BranchAddressInitializer, TTree, Form()
#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // kEra_*

RecoHadTauWriter::RecoHadTauWriter(int era)
  : RecoHadTauWriter(era, "Tau")
{}

RecoHadTauWriter::RecoHadTauWriter(int era,
                                   const std::string & branchName_obj)
  : RecoHadTauWriter(era, Form("n%s", branchName_obj.data()), branchName_obj)
{}

RecoHadTauWriter::RecoHadTauWriter(int era,
                                   const std::string & branchName_num,
                                   const std::string & branchName_obj)
  : era_(era)
  , max_nHadTaus_(32)
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
  , hadTau_idDecayModeNewDMs_(nullptr)
  , hadTau_idMVA_dR03_(nullptr)
  , hadTau_rawMVA_dR03_(nullptr)
  , hadTau_idMVA_dR05_(nullptr)
  , hadTau_rawMVA_dR05_(nullptr)
  , hadTau_idCombIso_dR03_(nullptr)
  , hadTau_rawCombIso_dR03_(nullptr)
  , hadTau_idCombIso_dR05_(nullptr)
  , hadTau_rawCombIso_dR05_(nullptr)
  , hadTau_idAgainstElec_(nullptr)
  , hadTau_idAgainstMu_(nullptr)
  , hadTau_filterBits_(nullptr)
{
  genLeptonWriter_ = new GenParticleWriter(Form("%s_genLepton", branchName_obj_.data()), max_nHadTaus_);
  genHadTauWriter_ = new GenParticleWriter(Form("%s_genTau",    branchName_obj_.data()), max_nHadTaus_);
  genJetWriter_    = new GenParticleWriter(Form("%s_genJet",    branchName_obj_.data()), max_nHadTaus_);
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
  delete[] hadTau_filterBits_;
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
  std::string mvaString;
  switch(era_)
  {
    case kEra_2016: mvaString = "MVAoldDMdR03";       break;
    case kEra_2017: mvaString = "MVAoldDMdR032017v2"; break;
    case kEra_2018: throw cmsException(this, __func__, __LINE__) << "Implement me!";
    default: throw cmsException(this, __func__, __LINE__) << "Invalid era = " << era_;
  }
  assert(! mvaString.empty());
  branchName_idMVA_dR03_ = Form("%s_%s", branchName_obj_.data(), Form("id%s_log", mvaString.data()));
  branchName_rawMVA_dR03_ = Form("%s_%s", branchName_obj_.data(), Form("raw%s", mvaString.data()));
  branchName_idMVA_dR05_ = Form("%s_%s", branchName_obj_.data(), "idMVAoldDM_log");
  branchName_rawMVA_dR05_ = Form("%s_%s", branchName_obj_.data(), "rawMVAoldDM");
  branchName_idCombIso_dR03_ = Form("%s_%s", branchName_obj_.data(), "idCI3hitdR03");
  branchName_rawCombIso_dR03_ = Form("%s_%s", branchName_obj_.data(), "isoCI3hitdR03");
  branchName_idCombIso_dR05_ = Form("%s_%s", branchName_obj_.data(), "idCI3hit");
  branchName_rawCombIso_dR05_ = Form("%s_%s", branchName_obj_.data(), "isoCI3hit"); 
  branchName_idAgainstElec_ = Form("%s_%s", branchName_obj_.data(), "idAntiEle_log");
  branchName_idAgainstMu_ = Form("%s_%s", branchName_obj_.data(), "idAntiMu_log");
  branchName_filterBits_ = Form("%s_%s", branchName_obj_.data(), "filterBits");
}

void RecoHadTauWriter::setBranches(TTree * tree)
{
  genLeptonWriter_->setBranches(tree);
  genHadTauWriter_->setBranches(tree);
  genJetWriter_->setBranches(tree);
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
  bai.setBranch(hadTau_idDecayModeNewDMs_, branchName_idDecayModeNewDMs_);
  bai.setBranch(hadTau_idMVA_dR03_, branchName_idMVA_dR03_);
  bai.setBranch(hadTau_rawMVA_dR03_, branchName_rawMVA_dR03_);
  bai.setBranch(hadTau_idMVA_dR05_, branchName_idMVA_dR05_);
  bai.setBranch(hadTau_rawMVA_dR05_, branchName_rawMVA_dR05_);
  bai.setBranch(hadTau_idCombIso_dR03_, branchName_idCombIso_dR03_);
  bai.setBranch(hadTau_rawCombIso_dR03_, branchName_rawCombIso_dR03_);
  bai.setBranch(hadTau_idCombIso_dR05_, branchName_idCombIso_dR05_);
  bai.setBranch(hadTau_rawCombIso_dR05_, branchName_rawCombIso_dR05_);
  bai.setBranch(hadTau_idAgainstElec_, branchName_idAgainstElec_);
  bai.setBranch(hadTau_idAgainstMu_, branchName_idAgainstMu_);
  bai.setBranch(hadTau_filterBits_, branchName_filterBits_);
}

void RecoHadTauWriter::write(const std::vector<const RecoHadTau *> & hadTaus)
{
  nHadTaus_ = hadTaus.size();
  for(UInt_t idxHadTau = 0; idxHadTau < nHadTaus_; ++idxHadTau)
  {
    const RecoHadTau * hadTau = hadTaus[idxHadTau];
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
    // "undo" insertion of "VVLose" (95% signal efficiency) working point for tau ID MVA trained
    // for dR=0->3 isolation cone and restore discriminator information
    if(era_ == kEra_2016)
    {
      hadTau_idMVA_dR03_[idxHadTau] = hadTau->id_mva_dR03() >= 2 ? hadTau->id_mva_dR03() - 1 : 0;
    }
    else
    {
      hadTau_idMVA_dR03_[idxHadTau] = hadTau->id_mva_dR03();
    }
    hadTau_rawMVA_dR03_[idxHadTau] = hadTau->raw_mva_dR03();
    hadTau_idMVA_dR05_[idxHadTau] = hadTau->id_mva_dR05();
    hadTau_rawMVA_dR05_[idxHadTau] = hadTau->raw_mva_dR05();
    hadTau_idCombIso_dR03_[idxHadTau] = hadTau->id_cut_dR03();
    hadTau_rawCombIso_dR03_[idxHadTau] = hadTau->raw_cut_dR03();
    hadTau_idCombIso_dR05_[idxHadTau] = hadTau->id_cut_dR05();
    hadTau_rawCombIso_dR05_[idxHadTau] = hadTau->raw_cut_dR05();
    hadTau_idAgainstElec_[idxHadTau] = hadTau->antiElectron();
    hadTau_idAgainstMu_[idxHadTau] = hadTau->antiMuon();
    hadTau_filterBits_[idxHadTau] = hadTau->filterBits();
  }
  writeGenMatching(hadTaus);
}

void RecoHadTauWriter::writeGenMatching(const std::vector<const RecoHadTau *> & hadTaus)
{
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
