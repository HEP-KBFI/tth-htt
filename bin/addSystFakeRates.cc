
/** \executable addSystFakeRates
 *
 * Add shape systematics for "closure" of electron, muon, and tau_h fake-rates to the datacard:
 *   - CMS_ttHl_Clos_e_normUp/Down
 *   - CMS_ttHl_Clos_e_shapeUp/Down
 *   - CMS_ttHl_Clos_m_normUp/Down
 *   - CMS_ttHl_Clos_m_shapeUp/Down
 *   - CMS_ttHl_Clos_t_normUp/Down
 *   - CMS_ttHl_Clos_t_shapeUp/Down
 *
 * \author Christian Veelken, Tallinn
 *
 */

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/PythonParameterSet/interface/MakeParameterSets.h"

#include "FWCore/Utilities/interface/Exception.h"
#include "tthAnalysis/HiggsToTauTau/interface/LocalFileInPath.h"

#include "PhysicsTools/FWLite/interface/TFileService.h"
#include "DataFormats/FWLite/interface/InputSource.h"
#include "DataFormats/FWLite/interface/OutputFiles.h"

#include "tthAnalysis/HiggsToTauTau/interface/histogramAuxFunctions.h"
#include "tthAnalysis/HiggsToTauTau/interface/generalAuxFunctions.h"
#include "tthAnalysis/HiggsToTauTau/interface/fitAuxFunctions.h" // EigenVector_and_Value, compEigenVectors_and_Values, fitFunction_and_legendEntry, makeControlPlot_fit

#include <TFile.h>
#include <TH1.h>
#include <TBenchmark.h>
#include <TMath.h>
#include <TError.h> // gErrorAbortLevel, kError
#include "TList.h"
#include "TKey.h"
#include "TObject.h"
#include "TString.h"
#include "TF1.h"
#include "TFitResult.h"

#include <iostream>
#include <string>
#include <vector>
#include <assert.h>

typedef std::vector<std::string> vstring;

struct addSystType
{
  addSystType(const edm::ParameterSet& cfg)
  {
    name_ = cfg.getParameter<std::string>("name");
    edm::ParameterSet cfg_nominal = cfg.getParameter<edm::ParameterSet>("nominal");
    inputFileName_nominal_ = cfg_nominal.getParameter<std::string>("inputFileName");
    histogramName_nominal_ = cfg_nominal.getParameter<std::string>("histogramName");
    edm::ParameterSet cfg_mcClosure = cfg.getParameter<edm::ParameterSet>("nominal");
    inputFileName_mcClosure_ = cfg_mcClosure.getParameter<std::string>("inputFileName");
    histogramName_mcClosure_ = cfg_mcClosure.getParameter<std::string>("histogramName");
  }
  ~addSystType() {}
  void print(std::ostream& stream) const
  {
    stream << "<addSystType>:" << std::endl;
    stream << " name = " << name_ << std::endl;
    stream << " nominal: inputFileName = " << inputFileName_nominal_ << ", histogramName = " << histogramName_nominal_ << std::endl;
    stream << " mcClosure: inputFileName = " << inputFileName_mcClosure_ << ", histogramName = " << histogramName_mcClosure_ << std::endl;
  }
  std::string name_;
  std::string inputFileName_nominal_;
  std::string histogramName_nominal_;
  std::string inputFileName_mcClosure_;
  std::string histogramName_mcClosure_;
};

TFile* openInputFile(const std::string& inputFileName, std::map<std::string, TFile*>& inputFiles_syst)
{
  if ( inputFiles_syst.find(inputFileName) == inputFiles_syst.end() ) {
    inputFiles_syst[inputFileName] = new TFile(inputFileName.data());
  }
  return inputFiles_syst[inputFileName];
}

TH1* loadHistogram(TFile* inputFile, const std::string& histogramName)
{
  TH1* histogram = dynamic_cast<TH1*>(inputFile->Get(histogramName.data()));
  if ( !histogram ) 
    throw cms::Exception("addSystFakeRates") 
      << "Failed to load histogram = '" << histogramName << "' from file = '" << inputFile->GetName() << "' !!\n";
  if ( !histogram->GetSumw2N() ) histogram->Sumw2();
  return histogram;
}

TH1* copyHistogram(const TH1* histogram_input, const std::string& histogramName_output)
{
  TH1* histogram_output = 0;
  const TAxis* xAxis = histogram_input->GetXaxis();
  if ( xAxis->GetXbins() ) histogram_output = new TH1F(histogramName_output.data(), histogram_input->GetTitle(), xAxis->GetNbins(), xAxis->GetXbins()->GetArray());
  else histogram_output = new TH1F(histogramName_output.data(), histogram_input->GetTitle(), xAxis->GetNbins(), xAxis->GetXmin(), xAxis->GetXmax());
  int numBins = xAxis->GetNbins();
  for ( int idxBin = 0; idxBin <= (numBins + 1); ++idxBin ) {
    double binContent = histogram_input->GetBinContent(idxBin);
    histogram_output->SetBinContent(idxBin, binContent);
    double binError = histogram_input->GetBinError(idxBin);
    histogram_output->SetBinError(idxBin, binError);
  }
  return histogram_output;
}

