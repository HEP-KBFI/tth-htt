#include "tthAnalysis/HiggsToTauTau/interface/EvtHistManager_LeptonFakeRate.h"

#include "tthAnalysis/HiggsToTauTau/interface/histogramAuxFunctions.h"

#include <TMath.h>

EvtHistManager_LeptonFakeRate::EvtHistManager_LeptonFakeRate(const edm::ParameterSet& cfg)
  : HistManagerBase(cfg)
{}

void EvtHistManager_LeptonFakeRate::bookHistograms(TFileDirectory& dir)
{
  // histogram_numElectrons_ = book1D(dir, "numElectrons", "numElectrons", 5, -0.5, +4.5);
  // histogram_numMuons_ = book1D(dir, "numMuons", "numMuons", 5, -0.5, +4.5);
  // histogram_numHadTaus_ = book1D(dir, "numHadTaus", "numHadTaus", 5, -0.5, +4.5);
  // histogram_numJets_ = book1D(dir, "numJets", "numJets", 20, -0.5, +19.5);
  // histogram_numBJets_loose_ = book1D(dir, "numBJets_loose", "numBJets_loose", 10, -0.5, +9.5);
  // histogram_numBJets_medium_ = book1D(dir, "numBJets_medium", "numBJets_medium", 10, -0.5, +9.5);
  // histogram_mLL_ = book1D(dir, "mLL", "mLL", 30, 60., 120.);
  // histogram_mT_e_ = book1D(dir, "mT_e", "mT_e", 40, 0., 200.);
  // histogram_mT_mu_ = book1D(dir, "mT_mu", "mT_mu", 40, 0., 200.);
  histogram_mT_fix_L_ = book1D(dir, "mT_fix_L", "mT_fix_L", 40, 0., 200.);
  histogram_mT_L_ = book1D(dir, "mT_L", "mT_L", 40, 0., 200.);
  histogram_MET_ = book1D(dir, "MET", "MET", 40, 0., 200.);
  histogram_EventCounter_ = book1D(dir, "EventCounter", "EventCounter", 1, -0.5, +0.5);
}

void EvtHistManager_LeptonFakeRate::fillHistograms(double met, double mT_L, double mT_fix_L, double evtWeight)
{
  double evtWeightErr = 0.;
  fillWithOverFlow(histogram_MET_, met, evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mT_fix_L_, mT_fix_L, evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mT_L_, mT_L, evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_EventCounter_, 0., evtWeight, evtWeightErr);
}


