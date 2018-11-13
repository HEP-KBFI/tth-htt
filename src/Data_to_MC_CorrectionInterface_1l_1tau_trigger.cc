#include "tthAnalysis/HiggsToTauTau/interface/Data_to_MC_CorrectionInterface_1l_1tau_trigger.h"

#include "tthAnalysis/TauTriggerSFs2017/interface/TauTriggerSFs2017.h"
#include "tthAnalysis/HiggsToTauTau/interface/leptonTypes.h" // kElectron, kMuon
#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // kEra_2017
#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h" // cmsException()
#include "tthAnalysis/HiggsToTauTau/interface/data_to_MC_corrections_auxFunctions.h" // aux::
#include "tthAnalysis/HiggsToTauTau/interface/sysUncertOptions.h" // TriggerSFsys, getTriggerSF_option()

#include <TString.h> // Form()
#include <TMath.h> // TMath::Abs()

#include <boost/algorithm/string/predicate.hpp> // boost::ends_with()

#include <cassert> // assert()

Data_to_MC_CorrectionInterface_1l_1tau_trigger::Data_to_MC_CorrectionInterface_1l_1tau_trigger(const edm::ParameterSet & cfg)
  : effTrigger_tauLeg_(nullptr)
  , era_(get_era(cfg.getParameter<std::string>("era")))
  , hadTauSelection_(cfg.getParameter<std::string>("hadTauSelection"))
  , isDEBUG_(cfg.exists("isDEBUG") ? cfg.getParameter<bool>("isDEBUG") : false)
  , triggerSF_option_(TauTriggerSFs2017::kCentral)
  , lepton_type_(-1)
  , lepton_pt_(0.)
  , lepton_eta_(0.)
  , hadTau_genPdgId_(0)
  , hadTau_pt_(0.)
  , hadTau_eta_(0.)
  , hadTau_phi_(0.)
  , hadTau_decayMode_(0)
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
    const std::vector<double> etaBinEdges_1e = { -1., 1.48, 2.1 };
    assert(etaBinEdges_1e.size() > 0);
    const std::size_t numEtaBins_1e = etaBinEdges_1e.size() - 1;
    for(std::size_t idxEtaBin = 0; idxEtaBin < numEtaBins_1e; ++idxEtaBin)
    {
      const double etaMin = etaBinEdges_1e[idxEtaBin];
      const double etaMax = etaBinEdges_1e[idxEtaBin + 1];
      const std::string etaBinLabel = aux::getEtaBinLabel(etaMin, etaMax);
      effTrigger_1e_data_.push_back(new lutWrapperTGraph(
        inputFiles_,
        "tthAnalysis/HiggsToTauTau/data/triggerSF/2016/Electron_Ele25WPTight_eff.root",
        Form("ZMassEta%s_Data", etaBinLabel.data()),
        lut::kXptYabsEta,
        -1., -1., lut::kLimit, etaMin, etaMax, lut::kCut
      ));
      effTrigger_1e_mc_.push_back(new lutWrapperTGraph(
        inputFiles_,
        "tthAnalysis/HiggsToTauTau/data/triggerSF/2016/Electron_Ele25WPTight_eff.root",
        Form("ZMassEta%s_MC", etaBinLabel.data()),
        lut::kXptYabsEta,
        -1., -1., lut::kLimit, etaMin, etaMax, lut::kCut
      ));
    }

    const std::vector<double> etaBinEdges_1e_1tau_lepLeg = { -1., 1.48, 2.1 };
    assert(etaBinEdges_1e_1tau_lepLeg.size() > 0);
    const std::size_t numEtaBins_1e_1tau_lepLeg = etaBinEdges_1e_1tau_lepLeg.size() - 1;
    for(std::size_t idxEtaBin = 0; idxEtaBin < numEtaBins_1e_1tau_lepLeg; ++idxEtaBin)
    {
      const double etaMin = etaBinEdges_1e_1tau_lepLeg[idxEtaBin];
      const double etaMax = etaBinEdges_1e_1tau_lepLeg[idxEtaBin + 1];
      const std::string etaBinLabel = aux::getEtaBinLabel(etaMin, etaMax);
      effTrigger_1e1tau_lepLeg_data_.push_back(new lutWrapperTGraph(
        inputFiles_,
        "tthAnalysis/HiggsToTauTau/data/triggerSF/2016/Electron_Ele24_eff.root",
        Form("ZMassEta%s_Data", etaBinLabel.data()),
        lut::kXptYabsEta,
        -1., -1., lut::kLimit, etaMin, etaMax, lut::kCut
      ));
      effTrigger_1e1tau_lepLeg_mc_.push_back(new lutWrapperTGraph(
        inputFiles_,
        "tthAnalysis/HiggsToTauTau/data/triggerSF/2016/Electron_Ele24_eff.root",
        Form("ZMassEta%s_MC", etaBinLabel.data()),
        lut::kXptYabsEta,
        -1., -1., lut::kLimit, etaMin, etaMax, lut::kCut
      ));
    }

    const std::vector<double> etaBinEdges_1e1tau_tauLeg = { -1., 1.48, 2.1 };
    assert(etaBinEdges_1e1tau_tauLeg.size() > 0);
    const std::size_t numEtaBins_1e1tau_tauLeg = etaBinEdges_1e1tau_tauLeg.size() - 1;
    for(std::size_t idxEtaBin = 0; idxEtaBin < numEtaBins_1e1tau_tauLeg; ++idxEtaBin)
    {
      const double etaMin = etaBinEdges_1e1tau_tauLeg[idxEtaBin];
      const double etaMax = etaBinEdges_1e1tau_tauLeg[idxEtaBin + 1];
      std::string etaBinLabel;
      switch(idxEtaBin)
      {
        case 0: etaBinLabel = "barrel"; break;
        case 1: etaBinLabel = "endcap"; break;
        default: assert(0);
      }

      const std::string hadTauSelectionLabel = aux::getHadTauSelectionLabel(hadTauSelection_);
      const std::vector<int> hadTauDecayModes_1e1tau_tauLeg = { 0, 1, 2, 10 };

      for(int hadTauDecayMode: hadTauDecayModes_1e1tau_tauLeg)
      {
        const std::string hadTauDecayModeLabel = aux::getHadTauDecayModeLabel(hadTauDecayMode);
        effTrigger_1e1tau_tauLeg_data_gentau_[hadTauDecayMode].push_back(new lutWrapperTGraph(
          inputFiles_, "tthAnalysis/HiggsToTauTau/data/triggerSF/2016/trigger_sf_et.root",
          Form("data_genuine_%s_%s_%s", etaBinLabel.data(),
          hadTauSelectionLabel.data(), hadTauDecayModeLabel.data()),
          lut::kXptYabsEta,
          0., 150., lut::kLimit, etaMin, etaMax, lut::kCut // not sure if lut:: args are correct here
        ));
        effTrigger_1e1tau_tauLeg_data_faketau_[hadTauDecayMode].push_back(new lutWrapperTGraph(
          inputFiles_,
          "tthAnalysis/HiggsToTauTau/data/triggerSF/2016/trigger_sf_et.root",
          Form("data_fake_%s_%s_%s", etaBinLabel.data(), hadTauSelectionLabel.data(), hadTauDecayModeLabel.data()),
          lut::kXptYabsEta,
          0., 150., lut::kLimit, etaMin, etaMax, lut::kCut // not sure if lut:: args are correct here
        ));
        //---------------------------------------------------------------------------------------------------------------
        // CV: need work-around for MC, because we do not have all e+tau cross triggers stored in VHbb Ntuples V25
        //    (only HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau30_v*)
        effTrigger_1e1tau_tauLeg_mc_gentau_[hadTauDecayMode].push_back(new lutWrapperTGraph(
          inputFiles_,
          "tthAnalysis/HiggsToTauTau/data/triggerSF/2016/tauleg_of_lepton_plus_tau_real_taus_skim_mc_v2.root",
          Form("%s_lowmt_zmass_sub_%s_%s_HLT_LooseIso30_L1iso26/tau_pt", etaBinLabel.data(), hadTauSelectionLabel.data(), hadTauDecayModeLabel.data()),
          lut::kXptYabsEta,
          0., 150., lut::kLimit, etaMin, etaMax, lut::kCut // not sure if lut:: args are correct here
        ));
        effTrigger_1e1tau_tauLeg_mc_faketau_[hadTauDecayMode].push_back(new lutWrapperTGraph(
          inputFiles_,
          "tthAnalysis/HiggsToTauTau/data/triggerSF/2016/tauleg_of_lepton_plus_tau_real_taus_skim_mc_v2.root",
          Form("%s_highmt_os_%s_%s_HLT_LooseIso30_L1iso26/tau_pt", etaBinLabel.data(), hadTauSelectionLabel.data(), hadTauDecayModeLabel.data()),
          lut::kXptYabsEta,
          0., 150., lut::kLimit, etaMin, etaMax, lut::kCut
        ));
        //---------------------------------------------------------------------------------------------------------------
      }
    }

    const std::vector<double> etaBinEdges_1m = { -1., 0.9, 1.2, 2.1 };
    assert(etaBinEdges_1m.size() > 0);
    const std::size_t numEtaBins_1m = etaBinEdges_1m.size() - 1;
    for(std::size_t idxEtaBin = 0; idxEtaBin < numEtaBins_1m; ++idxEtaBin)
    {
      const double etaMin = etaBinEdges_1m[idxEtaBin];
      const double etaMax = etaBinEdges_1m[idxEtaBin + 1];
      const std::string etaBinLabel = aux::getEtaBinLabel(etaMin, etaMax);
      effTrigger_1m_data_.push_back(new lutWrapperTGraph(
        inputFiles_,
        "tthAnalysis/HiggsToTauTau/data/triggerSF/2016/Muon_Mu22OR_eta2p1_eff.root", Form("ZMassEta%s_Data", etaBinLabel.data()),
        lut::kXptYabsEta,
        -1., -1., lut::kLimit, etaMin, etaMax, lut::kCut
      ));
      effTrigger_1m_mc_.push_back(new lutWrapperTGraph(
        inputFiles_,
        "tthAnalysis/HiggsToTauTau/data/triggerSF/2016/Muon_Mu22OR_eta2p1_eff.root",
        Form("ZMassEta%s_MC", etaBinLabel.data()),
        lut::kXptYabsEta,
        -1., -1., lut::kLimit, etaMin, etaMax, lut::kCut
      ));
    }

    const std::vector<double> etaBinEdges_1m1tau_lepLeg = { -1., 0.9, 1.2, 2.1 };
    assert(etaBinEdges_1m1tau_lepLeg.size() > 0);
    const std::size_t numEtaBins_1m1tau_lepLeg = etaBinEdges_1m1tau_lepLeg.size() - 1;
    for(std::size_t idxEtaBin = 0; idxEtaBin < numEtaBins_1m1tau_lepLeg; ++idxEtaBin)
    {
      const double etaMin = etaBinEdges_1m1tau_lepLeg[idxEtaBin];
      const double etaMax = etaBinEdges_1m1tau_lepLeg[idxEtaBin + 1];
      const std::string etaBinLabel = aux::getEtaBinLabel(etaMin, etaMax);
      effTrigger_1m1tau_lepLeg_data_.push_back(new lutWrapperTGraph(
        inputFiles_,
        "tthAnalysis/HiggsToTauTau/data/triggerSF/2016/Muon_Mu19leg_2016BtoH_eff.root",
        Form("ZMassEta%s_Data", etaBinLabel.data()),
        lut::kXptYabsEta,
        -1., -1., lut::kLimit, etaMin, etaMax, lut::kCut
      ));
      effTrigger_1m1tau_lepLeg_mc_.push_back(new lutWrapperTGraph(
        inputFiles_,
        "tthAnalysis/HiggsToTauTau/data/triggerSF/2016/Muon_Mu19leg_2016BtoH_eff.root",
        Form("ZMassEta%s_MC", etaBinLabel.data()),
        lut::kXptYabsEta, -1., -1., lut::kLimit, etaMin, etaMax, lut::kCut
      ));
    }

    const std::vector<double> etaBinEdges_1m1tau_tauLeg = { -1., 1.48, 2.1 };
    assert(etaBinEdges_1m1tau_tauLeg.size() > 0);
    const std::size_t numEtaBins_1m1tau_tauLeg = etaBinEdges_1m1tau_tauLeg.size() - 1;
    for(std::size_t idxEtaBin = 0; idxEtaBin < numEtaBins_1m1tau_tauLeg; ++idxEtaBin)
    {
      const double etaMin = etaBinEdges_1m1tau_tauLeg[idxEtaBin];
      const double etaMax = etaBinEdges_1m1tau_tauLeg[idxEtaBin + 1];
      std::string etaBinLabel;
      switch(idxEtaBin)
      {
        case 0: etaBinLabel = "barrel"; break;
        case 1: etaBinLabel = "endcap"; break;
        default: assert(0);
      }
      const std::string hadTauSelectionLabel = aux::getHadTauSelectionLabel(hadTauSelection_);
      effTrigger_1m1tau_tauLeg_data_gentau_.push_back(new lutWrapperTGraph(
        inputFiles_,
        "tthAnalysis/HiggsToTauTau/data/triggerSF/2016/trigger_sf_mt.root",
        Form("data_genuine_%s_%s", etaBinLabel.data(), hadTauSelectionLabel.data()),
        lut::kXptYabsEta,
        0., 150., lut::kLimit, etaMin, etaMax, lut::kCut
      ));
      effTrigger_1m1tau_tauLeg_data_faketau_.push_back(new lutWrapperTGraph(
        inputFiles_,
        "tthAnalysis/HiggsToTauTau/data/triggerSF/2016/trigger_sf_mt.root",
        Form("data_fake_%s_%s", etaBinLabel.data(), hadTauSelectionLabel.data()),
        lut::kXptYabsEta,
        0., 150., lut::kLimit, etaMin, etaMax, lut::kCut
      ));
      effTrigger_1m1tau_tauLeg_mc_gentau_.push_back(new lutWrapperTGraph(
        inputFiles_,
        "tthAnalysis/HiggsToTauTau/data/triggerSF/2016/trigger_sf_mt.root",
        Form("mc_genuine_%s_%s", etaBinLabel.data(), hadTauSelectionLabel.data()),
        lut::kXptYabsEta,
        0., 150., lut::kLimit, etaMin, etaMax, lut::kCut
      ));
      effTrigger_1m1tau_tauLeg_mc_faketau_.push_back(new lutWrapperTGraph(
        inputFiles_,
        "tthAnalysis/HiggsToTauTau/data/triggerSF/2016/trigger_sf_mt.root",
        Form("mc_fake_%s_%s", etaBinLabel.data(), hadTauSelectionLabel.data()),
        lut::kXptYabsEta,
        0., 150., lut::kLimit, etaMin, etaMax, lut::kCut
      ));
    }
  }
  else if(era_ == kEra_2017)
  {
    const std::vector<double> etaBinEdges_1e = { -1., 1.48, 2.1 };
    assert(etaBinEdges_1e.size() > 0);
    const std::size_t numEtaBins_1e = etaBinEdges_1e.size() - 1;

    for(std::size_t idxEtaBin = 0; idxEtaBin < numEtaBins_1e; ++idxEtaBin)
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
    assert(etaBinEdges_1e_1tau_lepLeg.size() > 0);
    const std::size_t numEtaBins_1e_1tau_lepLeg = etaBinEdges_1e_1tau_lepLeg.size() - 1;

    for(std::size_t idxEtaBin = 0; idxEtaBin < numEtaBins_1e_1tau_lepLeg; ++idxEtaBin)
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
    assert(etaBinEdges_1m.size() > 0);
    const std::size_t numEtaBins_1m = etaBinEdges_1m.size() - 1;

    for(std::size_t idxEtaBin = 0; idxEtaBin < numEtaBins_1m; ++idxEtaBin)
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
    assert(etaBinEdges_1m1tau_lepLeg.size() > 0);
    const std::size_t numEtaBins_1m1tau_lepLeg = etaBinEdges_1m1tau_lepLeg.size() - 1;

    for(std::size_t idxEtaBin = 0; idxEtaBin < numEtaBins_1m1tau_lepLeg; ++idxEtaBin)
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

    const LocalFileInPath inputFileName_tauLeg("tthAnalysis/TauTriggerSFs2017/data/tauTriggerEfficiencies2017_New.root");
    const LocalFileInPath inputFileName_tauLeg_old("tthAnalysis/TauTriggerSFs2017/data/tauTriggerEfficiencies2017.root");
    const std::string hadTauSelection_TauTriggerSFs2017 = aux::get_hadTauSelection_TauTriggerSFs2017(hadTauSelection_);
    const std::string wpType = "dR0p3"; // or "MVA"
    effTrigger_tauLeg_ = new TauTriggerSFs2017(
          inputFileName_tauLeg.fullPath().data(), inputFileName_tauLeg_old.fullPath().data(), hadTauSelection_TauTriggerSFs2017, wpType
    );
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

Data_to_MC_CorrectionInterface_1l_1tau_trigger::~Data_to_MC_CorrectionInterface_1l_1tau_trigger()
{
  aux::clearCollection(effTrigger_1e_data_);
  aux::clearCollection(effTrigger_1e_mc_);
  aux::clearCollection(effTrigger_1e1tau_lepLeg_data_);
  aux::clearCollection(effTrigger_1e1tau_lepLeg_mc_);

  aux::clearCollection(effTrigger_1m_data_);
  aux::clearCollection(effTrigger_1m_mc_);
  aux::clearCollection(effTrigger_1m1tau_lepLeg_data_);
  aux::clearCollection(effTrigger_1m1tau_lepLeg_mc_);

  if(era_ == kEra_2016)
  {
    aux::clearCollection(effTrigger_1e1tau_tauLeg_data_gentau_);
    aux::clearCollection(effTrigger_1e1tau_tauLeg_data_faketau_);
    aux::clearCollection(effTrigger_1e1tau_tauLeg_mc_gentau_);
    aux::clearCollection(effTrigger_1e1tau_tauLeg_mc_faketau_);

    aux::clearCollection(effTrigger_1m1tau_tauLeg_data_gentau_);
    aux::clearCollection(effTrigger_1m1tau_tauLeg_data_faketau_);
    aux::clearCollection(effTrigger_1m1tau_tauLeg_mc_gentau_);
    aux::clearCollection(effTrigger_1m1tau_tauLeg_mc_faketau_);
  }
  else if(era_ == kEra_2017)
  {
    delete effTrigger_tauLeg_;
  }
}

void
Data_to_MC_CorrectionInterface_1l_1tau_trigger::setTriggerBits(bool isTriggered_1e,
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
Data_to_MC_CorrectionInterface_1l_1tau_trigger::setLeptons(int lepton_type,
                                                           double lepton_pt,
                                                           double lepton_eta)
{
  lepton_type_ = lepton_type;
  lepton_pt_   = lepton_pt;
  lepton_eta_  = lepton_eta;
}

void
Data_to_MC_CorrectionInterface_1l_1tau_trigger::setHadTaus(double hadTau_pt, double hadTau_eta, double hadTau_phi)
{
  hadTau_pt_  = hadTau_pt;
  hadTau_eta_ = hadTau_eta;
  hadTau_phi_ = hadTau_phi;
}

void
Data_to_MC_CorrectionInterface_1l_1tau_trigger::setHadTaus(int hadTau_genPdgId, double hadTau_pt, double hadTau_eta, int hadTau_decayMode)
{
  hadTau_genPdgId_  = hadTau_genPdgId;
  hadTau_pt_        = hadTau_pt;
  hadTau_eta_       = hadTau_eta;
  hadTau_decayMode_ = hadTau_decayMode;
}

double
Data_to_MC_CorrectionInterface_1l_1tau_trigger::getWeight_triggerEff() const
{
  assert(0);
}

double
Data_to_MC_CorrectionInterface_1l_1tau_trigger::getSF_triggerEff() const
{
  if(isDEBUG_)
  {
    std::cout << get_human_line(this, __func__, __LINE__) << '\n';
  }

  double eff_1l_data            = 0.;
  double eff_1l_mc              = 0.;
  double eff_1l1tau_lepLeg_data = 0.;
  double eff_1l1tau_lepLeg_mc   = 0.;
  double eff_1l1tau_tauLeg_data = 0.;
  double eff_1l1tau_tauLeg_mc   = 0.;

  bool isTriggered_1l     = false;
  bool isTriggered_1l1tau = false;

  double sf = 1.;
  if(era_ == kEra_2016)
  {
    const bool hadTau_isGenTau = (hadTau_genPdgId_ == 11 || hadTau_genPdgId_ == 13 || hadTau_genPdgId_ == 15);

    if(lepton_type_ == kElectron)
    {
      if(isDEBUG_)
      {
        std::cout << "electron: pT = " << lepton_pt_ << ", eta = " << lepton_eta_ << '\n';
      }

      eff_1l_data = get_from_lut(effTrigger_1e_data_, lepton_pt_, lepton_eta_, isDEBUG_);
      eff_1l_mc   = get_from_lut(effTrigger_1e_mc_,   lepton_pt_, lepton_eta_);
      eff_1l1tau_lepLeg_data = get_from_lut(effTrigger_1e1tau_lepLeg_data_, lepton_pt_, lepton_eta_, isDEBUG_);
      eff_1l1tau_lepLeg_mc   = get_from_lut(effTrigger_1e1tau_lepLeg_mc_,   lepton_pt_, lepton_eta_, isDEBUG_);

      if(hadTau_isGenTau)
      {
        eff_1l1tau_tauLeg_data = get_from_lut(effTrigger_1e1tau_tauLeg_data_gentau_, hadTau_pt_, hadTau_eta_, hadTau_decayMode_, isDEBUG_);
        eff_1l1tau_tauLeg_mc   = get_from_lut(effTrigger_1e1tau_tauLeg_mc_gentau_,   hadTau_pt_, hadTau_eta_, hadTau_decayMode_, isDEBUG_);
      }
      else
      {
        eff_1l1tau_tauLeg_data = get_from_lut(effTrigger_1e1tau_tauLeg_data_faketau_, hadTau_pt_, hadTau_eta_, hadTau_decayMode_, isDEBUG_);
        eff_1l1tau_tauLeg_mc   = get_from_lut(effTrigger_1e1tau_tauLeg_mc_faketau_,   hadTau_pt_, hadTau_eta_, hadTau_decayMode_, isDEBUG_);
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

      eff_1l_data = get_from_lut(effTrigger_1m_data_, lepton_pt_, lepton_eta_, isDEBUG_);
      eff_1l_mc   = get_from_lut(effTrigger_1m_mc_,   lepton_pt_, lepton_eta_, isDEBUG_);
      eff_1l1tau_lepLeg_data = get_from_lut(effTrigger_1m1tau_lepLeg_data_, lepton_pt_, lepton_eta_, isDEBUG_);
      eff_1l1tau_lepLeg_mc   = get_from_lut(effTrigger_1m1tau_lepLeg_mc_,   lepton_pt_, lepton_eta_);

      if(hadTau_isGenTau)
      {
        eff_1l1tau_tauLeg_data = get_from_lut(effTrigger_1m1tau_tauLeg_data_gentau_, hadTau_pt_, hadTau_eta_, isDEBUG_);
        eff_1l1tau_tauLeg_mc   = get_from_lut(effTrigger_1m1tau_tauLeg_mc_gentau_,   hadTau_pt_, hadTau_eta_, isDEBUG_);
      }
      else
      {
        eff_1l1tau_tauLeg_data = get_from_lut(effTrigger_1m1tau_tauLeg_data_faketau_, hadTau_pt_, hadTau_eta_, isDEBUG_);
        eff_1l1tau_tauLeg_mc   = get_from_lut(effTrigger_1m1tau_tauLeg_mc_faketau_,   hadTau_pt_, hadTau_eta_, isDEBUG_);
      }

      isTriggered_1l     = isTriggered_1m_;
      isTriggered_1l1tau = isTriggered_1m1tau_;
    }
    else
    {
      assert(0);
    }
  }
  else if(era_ == kEra_2017)
  {
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

      eff_1l1tau_tauLeg_data = 0.;
      eff_1l1tau_tauLeg_mc = 0.;
      if ( TMath::Abs(hadTau_eta_) <= 2.1 ) {
        eff_1l1tau_tauLeg_data = effTrigger_tauLeg_->getETauEfficiencyData(hadTau_pt_, hadTau_eta_, hadTau_phi_, triggerSF_option_);
        eff_1l1tau_tauLeg_mc   = effTrigger_tauLeg_->getETauEfficiencyMC(hadTau_pt_, hadTau_eta_, hadTau_phi_, triggerSF_option_);
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

      eff_1l1tau_tauLeg_data = 0.;
      eff_1l1tau_tauLeg_mc = 0.;
      if ( TMath::Abs(hadTau_eta_) <= 2.1 ) {
        eff_1l1tau_tauLeg_data = effTrigger_tauLeg_->getMuTauEfficiencyData(hadTau_pt_, hadTau_eta_, hadTau_phi_, triggerSF_option_);
        eff_1l1tau_tauLeg_mc = effTrigger_tauLeg_->getMuTauEfficiencyMC(hadTau_pt_, hadTau_eta_, hadTau_phi_, triggerSF_option_);
      }
      
      isTriggered_1l     = isTriggered_1m_;
      isTriggered_1l1tau = isTriggered_1m1tau_;
    }
    else
    {
      assert(0);
    }
  }
  else if(era_ == kEra_2018)
  {
    throw cmsException(this, __func__, __LINE__) << "Implement me!";
  }
  else
  {
    throw cmsException(this, __func__, __LINE__) << "Invalid era = " << era_;
  }
  if(isDEBUG_)
  {
    std::cout << "hadTau (lead):    pT = " << hadTau_pt_ << ", eta = " << hadTau_eta_ << "\n"
                 "eff (L):     data = " << eff_1l_data            << ", MC = " << eff_1l_mc            << "\n"
                 "eff (X_lep): data = " << eff_1l1tau_lepLeg_data << ", MC = " << eff_1l1tau_lepLeg_mc << "\n"
                 "eff (X_tau): data = " << eff_1l1tau_tauLeg_data << ", MC = " << eff_1l1tau_tauLeg_mc << "\n"
    ;
  }

  //-------------------------------------------------------------------------------------------------------------------
  // CV: data/MC corrections are agreed as discussed on HTT working mailing list
  //     (email from Alexei Raspereza on February 22nd 2017)

  if(isTriggered_1l && isTriggered_1l1tau)
  {
    // case 4: both single lepton trigger and lepton+tau cross trigger fire

    const double eff_data = std::min(eff_1l_data, eff_1l1tau_lepLeg_data) * eff_1l1tau_tauLeg_data;
    const double eff_mc   = std::min(eff_1l_mc,   eff_1l1tau_lepLeg_mc)   * eff_1l1tau_tauLeg_mc;

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

    const double eff_data = std::max(1.e-2, (eff_1l1tau_lepLeg_data - eff_1l_data) * eff_1l1tau_tauLeg_data);
    const double eff_mc   = std::max(1.e-2, (eff_1l1tau_lepLeg_mc   - eff_1l_mc)   * eff_1l1tau_tauLeg_mc);

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

    const double eff_data = std::max(1.e-2, eff_1l_data - eff_1l1tau_tauLeg_data * std::min(eff_1l_data, eff_1l1tau_lepLeg_data));
    const double eff_mc   = std::max(1.e-2, eff_1l_mc   - eff_1l1tau_tauLeg_mc   * std::min(eff_1l_mc,   eff_1l1tau_lepLeg_mc));

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

  return sf;
}
