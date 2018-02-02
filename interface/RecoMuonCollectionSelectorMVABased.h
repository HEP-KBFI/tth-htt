#ifndef RECOMUONCOLLECTIONSELECTORMVABASED_H
#define RECOMUONCOLLECTIONSELECTORMVABASED_H

#include "tthAnalysis/HiggsToTauTau/interface/ParticleCollectionSelector.h" // ParticleCollectionSelector
#include "tthAnalysis/HiggsToTauTau/interface/RecoMuon.h" // RecoMuon

class RecoMuonSelectorMVABased
{
public:
  explicit
  RecoMuonSelectorMVABased(int era,
                           int index = -1,
                           bool debug = false);

  /**
   * @brief Check if muon given as function argument passes "cut-based" muon selection,
   *        defined in https://twiki.cern.ch/twiki/bin/viewauth/CMS/TTHtautauFor13TeV#mva_based_selection
   *        Assumes that a given muon has passed preselection cuts
   * @return True if muon passes selection; false otherwise
   */
  bool
  operator()(const RecoMuon & muon) const;

protected:
  int era_;

  Double_t min_pt_;         ///< lower cut threshold on pT
  Double_t min_mvaTTH_;     ///< lower cut threshold on lepton MVA of ttH multilepton analysis
  Double_t max_jetBtagCSV_; ///< upper cut threshold on CSV b-tagging discriminator value of nearby jet
  bool apply_mediumIdPOG_;  ///< apply (True) or do not apply (False) medium PFMuon id selection
  bool apply_tightCharge_;  ///< apply (True) or do not apply (False) tight charge cut (2 if ptError/pt < 0.20, 0 otherwise)
};

typedef ParticleCollectionSelector<RecoMuon, RecoMuonSelectorMVABased> RecoMuonCollectionSelectorMVABased;

#endif // RECOMUONCOLLECTIONSELECTORMVABASED_H
