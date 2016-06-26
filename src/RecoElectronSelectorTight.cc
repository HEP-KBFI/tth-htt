#include "tthAnalysis/HiggsToTauTau/interface/RecoElectronSelectorTight.h" // RecoElectronSelectorTight

#include <cmath> // fabs

RecoElectronSelectorTight::RecoElectronSelectorTight(int index, bool debug)
  : debug_(debug)
  , min_pt_(15.) // 15 GeV for 2lss channel, 10 GeV for 3l channel (cf. Table 13 of AN-2015/321)
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
  , max_jetBtagCSV_(0.89)  
  , apply_tightCharge_(false)
  , apply_conversionVeto_(false)  
  , max_nLostHits_(0)
  , min_mvaTTH_(0.75)  
{
  assert(min_mvaRawPOG_.size() == 3);
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
    std::cout << "<RecoElectronSelectorTight::operator()>:" << std::endl;
    std::cout << " electron: pT = " << electron.pt_ << ", eta = " << electron.eta_ << ", phi = " << electron.phi_ << ", charge = " << electron.charge_ << std::endl;
  }
  if ( electron.pt_ < min_pt_ ) {
    if ( debug_ ) std::cout << "FAILS pT cut." << std::endl;
    return false;
  }
  if ( electron.absEta_ > max_absEta_ ) {
    if ( debug_ ) std::cout << "FAILS eta cut." << std::endl;
    return false;
  }
  if ( std::fabs(electron.dxy_) > max_dxy_ ) {
    if ( debug_ ) std::cout << "FAILS dxy cut." << std::endl;
    return false;
  }
  if ( std::fabs(electron.dz_) > max_dz_ ) {
    if ( debug_ ) std::cout << "FAILS dz cut." << std::endl;
    return false;
  }
  if ( electron.relIso_ > max_relIso_ ) {
    if ( debug_ ) std::cout << "FAILS relIso cut." << std::endl;
    return false;
  }
  if ( electron.sip3d_ > max_sip3d_ ) {
    if ( debug_ ) std::cout << "FAILS sip3d cut." << std::endl;
    return false;
  }
  if ( electron.jetBtagCSV_ > max_jetBtagCSV_ ) {
    if ( debug_ ) std::cout << "FAILS jetBtagCSV cut." << std::endl;
    return false;
  }
  if ( electron.nLostHits_ > max_nLostHits_ ) {
    if ( debug_ ) std::cout << "FAILS nLostHits cut." << std::endl;
    return false;
  }
  if ( apply_tightCharge_ && electron.tightCharge_ < 2 ) {
    if ( debug_ ) std::cout << "FAILS tightCharge cut." << std::endl;
    return false;
  }
  if ( apply_conversionVeto_ && !electron.passesConversionVeto_ ) {
    if ( debug_ ) std::cout << "FAILS conversion veto." << std::endl;
    return false;
  }
  if ( electron.mvaRawTTH_ < min_mvaTTH_ ) {
    if ( debug_ ) std::cout << "FAILS mvaTTH cut." << std::endl;
    return false;
  }
  int idxBin = -1;
  if      ( electron.absEta_ <= binning_absEta_[0] ) idxBin = 0;
  else if ( electron.absEta_ <= binning_absEta_[1] ) idxBin = 1;
  else                                               idxBin = 2;
  assert(idxBin >= 0 && idxBin <= 2);
  if ( electron.mvaRawPOG_ < min_mvaRawPOG_[idxBin] ) {
    if ( debug_ ) std::cout << "FAILS mvaPOG cut." << std::endl;
    return false;
  }
  // extra cuts for electrons passing pT threshold of single electron trigger, as explained in section 3.3.4 of AN-2015/321
  if ( electron.pt_ >= min_pt_trig_ ) { 
    if ( electron.sigmaEtaEta_ > max_sigmaEtaEta_trig_[idxBin] ) {
      if ( debug_ ) std::cout << "FAILS sigmaEtaEta cut." << std::endl;
      return false;
    }
    if ( electron.HoE_ > max_HoE_trig_[idxBin] ) {
      if ( debug_ ) std::cout << "FAILS HoE cut." << std::endl;
      return false;
    }
    if ( electron.deltaEta_ > max_deltaEta_trig_[idxBin] ) {
      if ( debug_ ) std::cout << "FAILS deltaEta cut." << std::endl;
      return false;
    }
    if ( electron.deltaPhi_ > max_deltaPhi_trig_[idxBin] ) {
      if ( debug_ ) std::cout << "FAILS deltaPhi cut." << std::endl;
      return false;
    }
    if ( !(electron.OoEminusOoP_ >= min_OoEminusOoP_trig_ && electron.OoEminusOoP_ <= max_OoEminusOoP_trig_[idxBin]) ) {
      if ( debug_ ) std::cout << "FAILS OoEminusOoP cut." << std::endl;
      return false;
    }
  }
  // electron passes all cuts
  return true;
}