TH1* cloneHistogram(const TH1* histogram, const std::string& histogramName_clone)
{
  TH1* histogram_clone = (TH1*)histogram->Clone(histogramName_clone.data());
  histogram_clone->Reset();
  if ( !histogram_clone->GetSumw2N() ) histogram_clone->Sumw2();
  return histogram_clone;
}

TGraphAsymmErrors* convert_to_TGraph(const TH1* histogram)
{
  const TAxis* xAxis = histogram->GetXaxis();
  int numPoints = xAxis->GetNbins();
  TGraphAsymmErrors* graph = new TGraphAsymmErrors(numPoints);
  for ( int idxPoint = 0; idxPoint < numPoints; ++idxPoint ) {
    int idxBin = idxPoint + 1;
    double x = xAxis->GetBinCenter(idxBin);
    double y = histogram->GetBinContent(idxBin);
    graph->SetPoint(idxPoint, x, y);
    double xErrUp = xAxis->GetBinUpEdge(idxBin) - x;
    double xErrDown = x - xAxis->GetBinLowEdge(idxBin);
    double yErrUp = histogram->GetBinError(idxBin);
    double yErrDown = yErrUp;
    graph->SetPointError(idxPoint, xErrDown, xErrUp, yErrDown, yErrUp);
  }
  return graph;
}

double square(double x)
{
  return x*x;
}

