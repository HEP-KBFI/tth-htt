#ifndef EventInfo_H
#define EventInfo_H

#include "tthAnalysis/HiggsToTauTau/interface/KeyTypes.h" // *_TYPE, *_KEY

#include <iostream> // std::ostream
#include <string> // std::string
#include <map> // std::map<,>

class EventInfo
{
public:
  EventInfo();
  EventInfo(bool is_signal,
            bool is_mc,
            bool is_mc_th = false);
  EventInfo(const EventInfo & eventInfo);
  EventInfo &
  operator=(const EventInfo & eventInfo);

  RUN_TYPE               run;               ///< run number
  LUMI_TYPE              lumi;              ///< luminosity
  EVT_TYPE               event;             ///< event number
  GENHIGGSDECAYMODE_TYPE genHiggsDecayMode; ///< Higgs decay mode (only if MC signal)
  GENWEIGHT_TYPE         genWeight;         ///< generator-level weight (only if MC)
  GENWEIGHTTH_TYPE       genWeight_tH;      ///< reweight tH MC sample from kappa=-1 to kappa=+1 (SM) case
  PUWEIGHT_TYPE          pileupWeight;      ///< pile-up weight (only if MC)

  bool
  is_signal() const;

  bool
  is_mc() const;

  bool
  is_mc_th() const;

  bool
  is_initialized() const;

  std::string
  getDecayModeString() const;

  static std::vector<std::string>
  getDecayModes();

  friend std::ostream &
  operator<<(std::ostream & os,
             const EventInfo & info);

  friend class EventInfoWriter;

private:
  bool is_signal_;
  bool is_mc_;
  bool is_mc_th_;

  static const std::map<std::string, GENHIGGSDECAYMODE_TYPE> decayMode_idString;
};

#endif // EventInfo_H
