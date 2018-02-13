#include "tthAnalysis/HiggsToTauTau/interface/EvtHistManager_1l_2tau.h"

#include "tthAnalysis/HiggsToTauTau/interface/histogramAuxFunctions.h"
#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // kEra_2015, kEra_2016
#include "tthAnalysis/HiggsToTauTau/interface/lutAuxFunctions.h" // loadTH2, getSF_from_TH2

#include <iostream> // std::cerr, std::fixed
#include <iomanip> // std::setprecision(), std::setw()
#include <string> // std::string
#include <vector> // std::vector<>
#include <cstdlib> // EXIT_SUCCESS, EXIT_FAILURE
#include <algorithm> // std::sort
#include <fstream> // std::ofstream
#include <assert.h> // assert
#include <TMath.h>

EvtHistManager_1l_2tau::EvtHistManager_1l_2tau(const edm::ParameterSet& cfg)
  : HistManagerBase(cfg)
{}

void EvtHistManager_1l_2tau::bookHistogramsMap(TFileDirectory& dir , int nbinsStart, int nbinsTarget)
{
  std::string label[2]={"HTT","noHTT"};
  for (int ii=0 ; ii < 2 ; ii++ ){
    std::stringstream ss2;
    ss2 <<label[ii]<<"_from"<<nbinsStart<<"_to_"<<nbinsTarget;
    //std::cout<<ss2.str().c_str()<<std::endl;
    TH1* dumb= book1D(dir, ss2.str().c_str(), ss2.str().c_str(), nbinsTarget, -0.5, nbinsTarget-0.5);
    if (ii==0) hist_HTT_2D_.push_back(dumb);
    if (ii==1) hist_noHTT_2D_.push_back(dumb);
  }
}

void EvtHistManager_1l_2tau::fillHistogramsMap(int counter, double evtWeight,
                                                 std::vector<TH2*>* HTT,
                                                 std::vector<TH2*>* noHTT,
                                                 double mvaOutput_ttbar_HTT,
                                                 double mvaOutput_ttbar_noHTT,
                                                 double mvaOutput_ttV_noHTT,
                                                 double mvaOutput_ttV_HTT
                                                 )
{
  double evtWeightErr = 0.;
  fillWithOverFlow(hist_HTT_2D_.at(counter),
    getSF_from_TH2(HTT->at(counter), mvaOutput_ttbar_noHTT, mvaOutput_ttV_noHTT), evtWeight, evtWeightErr);
  fillWithOverFlow(hist_noHTT_2D_.at(counter),
    getSF_from_TH2(noHTT->at(counter), mvaOutput_ttbar_HTT, mvaOutput_ttV_HTT), evtWeight, evtWeightErr);
}

