#include "tthAnalysis/HiggsToTauTau/interface/EvtTreeManager_1l_2tau.h"

#include "tthAnalysis/HiggsToTauTau/interface/histogramAuxFunctions.h"

#include <TMath.h>

EvtTreeManager_1l_2tau::EvtTreeManager_1l_2tau(const edm::ParameterSet& cfg)
  : HistManagerBase(cfg)
{}

void EvtTreeManager_1l_2tau::bookTree(TFileDirectory& dir)
{
  EventTree_ = new TTree("evtTree", "evtTree");

  TDirectory* subdir = createHistogramSubdirectory(dir);
  subdir->cd();
  //EventTree_ = dir.make<TTree>("evtTree", "evtTree"); 
  EventTree_ = new TTree("evtTree", "evtTree"); 

  EventTree_->Branch("lep_pt_max", &lep_pt_max_, "lep_pt_max/F"); 
  EventTree_->Branch("nJet", &nJet_, "nJet/I");
  EventTree_->Branch("nBJetLoose", &nBJetLoose_, "nBJetLoose/I");
  EventTree_->Branch("nBJetMedium", &nBJetMedium_, "nBJetMedium/I");
  EventTree_->Branch("mindr_tau1_jet", &mindr_tau1_jet_, "mindr_tau1_jet/F");
  EventTree_->Branch("mindr_tau2_jet", &mindr_tau2_jet_, "mindr_tau2_jet/F");
  EventTree_->Branch("avg_dr_jet", &avg_dr_jet_, "avg_dr_jet/F"); 
  EventTree_->Branch("ptmiss", &ptmiss_, "ptmiss/F"); 
  EventTree_->Branch("mT_lep", &mT_lep_, "mT_lep/F");
  EventTree_->Branch("htmiss", &htmiss_, "htmiss/F"); 
  EventTree_->Branch("tau1_mva", &tau1_mva_, "tau1_mva/F"); 
  EventTree_->Branch("tau2_mva", &tau2_mva_, "tau2_mva/F");
  EventTree_->Branch("tau1_pt", &tau1_pt_, "tau1_pt/F");
  EventTree_->Branch("tau2_pt", &tau2_pt_, "tau2_pt/F");
  EventTree_->Branch("dr_taus", &dr_taus_, "dr_taus/F");
  EventTree_->Branch("mTauTauVis", &mTauTauVis_, "mTauTauVis/F");
}

void EvtTreeManager_1l_2tau::fillTree(float lep_pt_max, int nJet, int nBJetLoose, int nBJetMedium, float mindr_tau1_jet, float mindr_tau2_jet, 
				      float avg_dr_jet, float ptmiss, float mT_lep, float htmiss, float tau1_mva, float tau2_mva, 
				      float tau1_pt, float tau2_pt, float dr_taus, float mTauTauVis)
{
  lep_pt_max_ = lep_pt_max;
  nJet_ = nJet;
  nBJetLoose_ = nBJetLoose;
  nBJetMedium_ = nBJetMedium;
  mindr_tau1_jet_ = mindr_tau1_jet;
  mindr_tau2_jet_ = mindr_tau2_jet;
  avg_dr_jet_ = avg_dr_jet; 
  ptmiss_ = ptmiss;
  mT_lep_ = mT_lep;
  htmiss_ = htmiss;
  tau1_mva_ = tau1_mva;
  tau2_mva_ = tau2_mva;
  tau1_pt_ = tau1_pt;
  tau2_pt_ = tau2_pt;
  dr_taus_ = dr_taus;
  mTauTauVis_ = mTauTauVis;

  EventTree_->Fill();
}
