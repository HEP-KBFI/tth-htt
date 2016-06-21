#include "tthAnalysis/HiggsToTauTau/interface/RecoJetSelector.h" // RecoJetSelector

#include <cmath> // fabs

RecoJetSelector::RecoJetSelector(bool debug)
  : min_pt_(25.)
  , max_absEta_(2.4)
{}

bool RecoJetSelector::operator()(const RecoJet& jet) const
{
  if ( jet.pt_ >= min_pt_ &&
       jet.absEta_ <= max_absEta_ ) {
    return true;
  } 
  return false;
}