void EvtHistManager_1l_2tau::bookHistograms(TFileDirectory& dir)
{
  histogram_numElectrons_ = book1D(dir, "numElectrons", "numElectrons", 5, -0.5, +4.5);
  histogram_numMuons_ = book1D(dir, "numMuons", "numMuons", 5, -0.5, +4.5);
  histogram_numHadTaus_ = book1D(dir, "numHadTaus", "numHadTaus", 5, -0.5, +4.5);
  histogram_numJets_ = book1D(dir, "numJets", "numJets", 20, -0.5, +19.5);
  histogram_numBJets_loose_ = book1D(dir, "numBJets_loose", "numBJets_loose", 10, -0.5, +9.5);
  histogram_numBJets_medium_ = book1D(dir, "numBJets_medium", "numBJets_medium", 10, -0.5, +9.5);

  histogram_numBJets_loose_vs_numJets_ = book2D(dir, "numBJets_loose_vs_numJets", "numBJets_loose_vs_numJets", 8, -0.5, +7.5, 6, -0.5, +5.5);
  histogram_numBJets_medium_vs_numJets_ = book2D(dir, "numBJets_medium_vs_numJets", "numBJets_medium_vs_numJets", 8, -0.5, +7.5, 6, -0.5, +5.5);

  histogram_mvaOutput_1l_2tau_ttbar_ = book1D(dir, "mvaOutput_1l_2tau_ttbar", "mvaOutput_1l_2tau_ttbar", 600, -1, 1.);
  histogram_mvaOutput_1l_2tau_ttbar_HTTWithKinFit_MVAonly_ = book1D(dir, "mvaOutput_1l_2tau_ttbar_HTTWithKinFit_MVAonly", "mvaOutput_1l_2tau_ttbar_HTTWithKinFit_MVAonly", 600, 0., 1.);
  histogram_mvaOutput_1l_2tau_ttbar_HTTWithKinFit_ = book1D(dir, "mvaOutput_1l_2tau_ttbar_HTTWithKinFit", "mvaOutput_1l_2tau_ttbar_HTTWithKinFit", 600, 0., 1.);
  histogram_mvaOutput_1l_2tau_ttbar_Old_ = book1D(dir, "mvaOutput_1l_2tau_ttbar_Old", "mvaOutput_1l_2tau_ttbar_Old", 600, -1., 1.);
  histogram_mvaOutput_1l_2tau_ttbar_Old_5bins_ = book1D(dir, "mvaOutput_1l_2tau_ttbar_Old_5bins", "mvaOutput_1l_2tau_ttbar_Old_5bins", 5, -1., 1.);

  histogram_mvaOutput_1l_2tau_ttbar_HTTLepID_ = book1D(dir, "mvaOutput_1l_2tau_ttbar_HTTLepID", "mvaOutput_1l_2tau_ttbar_HTTLepID", 600, 0., 1.);
  histogram_mvaOutput_1l_2tau_ttbar_OldVar_ = book1D(dir, "mvaOutput_1l_2tau_ttbar_OldVar", "mvaOutput_1l_2tau_ttbar_OldVar", 600, 0., 1.);
  histogram_mvaOutput_1l_2tau_ttbar_OldVarHTT_ = book1D(dir, "mvaOutput_1l_2tau_ttbar_OldVarHTT", "mvaOutput_1l_2tau_ttbar_OldVarHTT", 600, 0., 1.);

  histogram_mvaOutput_1B_HTT_= book1D(dir, "mvaOutput_1B_HTT", "mvaOutput_1B_HTT", 600, 0., 1.);
  histogram_mvaOutput_1B_HTT_4bins_ = book1D(dir, "mvaOutput_1B_HTT_4bins", "mvaOutput_1B_HTT_4bins", 4, 0., 1.);
  histogram_mvaOutput_1B_HTT_5bins_ = book1D(dir, "mvaOutput_1B_HTT_5bins", "mvaOutput_1B_HTT_5bins", 5, 0., 1.);
  histogram_mvaOutput_1B_HTT_6bins_ = book1D(dir, "mvaOutput_1B_HTT_6bins", "mvaOutput_1B_HTT_6bins", 6, 0., 1.);
  histogram_mvaOutput_1B_HTT_7bins_ = book1D(dir, "mvaOutput_1B_HTT_7bins", "mvaOutput_1B_HTT_7bins", 7, 0., 1.);
  histogram_mvaOutput_1B_HTT_8bins_ = book1D(dir, "mvaOutput_1B_HTT_8bins", "mvaOutput_1B_HTT_8bins", 8, 0., 1.);
  histogram_mvaOutput_1B_HTT_9bins_ = book1D(dir, "mvaOutput_1B_HTT_9bins", "mvaOutput_1B_HTT_9bins", 9, 0., 1.);
  histogram_mvaOutput_1B_HTT_10bins_ = book1D(dir, "mvaOutput_1B_HTT_10bins", "mvaOutput_1B_HTT_10bins", 10, 0., 1.);
  histogram_mvaOutput_1B_HTT_11bins_ = book1D(dir, "mvaOutput_1B_HTT_11bins", "mvaOutput_1B_HTT_11bins", 11, 0., 1.);
  histogram_mvaOutput_1B_HTT_12bins_ = book1D(dir, "mvaOutput_1B_HTT_12bins", "mvaOutput_1B_HTT_12bins", 12, 0., 1.);
  histogram_mvaOutput_1B_HTT_14bins_ = book1D(dir, "mvaOutput_1B_HTT_14bins", "mvaOutput_1B_HTT_14bins", 14, 0., 1.);


  histogram_mvaOutput_1B_noHTT_= book1D(dir, "mvaOutput_1B_noHTT", "mvaOutput_1B_noHTT", 600, 0., 1.);
  histogram_mvaOutput_1B_noHTT_4bins_ = book1D(dir, "mvaOutput_1B_noHTT_4bins", "mvaOutput_1B_noHTT_4bins", 4, 0., 1.);
  histogram_mvaOutput_1B_noHTT_5bins_ = book1D(dir, "mvaOutput_1B_noHTT_5bins", "mvaOutput_1B_noHTT_5bins", 5, 0., 1.);
  histogram_mvaOutput_1B_noHTT_6bins_ = book1D(dir, "mvaOutput_1B_noHTT_6bins", "mvaOutput_1B_noHTT_6bins", 6, 0., 1.);
  histogram_mvaOutput_1B_noHTT_7bins_ = book1D(dir, "mvaOutput_1B_noHTT_7bins", "mvaOutput_1B_noHTT_7bins", 7, 0., 1.);
  histogram_mvaOutput_1B_noHTT_8bins_ = book1D(dir, "mvaOutput_1B_noHTT_8bins", "mvaOutput_1B_noHTT_8bins", 8, 0., 1.);
  histogram_mvaOutput_1B_noHTT_9bins_ = book1D(dir, "mvaOutput_1B_noHTT_9bins", "mvaOutput_1B_noHTT_9bins", 9, 0., 1.);
  histogram_mvaOutput_1B_noHTT_10bins_ = book1D(dir, "mvaOutput_1B_noHTT_10bins", "mvaOutput_1B_noHTT_10bins", 10, 0., 1.);
  histogram_mvaOutput_1B_noHTT_11bins_ = book1D(dir, "mvaOutput_1B_noHTT_11bins", "mvaOutput_1B_noHTT_11bins", 11, 0., 1.);
  histogram_mvaOutput_1B_noHTT_15bins_ = book1D(dir, "mvaOutput_1B_noHTT_15bins", "mvaOutput_1B_noHTT_15bins", 15, 0., 1.);
  histogram_mvaOutput_1B_noHTT_16bins_ = book1D(dir, "mvaOutput_1B_noHTT_16bins", "mvaOutput_1B_noHTT_16bins", 16, 0., 1.);

  histogram_mvaOutput_1l_2tau_ttV_ = book1D(dir, "mvaOutput_1l_2tau_ttV", "mvaOutput_1l_2tau_ttV", 20, -1., +1.);
  histogram_mvaDiscr_1l_2tau_ = book1D(dir, "mvaDiscr_1l_2tau", "mvaDiscr_1l_2tau", 10, 0.5, 10.5);

  histogram_mTauTauVis_ = book1D(dir, "mTauTauVis", "mTauTauVis", 20, 0., 200.);

  histogram_mvaOutput_ttbar_HTT_ = book1D(dir, "mvaOutput_ttbar_HTT", "mvaOutput_ttbar_HTT", 600, 0., 1.);
  histogram_mvaOutput_ttbar_HTT_4bins_ = book1D(dir, "mvaOutput_ttbar_HTT_4bins", "mvaOutput_ttbar_HTT_4bins", 4, 0., 1.);
  histogram_mvaOutput_ttbar_HTT_5bins_ = book1D(dir, "mvaOutput_ttbar_HTT_5bins", "mvaOutput_ttbar_HTT_5bins", 5, 0., 1.);
  histogram_mvaOutput_ttbar_HTT_6bins_ = book1D(dir, "mvaOutput_ttbar_HTT_6bins", "mvaOutput_ttbar_HTT_6bins", 6, 0., 1.);
  histogram_mvaOutput_ttbar_HTT_7bins_ = book1D(dir, "mvaOutput_ttbar_HTT_7bins", "mvaOutput_ttbar_HTT_7bins", 7, 0., 1.);
  histogram_mvaOutput_ttbar_HTT_8bins_ = book1D(dir, "mvaOutput_ttbar_HTT_8bins", "mvaOutput_ttbar_HTT_8bins", 8, 0., 1.);
  histogram_mvaOutput_ttbar_HTT_9bins_ = book1D(dir, "mvaOutput_ttbar_HTT_9bins", "mvaOutput_ttbar_HTT_9bins", 9, 0., 1.);
  histogram_mvaOutput_ttbar_HTT_10bins_ = book1D(dir, "mvaOutput_ttbar_HTT_10bins", "mvaOutput_ttbar_HTT_10bins", 10, 0., 1.);
  histogram_mvaOutput_ttbar_HTT_11bins_ = book1D(dir, "mvaOutput_ttbar_HTT_11bins", "mvaOutput_ttbar_HTT_11bins", 11, 0., 1.);
  histogram_mvaOutput_ttbar_HTT_12bins_ = book1D(dir, "mvaOutput_ttbar_HTT_12bins", "mvaOutput_ttbar_HTT_12bins", 12, 0., 1.);
  histogram_mvaOutput_ttbar_HTT_14bins_ = book1D(dir, "mvaOutput_ttbar_HTT_14bins", "mvaOutput_ttbar_HTT_14bins", 14, 0., 1.);

  histogram_mvaOutput_ttbar_noHTT_ = book1D(dir, "mvaOutput_ttbar_noHTT", "mvaOutput_ttbar_noHTT", 600, 0., 1.);
  histogram_mvaOutput_ttbar_noHTT_4bins_ = book1D(dir, "mvaOutput_ttbar_noHTT_4bins", "mvaOutput_ttbar_noHTT_4bins", 4, 0., 1.);
  histogram_mvaOutput_ttbar_noHTT_5bins_ = book1D(dir, "mvaOutput_ttbar_noHTT_5bins", "mvaOutput_ttbar_noHTT_5bins", 5, 0., 1.);
  histogram_mvaOutput_ttbar_noHTT_6bins_ = book1D(dir, "mvaOutput_ttbar_noHTT_6bins", "mvaOutput_ttbar_noHTT_6bins", 6, 0., 1.);
  histogram_mvaOutput_ttbar_noHTT_7bins_ = book1D(dir, "mvaOutput_ttbar_noHTT_7bins", "mvaOutput_ttbar_noHTT_7bins", 7, 0., 1.);
  histogram_mvaOutput_ttbar_noHTT_8bins_ = book1D(dir, "mvaOutput_ttbar_noHTT_8bins", "mvaOutput_ttbar_noHTT_8bins", 8, 0., 1.);
  histogram_mvaOutput_ttbar_noHTT_9bins_ = book1D(dir, "mvaOutput_ttbar_noHTT_9bins", "mvaOutput_ttbar_noHTT_9bins", 9, 0., 1.);
  histogram_mvaOutput_ttbar_noHTT_10bins_ = book1D(dir, "mvaOutput_ttbar_noHTT_10bins", "mvaOutput_ttbar_noHTT_10bins", 10, 0., 1.);
  histogram_mvaOutput_ttbar_noHTT_11bins_ = book1D(dir, "mvaOutput_ttbar_noHTT_11bins", "mvaOutput_ttbar_noHTT_11bins", 11, 0., 1.);
  histogram_mvaOutput_ttbar_noHTT_15bins_ = book1D(dir, "mvaOutput_ttbar_noHTT_15bins", "mvaOutput_ttbar_noHTT_15bins", 15, 0., 1.);
  histogram_mvaOutput_ttbar_noHTT_16bins_ = book1D(dir, "mvaOutput_ttbar_noHTT_16bins", "mvaOutput_ttbar_noHTT_16bins", 16, 0., 1.);

  ////////////////////////
  histogram_mvaOutput_sum_HTT_ = book1D(dir, "mvaOutput_sum_HTT", "mvaOutput_sum_HTT", 600, 0., 1.);
  histogram_mvaOutput_sum_HTT_4bins_ = book1D(dir, "mvaOutput_sum_HTT_4bins", "mvaOutput_sum_HTT_4bins", 4, 0., 1.);
  histogram_mvaOutput_sum_HTT_5bins_ = book1D(dir, "mvaOutput_sum_HTT_5bins", "mvaOutput_sum_HTT_5bins", 5, 0., 1.);
  histogram_mvaOutput_sum_HTT_6bins_ = book1D(dir, "mvaOutput_sum_HTT_6bins", "mvaOutput_sum_HTT_6bins", 6, 0., 1.);
  histogram_mvaOutput_sum_HTT_7bins_ = book1D(dir, "mvaOutput_sum_HTT_7bins", "mvaOutput_sum_HTT_7bins", 7, 0., 1.);
  histogram_mvaOutput_sum_HTT_8bins_ = book1D(dir, "mvaOutput_sum_HTT_8bins", "mvaOutput_sum_HTT_8bins", 8, 0., 1.);
  histogram_mvaOutput_sum_HTT_9bins_ = book1D(dir, "mvaOutput_sum_HTT_9bins", "mvaOutput_sum_HTT_9bins", 9, 0., 1.);
  histogram_mvaOutput_sum_HTT_10bins_ = book1D(dir, "mvaOutput_sum_HTT_10bins", "mvaOutput_sum_HTT_10bins", 10, 0., 1.);
  histogram_mvaOutput_sum_HTT_11bins_ = book1D(dir, "mvaOutput_sum_HTT_11bins", "mvaOutput_sum_HTT_11bins", 11, 0., 1.);
  histogram_mvaOutput_sum_HTT_12bins_ = book1D(dir, "mvaOutput_sum_HTT_12bins", "mvaOutput_sum_HTT_12bins", 12, 0., 1.);
  histogram_mvaOutput_sum_HTT_14bins_ = book1D(dir, "mvaOutput_sum_HTT_14bins", "mvaOutput_sum_HTT_14bins", 14, 0., 1.);

  histogram_mvaOutput_sum_noHTT_ = book1D(dir, "mvaOutput_sum_noHTT", "mvaOutput_sum_noHTT", 600, 0., 1.);
  histogram_mvaOutput_sum_noHTT_4bins_ = book1D(dir, "mvaOutput_sum_noHTT_4bins", "mvaOutput_sum_noHTT_4bins", 4, 0., 1.);
  histogram_mvaOutput_sum_noHTT_5bins_ = book1D(dir, "mvaOutput_sum_noHTT_5bins", "mvaOutput_sum_noHTT_5bins", 5, 0., 1.);
  histogram_mvaOutput_sum_noHTT_6bins_ = book1D(dir, "mvaOutput_sum_noHTT_6bins", "mvaOutput_sum_noHTT_6bins", 6, 0., 1.);
  histogram_mvaOutput_sum_noHTT_7bins_ = book1D(dir, "mvaOutput_sum_noHTT_7bins", "mvaOutput_sum_noHTT_7bins", 7, 0., 1.);
  histogram_mvaOutput_sum_noHTT_8bins_ = book1D(dir, "mvaOutput_sum_noHTT_8bins", "mvaOutput_sum_noHTT_8bins", 8, 0., 1.);
  histogram_mvaOutput_sum_noHTT_9bins_ = book1D(dir, "mvaOutput_sum_noHTT_9bins", "mvaOutput_sum_noHTT_9bins", 9, 0., 1.);
  histogram_mvaOutput_sum_noHTT_10bins_ = book1D(dir, "mvaOutput_sum_noHTT_10bins", "mvaOutput_sum_noHTT_10bins", 10, 0., 1.);
  histogram_mvaOutput_sum_noHTT_11bins_ = book1D(dir, "mvaOutput_sum_noHTT_11bins", "mvaOutput_sum_noHTT_11bins", 11, 0., 1.);
  histogram_mvaOutput_sum_noHTT_15bins_ = book1D(dir, "mvaOutput_sum_noHTT_15bins", "mvaOutput_sum_noHTT_15bins", 15, 0., 1.);
  histogram_mvaOutput_sum_noHTT_16bins_ = book1D(dir, "mvaOutput_sum_noHTT_16bins", "mvaOutput_sum_noHTT_16bins", 16, 0., 1.);

  /////////////////////////

  histogram_mvaOutput_ttV_noHTT_ = book1D(dir, "mvaOutput_ttV_noHTT", "mvaOutput_ttV_noHTT", 600, 0., 1.);
  histogram_mvaOutput_ttV_HTT_ = book1D(dir, "mvaOutput_ttV_HTT", "mvaOutput_ttV_HTT", 600, 0., 1.);
  histogram_mvaOutput_ttbar_OldVar_ = book1D(dir, "mvaOutput_ttbar_OldVar", "mvaOutput_ttbar_OldVar", 600, 0., 1.);

  histogram_EventCounter_ = book1D(dir, "EventCounter", "EventCounter", 1, -0.5, +0.5);
}

