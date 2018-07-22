#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTauReader.h" // RecoHadTauReader

#include "tthAnalysis/HiggsToTauTau/interface/GenLeptonReader.h" // GenLeptonReader
#include "tthAnalysis/HiggsToTauTau/interface/GenHadTauReader.h" // GenHadTauReader
#include "tthAnalysis/HiggsToTauTau/interface/GenJetReader.h" // GenJetReader
#include "tthAnalysis/HiggsToTauTau/interface/LocalFileInPath.h" // LocalFileInPath
#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // setValue_int(), setValue_float()
#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h" // cmsException()
#include "tthAnalysis/HiggsToTauTau/interface/BranchAddressInitializer.h" // BranchAddressInitializer, TTree, Form()
#include "tthAnalysis/HiggsToTauTau/interface/sysUncertOptions.h" // kHadTauPt_*

#include <TFile.h> // TFile
#include <TGraphAsymmErrors.h> // TGraphAsymmErrors
#include <TFormula.h> // TFormula

#include <boost/range/numeric.hpp> // boost::accumulate()
#include <boost/range/adaptor/map.hpp> // boost::adaptors::map_values

std::map<std::string, int> RecoHadTauReader::numInstances_;
std::map<std::string, RecoHadTauReader *> RecoHadTauReader::instances_;

RecoHadTauReader::RecoHadTauReader(int era,
                                   bool readGenMatching)
  : RecoHadTauReader(era, "Tau", readGenMatching)
{}

RecoHadTauReader::RecoHadTauReader(int era,
                                   const std::string & branchName_obj,
                                   bool readGenMatching)
  : tauIdMVArun2dR03DB_wpFile_(nullptr)
  , DBdR03oldDMwLTEff95_(nullptr)
  , mvaOutput_normalization_DBdR03oldDMwLT_(nullptr)
  , era_(era)
  , max_nHadTaus_(32)
  , branchName_num_(Form("n%s", branchName_obj.data()))
  , branchName_obj_(branchName_obj)
  , genLeptonReader_(nullptr)
  , genHadTauReader_(nullptr)
  , genJetReader_(nullptr)
  , readGenMatching_(readGenMatching)
  , hadTauPt_option_(kHadTauPt_central)
  , hadTau_pt_(nullptr)
  , hadTau_eta_(nullptr)
  , hadTau_phi_(nullptr)
  , hadTau_mass_(nullptr)
  , hadTau_charge_(nullptr)
  , hadTau_dxy_(nullptr)
  , hadTau_dz_(nullptr)
  , hadTau_decayMode_(nullptr)
  , hadTau_idDecayMode_(nullptr)
  , hadTau_idDecayModeNewDMs_(nullptr)
  , hadTau_idMVA_dR03_(nullptr)
  , hadTau_rawMVA_dR03_(nullptr)
  , hadTau_idMVA_dR05_(nullptr)
  , hadTau_rawMVA_dR05_(nullptr)
  , hadTau_idCombIso_dR03_(nullptr)
  , hadTau_rawCombIso_dR03_(nullptr)
  , hadTau_idCombIso_dR05_(nullptr)
  , hadTau_idAgainstElec_(nullptr)
  , hadTau_idAgainstMu_(nullptr)
  , hadTau_filterBits_(nullptr)
{
  if(readGenMatching_)
  {
    genLeptonReader_ = new GenLeptonReader(Form("%s_genLepton", branchName_obj_.data()), max_nHadTaus_);
    genHadTauReader_ = new GenHadTauReader(Form("%s_genTau",    branchName_obj_.data()), max_nHadTaus_);
    genJetReader_    = new GenJetReader   (Form("%s_genJet",    branchName_obj_.data()), max_nHadTaus_);
  }
  setBranchNames();
  if(era == kEra_2016)
  {
    readDBdR03oldDMwLTEff95();
  }
}

