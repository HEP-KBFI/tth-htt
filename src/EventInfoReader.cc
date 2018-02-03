#include "tthAnalysis/HiggsToTauTau/interface/EventInfoReader.h"

#include "tthAnalysis/HiggsToTauTau/interface/EventInfo.h" // EventInfo
#include "tthAnalysis/HiggsToTauTau/interface/BranchAddressInitializer.h" // BranchAddressInitializer, TTree, Form()

EventInfoReader::EventInfoReader()
  : EventInfoReader(nullptr)
{}

EventInfoReader::EventInfoReader(EventInfo * info)
  : info_(info)
  , branchName_run("run")
  , branchName_lumi("luminosityBlock")
  , branchName_event("event")
  , branchName_genHiggsDecayMode("genHiggsDecayMode")
  , branchName_genWeight("genWeight")
  , branchName_puWeight("puWeight")
  , branchName_lheWeightSM("lheWeightSM")
{}

void
EventInfoReader::setBranchAddresses(TTree * tree)
{
  BranchAddressInitializer bai(tree);
  bai.setBranchAddress(info_ -> run, branchName_run);
  bai.setBranchAddress(info_ -> lumi, branchName_lumi);
  bai.setBranchAddress(info_ -> event, branchName_event);
  if(info_ -> is_signal())
  {
    bai.setBranchAddress(info_ -> genHiggsDecayMode, branchName_genHiggsDecayMode);
  }
  if(info_ -> is_mc())
  {
    bai.setBranchAddress(info_ -> genWeight,    branchName_genWeight);
    bai.setBranchAddress(info_ -> pileupWeight, branchName_puWeight);
  }
  if(info_ -> is_mc_th())
  {
    bai.setBranchAddress(info_ -> genWeight_tH, branchName_lheWeightSM);
  }
}

void
EventInfoReader::setEventInfo(EventInfo * info)
{
  info_ = info;
}
