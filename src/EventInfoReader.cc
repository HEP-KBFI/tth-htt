#include "tthAnalysis/HiggsToTauTau/interface/EventInfoReader.h"

#include "tthAnalysis/HiggsToTauTau/interface/EventInfo.h" // EventInfo
#include "tthAnalysis/HiggsToTauTau/interface/BranchAddressInitializer.h" // BranchAddressInitializer, TTree, Form()

EventInfoReader::EventInfoReader()
  : EventInfoReader(nullptr)
{}

EventInfoReader::EventInfoReader(EventInfo * info)
  : info_(info)
{}

std::vector<std::string>
EventInfoReader::setBranchAddresses(TTree * tree)
{
  BranchAddressInitializer bai(tree);
  bai.setBranchAddress(info_ -> run, "run");
  bai.setBranchAddress(info_ -> lumi, "luminosityBlock");
  bai.setBranchAddress(info_ -> event, "event");
  if(info_ -> is_signal())
  {
    bai.setBranchAddress(info_ -> genHiggsDecayMode, "genHiggsDecayMode");
  }
  if(info_ -> is_mc())
  {
    bai.setBranchAddress(info_ -> genWeight,    "genWeight");
    bai.setBranchAddress(info_ -> pileupWeight, "puWeight");
  }
  if(info_ -> is_mc_th())
  {
    bai.setBranchAddress(info_ -> genWeight_tH, "lheWeightSM");
  }
  return bai.branchNames;
}

void
EventInfoReader::setEventInfo(EventInfo * info)
{
  info_ = info;
}
