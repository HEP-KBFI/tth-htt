#include "tthAnalysis/HiggsToTauTau/interface/RunLumiEventSelector.h"

#include <TPRegexp.h>
#include <TObjArray.h>
#include <TObjString.h>
#include <TString.h>

#include <iostream>
#include <fstream>

const int noMatchRequired = -1;

RunLumiEventSelector::RunLumiEventSelector(const edm::ParameterSet& cfg)
{
  //std::cout << "<RunLumiEventSelector::RunLumiEventSelector>:" << std::endl;

  inputFileName_ = cfg.getParameter<std::string>("inputFileName");

  separator_ = cfg.exists("separator") ? 
    cfg.getParameter<std::string>("separator") : "[[:space:]]+";
  //std::cout << " separator = '" << separator_ << "'" << std::endl;
  
  if ( inputFileName_ == "" ) {
    std::cerr << "<RunLumiEventSelector::RunLumiSectionEventNumberFilter>: Invalid Configuration Parameter 'inputFileName' = " << inputFileName_ << " !!";
    assert(0);
  }
  readInputFile();

  numEventsProcessed_ = 0;
  numEventsSelected_ = 0;
}

RunLumiEventSelector::~RunLumiEventSelector()
{
  std::string matchRemark = ( numEventsSelected_ == numEventsToBeSelected_ ) ? "matches" : "does NOT match";
  std::cout << "<RunLumiEventSelector::~RunLumiEventSelector>:" 
	    << " Number of Events processed = " << numEventsProcessed_ << std::endl
	    << " Number of Events selected = " << numEventsSelected_ << ","
	    << " " << matchRemark << " Number of Events to be selected = " << numEventsToBeSelected_ << "." << std::endl;
 
//--- check for events specified by run + event number in ASCII file
//    and not found in EDM input .root file
  int numRunLumiSectionEventNumbersUnmatched = 0;
  for ( std::map<ULong_t, matchedLumiSectionEventNumberMap>::const_iterator run = matchedRunLumiSectionEventNumbers_.begin();
	run != matchedRunLumiSectionEventNumbers_.end(); ++run ) {
    for ( matchedLumiSectionEventNumberMap::const_iterator lumiSection = run->second.begin();
	  lumiSection != run->second.end(); ++lumiSection ) {
      for ( matchedEventNumbersMap::const_iterator event = lumiSection->second.begin();
	    event != lumiSection->second.end(); ++event ) {
	if ( event->second < 1 ) {
	  if ( numRunLumiSectionEventNumbersUnmatched == 0 ) {
	    std::cout << "Events not found:" << std::endl;
	  }
	  std::cout << " run# = " << run->first << ", ls# " << lumiSection->first << ", event# " << event->first << std::endl;
	  ++numRunLumiSectionEventNumbersUnmatched;
	}
      }
    }
  }

  if ( numRunLumiSectionEventNumbersUnmatched > 0 ) {
    std::cout << "--> Number of unmatched Events = " << numRunLumiSectionEventNumbersUnmatched << std::endl;
  }

//--- check for events specified by run + event number in ASCII file
//    and found more than once in EDM input .root file
  int numRunLumiSectionEventNumbersAmbiguousMatch = 0;
  for ( std::map<ULong_t, matchedLumiSectionEventNumberMap>::const_iterator run = matchedRunLumiSectionEventNumbers_.begin();
	run != matchedRunLumiSectionEventNumbers_.end(); ++run ) {
    for ( matchedLumiSectionEventNumberMap::const_iterator lumiSection = run->second.begin();
	  lumiSection != run->second.end(); ++lumiSection ) {
      for ( matchedEventNumbersMap::const_iterator event = lumiSection->second.begin();
	    event != lumiSection->second.end(); ++event ) {
	if ( event->second > 1 ) {
	  if ( numRunLumiSectionEventNumbersAmbiguousMatch == 0 ) {
	    std::cout << "Events found more than once:" << std::endl;
	  }
	  std::cout << " run# = " << run->first << ", ls# " << lumiSection->first << ", event# " << event->first << std::endl;
	  ++numRunLumiSectionEventNumbersAmbiguousMatch;
	}
      }
    }
  }
  
  if ( numRunLumiSectionEventNumbersAmbiguousMatch > 0 ) {
    std::cout << "--> Number of ambiguously matched Events = " << numRunLumiSectionEventNumbersAmbiguousMatch << std::endl;
  }
}

