#include "tthAnalysis/HiggsToTauTau/interface/RecoElectronCollectionSelectorLoose.h" // RecoElectronSelectorLoose

#include <cmath> // std::fabs()

RecoElectronSelectorLoose::RecoElectronSelectorLoose(int index, bool debug)
  : min_pt_(7.)
  , max_absEta_(2.5)
  , max_dxy_(0.05)
  , max_dz_(0.1)
  , max_relIso_(0.4)
  , max_sip3d_(8.)
  , min_mvaRawPOG_({ -0.7, -0.83, -0.92 })
  , binning_absEta_({ 0.8, 1.479 })
  , apply_tightCharge_(false)
  , apply_conversionVeto_(false)
  , max_nLostHits_(1)
{
  assert(min_mvaRawPOG_.size() == 3);
  assert(binning_absEta_.size() == 2);
}

bool RecoElectronSelectorLoose::operator()(const RecoElectron& electron) const
{
  if ( electron.pt_ >= min_pt_ &&
       electron.absEta_ <= max_absEta_ &&
       std::fabs(electron.dxy_) <= max_dxy_ &&
       std::fabs(electron.dz_) <= max_dz_ &&
       electron.relIso_ <= max_relIso_ &&
       electron.sip3d_ <= max_sip3d_ &&
       (electron.tightCharge_ >= 2 || !apply_tightCharge_) && 
       (electron.passesConversionVeto_ > 0 || !apply_conversionVeto_) &&
       electron.nLostHits_ <= max_nLostHits_ ) {
    int idxBin = -1;
    if      ( electron.absEta_ <= binning_absEta_[0] ) idxBin = 0;
    else if ( electron.absEta_ <= binning_absEta_[1] ) idxBin = 1;
    else                                               idxBin = 2;
    assert(idxBin >= 0 && idxBin <= 2);
    if ( electron.mvaRawPOG_ >= min_mvaRawPOG_[idxBin] ) return true;
  }
  return false;
}
