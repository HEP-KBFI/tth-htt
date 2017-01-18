#include "tthAnalysis/HiggsToTauTau/interface/RecoJetCollectionSelector.h" // RecoJetSelector

#include <cmath> // fabs

RecoJetSelector::RecoJetSelector(int era, int index, bool debug)
  : min_pt_(25.)
  , max_absEta_(2.4)
{}

bool RecoJetSelector::operator()(const RecoJet& jet) const
{
  if ( jet.pt() >= min_pt_ &&
       jet.absEta() <= max_absEta_ ) {
    return true;
  } 
  return false;
}
