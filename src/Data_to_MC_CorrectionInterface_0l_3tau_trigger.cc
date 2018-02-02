#include "tthAnalysis/HiggsToTauTau/interface/Data_to_MC_CorrectionInterface_0l_3tau_trigger.h"

#include "tthAnalysis/HiggsToTauTau/interface/leptonTypes.h" // kElectron, kMuon
#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // kEra_2017
#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h" // cmsException()
#include "tthAnalysis/HiggsToTauTau/interface/data_to_MC_corrections_auxFunctions.h" // aux::

#include <TString.h> // Form()

#include <boost/algorithm/string/predicate.hpp> // boost::ends_with()

#include <cassert> // assert()

Data_to_MC_CorrectionInterface_0l_3tau_trigger::Data_to_MC_CorrectionInterface_0l_3tau_trigger(const edm::ParameterSet& cfg)
  : hadTauSelection_(cfg.getParameter<std::string>("hadTauSelection"))
  , isDEBUG_(cfg.exists("isDEBUG") ? cfg.getParameter<bool>("isDEBUG") : false)
  , hadTau1_genPdgId_(-1)
  , hadTau1_pt_(0.)
  , hadTau1_eta_(0.)
  , hadTau1_decayMode_(-1)
  , hadTau2_genPdgId_(-1)
  , hadTau2_pt_(0.)
  , hadTau2_eta_(0.)
  , hadTau2_decayMode_(-1)
  , hadTau3_genPdgId_(-1)
  , hadTau3_pt_(0.)
  , hadTau3_eta_(0.)
  , hadTau3_decayMode_(-1)
{
  const std::string era_string = cfg.getParameter<std::string>("era");
  if(era_string == "2017")
  {
    era_ = kEra_2017;
  }
  else
  {
    throw cmsException(this) << "Invalid Configuration parameter 'era' = " << era_string;
  }

  const std::string central_or_shift = cfg.getParameter<std::string>("central_or_shift");
  if(central_or_shift != "central" )
  {
    std::string shiftUp_or_Down;
    if(boost::ends_with(central_or_shift, "Up"))
    {
      shiftUp_or_Down = "Up";
    }
    else if(boost::ends_with(central_or_shift, "Down"))
    {
      shiftUp_or_Down = "Down";
    }
    else
    {
      throw cmsException(this)
              << "Invalid Configuration parameter 'central_or_shift' = " << central_or_shift;
    }
    // CV: no systematic uncertainties on data/MC corrections for trigger efficiency in 1l_2tau category defined yet
  }

  const edm::ParameterSet cfg_triggerSF_2tau = cfg.getParameter<edm::ParameterSet>("triggerSF_2tau");
  const std::string hadTauSelectionLabel_str = aux::getHadTauSelectionLabel(hadTauSelection_);
  const char * hadTauSelectionLabel = hadTauSelectionLabel_str.data();
  const std::vector<int> hadTauDecayModes_2tau_perLeg = { 0, 1, 2, 10 };

  for(int hadTauDecayMode: hadTauDecayModes_2tau_perLeg)
  {
    const std::string hadTauDecayModeLabel_str = aux::getHadTauDecayModeLabel(hadTauDecayMode);
    const char * hadTauDecayModeLabel = hadTauDecayModeLabel_str.data();

    const std::string fitName_2tau_data_gentau = Form("data_genuine_%s_%s", hadTauSelectionLabel, hadTauDecayModeLabel);
    const edm::ParameterSet cfg_fit_2tau_data_gentau = cfg_triggerSF_2tau.getParameter<edm::ParameterSet>(fitName_2tau_data_gentau);
    effTrigger_2tau_perLeg_data_gentau_[hadTauDecayMode].push_back(new lutWrapperCrystalBall(
      fitName_2tau_data_gentau, cfg_fit_2tau_data_gentau, lut::kXpt, 20., 170.
    ));

    const std::string fitName_2tau_data_faketau = Form("data_fake_%s_%s", hadTauSelectionLabel, hadTauDecayModeLabel);
    const edm::ParameterSet cfg_fit_2tau_data_faketau = cfg_triggerSF_2tau.getParameter<edm::ParameterSet>(fitName_2tau_data_faketau);
    effTrigger_2tau_perLeg_data_faketau_[hadTauDecayMode].push_back(new lutWrapperCrystalBall(
      fitName_2tau_data_faketau, cfg_fit_2tau_data_faketau, lut::kXpt, 20., 170.
    ));

    const std::string fitName_2tau_mc_gentau = Form("mc_genuine_%s_%s", hadTauSelectionLabel, hadTauDecayModeLabel);
    const edm::ParameterSet cfg_fit_2tau_mc_gentau = cfg_triggerSF_2tau.getParameter<edm::ParameterSet>(fitName_2tau_mc_gentau);
    effTrigger_2tau_perLeg_mc_gentau_[hadTauDecayMode].push_back(new lutWrapperCrystalBall(
      fitName_2tau_mc_gentau, cfg_fit_2tau_mc_gentau, lut::kXpt, 20., 170.
    ));

    const std::string fitName_2tau_mc_faketau = Form("mc_fake_%s_%s", hadTauSelectionLabel, hadTauDecayModeLabel);
    const edm::ParameterSet cfg_fit_2tau_mc_faketau = cfg_triggerSF_2tau.getParameter<edm::ParameterSet>(fitName_2tau_mc_faketau);
    effTrigger_2tau_perLeg_mc_faketau_[hadTauDecayMode].push_back(new lutWrapperCrystalBall(
      fitName_2tau_mc_faketau, cfg_fit_2tau_mc_faketau, lut::kXpt, 20., 170.
    ));
  }
}

