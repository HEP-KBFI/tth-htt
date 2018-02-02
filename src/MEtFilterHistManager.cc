#include "tthAnalysis/HiggsToTauTau/interface/MEtFilterHistManager.h"

#include "tthAnalysis/HiggsToTauTau/interface/histogramAuxFunctions.h"

#include <TMath.h>

#include "tthAnalysis/HiggsToTauTau/interface/MEtFilterReader.h"
#include "tthAnalysis/HiggsToTauTau/interface/MEtFilter.h"



enum { kFlag_HBHENoiseIsoFilter = 1, kFlag_EcalDeadCellTriggerPrimitiveFilter = 2, kFlag_ecalLaserCorrFilter = 3, kFlag_hcalLaserEventFilter = 4,
       kFlag_muonBadTrackFilter = 5, kFlag_trkPOGFilters = 6, kFlag_trackingFailureFilter = 7, kFlag_CSCTightHaloFilter = 8, kFlag_HBHENoiseFilter = 9,
       kFlag_chargedHadronTrackResolutionFilter = 10, kFlag_GlobalTightHalo2016Filter = 11, kFlag_METFilters = 12, kFlag_CSCTightHalo2015Filter = 13,
       kFlag_eeBadScFilter = 14, kFlag_trkPOG_manystripclus53X = 15, kFlag_trkPOG_toomanystripclus53X = 16, kFlag_trkPOG_logErrorTooManyClusters = 17,
       kFlag_goodVertices = 18 };


MEtFilterHistManager::MEtFilterHistManager(const edm::ParameterSet& cfg)
  : HistManagerBase(cfg)
{}




void fill(TH1* histogram, int filter, bool flag, double evtWeight, double evtWeightErr)
{
  if ( !flag ) { // CV: fill histogram if filter has failed
    fill(histogram, filter, evtWeight, evtWeightErr);
  }
}



void MEtFilterHistManager::bookHistograms(TFileDirectory& dir)
{
  histogram_MEtFilterCounter_ = book1D(dir, "MEtFilterCounter", "MEtFilterCounter", 18, 1., 18.);
  histogram_MEtFilterCounter_->GetXaxis()->SetBinLabel(kFlag_HBHENoiseIsoFilter, "Flag_HBHENoiseIsoFilter");
  histogram_MEtFilterCounter_->GetXaxis()->SetBinLabel(kFlag_EcalDeadCellTriggerPrimitiveFilter, "Flag_EcalDeadCellTriggerPrimitiveFilter");
  histogram_MEtFilterCounter_->GetXaxis()->SetBinLabel(kFlag_ecalLaserCorrFilter, "Flag_ecalLaserCorrFilter");
  histogram_MEtFilterCounter_->GetXaxis()->SetBinLabel(kFlag_hcalLaserEventFilter, "Flag_hcalLaserEventFilter");
  histogram_MEtFilterCounter_->GetXaxis()->SetBinLabel(kFlag_muonBadTrackFilter, "Flag_muonBadTrackFilter");
  histogram_MEtFilterCounter_->GetXaxis()->SetBinLabel(kFlag_trkPOGFilters, "Flag_trkPOGFilters");
  histogram_MEtFilterCounter_->GetXaxis()->SetBinLabel(kFlag_trackingFailureFilter, "Flag_trackingFailureFilter");
  histogram_MEtFilterCounter_->GetXaxis()->SetBinLabel(kFlag_CSCTightHaloFilter, "Flag_CSCTightHaloFilter");
  histogram_MEtFilterCounter_->GetXaxis()->SetBinLabel(kFlag_HBHENoiseFilter, "Flag_HBHENoiseFilter");
  histogram_MEtFilterCounter_->GetXaxis()->SetBinLabel(kFlag_chargedHadronTrackResolutionFilter, "Flag_chargedHadronTrackResolutionFilter");
  histogram_MEtFilterCounter_->GetXaxis()->SetBinLabel(kFlag_GlobalTightHalo2016Filter, "Flag_GlobalTightHalo2016Filter");
  histogram_MEtFilterCounter_->GetXaxis()->SetBinLabel(kFlag_METFilters, "Flag_METFilters");
  histogram_MEtFilterCounter_->GetXaxis()->SetBinLabel(kFlag_CSCTightHalo2015Filter, "Flag_CSCTightHalo2015Filter");
  histogram_MEtFilterCounter_->GetXaxis()->SetBinLabel(kFlag_eeBadScFilter, "Flag_eeBadScFilter");
  histogram_MEtFilterCounter_->GetXaxis()->SetBinLabel(kFlag_trkPOG_manystripclus53X, "Flag_trkPOG_manystripclus53X");
  histogram_MEtFilterCounter_->GetXaxis()->SetBinLabel(kFlag_trkPOG_toomanystripclus53X, "Flag_trkPOG_toomanystripclus53X");
  histogram_MEtFilterCounter_->GetXaxis()->SetBinLabel(kFlag_trkPOG_logErrorTooManyClusters, "Flag_trkPOG_logErrorTooManyClusters");
  histogram_MEtFilterCounter_->GetXaxis()->SetBinLabel(kFlag_goodVertices, "Flag_goodVertices");
}

