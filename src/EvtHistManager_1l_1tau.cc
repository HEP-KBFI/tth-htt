#include "tthAnalysis/HiggsToTauTau/interface/EvtHistManager_1l_1tau.h"

#include "tthAnalysis/HiggsToTauTau/interface/histogramAuxFunctions.h" // fillWithOverFlow(), fillWithOverFlow2d()

EvtHistManager_1l_1tau::EvtHistManager_1l_1tau(const edm::ParameterSet & cfg)
  : HistManagerBase(cfg)
{
  const std::vector<std::string> sysOpts_central = {
    "numElectrons",
    "numMuons",
    "numHadTaus",
    "numJets",
    "numBJets_loose",
    "numBJets_medium",
    "numBJets_loose_vs_numJets",
    "numBJets_medium_vs_numJets",
    "mTauTauVis",
    "mTauTau"
  };
  const std::vector<std::string> sysOpts_all = {
    "mvaOutput_Legacy",
    "EventCounter",
  };
  for(const std::string & sysOpt: sysOpts_central)
  {
    central_or_shiftOptions_[sysOpt] = { "central" };
  }
  for(const std::string & sysOpt: sysOpts_all)
  {
    central_or_shiftOptions_[sysOpt] = { "*" };
  }
}

const TH1 *
EvtHistManager_1l_1tau::getHistogram_EventCounter() const
{
  return histogram_EventCounter_;
}

void
EvtHistManager_1l_1tau::bookHistograms(TFileDirectory & dir)
{
  histogram_numElectrons_    = book1D(dir, "numElectrons",    "numElectrons",     5, -0.5,  +4.5);
  histogram_numMuons_        = book1D(dir, "numMuons",        "numMuons",         5, -0.5,  +4.5);
  histogram_numHadTaus_      = book1D(dir, "numHadTaus",      "numHadTaus",       5, -0.5,  +4.5);
  histogram_numJets_         = book1D(dir, "numJets",         "numJets",         20, -0.5, +19.5);
  histogram_numBJets_loose_  = book1D(dir, "numBJets_loose",  "numBJets_loose",  10, -0.5,  +9.5);
  histogram_numBJets_medium_ = book1D(dir, "numBJets_medium", "numBJets_medium", 10, -0.5,  +9.5);

  histogram_mTauTauVis_   = book1D(dir, "mTauTauVis", "mTauTauVis",  40,    0.,   200.);
  histogram_mTauTau_      = book1D(dir, "mTauTau",    "mTauTau",     30,    0.,   300.);
  histogram_mvaOutput_1l_1tau_DeepTauMedium_     = book1D(dir, "mvaOutput_Legacy",   "mvaOutput_Legacy",    6,    0.,   1.);

  histogram_EventCounter_ = book1D(dir, "EventCounter", "EventCounter", 1, -0.5, +0.5);
}

void
EvtHistManager_1l_1tau::fillHistograms(int numElectrons,
                                       int numMuons,
                                       int numHadTaus,
                                       int numJets,
                                       int numBJets_loose,
                                       int numBJets_medium,
                                       double mTauTauVis,
                                       double mTauTau,
                                       double mvaOutput_1l_1tau_DeepTauMedium,
                                       double evtWeight)
{
  const double evtWeightErr = 0.;

  fillWithOverFlow(histogram_numElectrons_,    numElectrons,     evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_numMuons_,        numMuons,         evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_numHadTaus_,      numHadTaus,       evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_numJets_,         numJets,          evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_numBJets_loose_,  numBJets_loose,   evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_numBJets_medium_, numBJets_medium,  evtWeight, evtWeightErr);

  fillWithOverFlow(histogram_mTauTauVis_,      mTauTauVis,       evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mTauTau_,         mTauTau,          evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mvaOutput_1l_1tau_DeepTauMedium_,        mvaOutput_1l_1tau_DeepTauMedium,         evtWeight, evtWeightErr);

  fillWithOverFlow(histogram_EventCounter_, 0., evtWeight, evtWeightErr);
}
