#include "tthAnalysis/HiggsToTauTau/interface/Data_to_MC_CorrectionInterface_Base.h"

#include "tthAnalysis/HiggsToTauTau/interface/lutAuxFunctions.h" // get_from_lut()
#include "tthAnalysis/HiggsToTauTau/interface/leptonTypes.h" // kElectron, kMuon
#include "tthAnalysis/HiggsToTauTau/interface/data_to_MC_corrections_auxFunctions.h" // aux::
#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h" // cmsException()
#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // get_tau_id_wp_int()
#include "tthAnalysis/HiggsToTauTau/interface/RecoMuon.h" // RecoMuon
#include "tthAnalysis/HiggsToTauTau/interface/RecoElectron.h" // RecoElectron

#include "TauPOG/TauIDSFs/interface/TauIDSFTool.h" // TauIDSFTool

#include <TString.h> // Form()
#include <TFile.h> // TFile

#include <boost/algorithm/string/predicate.hpp> // boost::ends_with(), boost::starts_with()

#include <cassert> // assert()

#include <iostream>

namespace
{
  constexpr double
  square(double x)
  {
    return x * x;
  }
}

Data_to_MC_CorrectionInterface_Base::Data_to_MC_CorrectionInterface_Base(const edm::ParameterSet & cfg)
  : hadTauSelection_(-1)
  , hadTauId_(TauID::DeepTau2017v2VSjet)
  , tauIdSFs_(nullptr)
  , applyHadTauSF_(true)
  , isDEBUG_(cfg.exists("isDEBUG") ? cfg.getParameter<bool>("isDEBUG") : false)
  , numLeptons_(0)
  , numElectrons_(0)
  , numMuons_(0)
  , numHadTaus_(0)
{
  const std::string hadTauSelection_string = cfg.getParameter<std::string>("hadTauSelection");
  applyHadTauSF_ = hadTauSelection_string != "disabled";
  if(applyHadTauSF_)
  {
    setHadTauSelection(hadTauSelection_string);
  }

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

  if(applyHadTauSF_)
  {
    if(hadTauId_ == TauID::DeepTau2017v2VSjet)
    {
      tauIDSF_str_ = "DeepTau2017v2p1VSjet";
      tauIDSF_level_str_ = TauID_level_strings.at(TauID_levels.at(hadTauId_)).at(hadTauSelection_);
    }
    else if(hadTauId_ == TauID::MVAoldDM2017v2     ||
            hadTauId_ == TauID::MVAoldDMdR032017v2  )
    {
      tauIDSF_str_ = "MVAoldDM2017v2";
      tauIDSF_level_str_ = TauID_level_strings.at(TauID_levels.at(hadTauId_)).at(std::max(1, hadTauSelection_));
    }
    else
    {
      throw cmsException(this, __func__, __LINE__) << "Invalid tau ID: " << as_integer(hadTauId_);
    }
  }
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
  if(applyHadTauSF_)
  {
    delete tauIdSFs_;
    for(auto & kv: tauIDSFs_antiEle_)
    {
      delete kv.second;
    }
    for(auto & kv: tauIDSFs_antiMu_)
    {
      delete kv.second;
    }
  }
}

void
Data_to_MC_CorrectionInterface_Base::setHadTauSelection(const std::string & hadTauSelection)
{
  hadTauSelection_ = get_tau_id_wp_int(hadTauSelection);
  hadTauId_ = get_tau_id_enum(hadTauSelection);
}

