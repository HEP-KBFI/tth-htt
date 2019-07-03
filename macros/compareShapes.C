
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

TH1* loadHistogram(TFile* inputFile, const std::string& directory, const std::string& histogramName)
{
  TString histogramName_full = directory.data();
  if ( !histogramName_full.EndsWith("/") ) histogramName_full.Append("/");
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

double compIntegral(const TH1* histogram)
{
  if ( !histogram ) return -1.;
  double integral = 0.;
  int numBins = histogram->GetNbinsX();
  for ( int idxBin = 1; idxBin <= numBins; ++idxBin ) {
    double binContent = histogram->GetBinContent(idxBin);
    integral += binContent;
  }
  return integral;
}

void divideByBinWidth(TH1* histogram)
{
  if ( !histogram ) return;
  TAxis* xAxis = histogram->GetXaxis();
  int numBins = xAxis->GetNbins();
  for ( int idxBin = 1; idxBin <= numBins; ++idxBin ) {
    double binContent = histogram->GetBinContent(idxBin);
    double binError = histogram->GetBinError(idxBin);
    double binWidth = xAxis->GetBinWidth(idxBin);
    histogram->SetBinContent(idxBin, binContent/binWidth);
    histogram->SetBinError(idxBin, binError/binWidth);
  }
}

struct processEntry
{
  processEntry(const std::string& process, int color, const std::string& legendEntry)
    : process_(process)
    , color_(color)
    , legendEntry_(legendEntry)
    , histogram_(0)
  {}
  ~processEntry();
  void setHistogram(TH1* histogram) 
  { 
    histogram_ = histogram; 
  }
  TH1* getHistogram() 
  { 
    return histogram_; 
  }
  std::string process_;
  int color_;
  std::string legendEntry_;
  TH1* histogram_;
};

void
showHistograms(std::vector<processEntry*>& processes,
               const std::string& xAxisTitle,
               const std::string& yAxisTitle,
               const std::string& outputFileName,
               double canvasSizeX = 1200,
               double canvasSizeY = 900,
               double xAxisOffset = 1.35,
               double yAxisOffset = 1.55,
               bool useLogScale = true,
               double yMin = 1.e-4,
               double yMax = 1.e+4,
               double legendX0 = 0.73,
               double legendY0 = 0.68)
{
  TCanvas* canvas = new TCanvas("canvas", "canvas", canvasSizeX, canvasSizeY);
  canvas->SetFillColor(10);
  canvas->SetTopMargin(0.04);
  canvas->SetLeftMargin(0.18);
  canvas->SetBottomMargin(0.17);
  canvas->SetRightMargin(0.05);
  canvas->SetLogy(useLogScale);
  
  TLegend* legend = new TLegend(legendX0, legendY0, 0.93, 0.93, "", "brNDC");
  legend->SetBorderSize(0);
  legend->SetFillColor(0);
  legend->SetTextSize(0.055);

  for ( std::vector<processEntry*>::iterator process = processes.begin();
	process != processes.end(); ++process ) {
    TH1* histogram = (*process)->getHistogram();

    bool isFirst = (process == processes.begin());
    if ( isFirst ) {
      histogram->SetTitle("");
      histogram->SetStats(false);
      histogram->SetMinimum(yMin);
      histogram->SetMaximum(yMax);
      
      TAxis* xAxis = histogram->GetXaxis();
      xAxis->SetTitle(xAxisTitle.data());
      xAxis->SetTitleOffset(xAxisOffset);
      xAxis->SetTitleSize(0.060);
      xAxis->SetLabelOffset(0.02);
      xAxis->SetLabelSize(0.060);
      xAxis->SetTickLength(0.050);

      TAxis* yAxis = histogram->GetYaxis();
      yAxis->SetTitle(yAxisTitle.data());
      yAxis->SetTitleOffset(yAxisOffset);
      yAxis->SetTitleSize(0.060);
      yAxis->SetLabelOffset(0.02);
      yAxis->SetLabelSize(0.060);
      yAxis->SetTickLength(0.050);
    }

    histogram->SetLineColor((*process)->color_);
    histogram->SetLineWidth(2);
    histogram->SetMarkerColor((*process)->color_);
    histogram->SetMarkerStyle(20);
    histogram->SetMarkerSize(3);
    
    if ( isFirst ) {
      histogram->Draw("hist");
    } else {
      histogram->Draw("histsame");
    }

    legend->AddEntry(histogram, (*process)->legendEntry_.data(), "l");
  }

  legend->Draw();
  
  canvas->Update();

  const std::size_t idx = outputFileName.find_last_of('.');
  std::string outputFileName_plot(outputFileName, 0, idx);
  if ( useLogScale ) outputFileName_plot.append("_log");
  else outputFileName_plot.append("_linear");
  canvas->Print(std::string(outputFileName_plot).append(".pdf").data());
  canvas->Print(std::string(outputFileName_plot).append(".png").data());
  
  delete legend;
  delete canvas;  
}

struct categoryEntry
{
  categoryEntry(const std::string& directory, const std::string& label)
    : directory_(directory)
    , label_(label)
  {}
  ~categoryEntry() {}
  std::string directory_;
  std::string label_;
};

void compareShapes()
{
  gROOT->SetBatch(true);

  TH1::AddDirectory(false);

  std::string inputFilePath = "/hdfs/local/veelken/ttHAnalysis/2016/2017Jan12/histograms/LeptonFakeRate/";
  std::string inputFileName = "addBackground_LeptonFakeRate.root";
  TString inputFileName_full = inputFilePath.data();
  if ( !inputFileName_full.EndsWith("/") ) inputFileName_full.Append("/");
  inputFileName_full.Append(inputFileName.data());
  TFile* inputFile = new TFile(inputFileName_full.Data());
  if ( !inputFile ) {
    std::cerr << "Failed to open input file = '" << inputFileName_full.Data() << "' !!" << std::endl;
    assert(0);
  }
  
  std::vector<processEntry*> processes; // key = channel
  processes.push_back(new processEntry("EWKl",          610, "EWK"));           // purple
  processes.push_back(new processEntry("Raresl",        851, "Rares"));         // light blue
  processes.push_back(new processEntry("TTl",            16, "t#bar{t}+jets")); // gray
  processes.push_back(new processEntry("fakes_data",      1, "Fakes"));         // black
    
  std::vector<categoryEntry*> categories;
  categories.push_back(new categoryEntry(
    "LeptonFakeRate/numerator/electrons_tight/absEtaLt1_5/Pt20_0to30_0",
    "electrons_tight_absEtaLt1_5_Pt20_0to30_0_shapes"));
  categories.push_back(new categoryEntry(
    "LeptonFakeRate/numerator/electrons_tight/absEtaLt1_5/Pt30_0to45_0",
    "electrons_tight_absEtaLt1_5_Pt30_0to45_0_shapes"));
  categories.push_back(new categoryEntry(
    "LeptonFakeRate/numerator/electrons_tight/absEtaLt1_5/Pt45_0to65_0",
    "electrons_tight_absEtaLt1_5_Pt45_0to65_0_shapes"));
  categories.push_back(new categoryEntry(
    "LeptonFakeRate/numerator/electrons_tight/absEtaLt1_5/Pt65_0to100000_0",
    "electrons_tight_absEtaLt1_5_Pt65_0to100000_0_shapes"));
  categories.push_back(new categoryEntry(
    "LeptonFakeRate/numerator/electrons_tight/absEta1_5to9_9/Pt20_0to30_0",
    "electrons_tight_absEta1_5to9_9_Pt20_0to30_0_shapes"));
  categories.push_back(new categoryEntry(
    "LeptonFakeRate/numerator/electrons_tight/absEta1_5to9_9/Pt30_0to45_0",
    "electrons_tight_absEta1_5to9_9_Pt30_0to45_0_shapes"));
  categories.push_back(new categoryEntry(
    "LeptonFakeRate/numerator/electrons_tight/absEta1_5to9_9/Pt45_0to65_0",
    "electrons_tight_absEta1_5to9_9_Pt45_0to65_0_shapes"));
  categories.push_back(new categoryEntry(
    "LeptonFakeRate/numerator/electrons_tight/absEta1_5to9_9/Pt65_0to100000_0",
    "electrons_tight_absEta1_5to9_9_Pt65_0to100000_0_shapes"));
  categories.push_back(new categoryEntry(
    "LeptonFakeRate/numerator/muons_tight/absEtaLt1_5/Pt15_0to20_0",
    "muons_tight_absEtaLt1_5_Pt15_0to20_0_shapes"));
  categories.push_back(new categoryEntry(
    "LeptonFakeRate/numerator/muons_tight/absEtaLt1_5/Pt20_0to30_0",
    "muons_tight_absEtaLt1_5_Pt20_0to30_0_shapes"));
  categories.push_back(new categoryEntry(
    "LeptonFakeRate/numerator/muons_tight/absEtaLt1_5/Pt30_0to45_0",
    "muons_tight_absEtaLt1_5_Pt30_0to45_0_shapes"));
  categories.push_back(new categoryEntry(
    "LeptonFakeRate/numerator/muons_tight/absEtaLt1_5/Pt45_0to65_0",
    "muons_tight_absEtaLt1_5_Pt45_0to65_0_shapes"));
  categories.push_back(new categoryEntry(
    "LeptonFakeRate/numerator/muons_tight/absEtaLt1_5/Pt65_0to100000_0",
    "muons_tight_absEtaLt1_5_Pt65_0to100000_0_shapes"));
  categories.push_back(new categoryEntry(
    "LeptonFakeRate/numerator/muons_tight/absEta1_5to9_9/Pt15_0to20_0",
    "muons_tight_absEta1_5to9_9_Pt15_0to20_0_shapes"));
  categories.push_back(new categoryEntry(
    "LeptonFakeRate/numerator/muons_tight/absEta1_5to9_9/Pt20_0to30_0",
    "muons_tight_absEta1_5to9_9_Pt20_0to30_0_shapes"));
  categories.push_back(new categoryEntry(
    "LeptonFakeRate/numerator/muons_tight/absEta1_5to9_9/Pt30_0to45_0",
    "muons_tight_absEta1_5to9_9_Pt30_0to45_0_shapes"));
  categories.push_back(new categoryEntry(
    "LeptonFakeRate/numerator/muons_tight/absEta1_5to9_9/Pt45_0to65_0",
    "muons_tight_absEta1_5to9_9_Pt45_0to65_0_shapes"));
  categories.push_back(new categoryEntry(
    "LeptonFakeRate/numerator/muons_tight/absEta1_5to9_9/Pt65_0to100000_0",
    "muons_tight_absEta1_5to9_9_Pt65_0to100000_0_shapes"));

  std::string histogramName = "mT_fix_L";
    
  for ( std::vector<categoryEntry*>::const_iterator category = categories.begin();
	category != categories.end(); ++category ) {
    for ( std::vector<processEntry*>::iterator process = processes.begin();
	  process != processes.end(); ++process ) {
      TH1* histogram = loadHistogram(inputFile, Form("%s/%s", (*category)->directory_.data(), (*process)->process_.data()), histogramName);
      double integral = compIntegral(histogram);
      if ( integral > 0. ) histogram->Scale(1./integral);
      divideByBinWidth(histogram);
      (*process)->setHistogram(histogram);
    }
    
    std::string outputFileName = Form("plots/compareShapes_%s.pdf", (*category)->label_.data());
    showHistograms(processes,
		   "m_{T}^{fix} [GeV]",
		   "dN/dm_{T}^{fix} [1/GeV]",
		   outputFileName,
		   1200,
		   900,
		   1.35,
		   1.55,
		   true,
		   1.e-5,
		   1.e-1,
		   0.73,
		   0.68);
  }
  
  delete inputFile;
}
