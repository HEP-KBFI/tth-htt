
/** \executable addSystFakeRates
 *
 * Add shape systematics for "closure" of electron, muon, and tau_h fake-rates to the datacard:
 *   - CMS_ttHl_Clos_e_normUp/Down
 *   - CMS_ttHl_Clos_e_shapeUp/Down
 *   - CMS_ttHl_Clos_m_normUp/Down
 *   - CMS_ttHl_Clos_m_shapeUp/Down
 *   - CMS_ttHl_Clos_t_normUp/Down
 *   - CMS_ttHl_Clos_t_shapeUp/Down
 *
 * \author Christian Veelken, Tallinn
 *
 */

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#if __has_include (<FWCore/ParameterSetReader/interface/ParameterSetReader.h>)
#  include <FWCore/ParameterSetReader/interface/ParameterSetReader.h> // edm::readPSetsFrom()
#else
#  include <FWCore/PythonParameterSet/interface/MakeParameterSets.h> // edm::readPSetsFrom()
#endif

#include "FWCore/Utilities/interface/Exception.h"

#include "PhysicsTools/FWLite/interface/TFileService.h"
#include "DataFormats/FWLite/interface/InputSource.h"
#include "DataFormats/FWLite/interface/OutputFiles.h"

#include "tthAnalysis/HiggsToTauTau/interface/histogramAuxFunctions.h" // compRatioHistogram, dumpHistogram
#include "tthAnalysis/HiggsToTauTau/interface/generalAuxFunctions.h"
#include "tthAnalysis/HiggsToTauTau/interface/graphAuxFunctions.h" // compRatioGraph, dumpGraph
#include "tthAnalysis/HiggsToTauTau/interface/fitAuxFunctions.h" // EigenVector_and_Value, compEigenVectors_and_Values, fitFunction_and_legendEntry, makeControlPlot_fit

#include <TFile.h>
#include <TH1.h>
#include <TBenchmark.h>
#include <TCanvas.h>
#include <TPad.h>
#include <TLegend.h>
#include <TMath.h>
#include <TError.h> // gErrorAbortLevel, kError
#include <TList.h>
#include <TKey.h>
#include <TObject.h>
#include <TString.h>
#include <TF1.h>
#include <TFitResult.h>
#include <TGraphAsymmErrors.h>

#include <iostream>
#include <string>
#include <vector>
#include <assert.h>

typedef std::vector<std::string> vstring;

struct addSystType
{
  addSystType(const edm::ParameterSet& cfg)
  {
    name_ = cfg.getParameter<std::string>("name");
    edm::ParameterSet cfg_fakes_mc = cfg.getParameter<edm::ParameterSet>("fakes_mc");
    inputFileName_fakes_mc_ = cfg_fakes_mc.getParameter<std::vector<std::string>>("inputFileName");
    histogramName_fakes_mc_ = cfg_fakes_mc.getParameter<std::string>("histogramName");
    edm::ParameterSet cfg_mcClosure = cfg.getParameter<edm::ParameterSet>("mcClosure");
    inputFileName_mcClosure_ = cfg_mcClosure.getParameter<std::vector<std::string>>("inputFileName");
    histogramName_mcClosure_ = cfg_mcClosure.getParameter<std::string>("histogramName");
  }
  ~addSystType() {}
  void print(std::ostream& stream) const
  {
    stream << "<addSystType>:" << std::endl;
    stream << " name = " << name_ << std::endl;
    stream << " fakes_mc: inputFileName = " << format_vstring(inputFileName_fakes_mc_) << ", histogramName = " << histogramName_fakes_mc_ << std::endl;
    stream << " mcClosure: inputFileName = " << format_vstring(inputFileName_mcClosure_) << ", histogramName = " << histogramName_mcClosure_ << std::endl;
  }
  std::string name_;
  std::vector<std::string> inputFileName_fakes_mc_;
  std::string histogramName_fakes_mc_;
  std::vector<std::string> inputFileName_mcClosure_;
  std::string histogramName_mcClosure_;
};

