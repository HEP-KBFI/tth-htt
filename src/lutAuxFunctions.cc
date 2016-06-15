#include "tthAnalysis/HiggsToTauTau/interface/lutAuxFunctions.h"

#include "FWCore/Utilities/interface/Exception.h" // cms::Exception

#include <TAxis.h> // TAxis

#include <iostream>
#include <iomanip>

/**
 * @brief Open ROOT file the name of which is given as function argument
 * @param fileName name of ROOT file
 * @return pointer to TFile object
 */
TFile* openFile(const edm::FileInPath& fileName)
{
  if ( fileName.fullPath() == "" ) 
    throw cms::Exception("openFile") 
      << " Failed to find file = " << fileName << " !!\n";
  TFile* inputFile = new TFile(fileName.fullPath().data());
  return inputFile;
}

/**
 * @brief Load one-dimensional histogram (TH1) from ROOT file 
 * @param fileName name of ROOT file, histogramName name of the histogram
 * @return pointer to TH1 object
 */
TH1* loadTH1(TFile* inputFile, const std::string& histogramName)
{
  TH1* histogram = dynamic_cast<TH1*>(inputFile->Get(histogramName.data()));
  if ( !histogram ) 
    throw cms::Exception("loadTH1") 
      << " Failed to load TH1 = " << histogramName.data() << " from file = " << inputFile->GetName() << " !!\n";
  std::string histogramName_cloned = Form("%s_cloned", histogram->GetName());
  TH1* histogram_cloned = (TH1*)histogram->Clone(histogramName_cloned.data());
  return histogram_cloned;
}
/**
 * @brief Load two-dimensional histogram (TH2) from ROOT file 
 * @param fileName name of ROOT file, histogramName name of the histogram
 * @return pointer to TH2 object
 */
TH2* loadTH2(TFile* inputFile, const std::string& histogramName)
{
  TH2* histogram = dynamic_cast<TH2*>(inputFile->Get(histogramName.data()));
  if ( !histogram ) 
    throw cms::Exception("loadTH2") 
      << " Failed to load TH2 = " << histogramName.data() << " from file = " << inputFile->GetName() << " !!\n";
  std::string histogramName_cloned = Form("%s_cloned", histogram->GetName());
  TH2* histogram_cloned = (TH2*)histogram->Clone(histogramName_cloned.data());
  return histogram_cloned;
}

/**
 * @brief Retrieve data/MC scale-factor for given pT or eta value from one-dimensional histogram
 * @param lut pointer to histogram storing data/MC scale-factors as function of pT or eta, pt_or_eta either transverse momentum or pseudo-rapidity of lepton
 * @return data/MC scale-factor
 */
double get_sf_from_TH1(TH1* lut, double pt_or_eta)
{
  TAxis* xAxis = lut->GetXaxis();
  int numBins_x = xAxis->GetNbins();
  int idxBin_x = xAxis->FindBin(pt_or_eta);
  if ( idxBin_x <  1         ) idxBin_x = 1;
  if ( idxBin_x >= numBins_x ) idxBin_x = numBins_x;
  double sf = lut->GetBinContent(idxBin_x);
  return sf;
}
/**
 * @brief Retrieve data/MC scale-factor for given pT and eta value from two-dimensional histogram
 * @param lut pointer to histogram storing data/MC scale-factors as function of pT and eta, pT transverse momentum of lepton, eta pseudo-rapidity of lepton
 * @return data/MC scale-factor
 */
double get_sf_from_TH2(TH2* lut, double pt, double eta)
{
  TAxis* xAxis = lut->GetXaxis();
  int numBins_x = xAxis->GetNbins();
  int idxBin_x = xAxis->FindBin(pt);
  if ( idxBin_x <  1         ) idxBin_x = 1;
  if ( idxBin_x >= numBins_x ) idxBin_x = numBins_x;
  TAxis* yAxis = lut->GetYaxis();
  int numBins_y = yAxis->GetNbins();
  double abs_eta = fabs(eta);
  int idxBin_y = yAxis->FindBin(abs_eta);
  if ( idxBin_y <  1         ) idxBin_y = 1;
  if ( idxBin_y >= numBins_y ) idxBin_y = numBins_y;
  double sf = lut->GetBinContent(idxBin_x, idxBin_y);
  return sf;
}
