#include "tthAnalysis/HiggsToTauTau/interface/RecoElectronCollectionSelectorLoose.h" // RecoElectronSelectorLoose

#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // Era::k*
#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h"         // cmsException(), assert()

RecoElectronSelectorLoose::RecoElectronSelectorLoose(Era era,
                                                     int index,
                                                     bool debug,
                                                     bool set_selection_flags)
  : set_selection_flags_(set_selection_flags)
  , debug_(debug)
  , era_(era)
  , min_pt_(7.)
  , max_absEta_(2.5)
  , max_dxy_(0.05)
  , max_dz_(0.1)
  , max_relIso_(0.4)
  , max_sip3d_(8.)
  , apply_tightCharge_(false)
  , apply_conversionVeto_(false)
  , max_nLostHits_(1)
{}

void
RecoElectronSelectorLoose::set_min_pt(double min_pt)
{
  min_pt_ = min_pt;
}

void
RecoElectronSelectorLoose::set_max_absEta(double max_absEta)
{
  max_absEta_ = max_absEta;
}

double
RecoElectronSelectorLoose::get_min_pt() const
{
  return min_pt_;
}

double
RecoElectronSelectorLoose::get_max_absEta() const
{
  return max_absEta_;
}

bool
RecoElectronSelectorLoose::operator()(const RecoElectron & electron) const
{
  if(debug_)
  {
    std::cout << get_human_line(this, __func__) << ":\n" << electron;
  }

  if(electron.pt() < min_pt_)
  {
    if(debug_)
    {
      std::cout << "FAILS pT = " << electron.pt() << " >= " << min_pt_ << " loose cut\n";
    }
    return false;
  }
  if(electron.absEta() > max_absEta_)
  {
    if(debug_)
    {
      std::cout << "FAILS abs(eta) = " << electron.absEta() << " <= " << max_absEta_ << " loose cut\n";
    }
    return false;
  }
  if(std::fabs(electron.dxy()) > max_dxy_)
  {
    if(debug_)
    {
      std::cout << "FAILS abs(dxy) = " << std::fabs(electron.dxy()) << " <= " << max_dxy_ << " loose cut\n";
    }
    return false;
  }
  if(std::fabs(electron.dz()) > max_dz_)
  {
    if(debug_)
    {
      std::cout << "FAILS max(dz) = " << std::fabs(electron.dz()) << " <= " << max_dz_ << " loose cut\n";
    }
    return false;
  }
  if(electron.relIso() > max_relIso_)
  {
    if(debug_)
    {
      std::cout << "FAILS relIso = " << electron.relIso() << " <= " << max_relIso_ << " loose cut\n";
    }
    return false;
  }
  if(electron.sip3d() > max_sip3d_)
  {
    if(debug_)
    {
      std::cout << "FAILS sip3d = " << electron.sip3d() << " <= " << max_sip3d_ << " loose cut\n";
    }
    return false;
  }
  if(electron.nLostHits() > max_nLostHits_)
  {
    if(debug_)
    {
      std::cout << "FAILS nLostHits = " << electron.nLostHits() << " <= " << max_nLostHits_ << " loose cut\n";
    }
    return false;
  }
  if(apply_conversionVeto_ && ! electron.passesConversionVeto())
  {
    if(debug_)
    {
      std::cout << "FAILS conversion veto loose cut\n";
    }
    return false;
  }
  if(apply_tightCharge_ && electron.tightCharge() < 2)
  {
    if(debug_)
    {
      std::cout << "FAILS tight charge loose cut\n";
    }
    return false;
  }

  if(! electron.mvaID_POG(EGammaWP::WPL))
  {
    if(debug_)
    {
      std::cout << "FAILS loose EGamma POG MVA loose cut\n";
    }
    return false;
  }

  if(set_selection_flags_)
  {
    electron.set_isLoose();
  }

  return true;
}
