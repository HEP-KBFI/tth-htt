#include "tthAnalysis/HiggsToTauTau/interface/Data_to_MC_CorrectionInterface_Base.h"

#include "tthAnalysis/HiggsToTauTau/interface/lutAuxFunctions.h" // get_from_lut()
#include "tthAnalysis/HiggsToTauTau/interface/leptonTypes.h" // kElectron, kMuon
#include "tthAnalysis/HiggsToTauTau/interface/data_to_MC_corrections_auxFunctions.h" // aux::
#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h" // cmsException()

#include <TString.h> // Form()
#include <TFile.h> // TFile

#include <boost/algorithm/string/predicate.hpp> // boost::ends_with(), boost::starts_with()

#include <cassert> // assert()

Data_to_MC_CorrectionInterface_Base::Data_to_MC_CorrectionInterface_Base(const edm::ParameterSet & cfg)
  : hadTauSelection_(-1)
  , eToTauFakeRate_option_(FRet::central)
  , muToTauFakeRate_option_(FRmt::central)
  , triggerSF_option_(TriggerSFsys::central)
  , numLeptons_(0)
  , lepton_type_(4)
  , lepton_pt_(4)
  , lepton_eta_(4)
  , numElectrons_(0)
  , electron_pt_(4)
  , electron_eta_(4)
  , numMuons_(0)
  , muon_pt_(4)
  , muon_eta_(4)
  , numHadTaus_(0)
  , hadTau_genPdgId_(4)
  , hadTau_pt_(4)
  , hadTau_eta_(4)
{
  const std::string hadTauSelection_string = cfg.getParameter<std::string>("hadTauSelection");
  setHadTauSelection(hadTauSelection_string);

  for(int idxHadTau = 0; idxHadTau < 4; ++idxHadTau)
  {
    hadTauSelection_antiElectron_[idxHadTau] = -1;
    if(cfg.exists("hadTauSelection_antiElectron"))
    {
      hadTauSelection_antiElectron_[idxHadTau] = cfg.getParameter<int>("hadTauSelection_antiElectron");
    }
    else
    {
      const std::string cfgParName = "hadTauSelection_antiElectron" + aux::getHadTauIdxLabel(idxHadTau);
      if(cfg.exists(cfgParName))
      {
        hadTauSelection_antiElectron_[idxHadTau] = cfg.getParameter<int>(cfgParName);
      }
    }

    hadTauSelection_antiMuon_[idxHadTau] = -1;
    if(cfg.exists("hadTauSelection_antiMuon"))
    {
      hadTauSelection_antiMuon_[idxHadTau] = cfg.getParameter<int>("hadTauSelection_antiMuon");
    }
    else
    {
      const std::string cfgParName = "hadTauSelection_antiMuon" + aux::getHadTauIdxLabel(idxHadTau);
      if(cfg.exists(cfgParName))
      {
        hadTauSelection_antiMuon_[idxHadTau] = cfg.getParameter<int>(cfgParName);
      }
    }
  }

  const std::string central_or_shift = cfg.getParameter<std::string>("central_or_shift");

  eToTauFakeRate_option_ = getEToTauFR_option(central_or_shift);
  muToTauFakeRate_option_ = getMuToTauFR_option(central_or_shift);
  triggerSF_option_ = getTriggerSF_option(central_or_shift);
}

Data_to_MC_CorrectionInterface_Base::~Data_to_MC_CorrectionInterface_Base()
{
  aux::clearCollection(sfElectronID_and_Iso_loose_);
  aux::clearCollection(sfElectronID_and_Iso_tight_to_loose_woTightCharge_);
  aux::clearCollection(sfElectronID_and_Iso_tight_to_loose_wTightCharge_);
  aux::clearCollection(sfMuonID_and_Iso_loose_);
  aux::clearCollection(sfMuonID_and_Iso_tight_to_loose_woTightCharge_);
  aux::clearCollection(sfMuonID_and_Iso_tight_to_loose_wTightCharge_);
  for(auto & kv: inputFiles_)
  {
    delete kv.second;
  }
}

