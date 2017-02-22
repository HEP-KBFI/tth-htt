#include "tthAnalysis/HiggsToTauTau/interface/Data_to_MC_CorrectionInterface_1l_2tau_trigger.h"

#include "FWCore/Utilities/interface/Exception.h" // cms::Exception

#include "tthAnalysis/HiggsToTauTau/interface/lutAuxFunctions.h" // lutWrapperBase, openFile, loadTH1/TH2, get_sf_from_TH1/TH2 
#include "tthAnalysis/HiggsToTauTau/interface/leptonTypes.h" // kElectron, kMuon
#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // kEra_2015, kEra_2016

#include <TString.h>

#include <algorithm> // std::sort()
#include <assert.h> // assert

namespace
{
  std::string getEtaBinLabel(double etaMin, double etaMax)
  {
    TString etaBinLabel_tstring;
    if ( etaMin != -1. && etaMax != -1. ) {
      etaBinLabel_tstring = Form("%1.4gto%1.4g", etaMin, etaMax);
    } else if ( etaMin != -1. ) {
      etaBinLabel_tstring = Form("Gt%1.4g", etaMin);
    } else if ( etaMax != -1. ) {
      etaBinLabel_tstring = Form("Lt%1.4g", etaMax);
    } else assert(0);
    std::string etaBinLabel = etaBinLabel_tstring.ReplaceAll(".", "p").Data();
    return etaBinLabel;
  }

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
    else throw cms::Exception("Data_to_MC_CorrectionInterface_1l_2tau_trigger")
      << "Invalid Configuration parameter 'hadTauSelection' = " << hadTauSelection << " !!\n";
    return hadTauSelectionLabel;
  }
  
  std::string getHadTauDecayModeLabel(int hadTauDecayMode)
  {
    std::string hadTauDecayModeLabel;
    if      ( hadTauDecayMode ==  0                         ) hadTauDecayModeLabel = "dm0";  // 1-prong without pi0s
    else if ( hadTauDecayMode ==  1 || hadTauDecayMode == 2 ) hadTauDecayModeLabel = "dm1";  // 1-prong with pi0s
    else if ( hadTauDecayMode == 10                         ) hadTauDecayModeLabel = "dm10"; // 3-prong
    else throw cms::Exception("Data_to_MC_CorrectionInterface_1l_2tau_trigger")
      << "Invalid Configuration parameter 'hadTauDecayMode' = " << hadTauDecayMode << " !!\n";
    return hadTauDecayModeLabel;
  }
}

