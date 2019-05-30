#include "tthAnalysis/HiggsToTauTau/interface/EventInfo.h" // EventInfo

#include <FWCore/Utilities/interface/Exception.h> // cms::Exception

#include <boost/range/algorithm/copy.hpp> // boost::copy()
#include <boost/range/adaptor/map.hpp> // boost::adaptors::map_keys

#include <cmath> // std::fabs()
#include <cstring> // std::memcpy()

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

std::map<std::string, double>
EventInfo::genWeight_tH() const
{
  std::map<std::string, double> dumb = {{"not_th", 1.}};
  if ( nLHEReweightingWeight > LHEReweightingWeight_SMidx )
  {
    // X: the order of the following vector is important == do not change it/remove parts
    std::vector<std::string> dumbStr = {
      "kt_m3p0_kv_1p0" , "kt_m2p0_kv_1p0" , "kt_m1p5_kv_1p0" , "kt_m1p25_kv_1p0" , "kt_m0p75_kv_1p0" , "kt_m0p5_kv_1p0" , "kt_m0p25_kv_1p0" , "kt_0p0_kv_1p0" , "kt_0p25_kv_1p0" , "kt_0p5_kv_1p0" , "kt_0p75_kv_1p0" , "kt_1p0_kv_1p0" , "kt_1p25_kv_1p0" , "kt_1p5_kv_1p0" , "kt_2p0_kv_1p0" , "kt_3p0_kv_1p0",
      "kt_m3p0_kv_1p5" , "kt_m2p0_kv_1p5" , "kt_m1p5_kv_1p5" , "kt_m1p25_kv_1p5" , "kt_m0p75_kv_1p5" , "kt_m0p5_kv_1p5" , "kt_m0p25_kv_1p5" , "kt_0p0_kv_1p5" , "kt_0p25_kv_1p5" , "kt_0p5_kv_1p5" , "kt_0p75_kv_1p5" , "kt_1p0_kv_1p5" , "kt_1p25_kv_1p5" , "kt_1p5_kv_1p5" , "kt_2p0_kv_1p5" , "kt_3p0_kv_1p5" ,
      "kt_m3p0_kv_0p5" , "kt_m2p0_kv_0p5" , "kt_m1p5_kv_0p5" ,  "kt_m1p25_kv_0p5" , "kt_m0p75_kv_0p5" , "kt_m0p5_kv_0p5" , "kt_m0p25_kv_0p5" , "kt_0p0_kv_0p5" , "kt_0p25_kv_0p5" , "kt_0p5_kv_0p5" , "kt_0p75_kv_0p5" , "kt_1p0_kv_0p5" , "kt_1p25_kv_0p5" , "kt_1p5_kv_0p5" , "kt_2p0_kv_0p5" ,  "kt_3p0_kv_0p5"
    };
    int counter = 0;
    for(const std::string & param: dumbStr)
    {
      dumb[param] = LHEReweightingWeight[counter];
      //std::cout << param << " = " << counter << std::endl;
      counter++;
    }
    //std::cout << "kt_1p0_kv_1p0"<< " = " << dumb["kt_1p0_kv_1p0"] << std::endl;
    // X: I leave it here to have a second pair of eyes on the ordering
    /*
    , branchName_lheWeight_kt_m3p0_kv_1p0("LHEWeight_rwgt_1")
    , branchName_lheWeight_kt_m2p0_kv_1p0("LHEWeight_rwgt_2")
    , branchName_lheWeight_kt_m1p5_kv_1p0("LHEWeight_rwgt_3")
    , branchName_lheWeight_kt_m1p25_kv_1p0("LHEWeight_rwgt_4")
    , branchName_lheWeight_kt_m0p75_kv_1p0("LHEWeight_rwgt_5")
    , branchName_lheWeight_kt_m0p5_kv_1p0("LHEWeight_rwgt_6")
    , branchName_lheWeight_kt_m0p25_kv_1p0("LHEWeight_rwgt_7")
    , branchName_lheWeight_kt_0p0_kv_1p0("LHEWeight_rwgt_8")
    , branchName_lheWeight_kt_0p25_kv_1p0("LHEWeight_rwgt_9")
    , branchName_lheWeight_kt_0p5_kv_1p0("LHEWeight_rwgt_10")
    , branchName_lheWeight_kt_0p75_kv_1p0("LHEWeight_rwgt_11")
    , branchName_lheWeight_kt_1p0_kv_1p0("LHEWeight_rwgt_12")
    , branchName_lheWeight_kt_1p25_kv_1p0("LHEWeight_rwgt_13")
    , branchName_lheWeight_kt_1p5_kv_1p0("LHEWeight_rwgt_14")
    , branchName_lheWeight_kt_2p0_kv_1p0("LHEWeight_rwgt_15")
    , branchName_lheWeight_kt_3p0_kv_1p0("LHEWeight_rwgt_16")
    //
    , branchName_lheWeight_kt_m3p0_kv_1p5("LHEWeight_rwgt_17")
    , branchName_lheWeight_kt_m2p0_kv_1p5("LHEWeight_rwgt_18")
    , branchName_lheWeight_kt_m1p5_kv_1p5("LHEWeight_rwgt_19")
    , branchName_lheWeight_kt_m1p25_kv_1p5("LHEWeight_rwgt_20")
    , branchName_lheWeight_kt_m0p75_kv_1p5("LHEWeight_rwgt_21")
    , branchName_lheWeight_kt_m0p5_kv_1p5("LHEWeight_rwgt_22")
    , branchName_lheWeight_kt_m0p25_kv_1p5("LHEWeight_rwgt_23")
    , branchName_lheWeight_kt_0p0_kv_1p5("LHEWeight_rwgt_24")
    , branchName_lheWeight_kt_0p25_kv_1p5("LHEWeight_rwgt_25")
    , branchName_lheWeight_kt_0p5_kv_1p5("LHEWeight_rwgt_26")
    , branchName_lheWeight_kt_0p75_kv_1p5("LHEWeight_rwgt_27")
    , branchName_lheWeight_kt_1p0_kv_1p5("LHEWeight_rwgt_28")
    , branchName_lheWeight_kt_1p25_kv_1p5("LHEWeight_rwgt_29")
    , branchName_lheWeight_kt_1p5_kv_1p5("LHEWeight_rwgt_30")
    , branchName_lheWeight_kt_2p0_kv_1p5("LHEWeight_rwgt_31")
    , branchName_lheWeight_kt_3p0_kv_1p5("LHEWeight_rwgt_32")
    //
    , branchName_lheWeight_kt_m3p0_kv_0p5("LHEWeight_rwgt_33")
    , branchName_lheWeight_kt_m2p0_kv_0p5("LHEWeight_rwgt_34")
    , branchName_lheWeight_kt_m1p5_kv_0p5("LHEWeight_rwgt_35")
    , branchName_lheWeight_kt_m1p25_kv_0p5("LHEWeight_rwgt_36")
    , branchName_lheWeight_kt_m0p75_kv_0p5("LHEWeight_rwgt_37")
    , branchName_lheWeight_kt_m0p5_kv_0p5("LHEWeight_rwgt_38")
    , branchName_lheWeight_kt_m0p25_kv_0p5("LHEWeight_rwgt_39")
    , branchName_lheWeight_kt_0p0_kv_0p5("LHEWeight_rwgt_40")
    , branchName_lheWeight_kt_0p25_kv_0p5("LHEWeight_rwgt_41")
    , branchName_lheWeight_kt_0p5_kv_0p5("LHEWeight_rwgt_42")
    , branchName_lheWeight_kt_0p75_kv_0p5("LHEWeight_rwgt_43")
    , branchName_lheWeight_kt_1p0_kv_0p5("LHEWeight_rwgt_44")
    , branchName_lheWeight_kt_1p25_kv_0p5("LHEWeight_rwgt_45")
    , branchName_lheWeight_kt_1p5_kv_0p5("LHEWeight_rwgt_46")
    , branchName_lheWeight_kt_2p0_kv_0p5("LHEWeight_rwgt_47")
    , branchName_lheWeight_kt_3p0_kv_0p5("LHEWeight_rwgt_48")
    */
  }
  return dumb;
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