void
Data_to_MC_CorrectionInterface_Base::setHadTauSelection(const std::string& hadTauSelection)
{
  hadTauSelection_ = -1;
  if     (hadTauSelection == "dR03mvaVVLoose") hadTauSelection_ = 1;
  else if(hadTauSelection == "dR03mvaVLoose" ) hadTauSelection_ = 2;
  else if(hadTauSelection == "dR03mvaLoose"  ) hadTauSelection_ = 3;
  else if(hadTauSelection == "dR03mvaMedium" ) hadTauSelection_ = 4;
  else if(hadTauSelection == "dR03mvaTight"  ) hadTauSelection_ = 5;
  else if(hadTauSelection == "dR03mvaVTight" ) hadTauSelection_ = 6;
  else if(hadTauSelection == "dR03mvaVVTight") hadTauSelection_ = 7;
  else throw cmsException(this, __func__)
         << "Invalid Configuration parameter 'hadTauSelection' = " << hadTauSelection
       ;
}

void
Data_to_MC_CorrectionInterface_Base::setLeptons(int lepton1_type, double lepton1_pt, double lepton1_eta,
                                                int lepton2_type, double lepton2_pt, double lepton2_eta,
                                                int lepton3_type, double lepton3_pt, double lepton3_eta,
                                                int lepton4_type, double lepton4_pt, double lepton4_eta)
{
  numElectrons_ = 0;
  if(lepton1_type == kElectron)
  {
    electron_pt_[numElectrons_] = lepton1_pt;
    electron_eta_[numElectrons_] = lepton1_eta;
    ++numElectrons_;
  }
  if(lepton2_type == kElectron)
  {
    electron_pt_[numElectrons_] = lepton2_pt;
    electron_eta_[numElectrons_] = lepton2_eta;
    ++numElectrons_;
  }
  if(lepton3_type == kElectron)
  {
    electron_pt_[numElectrons_] = lepton3_pt;
    electron_eta_[numElectrons_] = lepton3_eta;
    ++numElectrons_;
  }
  if(lepton4_type == kElectron)
  {
    electron_pt_[numElectrons_] = lepton4_pt;
    electron_eta_[numElectrons_] = lepton4_eta;
    ++numElectrons_;
  }

  numMuons_ = 0;
  if(lepton1_type == kMuon)
  {
    muon_pt_[numMuons_] = lepton1_pt;
    muon_eta_[numMuons_] = lepton1_eta;
    ++numMuons_;
  }
  if(lepton2_type == kMuon)
  {
    muon_pt_[numMuons_] = lepton2_pt;
    muon_eta_[numMuons_] = lepton2_eta;
    ++numMuons_;
  }
  if(lepton3_type == kMuon)
  {
    muon_pt_[numMuons_] = lepton3_pt;
    muon_eta_[numMuons_] = lepton3_eta;
    ++numMuons_;
  }
  if(lepton4_type == kMuon)
  {
    muon_pt_[numMuons_] = lepton4_pt;
    muon_eta_[numMuons_] = lepton4_eta;
    ++numMuons_;
  }

  numLeptons_ = 0;
  for(std::size_t idxElectron = 0; idxElectron < numElectrons_; ++idxElectron)
  {
    lepton_type_[numLeptons_] = kElectron;
    lepton_pt_[numLeptons_] = electron_pt_[idxElectron];
    lepton_eta_[numLeptons_] = electron_eta_[idxElectron];
    ++numLeptons_;
  }
  for(std::size_t idxMuon = 0; idxMuon < numMuons_; ++idxMuon)
  {
    lepton_type_[numLeptons_] = kMuon;
    lepton_pt_[numLeptons_] = muon_pt_[idxMuon];
    lepton_eta_[numLeptons_] = muon_eta_[idxMuon];
    ++numLeptons_;
  }
}

