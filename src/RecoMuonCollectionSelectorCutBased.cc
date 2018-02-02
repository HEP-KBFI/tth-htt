#include "tthAnalysis/HiggsToTauTau/interface/RecoMuonCollectionSelectorCutBased.h" // RecoMuonSelectorCutBased

RecoMuonSelectorCutBased::RecoMuonSelectorCutBased(int era,
                                                   int index,
                                                   bool debug)
  : min_pt_(10.)
  , max_relIso_(0.2)
  , max_sip3d_(4.)
  , apply_mediumIdPOG_(true)
  , apply_tightCharge_(true)
{}

bool
RecoMuonSelectorCutBased::operator()(const RecoMuon & muon) const
{
  return
    muon.pt()     >= min_pt_                          &&
    muon.relIso() <= max_relIso_                      &&
    muon.sip3d()  <= max_sip3d_                       &&
    (muon.passesMediumIdPOG() || !apply_mediumIdPOG_) &&
    (muon.tightCharge() >= 2 || !apply_tightCharge_)
  ;
}
