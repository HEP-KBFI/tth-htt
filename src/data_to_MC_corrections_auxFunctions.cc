#include "tthAnalysis/HiggsToTauTau/interface/data_to_MC_corrections_auxFunctions.h"

#include "tthAnalysis/HiggsToTauTau/interface/lutAuxFunctions.h" // lutWrapperBase, vLutWrapperBase
#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h" // cmsException()
#include "tthAnalysis/HiggsToTauTau/interface/sysUncertOptions.h" // TriggerSFsys

#include "TauAnalysisTools/TauTriggerSFs/interface/TauTriggerSFs2017.h" // TauTriggerSFs2017

#include <boost/algorithm/string/replace.hpp> // boost::replace_all_copy()
#include <boost/algorithm/string/predicate.hpp> // boost::ends_with()

#include <cassert> // assert()

namespace aux
{
  std::string
  getEtaBinLabel(double etaMin,
                 double etaMax,
                 bool replace_period)
  {
    std::string etaBinLabel_tstring;
    if(etaMin != -1. && etaMax != -1.)
    {
      std::string etaBinLabel_partMin = Form("%1.4g", etaMin);
      std::string etaBinLabel_partMax = Form("%1.4g", etaMax);
      if(replace_period)
      {
        if(etaBinLabel_partMin.find('.') == std::string::npos)
        {
          etaBinLabel_partMin += ".0";
        }
        if(etaBinLabel_partMax.find('.') == std::string::npos)
        {
          etaBinLabel_partMax += ".0";
        }
      }
      etaBinLabel_tstring = Form("%sto%s", etaBinLabel_partMin.data(), etaBinLabel_partMax.data());
    }
    else if(etaMin != -1.)
    {
      etaBinLabel_tstring = Form("Gt%1.4g", etaMin);
    }
    else if(etaMax != -1.)
    {
      etaBinLabel_tstring = Form("Lt%1.4g", etaMax);
    }
    else
    {
      assert(0);
    }
    if(replace_period)
    {
      if(etaBinLabel_tstring.find('.') != std::string::npos)
      {
        std::replace(etaBinLabel_tstring.begin(), etaBinLabel_tstring.end(), '.', 'p');
      }
      else
      {
        assert(etaMin == -1. || etaMax == -1.);
        etaBinLabel_tstring += "p0";
      }
    }
    const std::string etaBinLabel = boost::replace_all_copy(etaBinLabel_tstring, ".", "p");
    return etaBinLabel;
  }

  std::string
  getHadTauIdxLabel(int idx)
  {
    std::string hadTauIdxLabel;
    switch(idx)
    {
      case 0:  hadTauIdxLabel = "_lead";    break;
      case 1:  hadTauIdxLabel = "_sublead"; break;
      case 2:  hadTauIdxLabel = "_third";   break;
      case 3:  hadTauIdxLabel = "_fourth";  break;	
      default: assert(0);
    }
    return hadTauIdxLabel;
  }

  std::string
  getHadTauSelectionLabel(const std::string & hadTauSelection)
  {
    std::string hadTauSelection_param;
    if     (boost::ends_with(hadTauSelection, "VVLoose")) hadTauSelection_param = "vloose"; // not measured for VVLoose in 2017
    else if(boost::ends_with(hadTauSelection, "VLoose" )) hadTauSelection_param = "vloose";
    else if(boost::ends_with(hadTauSelection, "Loose"  )) hadTauSelection_param = "loose";
    else if(boost::ends_with(hadTauSelection, "Medium" )) hadTauSelection_param = "medium";
    else if(boost::ends_with(hadTauSelection, "VVTight")) hadTauSelection_param = "vvtight";
    else if(boost::ends_with(hadTauSelection, "VTight" )) hadTauSelection_param = "vtight";
    else if(boost::ends_with(hadTauSelection, "Tight"  )) hadTauSelection_param = "tight";
    else throw cmsException(__func__, __LINE__)
           << "Invalid Configuration parameter 'hadTauSelection' = " << hadTauSelection
         ;
    return hadTauSelection_param;
  }

