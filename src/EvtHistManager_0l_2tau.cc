#include "tthAnalysis/HiggsToTauTau/interface/EvtHistManager_0l_2tau.h"

#include "tthAnalysis/HiggsToTauTau/interface/histogramAuxFunctions.h" // fillWithOverFlow(), fillWithOverFlow2d()

EvtHistManager_0l_2tau::EvtHistManager_0l_2tau(const edm::ParameterSet & cfg)
  : HistManagerBase(cfg)
{}

const TH1 *
EvtHistManager_0l_2tau::getHistogram_EventCounter() const
{
  return histogram_EventCounter_;
}

void
EvtHistManager_0l_2tau::bookHistograms(TFileDirectory & dir)
{
  histogram_numElectrons_    = book1D(dir, "numElectrons",    "numElectrons",     5, -0.5,  +4.5);
  histogram_numMuons_        = book1D(dir, "numMuons",        "numMuons",         5, -0.5,  +4.5);
  histogram_numHadTaus_      = book1D(dir, "numHadTaus",      "numHadTaus",       5, -0.5,  +4.5);
  histogram_numJets_         = book1D(dir, "numJets",         "numJets",         20, -0.5, +19.5);
  histogram_numBJets_loose_  = book1D(dir, "numBJets_loose",  "numBJets_loose",  10, -0.5,  +9.5);
  histogram_numBJets_medium_ = book1D(dir, "numBJets_medium", "numBJets_medium", 10, -0.5,  +9.5);

  histogram_numBJets_loose_vs_numJets_  = book2D(dir, "numBJets_loose_vs_numJets",  "numBJets_loose_vs_numJets",  8, -0.5, +7.5, 6, -0.5, +5.5);
  histogram_numBJets_medium_vs_numJets_ = book2D(dir, "numBJets_medium_vs_numJets", "numBJets_medium_vs_numJets", 8, -0.5, +7.5, 6, -0.5, +5.5);

  histogram_mvaOutput_0l_2tau_ttbar_ = book1D(dir, "mvaOutput_0l_2tau_ttbar", "mvaOutput_0l_2tau_ttbar", 20, -1., +1.);
  histogram_mvaOutput_0l_2tau_HTT_tt_ = book1D(dir, "mvaOutput_0l_2tau_HTT_tt", "mvaOutput_0l_2tau_HTT_tt", 20, 0., 1.);
  histogram_mvaOutput_0l_2tau_HTT_ttv_ = book1D(dir, "mvaOutput_0l_2tau_HTT_ttv", "mvaOutput_0l_2tau_HTT_ttv", 20, 0., 1.);
  histogram_mvaOutput_0l_2tau_HTT_sum_ = book1D(dir, "mvaOutput_0l_2tau_HTT_sum", "mvaOutput_0l_2tau_HTT_sum", 20, 0., 1.);
  histogram_mvaDiscr_0l_2tau_HTT_ = book1D(dir, "mvaDiscr_0l_2tau_HTT", "mvaDiscr_0l_2tau_HTT", 10, 0., 10.);
  
  histogram_mTauTauVis_ = book1D(dir, "mTauTauVis", "mTauTauVis", 40, 0., 200.);
  histogram_mTauTau_    = book1D(dir, "mTauTau",    "mTauTau",    30, 0., 300.);

  histogram_EventCounter_ = book1D(dir, "EventCounter", "EventCounter", 1, -0.5, +0.5);
}

void
EvtHistManager_0l_2tau::fillHistograms(int numElectrons,
                                       int numMuons,
                                       int numHadTaus,
                                       int numJets,
                                       int numBJets_loose,
                                       int numBJets_medium,
                                       double mvaOutput_0l_2tau_ttbar,
				       double mvaOutput_0l_2tau_HTT_tt,
				       double mvaOutput_0l_2tau_HTT_ttv,
				       double mvaOutput_0l_2tau_HTT_sum,
				       float mvaDiscr_0l_2tau_HTT,
                                       double mTauTauVis,
                                       double mTauTau,
                                       double evtWeight)
{
  const double evtWeightErr = 0.;

  fillWithOverFlow(histogram_numElectrons_,    numElectrons,    evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_numMuons_,        numMuons,        evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_numHadTaus_,      numHadTaus,      evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_numJets_,         numJets,         evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_numBJets_loose_,  numBJets_loose,  evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_numBJets_medium_, numBJets_medium, evtWeight, evtWeightErr);
  
  fillWithOverFlow2d(histogram_numBJets_loose_vs_numJets_,  numJets, numBJets_loose,  evtWeight, evtWeightErr);
  fillWithOverFlow2d(histogram_numBJets_medium_vs_numJets_, numJets, numBJets_medium, evtWeight, evtWeightErr);

  fillWithOverFlow(histogram_mvaOutput_0l_2tau_ttbar_, mvaOutput_0l_2tau_ttbar, evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mvaOutput_0l_2tau_HTT_tt_, mvaOutput_0l_2tau_HTT_tt, evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mvaOutput_0l_2tau_HTT_ttv_, mvaOutput_0l_2tau_HTT_ttv, evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mvaOutput_0l_2tau_HTT_sum_, mvaOutput_0l_2tau_HTT_sum, evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mvaDiscr_0l_2tau_HTT_, mvaDiscr_0l_2tau_HTT, evtWeight, evtWeightErr);

  fillWithOverFlow(histogram_mTauTauVis_, mTauTauVis, evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mTauTau_,    mTauTau,    evtWeight, evtWeightErr);

  fillWithOverFlow(histogram_EventCounter_, 0., evtWeight, evtWeightErr);
}
