#ifndef tthAnalysis_HiggsToTauTau_EvtHistManager_ttZctrl_h
#define tthAnalysis_HiggsToTauTau_EvtHistManager_ttZctrl_h

/** \class EvtHistManager_ttZctrl
 *
 * Book and fill histograms for event-level quantities in ttH, H->tautau analysis
 * in control region enriched in ttZ background
 *
 * \author Christian Veelken, Tallin
 *
 */

#include "tthAnalysis/HiggsToTauTau/interface/HistManagerBase.h" // HistManagerBase

class EvtHistManager_ttZctrl
  : public HistManagerBase
{
 public:
  EvtHistManager_ttZctrl(edm::ParameterSet const& cfg);
  ~EvtHistManager_ttZctrl() {}

  /// book and fill histograms
  void bookHistograms(TFileDirectory& dir);
  void fillHistograms(int numElectrons, int numMuons, int numHadTaus, int numJets, int numBJets_loose, int numBJets_medium, 
		      double mLL, double mT, int sumLeptonCharge, double evtWeight);

 private:
  TH1* histogram_numElectrons_;
  TH1* histogram_numMuons_;
  TH1* histogram_numLeptons_;
  TH1* histogram_numHadTaus_;
  TH1* histogram_numJets_;
  TH1* histogram_numBJets_loose_;
  TH1* histogram_numBJets_medium_;

  TH1* histogram_mLL_;

  TH1* histogram_mT_;

  TH1* histogram_sumLeptonCharge_;

  TH1* histogram_EventCounter_;

  std::vector<TH1*> histograms_;
};

#endif
