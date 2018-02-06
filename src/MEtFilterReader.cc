#include "tthAnalysis/HiggsToTauTau/interface/MEtFilterReader.h" // MEtFilterReader

#include "tthAnalysis/HiggsToTauTau/interface/MEtFilter.h"
#include "tthAnalysis/HiggsToTauTau/interface/BranchAddressInitializer.h" // BranchAddressInitializer, TTree, Form()

#include <cassert> // assert()

int MEtFilterReader::numInstances_ = 0;
MEtFilterReader* MEtFilterReader::instance_ = nullptr;

MEtFilterReader::MEtFilterReader(MEtFilter* metFilter)

  : branchNameFlag_goodVertices_("Flag_goodVertices"),
    branchNameFlag_globalSuperTightHalo2016Filter_("Flag_globalSuperTightHalo2016Filter"),
    branchNameFlag_HBHENoiseFilter_("Flag_HBHENoiseFilter"),
    branchNameFlag_HBHENoiseIsoFilter_("Flag_HBHENoiseIsoFilter"),
    branchNameFlag_EcalDeadCellTriggerPrimitiveFilter_("Flag_EcalDeadCellTriggerPrimitiveFilter"),
    branchNameFlag_eeBadScFilter_("Flag_eeBadScFilter"),
    branchNameFlag_BadPFMuonFilter_("Flag_BadPFMuonFilter"),
    branchNameFlag_BadChargedCandidateFilter_("Flag_BadChargedCandidateFilter"),
    branchNameFlag_hcalLaserEventFilter_("Flag_hcalLaserEventFilter"),
    branchNameFlag_trkPOGFilters_("Flag_trkPOGFilters"),
    branchNameFlag_CSCTightHaloFilter_("Flag_CSCTightHaloFilter"),
    branchNameFlag_trkPOG_manystripclus53X_("Flag_trkPOG_manystripclus53X"),
    branchNameFlag_trkPOG_toomanystripclus53X_("Flag_trkPOG_toomanystripclus53X"),
    branchNameFlag_trkPOG_logErrorTooManyClusters_("Flag_trkPOG_logErrorTooManyClusters"),
    branchNameFlag_CSCTightHalo2015Filter_("Flag_CSCTightHalo2015Filter"),
    branchNameFlag_BadChargedCandidateSummer16Filter_("Flag_BadChargedCandidateSummer16Filter"),
    branchNameFlag_BadPFMuonSummer16Filter_("Flag_BadPFMuonSummer16Filter"),
    branchNameFlag_CSCTightHaloTrkMuUnvetoFilter_("Flag_CSCTightHaloTrkMuUnvetoFilter"),
    branchNameFlag_EcalDeadCellBoundaryEnergyFilter_("Flag_EcalDeadCellBoundaryEnergyFilter"),
    branchNameFlag_HcalStripHaloFilter_("Flag_HcalStripHaloFilter"),
    branchNameFlag_METFilters_("Flag_METFilters"),
    branchNameFlag_chargedHadronTrackResolutionFilter_("Flag_chargedHadronTrackResolutionFilter"),
    branchNameFlag_ecalBadCalibFilter_("Flag_ecalBadCalibFilter"),
    branchNameFlag_ecalLaserCorrFilter_("Flag_ecalLaserCorrFilter"),
    branchNameFlag_muonBadTrackFilter_("Flag_muonBadTrackFilter"),
    metFilter_(metFilter)


{
  setBranchNames();
}

MEtFilterReader::~MEtFilterReader()
{
  --numInstances_;
  assert(numInstances_ >= 0);
  if(numInstances_ == 0)
  {
    instance_ = nullptr;
  }
}

void
MEtFilterReader::setBranchNames()
{
  if(numInstances_ == 0)
  {
    instance_ = this;
  } 
  ++numInstances_;
}

