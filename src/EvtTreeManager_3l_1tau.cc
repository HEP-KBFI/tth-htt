#include "tthAnalysis/HiggsToTauTau/interface/EvtTreeManager_3l_1tau.h"

#include "tthAnalysis/HiggsToTauTau/interface/histogramAuxFunctions.h"

#include <TMath.h>

EvtTreeManager_3l_1tau::EvtTreeManager_3l_1tau(const edm::ParameterSet& cfg)
  : HistManagerBase(cfg)
{}

void EvtTreeManager_3l_1tau::bookTree(TFileDirectory& dir)
{
  EventTree_ = new TTree("evtTree", "evtTree");

  TDirectory* subdir = createHistogramSubdirectory(dir);
  subdir->cd();
  //EventTree_ = dir.make<TTree>("evtTree", "evtTree"); 
  EventTree_ = new TTree("evtTree", "evtTree"); 

  EventTree_->Branch("lep1_pt", &lep1_pt_, "lep1_pt/F"); 
  EventTree_->Branch("lep2_pt", &lep2_pt_, "lep2_pt/F");
  EventTree_->Branch("lep3_pt", &lep3_pt_, "lep3_pt/F");
  EventTree_->Branch("lep1_conePt", &lep1_conePt_, "lep1_conePt/F");  
  EventTree_->Branch("lep2_conePt", &lep2_conePt_, "lep2_conePt/F");
  EventTree_->Branch("lep3_conePt", &lep3_conePt_, "lep3_conePt/F");
  EventTree_->Branch("lep1_eta", &lep1_eta_, "lep1_eta/F"); 
  EventTree_->Branch("lep2_eta", &lep2_eta_, "lep2_eta/F");
  EventTree_->Branch("lep3_eta", &lep3_eta_, "lep3_eta/F");
  EventTree_->Branch("lep1_tth_mva", &lep1_tth_mva_, "lep1_tth_mva/F");
  EventTree_->Branch("lep2_tth_mva", &lep2_tth_mva_, "lep2_tth_mva/F"); 
  EventTree_->Branch("lep3_tth_mva", &lep3_tth_mva_, "lep3_tth_mva/F");
  EventTree_->Branch("nJet", &nJet_, "nJet/I");
  EventTree_->Branch("nBJetLoose", &nBJetLoose_, "nBJetLoose/I");
  EventTree_->Branch("nBJetMedium", &nBJetMedium_, "nBJetMedium/I");
  EventTree_->Branch("mindr_lep1_jet", &mindr_lep1_jet_, "mindr_lep1_jet/F");
  EventTree_->Branch("mindr_lep2_jet", &mindr_lep2_jet_, "mindr_lep2_jet/F");
  EventTree_->Branch("mindr_lep3_jet", &mindr_lep3_jet_, "mindr_lep3_jet/F");
  EventTree_->Branch("mindr_tau_jet", &mindr_tau_jet_, "mindr_tau_jet/F");
  EventTree_->Branch("avg_dr_jet", &avg_dr_jet_, "avg_dr_jet/F"); 
  EventTree_->Branch("ptmiss", &ptmiss_, "ptmiss/F"); 
  EventTree_->Branch("mT_lep1", &mT_lep1_, "mT_lep1/F");
  EventTree_->Branch("mT_lep2", &mT_lep2_, "mT_lep2/F");
  EventTree_->Branch("mT_lep3", &mT_lep3_, "mT_lep3/F");
  EventTree_->Branch("htmiss", &htmiss_, "htmiss/F"); 
  EventTree_->Branch("tau_mva", &tau_mva_, "tau_mva/F"); 
  EventTree_->Branch("tau_pt", &tau_pt_, "tau_pt/F");
  EventTree_->Branch("tau_eta", &tau_eta_, "tau_eta/F");
  EventTree_->Branch("dr_leps", &dr_leps_, "dr_leps/F");
  EventTree_->Branch("dr_lep1_tau", &dr_lep1_tau_, "dr_lep1_tau/F");
  EventTree_->Branch("dr_lep2_tau", &dr_lep2_tau_, "dr_lep2_tau/F");
  EventTree_->Branch("dr_lep3_tau", &dr_lep3_tau_, "dr_lep3_tau/F");
  EventTree_->Branch("mTauTauVis1", &mTauTauVis1_, "mTauTauVis1/F");
  EventTree_->Branch("mTauTauVis2", &mTauTauVis2_, "mTauTauVis2/F");
  EventTree_->Branch("lumiScale", &lumiScale_, "lumiScale/F");
  EventTree_->Branch("genWeight", &genWeight_, "genWeight/F");
  EventTree_->Branch("evtWeight", &evtWeight_, "evtWeight/F");
}

void EvtTreeManager_3l_1tau::fillTree(float lep1_pt, float lep2_pt, float lep3_pt, float lep1_conePt, float lep2_conePt, float lep3_conePt, float lep1_eta, float lep2_eta,
				      float lep3_eta, float lep1_tth_mva, float lep2_tth_mva, float lep3_tth_mva, int nJet, int nBJetLoose, int nBJetMedium,
				      float mindr_lep1_jet, float mindr_lep2_jet, float mindr_lep3_jet, float mindr_tau_jet, float avg_dr_jet, float ptmiss,
				      float mT_lep1, float mT_lep2, float mT_lep3, float htmiss, float tau_mva, float tau_pt, float tau_eta, float dr_leps,
				      float dr_lep1_tau, float dr_lep2_tau, float dr_lep3_tau, float mTauTauVis1, float mTauTauVis2,
				      float lumiScale, float genWeight, float evtWeight)
{
  lep1_pt_ = lep1_pt;
  lep2_pt_ = lep2_pt;
  lep3_pt_ = lep3_pt;
  lep1_conePt_ = lep1_conePt;
  lep2_conePt_ = lep2_conePt;
  lep3_conePt_ = lep3_conePt;
  lep1_eta_ = lep1_eta;
  lep2_eta_ = lep2_eta;
  lep3_eta_ = lep3_eta;
  lep1_tth_mva_ = lep1_tth_mva;
  lep2_tth_mva_ = lep2_tth_mva;
  lep3_tth_mva_ = lep3_tth_mva;
  nJet_ = nJet;
  nBJetLoose_ = nBJetLoose;
  nBJetMedium_ = nBJetMedium;
  mindr_lep1_jet_ = mindr_lep1_jet;
  mindr_lep2_jet_ = mindr_lep2_jet;
  mindr_lep3_jet_ = mindr_lep3_jet;
  mindr_tau_jet_ = mindr_tau_jet;
  avg_dr_jet_ = avg_dr_jet; 
  ptmiss_ = ptmiss;
  mT_lep1_ = mT_lep1;
  mT_lep2_ = mT_lep2;
  mT_lep3_ = mT_lep3;
  htmiss_ = htmiss;
  tau_mva_ = tau_mva;
  tau_pt_ = tau_pt;
  tau_eta_ = tau_eta;
  dr_leps_ = dr_leps;
  dr_lep1_tau_ = dr_lep1_tau;
  dr_lep2_tau_ = dr_lep2_tau;
  dr_lep3_tau_ = dr_lep3_tau;
  mTauTauVis1_ = mTauTauVis1;
  mTauTauVis2_ = mTauTauVis2;
  lumiScale_ = lumiScale;
  genWeight_ = genWeight;
  evtWeight_ = evtWeight;

  EventTree_->Fill();
}
