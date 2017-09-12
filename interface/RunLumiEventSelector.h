#ifndef tthAnalysis_HiggsToTauTau_RunLumiEventSelector_h
#define tthAnalysis_HiggsToTauTau_RunLumiEventSelector_h

/** \class RunLumiEventSelector
 *
 * Select events based on run + luminosity section + event number pairs
 * written (a three columns separated by white-space character) into an ASCII file
 * 
 * \author Christian Veelken, Tallinn
 *
 */

#include "tthAnalysis/HiggsToTauTau/interface/EventInfo.h" // EventInfo

#include <FWCore/Framework/interface/EDFilter.h>
#include <FWCore/Framework/interface/Event.h>
#include <FWCore/Framework/interface/EventSetup.h>
#include <FWCore/ParameterSet/interface/ParameterSet.h>

#include <TObject.h>

#include <string>
#include <map>

class RunLumiEventSelector 
{
 public:
  // constructor 
  explicit RunLumiEventSelector(const edm::ParameterSet&);
    
  // destructor
  virtual ~RunLumiEventSelector();
    
  bool operator()(ULong_t, ULong_t, ULong_t) const;
  bool operator()(const EventInfo & info) const;

 private:

//--- read ASCII file containing run and event numbers
  void readInputFile();
  
  std::string inputFileName_;

  std::string separator_;

  typedef std::set<ULong_t> eventNumberSet;
  typedef std::map<ULong_t, eventNumberSet> lumiSectionEventNumberMap;
  std::map<ULong_t, lumiSectionEventNumberMap> runLumiSectionEventNumbers_;
  
  typedef std::map<ULong_t, int> matchedEventNumbersMap;
  typedef std::map<ULong_t, matchedEventNumbersMap> matchedLumiSectionEventNumberMap;
  mutable std::map<ULong_t, matchedLumiSectionEventNumberMap> matchedRunLumiSectionEventNumbers_;

  mutable long numEventsProcessed_;
  mutable long numEventsToBeSelected_;
  mutable long numEventsSelected_;
};

RunLumiEventSelector* makeRunLumiEventSelector(const std::string& inputFileName);

#endif // tthAnalysis_HiggsToTauTau_RunLumiEventSelector_h
