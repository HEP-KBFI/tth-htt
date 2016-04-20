#ifndef tthAnalysis_HiggsToTauTau_EvtHistManager_2los_1tau_h
#define tthAnalysis_HiggsToTauTau_EvtHistManager_2los_1tau_h

/** \class EvtHistManager_2los_1tau
 *
 * Book and fill histograms for event-level quantities in ttH, H->tautau analysis
 * in 2los_1tau category
 *
 * \author Christian Veelken, Tallin
 *
 */

#include "tthAnalysis/HiggsToTauTau/interface/HistManagerBase.h" // HistManagerBase

class EvtHistManager_2los_1tau
  : public HistManagerBase
{
 public:
  EvtHistManager_2los_1tau(edm::ParameterSet const& cfg);
  ~EvtHistManager_2los_1tau() {}

  /// book and fill histograms
  void bookHistograms(TFileDirectory& dir);
  void fillHistograms(double mvaOutput_2los_ttV, double mvaOutput_2los_ttbar, double mvaDiscr_2los, int numJets, double evtWeight);

 private:
  TH1* histogram_mvaOutput_2los_ttV_;
  TH1* histogram_mvaOutput_2los_ttbar_;
  TH1* histogram_mvaDiscr_2los_;

  TH1* histogram_numJets_;

  std::vector<TH1*> histograms_;
};

#endif
