
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

TH1* loadHistogram(TFile* inputFile, const std::string& histogramName)
{
  TH1* histogram = dynamic_cast<TH1*>(inputFile->Get(histogramName.data()));
  if ( !histogram ) {
    std::cerr << "Failed to load histogram = " << histogramName << " from file = " << inputFile->GetName() << " !!" << std::endl;
    assert(0);
  }
  if ( !histogram->GetSumw2N() ) histogram->Sumw2();
  return histogram;
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

void showHistograms(double canvasSizeX, double canvasSizeY,
		    TH1* histogram1, const std::string& legendEntry1, 
		    TH1* histogram2, const std::string& legendEntry2, 
		    TH1* histogram3, const std::string& legendEntry3, 
		    TH1* histogram4, const std::string& legendEntry4, 
		    TH1* histogram5, const std::string& legendEntry5, 
		    TH1* histogram6, const std::string& legendEntry6, 
		    const std::string& xAxisTitle, double xAxisOffset,
		    bool useLogScale, double yMin, double yMax, const std::string& yAxisTitle, double yAxisOffset,
		    double legendX0, double legendY0, 
		    const std::string& outputFileName)
{
  if ( !(histogram1 && histogram2) ) return;

  TCanvas* canvas = new TCanvas("canvas", "canvas", canvasSizeX, canvasSizeY);
  canvas->SetFillColor(10);
  canvas->SetBorderSize(2);
  canvas->SetLeftMargin(0.12);
  canvas->SetBottomMargin(0.12);

  //int colors[6] = { kBlack, kGreen - 6, kBlue - 7,  kMagenta - 7, kCyan - 6, kRed - 6 };
  int colors[6] = { kBlack, kRed, kBlue - 7,  kMagenta - 7, kCyan - 6, kRed - 6 };
  int markerStyles[6] = { 24, 25, 20, 21, 22, 23 };
  int markerSizes[6] = { 1, 1, 1, 1, 1, 1 };

  TLegend* legend = new TLegend(legendX0, legendY0, legendX0 + 0.61, legendY0 + 0.21, "", "brNDC"); 
  legend->SetBorderSize(0);
  legend->SetFillColor(0);

  histogram1->SetTitle("");
  histogram1->SetStats(false);
  histogram1->SetMinimum(yMin);
  histogram1->SetMaximum(yMax);
  histogram1->SetLineColor(colors[0]);
  histogram1->SetLineWidth(2);
  histogram1->SetMarkerColor(colors[0]);
  histogram1->SetMarkerStyle(markerStyles[0]);
  histogram1->SetMarkerSize(markerSizes[0]);
  histogram1->Draw("e1p");
  legend->AddEntry(histogram1, legendEntry1.data(), "p");

  TAxis* xAxis = histogram1->GetXaxis();
  xAxis->SetTitle(xAxisTitle.data());
  xAxis->SetTitleOffset(xAxisOffset);

  TAxis* yAxis = histogram1->GetYaxis();
  yAxis->SetTitle(yAxisTitle.data());
  yAxis->SetTitleOffset(yAxisOffset);

  if ( histogram2 ) {
    histogram2->SetLineColor(colors[1]);
    histogram2->SetLineWidth(2);
    histogram2->SetMarkerColor(colors[1]);
    histogram2->SetMarkerStyle(markerStyles[1]);
    histogram2->SetMarkerSize(markerSizes[1]);
    histogram2->Draw("e1psame");
    legend->AddEntry(histogram2, legendEntry2.data(), "p");
  }

  if ( histogram3 ) {
    histogram3->SetLineColor(colors[2]);
    histogram3->SetLineWidth(2);
    histogram3->SetMarkerColor(colors[2]);
    histogram3->SetMarkerStyle(markerStyles[2]);
    histogram3->SetMarkerSize(markerSizes[2]);
    histogram3->Draw("e1psame");
    legend->AddEntry(histogram3, legendEntry3.data(), "p");
  }

  if ( histogram4 ) {
    histogram4->SetLineColor(colors[3]);
    histogram4->SetLineWidth(2);
    histogram4->SetMarkerColor(colors[3]);
    histogram4->SetMarkerStyle(markerStyles[3]);
    histogram4->SetMarkerSize(markerSizes[3]);
    histogram4->Draw("e1psame");
    legend->AddEntry(histogram4, legendEntry4.data(), "p");
  }

  if ( histogram5 ) {
    histogram5->SetLineColor(colors[4]);
    histogram5->SetLineWidth(2);
    histogram5->SetMarkerColor(colors[4]);
    histogram5->SetMarkerStyle(markerStyles[4]);
    histogram5->SetMarkerSize(markerSizes[4]);
    histogram5->Draw("e1psame");
    legend->AddEntry(histogram5, legendEntry5.data(), "p");
  }

  if ( histogram6 ) {
    histogram6->SetLineColor(colors[5]);
    histogram6->SetLineWidth(2);
    histogram6->SetMarkerColor(colors[5]);
    histogram6->SetMarkerStyle(markerStyles[5]);
    histogram6->SetMarkerSize(markerSizes[5]);
    histogram6->Draw("e1psame");
    legend->AddEntry(histogram6, legendEntry6.data(), "p");
  }

  legend->Draw();
  
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
  delete canvas;  
}

double compIntegral(const TH1* histogram, bool includeUnderflowBin = true, bool includeOverflowBin = true)
{
  int idxFirstBin = ( includeUnderflowBin ) ? 0 : 1;
  int idxLastBin = ( includeOverflowBin ) ? histogram->GetNbinsX() + 1 : histogram->GetNbinsX();
  double integral = 0.;
  for ( int idxBin = idxFirstBin; idxBin <= idxLastBin; ++idxBin ) {
    integral += histogram->GetBinContent(idxBin);
  }
  return integral;
}

void makeGenFilterPlots_before_and_afterCuts()
{
  gROOT->SetBatch(true);

  TH1::AddDirectory(false);

  typedef std::vector<std::string> vstring;
  vstring channels;
  //channels.push_back("0l_2tau");
  //channels.push_back("1l_1tau");
  //channels.push_back("0l_3tau");
  channels.push_back("1l_2tau");
  channels.push_back("2lss_1tau");
  //channels.push_back("2los_1tau");
  //channels.push_back("2l_2tau");
  channels.push_back("3l_1tau");

  std::map<std::string, std::string> inputFilePaths; // key = channel
  inputFilePaths["0l_2tau"] = "/home/veelken/ttHAnalysis/2016Sep07_dR03mvaTight/histograms/";
  inputFilePaths["1l_1tau"] = "/home/veelken/ttHAnalysis/2016Sep07_dR03mvaTight/histograms/";
  inputFilePaths["1l_2tau"] = "/home/veelken/ttHAnalysis/2016Sep07_dR03mvaTight/histograms/";
  inputFilePaths["0l_3tau"] = "/home/veelken/ttHAnalysis/2016Sep07_dR03mvaMedium/histograms/";
  inputFilePaths["2lss_1tau"] = "/home/veelken/ttHAnalysis/2016Sep07_dR03mvaLoose/histograms/";
  inputFilePaths["2los_1tau"] = "/home/veelken/ttHAnalysis/2016Sep07_dR03mvaVVTight/histograms/";
  inputFilePaths["2l_2tau"] = "/home/veelken/ttHAnalysis/2016Sep07_dR03mvaMedium/histograms/";
  inputFilePaths["3l_1tau"] = "/home/veelken/ttHAnalysis/2016Sep07_dR03mvaLoose/histograms/";
  
  std::map<std::string, std::string> inputFileNames; // key = channel
  inputFileNames["0l_2tau"] = "histograms_harvested_stage1_0l_2tau_$PROCESS.root";
  inputFileNames["1l_1tau"] = "histograms_harvested_stage1_1l_1tau_$PROCESS.root";
  inputFileNames["1l_2tau"] = "histograms_harvested_stage1_1l_2tau_$PROCESS.root";
  inputFileNames["0l_3tau"] = "histograms_harvested_stage1_0l_3tau_$PROCESS.root";
  inputFileNames["2lss_1tau"] = "histograms_harvested_stage1_2lss_1tau_$PROCESS.root";
  inputFileNames["2los_1tau"] = "histograms_harvested_stage1_2los_1tau_$PROCESS.root";
  inputFileNames["2l_2tau"] = "histograms_harvested_stage1_2l_2tau_$PROCESS.root";
  inputFileNames["3l_1tau"] = "histograms_harvested_stage1_3l_1tau_$PROCESS.root";

  std::map<std::string, std::string> directoryNames; // key = channel
  directoryNames["0l_2tau"] = "0l_2tau_OS_Tight/$SELECTION/genEvt/$PROCESS_CATEGORY/";
  directoryNames["1l_1tau"] = "1l_1tau_OS_Tight/$SELECTION/genEvt/$PROCESS_CATEGORY/";
  directoryNames["1l_2tau"] = "1l_2tau_OS_Tight/$SELECTION/genEvt/$PROCESS_CATEGORY/";
  directoryNames["0l_3tau"] = "0l_3tau_Tight/$SELECTION/genEvt/$PROCESS_CATEGORY/";
  directoryNames["2lss_1tau"] = "2lss_1tau_SS_Tight/$SELECTION/genEvt/$PROCESS_CATEGORY/";
  directoryNames["2los_1tau"] = "2los_1tau_Tight/$SELECTION/genEvt/$PROCESS_CATEGORY/";
  directoryNames["2l_2tau"] = "2l_2tau_lepOS_tauOS_Tight/$SELECTION/genEvt/$PROCESS_CATEGORY/";
  directoryNames["3l_1tau"] = "3l_1tau_OS_Tight/$SELECTION/genEvt/$PROCESS_CATEGORY/";

  std::map<std::string, vstring> histogramNames; // key = channel
  histogramNames["0l_2tau"].push_back("numGenLeptons_withinAcc");
  histogramNames["0l_2tau"].push_back("numGenHadTaus_withinAcc");
  histogramNames["0l_2tau"].push_back("numGenLeptonsAndHadTaus_withinAcc");
  histogramNames["0l_2tau"].push_back("numGenJets_withinAcc");
  histogramNames["0l_2tau"].push_back("numGenLeptonsAndHadTausAndJets_withinAcc");
  histogramNames["1l_1tau"] = histogramNames["0l_2tau"];
  histogramNames["1l_2tau"] = histogramNames["0l_2tau"];
  histogramNames["0l_3tau"] = histogramNames["0l_2tau"];
  histogramNames["2lss_1tau"] = histogramNames["0l_2tau"];
  histogramNames["2los_1tau"] = histogramNames["0l_2tau"];
  histogramNames["2l_2tau"] = histogramNames["0l_2tau"];
  histogramNames["3l_1tau"] = histogramNames["0l_2tau"];
  
  std::map<std::string, std::string> xAxisTitles; // key = histogramName
  xAxisTitles["numGenLeptons_withinAcc"] = "N_{e}^{gen} + N_{#mu}^{gen}";
  xAxisTitles["numGenHadTaus_withinAcc"] = "N_{#tau}^{gen}";
  xAxisTitles["numGenLeptonsAndHadTaus_withinAcc"] = "N_{e}^{gen} + N_{#mu}^{gen} + N_{#tau}^{gen}";
  xAxisTitles["numGenJets_withinAcc"] = "N_{jet}^{gen}";
  xAxisTitles["numGenLeptonsAndHadTausAndJets_withinAcc"] = "N_{e}^{gen} + N_{#mu}^{gen} + N_{#tau}^{gen} + N_{jet}^{gen}";

  std::map<std::string, std::string> yAxisTitles; // key = histogramName
  yAxisTitles["numGenLeptons_withinAcc"] = "Events";
  yAxisTitles["numGenHadTaus_withinAcc"] = "Events";
  yAxisTitles["numGenLeptonsAndHadTaus_withinAcc"] = "Events";
  yAxisTitles["numGenJets_withinAcc"] = "Events";
  yAxisTitles["numGenLeptonsAndHadTausAndJets_withinAcc"] = "Events";

  std::map<std::string, vstring> processes; // key = channel
  processes["0l_2tau"].push_back("ttHJetToNonbb_M125");
  processes["0l_2tau"].push_back("TTJets_SingleLeptFromTbar");
  processes["0l_2tau"].push_back("TTJets_SingleLeptFromT");
  processes["0l_2tau"].push_back("TTJets_DiLept");
  processes["0l_2tau"].push_back("TTWJetsToLNu");
  processes["0l_2tau"].push_back("TTZToLLNuNu");
  processes["0l_2tau"].push_back("WZTo3LNu");
  processes["1l_1tau"] = processes["0l_2tau"];
  processes["0l_3tau"] = processes["0l_2tau"];
  processes["1l_2tau"] = processes["0l_2tau"];
  processes["2lss_1tau"].push_back("ttHJetToNonbb_M125");
  processes["2lss_1tau"].push_back("TTWJetsToLNu");
  processes["2lss_1tau"].push_back("TTZToLLNuNu");
  processes["2lss_1tau"].push_back("WZTo3LNu");
  processes["2los_1tau"] = processes["0l_2tau"];
  processes["2l_2tau"] = processes["0l_2tau"];
  processes["3l_1tau"] = processes["0l_2tau"];

  typedef std::map<std::string, std::string> string_to_string_map;
  std::map<std::string, string_to_string_map> process_categories; // key = channel, process
  process_categories["0l_2tau"]["ttHJetToNonbb_M125"] = "signal";
  process_categories["0l_2tau"]["TTJets_SingleLeptFromTbar"] = "TT";
  process_categories["0l_2tau"]["TTJets_SingleLeptFromT"] = "TT";
  process_categories["0l_2tau"]["TTJets_DiLept"] = "TT";
  process_categories["0l_2tau"]["WZTo3LNu"] = "EWK";
  process_categories["0l_2tau"]["TTWJetsToLNu"] = "TTW";
  process_categories["0l_2tau"]["TTZToLLNuNu"] = "TTZ";			  
  process_categories["1l_1tau"] = process_categories["0l_2tau"];
  process_categories["0l_3tau"] = process_categories["0l_2tau"];
  process_categories["1l_2tau"] = process_categories["0l_2tau"];
  process_categories["2lss_1tau"] = process_categories["0l_2tau"];
  process_categories["2lss_1tau"]["WZTo3LNu"] = "WZ";
  process_categories["2los_1tau"] = process_categories["0l_2tau"];
  process_categories["2l_2tau"] = process_categories["0l_2tau"];
  process_categories["3l_1tau"] = process_categories["0l_2tau"];

  for ( vstring::const_iterator channel = channels.begin();
	channel != channels.end(); ++channel ) {
    std::cout << "channel = " << (*channel) << std::endl;

    for ( vstring::const_iterator process = processes[*channel].begin();
	  process != processes[*channel].end(); ++process ) {

      TString inputFileName_full = inputFilePaths[*channel].data();
      if ( !inputFileName_full.EndsWith("/") ) inputFileName_full.Append("/");
      inputFileName_full.Append(inputFileNames[*channel].data());
      inputFileName_full = inputFileName_full.ReplaceAll("$PROCESS", process->data());
      TFile* inputFile = new TFile(inputFileName_full.Data());
      if ( !inputFile ) {
	std::cerr << "Failed to open input file = " << inputFileName_full.Data() << " !!" << std::endl;
	assert(0);
      }

      for ( vstring::const_iterator histogramName = histogramNames[*channel].begin();
	    histogramName != histogramNames[*channel].end(); ++histogramName ) {
	
	TString histogramName_full = directoryNames[*channel].data();
	histogramName_full = histogramName_full.ReplaceAll("$PROCESS_CATEGORY", process_categories[*channel][*process].data());
	if ( !histogramName_full.EndsWith("/") ) histogramName_full.Append("/");
	histogramName_full.Append(histogramName->data());

	TString histogramName_beforeCuts = histogramName_full;
	histogramName_beforeCuts = histogramName_beforeCuts.ReplaceAll("$SELECTION", "unbiased");
	TH1* histogram_beforeCuts = loadHistogram(inputFile, histogramName_beforeCuts.Data());
	double integral_beforeCuts = compIntegral(histogram_beforeCuts);
	histogram_beforeCuts->Scale(1./integral_beforeCuts);

	TString histogramName_afterCuts = histogramName_full;
	histogramName_afterCuts = histogramName_afterCuts.ReplaceAll("$SELECTION", "sel");
	TH1* histogram_afterCuts = loadHistogram(inputFile, histogramName_afterCuts.Data());
	histogram_afterCuts->Scale(1./integral_beforeCuts);

	std::string outputFileName = Form("makeGenFilterPlots_before_and_afterCuts_%s_%s_%s.png", channel->data(), process->data(), histogramName->data());
	showHistograms(800, 900,
		       histogram_beforeCuts, "before Cuts",
		       histogram_afterCuts, "after Cuts",
		       NULL, "", 
		       NULL, "", 		       
		       NULL, "", 
		       NULL, "", 
		       xAxisTitles[*histogramName], 1.10,
		       true, 1.e-4, 1.e0, yAxisTitles[*histogramName], 1.20,
		       0.54, 0.72,
		       outputFileName.data());	
      }

      delete inputFile;
    }
  }
}


