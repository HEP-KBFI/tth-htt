#include "tthAnalysis/HiggsToTauTau/interface/EvtHistManager_2lss_1tau.h"

#include "tthAnalysis/HiggsToTauTau/interface/histogramAuxFunctions.h" // fillWithOverFlow, fillWithOverFlow2d, getLogWeight
#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // kEra_2017
#include "tthAnalysis/HiggsToTauTau/interface/lutAuxFunctions.h" // loadTH2, getSF_from_TH2

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
  if ( era_string == "2017" ) era_ = kEra_2017;
  else throw cms::Exception("EvtHistManager_2lss_1tau")
    << "Invalid Configuration parameter 'era' = " << era_string << " !!\n";
}

/*
void EvtHistManager_2lss_1tau::LoadMaps(int nstart, int ntarget)
{
  const Int_t  nbinsTarget[9]={5,6,7,8,9,10};
  const Int_t  nbinsStart[3]={15,20};
  std::string binOptSource="/hdfs/local/acaan/ttHAnalysis/2016/2lss_1tau_opt1";
  std::string binOptSourceEndTrue="bins_relLepIDTrue_CumulativeBins.root";
  std::string binOptSourceEndFalse="bins_relLepIDFalse_CumulativeBins.root";
  /////////////////////////////////////////
  for (int nbinsStartN=0 ; nbinsStartN<nstart ; nbinsStartN++ ) {
    for (int nbinsTargetN=0 ; nbinsTargetN<ntarget ; nbinsTargetN++ ) {
      std::cout<< binOptSource << "/bin_opt/oldVarA_from"<<nbinsStart[nbinsStartN]<<"_to_"<<nbinsTarget[nbinsTargetN]<< binOptSourceEndFalse<<std::endl;
      std::stringstream BDT_mapping_oldVarA_name;
      BDT_mapping_oldVarA_name << binOptSource << "/bin_opt/oldVarA_from"<<nbinsStart[nbinsStartN]<<"_to_"<<nbinsTarget[nbinsTargetN]<< binOptSourceEndFalse;
      std::cout<<"loaded histogram " <<std::endl;
      TH2* dumb_oldVarA= loadTH2(TFile::Open(BDT_mapping_oldVarA_name.str().c_str()), "hTargetBinning");
      std::cout<<"pushing " <<std::endl;
      oldVarA_.push_back(dumb_oldVarA);
      std::cout<<"loaded file "<<BDT_mapping_oldVarA_name.str() <<std::endl;
   }
  }
}
*/

/*
void EvtHistManager_2lss_1tau::bookHistogramsMap(TFileDirectory& dir , int nbinsStart, int nbinsTarget)
{
  string label[4]={"oldVarA","HTT","HTTMEM","noHTT"};
  for (int ii=0 ; ii < 4 ; ii++ ){
    std::stringstream ss2;
    ss2 <<label[ii]<<"_from"<<nbinsStart<<"_to_"<<nbinsTarget;
    //std::cout<<ss2.str().c_str()<<std::endl;
    TH1* dumb= book1D(dir, ss2.str().c_str(), ss2.str().c_str(), nbinsTarget, -0.5, nbinsTarget+0.5);
    if (ii==0) hist_oldVarA_2D_.push_back(dumb);
    if (ii==1) hist_HTT_2D_.push_back(dumb);
    if (ii==2) hist_HTTMEM_2D_.push_back(dumb);
    if (ii==3) hist_noHTT_2D_.push_back(dumb);
  }
}
*/

