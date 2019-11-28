#ifndef tthAnalysis_HiggsToTauTau_EvtHistManager_3l_h
#define tthAnalysis_HiggsToTauTau_EvtHistManager_3l_h

/** \class EvtHistManager_3l
 *
 * Book and fill histograms for event-level quantities in ttH multilepton analysis
 * in 3l category
 *
 * \author Christian Veelken, Tallin
 *
 */

#include "tthAnalysis/HiggsToTauTau/interface/HistManagerBase.h" // HistManagerBase

#include "tthAnalysis/HiggsToTauTau/interface/MEMOutput_3l.h" // MEMOutput_3l

class EvtHistManager_3l
  : public HistManagerBase
{
 public:
  EvtHistManager_3l(const edm::ParameterSet & cfg);
  ~EvtHistManager_3l() {}

  /// book and fill histograms
  void
  bookHistograms(TFileDirectory & dir) override;

  void
  setCRcategories(TFileDirectory & dir,
                  const std::vector<std::string> & ctrl_categories);

  void
  bookCategories(TFileDirectory & dir,
                 const std::map<std::string, std::vector<double>> & categories,
                 const std::map<std::string, std::vector<double>> & categories_TensorFlow_3l_sig_2_rest_2_th_2_withWZ,
                 const std::map<std::string, std::vector<double>> & categories_TensorFlow_3l_sig_2p5_rest_2_th_2p5_withWZ,
                 const std::map<std::string, std::vector<double>> & categories_TensorFlow_3l_sig_2_rest_2p5_th_2_withWZ
               );

  void
  fillHistograms(int numElectrons,
                 int numMuons,
                 int numHadTaus,
                 int numJets,
                 int numBJets_loose,
                 int numBJets_medium,
                 const std::string & ctrl_category,
                 double mvaOutput_3l_ttV,
                 double mvaOutput_3l_ttbar,
                 double mvaDiscr_3l,
                 double mvaOutput_category, const std::string & category,
                 double mvaOutput_category_sig_2_rest_2_th_2_withWZ,   const std::string & category_sig_2_rest_2_th_2_withWZ,
                 double mvaOutput_category_sig_2p5_rest_2_th_2p5_withWZ,   const std::string & category_sig_2p5_rest_2_th_2p5_withWZ,
                 double mvaOutput_category_sig_2_rest_2p5_th_2_withWZ,   const std::string & category_sig_2_rest_2p5_th_2_withWZ,
                 const MEMOutput_3l * memOutput_3l,
                 double evtWeight);

  const TH1 *
  getHistogram_EventCounter() const;

 private:
  int era_;
  std::vector<std::string> ctrl_cateories_;

  TH1 * histogram_numElectrons_;
  TH1 * histogram_numMuons_;
  TH1 * histogram_numHadTaus_;
  TH1 * histogram_numJets_;
  TH1 * histogram_numBJets_loose_;
  TH1 * histogram_numBJets_medium_;

  // CV: used to check loss in signal efficiency in case events with high jet and b-jet multiplicity are vetoed
  // to avoid overlap with ttH, H->bb analysis (alternative: ttH, H->bb analysis adds hadronic tau veto)
  TH2 * histogram_numBJets_loose_vs_numJets_;
  TH2 * histogram_numBJets_medium_vs_numJets_;

  TH1 * histogram_mvaOutput_3l_ttV_;
  TH1 * histogram_mvaOutput_3l_ttbar_;
  TH1 * histogram_mvaDiscr_3l_;

  std::map<std::string, TH1 *> histograms_by_category_;
  std::map<std::string, TH1 *> histograms_by_category_TensorFlow_3l_sig_2_rest_2_th_2_withWZ_;
  std::map<std::string, TH1 *> histograms_by_category_TensorFlow_3l_sig_2p5_rest_2_th_2p5_withWZ_;
  std::map<std::string, TH1 *> histograms_by_category_TensorFlow_3l_sig_2_rest_2p5_th_2_withWZ_;

  TH1 * histogram_memOutput_isValid_;
  TH1 * histogram_memOutput_errorFlag_;
  TH1 * histogram_memOutput_logWeight_ttH_;
  TH1 * histogram_memOutput_logWeight_tt_;
  TH1 * histogram_memOutput_LR_;
  TH1 * histogram_mem_logCPUTime_;
  TH1 * histogram_mem_logRealTime_;

  TH1 * histogram_ctrl_;

  TH1 * histogram_EventCounter_;
};

#endif
