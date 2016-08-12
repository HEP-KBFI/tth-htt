#ifndef tthAnalysis_HiggsToTauTau_EvtTreeManager_1l_1tau_h
#define tthAnalysis_HiggsToTauTau_EvtTreeManager_1l_1tau_h

/** \class EvtTreeManager_1l_1tau
 *
 * Book and fill trees for event-level quantities in ttH, H->tautau analysis
 * in 1l_1tau category
 *
 * \author Aruna Nayak
 *
 */

#include "tthAnalysis/HiggsToTauTau/interface/HistManagerBase.h" // HistManagerBase
#include "TTree.h"

class EvtTreeManager_1l_1tau
  : public HistManagerBase
{
 public:
  EvtTreeManager_1l_1tau(edm::ParameterSet const& cfg);
  ~EvtTreeManager_1l_1tau() {}

  /// book and fill histograms
  void bookTree(TFileDirectory& dir);
  void fillTree(float lep_pt, float lep_eta, float lep_tth_mva, int nJet, int nBJetLoose, int nBJetMedium, float mindr_lep_jet, 
		float mindr_tau_jet, float avg_dr_jet, float ptmiss, float mT_lep, float htmiss, float tau_mva,	float tau_pt, 
		float tau_eta, float dr_tau_lep, float mTauTauVis, float mTauTau);
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
  float mindr_tau_jet_;
  float avg_dr_jet_;
  float ptmiss_;
  float mT_lep_;
  float htmiss_;
  float tau_mva_;
  float tau_pt_;
  float tau_eta_;
  float dr_tau_lep_;
  float mTauTauVis_;
  float mTauTau_;
};

#endif
