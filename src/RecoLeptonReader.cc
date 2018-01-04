#include "tthAnalysis/HiggsToTauTau/interface/RecoLeptonReader.h" // RecoLeptonReader

#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h" // cmsException()

#include <TString.h> // Form()
#include <TTree.h> // TTree

std::map<std::string, int> RecoLeptonReader::numInstances_;
std::map<std::string, RecoLeptonReader *> RecoLeptonReader::instances_;

RecoLeptonReader::RecoLeptonReader(bool readGenMatching)
  : RecoLeptonReader("nLepton", "Lepton", readGenMatching)
{}

RecoLeptonReader::RecoLeptonReader(const std::string & branchName_num,
                                   const std::string & branchName_obj,
                                   bool readGenMatching)
  : max_nLeptons_(32)
  , branchName_num_(branchName_num)
  , branchName_obj_(branchName_obj)
  , genLeptonReader_(nullptr)
  , genHadTauReader_(nullptr)
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
  , hadRelIso03_chg_(nullptr)
  , absIso_chg_(nullptr)
  , absIso_neu_(nullptr)
  , sip3d_(nullptr)
  , mvaRawTTH_(nullptr)
  , jetPtRatio_(nullptr)
  , jetBtagCSV_(nullptr)
  , tightCharge_(nullptr)
  , charge_(nullptr)
{
  if(readGenMatching_)
  {
    genLeptonReader_ = new GenLeptonReader(Form("%s_genLepton", branchName_num_.data()), Form("%s_genLepton", branchName_obj_.data()));
    genHadTauReader_ = new GenHadTauReader(Form("%s_genTau",    branchName_num_.data()), Form("%s_genTau",    branchName_obj_.data()));
    genJetReader_    = new GenJetReader   (Form("%s_genJet",    branchName_num_.data()), Form("%s_genJet",    branchName_obj_.data()));
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
    delete gInstance->genJetReader_;
    delete gInstance->pt_;
    delete gInstance->eta_;
    delete gInstance->phi_;
    delete gInstance->mass_;
    delete gInstance->pdgId_;
    delete gInstance->dxy_;
    delete gInstance->dz_;
    delete gInstance->relIso_all_;
    delete gInstance->hadRelIso03_chg_;
    delete gInstance->absIso_chg_;
    delete gInstance->absIso_neu_;
    delete gInstance->sip3d_;
    delete gInstance->mvaRawTTH_;
    delete gInstance->jetPtRatio_;
    delete gInstance->jetBtagCSV_;
    delete gInstance->tightCharge_;
    delete gInstance->charge_;
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
    branchName_hadRelIso03_chg_ = Form("%s_%s", branchName_obj_.data(), "pfRelIso03_chg");
    branchName_absIso_chg_ = Form("%s_%s", branchName_obj_.data(), "miniPFAbsIso_chg");
    branchName_absIso_neu_ = Form("%s_%s", branchName_obj_.data(), "miniPFAbsIso_neu");
    branchName_sip3d_ = Form("%s_%s", branchName_obj_.data(), "sip3d");
    branchName_mvaRawTTH_ = Form("%s_%s", branchName_obj_.data(), "mvaTTH");
    branchName_jetPtRatio_ = Form("%s_%s", branchName_obj_.data(), "jetPtRatio");
    branchName_jetBtagCSV_ = Form("%s_%s", branchName_obj_.data(), "jetBtag_csvv2");
    branchName_tightCharge_ = Form("%s_%s", branchName_obj_.data(), "tightCharge");
    branchName_charge_ = Form("%s_%s", branchName_obj_.data(), "charge");
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
      genJetReader_->setBranchAddresses(tree);  
    }
    tree->SetBranchAddress(branchName_num_.data(), &nLeptons_);
    pt_ = new Float_t[max_nLeptons_];
    tree->SetBranchAddress(branchName_pt_.data(), pt_);
    eta_ = new Float_t[max_nLeptons_];
    tree->SetBranchAddress(branchName_eta_.data(), eta_);
    phi_ = new Float_t[max_nLeptons_];
    tree->SetBranchAddress(branchName_phi_.data(), phi_);
    mass_ = new Float_t[max_nLeptons_];
    tree->SetBranchAddress(branchName_mass_.data(), mass_);
    pdgId_ = new Int_t[max_nLeptons_];
    tree->SetBranchAddress(branchName_pdgId_.data(), pdgId_);
    dxy_ = new Float_t[max_nLeptons_];
    tree->SetBranchAddress(branchName_dxy_.data(), dxy_);
    dz_ = new Float_t[max_nLeptons_];
    tree->SetBranchAddress(branchName_dz_.data(), dz_);
    hadRelIso03_chg_ = new Float_t[max_nLeptons_];
    tree->SetBranchAddress(branchName_hadRelIso03_chg_.data(), hadRelIso03_chg_);
    relIso_all_ = new Float_t[max_nLeptons_];
    tree->SetBranchAddress(branchName_relIso_all_.data(), relIso_all_);
    absIso_chg_ = new Float_t[max_nLeptons_];
    tree->SetBranchAddress(branchName_absIso_chg_.data(), absIso_chg_);
    absIso_neu_ = new Float_t[max_nLeptons_];
    tree->SetBranchAddress(branchName_absIso_neu_.data(), absIso_neu_);
    sip3d_ = new Float_t[max_nLeptons_];
    tree->SetBranchAddress(branchName_sip3d_.data(), sip3d_);
    mvaRawTTH_ = new Float_t[max_nLeptons_];
    tree->SetBranchAddress(branchName_mvaRawTTH_.data(), mvaRawTTH_);
    jetPtRatio_ = new Float_t[max_nLeptons_];
    tree->SetBranchAddress(branchName_jetPtRatio_.data(), jetPtRatio_);
    jetBtagCSV_ = new Float_t[max_nLeptons_];
    tree->SetBranchAddress(branchName_jetBtagCSV_.data(), jetBtagCSV_);
    tightCharge_ = new Int_t[max_nLeptons_];
    tree->SetBranchAddress(branchName_tightCharge_.data(), tightCharge_);
    charge_ = new Int_t[max_nLeptons_];
    tree->SetBranchAddress(branchName_charge_.data(), charge_);
  }
}

