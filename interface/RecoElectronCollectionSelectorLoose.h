#ifndef tthAnalysis_HiggsToTauTau_RecoElectronCollectionSelectorLoose_h
#define tthAnalysis_HiggsToTauTau_RecoElectronCollectionSelectorLoose_h

#include "tthAnalysis/HiggsToTauTau/interface/ParticleCollectionSelector.h" // ParticleCollectionSelector
#include "tthAnalysis/HiggsToTauTau/interface/RecoElectronCollectionSelectorTight.h" // RecoElectronSelectorTight, RecoElectron

class RecoElectronSelectorLoose
{
public:
  explicit
  RecoElectronSelectorLoose(int era,
                            int index = -1,
                            bool debug = false,
                            bool set_selection_flags = true);
  ~RecoElectronSelectorLoose() {}

  /**
   * @brief Check if electron given as function argument passes "loose" electron selection, defined in Table 13 of AN-2015/321
   * @return True if electron passes selection; false otherwise
   */
  bool operator()(const RecoElectron & electron) const;

protected:
  bool set_selection_flags_;
  bool debug_;                        ///< enable printout for debugging purposes
  int era_;

  RecoElectronSelectorTight tightElectronSelector_;

  Double_t min_pt_;                   ///< lower cut threshold on pT
  Double_t max_absEta_;               ///< upper cut threshold on absolute value of eta
  Double_t max_dxy_;                  ///< upper cut threshold on d_{xy}, distance in the transverse plane w.r.t PV
  Double_t max_dz_;                   ///< upper cut threshold on d_{z}, distance on the z axis w.r.t PV
  Double_t max_relIso_;               ///< upper cut threshold on relative isolation
  Double_t max_sip3d_;                ///< upper cut threshold on significance of IP
//--- define cuts that dependent on eta
//    format: central region (|eta| < 0.8) / transition region (0.8 < |eta| < 1.479) / forward region (|eta| > 1.479)
  typedef std::vector<Double_t> vDouble_t;
  vDouble_t min_mvaRawPOG_vlow_;      ///< upper cut threshold on EGamma POG electron MVA value, very low pT
  vDouble_t min_mvaRawPOG_low_;       ///< upper cut threshold on EGamma POG electron MVA value, low pT
  vDouble_t min_mvaRawPOG_high_;      ///< upper cut threshold on EGamma POG electron MVA value, high pT
  vDouble_t binning_absEta_;          ///< eta values separating central, transition and forward region (0.8, 1.479)
//-------------------------------------------------------------------------------
  bool apply_tightCharge_;            ///< apply (True) or do not apply (False) tight charge cut
  bool apply_conversionVeto_;         ///< apply (True) or do not apply (False) conversion veto
  Int_t max_nLostHits_;               ///< upper cut threshold on lost hits in the innermost layer of the tracker (electrons with lost_hits equal to cut threshold pass)
//-------------------------------------------------------------------------------
};

typedef ParticleCollectionSelector<RecoElectron, RecoElectronSelectorLoose> RecoElectronCollectionSelectorLoose;

#endif // tthAnalysis_HiggsToTauTau_RecoElectronCollectionSelectorLoose_h
