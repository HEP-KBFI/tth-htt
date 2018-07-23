#include "tthAnalysis/HiggsToTauTau/interface/data_to_MC_corrections_auxFunctions.h"

#include "tthAnalysis/HiggsToTauTau/interface/lutAuxFunctions.h" // lutWrapperBase, vLutWrapperBase
#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h" // cmsException()

#include <TString.h> // Form()

#include <boost/algorithm/string/replace.hpp> // boost::replace_all_copy()

#include <cassert> // assert()

namespace aux
{
  std::string
  getEtaBinLabel(double etaMin,
                 double etaMax)
  {
    std::string etaBinLabel_tstring;
    if(etaMin != -1. && etaMax != -1.)
    {
      etaBinLabel_tstring = Form("%1.4gto%1.4g", etaMin, etaMax);
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
    std::string hadTauSelectionLabel;
    if     (hadTauSelection == "dR03mvaVVLoose") hadTauSelectionLabel = "VLooseIso"; // CV: custom WP for which no trigger efficiency turn-on curve has been measured
    else if(hadTauSelection == "dR03mvaVLoose" ) hadTauSelectionLabel = "VLooseIso";
    else if(hadTauSelection == "dR03mvaLoose"  ) hadTauSelectionLabel = "LooseIso";
    else if(hadTauSelection == "dR03mvaMedium" ) hadTauSelectionLabel = "MediumIso";
    else if(hadTauSelection == "dR03mvaTight"  ) hadTauSelectionLabel = "TightIso";
    else if(hadTauSelection == "dR03mvaVTight" ) hadTauSelectionLabel = "VTightIso";
    else if(hadTauSelection == "dR03mvaVVTight") hadTauSelectionLabel = "VVTightIso";
    else throw cmsException(__func__, __LINE__)
           << "Invalid Configuration parameter 'hadTauSelection' = " << hadTauSelection;
    return hadTauSelectionLabel;
  }

  std::string
  get_hadTauSelection_TauTriggerSFs2017(const std::string & hadTauSelection)
  {
    std::string hadTauSelection_TauTriggerSFs2017;
    if     (hadTauSelection == "dR03mvaVVLoose") hadTauSelection_TauTriggerSFs2017 = "medium"; // CV: trigger efficiency turn-on curve has not been measured for this working-point
    else if(hadTauSelection == "dR03mvaVLoose" ) hadTauSelection_TauTriggerSFs2017 = "medium"; // CV: trigger efficiency turn-on curve has not been measured for this working-point
    else if(hadTauSelection == "dR03mvaLoose"  ) hadTauSelection_TauTriggerSFs2017 = "medium"; // CV: trigger efficiency turn-on curve has not been measured for this working-point
    else if(hadTauSelection == "dR03mvaMedium" ) hadTauSelection_TauTriggerSFs2017 = "medium";
    else if(hadTauSelection == "dR03mvaTight"  ) hadTauSelection_TauTriggerSFs2017 = "tight";
    else if(hadTauSelection == "dR03mvaVTight" ) hadTauSelection_TauTriggerSFs2017 = "vtight";
    else if(hadTauSelection == "dR03mvaVVTight") hadTauSelection_TauTriggerSFs2017 = "vtight"; // CV: trigger efficiency turn-on curve has not been measured for this working-point
    else throw cmsException(__func__, __LINE__)
           << "Invalid Configuration parameter 'hadTauSelection' = " << hadTauSelection
         ;
    return hadTauSelection_TauTriggerSFs2017;
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
}
