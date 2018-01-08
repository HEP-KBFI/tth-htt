#include "tthAnalysis/HiggsToTauTau/interface/RecoElectronWriter.h" // RecoElectronWriter

#include "tthAnalysis/HiggsToTauTau/interface/RecoLeptonWriter.h" // RecoLeptonWriter
#include "tthAnalysis/HiggsToTauTau/interface/RecoElectron.h" // RecoElectron
#include "tthAnalysis/HiggsToTauTau/interface/BranchAddressInitializer.h" // BranchAddressInitializer, TTree, Form()

RecoElectronWriter::RecoElectronWriter(int era)
  : RecoElectronWriter(era, "nElectron", "Electron")
{}

RecoElectronWriter::RecoElectronWriter(int era,
                                       const std::string & branchName_num,
                                       const std::string & branchName_obj)
  : branchName_num_(branchName_num)
  , branchName_obj_(branchName_obj)
  , leptonWriter_(nullptr)
  , mvaRawPOG_GP_(nullptr)
  , mvaRawPOG_HZZ_(nullptr)
  , sigmaEtaEta_(nullptr)
  , HoE_(nullptr)
  , deltaEta_(nullptr)
  , deltaPhi_(nullptr)
  , OoEminusOoP_(nullptr)
  , lostHits_(nullptr)
  , conversionVeto_(nullptr)
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
  unsigned int max_nLeptons = leptonWriter_->max_nLeptons_;
  BranchAddressInitializer bai(tree, max_nLeptons, branchName_num_);
  bai.setBranch(mvaRawPOG_GP_, branchName_mvaRawPOG_GP_);
  bai.setBranch(mvaRawPOG_HZZ_, branchName_mvaRawPOG_HZZ_);
  bai.setBranch(sigmaEtaEta_, branchName_sigmaEtaEta_);
  bai.setBranch(HoE_, branchName_HoE_);
  bai.setBranch(deltaEta_, branchName_deltaEta_);
  bai.setBranch(deltaPhi_, branchName_deltaPhi_);
  bai.setBranch(OoEminusOoP_, branchName_OoEminusOoP_);
  bai.setBranch(lostHits_, branchName_lostHits_);
  bai.setBranch(conversionVeto_, branchName_conversionVeto_);
}

void RecoElectronWriter::write(const std::vector<const RecoElectron *> & leptons)
{
  leptonWriter_->write(leptons);
  Int_t nLeptons = leptons.size();
  for(Int_t idxLepton = 0; idxLepton < nLeptons; ++idxLepton)
  {
    const RecoElectron * lepton = leptons[idxLepton];
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
