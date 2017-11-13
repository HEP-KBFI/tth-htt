#include "tthAnalysis/HiggsToTauTau/interface/RecoMuonCollectionSelectorTight.h" // RecoMuonSelectorTight

#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // kEra_2017

#include "FWCore/Utilities/interface/Exception.h" // cms::Exception

#include <cmath> // fabs

RecoMuonSelectorTight::RecoMuonSelectorTight(int era, int index, bool debug, bool set_selection_flags)
  : era_(era)
  , set_selection_flags_(set_selection_flags)
  , debug_(debug)
  , min_pt_(10.) // 15 GeV for 2lss channel, 10 GeV for 3l channel (cf. Table 13 of AN-2015/321)
  , max_absEta_(2.4)
  , max_dxy_(0.05)
  , max_dz_(0.1)
  , max_relIso_(0.4)
  , max_sip3d_(8.)
  , apply_looseIdPOG_(true)
  , apply_mediumIdPOG_(true)
  , min_mvaTTH_(0.75)
{
  switch(era_)
  {
    case kEra_2017:
    {
      max_jetBtagCSV_ = 0.8484;
      break;
    }
    default: throw cms::Exception("RecoMuonSelectorFakeable") << "Invalid era: " << era_;
  }
}

bool RecoMuonSelectorTight::operator()(const RecoMuon& muon) const
{
  if ( debug_ ) {
    std::cout << "<RecoMuonSelectorTight::operator()>:" << std::endl;
    std::cout << " muon: pT = " << muon.pt() << ", eta = " << muon.eta() << ", phi = " << muon.phi() << ", charge = " << muon.charge() << std::endl;
  }
  if ( muon.pt() < min_pt_ ) {
    if ( debug_ ) std::cout << "FAILS pT cut." << std::endl;
    return false;
  }
  if ( muon.absEta() > max_absEta_ ) {
    if ( debug_ ) std::cout << "FAILS eta cut." << std::endl;
    return false;
  }
  if ( std::fabs(muon.dxy()) > max_dxy_ ) {
    if ( debug_ ) std::cout << "FAILS dxy cut." << std::endl;
    return false;
  }
  if ( std::fabs(muon.dz()) > max_dz_ ) {
    if ( debug_ ) std::cout << "FAILS dz cut." << std::endl;
    return false;
  }
  if ( muon.relIso() > max_relIso_ ) {
    if ( debug_ ) std::cout << "FAILS relIso cut." << std::endl;
    return false;
  }
  if ( muon.sip3d() > max_sip3d_ ) {
    if ( debug_ ) std::cout << "FAILS sip3d cut." << std::endl;
    return false;
  }
  if ( apply_looseIdPOG_ && !muon.passesLooseIdPOG() ) {
    if ( debug_ ) std::cout << "FAILS looseIdPOG cut." << std::endl;
    return false;
  }
  if ( muon.jetBtagCSV() > max_jetBtagCSV_ ) {
    if ( debug_ ) std::cout << "FAILS jetBtagCSV cut." << std::endl;
    return false;
  }
  if ( apply_mediumIdPOG_ && !muon.passesMediumIdPOG() ) {
    if ( debug_ ) std::cout << "FAILS mediumIdPOG cut." << std::endl;
    return false;
  }
  if ( muon.mvaRawTTH() < min_mvaTTH_ ) {
    if ( debug_ ) std::cout << "FAILS mvaTTH cut." << std::endl;
    return false;
  }
  // muon passes all cuts
  if ( set_selection_flags_ ) muon.set_isTight();
  return true;
}
