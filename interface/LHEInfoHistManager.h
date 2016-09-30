#ifndef tthAnalysis_HiggsToTauTau_LHEInfoHistManager_h
#define tthAnalysis_HiggsToTauTau_LHEInfoHistManager_h

/** \class GenEvtHistManager
 *
 * Book and fill histograms for estimating systematic uncertainties related to scale and PDF variations in ttH, H->tautau analysis
 *
 * \author Christian Veelken, Tallin
 *
 */

#include "CommonTools/Utils/interface/TFileDirectory.h" // TFileDirectory

#include "tthAnalysis/HiggsToTauTau/interface/HistManagerBase.h" // HistManagerBase

#include "tthAnalysis/HiggsToTauTau/interface/LHEInfoReader.h" // LHEInfoReader

class LHEInfoHistManager : public HistManagerBase
{
 public:
  LHEInfoHistManager(edm::ParameterSet const& cfg);
  ~LHEInfoHistManager() {}

  /// book and fill histograms
  void bookHistograms(TFileDirectory& dir);
  void fillHistograms(const LHEInfoReader& lheInfoReader, double evtWeight = 1.);

 private:
  TH1* histogram_scaleWeights_;
  TH1* histogram_pdfWeights_;
  TFileDirectory* dir_;

  TH1* histogram_EventCounter_;

  std::vector<TH1*> histograms_;
};

#endif
