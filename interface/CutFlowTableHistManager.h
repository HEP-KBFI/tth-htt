#ifndef CUTFLOWTABLEHISTMANAGER_H
#define CUTFLOWTABLEHISTMANAGER_H

#include "tthAnalysis/HiggsToTauTau/interface/HistManagerBase.h" // HistManagerBase

class CutFlowTableHistManager
  : public HistManagerBase
{
public:
  CutFlowTableHistManager(const edm::ParameterSet & cfg,
                          const std::vector<std::string> & cuts);
  ~CutFlowTableHistManager() {}

  /// book and fill histograms
  void
  bookHistograms(TFileDirectory & dir) override;

  void
  fillHistograms(const std::string & cut,
                 double evtWeight = 1.);

protected:
  TH1 * histogram_cutFlow_;
  std::vector<std::string> cuts_;
};

#endif // CUTFLOWTABLEHISTMANAGER_H
