#include "tthAnalysis/HiggsToTauTau/interface/EvtHistManager_2los_1tau.h"

#include "tthAnalysis/HiggsToTauTau/interface/histogramAuxFunctions.h" // fillWithOverFlow(), fillWithOverFlow2d()

EvtHistManager_2los_1tau::EvtHistManager_2los_1tau(const edm::ParameterSet & cfg)
  : HistManagerBase(cfg)
{

  central_or_shiftOptions_["numElectrons"] = { "central" };
  central_or_shiftOptions_["numMuons"] = { "central" };
  central_or_shiftOptions_["numHadTaus"] = { "central" };
  central_or_shiftOptions_["numJets"] = { "central" };
  central_or_shiftOptions_["numBJets_loose"] = { "central" };
  central_or_shiftOptions_["numBJets_medium"] = { "central" };
  central_or_shiftOptions_["mvaOutput_2lss_ttV"] = { "central" };
  central_or_shiftOptions_["mvaOutput_2lss_ttbar"] = { "central" };
  central_or_shiftOptions_["mvaDiscr_2lss"] = { "central" };
  central_or_shiftOptions_["mvaOutput_2los_1tau_ttV"] = { "central" };
  central_or_shiftOptions_["mvaOutput_2los_1tau_ttbar"] = { "central" };
  central_or_shiftOptions_["mvaOutput_2los_1tau_evtLevelSUM_TTH_19Var"] = { "*" };
  central_or_shiftOptions_["mvaOutput_2los_1tau_evtLevelTT_TTH_20Var"] = { "*" };
  central_or_shiftOptions_["mvaOutput_XGB_Updated"] = { "*" };
  central_or_shiftOptions_["mvaOutput_XGB_Boosted_AK8"] = { "*" };
  central_or_shiftOptions_["mvaDiscr_2los_1tau"] = { "*" };
  central_or_shiftOptions_["mTauTauVis"] = { "central" };
  central_or_shiftOptions_["EventCounter"] = { "*" };

}

const TH1 *
EvtHistManager_2los_1tau::getHistogram_EventCounter() const
{
  return histogram_EventCounter_;
}

void
EvtHistManager_2los_1tau::bookHistograms(TFileDirectory & dir)
{
  histogram_numElectrons_    = book1D(dir, "numElectrons",    "numElectrons",     5, -0.5,  +4.5);
  histogram_numMuons_        = book1D(dir, "numMuons",        "numMuons",         5, -0.5,  +4.5);
  histogram_numHadTaus_      = book1D(dir, "numHadTaus",      "numHadTaus",       5, -0.5,  +4.5);
  histogram_numJets_         = book1D(dir, "numJets",         "numJets",         20, -0.5, +19.5);
  histogram_numBJets_loose_  = book1D(dir, "numBJets_loose",  "numBJets_loose",  10, -0.5,  +9.5);
  histogram_numBJets_medium_ = book1D(dir, "numBJets_medium", "numBJets_medium", 10, -0.5,  +9.5);

  histogram_mvaOutput_2lss_ttV_   = book1D(dir, "mvaOutput_2lss_ttV",   "mvaOutput_2lss_ttV",   40, -1., +1.);
  histogram_mvaOutput_2lss_ttbar_ = book1D(dir, "mvaOutput_2lss_ttbar", "mvaOutput_2lss_ttbar", 40, -1., +1.);
  histogram_mvaDiscr_2lss_        = book1D(dir, "mvaDiscr_2lss",        "mvaDiscr_2lss",         6,  0.5, 6.5);

  histogram_mvaOutput_2los_1tau_ttV_   = book1D(dir, "mvaOutput_2los_1tau_ttV",   "mvaOutput_2los_1tau_ttV",   40, -1., +1.);
  histogram_mvaOutput_2los_1tau_ttbar_ = book1D(dir, "mvaOutput_2los_1tau_ttbar", "mvaOutput_2los_1tau_ttbar", 40, -1., +1.);

  histogram_mvaOutput_2los_1tau_evtLevelSUM_TTH_19Var_ = book1D(dir, "mvaOutput_2los_1tau_evtLevelSUM_TTH_19Var", "mvaOutput_2los_1tau_evtLevelSUM_TTH_19Var", 100, 0., +1.);
  histogram_mvaOutput_2los_1tau_evtLevelTT_TTH_20Var_  = book1D(dir, "mvaOutput_2los_1tau_evtLevelTT_TTH_20Var",  "mvaOutput_2los_1tau_evtLevelTT_TTH_20Var",  100, 0., +1.);

  histogram_mvaOutput_XGB_Updated_ = book1D(dir, "mvaOutput_XGB_Updated", "mvaOutput_XGB_Updated", 100, 0., +1.);
  histogram_mvaOutput_XGB_Boosted_AK8_ = book1D(dir, "mvaOutput_XGB_Boosted_AK8", "mvaOutput_XGB_Boosted_AK8", 100, 0., +1.);

  histogram_mvaDiscr_2los_1tau_        = book1D(dir, "mvaDiscr_2los_1tau",        "mvaDiscr_2los_1tau",         8,  0.5, 8.5);

  histogram_mTauTauVis_   = book1D(dir, "mTauTauVis",   "mTauTauVis",  40,  0., 200.);
  histogram_EventCounter_ = book1D(dir, "EventCounter", "EventCounter", 1, -0.5, +0.5);
}