void RunLumiEventSelector::readInputFile()
{
//--- read run + luminosity section + event number pairs from ASCII file

  std::string regexpParser_threeColumnLine_string = std::string("\\s*[[:digit:]]+\\s*");
  regexpParser_threeColumnLine_string.append(separator_).append("\\s*[[:digit:]]+\\s*").append(separator_).append("\\s*[[:digit:]]+\\s*");
  TPRegexp regexpParser_threeColumnLine(regexpParser_threeColumnLine_string.data());
  std::string regexpParser_threeColumnNumber_string = std::string("\\s*([[:digit:]]+)\\s*");
  regexpParser_threeColumnNumber_string.append(separator_).append("\\s*([[:digit:]]+)\\s*").append(separator_).append("\\s*([[:digit:]]+)\\s*");
  TPRegexp regexpParser_threeColumnNumber(regexpParser_threeColumnNumber_string.data());

  std::ifstream inputFile(inputFileName_.data());
  int iLine = 0;
  numEventsToBeSelected_ = 0;
  while ( !(inputFile.eof() || inputFile.bad()) ) {
    std::string line;
    getline(inputFile, line);
    ++iLine;

//--- skip empty lines
    if ( line == "" ) continue;

    //std::cout << " line = '" << line << "'" << std::endl;

    bool parseError = false;

    TString line_tstring = line.data();
//--- check if line matches three column format;
//    in which case require four matches (first match refers to entire line)
//    and match individually run, event and luminosity section numbers
    if ( regexpParser_threeColumnLine.Match(line_tstring) == 1 ) {
      TObjArray* subStrings = regexpParser_threeColumnNumber.MatchS(line_tstring);
      if ( subStrings->GetEntries() == 4 ) {
	//std::cout << " runNumber_string = " << ((TObjString*)subStrings->At(1))->GetString() << std::endl;
	ULong_t runNumber = ((TObjString*)subStrings->At(1))->GetString().Atoll();
	//std::cout << " lumiSectionNumber_string = " << ((TObjString*)subStrings->At(2))->GetString() << std::endl;
	ULong_t lumiSectionNumber = ((TObjString*)subStrings->At(2))->GetString().Atoll();
	//std::cout << " eventNumber_string = " << ((TObjString*)subStrings->At(3))->GetString() << std::endl;
	ULong_t eventNumber = ((TObjString*)subStrings->At(3))->GetString().Atoll();

	std::cout << "--> adding run# = " << runNumber << ", ls# " << lumiSectionNumber << ", event# " << eventNumber << std::endl;

	runLumiSectionEventNumbers_[runNumber][lumiSectionNumber].insert(eventNumber);
	matchedRunLumiSectionEventNumbers_[runNumber][lumiSectionNumber][eventNumber] = 0;
	++numEventsToBeSelected_;
      } else {
	parseError = true;
      }
      
      delete subStrings;
    } else {
      parseError = true;
    }

    if ( parseError ) {
      std::cerr << "<RunLumiEventSelector::readInputFile>: Error in parsing line " << iLine << " = '" << line << "'" << " of input file = " << inputFileName_ << " !!" << std::endl;
      //assert(0);
    }
  }

  if ( numEventsToBeSelected_ == 0 ) {
    std::cerr << "<RunLumiEventSelector::readInputFile>: Failed to read any run+ls+event numbers from input file = " << inputFileName_ << " !!" << std::endl;
    assert(0);
  }
}

bool RunLumiEventSelector::operator()(ULong_t run, ULong_t ls, ULong_t event) const
{
//--- check if run number matches any of the runs containing events to be selected
  bool isSelected = false;
  if ( runLumiSectionEventNumbers_.find(run) != runLumiSectionEventNumbers_.end() ) {
    const lumiSectionEventNumberMap& lumiSectionEventNumbers = runLumiSectionEventNumbers_.find(run)->second;
    if ( lumiSectionEventNumbers.find(ls) != lumiSectionEventNumbers.end() ) {
      const eventNumberSet& eventNumbers = lumiSectionEventNumbers.find(ls)->second;
      if ( eventNumbers.find(event) != eventNumbers.end() ) isSelected = true;
    }
  }

  ++numEventsProcessed_;
  if ( isSelected ) {
    std::cout << "<RunLumiEventSelector::operator>: selecting run# = " << run << ", ls# " << ls << ", event# " << event << std::endl;
    ++matchedRunLumiSectionEventNumbers_[run][ls][event];
    ++numEventsSelected_;
    return true;
  } else {
    return false;
  }
}

RunLumiEventSelector* makeRunLumiEventSelector(const std::string& inputFileName)
{
  RunLumiEventSelector* run_lumi_eventSelector = 0;
  if ( inputFileName != "" ) {
    edm::ParameterSet cfgRunLumiEventSelector;
    cfgRunLumiEventSelector.addParameter<std::string>("inputFileName", inputFileName);
    cfgRunLumiEventSelector.addParameter<std::string>("separator", ":");
    run_lumi_eventSelector = new RunLumiEventSelector(cfgRunLumiEventSelector);
  }
  return run_lumi_eventSelector;
}
