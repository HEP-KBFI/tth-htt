#include "tthAnalysis/HiggsToTauTau/interface/EvtHistManager_jetToTauFakeRate.h"

#include "tthAnalysis/HiggsToTauTau/interface/histogramAuxFunctions.h"

#include <TMath.h>

EvtHistManager_jetToTauFakeRate::EvtHistManager_jetToTauFakeRate(const edm::ParameterSet& cfg)
  : HistManagerBase(cfg)
{}

void EvtHistManager_jetToTauFakeRate::bookHistograms(TFileDirectory& dir)
{
  histogram_numJets_ = book1D(dir, "numJets", "numJets", 10, -0.5, +9.5);

  histogram_EventCounter_ = book1D(dir, "EventCounter", "EventCounter", 1, -0.5, +0.5);
}

void EvtHistManager_jetToTauFakeRate::fillHistograms(int numJets, double evtWeight)
{
  double evtWeightErr = 0.;

  fillWithOverFlow(histogram_numJets_, numJets, evtWeight, evtWeightErr);

  fillWithOverFlow(histogram_EventCounter_, 0., evtWeight, evtWeightErr);
}
