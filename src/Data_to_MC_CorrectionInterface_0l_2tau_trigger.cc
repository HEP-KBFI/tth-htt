#include "tthAnalysis/HiggsToTauTau/interface/Data_to_MC_CorrectionInterface_0l_2tau_trigger.h"

#include "tthAnalysis/HiggsToTauTau/interface/leptonTypes.h" // kElectron, kMuon
#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // kEra_2017
#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h" // cmsException()
#include "tthAnalysis/HiggsToTauTau/interface/data_to_MC_corrections_auxFunctions.h" // aux::
#include "tthAnalysis/HiggsToTauTau/interface/sysUncertOptions.h" // TriggerSFsys, getTriggerSF_option()
#include "tthAnalysis/HiggsToTauTau/interface/lutAuxFunctions.h" // get_from_lut()

#include <TString.h> // Form()
#include <TMath.h> // TMath::Abs()

#include <boost/algorithm/string/predicate.hpp> // boost::ends_with()

#include <cassert> // assert()

Data_to_MC_CorrectionInterface_0l_2tau_trigger::Data_to_MC_CorrectionInterface_0l_2tau_trigger(const edm::ParameterSet & cfg)
  : effTrigger_tauLeg_(nullptr)
  , era_(get_era(cfg.getParameter<std::string>("era")))
  , hadTauSelection_(cfg.getParameter<std::string>("hadTauSelection"))
  , isDEBUG_(cfg.exists("isDEBUG") ? cfg.getParameter<bool>("isDEBUG") : false)
  , triggerSF_option_(TauTriggerSFs2017::kCentral)
  , hadTau1_genPdgId_(0)
  , hadTau1_pt_(0.)
  , hadTau1_eta_(0.)
  , hadTau1_phi_(0.)
  , hadTau1_decayMode_(0)
  , hadTau2_genPdgId_(0)
  , hadTau2_pt_(0.)
  , hadTau2_eta_(0.)
  , hadTau2_phi_(0.)
  , hadTau2_decayMode_(0)
{
  const std::string central_or_shift = cfg.getParameter<std::string>("central_or_shift");
  const TriggerSFsys triggerSF_option = getTriggerSF_option(central_or_shift);
  switch(triggerSF_option)
  {
    // applies to only e+tau and mu+tau legs
    case TriggerSFsys::central:   triggerSF_option_ = TauTriggerSFs2017::kCentral;  break;
    case TriggerSFsys::shiftUp:   triggerSF_option_ = TauTriggerSFs2017::kStatUp;   break;
    case TriggerSFsys::shiftDown: triggerSF_option_ = TauTriggerSFs2017::kStatDown; break;
    default: throw cmsException(this) << "Invalid triggerSF option = " << static_cast<int>(triggerSF_option);
  }

  if(era_ == kEra_2016)
  {
    edm::ParameterSet cfg_triggerSF_2tau = cfg.getParameter<edm::ParameterSet>("triggerSF_2tau");

    std::string hadTauSelectionLabel;
    if     (hadTauSelection_ == "dR03mvaVVLoose") hadTauSelectionLabel = "VLooseIso"; // CV: custom WP for which no trigger efficiency turn-on curve has been measured
    else if(hadTauSelection_ == "dR03mvaVLoose" ) hadTauSelectionLabel = "VLooseIso";
    else if(hadTauSelection_ == "dR03mvaLoose"  ) hadTauSelectionLabel = "LooseIso";
    else if(hadTauSelection_ == "dR03mvaMedium" ) hadTauSelectionLabel = "MediumIso";
    else if(hadTauSelection_ == "dR03mvaTight"  ) hadTauSelectionLabel = "TightIso";
    else if(hadTauSelection_ == "dR03mvaVTight" ) hadTauSelectionLabel = "VTightIso";
    else if(hadTauSelection_ == "dR03mvaVVTight") hadTauSelectionLabel = "VVTightIso";
    else throw cmsException(this)
           << "Invalid Configuration parameter 'hadTauSelection' = " << hadTauSelection_
         ;

    const std::vector<int> hadTauDecayModes_2tau_perLeg = { 0, 1, 2, 10 };
    for(int hadTauDecayMode: hadTauDecayModes_2tau_perLeg)
    {
      std::string hadTauDecayModeLabel;
      if     (hadTauDecayMode ==  0                        ) hadTauDecayModeLabel = "dm0";  // 1-prong without pi0s
      else if(hadTauDecayMode ==  1 || hadTauDecayMode == 2) hadTauDecayModeLabel = "dm1";  // 1-prong with pi0s
      else if(hadTauDecayMode == 10                        ) hadTauDecayModeLabel = "dm10"; // 3-prong
      else throw cmsException(this)
             << "Invalid Configuration parameter 'hadTauDecayMode' = " << hadTauDecayMode
           ;

      const std::string fitName_2tau_data_gentau = Form("data_genuine_%s_%s", hadTauSelectionLabel.data(), hadTauDecayModeLabel.data());
      const edm::ParameterSet cfg_fit_2tau_data_gentau = cfg_triggerSF_2tau.getParameter<edm::ParameterSet>(fitName_2tau_data_gentau);
      effTrigger_2tau_perLeg_data_gentau_[hadTauDecayMode].push_back(new lutWrapperCrystalBall(
        fitName_2tau_data_gentau, cfg_fit_2tau_data_gentau,
        lut::kXpt, 20., 170.
      ));

      const std::string fitName_2tau_data_faketau = Form("data_fake_%s_%s", hadTauSelectionLabel.data(), hadTauDecayModeLabel.data());
      const edm::ParameterSet cfg_fit_2tau_data_faketau = cfg_triggerSF_2tau.getParameter<edm::ParameterSet>(fitName_2tau_data_faketau);
      effTrigger_2tau_perLeg_data_faketau_[hadTauDecayMode].push_back(new lutWrapperCrystalBall(
        fitName_2tau_data_faketau, cfg_fit_2tau_data_faketau,
        lut::kXpt, 20., 170.
      ));

      const std::string fitName_2tau_mc_gentau = Form("mc_genuine_%s_%s", hadTauSelectionLabel.data(), hadTauDecayModeLabel.data());
      const edm::ParameterSet cfg_fit_2tau_mc_gentau = cfg_triggerSF_2tau.getParameter<edm::ParameterSet>(fitName_2tau_mc_gentau);
      effTrigger_2tau_perLeg_mc_gentau_[hadTauDecayMode].push_back(new lutWrapperCrystalBall(
        fitName_2tau_mc_gentau, cfg_fit_2tau_mc_gentau,
        lut::kXpt, 20., 170.
      ));
      const std::string fitName_2tau_mc_faketau = Form("mc_fake_%s_%s", hadTauSelectionLabel.data(), hadTauDecayModeLabel.data());
      const edm::ParameterSet cfg_fit_2tau_mc_faketau = cfg_triggerSF_2tau.getParameter<edm::ParameterSet>(fitName_2tau_mc_faketau);
      effTrigger_2tau_perLeg_mc_faketau_[hadTauDecayMode].push_back(new lutWrapperCrystalBall(
        fitName_2tau_mc_faketau, cfg_fit_2tau_mc_faketau,
        lut::kXpt, 20., 170.
      ));
    }
  }
  else if(era_ == kEra_2017)
  {
    LocalFileInPath inputFileName_tauLeg("tthAnalysis/TauTriggerSFs2017/data/tauTriggerEfficiencies2017.root");
    std::string hadTauSelection_TauTriggerSFs2017;
    if     (hadTauSelection_ == "dR03mvaVVLoose") hadTauSelection_TauTriggerSFs2017 = "medium"; // CV: trigger efficiency turn-on curve has not been measured for this working-point
    else if(hadTauSelection_ == "dR03mvaVLoose" ) hadTauSelection_TauTriggerSFs2017 = "medium"; // CV: trigger efficiency turn-on curve has not been measured for this working-point
    else if(hadTauSelection_ == "dR03mvaLoose"  ) hadTauSelection_TauTriggerSFs2017 = "medium"; // CV: trigger efficiency turn-on curve has not been measured for this working-point
    else if(hadTauSelection_ == "dR03mvaMedium" ) hadTauSelection_TauTriggerSFs2017 = "medium";
    else if(hadTauSelection_ == "dR03mvaTight"  ) hadTauSelection_TauTriggerSFs2017 = "tight";
    else if(hadTauSelection_ == "dR03mvaVTight" ) hadTauSelection_TauTriggerSFs2017 = "vtight";
    else if(hadTauSelection_ == "dR03mvaVVTight") hadTauSelection_TauTriggerSFs2017 = "vtight"; // CV: trigger efficiency turn-on curve has not been measured for this working-point
    else throw cmsException(__func__, __LINE__)
           << "Invalid Configuration parameter 'hadTauSelection' = " << hadTauSelection_
         ;
    effTrigger_tauLeg_ = new TauTriggerSFs2017(inputFileName_tauLeg.fullPath().data(), hadTauSelection_TauTriggerSFs2017);
  }
  else if(era_ == kEra_2018)
  {
    throw cmsException(this) << "Implement me!";
  }
  else
  {
    throw cmsException(this) << "Invalid era = " << era_;
  }
}

