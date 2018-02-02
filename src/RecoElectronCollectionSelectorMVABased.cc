#include "tthAnalysis/HiggsToTauTau/interface/RecoElectronCollectionSelectorMVABased.h" // RecoElectronSelectorMVABased

#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // kEra_2017
#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h" // cmsException(), assert()

RecoElectronSelectorMVABased::RecoElectronSelectorMVABased(int era,
                                                           int index,
                                                           bool debug)
  : era_(era)
  , min_pt_(15.)
  , binning_absEta_({ 0.8, 1.479 })
  , min_pt_trig_(30.)
  , max_sigmaEtaEta_trig_({ 0.011, 0.011, 0.030 })
  , max_HoE_trig_({ 0.10, 0.10, 0.07 })
  , max_deltaEta_trig_({ 0.01, 0.01, 0.008 })
  , max_deltaPhi_trig_({ 0.04, 0.04, 0.07 })
  , min_OoEminusOoP_trig_(-0.05)
  , max_OoEminusOoP_trig_({ 0.010, 0.010, 0.005 })
  , min_mvaTTH_(0.75)
{
  switch(era_)
  {
    case kEra_2017:
    {
      max_nLostHits_ = 1;
      max_jetBtagCSV_ = 0.80;
      apply_tightCharge_ = false;
      apply_conversionVeto_ = false;
      break;
    }
    default:
      throw cms::Exception("RecoElectronSelectorMVABased") << "Invalid era = " << era_;
  }

  assert(binning_absEta_.size() == 2);
  assert(max_sigmaEtaEta_trig_.size() == 3);
  assert(max_HoE_trig_.size() == 3);
  assert(max_deltaEta_trig_.size() == 3);
  assert(max_deltaPhi_trig_.size() == 3);
  assert(max_OoEminusOoP_trig_.size() == 3);
}

bool
RecoElectronSelectorMVABased::operator()(const RecoElectron & electron) const
{
  if(electron.pt() >= min_pt_                                  &&
     electron.nLostHits() <= max_nLostHits_                    &&
     electron.jetBtagCSV() <= max_jetBtagCSV_                  &&
     electron.mvaRawTTH() >= min_mvaTTH_                       &&
     (electron.tightCharge() >= 2 || !apply_tightCharge_)      &&
     (electron.passesConversionVeto() || !apply_conversionVeto_))
  {
    const int idxBin_absEta = electron.absEta() <= binning_absEta_[0] ? 0 :
                             (electron.absEta() <= binning_absEta_[1] ? 1 : 2)
    ;

    if(electron.pt() <= min_pt_trig_)
    {
      return true;
    }
    if(electron.sigmaEtaEta() <= max_sigmaEtaEta_trig_[idxBin_absEta] &&
       electron.HoE() <= max_HoE_trig_[idxBin_absEta]                 &&
       electron.deltaEta() <= max_deltaEta_trig_[idxBin_absEta]       &&
       electron.deltaPhi() <= max_deltaPhi_trig_[idxBin_absEta]       &&
       electron.OoEminusOoP() >= min_OoEminusOoP_trig_                &&
       electron.OoEminusOoP() <= max_OoEminusOoP_trig_[idxBin_absEta])
    {
      return true;
    }
  }
  return false;
}
