#ifndef tthAnalysis_HiggsToTauTau_CutFlowTableHistManager_charge_flip_h
#define tthAnalysis_HiggsToTauTau_CutFlowTableHistManager_charge_flip_h

/** \class CutFlowTableHistManager_charge_flip
 *
 * Book and fill histogram recording cut-flow in electron charge misidentification rate measurement
 *
 * \author Christian Veelken, Tallin
 *
 */

#include "tthAnalysis/HiggsToTauTau/interface/HistManagerBase.h" // HistManagerBase

class CutFlowTableHistManager_charge_flip
  : public HistManagerBase
{
 public:
  CutFlowTableHistManager_charge_flip(edm::ParameterSet const& cfg);
  ~CutFlowTableHistManager_charge_flip() {}

  /// book and fill histograms
  void bookHistograms(TFileDirectory& dir);
  void fillHistograms(const std::string& cut, double evtWeight = 1.);

 private:
  TH1* histogram_cutFlow_;

  std::vector<TH1*> histograms_;
};

#endif
