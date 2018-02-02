#include "tthAnalysis/HiggsToTauTau/interface/MEtFilterReader.h" // MEtFilterReader

#include "tthAnalysis/HiggsToTauTau/interface/MEtFilter.h"
#include "tthAnalysis/HiggsToTauTau/interface/BranchAddressInitializer.h" // BranchAddressInitializer, TTree, Form()

#include <cassert> // assert()

int MEtFilterReader::numInstances_ = 0;
MEtFilterReader * MEtFilterReader::instance_ = nullptr;

MEtFilterReader::MEtFilterReader(MEtFilter * metFilter)
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

std::vector<std::string>
MEtFilterReader::setBranchAddresses(TTree * tree)
{
  std::vector<std::string> branchNames;
  if(instance_ == this)
  {
    BranchAddressInitializer bai(tree);
    bai.setBranchAddress(metFilter_->Flag_HBHENoiseIsoFilter_,                 branchNameFlag_HBHENoiseIsoFilter_);
    bai.setBranchAddress(metFilter_->Flag_EcalDeadCellTriggerPrimitiveFilter_, branchNameFlag_EcalDeadCellTriggerPrimitiveFilter_);
    bai.setBranchAddress(metFilter_->Flag_ecalLaserCorrFilter_,                branchNameFlag_ecalLaserCorrFilter_);
    bai.setBranchAddress(metFilter_->Flag_hcalLaserEventFilter_,               branchNameFlag_hcalLaserEventFilter_);
    bai.setBranchAddress(metFilter_->Flag_muonBadTrackFilter_,                 branchNameFlag_muonBadTrackFilter_);
    bai.setBranchAddress(metFilter_->Flag_trkPOGFilters_,                      branchNameFlag_trkPOGFilters_);
    bai.setBranchAddress(metFilter_->Flag_trackingFailureFilter_,              branchNameFlag_trackingFailureFilter_);
    bai.setBranchAddress(metFilter_->Flag_CSCTightHaloFilter_,                 branchNameFlag_CSCTightHaloFilter_);
    bai.setBranchAddress(metFilter_->Flag_HBHENoiseFilter_,                    branchNameFlag_HBHENoiseFilter_);
    bai.setBranchAddress(metFilter_->Flag_chargedHadronTrackResolutionFilter_, branchNameFlag_chargedHadronTrackResolutionFilter_);
    bai.setBranchAddress(metFilter_->Flag_GlobalTightHalo2016Filter_,          branchNameFlag_GlobalTightHalo2016Filter_);
    bai.setBranchAddress(metFilter_->Flag_METFilters_,                         branchNameFlag_METFilters_);
    bai.setBranchAddress(metFilter_->Flag_CSCTightHalo2015Filter_,             branchNameFlag_CSCTightHalo2015Filter_);
    bai.setBranchAddress(metFilter_->Flag_eeBadScFilter_,                      branchNameFlag_eeBadScFilter_);
    bai.setBranchAddress(metFilter_->Flag_trkPOG_manystripclus53X_,            branchNameFlag_trkPOG_manystripclus53X_);
    bai.setBranchAddress(metFilter_->Flag_trkPOG_toomanystripclus53X_,         branchNameFlag_trkPOG_toomanystripclus53X_);
    bai.setBranchAddress(metFilter_->Flag_trkPOG_logErrorTooManyClusters_,     branchNameFlag_trkPOG_logErrorTooManyClusters_);
    bai.setBranchAddress(metFilter_->Flag_goodVertices_,                       branchNameFlag_goodVertices_);
    bai.mergeBranchNames(branchNames);
  }
  return branchNames;
}

void
MEtFilterReader::read() const
{}
