#ifndef tthAnalysis_HiggsToTauTau_EvtHistManager_2lss_1tau_h
#define tthAnalysis_HiggsToTauTau_EvtHistManager_2lss_1tau_h

/** \class EvtHistManager_2lss_1tau
 *
 * Book and fill histograms for event-level quantities in ttH, H->tautau analysis
 * in 2lss_1tau category
 *
 * \author Christian Veelken, Tallin
 *
 */

#include "tthAnalysis/HiggsToTauTau/interface/HistManagerBase.h" // HistManagerBase

class EvtHistManager_2lss_1tau
  : public HistManagerBase
{
 public:
  EvtHistManager_2lss_1tau(edm::ParameterSet const& cfg);
  ~EvtHistManager_2lss_1tau() {}

  /// book and fill histograms
  void bookHistograms(TFileDirectory& dir);
  void fillHistograms(double mvaOutput_2lss_ttV, double mvaOutput_2lss_ttbar, double mvaDiscr_2lss, double evtWeight);

 private:
  TH1* histogram_mvaOutput_2lss_ttV_;
  TH1* histogram_mvaOutput_2lss_ttbar_;
  TH1* histogram_mvaDiscr_2lss_;

  std::vector<TH1*> histograms_;
};

#endif
