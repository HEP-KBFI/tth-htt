#include "tthAnalysis/HiggsToTauTau/interface/EventInfoReader.h"

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
  bai.setBranchAddress(info_ -> run, RUN_KEY);
  bai.setBranchAddress(info_ -> lumi, LUMI_KEY);
  bai.setBranchAddress(info_ -> event, EVT_KEY);
  if(info_ -> is_signal())
  {
    bai.setBranchAddress(info_ -> genHiggsDecayMode, GENHIGGSDECAYMODE_KEY);
  }
  if(info_ -> is_mc())
  {
    bai.setBranchAddress(info_ -> genWeight,    GENWEIGHT_KEY);
    bai.setBranchAddress(info_ -> pileupWeight, PUWEIGHT_KEY);
  }
  if(info_ -> is_mc_th())
  {
    bai.setBranchAddress(info_ -> genWeight_tH, GENWEIGHTTH_KEY);
  }
  return bai.branchNames;
}

void
EventInfoReader::setEventInfo(EventInfo * info)
{
  info_ = info;
}
