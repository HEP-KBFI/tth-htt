
#include <TFile.h>
#include <TKey.h>
#include <TString.h>
#include <TCanvas.h>
#include <TH1.h>
#include <TH2.h>
#include <THStack.h>
#include <TAxis.h>
#include <TLegend.h>
#include <TPaveText.h>
#include <TMath.h>
#include <TROOT.h>
#include <TStyle.h>
#include <TList.h>

#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <iomanip>
#include <assert.h>

TFile* openFile(const std::string& inputFilePath, const std::string& inputFileName)
{
  std::string inputFileName_full = inputFilePath;
  if ( inputFileName_full.back() != '/' ) inputFileName_full.append("/");
  inputFileName_full.append(inputFileName);
  TFile* inputFile = new TFile(inputFileName_full.data());
  if ( !inputFile ) {
    std::cerr << "Failed to open input file = " << inputFileName_full << " !!" << std::endl;
    assert(0);
  }

  inputFile->ls();

  return inputFile;
}

TH1* loadHistogram(TFile* inputFile, const std::string& directoryName, const std::string& histogramName)
{
  std::string histogramName_full = directoryName;
  if ( histogramName_full.length() > 0 && histogramName_full.back() != '/' ) histogramName_full.append("/");
  histogramName_full.append(histogramName);
  std::cout << "loading histogram = " << histogramName_full << " from file = " << inputFile->GetName() << std::endl;
  TH1* histogram = dynamic_cast<TH1*>(inputFile->Get(histogramName_full.data()));
  std::cout << "histogram = " << histogram << std::endl;
  if ( !histogram ) {
    std::cerr << "Failed to load histogram = " << histogramName_full << " from file = " << inputFile->GetName() << " --> skipping !!" << std::endl;
    return 0;
  }
  if ( !histogram->GetSumw2N() ) histogram->Sumw2();
  return histogram;
}

TH1* sumHistograms(const TH1* histogram1, const TH1* histogram2)
{
  std::string histogramName_sum = Form("%s_plus_%s", histogram1->GetName(), histogram2->GetName());
  TH1* histogram_sum = (TH1*)histogram1->Clone(histogramName_sum.data());
  if ( !histogram_sum->GetSumw2N() ) histogram_sum->Sumw2();
  histogram_sum->Add(histogram2);
  return histogram_sum;
}

TH1* rebinHistogram(const TH1* histogram, int rebin)
{
  assert(rebin > 1);
  std::string histogramName_rebinned = Form("%s_rebinned", histogram->GetName());
  TH1* histogram_rebinned = (TH1*)histogram->Clone(histogramName_rebinned.data());
  if ( !histogram_rebinned->GetSumw2N() ) histogram_rebinned->Sumw2();
  histogram_rebinned->Rebin(rebin);
  return histogram_rebinned;
}

void divideByBinWidth(TH1* histogram)
{
  int numBins = histogram->GetNbinsX();
  for ( int iBin = 1; iBin <= numBins; ++iBin ) {
    double binContent = histogram->GetBinContent(iBin);
    double binError = histogram->GetBinError(iBin);
    double binWidth = histogram->GetBinWidth(iBin);    
    assert(binWidth >0.); 
    histogram->SetBinContent(iBin, binContent/binWidth);
    histogram->SetBinError(iBin, binError/binWidth);
  }
}

TH1* normalizeHistogram(const TH1* histogram)
{
  std::string histogramName_normalized = Form("%s_normalized", histogram->GetName());
  TH1* histogram_normalized = (TH1*)histogram->Clone(histogramName_normalized.data());
  if ( !histogram_normalized->GetSumw2N() ) histogram_normalized->Sumw2();
  //divideByBinWidth(histogram_normalized);
  double integral = 0.;
  int numBins = histogram_normalized->GetNbinsX();
  for ( int idxBin = 1; idxBin <= numBins; ++idxBin ) {
    //integral += histogram_normalized->GetBinContent(idxBin)*histogram_normalized->GetBinWidth(idxBin);
    integral += histogram_normalized->GetBinContent(idxBin);
  } 
  if ( integral > 0. ) {
    histogram_normalized->Scale(1./integral);
  }  
  return histogram_normalized;
}

