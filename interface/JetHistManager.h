#ifndef tthAnalysis_HiggsToTauTau_JetHistManager_h
#define tthAnalysis_HiggsToTauTau_JetHistManager_h

/** \class HadTauHistManager
 *
 * Book and fill histograms for jets (b-tagged and non-b-tagged) in ttH, H->tautau analysis
 *
 * \author Christian Veelken, Tallin
 *
 */

#include "tthAnalysis/HiggsToTauTau/interface/HistManagerBase.h" // HistManagerBase
#include "tthAnalysis/HiggsToTauTau/interface/RecoJet.h"

class JetHistManager
  : public HistManagerBase
{
public:
  JetHistManager(const edm::ParameterSet & cfg);
  ~JetHistManager() {}

  /// book and fill histograms
  void
  bookHistograms(TFileDirectory & dir) override;

  void
  fillHistograms(const RecoJet & jet,
                 double evtWeight);

  void
  fillHistograms(const std::vector<const RecoJet *> & jets,
                 double evtWeight);

private:
  TH1 * histogram_pt_;
  TH1 * histogram_eta_;
  TH1 * histogram_phi_;
  TH1 * histogram_mass_;

  TH1 * histogram_BtagCSV_;

  TH1 * histogram_abs_genPdgId_;

  std::vector<TH1 *> histograms_;

  int idx_; // flag to select leading or subleading jet (set idx to -1 to make plots for all jets)
};

#endif
