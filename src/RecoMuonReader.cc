#include "tthAnalysis/HiggsToTauTau/interface/RecoMuonReader.h" // RecoMuonReader

#include "FWCore/Utilities/interface/Exception.h"

#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // kEra_2017

#include <TString.h> // Form

std::map<std::string, int> RecoMuonReader::numInstances_;
std::map<std::string, RecoMuonReader *> RecoMuonReader::instances_;

RecoMuonReader::RecoMuonReader(int era, bool readGenMatching)
  : era_(era)
  , use_HIP_mitigation_(true)
  , branchName_num_("nselLeptons")
  , branchName_obj_("selLeptons")
  , leptonReader_(0)
  , mediumIdPOG_(0)
  , segmentCompatibility_(0)
{
  leptonReader_ = new RecoLeptonReader(branchName_num_, branchName_obj_, readGenMatching);
  setBranchNames();
}

RecoMuonReader::RecoMuonReader(int era, const std::string& branchName_num, const std::string& branchName_obj, bool readGenMatching)
  : era_(era)
  , use_HIP_mitigation_(true)
  , branchName_num_(branchName_num)
  , branchName_obj_(branchName_obj)
  , leptonReader_(0)
  , mediumIdPOG_(0)
  , segmentCompatibility_(0)
{
  leptonReader_ = new RecoLeptonReader(branchName_num_, branchName_obj_, readGenMatching);
  setBranchNames();
}

RecoMuonReader::~RecoMuonReader()
{
  --numInstances_[branchName_obj_];
  assert(numInstances_[branchName_obj_] >= 0);

  if (numInstances_[branchName_obj_] == 0) {
    RecoMuonReader *gInstance = instances_[branchName_obj_];
    assert(gInstance);
    delete[] gInstance->mediumIdPOG_;
    delete[] gInstance->segmentCompatibility_;
    instances_[branchName_obj_] = 0;
  }
}

void RecoMuonReader::setBranchNames()
{
  if ( numInstances_[branchName_obj_] == 0 ) {
    branchName_mediumIdPOG_ = Form("%s_%s", branchName_obj_.data(), "mediumId"); // Karl: already includes HIP mitigation for 2016 B-F
    branchName_segmentCompatibility_ = Form("%s_%s", branchName_obj_.data(), "segmentComp");
    instances_[branchName_obj_] = this;
  } else {
    if (branchName_num_ != instances_[branchName_obj_]->branchName_num_) {
      throw cms::Exception("RecoMuonReader")
	<< "Association between configuration parameters 'branchName_num' and 'branchName_obj' must be unique:"
	<< " present association 'branchName_num' = " << branchName_num_ << " with 'branchName_obj' = " << branchName_obj_
	<< " does not match previous association 'branchName_num' = " << instances_[branchName_obj_]->branchName_num_ << " with 'branchName_obj' = " << instances_[branchName_obj_]->branchName_obj_ << " !!\n";
    }
  }
  ++numInstances_[branchName_obj_];
}

void RecoMuonReader::setBranchAddresses(TTree *tree)
{
  if ( instances_[branchName_obj_] == this ) {
    leptonReader_->setBranchAddresses(tree);
    int max_nLeptons = leptonReader_->max_nLeptons_;
    mediumIdPOG_ = new Bool_t[max_nLeptons];
    tree->SetBranchAddress(branchName_mediumIdPOG_.data(), mediumIdPOG_);
    segmentCompatibility_ = new Float_t[max_nLeptons];
    tree->SetBranchAddress(branchName_segmentCompatibility_.data(), segmentCompatibility_);
  }
}

std::vector<RecoMuon> RecoMuonReader::read() const
{
  RecoLeptonReader* gLeptonReader = leptonReader_->instances_[branchName_obj_];
  assert(gLeptonReader);
  RecoMuonReader* gMuonReader = instances_[branchName_obj_];
  assert(gMuonReader);
  std::vector<RecoMuon> muons;
  Int_t nLeptons = gLeptonReader->nLeptons_;
  
  if ( nLeptons > leptonReader_->max_nLeptons_ ) {
    throw cms::Exception("RecoMuonReader")
      << "Number of leptons stored in Ntuple = " << nLeptons << ", exceeds max_nLeptons = " << leptonReader_->max_nLeptons_ << " !!\n";
  }
  if ( nLeptons > 0 ) {
    muons.reserve(nLeptons);
    for ( Int_t idxLepton = 0; idxLepton < nLeptons; ++idxLepton ) {
      if ( std::abs(gLeptonReader->pdgId_[idxLepton]) == 13 ) {
        muons.push_back(RecoMuon({
          gLeptonReader->pt_[idxLepton],
          gLeptonReader->eta_[idxLepton],
          gLeptonReader->phi_[idxLepton],
          gLeptonReader->mass_[idxLepton],
          gLeptonReader->pdgId_[idxLepton],
          gLeptonReader->dxy_[idxLepton],
          gLeptonReader->dz_[idxLepton],
          gLeptonReader->relIso_[idxLepton],
          gLeptonReader->chargedHadRelIso03_[idxLepton],
          gLeptonReader->miniRelIsoCharged_[idxLepton],
          gLeptonReader->sip3d_[idxLepton],
          gLeptonReader->mvaRawTTH_[idxLepton],
          gLeptonReader->jetPtRatio_[idxLepton],
          gLeptonReader->jetBtagCSV_[idxLepton],
          gLeptonReader->tightCharge_[idxLepton],
          gLeptonReader->charge_[idxLepton],
          true, // Karl: all muon objects pass Muon POG's loose definition at the nanoAOD prodction level
          gMuonReader->mediumIdPOG_[idxLepton],
          gMuonReader->segmentCompatibility_[idxLepton]
        }));
      }
    }
    gLeptonReader->readGenMatching(muons);
  }
  return muons;
}