Data_to_MC_CorrectionInterface_0l_3tau_trigger::~Data_to_MC_CorrectionInterface_0l_3tau_trigger()
{
  aux::clearCollection(effTrigger_2tau_perLeg_data_gentau_);
  aux::clearCollection(effTrigger_2tau_perLeg_data_faketau_);
  aux::clearCollection(effTrigger_2tau_perLeg_mc_gentau_);
  aux::clearCollection(effTrigger_2tau_perLeg_mc_faketau_);
}

void Data_to_MC_CorrectionInterface_0l_3tau_trigger::setTriggerBits(bool isTriggered_2tau)
{
  isTriggered_2tau_ = isTriggered_2tau;
}

void Data_to_MC_CorrectionInterface_0l_3tau_trigger::setHadTaus(int hadTau1_genPdgId, double hadTau1_pt, double hadTau1_eta, int hadTau1_decayMode,
                                                                int hadTau2_genPdgId, double hadTau2_pt, double hadTau2_eta, int hadTau2_decayMode,
                                                                int hadTau3_genPdgId, double hadTau3_pt, double hadTau3_eta, int hadTau3_decayMode)
{
  hadTau1_genPdgId_  = hadTau1_genPdgId;
  hadTau1_pt_        = hadTau1_pt;
  hadTau1_eta_       = hadTau1_eta;
  hadTau1_decayMode_ = hadTau1_decayMode;

  hadTau2_genPdgId_  = hadTau2_genPdgId;
  hadTau2_pt_        = hadTau2_pt;
  hadTau2_eta_       = hadTau2_eta;
  hadTau2_decayMode_ = hadTau2_decayMode;

  hadTau3_genPdgId_  = hadTau3_genPdgId;
  hadTau3_pt_        = hadTau3_pt;
  hadTau3_eta_       = hadTau3_eta;
  hadTau3_decayMode_ = hadTau3_decayMode;
}

double
Data_to_MC_CorrectionInterface_0l_3tau_trigger::getWeight_triggerEff() const
{
  assert(0);
}

