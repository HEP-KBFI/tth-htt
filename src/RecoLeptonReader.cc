#include "tthAnalysis/HiggsToTauTau/interface/RecoLeptonReader.h" // RecoLeptonReader

#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h" // cmsException()
#include "tthAnalysis/HiggsToTauTau/interface/BranchAddressInitializer.h" // BranchAddressInitializer, TTree, Form()

std::map<std::string, int> RecoLeptonReader::numInstances_;
std::map<std::string, RecoLeptonReader *> RecoLeptonReader::instances_;

RecoLeptonReader::RecoLeptonReader(bool readGenMatching)
  : RecoLeptonReader("Lepton", readGenMatching)
{}

RecoLeptonReader::RecoLeptonReader(const std::string & branchName_obj,
                                   bool readGenMatching)
  : max_nLeptons_(64)
  , branchName_num_(Form("n%s", branchName_obj.data()))
  , branchName_obj_(branchName_obj)
  , genLeptonReader_(nullptr)
  , genHadTauReader_(nullptr)
  , genPhotonReader_(nullptr)
  , genJetReader_(nullptr)
  , readGenMatching_(readGenMatching)
  , pt_(nullptr)
  , eta_(nullptr)
  , phi_(nullptr)
  , mass_(nullptr)
  , pdgId_(nullptr)
  , dxy_(nullptr)
  , dz_(nullptr)
  , relIso_all_(nullptr)
  , pfRelIso04_all_(nullptr)
  , absIso_chg_(nullptr)
  , absIso_neu_(nullptr)
  , sip3d_(nullptr)
  , mvaRawTTH_(nullptr)
  , jetPtRatio_(nullptr)
  , jetPtRel_(nullptr)
  , jetBtagCSV_(nullptr)
  , jetNDauChargedMVASel_(nullptr)
  , tightCharge_(nullptr)
  , charge_(nullptr)
  , filterBits_(nullptr)
{
  if(readGenMatching_)
  {
    genLeptonReader_ = new GenLeptonReader(Form("%s_genLepton", branchName_obj_.data()), max_nLeptons_);
    genHadTauReader_ = new GenHadTauReader(Form("%s_genTau",    branchName_obj_.data()), max_nLeptons_);
    genPhotonReader_ = new GenPhotonReader(Form("%s_genPhoton", branchName_obj_.data()), max_nLeptons_);
    genJetReader_    = new GenJetReader   (Form("%s_genJet",    branchName_obj_.data()), max_nLeptons_);
  }
  setBranchNames();
}

RecoLeptonReader::~RecoLeptonReader()
{
  --numInstances_[branchName_obj_];
  assert(numInstances_[branchName_obj_] >= 0);

  if(numInstances_[branchName_obj_] == 0)
  {
    RecoLeptonReader * const gInstance = instances_[branchName_obj_];
    assert(gInstance);
    delete gInstance->genLeptonReader_;
    delete gInstance->genHadTauReader_;
    delete gInstance->genPhotonReader_;
    delete gInstance->genJetReader_;
    delete[] gInstance->pt_;
    delete[] gInstance->eta_;
    delete[] gInstance->phi_;
    delete[] gInstance->mass_;
    delete[] gInstance->pdgId_;
    delete[] gInstance->dxy_;
    delete[] gInstance->dz_;
    delete[] gInstance->relIso_all_;
    delete[] gInstance->pfRelIso04_all_;
    delete[] gInstance->absIso_chg_;
    delete[] gInstance->absIso_neu_;
    delete[] gInstance->sip3d_;
    delete[] gInstance->mvaRawTTH_;
    delete[] gInstance->jetPtRatio_;
    delete[] gInstance->jetPtRel_;
    delete[] gInstance->jetBtagCSV_;
    delete[] gInstance->jetNDauChargedMVASel_;
    delete[] gInstance->tightCharge_;
    delete[] gInstance->charge_;
    delete[] gInstance->filterBits_;
    instances_[branchName_obj_] = nullptr;
  }
}

