
/** \executable comp_jetToTauFakeRate
 *
 * Determine probability for jets to get misidentified as hadronic tau candidates,
 * measured in tt+jets events selected by requiring the presence of two b-jets, plus an electron and muon pair of opposite charge.
 *
 * \author Christian Veelken, Tallinn
 *
 */

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/PythonParameterSet/interface/MakeParameterSets.h"

#include "FWCore/Utilities/interface/Exception.h"

#include "PhysicsTools/FWLite/interface/TFileService.h"
#include "DataFormats/FWLite/interface/InputSource.h"
#include "DataFormats/FWLite/interface/OutputFiles.h"

#include "tthAnalysis/HiggsToTauTau/interface/histogramAuxFunctions.h"
#include "tthAnalysis/HiggsToTauTau/interface/jetToTauFakeRateAuxFunctions.h"
#include "tthAnalysis/HiggsToTauTau/interface/compFakeRateAuxFunctions.h" // compFakeRate
#include "tthAnalysis/HiggsToTauTau/interface/graphAuxFunctions.h" // compRatioGraph
#include "tthAnalysis/HiggsToTauTau/interface/fitAuxFunctions.h" // EigenVector_and_Value, compEigenVectors_and_Values, fitFunction_and_legendEntry, makeControlPlot_fit

#include <TFile.h>
#include <TH1.h>
#include <TBenchmark.h>
#include <TMath.h>
#include <TGraphAsymmErrors.h>
#include <TGraphErrors.h>
#include <TF1.h>
#include <TVectorD.h>
#include <TMatrixD.h>
#include <TArrayD.h>
#include <TFitResult.h>
#include <TString.h>
#include <TCanvas.h>
#include <TPad.h>
#include <TLegend.h>
#include <TError.h> // gErrorAbortLevel, kError

#include <iostream>
#include <string>
#include <vector>
#include <assert.h>

typedef std::vector<std::string> vstring;
typedef std::vector<double> vdouble;
typedef std::vector<int> vint;

double square(double x)
{
  return x*x;
} 

void compIntegral_and_Error(const TH1* histogram, double& integral, double& integralErr)
{
  integral = 0.;
  double integralErr2 = 0.;
  int numBins = histogram->GetNbinsX();
  for ( int iBin = 1; iBin <= numBins; ++iBin ) {
    double binContent = histogram->GetBinContent(iBin);
    double binError = histogram->GetBinError(iBin);
    integral += binContent;
    integralErr2 += square(binError);
  }
  assert(integralErr2 >= 0.);
  integralErr = TMath::Sqrt(integralErr2);
}

