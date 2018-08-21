#include "tthAnalysis/HiggsToTauTau/interface/histogramAuxFunctions.h"

#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h" // cmsException()

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
    if(histogram1->GetNbinsX() != histogram2->GetNbinsX())
    {
      throw cmsException(__func__, __LINE__)
        << "Histograms " << histogram1->GetName() << " and " << histogram2->GetName()
        << " have incompatible binning !!\n (NbinsX: histogram1 = "
        << histogram1->GetNbinsX() << ", histogram2 = " << histogram2->GetNbinsX() << ')';
    }
    const TAxis * const xAxis1 = histogram1->GetXaxis();
    const TAxis * const xAxis2 = histogram2->GetXaxis();
    const int numBins_plus1 = xAxis1->GetNbins() + 1;

    for(int iBin = 1; iBin < numBins_plus1; ++iBin)
    {
      const double binWidth = 0.5 * (xAxis1->GetBinWidth(iBin) + xAxis2->GetBinWidth(iBin));
      const double dBinLowEdge = xAxis1->GetBinLowEdge(iBin) - xAxis2->GetBinLowEdge(iBin);
      const double dBinUpEdge  = xAxis1->GetBinUpEdge(iBin)  - xAxis2->GetBinUpEdge(iBin);

      if(! (dBinLowEdge < 1.e-3 * binWidth && dBinUpEdge < 1.e-3 * binWidth))
      {
        throw cmsException(__func__, __LINE__)
          << "Histograms " << histogram1->GetName() << " and " << histogram2->GetName()
          << " have incompatible binning !!\n (bin #" << iBin << ": histogram1 = "
          << xAxis1->GetBinLowEdge(iBin) << ".." << xAxis1->GetBinUpEdge(iBin) << ","
             " histogram2 = " << xAxis2->GetBinLowEdge(iBin) << ".." << xAxis2->GetBinUpEdge(iBin) << ')';
      }
    }
  }
}

