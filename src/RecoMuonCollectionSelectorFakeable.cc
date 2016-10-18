#include "tthAnalysis/HiggsToTauTau/interface/RecoMuonCollectionSelectorFakeable.h" // RecoMuonSelectorFakeable

#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // kEra_2015, kEra_2016

#include <cmath> // fabs

RecoMuonSelectorFakeable::RecoMuonSelectorFakeable(int era, int index, bool debug)
  : era_(era)
  , min_pt_(10.)
  , max_absEta_(2.4)
  , max_dxy_(0.05)
  , max_dz_(0.1)
  , max_relIso_(0.4)
  , max_sip3d_(8.)
  , apply_looseIdPOG_(true)
  , binning_mvaTTH_({ 0.75 })
  , min_jetPtRatio_({ 0.30, -1.e+3 })   
  , apply_mediumIdPOG_(false)
  , apply_tightCharge_(false)
{
  if      ( era_ == kEra_2015 ) max_jetBtagCSV_ = { 0.605, 0.89 };
  else if ( era_ == kEra_2016 ) max_jetBtagCSV_ = { 0.460, 0.80 };
  else assert(0);
}

bool RecoMuonSelectorFakeable::operator()(const RecoMuon& muon) const
{
  double muonPt_corr = ( muon.jetPtRatio_ > 1.e-3 ) ? 0.85*muon.pt_/muon.jetPtRatio_ : muon.pt_;
  if ( muonPt_corr >= min_pt_ &&
       muon.absEta_ <= max_absEta_ &&
       std::fabs(muon.dxy_) <= max_dxy_ &&
       std::fabs(muon.dz_) <= max_dz_ &&
       muon.relIso_ <= max_relIso_ &&
       muon.sip3d_ <= max_sip3d_ &&
       (muon.passesLooseIdPOG_ || !apply_looseIdPOG_) && 
       (muon.passesMediumIdPOG_ || !apply_mediumIdPOG_) &&
       (muon.tightCharge_ >= 2 || !apply_tightCharge_) ) {
    int idxBin = -1;
    if   ( muon.mvaRawTTH_ <= binning_mvaTTH_[0] ) idxBin = 0;
    else                                           idxBin = 1;
    assert(idxBin >= 0 && idxBin <= 1);
    if ( muon.jetPtRatio_ >= min_jetPtRatio_[idxBin] &&
	 muon.jetBtagCSV_ <= max_jetBtagCSV_[idxBin] ) return true;
  }
  return false;
}
