#include "tthAnalysis/HiggsToTauTau/interface/MEtFilterHistManager.h"

#include "tthAnalysis/HiggsToTauTau/interface/histogramAuxFunctions.h" // fill()

enum
{
  kFlag_HBHENoiseIsoFilter = 1,
  kFlag_EcalDeadCellTriggerPrimitiveFilter,
  kFlag_ecalLaserCorrFilter,
  kFlag_hcalLaserEventFilter,
  kFlag_muonBadTrackFilter,
  kFlag_trkPOGFilters,
  kFlag_trackingFailureFilter,
  kFlag_CSCTightHaloFilter,
  kFlag_HBHENoiseFilter,
  kFlag_chargedHadronTrackResolutionFilter,
  kFlag_GlobalTightHalo2016Filter,
  kFlag_METFilters,
  kFlag_CSCTightHalo2015Filter,
  kFlag_eeBadScFilter,
  kFlag_trkPOG_manystripclus53X,
  kFlag_trkPOG_toomanystripclus53X,
  kFlag_trkPOG_logErrorTooManyClusters,
  kFlag_goodVertices
};


MEtFilterHistManager::MEtFilterHistManager(const edm::ParameterSet& cfg)
  : HistManagerBase(cfg)
{}

void MEtFilterHistManager::bookHistograms(TFileDirectory& dir)
{
  histogram_MEtFilterCounter_ = book1D(dir, "MEtFilterCounter", "MEtFilterCounter", 18, 1., 18.);
  histogram_MEtFilterCounter_->GetXaxis()->SetBinLabel(kFlag_HBHENoiseIsoFilter,                 "Flag_HBHENoiseIsoFilter");
  histogram_MEtFilterCounter_->GetXaxis()->SetBinLabel(kFlag_EcalDeadCellTriggerPrimitiveFilter, "Flag_EcalDeadCellTriggerPrimitiveFilter");
  histogram_MEtFilterCounter_->GetXaxis()->SetBinLabel(kFlag_ecalLaserCorrFilter,                "Flag_ecalLaserCorrFilter");
  histogram_MEtFilterCounter_->GetXaxis()->SetBinLabel(kFlag_hcalLaserEventFilter,               "Flag_hcalLaserEventFilter");
  histogram_MEtFilterCounter_->GetXaxis()->SetBinLabel(kFlag_muonBadTrackFilter,                 "Flag_muonBadTrackFilter");
  histogram_MEtFilterCounter_->GetXaxis()->SetBinLabel(kFlag_trkPOGFilters,                      "Flag_trkPOGFilters");
  histogram_MEtFilterCounter_->GetXaxis()->SetBinLabel(kFlag_trackingFailureFilter,              "Flag_trackingFailureFilter");
  histogram_MEtFilterCounter_->GetXaxis()->SetBinLabel(kFlag_CSCTightHaloFilter,                 "Flag_CSCTightHaloFilter");
  histogram_MEtFilterCounter_->GetXaxis()->SetBinLabel(kFlag_HBHENoiseFilter,                    "Flag_HBHENoiseFilter");
  histogram_MEtFilterCounter_->GetXaxis()->SetBinLabel(kFlag_chargedHadronTrackResolutionFilter, "Flag_chargedHadronTrackResolutionFilter");
  histogram_MEtFilterCounter_->GetXaxis()->SetBinLabel(kFlag_GlobalTightHalo2016Filter,          "Flag_GlobalTightHalo2016Filter");
  histogram_MEtFilterCounter_->GetXaxis()->SetBinLabel(kFlag_METFilters,                         "Flag_METFilters");
  histogram_MEtFilterCounter_->GetXaxis()->SetBinLabel(kFlag_CSCTightHalo2015Filter,             "Flag_CSCTightHalo2015Filter");
  histogram_MEtFilterCounter_->GetXaxis()->SetBinLabel(kFlag_eeBadScFilter,                      "Flag_eeBadScFilter");
  histogram_MEtFilterCounter_->GetXaxis()->SetBinLabel(kFlag_trkPOG_manystripclus53X,            "Flag_trkPOG_manystripclus53X");
  histogram_MEtFilterCounter_->GetXaxis()->SetBinLabel(kFlag_trkPOG_toomanystripclus53X,         "Flag_trkPOG_toomanystripclus53X");
  histogram_MEtFilterCounter_->GetXaxis()->SetBinLabel(kFlag_trkPOG_logErrorTooManyClusters,     "Flag_trkPOG_logErrorTooManyClusters");
  histogram_MEtFilterCounter_->GetXaxis()->SetBinLabel(kFlag_goodVertices,                       "Flag_goodVertices");
}