Data_to_MC_CorrectionInterface_1l_2tau_trigger::Data_to_MC_CorrectionInterface_1l_2tau_trigger(const edm::ParameterSet& cfg)
  : lepton_type_(-1)
  , lepton_pt_(0.)
  , lepton_eta_(0.)
  , hadTau1_genPdgId_(-1)
  , hadTau1_pt_(0.)
  , hadTau1_eta_(0.)
  , hadTau1_decayMode_(-1)
  , hadTau2_genPdgId_(-1)
  , hadTau2_pt_(0.)
  , hadTau2_eta_(0.)
  , hadTau2_decayMode_(-1)
{
  std::string era_string = cfg.getParameter<std::string>("era");
  if ( era_string == "2016" ) era_ = kEra_2016;
  else throw cms::Exception("Data_to_MC_CorrectionInterface_1l_2tau_trigger") 
    << "Invalid Configuration parameter 'era' = " << era_string << " !!\n";

  hadTauSelection_ = cfg.getParameter<std::string>("hadTauSelection");

  std::string central_or_shift = cfg.getParameter<std::string>("central_or_shift");
  if ( central_or_shift != "central" ) {
    TString central_or_shift_tstring = central_or_shift.data();
    std::string shiftUp_or_Down = "";
    if      ( central_or_shift_tstring.EndsWith("Up")   ) shiftUp_or_Down = "Up";
    else if ( central_or_shift_tstring.EndsWith("Down") ) shiftUp_or_Down = "Down";
    else throw cms::Exception("Data_to_MC_CorrectionInterface_1l_2tau_trigger")
      << "Invalid Configuration parameter 'central_or_shift' = " << central_or_shift << " !!\n";
    // CV: no systematic uncertainties on data/MC corrections for trigger efficiency in 1l_2tau category defined yet
  }

  if ( era_ == kEra_2016 ) {
    std::vector<double> etaBinEdges_1e = { -1., 1.48, 2.1 }; 
    int numEtaBins_1e = etaBinEdges_1e.size() - 1;
    for ( int idxEtaBin = 0; idxEtaBin < numEtaBins_1e; ++idxEtaBin ) {
      double etaMin = etaBinEdges_1e[idxEtaBin];
      double etaMax = etaBinEdges_1e[idxEtaBin + 1];
      std::string etaBinLabel = getEtaBinLabel(etaMin, etaMax);
      effTrigger_1e_data_.push_back(new lutWrapperTGraph(
        inputFiles_, "tthAnalysis/HiggsToTauTau/data/triggerSF/2016/Electron_Ele25WPTight_eff.root", Form("ZMassEta%s_Data", etaBinLabel.data()),
        lut::kXptYabsEta, -1., -1., etaMin, etaMax)); 
      effTrigger_1e_mc_.push_back(new lutWrapperTGraph(
        inputFiles_, "tthAnalysis/HiggsToTauTau/data/triggerSF/2016/Electron_Ele25WPTight_eff.root", Form("ZMassEta%s_MC", etaBinLabel.data()),
        lut::kXptYabsEta, -1., -1., etaMin, etaMax)); 
    }

    std::vector<double> etaBinEdges_1e_1tau_lepLeg = { -1., 1.48, 2.1 }; 
    int numEtaBins_1e_1tau_lepLeg = etaBinEdges_1e_1tau_lepLeg.size() - 1;
    for ( int idxEtaBin = 0; idxEtaBin < numEtaBins_1e_1tau_lepLeg; ++idxEtaBin ) {
      double etaMin = etaBinEdges_1e_1tau_lepLeg[idxEtaBin];
      double etaMax = etaBinEdges_1e_1tau_lepLeg[idxEtaBin + 1];
      std::string etaBinLabel = getEtaBinLabel(etaMin, etaMax);
      effTrigger_1e1tau_lepLeg_data_.push_back(new lutWrapperTGraph(
        inputFiles_, "tthAnalysis/HiggsToTauTau/data/triggerSF/2016/Electron_Ele24_eff.root", Form("ZMassEta%s_Data", etaBinLabel.data()),
        lut::kXptYabsEta, -1., -1., etaMin, etaMax)); 
      effTrigger_1e1tau_lepLeg_mc_.push_back(new lutWrapperTGraph(
        inputFiles_, "tthAnalysis/HiggsToTauTau/data/triggerSF/2016/Electron_Ele24_eff.root", Form("ZMassEta%s_MC", etaBinLabel.data()),
        lut::kXptYabsEta, -1., -1., etaMin, etaMax));       
    }

    std::vector<double> etaBinEdges_1e1tau_tauLeg = { -1., 1.48, 2.1 };
    int numEtaBins_1e1tau_tauLeg = etaBinEdges_1e1tau_tauLeg.size() - 1;
    for ( int idxEtaBin = 0; idxEtaBin < numEtaBins_1e1tau_tauLeg; ++idxEtaBin ) {
      double etaMin = etaBinEdges_1e1tau_tauLeg[idxEtaBin];
      double etaMax = etaBinEdges_1e1tau_tauLeg[idxEtaBin + 1];
      std::string etaBinLabel;
      if      ( idxEtaBin == 0 ) etaBinLabel = "barrel";
      else if ( idxEtaBin == 1 ) etaBinLabel = "endcap";
      else assert(0);
      std::string hadTauSelectionLabel = getHadTauSelectionLabel(hadTauSelection_);
      std::vector<int> hadTauDecayModes_1e1tau_tauLeg = { 0, 1, 2, 10 };
      for ( std::vector<int>::const_iterator hadTauDecayMode = hadTauDecayModes_1e1tau_tauLeg.begin();
	    hadTauDecayMode != hadTauDecayModes_1e1tau_tauLeg.end(); ++hadTauDecayMode ) {
	std::string hadTauDecayModeLabel = getHadTauDecayModeLabel(*hadTauDecayMode);
	effTrigger_1e1tau_tauLeg_data_gentau_[*hadTauDecayMode].push_back(new lutWrapperTGraph(
          inputFiles_, "tthAnalysis/HiggsToTauTau/data/triggerSF/2016/trigger_sf_et.root", 
	  Form("data_genuine_%s_%s_%s", etaBinLabel.data(), hadTauSelectionLabel.data(), hadTauDecayModeLabel.data()),
          lut::kXpt, 0., 150., etaMin, etaMax));     
	effTrigger_1e1tau_tauLeg_data_faketau_[*hadTauDecayMode].push_back(new lutWrapperTGraph(
          inputFiles_, "tthAnalysis/HiggsToTauTau/data/triggerSF/2016/trigger_sf_et.root", 
	  Form("data_fake_%s_%s_%s", etaBinLabel.data(), hadTauSelectionLabel.data(), hadTauDecayModeLabel.data()),
          lut::kXpt, 0., 150., etaMin, etaMax));
	//---------------------------------------------------------------------------------------------------------------
	// CV: need work-around for MC, because we do not have all e+tau cross triggers stored in VHbb Ntuples V25
	//    (only HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau30_v*)
	effTrigger_1e1tau_tauLeg_mc_gentau_[*hadTauDecayMode].push_back(new lutWrapperTGraph(
          inputFiles_, "tthAnalysis/HiggsToTauTau/data/triggerSF/2016/tauleg_of_lepton_plus_tau_real_taus_skim_mc_v2.root", 
	  Form("%s_lowmt_zmass_sub_%s_%s_HLT_LooseIso30_L1iso26/tau_pt", etaBinLabel.data(), hadTauSelectionLabel.data(), hadTauDecayModeLabel.data()),
          lut::kXpt, 0., 150., etaMin, etaMax));     
	effTrigger_1e1tau_tauLeg_mc_faketau_[*hadTauDecayMode].push_back(new lutWrapperTGraph(
          inputFiles_, "tthAnalysis/HiggsToTauTau/data/triggerSF/2016/tauleg_of_lepton_plus_tau_real_taus_skim_mc_v2.root", 
	  Form("%s_highmt_os_%s_%s_HLT_LooseIso30_L1iso26/tau_pt", etaBinLabel.data(), hadTauSelectionLabel.data(), hadTauDecayModeLabel.data()),
          lut::kXpt, 0., 150., etaMin, etaMax));
	//---------------------------------------------------------------------------------------------------------------
      }
    }

    std::vector<double> etaBinEdges_1m = { -1., 0.9, 1.2, 2.1 };
    int numEtaBins_1m = etaBinEdges_1m.size() - 1;
    for ( int idxEtaBin = 0; idxEtaBin < numEtaBins_1m; ++idxEtaBin ) {
      double etaMin = etaBinEdges_1m[idxEtaBin];
      double etaMax = etaBinEdges_1m[idxEtaBin + 1];
      std::string etaBinLabel = getEtaBinLabel(etaMin, etaMax);
      effTrigger_1m_data_.push_back(new lutWrapperTGraph(
        inputFiles_, "tthAnalysis/HiggsToTauTau/data/triggerSF/2016/Muon_Mu22OR_eta2p1_eff.root", Form("ZMassEta%s_Data", etaBinLabel.data()),
        lut::kXptYabsEta, -1., -1., etaMin, etaMax)); 
      effTrigger_1m_mc_.push_back(new lutWrapperTGraph(
        inputFiles_, "tthAnalysis/HiggsToTauTau/data/triggerSF/2016/Muon_Mu22OR_eta2p1_eff.root", Form("ZMassEta%s_MC", etaBinLabel.data()),
        lut::kXptYabsEta, -1., -1., etaMin, etaMax)); 
    }

    std::vector<double> etaBinEdges_1m1tau_lepLeg = { -1., 0.9, 1.2, 2.1 };
    int numEtaBins_1m1tau_lepLeg = etaBinEdges_1m1tau_lepLeg.size() - 1;
    for ( int idxEtaBin = 0; idxEtaBin < numEtaBins_1m1tau_lepLeg; ++idxEtaBin ) {
      double etaMin = etaBinEdges_1m1tau_lepLeg[idxEtaBin];
      double etaMax = etaBinEdges_1m1tau_lepLeg[idxEtaBin + 1];
      std::string etaBinLabel = getEtaBinLabel(etaMin, etaMax);
      effTrigger_1m1tau_lepLeg_data_.push_back(new lutWrapperTGraph(
        inputFiles_, "tthAnalysis/HiggsToTauTau/data/triggerSF/2016/Muon_Mu19leg_2016BtoH_eff.root", Form("ZMassEta%s_Data", etaBinLabel.data()),
        lut::kXptYabsEta, -1., -1., etaMin, etaMax)); 
      effTrigger_1m1tau_lepLeg_mc_.push_back(new lutWrapperTGraph(
        inputFiles_, "tthAnalysis/HiggsToTauTau/data/triggerSF/2016/Muon_Mu19leg_2016BtoH_eff.root", Form("ZMassEta%s_MC", etaBinLabel.data()),
        lut::kXptYabsEta, -1., -1., etaMin, etaMax));
    }

    std::vector<double> etaBinEdges_1m1tau_tauLeg = { -1., 1.48, 2.1 };
    int numEtaBins_1m1tau_tauLeg = etaBinEdges_1m1tau_tauLeg.size() - 1;
    for ( int idxEtaBin = 0; idxEtaBin < numEtaBins_1m1tau_tauLeg; ++idxEtaBin ) {
      double etaMin = etaBinEdges_1m1tau_tauLeg[idxEtaBin];
      double etaMax = etaBinEdges_1m1tau_tauLeg[idxEtaBin + 1];
      std::string etaBinLabel;
      if      ( idxEtaBin == 0 ) etaBinLabel = "barrel";
      else if ( idxEtaBin == 1 ) etaBinLabel = "endcap";
      else assert(0);
      std::string hadTauSelectionLabel = getHadTauSelectionLabel(hadTauSelection_);
      effTrigger_1m1tau_tauLeg_data_gentau_.push_back(new lutWrapperTGraph(
        inputFiles_, "tthAnalysis/HiggsToTauTau/data/triggerSF/2016/trigger_sf_mt.root", 
        Form("data_genuine_%s_%s", etaBinLabel.data(), hadTauSelectionLabel.data()),
        lut::kXpt, 0., 150., etaMin, etaMax));     
      effTrigger_1m1tau_tauLeg_data_faketau_.push_back(new lutWrapperTGraph(
        inputFiles_, "tthAnalysis/HiggsToTauTau/data/triggerSF/2016/trigger_sf_mt.root", 
	Form("data_fake_%s_%s", etaBinLabel.data(), hadTauSelectionLabel.data()),
        lut::kXpt, 0., 150., etaMin, etaMax));
      effTrigger_1m1tau_tauLeg_mc_gentau_.push_back(new lutWrapperTGraph(
        inputFiles_, "tthAnalysis/HiggsToTauTau/data/triggerSF/2016/trigger_sf_mt.root",
        Form("mc_genuine_%s_%s", etaBinLabel.data(), hadTauSelectionLabel.data()),
        lut::kXpt, 0., 150., etaMin, etaMax));     
      effTrigger_1m1tau_tauLeg_mc_faketau_.push_back(new lutWrapperTGraph(
        inputFiles_, "tthAnalysis/HiggsToTauTau/data/triggerSF/2016/trigger_sf_mt.root",
	Form("mc_fake_%s_%s", etaBinLabel.data(), hadTauSelectionLabel.data()),
        lut::kXpt, 0., 150., etaMin, etaMax));
    }
  } else assert(0);
}
 
