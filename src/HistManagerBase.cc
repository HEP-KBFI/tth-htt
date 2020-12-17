#include <iostream>

#include "tthAnalysis/HiggsToTauTau/interface/HistManagerBase.h"

#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h" // cmsException()
#include "tthAnalysis/HiggsToTauTau/interface/histogramAuxFunctions.h" // createSubdirectory_recursively()

#include <TH2.h> // TH2D

std::map<TDirectory *, std::vector<TH1 *>> HistManagerBase::gHistograms_;

HistManagerBase::HistManagerBase(const edm::ParameterSet & cfg)
  : process_(cfg.getParameter<std::string>("process"))
  , category_(cfg.getParameter<std::string>("category"))
  , central_or_shift_(cfg.getParameter<std::string>("central_or_shift"))
{}

void
HistManagerBase::writeHistograms()
{
  for ( std::map<TDirectory *, std::vector<TH1 *>>::iterator directory = gHistograms_.begin(); directory != gHistograms_.end(); ++directory )
  {
    assert(directory->first);
    directory->first->cd();
    for ( std::vector<TH1 *>::iterator histogram = directory->second.begin(); histogram != directory->second.end(); ++histogram ) 
    {
      assert(*histogram);
      (*histogram)->Write();
    }
  }
}

TH1 *
HistManagerBase::book1D(TDirectory * dir,
                        const std::string & distribution,
                        const std::string & title,
                        int numBins,
                        double min,
                        double max)
{
  TH1 * retVal = nullptr;
  const bool doBookHistogram = checkOptionIsSelected(distribution);
  if(doBookHistogram)
    {
      dir->cd();
      retVal = new TH1D(getHistogramName(distribution).data(), title.data(), numBins, min, max);
      if(! retVal->GetSumw2N())
	{
	  retVal->Sumw2();
	}
      histograms_.push_back(retVal);
      gHistograms_[dir].push_back(retVal);
    }
  return retVal;
}

TH1 *
HistManagerBase::book1D(TFileDirectory & dir,
                        const std::string & distribution,
                        const std::string & title,
                        int numBins,
                        double min,
                        double max)
{
  TDirectory * const subdir = createHistogramSubdirectory(dir);
  return book1D(subdir, distribution, title, numBins, min, max);
}

TH1 *
HistManagerBase::book1D(TFileDirectory & dir,
                        const std::string & distribution,
                        int numBins,
                        double min,
                        double max)
{
  return this->book1D(dir, distribution, distribution, numBins, min, max);
}


TH1 *
HistManagerBase::book1D(TFileDirectory & dir,
                        const std::string & distribution,
                        const std::string & title,
                        int numBins,
                        const float * binning)
{
  TH1 * retVal = nullptr;
  const bool doBookHistogram = checkOptionIsSelected(distribution);
  if(doBookHistogram)
    {
      TDirectory * const subdir = createHistogramSubdirectory(dir);
      subdir->cd();
      retVal = new TH1D(getHistogramName(distribution).data(), title.data(), numBins, binning);
      if(! retVal->GetSumw2N())
	{
	  retVal->Sumw2();
	}
      histograms_.push_back(retVal);
      gHistograms_[subdir].push_back(retVal);
    }
  return retVal;
}

TH1 *
HistManagerBase::book1D(TFileDirectory & dir,
                        const std::string & distribution,
                        int numBins,
                        const float * binning)
{
  return this->book1D(dir, distribution, distribution, numBins, binning);
}

TH1 *
HistManagerBase::book1D(TFileDirectory & dir,
                        const std::string & distribution,
                        const std::string & title,
                        int numBins,
                        const double * binning)
{
  TH1 * retVal = nullptr;
  const bool doBookHistogram = checkOptionIsSelected(distribution);
  if(doBookHistogram)
  {
    TDirectory * const subdir = createHistogramSubdirectory(dir);
    subdir->cd();
    retVal = new TH1D(getHistogramName(distribution).data(), title.data(), numBins, binning);
    if(! retVal->GetSumw2N())
    {
      retVal->Sumw2();
    }
    histograms_.push_back(retVal);
    gHistograms_[subdir].push_back(retVal);
  }
  return retVal;
}

TH1 *
HistManagerBase::book1D(TFileDirectory & dir,
                        const std::string & distribution,
                        int numBins,
                        const double * binning)
{
  return this->book1D(dir, distribution, distribution, numBins, binning);
}

void
HistManagerBase::book1D(TDirectory * dir,
                        TH1 * histogram)
{
  histograms_.push_back(histogram);
  gHistograms_[dir].push_back(histogram);
}

TH2 *
HistManagerBase::book2D(TFileDirectory & dir,
                        const std::string & distribution,
                        const std::string & title,
                        int numBinsX,
                        double xMin,
                        double xMax,
                        int numBinsY,
                        double yMin,
                        double yMax)
{
  TH2 * retVal = nullptr;
  const bool doBookHistogram = checkOptionIsSelected(distribution);
  if(doBookHistogram)
  {
    TDirectory * const subdir = createHistogramSubdirectory(dir);
    subdir->cd();
    retVal = new TH2D(getHistogramName(distribution).data(), title.data(), numBinsX, xMin, xMax, numBinsY, yMin, yMax);
    if(! retVal->GetSumw2N())
    {
      retVal->Sumw2();
    }
    histograms_2d_.push_back(retVal);
    gHistograms_[subdir].push_back(retVal);
  }
  return retVal;
}

TH2 *
HistManagerBase::book2D(TFileDirectory & dir,
                        const std::string & distribution,
                        int numBinsX,
                        double xMin,
                        double xMax,
                        int numBinsY,
                        double yMin,
                        double yMax)
{
  return this->book2D(dir, distribution, distribution, numBinsX, xMin, xMax, numBinsY, yMin, yMax);
}

