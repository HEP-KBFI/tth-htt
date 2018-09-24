#include "tthAnalysis/HiggsToTauTau/interface/RecoJetCollectionSelectorBtag.h" // RecoJetSelector

#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // kEra_*
#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h" // cmsException()

RecoJetSelectorBtag::RecoJetSelectorBtag(int era,
                                         int index,
                                         bool debug)
  : era_(era)
  , debug_(debug)
  , min_pt_(25.)
  , max_absEta_(2.4)
  , min_jetId_(-1.e+3)
  , min_BtagCSV_(-1.e+3)
{
  switch(era)
  {
    case kEra_2016: break;
    case kEra_2017: min_jetId_ = 2; break; // 2 means tight (loose jet ID deprecated since 94x)
    case kEra_2018: throw cmsException(this) << "Implement me!";
    default: throw cmsException(this) << "Implement me!";
  }
}

void
RecoJetSelectorBtag::set_min_pt(double min_pt)
{
  min_pt_ = min_pt;
}

void
RecoJetSelectorBtag::set_max_absEta(double max_absEta)
{
  max_absEta_ = max_absEta;
}

void
RecoJetSelectorBtag::set_min_jetId(int min_jetId)
{
  min_jetId_ = min_jetId;
}

double
RecoJetSelectorBtag::get_min_pt() const
{
  return min_pt_;
}

double
RecoJetSelectorBtag::get_max_absEta() const
{
  return max_absEta_;
}

int
RecoJetSelectorBtag::get_min_jetId() const
{
  return min_jetId_;
}

RecoJetSelectorBtagLoose::RecoJetSelectorBtagLoose(int era,
                                                   int index,
                                                   bool debug)
  : RecoJetSelectorBtag(era, index, debug)
{
  min_BtagCSV_ = get_BtagWP(era_, BtagWP::kLoose);
}

RecoJetSelectorBtagMedium::RecoJetSelectorBtagMedium(int era,
                                                     int index,
                                                     bool debug)
  : RecoJetSelectorBtag(era, index, debug)
{
  min_BtagCSV_ = get_BtagWP(era_, BtagWP::kMedium);
}

bool
RecoJetSelectorBtag::operator()(const RecoJet & jet) const
{
  if(debug_)
  {
    std::cout << get_human_line(this, __func__) << ":\n jet: " << jet << '\n';
  }

  if(jet.pt() < min_pt_)
  {
    if(debug_)
    {
      std::cout << "FAILS pT >= " << min_pt_ << " cut\n";
    }
    return false;
  }
  if(max_absEta_ > 0. && jet.absEta() > max_absEta_)
  {
    if(debug_)
    {
      std::cout << "FAILS abs(eta) <= " << max_absEta_ << " cut\n";
    }
    return false;
  }
  if(jet.jetId() < min_jetId_)
  {
    if(debug_)
    {
      std::cout << "FAILS jet ID >= " << min_jetId_ << " cut\n";
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
