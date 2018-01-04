#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTauReader.h" // RecoHadTauReader

#include "tthAnalysis/HiggsToTauTau/interface/GenLeptonReader.h" // GenLeptonReader
#include "tthAnalysis/HiggsToTauTau/interface/GenHadTauReader.h" // GenHadTauReader
#include "tthAnalysis/HiggsToTauTau/interface/GenJetReader.h" // GenJetReader
#include "tthAnalysis/HiggsToTauTau/interface/LocalFileInPath.h" // LocalFileInPath
#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // setValue_int(), setValue_float()
#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h" // cmsException()

#include <TString.h> // Form()
#include <TTree.h> // TTree
#include <TFile.h> // TFile
#include <TGraph.h> // TGraph
#include <TFormula.h> // TFormula

#include <boost/range/numeric.hpp> // boost::accumulate()
#include <boost/range/adaptor/map.hpp> // boost::adaptors::map_values

std::map<std::string, int> RecoHadTauReader::numInstances_;
std::map<std::string, RecoHadTauReader *> RecoHadTauReader::instances_;

RecoHadTauReader::RecoHadTauReader(int era, bool readGenMatching)
  : RecoHadTauReader(era, "nTau", "Tau", readGenMatching)
{}

RecoHadTauReader::RecoHadTauReader(int era,
                                   const std::string & branchName_num,
                                   const std::string & branchName_obj,
                                   bool readGenMatching)
  : tauIdMVArun2dR03DB_wpFile_(nullptr)
  , DBdR03oldDMwLTEff95_(nullptr)
  , mvaOutput_normalization_DBdR03oldDMwLT_(nullptr)
  , era_(era)
  , max_nHadTaus_(32)
  , branchName_num_(branchName_num)
  , branchName_obj_(branchName_obj)
  , genLeptonReader_(nullptr)
  , genHadTauReader_(nullptr)
  , genJetReader_(nullptr)
  , readGenMatching_(readGenMatching)
  , hadTauPt_option_(RecoHadTauReader::kHadTauPt_central)
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
{
  if ( readGenMatching_ ) {
    genLeptonReader_ = new GenLeptonReader(Form("%s_genLepton", branchName_num_.data()), Form("%s_genLepton", branchName_obj_.data()));
    genHadTauReader_ = new GenHadTauReader(Form("%s_genTau",    branchName_num_.data()), Form("%s_genTau",    branchName_obj_.data()));
    genJetReader_    = new GenJetReader   (Form("%s_genJet",    branchName_num_.data()), Form("%s_genJet",    branchName_obj_.data()));
  }
  setBranchNames();
  readDBdR03oldDMwLTEff95();
}

