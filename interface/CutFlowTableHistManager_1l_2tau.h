#ifndef tthAnalysis_HiggsToTauTau_CutFlowTableHistManager_1l_2tau_h
#define tthAnalysis_HiggsToTauTau_CutFlowTableHistManager_1l_2tau_h

/** \class CutFlowTableHistManager_1l_2tau
 *
 * Book and fill histogram recording cut-flow in 1l_2tau category of ttH, H->tautau analysis
 *
 * \author Christian Veelken, Tallin
 *
 */

#include "tthAnalysis/HiggsToTauTau/interface/HistManagerBase.h" // HistManagerBase

class CutFlowTableHistManager_1l_2tau
  : public HistManagerBase
{
 public:
  CutFlowTableHistManager_1l_2tau(edm::ParameterSet const& cfg);
  ~CutFlowTableHistManager_1l_2tau() {}

  /// book and fill histograms
  void bookHistograms(TFileDirectory& dir);
  void fillHistograms(const std::string& cut, double evtWeight = 1.);

 private:
  TH1* histogram_cutFlow_;

  std::vector<TH1*> histograms_;
};

#endif