void
EvtHistManager_2los_1tau::fillHistograms(int numElectrons,
                                         int numMuons,
                                         int numHadTaus,
                                         int numJets,
                                         int numBJets_loose,
                                         int numBJets_medium,
                                         double mvaOutput_2lss_ttV,
                                         double mvaOutput_2lss_ttbar,
                                         double mvaDiscr_2lss,
                                         double mvaOutput_2los_1tau_ttV,
                                         double mvaOutput_2los_1tau_ttbar,
                                         double mvaDiscr_2los_1tau,
                                         double mTauTauVis,
                                         double mvaOutput_2los_1tau_evtLevelSUM_TTH_19Var,
                                         double mvaOutput_2los_1tau_evtLevelTT_TTH_20Var,
                                         double mvaOutput_XGB_Updated,
                                         double mvaOutput_XGB_Boosted_AK8,
                                         double evtWeight)
{
  const double evtWeightErr = 0.;

  fillWithOverFlow(histogram_numElectrons_,    numElectrons,    evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_numMuons_,        numMuons,        evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_numHadTaus_,      numHadTaus,      evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_numJets_,         numJets,         evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_numBJets_loose_,  numBJets_loose,  evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_numBJets_medium_, numBJets_medium, evtWeight, evtWeightErr);

  fillWithOverFlow(histogram_mvaOutput_2lss_ttV_,   mvaOutput_2lss_ttV,   evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mvaOutput_2lss_ttbar_, mvaOutput_2lss_ttbar, evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mvaDiscr_2lss_,        mvaDiscr_2lss,        evtWeight, evtWeightErr);

  fillWithOverFlow(histogram_mvaOutput_2los_1tau_ttV_,   mvaOutput_2los_1tau_ttV,   evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mvaOutput_2los_1tau_ttbar_, mvaOutput_2los_1tau_ttbar, evtWeight, evtWeightErr);

  fillWithOverFlow(histogram_mvaDiscr_2los_1tau_,                        mvaDiscr_2los_1tau,                        evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mvaOutput_2los_1tau_evtLevelSUM_TTH_19Var_, mvaOutput_2los_1tau_evtLevelSUM_TTH_19Var, evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mvaOutput_2los_1tau_evtLevelTT_TTH_20Var_,  mvaOutput_2los_1tau_evtLevelTT_TTH_20Var,  evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mvaOutput_XGB_Updated_,                     mvaOutput_XGB_Updated,                     evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mvaOutput_XGB_Boosted_AK8_,                 mvaOutput_XGB_Boosted_AK8,                 evtWeight, evtWeightErr);

  fillWithOverFlow(histogram_mTauTauVis_,   mTauTauVis, evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_EventCounter_, 0.,         evtWeight, evtWeightErr);
}
