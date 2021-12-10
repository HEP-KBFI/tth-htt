#ifndef tthAnalysis_HiggsToTauTau_histogramAuxFunctions_h
#define tthAnalysis_HiggsToTauTau_histogramAuxFunctions_h
#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h"
#include <CommonTools/Utils/interface/TFileDirectory.h> // TFile, TH1, TDirectory, TFileDirectory
#include<TH2.h>
#include <iostream> // std::cout
#include<boost/any.hpp>

// forward declarations
//class TH2;

void
fill(TH1 * histogram,
     double x,
     double evtWeight,
     double evtWeightErr = 0.);

void
fillWithOverFlow(TH1* histogram,
                 double x,
                 double evtWeight,
                 double evtWeightErr = 0.);

void
fill2d(TH2 * histogram,
       double x,
       double y,
       double evtWeight,
       double evtWeightErr = 0.);

void
fillWithOverFlow2d(TH2* histogram,
                   double x,
                   double y,
                   double evtWeight,
                   double evtWeightErr = 0.);

double
getLogWeight(double weight);


template<typename T>
void
checkCompatibleBinning(const T * histogram1,
                       const T * histogram2)
{
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
}

template<typename T>
bool
checkIfLabeledHistogram(const T * histogram) {
  bool isLabelled = checkIfLabeledAxis(histogram->GetXaxis());
  if(histogram->GetDimension() == 2)
    {
      if(checkIfLabeledAxis(histogram->GetYaxis())) isLabelled = true;
    }
  return isLabelled;
}

template<typename T>
bool
checkIfLabeledHistograms(const std::vector<T *> & histograms) {
  bool isLabelled = false;
  for(const T * histogram: histograms)
  {
    isLabelled = checkIfLabeledHistogram(histogram);
    if(isLabelled)
    {
      break;
    }
  }
  return isLabelled;
}

bool
checkIfLabeledAxis(const TAxis * axis);
TH1*
addHistograms(const std::string & newHistogramName,
              const TH1* histogram1,
              const TH1* histogram2,
              int verbosity = 0);
