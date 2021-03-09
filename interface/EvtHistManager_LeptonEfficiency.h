#ifndef tthAnalysis_HiggsToTauTau_EvtHistManager_LeptonEfficiency_h
#define tthAnalysis_HiggsToTauTau_EvtHistManager_LeptonEfficiency_h

/** \class EvtHistManager_LeptonEfficiency
 *
 * Book and fill histograms for event-level quantities in the control region 
 * used to measure the Lepton ID Efficiency in the HH/ttH Multi-lepton analysis
 *
 * \author Ram Krishna Dewanjee, Tallinn
 *
 */

#include "tthAnalysis/HiggsToTauTau/interface/HistManagerBase.h" // HistManagerBase

class EvtHistManager_LeptonEfficiency
  : public HistManagerBase
{
public:
  EvtHistManager_LeptonEfficiency(const edm::ParameterSet & cfg);
  ~EvtHistManager_LeptonEfficiency() {}

  /// book and fill histograms
  void
  bookHistograms(TFileDirectory & dir) override;

  void
    fillHistograms(double m_ll,
		   double evtWeight);

private:
  TH1 * histogram_m_ll_;
  TH1 * histogram_m_ll_num_;
  TH1 * histogram_m_ll_den_;
  TH1 * histogram_EventCounter_;
};

#endif
