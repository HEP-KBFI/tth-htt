#ifndef tthAnalysis_HiggsToTauTau_EvtTreeManager_0l_2tau_h
#define tthAnalysis_HiggsToTauTau_EvtTreeManager_0l_2tau_h

/** \class EvtTreeManager_0l_2tau
 *
 * Book and fill trees for mva training for event-level quantities in ttH, H->tautau analysis
 * in 0l_2tau category
 *
 * \author Aruna Nayak
 *
 */

#include "tthAnalysis/HiggsToTauTau/interface/HistManagerBase.h" // HistManagerBase
#include "TTree.h"

class EvtTreeManager_0l_2tau
  : public HistManagerBase
{
 public:
  EvtTreeManager_0l_2tau(edm::ParameterSet const& cfg);
  ~EvtTreeManager_0l_2tau() {}

  /// book and fill histograms
  void bookTree(TFileDirectory& dir);
  void fillTree(int nJet, int nBJetLoose, int nBJetMedium, float mindr_tau1_jet, float mindr_tau2_jet, float avg_dr_jet, 
		float ptmiss, float mT_tau1, float mT_tau2, float htmiss, float tau1_mva, float tau2_mva, float tau1_pt, 
		float tau2_pt, float tau1_eta, float tau2_eta, float dr_taus, float mTauTauVis, float mTauTau);
  void bookHistograms(TFileDirectory& dir){};

 private:
  TTree* EventTree_;

  int   nJet_;
  int nBJetLoose_;
  int nBJetMedium_;
  float mindr_tau1_jet_;
  float mindr_tau2_jet_;  
  float avg_dr_jet_;
  float ptmiss_;
  float mT_tau1_;
  float mT_tau2_;
  float htmiss_;
  float tau1_mva_;
  float tau2_mva_;
  float tau1_pt_;
  float tau2_pt_;
  float tau1_eta_; 
  float tau2_eta_;
  float dr_taus_;
  float mTauTauVis_;
  float mTauTau_;
};

#endif
