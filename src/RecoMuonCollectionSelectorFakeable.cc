#include "tthAnalysis/HiggsToTauTau/interface/RecoMuonCollectionSelectorFakeable.h" // RecoMuonSelectorFakeable

#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // kEra_2017
#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h" // cmsException()

RecoMuonSelectorFakeable::RecoMuonSelectorFakeable(int era,
                                                   int index,
                                                   bool debug,
                                                   bool set_selection_flags)
  : era_(era)
  , debug_(debug)
  , set_selection_flags_(set_selection_flags)
  , tightMuonSelector_(era_, index, debug, false)
  , min_cone_pt_(10.)
  , min_lepton_pt_(5.)
  , max_absEta_(2.4)
  , max_dxy_(0.05)
  , max_dz_(0.1)
  , max_relIso_(0.4)
  , max_sip3d_(8.)
  , apply_looseIdPOG_(true)
  , binning_mvaTTH_({ 0.90 }) // Table 6 in AN2017_029_v5
  , min_jetPtRatio_({ 0.50, -1.e+3 }) // Table 6 in AN2017_029_v5
  , apply_mediumIdPOG_(false)
  , min_segmentCompatibility_({0.3, -1.e+3})
{
  switch(era_)
  {
    case kEra_2017:
    {
      max_jetBtagCSV_ = { 0.3, BtagWP_CSV_2016.at(BtagWP::kMedium) };  // Table 6 in AN2017_029_v5
      break;
    }
    default: throw cmsException(this) << "Invalid era: " << era_;
  }
}

bool
RecoMuonSelectorFakeable::operator()(const RecoMuon & muon) const
{
  if(debug_)
  {
    std::cout << __func__ << ":\n" << muon;
  }

  if(muon.cone_pt() < min_cone_pt_)
  {
    if(debug_)
    {
      std::cout << "FAILS cone pT >= " << min_cone_pt_ << " fakeable cut\n";
    }
    return false;
  }

  if(muon.lepton_pt() < min_lepton_pt_)
  {
    if(debug_)
    {
      std::cout << "FAILS pT >= " << min_lepton_pt_ << " fakeable cut\n";
    }
  }

  if(muon.absEta() > max_absEta_)
  {
    if(debug_)
    {
      std::cout << "FAILS abs(eta) <= " << max_absEta_ << " fakeable cut\n";
    }
    return false;
  }

  if(std::fabs(muon.dxy()) > max_dxy_)
  {
    if(debug_)
    {
      std::cout << "FAILS abs(dxy) <= " << max_dxy_ << " fakeable cut\n";
    }
    return false;
  }

  if(std::fabs(muon.dz()) > max_dz_)
  {
    if(debug_)
    {
      std::cout << "FAILS abs(dz) <= " << max_dz_ << " fakeable cut\n";
    }
    return false;
  }

  if(muon.relIso() > max_relIso_)
  {
    if(debug_)
    {
      std::cout << "FAILS relIso <= " << max_relIso_ << " fakeable cut\n";
    }
    return false;
  }

  if(muon.sip3d() > max_sip3d_)
  {
    if(debug_)
    {
      std::cout << "FAILS sip3d <= " << max_sip3d_ << " fakeable cut\n";
    }
    return false;
  }

  if(! muon.passesLooseIdPOG() && apply_looseIdPOG_)
  {
    if(debug_)
    {
      std::cout << "FAILS loose POG fakeable cut\n";
    }
    return false;
  }

  if(! muon.passesMediumIdPOG() && apply_mediumIdPOG_)
  {
    if(debug_)
    {
      std::cout << "FAILS medium POG fakeable cut\n";
    }
    return false;
  }

  const int idxBin = muon.mvaRawTTH() <= binning_mvaTTH_[0] ? 0 : 1;

  if(muon.jetPtRatio() < min_jetPtRatio_[idxBin])
  {
    if(debug_)
    {
      std::cout << "FAILS jetPtRatio >= " << min_jetPtRatio_[idxBin] << " fakeable cut\n";
    }
    return false;
  }

  if(muon.jetBtagCSV() > max_jetBtagCSV_[idxBin])
  {
    if(debug_)
    {
      std::cout << "FAILS jetBtagCSV <= " << max_jetBtagCSV_[idxBin] << " fakeable cut\n";
    }
    return false;
  }

  if(muon.segmentCompatibility() <= min_segmentCompatibility_[idxBin])
  {
    if(debug_)
    {
      std::cout << "FAILS segmentCompatibility > " << min_segmentCompatibility_[idxBin] << " fakeable cut\n";
    }
    return false;
  }

  if(set_selection_flags_)
  {
    muon.set_isFakeable();
    if(tightMuonSelector_(muon))
    {
      muon.set_isTight();
    }
  }

  return true;
}

void
RecoMuonSelectorFakeable::set_selection_flags(bool selection_flags)
{
  set_selection_flags_ = selection_flags;
}

RecoMuonCollectionSelectorFakeable::RecoMuonCollectionSelectorFakeable(int era,
                                                                       int index,
                                                                       bool debug,
                                                                       bool set_selection_flags)
  : ParticleCollectionSelector<RecoMuon, RecoMuonSelectorFakeable>(era, index, debug)
{
  selector_.set_selection_flags(set_selection_flags);
}
