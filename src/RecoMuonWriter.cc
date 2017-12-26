#include "tthAnalysis/HiggsToTauTau/interface/RecoMuonWriter.h" // RecoMuonWriter

#include "FWCore/Utilities/interface/Exception.h"

#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // kEra_2017
#include "tthAnalysis/HiggsToTauTau/interface/writerAuxFunctions.h" // setBranchI, setBranchVI, setBranchVF

#include <TString.h> // Form

RecoMuonWriter::RecoMuonWriter(int era)
  : era_(era)
  , branchName_num_("nMuons")
  , branchName_obj_("Muons")
  , leptonWriter_(0)
  , looseIdPOG_(0)
  , mediumIdPOG_(0)
  , segmentCompatibility_(0)
{
  leptonWriter_ = new RecoLeptonWriter(branchName_num_, branchName_obj_);
  setBranchNames();
}

RecoMuonWriter::RecoMuonWriter(int era,
                               const std::string& branchName_num,
                               const std::string& branchName_obj)
  : era_(era)
  , branchName_num_(branchName_num)
  , branchName_obj_(branchName_obj)
  , leptonWriter_(0)
  , looseIdPOG_(0)
  , mediumIdPOG_(0)
  , segmentCompatibility_(0)
{
  leptonWriter_ = new RecoLeptonWriter(branchName_num_, branchName_obj_);
  setBranchNames();
}

RecoMuonWriter::~RecoMuonWriter()
{
  delete leptonWriter_;
  delete[] looseIdPOG_;
  delete[] mediumIdPOG_;
  delete[] segmentCompatibility_;
}

void RecoMuonWriter::setBranchNames()
{
  // Karl: let's write the looseIdPOG branch even though we aren't going to read it
  //       in the first place
  branchName_looseIdPOG_ = Form("%s_%s", branchName_obj_.data(), "looseIdPOG");
  branchName_mediumIdPOG_ = Form("%s_%s", branchName_obj_.data(), "mediumId");
  branchName_segmentCompatibility_ = Form("%s_%s", branchName_obj_.data(), "segmentComp");
}

void RecoMuonWriter::setBranches(TTree *tree)
{
  leptonWriter_->setBranches(tree);
  unsigned int max_nLeptons = leptonWriter_->max_nLeptons_;
  looseIdPOG_ = new Bool_t[max_nLeptons];
  setBranch(tree, looseIdPOG_, branchName_looseIdPOG_, branchName_num_);
  mediumIdPOG_ = new Bool_t[max_nLeptons];
  setBranch(tree, mediumIdPOG_, branchName_mediumIdPOG_, branchName_num_);
  segmentCompatibility_ = new Float_t[max_nLeptons];
  setBranch(tree, segmentCompatibility_, branchName_segmentCompatibility_, branchName_num_);
}

void RecoMuonWriter::write(const std::vector<const RecoMuon*>& leptons) 
{
  leptonWriter_->write(leptons);
  Int_t nLeptons = leptons.size();
  for ( Int_t idxLepton = 0; idxLepton < nLeptons; ++idxLepton ) {
    const RecoMuon* lepton = leptons[idxLepton];
    assert(lepton);
    looseIdPOG_[idxLepton] = lepton->passesLooseIdPOG();
    mediumIdPOG_[idxLepton] = lepton->passesMediumIdPOG();
    segmentCompatibility_[idxLepton] = lepton->segmentCompatibility();
  }
}
