
#include <TFile.h>
#include <TString.h>
#include <TH1.h>
#include <TH2.h>
#include <TGraph.h>
#include <TGraphAsymmErrors.h>
#include <TAxis.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TMath.h>
#include <TROOT.h>
#include <TStyle.h>
#include <TSystem.h>

#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <iomanip>
#include <assert.h>

enum { kTHQ, kTHW };
enum { kScale, kUnscale };

TH1* loadHistogram(TFile* inputFile, const std::string& directory, const std::string& histogramName)
{
  TString histogramName_full;
  if ( directory != "" ) {
    histogramName_full.Append(directory.data());
    if ( !histogramName_full.EndsWith("/") ) histogramName_full.Append("/");
  }
  histogramName_full.Append(histogramName.data());
  std::cout << "loading histogram = '" << histogramName_full.Data() << "' from file = '" << inputFile->GetName() << "'" << std::endl;
  TH1* histogram = dynamic_cast<TH1*>(inputFile->Get(histogramName_full.Data()));
  std::cout << "histogram = " << histogram << std::endl;
  if ( !histogram ) {
    std::cerr << "Failed to load histogram = " << histogramName_full.Data() << " from file = " << inputFile->GetName() << " --> skipping !!" << std::endl;
    return 0;
  }
  if ( !histogram->GetSumw2N() ) histogram->Sumw2();
  return histogram;
}

TH1* scaleHistogram(TH1* histogram, double kappa_t, double kappa_V, int process, int mode)
{
  // scale computed histogram to SM cross section, as reference histograms for tHq and tHW signals
  // for all values of kappa_t and kappa_V are normalized to SM cross section !!
  //
  // note: equations for the tHq and tHW cross sections taken from Eqs. (8) and (9) in CMS-AN-2019/111
  //
  double crossSection = 0.;
  if ( process == kTHQ ) {
    crossSection = 2.63*kappa_t*kappa_t + 3.58*kappa_V*kappa_V - 5.21*kappa_t*kappa_V;
  } else if ( process == kTHW ) {
    crossSection = 2.91*kappa_t*kappa_t + 2.31*kappa_V*kappa_V - 4.22*kappa_t*kappa_V;
  } else assert(0);
  assert(crossSection > 0.);

  std::string histogramName_scaled;
  double sf = 0.;
  if ( mode == kScale ) {
    histogramName_scaled = Form("%s_scaled", histogram->GetName());
    sf = crossSection;
  } else if ( mode == kUnscale ) {
    histogramName_scaled = Form("%s_unscaled", histogram->GetName());
    sf = 1./crossSection;
  } else assert(0);

  TH1* histogram_scaled = (TH1*)histogram->Clone(histogramName_scaled.data());
  histogram_scaled->Reset();
  if ( !histogram_scaled->GetSumw2N() ) histogram_scaled->Sumw2();

  int numBins = histogram->GetNbinsX();
  for ( int idxBin = 0; idxBin <= (numBins + 1); ++idxBin ) {
    double binContent = histogram->GetBinContent(idxBin);
    double binError = histogram->GetBinError(idxBin);
    histogram_scaled->SetBinContent(idxBin, sf*binContent);
    histogram_scaled->SetBinError(idxBin, sf*binError);
  }

  return histogram_scaled;
}

