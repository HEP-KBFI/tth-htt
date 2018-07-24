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
  , min_cone_pt_(-1.e+3)
  , min_lepton_pt_(-1.e+3)
  , max_absEta_(2.5) // L
  , max_dxy_(0.05) // L
  , max_dz_(0.1) // L
  , max_relIso_(0.4) // L
  , max_sip3d_(8.) // L
  , min_OoEminusOoP_trig_(-1.e+3)
  , apply_conversionVeto_(true) // F (after Giovanni sync)
  , max_nLostHits_(0) // F
{
  switch(era_)
  {
    case kEra_2016:
    {
// CV: use original lepton pT instead of mixing lepton pT and cone_pT, as discussed on slide 2 of
//     https://indico.cern.ch/event/597028/contributions/2413742/attachments/1391684/2120220/16.12.22_ttH_Htautau_-_Review_of_systematics.pdf
      min_cone_pt_ = -1.e+3;
      min_lepton_pt_ = 10.;
      binning_absEta_ = { 0.8, 1.479 };
      min_pt_trig_ = 30.;
      max_sigmaEtaEta_trig_ = { 0.011, 0.011, 0.030 };
      max_HoE_trig_ = { 0.10, 0.10, 0.07 };
      max_deltaEta_trig_ = { 0.01, 0.01, 0.008 };
      max_deltaPhi_trig_ = { 0.04, 0.04, 0.07 };
      min_OoEminusOoP_trig_ = -0.05;
      max_OoEminusOoP_trig_ = { 0.010, 0.010, 0.005 };
      binning_mvaTTH_ = { 0.75 };
      min_jetPtRatio_ = { 0.30, -1.e+3 };
      min_mvaIDraw_ = { -1.e+3, -1.e+3 };
      max_jetBtagCSV_ = { BtagWP_CSV_2016.at(BtagWP::kLoose), BtagWP_CSV_2016.at(BtagWP::kMedium) };
      break;
    }
    case kEra_2017:
    {
      min_cone_pt_ = 10.; // F
      min_lepton_pt_ = 7.; // L
      binning_absEta_ = { 1.479 }; // F; [*]
      min_pt_trig_ = -1.; // LFR sync; used to be 30 GeV Lines:237-240 in AN_2017_029_v5
      max_sigmaEtaEta_trig_ = { 0.011, 0.030 }; // F; [*]
      max_HoE_trig_ = { 0.10, 0.10 }; // F; [*]
      max_deltaEta_trig_ = { +1.e+3, +1.e+3 }; // F; [*]
      max_deltaPhi_trig_ = { +1.e+3, +1.e+3 }; // F; [*]
      min_OoEminusOoP_trig_ = -0.04; // F; [*]
      max_OoEminusOoP_trig_ = { +1.e+3, +1.e+3 }; // F; [*]
      binning_mvaTTH_ = { 0.90 }; // F; Table 7 in AN2017_029_v5
      min_jetPtRatio_ = { 0.60, -1.e+3 }; // F; [*]
      min_mvaIDraw_ = { 0.50, -1.e+3 }; // F; [*]
      max_jetBtagCSV_ = { 0.07, BtagWP_deepCSV_2017.at(BtagWP::kMedium) }; // F; [*]
      break;
    }
    case kEra_2018:
    {
      throw cmsException(this) << "Implement me!";
    }
    default: throw cmsException(this) << "Invalid era: " << era_;
  }
  assert(min_lepton_pt_ > 0.);
  assert(binning_absEta_.size() > 0);
  assert(max_sigmaEtaEta_trig_.size() == binning_absEta_.size() + 1);
  assert(max_HoE_trig_.size() == binning_absEta_.size() + 1);
  assert(max_deltaEta_trig_.size() == binning_absEta_.size() + 1);
  assert(max_deltaPhi_trig_.size() == binning_absEta_.size() + 1);
  assert(max_OoEminusOoP_trig_.size() == binning_absEta_.size() + 1);
  assert(binning_mvaTTH_.size() == 1);
  assert(min_jetPtRatio_.size() == binning_mvaTTH_.size() + 1);
  assert(max_jetBtagCSV_.size() == binning_mvaTTH_.size() + 1);
  assert(min_mvaIDraw_.size() == binning_mvaTTH_.size() + 1);
  // L -- inherited from the preselection (loose cut)
  // F -- additional fakeable cut not applied in the preselection
  // [*] https://gitlab.cern.ch/ttH_leptons/doc/blob/dbb7082bb3668bb3e839293602bc16f47f11c515/2017/objects.md
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

  if(! electron.mvaID_POG())
  {
    if(debug_)
    {
      std::cout << "FAILS EGamma POG MVA fakeable cut\n";
    }
    return false;
  }

  const int idxBin_mvaTTH = electron.mvaRawTTH() <= binning_mvaTTH_[0] ? 0 : 1;

  if(electron.jetPtRatio() < min_jetPtRatio_[idxBin_mvaTTH])
  {
    if(debug_)
    {
      std::cout << "FAILS jetPtRatio >= " << min_jetPtRatio_[idxBin_mvaTTH] << " fakeable cut\n";
    }
    return false;
  }

  if(electron.jetBtagCSV() > max_jetBtagCSV_[idxBin_mvaTTH])
  {
    if(debug_)
    {
      std::cout << "FAILS jetBtagCSV <= " << max_jetBtagCSV_[idxBin_mvaTTH] << " fakeable cut\n";
    }
    return false;
  }

  if(electron.mvaRaw_POG() < min_mvaIDraw_[idxBin_mvaTTH])
  {
    if(debug_)
    {
      std::cout << "FAILS EGamma POG MVA raw >= " << min_mvaIDraw_[idxBin_mvaTTH] << " fakeable cut\n";
    }
    return false;
  }

  double pt = -1.e+3;
  switch(era_)
  {
    case kEra_2016: pt = electron.pt();      break;
    case kEra_2017: pt = electron.cone_pt(); break;
    case kEra_2018: throw cmsException(this, __func__, __LINE__) << "Implement me!";
    default: throw cmsException(this, __func__, __LINE__) << "Invalid era = " << era_;
  }
  assert(pt > 0.);

  if(pt > min_pt_trig_ && apply_offline_e_trigger_cuts_)
  {
    std::size_t idxBin_absEta = binning_absEta_.size();
    for(std::size_t binning_absEta_idx = 0; binning_absEta_idx < binning_absEta_.size(); ++binning_absEta_idx)
    {
      if(electron.absEta() <= binning_absEta_[binning_absEta_idx])
      {
        idxBin_absEta = binning_absEta_idx;
        break;
      }
    }
    if(electron.sigmaEtaEta() > max_sigmaEtaEta_trig_[idxBin_absEta])
    {
      if(debug_)
      {
        std::cout << "FAILS sigmaEtaEta <= " << max_sigmaEtaEta_trig_[idxBin_absEta] << " fakeable cut\n";
      }
      return false;
    }

    if(electron.HoE() > max_HoE_trig_[idxBin_absEta])
    {
      if(debug_)
      {
        std::cout << "FAILS HoE <= " << max_HoE_trig_[idxBin_absEta] << " fakeable cut\n";
      }
      return false;
    }

    if(std::fabs(electron.deltaEta()) > max_deltaEta_trig_[idxBin_absEta]) // why no abs in 2016?
    {
      if(debug_)
      {
        std::cout << "FAILS abs(deltaEta) <= " << max_deltaEta_trig_[idxBin_absEta] << " fakeable cut\n";
      }
      return false;
    }

    if(std::fabs(electron.deltaPhi()) > max_deltaPhi_trig_[idxBin_absEta]) // why no abs in 2016?
    {
      if(debug_)
      {
        std::cout << "FAILS abs(deltaPhi) <= " << max_deltaPhi_trig_[idxBin_absEta] << " fakeable cut\n";
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

    if(electron.OoEminusOoP() > max_OoEminusOoP_trig_[idxBin_absEta])
    {
      if(debug_)
      {
        std::cout << "FAILS OoEminusOoP <= " << max_OoEminusOoP_trig_[idxBin_absEta] << " fakeable cut\n";
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
