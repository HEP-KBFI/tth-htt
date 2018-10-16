#include "tthAnalysis/HiggsToTauTau/interface/plottingAuxFunctions.h"

#include "tthAnalysis/HiggsToTauTau/interface/histogramAuxFunctions.h"
#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h" // cmsException()

#include <FWCore/PythonParameterSet/interface/MakeParameterSets.h>

#include <TH1.h>
#include <TDirectory.h>
#include <TMath.h>
#include <TPRegexp.h>
#include <TObjString.h>
#include <TObjArray.h>

#include <boost/algorithm/string/replace.hpp> // boost::replace_all_copy()

#include <cassert> // assert()
#include <iostream> // std::cout

typedef std::vector<std::string> vstring;

histogramEntryType::histogramEntryType(const std::string & process,
                                       TH1 * histogram)
  : process_(process),
    histogram_(histogram)
{}

plotEntryType::plotEntryType(const edm::ParameterSet & cfg)
  : histogramName_(cfg.getParameter<std::string>("histogramName"))
  , outputFileName_(cfg.exists("outputFileName") ? cfg.getParameter<std::string>("outputFileName") : histogramName_)
  , xMin_(cfg.exists("xMin") ? cfg.getParameter<double>("xMin") : -1.)
  , xMax_(cfg.exists("xMax") ? cfg.getParameter<double>("xMax") : -1.)
  , xAxisTitle_(cfg.getParameter<std::string>("xAxisTitle"))
  , xAxisOffset_( cfg.exists("xAxisOffset") ? cfg.getParameter<double>("xAxisOffset") : 1.25)
  , yMin_(cfg.exists("yMin") ? cfg.getParameter<double>("yMin") : -1.)
  , yMax_(cfg.exists("yMax") ? cfg.getParameter<double>("yMax") : -1.)
  , yAxisTitle_(cfg.getParameter<std::string>("yAxisTitle"))
  , yAxisOffset_( cfg.exists("yAxisOffset") ? cfg.getParameter<double>("yAxisOffset") : 1.15)
  , explicitBinning_( cfg.exists("explicitBinning") ? cfg.getParameter<std::vector<double>>("explicitBinning") : std::vector<double>() )
{
  if(cfg.exists("keepBlinded"))
  {
    const vstring keepBlinded_string = cfg.getParameter<vstring>("keepBlinded");
    TPRegexp regexpParser_range("([0-9.e+/-]+):([0-9.e+/-]+)");
    for(const std::string & keepBlinded_it: keepBlinded_string)
    {
      const TObjArray * const subStrings = regexpParser_range.MatchS(keepBlinded_it.data());
      if(subStrings->GetEntries() == 3)
      {
        const double range_begin = (static_cast<TObjString *>(subStrings->At(1)))->GetString().Atof();
        const double range_end   = (static_cast<TObjString *>(subStrings->At(2)))->GetString().Atof();
        keepBlinded_.push_back(std::make_pair(range_begin, range_end));
      }
      delete subStrings;
    }
  }
}

bool
plotEntryType::hasExplicitBinning() const
{
  return ! explicitBinning_.empty();
}

//-----------------------------------------------------------------------------
void
parseValue_and_Uncertainty(const std::string & valueErr_string,
                           double & value,
                           double & err)
{
  TPRegexp regexpParser("([0-9.eE+-]+)\\s*\\+/-\\s*([0-9.eE+-]+)");
  const TObjArray * const subStrings = regexpParser.MatchS(valueErr_string.data());
  if(subStrings->GetEntries() == 3)
  {
    value = (static_cast<TObjString *>(subStrings->At(1)))->GetString().Atof();
    err   = (static_cast<TObjString *>(subStrings->At(2)))->GetString().Atof();
    delete subStrings;
  }
  else
  {
    throw cmsException(__func__, __LINE__) << "Failed to parse string = '" << valueErr_string << "' !!\n";
  }
}

