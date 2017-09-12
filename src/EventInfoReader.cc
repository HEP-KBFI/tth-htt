#include "tthAnalysis/HiggsToTauTau/interface/EventInfoReader.h"

#include <TTree.h> // TTree

EventInfoReader::EventInfoReader()
  : EventInfoReader(nullptr)
{}

EventInfoReader::EventInfoReader(EventInfo * info)
  : info_(info)
{}

void
EventInfoReader::setBranchAddresses(TTree * tree)
{
  tree -> SetBranchAddress(RUN_KEY,  &info_ -> run);
  tree -> SetBranchAddress(LUMI_KEY, &info_ -> lumi);
  tree -> SetBranchAddress(EVT_KEY,  &info_ -> event);

  if(info_ -> is_signal())
  {
    tree -> SetBranchAddress(GENHIGGSDECAYMODE_KEY, &info_ -> genHiggsDecayMode);
  }

  if(info_ -> is_mc())
  {
    tree -> SetBranchAddress(GENWEIGHT_KEY, &info_ -> genWeight);
    tree -> SetBranchAddress(PUWEIGHT_KEY,  &info_ -> pileupWeight);
  }
}

void
EventInfoReader::setEventInfo(EventInfo * info)
{
  info_ = info;
}
