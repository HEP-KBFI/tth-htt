#include "tthAnalysis/HiggsToTauTau/interface/EvtHistManager_LeptonFakeRate.h"

#include "tthAnalysis/HiggsToTauTau/interface/histogramAuxFunctions.h" // fillWithOverFlow()

EvtHistManager_LeptonFakeRate::EvtHistManager_LeptonFakeRate(const edm::ParameterSet & cfg)
  : HistManagerBase(cfg)
{
  const std::vector<std::string> sysOpts_all = {
    "mT_fix_L",
    "mT_fix_L_num",
    "mT_fix_L_den",
    "mT_L",
    "MET",
    "EventCounter",
  };
  for(const std::string & sysOpt: sysOpts_all)
  {
    central_or_shiftOptions_[sysOpt] = { "*" };
  }
}

void
EvtHistManager_LeptonFakeRate::bookHistograms(TFileDirectory & dir)
{
  histogram_mT_fix_L_     = book1D(dir, "mT_fix_L",     "mT_fix_L",     40,  0.,  200.);
  histogram_mT_fix_L_num_ = book1D(dir, "mT_fix_L_num", "mT_fix_L_num", 40,  0.,  200.);
  histogram_mT_fix_L_den_ = book1D(dir, "mT_fix_L_den", "mT_fix_L_den", 40,  0.,  200.);
  histogram_mT_L_         = book1D(dir, "mT_L",         "mT_L",         40,  0.,  200.);
  histogram_MET_          = book1D(dir, "MET",          "MET",          40,  0.,  200.);
  histogram_EventCounter_ = book1D(dir, "EventCounter", "EventCounter",  1, -0.5,  +0.5);
}

void
EvtHistManager_LeptonFakeRate::fillHistograms(double met,
                                              double mT_L,
                                              double mT_fix_L,
                                              double evtWeight)
{
  const double evtWeightErr = 0.;

  fillWithOverFlow(histogram_MET_,          met,      evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mT_fix_L_,     mT_fix_L, evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mT_fix_L_num_, mT_fix_L, evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mT_fix_L_den_, mT_fix_L, evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mT_L_,         mT_L,     evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_EventCounter_, 0.,       evtWeight, evtWeightErr);
}
