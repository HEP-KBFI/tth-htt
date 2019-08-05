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
  , min_cone_pt_(10.) // F
  , min_lepton_pt_(5.) // L
  , max_absEta_(2.4) // L
  , max_dxy_(0.05) // L
  , max_dz_(0.1) // L
  , max_relIso_(0.4) // L
  , max_sip3d_(8.) // L
  , apply_looseIdPOG_(true) // L
  , apply_mediumIdPOG_(false) // L
  , wp_mvaTTH_(0.85) // F
  , min_jetPtRatio_(2. / 3) // F
  , min_jetBtagCSV_(get_BtagWP(era_, Btag::kDeepJet, BtagWP::kLoose)) // F
  , max_jetBtagCSV_(get_BtagWP(era_, Btag::kDeepJet, BtagWP::kMedium)) // F
  , smoothBtagCut_minPt_(20.)
  , smoothBtagCut_maxPt_(45.)
  , smoothBtagCut_ptDiff_(smoothBtagCut_maxPt_ - smoothBtagCut_minPt_)
{
  // L -- inherited from the preselection (loose cut)
  // F -- additional fakeable cut not applied in the preselection
}

void RecoMuonSelectorFakeable::set_mvaTTH_wp(double wp_mvaTTH)
{
  std::cout << "setting cut on prompt-lepton MVA for fakeable muons: " << wp_mvaTTH_ << '\n';
  wp_mvaTTH_ = wp_mvaTTH;
}

double RecoMuonSelectorFakeable::get_mvaTTH_wp() const
{
  return wp_mvaTTH_;
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
      std::cout << "FAILS cone pT = " << muon.cone_pt() << " >= " << min_cone_pt_ << " fakeable cut\n";
    }
    return false;
  }

  if(muon.lepton_pt() < min_lepton_pt_)
  {
    if(debug_)
    {
      std::cout << "FAILS pT = " << muon.pt() << " >= " << min_lepton_pt_ << " fakeable cut\n";
    }
  }

  if(muon.absEta() > max_absEta_)
  {
    if(debug_)
    {
      std::cout << "FAILS abs(eta) = " << muon.absEta() << " <= " << max_absEta_ << " fakeable cut\n";
    }
    return false;
  }

  if(std::fabs(muon.dxy()) > max_dxy_)
  {
    if(debug_)
    {
      std::cout << "FAILS abs(dxy) = " << std::fabs(muon.dxy()) << " <= " << max_dxy_ << " fakeable cut\n";
    }
    return false;
  }

  if(std::fabs(muon.dz()) > max_dz_)
  {
    if(debug_)
    {
      std::cout << "FAILS abs(dz) = " << std::fabs(muon.dz()) << " <= " << max_dz_ << " fakeable cut\n";
    }
    return false;
  }

  if(muon.relIso() > max_relIso_)
  {
    if(debug_)
    {
      std::cout << "FAILS relIso = " << muon.relIso() << " <= " << max_relIso_ << " fakeable cut\n";
    }
    return false;
  }

  if(muon.sip3d() > max_sip3d_)
  {
    if(debug_)
    {
      std::cout << "FAILS sip3d = " << muon.sip3d() << " <= " << max_sip3d_ << " fakeable cut\n";
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
  if(muon.jetBtagCSV() > max_jetBtagCSV_)
  {
    if(debug_)
    {
      std::cout << "FAILS jetBtagCSV = " << muon.jetBtagCSV() << " <= " << max_jetBtagCSV_ << " fakeable cut\n";
    }
    return false;
  }

  if(muon.mvaRawTTH() <= wp_mvaTTH_)
  {
    if(muon.jetPtRatio() < min_jetPtRatio_)
    {
      if(debug_)
      {
        std::cout << "FAILS jetPtRatio = " << muon.jetPtRatio() << " >= " << min_jetPtRatio_ << " fakeable cut\n";
      }
      return false;
    }

    const double max_jetBtagCSV = smoothBtagCut(muon.assocJet_pt());
    if(debug_)
    {
      std::cout << get_human_line(this, __func__) << ": smooth jetBtagCSV cut = " << max_jetBtagCSV << '\n';
    }
    if(muon.jetBtagCSV() > max_jetBtagCSV)
    {
      if(debug_)
      {
        std::cout << "FAILS smooth jetBtagCSV = " << muon.jetBtagCSV() << " <= " << max_jetBtagCSV << " fakeable cut\n";
      }
      return false;
    }
  }

  if(set_selection_flags_)
  {
    muon.set_isFakeable();
  }

  return true;
}

double
RecoMuonSelectorFakeable::smoothBtagCut(double assocJet_pt) const
{
  const double ptInterp = std::min(1., std::max(0., assocJet_pt - smoothBtagCut_minPt_) / smoothBtagCut_ptDiff_);
  return ptInterp * min_jetBtagCSV_ + (1. - ptInterp) * max_jetBtagCSV_;
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
