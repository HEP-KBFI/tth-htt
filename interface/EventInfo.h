#ifndef EventInfo_H
#define EventInfo_H

#include <Rtypes.h> // *_t

#include <iostream> // std::ostream
#include <string> // std::string
#include <map> // std::map<,>

class EventInfo
{
public:
  EventInfo();
  EventInfo(bool is_signal,
            bool is_mc,
            bool is_mc_th);
  EventInfo(const EventInfo & eventInfo);
  EventInfo &
  operator=(const EventInfo & eventInfo);

  UInt_t    run;               ///< run number
  UInt_t    lumi;              ///< luminosity
  ULong64_t event;             ///< event number
  Int_t     genHiggsDecayMode; ///< Higgs decay mode (only if MC signal)
  Float_t   genWeight;         ///< generator-level weight (only if MC)
  Float_t   genWeight_tH;      ///< reweight tH MC sample from kappa=-1 to kappa=+1 (SM) case
  Float_t   pileupWeight;      ///< pile-up weight (only if MC)

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

  std::string
  str() const;

  friend std::ostream &
  operator<<(std::ostream & os,
             const EventInfo & info);

  friend class EventInfoWriter;

private:
  bool is_signal_;
  bool is_mc_;
  bool is_mc_th_;

  static const std::map<std::string, Float_t> decayMode_idString;
};

#endif // EventInfo_H