TH1 *
getHistogram_wrapper(const TDirectory * dir,
                     const std::string & process,
                     const std::string & histogramName,
                     const std::string & central_or_shift,
                     bool enableException)
{
  const std::string histogramName_full = boost::replace_all_copy(histogramName, "$PROCESS", process);
  const std::size_t idx = histogramName_full.find_last_of("/");
  if(idx == std::string::npos)
  {
    throw cmsException(__func__, __LINE__)
      << "Expected slash in histogramName_full = '" << histogramName_full << '\'';
  }

  const std::string subdirName = std::string(histogramName_full, 0, idx);
  const std::string histogramName_wrt_subdir = std::string(histogramName_full, idx + 1);
  TH1 * histogram = getHistogram(dir, subdirName, histogramName_wrt_subdir, central_or_shift, enableException, true);
  return histogram;
}

void
printHistogram(const TH1 * histogram)
{
  std::cout << "<printHistogram>:\nname = " << histogram->GetName() << '\n';
  const int numBins = histogram->GetNbinsX();
  for(int iBin = 1; iBin <= numBins; ++iBin)
  {
    std::cout << " bin #" << iBin << ": " << histogram->GetBinContent(iBin)
              << " +/- " << histogram->GetBinError(iBin) << '\n';
  }
  std::cout << "integral = " << histogram->Integral() << '\n';
}

constexpr double
square(double x)
{
  return x * x;
}

HistogramManager::HistogramManager(const vstring & processesBackground,
                                   const std::string & processSignal,
                                   const vstring & categories,
                                   const edm::ParameterSet & cfg)
  : currentDir_(nullptr),
    isUpToDate_(false),
    histogram_uncertainty_(nullptr)
{
  processes_ = processesBackground;
  if ( processSignal != "" ) processes_.push_back(processSignal);

  const edm::ParameterSet cfgNormalization = cfg.getParameter<edm::ParameterSet>("normalization");
  for(const std::string & process: processes_)
  {
    for(const std::string & category: categories)
    {
      normEntryType processEntry;
      processEntry.process_  = process;
      processEntry.category_ = category;
      parseValue_and_Uncertainty(
        cfgNormalization.getParameter<std::string>(process), processEntry.sf_, processEntry.sfErr_
      );
      normalizationValues_and_Uncertainties_[process][category] = processEntry;
    }
  }

  const edm::ParameterSet cfgShape = cfg.getParameter<edm::ParameterSet>("shape");
  sysShifts_ = cfgShape.getParameterNamesForType<std::string>();
  for(const std::string & sysShift: sysShifts_)
  {
    shapeEntryType sysShiftEntry;
    sysShiftEntry.sysShift_ = sysShift;
    parseValue_and_Uncertainty(
      cfgShape.getParameter<std::string>(sysShift), sysShiftEntry.value_, sysShiftEntry.err_
    );
    shapeValues_and_Uncertainties_[sysShift] = sysShiftEntry;
  }
}

void
HistogramManager::setDirectory(TDirectory * dir)
{
  currentDir_ = dir;
  isUpToDate_ = false;
}

void
HistogramManager::setCategory(const std::string & category)
{
  currentCategory_ = category;
  isUpToDate_ = false;
}

void
HistogramManager::setHistogram(const std::string & histogramName)
{
  currentHistogramName_ = histogramName;
  isUpToDate_ = false;
}

TH1 *
HistogramManager::getHistogramPrefit(const std::string & process,
                                     bool enableException)
{
  if(! isUpToDate_)
  {
    update();
  }

  TH1 * histogram = nullptr;
  if(histograms_prefit_.count(process))
  {
    histogram = histograms_prefit_[process];
  }
  if(enableException && ! histogram)
  {
    throw cmsException(this, __func__)
      << "Failed to find prefit histogram for process = " << process;
  }

  return histogram;
}

TH1 *
HistogramManager::getHistogramPostfit(const std::string & process,
                                      bool enableException)
{
  if(! isUpToDate_)
  {
    update();
  }

  TH1 * histogram = nullptr;
  if(histograms_postfit_.count(process))
  {
    histogram = histograms_postfit_[process];
  }
  if(enableException && ! histogram)
  {
    throw cmsException(this, __func__)
      << "Failed to find postfit histogram for process = " << process;
  }
  return histogram;
}

TH1 *
HistogramManager::getHistogramUncertainty()
{
  if(! isUpToDate_)
  {
    update();
  }
  return histogram_uncertainty_;
}