void
RecoLeptonReader::setBranchNames()
{
  if(numInstances_[branchName_obj_] == 0)
  {
    branchName_pt_ = Form("%s_%s", branchName_obj_.data(), "pt");
    branchName_eta_ = Form("%s_%s", branchName_obj_.data(), "eta");
    branchName_phi_ = Form("%s_%s", branchName_obj_.data(), "phi");
    branchName_mass_ = Form("%s_%s", branchName_obj_.data(), "mass");
    branchName_pdgId_ = Form("%s_%s", branchName_obj_.data(), "pdgId");
    branchName_dxy_ = Form("%s_%s", branchName_obj_.data(), "dxy");
    branchName_dz_ = Form("%s_%s", branchName_obj_.data(), "dz");
    branchName_relIso_all_ = Form("%s_%s", branchName_obj_.data(), "miniPFRelIso_all");
    branchName_pfRelIso04_all_ = Form("%s_%s", branchName_obj_.data(), "pfRelIso04_all");
    branchName_absIso_chg_ = Form("%s_%s", branchName_obj_.data(), "miniPFAbsIso_chg");
    branchName_absIso_neu_ = Form("%s_%s", branchName_obj_.data(), "miniPFAbsIso_neu");
    branchName_sip3d_ = Form("%s_%s", branchName_obj_.data(), "sip3d");
    branchName_mvaRawTTH_ = Form("%s_%s", branchName_obj_.data(), "mvaTTH");
    branchName_jetPtRatio_ = Form("%s_%s", branchName_obj_.data(), "jetPtRatio_TTHMVA");
    branchName_jetPtRel_ = Form("%s_%s", branchName_obj_.data(), "jetPtRelv2_TTHMVA");
    branchName_jetNDauChargedMVASel_ = Form("%s_%s", branchName_obj_.data(), "jetNDauChargedMVASel");
    branchName_jetBtagCSV_ = Form("%s_%s", branchName_obj_.data(), "jetBTagDeepCSV_TTHMVA");
    branchName_tightCharge_ = Form("%s_%s", branchName_obj_.data(), "tightCharge");
    branchName_charge_ = Form("%s_%s", branchName_obj_.data(), "charge");
    branchName_filterBits_ = Form("%s_%s", branchName_obj_.data(), "filterBits");
    instances_[branchName_obj_] = this;
  }
  else
  {
    if(branchName_num_ != instances_[branchName_obj_]->branchName_num_)
    {
      throw cmsException(this)
        << "Association between configuration parameters 'branchName_num' and 'branchName_obj' must be unique:"
        << " present association 'branchName_num' = " << branchName_num_ << " with 'branchName_obj' = " << branchName_obj_
        << " does not match previous association 'branchName_num' = " << instances_[branchName_obj_]->branchName_num_
        << " with 'branchName_obj' = " << instances_[branchName_obj_]->branchName_obj_ << " !!\n";
    }
  }
  ++numInstances_[branchName_obj_];
}

void
RecoLeptonReader::setBranchAddresses(TTree * tree)
{
  if(instances_[branchName_obj_] == this)
  {
    if(readGenMatching_)
    {
      genLeptonReader_->setBranchAddresses(tree);
      genHadTauReader_->setBranchAddresses(tree);
      genPhotonReader_->setBranchAddresses(tree);
      genJetReader_->setBranchAddresses(tree);
    }
    BranchAddressInitializer bai(tree, max_nLeptons_);
    bai.setBranchAddress(nLeptons_, branchName_num_);
    bai.setBranchAddress(pt_, branchName_pt_);
    bai.setBranchAddress(eta_, branchName_eta_);
    bai.setBranchAddress(phi_, branchName_phi_);
    bai.setBranchAddress(mass_, branchName_mass_);
    bai.setBranchAddress(pdgId_, branchName_pdgId_);
    bai.setBranchAddress(dxy_, branchName_dxy_);
    bai.setBranchAddress(dz_, branchName_dz_);
    bai.setBranchAddress(pfRelIso04_all_, branchName_pfRelIso04_all_);
    bai.setBranchAddress(relIso_all_, branchName_relIso_all_);
    bai.setBranchAddress(absIso_chg_, branchName_absIso_chg_);
    bai.setBranchAddress(absIso_neu_, branchName_absIso_neu_);
    bai.setBranchAddress(sip3d_, branchName_sip3d_);
    bai.setBranchAddress(mvaRawTTH_, branchName_mvaRawTTH_);
    bai.setBranchAddress(jetPtRatio_, branchName_jetPtRatio_);
    bai.setBranchAddress(jetPtRel_, branchName_jetPtRel_, -1.);
    bai.setBranchAddress(jetBtagCSV_, branchName_jetBtagCSV_);
    bai.setBranchAddress(jetNDauChargedMVASel_, branchName_jetNDauChargedMVASel_, -1);
    bai.setBranchAddress(tightCharge_, branchName_tightCharge_);
    bai.setBranchAddress(charge_, branchName_charge_);
    bai.setBranchAddress(filterBits_, branchName_filterBits_);
  }
}
