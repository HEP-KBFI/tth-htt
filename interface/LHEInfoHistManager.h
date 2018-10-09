#ifndef tthAnalysis_HiggsToTauTau_LHEInfoHistManager_h
#define tthAnalysis_HiggsToTauTau_LHEInfoHistManager_h

/** \class GenEvtHistManager
 *
 * Book and fill histograms for estimating systematic uncertainties related to scale and PDF variations in ttH, H->tautau analysis
 *
 * \author Christian Veelken, Tallin
 *
 */

#include "tthAnalysis/HiggsToTauTau/interface/HistManagerBase.h" // HistManagerBase, TFileDirectory, edm::ParameterSet
#include "tthAnalysis/HiggsToTauTau/interface/LHEInfoReader.h" // LHEInfoReader

// forward declarations
class TH1;

class LHEInfoHistManager
  : public HistManagerBase
{
public:
  LHEInfoHistManager(const edm::ParameterSet & cfg);
  ~LHEInfoHistManager() {}

  /// book and fill histograms
  void
  bookHistograms(TFileDirectory & dir) override;

  void
  fillHistograms(const LHEInfoReader & lheInfoReader,
                 double evtWeight = 1.);

private:
  TH1 * histogram_scaleWeights_;
  TH1 * histogram_pdfWeights_;
  TH1 * histogram_EventCounter_;
};

#endif
