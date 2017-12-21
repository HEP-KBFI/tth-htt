#include "tthAnalysis/HiggsToTauTau/interface/EvtHistManager_2lss_1tau.h"

#include "tthAnalysis/HiggsToTauTau/interface/histogramAuxFunctions.h" // fillWithOverFlow, fillWithOverFlow2d, getLogWeight
#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // kEra_2015, kEra_2016

#include <iostream> // std::cerr, std::fixed
#include <iomanip> // std::setprecision(), std::setw()
#include <string> // std::string
#include <vector> // std::vector<>
#include <cstdlib> // EXIT_SUCCESS, EXIT_FAILURE
#include <algorithm> // std::sort
#include <fstream> // std::ofstream
#include <assert.h> // assert

EvtHistManager_2lss_1tau::EvtHistManager_2lss_1tau(const edm::ParameterSet& cfg)
  : HistManagerBase(cfg)
{
  std::string era_string = cfg.getParameter<std::string>("era");
  era_ = -1;
  if      ( era_string == "2015" ) era_ = kEra_2015;
  else if ( era_string == "2016" ) era_ = kEra_2016;
  else throw cms::Exception("EvtHistManager_2lss_1tau")
    << "Invalid Configuration parameter 'era' = " << era_string << " !!\n";
}

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
  if      ( era_ == kEra_2015 ) histogram_mvaDiscr_2lss_ = book1D(dir, "mvaDiscr_2lss", "mvaDiscr_2lss", 6, 0.5, 6.5);
  else if ( era_ == kEra_2016 ) histogram_mvaDiscr_2lss_ = book1D(dir, "mvaDiscr_2lss", "mvaDiscr_2lss", 7, 0.5, 7.5);
  else assert(0);

  histogram_mvaOutput_2lss_1tau_ttV_ = book1D(dir, "mvaOutput_2lss_1tau_ttV", "mvaOutput_2lss_1tau_ttV", 20, -1., +1.);
  histogram_mvaOutput_2lss_1tau_ttbar_ = book1D(dir, "mvaOutput_2lss_1tau_ttbar", "mvaOutput_2lss_1tau_ttbar", 20, -1., +1.);
  histogram_mvaDiscr_2lss_1tau_ = book1D(dir, "mvaDiscr_2lss_1tau", "mvaDiscr_2lss_1tau", 8, 0.5, 8.5);
  histogram_mvaOutput_2lss_1tau_ttV_wMEM_ = book1D(dir, "mvaOutput_2lss_1tau_ttV_wMEM", "mvaOutput_2lss_1tau_ttV_wMEM", 20, -1., +1.);
  histogram_mvaOutput_2lss_1tau_ttbar_wMEM_ = book1D(dir, "mvaOutput_2lss_1tau_ttbar_wMEM", "mvaOutput_2lss_1tau_ttbar_wMEM", 20, -1., +1.);
  histogram_mvaDiscr_2lss_1tau_wMEM_ = book1D(dir, "mvaDiscr_2lss_1tau_wMEM", "mvaDiscr_2lss_1tau_wMEM", 8, 0.5, 8.5);

  histogram_mvaOutput_Hj_tagger_ = book1D(dir, "mvaOutput_Hj_tagger", "mvaOutput_Hj_tagger", 20, -1., +1.);
  histogram_mvaOutput_Hjj_tagger_ = book1D(dir, "mvaOutput_Hjj_tagger", "mvaOutput_Hjj_tagger", 20, -1., +1.);

  histogram_mTauTauVis_ = book1D(dir, "mTauTauVis", "mTauTauVis", 20, 0., 200.);

  histogram_memOutput_isValid_ = book1D(dir, "memOutput_isValid", "memOutput_isValid", 3, -1.5, +1.5);
  histogram_memOutput_errorFlag_ = book1D(dir, "memOutput_errorFlag", "memOutput_errorFlag", 2, -0.5, +1.5);
  histogram_memOutput_type_ = book1D(dir, "memOutput_type", "memOutput_type", 4, -1.5, +2.5);
  histogram_memOutput_logWeight_ttH_ = book1D(dir, "memOutput_logWeight_ttH", "memOutput_logWeight_ttH", 100, -20., +20.);
  histogram_memOutput_logWeight_ttZ_ = book1D(dir, "memOutput_logWeight_ttZ", "memOutput_logWeight_ttZ", 100, -20., +20.);
  histogram_memOutput_logWeight_ttZ_Zll_ =book1D(dir, "memOutput_logWeight_ttZ_Zll", "memOutput_logWeight_ttZ_Zll", 100, -20., +20.);
  histogram_memOutput_logWeight_tt_ = book1D(dir, "memOutput_logWeight_tt", "memOutput_logWeight_tt", 100, -20., +20.);
  histogram_memOutput_LR_ = book1D(dir, "memOutput_LR", "memOutput_LR", 40, 0., 1.);
  histogram_memOutput_LR_type0_ = book1D(dir, "memOutput_LR_type0", "memOutput_LR_type0", 40, 0., 1.);
  histogram_memOutput_LR_type1_ = book1D(dir, "memOutput_LR_type1", "memOutput_LR_type1", 40, 0., 1.);
  histogram_memDiscr_ = book1D(dir, "memDiscr", "memDiscr", 8, 0.5, 8.5);
  histogram_memDiscr_type0_ = book1D(dir, "memDiscr_type0", "memDiscr_type0", 8, 0.5, 8.5);
  histogram_memDiscr_type1_ = book1D(dir, "memDiscr_type1", "memDiscr_type1", 8, 0.5, 8.5);
  histogram_mem_logCPUTime_ = book1D(dir, "mem_logCPUTime", "mem_logCPUTime", 400, -20., +20.);
  histogram_mem_logRealTime_ = book1D(dir, "mem_logRealTime", "mem_logRealTime", 400, -20., +20.);

  histogram_EventCounter_ = book1D(dir, "EventCounter", "EventCounter", 1, -0.5, +0.5);

  histogram_mvaOutput_2lss_oldVar_tt_= book1D(dir, "mvaOutput_2lss_oldVar_tt", "mvaOutput_2lss_oldVar_tt", 600, 0., +1.);
  histogram_mvaOutput_2lss_oldVar_ttV_= book1D(dir, "mvaOutput_2lss_oldVar_ttV", "mvaOutput_2lss_oldVar_ttV",    600, 0., +1.);
  histogram_mvaOutput_2lss_HTT_tt_= book1D(dir, "mvaOutput_2lss_HTT_tt", "mvaOutput_2lss_HTT_tt",          600, 0., +1.);
  histogram_mvaOutput_2lss_noHTT_tt_= book1D(dir, "mvaOutput_2lss_noHTT_tt", "mvaOutput_2lss_noHTT_tt",    600, 0., +1.);
  histogram_mvaOutput_2lss_noHTT_ttV_= book1D(dir, "mvaOutput_2lss_noHTT_ttV", "mvaOutput_2lss_noHTT_ttV", 600, 0., +1.);
  histogram_mvaOutput_2lss_HTT_LepID_tt_= book1D(dir, "mvaOutput_2lss_HTT_LepID_tt", "mvaOutput_2lss_HTT_LepID_tt", 600, 0., +1.);

  hist_oldVar_from20_to_12_ = book1D(dir, "oldVar_from20_to_12", "oldVar_from20_to_12", 12, -0.5, 12+0.5);
  hist_oldVar_from20_to_7_ = book1D(dir, "oldVar_from20_to_7", "oldVar_from20_to_7", 7, -0.5, 7+0.5);

  for (int nbinsStartN=0 ; nbinsStartN<3 ; nbinsStartN++ ) {
    for (int nbinsTargetN=0 ; nbinsTargetN<9 ; nbinsTargetN++ ) {
      //std::cout<<"internal declaring histos "<<nbinsStartN<<" "<<nbinsTargetN
      //    << " HTT_from"<<nbinsStart[nbinsStartN]<<"_to_"<<nbinsTarget[nbinsTargetN]<<std::endl;
      std::stringstream ss2;
      ss2 << "HTT_from"<<nbinsStart[nbinsStartN]<<"_to_"<<nbinsTarget[nbinsTargetN];
      hist_HTT_2D_[nbinsStartN][nbinsTargetN]=book1D(dir, ss2.str(), ss2.str(),
                                                    nbinsTarget[nbinsTargetN],
                                                    -0.5, nbinsTarget[nbinsTargetN]+0.5);
      std::stringstream ss3;
      ss3 << "noHTT_from"<<nbinsStart[nbinsStartN]<<"_to_"<<nbinsTarget[nbinsTargetN];
      hist_noHTT_2D_[nbinsStartN][nbinsTargetN]=book1D(dir, ss3.str(), ss3.str(),
                                                    nbinsTarget[nbinsTargetN],
                                                    -0.5, nbinsTarget[nbinsTargetN]+0.5);
    }
  }

}

