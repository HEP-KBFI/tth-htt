#include "tthAnalysis/HiggsToTauTau/interface/EvtHistManager_2lss_1tau.h"

#include "tthAnalysis/HiggsToTauTau/interface/histogramAuxFunctions.h"

#include <TMath.h>

EvtHistManager_2lss_1tau::EvtHistManager_2lss_1tau(const edm::ParameterSet& cfg)
  : HistManagerBase(cfg)
{}

void EvtHistManager_2lss_1tau::bookHistograms(TFileDirectory& dir)
{
  histogram_numElectrons_ = book1D(dir, "numElectrons", "numElectrons", 5, -0.5, +4.5);
  histogram_numMuons_ = book1D(dir, "numMuons", "numMuons", 5, -0.5, +4.5);
  histogram_numHadTaus_ = book1D(dir, "numHadTaus", "numHadTaus", 5, -0.5, +4.5);
  histogram_numJets_ = book1D(dir, "numJets", "numJets", 20, -0.5, +19.5);
  histogram_numBJets_loose_ = book1D(dir, "numBJets_loose", "numBJets_loose", 10, -0.5, +9.5);
  histogram_numBJets_medium_ = book1D(dir, "numBJets_medium", "numBJets_medium", 10, -0.5, +9.5);

  histogram_numBJets_loose_vs_numJets_ = book2D(dir, "numBJets_loose_vs_numJets", "numBJets_loose_vs_numJets", 8, -0.5, +7.5, 6, -0.5, +5.5);
  histogram_numBJets_medium_vs_numJets_ = book2D(dir, "numBJets_medium_vs_numJets", "numBJets_medium_vs_numJets", 8, -0.5, +7.5, 6, -0.5, +5.5);

  histogram_mvaOutput_2lss_ttV_ = book1D(dir, "mvaOutput_2lss_ttV", "mvaOutput_2lss_ttV", 40, -1., +1.);
  histogram_mvaOutput_2lss_ttbar_ = book1D(dir, "mvaOutput_2lss_ttbar", "mvaOutput_2lss_ttbar", 40, -1., +1.);
  histogram_mvaDiscr_2lss_ = book1D(dir, "mvaDiscr_2lss", "mvaDiscr_2lss", 6, 0.5, 6.5);

  histogram_mvaOutput_2lss_1tau_ttbar_TMVA_ = book1D(dir, "mvaOutput_2lss_1tau_ttbar_TMVA", "mvaOutput_2lss_1tau_ttbar_TMVA", 20, -1., +1.);
  histogram_mvaOutput_2lss_1tau_ttbar_sklearn_ = book1D(dir, "mvaOutput_2lss_1tau_ttbar_sklearn", "mvaOutput_2lss_1tau_ttbar_sklearn", 20, -1., +1.);

  histogram_mTauTauVis_ = book1D(dir, "mTauTauVis", "mTauTauVis", 40, 0., 200.);

  histogram_memOutput_errorFlag_ = book1D(dir, "memOutput_errorFlag", "memOutput_errorFlag", 2, -0.5, +1.5);
  histogram_memOutput_type_ = book1D(dir, "memOutput_type", "memOutput_type", 4, -1.5, +2.5);
  histogram_memOutput_logWeight_ttH_ = book1D(dir, "memOutput_logWeight_ttH", "memOutput_logWeight_ttH", 100, -20., +20.);
  histogram_memOutput_logWeight_ttZ_ = book1D(dir, "memOutput_logWeight_ttZ", "memOutput_logWeight_ttZ", 100, -20., +20.);
  histogram_memOutput_logWeight_ttZ_Zll_ =book1D(dir, "memOutput_logWeight_ttZ_Zll", "memOutput_logWeight_ttZ_Zll", 100, -20., +20.);
  histogram_memOutput_logWeight_tt_ = book1D(dir, "memOutput_logWeight_tt", "memOutput_logWeight_tt", 100, -20., +20.);
  histogram_memOutput_LR_ = book1D(dir, "memOutput_LR", "memOutput_LR", 40, 0., 1.);
  histogram_mem_logCPUTime_ = book1D(dir, "mem_logCPUTime", "mem_logCPUTime", 400, -20., +20.);
  histogram_mem_logRealTime_ = book1D(dir, "mem_logRealTime", "mem_logRealTime", 400, -20., +20.);

  histogram_EventCounter_ = book1D(dir, "EventCounter", "EventCounter", 1, -0.5, +0.5);
}