RecoHadTauReader::~RecoHadTauReader()
{
  --numInstances_[branchName_obj_];
  assert(numInstances_[branchName_obj_] >= 0);

  if(numInstances_[branchName_obj_] == 0)
  {
    numInstances_.erase(branchName_obj_);

    const int numInstances_total = boost::accumulate(numInstances_ | boost::adaptors::map_values, 0);
    if(numInstances_total == 0)
    {
      const RecoHadTauReader * const gInstance = instances_.begin()->second;
      assert(gInstance);
      delete gInstance->tauIdMVArun2dR03DB_wpFile_;
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

    instances_.erase(branchName_obj_);
  }
}

void
RecoHadTauReader::setHadTauPt_central_or_shift(int hadTauPt_option)
{
  hadTauPt_option_ = hadTauPt_option;
}

void RecoHadTauReader::readDBdR03oldDMwLTEff95()
{
  RecoHadTauReader * gInstance = instances_.begin()->second;
  assert(gInstance);

  if(! gInstance->tauIdMVArun2dR03DB_wpFile_)
  {
    LocalFileInPath tauIdMVArun2dR03DB_wpFilePath = LocalFileInPath(
      "tthAnalysis/HiggsToTauTau/data/wpDiscriminationByIsolationMVARun2v1_DBdR03oldDMwLT.root"
    );
    gInstance->tauIdMVArun2dR03DB_wpFile_ = new TFile(tauIdMVArun2dR03DB_wpFilePath.fullPath().c_str());
  }
  DBdR03oldDMwLTEff95_ = dynamic_cast<TGraph *>(
    gInstance->tauIdMVArun2dR03DB_wpFile_->Get("DBdR03oldDMwLTEff95")
  );
  mvaOutput_normalization_DBdR03oldDMwLT_ = dynamic_cast<TFormula *>(
    gInstance->tauIdMVArun2dR03DB_wpFile_->Get("mvaOutput_normalization_DBdR03oldDMwLT")
  );
}

void RecoHadTauReader::setBranchNames()
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
    branchName_idMVA_dR03_ = Form("%s_%s", branchName_obj_.data(), "idMVAoldDMdR03_log");
    branchName_rawMVA_dR03_ = Form("%s_%s", branchName_obj_.data(), "rawMVAoldDMdR03");
    branchName_idMVA_dR05_ = Form("%s_%s", branchName_obj_.data(), "idMVAoldDM_log");
    branchName_rawMVA_dR05_ = Form("%s_%s", branchName_obj_.data(), "rawMVAoldDM");
    branchName_idCombIso_dR03_ = Form("%s_%s", branchName_obj_.data(), "idCI3hitdR03");
    branchName_isoCombIso_dR03_ = Form("%s_%s", branchName_obj_.data(), "isoCI3hitdR03");
    branchName_idCombIso_dR05_ = Form("%s_%s", branchName_obj_.data(), "idCI3hit");
    branchName_isoCombIso_dR05_ = Form("%s_%s", branchName_obj_.data(), "isoCI3hit");
    branchName_idAgainstElec_ = Form("%s_%s", branchName_obj_.data(), "idAntiEle_log");
    branchName_idAgainstMu_ = Form("%s_%s", branchName_obj_.data(), "idAntiMu_log");
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
    tree->SetBranchAddress(branchName_num_.data(), &nHadTaus_);   
    hadTau_pt_ = new Float_t[max_nHadTaus_];
    tree->SetBranchAddress(branchName_pt_.data(), hadTau_pt_); 
    hadTau_eta_ = new Float_t[max_nHadTaus_];
    tree->SetBranchAddress(branchName_eta_.data(), hadTau_eta_); 
    hadTau_phi_ = new Float_t[max_nHadTaus_];
    tree->SetBranchAddress(branchName_phi_.data(), hadTau_phi_); 
    hadTau_mass_ = new Float_t[max_nHadTaus_];
    tree->SetBranchAddress(branchName_mass_.data(), hadTau_mass_); 
    hadTau_charge_ = new Int_t[max_nHadTaus_];
    tree->SetBranchAddress(branchName_charge_.data(), hadTau_charge_); 
    hadTau_dxy_ = new Float_t[max_nHadTaus_];
    tree->SetBranchAddress(branchName_dxy_.data(), hadTau_dxy_);
    hadTau_dz_ = new Float_t[max_nHadTaus_];
    tree->SetBranchAddress(branchName_dz_.data(), hadTau_dz_);
    hadTau_decayMode_ = new Int_t[max_nHadTaus_];
    tree->SetBranchAddress(branchName_decayMode_.data(), hadTau_decayMode_);
    hadTau_idDecayMode_ = new Bool_t[max_nHadTaus_];
    tree->SetBranchAddress(branchName_idDecayMode_.data(), hadTau_idDecayMode_);
    hadTau_idDecayModeNewDMs_ = new Bool_t[max_nHadTaus_];
    tree->SetBranchAddress(branchName_idDecayModeNewDMs_.data(), hadTau_idDecayModeNewDMs_);
    hadTau_idMVA_dR03_ = new Int_t[max_nHadTaus_];
    tree->SetBranchAddress(branchName_idMVA_dR03_.data(), hadTau_idMVA_dR03_); 
    hadTau_rawMVA_dR03_ = new Float_t[max_nHadTaus_];
    tree->SetBranchAddress(branchName_rawMVA_dR03_.data(), hadTau_rawMVA_dR03_); 
    hadTau_idMVA_dR05_ = new Int_t[max_nHadTaus_];
    tree->SetBranchAddress(branchName_idMVA_dR05_.data(), hadTau_idMVA_dR05_);
    hadTau_rawMVA_dR05_ = new Float_t[max_nHadTaus_];
    tree->SetBranchAddress(branchName_rawMVA_dR05_.data(), hadTau_rawMVA_dR05_); 
//--- Karl: the following tau ID (fallback) variables missing in nanoAOD
    hadTau_idCombIso_dR03_ = new Int_t[max_nHadTaus_];
    setValue_int(hadTau_idCombIso_dR03_, max_nHadTaus_, -1);
    hadTau_rawCombIso_dR03_ = new Float_t[max_nHadTaus_];
    setValue_float(hadTau_rawCombIso_dR03_, max_nHadTaus_, -1.);
    hadTau_idCombIso_dR05_ = new Int_t[max_nHadTaus_];
    setValue_int(hadTau_idCombIso_dR05_, max_nHadTaus_, -1);
    hadTau_rawCombIso_dR05_ = new Float_t[max_nHadTaus_];
    setValue_float(hadTau_rawCombIso_dR05_, max_nHadTaus_, -1.);
//--- end
    hadTau_idAgainstElec_ = new Int_t[max_nHadTaus_];
    tree->SetBranchAddress(branchName_idAgainstElec_.data(), hadTau_idAgainstElec_); 
    hadTau_idAgainstMu_ = new Int_t[max_nHadTaus_];
    tree->SetBranchAddress(branchName_idAgainstMu_.data(), hadTau_idAgainstMu_);
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
        case RecoHadTauReader::kHadTauPt_central:   hadTau_pt = 1.00*gInstance->hadTau_pt_[idxHadTau]; break;
        case RecoHadTauReader::kHadTauPt_shiftUp:   hadTau_pt = 1.03*gInstance->hadTau_pt_[idxHadTau]; break;
        case RecoHadTauReader::kHadTauPt_shiftDown: hadTau_pt = 0.97*gInstance->hadTau_pt_[idxHadTau]; break;
        default: throw cmsException(this) << "Invalid tau ES option: " << hadTauPt_option_;
      }
      // compute "VVLose" (95% signal efficiency) working point for tau ID MVA trained for dR=0.3 isolation cone,
      // used to enhance background event statistics for training of event-level MVAs that separate
      // ttH signal from backgrounds
      Int_t hadTau_idMVA_dR03 = hadTau_idMVA_dR03_[idxHadTau];
      if(hadTau_idMVA_dR03 >= 1)
      {
        hadTau_idMVA_dR03 += 1;
      }
      else
      {
        assert(DBdR03oldDMwLTEff95_ && mvaOutput_normalization_DBdR03oldDMwLT_);
        if(mvaOutput_normalization_DBdR03oldDMwLT_->Eval(gInstance->hadTau_rawMVA_dR03_[idxHadTau]) >
           DBdR03oldDMwLTEff95_->Eval(gInstance->hadTau_pt_[idxHadTau])                             )
        {
           hadTau_idMVA_dR03 = 1;
        }
        else
        {
          hadTau_idMVA_dR03 = 0;
        }
      } // hadTau_idMVA_dR03 >= 1

      hadTaus.push_back({
        hadTau_pt,
        gInstance->hadTau_eta_[idxHadTau],
        gInstance->hadTau_phi_[idxHadTau],
        gInstance->hadTau_mass_[idxHadTau],
        gInstance->hadTau_charge_[idxHadTau],
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
        gInstance->hadTau_idAgainstMu_[idxHadTau]
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
      if(matched_genLepton.isValid()) hadTau.set_genLepton(new GenLepton(matched_genLepton), true);

      const GenHadTau & matched_genHadTau = matched_genHadTaus[idxHadTau];
      if(matched_genHadTau.isValid()) hadTau.set_genHadTau(new GenHadTau(matched_genHadTau), true);

      const GenJet & matched_genJet = matched_genJets[idxHadTau];
      if(matched_genJet.isValid()) hadTau.set_genJet(new GenJet(matched_genJet), true);
    }
  }
}