void
HistogramManager::getSF(const std::string & process,
                        double & sf,
                        double & sfErr) const
{
  assert(normalizationValues_and_Uncertainties_.count(process));
  const stringToNormEntryTypeMap & entryMap = normalizationValues_and_Uncertainties_.at(process);
  assert(entryMap.count(currentCategory_));
  const normEntryType & entryType = entryMap.at(currentCategory_);
  sf    = entryType.sf_;
  sfErr = entryType.sfErr_;
}

void
HistogramManager::update()
{
  for(const std::string & process: processes_)
  {
    std::cout << "process = " << process << '\n';

    TH1 * histogram_prefit = getHistogram_wrapper(currentDir_, process, currentHistogramName_, "central", true);
    histograms_prefit_[process] = histogram_prefit;

    for(const std::string & sysShift: sysShifts_)
    {
      const std::string sysShiftUp = Form("%sUp", sysShift.data());
      TH1 * histogram_sysShiftUp = getHistogram_wrapper(currentDir_, process, currentHistogramName_, sysShiftUp, false);
      if(histogram_sysShiftUp)
      {
        histograms_sysShifts_[process][sysShiftUp] = histogram_sysShiftUp;
      }

      const std::string sysShiftDown = Form("%sDown", sysShift.data());
      TH1 * histogram_sysShiftDown = getHistogram_wrapper(currentDir_, process, currentHistogramName_, sysShiftDown, false);
      if(histogram_sysShiftDown)
      {
        histograms_sysShifts_[process][sysShiftDown] = histogram_sysShiftDown;
      }
    } // sysShift

    const std::string histogramName_postfit = Form("%s_postfit", histogram_prefit->GetName());
    TH1 * histogram_postfit = static_cast<TH1 *>(histogram_prefit->Clone(histogramName_postfit.data()));
    if(! histogram_postfit->GetSumw2N())
    {
      histogram_postfit->Sumw2();
    }

    if(normalizationValues_and_Uncertainties_.count(process))
    {
      double sf, sfErr;
      getSF(process, sf, sfErr);
      std::cout << "--> scaling histogram = " << histogram_postfit->GetName() << " by factor = " << sf << '\n';
      histogram_postfit->Scale(sf);
    }

    for(const std::string & sysShift: sysShifts_)
    {
      const std::string sysShiftUp   = Form("%sUp", sysShift.data());
      const std::string sysShiftDown = Form("%sDown", sysShift.data());

      if(histograms_sysShifts_.find(process) != histograms_sysShifts_.end() &&
         histograms_sysShifts_.at(process).count(sysShiftUp) &&
         histograms_sysShifts_.at(process).count(sysShiftDown))
      {
        const double sysShift_value = shapeValues_and_Uncertainties_[sysShift].value_;
        TH1 * histogram_sysShift = nullptr;

        if(sysShift_value > 0.)
        {
          histogram_sysShift = histograms_sysShifts_[process][sysShiftUp];
        }
        else if(sysShift_value < 0.)
        {
          histogram_sysShift = histograms_sysShifts_[process][sysShiftDown];
        }

        if(histogram_sysShift)
        {
          const double absSysShift_value = TMath::Abs(sysShift_value);
          TH1 * histogram_prefit_central = histograms_prefit_[process];
          assert(histogram_prefit_central);

          int numBins = histogram_postfit->GetNbinsX();
          for(int iBin = 1; iBin <= numBins; ++iBin)
          {
            double binContent_central  = histogram_prefit_central->GetBinContent(iBin);
            double binContent_sysShift = histogram_sysShift->GetBinContent(iBin);
            double binContent_postfit  = histogram_postfit->GetBinContent(iBin);

            binContent_postfit *= (binContent_central + absSysShift_value * (binContent_sysShift - binContent_central));
            if(binContent_postfit < 0.)
            {
              binContent_postfit = 0.;
            }
            histogram_postfit->SetBinContent(iBin, binContent_postfit);
          }
        } // histogram_sysShift
      } // if sysShiftUp, sysShiftDown
    } // sysShift

    delete histograms_postfit_[process];
    histograms_postfit_[process] = histogram_postfit;
  } // process

  delete histogram_uncertainty_;
  const std::string histogramName_uncertainty = Form("%s_uncertainty", currentHistogramName_.data());
  histogram_uncertainty_ = static_cast<TH1 *>(histograms_prefit_.cbegin()->second->Clone(histogramName_uncertainty.data()));
  histogram_uncertainty_->Reset();
  if(! histogram_uncertainty_->GetSumw2N())
  {
    histogram_uncertainty_->Sumw2();
  }

  const int numBins = histogram_uncertainty_->GetNbinsX();
  for(int iBin = 1; iBin <= numBins; ++iBin)
  {
    double binContent_uncertainty = 0.;
    double binErr2_uncertainty = 0.;
    for(const std::string & process: processes_)
    {
      TH1 * histogram_prefit = histograms_prefit_[process];
      assert(histogram_prefit);
      const double binContent_prefit = histogram_prefit->GetBinContent(iBin);

      TH1 * histogram_postfit = histograms_postfit_[process];
      assert(histogram_postfit);
      const double binContent_postfit = histogram_postfit->GetBinContent(iBin);

      const double binErr_postfit = histogram_postfit->GetBinError(iBin);
      binContent_uncertainty += binContent_postfit;
      binErr2_uncertainty    += square(binErr_postfit); // statistical uncertainty of background process in given bin

      double sf, sfErr;
      getSF(process, sf, sfErr);
      if(sf > 0.)
      {
        binErr2_uncertainty += square(binContent_postfit*(sfErr/sf)); // systematic uncertainty on background normalization
      }

      for(const std::string & sysShift: sysShifts_)
      {
        const double sysShift_value = shapeValues_and_Uncertainties_[sysShift].value_;

        TH1 * histogram_sysShift = nullptr;
        if ( sysShift_value > 0. )
        {
          const std::string sysShiftUp = Form("%sUp", sysShift.data());
          if(histograms_sysShifts_.at(process).count(sysShiftUp))
          {
            histogram_sysShift = histograms_sysShifts_[process][sysShiftUp];
          }
        }
        else if(sysShift_value < 0.)
        {
          const std::string sysShiftDown = Form("%sDown", sysShift.data());
          if(histograms_sysShifts_.at(process).count(sysShiftDown))
          {
            histogram_sysShift = histograms_sysShifts_[process][sysShiftDown];
          }
        }

        if(histogram_sysShift)
        {
          const double sysShift_err = shapeValues_and_Uncertainties_[sysShift].err_;
          const double binContent_sysShift = histogram_sysShift->GetBinContent(iBin);

          if(binContent_prefit > 0.)
          {
            binErr2_uncertainty += square(
              binContent_postfit * sysShift_err * (binContent_sysShift - binContent_prefit) / binContent_prefit
            ); // systematic uncertainty on background shape
          }
          else if( binContent_postfit > 0.)
          {
            binErr2_uncertainty += square(
              sysShift_err * (binContent_sysShift - binContent_prefit)
            );
          }
        }
      } // sysShift
    } // process

    histogram_uncertainty_->SetBinContent(iBin, binContent_uncertainty);
    assert(binErr2_uncertainty >= 0.);
    histogram_uncertainty_->SetBinError(iBin, TMath::Sqrt(binErr2_uncertainty));
  } // iBin

  isUpToDate_ = true;
}
//-----------------------------------------------------------------------------

