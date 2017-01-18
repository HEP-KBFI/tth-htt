#include "tthAnalysis/HiggsToTauTau/interface/RecoJetCollectionSelectorBtag.h" // RecoJetSelector

#include <cmath> // fabs

RecoJetSelectorBtag::RecoJetSelectorBtag(int era, int index, bool debug)
  : era_(era)
  , debug_(debug)
  , min_pt_(25.)
  , max_absEta_(2.4)
  , min_BtagCSV_(-1.e+3)  
{}

bool RecoJetSelectorBtag::operator()(const RecoJet& jet) const
{
  if ( debug_ ) {
    std::cout << "<RecoJetSelectorBtag::operator()>:" << std::endl;
    std::cout << " jet: pT = " << jet.pt() << ", eta = " << jet.eta() << ", phi = " << jet.phi() << ", CSV = " << jet.BtagCSV() << std::endl;
  }
  if ( jet.pt() < min_pt_ ) {
    if ( debug_ ) std::cout << "FAILS pT cut." << std::endl;
    return false;
  }
  if ( jet.absEta() > max_absEta_ ) {
    if ( debug_ ) std::cout << "FAILS eta cut." << std::endl;
    return false;
  }
  if ( jet.BtagCSV() < min_BtagCSV_ ) {
    if ( debug_ ) std::cout << "FAILS CSV cut (" << min_BtagCSV_ << ")." << std::endl;
    return false;
  }
  // jet passes all cuts
  return true;
}
