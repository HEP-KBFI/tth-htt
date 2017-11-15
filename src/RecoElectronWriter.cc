#include "tthAnalysis/HiggsToTauTau/interface/RecoElectronWriter.h" // RecoElectronWriter

#include "FWCore/Utilities/interface/Exception.h"

#include "tthAnalysis/HiggsToTauTau/interface/writerAuxFunctions.h" // setBranchVI, setBranchVF

#include <TString.h> // Form

RecoElectronWriter::RecoElectronWriter(int era)
  : branchName_num_("nElectrons")
  , branchName_obj_("Electrons")
  , leptonWriter_(0)
  , mvaRawPOG_GP_(0)
  , mvaRawPOG_HZZ_(0)
  , sigmaEtaEta_(0)
  , HoE_(0)
  , deltaEta_(0)
  , deltaPhi_(0)
  , OoEminusOoP_(0)
  , lostHits_(0)
  , conversionVeto_(0)
{
  leptonWriter_ = new RecoLeptonWriter(branchName_num_, branchName_obj_);
  setBranchNames();
}

RecoElectronWriter::RecoElectronWriter(int era, const std::string& branchName_num, const std::string& branchName_obj)
  : branchName_num_(branchName_num)
  , branchName_obj_(branchName_obj)
  , leptonWriter_(0)
  , mvaRawPOG_GP_(0)
  , mvaRawPOG_HZZ_(0)
  , sigmaEtaEta_(0)
  , HoE_(0)
  , deltaEta_(0)
  , deltaPhi_(0)
  , OoEminusOoP_(0)
  , lostHits_(0)
  , conversionVeto_(0)
{
  leptonWriter_ = new RecoLeptonWriter(branchName_num_, branchName_obj_);
  setBranchNames();
}

RecoElectronWriter::~RecoElectronWriter()
{
  delete leptonWriter_;
  delete[] mvaRawPOG_GP_;
  delete[] mvaRawPOG_HZZ_;
  delete[] sigmaEtaEta_;
  delete[] HoE_;
  delete[] deltaEta_;
  delete[] deltaPhi_;
  delete[] OoEminusOoP_;
  delete[] lostHits_;
  delete[] conversionVeto_;
}

void RecoElectronWriter::setBranchNames()
{
  branchName_mvaRawPOG_GP_ = Form("%s_%s", branchName_obj_.data(), "mvaSpring16GP");
  branchName_mvaRawPOG_HZZ_ = Form("%s_%s", branchName_obj_.data(), "mvaSpring16HZZ");
  branchName_sigmaEtaEta_ = Form("%s_%s", branchName_obj_.data(), "sieie");
  branchName_HoE_ = Form("%s_%s", branchName_obj_.data(), "hoe");
  branchName_deltaEta_ = Form("%s_%s", branchName_obj_.data(), "eleDEta");
  branchName_deltaPhi_ = Form("%s_%s", branchName_obj_.data(), "eleDPhi");
  branchName_OoEminusOoP_ = Form("%s_%s", branchName_obj_.data(), "eInvMinusPInv");
  branchName_lostHits_ = Form("%s_%s", branchName_obj_.data(), "lostHits");
  branchName_conversionVeto_ = Form("%s_%s", branchName_obj_.data(), "convVeto");
}

void RecoElectronWriter::setBranches(TTree *tree)
{
  leptonWriter_->setBranches(tree);
  int max_nLeptons = leptonWriter_->max_nLeptons_;
  mvaRawPOG_GP_ = new Float_t[max_nLeptons];
  setBranch(tree, mvaRawPOG_GP_, branchName_mvaRawPOG_GP_, branchName_num_);
  mvaRawPOG_HZZ_ = new Float_t[max_nLeptons];
  setBranch(tree, mvaRawPOG_HZZ_, branchName_mvaRawPOG_HZZ_, branchName_num_);
  sigmaEtaEta_ = new Float_t[max_nLeptons];
  setBranch(tree, sigmaEtaEta_, branchName_sigmaEtaEta_, branchName_num_);
  HoE_ = new Float_t[max_nLeptons];
  setBranch(tree, HoE_, branchName_HoE_, branchName_num_);
  deltaEta_ = new Float_t[max_nLeptons];
  setBranch(tree, deltaEta_, branchName_deltaEta_, branchName_num_);
  deltaPhi_ = new Float_t[max_nLeptons];
  setBranch(tree, deltaPhi_, branchName_deltaPhi_, branchName_num_);
  OoEminusOoP_ = new Float_t[max_nLeptons];
  setBranch(tree, OoEminusOoP_, branchName_OoEminusOoP_, branchName_num_);
  lostHits_ = new UChar_t[max_nLeptons];
  setBranch(tree, lostHits_, branchName_lostHits_, branchName_num_);
  conversionVeto_ = new Bool_t[max_nLeptons];
  setBranch(tree, conversionVeto_, branchName_conversionVeto_, branchName_num_);
}

void RecoElectronWriter::write(const std::vector<const RecoElectron*>& leptons) 
{
  leptonWriter_->write(leptons);
  Int_t nLeptons = leptons.size();
  for ( Int_t idxLepton = 0; idxLepton < nLeptons; ++idxLepton ) {
    const RecoElectron* lepton = leptons[idxLepton];
    assert(lepton);
    mvaRawPOG_GP_[idxLepton] = lepton->mvaRawPOG_GP();
    mvaRawPOG_HZZ_[idxLepton] = lepton->mvaRawPOG_HZZ();
    sigmaEtaEta_[idxLepton] = lepton->sigmaEtaEta();
    HoE_[idxLepton] = lepton->HoE();
    deltaEta_[idxLepton] = lepton->deltaEta();
    deltaPhi_[idxLepton] = lepton->deltaPhi();
    OoEminusOoP_[idxLepton] = lepton->OoEminusOoP();
    lostHits_[idxLepton] = lepton->nLostHits(); 
    conversionVeto_[idxLepton] = lepton->passesConversionVeto();
  }
}
