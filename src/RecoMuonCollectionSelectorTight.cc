#include "tthAnalysis/HiggsToTauTau/interface/RecoMuonCollectionSelectorTight.h" // RecoMuonSelectorTight

#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // kEra_2017
#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h" // cmsException()

RecoMuonSelectorTight::RecoMuonSelectorTight(int era,
                                             int index,
                                             bool debug,
                                             bool set_selection_flags)
  : era_(era)
  , set_selection_flags_(set_selection_flags)
  , debug_(debug)
  , min_pt_(5.)
  , max_absEta_(2.4)
  , max_dxy_(0.05)
  , max_dz_(0.1)
  , max_relIso_(0.4)
  , max_sip3d_(8.)
  , apply_looseIdPOG_(true)
  , apply_mediumIdPOG_(true)
  , min_mvaTTH_(0.75)
{
  switch(era_)
  {
    case kEra_2017:
    {
      max_jetBtagCSV_ = 0.8484;
      break;
    }
    default: throw cmsException(this) << "Invalid era: " << era_;
  }
}

bool
RecoMuonSelectorTight::operator()(const RecoMuon & muon) const
{
  if(debug_)
  {
    std::cout << "<RecoMuonSelectorTight::operator()>:\n muon: " << muon << '\n';
  }

  if(muon.pt() < min_pt_)
  {
    if(debug_)
    {
      std::cout << "FAILS pT >= " << min_pt_ << " tight cut\n";
    }
    return false;
  }
  if(muon.absEta() > max_absEta_)
  {
    if(debug_)
    {
      std::cout << "FAILS abs(eta) <= " << max_absEta_ << " tight cut\n";
    }
    return false;
  }
  if(std::fabs(muon.dxy()) > max_dxy_)
  {
    if(debug_)
    {
      std::cout << "FAILS abs(dxy) <= " << max_dxy_ << " tight cut\n";
    }
    return false;
  }
  if(std::fabs(muon.dz()) > max_dz_)
  {
    if(debug_)
    {
      std::cout << "FAILS abs(dz) <= " << max_dz_ << " tight cut\n";
    }
    return false;
  }
  if(muon.relIso() > max_relIso_)
  {
    if(debug_)
    {
      std::cout << "FAILS relIso <= " << max_relIso_ << " tight cut\n";
    }
    return false;
  }
  if(muon.sip3d() > max_sip3d_)
  {
    if(debug_)
    {
      std::cout << "FAILS sip3d <= " << max_sip3d_ << " tight cut\n";
    }
    return false;
  }
  if(apply_looseIdPOG_ && ! muon.passesLooseIdPOG())
  {
    if(debug_)
    {
      std::cout << "FAILS looseIdPOG tight cut\n";
    }
    return false;
  }
  if(muon.jetBtagCSV() > max_jetBtagCSV_)
  {
    if(debug_)
    {
      std::cout << "FAILS jetBtagCSV <= " << max_jetBtagCSV_ << " tight cut\n";
    }
    return false;
  }
  if(apply_mediumIdPOG_ && ! muon.passesMediumIdPOG())
  {
    if(debug_)
    {
      std::cout << "FAILS mediumIdPOG tight cut\n";
    }
    return false;
  }
  if(muon.mvaRawTTH() < min_mvaTTH_)
  {
    if(debug_)
    {
      std::cout << "FAILS mvaTTH >= " << min_mvaTTH_ << " tight cut\n";
    }
    return false;
  }

  // muon passes all cuts
  if(set_selection_flags_)
  {
    muon.set_isTight();
  }
  return true;
}

RecoMuonCollectionSelectorTight::RecoMuonCollectionSelectorTight(int era,
                                                                 int index,
                                                                 bool debug)
  : selIndex_(index)
  , selector_(era, index, debug)
{}

std::vector<const RecoMuon *>
RecoMuonCollectionSelectorTight::operator()(const std::vector<const RecoMuon *> & muons) const
{
  std::vector<const RecoMuon *> selMuons;
  int idx = 0;
  for(const RecoMuon * const & muon: muons)
  {
    if(selector_(*muon))
    {
      if(idx == selIndex_ || selIndex_ == -1)
      {
        selMuons.push_back(muon);
      }
      ++idx;
    }
  }
  return selMuons;
}
