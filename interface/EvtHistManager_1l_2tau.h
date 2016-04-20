#ifndef tthAnalysis_HiggsToTauTau_EvtHistManager_1l_2tau_h
#define tthAnalysis_HiggsToTauTau_EvtHistManager_1l_2tau_h

/** \class EvtHistManager_1l_2tau
 *
 * Book and fill histograms for event-level quantities in ttH, H->tautau analysis
 * in 1l_2tau category
 *
 * \author Christian Veelken, Tallin
 *
 */

#include "tthAnalysis/HiggsToTauTau/interface/HistManagerBase.h" // HistManagerBase

class EvtHistManager_1l_2tau
  : public HistManagerBase
{
 public:
  EvtHistManager_1l_2tau(edm::ParameterSet const& cfg);
  ~EvtHistManager_1l_2tau() {}

  /// book and fill histograms
  void bookHistograms(TFileDirectory& dir);
  void fillHistograms(int numJets, double mTauTauVis, double evtWeight);

 private:
  TH1* histogram_numJets_;

  TH1* histogram_mTauTauVis_;

  std::vector<TH1*> histograms_;
};

#endif
