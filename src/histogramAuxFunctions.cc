#include "tthAnalysis/HiggsToTauTau/interface/histogramAuxFunctions.h"

#include "FWCore/Utilities/interface/Exception.h"

#include <TMath.h>
#include <TArrayD.h>
#include <TString.h>

#include <iostream>
#include <assert.h>

void fill(TH1* histogram, double x, double evtWeight, double evtWeightErr)
{
  TAxis* xAxis = histogram->GetXaxis();
  int bin = xAxis->FindBin(x);
  int numBins = xAxis->GetNbins();
  if ( !(bin >= 1 && bin <= numBins) ) return;
  double binContent = histogram->GetBinContent(bin);
  double binError = histogram->GetBinError(bin);
  histogram->SetBinContent(bin, binContent + evtWeight);
  histogram->SetBinError(bin, TMath::Sqrt(binError*binError + evtWeight*evtWeight + evtWeightErr*evtWeightErr));
}

void fillWithOverFlow(TH1* histogram, double x, double evtWeight, double evtWeightErr)
{
  TAxis* xAxis = histogram->GetXaxis();
  int bin = xAxis->FindBin(x);
  int numBins = xAxis->GetNbins();
  if ( bin < 1       ) bin = 1;
  if ( bin > numBins ) bin = numBins;
  double binContent = histogram->GetBinContent(bin);
  double binError = histogram->GetBinError(bin);
  histogram->SetBinContent(bin, binContent + evtWeight);
  histogram->SetBinError(bin, TMath::Sqrt(binError*binError + evtWeight*evtWeight + evtWeightErr*evtWeightErr));
}

void fill2d(TH2* histogram, double x, double y, double evtWeight, double evtWeightErr)
{
  TAxis* xAxis = histogram->GetXaxis();
  int binX = xAxis->FindBin(x);
  int numBinsX = xAxis->GetNbins();
  if ( !(binX >= 1 && binX <= numBinsX) ) return;
  TAxis* yAxis = histogram->GetYaxis();
  int binY = yAxis->FindBin(y);
  int numBinsY = yAxis->GetNbins();
  if ( !(binY >= 1 && binY <= numBinsY) ) return;
  double binContent = histogram->GetBinContent(binX, binY);
  double binError = histogram->GetBinError(binX, binY);
  histogram->SetBinContent(binX, binY, binContent + evtWeight);
  histogram->SetBinError(binX, binY, TMath::Sqrt(binError*binError + evtWeight*evtWeight + evtWeightErr*evtWeightErr));
}

void fillWithOverFlow2d(TH2* histogram, double x, double y, double evtWeight, double evtWeightErr)
{
  TAxis* xAxis = histogram->GetXaxis();
  int binX = xAxis->FindBin(x);
  int numBinsX = xAxis->GetNbins();
  if ( binX < 1        ) binX = 1;
  if ( binX > numBinsX ) binX = numBinsX;
  TAxis* yAxis = histogram->GetYaxis();
  int binY = yAxis->FindBin(y);
  int numBinsY = yAxis->GetNbins();
  if ( binY < 1        ) binY = 1;
  if ( binY > numBinsY ) binY = numBinsY;
  double binContent = histogram->GetBinContent(binX, binY);
  double binError = histogram->GetBinError(binX, binY);
  histogram->SetBinContent(binX, binY, binContent + evtWeight);
  histogram->SetBinError(binX, binY, TMath::Sqrt(binError*binError + evtWeight*evtWeight + evtWeightErr*evtWeightErr));
}

//
//-------------------------------------------------------------------------------
//

double getLogWeight(double weight)
{
  if ( weight > 0. ) return TMath::Log(weight);
  else return -1.e+6;
}

//
//-------------------------------------------------------------------------------
//