void
Data_to_MC_CorrectionInterface_Base::setLeptons(const std::vector<const RecoLepton *> & leptons,
                                                bool requireChargeMatch)
{
  numLeptons_ = 0;
  numMuons_ = 0;
  numElectrons_ = 0;

  lepton_type_.clear();
  lepton_pt_.clear();
  lepton_cone_pt_.clear();
  lepton_eta_.clear();

  muon_pt_.clear();
  muon_cone_pt_.clear();
  muon_eta_.clear();
  muon_isGenMatched_.clear();

  electron_pt_.clear();
  electron_cone_pt_.clear();
  electron_eta_.clear();
  electron_isGenMatched_.clear();

  for(const RecoLepton * const lepton: leptons)
  {
    lepton_pt_.push_back(lepton->pt());
    lepton_eta_.push_back(lepton->eta());
    ++numLeptons_;

    const RecoMuon * const muon = dynamic_cast<const RecoMuon * const>(lepton);
    const RecoElectron * const electron = dynamic_cast<const RecoElectron * const>(lepton);
    if(muon)
    {
      const double cone_pt = muon->cone_pt();
      lepton_type_.push_back(kMuon);
      lepton_cone_pt_.push_back(cone_pt);

      muon_pt_.push_back(muon->pt());
      muon_cone_pt_.push_back(cone_pt);
      muon_eta_.push_back(muon->eta());
      muon_isGenMatched_.push_back(muon->isGenMatched(requireChargeMatch));
      ++numMuons_;
    }
    else if(electron)
    {
      const double cone_pt = electron->cone_pt();
      lepton_type_.push_back(kElectron);
      lepton_cone_pt_.push_back(cone_pt);

      electron_pt_.push_back(electron->pt());
      electron_cone_pt_.push_back(cone_pt);
      electron_eta_.push_back(electron->eta());
      electron_isGenMatched_.push_back(electron->isGenMatched(requireChargeMatch) && electron->genLepton()); // [*]
      ++numElectrons_;
      // [*] isGenMatched() can also return true if the reconstructed electron is matched to a generator level photon
    }
    else
    {
      assert(0);
    }
  }
}

void
Data_to_MC_CorrectionInterface_Base::setHadTaus(const std::vector<const RecoHadTau *> & hadTaus)
{
  numHadTaus_ = 0;
  hadTau_genPdgId_.clear();
  hadTau_pt_.clear();
  hadTau_absEta_.clear();
  for(const RecoHadTau * const hadTau: hadTaus)
  {
    hadTau_genPdgId_[numHadTaus_] = getHadTau_genPdgId(hadTau);
    hadTau_pt_[numHadTaus_] = hadTau->pt();
    hadTau_absEta_[numHadTaus_] = hadTau->absEta();
    ++numHadTaus_;
  }
}

double
Data_to_MC_CorrectionInterface_Base::getSF_leptonTriggerEff(TriggerSFsys central_or_shift) const
{
  throw cmsException(this, __func__, __LINE__)
    << "Cannot call from base class"
  ;
}

double
Data_to_MC_CorrectionInterface_Base::getSF_leptonID_and_Iso(std::size_t numLeptons,
                                                            const std::vector<double> & lepton_pt,
                                                            const std::vector<double> & lepton_eta,
                                                            const std::vector<bool> & lepton_isGenMatched,
                                                            const std::vector<lutWrapperBase *> & corrections,
                                                            int error_shift) const
{
  double sf = 1.;
  for(std::size_t idxLepton = 0; idxLepton < numLeptons; ++idxLepton)
  {
    if(! lepton_isGenMatched[idxLepton])
    {
      continue;
    }
    sf *= get_from_lut_err(corrections, lepton_pt[idxLepton], lepton_eta[idxLepton], error_shift, isDEBUG_);
  }
  return sf;
}

void
Data_to_MC_CorrectionInterface_Base::initAntiEle_tauIDSFs(const std::string & era_str)
{
  return init_tauIDSFs(era_str, tauIDSFs_antiEle_, "antiEleMVA6", 5);
}

void
Data_to_MC_CorrectionInterface_Base::initAntiMu_tauIDSFs(const std::string & era_str)
{
  return init_tauIDSFs(era_str, tauIDSFs_antiMu_, "antiMu3", 2);
}

void
Data_to_MC_CorrectionInterface_Base::init_tauIDSFs(const std::string & era_str,
                                                   std::map<int, TauIDSFTool *> & tauIDSF_map,
                                                   const std::string & tauID_str,
                                                   int nof_levels)
{
  const std::vector<std::string> levels = TauID_level_strings.at(nof_levels);
  for(int level = 0; level < nof_levels; ++level)
  {
    tauIDSF_map[level + 1] = new TauIDSFTool(era_str, tauID_str, levels.at(level), false);
  }
}

