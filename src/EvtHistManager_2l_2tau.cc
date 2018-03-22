#include "tthAnalysis/HiggsToTauTau/interface/EvtHistManager_2l_2tau.h"

#include "tthAnalysis/HiggsToTauTau/interface/histogramAuxFunctions.h"

#include <TMath.h>

EvtHistManager_2l_2tau::EvtHistManager_2l_2tau(const edm::ParameterSet& cfg)
  : HistManagerBase(cfg)
{}

void EvtHistManager_2l_2tau::bookHistograms(TFileDirectory& dir)
{
  histogram_numElectrons_ = book1D(dir, "numElectrons", "numElectrons", 5, -0.5, +4.5);
  histogram_numMuons_ = book1D(dir, "numMuons", "numMuons", 5, -0.5, +4.5);
  histogram_numHadTaus_ = book1D(dir, "numHadTaus", "numHadTaus", 5, -0.5, +4.5);
  histogram_numJets_ = book1D(dir, "numJets", "numJets", 20, -0.5, +19.5);
  histogram_numBJets_loose_ = book1D(dir, "numBJets_loose", "numBJets_loose", 10, -0.5, +9.5);
  histogram_numBJets_medium_ = book1D(dir, "numBJets_medium", "numBJets_medium", 10, -0.5, +9.5);

  histogram_numBJets_loose_vs_numJets_ = book2D(dir, "numBJets_loose_vs_numJets", "numBJets_loose_vs_numJets", 8, -0.5, +7.5, 6, -0.5, +5.5);
  histogram_numBJets_medium_vs_numJets_ = book2D(dir, "numBJets_medium_vs_numJets", "numBJets_medium_vs_numJets", 8, -0.5, +7.5, 6, -0.5, +5.5);

  histogram_mvaOutput_2l_2tau_ttV_ = book1D(dir, "mvaOutput_2l_2tau_ttV", "mvaOutput_2l_2tau_ttV", 40, -1., +1.);
  histogram_mvaOutput_2l_2tau_ttbar_ = book1D(dir, "mvaOutput_2l_2tau_ttbar", "mvaOutput_2l_2tau_ttbar", 40, -1., +1.);
  histogram_mvaDiscr_2l_2tau_  = book1D(dir, "mvaDiscr_2l_2tau", "mvaDiscr_2l_2tau", 6, 0.5, 6.5);

  histogram_mTauTauVis_ = book1D(dir, "mTauTauVis", "mTauTauVis", 40, 0., 200.);
  histogram_leptonPairCharge_ = book1D(dir, "leptonPairCharge", "leptonPairCharge", 5, -2.5, +2.5);
  histogram_hadTauPairCharge_ = book1D(dir, "hadTauPairCharge", "hadTauPairCharge", 5, -2.5, +2.5);


  histogram_mvaOutput_noHTT_tt_ = book1D(dir, "mvaOutput_noHTT_tt", "mvaOutput_noHTT_tt", 100, 0.0, 1.0);
  histogram_mvaOutput_noHTT_ttV_ = book1D(dir, "mvaOutput_noHTT_ttV", "mvaOutput_noHTT_ttV", 100, 0.0, 1.0);
  histogram_mvaOutput_noHTT_SUM_M_ = book1D(dir, "mvaOutput_noHTT_SUM_M", "mvaOutput_noHTT_SUM_M", 100, 0.0, 1.0);
  histogram_mvaOutput_noHTT_SUM_T_ = book1D(dir, "mvaOutput_noHTT_SUM_T", "mvaOutput_noHTT_SUM_T", 100, 0.0, 1.0);
  histogram_mvaOutput_noHTT_SUM_VT_= book1D(dir, "mvaOutput_noHTT_SUM_VT", "mvaOutput_noHTT_SUM_VT", 100, 0.0, 1.0);
  histogram_mvaOutput_noHTT_1B_M_ = book1D(dir, "mvaOutput_noHTT_1B_M", "mvaOutput_noHTT_1B_M", 100, 0.0, 1.0);
  histogram_mvaOutput_noHTT_1B_T_ = book1D(dir, "mvaOutput_noHTT_1B_T", "mvaOutput_noHTT_1B_T", 100, 0.0, 1.0);
  histogram_mvaOutput_noHTT_1B_VT_= book1D(dir, "mvaOutput_noHTT_1B_VT", "mvaOutput_noHTT_1B_VT", 100, 0.0, 1.0);
  histogram_EventCounter_ = book1D(dir, "EventCounter", "EventCounter", 1, -0.5, +0.5);
}

void EvtHistManager_2l_2tau::fillHistograms(int numElectrons, int numMuons, int numHadTaus, int numJets, int numBJets_loose, int numBJets_medium,
					    double mvaOutput_2l_2tau_ttV, double mvaOutput_2l_2tau_ttbar, double mvaDiscr_2l_2tau,
					    double mTauTauVis, double leptonPairCharge, double hadTauPairCharge, double evtWeight,
              double mvaOutput_noHTT_tt, double mvaOutput_noHTT_ttV,
              double mvaOutput_noHTT_SUM_M, double mvaOutput_noHTT_SUM_T, double mvaOutput_noHTT_SUM_VT,
              double mvaOutput_noHTT_1B_M, double mvaOutput_noHTT_1B_T, double mvaOutput_noHTT_1B_VT
            )
{
  double evtWeightErr = 0.;

  fillWithOverFlow(histogram_numElectrons_, numElectrons, evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_numMuons_, numMuons, evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_numHadTaus_, numHadTaus, evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_numJets_, numJets, evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_numBJets_loose_, numBJets_loose, evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_numBJets_medium_, numBJets_medium, evtWeight, evtWeightErr);

  fillWithOverFlow2d(histogram_numBJets_loose_vs_numJets_, numJets, numBJets_loose, evtWeight, evtWeightErr);
  fillWithOverFlow2d(histogram_numBJets_medium_vs_numJets_, numJets, numBJets_medium, evtWeight, evtWeightErr);

  fillWithOverFlow(histogram_mvaOutput_2l_2tau_ttV_, mvaOutput_2l_2tau_ttV, evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mvaOutput_2l_2tau_ttbar_, mvaOutput_2l_2tau_ttbar, evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mvaDiscr_2l_2tau_, mvaDiscr_2l_2tau, evtWeight, evtWeightErr);

  fillWithOverFlow(histogram_mTauTauVis_, mTauTauVis, evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_leptonPairCharge_, leptonPairCharge, evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_hadTauPairCharge_, hadTauPairCharge, evtWeight, evtWeightErr);

  fillWithOverFlow(histogram_EventCounter_, 0., evtWeight, evtWeightErr);

  fillWithOverFlow(histogram_mvaOutput_noHTT_tt_, mvaOutput_noHTT_tt, evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mvaOutput_noHTT_ttV_, mvaOutput_noHTT_ttV, evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mvaOutput_noHTT_SUM_M_, mvaOutput_noHTT_SUM_M, evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mvaOutput_noHTT_SUM_T_, mvaOutput_noHTT_SUM_T, evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mvaOutput_noHTT_SUM_VT_, mvaOutput_noHTT_SUM_VT, evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mvaOutput_noHTT_1B_M_, mvaOutput_noHTT_1B_M, evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mvaOutput_noHTT_1B_T_, mvaOutput_noHTT_1B_T, evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mvaOutput_noHTT_1B_VT_, mvaOutput_noHTT_1B_VT, evtWeight, evtWeightErr);
}
