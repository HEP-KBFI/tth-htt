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
  EvtHistManager_2lss_1tau(const edm::ParameterSet & cfg);
  ~EvtHistManager_2lss_1tau() {}

  void
  bookHistograms(TFileDirectory & dir) override;

  void
  integralHistograms() const;

  void
  fillHistograms(int numElectrons,
                 int numMuons,
                 int numHadTaus,
                 int numJets,
                 int numBJets_loose,
                 int numBJets_medium,
                 const std::vector<TH2 *> & oldVarA,
                 const std::vector<TH2 *> & HTT,
                 const std::vector<TH2 *> & noHTT,
                 const std::vector<TH2 *> & HTTMEM,
                 double evtWeight,
                 double mvaOutput_2lss_ttV,
                 double mvaOutput_2lss_ttbar,
                 double mvaDiscr_2lss,
                 double mvaOutput_2lss_1tau_ttV,
                 double mvaOutput_2lss_1tau_ttbar,
                 double mvaDiscr_2lss_1tau,
                 double mvaOutput_2lss_1tau_ttV_wMEM,
                 double mvaOutput_2lss_1tau_ttbar_wMEM,
                 double mvaDiscr_2lss_1tau_wMEM,
                 double mvaOutput_Hj_tagger,
                 double mvaOutput_Hjj_tagger,
                 double mTauTauVis1,
                 double mTauTauVis2,
                 double memOutput_LR,
                 double memDiscr,
                 // XGB training 1D
                 double mvaOutput_2lss_oldVarA_tt,
                 double mvaOutput_2lss_oldVarA_ttV,
                 double mvaOutput_2lss_noHTT_tt,
                 double mvaOutput_2lss_noHTT_ttV,
                 double mvaOutput_2lss_HTT_tt,
                 double mvaOutput_2lss_HTTMEM_tt,
                 double mvaOutput_2lss_HTTMEM_ttV,
                 double mvaOutput_2lss_HTT_LepID_tt,
                 // XGB training, joint
                 double mvaOutput_2lss_HTTMEM_1B,
                 double mvaOutput_2lss_HTT_1B,
                 double mvaOutput_2lss_noHTT_1B,
                 double mvaOutput_2lss_oldVarA_1B,
                 double mvaOutput_2lss_oldVarA_2MEM,
                 double mvaOutput_2lss_noHTT_2MEM,
                 double mvaOutput_2lss_noHTT_2HTT);

  const TH1 *
  getHistogram_EventCounter() const;

 private:
  int era_;

  const std::array<Int_t, 6> nbinsTarget_;
  const std::array<Int_t, 2> nbinsStart_;

  TH1 * histogram_numElectrons_;
  TH1 * histogram_numMuons_;
  TH1 * histogram_numHadTaus_;
  TH1 * histogram_numJets_;
  TH1 * histogram_numBJets_loose_;
  TH1 * histogram_numBJets_medium_;

  // CV: used to check loss in signal efficiency in case events with
  // high jet and b-jet multiplicity are vetoed to avoid overlap with ttH, H->bb analysis
  // (alternative: ttH, H->bb analysis adds hadronic tau veto)
  TH2 * histogram_numBJets_loose_vs_numJets_;
  TH2 * histogram_numBJets_medium_vs_numJets_;

  TH1 * histogram_mvaOutput_2lss_ttV_;
  TH1 * histogram_mvaOutput_2lss_ttbar_;
  TH1 * histogram_mvaDiscr_2lss_;

  TH1 * histogram_mvaOutput_2lss_1tau_ttV_;
  TH1 * histogram_mvaOutput_2lss_1tau_ttbar_;
  TH1 * histogram_mvaDiscr_2lss_1tau_;
  TH1 * histogram_mvaOutput_2lss_1tau_ttV_wMEM_;
  TH1 * histogram_mvaOutput_2lss_1tau_ttbar_wMEM_;
  TH1 * histogram_mvaDiscr_2lss_1tau_wMEM_;

  TH1 * histogram_mvaOutput_Hj_tagger_;
  TH1 * histogram_mvaOutput_Hjj_tagger_;

  TH1 * histogram_mTauTauVis1_;
  TH1 * histogram_mTauTauVis_;
  TH1 * histogram_mTauTauVis2_;
  TH1 * histogram_memOutput_LR_;
  TH1 * histogram_memDiscr_;

  TH1 * histogram_EventCounter_;

  TH1 * histogram_mvaOutput_2lss_oldVarA_tt_;
  TH1 * histogram_mvaOutput_2lss_oldVarA_ttV_;
  TH1 * histogram_mvaOutput_2lss_noHTT_tt_;
  TH1 * histogram_mvaOutput_2lss_noHTT_ttV_;
  TH1 * histogram_mvaOutput_2lss_HTT_tt_;
  TH1 * histogram_mvaOutput_2lss_HTTMEM_tt_;
  TH1 * histogram_mvaOutput_2lss_HTTMEM_ttV_;
  TH1 * histogram_mvaOutput_2lss_HTT_LepID_tt_;

  TH1 * histogram_mvaOutput_2lss_HTTMEM_1B_;
  TH1 * histogram_mvaOutput_2lss_HTT_1B_;
  TH1 * histogram_mvaOutput_2lss_noHTT_1B_;
  TH1 * histogram_mvaOutput_2lss_oldVarA_1B_;
  TH1 * histogram_mvaOutput_2lss_oldVarA_2MEM_;
  TH1 * histogram_mvaOutput_2lss_noHTT_2MEM_;
  TH1 * histogram_mvaOutput_2lss_noHTT_2HTT_;

  std::vector<TH1 *> hist_oldVarA_2D_;
  std::vector<TH1 *> hist_HTT_2D_;
  std::vector<TH1 *> hist_HTTMEM_2D_;
  std::vector<TH1 *> hist_noHTT_2D_;
};

#endif
