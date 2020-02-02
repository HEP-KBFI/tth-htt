#ifndef tthAnalysis_HiggsToTauTau_RecoMuonCollectionSelectorLoose_h
#define tthAnalysis_HiggsToTauTau_RecoMuonCollectionSelectorLoose_h

#include "tthAnalysis/HiggsToTauTau/interface/ParticleCollectionSelector.h" // ParticleCollectionSelector
#include "tthAnalysis/HiggsToTauTau/interface/RecoMuon.h" // RecoMuon

class RecoMuonSelectorLoose
{
public:
  explicit
  RecoMuonSelectorLoose(int era,
                        int index = -1,
                        bool debug = false,
                        bool set_selection_flags = true);

  void set_min_pt(double min_pt);

  /**
   * @brief Check if muon given as function argument passes "loose" muon selection, defined in Table 12 of AN-2015/321
   * @return True if muon passes selection; false otherwise
   */
  bool
  operator()(const RecoMuon & muon) const;

protected:
  const int era_;
  bool debug_;
  bool set_selection_flags_;

  Double_t min_pt_;        ///< lower cut threshold on pT
  const Double_t max_absEta_;    ///< upper cut threshold on absolute value of eta
  const Double_t max_dxy_;       ///< upper cut threshold on d_{xy}, distance in the transverse plane w.r.t PV
  const Double_t max_dz_;        ///< upper cut threshold on d_{z}, distance on the z axis w.r.t PV
  const Double_t max_relIso_;    ///< upper cut threshold on relative isolation
  const Double_t max_sip3d_;     ///< upper cut threshold on significance of IP
  const bool apply_looseIdPOG_;  ///< apply (True) or do not apply (False) loose PFMuon id selection
  const bool apply_mediumIdPOG_; ///< apply (True) or do not apply (False) medium PFMuon id selection
  const bool apply_tightCharge_; ///< apply (True) or do not apply (False) tight charge cut
};

typedef ParticleCollectionSelector<RecoMuon, RecoMuonSelectorLoose> RecoMuonCollectionSelectorLoose;

#endif // tthAnalysis_HiggsToTauTau_RecoMuonCollectionSelectorLoose_h
