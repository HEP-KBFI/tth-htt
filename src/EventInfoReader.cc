#include "tthAnalysis/HiggsToTauTau/interface/EventInfoReader.h"

#include "tthAnalysis/HiggsToTauTau/interface/EventInfo.h" // EventInfo
#include "tthAnalysis/HiggsToTauTau/interface/BranchAddressInitializer.h" // BranchAddressInitializer, TTree, Form()

EventInfoReader::EventInfoReader(PUsys puSys_option,
                                 bool read_genHiggsDecayMode,
                                 bool read_puWeight)
  : EventInfoReader(nullptr, puSys_option, read_genHiggsDecayMode, read_puWeight)
{}

EventInfoReader::EventInfoReader(EventInfo * info,
                                 PUsys puSys_option,
                                 bool read_genHiggsDecayMode,
                                 bool read_puWeight)
  : read_genHiggsDecayMode_(read_genHiggsDecayMode)
  , read_puWeight_(read_puWeight)
  , info_(info)
  , branchName_run("run")
  , branchName_lumi("luminosityBlock")
  , branchName_event("event")
  , branchName_PV_ndof("PV_ndof")
  , branchName_genHiggsDecayMode("genHiggsDecayMode")
  , branchName_genWeight("genWeight")
  , branchName_LHEReweightingWeight("LHEReweightingWeight")
  , branchName_nLHEReweightingWeight(Form("n%s", branchName_LHEReweightingWeight.data()))
{}

EventInfoReader::~EventInfoReader()
{
  if(info_ -> is_mc())
  {
    delete[] info_ -> LHEReweightingWeight;
  }
}

void
EventInfoReader::setBranchAddresses(TTree * tree)
{
  BranchAddressInitializer bai(tree);
  bai.setBranchAddress(info_ -> run, branchName_run);
  bai.setBranchAddress(info_ -> lumi, branchName_lumi);
  bai.setBranchAddress(info_ -> event, branchName_event);
  bai.setBranchAddress(info_ -> PV_ndof, branchName_PV_ndof);
  if(info_ -> is_signal() && read_genHiggsDecayMode_)
  {
    bai.setBranchAddress(info_ -> genHiggsDecayMode, branchName_genHiggsDecayMode);
  }
  if(info_ -> is_mc())
  {
    bai.setBranchAddress(info_ -> genWeight, branchName_genWeight);
    if(read_puWeight_)
    {
      bai.setBranchAddress(info_ -> pileupWeight, getBranchName_pileup(PUsys::central));
      bai.setBranchAddress(info_ -> pileupWeightUp, getBranchName_pileup(PUsys::up));
      bai.setBranchAddress(info_ -> pileupWeightDown, getBranchName_pileup(PUsys::down));
    }
  }
  if(info_ -> is_mc() && ! info_ -> tH_sf.empty())
  {
    BranchAddressInitializer bai_LHEReweight(tree, info_ -> LHEReweightingWeight_max);
    bai_LHEReweight.setBranchAddress(info_ -> nLHEReweightingWeight, branchName_nLHEReweightingWeight);
    bai_LHEReweight.setBranchAddress(info_ -> LHEReweightingWeight, branchName_LHEReweightingWeight);
  }
}

void
EventInfoReader::setEventInfo(EventInfo * info)
{
  info_ = info;
}
