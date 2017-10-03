
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
#include <TSystem.h>

#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <iomanip>
#include <assert.h>

/// comapreDatacards v2
///@todo enable > 2 test datacards (need to switch from test & test2 to a vector of tests)

enum { kUndefined, kAbsolute, kRelative };

struct InputFileEntry
{
  InputFileEntry() = default;
  InputFileEntry(const std::string & inputFilePath,
                 const std::string & inputFileName,
                 const std::string & legendEntry)
    : inputFilePath_(inputFilePath)
    , inputFileName_(inputFileName)
    , inputFileFullPath_(
        inputFilePath_ +
        (! inputFilePath_.empty() && inputFilePath_.back() != '/' ? "/" : "") +
        inputFileName_
      )
    , legendEntry_(legendEntry)
  {}
  const std::string inputFilePath_;
  const std::string inputFileName_;
  const std::string inputFileFullPath_;
  const std::string legendEntry_;

  TFile * file_;

};

struct ComparisonEntries
{
  ComparisonEntries() = default;
  ComparisonEntries(const InputFileEntry & ref,
                    const InputFileEntry & test,
                    const InputFileEntry & test2,
                    const std::string & outputFilePath,
                    const std::string & xAxisTitle,
                    const std::string & unit)
    : ref_(ref)
    , test_(test)
    , test2_(test2)
    , outputFilePath_(outputFilePath)
    , xAxisTitle_   (Form("%s%s",           xAxisTitle.c_str(), unit.empty() ? "" : Form(" [%s]",   unit.c_str())))
    , yAxisTitle_   (Form("1/%s%s",         xAxisTitle.c_str(), unit.empty() ? "" : Form(" [1/%s]", unit.c_str())))
    , yAxisTitleErr_(Form("#sigma(1/%s)%s", xAxisTitle.c_str(), unit.empty() ? "" : Form(" [1/%s]", unit.c_str())))
    , yAxisTitleRel_(Form("#Delta 1/%s",    xAxisTitle.c_str()))
  {}
  const InputFileEntry ref_;
  const InputFileEntry test_;
  const InputFileEntry test2_;
  const std::string outputFilePath_;
  const std::string xAxisTitle_;
  const std::string yAxisTitle_;
  const std::string yAxisTitleErr_;
  const std::string yAxisTitleRel_;
};

struct HistogramEntry
{
  HistogramEntry() = default;
  HistogramEntry(TH1 * histogram,
                 const std::string & legendEntry,
                 double integral)
    : histogram_(histogram)
    , legendEntry_(legendEntry)
    , integral_(integral)
  {}
  TH1 * histogram_;
  const std::string legendEntry_;
  const double integral_;
};


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

