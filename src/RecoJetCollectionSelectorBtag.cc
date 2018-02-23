#include "tthAnalysis/HiggsToTauTau/interface/RecoJetCollectionSelectorBtag.h" // RecoJetSelector

#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // kEra_2017
#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h" // cmsException()

RecoJetSelectorBtag::RecoJetSelectorBtag(int era,
                                         int index,
                                         bool debug)
  : era_(era)
  , debug_(debug)
  , min_pt_(25.)
  , max_absEta_(2.4)
  , min_BtagCSV_(-1.e+3)
{}

RecoJetSelectorBtagLoose::RecoJetSelectorBtagLoose(int era,
                                                   int index,
                                                   bool debug)
  : RecoJetSelectorBtag(era, index, debug)
{
  // NB! no btag CSVv2 WPs for 2017, yet!
  switch(era_)
  {
    case kEra_2017:
    {
      // Karl: CSV loose WP, cf. https://twiki.cern.ch/twiki/bin/viewauth/CMS/BtagRecommendation94X
      min_BtagCSV_ = 0.5803;
      break;
    }
    default: throw cmsException(this) << "Invalid era = " << era_;
  }
}

RecoJetSelectorBtagMedium::RecoJetSelectorBtagMedium(int era,
                                                     int index,
                                                     bool debug)
  : RecoJetSelectorBtag(era, index, debug)
{
  // NB! no btag CSVv2 WPs for 2017, yet!
  switch(era_)
  {
    case kEra_2017:
    {
      // Karl: CSV medium WP, cf. https://twiki.cern.ch/twiki/bin/viewauth/CMS/BtagRecommendation94X
      min_BtagCSV_ = 0.8838;
      break;
    }
    default: throw cmsException(this) << "Invalid era = " << era_;
  }
}

bool
RecoJetSelectorBtag::operator()(const RecoJet & jet) const
{
  if(debug_)
  {
    std::cout << "<RecoJetSelectorBtag::operator()>:\n jet: " << jet << '\n';
  }

  if(jet.pt() < min_pt_)
  {
    if(debug_)
    {
      std::cout << "FAILS pT >= " << min_pt_ << " cut\n";
    }
    return false;
  }
  if(jet.absEta() > max_absEta_)
  {
    if(debug_)
    {
      std::cout << "FAILS abs(eta) <= " << max_absEta_ << " cut\n";
    }
    return false;
  }
  if(jet.BtagCSV() < min_BtagCSV_)
  {
    if(debug_)
    {
      std::cout << "FAILS b-tagging CSV >= " << min_BtagCSV_ << " cut\n";
    }
    return false;
  }

  // jet passes all cuts
  return true;
}