/*
void EvtHistManager_2lss_1tau::fillHistogramsMap(int counter, double evtWeight,
                                                 std::vector<TH2*>* oldVarA,
                                                 std::vector<TH2*>* HTT,
                                                 std::vector<TH2*>* noHTT,
                                                 std::vector<TH2*>* HTTMEM,
                                                 double mvaOutput_2lss_oldVarA_tt, double mvaOutput_2lss_oldVarA_ttV,
                                                 double mvaOutput_2lss_noHTT_tt, double mvaOutput_2lss_noHTT_ttV,
                                                 double mvaOutput_2lss_HTT_tt,
                                                 double mvaOutput_2lss_HTTMEM_tt, double mvaOutput_2lss_HTTMEM_ttV
                                                 )
{
  hist_oldVarA_2D_.at(counter)->AddBinContent( getSF_from_TH2(oldVarA->at(counter), mvaOutput_2lss_oldVarA_tt, mvaOutput_2lss_oldVarA_ttV)+1, evtWeight);
  // in root the bin number starts at 1, while the getSF_from_TH2 starts from zero
  //std::cout<<getSF_from_TH2(oldVarA->at(counter), mvaOutput_2lss_oldVarA_tt, mvaOutput_2lss_oldVarA_ttV)<<std::endl;
  hist_HTT_2D_.at(counter)->AddBinContent( getSF_from_TH2(HTT->at(counter), mvaOutput_2lss_HTT_tt, mvaOutput_2lss_noHTT_ttV)+1, evtWeight);
  hist_noHTT_2D_.at(counter)->AddBinContent( getSF_from_TH2(noHTT->at(counter), mvaOutput_2lss_noHTT_tt, mvaOutput_2lss_noHTT_ttV)+1, evtWeight);
  hist_HTTMEM_2D_.at(counter)->AddBinContent( getSF_from_TH2(HTTMEM->at(counter), mvaOutput_2lss_HTTMEM_tt, mvaOutput_2lss_HTTMEM_ttV)+1, evtWeight);
}
*/

