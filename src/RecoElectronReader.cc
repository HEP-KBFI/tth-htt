#include "tthAnalysis/HiggsToTauTau/interface/RecoElectronReader.h" // RecoElectronReader

#include "tthAnalysis/HiggsToTauTau/interface/RecoLeptonReader.h" // RecoLeptonReader
#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // setValue_float()
#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h" // cmsException()

#include <TString.h> // Form()
#include <TTree.h> // TTree

std::map<std::string, int> RecoElectronReader::numInstances_;
std::map<std::string, RecoElectronReader *> RecoElectronReader::instances_;

RecoElectronReader::RecoElectronReader(int era,
                                       bool readGenMatching)
  : RecoElectronReader(era, "nselLeptons", "selLeptons", readGenMatching)
{}

RecoElectronReader::RecoElectronReader(int era,
                                       const std::string & branchName_num,
                                       const std::string & branchName_obj,
                                       bool readGenMatching)
  : branchName_num_(branchName_num)
  , branchName_obj_(branchName_obj)
  , leptonReader_( new RecoLeptonReader(branchName_num_, branchName_obj_, readGenMatching))
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
  setBranchNames();
}

RecoElectronReader::~RecoElectronReader()
{
  delete leptonReader_;
  leptonReader_ = 0;
  --numInstances_[branchName_obj_];
  assert(numInstances_[branchName_obj_] >= 0);

  if(numInstances_[branchName_obj_] == 0)
  {
    RecoElectronReader * const gInstance = instances_[branchName_obj_];
    assert(gInstance);
    delete[] gInstance->mvaRawPOG_GP_;
    delete[] gInstance->mvaRawPOG_HZZ_;
    delete[] gInstance->sigmaEtaEta_;
    delete[] gInstance->HoE_;
    delete[] gInstance->deltaEta_;
    delete[] gInstance->deltaPhi_;
    delete[] gInstance->OoEminusOoP_;
    delete[] gInstance->lostHits_;
    delete[] gInstance->conversionVeto_;
    instances_[branchName_obj_] = nullptr;
  }
}

void
RecoElectronReader::setBranchNames()
{
  if (numInstances_[branchName_obj_] == 0)
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
    instances_[branchName_obj_] = this;
  }
  else
  {
    if ( branchName_num_ != instances_[branchName_obj_]->branchName_num_)
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
RecoElectronReader::setBranchAddresses(TTree * tree)
{
  if(instances_[branchName_obj_] == this)
  {
    leptonReader_->setBranchAddresses(tree);
    unsigned int max_nLeptons = leptonReader_->max_nLeptons_;
    mvaRawPOG_GP_ = new Float_t[max_nLeptons];
    tree->SetBranchAddress(branchName_mvaRawPOG_GP_.data(), mvaRawPOG_GP_);
    mvaRawPOG_HZZ_ = new Float_t[max_nLeptons];
    tree->SetBranchAddress(branchName_mvaRawPOG_HZZ_.data(), mvaRawPOG_HZZ_);
    sigmaEtaEta_ = new Float_t[max_nLeptons];
    tree->SetBranchAddress(branchName_sigmaEtaEta_.data(), sigmaEtaEta_);
    HoE_ = new Float_t[max_nLeptons];
    tree->SetBranchAddress(branchName_HoE_.data(), HoE_);
//--- Karl: ECAL-related variables missing in nanoAOD
    deltaEta_ = new Float_t[max_nLeptons];
    setValue_float(deltaEta_, max_nLeptons, 0.);
    deltaPhi_ = new Float_t[max_nLeptons];
    setValue_float(deltaPhi_, max_nLeptons, 0.);
//--- end
    OoEminusOoP_ = new Float_t[max_nLeptons];
    tree->SetBranchAddress(branchName_OoEminusOoP_.data(), OoEminusOoP_);
    lostHits_ = new UChar_t[max_nLeptons];
    tree->SetBranchAddress(branchName_lostHits_.data(), lostHits_);
    conversionVeto_ = new Bool_t[max_nLeptons];
    tree->SetBranchAddress(branchName_conversionVeto_.data(), conversionVeto_);
  }
}

std::vector<RecoElectron>
RecoElectronReader::read() const
{
  const RecoLeptonReader * const gLeptonReader = leptonReader_->instances_[branchName_obj_];
  assert(gLeptonReader);
  const RecoElectronReader * const gElectronReader = instances_[branchName_obj_];
  assert(gElectronReader);
  std::vector<RecoElectron> electrons;

  const UInt_t nLeptons = gLeptonReader->nLeptons_;
  if(nLeptons > leptonReader_->max_nLeptons_)
  {
    throw cmsException(this)
      << "Number of leptons stored in Ntuple = " << nLeptons << ", exceeds max_nLeptons = "
      << leptonReader_->max_nLeptons_ << " !!\n";
  }

  if (nLeptons > 0)
  {
    electrons.reserve(nLeptons);
    for(UInt_t idxLepton = 0; idxLepton < nLeptons; ++idxLepton)
    {
      if(std::abs(gLeptonReader->pdgId_[idxLepton]) == 11)
      {
        electrons.push_back({
          gLeptonReader->pt_[idxLepton],
          gLeptonReader->eta_[idxLepton],
          gLeptonReader->phi_[idxLepton],
          gLeptonReader->mass_[idxLepton],
          gLeptonReader->pdgId_[idxLepton],
          gLeptonReader->dxy_[idxLepton],
          gLeptonReader->dz_[idxLepton],
          gLeptonReader->relIso_all_[idxLepton],
          gLeptonReader->hadRelIso03_chg_[idxLepton],
          gLeptonReader->absIso_chg_[idxLepton],
          gLeptonReader->absIso_neu_[idxLepton],
          gLeptonReader->sip3d_[idxLepton],
          gLeptonReader->mvaRawTTH_[idxLepton],
          gLeptonReader->jetPtRatio_[idxLepton],
          gLeptonReader->jetBtagCSV_[idxLepton],
          gLeptonReader->tightCharge_[idxLepton],
          gLeptonReader->charge_[idxLepton],
          gElectronReader->mvaRawPOG_GP_[idxLepton],
          gElectronReader->mvaRawPOG_HZZ_[idxLepton],
          gElectronReader->sigmaEtaEta_[idxLepton],
          gElectronReader->HoE_[idxLepton],
          gElectronReader->deltaEta_[idxLepton],
          gElectronReader->deltaPhi_[idxLepton],
          gElectronReader->OoEminusOoP_[idxLepton],
          gElectronReader->lostHits_[idxLepton],
          gElectronReader->conversionVeto_[idxLepton]
        });
      }
    }
    gLeptonReader->readGenMatching(electrons);
  }
  return electrons;
}
