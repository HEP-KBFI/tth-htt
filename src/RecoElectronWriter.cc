#include "tthAnalysis/HiggsToTauTau/interface/RecoElectronWriter.h"

#include "tthAnalysis/HiggsToTauTau/interface/RecoLeptonWriter.h"         // RecoLeptonWriter
#include "tthAnalysis/HiggsToTauTau/interface/RecoElectron.h"             // RecoElectron
#include "tthAnalysis/HiggsToTauTau/interface/BranchAddressInitializer.h" // BranchAddressInitializer, TTree, Form()
#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h"     // Era::k*

RecoElectronWriter::RecoElectronWriter(Era era,
                                       bool isMC)
  : RecoElectronWriter(era, isMC, "Electron")
{}

RecoElectronWriter::RecoElectronWriter(Era era,
                                       bool isMC,
                                       const std::string & branchName_obj)
  : RecoElectronWriter(era, isMC, Form("n%s", branchName_obj.data()), branchName_obj)
{}

RecoElectronWriter::RecoElectronWriter(Era era,
                                       bool isMC,
                                       const std::string & branchName_num,
                                       const std::string & branchName_obj)
  : era_(era)
  , branchName_num_(branchName_num)
  , branchName_obj_(branchName_obj)
  , writeUncorrected_(false)
  , leptonWriter_(nullptr)
  , eCorr_(nullptr)
  , sigmaEtaEta_(nullptr)
  , HoE_(nullptr)
  , deltaEta_(nullptr)
  , deltaPhi_(nullptr)
  , OoEminusOoP_(nullptr)
  , lostHits_(nullptr)
  , conversionVeto_(nullptr)
  , cutbasedID_HLT_(nullptr)
{
  leptonWriter_ = new RecoLeptonWriter(era, isMC, branchName_obj_);
  setBranchNames();
}

RecoElectronWriter::~RecoElectronWriter()
{
  delete leptonWriter_;
  delete[] eCorr_;
  delete[] sigmaEtaEta_;
  delete[] HoE_;
  delete[] deltaEta_;
  delete[] deltaPhi_;
  delete[] OoEminusOoP_;
  delete[] lostHits_;
  delete[] conversionVeto_;
  delete[] cutbasedID_HLT_;

  for(auto & kv: rawMVAs_POG_)
  {
    delete[] kv.second;
  }
  for(auto & kv: mvaIDs_POG_)
  {
    for(auto & kw: kv.second)
    {
      delete[] kw.second;
    }
  }
}

void
RecoElectronWriter::setBranchNames()
{
  for(const auto & EGammaID_choice: EGammaID_map)
  {
    branchNames_mvaRaw_POG_[EGammaID_choice.first] = Form(
      "%s_%s", branchName_obj_.data(), EGammaID_choice.second.data()
    );
    branchNames_mvaID_POG_[EGammaID_choice.first] = {};
    for(const auto & EGammaWP_choice: EGammaWP_map)
    {
      branchNames_mvaID_POG_[EGammaID_choice.first][EGammaWP_choice.first] = Form(
        "%s_%s", branchNames_mvaRaw_POG_[EGammaID_choice.first].data(), EGammaWP_choice.second.data()
      );
    }
  }

  branchName_eCorr_ = Form("%s_%s", branchName_obj_.data(), "eCorr");
  branchName_sigmaEtaEta_ = Form("%s_%s", branchName_obj_.data(), "sieie");
  branchName_HoE_ = Form("%s_%s", branchName_obj_.data(), "hoe");
  branchName_deltaEta_ = Form("%s_%s", branchName_obj_.data(), "deltaEtaSC");
  branchName_deltaPhi_ = Form("%s_%s", branchName_obj_.data(), "deltaPhiSC");
  branchName_OoEminusOoP_ = Form("%s_%s", branchName_obj_.data(), "eInvMinusPInv");
  branchName_lostHits_ = Form("%s_%s", branchName_obj_.data(), "lostHits");
  branchName_conversionVeto_ = Form("%s_%s", branchName_obj_.data(), "convVeto");
  branchName_cutbasedID_HLT_ = Form("%s_%s", branchName_obj_.data(), "cutBased_HLTPreSel");
}

