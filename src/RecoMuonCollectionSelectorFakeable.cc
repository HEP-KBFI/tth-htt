#include "tthAnalysis/HiggsToTauTau/interface/RecoMuonCollectionSelectorFakeable.h" // RecoMuonSelectorFakeable

#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // kEra_*
#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h" // cmsException()

RecoMuonSelectorFakeable::RecoMuonSelectorFakeable(int era,
                                                   int index,
                                                   bool debug,
                                                   bool set_selection_flags)
  : era_(era)
  , debug_(debug)
  , set_selection_flags_(set_selection_flags)
  , min_cone_pt_(-1.e+3)
  , min_lepton_pt_(-1.e+3)
  , max_absEta_(2.4) // L
  , max_dxy_(0.05) // L
  , max_dz_(0.1) // L
  , max_relIso_(0.4) // L
  , max_sip3d_(8.) // L
  , apply_looseIdPOG_(true) // L
  , apply_mediumIdPOG_(false) // L
{
  switch(era_)
  {
    case kEra_2016:
    {
// CV: use original lepton pT instead of mixing lepton pT and cone_pT, as discussed on slide 2 of
//     https://indico.cern.ch/event/597028/contributions/2413742/attachments/1391684/2120220/16.12.22_ttH_Htautau_-_Review_of_systematics.pdf
      min_cone_pt_ = -1.e+3;
      min_lepton_pt_ = 10.;
      binning_mvaTTH_ = { 0.75 };
      min_jetPtRatio_ = { 0.30, -1.e+3 };
      min_segmentCompatibility_ = { -1.e+3, -1.e+3 }; // F
      max_jetBtagCSV_ = { BtagWP_CSV_2016.at(BtagWP::kLoose), BtagWP_CSV_2016.at(BtagWP::kMedium) };
      break;
    }
    case kEra_2017:
    {
      min_cone_pt_ = 10.; // F
      min_lepton_pt_ = 5.; // L
      binning_mvaTTH_ = { 0.90 }; // F; Table 6 in AN2017_029_v5
      min_jetPtRatio_ = { 0.60, -1.e+3 }; // F; [*]
      min_segmentCompatibility_ = { 0.3, -1.e+3 }; // F
      max_jetBtagCSV_ = { 0.07, BtagWP_deepCSV_2017.at(BtagWP::kMedium) };  // F; [*]
      break;
    }
    case kEra_2018:
    {
      throw cmsException(this) << "Implement me!";
    }
    default: throw cmsException(this) << "Invalid era: " << era_;
  }
  assert(min_lepton_pt_ > 0.);
  assert(binning_mvaTTH_.size() == 1);
  assert(min_jetPtRatio_.size() == binning_mvaTTH_.size() + 1);
  assert(min_segmentCompatibility_.size() == binning_mvaTTH_.size() + 1);
  assert(max_jetBtagCSV_.size() == binning_mvaTTH_.size() + 1);
  // L -- inherited from the preselection (loose cut)
  // F -- additional fakeable cut not applied in the preselection
  // [*] https://gitlab.cern.ch/ttH_leptons/doc/blob/dbb7082bb3668bb3e839293602bc16f47f11c515/2017/objects.md
}

bool
RecoMuonSelectorFakeable::operator()(const RecoMuon & muon) const
{
  if(debug_)
  {
    std::cout << get_human_line(this, __func__) << ":\n" << muon;
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
