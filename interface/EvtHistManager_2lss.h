#ifndef tthAnalysis_HiggsToTauTau_EvtHistManager_2lss_h
#define tthAnalysis_HiggsToTauTau_EvtHistManager_2lss_h

/** \class EvtHistManager_2lss
 *
 * Book and fill histograms for event-level quantities in ttH multilepton analysis
 * in 2lss category
 *
 * \author Christian Veelken, Tallin
 *
 */

#include "tthAnalysis/HiggsToTauTau/interface/HistManagerBase.h" // HistManagerBase

class EvtHistManager_2lss
  : public HistManagerBase
{
 public:
  EvtHistManager_2lss(const edm::ParameterSet & cfg);
  ~EvtHistManager_2lss() {}

  void
  bookHistograms(TFileDirectory & dir) override;

  void
  bookCategories(TFileDirectory & dir,
                 const std::map<std::string, std::vector<double>> &  categories,
                 const std::map<std::string, std::vector<double>> &  categories_SVA
               );

  void
  fillHistograms(int numElectrons,
                 int numMuons,
                 int numHadTaus,
                 int numJets,
                 int numBJets_loose,
                 int numBJets_medium,
                 double evtWeight,
                 double mvaOutput_2lss_ttV,
                 double mvaOutput_2lss_ttbar,
                 double mvaDiscr_2lss,
                 double mvaOutput_Hj_tagger,
                 double mvaOutput_category,
                 const std::string & category,
                 double mass_2L,
                 const std::string & category_SVA);

  const TH1 *
  getHistogram_EventCounter() const;

 private:
  int era_;

  TH1 * histogram_numElectrons_;
  TH1 * histogram_numMuons_;
  TH1 * histogram_numHadTaus_;
  TH1 * histogram_numJets_;
  TH1 * histogram_numBJets_loose_;
  TH1 * histogram_numBJets_medium_;

  // CV: used to check loss in signal efficiency in case events with
  // high jet and b-jet multiplicity are vetoed to avoid overlap with ttH, H->bb analysis
  // (alternative: ttH, H->bb analysis adds hadronic tau veto)
  TH2 * histogram_numBJets_loose_vs_numJets_;
  TH2 * histogram_numBJets_medium_vs_numJets_;

  TH1 * histogram_mvaOutput_2lss_ttV_;
  TH1 * histogram_mvaOutput_2lss_ttbar_;
  TH1 * histogram_mvaDiscr_2lss_;

  TH1 * histogram_mvaOutput_Hj_tagger_;
  std::map<std::string, TH1 *> histograms_by_category_;
  std::map<std::string, TH1 *> histograms_by_category_SVA_;

  TH1 * histogram_EventCounter_;
};

#endif
