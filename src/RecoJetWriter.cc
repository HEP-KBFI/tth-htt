#include "tthAnalysis/HiggsToTauTau/interface/RecoJetWriter.h" // RecoJetWriter

#include "tthAnalysis/HiggsToTauTau/interface/GenParticleWriter.h" // GenParticleWriter
#include "tthAnalysis/HiggsToTauTau/interface/RecoJet.h" // RecoJet, GenLepton, GenHadTau, GenJet
#include "tthAnalysis/HiggsToTauTau/interface/BranchAddressInitializer.h" // BranchAddressInitializer, TTree, Form()
#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // kBtag_*

RecoJetWriter::RecoJetWriter(int era,
                             bool isMC)
  : RecoJetWriter(era, isMC, "nJet", "Jet")
{}

RecoJetWriter::RecoJetWriter(int era,
                             bool isMC,
                             const std::string & branchName_num,
                             const std::string & branchName_obj)
  : era_(era)
  , isMC_(isMC)
  , max_nJets_(32)
  , branchName_num_(branchName_num)
  , branchName_obj_(branchName_obj)
  , genLeptonWriter_(nullptr)
  , genHadTauWriter_(nullptr)
  , genJetWriter_(nullptr)
  , jet_pt_(nullptr)
  , jet_eta_(nullptr)
  , jet_phi_(nullptr)
  , jet_mass_(nullptr)
  , jet_jecUncertTotal_(nullptr)
  , jet_BtagCSV_(nullptr)
  , jet_BtagWeight_(nullptr)
  , jet_QGDiscr_(nullptr)
{
  genLeptonWriter_ = new GenParticleWriter(Form("%s_genLepton", branchName_num_.data()), Form("%s_genLepton", branchName_obj_.data()));
  genHadTauWriter_ = new GenParticleWriter(Form("%s_genTau",    branchName_num_.data()), Form("%s_genTau",    branchName_obj_.data()));
  genJetWriter_    = new GenParticleWriter(Form("%s_genJet",    branchName_num_.data()), Form("%s_genJet",    branchName_obj_.data()));
  setBranchNames();
}

RecoJetWriter::~RecoJetWriter()
{
  delete genLeptonWriter_;
  delete genHadTauWriter_;
  delete genJetWriter_;
  delete[] jet_pt_;
  delete[] jet_eta_;
  delete[] jet_phi_;
  delete[] jet_mass_;
  delete[] jet_jecUncertTotal_;
  delete[] jet_BtagCSV_;
  delete[] jet_BtagWeight_;
  delete[] jet_QGDiscr_;
  for(auto & kv: jet_BtagWeights_systematics_)
  {
    delete[] kv.second;
  }
}

void RecoJetWriter::setBranchNames()
{
  branchName_pt_ = Form("%s_%s", branchName_obj_.data(), "pt");
  branchName_eta_ = Form("%s_%s", branchName_obj_.data(), "eta");
  branchName_phi_ = Form("%s_%s", branchName_obj_.data(), "phi");
  branchName_mass_ = Form("%s_%s", branchName_obj_.data(), "mass");
  branchName_jecUncertTotal_ = Form("%s_%s", branchName_obj_.data(), "jecUncertTotal");
  branchName_BtagCSV_ = Form("%s_%s", branchName_obj_.data(), "btagCSVV2");
  branchName_QGDiscr_ = Form("%s_%s", branchName_obj_.data(), "qgl");
  branchName_BtagWeight_ = Form("%s_%s", branchName_obj_.data(), "btagSF_csvv2");
  for(int idxShift = kBtag_hfUp; idxShift <= kBtag_jesDown; ++idxShift)
  {
    branchNames_BtagWeight_systematics_[idxShift] = TString(getBranchName_bTagWeight(era_, idxShift))
      .ReplaceAll("Jet_", Form("%s_", branchName_obj_.data())).Data()
    ;
  }
}

