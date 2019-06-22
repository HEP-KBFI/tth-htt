#ifndef tthAnalysis_HiggsToTauTau_RecoMuonCollectionSelectorFakeable_h
#define tthAnalysis_HiggsToTauTau_RecoMuonCollectionSelectorFakeable_h

#include "tthAnalysis/HiggsToTauTau/interface/ParticleCollectionSelector.h" // ParticleCollectionSelector
#include "tthAnalysis/HiggsToTauTau/interface/RecoMuon.h" // RecoMuon

class RecoMuonSelectorFakeable
{
public:
  explicit
  RecoMuonSelectorFakeable(int era,
                           int index = -1,
                           bool debug = false,
                           bool set_selection_flags = true);

  /**
   * @brief Check if muon given as function argument passes "fakeable" muon selection, defined in Table 12 of AN-2015/321
   * @return True if muon passes selection; false otherwise
   */
  bool
  operator()(const RecoMuon & muon) const;

  void set_mvaTTH_wp(double mvaTTH_wp);
  double get_mvaTTH_wp() const;

  void
  set_selection_flags(bool selection_flags);

protected:
  const int era_;
  bool debug_;
  bool set_selection_flags_;

  const Double_t min_cone_pt_;    ///< lower cut threshold on cone pT
  const Double_t min_lepton_pt_;  ///< lower cut threshold on "raw" lepton pT
  const Double_t max_absEta_;     ///< upper cut threshold on absolute value of eta
  const Double_t max_dxy_;        ///< upper cut threshold on d_{xy}, distance in the transverse plane w.r.t PV
  const Double_t max_dz_;         ///< upper cut threshold on d_{z}, distance on the z axis w.r.t PV
  const Double_t max_relIso_;     ///< upper cut threshold on relative isolation
  const Double_t max_sip3d_;      ///< upper cut threshold on significance of IP
  const bool apply_looseIdPOG_;   ///< apply (True) or do not apply (False) loose PFMuon id selection
  const bool apply_mediumIdPOG_;  ///< apply (True) or do not apply (False) medium PFMuon id selection

  Double_t wp_mvaTTH_;      ///< lepton MVA threshold
  const Double_t min_jetPtRatio_; ///< lower cut on ratio of lepton pT to pT of nearby jet
  const Double_t min_jetBtagCSV_; ///< lower cut threshold on b-tagging discriminator value of nearby jet
  const Double_t max_jetBtagCSV_; ///< upper cut threshold on b-tagging discriminator value of nearby jet
//-------------------------------------------------------------------------------
  const Double_t smoothBtagCut_minPt_;
  const Double_t smoothBtagCut_maxPt_;
  const Double_t smoothBtagCut_ptDiff_;

  double
  smoothBtagCut(double assocJet_pt) const;
};

class RecoMuonCollectionSelectorFakeable
  : public ParticleCollectionSelector<RecoMuon, RecoMuonSelectorFakeable>
{
public:
  explicit
  RecoMuonCollectionSelectorFakeable(int era,
                                     int index = -1,
                                     bool debug = false,
                                     bool set_selection_flags = true);
  ~RecoMuonCollectionSelectorFakeable() {}
};

#endif // tthAnalysis_HiggsToTauTau_RecoMuonCollectionSelectorFakeable_h

