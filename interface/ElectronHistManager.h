#ifndef tthAnalysis_HiggsToTauTau_ElectronHistManager_h
#define tthAnalysis_HiggsToTauTau_ElectronHistManager_h

/** \class ElectronHistManager
 *
 * Book and fill histograms for electrons in ttH, H->tautau analysis
 *
 * \author Christian Veelken, Tallinn
 *
 */

#include "tthAnalysis/HiggsToTauTau/interface/HistManagerBase.h" // HistManagerBase
#include "tthAnalysis/HiggsToTauTau/interface/RecoElectron.h" // RecoElectron

class ElectronHistManager
  : public HistManagerBase
{
public:
  ElectronHistManager(const edm::ParameterSet & cfg);
  ~ElectronHistManager() {}

  /// book and fill histograms
  void
  bookHistograms(TFileDirectory & dir) override;

  void
  fillHistograms(const RecoElectron & electron,
                 double evtWeight);

  void
  fillHistograms(const std::vector<const RecoElectron *> & electrons,
                 double evtWeight);

private:
  TH1 * histogram_pt_;
  TH1 * histogram_eta_;
  TH1 * histogram_phi_;
  TH1 * histogram_charge_;

  TH1 * histogram_dxy_;
  TH1 * histogram_dz_;
  TH1 * histogram_relIso_;
  TH1 * histogram_sip3d_;
  TH1 * histogram_mvaRawTTH_;
  TH1 * histogram_jetPtRatio_;
  TH1 * histogram_jetBtagCSV_;
  TH1 * histogram_tightCharge_;
  TH1 * histogram_mvaRawPOG_;
  TH1 * histogram_mvaRawPOG_HZZ_;
  TH1 * histogram_sigmaEtaEta_;
  TH1 * histogram_HoE_;
  TH1 * histogram_deltaEta_;
  TH1 * histogram_deltaPhi_;
  TH1 * histogram_OoEminusOoP_;
  TH1 * histogram_nLostHits_;
  TH1 * histogram_passesConversionVeto_;

  TH1 * histogram_abs_genPdgId_;
  TH1 * histogram_gen_times_recCharge_;

  int idx_; // flag to select leading or subleading electron (set idx to -1 to make plots for all electrons)
};

#endif
