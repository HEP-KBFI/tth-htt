#include "tthAnalysis/HiggsToTauTau/interface/RecoMuonCollectionSelectorLoose.h" // RecoMuonSelectorLoose

#include <cmath> // fabs

RecoMuonSelectorLoose::RecoMuonSelectorLoose(int era, bool set_selection_flags, int index, bool debug)
  : set_selection_flags_(set_selection_flags)
  , min_pt_(5.)
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
  if ( muon.pt() >= min_pt_ &&
       muon.absEta() <= max_absEta_ &&
       std::fabs(muon.dxy()) <= max_dxy_ &&
       std::fabs(muon.dz()) <= max_dz_ &&
       muon.relIso() <= max_relIso_ &&
       muon.sip3d() <= max_sip3d_ &&
       (muon.passesLooseIdPOG() || !apply_looseIdPOG_) && 
       (muon.passesMediumIdPOG() || !apply_mediumIdPOG_) ) {
    if ( set_selection_flags_ ) muon.set_isLoose();
    return true;
  }
  return false;
}
