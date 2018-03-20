#include "tthAnalysis/HiggsToTauTau/interface/RecoElectronCollectionSelectorLoose.h" // RecoElectronSelectorLoose

#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // kEra_2017
#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h" // cmsException(), assert()

RecoElectronSelectorLoose::RecoElectronSelectorLoose(int era,
                                                     int index,
                                                     bool debug,
                                                     bool set_selection_flags)
  : set_selection_flags_(set_selection_flags)
  , debug_(debug)
  , era_(era)
  , tightElectronSelector_(era_, index, debug, false)
  , min_pt_(7.)
  , max_absEta_(2.5)
  , max_dxy_(0.05)
  , max_dz_(0.1)
  , max_relIso_(0.4)
  , max_sip3d_(8.)
  , min_mvaRawPOG_({ 0.0, 0.0, 0.7 }) // Table 7 in AN2017_029_v5
  , binning_absEta_({ 0.8, 1.479 })
  , apply_tightCharge_(false)
  , apply_conversionVeto_(false)
  , max_nLostHits_(1)
{
  assert(min_mvaRawPOG_.size() == 3);
  assert(binning_absEta_.size() == 2);
}

bool
RecoElectronSelectorLoose::operator()(const RecoElectron & electron) const
{
  if(debug_)
  {
    std::cout << "<RecoElectronSelectorTight::operator()>:\n" << electron;
  }

  if(electron.pt() < min_pt_)
  {
    if(debug_)
    {
      std::cout << "FAILS pT >= " << min_pt_ << " loose cut\n";
    }
    return false;
  }
  if(electron.absEta() > max_absEta_)
  {
    if(debug_)
    {
      std::cout << "FAILS abs(eta) <= " << max_absEta_ << " loose cut\n";
    }
    return false;
  }
  if(std::fabs(electron.dxy()) > max_dxy_)
  {
    if(debug_)
    {
      std::cout << "FAILS abs(dxy) <= " << max_dxy_ << " loose cut\n";
    }
    return false;
  }
  if(std::fabs(electron.dz()) > max_dz_)
  {
    if(debug_)
    {
      std::cout << "FAILS max(dz) <= " << max_dz_ << " loose cut\n";
    }
    return false;
  }
  if(electron.relIso() > max_relIso_)
  {
    if(debug_)
    {
      std::cout << "FAILS relIso <= " << max_relIso_ << " loose cut\n";
    }
    return false;
  }
  if(electron.sip3d() > max_sip3d_)
  {
    if(debug_)
    {
      std::cout << "FAILS sip3d <= " << max_sip3d_ << " loose cut\n";
    }
    return false;
  }
  if(electron.nLostHits() > max_nLostHits_)
  {
    if(debug_)
    {
      std::cout << "FAILS nLostHits <= " << max_nLostHits_ << " loose cut\n";
    }
    return false;
  }
  if(apply_conversionVeto_ && ! electron.passesConversionVeto())
  {
    if(debug_)
    {
      std::cout << "FAILS conversion veto\n";
    }
    return false;
  }
  if(apply_tightCharge_ && electron.tightCharge() < 2)
  {
    if(debug_)
    {
      std::cout << "FAILS tight charge\n";
    }
    return false;
  }

  const int idxBin = electron.absEta() <= binning_absEta_[0] ? 0 :
                    (electron.absEta() <= binning_absEta_[1] ? 1 : 2)
  ;

  if(electron.mvaRawPOG_HZZ() < min_mvaRawPOG_[idxBin])
  {
    if(debug_)
    {
      std::cout << "FAILS mvaPOG HZZ >= " << min_mvaRawPOG_[idxBin] << " loose cut\n";
    }
    return false;
  }

  if(set_selection_flags_)
  {
    electron.set_isLoose();
  }
  if(tightElectronSelector_(electron))
  {
    electron.set_isTight();
  }

  return true;
}
