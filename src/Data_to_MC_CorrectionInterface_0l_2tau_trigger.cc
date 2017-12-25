#include "tthAnalysis/HiggsToTauTau/interface/Data_to_MC_CorrectionInterface_0l_2tau_trigger.h"

#include "FWCore/Utilities/interface/Exception.h" // cms::Exception

#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // kEra_2017

#include <TString.h>

#include <algorithm> // std::sort()
#include <assert.h> // assert

namespace
{
  std::string getHadTauSelectionLabel(const std::string& hadTauSelection)
  {
    std::string hadTauSelectionLabel;
    if      ( hadTauSelection == "dR03mvaVVLoose" ) hadTauSelectionLabel = "VLooseIso"; // CV: custom WP for which no trigger efficiency turn-on curve has been measured
    else if ( hadTauSelection == "dR03mvaVLoose"  ) hadTauSelectionLabel = "VLooseIso";
    else if ( hadTauSelection == "dR03mvaLoose"   ) hadTauSelectionLabel = "LooseIso"; 
    else if ( hadTauSelection == "dR03mvaMedium"  ) hadTauSelectionLabel = "MediumIso";
    else if ( hadTauSelection == "dR03mvaTight"   ) hadTauSelectionLabel = "TightIso"; 
    else if ( hadTauSelection == "dR03mvaVTight"  ) hadTauSelectionLabel = "VTightIso";
    else if ( hadTauSelection == "dR03mvaVVTight" ) hadTauSelectionLabel = "VVTightIso";
    else throw cms::Exception("Data_to_MC_CorrectionInterface_0l_2tau_trigger")
      << "Invalid Configuration parameter 'hadTauSelection' = " << hadTauSelection << " !!\n";
    return hadTauSelectionLabel;
  }
  
  std::string getHadTauDecayModeLabel(int hadTauDecayMode)
  {
    std::string hadTauDecayModeLabel;
    if      ( hadTauDecayMode ==  0                         ) hadTauDecayModeLabel = "dm0";  // 1-prong without pi0s
    else if ( hadTauDecayMode ==  1 || hadTauDecayMode == 2 ) hadTauDecayModeLabel = "dm1";  // 1-prong with pi0s
    else if ( hadTauDecayMode == 10                         ) hadTauDecayModeLabel = "dm10"; // 3-prong
    else throw cms::Exception("Data_to_MC_CorrectionInterface_0l_2tau_trigger")
      << "Invalid Configuration parameter 'hadTauDecayMode' = " << hadTauDecayMode << " !!\n";
    return hadTauDecayModeLabel;
  }
}