template<typename T>
T*
addHistograms_temp(const std::string & newHistogramName,
              const std::vector<T *> & histogramsToAdd,
                   int verbosity = 0) {


  if(verbosity)
  {
    std::cout << "<addHistograms>:\n"
      " newHistogramName = " << newHistogramName << '\n';
  }
  if(histogramsToAdd.empty())
  {
    throw cmsException(__func__, __LINE__) << "No histograms given to add";
  }

  const T* const histogramRef = histogramsToAdd.front();
  if(verbosity)
  {
    std::cout << "histogramRef = "     << histogramRef->GetName() << "\n"
      "#histogramsToAdd = " << histogramsToAdd.size() << '\n';
  }

  for(const T* const histogramToAdd: histogramsToAdd)
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
  
  T* const newHistogram = static_cast<T* >(histogramRef->Clone(newHistogramName.data()));
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
      for(const T* const histogramToAdd: histogramsToAdd)
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
        sumBinError2  += binError*binError;
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

template<typename T>
T *
subtractHistograms(const std::string & newHistogramName,
                   const T * histogramMinuend,
                   const T * histogramSubtrahend,
                   int verbosity = 0)
{
  if(verbosity)
  {
    std::cout << "<subtractHistograms>:\n"
      " newHistogramName = " << newHistogramName << '\n';
  }
  checkCompatibleBinning(histogramMinuend, histogramSubtrahend);

  T * const newHistogram = static_cast<T *>(histogramMinuend->Clone(newHistogramName.data()));
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
      double newBinError2  = (binErrorMinuend*binErrorMinuend) + (binErrorSubtrahend*binErrorSubtrahend);
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

template<typename T>
T *
subtractHistograms(const std::string & newHistogramName,
                   const T* histogram,
                   const std::vector<T *> & histogramsToSubtract,
                   int verbosity = 0){
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
  T * newHistogram = nullptr;
  if(histogramsToSubtract.empty())
  {
    newHistogram = static_cast<T *>(histogram->Clone(newHistogramName.data()));
  }
  else
  {
    std::string name = "subtractHistogramsTMP";
    std::vector<TH1*> histogramsToSubtract_1d;
    std::vector<TH2*> histogramsToSubtract_2d;
    for(unsigned int i=0; i<histogramsToSubtract.size(); i++)
    {
      if (dynamic_cast<const TH1*>(histogramsToSubtract[i]))
      {
        histogramsToSubtract_1d.push_back(dynamic_cast<TH1*>(histogramsToSubtract[i]));
      }
      else {
        histogramsToSubtract_2d.push_back(dynamic_cast<TH2*>(histogramsToSubtract[i]));
      }
    }
    if(histogramsToSubtract_1d.size())
    {
      const TH1 * histogramSubtrahend = addHistograms_temp<TH1>("subtractHistogramsTMP", histogramsToSubtract_1d);
      const TH1* histogram_1d = dynamic_cast<TH1*>(const_cast<T*>(histogram));
      newHistogram = dynamic_cast<T*>(subtractHistograms<TH1>(newHistogramName, histogram_1d, histogramSubtrahend, verbosity));
      delete histogramSubtrahend;
      delete histogram_1d;
      for (unsigned int i=0; i<histogramsToSubtract_1d.size(); i++) delete histogramsToSubtract_1d[i];
    }
    else {
      const TH2 * histogramSubtrahend = addHistograms_temp<TH2>("subtractHistogramsTMP", histogramsToSubtract_2d);
      const TH2* histogram_2d = dynamic_cast<TH2*>(const_cast<T*>(histogram));
      newHistogram = dynamic_cast<T*>(subtractHistograms<TH2>(newHistogramName, histogram_2d, histogramSubtrahend, verbosity));
      delete histogramSubtrahend;
      delete histogram_2d;
      for (unsigned int i=0; i<histogramsToSubtract_2d.size(); i++) delete histogramsToSubtract_2d[i];
    }
  }

  return newHistogram;
}


double
compIntegral(const TH1 * histogram,
             bool includeUnderflowBin,
             bool includeOverflowBin);

double
compIntegralErr(const TH1 * histogram,
                bool includeUnderflowBin,
                bool includeOverflowBin);

void
makeBinContentsPositive(TH1 * histogram, bool isData,
                        int verbosity = 0);

void
dumpHistogram(const TH1 * histogram);

TDirectory *
getDirectory(const TFile * inputFile,
             const std::string & dirName,
             bool enableException);

TDirectory *
getSubdirectory(const TDirectory * dir,
                const std::string & subdirName,
                bool enableException);

TObject*
getHistogram1d2d(const TDirectory * dir,
             const std::string & process,
             const std::string & histogramName,
             const std::string & central_or_shift,
             bool enableException,
             bool verbose = false);

TH1*
getHistogram(const TDirectory * dir,
                 const std::string & process,
                 const std::string & histogramName,
                 const std::string & central_or_shift,
                 bool enableException,
                 bool verbose = false);

TDirectory *
createSubdirectory(TDirectory * dir,
                   const std::string & subdirName,
                   bool verbose = false);

TDirectory *
createSubdirectory_recursively(TFileDirectory & dir,
                               const std::string & fullSubdirName,
                               bool verbose = false);

TArrayD
getBinning_axis(const TAxis * axis,
           double xMin = -1.,
           double xMax = -1.);
TArrayD
getBinning(const TH1 * histogram,
           double xMin = -1.,
           double xMax = -1.);

TH1 *
getRebinnedHistogram1d(const TH1 * histoOriginal,
                       unsigned numBins_rebinned,
                       const TArrayD & binEdges_rebinned,
		       bool add_uniqueId = false);

TH2 *
getRebinnedHistogram2d(const TH1 * histoOriginal,
                       unsigned numBinsX_rebinned,
                       const TArrayD & binEdgesX_rebinned,
                       unsigned numBinsY_rebinned,
                       const TArrayD & binEdgesY_rebinned,
		       bool add_uniqueId = false);

TArrayD getRebinnedBinning(TH1*, double);

TArrayD
getTArrayDfromVector(const std::vector<double> & histogramBinning);

TH1 *
compRatioHistogram(const std::string & ratioHistogramName,
                   const TH1 * numerator,
                   const TH1 * denominator);

void
divideByBinWidth(TH1 * histogram);

struct histogramEntryType_private
{
  histogramEntryType_private(TH1 * histogram,
                             bool isData);

  ~histogramEntryType_private(){}

  TH1 * histogram_;
  bool isData_;
};

#endif // tthAnalysis_HiggsToTauTau_histogramAuxFunctions_h
