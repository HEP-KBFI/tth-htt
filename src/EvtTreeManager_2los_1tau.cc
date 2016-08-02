#include "tthAnalysis/HiggsToTauTau/interface/EvtTreeManager_2los_1tau.h"

#include "tthAnalysis/HiggsToTauTau/interface/histogramAuxFunctions.h"

#include <TMath.h>

EvtTreeManager_2los_1tau::EvtTreeManager_2los_1tau(const edm::ParameterSet& cfg)
  : HistManagerBase(cfg)
{}

void EvtTreeManager_2los_1tau::bookTree(TFileDirectory& dir)
{
  EventTree_ = new TTree("evtTree", "evtTree");

  TDirectory* subdir = createHistogramSubdirectory(dir);
  subdir->cd();
  //EventTree_ = dir.make<TTree>("evtTree", "evtTree"); 
  EventTree_ = new TTree("evtTree", "evtTree"); 

  EventTree_->Branch("lep_pt_max", &lep_pt_max_, "lep_pt_max/F"); 
  EventTree_->Branch("lep_eta_max", &lep_eta_max_, "lep_eta_max/F"); 
  EventTree_->Branch("lep1_tth_mva", &lep1_tth_mva_, "lep1_tth_mva/F");
  EventTree_->Branch("lep2_tth_mva", &lep2_tth_mva_, "lep2_tth_mva/F"); 
  EventTree_->Branch("nJet", &nJet_, "nJet/I");
  EventTree_->Branch("nBJetLoose", &nBJetLoose_, "nBJetLoose/I");
  EventTree_->Branch("nBJetMedium", &nBJetMedium_, "nBJetMedium/I");
  EventTree_->Branch("mindr_lep1_jet", &mindr_lep1_jet_, "mindr_lep1_jet/F");
  EventTree_->Branch("mindr_lep2_jet", &mindr_lep2_jet_, "mindr_lep2_jet/F");
  EventTree_->Branch("mindr_tau_jet", &mindr_tau_jet_, "mindr_tau_jet/F");
  EventTree_->Branch("avg_dr_jet", &avg_dr_jet_, "avg_dr_jet/F"); 
  EventTree_->Branch("ptmiss", &ptmiss_, "ptmiss/F"); 
  EventTree_->Branch("mT_lep1", &mT_lep1_, "mT_lep1/F");
  EventTree_->Branch("mT_lep2", &mT_lep2_, "mT_lep2/F");
  EventTree_->Branch("htmiss", &htmiss_, "htmiss/F"); 
  EventTree_->Branch("tau_mva", &tau_mva_, "tau_mva/F"); 
  EventTree_->Branch("tau_pt", &tau_pt_, "tau_pt/F");
  EventTree_->Branch("dr_leps", &dr_leps_, "dr_leps/F");
  EventTree_->Branch("mTauTauVis", &mTauTauVis_, "mTauTauVis/F");
}

void EvtTreeManager_2los_1tau::fillTree(float lep_pt_max, float lep_eta_max, float lep1_tth_mva, float lep2_tth_mva,
					int nJet, int nBJetLoose, int nBJetMedium, float mindr_lep1_jet, 
					float mindr_lep2_jet, float mindr_tau_jet, float avg_dr_jet, float ptmiss, float mT_lep1, float mT_lep2, 
					float htmiss, float tau_mva, float tau_pt, float dr_leps, float mTauTauVis)
{
  lep_pt_max_ = lep_pt_max;
  lep_eta_max_ = lep_eta_max;
  lep1_tth_mva_ = lep1_tth_mva;
  lep2_tth_mva_ = lep2_tth_mva;
  nJet_ = nJet;
  nBJetLoose_ = nBJetLoose;
  nBJetMedium_ = nBJetMedium;
  mindr_lep1_jet_ = mindr_lep1_jet;
  mindr_lep2_jet_ = mindr_lep2_jet;
  mindr_tau_jet_ = mindr_tau_jet;
  avg_dr_jet_ = avg_dr_jet; 
  ptmiss_ = ptmiss;
  mT_lep1_ = mT_lep1;
  mT_lep2_ = mT_lep2;
  htmiss_ = htmiss;
  tau_mva_ = tau_mva;
  tau_pt_ = tau_pt;
  dr_leps_ = dr_leps;
  mTauTauVis_ = mTauTauVis;

  EventTree_->Fill();
}