Data_to_MC_CorrectionInterface_0l_2tau_trigger::~Data_to_MC_CorrectionInterface_0l_2tau_trigger()
{
  if(era_ == kEra_2016)
  {
    aux::clearCollection(effTrigger_2tau_perLeg_data_gentau_);
    aux::clearCollection(effTrigger_2tau_perLeg_data_faketau_);
    aux::clearCollection(effTrigger_2tau_perLeg_mc_gentau_);
    aux::clearCollection(effTrigger_2tau_perLeg_mc_faketau_);
  }
  else if(era_ == kEra_2017)
  {
    delete effTrigger_tauLeg_;
  }
}

void
Data_to_MC_CorrectionInterface_0l_2tau_trigger::setTriggerBits(bool isTriggered_2tau)
{
  isTriggered_2tau_ = isTriggered_2tau;
}

void
Data_to_MC_CorrectionInterface_0l_2tau_trigger::setHadTaus(double hadTau1_pt, double hadTau1_eta, double hadTau1_phi,
                                                           double hadTau2_pt, double hadTau2_eta, double hadTau2_phi)
{
  hadTau1_pt_  = hadTau1_pt;
  hadTau1_eta_ = hadTau1_eta;
  hadTau1_phi_ = hadTau1_phi;

  hadTau2_pt_  = hadTau2_pt;
  hadTau2_eta_ = hadTau2_eta;
  hadTau2_phi_ = hadTau2_phi;
}

