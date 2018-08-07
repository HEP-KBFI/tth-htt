#include "tthAnalysis/HiggsToTauTau/interface/RecoElectronReader.h" // RecoElectronReader

#include "tthAnalysis/HiggsToTauTau/interface/RecoLeptonReader.h" // RecoLeptonReader
#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // setValue_float()
#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h" // cmsException()
#include "tthAnalysis/HiggsToTauTau/interface/BranchAddressInitializer.h" // BranchAddressInitializer, TTree, Form()
#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // kEra_*

std::map<std::string, int> RecoElectronReader::numInstances_;
std::map<std::string, RecoElectronReader *> RecoElectronReader::instances_;

RecoElectronReader::RecoElectronReader(int era,
                                       bool readGenMatching)
  : RecoElectronReader(era, "Electron", readGenMatching)
{}

RecoElectronReader::RecoElectronReader(int era,
                                       const std::string & branchName_obj,
                                       bool readGenMatching)
  : era_(era)
  , branchName_num_(Form("n%s", branchName_obj.data()))
  , branchName_obj_(branchName_obj)
  , readUncorrected_(false)
  , leptonReader_(new RecoLeptonReader(branchName_obj_, readGenMatching))
  , eCorr_(nullptr)
  , mvaRaw_POG_(nullptr)
  , mvaID_POG_(nullptr)
  , sigmaEtaEta_(nullptr)
  , HoE_(nullptr)
  , deltaEta_(nullptr)
  , deltaPhi_(nullptr)
  , OoEminusOoP_(nullptr)
  , lostHits_(nullptr)
  , conversionVeto_(nullptr)
  , cutbasedID_HLT_(nullptr)
{
  setBranchNames();
}

RecoElectronReader::~RecoElectronReader()
{
  --numInstances_[branchName_obj_];
  assert(numInstances_[branchName_obj_] >= 0);

  if(numInstances_[branchName_obj_] == 0)
  {
    RecoElectronReader * const gInstance = instances_[branchName_obj_];
    assert(gInstance);
    delete gInstance->leptonReader_;
    delete[] gInstance->eCorr_;
    delete[] gInstance->mvaRaw_POG_;
    delete[] gInstance->mvaID_POG_;
    delete[] gInstance->sigmaEtaEta_;
    delete[] gInstance->HoE_;
    delete[] gInstance->deltaEta_;
    delete[] gInstance->deltaPhi_;
    delete[] gInstance->OoEminusOoP_;
    delete[] gInstance->lostHits_;
    delete[] gInstance->conversionVeto_;
    delete[] gInstance->cutbasedID_HLT_;
    instances_[branchName_obj_] = nullptr;
  }
}

