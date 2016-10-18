#include "tthAnalysis/HiggsToTauTau/interface/RecoMuonCollectionSelectorMVABased.h" // RecoMuonSelectorMVABased

#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // kEra_2015, kEra_2016

#include <FWCore/Utilities/interface/Exception.h> // cms::Exception

RecoMuonSelectorMVABased::RecoMuonSelectorMVABased(int era, int index, bool debug)
  : era_(era)
  , min_pt_(10)
  , min_mvaTTH_(0.75)
  , max_jetBtagCSV_(0.89)
  , apply_mediumIdPOG_(true)
{
  switch(era_)
  {
    case kEra_2015:
      max_jetBtagCSV_ = 0.89;
      apply_tightCharge_ = true;
      break;
    case kEra_2016:
      max_jetBtagCSV_ = 0.80;
      apply_tightCharge_ = false; // no thight charge requirement in 2016 sync?
      break;
    default:
      throw cms::Exception("RecoMuonSelectorMVABased") << "Invalid era = " << era_;
  }
}

bool
RecoMuonSelectorMVABased::operator()(const RecoMuon& muon) const
{
  if(muon.pt_ >= min_pt_ &&
     muon.mvaRawTTH_ >= min_mvaTTH_ &&
     muon.jetBtagCSV_ <= max_jetBtagCSV_ &&
     (muon.passesMediumIdPOG_ || !apply_mediumIdPOG_) &&
     (muon.tightCharge_ >= 2 || !apply_tightCharge_)) {
    return true;
  }
  return false;
}
