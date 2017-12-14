/** \executable comp_LeptonFakeRate
 *
 * Determine probability for jets to get misidentified as hadronic tau candidates,
 * measured in tt+jets events selected by requiring the presence of two b-jets, plus an electron and muon pair of opposite charge.
 *
 * \author Ram Krishna Dewanjee, Tallinn
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
#include <TRandom3.h>
#include <TError.h> // gErrorAbortLevel, kError

#include <iostream>
#include <string>
#include <vector>
#include <assert.h>
#include <fstream>
typedef std::vector<std::string> vstring;
typedef std::vector<double> vdouble;

TArrayD convertToTArrayD(const vdouble& binEdges)
{
  int numBins = binEdges.size() - 1;
  assert(numBins >= 1);
  TArrayD binEdges_array(numBins + 1);
  for ( int idxBin = 0; idxBin < numBins; ++idxBin ) {
    binEdges_array[idxBin] = binEdges[idxBin];
    binEdges_array[idxBin + 1] = binEdges[idxBin + 1];
  }
  return binEdges_array;
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
    //std::cout << "vec2:" << std::endl;
    //vec2.Print();
    // CV: check that EigenVector is indeed an EigenVector,
    //     i.e. that we interpreted the ordering of columns and rows of the eigenVectors matrix correctly
    for ( int iComponent = 0; iComponent < dimension; ++iComponent ) {   
      std::cout << "component #" << iComponent << ": vec1 = " << vec1(iComponent) << ", vec2 = " << vec2(iComponent) << std::endl;
      double diff = vec1(iComponent) - vec2(iComponent);
      double sum = TMath::Abs(TMath::Max(1.e-6, vec1(iComponent))) + TMath::Abs(TMath::Max(1.e-6, vec2(iComponent)));
      std::cout << "assert(" << diff << " < " << TMath::Max(1.e-6, 1.e-3*sum) << ")" << std::endl;
      assert(diff < TMath::Max(1.e-6, 1.e-3*sum));
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

void makeControlPlot(TGraphAsymmErrors* graph_data, const std::string& legendEntry_data,
		     TGraphAsymmErrors* graph_mc, const std::string& legendEntry_mc,
		     TGraphAsymmErrors* graph_data_div_mc, 
		     double xMin, double xMax, const std::string& xAxisTitle, 
		     bool useLogScale, double yMin, double yMax, 
		     const std::string& outputFileName)
{
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

  TLegend* legend = new TLegend(0.74, 0.785, 0.94, 0.935, "", "brNDC"); 
  legend->SetBorderSize(0);
  legend->SetFillColor(0);
  legend->AddEntry(graph_data, legendEntry_data.data(), "p");
  legend->AddEntry(graph_mc, legendEntry_mc.data(), "p");

  graph_mc->SetMarkerStyle(24);
  graph_mc->SetMarkerColor(1);
  graph_mc->Draw("p");

  graph_data->SetMarkerStyle(20);
  graph_data->SetMarkerColor(1);
  graph_data->Draw("p");

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
  
  dummyHistogram_bottom->SetMinimum(-1.50);
  dummyHistogram_bottom->SetMaximum(+1.50);

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
  yAxis_bottom->SetTitle("#frac{f_{#tau}^{data} - f_{#tau}^{mc}}{f_{#tau}^{mc}}");
  yAxis_bottom->SetTitleOffset(0.75);
  yAxis_bottom->SetNdivisions(505);
  yAxis_bottom->CenterTitle();
  yAxis_bottom->SetTitleSize(0.08);
  yAxis_bottom->SetLabelSize(0.08);
  yAxis_bottom->SetTickLength(0.04);

  dummyHistogram_bottom->SetTitle("");
  dummyHistogram_bottom->SetStats(false);
  dummyHistogram_bottom->Draw();

  graph_data_div_mc->SetMarkerStyle(20);
  graph_data_div_mc->SetMarkerColor(1);
  graph_data_div_mc->Draw("p");
  
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
  delete canvas;
}

void makeControlPlot_fit(TGraphAsymmErrors* graph, 
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
  yAxis_top->SetTitle("#frac{f_{#tau}^{data} - f_{#tau}^{mc}}{f_{#tau}^{mc}}");
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
  
  dummyHistogram_bottom->SetMinimum(-1.50);
  dummyHistogram_bottom->SetMaximum(+1.50);

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
  yAxis_bottom->SetTitle("#frac{f_{#tau}^{data} - f_{#tau}^{mc}}{f_{#tau}^{mc}} - Fit");
  yAxis_bottom->SetTitleOffset(0.75);
  yAxis_bottom->SetNdivisions(505);
  yAxis_bottom->CenterTitle();
  yAxis_bottom->SetTitleSize(0.08);
  yAxis_bottom->SetLabelSize(0.08);
  yAxis_bottom->SetTickLength(0.04);

  dummyHistogram_bottom->SetTitle("");
  dummyHistogram_bottom->SetStats(false);
  dummyHistogram_bottom->Draw();

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

  int numPoints = graph->GetN();
  TGraphAsymmErrors* graph_div_fit = new TGraphAsymmErrors(numPoints);
  for ( int iPoint = 0; iPoint < numPoints; ++iPoint ) {
    double x, y;
    graph->GetPoint(iPoint, x, y);
    double fitFunctionValue = fitFunction_central->Eval(x);
    graph_div_fit->SetPoint(iPoint, x, y - fitFunctionValue);
    double xErrUp = graph->GetErrorXhigh(iPoint);
    double xErrDown = graph->GetErrorXlow(iPoint);
    double yErrUp = graph->GetErrorYhigh(iPoint);
    double yErrDown = graph->GetErrorYlow(iPoint);
    graph_div_fit->SetPointError(iPoint, xErrDown, xErrUp, yErrDown, yErrUp);
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
    subdirName_tight = Form("%s/%s/%s", hadTauSelection.data(), etaBin.data(), std::string(histogramToFit, 0, idx).data());
  } else {
    histogramName = histogramToFit;
    subdirName_loose = Form("%s", etaBin.data());
    subdirName_tight = Form("%s/%s", hadTauSelection.data(), etaBin.data());
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
  std::string histogramNameJetToTauFakeRate_loose = Form("jetToTauFakeRate_%s_%s_%s_%s_loose", processData_or_mc.data(), hadTauSelection.data(), etaBin.data(), histogramName.data());
  TH1* histogramJetToTauFakeRate_loose = subtractHistograms(histogramNameJetToTauFakeRate_loose.data(), histogramData_or_mc_loose, histogramsToSubtract_loose);  
  std::cout << "computing sum(histograms) in tight region" << std::endl;
  std::string histogramNameJetToTauFakeRate_tight = Form("jetToTauFakeRate_%s_%s_%s_%s_tight", processData_or_mc.data(), hadTauSelection.data(), etaBin.data(), histogramName.data());
  TH1* histogramJetToTauFakeRate_tight = subtractHistograms(histogramNameJetToTauFakeRate_tight.data(), histogramData_or_mc_tight, histogramsToSubtract_tight);  

  return std::pair<TH1*, TH1*>(histogramJetToTauFakeRate_loose, histogramJetToTauFakeRate_tight);
}



std::pair<TH1*, TH1*> getHistogramsLoose_and_Tight_LeptonFakeRate( 
  TDirectory* inputDir_loose, const std::string& looseRegion, TDirectory* inputDir_tight, const std::string& tightRegion, 
  const std::string& processData_or_mc, const vstring& processesToSubtract, 
  const std::string& etaBin, const std::string& PtBin, const std::string& histogramToFit)
{
  std::cout << "<getHistogramsPass_and_Fail>:" << std::endl;
  std::cout << " inputDir_loose = " << inputDir_loose << ": name = " << inputDir_loose->GetName() << std::endl;
  std::cout << " looseRegion = " << looseRegion << std::endl;
  std::cout << " inputDir_tight = " << inputDir_tight << ": name = " << inputDir_tight->GetName() << std::endl;
  std::cout << " tightRegion = " << tightRegion << std::endl;
  std::cout << " etaBin = " << etaBin << std::endl;
  std::cout << " PtBin = " << PtBin << std::endl;
  std::cout << " histogramToFit = " << histogramToFit << std::endl;

  std::string histogramName, subdirName_loose, subdirName_tight;
  size_t idx = histogramToFit.find_last_of('/');
  if(etaBin != "" && PtBin != ""){
    if ( idx != std::string::npos) {
      histogramName = std::string(histogramToFit, idx + 1, std::string::npos);
      subdirName_loose = Form("%s/%s/%s", etaBin.data(), PtBin.data(), std::string(histogramToFit, 0, idx).data());
      subdirName_tight = Form("%s/%s/%s", etaBin.data(), PtBin.data(), std::string(histogramToFit, 0, idx).data());
    } else {
      histogramName = histogramToFit;
      subdirName_loose = Form("%s/%s", etaBin.data(), PtBin.data());
      subdirName_tight = Form("%s/%s", etaBin.data(), PtBin.data());
    }
  } else if(etaBin == "" && PtBin == ""){
    histogramName = histogramToFit;
    subdirName_loose = "incl";
    subdirName_tight = "incl";
  }

  std::cout<< " subdirName_loose " << subdirName_loose << std::endl;
  std::cout<< " subdirName_tight " << subdirName_tight << std::endl;

  std::cout<< "Entering Loose "<< std::endl;
  TDirectory* inputSubdir_loose = getSubdirectory(inputDir_loose, subdirName_loose, true);

  std::cout<< "Entering Tight "<< std::endl;
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
      

  std::string histogramNameLeptonFakeRate_loose = "";
  std::string histogramNameLeptonFakeRate_tight = "";

  if(etaBin != "" && PtBin != ""){
    histogramNameLeptonFakeRate_loose  = Form("LeptonFakeRate_%s_%s_%s_%s_loose", processData_or_mc.data(), etaBin.data(), PtBin.data(), histogramName.data());
    histogramNameLeptonFakeRate_tight = Form("LeptonFakeRate_%s_%s_%s_%s_tight", processData_or_mc.data(), etaBin.data(), PtBin.data(), histogramName.data());
  }else{
    histogramNameLeptonFakeRate_loose  = Form("LeptonFakeRate_%s_incl_%s_loose", processData_or_mc.data(), histogramName.data());
    histogramNameLeptonFakeRate_tight  = Form("LeptonFakeRate_%s_incl_%s_tight", processData_or_mc.data(), histogramName.data());
  }

  std::cout << "computing sum(histograms) in loose region" << std::endl;
  TH1* histogramLeptonFakeRate_loose = subtractHistograms(histogramNameLeptonFakeRate_loose.data(), histogramData_or_mc_loose, histogramsToSubtract_loose);  
  std::cout << "computing sum(histograms) in tight region" << std::endl;
  TH1* histogramLeptonFakeRate_tight = subtractHistograms(histogramNameLeptonFakeRate_tight.data(), histogramData_or_mc_tight, histogramsToSubtract_tight);  

  return std::pair<TH1*, TH1*>(histogramLeptonFakeRate_loose, histogramLeptonFakeRate_tight);
}


int GetBinIndex(double value, TH2* h2d_mu, bool isXaxis){
  int bin_index = 0;

  if(isXaxis){ // x axis

    for(int i = 1; i <= h2d_mu->GetNbinsX(); i++){
      if((i+1) <= h2d_mu->GetNbinsX() && value <= (h2d_mu->GetXaxis()->GetBinCenter(i) + h2d_mu->GetXaxis()->GetBinCenter(i+1))/2.){
 	// std::cout << "The x index is " << i << std::endl;  
        bin_index = i;
        break;
      }else if( (i+1) > h2d_mu->GetNbinsX() ){
	// std::cout << "The x index is " << i << std::endl;  
	bin_index = i;
	break;
      }
    }

  }else{ // y axis
    std::cout << "No. of Y bins " << h2d_mu->GetNbinsY() << std::endl;
    for(int j = 1; j <= h2d_mu->GetNbinsY(); j++){
      std::cout << "Avg value: " << (h2d_mu->GetYaxis()->GetBinCenter(j) + h2d_mu->GetYaxis()->GetBinCenter(j+1))/2. << std::endl; 
      if((j+1) <= h2d_mu->GetNbinsY() && value <= (h2d_mu->GetYaxis()->GetBinCenter(j) + h2d_mu->GetYaxis()->GetBinCenter(j+1))/2.){
	std::cout << "Eta Bin " << value  << " The y index is " << j << std::endl; 
	bin_index = j; 
	break;
      }else if( (j+1) > h2d_mu->GetNbinsY() ){
	std::cout << "The y index is " << j << std::endl;
	bin_index = j;  
	break;
      }
    }
  }

  return bin_index;
}

void Make2DHisto(TGraphAsymmErrors* graph, TH2* histo, double absEtaMax = 0.){
  
  int numPoints = graph->GetN();
  const int size = numPoints;
  double X[size], Y[size];
  for(int iPoint = 0; iPoint < numPoints; ++iPoint){
    graph->GetPoint(iPoint, X[iPoint], Y[iPoint]);
    // double xErrUp = graph->GetErrorXhigh(iPoint);
    // double xErrDown = graph->GetErrorXlow(iPoint);
    double yErrUp = graph->GetErrorYhigh(iPoint);
    double yErrDown = graph->GetErrorYlow(iPoint);
    double ErrSymmY = TMath::Sqrt( TMath::Power((Y[iPoint] - yErrUp), 2.0) + TMath::Power( (Y[iPoint] - yErrDown), 2.0) )/2.0;
    int x_index = GetBinIndex(X[iPoint], histo, true);
    int y_index = GetBinIndex(absEtaMax, histo, false);
    std::cout<< "x_index "<< x_index << " y_index " << y_index << " BinContent " << Y[iPoint] <<  std::endl;
    histo->SetBinContent(x_index, y_index, Y[iPoint]);
    histo->SetBinError(x_index, y_index, ErrSymmY);
  }
}

void Fill2DHisto(TH2* histo, double value = 0., double err_value = 0., double PtMax = 0., double absEtaMax = 0.){

    int x_index = GetBinIndex(PtMax, histo, true);
    int y_index = GetBinIndex(absEtaMax, histo, false);
    std::cout<< "x_index "<< x_index << " y_index " << y_index << " BinContent " << value <<  std::endl;
    histo->SetBinContent(x_index, y_index, value);
    histo->SetBinError(x_index, y_index, err_value);
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
    TH1* histogram_pass_plus_fail_tmp = new TH1D("histogram_pass_plus_fail_tmp", "histogram_pass_plus_fail_tmp", 1, -0.5, +0.5);
    histogram_pass_plus_fail_tmp->SetBinContent(1, nPass_int + nFail_int);
    histogram_pass_plus_fail_tmp->SetBinError(1, TMath::Sqrt(nPass_int + nFail_int));
    TGraphAsymmErrors* graph_pass_div_pass_plus_fail_tmp = new TGraphAsymmErrors(1);
    graph_pass_div_pass_plus_fail_tmp->Divide(histogram_pass_tmp, histogram_pass_plus_fail_tmp, "cp");
    double dummy;
    graph_pass_div_pass_plus_fail_tmp->GetPoint(0, dummy, avFakeRate);
    avFakeRateErrUp = graph_pass_div_pass_plus_fail_tmp->GetErrorYhigh(0);
    if ( avFakeRateErrUp < 2.e-2 ) avFakeRateErrUp = 2.e-2;
    avFakeRateErrDown = graph_pass_div_pass_plus_fail_tmp->GetErrorYlow(0);
    if ( avFakeRateErrDown < 2.e-2 ) avFakeRateErrDown = 2.e-2;
    delete histogram_pass_tmp;
    delete histogram_pass_plus_fail_tmp;
    delete graph_pass_div_pass_plus_fail_tmp;
    errorFlag = false;
    std::cout << " nPass = " << nPass << " +/- " << nPassErr << " (int = " << nPass_int << "), nFail = " << nFail << " +/- " << nFailErr << " (int = " << nFail_int << ")"
	      << " --> avFakeRate = " << avFakeRate << " + " << avFakeRateErrUp << " - " << avFakeRateErrDown << std::endl;
  } else {
    avFakeRate        = 0.5;
    avFakeRateErrUp   = 0.5;
    avFakeRateErrDown = 0.5;
    errorFlag = true;
    std::cout << " sumWeights = " << sumWeights << ", sumWeights2 = " << sumWeights2 
	      << " --> avFakeRate = " << avFakeRate << " + " << avFakeRateErrUp << " - " << avFakeRateErrDown << std::endl;
  }
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
  
TGraphAsymmErrors* compRatioGraph(const std::string& ratioGraphName, const TGraph* numerator, const TGraph* denominator)
{
  assert(numerator->GetN() == denominator->GetN());
  int nPoints = numerator->GetN();

  TGraphAsymmErrors* graphRatio = new TGraphAsymmErrors(nPoints);
  graphRatio->SetName(ratioGraphName.data());

  for ( int iPoint = 0; iPoint < nPoints; ++iPoint ){
    double x_numerator, y_numerator;
    numerator->GetPoint(iPoint, x_numerator, y_numerator);
    double xErrUp_numerator = 0.;
    double xErrDown_numerator = 0.;
    double yErrUp_numerator = 0.;
    double yErrDown_numerator = 0.;
    if ( dynamic_cast<const TGraphAsymmErrors*>(numerator) ) {
      const TGraphAsymmErrors* numerator_asymmerrors = dynamic_cast<const TGraphAsymmErrors*>(numerator);
      xErrUp_numerator = numerator_asymmerrors->GetErrorXhigh(iPoint);
      xErrDown_numerator = numerator_asymmerrors->GetErrorXlow(iPoint);
      yErrUp_numerator = numerator_asymmerrors->GetErrorYhigh(iPoint);
      yErrDown_numerator = numerator_asymmerrors->GetErrorYlow(iPoint);
    } else if ( dynamic_cast<const TGraphErrors*>(numerator) ) {
      const TGraphErrors* numerator_errors = dynamic_cast<const TGraphErrors*>(numerator);
      xErrUp_numerator = numerator_errors->GetErrorX(iPoint);
      xErrDown_numerator = xErrUp_numerator;
      yErrUp_numerator = numerator_errors->GetErrorY(iPoint);
      yErrDown_numerator = yErrUp_numerator;
    }

    double x_denominator, y_denominator;
    denominator->GetPoint(iPoint, x_denominator, y_denominator);
    assert(x_denominator == x_numerator);
    double xErrUp_denominator = 0.;
    double xErrDown_denominator = 0.;
    double yErrUp_denominator = 0.;
    double yErrDown_denominator = 0.;
    if ( dynamic_cast<const TGraphAsymmErrors*>(denominator) ) {
      const TGraphAsymmErrors* denominator_asymmerrors = dynamic_cast<const TGraphAsymmErrors*>(denominator);
      xErrUp_denominator = denominator_asymmerrors->GetErrorXhigh(iPoint);
      xErrDown_denominator = denominator_asymmerrors->GetErrorXlow(iPoint);
      yErrUp_denominator = denominator_asymmerrors->GetErrorYhigh(iPoint);
      yErrDown_denominator = denominator_asymmerrors->GetErrorYlow(iPoint);
    } else if ( dynamic_cast<const TGraphErrors*>(denominator) ) {
      const TGraphErrors* denominator_errors = dynamic_cast<const TGraphErrors*>(denominator);
      xErrUp_denominator = denominator_errors->GetErrorX(iPoint);
      xErrDown_denominator = xErrUp_denominator;
      yErrUp_denominator = denominator_errors->GetErrorY(iPoint);
      yErrDown_denominator = yErrUp_denominator;
    }

    double x_ratio = x_numerator;
    double y_ratio = ( y_denominator > 0. ) ? (y_numerator/y_denominator) : 0.;
    double xErrUp_ratio = TMath::Max(xErrUp_numerator, xErrUp_denominator);
    double xErrDown_ratio = TMath::Max(xErrDown_numerator, xErrDown_denominator);
    double yErr2Up_ratio = 0.;
    if ( y_numerator   ) yErr2Up_ratio += square(yErrUp_numerator/y_numerator);
    if ( y_denominator ) yErr2Up_ratio += square(yErrDown_denominator/y_numerator);
    double yErrUp_ratio = TMath::Sqrt(yErr2Up_ratio)*y_ratio;
    double yErr2Down_ratio = 0.;
    if ( y_numerator   ) yErr2Down_ratio += square(yErrDown_numerator/y_numerator);
    if ( y_denominator ) yErr2Down_ratio += square(yErrUp_denominator/y_numerator);
    double yErrDown_ratio = TMath::Sqrt(yErr2Down_ratio)*y_ratio;

    graphRatio->SetPoint(iPoint, x_ratio, y_ratio);
    graphRatio->SetPointError(iPoint, xErrDown_ratio, xErrUp_ratio, yErrDown_ratio, yErrUp_ratio);
  }
  
  graphRatio->SetLineColor(numerator->GetLineColor());
  graphRatio->SetLineWidth(numerator->GetLineWidth());
  graphRatio->SetMarkerColor(numerator->GetMarkerColor());
  graphRatio->SetMarkerStyle(numerator->GetMarkerStyle());
  graphRatio->SetMarkerSize(numerator->GetMarkerSize());

  return graphRatio;
}


double FileNameMatch(const vdouble& PtBins, const vdouble& EtaBins, const std::string& filename, const std::string& lepton_type, bool isNum, bool getPt, bool getMin){
  int numEtaBins  = EtaBins.size() - 1;
  int numPtBins   = PtBins.size() - 1;
  
  std::string name = "";
  for(int idxEtaBin = 0; idxEtaBin < numEtaBins; ++idxEtaBin) { // ETA LOOP
    double minAbsEta = std::abs(EtaBins[idxEtaBin]);
    double maxAbsEta = std::abs(EtaBins[idxEtaBin + 1]);                                                                                                     
    for(int idxPtBin = 0; idxPtBin < numPtBins; ++idxPtBin) { // PT LOOP                                                                                     
      double minPt = PtBins[idxPtBin];
      double maxPt = PtBins[idxPtBin + 1];                                                                                                     

      if(isNum) name = Form("fit_results_num_%s_tight_%s_%s.txt", lepton_type.data(), (getEtaBin(minAbsEta, maxAbsEta)).data(), (getPtBin(minPt, maxPt)).data());
      if(!isNum) name = Form("fit_results_den_%s_fakeable_%s_%s.txt", lepton_type.data(), (getEtaBin(minAbsEta, maxAbsEta)).data(), (getPtBin(minPt, maxPt)).data());
      
      std::cout<< "name " << name << std::endl;
      
      if(name == filename){
	//	std::cout<< "Matched eta bin " << "(" << minAbsEta << " , " << maxAbsEta  << ")" << std::endl;
	//      std::cout<< "Matched pT bin " << "(" << minPt << " , " << maxPt  << ")" << std::endl;
        if(getPt && getMin) return minPt;
	if(!getPt && getMin) return minAbsEta;
        if(getPt && !getMin) return maxPt;
	if(!getPt && !getMin) return maxAbsEta;
      }
    }
  }

  return -1.;
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

  std::cout << "<comp_LeptonFakeRate>:" << std::endl;

//--- keep track of time it takes the macro to execute
  TBenchmark clock;
  clock.Start("comp_LeptonFakeRate");

//--- read python configuration parameters
  if ( !edm::readPSetsFrom(argv[1])->existsAs<edm::ParameterSet>("process") ) 
    throw cms::Exception("comp_LeptonFakeRate") 
      << "No ParameterSet 'process' found in configuration file = " << argv[1] << " !!\n";

  edm::ParameterSet cfg = edm::readPSetsFrom(argv[1])->getParameter<edm::ParameterSet>("process");
  edm::ParameterSet cfg_comp_LeptonFakeRate = cfg.getParameter<edm::ParameterSet>("comp_LeptonFakeRate");

  edm::VParameterSet cfg_inputfiles = cfg_comp_LeptonFakeRate.getParameter<edm::VParameterSet>("inputfiles");

  vdouble EtaBins_e = cfg_comp_LeptonFakeRate.getParameter<vdouble>("absEtaBins_e");
  vdouble PtBins_e = cfg_comp_LeptonFakeRate.getParameter<vdouble>("absPtBins_e");
  vdouble EtaBins_mu = cfg_comp_LeptonFakeRate.getParameter<vdouble>("absEtaBins_mu");
  vdouble PtBins_mu = cfg_comp_LeptonFakeRate.getParameter<vdouble>("absPtBins_mu");

  fwlite::OutputFiles outputFile(cfg);
  fwlite::TFileService fs = fwlite::TFileService(outputFile.file().data());
 


  TH2F* h2d_e = new TH2F("h2d_electron", "Electron 2-dim. Histo", 20, 0., 200., 2, 0., 3.0);
  TH2F* h2d_mu = new TH2F("h2d_muon", "Muon 2-dim. Histo", 20, 0., 200., 2, 0., 3.0);




  //  float x,y;
  // double a = 0.;
  // std::vector<double> fake_rate_vec, fake_rate_err_vec;
  TString X,Y ;

  for(edm::VParameterSet::const_iterator cfgInputfile = cfg_inputfiles.begin(); 
      cfgInputfile != cfg_inputfiles.end(); cfgInputfile++){ // inputfile loop

    std::string num_file = (*cfgInputfile).getParameter<std::string>("num_file");
    std::string den_file = (*cfgInputfile).getParameter<std::string>("den_file");

    std::cout<< num_file << std::endl;
    std::cout<< den_file << std::endl;
 
    std::ifstream mynumfile;
    std::ifstream mydenfile;

    mynumfile.open(num_file);
    mydenfile.open(den_file);

    // while(!mynumfile.eof()){ mynumfile >> x >> y;}
    // std::cout<< x << " " << y << std::endl;

    X.Resize(0);
    X.ReadFile(mynumfile);
    mynumfile.close();    

    Y.Resize(0);
    Y.ReadFile(mydenfile);
    mydenfile.close();    

    TObjArray *tx = X.Tokenize(" ");
    TObjArray *ty = Y.Tokenize(" ");


    // tx->Print();
    // ty->Print();

    std::cout << " Num. Array size " << tx->GetEntries() << std::endl;
    std::cout << "Den. Array size " << ty->GetEntries() << std::endl;

    double x = 0.;
    double x_err = 0.;
    if(tx->GetEntries() == 2){
      x = (((TObjString *)(tx->At(0)))->String()).Atof();
      x_err = (((TObjString *)(tx->At(1)))->String()).Atof();
      std::cout<< "num yield " << x << " +/- " << x_err << std::endl; 
      // std::cout << (((TObjString *)(tx->At(0)))->String()).Atof()  << std::endl;
      // std::cout << (((TObjString *)(tx->At(1)))->String()).Atof()  << std::endl;
    }

    double y = 0.;
    double y_err = 0.;
    if(ty->GetEntries() == 2){ 
      y = (((TObjString *)(ty->At(0)))->String()).Atof();
      y_err = (((TObjString *)(ty->At(1)))->String()).Atof();
      std::cout<< "den. yield " << y << " +/- " << y_err << std::endl; 
      // std::cout << (((TObjString *)(ty->At(0)))->String()).Atof()  << std::endl;
      // std::cout << (((TObjString *)(ty->At(1)))->String()).Atof()  << std::endl;
    }

    double fake_rate = 0.;
    if(y != 0.){
      fake_rate = x/y;
    }else{
      fake_rate = 0.;
    }

    double fake_rate_err = 0.;
    if(y != 0. && x != 0.){
      fake_rate_err = TMath::Sqrt( TMath::Power((x_err/x), 2.) + TMath::Power((y_err/y), 2. ) ) * fake_rate;
    }else{
      fake_rate_err = 0.;
    } 


    double PtMax_e = -1.;
    double absEtaMax_e = -1.;
    PtMax_e = FileNameMatch(PtBins_e, EtaBins_e, num_file, "e", true, true, false);
    absEtaMax_e = FileNameMatch(PtBins_e, EtaBins_e, num_file, "e", true, false, false);


    if(PtMax_e != -1. && absEtaMax_e != -1.){ Fill2DHisto(h2d_e, fake_rate, fake_rate_err, PtMax_e, absEtaMax_e); }

    double PtMax_mu = -1.;
    double absEtaMax_mu = -1.;
    PtMax_mu = FileNameMatch(PtBins_mu, EtaBins_mu, num_file, "mu", true, true, false);
    absEtaMax_mu = FileNameMatch(PtBins_mu, EtaBins_mu, num_file, "mu", true, false, false);

    if(PtMax_mu != -1. && absEtaMax_mu != -1.){ Fill2DHisto(h2d_mu, fake_rate, fake_rate_err, PtMax_mu, absEtaMax_mu); }

    // fake_rate_vec.push_back(fake_rate);
    // fake_rate_err_vec.push_back(fake_rate_err);

  } // input file loop ends


    // std::cout<< "Fake rate: " << fake_rate_vec[0] << " +/- " << fake_rate_err_vec[0] << std::endl;
  
    clock.Show("comp_LeptonFakeRate");

  return 0;
}