void addLabel_CMS_simulation(double x0, double y0)
{
  TPaveText* label_cms = new TPaveText(x0, y0 + 0.0075, x0 + 0.0800, y0 + 0.0725, "NDC");
  label_cms->AddText("CMS");
  label_cms->SetTextFont(61);
  label_cms->SetTextAlign(13);
  label_cms->SetTextSize(0.060);
  label_cms->SetTextColor(1);
  label_cms->SetFillStyle(0);
  label_cms->SetBorderSize(0);
  label_cms->Draw();
  
  TPaveText* label_cms_simulation = new TPaveText(x0 + 0.1450, y0 + 0.0010, x0 + 0.3500, y0 + 0.0610, "NDC");
  label_cms_simulation->AddText("Simulation");
  label_cms_simulation->SetTextFont(52);
  label_cms_simulation->SetTextAlign(13);
  label_cms_simulation->SetTextSize(0.055);
  label_cms_simulation->SetTextColor(1);
  label_cms_simulation->SetFillStyle(0);
  label_cms_simulation->SetBorderSize(0);
  label_cms_simulation->Draw();
}

void makePlot(TH1* histogram1, const std::string& legendEntry1,
              TH1* histogram2, const std::string& legendEntry2,
              TH1* histogram3, const std::string& legendEntry3,
              double xMin, double xMax, const std::string& xAxisTitle, 
              bool useLogScale, double yMin, double yMax, const std::string& yAxisTitle, 
              double legendX0, double legendSizeX, double legendY0, double legendSizeY, double legendTextSize, 
              const std::string& outputFileName)
{
  TCanvas* canvas = new TCanvas("canvas", "canvas", 800, 900);
  canvas->SetFillColor(10);
  canvas->SetBorderSize(2);
  canvas->SetLeftMargin(0.195);
  canvas->SetTopMargin(0.06);
  canvas->SetRightMargin(0.045);
  canvas->SetBottomMargin(0.17);
  //gStyle->SetPadGridX(2); 
  //gStyle->SetPadGridY(2);
  canvas->SetLogy(useLogScale);
  canvas->Draw();

  assert(histogram1);
  histogram1->SetTitle("");
  histogram1->SetStats(false);  
  histogram1->SetMinimum(yMin);
  histogram1->SetMaximum(yMax);  

  gStyle->SetPaintTextFormat("1.2f");

  TAxis* xAxis = histogram1->GetXaxis();
  xAxis->SetRangeUser(xMin, xMax);
  xAxis->SetTitle(xAxisTitle.data());
  xAxis->SetTitleOffset(1.05);
  xAxis->SetTitleSize(0.075);
  xAxis->SetLabelSize(0.055);
  //xAxis->SetLabelOffset(0.01);
  xAxis->SetNdivisions(505);

  TAxis* yAxis = histogram1->GetYaxis();
  //yAxis->SetTitle(yAxisTitle.data());
  yAxis->SetTitle("Relative yield");
  yAxis->SetTitleOffset(1.40);
  yAxis->SetTitleSize(0.070);
  yAxis->SetLabelSize(0.055);
  yAxis->SetLabelOffset(0.01);
  yAxis->SetNdivisions(505);

  //canvas->SetTickx(1);
  //canvas->SetTicky(1);

  int colors[]       = {  2,  1,  1 };
  int markerStyles[] = { 20, 21, 25 };
  int markerSizes[]  = {  2,  2,  2 };
  int lineWidths[]   = {  1,  1,  1 };

  histogram1->SetMarkerColor(colors[0]);
  histogram1->SetMarkerStyle(markerStyles[0]);
  histogram1->SetMarkerSize(markerSizes[0]);
  histogram1->SetLineColor(colors[0]);
  histogram1->SetLineWidth(lineWidths[0]);
  histogram1->Draw("e1p");

  if ( histogram2 ) {
    histogram2->SetMarkerColor(colors[1]);
    histogram2->SetMarkerStyle(markerStyles[1]);
    histogram2->SetMarkerSize(markerSizes[1]);
    histogram2->SetLineColor(colors[1]);
    histogram2->SetLineWidth(lineWidths[1]);
    histogram2->Draw("e1psame");
  }

  if ( histogram3 ) {
    histogram3->SetMarkerColor(colors[2]);
    histogram3->SetMarkerStyle(markerStyles[2]);
    histogram3->SetMarkerSize(markerSizes[2]);
    histogram3->SetLineColor(colors[2]);
    histogram3->SetLineWidth(lineWidths[2]);
    histogram3->Draw("e1psame");
  }

  TLegend* legend = new TLegend(legendX0, legendY0, legendX0 + legendSizeX, legendY0 + legendSizeY, NULL, "brNDC");
  legend->SetFillStyle(0);
  legend->SetBorderSize(0);
  legend->SetFillColor(10);
  legend->SetTextSize(legendTextSize);
  legend->AddEntry(histogram1, legendEntry1.data(), "p");
  if ( histogram2 ) legend->AddEntry(histogram2, legendEntry2.data(), "p");
  if ( histogram3 ) legend->AddEntry(histogram3, legendEntry3.data(), "p");
  legend->Draw();

  addLabel_CMS_simulation(0.2250, 0.9600);
  
  canvas->Update();

  std::string outputFileName_full = Form("./plots/%s", outputFileName.data());
  size_t idx = outputFileName_full.find_last_of('.');
  std::string outputFileName_plot = std::string(outputFileName_full, 0, idx);
  canvas->Print(std::string(outputFileName_plot).append(".pdf").data());
  canvas->Print(std::string(outputFileName_plot).append(".png").data());
  canvas->Print(std::string(outputFileName_plot).append(".root").data());

  delete canvas;
}

