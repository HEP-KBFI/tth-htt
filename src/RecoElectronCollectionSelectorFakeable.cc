#include "tthAnalysis/HiggsToTauTau/interface/RecoElectronCollectionSelectorFakeable.h" // RecoElectronSelectorFakeable

#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // kEra_2015, kEra_2016

#include <FWCore/Utilities/interface/Exception.h> // cms::Exception

#include <cmath> // fabs
#include <assert.h> // assert

RecoElectronSelectorFakeable::RecoElectronSelectorFakeable(int era, int index, bool debug)
  : era_(era)
  , apply_offline_e_trigger_cuts_(true)
  , min_pt_(10.)
  , max_absEta_(2.5)
  , max_dxy_(0.05)
  , max_dz_(0.1)
  , max_relIso_(0.4)
  , max_sip3d_(8.)
  , min_mvaRawPOG_({ -0.7, -0.83, -0.92 })
  , binning_absEta_({ 0.8, 1.479 })
  , min_pt_trig_(30.)
  , max_sigmaEtaEta_trig_({ 0.011, 0.011, 0.030 })
  , max_HoE_trig_({ 0.10, 0.10, 0.07 }) 
  , max_deltaEta_trig_({ 0.01, 0.01, 0.008 })
  , max_deltaPhi_trig_({ 0.04, 0.04, 0.07 })  
  , min_OoEminusOoP_trig_(-0.05)   
  , max_OoEminusOoP_trig_({ 0.010, 0.010, 0.005 })    
  , binning_mvaTTH_({ 0.75 })
  , min_jetPtRatio_({ 0.30, -1.e+3 })
  , apply_conversionVeto_(true)   
  , max_nLostHits_(0)
{
  if      ( era_ == kEra_2015 ) max_jetBtagCSV_ = { 0.605, 0.89 };
  else if ( era_ == kEra_2016 ) max_jetBtagCSV_ = { 0.460, 0.80 };
  else assert(0);
  assert(min_mvaRawPOG_.size() == 3);
  assert(binning_absEta_.size() == 2);
  assert(max_sigmaEtaEta_trig_.size() == 3);
  assert(max_HoE_trig_.size() == 3);
  assert(max_deltaEta_trig_.size() == 3);
  assert(max_deltaPhi_trig_.size() == 3);
  assert(max_OoEminusOoP_trig_.size() == 3);
  assert(binning_mvaTTH_.size() == 1);
  assert(min_jetPtRatio_.size() == 2);
  assert(max_jetBtagCSV_.size() == 2);
}

bool RecoElectronSelectorFakeable::operator()(const RecoElectron& electron) const
{
  if ( electron.pt_ >= min_pt_ &&
       electron.absEta_ <= max_absEta_ &&
       std::fabs(electron.dxy_) <= max_dxy_ &&
       std::fabs(electron.dz_) <= max_dz_ &&
       electron.relIso_ <= max_relIso_ &&
       electron.sip3d_ <= max_sip3d_ &&
       electron.nLostHits_ <= max_nLostHits_ && 
       (electron.passesConversionVeto_ || !apply_conversionVeto_) ) {
    int idxBin_absEta = -1;
    if      ( electron.absEta_ <= binning_absEta_[0] ) idxBin_absEta = 0;
    else if ( electron.absEta_ <= binning_absEta_[1] ) idxBin_absEta = 1;
    else                                               idxBin_absEta = 2;
    assert(idxBin_absEta >= 0 && idxBin_absEta <= 2);
    if ( electron.mvaRawPOG_ >= min_mvaRawPOG_[idxBin_absEta] ) {
      int idxBin_mvaTTH = -1;
      if   ( electron.mvaRawTTH_ <= binning_mvaTTH_[0] ) idxBin_mvaTTH = 0;
      else                                               idxBin_mvaTTH = 1;
      assert(idxBin_mvaTTH >= 0 && idxBin_mvaTTH <= 1);
      if ( electron.jetPtRatio_ >= min_jetPtRatio_[idxBin_mvaTTH] &&
	   electron.jetBtagCSV_ <= max_jetBtagCSV_[idxBin_mvaTTH] ) {
	if ( electron.pt_ <= min_pt_trig_ || !apply_offline_e_trigger_cuts_ ) return true;
	else if ( electron.sigmaEtaEta_ <= max_sigmaEtaEta_trig_[idxBin_absEta] &&
		  electron.HoE_ <= max_HoE_trig_[idxBin_absEta] &&
		  electron.deltaEta_ <= max_deltaEta_trig_[idxBin_absEta] &&
		  electron.deltaPhi_ <= max_deltaPhi_trig_[idxBin_absEta] &&
		  electron.OoEminusOoP_ >= min_OoEminusOoP_trig_ &&
		  electron.OoEminusOoP_ <= max_OoEminusOoP_trig_[idxBin_absEta] ) return true;
      }
    }
  }
  return false;
}