bool
Data_to_MC_CorrectionInterface_Base::check_triggerSFsys_opt(TriggerSFsys central_or_shift) const
{
  if(central_or_shift == TriggerSFsys::central ||
     central_or_shift == TriggerSFsys::shiftUp ||
     central_or_shift == TriggerSFsys::shiftDown)
  {
    return true;
  }
  if(central_or_shift == TriggerSFsys::shift_2lssUp      ||
     central_or_shift == TriggerSFsys::shift_2lssDown    ||
     central_or_shift == TriggerSFsys::shift_2lssEEUp    ||
     central_or_shift == TriggerSFsys::shift_2lssEEDown  ||
     central_or_shift == TriggerSFsys::shift_2lssEMuUp   ||
     central_or_shift == TriggerSFsys::shift_2lssEMuDown ||
     central_or_shift == TriggerSFsys::shift_2lssMuMuUp  ||
     central_or_shift == TriggerSFsys::shift_2lssMuMuDown)
  {
    return (numElectrons_ + numMuons_) <= 2 && numHadTaus_ <= 2;
  }
  if(central_or_shift == TriggerSFsys::shift_3lUp ||
     central_or_shift == TriggerSFsys::shift_3lDown)
  {
    return (numElectrons_ + numMuons_) >= 3 && numHadTaus_ <= 1;
  }
  return false;
}

double
Data_to_MC_CorrectionInterface_Base::comp_triggerSFsys_opt(double sf,
                                                           double sfErr,
                                                           TriggerSFsys central_or_shift) const
{
  if(central_or_shift == TriggerSFsys::central ||
     ((central_or_shift == TriggerSFsys::shift_2lssEEUp   || central_or_shift == TriggerSFsys::shift_2lssEEDown  ) && (numElectrons_ != 2 || numMuons_ != 0)) ||
     ((central_or_shift == TriggerSFsys::shift_2lssEMuUp  || central_or_shift == TriggerSFsys::shift_2lssEMuDown ) && (numElectrons_ != 1 || numMuons_ != 1)) ||
     ((central_or_shift == TriggerSFsys::shift_2lssMuMuUp || central_or_shift == TriggerSFsys::shift_2lssMuMuDown) && (numElectrons_ != 0 || numMuons_ != 2)))
  {
    return sf;
  }
  else if(central_or_shift == TriggerSFsys::shiftUp          ||
          central_or_shift == TriggerSFsys::shift_2lssUp     ||
          central_or_shift == TriggerSFsys::shift_2lssEEUp   ||
          central_or_shift == TriggerSFsys::shift_2lssEMuUp  ||
          central_or_shift == TriggerSFsys::shift_2lssMuMuUp ||
          central_or_shift == TriggerSFsys::shift_3lUp)
  {
    return sf * (1. + sfErr);
  }
  else if(central_or_shift == TriggerSFsys::shiftDown          ||
          central_or_shift == TriggerSFsys::shift_2lssDown     ||
          central_or_shift == TriggerSFsys::shift_2lssEEDown   ||
          central_or_shift == TriggerSFsys::shift_2lssEMuDown  ||
          central_or_shift == TriggerSFsys::shift_2lssMuMuDown ||
          central_or_shift == TriggerSFsys::shift_3lDown)
  {
    return sf * (1. - sfErr);
  }
  throw cmsException(this, __func__, __LINE__) << "Invalid option: " << static_cast<int>(central_or_shift);
}