void makeBJetPlots_for_HIG_19_008()
{
  gROOT->SetBatch(true);

  TH1::AddDirectory(false);

  std::string inputFilePath  = "/hdfs/local/veelken/ttHAnalysis/2017/2020Jan10/histograms/2lss/Tight_SS/";
  std::string inputFileName_signal = "ttHJetToNonbb_M125_amcatnlo/hadd_stage1_ttHJetToNonbb_M125_amcatnlo_Tight_SS.root";
  TFile* inputFile_signal = openFile(inputFilePath, inputFileName_signal);
  std::string inputFileName_background = "hadd/hadd_stage1_sumTT_Tight_SS.root";
  TFile* inputFile_background = openFile(inputFilePath, inputFileName_background);

  std::vector<std::string> plots;
  plots.push_back("genBJetPt");
  plots.push_back("genBJetEta");
  plots.push_back("numRecBJetsMedium");

  std::map<std::string, std::string> outputFileNames; // key = plot
  outputFileNames["genBJetPt"]         = "genBJetPt.pdf";
  outputFileNames["genBJetEta"]        = "genBJetEta.pdf";
  outputFileNames["numRecBJetsMedium"] = "numRecBJets_medium.pdf";

  std::map<std::string, int> rebin; // key = plot
  rebin["genBJetPt"]                   =   5;
  rebin["genBJetEta"]                  =   2;
  rebin["numRecBJetsMedium"]           =   1;

  std::map<std::string, double> xMin; // key = plot
  xMin["genBJetPt"]                    =   0.;
  xMin["genBJetEta"]                   =  -3.0;
  xMin["numRecBJetsMedium"]            =  -0.5;

  std::map<std::string, double> xMax; // key = plot
  xMax["genBJetPt"]                    = 250.;
  xMax["genBJetEta"]                   =  +3.0;
  xMax["numRecBJetsMedium"]            =  +4.5;

  std::map<std::string, std::string> xAxisTitles; // key = plot
  xAxisTitles["genBJetPt"]             = "p_{T} [GeV]";
  xAxisTitles["genBJetEta"]            = "#eta";
  xAxisTitles["numRecBJetsMedium"]     = "N_{j}";

  std::map<std::string, std::string> yAxisTitles; // key = plot
  yAxisTitles["genBJetPt"]             = "dN/dp_{T} [1/GeV]";
  yAxisTitles["genBJetEta"]            = "dN/d#eta";
  yAxisTitles["numRecBJetsMedium"]     = "dN/dN_{j}";

  std::map<std::string, double> useLogScale; // key = plot
  useLogScale["genBJetPt"]             = false;
  useLogScale["genBJetEta"]            = false;
  useLogScale["numRecBJetsMedium"]     = true;

  std::map<std::string, double> yMin; // key = plot
  yMin["genBJetPt"]                    =   0.;
  yMin["genBJetEta"]                   =   0.;
  yMin["numRecBJetsMedium"]            =   1.01e-3;

  std::map<std::string, double> yMax; // key = plot
  yMax["genBJetPt"]                    =   0.12;
  yMax["genBJetEta"]                   =   0.09;
  yMax["numRecBJetsMedium"]            =   9.99e0;

  for ( std::vector<std::string>::const_iterator plot = plots.begin();
        plot != plots.end(); ++plot ) {
    TH1* histogram_signal = loadHistogram(inputFile_signal, "", Form("%s_nonfake", plot->data()));
    TH1* histogram_background_fake = loadHistogram(inputFile_background, "", Form("%s_fake", plot->data()));
    TH1* histogram_background_nonfake = loadHistogram(inputFile_background, "", Form("%s_nonfake", plot->data()));

    if ( rebin[*plot] > 1 ) {
      histogram_signal = rebinHistogram(histogram_signal, rebin[*plot]);
      histogram_background_fake = rebinHistogram(histogram_background_fake, rebin[*plot]);
      histogram_background_nonfake = rebinHistogram(histogram_background_nonfake, rebin[*plot]);
    }

    if ( (*plot) == "genBJetPt" || (*plot) == "genBJetEta" ) {
      histogram_signal = normalizeHistogram(histogram_signal);
      TH1* histogram_background = sumHistograms(histogram_background_fake, histogram_background_nonfake);
      histogram_background = normalizeHistogram(histogram_background);
      makePlot(
        histogram_signal,             "t#bar{t}H",
        histogram_background,         "t#bar{t}+jets",
        nullptr,                      "",
        xMin[*plot], xMax[*plot], xAxisTitles[*plot], 
        useLogScale[*plot], yMin[*plot], yMax[*plot], yAxisTitles[*plot], 
        0.72, 0.17, 0.74, 0.16, 0.060,
        outputFileNames[*plot]);
      delete histogram_background;
    } else if ( (*plot) == "numRecBJetsMedium" ) {
      histogram_signal = normalizeHistogram(histogram_signal);
      histogram_background_fake = normalizeHistogram(histogram_background_fake);
      histogram_background_nonfake = normalizeHistogram(histogram_background_nonfake);
      makePlot(
        histogram_signal,             "t#bar{t}H",
        histogram_background_nonfake, "t#bar{t}+jets (prompt)",
        histogram_background_fake,    "t#bar{t}+jets (non-prompt)",
        xMin[*plot], xMax[*plot], xAxisTitles[*plot], 
        useLogScale[*plot], yMin[*plot], yMax[*plot], yAxisTitles[*plot], 
        0.41, 0.48, 0.75, 0.18, 0.050,
        outputFileNames[*plot]);
    } else assert(0);
  }

  delete inputFile_signal;
  delete inputFile_background;
}
