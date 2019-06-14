#ifndef tthAnalysis_HiggsToTauTau_RecoElectronCollectionSelectorFakeable_h
#define tthAnalysis_HiggsToTauTau_RecoElectronCollectionSelectorFakeable_h

#include "tthAnalysis/HiggsToTauTau/interface/ParticleCollectionSelector.h" // ParticleCollectionSelector
#include "tthAnalysis/HiggsToTauTau/interface/RecoElectron.h" // RecoElectron

class RecoElectronSelectorFakeable
{
public:
  explicit
  RecoElectronSelectorFakeable(int era,
                               int index = -1,
                               bool debug = false,
                               bool set_selection_flags = true);
  ~RecoElectronSelectorFakeable() {}

  // enable/disable cuts on electron ID variables to mimic electron ID cuts applied by single electron trigger 
  void enable_offline_e_trigger_cuts();
  void disable_offline_e_trigger_cuts();

  void set_mvaTTH_wp(double mvaTTH_wp);
  double get_mvaTTH_wp() const;

  void set_selection_flags(bool selection_flags);

  /**
   * @brief Check if electron given as function argument passes "tight" electron selection, defined in Table 13 of AN-2015/321
   * @return True if electron passes selection; false otherwise
   */
  bool operator()(const RecoElectron & electron) const;

protected:
  int era_;
  bool debug_;
  bool set_selection_flags_;
  bool apply_offline_e_trigger_cuts_;

  Double_t min_cone_pt_;              ///< lower cut threshold on cone pT
  Double_t min_lepton_pt_;            ///< lower cut threshold on "raw" lepton pT
  Double_t max_absEta_;               ///< upper cut threshold on absolute value of eta
  Double_t max_dxy_;                  ///< upper cut threshold on d_{xy}, distance in the transverse plane w.r.t PV
  Double_t max_dz_;                   ///< upper cut threshold on d_{z}, distance on the z axis w.r.t PV
  Double_t max_relIso_;               ///< upper cut threshold on relative isolation
  Double_t max_sip3d_;                ///< upper cut threshold on significance of IP
//--- define cuts that dependent on eta
//    format: central region (|eta| < 0.8) / transition region (0.8 < |eta| < 1.479) / forward region (|eta| > 1.479)
  typedef std::vector<Double_t> vDouble_t;
  vDouble_t binning_absEta_;          ///< eta values separating central, transition and forward region (0.8, 1.479)
  Double_t min_pt_trig_;              ///< lower pT threshold for applying shower shape cuts (to mimic selection applied on trigger level)
  vDouble_t max_sigmaEtaEta_trig_;    ///< upper cut threshold on second shower moment in eta-direction 
  vDouble_t max_HoE_trig_;            ///< upper cut threshold on ratio of energy deposits in hadronic/electromagnetic section of calorimeter
  vDouble_t max_deltaEta_trig_;       ///< upper cut threshold on difference in eta between impact position of track and electron cluster
  vDouble_t max_deltaPhi_trig_;       ///< upper cut threshold on difference in phi between impact position of track and electron cluster
  Double_t min_OoEminusOoP_trig_;     ///< lower cut threshold on difference between calorimeter energy and track momentum (1/E - 1/P)
  vDouble_t max_OoEminusOoP_trig_;    ///< upper cut threshold on difference between calorimeter energy and track momentum (1/E - 1/P)
//-------------------------------------------------------------------------------
//--- define cuts that dependent on lepton MVA of ttH multilepton analysis 
//    format: electron fails / passes loose cut on lepton MVA value
  Double_t wp_mvaTTH_;                ///< lepton MVA threshold
  vDouble_t min_jetPtRatio_;          ///< lower cut on ratio of lepton pT to pT of nearby jet
  vDouble_t max_jetBtagCSV_;          ///< upper cut threshold on CSV b-tagging discriminator value of nearby jet
  vDouble_t min_mvaIDraw_;            ///< lower cut on EGamma POG MVA raw value
//-------------------------------------------------------------------------------
  bool apply_conversionVeto_;         ///< apply (True) or do not apply (False) conversion veto
  Int_t max_nLostHits_;               ///< upper cut threshold on lost hits in the innermost layer of the tracker (electrons with lost_hits equal to cut threshold pass) 
};

class RecoElectronCollectionSelectorFakeable
  : public ParticleCollectionSelector<RecoElectron, RecoElectronSelectorFakeable>
{
public:
  explicit
  RecoElectronCollectionSelectorFakeable(int era,
                                         int index = -1,
                                         bool debug = false,
                                         bool set_selection_flags = true);
  ~RecoElectronCollectionSelectorFakeable() {}

  void enable_offline_e_trigger_cuts();
  void disable_offline_e_trigger_cuts();
};

#endif // tthAnalysis_HiggsToTauTau_RecoElectronCollectionSelectorFakeable_h

