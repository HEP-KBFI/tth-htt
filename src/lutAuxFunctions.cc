#include "tthAnalysis/HiggsToTauTau/interface/lutAuxFunctions.h"

#include "FWCore/Utilities/interface/Exception.h" // cms::Exception

#include <TAxis.h> // TAxis

#include <iostream>
#include <iomanip>
#include <assert.h>

using namespace lut;

const double epsilon = 1.e-3;

/**
 * @brief Open ROOT file the name of which is given as function argument
 * @param fileName: name of ROOT file
 * @return pointer to TFile object
 */
TFile* openFile(const LocalFileInPath& fileName)
{
  if ( fileName.fullPath() == "" ) 
    throw cms::Exception("openFile") 
      << " Failed to find file = " << fileName << " !!\n";
  TFile* inputFile = new TFile(fileName.fullPath().data());
  return inputFile;
}

/**
 * @brief Load one-dimensional histogram (TH1) from ROOT file 
 * @param fileName: name of ROOT file; histogramName: name of the histogram
 * @return pointer to TH1 object
 */
TH1* loadTH1(TFile* inputFile, const std::string& histogramName)
{
  TH1* histogram = dynamic_cast<TH1*>(inputFile->Get(histogramName.data()));
  if ( !histogram ) 
    throw cms::Exception("loadTH1") 
      << " Failed to load TH1 = " << histogramName.data() << " from file = " << inputFile->GetName() << " !!\n";
  //std::string histogramName_cloned = Form("%s_cloned", histogram->GetName());
  //TH1* histogram_cloned = (TH1*)histogram->Clone(histogramName_cloned.data());
  //return histogram_cloned;
  return histogram;
}
/**
 * @brief Load two-dimensional histogram (TH2) from ROOT file 
 * @param fileName: name of ROOT file; histogramName: name of the histogram
 * @return pointer to TH2 object
 */
TH2* loadTH2(TFile* inputFile, const std::string& histogramName)
{
  TH2* histogram = dynamic_cast<TH2*>(inputFile->Get(histogramName.data()));
  if ( !histogram ) 
    throw cms::Exception("loadTH2") 
      << " Failed to load TH2 = " << histogramName.data() << " from file = " << inputFile->GetName() << " !!\n";
  //std::string histogramName_cloned = Form("%s_cloned", histogram->GetName());
  //TH2* histogram_cloned = (TH2*)histogram->Clone(histogramName_cloned.data());
  //return histogram_cloned;
  return histogram;
}
/**
 * @brief Load graph (TGraph) from ROOT file 
 * @param fileName: name of ROOT file; graphName: name of the graph
 * @return pointer to TGraph object
 */
TGraph* loadTGraph(TFile* inputFile, const std::string& graphName)
{
  TGraph* graph = dynamic_cast<TGraph*>(inputFile->Get(graphName.data()));
  if ( !graph ) 
    throw cms::Exception("loadTGraph") 
      << " Failed to load TGraph = " << graphName.data() << " from file = " << inputFile->GetName() << " !!\n";
  //std::string graphName_cloned = Form("%s_cloned", graph->GetName());
  //TGraph* graph_cloned = (TGraph*)graph->Clone(graphName_cloned.data());
  //return graph_cloned;
  return graph;
}

/**
 * @brief Retrieve data/MC scale-factor for given pT or eta value from one-dimensional histogram
 * @param lut: pointer to histogram storing data/MC scale-factors as function of pT or eta; x: transverse momentum respectively pseudo-rapidity of lepton
 * @return data/MC scale-factor
 */
double getSF_from_TH1(TH1* lut, double x)
{
  TAxis* xAxis = lut->GetXaxis();
  int numBins_x = xAxis->GetNbins();
  int idxBin_x = xAxis->FindBin(x);
  if ( idxBin_x <  1         ) idxBin_x = 1;
  if ( idxBin_x >= numBins_x ) idxBin_x = numBins_x;
  double sf = lut->GetBinContent(idxBin_x);
  return sf;
}
/**
 * @brief Retrieve data/MC scale-factor for given pT and eta value from two-dimensional histogram
 * @param lut: pointer to histogram storing data/MC scale-factors as function of pT and eta; x, y: transverse momentum respectively pseudo-rapidity of lepton
 * @return data/MC scale-factor
 */