void checkCompatibleBinning(const TH1* histogram1, const TH1* histogram2)
{
  if ( histogram1 && histogram2 ) {
    if ( !(histogram1->GetNbinsX() == histogram2->GetNbinsX()) )
      throw cms::Exception("checkCompatibleBinning") 
	<< "Histograms " << histogram1->GetName() << " and " << histogram2->GetName() << " have incompatible binning !!\n"
	<< " (NbinsX: histogram1 = " << histogram1->GetNbinsX() << ", histogram2 = " << histogram2->GetNbinsX() << ")\n";
    const TAxis* xAxis1 = histogram1->GetXaxis();
    const TAxis* xAxis2 = histogram2->GetXaxis();
    int numBins = xAxis1->GetNbins();
    for ( int iBin = 1; iBin <= numBins; ++iBin ) {
      double binWidth = 0.5*(xAxis1->GetBinWidth(iBin) + xAxis2->GetBinWidth(iBin));
      double dBinLowEdge = xAxis1->GetBinLowEdge(iBin) - xAxis2->GetBinLowEdge(iBin);
      double dBinUpEdge = xAxis1->GetBinUpEdge(iBin) - xAxis2->GetBinUpEdge(iBin);
      if ( !(dBinLowEdge < (1.e-3*binWidth) && dBinUpEdge < (1.e-3*binWidth)) )
	throw cms::Exception("checkCompatibleBinning") 
	  << "Histograms " << histogram1->GetName() << " and " << histogram2->GetName() << " have incompatible binning !!\n"
	  << " (bin #" << iBin << ": histogram1 = " << xAxis1->GetBinLowEdge(iBin) << ".." << xAxis1->GetBinUpEdge(iBin) << ","
	  << " histogram2 = " << xAxis2->GetBinLowEdge(iBin) << ".." << xAxis2->GetBinUpEdge(iBin) << ")\n";
    }
  }
}

TH1* addHistograms(const std::string& newHistogramName, const TH1* histogram1, const TH1* histogram2, int verbosity)
{
  std::vector<TH1*> histogramsToAdd;
  histogramsToAdd.push_back(const_cast<TH1*>(histogram1));
  histogramsToAdd.push_back(const_cast<TH1*>(histogram2));
  return addHistograms(newHistogramName, histogramsToAdd, verbosity);
}

namespace
{
  double square(double x)
  {
    return x*x;
  }
}

TH1* addHistograms(const std::string& newHistogramName, const std::vector<TH1*>& histogramsToAdd, int verbosity)
{
  if ( verbosity ) {
    std::cout << "<addHistograms>:" << std::endl;
    std::cout << " newHistogramName = " << newHistogramName << std::endl;
  }
  if ( histogramsToAdd.size() == 0 )
    throw cms::Exception("addHistograms") 
      << "No histograms given to add !!\n";
  const TH1* histogramRef = histogramsToAdd.front();
  if ( verbosity ) {
    std::cout << "histogramRef = " << histogramRef->GetName() << std::endl;
    std::cout << "#histogramsToAdd = " << histogramsToAdd.size() << std::endl;
  }
  for ( std::vector<TH1*>::const_iterator histogramToAdd = histogramsToAdd.begin();
	histogramToAdd != histogramsToAdd.end(); ++histogramToAdd ) {
    if ( (*histogramToAdd) == histogramRef ) continue;
    if ( verbosity ) {
      std::cout << "histogramToAdd = " << (*histogramToAdd)->GetName() << ", integral = " << (*histogramToAdd)->Integral() << std::endl;
    }
    checkCompatibleBinning(*histogramToAdd, histogramRef);
  }
  TH1* newHistogram = (TH1*)histogramRef->Clone(newHistogramName.data());
  newHistogram->Reset();
  if ( !newHistogram->GetSumw2N() ) newHistogram->Sumw2();
  int numBins = newHistogram->GetNbinsX();
  //TArrayD histogramRefBinning = getBinning(histogramRef);
  //int numBins = histogramRefBinning.GetSize() - 1;
  //TH1* newHistogram = new TH1D(newHistogramName.data(), newHistogramName.data(), numBins, histogramRefBinning.GetArray());
  for ( int iBin = 0; iBin <= (numBins + 1); ++iBin ) {
    double sumBinContent = 0.;
    double sumBinError2 = 0.;
    for ( std::vector<TH1*>::const_iterator histogramToAdd = histogramsToAdd.begin();
	  histogramToAdd != histogramsToAdd.end(); ++histogramToAdd ) {
      if ( verbosity ) {
	std::cout << "histogramToAdd = " << (*histogramToAdd)->GetName() << ", binContent = " << (*histogramToAdd)->GetBinContent(iBin) << ", binError = " << (*histogramToAdd)->GetBinError(iBin) << std::endl;
      }
      sumBinContent += (*histogramToAdd)->GetBinContent(iBin);
      sumBinError2 += square((*histogramToAdd)->GetBinError(iBin));
    }
    if ( verbosity ) {
      std::cout << "bin #" << iBin << " (x =  " << newHistogram->GetBinCenter(iBin) << "): sumBinContent = " << sumBinContent << ", sumBinError2 = " << sumBinError2 << std::endl;
    }
    newHistogram->SetBinContent(iBin, sumBinContent);
    assert(sumBinError2 >= 0.);
    newHistogram->SetBinError(iBin, TMath::Sqrt(sumBinError2));
  }
  return newHistogram;
}

