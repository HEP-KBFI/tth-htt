#include "tthAnalysis/HiggsToTauTau/interface/EvtHistManager_2lss_1tau.h"

#include "tthAnalysis/HiggsToTauTau/interface/histogramAuxFunctions.h"

#include <TMath.h>

EvtHistManager_2lss_1tau::EvtHistManager_2lss_1tau(const edm::ParameterSet& cfg)
  : HistManagerBase(cfg)
{}

void EvtHistManager_2lss_1tau::bookHistograms(TFileDirectory& dir)
{
  histogram_mvaOutput_2lss_ttV_ = book1D(dir, "mvaOutput_2lss_ttV", "mvaOutput_2lss_ttV", 40, -1., +1.);
  histogram_mvaOutput_2lss_ttbar_  = book1D(dir, "mvaOutput_2lss_ttbar", "mvaOutput_2lss_ttbar", 40, -1., +1.);
  histogram_mvaDiscr_2lss_  = book1D(dir, "mvaDiscr_2lss", "mvaDiscr_2lss", 6, 0.5, 6.5);
}

void EvtHistManager_2lss_1tau::fillHistograms(double mvaOutput_2lss_ttV, double mvaOutput_2lss_ttbar, double mvaDiscr_2lss, double evtWeight)
{
  double evtWeightErr = 0.;

  fillWithOverFlow(histogram_mvaOutput_2lss_ttV_, mvaOutput_2lss_ttV, evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mvaOutput_2lss_ttbar_, mvaOutput_2lss_ttbar, evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mvaDiscr_2lss_, mvaDiscr_2lss, evtWeight, evtWeightErr);
}
