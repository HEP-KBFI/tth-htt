#include "tthAnalysis/HiggsToTauTau/interface/EvtHistManager_0l_2tau.h"

#include "tthAnalysis/HiggsToTauTau/interface/histogramAuxFunctions.h" // fillWithOverFlow(), fillWithOverFlow2d()

EvtHistManager_0l_2tau::EvtHistManager_0l_2tau(const edm::ParameterSet & cfg)
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
    "mvaOutput_0l_2tau_ttbar",
    "mvaOutput_0l_2tau_HTT_tt",
    "mvaOutput_0l_2tau_HTT_ttv",
    "mvaOutput_0l_2tau_HTT_sum",
    "mvaOutput_0l_2tau_HTT_sum_dy",
    "mvaDiscr_0l_2tau_HTT",
    "mTauTauVis",
    "pt_HHvis_loose", 
    "pt_HHvis_medium",
    "mTauTau",
    "Pzeta",
    "PzetaVis",
    "PzetaMiss",
    "PzetaComb",
    "mT_tau1",
    "mT_tau2",
    "mbb",
    "mbb_loose",
  };
  const std::vector<std::string> sysOpts_all = {
    "mva_Boosted_AK8",
    "mva_Updated",
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
  histogram_numElectrons_    = book1D(dir, "numElectrons",    "numElectrons",     5, -0.5,  +4.5);
  histogram_numMuons_        = book1D(dir, "numMuons",        "numMuons",         5, -0.5,  +4.5);
  histogram_numHadTaus_      = book1D(dir, "numHadTaus",      "numHadTaus",       5, -0.5,  +4.5);
  histogram_numJets_         = book1D(dir, "numJets",         "numJets",         20, -0.5, +19.5);
  histogram_numBJets_loose_  = book1D(dir, "numBJets_loose",  "numBJets_loose",  10, -0.5,  +9.5);
  histogram_numBJets_medium_ = book1D(dir, "numBJets_medium", "numBJets_medium", 10, -0.5,  +9.5);

  histogram_mvaOutput_0l_2tau_ttbar_      = book1D(dir, "mvaOutput_0l_2tau_ttbar",      "mvaOutput_0l_2tau_ttbar",      20, -1., +1.);
  histogram_mvaOutput_0l_2tau_HTT_tt_     = book1D(dir, "mvaOutput_0l_2tau_HTT_tt",     "mvaOutput_0l_2tau_HTT_tt",      7,  0.,  1.);
  histogram_mvaOutput_0l_2tau_HTT_ttv_    = book1D(dir, "mvaOutput_0l_2tau_HTT_ttv",    "mvaOutput_0l_2tau_HTT_ttv",     7,  0.,  1.);
  histogram_mvaOutput_0l_2tau_HTT_sum_    = book1D(dir, "mvaOutput_0l_2tau_HTT_sum",    "mvaOutput_0l_2tau_HTT_sum",     7,  0.,  1.);
  histogram_mvaOutput_0l_2tau_HTT_sum_dy_ = book1D(dir, "mvaOutput_0l_2tau_HTT_sum_dy", "mvaOutput_0l_2tau_HTT_sum_dy",  7,  0.,  1.);
  histogram_mvaDiscr_0l_2tau_HTT_         = book1D(dir, "mvaDiscr_0l_2tau_HTT",         "mvaDiscr_0l_2tau_HTT",         10,  0., 10.);
  histogram_mva_Boosted_AK8_              = book1D(dir, "mva_Boosted_AK8",              "mva_Boosted_AK8",               7,  0.,  1.);
  histogram_mva_Updated_                  = book1D(dir, "mva_Updated",                  "mva_Updated",                   7,  0.,  1.);

  histogram_mTauTauVis_ = book1D(dir, "mTauTauVis", "mTauTauVis",  40,    0.,   200.);
  histogram_pt_HHvis_loose_ = book1D(dir, "pt_HHvis_loose", "pt_HHvis_loose",  15,    0.,   300.);
  histogram_pt_HHvis_medium_ = book1D(dir, "pt_HHvis_medium", "pt_HHvis_medium",  15,    0.,   300.);
  histogram_mTauTau_    = book1D(dir, "mTauTau",    "mTauTau",     30,    0.,   300.);
  histogram_Pzeta_      = book1D(dir, "Pzeta",      "Pzeta",      100, -500.,  +500.);
  histogram_PzetaVis_   = book1D(dir, "PzetaVis",   "PzetaVis",    50,    0.,   500.);
  histogram_PzetaMiss_  = book1D(dir, "PzetaMiss",  "PzetaMiss",   50,    0.,   500.);
  histogram_PzetaComb_  = book1D(dir, "PzetaComb",  "PzetaComb",  100, -500.,  +500.);
  histogram_mT_tau1_    = book1D(dir, "mT_tau1",    "mT_tau1",     30,    0.,   150.);
  histogram_mT_tau2_    = book1D(dir, "mT_tau2",    "mT_tau2",     30,    0.,   150.);
  histogram_mbb_        = book1D(dir, "mbb",        "mbb",         20,    0.,   300.);
  histogram_mbb_loose_  = book1D(dir, "mbb_loose",  "mbb_loose",   20,    0.,   300.);

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
                                       double mvaOutput_0l_2tau_HTT_sum_dy,
                                       double mvaDiscr_0l_2tau_HTT,
                                       double mva_Boosted_AK8,
                                       double mva_Updated,
                                       double mTauTauVis,
				       double pt_HHvis_loose,
				       double pt_HHvis_medium,
                                       double mTauTau,
                                       double Pzeta,
                                       double PzetaVis,
                                       double PzetaComb,
                                       double mT_tau1,
                                       double mbb,
                                       double mbb_loose,
                                       double evtWeight)
{
  const double evtWeightErr = 0.;

  fillWithOverFlow(histogram_numElectrons_,    numElectrons,     evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_numMuons_,        numMuons,         evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_numHadTaus_,      numHadTaus,       evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_numJets_,         numJets,          evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_numBJets_loose_,  numBJets_loose,   evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_numBJets_medium_, numBJets_medium,  evtWeight, evtWeightErr);

  fillWithOverFlow(histogram_mvaOutput_0l_2tau_ttbar_,      mvaOutput_0l_2tau_ttbar,      evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mvaOutput_0l_2tau_HTT_tt_,     mvaOutput_0l_2tau_HTT_tt,     evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mvaOutput_0l_2tau_HTT_ttv_,    mvaOutput_0l_2tau_HTT_ttv,    evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mvaOutput_0l_2tau_HTT_sum_,    mvaOutput_0l_2tau_HTT_sum,    evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mvaOutput_0l_2tau_HTT_sum_dy_, mvaOutput_0l_2tau_HTT_sum_dy, evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mvaDiscr_0l_2tau_HTT_,         mvaDiscr_0l_2tau_HTT,         evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mva_Boosted_AK8_,              mva_Boosted_AK8,              evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mva_Updated_,                  mva_Updated,                  evtWeight, evtWeightErr);

  fillWithOverFlow(histogram_mTauTauVis_,      mTauTauVis,       evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_pt_HHvis_loose_,      pt_HHvis_loose,       evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_pt_HHvis_medium_,      pt_HHvis_medium,       evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mTauTau_,         mTauTau,          evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_Pzeta_,           Pzeta,            evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_PzetaVis_,        PzetaVis,         evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_PzetaMiss_,       Pzeta - PzetaVis, evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_PzetaComb_,       PzetaComb,        evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mT_tau1_,         mT_tau1,          evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mT_tau2_,         mT_tau1,          evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mbb_,             mbb,              evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mbb_loose_,       mbb_loose,        evtWeight, evtWeightErr);

  fillWithOverFlow(histogram_EventCounter_, 0., evtWeight, evtWeightErr);
}
