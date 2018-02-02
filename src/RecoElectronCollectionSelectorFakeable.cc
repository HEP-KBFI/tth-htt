#include "tthAnalysis/HiggsToTauTau/interface/RecoElectronCollectionSelectorFakeable.h" // RecoElectronSelectorFakeable

#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // kEra_2017
#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h" // cmsException(), assert()

RecoElectronSelectorFakeable::RecoElectronSelectorFakeable(int era,
                                                           int index,
                                                           bool debug,
                                                           bool set_selection_flags)
  : era_(era)
  , set_selection_flags_(set_selection_flags)
  , apply_offline_e_trigger_cuts_(true)
  , tightElectronSelector_(era_, index, debug, false)
  , min_pt_(10.)
  , max_absEta_(2.5)
  , max_dxy_(0.05)
  , max_dz_(0.1)
  , max_relIso_(0.4)
  , max_sip3d_(8.)
  , min_mvaRawPOG_vlow_({ -0.30,-0.46,-0.63 })
  , min_mvaRawPOG_low_({ -0.86,-0.85,-0.81 })
  , min_mvaRawPOG_high_({ -0.96,-0.96,-0.95 })
  , binning_absEta_({ 0.8, 1.479 })
  , min_pt_trig_(30.)
  , max_sigmaEtaEta_trig_({ 0.011, 0.011, 0.030 })
  , max_HoE_trig_({ 0.10, 0.10, 0.07 }) 
  , max_deltaEta_trig_({ 0.01, 0.01, 0.008 })
  , max_deltaPhi_trig_({ 0.04, 0.04, 0.07 })
  , min_OoEminusOoP_trig_(-0.05)
  , max_OoEminusOoP_trig_({ 0.010, 0.010, 0.005 })
  , binning_mvaTTH_({ 0.75 })
  , min_jetPtRatio_({ 0.30, -1.e+3 })
  , apply_conversionVeto_(true)
  , max_nLostHits_(0)
{
  switch(era_)
  {
    case kEra_2017:
    {
      max_jetBtagCSV_ = { 0.5426, 0.8484 };
      break;
    }
    default: throw cms::Exception("RecoElectronSelectorFakeable") << "Invalid era: " << era_;
  }
  assert(min_mvaRawPOG_vlow_.size() == 3);
  assert(min_mvaRawPOG_low_.size() == 3);
  assert(min_mvaRawPOG_high_.size() == 3);
  assert(binning_absEta_.size() == 2);
  assert(max_sigmaEtaEta_trig_.size() == 3);
  assert(max_HoE_trig_.size() == 3);
  assert(max_deltaEta_trig_.size() == 3);
  assert(max_deltaPhi_trig_.size() == 3);
  assert(max_OoEminusOoP_trig_.size() == 3);
  assert(binning_mvaTTH_.size() == 1);
  assert(min_jetPtRatio_.size() == 2);
  assert(max_jetBtagCSV_.size() == 2);
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

bool
RecoElectronSelectorFakeable::operator()(const RecoElectron & electron) const
{
  // CV: use original lepton pT instead of mixing lepton pT and cone_pT, as discussed on slide 2 of 
  //     https://indico.cern.ch/event/597028/contributions/2413742/attachments/1391684/2120220/16.12.22_ttH_Htautau_-_Review_of_systematics.pdf
  const double pt = electron.pt();

  if(pt >= min_pt_                                              &&
     electron.absEta() <= max_absEta_                           &&
     std::fabs(electron.dxy()) <= max_dxy_                      &&
     std::fabs(electron.dz()) <= max_dz_                        &&
     electron.relIso() <= max_relIso_                           &&
     electron.sip3d() <= max_sip3d_                             &&
     electron.nLostHits() <= max_nLostHits_                     &&
     (electron.passesConversionVeto() || ! apply_conversionVeto_))
  {
    const int idxBin_absEta = electron.absEta() <= binning_absEta_[0] ? 0 :
                             (electron.absEta() <= binning_absEta_[1] ? 1 : 2)
    ;

    double mvaRawPOGCut = -1;
    double mvaRawPOG = -1;
    if(electron.pt() <= 10)
    {
      mvaRawPOG = electron.mvaRawPOG_HZZ();
      mvaRawPOGCut = min_mvaRawPOG_vlow_[idxBin_absEta];
    }
    else
    {
      const double a = min_mvaRawPOG_low_[idxBin_absEta];
      const double b = min_mvaRawPOG_high_[idxBin_absEta];
      const double c = (a - b) / 10;

      // warning: the _high WP must be looser than the _low one
      mvaRawPOGCut = std::min(a, std::max(b, a - c * (electron.pt() - 15)));
      mvaRawPOG = electron.mvaRawPOG_GP();
    }

    if(mvaRawPOG >= mvaRawPOGCut)
    {
      const int idxBin_mvaTTH = electron.mvaRawTTH() <= binning_mvaTTH_[0] ? 0 : 1;

      if(electron.jetPtRatio() >= min_jetPtRatio_[idxBin_mvaTTH] &&
         electron.jetBtagCSV() <= max_jetBtagCSV_[idxBin_mvaTTH])
      {
        const bool isTight = tightElectronSelector_(electron);
        if(pt <= min_pt_trig_ || ! apply_offline_e_trigger_cuts_)
        {
          if(set_selection_flags_)
          {
            electron.set_isFakeable();
            if(isTight)
            {
              electron.set_isTight();
            }
          }
          return true;
        }
        else if(electron.sigmaEtaEta() <= max_sigmaEtaEta_trig_[idxBin_absEta] &&
                electron.HoE() <= max_HoE_trig_[idxBin_absEta]                 &&
                electron.deltaEta() <= max_deltaEta_trig_[idxBin_absEta]       &&
                electron.deltaPhi() <= max_deltaPhi_trig_[idxBin_absEta]       &&
                electron.OoEminusOoP() >= min_OoEminusOoP_trig_                &&
                electron.OoEminusOoP() <= max_OoEminusOoP_trig_[idxBin_absEta])
        {
          if(set_selection_flags_)
          {
            electron.set_isFakeable();
            if(isTight)
            {
              electron.set_isTight();
            }
          }
          return true;
        }
      }
    } // mvaRawPOG >= mvaRawPOGCut
  }
  return false;
}

RecoElectronCollectionSelectorFakeable::RecoElectronCollectionSelectorFakeable(int era,
                                                                               int index,
                                                                               bool debug,
                                                                               bool set_selection_flags)
  : selIndex_(index)
  , selector_(era, index, debug, set_selection_flags)
{}

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

std::vector<const RecoElectron *>
RecoElectronCollectionSelectorFakeable::operator()(const std::vector<const RecoElectron * > & electrons) const
{
  std::vector<const RecoElectron *> selElectrons;
  int idx = 0;
  for(const RecoElectron * electron: electrons)
  {
    if(selector_(*electron))
    {
      if(idx == selIndex_ || selIndex_ == -1)
      {
        selElectrons.push_back(electron);
      }
      ++idx;
    }
  }
  return selElectrons;
}
