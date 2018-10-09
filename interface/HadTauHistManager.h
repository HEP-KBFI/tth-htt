#ifndef tthAnalysis_HiggsToTauTau_HadTauHistManager_h
#define tthAnalysis_HiggsToTauTau_HadTauHistManager_h

/** \class HadTauHistManager
 *
 * Book and fill histograms for hadronic tau decays in ttH, H->tautau analysis
 *
 * \author Christian Veelken, Tallin
 *
 */

#include "tthAnalysis/HiggsToTauTau/interface/HistManagerBase.h" // HistManagerBase
#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTau.h"

class HadTauHistManager
  : public HistManagerBase
{
public:
  HadTauHistManager(const edm::ParameterSet & cfg);
  ~HadTauHistManager() {}

  /// book and fill histograms
  void
  bookHistograms(TFileDirectory & dir) override;

  void
  fillHistograms(const RecoHadTau & hadTau,
                 double evtWeight);

  void
  fillHistograms(const std::vector<const RecoHadTau *> & hadTau_ptrs,
                 double evtWeight);

private:
  TH1 * histogram_pt_;
  TH1 * histogram_eta_;
  TH1 * histogram_phi_;
  TH1 * histogram_decayMode_;
  TH1 * histogram_mass_;
  TH1 * histogram_charge_;
  TH1 * histogram_dz_;
  TH1 * histogram_dxy_;
  
  TH1 * histogram_decayModeFinding_;
  TH1 * histogram_id_mva_dR03_;
  TH1 * histogram_id_mva_dR05_;
  TH1 * histogram_id_cut_dR03_;
  TH1 * histogram_id_cut_dR05_;
  TH1 * histogram_antiElectron_;
  TH1 * histogram_antiMuon_;

  TH1 * histogram_abs_genPdgId_;

  std::vector<TH1 *> histograms_;

  int idx_; // flag to select leading or subleading hadronic tau (set idx to -1 to make plots for all hadronic taus)
};

#endif
