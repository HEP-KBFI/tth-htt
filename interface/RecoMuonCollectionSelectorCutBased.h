#ifndef RECOMUONCOLLECTIONSELECTORCUTBASED_H
#define RECOMUONCOLLECTIONSELECTORCUTBASED_H

#include "tthAnalysis/HiggsToTauTau/interface/RecoMuon.h" // RecoMuon
#include "tthAnalysis/HiggsToTauTau/interface/ParticleCollectionSelector.h" // ParticleCollectionSelector

#include <Rtypes.h> // Double_t

class RecoMuonSelectorCutBased
{
 public:
  RecoMuonSelectorCutBased(int era, int index = -1, bool debug = false);
  ~RecoMuonSelectorCutBased() {}

  /**
   * @brief Check if muon given as function argument passes "cut-based" muon selection,
   *        defined in https://twiki.cern.ch/twiki/bin/viewauth/CMS/TTHtautauFor13TeV#cut_based_selection
   *        Assumes that a given muon has passed preselection cuts
   * @return True if muon passes selection; false otherwise
   */
  bool operator()(const RecoMuon& muon) const;

 protected:
  Double_t min_pt_;         ///< lower cut threshold on pT
  Double_t max_relIso_;     ///< upper cut threshold on relative isolation
  Double_t max_sip3d_;      ///< upper cut threshold on significance of IP
  bool apply_mediumIdPOG_;  ///< apply (True) or do not apply (False) medium PFMuon id selection
  bool apply_tightCharge_;  ///< apply (True) or do not apply (False) tight charge cut (2 if ptError/pt < 0.20, 0 otherwise)
};

typedef ParticleCollectionSelector<RecoMuon, RecoMuonSelectorCutBased> RecoMuonCollectionSelectorCutBased;

#endif // RECOMUONCOLLECTIONSELECTORCUTBASED_H