TH2 *
HistManagerBase::book2D(TFileDirectory & dir,
                        const std::string & distribution,
                        const std::string & title,
                        int numBinsX,
                        const float * binningX,
                        int numBinsY,
                        const float * binningY)
{
  TH2 * retVal = nullptr;
  const bool doBookHistogram = checkOptionIsSelected(distribution);
  if(doBookHistogram)
  {
    TDirectory * const subdir = createHistogramSubdirectory(dir);
    subdir->cd();
    retVal = new TH2D(getHistogramName(distribution).data(), title.data(), numBinsX, binningX, numBinsY, binningY);
    if(! retVal->GetSumw2N())
    {
      retVal->Sumw2();
    }
    histograms_2d_.push_back(retVal);
    gHistograms_[subdir].push_back(retVal);
  }
  return retVal;
}

TH2 *
HistManagerBase::book2D(TFileDirectory & dir,
                        const std::string & distribution,
                        int numBinsX,
                        const float * binningX,
                        int numBinsY,
                        const float * binningY)
{
  return this->book2D(dir, distribution, distribution, numBinsX, binningX, numBinsY, binningY);
}

TH2 *
HistManagerBase::book2D(TFileDirectory & dir,
                        const std::string & distribution,
                        const std::string & title,
                        int numBinsX,
                        const double * binningX,
                        int numBinsY,
                        const double * binningY)
{
  TH2 * retVal = nullptr;
  const bool doBookHistogram = checkOptionIsSelected(distribution);
  if(doBookHistogram)
  {
    TDirectory * const subdir = createHistogramSubdirectory(dir);
    subdir->cd();
    retVal = new TH2D(getHistogramName(distribution).data(), title.data(), numBinsX, binningX, numBinsY, binningY);
    if(! retVal->GetSumw2N())
    {
      retVal->Sumw2();
    }
    histograms_2d_.push_back(retVal);
    gHistograms_[subdir].push_back(retVal);
  }
  return retVal;
}

TH2 *
HistManagerBase::book2D(TFileDirectory & dir,
                        const std::string & distribution,
                        int numBinsX,
                        const double * binningX,
                        int numBinsY,
                        const double * binningY)
{
  return this->book2D(dir, distribution, distribution, numBinsX, binningX, numBinsY, binningY);
}

void
HistManagerBase::book2D(TDirectory * dir,
                        TH2 * histogram)
{
  histograms_2d_.push_back(histogram);
  gHistograms_[dir].push_back(histogram);
}

bool 
HistManagerBase::checkOptionIsSelected(const std::string & distribution) const
{
  bool isSelected = false;
  const auto central_or_shiftOptions_iter = central_or_shiftOptions_.find(distribution);
  if(central_or_shiftOptions_iter != central_or_shiftOptions_.end())
  {
    for(const std::string & central_or_shiftOption: central_or_shiftOptions_iter->second)
    {
      if(central_or_shiftOption == "*")
      {
        isSelected = true;
        break;
      }
      if((central_or_shiftOption == "central" || central_or_shiftOption.empty()) &&
         (central_or_shift_      == "central" || central_or_shift_.empty())       )
      {
        isSelected = true;
        break;
      }
    }
  }
  else
  {
    throw cmsException(this, __func__, __LINE__)
      << "Failed to find distribution = '" << distribution << "' in histogramOptions"
    ;
  }
  return isSelected;
}

TDirectory *
HistManagerBase::createHistogramSubdirectory(TFileDirectory & dir)
{
  const std::string fullSubdirName = category_.empty() ?
    Form("%s", process_.data())                        :
    Form("%s/%s", category_.data(), process_.data())
  ;
  TDirectory * const subdir = createSubdirectory_recursively(dir, fullSubdirName, false);
  return subdir;
}
 
std::string
HistManagerBase::getHistogramName(const std::string & distribution) const
{
  std::string retVal = "";
  if(! (central_or_shift_.empty() || central_or_shift_ == "central"))
  {
    retVal = central_or_shift_;
  }
  if(! retVal.empty())
  {
    retVal.append("_");
  }
  retVal.append(distribution);
  return retVal;
}

/**
 * @brief Build edm::ParameterSet needed to initialize HistManager classes
 * @param process MC or data sample
 *        category event category
 *        era data-taking period
 *        central_or_shift "central" for nominal selection, other values for systematic uncertainties
 *        option flag to book & fill either full or minimal set of histograms (to reduce memory consumption of hadd jobs)
 *        idx flag to make plots for all particles (idx=-1), for leading particle (idx=0) or for subleading particle (idx=1) only
 * @return edm::ParameterSet to be passed to constructor of all classes inheriting from HistManagerBase
 */
edm::ParameterSet
makeHistManager_cfg(const std::string & process,
                    const std::string & category,
                    const std::string & era,
                    const std::string & central_or_shift,
                    int idx)
{
  edm::ParameterSet cfg;
  cfg.addParameter<std::string>("process", process);
  cfg.addParameter<std::string>("category", category);
  cfg.addParameter<std::string>("era", era);
  cfg.addParameter<std::string>("central_or_shift", central_or_shift);
  cfg.addParameter<int>("idx", idx);
  return cfg;
}

edm::ParameterSet
makeHistManager_cfg(const std::string & process,
                    const std::string & category,
                    const std::string & era,
                    const std::string & central_or_shift,
                    const std::string & option,
                    int idx)
{
  edm::ParameterSet cfg = makeHistManager_cfg(process, category, era, central_or_shift, idx);
  cfg.addParameter<std::string>("option", option);
  return cfg;
}