void
RecoElectronWriter::setBranches(TTree * tree)
{
  leptonWriter_->setBranches(tree);
  unsigned int max_nLeptons = leptonWriter_->max_nLeptons_;
  BranchAddressInitializer bai(tree, max_nLeptons, branchName_num_);
  for(const auto & EGammaID_choice: EGammaID_map)
  {
    bai.setBranch(rawMVAs_POG_[EGammaID_choice.first], branchNames_mvaRaw_POG_[EGammaID_choice.first]);
    mvaIDs_POG_[EGammaID_choice.first] = {};
    for(const auto & EGammaWP_choice: EGammaWP_map)
    {
      bai.setBranch(
        mvaIDs_POG_           [EGammaID_choice.first][EGammaWP_choice.first],
        branchNames_mvaID_POG_[EGammaID_choice.first][EGammaWP_choice.first]
      );
    }
  }
  bai.setBranch(eCorr_, branchName_eCorr_);
  bai.setBranch(sigmaEtaEta_, branchName_sigmaEtaEta_);
  bai.setBranch(HoE_, branchName_HoE_);
  bai.setBranch(deltaEta_, branchName_deltaEta_);
  bai.setBranch(deltaPhi_, branchName_deltaPhi_);
  bai.setBranch(OoEminusOoP_, branchName_OoEminusOoP_);
  bai.setBranch(lostHits_, branchName_lostHits_);
  bai.setBranch(conversionVeto_, branchName_conversionVeto_);
  bai.setBranch(cutbasedID_HLT_, branchName_cutbasedID_HLT_);
}

void
RecoElectronWriter::writeUncorrected(bool flag)
{
  writeUncorrected_ = flag;
}

void
RecoElectronWriter::write(const std::vector<const RecoElectron *> & leptons)
{
  Int_t nLeptons = leptons.size();
  if(writeUncorrected_)
  {
    Double_t * eCorr = new Double_t[nLeptons];
    std::transform(
      leptons.begin(), leptons.end(), eCorr,
      [](const RecoElectron * lepton) -> Double_t
      {
        return lepton->eCorr();
      }
    );
    leptonWriter_->write(leptons, eCorr);
    delete eCorr;
  }
  else
  {
    leptonWriter_->write(leptons);
  }
  for(Int_t idxLepton = 0; idxLepton < nLeptons; ++idxLepton)
  {
    const RecoElectron * lepton = leptons[idxLepton];
    assert(lepton);
    eCorr_[idxLepton] = lepton->eCorr();
    sigmaEtaEta_[idxLepton] = lepton->sigmaEtaEta();
    HoE_[idxLepton] = lepton->HoE();
    deltaEta_[idxLepton] = lepton->deltaEta();
    deltaPhi_[idxLepton] = lepton->deltaPhi();
    OoEminusOoP_[idxLepton] = lepton->OoEminusOoP();
    lostHits_[idxLepton] = lepton->nLostHits(); 
    conversionVeto_[idxLepton] = lepton->passesConversionVeto();
    cutbasedID_HLT_[idxLepton] = lepton->cutbasedID_HLT();
    for(const auto & EGammaID_choice: branchNames_mvaRaw_POG_)
    {
      rawMVAs_POG_[EGammaID_choice.first][idxLepton] = lepton->mvaRaw_POG(EGammaID_choice.first);
    }
    for(const auto & EGammaID_choice: branchNames_mvaID_POG_)
    {
      for(const auto & EGammaWP_choice: EGammaID_choice.second)
      {
        mvaIDs_POG_[EGammaID_choice.first][EGammaWP_choice.first][idxLepton] =
          lepton->mvaID_POG(EGammaID_choice.first, EGammaWP_choice.first)
        ;
      }
    }
  }
}
