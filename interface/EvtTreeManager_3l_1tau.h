#ifndef tthAnalysis_HiggsToTauTau_EvtTreeManager_3l_1tau_h
#define tthAnalysis_HiggsToTauTau_EvtTreeManager_3l_1tau_h

/** \class EvtTreeManager_3l_1tau
 *
 * Book and fill trees for mva training for event-level quantities in ttH, H->tautau analysis
 * in 3l_1tau category
 *
 * \author Aruna Nayak
 *
 */

#include "tthAnalysis/HiggsToTauTau/interface/HistManagerBase.h" // HistManagerBase
#include "TTree.h"

class EvtTreeManager_3l_1tau
  : public HistManagerBase
{
 public:
  EvtTreeManager_3l_1tau(edm::ParameterSet const& cfg);
  ~EvtTreeManager_3l_1tau() {}

  /// book and fill histograms
  void bookTree(TFileDirectory& dir);
  void fillTree(float lep1_pt, float lep2_pt, float lep3_pt, float lep1_conePt, float lep2_conePt, float lep3_conePt, float lep1_eta, float lep2_eta, 
		float lep3_eta, float lep1_tth_mva, float lep2_tth_mva, float lep3_tth_mva, int nJet, int nBJetLoose, int nBJetMedium, 
		float mindr_lep1_jet, float mindr_lep2_jet, float mindr_lep3_jet, float mindr_tau_jet, float avg_dr_jet, float ptmiss, 
		float mT_lep1, float mT_lep2, float mT_lep3, float htmiss, float tau_mva, float tau_pt, float tau_eta, float dr_leps, 
		float dr_lep1_tau, float dr_lep2_tau, float dr_lep3_tau, float mTauTauVis1, float mTauTauVis2,
		float lumiScale, float genWeight, float evtWeight);
		
  void bookHistograms(TFileDirectory& dir){};

 private:
  TTree* EventTree_;

  float lep1_pt_;
  float lep2_pt_;
  float lep3_pt_;
  float lep1_conePt_;
  float lep2_conePt_;
  float lep3_conePt_;
  float lep1_eta_;
  float lep2_eta_;
  float lep3_eta_;
  float lep1_tth_mva_;
  float lep2_tth_mva_;
  float lep3_tth_mva_;
  int   nJet_;
  int nBJetLoose_;
  int nBJetMedium_;
  float mindr_lep1_jet_;
  float mindr_lep2_jet_;
  float mindr_lep3_jet_;
  float mindr_tau_jet_;
  float avg_dr_jet_;
  float ptmiss_;
  float mT_lep1_;
  float mT_lep2_;
  float mT_lep3_;
  float htmiss_;
  float tau_mva_;
  float tau_pt_;
  float tau_eta_;
  float dr_leps_;
  float dr_lep1_tau_;
  float dr_lep2_tau_;
  float dr_lep3_tau_;
  float mTauTauVis1_;
  float mTauTauVis2_;
  float lumiScale_;
  float genWeight_;
  float evtWeight_;
};

#endif