void RecoJetWriter::setBranches(TTree * tree)
{
  genLeptonWriter_->setBranches(tree);
  genHadTauWriter_->setBranches(tree);
  genJetWriter_->setBranches(tree);

  BranchAddressInitializer bai(tree, branchName_num_, max_nJets_);
  bai.setBranch(nJets_, branchName_num_);
  bai.setBranch(jet_pt_, branchName_pt_);
  bai.setBranch(jet_eta_, branchName_eta_);
  bai.setBranch(jet_phi_, branchName_phi_);
  bai.setBranch(jet_mass_, branchName_mass_);
  bai.setBranch(jet_jecUncertTotal_, branchName_jecUncertTotal_);
  bai.setBranch(jet_BtagCSV_, branchName_BtagCSV_);
  bai.setBranch(jet_BtagWeight_, branchName_BtagWeight_);
  for(int idxShift = kBtag_hfUp; idxShift <= kBtag_jesDown; ++idxShift)
  {
    jet_BtagWeights_systematics_[idxShift] = new std::remove_pointer<
        decltype(jet_BtagWeights_systematics_)::mapped_type
      >::type[max_nJets_];
    bai.setBranch(jet_BtagWeights_systematics_[idxShift], branchNames_BtagWeight_systematics_[idxShift], true);
  }
  bai.setBranch(jet_QGDiscr_, branchName_QGDiscr_);
}

void RecoJetWriter::write(const std::vector<const RecoJet *> & jets)
{
  nJets_ = jets.size();
  for(UInt_t idxJet = 0; idxJet < nJets_; ++idxJet)
  {
    const RecoJet * jet = jets[idxJet];
    assert(jet);
    jet_pt_[idxJet] = jet->pt();
    jet_eta_[idxJet] = jet->eta();
    jet_phi_[idxJet] = jet->phi();
    jet_mass_[idxJet] = jet->mass();
    jet_jecUncertTotal_[idxJet] = jet->jecUncertTotal();
    jet_BtagCSV_[idxJet] = jet->BtagCSV_;
    jet_BtagWeight_[idxJet] = jet->BtagWeight();
    for(int idxShift = kBtag_hfUp; idxShift <= kBtag_jesDown; ++idxShift)
    {
      if(jet->BtagWeight_systematics_.count(idxShift))
      {
        jet_BtagWeights_systematics_[idxShift][idxJet] = jet->BtagWeight_systematics_.at(idxShift);
      }
      else
      {
        jet_BtagWeights_systematics_[idxShift][idxJet] = 1.;
      }
    }
    jet_QGDiscr_[idxJet] = jet->QGDiscr();
  }
  writeGenMatching(jets);
}

void RecoJetWriter::writeGenMatching(const std::vector<const RecoJet *> & jets)
{
  std::vector<GenParticle> matched_genLeptons;
  std::vector<GenParticle> matched_genHadTaus;
  std::vector<GenParticle> matched_genJets;

  assert(nJets_ == jets.size());
  for(const RecoJet * jet: jets)
  {
    assert(jet);
    const GenLepton * matched_genLepton = jet->genLepton();
    if(matched_genLepton) matched_genLeptons.push_back(static_cast<GenParticle>(*matched_genLepton));
    else                  matched_genLeptons.push_back(dummyGenParticle_);

    const GenHadTau * matched_genHadTau = jet->genHadTau();
    if(matched_genHadTau) matched_genHadTaus.push_back(static_cast<GenParticle>(*matched_genHadTau));
    else                  matched_genHadTaus.push_back(dummyGenParticle_);

    const GenJet * matched_genJet = jet->genJet();
    if(matched_genJet) matched_genJets.push_back(static_cast<GenParticle>(*matched_genJet));
    else               matched_genJets.push_back(dummyGenParticle_);
  }
  genLeptonWriter_->write(matched_genLeptons);
  genHadTauWriter_->write(matched_genHadTaus);
  genJetWriter_->write(matched_genJets);
}