  std::string
  getHadTauDecayModeLabel(int hadTauDecayMode)
  {
    std::string hadTauDecayModeLabel;
    if     (hadTauDecayMode ==  0                        ) hadTauDecayModeLabel = "dm0";  // 1-prong without pi0s
    else if(hadTauDecayMode ==  1 || hadTauDecayMode == 2) hadTauDecayModeLabel = "dm1";  // 1-prong with pi0s
    else if(hadTauDecayMode == 10                        ) hadTauDecayModeLabel = "dm10"; // 3-prong
    else throw cmsException(__func__, __LINE__)
           << "Invalid Configuration parameter 'hadTauDecayMode' = " << hadTauDecayMode;
    return hadTauDecayModeLabel;
  }

  void
  clearCollection(std::vector<lutWrapperBase *> & collection)
  {
    for(lutWrapperBase * it: collection)
    {
      delete it;
    }
    collection.clear();
  }

  void
  clearCollection(std::map<int, std::vector<lutWrapperBase *>> & collection)
  {
    for(auto & kv: collection)
    {
      for(lutWrapperBase * it: kv.second)
      {
        delete it;
      }
      kv.second.clear();
    }
  }

  double
  get_from_lut(const std::map<int, std::vector<lutWrapperBase *>> & corrections,
               double hadTau_pt,
               double hadTau_eta,
               int hadTau_decayMode,
               bool isDEBUG)
  {
    if(! corrections.count(hadTau_decayMode))
    {
      throw cmsException(__func__, __LINE__)
              << "Invalid parameter 'hadTauDecayMode' = " << hadTau_decayMode;
    }
    const double sf = get_from_lut(corrections.at(hadTau_decayMode), hadTau_pt, hadTau_eta, isDEBUG);
    return sf;
  }

  double
  compSF(double eff_data,
         double eff_mc)
  {
    if(eff_data == 0. && eff_mc == 0.)
    {
      std::cout << "WARNING: efficiency in data and in MC are both zero -> returning SF = 1 instead";
      return 1.;
    }
    return std::min(eff_data / std::max(1.e-6, eff_mc), 1.e+1);
  }

  bool
  hasDecayMode(const std::vector<int> & allowedDecayModes,
               int hadTau_decayMode)
  {
    return std::find(allowedDecayModes.cbegin(), allowedDecayModes.cend(), hadTau_decayMode) != allowedDecayModes.cend();
  }

  void
  loadTriggerEff_1e_2016(vLutWrapperBase & effTrigger_1e_data,
                         vLutWrapperBase & effTrigger_1e_mc,
                         std::map<std::string, TFile *> & inputFiles)
  {
    const std::vector<double> etaBinEdges_1e = { -1., 1.48, 2.1 };
    assert(etaBinEdges_1e.size() > 0);
    const std::size_t numEtaBins_1e = etaBinEdges_1e.size() - 1;
    for(std::size_t idxEtaBin = 0; idxEtaBin < numEtaBins_1e; ++idxEtaBin)
    {
      const double etaMin = etaBinEdges_1e[idxEtaBin];
      const double etaMax = etaBinEdges_1e[idxEtaBin + 1];
      const std::string etaBinLabel = aux::getEtaBinLabel(etaMin, etaMax);
      effTrigger_1e_data.push_back(new lutWrapperTGraph(
        inputFiles,
        "tthAnalysis/HiggsToTauTau/data/triggerSF/2016/Electron_Ele25WPTight_eff.root",
        Form("ZMassEta%s_Data", etaBinLabel.data()),
        lut::kXptYabsEta,
        -1., -1., lut::kLimit, etaMin, etaMax, lut::kCut
      ));
      effTrigger_1e_mc.push_back(new lutWrapperTGraph(
        inputFiles,
        "tthAnalysis/HiggsToTauTau/data/triggerSF/2016/Electron_Ele25WPTight_eff.root",
        Form("ZMassEta%s_MC", etaBinLabel.data()),
        lut::kXptYabsEta,
        -1., -1., lut::kLimit, etaMin, etaMax, lut::kCut
      ));
    }
  }

