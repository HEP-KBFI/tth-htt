#include "tthAnalysis/HiggsToTauTau/interface/EvtHistManager_LeptonEfficiency.h"

#include "tthAnalysis/HiggsToTauTau/interface/histogramAuxFunctions.h" // fillWithOverFlow()

EvtHistManager_LeptonEfficiency::EvtHistManager_LeptonEfficiency(const edm::ParameterSet & cfg)
  : HistManagerBase(cfg)
{
  const std::vector<std::string> sysOpts_all = {
    "m_ll",
    "EventCounter",
  };
  for(const std::string & sysOpt: sysOpts_all)
  {
    central_or_shiftOptions_[sysOpt] = { "*" };
  }
}

void
EvtHistManager_LeptonEfficiency::bookHistograms(TFileDirectory & dir)
{
  histogram_m_ll_         = book1D(dir, "m_ll",     "m_ll",     40,  0.,  200.);
  histogram_EventCounter_ = book1D(dir, "EventCounter", "EventCounter",  1, -0.5,  +0.5);
}

void
EvtHistManager_LeptonEfficiency::fillHistograms(double m_ll,
						double evtWeight)
{
  const double evtWeightErr = 0.;

  fillWithOverFlow(histogram_m_ll_,     m_ll, evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_EventCounter_, 0., evtWeight, evtWeightErr);
}
