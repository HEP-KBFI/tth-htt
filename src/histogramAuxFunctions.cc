#include "tthAnalysis/HiggsToTauTau/interface/histogramAuxFunctions.h"

#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h" // cmsException()

#include "tthAnalysis/HiggsToTauTau/interface/generalAuxFunctions.h" // format_vdouble

#include <TH2.h> // TH2

#include <iostream> // std::cout
#include <cmath> // std::sqrt(), std::log()
#include <cassert> // assert()

namespace
{
  std::string
  removeLastSlash(const std::string & dirName)
  {
    const std::size_t dirNameLength_minus1 = dirName.length() - 1;
    return dirName.find_last_of('/') == dirNameLength_minus1 ?
      std::string(dirName, 0, dirNameLength_minus1)          :
      dirName
    ;
  }

  template <typename T,
            typename = typename std::enable_if<std::is_arithmetic<T>::value>>
  /**
   * @brief Constrains value between the lower and the upper bound (both included)
   * @param value      The value to be constrained
   * @param lowerBound The lower bound
   * @param upperBound The upper bound
   * @return Value between the lower and the upper bound (lowerBound <= value <= upperBound)
   */
  T
  constrainValue(T value,
                 T lowerBound,
                 T upperBound)
  {
    assert(lowerBound <= upperBound);
    value = std::max(value, lowerBound);
    value = std::min(value, upperBound);
    return value;
  }

  template <typename T,
            typename = typename std::enable_if<std::is_arithmetic<T>::value>>
  T constexpr
  square(T x)
  {
    return x * x;
  }

  template <typename T,
            typename... Args,
            typename = typename std::enable_if<std::is_arithmetic<T>::value>>
  T constexpr
  square(T x,
         Args... rest)
  {
    return square(x) + square(rest...);
  }

  template<typename... Args>
  double
  quad(Args... args)
  {
    return std::sqrt(square(args...));
  }
}

void
fill(TH1 * histogram,
     double x,
     double evtWeight,
     double evtWeightErr)
{
  if(!histogram) return;
  const TAxis * const xAxis = histogram->GetXaxis();
  const int bin     = xAxis->FindBin(x);
  const int numBins = xAxis->GetNbins();
  if(! (bin >= 1 && bin <= numBins))
  {
    return;
  }

  const double binContent = histogram->GetBinContent(bin);
  const double binError   = histogram->GetBinError(bin);
  histogram->SetBinContent(bin, binContent + evtWeight);
  histogram->SetBinError(bin, quad(binError, evtWeight, evtWeightErr));
}

void
fillWithOverFlow(TH1 * histogram,
                 double x,
                 double evtWeight,
                 double evtWeightErr)
{
  if(!histogram) return;
  const TAxis * const xAxis = histogram->GetXaxis();
  const int bin = constrainValue(xAxis->FindBin(x), 1, xAxis->GetNbins());
  const double binContent = histogram->GetBinContent(bin);
  const double binError   = histogram->GetBinError(bin);
  histogram->SetBinContent(bin, binContent + evtWeight);
  histogram->SetBinError(bin, quad(binError, evtWeight, evtWeightErr));
}

void
fill2d(TH2 * histogram,
       double x,
       double y,
       double evtWeight,
       double evtWeightErr)
{
  if(!histogram) return;
  const TAxis * const xAxis = histogram->GetXaxis();
  const int binX     = xAxis->FindBin(x);
  const int numBinsX = xAxis->GetNbins();
  if(! (binX >= 1 && binX <= numBinsX))
  {
    return;
  }

  const TAxis * const yAxis = histogram->GetYaxis();
  const int binY     = yAxis->FindBin(y);
  const int numBinsY = yAxis->GetNbins();
  if(! (binY >= 1 && binY <= numBinsY))
  {
    return;
  }

  const double binContent = histogram->GetBinContent(binX, binY);
  const double binError   = histogram->GetBinError(binX, binY);
  histogram->SetBinContent(binX, binY, binContent + evtWeight);
  histogram->SetBinError(binX, binY, quad(binError, evtWeight, evtWeightErr));
}

void
fillWithOverFlow2d(TH2 * histogram,
                   double x,
                   double y,
                   double evtWeight,
                   double evtWeightErr)
{
  if(!histogram) return;
  const TAxis * const xAxis = histogram->GetXaxis();
  const int binX = constrainValue(xAxis->FindBin(x), 1, xAxis->GetNbins());

  const TAxis * const yAxis = histogram->GetYaxis();
  const int binY = constrainValue(yAxis->FindBin(y), 1, yAxis->GetNbins());

  const double binContent = histogram->GetBinContent(binX, binY);
  const double binError   = histogram->GetBinError(binX, binY);
  histogram->SetBinContent(binX, binY, binContent + evtWeight);
  histogram->SetBinError(binX, binY, quad(binError, evtWeight, evtWeightErr));
}

//
//-------------------------------------------------------------------------------
//

double
getLogWeight(double weight)
{
  return weight > 0. ? std::log(weight) : -1.e+6;
}

//
//-------------------------------------------------------------------------------
//

