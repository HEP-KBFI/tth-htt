#include "tthAnalysis/HiggsToTauTau/interface/EvtHistManager_4l.h"

#include "tthAnalysis/HiggsToTauTau/interface/histogramAuxFunctions.h" // fillWithOverFlow(), getLogWeight()
#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // get_era(), kEra_*
#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h" // cmsException()

EvtHistManager_4l::EvtHistManager_4l(const edm::ParameterSet & cfg, bool isControlRegion)
  : HistManagerBase(cfg)
  , era_(get_era(cfg.getParameter<std::string>("era")))
{
  const std::vector<std::string> sysOpts_central = {
    "numElectrons",
    "numMuons",
    "numHadTaus",
    "numJets",
    "numBJets_loose",
    "numBJets_medium",
    "numBJets_loose_vs_numJets",
    "numBJets_medium_vs_numJets"
  };
  std::vector<std::string> sysOpts_all = {
    "EventCounter"
  };
  if ( isControlRegion )
  {
    sysOpts_all.push_back("control");
  } else {
    sysOpts_all.push_back("mva_4l");
    sysOpts_all.push_back("mass_4L");
  }
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
EvtHistManager_4l::getHistogram_EventCounter() const
{
  return histogram_EventCounter_;
}


void
EvtHistManager_4l::bookHistograms(TFileDirectory & dir)
{
  histogram_numElectrons_    = book1D(dir, "numElectrons",    "numElectrons",     5, -0.5,  +4.5);
  histogram_numMuons_        = book1D(dir, "numMuons",        "numMuons",         5, -0.5,  +4.5);
  histogram_numJets_         = book1D(dir, "numJets",         "numJets",         20, -0.5, +19.5);
  histogram_numBJets_loose_  = book1D(dir, "numBJets_loose",  "numBJets_loose",  10, -0.5,  +9.5);
  histogram_numBJets_medium_ = book1D(dir, "numBJets_medium", "numBJets_medium", 10, -0.5,  +9.5);

  histogram_EventCounter_ = book1D(dir, "EventCounter", "EventCounter", 1, -0.5, +0.5);
  Float_t bins_mass_4L[4] = { 70.,200.0,300.0,1000. };
  histogram_mass_4L_ = book1D(dir, "mass_4L", "mass_4L", 3, bins_mass_4L);
  Float_t binsx[3] = { 0.0, 0.55, 1.0 };
  histogram_mva_4l_ = book1D(dir, "mva_4l", "mva_4l", 2, binsx);

  histogram_ctrl_ = book1D(dir, "control", "control", 4, -0.5,  +3.5);
}

void
EvtHistManager_4l::fillHistograms(int numElectrons,
                                  int numMuons,
                                  int numJets,
                                  int numBJets_loose,
                                  int numBJets_medium,
                                  double mass_4L,
                                  double mva_4l,
                                  int ctrl_category,
                                  double evtWeight)
{
  const double evtWeightErr = 0.;

  fillWithOverFlow(histogram_numElectrons_,    numElectrons,    evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_numMuons_,        numMuons,        evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_numJets_,         numJets,         evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_numBJets_loose_,  numBJets_loose,  evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_numBJets_medium_, numBJets_medium, evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mass_4L_, mass_4L, evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mva_4l_, mva_4l, evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_ctrl_, ctrl_category, evtWeight, evtWeightErr);

  fillWithOverFlow(histogram_EventCounter_, 0., evtWeight, evtWeightErr);
}