void
Data_to_MC_CorrectionInterface_0l_2tau_trigger::setHadTaus(int hadTau1_genPdgId, double hadTau1_pt, double hadTau1_eta, int hadTau1_decayMode,
                                                           int hadTau2_genPdgId, double hadTau2_pt, double hadTau2_eta, int hadTau2_decayMode)
{
  hadTau1_genPdgId_  = hadTau1_genPdgId;
  hadTau1_pt_        = hadTau1_pt;
  hadTau1_eta_       = hadTau1_eta;
  hadTau1_decayMode_ = hadTau1_decayMode;

  hadTau2_genPdgId_  = hadTau2_genPdgId;
  hadTau2_pt_        = hadTau2_pt;
  hadTau2_eta_       = hadTau2_eta;
  hadTau2_decayMode_ = hadTau2_decayMode;
}

double
Data_to_MC_CorrectionInterface_0l_2tau_trigger::getWeight_triggerEff() const
{
  assert(0);
}

double
Data_to_MC_CorrectionInterface_0l_2tau_trigger::getSF_triggerEff() const
{
  if(isDEBUG_)
  {
    std::cout << get_human_line(this, __func__, __LINE__) << '\n';
  }

  double sf = 1.;
  if(era_ == kEra_2016)
  {

    double eff_2tau_leg1_data = 0.;
    double eff_2tau_leg1_mc = 0.;
    const bool hadTau1_isGenTau = (hadTau1_genPdgId_ == 11 || hadTau1_genPdgId_ == 13 || hadTau1_genPdgId_ == 15);
    if(hadTau1_isGenTau)
    {
      eff_2tau_leg1_data = get_from_lut(effTrigger_2tau_perLeg_data_gentau_, hadTau1_pt_, hadTau1_eta_, hadTau1_decayMode_, isDEBUG_);
      eff_2tau_leg1_mc   = get_from_lut(effTrigger_2tau_perLeg_mc_gentau_, hadTau1_pt_, hadTau1_eta_, hadTau1_decayMode_, isDEBUG_);
    }
    else
    {
      eff_2tau_leg1_data = get_from_lut(effTrigger_2tau_perLeg_data_faketau_, hadTau1_pt_, hadTau1_eta_, hadTau1_decayMode_, isDEBUG_);
      eff_2tau_leg1_mc   = get_from_lut(effTrigger_2tau_perLeg_mc_faketau_, hadTau1_pt_, hadTau1_eta_, hadTau1_decayMode_, isDEBUG_);
    }

    double eff_2tau_leg2_data = 0.;
    double eff_2tau_leg2_mc = 0.;
    const bool hadTau2_isGenTau = (hadTau2_genPdgId_ == 11 || hadTau2_genPdgId_ == 13 || hadTau2_genPdgId_ == 15);
    if(hadTau2_isGenTau)
    {
      eff_2tau_leg2_data = get_from_lut(effTrigger_2tau_perLeg_data_gentau_, hadTau2_pt_, hadTau2_eta_, hadTau2_decayMode_, isDEBUG_);
      eff_2tau_leg2_mc   = get_from_lut(effTrigger_2tau_perLeg_mc_gentau_, hadTau2_pt_, hadTau2_eta_, hadTau2_decayMode_, isDEBUG_);
    }
    else
    {
      eff_2tau_leg2_data = get_from_lut(effTrigger_2tau_perLeg_data_faketau_, hadTau2_pt_, hadTau2_eta_, hadTau2_decayMode_, isDEBUG_);
      eff_2tau_leg2_mc   = get_from_lut(effTrigger_2tau_perLeg_mc_faketau_, hadTau2_pt_, hadTau2_eta_, hadTau2_decayMode_, isDEBUG_);
    }

    const double eff_2tau_data = eff_2tau_leg1_data * eff_2tau_leg2_data;
    const double eff_2tau_mc   = eff_2tau_leg1_mc   * eff_2tau_leg2_mc;

    if(isDEBUG_)
    {
      std::cout << "hadTau (lead): pT = "    << hadTau1_pt_ << ", eta = " << hadTau1_eta_ << "\n"
                   "hadTau (sublead): pT = " << hadTau2_pt_ << ", eta = " << hadTau2_eta_ << '\n'
      ;
    }

    if(isTriggered_2tau_)
    {
      sf = aux::compSF(eff_2tau_data, eff_2tau_mc);
      if(isDEBUG_)
      {
        std::cout << " eff: data = " << eff_2tau_data << ", "
                     "MC = " << eff_2tau_mc << " --> SF = " << sf << '\n'
        ;
      }
    }
    else
    {
      sf = 0.;
      if(isDEBUG_)
      {
        std::cout << "neither single lepton trigger nor lepton+tau cross trigger fires\n"
                     "--> setting SF = " << sf << '\n'
        ;
      }
    }

  }
  if(era_ == kEra_2017)
  {
    double eff_2tau_tauLeg1_data = 0.;
    double eff_2tau_tauLeg1_mc   = 0.;
    if(std::fabs(hadTau1_eta_) <= 2.1)
    {
      eff_2tau_tauLeg1_data = effTrigger_tauLeg_->getDiTauEfficiencyData(hadTau1_pt_, hadTau1_eta_, hadTau1_phi_, triggerSF_option_);
      eff_2tau_tauLeg1_mc   = effTrigger_tauLeg_->getDiTauEfficiencyMC(hadTau1_pt_, hadTau1_eta_, hadTau1_phi_, triggerSF_option_);
    }
      
    double eff_2tau_tauLeg2_data = 0.;
    double eff_2tau_tauLeg2_mc   = 0.;
    if(std::fabs(hadTau2_eta_) <= 2.1)
    {
      eff_2tau_tauLeg2_data = effTrigger_tauLeg_->getDiTauEfficiencyData(hadTau2_pt_, hadTau2_eta_, hadTau2_phi_, triggerSF_option_);
      eff_2tau_tauLeg2_mc   = effTrigger_tauLeg_->getDiTauEfficiencyMC(hadTau2_pt_, hadTau2_eta_, hadTau2_phi_, triggerSF_option_);
    }

    if(isDEBUG_)
    {
      std::cout << "hadTau (lead):    pT = " << hadTau1_pt_ << ", eta = " << hadTau1_eta_ << "\n"
                   "hadTau (sublead): pT = " << hadTau2_pt_ << ", eta = " << hadTau2_eta_ << "\n"
                   "eff (tau1): data = " << eff_2tau_tauLeg1_data << ", MC = " << eff_2tau_tauLeg1_mc << "\n"
                   "eff (tau2): data = " << eff_2tau_tauLeg2_data << ", MC = " << eff_2tau_tauLeg2_mc << '\n'
      ;
    }

    //-------------------------------------------------------------------------------------------------------------------
    if(isTriggered_2tau_)
    {
      // case 2: ditau trigger fires

      const double eff_data = eff_2tau_tauLeg1_data*eff_2tau_tauLeg2_data;
      const double eff_mc   = eff_2tau_tauLeg1_mc*eff_2tau_tauLeg2_mc;

      sf = aux::compSF(eff_data, eff_mc);
      if(isDEBUG_)
      {
        std::cout << "case 2: ditau trigger fires\n"
                     " eff: data = " << eff_data << ", MC = " << eff_mc << " --> SF = " << sf << '\n'
        ;
      }
    }
    else 
    {
      // case 1: ditau trigger doesn't fire
      // (SF doesn't matter, as event does not pass event selection)

      sf = 0.;
      if(isDEBUG_)
      {
        std::cout << "case 1: ditau trigger doesn't fire\n"
                     "--> setting SF = " << sf << '\n'
        ;
      }
    } // isTriggered_*
  } // era_
  else if(era_ == kEra_2018)
  {
    throw cmsException(this, __func__, __LINE__) << "Implement me!";
  }
  else
  {
    throw cmsException(this, __func__, __LINE__) << "Invalid era = " << era_;
  }

  return sf;
}
