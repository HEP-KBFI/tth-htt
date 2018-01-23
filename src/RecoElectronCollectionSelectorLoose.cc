#include "tthAnalysis/HiggsToTauTau/interface/RecoElectronCollectionSelectorLoose.h" // RecoElectronSelectorLoose
#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // kEra_2015, kEra_2016
#include <cmath> // std::fabs()

RecoElectronSelectorLoose::RecoElectronSelectorLoose(int era, int index, bool debug, bool set_selection_flags)
  : set_selection_flags_(set_selection_flags)
  , debug_(debug)
  , era_(era)
  , tightElectronSelector_(0)
  , min_pt_(7.)
  , max_absEta_(2.5)
  , max_dxy_(0.05)
  , max_dz_(0.1)
  , max_relIso_(0.4)
  , max_sip3d_(8.)
  , min_mvaRawPOG_vlow_({ -0.30,-0.46,-0.63 })
  , min_mvaRawPOG_low_({ -0.86,-0.85,-0.81 })
  , min_mvaRawPOG_high_({ -0.96,-0.96,-0.95 })
  , binning_absEta_({ 0.8, 1.479 })
  , apply_tightCharge_(false)
  , apply_conversionVeto_(false)
  , max_nLostHits_(1)
{
  assert(min_mvaRawPOG_vlow_.size() == 3);
  assert(min_mvaRawPOG_low_.size() == 3);
  assert(min_mvaRawPOG_high_.size() == 3);
  assert(binning_absEta_.size() == 2);
  tightElectronSelector_ = new RecoElectronSelectorTight(era_, index, debug, false);
}

RecoElectronSelectorLoose::~RecoElectronSelectorLoose()
{
  delete tightElectronSelector_;
}

bool RecoElectronSelectorLoose::operator()(const RecoElectron& electron) const
{
  bool isTight = (*tightElectronSelector_)(electron);
  if(debug_)
  {
    const int idxBin = [this, &electron]() -> int
    {
        if      ( electron.absEta() <= binning_absEta_[0] ) return 0;
        else if ( electron.absEta() <= binning_absEta_[1] ) return 1;
        else                                                return 2;
    }();

    double mvaRawPOGCut = -1;
    double mvaRawPOG = -1;
    if (electron.pt() <= 10) {
      mvaRawPOG = electron.mvaRawPOG_HZZ();
      mvaRawPOGCut = min_mvaRawPOG_vlow_[idxBin];
    } else {
      double a = min_mvaRawPOG_low_[idxBin];
      double b = min_mvaRawPOG_high_[idxBin];
      double c = (a-b)/10;
      mvaRawPOGCut = std::min(a, std::max(b,a-c*(electron.pt()-15)));   // warning: the _high WP must be looser than the _low one
      mvaRawPOG = electron.mvaRawPOG_GP();
    }

    std::cout << "pt           = " << electron.pt()                   << " (>= " << min_pt_
                                   << ") => " << (electron.pt()             >= min_pt_                ? "PASS" : "FAIL") << '\n'
              << "abs(eta)     = " << electron.absEta()               << " (<= " << max_absEta_ << "; idx = " << idxBin
                                   << ") => " << (electron.absEta()         <= max_absEta_            ? "PASS" : "FAIL") << '\n'
              << "abs(dxy)     = " << std::fabs(electron.dxy())       << " (<= " << max_dxy_
                                   << ") => " << (std::fabs(electron.dxy()) <= max_dxy_               ? "PASS" : "FAIL") << '\n'
              << "abs(dz)      = " << std::fabs(electron.dz())        << " (<= " << max_dz_
                                   << ") => " << (std::fabs(electron.dz())  <= max_dz_                ? "PASS" : "FAIL") << '\n'
              << "relIso       = " << electron.relIso()               << " (<= " << max_relIso_
                                   << ") => " << (electron.relIso()         <= max_relIso_            ? "PASS" : "FAIL") << '\n'
              << "sip3d        = " << electron.sip3d()                << " (<= " << max_sip3d_
                                   << ") => " << (electron.sip3d()          <= max_sip3d_             ? "PASS" : "FAIL") << '\n'
              << "nLostHits    = " << electron.nLostHits()            << " (<= " << max_nLostHits_
                                   << ") => " << (electron.nLostHits()      <= max_nLostHits_         ? "PASS" : "FAIL") << '\n'
              << "mvaRawPOG    = " << mvaRawPOG                       << " (>= " << mvaRawPOGCut
                                   << ") => " << (mvaRawPOG                 >= mvaRawPOGCut           ? "PASS" : "FAIL") << '\n';
    if(apply_tightCharge_)
      std::cout << "tight charge = " << electron.tightCharge() << " (>= 2) => "
                                     << (electron.tightCharge()      >= 2         ? "PASS" : "FAIL") << '\n';
    if(apply_conversionVeto_)
      std::cout << "convVeto     = " << electron.passesConversionVeto() << " (> 0) => "
                                     << (electron.passesConversionVeto()      > 0 ? "PASS" : "FAIL") << '\n';
    std::cout << std::string(80, '-') << '\n';
  }
  if ( electron.pt() >= min_pt_ &&
       electron.absEta() <= max_absEta_ &&
       std::fabs(electron.dxy()) <= max_dxy_ &&
       std::fabs(electron.dz()) <= max_dz_ &&
       electron.relIso() <= max_relIso_ &&
       electron.sip3d() <= max_sip3d_ &&
       (electron.tightCharge() >= 2 || !apply_tightCharge_) &&
       (electron.passesConversionVeto() > 0 || !apply_conversionVeto_) &&
       electron.nLostHits() <= max_nLostHits_ ) {
    int idxBin = -1;
    if      ( electron.absEta() <= binning_absEta_[0] ) idxBin = 0;
    else if ( electron.absEta() <= binning_absEta_[1] ) idxBin = 1;
    else                                                idxBin = 2;
    assert(idxBin >= 0 && idxBin <= 2);

    if (electron.pt() <= 10) {
      if ( electron.mvaRawPOG_HZZ() >= min_mvaRawPOG_vlow_[idxBin] ){
        if ( set_selection_flags_ ) electron.set_isLoose();
        if ( isTight ) electron.set_isTight();
        return true;
      }
    } else {
      double a = min_mvaRawPOG_low_[idxBin];
      double b = min_mvaRawPOG_high_[idxBin];
      double c = (a-b)/10;
      double cut = std::min(a, std::max(b,a-c*(electron.pt()-15)));   // warning: the _high WP must be looser than the _low one
      if ( electron.mvaRawPOG_GP() >= cut ) {
        if ( set_selection_flags_ ) electron.set_isLoose();
        if ( isTight ) electron.set_isTight();
        return true;
      }
    }
  }
  return false;
}
