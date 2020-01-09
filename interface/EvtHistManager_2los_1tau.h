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
  fillHistograms(int numElectrons,
                 int numMuons,
                 int numHadTaus,
                 int numJets,
                 int numBJets_loose,
                 int numBJets_medium,
                 double mTauTauVis,
                 double mvaOutput_legacy,
                 double evtWeight);

  const TH1 *
  getHistogram_EventCounter() const;

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

};

#endif
