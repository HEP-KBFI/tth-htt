#ifndef tthAnalysis_HiggsToTauTau_EvtHistManager_2l_2tau_h
#define tthAnalysis_HiggsToTauTau_EvtHistManager_2l_2tau_h

/** \class EvtHistManager_2l_2tau
 *
 * Book and fill histograms for event-level quantities in ttH, H->tautau analysis
 * in 2l_2tau category
 *
 */

#include "tthAnalysis/HiggsToTauTau/interface/HistManagerBase.h" // HistManagerBase

struct EvtHistManager_2l_2tau_Input
{
  std::size_t numElectrons;
  std::size_t numMuons;
  std::size_t numHadTaus;
  std::size_t numJets;
  std::size_t numBJets_loose;
  std::size_t numBJets_medium;
  double mTauTauVis;
  int leptonPairCharge;
  int hadTauPairCharge;
  double evtWeight;
  double mvaOutput_legacy;
};

class EvtHistManager_2l_2tau
  : public HistManagerBase
{
public:
  EvtHistManager_2l_2tau(const edm::ParameterSet & cfg);
  ~EvtHistManager_2l_2tau() {}

  /// book and fill histograms
  void
  bookHistograms(TFileDirectory & dir) override;

  void
  fillHistograms(const EvtHistManager_2l_2tau_Input & variables);

  const TH1 * getHistogram_EventCounter() const { return histogram_EventCounter_; }

  enum { kOption_undefined, kOption_allHistograms, kOption_minimalHistograms };

private:
  TH1 * histogram_numElectrons_;
  TH1 * histogram_numMuons_;
  TH1 * histogram_numHadTaus_;
  TH1 * histogram_numJets_;
  TH1 * histogram_numBJets_loose_;
  TH1 * histogram_numBJets_medium_;

  // CV: used to check loss in signal efficiency in case events with
  // high jet and b-jet multiplicity are vetoed to avoid overlap with ttH, H->bb analysis
  // (alternative: ttH, H->bb analysis adds hadronic tau veto)
  TH2 * histogram_numBJets_loose_vs_numJets_;
  TH2 * histogram_numBJets_medium_vs_numJets_;

  TH1 * histogram_mTauTauVis_;
  TH1 * histogram_leptonPairCharge_;
  TH1 * histogram_hadTauPairCharge_;

  TH1 * histogram_EventCounter_;

  TH1 * histogram_final_;
  int option_; // flag to book & fill either full or minimal set of histograms (to reduce memory consumption of hadd jobs)
};

#endif
