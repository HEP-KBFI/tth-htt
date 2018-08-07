#include "tthAnalysis/HiggsToTauTau/interface/EvtHistManager_3l.h"

#include "tthAnalysis/HiggsToTauTau/interface/histogramAuxFunctions.h" // fillWithOverFlow(), getLogWeight()
#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // get_era(), kEra_*
#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h" // cmsException()

EvtHistManager_3l::EvtHistManager_3l(const edm::ParameterSet & cfg)
  : HistManagerBase(cfg)
  , era_(get_era(cfg.getParameter<std::string>("era")))
{}

const TH1 *
EvtHistManager_3l::getHistogram_EventCounter() const
{
  return histogram_EventCounter_;
}

void
EvtHistManager_3l::bookHistograms(TFileDirectory & dir)
{
  histogram_numElectrons_    = book1D(dir, "numElectrons",    "numElectrons",     5, -0.5,  +4.5);
  histogram_numMuons_        = book1D(dir, "numMuons",        "numMuons",         5, -0.5,  +4.5);
  histogram_numHadTaus_      = book1D(dir, "numHadTaus",      "numHadTaus",       5, -0.5,  +4.5);
  histogram_numJets_         = book1D(dir, "numJets",         "numJets",         20, -0.5, +19.5);
  histogram_numBJets_loose_  = book1D(dir, "numBJets_loose",  "numBJets_loose",  10, -0.5,  +9.5);
  histogram_numBJets_medium_ = book1D(dir, "numBJets_medium", "numBJets_medium", 10, -0.5,  +9.5);

  histogram_numBJets_loose_vs_numJets_  = book2D(dir, "numBJets_loose_vs_numJets",  "numBJets_loose_vs_numJets",  8, -0.5, +7.5, 6, -0.5, +5.5);
  histogram_numBJets_medium_vs_numJets_ = book2D(dir, "numBJets_medium_vs_numJets", "numBJets_medium_vs_numJets", 8, -0.5, +7.5, 6, -0.5, +5.5);

  histogram_mvaOutput_3l_ttV_   = book1D(dir, "mvaOutput_3l_ttV",   "mvaOutput_3l_ttV",   40, -1., +1.);
  histogram_mvaOutput_3l_ttbar_ = book1D(dir, "mvaOutput_3l_ttbar", "mvaOutput_3l_ttbar", 40, -1., +1.);
  histogram_mvaDiscr_3l_        = book1D(dir, "mvaDiscr_3l",        "mvaDiscr_3l",         5,  0.5, 5.5);

  histogram_EventCounter_ = book1D(dir, "EventCounter", "EventCounter", 1, -0.5, +0.5);
}

void
EvtHistManager_3l::fillHistograms(int numElectrons,
                                  int numMuons,
                                  int numHadTaus,
                                  int numJets,
                                  int numBJets_loose,
                                  int numBJets_medium,
                                  double mvaOutput_3l_ttV,
                                  double mvaOutput_3l_ttbar,
                                  double mvaDiscr_3l,
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

  fillWithOverFlow(histogram_mvaOutput_3l_ttV_,   mvaOutput_3l_ttV,   evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mvaOutput_3l_ttbar_, mvaOutput_3l_ttbar, evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mvaDiscr_3l_,        mvaDiscr_3l,        evtWeight, evtWeightErr);

  fillWithOverFlow(histogram_EventCounter_, 0., evtWeight, evtWeightErr);
}
