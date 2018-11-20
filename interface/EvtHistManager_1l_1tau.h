#ifndef tthAnalysis_HiggsToTauTau_EvtHistManager_1l_1tau_h
#define tthAnalysis_HiggsToTauTau_EvtHistManager_1l_1tau_h

/** \class EvtHistManager_1l_1tau
 *
 * Book and fill histograms for event-level quantities in ttH, H->tautau analysis
 * in 1l_1tau category
 *
 * \author Christian Veelken, Tallinn
 *
 */

#include "tthAnalysis/HiggsToTauTau/interface/HistManagerBase.h" // HistManagerBase

class EvtHistManager_1l_1tau
  : public HistManagerBase
{
public:
  EvtHistManager_1l_1tau(const edm::ParameterSet & cfg);
  ~EvtHistManager_1l_1tau() {}

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
                 //double mvaOutput_plainKin_ttV,
                 //double mvaOutput_plainKin_tt,
                 //double mvaOutput_plainKin_1B_VT,
                 //double mvaOutput_HTT_SUM_VT,
                 //double mvaOutput_plainKin_SUM_VT,
                 double mTauTauVis,
		 double mTauTau,
		 double Pzeta, double PzetaVis, double PzetaComb,
		 double mT_lep, 
		 double mT_tau,
		 double mbb,
		 double mbb_loose,
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

  // CV: used to check loss in signal efficiency in case events with
  // high jet and b-jet multiplicity are vetoed to avoid overlap with ttH, H->bb analysis
  // (alternative: ttH, H->bb analysis adds hadronic tau veto)
  TH2 * histogram_numBJets_loose_vs_numJets_;
  TH2 * histogram_numBJets_medium_vs_numJets_;

  //TH1 * histogram_mvaOutput_plainKin_ttV_;
  //TH1 * histogram_mvaOutput_plainKin_tt_;
  //TH1 * histogram_mvaOutput_plainKin_1B_VT_;
  //TH1 * histogram_mvaOutput_HTT_SUM_VT_;
  //TH1 * histogram_mvaOutput_HTT_SUM_VT_noRebin_;
  //TH1 * histogram_mvaOutput_plainKin_SUM_VT_;
  //TH1 * histogram_mvaOutput_plainKin_SUM_VT_noRebin_;
  //TH1 * histogram_final_;

  TH1 * histogram_mTauTauVis_;
  TH1 * histogram_mTauTau_;  
  TH1 * histogram_Pzeta_;
  TH1 * histogram_PzetaVis_;
  TH1 * histogram_PzetaMiss_;
  TH1 * histogram_PzetaComb_;
  TH1 * histogram_mT_lep_;
  TH1 * histogram_mT_tau_;
  TH1 * histogram_mbb_;
  TH1 * histogram_mbb_loose_;

  TH1 * histogram_EventCounter_;
};

#endif