void
checkCompatibleBinning(const TH1 * histogram1,
                       const TH1 * histogram2)
{
  if(histogram1 && histogram2)
  {
    int dimension1 = histogram1->GetDimension();
    int dimension2 = histogram2->GetDimension();
    if(dimension1 != dimension2)
    {
      throw cmsException(__func__, __LINE__)
        << "Histograms " << histogram1->GetName() << " and " << histogram2->GetName()
        << " have incompatible dimension (dimension: histogram1 = "
        << dimension1 << ", histogram2 = " << dimension2 << ')';
    }
    if(histogram1->GetNbinsX() != histogram2->GetNbinsX())
    {
      throw cmsException(__func__, __LINE__)
        << "Histograms " << histogram1->GetName() << " and " << histogram2->GetName()
        << " have incompatible x-axis binning !!\n (NbinsX: histogram1 = "
        << histogram1->GetNbinsX() << ", histogram2 = " << histogram2->GetNbinsX() << ')';
    }
    const TAxis * const xAxis1 = histogram1->GetXaxis();
    const TAxis * const xAxis2 = histogram2->GetXaxis();
    const int numBinsX = xAxis1->GetNbins();
    
    for(int idxBinX = 1; idxBinX <= numBinsX; ++idxBinX)
    {
      const double binWidthX = 0.5 * (xAxis1->GetBinWidth(idxBinX) + xAxis2->GetBinWidth(idxBinX));
      const double dBinLowEdgeX = xAxis1->GetBinLowEdge(idxBinX) - xAxis2->GetBinLowEdge(idxBinX);
      const double dBinUpEdgeX  = xAxis1->GetBinUpEdge(idxBinX)  - xAxis2->GetBinUpEdge(idxBinX);

      if(! (dBinLowEdgeX < 1.e-3 * binWidthX && dBinUpEdgeX < 1.e-3 * binWidthX))
      {
        throw cmsException(__func__, __LINE__)
          << "Histograms " << histogram1->GetName() << " and " << histogram2->GetName()
          << " have incompatible x-axis binning !!\n (bin #" << idxBinX << ": histogram1 = "
          << xAxis1->GetBinLowEdge(idxBinX) << ".." << xAxis1->GetBinUpEdge(idxBinX) << ","
             " histogram2 = " << xAxis2->GetBinLowEdge(idxBinX) << ".." << xAxis2->GetBinUpEdge(idxBinX) << ')';
      }
    }

    if(dimension1 >= 2 && dimension2 >= 2)
    {
      if(histogram1->GetNbinsY() != histogram2->GetNbinsY())
      {
        throw cmsException(__func__, __LINE__)
          << "Histograms " << histogram1->GetName() << " and " << histogram2->GetName()
          << " have incompatible y-axis binning !!\n (NbinsY: histogram1 = "
          << histogram1->GetNbinsY() << ", histogram2 = " << histogram2->GetNbinsY() << ')';
      }
      const TAxis * const yAxis1 = histogram1->GetYaxis();
      const TAxis * const yAxis2 = histogram2->GetYaxis();
      const int numBinsY = yAxis1->GetNbins();

      for(int idxBinY = 1; idxBinY <= numBinsY; ++idxBinY)
      {
        const double binWidthY = 0.5 * (yAxis1->GetBinWidth(idxBinY) + yAxis2->GetBinWidth(idxBinY));
        const double dBinLowEdgeY = yAxis1->GetBinLowEdge(idxBinY) - yAxis2->GetBinLowEdge(idxBinY);
        const double dBinUpEdgeY  = yAxis1->GetBinUpEdge(idxBinY)  - yAxis2->GetBinUpEdge(idxBinY);

        if(! (dBinLowEdgeY < 1.e-3 * binWidthY && dBinUpEdgeY < 1.e-3 * binWidthY))
        {
          throw cmsException(__func__, __LINE__)
            << "Histograms " << histogram1->GetName() << " and " << histogram2->GetName()
            << " have incompatible y-axis binning !!\n (bin #" << idxBinY << ": histogram1 = "
            << yAxis1->GetBinLowEdge(idxBinY) << ".." << yAxis1->GetBinUpEdge(idxBinY) << ","
               " histogram2 = " << yAxis2->GetBinLowEdge(idxBinY) << ".." << yAxis2->GetBinUpEdge(idxBinY) << ')';
        }
      }
    }
  }
}

bool
checkIfLabeledAxis(const TAxis * axis)
{
  bool areAllLabelled = true;
  const int numBins = axis->GetNbins();
  for(int idxBin = 1; idxBin <= numBins; ++idxBin)
  {
    const std::string binLabel = axis->GetBinLabel(idxBin);
    if(binLabel.empty())
    {
      areAllLabelled = false;
      break;
    }
  }
  return areAllLabelled;
}

bool
checkIfLabeledHistogram(const TH1 * histogram)
{
  bool areAllLabelled = checkIfLabeledAxis(histogram->GetXaxis());
  if(histogram->GetDimension() == 2)
  {
    if(!checkIfLabeledAxis(histogram->GetYaxis())) areAllLabelled = false;
  }
  return areAllLabelled;
}

bool
checkIfLabeledHistograms(const std::vector<TH1 *> & histograms)
{
  bool areAllLabelled = true;
  for(const TH1 * histogram: histograms)
  {
    areAllLabelled = checkIfLabeledHistogram(histogram);
    if(! areAllLabelled)
    {
      break;
    }
  }
  return areAllLabelled;
}

TH1 *
addHistograms(const std::string & newHistogramName,
              const TH1 * histogram1,
              const TH1 * histogram2,
              int verbosity)
{
  const std::vector<TH1 *> histogramsToAdd = {
    const_cast<TH1 *>(histogram1),
    const_cast<TH1 *>(histogram2)
  };
  return addHistograms(newHistogramName, histogramsToAdd, verbosity);
}

