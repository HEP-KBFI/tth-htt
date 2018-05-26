#include "tthAnalysis/HiggsToTauTau/interface/EventInfoReader.h"

#include "tthAnalysis/HiggsToTauTau/interface/EventInfo.h" // EventInfo
#include "tthAnalysis/HiggsToTauTau/interface/BranchAddressInitializer.h" // BranchAddressInitializer, TTree, Form()

EventInfoReader::EventInfoReader(bool read_genHiggsDecayMode, bool read_puWeight)
  : EventInfoReader(nullptr, read_genHiggsDecayMode, read_puWeight)
{}

EventInfoReader::EventInfoReader(EventInfo * info, bool read_genHiggsDecayMode, bool read_puWeight)
  : read_genHiggsDecayMode_(read_genHiggsDecayMode)
  , read_puWeight_(read_puWeight)
  , info_(info)
  , branchName_run("run")
  , branchName_lumi("luminosityBlock")
  , branchName_event("event")
  , branchName_genHiggsDecayMode("genHiggsDecayMode")
  , branchName_genWeight("genWeight")
  , branchName_puWeight("puWeight")
  , branchName_lheWeightSM("LHEWeight_rwgt_12")
{}

void
EventInfoReader::setBranchAddresses(TTree * tree)
{
  BranchAddressInitializer bai(tree);
  bai.setBranchAddress(info_ -> run, branchName_run);
  bai.setBranchAddress(info_ -> lumi, branchName_lumi);
  bai.setBranchAddress(info_ -> event, branchName_event);
  if(info_ -> is_signal() && read_genHiggsDecayMode_)
  {
    bai.setBranchAddress(info_ -> genHiggsDecayMode, branchName_genHiggsDecayMode);
  }
  if(info_ -> is_mc())
  {
    bai.setBranchAddress(info_ -> genWeight, branchName_genWeight);
    if (read_puWeight_)
    {
      bai.setBranchAddress(info_ -> pileupWeight, branchName_puWeight);
    }
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
