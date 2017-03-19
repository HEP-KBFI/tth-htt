
/** \executable makePlots_mcClosure
 *
 * Make control plots demonstrating MC closure of procedure for jet->tau fake background estimation.
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
#include "tthAnalysis/HiggsToTauTau/interface/plottingAuxFunctions.h"

#include <TFile.h>
#include <TH1.h>
#include <THStack.h>
#include <TBenchmark.h>
#include <TMath.h>
#include <TString.h>
#include <TCanvas.h>
#include <TPad.h>
#include <TLegend.h>
#include <TPaveText.h>
#include <TF1.h>
#include <TStyle.h>
#include <TROOT.h>
#include <TError.h> // gErrorAbortLevel, kError

#include <iostream>
#include <string>
#include <vector>
#include <assert.h>

typedef std::vector<std::string> vstring;

namespace
{
  struct categoryEntryType
  {
    categoryEntryType(const edm::ParameterSet& cfg)
    {
      signal_ = cfg.getParameter<std::string>("signal");
      sideband_ = cfg.getParameter<std::string>("sideband");
      label_ = cfg.getParameter<std::string>("label");
    }
    ~categoryEntryType() {}
    std::string signal_;
    std::string sideband_;
    std::string label_;
  };

  TH1* normalizeHistogram(TH1* histogram, bool includeUnderflowBin = false, bool includeOverflowBin = false)
  {
    std::string histogramName_normalized = Form("%s_normalized", histogram->GetName());
    TH1* histogram_normalized = (TH1*)histogram->Clone(histogramName_normalized.data());
    histogram_normalized->Reset();
    if ( !histogram_normalized->GetSumw2() ) histogram_normalized->Sumw2();
    double integral = 0.;
    int idxBin_first = ( includeUnderflowBin ) ? 0 : 1;
    int idxBin_last = ( includeOverflowBin ) ? histogram->GetNbinsX() + 1 : histogram->GetNbinsX();
    for ( int idxBin = idxBin_first; idxBin <= idxBin_last; ++idxBin ) {
      integral += histogram->GetBinContent(idxBin);
    }
    if ( integral > 0. ) {
      double sf = 1./integral;
      for ( int idxBin = idxBin_first; idxBin <= idxBin_last; ++idxBin ) {
	double binContent = histogram->GetBinContent(idxBin);
	double binError = histogram->GetBinError(idxBin);
	histogram_normalized->SetBinContent(idxBin, sf*binContent);
	histogram_normalized->SetBinError(idxBin, sf*binError);
      }
    }
    return histogram_normalized;
  }
  
  void makePlot_mcClosure(double canvasSizeX, double canvasSizeY,
			  TH1* histogramSignal,
			  TH1* histogramSideband,
			  TH1* histogramUncertainty,
			  double legendTextSize, double legendPosX, double legendPosY, double legendSizeX, double legendSizeY, 
			  const std::string& labelOnTop,
			  std::vector<std::string>& extraLabels, double labelTextSize,
			  double labelPosX, double labelPosY, double labelSizeX, double labelSizeY,
			  double xMin, double xMax, const std::string& xAxisTitle, double xAxisOffset,
			  bool useLogScale, double yMin, double yMax, const std::string& yAxisTitle, double yAxisOffset,
			  const std::string& outputFileName)
  {
    std::cout << "<makePlot_mcClosure>:" << std::endl;

    TH1* histogramSignal_density = divideHistogramByBinWidth(histogramSignal);      
    checkCompatibleBinning(histogramSideband, histogramSignal);
    TH1* histogramSideband_density = divideHistogramByBinWidth(histogramSideband);

    TH1* histogramUncertainty_density = 0;
    if ( histogramUncertainty ) {
      checkCompatibleBinning(histogramUncertainty, histogramSignal);
      histogramUncertainty_density = divideHistogramByBinWidth(histogramUncertainty);
    }

    TCanvas* canvas = new TCanvas("canvas", "", canvasSizeX, canvasSizeY);
    canvas->SetFillColor(10);
    canvas->SetFillStyle(4000);
    canvas->SetFillColor(10);
    canvas->SetTicky();
    canvas->SetBorderSize(2);
    canvas->SetLeftMargin(0.12);
    canvas->SetBottomMargin(0.12);

    TPad* topPad = new TPad("topPad", "topPad", 0.00, 0.35, 1.00, 1.00);
    topPad->SetFillColor(10);
    topPad->SetTopMargin(0.055);
    topPad->SetLeftMargin(0.15);
    topPad->SetBottomMargin(0.03);
    topPad->SetRightMargin(0.05);
    topPad->SetLogy(useLogScale);

    TPad* bottomPad = new TPad("bottomPad", "bottomPad", 0.00, 0.00, 1.00, 0.35);
    bottomPad->SetFillColor(10);
    bottomPad->SetTopMargin(0.02);
    bottomPad->SetLeftMargin(0.15);
    bottomPad->SetBottomMargin(0.31);
    bottomPad->SetRightMargin(0.05);
    bottomPad->SetLogy(false);

    canvas->cd();
    topPad->Draw();
    topPad->cd();

    TAxis* xAxis_top = histogramSignal_density->GetXaxis();
    if ( xMin >= 0. && xMax > xMin ) xAxis_top->SetRangeUser(xMin, xMax);
    xAxis_top->SetTitle(xAxisTitle.data());
    xAxis_top->SetTitleOffset(xAxisOffset);
    xAxis_top->SetLabelColor(10);
    xAxis_top->SetTitleColor(10);
    
    TAxis* yAxis_top = histogramSignal_density->GetYaxis();
    yAxis_top->SetTitle(yAxisTitle.data());
    yAxis_top->SetTitleOffset(yAxisOffset);
    yAxis_top->SetTitleSize(0.065);
    yAxis_top->SetLabelSize(0.05);
    yAxis_top->SetTickLength(0.04);  

    TLegend* legend = new TLegend(legendPosX, legendPosY, legendPosX + legendSizeX, legendPosY + legendSizeY, NULL, "brNDC");
    legend->SetFillStyle(0);
    legend->SetBorderSize(0);
    legend->SetFillColor(10);
    legend->SetTextSize(legendTextSize);

    if ( !(yMin >= 0. && yMax > yMin) ) {
      if ( useLogScale ) {
	const double numOrdersOfMagnitude = 4.5;
	yMax = compYmaxForClearance(histogramSignal_density, legendPosX, legendPosY, labelPosY, true, numOrdersOfMagnitude);
	yMax = TMath::Max(yMax, compYmaxForClearance(histogramSideband_density, legendPosX, legendPosY, labelPosY, true, numOrdersOfMagnitude));
	yMin = TMath::Power(10., -numOrdersOfMagnitude)*TMath::Max(1., yMax);
      } else {
	yMax = compYmaxForClearance(histogramSignal_density, legendPosX, legendPosY, labelPosY, false, -1.);
	yMax = TMath::Max(yMax, compYmaxForClearance(histogramSideband_density, legendPosX, legendPosY, labelPosY, false, -1.));
	yMin = 0.;
      }
    }
    std::cout << "yMin = " << yMin << ", yMax = " << yMax << std::endl;

    histogramSignal_density->SetTitle("");
    histogramSignal_density->SetStats(false);
    histogramSignal_density->SetMaximum(yMax);
    histogramSignal_density->SetMinimum(yMin);
    histogramSignal_density->SetMarkerStyle(20);
    histogramSignal_density->SetMarkerSize(2);
    histogramSignal_density->SetMarkerColor(kBlack);
    histogramSignal_density->SetLineColor(kBlack);
    legend->AddEntry(histogramSignal_density, "Simulation", "p");
    histogramSignal_density->Draw("ep");
        
    histogramSideband_density->SetFillColor(1);
    histogramSideband_density->SetFillStyle(3005); // stripes extending from top left to bottom right
    histogramSideband_density->SetLineColor(1);
    legend->AddEntry(histogramSideband_density, "Prediction", "f");
    histogramSideband_density->Draw("histsame");
        
    if ( histogramUncertainty_density ) {
      int numBins_top = histogramUncertainty_density->GetNbinsX();
      for ( int iBin = 1; iBin <= numBins_top; ++iBin ) {
	double binContent = histogramSideband_density->GetBinContent(iBin);
	histogramUncertainty_density->SetBinContent(iBin, binContent);
      }
      histogramUncertainty_density->SetFillColor(kBlack);
      histogramUncertainty_density->SetFillStyle(3344);    
      histogramUncertainty_density->Draw("e2same");
      legend->AddEntry(histogramUncertainty_density, "Uncertainty", "f");
    }
    
    histogramSignal_density->Draw("epsame");
    histogramSignal_density->Draw("axissame");
    
    legend->Draw();

    TPaveText* labelOnTop_pave = 0;
    if ( labelOnTop != "" ) {
      labelOnTop_pave = new TPaveText(0.165, 0.95, 0.61, 1.00, "brNDC");
      labelOnTop_pave->AddText(labelOnTop.data());
      labelOnTop_pave->SetFillColor(10);
      labelOnTop_pave->SetBorderSize(0);
      labelOnTop_pave->SetTextColor(1);
      labelOnTop_pave->SetTextAlign(12);
      labelOnTop_pave->SetTextSize(0.045);
      labelOnTop_pave->Draw();
    }
    TPaveText* extraLabels_pave = 0;
    if ( extraLabels.size() > 0 ) {
      extraLabels_pave = new TPaveText(labelPosX, labelPosY, labelPosX + labelSizeX, labelPosY + labelSizeY, "brNDC");
      for ( std::vector<std::string>::const_iterator extraLabel = extraLabels.begin();
	    extraLabel != extraLabels.end(); ++extraLabel ) {
	extraLabels_pave->AddText(extraLabel->data());
      }
      extraLabels_pave->SetFillColor(10);
      extraLabels_pave->SetBorderSize(0);
      extraLabels_pave->SetTextColor(1);
      extraLabels_pave->SetTextAlign(12);
      extraLabels_pave->SetTextSize(labelTextSize);
      extraLabels_pave->Draw();
    }

    TH1* histogram_test = ( histogramUncertainty ) ? histogramUncertainty : histogramSideband;
    assert(histogram_test);
    double pChi2 = histogramSignal->Chi2Test(histogram_test);
    double pKS = histogramSignal->KolmogorovTest(histogram_test);

    TPaveText* label_pChi2 = new TPaveText(0.21, 0.83, 0.46, 0.90, "brNDC");
    label_pChi2->AddText(Form("%1.3f", pChi2));
    label_pChi2->SetFillColor(10);
    label_pChi2->SetBorderSize(0);
    label_pChi2->SetTextColor(1);
    label_pChi2->SetTextAlign(12);
    label_pChi2->SetTextSize(0.050);
    label_pChi2->Draw();

    TPaveText* label_pKS = new TPaveText(0.56, 0.83, 0.81, 0.90, "brNDC");
    label_pKS->AddText(Form("%1.3f", pKS));
    label_pKS->SetFillColor(10);
    label_pKS->SetBorderSize(0);
    label_pKS->SetTextColor(1);
    label_pKS->SetTextAlign(12);
    label_pKS->SetTextSize(0.050);
    label_pKS->Draw();

    canvas->cd();
    bottomPad->Draw();
    bottomPad->cd();

    TH1* histogramRatio = (TH1*)histogramSignal->Clone("histogramRatio");
    histogramRatio->Reset();
    if ( !histogramRatio->GetSumw2N() ) histogramRatio->Sumw2();
    histogramRatio->Divide(histogramSignal, histogramSideband);
    int numBins_bottom = histogramRatio->GetNbinsX();
    for ( int iBin = 1; iBin <= numBins_bottom; ++iBin ) {
      double binContent = histogramRatio->GetBinContent(iBin);
      if ( histogramSignal->GetBinContent(iBin) >= 0. ) histogramRatio->SetBinContent(iBin, binContent - 1.0);
      else histogramSignal->SetBinContent(iBin, -10.);
      //std::cout << " bin #" << iBin << " (x = " << histogramRatio->GetBinCenter(iBin) << "): ratio = " << histogramRatio->GetBinContent(iBin) << std::endl;
    }

    histogramRatio->SetTitle("");
    histogramRatio->SetStats(false);
    histogramRatio->SetMinimum(-0.50);
    histogramRatio->SetMaximum(+0.50);
    histogramRatio->SetMarkerStyle(histogramSignal_density->GetMarkerStyle());
    histogramRatio->SetMarkerSize(histogramSignal_density->GetMarkerSize());
    histogramRatio->SetMarkerColor(histogramSignal_density->GetMarkerColor());
    histogramRatio->SetLineColor(histogramSignal_density->GetLineColor());

    TAxis* xAxis_bottom = histogramRatio->GetXaxis();
    if ( xMin >= 0. && xMax > xMin ) xAxis_bottom->SetRangeUser(xMin, xMax);
    xAxis_bottom->SetTitle(xAxis_top->GetTitle());
    xAxis_bottom->SetLabelColor(1);
    xAxis_bottom->SetTitleColor(1);
    xAxis_bottom->SetTitleOffset(1.20);
    xAxis_bottom->SetTitleSize(0.12);
    xAxis_bottom->SetLabelOffset(0.02);
    xAxis_bottom->SetLabelSize(0.10);
    xAxis_bottom->SetTickLength(0.055);
    
    TAxis* yAxis_bottom = histogramRatio->GetYaxis();
    yAxis_bottom->SetTitle("#frac{Simulation - Prediction}{Prediction}");
    yAxis_bottom->SetTitleOffset(0.80);
    yAxis_bottom->SetNdivisions(505);
    yAxis_bottom->CenterTitle();
    yAxis_bottom->SetTitleSize(0.09);
    yAxis_bottom->SetLabelSize(0.10);
    yAxis_bottom->SetTickLength(0.04);  

    TH1* histogramRatioUncertainty = 0;
    if ( histogramUncertainty ) {
      histogramRatioUncertainty = (TH1*)histogramUncertainty->Clone("histogramRatioUncertainty");
      if ( !histogramRatioUncertainty->GetSumw2N() ) histogramRatioUncertainty->Sumw2();
      histogramRatioUncertainty->Divide(histogramSideband);
      int numBins = histogramRatioUncertainty->GetNbinsX();
      for ( int iBin = 1; iBin <= numBins; ++iBin ) {
	double binContent = histogramRatioUncertainty->GetBinContent(iBin);
	histogramRatioUncertainty->SetBinContent(iBin, binContent - 1.0);
      }
      histogramRatioUncertainty->SetFillColor(histogramUncertainty_density->GetFillColor());
      //histogramRatioUncertainty->SetFillStyle(histogramUncertainty_density->GetFillStyle());    
      histogramRatioUncertainty->SetFillStyle(3644);    
    }
    histogramRatio->Draw("ep");

    TF1* line = new TF1("line","0", xAxis_bottom->GetXmin(), xAxis_bottom->GetXmax());
    line->SetLineStyle(3);
    line->SetLineWidth(1.5);
    line->SetLineColor(kBlack);
    line->Draw("same");
    
    if ( histogramRatioUncertainty ) {
      //printHistogram(histogramRatioUncertainty);
      histogramRatioUncertainty->Draw("e2same");
    }
      
    histogramRatio->Draw("epsame");
    
    canvas->Update();
    size_t idx = outputFileName.find(".");
    std::string outputFileName_plot(outputFileName, 0, idx);
    if ( useLogScale ) outputFileName_plot.append("_log");
    else outputFileName_plot.append("_linear");
    if ( idx != std::string::npos ) canvas->Print(std::string(outputFileName_plot).append(std::string(outputFileName, idx)).data());
    canvas->Print(std::string(outputFileName_plot).append(".png").data());
    canvas->Print(std::string(outputFileName_plot).append(".pdf").data());
    canvas->Print(std::string(outputFileName_plot).append(".root").data());

    delete histogramSignal_density;
    delete histogramSideband_density;
    delete histogramUncertainty_density;
    delete legend;
    delete labelOnTop_pave;
    delete extraLabels_pave;
    delete label_pChi2;
    delete label_pKS;
    delete topPad;
    delete histogramRatio;
    delete histogramRatioUncertainty;
    delete line;
    delete bottomPad;    
    delete canvas;
  }
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

  std::cout << "<makePlots_mcClosure>:" << std::endl;

  gROOT->SetBatch(true);

//--- keep track of time it takes the macro to execute
  TBenchmark clock;
  clock.Start("makePlots_mcClosure");

//--- read python configuration parameters
  if ( !edm::readPSetsFrom(argv[1])->existsAs<edm::ParameterSet>("process") ) 
    throw cms::Exception("makePlots_mcClosure") 
      << "No ParameterSet 'process' found in configuration file = " << argv[1] << " !!\n";

  edm::ParameterSet cfg = edm::readPSetsFrom(argv[1])->getParameter<edm::ParameterSet>("process");

  edm::ParameterSet cfgMakePlots = cfg.getParameter<edm::ParameterSet>("makePlots_mcClosure");

  std::vector<categoryEntryType*> categories;
  vstring categoryNames_sideband;
  edm::VParameterSet cfgCategories = cfgMakePlots.getParameter<edm::VParameterSet>("categories");
  for ( edm::VParameterSet::const_iterator cfgCategory = cfgCategories.begin();
	cfgCategory != cfgCategories.end(); ++cfgCategory ) {
    categoryEntryType* category = new categoryEntryType(*cfgCategory);
    categories.push_back(category);
    categoryNames_sideband.push_back(category->sideband_);
  }

  std::string process_signal  = cfgMakePlots.getParameter<std::string>("process_signal");
  std::string process_sideband = cfgMakePlots.getParameter<std::string>("process_sideband");

  edm::VParameterSet cfgDistributions = cfgMakePlots.getParameter<edm::VParameterSet>("distributions");
  std::vector<plotEntryType*> distributions = readDistributions(cfgDistributions);
  for ( std::vector<plotEntryType*>::iterator distribution = distributions.begin();
	distribution != distributions.end(); ++distribution ) {
    (*distribution)->legendSizeY_ = 0.17;
  }

  edm::ParameterSet cfgNuisanceParameters = cfgMakePlots.getParameter<edm::ParameterSet>("nuisanceParameters");
  HistogramManager histogramManager({}, process_sideband, categoryNames_sideband, cfgNuisanceParameters);
  bool showUncertainty = cfgMakePlots.getParameter<bool>("showUncertainty");

  std::string labelOnTop_string = cfgMakePlots.getParameter<std::string>("labelOnTop");
  double intLumiData = cfgMakePlots.getParameter<double>("intLumiData");
  std::string labelOnTop = Form(labelOnTop_string.data(), intLumiData);
  
  std::string outputFileName = cfgMakePlots.getParameter<std::string>("outputFileName");

  fwlite::InputSource inputFiles(cfg); 
  if ( !(inputFiles.files().size() == 1) )
    throw cms::Exception("makePlots") 
      << "Exactly one input file expected !!\n";
  TFile* inputFile = new TFile(inputFiles.files().front().data());
  
  for ( std::vector<categoryEntryType*>::iterator category = categories.begin();
	category != categories.end(); ++category ) {
    std::cout << "processing category: signal = " << (*category)->signal_ << ", sideband = " << (*category)->sideband_ << std::endl;

    TDirectory* dir_signal = getDirectory(inputFile, (*category)->signal_, true);
    assert(dir_signal);
    TDirectory* dir_sideband = getDirectory(inputFile, (*category)->sideband_, true);
    assert(dir_sideband);

    for ( std::vector<plotEntryType*>::iterator distribution = distributions.begin();
	  distribution != distributions.end(); ++distribution ) {

      TH1* histogramSignal = getHistogram_wrapper(dir_signal, process_signal, (*distribution)->histogramName_, "central", true);

      histogramManager.setDirectory(dir_sideband);
      histogramManager.setCategory((*category)->sideband_);
      histogramManager.setHistogram((*distribution)->histogramName_);
      histogramManager.update();
      
      TH1* histogramSideband = histogramManager.getHistogramPrefit(process_sideband, true);
      
      TH1* histogramUncertainty = 0;
      if ( showUncertainty ) {
	histogramUncertainty = histogramManager.getHistogramUncertainty();
      }
            
      vstring extraLabels;
      if ( (*category)->label_ != "" ) extraLabels.push_back((*category)->label_);
      double extraLabelsSizeX = 0.12;

      size_t idx = outputFileName.find(".");
      std::string outputFileName_plot(outputFileName, 0, idx);
      outputFileName_plot.append(Form("_%s", (*distribution)->outputFileName_.data()));
      if ( idx != std::string::npos ) outputFileName_plot.append(std::string(outputFileName, idx));
	  
      makePlot_mcClosure(
	800, 900,
	histogramSignal,
	histogramSideband,
	histogramUncertainty,
	(*distribution)->legendTextSize_, (*distribution)->legendPosX_, (*distribution)->legendPosY_, (*distribution)->legendSizeX_, (*distribution)->legendSizeY_, 
	labelOnTop,
	extraLabels, 0.055, 0.185, 0.815 - 0.055*extraLabels.size(), extraLabelsSizeX, 0.055*extraLabels.size(),
	(*distribution)->xMin_, (*distribution)->xMax_, (*distribution)->xAxisTitle_, (*distribution)->xAxisOffset_, 
	true, (*distribution)->yMin_, (*distribution)->yMax_, (*distribution)->yAxisTitle_, (*distribution)->yAxisOffset_, 
	outputFileName_plot);
      makePlot_mcClosure(
	800, 900,
	histogramSignal,
	histogramSideband,
	histogramUncertainty,
	(*distribution)->legendTextSize_, (*distribution)->legendPosX_, (*distribution)->legendPosY_, (*distribution)->legendSizeX_, (*distribution)->legendSizeY_, 
	labelOnTop,
	extraLabels, 0.055, 0.185, 0.815 - 0.055*extraLabels.size(), extraLabelsSizeX, 0.055*extraLabels.size(),
	(*distribution)->xMin_, (*distribution)->xMax_, (*distribution)->xAxisTitle_, (*distribution)->xAxisOffset_, 
	false, (*distribution)->yMin_, (*distribution)->yMax_, (*distribution)->yAxisTitle_, (*distribution)->yAxisOffset_, 
	outputFileName_plot);

      TH1* histogramSignal_normalized = normalizeHistogram(histogramSignal);
      TH1* histogramSideband_normalized = normalizeHistogram(histogramSideband);
      TH1* histogramUncertainty_normalized = normalizeHistogram(histogramUncertainty);
      
      TString outputFileName_plot_normalized = outputFileName_plot.data();
      outputFileName_plot_normalized = outputFileName_plot_normalized.ReplaceAll((*distribution)->outputFileName_.data(), Form("%s_normalized", (*distribution)->outputFileName_.data()));
            
      makePlot_mcClosure(
	800, 900,
	histogramSignal_normalized,
	histogramSideband_normalized,
	histogramUncertainty_normalized,
	(*distribution)->legendTextSize_, (*distribution)->legendPosX_, (*distribution)->legendPosY_, (*distribution)->legendSizeX_, (*distribution)->legendSizeY_, 
	labelOnTop,
	extraLabels, 0.055, 0.185, 0.915 - 0.055*extraLabels.size(), extraLabelsSizeX, 0.055*extraLabels.size(),
	(*distribution)->xMin_, (*distribution)->xMax_, (*distribution)->xAxisTitle_, (*distribution)->xAxisOffset_, 
	true, (*distribution)->yMin_, (*distribution)->yMax_, (*distribution)->yAxisTitle_, (*distribution)->yAxisOffset_, 
	outputFileName_plot_normalized.Data());
      makePlot_mcClosure(
	800, 900,
	histogramSignal_normalized,
	histogramSideband_normalized,
	histogramUncertainty_normalized,
	(*distribution)->legendTextSize_, (*distribution)->legendPosX_, (*distribution)->legendPosY_, (*distribution)->legendSizeX_, (*distribution)->legendSizeY_, 
	labelOnTop,
	extraLabels, 0.055, 0.185, 0.915 - 0.055*extraLabels.size(), extraLabelsSizeX, 0.055*extraLabels.size(),
	(*distribution)->xMin_, (*distribution)->xMax_, (*distribution)->xAxisTitle_, (*distribution)->xAxisOffset_, 
	false, (*distribution)->yMin_, (*distribution)->yMax_, (*distribution)->yAxisTitle_, (*distribution)->yAxisOffset_, 
	outputFileName_plot_normalized.Data());
      
      delete histogramSignal_normalized;
      delete histogramSideband_normalized;
      delete histogramUncertainty_normalized;
    }
  }

  delete inputFile;
  
  for ( std::vector<categoryEntryType*>::iterator it = categories.begin();
	it != categories.end(); ++it ) {
    delete (*it);
  }
  for ( std::vector<plotEntryType*>::iterator it = distributions.begin();
	it != distributions.end(); ++it ) {
    delete (*it);
  }

  clock.Show("makePlots_mcClosure");

  return 0;
}

