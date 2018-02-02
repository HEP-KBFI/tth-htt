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

  std::vector<std::string>
  setBranchAddresses(TTree * tree) override;

  void
  setEventInfo(EventInfo * info);

protected:
  EventInfo * info_;
};

#endif // EventInfoReader_H