TH1 *
addHistograms(const std::string & newHistogramName,
              const std::vector<TH1 *> & histogramsToAdd,
              int verbosity)
{
  if(verbosity)
  {
    std::cout << "<addHistograms>:\n"
                 " newHistogramName = " << newHistogramName << '\n';
  }
  if(histogramsToAdd.empty())
  {
    throw cmsException(__func__, __LINE__) << "No histograms given to add";
  }

  const TH1 * const histogramRef = histogramsToAdd.front();
  if(verbosity)
  {
    std::cout << "histogramRef = "     << histogramRef->GetName() << "\n"
                 "#histogramsToAdd = " << histogramsToAdd.size() << '\n';
  }

  for(const TH1 * const histogramToAdd: histogramsToAdd)
  {
    if(histogramToAdd == histogramRef)
    {
      continue;
    }
    if(verbosity)
    {
      std::cout << "histogramToAdd = " << histogramToAdd->GetName() << ", "
                   "integral = "       << histogramToAdd->Integral() << '\n';
    }
    checkCompatibleBinning(histogramToAdd, histogramRef);
  }

  TH1 * const newHistogram = static_cast<TH1 *>(histogramRef->Clone(newHistogramName.data()));
  newHistogram->Reset();
  if(! newHistogram->GetSumw2N())
  {
    newHistogram->Sumw2();
  }

  const bool isLabelledX = checkIfLabeledAxis(newHistogram->GetXaxis());
  const int firstBinX = isLabelledX ? 1 : 0;
  const int lastBinX = newHistogram->GetNbinsX() + (isLabelledX ? 0 : 1);
  const TAxis * const xAxis = newHistogram->GetXaxis();

  bool isLabelledY = false;
  int firstBinY = 1;
  int lastBinY = 1;
  const TAxis * yAxis = nullptr;
  bool isHistogram2d = ( newHistogram->GetDimension() == 2 ) ? true : false;
  if ( isHistogram2d ) 
  {
    isLabelledY = checkIfLabeledAxis(newHistogram->GetYaxis());
    firstBinY = isLabelledY ? 1 : 0;
    lastBinY = newHistogram->GetNbinsY() + (isLabelledY ? 0 : 1);
    yAxis = newHistogram->GetYaxis();
  }

  for(int idxBinX = firstBinX; idxBinX <= lastBinX; ++idxBinX)
  {
    for(int idxBinY = firstBinY; idxBinY <= lastBinY; ++idxBinY)
    {
      double sumBinContent = 0.;
      double sumBinError2  = 0.;
      for(const TH1 * const histogramToAdd: histogramsToAdd)
      {
        double binContent = 0.;
        double binError = 0.;
        if(isHistogram2d)
        {
          binContent = histogramToAdd->GetBinContent(idxBinX, idxBinY);
          binError = histogramToAdd->GetBinError(idxBinX, idxBinY);
        }
        else
        {
          assert(idxBinY == firstBinY);
          binContent = histogramToAdd->GetBinContent(idxBinX);
          binError = histogramToAdd->GetBinError(idxBinX);
        }
        if(verbosity)
        {
          std::cout << "histogramToAdd = " << histogramToAdd->GetName() << ", "
                       "binContent = "     << binContent << ", "
                       "binError = "       << binError << '\n';
        }
        sumBinContent += binContent;
        sumBinError2  += square(binError);
      }

      if(verbosity)
      {
        std::cout << "binX #" << idxBinX << " (x =  " << xAxis->GetBinCenter(idxBinX) << ")";
        if(isHistogram2d)
        {
          std::cout << ", binY #" << idxBinY << " (y =  " << yAxis->GetBinCenter(idxBinY) << ")";
        }
        std::cout << ": " 
                     "sumBinContent = "           << sumBinContent << ", "
                     "sumBinError2 = "            << sumBinError2 << '\n';
      }
      if (!(sumBinError2 >= 0.))
      {
        std::cout << "Infinite: binX #" << idxBinX << " (x =  " << xAxis->GetBinCenter(idxBinX) << ")";
        if(isHistogram2d)
        {
          std::cout << ", binY #" << idxBinY << " (y =  " << yAxis->GetBinCenter(idxBinY) << ")";
        }
        std::cout << ": " 
                     "sumBinContent = "           << sumBinContent << ", "
                     "sumBinError2 = "            << sumBinError2 << '\n';
        sumBinError2 = 0.;
        sumBinContent = 0.;
      }
      if(isHistogram2d)
      {
        newHistogram->SetBinContent(idxBinX, idxBinY, sumBinContent);
        newHistogram->SetBinError(idxBinX, idxBinY, std::sqrt(sumBinError2));
      }
      else
      {
        newHistogram->SetBinContent(idxBinX, sumBinContent);
        newHistogram->SetBinError(idxBinX, std::sqrt(sumBinError2));
      }
    }
  }
  return newHistogram;
}

