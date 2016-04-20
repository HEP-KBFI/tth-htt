#include "tthAnalysis/HiggsToTauTau/interface/EvtHistManager_2los_1tau.h"

#include "tthAnalysis/HiggsToTauTau/interface/histogramAuxFunctions.h"

#include <TMath.h>

EvtHistManager_2los_1tau::EvtHistManager_2los_1tau(const edm::ParameterSet& cfg)
  : HistManagerBase(cfg)
{}

void EvtHistManager_2los_1tau::bookHistograms(TFileDirectory& dir)
{
  histogram_mvaOutput_2los_ttV_ = book1D(dir, "mvaOutput_2los_ttV", "mvaOutput_2los_ttV", 40, -1., +1.);
  histogram_mvaOutput_2los_ttbar_  = book1D(dir, "mvaOutput_2los_ttbar", "mvaOutput_2los_ttbar", 40, -1., +1.);
  histogram_mvaDiscr_2los_  = book1D(dir, "mvaDiscr_2los", "mvaDiscr_2los", 6, 0.5, 6.5);

  histogram_numJets_ = book1D(dir, "numJets", "numJets", 10, -0.5, +9.5);
}

void EvtHistManager_2los_1tau::fillHistograms(double mvaOutput_2los_ttV, double mvaOutput_2los_ttbar, double mvaDiscr_2los, int numJets, double evtWeight)
{
  double evtWeightErr = 0.;

  fillWithOverFlow(histogram_mvaOutput_2los_ttV_, mvaOutput_2los_ttV, evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mvaOutput_2los_ttbar_, mvaOutput_2los_ttbar, evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mvaDiscr_2los_, mvaDiscr_2los, evtWeight, evtWeightErr);

  fillWithOverFlow(histogram_numJets_, numJets, evtWeight, evtWeightErr);
}
