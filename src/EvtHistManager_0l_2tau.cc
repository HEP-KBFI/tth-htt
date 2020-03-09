#include "tthAnalysis/HiggsToTauTau/interface/EvtHistManager_0l_2tau.h"

#include "tthAnalysis/HiggsToTauTau/interface/histogramAuxFunctions.h" // fillWithOverFlow(), fillWithOverFlow2d()
#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h" // cmsException()

EvtHistManager_0l_2tau::EvtHistManager_0l_2tau(const edm::ParameterSet & cfg)
  : HistManagerBase(cfg)
  , option_(kOption_undefined)
{
  const std::string option_string = cfg.getParameter<std::string>("option");
  if(option_string == "allHistograms")
  {
    option_ = kOption_allHistograms;
  }
  else if(option_string == "minimalHistograms")
  {
    option_ = kOption_minimalHistograms;
  }
  else
  {
    throw cmsException(__func__) << "Invalid Configuration parameter 'option' = " << option_string;
  }
  const std::vector<std::string> sysOpts_central = {
    "numElectrons",
    "numMuons",
    "numHadTaus",
    "numJets",
    "numBJets_loose",
    "numBJets_medium",
    "numBJets_loose_vs_numJets",
    "numBJets_medium_vs_numJets",
    "mva_Updated",
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
EvtHistManager_0l_2tau::getHistogram_EventCounter() const
{
  return histogram_EventCounter_;
}

void
EvtHistManager_0l_2tau::bookHistograms(TFileDirectory & dir)
{
  if(option_ == kOption_allHistograms)
  {
    histogram_numElectrons_    = book1D(dir, "numElectrons",    "numElectrons",     5, -0.5,  +4.5);
    histogram_numMuons_        = book1D(dir, "numMuons",        "numMuons",         5, -0.5,  +4.5);
    histogram_numHadTaus_      = book1D(dir, "numHadTaus",      "numHadTaus",       5, -0.5,  +4.5);
    histogram_numJets_         = book1D(dir, "numJets",         "numJets",         20, -0.5, +19.5);
    histogram_numBJets_loose_  = book1D(dir, "numBJets_loose",  "numBJets_loose",  10, -0.5,  +9.5);
    histogram_numBJets_medium_ = book1D(dir, "numBJets_medium", "numBJets_medium", 10, -0.5,  +9.5);
  }

  histogram_mvaOutput_Legacy_ = book1D(dir, "mvaOutput_Legacy", "mvaOutput_Legacy", 10, 0., +1.);
  histogram_mva_Updated_      = book1D(dir, "mva_Updated",      "mva_Updated",       7, 0., +1.);

  histogram_mTauTauVis_ = book1D(dir, "mTauTauVis", "mTauTauVis",  40, 0., 200.);
  histogram_mTauTau_    = book1D(dir, "mTauTau",    "mTauTau",     30, 0., 300.);

  histogram_EventCounter_ = book1D(dir, "EventCounter", "EventCounter", 1, -0.5, +0.5);
}

void
EvtHistManager_0l_2tau::fillHistograms(const EvtHistManager_0l_2tau_Input & variables)
{
  const double evtWeightErr = 0.;
  const double & evtWeight = variables.evtWeight;

  if(option_ == kOption_allHistograms)
  {
    fillWithOverFlow(histogram_numElectrons_,    variables.numElectrons,     evtWeight, evtWeightErr);
    fillWithOverFlow(histogram_numMuons_,        variables.numMuons,         evtWeight, evtWeightErr);
    fillWithOverFlow(histogram_numHadTaus_,      variables.numHadTaus,       evtWeight, evtWeightErr);
    fillWithOverFlow(histogram_numJets_,         variables.numJets,          evtWeight, evtWeightErr);
    fillWithOverFlow(histogram_numBJets_loose_,  variables.numBJets_loose,   evtWeight, evtWeightErr);
    fillWithOverFlow(histogram_numBJets_medium_, variables.numBJets_medium,  evtWeight, evtWeightErr);
  }

  fillWithOverFlow(histogram_mvaOutput_Legacy_, variables.mvaOutput_Legacy, evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mva_Updated_,      variables.mva_Updated,      evtWeight, evtWeightErr);

  fillWithOverFlow(histogram_mTauTauVis_, variables.mTauTauVis, evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mTauTau_,    variables.mTauTau,    evtWeight, evtWeightErr);

  fillWithOverFlow(histogram_EventCounter_, 0., evtWeight, evtWeightErr);
}
