
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

#include <TFile.h>
#include <TH1.h>
#include <TBenchmark.h>
#include <TMath.h>
#include <TGraphAsymmErrors.h>
#include <TF1.h>
#include <TVectorD.h>
#include <TMatrixD.h>
#include <TFitResult.h>
#include <TString.h>
#include <TCanvas.h>
#include <TPad.h>
#include <TLegend.h>
#include <TRandom3.h>

#include <iostream>
#include <string>
#include <vector>
#include <assert.h>

typedef std::vector<std::string> vstring;
typedef std::vector<double> vdouble;

std::string getEtaBin(double minAbsEta, double maxAbsEta)
{
  std::string absEtaBin = "";
  if      ( minAbsEta > 0. && maxAbsEta > 0. ) absEtaBin.append(Form("absEta%1.0fto%1.0f", minAbsEta, maxAbsEta));
  else if ( minAbsEta > 0.                   ) absEtaBin.append(Form("absEtaGt%1.0f", minAbsEta));
  else if (                   maxAbsEta > 0. ) absEtaBin.append(Form("absEtaLt%1.0f", maxAbsEta));
  return absEtaBin;
}

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

struct EigenVector_and_Value
{
  EigenVector_and_Value(const TVectorD& eigenVector, double eigenValue)
    : eigenVector_(eigenVector),
      eigenValue_(eigenValue)
  {}
  ~EigenVector_and_Value() {}  
  TVectorD eigenVector_;
  double eigenValue_;
};

std::vector<EigenVector_and_Value> compEigenVectors_and_Values(const TMatrixD& cov)
{
  std::cout << "<compEigenVectors_and_Values>:" << std::endl;
  std::cout << " cov:" << std::endl;
  cov.Print();
  if ( cov.GetNcols() != cov.GetNrows() ) 
    throw cms::Exception("compEigenVectors_and_Values") 
      << "Matrix given as function argument is not symmetric !!\n";
  int dimension = cov.GetNrows();
  TVectorD eigenValues(dimension);
  TMatrixD eigenVectors = cov.EigenVectors(eigenValues);
  assert(eigenVectors.GetNrows() == dimension);
  assert(eigenVectors.GetNcols() == dimension);
  std::vector<EigenVector_and_Value> eigenVectors_and_Values;
  for ( int iEigenVector = 0; iEigenVector < dimension; ++iEigenVector ) {    
    TVectorD eigenVector(dimension);
    for ( int iComponent = 0; iComponent < dimension; ++iComponent ) {    
      eigenVector(iComponent) = eigenVectors(iComponent, iEigenVector);
    }
    double eigenValue = eigenValues(iEigenVector);
    TVectorD vec1 = cov*eigenVector;
    std::cout << "vec1:" << std::endl;
    vec1.Print();
    TVectorD vec2 = eigenValue*eigenVector;
    std::cout << "vec2:" << std::endl;
    vec2.Print();
    // CV: check that EigenVector is indeed an EigenVector,
    //     i.e. that we interpreted the ordering of columns and rows of the eigenVectors matrix correctly
    for ( int iComponent = 0; iComponent < dimension; ++iComponent ) {   
      std::cout << "component #" << iComponent << ": vec1 = " << vec1(iComponent) << ", vec2 = " << vec2(iComponent) << std::endl;
      std::cout << "assert(" << (vec1(iComponent) - vec2(iComponent)) << " < " << 1.e-3*(TMath::Abs(TMath::Max(1.e-6, vec1(iComponent))) + TMath::Abs(TMath::Max(1.e-6, vec2(iComponent)))) << ")" << std::endl;
      assert((vec1(iComponent) - vec2(iComponent)) < 1.e-3*(TMath::Abs(TMath::Max(1.e-6, vec1(iComponent))) + TMath::Abs(TMath::Max(1.e-6, vec2(iComponent)))));
    }
    eigenVectors_and_Values.push_back(EigenVector_and_Value(eigenVector, eigenValue));
  }
  return eigenVectors_and_Values;
}

