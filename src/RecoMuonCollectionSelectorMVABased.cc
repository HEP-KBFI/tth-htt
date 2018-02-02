#include "tthAnalysis/HiggsToTauTau/interface/RecoMuonCollectionSelectorMVABased.h" // RecoMuonSelectorMVABased

#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // kEra_2017
#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h" // cmsException()

RecoMuonSelectorMVABased::RecoMuonSelectorMVABased(int era,
                                                   int index,
                                                   bool debug)
  : era_(era)
  , min_pt_(10)
  , min_mvaTTH_(0.75)
  , max_jetBtagCSV_(0.89)
  , apply_mediumIdPOG_(true)
{
  switch(era_)
  {
    case kEra_2017:
      max_jetBtagCSV_    = 0.80;
      apply_tightCharge_ = false; // no thight charge requirement in 2017 sync?
      break;
    default:
      throw cmsException(this) << "Invalid era = " << era_;
  }
}

bool
RecoMuonSelectorMVABased::operator()(const RecoMuon & muon) const
{
  return
    muon.pt()         >= min_pt_                      &&
    muon.mvaRawTTH()  >= min_mvaTTH_                  &&
    muon.jetBtagCSV() <= max_jetBtagCSV_              &&
    (muon.passesMediumIdPOG() || !apply_mediumIdPOG_) &&
    (muon.tightCharge() >= 2 || !apply_tightCharge_)
  ;
}