void
Data_to_MC_CorrectionInterface_Base::setHadTaus(int hadTau1_genPdgId, double hadTau1_pt, double hadTau1_eta,
                                                int hadTau2_genPdgId, double hadTau2_pt, double hadTau2_eta,
                                                int hadTau3_genPdgId, double hadTau3_pt, double hadTau3_eta,
                                                int hadTau4_genPdgId, double hadTau4_pt, double hadTau4_eta)
{
  numHadTaus_ = 0;
  if(hadTau1_pt > 0.)
  {
    hadTau_genPdgId_[numHadTaus_] = hadTau1_genPdgId;
    hadTau_pt_[numHadTaus_] = hadTau1_pt;
    hadTau_eta_[numHadTaus_] = hadTau1_eta;
    ++numHadTaus_;
  }
  if(hadTau2_pt > 0.)
  {
    hadTau_genPdgId_[numHadTaus_] = hadTau2_genPdgId;
    hadTau_pt_[numHadTaus_] = hadTau2_pt;
    hadTau_eta_[numHadTaus_] = hadTau2_eta;
    ++numHadTaus_;
  }
  if(hadTau3_pt > 0.)
  {
    hadTau_genPdgId_[numHadTaus_] = hadTau3_genPdgId;
    hadTau_pt_[numHadTaus_] = hadTau3_pt;
    hadTau_eta_[numHadTaus_] = hadTau3_eta;
    ++numHadTaus_;
  }
  if(hadTau4_pt > 0.)
  {
    hadTau_genPdgId_[numHadTaus_] = hadTau4_genPdgId;
    hadTau_pt_[numHadTaus_] = hadTau4_pt;
    hadTau_eta_[numHadTaus_] = hadTau4_eta;
    ++numHadTaus_;
  }
}

double
Data_to_MC_CorrectionInterface_Base::getWeight_leptonTriggerEff() const
{
  throw cmsException(this, __func__, __LINE__)
    << "Cannot call from base class"
  ;
}

double
Data_to_MC_CorrectionInterface_Base::getSF_leptonTriggerEff() const
{
  throw cmsException(this, __func__, __LINE__)
    << "Cannot call from base class"
  ;
}

double
Data_to_MC_CorrectionInterface_Base::getSF_leptonID_and_Iso(std::size_t numLeptons,
                                                            const std::vector<double> & lepton_pt,
                                                            const std::vector<double> & lepton_eta,
                                                            const std::vector<lutWrapperBase *> & corrections) const
{
  double sf = 1.;
  for(std::size_t idxLepton = 0; idxLepton < numLeptons; ++idxLepton)
  {
    const double pt = lepton_pt[idxLepton];
    const double eta = lepton_eta[idxLepton];
    sf *= get_from_lut(corrections, pt, eta);
  }
  return sf;
}

double
Data_to_MC_CorrectionInterface_Base::getSF_leptonID_and_Iso_loose() const
{
  const double sf =
    getSF_leptonID_and_Iso(numElectrons_, electron_pt_, electron_eta_, sfElectronID_and_Iso_loose_) *
    getSF_leptonID_and_Iso(numMuons_,     muon_pt_,     muon_eta_,     sfMuonID_and_Iso_loose_)
  ;
  return sf;
}

double
Data_to_MC_CorrectionInterface_Base::getSF_leptonID_and_Iso_fakeable_to_loose() const
{
  return 1.; // CV: no data/MC corrections for "fakeable" leptons determined yet
}

double
Data_to_MC_CorrectionInterface_Base::getSF_leptonID_and_Iso_tight_to_loose_woTightCharge() const
{
  const double sf =
    getSF_leptonID_and_Iso(numElectrons_, electron_pt_, electron_eta_, sfElectronID_and_Iso_tight_to_loose_woTightCharge_) *
    getSF_leptonID_and_Iso(numMuons_,     muon_pt_,     muon_eta_,     sfElectronID_and_Iso_tight_to_loose_woTightCharge_)
  ;
  return sf;
}

double
Data_to_MC_CorrectionInterface_Base::getSF_leptonID_and_Iso_tight_to_loose_wTightCharge() const
{
  const double sf =
    getSF_leptonID_and_Iso(numElectrons_, electron_pt_, electron_eta_, sfElectronID_and_Iso_tight_to_loose_wTightCharge_) *
    getSF_leptonID_and_Iso(numMuons_,     muon_pt_,     muon_eta_,     sfElectronID_and_Iso_tight_to_loose_wTightCharge_)
  ;
  return sf;
}

double
Data_to_MC_CorrectionInterface_Base::getSF_hadTauID_and_Iso() const
{
  throw cmsException(this, __func__, __LINE__)
    << "Cannot call from base class"
  ;
}

double
Data_to_MC_CorrectionInterface_Base::getSF_eToTauFakeRate() const
{
  throw cmsException(this, __func__, __LINE__)
    << "Cannot call from base class"
  ;
}

double
Data_to_MC_CorrectionInterface_Base::getSF_muToTauFakeRate() const
{
  throw cmsException(this, __func__, __LINE__)
    << "Cannot call from base class"
  ;
}