TH1 *
divideHistogramByBinWidth(TH1 * histogram)
{
  const std::string histogramDensityName = Form("%s_density", histogram->GetName());
  TH1 * histogramDensity = (TH1*)histogram->Clone(histogramDensityName.data());
  const TAxis * const xAxis = histogram->GetXaxis();

  const int numBins = xAxis->GetNbins();
  for(int iBin = 1; iBin <= numBins; ++iBin)
  {
    const double binContent = histogram->GetBinContent(iBin);
    const double binError   = histogram->GetBinError(iBin);
    const double binWidth   = xAxis->GetBinWidth(iBin);
    histogramDensity->SetBinContent(iBin, binContent / binWidth);
    histogramDensity->SetBinError(iBin, binError / binWidth);
  }
  return histogramDensity;
}

std::pair<double, double>
compYmin_and_YmaxForClearance(TH1 * histogram,
			      double legendPosX,
			      double legendPosY,
			      double labelPosY,
			      bool useLogScale,
			      double numOrdersOfMagnitude)
{
  //std::cout << "<compYmaxForClearance>:" << std::endl;
  //std::cout << " legendPos: x = " << legendPosX << ", y = " << legendPosY << std::endl;
  //std::cout << " labelPos: x = " << labelPosY << std::endl;
  const TAxis * const xAxis = histogram->GetXaxis();
  const double xMin = xAxis->GetXmin();
  const double xMax = xAxis->GetXmax();
  const double dX = 0.05;
  const double dY = 0.05;
  const double x12 = xMin + (xMax - xMin) * legendPosX;
  //std::cout << "x12 = " << x12 << std::endl;
  double maxBinContent1 = 0.;
  double maxBinContent2 = 0.;

  const int numBins = xAxis->GetNbins();
  for(int iBin = 1; iBin <= numBins; ++iBin)
  {
    const double binContent = histogram->GetBinContent(iBin);
    if(xAxis->GetBinLowEdge(iBin) < (x12 + dX))
    {
      if(binContent > maxBinContent1)
      {
        maxBinContent1 = binContent;
      }
    }
    if(xAxis->GetBinUpEdge(iBin) > (x12 - dX))
    {
      if(binContent > maxBinContent2)
      {
        maxBinContent2 = binContent;
      }
    }
  }
  //std::cout << "maxBinContent1 = " << maxBinContent1 << ", maxBinContent2 = " << maxBinContent2 << std::endl;

  double yMinForClearance = 0.;
  double yMaxForClearance = 0.;
  if(useLogScale)
  {
    const double maxBinContent = TMath::Max(maxBinContent1, maxBinContent2);
    double logYmin = TMath::Log10(maxBinContent) - numOrdersOfMagnitude;
    //std::cout << "logYmin = " << logYmin << std::endl;

    double logYmaxForClearance1 = 0.;
    if(maxBinContent1 > 0. && maxBinContent > 0.)
    {
      logYmaxForClearance1 = (TMath::Log10(maxBinContent1) - logYmin)/(labelPosY - dY);
    }

    double logYmaxForClearance2 = 0.;
    if(maxBinContent2 > 0. && maxBinContent > 0.)
    {
      logYmaxForClearance2 = (TMath::Log10(maxBinContent2) - logYmin)/(legendPosY - dY);      
    }
    //std::cout << "logYmaxForClearance1 = " << logYmaxForClearance1 << ", logYmaxForClearance2 = " << logYmaxForClearance2 << std::endl;
    const double logYmaxForClearance = TMath::Max(logYmaxForClearance1, logYmaxForClearance2);
    yMinForClearance = TMath::Power(10., logYmin);
    yMaxForClearance = TMath::Power(10., logYmaxForClearance) + TMath::Power(10., logYmin);
  }
  else
  {
    yMinForClearance = 0.;
    yMaxForClearance = TMath::Max(maxBinContent1 / (labelPosY - dY), maxBinContent2 / (legendPosY - dY));
  }
  //std::cout << "yMaxForClearance = " << yMaxForClearance << std::endl;
  return std::pair<double, double>(yMinForClearance, yMaxForClearance);
}

