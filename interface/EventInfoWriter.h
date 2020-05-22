#ifndef EVENTINFOWRITER_H
#define EVENTINFOWRITER_H

#include "tthAnalysis/HiggsToTauTau/interface/EventInfo.h" // EventInfo

// forward declarations
class TTree;

class EventInfoWriter
{
public:
  EventInfoWriter();
  EventInfoWriter(bool is_signal,
                  bool is_mc,
                  const std::string & prefix = "");

  void
  setBranches(TTree * tree);

  void
  write(const EventInfo & eventInfo);

  std::string
  getBranchName_run() const;

  std::string
  getBranchName_lumi() const;

  std::string
  getBranchName_event() const;

protected:
  std::string branchName_run_;
  std::string branchName_lumi_;
  std::string branchName_event_;

  std::string branchName_genHiggsDecayMode_;
  std::string branchName_genWeight_;
  std::string branchName_pileupWeight_;
  std::string branchName_pileupWeightUp_;
  std::string branchName_pileupWeightDown_;
  std::string branchName_LHEReweightingWeight;
  std::string branchName_nLHEReweightingWeight;

  EventInfo eventInfo_;
};

#endif // EVENTINFOWRITER_H
