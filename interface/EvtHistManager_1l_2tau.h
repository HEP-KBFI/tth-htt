#ifndef tthAnalysis_HiggsToTauTau_EvtHistManager_1l_2tau_h
#define tthAnalysis_HiggsToTauTau_EvtHistManager_1l_2tau_h

/** \class EvtHistManager_1l_2tau
 *
 * Book and fill histograms for event-level quantities in ttH, H->tautau analysis
 * in 1l_2tau category
 *
 * \author Christian Veelken, Tallin
 *
 */

#include "tthAnalysis/HiggsToTauTau/interface/HistManagerBase.h" // HistManagerBase
#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h"

class EvtHistManager_1l_2tau
  : public HistManagerBase
{
 public:
  EvtHistManager_1l_2tau(edm::ParameterSet const& cfg);
  ~EvtHistManager_1l_2tau() {}

  /// book and fill histograms
  void bookHistograms(TFileDirectory& dir);
  void fillHistograms(int numElectrons, int numMuons, int numHadTaus, int numJets, int numBJets_loose, int numBJets_medium,
    double mvaOutput_1l_2tau_ttbar,
    double mvaOutput_1l_2tau_ttbar_Old,
    double mvaOutput_1l_2tau_ttV,
    double mvaDiscr_1l_2tau,
    double mTauTauVis,
    double evtWeight);

  const TH1* getHistogram_EventCounter() const { return histogram_EventCounter_; }

 private:
  TH1* histogram_numElectrons_;
  TH1* histogram_numMuons_;
  TH1* histogram_numHadTaus_;
  TH1* histogram_numJets_;
  TH1* histogram_numBJets_loose_;
  TH1* histogram_numBJets_medium_;

  TH2* histogram_numBJets_loose_vs_numJets_;  // CV: used to check loss in signal efficiency in case events with high jet and b-jet multiplicity are vetoed
  TH2* histogram_numBJets_medium_vs_numJets_; //     to avoid overlap with ttH, H->bb analysis (alternative: ttH, H->bb analysis adds hadronic tau veto)

  TH1* histogram_mvaOutput_1l_2tau_ttbar_;
  TH1* histogram_mvaOutput_1l_2tau_ttbar_Old_;
  TH1* histogram_mvaOutput_1l_2tau_ttbar_Old_5bins_;

  TH1* histogram_mvaOutput_1l_2tau_ttV_;
  TH1* histogram_mvaDiscr_1l_2tau_;

  TH1* histogram_mTauTauVis_;

  TH1* histogram_EventCounter_;

};

#endif
