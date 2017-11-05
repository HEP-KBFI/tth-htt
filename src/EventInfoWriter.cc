#include "tthAnalysis/HiggsToTauTau/interface/EventInfoWriter.h"

#include "tthAnalysis/HiggsToTauTau/interface/writerAuxFunctions.h" //

EventInfoWriter::EventInfoWriter()
  : EventInfoWriter(false, false, false, "")
{}

EventInfoWriter::EventInfoWriter(bool is_signal,
                                 bool is_mc,
                                 bool is_mc_th,
                                 const std::string & prefix)
{
  const std::string pattern = prefix.empty() ? "%s" : prefix + "_%s";
  branchName_run_   = Form(pattern.data(), RUN_KEY);
  branchName_lumi_  = Form(pattern.data(), LUMI_KEY);
  branchName_event_ = Form(pattern.data(), EVT_KEY);

  branchName_genHiggsDecayMode_ = is_signal ? Form(pattern.data(), GENHIGGSDECAYMODE_KEY) : "";
  branchName_genWeight_         = is_mc     ? Form(pattern.data(), GENWEIGHT_KEY)         : "";
  branchName_genWeight_tH_      = is_mc_th  ? Form(pattern.data(), GENWEIGHTTH_KEY)       : "";
  branchName_pileupWeight_      = is_mc     ? Form(pattern.data(), PUWEIGHT_KEY)          : "";
}

void
EventInfoWriter::setBranches(TTree * tree)
{
  setBranch(tree, &eventInfo_.run, branchName_run_);
  setBranch(tree, &eventInfo_.lumi, branchName_lumi_);
  setBranch(tree, &eventInfo_.event, branchName_event_);
  if(! branchName_genHiggsDecayMode_.empty())
  {
    setBranch(tree, &eventInfo_.genHiggsDecayMode, branchName_genHiggsDecayMode_);
  }
  if(! branchName_genWeight_.empty())
  {
    setBranch(tree, &eventInfo_.genWeight, branchName_genWeight_);
  }
  if(! branchName_genWeight_tH_.empty())
  {
    setBranch(tree, &eventInfo_.genWeight_tH, branchName_genWeight_tH_);
  }
  if(! branchName_pileupWeight_.empty())
  {
    setBranch(tree, &eventInfo_.pileupWeight, branchName_pileupWeight_);
  }
}

void
EventInfoWriter::write(const EventInfo & eventInfo)
{
  eventInfo_ = eventInfo;
}
