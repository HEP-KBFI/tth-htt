
#include <TFile.h>
#include <TString.h>
#include <TH1.h>
#include <TH2.h>
#include <TGraph.h>
#include <TAxis.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TMath.h>
#include <TROOT.h>
#include <TStyle.h>

#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <iomanip>
#include <assert.h>

enum { kUndefined, kAbsolute, kRelative };

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

void showHistograms(double canvasSizeX, double canvasSizeY,
		    TH1* histogram_ref, const std::string& legendEntry_ref, double integral_ref,
		    TH1* histogram2, const std::string& legendEntry2, double integral2,
		    TH1* histogram3, const std::string& legendEntry3, double integral3,
		    TH1* histogram4, const std::string& legendEntry4, double integral4,
		    TH1* histogram5, const std::string& legendEntry5, double integral5,
		    TH1* histogram6, const std::string& legendEntry6, double integral6,
		    const std::string& xAxisTitle, double xAxisOffset,
		    bool useLogScale, double yMin, double yMax, const std::string& yAxisTitle, double yAxisOffset,
		    double legendX0, double legendY0, 
		    const std::string& outputFileName)
{
  if ( !(histogram_ref && histogram2) ) return;

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

  //int colors[6] = { kBlack, kGreen - 6, kBlue - 7,  kMagenta - 7, kCyan - 6, kRed - 6 };
  int colors[6] = { kBlack, kRed, kBlue - 7,  kMagenta - 7, kCyan - 6, kRed - 6 };
  int markerStyles[6] = { 24, 25, 20, 21, 22, 23 };
  int markerSizes[6] = { 1, 1, 1, 1, 1, 1 };

  TLegend* legend = new TLegend(legendX0, legendY0, legendX0 + 0.61, legendY0 + 0.21, "", "brNDC"); 
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
  //if ( integral_ref >= 0. ) legend->AddEntry(histogram_ref, Form("%s: %1.2f", legendEntry_ref.data(), integral_ref), "p");
  //else legend->AddEntry(histogram_ref, legendEntry_ref.data(), "p");
  legend->AddEntry(histogram_ref, Form("%s: %1.2f", legendEntry_ref.data(), integral_ref), "p");

  TAxis* xAxis_top = histogram_ref->GetXaxis();
  xAxis_top->SetTitle(xAxisTitle.data());
  xAxis_top->SetTitleOffset(xAxisOffset);
  xAxis_top->SetLabelColor(10);
  xAxis_top->SetTitleColor(10);

  TAxis* yAxis_top = histogram_ref->GetYaxis();
  yAxis_top->SetTitle(yAxisTitle.data());
  yAxis_top->SetTitleOffset(yAxisOffset);

  if ( histogram2 ) {
    histogram2->SetLineColor(colors[1]);
    histogram2->SetLineWidth(2);
    histogram2->SetMarkerColor(colors[1]);
    histogram2->SetMarkerStyle(markerStyles[1]);
    histogram2->SetMarkerSize(markerSizes[1]);
    histogram2->Draw("e1psame");
    //if ( integral2 >= 0. ) legend->AddEntry(histogram2, Form("%s: %1.2f", legendEntry2.data(), integral2), "p");
    //else legend->AddEntry(histogram2, legendEntry2.data(), "p");
    legend->AddEntry(histogram2, Form("%s: %1.2f", legendEntry2.data(), integral2), "p");
  }

  if ( histogram3 ) {
    histogram3->SetLineColor(colors[2]);
    histogram3->SetLineWidth(2);
    histogram3->SetMarkerColor(colors[2]);
    histogram3->SetMarkerStyle(markerStyles[2]);
    histogram3->SetMarkerSize(markerSizes[2]);
    histogram3->Draw("e1psame");
    //if ( integral3 >= 0. ) legend->AddEntry(histogram3, Form("%s: %1.2f", legendEntry3.data(), integral3), "p");
    //else legend->AddEntry(histogram3, legendEntry3.data(), "p");
    legend->AddEntry(histogram3, Form("%s: %1.2f", legendEntry3.data(), integral3), "p");
  }

  if ( histogram4 ) {
    histogram4->SetLineColor(colors[3]);
    histogram4->SetLineWidth(2);
    histogram4->SetMarkerColor(colors[3]);
    histogram4->SetMarkerStyle(markerStyles[3]);
    histogram4->SetMarkerSize(markerSizes[3]);
    histogram4->Draw("e1psame");
    if ( integral4 >= 0. ) legend->AddEntry(histogram4, Form("%s: %1.2f", legendEntry4.data(), integral4), "p");
    else legend->AddEntry(histogram4, legendEntry4.data(), "p");
  }

  if ( histogram5 ) {
    histogram5->SetLineColor(colors[4]);
    histogram5->SetLineWidth(2);
    histogram5->SetMarkerColor(colors[4]);
    histogram5->SetMarkerStyle(markerStyles[4]);
    histogram5->SetMarkerSize(markerSizes[4]);
    histogram5->Draw("e1psame");
    if ( integral5 >= 0. ) legend->AddEntry(histogram5, Form("%s: %1.2f", legendEntry5.data(), integral5), "p");
    else legend->AddEntry(histogram5, legendEntry5.data(), "p");
  }

  if ( histogram6 ) {
    histogram6->SetLineColor(colors[5]);
    histogram6->SetLineWidth(2);
    histogram6->SetMarkerColor(colors[5]);
    histogram6->SetMarkerStyle(markerStyles[5]);
    histogram6->SetMarkerSize(markerSizes[5]);
    histogram6->Draw("e1psame");
    if ( integral6 >= 0. ) legend->AddEntry(histogram6, Form("%s: %1.2f", legendEntry6.data(), integral6), "p");
    else legend->AddEntry(histogram6, legendEntry6.data(), "p");
  }

  legend->Draw();

  canvas->cd();
  bottomPad->Draw();
  bottomPad->cd();

  TH1* histogram2_div_ref = 0;
  if ( histogram2 ) {
    std::string histogramName2_div_ref = std::string(histogram2->GetName()).append("_div_").append(histogram_ref->GetName());
    histogram2_div_ref = compRatioHistogram(histogramName2_div_ref, histogram2, histogram_ref);
    if ( histogram2_div_ref ) {
      histogram2_div_ref->SetTitle("");
      histogram2_div_ref->SetStats(false);
      histogram2_div_ref->SetMinimum(-0.50);
      histogram2_div_ref->SetMaximum(+0.50);
      
      TAxis* xAxis_bottom = histogram2_div_ref->GetXaxis();
      xAxis_bottom->SetTitle(xAxis_top->GetTitle());
      xAxis_bottom->SetLabelColor(1);
      xAxis_bottom->SetTitleColor(1);
      xAxis_bottom->SetTitleOffset(1.20);
      xAxis_bottom->SetTitleSize(0.08);
      xAxis_bottom->SetLabelOffset(0.02);
      xAxis_bottom->SetLabelSize(0.08);
      xAxis_bottom->SetTickLength(0.055);
      
      TAxis* yAxis_bottom = histogram2_div_ref->GetYaxis();
      yAxis_bottom->SetTitle(Form("#frac{%s - %s}{%s}", legendEntry2.data(), legendEntry_ref.data(), legendEntry_ref.data()));
      yAxis_bottom->SetTitleOffset(0.85);
      yAxis_bottom->SetNdivisions(505);
      yAxis_bottom->CenterTitle();
      yAxis_bottom->SetTitleSize(0.08);
      yAxis_bottom->SetLabelSize(0.08);
      yAxis_bottom->SetTickLength(0.04);  
      
      histogram2_div_ref->Draw("e1p");
    }
  }

  TH1* histogram3_div_ref = 0;
  if ( histogram3 ) {
    std::string histogramName3_div_ref = std::string(histogram3->GetName()).append("_div_").append(histogram_ref->GetName());
    histogram3_div_ref = compRatioHistogram(histogramName3_div_ref, histogram3, histogram_ref);
    if ( histogram3_div_ref ) {
      histogram3_div_ref->SetTitle("");
      histogram3_div_ref->SetStats(false);
      histogram3_div_ref->SetMinimum(-0.50);
      histogram3_div_ref->SetMaximum(+0.50);
      
      TAxis* xAxis_bottom = histogram3_div_ref->GetXaxis();
      xAxis_bottom->SetTitle(xAxis_top->GetTitle());
      xAxis_bottom->SetLabelColor(1);
      xAxis_bottom->SetTitleColor(1);
      xAxis_bottom->SetTitleOffset(1.20);
      xAxis_bottom->SetTitleSize(0.08);
      xAxis_bottom->SetLabelOffset(0.02);
      xAxis_bottom->SetLabelSize(0.08);
      xAxis_bottom->SetTickLength(0.055);
      
      TAxis* yAxis_bottom = histogram3_div_ref->GetYaxis();
      yAxis_bottom->SetTitle(Form("#frac{%s - %s}{%s}", legendEntry3.data(), legendEntry_ref.data(), legendEntry_ref.data()));
      yAxis_bottom->SetTitleOffset(0.85);
      yAxis_bottom->SetNdivisions(505);
      yAxis_bottom->CenterTitle();
      yAxis_bottom->SetTitleSize(0.08);
      yAxis_bottom->SetLabelSize(0.08);
      yAxis_bottom->SetTickLength(0.04);  
      
      if ( histogram2 ) histogram3_div_ref->Draw("e1psame");
      else histogram3_div_ref->Draw("e1p");
    }
  }

  TGraph* graph_line = new TGraph(2);
  graph_line->SetPoint(0, xAxis_top->GetXmin(), 0.);
  graph_line->SetPoint(1, xAxis_top->GetXmax(), 0.);
  graph_line->SetLineColor(8);
  graph_line->SetLineWidth(1);
  graph_line->Draw("L");

  if ( histogram2_div_ref ) histogram2_div_ref->Draw("e1psame");
  if ( histogram3_div_ref ) histogram3_div_ref->Draw("e1psame");

  TH1* histogram4_div_ref = 0;
  if ( histogram4 ) {
    std::string histogramName4_div_ref = std::string(histogram4->GetName()).append("_div_").append(histogram_ref->GetName());
    histogram4_div_ref = compRatioHistogram(histogramName4_div_ref, histogram4, histogram_ref);
    if ( histogram4_div_ref ) {
      histogram4_div_ref->Draw("e1psame");
    }
  }

  TH1* histogram5_div_ref = 0;
  if ( histogram5 ) {
    std::string histogramName5_div_ref = std::string(histogram5->GetName()).append("_div_").append(histogram_ref->GetName());
    histogram5_div_ref = compRatioHistogram(histogramName5_div_ref, histogram5, histogram_ref);
    if ( histogram5_div_ref ) {
      histogram5_div_ref->Draw("e1psame");
    }
  }

  TH1* histogram6_div_ref = 0;
  if ( histogram6 ) {
    std::string histogramName6_div_ref = std::string(histogram6->GetName()).append("_div_").append(histogram_ref->GetName());
    histogram6_div_ref = compRatioHistogram(histogramName6_div_ref, histogram6, histogram_ref);
    if ( histogram6_div_ref ) {
      histogram6_div_ref->Draw("e1psame");
    }
  }
  
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
  delete histogram2_div_ref;
  delete histogram3_div_ref;
  delete histogram4_div_ref;
  delete histogram5_div_ref;
  delete histogram6_div_ref;
  delete topPad;
  delete bottomPad;
  delete canvas;  
}