RecoHadTauReader::~RecoHadTauReader()
{
  --numInstances_[branchName_obj_];
  assert(numInstances_[branchName_obj_] >= 0);

  if(numInstances_[branchName_obj_] == 0)
  {
    numInstances_.erase(branchName_obj_);

    if(era_ == kEra_2016)
    {
      int numInstances_total = 0;
      for(const auto & it: numInstances_)
      {
        numInstances_total += it.second;
      }
      if(numInstances_total == 0)
      {
        RecoHadTauReader * const gInstance = instances_.begin()->second;
        assert(gInstance);
        delete gInstance->tauIdMVArun2dR03DB_wpFile_;
      }
    }

    RecoHadTauReader * const gInstance = instances_[branchName_obj_];
    assert(gInstance);

    delete gInstance->genLeptonReader_;
    delete gInstance->genHadTauReader_;
    delete gInstance->genJetReader_;
    delete[] gInstance->hadTau_pt_;
    delete[] gInstance->hadTau_eta_;
    delete[] gInstance->hadTau_phi_;
    delete[] gInstance->hadTau_mass_;
    delete[] gInstance->hadTau_dxy_;
    delete[] gInstance->hadTau_dz_;
    delete[] gInstance->hadTau_decayMode_;
    delete[] gInstance->hadTau_idDecayMode_;
    delete[] gInstance->hadTau_idDecayModeNewDMs_;
    delete[] gInstance->hadTau_idMVA_dR03_;
    delete[] gInstance->hadTau_rawMVA_dR03_;
    delete[] gInstance->hadTau_idMVA_dR05_;
    delete[] gInstance->hadTau_rawMVA_dR05_;
    delete[] gInstance->hadTau_idCombIso_dR03_;
    delete[] gInstance->hadTau_rawCombIso_dR03_;
    delete[] gInstance->hadTau_idCombIso_dR05_;
    delete[] gInstance->hadTau_rawCombIso_dR05_;
    delete[] gInstance->hadTau_idAgainstElec_;
    delete[] gInstance->hadTau_idAgainstMu_;
    delete[] gInstance->hadTau_charge_;
    delete[] gInstance->hadTau_filterBits_;

    instances_.erase(branchName_obj_);
  }
}

void
RecoHadTauReader::readDBdR03oldDMwLTEff95()
{
  RecoHadTauReader * gInstance = instances_.begin()->second;
  assert(gInstance);
  if(! gInstance->tauIdMVArun2dR03DB_wpFile_)
  {
    const LocalFileInPath tauIdMVArun2dR03DB_wpFilePath = LocalFileInPath(
      "tthAnalysis/HiggsToTauTau/data/wpDiscriminationByIsolationMVARun2v1_DBdR03oldDMwLT.root"
    );
    gInstance->tauIdMVArun2dR03DB_wpFile_ = new TFile(tauIdMVArun2dR03DB_wpFilePath.fullPath().c_str(), "read");
  }
  DBdR03oldDMwLTEff95_ = dynamic_cast<TGraphAsymmErrors *>(gInstance->tauIdMVArun2dR03DB_wpFile_->Get("DBdR03oldDMwLTEff95"));
  mvaOutput_normalization_DBdR03oldDMwLT_ = dynamic_cast<TFormula *>(
    gInstance->tauIdMVArun2dR03DB_wpFile_->Get("mvaOutput_normalization_DBdR03oldDMwLT")
  );
}

void
RecoHadTauReader::setHadTauPt_central_or_shift(int hadTauPt_option)
{
  hadTauPt_option_ = hadTauPt_option;
}

void
RecoHadTauReader::setBranchNames()
{
  if(numInstances_[branchName_obj_] == 0)
  {
    branchName_pt_ = Form("%s_%s", branchName_obj_.data(), "pt");
    branchName_eta_ = Form("%s_%s", branchName_obj_.data(), "eta");
    branchName_phi_ = Form("%s_%s", branchName_obj_.data(), "phi");
    branchName_mass_ = Form("%s_%s", branchName_obj_.data(), "mass");
    branchName_charge_ = Form("%s_%s", branchName_obj_.data(), "charge");
    branchName_dxy_ = Form("%s_%s", branchName_obj_.data(), "dxy");
    branchName_dz_ = Form("%s_%s", branchName_obj_.data(), "dz");
    branchName_decayMode_ = Form("%s_%s", branchName_obj_.data(), "decayMode");
    branchName_idDecayMode_ = Form("%s_%s", branchName_obj_.data(), "idDecayMode");
    branchName_idDecayModeNewDMs_ = Form("%s_%s", branchName_obj_.data(), "idDecayModeNewDMs");
    std::string mvaString;
    switch(era_)
    {
      case kEra_2016: mvaString = "MVAoldDMdR03";       break;
      case kEra_2017: mvaString = "MVAoldDMdR032017v2"; break;
      case kEra_2018: throw cmsException(this, __func__, __LINE__) << "Implement me!";
      default: throw cmsException(this, __func__, __LINE__) << "Invalid era = " << era_;
    }
    assert(! mvaString.empty());
    branchName_idMVA_dR03_ = Form("%s_%s", branchName_obj_.data(), Form("id%s_log", mvaString.data()));
    branchName_rawMVA_dR03_ = Form("%s_%s", branchName_obj_.data(), Form("raw%s", mvaString.data()));
    branchName_idMVA_dR05_ = Form("%s_%s", branchName_obj_.data(), "idMVAoldDM_log");
    branchName_rawMVA_dR05_ = Form("%s_%s", branchName_obj_.data(), "rawMVAoldDM");
    branchName_idCombIso_dR03_ = Form("%s_%s", branchName_obj_.data(), "idCI3hitdR03");
    branchName_isoCombIso_dR03_ = Form("%s_%s", branchName_obj_.data(), "isoCI3hitdR03");
    branchName_idCombIso_dR05_ = Form("%s_%s", branchName_obj_.data(), "idCI3hit");
    branchName_isoCombIso_dR05_ = Form("%s_%s", branchName_obj_.data(), "isoCI3hit");
    branchName_idAgainstElec_ = Form("%s_%s", branchName_obj_.data(), "idAntiEle_log");
    branchName_idAgainstMu_ = Form("%s_%s", branchName_obj_.data(), "idAntiMu_log");
    branchName_filterBits_ = Form("%s_%s", branchName_obj_.data(), "filterBits");
    instances_[branchName_obj_] = this;
  }
  else
  {
    if(branchName_num_ != instances_[branchName_obj_]->branchName_num_)
    {
      throw cmsException(this)
        << "Association between configuration parameters 'branchName_num' and 'branchName_obj' must be unique:"
           " present association 'branchName_num' = " << branchName_num_ << " with 'branchName_obj' = " << branchName_obj_
        << " does not match previous association 'branchName_num' = " << instances_[branchName_obj_]->branchName_num_
        << " with 'branchName_obj' = " << instances_[branchName_obj_]->branchName_obj_ << " !!\n";
    }
  }
  ++numInstances_[branchName_obj_];
}

