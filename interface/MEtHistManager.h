#ifndef tthAnalysis_HiggsToTauTau_MEtHistManager_h
#define tthAnalysis_HiggsToTauTau_MEtHistManager_h

/** \class MEtHistManager
 *
 * Book and fill histograms for missing transverse momentum and related quantities in ttH, H->tautau analysis
 *
 * \author Christian Veelken, Tallin
 *
 */

#include "DataFormats/Math/interface/LorentzVector.h" // math::PtEtaPhiMLorentzVector

#include "tthAnalysis/HiggsToTauTau/interface/HistManagerBase.h" // HistManagerBase

class MEtHistManager
  : public HistManagerBase
{
 public:
  MEtHistManager(edm::ParameterSet const& cfg);
  ~MEtHistManager() {}

  /// book and fill histograms
  void bookHistograms(TFileDirectory& dir);
  typedef math::PtEtaPhiMLorentzVector LV;
  void fillHistograms(const LV& met_p4, const LV& mht_p4, double met_LD, double evtWeight);

 private:
  TH1* histogram_met_pt_;
  TH1* histogram_met_phi_;
  TH1* histogram_mht_pt_;
  TH1* histogram_mht_phi_;
  
  TH2* histogram_mhtPt_vs_metPt_;

  TH1* histogram_met_LD_;

  std::vector<TH1*> histograms_;
};

#endif