void EvtHistManager_2lss_1tau::fillHistograms(
                int numElectrons, int numMuons, int numHadTaus, int numJets, int numBJets_loose, int numBJets_medium,
					      double mvaOutput_2lss_ttV, double mvaOutput_2lss_ttbar, double mvaDiscr_2lss,
					      double mvaOutput_2lss_1tau_ttV, double mvaOutput_2lss_1tau_ttbar, double mvaDiscr_2lss_1tau,
					      double mvaOutput_2lss_1tau_ttV_wMEM, double mvaOutput_2lss_1tau_ttbar_wMEM, double mvaDiscr_2lss_1tau_wMEM,
					      double mvaOutput_Hj_tagger, double mvaOutput_Hjj_tagger,
					      double mTauTauVis1, double mTauTauVis2,
					      const MEMOutput_2lss_1tau* memOutput_2lss_1tau, double memDiscr, double evtWeight,
                double mvaOutput_2lss_oldVar_tt,
                double mvaOutput_2lss_oldVar_ttV,
                double mvaOutput_2lss_HTT_tt,
                double mvaOutput_2lss_noHTT_tt,
                double mvaOutput_2lss_noHTT_ttV,
                double mvaOutput_2lss_HTT_LepID_tt,
                double oldVar_from20_to_12,
                double oldVar_from20_to_7,
                Double_t  (&HTT_2D)[3][9],
                Double_t  (&noHTT_2D)[3][9]
              )
{
  //std::vector<std::vector<Double_t>>& HTT_2D,
  //std::vector<std::vector<Double_t>>& noHTT_2D
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

  fillWithOverFlow(histogram_mvaOutput_2lss_1tau_ttV_, mvaOutput_2lss_1tau_ttV, evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mvaOutput_2lss_1tau_ttbar_, mvaOutput_2lss_1tau_ttbar, evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mvaDiscr_2lss_1tau_, mvaDiscr_2lss_1tau, evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mvaOutput_2lss_1tau_ttV_wMEM_, mvaOutput_2lss_1tau_ttV_wMEM, evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mvaOutput_2lss_1tau_ttbar_wMEM_, mvaOutput_2lss_1tau_ttbar_wMEM, evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mvaDiscr_2lss_1tau_wMEM_, mvaDiscr_2lss_1tau_wMEM, evtWeight, evtWeightErr);

  fillWithOverFlow(histogram_mvaOutput_Hj_tagger_, mvaOutput_Hj_tagger, evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mvaOutput_Hjj_tagger_, mvaOutput_Hjj_tagger, evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mvaOutput_2lss_oldVar_tt_, mvaOutput_2lss_oldVar_tt, evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mvaOutput_2lss_oldVar_ttV_, mvaOutput_2lss_oldVar_ttV, evtWeight, evtWeightErr);

  fillWithOverFlow(histogram_mvaOutput_2lss_HTT_tt_, mvaOutput_2lss_HTT_tt, evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mvaOutput_2lss_noHTT_tt_, mvaOutput_2lss_noHTT_tt, evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mvaOutput_2lss_noHTT_ttV_, mvaOutput_2lss_noHTT_ttV, evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mvaOutput_2lss_HTT_LepID_tt_, mvaOutput_2lss_HTT_LepID_tt, evtWeight, evtWeightErr);

  fillWithOverFlow(hist_oldVar_from20_to_12_, oldVar_from20_to_12, evtWeight, evtWeightErr);
  fillWithOverFlow(hist_oldVar_from20_to_7_, oldVar_from20_to_7, evtWeight, evtWeightErr);  

  for (int nbinsStartN=0 ; nbinsStartN<3 ; nbinsStartN++ ) {
    for (int nbinsTargetN=0 ; nbinsTargetN<9 ; nbinsTargetN++ ) {
      //std::cout<<"internal filling histos "<<HTT_2D[nbinsStartN][nbinsTargetN]<<" "<< noHTT_2D[nbinsStartN][nbinsTargetN]<<std::endl;
      fillWithOverFlow(hist_HTT_2D_[nbinsStartN][nbinsTargetN], HTT_2D[nbinsStartN][nbinsTargetN], evtWeight, evtWeightErr);
      fillWithOverFlow(hist_noHTT_2D_[nbinsStartN][nbinsTargetN], noHTT_2D[nbinsStartN][nbinsTargetN], evtWeight, evtWeightErr);
    }
  }



  double mTauTauVisSF = ( mTauTauVis1 > 0. && mTauTauVis2 > 0. ) ? 0.5 : 1.;
  if ( mTauTauVis1 > 0. ) {
    fillWithOverFlow(histogram_mTauTauVis_, mTauTauVis1, mTauTauVisSF*evtWeight, mTauTauVisSF*evtWeightErr);
  }
  if ( mTauTauVis2 > 0. ) {
    fillWithOverFlow(histogram_mTauTauVis_, mTauTauVis2, mTauTauVisSF*evtWeight, mTauTauVisSF*evtWeightErr);
  }

  if ( memOutput_2lss_1tau ) {
    fillWithOverFlow(histogram_memOutput_isValid_, memOutput_2lss_1tau->isValid(), evtWeight, evtWeightErr);
    if ( memOutput_2lss_1tau->isValid() ) {
      fillWithOverFlow(histogram_memOutput_errorFlag_, memOutput_2lss_1tau->errorFlag(), evtWeight, evtWeightErr);
      if ( memOutput_2lss_1tau->errorFlag() == 0 ) {
	fillWithOverFlow(histogram_memOutput_type_, memOutput_2lss_1tau->type(), evtWeight, evtWeightErr);
	fillWithOverFlow(histogram_memOutput_logWeight_ttH_, getLogWeight(memOutput_2lss_1tau->weight_ttH()), evtWeight, evtWeightErr);
	fillWithOverFlow(histogram_memOutput_logWeight_ttZ_, getLogWeight(memOutput_2lss_1tau->weight_ttZ()), evtWeight, evtWeightErr);
	fillWithOverFlow(histogram_memOutput_logWeight_ttZ_Zll_, getLogWeight(memOutput_2lss_1tau->weight_ttZ_Zll()), evtWeight, evtWeightErr);
	fillWithOverFlow(histogram_memOutput_logWeight_tt_, getLogWeight(memOutput_2lss_1tau->weight_tt()), evtWeight, evtWeightErr);
	fillWithOverFlow(histogram_memOutput_LR_, memOutput_2lss_1tau->LR(), evtWeight, evtWeightErr);
	fillWithOverFlow(histogram_memDiscr_, memDiscr, evtWeight, evtWeightErr);
	TH1* histogram_memOutput_LR_type = 0;
	TH1* histogram_memDiscr_type = 0;
	if ( memOutput_2lss_1tau->type() == 0 ) {
	  histogram_memOutput_LR_type = histogram_memOutput_LR_type0_;
	  histogram_memDiscr_type = histogram_memDiscr_type0_;
	} else if ( memOutput_2lss_1tau->type() == 1 ) {
	  histogram_memOutput_LR_type = histogram_memOutput_LR_type1_;
	  histogram_memDiscr_type = histogram_memDiscr_type1_;
	}
	if ( histogram_memOutput_LR_type ) {
	  fillWithOverFlow(histogram_memOutput_LR_type, memOutput_2lss_1tau->LR(), evtWeight, evtWeightErr);
	}
	if ( histogram_memDiscr_type ) {
	  fillWithOverFlow(histogram_memDiscr_type, memDiscr, evtWeight, evtWeightErr);
	}
	fillWithOverFlow(histogram_mem_logCPUTime_, TMath::Log(TMath::Max((Float_t)1.e-21, memOutput_2lss_1tau->cpuTime())), evtWeight, evtWeightErr);
	fillWithOverFlow(histogram_mem_logRealTime_, TMath::Log(TMath::Max((Float_t)1.e-21, memOutput_2lss_1tau->realTime())), evtWeight, evtWeightErr);
      }
    }
  } else {
    fillWithOverFlow(histogram_memOutput_isValid_, -1, evtWeight, evtWeightErr);
  }

  fillWithOverFlow(histogram_EventCounter_, 0., evtWeight, evtWeightErr);
}