void EvtHistManager_2lss_1tau::bookHistograms(TFileDirectory& dir)
{
  //std::cout << "Book histos "<< std::endl;
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
  if ( era_ == kEra_2017 ) histogram_mvaDiscr_2lss_ = book1D(dir, "mvaDiscr_2lss", "mvaDiscr_2lss", 7, 0.5, 7.5);
  else assert(0);

  histogram_mvaOutput_2lss_1tau_ttV_ = book1D(dir, "mvaOutput_2lss_1tau_ttV", "mvaOutput_2lss_1tau_ttV", 600, -1., +1.);
  histogram_mvaOutput_2lss_1tau_ttbar_ = book1D(dir, "mvaOutput_2lss_1tau_ttbar", "mvaOutput_2lss_1tau_ttbar", 600, -1., +1.);
  histogram_mvaDiscr_2lss_1tau_ = book1D(dir, "mvaDiscr_2lss_1tau", "mvaDiscr_2lss_1tau", 7, 0.5, 7.5);
  histogram_mvaOutput_2lss_1tau_ttV_wMEM_ = book1D(dir, "mvaOutput_2lss_1tau_ttV_wMEM", "mvaOutput_2lss_1tau_ttV_wMEM", 600, -1., +1.);
  histogram_mvaOutput_2lss_1tau_ttbar_wMEM_ = book1D(dir, "mvaOutput_2lss_1tau_ttbar_wMEM", "mvaOutput_2lss_1tau_ttbar_wMEM", 600, -1., +1.);
  histogram_mvaDiscr_2lss_1tau_wMEM_ = book1D(dir, "mvaDiscr_2lss_1tau_wMEM", "mvaDiscr_2lss_1tau_wMEM", 7, 0.5, 7.5);

  histogram_mvaOutput_Hj_tagger_ = book1D(dir, "mvaOutput_Hj_tagger", "mvaOutput_Hj_tagger", 20, -1., +1.);
  histogram_mvaOutput_Hjj_tagger_ = book1D(dir, "mvaOutput_Hjj_tagger", "mvaOutput_Hjj_tagger", 20, -1., +1.);

  histogram_mTauTauVis_ = book1D(dir, "mTauTauVis", "mTauTauVis", 20, 0., 200.);
  histogram_mTauTauVis1_ = book1D(dir, "mTauTauVis1", "mTauTauVis1", 20, 0., 200.);
  histogram_mTauTauVis2_ = book1D(dir, "mTauTauVis2", "mTauTauVis2", 20, 0., 200.);
  histogram_memOutput_LR_ = book1D(dir, "memOutput_LR", "memOutput_LR", 600, 0., 1.);

  string label[4]={"oldVarA","HTT","HTTMEM","noHTT"};
  for (int nbinsStartN=0 ; nbinsStartN< nstart  ; nbinsStartN++ ) {
    for (int nbinsTargetN=0 ; nbinsTargetN<ntarget ; nbinsTargetN++ ) {
      for (int ii=0 ; ii < 4 ; ii++ ){
        std::stringstream ss2;
        ss2 <<label[ii]<<"_from"<<nbinsStart[nbinsStartN]<<"_to_"<<nbinsTarget[nbinsTargetN];
        //std::cout<<ss2.str().c_str()<<std::endl;
        TH1* dumb= book1D(dir, ss2.str().c_str(), ss2.str().c_str(), nbinsTarget[nbinsTargetN], -0.5, nbinsTarget[nbinsTargetN]+0.5);
        if (ii==0) hist_oldVarA_2D_.push_back(dumb);
        if (ii==1) hist_HTT_2D_.push_back(dumb);
        if (ii==2) hist_HTTMEM_2D_.push_back(dumb);
        if (ii==3) hist_noHTT_2D_.push_back(dumb);
        }
      }
    }

  /*
  histogram_memOutput_isValid_ = book1D(dir, "memOutput_isValid", "memOutput_isValid", 3, -1.5, +1.5);
  histogram_memOutput_errorFlag_ = book1D(dir, "memOutput_errorFlag", "memOutput_errorFlag", 2, -0.5, +1.5);
  histogram_memOutput_type_ = book1D(dir, "memOutput_type", "memOutput_type", 4, -1.5, +2.5);
  histogram_memOutput_logWeight_ttH_ = book1D(dir, "memOutput_logWeight_ttH", "memOutput_logWeight_ttH", 100, -20., +20.);
  histogram_memOutput_logWeight_ttZ_ = book1D(dir, "memOutput_logWeight_ttZ", "memOutput_logWeight_ttZ", 100, -20., +20.);
  histogram_memOutput_logWeight_ttZ_Zll_ =book1D(dir, "memOutput_logWeight_ttZ_Zll", "memOutput_logWeight_ttZ_Zll", 100, -20., +20.);
  histogram_memOutput_logWeight_tt_ = book1D(dir, "memOutput_logWeight_tt", "memOutput_logWeight_tt", 100, -20., +20.);
  histogram_memOutput_LR_ = book1D(dir, "memOutput_LR", "memOutput_LR", 100, 0., 1.);
  histogram_memOutput_LR_type0_ = book1D(dir, "memOutput_LR_type0", "memOutput_LR_type0", 40, 0., 1.);
  histogram_memOutput_LR_type1_ = book1D(dir, "memOutput_LR_type1", "memOutput_LR_type1", 40, 0., 1.);

  histogram_memDiscr_type0_ = book1D(dir, "memDiscr_type0", "memDiscr_type0", 8, 0.5, 8.5);
  histogram_memDiscr_type1_ = book1D(dir, "memDiscr_type1", "memDiscr_type1", 8, 0.5, 8.5);
  histogram_mem_logCPUTime_ = book1D(dir, "mem_logCPUTime", "mem_logCPUTime", 400, -20., +20.);
  histogram_mem_logRealTime_ = book1D(dir, "mem_logRealTime", "mem_logRealTime", 400, -20., +20.);
  */
  histogram_memDiscr_ = book1D(dir, "memDiscr", "memDiscr", 8, 0.5, 8.5);
  histogram_EventCounter_ = book1D(dir, "EventCounter", "EventCounter", 1, -0.5, +0.5);

  histogram_mvaOutput_2lss_oldVarA_tt_= book1D(dir, "mvaOutput_2lss_oldVarA_tt", "mvaOutput_2lss_oldVarA_tt", 600, 0., +1.);
  histogram_mvaOutput_2lss_oldVarA_ttV_= book1D(dir, "mvaOutput_2lss_oldVarA_ttV", "mvaOutput_2lss_oldVarA_ttV",    600, 0., +1.);
  histogram_mvaOutput_2lss_HTT_tt_= book1D(dir, "mvaOutput_2lss_HTT_tt", "mvaOutput_2lss_HTT_tt",          600, 0., +1.);
  histogram_mvaOutput_2lss_noHTT_tt_= book1D(dir, "mvaOutput_2lss_noHTT_tt", "mvaOutput_2lss_noHTT_tt",    600, 0., +1.);
  histogram_mvaOutput_2lss_noHTT_ttV_= book1D(dir, "mvaOutput_2lss_noHTT_ttV", "mvaOutput_2lss_noHTT_ttV", 600, 0., +1.);
  histogram_mvaOutput_2lss_HTTMEM_tt_= book1D(dir, "mvaOutput_2lss_HTTMEM_tt", "mvaOutput_2lss_HTTMEM_tt",    600, 0., +1.);
  histogram_mvaOutput_2lss_HTTMEM_ttV_= book1D(dir, "mvaOutput_2lss_HTTMEM_ttV", "mvaOutput_2lss_HTTMEM_ttV", 600, 0., +1.);
  histogram_mvaOutput_2lss_HTT_LepID_tt_= book1D(dir, "mvaOutput_2lss_HTT_LepID_tt", "mvaOutput_2lss_HTT_LepID_tt", 600, 0., +1.);

  //hist_oldVar_from20_to_12_ = book1D(dir, "oldVar_from20_to_12", "oldVar_from20_to_12", 12, -0.5, 12+0.5);
  //hist_oldVar_from20_to_7_ = book1D(dir, "oldVar_from20_to_7", "oldVar_from20_to_7", 7, -0.5, 7+0.5);

  histogram_mvaOutput_2lss_HTTMEM_1B_= book1D(dir, "mvaOutput_2lss_HTTMEM_1B", "mvaOutput_2lss_HTTMEM_1B", 600, 0., +1.);
  histogram_mvaOutput_2lss_HTT_1B_= book1D(dir, "mvaOutput_2lss_HTT_1B", "mvaOutput_2lss_HTT_1B",    600, 0., +1.);
  histogram_mvaOutput_2lss_noHTT_1B_= book1D(dir, "mvaOutput_2lss_noHTT_1B", "mvaOutput_2lss_noHTT_1B",          600, 0., +1.);
  histogram_mvaOutput_2lss_oldVarA_1B_= book1D(dir, "mvaOutput_2lss_oldVarA_1B", "mvaOutput_2lss_oldVarA_1B",    600, 0., +1.);
  histogram_mvaOutput_2lss_oldVarA_2MEM_= book1D(dir, "mvaOutput_2lss_oldVarA_2MEM", "mvaOutput_2lss_oldVarA_2MEM", 600, 0., +1.);
  histogram_mvaOutput_2lss_noHTT_2MEM_= book1D(dir, "mvaOutput_2lss_noHTT_2MEM", "mvaOutput_2lss_noHTT_2MEM",    600, 0., +1.);
  histogram_mvaOutput_2lss_noHTT_2HTT_= book1D(dir, "mvaOutput_2lss_noHTT_2HTT", "mvaOutput_2lss_noHTT_2HTT", 600, 0., +1.);

}