std::pair<TH1*, TH1*> getHistogramsLoose_and_Tight(
  TDirectory* inputDir_loose, const std::string& looseRegion, TDirectory* inputDir_tight, const std::string& tightRegion, 
  const std::string& processData_or_mc, const vstring& processesToSubtract, 
  const std::string& etaBin, int decayMode, const std::string& hadTauSelection, const std::string& histogramToFit)
{
  std::cout << "<getHistogramsPass_and_Fail>:" << std::endl;
  std::cout << " inputDir_loose = " << inputDir_loose << ": name = " << inputDir_loose->GetName() << std::endl;
  std::cout << " looseRegion = " << looseRegion << std::endl;
  std::cout << " inputDir_tight = " << inputDir_tight << ": name = " << inputDir_tight->GetName() << std::endl;
  std::cout << " tightRegion = " << tightRegion << std::endl;
  std::cout << " etaBin = " << etaBin << std::endl;
  std::cout << " hadTauSelection = " << hadTauSelection << std::endl;
  std::cout << " histogramToFit = " << histogramToFit << std::endl;

  std::string etaBin_and_decayMode = etaBin;
  if ( decayMode != -1 ) etaBin_and_decayMode.append(Form("_dm%i", decayMode));
  
  std::string histogramName, subdirName_loose, subdirName_tight;
  size_t idx = histogramToFit.find_last_of('/');
  if ( idx != std::string::npos ) {
    histogramName = std::string(histogramToFit, idx + 1, std::string::npos);
    subdirName_loose = Form("%s/%s", etaBin_and_decayMode.data(), std::string(histogramToFit, 0, idx).data());
    subdirName_tight = Form("%s/%s/%s", hadTauSelection.data(), etaBin_and_decayMode.data(), std::string(histogramToFit, 0, idx).data());
  } else {
    histogramName = histogramToFit;
    subdirName_loose = Form("%s", etaBin_and_decayMode.data());
    subdirName_tight = Form("%s/%s", hadTauSelection.data(), etaBin_and_decayMode.data());
  }
  TDirectory* inputSubdir_loose = getSubdirectory(inputDir_loose, subdirName_loose, true);
  TDirectory* inputSubdir_tight = getSubdirectory(inputDir_tight, subdirName_tight, true);

  TH1* histogramData_or_mc_loose = getHistogram(inputSubdir_loose, processData_or_mc, histogramName, "central", true);
  assert(histogramData_or_mc_loose);
  std::cout << "histogramData_or_mc_loose = " << histogramData_or_mc_loose << ":" << std::endl;
  dumpHistogram(histogramData_or_mc_loose);
  TH1* histogramData_or_mc_tight = getHistogram(inputSubdir_tight, processData_or_mc, histogramName, "central", true);
  assert(histogramData_or_mc_tight);
  std::cout << "histogramData_or_mc_tight = " << histogramData_or_mc_tight << ":" << std::endl;
  dumpHistogram(histogramData_or_mc_tight);
  checkCompatibleBinning(histogramData_or_mc_loose, histogramData_or_mc_tight);

  std::vector<TH1*> histogramsToSubtract_loose;
  std::vector<TH1*> histogramsToSubtract_tight;
  for ( vstring::const_iterator processToSubtract = processesToSubtract.begin();
	processToSubtract != processesToSubtract.end(); ++processToSubtract ) {
    TH1* histogramToSubtract_loose = getHistogram(inputSubdir_loose, *processToSubtract, histogramName, "central", true);
    std::cout << " histogramToSubtract_loose (process = " << (*processToSubtract) << ") = " << histogramToSubtract_loose << ":" 
	      << " name = " << histogramToSubtract_loose->GetName() << ", integral = " << histogramToSubtract_loose->Integral() << std::endl;
    dumpHistogram(histogramToSubtract_loose);
    histogramsToSubtract_loose.push_back(histogramToSubtract_loose);
    TH1* histogramToSubtract_tight = getHistogram(inputSubdir_tight, *processToSubtract, histogramName, "central", true);
    std::cout << " histogramToSubtract_tight (process = " << (*processToSubtract) << ") = " << histogramToSubtract_tight << ":" 
	      << " name = " << histogramToSubtract_tight->GetName() << ", integral = " << histogramToSubtract_tight->Integral() << std::endl;
    dumpHistogram(histogramToSubtract_tight);
    histogramsToSubtract_tight.push_back(histogramToSubtract_tight);
  }
      
  std::cout << "computing sum(histograms) in loose region" << std::endl;
  std::string histogramNameJetToTauFakeRate_loose = Form("jetToTauFakeRate_%s_%s_%s_%s_loose", 
    processData_or_mc.data(), hadTauSelection.data(), etaBin_and_decayMode.data(), histogramName.data());
  TH1* histogramJetToTauFakeRate_loose = subtractHistograms(histogramNameJetToTauFakeRate_loose.data(), histogramData_or_mc_loose, histogramsToSubtract_loose);  
  std::cout << "computing sum(histograms) in tight region" << std::endl;
  std::string histogramNameJetToTauFakeRate_tight = Form("jetToTauFakeRate_%s_%s_%s_%s_tight", 
    processData_or_mc.data(), hadTauSelection.data(), etaBin_and_decayMode.data(), histogramName.data());
  TH1* histogramJetToTauFakeRate_tight = subtractHistograms(histogramNameJetToTauFakeRate_tight.data(), histogramData_or_mc_tight, histogramsToSubtract_tight);  

  return std::pair<TH1*, TH1*>(histogramJetToTauFakeRate_loose, histogramJetToTauFakeRate_tight);
}

