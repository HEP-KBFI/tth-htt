#include "tthAnalysis/HiggsToTauTau/interface/RecoJetWriter.h" // RecoJetWriter

#include "FWCore/Utilities/interface/Exception.h"

#include "tthAnalysis/HiggsToTauTau/interface/writerAuxFunctions.h" // setBranchI, setBranchVF

#include <TString.h> // Form

RecoJetWriter::RecoJetWriter(int era, bool isMC)
  : era_(era)
  , isMC_(isMC)
  , max_nJets_(32)
  , branchName_num_("nJets")
  , branchName_obj_("Jets")
  , genLeptonWriter_(0)
  , genHadTauWriter_(0)
  , genJetWriter_(0)
  , jet_pt_(0)
  , jet_eta_(0)
  , jet_phi_(0)
  , jet_mass_(0)
  , jet_jecUncertTotal_(0)
  , jet_BtagCSV_(0)
  , jet_BtagWeight_(0)
  , jet_QGDiscr_(0)
  , jet_heppyFlavour_(0)
{
  genLeptonWriter_ = new GenParticleWriter(Form("%s_genLepton", branchName_num_.data()), Form("%s_genLepton", branchName_obj_.data()));
  genHadTauWriter_ = new GenParticleWriter(Form("%s_genHadTau", branchName_num_.data()), Form("%s_genHadTau", branchName_obj_.data()));
  genJetWriter_ = new GenParticleWriter(Form("%s_genJet", branchName_num_.data()), Form("%s_genJet", branchName_obj_.data()));
  setBranchNames();
}

RecoJetWriter::RecoJetWriter(int era, bool isMC, const std::string& branchName_num, const std::string& branchName_obj)
  : era_(era)
  , isMC_(isMC)
  , max_nJets_(32)
  , branchName_num_(branchName_num)
  , branchName_obj_(branchName_obj)
  , genLeptonWriter_(0)
  , genHadTauWriter_(0)
  , genJetWriter_(0)
  , jet_pt_(0)
  , jet_eta_(0)
  , jet_phi_(0)
  , jet_mass_(0)
  , jet_jecUncertTotal_(0)
  , jet_BtagCSV_(0)
  , jet_BtagWeight_(0)
  , jet_QGDiscr_(0)
  , jet_heppyFlavour_(0)
{
  genLeptonWriter_ = new GenParticleWriter(Form("%s_genLepton", branchName_num_.data()), Form("%s_genLepton", branchName_obj_.data()));
  genHadTauWriter_ = new GenParticleWriter(Form("%s_genHadTau", branchName_num_.data()), Form("%s_genHadTau", branchName_obj_.data()));
  genJetWriter_ = new GenParticleWriter(Form("%s_genJet", branchName_num_.data()), Form("%s_genJet", branchName_obj_.data()));
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
  delete[] jet_heppyFlavour_;
  for ( std::map<int, Float_t*>::iterator it = jet_BtagWeights_systematics_.begin();
	it != jet_BtagWeights_systematics_.end(); ++it ) {
    delete[] it->second;
  }
}

void RecoJetWriter::setBranchNames()
{
  branchName_pt_ = Form("%s_%s", branchName_obj_.data(), "pt");    
  branchName_eta_ = Form("%s_%s", branchName_obj_.data(), "eta");
  branchName_phi_ = Form("%s_%s", branchName_obj_.data(), "phi");
  branchName_mass_ = Form("%s_%s", branchName_obj_.data(), "mass");
  branchName_jecUncertTotal_ = Form("%s_%s", branchName_obj_.data(), "jecUncertTotal");
  branchName_BtagCSV_ = Form("%s_%s", branchName_obj_.data(), "btagCSV");
  if ( era_ == kEra_2015 ) {
    branchName_QGDiscr_ = "";
  } else if ( era_ == kEra_2016 ) {
    branchName_QGDiscr_ = Form("%s_%s", branchName_obj_.data(), "qgl");
  } else assert(0);
  if ( era_ == kEra_2015 ) {
    branchName_BtagWeight_ = Form("%s_%s", branchName_obj_.data(), "bTagWeight");
  } else if ( era_ == kEra_2016 ) {
    branchName_BtagWeight_ = Form("%s_%s", branchName_obj_.data(), "btagWeightCSV");
  } else assert(0);
  for ( int idxShift = kBtag_hfUp; idxShift <= kBtag_jesDown; ++idxShift ) {
    std::string branchName_BtagWeight = TString(getBranchName_bTagWeight(era_, idxShift)).ReplaceAll("Jet_", Form("%s_", branchName_obj_.data())).Data();
    branchNames_BtagWeight_systematics_[idxShift] = branchName_BtagWeight;
  }
  if(isMC_ && era_ == kEra_2016) {
    branchName_heppyFlavour_ = Form("%s_%s", branchName_obj_.data(), "heppyFlavour");
  } else {
    branchName_heppyFlavour_ = "";
  }
}