TH1 *
subtractHistograms(const std::string & newHistogramName,
                   const TH1 * histogramMinuend,
                   const TH1 * histogramSubtrahend,
                   int verbosity)
{
  if(verbosity)
  {
    std::cout << "<subtractHistograms>:\n"
                 " newHistogramName = " << newHistogramName << '\n';
  }
  checkCompatibleBinning(histogramMinuend, histogramSubtrahend);

  TH1 * const newHistogram = static_cast<TH1 *>(histogramMinuend->Clone(newHistogramName.data()));
  newHistogram->Reset();
  if(! newHistogram->GetSumw2N())
  {
    newHistogram->Sumw2();
  }

  const bool isLabelledX = checkIfLabeledAxis(histogramMinuend->GetXaxis()) && checkIfLabeledAxis(histogramSubtrahend->GetXaxis());
  const int firstBinX = isLabelledX ? 1 : 0;
  const int lastBinX = newHistogram->GetNbinsX() + (isLabelledX ? 0 : 1);
  const TAxis * const xAxis = newHistogram->GetXaxis();

  bool isLabelledY = false;
  int firstBinY = 1;
  int lastBinY = 1;
  const TAxis * yAxis = nullptr;
  bool isHistogram2d = ( newHistogram->GetDimension() == 2 ) ? true : false;
  if ( isHistogram2d ) 
  {
    isLabelledY = checkIfLabeledAxis(histogramMinuend->GetYaxis()) && checkIfLabeledAxis(histogramSubtrahend->GetYaxis());
    firstBinY = isLabelledY ? 1 : 0;
    lastBinY = newHistogram->GetNbinsY() + (isLabelledY ? 0 : 1);
    yAxis = newHistogram->GetYaxis();
  }

  for(int idxBinX = firstBinX; idxBinX <= lastBinX; ++idxBinX)
  {
    for(int idxBinY = firstBinY; idxBinY <= lastBinY; ++idxBinY)
    {
      double binContentMinuend = 0.;
      double binErrorMinuend = 0.;
      double binContentSubtrahend = 0.;
      double binErrorSubtrahend = 0.;
      if(isHistogram2d)
      {
        binContentMinuend = histogramMinuend->GetBinContent(idxBinX, idxBinY);
        binErrorMinuend = histogramMinuend->GetBinError(idxBinX, idxBinY);
        binContentSubtrahend = histogramSubtrahend->GetBinContent(idxBinX, idxBinY);
        binErrorSubtrahend = histogramSubtrahend->GetBinError(idxBinX, idxBinY);
      }
      else
      {
        assert(idxBinY == firstBinY);
        binContentMinuend = histogramMinuend->GetBinContent(idxBinX);
        binErrorMinuend = histogramMinuend->GetBinError(idxBinX);
        binContentSubtrahend = histogramSubtrahend->GetBinContent(idxBinX);
        binErrorSubtrahend = histogramSubtrahend->GetBinError(idxBinX);
      }
      if(verbosity)
      {
        std::cout << "binX #" << idxBinX << " (x =  " << xAxis->GetBinCenter(idxBinX) << ")";
        if(isHistogram2d)
        {
          std::cout << ", binY #" << idxBinY << " (y =  " << yAxis->GetBinCenter(idxBinY) << ")";
        }
        std::cout << ": " 
                     "minuend = "    << binContentMinuend         << " +/- "
                                     << binErrorMinuend           << ", "
                     "subtrahend = " << binContentSubtrahend      << " +/- "
                                     << binErrorSubtrahend        << '\n';
      }
      double newBinContent = binContentMinuend - binContentSubtrahend;
      double newBinError2  = square(binErrorMinuend) + square(binErrorSubtrahend);
      if (!(newBinError2 >= 0.))
      {
        std::cout << "Infinite: binX #" << idxBinX << " (x =  " << xAxis->GetBinCenter(idxBinX) << ")";
        if(isHistogram2d)
        {
          std::cout << ", binY #" << idxBinY << " (y =  " << yAxis->GetBinCenter(idxBinY) << ")";
        }
        std::cout << ": " 
                     "newBinContent = "           << newBinContent << ", "
                     "newBinError2 = "            << newBinError2 << '\n';
        newBinError2 = 0.;
        newBinContent = 0.;
      }
      if(isHistogram2d)
      {
        newHistogram->SetBinContent(idxBinX, idxBinY, newBinContent);
        newHistogram->SetBinError(idxBinX, idxBinY, std::sqrt(newBinError2));
      }
      else
      {
        newHistogram->SetBinContent(idxBinX, newBinContent);
        newHistogram->SetBinError(idxBinX, std::sqrt(newBinError2));
      }
    }
  }
  return newHistogram;
}

TH1 *
subtractHistograms(const std::string & newHistogramName,
                   const TH1 * histogram,
                   const std::vector<TH1 *> & histogramsToSubtract,
                   int verbosity)
{
  if(verbosity)
  {
    std::cout << "<subtractHistograms>:\n"
                 " newHistogramName = "      << newHistogramName            << "\n"
                 " histogram = "             << histogram->GetName()        << "\n"
                 " #histogramsToSubtract = " << histogramsToSubtract.size() << '\n';
  }
  if(! histogram)
  {
    throw cmsException(__func__, __LINE__) << "No histograms given to subtract !!";
  }

  TH1 * newHistogram = nullptr;
  if(histogramsToSubtract.empty())
  {
    newHistogram = static_cast<TH1 *>(histogram->Clone(newHistogramName.data()));
  }
  else
  {
    const TH1 * histogramSubtrahend = addHistograms("subtractHistogramsTMP", histogramsToSubtract);
    newHistogram = subtractHistograms(newHistogramName, histogram, histogramSubtrahend, verbosity);
    delete histogramSubtrahend;
  }
  return newHistogram;
}

double
compIntegral(const TH1 * histogram,
             bool includeUnderflowBin,
             bool includeOverflowBin)
{
  const int numBinsX  = histogram->GetNbinsX();
  const int firstBinX = includeUnderflowBin ? 0            : 1;
  const int lastBinX  = includeOverflowBin  ? numBinsX + 1 : numBinsX;

  int firstBinY = 1;
  int lastBinY = 1;
  bool isHistogram2d = ( histogram->GetDimension() == 2 ) ? true : false;
  if ( isHistogram2d ) 
  {
    const int numBinsY  = histogram->GetNbinsY();
    firstBinY = includeUnderflowBin ? 0            : 1;
    lastBinY  = includeOverflowBin  ? numBinsY + 1 : numBinsY;
  }

  double sumBinContent = 0.;
  for ( int idxBinX = firstBinX; idxBinX <= lastBinX; ++idxBinX)
  {
    for ( int idxBinY = firstBinY; idxBinY <= lastBinY; ++idxBinY)
    {
      if (isHistogram2d)
      {
        sumBinContent += histogram->GetBinContent(idxBinX, idxBinY);
      }
      else
      {
        assert(idxBinY == firstBinY);
        sumBinContent += histogram->GetBinContent(idxBinX);
      }
    }
  }
  return sumBinContent;
}

