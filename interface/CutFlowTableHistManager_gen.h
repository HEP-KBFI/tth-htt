#ifndef tthAnalysis_HiggsToTauTau_CutFlowTableHistManager_gen_h
#define tthAnalysis_HiggsToTauTau_CutFlowTableHistManager_gen_h

/** \class CutFlowTableHistManager_gen
 *
 * Book and fill histogram recording cut-flow for analyze_gen executable of ttH, H->tautau analysis
 *
 * \author Christian Veelken, Tallin
 *
 */

#include "tthAnalysis/HiggsToTauTau/interface/HistManagerBase.h" // HistManagerBase

class CutFlowTableHistManager_gen
  : public HistManagerBase
{
 public:
  CutFlowTableHistManager_gen(edm::ParameterSet const& cfg);
  ~CutFlowTableHistManager_gen() {}

  /// book and fill histograms
  void bookHistograms(TFileDirectory& dir);
  void fillHistograms(const std::string& cut, double evtWeight = 1.);

 private:
  TH1* histogram_cutFlow_;

  std::vector<TH1*> histograms_;
};

#endif
