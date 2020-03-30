#include "tthAnalysis/HiggsToTauTau/interface/EvtHistManager_jetToTauFakeRateDYmumu.h"

#include "tthAnalysis/HiggsToTauTau/interface/histogramAuxFunctions.h" // fillWithOverFlow()

EvtHistManager_jetToTauFakeRateDYmumu::EvtHistManager_jetToTauFakeRateDYmumu(const edm::ParameterSet & cfg)
  : HistManagerBase(cfg)
{
  const std::vector<std::string> sysOpts_central = {
    "numElectrons",
    "numMuons",
    "numHadTaus",
    "numJets",
    "numBJets_loose",
    "numBJets_medium",
    "m_ll"
  };
  const std::vector<std::string> sysOpts_all = {
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

void
EvtHistManager_jetToTauFakeRateDYmumu::bookHistograms(TFileDirectory & dir)
{
  histogram_numElectrons_    = book1D(dir, "numElectrons",    "numElectrons",     5, -0.5,   +4.5);
  histogram_numMuons_        = book1D(dir, "numMuons",        "numMuons",         5, -0.5,   +4.5);
  histogram_numHadTaus_      = book1D(dir, "numHadTaus",      "numHadTaus",       5, -0.5,   +4.5);
  histogram_numJets_         = book1D(dir, "numJets",         "numJets",         20, -0.5,  +19.5);
  histogram_numBJets_loose_  = book1D(dir, "numBJets_loose",  "numBJets_loose",  10, -0.5,   +9.5);
  histogram_numBJets_medium_ = book1D(dir, "numBJets_medium", "numBJets_medium", 10, -0.5,   +9.5);
  
  histogram_m_ll_            = book1D(dir, "m_ll",            "m_ll",            40,   0.,  200.);

  histogram_EventCounter_    = book1D(dir, "EventCounter",    "EventCounter",     1,  -0.5,  +0.5);
}

void
EvtHistManager_jetToTauFakeRateDYmumu::fillHistograms(int numElectrons,
                                                      int numMuons,
                                                      int numHadTaus,
                                                      int numJets,
                                                      int numBJets_loose,
                                                      int numBJets_medium,
                                                      double m_ll,
                                                      double evtWeight)
{
  const double evtWeightErr = 0.;

  fillWithOverFlow(histogram_numElectrons_,    numElectrons,            evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_numMuons_,        numMuons,                evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_numHadTaus_,      numHadTaus,              evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_numJets_,         numJets,                 evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_numBJets_loose_,  numBJets_loose,          evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_numBJets_medium_, numBJets_medium,         evtWeight, evtWeightErr);
    
  fillWithOverFlow(histogram_m_ll_,            m_ll,                    evtWeight, evtWeightErr);

  fillWithOverFlow(histogram_EventCounter_,    0.,                      evtWeight, evtWeightErr);
}
