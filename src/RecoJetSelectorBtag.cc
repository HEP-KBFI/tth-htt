#include "tthAnalysis/HiggsToTauTau/interface/RecoJetSelectorBtag.h" // RecoJetSelector

#include <cmath> // fabs

RecoJetSelectorBtag::RecoJetSelectorBtag()
  : min_pt_(25.)
  , max_absEta_(2.4)
  , min_BtagCSV_(-1.e+3)  
{}

bool RecoJetSelectorBtag::operator()(const RecoJet& jet) const
{
  if ( jet.pt_ >= min_pt_ &&
       jet.absEta_ <= max_absEta_ &&
       jet.BtagCSV_ >= min_BtagCSV_ ) {
    return true;
  } 
  return false;
}
