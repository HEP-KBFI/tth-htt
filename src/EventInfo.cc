#include "tthAnalysis/HiggsToTauTau/interface/EventInfo.h" // EventInfo

#include <FWCore/Utilities/interface/Exception.h> // cms::Exception

#include <boost/range/algorithm/copy.hpp> // boost::copy()
#include <boost/range/adaptor/map.hpp> // boost::adaptors::map_keys

#include <cmath> // std::fabs()

#define EPS 1E-2

const std::map<std::string, GENHIGGSDECAYMODE_TYPE> EventInfo::decayMode_idString =
{
  { "ttH_hww", static_cast<GENHIGGSDECAYMODE_TYPE>(24) },
  { "ttH_hzz", static_cast<GENHIGGSDECAYMODE_TYPE>(23) },
  { "ttH_htt", static_cast<GENHIGGSDECAYMODE_TYPE>(15) }
};

EventInfo::EventInfo()
  : EventInfo(false, false, false)
{}

EventInfo::EventInfo(bool is_signal,
                     bool is_mc,
                     bool is_mc_th)
  : run(0)
  , lumi(0)
  , event(0)
  , genHiggsDecayMode(-1)
  , genWeight(1.)
  , pileupWeight(1.)
  , is_signal_(is_signal)
  , is_mc_(is_mc)
  , is_mc_th_(is_mc_th)
{}

EventInfo::EventInfo(const EventInfo & eventInfo)
{
  *this = eventInfo;
}

EventInfo &
EventInfo::operator=(const EventInfo & eventInfo)
{
  run               = eventInfo.run;
  lumi              = eventInfo.lumi;
  event             = eventInfo.event;
  genHiggsDecayMode = eventInfo.genHiggsDecayMode;
  genWeight         = eventInfo.genWeight;
  genWeight_tH      = eventInfo.genWeight_tH;

  is_signal_ = eventInfo.is_signal_;
  is_mc_     = eventInfo.is_mc_;
  is_mc_th_  = eventInfo.is_mc_th_;

  return *this;
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
EventInfo::is_mc_th() const
{
  return is_mc_th_;
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
         "for a decay mode as a string is not applicable\n";
  }
  for(const auto & kv: EventInfo::decayMode_idString)
  {
    if(std::fabs(genHiggsDecayMode - kv.second) < EPS)
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

std::ostream &
operator<<(std::ostream & os,
           const EventInfo & info)
{
  os << "run = " << info.run << ", ls = " << info.lumi << ", event = " << info.event;
  return os;
}
