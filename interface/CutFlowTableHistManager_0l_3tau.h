#ifndef tthAnalysis_HiggsToTauTau_CutFlowTableHistManager_0l_3tau_h
#define tthAnalysis_HiggsToTauTau_CutFlowTableHistManager_0l_3tau_h

/** \class CutFlowTableHistManager_0l_3tau
 *
 * Book and fill histogram recording cut-flow in 0l_3tau category of ttH, H->tautau analysis
 *
 * \author Christian Veelken, Tallin
 *
 */

#include "tthAnalysis/HiggsToTauTau/interface/HistManagerBase.h" // HistManagerBase

class CutFlowTableHistManager_0l_3tau
  : public HistManagerBase
{
 public:
  CutFlowTableHistManager_0l_3tau(edm::ParameterSet const& cfg);
  ~CutFlowTableHistManager_0l_3tau() {}

  /// book and fill histograms
  void bookHistograms(TFileDirectory& dir);
  void fillHistograms(const std::string& cut, double evtWeight = 1.);

 private:
  TH1* histogram_cutFlow_;

  std::vector<TH1*> histograms_;
};

#endif