std::vector<plotEntryType *>
readDistributions(const edm::VParameterSet & cfgDistributions)
{
  std::vector<plotEntryType *> distributions;
  for(const edm::ParameterSet & cfgDistribution: cfgDistributions)
  {
    const TString histogramName = cfgDistribution.getParameter<std::string>("histogramName").data();
    const TObjArray * const histogramName_parts = histogramName.Tokenize("/");
    const int numParts = histogramName_parts->GetEntries();
    std::string histogramName_wrt_subdir;

    for(int idxPart = 0; idxPart < numParts; ++idxPart)
    {
      const TObjString * const part = dynamic_cast<TObjString *>(histogramName_parts->At(idxPart));
      assert(part);

      if(part->GetString().Contains("$"))
      {
        continue;
      }
      if(histogramName_wrt_subdir.length() > 0)
      {
        histogramName_wrt_subdir.append("_");
      }
      histogramName_wrt_subdir.append(part->GetString().Data());
    }

    edm::ParameterSet cfgDistribution_modified(cfgDistribution);
    cfgDistribution_modified.addParameter<std::string>("outputFileName", histogramName_wrt_subdir);

    plotEntryType * distribution = new plotEntryType(cfgDistribution_modified);
    distributions.push_back(distribution);

    delete histogramName_parts;
  }
  return distributions;
}
