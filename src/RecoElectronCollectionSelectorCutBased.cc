#include "tthAnalysis/HiggsToTauTau/interface/RecoElectronCollectionSelectorCutBased.h" // RecoElectronSelectorCutBased

#include <cassert> // assert()

RecoElectronSelectorCutBased::RecoElectronSelectorCutBased(int era,
                                                           int index,
                                                           bool debug)
  : min_pt_(15.)
  , max_relIso_(0.1)
  , max_sip3d_(4.)
  , min_mvaRawPOG_vlow_({ -0.30,-0.46,-0.63 })
  , min_mvaRawPOG_low_({ -0.86,-0.85,-0.81 })
  , min_mvaRawPOG_high_({ -0.96,-0.96,-0.95 })
  , binning_absEta_({ 0.8, 1.479 })
  , apply_tightCharge_(true)
  , apply_conversionVeto_(true)
  , max_nLostHits_(0)
{
  assert(min_mvaRawPOG_vlow_.size() == 3);
  assert(min_mvaRawPOG_low_.size() == 3);
  assert(min_mvaRawPOG_high_.size() == 3);
  assert(binning_absEta_.size() == 2);
}

bool
RecoElectronSelectorCutBased::operator()(const RecoElectron & electron) const
{
  return (
    electron.pt() >= min_pt_                                   &&
    electron.relIso() <= max_relIso_                           &&
    electron.sip3d() <= max_sip3d_                             &&
    electron.nLostHits() <= max_nLostHits_                     &&
   (electron.tightCharge() >= 2 || !apply_tightCharge_)        &&
   (electron.passesConversionVeto() || !apply_conversionVeto_) &&
    electron.mvaRawPOG_WP(EGammaPOG::kWPL)
  );
}