struct fitFunction_and_legendEntry
{
  fitFunction_and_legendEntry(TF1* fitFunction, const std::string& legendEntry)
    : fitFunction_(fitFunction),
      legendEntry_(legendEntry)
  {}
  ~fitFunction_and_legendEntry() {}
  TF1* fitFunction_;
  std::string legendEntry_;
};

void makeControlPlot(TGraphAsymmErrors* graph, 
		     TF1* fitFunction_central, std::vector<fitFunction_and_legendEntry>& fitFunctions_sysShifts, 
		     double xMin, double xMax, const std::string& xAxisTitle, 
		     bool useLogScale, double yMin, double yMax, 
		     const std::string& outputFileName)
{
  if ( fitFunctions_sysShifts.size() > 6 )
    throw cms::Exception("makeControlPlot") 
      << "Fit functions with more than 3 parameters are not supported yet !!\n";

  TCanvas* canvas = new TCanvas("canvas", "canvas", 800, 900);
  canvas->SetFillColor(10);
  canvas->SetBorderSize(2);
  canvas->SetTopMargin(0.12);
  canvas->SetLeftMargin(0.12);
  canvas->SetBottomMargin(0.12);
  
  TPad* topPad = new TPad("topPad", "topPad", 0.00, 0.35, 1.00, 1.00);
  topPad->SetFillColor(10);
  topPad->SetTopMargin(0.04);
  topPad->SetLeftMargin(0.15);
  topPad->SetBottomMargin(0.03);
  topPad->SetRightMargin(0.05);
  topPad->SetGridx();
  topPad->SetGridy();
  topPad->SetLogy(useLogScale);

  canvas->cd();
  topPad->Draw();
  topPad->cd();

  TH1* dummyHistogram_top = new TH1D("dummyHistogram_top", "dummyHistogram_top", 10, xMin, xMax);
  dummyHistogram_top->SetTitle("");
  dummyHistogram_top->SetStats(false);
  dummyHistogram_top->SetMaximum(yMax);
  dummyHistogram_top->SetMinimum(yMin);
  
  TAxis* xAxis_top = dummyHistogram_top->GetXaxis();
  xAxis_top->SetTitle(xAxisTitle.data());
  xAxis_top->SetTitleOffset(1.2);
  xAxis_top->SetLabelColor(10);
  xAxis_top->SetTitleColor(10);

  TAxis* yAxis_top = dummyHistogram_top->GetYaxis();
  yAxis_top->SetTitle("f_{#tau}");
  yAxis_top->SetTitleSize(0.050);
  yAxis_top->SetTitleOffset(1.15);

  dummyHistogram_top->Draw();

  TLegend* legend = new TLegend(0.69, 0.935 - 0.055*(1 + fitFunctions_sysShifts.size()/2), 0.94, 0.935, "", "brNDC"); 
  legend->SetBorderSize(0);
  legend->SetFillColor(0);

  fitFunction_central->SetLineColor(2);
  fitFunction_central->Draw("Lsame");
  legend->AddEntry(fitFunction_central, "Best Fit", "L");    

  int colors[3] = { 4, 6, 7 };

  int idx_top = 0;
  for ( std::vector<fitFunction_and_legendEntry>::const_iterator fitFunction_sysShift = fitFunctions_sysShifts.begin();
	fitFunction_sysShift != fitFunctions_sysShifts.end(); ++fitFunction_sysShift ) {
    int iColor = idx_top / 2;
    assert(iColor <= 2);
    fitFunction_sysShift->fitFunction_->SetLineColor(colors[iColor]);
    fitFunction_sysShift->fitFunction_->SetLineStyle(8);
    fitFunction_sysShift->fitFunction_->Draw("Lsame");
    if ( (idx_top % 2) == 0 ) legend->AddEntry(fitFunction_sysShift->fitFunction_, fitFunction_sysShift->legendEntry_.data(), "L");
    ++idx_top;
  }

  graph->SetMarkerStyle(8);
  graph->SetMarkerColor(1);
  graph->Draw("p");

  legend->Draw();

  TPad* bottomPad = new TPad("bottomPad", "bottomPad", 0.00, 0.00, 1.00, 0.35);
  bottomPad->SetFillColor(10);
  bottomPad->SetTopMargin(0.02);
  bottomPad->SetLeftMargin(0.15);
  bottomPad->SetBottomMargin(0.24);
  bottomPad->SetRightMargin(0.05);
  bottomPad->SetGridx();
  bottomPad->SetGridy();

  canvas->cd();
  bottomPad->Draw();
  bottomPad->cd();

  TH1* dummyHistogram_bottom = new TH1D("dummyHistogram_bottom", "dummyHistogram_bottom", 10, xMin, xMax);
  
  dummyHistogram_bottom->SetMinimum(-0.50);
  dummyHistogram_bottom->SetMaximum(+0.50);

  TAxis* xAxis_bottom = dummyHistogram_bottom->GetXaxis();
  xAxis_bottom->SetTitle(xAxisTitle.data());
  xAxis_bottom->SetTitleOffset(1.20);
  xAxis_bottom->SetLabelColor(1);
  xAxis_bottom->SetTitleColor(1);
  xAxis_bottom->SetTitleSize(0.08);
  xAxis_bottom->SetLabelOffset(0.02);
  xAxis_bottom->SetLabelSize(0.08);
  xAxis_bottom->SetTickLength(0.055);

  TAxis* yAxis_bottom = dummyHistogram_bottom->GetYaxis();
  yAxis_bottom->SetTitle("#frac{f_{#tau} - Fit}{Fit}");
  yAxis_bottom->SetTitleOffset(0.75);
  yAxis_bottom->SetNdivisions(505);
  yAxis_bottom->CenterTitle();
  yAxis_bottom->SetTitleSize(0.08);
  yAxis_bottom->SetLabelSize(0.08);
  yAxis_bottom->SetTickLength(0.04);

  dummyHistogram_bottom->SetTitle("");
  dummyHistogram_bottom->SetStats(false);
  dummyHistogram_bottom->Draw();

  int numPoints = graph->GetN();
  TGraph* graph_line = new TGraph(numPoints);
  for ( int iPoint = 0; iPoint < numPoints; ++iPoint ) {
    Double_t x, y;
    graph->GetPoint(iPoint, x, y);
    graph_line->SetPoint(iPoint, x, 1.0);
  }
  graph_line->SetLineColor(8);
  graph_line->SetLineWidth(1);
  graph_line->Draw("L");

  std::vector<TF1*> fitFunctionsToDelete;

  int idx_bottom = 0;
  for ( std::vector<fitFunction_and_legendEntry>::const_iterator fitFunction_sysShift = fitFunctions_sysShifts.begin();
	fitFunction_sysShift != fitFunctions_sysShifts.end(); ++fitFunction_sysShift ) {
    TF1* fitFunction_pass = fitFunction_sysShift->fitFunction_;
    TString fitFunction_formula_pass = fitFunction_pass->GetTitle();
    int numPar_pass = fitFunction_pass->GetNpar();
    TF1* fitFunction_fail = fitFunction_central;
    TString fitFunction_formula_fail = fitFunction_fail->GetTitle();
    int numPar_fail = fitFunction_fail->GetNpar();
    for ( int iPar = 0; iPar < numPar_fail; ++iPar ) {
      fitFunction_formula_fail.ReplaceAll(Form("[%i]", iPar), Form("[%i]", iPar + numPar_pass));      
    }
    std::string fitFunctionName_sysShift_div_central = Form("%s_div_central", fitFunction_pass->GetName());
    std::string fitFunction_formula_sysShift_div_central = Form("(%s)/(%s) - 1.0", fitFunction_formula_pass.Data(), fitFunction_formula_fail.Data());
    TF1* fitFunction_sysShift_div_central = new TF1(fitFunctionName_sysShift_div_central.data(), fitFunction_formula_sysShift_div_central.data(), xMin, xMax);
    for ( int iPar_pass = 0; iPar_pass < numPar_fail; ++iPar_pass ) {
      fitFunction_sysShift_div_central->SetParameter(iPar_pass, fitFunction_fail->GetParameter(iPar_pass));
    }
    for ( int iPar_fail = 0; iPar_fail < numPar_fail; ++iPar_fail ) {
      fitFunction_sysShift_div_central->SetParameter(iPar_fail + numPar_pass, fitFunction_fail->GetParameter(iPar_fail));
    }
    int iColor = idx_bottom / 2;
    assert(iColor <= 2);
    fitFunction_sysShift_div_central->SetLineColor(colors[iColor]);
    fitFunction_sysShift_div_central->Draw("Lsame");
    fitFunctionsToDelete.push_back(fitFunction_sysShift_div_central);
    ++idx_bottom;
  }

  TGraphAsymmErrors* graph_div_fit = new TGraphAsymmErrors(numPoints);
  for ( int iPoint = 0; iPoint < numPoints; ++iPoint ) {
    double x, y;
    graph->GetPoint(iPoint, x, y);
    double fitFunctionValue = fitFunction_central->Eval(x);
    graph_div_fit->SetPoint(iPoint, x, y/fitFunctionValue - 1.0);
    double xErrUp = graph->GetErrorXhigh(iPoint);
    double xErrDown = graph->GetErrorXlow(iPoint);
    double yErrUp = graph->GetErrorYhigh(iPoint);
    double yErrDown = graph->GetErrorYlow(iPoint);
    graph_div_fit->SetPointError(iPoint, xErrDown, xErrUp, yErrDown/fitFunctionValue, yErrUp/fitFunctionValue);
  }
  graph_div_fit->SetMarkerStyle(8);
  graph_div_fit->SetMarkerColor(1);
  graph_div_fit->Draw("p");
  
  canvas->Update();
  size_t idx = outputFileName.find_last_of('.');
  std::string outputFileName_plot = std::string(outputFileName, 0, idx);
  if ( useLogScale ) outputFileName_plot.append("_log");
  else outputFileName_plot.append("_linear");
  if ( idx != std::string::npos ) canvas->Print(std::string(outputFileName_plot).append(std::string(outputFileName, idx)).data());
  canvas->Print(std::string(outputFileName_plot).append(".png").data());
  canvas->Print(std::string(outputFileName_plot).append(".pdf").data());
  canvas->Print(std::string(outputFileName_plot).append(".root").data());
  
  delete legend;
  delete dummyHistogram_top;
  delete topPad;
  delete dummyHistogram_bottom;
  delete graph_line;
  for ( std::vector<TF1*>::iterator it = fitFunctionsToDelete.begin();
	it != fitFunctionsToDelete.end(); ++it ) {
    delete (*it);
  }
  delete graph_div_fit;
  delete canvas;
}