double
compIntegralErr(const TH1 * histogram,
                bool includeUnderflowBin,
                bool includeOverflowBin)
{
  const int numBinsX  = histogram->GetNbinsX();
  const int firstBinX = includeUnderflowBin ? 0            : 1;
  const int lastBinX  = includeOverflowBin  ? numBinsX + 1 : numBinsX;

  int firstBinY = 1;
  int lastBinY = 1;
  bool isHistogram2d = ( histogram->GetDimension() == 2 ) ? true : false;
  if ( isHistogram2d ) 
  {
    const int numBinsY  = histogram->GetNbinsY();
    firstBinY = includeUnderflowBin ? 0            : 1;
    lastBinY  = includeOverflowBin  ? numBinsY + 1 : numBinsY;
  }

  double sumBinErr2 = 0.;
  for ( int idxBinX = firstBinX; idxBinX <= lastBinX; ++idxBinX)
  {
    for ( int idxBinY = firstBinY; idxBinY <= lastBinY; ++idxBinY)
    {
      if (isHistogram2d)
      {
        sumBinErr2 += square(histogram->GetBinError(idxBinX, idxBinY));
      }
      else
      {
        assert(idxBinY == firstBinY);
        sumBinErr2 += square(histogram->GetBinError(idxBinX));
      }
    }
  }
  return std::sqrt(sumBinErr2);
}

void
makeBinContentsPositive(TH1 * histogram, bool isData,
                        int verbosity)
{
  if(verbosity)
  {
    std::cout << "<makeBinContentsPositive>:\n"
                 " integral(" << histogram->GetName()  << ") = "
                              << histogram->Integral() << '\n';
  }

  double integral_original = compIntegral(histogram, false, false);
  if(integral_original < 0.)
  {
    integral_original = 0.;
  }
  if(verbosity)
  {
    std::cout << " integral_original = " << integral_original << '\n';
  }

  const bool isLabelledX = checkIfLabeledAxis(histogram->GetXaxis());
  const int firstBinX = isLabelledX ? 1 : 0;
  const int lastBinX = histogram->GetNbinsX() + (isLabelledX ? 0 : 1);
  const TAxis * const xAxis = histogram->GetXaxis();

  bool isLabelledY = false;
  int firstBinY = 1;
  int lastBinY = 1;
  const TAxis * yAxis = nullptr;
  bool isHistogram2d = ( histogram->GetDimension() == 2 ) ? true : false;
  if ( isHistogram2d ) 
  {
    isLabelledY = checkIfLabeledAxis(histogram->GetYaxis());
    firstBinY = isLabelledY ? 1 : 0;
    lastBinY = histogram->GetNbinsY() + (isLabelledY ? 0 : 1);
    yAxis = histogram->GetYaxis();
  }

  for(int idxBinX = firstBinX; idxBinX <= lastBinX; ++idxBinX)
  {
    for(int idxBinY = firstBinY; idxBinY <= lastBinY; ++idxBinY)
    {
      double binContent_original = 0.;
      double binError2_original = 0.;
      if(isHistogram2d)
      {
        binContent_original = histogram->GetBinContent(idxBinX, idxBinY);
        binError2_original = square(histogram->GetBinError(idxBinX, idxBinY));
      }
      else
      {
        assert(idxBinY == firstBinY);
        binContent_original = histogram->GetBinContent(idxBinX);
        binError2_original = square(histogram->GetBinError(idxBinX));
      }
      if(binContent_original < 0.)
      {
        const double binContent_modified = 0.;
        const double binError2_modified = binError2_original + square(binContent_original - binContent_modified);
        assert(binError2_modified >= 0.);
        if(verbosity)
        {
          std::cout << "binX #" << idxBinX << " (x =  " << xAxis->GetBinCenter(idxBinX) << ")";
          if(isHistogram2d)
          {
            std::cout << ", binY #" << idxBinY << " (y =  " << yAxis->GetBinCenter(idxBinY) << ")";
          }
          std::cout << ": " 
                       "binContent = " << binContent_original << " +/- " << std::sqrt(binError2_original) << " --> setting it to "
                       "binContent = " << binContent_modified << " +/- " << std::sqrt(binError2_modified) << '\n';
        }
        if(isHistogram2d)
        {
          histogram->SetBinContent(idxBinX, idxBinY, binContent_modified);
          histogram->SetBinError(idxBinX, idxBinY, std::sqrt(binError2_modified));
        }
        else
        {          
          histogram->SetBinContent(idxBinX, binContent_modified);
          histogram->SetBinError(idxBinX, std::sqrt(binError2_modified));
        }
      }
    }
  }

  double integral_modified = compIntegral(histogram, false, false);
  if(integral_modified < 0.)
  {
    integral_modified = 0.;
  }
  if(verbosity)
  {
    std::cout << " integral_modified = " << integral_modified << '\n';
  }

  if(integral_original > 0. && integral_modified > 0.)
  {
    const double sf = integral_original / integral_modified;
    if(verbosity)
    {
      std::cout << "--> scaling bin-contents by factor = " << sf << ", while keeping the bin-errors the same" << '\n';
    }
    for(int idxBinX = firstBinX; idxBinX <= lastBinX; ++idxBinX)
    {
      for(int idxBinY = firstBinY; idxBinY <= lastBinY; ++idxBinY)
      {
        if(isHistogram2d)
        {
          const double binContent = histogram->GetBinContent(idxBinX, idxBinY);
          histogram->SetBinContent(idxBinX, idxBinY, sf*binContent);
        }
        else
        {
          const double binContent = histogram->GetBinContent(idxBinX);
          histogram->SetBinContent(idxBinX, sf*binContent);
        }
      }
    }
  }
  else if ( !isData )
  {
    for(int idxBinX = firstBinX; idxBinX <= lastBinX; ++idxBinX)
    {
      for(int idxBinY = firstBinY; idxBinY <= lastBinY; ++idxBinY)
      {
        if(isHistogram2d)
        {
          histogram->SetBinContent(idxBinX, idxBinY, 1.e-3/((lastBinX - firstBinX + 1)*(lastBinY - firstBinY + 1)));
        }
        else
        {
          histogram->SetBinContent(idxBinX, 1.e-3/(lastBinX - firstBinX + 1));
        }
      }
    }
  }

  if(verbosity)
  {
    double integral = compIntegral(histogram, false, false);
    double integralErr = compIntegralErr(histogram, false, false);
    std::cout << " integral(" << histogram->GetName() << ") = " << integral << " +/- " << integralErr << '\n';
  }
}

