#ifndef tthAnalysis_HiggsToTauTau_EvtHistManager_ZZctrl_h
#define tthAnalysis_HiggsToTauTau_EvtHistManager_ZZctrl_h

/** \class EvtHistManager_ZZctrl
 *
 * Book and fill histograms for event-level quantities in ttH multilepton analysis
 * in ZZctrl category
 *
 * \author Christian Veelken, Tallin
 *
 */

#include "tthAnalysis/HiggsToTauTau/interface/HistManagerBase.h" // HistManagerBase

class EvtHistManager_ZZctrl
  : public HistManagerBase
{
 public:
  EvtHistManager_ZZctrl(const edm::ParameterSet & cfg);
  ~EvtHistManager_ZZctrl() {}

  /// book and fill histograms
  void
  bookHistograms(TFileDirectory & dir) override;

  void
  fillHistograms(int numElectrons,
                 int numMuons,
                 int numJets,
                 int numBJets_loose,
                 int numBJets_medium,
                 double evtWeight);

  const TH1 *
  getHistogram_EventCounter() const;

 private:
  TH1 * histogram_numElectrons_;
  TH1 * histogram_numMuons_;
  TH1 * histogram_numJets_;
  TH1 * histogram_numBJets_loose_;
  TH1 * histogram_numBJets_medium_;

  // CV: used to check loss in signal efficiency in case events with high jet and b-jet multiplicity are vetoed
  // to avoid overlap with ttH, H->bb analysis (alternative: ttH, H->bb analysis adds hadronic tau veto)
  TH2 * histogram_numBJets_loose_vs_numJets_;
  TH2 * histogram_numBJets_medium_vs_numJets_;

  TH1 * histogram_EventCounter_;
};

#endif