TH1* subtractHistograms(const std::string& newHistogramName, const TH1* histogramMinuend, const TH1* histogramSubtrahend, int verbosity)
{
  if ( verbosity ) {
    std::cout << "<subtractHistograms>:" << std::endl;
    std::cout << " newHistogramName = " << newHistogramName << std::endl;
  }
  checkCompatibleBinning(histogramMinuend, histogramSubtrahend);
  TH1* newHistogram = (TH1*)histogramMinuend->Clone(newHistogramName.data());
  newHistogram->Reset();
  if ( !newHistogram->GetSumw2N() ) newHistogram->Sumw2();
  int numBins = newHistogram->GetNbinsX();
  //TArrayD histogramBinning = getBinning(histogramMinuend);
  //int numBins = histogramBinning.GetSize() - 1;
  //TH1* newHistogram = new TH1D(newHistogramName.data(), newHistogramName.data(), numBins, histogramBinning.GetArray());
  for ( int iBin = 0; iBin <= (numBins + 1); ++iBin ) {
    if ( verbosity ) {
      std::cout << "bin #" << iBin << " (x =  " << newHistogram->GetBinCenter(iBin) << "):"
		<< " minuend = " << histogramMinuend->GetBinContent(iBin) << " +/- " << histogramMinuend->GetBinError(iBin) << ","
		<< " subtrahend = " << histogramSubtrahend->GetBinContent(iBin) << " +/- " << histogramSubtrahend->GetBinError(iBin) << std::endl;
    }
    double newBinContent = histogramMinuend->GetBinContent(iBin) - histogramSubtrahend->GetBinContent(iBin);
    double newBinError2 = square(histogramMinuend->GetBinError(iBin)) + square(histogramSubtrahend->GetBinError(iBin));
    newHistogram->SetBinContent(iBin, newBinContent);
    assert(newBinError2 >= 0.);
    newHistogram->SetBinError(iBin, TMath::Sqrt(newBinError2));
  }
  return newHistogram;
}

TH1* subtractHistograms(const std::string& newHistogramName, const TH1* histogram, const std::vector<TH1*>& histogramsToSubtract, int verbosity)
{
  if ( verbosity ) {
    std::cout << "<subtractHistograms>:" << std::endl;
    std::cout << " newHistogramName = " << newHistogramName << std::endl;
    std::cout << "histogram = " << histogram->GetName() << std::endl;
    std::cout << "#histogramsToSubtract = " << histogramsToSubtract.size() << std::endl;
  }
  if ( !histogram ) 
    throw cms::Exception("subtractHistograms") 
      << "No histograms given to subtract !!\n";
  TH1* newHistogram = 0;
  if ( histogramsToSubtract.size() == 0 ) {
    newHistogram = (TH1*)histogram->Clone(newHistogramName.data());
  } else {
    TH1* histogramSubtrahend = addHistograms("subtractHistogramsTMP", histogramsToSubtract);
    newHistogram = subtractHistograms(newHistogramName, histogram, histogramSubtrahend, verbosity);
    delete histogramSubtrahend;
  }
  return newHistogram;
}

