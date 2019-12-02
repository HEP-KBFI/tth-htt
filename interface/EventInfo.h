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
  EventInfo(bool is_mc,
            bool is_signal = false,
            bool is_hh_nonresonant = false,
            bool is_ttbar_rwgt = false);
  EventInfo(const EventInfo & eventInfo);
  EventInfo &
  operator=(const EventInfo & eventInfo);

  ~EventInfo();

  UInt_t    run;                 ///< run number
  UInt_t    lumi;                ///< luminosity
  ULong64_t event;               ///< event number
  Int_t     genHiggsDecayMode;   ///< Higgs decay mode (only if ttH signal MC)
  Float_t   genWeight;           ///< generator-level weight (only if MC)
  Float_t   pileupWeight;        ///< pile-up weight (only if MC)
  Float_t   pileupWeightUp;      ///< pile-up weight up-shifted (only if MC)
  Float_t   pileupWeightDown;    ///< pile-up weight down-shifted (only if MC)
  Float_t   PV_ndof;             ///< number of degree of freedom of the main primary vertex
  Int_t     genDiHiggsDecayMode; ///< Decay mode of both Higgs bosons (only if HH signal MC)
  Float_t   gen_mHH;             ///< LHE parton-level di-Higgs mass
  Float_t   gen_cosThetaStar;    ///< LHE parton-level cos(theta*) variable
  Float_t   topPtRwgtSF;         ///< SF correct ttbar samples in top quark pT distribution (only if MC)

  double
  genWeight_tH() const;

  double
  genWeight_tH(double kv,
               double kt,
               double cosa) const;

  double
  genWeight_tH(const std::string & central_or_shift) const;

  double
  genWeight_tH(const std::string & central_or_shift,
               const std::string & name) const;

  void
  loadWeight_tH(const std::vector<edm::ParameterSet> & cfg);

  std::vector<std::string>
  getWeight_tH_str(const std::string & central_or_shift,
                   bool include_sm = false) const;

  std::vector<std::string>
  getWeight_tH_str(bool include_sm = false) const;

  void
  set_central_or_shift(const std::string & central_or_shift);

  bool
  has_central_or_shift(const std::string & central_or_shift) const;

  bool
  is_signal() const;

  bool
  is_mc() const;

  bool
  is_hh_nonresonant() const;

  bool
  is_ttbar_rwgt() const;

  bool
  is_initialized() const;

  std::string
  getDecayModeString() const;

  std::string
  getDiHiggsDecayModeString() const;

  static std::vector<std::string>
  getDecayModes();

  static std::vector<std::string>
  getDiHiggsDecayModes();

  std::string
  str() const;

  friend std::ostream &
  operator<<(std::ostream & os,
             const EventInfo & info);

  friend class EventInfoReader;
  friend class EventInfoWriter;

protected:
  bool is_signal_;
  bool is_mc_;
  bool is_hh_nonresonant_;
  bool is_ttbar_rwgt_;
  std::string central_or_shift_;

  UInt_t nLHEReweightingWeight;
  Float_t * LHEReweightingWeight;

  const unsigned int LHEReweightingWeight_max;
  bool is_owner;

  std::map<std::string, std::map<std::string, std::pair<int, double>>> tH_sf;
  static const std::map<std::string, Int_t> decayMode_idString_singleHiggs;
  static const std::map<std::string, Int_t> decayMode_idString_diHiggs_multilepton;

  std::string
  getDecayModeString(const std::map<std::string, Int_t> & decayMode_idString) const;

  static std::vector<std::string>
  getDecayModes(const std::map<std::string, Int_t> & decayMode_idString);

  void
  copy(const EventInfo & eventInfo);
};

#endif // EventInfo_H
