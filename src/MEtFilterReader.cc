#include "tthAnalysis/HiggsToTauTau/interface/MEtFilterReader.h" // MEtFilterReader

#include "FWCore/Utilities/interface/Exception.h"

#include <assert.h> // assert

int MEtFilterReader::numInstances_ = 0;
MEtFilterReader* MEtFilterReader::instance_ = 0;

MEtFilterReader::MEtFilterReader(MEtFilter* metFilter) // NEW !
  : branchNameFlag_HBHENoiseIsoFilter_("Flag_HBHENoiseIsoFilter")
  , branchNameFlag_EcalDeadCellTriggerPrimitiveFilter_("Flag_EcalDeadCellTriggerPrimitiveFilter")
  , branchNameFlag_ecalLaserCorrFilter_("Flag_ecalLaserCorrFilter")
  , branchNameFlag_hcalLaserEventFilter_("Flag_hcalLaserEventFilter")
  , branchNameFlag_muonBadTrackFilter_("Flag_muonBadTrackFilter")
  , branchNameFlag_trkPOGFilters_("Flag_trkPOGFilters")
  , branchNameFlag_trackingFailureFilter_("Flag_trackingFailureFilter")
  , branchNameFlag_CSCTightHaloFilter_("Flag_CSCTightHaloFilter")
  , branchNameFlag_HBHENoiseFilter_("Flag_HBHENoiseFilter")
  , branchNameFlag_chargedHadronTrackResolutionFilter_("Flag_chargedHadronTrackResolutionFilter")
  , branchNameFlag_GlobalTightHalo2016Filter_("Flag_GlobalTightHalo2016Filter")
  , branchNameFlag_METFilters_("Flag_METFilters")
  , branchNameFlag_CSCTightHalo2015Filter_("Flag_CSCTightHalo2015Filter")
  , branchNameFlag_eeBadScFilter_("Flag_eeBadScFilter")
  , branchNameFlag_trkPOG_manystripclus53X_("Flag_trkPOG_manystripclus53X")
  , branchNameFlag_trkPOG_toomanystripclus53X_("Flag_trkPOG_toomanystripclus53X")
  , branchNameFlag_trkPOG_logErrorTooManyClusters_("Flag_trkPOG_logErrorTooManyClusters")
  , branchNameFlag_goodVertices_("Flag_goodVertices")
  , metFilter_(metFilter) 
{
  setBranchNames();
}

MEtFilterReader::~MEtFilterReader()
{
  --numInstances_;
  assert(numInstances_ >= 0);
  if ( numInstances_ == 0 ) {
    instance_ = 0;
  }
}

void MEtFilterReader::setBranchNames()
{
  if ( numInstances_ == 0 ) {
    instance_ = this;
  } 
  ++numInstances_;
}

void MEtFilterReader::setBranchAddresses(TTree* tree)
{
  if ( instance_ == this ) { // NEW !
    tree->SetBranchAddress(branchNameFlag_HBHENoiseIsoFilter_.data(), &metFilter_->Flag_HBHENoiseIsoFilter_);   
    tree->SetBranchAddress(branchNameFlag_EcalDeadCellTriggerPrimitiveFilter_.data(), &metFilter_->Flag_EcalDeadCellTriggerPrimitiveFilter_);   
    tree->SetBranchAddress(branchNameFlag_ecalLaserCorrFilter_.data(), &metFilter_->Flag_ecalLaserCorrFilter_);
    tree->SetBranchAddress(branchNameFlag_hcalLaserEventFilter_.data(), &metFilter_->Flag_hcalLaserEventFilter_);   
    tree->SetBranchAddress(branchNameFlag_muonBadTrackFilter_.data(), &metFilter_->Flag_muonBadTrackFilter_);   
    tree->SetBranchAddress(branchNameFlag_trkPOGFilters_.data(), &metFilter_->Flag_trkPOGFilters_);   
    tree->SetBranchAddress(branchNameFlag_trackingFailureFilter_.data(), &metFilter_->Flag_trackingFailureFilter_);   
    tree->SetBranchAddress(branchNameFlag_CSCTightHaloFilter_.data(), &metFilter_->Flag_CSCTightHaloFilter_);   
    tree->SetBranchAddress(branchNameFlag_HBHENoiseFilter_.data(), &metFilter_->Flag_HBHENoiseFilter_);   
    tree->SetBranchAddress(branchNameFlag_chargedHadronTrackResolutionFilter_.data(), &metFilter_->Flag_chargedHadronTrackResolutionFilter_);   
    tree->SetBranchAddress(branchNameFlag_GlobalTightHalo2016Filter_.data(), &metFilter_->Flag_GlobalTightHalo2016Filter_);   
    tree->SetBranchAddress(branchNameFlag_METFilters_.data(), &metFilter_->Flag_METFilters_);   
    tree->SetBranchAddress(branchNameFlag_CSCTightHalo2015Filter_.data(), &metFilter_->Flag_CSCTightHalo2015Filter_);   
    tree->SetBranchAddress(branchNameFlag_eeBadScFilter_.data(), &metFilter_->Flag_eeBadScFilter_);   
    tree->SetBranchAddress(branchNameFlag_trkPOG_manystripclus53X_.data(), &metFilter_->Flag_trkPOG_manystripclus53X_);   
    tree->SetBranchAddress(branchNameFlag_trkPOG_toomanystripclus53X_.data(), &metFilter_->Flag_trkPOG_toomanystripclus53X_);   
    tree->SetBranchAddress(branchNameFlag_trkPOG_logErrorTooManyClusters_.data(), &metFilter_->Flag_trkPOG_logErrorTooManyClusters_);   
    tree->SetBranchAddress(branchNameFlag_goodVertices_.data(), &metFilter_->Flag_goodVertices_);   
  }
}

void MEtFilterReader::read() const
{}


























