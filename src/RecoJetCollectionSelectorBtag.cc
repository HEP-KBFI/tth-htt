#include "tthAnalysis/HiggsToTauTau/interface/RecoJetCollectionSelectorBtag.h"

#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // Era::k*
#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h"         // cmsException()

RecoJetSelectorBtag::RecoJetSelectorBtag(Era era,
                                         int index,
                                         bool debug)
  : RecoJetSelector(era, index, debug)
  , min_BtagCSV_(-1.e+3)
{}

double
RecoJetSelectorBtag::get_min_BtagCSV() const
{
  return min_BtagCSV_;
}

RecoJetSelectorBtagLoose::RecoJetSelectorBtagLoose(Era era,
                                                   int index,
                                                   bool debug)
  : RecoJetSelectorBtag(era, index, debug)
{
  min_BtagCSV_ = get_BtagWP(era_, Btag::kDeepJet, BtagWP::kLoose);
}

RecoJetSelectorBtagMedium::RecoJetSelectorBtagMedium(Era era,
                                                     int index,
                                                     bool debug)
  : RecoJetSelectorBtag(era, index, debug)
{
  min_BtagCSV_ = get_BtagWP(era_, Btag::kDeepJet, BtagWP::kMedium);
}

bool
RecoJetSelectorBtag::operator()(const RecoJet & jet) const
{
  if(debug_)
  {
    std::cout << get_human_line(this, __func__) << ":\n jet: " << jet << '\n';
  }
  if(! RecoJetSelector::operator()(jet))
  {
    return false;
  }
  if(jet.BtagCSV() < min_BtagCSV_)
  {
    if(debug_)
    {
      std::cout << "FAILS b-tagging CSV = " << jet.BtagCSV() << " >= " << min_BtagCSV_ << " cut\n";
    }
    return false;
  }

  // jet passes all cuts
  return true;
}
