
/** \executable makePlots
 *
 * Make control plots (prefit and postfit) for all channels of ttH, H->tautau analysis.
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
typedef std::pair<double, double> pdouble;

namespace
{
  struct categoryEntryType
  {
    categoryEntryType(const edm::ParameterSet& cfg)
    {
      name_ = cfg.getParameter<std::string>("name");
      label_ = cfg.getParameter<std::string>("label");
    }
    ~categoryEntryType() {}
    std::string name_;
    std::string label_;
  };
  std::vector<pdouble> GetBlindedRanges(TH1* histogramData, std::vector<histogramEntryType*>& histogramsBackground, TH1* histogramSignal){
    std::vector<pdouble> range;
    TH1* histogramBackgroundSum = 0;
    for ( std::vector<histogramEntryType*>::iterator histogramBackground_entry = histogramsBackground.begin();
          histogramBackground_entry != histogramsBackground.end(); ++histogramBackground_entry ) {
      TH1* histogramBackground = (*histogramBackground_entry)->histogram_;
      checkCompatibleBinning(histogramSignal, histogramBackground);
      if(!histogramBackgroundSum) histogramBackgroundSum = (TH1*) histogramBackground->Clone("histogramBackgroundSum");
      histogramBackgroundSum->Add(histogramBackground);
    }
    int numBins = histogramData->GetNbinsX();
    for ( int iBin = 1; iBin <= numBins; ++iBin ) {
      double x = histogramData->GetBinCenter(iBin);
      double w = histogramData->GetBinWidth(iBin);
      double s = histogramSignal->GetBinContent(iBin);
      double b = histogramBackgroundSum->GetBinContent(iBin);
      if((s/sqrt(b+pow(0.09*b, 2))) >= 0.5){
	double xmin = x - 0.5*w;
	double xmax = x + 0.5*w;
	range.push_back(pdouble(xmin, xmax));
      }
    }
    return range;
  }
  
  TH1* blindHistogram(TH1* histogram, const std::vector<pdouble>& keepBlinded)
  {
    //std::cout << "<blindHistogram>:" << std::endl;
    std::string blindedHistogramName = Form("%s_blinded", histogram->GetName());
    TH1* blindedHistogram = (TH1*)histogram->Clone(blindedHistogramName.data());
    if ( !blindedHistogram->GetSumw2N() ) blindedHistogram->Sumw2();
    int numBins = histogram->GetNbinsX();
    for ( int iBin = 1; iBin <= numBins; ++iBin ) {
      double x = histogram->GetBinCenter(iBin);
      bool isBlinded = false;
      for ( std::vector<pdouble>::const_iterator keepBlinded_it = keepBlinded.begin();
	    keepBlinded_it != keepBlinded.end(); ++keepBlinded_it ) {
	if ( x >= keepBlinded_it->first && x <= keepBlinded_it->second ) {
	  isBlinded = true;
	  break;
	}
      }
      //      std::cout << "BinCenter = " << x << ": isBlinded = " << isBlinded << std::endl;
      if ( isBlinded ) {
	blindedHistogram->SetBinContent(iBin, -10.);
	blindedHistogram->SetBinError(iBin, 0.);
      }
    }
    //std::cout << "histogram: name = " << histogram->GetName() << ", integral = " << histogram->Integral() << std::endl;
    //std::cout << "histogram(blinded): name = " << blindedHistogram->GetName() << ", integral = " << blindedHistogram->Integral() << std::endl;
    return blindedHistogram;
  }

  void makePlot(double canvasSizeX, double canvasSizeY,
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
		const std::string& outputFileName)
  {
    std::cout << "<makePlot>:" << std::endl;
    std::cout << " outputFileName = " << outputFileName << std::endl;

    TH1* histogramData_density = 0;
    if ( histogramData ) {
      histogramData_density = divideHistogramByBinWidth(histogramData);      
    }

    TH1* histogramData_blinded_density = 0;
    if ( histogramData_blinded ) {
      if ( histogramData ) checkCompatibleBinning(histogramData_blinded, histogramData);
      histogramData_blinded_density = divideHistogramByBinWidth(histogramData_blinded);
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
    TH1* histogramFakes = 0;
    TH1* histogramFakes_density = 0;
    TH1* histogramFlips = 0;
    TH1* histogramFlips_density = 0;
    for ( std::vector<histogramEntryType*>::iterator histogramBackground_entry = histogramsBackground.begin();
	  histogramBackground_entry != histogramsBackground.end(); ++histogramBackground_entry ) {
      TH1* histogramBackground = (*histogramBackground_entry)->histogram_;
      const std::string& process = (*histogramBackground_entry)->process_;
      //      std::cout << "process = " << process << ": histogramBackground = " << histogramBackground << std::endl;
      //printHistogram(histogramBackground);
      checkCompatibleBinning(histogramBackground, histogramData);
      TH1* histogramBackground_density = divideHistogramByBinWidth(histogramBackground); 
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
      } else if ( process.find("Fakes") != std::string::npos || process.find("fakes") != std::string::npos ) {
	histogramFakes = histogramBackground;
	histogramFakes_density = histogramBackground_density;
      } else if ( process.find("Flips") != std::string::npos || process.find("flips") != std::string::npos ) {
	histogramFlips = histogramBackground;
	histogramFlips_density = histogramBackground_density;
      }
      histogramsBackground_density.push_back(histogramBackground_density);
    }
    //    std::cout << "histogramTTW_density = " << histogramTTW_density << std::endl;
    //    std::cout << "histogramTTWW_density = " << histogramTTWW_density << std::endl;
    //    std::cout << "histogramTTZ_density = " << histogramTTZ_density << std::endl;

    TH1* histogramSignal_density = 0;
    if ( histogramSignal ) {
      if ( histogramSignal ) checkCompatibleBinning(histogramSignal, histogramData);
      histogramSignal_density = divideHistogramByBinWidth(histogramSignal); 
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
      histogramUncertainty_density = divideHistogramByBinWidth(histogramUncertainty);
    }

    //---------------------------------------------------------------------------
    // CV: sum ttW and ttWW backgrounds
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
      if ( useLogScale ) {
	const double numOrdersOfMagnitude = 4.5;
	if ( histogramData_density ) yMax = compYmaxForClearance(histogramData_density, legendPosX, legendPosY, labelPosY, true, numOrdersOfMagnitude);
	else yMax = 1.;
	yMax = TMath::Max(yMax, compYmaxForClearance(histogramSum_density, legendPosX, legendPosY, labelPosY, true, numOrdersOfMagnitude));
	yMin = TMath::Power(10., -numOrdersOfMagnitude)*TMath::Max(1., yMax);
      } else {
	if ( histogramData_density ) yMax = compYmaxForClearance(histogramData_density, legendPosX, legendPosY, labelPosY, false, -1.);
	else yMax = 1.;
	yMax = TMath::Max(yMax, compYmaxForClearance(histogramSum_density, legendPosX, legendPosY, labelPosY, false, -1.));
	yMin = 0.;
      }
    }
    //    std::cout << "yMin = " << yMin << ", yMax = " << yMax << std::endl;

    if ( histogramData_blinded_density ) {
      histogramData_blinded_density->SetTitle("");
      histogramData_blinded_density->SetStats(false);
      histogramData_blinded_density->SetMaximum(yMax);
      histogramData_blinded_density->SetMinimum(yMin);
      histogramData_blinded_density->SetMarkerStyle(20);
      histogramData_blinded_density->SetMarkerSize(2);
      histogramData_blinded_density->SetMarkerColor(kBlack);
      histogramData_blinded_density->SetLineColor(kBlack);
      legend->AddEntry(histogramData_blinded_density, "observed", "p");
      histogramData_blinded_density->Draw("ep");
    }
        
    const int color_ttW     = 823; // dark green
    const int color_ttZ     = 822; // dark green
    const int color_ttH     = 628; // red
    const int color_ttjets  =  16; // gray
    const int color_EWK     = 610; // purple
    const int color_Diboson = 634; // dark red
    const int color_WZ      = 634; // dark red
    const int color_Rares   = 851; // light blue
    const int color_Fakes   =   1; // black
    const int color_Flips   =   1; // black
    
    //---------------------------------------------------------------------------
    // CV: sum ttW and ttWW backgrounds
    const std::string legendEntry_ttW     = "t#bar{t}W + t#bar{t}WW";
    //---------------------------------------------------------------------------
    //const std::string legendEntry_ttW     = "t#bar{t}W";
    const std::string legendEntry_ttZ     = "t#bar{t}Z";
    const std::string legendEntry_ttH     = "t#bar{t}H";
    const std::string legendEntry_ttjets  = "t#bar{t}+jets";
    const std::string legendEntry_EWK     = "EWK";
    const std::string legendEntry_Diboson = "Diboson";
    const std::string legendEntry_WZ      = "WZ";
    const std::string legendEntry_Rares   = "Rares";
    const std::string legendEntry_Fakes   = "Fakes";
    const std::string legendEntry_Flips   = "Flips";
   
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
    
    if ( histogramUncertainty_density ) {
      int numBins_top = histogramUncertainty_density->GetNbinsX();
      for ( int iBin = 1; iBin <= numBins_top; ++iBin ) {
	double sumBinContents = 0.;
	if      ( histogramSignal_density  ) sumBinContents += histogramSignal_density->GetBinContent(iBin);
	if      ( histogramTTW_density     ) sumBinContents += histogramTTW_density->GetBinContent(iBin);
	if      ( histogramTTZ_density     ) sumBinContents += histogramTTZ_density->GetBinContent(iBin);
	if      ( histogramTTH_density     ) sumBinContents += histogramTTH_density->GetBinContent(iBin);
	if      ( histogramTT_density      ) sumBinContents += histogramTT_density->GetBinContent(iBin);
	if      ( histogramEWK_density     ) sumBinContents += histogramEWK_density->GetBinContent(iBin);
	if      ( histogramDiboson_density ) sumBinContents += histogramDiboson_density->GetBinContent(iBin);
	else if ( histogramWZ_density      ) sumBinContents += histogramWZ_density->GetBinContent(iBin);
	if      ( histogramRares_density   ) sumBinContents += histogramRares_density->GetBinContent(iBin);
	if      ( histogramFakes_density   ) sumBinContents += histogramFakes_density->GetBinContent(iBin);
	if      ( histogramFlips_density   ) sumBinContents += histogramFlips_density->GetBinContent(iBin);
	histogramUncertainty_density->SetBinContent(iBin, sumBinContents);
      }
      histogramUncertainty_density->SetFillColor(kBlack);
      histogramUncertainty_density->SetFillStyle(3344);    
      histogramUncertainty_density->Draw("e2same");
      legend->AddEntry(histogramUncertainty_density, "Uncertainty", "f");
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
      if      ( histogramSignal  ) histogramSum->Add(histogramSignal);
      if      ( histogramTTW     ) histogramSum->Add(histogramTTW);
      if      ( histogramTTZ     ) histogramSum->Add(histogramTTZ);
      if      ( histogramTTH     ) histogramSum->Add(histogramTTH);
      if      ( histogramTT      ) histogramSum->Add(histogramTT);
      if      ( histogramEWK     ) histogramSum->Add(histogramEWK);
      else if ( histogramDiboson ) histogramSum->Add(histogramDiboson);
      else if ( histogramWZ      ) histogramSum->Add(histogramWZ);
      if      ( histogramRares   ) histogramSum->Add(histogramRares);
      if      ( histogramFakes   ) histogramSum->Add(histogramFakes);
      if      ( histogramFlips   ) histogramSum->Add(histogramFlips);
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
    if ( idx != std::string::npos ) canvas->Print(std::string(outputFileName_plot).append(std::string(outputFileName, idx)).data());
    canvas->Print(std::string(outputFileName_plot).append(".png").data());
    canvas->Print(std::string(outputFileName_plot).append(".pdf").data());
    canvas->Print(std::string(outputFileName_plot).append(".root").data());

    delete histogramData_density;
    delete histogramData_blinded_density;
    delete histogramSignal_density;
    delete histogramTTW_density;
    delete histogramTTZ_density;
    delete histogramTTH_density;
    delete histogramTT_density;
    delete histogramWZ_density;
    delete histogramDiboson_density;
    delete histogramEWK_density;
    delete histogramRares_density;
    delete histogramFakes_density;
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

  std::cout << "<makePlots>:" << std::endl;

  gROOT->SetBatch(true);

//--- keep track of time it takes the macro to execute
  TBenchmark clock;
  clock.Start("makePlots");

//--- read python configuration parameters
  if ( !edm::readPSetsFrom(argv[1])->existsAs<edm::ParameterSet>("process") ) 
    throw cms::Exception("makePlots") 
      << "No ParameterSet 'process' found in configuration file = " << argv[1] << " !!\n";

  edm::ParameterSet cfg = edm::readPSetsFrom(argv[1])->getParameter<edm::ParameterSet>("process");

  edm::ParameterSet cfgMakePlots = cfg.getParameter<edm::ParameterSet>("makePlots");

  std::vector<categoryEntryType*> categories;
  vstring categoryNames;
  edm::VParameterSet cfgCategories = cfgMakePlots.getParameter<edm::VParameterSet>("categories");
  for ( edm::VParameterSet::const_iterator cfgCategory = cfgCategories.begin();
	cfgCategory != cfgCategories.end(); ++cfgCategory ) {
    categoryEntryType* category = new categoryEntryType(*cfgCategory);
    categories.push_back(category);
    categoryNames.push_back(category->name_);
  }
  bool applyAutoBlinding  = cfgMakePlots.getParameter<bool>("applyAutoBlinding");
  std::string processData  = cfgMakePlots.getParameter<std::string>("processData");
  vstring processesBackground = cfgMakePlots.getParameter<vstring>("processesBackground");
  std::string processSignal = cfgMakePlots.getParameter<std::string>("processSignal");

  edm::VParameterSet cfgDistributions = cfgMakePlots.getParameter<edm::VParameterSet>("distributions");
  std::vector<plotEntryType*> distributions = readDistributions(cfgDistributions);

  edm::ParameterSet cfgNuisanceParameters = cfgMakePlots.getParameter<edm::ParameterSet>("nuisanceParameters");
  HistogramManager histogramManager(processesBackground, processSignal, categoryNames, cfgNuisanceParameters);
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
    std::cout << "processing category = " << (*category)->name_ << std::endl;

    TDirectory* dir = getDirectory(inputFile, (*category)->name_, true);
    assert(dir);

    for ( std::vector<plotEntryType*>::iterator distribution = distributions.begin();
	  distribution != distributions.end(); ++distribution ) {

      TH1* histogramData = 0;
      if ( processData != "" ) {
	histogramData = getHistogram_wrapper(dir, processData, (*distribution)->histogramName_, "central", true);
      }

      histogramManager.setDirectory(dir);
      histogramManager.setCategory((*category)->name_);
      histogramManager.setHistogram((*distribution)->histogramName_);
      histogramManager.update();

      std::vector<histogramEntryType*> histogramsBackground;
      for ( vstring::const_iterator processBackground = processesBackground.begin();
	    processBackground != processesBackground.end(); ++processBackground ) {
	TH1* histogramBackground = histogramManager.getHistogramPrefit(*processBackground, true);
	histogramsBackground.push_back(new histogramEntryType(*processBackground, histogramBackground));
      }
      
      TH1* histogramSignal = histogramManager.getHistogramPrefit(processSignal, true);

      std::vector<pdouble> keepBlinded =GetBlindedRanges(histogramData, histogramsBackground, histogramSignal);
      TH1* histogramData_blinded = 0;
      if ( processData != "" ) {
	if ( keepBlinded.size() >= 1 && applyAutoBlinding) histogramData_blinded = blindHistogram(histogramData, keepBlinded);
	else histogramData_blinded = histogramData;
      }

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
	  
      makePlot(
	800, 900,
	histogramData, histogramData_blinded,
	histogramsBackground,
	histogramSignal,
	histogramUncertainty,
	(*distribution)->legendTextSize_, (*distribution)->legendPosX_, (*distribution)->legendPosY_, (*distribution)->legendSizeX_, (*distribution)->legendSizeY_, 
	labelOnTop,
	extraLabels, 0.055, 0.185, 0.915 - 0.055*extraLabels.size(), extraLabelsSizeX, 0.055*extraLabels.size(),
	(*distribution)->xMin_, (*distribution)->xMax_, (*distribution)->xAxisTitle_, (*distribution)->xAxisOffset_, 
	true, (*distribution)->yMin_, (*distribution)->yMax_, (*distribution)->yAxisTitle_, (*distribution)->yAxisOffset_, 
	outputFileName_plot);
      makePlot(
	800, 900,
	histogramData, histogramData_blinded,
	histogramsBackground,
	histogramSignal,
	histogramUncertainty,
	(*distribution)->legendTextSize_, (*distribution)->legendPosX_, (*distribution)->legendPosY_, (*distribution)->legendSizeX_, (*distribution)->legendSizeY_, 
	labelOnTop,
	extraLabels, 0.055, 0.185, 0.915 - 0.055*extraLabels.size(), extraLabelsSizeX, 0.055*extraLabels.size(),
	(*distribution)->xMin_, (*distribution)->xMax_, (*distribution)->xAxisTitle_, (*distribution)->xAxisOffset_, 
	false, (*distribution)->yMin_, (*distribution)->yMax_, (*distribution)->yAxisTitle_, (*distribution)->yAxisOffset_, 
	outputFileName_plot);

      if ( histogramData_blinded != histogramData ) delete histogramData_blinded;
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

  clock.Show("makePlots");

  return 0;
}