double getSF_from_TH2(TH2* lut, double x, double y)
{
  TAxis* xAxis = lut->GetXaxis();
  int numBins_x = xAxis->GetNbins();
  int idxBin_x = xAxis->FindBin(x);
  if ( idxBin_x <  1         ) idxBin_x = 1;
  if ( idxBin_x >= numBins_x ) idxBin_x = numBins_x;
  TAxis* yAxis = lut->GetYaxis();
  int numBins_y = yAxis->GetNbins();
  int idxBin_y = yAxis->FindBin(y);
  if ( idxBin_y <  1         ) idxBin_y = 1;
  if ( idxBin_y >= numBins_y ) idxBin_y = numBins_y;
  double sf = lut->GetBinContent(idxBin_x, idxBin_y);
  return sf;
}
double getSF_from_TH2Poly(TH2* lut, double x, double y)
{
  TAxis* xAxis = lut->GetXaxis();
  double xMin = xAxis->GetXmin();
  double xMax = xAxis->GetXmax();
  if ( x < (xMin + epsilon) ) x = xMin + epsilon;
  if ( x > (xMax - epsilon) ) x = xMax - epsilon;
  TAxis* yAxis = lut->GetYaxis();
  double yMin = yAxis->GetXmin();
  double yMax = yAxis->GetXmax();
  if ( y < (yMin + epsilon) ) y = yMin + epsilon;
  if ( y > (yMax - epsilon) ) y = yMax - epsilon;
  int idxBin = lut->FindBin(x, y);
  double sf = lut->GetBinContent(idxBin);
  return sf;
}
/**
 * @brief Retrieve data/MC scale-factor for given pT or eta value from a graph
 * @param lut: pointer to graph storing data/MC scale-factors as function of pT or eta; x: transverse momentum respectively pseudo-rapidity of lepton
 * @return data/MC scale-factor
 */
double getSF_from_TGraph(TGraph* lut, double x)
{
  TAxis* xAxis = lut->GetXaxis();
  double xMin = xAxis->GetXmin();
  double xMax = xAxis->GetXmax();
  if ( x < xMin ) x = xMin;
  if ( x > xMax ) x = xMax;
  double sf = lut->Eval(x);
  return sf;
}  

//-------------------------------------------------------------------------------
lutWrapperBase::lutWrapperBase()
  : inputFile_(0)
  , lutTypeX_(kUndefined)
  , lutTypeY_(kUndefined)
  , xMin_(-1.)
  , xMax_(-1.)
  , yMin_(-1.)
  , yMax_(-1.)
{}

lutWrapperBase::lutWrapperBase(std::map<std::string, TFile*>& inputFiles, const std::string& inputFileName, const std::string& lutName, int lutType,
                               double xMin, double xMax, double yMin, double yMax)
  : inputFileName_(inputFileName)
  , inputFile_(0)
  , lutName_(lutName)
  , xMin_(xMin)
  , xMax_(xMax)
  , yMin_(yMin)
  , yMax_(yMax)
{
  if      ( lutType == kXpt        || lutType == kXptYpt     || lutType == kXptYeta    || lutType == kXptYabsEta ) lutTypeX_ = kPt;
  else if ( lutType == kXeta       || lutType == kXetaYpt                                                        ) lutTypeX_ = kEta;
  else if ( lutType == kXabsEta    || lutType == kXabsEtaYpt                                                     ) lutTypeX_ = kAbsEta;
  else assert(0);
  if ( xMin_ != -1. && xMax_ != -1. ) assert(xMax_ > xMin_);
  if      ( lutType == kXpt        || lutType == kXeta       || lutType == kXabsEta                              ) lutTypeY_ = kUndefined;
  else if ( lutType == kXptYpt     || lutType == kXetaYpt    || lutType == kXabsEtaYpt                           ) lutTypeY_ = kPt;
  else if ( lutType == kXptYeta                                                                                  ) lutTypeY_ = kEta;
  else if ( lutType == kXptYabsEta                                                                               ) lutTypeY_ = kAbsEta;
  else assert(0);
  if ( lutTypeY_ == kUndefined ) {
    yMin_ = -1.;
    yMax_ = -1.;
  }
  if ( yMin_ != -1. && yMax_ != -1. ) assert(yMax_ > yMin_);
  if ( inputFiles.find(inputFileName) != inputFiles.end() ) {
    inputFile_ = inputFiles[inputFileName];
  } else {
    inputFile_ = openFile(LocalFileInPath(inputFileName_));
    inputFiles[inputFileName] = inputFile_;
  }
}

double lutWrapperBase::getSF(double pt, double eta)
{
  double x = 0.;
  if      ( lutTypeX_ == kPt     ) x = pt;
  else if ( lutTypeX_ == kEta    ) x = eta;
  else if ( lutTypeX_ == kAbsEta ) x = std::fabs(eta);
  double y = 0.;
  if      ( lutTypeY_ == kPt     ) y = pt;
  else if ( lutTypeY_ == kEta    ) y = eta;
  else if ( lutTypeY_ == kAbsEta ) y = std::fabs(eta);
  return getSF_private(x, y);
}

double get_from_lut(const vLutWrapperBase& corrections, double pt, double eta, bool isDEBUG)
{
  if ( isDEBUG ) {
    std::cout << "<get_from_lut>:" << std::endl;
  }
  double sf = 1.;
  for ( vLutWrapperBase::const_iterator correction = corrections.begin();
	correction != corrections.end(); ++correction ) {    
    sf *= (*correction)->getSF(pt, eta);
    if ( isDEBUG ) {
      std::cout << "pT = " << pt << ", eta = " << eta << std::endl;
      std::cout << "LUT: inputFileName = " << (*correction)->inputFileName() << ", lutName = " << (*correction)->lutName() 
		<< " --> SF = " << (*correction)->getSF(pt, eta) << std::endl;
    }
  }
  return sf;
}
//-------------------------------------------------------------------------------


