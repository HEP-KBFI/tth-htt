#include "tthAnalysis/HiggsToTauTau/interface/RecoElectronCollectionSelectorTight.h" // RecoElectronSelectorTight

#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // kEra_*
#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h" // cmsException(), assert()

RecoElectronSelectorTight::RecoElectronSelectorTight(int era,
                                                     int index,
                                                     bool debug,
                                                     bool set_selection_flags)
  : era_(era)
  , set_selection_flags_(set_selection_flags)
  , apply_offline_e_trigger_cuts_(true)
  , debug_(debug)
  , min_pt_(7.) // L
  , min_cone_pt_(10) // F
  , max_absEta_(2.5) // F
  , max_dxy_(0.05) // F
  , max_dz_(0.1) // F
  , max_relIso_(0.4) // F
  , max_sip3d_(8.) // F
  , binning_absEta_(1.479) // F
  , min_sigmaEtaEta_trig_(0.011) // F
  , max_sigmaEtaEta_trig_(0.019) // F
  , max_HoE_trig_(0.10) // F
  , min_OoEminusOoP_trig_(-0.04) // F
  , max_jetBtagCSV_(get_BtagWP(era_, Btag::kDeepJet, BtagWP::kMedium)) // F
  , max_nLostHits_(0) // F
  , apply_conversionVeto_(true) // F
  , min_mvaTTH_(0.80) // T
{
  // L -- inherited from the preselection (loose cut)
  // F -- inherited from the fakeable selection
  // T -- additional tight cut not applied in the fakeable selection
}

void
RecoElectronSelectorTight::enable_offline_e_trigger_cuts()
{
  apply_offline_e_trigger_cuts_ = true;
}

void
RecoElectronSelectorTight::disable_offline_e_trigger_cuts()
{
  apply_offline_e_trigger_cuts_ = false;
}

// enable/disable photon conversion veto
void
RecoElectronSelectorTight::enable_conversionVeto()
{
  apply_conversionVeto_ = true;
}

void
RecoElectronSelectorTight::disable_conversionVeto()
{
  apply_conversionVeto_ = false;
}

void
RecoElectronSelectorTight::set_min_pt(double min_pt)
{
  min_pt_ = min_pt;
}

void
RecoElectronSelectorTight::set_max_absEta(double max_absEta)
{
  max_absEta_ = max_absEta;
}

void RecoElectronSelectorTight::set_min_mvaTTH(double min_mvaTTH)
{
  std::cout << "setting cut on prompt-lepton MVA for tight electrons: " << min_mvaTTH << '\n';
  min_mvaTTH_ = min_mvaTTH;
}
 
double
RecoElectronSelectorTight::get_min_pt() const
{
  return min_pt_;
}

double
RecoElectronSelectorTight::get_max_absEta() const
{
  return max_absEta_;
}

double 
RecoElectronSelectorTight::get_min_mvaTTH() const
{
  return min_mvaTTH_;
}

void
RecoElectronSelectorTight::set_selection_flags(bool selection_flag)
{
  set_selection_flags_ = selection_flag;
}

