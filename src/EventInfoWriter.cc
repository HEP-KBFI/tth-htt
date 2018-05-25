#include "tthAnalysis/HiggsToTauTau/interface/EventInfoWriter.h"

#include "tthAnalysis/HiggsToTauTau/interface/BranchAddressInitializer.h" // BranchAddressInitializer, TTree, Form()

EventInfoWriter::EventInfoWriter()
  : EventInfoWriter(false, false, false, "")
{}

EventInfoWriter::EventInfoWriter(bool is_signal,
                                 bool is_mc,
                                 bool is_mc_th,
                                 const std::string & prefix)
{
  const std::string pattern = prefix.empty() ? "%s" : prefix + "_%s";
  branchName_run_   = Form(pattern.data(), "run");
  branchName_lumi_  = Form(pattern.data(), "luminosityBlock");
  branchName_event_ = Form(pattern.data(), "event");

  branchName_genHiggsDecayMode_ = is_signal ? Form(pattern.data(), "genHiggsDecayMode") : "";
  branchName_genWeight_         = is_mc     ? Form(pattern.data(), "genWeight")         : "";
  branchName_genWeight_tH_      = is_mc_th  ? Form(pattern.data(), "LHEWeight_rwgt_12") : "";
  branchName_pileupWeight_      = is_mc     ? Form(pattern.data(), "puWeight")          : "";
}

void
EventInfoWriter::setBranches(TTree * tree)
{
  BranchAddressInitializer bai(tree);

  bai.setBranch(eventInfo_.run, branchName_run_);
  bai.setBranch(eventInfo_.lumi, branchName_lumi_);
  bai.setBranch(eventInfo_.event, branchName_event_);
  if(! branchName_genHiggsDecayMode_.empty())
  {
    bai.setBranch(eventInfo_.genHiggsDecayMode, branchName_genHiggsDecayMode_);
  }
  if(! branchName_genWeight_.empty())
  {
    bai.setBranch(eventInfo_.genWeight, branchName_genWeight_);
  }
  if(! branchName_genWeight_tH_.empty())
  {
    bai.setBranch(eventInfo_.genWeight_tH, branchName_genWeight_tH_);
  }
  if(! branchName_pileupWeight_.empty())
  {
    bai.setBranch(eventInfo_.pileupWeight, branchName_pileupWeight_);
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
EventInfoWriter::getBranchName_genHiggsDecayMode() const
{
  return branchName_genHiggsDecayMode_;
}

std::string
EventInfoWriter::getBranchName_genWeight() const
{
  return branchName_genWeight_;
}

std::string
EventInfoWriter::getBranchName_genWeight_tH() const
{
  return branchName_genWeight_tH_;
}

std::string
EventInfoWriter::getBranchName_pileupWeight() const
{
  return branchName_pileupWeight_;
}