double
Data_to_MC_CorrectionInterface_Base::getSF_leptonID_and_Iso_loose(LeptonIDSFsys central_or_shift) const
{
  if(isDEBUG_)
  {
    std::cout << get_human_line(this, __func__, __LINE__) << "Computing SF for electrons\n";
  }
  int sf_el_error = 0;
  if(central_or_shift == LeptonIDSFsys::elLooseUp)
  {
    sf_el_error = +1;
  }
  else if(central_or_shift == LeptonIDSFsys::elLooseDown)
  {
    sf_el_error = -1;
  }
  const double sf_el = getSF_leptonID_and_Iso(
    numElectrons_, electron_pt_, electron_eta_, electron_isGenMatched_, sfElectronID_and_Iso_loose_, sf_el_error
  );
  if(isDEBUG_)
  {
    std::cout
      << "Final SF for electrons: " << sf_el << '\n'
      << get_human_line(this, __func__, __LINE__) << "Computing SF for muons\n"
    ;
  }

  int sf_mu_error = 0;
  if(central_or_shift == LeptonIDSFsys::muLooseUp)
  {
    sf_mu_error = +1;
  }
  else if(central_or_shift == LeptonIDSFsys::muLooseDown)
  {
    sf_mu_error = -1;
  }
  const double sf_mu = getSF_leptonID_and_Iso(
    numMuons_, muon_pt_, muon_eta_, muon_isGenMatched_, sfMuonID_and_Iso_loose_, sf_mu_error
  );
  const double sf = sf_el * sf_mu;
  if(isDEBUG_)
  {
    std::cout
      << "Final SF for muons: " << sf_mu << "\n"
         "Final SF: " << sf << '\n'
    ;
  }
  return sf;
}

double
Data_to_MC_CorrectionInterface_Base::getSF_leptonID_and_Iso_looseToFakeable() const
{
  return 1.; // CV: no data/MC corrections for "fakeable" leptons determined yet
}

double
Data_to_MC_CorrectionInterface_Base::getSF_leptonID_and_Iso_tight_to_loose_woTightCharge(LeptonIDSFsys central_or_shift) const
{
  if(isDEBUG_)
  {
    std::cout << get_human_line(this, __func__, __LINE__) << "Computing SF for electrons\n";
  }
  double sf_el = getSF_leptonID_and_Iso(
    numElectrons_, electron_pt_, electron_eta_, electron_isGenMatched_, sfElectronID_and_Iso_tight_to_loose_woTightCharge_, 0
  );
  if(isDEBUG_)
  {
    std::cout << get_human_line(this, __func__, __LINE__) << "Computing SF errors for electrons\n";
  }
  if(central_or_shift == LeptonIDSFsys::elTightUp)
  {
    sf_el *= getSF_leptonID_and_Iso(
      numElectrons_, electron_pt_, electron_eta_, electron_isGenMatched_, sfElectronID_and_Iso_tight_to_loose_errors_up_, 0
    );
  }
  else if(central_or_shift == LeptonIDSFsys::elTightDown)
  {
    sf_el *= getSF_leptonID_and_Iso(
      numElectrons_, electron_pt_, electron_eta_, electron_isGenMatched_, sfElectronID_and_Iso_tight_to_loose_errors_down_, 0
    );
  }
  if(isDEBUG_)
  {
    std::cout
      << "Final SF for electrons: " << sf_el << '\n'
      << get_human_line(this, __func__, __LINE__) << "Computing SF for muons\n"
    ;
  }

  double sf_mu = getSF_leptonID_and_Iso(
    numMuons_, muon_pt_, muon_eta_, muon_isGenMatched_, sfMuonID_and_Iso_tight_to_loose_woTightCharge_, 0
  );
  if(isDEBUG_)
  {
    std::cout << get_human_line(this, __func__, __LINE__) << "Computing SF errors for muons\n";
  }
  if(central_or_shift == LeptonIDSFsys::muTightUp)
  {
    sf_mu *= getSF_leptonID_and_Iso(
      numMuons_, muon_pt_, muon_eta_, muon_isGenMatched_, sfMuonID_and_Iso_tight_to_loose_errors_up_, 0
    );
  }
  else if(central_or_shift == LeptonIDSFsys::muTightDown)
  {
    sf_mu *= getSF_leptonID_and_Iso(
      numMuons_, muon_pt_, muon_eta_, muon_isGenMatched_, sfMuonID_and_Iso_tight_to_loose_errors_down_, 0
    );
  }
  const double sf = sf_el * sf_mu;
  if(isDEBUG_)
  {
    std::cout
      << "Final SF for muons: " << sf_mu << "\n"
         "Final SF: " << sf << '\n'
    ;
  }
  return sf;
}

