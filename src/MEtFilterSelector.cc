#include "tthAnalysis/HiggsToTauTau/interface/MEtFilterSelector.h"

MEtFilterSelector::MEtFilterSelector(const edm::ParameterSet & cfg)
  : apply_Flag_goodVertices_                      (cfg.getParameter<bool>("apply_Flag_goodVertices"))
  , apply_Flag_HBHENoiseIsoFilter_                (cfg.getParameter<bool>("apply_Flag_HBHENoiseIsoFilter"))
  , apply_Flag_EcalDeadCellTriggerPrimitiveFilter_(cfg.getParameter<bool>("apply_Flag_EcalDeadCellTriggerPrimitiveFilter"))
  , apply_Flag_ecalLaserCorrFilter_               (cfg.getParameter<bool>("apply_Flag_ecalLaserCorrFilter"))
  , apply_Flag_muonBadTrackFilter_                (cfg.getParameter<bool>("apply_Flag_muonBadTrackFilter"))
  , apply_Flag_HBHENoiseFilter_                   (cfg.getParameter<bool>("apply_Flag_HBHENoiseFilter"))
  , apply_Flag_chargedHadronTrackResolutionFilter_(cfg.getParameter<bool>("apply_Flag_chargedHadronTrackResolutionFilter"))
  , apply_Flag_GlobalTightHalo2016Filter_         (cfg.getParameter<bool>("apply_Flag_GlobalTightHalo2016Filter"))
  , apply_Flag_eeBadScFilter_                     (cfg.getParameter<bool>("apply_Flag_eeBadScFilter"))
// ---- Flags not recommended in Moriond 2017 recipe but are present inside VHBB 2016 Ntuples ----
  , apply_Flag_hcalLaserEventFilter_              (cfg.getParameter<bool>("apply_Flag_hcalLaserEventFilter"))
  , apply_Flag_trkPOGFilters_                     (cfg.getParameter<bool>("apply_Flag_trkPOGFilters"))
//  , apply_Flag_trackingFailureFilter_             (cfg.getParameter<bool>("apply_Flag_trackingFailureFilter")) // Karl: missing in nanoAOD
  , apply_Flag_CSCTightHaloFilter_                (cfg.getParameter<bool>("apply_Flag_CSCTightHaloFilter"))
  , apply_Flag_METFilters_                        (cfg.getParameter<bool>("apply_Flag_METFilters"))
  , apply_Flag_CSCTightHalo2015Filter_            (cfg.getParameter<bool>("apply_Flag_CSCTightHalo2015Filter"))
  , apply_Flag_trkPOG_manystripclus53X_           (cfg.getParameter<bool>("apply_Flag_trkPOG_manystripclus53X"))
  , apply_Flag_trkPOG_toomanystripclus53X_        (cfg.getParameter<bool>("apply_Flag_trkPOG_toomanystripclus53X"))
  , apply_Flag_trkPOG_logErrorTooManyClusters_    (cfg.getParameter<bool>("apply_Flag_trkPOG_logErrorTooManyClusters"))
{}

bool
MEtFilterSelector::operator()(const MEtFilter & metFilter) const
{
  if(apply_Flag_goodVertices_                       && ! metFilter.getFlag_goodVertices())                       return false;
  if(apply_Flag_HBHENoiseIsoFilter_                 && ! metFilter.getFlag_HBHENoiseIsoFilter())                 return false;
  if(apply_Flag_EcalDeadCellTriggerPrimitiveFilter_ && ! metFilter.getFlag_EcalDeadCellTriggerPrimitiveFilter()) return false;
  if(apply_Flag_ecalLaserCorrFilter_                && ! metFilter.getFlag_ecalLaserCorrFilter())                return false;
  if(apply_Flag_muonBadTrackFilter_                 && ! metFilter.getFlag_muonBadTrackFilter())                 return false;
  if(apply_Flag_HBHENoiseFilter_                    && ! metFilter.getFlag_HBHENoiseFilter())                    return false;
  if(apply_Flag_chargedHadronTrackResolutionFilter_ && ! metFilter.getFlag_chargedHadronTrackResolutionFilter()) return false;
  if(apply_Flag_GlobalTightHalo2016Filter_          && ! metFilter.getFlag_GlobalTightHalo2016Filter())          return false;
  if(apply_Flag_eeBadScFilter_                      && ! metFilter.getFlag_eeBadScFilter())                      return false;

  // ---- Flags not recommended in Moriond 2017 recipe but are present inside VHBB 2016 Ntuples ----
  if(apply_Flag_hcalLaserEventFilter_           && ! metFilter.getFlag_hcalLaserEventFilter())           return false;
  if(apply_Flag_trkPOGFilters_                  && ! metFilter.getFlag_trkPOGFilters())                  return false;
//  if(apply_Flag_trackingFailureFilter_          && ! metFilter.getFlag_trackingFailureFilter())          return false; // Karl: missing in nanoAOD
  if(apply_Flag_CSCTightHaloFilter_             && ! metFilter.getFlag_CSCTightHaloFilter())             return false;
  if(apply_Flag_METFilters_                     && ! metFilter.getFlag_METFilters())                     return false;
  if(apply_Flag_CSCTightHalo2015Filter_         && ! metFilter.getFlag_CSCTightHalo2015Filter())         return false;
  if(apply_Flag_trkPOG_manystripclus53X_        && ! metFilter.getFlag_trkPOG_manystripclus53X())        return false;
  if(apply_Flag_trkPOG_toomanystripclus53X_     && ! metFilter.getFlag_trkPOG_toomanystripclus53X())     return false;
  if(apply_Flag_trkPOG_logErrorTooManyClusters_ && ! metFilter.getFlag_trkPOG_logErrorTooManyClusters()) return false;

  return true;
}




