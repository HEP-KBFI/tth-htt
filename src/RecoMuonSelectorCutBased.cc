#include "tthAnalysis/HiggsToTauTau/interface/RecoMuonSelectorCutBased.h" // RecoMuonSelectorCutBased

RecoMuonSelectorCutBased::RecoMuonSelectorCutBased()
  : min_pt_(10)
  , max_relIso_(0.2)
  , max_sip3d_(4)
  , apply_mediumIdPOG_(true)
  , apply_tightCharge_(true)
{}

bool RecoMuonSelectorCutBased::operator()(const RecoMuon& muon) const
{
  if(muon.pt_ >= min_pt_ &&
     muon.relIso_ <= max_relIso_ &&
     muon.sip3d_ <= max_sip3d_ &&
     (muon.passesMediumIdPOG_ || !apply_mediumIdPOG_) &&
     (muon.tightCharge_ >= 2 || !apply_tightCharge_)) {
      return true;
  }
  return false;
}
