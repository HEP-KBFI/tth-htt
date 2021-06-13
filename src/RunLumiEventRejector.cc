#include "tthAnalysis/HiggsToTauTau/interface/RunLumiEventRejector.h"

#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h" // get_human_line(), cmsException()
#include "tthAnalysis/HiggsToTauTau/interface/LocalFileInPath.h" // LocalFileInPath

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wswitch-enum"
#if defined(__OPTIMIZE__)
#pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
#endif
#include <boost/algorithm/string.hpp> // boost::split(), boost::is_any_of()
#pragma GCC diagnostic pop

#include <boost/lexical_cast.hpp> // boost::lexical_cast<>()
#include <boost/algorithm/string/join.hpp> // boost::algorithm::join()

#include <fstream> // ifstream
#include <cassert> // assert()
#include <regex> // std::regex, std::regex_search(), std::smatch

RunLumiEventRejector::RunLumiEventRejector(const std::vector<std::string> & inputFileNames,
                                           const std::string & sampleName)
  : inputFileNames_(inputFileNames)
  , sampleName_(sampleName)
  , numEventsProcessed_(0)
  , numEventsRejected_(0)
{
  assert(! inputFileNames_.empty());
  assert(! sampleName_.empty());
  readInputFile();
}

RunLumiEventRejector::RunLumiEventRejector(const edm::ParameterSet & cfg)
  : RunLumiEventRejector(
      cfg.getParameter<std::vector<std::string>>("inputFileNames"),
      cfg.getParameter<std::string>("sampleName")
    )
{}

RunLumiEventRejector::~RunLumiEventRejector()
{
  std::cout << get_human_line(this, __func__, __LINE__)
            << "Rejected " << numEventsRejected_ << " events out of " << numEventsProcessed_ << '\n';
}

bool
RunLumiEventRejector::operator()(ULong_t run,
                                 ULong_t ls,
                                 ULong_t event) const
{
//--- check if run number matches any of the runs containing events to be selected
  bool isSelected = false;
  if(runLumiSectionEventNumbers_.count(run))
  {
    const lumiSectionEventNumberMap & lumiSectionEventNumbers = runLumiSectionEventNumbers_.at(run);
    if(lumiSectionEventNumbers.count(ls))
    {
      const eventNumberSet & eventNumbers = lumiSectionEventNumbers.at(ls);
      if(eventNumbers.count(event))
      {
        isSelected = true;
        ++numEventsRejected_;

        std::stringstream ss;
        ss << run << ':' << ls << ':' << event;
        std::cout << get_human_line(this, __func__, __LINE__) << "WARNING: rejected event " << ss.str() << '\n';
      }
    }
  }

  ++numEventsProcessed_;

  return isSelected;
}

bool
RunLumiEventRejector::operator()(const EventInfo & info) const
{
  return RunLumiEventRejector::operator()(info.run, info.lumi, info.event);
}

void
RunLumiEventRejector::readInputFile()
{
  unsigned long long numToReject = 0;
  for(const std::string & inputFileName: inputFileNames_)
  {
    const std::string inputFileNamePath = LocalFileInPath(inputFileName).fullPath();
    std::ifstream inputFile(inputFileNamePath);
    if(inputFile)
    {
      for(std::string line; std::getline(inputFile, line); )
      {
        const std::size_t space_pos = line.find_first_of(" ");
        if(space_pos == std::string::npos)
        {
          throw cmsException(this, __func__, __LINE__) << "Unable to parse line from " << inputFileName << ": " << line;
        }
        const std::string sample_name = line.substr(0, space_pos);
        if(sample_name != sampleName_)
        {
          continue;
        }

        std::vector<std::string> rle_split;
        const std::string rle_str = line.substr(space_pos + 1);
        boost::split(rle_split, rle_str, boost::is_any_of(";"));

        std::smatch match;
        const std::regex pattern(boost::algorithm::join(std::vector<std::string>(3, "([[:digit:]]+)"), ":"));
        for(const std::string & rle: rle_split)
        {
          bool parseError = false;
          try
          {
            if(std::regex_search(rle, match, pattern))
            {
              const RunType         runNumber         = boost::lexical_cast<RunType>        (match[1]);
              const LumiSectionType lumiSectionNumber = boost::lexical_cast<LumiSectionType>(match[2]);
              const EventType       eventNumber       = boost::lexical_cast<EventType>      (match[3]);

              runLumiSectionEventNumbers_[runNumber][lumiSectionNumber].insert(eventNumber);
              ++numToReject;
            }
            else
            {
              parseError = true;
            }
          }
          catch(const boost::bad_lexical_cast & e)
          {
            parseError = true;
          }

          if(parseError)
          {
            throw cmsException(this, __func__, __LINE__) << "Unable to parse run:lumi:event numbers from " << inputFileName;
          }
        }
      }
    }
    else
    {
      throw cmsException(this, __func__, __LINE__) << "Could not open file " << inputFileName << " for reading";
    }
  }
  std::cout << get_human_line(this, __func__, __LINE__) << "Considering " << numToReject << " events to reject\n";
}
