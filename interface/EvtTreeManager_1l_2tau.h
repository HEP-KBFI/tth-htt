#ifndef tthAnalysis_HiggsToTauTau_EvtTreeManager_1l_2tau_h
#define tthAnalysis_HiggsToTauTau_EvtTreeManager_1l_2tau_h

/** \class EvtTreeManager_1l_2tau
 *
 * Book and fill histograms for event-level quantities in ttH, H->tautau analysis
 * in 1l_2tau category
 *
 * \author Christian Veelken, Tallin
 *
 */

#include "tthAnalysis/HiggsToTauTau/interface/HistManagerBase.h" // HistManagerBase
#include "TTree.h"

class EvtTreeManager_1l_2tau
  : public HistManagerBase
{
 public:
  EvtTreeManager_1l_2tau(edm::ParameterSet const& cfg);
  ~EvtTreeManager_1l_2tau() {}

  /// book and fill histograms
  void bookTree(TFileDirectory& dir);
  void fillTree(float lep_pt, float lep_eta, float lep_tth_mva, int nJet, int nBJetLoose, int nBJetMedium, float mindr_lep_jet, 
		float mindr_tau1_jet, float mindr_tau2_jet, float avg_dr_jet, float ptmiss, float mT_lep, float htmiss, float tau1_mva, 
		float tau2_mva, float tau1_pt, float tau2_pt, float tau1_eta, float tau2_eta, float dr_taus, float dr_lep_tau_os,
		float dr_lep_tau_ss, float mTauTauVis);
  void bookHistograms(TFileDirectory& dir){};

 private:
  TTree* EventTree_;

  float lep_pt_;
  float lep_eta_;
  float lep_tth_mva_;
  int   nJet_;
  int nBJetLoose_;
  int nBJetMedium_;
  float mindr_lep_jet_;
  float mindr_tau1_jet_;
  float mindr_tau2_jet_;  
  float avg_dr_jet_;
  float ptmiss_;
  float mT_lep_;
  float htmiss_;
  float tau1_mva_;
  float tau2_mva_;
  float tau1_pt_;
  float tau2_pt_;
  float tau1_eta_; 
  float tau2_eta_;
  float dr_taus_;
  float dr_lep_tau_os_;
  float dr_lep_tau_ss_;
  float mTauTauVis_;
};

#endif
