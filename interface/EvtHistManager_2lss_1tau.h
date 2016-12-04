#ifndef tthAnalysis_HiggsToTauTau_EvtHistManager_2lss_1tau_h
#define tthAnalysis_HiggsToTauTau_EvtHistManager_2lss_1tau_h

/** \class EvtHistManager_2lss_1tau
 *
 * Book and fill histograms for event-level quantities in ttH, H->tautau analysis
 * in 2lss_1tau category
 *
 * \author Christian Veelken, Tallin
 *
 */

#include "tthAnalysis/HiggsToTauTau/interface/HistManagerBase.h" // HistManagerBase

#include "tthAnalysis/HiggsToTauTau/interface/MEMInterface_2lss_1tau.h" // MEMOutput_2lss_1tau

class EvtHistManager_2lss_1tau
  : public HistManagerBase
{
 public:
  EvtHistManager_2lss_1tau(edm::ParameterSet const& cfg);
  ~EvtHistManager_2lss_1tau() {}

  /// book and fill histograms
  void bookHistograms(TFileDirectory& dir);
  void fillHistograms(int numElectrons, int numMuons, int numHadTaus, int numJets, int numBJets_loose, int numBJets_medium,
		      double mvaOutput_2lss_ttV, double mvaOutput_2lss_ttbar, double mvaDiscr_2lss, 
		      double mvaOutput_2lss_1tau_ttbar_TMVA, double mvaOutput_2lss_1tau_ttbar_sklearn, 
		      double mTauTauVis1, double mTauTauVis2, 
		      const MEMInterface_2lss_1tau::MEMOutput* memOutput_2lss_1tau, double evtWeight);

 private:
  TH1* histogram_numElectrons_;
  TH1* histogram_numMuons_;
  TH1* histogram_numHadTaus_;
  TH1* histogram_numJets_;
  TH1* histogram_numBJets_loose_;
  TH1* histogram_numBJets_medium_;

  TH2* histogram_numBJets_loose_vs_numJets_;  // CV: used to check loss in signal efficiency in case events with high jet and b-jet multiplicity are vetoed
  TH2* histogram_numBJets_medium_vs_numJets_; //     to avoid overlap with ttH, H->bb analysis (alternative: ttH, H->bb analysis adds hadronic tau veto)

  TH1* histogram_mvaOutput_2lss_ttV_;
  TH1* histogram_mvaOutput_2lss_ttbar_;
  TH1* histogram_mvaDiscr_2lss_;

  TH1* histogram_mvaOutput_2lss_1tau_ttbar_TMVA_;
  TH1* histogram_mvaOutput_2lss_1tau_ttbar_sklearn_;

  TH1* histogram_mTauTauVis_;

  TH1* histogram_memOutput_errorFlag_;
  TH1* histogram_memOutput_type_;
  TH1* histogram_memOutput_logWeight_ttH_;
  TH1* histogram_memOutput_logWeight_ttZ_;
  TH1* histogram_memOutput_logWeight_ttZ_Zll_;
  TH1* histogram_memOutput_logWeight_tt_;
  TH1* histogram_memOutput_LR_;
  TH1* histogram_mem_logCPUTime_;
  TH1* histogram_mem_logRealTime_;

  TH1* histogram_EventCounter_;

  std::vector<TH1*> histograms_;
};

#endif
