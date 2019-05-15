#include "tthAnalysis/HiggsToTauTau/interface/EventInfo.h" // EventInfo

#include <FWCore/Utilities/interface/Exception.h> // cms::Exception

#include <boost/range/algorithm/copy.hpp> // boost::copy()
#include <boost/range/adaptor/map.hpp> // boost::adaptors::map_keys

#include <cmath> // std::fabs()
#include <cstring> // std::memcpy()

#define EPS 1E-2

const std::map<std::string, Float_t> EventInfo::decayMode_idString =
{
  { "ttH_hww",     24 },
  { "ttH_hzz",     23 },
  { "ttH_htt",     15 },
  { "ttH_hzg", 230022 },
  { "ttH_hmm",     13 },
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
  , LHEReweightingWeight_SMidx(11)
  , LHEReweightingWeight_max(69)
{}

EventInfo::EventInfo(const EventInfo & eventInfo)
  : LHEReweightingWeight_SMidx(eventInfo.LHEReweightingWeight_SMidx)
  , LHEReweightingWeight_max(eventInfo.LHEReweightingWeight_max)
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

Float_t
EventInfo::genWeight_tH() const
{
  return nLHEReweightingWeight > LHEReweightingWeight_SMidx ? LHEReweightingWeight[LHEReweightingWeight_SMidx] : 1.;
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
    throw cms::Exception("EventInfo")
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