std::pair<double, double> findXpos(TH1* h, double lowvalue, double highvalue)
{
  TH1* hclone = (TH1*)h->Clone(Form("%s_cloned", h->GetName()));
  hclone->Scale(1/hclone->Integral());
  TH1* cdf =  hclone->GetCumulative();
  double xMin = cdf->GetBinLowEdge(cdf->FindFirstBinAbove(lowvalue));
  double xMax = cdf->GetBinLowEdge(cdf->FindFirstBinAbove(highvalue));
  std::cout << "xmin: " << cdf->GetBinContent(cdf->FindFirstBinAbove(lowvalue)) << "\t xmax: " << cdf->GetBinContent(cdf->FindFirstBinAbove(highvalue)-1) << std::endl;
  delete hclone;
  return std::pair<double, double>(xMin, xMax);
}

TH1* rebin(TH1* h1, double xmin, double xmax, TH1* clone=0)
{
  bool rebin_(false);
  Int_t bin1 = h1->FindBin(xmin);
  Int_t bin2 = h1->FindBin(xmax)-1;
  TH1* h_clone =0;
  if(clone==0) h_clone = (TH1*)h1->Clone(Form("%s_rebinned", h1->GetName()));
  else {
    h_clone = clone;
  }
  if(bin2-bin1 >=3){
    for (Int_t i=bin1; i<=bin2; i++){
      if (h_clone->GetBinContent(i) <10) {
        rebin_ = true;
        break;
      }
    }
  }
  if(rebin_) {
    int nbin = (h1->GetNbinsX()%2 ==0) ? 2 : 1;
    if(nbin==1) return h_clone;
    else {
      h_clone->Rebin(nbin);
      rebin(h_clone, xmin, xmax, h_clone);
    }
  }
  return h_clone;
}

TFile* openInputFile(const std::string& inputFileName, std::map<std::string, TFile*>& inputFiles_syst)
{
  if ( inputFiles_syst.find(inputFileName) == inputFiles_syst.end() ) {
    inputFiles_syst[inputFileName] = new TFile(inputFileName.data());
  }
  return inputFiles_syst[inputFileName];
}

TH1* loadHistogram(TFile* inputFile, const std::string& histogramName)
{
  TH1* histogram = dynamic_cast<TH1*>(inputFile->Get(histogramName.data()));
  if ( !histogram ) 
    throw cms::Exception("addSystFakeRates") 
      << "Failed to load histogram = '" << histogramName << "' from file = '" << inputFile->GetName() << "' !!\n";
  if ( !histogram->GetSumw2N() ) histogram->Sumw2();
  return histogram;
}

TH1* copyHistogram(const TH1* histogram_input, const std::string& histogramName_output)
{
  TH1* histogram_output = 0;
  const TAxis* xAxis = histogram_input->GetXaxis();
  if ( xAxis->GetXbins() ) histogram_output = new TH1F(histogramName_output.data(), histogram_input->GetTitle(), xAxis->GetNbins(), xAxis->GetXbins()->GetArray());
  else histogram_output = new TH1F(histogramName_output.data(), histogram_input->GetTitle(), xAxis->GetNbins(), xAxis->GetXmin(), xAxis->GetXmax());
  int numBins = xAxis->GetNbins();
  for ( int idxBin = 0; idxBin <= (numBins + 1); ++idxBin ) {
    double binContent = histogram_input->GetBinContent(idxBin);
    histogram_output->SetBinContent(idxBin, binContent);
    double binError = histogram_input->GetBinError(idxBin);
    histogram_output->SetBinError(idxBin, binError);
  }
  return histogram_output;
}

