#ifndef EventInfoReader_H
#define EventInfoReader_H

#include "tthAnalysis/HiggsToTauTau/interface/ReaderBase.h" // ReaderBase

// forward declarations
class TTree;
class EventInfo;

class EventInfoReader
  : public ReaderBase
{
public:
  EventInfoReader();
  EventInfoReader(EventInfo * info);
  ~EventInfoReader() {}

  void
  setBranchAddresses(TTree * tree) override;

  void
  setEventInfo(EventInfo * info);

protected:
  EventInfo * info_;

public:
  const std::string branchName_run;
  const std::string branchName_lumi;
  const std::string branchName_event;
  const std::string branchName_genHiggsDecayMode;
  const std::string branchName_genWeight;
  const std::string branchName_puWeight;
  const std::string branchName_lheWeightSM;
};

#endif // EventInfoReader_H
