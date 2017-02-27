#include "tthAnalysis/HiggsToTauTau/interface/RecoElectronCollectionSelectorFakeable.h" // RecoElectronSelectorFakeable

#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // kEra_2015, kEra_2016

#include <FWCore/Utilities/interface/Exception.h> // cms::Exception

#include <cmath> // fabs
#include <assert.h> // assert

RecoElectronSelectorFakeable::RecoElectronSelectorFakeable(int era, int index, bool debug, bool set_selection_flags)
  : era_(era)
  , set_selection_flags_(set_selection_flags)
  , apply_offline_e_trigger_cuts_(true)
  , tightElectronSelector_(0)
  , min_pt_(10.)
  , max_absEta_(2.5)
  , max_dxy_(0.05)
  , max_dz_(0.1)
  , max_relIso_(0.4)
  , max_sip3d_(8.)
  , min_mvaRawPOG_({ -0.7, -0.83, -0.92 })
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
  if      ( era_ == kEra_2015 ) max_jetBtagCSV_ = { 0.6050, 0.8900 };
  else if ( era_ == kEra_2016 ) max_jetBtagCSV_ = { 0.3000, 0.8484 };
  else assert(0);
  assert(min_mvaRawPOG_.size() == 3);
  assert(binning_absEta_.size() == 2);
  assert(max_sigmaEtaEta_trig_.size() == 3);
  assert(max_HoE_trig_.size() == 3);
  assert(max_deltaEta_trig_.size() == 3);
  assert(max_deltaPhi_trig_.size() == 3);
  assert(max_OoEminusOoP_trig_.size() == 3);
  assert(binning_mvaTTH_.size() == 1);
  assert(min_jetPtRatio_.size() == 2);
  assert(max_jetBtagCSV_.size() == 2);
  tightElectronSelector_ = new RecoElectronSelectorTight(era_, index, debug, false);
}

RecoElectronSelectorFakeable::~RecoElectronSelectorFakeable()
{
  delete tightElectronSelector_;
}

bool RecoElectronSelectorFakeable::operator()(const RecoElectron& electron) const
{
  //std::cout << "<RecoElectronSelectorFakeable::operator()>:" << std::endl;
  //std::cout << electron;
  bool isTight = (*tightElectronSelector_)(electron);
  //double pt = ( isTight ) ? electron.pt() : electron.cone_pt();
  // CV: use original lepton pT instead of mixing lepton pT and cone_pT, as discussed on slide 2 of 
  //     https://indico.cern.ch/event/597028/contributions/2413742/attachments/1391684/2120220/16.12.22_ttH_Htautau_-_Review_of_systematics.pdf
  double pt = electron.pt();
  //std::cout << "isTight = " << isTight << ": pT = " << pt << std::endl;  
  if ( pt >= min_pt_ &&
       electron.absEta() <= max_absEta_ &&
       std::fabs(electron.dxy()) <= max_dxy_ &&
       std::fabs(electron.dz()) <= max_dz_ &&
       electron.relIso() <= max_relIso_ &&
       electron.sip3d() <= max_sip3d_ &&
       electron.nLostHits() <= max_nLostHits_ && 
       (electron.passesConversionVeto() || !apply_conversionVeto_) ) {
    int idxBin_absEta = -1;
    if      ( electron.absEta() <= binning_absEta_[0] ) idxBin_absEta = 0;
    else if ( electron.absEta() <= binning_absEta_[1] ) idxBin_absEta = 1;
    else                                                idxBin_absEta = 2;
    assert(idxBin_absEta >= 0 && idxBin_absEta <= 2);
    if ( electron.mvaRawPOG() >= min_mvaRawPOG_[idxBin_absEta] ) {
      int idxBin_mvaTTH = -1;
      if   ( electron.mvaRawTTH() <= binning_mvaTTH_[0] ) idxBin_mvaTTH = 0;
      else                                                idxBin_mvaTTH = 1;
      assert(idxBin_mvaTTH >= 0 && idxBin_mvaTTH <= 1);
      if ( electron.jetPtRatio() >= min_jetPtRatio_[idxBin_mvaTTH] &&
	   electron.jetBtagCSV() <= max_jetBtagCSV_[idxBin_mvaTTH] ) {
	if ( pt <= min_pt_trig_ || !apply_offline_e_trigger_cuts_ ) {
	  if ( set_selection_flags_ ) {
	    electron.set_isFakeable();
	    if ( isTight ) electron.set_isTight();
	  }
	  return true;
	} else if ( electron.sigmaEtaEta() <= max_sigmaEtaEta_trig_[idxBin_absEta] &&
		    electron.HoE() <= max_HoE_trig_[idxBin_absEta] &&
		    electron.deltaEta() <= max_deltaEta_trig_[idxBin_absEta] &&
		    electron.deltaPhi() <= max_deltaPhi_trig_[idxBin_absEta] &&
		    electron.OoEminusOoP() >= min_OoEminusOoP_trig_ &&
		    electron.OoEminusOoP() <= max_OoEminusOoP_trig_[idxBin_absEta] ) {
	  if ( set_selection_flags_ ) {
	    electron.set_isFakeable();
	    if ( isTight ) electron.set_isTight();
	  }
	  return true;
	}
      }
    }
  }
  return false;
}
