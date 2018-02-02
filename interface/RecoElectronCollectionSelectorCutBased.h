#ifndef RECOELECTRONCOLLECTIONSELECTORCUTBASED_H
#define RECOELECTRONCOLLECTIONSELECTORCUTBASED_H

#include "tthAnalysis/HiggsToTauTau/interface/ParticleCollectionSelector.h" // ParticleCollectionSelector
#include "tthAnalysis/HiggsToTauTau/interface/RecoElectron.h" // RecoElectron

class RecoElectronSelectorCutBased
{
public:
  explicit
  RecoElectronSelectorCutBased(int era,
                               int index = -1,
                               bool debug = false);
  ~RecoElectronSelectorCutBased() {}

  /**
   * @brief Check if electron given as function argument passes "cut-based" electron selection,
   *        defined in https://twiki.cern.ch/twiki/bin/viewauth/CMS/TTHtautauFor13TeV#cut_based_selection_AN1
   *        Assumes that a given muon has passed preselection cuts
   * @return True if electron passes selection; false otherwise
   */
  bool operator()(const RecoElectron & electron) const;

protected:
  Double_t min_pt_;                   ///< lower cut threshold on pT
  Double_t max_relIso_;               ///< upper cut threshold on relative isolation
  Double_t max_sip3d_;                ///< upper cut threshold on significance of IP
//--- define cuts that dependent on eta
//    format: central region (|eta| < 0.8) / transition region (0.8 < |eta| < 1.479) / forward region (|eta| > 1.479)
  typedef std::vector<Double_t> vDouble_t;
  vDouble_t min_mvaRawPOG_vlow_;       ///< upper cut threshold on EGamma POG electron MVA value, very low pT
  vDouble_t min_mvaRawPOG_low_;        ///< upper cut threshold on EGamma POG electron MVA value, low pT
  vDouble_t min_mvaRawPOG_high_;       ///< upper cut threshold on EGamma POG electron MVA value, high pT  
  vDouble_t binning_absEta_;          ///< eta values separating central, transition and forward region (0.8, 1.479)
//-------------------------------------------------------------------------------
  bool apply_tightCharge_;            ///< apply (True) or do not apply (False) tight charge cut
  bool apply_conversionVeto_;         ///< apply (True) or do not apply (False) conversion veto
  Int_t max_nLostHits_;               ///< upper cut threshold on lost hits in the innermost layer of the tracker (electrons with lost_hits equal to cut threshold pass)
};

typedef ParticleCollectionSelector<RecoElectron, RecoElectronSelectorCutBased> RecoElectronCollectionSelectorCutBased;

#endif // RECOELECTRONCOLLECTIONSELECTORCUTBASED_H
