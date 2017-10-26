#ifndef EventInfoReader_H
#define EventInfoReader_H

#include "tthAnalysis/HiggsToTauTau/interface/ReaderBase.h" // ReaderBase
#include "tthAnalysis/HiggsToTauTau/interface/EventInfo.h" // EventInfo

// forward declarations
class TTree;

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
};

#endif // EventInfoReader_H
