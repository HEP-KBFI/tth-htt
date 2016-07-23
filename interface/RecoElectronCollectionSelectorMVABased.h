#ifndef RECOELECTRONCOLLECTIONSELECTORMVABASED_H
#define RECOELECTRONCOLLECTIONSELECTORMVABASED_H

#include "tthAnalysis/HiggsToTauTau/interface/RecoElectron.h" // RecoElectron
#include "tthAnalysis/HiggsToTauTau/interface/ParticleCollectionSelector.h" // ParticleCollectionSelector

#include <Rtypes.h> // Int_t, Double_t

#include <vector> // std::vector<>

class RecoElectronSelectorMVABased
{
 public:
  RecoElectronSelectorMVABased(int index = -1, bool debug = false);
  ~RecoElectronSelectorMVABased() {}

  /**
   * @brief Check if electron given as function argument passes "mva-based" electron selection,
   *        defined in https://twiki.cern.ch/twiki/bin/viewauth/CMS/TTHtautauFor13TeV#mva_based_selection_AN1
   * @return True if electron passes selection; false otherwise
   */
  bool operator()(const RecoElectron& electron) const;

 protected:
  Double_t min_pt_;                   ///< lower cut threshold on pT
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
  Double_t min_mvaTTH_;     ///< lower cut threshold on lepton MVA of ttH multilepton analysis
  Double_t max_jetBtagCSV_; ///< upper cut threshold on CSV b-tagging discriminator value of nearby jet
  bool apply_tightCharge_;            ///< apply (True) or do not apply (False) tight charge cut
  bool apply_conversionVeto_;         ///< apply (True) or do not apply (False) conversion veto
  Int_t max_nLostHits_;               ///< upper cut threshold on lost hits in the innermost layer of the tracker (electrons with lost_hits equal to cut threshold pass)
};

typedef ParticleCollectionSelector<RecoElectron, RecoElectronSelectorMVABased> RecoElectronCollectionSelectorMVABased;

#endif // RECOELECTRONCOLLECTIONSELECTORMVABASED_H
