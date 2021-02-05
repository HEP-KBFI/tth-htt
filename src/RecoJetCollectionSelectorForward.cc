#include "tthAnalysis/HiggsToTauTau/interface/RecoJetCollectionSelectorForward.h"

#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h"         // get_human_line()
#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // Era::k*

RecoJetSelectorForward::RecoJetSelectorForward(Era era,
                                               int index,
                                               bool debug)
  : RecoJetSelector(era, index, debug)
  , min_absEta_(2.4)
{
  RecoJetSelector::set_max_absEta(5.0);
}

double
RecoJetSelectorForward::get_min_absEta() const
{
  return min_absEta_;
}

bool
RecoJetSelectorForward::operator()(const RecoJet & jet) const
{
  if(debug_)
  {
    std::cout << get_human_line(this, __func__) << ":\n jet: " << jet << '\n';
  }
  if(! RecoJetSelector::operator()(jet))
  {
    return false;
  }
  if(min_absEta_ > 0. && jet.absEta() < min_absEta_)
  {
    if(debug_)
    {
      std::cout << "FAILS abs(eta) = " << jet.absEta() << " >= " << min_absEta_ << " cut\n";
    }
    return false;
  }
  return true;
}
