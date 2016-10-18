#include "tthAnalysis/HiggsToTauTau/interface/RecoMuonCollectionSelectorLoose.h" // RecoMuonSelectorLoose

#include <cmath> // fabs

RecoMuonSelectorLoose::RecoMuonSelectorLoose(int era, int index, bool debug)
  : min_pt_(5.)
  , max_absEta_(2.4)
  , max_dxy_(0.05)
  , max_dz_(0.1)
  , max_relIso_(0.4)
  , max_sip3d_(8.)
  , apply_looseIdPOG_(true)
  , apply_mediumIdPOG_(false)
  , apply_tightCharge_(false)  
{}

bool RecoMuonSelectorLoose::operator()(const RecoMuon& muon) const
{
  if ( muon.pt_ >= min_pt_ &&
       muon.absEta_ <= max_absEta_ &&
       std::fabs(muon.dxy_) <= max_dxy_ &&
       std::fabs(muon.dz_) <= max_dz_ &&
       muon.relIso_ <= max_relIso_ &&
       muon.sip3d_ <= max_sip3d_ &&
       (muon.passesLooseIdPOG_ || !apply_looseIdPOG_) && 
       (muon.passesMediumIdPOG_ || !apply_mediumIdPOG_) ) {
    return true;
  }
  return false;
}