bool
checkIfLabeledHistogram(const TH1 * histogram)
{
  bool areAllLabelled = true;
  const int nofBins = histogram->GetNbinsX() + 1;
  for(int iBin = 1; iBin < nofBins; ++iBin)
  {
    const std::string binLabel = histogram->GetXaxis()->GetBinLabel(iBin);
    if(binLabel.empty())
    {
      areAllLabelled = false;
      break;
    }
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

  const bool isLabelled = checkIfLabeledHistograms(histogramsToAdd);
  const int initBin = isLabelled ? 1 : 0;
  const int endBin = newHistogram->GetNbinsX() + (isLabelled ? 1 : 2);
  for(int iBin = initBin; iBin < endBin; ++iBin)
  {
    double sumBinContent = 0.;
    double sumBinError2  = 0.;
    for(const TH1 * const histogramToAdd: histogramsToAdd)
    {
      if(verbosity)
      {
        std::cout << "histogramToAdd = " << histogramToAdd->GetName() << ", "
                     "binContent = "     << histogramToAdd->GetBinContent(iBin) << ", "
                     "binError = "       << histogramToAdd->GetBinError(iBin) << '\n';
      }
      sumBinContent += histogramToAdd->GetBinContent(iBin);
      sumBinError2  += square(histogramToAdd->GetBinError(iBin));
    }

    if(verbosity)
    {
      std::cout << "bin #" << iBin << " (x =  " << newHistogram->GetBinCenter(iBin) << "): "
                   "sumBinContent = "           << sumBinContent << ", "
                   "sumBinError2 = "            << sumBinError2 << '\n';
    }
    newHistogram->SetBinContent(iBin, sumBinContent);
    assert(sumBinError2 >= 0.);
    newHistogram->SetBinError(iBin, std::sqrt(sumBinError2));
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

  const bool isLabelled = checkIfLabeledHistogram(histogramMinuend) && checkIfLabeledHistogram(histogramSubtrahend);
  const int initBin = isLabelled ? 1 : 0;
  const int endBin = histogramMinuend->GetNbinsX() + (isLabelled ? 1 : 2);
  for(int iBin = initBin; iBin < endBin; ++iBin)
  {
    if(verbosity)
    {
      std::cout << "bin #" << iBin << " (x =  " << newHistogram->GetBinCenter(iBin) << "): "
                   "minuend = " << histogramMinuend->GetBinContent(iBin)            << " +/- "
                                << histogramMinuend->GetBinError(iBin)              << ", "
                   "subtrahend = " << histogramSubtrahend->GetBinContent(iBin)      << " +/- "
                                   << histogramSubtrahend->GetBinError(iBin)        << '\n';
    }
    const double newBinContent =        histogramMinuend->GetBinContent(iBin) -       histogramSubtrahend->GetBinContent(iBin);
    const double newBinError2  = square(histogramMinuend->GetBinError(iBin)) + square(histogramSubtrahend->GetBinError(iBin));
    newHistogram->SetBinContent(iBin, newBinContent);
    assert(newBinError2 >= 0.);
    newHistogram->SetBinError(iBin, std::sqrt(newBinError2));
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
  const int numBins  = histogram->GetNbinsX();
  const int firstBin = includeUnderflowBin ? 0           : 1;
  const int lastBin  = includeOverflowBin  ? numBins + 1 : numBins;

  double sumBinContent = 0.;
  for(int iBin = firstBin; iBin <= lastBin; ++iBin)
  {
    sumBinContent += histogram->GetBinContent(iBin);
  }
  return sumBinContent;
}

double
compIntegralErr(const TH1 * histogram,
		bool includeUnderflowBin,
		bool includeOverflowBin)
{
  const int numBins  = histogram->GetNbinsX();
  const int firstBin = includeUnderflowBin ? 0           : 1;
  const int lastBin  = includeOverflowBin  ? numBins + 1 : numBins;

  double sumBinErr2 = 0.;
  for(int iBin = firstBin; iBin <= lastBin; ++iBin)
  {
    sumBinErr2 += square(histogram->GetBinError(iBin));
  }
  return std::sqrt(sumBinErr2);
}

void
makeBinContentsPositive(TH1 * histogram,
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

  const bool isLabelled = checkIfLabeledHistogram(histogram);
  const int initBin = isLabelled ? 1 : 0;
  const int endBin = histogram->GetNbinsX() + (isLabelled ? 1 : 2);
  for(int iBin = initBin; iBin < endBin; ++iBin)
  {
    const double binContent_original = histogram->GetBinContent(iBin);
    const double binError2_original = square(histogram->GetBinError(iBin));
    if(binContent_original < 0.)
    {
      const double binContent_modified = 0.;
      const double binError2_modified = binError2_original + square(binContent_original - binContent_modified);
      assert(binError2_modified >= 0.);

      if(verbosity)
      {
        std::cout << "bin #" << iBin << " (x =  " << histogram->GetBinCenter(iBin) << "): "
                     "binContent = " << binContent_original << " +/- " << std::sqrt(binError2_original) << " --> setting it to "
                     "binContent = " << binContent_modified << " +/- " << std::sqrt(binError2_modified) << '\n';
      }
      histogram->SetBinContent(iBin, binContent_modified);
      histogram->SetBinError(iBin, std::sqrt(binError2_modified));
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
      std::cout << "--> scaling histogram by factor = " << sf << '\n';
    }
    histogram->Scale(sf);
  }
  else
  {
    for(int iBin = initBin; iBin < endBin; ++iBin)
    {
      histogram->SetBinContent(iBin, 1.e-3/((endBin - 1) - initBin));
    }
  }

  if(verbosity)
  {
    std::cout << " integral(" << histogram->GetName() << ") = "
                              << histogram->Integral() << '\n';
  }
}

void
dumpHistogram(const TH1 * histogram)
{
  std::cout << "<dumpHistogram>:\n"
               "histogram = " << histogram->GetName() << "\n"
               "integral = "  << histogram->Integral() << '\n';

  const TAxis * const xAxis = histogram->GetXaxis();
  const int numBins_plus1 = xAxis->GetNbins() + 1;
  for(int idxBin = 1; idxBin < numBins_plus1; ++idxBin)
  {
    const double binCenter = xAxis->GetBinCenter(idxBin);
    const double binContent = histogram->GetBinContent(idxBin);
    const double binError = histogram->GetBinError(idxBin);
    std::cout << "bin #" << idxBin << " (x = " << binCenter << "): "
              << binContent << " +/- " << binError << '\n';
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
  const int numBins_plus1 = xAxis->GetNbins() + 1;

  std::vector<double> binning;
  for(int idxBin = 1; idxBin < numBins_plus1; ++idxBin)
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
  std::cout << "<compBinning>:\n";
  std::vector<double> histogramBinning;
  const TAxis * xAxis = histogram->GetXaxis();

  histogramBinning.push_back(xAxis->GetBinLowEdge(1));
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

  TArrayD binning_tarray(histogramBinning.size());
  for(std::size_t idxBin = 0; idxBin < histogramBinning.size(); ++idxBin)
  {
    binning_tarray[idxBin] = histogramBinning[idxBin];
  }

  std::cout << "binning = { ";
  for(std::size_t binIdx = 0; binIdx < histogramBinning.size(); ++binIdx)
  {
    if(binIdx < (histogramBinning.size() - 1))
    {
      std::cout << ", ";
    }
    std::cout << histogramBinning[binIdx];
  }
  std::cout << " }\n";
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

TH1* compRatioHistogram(const std::string& ratioHistogramName, const TH1* numerator, const TH1* denominator)
{
  TH1* histogramRatio = 0;
  
  if ( numerator->GetDimension() == denominator->GetDimension() &&
       numerator->GetNbinsX() == denominator->GetNbinsX() ) {
    histogramRatio = (TH1*)numerator->Clone(ratioHistogramName.data());
    histogramRatio->Divide(denominator);
    
    int nBins = histogramRatio->GetNbinsX();
    for ( int iBin = 1; iBin <= nBins; ++iBin ){
      double binContent = histogramRatio->GetBinContent(iBin);
      histogramRatio->SetBinContent(iBin, binContent - 1.);
    }
    
    histogramRatio->SetLineColor(numerator->GetLineColor());
    histogramRatio->SetLineWidth(numerator->GetLineWidth());
    histogramRatio->SetMarkerColor(numerator->GetMarkerColor());
    histogramRatio->SetMarkerStyle(numerator->GetMarkerStyle());
    histogramRatio->SetMarkerSize(numerator->GetMarkerSize());
  }

  return histogramRatio;
}

void divideByBinWidth(TH1* histogram)
{
  if ( !histogram ) return;
  TAxis* xAxis = histogram->GetXaxis();
  int numBins = xAxis->GetNbins();
  for ( int iBin = 1; iBin <= numBins; ++iBin ) {
    double binContent = histogram->GetBinContent(iBin);
    double binError = histogram->GetBinError(iBin);
    double binWidth = xAxis->GetBinWidth(iBin);
    histogram->SetBinContent(iBin, binContent/binWidth);
    histogram->SetBinError(iBin, binError/binWidth);
  }
}