Data_to_MC_CorrectionInterface_0l_2tau_trigger::Data_to_MC_CorrectionInterface_0l_2tau_trigger(const edm::ParameterSet& cfg)
  : hadTau1_genPdgId_(-1)
  , hadTau1_pt_(0.)
  , hadTau1_eta_(0.)
  , hadTau1_decayMode_(-1)
  , hadTau2_genPdgId_(-1)
  , hadTau2_pt_(0.)
  , hadTau2_eta_(0.)
  , hadTau2_decayMode_(-1)
{
  std::string era_string = cfg.getParameter<std::string>("era");
  if ( era_string == "2017" ) era_ = kEra_2017;
  else throw cms::Exception("Data_to_MC_CorrectionInterface_0l_2tau_trigger") 
    << "Invalid Configuration parameter 'era' = " << era_string << " !!\n";

  hadTauSelection_ = cfg.getParameter<std::string>("hadTauSelection");

  std::string central_or_shift = cfg.getParameter<std::string>("central_or_shift");
  if ( central_or_shift != "central" ) {
    TString central_or_shift_tstring = central_or_shift.data();
    std::string shiftUp_or_Down = "";
    if      ( central_or_shift_tstring.EndsWith("Up")   ) shiftUp_or_Down = "Up";
    else if ( central_or_shift_tstring.EndsWith("Down") ) shiftUp_or_Down = "Down";
    else throw cms::Exception("Data_to_MC_CorrectionInterface_0l_2tau_trigger")
      << "Invalid Configuration parameter 'central_or_shift' = " << central_or_shift << " !!\n";
    // CV: no systematic uncertainties on data/MC corrections for trigger efficiency in 0l_2tau category defined yet
  }

  isDEBUG_ = ( cfg.exists("isDEBUG") ) ? cfg.getParameter<bool>("isDEBUG") : false; 

  edm::ParameterSet cfg_triggerSF_2tau = cfg.getParameter<edm::ParameterSet>("triggerSF_2tau");
  std::string hadTauSelectionLabel = getHadTauSelectionLabel(hadTauSelection_);
  std::vector<int> hadTauDecayModes_2tau_perLeg = { 0, 1, 2, 10 };
  for ( std::vector<int>::const_iterator hadTauDecayMode = hadTauDecayModes_2tau_perLeg.begin();
	hadTauDecayMode != hadTauDecayModes_2tau_perLeg.end(); ++hadTauDecayMode ) {
    std::string hadTauDecayModeLabel = getHadTauDecayModeLabel(*hadTauDecayMode);

    std::string fitName_2tau_data_gentau = Form("data_genuine_%s_%s", hadTauSelectionLabel.data(), hadTauDecayModeLabel.data());
    edm::ParameterSet cfg_fit_2tau_data_gentau = cfg_triggerSF_2tau.getParameter<edm::ParameterSet>(fitName_2tau_data_gentau);
    effTrigger_2tau_perLeg_data_gentau_[*hadTauDecayMode].push_back(new lutWrapperCrystalBall(
      fitName_2tau_data_gentau, cfg_fit_2tau_data_gentau,
      lut::kXpt, 20., 170.));
    std::string fitName_2tau_data_faketau = Form("data_fake_%s_%s", hadTauSelectionLabel.data(), hadTauDecayModeLabel.data());
    edm::ParameterSet cfg_fit_2tau_data_faketau = cfg_triggerSF_2tau.getParameter<edm::ParameterSet>(fitName_2tau_data_faketau);
    effTrigger_2tau_perLeg_data_faketau_[*hadTauDecayMode].push_back(new lutWrapperCrystalBall(
      fitName_2tau_data_faketau, cfg_fit_2tau_data_faketau,
      lut::kXpt, 20., 170.));

    std::string fitName_2tau_mc_gentau = Form("mc_genuine_%s_%s", hadTauSelectionLabel.data(), hadTauDecayModeLabel.data());
    edm::ParameterSet cfg_fit_2tau_mc_gentau = cfg_triggerSF_2tau.getParameter<edm::ParameterSet>(fitName_2tau_mc_gentau);
    effTrigger_2tau_perLeg_mc_gentau_[*hadTauDecayMode].push_back(new lutWrapperCrystalBall(
      fitName_2tau_mc_gentau, cfg_fit_2tau_mc_gentau,
      lut::kXpt, 20., 170.));
    std::string fitName_2tau_mc_faketau = Form("mc_fake_%s_%s", hadTauSelectionLabel.data(), hadTauDecayModeLabel.data());
    edm::ParameterSet cfg_fit_2tau_mc_faketau = cfg_triggerSF_2tau.getParameter<edm::ParameterSet>(fitName_2tau_mc_faketau);
    effTrigger_2tau_perLeg_mc_faketau_[*hadTauDecayMode].push_back(new lutWrapperCrystalBall(
      fitName_2tau_mc_faketau, cfg_fit_2tau_mc_faketau,
      lut::kXpt, 20., 170.));
  }
}
 
namespace
{
  void clearCollection(std::map<int, std::vector<lutWrapperBase*> >& collection)
  {
    for ( std::map<int, std::vector<lutWrapperBase*> >::iterator it1 = collection.begin();
	  it1 != collection.end(); ++it1 ) {
      for ( std::vector<lutWrapperBase*>::iterator it2 = it1->second.begin();
	    it2 != it1->second.end(); ++it2 ) {
	delete (*it2);
      }
      it1->second.clear();
    }
  }
}

Data_to_MC_CorrectionInterface_0l_2tau_trigger::~Data_to_MC_CorrectionInterface_0l_2tau_trigger()
{
  clearCollection(effTrigger_2tau_perLeg_data_gentau_);
  clearCollection(effTrigger_2tau_perLeg_data_faketau_);
  clearCollection(effTrigger_2tau_perLeg_mc_gentau_);
  clearCollection(effTrigger_2tau_perLeg_mc_faketau_);  
}

void Data_to_MC_CorrectionInterface_0l_2tau_trigger::setTriggerBits(bool isTriggered_2tau)
{
  isTriggered_2tau_ = isTriggered_2tau;
}

void Data_to_MC_CorrectionInterface_0l_2tau_trigger::setHadTaus(int hadTau1_genPdgId, double hadTau1_pt, double hadTau1_eta, int hadTau1_decayMode,
								int hadTau2_genPdgId, double hadTau2_pt, double hadTau2_eta, int hadTau2_decayMode)
{
  hadTau1_genPdgId_ = hadTau1_genPdgId;
  hadTau1_pt_ = hadTau1_pt;
  hadTau1_eta_ = hadTau1_eta;
  hadTau1_decayMode_ = hadTau1_decayMode;
  hadTau2_genPdgId_ = hadTau2_genPdgId;
  hadTau2_pt_ = hadTau2_pt;
  hadTau2_eta_ = hadTau2_eta;
  hadTau2_decayMode_ = hadTau2_decayMode;
}