double compIntegral(const TH1* histogram)
{
  if ( !histogram ) return -1.;
  double integral = 0.;
  int numBins = histogram->GetNbinsX();
  for ( int iBin = 1; iBin <= numBins; ++iBin ) {
    double binContent = histogram->GetBinContent(iBin);
    integral += binContent;
  }
  return integral;
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

TH1* linearizeHistogram(TH1* histogram)
{
  if ( !histogram ) return 0;

  TH1* histogram2d = dynamic_cast<TH2*>(histogram);
  if ( !histogram2d ) return histogram;

  TAxis* xAxis = histogram2d->GetXaxis();
  int numBinsX = xAxis->GetNbins();
  TAxis* yAxis = histogram2d->GetYaxis();
  int numBinsY = yAxis->GetNbins();

  std::string histogramName1d = Form("%s_1d", histogram->GetName());
  int numBins1d = numBinsX*numBinsY;
  TH1* histogram1d = new TH1D(histogramName1d.data(),histogramName1d.data(), numBins1d, -0.5, numBins1d - 0.5);
  int iBin1d = 1;
  for ( int iBinX = 1; iBinX <= numBinsX; ++iBinX ) {
    for ( int iBinY = 1; iBinY <= numBinsY; ++iBinY ) {
      double binContent = histogram2d->GetBinContent(iBinX, iBinY);
      double binError = histogram2d->GetBinError(iBinX, iBinY);
      histogram1d->SetBinContent(iBin1d, binContent);
      histogram1d->SetBinError(iBin1d, binError);
      ++iBin1d;
    }
  }

  return histogram1d;
}

TH1* compHistogramErr(const TH1* histogram)
{
  if ( !histogram ) return 0;
  std::string histogramErrName = Form("%sErr", histogram->GetName());
  TH1* histogramErr = (TH1*)histogram->Clone();
  int numBins = histogram->GetNbinsX();
  for ( int iBin = 1; iBin <= numBins; ++iBin ) {
    double binError = histogram->GetBinError(iBin);
    histogramErr->SetBinContent(iBin, binError);
    histogramErr->SetBinError(iBin, 0.);
  }
  return histogramErr;
}

TH1* loadHistogram(TFile* inputFile, const std::string& histogramName)
{
  std::cout << "loading histogram = " << histogramName << " from file = " << inputFile->GetName() << std::endl;
  TH1* histogram = dynamic_cast<TH1*>(inputFile->Get(histogramName.data()));
  std::cout << "histogram = " << histogram << std::endl;
  if ( !histogram ) {
    std::cerr << "Failed to load histogram = " << histogramName << " from file = " << inputFile->GetName() << " --> skipping !!" << std::endl;
    return 0;
  }
  if ( !histogram->GetSumw2N() ) histogram->Sumw2();
  if ( dynamic_cast<TH2*>(histogram) ) histogram = linearizeHistogram(histogram);
  //else if ( histogram->GetNbinsX() >= 100 ) histogram->Rebin(5);
  return histogram;
}

void makePlot(
       const std::string& inputFilePath_ref, const std::string& inputFileName_ref, const std::string& histogramName_ref, const std::string& legendEntry_ref,
       const std::string& inputFilePath_test, const std::string& inputFileName_test, const std::string& histogramName_test, const std::string& legendEntry_test, 
       const std::string& inputFilePath_test2, const std::string& inputFileName_test2, const std::string& histogramName_test2, const std::string& legendEntry_test2,
       const std::string& outputFileName)
{
  std::cout << "<makePlot_shift_minus_central>:" << std::endl;

  TString inputFileName_ref_full = inputFilePath_ref;
  if ( !inputFileName_ref_full.EndsWith("/") ) inputFileName_ref_full.Append("/");
  inputFileName_ref_full.Append(inputFileName_ref.data());
  TFile* inputFile_ref = new TFile(inputFileName_ref_full.Data());
  TH1* histogram_ref = loadHistogram(inputFile_ref, histogramName_ref);
  double integral_ref = compIntegral(histogram_ref);
  divideByBinWidth(histogram_ref);

  TString inputFileName_test_full = inputFilePath_test;
  if ( !inputFileName_test_full.EndsWith("/") ) inputFileName_test_full.Append("/");
  inputFileName_test_full.Append(inputFileName_test.data());
  TFile* inputFile_test = ( inputFileName_test_full != inputFileName_ref_full ) ? 
    new TFile(inputFileName_test_full.Data()) : inputFile_ref;
  TH1* histogram_test = loadHistogram(inputFile_test, histogramName_test);
  double integral_test = compIntegral(histogram_test);
  divideByBinWidth(histogram_test);
  
  TFile* inputFile_test2 = 0;
  TH1* histogram_test2 = 0;
  double integral_test2 = -1.;
  if ( inputFilePath_test2 != "" && inputFileName_test2 != "" && histogramName_test2 != "" ) {
    TString inputFileName_test2_full = inputFilePath_test2;
    if ( !inputFileName_test2_full.EndsWith("/") ) inputFileName_test2_full.Append("/");
    inputFileName_test2_full.Append(inputFileName_test2.data());
    inputFile_test2 = ( inputFileName_test2_full != inputFileName_ref_full ) ? 
      new TFile(inputFileName_test2_full.Data()) : inputFile_ref;
    histogram_test2 = loadHistogram(inputFile_test2, histogramName_test2);
    integral_test2 = compIntegral(histogram_test2);
    divideByBinWidth(histogram_test2);
  }
  
  showHistograms(800, 900, 
		 histogram_ref, legendEntry_ref, integral_ref,
		 histogram_test, legendEntry_test, integral_test, 
		 histogram_test2, legendEntry_test2, integral_test2, 
		 //NULL, "", 0.,
		 NULL, "", 0.,
		 NULL, "", 0.,
		 NULL, "", 0.,
		 "m_{#tau#tau} [GeV]", 1.10,
		 true, 1.e-4, 1.e+4, "1/dm_{#tau#tau} [1/GeV]", 1.30,
		 0.34, 0.72,
		 outputFileName.data());

  TH1* histogramErr_ref = compHistogramErr(histogram_ref);
  TH1* histogramErr_test = compHistogramErr(histogram_test);
  TH1* histogramErr_test2 = ( histogram_test2 ) ?
    compHistogramErr(histogram_test2) : 0;
  std::string outputFileNameErr = TString(outputFileName.data()).ReplaceAll(".png", "_Err.png").Data();
  showHistograms(800, 900, 
		 histogramErr_ref, legendEntry_ref, -1.,
		 histogramErr_test, legendEntry_test, -1., 
		 histogramErr_test2, legendEntry_test2, -1., 
		 //NULL, "", 0.,
		 NULL, "", 0.,
		 NULL, "", 0.,
		 NULL, "", 0.,
		 "m_{#tau#tau} [GeV]", 1.10,
		 true, 1.e-4, 1.e+4, "#sigma(1/dm_{#tau#tau}) [1/GeV]", 1.30,
		 0.34, 0.72,
		 outputFileNameErr.data());

  delete histogramErr_ref;
  delete histogramErr_test;
  delete histogramErr_test2;
  
  delete inputFile_ref;
  if ( inputFile_test != inputFile_ref ) delete inputFile_test;
  if ( inputFile_test2 != inputFile_ref && inputFile_test2 != inputFile_test ) delete inputFile_test2;
}

double square(double x)
{
  return x*x;
}

TH1* subtractHistograms(const std::string& newHistogramName, const TH1* histogram_central, const TH1* histogram_shift, int mode)
{
  const TH1* histogramMinuend = 0;
  const TH1* histogramSubtrahend = 0;
  if ( compIntegral(histogram_central) >= compIntegral(histogram_shift) ) {
    histogramMinuend    = histogram_central;
    histogramSubtrahend = histogram_shift;
  } else {
    histogramMinuend    = histogram_shift;
    histogramSubtrahend = histogram_central;
  }
  if ( !(histogramMinuend && histogramSubtrahend) ) return 0;
  TH1* newHistogram = (TH1*)histogramMinuend->Clone(newHistogramName.data());
  newHistogram->Reset();
  if ( !newHistogram->GetSumw2N() ) newHistogram->Sumw2();
  int numBins = newHistogram->GetNbinsX();
  for ( int iBin = 0; iBin <= (numBins + 1); ++iBin ) {
    double newBinContent = histogramMinuend->GetBinContent(iBin) - histogramSubtrahend->GetBinContent(iBin);
    double newBinError2 = square(histogramMinuend->GetBinError(iBin)) + square(histogramSubtrahend->GetBinError(iBin));
    if ( mode == kRelative ) {
      if ( histogram_central->GetBinContent(iBin) > 0. ) {
	newBinContent /= histogram_central->GetBinContent(iBin);
	newBinError2 /= square(histogram_central->GetBinContent(iBin));
      } else {
	newBinContent = 0.;
	newBinError2 = 0.;
      }
    }
    newHistogram->SetBinContent(iBin, newBinContent);
    assert(newBinError2 >= 0.);
    newHistogram->SetBinError(iBin, TMath::Sqrt(newBinError2));
  }
  return newHistogram;
}

void makePlot_shift_minus_central(
       const std::string& inputFilePath_ref, const std::string& inputFileName_ref, 
       const std::string& histogramName_ref_shift, const std::string& histogramName_ref_central, const std::string& legendEntry_ref,
       const std::string& inputFilePath_test, const std::string& inputFileName_test, 
       const std::string& histogramName_test_shift, const std::string& histogramName_test_central, const std::string& legendEntry_test, 
       const std::string& inputFilePath_test2, const std::string& inputFileName_test2, 
       const std::string& histogramName_test2_shift, const std::string& histogramName_test2_central, const std::string& legendEntry_test2,
       const std::string& outputFileName)
{
  std::cout << "<makePlot_shift_minus_central>:" << std::endl;

  TString inputFileName_ref_full = inputFilePath_ref;
  if ( !inputFileName_ref_full.EndsWith("/") ) inputFileName_ref_full.Append("/");
  inputFileName_ref_full.Append(inputFileName_ref.data());
  TFile* inputFile_ref = new TFile(inputFileName_ref_full.Data());
  TH1* histogram_ref_shift = loadHistogram(inputFile_ref, histogramName_ref_shift);
  TH1* histogram_ref_central = loadHistogram(inputFile_ref, histogramName_ref_central);
  TH1* histogram_ref_shift_minus_centralAbs = 0;
  TH1* histogram_ref_shift_minus_centralRel = 0;
  double integral_ref = -1.;
  if ( histogram_ref_shift && histogram_ref_central ) {
    std::string histogramName_ref_shift_minus_centralAbs = Form("%s_minus_%sAbs", histogram_ref_shift->GetName(), histogram_ref_central->GetName());
    histogram_ref_shift_minus_centralAbs = subtractHistograms(histogramName_ref_shift_minus_centralAbs, histogram_ref_shift, histogram_ref_central, kAbsolute);
    std::string histogramName_ref_shift_minus_centralRel = Form("%s_minus_%sRel", histogram_ref_shift->GetName(), histogram_ref_central->GetName());
    histogram_ref_shift_minus_centralRel = subtractHistograms(histogramName_ref_shift_minus_centralRel, histogram_ref_shift, histogram_ref_central, kRelative);
    integral_ref = compIntegral(histogram_ref_shift_minus_centralAbs);
    std::cout << " integral_ref = " << integral_ref << std::endl;
    divideByBinWidth(histogram_ref_shift_minus_centralAbs);
  }

  TString inputFileName_test_full = inputFilePath_test;
  if ( !inputFileName_test_full.EndsWith("/") ) inputFileName_test_full.Append("/");
  inputFileName_test_full.Append(inputFileName_test.data());
  TFile* inputFile_test = ( inputFileName_test_full != inputFileName_ref_full ) ? 
    new TFile(inputFileName_test_full.Data()) : inputFile_ref;
  TH1* histogram_test_shift = loadHistogram(inputFile_test, histogramName_test_shift);
  TH1* histogram_test_central = loadHistogram(inputFile_test, histogramName_test_central);
  TH1* histogram_test_shift_minus_centralAbs = 0;
  TH1* histogram_test_shift_minus_centralRel = 0;
  double integral_test = -1.;
  if ( histogram_test_shift && histogram_test_central ) {
    std::string histogramName_test_shift_minus_centralAbs = Form("%s_minus_%sAbs", histogram_test_shift->GetName(), histogram_test_central->GetName());
    histogram_test_shift_minus_centralAbs = subtractHistograms(histogramName_test_shift_minus_centralAbs, histogram_test_shift, histogram_test_central, kAbsolute);
    std::string histogramName_test_shift_minus_centralRel = Form("%s_minus_%sRel", histogram_test_shift->GetName(), histogram_test_central->GetName());
    histogram_test_shift_minus_centralRel = subtractHistograms(histogramName_test_shift_minus_centralRel, histogram_test_shift, histogram_test_central, kRelative);
    integral_test = compIntegral(histogram_test_shift_minus_centralAbs);
    std::cout << " integral_test = " << integral_test << std::endl;
    divideByBinWidth(histogram_test_shift_minus_centralAbs);
  }

  TFile* inputFile_test2 = 0;
  TH1* histogram_test2_shift_minus_centralAbs = 0;
  TH1* histogram_test2_shift_minus_centralRel = 0;
  double integral_test2 = -1.;
  if ( inputFilePath_test2 != "" && inputFileName_test2 != "" && histogramName_test2_shift != "" && histogramName_test2_central != "" ) {
    TString inputFileName_test2_full = inputFilePath_test2;
    if ( !inputFileName_test2_full.EndsWith("/") ) inputFileName_test2_full.Append("/");
    inputFileName_test2_full.Append(inputFileName_test2.data());
    inputFile_test2 = ( inputFileName_test2_full != inputFileName_ref_full ) ? 
      new TFile(inputFileName_test2_full.Data()) : inputFile_ref;
    TH1* histogram_test2_shift = loadHistogram(inputFile_test2, histogramName_test2_shift);
    TH1* histogram_test2_central = loadHistogram(inputFile_test2, histogramName_test2_central);
    if ( histogram_test2_shift && histogram_test2_central ) {
      std::string histogramName_test2_shift_minus_centralAbs = Form("%s_minus_%sAbs", histogram_test2_shift->GetName(), histogram_test2_central->GetName());
      histogram_test2_shift_minus_centralAbs = subtractHistograms(histogramName_test2_shift_minus_centralAbs, histogram_test2_shift, histogram_test2_central, kAbsolute);
      std::string histogramName_test2_shift_minus_centralRel = Form("%s_minus_%sRel", histogram_test2_shift->GetName(), histogram_test2_central->GetName());
      histogram_test2_shift_minus_centralRel = subtractHistograms(histogramName_test2_shift_minus_centralRel, histogram_test2_shift, histogram_test2_central, kRelative);
      integral_test2 = compIntegral(histogram_test2_shift_minus_centralAbs);
      std::cout << " integral_test2 = " << integral_test2 << std::endl;
      divideByBinWidth(histogram_test2_shift_minus_centralAbs);
    }
  }

  size_t idx = outputFileName.find_last_of('.');
  std::string outputFileName_abs = std::string(outputFileName, 0, idx);
  outputFileName_abs.append("_absolute");
  if ( idx != std::string::npos ) outputFileName_abs.append(std::string(outputFileName, idx));

  showHistograms(800, 900, 
		 histogram_ref_shift_minus_centralAbs, legendEntry_ref, integral_ref,
		 histogram_test_shift_minus_centralAbs, legendEntry_test, integral_test, 
		 histogram_test2_shift_minus_centralAbs, legendEntry_test2, integral_test2, 
		 //NULL, "", 0.,
		 NULL, "", 0.,
		 NULL, "", 0.,
		 NULL, "", 0.,
		 "m_{#tau#tau} [GeV]", 1.10,
		 true, 1.e-4, 1.e+4, "1/dm_{#tau#tau} [1/GeV]", 1.30,
		 0.34, 0.72,
		 outputFileName_abs.data());
  
  std::string outputFileName_rel = std::string(outputFileName, 0, idx);
  outputFileName_rel.append("_relative");
  if ( idx != std::string::npos ) outputFileName_rel.append(std::string(outputFileName, idx));
  
  showHistograms(800, 900, 
		 histogram_ref_shift_minus_centralRel, legendEntry_ref, integral_ref,
		 histogram_test_shift_minus_centralRel, legendEntry_test, integral_test, 
		 histogram_test2_shift_minus_centralRel, legendEntry_test2, integral_test2, 
		 //NULL, "", 0.,
		 NULL, "", 0.,
		 NULL, "", 0.,
		 NULL, "", 0.,
		 "m_{#tau#tau} [GeV]", 1.10,
		 true, 1.e-4, 1.e+4, "#Delta 1/dm_{#tau#tau}", 1.30,
		 0.34, 0.72,
		 outputFileName_rel.data());

  delete inputFile_ref;
  if ( inputFile_test != inputFile_ref ) delete inputFile_test;
  if ( inputFile_test2 != inputFile_ref && inputFile_test2 != inputFile_test ) delete inputFile_test2;
}

void compareDatacards_old()
{
  gROOT->SetBatch(true);

  TH1::AddDirectory(false);

  std::string inputFilePath_ref = "/home/veelken/ttHAnalysis/2016/2017Mar04/datacards/2lss_1tau/";
  std::string inputFileName_ref = "prepareDatacards_2lss_1tau_sumOS_mvaDiscr_2lss.root";
  std::string legendEntry_ref = "Tallinn";

  std::string inputFilePath_test = "/home/veelken/ttHAnalysis/2016/2017Mar16/datacards/2lss_1tau/";
  std::string inputFileName_test = "prepareDatacards_2lss_1tau_sumOS_mvaDiscr_2lss.root";
  std::string legendEntry_test = "Tallinn (addMEM)";

  std::string inputFilePath_test2 = "";
  std::string inputFileName_test2 = "";
  std::string legendEntry_test2 = "";

  std::string outputFilePath = "/home/veelken/VHbbNtuples_8_0_x/CMSSW_8_0_19/src/tthAnalysis/HiggsToTauTau/macros/plots";

  std::vector<std::string> processes; 
  processes.push_back("data_obs");
  processes.push_back("ttH_hww");
  processes.push_back("ttH_htt");
  processes.push_back("ttH_hzz");
  processes.push_back("TTW");
  processes.push_back("TTZ");
  processes.push_back("EWK");
  processes.push_back("Rares");
  processes.push_back("data_fakes");
  processes.push_back("data_flips");

  std::vector<std::string> sysShifts;
/*
  sysShifts.push_back("CMS_ttHl_tauESUp");
  sysShifts.push_back("CMS_ttHl_tauESDown");
  sysShifts.push_back("CMS_ttHl_JESUp");
  sysShifts.push_back("CMS_ttHl_JESDown");
  sysShifts.push_back("CMS_ttHl_FRe_shape_2lss_anticorr1Up");
  sysShifts.push_back("CMS_ttHl_FRe_shape_2lss_anticorr1Down");
  sysShifts.push_back("CMS_ttHl_FRe_shape_2lss_corr1Up");
  sysShifts.push_back("CMS_ttHl_FRe_shape_2lss_corr1Down");
  sysShifts.push_back("CMS_ttHl_FRm_shape_2lss_anticorr1Up");
  sysShifts.push_back("CMS_ttHl_FRm_shape_2lss_anticorr1Down");
  sysShifts.push_back("CMS_ttHl_FRm_shape_2lss_corr1Up");
  sysShifts.push_back("CMS_ttHl_FRm_shape_2lss_corr1Down");
  sysShifts.push_back("CMS_ttHl_btag_HFUp");
  sysShifts.push_back("CMS_ttHl_btag_HFDown");
  sysShifts.push_back("CMS_ttHl_btag_HFStats1Up");
  sysShifts.push_back("CMS_ttHl_btag_HFStats1Down");
  sysShifts.push_back("CMS_ttHl_btag_HFStats2Up");
  sysShifts.push_back("CMS_ttHl_btag_HFStats2Down");
  sysShifts.push_back("CMS_ttHl_btag_LFUp");
  sysShifts.push_back("CMS_ttHl_btag_LFDown");
  sysShifts.push_back("CMS_ttHl_btag_LFStats1Up");
  sysShifts.push_back("CMS_ttHl_btag_LFStats1Down");
  sysShifts.push_back("CMS_ttHl_btag_LFStats2Up");
  sysShifts.push_back("CMS_ttHl_btag_LFStats2Down");
  sysShifts.push_back("CMS_ttHl_btag_cErr1Up");
  sysShifts.push_back("CMS_ttHl_btag_cErr1Down");
  sysShifts.push_back("CMS_ttHl_btag_cErr2Up");
  sysShifts.push_back("CMS_ttHl_btag_cErr2Down");
  sysShifts.push_back("CMS_ttHl_thu_shape_ttH_x1Up");
  sysShifts.push_back("CMS_ttHl_thu_shape_ttH_x1Down");
  sysShifts.push_back("CMS_ttHl_thu_shape_ttH_y1Up");
  sysShifts.push_back("CMS_ttHl_thu_shape_ttH_y1Down");
  sysShifts.push_back("CMS_ttHl_thu_shape_ttW_x1Up");
  sysShifts.push_back("CMS_ttHl_thu_shape_ttW_x1Down");
  sysShifts.push_back("CMS_ttHl_thu_shape_ttW_y1Up");
  sysShifts.push_back("CMS_ttHl_thu_shape_ttW_y1Down");
  sysShifts.push_back("CMS_ttHl_thu_shape_ttZ_x1Up");
  sysShifts.push_back("CMS_ttHl_thu_shape_ttZ_x1Down");
  sysShifts.push_back("CMS_ttHl_thu_shape_ttZ_y1Up");
  sysShifts.push_back("CMS_ttHl_thu_shape_ttZ_y1Down");
 */
  sysShifts.push_back(""); // central value

  for ( std::vector<std::string>::const_iterator process = processes.begin();
	process != processes.end(); ++process ) {
    for ( std::vector<std::string>::const_iterator central_or_shift = sysShifts.begin();
	  central_or_shift != sysShifts.end(); ++central_or_shift ) {
      std::cout << "processing: process = " << (*process) << ", central_or_shift = " << (*central_or_shift) << std::endl;

      std::string histogramName_ref, histogramName_test, histogramName_test2, outputFileName;
      if ( !((*central_or_shift) == "" || (*central_or_shift) == "central") ) {
	histogramName_ref = Form("x_%s_%s", process->data(), central_or_shift->data());
	histogramName_test = Form("x_%s_%s", process->data(), central_or_shift->data());
	histogramName_test2 = Form("x_%s_%s", process->data(), central_or_shift->data());
	outputFileName = Form("compareDatacards_%s_%s.png", process->data(), central_or_shift->data());
      } else {
	histogramName_ref = Form("x_%s", process->data());
	histogramName_test = Form("x_%s", process->data());
	histogramName_test2 = Form("x_%s", process->data());
	outputFileName = Form("compareDatacards_%s.png", process->data());
      }
      makePlot(inputFilePath_ref, inputFileName_ref, histogramName_ref, legendEntry_ref, 
	       inputFilePath_test, inputFileName_test, histogramName_test, legendEntry_test, 
	       inputFilePath_test2, inputFileName_test2, histogramName_test2, legendEntry_test2,
	       //"", "", "", "",
	       Form("%s/%s", outputFilePath.data(), outputFileName.data()));
      if ( !((*central_or_shift) == "" || (*central_or_shift) == "central") ) {
	std::string histogramName_ref_shift = Form("x_%s_%s", process->data(), central_or_shift->data());
	std::string histogramName_ref_central = Form("x_%s", process->data());
	std::string histogramName_test_shift = Form("x_%s_%s", process->data(), central_or_shift->data());
	std::string histogramName_test_central = Form("x_%s", process->data());;
	std::string histogramName_test2_shift = Form("x_%s_%s", process->data(), central_or_shift->data()); 
	std::string histogramName_test2_central = Form("x_%s", process->data()); 
	outputFileName = Form("compareDatacards_%s_%s_minus_central.png", process->data(), central_or_shift->data());
	if ( central_or_shift->find("Up") != std::string::npos ) {
	  makePlot_shift_minus_central(inputFilePath_ref, inputFileName_ref, histogramName_ref_shift, histogramName_ref_central, legendEntry_ref, 
				       inputFilePath_test, inputFileName_test, histogramName_test_shift, histogramName_test_central, legendEntry_test, 
				       inputFilePath_test2, inputFileName_test2, histogramName_test2_shift, histogramName_test2_central, legendEntry_test2,
				       //"", "", "", "",
				       Form("%s/%s", outputFilePath.data(), outputFileName.data()));
	} 
	if ( central_or_shift->find("Down") != std::string::npos ) {
	  makePlot_shift_minus_central(inputFilePath_ref, inputFileName_ref, histogramName_ref_central, histogramName_ref_shift, legendEntry_ref, 
				       inputFilePath_test, inputFileName_test, histogramName_test_central, histogramName_test_shift, legendEntry_test, 
				       inputFilePath_test2, inputFileName_test2, histogramName_test2_central, histogramName_test2_shift, legendEntry_test2,
				       //"", "", "", "",
				       Form("%s/%s", outputFilePath.data(), outputFileName.data()));
	}
      }
    }
  }
}


