#ifndef DATA_TO_MC_CORRECTIONS_AUXFUNCTIONS_H
#define DATA_TO_MC_CORRECTIONS_AUXFUNCTIONS_H

#include <string> // std::string
#include <cmath> // std::min(), std::max()
#include <vector> // std::vector<>
#include <map> // std::map<>

// forward declarations
class lutWrapperBase;

namespace aux
{
  std::string
  getEtaBinLabel(double etaMin,
                 double etaMax);

  std::string
  getHadTauIdxLabel(int idx);

  std::string
  getHadTauSelectionLabel(const std::string & hadTauSelection);

  std::string
  get_hadTauSelection_TauTriggerSFs2017(const std::string & hadTauSelection);

  std::string
  getHadTauDecayModeLabel(int hadTauDecayMode);

  void
  clearCollection(std::vector<lutWrapperBase *> & collection);

  void
  clearCollection(std::map<int, std::vector<lutWrapperBase *>> & collection);

  double
  get_from_lut(const std::map<int, std::vector<lutWrapperBase *>> & corrections,
               double hadTau_pt,
               double hadTau_eta,
               int hadTau_decayMode,
               bool isDEBUG);

  double constexpr
  compSF(double eff_data,
         double eff_mc)
  {
    return std::min(eff_data / std::max(1.e-6, eff_mc), 1.e+1);
  }
}

#endif // DATA_TO_MC_CORRECTIONS_AUXFUNCTIONS_H
