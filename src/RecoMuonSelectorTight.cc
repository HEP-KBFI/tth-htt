#include "tthAnalysis/HiggsToTauTau/interface/RecoMuonSelectorTight.h" // RecoMuonSelectorTight

#include <cmath> // fabs

RecoMuonSelectorTight::RecoMuonSelectorTight(int index, bool debug)
  : debug_(debug)
  , min_pt_(10.) // 15 GeV for 2lss channel, 10 GeV for 3l channel (cf. Table 13 of AN-2015/321)
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
  if ( debug_ ) {
    std::cout << "<RecoMuonSelectorTight::operator()>:" << std::endl;
    std::cout << " muon: pT = " << muon.pt_ << ", eta = " << muon.eta_ << ", phi = " << muon.phi_ << ", charge = " << muon.charge_ << std::endl;
  }
  if ( muon.pt_ < min_pt_ ) {
    if ( debug_ ) std::cout << "FAILS pT cut." << std::endl;
    return false;
  }
  if ( muon.absEta_ > max_absEta_ ) {
    if ( debug_ ) std::cout << "FAILS eta cut." << std::endl;
    return false;
  }
  if ( std::fabs(muon.dxy_) > max_dxy_ ) {
    if ( debug_ ) std::cout << "FAILS dxy cut." << std::endl;
    return false;
  }
  if ( std::fabs(muon.dz_) > max_dz_ ) {
    if ( debug_ ) std::cout << "FAILS dz cut." << std::endl;
    return false;
  }
  if ( muon.relIso_ > max_relIso_ ) {
    if ( debug_ ) std::cout << "FAILS relIso cut." << std::endl;
    return false;
  }
  if ( muon.sip3d_ > max_sip3d_ ) {
    if ( debug_ ) std::cout << "FAILS sip3d cut." << std::endl;
    return false;
  }
  if ( apply_looseIdPOG_ && !muon.passesLooseIdPOG_ ) {
    if ( debug_ ) std::cout << "FAILS looseIdPOG cut." << std::endl;
    return false;
  }
  if ( muon.jetBtagCSV_ > max_jetBtagCSV_ ) {
    if ( debug_ ) std::cout << "FAILS jetBtagCSV cut." << std::endl;
    return false;
  }
  if ( apply_mediumIdPOG_ && !muon.passesMediumIdPOG_ ) {
    if ( debug_ ) std::cout << "FAILS mediumIdPOG cut." << std::endl;
    return false;
  }
  if ( apply_tightCharge_ && muon.tightCharge_ < 2 ) {
    if ( debug_ ) std::cout << "FAILS tightCharge cut." << std::endl;
    return false;
  }
  if ( muon.mvaRawTTH_ < min_mvaTTH_ ) {
    if ( debug_ ) std::cout << "FAILS mvaTTH cut." << std::endl;
    return false;
  }
  // muon passes all cuts
  return true;
}
