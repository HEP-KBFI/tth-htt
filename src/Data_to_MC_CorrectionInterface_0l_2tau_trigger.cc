#include "tthAnalysis/HiggsToTauTau/interface/Data_to_MC_CorrectionInterface_0l_2tau_trigger.h"

#include "tthAnalysis/HiggsToTauTau/interface/leptonTypes.h" // kElectron, kMuon
#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // kEra_2017
#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h" // cmsException()
#include "tthAnalysis/HiggsToTauTau/interface/data_to_MC_corrections_auxFunctions.h" // aux::
#include "tthAnalysis/HiggsToTauTau/interface/sysUncertOptions.h" // TriggerSFsys, getTriggerSF_option()

#include <TString.h> // Form()
#include <TMath.h> // TMath::Abs()

#include <boost/algorithm/string/predicate.hpp> // boost::ends_with()

#include <cassert> // assert()

Data_to_MC_CorrectionInterface_0l_2tau_trigger::Data_to_MC_CorrectionInterface_0l_2tau_trigger(const edm::ParameterSet & cfg)
  : effTrigger_tauLeg_(nullptr)
  , hadTauSelection_(cfg.getParameter<std::string>("hadTauSelection"))
  , isDEBUG_(cfg.exists("isDEBUG") ? cfg.getParameter<bool>("isDEBUG") : false)
  , triggerSF_option_(TauTriggerSFs2017::kCentral)
  , hadTau1_pt_(0.)
  , hadTau1_eta_(0.)
  , hadTau1_phi_(0.)
  , hadTau2_pt_(0.)
  , hadTau2_eta_(0.)
  , hadTau2_phi_(0.)
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
  const TriggerSFsys triggerSF_option = getTriggerSF_option(central_or_shift);
  switch(triggerSF_option)
  {
    // applies to only e+tau and mu+tau legs
    case TriggerSFsys::central:   triggerSF_option_ = TauTriggerSFs2017::kCentral;  break;
    case TriggerSFsys::shiftUp:   triggerSF_option_ = TauTriggerSFs2017::kStatUp;   break;
    case TriggerSFsys::shiftDown: triggerSF_option_ = TauTriggerSFs2017::kStatDown; break;
    default: throw cmsException(this) << "Invalid triggerSF option = " << static_cast<int>(triggerSF_option);
  }

  LocalFileInPath inputFileName_tauLeg("tthAnalysis/TauTriggerSFs2017/data/tauTriggerEfficiencies2017.root");
  std::string hadTauSelection_TauTriggerSFs2017;
  if      ( hadTauSelection_ == "dR03mvaVVLoose" ) hadTauSelection_TauTriggerSFs2017 = "medium"; // CV: trigger efficiency turn-on curve has not been measured for this working-point
  else if ( hadTauSelection_ == "dR03mvaVLoose"  ) hadTauSelection_TauTriggerSFs2017 = "medium"; // CV: trigger efficiency turn-on curve has not been measured for this working-point
  else if ( hadTauSelection_ == "dR03mvaLoose"   ) hadTauSelection_TauTriggerSFs2017 = "medium"; // CV: trigger efficiency turn-on curve has not been measured for this working-point
  else if ( hadTauSelection_ == "dR03mvaMedium"  ) hadTauSelection_TauTriggerSFs2017 = "medium";
  else if ( hadTauSelection_ == "dR03mvaTight"   ) hadTauSelection_TauTriggerSFs2017 = "tight";
  else if ( hadTauSelection_ == "dR03mvaVTight"  ) hadTauSelection_TauTriggerSFs2017 = "vtight";
  else if ( hadTauSelection_ == "dR03mvaVVTight" ) hadTauSelection_TauTriggerSFs2017 = "vtight"; // CV: trigger efficiency turn-on curve has not been measured for this working-point
  else throw cmsException(__func__, __LINE__)
    << "Invalid Configuration parameter 'hadTauSelection' = " << hadTauSelection_ << " !!";
  effTrigger_tauLeg_ = new TauTriggerSFs2017(inputFileName_tauLeg.fullPath().data(), hadTauSelection_TauTriggerSFs2017);
}

Data_to_MC_CorrectionInterface_0l_2tau_trigger::~Data_to_MC_CorrectionInterface_0l_2tau_trigger()
{}

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
    std::cout << "<Data_to_MC_CorrectionInterface_0l_2tau_trigger::getSF_triggerEff>:\n";
  }

  double sf = 1.;
  if(era_ == kEra_2017)
  {
    double eff_2tau_tauLeg1_data = 0.;
    double eff_2tau_tauLeg1_mc   = 0.;
    if ( TMath::Abs(hadTau1_eta_) <= 2.1 ) {
      eff_2tau_tauLeg1_data = effTrigger_tauLeg_->getDiTauEfficiencyData(hadTau1_pt_, hadTau1_eta_, hadTau1_phi_, triggerSF_option_);
      eff_2tau_tauLeg1_mc   = effTrigger_tauLeg_->getDiTauEfficiencyMC(hadTau1_pt_, hadTau1_eta_, hadTau1_phi_, triggerSF_option_);
    }
      
    double eff_2tau_tauLeg2_data = 0.;
    double eff_2tau_tauLeg2_mc   = 0.;
    if ( TMath::Abs(hadTau2_eta_) <= 2.1 ) {
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
                     " eff: data = " << eff_data << ", MC = " << eff_mc << " --> SF = " << sf << '\n';
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
                     "--> setting SF = " << sf << '\n';
      }
    } // isTriggered_*
  } // era_
  else
  {
    assert(0);
  }

  return sf;
}
