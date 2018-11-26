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
                 double mvaOutput_2lss_ttV,
                 double mvaOutput_2lss_ttbar,
                 double mvaDiscr_2lss,
                 double mvaOutput_2los_1tau_ttV,
                 double mvaOutput_2los_1tau_ttbar,
                 double mvaDiscr_2los_1tau,
                 double mTauTauVis,
                 double mvaOutput_2los_1tau_evtLevelSUM_TTH_19Var,
                 double mvaOutput_XGB_Updated,
                 double mvaOutput_XGB_Boosted_AK8,
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

  TH2 * histogram_numBJets_loose_vs_numJets_;  // CV: used to check loss in signal efficiency in case events with high jet and b-jet multiplicity are vetoed
  TH2 * histogram_numBJets_medium_vs_numJets_; //     to avoid overlap with ttH, H->bb analysis (alternative: ttH, H->bb analysis adds hadronic tau veto)

  TH1 * histogram_mvaOutput_2lss_ttV_;
  TH1 * histogram_mvaOutput_2lss_ttbar_;
  TH1 * histogram_mvaDiscr_2lss_;

  TH1 * histogram_mvaOutput_2los_1tau_ttV_;
  TH1 * histogram_mvaOutput_2los_1tau_ttbar_;
  TH1 * histogram_mvaOutput_2los_1tau_SUM_;
  TH1 * histogram_mvaDiscr_2los_1tau_;

  TH1 * histogram_mTauTauVis_;
  TH1 * histogram_EventCounter_;
  TH1 * histogram_mvaOutput_2los_1tau_evtLevelSUM_TTH_19Var_;
  TH1 * histogram_mvaOutput_XGB_Updated_;
  TH1 * histogram_mvaOutput_XGB_Boosted_AK8_;

};

#endif
