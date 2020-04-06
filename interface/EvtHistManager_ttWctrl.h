#ifndef tthAnalysis_HiggsToTauTau_EvtHistManager_ttWctrl_h
#define tthAnalysis_HiggsToTauTau_EvtHistManager_ttWctrl_h

/** \class EvtHistManager_ttWctrl
 *
 * Book and fill histograms for event-level quantities in ttH, H->tautau analysis
 * in control region enriched in ttW background
 *
 * \author Christian Veelken, Tallinn
 *
 */

#include "tthAnalysis/HiggsToTauTau/interface/HistManagerBase.h"      // HistManagerBase
#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // Era

class EvtHistManager_ttWctrl
  : public HistManagerBase
{
 public:
  EvtHistManager_ttWctrl(const edm::ParameterSet & cfg);
  ~EvtHistManager_ttWctrl() {}

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
                 double mvaOutput_2lss_ttV,
                 double mvaOutput_2lss_ttbar,
                 double mvaDiscr_2lss,
                 double sumLeptonPt,
                 double evtWeight);

 private:
  Era era_;

  TH1 * histogram_numElectrons_;
  TH1 * histogram_numMuons_;
  TH1 * histogram_numLeptons_;
  TH1 * histogram_numHadTaus_;
  TH1 * histogram_numJets_;
  TH1 * histogram_numBJets_loose_;
  TH1 * histogram_numBJets_medium_;

  TH1 * histogram_mvaOutput_2lss_ttV_;
  TH1 * histogram_mvaOutput_2lss_ttbar_;
  TH1 * histogram_mvaDiscr_2lss_;

  TH1 * histogram_sumLeptonPt_;

  TH1 * histogram_EventCounter_;
};

#endif