void
RecoHadTauReader::setBranchAddresses(TTree * tree)
{
  if(instances_[branchName_obj_] == this)
  {
    if(readGenMatching_)
    {
      genLeptonReader_->setBranchAddresses(tree);
      genHadTauReader_->setBranchAddresses(tree);
      genJetReader_->setBranchAddresses(tree);
    }
    BranchAddressInitializer bai(tree, max_nHadTaus_);
    bai.setBranchAddress(nHadTaus_, branchName_num_);
    bai.setBranchAddress(hadTau_pt_, branchName_pt_);
    bai.setBranchAddress(hadTau_eta_, branchName_eta_);
    bai.setBranchAddress(hadTau_phi_, branchName_phi_);
    bai.setBranchAddress(hadTau_mass_, branchName_mass_);
    bai.setBranchAddress(hadTau_charge_, branchName_charge_);
    bai.setBranchAddress(hadTau_dxy_, branchName_dxy_);
    bai.setBranchAddress(hadTau_dz_, branchName_dz_);
    bai.setBranchAddress(hadTau_decayMode_, branchName_decayMode_);
    bai.setBranchAddress(hadTau_idDecayMode_, branchName_idDecayMode_);
    bai.setBranchAddress(hadTau_idDecayModeNewDMs_, branchName_idDecayModeNewDMs_);
    bai.setBranchAddress(hadTau_idMVA_dR03_, branchName_idMVA_dR03_);
    bai.setBranchAddress(hadTau_rawMVA_dR03_, branchName_rawMVA_dR03_);
    bai.setBranchAddress(hadTau_idMVA_dR05_, branchName_idMVA_dR05_);
    bai.setBranchAddress(hadTau_rawMVA_dR05_, branchName_rawMVA_dR05_);
    bai.setBranchAddress(hadTau_idCombIso_dR03_, "", -1);
    bai.setBranchAddress(hadTau_rawCombIso_dR03_, "", -1.);
    bai.setBranchAddress(hadTau_idCombIso_dR05_, "", -1);
    bai.setBranchAddress(hadTau_rawCombIso_dR05_, "", -1.);
    bai.setBranchAddress(hadTau_idAgainstElec_, branchName_idAgainstElec_);
    bai.setBranchAddress(hadTau_idAgainstMu_, branchName_idAgainstMu_);
    bai.setBranchAddress(hadTau_filterBits_, branchName_filterBits_);
  }
}

