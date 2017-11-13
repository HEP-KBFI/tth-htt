#include "tthAnalysis/HiggsToTauTau/interface/RecoMuonWriter.h" // RecoMuonWriter

#include "FWCore/Utilities/interface/Exception.h"

#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // kEra_2015, kEra_2016
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
  branchName_looseIdPOG_ = Form("%s_%s", branchName_obj_.data(), "looseIdPOG");
  // CV: for 2016 data, switch to short term Muon POG recommendation for ICHEP,
  //     given at https://twiki.cern.ch/twiki/bin/view/CMS/SWGuideMuonIdRun2#Short_Term_Medium_Muon_Definitio
  if      ( era_ == kEra_2015 ) branchName_mediumIdPOG_ = Form("%s_%s", branchName_obj_.data(), "mediumMuonId");
  else if ( era_ == kEra_2016 ) branchName_mediumIdPOG_ = Form("%s_%s", branchName_obj_.data(), "mediumIdPOG_ICHEP2016");
  else assert(0);
  branchName_segmentCompatibility_ = Form("%s_%s", branchName_obj_.data(), "segmentCompatibility");
}

void RecoMuonWriter::setBranches(TTree *tree)
{
  leptonWriter_->setBranches(tree);
  int max_nLeptons = leptonWriter_->max_nLeptons_;
  looseIdPOG_ = new Int_t[max_nLeptons];
  setBranchVI(tree, branchName_looseIdPOG_, branchName_num_, looseIdPOG_);
  mediumIdPOG_ = new Int_t[max_nLeptons];
  setBranchVI(tree, branchName_mediumIdPOG_, branchName_num_, mediumIdPOG_);
  segmentCompatibility_ = new Float_t[max_nLeptons];
  setBranchVF(tree, branchName_segmentCompatibility_, branchName_num_, segmentCompatibility_);
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