double
Data_to_MC_CorrectionInterface_0l_3tau_trigger::getSF_triggerEff() const
{
  if(isDEBUG_)
  {
    std::cout << "<Data_to_MC_CorrectionInterface_0l_3tau_trigger::getSF_triggerEff>:" << std::endl;
  }

  double eff_2tau_tau1_data = 0.;
  double eff_2tau_tau1_mc   = 0.;
  double eff_2tau_tau2_data = 0.;
  double eff_2tau_tau2_mc   = 0.;
  double eff_2tau_tau3_data = 0.;
  double eff_2tau_tau3_mc   = 0.;

  const bool hadTau1_isGenTau = (hadTau1_genPdgId_ == 11 || hadTau1_genPdgId_ == 13 || hadTau1_genPdgId_ == 15);
  const bool hadTau2_isGenTau = (hadTau2_genPdgId_ == 11 || hadTau2_genPdgId_ == 13 || hadTau2_genPdgId_ == 15);
  const bool hadTau3_isGenTau = (hadTau3_genPdgId_ == 11 || hadTau3_genPdgId_ == 13 || hadTau3_genPdgId_ == 15);

  if(hadTau1_isGenTau)
  {
    eff_2tau_tau1_data = aux::get_from_lut(effTrigger_2tau_perLeg_data_gentau_, hadTau1_pt_, hadTau1_eta_, hadTau1_decayMode_, isDEBUG_);
    eff_2tau_tau1_mc   = aux::get_from_lut(effTrigger_2tau_perLeg_mc_gentau_,   hadTau1_pt_, hadTau1_eta_, hadTau1_decayMode_, isDEBUG_);
  }
  else
  {
    eff_2tau_tau1_data = aux::get_from_lut(effTrigger_2tau_perLeg_data_faketau_, hadTau1_pt_, hadTau1_eta_, hadTau1_decayMode_, isDEBUG_);
    eff_2tau_tau1_mc   = aux::get_from_lut(effTrigger_2tau_perLeg_mc_faketau_,   hadTau1_pt_, hadTau1_eta_, hadTau1_decayMode_, isDEBUG_);
  }

  if(hadTau2_isGenTau)
  {
    eff_2tau_tau2_data = aux::get_from_lut(effTrigger_2tau_perLeg_data_gentau_, hadTau2_pt_, hadTau2_eta_, hadTau2_decayMode_, isDEBUG_);
    eff_2tau_tau2_mc   = aux::get_from_lut(effTrigger_2tau_perLeg_mc_gentau_,   hadTau2_pt_, hadTau2_eta_, hadTau2_decayMode_, isDEBUG_);
  }
  else
  {
    eff_2tau_tau2_data = aux::get_from_lut(effTrigger_2tau_perLeg_data_faketau_, hadTau2_pt_, hadTau2_eta_, hadTau2_decayMode_, isDEBUG_);
    eff_2tau_tau2_mc   = aux::get_from_lut(effTrigger_2tau_perLeg_mc_faketau_,   hadTau2_pt_, hadTau2_eta_, hadTau2_decayMode_, isDEBUG_);
  }

  if(std::fabs(hadTau3_eta_) < 2.1)
  {
    if(hadTau3_isGenTau)
    {
      eff_2tau_tau3_data = aux::get_from_lut(effTrigger_2tau_perLeg_data_gentau_, hadTau3_pt_, hadTau3_eta_, hadTau3_decayMode_, isDEBUG_);
      eff_2tau_tau3_mc   = aux::get_from_lut(effTrigger_2tau_perLeg_mc_gentau_,   hadTau3_pt_, hadTau3_eta_, hadTau3_decayMode_, isDEBUG_);
    }
    else
    {
      eff_2tau_tau3_data = aux::get_from_lut(effTrigger_2tau_perLeg_data_faketau_, hadTau3_pt_, hadTau3_eta_, hadTau3_decayMode_, isDEBUG_);
      eff_2tau_tau3_mc   = aux::get_from_lut(effTrigger_2tau_perLeg_mc_faketau_,   hadTau3_pt_, hadTau3_eta_, hadTau3_decayMode_, isDEBUG_);
    }
  }
  double eff_2tau_data =
    eff_2tau_tau1_data        * eff_2tau_tau2_data        * (1. - eff_2tau_tau3_data) +
    eff_2tau_tau1_data        * (1. - eff_2tau_tau2_data) * eff_2tau_tau3_data        +
    (1. - eff_2tau_tau1_data) * eff_2tau_tau2_data        * eff_2tau_tau3_data        +
    eff_2tau_tau1_data        * eff_2tau_tau2_data        * eff_2tau_tau3_data
  ;
  eff_2tau_data = std::min(std::max(eff_2tau_data, 0.), 1.);

  double eff_2tau_mc =
    eff_2tau_tau1_mc        * eff_2tau_tau2_mc        * (1. - eff_2tau_tau3_mc) +
    eff_2tau_tau1_mc        * (1. - eff_2tau_tau2_mc) * eff_2tau_tau3_mc        +
    (1. - eff_2tau_tau1_mc) * eff_2tau_tau2_mc        * eff_2tau_tau3_mc        +
    eff_2tau_tau1_mc        * eff_2tau_tau2_mc        * eff_2tau_tau3_mc
  ;
  eff_2tau_mc = std::min(std::max(eff_2tau_mc, 0.), 1.);

  if(isDEBUG_)
  {
    std::cout << "hadTau (lead):    pT = " << hadTau1_pt_ << ", eta = " << hadTau1_eta_ << "\n"
                 "hadTau (sublead): pT = " << hadTau2_pt_ << ", eta = " << hadTau2_eta_ << "\n"
                 "hadTau (third):   pT = " << hadTau3_pt_ << ", eta = " << hadTau3_eta_ << '\n';
  }

  double sf = 1.;
  if(isTriggered_2tau_)
  {
    sf = aux::compSF(eff_2tau_data, eff_2tau_mc);
    if(isDEBUG_)
    {
      std::cout << " eff: data = " << eff_2tau_data << ", MC = " << eff_2tau_mc << " --> SF = " << sf << '\n';
    }
  }
  else
  {
    sf = 0.;
    if(isDEBUG_)
    {
      std::cout << "neither single lepton trigger nor lepton+tau cross trigger fires\n"
                   "--> setting SF = " << sf << '\n';
    }      
  }

  return sf;
}
