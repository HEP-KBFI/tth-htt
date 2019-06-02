#include "tthAnalysis/HiggsToTauTau/interface/EventInfo.h" // EventInfo

#include "tthAnalysis/HiggsToTauTau/interface/weightAuxFunctions.h" // get_tH_weight_str()
#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h" // cmsException()

#include <boost/range/algorithm/copy.hpp> // boost::copy()
#include <boost/range/adaptor/map.hpp> // boost::adaptors::map_keys

#include <boost/range/adaptor/map.hpp> // boost::adaptors::map_keys
#include <boost/range/algorithm/copy.hpp> // boost::copy()

#include <cmath> // std::fabs()
#include <cstring> // std::memcpy()
#include <cassert> // assert()

#define EPS 1E-2

const std::map<std::string, Float_t> EventInfo::decayMode_idString =
{
  { "hww",     24 },
  { "hzz",     23 },
  { "htt",     15 },
  { "hzg", 230022 },
  { "hmm",     13 },
};

EventInfo::EventInfo()
  : EventInfo(false, false)
{}

EventInfo::EventInfo(bool is_signal,
                     bool is_mc)
  : run(0)
  , lumi(0)
  , event(0)
  , genHiggsDecayMode(-1)
  , genDiHiggsDecayMode(-1)
  , genWeight(1.)
  , pileupWeight(1.)
  , is_signal_(is_signal)
  , is_mc_(is_mc)
  , nLHEReweightingWeight(0)
  , LHEReweightingWeight(nullptr)
  , LHEReweightingWeight_max(69)
{}

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
  genDiHiggsDecayMode = eventInfo.genDiHiggsDecayMode;
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
  return genWeight_tH(1.0, 1.0);
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
  const std::pair<unsigned, double> & settings = tH_sf.at(name);
  assert(settings.first < nLHEReweightingWeight);

  return LHEReweightingWeight[settings.first] * settings.second;
}

void
EventInfo::loadWeight_tH(const std::vector<edm::ParameterSet> & cfg_main,
                         const std::vector<edm::ParameterSet> & cfg_choice)
{
  std::map<unsigned, double> choice_map;
  for(const edm::ParameterSet & cfg_choice_entry: cfg_choice)
  {
    const unsigned idx = cfg_choice_entry.getParameter<unsigned>("idx");
    const double weight = cfg_choice_entry.getParameter<double>("weight");
    assert(! choice_map.count(idx));
    choice_map[idx] = weight;
  }

  std::map<std::string, unsigned> main_map;
  for(const edm::ParameterSet & cfg_main_entry: cfg_main)
  {
    const double kt = cfg_main_entry.getParameter<double>("kt");
    const double kv = cfg_main_entry.getParameter<double>("kv");
    const unsigned idx = cfg_main_entry.getParameter<unsigned>("idx");
    const std::string name = get_tH_weight_str(kt, kv);

    // make sure that we can recover the paramters encoded by the string
    const std::pair<double, double> kt_kv = get_tH_params(name);
    assert(kt_kv.first == kt);
    assert(kt_kv.second == kv);

    assert(! tH_sf.count(name));
    if(choice_map.count(idx))
    {
      tH_sf[name] = std::pair<unsigned, double>(idx, choice_map.at(idx));
      std::cout
        << "Loaded weight '" << name << "': kt = " << kt << " & kv = " << kv
        << " -> weight = " << choice_map.at(idx) <<" @ idx = " << idx << '\n'
      ;
    }
  }

  assert(tH_sf.size() == choice_map.size());
}

std::vector<std::string>
EventInfo::getWeight_tH_str() const
{
  std::vector<std::string> names;
  boost::copy(tH_sf | boost::adaptors::map_keys, std::back_inserter(names));
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
  if(! is_signal())
  {
    throw cmsException(this, __func__, __LINE__)
      << "The event " << *this << " is not a signal event => request "
         "for a decay mode as a string is not applicable\n"
    ;
  }
  for(const auto & kv: EventInfo::decayMode_idString)
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
  std::vector<std::string> decayModes;
  decayModes.reserve(EventInfo::decayMode_idString.size());
  boost::copy(
    EventInfo::decayMode_idString | boost::adaptors::map_keys, std::back_inserter(decayModes)
  );
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
