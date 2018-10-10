#include "tthAnalysis/HiggsToTauTau/interface/RecoJetCollectionSelector.h" // RecoJetSelector

#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h" // get_human_line()
#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // kEra_*

RecoJetSelector::RecoJetSelector(int era,
                                 int index,
                                 bool debug)
  : era_(era)
  , min_pt_(25.)
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
  if(max_absEta_ > 0. && jet.absEta() > max_absEta_)
  {
    if(debug_)
    {
      std::cout << "FAILS abs(eta) <= " << max_absEta_ << " cut\n";
    }
    return false;
  }
  // CV: Ignore jets with 2.65 < |eta| < 3.139 and pT < 50 GeV when selecting jets in 2017 data and MC,
  //     in order to reduce effect of noise in ECAL endcap,
  //     cf. slide 13 of presentation by Alexei Raspereza in HTT meeting on October 10th 2018
  //    (https://indico.cern.ch/event/762837/contributions/3172618/attachments/1731302/2798220/Recoils_20181010.pdf )
  if ( era_ == kEra_2017 && jet.pt() < 50. && jet.absEta() > 2.65 && jet.absEta() < 3.159 ) {
    if(debug_)
    {
      std::cout << "FAILS EE noise cut, introduced for 2017 analysis\n";
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