void MEtFilterHistManager::fillHistograms(const MEtFilter& metFilter, double evtWeight)
{
  double evtWeightErr = 0.;
  fill(histogram_MEtFilterCounter_, kFlag_HBHENoiseIsoFilter, metFilter.getFlag_HBHENoiseIsoFilter(), evtWeight, evtWeightErr);
  fill(histogram_MEtFilterCounter_, kFlag_EcalDeadCellTriggerPrimitiveFilter, metFilter.getFlag_EcalDeadCellTriggerPrimitiveFilter(), evtWeight, evtWeightErr);
  fill(histogram_MEtFilterCounter_, kFlag_ecalLaserCorrFilter, metFilter.getFlag_ecalLaserCorrFilter(), evtWeight, evtWeightErr);
  fill(histogram_MEtFilterCounter_, kFlag_hcalLaserEventFilter, metFilter.getFlag_hcalLaserEventFilter(), evtWeight, evtWeightErr);
  fill(histogram_MEtFilterCounter_, kFlag_muonBadTrackFilter, metFilter.getFlag_muonBadTrackFilter(), evtWeight, evtWeightErr);
  fill(histogram_MEtFilterCounter_, kFlag_trkPOGFilters,  metFilter.getFlag_trkPOGFilters(), evtWeight, evtWeightErr);
  fill(histogram_MEtFilterCounter_, kFlag_trackingFailureFilter, metFilter.getFlag_trackingFailureFilter(), evtWeight, evtWeightErr);
  fill(histogram_MEtFilterCounter_, kFlag_CSCTightHaloFilter,  metFilter.getFlag_CSCTightHaloFilter(), evtWeight, evtWeightErr);
  fill(histogram_MEtFilterCounter_, kFlag_HBHENoiseFilter,  metFilter.getFlag_HBHENoiseFilter(), evtWeight, evtWeightErr);
  fill(histogram_MEtFilterCounter_, kFlag_chargedHadronTrackResolutionFilter, metFilter.getFlag_chargedHadronTrackResolutionFilter(), evtWeight, evtWeightErr);
  fill(histogram_MEtFilterCounter_, kFlag_GlobalTightHalo2016Filter, metFilter.getFlag_GlobalTightHalo2016Filter(), evtWeight, evtWeightErr);
  fill(histogram_MEtFilterCounter_, kFlag_METFilters, metFilter.getFlag_METFilters(), evtWeight, evtWeightErr);
  fill(histogram_MEtFilterCounter_, kFlag_CSCTightHalo2015Filter, metFilter.getFlag_CSCTightHalo2015Filter(), evtWeight, evtWeightErr);
  fill(histogram_MEtFilterCounter_, kFlag_eeBadScFilter, metFilter.getFlag_eeBadScFilter(), evtWeight, evtWeightErr);
  fill(histogram_MEtFilterCounter_, kFlag_trkPOG_manystripclus53X, metFilter.getFlag_trkPOG_manystripclus53X(), evtWeight, evtWeightErr);
  fill(histogram_MEtFilterCounter_, kFlag_trkPOG_toomanystripclus53X, metFilter.getFlag_trkPOG_toomanystripclus53X(), evtWeight, evtWeightErr);
  fill(histogram_MEtFilterCounter_, kFlag_trkPOG_logErrorTooManyClusters, metFilter.getFlag_trkPOG_logErrorTooManyClusters(), evtWeight, evtWeightErr);
  fill(histogram_MEtFilterCounter_, kFlag_goodVertices, metFilter.getFlag_goodVertices(), evtWeight, evtWeightErr);
}


