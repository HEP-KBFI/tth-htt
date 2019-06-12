#include "tthAnalysis/HiggsToTauTau/interface/EventInfo.h" // EventInfo

#include "tthAnalysis/HiggsToTauTau/interface/weightAuxFunctions.h" // get_tH_weight_str()
#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h" // cmsException()

#include <boost/range/adaptor/map.hpp> // boost::adaptors::map_keys
#include <boost/range/algorithm/copy.hpp> // boost::copy()

#include <cmath> // std::fabs()
#include <cstring> // std::memcpy()
#include <cassert> // assert()

#define EPS 1E-2

const std::map<std::string, Int_t> EventInfo::decayMode_idString_singleHiggs =
{
  { "hww",     24 },
  { "hzz",     23 },
  { "htt",     15 },
  { "hzg", 220023 },
  { "hmm",     13 },
};

EventInfo::EventInfo()
  : EventInfo(false)
{}

EventInfo::EventInfo(bool is_mc,
                     bool is_signal)
  : run(0)
  , lumi(0)
  , event(0)
  , genHiggsDecayMode(-1)
  , genWeight(1.)
  , pileupWeight(1.)
  , is_signal_(is_signal)
  , is_mc_(is_mc)
  , nLHEReweightingWeight(0)
  , LHEReweightingWeight(nullptr)
  , LHEReweightingWeight_max(69)
{
  assert(is_mc_ || ! is_signal_);
}

EventInfo::EventInfo(const EventInfo & eventInfo)
  : LHEReweightingWeight_max(eventInfo.LHEReweightingWeight_max)
{
  *this = eventInfo;
}

EventInfo &
EventInfo::operator=(const EventInfo & eventInfo)
{
  run                 = eventInfo.run;
  lumi                = eventInfo.lumi;
  event               = eventInfo.event;
  genHiggsDecayMode   = eventInfo.genHiggsDecayMode;
  genWeight           = eventInfo.genWeight;

  is_signal_ = eventInfo.is_signal_;
  is_mc_     = eventInfo.is_mc_;

  nLHEReweightingWeight = eventInfo.nLHEReweightingWeight;
  if(eventInfo.LHEReweightingWeight)
  {
    if(! LHEReweightingWeight)
    {
      LHEReweightingWeight = new Float_t[LHEReweightingWeight_max];
    }
    std::memcpy(LHEReweightingWeight, eventInfo.LHEReweightingWeight, nLHEReweightingWeight);
  }

  return *this;
}

EventInfo::~EventInfo()
{
  delete[] this->LHEReweightingWeight;
}

double
EventInfo::genWeight_tH() const
{
  return genWeight_tH(get_tH_SM_str());
}

double
EventInfo::genWeight_tH(double kv,
                        double kt) const
{
  return genWeight_tH(get_tH_weight_str(kv, kt));
}

double
EventInfo::genWeight_tH(const std::string & name) const
{
  if(tH_sf.empty())
  {
    return 1.;
  }
  if(! tH_sf.count(name))
  {
    throw cmsException(this, __func__, __LINE__) << "Invalid coupling requested: " << name;
  }
  const std::pair<int, double> & settings = tH_sf.at(name);
  assert(settings.first < static_cast<int>(nLHEReweightingWeight));

  return (settings.first >= 0 ? LHEReweightingWeight[settings.first] : 1.) * settings.second;
}

void
EventInfo::loadWeight_tH(const std::vector<edm::ParameterSet> & cfg)
{
  std::map<std::string, int> main_map;
  for(const edm::ParameterSet & cfg_entry: cfg)
  {
    const double weight = cfg_entry.getParameter<double>("weight");
    const double kt = cfg_entry.getParameter<double>("kt");
    const double kv = cfg_entry.getParameter<double>("kv");
    const int idx = cfg_entry.getParameter<int>("idx");
    const std::string name = get_tH_weight_str(kt, kv);

    // make sure that we can recover the paramters encoded by the string
    const std::pair<double, double> kt_kv = get_tH_params(name);
    assert(kt_kv.first == kt);
    assert(kt_kv.second == kv);

    assert(! tH_sf.count(name));
    tH_sf[name] = std::pair<int, double>(idx, weight);
    std::cout
      << "Loaded weight '" << name << "': kt = " << kt << " & kv = " << kv
      << " -> weight = " << weight <<" @ idx = " << idx << '\n'
    ;
  }
}

std::vector<std::string>
EventInfo::getWeight_tH_str(bool include_sm) const
{
  std::vector<std::string> names;
  const std::string sm_str = get_tH_SM_str();
  for(const auto & kv: tH_sf)
  {
    if(! include_sm && kv.first == sm_str)
    {
      continue;
    }
    names.push_back(kv.first);
  }
  return names;
}

bool
EventInfo::is_signal() const
{
  return is_signal_;
}

bool
EventInfo::is_mc() const
{
  return is_mc_;
}

bool
EventInfo::is_initialized() const
{
  return run != 0 && lumi != 0 && event != 0;
}

std::string
EventInfo::getDecayModeString() const
{
  return EventInfo::getDecayModeString(decayMode_idString_singleHiggs);
}

std::string
EventInfo::getDecayModeString(const std::map<std::string, Int_t> & decayMode_idString) const
{
  if(! is_signal_)
  {
    throw cmsException(this, __func__, __LINE__)
      << "The event " << *this << " is not a signal event => request "
         "for a decay mode as a string is not applicable\n"
    ;
  }
  for(const auto & kv: decayMode_idString)
  {
    if(genHiggsDecayMode == kv.second)
    {
      return kv.first;
    }
  }
  return ""; // unrecognizable decay mode
}

std::vector<std::string>
EventInfo::getDecayModes()
{
  return getDecayModes(decayMode_idString_singleHiggs);
}

std::vector<std::string>
EventInfo::getDecayModes(const std::map<std::string, Int_t> & decayMode_idString)
{
  std::vector<std::string> decayModes;
  decayModes.reserve(decayMode_idString.size());
  boost::copy(decayMode_idString | boost::adaptors::map_keys, std::back_inserter(decayModes));
  return decayModes;
}

std::string
EventInfo::str() const
{
  std::stringstream ss;
  ss << run << ':' << lumi << ':' << event;
  return ss.str();
}

std::ostream &
operator<<(std::ostream & os,
           const EventInfo & info)
{
  os << "run = " << info.run << ", ls = " << info.lumi << ", event = " << info.event;
  return os;
}
