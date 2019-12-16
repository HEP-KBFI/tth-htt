#ifndef tthAnalysis_HiggsToTauTau_TauTriggerSFInterface_h
#define tthAnalysis_HiggsToTauTau_TauTriggerSFInterface_h

#include <string> // std::string
#include <functional> // std::function<>

// forward declarations
class TauTriggerSFs2017; // for MVAv2 tau ID
namespace tau_trigger {
  class SFProvider; // for DeepTau ID
}
enum class TriggerSFsys;

enum class TauTriggerType
{
  DiTau, ETau, MuTau
};

class TauTriggerSFInterface
{
public:
  TauTriggerSFInterface();
  TauTriggerSFInterface(const std::string & era_str,
                        const std::string & hadTauSelection,
                        TauTriggerType triggerType);

  double
  getTauTriggerEvalData(TriggerSFsys central_or_shift,
                        double pt,
                        double eta,
                        double phi,
                        int dm) const;

  double
  getTauTriggerEvalMC(TriggerSFsys central_or_shift,
                      double pt,
                      double eta,
                      double phi,
                      int dm,
                      bool flip = true) const;

protected:
  static std::string
  tauTriggerType_toStr(TauTriggerType triggerType);

  TauTriggerSFs2017 * eff_mvav2_;
  tau_trigger::SFProvider * eff_deep_;
};

#endif
