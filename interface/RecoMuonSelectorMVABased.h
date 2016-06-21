#ifndef RECOMUONSELECTORMVABASED_H
#define RECOMUONSELECTORMVABASED_H

#include "tthAnalysis/HiggsToTauTau/interface/RecoMuon.h" // RecoMuon

#include <Rtypes.h> // Double_t

class RecoMuonSelectorMVABased
{
 public:
  RecoMuonSelectorMVABased(bool debug = false);
  ~RecoMuonSelectorMVABased() {}

  /**
   * @brief Check if muon given as function argument passes "cut-based" muon selection,
   *        defined in https://twiki.cern.ch/twiki/bin/viewauth/CMS/TTHtautauFor13TeV#mva_based_selection
   *        Assumes that a given muon has passed preselection cuts
   * @return True if muon passes selection; false otherwise
   */
  bool operator()(const RecoMuon& muon) const;

 protected:
  Double_t min_pt_;         ///< lower cut threshold on pT
  Double_t min_mvaTTH_;     ///< lower cut threshold on lepton MVA of ttH multilepton analysis
  Double_t max_jetBtagCSV_; ///< upper cut threshold on CSV b-tagging discriminator value of nearby jet
  bool apply_mediumIdPOG_;  ///< apply (True) or do not apply (False) medium PFMuon id selection
  bool apply_tightCharge_;  ///< apply (True) or do not apply (False) tight charge cut (2 if ptError/pt < 0.20, 0 otherwise)
};

#endif // RECOMUONSELECTORMVABASED_H
