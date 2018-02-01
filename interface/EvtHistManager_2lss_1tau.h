#ifndef tthAnalysis_HiggsToTauTau_EvtHistManager_2lss_1tau_h
#define tthAnalysis_HiggsToTauTau_EvtHistManager_2lss_1tau_h

/** \class EvtHistManager_2lss_1tau
 *
 * Book and fill histograms for event-level quantities in ttH, H->tautau analysis
 * in 2lss_1tau category
 *
 * \author Christian Veelken, Tallin
 *
 */

#include "tthAnalysis/HiggsToTauTau/interface/HistManagerBase.h" // HistManagerBase

#include "tthAnalysis/HiggsToTauTau/interface/MEMInterface_2lss_1tau.h" // MEMOutput_2lss_1tau
#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h"

class EvtHistManager_2lss_1tau
  : public HistManagerBase
{
 public:
  EvtHistManager_2lss_1tau(edm::ParameterSet const& cfg);
  ~EvtHistManager_2lss_1tau() {}

  const Int_t  nbinsTarget[9]={5,6,7,8,9,10};
  const Int_t  nbinsStart[3]={15,20};
  const Int_t nstart =2;
  const Int_t ntarget =6;

  //void LoadMaps(int nstart, int ntarget);
  ///*
  void bookHistogramsMap(TFileDirectory& dir , int , int);
  void fillHistogramsMap(int counter, double evtWeight,
     std::vector<TH2*>* oldVarA,
     std::vector<TH2*>* HTT,
     std::vector<TH2*>* noHTT,
     std::vector<TH2*>* HTTMEM,
     double mvaOutput_2lss_oldVarA_tt, double mvaOutput_2lss_oldVarA_ttV,
     double mvaOutput_2lss_noHTT_tt, double mvaOutput_2lss_noHTT_ttV,
     double mvaOutput_2lss_HTT_tt,
     double mvaOutput_2lss_HTTMEM_tt, double mvaOutput_2lss_HTTMEM_ttV
     );
     //*/


  void bookHistograms(TFileDirectory& dir);
  void integralHistograms(TFileDirectory& dir);
  void fillHistograms(
    std::vector<const RecoElectron*>::size_type numElectrons,
    std::vector<const RecoMuon*>::size_type numMuons,
    std::vector<const RecoHadTau*>::size_type numHadTaus,
    std::vector<const RecoJet*>::size_type numJets,
    std::vector<const RecoJet*>::size_type numBJets_loose,
    std::vector<const RecoJet*>::size_type numBJets_medium,
    //std::vector<TH2*>* oldVarA,
    //std::vector<TH2*>* HTT,
    //std::vector<TH2*>* noHTT,
    //std::vector<TH2*>* HTTMEM,
    //int sel,
    double evtWeight,
    //
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
        );

  const TH1* getHistogram_EventCounter() const { return histogram_EventCounter_; }

 private:
  int era_;

  TH1* histogram_numElectrons_;
  TH1* histogram_numMuons_;
  TH1* histogram_numHadTaus_;
  TH1* histogram_numJets_;
  TH1* histogram_numBJets_loose_;
  TH1* histogram_numBJets_medium_;

  TH2* histogram_numBJets_loose_vs_numJets_;  // CV: used to check loss in signal efficiency in case events with high jet and b-jet multiplicity are vetoed
  TH2* histogram_numBJets_medium_vs_numJets_; //     to avoid overlap with ttH, H->bb analysis (alternative: ttH, H->bb analysis adds hadronic tau veto)

  TH1* histogram_mvaOutput_2lss_ttV_;
  TH1* histogram_mvaOutput_2lss_ttbar_;
  TH1* histogram_mvaDiscr_2lss_;

  TH1* histogram_mvaOutput_2lss_1tau_ttV_;
  TH1* histogram_mvaOutput_2lss_1tau_ttbar_;
  TH1* histogram_mvaDiscr_2lss_1tau_;
  TH1* histogram_mvaOutput_2lss_1tau_ttV_wMEM_;
  TH1* histogram_mvaOutput_2lss_1tau_ttbar_wMEM_;
  TH1* histogram_mvaDiscr_2lss_1tau_wMEM_;

  TH1* histogram_mvaOutput_Hj_tagger_;
  TH1* histogram_mvaOutput_Hjj_tagger_;

  TH1* histogram_mTauTauVis1_;
  TH1* histogram_mTauTauVis_;
  TH1* histogram_mTauTauVis2_;
  TH1* histogram_memOutput_LR_;
  TH1* histogram_memDiscr_;

  /*
  TH1* histogram_memOutput_isValid_;
  TH1* histogram_memOutput_errorFlag_;
  TH1* histogram_memOutput_type_;
  TH1* histogram_memOutput_logWeight_ttH_;
  TH1* histogram_memOutput_logWeight_ttZ_;
  TH1* histogram_memOutput_logWeight_ttZ_Zll_;
  TH1* histogram_memOutput_logWeight_tt_;
  TH1* histogram_memOutput_LR_;
  TH1* histogram_memOutput_LR_type0_;
  TH1* histogram_memOutput_LR_type1_;
  TH1* histogram_memDiscr_;
  TH1* histogram_memDiscr_type0_;
  TH1* histogram_memDiscr_type1_;
  TH1* histogram_mem_logCPUTime_;
  TH1* histogram_mem_logRealTime_;
  */

  TH1* histogram_EventCounter_;

  TH1* histogram_mvaOutput_2lss_oldVarA_tt_;
  TH1* histogram_mvaOutput_2lss_oldVarA_ttV_;
  TH1* histogram_mvaOutput_2lss_noHTT_tt_;
  TH1* histogram_mvaOutput_2lss_noHTT_ttV_;
  TH1* histogram_mvaOutput_2lss_HTT_tt_;
  TH1* histogram_mvaOutput_2lss_HTTMEM_tt_;
  TH1* histogram_mvaOutput_2lss_HTTMEM_ttV_;
  TH1* histogram_mvaOutput_2lss_HTT_LepID_tt_;

  //TH1* hist_oldVar_from20_to_12_;
  //TH1* hist_oldVar_from20_to_7_;
  //std::vector<std::vector<TH1*>> hist_HTT_2D_(int 3, int 9); // nbinsStart.size()
  //std::vector<std::vector<TH1*>> hist_noHTT_2D_(int 3, int 9);

  //const int & nstart =2;
  //const int & ntarget =6;
  //TH1* hist_HTT_2D_[2][6];
  //TH1* hist_noHTT_2D_[2][6];
  //TH1* hist_HTTMEM_2D_[2][6];
  //TH1* hist_oldVarA_2D_[2][6];

  TH1* histogram_mvaOutput_2lss_HTTMEM_1B_;
  TH1* histogram_mvaOutput_2lss_HTT_1B_;
  TH1* histogram_mvaOutput_2lss_noHTT_1B_;
  TH1* histogram_mvaOutput_2lss_oldVarA_1B_;
  TH1* histogram_mvaOutput_2lss_oldVarA_2MEM_;
  TH1* histogram_mvaOutput_2lss_noHTT_2MEM_;
  TH1* histogram_mvaOutput_2lss_noHTT_2HTT_;

  std::vector<TH1*> hist_oldVarA_2D_;
  std::vector<TH1*> hist_HTT_2D_;
  std::vector<TH1*> hist_HTTMEM_2D_;
  std::vector<TH1*> hist_noHTT_2D_;

  std::vector<TH1*> histograms_;
};

#endif
