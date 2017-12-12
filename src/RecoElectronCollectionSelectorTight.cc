#include "tthAnalysis/HiggsToTauTau/interface/RecoElectronCollectionSelectorTight.h" // RecoElectronSelectorTight

#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // kEra_2017

#include <FWCore/Utilities/interface/Exception.h> // cms::Exception

#include <cmath> // fabs()
#include <assert.h> // assert()

RecoElectronSelectorTight::RecoElectronSelectorTight(int era, int index, bool debug, bool set_selection_flags)
  : era_(era)
  , set_selection_flags_(set_selection_flags)
  , apply_offline_e_trigger_cuts_(true)
  , debug_(debug)
  , min_pt_(10.) // 15 GeV for 2lss channel, 10 GeV for 3l channel (cf. Table 13 of AN-2015/321)
  , max_absEta_(2.5)
  , max_dxy_(0.05)
  , max_dz_(0.1)
  , max_relIso_(0.4)
  , max_sip3d_(8.)
  , min_mvaRawPOG_vlow_({ -0.30,-0.46,-0.63 })
  , min_mvaRawPOG_low_({ -0.86,-0.85,-0.81 })
  , min_mvaRawPOG_high_({ -0.96,-0.96,-0.95 })
  , binning_absEta_({ 0.8, 1.479 })
  , min_pt_trig_(30.)
  , max_sigmaEtaEta_trig_({ 0.011, 0.011, 0.030 })
  , max_HoE_trig_({ 0.10, 0.10, 0.07 }) 
  , max_deltaEta_trig_({ 0.01, 0.01, 0.008 })
  , max_deltaPhi_trig_({ 0.04, 0.04, 0.07 })  
  , min_OoEminusOoP_trig_(-0.05)   
  , max_OoEminusOoP_trig_({ 0.010, 0.010, 0.005 })      
  , apply_conversionVeto_(true)  
  , max_nLostHits_(0)
  , min_mvaTTH_(0.75)  
{
  switch(era_)
  {
    case kEra_2017:
    {
      max_jetBtagCSV_ = 0.8484;
      break;
    }
    default: throw cms::Exception("RecoElectronSelectorTight") << "Invalid era: " << era_;
  }
  assert(min_mvaRawPOG_vlow_.size() == 3);
  assert(min_mvaRawPOG_low_.size() == 3);
  assert(min_mvaRawPOG_high_.size() == 3);
  assert(binning_absEta_.size() == 2);
  assert(max_sigmaEtaEta_trig_.size() == 3);
  assert(max_HoE_trig_.size() == 3);
  assert(max_deltaEta_trig_.size() == 3);
  assert(max_deltaPhi_trig_.size() == 3);
  assert(max_OoEminusOoP_trig_.size() == 3);
}

bool RecoElectronSelectorTight::operator()(const RecoElectron& electron) const
{
  if ( debug_ ) {
    std::cout << "<RecoElectronSelectorTight::operator()>:\n" << electron;
  }
  if ( electron.pt() < min_pt_ ) {
    if ( debug_ ) std::cout << "FAILS pT cut." << std::endl;
    return false;
  }
  if ( electron.absEta() > max_absEta_ ) {
    if ( debug_ ) std::cout << "FAILS eta cut." << std::endl;
    return false;
  }
  if ( std::fabs(electron.dxy()) > max_dxy_ ) {
    if ( debug_ ) std::cout << "FAILS dxy cut." << std::endl;
    return false;
  }
  if ( std::fabs(electron.dz()) > max_dz_ ) {
    if ( debug_ ) std::cout << "FAILS dz cut." << std::endl;
    return false;
  }
  if ( electron.relIso() > max_relIso_ ) {
    if ( debug_ ) std::cout << "FAILS relIso cut." << std::endl;
    return false;
  }
  if ( electron.sip3d() > max_sip3d_ ) {
    if ( debug_ ) std::cout << "FAILS sip3d cut." << std::endl;
    return false;
  }
  if ( electron.jetBtagCSV() > max_jetBtagCSV_ ) {
    if ( debug_ ) std::cout << "FAILS jetBtagCSV cut." << std::endl;
    return false;
  }
  if ( electron.nLostHits() > max_nLostHits_ ) {
    if ( debug_ ) std::cout << "FAILS nLostHits cut." << std::endl;
    return false;
  }
  if ( apply_conversionVeto_ && !electron.passesConversionVeto() ) {
    if ( debug_ ) std::cout << "FAILS conversion veto." << std::endl;
    return false;
  }
  if ( electron.mvaRawTTH() < min_mvaTTH_ ) {
    if ( debug_ ) std::cout << "FAILS mvaTTH cut." << std::endl;
    return false;
  }
  int idxBin = -1;
  if      ( electron.absEta() <= binning_absEta_[0] ) idxBin = 0;
  else if ( electron.absEta() <= binning_absEta_[1] ) idxBin = 1;
  else                                                idxBin = 2;
  assert(idxBin >= 0 && idxBin <= 2);
  
  if (electron.pt() <= 10) {
    if ( electron.mvaRawPOG_HZZ() < min_mvaRawPOG_vlow_[idxBin] ) {
      if ( debug_ ) std::cout << "FAILS mvaPOG HZZ cut." << std::endl;
      return false;
    }  
  }
  else {
    double a = min_mvaRawPOG_low_[idxBin];
    double b = min_mvaRawPOG_high_[idxBin];
    double c = (a-b)/10;
    double cut = std::min(a, std::max(b,a-c*(electron.pt()-15)));   // warning: the _high WP must be looser than the _low one
    if ( electron.mvaRawPOG_GP() < cut ) {
      if ( debug_ ) std::cout << "FAILS mvaPOG GP cut." << std::endl;
      return false;
    }
  }
  
  // extra cuts for electrons passing pT threshold of single electron trigger, as explained in section 3.3.4 of AN-2015/321
  if ( apply_offline_e_trigger_cuts_ && electron.pt() >= min_pt_trig_ ) { 
    if ( electron.sigmaEtaEta() > max_sigmaEtaEta_trig_[idxBin] ) {
      if ( debug_ ) std::cout << "FAILS sigmaEtaEta cut." << std::endl;
      return false;
    }
    if ( electron.HoE() > max_HoE_trig_[idxBin] ) {
      if ( debug_ ) std::cout << "FAILS HoE cut." << std::endl;
      return false;
    }
    if ( electron.deltaEta() > max_deltaEta_trig_[idxBin] ) {
      if ( debug_ ) std::cout << "FAILS deltaEta cut." << std::endl;
      return false;
    }
    if ( electron.deltaPhi() > max_deltaPhi_trig_[idxBin] ) {
      if ( debug_ ) std::cout << "FAILS deltaPhi cut." << std::endl;
      return false;
    }
    if ( !(electron.OoEminusOoP() >= min_OoEminusOoP_trig_ && electron.OoEminusOoP() <= max_OoEminusOoP_trig_[idxBin]) ) {
      if ( debug_ ) std::cout << "FAILS OoEminusOoP cut." << std::endl;
      return false;
    }
  }
  // electron passes all cuts
  if ( set_selection_flags_ ) electron.set_isTight();
  return true;
}