std::pair<TH1*, TH1*> getHistogramsLoose_and_Tight(
  TDirectory* inputDir_loose, const std::string& looseRegion, TDirectory* inputDir_tight, const std::string& tightRegion, 
  const std::string& processData_or_mc, const vstring& processesToSubtract, 
  const std::string& etaBin, const std::string& hadTauSelection, const std::string& histogramToFit)
{
  std::cout << "<getHistogramsPass_and_Fail>:" << std::endl;
  std::cout << " inputDir_loose = " << inputDir_loose << ": name = " << inputDir_loose->GetName() << std::endl;
  std::cout << " looseRegion = " << looseRegion << std::endl;
  std::cout << " inputDir_tight = " << inputDir_tight << ": name = " << inputDir_tight->GetName() << std::endl;
  std::cout << " tightRegion = " << tightRegion << std::endl;
  std::cout << " etaBin = " << etaBin << std::endl;
  std::cout << " hadTauSelection = " << hadTauSelection << std::endl;
  std::cout << " histogramToFit = " << histogramToFit << std::endl;

  std::string histogramName, subdirName_loose, subdirName_tight;
  size_t idx = histogramToFit.find_last_of('/');
  if ( idx != std::string::npos ) {
    histogramName = std::string(histogramToFit, idx + 1, std::string::npos);
    subdirName_loose = Form("%s/%s", etaBin.data(), std::string(histogramToFit, 0, idx).data());
    subdirName_tight = Form("%s/%s/%s", etaBin.data(), hadTauSelection.data(), std::string(histogramToFit, 0, idx).data());
  } else {
    histogramName = histogramToFit;
    subdirName_loose = Form("%s", etaBin.data());
    subdirName_tight = Form("%s/%s", etaBin.data(), hadTauSelection.data());
  }
  TDirectory* inputSubdir_loose = getSubdirectory(inputDir_loose, subdirName_loose, true);
  TDirectory* inputSubdir_tight = getSubdirectory(inputDir_tight, subdirName_tight, true);

  TH1* histogramData_or_mc_loose = getHistogram(inputSubdir_loose, processData_or_mc, histogramName, "central", true);
  assert(histogramData_or_mc_loose);
  std::cout << " histogramData_or_mc_loose = " << histogramData_or_mc_loose << ":" 
	    << " name = " << histogramData_or_mc_loose->GetName() << ", integral = " << histogramData_or_mc_loose->Integral() << std::endl;
  dumpHistogram(histogramData_or_mc_loose);
  TH1* histogramData_or_mc_tight = getHistogram(inputSubdir_tight, processData_or_mc, histogramName, "central", true);
  assert(histogramData_or_mc_tight);
  std::cout << " histogramData_or_mc_tight = " << histogramData_or_mc_tight << ":" 
	    << " name = " << histogramData_or_mc_tight->GetName() << ", integral = " << histogramData_or_mc_tight->Integral() << std::endl;
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
  std::string histogramNameJetToTauFakeRate_loose = Form("jetToTauFakeRate_%s_%s_loose", hadTauSelection.data(), histogramName.data());
  TH1* histogramJetToTauFakeRate_loose = subtractHistograms(histogramNameJetToTauFakeRate_loose.data(), histogramData_or_mc_loose, histogramsToSubtract_loose);  
  std::cout << "computing sum(histograms) in tight region" << std::endl;
  std::string histogramNameJetToTauFakeRate_tight = Form("jetToTauFakeRate_%s_%s_tight", hadTauSelection.data(), histogramName.data());
  TH1* histogramJetToTauFakeRate_tight = subtractHistograms(histogramNameJetToTauFakeRate_tight.data(), histogramData_or_mc_tight, histogramsToSubtract_tight);  

  return std::pair<TH1*, TH1*>(histogramJetToTauFakeRate_loose, histogramJetToTauFakeRate_tight);
}