TH1* cloneHistogram(const TH1* histogram, const std::string& histogramName_clone)
{
  TArrayD histogramBinning = getBinning(histogram);
  int numBins = histogramBinning.GetSize() - 1;
  TH1* histogram_clone = new TH1F(histogramName_clone.data(), histogramName_clone.data(), numBins, histogramBinning.GetArray());
  if ( !histogram_clone->GetSumw2N() ) histogram_clone->Sumw2();
  for ( int idxBin = 0; idxBin <= (numBins + 1); ++idxBin ) { // CV: include underflow and overflow bins
    double binContent = histogram->GetBinContent(idxBin);
    double binError = histogram->GetBinError(idxBin);
    histogram_clone->SetBinContent(idxBin, binContent);
    histogram_clone->SetBinError(idxBin, binError);
  }
  return histogram_clone;
}

double square(double x)
{
  return x*x;
}

TGraphAsymmErrors* convert_to_TGraph(const TH1* histogram)
{
  const TAxis* xAxis = histogram->GetXaxis();
  int numPoints = xAxis->GetNbins();

  double sumBinContent = 0.;
  double sumBinErr2 = 0.;
  for ( int idxPoint = 0; idxPoint < numPoints; ++idxPoint ) {
    int idxBin = idxPoint + 1;
    sumBinContent += histogram->GetBinContent(idxBin);
    sumBinErr2 += square(histogram->GetBinError(idxBin));
  }
  double numEntries_effective = square(sumBinContent)/sumBinErr2;
  double avWeight = sumBinContent/numEntries_effective;

  TGraphAsymmErrors* graph = new TGraphAsymmErrors(numPoints);
  for ( int idxPoint = 0; idxPoint < numPoints; ++idxPoint ) {
    int idxBin = idxPoint + 1;
    double x = xAxis->GetBinCenter(idxBin);
    double y = histogram->GetBinContent(idxBin);
    graph->SetPoint(idxPoint, x, y);
    double xErrUp = xAxis->GetBinUpEdge(idxBin) - x;
    double xErrDown = x - xAxis->GetBinLowEdge(idxBin);
    double yErrUp = TMath::Sqrt(square(histogram->GetBinError(idxBin)) + square(avWeight));
    double yErrDown = yErrUp;
    graph->SetPointError(idxPoint, xErrDown, xErrUp, yErrDown, yErrUp);
  }
  return graph;
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

int main(int argc, char* argv[]) 
{
//--- throw an exception in case ROOT encounters an error
  gErrorAbortLevel = kError;

//--- parse command-line arguments
  if ( argc < 2 ) {
    std::cout << "Usage: " << argv[0] << " [parameters.py]" << std::endl;
    return EXIT_FAILURE;
  }

  std::cout << "<addSystFakeRates>:" << std::endl;

//--- keep track of time it takes the macro to execute
  TBenchmark clock;
  clock.Start("addSystFakeRates");

//--- read python configuration parameters
  if ( !edm::readPSetsFrom(argv[1])->existsAs<edm::ParameterSet>("process") ) 
    throw cms::Exception("addSystFakeRates") 
      << "No ParameterSet 'process' found in configuration file = " << argv[1] << " !!\n";
  
  edm::ParameterSet cfg = edm::readPSetsFrom(argv[1])->getParameter<edm::ParameterSet>("process");

  edm::ParameterSet cfg_addSystFakeRates = cfg.getParameter<edm::ParameterSet>("addSystFakeRates");
  
  std::string process = cfg_addSystFakeRates.getParameter<std::string>("process");

  std::string histogramToFit = cfg_addSystFakeRates.getParameter<std::string>("histogramToFit");
  std::string category = cfg_addSystFakeRates.getParameter<std::string>("category");
  std::string xAxisTitle = cfg_addSystFakeRates.getParameter<std::string>("xAxisTitle");
  std::string yAxisTitle = cfg_addSystFakeRates.getParameter<std::string>("yAxisTitle");
  bool multiclass = cfg_addSystFakeRates.exists("multiclass") ? cfg_addSystFakeRates.getParameter<bool>("multiclass") : false;

  std::string outputFileNamePrefix = category.empty() ? "" : Form("_%s", category.data());
  outputFileNamePrefix += Form("_%s", histogramToFit.data());

  std::vector<addSystType*> addSystConfigs;
  edm::VParameterSet cfg_addSystConfigs = cfg_addSystFakeRates.getParameter<edm::VParameterSet>("addSyst");
  for ( edm::VParameterSet::const_iterator cfgAddSystConfig = cfg_addSystConfigs.begin();
	cfgAddSystConfig != cfg_addSystConfigs.end(); ++cfgAddSystConfig ) {
    addSystConfigs.push_back(new addSystType(*cfgAddSystConfig));
  }

  std::string outputFileName = cfg_addSystFakeRates.getParameter<std::string>("outputFileName"); // for control plots

  fwlite::InputSource inputFiles(cfg); 
  if ( !(inputFiles.files().size() == 1) )
    throw cms::Exception("addSystFakeRates") 
      << "Exactly one input file expected !!\n";
  TFile* inputFile = new TFile(inputFiles.files().front().data());

  std::map<std::string, TFile*> inputFiles_syst; // key = inputFileName
 
  fwlite::OutputFiles outputFile(cfg);
  fwlite::TFileService fs = fwlite::TFileService(outputFile.file().data());
      
  // copy histograms that do not require modifications
  std::cout << "copying histograms that do not require modifications" << std::endl;
  TList* list1 = inputFile->GetListOfKeys();
  TIter next1(list1);
  TKey* key1 = 0;
  while ( (key1 = dynamic_cast<TKey*>(next1())) ) {
    TObject* object = key1->ReadObj();
    TH1* histogram_input = dynamic_cast<TH1*>(object);

    TFileDirectory* subdir_output = &fs;
    subdir_output->cd();
    
    copyHistogram(histogram_input, histogram_input->GetName());
  }

  // add histograms for "closure" uncertainties of electron, muon, and tau_h fake-rates
  for ( std::vector<addSystType*>::iterator addSystConfig = addSystConfigs.begin();
	addSystConfig != addSystConfigs.end(); ++addSystConfig ) {
    std::cout << "processing addSystConfig = '" << (*addSystConfig)->name_ << "'" << std::endl;

    TH1* histogram_fakes_mc = nullptr;
    for(const std::string & inputFileName_fakes_mc: (*addSystConfig)->inputFileName_fakes_mc_)
    {
      TFile* inputFile_fakes_mc = openInputFile(inputFileName_fakes_mc, inputFiles_syst);
      if(! histogram_fakes_mc)
      {
        histogram_fakes_mc = loadHistogram(inputFile_fakes_mc, (*addSystConfig)->histogramName_fakes_mc_);
      }
      else
      {
        histogram_fakes_mc->Add(loadHistogram(inputFile_fakes_mc, (*addSystConfig)->histogramName_fakes_mc_));
      }
    }
    assert(histogram_fakes_mc);
    std::cout << "histogram_fakes_mc:" << std::endl;
    dumpHistogram(histogram_fakes_mc);
    TGraphAsymmErrors* graph_fakes_mc = convert_to_TGraph(histogram_fakes_mc);
    std::cout << "graph_fakes_mc:" << std::endl;
    dumpGraph(graph_fakes_mc);
    
    TH1* histogram_mcClosure = nullptr;
    for(const std::string & inputFileName_mcClosure: (*addSystConfig)->inputFileName_mcClosure_)
    {
      TFile* inputFile_mcClosure = openInputFile(inputFileName_mcClosure, inputFiles_syst);
      if(! histogram_mcClosure)
      {
        histogram_mcClosure = loadHistogram(inputFile_mcClosure, (*addSystConfig)->histogramName_mcClosure_);
      }
      else
      {
        histogram_mcClosure->Add(loadHistogram(inputFile_mcClosure, (*addSystConfig)->histogramName_mcClosure_));
      }
    }
    assert(histogram_mcClosure);
    std::cout << "histogram_mcClosure:" << std::endl;
    dumpHistogram(histogram_mcClosure);
    TGraphAsymmErrors* graph_mcClosure = convert_to_TGraph(histogram_mcClosure);
    std::cout << "graph_mcClosure:" << std::endl;
    dumpGraph(graph_mcClosure);

    std::string graphName_ratio = Form("graph_ratio_%s", (*addSystConfig)->name_.data());
    TGraphAsymmErrors* graph_ratio = compRatioGraph(graphName_ratio, graph_fakes_mc, graph_mcClosure);
    std::cout << "graph_ratio:" << std::endl;
    dumpGraph(graph_ratio);

    double xMin, xMax;
    if (!multiclass) {
      xMin = histogram_fakes_mc->GetXaxis()->GetXmin();
      xMax = histogram_fakes_mc->GetXaxis()->GetXmax();
    }
    else {
      std::pair<double, double> pair = findXpos(histogram_fakes_mc, 0.049999, 0.949999);
      xMin = pair.first;
      xMax = pair.second;
    }

    double yMax = 1.4*TMath::Max(histogram_fakes_mc->GetMaximum(), histogram_mcClosure->GetMaximum());
    double yMin = TMath::Min(histogram_fakes_mc->GetMinimum(), histogram_mcClosure->GetMinimum());
    if ( yMin < 0. ) yMin *= 1.1;
    else yMin = 0.;
    std::string outputFileName_graphs = std::string(outputFileName, 0, outputFileName.find_last_of('.'));
    outputFileName_graphs.append(Form("%s_%s.png", outputFileNamePrefix.data(), (*addSystConfig)->name_.data()));
    makeControlPlot_graphs(
      graph_fakes_mc, "fakes_mc",
      graph_mcClosure, "mcClosure",
      graph_ratio, 
      histogram_fakes_mc->GetBinLowEdge(1), histogram_fakes_mc->GetBinLowEdge(histogram_fakes_mc->GetNbinsX())+histogram_fakes_mc->GetBinWidth(histogram_fakes_mc->GetNbinsX()), xAxisTitle.data(),
      false, yMin, yMax, yAxisTitle.data(), -1.50, +2.50, "#frac{fakes_mc - mcClosure}{mcClosure}", 
      outputFileName_graphs);

    double integral_fakes_mc = compIntegral(histogram_fakes_mc, false, false);
    double integralErr_fakes_mc = compIntegralErr(histogram_fakes_mc, false, false);
    double integral_mcClosure = compIntegral(histogram_mcClosure, false, false);
    double integralErr_mcClosure = compIntegralErr(histogram_mcClosure, false, false);

    double norm = 1.;
    double normErr = 0.3;

    double slope = 0.;
    double slopeErr = 0.;
    bool fitResult_isValid = false; 
    if ( integral_fakes_mc > 0. && integral_mcClosure > 0. ) {
      norm = integral_fakes_mc/integral_mcClosure;
      normErr = norm*TMath::Sqrt(square(integralErr_fakes_mc/integral_fakes_mc) + square(integralErr_mcClosure/integral_mcClosure));

      TH1* histogram_fakes_mc_rebinned = (multiclass) ? rebin(histogram_fakes_mc, xMin, xMax) : histogram_fakes_mc;
      TGraphAsymmErrors* graph_fakes_mc_rebinned = convert_to_TGraph(histogram_fakes_mc_rebinned);
      if ( histogram_fakes_mc_rebinned->GetNbinsX() >= 3 ) {
	std::string histogramName_mcClosure_scaled = Form("%s_scaled", histogram_mcClosure->GetName());
	TH1* histogram_mcClosure_scaled = cloneHistogram(histogram_mcClosure, histogramName_mcClosure_scaled);
	histogram_mcClosure_scaled->Scale(integral_fakes_mc/integral_mcClosure);
    if(multiclass)
      histogram_mcClosure_scaled->Rebin(histogram_mcClosure_scaled->GetNbinsX()/histogram_fakes_mc_rebinned->GetNbinsX());
	TGraphAsymmErrors* graph_mcClosure_scaled = convert_to_TGraph(histogram_mcClosure_scaled);

	std::string graphName_ratio_scaled = Form("%s_scaled", graph_ratio->GetName());
	TGraphAsymmErrors* graph_ratio_scaled = compRatioGraph(graphName_ratio_scaled, graph_fakes_mc_rebinned, graph_mcClosure_scaled);

	std::string fitFunctionName = Form("%s_fit", graph_ratio_scaled->GetName());
	double x0 = histogram_fakes_mc->GetMean();
	std::string fitFunction_formula_wrt_x0 = Form("[0] + [1]*(x - %f)", x0);
	TF1* fitFunction = new TF1(fitFunctionName.data(), fitFunction_formula_wrt_x0.data(), xMin, xMax);
	fitFunction->SetParameter(0, 1.);
	fitFunction->SetParameter(1, 0.);
	
	TFitResultPtr fitResult = graph_ratio_scaled->Fit(fitFunction, "ERNS");
	fitResult_isValid = fitResult->IsValid();
	if ( fitResult_isValid ) {
	  TMatrixD cov = fitResult->GetCovarianceMatrix();
	  std::vector<EigenVector_and_Value> eigenVectors_and_Values = compEigenVectors_and_Values(cov);
	  size_t dimension = fitFunction->GetNpar();
	  assert(eigenVectors_and_Values.size() == dimension);
	  int idxPar = 1;
	  std::vector<fitFunction_and_legendEntry> fitFunctions_sysShifts;
	  for ( std::vector<EigenVector_and_Value>::const_iterator eigenVector_and_Value = eigenVectors_and_Values.begin();
		eigenVector_and_Value != eigenVectors_and_Values.end(); ++eigenVector_and_Value ) {
	    assert(eigenVector_and_Value->eigenVector_.GetNrows() == (int)dimension);
	    std::cout << "EigenVector #" << idxPar << ":" << std::endl;
	    eigenVector_and_Value->eigenVector_.Print();
	    std::cout << "EigenValue #" << idxPar << " = " << eigenVector_and_Value->eigenValue_ << std::endl;
	    assert(eigenVector_and_Value->eigenValue_ >= 0.);
	    std::string fitFunctionParUpName = Form("%s_par%iUp", fitFunctionName.data(), idxPar);
	    TF1* fitFunctionParUp = new TF1(fitFunctionParUpName.data(), fitFunction_formula_wrt_x0.data(), xMin, xMax);
	    for ( size_t idxComponent = 0; idxComponent < dimension; ++idxComponent ) {    
	      fitFunctionParUp->SetParameter(
		idxComponent, 
		fitFunction->GetParameter(idxComponent) + TMath::Sqrt(eigenVector_and_Value->eigenValue_)*eigenVector_and_Value->eigenVector_(idxComponent));
        }
	    fitFunctions_sysShifts.push_back(fitFunction_and_legendEntry(fitFunctionParUp, Form("EigenVec #%i", idxPar)));
	    std::string fitFunctionParDownName = Form("%s_par%iDown", fitFunctionName.data(), idxPar);
	    TF1* fitFunctionParDown = new TF1(fitFunctionParDownName.data(), fitFunction_formula_wrt_x0.data(), xMin, xMax);
	    for ( size_t idxComponent = 0; idxComponent < dimension; ++idxComponent ) {    
  	      fitFunctionParDown->SetParameter(
	        idxComponent, 
		fitFunction->GetParameter(idxComponent) - TMath::Sqrt(eigenVector_and_Value->eigenValue_)*eigenVector_and_Value->eigenVector_(idxComponent));
	    }
	    fitFunctions_sysShifts.push_back(fitFunction_and_legendEntry(fitFunctionParDown, Form("EigenVec #%i", idxPar)));
	    ++idxPar;
      }
	  std::string outputFileName_fit = std::string(outputFileName, 0, outputFileName.find_last_of('.'));
          outputFileName_fit.append(Form("%s_%s_fit.png", outputFileNamePrefix.data(), (*addSystConfig)->name_.data()));
	  makeControlPlot_fit(
	    graph_ratio_scaled, 
	    fitFunction, fitFunctions_sysShifts, 
	    xMin, xMax, xAxisTitle, 
	    false, -0.5, +3.5, "fakes_mc/mcClosure", 
	    outputFileName_fit,
        histogram_fakes_mc->GetBinLowEdge(1), \
        histogram_fakes_mc->GetBinLowEdge(histogram_fakes_mc->GetNbinsX())+histogram_fakes_mc->GetBinWidth(histogram_fakes_mc->GetNbinsX())
        );
	  slope = fitFunction->GetParameter(1);
	  slopeErr = fitFunction->GetParError(1);
	} else {
	  throw cms::Exception("addSystFakeRates") 
	    << "Fit for observable = '" << (*addSystConfig)->name_ << "' failed to converge !!\n";
	}

        delete histogram_mcClosure_scaled;
        delete graph_mcClosure_scaled;
        if(multiclass)
        {
          delete histogram_fakes_mc_rebinned;
        }
        delete graph_fakes_mc_rebinned;
        delete graph_ratio_scaled;
        delete fitFunction;
      }
    }

    std::cout << "norm = " << norm << " +/- " << normErr << std::endl;
    std::cout << "slope = " << slope << " +/- " << slopeErr << " (fitResult_isValid = " << fitResult_isValid << ")" << std::endl;
    assert(norm > 0.); // require both integrals to be greater than 0
    const double dy_closureNorm = std::fabs(1. - std::min(norm, 2.)); // keep between -1 and +1

    TH1* histogram_data_fakes = loadHistogram(inputFile, process);
    std::cout << "histogram_data_fakes:" << std::endl;
    dumpHistogram(histogram_data_fakes);
   
    // convert results of fit to histogram format and write histograms to output file
    TFileDirectory* subdir_output = &fs;
    subdir_output->cd();

    std::string histogramName_closureNormUp = Form("%s_%s_normUp", process.data(), (*addSystConfig)->name_.data());
    TH1* histogram_closureNormUp = cloneHistogram(histogram_fakes_mc, histogramName_closureNormUp);
    std::string histogramName_closureNormDown = Form("%s_%s_normDown", process.data(), (*addSystConfig)->name_.data());
    TH1* histogram_closureNormDown = cloneHistogram(histogram_fakes_mc, histogramName_closureNormDown);
    std::string histogramName_closureShapeUp = Form("%s_%s_shapeUp", process.data(), (*addSystConfig)->name_.data());
    TH1* histogram_closureShapeUp = cloneHistogram(histogram_fakes_mc, histogramName_closureShapeUp);
    std::string histogramName_closureShapeDown = Form("%s_%s_shapeDown", process.data(), (*addSystConfig)->name_.data());
    TH1* histogram_closureShapeDown = cloneHistogram(histogram_fakes_mc, histogramName_closureShapeDown);
    for ( int idxBin = 1; idxBin <= histogram_fakes_mc->GetNbinsX(); ++idxBin ) {
      double binContent_data_fakes = histogram_data_fakes->GetBinContent(idxBin);
      double binError_data_fakes = histogram_data_fakes->GetBinError(idxBin);
      histogram_closureNormUp->SetBinContent(idxBin, binContent_data_fakes*(1. + dy_closureNorm));
      histogram_closureNormUp->SetBinError(idxBin, binError_data_fakes);
      histogram_closureNormDown->SetBinContent(idxBin, binContent_data_fakes*(1. - dy_closureNorm));
      histogram_closureNormDown->SetBinError(idxBin, binError_data_fakes);
      if ( (integral_fakes_mc > integral_mcClosure) && fabs(dy_closureNorm) ==1) {
        histogram_closureNormDown->SetBinContent(idxBin, binContent_data_fakes);
      }
      else if ( (integral_fakes_mc < integral_mcClosure) && fabs(dy_closureNorm) ==1) {
        histogram_closureNormUp->SetBinContent(idxBin, binContent_data_fakes);
      }
      double x = histogram_fakes_mc->GetXaxis()->GetBinCenter(idxBin);
      double x0 = histogram_fakes_mc->GetMean();
      //double dy_closureShape;
      //if ( slope > 0. ) dy_closureShape = (x - x0)*(slope + slopeErr);
      //else dy_closureShape = (x - x0)*(slope - slopeErr);
      double dy_closureShape = (x - x0)*slope;
      if ( dy_closureShape < -1. ) dy_closureShape = -1.; // CV: keep all bins of histogram_closureShapeUp positive (unless bin is negative in histogram_data_fakes also)
      if ( dy_closureShape > +1. ) dy_closureShape = +1.; // CV: keep all bins of histogram_closureShapeDown positive (unless bin is negative in histogram_data_fakes also)
      histogram_closureShapeUp->SetBinContent(idxBin, binContent_data_fakes*(1. + dy_closureShape));
      histogram_closureShapeUp->SetBinError(idxBin, binError_data_fakes);
      histogram_closureShapeDown->SetBinContent(idxBin, binContent_data_fakes*(1. - dy_closureShape));
      histogram_closureShapeDown->SetBinError(idxBin, binError_data_fakes);
    }
    std::cout << "histogram_closureNormUp:" << std::endl;
    dumpHistogram(histogram_closureNormUp);
    std::cout << "histogram_closureNormDown:" << std::endl;
    dumpHistogram(histogram_closureNormDown);
    std::cout << "histogram_closureShapeUp:" << std::endl;
    dumpHistogram(histogram_closureShapeUp);
    std::cout << "histogram_closureShapeDown:" << std::endl;
    dumpHistogram(histogram_closureShapeDown);
    yMax = 1.4*TMath::Max(histogram_closureNormUp->GetMaximum(), histogram_closureNormDown->GetMaximum());
    yMin = TMath::Min(histogram_closureNormUp->GetMinimum(), histogram_closureNormDown->GetMinimum());
    if ( yMin < 0. ) yMin *= 1.1;
    else yMin = 0.;
    std::string outputFileName_syst = std::string(outputFileName, 0, outputFileName.find_last_of('.'));
    outputFileName_syst.append(Form("%s_%s_syst.png", outputFileNamePrefix.data(), (*addSystConfig)->name_.data()));
    showHistograms(
      800, 900, 
      histogram_data_fakes, process, compIntegral(histogram_data_fakes, false, false),
      histogram_closureNormUp, histogramName_closureNormUp.data(), compIntegral(histogram_closureNormUp, false, false),
      histogram_closureNormDown, histogramName_closureNormDown.data(), compIntegral(histogram_closureNormDown, false, false),
      histogram_closureShapeUp, histogramName_closureShapeUp.data(), compIntegral(histogram_closureShapeUp, false, false),
      histogram_closureShapeDown, histogramName_closureShapeDown.data(), compIntegral(histogram_closureShapeDown, false, false),
      NULL, "", 0.,
      xAxisTitle, 1.10,
      false, yMin, yMax, yAxisTitle, 1.30,
      0.34, 0.72,
      outputFileName_syst.data());
    histogram_closureNormUp->Write();
    histogram_closureNormDown->Write();
    histogram_closureShapeUp->Write();
    histogram_closureShapeDown->Write();
    
    // delete temporary objects
    delete graph_fakes_mc;
    delete graph_mcClosure;
    delete graph_ratio;
  }
  
  clock.Show("addSystFakeRates");
  
  return 0;
}
