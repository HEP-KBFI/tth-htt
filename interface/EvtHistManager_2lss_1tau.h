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
#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h"

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
		      double mvaOutput_2lss_1tau_ttV, double mvaOutput_2lss_1tau_ttbar, double mvaDiscr_2lss_1tau,
		      double mvaOutput_2lss_1tau_ttV_wMEM, double mvaOutput_2lss_1tau_ttbar_wMEM, double mvaDiscr_2lss_1tau_wMEM,
		      double mvaOutput_Hj_tagger, double mvaOutput_Hjj_tagger,
		      double mTauTauVis1, double mTauTauVis2,
		      const MEMOutput_2lss_1tau* memOutput_2lss_1tau, double memDiscr, double evtWeight,
          double mvaOutput_2lss_oldVar_tt,
          double mvaOutput_2lss_oldVar_ttV,
          double mvaOutput_2lss_HTT_tt,
          double mvaOutput_2lss_noHTT_tt,
          double mvaOutput_2lss_noHTT_ttV,
          double mvaOutput_2lss_HTT_LepID_tt,
          double oldVar_from20_to_12,
          double oldVar_from20_to_7,
          double HTT_2D[9][3],
          double noHTT_2D[9][3]
        );

  const TH1* getHistogram_EventCounter() const { return histogram_EventCounter_; }

 private:
  int era_;

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

  TH1* histogram_mvaOutput_2lss_1tau_ttV_;
  TH1* histogram_mvaOutput_2lss_1tau_ttbar_;
  TH1* histogram_mvaDiscr_2lss_1tau_;
  TH1* histogram_mvaOutput_2lss_1tau_ttV_wMEM_;
  TH1* histogram_mvaOutput_2lss_1tau_ttbar_wMEM_;
  TH1* histogram_mvaDiscr_2lss_1tau_wMEM_;

  TH1* histogram_mvaOutput_Hj_tagger_;
  TH1* histogram_mvaOutput_Hjj_tagger_;

  TH1* histogram_mTauTauVis_;

  TH1* histogram_memOutput_isValid_;
  TH1* histogram_memOutput_errorFlag_;
  TH1* histogram_memOutput_type_;
  TH1* histogram_memOutput_logWeight_ttH_;
  TH1* histogram_memOutput_logWeight_ttZ_;
  TH1* histogram_memOutput_logWeight_ttZ_Zll_;
  TH1* histogram_memOutput_logWeight_tt_;
  TH1* histogram_memOutput_LR_;
  TH1* histogram_memOutput_LR_type0_;
  TH1* histogram_memOutput_LR_type1_;
  TH1* histogram_memDiscr_;
  TH1* histogram_memDiscr_type0_;
  TH1* histogram_memDiscr_type1_;
  TH1* histogram_mem_logCPUTime_;
  TH1* histogram_mem_logRealTime_;

  TH1* histogram_EventCounter_;

  TH1* histogram_mvaOutput_2lss_oldVar_tt_;
  TH1* histogram_mvaOutput_2lss_oldVar_ttV_;
  TH1* histogram_mvaOutput_2lss_HTT_tt_;
  TH1* histogram_mvaOutput_2lss_noHTT_tt_;
  TH1* histogram_mvaOutput_2lss_noHTT_ttV_;
  TH1* histogram_mvaOutput_2lss_HTT_LepID_tt_;

  TH1* hist_oldVar_from20_to_12_;
  TH1* hist_oldVar_from20_to_7_;
  //std::vector<std::vector<TH1*>> hist_HTT_2D_(int 3, int 9); // nbinsStart.size()
  //std::vector<std::vector<TH1*>> hist_noHTT_2D_(int 3, int 9);
  TH1* hist_HTT_2D_[9][3];
  TH1* hist_noHTT_2D_[9][3];

  std::vector<TH1*> histograms_;
};

#endif