  void
  loadTriggerEff_1e_1tau_lepLeg_2016(vLutWrapperBase & effTrigger_1e1tau_lepLeg_data,
                                     vLutWrapperBase & effTrigger_1e1tau_lepLeg_mc,
                                     std::map<std::string, TFile *> & inputFiles)
  {
    const std::vector<double> etaBinEdges_1e_1tau_lepLeg = { -1., 1.48, 2.1 };
    assert(etaBinEdges_1e_1tau_lepLeg.size() > 0);
    const std::size_t numEtaBins_1e_1tau_lepLeg = etaBinEdges_1e_1tau_lepLeg.size() - 1;
    for(std::size_t idxEtaBin = 0; idxEtaBin < numEtaBins_1e_1tau_lepLeg; ++idxEtaBin)
    {
      const double etaMin = etaBinEdges_1e_1tau_lepLeg[idxEtaBin];
      const double etaMax = etaBinEdges_1e_1tau_lepLeg[idxEtaBin + 1];
      const std::string etaBinLabel = aux::getEtaBinLabel(etaMin, etaMax);
      effTrigger_1e1tau_lepLeg_data.push_back(new lutWrapperTGraph(
        inputFiles,
        "tthAnalysis/HiggsToTauTau/data/triggerSF/2016/Electron_Ele24_eff.root",
        Form("ZMassEta%s_Data", etaBinLabel.data()),
        lut::kXptYabsEta,
        -1., -1., lut::kLimit, etaMin, etaMax, lut::kCut
      ));
      effTrigger_1e1tau_lepLeg_mc.push_back(new lutWrapperTGraph(
        inputFiles,
        "tthAnalysis/HiggsToTauTau/data/triggerSF/2016/Electron_Ele24_eff.root",
        Form("ZMassEta%s_MC", etaBinLabel.data()),
        lut::kXptYabsEta,
        -1., -1., lut::kLimit, etaMin, etaMax, lut::kCut
      ));
    }
  }

  void
  loadTriggerEff_1m_2016(vLutWrapperBase & effTrigger_1m_data,
                         vLutWrapperBase & effTrigger_1m_mc,
                         std::map<std::string, TFile *> & inputFiles)
  {
    const std::vector<double> etaBinEdges_1m = { -1., 0.9, 1.2, 2.1 };
    assert(etaBinEdges_1m.size() > 0);
    const std::size_t numEtaBins_1m = etaBinEdges_1m.size() - 1;
    for(std::size_t idxEtaBin = 0; idxEtaBin < numEtaBins_1m; ++idxEtaBin)
    {
      const double etaMin = etaBinEdges_1m[idxEtaBin];
      const double etaMax = etaBinEdges_1m[idxEtaBin + 1];
      const std::string etaBinLabel = aux::getEtaBinLabel(etaMin, etaMax);
      effTrigger_1m_data.push_back(new lutWrapperTGraph(
        inputFiles,
        "tthAnalysis/HiggsToTauTau/data/triggerSF/2016/Muon_Mu22OR_eta2p1_eff.root", Form("ZMassEta%s_Data", etaBinLabel.data()),
        lut::kXptYabsEta,
        -1., -1., lut::kLimit, etaMin, etaMax, lut::kCut
      ));
      effTrigger_1m_mc.push_back(new lutWrapperTGraph(
        inputFiles,
        "tthAnalysis/HiggsToTauTau/data/triggerSF/2016/Muon_Mu22OR_eta2p1_eff.root",
        Form("ZMassEta%s_MC", etaBinLabel.data()),
        lut::kXptYabsEta,
        -1., -1., lut::kLimit, etaMin, etaMax, lut::kCut
      ));
    }
  }

  void
  loadTriggerEff_1m_1tau_lepLeg_2016(vLutWrapperBase & effTrigger_1m1tau_lepLeg_data,
                                     vLutWrapperBase & effTrigger_1m1tau_lepLeg_mc,
                                     std::map<std::string, TFile *> & inputFiles)
  {
    const std::vector<double> etaBinEdges_1m1tau_lepLeg = { -1., 0.9, 1.2, 2.1 };
    assert(etaBinEdges_1m1tau_lepLeg.size() > 0);
    const std::size_t numEtaBins_1m1tau_lepLeg = etaBinEdges_1m1tau_lepLeg.size() - 1;
    for(std::size_t idxEtaBin = 0; idxEtaBin < numEtaBins_1m1tau_lepLeg; ++idxEtaBin)
    {
      const double etaMin = etaBinEdges_1m1tau_lepLeg[idxEtaBin];
      const double etaMax = etaBinEdges_1m1tau_lepLeg[idxEtaBin + 1];
      const std::string etaBinLabel = aux::getEtaBinLabel(etaMin, etaMax);
      effTrigger_1m1tau_lepLeg_data.push_back(new lutWrapperTGraph(
        inputFiles,
        "tthAnalysis/HiggsToTauTau/data/triggerSF/2016/Muon_Mu19leg_2016BtoH_eff.root",
        Form("ZMassEta%s_Data", etaBinLabel.data()),
        lut::kXptYabsEta,
        -1., -1., lut::kLimit, etaMin, etaMax, lut::kCut
      ));
      effTrigger_1m1tau_lepLeg_mc.push_back(new lutWrapperTGraph(
        inputFiles,
        "tthAnalysis/HiggsToTauTau/data/triggerSF/2016/Muon_Mu19leg_2016BtoH_eff.root",
        Form("ZMassEta%s_MC", etaBinLabel.data()),
        lut::kXptYabsEta, -1., -1., lut::kLimit, etaMin, etaMax, lut::kCut
      ));
    }
  }

