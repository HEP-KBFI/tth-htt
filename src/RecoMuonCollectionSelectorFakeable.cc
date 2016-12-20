#include "tthAnalysis/HiggsToTauTau/interface/RecoMuonCollectionSelectorFakeable.h" // RecoMuonSelectorFakeable

#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // kEra_2015, kEra_2016

#include <cmath> // fabs

RecoMuonSelectorFakeable::RecoMuonSelectorFakeable(int era, bool set_selection_flags, int index, bool debug)
  : era_(era)
  , set_selection_flags_(set_selection_flags)
  , tightMuonSelector_(0)
  , min_pt_(10.)
  , max_absEta_(2.4)
  , max_dxy_(0.05)
  , max_dz_(0.1)
  , max_relIso_(0.4)
  , max_sip3d_(8.)
  , apply_looseIdPOG_(true)
  , binning_mvaTTH_({ 0.75 })
  , min_jetPtRatio_({ 0.30, -1.e+3 })   
  , apply_mediumIdPOG_(false)
{
  if      ( era_ == kEra_2015 ) max_jetBtagCSV_ = { 0.605, 0.89 };
  else if ( era_ == kEra_2016 ) max_jetBtagCSV_ = { 0.460, 0.80 };
  else assert(0);
  tightMuonSelector_ = new RecoMuonSelectorTight(era_, false, index, debug);
}

RecoMuonSelectorFakeable::~RecoMuonSelectorFakeable()
{
  delete tightMuonSelector_;
}

bool RecoMuonSelectorFakeable::operator()(const RecoMuon& muon) const
{
  bool isTight = (*tightMuonSelector_)(muon);
  double pt = ( isTight ) ? muon.pt() : muon.cone_pt();
  if ( pt >= min_pt_ &&
       muon.absEta() <= max_absEta_ &&
       std::fabs(muon.dxy()) <= max_dxy_ &&
       std::fabs(muon.dz()) <= max_dz_ &&
       muon.relIso() <= max_relIso_ &&
       muon.sip3d() <= max_sip3d_ &&
       (muon.passesLooseIdPOG() || !apply_looseIdPOG_) && 
       (muon.passesMediumIdPOG() || !apply_mediumIdPOG_) ) {
    int idxBin = -1;
    if   ( muon.mvaRawTTH() <= binning_mvaTTH_[0] ) idxBin = 0;
    else                                            idxBin = 1;
    assert(idxBin >= 0 && idxBin <= 1);
    if ( muon.jetPtRatio() >= min_jetPtRatio_[idxBin] &&
	 muon.jetBtagCSV() <= max_jetBtagCSV_[idxBin] ) {
      if ( set_selection_flags_ ) muon.set_isFakeable();
      return true;
    }
  }
  return false;
}