int main(int argc, char* argv[]) 
{
//--- throw an exception in case ROOT encounters an error
  gErrorAbortLevel = kError;

//--- parse command-line arguments
  if ( argc < 2 ) {
    std::cout << "Usage: " << argv[0] << " [parameters.py]" << std::endl;
    return EXIT_FAILURE;
  }

  std::cout << "<addSystFakeRates>:" << std::endl;

//--- keep track of time it takes the macro to execute
  TBenchmark clock;
  clock.Start("addSystFakeRates");

//--- read python configuration parameters
  if ( !edm::readPSetsFrom(argv[1])->existsAs<edm::ParameterSet>("process") ) 
    throw cms::Exception("addSystFakeRates") 
      << "No ParameterSet 'process' found in configuration file = " << argv[1] << " !!\n";
  
  edm::ParameterSet cfg = edm::readPSetsFrom(argv[1])->getParameter<edm::ParameterSet>("process");

  edm::ParameterSet cfg_addSystFakeRates = cfg.getParameter<edm::ParameterSet>("addSystFakeRates");
  
  std::string process = cfg_addSystFakeRates.getParameter<std::string>("process");

  std::string histogramToFit = cfg_addSystFakeRates.getParameter<std::string>("histogramToFit");
  std::string xAxisTitle = cfg_addSystFakeRates.getParameter<std::string>("xAxisTitle");
  std::string yAxisTitle = cfg_addSystFakeRates.getParameter<std::string>("yAxisTitle");

  std::vector<addSystType*> addSystConfigs;
  edm::VParameterSet cfg_addSystConfigs = cfg_addSystFakeRates.getParameter<edm::VParameterSet>("addSyst");
  for ( edm::VParameterSet::const_iterator cfgAddSystConfig = cfg_addSystConfigs.begin();
	cfgAddSystConfig != cfg_addSystConfigs.end(); ++cfgAddSystConfig ) {
    addSystConfigs.push_back(new addSystType(*cfgAddSystConfig));
  }

  std::string outputFileName = cfg_addSystFakeRates.getParameter<std::string>("outputFileName"); // for control plots

  fwlite::InputSource inputFiles(cfg); 
  if ( !(inputFiles.files().size() == 1) )
    throw cms::Exception("addSystFakeRates") 
      << "Exactly one input file expected !!\n";
  TFile* inputFile = new TFile(inputFiles.files().front().data());

  std::map<std::string, TFile*> inputFiles_syst; // key = inputFileName
 
  fwlite::OutputFiles outputFile(cfg);
  fwlite::TFileService fs = fwlite::TFileService(outputFile.file().data());
      
  // copy histograms that do not require modifications
  std::cout << "copying histograms that do not require modifications" << std::endl;
  TList* list1 = inputFile->GetListOfKeys();
  TIter next1(list1);
  TKey* key1 = 0;
  while ( (key1 = dynamic_cast<TKey*>(next1())) ) {
    TObject* object = key1->ReadObj();
    TH1* histogram_input = dynamic_cast<TH1*>(object);

    TFileDirectory* subdir_output = &fs;
    subdir_output->cd();
    
    copyHistogram(histogram_input, histogram_input->GetName());
  }

  // add histograms for "closure" uncertainties of electron, muon, and tau_h fake-rates
  for ( std::vector<addSystType*>::iterator addSystConfig = addSystConfigs.begin();
	addSystConfig != addSystConfigs.end(); ++addSystConfig ) {
    TFile* inputFile_nominal = openInputFile((*addSystConfig)->inputFileName_nominal_, inputFiles_syst);
    TH1* histogram_nominal = loadHistogram(inputFile_nominal, (*addSystConfig)->histogramName_nominal_);
    TGraphAsymmErrors* graph_nominal = convert_to_TGraph(histogram_nominal);
    
    TFile* inputFile_mcClosure = openInputFile((*addSystConfig)->inputFileName_mcClosure_, inputFiles_syst);
    TH1* histogram_mcClosure = loadHistogram(inputFile_mcClosure, (*addSystConfig)->histogramName_mcClosure_);
    TGraphAsymmErrors* graph_mcClosure = convert_to_TGraph(histogram_mcClosure);

    std::string histogramName_ratio = Form("%s_div_%s", histogram_nominal->GetName(), histogram_mcClosure->GetName());
    TH1* histogram_ratio = cloneHistogram(histogram_nominal, histogramName_ratio);
    histogram_ratio->Divide(histogram_nominal, histogram_mcClosure);
    TGraphAsymmErrors* graph_ratio = convert_to_TGraph(histogram_ratio);

    double xMin = histogram_nominal->GetXaxis()->GetXmin();
    double xMax = histogram_nominal->GetXaxis()->GetXmax();

    double yMax = 1.e+1*TMath::Max(histogram_nominal->GetMaximum(), histogram_mcClosure->GetMaximum());
    double yMin = 1.e-4*yMax;
    std::string outputFileName_graphs = std::string(outputFileName, 0, outputFileName.find_last_of('.'));
    outputFileName_graphs.append(Form("_%s_%s.png", histogramToFit.data(), (*addSystConfig)->name_.data()));
    makeControlPlot_graphs(
      graph_nominal, "nominal",
      graph_mcClosure, "mcClosure",
      graph_ratio, 
      xMin, xMax, xAxisTitle.data(), 
      true, yMin, yMax, yAxisTitle.data(), "#frac{nominal - mcClosure}{mcClosure}", 
      outputFileName_graphs);

    std::string fitFunctionName = Form("%s_fit", histogramName_ratio.data());
    double x0 = histogram_nominal->GetMean();
    std::string fitFunction_formula_wrt_x0 = Form("[0] + [1]*(x - %f)", x0);
    TF1* fitFunction = new TF1(fitFunctionName.data(), fitFunction_formula_wrt_x0.data(), xMin, xMax);
    fitFunction->SetParameter(0, 1.);
    fitFunction->SetParameter(1, 0.);
	
    TFitResultPtr fitResult = graph_ratio->Fit(fitFunction, "ERNS");
    std::vector<fitFunction_and_legendEntry> fitFunctions_sysShifts;
    if ( fitResult->IsValid() ) {
      TMatrixD cov = fitResult->GetCovarianceMatrix();
      std::vector<EigenVector_and_Value> eigenVectors_and_Values = compEigenVectors_and_Values(cov);
      size_t dimension = fitFunction->GetNpar();
      assert(eigenVectors_and_Values.size() == dimension);
      int idxPar = 1;
      for ( std::vector<EigenVector_and_Value>::const_iterator eigenVector_and_Value = eigenVectors_and_Values.begin();
	    eigenVector_and_Value != eigenVectors_and_Values.end(); ++eigenVector_and_Value ) {
	assert(eigenVector_and_Value->eigenVector_.GetNrows() == (int)dimension);
	std::cout << "EigenVector #" << idxPar << ":" << std::endl;
	eigenVector_and_Value->eigenVector_.Print();
	std::cout << "EigenValue #" << idxPar << " = " << eigenVector_and_Value->eigenValue_ << std::endl;
	assert(eigenVector_and_Value->eigenValue_ >= 0.);
	std::string fitFunctionParUpName = Form("%s_par%iUp", fitFunctionName.data(), idxPar);
	TF1* fitFunctionParUp = new TF1(fitFunctionParUpName.data(), fitFunction_formula_wrt_x0.data(), xMin, xMax);
	for ( size_t idxComponent = 0; idxComponent < dimension; ++idxComponent ) {    
	  fitFunctionParUp->SetParameter(
	    idxComponent, 
	    fitFunction->GetParameter(idxComponent) + TMath::Sqrt(eigenVector_and_Value->eigenValue_)*eigenVector_and_Value->eigenVector_(idxComponent));
	}
	fitFunctions_sysShifts.push_back(fitFunction_and_legendEntry(fitFunctionParUp, Form("EigenVec #%i", idxPar)));
	std::string fitFunctionParDownName = Form("%s_par%iDown", fitFunctionName.data(), idxPar);
	TF1* fitFunctionParDown = new TF1(fitFunctionParDownName.data(), fitFunction_formula_wrt_x0.data(), xMin, xMax);
	for ( size_t idxComponent = 0; idxComponent < dimension; ++idxComponent ) {    
	  fitFunctionParDown->SetParameter(
	    idxComponent, 
	    fitFunction->GetParameter(idxComponent) - TMath::Sqrt(eigenVector_and_Value->eigenValue_)*eigenVector_and_Value->eigenVector_(idxComponent));
	}
	fitFunctions_sysShifts.push_back(fitFunction_and_legendEntry(fitFunctionParDown, Form("EigenVec #%i", idxPar)));
	++idxPar;
      }    
    } else {
      throw cms::Exception("addSystFakeRates") 
	<< "Fit failed to converge !!\n";
    }
    
    std::string outputFileName_fit = std::string(outputFileName, 0, outputFileName.find_last_of('.'));
    outputFileName_fit.append(Form("_%s_%s_fit.png", histogramToFit.data(), (*addSystConfig)->name_.data()));
    makeControlPlot_fit(
      graph_ratio, 
      fitFunction, fitFunctions_sysShifts, 
      xMin, xMax, xAxisTitle, 
      false, 0., 2., "nominal/mcClosure", 
      outputFileName_fit);

    // convert results of fit to histogram format and write histograms to output file
    TFileDirectory* subdir_output = &fs;
    subdir_output->cd();

    std::string histogramName_closureNormUp = Form("%s_%sUp", histogramToFit.data(), (*addSystConfig)->name_.data());
    TH1* histogram_closureNormUp = cloneHistogram(histogram_nominal, histogramName_closureNormUp);
    std::string histogramName_closureNormDown = Form("%s_%sDown", histogramToFit.data(), (*addSystConfig)->name_.data());
    TH1* histogram_closureNormDown = cloneHistogram(histogram_nominal, histogramName_closureNormDown);
    std::string histogramName_closureShapeUp = Form("%s_%sUp", histogramToFit.data(), (*addSystConfig)->name_.data());
    TH1* histogram_closureShapeUp = cloneHistogram(histogram_nominal, histogramName_closureShapeUp);
    std::string histogramName_closureShapeDown = Form("%s_%sDown", histogramToFit.data(), (*addSystConfig)->name_.data());
    TH1* histogram_closureShapeDown = cloneHistogram(histogram_nominal, histogramName_closureShapeDown);
    for ( int idxBin = 1; idxBin <= histogram_nominal->GetNbinsX(); ++idxBin ) {
      double binContent_nominal = histogram_nominal->GetBinContent(idxBin);
      double binError_nominal = histogram_nominal->GetBinError(idxBin);
      double norm = fitFunction->GetParameter(0);
      double normErr = fitFunction->GetParError(0);
      double dy_closureNorm;
      if ( norm > 1. ) dy_closureNorm = (norm + normErr) - 1.;
      else dy_closureNorm = 1. - (norm - normErr);      
      histogram_closureNormUp->SetBinContent(idxBin, binContent_nominal + dy_closureNorm);
      histogram_closureNormUp->SetBinError(idxBin, binError_nominal);
      histogram_closureNormDown->SetBinContent(idxBin, binContent_nominal - dy_closureNorm);
      histogram_closureNormDown->SetBinError(idxBin, binError_nominal);
      double slope = fitFunction->GetParameter(1);
      double slopeErr = fitFunction->GetParError(1);
      double x = histogram_nominal->GetXaxis()->GetBinCenter(idxBin);
      double dy_closureShape;
      if ( slope > 0. ) dy_closureShape = (x - x0)*(slope + slopeErr);
      else dy_closureShape = (x - x0)*(slope - slopeErr);
      histogram_closureShapeUp->SetBinContent(idxBin, binContent_nominal + dy_closureShape);
      histogram_closureShapeUp->SetBinError(idxBin, binError_nominal);
      histogram_closureShapeDown->SetBinContent(idxBin, binContent_nominal - dy_closureShape);
      histogram_closureShapeDown->SetBinError(idxBin, binError_nominal);
    }
    histogram_closureNormUp->Write();
    histogram_closureNormDown->Write();
    histogram_closureShapeUp->Write();
    histogram_closureShapeDown->Write();
    
    // delete temporary objects
    delete histogram_ratio;
    delete fitFunction;
  }
  
  clock.Show("addSystFakeRates");
  
  return 0;
}
