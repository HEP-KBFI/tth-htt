#include "tthAnalysis/HiggsToTauTau/interface/MEtFilter.h" // MEtFilter

bool MEtFilter::getFlag_HBHENoiseIsoFilter() const                 { return Flag_HBHENoiseIsoFilter_; }
bool MEtFilter::getFlag_EcalDeadCellTriggerPrimitiveFilter() const { return Flag_EcalDeadCellTriggerPrimitiveFilter_; }
bool MEtFilter::getFlag_ecalLaserCorrFilter() const                { return Flag_ecalLaserCorrFilter_; }
bool MEtFilter::getFlag_hcalLaserEventFilter() const               { return Flag_hcalLaserEventFilter_; }
bool MEtFilter::getFlag_muonBadTrackFilter() const                 { return Flag_muonBadTrackFilter_; }
bool MEtFilter::getFlag_trkPOGFilters() const                      { return Flag_trkPOGFilters_; }
//bool MEtFilter::getFlag_trackingFailureFilter() const              { return Flag_trackingFailureFilter_; } // Karl: missing in nanoAOD
bool MEtFilter::getFlag_CSCTightHaloFilter() const                 { return Flag_CSCTightHaloFilter_; }
bool MEtFilter::getFlag_HBHENoiseFilter() const                    { return Flag_HBHENoiseFilter_; }
bool MEtFilter::getFlag_chargedHadronTrackResolutionFilter() const { return Flag_chargedHadronTrackResolutionFilter_; }
bool MEtFilter::getFlag_GlobalTightHalo2016Filter() const          { return Flag_GlobalTightHalo2016Filter_; }
bool MEtFilter::getFlag_METFilters() const                         { return Flag_METFilters_; }
bool MEtFilter::getFlag_CSCTightHalo2015Filter() const             { return Flag_CSCTightHalo2015Filter_; }
bool MEtFilter::getFlag_eeBadScFilter() const                      { return Flag_eeBadScFilter_; }
bool MEtFilter::getFlag_trkPOG_manystripclus53X() const            { return Flag_trkPOG_manystripclus53X_; }
bool MEtFilter::getFlag_trkPOG_toomanystripclus53X() const         { return Flag_trkPOG_toomanystripclus53X_; }
bool MEtFilter::getFlag_trkPOG_logErrorTooManyClusters() const     { return Flag_trkPOG_logErrorTooManyClusters_; }
bool MEtFilter::getFlag_goodVertices() const                       { return Flag_goodVertices_; }

