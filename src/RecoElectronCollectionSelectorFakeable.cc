#include "tthAnalysis/HiggsToTauTau/interface/RecoElectronCollectionSelectorFakeable.h" // RecoElectronSelectorFakeable

#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // kEra_*
#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h" // cmsException(), assert()

RecoElectronSelectorFakeable::RecoElectronSelectorFakeable(int era,
                                                           int index,
                                                           bool debug,
                                                           bool set_selection_flags)
  : era_(era)
  , debug_(debug)
  , set_selection_flags_(set_selection_flags)
  , apply_offline_e_trigger_cuts_(true)
  , min_cone_pt_(10.) // F
  , min_lepton_pt_(7.) // L
  , max_absEta_(2.5) // L
  , max_dxy_(0.05) // L
  , max_dz_(0.1) // L
  , max_relIso_(0.4) // L
  , max_sip3d_(8.) // L
  , binning_absEta_(1.479) // F
  , min_sigmaEtaEta_trig_(0.011) // F
  , max_sigmaEtaEta_trig_(0.019) // F
  , max_HoE_trig_(0.10) // F
  , min_OoEminusOoP_trig_(-0.04) // F
  , wp_mvaTTH_ (0.80) // F
  , min_jetPtRatio_(1. / 1.7) // F
  , max_jetBtagCSV_(get_BtagWP(era_, Btag::kDeepJet, BtagWP::kMedium)) // F
  , apply_conversionVeto_(true) // F
  , max_nLostHits_(0) // F
{
  // L -- inherited from the preselection (loose cut)
  // F -- additional fakeable cut not applied in the preselection
}

void
RecoElectronSelectorFakeable::enable_offline_e_trigger_cuts()
{
  apply_offline_e_trigger_cuts_ = true;
}

void
RecoElectronSelectorFakeable::disable_offline_e_trigger_cuts()
{
  apply_offline_e_trigger_cuts_ = false;
}

void
RecoElectronSelectorFakeable::set_selection_flags(bool selection_flags)
{
  set_selection_flags_ = selection_flags;
}

void RecoElectronSelectorFakeable::set_mvaTTH_wp(double wp_mvaTTH)
{
  std::cout << "setting cut on prompt-lepton MVA for fakeable electrons: " << wp_mvaTTH_ << '\n';
  wp_mvaTTH_ = wp_mvaTTH;
}

double RecoElectronSelectorFakeable::get_mvaTTH_wp() const
{
  return wp_mvaTTH_;
}

bool
RecoElectronSelectorFakeable::operator()(const RecoElectron & electron) const
{
  if(debug_)
  {
    std::cout << get_human_line(this, __func__) << ":\n" << electron;
  }

  if(electron.cone_pt() < min_cone_pt_)
  {
    if(debug_)
    {
      std::cout << "FAILS cone pT >= " << min_cone_pt_ << " fakeable cut\n";
    }
    return false;
  }

  if(electron.lepton_pt() < min_lepton_pt_)
  {
    if(debug_)
    {
      std::cout << "FAILS pT >= " << min_lepton_pt_ << " fakeable cut\n";
    }
  }

  if(electron.absEta() > max_absEta_)
  {
    if(debug_)
    {
      std::cout << "FAILS abs(eta) <= " << max_absEta_ << " fakeable cut\n";
    }
    return false;
  }

  if(std::fabs(electron.dxy()) > max_dxy_)
  {
    if(debug_)
    {
      std::cout << "FAILS abs(dxy) <= " << max_dxy_ << " fakeable cut\n";
    }
    return false;
  }

  if(std::fabs(electron.dz()) > max_dz_)
  {
    if(debug_)
    {
      std::cout << "FAILS abs(dz) <= " << max_dz_ << " fakeable cut\n";
    }
    return false;
  }

  if(electron.relIso() > max_relIso_)
  {
    if(debug_)
    {
      std::cout << "FAILS relIso <= " << max_relIso_ << " fakeable cut\n";
    }
    return false;
  }

  if(electron.sip3d() > max_sip3d_)
  {
    if(debug_)
    {
      std::cout << "FAILS sip3d <= " << max_sip3d_ << " fakeable cut\n";
    }
    return false;
  }

  if(electron.nLostHits() > max_nLostHits_)
  {
    if(debug_)
    {
      std::cout << "FAILS nLostHits <= " << max_nLostHits_ << " fakeable cut\n";
    }
    return false;
  }

  if(! electron.passesConversionVeto() && apply_conversionVeto_)
  {
    if(debug_)
    {
      std::cout << "FAILS conversion veto fakeable cut\n";
    }
    return false;
  }

  if(! electron.mvaID_POG(EGammaWP::WPL))
  {
    if(debug_)
    {
      std::cout << "FAILS loose EGamma POG MVA fakeable cut\n";
    }
    return false;
  }

  if(electron.mvaRawTTH() > wp_mvaTTH_)
  {
    if(electron.jetBtagCSV() > max_jetBtagCSV_)
    {
      if(debug_)
      {
        std::cout << "FAILS jetBtagCSV <= " << max_jetBtagCSV_ << " fakeable cut\n";
      }
      return false;
    }
  }
  else
  {
    if(electron.jetPtRatio() < min_jetPtRatio_)
    {
      if(debug_)
      {
        std::cout << "FAILS jetPtRatio >= " << min_jetPtRatio_ << " fakeable cut\n";
      }
      return false;
    }
    if(! electron.mvaID_POG(EGammaWP::WP80))
    {
      if(debug_)
      {
        std::cout << "FAILS 80% EGamma POG MVA fakeable cut\n";
      }
      return false;
    }
  }

  if(apply_offline_e_trigger_cuts_)
  {
    const double max_sigmaEtaEta_trig = min_sigmaEtaEta_trig_ +
                                        max_sigmaEtaEta_trig_ * (electron.absEta() > binning_absEta_);
    if(electron.sigmaEtaEta() > max_sigmaEtaEta_trig)
    {
      if(debug_)
      {
        std::cout << "FAILS sigmaEtaEta <= " << max_sigmaEtaEta_trig << " fakeable cut\n";
      }
      return false;
    }

    if(electron.HoE() > max_HoE_trig_)
    {
      if(debug_)
      {
        std::cout << "FAILS HoE <= " << max_HoE_trig_ << " fakeable cut\n";
      }
      return false;
    }
    if(electron.OoEminusOoP() < min_OoEminusOoP_trig_)
    {
      if(debug_)
      {
        std::cout << "FAILS OoEminusOoP >= " << min_OoEminusOoP_trig_ << " fakeable cut\n";
      }
      return false;
    }
  }

  if(set_selection_flags_)
  {
    electron.set_isFakeable();
  }

  return true;
}

RecoElectronCollectionSelectorFakeable::RecoElectronCollectionSelectorFakeable(int era,
                                                                               int index,
                                                                               bool debug,
                                                                               bool set_selection_flags)
  : ParticleCollectionSelector<RecoElectron, RecoElectronSelectorFakeable>(era, index, debug)
{
  selector_.set_selection_flags(set_selection_flags);
}

void
RecoElectronCollectionSelectorFakeable::enable_offline_e_trigger_cuts()
{
  selector_.enable_offline_e_trigger_cuts();
}

void
RecoElectronCollectionSelectorFakeable::disable_offline_e_trigger_cuts()
{
  selector_.disable_offline_e_trigger_cuts();
}
