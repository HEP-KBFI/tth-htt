#ifndef EventInfo_H
#define EventInfo_H

#include "FWCore/ParameterSet/interface/ParameterSet.h" // edm::ParameterSet

#include <Rtypes.h> // *_t

#include <iostream> // std::ostream
#include <string> // std::string
#include <map> // std::map<,>

class EventInfo
{
public:
  EventInfo();
  EventInfo(bool is_signal,
            bool is_mc);
  EventInfo(const EventInfo & eventInfo);
  EventInfo &
  operator=(const EventInfo & eventInfo);

  ~EventInfo();

  UInt_t    run;                 ///< run number
  UInt_t    lumi;                ///< luminosity
  ULong64_t event;               ///< event number
  Int_t     genHiggsDecayMode;   ///< Higgs decay mode (only if ttH signal MC)
  Int_t     genDiHiggsDecayMode; ///< Decay mode of both Higgs bosons (only if HH signal MC)
  Float_t   genWeight;           ///< generator-level weight (only if MC)
  Float_t   pileupWeight;        ///< pile-up weight (only if MC)

  double
  genWeight_tH() const;

  double
  genWeight_tH(double kv,
               double kt) const;

  double
  genWeight_tH(const std::string & name) const;

  void
  loadWeight_tH(const std::vector<edm::ParameterSet> & cfg_main,
                const std::vector<edm::ParameterSet> & cfg_choice);

  std::vector<std::string>
  getWeight_tH_str() const;

  bool
  is_signal() const;

  bool
  is_mc() const;

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

  friend class EventInfoReader;
  friend class EventInfoWriter;

private:
  bool is_signal_;
  bool is_mc_;

  UInt_t nLHEReweightingWeight;
  Float_t * LHEReweightingWeight;
  const unsigned int LHEReweightingWeight_max;

  std::map<std::string, std::pair<int, double>> tH_sf;
  static const std::map<std::string, Float_t> decayMode_idString;
};

#endif // EventInfo_H
