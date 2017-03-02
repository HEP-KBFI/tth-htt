#include "tthAnalysis/HiggsToTauTau/interface/RecoJetCollectionSelector.h" // RecoJetSelector

#include <cmath> // fabs

RecoJetSelector::RecoJetSelector(int era, int index, bool debug)
  : min_pt_(25.)
  , max_absEta_(2.4)
  , debug_(debug)
{}

bool RecoJetSelector::operator()(const RecoJet& jet) const
{
  if ( debug_ ) {
    std::cout << "<RecoJetSelector::operator()>:" << std::endl;
    std::cout << (jet.pt() >= min_pt_ && jet.absEta() <= max_absEta_) << " jet: pT = " << jet.pt() << ", eta = " << jet.eta() << ", phi = " << jet.phi() << ", CSV = " << jet.BtagCSV() << std::endl;
  }
  if ( jet.pt() >= min_pt_ &&
       jet.absEta() <= max_absEta_ ) {
    return true;
  } 
  return false;
}
