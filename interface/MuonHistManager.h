#ifndef tthAnalysis_HiggsToTauTau_MuonHistManager_h
#define tthAnalysis_HiggsToTauTau_MuonHistManager_h

/** \class MuonHistManager
 *
 * Book and fill histograms for muons in ttH, H->tautau analysis
 *
 * \author Christian Veelken, Tallin
 *
 */

#include "tthAnalysis/HiggsToTauTau/interface/HistManagerBase.h" // HistManagerBase
#include "tthAnalysis/HiggsToTauTau/interface/RecoMuon.h" // RecoMuon

class MuonHistManager
  : public HistManagerBase
{
public:
  MuonHistManager(const edm::ParameterSet & cfg);
  ~MuonHistManager() {}

  /// book and fill histograms
  void
  bookHistograms(TFileDirectory & dir) override;

  void
  fillHistograms(const RecoMuon & muon,
                 double evtWeight);

  void
  fillHistograms(const std::vector<const RecoMuon *> & muons,
                 double evtWeight);

  /// flag to book & fill either minimal (cone_pt, eta, phi) or full (incl. muon ID variables) set of histograms 
  /// 
  /// Note: use kOption_minimalHistograms whenever possible, to reduce memory consumption of hadd jobs
  enum { kOption_undefined, kOption_allHistograms, kOption_minimalHistograms };

private:
  TH1 * histogram_cone_pt_;
  TH1 * histogram_eta_;
  TH1 * histogram_phi_;
  TH1 * histogram_abs_genPdgId_;

  TH1 * histogram_pt_;
  TH1 * histogram_assocJet_pt_;
  TH1 * histogram_charge_;
  TH1 * histogram_dxy_;
  TH1 * histogram_dz_;
  TH1 * histogram_relIso_;
  TH1 * histogram_sip3d_;
  TH1 * histogram_mvaRawTTH_;
  TH1 * histogram_jetPtRatio_;
  TH1 * histogram_jetBtagCSV_;
  TH1 * histogram_tightCharge_;
  TH1 * histogram_passesLooseIdPOG_;
  TH1 * histogram_passesMediumIdPOG_;
  TH1 * histogram_gen_times_recCharge_;

  std::vector<TH1 *> histograms_;

  int option_; // flag to book & fill either full or minimal set of histograms (to reduce memory consumption of hadd jobs)

  int idx_; // flag to select leading or subleading muon (set idx to -1 to make plots for all muons)
};

#endif
