#ifndef tthAnalysis_HiggsToTauTau_CutFlowTableHistManager_3l_1tau_h
#define tthAnalysis_HiggsToTauTau_CutFlowTableHistManager_3l_1tau_h

/** \class CutFlowTableHistManager_3l_1tau
 *
 * Book and fill histogram recording cut-flow in 3l_1tau category of ttH, H->tautau analysis
 *
 * \author Christian Veelken, Tallin
 *
 */

#include "tthAnalysis/HiggsToTauTau/interface/HistManagerBase.h" // HistManagerBase

class CutFlowTableHistManager_3l_1tau
  : public HistManagerBase
{
 public:
  CutFlowTableHistManager_3l_1tau(edm::ParameterSet const& cfg);
  ~CutFlowTableHistManager_3l_1tau() {}

  /// book and fill histograms
  void bookHistograms(TFileDirectory& dir);
  void fillHistograms(const std::string& cut, double evtWeight = 1.);

 private:
  TH1* histogram_cutFlow_;

  std::vector<TH1*> histograms_;
};

#endif
