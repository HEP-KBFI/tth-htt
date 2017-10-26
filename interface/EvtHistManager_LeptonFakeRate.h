#ifndef tthAnalysis_HiggsToTauTau_EvtHistManager_LeptonFakeRate_h
#define tthAnalysis_HiggsToTauTau_EvtHistManager_LeptonFakeRate_h

/** \class EvtHistManager_LeptonFakeRate
 *
 * Book and fill histograms for event-level quantities in the control region 
 * used to measure the Lepton fake-rate in the ttH, H->tautau analysis
 *
 * \author Ram Krishna Dewanjee, Tallin
 *
 */

#include "tthAnalysis/HiggsToTauTau/interface/HistManagerBase.h" // HistManagerBase
#include "tthAnalysis/HiggsToTauTau/interface/RecoElectron.h"
#include "tthAnalysis/HiggsToTauTau/interface/RecoMuon.h"
#include "tthAnalysis/HiggsToTauTau/interface/RecoLepton.h"
#include "tthAnalysis/HiggsToTauTau/interface/jetToTauFakeRateAuxFunctions.h" // getEtaBin, getPtBin

class EvtHistManager_LeptonFakeRate
  : public HistManagerBase
{
 public:
  EvtHistManager_LeptonFakeRate(edm::ParameterSet const& cfg);
  ~EvtHistManager_LeptonFakeRate() {}

  /// book and fill histograms
  void bookHistograms(TFileDirectory& dir);
  // void fillHistograms(int numElectrons, int numMuons, int numHadTaus, int numJets, int numBJets_loose, int numBJets_medium, double mLL, double mT_e, double mT_mu, double evtWeight);
  void fillHistograms(double met, double mT_L, double mT_fix_L, double evtWeight);

 private:
  // TH1* histogram_numElectrons_;
  // TH1* histogram_numMuons_;
  // TH1* histogram_numHadTaus_;
  // TH1* histogram_numJets_;
  // TH1* histogram_numBJets_loose_;
  // TH1* histogram_numBJets_medium_;

  // TH1* histogram_mLL_;
  // TH1* histogram_mT_e_;
  // TH1* histogram_mT_mu_;

  TH1* histogram_mT_L_;
  TH1* histogram_mT_fix_L_;
  TH1* histogram_MET_;
  TH1* histogram_EventCounter_;
  // std::vector<TH1*> histograms_;
};

#endif
