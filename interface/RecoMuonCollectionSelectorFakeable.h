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
  int era_;
  bool debug_;
  bool set_selection_flags_;

  Double_t min_cone_pt_;    ///< lower cut threshold on cone pT
  Double_t min_lepton_pt_;  ///< lower cut threshold on "raw" lepton pT  
  Double_t max_absEta_;     ///< upper cut threshold on absolute value of eta
  Double_t max_dxy_;        ///< upper cut threshold on d_{xy}, distance in the transverse plane w.r.t PV
  Double_t max_dz_;         ///< upper cut threshold on d_{z}, distance on the z axis w.r.t PV
  Double_t max_relIso_;     ///< upper cut threshold on relative isolation
  Double_t max_sip3d_;      ///< upper cut threshold on significance of IP
  bool apply_looseIdPOG_;   ///< apply (True) or do not apply (False) loose PFMuon id selection
//-------------------------------------------------------------------------------
//--- define cuts that dependent on lepton MVA of ttH multilepton analysis 
//    format: muon fails / passes loose cut on lepton MVA value
  typedef std::vector<Double_t> vDouble_t;  
  Double_t  wp_mvaTTH_;               ///< lepton MVA threshold
  vDouble_t min_jetPtRatio_;          ///< lower cut on ratio of lepton pT to pT of nearby jet
  vDouble_t max_jetBtagCSV_;          ///< upper cut threshold on CSV b-tagging discriminator value of nearby jet
//-------------------------------------------------------------------------------
  bool apply_mediumIdPOG_;  ///< apply (True) or do not apply (False) medium PFMuon id selection
  vDouble_t min_segmentCompatibility_;

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

