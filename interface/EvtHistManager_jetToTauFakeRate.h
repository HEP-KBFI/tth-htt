#ifndef tthAnalysis_HiggsToTauTau_EvtHistManager_jetToTauFakeRate_h
#define tthAnalysis_HiggsToTauTau_EvtHistManager_jetToTauFakeRate_h

/** \class EvtHistManager_jetToTauFakeRate
 *
 * Book and fill histograms for event-level quantities in the control region 
 * used to measure the jet->tau fake-rate in the ttH, H->tautau analysis
 *
 * \author Christian Veelken, Tallin
 *
 */

#include "tthAnalysis/HiggsToTauTau/interface/HistManagerBase.h" // HistManagerBase

class EvtHistManager_jetToTauFakeRate
  : public HistManagerBase
{
 public:
  EvtHistManager_jetToTauFakeRate(edm::ParameterSet const& cfg);
  ~EvtHistManager_jetToTauFakeRate() {}

  /// book and fill histograms
  void bookHistograms(TFileDirectory& dir);
  void fillHistograms(int numJets, double evtWeight);

 private:
  TH1* histogram_numJets_;

  TH1* histogram_EventCounter_;

  std::vector<TH1*> histograms_;
};

#endif