void
showHistograms(const HistogramEntry & ref,
               const std::vector<HistogramEntry> & tests,
               const std::string & xAxisTitle,
               const std::string & yAxisTitle,
               const std::string & outputFileName,
               double canvasSizeX = 800,
               double canvasSizeY = 900,
               double xAxisOffset = 1.10,
               double yAxisOffset = 1.30,
               bool useLogScale = true,
               double yMin = 1.e-4,
               double yMax = 1.e+4,
               double legendX0 = 0.34,
               double legendY0 = 0.72)
{
  if(! ref.histogram_ || std::count_if(
       tests.begin(), tests.end(), [](const HistogramEntry & entry) { return entry.histogram_; }) == 0)
  {
    return;
  }
  const std::size_t nof_tests = tests.size();
  if(nof_tests > 5)
  {
    std::cout << "Too many histograms to plot: " << nof_tests << '\n';
    return;
  }

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

  const int colors[6]       = { kBlack, kRed, kBlue - 7,  kMagenta - 7, kCyan - 6, kRed - 6 };
  const int markerStyles[6] = { 24, 25, 20, 21, 22, 23 };
  const int markerSizes[6]  = { 1, 1, 1, 1, 1, 1 };

  TLegend* legend = new TLegend(legendX0, legendY0, legendX0 + 0.61, legendY0 + 0.21, "", "brNDC"); 
  legend->SetBorderSize(0);
  legend->SetFillColor(0);

  ref.histogram_->SetTitle("");
  ref.histogram_->SetStats(false);
  ref.histogram_->SetMinimum(yMin);
  ref.histogram_->SetMaximum(yMax);
  ref.histogram_->SetLineColor(colors[0]);
  ref.histogram_->SetLineWidth(2);
  ref.histogram_->SetMarkerColor(colors[0]);
  ref.histogram_->SetMarkerStyle(markerStyles[0]);
  ref.histogram_->SetMarkerSize(markerSizes[0]);
  ref.histogram_->Draw("e1p");
  legend->AddEntry(ref.histogram_, Form("%s: %1.2f", ref.legendEntry_.data(), ref.integral_), "p");

  TAxis* xAxis_top = ref.histogram_->GetXaxis();
  xAxis_top->SetTitle(xAxisTitle.data());
  xAxis_top->SetTitleOffset(xAxisOffset);
  xAxis_top->SetLabelColor(10);
  xAxis_top->SetTitleColor(10);

  TAxis* yAxis_top = ref.histogram_->GetYaxis();
  yAxis_top->SetTitle(yAxisTitle.data());
  yAxis_top->SetTitleOffset(yAxisOffset);

  for(std::size_t i = 0; i < nof_tests; ++i)
  {
    if(tests[i].histogram_)
    {
      tests[i].histogram_->SetLineColor(colors[i + 1]);
      tests[i].histogram_->SetLineWidth(2);
      tests[i].histogram_->SetMarkerColor(colors[i + 1]);
      tests[i].histogram_->SetMarkerStyle(markerStyles[i + 1]);
      tests[i].histogram_->SetMarkerSize(markerSizes[i + 1]);
      tests[i].histogram_->Draw("e1psame");
      legend->AddEntry(tests[i].histogram_, Form("%s: %1.2f", tests[i].legendEntry_.data(), tests[i].integral_), "p");
    }
  }

  legend->Draw();
  canvas->cd();
  bottomPad->Draw();
  bottomPad->cd();

  std::vector<TH1 *> div_refs;
  for(const HistogramEntry & test: tests)
  {
    if(test.histogram_)
    {
      std::string histogramName_div_ref = std::string(test.histogram_->GetName()).append("_div_").append(ref.histogram_->GetName());
      TH1 * histogram_div_ref = compRatioHistogram(histogramName_div_ref, test.histogram_, ref.histogram_);
      if(histogram_div_ref)
      {
        histogram_div_ref->SetTitle("");
        histogram_div_ref->SetStats(false);
        histogram_div_ref->SetMinimum(-0.50);
        histogram_div_ref->SetMaximum(+0.50);

        TAxis* xAxis_bottom = histogram_div_ref->GetXaxis();
        xAxis_bottom->SetTitle(xAxis_top->GetTitle());
        xAxis_bottom->SetLabelColor(1);
        xAxis_bottom->SetTitleColor(1);
        xAxis_bottom->SetTitleOffset(1.20);
        xAxis_bottom->SetTitleSize(0.08);
        xAxis_bottom->SetLabelOffset(0.02);
        xAxis_bottom->SetLabelSize(0.08);
        xAxis_bottom->SetTickLength(0.055);

        TAxis* yAxis_bottom = histogram_div_ref->GetYaxis();
        yAxis_bottom->SetTitle(Form("#frac{%s - %s}{%s}", test.legendEntry_.data(), ref.legendEntry_.data(), ref.legendEntry_.data()));
        yAxis_bottom->SetTitleOffset(0.85);
        yAxis_bottom->SetNdivisions(505);
        yAxis_bottom->CenterTitle();
        yAxis_bottom->SetTitleSize(0.08);
        yAxis_bottom->SetLabelSize(0.08);
        yAxis_bottom->SetTickLength(0.04);

        if(div_refs.size())
        {
          histogram_div_ref->Draw("e1psame");
        }
        else
        {
          histogram_div_ref->Draw("e1p");
        }
        div_refs.push_back(histogram_div_ref);
      }
    }
  }

  TGraph* graph_line = new TGraph(2);
  graph_line->SetPoint(0, xAxis_top->GetXmin(), 0.);
  graph_line->SetPoint(1, xAxis_top->GetXmax(), 0.);
  graph_line->SetLineColor(8);
  graph_line->SetLineWidth(1);
  graph_line->Draw("L");

  for(TH1 * histogram_div_ref: div_refs)
  {
    histogram_div_ref->Draw("e1psame");
  }
  
  canvas->Update();
  const std::size_t idx = outputFileName.find_last_of('.');
  std::string outputFileName_plot(outputFileName, 0, idx);
  if(useLogScale)
  {
    outputFileName_plot.append("_log");
  }
  else
  {
    outputFileName_plot.append("_linear");
  }
  if(idx != std::string::npos)
  {
    canvas->Print(std::string(outputFileName_plot).append(std::string(outputFileName, idx)).data());
  }
  canvas->Print(std::string(outputFileName_plot).append(".png").data());
  
  delete legend;
  for(TH1 * histogram_div_ref: div_refs)
  {
    if(histogram_div_ref)
    {
      delete histogram_div_ref;
    }
  }
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

void makePlot(const ComparisonEntries & entries,
              const std::string & outputFileName,
              const std::string & histogramName)
{
  std::cout << "<makePlot_shift_minus_central>:\n";

  TFile* inputFile_ref = new TFile(entries.ref_.inputFileFullPath_.c_str());
  TH1* histogram_ref = loadHistogram(inputFile_ref, histogramName);
  const double integral_ref = compIntegral(histogram_ref);
  divideByBinWidth(histogram_ref);

  TFile* inputFile_test = entries.ref_.inputFileFullPath_ != entries.test_.inputFileFullPath_ ?
    new TFile(entries.test_.inputFileFullPath_.c_str()) :
    inputFile_ref
  ;
  TH1* histogram_test = loadHistogram(inputFile_test, histogramName);
  const double integral_test = compIntegral(histogram_test);
  divideByBinWidth(histogram_test);

  TFile* inputFile_test2 = nullptr;
  TH1* histogram_test2   = nullptr;
  double integral_test2 = -1.;
  if(! entries.test2_.inputFileFullPath_.empty())
  {
    inputFile_test2 = [&]() -> TFile *
    {
      if(entries.ref_.inputFileFullPath_ == entries.test2_.inputFileFullPath_)
      {
        return inputFile_ref;
      }
      if(entries.test_.inputFileFullPath_ == entries.test2_.inputFileFullPath_)
      {
        return inputFile_test;
      }
      return new TFile(entries.test2_.inputFileFullPath_.c_str());
    }();
    histogram_test2 = loadHistogram(inputFile_test2, histogramName);
    integral_test2  = compIntegral(histogram_test2);
    divideByBinWidth(histogram_test2);
  }
  
  const HistogramEntry ref(histogram_ref, entries.ref_.legendEntry_, integral_ref);
  const std::vector<HistogramEntry> tests = {
    { histogram_test,  entries.test_.legendEntry_,  integral_test  },
    { histogram_test2, entries.test2_.legendEntry_, integral_test2 },
  };

  showHistograms(ref, tests, entries.xAxisTitle_, entries.yAxisTitle_, outputFileName);

  TH1* histogramErr_ref   = compHistogramErr(histogram_ref);
  TH1* histogramErr_test  = compHistogramErr(histogram_test);
  TH1* histogramErr_test2 = histogram_test2 ? compHistogramErr(histogram_test2) : nullptr;
  const std::string outputFileNameErr(TString(outputFileName.data()).ReplaceAll(".png", "_Err.png").Data());

  const HistogramEntry ref_err(histogramErr_ref, entries.ref_.legendEntry_, -1.);
  const std::vector<HistogramEntry> tests_err = {
    { histogramErr_test,  entries.test_.legendEntry_,  -1. },
    { histogramErr_test2, entries.test2_.legendEntry_, -1. }
  };

  showHistograms(ref_err, tests_err, entries.xAxisTitle_, entries.yAxisTitleErr_, outputFileNameErr);

  delete histogramErr_ref;
  delete histogramErr_test;
  delete histogramErr_test2;
  
  delete inputFile_ref;
  if(inputFile_test != inputFile_ref)
  {
    delete inputFile_test;
  }
  if(inputFile_test2 != inputFile_ref && inputFile_test2 != inputFile_test)
  {
    delete inputFile_test2;
  }
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

void makePlot_shift_minus_central(const ComparisonEntries & entries,
                                  const std::string & histogramName_central,
                                  const std::string & histogramName_shift,
                                  const std::string & outputFileName)
{
  std::cout << "<makePlot_shift_minus_central>:\n";

  TFile* inputFile_ref = new TFile(entries.ref_.inputFileFullPath_.data());
  TH1* histogram_ref_shift   = loadHistogram(inputFile_ref, histogramName_shift);
  TH1* histogram_ref_central = loadHistogram(inputFile_ref, histogramName_central);
  TH1* histogram_ref_shift_minus_centralAbs = nullptr;
  TH1* histogram_ref_shift_minus_centralRel = nullptr;
  double integral_ref = -1.;
  if (histogram_ref_shift && histogram_ref_central)
  {
    const std::string histogramName_ref_shift_minus_central = Form("%s_minus_%s", histogram_ref_shift->GetName(), histogram_ref_central->GetName());
    const std::string histogramName_ref_shift_minus_centralAbs = Form("%sAbs", histogramName_ref_shift_minus_central.data());
    const std::string histogramName_ref_shift_minus_centralRel = Form("%sRel", histogramName_ref_shift_minus_central.data());
    histogram_ref_shift_minus_centralAbs = subtractHistograms(histogramName_ref_shift_minus_centralAbs, histogram_ref_shift, histogram_ref_central, kAbsolute);
    histogram_ref_shift_minus_centralRel = subtractHistograms(histogramName_ref_shift_minus_centralRel, histogram_ref_shift, histogram_ref_central, kRelative);
    integral_ref = compIntegral(histogram_ref_shift_minus_centralAbs);
    std::cout << " integral_ref = " << integral_ref << '\n';
    divideByBinWidth(histogram_ref_shift_minus_centralAbs);
  }

  TFile* inputFile_test = new TFile(entries.test_.inputFileFullPath_.data());
  TH1* histogram_test_shift   = loadHistogram(inputFile_test, histogramName_shift);
  TH1* histogram_test_central = loadHistogram(inputFile_test, histogramName_central);
  TH1* histogram_test_shift_minus_centralAbs = nullptr;
  TH1* histogram_test_shift_minus_centralRel = nullptr;
  double integral_test = -1.;
  if (histogram_test_shift && histogram_test_central)
  {
    const std::string histogramName_test_shift_minus_central = Form("%s_minus_%s", histogram_test_shift->GetName(), histogram_test_central->GetName());
    const std::string histogramName_test_shift_minus_centralAbs = Form("%sAbs", histogramName_test_shift_minus_central.data());
    const std::string histogramName_test_shift_minus_centralRel = Form("%sRel", histogramName_test_shift_minus_central.data());
    histogram_test_shift_minus_centralAbs = subtractHistograms(histogramName_test_shift_minus_centralAbs, histogram_test_shift, histogram_test_central, kAbsolute);
    histogram_test_shift_minus_centralRel = subtractHistograms(histogramName_test_shift_minus_centralRel, histogram_test_shift, histogram_test_central, kRelative);
    integral_test = compIntegral(histogram_test_shift_minus_centralAbs);
    std::cout << " integral_test = " << integral_test << '\n';
    divideByBinWidth(histogram_test_shift_minus_centralAbs);
  }

  TFile* inputFile_test2 = nullptr;
  TH1* histogram_test2_shift_minus_centralAbs = nullptr;
  TH1* histogram_test2_shift_minus_centralRel = nullptr;
  double integral_test2 = -1.;
  if(! entries.test2_.inputFileFullPath_.empty())
  {
    inputFile_test2 = entries.test2_.inputFileFullPath_ != entries.ref_.inputFileFullPath_ ?
      new TFile(entries.test2_.inputFileFullPath_.data()) :
      inputFile_ref
    ;
    TH1* histogram_test2_shift   = loadHistogram(inputFile_test2, histogramName_shift);
    TH1* histogram_test2_central = loadHistogram(inputFile_test2, histogramName_central);
    if(histogram_test2_shift && histogram_test2_central)
    {
      const std::string histogramName_test2_shift_minus_central = Form("%s_minus_%s", histogram_test2_shift->GetName(), histogram_test2_central->GetName());
      const std::string histogramName_test2_shift_minus_centralAbs = Form("%sAbs", histogramName_test2_shift_minus_central.data());
      const std::string histogramName_test2_shift_minus_centralRel = Form("%sRel", histogramName_test2_shift_minus_central.data());
      histogram_test2_shift_minus_centralAbs = subtractHistograms(histogramName_test2_shift_minus_centralAbs, histogram_test2_shift, histogram_test2_central, kAbsolute);
      histogram_test2_shift_minus_centralRel = subtractHistograms(histogramName_test2_shift_minus_centralRel, histogram_test2_shift, histogram_test2_central, kRelative);
      integral_test2 = compIntegral(histogram_test2_shift_minus_centralAbs);
      std::cout << " integral_test = " << integral_test2 << '\n';
      divideByBinWidth(histogram_test2_shift_minus_centralAbs);
    }
  }

  const std::size_t idx = outputFileName.find_last_of('.');
  const std::string outputFileName_abs = std::string(outputFileName, 0, idx)
    .append("_absolute")
    .append(idx != std::string::npos ? std::string(outputFileName, idx) : "")
  ;
  const std::string outputFileName_rel = std::string(outputFileName, 0, idx)
    .append("_relative")
    .append(idx != std::string::npos ? std::string(outputFileName, idx) : "")
  ;

  const HistogramEntry ref(histogram_ref_shift_minus_centralAbs, entries.ref_.legendEntry_, integral_ref);
  const std::vector<HistogramEntry> tests_abs = {
    { histogram_test_shift_minus_centralAbs,  entries.test_.legendEntry_,  integral_test },
    { histogram_test2_shift_minus_centralAbs, entries.test2_.legendEntry_, integral_test2 }
  };
  const std::vector<HistogramEntry> tests_rel = {
    { histogram_test_shift_minus_centralRel,  entries.test_.legendEntry_,  integral_test },
    { histogram_test2_shift_minus_centralRel, entries.test2_.legendEntry_, integral_test2 }
  };

  showHistograms(ref, tests_abs, entries.xAxisTitle_, entries.yAxisTitle_,    outputFileName_abs);
  showHistograms(ref, tests_rel, entries.xAxisTitle_, entries.yAxisTitleRel_, outputFileName_rel);

  delete inputFile_ref;
  if(inputFile_test != inputFile_ref)
  {
    delete inputFile_test;
  }
  if(inputFile_test2 != inputFile_ref && inputFile_test2 != inputFile_test)
  {
    delete inputFile_test2;
  }
}

void compareDatacards_run(const ComparisonEntries & entry)
{
  const Int_t mkdir_exit_code = gSystem -> Exec(Form("mkdir -p %s", entry.outputFilePath_.c_str()));
  if(mkdir_exit_code)
  {
    std::cerr << "Could not create directory " << entry.outputFilePath_ << '\n';
    return;
  }

  const std::vector<std::string> processes = {
    "data_obs",
    "ttH_hww"
    "ttH_htt",
    "ttH_hzz",
    "TTW",
    "TTZ",
    "EWK",
    "Rares",
    "fakes_data",
    "flips_data",
    "TT"
  };

  const std::vector<std::string> sysShifts = {
    /*
    "CMS_ttHl_tauESUp",
    "CMS_ttHl_tauESDown",
    "CMS_ttHl_JESUp",
    "CMS_ttHl_JESDown",
    "CMS_ttHl_FRe_shape_2lss_anticorr1Up",
    "CMS_ttHl_FRe_shape_2lss_anticorr1Down",
    "CMS_ttHl_FRe_shape_2lss_corr1Up",
    "CMS_ttHl_FRe_shape_2lss_corr1Down",
    "CMS_ttHl_FRm_shape_2lss_anticorr1Up",
    "CMS_ttHl_FRm_shape_2lss_anticorr1Down",
    "CMS_ttHl_FRm_shape_2lss_corr1Up",
    "CMS_ttHl_FRm_shape_2lss_corr1Down",
    "CMS_ttHl_btag_HFUp",
    "CMS_ttHl_btag_HFDown",
    "CMS_ttHl_btag_HFStats1Up",
    "CMS_ttHl_btag_HFStats1Down",
    "CMS_ttHl_btag_HFStats2Up",
    "CMS_ttHl_btag_HFStats2Down",
    "CMS_ttHl_btag_LFUp",
    "CMS_ttHl_btag_LFDown",
    "CMS_ttHl_btag_LFStats1Up",
    "CMS_ttHl_btag_LFStats1Down",
    "CMS_ttHl_btag_LFStats2Up",
    "CMS_ttHl_btag_LFStats2Down",
    "CMS_ttHl_btag_cErr1Up",
    "CMS_ttHl_btag_cErr1Down",
    "CMS_ttHl_btag_cErr2Up",
    "CMS_ttHl_btag_cErr2Down",
    "CMS_ttHl_thu_shape_ttH_x1Up",
    "CMS_ttHl_thu_shape_ttH_x1Down",
    "CMS_ttHl_thu_shape_ttH_y1Up",
    "CMS_ttHl_thu_shape_ttH_y1Down",
    "CMS_ttHl_thu_shape_ttW_x1Up",
    "CMS_ttHl_thu_shape_ttW_x1Down",
    "CMS_ttHl_thu_shape_ttW_y1Up",
    "CMS_ttHl_thu_shape_ttW_y1Down",
    "CMS_ttHl_thu_shape_ttZ_x1Up",
    "CMS_ttHl_thu_shape_ttZ_x1Down",
    "CMS_ttHl_thu_shape_ttZ_y1Up",
    "CMS_ttHl_thu_shape_ttZ_y1Down",
    */
    "" // central value
  };

  for(const std::string & process: processes)
  {
    for(const std::string & central_or_shift: sysShifts)
    {
      std::cout << "processing: process = " << process << ", central_or_shift = " << central_or_shift << '\n';

      const std::string histogramName_central = Form("x_%s",    process.data());
      const std::string histogramName_shifted = Form("x_%s_%s", process.data(), central_or_shift.data());
      const bool is_central = central_or_shift == "" || central_or_shift == "central";

      const std::string histogramName = is_central ? histogramName_central : histogramName_shifted;
      const std::string outputFileName = is_central ?
        Form("compareDatacards_%s.png",    process.data()) :
        Form("compareDatacards_%s_%s.png", process.data(), central_or_shift.data())
      ;

      makePlot(entry, Form("%s/%s", entry.outputFilePath_.data(), outputFileName.data()), histogramName);
      if(! is_central)
      {
        const std::string outputFileName_minus_central = Form(
          "%s/compareDatacards_%s_%s_minus_central.png", entry.outputFilePath_.data(), process.data(), central_or_shift.data()
        );
        if(central_or_shift.find("Up") != std::string::npos)
        {
          makePlot_shift_minus_central(entry, histogramName_central, histogramName_shifted, outputFileName_minus_central);
        }
        if(central_or_shift.find("Down") != std::string::npos)
        {
          makePlot_shift_minus_central(entry, histogramName_shifted, histogramName_central, outputFileName_minus_central);
        }
      } // ! is_central
    } // for central_or_shift
  } // for process
}

void compareDatacards()
{
    gROOT->SetBatch(true);

    TH1::AddDirectory(false);

    const std::vector<std::array<std::string, 4>> discriminatingVariables = {
      { "1l_2tau_EventCounter",               "Events",                        ""    },
      { "1l_2tau_SS_EventCounter",            "Events (SS)",                   ""    },
      { "1l_2tau_SS_mTauTauVis",              "m_{#tau#tau} (SS)",             "GeV" },
      { "1l_2tau_SS_mvaDiscr_1l_2tau",        "MVA discr 1l2#tau (SS)",        ""    },
      { "1l_2tau_SS_mvaOutput_1l_2tau_ttbar", "MVA out 1l2#tau t#bar{t} (SS)", ""    },
      { "1l_2tau_SS_numJets",                 "#Jets",                         ""    },
      { "1l_2tau_mTauTauVis",                 "m_{#tau#tau}",                  "GeV" },
      { "1l_2tau_mvaDiscr_1l_2tau",           "MVA discr 1l2#tau",             ""    },
      { "1l_2tau_mvaOutput_1l_2tau_ttbar",    "MVA out 1l2#tau t#bar{t}",      ""    },
      { "1l_2tau_numJets",                    "#Jets",                         ""    }
    };
    std::vector<ComparisonEntries> entries;
    const std::string ref_path  = "/home/karl/ttHAnalysis/2016/2017Sep27/datacards/1l_2tau/";
    const std::string test_path = "/home/karl/ttHAnalysis/2016/2017Sep30/datacards/1l_2tau/";
    for(const std::array<std::string, 4> & var: discriminatingVariables)
    {
      const InputFileEntry ref  = {ref_path,  Form("prepareDatacards_%s.root", var.at(0).c_str()), "Tallinn"};
      const InputFileEntry test = {test_path, Form("prepareDatacards_%s.root", var.at(0).c_str()), "Production Ntuples"};
      const std::string outputFilePath = Form("/home/karl/sandbox/plots/plots_%s", var.at(0).c_str());
      entries.push_back({ref, test, {}, outputFilePath, var.at(1), var.at(2)});
    }

    // Example usage when comparing individual datacards:
//    const std::vector<ComparisonEntries> entries = {
//      {
//        // path where the datacard is stored                          file name of the datacard                   plot label
//        { "/home/karl/ttHAnalysis/2016/2017Sep27/datacards/1l_2tau/", "prepareDatacards_1l_2tau_mTauTauVis.root", "Tallinn" },            // ref
//        { "/home/karl/ttHAnalysis/2016/2017Sep30/datacards/1l_2tau/", "prepareDatacards_1l_2tau_mTauTauVis.root", "Production Ntuples" }, // test
//        { "", "", "" },                                                                                                                   // test2
//        "/home/karl/sandbox/plots_1l_2tau_mTauTauVis", // where to put the plots
//        "m_{#tau#tau} [GeV]",                          // x axis label
//        "GeV"                                          // unit
//      }
//    };

    for(const ComparisonEntries & entry: entries)
    {
      compareDatacards_run(entry);
    }
}
