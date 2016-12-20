#include "tthAnalysis/HiggsToTauTau/interface/RecoElectronCollectionSelectorCutBased.h" // RecoElectronSelectorCutBased

RecoElectronSelectorCutBased::RecoElectronSelectorCutBased(int era, int index, bool debug)
  : min_pt_(15.)
  , max_relIso_(0.1)
  , max_sip3d_(4.)
  , min_mvaRawPOG_({ -0.7, -0.83, -0.92 }) /* min_mvaRawPOG_({ 0.87, 0.60, 0.17 }) */
  , binning_absEta_({ 0.8, 1.479 })
  , apply_tightCharge_(true)
  , apply_conversionVeto_(true)
  , max_nLostHits_(0)
{
  /*
  if      ( era_ == kEra_2015 ) max_jetBtagCSV_ = 0.89;
  else if ( era_ == kEra_2016 ) max_jetBtagCSV_ = 0.80;
  else assert(0);
   */
  assert(min_mvaRawPOG_.size() == 3);
  assert(binning_absEta_.size() == 2);
}

bool
RecoElectronSelectorCutBased::operator()(const RecoElectron& electron) const
{
  if(electron.pt() >= min_pt_ &&
     electron.relIso() <= max_relIso_ &&
     electron.sip3d() <= max_sip3d_ &&
     electron.nLostHits() <= max_nLostHits_ &&
     (electron.tightCharge() >= 2 || !apply_tightCharge_) &&
     (electron.passesConversionVeto() || !apply_conversionVeto_))
  {
    int idxBin = -1;
    if      (electron.absEta() <= binning_absEta_[0]) idxBin = 0;
    else if (electron.absEta() <= binning_absEta_[1]) idxBin = 1;
    else                                              idxBin = 2;
    assert(idxBin >= 0 && idxBin <= 2);
    if (electron.mvaRawPOG() >= min_mvaRawPOG_[idxBin]) return true;
  }
  return false;
}
