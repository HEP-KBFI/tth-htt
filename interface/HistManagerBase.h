#ifndef tthAnalysis_HiggsToTauTau_HistManagerBase_h
#define tthAnalysis_HiggsToTauTau_HistManagerBase_h

/** \class HistManagerBase
 *
 * Base class for histogram booking and filling for ttH, H->tautau analysis
 *
 * \author Christian Veelken, Tallinn
 *
 */

#include "FWCore/ParameterSet/interface/ParameterSet.h" // edm::ParameterSet

#include "CommonTools/Utils/interface/TFileDirectory.h" // TFileDirectory

#include <TH1.h> // TH1D
#include <TH2.h> // TH2D
#include <TString.h> // Form
#include <TMath.h>

#include <string> // std::string
#include <vector> // std::vector

class HistManagerBase
{
 public:
  HistManagerBase(const edm::ParameterSet& cfg);
  virtual ~HistManagerBase() {}

  /// book and fill histograms
  virtual void bookHistograms(TFileDirectory& dir) = 0;
  
 protected:
  TH1* book1D(TFileDirectory& dir, const std::string& distribution, const std::string& title, int numBins, double min, double max);
  TH1* book1D(TFileDirectory& dir, const std::string& distribution, const std::string& title, int numBins, float* binning);
  TH2* book2D(TFileDirectory& dir, const std::string& distribution, const std::string& title, int numBinsX, double xMin, double xMax, int numBinsY, double yMin, double yMax);
  TH2* book2D(TFileDirectory& dir, const std::string& distribution, const std::string& title, int numBinsX, float* binningX, int numBinsY, float* binningY);

  TDirectory* createHistogramSubdirectory(TFileDirectory&);

  std::string getHistogramName(const std::string&) const;

  std::string process_;
  std::string category_;
  std::string central_or_shift_;

  std::vector<TH1*> histograms_;
};

edm::ParameterSet makeHistManager_cfg(const std::string& process, const std::string& category, const std::string& central_or_shift, int idx = -1);
edm::ParameterSet makeHistManager_cfg(const std::string& process, const std::string& category, const std::string& era, const std::string& central_or_shift, int idx = -1);

#endif // tthAnalysis_HiggsToTauTau_HistManagerBase_h