TH1* computeHistogram(const TH1* histogram_1p0_1p0, const TH1* histogram_0p0_1p0, const TH1* histogram_2p0_1p0, const std::string& histogramName_computed, double kappa_t, double kappa_V, int process)
{
  int numBins = histogram_1p0_1p0->GetNbinsX();
  assert(histogram_1p0_1p0->GetNbinsX() == numBins);
  assert(histogram_2p0_1p0->GetNbinsX() == numBins);
  assert(histogram_0p0_1p0->GetNbinsX() == numBins);
  TH1* histogram_computed = (TH1*)histogram_1p0_1p0->Clone(histogramName_computed.data());
  histogram_computed->Reset();
  if ( !histogram_computed->GetSumw2N() ) histogram_computed->Sumw2();
  for ( int idxBin = 0; idxBin <= (numBins + 1); ++idxBin ) {
    double binContent_1p0_1p0 = histogram_1p0_1p0->GetBinContent(idxBin); 
    double binError_1p0_1p0 = histogram_1p0_1p0->GetBinError(idxBin);

    double binContent_0p0_1p0 = histogram_0p0_1p0->GetBinContent(idxBin); 
    double binError_0p0_1p0 = histogram_0p0_1p0->GetBinError(idxBin);

    double binContent_2p0_1p0 = histogram_2p0_1p0->GetBinContent(idxBin); 
    double binError_2p0_1p0 = histogram_2p0_1p0->GetBinError(idxBin);

    double binContent_computed = 
       kappa_t*kappa_t*0.5*(binContent_2p0_1p0 - 2.*binContent_1p0_1p0 +    binContent_0p0_1p0)
     + kappa_V*kappa_V*binContent_0p0_1p0
     - kappa_t*kappa_V*0.5*(binContent_2p0_1p0 - 4.*binContent_1p0_1p0 + 3.*binContent_0p0_1p0); 
    double binError_computed = 
       kappa_t*kappa_t*0.5*(binError_2p0_1p0   - 2.*binError_1p0_1p0   +    binError_0p0_1p0)
     + kappa_V*kappa_V*binError_0p0_1p0
     - kappa_t*kappa_V*0.5*(binError_2p0_1p0   - 4.*binError_1p0_1p0   + 3.*binError_0p0_1p0);
    histogram_computed->SetBinContent(idxBin, binContent_computed); 
    histogram_computed->SetBinError(idxBin, binError_computed); 
  }
  return histogram_computed;
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

TGraphAsymmErrors* convertToGraph(const TH1* histogram, double offsetX = 0.15)
{
  int numPoints = histogram->GetNbinsX();
  TGraphAsymmErrors* graph = new TGraphAsymmErrors(numPoints);
  for ( int idxPoint = 0; idxPoint < numPoints; ++idxPoint ) {
    double idxBin = idxPoint + 1;
    double binCenter = histogram->GetBinCenter(idxBin);
    double binWidth = histogram->GetBinWidth(idxBin);
    assert(binWidth > offsetX);
    double binContent = histogram->GetBinContent(idxBin);
    double binError = histogram->GetBinError(idxBin);
    graph->SetPoint(idxPoint, binCenter + offsetX, binContent);
    graph->SetPointError(idxPoint, 0.5*binWidth + offsetX, 0.5*binWidth - offsetX, binError, binError);
  }
  graph->SetLineColor(histogram->GetLineColor());
  graph->SetLineWidth(histogram->GetLineWidth());
  graph->SetMarkerColor(histogram->GetMarkerColor());
  graph->SetMarkerStyle(histogram->GetMarkerStyle());
  graph->SetMarkerSize(histogram->GetMarkerSize());
  return graph;
}

void showHistograms(double canvasSizeX, double canvasSizeY,
		    TH1* histogram_ref, const std::string& legendEntry_ref,
		    TH1* histogram_computed, const std::string& legendEntry_computed,
		    const std::string& xAxisTitle, double xAxisOffset,
		    bool useLogScale, double yMin, double yMax, const std::string& yAxisTitle, double yAxisOffset,
		    double legendX0, double legendY0, 
		    const std::string& outputFileName)
{
  assert(histogram_ref && histogram_computed);

  TCanvas* canvas = new TCanvas("canvas", "canvas", canvasSizeX, canvasSizeY);
  canvas->SetFillColor(10);
  canvas->SetBorderSize(2);
  canvas->SetLeftMargin(0.12);
  canvas->SetBottomMargin(0.12);

  TPad* topPad = new TPad("topPad", "topPad", 0.00, 0.35, 1.00, 1.00);
  topPad->SetFillColor(10);
  topPad->SetTopMargin(0.04);
  topPad->SetLeftMargin(0.15);
  topPad->SetBottomMargin(0.03);
  topPad->SetRightMargin(0.05);
  topPad->SetLogy(useLogScale);

  TPad* bottomPad = new TPad("bottomPad", "bottomPad", 0.00, 0.00, 1.00, 0.35);
  bottomPad->SetFillColor(10);
  bottomPad->SetTopMargin(0.02);
  bottomPad->SetLeftMargin(0.15);
  bottomPad->SetBottomMargin(0.24);
  bottomPad->SetRightMargin(0.05);
  bottomPad->SetLogy(false);

  canvas->cd();
  topPad->Draw();
  topPad->cd();

  int colors[6] = { kBlack, kGreen - 6, kBlue - 7,  kMagenta - 7, kCyan - 6, kRed - 6 };
  int markerStyles[6] = { 24, 21, 20, 21, 22, 23 };
  int markerSizes[6] = { 2, 2, 2, 2, 2, 2 };

  TLegend* legend = new TLegend(legendX0, legendY0, legendX0 + 0.25, legendY0 + 0.15, "", "brNDC"); 
  legend->SetBorderSize(0);
  legend->SetFillColor(0);

  histogram_ref->SetTitle("");
  histogram_ref->SetStats(false);
  histogram_ref->SetMinimum(yMin);
  histogram_ref->SetMaximum(yMax);
  histogram_ref->SetLineColor(colors[0]);
  histogram_ref->SetLineWidth(2);
  histogram_ref->SetMarkerColor(colors[0]);
  histogram_ref->SetMarkerStyle(markerStyles[0]);
  histogram_ref->SetMarkerSize(markerSizes[0]);
  histogram_ref->Draw("e1p");
  legend->AddEntry(histogram_ref, legendEntry_ref.data(), "p");

  TAxis* xAxis_top = histogram_ref->GetXaxis();
  xAxis_top->SetTitle(xAxisTitle.data());
  xAxis_top->SetTitleOffset(xAxisOffset);
  xAxis_top->SetLabelColor(10);
  xAxis_top->SetTitleColor(10);

  TAxis* yAxis_top = histogram_ref->GetYaxis();
  yAxis_top->SetTitle(yAxisTitle.data());
  yAxis_top->SetTitleOffset(yAxisOffset);

  histogram_computed->SetLineColor(colors[1]);
  histogram_computed->SetLineWidth(2);
  histogram_computed->SetMarkerColor(colors[1]);
  histogram_computed->SetMarkerStyle(markerStyles[1]);
  histogram_computed->SetMarkerSize(markerSizes[1]);
  //histogram_computed->Draw("e1psame");
  TGraphAsymmErrors* graph_computed = convertToGraph(histogram_computed);
  graph_computed->Draw("P");
  legend->AddEntry(histogram_computed, legendEntry_computed.data(), "p");

  legend->Draw();

  canvas->cd();
  bottomPad->Draw();
  bottomPad->cd();

  std::string histogramName_computed_div_ref = std::string(histogram_computed->GetName()).append("_div_").append(histogram_ref->GetName());
  TH1* histogram_computed_div_ref = compRatioHistogram(histogramName_computed_div_ref, histogram_computed, histogram_ref);
  histogram_computed_div_ref->SetTitle("");
  histogram_computed_div_ref->SetStats(false);
  histogram_computed_div_ref->SetMinimum(-0.50);
  histogram_computed_div_ref->SetMaximum(+0.50);
  
  TAxis* xAxis_bottom = histogram_computed_div_ref->GetXaxis();
  xAxis_bottom->SetTitle(xAxis_top->GetTitle());
  xAxis_bottom->SetLabelColor(1);
  xAxis_bottom->SetTitleColor(1);
  xAxis_bottom->SetTitleOffset(1.20);
  xAxis_bottom->SetTitleSize(0.08);
  xAxis_bottom->SetLabelOffset(0.02);
  xAxis_bottom->SetLabelSize(0.08);
  xAxis_bottom->SetTickLength(0.055);
      
  TAxis* yAxis_bottom = histogram_computed_div_ref->GetYaxis();
  yAxis_bottom->SetTitle(Form("#frac{%s - %s}{%s}", legendEntry_computed.data(), legendEntry_ref.data(), legendEntry_ref.data()));
  yAxis_bottom->SetTitleOffset(0.85);
  yAxis_bottom->SetNdivisions(505);
  yAxis_bottom->CenterTitle();
  yAxis_bottom->SetTitleSize(0.08);
  yAxis_bottom->SetLabelSize(0.08);
  yAxis_bottom->SetTickLength(0.04);  
  
  histogram_computed_div_ref->Draw("e1p");

  TGraph* graph_line = new TGraph(2);
  graph_line->SetPoint(0, xAxis_top->GetXmin(), 0.);
  graph_line->SetPoint(1, xAxis_top->GetXmax(), 0.);
  graph_line->SetLineColor(8);
  graph_line->SetLineWidth(1);
  graph_line->Draw("L");

  histogram_computed_div_ref->Draw("e1psame");
  
  canvas->Update();
  size_t idx = outputFileName.find_last_of('.');
  std::string outputFileName_plot = std::string(outputFileName, 0, idx);
  if ( useLogScale ) outputFileName_plot.append("_log");
  else outputFileName_plot.append("_linear");
  if ( idx != std::string::npos ) canvas->Print(std::string(outputFileName_plot).append(std::string(outputFileName, idx)).data());
  canvas->Print(std::string(outputFileName_plot).append(".png").data());
  //canvas->Print(std::string(outputFileName_plot).append(".pdf").data());
  //canvas->Print(std::string(outputFileName_plot).append(".root").data());
  
  delete legend;
  delete graph_computed;
  delete histogram_computed_div_ref;
  delete topPad;
  delete bottomPad;
  delete canvas;  
}

void computeShapes4tH()
{
  gROOT->SetBatch(true);

  TH1::AddDirectory(false);

  std::string inputFilePath = "/home/acaan/ttHAnalysis/2017/3l_0tau_central_tauMVA_cards_2019Aug21/datacards/3l/prepareDatacards/";
  std::string inputFileName = "prepareDatacards_3l_OS_mvaDiscr_3l.root";
  TString inputFileName_full = inputFilePath.data();
  if ( !inputFileName_full.EndsWith("/") ) inputFileName_full.Append("/");
  inputFileName_full.Append(inputFileName.data());
  TFile* inputFile = new TFile(inputFileName_full.Data());
  if ( !inputFile ) {
    std::cerr << "Failed to open input file = '" << inputFileName_full.Data() << "' !!" << std::endl;
    assert(0);
  }

  const std::string xAxisTitle = "D_{mva}";
  const std::string yAxisTitle = "dN/dD_{mva}";
  
  //-------------------------------------------------------------------------------------------------
  // Define histograms
  //
  // naming convention: first number refers to kappa_t, second number refers to kappa_V
  //-------------------------------------------------------------------------------------------------

  //-------------------------------------------------------------------------------------------------
  // t-channel tH production, with decay H->tautau
  //
  // histograms used as "basis" histograms
  std::string histogramName_tHq_htt_1p0_1p0              = "tHq_htt";
  TH1*        histogram_tHq_htt_1p0_1p0                  = loadHistogram(inputFile, "", histogramName_tHq_htt_1p0_1p0);
  std::string histogramName_tHq_htt_0p0_1p0              = "tHq_kt_0_kv_1_htt";
  TH1*        histogram_tHq_htt_0p0_1p0                  = loadHistogram(inputFile, "", histogramName_tHq_htt_0p0_1p0);
  std::string histogramName_tHq_htt_2p0_1p0              = "tHq_kt_2_kv_1_htt";
  TH1*        histogram_tHq_htt_2p0_1p0                  = loadHistogram(inputFile, "", histogramName_tHq_htt_2p0_1p0);

  // histograms used as reference for testing
  std::string histogramName_tHq_htt_m2p0_1p0             = "tHq_kt_m2_kv_1_htt";
  TH1*        histogram_tHq_htt_m2p0_1p0                 = loadHistogram(inputFile, "", histogramName_tHq_htt_m2p0_1p0);
  std::string histogramName_tHq_htt_m1p0_1p0             = "tHq_kt_m1_kv_1_htt";
  TH1*        histogram_tHq_htt_m1p0_1p0                 = loadHistogram(inputFile, "", histogramName_tHq_htt_m1p0_1p0);
  std::string histogramName_tHq_htt_0p5_1p0              = "tHq_kt_0p5_kv_1_htt";
  TH1*        histogram_tHq_htt_0p5_1p0                  = loadHistogram(inputFile, "", histogramName_tHq_htt_0p5_1p0);
  std::string histogramName_tHq_htt_3p0_1p0              = "tHq_kt_3_kv_1_htt";
  TH1*        histogram_tHq_htt_3p0_1p0                  = loadHistogram(inputFile, "", histogramName_tHq_htt_3p0_1p0);

  // Scale reference histograms to proper cross section.
  // This step is neccessary, as the reference histograms for tHq and tHW signals
  // are normalized to the SM cross section for all values of kappa_t and kappa_V !!
  TH1*        histogram_tHq_htt_1p0_1p0_scaled           = scaleHistogram(histogram_tHq_htt_1p0_1p0,  +1.0, 1.0, kTHQ, kScale);
  TH1*        histogram_tHq_htt_0p0_1p0_scaled           = scaleHistogram(histogram_tHq_htt_0p0_1p0,   0.0, 1.0, kTHQ, kScale);
  TH1*        histogram_tHq_htt_2p0_1p0_scaled           = scaleHistogram(histogram_tHq_htt_2p0_1p0,  +2.0, 1.0, kTHQ, kScale);
  TH1*        histogram_tHq_htt_m2p0_1p0_scaled          = scaleHistogram(histogram_tHq_htt_m2p0_1p0, -2.0, 1.0, kTHQ, kScale);
  TH1*        histogram_tHq_htt_m1p0_1p0_scaled          = scaleHistogram(histogram_tHq_htt_m1p0_1p0, -1.0, 1.0, kTHQ, kScale);
  TH1*        histogram_tHq_htt_0p5_1p0_scaled           = scaleHistogram(histogram_tHq_htt_0p5_1p0,  +0.5, 1.0, kTHQ, kScale);
  TH1*        histogram_tHq_htt_3p0_1p0_scaled           = scaleHistogram(histogram_tHq_htt_3p0_1p0,  +3.0, 1.0, kTHQ, kScale);

  // computed histograms
  TH1*        histogram_tHq_htt_1p0_1p0_computed_scaled  = computeHistogram(histogram_tHq_htt_1p0_1p0_scaled, histogram_tHq_htt_0p0_1p0_scaled, histogram_tHq_htt_2p0_1p0_scaled, "tHq_kt_1_kv_1_htt_computed",   +1.0, +1.0, kTHQ);
  TH1*        histogram_tHq_htt_0p0_1p0_computed_scaled  = computeHistogram(histogram_tHq_htt_1p0_1p0_scaled, histogram_tHq_htt_0p0_1p0_scaled, histogram_tHq_htt_2p0_1p0_scaled, "tHq_kt_0_kv_1_htt_computed",    0.0, +1.0, kTHQ);
  TH1*        histogram_tHq_htt_2p0_1p0_computed_scaled  = computeHistogram(histogram_tHq_htt_1p0_1p0_scaled, histogram_tHq_htt_0p0_1p0_scaled, histogram_tHq_htt_2p0_1p0_scaled, "tHq_kt_2_kv_1_htt_computed",   +2.0, +1.0, kTHQ);
  
  TH1*        histogram_tHq_htt_m2p0_1p0_computed_scaled = computeHistogram(histogram_tHq_htt_1p0_1p0_scaled, histogram_tHq_htt_0p0_1p0_scaled, histogram_tHq_htt_2p0_1p0_scaled, "tHq_kt_m2_kv_1_htt_computed",  -2.0, +1.0, kTHQ); 
  TH1*        histogram_tHq_htt_m1p0_1p0_computed_scaled = computeHistogram(histogram_tHq_htt_1p0_1p0_scaled, histogram_tHq_htt_0p0_1p0_scaled, histogram_tHq_htt_2p0_1p0_scaled, "tHq_kt_m1_kv_1_htt_computed",  -1.0, +1.0, kTHQ); 
  TH1*        histogram_tHq_htt_0p5_1p0_computed_scaled  = computeHistogram(histogram_tHq_htt_1p0_1p0_scaled, histogram_tHq_htt_0p0_1p0_scaled, histogram_tHq_htt_2p0_1p0_scaled, "tHq_kt_0p5_kv_1_htt_computed", +0.5, +1.0, kTHQ); 
  TH1*        histogram_tHq_htt_3p0_1p0_computed_scaled  = computeHistogram(histogram_tHq_htt_1p0_1p0_scaled, histogram_tHq_htt_0p0_1p0_scaled, histogram_tHq_htt_2p0_1p0_scaled, "tHq_kt_3_kv_1_htt_computed",   +3.0, +1.0, kTHQ);

  TH1*        histogram_tHq_htt_1p0_1p0_computed         = scaleHistogram(histogram_tHq_htt_1p0_1p0_computed_scaled,  +1.0, 1.0, kTHQ, kUnscale);
  TH1*        histogram_tHq_htt_0p0_1p0_computed         = scaleHistogram(histogram_tHq_htt_0p0_1p0_computed_scaled,   0.0, 1.0, kTHQ, kUnscale);
  TH1*        histogram_tHq_htt_2p0_1p0_computed         = scaleHistogram(histogram_tHq_htt_2p0_1p0_computed_scaled,  +2.0, 1.0, kTHQ, kUnscale);

  TH1*        histogram_tHq_htt_m2p0_1p0_computed        = scaleHistogram(histogram_tHq_htt_m2p0_1p0_computed_scaled, -2.0, 1.0, kTHQ, kUnscale);
  TH1*        histogram_tHq_htt_m1p0_1p0_computed        = scaleHistogram(histogram_tHq_htt_m1p0_1p0_computed_scaled, -1.0, 1.0, kTHQ, kUnscale);
  TH1*        histogram_tHq_htt_0p5_1p0_computed         = scaleHistogram(histogram_tHq_htt_0p5_1p0_computed_scaled,  +0.5, 1.0, kTHQ, kUnscale);
  TH1*        histogram_tHq_htt_3p0_1p0_computed         = scaleHistogram(histogram_tHq_htt_3p0_1p0_computed_scaled,  +3.0, 1.0, kTHQ, kUnscale);

  // make control plots
  showHistograms(800, 900,
		 histogram_tHq_htt_1p0_1p0,           "Reference",
		 histogram_tHq_htt_1p0_1p0_computed,  "Computed",
		 xAxisTitle, 1.10,
		 true, 1.e-4, 1.e+4, yAxisTitle, 1.30,
		 0.64, 0.78,
		 "plots/computeShapes4tH_tHq_htt_1p0_1p0.png");
  showHistograms(800, 900,
		 histogram_tHq_htt_0p0_1p0,           "Reference",
		 histogram_tHq_htt_0p0_1p0_computed,  "Computed",
		 xAxisTitle, 1.10,
		 true, 1.e-4, 1.e+4, yAxisTitle, 1.30,
		 0.64, 0.78,
		 "plots/computeShapes4tH_tHq_htt_0p0_1p0.png");
  showHistograms(800, 900,
		 histogram_tHq_htt_2p0_1p0,           "Reference",
		 histogram_tHq_htt_2p0_1p0_computed,  "Computed",
		 xAxisTitle, 1.10,
		 true, 1.e-4, 1.e+4, yAxisTitle, 1.30,
		 0.64, 0.78,
		 "plots/computeShapes4tH_tHq_htt_2p0_1p0.png");

  showHistograms(800, 900,
		 histogram_tHq_htt_m2p0_1p0,          "Reference",
		 histogram_tHq_htt_m2p0_1p0_computed, "Computed",
		 xAxisTitle, 1.10,
		 true, 1.e-4, 1.e+4, yAxisTitle, 1.30,
		 0.64, 0.78,
		 "plots/computeShapes4tH_tHq_htt_m2p0_1p0.png");
  showHistograms(800, 900,
		 histogram_tHq_htt_m1p0_1p0,          "Reference",
		 histogram_tHq_htt_m1p0_1p0_computed, "Computed",
		 xAxisTitle, 1.10,
		 true, 1.e-4, 1.e+4, yAxisTitle, 1.30,
		 0.64, 0.78,
		 "plots/computeShapes4tH_tHq_htt_m1p0_1p0.png");
  showHistograms(800, 900,
		 histogram_tHq_htt_0p5_1p0,           "Reference",
		 histogram_tHq_htt_0p5_1p0_computed,  "Computed",
		 xAxisTitle, 1.10,
		 true, 1.e-4, 1.e+4, yAxisTitle, 1.30,
		 0.64, 0.78,
		 "plots/computeShapes4tH_tHq_htt_0p5_1p0.png");
  showHistograms(800, 900,
		 histogram_tHq_htt_3p0_1p0,           "Reference",
		 histogram_tHq_htt_3p0_1p0_computed,  "Computed",
		 xAxisTitle, 1.10,
		 true, 1.e-4, 1.e+4, yAxisTitle, 1.30,
		 0.64, 0.78,
		 "plots/computeShapes4tH_tHq_htt_3p0_1p0.png");
  //-------------------------------------------------------------------------------------------------
  
  //-------------------------------------------------------------------------------------------------
  // t-channel tH production, with decay H->WW
  //
  // histograms used as "basis" histograms
  std::string histogramName_tHq_hww_1p0_1p0              = "tHq_hww";
  TH1*        histogram_tHq_hww_1p0_1p0                  = loadHistogram(inputFile, "", histogramName_tHq_hww_1p0_1p0);
  std::string histogramName_tHq_hww_0p0_1p0              = "tHq_kt_0_kv_1_hww";
  TH1*        histogram_tHq_hww_0p0_1p0                  = loadHistogram(inputFile, "", histogramName_tHq_hww_0p0_1p0);
  std::string histogramName_tHq_hww_2p0_1p0              = "tHq_kt_2_kv_1_hww";
  TH1*        histogram_tHq_hww_2p0_1p0                  = loadHistogram(inputFile, "", histogramName_tHq_hww_2p0_1p0);

  // histograms used as reference for testing
  std::string histogramName_tHq_hww_m2p0_1p0             = "tHq_kt_m2_kv_1_hww";
  TH1*        histogram_tHq_hww_m2p0_1p0                 = loadHistogram(inputFile, "", histogramName_tHq_hww_m2p0_1p0);
  std::string histogramName_tHq_hww_m1p0_1p0             = "tHq_kt_m1_kv_1_hww";
  TH1*        histogram_tHq_hww_m1p0_1p0                 = loadHistogram(inputFile, "", histogramName_tHq_hww_m1p0_1p0);
  std::string histogramName_tHq_hww_0p5_1p0              = "tHq_kt_0p5_kv_1_hww";
  TH1*        histogram_tHq_hww_0p5_1p0                  = loadHistogram(inputFile, "", histogramName_tHq_hww_0p5_1p0);
  std::string histogramName_tHq_hww_3p0_1p0              = "tHq_kt_3_kv_1_hww";
  TH1*        histogram_tHq_hww_3p0_1p0                  = loadHistogram(inputFile, "", histogramName_tHq_hww_3p0_1p0);

  // Scale reference histograms to proper cross section.
  // This step is neccessary, as the reference histograms for tHq and tHW signals
  // are normalized to the SM cross section for all values of kappa_t and kappa_V !!
  TH1*        histogram_tHq_hww_1p0_1p0_scaled           = scaleHistogram(histogram_tHq_hww_1p0_1p0,  +1.0, 1.0, kTHQ, kScale);
  TH1*        histogram_tHq_hww_0p0_1p0_scaled           = scaleHistogram(histogram_tHq_hww_0p0_1p0,   0.0, 1.0, kTHQ, kScale);
  TH1*        histogram_tHq_hww_2p0_1p0_scaled           = scaleHistogram(histogram_tHq_hww_2p0_1p0,  +2.0, 1.0, kTHQ, kScale);
  TH1*        histogram_tHq_hww_m2p0_1p0_scaled          = scaleHistogram(histogram_tHq_hww_m2p0_1p0, -2.0, 1.0, kTHQ, kScale);
  TH1*        histogram_tHq_hww_m1p0_1p0_scaled          = scaleHistogram(histogram_tHq_hww_m1p0_1p0, -1.0, 1.0, kTHQ, kScale);
  TH1*        histogram_tHq_hww_0p5_1p0_scaled           = scaleHistogram(histogram_tHq_hww_0p5_1p0,  +0.5, 1.0, kTHQ, kScale);
  TH1*        histogram_tHq_hww_3p0_1p0_scaled           = scaleHistogram(histogram_tHq_hww_3p0_1p0,  +3.0, 1.0, kTHQ, kScale);

  // computed histograms
  TH1*        histogram_tHq_hww_1p0_1p0_computed_scaled  = computeHistogram(histogram_tHq_hww_1p0_1p0_scaled, histogram_tHq_hww_0p0_1p0_scaled, histogram_tHq_hww_2p0_1p0_scaled, "tHq_kt_1_kv_1_hww_computed",   +1.0, +1.0, kTHQ);
  TH1*        histogram_tHq_hww_0p0_1p0_computed_scaled  = computeHistogram(histogram_tHq_hww_1p0_1p0_scaled, histogram_tHq_hww_0p0_1p0_scaled, histogram_tHq_hww_2p0_1p0_scaled, "tHq_kt_0_kv_1_hww_computed",    0.0, +1.0, kTHQ);
  TH1*        histogram_tHq_hww_2p0_1p0_computed_scaled  = computeHistogram(histogram_tHq_hww_1p0_1p0_scaled, histogram_tHq_hww_0p0_1p0_scaled, histogram_tHq_hww_2p0_1p0_scaled, "tHq_kt_2_kv_1_hww_computed",   +2.0, +1.0, kTHQ);
  
  TH1*        histogram_tHq_hww_m2p0_1p0_computed_scaled = computeHistogram(histogram_tHq_hww_1p0_1p0_scaled, histogram_tHq_hww_0p0_1p0_scaled, histogram_tHq_hww_2p0_1p0_scaled, "tHq_kt_m2_kv_1_hww_computed",  -2.0, +1.0, kTHQ); 
  TH1*        histogram_tHq_hww_m1p0_1p0_computed_scaled = computeHistogram(histogram_tHq_hww_1p0_1p0_scaled, histogram_tHq_hww_0p0_1p0_scaled, histogram_tHq_hww_2p0_1p0_scaled, "tHq_kt_m1_kv_1_hww_computed",  -1.0, +1.0, kTHQ); 
  TH1*        histogram_tHq_hww_0p5_1p0_computed_scaled  = computeHistogram(histogram_tHq_hww_1p0_1p0_scaled, histogram_tHq_hww_0p0_1p0_scaled, histogram_tHq_hww_2p0_1p0_scaled, "tHq_kt_0p5_kv_1_hww_computed", +0.5, +1.0, kTHQ); 
  TH1*        histogram_tHq_hww_3p0_1p0_computed_scaled  = computeHistogram(histogram_tHq_hww_1p0_1p0_scaled, histogram_tHq_hww_0p0_1p0_scaled, histogram_tHq_hww_2p0_1p0_scaled, "tHq_kt_3_kv_1_hww_computed",   +3.0, +1.0, kTHQ);

  TH1*        histogram_tHq_hww_1p0_1p0_computed         = scaleHistogram(histogram_tHq_hww_1p0_1p0_computed_scaled,  +1.0, 1.0, kTHQ, kUnscale);
  TH1*        histogram_tHq_hww_0p0_1p0_computed         = scaleHistogram(histogram_tHq_hww_0p0_1p0_computed_scaled,   0.0, 1.0, kTHQ, kUnscale);
  TH1*        histogram_tHq_hww_2p0_1p0_computed         = scaleHistogram(histogram_tHq_hww_2p0_1p0_computed_scaled,  +2.0, 1.0, kTHQ, kUnscale);

  TH1*        histogram_tHq_hww_m2p0_1p0_computed        = scaleHistogram(histogram_tHq_hww_m2p0_1p0_computed_scaled, -2.0, 1.0, kTHQ, kUnscale);
  TH1*        histogram_tHq_hww_m1p0_1p0_computed        = scaleHistogram(histogram_tHq_hww_m1p0_1p0_computed_scaled, -1.0, 1.0, kTHQ, kUnscale);
  TH1*        histogram_tHq_hww_0p5_1p0_computed         = scaleHistogram(histogram_tHq_hww_0p5_1p0_computed_scaled,  +0.5, 1.0, kTHQ, kUnscale);
  TH1*        histogram_tHq_hww_3p0_1p0_computed         = scaleHistogram(histogram_tHq_hww_3p0_1p0_computed_scaled,  +3.0, 1.0, kTHQ, kUnscale);

  // make control plots
  showHistograms(800, 900,
		 histogram_tHq_hww_1p0_1p0,           "Reference",
		 histogram_tHq_hww_1p0_1p0_computed,  "Computed",
		 xAxisTitle, 1.10,
		 true, 1.e-4, 1.e+4, yAxisTitle, 1.30,
		 0.64, 0.78,
		 "plots/computeShapes4tH_tHq_hww_1p0_1p0.png");
  showHistograms(800, 900,
		 histogram_tHq_hww_0p0_1p0,           "Reference",
		 histogram_tHq_hww_0p0_1p0_computed,  "Computed",
		 xAxisTitle, 1.10,
		 true, 1.e-4, 1.e+4, yAxisTitle, 1.30,
		 0.64, 0.78,
		 "plots/computeShapes4tH_tHq_hww_0p0_1p0.png");
  showHistograms(800, 900,
		 histogram_tHq_hww_2p0_1p0,           "Reference",
		 histogram_tHq_hww_2p0_1p0_computed,  "Computed",
		 xAxisTitle, 1.10,
		 true, 1.e-4, 1.e+4, yAxisTitle, 1.30,
		 0.64, 0.78,
		 "plots/computeShapes4tH_tHq_hww_2p0_1p0.png");

  showHistograms(800, 900,
		 histogram_tHq_hww_m2p0_1p0,          "Reference",
		 histogram_tHq_hww_m2p0_1p0_computed, "Computed",
		 xAxisTitle, 1.10,
		 true, 1.e-4, 1.e+4, yAxisTitle, 1.30,
		 0.64, 0.78,
		 "plots/computeShapes4tH_tHq_hww_m2p0_1p0.png");
  showHistograms(800, 900,
		 histogram_tHq_hww_m1p0_1p0,          "Reference",
		 histogram_tHq_hww_m1p0_1p0_computed, "Computed",
		 xAxisTitle, 1.10,
		 true, 1.e-4, 1.e+4, yAxisTitle, 1.30,
		 0.64, 0.78,
		 "plots/computeShapes4tH_tHq_hww_m1p0_1p0.png");
  showHistograms(800, 900,
		 histogram_tHq_hww_0p5_1p0,           "Reference",
		 histogram_tHq_hww_0p5_1p0_computed,  "Computed",
		 xAxisTitle, 1.10,
		 true, 1.e-4, 1.e+4, yAxisTitle, 1.30,
		 0.64, 0.78,
		 "plots/computeShapes4tH_tHq_hww_0p5_1p0.png");
  showHistograms(800, 900,
		 histogram_tHq_hww_3p0_1p0,           "Reference",
		 histogram_tHq_hww_3p0_1p0_computed,  "Computed",
		 xAxisTitle, 1.10,
		 true, 1.e-4, 1.e+4, yAxisTitle, 1.30,
		 0.64, 0.78,
		 "plots/computeShapes4tH_tHq_hww_3p0_1p0.png");
  //-------------------------------------------------------------------------------------------------

  //-------------------------------------------------------------------------------------------------
  // tH production in association with a W boson, with decay H->tautau
  //
  // histograms used as "basis" histograms
  std::string histogramName_tHW_htt_1p0_1p0              = "tHW_htt";
  TH1*        histogram_tHW_htt_1p0_1p0                  = loadHistogram(inputFile, "", histogramName_tHW_htt_1p0_1p0);
  std::string histogramName_tHW_htt_0p0_1p0              = "tHW_kt_0_kv_1_htt";
  TH1*        histogram_tHW_htt_0p0_1p0                  = loadHistogram(inputFile, "", histogramName_tHW_htt_0p0_1p0);
  std::string histogramName_tHW_htt_2p0_1p0              = "tHW_kt_2_kv_1_htt";
  TH1*        histogram_tHW_htt_2p0_1p0                  = loadHistogram(inputFile, "", histogramName_tHW_htt_2p0_1p0);

  // histograms used as reference for testing
  std::string histogramName_tHW_htt_m2p0_1p0             = "tHW_kt_m2_kv_1_htt";
  TH1*        histogram_tHW_htt_m2p0_1p0                 = loadHistogram(inputFile, "", histogramName_tHW_htt_m2p0_1p0);
  std::string histogramName_tHW_htt_m1p0_1p0             = "tHW_kt_m1_kv_1_htt";
  TH1*        histogram_tHW_htt_m1p0_1p0                 = loadHistogram(inputFile, "", histogramName_tHW_htt_m1p0_1p0);
  std::string histogramName_tHW_htt_0p5_1p0              = "tHW_kt_0p5_kv_1_htt";
  TH1*        histogram_tHW_htt_0p5_1p0                  = loadHistogram(inputFile, "", histogramName_tHW_htt_0p5_1p0);
  std::string histogramName_tHW_htt_3p0_1p0              = "tHW_kt_3_kv_1_htt";
  TH1*        histogram_tHW_htt_3p0_1p0                  = loadHistogram(inputFile, "", histogramName_tHW_htt_3p0_1p0);

  // Scale reference histograms to proper cross section.
  // This step is neccessary, as the reference histograms for tHW and tHW signals
  // are normalized to the SM cross section for all values of kappa_t and kappa_V !!
  TH1*        histogram_tHW_htt_1p0_1p0_scaled           = scaleHistogram(histogram_tHW_htt_1p0_1p0,  +1.0, 1.0, kTHW, kScale);
  TH1*        histogram_tHW_htt_0p0_1p0_scaled           = scaleHistogram(histogram_tHW_htt_0p0_1p0,   0.0, 1.0, kTHW, kScale);
  TH1*        histogram_tHW_htt_2p0_1p0_scaled           = scaleHistogram(histogram_tHW_htt_2p0_1p0,  +2.0, 1.0, kTHW, kScale);
  TH1*        histogram_tHW_htt_m2p0_1p0_scaled          = scaleHistogram(histogram_tHW_htt_m2p0_1p0, -2.0, 1.0, kTHW, kScale);
  TH1*        histogram_tHW_htt_m1p0_1p0_scaled          = scaleHistogram(histogram_tHW_htt_m1p0_1p0, -1.0, 1.0, kTHW, kScale);
  TH1*        histogram_tHW_htt_0p5_1p0_scaled           = scaleHistogram(histogram_tHW_htt_0p5_1p0,  +0.5, 1.0, kTHW, kScale);
  TH1*        histogram_tHW_htt_3p0_1p0_scaled           = scaleHistogram(histogram_tHW_htt_3p0_1p0,  +3.0, 1.0, kTHW, kScale);

  // computed histograms
  TH1*        histogram_tHW_htt_1p0_1p0_computed_scaled  = computeHistogram(histogram_tHW_htt_1p0_1p0_scaled, histogram_tHW_htt_0p0_1p0_scaled, histogram_tHW_htt_2p0_1p0_scaled, "tHW_kt_1_kv_1_htt_computed",   +1.0, +1.0, kTHW);
  TH1*        histogram_tHW_htt_0p0_1p0_computed_scaled  = computeHistogram(histogram_tHW_htt_1p0_1p0_scaled, histogram_tHW_htt_0p0_1p0_scaled, histogram_tHW_htt_2p0_1p0_scaled, "tHW_kt_0_kv_1_htt_computed",    0.0, +1.0, kTHW);
  TH1*        histogram_tHW_htt_2p0_1p0_computed_scaled  = computeHistogram(histogram_tHW_htt_1p0_1p0_scaled, histogram_tHW_htt_0p0_1p0_scaled, histogram_tHW_htt_2p0_1p0_scaled, "tHW_kt_2_kv_1_htt_computed",   +2.0, +1.0, kTHW);
  
  TH1*        histogram_tHW_htt_m2p0_1p0_computed_scaled = computeHistogram(histogram_tHW_htt_1p0_1p0_scaled, histogram_tHW_htt_0p0_1p0_scaled, histogram_tHW_htt_2p0_1p0_scaled, "tHW_kt_m2_kv_1_htt_computed",  -2.0, +1.0, kTHW); 
  TH1*        histogram_tHW_htt_m1p0_1p0_computed_scaled = computeHistogram(histogram_tHW_htt_1p0_1p0_scaled, histogram_tHW_htt_0p0_1p0_scaled, histogram_tHW_htt_2p0_1p0_scaled, "tHW_kt_m1_kv_1_htt_computed",  -1.0, +1.0, kTHW); 
  TH1*        histogram_tHW_htt_0p5_1p0_computed_scaled  = computeHistogram(histogram_tHW_htt_1p0_1p0_scaled, histogram_tHW_htt_0p0_1p0_scaled, histogram_tHW_htt_2p0_1p0_scaled, "tHW_kt_0p5_kv_1_htt_computed", +0.5, +1.0, kTHW); 
  TH1*        histogram_tHW_htt_3p0_1p0_computed_scaled  = computeHistogram(histogram_tHW_htt_1p0_1p0_scaled, histogram_tHW_htt_0p0_1p0_scaled, histogram_tHW_htt_2p0_1p0_scaled, "tHW_kt_3_kv_1_htt_computed",   +3.0, +1.0, kTHW);

  TH1*        histogram_tHW_htt_1p0_1p0_computed         = scaleHistogram(histogram_tHW_htt_1p0_1p0_computed_scaled,  +1.0, 1.0, kTHW, kUnscale);
  TH1*        histogram_tHW_htt_0p0_1p0_computed         = scaleHistogram(histogram_tHW_htt_0p0_1p0_computed_scaled,   0.0, 1.0, kTHW, kUnscale);
  TH1*        histogram_tHW_htt_2p0_1p0_computed         = scaleHistogram(histogram_tHW_htt_2p0_1p0_computed_scaled,  +2.0, 1.0, kTHW, kUnscale);

  TH1*        histogram_tHW_htt_m2p0_1p0_computed        = scaleHistogram(histogram_tHW_htt_m2p0_1p0_computed_scaled, -2.0, 1.0, kTHW, kUnscale);
  TH1*        histogram_tHW_htt_m1p0_1p0_computed        = scaleHistogram(histogram_tHW_htt_m1p0_1p0_computed_scaled, -1.0, 1.0, kTHW, kUnscale);
  TH1*        histogram_tHW_htt_0p5_1p0_computed         = scaleHistogram(histogram_tHW_htt_0p5_1p0_computed_scaled,  +0.5, 1.0, kTHW, kUnscale);
  TH1*        histogram_tHW_htt_3p0_1p0_computed         = scaleHistogram(histogram_tHW_htt_3p0_1p0_computed_scaled,  +3.0, 1.0, kTHW, kUnscale);

  // make control plots
  showHistograms(800, 900,
		 histogram_tHW_htt_1p0_1p0,           "Reference",
		 histogram_tHW_htt_1p0_1p0_computed,  "Computed",
		 xAxisTitle, 1.10,
		 true, 1.e-4, 1.e+4, yAxisTitle, 1.30,
		 0.64, 0.78,
		 "plots/computeShapes4tH_tHW_htt_1p0_1p0.png");
  showHistograms(800, 900,
		 histogram_tHW_htt_0p0_1p0,           "Reference",
		 histogram_tHW_htt_0p0_1p0_computed,  "Computed",
		 xAxisTitle, 1.10,
		 true, 1.e-4, 1.e+4, yAxisTitle, 1.30,
		 0.64, 0.78,
		 "plots/computeShapes4tH_tHW_htt_0p0_1p0.png");
  showHistograms(800, 900,
		 histogram_tHW_htt_2p0_1p0,           "Reference",
		 histogram_tHW_htt_2p0_1p0_computed,  "Computed",
		 xAxisTitle, 1.10,
		 true, 1.e-4, 1.e+4, yAxisTitle, 1.30,
		 0.64, 0.78,
		 "plots/computeShapes4tH_tHW_htt_2p0_1p0.png");

  showHistograms(800, 900,
		 histogram_tHW_htt_m2p0_1p0,          "Reference",
		 histogram_tHW_htt_m2p0_1p0_computed, "Computed",
		 xAxisTitle, 1.10,
		 true, 1.e-4, 1.e+4, yAxisTitle, 1.30,
		 0.64, 0.78,
		 "plots/computeShapes4tH_tHW_htt_m2p0_1p0.png");
  showHistograms(800, 900,
		 histogram_tHW_htt_m1p0_1p0,          "Reference",
		 histogram_tHW_htt_m1p0_1p0_computed, "Computed",
		 xAxisTitle, 1.10,
		 true, 1.e-4, 1.e+4, yAxisTitle, 1.30,
		 0.64, 0.78,
		 "plots/computeShapes4tH_tHW_htt_m1p0_1p0.png");
  showHistograms(800, 900,
		 histogram_tHW_htt_0p5_1p0,           "Reference",
		 histogram_tHW_htt_0p5_1p0_computed,  "Computed",
		 xAxisTitle, 1.10,
		 true, 1.e-4, 1.e+4, yAxisTitle, 1.30,
		 0.64, 0.78,
		 "plots/computeShapes4tH_tHW_htt_0p5_1p0.png");
  showHistograms(800, 900,
		 histogram_tHW_htt_3p0_1p0,           "Reference",
		 histogram_tHW_htt_3p0_1p0_computed,  "Computed",
		 xAxisTitle, 1.10,
		 true, 1.e-4, 1.e+4, yAxisTitle, 1.30,
		 0.64, 0.78,
		 "plots/computeShapes4tH_tHW_htt_3p0_1p0.png");
  //-------------------------------------------------------------------------------------------------
  
  //-------------------------------------------------------------------------------------------------
  // tH production in association with a W boson, with decay H->WW
  //
  // histograms used as "basis" histograms
  std::string histogramName_tHW_hww_1p0_1p0              = "tHW_hww";
  TH1*        histogram_tHW_hww_1p0_1p0                  = loadHistogram(inputFile, "", histogramName_tHW_hww_1p0_1p0);
  std::string histogramName_tHW_hww_0p0_1p0              = "tHW_kt_0_kv_1_hww";
  TH1*        histogram_tHW_hww_0p0_1p0                  = loadHistogram(inputFile, "", histogramName_tHW_hww_0p0_1p0);
  std::string histogramName_tHW_hww_2p0_1p0              = "tHW_kt_2_kv_1_hww";
  TH1*        histogram_tHW_hww_2p0_1p0                  = loadHistogram(inputFile, "", histogramName_tHW_hww_2p0_1p0);

  // histograms used as reference for testing
  std::string histogramName_tHW_hww_m2p0_1p0             = "tHW_kt_m2_kv_1_hww";
  TH1*        histogram_tHW_hww_m2p0_1p0                 = loadHistogram(inputFile, "", histogramName_tHW_hww_m2p0_1p0);
  std::string histogramName_tHW_hww_m1p0_1p0             = "tHW_kt_m1_kv_1_hww";
  TH1*        histogram_tHW_hww_m1p0_1p0                 = loadHistogram(inputFile, "", histogramName_tHW_hww_m1p0_1p0);
  std::string histogramName_tHW_hww_0p5_1p0              = "tHW_kt_0p5_kv_1_hww";
  TH1*        histogram_tHW_hww_0p5_1p0                  = loadHistogram(inputFile, "", histogramName_tHW_hww_0p5_1p0);
  std::string histogramName_tHW_hww_3p0_1p0              = "tHW_kt_3_kv_1_hww";
  TH1*        histogram_tHW_hww_3p0_1p0                  = loadHistogram(inputFile, "", histogramName_tHW_hww_3p0_1p0);

  // Scale reference histograms to proper cross section.
  // This step is neccessary, as the reference histograms for tHW and tHW signals
  // are normalized to the SM cross section for all values of kappa_t and kappa_V !!
  TH1*        histogram_tHW_hww_1p0_1p0_scaled           = scaleHistogram(histogram_tHW_hww_1p0_1p0,  +1.0, 1.0, kTHW, kScale);
  TH1*        histogram_tHW_hww_0p0_1p0_scaled           = scaleHistogram(histogram_tHW_hww_0p0_1p0,   0.0, 1.0, kTHW, kScale);
  TH1*        histogram_tHW_hww_2p0_1p0_scaled           = scaleHistogram(histogram_tHW_hww_2p0_1p0,  +2.0, 1.0, kTHW, kScale);
  TH1*        histogram_tHW_hww_m2p0_1p0_scaled          = scaleHistogram(histogram_tHW_hww_m2p0_1p0, -2.0, 1.0, kTHW, kScale);
  TH1*        histogram_tHW_hww_m1p0_1p0_scaled          = scaleHistogram(histogram_tHW_hww_m1p0_1p0, -1.0, 1.0, kTHW, kScale);
  TH1*        histogram_tHW_hww_0p5_1p0_scaled           = scaleHistogram(histogram_tHW_hww_0p5_1p0,  +0.5, 1.0, kTHW, kScale);
  TH1*        histogram_tHW_hww_3p0_1p0_scaled           = scaleHistogram(histogram_tHW_hww_3p0_1p0,  +3.0, 1.0, kTHW, kScale);

  // computed histograms
  TH1*        histogram_tHW_hww_1p0_1p0_computed_scaled  = computeHistogram(histogram_tHW_hww_1p0_1p0_scaled, histogram_tHW_hww_0p0_1p0_scaled, histogram_tHW_hww_2p0_1p0_scaled, "tHW_kt_1_kv_1_hww_computed",   +1.0, +1.0, kTHW);
  TH1*        histogram_tHW_hww_0p0_1p0_computed_scaled  = computeHistogram(histogram_tHW_hww_1p0_1p0_scaled, histogram_tHW_hww_0p0_1p0_scaled, histogram_tHW_hww_2p0_1p0_scaled, "tHW_kt_0_kv_1_hww_computed",    0.0, +1.0, kTHW);
  TH1*        histogram_tHW_hww_2p0_1p0_computed_scaled  = computeHistogram(histogram_tHW_hww_1p0_1p0_scaled, histogram_tHW_hww_0p0_1p0_scaled, histogram_tHW_hww_2p0_1p0_scaled, "tHW_kt_2_kv_1_hww_computed",   +2.0, +1.0, kTHW);
  
  TH1*        histogram_tHW_hww_m2p0_1p0_computed_scaled = computeHistogram(histogram_tHW_hww_1p0_1p0_scaled, histogram_tHW_hww_0p0_1p0_scaled, histogram_tHW_hww_2p0_1p0_scaled, "tHW_kt_m2_kv_1_hww_computed",  -2.0, +1.0, kTHW); 
  TH1*        histogram_tHW_hww_m1p0_1p0_computed_scaled = computeHistogram(histogram_tHW_hww_1p0_1p0_scaled, histogram_tHW_hww_0p0_1p0_scaled, histogram_tHW_hww_2p0_1p0_scaled, "tHW_kt_m1_kv_1_hww_computed",  -1.0, +1.0, kTHW); 
  TH1*        histogram_tHW_hww_0p5_1p0_computed_scaled  = computeHistogram(histogram_tHW_hww_1p0_1p0_scaled, histogram_tHW_hww_0p0_1p0_scaled, histogram_tHW_hww_2p0_1p0_scaled, "tHW_kt_0p5_kv_1_hww_computed", +0.5, +1.0, kTHW); 
  TH1*        histogram_tHW_hww_3p0_1p0_computed_scaled  = computeHistogram(histogram_tHW_hww_1p0_1p0_scaled, histogram_tHW_hww_0p0_1p0_scaled, histogram_tHW_hww_2p0_1p0_scaled, "tHW_kt_3_kv_1_hww_computed",   +3.0, +1.0, kTHW);

  TH1*        histogram_tHW_hww_1p0_1p0_computed         = scaleHistogram(histogram_tHW_hww_1p0_1p0_computed_scaled,  +1.0, 1.0, kTHW, kUnscale);
  TH1*        histogram_tHW_hww_0p0_1p0_computed         = scaleHistogram(histogram_tHW_hww_0p0_1p0_computed_scaled,   0.0, 1.0, kTHW, kUnscale);
  TH1*        histogram_tHW_hww_2p0_1p0_computed         = scaleHistogram(histogram_tHW_hww_2p0_1p0_computed_scaled,  +2.0, 1.0, kTHW, kUnscale);

  TH1*        histogram_tHW_hww_m2p0_1p0_computed        = scaleHistogram(histogram_tHW_hww_m2p0_1p0_computed_scaled, -2.0, 1.0, kTHW, kUnscale);
  TH1*        histogram_tHW_hww_m1p0_1p0_computed        = scaleHistogram(histogram_tHW_hww_m1p0_1p0_computed_scaled, -1.0, 1.0, kTHW, kUnscale);
  TH1*        histogram_tHW_hww_0p5_1p0_computed         = scaleHistogram(histogram_tHW_hww_0p5_1p0_computed_scaled,  +0.5, 1.0, kTHW, kUnscale);
  TH1*        histogram_tHW_hww_3p0_1p0_computed         = scaleHistogram(histogram_tHW_hww_3p0_1p0_computed_scaled,  +3.0, 1.0, kTHW, kUnscale);

  // make control plots
  showHistograms(800, 900,
		 histogram_tHW_hww_1p0_1p0,           "Reference",
		 histogram_tHW_hww_1p0_1p0_computed,  "Computed",
		 xAxisTitle, 1.10,
		 true, 1.e-4, 1.e+4, yAxisTitle, 1.30,
		 0.64, 0.78,
		 "plots/computeShapes4tH_tHW_hww_1p0_1p0.png");
  showHistograms(800, 900,
		 histogram_tHW_hww_0p0_1p0,           "Reference",
		 histogram_tHW_hww_0p0_1p0_computed,  "Computed",
		 xAxisTitle, 1.10,
		 true, 1.e-4, 1.e+4, yAxisTitle, 1.30,
		 0.64, 0.78,
		 "plots/computeShapes4tH_tHW_hww_0p0_1p0.png");
  showHistograms(800, 900,
		 histogram_tHW_hww_2p0_1p0,           "Reference",
		 histogram_tHW_hww_2p0_1p0_computed,  "Computed",
		 xAxisTitle, 1.10,
		 true, 1.e-4, 1.e+4, yAxisTitle, 1.30,
		 0.64, 0.78,
		 "plots/computeShapes4tH_tHW_hww_2p0_1p0.png");

  showHistograms(800, 900,
		 histogram_tHW_hww_m2p0_1p0,          "Reference",
		 histogram_tHW_hww_m2p0_1p0_computed, "Computed",
		 xAxisTitle, 1.10,
		 true, 1.e-4, 1.e+4, yAxisTitle, 1.30,
		 0.64, 0.78,
		 "plots/computeShapes4tH_tHW_hww_m2p0_1p0.png");
  showHistograms(800, 900,
		 histogram_tHW_hww_m1p0_1p0,          "Reference",
		 histogram_tHW_hww_m1p0_1p0_computed, "Computed",
		 xAxisTitle, 1.10,
		 true, 1.e-4, 1.e+4, yAxisTitle, 1.30,
		 0.64, 0.78,
		 "plots/computeShapes4tH_tHW_hww_m1p0_1p0.png");
  showHistograms(800, 900,
		 histogram_tHW_hww_0p5_1p0,           "Reference",
		 histogram_tHW_hww_0p5_1p0_computed,  "Computed",
		 xAxisTitle, 1.10,
		 true, 1.e-4, 1.e+4, yAxisTitle, 1.30,
		 0.64, 0.78,
		 "plots/computeShapes4tH_tHW_hww_0p5_1p0.png");
  showHistograms(800, 900,
		 histogram_tHW_hww_3p0_1p0,           "Reference",
		 histogram_tHW_hww_3p0_1p0_computed,  "Computed",
		 xAxisTitle, 1.10,
		 true, 1.e-4, 1.e+4, yAxisTitle, 1.30,
		 0.64, 0.78,
		 "plots/computeShapes4tH_tHW_hww_3p0_1p0.png");
  //-------------------------------------------------------------------------------------------------
  
  delete inputFile;
}

