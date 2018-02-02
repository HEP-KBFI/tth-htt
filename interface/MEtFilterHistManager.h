#ifndef tthAnalysis_HiggsToTauTau_MEtFilterHistManager_h
#define tthAnalysis_HiggsToTauTau_MEtFilterHistManager_h

/** \class MEtFilterHistManager
 *
 * Book and fill histogram for MET filters in the ttH, H->tautau analysis
 *
 * \author Ram Krishna Dewanjee, Tallin
 *
 */

#include "tthAnalysis/HiggsToTauTau/interface/HistManagerBase.h" // HistManagerBase
#include "tthAnalysis/HiggsToTauTau/interface/RecoElectron.h"
#include "tthAnalysis/HiggsToTauTau/interface/RecoMuon.h"
#include "tthAnalysis/HiggsToTauTau/interface/RecoLepton.h"
#include "tthAnalysis/HiggsToTauTau/interface/jetToTauFakeRateAuxFunctions.h" // getEtaBin, getPtBin
#include "tthAnalysis/HiggsToTauTau/interface/MEtFilterReader.h"
#include "tthAnalysis/HiggsToTauTau/interface/MEtFilter.h"


class MEtFilterHistManager
  : public HistManagerBase
{
 public:
  MEtFilterHistManager(const edm::ParameterSet& cfg);
  ~MEtFilterHistManager() {}

  /// book and fill histograms
  void bookHistograms(TFileDirectory& dir);
  void fillHistograms(const MEtFilter& metFilter, double evtWeight);


 private:
  TH1* histogram_MEtFilterCounter_;
};

#endif
