#ifndef tthAnalysis_HiggsToTauTau_EvtHistManager_jetToTauFakeRateDYmumu_h
#define tthAnalysis_HiggsToTauTau_EvtHistManager_jetToTauFakeRateDYmumu_h

/** \class EvtHistManager_jetToTauFakeRateDYmumu
 *
 * Book and fill histograms for event-level quantities in the control region 
 * used to measure the jet->tau fake-rate in Drell-Yan (DY) events for the ttH, H->tautau analysis
 *
 * \author Christian Veelken, Tallinn
 *
 */

#include "tthAnalysis/HiggsToTauTau/interface/HistManagerBase.h" // HistManagerBase

class EvtHistManager_jetToTauFakeRateDYmumu
  : public HistManagerBase
{
public:
  EvtHistManager_jetToTauFakeRateDYmumu(const edm::ParameterSet & cfg);
  ~EvtHistManager_jetToTauFakeRateDYmumu() {}

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
                 double m_ll,
                 double evtWeight);

private:
  TH1 * histogram_numElectrons_;
  TH1 * histogram_numMuons_;
  TH1 * histogram_numHadTaus_;
  TH1 * histogram_numJets_;
  TH1 * histogram_numBJets_loose_;
  TH1 * histogram_numBJets_medium_;

  TH1 * histogram_m_ll_;

  TH1 * histogram_EventCounter_;
};

#endif
