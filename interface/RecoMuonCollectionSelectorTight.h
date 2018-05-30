#ifndef tthAnalysis_HiggsToTauTau_RecoMuonCollectionSelectorTight_h
#define tthAnalysis_HiggsToTauTau_RecoMuonCollectionSelectorTight_h

#include "tthAnalysis/HiggsToTauTau/interface/ParticleCollectionSelector.h" // ParticleCollectionSelector
#include "tthAnalysis/HiggsToTauTau/interface/RecoMuon.h" // RecoMuon

class RecoMuonSelectorTight
{
public:
  explicit
  RecoMuonSelectorTight(int era,
                        int index = -1,
                        bool debug = false,
                        bool set_selection_flags = true);

  void set_min_mvaTTH(double min_mvaTTH);
  double get_min_mvaTTH() const;

  void
  set_selection_flags(bool selection_flags);

  /**
   * @brief Check if muon given as function argument passes "tight" muon selection, defined in Table 12 of AN-2015/321
   * @return True if muon passes selection; false otherwise
   */
  bool
  operator()(const RecoMuon & muon) const;

protected:
  int era_;
  bool set_selection_flags_;
  int index_;
  bool debug_;

  Double_t min_pt_;         ///< lower cut threshold on pT
  Double_t max_absEta_;     ///< upper cut threshold on absolute value of eta
  Double_t max_dxy_;        ///< upper cut threshold on d_{xy}, distance in the transverse plane w.r.t PV
  Double_t max_dz_;         ///< upper cut threshold on d_{z}, distance on the z axis w.r.t PV
  Double_t max_relIso_;     ///< upper cut threshold on relative isolation
  Double_t max_sip3d_;      ///< upper cut threshold on significance of IP
  bool apply_looseIdPOG_;   ///< apply (True) or do not apply (False) loose PFMuon id selection
  Double_t max_jetBtagCSV_; ///< upper cut threshold on CSV b-tagging discriminator value of nearby jet
  bool apply_mediumIdPOG_;  ///< apply (True) or do not apply (False) medium PFMuon id selection
  Double_t min_mvaTTH_;     ///< lower cut threshold on lepton MVA of ttH multilepton analysis
};

class RecoMuonCollectionSelectorTight
  : public ParticleCollectionSelector<RecoMuon, RecoMuonSelectorTight>
{
public:
  explicit
  RecoMuonCollectionSelectorTight(int era,
                                  int index = -1,
                                  bool debug = false,
                                  bool set_selection_flags = true);
  ~RecoMuonCollectionSelectorTight() {}
};

#endif // tthAnalysis_HiggsToTauTau_RecoMuonCollectionSelectorTight_h
