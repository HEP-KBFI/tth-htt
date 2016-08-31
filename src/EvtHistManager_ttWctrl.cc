#include "tthAnalysis/HiggsToTauTau/interface/EvtHistManager_ttWctrl.h"

#include "tthAnalysis/HiggsToTauTau/interface/histogramAuxFunctions.h"

#include <TMath.h>

EvtHistManager_ttWctrl::EvtHistManager_ttWctrl(const edm::ParameterSet& cfg)
  : HistManagerBase(cfg)
{}

void EvtHistManager_ttWctrl::bookHistograms(TFileDirectory& dir)
{
  histogram_numElectrons_ = book1D(dir, "numElectrons", "numElectrons", 5, -0.5, +4.5);
  histogram_numMuons_ = book1D(dir, "numMuons", "numMuons", 5, -0.5, +4.5);
  histogram_numLeptons_ = book1D(dir, "numLeptons", "numLeptons", 5, -0.5, +4.5);
  histogram_numHadTaus_ = book1D(dir, "numHadTaus", "numHadTaus", 5, -0.5, +4.5);
  histogram_numJets_ = book1D(dir, "numJets", "numJets", 20, -0.5, +19.5);
  histogram_numBJets_loose_ = book1D(dir, "numBJets_loose", "numBJets_loose", 10, -0.5, +9.5);
  histogram_numBJets_medium_ = book1D(dir, "numBJets_medium", "numBJets_medium", 10, -0.5, +9.5);

  histogram_sumLeptonCharge_ = book1D(dir, "sumLeptonCharge", "sumLeptonCharge", 7, -3., +3.);

  histogram_EventCounter_ = book1D(dir, "EventCounter", "EventCounter", 1, -0.5, +0.5);
}

void EvtHistManager_ttWctrl::fillHistograms(int numElectrons, int numMuons, int numHadTaus, int numJets, int numBJets_loose, int numBJets_medium, 
					    int sumLeptonCharge, double evtWeight)
{
  double evtWeightErr = 0.;

  fillWithOverFlow(histogram_numElectrons_, numElectrons, evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_numMuons_, numMuons, evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_numLeptons_, numElectrons + numMuons, evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_numHadTaus_, numHadTaus, evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_numJets_, numJets, evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_numBJets_loose_, numBJets_loose, evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_numBJets_medium_, numBJets_medium, evtWeight, evtWeightErr);

  fillWithOverFlow(histogram_sumLeptonCharge_, sumLeptonCharge, evtWeight, evtWeightErr);

  fillWithOverFlow(histogram_EventCounter_, 0., evtWeight, evtWeightErr);
}