double getLogWeight(double weight)
{
  if ( weight > 0. ) return TMath::Log(weight);
  else return -1.e+6;
}

void EvtHistManager_2lss_1tau::fillHistograms(int numElectrons, int numMuons, int numHadTaus, int numJets, int numBJets_loose, int numBJets_medium,
					      double mvaOutput_2lss_ttV, double mvaOutput_2lss_ttbar, double mvaDiscr_2lss, 
					      double mvaOutput_2lss_1tau_ttbar_TMVA, double mvaOutput_2lss_1tau_ttbar_sklearn, 
					      double mTauTauVis1, double mTauTauVis2, 
					      const MEMInterface_2lss_1tau::MEMOutput* memOutput_2lss_1tau, double evtWeight)
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

  fillWithOverFlow(histogram_mvaOutput_2lss_ttV_, mvaOutput_2lss_ttV, evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mvaOutput_2lss_ttbar_, mvaOutput_2lss_ttbar, evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mvaDiscr_2lss_, mvaDiscr_2lss, evtWeight, evtWeightErr);

  fillWithOverFlow(histogram_mvaOutput_2lss_1tau_ttbar_TMVA_, mvaOutput_2lss_1tau_ttbar_TMVA, evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mvaOutput_2lss_1tau_ttbar_sklearn_, mvaOutput_2lss_1tau_ttbar_sklearn, evtWeight, evtWeightErr);

  double mTauTauVisSF = ( mTauTauVis1 > 0. && mTauTauVis2 > 0. ) ? 0.5 : 1.;
  if ( mTauTauVis1 > 0. ) {
    fillWithOverFlow(histogram_mTauTauVis_, mTauTauVis1, mTauTauVisSF*evtWeight, mTauTauVisSF*evtWeightErr);
  }
  if ( mTauTauVis2 > 0. ) {
    fillWithOverFlow(histogram_mTauTauVis_, mTauTauVis2, mTauTauVisSF*evtWeight, mTauTauVisSF*evtWeightErr);
  }

  if ( memOutput_2lss_1tau ) {
    fillWithOverFlow(histogram_memOutput_errorFlag_, memOutput_2lss_1tau->errorFlag_, evtWeight, evtWeightErr);
    if ( memOutput_2lss_1tau->errorFlag_ == 0 ) {
      fillWithOverFlow(histogram_memOutput_type_, memOutput_2lss_1tau->type_, evtWeight, evtWeightErr);
      fillWithOverFlow(histogram_memOutput_logWeight_ttH_, getLogWeight(memOutput_2lss_1tau->weight_ttH_), evtWeight, evtWeightErr);
      fillWithOverFlow(histogram_memOutput_logWeight_ttZ_, getLogWeight(memOutput_2lss_1tau->weight_ttZ_), evtWeight, evtWeightErr);
      fillWithOverFlow(histogram_memOutput_logWeight_ttZ_Zll_, getLogWeight(memOutput_2lss_1tau->weight_ttZ_Zll_), evtWeight, evtWeightErr);
      fillWithOverFlow(histogram_memOutput_logWeight_tt_, getLogWeight(memOutput_2lss_1tau->weight_tt_), evtWeight, evtWeightErr);
      fillWithOverFlow(histogram_memOutput_LR_, memOutput_2lss_1tau->LR_, evtWeight, evtWeightErr);
      fillWithOverFlow(histogram_mem_logCPUTime_, TMath::Log(TMath::Max(1.e-21, memOutput_2lss_1tau->cpuTime_)), evtWeight, evtWeightErr);
      fillWithOverFlow(histogram_mem_logRealTime_, TMath::Log(TMath::Max(1.e-21, memOutput_2lss_1tau->realTime_)), evtWeight, evtWeightErr);
    }
  }

  fillWithOverFlow(histogram_EventCounter_, 0., evtWeight, evtWeightErr);
}