bool
RecoElectronSelectorTight::operator()(const RecoElectron & electron) const
{
  if(debug_)
  {
    std::cout << get_human_line(this, __func__) << ":\n" << electron;
  }

  if(electron.cone_pt() < min_cone_pt_)
  {
    if(debug_)
    {
      std::cout << "FAILS cone pT = " << electron.cone_pt() << " >= " << min_cone_pt_ << " tight cut\n";
    }
    return false;
  }
  if(electron.pt() < min_pt_)
  {
    if(debug_)
    {
      std::cout << "FAILS pT = " << electron.pt() << " >= " << min_pt_ << " tight cut\n";
    }
    return false;
  }
  if(electron.absEta() > max_absEta_)
  {
    if(debug_)
    {
      std::cout << "FAILS abs(eta) = " << electron.absEta() << " <= " << max_absEta_ << " tight cut\n";
    }
    return false;
  }
  if(std::fabs(electron.dxy()) > max_dxy_)
  {
    if(debug_)
    {
      std::cout << "FAILS abs(dxy) = " << std::fabs(electron.dxy()) << " <= " << max_dxy_ << " tight cut\n";
    }
    return false;
  }
  if(std::fabs(electron.dz()) > max_dz_)
  {
    if(debug_)
    {
      std::cout << "FAILS max(dz) = " << std::fabs(electron.dz()) << " <= " << max_dz_ << " tight cut\n";
    }
    return false;
  }
  if(electron.relIso() > max_relIso_)
  {
    if(debug_)
    {
      std::cout << "FAILS relIso = " << electron.relIso() << " <= " << max_relIso_ << " tight cut\n";
    }
    return false;
  }
  if(electron.sip3d() > max_sip3d_)
  {
    if(debug_)
    {
      std::cout << "FAILS sip3d = " << electron.sip3d() << " <= " << max_sip3d_ << " tight cut\n";
    }
    return false;
  }
  if(electron.jetBtagCSV() > max_jetBtagCSV_)
  {
    if(debug_)
    {
      std::cout << "FAILS jetBtagCSV = " << electron.jetBtagCSV() << " <= " << max_jetBtagCSV_ << " tight cut\n";
    }
    return false;
  }
  if(electron.nLostHits() > max_nLostHits_)
  {
    if(debug_)
    {
      std::cout << "FAILS nLostHits = " << electron.nLostHits() << " <= " << max_nLostHits_ << " tight cut\n";
    }
    return false;
  }
  if(apply_conversionVeto_ && ! electron.passesConversionVeto())
  {
    if(debug_)
    {
      std::cout << "FAILS conversion veto tight cut\n";
    }
    return false;
  }
  if(electron.mvaRawTTH() < min_mvaTTH_)
  {
    if(debug_)
    {
      std::cout << "FAILS mvaTTH = " << electron.mvaRawTTH() << " >= " << min_mvaTTH_ << " tight cut\n";
    }
    return false;
  }
  if(! electron.mvaID_POG(EGammaWP::WPL))
  {
    if(debug_)
    {
      std::cout << "FAILS loose EGamma POG MVA tight cut\n";
    }
    return false;
  }

  // extra cuts for electrons passing pT threshold of single electron trigger,
  // as explained in section 3.3.4 of AN-2015/321
  if(apply_offline_e_trigger_cuts_)
  {
    const double max_sigmaEtaEta_trig = min_sigmaEtaEta_trig_ +
                                        max_sigmaEtaEta_trig_ * (electron.absEtaSC() > binning_absEta_);
    if(electron.sigmaEtaEta() > max_sigmaEtaEta_trig)
    {
      if(debug_)
      {
        std::cout << "FAILS sigmaEtaEta = " << electron.sigmaEtaEta() << " <= " << max_sigmaEtaEta_trig << " tight cut\n";
      }
      return false;
    }
    if(electron.HoE() > max_HoE_trig_)
    {
      if(debug_)
      {
        std::cout << "FAILS HoE = " << electron.HoE() << " <= " << max_HoE_trig_ << " tight cut\n";
      }
      return false;
    }
    if(electron.OoEminusOoP() < min_OoEminusOoP_trig_)
    {
      if(debug_)
      {
        std::cout << "FAILS OoEminusOoP = " << electron.OoEminusOoP() << " >= " << min_OoEminusOoP_trig_ << " tight cut\n";
      }
      return false;
    }
  }

  // electron passes all cuts
  if(set_selection_flags_)
  {
    electron.set_isTight();
  }
  return true;
}

RecoElectronCollectionSelectorTight::RecoElectronCollectionSelectorTight(int era,
                                                                         int index,
                                                                         bool debug,
                                                                         bool set_selection_flags)
  : ParticleCollectionSelector<RecoElectron, RecoElectronSelectorTight>(era, index, debug)
{
  selector_.set_selection_flags(set_selection_flags);
}

void
RecoElectronCollectionSelectorTight::enable_offline_e_trigger_cuts()
{
  selector_.enable_offline_e_trigger_cuts();
}

void
RecoElectronCollectionSelectorTight::disable_offline_e_trigger_cuts()
{
  selector_.disable_offline_e_trigger_cuts();
}

// enable/disable photon conversion veto
void
RecoElectronCollectionSelectorTight::enable_conversionVeto()
{
  selector_.enable_conversionVeto();
}

void
RecoElectronCollectionSelectorTight::disable_conversionVeto()
{
  selector_.disable_conversionVeto();
}
