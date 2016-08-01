#ifndef tthAnalysis_HiggsToTauTau_EvtHistManager_0l_3tau_h
#define tthAnalysis_HiggsToTauTau_EvtHistManager_0l_3tau_h

/** \class EvtHistManager_0l_3tau
 *
 * Book and fill histograms for event-level quantities in ttH, H->tautau analysis
 * in 0l_3tau category
 *
 * \author Christian Veelken, Tallin
 *
 */

#include "tthAnalysis/HiggsToTauTau/interface/HistManagerBase.h" // HistManagerBase

class EvtHistManager_0l_3tau
  : public HistManagerBase
{
 public:
  EvtHistManager_0l_3tau(edm::ParameterSet const& cfg);
  ~EvtHistManager_0l_3tau() {}

  /// book and fill histograms
  void bookHistograms(TFileDirectory& dir);
  void fillHistograms(int numElectrons, int numMuons, int numHadTaus, int numJets, int numBJets_loose, int numBJets_medium,
		      double mTauTauVis1, double mTauTauVis2, double evtWeight);

 private:
  TH1* histogram_numElectrons_;
  TH1* histogram_numMuons_;
  TH1* histogram_numHadTaus_;
  TH1* histogram_numJets_;
  TH1* histogram_numBJets_loose_;
  TH1* histogram_numBJets_medium_;

  TH1* histogram_mTauTauVis_;

  TH1* histogram_EventCounter_;

  std::vector<TH1*> histograms_;
};

#endif