void
dumpHistogram(const TH1 * histogram)
{
  double integral = compIntegral(histogram, false, false);
  double integralErr = compIntegralErr(histogram, false, false);
  std::cout << "<dumpHistogram>:\n"
               "histogram = '" << histogram->GetName() << "'\n"
               "integral = " << integral << " +/- " << integralErr << '\n';

  const int firstBinX = 1;
  const int lastBinX = histogram->GetNbinsX();
  const TAxis * const xAxis = histogram->GetXaxis();

  int firstBinY = 1;
  int lastBinY = 1;
  const TAxis * yAxis = nullptr;
  bool isHistogram2d = ( histogram->GetDimension() == 2 ) ? true : false;
  if ( isHistogram2d ) 
  {
    firstBinY = 1;
    lastBinY = histogram->GetNbinsY();
    yAxis = histogram->GetYaxis();
  }

  for(int idxBinX = firstBinX; idxBinX <= lastBinX; ++idxBinX)
  {
    for(int idxBinY = firstBinY; idxBinY <= lastBinY; ++idxBinY)
    {
      double binContent = 0.;
      double binError = 0.;
      if(isHistogram2d)
      {
        binContent = histogram->GetBinContent(idxBinX, idxBinY);
        binError = histogram->GetBinError(idxBinX, idxBinY);
      }
      else
      {
        assert(idxBinY == firstBinY);
        binContent = histogram->GetBinContent(idxBinX);
        binError = histogram->GetBinError(idxBinX);
      }
      std::cout << "binX #" << idxBinX << " (x =  " << xAxis->GetBinCenter(idxBinX) << ")";
      if(isHistogram2d)
      {
        std::cout << ", binY #" << idxBinY << " (y =  " << yAxis->GetBinCenter(idxBinY) << ")";
      }
      std::cout << ": " 
                   "binContent = " << binContent << " +/- " << binError << '\n';
    }
  }
}

//
//-------------------------------------------------------------------------------
//

TDirectory *
getDirectory(const TFile * inputFile,
             const std::string & dirName,
             bool enableException)
{
  const std::string dirName_tmp = removeLastSlash(dirName);
  TDirectory * dir = dynamic_cast<TDirectory *>((const_cast<TFile *>(inputFile))->Get(dirName_tmp.data()));
  if(dir)
  {
    std::cout << "--> returning dir = " << dir << ": name = '" << dir->GetName() << "'\n";
  }
  else if( enableException)
  {
    inputFile->ls();
    throw cmsException(__func__, __LINE__)
      << "Failed to find directory = '" << dirName << "' in file = '" << inputFile->GetName() << "'\n";
  }
  return dir;
}

TDirectory *
getSubdirectory(const TDirectory * dir,
                const std::string & subdirName,
                bool enableException)
{
  const std::string subdirName_tmp = removeLastSlash(subdirName);;
  TDirectory * subdir = dynamic_cast<TDirectory *>((const_cast<TDirectory *>(dir))->Get(subdirName_tmp.data()));
  std::cout << "--> returning subdir = " << subdir << ": name = '" << subdirName << "'\n";
  if(subdir)
  {
    std::cout << "--> returning subdir = " << subdir << ": name = '" << subdir->GetName() << "'\n";
  }
  else if(enableException)
  {
    std::cout << "--> returning subdir = " << subdir << ": name = '" << subdir->GetName() << "'\n";
    dir->ls();

    throw cmsException(__func__, __LINE__)
      << "Failed to find subdirectory = '" << subdirName << "' in directory = "
      << dir << ": name = '" << dir->GetName() << "'\n";
  }
  return subdir;
}

TH1 *
getHistogram(const TDirectory * dir,
             const std::string & process,
             const std::string & histogramName,
             const std::string & central_or_shift,
             bool enableException,
             bool verbose)
{
  std::string histogramName_full = Form("%s/", process.data());
  if(! central_or_shift.empty() && central_or_shift != "central")
  {
    histogramName_full.append(Form("%s_%s", central_or_shift.data(), histogramName.data()));
  }
  else
  {
    histogramName_full.append(histogramName);
  }

  TH1 * histogram = dynamic_cast<TH1 *>((const_cast<TDirectory *>(dir))->Get(histogramName_full.data()));
  if(histogram)
  {
    if(verbose)
    {
      std::cout << "--> returning histogram = " << histogram << ": name = '" << histogram->GetName() << "'\n";
    }
  }
  else if(enableException)
  {
    dir->ls();
    throw cmsException(__func__, __LINE__)
      << "Failed to find histogram = '" << histogramName_full << "' in directory = " << dir << ": "
         "name = '" << dir->GetName() << "' !!\n";
  }
  return histogram;
}