double
Data_to_MC_CorrectionInterface_Base::getSF_leptonID_and_Iso_tight_to_loose_wTightCharge(LeptonIDSFsys central_or_shift) const
{
  if(isDEBUG_)
  {
    std::cout << get_human_line(this, __func__, __LINE__) << "Computing SF for electrons\n";
  }
  double sf_el = getSF_leptonID_and_Iso(
    numElectrons_, electron_pt_, electron_eta_, electron_isGenMatched_, sfElectronID_and_Iso_tight_to_loose_wTightCharge_, 0
  );
  if(isDEBUG_)
  {
    std::cout << get_human_line(this, __func__, __LINE__) << "Computing SF errors for electrons\n";
  }
  if(central_or_shift == LeptonIDSFsys::elTightUp)
  {
    sf_el *= getSF_leptonID_and_Iso(
      numElectrons_, electron_pt_, electron_eta_, electron_isGenMatched_, sfElectronID_and_Iso_tight_to_loose_errors_up_, 0
    );
  }
  else if(central_or_shift == LeptonIDSFsys::elTightDown)
  {
    sf_el *= getSF_leptonID_and_Iso(
      numElectrons_, electron_pt_, electron_eta_, electron_isGenMatched_, sfElectronID_and_Iso_tight_to_loose_errors_down_, 0
    );
  }
  if(isDEBUG_)
  {
    std::cout
      << "Final SF for electrons: " << sf_el << '\n'
      << get_human_line(this, __func__, __LINE__) << "Computing SF for muons\n"
    ;
  }

  double sf_mu = getSF_leptonID_and_Iso(
    numMuons_, muon_pt_, muon_eta_, muon_isGenMatched_, sfMuonID_and_Iso_tight_to_loose_wTightCharge_, 0
  );
  if(isDEBUG_)
  {
    std::cout << get_human_line(this, __func__, __LINE__) << "Computing SF errors for muons\n";
  }
  if(central_or_shift == LeptonIDSFsys::muTightUp)
  {
    sf_mu *= getSF_leptonID_and_Iso(
      numMuons_, muon_pt_, muon_eta_, muon_isGenMatched_, sfMuonID_and_Iso_tight_to_loose_errors_up_, 0
    );
  }
  else if(central_or_shift == LeptonIDSFsys::muTightDown)
  {
    sf_mu *= getSF_leptonID_and_Iso(
      numMuons_, muon_pt_, muon_eta_, muon_isGenMatched_, sfMuonID_and_Iso_tight_to_loose_errors_down_, 0
    );
  }
  const double sf = sf_el * sf_mu;
  if(isDEBUG_)
  {
    std::cout
      << "Final SF for muons: " << sf_mu << "\n"
         "Final SF: " << sf << '\n'
    ;
  }
  return sf;
}

