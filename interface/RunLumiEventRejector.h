#ifndef tthAnalysis_HiggsToTauTau_RunLumiEventRejector_h
#define tthAnalysis_HiggsToTauTau_RunLumiEventRejector_h

#include "tthAnalysis/HiggsToTauTau/interface/EventInfo.h" // EventInfo

#include <FWCore/ParameterSet/interface/ParameterSet.h> // edm::ParameterSet

#include <set> // std::set<>

class RunLumiEventRejector
{
public:
  // constructor
  explicit RunLumiEventRejector(const edm::ParameterSet & cfg);
  explicit RunLumiEventRejector(const std::vector<std::string> & inputFileNames,
                                const std::string & sampleName);

  // destructor
  virtual ~RunLumiEventRejector();

  bool
  operator()(ULong_t run,
             ULong_t ls,
             ULong_t event) const;

  bool
  operator()(const EventInfo & info) const;

private:

  void readInputFile();

  std::vector<std::string> inputFileNames_;
  std::string sampleName_;

  typedef ULong_t   RunType;
  typedef ULong_t   LumiSectionType;
  typedef ULong64_t EventType;

  typedef std::set<EventType> eventNumberSet;
  typedef std::map<LumiSectionType, eventNumberSet> lumiSectionEventNumberMap;
  std::map<RunType, lumiSectionEventNumberMap> runLumiSectionEventNumbers_;

  mutable unsigned long numEventsProcessed_;
  mutable unsigned long numEventsRejected_;
};

#endif // tthAnalysis_HiggsToTauTau_RunLumiEventRejector_h
