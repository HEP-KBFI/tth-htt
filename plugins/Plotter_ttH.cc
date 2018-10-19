#include "tthAnalysis/HiggsToTauTau/plugins/Plotter_ttH.h"

#include <TH1.h>
#include <THStack.h>
#include <TMath.h>
#include <TString.h> // Form
#include <TCanvas.h>
#include <TPad.h>
#include <TLegend.h>
#include <TPaveText.h>
#include <TF1.h>
#include <TStyle.h>
#include <TROOT.h> // gROOT (needed to (re)define colors)

Plotter_ttH::Plotter_ttH(const TFile* inputFile, const edm::ParameterSet& cfg)
  : Plotter(inputFile, cfg)
{}

Plotter_ttH::~Plotter_ttH()
{}

void Plotter_ttH::makePlot(double canvasSizeX, double canvasSizeY,
			   TH1* histogramData, TH1* histogramData_blinded,
			   std::vector<histogramEntryType*>& histogramsBackground, 	
			   TH1* histogramSignal,
			   TH1* histogramUncertainty,
			   double legendTextSize, double legendPosX, double legendPosY, double legendSizeX, double legendSizeY, 
			   const std::string& labelOnTop,
			   std::vector<std::string>& extraLabels, double labelTextSize,
			   double labelPosX, double labelPosY, double labelSizeX, double labelSizeY,
			   double xMin, double xMax, const std::string& xAxisTitle, double xAxisOffset,
			   bool useLogScale, double yMin, double yMax, const std::string& yAxisTitle, double yAxisOffset,
			   const std::string& outputFileName, 
			   bool isRebinned, 
			   bool divideByBinWidth)
{
  std::cout << "<Plotter_ttH::makePlot>:" << std::endl;
  std::cout << " outputFileName = " << outputFileName << std::endl;

  TH1* histogramData_density = 0;
  if ( histogramData ) {
    if  ( divideByBinWidth ) {
      histogramData_density = divideHistogramByBinWidth(histogramData);      
    } else {
      std::string histogramNameData_density = Form("%s_NotDivided", histogramData->GetName());	
      histogramData_density = (TH1*)histogramData->Clone(histogramNameData_density.data());
    }
  }
  
  TH1* histogramData_blinded_density = 0;
  if ( histogramData_blinded ) {
    if ( histogramData ) checkCompatibleBinning(histogramData_blinded, histogramData);
    if ( divideByBinWidth ) {
      histogramData_blinded_density = divideHistogramByBinWidth(histogramData_blinded);
    } else {
      std::string histogramNameData_blinded_density = Form("%s_NotDivide", histogramData_blinded->GetName());
      histogramData_blinded_density = (TH1*)histogramData_blinded->Clone(histogramNameData_blinded_density.data());
    }
  }
  
  std::vector<TH1*> histogramsBackground_density;
  TH1* histogramTTW = 0;
  TH1* histogramTTW_density = 0;
  TH1* histogramTTWW = 0;
  TH1* histogramTTWW_density = 0;
  TH1* histogramTTZ = 0;
  TH1* histogramTTZ_density = 0;
  TH1* histogramTTH = 0;
  TH1* histogramTTH_density = 0;
  TH1* histogramTT = 0;
  TH1* histogramTT_density = 0;
  TH1* histogramWZ = 0;
  TH1* histogramWZ_density = 0;
  TH1* histogramDiboson = 0;
  TH1* histogramDiboson_density = 0;
  TH1* histogramEWK = 0;
  TH1* histogramEWK_density = 0;
  TH1* histogramRares = 0;
  TH1* histogramRares_density = 0;
  TH1* histogramConversions = 0;
  TH1* histogramConversions_density = 0;
  TH1* histogramFakes = 0;
  TH1* histogramFakes_density = 0;
  TH1* histogramFlips = 0;
  TH1* histogramFlips_density = 0;
  for ( std::vector<histogramEntryType*>::iterator histogramBackground_entry = histogramsBackground.begin();
	histogramBackground_entry != histogramsBackground.end(); ++histogramBackground_entry ) {
    std::string histogramNameBackground = Form("%s_", (*histogramBackground_entry)->histogram_->GetName());
    TH1* histogramBackground = (TH1*)(*histogramBackground_entry)->histogram_->Clone(histogramNameBackground.data());
    const std::string& process = (*histogramBackground_entry)->process_;
    //      std::cout << "process = " << process << ": histogramBackground = " << histogramBackground << std::endl;
    //printHistogram(histogramBackground);
    checkCompatibleBinning(histogramBackground, histogramData);
    TH1* histogramBackground_density ;
    if ( divideByBinWidth ) {
      histogramBackground_density = divideHistogramByBinWidth(histogramBackground); 
    } else {
      std::string histogramNameBackground_density = Form("%s_NotDivided", histogramBackground->GetName());
      histogramBackground_density = (TH1*)histogramBackground->Clone(histogramNameBackground_density.data());
    }
    if ( process.find("TTWW") != std::string::npos ) {
      histogramTTWW = histogramBackground;
      histogramTTWW_density = histogramBackground_density;
    } else if ( process.find("TTW") != std::string::npos ) {
      histogramTTW = histogramBackground;
      histogramTTW_density = histogramBackground_density;
    } else if ( process.find("TTZ") != std::string::npos ) {
      histogramTTZ = histogramBackground;
      histogramTTZ_density = histogramBackground_density;
    } else if ( process.find("signal") != std::string::npos ) {
      histogramTTH = histogramBackground;
      histogramTTH_density = histogramBackground_density;
    } else if ( process.find("TT") != std::string::npos ) {
      histogramTT = histogramBackground;
      histogramTT_density = histogramBackground_density;
    } else if ( process.find("EWK") != std::string::npos ) {
      histogramEWK = histogramBackground;
      histogramEWK_density = histogramBackground_density;
    } else if ( process.find("Diboson") != std::string::npos ) { 
      histogramDiboson = histogramBackground;
      histogramDiboson_density = histogramBackground_density;
    } else if ( process.find("WZ") != std::string::npos ) {
      histogramWZ = histogramBackground;
      histogramWZ_density = histogramBackground_density;
    } else if ( process.find("Rares") != std::string::npos ) {
      histogramRares = histogramBackground;
      histogramRares_density = histogramBackground_density;
    } else if ( process.find("Conversions") != std::string::npos || process.find("conversions") != std::string::npos ) {
      histogramConversions = histogramBackground;
      histogramConversions_density = histogramBackground_density;
    } else if ( process.find("Fakes") != std::string::npos || process.find("fakes") != std::string::npos ) {
      histogramFakes = histogramBackground;
      histogramFakes_density = histogramBackground_density;
    } else if ( process.find("Flips") != std::string::npos || process.find("flips") != std::string::npos ) {
      histogramFlips = histogramBackground;
      histogramFlips_density = histogramBackground_density;
    }
    histogramsBackground_density.push_back(histogramBackground_density);
  }
  
  TH1* histogramSignal_density = 0;
  if ( histogramSignal ) {
    if ( histogramSignal ) checkCompatibleBinning(histogramSignal, histogramData);
    if ( divideByBinWidth ) {
      histogramSignal_density = divideHistogramByBinWidth(histogramSignal); 
    } else {
      std::string histogramNameSignal_density = Form("%s_NotDivided",histogramSignal->GetName());
      histogramSignal_density = (TH1*)histogramSignal->Clone(histogramNameSignal_density.data());
    }
  }
  
  TH1* histogramSum_density = 0;
  std::vector<TH1*> histogramsSignal_and_Background_density = histogramsBackground_density;
  if ( histogramSignal_density ) histogramsSignal_and_Background_density.push_back(histogramSignal_density);
  for ( std::vector<TH1*>::iterator histogram_density = histogramsSignal_and_Background_density.begin();
	histogram_density != histogramsSignal_and_Background_density.end(); ++histogram_density ) {
    if ( !histogramSum_density ) histogramSum_density = (TH1*)(*histogram_density)->Clone("histogramSum_density"); // CV: used for y-axis normalization only
    else histogramSum_density->Add(*histogram_density);
  }
  assert(histogramSum_density);
  
  TH1* histogramUncertainty_density = 0;
  if ( histogramUncertainty ) {
    if ( histogramData ) checkCompatibleBinning(histogramUncertainty, histogramData);
    if ( divideByBinWidth ) {
      histogramUncertainty_density = divideHistogramByBinWidth(histogramUncertainty);
    } else {
      std::string histogramNameUncertainty_density = Form("%s_NotDivided",histogramUncertainty->GetName());
      histogramUncertainty_density = (TH1*)histogramUncertainty->Clone(histogramNameUncertainty_density.data());
    }
  }
  
  //---------------------------------------------------------------------------
  // CV: sum ttW and ttWW backgrounds
  assert(histogramTTW && histogramTTW_density && histogramTTWW && histogramTTWW_density);
  histogramTTW->Add(histogramTTWW);
  histogramTTW_density->Add(histogramTTWW_density);
  //---------------------------------------------------------------------------
  
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
  
  TAxis* xAxis_top = 0;
  if ( histogramData_blinded_density ) xAxis_top = histogramData_blinded_density->GetXaxis();
  else xAxis_top = histogramSum_density->GetXaxis();
  if ( xMin >= 0. && xMax > xMin ) xAxis_top->SetRangeUser(xMin, xMax);
  xAxis_top->SetTitle(xAxisTitle.data());
  xAxis_top->SetTitleOffset(xAxisOffset);
  xAxis_top->SetLabelColor(10);
  xAxis_top->SetTitleColor(10);
  
  TAxis* yAxis_top = 0;
  if ( histogramData_blinded_density ) yAxis_top = histogramData_blinded_density->GetYaxis();
  else yAxis_top = histogramSum_density->GetYaxis();
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
    for ( int i = 0; i < 2; ++i ) {
      TH1* histogram_i = nullptr;
      if      ( i == 0 ) histogram_i = histogramData_density;
      else if ( i == 1 ) histogram_i = histogramSum_density;
      else assert(0);
      double numOrdersOfMagnitude;
      if ( useLogScale ) numOrdersOfMagnitude = 4.5;
      else numOrdersOfMagnitude = -1.;
      if ( histogram_i ) {
	std::pair<double, double> yMin_and_yMax = compYmin_and_YmaxForClearance(histogram_i, legendPosX, legendPosY, labelPosY, useLogScale, numOrdersOfMagnitude);
	if ( yMin_and_yMax.second > yMax || i == 0 ) {
	  yMin = yMin_and_yMax.first;
	  yMax = yMin_and_yMax.second;
	}
      } else if ( i == 0 ) {
	if ( useLogScale ) yMin = TMath::Power(10., -numOrdersOfMagnitude);
	else yMin = 0.;
	yMax = 1.;
      }
    }
  }
  
  if ( histogramData_blinded_density ) {
    histogramData_blinded_density->SetTitle("");
    histogramData_blinded_density->SetStats(false);
    histogramData_blinded_density->SetMaximum(yMax);
    histogramData_blinded_density->SetMinimum(yMin);
    histogramData_blinded_density->SetMarkerStyle(20);
    int markerSize = ( histogramData_blinded_density->GetNbinsX() < 40 ) ? 2 : 1;
    histogramData_blinded_density->SetMarkerSize(markerSize);
    histogramData_blinded_density->SetMarkerColor(kBlack);
    histogramData_blinded_density->SetLineColor(kBlack);
    legend->AddEntry(histogramData_blinded_density, "observed", "p");
    histogramData_blinded_density->Draw("ep");
  }
  
  const int color_ttW         = 823; // dark green
  const int color_ttZ         = 822; // light green
  const int color_ttH         = 628; // red
  const int color_ttjets      =  16; // gray
  const int color_EWK         = 610; // purple
  const int color_Diboson     = 634; // dark red
  const int color_WZ          = 634; // dark red
  const int color_Rares       = 851; // light blue
  const int color_Conversions = 800; // yellow/orange
  const int color_Fakes       =   1; // black
  const int color_Flips       =   1; // black
  
  //---------------------------------------------------------------------------
  // CV: sum ttW and ttWW backgrounds
  const std::string legendEntry_ttW         = "t#bar{t}W + t#bar{t}WW";
  //---------------------------------------------------------------------------
  //const std::string legendEntry_ttW     = "t#bar{t}W";
  const std::string legendEntry_ttZ         = "t#bar{t}Z";
  const std::string legendEntry_ttH         = "t#bar{t}H";
  const std::string legendEntry_ttjets      = "t#bar{t}+jets";
  const std::string legendEntry_EWK         = "EWK";
  const std::string legendEntry_Diboson     = "Diboson";
  const std::string legendEntry_WZ          = "WZ";
  const std::string legendEntry_Rares       = "Rares";
  const std::string legendEntry_Conversions = "Conversions";
  const std::string legendEntry_Fakes       = "Fakes";
  const std::string legendEntry_Flips       = "Flips";
  
  std::vector<TH1*> histogramsForStack_density;
  if ( histogramSignal_density ) {
    std::string histogramNameSignal = histogramSignal->GetName();
    int color = 10;
    std::string legendEntry = "";
    if ( !histogramTTH_density ) { // "signal" is ttH
      color = color_ttH; 
      legendEntry = legendEntry_ttH;
    } else if ( !histogramTTZ_density ) { // "signal" is ttZ
      color = color_ttZ; 
      legendEntry = legendEntry_ttZ;
    } else if ( !histogramTTW_density ) { // "signal" is ttW
      color = color_ttW; 
      legendEntry = legendEntry_ttW;
    } else if ( !histogramWZ_density ) { // "signal" is WZ
      color = color_WZ; 
      legendEntry = legendEntry_WZ;
    } else assert(0);
    histogramSignal_density->SetFillColor(color); 
    histogramsForStack_density.push_back(histogramSignal_density);
    legend->AddEntry(histogramSignal_density, legendEntry.data(), "f");
  }    
  if ( histogramTTW_density ) {
    histogramTTW_density->SetFillColor(color_ttW);
    histogramsForStack_density.push_back(histogramTTW_density);
    legend->AddEntry(histogramTTW_density, legendEntry_ttW.data(), "f");
  }
  if ( histogramTTZ_density ) {
    histogramTTZ_density->SetFillColor(color_ttZ);
    histogramsForStack_density.push_back(histogramTTZ_density);
    legend->AddEntry(histogramTTZ_density, legendEntry_ttZ.data(), "f");
  }    
  if ( histogramTTH_density ) {
    histogramTTH_density->SetFillColor(color_ttH); 
    histogramsForStack_density.push_back(histogramTTH_density);
    legend->AddEntry(histogramTTH_density, legendEntry_ttH.data(), "f");
  } 
  if ( histogramTT_density ) {
    histogramTT_density->SetFillColor(color_ttjets);
    histogramsForStack_density.push_back(histogramTT_density);
    legend->AddEntry(histogramTT_density, legendEntry_ttjets.data(), "f");
  }
  if ( histogramEWK_density ) {
    histogramEWK_density->SetFillColor(color_EWK);
    histogramsForStack_density.push_back(histogramEWK_density);
    legend->AddEntry(histogramEWK_density, legendEntry_EWK.data(), "f");
  } 
  if ( histogramDiboson_density ) {
    histogramDiboson_density->SetFillColor(color_Diboson);
    histogramsForStack_density.push_back(histogramDiboson_density);
    legend->AddEntry(histogramDiboson_density, legendEntry_Diboson.data(), "f");
  } else if ( histogramWZ_density ) {
    histogramWZ_density->SetFillColor(color_WZ);
    histogramsForStack_density.push_back(histogramWZ_density);
    legend->AddEntry(histogramWZ_density, legendEntry_WZ.data(), "f");
  }
  if ( histogramRares_density ) {
    histogramRares_density->SetFillColor(color_Rares);
    histogramsForStack_density.push_back(histogramRares_density);
    legend->AddEntry(histogramRares_density, legendEntry_Rares.data(), "f");
  }
  if ( histogramConversions_density ) {
    histogramConversions_density->SetFillColor(color_Conversions);
    histogramsForStack_density.push_back(histogramConversions_density);
    legend->AddEntry(histogramConversions_density, legendEntry_Conversions.data(), "f");
  }
  if ( histogramFakes_density ) {
    histogramFakes_density->SetFillColor(color_Fakes);
    histogramFakes_density->SetFillStyle(3005); // stripes extending from top left to bottom right
    histogramsForStack_density.push_back(histogramFakes_density);
    legend->AddEntry(histogramFakes_density, legendEntry_Fakes.data(), "f");
  }
  if ( histogramFlips_density ) {
    histogramFlips_density->SetFillColor(color_Flips);
    histogramFlips_density->SetFillStyle(3006); // vertical stripes
    histogramsForStack_density.push_back(histogramFlips_density);
    legend->AddEntry(histogramFlips_density, legendEntry_Flips.data(), "f");
  }
  
  // CV: add histograms to THStack in "reverse" order, so that ttH signal is drawn on top
  THStack* histogramStack_density = new THStack("stack", "");
  for ( std::vector<TH1*>::reverse_iterator histogram_density = histogramsForStack_density.rbegin(); 
	histogram_density != histogramsForStack_density.rend(); ++histogram_density ) {
    histogramStack_density->Add(*histogram_density);
  }
  if ( histogramData_blinded_density ) histogramStack_density->Draw("histsame");
  else histogramStack_density->Draw("hist");
  std::string histogramNameBkg_bins = Form("%s_bins", histogramData_blinded_density->GetName());
  TH1* histogramBkg_bins = (TH1*)histogramData_blinded_density->Clone(histogramNameBkg_bins.data());
  //    if ( histogramUncertainty_density ) {
  //      int numBins_top = histogramUncertainty_density->GetNbinsX();
  int numBins_top = histogramBkg_bins->GetNbinsX();
  for ( int iBin = 1; iBin <= numBins_top; ++iBin ) {
    double sumBinContents = 0.;
    if      ( histogramSignal_density      ) sumBinContents += histogramSignal_density->GetBinContent(iBin);
    if      ( histogramTTW_density         ) sumBinContents += histogramTTW_density->GetBinContent(iBin);
    if      ( histogramTTZ_density         ) sumBinContents += histogramTTZ_density->GetBinContent(iBin);
    if      ( histogramTTH_density         ) sumBinContents += histogramTTH_density->GetBinContent(iBin);
    if      ( histogramTT_density          ) sumBinContents += histogramTT_density->GetBinContent(iBin);
    if      ( histogramEWK_density         ) sumBinContents += histogramEWK_density->GetBinContent(iBin);
    if      ( histogramDiboson_density     ) sumBinContents += histogramDiboson_density->GetBinContent(iBin);
    else if ( histogramWZ_density          ) sumBinContents += histogramWZ_density->GetBinContent(iBin);
    if      ( histogramRares_density       ) sumBinContents += histogramRares_density->GetBinContent(iBin);
    if      ( histogramConversions_density ) sumBinContents += histogramConversions_density->GetBinContent(iBin);
    if      ( histogramFakes_density       ) sumBinContents += histogramFakes_density->GetBinContent(iBin);
    if      ( histogramFlips_density       ) sumBinContents += histogramFlips_density->GetBinContent(iBin);
    if ( histogramUncertainty_density ) histogramUncertainty_density->SetBinContent(iBin, sumBinContents);
    histogramBkg_bins->SetBinContent(iBin, sumBinContents);
  }
  if ( histogramUncertainty_density ) {
    histogramUncertainty_density->SetFillColor(kBlack);
    histogramUncertainty_density->SetFillStyle(3344);    
    histogramUncertainty_density->Draw("e2same");
    legend->AddEntry(histogramUncertainty_density, "Uncertainty", "f");
  }

  if ( histogramData_blinded_density ) {
    std::string histogramNameData_blinded_bins = Form("%s_bins", histogramData_blinded_density->GetName());
    TH1* histogramData_blinded_bins = (TH1*)histogramData_blinded_density->Clone(histogramNameData_blinded_bins.data());
    int numBins = histogramData_blinded_density->GetNbinsX();
    for ( int iBin = 1; iBin <= numBins; ++iBin ) {
      double iData = histogramData_blinded_density->GetBinContent(iBin);
      double iBkg = histogramBkg_bins->GetBinContent(iBin);
      if ( iData == -10 ){
	histogramData_blinded_bins->SetBinContent(iBin, (iBkg+0.2*iBkg));
      } else{
	histogramData_blinded_bins->SetBinContent(iBin, yMin);
      }
    }
    const int color_int = 12;
    const double alpha = 0.40;
    TColor* color = gROOT->GetColor(color_int);
    static int newColor_int = -1;
    static TColor* newColor = 0;
    if ( !newColor ) {
      newColor_int = gROOT->GetListOfColors()->GetSize() + 1;
      newColor = new TColor(newColor_int, color->GetRed(), color->GetGreen(), color->GetBlue(), "", alpha);
    }
    histogramData_blinded_bins->SetLineColor(newColor_int);
    histogramData_blinded_bins->SetLineWidth(0);
    histogramData_blinded_bins->SetFillColor(newColor_int);
    histogramData_blinded_bins->SetFillStyle(1001);
    
    histogramData_blinded_bins->Draw("histsame");
    legend->AddEntry(histogramData_blinded_bins, "blinded", "f");
  }
  
  if ( histogramData_blinded_density ) {
    histogramData_blinded_density->Draw("epsame");
    histogramData_blinded_density->Draw("axissame");
  }
  
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
  
  canvas->cd();
  bottomPad->Draw();
  bottomPad->cd();
  
  TH1* histogramSum = 0;
  TH1* histogramRatio = 0;
  TH1* histogramRatioUncertainty = 0;
  TF1* line = 0;
  if ( histogramData && histogramData_blinded ) {
    histogramSum = (TH1*)histogramData->Clone("histogramSum");
    histogramSum->Reset();
    if ( !histogramSum->GetSumw2N() ) histogramSum->Sumw2();
    if      ( histogramSignal      ) histogramSum->Add(histogramSignal);
    if      ( histogramTTW         ) histogramSum->Add(histogramTTW);
    if      ( histogramTTZ         ) histogramSum->Add(histogramTTZ);
    if      ( histogramTTH         ) histogramSum->Add(histogramTTH);
    if      ( histogramTT          ) histogramSum->Add(histogramTT);
    if      ( histogramEWK         ) histogramSum->Add(histogramEWK);
    else if ( histogramDiboson     ) histogramSum->Add(histogramDiboson);
    else if ( histogramWZ          ) histogramSum->Add(histogramWZ);
    if      ( histogramRares       ) histogramSum->Add(histogramRares);
    if      ( histogramConversions ) histogramSum->Add(histogramConversions);
    if      ( histogramFakes       ) histogramSum->Add(histogramFakes);
    if      ( histogramFlips       ) histogramSum->Add(histogramFlips);
    histogramRatio = (TH1*)histogramData->Clone("histogramRatio");
    histogramRatio->Reset();
    if ( !histogramRatio->GetSumw2N() ) histogramRatio->Sumw2();
    checkCompatibleBinning(histogramRatio, histogramSum);
    histogramRatio->Divide(histogramData, histogramSum);
    int numBins_bottom = histogramRatio->GetNbinsX();
    for ( int iBin = 1; iBin <= numBins_bottom; ++iBin ) {
      double binContent = histogramRatio->GetBinContent(iBin);
      if ( histogramData_blinded && histogramData_blinded->GetBinContent(iBin) >= 0. ) histogramRatio->SetBinContent(iBin, binContent - 1.0);
      else histogramRatio->SetBinContent(iBin, -10.);
      //std::cout << " bin #" << iBin << " (x = " << histogramRatio->GetBinCenter(iBin) << "): ratio = " << histogramRatio->GetBinContent(iBin) << std::endl;
    }
    
    histogramRatio->SetTitle("");
    histogramRatio->SetStats(false);
    histogramRatio->SetMinimum(-0.50);
    histogramRatio->SetMaximum(+0.50);
    histogramRatio->SetMarkerStyle(histogramData_blinded_density->GetMarkerStyle());
    histogramRatio->SetMarkerSize(histogramData_blinded_density->GetMarkerSize());
    histogramRatio->SetMarkerColor(histogramData_blinded_density->GetMarkerColor());
    histogramRatio->SetLineColor(histogramData_blinded_density->GetLineColor());
    
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
    yAxis_bottom->SetTitle("#frac{Data - Simulation}{Simulation}");
    yAxis_bottom->SetTitleOffset(0.80);
    yAxis_bottom->SetNdivisions(505);
    yAxis_bottom->CenterTitle();
    yAxis_bottom->SetTitleSize(0.09);
    yAxis_bottom->SetLabelSize(0.10);
    yAxis_bottom->SetTickLength(0.04);  
    
    if ( histogramUncertainty ) {
      histogramRatioUncertainty = (TH1*)histogramUncertainty->Clone("histogramRatioUncertainty");
      if ( !histogramRatioUncertainty->GetSumw2N() ) histogramRatioUncertainty->Sumw2();
      checkCompatibleBinning(histogramRatioUncertainty, histogramSum);
      histogramRatioUncertainty->Divide(histogramSum);
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
    
    line = new TF1("line","0", xAxis_bottom->GetXmin(), xAxis_bottom->GetXmax());
    line->SetLineStyle(3);
    line->SetLineWidth(1.5);
    line->SetLineColor(kBlack);
    line->Draw("same");
    
    if ( histogramRatioUncertainty ) {
      //printHistogram(histogramRatioUncertainty);
      histogramRatioUncertainty->Draw("e2same");
    }
    
    histogramRatio->Draw("epsame");
  }
  
  canvas->Update();
  size_t idx = outputFileName.find_last_of('.');
  std::string outputFileName_plot(outputFileName, 0, idx);
  if ( useLogScale ) outputFileName_plot.append("_log");
  else outputFileName_plot.append("_linear");
  if(isRebinned)outputFileName_plot.append("_rebinned");
  if ( idx != std::string::npos ) canvas->Print(std::string(outputFileName_plot).append(std::string(outputFileName, idx)).data());
  canvas->Print(std::string(outputFileName_plot).append(".png").data());
  canvas->Print(std::string(outputFileName_plot).append(".pdf").data());
  canvas->Print(std::string(outputFileName_plot).append(".root").data());
  
  delete histogramData_density;
  delete histogramData_blinded_density;
  delete histogramSignal_density;
  delete histogramTTW;
  delete histogramTTW_density;
  delete histogramTTWW;
  delete histogramTTWW_density;
  delete histogramTTZ;
  delete histogramTTZ_density;
  delete histogramTTH;
  delete histogramTTH_density;
  delete histogramTT;
  delete histogramTT_density;
  delete histogramWZ;
  delete histogramWZ_density;
  delete histogramDiboson;
  delete histogramDiboson_density;
  delete histogramEWK;
  delete histogramEWK_density;
  delete histogramRares;
  delete histogramRares_density;
  delete histogramConversions;
  delete histogramConversions_density;
  delete histogramFakes;
  delete histogramFakes_density;
  delete histogramFlips;
  delete histogramFlips_density;
  delete histogramSum_density;
  delete histogramUncertainty_density;
  delete legend;
  delete labelOnTop_pave;
  delete extraLabels_pave;
  delete topPad;
  delete histogramSum;
  delete histogramRatio;
  delete histogramRatioUncertainty;        
  delete line;
  delete bottomPad;    
  delete canvas;
}

#include "FWCore/Framework/interface/MakerMacros.h"

DEFINE_EDM_PLUGIN(PlotterPluginFactory, Plotter_ttH, "Plotter_ttH");
