#include "tthAnalysis/HiggsToTauTau/interface/EvtTreeManager_1l_1tau.h"

#include "tthAnalysis/HiggsToTauTau/interface/histogramAuxFunctions.h"

#include <TMath.h>

EvtTreeManager_1l_1tau::EvtTreeManager_1l_1tau(const edm::ParameterSet& cfg)
  : HistManagerBase(cfg)
{}

void EvtTreeManager_1l_1tau::bookTree(TFileDirectory& dir)
{
  EventTree_ = new TTree("evtTree", "evtTree");

  TDirectory* subdir = createHistogramSubdirectory(dir);
  subdir->cd();
  //EventTree_ = dir.make<TTree>("evtTree", "evtTree"); 
  EventTree_ = new TTree("evtTree", "evtTree"); 

  EventTree_->Branch("lep_pt", &lep_pt_, "lep_pt/F"); 
  EventTree_->Branch("lep_eta", &lep_eta_, "lep_eta/F");
  EventTree_->Branch("lep_tth_mva", &lep_tth_mva_, "lep_tth_mva/F");
  EventTree_->Branch("nJet", &nJet_, "nJet/I");
  EventTree_->Branch("nBJetLoose", &nBJetLoose_, "nBJetLoose/I");
  EventTree_->Branch("nBJetMedium", &nBJetMedium_, "nBJetMedium/I");
  EventTree_->Branch("mindr_lep_jet", &mindr_lep_jet_, "mindr_lep_jet/F");
  EventTree_->Branch("mindr_tau_jet", &mindr_tau_jet_, "mindr_tau_jet/F");
  EventTree_->Branch("avg_dr_jet", &avg_dr_jet_, "avg_dr_jet/F"); 
  EventTree_->Branch("ptmiss", &ptmiss_, "ptmiss/F"); 
  EventTree_->Branch("mT_lep", &mT_lep_, "mT_lep/F");
  EventTree_->Branch("htmiss", &htmiss_, "htmiss/F"); 
  EventTree_->Branch("tau_mva", &tau_mva_, "tau_mva/F"); 
  EventTree_->Branch("tau_pt", &tau_pt_, "tau_pt/F");
  EventTree_->Branch("mTauTauVis", &mTauTauVis_, "mTauTauVis/F");
  EventTree_->Branch("mTauTau", &mTauTau_, "mTauTau/F"); 
}

void EvtTreeManager_1l_1tau::fillTree(float lep_pt, float lep_eta, float lep_tth_mva, int nJet, int nBJetLoose, int nBJetMedium, float mindr_lep_jet,  
				      float mindr_tau_jet, float avg_dr_jet, float ptmiss, float mT_lep, float htmiss, float tau_mva, float tau_pt,  
				      float mTauTauVis, float mTauTau)
{
  lep_pt_ = lep_pt;
  lep_eta_ = lep_eta;
  lep_tth_mva_ = lep_tth_mva;
  nJet_ = nJet;
  nBJetLoose_ = nBJetLoose;
  nBJetMedium_ = nBJetMedium;
  mindr_lep_jet_ = mindr_lep_jet;
  mindr_tau_jet_ = mindr_tau_jet;
  avg_dr_jet_ = avg_dr_jet; 
  ptmiss_ = ptmiss;
  mT_lep_ = mT_lep;
  htmiss_ = htmiss;
  tau_mva_ = tau_mva;
  tau_pt_ = tau_pt;
  mTauTauVis_ = mTauTauVis;
  mTauTau_ = mTauTau;

  EventTree_->Fill();
}