  void 
  loadTriggerEff_1e_2017(vLutWrapperBase & effTrigger_1e_data,
                         vLutWrapperBase & effTrigger_1e_mc,
                         std::map<std::string, TFile *> & inputFiles)
  {
    const std::vector<double> etaBinEdges_1e = { -1., 1.48, 2.1 };
    assert(etaBinEdges_1e.size() > 0);
    const std::size_t numEtaBins_1e = etaBinEdges_1e.size() - 1;

    for(std::size_t idxEtaBin = 0; idxEtaBin < numEtaBins_1e; ++idxEtaBin)
    {
      const double etaMin = etaBinEdges_1e[idxEtaBin];
      const double etaMax = etaBinEdges_1e[idxEtaBin + 1];
      const std::string etaBinLabel = aux::getEtaBinLabel(etaMin, etaMax);

      effTrigger_1e_data.push_back(new lutWrapperTGraph(
        inputFiles,
        "tthAnalysis/HiggsToTauTau/data/triggerSF/2017/Electron_Ele32orEle35_eff.root",
        Form("ZMassEta%s_Data", etaBinLabel.data()),
        lut::kXptYabsEta, -1., -1., lut::kLimit, etaMin, etaMax, lut::kCut
      ));
      effTrigger_1e_mc.push_back(new lutWrapperTGraph(
        inputFiles,
        "tthAnalysis/HiggsToTauTau/data/triggerSF/2017/Electron_Ele32orEle35_eff.root",
        Form("ZMassEta%s_MC", etaBinLabel.data()),
        lut::kXptYabsEta, -1., -1., lut::kLimit, etaMin, etaMax, lut::kCut
      ));
    }
  }

  void
  loadTriggerEff_1e_1tau_lepLeg_2017(vLutWrapperBase & effTrigger_1e1tau_lepLeg_data,
                                     vLutWrapperBase & effTrigger_1e1tau_lepLeg_mc,
                                     std::map<std::string, TFile *> & inputFiles)
  {
    const std::vector<double> etaBinEdges_1e_1tau_lepLeg = { -1., 1.48, 2.1 };
    assert(etaBinEdges_1e_1tau_lepLeg.size() > 0);
    const std::size_t numEtaBins_1e_1tau_lepLeg = etaBinEdges_1e_1tau_lepLeg.size() - 1;

    for(std::size_t idxEtaBin = 0; idxEtaBin < numEtaBins_1e_1tau_lepLeg; ++idxEtaBin)
    {
      const double etaMin = etaBinEdges_1e_1tau_lepLeg[idxEtaBin];
      const double etaMax = etaBinEdges_1e_1tau_lepLeg[idxEtaBin + 1];
      const std::string etaBinLabel = aux::getEtaBinLabel(etaMin, etaMax);

      effTrigger_1e1tau_lepLeg_data.push_back(new lutWrapperTGraph(
        inputFiles,
        "tthAnalysis/HiggsToTauTau/data/triggerSF/2017/Electron_EleTau_Ele24_eff.root",
        Form("ZMassEta%s_Data", etaBinLabel.data()),
        lut::kXptYabsEta, -1., -1., lut::kLimit, etaMin, etaMax, lut::kCut
      ));
      effTrigger_1e1tau_lepLeg_mc.push_back(new lutWrapperTGraph(
        inputFiles,
        "tthAnalysis/HiggsToTauTau/data/triggerSF/2017/Electron_EleTau_Ele24_eff.root",
        Form("ZMassEta%s_MC", etaBinLabel.data()),
        lut::kXptYabsEta, -1., -1., lut::kLimit, etaMin, etaMax, lut::kCut
      ));
    }
  }

