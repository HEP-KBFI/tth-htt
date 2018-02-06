#include "tthAnalysis/HiggsToTauTau/interface/MEtFilterHistManager.h"

#include "tthAnalysis/HiggsToTauTau/interface/histogramAuxFunctions.h" // fill()

enum
{
  kFlag_goodVertices = 1,
  kFlag_globalSuperTightHalo2016Filter = 2,
  kFlag_HBHENoiseFilter = 3,
  kFlag_HBHENoiseIsoFilter = 4,
  kFlag_EcalDeadCellTriggerPrimitiveFilter = 5,
  kFlag_eeBadScFilter = 6,
  kFlag_BadPFMuonFilter = 7,  
  kFlag_BadChargedCandidateFilter = 8, 
  kFlag_hcalLaserEventFilter = 9,
  kFlag_trkPOGFilters = 10,
  kFlag_CSCTightHaloFilter = 11,
  kFlag_trkPOG_manystripclus53X = 12,
  kFlag_trkPOG_toomanystripclus53X = 13,
  kFlag_trkPOG_logErrorTooManyClusters = 14,
  kFlag_CSCTightHalo2015Filter = 15,            
  kFlag_BadChargedCandidateSummer16Filter = 16, 
  kFlag_BadPFMuonSummer16Filter = 17,           
  kFlag_CSCTightHaloTrkMuUnvetoFilter = 18,     
  kFlag_EcalDeadCellBoundaryEnergyFilter = 19,  
  kFlag_HcalStripHaloFilter = 20,                
  kFlag_METFilters = 21,                        
  kFlag_chargedHadronTrackResolutionFilter = 22, 
  kFlag_ecalBadCalibFilter = 23,                 
  kFlag_ecalLaserCorrFilter = 24,                
  kFlag_muonBadTrackFilter = 25
};


MEtFilterHistManager::MEtFilterHistManager(const edm::ParameterSet& cfg)
  : HistManagerBase(cfg)
{}

