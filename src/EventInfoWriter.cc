#include "tthAnalysis/HiggsToTauTau/interface/EventInfoWriter.h"

#include "tthAnalysis/HiggsToTauTau/interface/BranchAddressInitializer.h" // BranchAddressInitializer, TTree, Form()

EventInfoWriter::EventInfoWriter()
  : EventInfoWriter(false, false, "")
{}

EventInfoWriter::EventInfoWriter(bool is_signal,
                                 bool is_mc,
                                 const std::string & prefix)
{
  const std::string pattern = prefix.empty() ? "%s" : prefix + "_%s";
  branchName_run_     = Form(pattern.data(), "run");
  branchName_lumi_    = Form(pattern.data(), "luminosityBlock");
  branchName_event_   = Form(pattern.data(), "event");
  branchName_PV_ndof_ = Form(pattern.data(), "PV_ndof");

  branchName_genHiggsDecayMode_ = is_signal ? Form(pattern.data(), "genHiggsDecayMode") : "";
  branchName_genWeight_         = is_mc     ? Form(pattern.data(), "genWeight")         : "";
  branchName_pileupWeight_      = is_mc     ? Form(pattern.data(), "puWeight")          : "";

  const std::string LHEReweightingWeight_base = "LHEReweightingWeight";
  branchName_LHEReweightingWeight  = is_mc ? Form(pattern.data(), LHEReweightingWeight_base.data())              : "";
  branchName_nLHEReweightingWeight = is_mc ? Form(pattern.data(), Form("n%s", LHEReweightingWeight_base.data())) : "";
}

void
EventInfoWriter::setBranches(TTree * tree)
{
  BranchAddressInitializer bai(tree);

  bai.setBranch(eventInfo_.run, branchName_run_);
  bai.setBranch(eventInfo_.lumi, branchName_lumi_);
  bai.setBranch(eventInfo_.event, branchName_event_);
  bai.setBranch(eventInfo_.PV_ndof, branchName_PV_ndof_);
  if(! branchName_genHiggsDecayMode_.empty())
  {
    bai.setBranch(eventInfo_.genHiggsDecayMode, branchName_genHiggsDecayMode_);
  }
  if(! branchName_genWeight_.empty())
  {
    bai.setBranch(eventInfo_.genWeight, branchName_genWeight_);
  }
  if(! branchName_pileupWeight_.empty())
  {
    bai.setBranch(eventInfo_.pileupWeight, branchName_pileupWeight_);
  }
  if(! branchName_nLHEReweightingWeight.empty())
  {
    bai.setBranch(eventInfo_.nLHEReweightingWeight, branchName_nLHEReweightingWeight);
  }
  if(! branchName_LHEReweightingWeight.empty())
  {
    bai.setBranch(eventInfo_.LHEReweightingWeight, branchName_LHEReweightingWeight);
  }
}

void
EventInfoWriter::write(const EventInfo & eventInfo)
{
  eventInfo_ = eventInfo;
}

std::string
EventInfoWriter::getBranchName_run() const
{
  return branchName_run_;
}

std::string
EventInfoWriter::getBranchName_lumi() const
{
  return branchName_lumi_;
}

std::string
EventInfoWriter::getBranchName_event() const
{
  return branchName_event_;
}

std::string
EventInfoWriter::getBranchName_PV_ndof() const
{
  return branchName_PV_ndof_;
}
