#include "tthAnalysis/HiggsToTauTau/interface/Data_to_MC_CorrectionInterface_1l_2tau_trigger.h"

#include "tthAnalysis/HiggsToTauTau/interface/leptonTypes.h" // kElectron, kMuon
#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // kEra_2017
#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h" // cmsException()
#include "tthAnalysis/HiggsToTauTau/interface/data_to_MC_corrections_auxFunctions.h" // aux::

#include <TString.h> // Form()
#include <TMath.h> // TMath::Abs()

#include <boost/algorithm/string/predicate.hpp> // boost::ends_with()

#include <cassert> // assert()

Data_to_MC_CorrectionInterface_1l_2tau_trigger::Data_to_MC_CorrectionInterface_1l_2tau_trigger(const edm::ParameterSet & cfg)
  : effTrigger_tauLeg_(nullptr)
  , hadTauSelection_(cfg.getParameter<std::string>("hadTauSelection"))
  , isDEBUG_(cfg.exists("isDEBUG") ? cfg.getParameter<bool>("isDEBUG") : false)
  , lepton_type_(-1)
  , lepton_pt_(0.)
  , lepton_eta_(0.)
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

  if(era_ == kEra_2017)
  {
    const std::vector<double> etaBinEdges_1e = { -1., 1.48, 2.1 };
    const int numEtaBins_1e = etaBinEdges_1e.size() - 1;

    for(int idxEtaBin = 0; idxEtaBin < numEtaBins_1e; ++idxEtaBin)
    {
      const double etaMin = etaBinEdges_1e[idxEtaBin];
      const double etaMax = etaBinEdges_1e[idxEtaBin + 1];
      const std::string etaBinLabel = aux::getEtaBinLabel(etaMin, etaMax);

      effTrigger_1e_data_.push_back(new lutWrapperTGraph(
        inputFiles_,
        "tthAnalysis/HiggsToTauTau/data/triggerSF/2017/Electron_Ele32orEle35_eff.root",
        Form("ZMassEta%s_Data", etaBinLabel.data()),
        lut::kXptYabsEta, -1., -1., lut::kLimit, etaMin, etaMax, lut::kCut
      ));
      effTrigger_1e_mc_.push_back(new lutWrapperTGraph(
        inputFiles_,
        "tthAnalysis/HiggsToTauTau/data/triggerSF/2017/Electron_Ele32orEle35_eff.root",
        Form("ZMassEta%s_MC", etaBinLabel.data()),
        lut::kXptYabsEta, -1., -1., lut::kLimit, etaMin, etaMax, lut::kCut
      ));
    }

    const std::vector<double> etaBinEdges_1e_1tau_lepLeg = { -1., 1.48, 2.1 };
    const int numEtaBins_1e_1tau_lepLeg = etaBinEdges_1e_1tau_lepLeg.size() - 1;

    for(int idxEtaBin = 0; idxEtaBin < numEtaBins_1e_1tau_lepLeg; ++idxEtaBin)
    {
      const double etaMin = etaBinEdges_1e_1tau_lepLeg[idxEtaBin];
      const double etaMax = etaBinEdges_1e_1tau_lepLeg[idxEtaBin + 1];
      const std::string etaBinLabel = aux::getEtaBinLabel(etaMin, etaMax);

      effTrigger_1e1tau_lepLeg_data_.push_back(new lutWrapperTGraph(
        inputFiles_,
        "tthAnalysis/HiggsToTauTau/data/triggerSF/2017/Electron_EleTau_Ele24_eff.root",
        Form("ZMassEta%s_Data", etaBinLabel.data()),
        lut::kXptYabsEta, -1., -1., lut::kLimit, etaMin, etaMax, lut::kCut
      ));
      effTrigger_1e1tau_lepLeg_mc_.push_back(new lutWrapperTGraph(
        inputFiles_,
        "tthAnalysis/HiggsToTauTau/data/triggerSF/2017/Electron_EleTau_Ele24_eff.root",
        Form("ZMassEta%s_MC", etaBinLabel.data()),
        lut::kXptYabsEta, -1., -1., lut::kLimit, etaMin, etaMax, lut::kCut
      ));
    }

    const std::vector<double> etaBinEdges_1m = { -1., 0.9, 1.2, 2.1 };
    const int numEtaBins_1m = etaBinEdges_1m.size() - 1;

    for(int idxEtaBin = 0; idxEtaBin < numEtaBins_1m; ++idxEtaBin)
    {
      const double etaMin = etaBinEdges_1m[idxEtaBin];
      const double etaMax = etaBinEdges_1m[idxEtaBin + 1];
      const std::string etaBinLabel = aux::getEtaBinLabel(etaMin, etaMax);

      effTrigger_1m_data_.push_back(new lutWrapperTGraph(
        inputFiles_,
        "tthAnalysis/HiggsToTauTau/data/triggerSF/2017/Muon_IsoMu24orIsoMu27_eff.root",
        Form("ZMassEta%s_Data", etaBinLabel.data()),
        lut::kXptYabsEta, -1., -1., lut::kLimit, etaMin, etaMax, lut::kCut
      ));
      effTrigger_1m_mc_.push_back(new lutWrapperTGraph(
        inputFiles_,
        "tthAnalysis/HiggsToTauTau/data/triggerSF/2017/Muon_IsoMu24orIsoMu27_eff.root",
        Form("ZMassEta%s_MC", etaBinLabel.data()),
        lut::kXptYabsEta, -1., -1., lut::kLimit, etaMin, etaMax, lut::kCut
      ));
    }

    const std::vector<double> etaBinEdges_1m1tau_lepLeg = { -1., 0.9, 1.2, 2.1 };
    const int numEtaBins_1m1tau_lepLeg = etaBinEdges_1m1tau_lepLeg.size() - 1;

    for(int idxEtaBin = 0; idxEtaBin < numEtaBins_1m1tau_lepLeg; ++idxEtaBin)
    {
      const double etaMin = etaBinEdges_1m1tau_lepLeg[idxEtaBin];
      const double etaMax = etaBinEdges_1m1tau_lepLeg[idxEtaBin + 1];
      const std::string etaBinLabel = aux::getEtaBinLabel(etaMin, etaMax);

      effTrigger_1m1tau_lepLeg_data_.push_back(new lutWrapperTGraph(
        inputFiles_,
        "tthAnalysis/HiggsToTauTau/data/triggerSF/2017/Muon_MuTau_IsoMu20_eff.root",
        Form("ZMassEta%s_Data", etaBinLabel.data()),
        lut::kXptYabsEta, -1., -1., lut::kLimit, etaMin, etaMax, lut::kCut
      ));
      effTrigger_1m1tau_lepLeg_mc_.push_back(new lutWrapperTGraph(
        inputFiles_,
        "tthAnalysis/HiggsToTauTau/data/triggerSF/2017/Muon_MuTau_IsoMu20_eff.root",
        Form("ZMassEta%s_MC", etaBinLabel.data()),
        lut::kXptYabsEta, -1., -1., lut::kLimit, etaMin, etaMax, lut::kCut
      ));
    }
  } // era_
  else
  {
    assert(0);
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

Data_to_MC_CorrectionInterface_1l_2tau_trigger::~Data_to_MC_CorrectionInterface_1l_2tau_trigger()
{
  aux::clearCollection(effTrigger_1e_data_);
  aux::clearCollection(effTrigger_1e_mc_);
  aux::clearCollection(effTrigger_1e1tau_lepLeg_data_);
  aux::clearCollection(effTrigger_1e1tau_lepLeg_mc_);

  aux::clearCollection(effTrigger_1m_data_);
  aux::clearCollection(effTrigger_1m_mc_);
  aux::clearCollection(effTrigger_1m1tau_lepLeg_data_);
  aux::clearCollection(effTrigger_1m1tau_lepLeg_mc_);
}

void
Data_to_MC_CorrectionInterface_1l_2tau_trigger::setTriggerBits(bool isTriggered_1e,
                                                               bool isTriggered_1e1tau,
                                                               bool isTriggered_1m,
                                                               bool isTriggered_1m1tau)
{
  isTriggered_1e_     = isTriggered_1e;
  isTriggered_1e1tau_ = isTriggered_1e1tau;
  isTriggered_1m_     = isTriggered_1m;
  isTriggered_1m1tau_ = isTriggered_1m1tau;
}

void
Data_to_MC_CorrectionInterface_1l_2tau_trigger::setLeptons(int lepton_type,
                                                           double lepton_pt,
                                                           double lepton_eta)
{
  lepton_type_ = lepton_type;
  lepton_pt_   = lepton_pt;
  lepton_eta_  = lepton_eta;
}

void
Data_to_MC_CorrectionInterface_1l_2tau_trigger::setHadTaus(double hadTau1_pt, double hadTau1_eta, double hadTau1_phi,
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
Data_to_MC_CorrectionInterface_1l_2tau_trigger::getWeight_triggerEff() const
{
  assert(0);
}

double
Data_to_MC_CorrectionInterface_1l_2tau_trigger::getSF_triggerEff() const
{
  if(isDEBUG_)
  {
    std::cout << "<Data_to_MC_CorrectionInterface_1l_2tau_trigger::getSF_triggerEff>:\n";
  }

  double sf = 1.;
  if(era_ == kEra_2017)
  {
    double eff_1l_data             = 0.;
    double eff_1l_mc               = 0.;
    double eff_1l1tau_lepLeg_data  = 0.;
    double eff_1l1tau_lepLeg_mc    = 0.;
    double eff_1l1tau_tauLeg1_data = 0.;
    double eff_1l1tau_tauLeg1_mc   = 0.;
    double eff_1l1tau_tauLeg2_data = 0.;
    double eff_1l1tau_tauLeg2_mc   = 0.;

    bool isTriggered_1l     = false;
    bool isTriggered_1l1tau = false;

    if(lepton_type_ == kElectron)
    {
      if(isDEBUG_)
      {
        std::cout << "electron: pT = " << lepton_pt_ << ", eta = " << lepton_eta_ << '\n';
      }
      eff_1l_data            = get_from_lut(effTrigger_1e_data_,            lepton_pt_, lepton_eta_, isDEBUG_);
      eff_1l_mc              = get_from_lut(effTrigger_1e_mc_,              lepton_pt_, lepton_eta_, isDEBUG_);
      eff_1l1tau_lepLeg_data = get_from_lut(effTrigger_1e1tau_lepLeg_data_, lepton_pt_, lepton_eta_, isDEBUG_);
      eff_1l1tau_lepLeg_mc   = get_from_lut(effTrigger_1e1tau_lepLeg_mc_,   lepton_pt_, lepton_eta_, isDEBUG_);

      eff_1l1tau_tauLeg1_data = 0.;
      eff_1l1tau_tauLeg1_mc = 0.;
      if ( TMath::Abs(hadTau1_eta_) <= 2.1 ) {
	eff_1l1tau_tauLeg1_data = effTrigger_tauLeg_->getETauEfficiencyData(hadTau1_pt_, hadTau1_eta_, hadTau1_phi_);
	eff_1l1tau_tauLeg1_mc   = effTrigger_tauLeg_->getETauEfficiencyMC(hadTau1_pt_, hadTau1_eta_, hadTau1_phi_); 
      }
      
      eff_1l1tau_tauLeg2_data = 0.;
      eff_1l1tau_tauLeg2_mc = 0.;
      if ( TMath::Abs(hadTau2_eta_) <= 2.1 ) {
	eff_1l1tau_tauLeg2_data = effTrigger_tauLeg_->getETauEfficiencyData(hadTau2_pt_, hadTau2_eta_, hadTau2_phi_);
	eff_1l1tau_tauLeg2_mc   = effTrigger_tauLeg_->getETauEfficiencyMC(hadTau2_pt_, hadTau2_eta_, hadTau2_phi_); 
      }

      isTriggered_1l     = isTriggered_1e_;
      isTriggered_1l1tau = isTriggered_1e1tau_;
    }
    else if(lepton_type_ == kMuon)
    {
      if(isDEBUG_)
      {
        std::cout << "muon: pT = " << lepton_pt_ << ", eta = " << lepton_eta_ << '\n';
      }
      eff_1l_data            = get_from_lut(effTrigger_1m_data_,            lepton_pt_, lepton_eta_, isDEBUG_);
      eff_1l_mc              = get_from_lut(effTrigger_1m_mc_,              lepton_pt_, lepton_eta_, isDEBUG_);
      eff_1l1tau_lepLeg_data = get_from_lut(effTrigger_1m1tau_lepLeg_data_, lepton_pt_, lepton_eta_, isDEBUG_);
      eff_1l1tau_lepLeg_mc   = get_from_lut(effTrigger_1m1tau_lepLeg_mc_,   lepton_pt_, lepton_eta_, isDEBUG_);

      eff_1l1tau_tauLeg1_data = 0.;
      eff_1l1tau_tauLeg1_mc = 0.;
      if ( TMath::Abs(hadTau1_eta_) <= 2.1 ) {
	eff_1l1tau_tauLeg1_data = effTrigger_tauLeg_->getMuTauEfficiencyData(hadTau1_pt_, hadTau1_eta_, hadTau1_phi_);
	eff_1l1tau_tauLeg1_mc = effTrigger_tauLeg_->getMuTauEfficiencyMC(hadTau1_pt_, hadTau1_eta_, hadTau1_phi_);
      }
      
      eff_1l1tau_tauLeg2_data = 0.;
      eff_1l1tau_tauLeg2_mc = 0.;
      if ( TMath::Abs(hadTau2_eta_) <= 2.1 ) {
	eff_1l1tau_tauLeg2_data = effTrigger_tauLeg_->getMuTauEfficiencyData(hadTau2_pt_, hadTau2_eta_, hadTau2_phi_);
	eff_1l1tau_tauLeg2_mc = effTrigger_tauLeg_->getMuTauEfficiencyMC(hadTau2_pt_, hadTau2_eta_, hadTau2_phi_); 
      }

      isTriggered_1l     = isTriggered_1m_;
      isTriggered_1l1tau = isTriggered_1m1tau_;
    }
    else
    {
      assert(0);
    }

    const double eff_1l1tau_tauLegs_data = 1. - (1. - eff_1l1tau_tauLeg1_data) * (1. - eff_1l1tau_tauLeg2_data);
    const double eff_1l1tau_tauLegs_mc   = 1. - (1. - eff_1l1tau_tauLeg1_mc)   * (1. - eff_1l1tau_tauLeg2_mc);
    if(isDEBUG_)
    {
      std::cout << "hadTau (lead):    pT = " << hadTau1_pt_ << ", eta = " << hadTau1_eta_ << "\n"
                   "hadTau (sublead): pT = " << hadTau2_pt_ << ", eta = " << hadTau2_eta_ << "\n"
                   "eff (L):      data = " << eff_1l_data             << ", MC = " << eff_1l_mc             << "\n"
                   "eff (X_lep):  data = " << eff_1l1tau_lepLeg_data  << ", MC = " << eff_1l1tau_lepLeg_mc  << "\n"
                   "eff (X_tau):  data = " << eff_1l1tau_tauLegs_data << ", MC = " << eff_1l1tau_tauLegs_mc << "\n"
                   "eff (X_tau1): data = " << eff_1l1tau_tauLeg1_data << ", MC = " << eff_1l1tau_tauLeg1_mc << "\n"
                   "eff (X_tau2): data = " << eff_1l1tau_tauLeg2_data << ", MC = " << eff_1l1tau_tauLeg2_mc << '\n'
      ;
    }

    //-------------------------------------------------------------------------------------------------------------------
    // CV: data/MC corrections are agreed as discussed on HTT working mailing list 
    //     (email from Alexei Raspereza on February 22nd 2017)

    if(isTriggered_1l && isTriggered_1l1tau)
    {
      // case 4: both single lepton trigger and lepton+tau cross trigger fire

      const double eff_data = std::min(eff_1l_data, eff_1l1tau_lepLeg_data) * eff_1l1tau_tauLegs_data;
      const double eff_mc   = std::min(eff_1l_mc,   eff_1l1tau_lepLeg_mc)   * eff_1l1tau_tauLegs_mc;

      sf = aux::compSF(eff_data, eff_mc);
      if(isDEBUG_)
      {
        std::cout << "case 4: both single lepton trigger and lepton+tau cross trigger fire\n"
                     " eff: data = " << eff_data << ", MC = " << eff_mc << " --> SF = " << sf << '\n';
      }
    }
    else if(isTriggered_1l1tau)
    {
      // case 3: lepton+tau cross trigger fires, single lepton trigger doesn't fire

      const double eff_data = std::max(1.e-2, (eff_1l1tau_lepLeg_data - eff_1l_data) * eff_1l1tau_tauLegs_data);
      const double eff_mc   = std::max(1.e-2, (eff_1l1tau_lepLeg_mc   - eff_1l_mc)   * eff_1l1tau_tauLegs_mc);

      sf = aux::compSF(eff_data, eff_mc);
      if(isDEBUG_)
      {
        std::cout << "case 3: lepton+tau cross trigger fires, single lepton trigger doesn't fire\n"
                     " eff: data = " << eff_data << ", MC = " << eff_mc << " --> SF = " << sf << '\n';
      }
    }
    else if(isTriggered_1l)
    {
      // case 2: single lepton trigger fires, lepton+tau cross trigger doesn't fire

      const double eff_data = std::max(1.e-2, eff_1l_data - eff_1l1tau_tauLegs_data * std::min(eff_1l_data, eff_1l1tau_lepLeg_data));
      const double eff_mc   = std::max(1.e-2, eff_1l_mc   - eff_1l1tau_tauLegs_mc   * std::min(eff_1l_mc,   eff_1l1tau_lepLeg_mc));

      sf = aux::compSF(eff_data, eff_mc);
      if(isDEBUG_)
      {
        std::cout << "case 2: single lepton trigger fires, lepton+tau cross trigger doesn't fire\n"
                     " eff: data = " << eff_data << ", MC = " << eff_mc << " --> SF = " << sf << '\n';
      }
    }
    else
    {
      // case 1: neither single lepton trigger nor lepton+tau cross trigger fires
      // (SF doesn't matter, as event does not pass event selection)

      sf = 0.;
      if(isDEBUG_)
      {
        std::cout << "case 1: neither single lepton trigger nor lepton+tau cross trigger fires\n"
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