namespace
{
  double get_from_lut(const std::map<int, vLutWrapperBase>& corrections, double hadTau_pt, double hadTau_eta, int hadTau_decayMode, bool isDEBUG)
  {
    double sf = 1.;
    std::map<int, vLutWrapperBase>::const_iterator correction = corrections.find(hadTau_decayMode);
    if ( correction != corrections.end() ) {
      sf = get_from_lut(correction->second, hadTau_pt, hadTau_eta, isDEBUG);
    } else throw cms::Exception("get_from_lut")
	<< "Invalid parameter 'hadTauDecayMode' = " << hadTau_decayMode << " !!\n";      
    return sf;
  }
  
  double compSF(double eff_data, double eff_mc)
  {
    double sf = eff_data/TMath::Max(1.e-6, eff_mc);
    if ( sf > 1.e+1 ) sf = 1.e+1; 
    return sf;
  }
}

double Data_to_MC_CorrectionInterface_0l_2tau_trigger::getSF_triggerEff() const
{
  if ( isDEBUG_ ) {
    std::cout << "<Data_to_MC_CorrectionInterface_0l_2tau_trigger::getSF_triggerEff>:" << std::endl;
  }
  double eff_2tau_leg1_data = 0.;
  double eff_2tau_leg1_mc = 0.;
  double eff_2tau_leg2_data = 0.;
  double eff_2tau_leg2_mc = 0.;
  bool hadTau1_isGenTau = (hadTau1_genPdgId_ == 11 || hadTau1_genPdgId_ == 13 || hadTau1_genPdgId_ == 15);
  bool hadTau2_isGenTau = (hadTau2_genPdgId_ == 11 || hadTau2_genPdgId_ == 13 || hadTau2_genPdgId_ == 15);
  if ( hadTau1_isGenTau ) {
    eff_2tau_leg1_data = get_from_lut(effTrigger_2tau_perLeg_data_gentau_, hadTau1_pt_, hadTau1_eta_, hadTau1_decayMode_, isDEBUG_);
    eff_2tau_leg1_mc = get_from_lut(effTrigger_2tau_perLeg_mc_gentau_, hadTau1_pt_, hadTau1_eta_, hadTau1_decayMode_, isDEBUG_);
  } else {
    eff_2tau_leg1_data = get_from_lut(effTrigger_2tau_perLeg_data_faketau_, hadTau1_pt_, hadTau1_eta_, hadTau1_decayMode_, isDEBUG_);
    eff_2tau_leg1_mc = get_from_lut(effTrigger_2tau_perLeg_mc_faketau_, hadTau1_pt_, hadTau1_eta_, hadTau1_decayMode_, isDEBUG_);
  }
  if ( hadTau2_isGenTau ) {
    eff_2tau_leg2_data = get_from_lut(effTrigger_2tau_perLeg_data_gentau_, hadTau2_pt_, hadTau2_eta_, hadTau2_decayMode_, isDEBUG_);
    eff_2tau_leg2_mc = get_from_lut(effTrigger_2tau_perLeg_mc_gentau_, hadTau2_pt_, hadTau2_eta_, hadTau2_decayMode_, isDEBUG_);
  } else {
    eff_2tau_leg2_data = get_from_lut(effTrigger_2tau_perLeg_data_faketau_, hadTau2_pt_, hadTau2_eta_, hadTau2_decayMode_, isDEBUG_);
    eff_2tau_leg2_mc = get_from_lut(effTrigger_2tau_perLeg_mc_faketau_, hadTau2_pt_, hadTau2_eta_, hadTau2_decayMode_, isDEBUG_);
  }
  double eff_2tau_data = eff_2tau_leg1_data*eff_2tau_leg2_data;
  double eff_2tau_mc = eff_2tau_leg1_mc*eff_2tau_leg2_mc;
  if ( isDEBUG_ ) {
    std::cout << "hadTau (lead): pT = " << hadTau1_pt_ << ", eta = " << hadTau1_eta_ << std::endl;
    std::cout << "hadTau (sublead): pT = " << hadTau2_pt_ << ", eta = " << hadTau2_eta_ << std::endl;    
  }
  double sf = 1.;
  if ( isTriggered_2tau_ ) {
    sf = compSF(eff_2tau_data, eff_2tau_mc);
    if ( isDEBUG_ ) {
      std::cout << " eff: data = " << eff_2tau_data << ", MC = " << eff_2tau_mc << " --> SF = " << sf << std::endl;
    }
  } else { 
    sf = 0.;
    if ( isDEBUG_ ) {
      std::cout << "neither single lepton trigger nor lepton+tau cross trigger fires" << std::endl;
      std::cout << "--> setting SF = " << sf << std::endl;
    }      
  }
  //std::cout << "<Data_to_MC_CorrectionInterface::getSF_triggerEff>: sf = " << sf << std::endl;
  return sf;
}
