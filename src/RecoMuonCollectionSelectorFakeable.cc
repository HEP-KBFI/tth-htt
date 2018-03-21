#include "tthAnalysis/HiggsToTauTau/interface/RecoMuonCollectionSelectorFakeable.h" // RecoMuonSelectorFakeable

#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // kEra_2017
#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h" // cmsException()

RecoMuonSelectorFakeable::RecoMuonSelectorFakeable(int era,
                                                   int index,
                                                   bool debug,
                                                   bool set_selection_flags)
  : era_(era)
  , set_selection_flags_(set_selection_flags)
  , tightMuonSelector_(era_, index, debug, false)
  , min_cone_pt_(10.)
  , min_lepton_pt_(5.)
  , max_absEta_(2.4)
  , max_dxy_(0.05)
  , max_dz_(0.1)
  , max_relIso_(0.4)
  , max_sip3d_(8.)
  , apply_looseIdPOG_(true)
  , binning_mvaTTH_({ 0.90 }) // Table 6 in AN2017_029_v5
  , min_jetPtRatio_({ 0.50, -1.e+3 }) // Table 6 in AN2017_029_v5
  , apply_mediumIdPOG_(false)
  , min_segmentCompatibility_({0.3, -1.e+3})
{
  switch(era_)
  {
    case kEra_2017:
    {
      // temporary encoding:
      // 0 -- no jet nearby
      // 1 -- jet CSVv2 < 0.3
      // 2 -- 0.3 <= jet CSVv2 < 0.8484
      // 3 -- jet CSVv2 >= 0.8484
      max_jetBtagCSV_ = { 1, 2 };  // Table 6 in AN2017_029_v5
      break;
    }
    default: throw cmsException(this) << "Invalid era: " << era_;
  }
}

bool
RecoMuonSelectorFakeable::operator()(const RecoMuon & muon) const
{
  if(muon.cone_pt()        >= min_cone_pt_            &&
     muon.lepton_pt()      >= min_lepton_pt_          &&
     muon.absEta()         <= max_absEta_             &&
     std::fabs(muon.dxy()) <= max_dxy_                &&
     std::fabs(muon.dz())  <= max_dz_                 &&
     muon.relIso()         <= max_relIso_             &&
     muon.sip3d()          <= max_sip3d_              &&
     (muon.passesLooseIdPOG() || ! apply_looseIdPOG_) &&
     (muon.passesMediumIdPOG() || ! apply_mediumIdPOG_))
  {
    const int idxBin = muon.mvaRawTTH() <= binning_mvaTTH_[0] ? 0 : 1;
    if(muon.jetPtRatio()        >= min_jetPtRatio_[idxBin] &&
       muon.jetBtag_csvv2_cut() <= max_jetBtagCSV_[idxBin] &&
       muon.segmentCompatibility() > min_segmentCompatibility_[idxBin])
    {
      if(set_selection_flags_)
      {
        muon.set_isFakeable();
        if(tightMuonSelector_(muon))
        {
          muon.set_isTight();
        }
      } // set_selection_flags
      return true;
    } // muon.jetPtRatio, muon.jetBtagCSV
  }
  return false;
}

void
RecoMuonSelectorFakeable::set_selection_flags(bool selection_flags)
{
  set_selection_flags_ = selection_flags;
}

RecoMuonCollectionSelectorFakeable::RecoMuonCollectionSelectorFakeable(int era,
                                                                       int index,
                                                                       bool debug,
                                                                       bool set_selection_flags)
  : ParticleCollectionSelector<RecoMuon, RecoMuonSelectorFakeable>(era, index, debug)
{
  selector_.set_selection_flags(set_selection_flags);
}
