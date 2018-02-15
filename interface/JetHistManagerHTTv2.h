#ifndef tthAnalysis_HiggsToTauTau_JetHistManagerHTTv2_h
#define tthAnalysis_HiggsToTauTau_JetHistManagerHTTv2_h

/** \class JetHistManagerHTTv2
 *
 * Book and fill histograms for jets reconstructed by hep-top-tagger (HTTv2) algorithm in ttH, H->tautau analysis
 *
 * \author Christian Veelken, Tallin
 *
 */

#include "tthAnalysis/HiggsToTauTau/interface/HistManagerBase.h" // HistManagerBase
#include "tthAnalysis/HiggsToTauTau/interface/RecoJetHTTv2.h"

class JetHistManagerHTTv2
  : public HistManagerBase
{
public:
  JetHistManagerHTTv2(const edm::ParameterSet & cfg);
  ~JetHistManagerHTTv2() {}

  /// book and fill histograms
  void
  bookHistograms(TFileDirectory & dir) override;

  void
  fillHistograms(const RecoJetHTTv2 & jet,
                 double evtWeight);

  void
  fillHistograms(const std::vector<const RecoJetHTTv2 *> & jets,
                 double evtWeight);

private:
  TH1 * histogram_pt_;
  TH1 * histogram_eta_;
  TH1 * histogram_phi_;
  TH1 * histogram_mass_;

  TH1 * histogram_fRec_;
  TH1 * histogram_deltaRopt_;
  TH1 * histogram_maxSubjetBtagCSV_;

  TH1 * histogram_tau21_;
  TH1 * histogram_tau32_;
  
  std::vector<TH1 *> histograms_;

  int idx_; // flag to select leading or subleading jet (set idx to -1 to make plots for all jets)
};

#endif
