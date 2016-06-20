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
  void fillHistograms(int numElectrons, int numMuons, int numHadTaus, int numJets, int numBJets_loose, int numBJets_medium,
		      double mvaOutput_2los_ttV, double mvaOutput_2los_ttbar, double mvaDiscr_2los, double evtWeight);

 private:
  TH1* histogram_numElectrons_;
  TH1* histogram_numMuons_;
  TH1* histogram_numHadTaus_;
  TH1* histogram_numJets_;
  TH1* histogram_numBJets_loose_;
  TH1* histogram_numBJets_medium_;

  TH1* histogram_mvaOutput_2los_ttV_;
  TH1* histogram_mvaOutput_2los_ttbar_;
  TH1* histogram_mvaDiscr_2los_;

  TH1* histogram_EventCounter_;

  std::vector<TH1*> histograms_;
};

#endif
