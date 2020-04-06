#include "tthAnalysis/HiggsToTauTau/interface/RecoJetCollectionSelectorBtag.h"

#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // Era::k*
#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h"         // cmsException()

RecoJetSelectorBtag::RecoJetSelectorBtag(Era era,
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
    case Era::k2016: min_jetId_ = 1; break; // 1 means loose
    case Era::k2017:
    case Era::k2018: min_jetId_ = 2; break; // 2 means tight (loose jet ID deprecated since 94x)
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

  if(jet.pt() < min_pt_)
  {
    if(debug_)
    {
      std::cout << "FAILS pT = " << jet.pt() << " >= " << min_pt_ << " cut\n";
    }
    return false;
  }
  if(max_absEta_ > 0. && jet.absEta() > max_absEta_)
  {
    if(debug_)
    {
      std::cout << "FAILS abs(eta) = " << jet.absEta() << " <= " << max_absEta_ << " cut\n";
    }
    return false;
  }
  // CV: Ignore jets with 2.65 < |eta| < 3.139 and pT < 50 GeV when selecting jets in 2017 data and MC,
  //     in order to reduce effect of noise in ECAL endcap,
  //     cf. slide 13 of presentation by Alexei Raspereza in HTT meeting on October 10th 2018
  //    (https://indico.cern.ch/event/762837/contributions/3172618/attachments/1731302/2798220/Recoils_20181010.pdf )
  // Karl: "rounded" the eta thresholds, increased the pT threshold and applied it equally to all eras, see:
  // https://gitlab.cern.ch/ttH_leptons/doc/blob/01f187e5b2efb39f93004acb7606a149c765ea18/Legacy/objects.md#23-jets
  if(jet.pt() < 60. && jet.absEta() > 2.7 && jet.absEta() < 3.)
  {
    if(debug_)
    {
      std::cout << "FAILS EE noise cut\n";
    }
    return false;
  }
  if(jet.jetId() < min_jetId_)
  {
    if(debug_)
    {
      std::cout << "FAILS jet ID = " << jet.jetId() << " >= " << min_jetId_ << " cut\n";
    }
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