  void 
  loadTriggerEff_1m_2017(vLutWrapperBase & effTrigger_1m_data,
                         vLutWrapperBase & effTrigger_1m_mc,
                         std::map<std::string, TFile *> & inputFiles)
  {
    const std::vector<double> etaBinEdges_1m = { -1., 0.9, 1.2, 2.1 };
    assert(etaBinEdges_1m.size() > 0);
    const std::size_t numEtaBins_1m = etaBinEdges_1m.size() - 1;

    for(std::size_t idxEtaBin = 0; idxEtaBin < numEtaBins_1m; ++idxEtaBin)
    {
      const double etaMin = etaBinEdges_1m[idxEtaBin];
      const double etaMax = etaBinEdges_1m[idxEtaBin + 1];
      const std::string etaBinLabel = aux::getEtaBinLabel(etaMin, etaMax);

      effTrigger_1m_data.push_back(new lutWrapperTGraph(
        inputFiles,
        "tthAnalysis/HiggsToTauTau/data/triggerSF/2017/Muon_IsoMu24orIsoMu27_eff.root",
        Form("ZMassEta%s_Data", etaBinLabel.data()),
        lut::kXptYabsEta, -1., -1., lut::kLimit, etaMin, etaMax, lut::kCut
      ));
      effTrigger_1m_mc.push_back(new lutWrapperTGraph(
        inputFiles,
        "tthAnalysis/HiggsToTauTau/data/triggerSF/2017/Muon_IsoMu24orIsoMu27_eff.root",
        Form("ZMassEta%s_MC", etaBinLabel.data()),
        lut::kXptYabsEta, -1., -1., lut::kLimit, etaMin, etaMax, lut::kCut
      ));
    }
  }
 
  void
  loadTriggerEff_1m_1tau_lepLeg_2017(vLutWrapperBase & effTrigger_1m1tau_lepLeg_data,
                                     vLutWrapperBase & effTrigger_1m1tau_lepLeg_mc,
                                     std::map<std::string, TFile *> & inputFiles)
  {
    const std::vector<double> etaBinEdges_1m1tau_lepLeg = { -1., 0.9, 1.2, 2.1 };
    assert(etaBinEdges_1m1tau_lepLeg.size() > 0);
    const std::size_t numEtaBins_1m1tau_lepLeg = etaBinEdges_1m1tau_lepLeg.size() - 1;

    for(std::size_t idxEtaBin = 0; idxEtaBin < numEtaBins_1m1tau_lepLeg; ++idxEtaBin)
    {
      const double etaMin = etaBinEdges_1m1tau_lepLeg[idxEtaBin];
      const double etaMax = etaBinEdges_1m1tau_lepLeg[idxEtaBin + 1];
      const std::string etaBinLabel = aux::getEtaBinLabel(etaMin, etaMax);

      effTrigger_1m1tau_lepLeg_data.push_back(new lutWrapperTGraph(
        inputFiles,
        "tthAnalysis/HiggsToTauTau/data/triggerSF/2017/Muon_MuTau_IsoMu20_eff.root",
        Form("ZMassEta%s_Data", etaBinLabel.data()),
        lut::kXptYabsEta, -1., -1., lut::kLimit, etaMin, etaMax, lut::kCut
      ));
      effTrigger_1m1tau_lepLeg_mc.push_back(new lutWrapperTGraph(
        inputFiles,
        "tthAnalysis/HiggsToTauTau/data/triggerSF/2017/Muon_MuTau_IsoMu20_eff.root",
        Form("ZMassEta%s_MC", etaBinLabel.data()),
        lut::kXptYabsEta, -1., -1., lut::kLimit, etaMin, etaMax, lut::kCut
      ));
    }
  }