void
MEtFilterHistManager::fillHistograms(const MEtFilter & metFilter,
                                     double evtWeight)
{
  const double evtWeightErr = 0.;

  const auto conditionalFill = [evtWeight, evtWeightErr](TH1 * histogram,
                                                         int filter,
                                                         bool flag) -> void
  {
    if(! flag)
    {
      // CV: fill histogram if filter has failed
      fill(histogram, filter, evtWeight, evtWeightErr);
    }
  };

  conditionalFill(histogram_MEtFilterCounter_, kFlag_HBHENoiseIsoFilter,                 metFilter.getFlag_HBHENoiseIsoFilter());
  conditionalFill(histogram_MEtFilterCounter_, kFlag_EcalDeadCellTriggerPrimitiveFilter, metFilter.getFlag_EcalDeadCellTriggerPrimitiveFilter());
  conditionalFill(histogram_MEtFilterCounter_, kFlag_ecalLaserCorrFilter,                metFilter.getFlag_ecalLaserCorrFilter());
  conditionalFill(histogram_MEtFilterCounter_, kFlag_hcalLaserEventFilter,               metFilter.getFlag_hcalLaserEventFilter());
  conditionalFill(histogram_MEtFilterCounter_, kFlag_muonBadTrackFilter,                 metFilter.getFlag_muonBadTrackFilter());
  conditionalFill(histogram_MEtFilterCounter_, kFlag_trkPOGFilters,                      metFilter.getFlag_trkPOGFilters());
  conditionalFill(histogram_MEtFilterCounter_, kFlag_trackingFailureFilter,              metFilter.getFlag_trackingFailureFilter());
  conditionalFill(histogram_MEtFilterCounter_, kFlag_CSCTightHaloFilter,                 metFilter.getFlag_CSCTightHaloFilter());
  conditionalFill(histogram_MEtFilterCounter_, kFlag_HBHENoiseFilter,                    metFilter.getFlag_HBHENoiseFilter());
  conditionalFill(histogram_MEtFilterCounter_, kFlag_chargedHadronTrackResolutionFilter, metFilter.getFlag_chargedHadronTrackResolutionFilter());
  conditionalFill(histogram_MEtFilterCounter_, kFlag_GlobalTightHalo2016Filter,          metFilter.getFlag_GlobalTightHalo2016Filter());
  conditionalFill(histogram_MEtFilterCounter_, kFlag_METFilters,                         metFilter.getFlag_METFilters());
  conditionalFill(histogram_MEtFilterCounter_, kFlag_CSCTightHalo2015Filter,             metFilter.getFlag_CSCTightHalo2015Filter());
  conditionalFill(histogram_MEtFilterCounter_, kFlag_eeBadScFilter,                      metFilter.getFlag_eeBadScFilter());
  conditionalFill(histogram_MEtFilterCounter_, kFlag_trkPOG_manystripclus53X,            metFilter.getFlag_trkPOG_manystripclus53X());
  conditionalFill(histogram_MEtFilterCounter_, kFlag_trkPOG_toomanystripclus53X,         metFilter.getFlag_trkPOG_toomanystripclus53X());
  conditionalFill(histogram_MEtFilterCounter_, kFlag_trkPOG_logErrorTooManyClusters,     metFilter.getFlag_trkPOG_logErrorTooManyClusters());
  conditionalFill(histogram_MEtFilterCounter_, kFlag_goodVertices,                       metFilter.getFlag_goodVertices());
}
