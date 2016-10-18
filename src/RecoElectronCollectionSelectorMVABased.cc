#include "tthAnalysis/HiggsToTauTau/interface/RecoElectronCollectionSelectorMVABased.h" // RecoElectronSelectorMVABased

#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // kEra_2015, kEra_2016

#include <FWCore/Utilities/interface/Exception.h> // cms::Exception

RecoElectronSelectorMVABased::RecoElectronSelectorMVABased(int era, int index, bool debug)
  : era_(era)
  , min_pt_(15.)
  , binning_absEta_({ 0.8, 1.479 })
  , min_pt_trig_(30.)
  , max_sigmaEtaEta_trig_({ 0.011, 0.011, 0.030 })
  , max_HoE_trig_({ 0.10, 0.10, 0.07 })
  , max_deltaEta_trig_({ 0.01, 0.01, 0.008 })
  , max_deltaPhi_trig_({ 0.04, 0.04, 0.07 })
  , min_OoEminusOoP_trig_(-0.05)
  , max_OoEminusOoP_trig_({ 0.010, 0.010, 0.005 })
  , min_mvaTTH_(0.75)
{
  switch(era_)
  {
    case kEra_2015:
      max_nLostHits_ = 0;
      max_jetBtagCSV_ = 0.89;
      apply_tightCharge_ = true;
      apply_conversionVeto_ = true;
      break;
    case kEra_2016:
      max_nLostHits_ = 1;
      max_jetBtagCSV_ = 0.80;
      apply_tightCharge_ = false;
      apply_conversionVeto_ = false;
      break;
    default:
      throw cms::Exception("RecoElectronSelectorMVABased") << "Invalid era = " << era_;
  }

  assert(binning_absEta_.size() == 2);
  assert(max_sigmaEtaEta_trig_.size() == 3);
  assert(max_HoE_trig_.size() == 3);
  assert(max_deltaEta_trig_.size() == 3);
  assert(max_deltaPhi_trig_.size() == 3);
  assert(max_OoEminusOoP_trig_.size() == 3);
}

bool
RecoElectronSelectorMVABased::operator()(const RecoElectron& electron) const
{
  if ( electron.pt_ >= min_pt_ &&
       electron.nLostHits_ <= max_nLostHits_ &&
       electron.jetBtagCSV_ <= max_jetBtagCSV_ &&
       electron.mvaRawTTH_ >= min_mvaTTH_ &&
       (electron.tightCharge_ >= 2 || !apply_tightCharge_) &&
       (electron.passesConversionVeto_ || !apply_conversionVeto_) ) {
    int idxBin_absEta = -1;
    if      ( electron.absEta_ <= binning_absEta_[0] ) idxBin_absEta = 0;
    else if ( electron.absEta_ <= binning_absEta_[1] ) idxBin_absEta = 1;
    else                                               idxBin_absEta = 2;
    assert(idxBin_absEta >= 0 && idxBin_absEta <= 2);
    if ( electron.pt_ <= min_pt_trig_ ) return true;
    else if ( electron.sigmaEtaEta_ <= max_sigmaEtaEta_trig_[idxBin_absEta] &&
              electron.HoE_ <= max_HoE_trig_[idxBin_absEta] &&
              electron.deltaEta_ <= max_deltaEta_trig_[idxBin_absEta] &&
              electron.deltaPhi_ <= max_deltaPhi_trig_[idxBin_absEta] &&
              electron.OoEminusOoP_ >= min_OoEminusOoP_trig_ && electron.OoEminusOoP_ <= max_OoEminusOoP_trig_[idxBin_absEta] )
      return true;
  }
  return false;
}
