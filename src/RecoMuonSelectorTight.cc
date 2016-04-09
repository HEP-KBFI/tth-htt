#include "tthAnalysis/HiggsToTauTau/interface/RecoMuonSelectorTight.h" // RecoMuonSelectorTight

#include <cmath> // fabs

RecoMuonSelectorTight::RecoMuonSelectorTight()
  : min_pt_(10.)
  , max_absEta_(2.4)
  , max_dxy_(0.05)
  , max_dz_(0.1)
  , max_relIso_(0.4)
  , max_sip3d_(8.)
  , apply_looseIdPOG_(true)
  , max_jetBtagCSV_(0.89)  
  , apply_mediumIdPOG_(true)
  , apply_tightCharge_(true)
  , min_mvaTTH_(0.75)
{}

bool RecoMuonSelectorTight::operator()(const RecoMuon& muon) const
{
  if ( muon.pt_ >= min_pt_ &&
       muon.absEta_ <= max_absEta_ &&
       std::fabs(muon.dxy_) <= max_dxy_ &&
       std::fabs(muon.dz_) <= max_dz_ &&
       muon.relIso_ <= max_relIso_ &&
       muon.sip3d_ <= max_sip3d_ &&
       (muon.passesLooseIdPOG_ || !apply_looseIdPOG_) && 
       muon.jetBtagCSV_ <= max_jetBtagCSV_ &&
       (muon.passesMediumIdPOG_ || !apply_mediumIdPOG_) &&
       (muon.tightCharge_ >= 2 || !apply_tightCharge_) && 
       muon.mvaRawTTH_ >= min_mvaTTH_ ) {
    return true;
  } 
  return false;
}
