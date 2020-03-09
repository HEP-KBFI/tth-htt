#ifndef tthAnalysis_HiggsToTauTau_EvtHistManager_3l_1tau_h
#define tthAnalysis_HiggsToTauTau_EvtHistManager_3l_1tau_h

/** \class EvtHistManager_3l_1tau
 *
 * Book and fill histograms for event-level quantities in ttH, H->tautau analysis
 * in 3l_1tau category
 *
 * \author Christian Veelken, Tallin
 *
 */

#include "tthAnalysis/HiggsToTauTau/interface/HistManagerBase.h" // HistManagerBase

#include "tthAnalysis/HiggsToTauTau/interface/MEMOutput_3l_1tau.h" // MEMOutput_3l_1tau

struct EvtHistManager_3l_1tau_Input
{
  std::size_t numElectrons;
  std::size_t numMuons;
  std::size_t numHadTaus;
  std::size_t numJets;
  std::size_t numBJets_loose;
  std::size_t numBJets_medium;
  double mvaOutput_legacy;
  double mTauTauVis1;
  double mTauTauVis2;
  const MEMOutput_3l_1tau * memOutput_3l_1tau;
  double evtWeight;
};

class EvtHistManager_3l_1tau
  : public HistManagerBase
{
 public:
  EvtHistManager_3l_1tau(const edm::ParameterSet & cfg);
  ~EvtHistManager_3l_1tau() {}

  /// book and fill histograms
  void
  bookHistograms(TFileDirectory & dir) override;

  void
  fillHistograms(const EvtHistManager_3l_1tau_Input & variables);

  const TH1 *
  getHistogram_EventCounter() const;

  enum { kOption_undefined, kOption_allHistograms, kOption_minimalHistograms };

 private:
  int era_;

  TH1 * histogram_numElectrons_;
  TH1 * histogram_numMuons_;
  TH1 * histogram_numHadTaus_;
  TH1 * histogram_numJets_;
  TH1 * histogram_numBJets_loose_;
  TH1 * histogram_numBJets_medium_;

  // CV: used to check loss in signal efficiency in case events with high jet and b-jet multiplicity are vetoed
  // to avoid overlap with ttH, H->bb analysis (alternative: ttH, H->bb analysis adds hadronic tau veto)
  TH2 * histogram_numBJets_loose_vs_numJets_;
  TH2 * histogram_numBJets_medium_vs_numJets_;

  TH1 * histogram_mvaOutput_legacy_;
  TH1 * histogram_mTauTauVis_;

  TH1 * histogram_memOutput_isValid_;
  TH1 * histogram_memOutput_errorFlag_;
  TH1 * histogram_memOutput_type_;
  TH1 * histogram_memOutput_logWeight_ttH_;
  TH1 * histogram_memOutput_logWeight_ttZ_;
  TH1 * histogram_memOutput_logWeight_ttH_hww_;
  TH1 * histogram_memOutput_LR_;
  TH1 * histogram_mem_logCPUTime_;
  TH1 * histogram_mem_logRealTime_;

  TH1 * histogram_EventCounter_;
  int option_; // flag to book & fill either full or minimal set of histograms (to reduce memory consumption of hadd jobs)
};

#endif