TDirectory *
createSubdirectory(TDirectory * dir,
                   const std::string & subdirName,
                   bool verbose)
{
  if(verbose)
  {
    std::cout << "<createSubdirectory>:\n"
                 " dir = " << dir << ": name = '" << dir->GetName() << "'\n"
                 " subdirName = '" << subdirName << "'\n";
  }

  dir->cd();
  if(! dir->Get(subdirName.data()))
  {
    if(verbose)
    {
      std::cout << "--> creating subdir = '" << subdirName << "'\n";
    }
    dir->mkdir(subdirName.data());
  }
  else
  {
    if(verbose)
    {
      std::cout << "--> subdir = '" << subdirName << "' already exists --> skipping\n";
    }
  }
  TDirectory * subdir = dynamic_cast<TDirectory *>(dir->Get(subdirName.data()));
  assert(subdir);
  return subdir;
}

TDirectory *
createSubdirectory_recursively(TFileDirectory & dir,
                               const std::string & fullSubdirName,
                               bool verbose)
{
  if(verbose)
  {
    std::cout << "<createSubdirectory_recursively>:\n"
                 " dir = " << &dir << ": name = '" << dir.getBareDirectory()->GetName() << "'\n"
                 " fullSubdirName = '" << fullSubdirName << "'\n";
  }

  TString fullSubdirName_tstring = fullSubdirName.data();
  TObjArray * subdirNames = fullSubdirName_tstring.Tokenize("/");
  int numSubdirectories = subdirNames->GetEntries();

  TDirectory * parent = dir.getBareDirectory();
  for(int iSubdirectory = 0; iSubdirectory < numSubdirectories; ++iSubdirectory)
  {
    const TObjString * subdirName = dynamic_cast<TObjString *>(subdirNames->At(iSubdirectory));
    assert(subdirName);

    TDirectory * subdir = createSubdirectory(parent, subdirName->GetString().Data(), verbose);
    parent = subdir;
  }
  delete subdirNames;
  return parent;
}

//
//-------------------------------------------------------------------------------
//

TArrayD
getBinning(const TH1 * histogram,
           double xMin,
           double xMax)
{
  const TAxis * const xAxis = histogram->GetXaxis();
  const int numBins = xAxis->GetNbins();

  std::vector<double> binning;
  for(int idxBin = 1; idxBin <= numBins; ++idxBin)
  {
    const double binCenter = xAxis->GetBinCenter(idxBin);
    if ((xMin == -1. || binCenter > xMin) && (xMax == -1. || binCenter < xMax))
    {
      if(binning.empty())
      {
        binning.push_back(xAxis->GetBinLowEdge(idxBin));
      }
      binning.push_back(xAxis->GetBinUpEdge(idxBin));
    }
  }

  const int binning_size = binning.size();
  assert(binning_size >= 2);

  TArrayD binning_tarray(binning_size);
  for(int idxBin = 0; idxBin < binning_size; ++idxBin)
  {
    binning_tarray[idxBin] = binning[idxBin];
  }
  return binning_tarray;
}

TH1 *
getRebinnedHistogram1d(const TH1 * histoOriginal,
                       unsigned numBins_rebinned, // unused
                       const TArrayD & binEdges_rebinned,
                       bool add_uniqueId)
{
  static int idx = 0;
  std::string histoRebinnedName;
  if ( add_uniqueId ) {
    ++idx;
    histoRebinnedName = Form("%s_rebinned%i", histoOriginal->GetName(), idx);
  } else {
    histoRebinnedName = Form("%s_rebinned", histoOriginal->GetName());
  }
  TH1 * histoRebinned = new TH1D(
    histoRebinnedName.data(),
    histoOriginal->GetTitle(),
    binEdges_rebinned.GetSize() - 1,
    binEdges_rebinned.GetArray()
  );

  histoRebinned->Sumw2();
  const TAxis * const axis_original = histoOriginal->GetXaxis();
  const int numBins_original_plus1 = axis_original->GetNbins() + 1;

  for(int idxBin = 1; idxBin < numBins_original_plus1; ++idxBin)
  {
    const double binContent_original = histoOriginal->GetBinContent(idxBin);
    const double binError_original = histoOriginal->GetBinError(idxBin);
    const double binCenter_original = axis_original->GetBinCenter(idxBin);

    const int binIndex_rebinned = histoRebinned->FindBin(binCenter_original);
    const double binContent_rebinned = histoRebinned->GetBinContent(binIndex_rebinned) + binContent_original;
    const double binError_rebinned = quad(histoRebinned->GetBinError(binIndex_rebinned), binError_original);

    histoRebinned->SetBinContent(binIndex_rebinned, binContent_rebinned);
    histoRebinned->SetBinError  (binIndex_rebinned, binError_rebinned);
  }
  return histoRebinned;
}