void RecoJetWriter::setBranches(TTree* tree)
{
  genLeptonWriter_->setBranches(tree);
  genHadTauWriter_->setBranches(tree);
  genJetWriter_->setBranches(tree);
  setBranchI(tree, branchName_num_, &nJets_);
  jet_pt_ = new Float_t[max_nJets_];
  setBranchVF(tree, branchName_pt_, branchName_num_, jet_pt_);
  jet_eta_ = new Float_t[max_nJets_];
  setBranchVF(tree, branchName_eta_, branchName_num_, jet_eta_);
  jet_phi_ = new Float_t[max_nJets_];
  setBranchVF(tree, branchName_phi_, branchName_num_, jet_phi_);
  jet_mass_ = new Float_t[max_nJets_];
  setBranchVF(tree, branchName_mass_, branchName_num_, jet_mass_);
  jet_jecUncertTotal_ = new Float_t[max_nJets_];
  setBranchVF(tree, branchName_jecUncertTotal_, branchName_num_, jet_jecUncertTotal_);
  jet_BtagCSV_ = new Float_t[max_nJets_];
  setBranchVF(tree, branchName_BtagCSV_, branchName_num_, jet_BtagCSV_);
  jet_BtagWeight_ = new Float_t[max_nJets_];
  setBranchVF(tree, branchName_BtagWeight_, branchName_num_, jet_BtagWeight_);
  for ( int idxShift = kBtag_hfUp; idxShift <= kBtag_jesDown; ++idxShift ) {
    jet_BtagWeights_systematics_[idxShift] = new Float_t[max_nJets_];
    setBranchVF(tree, branchNames_BtagWeight_systematics_[idxShift], branchName_num_, jet_BtagWeights_systematics_[idxShift]);
  }
  jet_QGDiscr_ = new Float_t[max_nJets_];
  if(branchName_QGDiscr_ != "") {
    setBranchVF(tree, branchName_QGDiscr_, branchName_num_, jet_QGDiscr_);
  }
  jet_heppyFlavour_ = new Float_t[max_nJets_];
  if ( branchName_heppyFlavour_ != "" ) {
    setBranchVF(tree, branchName_heppyFlavour_, branchName_num_, jet_heppyFlavour_);
  }
}

void RecoJetWriter::write(const std::vector<const RecoJet*>& jets) 
{
  nJets_ = jets.size();
  for ( Int_t idxJet = 0; idxJet < nJets_; ++idxJet ) {
    const RecoJet* jet = jets[idxJet];
    assert(jet);
    jet_pt_[idxJet] = jet->pt();
    jet_eta_[idxJet] = jet->eta();
    jet_phi_[idxJet] = jet->phi();
    jet_mass_[idxJet] = jet->mass();
    jet_jecUncertTotal_[idxJet] = jet->jecUncertTotal();
    jet_BtagCSV_[idxJet] = jet->BtagCSV_;
    jet_BtagWeight_[idxJet] = jet->BtagWeight();
    for ( int idxShift = kBtag_hfUp; idxShift <= kBtag_jesDown; ++idxShift ) {
      std::map<int, Double_t>::const_iterator jet_BtagWeight_systematics_iter = jet->BtagWeight_systematics_.find(idxShift);
      if ( jet_BtagWeight_systematics_iter != jet->BtagWeight_systematics_.end() ) {
	jet_BtagWeights_systematics_[idxShift][idxJet] = jet_BtagWeight_systematics_iter->second;
      } else {
	jet_BtagWeights_systematics_[idxShift][idxJet] = 1.;
      }
    }
    jet_QGDiscr_[idxJet] = jet->QGDiscr();
    jet_heppyFlavour_[idxJet] = jet->heppyFlavour();
  }
  writeGenMatching(jets);
}

void RecoJetWriter::writeGenMatching(const std::vector<const RecoJet*>& jets) 
{
  std::vector<GenParticle> matched_genLeptons;
  std::vector<GenParticle> matched_genHadTaus;
  std::vector<GenParticle> matched_genJets;
  assert(nJets_ == (int)jets.size());
  for ( Int_t idxJet = 0; idxJet < nJets_; ++idxJet ) {
    const RecoJet* jet = jets[idxJet];
    assert(jet);
    const GenLepton* matched_genLepton = jet->genLepton();
    if ( matched_genLepton ) matched_genLeptons.push_back(static_cast<GenParticle>(*matched_genLepton));
    else matched_genLeptons.push_back(dummyGenParticle_);
    const GenHadTau* matched_genHadTau = jet->genHadTau();
    if ( matched_genHadTau ) matched_genHadTaus.push_back(static_cast<GenParticle>(*matched_genHadTau));
    else matched_genHadTaus.push_back(dummyGenParticle_);
    const GenJet* matched_genJet = jet->genJet();
    if ( matched_genJet ) matched_genJets.push_back(static_cast<GenParticle>(*matched_genJet));
    else matched_genJets.push_back(dummyGenParticle_);
  }
  genLeptonWriter_->write(matched_genLeptons);
  genHadTauWriter_->write(matched_genHadTaus);
  genJetWriter_->write(matched_genJets);
}
