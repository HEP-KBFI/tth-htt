#ifndef tthAnalysis_HiggsToTauTau_EvtHistManager_2los_1tau_h
#define tthAnalysis_HiggsToTauTau_EvtHistManager_2los_1tau_h

/** \class EvtHistManager_2los_1tau
 *
 * Book and fill histograms for event-level quantities in ttH, H->tautau analysis
 * in 2los_1tau category
 *
 * \author Christian Veelken, Tallinn
 *
 */

#include "tthAnalysis/HiggsToTauTau/interface/HistManagerBase.h" // HistManagerBase

struct EvtHistManager_2los_1tau_Input
{
  std::size_t numElectrons;
  std::size_t numMuons;
  std::size_t numHadTaus;
  std::size_t numJets;
  std::size_t numBJets_loose;
  std::size_t numBJets_medium;
  double mTauTauVis;
  double mvaOutput_legacy;
  double evtWeight;
};

class EvtHistManager_2los_1tau
  : public HistManagerBase
{
public:
  EvtHistManager_2los_1tau(const edm::ParameterSet & cfg);
  ~EvtHistManager_2los_1tau() {}

  /// book and fill histograms
  void
  bookHistograms(TFileDirectory & dir) override;

  void
  fillHistograms(const EvtHistManager_2los_1tau_Input & variables);

  const TH1 *
  getHistogram_EventCounter() const;

  enum { kOption_undefined, kOption_allHistograms, kOption_minimalHistograms };

private:
  TH1 * histogram_numElectrons_;
  TH1 * histogram_numMuons_;
  TH1 * histogram_numHadTaus_;
  TH1 * histogram_numJets_;
  TH1 * histogram_numBJets_loose_;
  TH1 * histogram_numBJets_medium_;

  TH1 * histogram_mTauTauVis_;
  TH1 * histogram_EventCounter_;
  TH1 * histogram_mvaOutput_legacy_;
  int option_; // flag to book & fill either full or minimal set of histograms (to reduce memory consumption of hadd jobs)
};

#endif