void
MEtFilterReader::setBranchAddresses(TTree * tree)
{
  if(instance_ == this)
  {
    BranchAddressInitializer bai(tree);

    bai.setBranchAddress(metFilter_->Flag_goodVertices_,                 branchNameFlag_goodVertices_);
    bai.setBranchAddress(metFilter_->Flag_globalSuperTightHalo2016Filter_,                 branchNameFlag_globalSuperTightHalo2016Filter_);
    bai.setBranchAddress(metFilter_->Flag_HBHENoiseFilter_,                 branchNameFlag_HBHENoiseFilter_);
    bai.setBranchAddress(metFilter_->Flag_HBHENoiseIsoFilter_,                 branchNameFlag_HBHENoiseIsoFilter_);
    bai.setBranchAddress(metFilter_->Flag_EcalDeadCellTriggerPrimitiveFilter_,                 branchNameFlag_EcalDeadCellTriggerPrimitiveFilter_);
    bai.setBranchAddress(metFilter_->Flag_eeBadScFilter_,                 branchNameFlag_eeBadScFilter_);
    bai.setBranchAddress(metFilter_->Flag_BadPFMuonFilter_,                 branchNameFlag_BadPFMuonFilter_);
    bai.setBranchAddress(metFilter_->Flag_BadChargedCandidateFilter_,                 branchNameFlag_BadChargedCandidateFilter_);
    bai.setBranchAddress(metFilter_->Flag_hcalLaserEventFilter_,                 branchNameFlag_hcalLaserEventFilter_);
    bai.setBranchAddress(metFilter_->Flag_trkPOGFilters_,                 branchNameFlag_trkPOGFilters_);
    bai.setBranchAddress(metFilter_->Flag_CSCTightHaloFilter_,                 branchNameFlag_CSCTightHaloFilter_);
    bai.setBranchAddress(metFilter_->Flag_trkPOG_manystripclus53X_,                 branchNameFlag_trkPOG_manystripclus53X_);
    bai.setBranchAddress(metFilter_->Flag_trkPOG_toomanystripclus53X_,                 branchNameFlag_trkPOG_toomanystripclus53X_);
    bai.setBranchAddress(metFilter_->Flag_trkPOG_logErrorTooManyClusters_,                 branchNameFlag_trkPOG_logErrorTooManyClusters_);
    bai.setBranchAddress(metFilter_->Flag_CSCTightHalo2015Filter_,                 branchNameFlag_CSCTightHalo2015Filter_);
    bai.setBranchAddress(metFilter_->Flag_BadChargedCandidateSummer16Filter_,                 branchNameFlag_BadChargedCandidateSummer16Filter_);
    bai.setBranchAddress(metFilter_->Flag_BadPFMuonSummer16Filter_,                 branchNameFlag_BadPFMuonSummer16Filter_);
    bai.setBranchAddress(metFilter_->Flag_CSCTightHaloTrkMuUnvetoFilter_,                 branchNameFlag_CSCTightHaloTrkMuUnvetoFilter_);
    bai.setBranchAddress(metFilter_->Flag_EcalDeadCellBoundaryEnergyFilter_,                 branchNameFlag_EcalDeadCellBoundaryEnergyFilter_);
    bai.setBranchAddress(metFilter_->Flag_HcalStripHaloFilter_,                 branchNameFlag_HcalStripHaloFilter_);
    bai.setBranchAddress(metFilter_->Flag_METFilters_,                 branchNameFlag_METFilters_);
    bai.setBranchAddress(metFilter_->Flag_chargedHadronTrackResolutionFilter_,                 branchNameFlag_chargedHadronTrackResolutionFilter_);
    bai.setBranchAddress(metFilter_->Flag_ecalBadCalibFilter_,                 branchNameFlag_ecalBadCalibFilter_);
    bai.setBranchAddress(metFilter_->Flag_ecalLaserCorrFilter_,                 branchNameFlag_ecalLaserCorrFilter_);
    bai.setBranchAddress(metFilter_->Flag_muonBadTrackFilter_,                 branchNameFlag_muonBadTrackFilter_);

  }
}