void EvtHistManager_1l_2tau::fillHistograms(int numElectrons, int numMuons, int numHadTaus, int numJets, int numBJets_loose, int numBJets_medium,
  double mvaOutput_1l_2tau_ttbar,
  double mvaOutput_1l_2tau_ttbar_HTTWithKinFit_MVAonly,
  double mvaOutput_1l_2tau_ttbar_HTTWithKinFit,
  double mvaOutput_1l_2tau_ttbar_Old,
  double mvaOutput_1l_2tau_ttbar_HTTLepID,
  double mvaOutput_1l_2tau_ttbar_OldVar,
  double mvaOutput_1l_2tau_ttbar_OldVarHTT,
  double mvaOutput_1l_2tau_ttV, double mvaDiscr_1l_2tau, double mTauTauVis,
  //////////////
  double mvaOutput_sum_HTT,
  double mvaOutput_sum_noHTT,
  /////////////
  double mvaOutput_ttbar_HTT,
  double mvaOutput_ttbar_noHTT,
  double mvaOutput_ttV_noHTT,
  double mvaOutput_ttV_HTT,
  double mvaOutput_ttbar_OldVar,
  double mvaOutput_1B_HTT,
  double mvaOutput_1B_noHTT,
  /////////////
  double evtWeight)
{
  double evtWeightErr = 0.;

  fillWithOverFlow(histogram_mvaOutput_ttbar_HTT_, mvaOutput_ttbar_HTT, evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mvaOutput_ttbar_HTT_4bins_, mvaOutput_ttbar_HTT, evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mvaOutput_ttbar_HTT_5bins_, mvaOutput_ttbar_HTT, evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mvaOutput_ttbar_HTT_6bins_, mvaOutput_ttbar_HTT, evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mvaOutput_ttbar_HTT_7bins_, mvaOutput_ttbar_HTT, evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mvaOutput_ttbar_HTT_8bins_, mvaOutput_ttbar_HTT, evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mvaOutput_ttbar_HTT_9bins_, mvaOutput_ttbar_HTT, evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mvaOutput_ttbar_HTT_10bins_, mvaOutput_ttbar_HTT, evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mvaOutput_ttbar_HTT_11bins_, mvaOutput_ttbar_HTT, evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mvaOutput_ttbar_HTT_12bins_, mvaOutput_ttbar_HTT, evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mvaOutput_ttbar_HTT_14bins_, mvaOutput_ttbar_HTT, evtWeight, evtWeightErr);

  fillWithOverFlow(histogram_mvaOutput_ttbar_noHTT_, mvaOutput_ttbar_noHTT, evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mvaOutput_ttbar_noHTT_4bins_, mvaOutput_ttbar_noHTT, evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mvaOutput_ttbar_noHTT_5bins_, mvaOutput_ttbar_noHTT, evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mvaOutput_ttbar_noHTT_6bins_, mvaOutput_ttbar_noHTT, evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mvaOutput_ttbar_noHTT_7bins_, mvaOutput_ttbar_noHTT, evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mvaOutput_ttbar_noHTT_8bins_, mvaOutput_ttbar_noHTT, evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mvaOutput_ttbar_noHTT_9bins_, mvaOutput_ttbar_noHTT, evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mvaOutput_ttbar_noHTT_10bins_, mvaOutput_ttbar_noHTT, evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mvaOutput_ttbar_noHTT_11bins_, mvaOutput_ttbar_noHTT, evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mvaOutput_ttbar_noHTT_15bins_, mvaOutput_ttbar_noHTT, evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mvaOutput_ttbar_noHTT_16bins_, mvaOutput_ttbar_noHTT, evtWeight, evtWeightErr);

  ////////////////////////////////////////////////////////////////////
  fillWithOverFlow(histogram_mvaOutput_sum_HTT_, mvaOutput_sum_HTT, evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mvaOutput_sum_HTT_4bins_, mvaOutput_sum_HTT, evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mvaOutput_sum_HTT_5bins_, mvaOutput_sum_HTT, evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mvaOutput_sum_HTT_6bins_, mvaOutput_sum_HTT, evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mvaOutput_sum_HTT_7bins_, mvaOutput_sum_HTT, evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mvaOutput_sum_HTT_8bins_, mvaOutput_sum_HTT, evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mvaOutput_sum_HTT_9bins_, mvaOutput_sum_HTT, evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mvaOutput_sum_HTT_10bins_, mvaOutput_sum_HTT, evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mvaOutput_sum_HTT_11bins_, mvaOutput_sum_HTT, evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mvaOutput_sum_HTT_12bins_, mvaOutput_sum_HTT, evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mvaOutput_sum_HTT_14bins_, mvaOutput_sum_HTT, evtWeight, evtWeightErr);

  fillWithOverFlow(histogram_mvaOutput_sum_noHTT_, mvaOutput_sum_noHTT, evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mvaOutput_sum_noHTT_4bins_, mvaOutput_sum_noHTT, evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mvaOutput_sum_noHTT_5bins_, mvaOutput_sum_noHTT, evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mvaOutput_sum_noHTT_6bins_, mvaOutput_sum_noHTT, evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mvaOutput_sum_noHTT_7bins_, mvaOutput_sum_noHTT, evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mvaOutput_sum_noHTT_8bins_, mvaOutput_sum_noHTT, evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mvaOutput_sum_noHTT_9bins_, mvaOutput_sum_noHTT, evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mvaOutput_sum_noHTT_10bins_, mvaOutput_sum_noHTT, evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mvaOutput_sum_noHTT_11bins_, mvaOutput_sum_noHTT, evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mvaOutput_sum_noHTT_15bins_, mvaOutput_sum_noHTT, evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mvaOutput_sum_noHTT_16bins_, mvaOutput_sum_noHTT, evtWeight, evtWeightErr);

  ////////////////////////////////////////////////////////////////////

  fillWithOverFlow(histogram_mvaOutput_ttV_noHTT_, mvaOutput_ttV_noHTT, evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mvaOutput_ttV_HTT_, mvaOutput_ttV_HTT, evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mvaOutput_ttbar_OldVar_, mvaOutput_ttbar_OldVar, evtWeight, evtWeightErr);

  fillWithOverFlow(histogram_mvaOutput_1B_HTT_, mvaOutput_1B_HTT, evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mvaOutput_1B_HTT_4bins_, mvaOutput_1B_HTT, evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mvaOutput_1B_HTT_5bins_, mvaOutput_1B_HTT, evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mvaOutput_1B_HTT_6bins_, mvaOutput_1B_HTT, evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mvaOutput_1B_HTT_7bins_, mvaOutput_1B_HTT, evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mvaOutput_1B_HTT_8bins_, mvaOutput_1B_HTT, evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mvaOutput_1B_HTT_9bins_, mvaOutput_1B_HTT, evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mvaOutput_1B_HTT_10bins_, mvaOutput_1B_HTT, evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mvaOutput_1B_HTT_11bins_, mvaOutput_1B_HTT, evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mvaOutput_1B_HTT_12bins_, mvaOutput_1B_HTT, evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mvaOutput_1B_HTT_14bins_, mvaOutput_1B_HTT, evtWeight, evtWeightErr);

  fillWithOverFlow(histogram_mvaOutput_1B_noHTT_, mvaOutput_1B_noHTT, evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mvaOutput_1B_noHTT_4bins_, mvaOutput_1B_noHTT, evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mvaOutput_1B_noHTT_5bins_, mvaOutput_1B_noHTT, evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mvaOutput_1B_noHTT_6bins_, mvaOutput_1B_noHTT, evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mvaOutput_1B_noHTT_7bins_, mvaOutput_1B_noHTT, evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mvaOutput_1B_noHTT_8bins_, mvaOutput_1B_noHTT, evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mvaOutput_1B_noHTT_9bins_, mvaOutput_1B_noHTT, evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mvaOutput_1B_noHTT_10bins_, mvaOutput_1B_noHTT, evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mvaOutput_1B_noHTT_11bins_, mvaOutput_1B_noHTT, evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mvaOutput_1B_noHTT_15bins_, mvaOutput_1B_noHTT, evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mvaOutput_1B_noHTT_16bins_, mvaOutput_1B_noHTT, evtWeight, evtWeightErr);


  fillWithOverFlow(histogram_numElectrons_, numElectrons, evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_numMuons_, numMuons, evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_numHadTaus_, numHadTaus, evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_numJets_, numJets, evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_numBJets_loose_, numBJets_loose, evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_numBJets_medium_, numBJets_medium, evtWeight, evtWeightErr);

  fillWithOverFlow2d(histogram_numBJets_loose_vs_numJets_, numJets, numBJets_loose, evtWeight, evtWeightErr);
  fillWithOverFlow2d(histogram_numBJets_medium_vs_numJets_, numJets, numBJets_medium, evtWeight, evtWeightErr);

  fillWithOverFlow(histogram_mvaOutput_1l_2tau_ttbar_, mvaOutput_1l_2tau_ttbar, evtWeight, evtWeightErr);

  fillWithOverFlow(histogram_mvaOutput_1l_2tau_ttbar_Old_, mvaOutput_1l_2tau_ttbar_Old, evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mvaOutput_1l_2tau_ttbar_Old_5bins_, mvaOutput_1l_2tau_ttbar_Old, evtWeight, evtWeightErr);

  fillWithOverFlow(histogram_mvaOutput_1l_2tau_ttbar_HTTWithKinFit_MVAonly_, mvaOutput_1l_2tau_ttbar_HTTWithKinFit_MVAonly, evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mvaOutput_1l_2tau_ttbar_HTTWithKinFit_, mvaOutput_1l_2tau_ttbar_HTTWithKinFit, evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mvaOutput_1l_2tau_ttbar_HTTLepID_, mvaOutput_1l_2tau_ttbar_HTTLepID, evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mvaOutput_1l_2tau_ttbar_OldVar_, mvaOutput_1l_2tau_ttbar_OldVar, evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mvaOutput_1l_2tau_ttbar_OldVarHTT_, mvaOutput_1l_2tau_ttbar_OldVarHTT, evtWeight, evtWeightErr);

  fillWithOverFlow(histogram_mvaOutput_1l_2tau_ttV_, mvaOutput_1l_2tau_ttV, evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mvaDiscr_1l_2tau_, mvaDiscr_1l_2tau, evtWeight, evtWeightErr);

  fillWithOverFlow(histogram_mTauTauVis_, mTauTauVis, evtWeight, evtWeightErr);

  fillWithOverFlow(histogram_EventCounter_, 0., evtWeight, evtWeightErr);
}
