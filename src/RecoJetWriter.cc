#include "tthAnalysis/HiggsToTauTau/interface/RecoJetWriter.h" // RecoJetWriter

#include "FWCore/Utilities/interface/Exception.h"

#include "tthAnalysis/HiggsToTauTau/interface/writerAuxFunctions.h" // setBranchI, setBranchVF

#include <TString.h> // Form

RecoJetWriter::RecoJetWriter(int era,
                             bool isMC)
  : era_(era)
  , isMC_(isMC)
  , max_nJets_(32)
  , branchName_num_("nJets")
  , branchName_obj_("Jets")
  , jet_pt_(0)
  , jet_eta_(0)
  , jet_phi_(0)
  , jet_mass_(0)
  , jet_corr_(0)
  , jet_corr_JECUp_(0)
  , jet_corr_JECDown_(0) 
  , jet_BtagCSVwHipMitigation_(0)
  , jet_BtagCSVwoHipMitigation_(0)
  , jet_BtagWeight_(0)
  , jet_heppyFlavour_(0)
{
  setBranchNames();
}

RecoJetWriter::RecoJetWriter(int era, bool isMC, const std::string& branchName_num, const std::string& branchName_obj)
  : era_(era)
  , isMC_(isMC)
  , max_nJets_(32)
  , branchName_num_(branchName_num)
  , branchName_obj_(branchName_obj)
  , jet_pt_(0)
  , jet_eta_(0)
  , jet_phi_(0)
  , jet_mass_(0)
  , jet_corr_(0)
  , jet_corr_JECUp_(0)
  , jet_corr_JECDown_(0) 
  , jet_BtagCSVwHipMitigation_(0)
  , jet_BtagCSVwoHipMitigation_(0)
  , jet_BtagWeight_(0)
  , jet_heppyFlavour_(0)
{
  setBranchNames();
}

RecoJetWriter::~RecoJetWriter()
{
  delete[] jet_pt_;
  delete[] jet_eta_;
  delete[] jet_phi_;
  delete[] jet_mass_;
  delete[] jet_corr_;
  delete[] jet_corr_JECUp_;
  delete[] jet_corr_JECDown_;
  delete[] jet_BtagCSVwHipMitigation_;
  delete[] jet_BtagCSVwoHipMitigation_;
  delete[] jet_BtagWeight_;
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
  branchName_corr_ = Form("%s_%s", branchName_obj_.data(), "corr");
  branchName_corr_JECUp_ = Form("%s_%s_%s", branchName_obj_.data(), "corr", "JECUp");
  branchName_corr_JECDown_ = Form("%s_%s_%s", branchName_obj_.data(), "corr", "JECDown");
  if ( era_ == kEra_2015 ) {
    branchName_BtagCSVwHipMitigation_ = "";
    branchName_BtagCSVwoHipMitigation_ = Form("%s_%s", branchName_obj_.data(), "btagCSV");
    branchName_BtagWeight_ = Form("%s_%s", branchName_obj_.data(), "bTagWeight");
  } else if ( era_ == kEra_2016 ) {
    branchName_BtagCSVwHipMitigation_ = Form("%s_%s", branchName_obj_.data(), "btagCSV");               // CV: CSV algorithm with HIP mitigation
    branchName_BtagCSVwoHipMitigation_ = Form("%s_%s", branchName_obj_.data(), "btagNoHipMitigation"); // CV: CSV algorithm without HIP mitigation
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
  setBranchI(tree, branchName_num_, &nJets_);
  jet_pt_ = new Float_t[max_nJets_];
  setBranchVF(tree, branchName_pt_, branchName_num_, jet_pt_);
  jet_eta_ = new Float_t[max_nJets_];
  setBranchVF(tree, branchName_eta_, branchName_num_, jet_eta_);
  jet_phi_ = new Float_t[max_nJets_];
  setBranchVF(tree, branchName_phi_, branchName_num_, jet_phi_);
  jet_mass_ = new Float_t[max_nJets_];
  setBranchVF(tree, branchName_mass_, branchName_num_, jet_mass_);
  jet_corr_ = new Float_t[max_nJets_];
  setBranchVF(tree, branchName_corr_, branchName_num_, jet_corr_);
  jet_corr_JECUp_ = new Float_t[max_nJets_];
  setBranchVF(tree, branchName_corr_JECUp_, branchName_num_, jet_corr_JECUp_);
  jet_corr_JECDown_ = new Float_t[max_nJets_];
  setBranchVF(tree, branchName_corr_JECDown_, branchName_num_, jet_corr_JECDown_);
  jet_BtagCSVwHipMitigation_ = new Float_t[max_nJets_];
  if ( branchName_BtagCSVwHipMitigation_ != "" ) {
    setBranchVF(tree, branchName_BtagCSVwHipMitigation_, branchName_num_, jet_BtagCSVwHipMitigation_);
  }
  jet_BtagCSVwoHipMitigation_ = new Float_t[max_nJets_];
  if ( branchName_BtagCSVwoHipMitigation_ != "" ) {
    setBranchVF(tree, branchName_BtagCSVwoHipMitigation_, branchName_num_, jet_BtagCSVwoHipMitigation_);
  }
  jet_BtagWeight_ = new Float_t[max_nJets_];
  setBranchVF(tree, branchName_BtagWeight_, branchName_num_, jet_BtagWeight_);
  for ( int idxShift = kBtag_hfUp; idxShift <= kBtag_jesDown; ++idxShift ) {
    jet_BtagWeights_systematics_[idxShift] = new Float_t[max_nJets_];
    setBranchVF(tree, branchNames_BtagWeight_systematics_[idxShift], branchName_num_, jet_BtagWeights_systematics_[idxShift]);
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
    jet_corr_[idxJet] = jet->corr();
    jet_corr_JECUp_[idxJet] = jet->corr_JECUp();
    jet_corr_JECDown_[idxJet] = jet->corr_JECDown();
    jet_BtagCSVwHipMitigation_[idxJet] = jet->BtagCSVwHipMitigation_;
    jet_BtagCSVwoHipMitigation_[idxJet] = jet->BtagCSVwoHipMitigation_;
    jet_BtagWeight_[idxJet] = jet->BtagWeight();
    for ( int idxShift = kBtag_hfUp; idxShift <= kBtag_jesDown; ++idxShift ) {
      std::map<int, Double_t>::const_iterator jet_BtagWeight_systematics_iter = jet->BtagWeight_systematics_.find(idxShift);
      if ( jet_BtagWeight_systematics_iter != jet->BtagWeight_systematics_.end() ) {
	jet_BtagWeights_systematics_[idxShift][idxJet] = jet_BtagWeight_systematics_iter->second;
      } else {
	jet_BtagWeights_systematics_[idxShift][idxJet] = 1.;
      }
    }
    jet_heppyFlavour_[idxJet] = jet->heppyFlavour();
  }
}
