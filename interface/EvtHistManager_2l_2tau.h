#ifndef tthAnalysis_HiggsToTauTau_EvtHistManager_2l_2tau_h
#define tthAnalysis_HiggsToTauTau_EvtHistManager_2l_2tau_h

/** \class EvtHistManager_2l_2tau
 *
 * Book and fill histograms for event-level quantities in ttH, H->tautau analysis
 * in 2l_2tau category
 *
 */

#include "tthAnalysis/HiggsToTauTau/interface/HistManagerBase.h" // HistManagerBase

class EvtHistManager_2l_2tau
: public HistManagerBase
{
 public:
  EvtHistManager_2l_2tau(edm::ParameterSet const& cfg);
  ~EvtHistManager_2l_2tau() {}

  /// book and fill histograms
  void bookHistograms(TFileDirectory& dir);
  void fillHistograms(int numElectrons, int numMuons, int numHadTaus, int numJets, int numBJets_loose, int numBJets_medium,
		      double mvaOutput_2l_2tau_ttV, double mvaOutput_2l_2tau_ttbar, double mvaDiscr_2l_2tau,
		      double mTauTauVis, double leptonPairCharge, double hadTauPairCharge, double evtWeight,
          double mvaOutput_noHTT_tt, double mvaOutput_noHTT_ttV,
          double mvaOutput_noHTT_SUM_M, double mvaOutput_noHTT_SUM_T, double mvaOutput_noHTT_SUM_VT,
          double mvaOutput_noHTT_1B_M, double mvaOutput_noHTT_1B_T, double mvaOutput_noHTT_1B_VT
        );

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

  TH1* histogram_mvaOutput_2l_2tau_ttV_;
  TH1* histogram_mvaOutput_2l_2tau_ttbar_;
  TH1* histogram_mvaDiscr_2l_2tau_;

  TH1* histogram_mTauTauVis_;
  TH1* histogram_leptonPairCharge_;
  TH1* histogram_hadTauPairCharge_;

  TH1* histogram_EventCounter_;

  TH1* histogram_mvaOutput_noHTT_tt_;
  TH1* histogram_mvaOutput_noHTT_ttV_;
  TH1* histogram_mvaOutput_noHTT_SUM_M_;
  TH1* histogram_mvaOutput_noHTT_SUM_T_;
  TH1* histogram_mvaOutput_noHTT_SUM_VT_;
  TH1* histogram_mvaOutput_noHTT_1B_M_;
  TH1* histogram_mvaOutput_noHTT_1B_T_;
  TH1* histogram_mvaOutput_noHTT_1B_VT_;
};

#endif