std::vector<RecoHadTau>
RecoHadTauReader::read() const
{
  const RecoHadTauReader * const gInstance = instances_[branchName_obj_];
  assert(gInstance);

  std::vector<RecoHadTau> hadTaus;
  const Int_t nHadTaus = gInstance->nHadTaus_;
  if(nHadTaus > max_nHadTaus_)
  {
    throw cmsException(this)
      << "Number of hadronic taus stored in Ntuple = " << nHadTaus
      << ", exceeds max_nHadTaus = " << max_nHadTaus_ << " !!\n";
  }

  if(nHadTaus > 0)
  {
    hadTaus.reserve(nHadTaus);
    for(Int_t idxHadTau = 0; idxHadTau < nHadTaus; ++idxHadTau)
    {
      Float_t hadTau_pt = -1.;
      switch(hadTauPt_option_)
      {
        case kHadTauPt_central:   hadTau_pt =        gInstance->hadTau_pt_[idxHadTau]; break;
        case kHadTauPt_shiftUp:   hadTau_pt = 1.03 * gInstance->hadTau_pt_[idxHadTau]; break;
        case kHadTauPt_shiftDown: hadTau_pt = 0.97 * gInstance->hadTau_pt_[idxHadTau]; break;
        default: throw cmsException(this) << "Invalid tau ES option: " << hadTauPt_option_;
      }

      Int_t hadTau_idMVA_dR03 = hadTau_idMVA_dR03_[idxHadTau];
      if(era_ == kEra_2016)
      {
        if(hadTau_idMVA_dR03 >= 1)
        {
          hadTau_idMVA_dR03 += 1;
        }
        else
        {
          assert(DBdR03oldDMwLTEff95_ && mvaOutput_normalization_DBdR03oldDMwLT_);
          if(mvaOutput_normalization_DBdR03oldDMwLT_->Eval(gInstance->hadTau_rawMVA_dR03_[idxHadTau]) >
             DBdR03oldDMwLTEff95_->Eval(gInstance->hadTau_pt_[idxHadTau]))
          {
            hadTau_idMVA_dR03 = 1;
          }
          else
          {
            hadTau_idMVA_dR03 = 0;
          }
        }
      }

      hadTaus.push_back({
        {
          hadTau_pt,
          gInstance->hadTau_eta_[idxHadTau],
          gInstance->hadTau_phi_[idxHadTau],
          gInstance->hadTau_mass_[idxHadTau],
          gInstance->hadTau_charge_[idxHadTau]
        },
        gInstance->hadTau_dxy_[idxHadTau],
        gInstance->hadTau_dz_[idxHadTau],
        gInstance->hadTau_decayMode_[idxHadTau],
        gInstance->hadTau_idDecayMode_[idxHadTau],
        gInstance->hadTau_idDecayModeNewDMs_[idxHadTau],
        hadTau_idMVA_dR03,
        gInstance->hadTau_rawMVA_dR03_[idxHadTau],
        gInstance->hadTau_idMVA_dR05_[idxHadTau],
        gInstance->hadTau_rawMVA_dR05_[idxHadTau],
        gInstance->hadTau_idCombIso_dR03_[idxHadTau],
        gInstance->hadTau_rawCombIso_dR03_[idxHadTau],
        gInstance->hadTau_idCombIso_dR05_[idxHadTau],
        gInstance->hadTau_rawCombIso_dR05_[idxHadTau],
        gInstance->hadTau_idAgainstElec_[idxHadTau],
        gInstance->hadTau_idAgainstMu_[idxHadTau],
        gInstance->hadTau_filterBits_[idxHadTau]
      });
    }
    readGenMatching(hadTaus);
  }
  return hadTaus;
}

void
RecoHadTauReader::readGenMatching(std::vector<RecoHadTau> & hadTaus) const
{
  if(readGenMatching_)
  {
    assert(genLeptonReader_ && genHadTauReader_ && genJetReader_);
    const std::size_t nHadTaus = hadTaus.size();

    std::vector<GenLepton> matched_genLeptons = genLeptonReader_->read();
    assert(matched_genLeptons.size() == nHadTaus);

    std::vector<GenHadTau> matched_genHadTaus = genHadTauReader_->read();
    assert(matched_genHadTaus.size() == nHadTaus);

    std::vector<GenJet> matched_genJets = genJetReader_->read();
    assert(matched_genJets.size() == nHadTaus);

    for(std::size_t idxHadTau = 0; idxHadTau < nHadTaus; ++idxHadTau)
    {
      RecoHadTau & hadTau = hadTaus[idxHadTau];

      const GenLepton & matched_genLepton = matched_genLeptons[idxHadTau];
      if(matched_genLepton.isValid()) hadTau.set_genLepton(new GenLepton(matched_genLepton));

      const GenHadTau & matched_genHadTau = matched_genHadTaus[idxHadTau];
      if(matched_genHadTau.isValid()) hadTau.set_genHadTau(new GenHadTau(matched_genHadTau));

      const GenJet & matched_genJet = matched_genJets[idxHadTau];
      if(matched_genJet.isValid()) hadTau.set_genJet(new GenJet(matched_genJet));
    }
  }
}