void EvtHistManager_2lss_1tau::fillHistograms(
      std::vector<const RecoElectron*>::size_type numElectrons,
      std::vector<const RecoMuon*>::size_type numMuons,
      std::vector<const RecoHadTau*>::size_type numHadTaus,
      std::vector<const RecoJet*>::size_type numJets,
      std::vector<const RecoJet*>::size_type numBJets_loose,
      std::vector<const RecoJet*>::size_type numBJets_medium,
      std::vector<TH2*>* oldVarA,
      std::vector<TH2*>* HTT,
      std::vector<TH2*>* noHTT,
      std::vector<TH2*>* HTTMEM,
      int sel,
      double evtWeight,
      double mvaOutput_2lss_ttV,
      double mvaOutput_2lss_ttbar,
      double mvaDiscr_2lss,
      double mvaOutput_2lss_1tau_ttV,
      double mvaOutput_2lss_1tau_ttbar,
      double mvaDiscr_2lss_1tau,
      double mvaOutput_2lss_1tau_ttV_wMEM,
      double mvaOutput_2lss_1tau_ttbar_wMEM,
      double mvaDiscr_2lss_1tau_wMEM,
      double mvaOutput_Hj_tagger,
      double mvaOutput_Hjj_tagger,
      double mTauTauVis1,
      double mTauTauVis2,
      double memOutput_LR, //const MEMOutput_2lss_1tau* memOutput_2lss_1tau,
      double memDiscr,
      // XGB training 1D
      double mvaOutput_2lss_oldVarA_tt,
      double mvaOutput_2lss_oldVarA_ttV,
      double mvaOutput_2lss_noHTT_tt,
      double mvaOutput_2lss_noHTT_ttV,
      double mvaOutput_2lss_HTT_tt,
      double mvaOutput_2lss_HTTMEM_tt,
      double mvaOutput_2lss_HTTMEM_ttV,
      double mvaOutput_2lss_HTT_LepID_tt,
      // 2D mapppings [nstart][ntarget]
      /*
      Double_t  (&oldVarA_2D)[2][6],
      Double_t  (&HTT_2D)[2][6],
      Double_t  (&HTTMEM_2D)[2][6],
      Double_t  (&noHTT_2D)[2][6],
      */
      //double  oldVarA_2D[2][6],
      //double  HTT_2D[2][6],
      //double  HTTMEM_2D[2][6],
      //double  noHTT_2D[2][6],
      // XGB training, joint
      double mvaOutput_2lss_HTTMEM_1B,
      double mvaOutput_2lss_HTT_1B,
      double mvaOutput_2lss_noHTT_1B,
      double mvaOutput_2lss_oldVarA_1B,
      double mvaOutput_2lss_oldVarA_2MEM,
      double mvaOutput_2lss_noHTT_2MEM,
      double mvaOutput_2lss_noHTT_2HTT
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

  fillWithOverFlow(histogram_mTauTauVis_, mTauTauVis1, evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mTauTauVis1_, mTauTauVis1, evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mTauTauVis2_, mTauTauVis2, evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_memOutput_LR_, memOutput_LR, evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_memDiscr_, memDiscr , evtWeight, evtWeightErr);

  fillWithOverFlow(histogram_mvaOutput_2lss_oldVarA_tt_, mvaOutput_2lss_oldVarA_tt, evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mvaOutput_2lss_oldVarA_ttV_, mvaOutput_2lss_oldVarA_ttV, evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mvaOutput_2lss_HTT_tt_, mvaOutput_2lss_HTT_tt, evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mvaOutput_2lss_noHTT_tt_, mvaOutput_2lss_noHTT_tt, evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mvaOutput_2lss_noHTT_ttV_, mvaOutput_2lss_noHTT_ttV, evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mvaOutput_2lss_HTT_LepID_tt_, mvaOutput_2lss_HTT_LepID_tt, evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mvaOutput_2lss_HTTMEM_tt_, mvaOutput_2lss_HTTMEM_tt, evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mvaOutput_2lss_HTTMEM_ttV_, mvaOutput_2lss_HTTMEM_ttV, evtWeight, evtWeightErr);

  //fillWithOverFlow(hist_oldVar_from20_to_12_, oldVar_from20_to_12, evtWeight, evtWeightErr);
  //fillWithOverFlow(hist_oldVar_from20_to_7_, oldVar_from20_to_7, evtWeight, evtWeightErr);

  /*
  for (int nbinsStartN=0 ; nbinsStartN<2 ; nbinsStartN++ ) {
    for (int nbinsTargetN=0 ; nbinsTargetN<6 ; nbinsTargetN++ ) {
      //std::cout<<"internal filling histos "<<HTT_2D[nbinsStartN][nbinsTargetN]<<" "<< noHTT_2D[nbinsStartN][nbinsTargetN]<<std::endl;
      fillWithOverFlow(hist_oldVarA_2D_[nbinsStartN][nbinsTargetN], oldVarA_2D[nbinsStartN][nbinsTargetN], evtWeight, evtWeightErr);
      fillWithOverFlow(hist_HTT_2D_[nbinsStartN][nbinsTargetN], HTT_2D[nbinsStartN][nbinsTargetN], evtWeight, evtWeightErr);
      fillWithOverFlow(hist_noHTT_2D_[nbinsStartN][nbinsTargetN], noHTT_2D[nbinsStartN][nbinsTargetN], evtWeight, evtWeightErr);
      fillWithOverFlow(hist_HTTMEM_2D_[nbinsStartN][nbinsTargetN], HTTMEM_2D[nbinsStartN][nbinsTargetN], evtWeight, evtWeightErr);
    }
  }
  */

  fillWithOverFlow(histogram_mvaOutput_2lss_HTTMEM_1B_, mvaOutput_2lss_HTTMEM_1B, evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mvaOutput_2lss_HTT_1B_, mvaOutput_2lss_HTT_1B, evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mvaOutput_2lss_noHTT_1B_, mvaOutput_2lss_noHTT_1B, evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mvaOutput_2lss_oldVarA_1B_, mvaOutput_2lss_oldVarA_1B, evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mvaOutput_2lss_oldVarA_2MEM_, mvaOutput_2lss_oldVarA_2MEM, evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mvaOutput_2lss_noHTT_2MEM_, mvaOutput_2lss_noHTT_2MEM, evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mvaOutput_2lss_noHTT_2HTT_, mvaOutput_2lss_noHTT_2HTT, evtWeight, evtWeightErr);

  ///* DO 2D
  //if (sel==1)  std::cout<<"filling with 2D maps"<<std::endl;
  int countHist2=0;
  for (int nbinsStartN=0 ; nbinsStartN<nstart ; nbinsStartN++ ) {
    for (int nbinsTargetN=0 ; nbinsTargetN<ntarget ; nbinsTargetN++ ) {
      // in root the bin number starts at 1, while the getSF_from_TH2 starts from zero
      fillWithOverFlow(hist_oldVarA_2D_.at(countHist2),
        getSF_from_TH2(oldVarA->at(countHist2),mvaOutput_2lss_oldVarA_tt, mvaOutput_2lss_oldVarA_ttV)+1, evtWeight, evtWeightErr);
      fillWithOverFlow(hist_HTT_2D_.at(countHist2),
        getSF_from_TH2(HTT->at(countHist2), mvaOutput_2lss_HTT_tt, mvaOutput_2lss_noHTT_ttV)+1, evtWeight, evtWeightErr);
      fillWithOverFlow(hist_noHTT_2D_.at(countHist2),
        getSF_from_TH2(noHTT->at(countHist2), mvaOutput_2lss_noHTT_tt, mvaOutput_2lss_noHTT_ttV)+1, evtWeight, evtWeightErr);
      fillWithOverFlow(hist_HTTMEM_2D_.at(countHist2),
        getSF_from_TH2(HTTMEM->at(countHist2), mvaOutput_2lss_HTTMEM_tt, mvaOutput_2lss_HTTMEM_ttV)+1, evtWeight, evtWeightErr);
      ////////////////////////////////
      //hist_oldVarA_2D_.at(countHist2)->AddBinContent(
      //                  getSF_from_TH2(oldVarA->at(countHist2),mvaOutput_2lss_oldVarA_tt, mvaOutput_2lss_oldVarA_ttV)+1, evtWeight);
      //hist_HTT_2D_.at(countHist2)->AddBinContent(
      //                  getSF_from_TH2(HTT->at(countHist2), mvaOutput_2lss_HTT_tt, mvaOutput_2lss_noHTT_ttV)+1, evtWeight);
      //hist_noHTT_2D_.at(countHist2)->AddBinContent(
      //                  getSF_from_TH2(noHTT->at(countHist2), mvaOutput_2lss_noHTT_tt, mvaOutput_2lss_noHTT_ttV)+1, evtWeight);
      //hist_HTTMEM_2D_.at(countHist2)->AddBinContent(
      //                  getSF_from_TH2(HTTMEM->at(countHist2), mvaOutput_2lss_HTTMEM_tt, mvaOutput_2lss_HTTMEM_ttV)+1, evtWeight);
      countHist2++;
    }
  }
  /*
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
  */

  fillWithOverFlow(histogram_EventCounter_, 0., evtWeight, evtWeightErr);
}

void EvtHistManager_2lss_1tau::integralHistograms(TFileDirectory& dir)
{
  std::cout<<"Integral of histogram "<< histogram_mvaOutput_2lss_oldVarA_tt_->Integral() <<std::endl;
}