void
RecoElectronReader::setBranchNames()
{
  if (numInstances_[branchName_obj_] == 0)
  {
    branchName_eCorr_ = Form("%s_%s", branchName_obj_.data(), "eCorr");
    std::string mvaString;
    switch(era_)
    {
      case kEra_2016: mvaString = "mvaSpring16";                                              break;
      case kEra_2017: mvaString = RecoElectron::useNoIso ? "mvaFall17noIso" : "mvaFall17Iso"; break;
      default:        throw cmsException(this, __func__, __LINE__) << "Invalid era: " << era_;
    }
    branchName_mvaRaw_POG_ = Form("%s_%s", branchName_obj_.data(), mvaString.data());
    branchName_mvaID_POG_ = Form("%s_%s", branchName_obj_.data(), Form("%s_WPL", mvaString.data()));
    branchName_sigmaEtaEta_ = Form("%s_%s", branchName_obj_.data(), "sieie");
    branchName_HoE_ = Form("%s_%s", branchName_obj_.data(), "hoe");
    branchName_deltaEta_ = Form("%s_%s", branchName_obj_.data(), "deltaEtaSC_trackatVtx");
    branchName_deltaPhi_ = Form("%s_%s", branchName_obj_.data(), "deltaPhiSC_trackatVtx");
    branchName_OoEminusOoP_ = Form("%s_%s", branchName_obj_.data(), "eInvMinusPInv");
    branchName_lostHits_ = Form("%s_%s", branchName_obj_.data(), "lostHits");
    branchName_conversionVeto_ = Form("%s_%s", branchName_obj_.data(), "convVeto");
    branchName_cutbasedID_HLT_ = Form("%s_%s", branchName_obj_.data(), "cutBased_HLTPreSel");
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
RecoElectronReader::setBranchAddresses(TTree * tree)
{
  if(instances_[branchName_obj_] == this)
  {
    leptonReader_->setBranchAddresses(tree);
    const unsigned int max_nLeptons = leptonReader_->max_nLeptons_;

    BranchAddressInitializer bai(tree, max_nLeptons);
    bai.setBranchAddress(eCorr_, branchName_eCorr_);
    bai.setBranchAddress(mvaRaw_POG_, branchName_mvaRaw_POG_);
    bai.setBranchAddress(mvaID_POG_, branchName_mvaID_POG_);
    bai.setBranchAddress(sigmaEtaEta_, branchName_sigmaEtaEta_);
    bai.setBranchAddress(HoE_, branchName_HoE_);
    bai.setBranchAddress(deltaEta_, branchName_deltaEta_);
    bai.setBranchAddress(deltaPhi_, branchName_deltaPhi_);
    bai.setBranchAddress(OoEminusOoP_, branchName_OoEminusOoP_);
    bai.setBranchAddress(lostHits_, branchName_lostHits_);
    bai.setBranchAddress(conversionVeto_, branchName_conversionVeto_);
    bai.setBranchAddress(cutbasedID_HLT_, ""); // no safe HLT selection, yet
  }
}

void
RecoElectronReader::readUncorrected(bool flag)
{
  readUncorrected_ = flag;
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
        // Karl: For *some* leptons that don't have an associated jet,
        //       the deepCSV score is nan (and not -1) for an unknown reason.
        //       Adding a safeguard for these instances.
        const double jetBtagCSV = gLeptonReader->jetBtagCSV_[idxLepton];
        const double ptCorr = readUncorrected_ ? gElectronReader->eCorr_[idxLepton] : 1.;
        electrons.push_back({
          {
            {
              gLeptonReader->pt_[idxLepton] / ptCorr,
              gLeptonReader->eta_[idxLepton],
              gLeptonReader->phi_[idxLepton],
              gLeptonReader->mass_[idxLepton],
              gLeptonReader->pdgId_[idxLepton]
            },
            gLeptonReader->dxy_[idxLepton],
            gLeptonReader->dz_[idxLepton],
            gLeptonReader->relIso_all_[idxLepton],
            gLeptonReader->pfRelIso04_all_[idxLepton],
            gLeptonReader->absIso_chg_[idxLepton],
            gLeptonReader->absIso_neu_[idxLepton],
            gLeptonReader->sip3d_[idxLepton],
            gLeptonReader->mvaRawTTH_[idxLepton],
            gLeptonReader->jetPtRatio_[idxLepton],
            gLeptonReader->jetPtRel_[idxLepton],
            std::isnan(jetBtagCSV) ? -1. : jetBtagCSV,
            gLeptonReader->jetNDauChargedMVASel_[idxLepton],
            gLeptonReader->tightCharge_[idxLepton],
            gLeptonReader->charge_[idxLepton],
            gLeptonReader->filterBits_[idxLepton]
          },
          gElectronReader->eCorr_[idxLepton],
          gElectronReader->mvaRaw_POG_[idxLepton],
          gElectronReader->mvaID_POG_[idxLepton],
          gElectronReader->sigmaEtaEta_[idxLepton],
          gElectronReader->HoE_[idxLepton],
          gElectronReader->deltaEta_[idxLepton],
          gElectronReader->deltaPhi_[idxLepton],
          gElectronReader->OoEminusOoP_[idxLepton],
          gElectronReader->lostHits_[idxLepton],
          gElectronReader->conversionVeto_[idxLepton],
          gElectronReader->cutbasedID_HLT_[idxLepton]
        });
      }
    }
    gLeptonReader->readGenMatching(electrons);
  }
  return electrons;
}
