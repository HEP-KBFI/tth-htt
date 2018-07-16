#ifndef tthAnalysis_HiggsToTauTau_EvtHistManager_LeptonFakeRate_h
#define tthAnalysis_HiggsToTauTau_EvtHistManager_LeptonFakeRate_h

/** \class EvtHistManager_LeptonFakeRate
 *
 * Book and fill histograms for event-level quantities in the control region 
 * used to measure the Lepton fake-rate in the ttH, H->tautau analysis
 *
 * \author Ram Krishna Dewanjee, Tallinn
 *
 */

#include "tthAnalysis/HiggsToTauTau/interface/HistManagerBase.h" // HistManagerBase

class EvtHistManager_LeptonFakeRate
  : public HistManagerBase
{
public:
  EvtHistManager_LeptonFakeRate(const edm::ParameterSet & cfg);
  ~EvtHistManager_LeptonFakeRate() {}

  /// book and fill histograms
  void
  bookHistograms(TFileDirectory & dir) override;

  void
  fillHistograms(double met,
                 double mT_L,
                 double mT_fix_L,
                 double evtWeight);

private:
  TH1 * histogram_mT_L_;
  TH1 * histogram_mT_fix_L_;
  TH1 * histogram_mT_fix_L_num_;
  TH1 * histogram_mT_fix_L_den_;
  TH1 * histogram_MET_;
  TH1 * histogram_EventCounter_;
};

#endif
