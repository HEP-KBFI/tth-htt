#include "tthAnalysis/HiggsToTauTau/interface/RecoMuonSelectorMVABased.h" // RecoMuonSelectorMVABased

RecoMuonSelectorMVABased::RecoMuonSelectorMVABased(int index, bool debug)
  : min_pt_(10)
  , min_mvaTTH_(0.75)
  , max_jetBtagCSV_(0.89)
  , apply_mediumIdPOG_(true)
  , apply_tightCharge_(true)
{}

bool
RecoMuonSelectorMVABased::operator()(const RecoMuon& muon) const
{
  if(muon.pt_ >= min_pt_ &&
     muon.mvaRawTTH_ >= min_mvaTTH_ &&
     muon.jetBtagCSV_ <= max_jetBtagCSV_ &&
     (muon.passesMediumIdPOG_ || !apply_mediumIdPOG_) &&
     (muon.tightCharge_ >= 2 || !apply_tightCharge_)) {
    return true;
  }
  return false;
}