namespace
{
  void clearCollection(std::vector<lutWrapperBase*>& collection)
  {
    for ( std::vector<lutWrapperBase*>::iterator it = collection.begin();
	  it != collection.end(); ++it ) {
      delete (*it);
    }
    collection.clear();
  }

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

Data_to_MC_CorrectionInterface_1l_2tau_trigger::~Data_to_MC_CorrectionInterface_1l_2tau_trigger()
{
  clearCollection(effTrigger_1e_data_);
  clearCollection(effTrigger_1e_mc_);
  clearCollection(effTrigger_1e1tau_lepLeg_data_);
  clearCollection(effTrigger_1e1tau_lepLeg_mc_);
  clearCollection(effTrigger_1e1tau_tauLeg_data_gentau_);
  clearCollection(effTrigger_1e1tau_tauLeg_data_faketau_);
  clearCollection(effTrigger_1e1tau_tauLeg_mc_gentau_);
  clearCollection(effTrigger_1e1tau_tauLeg_mc_faketau_);
  
  clearCollection(effTrigger_1m_data_);
  clearCollection(effTrigger_1m_mc_);
  clearCollection(effTrigger_1m1tau_lepLeg_data_);
  clearCollection(effTrigger_1m1tau_lepLeg_mc_);
  clearCollection(effTrigger_1m1tau_tauLeg_data_gentau_);
  clearCollection(effTrigger_1m1tau_tauLeg_data_faketau_);
  clearCollection(effTrigger_1m1tau_tauLeg_mc_gentau_);
  clearCollection(effTrigger_1m1tau_tauLeg_mc_faketau_);
}

void Data_to_MC_CorrectionInterface_1l_2tau_trigger::setTriggerBits(bool isTriggered_1e, bool isTriggered_1e1tau, bool isTriggered_1m, bool isTriggered_1m1tau)
{
  isTriggered_1e_ = isTriggered_1e;
  isTriggered_1e1tau_ = isTriggered_1e1tau;
  isTriggered_1m_ = isTriggered_1m;
  isTriggered_1m1tau_ = isTriggered_1m1tau;
}

void Data_to_MC_CorrectionInterface_1l_2tau_trigger::setLeptons(int lepton_type, double lepton_pt, double lepton_eta)
{
  lepton_type_ = lepton_type;
  lepton_pt_ = lepton_pt;
  lepton_eta_ = lepton_eta;
}

void Data_to_MC_CorrectionInterface_1l_2tau_trigger::setHadTaus(int hadTau1_genPdgId, double hadTau1_pt, double hadTau1_eta, int hadTau1_decayMode,
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
  double get_from_lut(const std::map<int, vLutWrapperBase>& corrections, double hadTau_pt, double hadTau_eta, int hadTau_decayMode)
  {
    double sf = 1.;
    std::map<int, vLutWrapperBase>::const_iterator correction = corrections.find(hadTau_decayMode);
    if ( correction != corrections.end() ) {
      sf = get_from_lut(correction->second, hadTau_pt, hadTau_eta);
    } else throw cms::Exception("get_from_lut")
      << "Invalid parameter 'hadTauDecayMode' = " << hadTau_decayMode << " !!\n";
    return sf;
  }
  
  double compSF(double eff_data, double eff_mc)
  {
    const double epsilon = 1.e-1;
    double sf = eff_data/TMath::Max(epsilon, eff_mc);
    return sf;
  }
}

double Data_to_MC_CorrectionInterface_1l_2tau_trigger::getSF_triggerEff() const
{
  double sf = 1.;
  if ( era_ == kEra_2016 ) {
    double eff_1l_data = 0.;
    double eff_1l_mc = 0.;
    double eff_1l1tau_lepLeg_data = 0.;
    double eff_1l1tau_lepLeg_mc = 0.;
    double eff_1l1tau_tauLeg1_data = 0.;
    double eff_1l1tau_tauLeg1_mc = 0.;
    double eff_1l1tau_tauLeg2_data = 0.;
    double eff_1l1tau_tauLeg2_mc = 0.;
    bool isTriggered_1l = false;
    bool isTriggered_1l1tau = false;
    bool hadTau1_isGenTau = (hadTau1_genPdgId_ == 11 || hadTau1_genPdgId_ == 13 || hadTau1_genPdgId_ == 15);
    bool hadTau2_isGenTau = (hadTau2_genPdgId_ == 11 || hadTau2_genPdgId_ == 13 || hadTau2_genPdgId_ == 15);
    if ( lepton_type_ == kElectron ) {
      eff_1l_data = get_from_lut(effTrigger_1e_data_, lepton_pt_, lepton_eta_);
      eff_1l_mc = get_from_lut(effTrigger_1e_mc_, lepton_pt_, lepton_eta_);
      eff_1l1tau_lepLeg_data = get_from_lut(effTrigger_1e1tau_lepLeg_data_, lepton_pt_, lepton_eta_);
      eff_1l1tau_lepLeg_mc = get_from_lut(effTrigger_1e1tau_lepLeg_mc_, lepton_pt_, lepton_eta_);
      if ( hadTau1_isGenTau ) {
	eff_1l1tau_tauLeg1_data = get_from_lut(effTrigger_1e1tau_tauLeg_data_gentau_, hadTau1_pt_, hadTau1_eta_, hadTau1_decayMode_);
	eff_1l1tau_tauLeg1_mc = get_from_lut(effTrigger_1e1tau_tauLeg_mc_gentau_, hadTau1_pt_, hadTau1_eta_, hadTau1_decayMode_);
      } else {
	eff_1l1tau_tauLeg1_data = get_from_lut(effTrigger_1e1tau_tauLeg_data_faketau_, hadTau1_pt_, hadTau1_eta_, hadTau1_decayMode_);
	eff_1l1tau_tauLeg1_mc = get_from_lut(effTrigger_1e1tau_tauLeg_mc_faketau_, hadTau1_pt_, hadTau1_eta_, hadTau1_decayMode_);
      }
      if ( hadTau2_isGenTau ) {
	eff_1l1tau_tauLeg2_data = get_from_lut(effTrigger_1e1tau_tauLeg_data_gentau_, hadTau2_pt_, hadTau2_eta_, hadTau2_decayMode_);
	eff_1l1tau_tauLeg2_mc = get_from_lut(effTrigger_1e1tau_tauLeg_mc_gentau_, hadTau2_pt_, hadTau2_eta_, hadTau2_decayMode_);
      } else {
	eff_1l1tau_tauLeg2_data = get_from_lut(effTrigger_1e1tau_tauLeg_data_faketau_, hadTau2_pt_, hadTau2_eta_, hadTau2_decayMode_);
	eff_1l1tau_tauLeg2_mc = get_from_lut(effTrigger_1e1tau_tauLeg_mc_faketau_, hadTau2_pt_, hadTau2_eta_, hadTau2_decayMode_);
      }
      isTriggered_1l = isTriggered_1e_;
      isTriggered_1l1tau = isTriggered_1e1tau_;
    } else if ( lepton_type_ == kMuon ) {
      eff_1l_data = get_from_lut(effTrigger_1m_data_, lepton_pt_, lepton_eta_);
      eff_1l_mc = get_from_lut(effTrigger_1m_mc_, lepton_pt_, lepton_eta_);
      eff_1l1tau_lepLeg_data = get_from_lut(effTrigger_1m1tau_lepLeg_data_, lepton_pt_, lepton_eta_);
      eff_1l1tau_lepLeg_mc = get_from_lut(effTrigger_1m1tau_lepLeg_mc_, lepton_pt_, lepton_eta_);
      if ( hadTau1_isGenTau ) {
	eff_1l1tau_tauLeg1_data = get_from_lut(effTrigger_1m1tau_tauLeg_data_gentau_, hadTau1_pt_, hadTau1_eta_);
	eff_1l1tau_tauLeg1_mc = get_from_lut(effTrigger_1m1tau_tauLeg_mc_gentau_, hadTau1_pt_, hadTau1_eta_);
      } else {
	eff_1l1tau_tauLeg1_data = get_from_lut(effTrigger_1m1tau_tauLeg_data_faketau_, hadTau1_pt_, hadTau1_eta_);
	eff_1l1tau_tauLeg1_mc = get_from_lut(effTrigger_1m1tau_tauLeg_mc_faketau_, hadTau1_pt_, hadTau1_eta_);
      }
      if ( hadTau2_isGenTau ) {
	eff_1l1tau_tauLeg2_data = get_from_lut(effTrigger_1m1tau_tauLeg_data_gentau_, hadTau2_pt_, hadTau2_eta_);
	eff_1l1tau_tauLeg2_mc = get_from_lut(effTrigger_1m1tau_tauLeg_mc_gentau_, hadTau2_pt_, hadTau2_eta_);
      } else {
	eff_1l1tau_tauLeg2_data = get_from_lut(effTrigger_1m1tau_tauLeg_data_faketau_, hadTau2_pt_, hadTau2_eta_);
	eff_1l1tau_tauLeg2_mc = get_from_lut(effTrigger_1m1tau_tauLeg_mc_faketau_, hadTau2_pt_, hadTau2_eta_);
      }
      isTriggered_1l = isTriggered_1m_;
      isTriggered_1l1tau = isTriggered_1m1tau_;
    } else assert(0);
    double eff_1l1tau_tauLegs_data = 1. - (1. - eff_1l1tau_tauLeg1_data)*(1. - eff_1l1tau_tauLeg2_data);
    double eff_1l1tau_tauLegs_mc = 1. - (1. - eff_1l1tau_tauLeg1_mc)*(1. - eff_1l1tau_tauLeg2_mc);
    //-------------------------------------------------------------------------------------------------------------------
    // CV: data/MC corrections are agreed as discussed on HTT working mailing list 
    //    (email from Alexei Raspereza on February 22nd 2017)    
    if ( isTriggered_1l && isTriggered_1l1tau ) { // case 4: both single lepton trigger and lepton+tau cross trigger fire
      double eff_data = eff_1l_data*eff_1l1tau_tauLegs_data;
      double eff_mc = eff_1l_mc*eff_1l1tau_tauLegs_mc;
      sf = compSF(eff_data, eff_mc);
    } else if ( isTriggered_1l1tau ) {            // case 3: lepton+tau cross trigger fires, single lepton trigger doesn't fire
      double eff_data = (eff_1l1tau_lepLeg_data - eff_1l_data)*eff_1l1tau_tauLegs_data;
      double eff_mc = (eff_1l1tau_lepLeg_mc - eff_1l_mc)*eff_1l1tau_tauLegs_mc;
      sf = compSF(eff_data, eff_mc);
    } else if ( isTriggered_1l ) {                // case 2: single lepton trigger fires, lepton+tau cross trigger doesn't fire
      double eff_data = eff_1l1tau_lepLeg_data*(1. - eff_1l1tau_tauLegs_data);
      double eff_mc = eff_1l1tau_lepLeg_mc*(1. - eff_1l1tau_tauLegs_mc);
      sf = compSF(eff_data, eff_mc);
    } else {                                      // case 1: neither single lepton trigger nor lepton+tau cross trigger fires (SF doesn't matter, as event does not pass event selection)
      sf = 0.;
    }
    //-------------------------------------------------------------------------------------------------------------------
  } else assert(0);
  //std::cout << "<Data_to_MC_CorrectionInterface::getSF_triggerEff>: sf = " << sf << std::endl;
  return sf;
}