  void 
  loadTriggerEff_1e_2018(vLutWrapperBase & effTrigger_1e_data,
                         vLutWrapperBase & effTrigger_1e_mc,
                         std::map<std::string, TFile *> & inputFiles)
  {
    const std::vector<double> etaBinEdges_1e = { -1., 1.0, 1.48, 1.65, 2.1 };
    assert(etaBinEdges_1e.size() > 0);
    const std::size_t numEtaBins_1e = etaBinEdges_1e.size() - 1;

    for(std::size_t idxEtaBin = 0; idxEtaBin < numEtaBins_1e; ++idxEtaBin)
    {
      const double etaMin = etaBinEdges_1e[idxEtaBin];
      const double etaMax = etaBinEdges_1e[idxEtaBin + 1];
      const std::string etaBinLabel = aux::getEtaBinLabel(etaMin, etaMax, true);

      effTrigger_1e_data.push_back(new lutWrapperTGraph(
        inputFiles,
        "tthAnalysis/HiggsToTauTau/data/triggerSF/2018/Electron_Run2018_Ele32orEle35.root",
        Form("ZMassEta%s_Data", etaBinLabel.data()),
        lut::kXptYabsEta, -1., -1., lut::kLimit, etaMin, etaMax, lut::kCut
      ));
      effTrigger_1e_mc.push_back(new lutWrapperTGraph(
        inputFiles,
        "tthAnalysis/HiggsToTauTau/data/triggerSF/2018/Electron_Run2018_Ele32orEle35.root",
        Form("ZMassEta%s_MC", etaBinLabel.data()),
        lut::kXptYabsEta, -1., -1., lut::kLimit, etaMin, etaMax, lut::kCut
      ));
    }
  }

  void
  loadTriggerEff_1e_1tau_lepLeg_2018(vLutWrapperBase & effTrigger_1e1tau_lepLeg_data,
                                     vLutWrapperBase & effTrigger_1e1tau_lepLeg_mc,
                                     std::map<std::string, TFile *> & inputFiles)
  {
    const std::vector<double> etaBinEdges_1e_1tau_lepLeg = { -1., 1.0, 1.48, 1.65, 2.1 };
    assert(etaBinEdges_1e_1tau_lepLeg.size() > 0);
    const std::size_t numEtaBins_1e_1tau_lepLeg = etaBinEdges_1e_1tau_lepLeg.size() - 1;

    for(std::size_t idxEtaBin = 0; idxEtaBin < numEtaBins_1e_1tau_lepLeg; ++idxEtaBin)
    {
      const double etaMin = etaBinEdges_1e_1tau_lepLeg[idxEtaBin];
      const double etaMax = etaBinEdges_1e_1tau_lepLeg[idxEtaBin + 1];
      const std::string etaBinLabel = aux::getEtaBinLabel(etaMin, etaMax, true);

      effTrigger_1e1tau_lepLeg_data.push_back(new lutWrapperTGraph(
        inputFiles,
        "tthAnalysis/HiggsToTauTau/data/triggerSF/2018/Electron_Run2018_Ele24.root",
        Form("ZMassEta%s_Data", etaBinLabel.data()),
        lut::kXptYabsEta, -1., -1., lut::kLimit, etaMin, etaMax, lut::kCut
      ));
      effTrigger_1e1tau_lepLeg_mc.push_back(new lutWrapperTGraph(
        inputFiles,
        "tthAnalysis/HiggsToTauTau/data/triggerSF/2018/Electron_Run2018_Ele24.root",
        Form("ZMassEta%s_MC", etaBinLabel.data()),
        lut::kXptYabsEta, -1., -1., lut::kLimit, etaMin, etaMax, lut::kCut
      ));
    }
  }