TH2 *
getRebinnedHistogram2d(const TH1 * histoOriginal,
                       unsigned numBinsX_rebinned, // unused
                       const TArrayD & binEdgesX_rebinned,
                       unsigned numBinsY_rebinned, // unused
                       const TArrayD & binEdgesY_rebinned,
                       bool add_uniqueId)
{
  static int idx = 0;
  std::string histoRebinnedName;
  if ( add_uniqueId ) {
    ++idx;
    histoRebinnedName = Form("%s_rebinned%i", histoOriginal->GetName(), idx);
  } else {
    histoRebinnedName = Form("%s_rebinned", histoOriginal->GetName());
  }
  TH2D * histoRebinned = new TH2D(
    histoRebinnedName.data(),
    histoOriginal->GetTitle(),
    binEdgesX_rebinned.GetSize() - 1,
    binEdgesX_rebinned.GetArray(),
    binEdgesY_rebinned.GetSize() - 1,
    binEdgesY_rebinned.GetArray()
  );
  histoRebinned->Sumw2();

  const TAxis * const xAxis_original = histoOriginal->GetXaxis();
  const TAxis * const yAxis_original = histoOriginal->GetYaxis();
  const int numBinsX_original_plus1 = xAxis_original->GetNbins() + 1;
  for(int idxBinX = 1; idxBinX < numBinsX_original_plus1; ++idxBinX)
  {
    const int numBinsY_original_plus1 = yAxis_original->GetNbins() + 1;
    for(int idxBinY = 1; idxBinY < numBinsY_original_plus1; ++idxBinY)
    {
      const double binContent_original = histoOriginal->GetBinContent(idxBinX, idxBinY);
      const double binError_original   = histoOriginal->GetBinError(idxBinX, idxBinY);
      const double binCenterX_original = xAxis_original->GetBinCenter(idxBinX);
      const double binCenterY_original = yAxis_original->GetBinCenter(idxBinY);

      const int binIndex_rebinned = histoRebinned->FindBin(binCenterX_original, binCenterY_original);
      const double binContent_rebinned = histoRebinned->GetBinContent(binIndex_rebinned) + binContent_original;
      const double binError_rebinned   = quad(histoRebinned->GetBinError(binIndex_rebinned), binError_original);

      histoRebinned->SetBinContent(binIndex_rebinned, binContent_rebinned);
      histoRebinned->SetBinError  (binIndex_rebinned, binError_rebinned);
    }
  }
  return histoRebinned;
}

TArrayD
getRebinnedBinning(TH1 * histogram,
                   double minEvents)
{
  std::cout << __func__ << ":\n";
  const TAxis * xAxis = histogram->GetXaxis();

  std::vector<double> histogramBinning = { xAxis->GetBinLowEdge(1) };
  double sumEvents = 0.;
  const int numBins = xAxis->GetNbins();
  for(int idxBin = 1; idxBin <= numBins; ++idxBin)
  {
    sumEvents += histogram->GetBinContent(idxBin);
    if(sumEvents >= minEvents)
    {
      histogramBinning.push_back(xAxis->GetBinUpEdge(idxBin));
      sumEvents = 0.;
    }
  }
  if(std::fabs(histogramBinning.back() - xAxis->GetBinUpEdge(numBins)) > 1.e-3)
  {
    if(histogramBinning.size() >= 2)
    {
      histogramBinning.back() = xAxis->GetBinUpEdge(numBins);
    }
    else
    {
      histogramBinning.push_back(xAxis->GetBinUpEdge(numBins));
    }
  }
  assert(histogramBinning.size() >= 2);
  std::cout << "binning = " << format_vdouble(histogramBinning) << '\n';

  TArrayD binning_tarray(histogramBinning.size());
  for(std::size_t idxBin = 0; idxBin < histogramBinning.size(); ++idxBin)
  {
    binning_tarray[idxBin] = histogramBinning[idxBin];
  }
  return binning_tarray;
}

TArrayD
getTArraDfromVector(const std::vector<double> & histogramBinning)
{
  TArrayD binning_tarray(histogramBinning.size());
  for(std::size_t idxBin = 0; idxBin < histogramBinning.size(); ++idxBin)
  {
    binning_tarray[idxBin] = histogramBinning[idxBin];
  }
  return binning_tarray;
}

TH1 *
compRatioHistogram(const std::string & ratioHistogramName,
                   const TH1 * numerator,
                   const TH1 * denominator)
{
  checkCompatibleBinning(numerator, denominator);

  TH1 * histogramRatio = (TH1*)numerator->Clone(ratioHistogramName.data());
  histogramRatio->Divide(denominator);

  const int firstBinX = 1;
  const int lastBinX = denominator->GetNbinsX();

  int firstBinY = 1;
  int lastBinY = 1;
  bool isHistogram2d = ( denominator->GetDimension() == 2 ) ? true : false;
  if ( isHistogram2d ) 
  {
    firstBinY = 1;
    lastBinY = denominator->GetNbinsY();
  }

  for(int idxBinX = firstBinX; idxBinX <= lastBinX; ++idxBinX)
  {
    for(int idxBinY = firstBinY; idxBinY <= lastBinY; ++idxBinY)
    {
      if(isHistogram2d)
      {
        const double binContent = histogramRatio->GetBinContent(idxBinX, idxBinY);
        histogramRatio->SetBinContent(idxBinX, idxBinY, binContent - 1.);
      }
      else
      {
        assert(idxBinY == firstBinY);
        const double binContent = histogramRatio->GetBinContent(idxBinX);
        histogramRatio->SetBinContent(idxBinX, binContent - 1.);
      }
    }
  }

  histogramRatio->SetLineColor(numerator->GetLineColor());
  histogramRatio->SetLineWidth(numerator->GetLineWidth());
  histogramRatio->SetMarkerColor(numerator->GetMarkerColor());
  histogramRatio->SetMarkerStyle(numerator->GetMarkerStyle());
  histogramRatio->SetMarkerSize(numerator->GetMarkerSize());

  return histogramRatio;
}

void
divideByBinWidth(TH1 * histogram)
{
  if(! (histogram && histogram->GetDimension() == 1))
  {
    return;
  }
  const TAxis * const xAxis = histogram->GetXaxis();
  const int numBins = xAxis->GetNbins();
  for(int idxBin = 1; idxBin <= numBins; ++idxBin)
  {
    const double binContent = histogram->GetBinContent(idxBin);
    const double binError = histogram->GetBinError(idxBin);
    const double binWidth = xAxis->GetBinWidth(idxBin);
    histogram->SetBinContent(idxBin, binContent/binWidth);
    histogram->SetBinError(idxBin, binError/binWidth);
  }
}

histogramEntryType_private::histogramEntryType_private(TH1* histogram,
                                                       bool isData)
  : histogram_(histogram)
  , isData_(isData)
{}