//-------------------------------------------------------------------------------
lutWrapperTH1::lutWrapperTH1(std::map<std::string, TFile*>& inputFiles, const std::string& inputFileName, const std::string& lutName, int lutType, 
			     double xMin, double xMax, double yMin, double yMax)
  : lutWrapperBase(inputFiles, inputFileName, lutName, lutType, xMin, xMax, yMin, yMax)
{
  lut_ = loadTH1(inputFile_, lutName_);
}

double lutWrapperTH1::getSF_private(double x, double y)
{
  double sf = 1.;
  if ( (y >= yMin_ || yMin_ == -1.) && (y < yMax_ || yMax_ == -1.) ) {
    if ( xMin_ != -1. && x < xMin_ ) x = xMin_;
    if ( xMax_ != -1. && x > xMax_ ) x = xMax_;
    sf = getSF_from_TH1(lut_, x);
  }
  return sf;
}
//-------------------------------------------------------------------------------


//-------------------------------------------------------------------------------
lutWrapperTH2::lutWrapperTH2(std::map<std::string, TFile*>& inputFiles, const std::string& inputFileName, const std::string& lutName, int lutType, 
			     double xMin, double xMax, double yMin, double yMax)
  : lutWrapperBase(inputFiles, inputFileName, lutName, lutType, xMin, xMax, yMin, yMax)
{
  lut_ = loadTH2(inputFile_, lutName_);
}

double lutWrapperTH2::getSF_private(double x, double y)
{
  if ( xMin_ != -1. && x < xMin_ ) x = xMin_;
  if ( xMax_ != -1. && x > xMax_ ) x = xMax_;
  if ( yMin_ != -1. && y < yMin_ ) y = yMin_;
  if ( yMax_ != -1. && y > yMax_ ) y = yMax_;
  double sf = getSF_from_TH2(lut_, x, y);
  return sf;
}
//-------------------------------------------------------------------------------


//-------------------------------------------------------------------------------
lutWrapperTH2Poly::lutWrapperTH2Poly(std::map<std::string, TFile*>& inputFiles, const std::string& inputFileName, const std::string& lutName, int lutType, 
				     double xMin, double xMax, double yMin, double yMax)
  : lutWrapperBase(inputFiles, inputFileName, lutName, lutType, xMin, xMax, yMin, yMax)
{
  lut_ = loadTH2(inputFile_, lutName_);
}

double lutWrapperTH2Poly::getSF_private(double x, double y)
{
  if ( xMin_ != -1. && x < xMin_ ) x = xMin_;
  if ( xMax_ != -1. && x > xMax_ ) x = xMax_;
  if ( yMin_ != -1. && y < yMin_ ) y = yMin_;
  if ( yMax_ != -1. && y > yMax_ ) y = yMax_;
  double sf = getSF_from_TH2Poly(lut_, x, y);
  return sf;
}
//-------------------------------------------------------------------------------


//-------------------------------------------------------------------------------
lutWrapperTGraph::lutWrapperTGraph(std::map<std::string, TFile*>& inputFiles, const std::string& inputFileName, const std::string& lutName, int lutType, 
				   double xMin, double xMax, double yMin, double yMax)
  : lutWrapperBase(inputFiles, inputFileName, lutName, lutType, xMin, xMax, yMin, yMax)
{
  lut_ = loadTGraph(inputFile_, lutName_);
}

double lutWrapperTGraph::getSF_private(double x, double y)
{
  double sf = 1.;
  if ( (y >= yMin_ || yMin_ == -1.) && (y < yMax_ || yMax_ == -1.) ) {
    if ( xMin_ != -1. && x < xMin_ ) x = xMin_;
    if ( xMax_ != -1. && x > xMax_ ) x = xMax_;
    sf = getSF_from_TGraph(lut_, x);
  }
  return sf;
}
//-------------------------------------------------------------------------------

//-------------------------------------------------------------------------------
lutWrapperData_to_MC::lutWrapperData_to_MC(lutWrapperBase* lutData, lutWrapperBase* lutMC)
  : lutData_(lutData)
  , lutMC_(lutMC)
{}

lutWrapperData_to_MC::~lutWrapperData_to_MC()
{
  delete lutData_;
  delete lutMC_;
}

double lutWrapperData_to_MC::getSF_private(double x, double y)
{
  double effData = lutData_->getSF(x, y);
  double effMC = lutMC_->getSF(x, y);
  double sf = ( effMC > 0. ) ? effData/effMC : 1.;
  if ( sf > 1.e+1 ) sf = 1.e+1;
  return sf;
}
//-------------------------------------------------------------------------------