double
Data_to_MC_CorrectionInterface_Base::getSF_hadTauID_and_Iso(TauIDSFsys central_or_shift) const
{
  double sf = 1.;
  if(applyHadTauSF_)
  {
    for(std::size_t idxHadTau = 0; idxHadTau < numHadTaus_; ++idxHadTau)
    {
      if(hadTau_genPdgId_[idxHadTau] == 15)
      {
        // because we use looser anti-e/mu DeepTau ID WPs compared to the WPs used in the tau ID SF measurement,
        // we have to add additional 3% or 15% uncertainty to the tau ID SF depending on the tau pT, as explained here:
        // https://indico.cern.ch/event/880308/contributions/3708888/attachments/1972379/3281439/NewsRun2SFsRecommendation.pdf
        const double sf_central = tauIdSFs_->getSFvsPT(hadTau_pt_[idxHadTau]);
        const double sf_up      = tauIdSFs_->getSFvsPT(hadTau_pt_[idxHadTau], "Up");
        const double sf_down    = tauIdSFs_->getSFvsPT(hadTau_pt_[idxHadTau], "Down");
        const double sf_unc = hadTau_pt_[idxHadTau] > 100. ? 0.15 : 0.03;
        const double sf_unc_up   = std::sqrt(square(sf_up   / sf_central - 1.) + square(sf_unc));
        const double sf_unc_down = std::sqrt(square(sf_down / sf_central - 1.) + square(sf_unc));
        switch(central_or_shift)
        {
          case TauIDSFsys::central:   sf *= sf_central;                      break;
          case TauIDSFsys::shiftUp:   sf *= sf_central * (1. + sf_unc_up);   break;
          case TauIDSFsys::shiftDown: sf *= sf_central * (1. - sf_unc_down); break;
        }
      }
    }
  }
  return sf;
}

double
Data_to_MC_CorrectionInterface_Base::getSF_eToTauFakeRate(FRet central_or_shift) const
{
  double sf = 1.;
  if(applyHadTauSF_)
  {
    for(std::size_t idxHadTau = 0; idxHadTau < numHadTaus_; ++idxHadTau)
    {
      const int hadTauSelection_antiElectron = hadTauSelection_antiElectron_[idxHadTau];
      const int hadTau_genPdgId = std::abs(hadTau_genPdgId_[idxHadTau]);
      if(hadTauSelection_antiElectron > 0 && hadTau_genPdgId  == 11)
      {
        if(! tauIDSFs_antiEle_.count(hadTauSelection_antiElectron))
        {
          throw cmsException(this, __func__, __LINE__) << "Anti-e SFs not initalized for WP " << hadTauSelection_antiElectron;
        }
        const TauIDSFTool * const tauIDSF_antiEle = tauIDSFs_antiEle_.at(hadTauSelection_antiElectron);

        switch(central_or_shift)
        {
          case FRet::shiftUp:   sf *= tauIDSF_antiEle->getSFvsEta(hadTau_absEta_[idxHadTau], 1, "Up");   break;
          case FRet::shiftDown: sf *= tauIDSF_antiEle->getSFvsEta(hadTau_absEta_[idxHadTau], 1, "Down"); break;
          case FRet::central:   sf *= tauIDSF_antiEle->getSFvsEta(hadTau_absEta_[idxHadTau], 1);         break;
        }
      }
    }
  }
  return sf;
}

double
Data_to_MC_CorrectionInterface_Base::getSF_muToTauFakeRate(FRmt central_or_shift) const
{
  double sf = 1.;
  if(applyHadTauSF_)
  {
    for(std::size_t idxHadTau = 0; idxHadTau < numHadTaus_; ++idxHadTau)
    {
      const int hadTauSelection_antiMuon = hadTauSelection_antiMuon_[idxHadTau];
      const int hadTau_genPdgId = std::abs(hadTau_genPdgId_[idxHadTau]);
      if(hadTauSelection_antiMuon > 0 && hadTau_genPdgId  == 13)
      {
        if(! tauIDSFs_antiMu_.count(hadTauSelection_antiMuon))
        {
          throw cmsException(this, __func__, __LINE__) << "Anti-mu SFs not initalized for WP " << hadTauSelection_antiMuon;
        }
        const TauIDSFTool * const tauIDSF_antiMu = tauIDSFs_antiMu_.at(hadTauSelection_antiMuon);

        switch(central_or_shift)
        {
          case FRmt::shiftUp:   sf *= tauIDSF_antiMu->getSFvsEta(hadTau_absEta_[idxHadTau], 2, "Up");   break;
          case FRmt::shiftDown: sf *= tauIDSF_antiMu->getSFvsEta(hadTau_absEta_[idxHadTau], 2, "Down"); break;
          case FRmt::central:   sf *= tauIDSF_antiMu->getSFvsEta(hadTau_absEta_[idxHadTau], 2);         break;
        }
      }
    }
  }
  return sf;
}