double compIntegral(TH1* histogram, bool includeUnderflowBin, bool includeOverflowBin)
{
  double sumBinContent = 0.;
  int numBins = histogram->GetNbinsX();
  int firstBin = ( includeUnderflowBin ) ? 0 : 1;
  int lastBin = ( includeOverflowBin  ) ? (numBins + 1) : numBins;
  for ( int iBin = firstBin; iBin <= lastBin; ++iBin ) {
    sumBinContent += histogram->GetBinContent(iBin);
  }
  return sumBinContent;
}

void makeBinContentsPositive(TH1* histogram, int verbosity)
{
  if ( verbosity ) {
    std::cout << "<makeBinContentsPositive>:" << std::endl;
    std::cout << " integral(" << histogram->GetName() << ") = " << histogram->Integral() << std::endl;
  }
  double integral_original = compIntegral(histogram, true, true);
  if ( integral_original < 0. ) integral_original = 0.;
  if ( verbosity ) {
    std::cout << " integral_original = " << integral_original << std::endl;
  }
  int numBins = histogram->GetNbinsX();
  for ( int iBin = 0; iBin <= (numBins + 1); ++iBin ) {
    double binContent_original = histogram->GetBinContent(iBin);
    double binError2_original = square(histogram->GetBinError(iBin));
    if ( binContent_original < 0. ) {
      double binContent_modified = 0.;
      double binError2_modified = binError2_original + square(binContent_original - binContent_modified);
      assert(binError2_modified >= 0.);
      if ( verbosity ) {
	std::cout << "bin #" << iBin << " (x =  " << histogram->GetBinCenter(iBin) << "): binContent = " << binContent_original << " +/- " << TMath::Sqrt(binError2_original) 
		  << " --> setting it to binContent = " << binContent_modified << " +/- " << TMath::Sqrt(binError2_modified) << std::endl;
      }
      histogram->SetBinContent(iBin, binContent_modified);
      histogram->SetBinError(iBin, TMath::Sqrt(binError2_modified));
    }
  }
  double integral_modified = compIntegral(histogram, true, true);
  if ( integral_modified < 0. ) integral_modified = 0.;
  if ( verbosity ) {
    std::cout << " integral_modified = " << integral_modified << std::endl;
  }
  if ( integral_modified > 0. ) {
    double sf = integral_original/integral_modified;
    if ( verbosity ) {
      std::cout << "--> scaling histogram by factor = " << sf << std::endl;
    }
    histogram->Scale(sf);
  } else {
    for ( int iBin = 0; iBin <= (numBins + 1); ++iBin ) {
      histogram->SetBinContent(iBin, 0.);
    }
  }
  if ( verbosity ) {
    std::cout << " integral(" << histogram->GetName() << ") = " << histogram->Integral() << std::endl;
  }
}

void dumpHistogram(const TH1* histogram)
{
  std::cout << "<dumpHistogram>:" << std::endl;
  std::cout << "histogram = " << histogram->GetName() << std::endl;
  std::cout << "integral = " << histogram->Integral() << std::endl;
  const TAxis* xAxis = histogram->GetXaxis();
  int numBins = xAxis->GetNbins();
  for ( int idxBin = 1; idxBin <= numBins; ++idxBin ) {
    double binCenter = xAxis->GetBinCenter(idxBin);
    double binContent = histogram->GetBinContent(idxBin);
    double binError = histogram->GetBinError(idxBin); 
    std::cout << "bin #" << idxBin << " (x = " << binCenter << "): " << binContent << " +/- " << binError << std::endl; 
  }
}

//
//-------------------------------------------------------------------------------
//

TDirectory* getDirectory(const TFile* inputFile, const std::string& dirName, bool enableException)
{
  std::cout << "<getDirectory>:" << std::endl;
  std::cout << " inputFile = " << inputFile->GetName() << std::endl;
  std::cout << " dirName = " << dirName << std::endl;
  //std::cout << " enableException = " << enableException << std::endl;
  std::string dirName_tmp = ( dirName.find_last_of('/') == (dirName.length() - 1) ) ? std::string(dirName, 0, dirName.length() - 1) : dirName;
  TDirectory* dir = dynamic_cast<TDirectory*>((const_cast<TFile*>(inputFile))->Get(dirName_tmp.data()));
  if ( enableException && !dir ) {
    inputFile->ls();
    throw cms::Exception("getDirectory") 
      << "Failed to find directory = '" << dirName << "' in file = '" << inputFile->GetName() << "' !!\n";
  }
  std::cout << "--> returning dir = " << dir << ": name = '" << dir->GetName() << "'" << std::endl;    
  return dir;
}

