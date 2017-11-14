#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTauCollectionSelectorBase.h" // RecoHadTauSelectorBase

#include <cmath> // fabs

RecoHadTauSelectorBase::RecoHadTauSelectorBase(int era, int index, bool debug, bool set_selection_flags)
  : set_selection_flags_(set_selection_flags)
  , debug_(debug)
  , min_pt_(20.)
  , max_absEta_(2.3)
  , max_dz_(0.2)
  , apply_decayModeFinding_(true)
  , min_id_mva_dR03_(-1000)
  , min_raw_mva_dR03_(-1.e+6)
  , min_id_mva_dR05_(-1000)
  , min_raw_mva_dR05_(-1.e+6)
  , min_id_cut_dR03_(-1000)
  , max_raw_cut_dR03_(1.e+6)
  , min_id_cut_dR05_(-1000)
  , min_antiElectron_(-1000)
  , min_antiMuon_(-1000)   
{}

bool RecoHadTauSelectorBase::operator()(const RecoHadTau& hadTau) const
{
  if ( debug_ ) {
    std::cout << "<RecoHadTauSelectorBase::operator()>:" << std::endl;
    std::cout << " hadTau: pT = " << hadTau.pt() << ", eta = " << hadTau.eta() << ", phi = " << hadTau.phi() << ", charge = " << hadTau.charge() << std::endl;
  }
  if ( hadTau.pt() < min_pt_ ) {
    if ( debug_ ) std::cout << "FAILS pT cut." << std::endl;
    return false;
  }
  if ( hadTau.absEta() > max_absEta_ ) {
    if ( debug_ ) std::cout << "FAILS eta cut." << std::endl;
    return false;
  }
  if ( std::fabs(hadTau.dz()) > max_dz_ ) {
    if ( debug_ ) std::cout << "FAILS dz cut." << std::endl;
    return false;
  }
  if ( apply_decayModeFinding_ && ! hadTau.decayModeFinding() ) {
    if ( debug_ ) std::cout << "FAILS decayModeFinding cut." << std::endl;
    return false;
  }
  if ( hadTau.id_mva_dR03() < min_id_mva_dR03_ ) {
    if ( debug_ ) std::cout << "FAILS id_mva_dR03 cut." << std::endl;
    return false;
  }
  if ( hadTau.raw_mva_dR03() < min_raw_mva_dR03_ ) {
    if ( debug_ ) std::cout << "FAILS raw_mva_dR03 cut." << std::endl;
    return false;
  }
  if ( hadTau.id_mva_dR05() < min_id_mva_dR05_ ) {
    if ( debug_ ) std::cout << "FAILS id_mva_dR05 cut." << std::endl;
    return false;
  }
  if ( hadTau.raw_mva_dR05() < min_raw_mva_dR05_ ) {
    if ( debug_ ) std::cout << "FAILS raw_mva_dR05 cut." << std::endl;
    return false;
  }
  if ( hadTau.id_cut_dR03() < min_id_cut_dR03_ ) {
    if ( debug_ ) std::cout << "FAILS id_cut_dR03 cut." << std::endl;
    return false;
  }
  if ( hadTau.raw_cut_dR03() > max_raw_cut_dR03_ ) {
    if ( debug_ ) std::cout << "FAILS raw_cut_dR03 cut." << std::endl;
    return false;
  }
  if ( hadTau.id_cut_dR05() < min_id_cut_dR05_ ) {
    if ( debug_ ) std::cout << "FAILS id_cut_dR05 cut." << std::endl;
    return false;
  }
  if ( hadTau.antiElectron() < min_antiElectron_ ) {
    if ( debug_ ) std::cout << "FAILS antiElectron cut." << std::endl;
    return false;
  }
  if ( hadTau.antiMuon() < min_antiMuon_ ) {
    if ( debug_ ) std::cout << "FAILS antiMuon cut." << std::endl;
    return false;
  }
  // hadTau passes all cuts
  if ( set_selection_flags_ ) set_selection_flags(hadTau);
  return true;
}
