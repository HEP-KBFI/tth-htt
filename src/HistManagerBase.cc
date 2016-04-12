#include "tthAnalysis/HiggsToTauTau/interface/HistManagerBase.h"

#include "tthAnalysis/HiggsToTauTau/interface/histogramAuxFunctions.h"

HistManagerBase::HistManagerBase(const edm::ParameterSet& cfg)
{
  process_ = cfg.getParameter<std::string>("process");
  category_ = cfg.getParameter<std::string>("category");
  central_or_shift_ = cfg.getParameter<std::string>("central_or_shift");
}

TH1* HistManagerBase::book1D(TFileDirectory& dir,
			     const std::string& distribution, const std::string& title, int numBins, double min, double max)
{
  TDirectory* subdir = createHistogramSubdirectory(dir);
  subdir->cd();
  TH1* retVal = new TH1D(getHistogramName(distribution).data(), title.data(), numBins, min, max);
  if ( !retVal->GetSumw2N() ) retVal->Sumw2();
  histograms_.push_back(retVal);
  return retVal;
}
 
TH1* HistManagerBase::book1D(TFileDirectory& dir,
			     const std::string& distribution, const std::string& title, int numBins, float* binning)
{
  TDirectory* subdir = createHistogramSubdirectory(dir);
  subdir->cd();
  TH1* retVal = new TH1D(getHistogramName(distribution).data(), title.data(), numBins, binning);
  if ( !retVal->GetSumw2N() ) retVal->Sumw2();
  histograms_.push_back(retVal);
  return retVal;
}

TH2* HistManagerBase::book2D(TFileDirectory& dir,
			     const std::string& distribution, const std::string& title, int numBinsX, double xMin, double xMax, int numBinsY, double yMin, double yMax)
{
  TDirectory* subdir = createHistogramSubdirectory(dir);
  subdir->cd();
  TH2* retVal = new TH2D(getHistogramName(distribution).data(), title.data(), numBinsX, xMin, xMax, numBinsY, yMin, yMax);
  if ( !retVal->GetSumw2N() ) retVal->Sumw2();
  histograms_.push_back(retVal);
  return retVal;
}
 
TH2* HistManagerBase::book2D(TFileDirectory& dir,
			     const std::string& distribution, const std::string& title, int numBinsX, float* binningX, int numBinsY, float* binningY)
{
  TDirectory* subdir = createHistogramSubdirectory(dir);
  subdir->cd();
  TH2* retVal = new TH2D(getHistogramName(distribution).data(), title.data(), numBinsX, binningX, numBinsY, binningY);
  if ( !retVal->GetSumw2N() ) retVal->Sumw2();
  histograms_.push_back(retVal);
  return retVal;
}

TDirectory* HistManagerBase::createHistogramSubdirectory(TFileDirectory& dir)
{
  std::string fullSubdirName = Form("%s/%s", category_.data(), process_.data());
  TDirectory* subdir = createSubdirectory_recursively(dir, fullSubdirName);
  return subdir;
}
 
std::string HistManagerBase::getHistogramName(const std::string& distribution) const
{
  std::string retVal = std::string(process_);
  if ( !(central_or_shift_ == "" || central_or_shift_ == "central") ) retVal.append("_").append(central_or_shift_);
  retVal.append("_").append(distribution);
  return retVal;
}

/**
 * @brief Build edm::ParameterSet needed to initialize HistManager classes
 * @param process MC or data sample
 *        category event category
 *        central_or_shift "central" for nominal selection, other values for systematic uncertainties
 *        idx flag to make plots for all particles (idx=-1), for leading particle (idx=0) or for subleading particle (idx=1) only
 * @return edm::ParameterSet to be passed to constructor of all classes inheriting from HistManagerBase
 */
edm::ParameterSet makeHistManager_cfg(const std::string& process, const std::string& category, const std::string& central_or_shift, int idx)
{
  edm::ParameterSet cfg;
  cfg.addParameter<std::string>("process", process);
  cfg.addParameter<std::string>("category", category);
  cfg.addParameter<std::string>("central_or_shift", central_or_shift);
  cfg.addParameter<int>("idx", idx);
  return cfg;
}