void compFakeRate(double nPass, double nPassErr, double nFail, double nFailErr, double& avFakeRate, double& avFakeRateErrUp, double& avFakeRateErrDown, bool& errorFlag)
{ 
  double sumWeights = nPass + nFail;
  double sumWeights2 = square(nPassErr) + square(nFailErr);
  if ( sumWeights > 0. && sumWeights2 > 0. ) {
    double n_eff = square(sumWeights/TMath::Sqrt(sumWeights2));
    double sf = n_eff/(sumWeights);
    static TRandom3 rnd;
    Int_t nPass_int = TMath::Nint(sf*nPass);
    if ( nPass_int < 0 ) nPass_int = 0;
    TH1* histogram_pass_tmp = new TH1D("histogram_pass_tmp", "histogram_pass_tmp", 1, -0.5, +0.5);
    histogram_pass_tmp->SetBinContent(1, nPass_int);
    histogram_pass_tmp->SetBinError(1, TMath::Sqrt(nPass_int));
    Int_t nFail_int = TMath::Nint(sf*nFail);
    if ( nFail_int < 0 ) nFail_int = 0;
    TH1* histogram_fail_tmp = new TH1D("histogram_fail_tmp", "histogram_fail_tmp", 1, -0.5, +0.5);
    histogram_fail_tmp->SetBinContent(1, nFail_int);
    histogram_fail_tmp->SetBinError(1, TMath::Sqrt(nFail_int));
    TGraphAsymmErrors* graph_pass_div_fail_tmp = new TGraphAsymmErrors(1);
    graph_pass_div_fail_tmp->Divide(histogram_pass_tmp, histogram_fail_tmp, "pois");
    double dummy;
    graph_pass_div_fail_tmp->GetPoint(0, dummy, avFakeRate);
    avFakeRateErrUp   = graph_pass_div_fail_tmp->GetErrorYhigh(0);
    avFakeRateErrDown = graph_pass_div_fail_tmp->GetErrorYlow(0);
    delete histogram_pass_tmp;
    delete histogram_fail_tmp;
    delete graph_pass_div_fail_tmp;
    errorFlag = false;
    std::cout << "nPass = " << nPass << " +/- " << nPassErr << " (int = " << nPass_int << "), nFail = " << nFail << " +/- " << nFailErr << " (int = " << nFail_int << ")"
	      << " --> avFakeRate = " << avFakeRate << " + " << avFakeRateErrUp << " - " << avFakeRateErrDown << std::endl;
  } else {
    avFakeRate        = 0.5;
    avFakeRateErrUp   = 0.5;
    avFakeRateErrDown = 0.5;
    errorFlag = true;
    std::cout << "sumWeights = " << sumWeights << ", sumWeights2 = " << sumWeights2 
	      << " --> avFakeRate = " << avFakeRate << " + " << avFakeRateErrUp << " - " << avFakeRateErrDown << std::endl;
  }
}