TDirectory* getSubdirectory(const TDirectory* dir, const std::string& subdirName, bool enableException)
{
  std::cout << "<getSubdirectory>:" << std::endl;
  std::cout << " dir = " << dir->GetName() << std::endl;
  std::cout << " subdirName = " << subdirName << std::endl;
  //std::cout << " enableException = " << enableException << std::endl;
  std::string subdirName_tmp = ( subdirName.find_last_of('/') == (subdirName.length() - 1) ) ? std::string(subdirName, 0, subdirName.length() - 1) : subdirName;
  TDirectory* subdir = dynamic_cast<TDirectory*>((const_cast<TDirectory*>(dir))->Get(subdirName_tmp.data()));
  if ( enableException && !subdir ) {
    dir->ls();
    throw cms::Exception("getSubdirectory") 
      << "Failed to find subdirectory = '" << subdirName << "' in directory = " << dir << ": name = '" << dir->GetName() << "' !!\n";    
  }
  std::cout << "--> returning subdir = " << subdir << ": name = '" << subdir->GetName() << "'" << std::endl;    
  return subdir;
}

TH1* getHistogram(const TDirectory* dir, const std::string& process, const std::string& histogramName, const std::string& central_or_shift, bool enableException)
{
  //std::cout << "<getHistogram>:" << std::endl;
  //std::cout << " dir = " << dir->GetName() << std::endl;
  //std::cout << " process = " << process << std::endl;
  //std::cout << " histogramName = " << histogramName << std::endl;
  //std::cout << " central_or_shift = " << central_or_shift << std::endl;
  //std::cout << " enableException = " << enableException << std::endl;
  std::string histogramName_full = Form("%s/", process.data());
  if ( !(central_or_shift == "" || central_or_shift == "central") ) {
    histogramName_full.append(Form("%s_%s", central_or_shift.data(), histogramName.data()));
  } else {
    histogramName_full.append(histogramName);
  }
  TH1* histogram = dynamic_cast<TH1*>((const_cast<TDirectory*>(dir))->Get(histogramName_full.data()));
  if ( enableException && !histogram ) {
    dir->ls();
    throw cms::Exception("getHistogram") 
      << "Failed to find histogram = '" << histogramName_full << "' in directory = " << dir << ": name = '" << dir->GetName() << "' !!\n";    
  }
  return histogram;
}

TDirectory* createSubdirectory(TDirectory* dir, const std::string& subdirName)
{
  dir->cd();
  if ( !dir->Get(subdirName.data()) ) {
    dir->mkdir(subdirName.data());
  }
  TDirectory* subdir = dynamic_cast<TDirectory*>(dir->Get(subdirName.data()));
  assert(subdir);
  return subdir;
}

TDirectory* createSubdirectory_recursively(TFileDirectory& dir, const std::string& fullSubdirName)
{
  TString fullSubdirName_tstring = fullSubdirName.data();
  TObjArray* subdirNames = fullSubdirName_tstring.Tokenize("/");
  int numSubdirectories = subdirNames->GetEntries();
  TDirectory* parent = dir.getBareDirectory();
  for ( int iSubdirectory = 0; iSubdirectory < numSubdirectories; ++iSubdirectory ) {
    const TObjString* subdirName = dynamic_cast<TObjString*>(subdirNames->At(iSubdirectory));
    assert(subdirName);
    TDirectory* subdir = createSubdirectory(parent, subdirName->GetString().Data());
    parent = subdir;
  }
  return parent;
}

//
//-------------------------------------------------------------------------------
//

