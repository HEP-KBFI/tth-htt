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
  , min_pt_(-1.e+3)
  , max_absEta_(2.5) // F
  , max_dxy_(0.05) // F
  , max_dz_(0.1) // F
  , max_relIso_(0.4) // F
  , max_sip3d_(8.) // F
  , min_pt_trig_(-1.e+3)
  , min_OoEminusOoP_trig_(-1.e+3)
  , apply_conversionVeto_(true) // T
  , max_nLostHits_(0) // F
{
  switch(era_)
  {
    case kEra_2016:
    {
      min_pt_ = 10.;
      binning_absEta_ = { 0.8, 1.479 };
      min_pt_trig_ = 30.;
      max_sigmaEtaEta_trig_ = { 0.011, 0.011, 0.030 };
      max_HoE_trig_ = { 0.10, 0.10, 0.07 };
      max_deltaEta_trig_ = { 0.01, 0.01, 0.008 };
      max_deltaPhi_trig_ = { 0.04, 0.04, 0.07 };
      min_OoEminusOoP_trig_ = -0.05;
      max_OoEminusOoP_trig_ = { 0.010, 0.010, 0.005 };
      min_mvaTTH_ = 0.75;
      max_jetBtagCSV_ = BtagWP_CSV_2016.at(BtagWP::kMedium);
      break;
    }
    case kEra_2017:
    {
      min_pt_ = 7.; // F
      binning_absEta_ = { 1.479 }; // F
      min_pt_trig_ = -1.; // Lines:237-240 in AN_2017_029_V5
      max_sigmaEtaEta_trig_ = { 0.011, 0.030 }; // F
      max_HoE_trig_ = { 0.10, 0.10 }; // F
      max_deltaEta_trig_ = { +1.e+3, +1.e+3 }; // F
      max_deltaPhi_trig_ = { +1.e+3, +1.e+3 }; // F
      min_OoEminusOoP_trig_ = -0.04; // F
      max_OoEminusOoP_trig_ = { +1.e+3, +1.e+3 }; // F
      min_mvaTTH_ = 0.90; // Table 7 in AN2017_029_v5
      max_jetBtagCSV_ = BtagWP_deepCSV_2017.at(BtagWP::kMedium); // F
      break;
    }
    case kEra_2018:
    {
      throw cmsException(this) << "Implement me!";
    }
    default: throw cmsException(this) << "Invalid era: " << era_;
  }
  assert(min_pt_ > 0.);
  assert(binning_absEta_.size() > 0);
  assert(max_sigmaEtaEta_trig_.size() == binning_absEta_.size() + 1);
  assert(max_HoE_trig_.size() == binning_absEta_.size() + 1);
  assert(max_deltaEta_trig_.size() == binning_absEta_.size() + 1);
  assert(max_deltaPhi_trig_.size() == binning_absEta_.size() + 1);
  assert(max_OoEminusOoP_trig_.size() == binning_absEta_.size() + 1);
  // F -- inherited from the fakeable selection
  //      https://gitlab.cern.ch/ttH_leptons/doc/blob/dbb7082bb3668bb3e839293602bc16f47f11c515/2017/objects.md
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

void RecoElectronSelectorTight::set_min_mvaTTH(double min_mvaTTH)
{
  std::cout << "setting cut on prompt-lepton MVA for tight electrons: " << min_mvaTTH << std::endl; 
  min_mvaTTH_ = min_mvaTTH;
}
 
double RecoElectronSelectorTight::get_min_mvaTTH() const
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

  if(electron.pt() < min_pt_)
  {
    if(debug_)
    {
      std::cout << "FAILS pT >= " << min_pt_ << " tight cut\n";
    }
    return false;
  }
  if(electron.absEta() > max_absEta_)
  {
    if(debug_)
    {
      std::cout << "FAILS abs(eta) <= " << max_absEta_ << " tight cut\n";
    }
    return false;
  }
  if(std::fabs(electron.dxy()) > max_dxy_)
  {
    if(debug_)
    {
      std::cout << "FAILS abs(dxy) <= " << max_dxy_ << " tight cut\n";
    }
    return false;
  }
  if(std::fabs(electron.dz()) > max_dz_)
  {
    if(debug_)
    {
      std::cout << "FAILS max(dz) <= " << max_dz_ << " tight cut\n";
    }
    return false;
  }
  if(electron.relIso() > max_relIso_)
  {
    if(debug_)
    {
      std::cout << "FAILS relIso <= " << max_relIso_ << " tight cut\n";
    }
    return false;
  }
  if(electron.sip3d() > max_sip3d_)
  {
    if(debug_)
    {
      std::cout << "FAILS sip3d <= " << max_sip3d_ << " tight cut\n";
    }
    return false;
  }
  if(electron.jetBtagCSV() > max_jetBtagCSV_)
  {
    if(debug_)
    {
      std::cout << "FAILS jetBtagCSV <= " << max_jetBtagCSV_ << " tight cut\n";
    }
    return false;
  }
  if(electron.nLostHits() > max_nLostHits_)
  {
    if(debug_)
    {
      std::cout << "FAILS nLostHits <= " << max_nLostHits_ << " tight cut\n";
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
      std::cout << "FAILS mvaTTH >= " << min_mvaTTH_ << " tight cut\n";
    }
    return false;
  }
  if(! electron.mvaID_POG())
  {
    if(debug_)
    {
      std::cout << "FAILS EGamma POG MVA tight cut\n";
    }
    return false;
  }

  // extra cuts for electrons passing pT threshold of single electron trigger,
  // as explained in section 3.3.4 of AN-2015/321
  if(apply_offline_e_trigger_cuts_ && electron.pt() >= min_pt_trig_)
  {
    std::size_t idxBin = binning_absEta_.size();
    for(std::size_t binning_absEta_idx = 0; binning_absEta_idx < binning_absEta_.size(); ++binning_absEta_idx)
    {
      if(electron.absEta() <= binning_absEta_[binning_absEta_idx])
      {
        idxBin = binning_absEta_idx;
        break;
      }
    }

    if(electron.sigmaEtaEta() > max_sigmaEtaEta_trig_[idxBin])
    {
      if(debug_)
      {
        std::cout << "FAILS sigmaEtaEta <= " << max_sigmaEtaEta_trig_[idxBin] << " tight cut\n";
      }
      return false;
    }
    if(electron.HoE() > max_HoE_trig_[idxBin])
    {
      if(debug_)
      {
        std::cout << "FAILS HoE <= " << max_HoE_trig_[idxBin] << " tight cut\n";
      }
      return false;
    }
    if(std::fabs(electron.deltaEta()) > max_deltaEta_trig_[idxBin]) // why no abs in 2016?
    {
      if(debug_)
      {
        std::cout << "FAILS deltaEta <= " << max_deltaEta_trig_[idxBin] << " tight cut\n";
      }
      return false;
    }
    if(std::fabs(electron.deltaPhi()) > max_deltaPhi_trig_[idxBin]) // why no abs in 2016?
    {
      if(debug_)
      {
        std::cout << "FAILS deltaPhi <= " << max_deltaPhi_trig_[idxBin] << " tight cut\n";
      }
      return false;
    }
    if(electron.OoEminusOoP() < min_OoEminusOoP_trig_)
    {
      if(debug_)
      {
        std::cout << "FAILS OoEminusOoP >= " << min_OoEminusOoP_trig_ << " tight cut\n";
      }
      return false;
    }
    if(electron.OoEminusOoP() > max_OoEminusOoP_trig_[idxBin])
    {
      if(debug_)
      {
        std::cout << "FAILS OoEminusOoP <= " << max_OoEminusOoP_trig_[idxBin] << " tight cut\n";
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