int main(int argc, char* argv[]) 
{
//--- parse command-line arguments
  if ( argc < 2 ) {
    std::cout << "Usage: " << argv[0] << " [parameters.py]" << std::endl;
    return 0;
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

  std::string processData_or_mc = cfg_comp.getParameter<std::string>("processData");
  vstring processesToSubtract = cfg_comp.getParameter<vstring>("processesToSubtract");

  vstring hadTauSelections = cfg_comp.getParameter<vstring>("hadTauSelections");

  vdouble hadTauAbsEtaBins = cfg_comp.getParameter<vdouble>("hadTauAbsEtaBins");
  if ( hadTauAbsEtaBins.size() < 2 ) throw cms::Exception("comp_jetToTauFakeRate") 
    << "Invalid Configuration parameter 'hadTauAbsEtaBins' !!\n";
  
  bool isMC = cfg_comp.getParameter<bool>("isMC"); 
  std::string data_or_mc = ( isMC ) ? "mc" : "data";

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

  fwlite::InputSource inputFiles(cfg); 
  if ( !(inputFiles.files().size() == 1) )
    throw cms::Exception("comp_jetToTauFakeRate") 
      << "Exactly one input file expected !!\n";
  TFile* inputFile = new TFile(inputFiles.files().front().data());

  fwlite::OutputFiles outputFile(cfg);
  fwlite::TFileService fs = fwlite::TFileService(outputFile.file().data());

  TDirectory* inputDir_loose = getDirectory(inputFile, looseRegion, true);
  assert(inputDir_loose);
  std::cout << "inputDir_loose = " << inputDir_loose << ": name = " << inputDir_loose->GetName() << std::endl;
  TDirectory* inputDir_tight = getDirectory(inputFile, tightRegion, true);
  assert(inputDir_tight);
  std::cout << "inputDir_tight = " << inputDir_tight << ": name = " << inputDir_tight->GetName() << std::endl;

  int numEtaBins = hadTauAbsEtaBins.size() - 1;
  for ( int idxEtaBin = 0; idxEtaBin < numEtaBins; ++idxEtaBin ) {
    double minAbsEta = hadTauAbsEtaBins[idxEtaBin];
    double maxAbsEta = hadTauAbsEtaBins[idxEtaBin + 1];
    std::string etaBin = getEtaBin(minAbsEta, maxAbsEta);
    
    for ( vstring::const_iterator hadTauSelection = hadTauSelections.begin();
	  hadTauSelection != hadTauSelections.end(); ++hadTauSelection ) {
      TDirectory* outputDir = createSubdirectory_recursively(fs, Form("jetToTauFakeRate/%s/%s/%s", hadTauSelection->data(), etaBin.data(), data_or_mc.data()));
      outputDir->cd();

      for ( vstring::const_iterator histogramToFit = histogramsToFit.begin();
	    histogramToFit != histogramsToFit.end(); ++histogramToFit ) {
	std::cout << "fitting " << (*histogramToFit) << ":" << std::endl;

        std::pair<TH1*, TH1*> histogram_loose_and_tight = getHistogramsLoose_and_Tight(
          inputDir_loose, looseRegion, inputDir_tight, tightRegion, 
          processData_or_mc, processesToSubtract, 
	  etaBin, *hadTauSelection, *histogramToFit);
	TH1* histogram_loose = histogram_loose_and_tight.first;
	TH1* histogram_tight = histogram_loose_and_tight.second;

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
	  std::cout << "bin #" << idxBin << "(x = " << histogram_loose->GetBinCenter(idxBin) << ")" << ":";	  
	  compFakeRate(nPass, nPassErr, nFail, nFailErr, jetToTauFakeRate, jetToTauFakeRateErrUp, jetToTauFakeRateErrDown, errorFlag);
	  if ( errorFlag ) continue;
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
	std::string graphName_jetToTauFakeRate = Form("jetToTauFakeRate_%s", histogramToFit->data());
	graph_jetToTauFakeRate->SetName(graphName_jetToTauFakeRate.data());
	graph_jetToTauFakeRate->Write();

	std::string fitFunctionName = Form("fitFunction_%s", histogramToFit->data());
	double x0 = histogram_loose->GetMean();
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
	
	TFitResultPtr fitResult = graph_jetToTauFakeRate->Fit(fitFunction, "ERNS");
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
	    std::string fitFunctionParUpName = Form("fitFunctionPar%iUp_%s", idxPar, histogramToFit->data());
	    TF1* fitFunctionParUp = new TF1(fitFunctionParUpName.data(), fitFunction_formula_wrt_x0.data(), xMin, xMax);
	    for ( size_t idxComponent = 0; idxComponent < dimension; ++idxComponent ) {    
	      fitFunctionParUp->SetParameter(
		idxComponent, 
		fitFunction->GetParameter(idxComponent) + TMath::Sqrt(eigenVector_and_Value->eigenValue_)*eigenVector_and_Value->eigenVector_(idxComponent));
	    }
	    fitFunctions_sysShifts.push_back(fitFunction_and_legendEntry(fitFunctionParUp, Form("EigenVec #%i", idxPar)));
	    fitFunctionParUp->Write();
	    std::string fitFunctionParDownName = Form("fitFunctionPar%iDown_%s", idxPar, histogramToFit->data());
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
	std::string controlPlotFileName = TString(outputFile.file().data()).ReplaceAll(".root", Form(
	  "_%s_%s_%s_%s_controlPlot.png", hadTauSelection->data(), etaBin.data(), data_or_mc.data(), histogramToFit->data())).Data();
	makeControlPlot(graph_jetToTauFakeRate, 
			fitFunction, fitFunctions_sysShifts, xMin, xMax, "p_{T} [GeV]", true, 1.e-3, 1.e0, controlPlotFileName);
      }
    }
  }

  delete inputFile;

  clock.Show("comp_jetToTauFakeRate");

  return 0;
}