TArrayD getBinning(const TH1* histogram)
{
  const TAxis* xAxis = histogram->GetXaxis();
  int numBins = xAxis->GetNbins();
  TArrayD binning(numBins + 1);
  for ( int iBin = 1; iBin <= numBins; ++iBin ) {
    binning[iBin - 1] = xAxis->GetBinLowEdge(iBin);
    binning[iBin] = xAxis->GetBinUpEdge(iBin);
  }
  return binning;
}

TH1* getRebinnedHistogram1d(const TH1* histoOriginal, 
			    unsigned numBins_rebinned, const TArrayD& binEdges_rebinned)
{
  std::string histoRebinnedName = std::string(histoOriginal->GetName()).append("_rebinned");
  TH1* histoRebinned = new TH1D(
    histoRebinnedName.data(), histoOriginal->GetTitle(), 
    binEdges_rebinned.GetSize() - 1, binEdges_rebinned.GetArray());
  histoRebinned->Sumw2();
  const TAxis* axis_original = histoOriginal->GetXaxis();
  int numBins_original = axis_original->GetNbins();
  for ( int idxBin = 1; idxBin <= numBins_original; ++idxBin ) {
    double binContent_original = histoOriginal->GetBinContent(idxBin);
    double binError_original = histoOriginal->GetBinError(idxBin);
    double binCenter_original = axis_original->GetBinCenter(idxBin);
    int binIndex_rebinned = histoRebinned->FindBin(binCenter_original);
    double binContent_rebinned = histoRebinned->GetBinContent(binIndex_rebinned);
    binContent_rebinned += binContent_original;
    histoRebinned->SetBinContent(binIndex_rebinned, binContent_rebinned);   
    double binError_rebinned = histoRebinned->GetBinError(binIndex_rebinned);
    binError_rebinned = TMath::Sqrt(binError_rebinned*binError_rebinned + binError_original*binError_original);
    histoRebinned->SetBinError(binIndex_rebinned, binError_rebinned);
  }
  return histoRebinned;
}

TH2* getRebinnedHistogram2d(const TH1* histoOriginal, 
			    unsigned numBinsX_rebinned, const TArrayD& binEdgesX_rebinned,
			    unsigned numBinsY_rebinned, const TArrayD& binEdgesY_rebinned)
{
  std::string histoRebinnedName = std::string(histoOriginal->GetName()).append("_rebinned");
  TH2D* histoRebinned = new TH2D(
    histoRebinnedName.data(), histoOriginal->GetTitle(), 
    binEdgesX_rebinned.GetSize() - 1, binEdgesX_rebinned.GetArray(), 
    binEdgesY_rebinned.GetSize() - 1, binEdgesY_rebinned.GetArray());
  histoRebinned->Sumw2();
  const TAxis* xAxis_original = histoOriginal->GetXaxis();
  const TAxis* yAxis_original = histoOriginal->GetYaxis();
  int numBinsX_original = xAxis_original->GetNbins();
  for ( int idxBinX = 1; idxBinX <= numBinsX_original; ++idxBinX ) {
    int numBinsY_original = yAxis_original->GetNbins();
    for ( int idxBinY = 1; idxBinY <= numBinsY_original; ++idxBinY ) {
      double binContent_original = histoOriginal->GetBinContent(idxBinX, idxBinY);
      double binError_original = histoOriginal->GetBinError(idxBinX, idxBinY);     
      double binCenterX_original = xAxis_original->GetBinCenter(idxBinX);
      double binCenterY_original = yAxis_original->GetBinCenter(idxBinY);
      int binIndex_rebinned = histoRebinned->FindBin( binCenterX_original, binCenterY_original);
      double binContent_rebinned = histoRebinned->GetBinContent(binIndex_rebinned);
      binContent_rebinned += binContent_original;
      histoRebinned->SetBinContent(binIndex_rebinned, binContent_rebinned);    
      double binError_rebinned = histoRebinned->GetBinError(binIndex_rebinned);
      binError_rebinned = TMath::Sqrt(binError_rebinned*binError_rebinned + binError_original*binError_original);
      histoRebinned->SetBinError(binIndex_rebinned, binError_rebinned);
    }
  }
  return histoRebinned;
}
