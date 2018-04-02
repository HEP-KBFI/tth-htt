#include "tthAnalysis/HiggsToTauTau/interface/RecoElectronWriter.h" // RecoElectronWriter

#include "tthAnalysis/HiggsToTauTau/interface/RecoLeptonWriter.h" // RecoLeptonWriter
#include "tthAnalysis/HiggsToTauTau/interface/RecoElectron.h" // RecoElectron
#include "tthAnalysis/HiggsToTauTau/interface/BranchAddressInitializer.h" // BranchAddressInitializer, TTree, Form()

RecoElectronWriter::RecoElectronWriter(int era)
  : RecoElectronWriter(era, "Electron")
{}

RecoElectronWriter::RecoElectronWriter(int era,
                                       const std::string & branchName_obj)
  : RecoElectronWriter(era, Form("n%s", branchName_obj.data()), branchName_obj)
{}

RecoElectronWriter::RecoElectronWriter(int era,
                                       const std::string & branchName_num,
                                       const std::string & branchName_obj)
  : branchName_num_(branchName_num)
  , branchName_obj_(branchName_obj)
  , writeUncorrected_(false)
  , leptonWriter_(nullptr)
  , eCorr_(nullptr)
  , mvaRawPOG_(nullptr)
  , mvaRawPOG_WP80_(nullptr)
  , mvaRawPOG_WP90_(nullptr)
  , mvaRawPOG_WPL_(nullptr)
  , sigmaEtaEta_(nullptr)
  , HoE_(nullptr)
  , deltaEta_(nullptr)
  , deltaPhi_(nullptr)
  , OoEminusOoP_(nullptr)
  , lostHits_(nullptr)
  , conversionVeto_(nullptr)
  , cutbasedID_HLT_(nullptr)
{
  leptonWriter_ = new RecoLeptonWriter(branchName_obj_);
  setBranchNames();
}

RecoElectronWriter::~RecoElectronWriter()
{
  delete leptonWriter_;
  delete[] eCorr_;
  delete[] mvaRawPOG_;
  delete[] mvaRawPOG_WP80_;
  delete[] mvaRawPOG_WP90_;
  delete[] mvaRawPOG_WPL_;
  delete[] sigmaEtaEta_;
  delete[] HoE_;
  delete[] deltaEta_;
  delete[] deltaPhi_;
  delete[] OoEminusOoP_;
  delete[] lostHits_;
  delete[] conversionVeto_;
  delete[] cutbasedID_HLT_;
}

void
RecoElectronWriter::setBranchNames()
{
  const std::string mvaString = RecoElectron::useNoIso ? "mvaFall17noIso" : "mvaFall17Iso";
  branchName_eCorr_ = Form("%s_%s", branchName_obj_.data(), "eCorr");
  branchName_mvaRawPOG_ = Form("%s_%s", branchName_obj_.data(), mvaString.data());
  branchName_mvaRawPOG_WP80_ = Form("%s_%s", branchName_obj_.data(), Form("%s_WP80", mvaString.data()));
  branchName_mvaRawPOG_WP90_ = Form("%s_%s", branchName_obj_.data(), Form("%s_WP90", mvaString.data()));
  branchName_mvaRawPOG_WPL_ = Form("%s_%s", branchName_obj_.data(), Form("%s_WPL", mvaString.data()));
  branchName_sigmaEtaEta_ = Form("%s_%s", branchName_obj_.data(), "sieie");
  branchName_HoE_ = Form("%s_%s", branchName_obj_.data(), "hoe");
  branchName_deltaEta_ = Form("%s_%s", branchName_obj_.data(), "deltaEtaSC_trackatVtx");
  branchName_deltaPhi_ = Form("%s_%s", branchName_obj_.data(), "deltaPhiSC_trackatVtx");
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
  bai.setBranch(eCorr_, branchName_eCorr_);
  bai.setBranch(mvaRawPOG_, branchName_mvaRawPOG_);
  bai.setBranch(mvaRawPOG_WP80_, branchName_mvaRawPOG_WP80_);
  bai.setBranch(mvaRawPOG_WP90_, branchName_mvaRawPOG_WP90_);
  bai.setBranch(mvaRawPOG_WPL_, branchName_mvaRawPOG_WPL_);
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
    mvaRawPOG_[idxLepton] = lepton->mvaRawPOG();
    mvaRawPOG_WP80_[idxLepton] = lepton->mvaRawPOG_WP80();
    mvaRawPOG_WP90_[idxLepton] = lepton->mvaRawPOG_WP90();
    mvaRawPOG_WPL_[idxLepton] = lepton->mvaRawPOG_WPL();
    sigmaEtaEta_[idxLepton] = lepton->sigmaEtaEta();
    HoE_[idxLepton] = lepton->HoE();
    deltaEta_[idxLepton] = lepton->deltaEta();
    deltaPhi_[idxLepton] = lepton->deltaPhi();
    OoEminusOoP_[idxLepton] = lepton->OoEminusOoP();
    lostHits_[idxLepton] = lepton->nLostHits(); 
    conversionVeto_[idxLepton] = lepton->passesConversionVeto();
    cutbasedID_HLT_[idxLepton] = lepton->cutbasedID_HLT();
  }
}
