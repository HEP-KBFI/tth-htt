#include "tthAnalysis/HiggsToTauTau/interface/Data_to_MC_CorrectionInterface_0l_2tau_trigger.h"

#include "tthAnalysis/HiggsToTauTau/interface/leptonTypes.h" // kElectron, kMuon
#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // kEra_*
#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h" // cmsException()
#include "tthAnalysis/HiggsToTauTau/interface/data_to_MC_corrections_auxFunctions.h" // aux::
#include "tthAnalysis/HiggsToTauTau/interface/sysUncertOptions.h" // TriggerSFsys, getTriggerSF_option()
#include "tthAnalysis/HiggsToTauTau/interface/lutAuxFunctions.h" // get_from_lut()

#include "TauAnalysisTools/TauTriggerSFs/interface/TauTriggerSFs2017.h" // TauTriggerSFs2017

#include <TString.h> // Form()
#include <TMath.h> // TMath::Abs()

#include <boost/algorithm/string/predicate.hpp> // boost::ends_with()

#include <cassert> // assert()

Data_to_MC_CorrectionInterface_0l_2tau_trigger::Data_to_MC_CorrectionInterface_0l_2tau_trigger(const edm::ParameterSet & cfg)
  : effTrigger_tauLeg_(nullptr)
  , era_(get_era(cfg.getParameter<std::string>("era")))
  , hadTauSelection_(cfg.getParameter<std::string>("hadTauSelection"))
  , isDEBUG_(cfg.exists("isDEBUG") ? cfg.getParameter<bool>("isDEBUG") : false)
  , triggerSF_option_(getTriggerSF_option(cfg.getParameter<std::string>("central_or_shift")))
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
  if(era_ == kEra_2016)
  {
    const edm::ParameterSet cfg_triggerSF_2tau = cfg.getParameter<edm::ParameterSet>("triggerSF_2tau");

    const std::string hadTauSelectionLabel = aux::getHadTauSelectionLabel_2016(hadTauSelection_);
    const std::vector<int> hadTauDecayModes_2tau_perLeg = { 0, 1, 2, 10 };
    for(int hadTauDecayMode: hadTauDecayModes_2tau_perLeg)
    {
      const std::string hadTauDecayModeLabel = aux::getHadTauDecayModeLabel(hadTauDecayMode);
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
    const LocalFileInPath inputFileName_tauLeg("TauAnalysisTools/TauTriggerSFs/data/tauTriggerEfficiencies2017.root");
    const std::string hadTauSelection_TauTriggerSFs2017 = aux::getHadTauSelectionLabel_2017(hadTauSelection_);
    const std::string wpType = "MVAv2";
    const std::string year = "2017";
    effTrigger_tauLeg_ = new TauTriggerSFs2017(
      inputFileName_tauLeg.fullPath(), "ditau", year, hadTauSelection_TauTriggerSFs2017, wpType
    );
  }
  else if(era_ == kEra_2018)
  {
    const LocalFileInPath inputFileName_tauLeg("TauAnalysisTools/TauTriggerSFs/data/tauTriggerEfficiencies2018.root");
    const std::string hadTauSelection_TauTriggerSFs2017 = aux::getHadTauSelectionLabel_2017(hadTauSelection_);
    const std::string wpType = "MVAv2";
    const std::string year = "2018";
    effTrigger_tauLeg_ = new TauTriggerSFs2017(
      inputFileName_tauLeg.fullPath(), "ditau", year, hadTauSelection_TauTriggerSFs2017, wpType
    );
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
Data_to_MC_CorrectionInterface_0l_2tau_trigger::setHadTaus(double hadTau1_pt, double hadTau1_eta, double hadTau1_phi, int hadTau1_decayMode,
                                                           double hadTau2_pt, double hadTau2_eta, double hadTau2_phi, int hadTau2_decayMode)
{
  hadTau1_pt_        = hadTau1_pt;
  hadTau1_eta_       = hadTau1_eta;
  hadTau1_phi_       = hadTau1_phi;
  hadTau1_decayMode_ = hadTau1_decayMode;

  hadTau2_pt_        = hadTau2_pt;
  hadTau2_eta_       = hadTau2_eta;
  hadTau2_phi_       = hadTau2_phi;
  hadTau2_decayMode_ = hadTau2_decayMode;
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

  double eff_2tau_tauLeg1_data = 0.;
  double eff_2tau_tauLeg1_mc   = 0.;
  double eff_2tau_tauLeg2_data = 0.;
  double eff_2tau_tauLeg2_mc   = 0.;

  if(era_ == kEra_2016)
  {
    const bool hadTau1_isGenTau = (hadTau1_genPdgId_ == 11 || hadTau1_genPdgId_ == 13 || hadTau1_genPdgId_ == 15);
    if(hadTau1_isGenTau)
    {
      eff_2tau_tauLeg1_data = get_from_lut(effTrigger_2tau_perLeg_data_gentau_, hadTau1_pt_, hadTau1_eta_, hadTau1_decayMode_, isDEBUG_);
      eff_2tau_tauLeg1_mc   = get_from_lut(effTrigger_2tau_perLeg_mc_gentau_, hadTau1_pt_, hadTau1_eta_, hadTau1_decayMode_, isDEBUG_);
    }
    else
    {
      eff_2tau_tauLeg1_data = get_from_lut(effTrigger_2tau_perLeg_data_faketau_, hadTau1_pt_, hadTau1_eta_, hadTau1_decayMode_, isDEBUG_);
      eff_2tau_tauLeg1_mc   = get_from_lut(effTrigger_2tau_perLeg_mc_faketau_, hadTau1_pt_, hadTau1_eta_, hadTau1_decayMode_, isDEBUG_);
    }

    const bool hadTau2_isGenTau = (hadTau2_genPdgId_ == 11 || hadTau2_genPdgId_ == 13 || hadTau2_genPdgId_ == 15);
    if(hadTau2_isGenTau)
    {
      eff_2tau_tauLeg2_data = get_from_lut(effTrigger_2tau_perLeg_data_gentau_, hadTau2_pt_, hadTau2_eta_, hadTau2_decayMode_, isDEBUG_);
      eff_2tau_tauLeg2_mc   = get_from_lut(effTrigger_2tau_perLeg_mc_gentau_, hadTau2_pt_, hadTau2_eta_, hadTau2_decayMode_, isDEBUG_);
    }
    else
    {
      eff_2tau_tauLeg2_data = get_from_lut(effTrigger_2tau_perLeg_data_faketau_, hadTau2_pt_, hadTau2_eta_, hadTau2_decayMode_, isDEBUG_);
      eff_2tau_tauLeg2_mc   = get_from_lut(effTrigger_2tau_perLeg_mc_faketau_, hadTau2_pt_, hadTau2_eta_, hadTau2_decayMode_, isDEBUG_);
    }
  }
  else if(era_ == kEra_2017)
  {
    const auto getTriggerEfficiencyDataFunc = aux::getTriggerFuncData(triggerSF_option_);
    const auto getTriggerEfficiencyMCFunc   = aux::getTriggerFuncMC(triggerSF_option_);
    assert(getTriggerEfficiencyDataFunc);
    assert(getTriggerEfficiencyMCFunc);

    if(std::fabs(hadTau1_eta_) <= 2.1)
    {
      eff_2tau_tauLeg1_data = (effTrigger_tauLeg_->*getTriggerEfficiencyDataFunc)(hadTau1_pt_, hadTau1_eta_, hadTau1_phi_, hadTau1_decayMode_);
      eff_2tau_tauLeg1_mc   = (effTrigger_tauLeg_->*getTriggerEfficiencyMCFunc)  (hadTau1_pt_, hadTau1_eta_, hadTau1_phi_, hadTau1_decayMode_);
    }

    if(std::fabs(hadTau2_eta_) <= 2.1)
    {
      eff_2tau_tauLeg2_data = (effTrigger_tauLeg_->*getTriggerEfficiencyDataFunc)(hadTau2_pt_, hadTau2_eta_, hadTau2_phi_, hadTau2_decayMode_);
      eff_2tau_tauLeg2_mc   = (effTrigger_tauLeg_->*getTriggerEfficiencyMCFunc)  (hadTau2_pt_, hadTau2_eta_, hadTau2_phi_, hadTau2_decayMode_);
    }
  }
  else
  {
    throw cmsException(this, __func__, __LINE__) << "Invalid era = " << era_;
  }

  if(isDEBUG_)
  {
    std::cout << "hadTau (lead):    pT = " << hadTau1_pt_ << ", eta = " << hadTau1_eta_ << "\n"
                 "hadTau (sublead): pT = " << hadTau2_pt_ << ", eta = " << hadTau2_eta_ << "\n"
                 "eff (tau1): data = " << eff_2tau_tauLeg1_data << ", MC = " << eff_2tau_tauLeg1_mc << "\n"
                 "eff (tau2): data = " << eff_2tau_tauLeg2_data << ", MC = " << eff_2tau_tauLeg2_mc << '\n'
    ;
  }

  double sf = 1.;
  if(isTriggered_2tau_)
  {
    // case 2: ditau trigger fires

    const double eff_data = eff_2tau_tauLeg1_data * eff_2tau_tauLeg2_data;
    const double eff_mc   = eff_2tau_tauLeg1_mc   * eff_2tau_tauLeg2_mc;

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
  }

  return sf;
}
