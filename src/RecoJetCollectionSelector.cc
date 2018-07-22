#include "tthAnalysis/HiggsToTauTau/interface/RecoJetCollectionSelector.h" // RecoJetSelector

#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h" // get_human_line()
#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // kEra_*

RecoJetSelector::RecoJetSelector(int era,
                                 int index,
                                 bool debug)
  : min_pt_(25.)
  , max_absEta_(2.4)
  , min_jetId_(-1.e+3)
  , debug_(debug)
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
RecoJetSelector::set_min_pt(double min_pt)
{
  min_pt_ = min_pt;
}

void
RecoJetSelector::set_max_absEta(double max_absEta)
{
  max_absEta_ = max_absEta;
}

void
RecoJetSelector::set_min_jetId(int min_jetId)
{
  min_jetId_ = min_jetId;
}

double
RecoJetSelector::get_min_pt() const
{
  return min_pt_;
}

double
RecoJetSelector::get_max_absEta() const
{
  return max_absEta_;
}

int
RecoJetSelector::get_min_jetId() const
{
  return min_jetId_;
}

bool
RecoJetSelector::operator()(const RecoJet & jet) const
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
  if(jet.absEta() > max_absEta_)
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
  return true;
}
