#include "tthAnalysis/HiggsToTauTau/interface/RecoElectronReader.h" // RecoElectronReader

#include "tthAnalysis/HiggsToTauTau/interface/RecoLeptonReader.h" // RecoLeptonReader
#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // setValue_float()
#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h" // cmsException()
#include "tthAnalysis/HiggsToTauTau/interface/BranchAddressInitializer.h" // BranchAddressInitializer, TTree, Form()
#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // kEra_*

std::map<std::string, int> RecoElectronReader::numInstances_;
std::map<std::string, RecoElectronReader *> RecoElectronReader::instances_;

RecoElectronReader::RecoElectronReader(int era,
                                       bool isMC,
                                       bool readGenMatching)
  : RecoElectronReader(era, "Electron", isMC, readGenMatching)
{}

RecoElectronReader::RecoElectronReader(int era,
                                       const std::string & branchName_obj,
                                       bool isMC,
                                       bool readGenMatching)
  : era_(era)
  , branchName_num_(Form("n%s", branchName_obj.data()))
  , branchName_obj_(branchName_obj)
  , readUncorrected_(false)
  , leptonReader_(new RecoLeptonReader(branchName_obj_, isMC, readGenMatching))
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
    delete[] gInstance->sigmaEtaEta_;
    delete[] gInstance->HoE_;
    delete[] gInstance->deltaEta_;
    delete[] gInstance->deltaPhi_;
    delete[] gInstance->OoEminusOoP_;
    delete[] gInstance->lostHits_;
    delete[] gInstance->conversionVeto_;
    delete[] gInstance->cutbasedID_HLT_;

    for(auto & kv: gInstance->rawMVAs_POG_)
    {
      delete[] kv.second;
    }
    for(auto & kv: gInstance->mvaIDs_POG_)
    {
      for(auto & kw: kv.second)
      {
        delete[] kw.second;
      }
    }

    instances_[branchName_obj_] = nullptr;
  }
}

void
RecoElectronReader::setBranchNames()
{
  if (numInstances_[branchName_obj_] == 0)
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
    for(const auto & EGammaID_choice: EGammaID_map)
    {
      bai.setBranchAddress(rawMVAs_POG_[EGammaID_choice.first], branchNames_mvaRaw_POG_[EGammaID_choice.first]);
      mvaIDs_POG_[EGammaID_choice.first] = {};
      for(const auto & EGammaWP_choice: EGammaWP_map)
      {
        bai.setBranchAddress(
          mvaIDs_POG_           [EGammaID_choice.first][EGammaWP_choice.first],
          branchNames_mvaID_POG_[EGammaID_choice.first][EGammaWP_choice.first]
        );
      }
    }

    bai.setBranchAddress(eCorr_, branchName_eCorr_);
    bai.setBranchAddress(sigmaEtaEta_, branchName_sigmaEtaEta_);
    bai.setBranchAddress(HoE_, branchName_HoE_);
    bai.setBranchAddress(deltaEta_, branchName_deltaEta_);
    bai.setBranchAddress(deltaPhi_, branchName_deltaPhi_);
    bai.setBranchAddress(OoEminusOoP_, branchName_OoEminusOoP_);
    bai.setBranchAddress(lostHits_, branchName_lostHits_);
    bai.setBranchAddress(conversionVeto_, branchName_conversionVeto_);
    bai.setBranchAddress(cutbasedID_HLT_, era_ == kEra_2016 ? branchName_cutbasedID_HLT_ : "");
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
      << leptonReader_->max_nLeptons_
    ;
  }

  if (nLeptons > 0)
  {
    electrons.reserve(nLeptons);
    for(UInt_t idxLepton = 0; idxLepton < nLeptons; ++idxLepton)
    {
      if(std::abs(gLeptonReader->pdgId_[idxLepton]) == 11)
      {
        const double ptCorr = readUncorrected_ ? gElectronReader->eCorr_[idxLepton] : 1.;
        electrons.push_back({
          {
            {
              gLeptonReader->pt_[idxLepton] / ptCorr,
              gLeptonReader->eta_[idxLepton],
              gLeptonReader->phi_[idxLepton],
              gLeptonReader->mass_[idxLepton],
              gLeptonReader->pdgId_[idxLepton],
              gLeptonReader->charge_[idxLepton],
            },
            gLeptonReader->dxy_[idxLepton],
            gLeptonReader->dz_[idxLepton],
            gLeptonReader->relIso_all_[idxLepton],
            gLeptonReader->pfRelIso04_all_[idxLepton],
            gLeptonReader->relIso_chg_[idxLepton],
            gLeptonReader->relIso_neu_[idxLepton],
            gLeptonReader->sip3d_[idxLepton],
            gLeptonReader->mvaRawTTH_[idxLepton],
            gLeptonReader->jetPtRatio_[idxLepton],
            gLeptonReader->jetPtRel_[idxLepton],
            gLeptonReader->jetNDauChargedMVASel_[idxLepton],
            gLeptonReader->tightCharge_[idxLepton],
            gLeptonReader->filterBits_[idxLepton],
            gLeptonReader->jetIdx_[idxLepton],
            gLeptonReader->genPartFlav_[idxLepton],
            gLeptonReader->genMatchIdx_[idxLepton],
          },
          gElectronReader->eCorr_[idxLepton],
          gElectronReader->sigmaEtaEta_[idxLepton],
          gElectronReader->HoE_[idxLepton],
          gElectronReader->deltaEta_[idxLepton],
          gElectronReader->deltaPhi_[idxLepton],
          gElectronReader->OoEminusOoP_[idxLepton],
          gElectronReader->lostHits_[idxLepton],
          gElectronReader->conversionVeto_[idxLepton],
          gElectronReader->cutbasedID_HLT_[idxLepton],
        });

        RecoElectron & electron = electrons.back();
        for(const auto & kv: gLeptonReader->jetBtagCSVs_)
        {
          const double val = kv.second[idxLepton];
          electron.jetBtagCSVs_[kv.first] = std::isnan(val) ? -2. : val;
        }
        for(const auto & EGammaID_choice: gElectronReader->rawMVAs_POG_)
        {
          electron.egammaID_raws_[EGammaID_choice.first] = EGammaID_choice.second[idxLepton];
        }
        for(const auto & EGammaID_choice: gElectronReader->mvaIDs_POG_)
        {
          electron.egammaID_ids_[EGammaID_choice.first] = {};
          for(const auto & EGammaWP_choice: EGammaID_choice.second)
          {
            electron.egammaID_ids_[EGammaID_choice.first][EGammaWP_choice.first] = EGammaWP_choice.second[idxLepton];
          }
        }
      }
    }
    gLeptonReader->readGenMatching(electrons);
  }
  return electrons;
}