TGraphAsymmErrors* getGraph_jetToTauFakeRate(TH1* histogram_loose, TH1* histogram_tight, const std::string& graphName_jetToTauFakeRate)
{
  std::cout << "<getGraph_jetToTauFakeRate>:" << std::endl;
  assert(histogram_loose->GetNbinsX() == histogram_tight->GetNbinsX());
  int numBins = histogram_loose->GetNbinsX();
  std::vector<double> points_x;
  std::vector<double> points_xErrUp;
  std::vector<double> points_xErrDown;
  std::vector<double> points_y;
  std::vector<double> points_yErrUp;
  std::vector<double> points_yErrDown;
  for ( int idxBin = 1; idxBin <= numBins; ++idxBin ) {
    double nLoose = histogram_loose->GetBinContent(idxBin);
    double nLooseErr = histogram_loose->GetBinError(idxBin);
    double nTight = histogram_tight->GetBinContent(idxBin);
    double nTightErr = histogram_tight->GetBinError(idxBin);     
    
    double nPass = nTight;
    double nPassErr = nTightErr;
    double nFail = nLoose - nTight;
    double nFailErr = TMath::Sqrt(TMath::Max(0., square(nLooseErr) - square(nTightErr)));
    
    double jetToTauFakeRate, jetToTauFakeRateErrUp, jetToTauFakeRateErrDown;
    bool errorFlag;
    std::cout << "bin #" << idxBin << " (x = " << histogram_loose->GetBinCenter(idxBin) << ")" << ":";	  
    compFakeRate(nPass, nPassErr, nFail, nFailErr, jetToTauFakeRate, jetToTauFakeRateErrUp, jetToTauFakeRateErrDown, errorFlag);
    if ( errorFlag ) {
      std::cerr << "Warning: Cannot compute fake rate for nPass = " << nPass << " +/- " << nPassErr << ", nFail = " << nFail << " +/- " << nFailErr 
		<< " --> setting jetToTauFakeRate = " << jetToTauFakeRate << " + " << jetToTauFakeRateErrUp << " - " << jetToTauFakeRateErrDown << " !!" << std::endl;
    }
    double binCenter_loose = histogram_loose->GetBinCenter(idxBin);
    double binCenter_tight = histogram_tight->GetBinCenter(idxBin);
    assert(TMath::Abs(binCenter_loose - binCenter_tight) < 1.e-3*TMath::Abs(binCenter_loose + binCenter_tight));
    TAxis* xAxis = histogram_loose->GetXaxis();
    double x = xAxis->GetBinCenter(idxBin);
    points_x.push_back(x);
    double y = jetToTauFakeRate;
    points_y.push_back(y);
    double xErrUp = xAxis->GetBinUpEdge(idxBin) - xAxis->GetBinCenter(idxBin);
    points_xErrUp.push_back(xErrUp);
    double xErrDown = xAxis->GetBinCenter(idxBin) - xAxis->GetBinLowEdge(idxBin);
    points_xErrDown.push_back(xErrDown);
    double yErrUp = jetToTauFakeRateErrUp;
    points_yErrUp.push_back(yErrUp);
    double yErrDown = jetToTauFakeRateErrDown;
    points_yErrDown.push_back(yErrDown);
  }
  int numPoints = points_x.size();
  TGraphAsymmErrors* graph_jetToTauFakeRate = new TGraphAsymmErrors(numPoints);
  for ( int idxPoint = 0; idxPoint < numPoints; ++idxPoint ) {
    graph_jetToTauFakeRate->SetPoint(idxPoint, points_x[idxPoint], points_y[idxPoint]);
    graph_jetToTauFakeRate->SetPointError(idxPoint, points_xErrDown[idxPoint], points_xErrUp[idxPoint], points_yErrDown[idxPoint], points_yErrUp[idxPoint]);
  }
  graph_jetToTauFakeRate->SetName(graphName_jetToTauFakeRate.data());
  return graph_jetToTauFakeRate;
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

  std::cout << "<comp_jetToTauFakeRate>:" << std::endl;

//--- keep track of time it takes the macro to execute
  TBenchmark clock;
  clock.Start("comp_jetToTauFakeRate");

//--- read python configuration parameters
  if ( !edm::readPSetsFrom(argv[1])->existsAs<edm::ParameterSet>("process") ) 
    throw cms::Exception("comp_jetToTauFakeRate") 
      << "No ParameterSet 'process' found in configuration file = " << argv[1] << " !!\n";

  edm::ParameterSet cfg = edm::readPSetsFrom(argv[1])->getParameter<edm::ParameterSet>("process");

  edm::ParameterSet cfg_comp = cfg.getParameter<edm::ParameterSet>("comp_jetToTauFakeRate");
  
  std::string looseRegion = cfg_comp.getParameter<std::string>("looseRegion");
  std::string tightRegion = cfg_comp.getParameter<std::string>("tightRegion");

  std::string processData = cfg_comp.getParameter<std::string>("processData");
  vstring processesToSubtract = cfg_comp.getParameter<vstring>("processesToSubtract");

  std::string processMC = cfg_comp.getParameter<std::string>("processMC");

  vstring hadTauSelections = cfg_comp.getParameter<vstring>("hadTauSelections");

  vdouble absEtaBins = cfg_comp.getParameter<vdouble>("absEtaBins");
  if ( absEtaBins.size() < 2 ) throw cms::Exception("comp_jetToTauFakeRate") 
    << "Invalid Configuration parameter 'absEtaBins' !!\n";  
  vdouble ptBins = cfg_comp.getParameter<vdouble>("ptBins");
  TArrayD ptBins_array = convertToTArrayD(ptBins);
  vint decayModes = cfg_comp.getParameter<vint>("decayModes");
  if ( decayModes.size() < 1 ) throw cms::Exception("comp_jetToTauFakeRate") 
    << "Invalid Configuration parameter 'decayModes' !!\n";
  
  vstring histogramsToFit = cfg_comp.getParameter<vstring>("histogramsToFit");

  std::string fitFunction_formula = cfg_comp.getParameter<std::string>("fitFunction");
  std::cout << "fitFunction_formula = " << fitFunction_formula << std::endl;
  std::map<std::string, double> initialParameters; // key = fitParameterName
  if ( cfg_comp.exists("initialParameters") ) {
    edm::ParameterSet cfgInitialParameters = cfg_comp.getParameter<edm::ParameterSet>("initialParameters");
    vstring fitParameterNames = cfgInitialParameters.getParameterNamesForType<double>();
    for ( vstring::const_iterator fitParameterName = fitParameterNames.begin();
	  fitParameterName != fitParameterNames.end(); ++fitParameterName ) {
      double initialParameter_value = cfgInitialParameters.getParameter<double>(*fitParameterName);
      initialParameters[*fitParameterName] = initialParameter_value;
    }
  }
  double xMin = cfg_comp.getParameter<double>("xMin");
  double xMax = cfg_comp.getParameter<double>("xMax");
  std::cout << "xMin = " << xMin << ", xMax = " << xMax << std::endl;

  std::string outputFileName = cfg_comp.getParameter<std::string>("outputFileName"); // for control plots

  fwlite::InputSource inputFiles(cfg); 
  if ( !(inputFiles.files().size() == 1) )
    throw cms::Exception("comp_jetToTauFakeRate") 
      << "Exactly one input file expected !!\n";
  TFile* inputFile = new TFile(inputFiles.files().front().data());
  if ( !inputFile ) throw cms::Exception("comp_jetToTauFakeRate") 
    << "Failed to open input file = '" << inputFiles.files().front() << "' !!\n";
   
  fwlite::OutputFiles outputFile(cfg);
  fwlite::TFileService fs = fwlite::TFileService(outputFile.file().data());

  TDirectory* inputDir_loose = getDirectory(inputFile, looseRegion, true);
  assert(inputDir_loose);
  std::cout << "inputDir_loose = " << inputDir_loose << ": name = " << inputDir_loose->GetName() << std::endl;
  TDirectory* inputDir_tight = getDirectory(inputFile, tightRegion, true);
  assert(inputDir_tight);
  std::cout << "inputDir_tight = " << inputDir_tight << ": name = " << inputDir_tight->GetName() << std::endl;

  for ( vstring::const_iterator hadTauSelection = hadTauSelections.begin();
	hadTauSelection != hadTauSelections.end(); ++hadTauSelection ) {
    std::cout << "processing hadTauSelection = " << (*hadTauSelection) << std::endl;
    
    for ( vstring::const_iterator histogramToFit = histogramsToFit.begin();
	  histogramToFit != histogramsToFit.end(); ++histogramToFit ) {
      std::cout << "fitting " << (*histogramToFit) << ":" << std::endl;
      
      int numEtaBins = absEtaBins.size() - 1;
      for ( int idxEtaBin = 0; idxEtaBin < numEtaBins; ++idxEtaBin ) {
        double minAbsEta = absEtaBins[idxEtaBin];
        double maxAbsEta = absEtaBins[idxEtaBin + 1];
        std::string etaBin = getEtaBin(minAbsEta, maxAbsEta);
        for ( vint::const_iterator decayMode = decayModes.begin();
	      decayMode != decayModes.end(); ++decayMode ) {
	  std::string etaBin_and_decayMode = etaBin;
	  if ( (*decayMode) != -1 ) etaBin_and_decayMode.append(Form("_dm%i", *decayMode));

   	  std::string outputDirName = Form("jetToTauFakeRate/%s/%s", hadTauSelection->data(), etaBin_and_decayMode.data());
	  TDirectory* outputDir = createSubdirectory_recursively(fs, outputDirName.data());
	  outputDir->cd();

          std::pair<TH1*, TH1*> histogram_data_loose_and_tight = getHistogramsLoose_and_Tight(
            inputDir_loose, looseRegion, inputDir_tight, tightRegion, 
            processData, processesToSubtract, 
	    etaBin, *decayMode, *hadTauSelection, *histogramToFit);
  	  TH1* histogram_data_loose = histogram_data_loose_and_tight.first;
	  std::cout << "histogram_data_loose:" << std::endl;
   	  dumpHistogram(histogram_data_loose);
	  TH1* histogram_data_loose_rebinned = getRebinnedHistogram1d(histogram_data_loose, ptBins_array.GetSize() - 1, ptBins_array);
	  std::cout << "histogram_data_loose_rebinned:" << std::endl;
	  dumpHistogram(histogram_data_loose_rebinned);
	  TH1* histogram_data_tight = histogram_data_loose_and_tight.second;
	  std::cout << "histogram_data_tight:" << std::endl;
	  dumpHistogram(histogram_data_tight);
	  TH1* histogram_data_tight_rebinned = getRebinnedHistogram1d(histogram_data_tight, ptBins_array.GetSize() - 1, ptBins_array);
	  std::cout << "histogram_data_tight_rebinned:" << std::endl;
	  dumpHistogram(histogram_data_tight_rebinned);
	  std::string graphName_data_jetToTauFakeRate = Form("jetToTauFakeRate_data_%s", TString(histogramToFit->data()).ReplaceAll("/", "_").Data());
	  TGraphAsymmErrors* graph_data_jetToTauFakeRate = getGraph_jetToTauFakeRate(histogram_data_loose_rebinned, histogram_data_tight_rebinned, graphName_data_jetToTauFakeRate);

	  std::pair<TH1*, TH1*> histogram_mc_loose_and_tight = getHistogramsLoose_and_Tight(
            inputDir_loose, looseRegion, inputDir_tight, tightRegion, 
            processMC, {}, 
	    etaBin, *decayMode, *hadTauSelection, *histogramToFit);
	  TH1* histogram_mc_loose = histogram_mc_loose_and_tight.first;
	  std::cout << "histogram_mc_loose:" << std::endl;
	  dumpHistogram(histogram_mc_loose);
	  TH1* histogram_mc_loose_rebinned = getRebinnedHistogram1d(histogram_mc_loose, ptBins_array.GetSize() - 1, ptBins_array);
	  std::cout << "histogram_mc_loose_rebinned:" << std::endl;
	  dumpHistogram(histogram_mc_loose_rebinned);
	  TH1* histogram_mc_tight = histogram_mc_loose_and_tight.second;
	  std::cout << "histogram_mc_tight:" << std::endl;
	  dumpHistogram(histogram_mc_tight);
	  TH1* histogram_mc_tight_rebinned = getRebinnedHistogram1d(histogram_mc_tight, ptBins_array.GetSize() - 1, ptBins_array);
	  std::cout << "histogram_mc_tight_rebinned:" << std::endl;
	  dumpHistogram(histogram_mc_tight_rebinned);
	  std::string graphName_mc_jetToTauFakeRate = Form("jetToTauFakeRate_mc_%s", TString(histogramToFit->data()).ReplaceAll("/", "_").Data());
	  TGraphAsymmErrors* graph_mc_jetToTauFakeRate = getGraph_jetToTauFakeRate(histogram_mc_loose_rebinned, histogram_mc_tight_rebinned, graphName_mc_jetToTauFakeRate);

	  if ( !(graph_mc_jetToTauFakeRate->GetN() == graph_data_jetToTauFakeRate->GetN()) ) {
	    std::cout << "MC: graph = " << graph_mc_jetToTauFakeRate->GetName() << ", #points = " << graph_mc_jetToTauFakeRate->GetN() << std::endl;
	    std::cout << "Data: graph = " << graph_data_jetToTauFakeRate->GetName() << ", #points = " << graph_data_jetToTauFakeRate->GetN() << std::endl;
	    throw cms::Exception("comp_jetToTauFakeRate")
	      << "Graphs for MC and data do not have same number of points !!\n";
	  }

	  graph_data_jetToTauFakeRate->Write();
	  graph_mc_jetToTauFakeRate->Write();
	
  	  std::string graphName_data_div_mc_jetToTauFakeRate = Form("jetToTauFakeRate_data_div_mc_%s", TString(histogramToFit->data()).ReplaceAll("/", "_").Data());
	  TGraphAsymmErrors* graph_data_div_mc_jetToTauFakeRate = compRatioGraph(graphName_data_div_mc_jetToTauFakeRate, graph_data_jetToTauFakeRate, graph_mc_jetToTauFakeRate);

	  graph_data_div_mc_jetToTauFakeRate->Write();

	  std::string outputFileName_graphs = std::string(outputFileName, 0, outputFileName.find_last_of('.'));
	  outputFileName_graphs.append(TString(Form("_%s_%s_%s.png", hadTauSelection->data(), etaBin_and_decayMode.data(), histogramToFit->data())).ReplaceAll("/", "_").Data());
  	  makeControlPlot_graphs(
            graph_data_jetToTauFakeRate, "Data",
	    graph_mc_jetToTauFakeRate, "MC",
  	    graph_data_div_mc_jetToTauFakeRate, 
	    xMin, xMax, "p_{T} [GeV]", true, 1.e-2, 4.9e0, "f_{#tau}", -1.50, +1.50, "#frac{f_{#tau}^{data} - f_{#tau}^{mc}}{f_{#tau}^{mc}}", 
	    outputFileName_graphs);

	  std::string fitFunctionName = Form("fitFunction_data_div_mc_%s", TString(histogramToFit->data()).ReplaceAll("/", "_").Data());
	  double x0 = 0.5*(histogram_data_loose->GetMean() + histogram_mc_loose->GetMean());
	  std::string fitFunction_formula_wrt_x0 = TString(fitFunction_formula.data()).ReplaceAll("x", Form("(x - %f)", x0)).Data();
	  std::cout << "fitFunction = " << fitFunction_formula_wrt_x0 << std::endl;
	  TF1* fitFunction = new TF1(fitFunctionName.data(), fitFunction_formula_wrt_x0.data(), xMin, xMax);
	  int numFitParameter = fitFunction->GetNpar();
	  for ( int idxFitParameter = 0; idxFitParameter < numFitParameter; ++idxFitParameter ) {
	    std::string fitParameterName = Form("p%i", idxFitParameter);
	    if ( initialParameters.find(fitParameterName) != initialParameters.end() ) {
	      double initialParameter_value = initialParameters[fitParameterName];
	      std::cout << "initializing fitParameter #" << idxFitParameter << " = " << initialParameter_value << std::endl;
	      fitFunction->SetParameter(idxFitParameter, initialParameter_value);
	    }
	  }
	
	  TFitResultPtr fitResult = graph_data_div_mc_jetToTauFakeRate->Fit(fitFunction, "ERNS");
	  std::vector<fitFunction_and_legendEntry> fitFunctions_sysShifts;
	  if ( fitResult->IsValid() ) {
	    fitFunction->Write();
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
	      fitFunctionParUp->Write();
	      std::string fitFunctionParDownName = Form("%s_par%iDown", fitFunctionName.data(), idxPar);
	      TF1* fitFunctionParDown = new TF1(fitFunctionParDownName.data(), fitFunction_formula_wrt_x0.data(), xMin, xMax);
	      for ( size_t idxComponent = 0; idxComponent < dimension; ++idxComponent ) {    
		fitFunctionParDown->SetParameter(
		  idxComponent, 
		  fitFunction->GetParameter(idxComponent) - TMath::Sqrt(eigenVector_and_Value->eigenValue_)*eigenVector_and_Value->eigenVector_(idxComponent));
	      }
	      fitFunctions_sysShifts.push_back(fitFunction_and_legendEntry(fitFunctionParDown, Form("EigenVec #%i", idxPar)));
	      fitFunctionParDown->Write();
	      ++idxPar;
	    }    
	  } else {
	    std::cerr << "Warning: Fit failed to converge --> setting fitFunction to constant value !!" << std::endl;
	    delete fitFunction;
	    fitFunction = new TF1(fitFunctionName.data(), "1.0", xMin, xMax);
	    fitFunction->Write();
	  }

  	  std::string outputFileName_fit = std::string(outputFileName, 0, outputFileName.find_last_of('.'));
	  outputFileName_fit.append(TString(Form("_%s_%s_%s_fit.png", hadTauSelection->data(), etaBin_and_decayMode.data(), histogramToFit->data())).ReplaceAll("/", "_").Data());
	  makeControlPlot_fit(
            graph_data_div_mc_jetToTauFakeRate, 
	    fitFunction, fitFunctions_sysShifts, xMin, xMax, "p_{T} [GeV]", false, 0., 2., "#frac{f_{#tau}^{data}}{f_{#tau}^{mc}}", 
	    outputFileName_fit);
	}
      }
    }
  }

  delete inputFile;

  clock.Show("comp_jetToTauFakeRate");

  return 0;
}