void MEtFilterHistManager::bookHistograms(TFileDirectory& dir)
{
  histogram_MEtFilterCounter_ = book1D(dir, "MEtFilterCounter", "MEtFilterCounter", 18, 1., 18.);
  histogram_MEtFilterCounter_->GetXaxis()->SetBinLabel(kFlag_goodVertices,                 "Flag_goodVertices");
  histogram_MEtFilterCounter_->GetXaxis()->SetBinLabel(kFlag_globalSuperTightHalo2016Filter,                 "Flag_globalSuperTightHalo2016Filter");
  histogram_MEtFilterCounter_->GetXaxis()->SetBinLabel(kFlag_HBHENoiseFilter,                 "Flag_HBHENoiseFilter");
  histogram_MEtFilterCounter_->GetXaxis()->SetBinLabel(kFlag_HBHENoiseIsoFilter,                 "Flag_HBHENoiseIsoFilter");
  histogram_MEtFilterCounter_->GetXaxis()->SetBinLabel(kFlag_EcalDeadCellTriggerPrimitiveFilter,                 "Flag_EcalDeadCellTriggerPrimitiveFilter");
  histogram_MEtFilterCounter_->GetXaxis()->SetBinLabel(kFlag_eeBadScFilter,                 "Flag_eeBadScFilter");
  histogram_MEtFilterCounter_->GetXaxis()->SetBinLabel(kFlag_BadPFMuonFilter,                 "Flag_BadPFMuonFilter");
  histogram_MEtFilterCounter_->GetXaxis()->SetBinLabel(kFlag_BadChargedCandidateFilter,                 "Flag_BadChargedCandidateFilter");
  histogram_MEtFilterCounter_->GetXaxis()->SetBinLabel(kFlag_hcalLaserEventFilter,                 "Flag_hcalLaserEventFilter");
  histogram_MEtFilterCounter_->GetXaxis()->SetBinLabel(kFlag_trkPOGFilters,                 "Flag_trkPOGFilters");
  histogram_MEtFilterCounter_->GetXaxis()->SetBinLabel(kFlag_CSCTightHaloFilter,                 "Flag_CSCTightHaloFilter");
  histogram_MEtFilterCounter_->GetXaxis()->SetBinLabel(kFlag_trkPOG_manystripclus53X,                 "Flag_trkPOG_manystripclus53X");
  histogram_MEtFilterCounter_->GetXaxis()->SetBinLabel(kFlag_trkPOG_toomanystripclus53X,                 "Flag_trkPOG_toomanystripclus53X");
  histogram_MEtFilterCounter_->GetXaxis()->SetBinLabel(kFlag_trkPOG_logErrorTooManyClusters,                 "Flag_trkPOG_logErrorTooManyClusters");
  histogram_MEtFilterCounter_->GetXaxis()->SetBinLabel(kFlag_CSCTightHalo2015Filter,                 "Flag_CSCTightHalo2015Filter");
  histogram_MEtFilterCounter_->GetXaxis()->SetBinLabel(kFlag_BadChargedCandidateSummer16Filter,                 "Flag_BadChargedCandidateSummer16Filter");
  histogram_MEtFilterCounter_->GetXaxis()->SetBinLabel(kFlag_BadPFMuonSummer16Filter,                 "Flag_BadPFMuonSummer16Filter");
  histogram_MEtFilterCounter_->GetXaxis()->SetBinLabel(kFlag_CSCTightHaloTrkMuUnvetoFilter,                 "Flag_CSCTightHaloTrkMuUnvetoFilter");
  histogram_MEtFilterCounter_->GetXaxis()->SetBinLabel(kFlag_EcalDeadCellBoundaryEnergyFilter,                 "Flag_EcalDeadCellBoundaryEnergyFilter");
  histogram_MEtFilterCounter_->GetXaxis()->SetBinLabel(kFlag_HcalStripHaloFilter,                 "Flag_HcalStripHaloFilter");
  histogram_MEtFilterCounter_->GetXaxis()->SetBinLabel(kFlag_METFilters,                 "Flag_METFilters");
  histogram_MEtFilterCounter_->GetXaxis()->SetBinLabel(kFlag_chargedHadronTrackResolutionFilter,                 "Flag_chargedHadronTrackResolutionFilter");
  histogram_MEtFilterCounter_->GetXaxis()->SetBinLabel(kFlag_ecalBadCalibFilter,                 "Flag_ecalBadCalibFilter");
  histogram_MEtFilterCounter_->GetXaxis()->SetBinLabel(kFlag_ecalLaserCorrFilter,                 "Flag_ecalLaserCorrFilter");
  histogram_MEtFilterCounter_->GetXaxis()->SetBinLabel(kFlag_muonBadTrackFilter,                 "Flag_muonBadTrackFilter");




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


  conditionalFill(histogram_MEtFilterCounter_, kFlag_goodVertices,                 metFilter.getFlag_goodVertices());
  conditionalFill(histogram_MEtFilterCounter_, kFlag_globalSuperTightHalo2016Filter,                 metFilter.getFlag_globalSuperTightHalo2016Filter());
  conditionalFill(histogram_MEtFilterCounter_, kFlag_HBHENoiseFilter,                 metFilter.getFlag_HBHENoiseFilter());
  conditionalFill(histogram_MEtFilterCounter_, kFlag_HBHENoiseIsoFilter,                 metFilter.getFlag_HBHENoiseIsoFilter());
  conditionalFill(histogram_MEtFilterCounter_, kFlag_EcalDeadCellTriggerPrimitiveFilter,                 metFilter.getFlag_EcalDeadCellTriggerPrimitiveFilter());
  conditionalFill(histogram_MEtFilterCounter_, kFlag_eeBadScFilter,                 metFilter.getFlag_eeBadScFilter());
  conditionalFill(histogram_MEtFilterCounter_, kFlag_BadPFMuonFilter,                 metFilter.getFlag_BadPFMuonFilter());
  conditionalFill(histogram_MEtFilterCounter_, kFlag_BadChargedCandidateFilter,                 metFilter.getFlag_BadChargedCandidateFilter());
  conditionalFill(histogram_MEtFilterCounter_, kFlag_hcalLaserEventFilter,                 metFilter.getFlag_hcalLaserEventFilter());
  conditionalFill(histogram_MEtFilterCounter_, kFlag_trkPOGFilters,                 metFilter.getFlag_trkPOGFilters());
  conditionalFill(histogram_MEtFilterCounter_, kFlag_CSCTightHaloFilter,                 metFilter.getFlag_CSCTightHaloFilter());
  conditionalFill(histogram_MEtFilterCounter_, kFlag_trkPOG_manystripclus53X,                 metFilter.getFlag_trkPOG_manystripclus53X());
  conditionalFill(histogram_MEtFilterCounter_, kFlag_trkPOG_toomanystripclus53X,                 metFilter.getFlag_trkPOG_toomanystripclus53X());
  conditionalFill(histogram_MEtFilterCounter_, kFlag_trkPOG_logErrorTooManyClusters,                 metFilter.getFlag_trkPOG_logErrorTooManyClusters());
  conditionalFill(histogram_MEtFilterCounter_, kFlag_CSCTightHalo2015Filter,                 metFilter.getFlag_CSCTightHalo2015Filter());
  conditionalFill(histogram_MEtFilterCounter_, kFlag_BadChargedCandidateSummer16Filter,                 metFilter.getFlag_BadChargedCandidateSummer16Filter());
  conditionalFill(histogram_MEtFilterCounter_, kFlag_BadPFMuonSummer16Filter,                 metFilter.getFlag_BadPFMuonSummer16Filter());
  conditionalFill(histogram_MEtFilterCounter_, kFlag_CSCTightHaloTrkMuUnvetoFilter,                 metFilter.getFlag_CSCTightHaloTrkMuUnvetoFilter());
  conditionalFill(histogram_MEtFilterCounter_, kFlag_EcalDeadCellBoundaryEnergyFilter,                 metFilter.getFlag_EcalDeadCellBoundaryEnergyFilter());
  conditionalFill(histogram_MEtFilterCounter_, kFlag_HcalStripHaloFilter,                 metFilter.getFlag_HcalStripHaloFilter());
  conditionalFill(histogram_MEtFilterCounter_, kFlag_METFilters,                 metFilter.getFlag_METFilters());
  conditionalFill(histogram_MEtFilterCounter_, kFlag_chargedHadronTrackResolutionFilter,                 metFilter.getFlag_chargedHadronTrackResolutionFilter());
  conditionalFill(histogram_MEtFilterCounter_, kFlag_ecalBadCalibFilter,                 metFilter.getFlag_ecalBadCalibFilter());
  conditionalFill(histogram_MEtFilterCounter_, kFlag_ecalLaserCorrFilter,                 metFilter.getFlag_ecalLaserCorrFilter());
  conditionalFill(histogram_MEtFilterCounter_, kFlag_muonBadTrackFilter,                 metFilter.getFlag_muonBadTrackFilter());

  /*
  conditionalFill(histogram_MEtFilterCounter_, kFlag_HBHENoiseIsoFilter,                 metFilter.getFlag_HBHENoiseIsoFilter());
  conditionalFill(histogram_MEtFilterCounter_, kFlag_EcalDeadCellTriggerPrimitiveFilter, metFilter.getFlag_EcalDeadCellTriggerPrimitiveFilter());
  conditionalFill(histogram_MEtFilterCounter_, kFlag_ecalLaserCorrFilter,                metFilter.getFlag_ecalLaserCorrFilter());
  conditionalFill(histogram_MEtFilterCounter_, kFlag_hcalLaserEventFilter,               metFilter.getFlag_hcalLaserEventFilter());
  conditionalFill(histogram_MEtFilterCounter_, kFlag_muonBadTrackFilter,                 metFilter.getFlag_muonBadTrackFilter());
  conditionalFill(histogram_MEtFilterCounter_, kFlag_trkPOGFilters,                      metFilter.getFlag_trkPOGFilters());
//  conditionalFill(histogram_MEtFilterCounter_, kFlag_trackingFailureFilter,              metFilter.getFlag_trackingFailureFilter()); // Karl: missing in nanoAOD
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
  */
}