  void 
  loadTriggerEff_1m_2018(vLutWrapperBase & effTrigger_1m_data,
                         vLutWrapperBase & effTrigger_1m_mc,
                         std::map<std::string, TFile *> & inputFiles)
  {
    const std::vector<double> etaBinEdges_1m = { -1., 0.9, 1.2, 2.1 };
    assert(etaBinEdges_1m.size() > 0);
    const std::size_t numEtaBins_1m = etaBinEdges_1m.size() - 1;

    for(std::size_t idxEtaBin = 0; idxEtaBin < numEtaBins_1m; ++idxEtaBin)
    {
      const double etaMin = etaBinEdges_1m[idxEtaBin];
      const double etaMax = etaBinEdges_1m[idxEtaBin + 1];
      const std::string etaBinLabel = aux::getEtaBinLabel(etaMin, etaMax);

      effTrigger_1m_data.push_back(new lutWrapperTGraph(
        inputFiles,
        "tthAnalysis/HiggsToTauTau/data/triggerSF/2018/Muon_Run2018_IsoMu24orIsoMu27.root",
        Form("ZMassEta%s_Data", etaBinLabel.data()),
        lut::kXptYabsEta, -1., -1., lut::kLimit, etaMin, etaMax, lut::kCut
      ));
      effTrigger_1m_mc.push_back(new lutWrapperTGraph(
        inputFiles,
        "tthAnalysis/HiggsToTauTau/data/triggerSF/2018/Muon_Run2018_IsoMu24orIsoMu27.root",
        Form("ZMassEta%s_MC", etaBinLabel.data()),
        lut::kXptYabsEta, -1., -1., lut::kLimit, etaMin, etaMax, lut::kCut
      ));
    }
  }

  void
  loadTriggerEff_1m_1tau_lepLeg_2018(vLutWrapperBase & effTrigger_1m1tau_lepLeg_data,
                                     vLutWrapperBase & effTrigger_1m1tau_lepLeg_mc,
                                     std::map<std::string, TFile *> & inputFiles)
  {
    const std::vector<double> etaBinEdges_1m1tau_lepLeg = { -1., 0.9, 1.2, 2.1 };
    assert(etaBinEdges_1m1tau_lepLeg.size() > 0);
    const std::size_t numEtaBins_1m1tau_lepLeg = etaBinEdges_1m1tau_lepLeg.size() - 1;

    for(std::size_t idxEtaBin = 0; idxEtaBin < numEtaBins_1m1tau_lepLeg; ++idxEtaBin)
    {
      const double etaMin = etaBinEdges_1m1tau_lepLeg[idxEtaBin];
      const double etaMax = etaBinEdges_1m1tau_lepLeg[idxEtaBin + 1];
      const std::string etaBinLabel = aux::getEtaBinLabel(etaMin, etaMax);

      effTrigger_1m1tau_lepLeg_data.push_back(new lutWrapperTGraph(
        inputFiles,
        "tthAnalysis/HiggsToTauTau/data/triggerSF/2018/Muon_Run2018_IsoMu20.root",
        Form("ZMassEta%s_Data", etaBinLabel.data()),
        lut::kXptYabsEta, -1., -1., lut::kLimit, etaMin, etaMax, lut::kCut
      ));
      effTrigger_1m1tau_lepLeg_mc.push_back(new lutWrapperTGraph(
        inputFiles,
        "tthAnalysis/HiggsToTauTau/data/triggerSF/2018/Muon_Run2018_IsoMu20.root",
        Form("ZMassEta%s_MC", etaBinLabel.data()),
        lut::kXptYabsEta, -1., -1., lut::kLimit, etaMin, etaMax, lut::kCut
      ));
    }
  }

  getTriggerEfficiencyFunc
  getTriggerFuncMC(TriggerSFsys triggerSF_option,
                   bool flip)
  {
    switch(triggerSF_option)
    {
      case TriggerSFsys::central:   return        &TauTriggerSFs2017::getTriggerEfficiencyMC;
      case TriggerSFsys::shiftUp:   return flip ? &TauTriggerSFs2017::getTriggerEfficiencyMCUncertDown :
                                                  &TauTriggerSFs2017::getTriggerEfficiencyMCUncertUp;
      case TriggerSFsys::shiftDown: return flip ? &TauTriggerSFs2017::getTriggerEfficiencyMCUncertUp :
                                                  &TauTriggerSFs2017::getTriggerEfficiencyMCUncertDown;
    }
    return nullptr;
  }

  getTriggerEfficiencyFunc
  getTriggerFuncData(TriggerSFsys triggerSF_option)
  {
    switch(triggerSF_option)
    {
      case TriggerSFsys::central:   return &TauTriggerSFs2017::getTriggerEfficiencyData;           break;
      case TriggerSFsys::shiftUp:   return &TauTriggerSFs2017::getTriggerEfficiencyDataUncertUp;   break;
      case TriggerSFsys::shiftDown: return &TauTriggerSFs2017::getTriggerEfficiencyDataUncertDown; break;
    }
    return nullptr;
  }
}
