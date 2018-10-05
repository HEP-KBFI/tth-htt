#ifndef tthAnalysis_HiggsToTauTau_JetHistManagerAK8_h
#define tthAnalysis_HiggsToTauTau_JetHistManagerAK8_h

/** \class JetHistManagerAK8
 *
 * Book and fill histograms for jets reconstructed by the anti-kT algorithm with R=1.2 (AK8) in ttH, H->tautau analysis
 *
 * \author Christian Veelken, Tallin
 *
 */

#include "tthAnalysis/HiggsToTauTau/interface/HistManagerBase.h" // HistManagerBase
#include "tthAnalysis/HiggsToTauTau/interface/RecoJetAK8.h"

class JetHistManagerAK8
  : public HistManagerBase
{
public:
  JetHistManagerAK8(const edm::ParameterSet & cfg);
  ~JetHistManagerAK8() {}

  /// book and fill histograms
  void
  bookHistograms(TFileDirectory & dir) override;

  void
  fillHistograms(const RecoJetAK8 & jet,
                 double evtWeight);

  void
  fillHistograms(const std::vector<const RecoJetAK8 *> & jets,
                 double evtWeight);

private:
  TH1 * histogram_pt_;
  TH1 * histogram_eta_;
  TH1 * histogram_phi_;
  TH1 * histogram_mass_;

  TH1 * histogram_msoftdrop_;

  TH1 * histogram_tau21_;
  TH1 * histogram_tau32_;

  TH1 * histogram_subjet1_pt_;
  TH1 * histogram_subjet1_eta_;
  TH1 * histogram_subjet1_BtagCSV_;
  TH1 * histogram_subjet2_pt_;
  TH1 * histogram_subjet2_eta_;
  TH1 * histogram_subjet2_BtagCSV_;
  TH1 * histogram_dR_subjets_;

  std::vector<TH1 *> histograms_;

  int idx_; // flag to select leading or subleading jet (set idx to -1 to make plots for all jets)
};

#endif
